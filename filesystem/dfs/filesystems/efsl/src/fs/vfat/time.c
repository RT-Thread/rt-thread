/*****************************************************************************\
*                     EFSL - Embedded Filesystems Library                     *
*                     -----------------------------------                     *
*                                                                             *
* Filename : time.c                                                           *
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

/*****************************************************************************/
#include "tm.h"
/*****************************************************************************/

euint16 fs_makeDate(void)
{
#ifndef DATE_TIME_SUPPORT
	return(0);
#else
	euint8 m,d;
	euint16 y;
	
	y = time_getYear()-1980;
	m = time_getMonth();
	d = time_getDay();
	
	return(
		(y>127?127<<9:(y&0x3F)<<9)   |
		((m==0||m>12)?1:(m&0xF)<<5)  |
		((d==0||d>31)?1:(d&0x1F))
	);
#endif
}
/*****************************************************************************/

euint16 fs_makeTime(void)
{
#ifndef DATE_TIME_SUPPORT
	return(0);
#else
	euint8 s,m,h;
	
	s = time_getSecond();
	m = time_getMinute();
	h = time_getHour();
	
	return(
		(h>23?0:(h&0x1F)<<11) |
		(m>59?0:(m&0x3F)<<5)  |
		(s>59?0:(s-s%2)/2)
	);
#endif
}
/*****************************************************************************/

euint8 fs_hasTimeSupport(void)
{
#ifdef DATE_TIME_SUPPORT
	return(1);
#else
	return(0);
#endif
}
/*****************************************************************************/


