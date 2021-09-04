/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxeportlist.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxePORTLIST_H_
#define LnxePORTLIST_H_

#include "nxedef.h"

class nxePort;

class DLLDECL nxePortList
{
public:
	//! Constructor
	nxePortList() {};

	//! Destructor
	virtual ~nxePortList() {};

	//! Get port by name
	virtual nxePort* GetPortByName(const char* pPortName) const = 0;

	//! Append 
	virtual void Append(nxePort* pPort) = 0;

	//! Clear
	virtual void Clear(int pDestroy = 0) = 0;

	//! Get length
	virtual size_t Length() const = 0;
};

#endif /* #ifndef LnxePORTLIST_H_ */
