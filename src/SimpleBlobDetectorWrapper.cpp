/*
 * SimpleBlobDetectorWrapper.cpp
 *
 *  Created on: Jan 21, 2014
 *      Author: warren
 */

#include "SimpleBlobDetectorWrapper.h"

#include <opencv2/features2d/features2d.hpp>

#include <iostream>
using namespace std;

CSimpleBlobDetectorWrapper::CSimpleBlobDetectorWrapper(const SimpleBlobDetector::Params &parameters)
	: SimpleBlobDetector(parameters)
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
