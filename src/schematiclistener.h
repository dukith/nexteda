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

class SchematicListener : public nxeIFindPatternListener, public nxeICheckCircuitListener, public nxeIPredictConnectionListener {
public:
	//! Constructor
	SchematicListener();

	//! Destructor
	virtual ~SchematicListener();

	//! Append pair
	void OnFoundPattern(const nxeMatchingPattern& pPattern);

	/*!
	 * \brief Append pair
	 *
	 * \param pCurrConnList (o) Pairs of pins in current connection that maybe mistake
	 * \param pSuggestConnList (o) Solution to fix mistake in pCurrConnList
	 */
	void OnSuggestFix(const nxePinPairList& pCurrConnList, const nxePinPairList& pSuggestConnList);
	
	/*!
	 * \brief Append pair
	 *
	 * \param pCurrConnList (o) Pairs of pins in current connection that maybe mistake
	 * \param pSuggestConnList (o) Solution to fix mistake in pCurrConnList
	 */
	void OnSuggestConnection(const nxePinPairList& pSuggestConnList);
	
protected:
	//! Print matching instances
	void PrintMatchingInstances(const nxeInstancePairList* pInsPairList);

};

#endif /* #ifndef L_SCHEMATICLISTENER_H_ */




