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
 $Archive: /Fatfs/FileSystem/FSUnicode.c $                                        
 $Revision: 10 $                                       
 $Date: 9/13/03 7:07p $                                           
 Description: FSUnicode.c
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
		Global Declarations
----------------------------------------------------------------------------*/
const uint8_t Long_NameRes_Ch[10] = { 0x22, 0x2A, 0x2F, 0x3A, 0x3C, 0x3E, 0x3F, 0x5C, 0x7C };
const uint8_t Short_NameRes_Ch[6] = { 0x2B, 0x2C, 0x3B, 0x3D, 0x5B, 0x5D };

/*----------------------------------------------------------------------------
>  Function Name:  void DBCStoUnicode(uint8_t *filepath,uint8_t *buf,int32_t index,int32_t length)

   FunctionType:   Reentrant

   Inputs:         1) Pointer to file name
				   2) Pointer to buffer
				   3) Index   (starting point for string)
                   4) Length  (Ending point for string)

  Outputs:         Nil
     
  Description:     Converts the given DBCS string to kUTF16Encoding.
<
----------------------------------------------------------------------------*/
void DBCStoUnicode(uint8_t * filepath, uint8_t * buf, int32_t index, int32_t length)
{
    int32_t offset = 0, word = 0, i;
    int32_t Byte;

    for (i = index; i < length; i++) {
        Byte = FSGetByte(filepath, i);
        if (Byte == '/')
            Byte = 0;
        PutByte((uint8_t *) & word, Byte, 0);
        PutWord(buf, word, offset);
        offset += 2;
    }
    PutWord(buf, 0, offset);
}

/*----------------------------------------------------------------------------
>  Function Name:  void UnicodeToOEM(uint8_t *file,uint8_t *shortname,int32_t length,int32_t index)

   FunctionType:   Reentrant

   Inputs:         1) Pointer to file name
                   2) Pointer to Character
                   3) Length  (Ending point for string)
                   4) Index   (strating point for string)
   
   Outputs:        None

   Description:    Converts the given UTF16 string to OEM.
<
-----------------------------------------------------------------------------*/
void UnicodeToOEM(uint8_t * file, uint8_t * shortname, int32_t length, int32_t index)
{
    int32_t offset = 0, j, k = 0;
    int32_t word = 0;

    offset = index;
    while (offset < length) {
        word = FSGetWord(file, offset);
        for (j = 0; j < SHORTNAMERES_CH; j++) {
            if (word == Short_NameRes_Ch[j])
                word = 0x5F;
        }
        if ((word & 0x00FF) == 0)   //if the unicode was like 0x6700 or 0xXX00.
            word = 0x5F;
        PutByte(shortname, word, k);
        offset += 2;
        k++;
    }
    PutByte(shortname, 0, k);
}

/*----------------------------------------------------------------------------
>  Function Name:  void DBCStoTwoByteString(uint8_t *filename,uint8_t *string,int32_t length,int32_t index)

   FunctionType:   Reentrant

   Inputs:         1) Pointer to filename
                   2) Pointer to string 
                   3) Length
                   4) Index
                   
   Outputs:        Nil
      
   Description:    This function converts each character of the given string in two 
                   byte character and stores it in the second string.
<
----------------------------------------------------------------------------*/
void DBCStoTwoByteString(uint8_t * filename, uint8_t * string, int32_t length, int32_t index)
{
    int32_t Char, word = 0;
    int32_t i;
    int32_t offset = 0, offset_dest = 0;

    offset = index;
    for (i = index; i < length; i++) {
        if ((Char = GetChar(filename, &offset)) < 127)  //0x80
        {
            word = 0;
            PutByte((uint8_t *) & word, Char, 0);
        } else
            word = Char;
        PutWord(string, word, offset_dest);
        offset_dest += 2;
    }
    PutWord(string, 0, offset_dest);
}
