/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxeinstance.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeINSTANCE_H_
#define LnxeINSTANCE_H_

#include "nxedef.h"

class nxePin;
class nxeCell;
class nxeBlock;

class DLLDECL nxeInstance
{
public:
	//! Constructor
	nxeInstance(nxeBlock* pBlock, nxeCell* pCell, const char* pInsName) {};

	//! Destructor
	virtual ~nxeInstance() {};

	/**
	 * \brief Compare two instances
	 *
	 * \return 1 If this == pSrc
	 * \return 0 If else
	 */
	virtual int operator == (const nxeInstance& pSrc) const = 0;

	//! Block
	virtual nxeBlock* GetBlock() const = 0;

	//! Cell
	virtual nxeCell* GetCell() const = 0;

	//! Instance's name
	virtual const char* GetName() const = 0;

	//! Get pin by name
	virtual nxePin* CreatePin(const char* pPinName) = 0;

	//! Get pin by name
	virtual nxePin* GetPinByName(const char* pPinName) = 0;

};


#endif /* #ifndef LnxeINSTANCE_H_ */

