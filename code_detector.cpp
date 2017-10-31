#include <iostream>
#include <zbar.h>
#include "cv.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;
using namespace zbar;

int main()
{
	int width, height;
	uchar *raw;
	Image::SymbolIterator symbol;
	VideoCapture camera(-1);
	if (!camera.isOpened())
		return -1;
	ImageScanner scanner;
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
	Mat image, imageGray;

	while (1) {
		if (!camera.read(image))
			return -1;
		cvtColor(image, imageGray, CV_RGB2GRAY);
		width = imageGray.cols;
		height = imageGray.rows;
		raw = (uchar *)imageGray.data; 
		Image imageZbar(width, height, "Y800", raw, width * height);
		scanner.scan(imageZbar);
		symbol = imageZbar.symbol_begin();
		for (; symbol != imageZbar.symbol_end(); ++symbol)
			cout << symbol->get_data() << endl;
		imshow("Source Image",image);
		waitKey(1);
		imageZbar.set_data(NULL,0); 
	} 
	return 0;
}
