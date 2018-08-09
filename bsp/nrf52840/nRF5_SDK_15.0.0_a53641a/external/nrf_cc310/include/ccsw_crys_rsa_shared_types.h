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


#ifndef SW_CRYS_RSA_SHARED_TYPES_H
#define SW_CRYS_RSA_SHARED_TYPES_H

#ifdef __cplusplus
extern "C"
{
#endif


/** @file
 *  @brief This file contains the types for the CCSW RSA module.
 */

/************************ Defines ******************************/

/************************************************************************/
/* the following definitions are only relevant for RSA code on SW */
/************************************************************************/
/* Define the maximal allowed width of the exponentiation sliding window
in range 2...6. This define is actual for projects on soft platform.
To minimize code size use the minimum value. To optimize performance
choose the maximum value */

/* The valid key size in bits */
#define SW_CRYS_RSA_MIN_VALID_KEY_SIZE_VALUE_IN_BITS          512

#ifndef CRYS_NO_RSA_MAX_KEY_SIZE_4096_BIT_SUPPORT
#define SW_CRYS_RSA_MAX_VALID_KEY_SIZE_VALUE_IN_BITS         4096
#define SW_CRYS_RSA_MAX_KEY_GENERATION_SIZE_BITS             4096
#else
#ifndef CRYS_NO_RSA_MAX_KEY_SIZE_3072_BIT_SUPPORT
#define SW_CRYS_RSA_MAX_VALID_KEY_SIZE_VALUE_IN_BITS         3072
#define SW_CRYS_RSA_MAX_KEY_GENERATION_SIZE_BITS             3072
#else
#define SW_CRYS_RSA_MAX_VALID_KEY_SIZE_VALUE_IN_BITS         2048
#define SW_CRYS_RSA_MAX_KEY_GENERATION_SIZE_BITS             2048
#endif
#endif





/* Define the size of the exponentiation temp buffer, used in LLF_PKI exponentiation and NON DEPENDED on
   width of the sliding window. The size defined in units equaled to maximal RSA modulus size */
#define PKI_EXP_CONST_TEMP_BUFF_SIZE_IN_MODULUS_UNITS  7

#define PKI_EXP_SLIDING_WINDOW_MAX_VALUE  2

    /* The maximum buffer size for the 'H' value */
#define SW_CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS ((SW_CRYS_RSA_MAX_VALID_KEY_SIZE_VALUE_IN_BITS + 64UL ) / 32 )


/* definition of PKI_KEY_GEN_TEMP_BUFF_SIZE_WORDS IS DEPENDED on width of the sliding window*/
#if( PKI_EXP_SLIDING_WINDOW_MAX_VALUE > 2 )
#define PKI_KEY_GEN_TEMP_BUFF_SIZE_WORDS \
    ((4 + (1<<(PKI_EXP_SLIDING_WINDOW_MAX_VALUE-2))) * SW_CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS)
#else
#define PKI_KEY_GEN_TEMP_BUFF_SIZE_WORDS \
    (16 * SW_CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS)
#endif

#ifndef PKI_EXP_WINDOW_TEMP_BUFFER_SIZE_IN_MODULUS_UNITS
#define PKI_EXP_WINDOW_TEMP_BUFFER_SIZE_IN_MODULUS_UNITS  (3 + (1 << (PKI_EXP_SLIDING_WINDOW_MAX_VALUE-1)))
#endif


/* Define the size of the temp buffer, used in LLF_PKI exponentiation and DEPENDED on
   width of the sliding window in words */
#if (PKI_EXP_CONST_TEMP_BUFF_SIZE_IN_MODULUS_UNITS > PKI_EXP_WINDOW_TEMP_BUFFER_SIZE_IN_MODULUS_UNITS )
#define PKI_EXP_TEMP_BUFFER_SIZE_IN_WORDS  \
    (PKI_EXP_CONST_TEMP_BUFF_SIZE_IN_MODULUS_UNITS * SW_CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS + 2 )
#else
#define PKI_EXP_TEMP_BUFFER_SIZE_IN_WORDS  \
    (PKI_EXP_WINDOW_TEMP_BUFFER_SIZE_IN_MODULUS_UNITS * SW_CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS + 2 )
#endif

/* the RSA data type */
typedef struct SW_Shared_CRYS_RSAPrimeData_t {
    /* The aligned input and output data buffers */
    uint32_t DataIn[SW_CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS];
    uint32_t DataOut[SW_CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS];

    /* #include specific fields that are used by the low level */
    struct {
        union {
            struct { /* Temporary buffers used for the exponent calculation */
                uint32_t Tempbuff1[PKI_EXP_TEMP_BUFFER_SIZE_IN_WORDS];
                uint32_t Tempbuff2[SW_CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS * 2];
                /* Temporary buffer for self-test support */
                uint32_t TempBuffer[SW_CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS];
            }NonCrt;

            struct { /* Temporary buffers used for the exponent calculation */
                uint32_t Tempbuff1[PKI_EXP_TEMP_BUFFER_SIZE_IN_WORDS];
                uint32_t Tempbuff2[SW_CRYS_RSA_MAXIMUM_MOD_BUFFER_SIZE_IN_WORDS * 2];
            }Crt;
        }Data;
    }LLF;

}SW_Shared_CRYS_RSAPrimeData_t;




#ifdef __cplusplus
}
#endif
#endif
