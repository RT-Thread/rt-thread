/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
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
 * FilePath: fi2s_g.c
 * Created Date: 2023-05-09 09:59:03
 * Last Modified: 2023-09-27 19:33:55
 * Description:  This file is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------  -------- --------------------------------------
 *  1.0  Wangzq     2023/05/09  Modify the format and establish the version
 */

#include "fi2s.h"
#include "fparameters.h"

const FI2sConfig FI2S_CONFIG_TBL[FI2S_NUM] =
{
    [FI2S0_ID] =
    {
        .instance_id = FI2S0_ID,                  /* i2s id */
        .base_addr = FI2S0_BASE_ADDR,              /* i2s address*/
        .irq_num = FI2S0_IRQ_NUM,                 /* Device intrrupt id */
        .irq_prority = 0,
    },
    [FI2S1_ID] =
    {
        .instance_id = FI2S1_ID,                  /* i2s id */
        .base_addr = FI2S1_BASE_ADDR,              /* i2s address*/
        .irq_num = FI2S1_IRQ_NUM,                 /* Device intrrupt id */
        .irq_prority = 0,
    },
    [FI2S2_ID] =
    {
        .instance_id = FI2S2_ID,                  /* i2s id */
        .base_addr = FI2S2_BASE_ADDR,              /* i2s address*/
        .irq_num = FI2S2_IRQ_NUM,                 /* Device intrrupt id */
        .irq_prority = 0,
    },
};
