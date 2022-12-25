/**
 * @file hal_common.c
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#include "hal_common.h"
#include "bl808_l1c.h"
#include "bl808_glb.h"
#include "bl808_hbn.h"

volatile uint32_t nesting = 0;

void ATTR_TCM_SECTION cpu_global_irq_enable(void)
{
    nesting--;
    if (nesting == 0) {
        __enable_irq();
    }
}

void ATTR_TCM_SECTION cpu_global_irq_disable(void)
{
    __disable_irq();
    nesting++;
}

void hal_por_reset(void)
{
    GLB_SW_POR_Reset();
}

void hal_system_reset(void)
{
    GLB_SW_System_Reset();
}

void hal_cpu_reset(void)
{
    GLB_SW_CPU_Reset();
}

void hal_reboot_config(hal_reboot_cfg_t rbot)
{
    switch(rbot){
        case HAL_REBOOT_AS_BOOTPIN:
            HBN_Set_Hand_Off_Config(0);
            break;
        case HAL_REBOOT_FROM_INTERFACE:
            HBN_Set_Hand_Off_Config(1);
            break;
        case HAL_REBOOT_FROM_MEDIA:
            HBN_Set_Hand_Off_Config(2);
            break;
        default :
            HBN_Set_Hand_Off_Config(0);
            break;
    }
}

void ATTR_TCM_SECTION hal_dcache_clean_all(void)
{
    L1C_DCache_Clean_All();
}

void ATTR_TCM_SECTION hal_dcache_invalid_all(void)
{
    L1C_DCache_Invalid_All();
}

void ATTR_TCM_SECTION hal_dcache_clean_invalid_all(void)
{
    L1C_DCache_Clean_Invalid_All();
}

void ATTR_TCM_SECTION hal_dcache_clean_byaddr(uintptr_t addr, uint32_t len)
{
    int64_t op_size = len + (uint64_t)addr % 32;
    uint64_t op_addr = (uint64_t)addr & CACHE_INV_ADDR_Msk;
    int64_t linesize = 32;

    __DSB();

    while (op_size > 0) {
        __DCACHE_CPA(op_addr);
        op_addr += linesize;
        op_size -= linesize;
    }

    __DSB();
}

void ATTR_TCM_SECTION hal_dcache_invalidate_byaddr(uintptr_t addr, uint32_t len)
{
    int64_t op_size = len + (uint64_t)addr % 32;
    uint64_t op_addr = (uint64_t)addr;
    int64_t linesize = 32;

    __DSB();

    while (op_size > 0) {
        __DCACHE_IPA(op_addr);
        op_addr += linesize;
        op_size -= linesize;
    }

    __DSB();
}

void ATTR_TCM_SECTION hal_dcache_clean_invalidate_byaddr(uintptr_t addr, uint32_t len)
{
    int64_t op_size = len + (uint64_t)addr % 32;
    uint64_t op_addr = (uint64_t)addr;
    int64_t linesize = 32;

    __DSB();

    while (op_size > 0) {
        __DCACHE_CIPA(op_addr);
        op_addr += linesize;
        op_size -= linesize;
    }

    __DSB();
}