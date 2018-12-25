#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{

	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <picture path name>" << endl;

		return 1;
	}

	string windowNameGry ("CannyPicture Gray");
	string windowNameCny ("CannyPicture Canny");

	// canny edge detector needs only a single channel image to write to,
	// so we convert to a grayscale

	cv::Mat img_rgb = cv::imread(argv[1], -1);
	if (img_rgb.empty())
		return -1;

	cv::namedWindow(windowNameGry, cv::WINDOW_AUTOSIZE);
	cv::namedWindow(windowNameCny, cv::WINDOW_AUTOSIZE);

	cv::Mat img_gry;
	cv::Mat img_cny;

	cv::cvtColor(img_rgb, img_gry, cv::COLOR_BGR2GRAY);
	cv::imshow(windowNameGry, img_gry);

	cv::Canny(img_gry, img_cny, 10, 100, 3, true);
	cv::imshow(windowNameCny, img_cny);

	cv::waitKey(0);
	cv::destroyWindow(windowNameGry);
	cv::destroyWindow(windowNameCny);

	return 0;
}

