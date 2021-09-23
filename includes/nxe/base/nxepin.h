/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxepin.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxePIN_H_
#define LnxePIN_H_

#include "nxedef.h"

class nxeNet;
class nxePort;
class nxeInstance;

class DLLDECL nxePin
{
public:
	//! Constructor
	nxePin() {};

	//! Destructor
	virtual ~nxePin() {};

	//! Instance
	virtual nxeInstance* GetInstance() const = 0;

	//! Port
	virtual nxePort* GetPort() const = 0;

	//! Name
	virtual const char* GetName() const = 0;

	//! Get net
	virtual nxeNet* GetNet() const = 0;

	//! Connect
	virtual void Connect(nxeNet* pNet) = 0;

};

#endif /* #ifndef LnxePIN_H_ */
