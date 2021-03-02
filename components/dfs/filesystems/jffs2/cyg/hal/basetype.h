#ifndef CYGONCE_HAL_BASETYPE_H
#define CYGONCE_HAL_BASETYPE_H

//=============================================================================
//
//      basetype.h
//
//      Standard types for this architecture.
//
//=============================================================================
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
//=============================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):   nickg, gthomas
// Contributors:  nickg, gthomas
// Date:        1998-09-11
// Purpose:     Define architecture base types.
// Usage:       Included by "cyg_type.h", do not use directly

//
//####DESCRIPTIONEND####
//

//-----------------------------------------------------------------------------
// Characterize the architecture

#ifdef __ARMEB__
# define CYG_BYTEORDER           CYG_MSBFIRST    // Big endian
#else
# define CYG_BYTEORDER           CYG_LSBFIRST    // Little endian
#endif

#if defined(__ARMEL__) && defined(__VFP_FP__)
# define CYG_DOUBLE_BYTEORDER    CYG_LSBFIRST
#else
# define CYG_DOUBLE_BYTEORDER    CYG_MSBFIRST    // Big? endian
#endif

//-----------------------------------------------------------------------------
// ARM does not usually use labels with underscores.

#define CYG_LABEL_NAME(_name_) _name_
#define CYG_LABEL_DEFN(_name_) _name_

//-----------------------------------------------------------------------------
// Override the alignment definitions from cyg_type.h. ARM only allows 4
// byte alignment whereas the default is 8 byte.

#define CYGARC_ALIGNMENT 4
#define CYGARC_P2ALIGNMENT 2

//-----------------------------------------------------------------------------
// Define the standard variable sizes

// The ARM architecture uses the default definitions of the base types,
// so we do not need to define any here.

//-----------------------------------------------------------------------------
#endif // CYGONCE_HAL_BASETYPE_H
// End of basetype.h
