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
 * FilePath: fwdt_g.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 09:22:49
 * Description:  This files is for static config of wdt ctrl
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   Wangxiaodong   2021/8/25   init
 */

#include "fparameters.h"
#include "fwdt.h"

/* default configs of wdt ctrl */
const FWdtConfig FWdtConfigTbl[FWDT_INSTANCE_NUM] =
{
    {
        .instance_id = FWDT_INSTANCE_0,
        .refresh_base_addr = FWDT0_REFRESH_BASE,
        .control_base_addr = FWDT0_CONTROL_BASE,
        .irq_num = FWDT0_INTR_IRQ,
        .irq_prority = 0,
        .instance_name = "WDT-0"
    },

    {
        .instance_id = FWDT_INSTANCE_1,
        .refresh_base_addr = FWDT1_REFRESH_BASE,
        .control_base_addr = FWDT1_CONTROL_BASE,
        .irq_num = FWDT1_INTR_IRQ,
        .irq_prority = 0,
        .instance_name = "WDT-1"
    }
};
