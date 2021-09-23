/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxestringlist.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeSTRINGLIST_H_
#define LnxeSTRINGLIST_H_

#include "nxedef.h"

class nxeStringListIterator;

class DLLDECL nxeStringList
{
public:
	//! Constructor
	nxeStringList() {};

	//! Destructor
	virtual ~nxeStringList() {};

	//! Add node
	virtual void Append(const char* pStr) = 0;

	//! Create iterator
	virtual nxeStringListIterator* Iterator() const = 0;

	//! Clear
	virtual void Clear() = 0;

	//! Get length
	virtual const size_t& Length() const = 0;
};

class DLLDECL nxeStringListIterator {
public:
	//! Constructor
	nxeStringListIterator(const nxeStringList& pList) {};

	//! Destructor
	virtual ~nxeStringListIterator() {};

	//! Reset
	virtual void Reset() = 0;

	/**
	 * \brief Next
	 *
	 * \return 1 Next item existing
	 * \return 0 Last item reached
	 */
	virtual int operator ++() = 0;

	//! Get node
	virtual const char* Get() const = 0;
};


#endif /* #ifndef LnxeSTRINGLIST_H_ */



