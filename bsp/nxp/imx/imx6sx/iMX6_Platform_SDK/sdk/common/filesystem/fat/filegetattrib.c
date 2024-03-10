/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*----------------------------------------------------------------------------
 SigmaTel Inc
 $Archive: /Fatfs/FileSystem/Fat32/base/filegetattrib.c $
 $Revision: 7 $                                       
 $Date: 9/13/03 12:20p $
 Description: filegetattrib.c
 Notes:	This file read provides base api functon to get the attribute of the file.
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
		File Includes
----------------------------------------------------------------------------*/
#include <types.h>
#include "fstypes.h"
#include "filesystem/fsapi.h"
#include "fat_internal.h"
#include "diroffset.h"

/*----------------------------------------------------------------------------

>  Function Name:  RtStatus_t filegetattrib(uint8_t *FilePath)

   FunctionType:  Reentrant

   Inputs:        1)Pointer to the filepath

   Outputs:       Returns directory attributes for a file, or ERROR Code if  Error Occurs

   Description:   Gets directory attributes for a file

<
----------------------------------------------------------------------------*/
RtStatus_t filegetattrib(uint8_t * FilePath)
{
    int32_t dirattribute, HandleNumber;
    uint8_t *buf;
    uint32_t cacheToken;

    if ((HandleNumber = Fopen(FilePath, (uint8_t *) "r")) < 0) {
        return HandleNumber;
    }

    EnterNonReentrantSection();
    if ((buf =
         (uint8_t *) FSReadSector(Handle[HandleNumber].Device, Handle[HandleNumber].DirSector,
                                  WRITE_TYPE_RANDOM, &cacheToken)) == (uint8_t *) 0) {
        LeaveNonReentrantSection();
        return ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
    }
    dirattribute =
        FSGetByte((uint8_t *) buf, (DIR_ATTRIBUTEOFFSET + Handle[HandleNumber].diroffset));
    FSReleaseSector(cacheToken);
    LeaveNonReentrantSection();

    Freehandle(HandleNumber);
    return dirattribute;
}

/*----------------------------------------------------------------------------

>  Function Name:  RtStatus_t filegetattribhandle(int32_t HandleNumber)

   FunctionType:  Reentrant

   Inputs:        1)valid file handle 

   Outputs:       Returns directory attributes for a file, or ERROR Code if  Error Occurs

   Description:   Gets directory attributes (a byte) for a file. See possible attributes in fsapi.h

<
----------------------------------------------------------------------------*/
RtStatus_t filegetattribhandle(int32_t HandleNumber)
{
    RtStatus_t dirattribute;
    uint8_t *buf;
    uint32_t cacheToken;

    EnterNonReentrantSection();
    if ((buf =
         (uint8_t *) FSReadSector(Handle[HandleNumber].Device, Handle[HandleNumber].DirSector,
                                  WRITE_TYPE_RANDOM, &cacheToken)) == (uint8_t *) 0) {
        LeaveNonReentrantSection();
        return ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
    }
    dirattribute =
        (RtStatus_t) FSGetByte((uint8_t *) buf,
                               (DIR_ATTRIBUTEOFFSET + Handle[HandleNumber].diroffset));
    FSReleaseSector(cacheToken);
    LeaveNonReentrantSection();

    return dirattribute;
}

/*----------------------------------------------------------------------------

>  Function Name: RtStatus_t filegetdate(int32_t HandleNumber,int32_t crt_mod_date_time_para,DIR_DATE *dirdate,DIR_TIME *dirtime)

   FunctionType:  Reentrant

   Inputs:        1) HandleNumber
                  2) create\modify\date\time parameter
                  3) pointer to sturcture DIR_DATE
                  4) pointer to structure DIR_TIME

   Outputs:       Returns SUCCESS or error code if error occurs.
   
   Description:   This function finds the creation / modification date or time of 
                  the file referenced by the given handle number.
<
----------------------------------------------------------------------------*/
RtStatus_t filegetdate(int32_t HandleNumber, int32_t crt_mod_date_time_para, DIR_DATE * dirdate,
                       DIR_TIME * dirtime)
{
    int32_t date_time, offset = 0;
    uint8_t *buf;
    uint32_t cacheToken;

    if ((HandleNumber < 0) || (HandleNumber >= maxhandles))
        return ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED;

    if (crt_mod_date_time_para == CREATION_DATE)
        offset = DIR_CRTDATEOFFSET;

    else if (crt_mod_date_time_para == CREATION_TIME)
        offset = DIR_CRTTIMEOFFSET;

    else if (crt_mod_date_time_para == MODIFICATION_DATE)
        offset = DIR_WRTDATEOFFSET;

    else if (crt_mod_date_time_para == MODIFICATION_TIME)
        offset = DIR_WRTTIMEOFFSET;

    EnterNonReentrantSection();

    if ((buf =
         (uint8_t *) FSReadSector(Handle[HandleNumber].Device, Handle[HandleNumber].DirSector,
                                  WRITE_TYPE_RANDOM, &cacheToken)) == (uint8_t *) 0) {
        LeaveNonReentrantSection();
        return ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
    }
    date_time = FSGetWord((uint8_t *) buf, (offset + Handle[HandleNumber].diroffset));
    FSReleaseSector(cacheToken);
    LeaveNonReentrantSection();

    if (crt_mod_date_time_para == CREATION_DATE || crt_mod_date_time_para == MODIFICATION_DATE) {
        dirdate->Day = date_time & 0x001F;
        dirdate->Month = (date_time & 0x01E0) >> 5;
        dirdate->Year = ((date_time & 0xFE00) >> 9) + 1980;
    } else {
        dirtime->Second = (date_time & 0x001F) * 2;
        dirtime->Minute = (date_time & 0x07E0) >> 5;
        dirtime->Hour = ((date_time & 0xF800) >> 11);
    }
    return SUCCESS;
}

/*----------------------------------------------------------------------------

>  Function Name: RtStatus_t filesetattrib(int32_t HandleNumber,int32_t dirattribute)

   FunctionType:  Reentrant

   Inputs:        1)HandleNumber
                  2)dirattribute

   Outputs:       Returns SUCCESS or ERROR Code if  Error Occurs

   Description:   Sets directory attributes for a file

<
----------------------------------------------------------------------------*/
RtStatus_t filesetattrib(int32_t HandleNumber, int32_t dirattribute)
{
    RtStatus_t Retval;
    EnterNonReentrantSection();
    if ((HandleNumber < 0) || (HandleNumber >= maxhandles)) {
        LeaveNonReentrantSection();
        return ERROR_OS_FILESYSTEM_MAX_HANDLES_EXCEEDED;
    }

    if ((Retval = FSWriteSector(Handle[HandleNumber].Device, Handle[HandleNumber].DirSector,
                                (DIR_ATTRIBUTEOFFSET + Handle[HandleNumber].diroffset),
                                (uint8_t *) & dirattribute, 0, 2, WRITE_TYPE_RANDOM)) < 0) {
        LeaveNonReentrantSection();
        return Retval;
    }

    LeaveNonReentrantSection();
    return SUCCESS;
}

/*----------------------------------------------------------------------------

>  Function Name: RtStatus_t filesetdate(uint8_t *FilePath,int32_t crt_mod_date_time_para,DIR_DATE *dirdate,DIR_TIME *dirtime)

   FunctionType:  Reentrant

   Inputs:        1) FilePath
                  2) create\modify\date\time parameter
                  3) pointer to structure DIR_DATE
                  4) pointer to structure DIR_TIME

   Outputs:       Returns SUCCESS or error code if error occurs.
   
   Description:   This function sets the creation / modification date or time of 
                  the file referenced by the given handle to the specified date or time.

   Notes:

  Date Format:
   A FAT directory entry date stamp is a 16-bit field that is basically a date
   relative to the MS-DOS epoch of 01/01/1980.
     Bits  0–4: Day of month, valid value range 1-31 inclusive
     Bits  5–8: Month of year, 1 = January, valid value range 1–12 inclusive
     Bits 9–15: Count of years from 1980, valid value range 0–127 inclusive (1980–2107)

  Time Format:
   A FAT directory entry time stamp is a 16-bit field that has a granularity
   of 2 seconds.  The valid time range is from Midnight 00:00:00 to 23:59:58.
     Bits   0–4: 2-second count, valid value range 0–29 inclusive (0 – 58 seconds)
     Bits  5–10: Minutes, valid value range 0–59 inclusive
     Bits 11–15: Hours, valid value range 0–23 inclusive
<----------------------------------------------------------------------------*/
RtStatus_t filesetdate(uint8_t * FilePath, int32_t crt_mod_date_time_para, DIR_DATE * dirdate,
                       DIR_TIME * dirtime)
{
    uint32_t offset = 0;
    int32_t HandleNumber;
    RtStatus_t Retval = SUCCESS;
    int32_t date_time, year, month;
    int32_t hour, minute, second;

    if ((HandleNumber = Fopen(FilePath, (uint8_t *) "r")) < 0)
        return (RtStatus_t) HandleNumber;

    if (crt_mod_date_time_para == CREATION_DATE)
        offset = DIR_CRTDATEOFFSET;

    else if (crt_mod_date_time_para == CREATION_TIME)
        offset = DIR_CRTTIMEOFFSET;

    else if (crt_mod_date_time_para == MODIFICATION_DATE)
        offset = DIR_WRTDATEOFFSET;

    else if (crt_mod_date_time_para == MODIFICATION_TIME)
        offset = DIR_WRTTIMEOFFSET;

    if (crt_mod_date_time_para == CREATION_DATE || crt_mod_date_time_para == MODIFICATION_DATE) {
        // Local vars must have room to left shift the 8-bit dirdate fields
        month = ((dirdate->Month << 5) & 0x01E0);
        year = ((dirdate->Year - 1980) << 9);
        date_time = (dirdate->Day | month | year);
    } else {
        // Local vars must have room to left shift the 8-bit dirtime fields
        second = dirtime->Second >> 1;
        minute = ((dirtime->Minute << 5) & 0x07E0);
        hour = ((dirtime->Hour << 11) & 0xF800);
        date_time = (second | minute | hour);
    }

    if ((Retval = FSWriteSector(Handle[HandleNumber].Device, Handle[HandleNumber].DirSector,
                                (offset + Handle[HandleNumber].diroffset), (uint8_t *) & date_time,
                                0, 2, WRITE_TYPE_RANDOM)) < 0)
        return Retval;

    Freehandle(HandleNumber);
    return SUCCESS;
}
