/**
 * @file system_bl702.c
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
#include "bl702_glb.h"
#include "bl702_hbn.h"
#include "bl702_aon.h"
#include <arch/risc-v/e24/clic.h>

void SystemInit(void)
{
    uint32_t *p;
    uint8_t i;
    uint32_t tmpVal = 0;
    uint8_t flashCfg = 0;
    uint8_t psramCfg = 0;
    uint8_t isInternalFlash = 0;
    uint8_t isInternalPsram = 0;

    /* global IRQ disable */
    __disable_irq();

    tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);
    tmpVal |= (1 << 8);      /*mask pds wakeup*/
    tmpVal |= (1 << 10);     /*mask rf done*/
    tmpVal |= (1 << 11);     /*mask pll done*/
    tmpVal &= ~(0xff << 16); /*mask all pds wakeup source int*/
    BL_WR_REG(PDS_BASE, PDS_INT, tmpVal);

    /* GLB_Set_EM_Sel(GLB_EM_0KB); */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_SEAM_MISC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_EM_SEL, 0x00); //GLB_EM_0KB
    BL_WR_REG(GLB_BASE, GLB_SEAM_MISC, tmpVal);

    /* Restore default setting*/
    /* GLB_UART_Sig_Swap_Set(UART_SIG_SWAP_NONE); */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_PARM);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_UART_SWAP_SET, 0x00); //UART_SIG_SWAP_NONE
    BL_WR_REG(GLB_BASE, GLB_PARM, tmpVal);

    /* CLear all interrupt */
    p = (uint32_t *)(CLIC_HART0_BASE + CLIC_INTIE_OFFSET);

    for (i = 0; i < (IRQn_LAST + 3) / 4; i++) {
        p[i] = 0;
    }

    p = (uint32_t *)(CLIC_HART0_BASE + CLIC_INTIP_OFFSET);

    for (i = 0; i < (IRQn_LAST + 3) / 4; i++) {
        p[i] = 0;
    }

    /* SF io select from efuse value */
    tmpVal = BL_RD_WORD(0x40007074);
    flashCfg = ((tmpVal >> 26) & 7);
    psramCfg = ((tmpVal >> 24) & 3);
    if (flashCfg == 1 || flashCfg == 2) {
        isInternalFlash = 1;
    } else {
        isInternalFlash = 0;
    }
    if (psramCfg == 1) {
        isInternalPsram = 1;
    } else {
        isInternalPsram = 0;
    }
    tmpVal = BL_RD_REG(GLB_BASE, GLB_GPIO_USE_PSRAM__IO);
    if (isInternalFlash == 1 && isInternalPsram == 0) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CFG_GPIO_USE_PSRAM_IO, 0x3f);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_CFG_GPIO_USE_PSRAM_IO, 0x00);
    }
    BL_WR_REG(GLB_BASE, GLB_GPIO_USE_PSRAM__IO, tmpVal);

    BL_WR_REG(GLB_BASE, GLB_UART_SIG_SEL_0, 0xffffffff);

    /* init bor for all platform */
    // HBN_BOR_CFG_Type borCfg = { 0 /* pu_bor */, 0 /* irq_bor_en */, 1 /* bor_vth */, 0 /* bor_sel */ };
    // HBN_Set_BOR_Cfg(&borCfg);
    /* dcdc 1.8v -> 1.5v */
    tmpVal = BL_RD_REG(AON_BASE, AON_DCDC18_TOP_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_DCDC18_VOUT_SEL_AON, 0xC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_DCDC18_VPFM_AON, 0x3);
    BL_WR_REG(AON_BASE, AON_DCDC18_TOP_0, tmpVal);
}

void System_Post_Init(void)
{
    PDS_Trim_RC32M();
    HBN_Trim_RC32K();
    /* global IRQ enable */
    __enable_irq();
}