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
 * FilePath: fddma_g.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:24:47
 * Description:  This files is for ddma static configuration
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/5/13    init commit
 */

/***************************** Include Files *********************************/
#include "fparameters.h"

#include "fddma_hw.h"
#include "fddma.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/
const FDdmaConfig fddma_cfg_tbl[FDDMA_INSTANCE_NUM] =
{
    [FDDMA0_ID] =
    {
        .id = FDDMA0_ID,
        .base_addr = FDDMA0_BASE_ADDR,
        .irq_num = FDDMA0_IRQ_NUM,
        .irq_prority = 0
    },

    [FDDMA1_ID] =
    {
        .id = FDDMA1_ID,
        .base_addr = FDDMA1_BASE_ADDR,
        .irq_num = FDDMA1_IRQ_NUM,
        .irq_prority = 0
    }
}; /* DDMA控制器默认配置 */

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/