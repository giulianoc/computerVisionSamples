#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{

	/*
	if (argc != 3)
	{
		cerr << "Usage: " << argv[0] << " <in video path name> <out video path name>" << endl;
		cerr << "\t[ESC]: exit" << endl;

		return 1;
	}
	*/

	string windowName ("FaceRecognition");
	string cascadeName("/home/giuliano/catramms/opencv/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml");
	double scale = 1.1;
	int minNeighbors = 2;
	bool tryFlip = false;

	cv::CascadeClassifier cascade;

	if (!cascade.load(cascadeName))
	{
		cerr << "Could not load classifier cascade" << endl;

		return 1;
	}

	cv::VideoCapture capture(0);
	if (!capture.isOpened())
	{
		cerr << "Capture could not be opened" << endl;

		return 1;
	}

	cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);

	cv::Mat bgrFrame;
	cv::Mat grayFrame;
	cv::Mat smallFrame;

	while(true)
	{
		capture >> bgrFrame;
		if (bgrFrame.empty())
			break;

		cv::cvtColor(bgrFrame, grayFrame, cv::COLOR_BGR2GRAY);
		double fx = 1 / scale;
		cv::resize(grayFrame, smallFrame, cv::Size(), fx, fx, cv::INTER_LINEAR_EXACT);
		cv::equalizeHist(smallFrame, smallFrame);
		double t = (double) cv::getTickCount();
		vector<cv::Rect> faces;
		cascade.detectMultiScale(
				smallFrame,
				faces,
				scale,
				minNeighbors,
				0 | cv::CASCADE_SCALE_IMAGE,
				cv::Size(30,30)
				);
		if (tryFlip)
		{
			// 1: flip (mirror) horizontally
			cv::flip(smallFrame, smallFrame, 1);
			vector<cv::Rect> faces2;
			cascade.detectMultiScale(
				smallFrame,
				faces2,
				scale,
				minNeighbors,
				0 | cv::CASCADE_SCALE_IMAGE,
				cv::Size(30,30)
				);
			for (vector<cv::Rect>::const_iterator r = faces2.begin(); r != faces2.end(); ++r)
				faces.push_back(cv::Rect(
							smallFrame.cols - r->x - r->width,
							r->y,
							r->width,
							r->height
							));
		}
		t = (double) cv::getTickCount() - t;
		cout << "Detection time = " << t*1000/cv::getTickFrequency() << "ms" << endl;

		cv::Scalar color = cv::Scalar(255,0,0);
		for (size_t i = 0; i < faces.size(); i++)
		{
			cv::Rect r = faces[i];
			cv::Mat smallROI;
			cv::Point center;
			int radius;

			double aspectRatio = (double) r.width / r.height;
			if (0.75 < aspectRatio && aspectRatio < 1.3)
			{
				center.x = cvRound((r.x + r.width*0.5)*scale);
				center.y = cvRound((r.y + r.height*0.5)*scale);
				radius = cvRound((r.width + r.height)*0.25*scale);
				cv::circle(bgrFrame, center, radius, color, 3, 8, 0 );  
			}
			else
			{
				cv::rectangle(bgrFrame, cv::Point(cvRound(r.x*scale), cvRound(r.y*scale)),
					cv::Point(cvRound((r.x + r.width-1)*scale), cvRound((r.y + r.height-1)*scale)),
					color, 3, 8, 0);
			}
		}

		// cv::imwrite(...);

		cv::imshow(windowName, bgrFrame);

		char c = (char) cv::waitKey(20);
		if (c == 27)
			break;
	}

	cv::destroyWindow(windowName);

	capture.release();


	return 0;
}

