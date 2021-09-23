/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: schematicadapter.h
  File Description:

  Note(s):

  History:

========================================================================*/


#include "schematicadapter.h"


SchematicAdapter::SchematicAdapter(nxeCircuit* pCircuit) : mCircuit(pCircuit) {

}

SchematicAdapter::~SchematicAdapter() {

}

void SchematicAdapter::Load(const char* pSpcfile) {
	nxePSpcLoader *spcloader = nxeAPI::GetUtil()->CreatePSpiceLoader();

	try {
		spcloader->Load(pSpcfile);
	}
	catch (nxeException& e) {
		printf(e.what());
		delete spcloader;
		return;
	}

	nxePSpcModel* model = spcloader->GetTopModel();
	if (model == NULL) {
		delete spcloader;
		return;
	}

	mCircuit->SetDescription(spcloader->GetTitle());
	CreateCircuit(model);

	delete spcloader;
}

// Create circuit from spice model
void SchematicAdapter::CreateCircuit(const nxePSpcModel* pModel) {
	// Model
	const nxePSpcModelSet& model_set = pModel->GetModelSet();
	nxePSpcModelSetIterator* model_itr = model_set.Iterator();
	while (++ (*model_itr)) {
		nxePSpcModel* model = model_itr->GetModel();
		CreateCell(model);
	}
	delete model_itr;

	// Subckt
	const nxePSpcModelSet& subckt_set = pModel->GetSubcktSet();
	nxePSpcModelSetIterator* subckt_itr = subckt_set.Iterator();
	while (++ (*subckt_itr)) {
		nxePSpcModel* model = subckt_itr->GetModel();
		CreateCell(model);
	}
	delete subckt_itr;

	// Element
	nxeBlock* topcell = mCircuit->GetTopCell();
	const nxePSpcElementSet& element_set = pModel->GetElementSet();
	nxePSpcElementSetIterator* element_itr = element_set.Iterator();
	while (++ (*element_itr)) {
		nxePSpcElement* obj = element_itr->GetElement();
		nxeModelType model_type = obj->GetModelType();
		switch (model_type) {
		case LnxeModelType_Block:
			CreateBlock(topcell, obj);
			break;

		case LnxeModelType_Device:
			CreateDevice(topcell, obj);
			break;
		}
	}
	delete element_itr;
}

// Create cell
void SchematicAdapter::CreateCell(nxePSpcModel* pModel) {
	nxeCell* topcell = mCircuit->GetTopCell();
	nxeCell* cell = mCircuit->CreateCell(topcell->GetLibName(), pModel->GetName(), topcell->GetViewName(), pModel->GetModelType(), pModel->GetDeviceType());
	const nxeStringList& portnm_list = pModel->GetPortNameList();
	nxeStringListIterator* portnm_itr = portnm_list.Iterator();
	while (++ (*portnm_itr)) {
		cell->CreatePort(portnm_itr->Get());
	}
	delete portnm_itr;
}

// Create device
void SchematicAdapter::CreateDevice(nxeBlock* pBlock, const nxePSpcElement* pElement) {
	nxeDeviceType device_type = pElement->GetDeviceType();
	if (device_type == LnxeDeviceType_None) {
		printf("Unknown device. (%s)\n", pElement->GetName());
		return;
	}

	nxePSpcModel* model = pElement->GetModel();
	if (model == NULL) {
		printf("The device's model is not defined. (%s)\n", pElement->GetName());
		return;
	}

	nxeCell* cell = mCircuit->GetCellByName(pBlock->GetLibName(), model->GetName(), pBlock->GetViewName());
	if (cell == NULL) {
		printf("The device's model is not defined. (%s)\n", pElement->GetName());
		return;
	}

	const char* insname = pElement->GetName();
	const char* netnm1;
	const char* netnm2;
	const char* netnm3;
	const char* netnm4;
	switch (device_type) {
	case LnxeDeviceType_Resistor:
		netnm1 = pElement->GetNodeName(0); // Plus
		netnm2 = pElement->GetNodeName(1); // Minus
		pBlock->AddResistor(insname, cell, netnm1, netnm2);
		break;
	case LnxeDeviceType_Capacitor:
	case LnxeDeviceType_Inductor:
		netnm1 = pElement->GetNodeName(0); // Plus
		netnm2 = pElement->GetNodeName(1); // Minus
		pBlock->AddCapacitor(insname, cell, netnm1, netnm2);
		break;
	case LnxeDeviceType_Diode:
		netnm1 = pElement->GetNodeName(0); // Plus
		netnm2 = pElement->GetNodeName(1); // Minus
		pBlock->AddDiode(insname, cell, netnm1, netnm2);
		break;
	case LnxeDeviceType_NPN:
	case LnxeDeviceType_PNP:
		netnm1 = pElement->GetNodeName(0); // Collector
		netnm2 = pElement->GetNodeName(1); // Base
		netnm3 = pElement->GetNodeName(2); // Emitter
		pBlock->AddBJT(insname, cell, netnm2, netnm3, netnm1);
		break;
	case LnxeDeviceType_PMOS:
	case LnxeDeviceType_NMOS:
		netnm1 = pElement->GetNodeName(0); // Drain
		netnm2 = pElement->GetNodeName(1); // Gate 
		netnm3 = pElement->GetNodeName(2); // Source
		netnm4 = pElement->GetNodeName(3); // Bulk
		pBlock->AddMOS(insname, cell, netnm2, netnm3, netnm1, netnm4);
		break;
	}
}

// Create block
void SchematicAdapter::CreateBlock(nxeBlock* pBlock, const nxePSpcElement* pElement) {
	nxePSpcModel* model = pElement->GetModel();
	const char* model_name = model->GetName();
	const char* lib_name = pBlock->GetLibName();
	const char* view_name = pBlock->GetViewName();
	nxeCell* cell = mCircuit->GetCellByName(lib_name, model_name, view_name);
	if (NULL == cell) {
		printf("The cell '%s/%s/%s' not defined", lib_name, model_name, view_name);
		return;
	}

	const char* inst_name = pElement->GetName();
	nxeInstance* inst = pBlock->CreateInstance(inst_name, cell);

	const nxeStringList& nodenm_list = pElement->GetNodeNameList();
	const nxeStringList& portnm_list = model->GetPortNameList();

	nxeStringListIterator* nodenm_itr = nodenm_list.Iterator();
	nxeStringListIterator* portnm_itr = portnm_list.Iterator();
	while ((++ (*portnm_itr)) && (++ (*nodenm_itr))) {
		const char* portnm = portnm_itr->Get();
		nxePin* pin = inst->CreatePin(portnm);

		const char* nodenm = nodenm_itr->Get();
		nxeNet* net = pBlock->CreateNet(nodenm);

		pin->Connect(net);
	}

	delete nodenm_itr;
	delete portnm_itr;
}


