#include "ZBarQRLocator.h"

void findSingleQR(Mat &source, std::vector<Point2f> &warpSourcePoints, std::string &data){

    cv::Mat image;
    threshold(source, image, 128, 255, THRESH_BINARY);

    ImageScanner scanner;
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

    Image imageForQRDecode(image.cols, image.rows, "Y800", image.data, image.cols * image.rows);
    std::cout << "QR code found: " << scanner.scan(imageForQRDecode) << std::endl;

    for (Image::SymbolIterator symbol = imageForQRDecode.symbol_begin(); symbol != imageForQRDecode.symbol_end(); ++symbol) {
        data = symbol->get_data();

        std::cout << data << std::endl;
        if (symbol->get_location_size() == 4) {
            warpSourcePoints.push_back(Point(symbol->get_location_x(0), symbol->get_location_y(0)));
            warpSourcePoints.push_back(Point(symbol->get_location_x(3), symbol->get_location_y(3)));
            warpSourcePoints.push_back(Point(symbol->get_location_x(2), symbol->get_location_y(2)));
            warpSourcePoints.push_back(Point(symbol->get_location_x(1), symbol->get_location_y(1)));
        }
    }
}

void findMultipleQR(Mat &image, std::string &data){
    ImageScanner scanner;
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

    Image imageForQRDecode(image.cols, image.rows, "Y800", image.data, image.cols * image.rows);
    std::cout << scanner.scan(imageForQRDecode) << std::endl;

    std::string name = "";
    for (Image::SymbolIterator symbol = imageForQRDecode.symbol_begin(); symbol != imageForQRDecode.symbol_end(); ++symbol) {
        name += symbol->get_data() + " ";
    }

    data = name;
}
