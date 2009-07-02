/*****************************************************************************\
*                     EFSL - Embedded Filesystems Library                     *
*                     -----------------------------------                     *
*                                                                             *
* Filename : extract.h                                                        *
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

#ifndef __EXTRACT_H_
#define __EXTRACT_H_

/*****************************************************************************/
#include "config.h"
#include "types.h"
/*****************************************************************************/

#if !(defined(HOST_LITTLE_ENDIAN)) && !(defined(HOST_BIG_ENDIAN))
#error Endianess undefined, see config.h
#elif defined(HOST_LITTLE_ENDIAN) && (defined(HOST_BIG_ENDIAN))
#error Endianess defined as little and big, see config.h
#endif

/*****************************************************************************/

#define end_conv16(x)  ((((euint16)(x) & 0xff00) >> 8) | \
                      (((euint16)(x) & 0x00ff) << 8))
#define end_conv32(x)  ((((euint32)(x) & 0xff000000) >> 24) | \
                       (((euint32)(x) & 0x00ff0000) >> 8)  | \
                       (((euint32)(x) & 0x0000ff00) << 8)  | \
                       (((euint32)(x) & 0x000000ff) << 24))

/*****************************************************************************/

#if defined(BYTE_ALIGNMENT)
	#define ex_getb16(buf) (*((euint16*)(buf)))
	#define ex_setb16(buf,data) *((euint16*)(buf))=(data)
	#define ex_getb32(buf) (*((euint32*)(buf)))
	#define ex_setb32(buf,data) *((euint32*)(buf))=(data)
#else
	#define ex_getb16(buf) \
		((euint16)(*((euint8*)(buf)+1)<<8) + \
		 (euint16)(*((euint8*)(buf)+0)<<0))
	void ex_setb16(euint8* buf,euint16 data);
	#define ex_getb32(buf) \
		((euint32)(*((euint8*)(buf)+3)<<24) + \
		 (euint32)(*((euint8*)(buf)+2)<<16) + \
		 (euint32)(*((euint8*)(buf)+1)<<8)  + \
		 (euint32)(*((euint8*)(buf)+0)<<0))
	void ex_setb32(euint8* buf,euint32 data);
#endif

#if defined(HOST_LITTLE_ENDIAN)
	#define ex_lth16(buf) ex_getb16(buf)
	#define ex_lth32(buf) ex_getb32(buf)
	#define ex_bth16(buf) end_conv16(ex_getb16(buf))
	#define ex_bth32(buf) end_conv32(ex_getb32(buf))
	
	#define ex_htl16(buf) ex_setb16(buf)
	#define ex_htl32(buf) ex_setb32(buf)
	#define ex_htb16(buf) ex_setb16(end_conv16(buf))
	#define ex_htb32(buf) ex_setb32(end_conv32(buf))
#elif defined(HOST_BIG_ENDIAN)
	#define ex_lth16(buf) end_conv16(ex_getb16(buf))
	#define ex_lth32(buf) end_conv32(ex_getb32(buf))
	#define ex_bth16(buf) ex_getb16(buf)
	#define ex_bth32(buf) ex_getb32(buf)
	
	#define ex_htl16(buf) ex_setb16(end_conv16(buf))
	#define ex_htl32(buf) ex_setb32(end_conv32(buf))
	#define ex_htb16(buf) ex_setb16(buf)
	#define ex_htb32(buf) ex_setb32(buf)
#endif

#endif

