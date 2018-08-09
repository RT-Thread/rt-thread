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



#ifndef _SSI_PAL_MUTEX_H
#define _SSI_PAL_MUTEX_H

#include "ssi_pal_mutex_plat.h"
#include "ssi_pal_types_plat.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*!
@file
@brief This file contains functions for resource management (mutex operations).
       The functions implementations are generally just wrappers to different operating system calls.
       None of the described functions will check the input parameters so the behavior
       of the APIs in illegal parameters case is dependent on the operating system behavior.
@defgroup ssi_pal_mutex CryptoCell PAL mutex APIs
@{
@ingroup ssi_pal
*/




/*----------------------------
      PUBLIC FUNCTIONS
-----------------------------------*/

/**
 * @brief This function purpose is to create a mutex.
 *
 *
 * @return Zero on success.
 * @return A non-zero value on failure.
 */
SaSiError_t SaSi_PalMutexCreate(SaSi_PalMutex *pMutexId /*!< [out] Pointer to created mutex handle. */);


/**
 * @brief This function purpose is to destroy a mutex.
 *
 *
 * @return Zero on success.
 * @return A non-zero value on failure.
 */
SaSiError_t SaSi_PalMutexDestroy(SaSi_PalMutex *pMutexId /*!< [in] Pointer to mutex handle. */);


/**
 * @brief This function purpose is to Wait for Mutex with aTimeOut. aTimeOut is
 *        specified in milliseconds (SASI_INFINITE is blocking).
 *
 * @return Zero on success.
 * @return A non-zero value on failure.
 */
SaSiError_t SaSi_PalMutexLock (SaSi_PalMutex *pMutexId, /*!< [in] Pointer to Mutex handle. */
                   uint32_t aTimeOut    /*!< [in] Timeout in mSec, or SASI_INFINITE. */);


/**
 * @brief This function purpose is to release the mutex.
 *
 * @return Zero on success.
 * @return A non-zero value on failure.
 */
SaSiError_t SaSi_PalMutexUnlock (SaSi_PalMutex *pMutexId/*!< [in] Pointer to Mutex handle. */);





#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif


