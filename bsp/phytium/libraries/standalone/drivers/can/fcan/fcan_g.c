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
 * FilePath: fcan_g.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:28:45
 * Description:  This files is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */


#include "fcan.h"
#include "fparameters.h"

const FCanConfig FCanConfigTbl[FCAN_INSTANCE_NUM] =
{
    {
        .instance_id = FCAN_INSTANCE_0, /* Id of device */
        .base_address = FCAN0_BASEADDR,  /* Can base Address */
        .irq_num = FCAN0_IRQNUM,
    },
    {
        .instance_id = FCAN_INSTANCE_1, /* Id of device */
        .base_address = FCAN1_BASEADDR,  /* Can base Address */
        .irq_num = FCAN1_IRQNUM,
    },
#if defined(CONFIG_TARGET_F2000_4) || defined(CONFIG_TARGET_D2000)
    {
        .instance_id = FCAN_INSTANCE_2,  /* Id of device */
        .base_address = FCAN2_BASEADDR, /* Can base Address */
        .irq_num = FCAN2_IRQNUM,
    }
#endif

};
