/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxepspccommand.h
  File Description:

  Note(s):

  History:

========================================================================*/


#ifndef LnxePSPCCOMMAND_H_
#define LnxePSPCCOMMAND_H_

#include "nxe/base/nxedef.h"
#include "nxe/tools/pspice/nxepspcobject.h"

class DLLDECL nxePSpcCommand : public nxePSpcObject {
public:
	//! Constructor
	nxePSpcCommand() {
	}

	//! Destructor
	virtual ~nxePSpcCommand() {
	}

};


#endif /* #ifndef LnxePSPCCOMMAND_H_ */

