/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxesschdesigner.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxesSCHDESIGNER_H_
#define LnxesSCHDESIGNER_H_

#include "nxe/base/nxedef.h"
#include "nxe/base/nxedesigner.h"

class nxeInstance;
class nxeCircuit;
class nxePinPairList;
class nxeMatchingPattern;
class nxeIFindPatternListener;
class nxeICheckCircuitListener;
class nxeIPredictConnectionListener;

class DLLDECL nxeSchDesigner : public nxeDesigner
{
public:
	//! Constructor
	nxeSchDesigner(const char* pCtrlFile) : nxeDesigner(pCtrlFile) {};

	//! Destructor
	virtual ~nxeSchDesigner() {};

	//! Learn
	virtual void LearnShematic() = 0;

	//! Find matching pattern
	virtual void FindPattern(nxeIFindPatternListener* pListener) const = 0;

	/*!
	 * \brief Check circuit
	 *
	 * \ret 0 Have some dubious points
	 *		1 Don't have any dubious points
	 */
	virtual int CheckCircuit(nxeICheckCircuitListener* pListener) const = 0;

	/*!
	 * \brief Predict connection
	 *
	 * \ret 1 Have some suggests
	 *		0 Don't have any suggests
	 */
	virtual int PredictConnection(const nxeInstance* pFromInst
		, const nxeInstance* pToInst, nxeIPredictConnectionListener* pListener) const = 0;

};


class DLLDECL nxeIFindPatternListener
{
public:
	//! Constructor
	nxeIFindPatternListener() {};

	//! Destructor
	virtual ~nxeIFindPatternListener() {};

	//! Append pair
	virtual void OnFoundPattern(const nxeMatchingPattern& pPattern) = 0;
};


class DLLDECL nxeICheckCircuitListener
{
public:
	//! Constructor
	nxeICheckCircuitListener() {};

	//! Destructor
	virtual ~nxeICheckCircuitListener() {};

	/*!
	 * \brief Append pair
	 *
	 * \param pCurrConnList (o) Pairs of pins in current connection that maybe mistake
	 * \param pSuggestConnList (o) Solution to fix mistake in pCurrConnList
	 */
	virtual void OnSuggestFix(const nxePinPairList& pCurrConnList, const nxePinPairList& pSuggestConnList) = 0;
};


class DLLDECL nxeIPredictConnectionListener
{
public:
	//! Constructor
	nxeIPredictConnectionListener() {};

	//! Destructor
	virtual ~nxeIPredictConnectionListener() {};

	/*!
	 * \brief Append pair
	 *
	 * \param pCurrConnList (o) Pairs of pins in current connection that maybe mistake
	 * \param pSuggestConnList (o) Solution to fix mistake in pCurrConnList
	 */
	virtual void OnSuggestConnection(const nxePinPairList& pSuggestConnList) = 0;
};



#endif /* #ifndef LnxesSCHDESIGNER_H_*/

