#ifndef CYGONCE_PKGCONF_INFRA_H
# define CYGONCE_PKGCONF_INFRA_H

//======================================================================
//
//      infra.h
//
//      Host side implementation of the infrastructure configuration
//      header.
//
//======================================================================
// ####ECOSHOSTGPLCOPYRIGHTBEGIN####                                        
// -------------------------------------------                              
// This file is part of the eCos host tools.                                
// Copyright (C) 1998, 1999, 2000 Free Software Foundation, Inc.            
//
// This program is free software; you can redistribute it and/or modify     
// it under the terms of the GNU General Public License as published by     
// the Free Software Foundation; either version 2 or (at your option) any   
// later version.                                                           
//
// This program is distributed in the hope that it will be useful, but      
// WITHOUT ANY WARRANTY; without even the implied warranty of               
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU        
// General Public License for more details.                                 
//
// You should have received a copy of the GNU General Public License        
// along with this program; if not, write to the                            
// Free Software Foundation, Inc., 51 Franklin Street,                      
// Fifth Floor, Boston, MA  02110-1301, USA.                                
// -------------------------------------------                              
// ####ECOSHOSTGPLCOPYRIGHTEND####                                          
//======================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):   bartv
// Contact(s):  bartv   
// Date:        1998/07/13
// Version:     0.01
//
//####DESCRIPTIONEND####
//======================================================================

// The purpose of this header file is to replicate appropriate
// functionality from the target-side header file <pkgconf/infra.h>.
// This header file is intended to contain configuration options
// related to the implementation of the infrastructure, as opposed
// to how that infrastructure gets used by other packages. A good
// example would be a configuration option to control the size
// of the circular trace buffer.
//
// On the host side these things are handled by autoconf, and in
// particular the configure.in script will offer command-line
// arguments allowing the relevant options to be controlled.
// The relevant information will end up in <cyg/pkgconf/hostinfra.h>
# include <pkgconf/hostinfra.h>

// Some options should always be enabled in this header file.
#define CYGDBG_INFRA_DIAG_PRINTF_USE_VARARG
#define CYGDBG_INFRA_DEBUG_ASSERT_MESSAGE
#define CYGDBG_INFRA_DEBUG_TRACE_MESSAGE

// Other options should be decided on a package by package basis,
// e.g. whether or not assertions are used. On the host side it is
// not appropriate to control these globally, instead the infrastructure
// always provides the necessary functionality and it is up to the
// other parts of the system to decide whether or not the facilities
// get used.

// A third set of options deal with the environment, e.g. the sizes
// of various data types. autoconf macros take care of most of the
// work, but some translation is needed into eCos-style names to
// avoid namespace pollution.

// Process the definitions of SIZEOF_INT_P and SIZEOF_LONG to work
// out a sensible data type for CYG_ADDRESS and CYG_ADDRWORD.

#if (!defined(SIZEOF_INT_P) || !defined(SIZEOF_LONG))
# error "Configure problem: data type sizes not set"
#endif

#if (SIZEOF_INT_P == 4)
    // The default, nothing needs to be done
#elif (SIZEOF_INT_P == 8)
# define cyg_haladdress cyg_halint64
#else
# error "Only 32 and 64 bit pointers are supported"
#endif

#if ((SIZEOF_INT_P == 4) && (SIZEOF_LONG == 4))
    // The default, nothing needs to be done
#elif ((SIZEOF_INT_P <= 8) && (SIZEOF_LONG <= 8))
    // cyg_halint64 will have been defined appropriately.
# define cyg_haladdrword cyg_halint64
#else
# error "Only 32 and 64 bit machine word sizes are supported"
#endif

// Any symbols defined in <pkgconf/hostconf.h> which have been processed
// here should no longer be of any interest, and in the interests of
// reducing name space pollution they get undef'ed here.

// In addition there are two #define's in the config.h header file
// which are always present and which have names that are rather too
// generic. These get removed here as well. The version is worth
// preserving under a different name.
#undef SIZEOF_INT_P
#undef SIZEOF_LONG
#undef PACKAGE
#undef VERSION

#endif  // CYGONCE_PKGCONF_INFRA_H
// End of infra.h
