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
#include "nxe/base/nxeversion.h"

#if defined(L_WINDOWS_OS_) && defined(L_MSVC_C_)
#include <windows.h>
#include <direct.h>
#define LIB_NAME_ANIF "anif.dll"
#else
#include <dlfcn.h>
#include <unistd.h>
#define LIB_NAME_ANIF "libanif.so"
#endif

#define Lnxe_LIBPATH_VARNAME "NXE_LIB_PATH"
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
	static void Start(const char* pCtrlFile) {
		if (mMyself != NULL) {
			delete mMyself;
		}

		mMyself = new nxeAPI();
		mMyself->SetLibPath();
		if (mMyself->Load() != 1) {
			char msg[Lnxe_PATH_MAXLEN];
			snprintf(msg, Lnxe_PATH_MAXLEN, "Cannot load library from '%s'. Please check 'lib' directory.", mMyself->mLibPath);
			throw nxeException(msg, __FILE__, __LINE__);
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

	//! Get version by text
	static const char* GetVersionText() {
		if (mMyself == NULL || mMyself->ifUtil == NULL) {
			throw nxeException("The API is not started. Please call nxeAPI::Start() method before.", __FILE__, __LINE__);
		}
		if (mMyself->mVerText != NULL) {
			return mMyself->mVerText;
		}
		return mMyself->GetVersionByText();
	}

	//! Get version number
	static int GetVersionNumber() {
		if (mMyself == NULL || mMyself->ifUtil == NULL) {
			throw nxeException("The API is not started. Please call nxeAPI::Start() method before.", __FILE__, __LINE__);
		}
		return mMyself->GetVersionByNumber();
	}

protected:
	//! Constructor
	nxeAPI(const char* pLibName = LIB_NAME_ANIF)
		: mLibName(NULL), mLibPath(NULL), hLib(NULL), ifStart(NULL), ifEnd(NULL), ifDesigner(NULL), ifUtil(NULL), mVerText(NULL)
	{
		size_t len = M_STRLEN(pLibName);
		mLibName = (char*)M_MALLOC(len + 1);
		if (mLibName == NULL) {
			throw nxeOutOfMemoryException(__FILE__, __LINE__);
		}

		M_MEMCPY(mLibName, pLibName, len);
		mLibName[len] = '\0';
	}

	//! Destrutor
	virtual ~nxeAPI() {
		if (hLib) {
#if defined(L_WINDOWS_OS_) && defined(L_MSVC_C_)
			FreeLibrary(hLib);
#else
			dlclose(hLib);
#endif
		}

		if (NULL != mLibName) {
			M_FREE(mLibName);
		}

		if (NULL != mLibPath) {
			M_FREE(mLibPath);
		}

		if (NULL != mVerText) {
			M_FREE(mVerText);
		}
	}

	//! Get version by text
	const char* GetVersionByText() const {
		char* vertext = (char*)M_MALLOC(255);

		int ver_num = GetVersionNumber();
		int major_num = ver_num / 100000;
		int minor_num = (ver_num / 100) % 1000;
		int patch_num = ver_num % 100;
		snprintf(vertext, 255, "%d.%03d.%02d", major_num, minor_num, patch_num);

		((nxeAPI*)this)->mVerText = vertext;

		return mVerText;
	}

	//! Get version number
	int GetVersionByNumber() const {
		return NXE_VERSION;
	}

	//! Library name (File full path of dll or *.so, etc...)
	const char* GetLibName() const {
		return mLibName;
	}

	//! Add path referred during searching library
	void SetLibPath() {
		char lib_base_path[Lnxe_PATH_MAXLEN] = "";
		CheckAndSetDefaultLibPath(lib_base_path);

		// Set path to mLibPath
		size_t base_len = M_STRLEN(lib_base_path);
		size_t ext_len = M_STRLEN(Lnxe_LIB_PATH);
		mLibPath = (char*)M_MALLOC(base_len + ext_len + 1);
		if (NULL != mLibPath) {
			M_MEMCPY(mLibPath, lib_base_path, base_len);
			M_MEMCPY(mLibPath + base_len, Lnxe_LIB_PATH, ext_len);
			mLibPath[base_len + ext_len] = '\0';
		}
		else {
			throw nxeOutOfMemoryException(__FILE__, __LINE__);
		}

		// Set enviroment vairable PATH (for Windows) or LD_LIBRARY_PATH (for Linux/Unix)
		char buffer[Lnxe_PATH_MAXLEN] = "";
#if defined(L_WINDOWS_OS_) && defined(L_MSVC_C_)
		strcat_s(buffer, mLibPath);
		strcat_s(buffer, ";%PATH%");
		_putenv_s("PATH", buffer);
#else
		strcat(buffer, mLibPath);
		char* cur_libpath = getenv("LD_LIBRARY_PATH");
		if (cur_libpath != NULL && M_STRLEN(cur_libpath) > 0) {
			strcat(buffer, ":${LD_LIBRARY_PATH}");
		}
		setenv("LD_LIBRARY_PATH", buffer, 1);
#endif
	}

	/**
	 * \brief Get current directory as application path
	 */
	void CheckAndSetDefaultLibPath(char* pLibPath) {
		// Get path from enviroment variable
#if defined(L_WINDOWS_OS_) && defined(L_MSVC_C_)
		char* envvar_val = NULL;
		size_t len;
		errno_t err = _dupenv_s(&envvar_val, &len, Lnxe_LIBPATH_VARNAME);
		if (err) {
			envvar_val = NULL;
		}
#else
		char* envvar_val = getenv(Lnxe_LIBPATH_VARNAME);
#endif

		if (NULL != envvar_val && strlen(envvar_val) > 0) {
#if defined(L_WINDOWS_OS_) && defined(L_MSVC_C_)
			strncpy_s(pLibPath, Lnxe_PATH_MAXLEN, envvar_val, strlen(envvar_val));
#else
			strncpy(pLibPath, envvar_val, strlen(envvar_val));
#endif
		}
		else {
			SetLibPathFromExecPath(pLibPath);
		}

#if defined(L_WINDOWS_OS_) && defined(L_MSVC_C_)
		if (NULL != envvar_val) {
			free(envvar_val);
		}
#endif
	}

	void SetLibPathFromExecPath(char* pLibPath) {
		char exec_file_path[Lnxe_PATH_MAXLEN];

#if defined(L_WINDOWS_OS_) && defined(L_MSVC_C_)
		int bytes = GetModuleFileName(NULL, exec_file_path, Lnxe_PATH_MAXLEN);
		if (0 == bytes) {
			return;
		}
#else
		char szTmp[32];
		sprintf(szTmp, "/proc/%d/exe", getpid());
		int bytes = MIN(readlink(szTmp, exec_file_path, Lnxe_PATH_MAXLEN), Lnxe_PATH_MAXLEN - 1);
		if (bytes >= 0) {
			exec_file_path[bytes] = '\0';
		}
		else {
			return;
		}
#endif

		// Separate directory and file from full path
		const char* last_slash1 = strrchr(exec_file_path, '\\');
		const char* last_slash2 = strrchr(exec_file_path, '/');
		const char* last_slash = NULL;
		if (NULL == last_slash1 && NULL == last_slash2) {
			return;
		}
		else if (NULL == last_slash1) {
			last_slash = last_slash2;
		}
		else if (NULL == last_slash2) {
			last_slash = last_slash1;
		}
		else {
			last_slash = (last_slash1 < last_slash2) ? last_slash2 : last_slash1;
		}

		size_t path_len = M_STRLEN(exec_file_path);
		size_t filenm_len = M_STRLEN(last_slash);
		size_t app_path_len = path_len - filenm_len;

		// Set to lib path
		M_MEMCPY(pLibPath, exec_file_path, app_path_len);
		pLibPath[app_path_len] = '\0';
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

#if defined(L_WINDOWS_OS_) && defined(L_MSVC_C_)
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
#if defined(L_WINDOWS_OS_) && defined(L_MSVC_C_)
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
	//! Library name (File full path of dll or *.so, etc...)
	char* mLibName;
	char* mLibPath;

	//! Library handler
	LIB_HANDLE hLib;

	//! Version text
	char* mVerText;

	//! NXE I/F
	NXEStartIF ifStart;
	NXEEndIF ifEnd;
	NXESchDesignerIF ifDesigner;
	NXEUtilIF ifUtil;

};

template <class DUMMY>
nxeAPI* nxeAPIBase<DUMMY>::mMyself = NULL;

#endif /* #ifndef Lnxe_API_H */


