#ifndef DIGITIZER_WRAPPER_H
#define DIGITIZER_WRAPPER_H

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

#include <dinput.h>
#include <windows/common.h>

#include "Digitizer State.h"
#include "Digitizer Properties.h"


class DIDigitizer : public DigitizerState , public DigitizerProperties
{
public:

			/***************************
			* contructors & destructor *
			***************************/

	inline DIDigitizer(IDirectInput8 *directInputObject , WindowHandle mainWindow , DWORD modeFlags = DISCL_EXCLUSIVE | DISCL_BACKGROUND)	// DIDigitizer contructor
	{
		static GUID digitizerInstanceGUID = {0x0F75C0A0,0xD9B8,0x11E0,{0x80,0x09,0x44,0x45,0x53,0x54,0x00,0x00}};
		//0F734FA0-D9B8-11E0-8007-444553540000
		//0F75C0A0-D9B8-11E0-8009-444553540000
		//0F6E94B0-D9B8-11E0-8005-444553540000
		// create the digitizer device
		switch(directInputObject->CreateDevice(digitizerInstanceGUID,&iObject,NULL))
		{
		case DIERR_DEVICENOTREG:
			MessageBox(0,_T("The device or device instance is not registered with DirectInput."),_T("Device not registered:"),MB_OK | MB_ICONERROR);
			break;
		case DIERR_INVALIDPARAM:
			MessageBox(0,_T("An invalid parameter was passed to the returning function, or the object was not in a state that permitted the function to be called."),_T("Invalid parameter:"),MB_OK | MB_ICONERROR);
			break;
		case DIERR_NOINTERFACE:
			MessageBox(0,_T("The object does not support the specified interface."),_T("No interface:"),MB_OK | MB_ICONERROR);
			break;
		case DIERR_NOTINITIALIZED:
			MessageBox(0,_T("This object has not been initialized."),_T("Not initialized:"),MB_OK | MB_ICONERROR);
			break;
		case DIERR_OUTOFMEMORY:
			MessageBox(0,_T("The DirectInput subsystem could not allocate sufficient memory to complete the call."),_T("Out of Memory:"),MB_OK | MB_ICONERROR);
			break;
		default:
			MessageBox(0,_T("An unknown error has occured."),_T("Error:"),MB_OK | MB_ICONERROR);
			break;
		case DI_OK:	// everything in order
			break;
		} // end switch

		static DIOBJECTDATAFORMAT digitizerControlsDataFormats[] =
		{
			{&GUID_XAxis,0,DIDFT_ABSAXIS|DIDFT_MAKEINSTANCE(0),0},
			{&GUID_YAxis,4,DIDFT_ABSAXIS|DIDFT_MAKEINSTANCE(1),0},
			{&GUID_Unknown,8,DIDFT_ABSAXIS|DIDFT_MAKEINSTANCE(6),0},
			{&GUID_Unknown,12,DIDFT_ABSAXIS|DIDFT_MAKEINSTANCE(7),0},
			{&GUID_Unknown,16,DIDFT_ABSAXIS|DIDFT_MAKEINSTANCE(8),0},
			{&GUID_Unknown,20,DIDFT_ABSAXIS|DIDFT_MAKEINSTANCE(9),0},
			{&GUID_Unknown,24,DIDFT_ABSAXIS|DIDFT_MAKEINSTANCE(10),0},
			{&GUID_Unknown,28,DIDFT_ABSAXIS|DIDFT_MAKEINSTANCE(11),0},
			{&GUID_Button,32,DIDFT_PSHBUTTON|DIDFT_MAKEINSTANCE(0),0},
			{&GUID_Button,33,DIDFT_PSHBUTTON|DIDFT_MAKEINSTANCE(1),0},
			{&GUID_Button,34,DIDFT_PSHBUTTON|DIDFT_MAKEINSTANCE(2),0},
			{&GUID_Button,35,DIDFT_PSHBUTTON|DIDFT_MAKEINSTANCE(3),0},
			{&GUID_Button,36,DIDFT_PSHBUTTON|DIDFT_MAKEINSTANCE(4),0}
		};
		static DIDATAFORMAT digitizerDataFormat = {sizeof(DIDATAFORMAT) , sizeof(DIOBJECTDATAFORMAT) , DIDF_ABSAXIS , (sizeof(DigitizerState)+3)&0xfffffffc , sizeof(digitizerControlsDataFormats)/sizeof(digitizerControlsDataFormats[0]) , digitizerControlsDataFormats};

		// set the data format for the digitizer device
		switch(iObject->SetDataFormat(&digitizerDataFormat))
		{
		case E_HANDLE:
			MessageBox(0,_T("The window handle parameter is not a valid top-level window that belongs to the process."),_T("Invalid window handle:"),MB_OK | MB_ICONERROR);
			break;
		case DIERR_INVALIDPARAM:
			MessageBox(0,_T("An invalid parameter was passed to the returning function, or the object was not in a state that permitted the function to be called."),_T("Invalid parameter:"),MB_OK | MB_ICONERROR);
			break;
		case DIERR_NOTINITIALIZED:
			MessageBox(0,_T("This object has not been initialized."),_T("Not initialized:"),MB_OK | MB_ICONERROR);
			break;
		default:
			MessageBox(0,_T("An unknown error has occured."),_T("Error:"),MB_OK | MB_ICONERROR);
			break;
		case DI_OK:	// everything in order
			break;
		} // end switch

		// set the cooperative level for the digitizer device
		switch(iObject->SetCooperativeLevel(mainWindow,modeFlags))
		{
		case DIERR_ACQUIRED:
			MessageBox(0,_T("The operation cannot be performed while the device is acquired"),_T("Device acquired:"),MB_OK | MB_ICONERROR);
			break;
		case DIERR_INVALIDPARAM:
			MessageBox(0,_T("An invalid parameter was passed to the returning function, or the object was not in a state that permitted the function to be called."),_T("Invalid parameter:"),MB_OK | MB_ICONERROR);
			break;
		case DIERR_NOTINITIALIZED:
			MessageBox(0,_T("This object has not been initialized."),_T("Not initialized:"),MB_OK | MB_ICONERROR);
			break;
		default:
			MessageBox(0,_T("An unknown error has occured."),_T("Error:"),MB_OK | MB_ICONERROR);
			break;
		case DI_OK:	// everything in order
			break;
		} // end switch
	} // end DIDigitizer contructor


	inline ~DIDigitizer()																						// DIDigitizer destructor
	{
		iObject->Unacquire();
		iObject->Release();
	} // end DIDigitizer destructor



			/************
			* operators *
			************/

	inline IDirectInputDevice8 *operator->()																// operator->
	{
		return iObject;
	} // end function operator->



		/*******************
		* member functions *
		*******************/

	void acquire()																							// acquire
	{
		switch(iObject->Acquire())
		{
		case DIERR_INVALIDPARAM:
			MessageBox(0,_T("An invalid parameter was passed to the returning function, or the object was not in a state that permitted the function to be called. This may be due to the device data format not been set yet."),_T("Invalid parameter:"),MB_OK | MB_ICONERROR);
			break;
		case DIERR_NOTINITIALIZED:
			MessageBox(0,_T("This object has not been initialized."),_T("Not initialized:"),MB_OK | MB_ICONERROR);
			break;
		case DIERR_OTHERAPPHASPRIO:
			MessageBox(0,_T("Another application has a higher priority level, preventing this call from succeeding. This error can occur when an application has only foreground access to a device but is attempting to acquire the device while in the background."),_T("Another application has higher priority:"),MB_OK | MB_ICONERROR);
			break;
		case S_FALSE:
			MessageBox(0,_T("The device was already acquired."),_T("Already acquired:"),MB_OK | MB_ICONINFORMATION);
			break;
		case DI_OK:
			break;
		} // end switch
	} // end function acquire

	void getState()																							// getState
	{
		ResultHandle result;
		do
		{
			ZeroMemory(&Xaxis,sizeof(DigitizerState));
			switch(result = iObject->GetDeviceState(sizeof(DigitizerState),&Xaxis))
			{
			case DIERR_INVALIDPARAM:
				MessageBox(0,_T("An invalid parameter was passed to the returning function, or the object was not in a state that permitted the function to be called. This may be due to the device data format not been set yet."),_T("Invalid parameter:"),MB_OK | MB_ICONERROR);
				break;
			case DIERR_NOTINITIALIZED:
				MessageBox(0,_T("This object has not been initialized."),_T("Not initialized:"),MB_OK | MB_ICONERROR);
				break;
			case DIERR_NOTACQUIRED:
				MessageBox(0,_T("The operation cannot be performed unless the device is acquired."),_T("Not acquired:"),MB_OK | MB_ICONERROR);
				this->acquire();
				break;
			case E_PENDING:
				MessageBox(0,_T("Data is not yet available."),_T("Pending:"),MB_OK | MB_ICONERROR);
				break;
			case DIERR_INPUTLOST:
#ifdef DEBUG
				MessageBox(0,_T("Access to the input device has been lost. It must be reacquired."),_T("Input Lost:"),MB_OK | MB_ICONINFORMATION);
#endif
				this->acquire();
				break;
			default:
				MessageBox(0,_T("An unknown error has occured."),_T("Error:"),MB_OK | MB_ICONERROR);
				break;
			case DI_OK:	// everything in order
				break;
			} // end switch
		}
		while(result != DI_OK);
	} // end function getState

	void getProperty(const GUID &propertyID , DIPROPHEADER *result)											// getProperty
	{
		switch(iObject->GetProperty(propertyID,result))
		{
		case DIERR_INVALIDPARAM:
			MessageBox(0,_T("An invalid parameter was passed to the returning function, or the object was not in a state that permitted the function to be called. This may be due to the device data format not been set yet."),_T("Invalid parameter:"),MB_OK | MB_ICONERROR);
			break;
		case DIERR_NOTINITIALIZED:
			MessageBox(0,_T("This object has not been initialized."),_T("Not initialized:"),MB_OK | MB_ICONERROR);
			break;
		case DIERR_NOTEXCLUSIVEACQUIRED:
			MessageBox(0,_T("The operation cannot be performed unless the device is acquired in DISCL_EXCLUSIVE mode."),_T("Not acquired in exclusive mode:"),MB_OK | MB_ICONERROR);
			break;
		case DIERR_OBJECTNOTFOUND:
			MessageBox(0,_T("The requested object does not exist."),_T("Object not found:"),MB_OK | MB_ICONERROR);
			break;
		case DIERR_UNSUPPORTED:
			MessageBox(0,_T("The function called is not supported at this time."),_T("Unsupported:"),MB_OK | MB_ICONERROR);
			break;
		case S_FALSE:
		case DI_OK:
			break;
		} // end switch
	} // end function getProperty

	void getProperties()										// getProperties
	{
		DIPROPDWORD wordProperty = {sizeof(DIPROPDWORD),sizeof(DIPROPHEADER),0,DIPH_DEVICE};
		DIPROPRANGE rangeProperty = {sizeof(DIPROPRANGE),sizeof(DIPROPHEADER),0,DIPH_BYOFFSET};
		DIPROPSTRING stringProperty = {sizeof(DIPROPSTRING),sizeof(DIPROPHEADER),0,0};

		// get axis mode
		wordProperty.diph.dwObj = 0;
		getProperty(DIPROP_AXISMODE , &wordProperty.diph);
		if(wordProperty.dwData == DIPROPAXISMODE_ABS)
			usesAbsoluteAxes = true;
		else if(wordProperty.dwData == DIPROPAXISMODE_REL)
			usesAbsoluteAxes = false;
		else 
			MessageBox(0,_T("The called function returned an unknown value."),_T("Unexpected result:"),MB_OK | MB_ICONERROR);

		// get buffer size
		getProperty(DIPROP_AXISMODE , &wordProperty.diph);
		bufferSize = wordProperty.dwData;

		// get vendor and product ID
		getProperty(DIPROP_VIDPID , &wordProperty.diph);
		VendorID = LOWORD(wordProperty.dwData);
		ProductID = HIWORD(wordProperty.dwData);


		// get port name
		stringProperty.diph.dwHow = DIPH_DEVICE;
		stringProperty.diph.dwObj = 0;
		getProperty(DIPROP_GETPORTDISPLAYNAME , &stringProperty.diph);
		portName = stringProperty.wsz;
		
		// get granulatity, X axis
		wordProperty.diph.dwHow = DIPH_BYOFFSET;
		wordProperty.diph.dwObj = 0;
		getProperty(DIPROP_GRANULARITY , &wordProperty.diph);
		XAxisGranularity = wordProperty.dwData;

		// get granulatity, Y axis
		wordProperty.diph.dwObj = 4;
		getProperty(DIPROP_GRANULARITY , &wordProperty.diph);
		YAxisGranularity = wordProperty.dwData;

		// get granulatity, Tip Pressure
		wordProperty.diph.dwObj = 8;
		getProperty(DIPROP_GRANULARITY , &wordProperty.diph);
		TipPressureGranularity = wordProperty.dwData;

		// get granulatity, X tilt
		wordProperty.diph.dwObj = 12;
		getProperty(DIPROP_GRANULARITY , &wordProperty.diph);
		XTiltGranularity = wordProperty.dwData;

		// get granulatity, Y tilt
		wordProperty.diph.dwObj = 16;
		getProperty(DIPROP_GRANULARITY , &wordProperty.diph);
		YTiltGranularity = wordProperty.dwData;

		// get logical range, X axis
		rangeProperty.diph.dwObj = 0;
		getProperty(DIPROP_LOGICALRANGE , &rangeProperty.diph);
		XAxisLogicalMax = rangeProperty.lMax;
		XAxisLogicalMin = rangeProperty.lMin;

		// get logical range, Y axis
		rangeProperty.diph.dwObj = 4;
		getProperty(DIPROP_LOGICALRANGE , &rangeProperty.diph);
		YAxisLogicalMax = rangeProperty.lMax;
		YAxisLogicalMin = rangeProperty.lMin;

		// get logical range, tip pressure
		rangeProperty.diph.dwObj = 8;
		getProperty(DIPROP_LOGICALRANGE , &rangeProperty.diph);
		TipPressureLogicalMax = rangeProperty.lMax;
		TipPressureLogicalMin = rangeProperty.lMin;

		// get logical range, X tilt
		rangeProperty.diph.dwObj = 12;
		getProperty(DIPROP_LOGICALRANGE , &rangeProperty.diph);
		XTiltLogicalMax = rangeProperty.lMax;
		XTiltLogicalMin = rangeProperty.lMin;

		// get logical range, Y tilt
		rangeProperty.diph.dwObj = 16;
		getProperty(DIPROP_LOGICALRANGE , &rangeProperty.diph);
		YTiltLogicalMax = rangeProperty.lMax;
		YTiltLogicalMin = rangeProperty.lMin;

		// get physical range, X axis
		rangeProperty.diph.dwObj = 0;
		getProperty(DIPROP_PHYSICALRANGE , &rangeProperty.diph);
		XAxisPhysicalMax = rangeProperty.lMax;
		XAxisPhysicalMin = rangeProperty.lMin;

		// get physical range, Y axis
		rangeProperty.diph.dwObj = 4;
		getProperty(DIPROP_PHYSICALRANGE , &rangeProperty.diph);
		YAxisPhysicalMax = rangeProperty.lMax;
		YAxisPhysicalMin = rangeProperty.lMin;

		// get physical range, tip pressure
		rangeProperty.diph.dwObj = 8;
		getProperty(DIPROP_PHYSICALRANGE , &rangeProperty.diph);
		TipPressurePhysicalMax = rangeProperty.lMax;
		TipPressurePhysicalMin = rangeProperty.lMin;

		// get physical range, X tilt
		rangeProperty.diph.dwObj = 12;
		getProperty(DIPROP_PHYSICALRANGE , &rangeProperty.diph);
		XTiltPhysicalMax = rangeProperty.lMax;
		XTiltPhysicalMin = rangeProperty.lMin;

		// get physical range, Y tilt
		rangeProperty.diph.dwObj = 16;
		getProperty(DIPROP_PHYSICALRANGE , &rangeProperty.diph);
		YTiltPhysicalMax = rangeProperty.lMax;
		YTiltPhysicalMin = rangeProperty.lMin;

		// get range, X axis
		rangeProperty.diph.dwObj = 0;
		getProperty(DIPROP_RANGE , &rangeProperty.diph);
		XAxisMax = rangeProperty.lMax;
		XAxisMin = rangeProperty.lMin;

		// get range, Y axis
		rangeProperty.diph.dwObj = 4;
		getProperty(DIPROP_RANGE , &rangeProperty.diph);
		YAxisMax = rangeProperty.lMax;
		YAxisMin = rangeProperty.lMin;

		// get range, tip pressure
		rangeProperty.diph.dwObj = 8;
		getProperty(DIPROP_RANGE , &rangeProperty.diph);
		TipPressureMax = rangeProperty.lMax;
		TipPressureMin = rangeProperty.lMin;

		// get range, X tilt
		rangeProperty.diph.dwObj = 12;
		getProperty(DIPROP_RANGE , &rangeProperty.diph);
		XTiltMax = rangeProperty.lMax;
		XTiltMin = rangeProperty.lMin;

		// get range, Y tilt
		rangeProperty.diph.dwObj = 16;
		getProperty(DIPROP_RANGE , &rangeProperty.diph);
		YTiltMax = rangeProperty.lMax;
		YTiltMin = rangeProperty.lMin;
	} // end function getProperties


public:

		/***************
		* data members *
		***************/

	IDirectInputDevice8 *iObject;

private:
	inline DIDigitizer(const DIDigitizer &original){}	// passing objects of this class by value is prohibited.
}; // end class DIDigitizer


#endif // DIGITIZER_WRAPPER_H