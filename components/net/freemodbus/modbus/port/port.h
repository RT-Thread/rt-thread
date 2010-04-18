/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: port.h,v 1.1 2007/04/24 23:15:18 wolti Exp $
 */

#ifndef _PORT_H
#define _PORT_H

#include <rtthread.h>

#define INLINE
#define PR_BEGIN_EXTERN_C           extern "C" {
#define PR_END_EXTERN_C             }

#define assert(x) RT_ASSERT(x)
#define ENTER_CRITICAL_SECTION()	EnterCriticalSection()
#define EXIT_CRITICAL_SECTION()		ExitCriticalSection()

void EnterCriticalSection( void );
void ExitCriticalSection( void );

typedef rt_uint8_t BOOL;
typedef unsigned char UBYTE;
typedef unsigned char UCHAR;
typedef char CHAR;

typedef rt_uint16_t USHORT;
typedef rt_int16_t SHORT;

typedef rt_uint32_t ULONG;
typedef rt_int32_t LONG;

#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif

#endif
