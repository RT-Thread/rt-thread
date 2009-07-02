/*****************************************************************************\
*                     EFSL - Embedded Filesystems Library                     *
*                     -----------------------------------                     *
*                                                                             *
* Filename : time.h                                                           *
* Release  : 0.3 - devel                                                      *
* Description : This file contains functions for time support                 *
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

#ifndef __TIME_H_
#define __TIME_H_

/*****************************************************************************/
#include "types.h"
/*****************************************************************************/

#ifdef DATE_TIME_SUPPORT
	#define time_getYear(void) efsl_getYear()
	#define time_getMonth(void) efsl_getMonth()
	#define time_getDay(void) efsl_getDay()
	#define time_getHour(void) efsl_getHour()
	#define time_getMinute(void) efsl_getMinute()
	#define time_getSecond(void) efsl_getSecond()
	#define time_getDate(void) fs_makeDate()
	#define time_getTime(void) fs_makeTime()
#else
	#define time_getYear(void) 0x0;
	#define time_getMonth(void) 0x0;
	#define time_getDay(void) 0x0;
	#define time_getHour(void) 0x0;
	#define time_getMinute(void) 0x0;
	#define time_getSecond(void) 0x0;
	#define time_getDate(void) 0x0;
	#define time_getTime(void) 0x0;
#endif

#ifdef DATE_TIME_SUPPORT
euint16 efsl_getYear(void);
euint8  efsl_getMonth(void);
euint8  efsl_getDay(void);
euint8  efsl_getHour(void);
euint8  efsl_getMinute(void);
euint8  efsl_getSecond(void);
euint16 fs_makeDate(void);
euint16 fs_makeTime(void);
#endif

euint8 fs_hasTimeSupport(void);

#endif
