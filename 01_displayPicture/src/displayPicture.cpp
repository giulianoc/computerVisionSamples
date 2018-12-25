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

	string windowName ("DisplayPicture");

	cv::Mat img = cv::imread(argv[1], -1);
	if (img.empty())
		return -1;

	cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
	cv::imshow(windowName, img);

	cv::waitKey(0);
	cv::destroyWindow(windowName);
}

