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




#ifndef _SSI_PAL_MEM_H
#define _SSI_PAL_MEM_H


#ifdef __cplusplus
extern "C"
{
#endif

#include "ssi_pal_types.h"

/*!
@file
@brief This file contains functions for memory operations. The functions implementations
       are generally just wrappers to different operating system calls.
       None of the described functions will check the input parameters so the behavior
       of the APIs in illegal parameters case is dependent on the operating system behavior.
@defgroup ssi_pal_mem CryptoCell PAL memory operations
@{
@ingroup ssi_pal
*/


/*----------------------------
      PUBLIC FUNCTIONS
-----------------------------------*/

/**** ----- Memory Operations APIs ----- ****/

/*!
* @brief This function purpose is to compare between two given buffers according to given size.
*
* @return The return values is according to operating system return values.
*/


int32_t SaSi_PalMemCmp( const void* aTarget, /*!< [in] The target buffer to compare. */
                    const void* aSource, /*!< [in] The Source buffer to compare to. */
                uint32_t  aSize      /*!< [in] Number of bytes to compare. */);

/*!
 * @brief This function purpose is to perform secured memory comparison between two given
 *        buffers according to given size. The function will compare each byte till aSize
 *        number of bytes was compared even if the bytes are different.
 *        The function should be used to avoid security timing attacks.
 *
 * @return SASI_SUCCESS in case of success,
 * @return value on failure as defined in  ssi_pal_error.h.
 */
SaSiError_t SaSi_PalSecMemCmp(  const uint8_t* aTarget,  /*!< [in] The target buffer to compare. */
                        const uint8_t* aSource,  /*!< [in] The Source buffer to compare to. */
                        uint32_t  aSize      /*!< [in] Number of bytes to compare. */);

/*!
 * @brief This function purpose is to copy aSize bytes from source buffer to destination buffer.
 *
 * @return void.
 */
void SaSi_PalMemCopy(   void* aDestination, /*!< [out] The destination buffer to copy bytes to. */
                    const void* aSource,      /*!< [in] The Source buffer to copy from. */
                uint32_t  aSize       /*!< [in] Number of bytes to copy. */ );

/*!
 * @brief This function purpose is to copy aSize bytes from source buffer to destination buffer.
 * This function Supports overlapped buffers.
 *
 * @return void.
 */
void SaSi_PalMemMove(   void* aDestination, /*!< [out] The destination buffer to copy bytes to. */
                    const void* aSource,      /*!< [in] The Source buffer to copy from. */
                uint32_t  aSize       /*!< [in] Number of bytes to copy. */);

/*!
 * @brief This function purpose is to set aSize bytes in the given buffer with aChar.
 *
 * @return void.
 */
void SaSi_PalMemSet(    void* aTarget, /*!< [out]  The target buffer to set. */
                    const uint8_t aChar, /*!< [in] The char to set into aTarget. */
                uint32_t  aSize      /*!< [in] Number of bytes to set. */);

/*!
 * @brief This function purpose is to set aSize bytes in the given buffer with zeroes.
 *
 * @return void.
 */
void SaSi_PalMemSetZero(    void* aTarget, /*!< [out]  The target buffer to set. */
                        uint32_t  aSize      /*!< [in] Number of bytes to set. */);

/**** ----- Memory Allocation APIs ----- ****/

/*!
 * @brief This function purpose is to allocate a memory buffer according to aSize.
 *
 *
 * @return The function will return a pointer to allocated buffer or NULL if allocation failed.
 */
void* SaSi_PalMemMalloc(uint32_t aSize /*!< [in] Number of bytes to allocate. */);

/*!
 * @brief This function purpose is to reallocate a memory buffer according to aNewSize.
 *        The content of the old buffer is moved to the new location.
 *
 * @return The function will return a pointer to the newly allocated buffer or NULL if allocation failed.
 */
void* SaSi_PalMemRealloc(  void* aBuffer,   /*!< [in] Pointer to allocated buffer. */
                           uint32_t aNewSize    /*!< [in] Number of bytes to reallocate. */);

/*!
 * @brief This function purpose is to free allocated buffer.
 *
 *
 * @return void.
 */
void SaSi_PalMemFree(void* aBuffer /*!< [in] Pointer to allocated buffer.*/);

#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif


