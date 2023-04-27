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
 * FilePath: ftimer_tacho_g.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 09:09:07
 * Description:  This file is for timer_tacho static configuration
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  liushengming 2022/02/18    first commit
 */

/***************************** Include Files *********************************/

#include <string.h>
#include "fparameters.h"
#include "fassert.h"
#include "ftimer_tacho_hw.h"
#include "ftimer_tacho.h"

#define TACHO_PERIOD 1000000 /* 1000000/50000000 = 0.02s*/
/************************** Function Prototypes ******************************/
void FTimerGetDefConfig(u32 timer_id, FTimerTachoConfig *config_p)
{
    FASSERT((timer_id < FTIMER_NUM) && (NULL != config_p));

    memset(config_p, 0, sizeof(FTimerTachoConfig));
    config_p->id = timer_id;
    config_p->work_mode  = FTIMER_WORK_MODE_TIMER;
    config_p->timer_mode = FTIMER_RESTART;
    config_p->timer_bits = FTIMER_32_BITS;
    config_p->cmp_type = FTIMER_CYC_CMP;
    config_p->clear_cnt  = FALSE;
    config_p->force_load = TRUE;
}

void FTachoGetDefConfig(u32 tacho_id, FTimerTachoConfig *config_p)
{
    FASSERT((tacho_id < FTACHO_NUM) && (NULL != config_p));

    memset(config_p, 0, sizeof(FTimerTachoConfig));
    config_p->id = tacho_id;
    config_p->timer_bits = FTIMER_32_BITS;
    config_p->work_mode = FTIMER_WORK_MODE_TACHO;
    config_p->timer_mode = FTIMER_RESTART;
    config_p->edge_mode = FTACHO_RISING_EDGE;
    config_p->jitter_level = 0;
    config_p->plus_num = TACHO_PERIOD;/*采样周期越长，能够检测到的单位时间脉冲越多，能够检测更小的频率*/
    config_p->clear_cnt = FALSE;
    config_p->force_load = TRUE;
}