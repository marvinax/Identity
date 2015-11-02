#include "QRLocator.h"

using namespace cv;

bool intersection(Point2f o1, Point2f p1, Point2f o2, Point2f p2,
                      Point2f &r)
{
    Point2f x = o2 - o1;
    Point2f d1 = p1 - o1;
    Point2f d2 = p2 - o2;

    float cross = d1.x*d2.y - d1.y*d2.x;
    if (std::abs(cross) < /*EPS*/1e-8)
        return false;

    double t1 = (x.x * d2.y - x.y * d2.x)/cross;
    r = o1 + d1 * t1;
    return true;
}

int findTopLeft(vector<Point2f>& points){
	double AB = norm(points[0] - points[1]);
	double BC = norm(points[1] - points[2]);
	double CA = norm(points[2] - points[0]);

	if ( AB > BC && AB > CA ) {
		return 2;
	}
	else if ( CA > AB && CA > BC ) {
		return 1;
	}
	else if ( BC > AB && BC > CA ) {
		return 0;
	} else {
		return -1;
	}
}

int findTopRight(vector<Point2f>& points){
	int topLeft = findTopLeft(points);

	Point2f shortEdge1 = points[(topLeft-1)%3] - points[topLeft];
	Point2f shortEdge2 = points[(topLeft+1)%3] - points[topLeft];

	if (shortEdge1.x * shortEdge2.y - shortEdge1.y * shortEdge2.x < 0){
		// Means shortEdge1 have larger angle than shortEdge2, which
		// measn the point on the other side of shortEdge1 is topRight.
		return (topLeft - 1) % 3;
	} else {
		return (topLeft + 1) % 3;
	}
}

vector<Point> findOuterContour(vector<vector<Point>>& contours, vector<Vec4i>& hierarchy, int index){
	int out, count;
	for(count = 0, out = index; count < 5; count += 1, out = hierarchy[out][3]){}
	return contours[out];
}

void sortRectangleCorners(vector<Point>& rectangle, Point2f m){
	sort(rectangle, [m](const Point& a, const Point& b)->bool{
		float angleA = atan2(a.y - m.y, a.x - m.x);
		angleA = angleA > 0 ? angleA : 3.14159265358979323846*2 + angleA;

		float angleB = atan2(b.y - m.y, b.x - m.x);
		angleB = angleB > 0 ? angleB : 3.14159265358979323846*2 + angleB;

		return angleA > angleB;
	});
}

// A function to find the outermost rectangles of the align marker. It takes contours and
// hierarchy as argument, along with the list of the indices of the innermost contours.
// Firstly, it arranges the sequence of the three markers, with the order of top-left,
// bottom-left and then top-right. Then the points within the rectangles are arranged by
// the angle in polar coordinate.
void rearrangeAlignMarkers(	vector<vector<Point>>& contours, vector<Vec4i>& hierarchy, vector<int>&indices,
						vector<Point2f>& massCenters, vector<vector<Point>>& rectangles){

	vector<int> arrangedIndices(0);
	vector<Point2f> arrangedMassCenters(0);

	int topLeft = findTopLeft(massCenters);
	int topRight = findTopRight(massCenters);
	int bottomLeft = 3 - topLeft - topRight;

	arrangedIndices.push_back(indices[topLeft]);
	arrangedIndices.push_back(indices[bottomLeft]);
	arrangedIndices.push_back(indices[topRight]);

	arrangedMassCenters.push_back(massCenters[topLeft]);
	arrangedMassCenters.push_back(massCenters[bottomLeft]);
	arrangedMassCenters.push_back(massCenters[topRight]);

	std::cout << arrangedMassCenters << std::endl;

	for (int i = 0; i < 3; i++){
		approxPolyDP(findOuterContour(contours, hierarchy, indices[i]), rectangles[i], 10., true);
		sortRectangleCorners(rectangles[i], massCenters[i]);
	}
}

// Very initial operation on the detrended (gradient-compensated) image. It finds 
// the edge of the QR align markers, and then find the contours.
void findAllContours(Mat &image, vector<vector<Point>> &contours, vector<Vec4i> &hierarchy){
	Mat edges;
	image.copyTo(edges);

	threshold(edges, edges, 100, 255, THRESH_BINARY);
	// Canny detects the outline of the black border on the tag. While the
	// Sobel detecter could be only with diameter of 3. However, the basic
	// Canny detector doesn't gurarantee that the contour is continuous.
	// Thus we do some morphological transform on the image, so that to
	// enforce the enclosed border connected.
	Canny(edges, edges, 100, 200, 3);

	// here we do a simple morphological opening transform make the border
	// more smooth and clear. 
	int dSize = 2, eSize = 1;
	Mat dElem = getStructuringElement(MORPH_RECT, Size( 2*dSize + 1, 2*dSize+1 ), Point( dSize, dSize ) );
	Mat eElem = getStructuringElement(MORPH_RECT, Size( 2*eSize + 1, 2*eSize+1 ), Point( eSize, eSize ) );	
	dilate(edges, edges, dElem);
	erode(edges, edges, eElem);

	// After applying the Canny operation, we will have five layer of contours
	// the contour topological information will be stored in `hierarchy` table.
	findContours(edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
}

void findAlignMarkerContours(
	vector<vector<Point>>& contours, vector<Vec4i>& hierarchy,
	vector<Point2f>& alignMarkerMassCenters, vector<int>& alignMarkerContourIndices
){
	// massCenters will be stored, which will be further used for sorting the
	// points over the rectangles.
	vector<Moments> contourMoments(contours.size());
	vector<Point2f> massCenters(contours.size());

	for( unsigned long i = 0; i < contours.size(); i++ ) {
		contourMoments[i] = moments( contours[i], false ); 
		massCenters[i] = Point2f(
			contourMoments[i].m10/contourMoments[i].m00,
			contourMoments[i].m01/contourMoments[i].m00
		);
	}

	for( int i = 0; i < (int)(contours.size()); i++ ) {
		int k = i, c = 0;

		for(; hierarchy[k][2] != -1; k = hierarchy[k][2], c = c+1){}
		
		if (c > 4) {
			alignMarkerMassCenters.push_back(massCenters[i]);
			alignMarkerContourIndices.push_back(k);
		}

	} 

}

void findFourCorners(Mat &image, vector<vector<Point>>& rectangles, vector<Point2f>& corners){

	corners.push_back(Point2f(rectangles[0][2].x, rectangles[0][2].y));
	corners.push_back(Point2f(rectangles[1][1].x, rectangles[1][1].y));
	corners.push_back(Point2f(rectangles[2][0].x, rectangles[2][0].y));

	for (int i = 0; i < 3; i++){
		circle(image, corners[i], 20, Scalar(i*127), -1);
	}	
}

vector<Point2f> findQRAlignMarker(Mat &image){

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findAllContours(image, contours, hierarchy);

	// Iterate over the whole contour topogical tree and find nested
	// contour. We need both the mass center and the index of the
	// innermost contour of the align markers. Mass centers are for finding
	// the farthest point of the outermost contour of the align markers,
	// in order to find the bound of QR area.
	vector<Point2f> alignMarkerMassCenters(0);
	vector<int>     alignMarkerContourIndices(0);
	findAlignMarkerContours(contours, hierarchy, alignMarkerMassCenters, alignMarkerContourIndices);

	// If we didn't collected enough align markers, we'll return (and
	// supposed to have an error message). Otherwise we are going
	// re-arrange the points with a sequence of top-left, bottom-left,
	// bottom-right.
	// 
	vector<vector<Point>> rectangles(3, vector<Point>(0));
	rearrangeAlignMarkers(contours, hierarchy, alignMarkerContourIndices, alignMarkerMassCenters, rectangles);

	vector<Point2f> corners;
	findFourCorners(image, rectangles, corners);

	vector<Point2f> res;

	return res;
}