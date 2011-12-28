#ifndef OPERATIONAL_DEVICE_H
#define OPERATIONAL_DEVICE_H

#include "Device Wrapper.h"
#include "common.h"
#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>

class OperationalDevice : public DIDevice
{
private:

	/***************
	* data members *
	***************/

	std::vector<DIDEVICEOBJECTINSTANCE> deviceObjects;
	BYTE *cachedData;
	unsigned int cachedDataSize;



	static BOOL __stdcall callBack(LPCDIDEVICEOBJECTINSTANCE deviceObject,LPVOID deviceObjects)		// callBack (for use by the constructor)
	{
		if(!(deviceObject->dwType & DIDFT_NODATA))
			((vector<DIDEVICEOBJECTINSTANCE> *)deviceObjects)->push_back(*deviceObject);
		return DIENUM_CONTINUE;
	} // end function callBack


public:

	/***************************
	* contructors & destructor *
	***************************/

	OperationalDevice(IDirectInput8 *directInputObject , const GUID &deviceID)						// OperationalDevice constructor
		:DIDevice(directInputObject,deviceID)
	{
		std::auto_ptr<DIOBJECTDATAFORMAT> dataFormatArray(0);
		DIDATAFORMAT dataFormat;
		unsigned int maxOffset = 0;
		unsigned int respectiveSize;	// of the deviceObject with max offset

		enumObjects(callBack,&deviceObjects,DIDFT_ALL);
		if(deviceObjects.size() == 0)
		{
			cachedData = 0;
			cachedDataSize = 0;
			return;
		} // end if
		dataFormatArray.reset(new DIOBJECTDATAFORMAT[deviceObjects.size()]);

		for(unsigned int c = 0 ; c < deviceObjects.size() ; ++c)
		{
			dataFormatArray.get()[c].pguid = &deviceObjects[c].guidType;
			dataFormatArray.get()[c].dwOfs = deviceObjects[c].dwOfs;
			dataFormatArray.get()[c].dwType = deviceObjects[c].dwType;
			dataFormatArray.get()[c].dwFlags = deviceObjects[c].dwFlags;
			if(deviceObjects[c].dwOfs >= maxOffset)
			{
				maxOffset = deviceObjects[c].dwOfs;
				respectiveSize = (deviceObjects[c].guidType == GUID_Button || deviceObjects[c].guidType == GUID_Key) ? 1 : 4;
			} // end if
		} // end for
		cachedDataSize = (maxOffset+respectiveSize+3) & 0xfffffffc;

		dataFormat.dwSize = sizeof(DIDATAFORMAT);
		dataFormat.dwObjSize = sizeof(DIOBJECTDATAFORMAT);
		dataFormat.dwFlags = DIDF_ABSAXIS;
		dataFormat.dwDataSize = cachedDataSize;
		dataFormat.dwNumObjs = deviceObjects.size();
		dataFormat.rgodf = dataFormatArray.get();

		setDataFormat(&dataFormat);
		cachedData = new BYTE[cachedDataSize];
	} // end OperationalDevice constructor


	~OperationalDevice()																		// OperationalDevice destructor
	{
		delete[] cachedData;
	} // end OperationalDevice destructor


	/************
	* operators *
	************/


	/*******************
	* member functions *
	*******************/

	const BYTE *getCachedData() const															// getCachedData
	{
		return cachedData;
	} // end function getCachedData


	unsigned int getCachedDataSize() const														// getCachedDataSize
	{
		return cachedDataSize;
	} // end function getCachedDataSize


	const std::vector<DIDEVICEOBJECTINSTANCE> &getDeviceObjects() const							// getDeviceObjects
	{
		return deviceObjects;
	} // end function getDeviceObjects


	OperationalDevice &cacheData()																// cacheData
	{
		memset(cachedData,0,cachedDataSize);
		while(!getDeviceState(cachedDataSize,cachedData))
			acquire();
		return *this;
	} // end function cacheData

}; // end class OperationalDevice


std::ostream &operator<<(std::ostream &outStream , const OperationalDevice &device)
{
	std::ios_base::fmtflags flags = outStream.flags();	// store the old output format.
	const std::vector<DIDEVICEOBJECTINSTANCE> &deviceObjects = device.getDeviceObjects();

	for(unsigned int c = 0 ; c < deviceObjects.size() ; ++c)
	{
		outStream << ' ' << left << setw(30) << read_guid_type(deviceObjects[c].guidType);
		if(deviceObjects[c].guidType == GUID_Button || deviceObjects[c].guidType == GUID_Key)
		{
			if(*(device.getCachedData() + deviceObjects[c].dwOfs) & 0x80)
				outStream << "down";
			else
				outStream << "up";
			outStream << '\n';
		}
		else
		{
			outStream << *(LONG*)(device.getCachedData() + deviceObjects[c].dwOfs) << '\n';
		} // end else
	} // end for

	outStream.flags(flags);
	return outStream;
} // end function operator <<


#endif // OPERATIONAL_DEVICE_H