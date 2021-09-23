/*========================================================================
  Copyright (c) 2018 NextEDA Project Team.
  All rights reserved.

  File Name: nxeversion.h
  File Description:

  Note(s):

  History:

========================================================================*/

#ifndef Lnxe_VERSION_H_
#define Lnxe_VERSION_H_


#ifdef NXE_VERSION
#undef NXE_VERSION
#endif // #ifdef NXE_VERSION

/*
 *  NXE_VERSION % 100 is the patch level
 *  NXE_VERSION / 100 % 1000 is the minor version
 *  NXE_VERSION / 100000 is the major version
 *
 *  Example 103900 => 1.039.00
 */
#define NXE_VERSION 100000


#endif /* #ifndef Lnxe_VERSION_H_ */
