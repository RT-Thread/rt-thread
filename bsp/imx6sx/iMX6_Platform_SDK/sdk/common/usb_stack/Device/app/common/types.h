/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 ******************************************************************************
 *
 * THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
 * IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 **************************************************************************//*!
 *
 * @file types.h
 *
 * @author 
 *
 * @version 
 *
 * @date 
 *
 * @brief The file contains definitions of datatypes.
 *
 *****************************************************************************/


#ifndef _TYPES_H
#define _TYPES_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stddef.h>
/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define LSB(a)      ((a)._byte.byte0)
#define MSB(a)      ((a)._byte.byte1)

#define LOWER_LSB(a)    ((a)._byte.byte0)
#define LOWER_MSB(a)    ((a)._byte.byte1)
#define UPPER_LSB(a)    ((a)._byte.byte2)
#define UPPER_MSB(a)    ((a)._byte.byte3)

#define _PTR_ *
#define _CODE_PTR_ *

#ifndef TRUE
#define FALSE 0 
#define TRUE 1
#endif

#define BYTESWAP16(x)	(uint_16)((((x) & 0xFF00) >> 0x8) | (((x) & 0xFF) << 0x8))
#define BYTESWAP32(val)	(uint_32)((BYTESWAP16((uint_32)(val) & (uint_32)0xFFFF) << 0x10) |  \
					(BYTESWAP16((uint_32)((val) >> 0x10))))

#ifndef LITTLE_ENDIAN
#define ieee_htons(x)		(uint_16)(x)
#define ieee_htonl(x)		(uint_32)(x)
#define ieee_ntohs(x)		(uint_16)(x)
#define ieee_ntohl(x)		(uint_32)(x)
#else
#define ieee_htons(x)		BYTESWAP16(x)
#define ieee_htonl(x)		BYTESWAP32(x)
#define ieee_ntohs(x)		BYTESWAP16(x)
#define ieee_ntohl(x)		BYTESWAP32(x)
#endif

#define UNUSED(x)   (void)x;
/******************************************************************************
 * Types
 *****************************************************************************/
typedef void _PTR_		pointer;          /* Machine representation of a pointer */
typedef unsigned char   uint_8;           /* 8-bit*/
typedef   signed char    int_8;           /* 8-bit*/

typedef unsigned short  uint_16;          /* 16-bit*/
typedef   signed short   int_16;          /* 16-bit*/

typedef unsigned long   uint_32;          /* 32-bit*/
typedef   signed long   int_32;           /* 32-bit*/

typedef unsigned char   boolean;          /* 8-bit*/

typedef uint_8*         uint_8_ptr;          /* ptr to 8-bit*/
typedef uint_16*        uint_16_ptr;         /* ptr to 16-bit */
typedef uint_32*        uint_32_ptr;         /* ptr to 32-bit*/

typedef uint_8_ptr      uchar_ptr;           /* ptr to 8-bit*/

/* definition of 8 bit word */
typedef union _BYTE
{
    uint_8 _byte;
    struct
    {
        unsigned b0:1;
        unsigned b1:1;
        unsigned b2:1;
        unsigned b3:1;
        unsigned b4:1;
        unsigned b5:1;
        unsigned b6:1;
        unsigned b7:1;
    }Bit;
} BYTE;

/* definition of 16 bit word */
typedef union _WORD
{
    uint_16 _word;
    struct
    {
        uint_8 byte1;
        uint_8 byte0;
    }_byte;
    struct
    {
        BYTE HighB;
        BYTE LowB;
    }_Byte;
} WORD;

/* definition of 32 bit word */
typedef union _DWORD
{
    uint_32 _dword;
    struct
    {
        uint_8 byte3;
        uint_8 byte2;
        uint_8 byte1;
        uint_8 byte0;
    }_byte;
    struct
    {
        uint_16 word1;
        uint_16 word0;
    }_word;
    struct
    {
        BYTE Byte3;
        BYTE Byte2;
        BYTE Byte1;
        BYTE Byte0;
    }_Byte;
    struct
    {
        WORD Word1;
        WORD Word0;
    }_Word;
} DWORD;

/******************************************************************************
 * Global Functions - None
 *****************************************************************************/

#endif            
