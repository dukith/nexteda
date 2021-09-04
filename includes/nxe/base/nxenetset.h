/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxenetset.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeNETSET_H_
#define LnxeNETSET_H_

#include "nxedef.h"

class DLLDECL nxeNetSet
{
public:
	//! Constructor
	nxeNetSet() {};

	//! Destructor
	virtual ~nxeNetSet() {};

	//! Clear
	virtual void Clear(int pDestroy = 0) = 0;

	//! Get length
	virtual size_t Length() const = 0;

};

#endif /* #ifndef LnxeNETSET_H_ */

