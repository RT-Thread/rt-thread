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
 * FilePath: fnand_g.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:56:31
 * Description:  This file is for configuration table for devices
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/05/10    first release
 */

#include "fnand.h"
#include "fnand_hw.h"
#include "fparameters.h"


FNandConfig FNandConfigTable[FNAND_NUM] =
{
    {
        .instance_id = FNAND_INSTANCE0,  /* Id of device*/
        .irq_num = FNAND_IRQ_NUM,     /* Irq number */
        .base_address = FNAND_BASE_ADDR,
        .ecc_strength = 8, /* 每次ecc 步骤纠正的位数 */
        .ecc_step_size = 512 /* 进行读写操作时，单次ecc 的步骤的跨度 */
    },
};


