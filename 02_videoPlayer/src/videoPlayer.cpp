#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>

using namespace std;

int g_slider_position = 0;
// g_run:
//	if it is != 0, it displays new frames
//	if it is > 0, it indicates how many frames are displayed before stopping
//	if it is < 0, system run in continuous video mode
int g_run = 1;

// we want to have Single Step (g_run = 1) when the user use the Trackbar
// To do this:
//	set g_userSetPosition to false inside the loop for(;;)
//	set g_userSetPosition to true inside the onChangeTrackbarSlide callback
// In case inside the callback g_userSetPosition is true, it means the user used the callback
bool g_userSetPosition = false;

cv::VideoCapture g_cap;

void onChangeTrackbarSlide(int pos, void*)
{
	// at this point pos and g_slider_position will have the same value
	g_cap.set(cv::CAP_PROP_POS_FRAMES, pos);

	if (g_userSetPosition)
		g_run = 1;
	g_userSetPosition = true;
}

int main(int argc, char**argv)
{
	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <video path name>" << endl;

		return 1;
	}

	cv::namedWindow("VideoPlayer", cv::WINDOW_AUTOSIZE);

	g_cap.open(string(argv[1]));

	int frames = (int) g_cap.get(cv::CAP_PROP_FRAME_COUNT);
	int tmpw = (int) g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int tmph = (int) g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);

	cout << "Video has " << frames << " frames of dimensions(" << tmpw << ", " << tmph << ")." << endl;

	// cv::createTrackbar("Position", "VideoPlayer", &g_slider_position, frames, onChangeTrackbarSlide);

	cv::Mat frame;
	bool trackBarToBeInitialized = true;
	for (;;)
	{
		if(g_run != 0)
		{
			g_cap >> frame;
			if (frame.empty())
				break;

			if (trackBarToBeInitialized)
			{
				cv::createTrackbar("Position", "VideoPlayer", &g_slider_position, frames, onChangeTrackbarSlide);
				trackBarToBeInitialized = false;
			}

			int current_pos = (int) g_cap.get(cv::CAP_PROP_POS_FRAMES);
			g_userSetPosition = false;

			cv::setTrackbarPos("Position", "VideoPlayer", current_pos);
			cv::imshow("VideoPlayer", frame);

			g_run -= 1;
		}

		char c = (char) cv::waitKey(10);
		if (c == 's')
		{
			g_run = 1;
			cout << "Single step, run = " << g_run << endl;
		}
		else if (c == 'r')
		{
			g_run = -1;
			cout << "Run mode, run = " << g_run << endl;
		}
		else if (c == 27)	// ESC
			break;
	}

	cv::destroyWindow("VideoPlayer");

	return 0;
}

