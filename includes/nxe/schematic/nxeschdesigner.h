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
class nxeSchFixSolution;
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

	//! Circuit
	virtual const nxeCircuit& GetCircuit() const = 0;

	//! Circuit
	virtual nxeCircuit& GetCircuit() = 0;

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
	 * \brief If circuit is no problem then this event will be activated (Can be multiple times)
	 *
	 * \param pPattern (o) Found matching pattern
	 */
	virtual void OnMatch(const nxeMatchingPattern& pPattern) = 0;

	/*!
	 * \brief Append pair
	 *
	 * \param pFixSolution (o) Fix solution
	 */
	virtual void OnSuggestFix(const nxeSchFixSolution& pFixSolution) = 0;

	/**
	 * \brief The event activated in case of being not enough data to evaluate input
	 * 
	 */
	virtual void OnNotEnoughDataToEvaluate() = 0;

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

