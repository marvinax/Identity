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

// A function that turns the outermost contour of the align markers into rectangle for further calculation.
// such as sorting and rearranging
void getRectangles(	vector<vector<Point>>& contours, vector<int>&indices,
					vector<vector<Point>>& rectangles){

	for (int i = 0; i < 3; i++){
		approxPolyDP(contours[indices[i]], rectangles[i], 10., true);
	}
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


void rearrangeRectangles(vector<vector<Point>>& rectangles){

	vector<Moments> rectMoments(rectangles.size());
	vector<Point2f> massCenters(rectangles.size());

	for( unsigned long i = 0; i < rectangles.size(); i++ ) {
		rectMoments[i] = moments( rectangles[i], false ); 
		massCenters[i] = Point2f(
			rectMoments[i].m10/rectMoments[i].m00,
			rectMoments[i].m01/rectMoments[i].m00
		);

		sortRectangleCorners(rectangles[i], massCenters[i]);
	}

	int topLeft, topRight, bottomLeft;

	topLeft = findTopLeft(massCenters);
	topRight = findTopRight(massCenters);
	bottomLeft = 3 - topLeft - topRight;

	vector<vector<Point>> sortedRectangles;
	sortedRectangles.push_back(rectangles[topLeft]);
	sortedRectangles.push_back(rectangles[bottomLeft]);
	sortedRectangles.push_back(rectangles[topRight]);
	rectangles = sortedRectangles;

	for (unsigned long i = 0 ; i < rectangles.size(); i++){
		std::cout << rectangles[i] << std::endl;
	}

}

// Very initial operation on the detrended (gradient-compensated) image. It finds 
// the edge of the QR align markers, and then find the contours.
void findAllContours(	Mat &image, vector<vector<Point>> &contours, vector<Vec4i> &hierarchy,
						int dilationSize
					){
	Mat edges;
	image.copyTo(edges);

	// When using some paper with special material, the ink could not stick to some part
	// on the paper, which may lead a small contour appear on the center of align marker.
	// the threshold should be adjustable from the outside, or adaptively adjusted.
	threshold(edges, edges, 100, 255, THRESH_BINARY);

	// Canny detects the outline of the black border on the tag. While the
	// Sobel detecter could be only with diameter of 3. However, the basic
	// Canny detector doesn't gurarantee that the contour is continuous.
	// Thus we do some morphological transform on the image, so that to
	// enforce the enclosed border connected.
	Canny(edges, edges, 60, 200, 3);
	imwrite("./public/images/Canny.jpg", edges);

	// here we do a simple morphological opening transform make the border
	// more smooth and clear. 
	// 
	// NOTE: for scanned original patch, the dilation size should be no more
	// 		 than 1. Since excessive dilation will cause less contours. The
	// 		 dilation size should be proportional to the scale of the image.
	int dSize = dilationSize, eSize = 1;
	Mat dElem = getStructuringElement(MORPH_RECT, Size( 2*dSize + 1, 2*dSize+1 ), Point( dSize, dSize ) );
	Mat eElem = getStructuringElement(MORPH_RECT, Size( 2*eSize + 1, 2*eSize+1 ), Point( eSize, eSize ) );	
	dilate(edges, edges, dElem);
	erode(edges, edges, eElem);
	imwrite("./public/images/morphed.jpg", edges);

	// After applying the Canny operation, we will have five layer of contours
	// the contour topological information will be stored in `hierarchy` table.
	findContours(edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
	imwrite("./public/images/contours.jpg", edges);

}

void findAlignMarkerContours(
	vector<vector<Point>>& contours, vector<Vec4i>& hierarchy,
	vector<int>& alignMarkerContourIndices
){
	// massCenters will be stored, which will be further used for sorting the
	// points over the rectangles.

	for( int i = 0; i < (int)(contours.size()); i++ ) {
		int k = i, c = 0;

		for(; hierarchy[k][2] != -1; k = hierarchy[k][2], c++){}
		
		if (c > 4) {

			for(; c > 0; k = hierarchy[k][3], c--){}

			alignMarkerContourIndices.push_back(k);
		}

	}



}

void findFourCorners(Mat &image, vector<vector<Point>>& rectangles, vector<Point2f>& corners){

	corners.push_back(Point2f(rectangles[0][1].x, rectangles[0][1].y));
	corners.push_back(Point2f(rectangles[1][0].x, rectangles[1][0].y));
	corners.push_back(Point2f(rectangles[2][2].x, rectangles[2][2].y));

	Point2f fourthPoint;
	intersection(rectangles[1][0], rectangles[1][3], rectangles[2][2], rectangles[2][3], fourthPoint);

	corners.push_back(fourthPoint);

	for (int i = 0; i < 4; i++){
		circle(image, corners[i], 15, Scalar(64*i), -1);
	}	

	imwrite("./public/images/marked.jpg", image);
}

vector<Point2f> findQRAlignMarker(Mat &image, int dilationSize){

	std::cout << "findQRAlignMarker-Begin" << std::endl;

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findAllContours(image, contours, hierarchy, dilationSize);
	std::cout << "findQRAlignMarker-All Contours Found" << std::endl;


	// Iterate over the whole contour topogical tree and find nested
	// contour. We need both the mass center and the index of the
	// innermost contour of the align markers. Mass centers are for finding
	// the farthest point of the outermost contour of the align markers,
	// in order to find the bound of QR area.
	// vector<Point2f> alignMarkerMassCenters(0);
	vector<int>     alignMarkerContourIndices(0);
	findAlignMarkerContours(contours, hierarchy, alignMarkerContourIndices);
	std::cout << "findQRAlignMarker-Align Marker Contours Found" << std::endl;
	for(unsigned long i = 0; i < alignMarkerContourIndices.size(); i++){
	std::cout << alignMarkerContourIndices[i] << " "<< std::endl;		
	}
	// If we didn't collected enough align markers, we'll return (and
	// supposed to have an error message). Otherwise we are going
	// re-arrange the points with a sequence of top-left, bottom-left,
	// bottom-right.
	// 
	vector<vector<Point>> rectangles(3, vector<Point>(0));
	getRectangles(contours, alignMarkerContourIndices, rectangles);
	rearrangeRectangles(rectangles);

	vector<Point2f> corners;
	findFourCorners(image, rectangles, corners);

	std::cout << "findQRAlignMarker-End" << std::endl;

	return corners;
}