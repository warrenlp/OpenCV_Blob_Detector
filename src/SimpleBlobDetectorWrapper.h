/*
 * SimpleBlobDetectorWrapper.h
 *
 *  Created on: Jan 21, 2014
 *      Author: warren
 */

#ifndef SIMPLEBLOBDETECTORWRAPPER_H_
#define SIMPLEBLOBDETECTORWRAPPER_H_

#include <opencv2/features2d/features2d.hpp>

#include <vector>
using namespace std;

class CSimpleBlobDetectorWrapper: public cv::SimpleBlobDetector {
public:
	CSimpleBlobDetectorWrapper(const SimpleBlobDetector::Params &parameters = SimpleBlobDetector::Params());
	virtual ~CSimpleBlobDetectorWrapper();

	// Make this virtual function public instead of protected
	virtual void detectImpl( const cv::Mat& image, vector<cv::KeyPoint>& keypoints, const cv::Mat& mask=cv::Mat() ) const;
	virtual int read( const string& filename );
};

#endif /* SIMPLEBLOBDETECTORWRAPPER_H_ */
