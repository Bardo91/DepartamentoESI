/////////////////////////////////////////////////////////////////////////////////////////
//		OpenBil
//			Author: Pablo Ramon Soria
//			Date:	2014-02-13
/////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _OPENBIL_ALGORITHMS_COLORCLUSTERING_H_
#define _OPENBIL_ALGORITHMS_COLORCLUSTERING_H_

#include <vector>

namespace BIL{
	namespace algorithms{
		//-----------------------------------------------------------------------------
		struct color3f{
			color3f(){a = 0.0f; b = 0.0f; c = 0.0f;};
			color3f(float _a, float _b, float _c){a = _a; b = _b; c = _c;};

			float a,b,c;
		};

		//-----------------------------------------------------------------------------
		struct Point{
			// Constructors.
			Point(){ x = 0; y = 0;};
			Point(short int _x, short int _y){ x = _x; y = _y;};

			// Properties.
			short int x, y;		// Coordinates of the point in the image.
		};

		//-----------------------------------------------------------------------------
		class ImageObject{		// Summarized object.
		public:
			ImageObject(Point _centroid, short int _width, short int _height);

			Point getCentroid() const;
			short int getWidth() const;
			short int getHeight() const;
		private:
			Point centroid;
			short int width, height;
		};

		//-----------------------------------------------------------------------------
		struct LineRLE{		// RLE encoding object.
			LineRLE(unsigned short int _i,
					unsigned short int _js,
					unsigned short int _je,
					short int _color){
						i = _i;
						js = _js;
						je = _je;
						size = je - js;
						color = _color;
						hasParent = false;
						pi = pj = 0;
						iObjs = -1;
			};

			unsigned short int i;		// Row of the object.
			unsigned short int js;		// Started column of the object.
			unsigned short int je;		// Ended column of the object.
			unsigned short int size;	// Size of the object (= je - js + 1) its computed one time in order to reduce the algorithm operations.

			short int color;	// Color of the object.s

			bool hasParent;				// Flag if the RLE was parented.
			unsigned short int pi;		// Index of the parent in the vector.
			unsigned short int pj;		// Index of the parent in the vector.

			short int iObjs;

		};

		class SegmentedObject {
			std::vector<LineRLE> obj;

			Point upperLeft, downRight; // Border pixels
			short int color;
			unsigned int size;

		public:
			SegmentedObject(LineRLE ini);

			void addLineObjRLE(LineRLE);
			void addRLEFamily(SegmentedObject&);

			int getLines() const;
			LineRLE getRLEObj(int) const;
			Point getUpperLeft() const;
			Point getDownRight() const;
			unsigned int getColor() const;
			unsigned int getSize() const;
			unsigned int getBBSize() const;
			Point getCentroid() const;

			void sortObj();
		};

		//-----------------------------------------------------------------------------
		// This algorithm takes an image and segmentate it with
		void ColorClustering(float * _image, int _width, int _height, int _threshold, std::vector<ImageObject> _objects, LAMBDAFUNCTIONSEGMENTATION);	

		//-----------------------------------------------------------------------------

	}	// namespace algorithms
}	// namespace BIL

#endif	// _OPENBIL_ALGORITHMS_COLORCLUSTERING_H_