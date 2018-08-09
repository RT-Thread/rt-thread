/**************************************************************************************
* Copyright (c) 2016-2017, ARM Limited or its affiliates. All rights reserved         *
*                                                                                     *
* This file and the related binary are licensed under the following license:          *
*                                                                                     *
* ARM Object Code and Header Files License, v1.0 Redistribution.                      *
*                                                                                     *
* Redistribution and use of object code, header files, and documentation, without     *
* modification, are permitted provided that the following conditions are met:         *
*                                                                                     *
* 1) Redistributions must reproduce the above copyright notice and the                *
*    following disclaimer in the documentation and/or other materials                 *
*    provided with the distribution.                                                  *
*                                                                                     *
* 2) Unless to the extent explicitly permitted by law, no reverse                     *
*    engineering, decompilation, or disassembly of is permitted.                      *
*                                                                                     *
* 3) Redistribution and use is permitted solely for the purpose of                    *
*    developing or executing applications that are targeted for use                   *
*    on an ARM-based product.                                                         *
*                                                                                     *
* DISCLAIMER. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND                  *
* CONTRIBUTORS "AS IS." ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT             *
* NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT,        *
* AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE          *
* COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED            *
* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR              *
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF              *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING                *
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS                  *
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                        *
**************************************************************************************/


/*!
@file
@brief This file contains the platform dependent definitions and types.
@defgroup ssi_pal_types CryptoCell PAL platform dependant types
@{
@ingroup ssi_pal
*/

#ifndef SSI_PAL_TYPES_H
#define SSI_PAL_TYPES_H

#include "ssi_pal_types_plat.h"

/*! Boolean definition.*/
typedef enum {
    /*! Boolean false definition.*/
    SASI_FALSE = 0,
    /*! Boolean true definition.*/
    SASI_TRUE = 1
} SaSiBool;

/*! Success definition. */
#define SASI_SUCCESS              0UL
/*! Failure definition. */
#define SASI_FAIL         1UL

/*! Defintion of 1KB in bytes. */
#define SASI_1K_SIZE_IN_BYTES   1024
/*! Defintion of number of bits in a byte. */
#define SASI_BITS_IN_BYTE   8
/*! Defintion of number of bits in a 32bits word. */
#define SASI_BITS_IN_32BIT_WORD 32
/*! Defintion of number of bytes in a 32bits word. */
#define SASI_32BIT_WORD_SIZE    (sizeof(uint32_t))

/*! Success (OK) defintion. */
#define SASI_OK   SASI_SUCCESS

/*! Macro that handles unused parameters in the code (to avoid compilation warnings).  */
#define SASI_UNUSED_PARAM(prm)  ((void)prm)

/*! Maximal uint32 value.*/
#define SASI_MAX_UINT32_VAL     (0xFFFFFFFF)


/* Minimum and Maximum macros */
#ifdef  min
/*! Definition for minimum. */
#define CRYS_MIN(a,b) min( a , b )
#else
/*! Definition for minimum. */
#define CRYS_MIN( a , b ) ( ( (a) < (b) ) ? (a) : (b) )
#endif

#ifdef max
/*! Definition for maximum. */
#define CRYS_MAX(a,b) max( a , b )
#else
/*! Definition for maximum. */
#define CRYS_MAX( a , b ) ( ( (a) > (b) ) ? (a) : (b) )
#endif

/*! Macro that calculates number of full bytes from bits (i.e. 7 bits are 1 byte). */
#define CALC_FULL_BYTES(numBits)        (((numBits) + (SASI_BITS_IN_BYTE -1))/SASI_BITS_IN_BYTE)
/*! Macro that calculates number of full 32bits words from bits (i.e. 31 bits are 1 word). */
#define CALC_FULL_32BIT_WORDS(numBits)      (((numBits) + (SASI_BITS_IN_32BIT_WORD -1))/SASI_BITS_IN_32BIT_WORD)
/*! Macro that calculates number of full 32bits words from bytes (i.e. 3 bytes are 1 word). */
#define CALC_32BIT_WORDS_FROM_BYTES(sizeBytes)  (((sizeBytes) + SASI_32BIT_WORD_SIZE - 1) / SASI_32BIT_WORD_SIZE)
/*! Macro that round up bits to 32bits words. */
#define ROUNDUP_BITS_TO_32BIT_WORD(numBits)     (CALC_FULL_32BIT_WORDS(numBits)*SASI_BITS_IN_32BIT_WORD)
/*! Macro that round up bits to bytes. */
#define ROUNDUP_BITS_TO_BYTES(numBits)      (CALC_FULL_BYTES(numBits)*SASI_BITS_IN_BYTE)
/*! Macro that round up bytes to 32bits words. */
#define ROUNDUP_BYTES_TO_32BIT_WORD(numBytes)   (SASI_32BIT_WORD_SIZE*(((numBytes)+SASI_32BIT_WORD_SIZE-1)/SASI_32BIT_WORD_SIZE))


/**
@}
 */
#endif
