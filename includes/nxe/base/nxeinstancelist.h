/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxeinstancelist.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeINSTANCELIST_H_
#define LnxeINSTANCELIST_H_

#include "nxedef.h"


class nxeInstance;
class nxeInstanceListIterator;


class DLLDECL nxeInstanceList
{
public:
	//! Constructor
	nxeInstanceList() {};

	//! Destructor
	virtual ~nxeInstanceList() {};

	//! Clear
	virtual void Clear(int pDestroy = 0) = 0;

	//! Append one instance
	virtual void Append(nxeInstance* pIns) = 0;

	//! Get length
	virtual size_t Length() const = 0;

	//! Create iterator
	virtual nxeInstanceListIterator* Iterator() const = 0;
	
};


class DLLDECL nxeInstanceListIterator {
public:
	//! Constructor
	nxeInstanceListIterator() {};

	//! Destructor
	virtual ~nxeInstanceListIterator() {};

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
	virtual nxeInstance* Get() const = 0;
	
	
};



#endif /* #ifndef LnxeINSTANCELIST_H_ */

