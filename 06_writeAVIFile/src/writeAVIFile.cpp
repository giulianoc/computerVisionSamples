#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{

	if (argc != 3)
	{
		cerr << "Usage: " << argv[0] << " <in video path name> <out video path name>" << endl;
		cerr << "\t[ESC]: exit" << endl;

		return 1;
	}

	string windowName ("WriteFile");
	string windowNameLogPolar ("WriteFile Log_Polar");

	cv::VideoCapture capture(argv[1]);

	double fps = capture.get(cv::CAP_PROP_FPS);
	cv::Size size(
			(int) capture.get(cv::CAP_PROP_FRAME_WIDTH),
			(int) capture.get(cv::CAP_PROP_FRAME_HEIGHT)
	);

	cv::VideoWriter writer;

	// writer.open(argv[2], cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, size);
	writer.open(argv[2], cv::VideoWriter::fourcc('X', '2', '6', '4'), fps, size);

	cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
	cv::namedWindow(windowNameLogPolar, cv::WINDOW_AUTOSIZE);

	cv::Mat logPolarFrame;
	cv::Mat bgrFrame;

	while(true)
	{
		capture >> bgrFrame;
		if (bgrFrame.empty())
			break;

		cv::imshow(windowName, bgrFrame);

		cv::logPolar(
				bgrFrame,
				logPolarFrame,
				cv::Point2f(			// Center point for log polar transformation 
					bgrFrame.cols/2,
					bgrFrame.rows/2
					),
				40,						// magnitude (scale parameter)
				cv::WARP_FILL_OUTLIERS	// fill outliers with 'zero'
				);

		cv::imshow(windowNameLogPolar, logPolarFrame);

		writer << logPolarFrame;

		char c = (char) cv::waitKey(33);
		if (c == 27)
			break;
	}

	cv::destroyWindow(windowName);
	cv::destroyWindow(windowNameLogPolar);

	capture.release();


	return 0;
}

