/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxepspcloader.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxePSPCLOADER_H_
#define LnxePSPCLOADER_H_

#include "nxe/base/nxedef.h"

class nxePSpcModel;

class DLLDECL nxePSpcLoader
{
public:
	//! Constructor
	nxePSpcLoader() {};

	//! Destructor
	virtual ~nxePSpcLoader() {};

	//! Get lib name
	virtual const char* GetLibName() const = 0;

	//! Get view name
	virtual const char* GetViewName() const = 0;

	//! Set lib name
	virtual void SetLibName(const char* pLibnm) = 0;

	//! Set view name
	virtual void SetViewName(const char* pViewnm) = 0;

	//! Title
	virtual const char* GetTitle() const = 0;

	//! Get top model
	virtual nxePSpcModel* GetTopModel() const = 0;

	/**
	 * \brief Load circuit
	 *
	 * \exception lstdNotEnoughMemoryException
	 * \exception liopIOException
	 * \exception pspcPInvalidFormat
	 */
	virtual void Load(const char* pFilePath) = 0;


};


#endif /* #ifndef LnxePSPCLOADER_H_ */


