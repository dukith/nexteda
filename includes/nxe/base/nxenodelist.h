/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxenodelist.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeNODELIST_H_
#define LnxeNODELIST_H_

#include "nxedef.h"

class nxeNode;
class nxeNodeListIterator;

class DLLDECL nxeNodeList
{
public:
	//! Constructor
	nxeNodeList() {};

	//! Destructor
	virtual ~nxeNodeList() {};

	//! Add node
	virtual void Append(nxeNode* pNode) = 0;

	//! Create iterator
	virtual nxeNodeListIterator* Iterator() const = 0;

	//! Clear
	virtual void Clear(int pDestroy = 0) = 0;

	//! Get length
	virtual size_t Length() const = 0;
};

class DLLDECL nxeNodeListIterator {
public:
	//! Constructor
	nxeNodeListIterator(const nxeNodeList& pList) {};

	//! Destructor
	virtual ~nxeNodeListIterator() {};

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
	virtual nxeNode* GetNode() const = 0;
};


#endif /* #ifndef LnxeNODELIST_H_ */
