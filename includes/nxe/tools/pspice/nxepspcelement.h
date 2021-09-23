/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxepspcelement.h
  File Description:

  Note(s):

  History:

========================================================================*/


#ifndef LnxePSPCELEMENT_H_
#define LnxePSPCELEMENT_H_

#include "nxe/base/nxedef.h"
#include "nxe/tools/pspice/nxepspcobject.h"

class nxePSpcModel;
class nxeStringList;

class DLLDECL nxePSpcElement : public nxePSpcObject {
public:
	//! Constructor
	nxePSpcElement() {
	}

	//! Destructor
	virtual ~nxePSpcElement() {
	}

	//! Get model
	virtual nxePSpcModel* GetModel() const = 0;

	//! Get model type
	virtual const nxeModelType& GetModelType() const = 0;

	//! Type's letter
	virtual const char& GetElementType() const = 0;

	//! Get device type
	virtual const nxeDeviceType& GetDeviceType() const = 0;

	/**
	 * \brief GetNetName
	 *
	 * \exception lstdInvalidIndexException
	 */
	virtual const char* GetNodeName(const size_t& pIndex = 0) const = 0;

	//! Node name list
	virtual const nxeStringList& GetNodeNameList() const = 0;

};


#endif /* #ifndef LnxePSPCELEMENT_H_ */

