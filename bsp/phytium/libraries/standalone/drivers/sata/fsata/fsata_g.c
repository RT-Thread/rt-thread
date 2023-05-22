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
 * FilePath: fsata_g.c
 * Date: 2022-02-10 14:55:11
 * LastEditTime: 2022-02-18 09:03:08
 * Description:  This file is for static config of sata ctrl
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/2/10    first release
 * 1.1   wangxiaodong  2022/10/21   improve functions
 */

#include "fparameters.h"
#include "fsata.h"
#include "sdkconfig.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/


/* configs of pcie ahci ctrl */
const FSataConfig FSataPcieConfigTbl[PLAT_AHCI_HOST_MAX_COUNT] =
{
    [0] =
    {
        .base_addr = AHCI_BASE_0,
        .instance_name = "sata0",
        .irq_num = AHCI_IRQ_0     /* Irq number */

    },
    [1] =
    {
        .base_addr = AHCI_BASE_1,
        .instance_name = "sata1",
        .irq_num = AHCI_IRQ_1     /* Irq number */

    },
    [2] =
    {
        .base_addr = AHCI_BASE_2,
        .instance_name = "sata2",
        .irq_num = AHCI_IRQ_2     /* Irq number */

    },
    [3] =
    {
        .base_addr = AHCI_BASE_3,
        .instance_name = "sata3",
        .irq_num = AHCI_IRQ_3     /* Irq number */

    },
    [4] =
    {
        .base_addr = AHCI_BASE_4,
        .instance_name = "sata4",
        .irq_num = AHCI_IRQ_4     /* Irq number */

    },
};

#if defined(CONFIG_TARGET_E2000)

/* configs of controller ahci ctrl */
const FSataConfig FSataControllerConfigTbl[FSATA_NUM] =
{
    [0] =
    {
        .instance_id = FSATA0_ID,
        .base_addr = FSATA0_BASE_ADDR,
        .instance_name = "sata0",
        .irq_num = FSATA0_IRQ_NUM     /* Irq number */

    },
    [1] =
    {
        .instance_id = FSATA1_ID,
        .base_addr = FSATA1_BASE_ADDR,
        .instance_name = "sata1",
        .irq_num = FSATA1_IRQ_NUM     /* Irq number */

    },

};

#endif
