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
 $Archive: /Fatfs/FileSystem/Fat32/higherapi/Longfilename.c $                                        
 $Revision: 9 $                                       
 $Date: 10/01/03 2:23p $                                           
 Description: Longfilename.c
 Notes:	This file read provides higherlevel API function to provide long file name.
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
		File Includes
----------------------------------------------------------------------------*/
#include <types.h>
#include "fstypes.h"
#include "fat_internal.h"
#include "filesystem/fsapi.h"
#include "bootsecoffset.h"
#include "diroffset.h"
#include <string.h>

#define READ_CASE_EXTENSION_BYTE    0x0C
#define LOWER_CASE_BASENM_BIT3      0x08
#define LOWER_CASE_EXTNM_BIT4       0x10
#define SHORTNM_MAX_FILE_LEN        12

static void GeneratefilenameTail(uint8_t * shortfilename, int32_t i, int32_t Flag);

/*----------------------------------------------------------------------------
>  Function Name:  int32_t ConstructLongFileName(int32_t HandleNumber, int32_t RecordNumber, int32_t *LFNBuffer)

   FunctionType:   Reentrant

   Inputs:         1) Handle number
                   2) Record Number
				   3) Pointer to file name buffer
   
   Outputs:        Returns Length of the Long file name string
      
   Description:    Provides long file name
----------------------------------------------------------------------------*/
int32_t ConstructLongFileName(int32_t HandleNumber, int32_t RecordNumber, int8_t * LFNBuffer)
{
    int32_t offset, Dirattribute, Signature;
    int32_t i = 1, j;
    uint8_t Buffer[36];
    int32_t LFNStringOffset = 0;
    uint32_t unicodeWord;

    RecordNumber--;

    if (RecordNumber < 0) {
        PutWord((uint8_t *) LFNBuffer, 0, 0);
        return 0;
    }
    while (1) {
        if (RecordNumber >= 0) {
            memset(Buffer, 0, 36);
            if (ReadDirectoryRecord(HandleNumber, RecordNumber, Buffer) < 0)
                return ERROR_OS_FILESYSTEM_INVALID_RECORD_NUMBER;
            RecordNumber--;
            if (i == 1) {
                //only occurs once per file (i only equals 1 the first iteration of the loop).
                Signature = FSGetByte((uint8_t *) Buffer, LDIRORDOFFSET);
                if ((Signature & 0x000000FF) != 0x00000001
                    && (Signature & 0x000000FF) != 0x00000041) {
                    //in this case there is no LFN entry
                    PutWord((uint8_t *) LFNBuffer, 0, LFNStringOffset);
                    return LFNStringOffset;
                }
            }
            Dirattribute = FSGetByte((uint8_t *) Buffer, DIR_ATTRIBUTEOFFSET);
            if (Dirattribute != 0x0000000F) {
                PutWord((uint8_t *) LFNBuffer, 0, LFNStringOffset);
                return LFNStringOffset;
            }
        } else {
            PutWord((uint8_t *) LFNBuffer, 0, LFNStringOffset);
            return LFNStringOffset;
        }
        offset = LDIRNAME1OFFSET;
        for (j = 0; j < 5; j++) {
            //5 chars
            if (LFNStringOffset >= MAX_FILENAME_LENGTH * 2) {
                LFNStringOffset = MAX_FILENAME_LENGTH * 2;
                return LFNStringOffset;
            }
            unicodeWord = GetUnicodeWord(Buffer, offset);
            PutWord((uint8_t *) LFNBuffer, unicodeWord, LFNStringOffset);
            LFNStringOffset += 2;
            offset += 2;
        }
        offset = LDIRNAME2OFFSET;
        for (j = 0; j < 6; j++) {
            //6 chars
            if (LFNStringOffset >= MAX_FILENAME_LENGTH * 2) {
                LFNStringOffset = MAX_FILENAME_LENGTH * 2;
                return LFNStringOffset;
            }
            unicodeWord = GetUnicodeWord(Buffer, offset);
            PutWord((uint8_t *) LFNBuffer, unicodeWord, LFNStringOffset);
            LFNStringOffset += 2;
            offset += 2;
        }
        offset = LDIRNAME3OFFSET;
        for (j = 0; j < 2; j++) {
            //2 chars
            if (LFNStringOffset >= MAX_FILENAME_LENGTH * 2) {
                LFNStringOffset = MAX_FILENAME_LENGTH * 2;
                return LFNStringOffset;
            }
            unicodeWord = GetUnicodeWord(Buffer, offset);
            PutWord((uint8_t *) LFNBuffer, unicodeWord, LFNStringOffset);
            LFNStringOffset += 2;
            offset += 2;
        }
        i++;
    }                           // while(1)            
}

/*----------------------------------------------------------------------------
>  Function Name:  int32_t GetUnicodeWord(uint8_t *Buffer,int32_t LFNOffset)

   FunctionType:   Reentrant

   Inputs:         1) Pointer to Buffer
                   2) Long file name offset
   
   Outputs:        Returns 0(Null Terminator) or Unicode Word
      
   Description:    Provides Unicode Word from Unicode Character
----------------------------------------------------------------------------*/
int32_t GetUnicodeWord(uint8_t * Buffer, int32_t LFNOffset)
{
    //each Unicode char is 2 bytes
    int32_t rtn = 0;
    rtn = FSGetWord(Buffer, LFNOffset); //each unicode character is stored in little endian so reverse it
    if (rtn == 0x00FFFF) {
        rtn = 0;                //null terminator for unicode string
    }
    return rtn;
}

/*----------------------------------------------------------------------------
>  Function Name:  RtStatus_t ArrangeLongFileName(int32_t HandleNumber,uint8_t *filename,int32_t count, int32_t chksum)

   FunctionType:   Reentrant

   Inputs:         1) Handle number
				   2) Pointer to file name
				   3) Count 
				   4) Chksum

   Outputs:        Returns SUCCESS or an error code if function fails
      
   Description:    Arranges the given long file name. 
----------------------------------------------------------------------------*/
RtStatus_t ArrangeLongFileName(int32_t HandleNumber, uint8_t * filename, int32_t count,
                               int32_t chksum)
{
    int32_t offset, Flag;
    RtStatus_t Retval;
    int32_t wordno = 0, Ldirorder, word;
    uint8_t Longdirname[32];

    count--;
    Flag = count;

    PutByte(Longdirname, LONGDIRATTRIBUTE, LDIRATTRIOFFSET);    //long directory attribute
    PutByte(Longdirname, 0, LDIRTYPEOFFSET);    //directory type
    PutByte(Longdirname, chksum, LDIRCHKSUMOFFSET); //chksum
    PutWord(Longdirname, 0, DIR_FSTCLUSLOOFFSET);   //long directory first cluster

    while (Flag >= 1) {
        if (Flag == count)
            Ldirorder = (Flag | 0x40);
        else
            Ldirorder = Flag;
        PutByte(Longdirname, Ldirorder, LDIRORDOFFSET);

        offset = LDIRNAME1OFFSET;
        wordno = ((Flag - 1) * LONGDIRCH_PER_RECORD) << 1;

        while (offset != DIRRECORDSIZE) {
            word = FSGetWord(filename, wordno);
            PutWord(Longdirname, word, offset);

            wordno += 2;
            offset = offset + 2;
            /* if all words of longdir firstname field is occupied, check for 
               longdir secondname field */
            if (offset == LDIRATTRIOFFSET)
                offset = LDIRNAME2OFFSET;

            /* if all words of longdir secondname field is occupied  check for 
               longdir thirdname field */
            if (offset == LDIRFSTCLUSNOOFFSET)
                offset = LDIRNAME3OFFSET;

            if (word == '\0') {
                word = 0xFFFF;
                while (offset != DIRRECORDSIZE) {
                    if (offset == LDIRATTRIOFFSET)
                        offset = LDIRNAME2OFFSET;
                    if (offset == LDIRFSTCLUSNOOFFSET)
                        offset = LDIRNAME3OFFSET;
                    PutWord(Longdirname, word, offset);
                    offset += 2;
                }
            }

            /* if all words of longdir thirdname field is occupied check for next sub component of longdir entry */
        }                       // while(offset !=  DIRRECORDSIZE)

        if (Handle[HandleNumber].StartingCluster != 0) {
            if ((Retval = (RtStatus_t) Fwrite(HandleNumber, Longdirname, DIRRECORDSIZE)) <= 0)
                return Retval;
        } else {
            if ((Retval =
                 FSWriteSector(Handle[HandleNumber].Device, Handle[HandleNumber].CurrentSector,
                               Handle[HandleNumber].BytePosInSector, Longdirname, 0, DIRRECORDSIZE,
                               WRITE_TYPE_RANDOM)) < 0)
                return Retval;

            offset = (Handle[HandleNumber].CurrentOffset >> 5) + 1;
            SetcurrentPos(HandleNumber, offset);
        }
        Flag--;
    }                           // while(Flag>=1)

    return (SUCCESS);
}

/*----------------------------------------------------------------------------
>  Function Name: void Setshortfilename(int32_t HandleNumber,uint8_t *Buffer,uint8_t *shortfilename)

   FunctionType:  Reentrant

   Inputs:        1) Handle number
                  2) Pointer to file name or directory Buffer
                  3) Pointer to ShortName directory Buffer

   Outputs:       Nil

   Description:   Arranges the file name as short file name in 8+3 format
<
----------------------------------------------------------------------------*/
void Setshortfilename(int32_t HandleNumber, uint8_t * Buffer, uint8_t * shortfilename)
{
    uint8_t UpperCaseBuffer[256];
    int32_t byte = 0;
    int32_t i = 0;
    int32_t j = 0;
    int32_t k = 0;
    int32_t count = 0;
    int32_t Flag;
    int32_t Strlen;
    int32_t RecordNum = 0;
    RtStatus_t longFilenameFits8_3;

    // Get the string length in 2-byte characters, convert it to a byte count.
    Strlen = StrlengthW((uint8_t *) Buffer);
    Strlen = Strlen << 1;

    // Convert to OEM (1-byte character string) and convert to all uppercase.
    UnicodeToOEM((uint8_t *) Buffer, (uint8_t *) UpperCaseBuffer, Strlen, 0);
    Uppercase((uint8_t *) UpperCaseBuffer);

    // Check to see if OEM+UPPERCASE converted string already conforms to 8.3 short filename standard.
    // Note that IsShortNameValid() expects one-byte character strings as input.
    longFilenameFits8_3 = IsShortNameValid(UpperCaseBuffer, (Strlen >> 1), 0);
    if (longFilenameFits8_3 == SUCCESS) {
        // The name conforms, so copy it into the shortfilename buffer and exit.
        i = 0;
        while ((byte = FSGetByte(UpperCaseBuffer, i)) != '\0') {
            PutByte(shortfilename, byte, i);
            i++;
        }
        PutByte(shortfilename, '\0', i);
        return;
    }

    /* strip all leading and embedded spaces from the long name */
    /* strip all leading periods from the long file name */
    while ((byte = FSGetByte(UpperCaseBuffer, j)) != '\0') {
        if (byte == '.')
            count++;

        j++;
    }

    j = 0;
    /* strip all leading and embedded spaces from the long name */
    /* strip all leading periods from the long file name */
    while ((byte = FSGetByte(UpperCaseBuffer, i)) != '\0') {
        if (byte == '.') {
            if (count > 1)
                count--;
            else {
                if (j != 0) {
                    PutByte(UpperCaseBuffer, byte, j);
                    j++;
                } else
                    count--;
            }
        }
        if (byte != 0x20 && byte != 0x2E) {
            if (byte < 0x20) {
                byte = '_';
            } else {
                for (k = 0; k < SHORTNAMERES_CH; k++) {
                    if (byte == Short_NameRes_Ch[k]) {
                        byte = '_';
                        break;
                    }
                }

                if ('_' != byte) {

                    for (k = 0; k < LONGNAMERES_CH; k++) {

                        if (byte == Long_NameRes_Ch[k]) {
                            byte = '_';
                            break;
                        }

                    }           /* for */

                }
                /* if */
            }                   /* else */

            PutByte(UpperCaseBuffer, byte, j);
            j++;
        }
        i++;
    }
    PutByte(UpperCaseBuffer, 0, j);
    /* convert the filename to fit in 8+3 format */
    i = 0;
    while ((byte = FSGetByte(UpperCaseBuffer, i)) != '.' && i < 8 && byte != '\0') {
        PutByte(shortfilename, byte, i);
        i++;
    }

    PutByte(shortfilename, 0, i);
    if (count != 0) {
        while ((byte = FSGetByte(UpperCaseBuffer, i)) != '.') {
            i++;
        }
        if (i > 8)
            Flag = 8;
        else
            Flag = i;

        j = i + 2;
        if (j > 8)
            j = 8;
        count = 0;
        while ((byte = FSGetByte(UpperCaseBuffer, i)) != '\0' && count < 4) {
            PutByte(shortfilename, byte, j);
            i++;
            j++;
            count++;
        }
        PutByte(shortfilename, 0, j);
    } else
        Flag = Strlength(shortfilename);

    /* check if the file name exists then add file name tail */
    i = 1;
    if (Flag > 6)
        Flag = 6;
    PutByte(shortfilename, '~', Flag);
    PutByte(shortfilename, '1', (Flag + 1));

    Strlen = Strlength(shortfilename);
    while (Searchdirectory
           (HandleNumber, shortfilename, kDBCSEncoding, 0, (Strlen + 1), 0, Buffer, 1,
            &RecordNum) >= 0) {
        i++;
        GeneratefilenameTail(shortfilename, i, Flag);
    }
}

/*----------------------------------------------------------------------------
>  Function Name: void GeneratefilenameTail(uint8_t *shortfilename,int32_t i,int32_t Flag)

   FunctionType:  Reentrant

   Inputs:        1) pointer to shortfilename
                  2) i
                  3) Flag

   Outputs:       Nil

   Description:   Puts the given no. i in the given filename at the position 
                  indicated by the Flag.
<
----------------------------------------------------------------------------*/
void GeneratefilenameTail(uint8_t * shortfilename, int32_t i, int32_t Flag)
{
    int32_t length, count, j;
    uint8_t string[30];

    length = Convert_itoa(i, (uint8_t *) string);
    count = Flag - length + 1;

    PutByte(shortfilename, '~', count);
    for (j = 0; j < length; j++) {
        count++;
        PutByte(shortfilename, string[j], count);
    }

}

/*----------------------------------------------------------------------------
>  Function Name: RtStatus_t IsShortNameValid(uint8_t *Buffer,int32_t length,int32_t index)

   FunctionType:  Reentrant

   Inputs:        1) Pointer to Buffer
                  2) Length
                  3) Index  
                  
   Outputs:       Returns SUCCESS, 1 (OK but reserved) or an error code if error occurs

   Description:   This function checks whehter the file name will fit in 8+3 format
                  and it does not contain any restricted characters. 
<
----------------------------------------------------------------------------*/
RtStatus_t IsShortNameValid(uint8_t * Buffer, int32_t length, int32_t index)
{
    RtStatus_t Flag = (RtStatus_t) 1;   //Set value to OK - reserved.
    int32_t count = 0, i, j, Char;
    int32_t strlen, offset = index;

    strlen = length - index;
    if (strlen > 12)
        return (RtStatus_t) Flag;

    else {
        for (i = 0; i < strlen; i++) {
            Char = GetChar(Buffer, &offset);
            if (Char == 0x2e) {
                count++;
            }
            if (count > 1)
                return Flag;

            for (j = 0; j < SHORTNAMERES_CH; j++) {
                if (Char < 0x20)
                    return ERROR_OS_FILESYSTEM_ILLEGAL_FILENAME_CHARA;
                if (Char == Short_NameRes_Ch[j])
                    return Flag;
                if (Char == 0x20)
                    return Flag;
            }
            for (j = 0; j < LONGNAMERES_CH; j++) {
                if (Char == Long_NameRes_Ch[j])
                    return ERROR_OS_FILESYSTEM_ILLEGAL_FILENAME_CHARA;
            }
        }
        if (count == 0 && strlen > 8)
            return Flag;

        if (count == 1) {
            if ((Char = FSGetByte(Buffer, index)) == '.')
                return Flag;

            i = 0;
            offset = index;
            while ((Char = GetChar(Buffer, &offset)) != '.') {
                i++;
            }
            if (i > 8)
                return Flag;
            count = 0;
            while (offset < length) {
                Char = GetChar(Buffer, &offset);
                count++;
            }
            if (count > 3)
                return Flag;
        }

    }                           // else     

    return SUCCESS;
}

/*----------------------------------------------------------------------------

>  Function Name:  void ArrangeFileName(uint8_t *Buffer,uint8_t *ShortNameDir)

   FunctionType:  Reentrant

   Inputs:        1)Pointer to file name or directory
                  2)Pointer to ShortName directory Buffer

   Outputs:       Nil

   Description:   Arranges the file name as short file name in 8+3 format
<
----------------------------------------------------------------------------*/
void ArrangeFileName(uint8_t * Buffer, uint8_t * ShortNameDir)
{
    int32_t FName = 0, i = 0, j = 0, Length = 0;

    if ((FName = FSGetByte(Buffer, 0)) != 0x2e) {
        Uppercase((uint8_t *) Buffer);
        Length = Strlength((uint8_t *) Buffer);
        for (i = Length; i < 12; i++) {
            PutByte(Buffer, i, 0x20);
        }
    }

    else
        memcpy(ShortNameDir, Buffer, 12);

    i = 0;
    if (FName != 0x2e) {
        while ((FName = FSGetByte(Buffer, i)) != '\0') {
            if ((i == 0) && (FName == 0xe5))
                FName = 0x05;
            if (FName == '.') {
                i++;
                while ((FName = FSGetByte(Buffer, i + j)) != '\0') {
                    PutByte(ShortNameDir, FName, 8 + j);
                    j++;
                }
                break;
            }
            PutByte(ShortNameDir, FName, i);
            i++;
        }
    }
}
