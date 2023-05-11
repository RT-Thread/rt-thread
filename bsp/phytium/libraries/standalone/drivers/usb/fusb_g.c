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
 * FilePath: fusb_g.c
 * Date: 2022-02-11 13:33:11
 * LastEditTime: 2022-02-18 09:19:07
 * Description:  This files is for gloabl parameters
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

/***************************** Include Files *********************************/
#include "fparameters.h"
#include "fusb_private.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/
const FUsbConfig FUSBHC_CONFIG_TBL[FUSB3_NUM] =
{
    [FUSB3_ID_0] =
    {
        .instance_id = FUSB3_ID_0,
        .base_addr = FUSB3_0_BASE_ADDR,
        .irq_num = FUSB3_0_IRQ_NUM,
        .irq_priority = 0U,
        .allocator = NULL
    },

    [FUSB3_ID_1] =
    {
        .instance_id = FUSB3_ID_1,
        .base_addr = FUSB3_1_BASE_ADDR,
        .irq_num = FUSB3_1_IRQ_NUM,
        .irq_priority = 0U,
        .allocator = NULL
    }
};


/*****************************************************************************/
