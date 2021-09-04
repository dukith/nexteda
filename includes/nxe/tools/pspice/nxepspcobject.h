/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxepspcobject.h
  File Description:

  Note(s):

  History:

========================================================================*/


#ifndef LnxePSPCOBJECT_H_
#define LnxePSPCOBJECT_H_

#include "nxe/base/nxedef.h"

class DLLDECL nxePSpcObject {
public:
	//! Constructor
	nxePSpcObject() {};

	//! Destructor
	virtual ~nxePSpcObject() {};

	//! Is element
	virtual int IsElement() const = 0;

	//! Is model
	virtual int IsModel() const = 0;

	//! Is command
	virtual int IsCommand() const = 0;

	//! Get name
	virtual const char* GetName() const = 0;

};


#endif /* #ifndef LnxePSPCOBJECT_H_ */

