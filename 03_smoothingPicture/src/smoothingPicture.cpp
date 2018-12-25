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

	string windowNameIn ("SmoothingPicture in");
	string windowNameOut ("SmoothingPicture out");

	// smoothing: redures the information content of the image convolving it with a Gaussian
	// or similar function

	cv::Mat img = cv::imread(argv[1], -1);
	if (img.empty())
		return -1;

	cv::namedWindow(windowNameIn, cv::WINDOW_AUTOSIZE);
	cv::namedWindow(windowNameOut, cv::WINDOW_AUTOSIZE);

	cv::imshow(windowNameIn, img);

	cv::Mat out;

	// do the smoothing: we could use GaussianBlur(), blur(), medianBlur() or bilateralFilter()
	// We use two consecutive GaussianBlur to make clearer the trasformation
	// The size of the Gaussian kernel should always be given in odd numbers since
	// the Gaussian kernel is computed at the center pixelin that area
	cv::GaussianBlur(img, out, cv::Size(5, 5), 3, 3);
	cv::GaussianBlur(out, out, cv::Size(5, 5), 3, 3);
	cv::imshow(windowNameOut, out);

	cv::waitKey(0);
	cv::destroyWindow(windowNameIn);
	cv::destroyWindow(windowNameOut);

	return 0;
}

