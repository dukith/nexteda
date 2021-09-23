/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: schematicadapter.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef L_SCHEMATICADAPTER_H_
#define L_SCHEMATICADAPTER_H_

#include "sampledef.h"

class SchematicAdapter {
public:
	//! Constructor
	SchematicAdapter(nxeCircuit* pCircuit);

	//! Destructor
	virtual ~SchematicAdapter();

	//! Load schematic from pspice file and create circuit
	void Load(const char* pSpcfile);

protected:
	//! Create circuit from spice model
	void CreateCircuit(const nxePSpcModel* pModel);

	//! Create cell
	void CreateCell(nxePSpcModel* pModel);

	//! Create device
	void CreateDevice(nxeBlock* pBlock, const nxePSpcElement* pElement);

	//! Create block
	void CreateBlock(nxeBlock* pBlock, const nxePSpcElement* pElement);

private:
	//! Circuit
	nxeCircuit* mCircuit;
};

#endif /* #ifndef L_SCHEMATICADAPTER_H_ */




