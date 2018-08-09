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


#ifndef CRYS_SRP_ERROR_H
#define CRYS_SRP_ERROR_H


#include "crys_error.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*!
@file
@brief This module contains the definitions of the CRYS SRP errors.
@defgroup crys_srp_error CryptoCell SRP specific errors
@{
@ingroup crys_srp
*/



/************************ Defines ******************************/

/*! The CRYS SRP module errors base address - 0x00F02600. */
/*! Illegal parameter. */
#define CRYS_SRP_PARAM_INVALID_ERROR               (CRYS_SRP_MODULE_ERROR_BASE + 0x01UL)
/*! Illegal modulus size . */
#define CRYS_SRP_MOD_SIZE_INVALID_ERROR            (CRYS_SRP_MODULE_ERROR_BASE + 0x02UL)
/*! Illegal state (uninitialized) . */
#define CRYS_SRP_STATE_UNINITIALIZED_ERROR         (CRYS_SRP_MODULE_ERROR_BASE + 0x03UL)
/*! Result validation error. */
#define CRYS_SRP_RESULT_ERROR                  (CRYS_SRP_MODULE_ERROR_BASE + 0x04UL)
/*! Invalid parameter. */
#define CRYS_SRP_PARAM_ERROR                   (CRYS_SRP_MODULE_ERROR_BASE + 0x05UL)
/*! Internal PKI error */
#define CRYS_SRP_PKI_INTERNAL_ERROR                (CRYS_SRP_MODULE_ERROR_BASE + 0x06UL)

/************************ Enums ********************************/

/************************ Typedefs  ****************************/

/************************ Structs  *****************************/

/************************ Public Variables *********************/

/************************ Public Functions *********************/

#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif


