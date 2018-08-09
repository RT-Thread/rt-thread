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
        CryptoCell Lib init and finish APIs, as well as the APIs themselves.
@defgroup sns_silib CryptoCell library basic APIs
@{
@ingroup cryptocell_api

*/

#ifndef __SNS_SILIB_H__
#define __SNS_SILIB_H__

#include "ssi_pal_types.h"
#include "crys_rnd.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*! Definitions for error returns from SaSi_LibInit or SaSi_LibFini functions. */
typedef enum {
        SA_SILIB_RET_OK = 0, /*!< Success defintion.*/
        SA_SILIB_RET_EINVAL_CTX_PTR, /*!< Illegal context pointer.*/
        SA_SILIB_RET_EINVAL_WORK_BUF_PTR, /*!< Illegal work buffer pointer.*/
        SA_SILIB_RET_HAL, /*!< Error returned from HAL layer.*/
        SA_SILIB_RET_PAL, /*!< Error returned from PAL layer.*/
        SA_SILIB_RET_EINVAL_HW_VERSION,    /*!< Invalid HW version. */
        SA_SILIB_RET_EINVAL_HW_SIGNATURE,  /*!< Invalid HW signature. */
        SA_SILIB_RESERVE32B = 0x7FFFFFFFL  /*!< Reserved.*/
} SA_SilibRetCode_t;


/*! Internal defintion for the product register. */
#define DX_VERSION_PRODUCT_BIT_SHIFT    0x18UL
/*! Internal defintion for the product register size. */
#define DX_VERSION_PRODUCT_BIT_SIZE     0x8UL



/*!
@brief This function Perform global initialization of the ARM CryptoCell 3xx runtime library;
it must be called once per ARM CryptoCell for 3xx cold boot cycle.

\note The Mutexes, if used, are initialized by this API. Therefore, unlike the other APIs in the library,
this API is not thread-safe.
@return SA_SILIB_RET_OK on success.
@return A non-zero value in case of failure.
*/
SA_SilibRetCode_t SaSi_LibInit(void);

/*!
@brief This function finalize the library operations. It frees the associated resources (mutexes) and call hal and pal terminate functions.
in case of active instansiation - one must call CRYS_RND_UnInstantiation to clean the rnd state.
*/
void SaSi_LibFini(void);

#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif /*__DX_CCLIB_H__*/

