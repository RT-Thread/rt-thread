/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * @file vpu_io.h
 *
 * @brief VPU system ioctrl definition
 *
 * @ingroup diag_vpu
 */

#ifndef __VPU__IO__H
#define __VPU__IO__H

#include "sdk.h"

//! @addtogroup diag_vpu
//! @{

//////////////////////////////////////////////////////////////////////////////
// DEFINITIONS
//////////////////////////////////////////////////////////////////////////////

//! @brief  vpu memory description structure
typedef struct vpu_mem_desc {
    int size;                   /*!requested memory size */
    uint32_t phy_addr;          /*!physical memory address allocated */
    uint32_t virt_addr;         /*!virtual user space address */
} vpu_mem_desc;

//! @brief  vpu iram usage structure
typedef struct iram_s {
    uint32_t start;
    uint32_t end;
} iram_t;

//////////////////////////////////////////////////////////////////////////////
// API
//////////////////////////////////////////////////////////////////////////////

/*!
 * @brief IO system initialization.
 * before starting the codec, this function must be called first.
 * the work buffer address and vpu base address are settled here
 *
 * @return 0 for success others for failure
 */
int vpu_io_init(void);

/*!
 * @brief IO system shut down.
 *
 * When user wants to stop the codec system, this
 * function call is needed, to release the interrupt
 * signal, free the working buffer/code buffer/parameter
 * buffer, unmap the register into user space, and
 * close the codec device.
 *
 * @return
 * @li   0	IO init success.
 * @li   -1 IO uninit failure.
 */
int vpu_io_uninit(void);

/*!
 * @brief Allocated buffer of requested size
 * When user wants to get massive memory for the system, they needs to fill
 * the required size in buff structure, and if this function succeeds in
 * allocating memory and returns 0, the returned physical memory is filled in
 * phy_addr of buff structure. If the function fails and return -1,
 * the phy_addr remains the same as before.
 *
 * @param buff	the structure contains the memory information to be retrieved;
 *
 * @return
 * @li 0		Allocation memory success.
 * @li -1		Allocation memory failure.
 */
int vpu_malloc(vpu_mem_desc * buff);

/*!
 * @brief Free specified memory
 * When user wants to free massive memory for the system,
 * they needs to fill the physical address and size to be freed
 * in buff structure.
 *
 * @param buff	the structure containing memory information to be freed;
 *
 * @return
 * @li 0            Freeing memory success.
 * @li -1		Freeing memory failure.
 */
int vpu_codec_io_deinit(void);

/*!
 * @brief Write VPU registers
 * 
 * @param addr register address
 * @param data register value
 */
void vpu_reg_write(uint32_t addr, uint32_t data);

/*!
 * @brief Write VPU registers
 * 
 * @param addr register address
 *
 * @return data register value
 */
uint32_t vpu_reg_read(uint32_t addr);

/*!
 * @brief When the system starts up, resetting is needed in advance.
 */
void vpu_reset(void);

/*!
 * @brief Check is VPU is initialized by checking the PC.
 *
 * @return 1 for initialized, 0 for uninitialized
 */
int vpu_is_initialized(void);

//! @}

#endif

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
