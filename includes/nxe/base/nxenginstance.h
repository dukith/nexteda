/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxenginstance.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeNGINSTANCE_H_
#define LnxeNGINSTANCE_H_

#include "nxedef.h"


class nxeInstance;
class nxeNGPin;
class nxeNGPinList;
class nxeNGInstanceListIterator;

/**
 * \brief NG (Not good) instance. This instance should be modified.
 */
class DLLDECL nxeNGInstance
{
public:
	//! Constructor
	nxeNGInstance() {};

	//! Destructor
	virtual ~nxeNGInstance() {};

	/**
	 * \brief Compare two instances 
	 * 
	 * \return 1 If this == pSrc
	 * \return 0 If else
	 */
	virtual int operator == (const nxeNGInstance& pSrc) const = 0;

	/**
	 * \brief Check that this instance is appended or not
	 *
	 * If instance pin is appended then there is not current net
	 * \ret 0 If this instance is existing
	 * \ret 1 Else
	 */
	virtual int IsAppended() const = 0;

	/**
	 * \brief Get target instance  
	 */
	virtual nxeInstance* GetTargetInstance() const = 0;

	/**
	 * \brief Get appended instance name
	 *
	 * This name generated automatically in checked circuit's context
	 */
	virtual const char* GetAppendInstanceName() const = 0;

	/**
	 * \brief Get NG pins
	 */
	virtual const nxeNGPinList& GetNGPinList() const = 0;
	
};


class DLLDECL nxeNGInstanceList
{
public:
	//! Constructor
	nxeNGInstanceList() {};

	//! Destructor
	virtual ~nxeNGInstanceList() {};

	//! Clear
	virtual void Clear(int pDestroy = 0) = 0;

	//! Append
	virtual void Append(nxeNGInstance* pPin) = 0;

	//! Get length
	virtual size_t Length() const = 0;

	//! Create iterator
	virtual nxeNGInstanceListIterator* Iterator() const = 0;

};



class DLLDECL nxeNGInstanceListIterator {
public:
	//! Constructor
	nxeNGInstanceListIterator() {};

	//! Destructor
	virtual ~nxeNGInstanceListIterator() {};

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
	virtual nxeNGInstance* Get() const = 0;
	
	
};



#endif /* #ifndef LnxeNGINSTANCE_H_ */

