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
@brief This file contains all of the enums and definitions that are used for the
       CRYS POLY APIs, as well as the APIs themselves.
@defgroup crys_poly CryptoCell POLY APIs
@{
@ingroup cryptocell_api

*/
#ifndef CRYS_POLY_H
#define CRYS_POLY_H


#include "ssi_pal_types.h"
#include "crys_error.h"


#ifdef __cplusplus
extern "C"
{
#endif

/************************ Defines ******************************/
/*! POLY KEY size in words. */
#define CRYS_POLY_KEY_SIZE_IN_WORDS     8
/*! POLY KEY size in bytes. */
#define CRYS_POLY_KEY_SIZE_IN_BYTES     (CRYS_POLY_KEY_SIZE_IN_WORDS*SASI_32BIT_WORD_SIZE)

/*! POLY MAC size in words. */
#define CRYS_POLY_MAC_SIZE_IN_WORDS     4
/*! POLY MAC size in bytes. */
#define CRYS_POLY_MAC_SIZE_IN_BYTES     (CRYS_POLY_MAC_SIZE_IN_WORDS*SASI_32BIT_WORD_SIZE)

/************************ Typedefs  ****************************/

/*! CHACHA MAC buffer definition. */
typedef uint32_t CRYS_POLY_Mac_t[CRYS_POLY_MAC_SIZE_IN_WORDS];

/*! CHACHA key buffer definition. */
typedef uint32_t CRYS_POLY_Key_t[CRYS_POLY_KEY_SIZE_IN_WORDS];

/************************ Public Functions **********************/

/****************************************************************************************************/
/*!
@brief This function is used to perform the POLY MAC Calculation.

@return CRYS_OK on success.
@return A non-zero value on failure as defined crys_poly_error.h.
*/
CIMPORT_C CRYSError_t  CRYS_POLY(
                            CRYS_POLY_Key_t       pKey,            /*!< [in] A pointer to the user's key buffer. */
                uint8_t              *pDataIn,        /*!< [in] A pointer to the buffer of the input data to the CHACHA.
                                                                             must not be null. */
                            size_t                dataInSize,      /*!< [in]  The size of the input data. must not be 0. */
                CRYS_POLY_Mac_t   macRes       /*!< [in/out] Pointer to the MAC result buffer.*/
);



#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif /* #ifndef CRYS_POLY_H */





