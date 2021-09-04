/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxepspcelementset.h
  File Description:

  Note(s):

  History:

========================================================================*/


#ifndef LnxePSPCELEMENTSET_H_
#define LnxePSPCELEMENTSET_H_

#include "nxe/base/nxedef.h"
#include "nxe/tools/pspice/nxepspcobject.h"

class nxePSpcElement;
class nxePSpcElementSetIterator;

class DLLDECL nxePSpcElementSet {
public:
	//! Constructor
	nxePSpcElementSet(const size_t& pHashSize) {};

	//! Destructor
	virtual ~nxePSpcElementSet() {};

	//! Add node
	virtual void Append(nxePSpcElement* pModel) = 0;

	//! Create iterator
	virtual nxePSpcElementSetIterator* Iterator() const = 0;

	//! Clear
	virtual void Clear(int pDestroy = 0) = 0;

	//! Get length
	virtual const size_t& Length() const = 0;

};

class DLLDECL nxePSpcElementSetIterator {
public:
	//! Constructor
	nxePSpcElementSetIterator(const nxePSpcElementSet& pSet) {};

	//! Destructor
	virtual ~nxePSpcElementSetIterator() {};

	//! Reset
	virtual void Reset() = 0;

	/**
	 * \brief Next
	 *
	 * \return 1 Next item existing
	 * \return 0 Last item reached
	 */
	virtual int operator ++() = 0;

	//! Get node
	virtual nxePSpcElement* GetElement() const = 0;
};

#endif /* #ifndef LnxePSPCELEMENTSET_H_ */


