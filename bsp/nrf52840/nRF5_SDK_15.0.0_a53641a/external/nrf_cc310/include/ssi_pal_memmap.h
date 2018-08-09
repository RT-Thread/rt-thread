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




#ifndef _SSI_PAL_MEMMAP_H
#define _SSI_PAL_MEMMAP_H


#ifdef __cplusplus
extern "C"
{
#endif


#include "ssi_pal_types.h"
/*!
@file
@brief This file contains functions for memory mapping
       None of the described functions will check the input parameters so the behavior
       of the APIs in illegal parameters case is dependent on the operating system behavior.
@defgroup ssi_pal_memmap CryptoCell PAL memory mapping APIs
@{
@ingroup ssi_pal

*/


/*----------------------------
      PUBLIC FUNCTIONS
-----------------------------------*/

/**
 * @brief This function purpose is to return the base virtual address that maps the
 *        base physical address
 *
 * @return Zero on success.
 * @return A non-zero value in case of failure.
 */
uint32_t SaSi_PalMemMap(uint32_t physicalAddress, /*!< [in] Start physical address of the I/O range to be mapped. */
                    uint32_t mapSize,     /*!< [in] Number of bytes that were mapped. */
                uint32_t **ppVirtBuffAddr /*!< [out] Pointer to the base virtual address to which the physical pages were mapped. */ );


/**
 * @brief This function purpose is to Unmap a specified address range previously mapped
 *        by SaSi_PalMemMap.
 *
 * @return Zero on success.
 * @return A non-zero value in case of failure.
 */
uint32_t SaSi_PalMemUnMap(uint32_t *pVirtBuffAddr, /*!< [in] Pointer to the base virtual address to which the physical pages were mapped. */
                      uint32_t mapSize     /*!< [in] Number of bytes that were mapped. */);

#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif


