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
 $Archive: /Fatfs/FileSystem/Fat32/Utility/CreateDirectoryRecord.c $
 $Revision: 21 $
 $Date: 9/16/03 12:23p $
 Description: CreateDirectoryRecord.c
 Notes:
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
		File Includes
----------------------------------------------------------------------------*/
#include <string.h>

#include <types.h>
#include "fstypes.h"
#include "filesystem/fsapi.h"
#include "fat_internal.h"
#include "diroffset.h"

void Setfilename(uint8_t * buf, uint8_t * buffer_1);
void Uppercase(uint8_t * file);
int32_t ConverToShortname(uint8_t * file, uint8_t * filenamebuf, int32_t index, int32_t length);

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t CreateDirRecord(uint8_t *filepath,int32_t HandleNumber,int32_t ClusterNumber,
                  int32_t DirAttr,int32_t stringtype,int32_t length,int32_t index,uint8_t *Buffer)

   FunctionType:  Reentrant

   Inputs:        1) Pointer to file name or directory
                  2) HandleNumber
                  3) Cluster Number
                  4) Directory Attribute
                  5) String type
                  6) Length
                  7) Index
                  8) Pointer to buffer

   Outputs:       Returns SUCCESS else an error code

   Description:   Creates new directory record in the free record of the directory sector
<
----------------------------------------------------------------------------*/
RtStatus_t CreateDirRecord
    (uint8_t * filepath,
     int32_t HandleNumber,
     int32_t ClusterNumber,
     int32_t DirAttr,
     int32_t stringtype, int32_t length, int32_t index, uint8_t * Buffer, int32_t FileSize) {
    int32_t strlen, Flag = 0, count = 0;
    RtStatus_t RetValue;

    uint8_t buf[32];
    uint8_t ShortNameDir[12];

    uint8_t shortfilename[15];
    int32_t chksum, byte, offset = 0;
    int32_t k, i, j;

    for (k = 0; k < 12; k++) {
        ShortNameDir[k] = 0x20;
        shortfilename[k] = 0x00;
    }
    memset(buf, 0, 32);
    if (stringtype == kDBCSEncoding) {
        length = DiscardTrailigPeriods(filepath, length, index, 0);
    } else if (stringtype == kUTF16Encoding) {
        //modify: double the length
        Strcpyw((uint8_t *) filepath, Buffer, length, index);

        length = DiscardTrailigPeriodsw((uint8_t *) Buffer, (length - index), index);

        // The PutWord was not being qualified by 
        // if (length<MAX_UNICODE_SIZE) and therefore
        // causing stack corruption.
        if (length < MAX_UNICODE_SIZE) {
            PutWord(Buffer, 0, length);
        }
    }

    if (stringtype == kDBCSEncoding) {
        if ((Flag = IsShortNameValid(filepath, length, index)) < 0)
            return (RtStatus_t) Flag;
        if (Flag == 1)
            DBCStoUnicode(filepath, (uint8_t *) Buffer, index, length);
        else {
            count = 1;
            Strcpy(filepath, (uint8_t *) shortfilename, length, index);
        }
    }

    if ((stringtype == kUTF16Encoding) || (Flag == 1))  // TOVERIFY2   2.6 ver not chosen since 3.05 ver differed and sgtl-HK was referenced in comments of 2.6 ver.
    {
        strlen = StrlengthW((uint8_t *) Buffer);
        for (i = 0; i < strlen; i++) {
            byte = FSGetWord(Buffer, offset);
            for (j = 0; j < LONGNAMERES_CH; j++) {
                if (byte < 0x20)
                    return ERROR_OS_FILESYSTEM_ILLEGAL_FILENAME_CHARA;
                if (byte == Long_NameRes_Ch[j])
                    return ERROR_OS_FILESYSTEM_ILLEGAL_FILENAME_CHARA;
            }
            offset += 2;
        }
        count = (strlen - 1) / LONGDIRCH_PER_RECORD + 2;

        /* set the filename to fit in 8+3 format */
        Setshortfilename(HandleNumber, Buffer, (uint8_t *) shortfilename);
    }

    if (Handle[HandleNumber].StartingCluster != 0) {
        if ((RetValue = FindfreeRecord(HandleNumber, count)) < 0)
            return RetValue;
    } else {
        if ((RetValue = (RtStatus_t) CheckspaceinRootdir(HandleNumber, count)) < 0)
            return RetValue;
    }

    Handle[HandleNumber].Mode |= CREATE_MODE;   // einfo
    ArrangeFileName(shortfilename, ShortNameDir);

    if (stringtype == kUTF16Encoding || Flag == 1) {
        chksum = ChkSum((uint8_t *) ShortNameDir);
        ArrangeLongFileName(HandleNumber, (uint8_t *) Buffer, count, chksum);
    }

    if ((RetValue =
         CreateShortDirRecord(&ShortNameDir[0], HandleNumber, ClusterNumber, DirAttr,
                              FileSize)) < 0) {
        Handle[HandleNumber].Mode ^= CREATE_MODE;
        return RetValue;
    }

    Handle[HandleNumber].FileSize = FileSize;

    Handle[HandleNumber].Mode ^= CREATE_MODE;
    return SUCCESS;
}

/*----------------------------------------------------------------------------
>  Function Name: int32_t ChkSum(uint8_t *filename)

   FunctionType:  Reentrant

   Inputs:        1) Pointer to file name or directory
                 
   Outputs:       Chksum computed over the given filename.

   Description:   Computes the chksum of the given filename.
<
----------------------------------------------------------------------------*/
int32_t ChkSum(uint8_t * filename)
{
    int32_t Sum = 0, temp;
    int32_t i;

    for (i = 0; i < 11; i++) {
        temp = 0;
        if (Sum & 1)
            temp = 0x80;
        Sum = temp + (Sum >> 1) + (FSGetByte(filename, i));
        Sum = Sum & 0xff;
    }
    return Sum;
}

/*----------------------------------------------------------------------------
>  Function Name: int64_t ReadDirectoryRecord(int32_t HandleNumber,int32_t RecordNumber,uint8_t *Buffer)

   FunctionType:  Reentrant

   Inputs:        1)HandleNumber
                  2)RecordNumber
                  3)Pointer to Buffer

   Outputs:       Returns Number of Bytes read on Success else an Error Code

   Description:   Reads the directory record of the given record number
<
----------------------------------------------------------------------------*/
int64_t ReadDirectoryRecord(int32_t HandleNumber, int32_t RecordNumber, uint8_t * Buffer)
{
    RtStatus_t RetValue = SUCCESS;
    int32_t NumberOfBytestoSeek;
    int64_t Key, lTemp;

    if (Handle[HandleNumber].StartingCluster == 0) {
        if ((lTemp = (int64_t) ReadRootdirRecord(HandleNumber, RecordNumber, Buffer)) < 0) {
            return lTemp;
        }
        Key =
            (((int64_t) Handle[HandleNumber].Device << 44) | ((int64_t) Handle[HandleNumber].
                                                              BytePosInSector << 32) |
             Handle[HandleNumber].CurrentSector);
        return Key;
    } else {
        if ((NumberOfBytestoSeek =
             RecordNumber * DIRRECORDSIZE) != Handle[HandleNumber].CurrentOffset) {
            if ((RetValue = Fseek(HandleNumber, NumberOfBytestoSeek, SEEK_SET)) < 0) {
                return RetValue;
            }
        }
        if ((Fread(HandleNumber, Buffer, DIRRECORDSIZE)) <= 0) {
            return ERROR_OS_FILESYSTEM_INVALID_RECORD_NUMBER;
        }
        Key =
            (((int64_t) Handle[HandleNumber].
              Device << 44) | ((int64_t) (Handle[HandleNumber].BytePosInSector -
                                          32) << 32) | Handle[HandleNumber].CurrentSector);
        return Key;
    }
}

void GetDateTime(int32_t * date, int32_t * time)
{
    /* 26 APR 2012 */
    *date = (32 < 9) | (4 << 5) | 26;

    /* 14:30:00 */
    *time = (14 < 11) | (30 << 5) | 0;
}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t CreateShortDirRecord(uint8_t *filename,int32_t HandleNumber,int32_t ClusterNumber,int32_t DirAttr)

   FunctionType:  Reentrant

   Inputs:        1) Pointer to file name or directory
                  2) Handle Number
                  3) Cluster Number
                  4) Directory Attribute

   Outputs:       Returns SUCCESS else an error code

   Description:   Creates new directory record in the free record of the directory sector

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
<
----------------------------------------------------------------------------*/
RtStatus_t CreateShortDirRecord(uint8_t * filename, // SFN
                                int32_t HandleNumber,
                                int32_t ClusterNumber, int32_t DirAttr, int32_t FileSize)
{
    RtStatus_t RetValue;
    int32_t date, time;
    uint8_t buf[32];

    memset(buf, 0, 32);
    memcpy(buf, filename, 12);
    buf[DIR_ATTRIBUTEOFFSET] = DirAttr;

    PutWord(buf, (ClusterNumber >> 16) & 0x00ffff, DIR_FSTCLUSHIOFFSET);
    PutWord(buf, ClusterNumber & 0x00ffff, DIR_FSTCLUSLOOFFSET);
    PutDword(buf, FileSize, DIR_FILESIZEOFFSET);

    GetDateTime(&date, &time);
    PutWord(buf, date, DIR_CRTDATEOFFSET);  // Set creation date
    PutWord(buf, date, DIR_LSTACCDATEOFFSET);   // Set last access date
    PutWord(buf, date, DIR_WRTDATEOFFSET);  // Set modification date
    PutWord(buf, time, DIR_CRTTIMEOFFSET);  // Set creation time
    PutWord(buf, time, DIR_WRTTIMEOFFSET);  // Set modification time

    if (Handle[HandleNumber].StartingCluster != 0) {
        if ((RetValue = (RtStatus_t) Fwrite(HandleNumber, buf, DIRRECORDSIZE)) <= 0)
            return RetValue;
    } else
        if ((RetValue =
             FSWriteSector(Handle[HandleNumber].Device, Handle[HandleNumber].CurrentSector,
                           Handle[HandleNumber].BytePosInSector, buf, 0, DIRRECORDSIZE,
                           WRITE_TYPE_RANDOM)) < 0)
        return RetValue;

    return SUCCESS;
}

/*----------------------------------------------------------------------------
>  Function Name:  RtStatus_t Isdirectoryempty( int32_t Handlenumber)

   FunctionType:   Reentrant

   Inputs:         1) Handlenumber

   Outputs:        Returns SUCCESS or ERROR_OS_FILESYSTEM_DIR_NOT_EMPTY

   Description:    Determines the directory is empty or not by checking all the
                   records whether they are deleted or not 
<                   
----------------------------------------------------------------------------*/
RtStatus_t Isdirectoryempty(int32_t Handlenumber)
{
    int32_t Firstbyteofrecord, Recordno;
    int64_t NumBytesRead;
    uint8_t buf[32];

    Recordno = 2;
    do {
        if ((NumBytesRead = ReadDirectoryRecord(Handlenumber, Recordno, buf)) < 0)
            return SUCCESS;
        Firstbyteofrecord = FSGetByte(buf, 0);

        if (Firstbyteofrecord == 0x00)
            return (SUCCESS);

        if (Firstbyteofrecord != 0xE5)
            return (ERROR_OS_FILESYSTEM_DIR_NOT_EMPTY);

        Recordno++;
    } while (NumBytesRead != 0);

    return (SUCCESS);

}

/*----------------------------------------------------------------------------
>  Function Name:  RtStatus_t Longdirmatch(int32_t HandleNumber,int32_t RecordNo,uint8_t *file,int32_t index,int32_t length, int32_t stringtype)

   FunctionType:   Reentrant

   Inputs:         1) Handle Number
                   2) Record Number
				   3) Pointer to file name
                   4) Index
                   5) Length
                   6) String Type 

   Outputs:        Returns ERROR_OS_FILESYSTEM_FILE_FOUND if directory or file name matches else ERROR_OS_FILESYSTEM_FILE_NOT_FOUND
      
   Description:    This function first decrements the record no. and then reads the directory record 
                   for this record no. and then it matches the directory or file name with the 
                   directory record in the buffer word by word. If long name matches then returns 
                   ERROR_OS_FILESYSTEM_FILE_FOUND else returns ERROR_OS_FILESYSTEM_FILE_NOT_FOUND. 
>
----------------------------------------------------------------------------*/
RtStatus_t Longdirmatch(int32_t HandleNumber, int32_t RecordNo, uint8_t * file, int32_t index,
                        int32_t length, int32_t stringtype)
{
    int32_t offset, wordno = 0, filenameword, word, firstword, secondword, strlen;
    uint8_t buf[32];
    int32_t shortname[12];
    int64_t NumBytesRead;
    int32_t LongDirEnd = 0;

    offset = DIRRECORDSIZE;
    wordno = index;

    firstword = FSGetWord(file, offset);
    secondword = FSGetWord(file, (offset + 2));

    strlen = length - index;

    if (firstword == 0x2e && secondword == 0x2e && strlen == 2) {
        UnicodeToOEM((uint8_t *) file, (uint8_t *) shortname, 4, 0);
        return (Shortdirmatch
                (HandleNumber, RecordNo, (uint8_t *) shortname, (uint8_t *) shortname, buf, 0, 0, 3,
                 0));
    }

    else {
        while (wordno < length) {
            if (offset == DIRRECORDSIZE) {
                RecordNo--;
                NumBytesRead = ReadDirectoryRecord(HandleNumber, RecordNo, buf);
                //This will take care that we have reached the last record of long directory structure
                //LongDirEnd will be used later
                if (FSGetByte(buf, 0) & 0x40)
                    LongDirEnd = 1;
                else
                    LongDirEnd = 0;
                offset = LDIRNAME1OFFSET;
            }

            word = FSGetWord(file, wordno);
            wordno += 2;

            filenameword = FSGetWord(buf, offset);
            if (word != filenameword) {
                filenameword = Changecase(filenameword);
                if (word != filenameword)
                    return (ERROR_OS_FILESYSTEM_FILE_NOT_FOUND);
            }
            offset = offset + 2;
            /* if all words of longdir firstname field are occupied, check for 
               longdir secondname field */
            if (offset == LDIRATTRIOFFSET)
                offset = LDIRNAME2OFFSET;

            /* if all words of longdir secondname field are occupied, check for 
               longdir thirdname field */
            if (offset == LDIRFSTCLUSNOOFFSET)
                offset = LDIRNAME3OFFSET;

            /* if all words of longdir thirdname field are occupied, check for 
               next sub component of longdir entry */
        }                       // while(wordno<length)

    }

    /* check whether the file name found is correct or not */
    /* check whether the word at this offset is 00 or not */

    if (offset != DIRRECORDSIZE) {
        if (FSGetByte(buf, offset) != 0x00)
            return (ERROR_OS_FILESYSTEM_FILE_NOT_FOUND);
    }
    RecordNo--;
    //We have compared the name corectly, just check if we are at the end of the long directory name?
    //If yes we found the name correctly else return error as we encountered similar name
    if ((RecordNo >= 0) && (LongDirEnd == 0))
        return ERROR_OS_FILESYSTEM_FILE_NOT_FOUND;

    (void)NumBytesRead;
    return (ERROR_OS_FILESYSTEM_FILE_FOUND);
}

/*----------------------------------------------------------------------------
>  Function Name:  RtStatus_t MatchdirRecordW(int32_t HandleNumber,int32_t RecordNo,uint8_t *file,uint8_t *buf,int32_t index,int32_t length)

   FunctionType:   Reentrant

   Inputs:         1) Handle number
                   2) Record Number
				   3) Pointer to file name
				   4) Pointer to buffer
                   5) Index
                   6) Length
                   7) Shortnamebuf
  Outputs:         Returns ERROR_OS_FILESYSTEM_FILE_FOUND if filename matches otherwise ERROR_OS_FILESYSTEM_FILE_NOT_FOUND.
      
  Description:     This function first checks the long directory attribute from the directory record 
                   and if it is set then it checks the first byte of the record. If it is set to 
                   first long directory subcomponent then it matches the given file name with long 
                   directory name.  
                   IF long directory attribute is not set then function will try to match short directory record from passed 
                   Shortnamebuf.If file name matches then returns ERROR_OS_FILESYSTEM_FILE_FOUND else returns file not found 
<    
----------------------------------------------------------------------------*/
RtStatus_t MatchdirRecordW(int32_t HandleNumber, int32_t RecordNo, uint8_t * file, uint8_t * buf,
                           int32_t index, int32_t length, uint8_t * Shortnamebuf)
{
    RtStatus_t filefound = SUCCESS;
    int32_t dirattribute;
    int32_t Firstbyte;

    // SGTL_HK change
    //int32_t shortname[13],ucs2buffer[13];   
    Firstbyte = file[index];
    if ((file[index] == 0x2E) && (file[index + 1] == 0x2E) && ((length - index) == 2)) {
        RecordNo++;
        filefound = Longdirmatch(HandleNumber, RecordNo, file, index, length, UCS3s);
    } else {
        dirattribute = FSGetByte(buf, DIR_ATTRIBUTEOFFSET);

        if (dirattribute == LONGDIRATTRIBUTE) {
            Firstbyte = FSGetByte(buf, 0);
            if (Firstbyte == 1 || Firstbyte == 0x41) {
                RecordNo++;
                length = DiscardTrailigPeriodsw(file, length, index);
                filefound = Longdirmatch(HandleNumber, RecordNo, file, index, length, UCS3s);
            }
        }
        // #if 0 // removed segment to be like sdk3.05    TOVERIFY2   do we need this fix for player? is it benign in MTP?
        else                    // else block inserted for HK fix. Merged into br_sdk_2600 by HJ on 11May2005    TOVERIFY correctness review.
        {
            //  SGTL-HK 1-3-2005
            //  If the Length of the Name > 11, it must Not be a Short Name so No File will be found
            //modify: change the equation 
//          if (((length/2 - index/2)-1) <= 11)
//          {
//        //modify: Replace function with Strcpyw function 
//        //      strcpyUCS3_2((int32_t *)file, ucs2buffer, index,length);
//              Strcpyw((uint8_t *)file, (uint8_t *)ucs2buffer,length,index);
//              UnicodeToOEM((uint8_t *)ucs2buffer,(uint8_t *)shortname, length-index, 0); 
//              Uppercase((uint8_t*)shortname);
            filefound =
                Shortdirmatch(HandleNumber, RecordNo, (uint8_t *) Shortnamebuf,
                              (uint8_t *) Shortnamebuf, buf, 0, 0, length, 0);

            // }
        }
        // #endif
    }
    return (filefound);
}

/*----------------------------------------------------------------------------
>  Function Name:  RtStatus_t Shortdirmatch(int32_t HandleNumber,int32_t RecordNo,uint8_t *file,
                       uint8_t *Shortname,uint8_t *buf,int32_t Flag,int32_t index,int32_t length,uint8_t *UniCodeBuffer)

   FunctionType:   Reentrant

   Inputs:         1) Handle Number
                   2) Record Number
				   3) Pointer to file name
				   4) Pointer to Short name
				   5) Pointer to buffer
                   6) Flag
                   7) Index
                   8) Length
                   9) Pointer to Unicodebuffer

   Outputs:        Returns ERROR_OS_FILESYSTEM_FILE_FOUND if directory or file name matches else ERROR_OS_FILESYSTEM_FILE_NOT_FOUND.

   Description:    This function matches the directory or file name with the directory record 
                   in the buffer byte-by-byte. If the short name matches, then returns ERROR_OS_FILESYSTEM_FILE_FOUND. 
                   If short name is alias of a long directory name then checks for long directory 
                   name in the previous directory entry. If short directory name does not match then 
                   returns ERROR_OS_FILESYSTEM_FILE_NOT_FOUND. 
<
----------------------------------------------------------------------------*/
RtStatus_t Shortdirmatch(int32_t HandleNumber, int32_t RecordNo, uint8_t * file,
                         uint8_t * Shortname, uint8_t * buf, int32_t Flag, int32_t index,
                         int32_t length, uint8_t * UniCodeBuffer)
{
    int32_t byte;
    RtStatus_t filefound;
    int32_t offset = 0, Byteno = 0, filenamebyte, strlen;
    uint8_t filenamebuf[15];

    length = length - 1;

    if (buf[0] == 0xE5) {
        // a deleted record, don't bother to compare and return not found
        return (ERROR_OS_FILESYSTEM_FILE_NOT_FOUND);
    }

    offset = index;
    Setfilename((uint8_t *) buf, (uint8_t *) filenamebuf);
    while ((byte = FSGetByte(Shortname, Byteno)) != '\0') {
        filenamebyte = FSGetByte(filenamebuf, Byteno);
        if (filenamebyte == '~') {
            if (Flag == 1) {
                DBCStoUnicode(file, (uint8_t *) UniCodeBuffer, index, length);
                strlen = StrlengthW((uint8_t *) UniCodeBuffer);
                strlen = strlen << 1;
                filefound =
                    Longdirmatch(HandleNumber, RecordNo, (uint8_t *) UniCodeBuffer, 0, strlen,
                                 UCS2s);
                return (filefound);
            }
        }

        if (byte != filenamebyte)
            return (ERROR_OS_FILESYSTEM_FILE_NOT_FOUND);

        Byteno++;
    }

    if ((filenamebyte = FSGetByte(filenamebuf, Byteno)) != '\0')
        return ERROR_OS_FILESYSTEM_FILE_NOT_FOUND;

    (void)offset;
    return (ERROR_OS_FILESYSTEM_FILE_FOUND);
}

/*----------------------------------------------------------------------------
>  Function Name:  void Setfilename(uint8_t *buf,uint8_t *buffer_1)

   FunctionType:   Reentrant

   Inputs:         1) Pointer to buffer
                   2) Pointer to buffer_1

   Outputs:        Nil

   Description:    Sets file name
<
----------------------------------------------------------------------------*/
void Setfilename(uint8_t * buf, uint8_t * buffer_1)
{
    int32_t byte, j;
    int32_t offset = 0, offset_dest = 0;

    byte = FSGetByte(buf, 0);
    if (byte == 0x05)
        PutByte(buf, 0xe5, 0);

    while (offset < 8) {
        byte = GetChar(buf, &offset);
        if (byte == 0x20)
            break;
        PutChar(buffer_1, &offset_dest, byte);
    }

    PutChar(buffer_1, &offset_dest, '.');
    j = 0;
    offset = 8;
    while (offset < 11) {
        byte = GetChar(buf, &offset);
        if (byte == 0x20) {
            if ((offset_dest <= 9) && (j == 0))
                offset_dest--;
            PutByte(buffer_1, '\0', offset_dest);
            break;
        }
        PutChar(buffer_1, &offset_dest, byte);
        j++;
    }
    PutByte(buffer_1, '\0', offset_dest);
}

/*----------------------------------------------------------------------------
>  Function Name:  void Uppercase(uint8_t *file)

   FunctionType:   Reentrant

   Inputs:         1) Pointer to file name
			   
   Outputs:        Nil
   
   Description:    Converts given file name in Uppercase
<
----------------------------------------------------------------------------*/
void Uppercase(uint8_t * file)
{
    int32_t offset = 0, offset_dest = 0, CharPrevious = 1;
    int32_t Char;
    while ((Char = GetChar(file, &offset)) != '\0') {
        if ((Char >= 97) && (Char <= 122) && (CharPrevious) < 0x80)
            Char = Char - 32;
        PutChar(file, &offset_dest, Char);
        CharPrevious = Char;
    }
    PutByte(file, 0, offset_dest);
}

/*----------------------------------------------------------------------------
>  Function Name:  in32_t ConverToShortname(uint8_t *file,uint8_t *filenamebuf,int32_t index,int32_t length)

   FunctionType:   Reentrant

   Inputs:         1) Pointer to file name
                   2) Pointer to file name buffer 
			       3) Index
                   4) Length

   Outputs:        Returns Flag_1
   
   Description:    Converts given file name to Short name.
<
----------------------------------------------------------------------------*/
int32_t ConverToShortname(uint8_t * file, uint8_t * filenamebuf, int32_t index, int32_t length)
{
    int32_t offset = 0, offset_dest = 0, count = 0, strlen;
    int32_t Chara, CharaPrevious = 1, Flag = 0, j, Flag_1 = 1;
    uint8_t temp[15];

    offset = index;
    length = length - 1;

    while ((offset < length) && count <= 12) {
        Chara = GetChar(file, &offset);
        for (j = 0; j < SHORTNAMERES_CH; j++) {
            if ((Chara == Short_NameRes_Ch[j]) && (CharaPrevious < 0x80))
                Flag = 1;
        }
        CharaPrevious = Chara;
        if (Flag == 1) {
            Chara = 0x5F;
            Flag = 0;
        }
        PutChar((uint8_t *) temp, &offset_dest, Chara);
        count++;
    }
    PutChar((uint8_t *) temp, &offset_dest, 0);

    /* strip all leading and embedded spaces from the long name */
    /* strip all leading periods from the long file name */
    offset = 0;
    count = 0;

    while ((Chara = GetChar((uint8_t *) temp, &offset)) != '\0' && offset <= 12) {
        if (Chara == '.')
            count++;
        if (Chara == 0x20)
            Flag = 1;
    }
    offset = 0;
    offset_dest = 0;
    strlen = length - index - 1;

    if (count == 0) {
        if ((strlen < 8) && (Flag == 0))
            Flag_1 = 0;
    }
    if (count > 1)
        Flag = 1;
    /* strip all leading and embedded spaces from the long name */
    /* strip all leading periods from the long file name */
    while ((Chara = GetChar((uint8_t *) temp, &offset)) != '\0' && offset <= 12) {
        if (Chara == '.') {
            if (count > 1)
                count--;
            else {
                if (offset_dest != 0) {
                    PutChar(filenamebuf, &offset_dest, Chara);
                    if ((offset <= 9) && (Flag == 0))
                        Flag_1 = 0;
                } else {
                    count--;
                    Flag = 1;
                }
            }
        }
        if (Chara != 0x20 && Chara != 0x2E && Chara != 0x2f) {
            PutChar(filenamebuf, &offset_dest, Chara);
        }
    }
    if (strlen < 6 && Flag == 1) {
        PutChar(filenamebuf, &offset_dest, '~');
        PutChar(filenamebuf, &offset_dest, 0);
    } else
        PutChar(filenamebuf, &offset_dest, 0);
    return Flag_1;
}

/*----------------------------------------------------------------------------
>  Function Name:  RtStatus_t FindfreeRecord(int32_t Handlenumber,int32_t Flag)

   FunctionType:   Reentrant

   Inputs:         1) Handlenumber
                   2) Flag

   Outputs:        Returns SUCCESS or an Error Code if error occurs
                      
   Description:    Determines free space by reading the all the records and 
                   updates handle according to the free space.
<
----------------------------------------------------------------------------*/
RtStatus_t FindfreeRecord(int32_t Handlenumber, int32_t Flag)
{
    RtStatus_t RetValue;
    int32_t Devicenum, i, Firstbyte;
    uint8_t Buffer[96];
    int32_t Recordno;
    int64_t NumBytesRead;

    Devicenum = Handle[Handlenumber].Device;
    Recordno = 0;

    do {
        if ((NumBytesRead = ReadDirectoryRecord(Handlenumber, Recordno, Buffer)) < 0)
            break;
        Firstbyte = FSGetByte(Buffer, 0);
        if (Firstbyte == 0x00) {
            Fseek(Handlenumber, -DIRRECORDSIZE, SEEK_CUR);
            return (SUCCESS);
        } else if (Firstbyte == 0xE5) {
            if (Flag == 1) {
                Fseek(Handlenumber, -DIRRECORDSIZE, SEEK_CUR);
                return (SUCCESS);
            } else {
                i = 1;
                while (1) {
                    Recordno++;
                    NumBytesRead = ReadDirectoryRecord(Handlenumber, Recordno, Buffer);
                    Firstbyte = FSGetByte(Buffer, 0);
                    if (Firstbyte == 0x00) {
                        Fseek(Handlenumber, -DIRRECORDSIZE, SEEK_CUR);
                        return (SUCCESS);
                    } else if (Firstbyte != 0xE5)
                        break;
                    else {
                        i++;
                        if (i == Flag) {
                            Fseek(Handlenumber, -(Flag * DIRRECORDSIZE), SEEK_CUR);
                            return SUCCESS;
                        }
                    }
                }               // while(1)
            }
        }
        Recordno++;
    } while (NumBytesRead != 0);

    // EOF is reached, so in order to allocate a new cluster we need to write.
    // Dummy Write the empty record. This will force allocation of new cluster.
    if ((RetValue = GetNewcluster(Handlenumber)) < 0)
        return RetValue;
    if ((RetValue = ClearCluster(Handlenumber)) < 0)
        return RetValue;

    (void)Devicenum;
    //Stmp00006804
    //If CurrentOffset isn't reset under this condition (directory table needs a new cluster to enter this particular record)
    //Handle[].DirSector will contain the wrong value after updating handle, which results in an erroneous fast_key, which can generate
    //the wrong short filename if used right after this Fopen() .
    Handle[Handlenumber].CurrentOffset = 0;

    return (SUCCESS);
}

/*----------------------------------------------------------------------------
>  Function Name:  int32_t Searchfreerecord(int32_t DeviceNum,int32_t sectorNum)

   FunctionType:   Reentrant

   Inputs:         1) Device number
                   2) Sector number

   Outputs:        Returns index no. of free record in root directory if there is a space for new 
                   directory record else an error NOSPACEINROOTDIRECTORY

   Description:    Determines space in root directory by determining the first character 
                   of directory record for 0x00 or 0xE5
<
----------------------------------------------------------------------------*/
int32_t Searchfreerecord(int32_t DeviceNum, int32_t sectorNum)
{
    int32_t Dirrecordoffset, Firstbyteofrecord, direntryindex;
    uint8_t *buf;
    uint32_t cacheToken;

    EnterNonReentrantSection();
    if ((buf =
         (uint8_t *) FSReadSector(DeviceNum, sectorNum, WRITE_TYPE_RANDOM,
                                  &cacheToken)) == (uint8_t *) 0) {
        LeaveNonReentrantSection();
        return ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
    }
    Dirrecordoffset = 0;

    for (direntryindex = 0; direntryindex < DIR_RECORD_PERSECTOR; direntryindex++) {
        Firstbyteofrecord = FSGetByte((uint8_t *) buf, Dirrecordoffset);
        /* if first byte of the record is 0x00 or 0xE5 then this record
           is free or deleted */
        if (Firstbyteofrecord == 0 || Firstbyteofrecord == 0xE5) {
            FSReleaseSector(cacheToken);
            LeaveNonReentrantSection();
            return (Dirrecordoffset);
        }

        Dirrecordoffset = Dirrecordoffset + 32;
    }
    FSReleaseSector(cacheToken);
    LeaveNonReentrantSection();
    return (ERROR_OS_FILESYSTEM_SECTOR_FULL_OF_RECORD);
}

/*----------------------------------------------------------------------------
>  Function Name:  int32_t CheckspaceinRootdir(int32_t Handlenumber,int32_t Flag)

   FunctionType:   Reentrant

   Inputs:         1) Handle number
                   2) Flag

   Outputs:        Returns index no of free record in root directory if there is a space for new dir record
                   else error ERROR_OS_FILESYSTEM_NOSPACE_IN_ROOTDIRECTORY

   Description:    Determines space in root directory by determining the first character 
                   of directory record for 0x00 or 0xE5 
<
----------------------------------------------------------------------------*/
int32_t CheckspaceinRootdir(int32_t Handlenumber, int32_t Flag)
{
    int32_t NumBytesread;
    int32_t Firstbyte;
    int32_t i;
    uint8_t Buffer[96];
    int32_t Recordno;

//      variable "Devicenum" was set but never used
//  Devicenum =     Handle[Handlenumber].Device;
    Recordno = 0;

    do {
        if ((NumBytesread = ReadRootdirRecord(Handlenumber, Recordno, Buffer)) < 0)
            return NumBytesread;
        Firstbyte = FSGetByte(Buffer, 0);
        if (Firstbyte == 0x00)
            return (SUCCESS);

        else if (Firstbyte == 0xE5) {
            if (Flag == 1)
                return (SUCCESS);
            else {
                i = 1;
                while (1) {
                    Recordno++;
                    NumBytesread = ReadRootdirRecord(Handlenumber, Recordno, Buffer);
                    Firstbyte = FSGetByte(Buffer, 0);
                    if (Firstbyte == 0x00)
                        return (SUCCESS);

                    else if (Firstbyte != 0xE5)
                        break;
                    else {
                        i++;
                        if (i == Flag) {
                            SetcurrentPos(Handlenumber, (Recordno - i + 1));
                            return SUCCESS;
                        }
                    }
                }
            }
        }
        Recordno++;
    } while (NumBytesread != 0);

    return ERROR_OS_FILESYSTEM_NOSPACE_IN_ROOTDIRECTORY;

}

/*----------------------------------------------------------------------------

>  Function Name: RtStatus_t  DeleteRecord(int32_t HandleNumber, int32_t RecordNo)

   FunctionType:  Reentrant

   Inputs:        1)  HandleNumber
                  2)  RecordNo
				   
   Outputs:       SUCCESS or error code if error occurs   
   
   Description:   Mark the directoy record of the given record no. and all the long
                  directory records associated with it as deleted.  
----------------------------------------------------------------------------*/
RtStatus_t DeleteRecord(int32_t HandleNumber, int32_t RecordNo)
{
    int32_t firstbyteofrecord;
    uint8_t DeleteDirrecordch = DELETEDDIRRECORDCHARA;
    uint8_t buf[33];
    RtStatus_t Retval;
    int64_t lTemp;

    if (Handle[HandleNumber].StartingCluster == 0) {
        if ((Retval =
             FSWriteSector(Handle[HandleNumber].Device, Handle[HandleNumber].CurrentSector,
                           Handle[HandleNumber].BytePosInSector, &DeleteDirrecordch, 0, 1,
                           WRITE_TYPE_RANDOM)) < 0)
            return Retval;
    } else {
        if ((Retval = (RtStatus_t) Fwrite(HandleNumber, &DeleteDirrecordch, 1)) <= 0)
            return Retval;
    }

    /*Now delete all long file name records that are associated with 
       the file to be deleted */

    while (1) {
        RecordNo--;             //Decrement record number

        if (RecordNo < 0)
            break;

        // This line is needed because ReadDirectoryRecord
        // does and Fseek and a Fread, which results in
        // next iteration of this loop looking at data
        // that's completely bogus if we do not seek
        // back to the beginning.
        if ((Retval = Fseek(HandleNumber, 0, SEEK_SET)) < 0) {
            return Retval;
        }

        if ((lTemp = ReadDirectoryRecord(HandleNumber, RecordNo, buf)) < 0) {
            return ERROR_OS_FILESYSTEM_INVALID_RECORD_NUMBER;   //(RtStatus_t)lTemp;       
        }

        if (lTemp == 0) {
            break;
        }

        firstbyteofrecord = FSGetByte(buf, 0);

        /* First check if record is not already deleted or parent/this directory record */

        if (firstbyteofrecord == 0xE5 || firstbyteofrecord == 0x2E)
            break;

        /* Second check if the attribute is set to LONGDIRATTRIBUTE(0x0f) => long file name */
        if ((FSGetByte(buf, DIR_ATTRIBUTEOFFSET)) != LONGDIRATTRIBUTE)
            break;

        /* Finally check if first cluster position is 0 */
        if (FSGetWord(buf, DIR_FSTCLUSLOOFFSET) != 0)
            break;
        /* The record must be a long file name therefore delete it */
        /* check for root directory */
        if (Handle[HandleNumber].StartingCluster == 0) {
            if ((Retval =
                 FSWriteSector(Handle[HandleNumber].Device, Handle[HandleNumber].CurrentSector,
                               Handle[HandleNumber].BytePosInSector, &DeleteDirrecordch, 0, 1,
                               WRITE_TYPE_RANDOM)) < 0)
                return Retval;
        } else {
            /*set Handle to original position */
            if ((Retval = Fseek(HandleNumber, -DIRRECORDSIZE, SEEK_CUR)) < 0)
                return Retval;

            if ((Retval = (RtStatus_t) Fwrite(HandleNumber, &DeleteDirrecordch, 1)) <= 0)
                return Retval;
        }
    }
    return SUCCESS;
}

/*----------------------------------------------------------------------------

>  Function Name: RtStatus_t ReadRootdirRecord(int32_t HandleNumber,int32_t RecordNumber,uint8_t *Buffer)

   FunctionType:  Reentrant

   Inputs:        1)HandleNumber
                  2)RecordNumber
                  3)Pointer to Buffer

   Outputs:       Number of Bytes read if Success else an Error

   Description:   Reads the directory record of the given record number

<
----------------------------------------------------------------------------*/
RtStatus_t ReadRootdirRecord(int32_t HandleNumber, int32_t RecordNumber, uint8_t * Buffer)
{
    int32_t DeviceNum;
    RtStatus_t Retval;
    uint8_t *buf;
    uint32_t cacheToken;

    DeviceNum = Handle[HandleNumber].Device;
    if (MediaTable[DeviceNum].FATType == FAT12 || MediaTable[DeviceNum].FATType == FAT16) {
        if (RecordNumber >= MediaTable[DeviceNum].MaxRootDirEntries || RecordNumber < 0) {
            return ERROR_OS_FILESYSTEM_INVALID_RECORD_NUMBER;
        }

        if ((Retval = SetcurrentPos(HandleNumber, RecordNumber)) < 0) {
            return Retval;
        }

        EnterNonReentrantSection();
        if ((buf =
             (uint8_t *) FSReadSector(DeviceNum, Handle[HandleNumber].CurrentSector,
                                      WRITE_TYPE_RANDOM, &cacheToken)) == (uint8_t *) 0) {
            LeaveNonReentrantSection();
            return ERROR_OS_FILESYSTEM_READSECTOR_FAIL;
        }

        memcpy(Buffer, buf + Handle[HandleNumber].BytePosInSector, DIRRECORDSIZE);

        FSReleaseSector(cacheToken);
        LeaveNonReentrantSection();

        if (FSGetByte(Buffer, 0) == 0) {
            return 0;
        }

        return DIRRECORDSIZE;   //32

    } else {
        return ERROR_OS_FILESYSTEM_MEDIA_TYPE_NOT_SUPPORTED;
    }
}

/*----------------------------------------------------------------------------

>  Function Name: RtStatus_t SetcurrentPos(int32_t HandleNumber,int32_t RecordNumber)

   FunctionType:  Reentrant

   Inputs:        1)HandleNumber
                  2)RecordNumber
                  

   Outputs:       SUCCESS OR error code if error occurs   

   Description:   Sets the given handle according to the given record number  
<
----------------------------------------------------------------------------*/
RtStatus_t SetcurrentPos(int32_t HandleNumber, int32_t RecordNumber)
{
    int32_t DeviceNum;
    int32_t offset;
    int32_t sectorno;

    DeviceNum = Handle[HandleNumber].Device;
    offset = RecordNumber * DIRRECORDSIZE;
    Handle[HandleNumber].CurrentOffset = offset;

    sectorno = offset >> MediaTable[DeviceNum].SectorShift;

    Handle[HandleNumber].CurrentSector = sectorno + MediaTable[DeviceNum].FirRootdirsec;
    Handle[HandleNumber].BytePosInSector = offset & MediaTable[DeviceNum].SectorMask;

    return SUCCESS;
}

///*----------------------------------------------------------------------------
//
//   Function Name:int32_t _reentrant  GetVolumeLabel(BYTE *Buffer,int32_t DeviceNum)
//
//   FunctionType:  Reentrant
//
//   Inputs:        1)Buffer
//                  2)DeviceNumber
//
//   Outputs:       SUCCESS  or error code if an  Error  occurs
//
//   Description:   Get the Volume Id of the drive in passed Buffer
//
////----------------------------------------------------------------------------*/
int32_t GetVolumeLabel(BYTE * Buffer, int32_t DeviceNum)
{
    int32_t HandleNumber;
    int32_t buf[11];            //DIRRECORDSIZE];
    int32_t RecordNo = 0, Char, dirattribute, Retval;
    int32_t offset, offset_dest;
    int32_t byte;

    /* Search for free handle and allocate it */
    if ((HandleNumber = Searchfreehandleallocate()) < 0)
        return (ERROR_OS_FILESYSTEM_NO_FREE_HANDLE);
    Handle[HandleNumber].Device = DeviceNum;
    Handle[HandleNumber].Mode = DIRECTORY_MODE + READ_MODE;
    /*Change to root directory */
    if ((ChangeToRootdirectory(HandleNumber)) < 0) {
        Freehandle(HandleNumber);
        return ERROR_OS_FILESYSTEM_INVALID_DIR_PATH;
    }
    /*Find the volume label record */
    do {
        if ((Retval = ReadDirectoryRecord(HandleNumber, RecordNo, (BYTE *) buf)) < 0) {
            Freehandle(HandleNumber);
            return ERROR_OS_FILESYSTEM_VOLUMELABEL_NOT_FOUND;
        }

        Char = 0;
        Char = GetChar((BYTE *) buf, &Char);
        /* If no volume id found then return */
        if (Char == 0) {
            Freehandle(HandleNumber);
            return ERROR_OS_FILESYSTEM_VOLUMELABEL_NOT_FOUND;
        }
        if (Char == 0xe5) {
            RecordNo++;
            continue;
        }
        dirattribute = FSGetByte((uint8_t *) buf, DIR_ATTRIBUTEOFFSET);

        if (!(dirattribute & READ_ONLY || dirattribute & SYSTEM || dirattribute & DIRECTORY)) {
            if (dirattribute & VOLUME_ID) {
                break;
            }
        }
        RecordNo++;

    } while (Retval != 0);

    /*If volume id found then copy it in passed buffer */
    offset = 0;
    offset_dest = 0;
    while (offset < 11) {
        byte = GetChar((BYTE *) buf, &offset);
        if (byte == 0x20) {
            PutByte(Buffer, '\0', offset_dest);
            break;
        }
        PutChar((BYTE *) Buffer, &offset_dest, byte);

    }
    PutByte(Buffer, '\0', offset_dest);

    Freehandle(HandleNumber);
    return SUCCESS;
}
