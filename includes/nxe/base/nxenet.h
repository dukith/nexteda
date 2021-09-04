/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxenet.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeNET_H_
#define LnxeNET_H_

#include "nxedef.h"

class DLLDECL nxeNet
{
public:
	//! Constructor
	nxeNet(const char* pName) {};

	//! Destructor
	virtual ~nxeNet() {};

	//! Get name
	virtual const char* GetName() const = 0;

};

#endif /* #ifndef LnxeNET_H_ */

