/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxeknowhowhub.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeKNOWHOWHUB_H_
#define LnxeKNOWHOWHUB_H_

#include "nxedef.h"

class nxeCell;
class nxeDesigner;


class DLLDECL nxeKnowHowHub
{
public:
	//! Constructor
	nxeKnowHowHub() {};

	//! Destructor
	virtual ~nxeKnowHowHub() {};

	//! Init
	virtual nxeCell* GetSchCell(const char* pCellName) const = 0;

	//! Get designer
	virtual nxeDesigner& GetDesigner() const = 0;

};

#endif /* #ifndef LnxeKNOWHOWHUB_H_ */

