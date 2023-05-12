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
 * FilePath: fpl011_g.c
 * Date: 2021-11-02 14:53:42
 * LastEditTime: 2022-02-18 09:05:41
 * Description:  This file is for uart static configuration
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  huanghe 2021/11/2  first commit
 * 1.1  liushengming 2022/02/18 add configs
 */

/***************************** Include Files *********************************/

#include "fpl011.h"
#include "fparameters.h"
#include "sdkconfig.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

const FPl011Config FPl011ConfigTable[FUART_NUM] =
{
    {
        .instance_id = FUART0_ID,
        .base_address = FUART0_BASE_ADDR,
        .ref_clock_hz = FUART0_CLK_FREQ_HZ,
        .irq_num = FUART0_IRQ_NUM,
        .baudrate = 115200
    },
    {
        .instance_id = FUART1_ID,
        .base_address = FUART1_BASE_ADDR,
        .ref_clock_hz = FUART1_CLK_FREQ_HZ,
        .irq_num = FUART1_IRQ_NUM,
        .baudrate = 115200
    },
#ifndef TARDIGRADE
    {
        .instance_id = FUART2_ID,
        .base_address = FUART2_BASE_ADDR,
        .ref_clock_hz = FUART2_CLK_FREQ_HZ,
        .irq_num = FUART2_IRQ_NUM,
        .baudrate = 115200
    },
    {
        .instance_id = FUART3_ID,
        .base_address = FUART3_BASE_ADDR,
        .ref_clock_hz = FUART3_CLK_FREQ_HZ,
        .irq_num = FUART3_IRQ_NUM,
        .baudrate = 115200
    }
#endif // !TARDIGRADE 

};
