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
 * @file vpu_io.c
 *
 * @brief VPU system ioctrl implementation
 *
 * @ingroup diag_vpu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vpu/vpu_debug.h"
#include "vpu/vpu_reg.h"
#include "vpu/vpu_io.h"
#include "vpu/vpu_lib.h"
#include "vpu/vpu_util.h"
#include "sdk.h"

///////////////////////////////////////////////////////////////////////////////////
// DEFINITIONS
///////////////////////////////////////////////////////////////////////////////////
#define VPU_MEM_START_ADDR	(VIDEO_BUFFERS_START)
#define VPU_MEM_END_ADDR	(VIDEO_BUFFERS_END)

///////////////////////////////////////////////////////////////////////////////////
// VARIABLES
///////////////////////////////////////////////////////////////////////////////////
static uint32_t g_vpu_mem_alloc_ptr = VPU_MEM_START_ADDR;

vpu_mem_desc g_vpu_reg_base;
vpu_mem_desc g_bit_work_addr;

extern vpu_resource_t *g_vpu_hw_map;

int g_vpu_system_mem_size = 0;

///////////////////////////////////////////////////////////////////////////////////
// CODE
///////////////////////////////////////////////////////////////////////////////////

int vpu_is_initialized(void)
{
    int val;

    val = vpu_reg_read(BIT_CUR_PC);

    return val != 0;
}

/*!
 * @brief remap the vpu registers.
 * it should be on any access to vpu registers.
 */
/* make consideration for both register and physical mem access */
static inline uint32_t *vpu_reg_map(uint32_t offset)
{
    return (uint32_t *) (offset + (uint32_t) g_vpu_reg_base.virt_addr);
}

int vpu_io_init(void)
{
    /*vpu base is equal to the physical address. MMU disabled */
    g_vpu_system_mem_size = 0;
    g_vpu_reg_base.phy_addr = (uint32_t) VPU_BASE_ADDR;
    g_vpu_reg_base.virt_addr = (uint32_t) VPU_BASE_ADDR;

    g_bit_work_addr.size = TEMP_BUF_SIZE + PARA_BUF_SIZE + CODE_BUF_SIZE + PARA_BUF2_SIZE;
    if (vpu_malloc(&g_bit_work_addr) < 0) {
        err_msg("Get bitwork address failed!\n");
        goto err;
    }
    g_vpu_system_mem_size += g_bit_work_addr.size;
    g_vpu_hw_map = vpu_semaphore_open();

    return 0;

  err:
    err_msg("Error in %s", __FUNCTION__);
    vpu_io_uninit();
    return -1;
}

int vpu_io_uninit(void)
{
    g_vpu_mem_alloc_ptr = g_bit_work_addr.phy_addr;
    g_vpu_system_mem_size = 0;
    return 0;
}

void vpu_reg_write(uint32_t addr, uint32_t data)
{
    uint32_t *reg_addr = vpu_reg_map(addr);
    *(volatile uint32_t *)reg_addr = data;
}

uint32_t vpu_reg_read(uint32_t addr)
{
    uint32_t *reg_addr = vpu_reg_map(addr);
    return *(volatile uint32_t *)reg_addr;
}

int vpu_malloc(vpu_mem_desc * buff)
{
    buff->size = (buff->size + 0xFFF) & 0xFFFFF000; //align 
    if (g_vpu_mem_alloc_ptr + buff->size > VPU_MEM_END_ADDR) {
        err_msg("Memory reserved for VPU is not enough!!\n");
        err_msg("Memory required 0x%x, actual pointer 0x%x, actual room 0x%x!!\n",
                buff->size, g_vpu_mem_alloc_ptr, VPU_MEM_END_ADDR - g_vpu_mem_alloc_ptr);
        return -1;
    } else {
        buff->phy_addr = g_vpu_mem_alloc_ptr;
        buff->virt_addr = g_vpu_mem_alloc_ptr;
        g_vpu_mem_alloc_ptr += buff->size;
    }
    info_msg("%s: phy addr = %08lx\n", __FUNCTION__, buff->phy_addr);

    return 0;
}

int vpu_codec_io_deinit(void)
{
    int i = 0;
    g_vpu_mem_alloc_ptr = g_bit_work_addr.phy_addr + g_vpu_system_mem_size;
    for (i = 0; i < MAX_NUM_INSTANCE; i++) {
        g_vpu_hw_map->codecInstPool[i].inUse = 0;
        g_vpu_hw_map->codecInstPool[i].initDone = 0;
    }
    return 0;
}

void vpu_reset(void)
{
    uint32_t *reg_addr = vpu_reg_map(BIT_CODE_RESET);
    (*(volatile uint32_t *)reg_addr) |= 0x1;
    hal_delay_us(10);
    (*(volatile uint32_t *)reg_addr) &= ~0x1;

    return;
}

///////////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////////
