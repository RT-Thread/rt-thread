/*****************************************************************************\
*                     EFSL - Embedded Filesystems Library                     *
*                     -----------------------------------                     *
*                                                                             *
* Filename : ioman.c                                                          *
* Release  : 0.3 - devel                                                      *
* Description : The IO Manager receives all requests for sectors in a central *
*               allowing it to make smart decision regarding caching.         *
*               The IOMAN_NUMBUFFER parameter determines how many sectors     *
*               ioman can cache. ioman also supports overallocating and       *
*               backtracking sectors.                                         *
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

#ifndef __IOMAN_H__
#define __IOMAN_H__

/*****************************************************************************/
#include <rtthread.h>

#include "error.h"
#include "plibc.h"
#include "debug.h"
#include "types.h"
#include "config.h"
/*****************************************************************************/

#define IOMAN_STATUS_ATTR_VALIDDATA  0
#define IOMAN_STATUS_ATTR_USERBUFFER 1
#define IOMAN_STATUS_ATTR_WRITE      2

#define IOM_MODE_READONLY  1
#define IOM_MODE_READWRITE 2
#define IOM_MODE_EXP_REQ   4

struct _IOManStack{
	euint32 sector;
	euint8  status;
	euint8  usage;
};
typedef struct _IOManStack IOManStack;

struct _IOManager{
	rt_device_t device;
	euint8 *bufptr;
	euint16 numbuf;
	euint16 numit;
		
	IOMAN_ERR_EUINT8
		
	IOManStack stack[IOMAN_NUMBUFFER][IOMAN_NUMITERATIONS];
	
	euint32 sector[IOMAN_NUMBUFFER];
	euint8  status[IOMAN_NUMBUFFER];
	euint8  usage[IOMAN_NUMBUFFER];
	euint8  reference[IOMAN_NUMBUFFER];
	euint8  itptr[IOMAN_NUMBUFFER];
#ifdef IOMAN_DO_MEMALLOC
	euint8  cache_mem[IOMAN_NUMBUFFER * 512];
#endif
};
typedef struct _IOManager IOManager;

#define IOBJ ioman

#define ioman_isValid(bp) ioman_getAttr(IOBJ,bp,IOMAN_STATUS_ATTR_VALIDDATA)
#define ioman_isUserBuf(bp) ioman_getAttr(IOBJ,bp,IOMAN_STATUS_ATTR_USERBUFFER)
#define ioman_isWritable(bp) ioman_getAttr(IOBJ,bp,IOMAN_STATUS_ATTR_WRITE)

#define ioman_setValid(bp) ioman_setAttr(IOBJ,bp,IOMAN_STATUS_ATTR_VALIDDATA,1)
#define ioman_setUserBuf(bp) ioman_setAttr(IOBJ,bp,IOMAN_STATUS_ATTR_USERBUFFER,1)
#define ioman_setWritable(bp) ioman_setAttr(IOBJ,bp,IOMAN_STATUS_ATTR_WRITE,1)

#define ioman_setNotValid(bp) ioman_setAttr(IOBJ,bp,IOMAN_STATUS_ATTR_VALIDDATA,0)
#define ioman_setNotUserBuf(bp) ioman_setAttr(IOBJ,bp,IOMAN_STATUS_ATTR_USERBUFFER,0)
#define ioman_setNotWritable(bp) ioman_setAttr(IOBJ,bp,IOMAN_STATUS_ATTR_WRITE,0)

#define ioman_isReqRo(mode)  ((mode)&(IOM_MODE_READONLY))
#define ioman_isReqRw(mode)  ((mode)&(IOM_MODE_READWRITE))
#define ioman_isReqExp(mode) ((mode)&(IOM_MODE_EXP_REQ))

esint8 ioman_init(IOManager *ioman, euint8* bufferarea);
void ioman_reset(IOManager *ioman);
euint8* ioman_getBuffer(IOManager *ioman,euint8* bufferarea);
void ioman_setAttr(IOManager *ioman,euint16 bufplace,euint8 attribute,euint8 val);
euint8 ioman_getAttr(IOManager *ioman,euint16 bufplace,euint8 attribute);
euint8 ioman_getUseCnt(IOManager *ioman,euint16 bufplace);
void ioman_incUseCnt(IOManager *ioman,euint16 bufplace);
void ioman_decUseCnt(IOManager *ioman,euint16 bufplace);
void ioman_resetUseCnt(IOManager *ioman,euint16 bufplace);
euint8 ioman_getRefCnt(IOManager *ioman,euint16 bufplace);
void ioman_incRefCnt(IOManager *ioman,euint16 bufplace);
void ioman_decRefCnt(IOManager *ioman,euint16 bufplace);
void ioman_resetRefCnt(IOManager *ioman,euint16 bufplace);
esint8 ioman_pop(IOManager *ioman,euint16 bufplace);
esint8 ioman_push(IOManager *ioman,euint16 bufplace);
euint8* ioman_getPtr(IOManager *ioman,euint16 bufplace);
esint16 ioman_getBp(IOManager *ioman,euint8* buf);
esint8 ioman_readSector(IOManager *ioman,euint32 address,euint8* buf);
esint8 ioman_writeSector(IOManager *ioman, euint32 address, euint8* buf);
void ioman_resetCacheItem(IOManager *ioman,euint16 bufplace);
esint32 ioman_findSectorInCache(IOManager *ioman, euint32 address);
esint32 ioman_findFreeSpot(IOManager *ioman);
esint32 ioman_findUnusedSpot(IOManager *ioman);
esint32 ioman_findOverallocableSpot(IOManager *ioman);
esint8 ioman_putSectorInCache(IOManager *ioman,euint32 address, euint16 bufplace);
esint8 ioman_flushSector(IOManager *ioman, euint16 bufplace);
euint8* ioman_getSector(IOManager *ioman,euint32 address, euint8 mode);
esint8 ioman_releaseSector(IOManager *ioman,euint8* buf);
esint8 ioman_directSectorRead(IOManager *ioman,euint32 address, euint8* buf);
esint8 ioman_directSectorWrite(IOManager *ioman,euint32 address, euint8* buf);
esint8 ioman_flushRange(IOManager *ioman,euint32 address_low, euint32 address_high);
esint8 ioman_flushAll(IOManager *ioman);

void ioman_printStatus(IOManager *ioman);

#endif
