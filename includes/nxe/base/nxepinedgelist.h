/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxepinedgelist.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeNETEDGELIST_H_
#define LnxeNETEDGELIST_H_

#include "nxedef.h"

class nxePinEdge;
class nxePinEdgeListIterator;

class DLLDECL nxePinEdgeList
{
public:
	//! Constructor
	nxePinEdgeList() {};

	//! Destructor
	virtual ~nxePinEdgeList() {};

	//! Clear
	virtual void Clear(int pDestroy = 0) = 0;

	//! Get length
	virtual size_t Length() const = 0;

	/**
	 * \brief Create iterator
	 *
	 * 
	 */
	virtual nxePinEdgeListIterator* Iterator() const = 0;
};

class DLLDECL nxePinEdgeListIterator {
public:
	//! Constructor
	nxePinEdgeListIterator(const nxePinEdgeList& pList) {};

	//! Destructor
	virtual ~nxePinEdgeListIterator() {};

	//! Reset
	virtual void Reset() = 0;

	/**
	 * \brief Next
	 *
	 * \return 1 Next item existing
	 * \return 0 Last item reached
	 */
	virtual int operator ++() = 0;

	//! Get next edge
	virtual nxePinEdge* GetPinEdge() const = 0;
};

#endif /* #ifndef LnxeNETEDGELIST_H_ */


