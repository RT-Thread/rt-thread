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

#include "ioman_small.h"

esint8 ioman_init(IOManager *ioman, euint8* bufferarea)
{
	ioman_reset(ioman);
	return(0);
}
/*****************************************************************************/

void ioman_reset(IOManager *ioman)
{
	ioman->sector=ioman->status=ioman->itptr=0;
	ioman->stack.sector=ioman->stack.status=0;
		
	ioman_setError(ioman,IOMAN_NOERROR);
		
}
/*****************************************************************************/

void ioman_setAttr(IOManager *ioman,euint8 attribute,euint8 val)
{
	if(val){
		ioman->status|=1<<attribute;
	}else{
		ioman->status&=~(1<<attribute);
	}
}
/*****************************************************************************/

euint8 ioman_getAttr(IOManager *ioman,euint8 attribute)
{
	return(ioman->status&(1<<attribute));
}
/*****************************************************************************/


euint8* ioman_getSector(IOManager *ioman,euint32 address, euint8 mode)
{
	if(address==ioman->sector){
		if(mode==IOM_MODE_READWRITE)ioman_setWritable();
		return(ioman->bufptr);
	}
	
}

esint8 ioman_readSector(IOManager *ioman,euint32 address,euint8* buf)
{
	esint8 r;

	if(buf==0){
		return(-1);
	}
	
	//r=if_readBuf(ioman->iface,address,buf);
	r = efs_read_sectors(ioman->device, address, 1, buf);
	
	if(r!=0){
		ioman_setError(ioman,IOMAN_ERR_READFAIL);
		return(-1);
	}
	return(0);
}
/*****************************************************************************/

esint8 ioman_writeSector(IOManager *ioman, euint32 address, euint8* buf)
{
	esint8 r;

	if(buf==0)return(-1);
	
	//r=if_writeBuf(ioman->iface,address,buf);
	r = efs_write_sectors(ioman->device, address, 1, buf);
	
	if(r<=0){
		ioman_setError(ioman,IOMAN_ERR_WRITEFAIL);
		return(-1);
	}
	return(0);
}
/*****************************************************************************/
