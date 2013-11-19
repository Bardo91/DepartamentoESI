////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// Endless thread that run the specified algorithm

#ifndef _VISUAL_TRACKING_UI_THREAD_ALGORITHM_H_
#define _VISUAL_TRACKING_UI_THREAD_ALGORITHM_H_

#include <ComputerVisionLibraries/DataAcquisition/ImageManager.h>

#include "InfoCollector.h"

namespace vision{

void threadAlgoritm(InfoPointers * infoPointers);
} // namespace vision


#endif // _VISUAL_TRACKING_UI_THREAD_ALGORITHM_H_