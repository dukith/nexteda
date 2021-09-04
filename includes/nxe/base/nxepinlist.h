/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxepinlist.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxePINLIST_H_
#define LnxePINLIST_H_

#include "nxedef.h"

class nxePin;

class DLLDECL nxePinList
{
public:
	//! Constructor
	nxePinList() {};

	//! Destructor
	virtual ~nxePinList() {};

	//! Clear
	virtual void Clear(int pDestroy = 0) = 0;

	//! Append
	virtual void Append(nxePin* pPin) = 0;

	//! Get port by name
	virtual nxePin* GetPinByName(const char* pPinName) const = 0;

	//! Get length
	virtual size_t Length() const = 0;
};

#endif /* #ifndef LnxePINLIST_H_ */
