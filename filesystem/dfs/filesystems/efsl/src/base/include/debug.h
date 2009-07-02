/*****************************************************************************\
*                     EFSL - Embedded Filesystems Library                     *
*                     -----------------------------------                     *
*                                                                             *
* Filename : debug.h                                                          *
* Release  : 0.3 - devel                                                      *
* Description : These functions are used for debugging output on different    *
*               environments                                                  *
*                                                                             *
* This program is free software; you can redistribute it and/or               *
* modify it under the terms of the GNU General Public License                 *
* as published by the Free Software Foundation; version 2                     *
* of the License.                                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful,             *
* but WITHOUT ANY WARRANTY; without even the implied warranty of              *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
* GNU General Public License for more details.                                *
*                                                                             *
* As a special exception, if other files instantiate templates or             *
* use macros or inline functions from this file, or you compile this          *
* file and link it with other works to produce a work based on this file,     *
* this file does not by itself cause the resulting work to be covered         *
* by the GNU General Public License. However the source code for this         *
* file must still be made available in accordance with section (3) of         *
* the GNU General Public License.                                             *
*                                                                             *
* This exception does not invalidate any other reasons why a work based       *
* on this file might be covered by the GNU General Public License.            *
*                                                                             *
*                                                    (c)2006 Lennart Yseboodt *
*                                                    (c)2006 Michael De Nil   *
\*****************************************************************************/

#ifndef __DEBUG_H__
#define __DEBUG_H__

/*****************************************************************************/
#include "types.h"
#include "config.h"
/*****************************************************************************/

#ifndef DEBUG
	#define TXT(x) ;
	#define DBG(x) ;
	#define FUNC_IN(x) ;
	#define FUNC_OUT(x) ;
#endif

#ifdef DEBUG

	#ifdef HW_ENDPOINT_LINUX
		#include <stdio.h>
		#include <stdarg.h>
	
		#define TXT(x) x
		#define DBG(x) debug x
		#define FUNC_IN(x) debug_funcin(x)
		#define FUNC_OUT(x) debug_funcout(x)
	#endif

	void debug(const eint8 *format, ...);
	void debug_init();
	void debug_end();

#endif

#endif
