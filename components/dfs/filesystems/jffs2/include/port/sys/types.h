#ifndef CYGONCE_ISO_SYS_TYPES_H
#define CYGONCE_ISO_SYS_TYPES_H
/*========================================================================
//
//      sys/types.h
//
//      POSIX types
//
//========================================================================
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
//========================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):     jlarmour
// Contributors:
// Date:          2000-04-14
// Purpose:       This file provides various types required by POSIX 1003.1.
// Description:   The real contents of this file get set from the
//                configuration (set by the implementation)
// Usage:         #include <sys/types.h>
//
//####DESCRIPTIONEND####
//
//======================================================================
*/

/* CONFIGURATION */

//#include <pkgconf/system.h>
//#include <pkgconf/isoinfra.h>          /* Configuration header */

/* INCLUDES */

/* This is the "standard" way to get size_t from stddef.h,
 * which is the canonical location of the definition.
 */
//#define __need_size_t
//#include <stddef.h>

typedef long ssize_t;

typedef short dev_t;
typedef unsigned int ino_t;
typedef unsigned short nlink_t;
typedef long off_t;

typedef unsigned short gid_t;
typedef unsigned short uid_t;
typedef int pid_t;

#if defined(MSVC)
#include <time.h>
#else
typedef int time_t;
#endif
//#include "os_sys_stat.h"
#endif /* CYGONCE_ISO_SYS_TYPES_H multiple inclusion protection */

/* EOF sys/types.h */

