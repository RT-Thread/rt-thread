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
 * FilePath: fmio_g.c
 * Date: 2022-06-20 21:05:07
 * LastEditTime: 2022-06-20 21:05:07
 * Description:  This file is for mio static configuration
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  liushengming 2022/06/20    first commit
 */

/***************************** Include Files *********************************/
#include "fparameters.h"
#include "fmio_hw.h"
#include "fmio.h"

/************************** Constant Definitions *****************************/

const FMioConfig FMioConfigTbl[FMIO_NUM] =
{
    {
        .instance_id = FMIO0_ID,
        .func_base_addr = FMIO_BASE_ADDR(FMIO0_ID),
        .irq_num = FMIO_IRQ_NUM(FMIO0_ID),
        .mio_base_addr = FMIO_BASE_SET_ADDR(FMIO0_ID)
    },
    {
        .instance_id = FMIO1_ID,
        .func_base_addr = FMIO_BASE_ADDR(FMIO1_ID),
        .irq_num = FMIO_IRQ_NUM(FMIO1_ID),
        .mio_base_addr = FMIO_BASE_SET_ADDR(FMIO1_ID)
    },
    {
        .instance_id = FMIO2_ID,
        .func_base_addr = FMIO_BASE_ADDR(FMIO2_ID),
        .irq_num = FMIO_IRQ_NUM(FMIO2_ID),
        .mio_base_addr = FMIO_BASE_SET_ADDR(FMIO2_ID)
    },
    {
        .instance_id = FMIO3_ID,
        .func_base_addr = FMIO_BASE_ADDR(FMIO3_ID),
        .irq_num = FMIO_IRQ_NUM(FMIO3_ID),
        .mio_base_addr = FMIO_BASE_SET_ADDR(FMIO3_ID)
    },
    {
        .instance_id = FMIO4_ID,
        .func_base_addr = FMIO_BASE_ADDR(FMIO4_ID),
        .irq_num = FMIO_IRQ_NUM(FMIO4_ID),
        .mio_base_addr = FMIO_BASE_SET_ADDR(FMIO4_ID)
    },
    {
        .instance_id = FMIO5_ID,
        .func_base_addr = FMIO_BASE_ADDR(FMIO5_ID),
        .irq_num = FMIO_IRQ_NUM(FMIO5_ID),
        .mio_base_addr = FMIO_BASE_SET_ADDR(FMIO5_ID)
    },
    {
        .instance_id = FMIO6_ID,
        .func_base_addr = FMIO_BASE_ADDR(FMIO6_ID),
        .irq_num = FMIO_IRQ_NUM(FMIO6_ID),
        .mio_base_addr = FMIO_BASE_SET_ADDR(FMIO6_ID)
    },
    {
        .instance_id = FMIO7_ID,
        .func_base_addr = FMIO_BASE_ADDR(FMIO7_ID),
        .irq_num = FMIO_IRQ_NUM(FMIO7_ID),
        .mio_base_addr = FMIO_BASE_SET_ADDR(FMIO7_ID)
    },
#if defined(CONFIG_TARGET_E2000)
    {
        .instance_id = FMIO8_ID,
        .func_base_addr = FMIO_BASE_ADDR(FMIO8_ID),
        .irq_num = FMIO_IRQ_NUM(FMIO8_ID),
        .mio_base_addr = FMIO_BASE_SET_ADDR(FMIO8_ID)
    },
    {
        .instance_id = FMIO9_ID,
        .func_base_addr = FMIO_BASE_ADDR(FMIO9_ID),
        .irq_num = FMIO_IRQ_NUM(FMIO9_ID),
        .mio_base_addr = FMIO_BASE_SET_ADDR(FMIO9_ID)
    },
    {
        .instance_id = FMIO10_ID,
        .func_base_addr = FMIO_BASE_ADDR(FMIO10_ID),
        .irq_num = FMIO_IRQ_NUM(FMIO10_ID),
        .mio_base_addr = FMIO_BASE_SET_ADDR(FMIO10_ID)
    },
    {
        .instance_id = FMIO11_ID,
        .func_base_addr = FMIO_BASE_ADDR(FMIO11_ID),
        .irq_num = FMIO_IRQ_NUM(FMIO11_ID),
        .mio_base_addr = FMIO_BASE_SET_ADDR(FMIO11_ID)
    },
    {
        .instance_id = FMIO12_ID,
        .func_base_addr = FMIO_BASE_ADDR(FMIO12_ID),
        .irq_num = FMIO_IRQ_NUM(FMIO12_ID),
        .mio_base_addr = FMIO_BASE_SET_ADDR(FMIO12_ID)
    },
    {
        .instance_id = FMIO13_ID,
        .func_base_addr = FMIO_BASE_ADDR(FMIO13_ID),
        .irq_num = FMIO_IRQ_NUM(FMIO13_ID),
        .mio_base_addr = FMIO_BASE_SET_ADDR(FMIO13_ID)
    },
    {
        .instance_id = FMIO14_ID,
        .func_base_addr = FMIO_BASE_ADDR(FMIO14_ID),
        .irq_num = FMIO_IRQ_NUM(FMIO14_ID),
        .mio_base_addr = FMIO_BASE_SET_ADDR(FMIO14_ID)
    },
    {
        .instance_id = FMIO15_ID,
        .func_base_addr = FMIO_BASE_ADDR(FMIO15_ID),
        .irq_num = FMIO_IRQ_NUM(FMIO15_ID),
        .mio_base_addr = FMIO_BASE_SET_ADDR(FMIO15_ID)
    }
#endif
};
