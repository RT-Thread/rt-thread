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
 * FilePath: fspim_g.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 09:07:55
 * Description:  This file is for providing spim basic information.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2021/12/3   init commit
 * 1.1   zhugengyu  2022/4/15   support test mode
 */

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "fparameters.h"
#include "sdkconfig.h"

#include "fspim.h"
#include "fspim_hw.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

const FSpimConfig FSPIM_CONFIG_TBL[FSPI_NUM] =
{
    [FSPI0_ID] =
    {
        .instance_id  = FSPI0_ID, /* Id of device*/
        .base_addr = FSPI0_BASE_ADDR,
        .irq_num = FSPI0_IRQ_NUM,
        .irq_prority = 0,
        .work_mode = FSPIM_DEV_MASTER_MODE,
        .slave_dev_id = FSPIM_SLAVE_DEV_0,
        .max_freq_hz  = 4000000,
        .n_bytes      = 1,
        .en_test = FALSE,
        .en_dma  = FALSE
    },
    [FSPI1_ID] =
    {
        .instance_id  = FSPI1_ID, /* Id of device*/
        .base_addr = FSPI1_BASE_ADDR,
        .irq_num = FSPI1_IRQ_NUM,
        .irq_prority = 0,
        .work_mode = FSPIM_DEV_MASTER_MODE,
        .slave_dev_id = FSPIM_SLAVE_DEV_0,
        .max_freq_hz  = 4000000,
        .n_bytes      = 1,
        .en_test = FALSE,
        .en_dma  = FALSE
    },
#if defined(CONFIG_TARGET_E2000)
    [FSPI2_ID] =
    {
        .instance_id  = FSPI2_ID, /* Id of device*/
        .base_addr = FSPI2_BASE,
        .irq_num = FSPI2_IRQ_NUM,
        .irq_prority = 0,
        .work_mode = FSPIM_DEV_MASTER_MODE,
        .slave_dev_id = FSPIM_SLAVE_DEV_0,
        .max_freq_hz  = 4000000,
        .n_bytes      = 1,
        .en_test = FALSE,
        .en_dma  = FALSE
    },
    [FSPI3_ID] =
    {
        .instance_id  = FSPI3_ID, /* Id of device*/
        .base_addr = FSPI3_BASE,
        .irq_num = FSPI3_IRQ_NUM,
        .irq_prority = 0,
        .work_mode = FSPIM_DEV_MASTER_MODE,
        .slave_dev_id = FSPIM_SLAVE_DEV_0,
        .max_freq_hz  = 4000000,
        .n_bytes      = 1,
        .en_test = FALSE,
        .en_dma  = FALSE
    },
#endif
};


/*****************************************************************************/
