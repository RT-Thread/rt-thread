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
 * FilePath: fqspi_g.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 09:00:41
 * Description:  This file is for the qspi default configuration
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/3/29  first release
 * 1.1   wangxiaodong  2022/9/9   improve functions
 */

#include "fparameters.h"
#include "fqspi.h"
#include "sdkconfig.h"

FQspiConfig FQspiConfigTbl[FQSPI_NUM] =
{
    {
        .instance_id = FQSPI0_ID,
        .base_addr = FQSPI_BASE_ADDR,
        .mem_start = FQSPI_MEM_START_ADDR,
        .capacity = 0,
        .dev_num = 0,
        .channel = 0,
    }
};