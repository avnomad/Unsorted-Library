#ifndef DIRECT_INPUT_COMMON_H
#define DIRECT_INPUT_COMMON_H


#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

// includes
#include <dinput.h>
#include <string>


std::string read_control_type(DWORD type);
std::string read_guid_type(const GUID &type);
std::string read_data_format_flags(DWORD flags);
std::string read_device_type(unsigned char type);
std::string read_device_subtype(WORD type_and_subtype);

#endif // DIRECT_INPUT_COMMON_H
