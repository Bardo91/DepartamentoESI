//////////////////////////////////////////////////////////////////////////
//																		//
//		OpenGL Helper Libraries for CPU Processing  (GLHL)				//
//			Author: Pablo Ramón Soria									//
//			Date:	2014-01-19											//
//																		//
//////////////////////////////////////////////////////////////////////////
//	ActivityGL


#include "ActivityGL.h"


namespace GLHL{
	//---------------------------------------------------------------------------------
	ActivityGL::ActivityGL(){
		driverGPU = new DriverGPU();
		assert(driverGPU->initDriver());
			
	}

	//---------------------------------------------------------------------------------
	ActivityGL::~ActivityGL(){
		delete driverGPU;
	}

	//---------------------------------------------------------------------------------

}	// namespace GLHL