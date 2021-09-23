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

class nxeNet;
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
	virtual nxeInstance* AddMOS(const char* pInsnm, nxeCell* pCell, const char* pGNetnm
		, const char* pSNetnm, const char* pDNetnm, const char* pBNetnm) = 0;

	/**
	 * \brief Add BJT
	 *
	 * \exception lstdNotEnoughMemoryException
	 * \exception latmRedefineException
	 */
	virtual nxeInstance* AddBJT(const char* pInsnm, nxeCell* pCell, const char* pBNetnm
		, const char* pENetnm, const char* pCNetnm) = 0;

	/**
	 * \brief Add Diode
	 *
	 * \exception lstdNotEnoughMemoryException
	 * \exception latmRedefineException
	 */
	virtual nxeInstance* AddDiode(const char* pInsnm, nxeCell* pCell, const char* pPlusNetnm, const char* pMinusNetnm) = 0;

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

	/**
	 * \brief Create new instance
	 *
	 * \exception lstdNotEnoughMemoryException
	 * \exception latmRedefineException
	 */
	virtual nxeInstance* CreateInstance(const char* pInsName, nxeCell* pCell) = 0;

	/**
	 * \brief Create net
	 *
	 * \return Found net
	 */
	virtual nxeNet* CreateNet(const char* pNetnm) = 0;

	/**
	 * \brief Get instance by name
	 *
	 * \return Found instance
	 */
	virtual nxeInstance* GetInstanceByName(const char* pInsnm) const = 0;

	/**
	 * \brief Get net by name
	 *
	 * \return Found net
	 */
	virtual nxeNet* GetNetByName(const char* pNetnm) const = 0;

};

#endif /* #ifndef LnxeBLOCK_H_ */

