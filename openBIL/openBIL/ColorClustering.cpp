/////////////////////////////////////////////////////////////////////////////////////////
//		OpenBil
//			Author: Pablo Ramon Soria
//			Date:	2014-02-13
/////////////////////////////////////////////////////////////////////////////////////////
//

#include "ColorClustering.h"		// Header of the algorithm

using namespace std;

namespace BIL{
	namespace algorithms{
		void ColorClustering(float * _image, int _width, int _height, int _threshold, std::vector<ImageObject> &_objects, LAMBDAFUNCTIONSEGMENTATION){
			vector<vector<LineRLE>> aRLE;		// Matrix with every RLE encoded objects
			vector<SegmentedObject> objects;	// Auxiliary object that store Segmented objects while they are been growing.

			short int color, colorRLE = -1;
			short int js = 0;
			for(short int i = 0; i < _height ; i ++){	// Main vertical loop on the image

				// First horizontal loop. It will segmentate every pixel and encode it in a RLE if it's a desired color.
				vector<LineRLE> temp;
				for(int j = 0; j < _width ; j ++){		
					// 666 TODO:	Si hacemos una funcion que directamente modifique la imagen nos ahorramos 
					//				tener que comprobar luego el color que la funcion que determina el color elige para 
					//				luego modificar la imagen de nuevo para poner los colores simplificados (menos ifs... menos indirecciones.... etc....).
					

					// This function segmentate the pixel and return the color of those.
					color = FUNCION_DE_SEGMENTACION(_image[i + 3*j + 0],
													_image[i + 3*j + 1],
													_image[i + 3*j + 2]);

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
					aRLE.push_back(temp);
				}
				// End of first horizontal loop for RLE encoding and segmentation.

				// Now start the harder step, that takes the lineRLE objects of the current and previous row and connect them in order to collect every piece of the complete object



			}

		}	// ColorClustering(...);

	}	// namespace algorithms.
}	// namespace BIL