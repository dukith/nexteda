/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxepinedge.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeNETEDGE_H_
#define LnxeNETEDGE_H_

#include "nxedef.h"

class nxePin;

class DLLDECL nxePinEdge {
public:
	//! Constructor
	nxePinEdge(nxePin* pPin1, nxePin* pPin2) {};

	//! Destructor
	virtual ~nxePinEdge() {};

	//! Pin1 (start)
	virtual nxePin* GetPin1() const = 0;

	//! Pin2 (end)
	virtual nxePin* GetPin2() const = 0;
};

#endif /* #ifndef LnxeNETEDGE_H_ */


