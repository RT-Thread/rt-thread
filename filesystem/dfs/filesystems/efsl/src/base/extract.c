/*****************************************************************************\
*                     EFSL - Embedded Filesystems Library                     *
*                     -----------------------------------                     *
*                                                                             *
* Filename : extract.c                                                        *
* Release  : 0.3 - devel                                                      *
* Description : This file contains functions to copy structures that get      *
*               corrupted when using direct memory copy                       *
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
#include "extract.h"
/*****************************************************************************/

#if !(defined(BYTE_ALIGNMENT))
#warning "Compiling f_setbxx"
void ex_setb16(euint8* buf,euint16 data)
{
	buf[1] = data>>8;
	buf[0] = data>>0;
}

void ex_setb32(euint8* buf,euint32 data)
{
	buf[3] = data>>24;
	buf[2] = data>>16;
	buf[1] = data>>8;
	buf[0] = data>>0;
}
#endif



