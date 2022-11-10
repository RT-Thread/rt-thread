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
 * FilePath: fgpio_g.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:25:29
 * Description:  This files is for GPIO static configuration implementation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022-3-1     init commit
 */


/***************************** Include Files *********************************/
#include "fparameters.h"

#include "fgpio_hw.h"
#include "fgpio.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/*****************************************************************************/
#if defined(FGPIO_VERSION_1) /* FT2000-4, D2000 */
const FGpioConfig fgpio_cfg_tbl[FGPIO_NUM] =
{
    [FGPIO_ID_0] =
    {
        .instance_id = FGPIO_ID_0,
        .base_addr = FGPIO_0_BASE_ADDR,
        .irq_num = FGPIO_0_IRQ_NUM,
        .irq_priority = 0
    },
    [FGPIO_ID_1] =
    {
        .instance_id = FGPIO_ID_1,
        .base_addr = FGPIO_1_BASE_ADDR,
        .irq_num = FGPIO_1_IRQ_NUM,
        .irq_priority = 0
    }
};
#elif defined(FGPIO_VERSION_2) /* E2000 GPIO 0 ~ 5 */
FGpioConfig fgpio_cfg_tbl[FGPIO_NUM] =
{
    [FGPIO_ID_0] =
    {
        .instance_id = FGPIO_ID_0,
        .base_addr = FGPIO_0_BASE_ADDR,
        .irq_priority = 0
    },
    [FGPIO_ID_1] =
    {
        .instance_id = FGPIO_ID_1,
        .base_addr = FGPIO_1_BASE_ADDR,
        .irq_priority = 0
    },
    [FGPIO_ID_2] =
    {
        .instance_id = FGPIO_ID_2,
        .base_addr = FGPIO_2_BASE_ADDR,
        .irq_priority = 0
    },
    [FGPIO_ID_3] =
    {
        .instance_id = FGPIO_ID_3,
        .base_addr = FGPIO_3_BASE_ADDR,
        .irq_priority = 0
    },
    [FGPIO_ID_4] =
    {
        .instance_id = FGPIO_ID_4,
        .base_addr = FGPIO_4_BASE_ADDR,
        .irq_priority = 0
    },
    [FGPIO_ID_5] =
    {
        .instance_id = FGPIO_ID_5,
        .base_addr = FGPIO_5_BASE_ADDR,
        .irq_priority = 0
    },
};
#endif