////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/11/23
////////////////////////////////////////////////////////////////////////////////
// 

#include "Camera.h"

#include <opencv/cv.h>
#include <cassert>

using namespace cv;
using namespace std;

namespace vision{
	namespace position{
		//--------------------------------------------------------------------
		Camera::Camera(){
			nDistCoef = nProjCoef = 0;
		}
		//--------------------------------------------------------------------
		Camera::Camera(double _f, double _g, double _u0, double _v0){
			focalLenght = _f;
			gammaSkew = _g;
			u0 = _u0;
			v0 = _v0;
		}

		//--------------------------------------------------------------------
		int Camera::loadPropertiesFromFile(string _filePath){
			// infoFile order: focalLegth, gammaSkew, u0, v0, distorsionCoef & projectCoef
			ifstream infoFile(_filePath.c_str(), ifstream::in);
			if(!infoFile.is_open())
				return -1;
			int i = 0;

			string line = "init";
			while(line.size() != 0){
				if(infoFile.eof())
					break;
				getline(infoFile, line);
				switch (i)
				{
				case 0:
					focalLenght = atof(line.c_str());
					break;
				case 1:
					gammaSkew = atof(line.c_str());
					break;
				case 2:
					u0 = atof(line.c_str());
					break;
				case 3:
					v0 = atof(line.c_str());
					break;
				case 4:
					// 666 TODO: distorsionCoef
					break;
				case 5:
					// 666 TODO: projectionCoef
					break;
				default:
					break;
				}
				i++;
			}

			infoFile.close();

			if(i < 1) // Make sure that at least focal lenght is loaded
				return -1;

			return 0;
		}

		//--------------------------------------------------------------------
		double Camera::getFocalLenght() const{
			return focalLenght;
		}

		//--------------------------------------------------------------------
		Point2d Camera::getCentroid() const{
			return Point(int(u0),int(v0));
		}

		//--------------------------------------------------------------------
		int Camera::fixDistorsion(Mat& _frame) const{
			if(distorsionCoef == 0 || projectionCoef == 0)
				return -1;
			assert(_frame.rows != 0);
			// 666 TODO: implement function.

			return 0;
		}

	} // namespace position
} // namespace vision
