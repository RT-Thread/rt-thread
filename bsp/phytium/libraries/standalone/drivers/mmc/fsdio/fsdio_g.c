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
 * FilePath: fsdio_g.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:37:44
 * Description:  This file is for static init
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2021/12/2    init
 * 1.1   zhugengyu  2022/6/6     modify according to tech manual.
 */

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "fparameters.h"
#include "fsdio.h"
#include "fsdio_hw.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

const FSdioConfig FSDIO_CONFIG_TBL[FSDIO_NUM] =
{
    [FSDIO0_ID] =
    {
        .instance_id  = FSDIO0_ID,
        .base_addr    = FSDIO0_BASE_ADDR,
        .irq_num      = FSDIO0_IRQ_NUM,
        .trans_mode   = FSDIO_IDMA_TRANS_MODE,
        .voltage      = FSDIO_SD_3_3V_VOLTAGE,
        .non_removable  = FALSE,
        .filp_resp_byte_order = FALSE
    },

    [FSDIO1_ID] =
    {
        .instance_id = FSDIO1_ID,
        .base_addr   = FSDIO1_BASE_ADDR,
        .irq_num     = FSDIO1_IRQ_NUM,
        .trans_mode  = FSDIO_IDMA_TRANS_MODE,
        .voltage     = FSDIO_SD_3_3V_VOLTAGE,
        .non_removable  = FALSE,
        .filp_resp_byte_order = FALSE
    }
};


/*****************************************************************************/
