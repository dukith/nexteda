/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxecellset.h
  File Description:

  Note(s):

  History:

========================================================================*/


#ifndef LnxeCELLSET_H_
#define LnxeCELLSET_H_

#include "nxedef.h"

class DLLDECL nxeCellSet
{
public:
	//! Constructor
	nxeCellSet() {};

	//! Destructor
	virtual ~nxeCellSet() {};

	//! Clear
	virtual void Clear(int pDestroy = 0) = 0;

	//! Get length
	virtual size_t Length() const = 0;

};

#endif /* #ifndef LnxeCELLSET_H_ */

