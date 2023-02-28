/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "bl_timer.h"
#ifdef BL808
#include <bl808_clock.h>
#include <bl808_glb.h>
#elif defined(BL606P)
#include <bl606p_clock.h>
#include <bl606p_glb.h>
#else
#error "Use CHIP BL808/BL606P for this module"
#endif

#include <FreeRTOS.h>
#include <task.h>

uint32_t bl_timer_now_us(void)
{
    return xTaskGetTickCount() * 1000000 / configTICK_RATE_HZ;
}

uint32_t bl_system_core_clock_get(GLB_CORE_ID_Type core)
{
    uint32_t clockVal = 0;

    switch (core) {
        case GLB_CORE_ID_M0:
            clockVal = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_MCU_CLK);
            break;
        case GLB_CORE_ID_D0:
            clockVal = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_DSP_CLK);
            break;
        case GLB_CORE_ID_LP:
            clockVal = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_LP_CLK);
            break;
        default:
            clockVal = 0;
            break;
    }
    clockVal = clockVal ? clockVal : (32 * 1000 * 1000);

    return clockVal;
}

BL_Err_Type bl_cpu_set_core_mtimer_clk(GLB_CORE_ID_Type core, uint8_t enable, uint16_t div)
{
    uint32_t tmpVal = 0;
    uint32_t address = 0;

    CHECK_PARAM((div <= 0x3FF));

    switch (core) {
        case GLB_CORE_ID_M0:
            address = MCU_MISC_BASE + MCU_MISC_MCU_E907_RTC_OFFSET;
            break;
        case GLB_CORE_ID_D0:
            address = MM_MISC_BASE + MM_MISC_CPU_RTC_OFFSET;
            break;
        case GLB_CORE_ID_LP:
            address = PDS_BASE + PDS_CPU_CORE_CFG8_OFFSET;
            break;
        default:
            address = MCU_MISC_BASE + MCU_MISC_MCU_E907_RTC_OFFSET;
            break;
    }

    /* disable rtc first */
    /* MCU RTC_EN is [31] */
    /* DSP RTC_EN is [31] */
    /* LP  RTC_EN is [31] */
    tmpVal = BL_RD_WORD(address);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MCU_MISC_REG_MCU_RTC_EN);
    BL_WR_WORD(address, tmpVal);

    /* set div */
    /* MCU RTC_DIV is [9:0] */
    /* DSP RTC_DIV is [9:0] */
    /* LP  RTC_DIV is [9:0] */
    tmpVal = BL_RD_WORD(address);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MCU_MISC_REG_MCU_RTC_DIV, div);
    BL_WR_WORD(address, tmpVal);

    /* enable or not */
    /* MCU RTC_EN is [31] */
    /* DSP RTC_EN is [31] */
    /* LP  RTC_EN is [31] */
    tmpVal = BL_RD_WORD(address);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, MCU_MISC_REG_MCU_RTC_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, MCU_MISC_REG_MCU_RTC_EN);
    }
    BL_WR_WORD(address, tmpVal);

    return SUCCESS;
}

void bl_mtimer_c906_clock_init(void)
{
    uint32_t clockVal = 0;
    clockVal = bl_system_core_clock_get(GLB_CORE_ID_D0);

    /* Set MTimer clock source 10M */
    bl_cpu_set_core_mtimer_clk(GLB_CORE_ID_D0, 1, (clockVal / 1000 / 1000 / 10) - 1);
}
