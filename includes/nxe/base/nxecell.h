/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxecell.h
  File Description:

  Note(s):

  History:

========================================================================*/


#ifndef LnxeCELL_H_
#define LnxeCELL_H_

#include "nxedef.h"

class nxePort;
class nxeDesigner;
class nxePortList;

class DLLDECL nxeCell
{
public:
	//! Constructor
	nxeCell() {};

	//! Destructor
	virtual ~nxeCell() {};

	//! Get name
	virtual const char* GetName() const = 0;

	//! Get library name
	virtual const char* GetLibName() const = 0;

	//! Get model name
	virtual const char* GetModelName() const = 0;

	//! Get cell name
	virtual const char* GetViewName() const = 0;

	//! Check cell being block or not
	virtual int IsBlock() const = 0;

	//! Get cell (schemaic or layout) type
	virtual nxeCellType GetCellType() const = 0;

	//! Get designer 
	virtual nxeDesigner& GetDesigner() const = 0;

	/**
	 * \brief Create port
	 *
	 * \exception latmRedefineException
	 * \exception lstdNotEnoughMemoryException
	 */
	virtual nxePort* CreatePort(const char* pPortName) = 0;

	//! Get port by name
	virtual nxePort* GetPortByName(const char* pPortName) const = 0;

	//! Get port list
	virtual const nxePortList& GetPortList() const = 0;

	//! Compare 
	virtual int operator == (const nxeCell& pCell) const = 0;
};

#endif /* #ifndef LnxeCELL_H_ */

