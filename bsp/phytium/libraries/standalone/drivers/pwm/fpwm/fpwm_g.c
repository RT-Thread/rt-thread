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
 * LastEditTime: 2022-02-25 11:45:05
 * Description:  This files is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "fparameters.h"
#include "fpwm.h"
#include "fpwm_hw.h"

/* default configs of pwm ctrl */
const FPwmConfig FPwmConfigTbl[FPWM_INSTANCE_NUM] =
{
    [FPWM_INSTANCE_0] =
    {
        .instance_id = FPWM_INSTANCE_0,
        .db_base_addr = FPWM0_BASE_ADR,
        .pwm_base_addr = FPWM0_BASE_ADR + FPWM_OFFSET,
        .base_clk = FPWM_CLK,
        .irq_num[FPWM_CHANNEL_0] = FPWM0_INTR_IRQ,
        .irq_num[FPWM_CHANNEL_1] = FPWM1_INTR_IRQ,
        .irq_prority[FPWM_CHANNEL_0] = 0,
        .irq_prority[FPWM_CHANNEL_1] = 0,
        .instance_name = "PWM_CTRL0",
    },
    [FPWM_INSTANCE_1] =
    {
        .instance_id = FPWM_INSTANCE_1,
        .db_base_addr = FPWM1_BASE_ADR,
        .pwm_base_addr = FPWM1_BASE_ADR + FPWM_OFFSET,
        .base_clk = FPWM_CLK,
        .irq_num[FPWM_CHANNEL_0] = FPWM2_INTR_IRQ,
        .irq_num[FPWM_CHANNEL_1] = FPWM3_INTR_IRQ,
        .irq_prority[FPWM_CHANNEL_0] = 0,
        .irq_prority[FPWM_CHANNEL_1] = 0,
        .instance_name = "PWM_CTRL1",
    },
    [FPWM_INSTANCE_2] =
    {
        .instance_id = FPWM_INSTANCE_2,
        .db_base_addr = FPWM2_BASE_ADR,
        .pwm_base_addr = FPWM2_BASE_ADR + FPWM_OFFSET,
        .base_clk = FPWM_CLK,
        .irq_num[FPWM_CHANNEL_0] = FPWM4_INTR_IRQ,
        .irq_num[FPWM_CHANNEL_1] = FPWM5_INTR_IRQ,
        .irq_prority[FPWM_CHANNEL_0] = 0,
        .irq_prority[FPWM_CHANNEL_1] = 0,
        .instance_name = "PWM_CTRL2",
    },
    [FPWM_INSTANCE_3] =
    {
        .instance_id = FPWM_INSTANCE_3,
        .db_base_addr = FPWM3_BASE_ADR,
        .pwm_base_addr = FPWM3_BASE_ADR + FPWM_OFFSET,
        .base_clk = FPWM_CLK,
        .irq_num[FPWM_CHANNEL_0] = FPWM6_INTR_IRQ,
        .irq_num[FPWM_CHANNEL_1] = FPWM7_INTR_IRQ,
        .irq_prority[FPWM_CHANNEL_0] = 0,
        .irq_prority[FPWM_CHANNEL_1] = 0,
        .instance_name = "PWM_CTRL3",
    },
    [FPWM_INSTANCE_4] =
    {
        .instance_id = FPWM_INSTANCE_4,
        .db_base_addr = FPWM4_BASE_ADR,
        .pwm_base_addr = FPWM4_BASE_ADR + FPWM_OFFSET,
        .base_clk = FPWM_CLK,
        .irq_num[FPWM_CHANNEL_0] = FPWM8_INTR_IRQ,
        .irq_num[FPWM_CHANNEL_1] = FPWM9_INTR_IRQ,
        .irq_prority[FPWM_CHANNEL_0] = 0,
        .irq_prority[FPWM_CHANNEL_1] = 0,
        .instance_name = "PWM_CTRL4",
    },
    [FPWM_INSTANCE_5] =
    {
        .instance_id = FPWM_INSTANCE_5,
        .db_base_addr = FPWM5_BASE_ADR,
        .pwm_base_addr = FPWM5_BASE_ADR + FPWM_OFFSET,
        .base_clk = FPWM_CLK,
        .irq_num[FPWM_CHANNEL_0] = FPWM10_INTR_IRQ,
        .irq_num[FPWM_CHANNEL_1] = FPWM11_INTR_IRQ,
        .irq_prority[FPWM_CHANNEL_0] = 0,
        .irq_prority[FPWM_CHANNEL_1] = 0,
        .instance_name = "PWM_CTRL5",
    },
    [FPWM_INSTANCE_6] =
    {
        .instance_id = FPWM_INSTANCE_6,
        .db_base_addr = FPWM6_BASE_ADR,
        .pwm_base_addr = FPWM6_BASE_ADR + FPWM_OFFSET,
        .base_clk = FPWM_CLK,
        .irq_num[FPWM_CHANNEL_0] = FPWM12_INTR_IRQ,
        .irq_num[FPWM_CHANNEL_1] = FPWM13_INTR_IRQ,
        .irq_prority[FPWM_CHANNEL_0] = 0,
        .irq_prority[FPWM_CHANNEL_1] = 0,
        .instance_name = "PWM_CTRL6",
    },
    [FPWM_INSTANCE_7] =
    {
        .instance_id = FPWM_INSTANCE_7,
        .db_base_addr = FPWM7_BASE_ADR,
        .pwm_base_addr = FPWM7_BASE_ADR + FPWM_OFFSET,
        .base_clk = FPWM_CLK,
        .irq_num[FPWM_CHANNEL_0] = FPWM14_INTR_IRQ,
        .irq_num[FPWM_CHANNEL_1] = FPWM15_INTR_IRQ,
        .irq_prority[FPWM_CHANNEL_0] = 0,
        .irq_prority[FPWM_CHANNEL_1] = 0,
        .instance_name = "PWM_CTRL7",
    },


};