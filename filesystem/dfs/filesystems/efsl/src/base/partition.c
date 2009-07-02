/*****************************************************************************\
*                     EFSL - Embedded Filesystems Library                     *
*                     -----------------------------------                     *
*                                                                             *
* Filename : partition.c                                                      *
* Release  : 0.3 - devel                                                      *
* Description : These functions are partition specific. Searching FAT type    *
*               partitions and read/write functions to partitions.            *
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
#include "partition.h"
#include "efs.h"
/*****************************************************************************/

/* ****************************************************************************  
 * void part_initPartition(Partition *part,Disc* refDisc)
 * Description: This function searches the 4 partitions for a FAT class partition
 * and marks the first one found as the active to be used partition.
*/
void part_initPartition(Partition *part)
{	
	part_setError(part,PART_NOERROR);
}
/*****************************************************************************/ 


/* ****************************************************************************  
 * eint16 part_isFatPart(euint8 type)
 * Description: This functions checks if a partitiontype (eint8) is of the FAT
 * type in the broadest sense. I
 * Return value: If it is FAT, returns 1, otherwise 0.
*/
eint16 part_isFatPart(euint8 type)
{
	if(type == PT_FAT12  ||
	   type == PT_FAT16A ||
	   type == PT_FAT16  ||
	   type == PT_FAT32  ||
	   type == PT_FAT32A ||
	   type == PT_FAT16B   )
	{
		return(1);
	}
	return(0);
}
/*****************************************************************************/ 

esint8 part_readBuf(Partition *part, euint32 address, euint8* buf)
{
	return efs_read_sectors(part->ioman->device, address, 1, buf);
}

/* ****************************************************************************  
 * eint16 part_writeBuf(Partition *part,euint32 address,euint8* buf)
 * Description: This function writes 512 bytes, from buf. It's offset is address
 * sectors from the beginning of the partition.
 * Return value: It returns whatever the hardware function returns. (-1=error)
*/
eint16 part_writeBuf(Partition *part,euint32 address,euint8* buf)
{
	/*DBG((TXT("part_writeBuf :: %li\n"),address));*/
	return efs_write_sectors(part->ioman->device, address, 1, buf);
}
/*****************************************************************************/ 

/* ****************************************************************************  
 * euint8* part_getSect(Partition *part, euint32 address, euint8 mode)
 * Description: This function calls ioman_getSector, but recalculates the sector
 * address to be partition relative.
 * Return value: Whatever getSector returns. (pointer or 0)
*/
euint8* part_getSect(Partition *part, euint32 address, euint8 mode)
{
	return(ioman_getSector(part->ioman,address,mode));
}

/* ****************************************************************************  
 * esint8 part_relSect(Partition *part, euint8* buf)
 * Description: This function calls ioman_releaseSector.
 * Return value: Whatever releaseSector returns.
*/
esint8 part_relSect(Partition *part, euint8* buf)
{
	return(ioman_releaseSector(part->ioman,buf));
}

esint8 part_flushPart(Partition *part,euint32 addr_l, euint32 addr_h)
{
	return ioman_flushRange(part->ioman,addr_l,addr_h);
}

esint8 part_directSectorRead(Partition *part, euint32 address, euint8* buf, euint32 numsector)
{
	return ioman_directSectorRead(part->ioman, address, buf, numsector);
}

esint8 part_directSectorWrite(Partition *part,euint32 address, euint8* buf, euint32 numsector)
{
	return ioman_directSectorWrite(part->ioman, address, buf, numsector);
}
