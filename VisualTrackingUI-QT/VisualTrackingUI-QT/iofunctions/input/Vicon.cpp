////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/12/31
////////////////////////////////////////////////////////////////////////////////
// Vicon Manager


#include "Vicon.h"

using namespace cv;

namespace iofunctions{
	//---------------------------------------------------------------------------
	bool Vicon::connect(){
		int k = 0; 
		while(mSocketClient.IsConnected().Connected == false || k < 1000){
			// Try to connect to the vicon stream data source.
			mSocketClient.Connect("10.0.0.2:801"); 
			k++;
		}

		if(mSocketClient.IsConnected().Connected){
			// Enable data transmit
			mSocketClient.EnableSegmentData();
			// Set ref time.
			ViconDataStreamSDK::CPP::Output_GetTimecode time = mSocketClient.GetTimecode();
			mRefTime = 0; // 666 TODO: minimum resolution??? 
			return true;
		}

		return false;
	}

	//---------------------------------------------------------------------------
	bool Vicon::disconnect(){
		if(mSocketClient.IsConnected().Connected)
			mSocketClient.Disconnect();	

		return mSocketClient.IsConnected().Connected;
	}
	//---------------------------------------------------------------------------
	double Vicon::getTime(){
		ViconDataStreamSDK::CPP::Output_GetTimecode time = mSocketClient.GetTimecode();
		mRefTime = 0;
		return 0 - mRefTime; // 666 TODO: minimum resolution??? 
	}

	//---------------------------------------------------------------------------
	bool Vicon::getPosition(int obj, Mat& pos){
		// Cast the name of the object.
		char buffer[3];
		if(obj < 10)
			sprintf(buffer, "O0%d", obj);
		else
			sprintf(buffer, "O%d", obj); 

		// Get object from stream
		ViconDataStreamSDK::CPP::Output_GetSegmentGlobalTranslation traslationObject 
			= mSocketClient.GetSegmentGlobalTranslation(buffer, buffer);
		// Get position.
		double* globalPos = traslationObject.Translation;

		// Put into internal matrix variable.
		pos = (Mat_<double>() << globalPos[0], globalPos[1], globalPos[2]);
		
		return traslationObject.Occluded;
	}

	//---------------------------------------------------------------------------
	bool Vicon::getOrientation(int obj, Mat& ori){
		// Cast the name of the object.
		char buffer[3];
		if(obj < 10)
			sprintf(buffer, "O0%d", obj);
		else
			sprintf(buffer, "O%d", obj); 

		// Get object from stream
		ViconDataStreamSDK::CPP::Output_GetSegmentGlobalRotationEulerXYZ rotationObject 
			= mSocketClient.GetSegmentGlobalRotationEulerXYZ(buffer, buffer);
		// Get rotation.
		double* globalOri = rotationObject.Rotation;

		// Put into internal matrix variable.
		ori = (Mat_<double>() << globalOri[0], globalOri[1], globalOri[2]);

		return rotationObject.Occluded;
	}

	//---------------------------------------------------------------------------

} // namespace iofunctions.