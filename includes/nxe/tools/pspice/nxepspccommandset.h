/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxepspccommandset.h
  File Description:

  Note(s):

  History:

========================================================================*/


#ifndef LnxePSPCCOMMANDSET_H_
#define LnxePSPCCOMMANDSET_H_

#include "nxe/base/nxedef.h"

class nxePSpcCommand;
class nxePSpcCommandSetIterator;

class DLLDECL nxePSpcCommandSet {
public:
	//! Constructor
	nxePSpcCommandSet(const size_t& pHashSize) {};

	//! Destructor
	virtual ~nxePSpcCommandSet() {};

	//! Add node
	virtual void Append(nxePSpcCommand* pModel) = 0;

	//! Create iterator
	virtual nxePSpcCommandSetIterator* Iterator() const = 0;

	//! Clear
	virtual void Clear(int pDestroy = 0) = 0;

	//! Get length
	virtual const size_t& Length() const = 0;

};

class DLLDECL nxePSpcCommandSetIterator {
public:
	//! Constructor
	nxePSpcCommandSetIterator(const nxePSpcCommandSet& pSet) {};

	//! Destructor
	virtual ~nxePSpcCommandSetIterator() {};

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
	virtual nxePSpcCommand* GetCommand() const = 0;
};

#endif /* #ifndef LnxePSPCCOMMANDSET_H_ */


