/*
 * FastMatching.cpp
 *
 *  Created on: Oct 7, 2013
 *      Author: Pablo Ramon Soria
 *
 *      Here is be defined a function that provide a quick and secure matching between objects projected in both cameras.
 *      Is based not only on taken images but also on the current position so as the filtering is better than only matching
 *      isolated and informationless objects at projection images.
 *
 */

#include <FastStereoMatching.h>

using namespace sysctrl;
using namespace sysctrl::visionctrl;
using namespace std;
using namespace cv;

namespace ccss {

// Functions

void objectMatching(const vector<SegmentedObject>& objsL,
		const vector<SegmentedObject>& objsR, LR * matching, const camera& cam1,
		const camera& cam2, const StereoVisionEKF EKFs[8],
		const unsigned int& threshold) {

	for (unsigned int i = 0; i < objsL.size(); i++) {
		int ci = 0, cj = 0;
		bool flagFound = false;
		double energy = 999999999;
		if (objsL.at(i).getSize() > threshold) {
			for (unsigned int j = 0; j < objsR.size(); j++) {
				if (objsR.at(j).getSize() > threshold) {
					if (objsL.at(i).getColor() == objsR.at(j).getColor()) {
						/* Here is calculate the supposed actual position of the object using
						 * triangulation function and the last "z" coordinate in order to
						 * simplify the calculus.
						 *
						 *            P = Ci + Ri * Pci
						 *
						 */

						flagFound = true;

						Mat currentState;
						EKFs[objsL.at(i).getColor()].getStateVector(
								currentState);

						double Z = currentState.ptr<double>(1)[0];

						double XimC1 = objsL.at(i).getCentroid().x;
						double YimC1 = objsL.at(i).getCentroid().y;

						double XimC2 = objsR.at(j).getCentroid().x;
						double YimC2 = objsR.at(j).getCentroid().y;

						Mat Pc1 = (Mat_<double>(3, 1)
								<< XimC1 * Z / cam1.alphaX, YimC1 * Z
								/ cam2.alphaX, Z);
						Mat Pc2 = (Mat_<double>(3, 1)
								<< XimC2 * Z / cam1.alphaX, YimC2 * Z
								/ cam2.alphaX, Z);

						Mat C1 =
								(Mat_<double>(3, 1) << cam1.pos[0], cam1.pos[1], cam1.pos[2]);
						Mat C2 =
								(Mat_<double>(3, 1) << cam2.pos[0], cam2.pos[1], cam2.pos[2]);

						Mat P1 = C1 + cam1.ori.inv() * Pc1;
						Mat P2 = C2 + cam2.ori.inv() * Pc2;

						double aux = abs(norm(P1 - P2));
						if (aux < energy) {
							ci = i;
							cj = j;
							energy = aux;

							/*cout << "Intento numero j: " << j
							 << "Para el color: "
							 << objsL.at(i).getColor() << endl;
							 cout << P1 << endl << P2 << endl;
							 waitKey();*/
						}
					}
				}
			}
			if (flagFound) {
				LR auxLR = { ci, cj, { objsL.at(ci).getCentroid().x, objsL.at(
						ci).getCentroid().y }, { objsR.at(cj).getCentroid().x,
						objsR.at(cj).getCentroid().y }, energy,
						objsL.at(ci).getColor(), TRUE };

				/*cout << energy << endl;
				 waitKey();*/

				matching[objsL.at(ci).getColor()] = auxLR;
			}
		}
	}
}
}

