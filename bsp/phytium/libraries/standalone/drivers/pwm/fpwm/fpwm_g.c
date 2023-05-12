/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fpwm_g.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-04-16 11:45:05
 * Description:  This file is for pwm static configuration implementation.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/4/16   init commit
 */

#include "fparameters.h"
#include "fpwm.h"
#include "fpwm_hw.h"
#include "sdkconfig.h"

#if defined(CONFIG_TARGET_E2000) 
/* default configs of pwm ctrl */
const FPwmConfig FPwmConfigTbl[FPWM_NUM] =
{
    [FPWM0_ID] =
    {
        .instance_id = FPWM0_ID,
        .db_base_addr = FPWM0_BASE_ADR,
        .pwm_base_addr = FPWM0_BASE_ADR + FPWM_OFFSET,
        .base_clk = FPWM_CLK_FREQ_HZ,
        .irq_num[FPWM_CHANNEL_0] = FPWM0_IRQ_NUM,
        .irq_num[FPWM_CHANNEL_1] = FPWM1_IRQ_NUM,
        .irq_prority[FPWM_CHANNEL_0] = 0,
        .irq_prority[FPWM_CHANNEL_1] = 0,
        .instance_name = "PWM_CTRL0",
    },
    [FPWM1_ID] =
    {
        .instance_id = FPWM1_ID,
        .db_base_addr = FPWM1_BASE_ADR,
        .pwm_base_addr = FPWM1_BASE_ADR + FPWM_OFFSET,
        .base_clk = FPWM_CLK_FREQ_HZ,
        .irq_num[FPWM_CHANNEL_0] = FPWM2_IRQ_NUM,
        .irq_num[FPWM_CHANNEL_1] = FPWM3_IRQ_NUM,
        .irq_prority[FPWM_CHANNEL_0] = 0,
        .irq_prority[FPWM_CHANNEL_1] = 0,
        .instance_name = "PWM_CTRL1",
    },
    [FPWM2_ID] =
    {
        .instance_id = FPWM2_ID,
        .db_base_addr = FPWM2_BASE_ADR,
        .pwm_base_addr = FPWM2_BASE_ADR + FPWM_OFFSET,
        .base_clk = FPWM_CLK_FREQ_HZ,
        .irq_num[FPWM_CHANNEL_0] = FPWM4_IRQ_NUM,
        .irq_num[FPWM_CHANNEL_1] = FPWM5_IRQ_NUM,
        .irq_prority[FPWM_CHANNEL_0] = 0,
        .irq_prority[FPWM_CHANNEL_1] = 0,
        .instance_name = "PWM_CTRL2",
    },
    [FPWM3_ID] =
    {
        .instance_id = FPWM3_ID,
        .db_base_addr = FPWM3_BASE_ADR,
        .pwm_base_addr = FPWM3_BASE_ADR + FPWM_OFFSET,
        .base_clk = FPWM_CLK_FREQ_HZ,
        .irq_num[FPWM_CHANNEL_0] = FPWM6_IRQ_NUM,
        .irq_num[FPWM_CHANNEL_1] = FPWM7_IRQ_NUM,
        .irq_prority[FPWM_CHANNEL_0] = 0,
        .irq_prority[FPWM_CHANNEL_1] = 0,
        .instance_name = "PWM_CTRL3",
    },
    [FPWM4_ID] =
    {
        .instance_id = FPWM4_ID,
        .db_base_addr = FPWM4_BASE_ADR,
        .pwm_base_addr = FPWM4_BASE_ADR + FPWM_OFFSET,
        .base_clk = FPWM_CLK_FREQ_HZ,
        .irq_num[FPWM_CHANNEL_0] = FPWM8_IRQ_NUM,
        .irq_num[FPWM_CHANNEL_1] = FPWM9_IRQ_NUM,
        .irq_prority[FPWM_CHANNEL_0] = 0,
        .irq_prority[FPWM_CHANNEL_1] = 0,
        .instance_name = "PWM_CTRL4",
    },
    [FPWM5_ID] =
    {
        .instance_id = FPWM5_ID,
        .db_base_addr = FPWM5_BASE_ADR,
        .pwm_base_addr = FPWM5_BASE_ADR + FPWM_OFFSET,
        .base_clk = FPWM_CLK_FREQ_HZ,
        .irq_num[FPWM_CHANNEL_0] = FPWM10_IRQ_NUM,
        .irq_num[FPWM_CHANNEL_1] = FPWM11_IRQ_NUM,
        .irq_prority[FPWM_CHANNEL_0] = 0,
        .irq_prority[FPWM_CHANNEL_1] = 0,
        .instance_name = "PWM_CTRL5",
    },
    [FPWM6_ID] =
    {
        .instance_id = FPWM6_ID,
        .db_base_addr = FPWM6_BASE_ADR,
        .pwm_base_addr = FPWM6_BASE_ADR + FPWM_OFFSET,
        .base_clk = FPWM_CLK_FREQ_HZ,
        .irq_num[FPWM_CHANNEL_0] = FPWM12_IRQ_NUM,
        .irq_num[FPWM_CHANNEL_1] = FPWM13_IRQ_NUM,
        .irq_prority[FPWM_CHANNEL_0] = 0,
        .irq_prority[FPWM_CHANNEL_1] = 0,
        .instance_name = "PWM_CTRL6",
    },
    [FPWM7_ID] =
    {
        .instance_id = FPWM7_ID,
        .db_base_addr = FPWM7_BASE_ADR,
        .pwm_base_addr = FPWM7_BASE_ADR + FPWM_OFFSET,
        .base_clk = FPWM_CLK_FREQ_HZ,
        .irq_num[FPWM_CHANNEL_0] = FPWM14_IRQ_NUM,
        .irq_num[FPWM_CHANNEL_1] = FPWM15_IRQ_NUM,
        .irq_prority[FPWM_CHANNEL_0] = 0,
        .irq_prority[FPWM_CHANNEL_1] = 0,
        .instance_name = "PWM_CTRL7",
    },


};

#elif defined(TARDIGRADE) 
/* default configs of pwm ctrl */
const FPwmConfig FPwmConfigTbl[FPWM_NUM] =
{
    [FPWM0_ID] = 
    {
        .instance_id = FPWM0_ID,
        .pwm_base_addr = FPWM0_BASE_ADR,
        .base_clk = FPWM_CLK_FREQ_HZ,
        .irq_num[FPWM_CHANNEL_0] = FPWM0_IRQ_NUM,
        .irq_prority[FPWM_CHANNEL_0] = 0,
        .instance_name = "PWM_CTRL0",
    },

};

#endif