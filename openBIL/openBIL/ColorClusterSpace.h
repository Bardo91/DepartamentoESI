/*
 * ColorClusterSpace.h
 *
 *  Created on: Oct 22, 2013
 *      Author: Pablo Ramón Soria
 *
 *      In this header are defined the classes and functions used on ImageClusterSegmentation
 *		algorithm.
 *
 */

#include <math.h>
#include <stdint.h>
#include <string>

#ifndef _OPENBIL_COLORCLUSTERSPACE_H_
#define _OPENBIL_COLORCLUSTERSPACE_H_

#define LOG2 0.3010299957

namespace vision {
	namespace segmentation {
		typedef unsigned int uint;

		template<typename T> struct color3_ {
			color3 (){
				a = b = c = T(0);
			};
			color3int(T _a, T _b, T _c){
				a = _a; b = _b; c = _c;
			};

			T a, b, c;
		};

		typedef color3_<unsigned char> c3u;

		class ColorClusterSpace {
		public:
			int size;
			c3i *clusters;  // <<--------------- 666 TODO: change types
			ColorClusterSpace(int, uint8_t *, uint8_t *, uint8_t *, const c3i *);
			~ColorClusterSpace();

		private:
			uint8_t *AClass;
			uint8_t *BClass;
			uint8_t *CClass;

		public:
			int operator()(uint8_t *_a, uint8_t *_b, uint8_t *_c){
				c3i col(*_a, *_b, *_c);

				int color =  whichColor(col);	
				if(color != -1){
					*_a = clusters[color].a;
					*_b = clusters[color].b;
					*_c = clusters[color].c;
				} else{
					*_a = 0U;
					*_b = 0U;
					*_c = 0U;
				}

				return color;
			};

			int whichColor(c3i&); // Return between 0 and 255

		};


		inline int ColorClusterSpace::whichColor(c3i& color) { // If Opencv gives YCrCb values between 0 and 255
			int i = (color.a * (size - 1) / 180); // 666 TODO: improve (get 5%)
			int j = color.b*(size - 1) >> 7;
			j = (j>>1) + (j&1);
			int k = color.c*(size - 1) >> 7;
			k = (k>>1) + (k&1);
			

			int res = AClass[i] & BClass[j] & CClass[k]; //Supposing that colors are not over-layed there's only one possible solution and log2(x) returns an integer /

			int aux = 0;

			if (!res)
				return -1;

			while (!(res & 0x01)) {
				res = res >> 1;
				aux += 1;
			}

			return aux;
		}



	} // namespace segmentation.
} // namespace vision.
#endif // _OPENBIL_COLORCLUSTERSPACE_H_
