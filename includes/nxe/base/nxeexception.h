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
	nxeException() throw()
		: mMsg(NULL), mFileName(NULL), mLine(0) {
	}

	//! Copy string
	void CopyString(const char* pSrcStr, char*& pDestStr, const size_t pMaxLen = 0, const int& pAllocDest = 1) {
		size_t len = M_STRLEN(pSrcStr);
		if (pMaxLen > 0) {
			len = M_MIN(len, pMaxLen);
		}

		if (1 == pAllocDest) {
			pDestStr = (char*)M_MALLOC(len + 1);
		}

		if (pDestStr == NULL) {
			return;
		}

		M_MEMCPY(pDestStr, pSrcStr, len);
		pDestStr[len] = '\0';
	}

	//! Get message
	void SetMsg(char* pMsg) {
		mMsg = pMsg;
	}

	//! Get file name
	void SetFileName(char* pFileName) {
		mFileName = pFileName;
	}

	//! Get file name
	void SetLine(size_t pLineNum) {
		mLine = pLineNum;
	}

private:
	//! Message
	char* mMsg;

	//! File name
	char* mFileName;

	//! Line number
	size_t mLine;
};


class DLLDECL nxeUnsupportedOperationException : public nxeException
{
public:
	//! Constructor
	nxeUnsupportedOperationException(const char* pMsg, const char* pFileName, const size_t& pLine) throw()
		: nxeException(pMsg, pFileName, pLine) {
	}

	//! Destructor
	virtual ~nxeUnsupportedOperationException() throw() {
	}

};


class DLLDECL nxeOutOfMemoryException : public nxeException
{
public:
	//! Constructor
	nxeOutOfMemoryException(const char* pFileName, const size_t& pLine) throw()
		: nxeException("Out of memory", pFileName, pLine) {
	}

	//! Destructor
	virtual ~nxeOutOfMemoryException() throw() {
	}

};


#endif /* #ifndef LnxeEXCEPTION_H_ */
