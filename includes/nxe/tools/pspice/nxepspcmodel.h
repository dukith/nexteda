/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxepspcmodel.h
  File Description:

  Note(s):

  History:

========================================================================*/


#ifndef LnxePSPCMODEL_H_
#define LnxePSPCMODEL_H_

#include "nxe/base/nxedef.h"
#include "nxe/tools/pspice/nxepspcobject.h"

class nxeStringList;
class nxePSpcModelSet;
class nxePSpcElementSet;
class nxePSpcCommandSet;

class DLLDECL nxePSpcModel : public nxePSpcObject {
public:
	//! Constructor
	nxePSpcModel() {};

	//! Destructor
	virtual ~nxePSpcModel() {};

	//! Get model type
	virtual const nxeModelType& GetModelType() const = 0;

	//! Get device type
	virtual const nxeDeviceType& GetDeviceType() const = 0;

	//! Port list
	virtual const nxeStringList& GetPortNameList() const = 0;

	//! Elements list
	virtual const nxePSpcElementSet& GetElementSet() const = 0;

	//! Models list
	virtual const nxePSpcModelSet& GetModelSet() const = 0;

	//! Elements list
	virtual const nxePSpcCommandSet& GetCommandList() const = 0;

	//! Subckt list
	virtual const nxePSpcModelSet& GetSubcktSet() const = 0;

};



#endif /* #ifndef LnxePSPCMODEL_H_ */

