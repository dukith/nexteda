/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxeschfixsolution.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxesSCHFIXSOLUTION_H_
#define LnxesSCHFIXSOLUTION_H_

#include "nxe/base/nxedef.h"
#include "nxe/base/nxeinstancelist.h"


class nxeNGInstanceList;
class nxeNetList;

class DLLDECL nxeSchFixSolution
{
public:
	//! Constructor
	nxeSchFixSolution() {};

	//! Destructor
	virtual ~nxeSchFixSolution() {};

	/**
	 * \brief Get NG instances
	 */
	virtual const nxeNGInstanceList& GetNGInstanceList() const = 0;
	
	/**
	 * \brief Get removed instances
	 */
	virtual const nxeInstanceList& GetUnnecessaryInstanceList() const = 0;

	/**
	 * \brief Get removed nets
	 */
	virtual const nxeNetList& GetUnnecessaryNetList() const = 0;

};


#endif /* #ifndef LnxesSCHFIXSOLUTION_H_*/

