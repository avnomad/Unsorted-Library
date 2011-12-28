#ifndef WINDOWS_COMMON_H
#define WINDOWS_COMMON_H

// includes
#include <iostream>
#include <windows.h>
#include <TCHAR.h>

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#ifdef socket
#undef socket
#endif

// make windows.h names prettier!
#define InstanceHandle HINSTANCE
#define WindowHandle HWND
#define ResultHandle HRESULT

// protorypes
std::ostream &operator<<(std::ostream & , const GUID &);

#endif // WINDOWS_COMMON_H
