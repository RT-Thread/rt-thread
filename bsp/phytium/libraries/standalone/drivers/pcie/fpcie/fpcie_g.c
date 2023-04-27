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
 * FilePath: fpcie_g.c
 * Date: 2022-08-10 14:55:11
 * LastEditTime: 2022-08-18 08:58:07
 * Description: This file is for pcie static configuration implementation.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe  2022/8/18   init commit
 */


#include "fpcie.h"
#include "fpcie_hw.h"
#include "fparameters.h"
#include "sdkconfig.h"


FPcieConfig FPcieConfigTable[FPCIE_NUM] =
{
    {
        .instance_id = FPCIE0_ID, /* Id of device*/
        .irq_num = FPCIE0_MISC_IRQ_NUM,     // Irq number
        .ecam = FPCI_CONFIG_BASE_ADDR,  /* The Memory way */
        .peu0_config_address = FPCI_EU0_CONFIG_BASE_ADDR,
        .peu1_config_address = FPCI_EU1_CONFIG_BASE_ADDR,
        .control_c0_address = FPCI_EU0_C0_CONTROL_BASE_ADDR,
        .control_c1_address = FPCI_EU0_C1_CONTROL_BASE_ADDR,
        .control_c2_address = FPCI_EU0_C2_CONTROL_BASE_ADDR,
        .control_c3_address = FPCI_EU1_C0_CONTROL_BASE_ADDR,
        .control_c4_address = FPCI_EU1_C1_CONTROL_BASE_ADDR,
        .control_c5_address = FPCI_EU1_C2_CONTROL_BASE_ADDR,
#ifdef FPCI_INTX_EOI
        .intx_peux_stat_address =
        {
            [0] = FPCI_INTX_PEU0_STAT,
            [1] = FPCI_INTX_PEU1_STAT,
        },
        .intx_control_eux_cx_address =
        {
            [0] = FPCI_INTX_EU0_C0_CONTROL,
            [1] = FPCI_INTX_EU0_C1_CONTROL,
            [2] = FPCI_INTX_EU0_C2_CONTROL,
            [3] = FPCI_INTX_EU1_C0_CONTROL,
            [4] = FPCI_INTX_EU1_C1_CONTROL,
            [5] = FPCI_INTX_EU1_C2_CONTROL,
        },
#endif
        .io_base_addr = FPCI_IO_CONFIG_BASE_ADDR,
        .io_size = FPCI_IO_CONFIG_REG_LENGTH,
        .npmem_base_addr = FPCI_MEM32_BASE_ADDR,
        .npmem_size = FPCI_MEM32_REG_LENGTH,
        .pmem_base_addr = FPCI_MEM64_BASE_ADDR, /* Prefetchable memory */
        .pmem_size = FPCI_MEM64_REG_LENGTH,
        .inta_irq_num = FPCI_INTA_IRQ_NUM,
        .intb_irq_num = FPCI_INTB_IRQ_NUM,
        .intc_irq_num = FPCI_INTC_IRQ_NUM,
        .intd_irq_num = FPCI_INTD_IRQ_NUM,
        .need_skip = FPCI_NEED_SKIP
    }
};

