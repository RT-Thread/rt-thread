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
 * FilePath: fsdif_g.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:37:44
 * Description:  This file is for static init
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2021/12/2    init
 * 1.1   zhugengyu  2022/6/6     modify according to tech manual.
 * 2.0   zhugengyu  2023/9/16    rename as sdif, support SD 3.0 and rework clock timing
 */

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "fparameters.h"
#include "fsdif.h"
#include "fsdif_hw.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

const FSdifConfig FSDIF_CONFIG_TBL[FSDIF_NUM] =
{
    [FSDIF0_ID] =
    {
        .instance_id  = FSDIF0_ID,
        .base_addr    = FSDIF0_BASE_ADDR,
        .irq_num      = FSDIF0_IRQ_NUM,
        .trans_mode   = FSDIF_IDMA_TRANS_MODE,
        .non_removable  = FALSE,
        .get_tuning   = NULL,
    },

    [FSDIF1_ID] =
    {
        .instance_id = FSDIF1_ID,
        .base_addr   = FSDIF1_BASE_ADDR,
        .irq_num     = FSDIF1_IRQ_NUM,
        .trans_mode  = FSDIF_IDMA_TRANS_MODE,
        .non_removable  = FALSE,
        .get_tuning  = NULL,
    }
};


/*****************************************************************************/
