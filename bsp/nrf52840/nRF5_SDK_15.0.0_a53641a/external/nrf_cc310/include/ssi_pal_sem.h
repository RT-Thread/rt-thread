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




#ifndef _SSI_PAL_SEM_H
#define _SSI_PAL_SEM_H

#include "ssi_pal_sem_plat.h"

#define SASI_PAL_SEM_NO_WAIT          0
#define SASI_PAL_SEM_FREE         1
#define SASI_PAL_SEM_LOCKED       0


#ifdef __cplusplus
extern "C"
{
#endif

/**
* @brief File Description:
*        This file contains functions for resource management (semaphor operations).
*        The functions implementations are generally just wrappers to different operating system calls.
*        None of the described functions will check the input parameters so the behavior
*        of the APIs in illegal parameters case is dependent on the operating system behavior.
*
*/




/*----------------------------
      PUBLIC FUNCTIONS
-----------------------------------*/

/**
 * @brief This function purpose is to create a semaphore.
 *
 *
 * @param[out] aSemId - Pointer to created semaphor handle
 * @param[in] aInitialVal - Initial semaphore value
 *
 * @return The return values is according to operating system return values.
 */
//SaSiError_t SaSi_PalSemCreate( DX_PAL_SEM *aSemId, uint32_t aInitialVal );
#define SaSi_PalSemCreate _SaSi_PalSemCreate
/**
 * @brief This function purpose is to delete a semaphore
 *
 *
 * @param[in] aSemId - Semaphore handle
 *
 * @return The return values is according to operating system return values.
 */
//SaSiError_t SaSi_PalSemDelete( DX_PAL_SEM *aSemId );
#define SaSi_PalSemDelete _SaSi_PalSemDelete
/**
 * @brief This function purpose is to Wait for semaphore with aTimeOut. aTimeOut is
 *        specified in milliseconds.
 *
 *
 * @param[in] aSemId - Semaphore handle
 * @param[in] aTimeOut - timeout in mSec, or SASI_INFINITE
 *
 * @return The return values is according to operating system return values.
 */
//SaSiError_t SaSi_PalSemWait(DX_PAL_SEM aSemId, uint32_t aTimeOut);
#define SaSi_PalSemWait _SaSi_PalSemWait
/**
 * @brief This function purpose is to signal the semaphore.
 *
 *
 * @param[in] aSemId - Semaphore handle
 *
 * @return The return values is according to operating system return values.
 */
//SaSiError_t SaSi_PalSemGive(DX_PAL_SEM aSemId);

#define SaSi_PalSemGive _SaSi_PalSemGive




#ifdef __cplusplus
}
#endif

#endif


