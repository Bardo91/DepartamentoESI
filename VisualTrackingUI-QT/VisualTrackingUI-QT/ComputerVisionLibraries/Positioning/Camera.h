////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/11/23
////////////////////////////////////////////////////////////////////////////////
// 


#ifndef _VISUAL_TRACKING_UI_CAMERA_H_
#define _VISUAL_TRACKING_UI_CAMERA_H_

#include "ObjectGeo.h"

#include <opencv/cv.h>

namespace vision{
	namespace position{
		class Camera: ObjectGeo{ // Class that store all information about recording cameras
		public:
			double getFocalLenght();
			int fixDistorsion(cv::Mat&_frame);

		private:
			const double focalLenght; // Media between camera's X focal length and Y focal lenght.
			const double gammaSkew; // Skew coefficient between the x and y axis.
			const double u0, v0;  // Principal point (Ideally in the center of the image, in term of 1).
			const double* distorsionCoef; // Distorsión coefficients to make the properly correction of an image.
			const int nDistCoef; // Size of distorsion coeffient vector
			const double* projectionCoef; // Projection coefficients to make the properly correction of an image.
			const int nProjCoef; // Size of projection coeffient vector
		}; //class Camera

	} // namespace position
} // namespace vision


#endif //_VISUAL_TRACKING_UI_CAMERA_H_