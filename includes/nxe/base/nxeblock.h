/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxeblock.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeBLOCK_H_
#define LnxeBLOCK_H_

#include "nxedef.h"
#include "nxecell.h"

class nxeInstance;
class nxeDesigner;

class DLLDECL nxeBlock : public nxeCell
{
public:
	//! Constructor
	nxeBlock() {};

	//! Destructor
	virtual ~nxeBlock() {};

	/**
	 * \brief Add mos
	 *
	 * \exception lstdNotEnoughMemoryException
	 * \exception latmRedefineException
	 */
	virtual nxeInstance* AddMOS(const char* pInsnm, nxeCell* pCell, const char* pGNetnm,
		const char* pSNetnm, const char* pDNetnm, const char* pBNetnm) = 0;

	/**
	 * \brief Add mos
	 *
	 * \exception lstdNotEnoughMemoryException
	 * \exception latmRedefineException
	 */
	virtual nxeInstance* AddResistor(const char* pInsnm, nxeCell* pCell, const char* pPlusNetnm, const char* pMinusNetnm) = 0;

	/**
	 * \brief Add capacitor
	 *
	 * \exception lstdNotEnoughMemoryException
	 * \exception latmRedefineException
	 */
	virtual nxeInstance* AddCapacitor(const char* pInsnm, nxeCell* pCell, const char* pPlusNetnm, const char* pMinusNetnm) = 0;

};

#endif /* #ifndef LnxeBLOCK_H_ */

