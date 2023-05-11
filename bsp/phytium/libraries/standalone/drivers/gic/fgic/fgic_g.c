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
 * FilePath: fgic_g.c
 * Date: 2022-03-30 14:57:43
 * LastEditTime: 2022-03-30 14:57:43
 * Description:  This file is for gic static configuration implementation.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe  2022/4/16   init commit
 */

#include "fparameters.h"
#include "fgic.h"

FGicConfig fgic_config[FGIC_NUM] =
{
    {
        .instance_id = 0,                          /* Id of device */
        .dis_base = GICV3_DISTRIBUTOR_BASE_ADDR, /* Distributor base address      */
    }
};