/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxepspcmodelset.h
  File Description:

  Note(s):

  History:

========================================================================*/


#ifndef LnxePSPCMODELSET_H_
#define LnxePSPCMODELSET_H_

#include "nxe/base/nxedef.h"
#include "nxe/tools/pspice/nxepspcobject.h"

class nxePSpcModel;
class nxePSpcModelSetIterator;

class DLLDECL nxePSpcModelSet {
public:
	//! Constructor
	nxePSpcModelSet(const size_t& pHashSize) {};

	//! Destructor
	virtual ~nxePSpcModelSet() {};

	//! Add node
	virtual void Append(nxePSpcModel* pModel) = 0;

	//! Add node
	virtual nxePSpcModel* Find(const nxePSpcModel* pModel) const = 0;

	//! Create iterator
	virtual nxePSpcModelSetIterator* Iterator() const = 0;

	//! Clear
	virtual void Clear(int pDestroy = 0) = 0;

	//! Get length
	virtual const size_t& Length() const = 0;

};

class DLLDECL nxePSpcModelSetIterator {
public:
	//! Constructor
	nxePSpcModelSetIterator(const nxePSpcModelSet& pSet) {};

	//! Destructor
	virtual ~nxePSpcModelSetIterator() {};

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
	virtual nxePSpcModel* GetModel() const = 0;
};

#endif /* #ifndef LnxePSPCMODELSET_H_ */


