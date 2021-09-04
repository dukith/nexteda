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

#define L_USRCMD_TRAINING_SCH_HSPICE	"S"
#define L_USRCMD_TRAINING_SCH_DRIVER	"E"
#define L_USRCMD_TRAINING_LAYOUT_DRIVER "L"

#define L_USRCMD_SOLVE_PREDICT_CONN		"1"
#define L_USRCMD_SOLVE_CHECK_SCH		"2"
#define L_USRCMD_SOLVE_FIND_PATTERN		"3"
#define L_USRCMD_SOLVE_GEN_FPL			"4"
#define L_USRCMD_SOLVE_DESGIN_PLACE		"5"
#define L_USRCMD_SOLVE_DESGIN_LAYOUT	"6"

#define L_USRCMD_QUIT "Q"

#define L_CommandHint "\
Copyright (c) 2018 NextEDA Project Team. All rights reserved.\n\
Website: http://www.nexteda.com  E-mail: support@nexteda.com\n\
============================================================\n\
Choose a command in following: \n\
	TRAINING\n\
	S: Training schematic\n\
	L: Training layout\n\
	\n\
	SOLVE PROBLEM\n\
	1: Predict connection      -> Circuit autocomplete\n\
	2: Check and fix schematic -> Circuit autofix\n\
	3: Find pattern            -> Find schematic pattern\n\
	4: Generate floorplan\n\
	5: Design layout (only placement)\n\
	6: Design layout (placement and wiring)\n\
	\n\
	Q: Quit\n\
	\n\
Your choose: "

enum UserCommandType {
	L_UserCommand_None = 0,

	// Training command
	L_UserCommand_TrainingSchHSpice = 1,
	L_UserCommand_TrainingSchDriver = 2,
	L_UserCommand_TrainingLayoutDriver = 3,

	// Solve command
	L_UserCommand_SolvePredictConn = 4,
	L_UserCommand_SolveCheckSCH = 5,
	L_UserCommand_SolveFindPattern = 6,
	L_UserCommand_SolveGenFpl = 7,
	L_UserCommand_SolveDesignPlace = 8,
	L_UserCommand_SolveDesignLayout = 9,
	
	// Quit command
	L_UserCommand_Quit = 10
};

#endif /* #ifndef L_SAMPLE_DEF_H_ */





