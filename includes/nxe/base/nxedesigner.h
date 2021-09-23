/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxedesigner.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeDESIGNER_H_
#define LnxeDESIGNER_H_

#include "nxedef.h"

class nxeKnowHowHub;
class nxeKHModelBrowser;

class DLLDECL nxeDesigner
{
public:
	//! Constructor
	nxeDesigner(const char* pCtrlFile) {};

	//! Destructor
	virtual ~nxeDesigner() {};

	//! Init
	virtual void Init() = 0;

	//! Get know-how browser
	virtual nxeKHModelBrowser& GetKHModelBrowser() = 0;

	//! Get know-how browser
	virtual const nxeKHModelBrowser& GetKHModelBrowser() const = 0;

	//! Get know-how hub
	virtual nxeKnowHowHub& GetKnowHowHub() = 0;

	//! Get know-how hub
	virtual const nxeKnowHowHub& GetKnowHowHub() const = 0;

};

#endif /* #ifndef LnxeDESIGNER_H_ */

