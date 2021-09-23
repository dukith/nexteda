/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxekhmodel.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef LnxeKHMODEL_H_
#define LnxeKHMODEL_H_

#include "nxedef.h"

class nxeCell;


class DLLDECL nxeKHModel
{
public:
	//! Constructor
	nxeKHModel() {};

	//! Destructor
	virtual ~nxeKHModel() {};

	//! Name
	virtual const char* GetName() const = 0;
	
	//! Get type
	virtual nxeKHModelType GetType() const = 0;
	
	//! Get description
	virtual const char* GetDescription() const = 0;
	
	//! Compare
	virtual int operator == (const nxeKHModel& pSrc) const = 0;

};


class DLLDECL nxeKHModelIterator {
public:
	//! Constructor
	nxeKHModelIterator() {};

	//! Destructor
	virtual ~nxeKHModelIterator() {};

	//! Reset
	virtual void Reset() = 0;

	/**
	 * \brief Next
	 *
	 * \return 1 Next item existing
	 * \return 0 Last item reached
	 */
	virtual int operator ++() = 0;

	//! Get node
	virtual const nxeKHModel* Get() const = 0;
};


#endif /* #ifndef LnxeKHMODEL_H_ */



