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
 * FilePath: fadc_g.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:28:45
 * Description:  This files is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */
#include "fparameters.h"
#include "fadc.h"

/* default configs of wdt ctrl */
const FAdcConfig FAdcConfigTbl[FADC_INSTANCE_NUM] =
{
    {
        .instance_id = FADC_INSTANCE_0,
        .base_addr = FADC0_CONTROL_BASE,
        .irq_num = FADC0_INTR_IRQ,
        .irq_prority = 0,
        .instance_name = "ADC-0"

    },

    {
        .instance_id = FADC_INSTANCE_1,
        .base_addr = FADC1_CONTROL_BASE,
        .irq_num = FADC1_INTR_IRQ,
        .irq_prority = 0,
        .instance_name = "ADC-1"
    }
};