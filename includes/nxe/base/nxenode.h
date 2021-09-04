/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxenode.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeNODE_H_
#define LnxeNODE_H_

#include "nxedef.h"

class nxeNodeList;
class nxePinEdgeList;

class DLLDECL nxeNode
{
public:
	//! Constructor
	nxeNode() {};

	//! Destructor
	virtual ~nxeNode() {};

	/**
	 * \brief Check this node being astract node or not
	 *
	 * \return	1 Astract node
	 *			0 Not astract node
	 */
	virtual int IsAstractNode() const = 0;

	//! Get subnode list
	virtual const nxeNodeList& GetSubnodeList() const = 0;

	//! Get connection list
	virtual const nxePinEdgeList& GetPinEdgeList() const = 0;
};


#endif /* #ifndef LnxeNODE_H_ */
