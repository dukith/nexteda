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


UserCommandType ReadCommand();
void TrainingSchematic(nxeSchDesigner& pDesigner);
void AnalyzeCircuit(nxeSchDesigner& pDesigner, SchematicListener& pListner);
void CheckCircuit(nxeSchDesigner& pDesigner, SchematicListener& pListner);
void ListModel(nxeSchDesigner& pDesigner);
void ConfirmToContinue();

int main(int argc, char ** argv) {
	if (argc < 2) {
		printf("Command syntax error. Please input configuration file.\n");
		return 0;
	}

	// Initialize designer
	char* ctrlfile = argv[argc - 1];
	try {
		printf("Initializing...\n");
		nxeAPI::Start(ctrlfile);
	}
	catch (nxeException& e) {
		printf("%s\n", e.what());
		return 0;
	}

	nxeSchDesigner* designer = nxeAPI::GetSchDesigner();
	SchematicListener listener;

	// Waiting for command
	UserCommandType cmdtype = L_UserCommand_None;
	do {
		cmdtype = ReadCommand();
		try {
			switch (cmdtype) {
			case L_UserCommand_TrainingSchPSpice:
				TrainingSchematic(*designer);
				break;
			case L_UserCommand_SolveCheckCircuit:
				CheckCircuit(*designer, listener);
				break;
			case L_UserCommand_AnalyzeCircuit:
				AnalyzeCircuit(*designer, listener);
				break;
			case L_UserCommand_KHDBListModel:
				ListModel(*designer);
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
	printf(L_CommandHint, nxeAPI::GetVersionText());
	fgets(cmd, 10, stdin);

	nxeUtil* util = nxeAPI::GetUtil();

	util->TrimString(cmd);
	util->ToUpper(cmd);

	if (util->CompareStr(cmd, L_USRCMD_TRAINING_SCH_PSPICE) == 0) {
		return L_UserCommand_TrainingSchPSpice;
	}
	else if (util->CompareStr(cmd, L_USRCMD_SOLVE_CHECKCIRCUIT) == 0) {
		return L_UserCommand_SolveCheckCircuit;
	}
	else if (util->CompareStr(cmd, L_USRCMD_SOLVE_ANALYZECIRCUIT) == 0) {
		return L_UserCommand_AnalyzeCircuit;
	}
	else if (util->CompareStr(cmd, L_USRCMD_KHDB_LISTMODEL) == 0) {
		return L_UserCommand_KHDBListModel;
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
	nxeUtil* util = nxeAPI::GetUtil();

	char filepath[Lnxe_PATH_MAXLEN];
	printf("Enter netlist file(PSpice): ");
	fgets(filepath, Lnxe_PATH_MAXLEN, stdin);
	util->TrimString(filepath);

	char libnm[Lnxe_PATH_MAXLEN];
	printf("Enter library name (Optional. Default=lib): ");
	fgets(libnm, Lnxe_PATH_MAXLEN, stdin);
	util->TrimString(libnm);
	if (M_STRLEN(libnm) == 0) {
		M_MEMCPY(libnm, "lib", 3);
		libnm[3] = '\0';
	}

	char cellnm[Lnxe_PATH_MAXLEN];
	while (1) {
		printf("Enter cell name (Required): ");
		fgets(cellnm, Lnxe_PATH_MAXLEN, stdin);
		util->TrimString(cellnm);
		if (M_STRLEN(cellnm) > 0) {
			break;
		}
	}

	char viewnm[Lnxe_PATH_MAXLEN];
	printf("Enter view name (Optional. Default=symbol): ");
	fgets(viewnm, Lnxe_PATH_MAXLEN, stdin);
	util->TrimString(viewnm);
	if (M_STRLEN(viewnm) == 0) {
		M_MEMCPY(viewnm, "symbol", 6);
		viewnm[6] = '\0';
	}

	// Load spice file
	nxeCircuit& circuit = pDesigner.GetCircuit();
	circuit.Init(libnm, cellnm, viewnm);
	SchematicAdapter schloader(&circuit);
	schloader.Load(filepath);

	// Learn
	printf("Executing....\n");
	pDesigner.LearnShematic();

	ConfirmToContinue();
}

void AnalyzeCircuit(nxeSchDesigner& pDesigner, SchematicListener& pListner) {
	nxeUtil* util = nxeAPI::GetUtil();

	char filepath[Lnxe_PATH_MAXLEN];
	printf("Enter netlist file(PSpice): ");
	fgets(filepath, Lnxe_PATH_MAXLEN, stdin);
	util->TrimString(filepath);

	char libnm[Lnxe_PATH_MAXLEN];
	printf("Enter library name (Optional. Default=lib): ");
	fgets(libnm, Lnxe_PATH_MAXLEN, stdin);
	util->TrimString(libnm);
	if (M_STRLEN(libnm) == 0) {
		M_MEMCPY(libnm, "lib", 3);
		libnm[3] = '\0';
	}

	char cellnm[Lnxe_PATH_MAXLEN];
	while (1) {
		printf("Enter cell name (Required): ");
		fgets(cellnm, Lnxe_PATH_MAXLEN, stdin);
		util->TrimString(cellnm);
		if (M_STRLEN(cellnm) > 0) {
			break;
		}
	}

	char viewnm[Lnxe_PATH_MAXLEN];
	printf("Enter view name (Optional. Default=symbol): ");
	fgets(viewnm, Lnxe_PATH_MAXLEN, stdin);
	util->TrimString(viewnm);
	if (M_STRLEN(viewnm) == 0) {
		M_MEMCPY(viewnm, "symbol", 6);
		viewnm[6] = '\0';
	}

	// Load spice file
	nxeCircuit& circuit = pDesigner.GetCircuit();
	circuit.Init(libnm, cellnm, viewnm);
	SchematicAdapter schloader(&circuit);
	schloader.Load(filepath);

	// Solve
	printf("Executing....\n");
	pDesigner.FindPattern(&pListner);

	ConfirmToContinue();
}

void CheckCircuit(nxeSchDesigner& pDesigner, SchematicListener& pListner) {
	nxeUtil* util = nxeAPI::GetUtil();

	char filepath[Lnxe_PATH_MAXLEN];
	printf("Enter netlist file(PSpice): ");
	fgets(filepath, Lnxe_PATH_MAXLEN, stdin);
	util->TrimString(filepath);

	// Load spice file
	nxeCircuit& circuit = pDesigner.GetCircuit();
	circuit.Init("lib", "cell", "symbol");
	SchematicAdapter schloader(&circuit);
	schloader.Load(filepath);

	// Solve
	printf("Executing....\n");
	pDesigner.CheckCircuit(&pListner);

	ConfirmToContinue();
}

void ListModel(nxeSchDesigner& pDesigner) {
	printf("No.\tModel name\t\t\tType\t\t\tDescription\n");

	nxeKHModelBrowser& model_browser = pDesigner.GetKHModelBrowser();
	nxeKHModelIterator* model_itr = model_browser.Iterator();
	int cnt = 0;
	while (++(*model_itr)) {
		const nxeKHModel* model = model_itr->Get();
		const char* model_name = model->GetName();
		const char* type_name = (model->GetType() == LnxeKHModelType_DefinedPattern) ? "Defined-Pattern" : "Cell";
		const char* desc = model->GetDescription();
		printf("%d\t%.15s\t\t\t%.15s\t\t%.40s\n", (++ cnt), model_name, type_name, desc);
	}

	ConfirmToContinue();
}

void ConfirmToContinue() {
	char dummy[Lnxe_PATH_MAXLEN];
	printf("Press any key to continue!");
	fgets(dummy, Lnxe_PATH_MAXLEN, stdin);
}

