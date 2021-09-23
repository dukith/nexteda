/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: schematiclistener.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef L_SCHEMATICLISTENER_H_
#define L_SCHEMATICLISTENER_H_

#include "sampledef.h"

class SchematicListener : public nxeIFindPatternListener, public nxeICheckCircuitListener {
public:
	//! Constructor
	SchematicListener();

	//! Destructor
	virtual ~SchematicListener();

	//! Append pair
	void OnFoundPattern(const nxeMatchingPattern& pPattern);

	/*!
	 * \brief If circuit is no problem then this event will be activated (Can be multiple times)
	 *
	 * \param pPattern (o) Found matching pattern
	 */
	void OnMatch(const nxeMatchingPattern& pPattern);

	/*!
	 * \brief Append pair
	 *
	 * \param pFixSolution (o) Fix solution
	 */
	void OnSuggestFix(const nxeSchFixSolution& pFixSolution);

	/**
	 * \brief The event activated in case of being not enough data to evaluate input
	 *
	 */
	void OnNotEnoughDataToEvaluate();

	
protected:
	//! Print matching instances
	void PrintMatchingInstances(const nxeInstancePairList* pInsPairList);

};

#endif /* #ifndef L_SCHEMATICLISTENER_H_ */




