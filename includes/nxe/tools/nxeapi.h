/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxeapi.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef Lnxe_API_H
#define Lnxe_API_H

#include "nxe/base/nxedef.h"
#include "nxe/base/nxeexception.h"

#ifdef L_WINDOWS_OS_
#include <windows.h>
#include <direct.h>
#define LIB_NAME_ANIF "anif.dll"
#else
#include <dlfcn.h>
#include <unistd.h>
#define LIB_NAME_ANIF "libanif.so"
#endif

#define Lnxe_PATH_MAXLEN 2048

class nxeSchDesigner;
class nxeUtil;

typedef void (*NXEStartIF)(const char*);
typedef void (*NXEEndIF)();
typedef nxeSchDesigner* (*NXESchDesignerIF)();
typedef nxeUtil* (*NXEUtilIF)();

template <class DUMMY>
class nxeAPIBase {
public:
	nxeAPIBase() {};
	virtual ~nxeAPIBase() {};

protected:
	static class nxeAPI* mMyself;
};

class nxeAPI : public nxeAPIBase<void>
{
public:
	static void Start(const char* pAppPath, const char* pCtrlFile) {
		if (mMyself != NULL) {
			delete mMyself;
		}

		mMyself = new nxeAPI();
		mMyself->SetLibPath(pAppPath);
		if (mMyself->Load() != 1) {
			throw nxeException("Cannot load library. Please check 'lib' directory.", __FILE__, __LINE__);
		}

		// Initialize designer
		mMyself->ifStart(pCtrlFile);
	}

	static void End() {
		if (mMyself != NULL) {
			mMyself->ifEnd();
			delete mMyself;
			mMyself = NULL;
		}
	}
	
	static nxeSchDesigner* GetSchDesigner() {
		if (mMyself == NULL || mMyself->ifDesigner == NULL) {
			throw nxeException("The API is not started. Please call nxeAPI::Start() method before.", __FILE__, __LINE__);
		}
		return mMyself->ifDesigner();
	}
	
	static nxeUtil* GetUtil() {
		if (mMyself == NULL || mMyself->ifUtil == NULL) {
			throw nxeException("The API is not started. Please call nxeAPI::Start() method before.", __FILE__, __LINE__);
		}
		return mMyself->ifUtil();
	}

protected:
	//! Constructor
	nxeAPI(const char* pLibName = LIB_NAME_ANIF)
		: mLibName(NULL), hLib(NULL), ifStart(NULL), ifEnd(NULL), ifDesigner(NULL), ifUtil(NULL)
	{
		size_t len = M_STRLEN(pLibName);
		mLibName = (char*)M_MALLOC(M_MAX(len, Lnxe_PATH_MAXLEN) + 1);
		if (mLibName == NULL) {
			throw nxeException("Out of memory", __FILE__, __LINE__);
		}

		M_MEMCPY(mLibName, pLibName, len);
		mLibName[len] = '\0';
	}

	//! Destrutor
	virtual ~nxeAPI() {
		if (mLibName != NULL) {
			M_FREE(mLibName);
		}

		if (hLib) {
#ifdef L_WINDOWS_OS_
			FreeLibrary(hLib);
#else
			dlclose(hLib);
#endif
		}
	}

	//! Library name (File full path of dll or *.so, etc...)
	const char* GetLibName() const {
		return mLibName;
	}

	//! Add path referred during searching library
	void SetLibPath(const char* pAppPath) {
		char cwd[Lnxe_PATH_MAXLEN] = "";
		CheckAndSetAppPath(cwd, pAppPath);

#ifdef L_WINDOWS_OS_
		char buffer[Lnxe_PATH_MAXLEN] = "PATH=";
		strcat_s(buffer, cwd);
#else
		char buffer[Lnxe_PATH_MAXLEN] = "LD_LIBRARY_PATH=";
		char fullpath[Lnxe_PATH_MAXLEN] = "";
		strcat(buffer, cwd);
		strcat(fullpath, cwd);
#endif

#ifdef L_WINDOWS_OS_
		strcat_s(buffer, Lnxe_LIB_PATH);
		strcat_s(buffer, ";%PATH%");
		_putenv(buffer);
#else
		strcat(buffer, Lnxe_LIB_PATH);
		char* cur_libpath = getenv("LD_LIBRARY_PATH");
		if (cur_libpath != NULL && M_STRLEN(cur_libpath) > 0) {
			strcat(buffer, ":${LD_LIBRARY_PATH}");
		}
		putenv(buffer);

		strcat(fullpath, Lnxe_LIB_PATH);
		strcat(fullpath, mLibName);
		strcpy(mLibName, fullpath);
#endif
	}

	/**
	 * \brief Get current directory as application path
	 */
	void CheckAndSetAppPath(char* pAppPath, const char* pInputAppPath) {
#ifdef L_WINDOWS_OS_
		if (pInputAppPath == NULL || strlen(pInputAppPath) == 0) {
			_getcwd(pAppPath, sizeof(pAppPath));
		}
		else {
			strncpy_s(pAppPath, Lnxe_PATH_MAXLEN, pInputAppPath, strlen(pInputAppPath));
		}
#else
		if (pInputAppPath == NULL || strlen(pInputAppPath) == 0) {
			getcwd(pAppPath, sizeof(pAppPath));
		}
		else {
			strncpy(pAppPath, pInputAppPath);
		}
#endif
	}

	/**
	 * \brief Load library
	 *
	 * \return 1 Library loaded successfully
	 * \return 0 Failed
	 */
	int Load() {
		if (hLib) {
			return 1;
		}

#ifdef L_WINDOWS_OS_
		hLib = LoadLibrary(mLibName);
#else
		hLib = dlopen(mLibName, RTLD_LAZY | RTLD_GLOBAL);
#endif

		if (!hLib) {
			return 0;
		}

		return LoadNXEIFFunc();
	}

	/**
	 * \brief Load function
	 */
	FUNC_HANDLE GetFunc(const char* pFuncName) {
#ifdef L_WINDOWS_OS_
		return GetProcAddress(hLib, pFuncName);
#else
		return dlsym(hLib, pFuncName);
#endif
	}

	//! Load NXEIF function
	int LoadNXEIFFunc() {
		NXEStartIF func1 = (NXEStartIF)GetFunc("NXEStart");
		if (!func1) {
			return 0;
		}
		ifStart = func1;

		NXEEndIF func2 = (NXEEndIF)GetFunc("NXEEnd");
		if (!func2) {
			return 0;
		}
		ifEnd = func2;

		NXESchDesignerIF func3 = (NXESchDesignerIF)GetFunc("NXEGetSchDesigner");
		if (!func3) {
			return 0;
		}
		ifDesigner = func3;

		NXEUtilIF func4 = (NXEUtilIF)GetFunc("NXEGetUtility");
		if (!func4) {
			return 0;
		}
		ifUtil = func4;

		return 1;
	}

private:
	//! NXE I/F
	NXEStartIF ifStart;
	NXEEndIF ifEnd;
	NXESchDesignerIF ifDesigner;
	NXEUtilIF ifUtil;

private:
	//! Library name (File full path of dll or *.so, etc...)
	char* mLibName;

	//! Library handler
	LIB_HANDLE hLib;
};

template <class DUMMY>
nxeAPI* nxeAPIBase<DUMMY>::mMyself = NULL;

#endif /* #ifndef Lnxe_API_H */


