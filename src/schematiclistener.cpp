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

// If circuit is no problem then this event will be activated (Can be multiple times)
void SchematicListener::OnMatch(const nxeMatchingPattern& pPattern) {
	const char* cellnm = pPattern.GetMatchingCellName();
	printf("Matching cell name: %s\n", cellnm);

	nxeInstancePairList* inst_pair_list;
	pPattern.GetMatchingPairList(&inst_pair_list);
	PrintMatchingInstances(inst_pair_list);
	delete inst_pair_list;
}

// pFixSolution (o) Fix solution
void SchematicListener::OnSuggestFix(const nxeSchFixSolution& pFixSolution) {
	const nxeNGInstanceList& nginst_list = pFixSolution.GetNGInstanceList();
	nxeNGInstanceListIterator* nginst_itr = nginst_list.Iterator();
	while (++(*nginst_itr)) {
		nxeNGInstance* nginst = nginst_itr->Get();
		const nxeNGPinList& ngpin_list = nginst->GetNGPinList();

		if (nginst->IsAppended() == 0) {
			nxeInstance* target_inst = nginst->GetTargetInstance();
			printf("Modify instance: %s (Modified pin: %d)\n", target_inst->GetName(), ngpin_list.Length());
		}
		else {
			printf("Append instance: %s (Modified pin: %d)\n", nginst->GetAppendInstanceName(), ngpin_list.Length());
		}

		nxeNGPinListIterator* ngpin_itr = ngpin_list.Iterator();
		while (++(*ngpin_itr)) {
			nxeNGPin* ngpin = ngpin_itr->Get();
			printf("\tPin %s: ", ngpin->GetPinName());

			nxePin* target_pin = ngpin->GetTargetPin();
			nxeNet* modified_net = ngpin->GetModifiedNet();

			if (target_pin != NULL) {
				const char* netnm = (modified_net != NULL) ? (modified_net->GetName()) : ngpin->GetModifiedNetName();
				nxeNet* curr_net = target_pin->GetNet();
				if (netnm != NULL) {
					printf("%s (Before modify: %s)\n", netnm, ((NULL != curr_net) ? curr_net->GetName() : "(Not connected)"));
				}
			}
			else {
				const char* netnm = (modified_net != NULL) ? (modified_net->GetName()) : ngpin->GetModifiedNetName();
				if (netnm != NULL) {
					printf("%s %s\n", netnm, (modified_net == NULL ? "(Append)" : ""));
				}
			}
		}
		delete ngpin_itr;
	}

	delete nginst_itr;
}

// The event activated in case of being not enough data to evaluate input
void SchematicListener::OnNotEnoughDataToEvaluate() {
	printf("Not enough information to evaluate input circuit\n");
}



