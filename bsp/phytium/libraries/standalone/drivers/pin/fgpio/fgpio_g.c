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
 * 1.0   zhugengyu  2022/3/1     init commit
 * 2.0   zhugengyu  2022/7/1     support e2000
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
    [FGPIO0_ID] =
    {
        .instance_id = FGPIO0_ID,
        .base_addr = FGPIO0_BASE_ADDR,
        .irq_num = FGPIO0_IRQ_NUM,
        .irq_priority = 0
    },
    [FGPIO1_ID] =
    {
        .instance_id = FGPIO1_ID,
        .base_addr = FGPIO1_BASE_ADDR,
        .irq_num = FGPIO1_IRQ_NUM,
        .irq_priority = 0
    }
};
#elif defined(FGPIO_VERSION_2) /* E2000 GPIO 0 ~ 5 */
FGpioConfig fgpio_cfg_tbl[FGPIO_NUM] =
{
    [FGPIO0_ID] =
    {
        .instance_id = FGPIO0_ID,
        .base_addr = FGPIO0_BASE_ADDR,
        .irq_priority = 0
    },
    [FGPIO1_ID] =
    {
        .instance_id = FGPIO1_ID,
        .base_addr = FGPIO1_BASE_ADDR,
        .irq_priority = 0
    },
    [FGPIO2_ID] =
    {
        .instance_id = FGPIO2_ID,
        .base_addr = FGPIO2_BASE_ADDR,
        .irq_priority = 0
    },
    [FGPIO3_ID] =
    {
        .instance_id = FGPIO3_ID,
        .base_addr = FGPIO3_BASE_ADDR,
        .irq_priority = 0
    },
    [FGPIO4_ID] =
    {
        .instance_id = FGPIO4_ID,
        .base_addr = FGPIO4_BASE_ADDR,
        .irq_priority = 0
    },
    [FGPIO5_ID] =
    {
        .instance_id = FGPIO5_ID,
        .base_addr = FGPIO5_BASE_ADDR,
        .irq_priority = 0
    },
};
#elif defined(TARDIGRADE) /* TARDIGRADE */
const FGpioConfig fgpio_cfg_tbl[FGPIO_NUM] =
{
    [FGPIO0_ID] =
    {
        .instance_id = FGPIO0_ID,
        .base_addr = FGPIO0_BASE_ADDR,
        .irq_num = FGPIO0_IRQ_NUM,
        .irq_priority = 0
    },
    [FGPIO1_ID] =
    {
        .instance_id = FGPIO1_ID,
        .base_addr = FGPIO1_BASE_ADDR,
        .irq_num = FGPIO1_IRQ_NUM,
        .irq_priority = 0
    },
    [FGPIO2_ID] =
    {
        .instance_id = FGPIO2_ID,
        .base_addr = FGPIO2_BASE_ADDR,
        .irq_num = FGPIO2_IRQ_NUM,
        .irq_priority = 0
    },
    [FGPIO3_ID] =
    {
        .instance_id = FGPIO3_ID,
        .base_addr = FGPIO3_BASE_ADDR,
        .irq_num = FGPIO3_IRQ_NUM,
        .irq_priority = 0
    }

};
#endif