/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxeutil.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeUTIL_H_
#define LnxeUTIL_H_

#include "nxe/base/nxedef.h"

class nxePSpcLoader;

class DLLDECL nxeUtil {
public:
	//! Constructor
	nxeUtil() {};

	//! Destructor
	virtual ~nxeUtil() {};

	//! Copy string
	virtual void CopyString(const char* pSrcStr, char*& pDestStr) = 0;

	/**
	 * \brief Compare string
	 *
	 * \return 1 pStr1 > pStr2
	 * \return 0 pStr1 = pStr2
	 * \return -1 pStr1 < pStr2
	 */
	virtual int CompareStr(const char* pStr1, const char* pStr2) = 0;

	/**
	 * \brief Trim space from string
	 */
	virtual void TrimString(const char* pStr, char* pOutStr) = 0;

	/**
	 * \brief To upper
	 */
	virtual void ToUpper(const char* pStr, char* pOutStr) = 0;

	/**
	 * \brief Print into string
	 */
	virtual void Sprintf(char*& pOutStr, const char* pFmt, ...) = 0;

	/**
	 * \brief Clear console
	 */
	virtual void ClearConsole() = 0;

	/**
	 * \brief Get real path
	 */
	virtual void GetRealPath(const char* pPath, char*& pRealPath) = 0;

	/**
	 * \brief Get real path
	 */
	virtual void SetEnvVar(const char* pEnvName, const char* pEnvVal, int pIsAppend = 0) = 0;

	/**
	 * \brief Get pspice loader
	 */
	virtual nxePSpcLoader* CreatePSpiceLoader() = 0;

};

#endif /* #ifndef LnxeUTIL_H_ */

