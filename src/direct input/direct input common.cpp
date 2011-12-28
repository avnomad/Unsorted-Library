#include "common.h"

// includes
#include <sstream>


std::string read_control_type(DWORD type)
{
	std::string s;

	if(type & DIDFT_ABSAXIS)
		s += "absolute axis, ";
	if(type & DIDFT_RELAXIS)
		s += "relative axis, ";
	if(type & DIDFT_PSHBUTTON)
		s += "push button, ";	
	if(type & DIDFT_TGLBUTTON)
		s += "toggle button, ";
	if(type & DIDFT_POV)
		s += "point-of-view controller, ";
	if(type & DIDFT_ALIAS)
		s += "identified by HID usage alias, ";
	if(type & DIDFT_COLLECTION)
		s += "HID link collection, ";
	if(type & DIDFT_FFACTUATOR)
		s += "has FF actuator, ";
	if(type & DIDFT_FFEFFECTTRIGGER)
		s += "can trigger FF effects, ";
	if(type & DIDFT_NOCOLLECTION)
		s += "not in a HID link collection, ";
	if(type & DIDFT_NODATA)
		s += "does not generate data, ";
	if(type & DIDFT_OUTPUT)
		s += "supports output, ";	
	if(type & DIDFT_VENDORDEFINED)
			s += "defined by manufacturer, ";
	s += "instance number: ";
	return s + static_cast<std::ostringstream &>(std::ostringstream() << DIDFT_GETINSTANCE(type)).str();
} // end function read_device_type

std::string read_guid_type(const GUID &type)
{
	if(type == GUID_XAxis)
		return "x axis";
	else if(type == GUID_YAxis)
		return "y axis";
	else if(type == GUID_ZAxis)
		return "z axis (wheel, throttle)";
	else if(type == GUID_RxAxis)
		return "rotation around x axis";
	else if(type == GUID_RyAxis)
		return "rotation around y axis";
	else if(type == GUID_RzAxis)
		return "rotation around z axis";
	else if(type == GUID_Slider)
		return "slider axis";
	else if(type == GUID_Button)
		return "mouse button";
	else if(type == GUID_Key)
		return "keyboard key";
	else if(type == GUID_POV)
		return "point-of-view indicator";
	else if(type == GUID_Unknown)
		return "unknown";
	else
		return "-";
} // end function read_guid_type

std::string read_data_format_flags(DWORD flags)
{
	std::string s;

	if(flags & DIDOI_ASPECTACCEL)
		s += "reports acceleration, ";
	if(flags & DIDOI_ASPECTFORCE)
		s += "reports force, ";
	if(flags & DIDOI_ASPECTVELOCITY)
		s += "reports velocity, ";
	if(flags & DIDOI_ASPECTPOSITION)
		s += "reports position, ";
	if(flags & DIDOI_ASPECTMASK)
		s += "aspect bits, ";
	if(flags & DIDOI_FFACTUATOR)
		s += "can have FF effects aplied, ";
	if(flags & DIDOI_FFEFFECTTRIGGER)
		s += "can trigger playback of FF effects, ";
	if(flags & DIDOI_GUIDISUSAGE)
		s += "information in pguid, ";
	if(flags & DIDOI_POLLED)
		s += "waits for method call, ";
	if(s.size() > 0)
	{
		s.erase(s.end()-1);
		s.erase(s.end()-1);
	} // end if
	else
		s = "-";
	return s;
} // end function read_data_format_flags

std::string read_device_type(unsigned char type)
{
	switch(type)
	{
	case DI8DEVTYPE_1STPERSON:
		return "device for 1st person games";
	case DI8DEVTYPE_DEVICE:
		return "not in a category";
	case DI8DEVTYPE_DEVICECTRL:
		return "controls another device";
	case DI8DEVTYPE_DRIVING:
		return "device for steering";
	case DI8DEVTYPE_FLIGHT:
		return "controller for flight simulation";
	case DI8DEVTYPE_GAMEPAD:
		return "gamepad";
	case DI8DEVTYPE_JOYSTICK:
		return "joystick";
	case DI8DEVTYPE_KEYBOARD:
		return "keyboard or keyboardlike device";
	case DI8DEVTYPE_MOUSE:
		return "mouse or mouse-like device (such as a trackball)";
	case DI8DEVTYPE_REMOTE:
		return "remote-control device";
	case DI8DEVTYPE_SCREENPOINTER:
		return "screenpointer";
	case DI8DEVTYPE_SUPPLEMENTAL :
		return "specialized device";
	default:
		return "-";
	} // end switch
} // end function read_device_type

std::string read_device_subtype(WORD type_and_subtype)
{
	switch(type_and_subtype & 0x00ff)
	{
	case DI8DEVTYPE_1STPERSON:
		switch((type_and_subtype & 0xff00) >> 8)
		{
		case DI8DEVTYPE1STPERSON_LIMITED:
			return "insufficient device objects";
		case DI8DEVTYPE1STPERSON_SHOOTER:
			return "designed for 1st person shooters";
		case DI8DEVTYPE1STPERSON_SIXDOF:
			return "6 degrees of freedom";
		case DI8DEVTYPE1STPERSON_UNKNOWN:
			return "unknown subtype";
		} // end inner-switch
	case DI8DEVTYPE_DEVICE:
		return "no subtype";
	case DI8DEVTYPE_DEVICECTRL:
		switch((type_and_subtype & 0xff00) >> 8)
		{
		case DI8DEVTYPEDEVICECTRL_COMMSSELECTION:
			return "used to make communications selections";
		case DI8DEVTYPEDEVICECTRL_COMMSSELECTION_HARDWIRED:
			return "muse use it's default configuration";
		case DI8DEVTYPEDEVICECTRL_UNKNOWN:
			return "unknown subtype";
		} // end inner-switch
	case DI8DEVTYPE_DRIVING:
		switch((type_and_subtype & 0xff00) >> 8)
		{
		case DI8DEVTYPEDRIVING_COMBINEDPEDALS:
			return "acceleration and brake pedal values from separate axes";
		case DI8DEVTYPEDRIVING_DUALPEDALS:
			return "acceleration and brake pedal values from separate axes";
		case DI8DEVTYPEDRIVING_HANDHELD:
			return "hand-held steering device";
		case DI8DEVTYPEDRIVING_LIMITED:
			return "insufficient device objects";
		case DI8DEVTYPEDRIVING_THREEPEDALS:
			return "acceleration, brake, and clutch pedal values from separate axes";
		} // end inner-switch
	case DI8DEVTYPE_FLIGHT:
		switch((type_and_subtype & 0xff00) >> 8)
		{
		case DI8DEVTYPEFLIGHT_LIMITED:
			return "insufficient device objects";
		case DI8DEVTYPEFLIGHT_RC:
			return "based on a remote control for model aircraft";
		case DI8DEVTYPEFLIGHT_STICK:
			return "joystick";
		case DI8DEVTYPEFLIGHT_YOKE:
			return "yoke";
		} // end inner-switch
	case DI8DEVTYPE_GAMEPAD:
		switch((type_and_subtype & 0xff00) >> 8)
		{
		case DI8DEVTYPEGAMEPAD_LIMITED:
			return "insufficient device objects";
		case DI8DEVTYPEGAMEPAD_STANDARD:
			return "standard (minimum device objects)";
		case DI8DEVTYPEGAMEPAD_TILT:
			return "can report x-axis and y-axis data based on the attitude of the controller";
		} // end inner-switch
	case DI8DEVTYPE_JOYSTICK:
		switch((type_and_subtype & 0xff00) >> 8)
		{
		case DI8DEVTYPEJOYSTICK_LIMITED:
			return "insufficient device objects";
		case DI8DEVTYPEJOYSTICK_STANDARD:
			return "standard (minimum device objects)";
		} // end inner-switch
	case DI8DEVTYPE_KEYBOARD:
		switch((type_and_subtype & 0xff00) >> 8)
		{
		case DI8DEVTYPEKEYBOARD_UNKNOWN:
			return "subtype could not be determined";
		case DI8DEVTYPEKEYBOARD_PCXT:
			return "IBM PC/XT 83-key keyboard";
		case DI8DEVTYPEKEYBOARD_OLIVETTI:
			return "Olivetti 102-key keyboard";
		case DI8DEVTYPEKEYBOARD_PCAT:
			return "IBM PC/AT 84-key keyboard";
		case DI8DEVTYPEKEYBOARD_PCENH:
			return "IBM PC Enhanced 101/102-key or Microsoft Natural keyboard";
		case DI8DEVTYPEKEYBOARD_NOKIA1050:
			return "Nokia 1050 keyboard";
		case DI8DEVTYPEKEYBOARD_NOKIA9140:
			return "Nokia 9140 keyboard";
		case DI8DEVTYPEKEYBOARD_NEC98:
			return "Japanese NEC PC98 keyboard";
		case DI8DEVTYPEKEYBOARD_NEC98LAPTOP:
			return "Japanese NEC PC98 laptop keyboard";
		case DI8DEVTYPEKEYBOARD_NEC98106:
			return "Japanese NEC PC98 106-key keyboard";
		case DI8DEVTYPEKEYBOARD_JAPAN106:
			return "Japanese 106-key keyboard";
		case DI8DEVTYPEKEYBOARD_JAPANAX:
			return "Japanese AX keyboard";
		case DI8DEVTYPEKEYBOARD_J3100:
			return "Japanese J3100 keyboard";
		} // end inner-switch
	case DI8DEVTYPE_MOUSE:
		switch((type_and_subtype & 0xff00) >> 8)
		{
		case DI8DEVTYPEMOUSE_ABSOLUTE:
			return "returns absolute axis data";
		case DI8DEVTYPEMOUSE_FINGERSTICK:
			return "fingerstick";
		case DI8DEVTYPEMOUSE_TOUCHPAD:
			return "touchpad";
		case DI8DEVTYPEMOUSE_TRACKBALL:
			return "trackball";
		case DI8DEVTYPEMOUSE_TRADITIONAL:
			return "traditional";
		case DI8DEVTYPEMOUSE_UNKNOWN:
			return "subtype could not be determined";
		} // end inner-switch
	case DI8DEVTYPE_REMOTE:
		switch((type_and_subtype & 0xff00) >> 8)
		{
		case DI8DEVTYPEREMOTE_UNKNOWN:
			return "subtype could not be determined";
		} // end inner-switch
	case DI8DEVTYPE_SCREENPOINTER:
		switch((type_and_subtype & 0xff00) >> 8)
		{
		case DI8DEVTYPESCREENPTR_UNKNOWN:
			return "unknown subtype";
		case DI8DEVTYPESCREENPTR_LIGHTGUN:
			return "light gun";
		case DI8DEVTYPESCREENPTR_LIGHTPEN:
			return "light pen";
		case DI8DEVTYPESCREENPTR_TOUCH:
			return "touch screen";
		} // end inner-switch
	case DI8DEVTYPE_SUPPLEMENTAL :
		switch((type_and_subtype & 0xff00) >> 8)
		{
		case DI8DEVTYPESUPPLEMENTAL_2NDHANDCONTROLLER:
			return "secondary handheld controller";
		case DI8DEVTYPESUPPLEMENTAL_COMBINEDPEDALS:
			return "primary function is to report acceleration and brake pedal values from a single axis";
		case DI8DEVTYPESUPPLEMENTAL_DUALPEDALS:
			return "primary function is to report acceleration and brake pedal values from separate axes";
		case DI8DEVTYPESUPPLEMENTAL_HANDTRACKER:
			return "tracks hand movement";
		case DI8DEVTYPESUPPLEMENTAL_HEADTRACKER:
			return "tracks head movement";
		case DI8DEVTYPESUPPLEMENTAL_RUDDERPEDALS:
			return "rudder pedals";
		case DI8DEVTYPESUPPLEMENTAL_SHIFTER:
			return "reports gear selection from an axis";
		case DI8DEVTYPESUPPLEMENTAL_SHIFTSTICKGATE:
			return "reports gear selection from button states";
		case DI8DEVTYPESUPPLEMENTAL_SPLITTHROTTLE:
			return "primary function is to report at least two throttle values. It may have other controls";
		case DI8DEVTYPESUPPLEMENTAL_THREEPEDALS:
			return "primary function is to report acceleration, brake, and clutch pedal values from separate axes";
		case DI8DEVTYPESUPPLEMENTAL_THROTTLE:
			return "primary function is to report a single throttle value. It may have other controls";
		case DI8DEVTYPESUPPLEMENTAL_UNKNOWN:
			return "unknown subtype";
		} // end inner-switch
	} // end outer-switch
	return "-";
} // end function read_device_subtype
