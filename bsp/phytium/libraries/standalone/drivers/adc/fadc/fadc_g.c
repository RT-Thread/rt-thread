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
 * Description: This file is for adc static configuration implementation.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/4/16   init commit
 */

#include "fparameters.h"
#include "fadc.h"

/* default configs of adc ctrl */
const FAdcConfig FAdcConfigTbl[FADC_NUM] =
{
    {
        .instance_id = FADC0_ID,
        .base_addr = FADC0_BASE_ADDR,
        .irq_num = FADC0_IRQ_NUM,
        .irq_prority = 0,
        .instance_name = "ADC-0"
    }
};