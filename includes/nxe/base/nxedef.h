/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxedef.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef Lnxe_DEF_H_
#define Lnxe_DEF_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <new>

#ifdef L_NXE_VERSION
#undef L_NXE_VERSION
#endif /* #ifdef L_NXE_VERSION */
#define L_NXE_VERSION 10000 // V01.00.00

#if defined(WIN32) || defined(_WIN32) || defined(WINCE)
#define L_WINDOWS_OS_
#elif defined(__FreeBSD__)
#define L_FREEBSD_OS_
#elif defined(SOLARIS)
#define L_SOLARIS_OS_
#elif defined(__MACH__) && defined(__APPLE__)
#define L_MACH_OS_
#elif defined(__linux) || defined(__linux__)
#define L_LINUX_OS_
#elif (defined(__unix__) || defined(unix))
#define L_UNIX_OS_
#else
#define L_UNKNOWN_OS_
#endif

#if _WIN32 || _WIN64 // Windows
#if _WIN64
#define L_BUILD_64ENV_
#else
#define L_BUILD_32ENV_
#endif
#endif

#if __GNUC__ // GCC
#if __x86_64__ || __ppc64__
#define L_BUILD_64ENV_
#else
#define L_BUILD_32ENV_
#endif
#endif

#define M_MIN(x,y) ((x) < (y) ? (x) : (y))
#define M_MAX(x,y) ((x) > (y) ? (x) : (y))
#define M_ABS(x) (((x) < 0) ? (-(x)) : (x))

#define M_MEMCPY(pDestination, pSource, pLength) memcpy(pDestination, pSource, pLength)
#define M_MEMSET(pDestination, pSetVal, pLength) memset(pDestination, pSetVal, pLength)
#define M_MALLOC(pLength) malloc(pLength)
#define M_MEMCMP(pMem1, pMem2, pLength) memcmp((pMem1), (pMem2), (pLength))
#define M_FREE(pVar) free(pVar)

#define M_STRLEN(pStr) strlen(pStr)
#define M_STRCHR(pStr, pChr) strchr(pStr, pChr)

#ifdef L_WINDOWS_OS_
#define M_SCANF(pFmtStr, pVar, pLen) scanf_s(pFmtStr, pVar, pLen)
#else
#define M_SCANF(pFmtStr, pVar, pLen) scanf(pFmtStr, pVar)
#endif /* #if defined(L_WINDOWS_OS_) */

#ifdef _MSC_VER
#define L_MSVC_C_
#elif defined(__GNUC__)
#define L_GNU_C_
#endif

// Library dynamically load
#ifdef L_WINDOWS_OS_
#define LIB_HANDLE HINSTANCE
#define FUNC_HANDLE FARPROC
#else
#define LIB_HANDLE void*
#define FUNC_HANDLE void*
#endif /* #if defined(L_WINDOWS_OS_) */

#ifdef L_WINDOWS_OS_
#if defined(L_EXPORTDLL)
#define DLLDECL __declspec(dllexport)
#elif defined(L_IMPORTDLL)
#define DLLDECL __declspec(dllimport)
#else
#define DLLDECL
#endif
#else
#define DLLDECL
#endif // defined(L_WINDOWS_OS_)

#ifdef L_WINDOWS_OS_ // Windows
#ifdef L_BUILD_64ENV_
#define Lnxe_LIB_PATH "\\lib\\win64\\"
#elif defined(L_BUILD_32ENV_)
#define Lnxe_LIB_PATH "\\lib\\win32\\"
#endif
#elif defined(L_FREEBSD_OS_) // FreeBSD
#ifdef L_BUILD_64ENV_
#define Lnxe_LIB_PATH "/lib/freebsd64/"
#elif L_BUILD_32ENV_
#define Lnxe_LIB_PATH "/lib/freebsd32/"
#endif
#elif defined(L_SOLARIS_OS_) // Solaris
#ifdef L_BUILD_64ENV_
#define Lnxe_LIB_PATH "/lib/solaris64/"
#elif L_BUILD_32ENV_
#define Lnxe_LIB_PATH "/lib/solaris32/"
#endif
#elif defined(L_MACH_OS_) // MaxOS
#ifdef L_BUILD_64ENV_
#define Lnxe_LIB_PATH "/lib/osx64/"
#elif L_BUILD_32ENV_
#define Lnxe_LIB_PATH "/lib/osx32/"
#endif
#elif defined(L_LINUX_OS_) // Linux
#ifdef L_BUILD_64ENV_
#define Lnxe_LIB_PATH "/lib/rhel64/"
#elif L_BUILD_32ENV_
#define Lnxe_LIB_PATH "/lib/rhel32/"
#endif
#elif defined(L_UNIX_OS_) // Other unix
#else
#define Lnxe_LIB_PATH "."
#endif

//! Cell type
enum nxeCellType {
	LnxeCellType_None = 0,
	LnxeCellType_Schematic = 1,
	LnxeCellType_Layout = 2
};

//! Model type
enum nxeModelType {
	LnxeModelType_None = 0,
	LnxeModelType_Device = 1,
	LnxeModelType_Block = 2
};

//! Device type
enum nxeDeviceType {
	LnxeDeviceType_None = 0,
	LnxeDeviceType_Resistor = 1,
	LnxeDeviceType_Capacitor = 2,
	LnxeDeviceType_Inductor = 3,
	LnxeDeviceType_Diode = 4,
	LnxeDeviceType_NPN = 5,
	LnxeDeviceType_PNP = 6,
	LnxeDeviceType_PMOS = 7,
	LnxeDeviceType_NMOS = 8
};


#endif /* #ifndef Ltest_anif_DEF_H_ */





