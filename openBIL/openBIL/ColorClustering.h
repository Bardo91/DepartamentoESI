/////////////////////////////////////////////////////////////////////////////////////////
//		OpenBIL
//			Author: Pablo Ramon Soria
//			Date:	2014-02-13
/////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _OPENBIL_ALGORITHMS_COLORCLUSTERING_H_
#define _OPENBIL_ALGORITHMS_COLORCLUSTERING_H_

#include <vector>
#include <functional>

#include "ColorSpaceHSV8.h"

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
			Point(int _x, int _y){ x = _x; y = _y;};

			// Properties.
			unsigned int x, y;		// Coordinates of the point in the image.
		};

		//-----------------------------------------------------------------------------
		class ImageObject{		// Summarized object.
		public:
			ImageObject(Point _upperLeft, Point _downRight, int _size, int _color){
				centroid = Point((_upperLeft.x + _downRight.x)/2, (_upperLeft.y + _downRight.y)/2);
				width = _upperLeft.x - _upperLeft.x;
				height = _upperLeft.y - _upperLeft.y;
				size = _size;
				color = _color;
			};
			
			Point getCentroid() const {return centroid;};
			int getWidth() const {return width;};
			int getHeight() const {return height;};
			int getColor() const {return color;};
		private:
			Point centroid;
			int width, height;
			int color;
			int size;
		};

		//-----------------------------------------------------------------------------
		struct LineRLE{		// RLE encoding object.
			LineRLE(unsigned int _i,
					unsigned int _js,
					unsigned int _je,
					int _color){
						i = _i;
						js = _js;
						je = _je;
						size = je - js;
						color = _color;
						hasParent = false;
						pi = pj = 0;
						iObj = -1;
			};

			unsigned int i;			// Row of the object.
			unsigned int js;		// Started column of the object.
			unsigned int je;		// Ended column of the object.
			unsigned int size;		// Size of the object (= je - js + 1) its computed one time in order to reduce the algorithm operations.

			int color;	// Color of the object.s

			bool hasParent;				// Flag if the RLE was parented.
			unsigned int pi;			// Index of the parent in the vector.
			unsigned int pj;			// Index of the parent in the vector.

			int iObj;

		};

		class SegmentedObject {
			std::vector<LineRLE> obj;

			Point upperLeft, downRight; // Border pixels
			int color;
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
		// The template is the type of image pointer, and function is the segmentate pixel format
		template<typename T> void ColorClustering(	T *_image, 
													int _width,
													int _height, 
													unsigned int _sizeThreshold, 
													std::vector<ImageObject> _objects,
													std::function<int (T *_a, T *_b, T *_c)> _function){

			std::vector<std::vector<LineRLE>> aRLE;		// Matrix with every RLE encoded objects
			std::vector<SegmentedObject> objects;	// Auxiliary object that store Segmented objects while they are been growing.

			int color, colorRLE = -1;
			int js = 0;
			for(int i = 0; i < _height ; i ++){	// Main vertical loop on the image

				// First horizontal loop. It will segmentate every pixel and encode it in a RLE if it's a desired color.
				std::vector<LineRLE> temp;
				for(int j = 0; j < _width ; j ++){		
					// This function segmentate the pixel and return the color of those.
					color = _function(	_image + i * _width * 3 + 3*j + 0,
										_image + i * _width * 3 + 3*j + 1,
										_image + i * _width * 3 + 3*j + 2);

					if(color != -1){
						if(j == 0){			// If it's the first pixel of the row, set the current RLE color to the current pixel's color and initialize the js counter of columns.
							colorRLE = color;
							js = 0;
						} else {			// If not
							if (color != colorRLE){	// If the color of the current pixel is not the same that the current lineRLE's color then create the previous lineRLE and start a new.
								LineRLE lineRLE(i, js, j, colorRLE);
								temp.push_back(lineRLE);
								colorRLE = color;
								js = j;

							} else if (j == _height - 1){	// If it's the last pixel of the row finallize the last RLE line of this row.
								LineRLE lineRLE(i, js, j, colorRLE);
								temp.push_back(lineRLE);

							} 
						}
					}
				}
				aRLE.push_back(temp);
				// End of first horizontal loop for RLE encoding and segmentation.

				// Now start the harder step, that takes the lineRLE objects of the current and previous row and connect them in order to collect every piece of the complete object
				if(i){	//First line cannot have parents
					unsigned int pcRLE = 0, ppRLE = 0; 		// Index of the current lineRLE on the i row of aRLE
					unsigned int jc = aRLE[i][pcRLE].size, jp = aRLE[i-1][ppRLE].size;	// Index of current row's column and previous row's column.
					
					bool condition = true;
					while(condition){	// Connecting RLEs
						if(	aRLE[i-1][ppRLE].color == aRLE[i][pcRLE].color &&	// If lineRLEs have same color and have some column in common...
							aRLE[i-1][ppRLE].je >= aRLE[i][pcRLE].js &&
							aRLE[i-1][ppRLE].js <= aRLE[i][pcRLE].je){
								if(!aRLE[i][pcRLE].hasParent){			// If current lineRLE has no parent
									if(aRLE[i-1][ppRLE].hasParent){		// Use previous parent
										aRLE[i][pcRLE].pi = aRLE[i-1][ppRLE].pi;
										aRLE[i][pcRLE].pj = aRLE[i-1][ppRLE].pj;
										aRLE[i][pcRLE].hasParent = true;

									} else {			// Previous lineRLE is the parent
										aRLE[i][pcRLE].pi = i-1;
										aRLE[i][pcRLE].pj = ppRLE;
										aRLE[i][pcRLE].hasParent = true;

									}
								}else{	// If current lineRLE has parent --> OVERLAP
									if(aRLE[i-1][ppRLE].hasParent){		// There is a "family" of RLE lines
										if((aRLE[i-1][ppRLE].pi != aRLE[i][pcRLE].pi) && (aRLE[i-1][ppRLE].pj != aRLE[i][pcRLE].pj)){
											aRLE[aRLE[i-1][ppRLE].pi][aRLE[i-1][ppRLE].pj].pi = aRLE[i][pcRLE].pi;
											aRLE[aRLE[i-1][ppRLE].pi][aRLE[i-1][ppRLE].pj].pj = aRLE[i][pcRLE].pj;
											aRLE[aRLE[i-1][ppRLE].pi][aRLE[i-1][ppRLE].pj].hasParent = true;
										}


									} else {			// There is an orphan RLE line
										aRLE[i-1][ppRLE].pi = aRLE[i][pcRLE].pi;
										aRLE[i-1][ppRLE].pj = aRLE[i][pcRLE].pj;
										aRLE[i-1][ppRLE].hasParent = true;

									}
								}
						}	// Connecting RLEs
						if(pcRLE >= aRLE[i].size() - 1 ||ppRLE >= aRLE[i-1].size() -1)
							condition = false;
						if(jp >= jc){
							pcRLE++;
							jc += aRLE[i][pcRLE].size;
						} else if( jp <= jc){
							ppRLE++;
							jp += aRLE[i-1][ppRLE].size;
						}
					}	// while(1).

				}	// If not first row.
			}	// Vertical loop for each row
			
			// Re-assing overlaped parents
			for(unsigned int i = 0 ; i < aRLE.size() ; i++){
				for(unsigned int j = 0 ; j < aRLE[i].size() ; j++){
					if(aRLE[i][j].hasParent){
						LineRLE auxRLE = aRLE[aRLE[i][j].pi][aRLE[i][j].pj];

						int loopCounter = 0;
						while(auxRLE.hasParent && loopCounter < 30){
							aRLE[i][j].pi = auxRLE.pi;
							aRLE[i][j].pj = auxRLE.pj;

							auxRLE = aRLE[auxRLE.pi][auxRLE.pj];

							loopCounter++;
						}
						if (aRLE[aRLE[i][j].pi][aRLE[i][j].pj].iObj == -1) {
							aRLE[aRLE[i][j].pi][aRLE[i][j].pj].iObj = objects.size();
							SegmentedObject obj(aRLE[aRLE[i][j].pi][aRLE[i][j].pj]);
							objects.push_back(obj);
						}
					}
				}	// for i
			}	// for j

			for(unsigned int i = 0 ; i < aRLE.size() ; i++){
				for(unsigned int j = 0 ; j < aRLE[i].size() ; j++){
					if(aRLE[i][j].hasParent){
						objects[aRLE[aRLE[i][j].pi][aRLE[i][j].pj].iObj].addLineObjRLE(aRLE[i][j]);
					}
				}	// for i
			}	// for j
			
			for(unsigned int i = 0; i < objects.size() ; i ++){
				if(objects[i].getSize() >= _sizeThreshold)
					_objects.push_back(ImageObject(objects[i].getUpperLeft(), objects[i].getDownRight(), objects[i].getSize(), objects[i].getColor()));
			}
		}
		
		//-----------------------------------------------------------------------------

	}	// namespace algorithms
}	// namespace BIL

#endif	// _OPENBIL_ALGORITHMS_COLORCLUSTERING_H_