////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// ThreadManager

#ifndef _VISUAL_TRACKING_UI_THREAD_MANAGER_H_
#define _VISUAL_TRACKING_UI_THREAD_MANAGER_H_

#include "InfoCollector.h"

#include <thread>

namespace vision{

	class ThreadManager{
	public:
		ThreadManager();
		~ThreadManager();

	private:	
		std::thread *pThread;

		InfoPointers *infoPointers;

	public:
		void setInfo(InfoPointers * _infoPointers);

	public:
		bool isRunning();
		int startThread();
		void stopThread();
	};

} // namespace vision

#endif //_VISUAL_TRACKING_UI_THREAD_MANAGER_H_