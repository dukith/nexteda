/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxeinstanceset.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeINSTANCESET_H_
#define LnxeINSTANCESET_H_

#include "nxedef.h"


class DLLDECL nxeInstanceSet
{
public:
	//! Constructor
	nxeInstanceSet() {};

	//! Destructor
	virtual ~nxeInstanceSet() {};

	//! Clear
	virtual void Clear(int pDestroy = 0) = 0;

	//! Get length
	virtual size_t Length() const = 0;

};


#endif /* #ifndef LnxeINSTANCESET_H_ */

