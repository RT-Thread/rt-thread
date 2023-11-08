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
 * FilePath: fioctrl_g.c
 * Date: 2021-04-29 10:21:53
 * LastEditTime: 2022-02-18 08:29:20
 * Description:  This files is for the ioctrl static configuration
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2023/7/30    first release
 */

#include "fparameters.h"
#include "fioctrl.h"

FIOCtrlConfig FIOCtrlConfigTbl[FIOCTRL_NUM] =
{
    {
        .instance_id = FIOCTRL0_ID,
        .base_address = FIOCTRL_BASE_ADDR,
    }
};