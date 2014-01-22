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
#include <string>
using namespace std;

class CSimpleBlobDetectorWrapper: public cv::SimpleBlobDetector {
public:

	CSimpleBlobDetectorWrapper(const SimpleBlobDetector::Params &parameters = SimpleBlobDetector::Params());
	virtual ~CSimpleBlobDetectorWrapper();

	// Make this virtual function public instead of protected
	virtual void detectImpl( const cv::Mat& image, vector<cv::KeyPoint>& keypoints, const cv::Mat& mask=cv::Mat() ) const;
	virtual int read( const string& filename );

	void SetDummy(int dummy) { /*Do nothing*/ }
	void SetBlobColor(int blobColor);
	void SetMinThreshold(float minThreshold);
	void SetMaxThreshold(float maxThreshold);
	void SetMaxArea(float maxArea);
	void SetMinArea(float minArea);

	void createTrackBars(const string& windowName, vector<string>& trackbarNames);

private:

	int m_area_max;

};

void on_dummy_trackbar(int, void*);
void on_blob_color_trackbar(int, void*);
void on_min_threshold_trackbar(int, void*);
void on_max_threshold_trackbar(int, void*);
void on_max_area_trackbar(int, void*);
void on_min_area_trackbar(int, void*);

#endif /* SIMPLEBLOBDETECTORWRAPPER_H_ */
