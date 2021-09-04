/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxematchingpattern.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeMATCHINGPATTERN_H_
#define LnxeMATCHINGPATTERN_H_

#include "nxedef.h"

class nxePin;
class nxeNet;
class nxeInstance;
class nxePinPairList;
class nxeNetPairList;
class nxeInstancePairList;
class nxePinPairListIterator;
class nxeNetPairListIterator;
class nxeInstancePairListIterator;

class DLLDECL nxeMatchingPattern
{
public:
	//! Constructor
	nxeMatchingPattern() {};

	//! Destructor
	virtual ~nxeMatchingPattern() {};

	/**
	 * \brief Get matching cell name
	 *
	 */
	virtual const char* GetMatchingCellName() const = 0;

	/**
	 * \brief Get matching pair list
	 */
	virtual void GetMatchingPairList(nxeInstancePairList** pInstPairList = NULL
		, nxeNetPairList** pNetPairList = NULL, nxePinPairList** pPinPairList = NULL) const = 0;
};


class DLLDECL nxeInstancePairList
{
public:
	//! Constructor
	nxeInstancePairList() {};

	//! Destructor
	virtual ~nxeInstancePairList() {};

	//! Append pair
	virtual void AppendPair(nxeInstance* pInst1, nxeInstance* pInst2) = 0;

	//! Create iterator
	virtual nxeInstancePairListIterator* Iterator() const = 0;

};

class DLLDECL nxeInstancePairListIterator {
public:
	//! Constructor
	nxeInstancePairListIterator(const nxeInstancePairList& pList) {};

	//! Destructor
	virtual ~nxeInstancePairListIterator() {};

	//! Reset
	virtual void Reset() = 0;

	/**
	 * \brief Next
	 *
	 * \return 1 Next item existing
	 * \return 0 Last item reached
	 */
	virtual int operator ++() = 0;

	//! Get instance
	virtual nxeInstance* GetInstance1() const = 0;

	//! Get matching instance
	virtual nxeInstance* GetInstance2() const = 0;

};


class DLLDECL nxeNetPairList
{
public:
	//! Constructor
	nxeNetPairList() {};

	//! Destructor
	virtual ~nxeNetPairList() {};

	//! Create iterator
	virtual nxeNetPairListIterator* Iterator() const = 0;

};

class DLLDECL nxeNetPairListIterator {
public:
	//! Constructor
	nxeNetPairListIterator(const nxeNetPairList& pList) {};

	//! Destructor
	virtual ~nxeNetPairListIterator() {};

	//! Reset
	virtual void Reset() = 0;

	/**
	 * \brief Next
	 *
	 * \return 1 Next item existing
	 * \return 0 Last item reached
	 */
	virtual int operator ++() = 0;

	//! Get net
	virtual nxeNet* GetNet1() const = 0;

	//! Get matching net
	virtual nxeNet* GetNet2() const = 0;


};

class DLLDECL nxePinPairList
{
public:
	//! Constructor
	nxePinPairList() {};

	//! Destructor
	virtual ~nxePinPairList() {};

	//! Create iterator
	virtual nxePinPairListIterator* Iterator() const = 0;

};


class DLLDECL nxePinPairListIterator {
public:
	//! Constructor
	nxePinPairListIterator(const nxePinPairList& pList) {};

	//! Destructor
	virtual ~nxePinPairListIterator() {};

	//! Reset
	virtual void Reset() = 0;

	/**
	 * \brief Next
	 *
	 * \return 1 Next item existing
	 * \return 0 Last item reached
	 */
	virtual int operator ++() = 0;

	//! Get instance
	virtual nxePin* GetPin1() const = 0;

	//! Get matching instance
	virtual nxePin* GetPin2() const = 0;


};


#endif /* #ifndef LnxeMATCHINGPATTERN_H_ */
