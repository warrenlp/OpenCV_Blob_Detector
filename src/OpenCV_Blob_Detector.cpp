//============================================================================
// Name        : OpenCV_Blob_Detector.cpp
// Author      : warren
// Version     :
// Copyright   : Please, hack this code at your leisure!!!
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "SimpleBlobDetectorWrapper.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>

int main() {

	string windowName("Keypoints");
	string url("http://root:pass@192.168.0.19/axis-cgi/mjpg/video.cgi");

	// Use int 0 for default USB configuration
	// Use your own custom  "url" if pulling from an ip web camera
	cv::VideoCapture cap(url);

	if (!cap.isOpened())
	{
		std::cout << "Could not read or open url: " << url << std::endl;
		return -1;
	}

	CSimpleBlobDetectorWrapper simpleBlobDetector;

	string fileName = "SimpleBlobDetectorParams.xml";

	int errorCode = simpleBlobDetector.read(fileName);
	if (errorCode == -1)
	{
		cerr << "Could not read or open file: " << fileName << endl;
		return -1;
	}

	cv::namedWindow(windowName, CV_WINDOW_NORMAL);

	vector<string> trackbarNames;

	simpleBlobDetector.createTrackBars(windowName, trackbarNames);

	cv::Mat frame;
	vector<cv::KeyPoint> keypoints;

	for (;;)
	{
		cap >> frame;

		if( frame.empty() )
		{
			cout << "Could not load frame" << endl;
			continue;
		}

		simpleBlobDetector.detectImpl(frame, keypoints);

	    cv::Mat outImg = frame.clone();
	    for(size_t i=0; i<keypoints.size(); ++i)
	    {
	        cv::circle(outImg, keypoints[i].pt, keypoints[i].size, cv::Scalar(255, 0, 255), -1);
	    }
	    //drawKeypoints(image, keypoints, outImg);
	    cv::imshow(windowName, outImg);

		if (cv::waitKey(30) > 0)
			break;
	}

	return 0;
}
