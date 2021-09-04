/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxestringset.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeSTRINGSET_H_
#define LnxeSTRINGSET_H_

#include "nxedef.h"

class nxeStringSetIterator;

class DLLDECL nxeStringSet
{
public:
	//! Constructor
	nxeStringSet(const size_t& pHashSize) {};

	//! Destructor
	virtual ~nxeStringSet() {};

	//! Add node
	virtual void Append(const char* pStr) = 0;

	//! Create iterator
	virtual nxeStringSetIterator* Iterator() const = 0;

	//! Clear
	virtual void Clear() = 0;

	//! Get length
	virtual const size_t& Length() const = 0;
};

class DLLDECL nxeStringSetIterator {
public:
	//! Constructor
	nxeStringSetIterator(const nxeStringSet& pList) {};

	//! Destructor
	virtual ~nxeStringSetIterator() {};

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


#endif /* #ifndef LnxeSTRINGSET_H_ */
