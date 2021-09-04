/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: schematiclistener.h
  File Description:

  Note(s):

  History:

========================================================================*/


#include "schematiclistener.h"


SchematicListener::SchematicListener() {

}

SchematicListener::~SchematicListener() {

}

// Append pair
void SchematicListener::OnFoundPattern(const nxeMatchingPattern& pPattern) {
	const char* cellnm = pPattern.GetMatchingCellName();
	printf("Matching cell name: %s\n", cellnm);

	nxeInstancePairList* inst_pair_list;
	pPattern.GetMatchingPairList(&inst_pair_list);
	PrintMatchingInstances(inst_pair_list);
	delete inst_pair_list;
}

// Print matching instances
void SchematicListener::PrintMatchingInstances(const nxeInstancePairList* pInsPairList) {
	nxeInstancePairListIterator* itr = pInsPairList->Iterator();
	while (++(*itr)) {
		nxeInstance* inst1 = itr->GetInstance1();
		nxeInstance* inst2 = itr->GetInstance2();
		printf("%s <-> %s\n", inst1->GetName(), inst2->GetName());
	}
	delete itr;
}

// Append pair
void SchematicListener::OnSuggestFix(const nxePinPairList& pCurrConnList, const nxePinPairList& pSuggestConnList) {

}

// Append pair
void SchematicListener::OnSuggestConnection(const nxePinPairList& pSuggestConnList) {
}


