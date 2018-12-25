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
		cerr << "\t[i]: Zoom in" << endl;
		cerr << "\t[o]: Zoom out" << endl;
		cerr << "\t[ESC]: exit" << endl;

		return 1;
	}

	string windowName ("PyrUpAndDownPicture");

	cv::Mat img = cv::imread(argv[1], -1);
	if (img.empty())
		return -1;

	cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);

	cv::imshow(windowName, img);

	// pryDown: downsample (reduce size) an image
	// pryUp: upsample (increase size) an image
	while(true)
	{
		cv::imshow(windowName, img);
		char c = (char) cv::waitKey(0);
		if (c == 'i')
		{
			cout << "Zoom in: Image x 2 from (" << img.rows << ", " << img.cols << ")" << endl;
			cv::pyrUp(img, img, cv::Size(img.cols*2, img.rows*2));
			cout << "to (" << img.rows << ", " << img.cols << ")" << endl;
		}
		else if (c == 'o')
		{
			cout << "Zoom out: Image / 2 from (" << img.rows << ", " << img.cols << ")" << endl;
			cv::pyrDown(img, img, cv::Size(img.cols/2, img.rows/2));
			cout << "from (" << img.rows << ", " << img.cols << ")" << endl;
		}
		else if (c == 27)
			break;
	}

	cv::destroyWindow(windowName);

	return 0;
}

