/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxekhmodelbrowser.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeKHMODELBROWSER_H_
#define LnxeKHMODELBROWSER_H_

#include "nxedef.h"

class nxeKHModelIterator;

class DLLDECL nxeKHModelBrowser
{
public:
	//! Constructor
	nxeKHModelBrowser() {};

	//! Destructor
	virtual ~nxeKHModelBrowser() {};

	//! Create iterator
	virtual nxeKHModelIterator* Iterator() const = 0;

};



#endif /* #ifndef LnxeKHMODELBROWSER_H_ */



