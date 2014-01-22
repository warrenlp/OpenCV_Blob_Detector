/*
 * SimpleBlobDetectorWrapper.cpp
 *
 *  Created on: Jan 21, 2014
 *      Author: warren
 */

#include "SimpleBlobDetectorWrapper.h"

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
using namespace std;

CSimpleBlobDetectorWrapper::CSimpleBlobDetectorWrapper(const SimpleBlobDetector::Params &parameters)
	: SimpleBlobDetector(parameters),
	  m_area_max(10000)
{
	// Do nothing
}

CSimpleBlobDetectorWrapper::~CSimpleBlobDetectorWrapper()
{
	// Do nothing
}

void CSimpleBlobDetectorWrapper::detectImpl(const cv::Mat& image, std::vector<cv::KeyPoint>& keypoints, const cv::Mat& mask) const
{
	// This method is protected in parent class, so we expose it with public wrapper function
	SimpleBlobDetector::detectImpl(image, keypoints, mask);
}

int CSimpleBlobDetectorWrapper::read(const string& fileName)
{
	// Read default parameters from file
	cv::FileStorage fileStorage(fileName, cv::FileStorage::READ);

	if (!fileStorage.isOpened())
	{
		cerr << "Failed to open " << fileName << endl;
		return -1;
	}

	cv::FileNode fn =  fileStorage["opencv_storage"];

	SimpleBlobDetector::read(fn);

	fileStorage.release();

	return 0;
}

void CSimpleBlobDetectorWrapper::createTrackBars(const string& windowName, vector<string>& trackbarNames)
{
	int blobColorTrack = static_cast<int>(this->params.blobColor);
	int minThresholdTrack = static_cast<int>(this->params.minThreshold);
	int maxThresholdTrack = static_cast<int>(this->params.maxThreshold);
	int maxAreaTrack = static_cast<int>(this->params.maxArea);
	int minAreaTrack = static_cast<int>(this->params.minArea);

	// For some reason, the trackbar in the first position seems to have trouble.
	//	I've set up a dummy bar that does nothing.
	cv::createTrackbar(string("dummy bar"),
			windowName,
			&blobColorTrack,
			1,
			on_dummy_trackbar,
			this);

	// With the default code as written, the blobColor simple detects whether or not
	// 	a blob falls above or below a threshold value
	cv::createTrackbar(string("blobColor"),
			windowName,
			&blobColorTrack,
			1,
			on_blob_color_trackbar,
			this);

	cv::createTrackbar(string("minThreshold"),
			windowName,
			&minThresholdTrack,
			255,
			on_min_threshold_trackbar,
			this);

	cv::createTrackbar(string("maxThreshold"),
			windowName,
			&maxThresholdTrack,
			255,
			on_max_threshold_trackbar,
			this);

	cv::createTrackbar(string("maxArea"),
			windowName,
			&maxAreaTrack,
			m_area_max,
			on_max_area_trackbar,
			this);

	cv::createTrackbar(string("minArea"),
			windowName,
			&minAreaTrack,
			1000,
			on_min_area_trackbar,
			this);
}

void CSimpleBlobDetectorWrapper::SetMinThreshold(float minThreshold)
{
	if (minThreshold >= 255)
	{
		params.minThreshold = 255;
	}
	else if (minThreshold <= 0)
	{
		params.minThreshold = 0;
	}
	else
	{
		params.minThreshold = minThreshold;
	}
}

void CSimpleBlobDetectorWrapper::SetMaxThreshold(float maxThreshold)
{
	params.maxThreshold = cv::saturate_cast<uchar>(maxThreshold);
}

void CSimpleBlobDetectorWrapper::SetMaxArea(float maxArea)
{
	if (m_area_max >= maxArea)
	{
		params.maxArea = maxArea;
	}
	else
	{
		params.maxArea = m_area_max;
	}
}

void CSimpleBlobDetectorWrapper::SetMinArea(float minArea)
{
	if (params.maxArea >= minArea)
	{
		params.minArea = minArea;
	}
	else if (minArea <= 25)
	{
		params.minArea = 25;
	}
	else
	{
		params.minArea = params.maxArea;
	}
}

void CSimpleBlobDetectorWrapper::SetBlobColor(int blobColor)
{
	if (blobColor == 0)
	{
		params.blobColor = 0;
	}
	else
	{
		params.blobColor = 255;
	}
}

void on_dummy_trackbar(int dummy, void* voidBlobDetector)
{
	CSimpleBlobDetectorWrapper* simpleBlobDetector = reinterpret_cast<CSimpleBlobDetectorWrapper*>(voidBlobDetector);
	simpleBlobDetector->SetDummy(dummy);
}

void on_blob_color_trackbar(int blobColor, void* voidBlobDetector)
{
	CSimpleBlobDetectorWrapper* simpleBlobDetector = reinterpret_cast<CSimpleBlobDetectorWrapper*>(voidBlobDetector);
	simpleBlobDetector->SetBlobColor(blobColor);
}

void on_min_threshold_trackbar(int minThreshold, void* voidBlobDetector)
{
	CSimpleBlobDetectorWrapper* simpleBlobDetector = reinterpret_cast<CSimpleBlobDetectorWrapper*>(voidBlobDetector);
	simpleBlobDetector->SetMinThreshold(static_cast<float>(minThreshold));
}

void on_max_threshold_trackbar(int maxThreshold, void* voidBlobDetector)
{
	CSimpleBlobDetectorWrapper* simpleBlobDetector = reinterpret_cast<CSimpleBlobDetectorWrapper*>(voidBlobDetector);
	simpleBlobDetector->SetMaxThreshold(static_cast<float>(maxThreshold));
}

void on_max_area_trackbar(int maxArea, void* voidBlobDetector)
{
	CSimpleBlobDetectorWrapper* simpleBlobDetector = reinterpret_cast<CSimpleBlobDetectorWrapper*>(voidBlobDetector);
	simpleBlobDetector->SetMaxArea(static_cast<float>(maxArea));
}

void on_min_area_trackbar(int minArea, void* voidBlobDetector)
{
	CSimpleBlobDetectorWrapper* simpleBlobDetector = reinterpret_cast<CSimpleBlobDetectorWrapper*>(voidBlobDetector);
	simpleBlobDetector->SetMinArea(static_cast<float>(minArea));
}
