////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// ThreadManager

#include "ThreadManager.h"
#include "ThreadAlgorithm.h"

#include <thread>
#include <mutex>

using namespace vision;
using namespace std;

namespace vision{

	ThreadManager::ThreadManager(){
	pThread = 0;
}

//------------------------------------------------------------------------------
ThreadManager::~ThreadManager(){

}

//----------------------------------------------------------------------------
void ThreadManager::setInfo(InfoPointers * _infoPointers){
	infoPointers = _infoPointers;
}

//----------------------------------------------------------------------------
bool ThreadManager::isRunning(){
	return infoPointers->looping;

}

//----------------------------------------------------------------------------
void ThreadManager::stopThread(){
	std::mutex mutex;

	mutex.lock();
	if(isRunning() && pThread != nullptr){ //If Thread is currently been running first need to be stoped
		infoPointers->looping = false;
		pThread->join();
		pThread = 0;
	}
	mutex.unlock();

	//delete infoPointers->algorithmManager;

}

//----------------------------------------------------------------------------
int ThreadManager::startThread(){
	if(pThread != 0) //If Thread is currently been running first need to be stoped
		stopThread(); // Thread can not be stopped

	pThread = new thread(threadAlgoritm, infoPointers);

	if(pThread == 0)
		return -1;

	std::mutex mutex;
	mutex.lock();
	infoPointers->looping = true; // Set the flag to control that the thread is going to be running.
	mutex.unlock();

	return 0; // Thread started properly.

}
} // namespace vision