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
	const nxePSpcElementSet& element_set = pModel->GetElementSet();
	nxePSpcElementSetIterator* element_itr = element_set.Iterator();
	while (++ (*element_itr)) {
		nxePSpcElement* obj = element_itr->GetElement();
		nxeModelType model_type = obj->GetModelType();
		switch (model_type) {
		case LnxeModelType_Block:
			CreateBlock(obj);
			break;

		case LnxeModelType_Device:
			CreateDevice(obj);
			break;
		}
	}
	delete element_itr;
}

// Create cell
void SchematicAdapter::CreateCell(nxePSpcModel* pModel) {
	nxeCell* topcell = mCircuit->GetTopCell();
	nxeCell* cell = mCircuit->CreateCell(topcell->GetLibName(), pModel->GetName(), topcell->GetViewName(), pModel->GetModelType(), pModel->GetDeviceType());
	const nxeStringSet& portnm_set = pModel->GetPortNameSet();
	nxeStringSetIterator* portnm_itr = portnm_set.Iterator();
	while (++ (*portnm_itr)) {
		cell->CreatePort(portnm_itr->Get());
	}
	delete portnm_itr;
}

// Create device
void SchematicAdapter::CreateDevice(const nxePSpcElement* pElement) {
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

	nxeBlock* topcell = mCircuit->GetTopCell();
	nxeCell* cell = mCircuit->GetCellByName(topcell->GetLibName(), model->GetName(), topcell->GetViewName());
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
		netnm1 = pElement->GetNodeName(0);
		netnm2 = pElement->GetNodeName(1);
		topcell->AddResistor(insname, cell, netnm1, netnm2);
		break;
	case LnxeDeviceType_Capacitor:
	case LnxeDeviceType_Inductor:
		netnm1 = pElement->GetNodeName(0);
		netnm2 = pElement->GetNodeName(1);
		topcell->AddCapacitor(insname, cell, netnm1, netnm2);
		break;
	case LnxeDeviceType_Diode:
		break;
	case LnxeDeviceType_NPN:
	case LnxeDeviceType_PNP:
		break;
	case LnxeDeviceType_PMOS:
	case LnxeDeviceType_NMOS:
		netnm1 = pElement->GetNodeName(0); // Drain
		netnm2 = pElement->GetNodeName(1); // Gate 
		netnm3 = pElement->GetNodeName(2); // Source
		netnm4 = pElement->GetNodeName(3); // Bulk
		topcell->AddMOS(insname, cell, netnm2, netnm3, netnm1, netnm4);
		break;
	}
}

// Create block
void SchematicAdapter::CreateBlock(const nxePSpcElement* pElement) {

}


