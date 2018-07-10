#ifndef CYGONCE_ERROR_CODES_H
#define CYGONCE_ERROR_CODES_H
/*===========================================================================
//
//      codes.h
//
//      Common error code definitions
//
//===========================================================================
// ####ECOSGPLCOPYRIGHTBEGIN####
// -------------------------------------------
// This file is part of eCos, the Embedded Configurable Operating System.
// Copyright (C) 1998, 1999, 2000, 2001, 2002 Free Software Foundation, Inc.
//
// eCos is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 or (at your option) any later
// version.
//
// eCos is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public License
// along with eCos; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//
// As a special exception, if other files instantiate templates or use
// macros or inline functions from this file, or you compile this file
// and link it with other works to produce a work based on this file,
// this file does not by itself cause the resulting work to be covered by
// the GNU General Public License. However the source code for this file
// must still be made available in accordance with section (3) of the GNU
// General Public License v2.
//
// This exception does not invalidate any other reasons why a work based
// on this file might be covered by the GNU General Public License.
// -------------------------------------------
// ####ECOSGPLCOPYRIGHTEND####
//===========================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):    jlarmour
// Contributors: jlarmour
// Date:         2000-04-14
// Purpose:      To provide a common set of error codes
// Description:  This provides a common set of error codes that all
//               packages can agree on. It doesn't preclude them defining
//               their own error return system, but this is a preferable
//               system to use to help error support be as general as
//               possible.
//
//               We try and conform to the ANSI/POSIX error code format,
//               namely starting with the character 'E'
//
// Usage:        #include <cyg/error/codes.h>
//
//               Example:
//
//               err=myfun();
//               if (err != ENOERR)
//               {
//                 str=strerror(err);
//                 printf("myfun returned error: %s\n", str);
//               }
//               else ....
//
//####DESCRIPTIONEND####
//
//=========================================================================*/

/* CONFIGURATION */

//#include <pkgconf/error.h>      prife    // Configuration header

#ifdef __cplusplus
extern "C" {
#endif

/* TYPE DEFINITIONS */

/* A type for error codes which may be useful to explain the purpose of
 * a variable or return code. It shows that it contains an error code
 * of the type defined below */

typedef int Cyg_ErrNo;

#include <rtthread.h>

#define ENOERR  RT_EOK

#ifdef __cplusplus
}   /* extern "C" */
#endif

#endif /* CYGONCE_ERROR_CODES_H multiple inclusion protection */

/* EOF codes.h */
