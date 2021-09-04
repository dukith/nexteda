/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxeexception.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeEXCEPTION_H_
#define LnxeEXCEPTION_H_

#include "nxedef.h"
#include <exception>

#ifdef L_WINDOWS_OS_
class DLLDECL std::exception;
#endif

class DLLDECL nxeException : public std::exception
{
public:
	//! Constructor
	nxeException(const char* pMsg, const char* pFileName, const size_t& pLine) throw()
		: mMsg(NULL), mFileName(NULL), mLine(pLine) {
		CopyString(pMsg, mMsg);
		CopyString(pFileName, mFileName);
	}

	//! Destructor
	virtual ~nxeException() throw() {
		if (mMsg != NULL) {
			M_FREE(mMsg);
		}

		if (mFileName != NULL) {
			M_FREE(mFileName);
		}
	}

	virtual const char* what() const throw() {
		return mMsg;
	}

protected:
	//! Copy string
	void CopyString(const char* pSrcStr, char*& pDestStr) {
		size_t len = M_STRLEN(pSrcStr);
		pDestStr = (char*)M_MALLOC(len + 1);
		if (pDestStr == NULL) {
			return;
		}

		M_MEMCPY(pDestStr, pSrcStr, len);
		pDestStr[len] = '\0';
	}

private:
	//! Message
	char* mMsg;

	//! File name
	char* mFileName;

	//! Line number
	size_t mLine;
};

#endif /* #ifndef LnxeEXCEPTION_H_ */
