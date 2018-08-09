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


#ifndef _SSI_PAL_ERROR_H
#define _SSI_PAL_ERROR_H

/*!
@file
@brief This file contains the platform dependent error definitions.
@defgroup ssi_pal_error CryptoCell PAL specific errors
@{
@ingroup ssi_pal

*/

#ifdef __cplusplus
extern "C"
{
#endif

/*! PAL error base.*/
#define SASI_PAL_BASE_ERROR                0x0F000000

/* Memory error returns */
/*! Buffer 1 is greater than buffer 2 error.*/
#define SASI_PAL_MEM_BUF1_GREATER          SASI_PAL_BASE_ERROR + 0x01UL
/*! Buffer 2 is greater than buffer 1 error.*/
#define SASI_PAL_MEM_BUF2_GREATER          SASI_PAL_BASE_ERROR + 0x02UL

/* Semaphore error returns */
/*! Semaphor creation failed.*/
#define SASI_PAL_SEM_CREATE_FAILED         SASI_PAL_BASE_ERROR + 0x03UL
/*! Semaphor deletion failed.*/
#define SASI_PAL_SEM_DELETE_FAILED         SASI_PAL_BASE_ERROR + 0x04UL
/*! Semaphor reached timeout.*/
#define SASI_PAL_SEM_WAIT_TIMEOUT          SASI_PAL_BASE_ERROR + 0x05UL
/*! Semaphor wait failed.*/
#define SASI_PAL_SEM_WAIT_FAILED           SASI_PAL_BASE_ERROR + 0x06UL
/*! Semaphor release failed.*/
#define SASI_PAL_SEM_RELEASE_FAILED        SASI_PAL_BASE_ERROR + 0x07UL
/*! PAL illegal address.*/
#define SASI_PAL_ILLEGAL_ADDRESS       SASI_PAL_BASE_ERROR + 0x08UL

#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif


