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
#include <string>
#include <fstream>

namespace vision{
	namespace position{
		class Camera: public ObjectGeo{ // Class that store all information about recording cameras
		public:
			Camera();
			int loadPropertiesFromFile(std::string _filePath);
			
			int preparePositionFile();
			int startViconConnection(); // 666 TODO: Implement function

		public:
			double getFocalLenght() const;
			int fixDistorsion(cv::Mat&_frame) const;

		private: // Camera Parameters
			double focalLenght; // Media between camera's X focal length and Y focal lenght.
			double gammaSkew; // Skew coefficient between the x and y axis.
			double u0, v0;  // Principal point (Ideally in the center of the image, in term of 1).
			double* distorsionCoef; // Distorsión coefficients to make the properly correction of an image.
			int nDistCoef; // Size of distorsion coeffient vector
			double* projectionCoef; // Projection coefficients to make the properly correction of an image.
			int nProjCoef; // Size of projection coeffient vector
		private:
			std::ifstream positionFile;


		}; //class Camera

	} // namespace position
} // namespace vision


#endif //_VISUAL_TRACKING_UI_CAMERA_H_