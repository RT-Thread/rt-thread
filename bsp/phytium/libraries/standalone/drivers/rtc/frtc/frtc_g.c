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
 * FilePath: frtc_g.c
 * Date: 2021-08-25 14:53:42
 * LastEditTime: 2021-08-26 09:01:26
 * Description:  This file is for rtc static configuration
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   Wangxiaodong   2021/8/26 first commit
 */

#include "fparameters.h"
#include "frtc.h"

/* default configs of rtc ctrl */
const FRtcConfig FRtcConfigTbl =
{
    .control_base_addr = RTC_CONTROL_BASE,
    .instance_name = "RTC"
};

