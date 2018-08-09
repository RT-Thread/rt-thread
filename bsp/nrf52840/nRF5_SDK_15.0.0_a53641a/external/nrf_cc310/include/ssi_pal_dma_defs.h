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
@brief This file contains the platform dependent DMA definitions.
@defgroup ssi_pal_dma_defs CryptoCell PAL DMA specific definitions
@{
@ingroup ssi_pal
*/

#ifndef _SSI_PAL_DMA_DEFS_H
#define _SSI_PAL_DMA_DEFS_H


#ifdef __cplusplus
extern "C"
{
#endif

/*! Definition for DMA buffer handle.*/
typedef void * SaSi_PalDmaBufferHandle;

/*! DMA directions configuration */
typedef enum {
    SASI_PAL_DMA_DIR_NONE = 0, /*!< No direction. */
    SASI_PAL_DMA_DIR_TO_DEVICE = 1, /*!< The original buffer is the input to the operation, and should be copied/mapped to a temp buffer,
                         prior to activating the HW on the temp buffer. */
    SASI_PAL_DMA_DIR_FROM_DEVICE = 2, /*!< The temp buffer holds the output of the HW, and this API should copy/map it to the original output buffer.*/
    SASI_PAL_DMA_DIR_BI_DIRECTION = 3, /*!< Used when the result is written over the original data at the same address. should be treated as 1 & 2.*/
    SASI_PAL_DMA_DIR_MAX,          /*!< Maximal DMA directions options. */
    SASI_PAL_DMA_DIR_RESERVE32 = 0x7FFFFFFF /*!< Reserved.*/
}SaSi_PalDmaBufferDirection_t;


#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif


