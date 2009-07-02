/*****************************************************************************\
*                     EFSL - Embedded Filesystems Library                     *
*                     -----------------------------------                     *
*                                                                             *
* Filename : ioman_small.c                                                    *
* Release  : 0.3 - devel                                                      *
* Description : The IO Manager receives all requests for sectors in a central *
*               allowing it to make smart decision regarding caching.         *
*               The IOMAN_NUMBUFFER parameter determines how many sectors     *
*               ioman can cache. ioman also supports overallocating and       *
*               backtracking sectors.                                         *
*               This is the small version of IOMan, for systems with limited  *
*               resources. It features only one fixed buffer, and has         *
*               simplified operation                                          *
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

#include "error.h"
#include "plibc.h"
#include "debug.h"
#include "types.h"
#include "config.h"

#define IOMAN_STATUS_ATTR_VALIDDATA  0
#define IOMAN_STATUS_ATTR_USERBUFFER 1
#define IOMAN_STATUS_ATTR_WRITE      2

#define IOM_MODE_READONLY  1
#define IOM_MODE_READWRITE 2
#define IOM_MODE_EXP_REQ   4

struct _IOManStack{
	euint32 sector;
	euint8  status;
};
typedef struct _IOManStack IOManStack;

struct _IOManager{
	rt_device_t  device;					/* device handler */	
	euint8 bufptr[512];
	IOMAN_ERR_EUINT8
	euint32 sector;
	euint8  status;
	euint8  itptr;
	IOManStack stack;
};
typedef struct _IOManager IOManager;

#define IOBJ ioman

#define ioman_isValid() ioman_getAttr(IOBJ,IOMAN_STATUS_ATTR_VALIDDATA)
#define ioman_isUserBuf() ioman_getAttr(IOBJ,IOMAN_STATUS_ATTR_USERBUFFER)
#define ioman_isWritable() ioman_getAttr(IOBJ,IOMAN_STATUS_ATTR_WRITE)

#define ioman_setValid() ioman_setAttr(IOBJ,IOMAN_STATUS_ATTR_VALIDDATA,1)
#define ioman_setUserBuf() ioman_setAttr(IOBJ,IOMAN_STATUS_ATTR_USERBUFFER,1)
#define ioman_setWritable() ioman_setAttr(IOBJ,IOMAN_STATUS_ATTR_WRITE,1)

#define ioman_setNotValid() ioman_setAttr(IOBJ,IOMAN_STATUS_ATTR_VALIDDATA,0)
#define ioman_setNotUserBuf() ioman_setAttr(IOBJ,IOMAN_STATUS_ATTR_USERBUFFER,0)
#define ioman_setNotWritable() ioman_setAttr(IOBJ,IOMAN_STATUS_ATTR_WRITE,0)

#define ioman_isReqRo(mode)  ((mode)&(IOM_MODE_READONLY))
#define ioman_isReqRw(mode)  ((mode)&(IOM_MODE_READWRITE))
#define ioman_isReqExp(mode) ((mode)&(IOM_MODE_EXP_REQ))

esint8 ioman_init(IOManager *ioman, euint8* bufferarea);
void ioman_reset(IOManager *ioman);
void ioman_setAttr(IOManager *ioman,euint8 attribute,euint8 val);
euint8 ioman_getAttr(IOManager *ioman,euint8 attribute);
