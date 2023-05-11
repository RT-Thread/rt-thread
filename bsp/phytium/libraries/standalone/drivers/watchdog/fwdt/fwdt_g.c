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
 * LastEditTime: 2022-06-18 09:22:49
 * Description:  This file is for static config of wdt device.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   Wangxiaodong   2021/8/25   init
 * 1.1   Wangxiaodong   2022/6/25   adapt to e2000
 */

#include "fparameters.h"
#include "fwdt.h"

/* default configs of wdt ctrl */
const FWdtConfig FWdtConfigTbl[FWDT_NUM] =
{
    [FWDT0_ID] =
    {
        .instance_id = FWDT0_ID,
        .refresh_base_addr = FWDT0_REFRESH_BASE_ADDR,
        .control_base_addr = FWDT_CONTROL_BASE_ADDR(FWDT0_REFRESH_BASE_ADDR),
        .irq_num = FWDT0_IRQ_NUM,
        .irq_prority = 0,
        #if defined(TARDIGRADE)
        .irq_twice_num = FWDT0_TWICE_IRQ_NUM,
        .irq_twice_prority = 0,
        #endif
        .instance_name = "WDT-0"
    },
    [FWDT1_ID] =
    {
        .instance_id = FWDT1_ID,
        .refresh_base_addr = FWDT1_REFRESH_BASE_ADDR,
        .control_base_addr = FWDT_CONTROL_BASE_ADDR(FWDT1_REFRESH_BASE_ADDR),
        .irq_num = FWDT1_IRQ_NUM,
        .irq_prority = 0,
        #if defined(TARDIGRADE)
        .irq_twice_num = FWDT1_TWICE_IRQ_NUM,
        .irq_twice_prority = 0,
        #endif
        .instance_name = "WDT-1"
    },

    #if defined(TARDIGRADE)
    [FWDT2_ID] =
    {
        .instance_id = FWDT2_ID,
        .refresh_base_addr = FWDT2_REFRESH_BASE_ADDR,
        .control_base_addr = FWDT_CONTROL_BASE_ADDR(FWDT2_REFRESH_BASE_ADDR),
        .irq_num = FWDT2_IRQ_NUM,
        .irq_prority = 0,
        .irq_twice_num = FWDT2_TWICE_IRQ_NUM,
        .irq_twice_prority = 0,
        .instance_name = "WDT-2"
    },
    [FWDT3_ID] =
    {
        .instance_id = FWDT3_ID,
        .refresh_base_addr = FWDT3_REFRESH_BASE_ADDR,
        .control_base_addr = FWDT_CONTROL_BASE_ADDR(FWDT3_REFRESH_BASE_ADDR),
        .irq_num = FWDT3_IRQ_NUM,
        .irq_prority = 0,
        .irq_twice_num = FWDT3_TWICE_IRQ_NUM,
        .irq_twice_prority = 0,
        .instance_name = "WDT-3"
    },
    [FWDT4_ID] =
    {
        .instance_id = FWDT4_ID,
        .refresh_base_addr = FWDT4_REFRESH_BASE_ADDR,
        .control_base_addr = FWDT_CONTROL_BASE_ADDR(FWDT4_REFRESH_BASE_ADDR),
        .irq_num = FWDT4_IRQ_NUM,
        .irq_prority = 0,
        .irq_twice_num = FWDT4_TWICE_IRQ_NUM,
        .irq_twice_prority = 0,
        .instance_name = "WDT-4"
    },
    [FWDT5_ID] =
    {
        .instance_id = FWDT5_ID,
        .refresh_base_addr = FWDT5_REFRESH_BASE_ADDR,
        .control_base_addr = FWDT_CONTROL_BASE_ADDR(FWDT5_REFRESH_BASE_ADDR),
        .irq_num = FWDT5_IRQ_NUM,
        .irq_prority = 0,
        .irq_twice_num = FWDT5_TWICE_IRQ_NUM,
        .irq_twice_prority = 0,
        .instance_name = "WDT-5"
    },
    [FWDT6_ID] =
    {
        .instance_id = FWDT6_ID,
        .refresh_base_addr = FWDT6_REFRESH_BASE_ADDR,
        .control_base_addr = FWDT_CONTROL_BASE_ADDR(FWDT6_REFRESH_BASE_ADDR),
        .irq_num = FWDT6_IRQ_NUM,
        .irq_prority = 0,
        .irq_twice_num = FWDT6_TWICE_IRQ_NUM,
        .irq_twice_prority = 0,
        .instance_name = "WDT-6"
    },
    [FWDT7_ID] =
    {
        .instance_id = FWDT7_ID,
        .refresh_base_addr = FWDT7_REFRESH_BASE_ADDR,
        .control_base_addr = FWDT_CONTROL_BASE_ADDR(FWDT7_REFRESH_BASE_ADDR),
        .irq_num = FWDT7_IRQ_NUM,
        .irq_prority = 0,
        .irq_twice_num = FWDT7_TWICE_IRQ_NUM,
        .irq_twice_prority = 0,
        .instance_name = "WDT-7"
    },
    #endif // TARDIGRADE
};
