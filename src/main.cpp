/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: main.cpp
  File Description:

  Note(s):

  History:

========================================================================*/


#include "sampledef.h"
#include "schematicadapter.h"
#include "schematiclistener.h"


void GetAppPath(const char* pExecFilePath, char*& pAppPath);
UserCommandType ReadCommand();
void TrainingSchematic(nxeSchDesigner& pDesigner);
void ExecuteQuerySchematic(nxeSchDesigner& pDesigner, SchematicListener& pListner);
void CheckCircuit(nxeSchDesigner& pDesigner, SchematicListener& pListner);
void PredictConnection(nxeSchDesigner& pDesigner, SchematicListener& pListner);
void ConfirmToContinue();

int main(int argc, char ** argv) {
	if (argc < 2) {
		printf("Command syntax error. Please input configuration file.\n");
		return 0;
	}

	char* exec_path = argv[0];
	char* apppath = NULL;
	GetAppPath(exec_path, apppath);

	// Initialize designer
	char* ctrlfile = argv[argc - 1];
	try {
		nxeAPI::Start(apppath, ctrlfile);
	}
	catch (nxeException& e) {
		printf("%s\n", e.what());
		if (apppath != NULL) {
			delete apppath;
		}
		return 0;
	}

	if (apppath != NULL) {
		delete apppath;
		apppath = NULL;
	}

	nxeSchDesigner* designer = nxeAPI::GetSchDesigner();
	SchematicListener listener;

	// Waiting for command
	UserCommandType cmdtype = L_UserCommand_None;
	do {
		cmdtype = ReadCommand();
		try {
			switch (cmdtype) {
			case L_UserCommand_TrainingSchHSpice:
				TrainingSchematic(*designer);
				break;
			case L_UserCommand_TrainingSchDriver:
				break;
			case L_UserCommand_TrainingLayoutDriver:
				break;
			case L_UserCommand_SolvePredictConn:
				PredictConnection(*designer, listener);
				break;
			case L_UserCommand_SolveCheckSCH:
				CheckCircuit(*designer, listener);
				break;
			case L_UserCommand_SolveFindPattern:
				ExecuteQuerySchematic(*designer, listener);
				break;
			case L_UserCommand_SolveGenFpl:
				break;
			case L_UserCommand_SolveDesignPlace:
				break;
			case L_UserCommand_SolveDesignLayout:
				break;
			case L_UserCommand_Quit:
				break;
			}
		}
		catch (nxeException& e) {
			printf("%s\n", e.what());
			ConfirmToContinue();
		}
		if (cmdtype == L_UserCommand_Quit) {
			break;
		}
	} while (1);

	nxeAPI::End();

	return 1;
}

UserCommandType ReadCommand() {
	nxeAPI::GetUtil()->ClearConsole();

	char cmd[10];
	printf(L_CommandHint);
	M_SCANF("%s", cmd, 10);

	nxeUtil* util = nxeAPI::GetUtil();

	char* p_cmd = cmd;
	util->TrimString(cmd, p_cmd);
	util->ToUpper(cmd, p_cmd);

	if (util->CompareStr(cmd, L_USRCMD_TRAINING_SCH_HSPICE) == 0) {
		return L_UserCommand_TrainingSchHSpice;
	}
	else if (util->CompareStr(cmd, L_USRCMD_TRAINING_SCH_DRIVER) == 0) {
		return L_UserCommand_TrainingSchDriver;
	}
	else if (util->CompareStr(cmd, L_USRCMD_TRAINING_LAYOUT_DRIVER) == 0) {
		return L_UserCommand_TrainingLayoutDriver;
	}
	else if (util->CompareStr(cmd, L_USRCMD_SOLVE_PREDICT_CONN) == 0) {
		return L_UserCommand_SolvePredictConn;
	}
	else if (util->CompareStr(cmd, L_USRCMD_SOLVE_CHECK_SCH) == 0) {
		return L_UserCommand_SolveCheckSCH;
	}
	else if (util->CompareStr(cmd, L_USRCMD_SOLVE_FIND_PATTERN) == 0) {
		return L_UserCommand_SolveFindPattern;
	}
	else if (util->CompareStr(cmd, L_USRCMD_SOLVE_GEN_FPL) == 0) {
		return L_UserCommand_SolveGenFpl;
	}
	else if (util->CompareStr(cmd, L_USRCMD_SOLVE_DESGIN_PLACE) == 0) {
		return L_UserCommand_SolveDesignPlace;
	}
	else if (util->CompareStr(cmd, L_USRCMD_SOLVE_DESGIN_LAYOUT) == 0) {
		return L_UserCommand_SolveDesignLayout;
	}
	else if (util->CompareStr(cmd, L_USRCMD_QUIT) == 0) {
		return L_UserCommand_Quit;
	}
	else {
		printf("Unknown command. (%s)", cmd);
		ConfirmToContinue();
	} 

	return L_UserCommand_Quit;
}

void TrainingSchematic(nxeSchDesigner& pDesigner) {
	char buffer[Lnxe_PATH_MAXLEN];

	printf("Input spice file(full path): ");
	M_SCANF("%s", buffer, Lnxe_PATH_MAXLEN);

	// Load spice file
	nxeCircuit& circuit = pDesigner.GetCircuit();
	circuit.Init("lib", "cell", "symbol");
	SchematicAdapter schloader(&circuit);
	schloader.Load(buffer);

	// Learn
	pDesigner.LearnShematic();

	ConfirmToContinue();
}

void ExecuteQuerySchematic(nxeSchDesigner& pDesigner, SchematicListener& pListner) {
	char buffer[Lnxe_PATH_MAXLEN];

	printf("Input spice file(full path): ");
	M_SCANF("%s", buffer, Lnxe_PATH_MAXLEN);

	// Load spice file
	nxeCircuit& circuit = pDesigner.GetCircuit();
	circuit.Init("lib", "cell", "symbol");
	SchematicAdapter schloader(&circuit);
	schloader.Load(buffer);

	// Solve
	pDesigner.FindPattern(&pListner);

	ConfirmToContinue();
}

void PredictConnection(nxeSchDesigner& pDesigner, SchematicListener& pListner) {
	char buffer[Lnxe_PATH_MAXLEN];

	printf("Input spice file(full path): ");
	M_SCANF("%s", buffer, Lnxe_PATH_MAXLEN);

	// Load spice file
	nxeCircuit& circuit = pDesigner.GetCircuit();
	circuit.Init("lib", "cell", "symbol");
	SchematicAdapter schloader(&circuit);
	schloader.Load(buffer);

	// Solve
	pDesigner.PredictConnection(NULL, NULL, &pListner);

	ConfirmToContinue();
}

void CheckCircuit(nxeSchDesigner& pDesigner, SchematicListener& pListner) {
	char buffer[Lnxe_PATH_MAXLEN];

	printf("Input spice file(full path): ");
	M_SCANF("%s", buffer, Lnxe_PATH_MAXLEN);

	// Load spice file
	nxeCircuit& circuit = pDesigner.GetCircuit();
	circuit.Init("lib", "cell", "symbol");
	SchematicAdapter schloader(&circuit);
	schloader.Load(buffer);

	// Solve
	pDesigner.CheckCircuit(&pListner);

	ConfirmToContinue();
}

void ConfirmToContinue() {
	char dummy[Lnxe_PATH_MAXLEN];
	printf("Press any key to continue!");
	fgets(dummy, Lnxe_PATH_MAXLEN, stdin);
	getchar();
}

void GetAppPath(const char* pExecFilePath, char*& pAppPath) {
	const char* chr1 = strrchr(pExecFilePath, '\\');
	const char* chr2 = strrchr(pExecFilePath, '/');
	const char* slash_chr = (chr1 < chr2) ? chr2 : chr1;

	int path_len = (slash_chr - pExecFilePath);
	pAppPath = new char[path_len + 1];

#ifdef L_WINDOWS_OS_
	strncpy_s(pAppPath, path_len + 1, pExecFilePath, path_len);
#else
	strncpy(pAppPath, pExecFilePath, path_len);
#endif
}

