////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/12/31
////////////////////////////////////////////////////////////////////////////////
// Vicon Manager


#ifndef _VISUAL_TRACKING_UI_VICON_H_
#define _VISUAL_TRACKING_UI_VICON_H_

#include <Client.h>  //Header file of vicon
#include <opencv/cv.h>

namespace iofunctions{
	class Vicon{
	public:
		bool connect();
		bool disconnect();

	public:
		double getTime();
		bool getPosition(int obj, cv::Mat& pos);
		bool getOrientation(int obj, cv::Mat& ori);
	private:
		ViconDataStreamSDK::CPP::Client mSocketClient;

		double mRefTime;


	}; // class Vicon

} // namespace iofunctions.




#endif //_VISUAL_TRACKING_UI_VICON_H_
