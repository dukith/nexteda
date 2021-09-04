/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxeport.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxePORT_H_
#define LnxePORT_H_

#include "nxedef.h"

class nxeCell;

class DLLDECL nxePort
{
public:
	//! Constructor
	nxePort(nxeCell* pCell, const char* pName) {};

	//! Destructor
	virtual ~nxePort() {};

	//! Cell
	virtual nxeCell* GetCell() const = 0;

	//! Name
	virtual const char* GetName() const = 0;
};

#endif /* #ifndef LnxePORT_H_ */
