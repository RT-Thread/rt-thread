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
 $Archive: /Fatfs/FileSystem/Fat32/Utility/Convert_itoa.c $
 $Revision: 1 $                                       
 $Date: 9/18/03 11:52a $
 Description: Convert_itoa.c
 Notes:	
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
		File Includes
----------------------------------------------------------------------------*/
#include <types.h>
#include "fstypes.h"
#include "filesystem/fsapi.h"
#include "fat_internal.h"

/*----------------------------------------------------------------------------
>  Function Name: int32_t Convert_itoa(int32_t Number,uint8_t *string)

   FunctionType:  Reentrant

   Inputs:        1) Number
                  2) Pointer to string

   Outputs:       Length

   Description:   Arranges the file name as short file name in 8+3 format
<
----------------------------------------------------------------------------*/
int32_t Convert_itoa(int32_t Number, uint8_t * string)
{
    uint8_t Temp[12];
    int32_t i = 0, j = 0, Flag;
    int32_t Length = 0;

    while (Number != 0) {
        Flag = Number / 10;
        Temp[Length] = Number - (Flag * 10);
        Number = Flag;
        Length++;
    }
    j = Length - 1;
    for (i = 0; i < Length; i++) {
        string[i] = Temp[j] + 0x30;;
        j--;
    }
    return Length;
}

/*----------------------------------------------------------------------------
>  Function Name:  int32_t Changecase(int32_t filenameword)

   FunctionType:   Reentrant

   Inputs:         filenameword
   
   Outputs:        filenameword
      
   Description:    Changes the case 
----------------------------------------------------------------------------*/
int32_t Changecase(int32_t filenameword)
{
    if (filenameword >= 97 && filenameword <= 122)
        filenameword = filenameword - 32;
    else if (filenameword >= 65 && filenameword <= 90)
        filenameword = filenameword + 32;
    return (filenameword);
}

/*----------------------------------------------------------------------------
>  Function Name:  int32_t StrlengthW(uint8_t *filepath)

   FunctionType:   Reentrant

   Inputs:         pointer to filepath
                   
   Outputs:        Returns no. of characters in the string.(It considers the 
                   string as UNICODE.)
   
   Description:    Finds the no. of characters in the string i.e. length of the string. 
<
----------------------------------------------------------------------------*/
int32_t StrlengthW(uint8_t * filepath)
{
    int32_t strlength = 0, word, offset = 0;

    while (1) {
        if ((word = FSGetWord(filepath, offset)) == '\0')
            break;
        offset += 2;
        strlength++;
    }
    (void)word;
    return (strlength);
}

/*----------------------------------------------------------------------------
>  Function Name:  int32_t Strlength(uint8_t *filepath)

   FunctionType:   Reentrant

   Inputs:         pointer to filepath
                   
   Outputs:        Returns the no. of characters in the string.(It considers the 
                   string as DBCS.)
   
   Description:    Finds the no. of characters in the string i.e. length of the string.
<
----------------------------------------------------------------------------*/
int32_t Strlength(uint8_t * filepath)
{
    int32_t strlength = 0, offset = 0;
    int32_t Char;

    while (1) {
        Char = GetChar(filepath, &offset);
        if (Char == '\0')
            break;
        strlength++;
    }
    return (strlength);
}

/*----------------------------------------------------------------------------
>  Function Name:  RtStatus_t Strcpy(uint8_t *filepath, uint8_t *file_path1,int32_t length, int32_t index)

   FunctionType:   Reentrant

   Inputs:         1) pointer to filepath
                   2) pointer to file_path1
                   3) length
                   4) index
				   
   Outputs:        Returns SUCCESS or an error if function fails.
      
   Description:    This function copies the first string to second string.
<
----------------------------------------------------------------------------*/
RtStatus_t Strcpy(uint8_t * filepath, uint8_t * file_path1, int32_t length, int32_t index)
{
    int32_t Char, offset = index, offset_dest = 0;
    while (offset < length) {
        Char = GetChar(filepath, &offset);
        PutChar(file_path1, &offset_dest, Char);
        if (offset > (MAXFILENAME_CH - 1))
            break;
    }
    PutChar(file_path1, &offset_dest, 0);

    return SUCCESS;
}

/*----------------------------------------------------------------------------
>  Function Name:  RtStatus_t Strcpyw(uint8_t *filepath, uint8_t *file_path,int32_t length,int32_t index)

   FunctionType:   Reentrant

   Inputs:         1) pointer to filepath
                   2) pointer to file_path
                   3) length
                   4) index
				   
   Outputs:        Returns SUCCESS or an error if function fails.

   Description:    This function copies the first string to second string.
				   It considers the string as UNICODE.
<
----------------------------------------------------------------------------*/
RtStatus_t Strcpyw(uint8_t * filepath, uint8_t * file_path, int32_t length, int32_t index)
{
    int32_t word, Strlen, offset = index, offset_dest = 0;
    int32_t j;
    Strlen = (length - index) >> 1;

    if (Strlen > MAXFILENAME_CH)
        Strlen = MAXFILENAME_CH;

    for (j = 0; j < Strlen; j++) {
        word = FSGetWord(filepath, offset);
        PutWord(file_path, word, offset_dest);
        offset = offset + 2;
        offset_dest = offset_dest + 2;
    }
    PutWord(file_path, 0, offset_dest);

    return SUCCESS;
}

/*----------------------------------------------------------------------------
>  Function Name:  int32_t GetChar(uint8_t *Buffer,int32_t *offset)

   FunctionType:   Reentrant

   Inputs:         1) pointer to Buffer
                   2) offset 
                   
   Outputs:        Returns char of the given buffer at the given offset.
   
   Description:    This	function gets a character from the given string at the 
                   given offset and updates the offset accordingly.
<
----------------------------------------------------------------------------*/
int32_t GetChar(uint8_t * Buffer, int32_t * offset)
{
    int32_t Char;
    Char = FSGetByte(Buffer, *offset);
    *offset = *offset + 1;
    return Char;
}

/*----------------------------------------------------------------------------
>  Function Name:  int32_t GetCharW(uint8_t *Buffer,int32_t *offset)

   FunctionType:   Reentrant

   Inputs:         1) pointer to Buffer
                   2) offset 
                   
   Outputs:        Returns char of the given buffer at the given offset.
   
   Description:    This	function gets a word from the given Unicode string at the 
                   given offset and updates the offset accordingly.
<
----------------------------------------------------------------------------*/
int32_t GetCharW(uint8_t * Buffer, int32_t * offset)
{
    int32_t Word;
    Word = FSGetWord(Buffer, *offset);
    *offset = *offset + 2;
    return Word;
}

/*----------------------------------------------------------------------------
>  Function Name: void PutChar(uint8_t *Buffer,int32_t *offset,int32_t Char)

   FunctionType:  Reentrant

   Inputs:        1) Pointer to Buffer
                  2) Offset 
				  3) Char
                  
   Outputs:       Nil
   
   Description:   This function puts a character in the given string at given offset 
                  and updates the offset accordingly. 
----------------------------------------------------------------------------*/
void PutChar(uint8_t * Buffer, int32_t * offset, int32_t Char)
{
    PutByte(Buffer, Char, *offset);
    *offset = *offset + 1;
}

/*----------------------------------------------------------------------------
>  Function Name: void PutCharW(uint8_t *Buffer,int32_t *offset,int32_t Char)

   FunctionType:  Reentrant

   Inputs:        1) Pointer to Buffer
                  2) Offset 
				  3) Char
                  
   Outputs:       Nil
   
   Description:   This function puts a word in the given Unicode string at given offset 
                  and updates the offset accordingly. 
----------------------------------------------------------------------------*/
void PutCharW(uint8_t * Buffer, int32_t * offset, int32_t Char)
{
    PutWord(Buffer, Char, *offset);
    //PutByte(Buffer,Char,*offset);
    *offset = *offset + 2;
}

/*----------------------------------------------------------------------------
>  Function Name:  int32_t GetnameW(uint8_t *filepath,int32_t currentPosition)

   FunctionType:   Reentrant

   Inputs:         1) pointer to filepath
                   2) current position

   Outputs:        Returns current position.
   
   Description:    This function copies the string from current position to the 
                   directory separator or null character in the file path to 
                   another string called name.Current position is set to next 
                   directory separator or to end of file path. (It considers the string as UNICODE)
----------------------------------------------------------------------------*/
int32_t GetnameW(uint8_t * filepath, int32_t currentPosition)
{
    int32_t word;
    while (1) {
        word = FSGetWord(filepath, currentPosition);
        if (word == '/' || word == '\0')
            break;
        currentPosition += 2;
    }

    return (currentPosition);
}

/*----------------------------------------------------------------------------
>  Function Name:  int32_t Getname(uint8_t *filepath, int32_t currentPosition)

   FunctionType:   Reentrant

   Inputs:         1) pointer to filepath
				   2) current position

   Outputs:        Returns current position.
   
   Description:    This function copies the string from current position to the 
                   directory separator or null character in the file path to 
                   another string called name.Current position is set to next 
                   directory separator or to end of file path. (It considers the string as DBCS)
----------------------------------------------------------------------------*/
int32_t Getname(uint8_t * filepath, int32_t currentPosition)
{
    int Char;
    while (1) {
        Char = GetChar(filepath, &currentPosition);
        if (Char == '/' || Char == '\0')
            break;
    }

    return (currentPosition);
}

/*----------------------------------------------------------------------------
>  Function Name:  int32_t GetDirnameW(uint8_t *filepath,int32_t currentPosition)

   FunctionType:   Reentrant

   Inputs:         1) pointer to filepath
                   2) current position

   Outputs:        Returns current position.
   
   Description:    This function copies the string from current position to the 
                   directory separator or null character in the file path to 
                   another string called name.Current position is set to next 
                   directory separator or to end of file path. (It considers the string as UNICODE)
----------------------------------------------------------------------------*/
int32_t GetDirnameW(uint8_t * filepath, int32_t currentPosition)
{
    int32_t word;
    while (1) {
        word = GetCharW(filepath, &currentPosition);
        if (word == '/' || word == '\0')
            break;
    }

    return (currentPosition);
}

/*----------------------------------------------------------------------------
>  Function Name:  int32_t Extractfilename(uint8_t *filepath,int32_t strlength,int32_t *index)

   FunctionType:   Reentrant

   Inputs:         1) Pointer to filepath
                   2) String length
                   3) Index

   Outputs:        Returns String length
   
   Description:    This function copies the string from last directory separator 
                   to end of file to another string called filename.
----------------------------------------------------------------------------*/
int32_t Extractfilename(uint8_t * filepath, int32_t strlength, int32_t * index)
{
    int32_t currentposition = *index, strlen = 0;

    while (currentposition < strlength) {
        strlen = currentposition;
        currentposition = Getname(filepath, currentposition);
    }

    return strlen;
}

/*----------------------------------------------------------------------------
>  Function Name:  int32_t Extractfilenamew(uint8_t *filepath, int32_t *index)

   FunctionType:   Reentrant

   Inputs:         1) Pointer to filepath
                   2) Pointer to index

   Outputs:        Returns string length
   
   Description:    This function copies the string from last directory separator 
                   to end of file to another string called filename. It considers
				   the file name in UNICODE.
<
----------------------------------------------------------------------------*/
int32_t Extractfilenamew(uint8_t * filepath, int32_t * index)
{
    int32_t word, strlen;
    int32_t i;

    strlen = StrlengthW(filepath);

    // StrlenthW returns in terms of number of Wide characters = 2 bytes per character. 
    i = strlen << 1;

    while (i > *index) {
        word = FSGetWord(filepath, i);
        if (word == '/') {
            i += 2;
            break;
        }
        i -= 2;
    }

    return i;
}

/*----------------------------------------------------------------------------
>  Function Name:  int32_t Extractdirnamew(uint8_t *filepath,int32_t strlength,int32_t *index)

   FunctionType:   Reentrant

   Inputs:         1) Pointer to filepath
                   2) String length
                   3) Index

   Outputs:        Returns String length
   
   Description:    This function copies the string from last directory separator 
                   to end of file to another string called filename.
----------------------------------------------------------------------------*/
int32_t Extractdirnamew(uint8_t * filepath, int32_t strlength, int32_t * index)
{
    int32_t currentposition = *index, strlen = 0;

    while (currentposition < strlength) {
        strlen = currentposition;
        currentposition = GetDirnameW(filepath, currentposition);
    }

    return strlen;
}

/*----------------------------------------------------------------------------
>  Function Name:  RtStatus_t ExtractPathW(uint8_t *filepath,int32_t *index)

   FunctionType:   Reentrant

   Inputs:         1) Pointer to filepath
                   2) Pointer to index
				   
   Outputs:        Returns SUCCESS or an error if function fails.
      
   Description:    This function copies the string from first directory separator(\\)
                   to the end of string to the same string. It considers the 
                   string as UNICODE.
<
----------------------------------------------------------------------------*/
int32_t ExtractPathW(uint8_t * filepath, int32_t * index)
{
    int32_t word, Strlen, k = 0, offset = *index;

    Strlen = StrlengthW(filepath);
    while (1) {
        word = FSGetWord(filepath, offset);
        if (word == '/' || word == '\0')
            break;
        offset += 2;
        k++;
    }
    *index = offset + 2;
    if (k == Strlen)
        return END_OF_DIR_PATH;

    return SUCCESS;
}

/*----------------------------------------------------------------------------
>  Function Name:  RtStatus_t ExtractPath(uint8_t *filepath,int32_t *index)

   FunctionType:   Reentrant

   Inputs:         1) Pointer to filepath
                   2) Pointer to index
				   
   Outputs:        Returns SUCCESS or an error if function fails.

   Description:    This function copies the string from first directory separator(\\)
                   to the end of string to the same string. It considers the 
                   string as DBCS.
<
----------------------------------------------------------------------------*/
int32_t ExtractPath(uint8_t * filepath, int32_t * index)
{
    int32_t Strlen, offset = *index;
    int32_t Char;
    Strlen = Strlength(filepath);
    while (1) {
        Char = GetChar(filepath, &offset);
        if (Char == '/' || Char == '\0')
            break;
    }
    *index = offset;
    if (offset >= Strlen)
        return END_OF_DIR_PATH;

    return SUCCESS;
}

/*----------------------------------------------------------------------------
>  Function Name: int32_t DiscardTrailigPeriods(uint8_t *Buffer,int32_t length,int32_t index,int32_t Flag)

   FunctionType:  Reentrant

   Inputs:        1) Pointer to Buffer
                  2) Length
                  3) Index
                  4) Flag

   Outputs:       Returns length

   Description:   This function removes all the trailing periods from the given string. 
<
-----------------------------------------------------------------------------*/
int32_t DiscardTrailigPeriods(uint8_t * Buffer, int32_t length, int32_t index, int32_t Flag)
{
    int32_t Char, strlen, offset = index;
    int32_t dotfound = 0;

    if (Flag)
        strlen = length - 1;
    else
        strlen = length;
    while (offset < strlen) {
        Char = GetChar(Buffer, &offset);
        if (Char == '.') {
            dotfound++;
        } else {
            dotfound = 0;
        }
    }
    length = (length - dotfound);

    return length;
}

/*----------------------------------------------------------------------------
>  Function Name: int32_t  DiscardTrailigPeriodsw(uint8_t *Buffer,int32_t length,int32_t index)

   FunctionType:  Reentrant

   Inputs:        1) Pointer to Buffer
                  2) Length
                  3) Index

   Outputs:       Returns length

   Description:   This function removes all the trailing periods from the given string. 
<                 It considers the string in UNICODE.
-----------------------------------------------------------------------------*/
int32_t DiscardTrailigPeriodsw(uint8_t * Buffer, int32_t length, int32_t index)
{
    int32_t Char, offset = index;
    int32_t dotfound = 0;

    while (offset < length) {
        Char = FSGetWord(Buffer, offset);
        if (Char == '.') {
            dotfound++;
        } else {
            dotfound = 0;
        }
        offset += 2;
    }
    length = (length - (dotfound << 1));
    return length;
}

////////////////////////////////////////////////////////////////////////////////
//! \brief      Returns a byte from buffer.
//!
//! \fntype     Function
//!
//! As per the offset given this function returns byte from buffer.
//!
//! \param[in]  buffer          Pointer to a buffer.
//! \param[in]  iOffsetInUint8  Offset in bytes to a byte in that buffer.
//!
//! \retval int32_t             A byte that was in buffer at offset iOffsetInUint8.
//!
////////////////////////////////////////////////////////////////////////////////
int32_t FSGetByte(uint8_t * buffer, int32_t iOffsetInUint8)
{
    int32_t temp;
    temp = ((uint8_t) buffer[iOffsetInUint8]);
    return temp;
}

////////////////////////////////////////////////////////////////////////////////
//! \brief      Returns a u16 from buffer.
//!
//! \fntype     Function
//!
//! As per the offset given this function returns u16 from buffer.
//!
//! \param[in]  buffer          Pointer to a buffer.
//! \param[in]  iOffsetInUint8  Offset in bytes to a u16 in that buffer.
//!
//! \retval int32_t             A u16 that was in buffer at offset iOffsetInUint8.
//!
////////////////////////////////////////////////////////////////////////////////
int32_t FSGetWord(uint8_t * buffer, int32_t iOffsetInUint8)
{
    int32_t temp;
    temp =
        (((uint32_t) buffer[iOffsetInUint8]) |
         ((((uint32_t) buffer[iOffsetInUint8 + 1]) & 0xff) << 8));
    return temp;
}

////////////////////////////////////////////////////////////////////////////////
//! \brief      Returns a u32 from buffer.
//!
//! \fntype     Function
//!
//! As per the offset given this function returns u32 from buffer.
//!
//! \param[in]  buffer          Pointer to a buffer.
//! \param[in]  iOffsetInUint8  Offset in bytes to a u32 in that buffer.
//!
//! \retval int32_t             A u32 that was in buffer at offset iOffsetInUint8.
//!
////////////////////////////////////////////////////////////////////////////////
uint32_t FSGetDWord(uint8_t * buffer, int32_t iOffsetInUint8)
{
    uint32_t temp;
    temp =
        (((uint32_t) buffer[iOffsetInUint8]) |
         ((((uint32_t) buffer[iOffsetInUint8 + 1]) & 0xff) << 8) |
         ((((uint32_t) buffer[iOffsetInUint8 + 2]) & 0xff) << 16) |
         ((((uint32_t) buffer[iOffsetInUint8 + 3]) & 0xff) << 24));
    return temp;
}

/*----------------------------------------------------------------------------
>  Function Name: void PutByte(uint8_t *buffer, uint8_t byte,int32_t Offset)

   FunctionType:  Function

   Inputs:        1) Pointer to buffer
                  2) byte
                  3) Offset

   Outputs:       None

   Description:   Puts byte into buffer at given offset.
<
----------------------------------------------------------------------------*/
void PutByte(uint8_t * buffer, uint8_t byte, int32_t Offset)
{
    buffer[Offset] = (uint8_t) (byte & 0xff);
}

/*----------------------------------------------------------------------------
>  Function Name: void PutWord(uint8_t *buffer, int32_t word, int32_t Offset)

   FunctionType:  Function

   Inputs:        1) Pointer to buffer
                  2) word
                  3) Offset

   Outputs:       None

   Description:   Puts word into byte buffer starting from given offset.
<
----------------------------------------------------------------------------*/
void PutWord(uint8_t * buffer, int32_t word, int32_t Offset)
{
    buffer[Offset] = (uint8_t) (word & 0xff);
    buffer[Offset + 1] = (uint8_t) ((word >> 8) & 0xff);
}

/*----------------------------------------------------------------------------
>  Function Name: void PutDword(uint8_t *buffer, int32_t dword, int32_t Offset)

   FunctionType:  Function

   Inputs:        1) Pointer to buffer
                  2) dword
                  3) Offset

   Outputs:       None

   Description:   Puts dword into byte buffer starting from given offset.
<
----------------------------------------------------------------------------*/
void PutDword(uint8_t * buffer, uint32_t dword, int32_t Offset)
{
    buffer[Offset] = (uint8_t) (dword & 0xff);
    buffer[Offset + 1] = (uint8_t) ((dword >> 8) & 0xff);
    buffer[Offset + 2] = (uint8_t) ((dword >> 16) & 0xff);
    buffer[Offset + 3] = (uint8_t) ((dword >> 24) & 0xff);
}
