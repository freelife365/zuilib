#pragma once

#include "targetver.h"

#ifdef __GNUC__
// 怎么都没找到min，max的头文件-_-
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#endif

#ifndef __FILET__
#define __DUILIB_STR2WSTR(str)	L##str
#define _DUILIB_STR2WSTR(str)	__DUILIB_STR2WSTR(str)
#ifdef _UNICODE
#define __FILET__		_DUILIB_STR2WSTR(__FILE__)
#define __FUNCTIONT__	_DUILIB_STR2WSTR(__FUNCTION__)
#else
#define __FILET__	__FILE__
#define __FUNCTIONT__	__FUNCTION__
#endif
#endif

#define _CRT_SECURE_NO_DEPRECATE

// Remove pointless warning messages
#ifdef _MSC_VER
#pragma warning (disable : 4511) // copy operator could not be generated
#pragma warning (disable : 4512) // assignment operator could not be generated
#pragma warning (disable : 4702) // unreachable code (bugs in Microsoft's STL)
#pragma warning (disable : 4786) // identifier was truncated
#pragma warning (disable : 4996) // function or variable may be unsafe (deprecated)
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS // eliminate deprecation warnings for VS2005
#endif
#endif // _MSC_VER

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
//#include <windows.h>



// TODO: 在此处引用程序需要的其他头文件
#include "zuilib.h"
#include <olectl.h>

#define lengthof(x) (sizeof(x)/sizeof(*x))
#define MAX max
#define MIN min
#define CLAMP(x,a,b) (MIN(b,MAX(a,x)))


#ifdef _USE_GDIPLUS
using namespace Gdiplus;
#endif
