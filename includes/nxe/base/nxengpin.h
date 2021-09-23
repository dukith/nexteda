/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxengpin.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeNGPIN_H_
#define LnxeNGPIN_H_

#include "nxedef.h"


class nxeNet;
class nxePin;
class nxeNGInstance;
class nxeNGPinListIterator;


/**
 * \brief NG (Not good) pin. This pin should be fixed.
 */
class DLLDECL nxeNGPin
{
public:
	//! Constructor
	nxeNGPin() {};

	//! Destructor
	virtual ~nxeNGPin() {};

	/**
	 * \brief Compare two NG pins
	 *
	 * \return 1 If this == pSrc
	 * \return 0 If else
	 */
	virtual int operator == (const nxeNGPin& pSrc) const = 0;

	//! Instance
	virtual nxeNGInstance* GetNGInstance() const = 0;

	/**
	 * \brief Get pin should be fixed.
	 */
 	virtual nxePin* GetTargetPin() const = 0;

	/**
	 * \brief Get pin name
	 *
	 */
	virtual const char* GetPinName() const = 0;

	/**
	 * \brief Get net that this pin should be connected
	 *
	 */
	virtual nxeNet* GetModifiedNet() const = 0;

	/**
	 * \brief Modified net name (this name generated in taget netlist's context)
	 *
	 */
	virtual const char* GetModifiedNetName() const = 0;
	

};



class DLLDECL nxeNGPinList
{
public:
	//! Constructor
	nxeNGPinList() {};

	//! Destructor
	virtual ~nxeNGPinList() {};

	//! Clear
	virtual void Clear(int pDestroy = 0) = 0;

	//! Append
	virtual void Append(nxeNGPin* pPin) = 0;

	//! Get length
	virtual size_t Length() const = 0;

	//! Create iterator
	virtual nxeNGPinListIterator* Iterator() const = 0;

};



class DLLDECL nxeNGPinListIterator {
public:
	//! Constructor
	nxeNGPinListIterator() {};

	//! Destructor
	virtual ~nxeNGPinListIterator() {};

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
	virtual nxeNGPin* Get() const = 0;
	
	
};



#endif /* #ifndef LnxeNGPIN_H_ */
