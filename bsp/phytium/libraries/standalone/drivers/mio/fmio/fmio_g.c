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
 * Description:  This file is for mio
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 0.1.0  liu       2022.06.20    init
 */

/***************************** Include Files *********************************/
#include "fparameters.h"
#include "fmio_hw.h"
#include "fmio.h"

/************************** Constant Definitions *****************************/

const FMioConfig FMioConfigTbl[MIO_INSTANCE_NUM] =
{
    {
        .instance_id = MIO_INSTANCE_0,
        .func_base_addr = FMIO_BASE_ADDR(MIO_INSTANCE_0),
        .irq_num = FMIO_IRQ_NUM(MIO_INSTANCE_0),
        .mio_base_addr = FMIO_BASE_SET_ADDR(MIO_INSTANCE_0)
    },
    {
        .instance_id = MIO_INSTANCE_1,
        .func_base_addr = FMIO_BASE_ADDR(MIO_INSTANCE_1),
        .irq_num = FMIO_IRQ_NUM(MIO_INSTANCE_1),
        .mio_base_addr = FMIO_BASE_SET_ADDR(MIO_INSTANCE_1)
    },
    {
        .instance_id = MIO_INSTANCE_2,
        .func_base_addr = FMIO_BASE_ADDR(MIO_INSTANCE_2),
        .irq_num = FMIO_IRQ_NUM(MIO_INSTANCE_2),
        .mio_base_addr = FMIO_BASE_SET_ADDR(MIO_INSTANCE_2)
    },
    {
        .instance_id = MIO_INSTANCE_3,
        .func_base_addr = FMIO_BASE_ADDR(MIO_INSTANCE_3),
        .irq_num = FMIO_IRQ_NUM(MIO_INSTANCE_3),
        .mio_base_addr = FMIO_BASE_SET_ADDR(MIO_INSTANCE_3)
    },
    {
        .instance_id = MIO_INSTANCE_4,
        .func_base_addr = FMIO_BASE_ADDR(MIO_INSTANCE_4),
        .irq_num = FMIO_IRQ_NUM(MIO_INSTANCE_4),
        .mio_base_addr = FMIO_BASE_SET_ADDR(MIO_INSTANCE_4)
    },
    {
        .instance_id = MIO_INSTANCE_5,
        .func_base_addr = FMIO_BASE_ADDR(MIO_INSTANCE_5),
        .irq_num = FMIO_IRQ_NUM(MIO_INSTANCE_5),
        .mio_base_addr = FMIO_BASE_SET_ADDR(MIO_INSTANCE_5)
    },
    {
        .instance_id = MIO_INSTANCE_6,
        .func_base_addr = FMIO_BASE_ADDR(MIO_INSTANCE_6),
        .irq_num = FMIO_IRQ_NUM(MIO_INSTANCE_6),
        .mio_base_addr = FMIO_BASE_SET_ADDR(MIO_INSTANCE_6)
    },
    {
        .instance_id = MIO_INSTANCE_7,
        .func_base_addr = FMIO_BASE_ADDR(MIO_INSTANCE_7),
        .irq_num = FMIO_IRQ_NUM(MIO_INSTANCE_7),
        .mio_base_addr = FMIO_BASE_SET_ADDR(MIO_INSTANCE_7)
    },
    {
        .instance_id = MIO_INSTANCE_8,
        .func_base_addr = FMIO_BASE_ADDR(MIO_INSTANCE_8),
        .irq_num = FMIO_IRQ_NUM(MIO_INSTANCE_8),
        .mio_base_addr = FMIO_BASE_SET_ADDR(MIO_INSTANCE_8)
    },
    {
        .instance_id = MIO_INSTANCE_9,
        .func_base_addr = FMIO_BASE_ADDR(MIO_INSTANCE_9),
        .irq_num = FMIO_IRQ_NUM(MIO_INSTANCE_9),
        .mio_base_addr = FMIO_BASE_SET_ADDR(MIO_INSTANCE_9)
    },
    {
        .instance_id = MIO_INSTANCE_10,
        .func_base_addr = FMIO_BASE_ADDR(MIO_INSTANCE_10),
        .irq_num = FMIO_IRQ_NUM(MIO_INSTANCE_10),
        .mio_base_addr = FMIO_BASE_SET_ADDR(MIO_INSTANCE_10)
    },
    {
        .instance_id = MIO_INSTANCE_11,
        .func_base_addr = FMIO_BASE_ADDR(MIO_INSTANCE_11),
        .irq_num = FMIO_IRQ_NUM(MIO_INSTANCE_11),
        .mio_base_addr = FMIO_BASE_SET_ADDR(MIO_INSTANCE_11)
    },
    {
        .instance_id = MIO_INSTANCE_12,
        .func_base_addr = FMIO_BASE_ADDR(MIO_INSTANCE_12),
        .irq_num = FMIO_IRQ_NUM(MIO_INSTANCE_12),
        .mio_base_addr = FMIO_BASE_SET_ADDR(MIO_INSTANCE_12)
    },
    {
        .instance_id = MIO_INSTANCE_13,
        .func_base_addr = FMIO_BASE_ADDR(MIO_INSTANCE_13),
        .irq_num = FMIO_IRQ_NUM(MIO_INSTANCE_13),
        .mio_base_addr = FMIO_BASE_SET_ADDR(MIO_INSTANCE_13)
    },
    {
        .instance_id = MIO_INSTANCE_14,
        .func_base_addr = FMIO_BASE_ADDR(MIO_INSTANCE_14),
        .irq_num = FMIO_IRQ_NUM(MIO_INSTANCE_14),
        .mio_base_addr = FMIO_BASE_SET_ADDR(MIO_INSTANCE_14)
    },
    {
        .instance_id = MIO_INSTANCE_15,
        .func_base_addr = FMIO_BASE_ADDR(MIO_INSTANCE_15),
        .irq_num = FMIO_IRQ_NUM(MIO_INSTANCE_15),
        .mio_base_addr = FMIO_BASE_SET_ADDR(MIO_INSTANCE_15)
    }
};
