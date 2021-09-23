/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: sampledef.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef L_SAMPLE_DEF_H_
#define L_SAMPLE_DEF_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nxe/nxeschematic.h"

#define L_USRCMD_TRAINING_SCH_PSPICE	"S"

#define L_USRCMD_SOLVE_CHECKCIRCUIT		"1"
#define L_USRCMD_SOLVE_ANALYZECIRCUIT	"2"

#define L_USRCMD_KHDB_LISTMODEL			"M"

#define L_USRCMD_QUIT "Q"

#define L_CommandHint "\
NextEDA API Version %s.\n\
Copyright (c) 2018 NextEDA Project Team. All rights reserved.\n\
============================================================\n\
Choose a command in following: \n\
	TRAINING\n\
	S: Training schematic\n\
	\n\
	SOLVE PROBLEM\n\
	1: Check and fix circuit\n\
	2: Analyze circuit (developing)\n\
	\n\
	KNOW-HOW DATABASE\n\
	M: List model\n\
	\n\
	Q: Quit\n\
	\n\
Your choose: "

enum UserCommandType {
	L_UserCommand_None = 0,

	// Training command
	L_UserCommand_TrainingSchPSpice = 1,

	// Solve command
	L_UserCommand_SolveCheckCircuit = 2,
	L_UserCommand_AnalyzeCircuit = 3,

	// Know-how Database
	L_UserCommand_KHDBListModel = 4,

	// Quit command
	L_UserCommand_Quit = 10
};


#endif /* #ifndef L_SAMPLE_DEF_H_ */





