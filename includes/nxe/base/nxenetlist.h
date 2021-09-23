/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxenetlist.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeNETLIST_H_
#define LnxeNETLIST_H_


#include "nxedef.h"


class nxeNet;
class nxeNetListIterator;


class DLLDECL nxeNetList
{
public:
	//! Constructor
	nxeNetList() {};

	//! Destructor
	virtual ~nxeNetList() {};

	//! Clear
	virtual void Clear(int pDestroy = 0) = 0;

	//! Append one net
	virtual void Append(nxeNet* pNet) = 0;

	//! Get length
	virtual size_t Length() const = 0;

	//! Create iterator
	virtual nxeNetListIterator* Iterator() const = 0;
	
};


class DLLDECL nxeNetListIterator {
public:
	//! Constructor
	nxeNetListIterator() {};

	//! Destructor
	virtual ~nxeNetListIterator() {};

	//! Reset
	virtual void Reset() = 0;

	/**
	 * \brief Next
	 *
	 * \return 1 Next item existing
	 * \return 0 Last item reached
	 */
	virtual int operator ++() = 0;

	//! Get net
	virtual nxeNet* Get() const = 0;
	
	
};



#endif /* #ifndef LnxeNETLIST_H_ */

