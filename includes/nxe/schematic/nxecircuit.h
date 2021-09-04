/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxecircuit.h
  File Description:

  Note(s):
  
  History:

========================================================================*/


#ifndef LnxeCIRCUIT_H_
#define LnxeCIRCUIT_H_

#include "nxe/base/nxedef.h"

class nxeCell;
class nxeBlock;
class nxeDesigner;

class DLLDECL nxeCircuit
{
public:
	//! Constructor
	nxeCircuit() {};

	//! Destructor
	virtual ~nxeCircuit() {};

	/**
	 * \brief Initialize
	 *
	 * \param pLibnm The top cell's library name
	 * \param pModelnm The top cell's model name
	 * \param pViewnm The top cell's view name
	 */
	virtual void Init(const char* pLibnm, const char* pModelnm, const char* pViewnm) = 0;

	//! Set description
	virtual void SetDescription(const char* pDesc) = 0;

	//! Get description
	virtual const char* GetDescription() const = 0;

	//! Get top cell
	virtual const nxeBlock* GetTopCell() const = 0;
	virtual nxeBlock* GetTopCell() = 0;

	//! Create cell
	virtual nxeCell* GetCellByName(const char* pLibnm, const char* pModelnm, const char* pViewnm) const = 0;

	//! Create cell by full name
	virtual nxeCell* GetCellByName(const char* pFullnm) const = 0;

	/**
	 * \brief Create cell
	 *
	 * \exception nxeException Out of memory
	 * \exception nxeException Model refdefined
	 */
	virtual nxeCell* CreateCell(const char* pLibnm, const char* pModelnm, const char* pViewnm,
		const nxeModelType& pMType, const nxeDeviceType& pDType) = 0;

	//! Get designer 
	virtual nxeDesigner& GetDesigner() const = 0;

};

#endif /* #ifndef LnxeCIRCUIT_H_ */



