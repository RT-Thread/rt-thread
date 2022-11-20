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
 * Date: 2022-02-10 14:55:11
 * LastEditTime: 2022-02-18 08:58:07
 * Description:  This files is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */


#include "fpcie.h"
#include "fpcie_hw.h"
#include "fparameters.h"
#include "sdkconfig.h"


FPcieConfig FPcieConfigTable[FT_PCIE_NUM] =
{
    {
        .instance_id = FT_PCIE0_ID, /* Id of device*/
        .irq_num = FT_PCIE0_MISC_IRQ_NUM,     // Irq number
        .ecam = FT_PCI_CONFIG_BASEADDR,  /* The Memory way */
        .peu0_config_address = FT_PCI_EU0_CONFIG_BASEADDR,
        .peu1_config_address = FT_PCI_EU1_CONFIG_BASEADDR,
        .control_c0_address = FT_PCI_EU0_C0_CONTROL_BASEADDR,
        .control_c1_address = FT_PCI_EU0_C1_CONTROL_BASEADDR,
        .control_c2_address = FT_PCI_EU0_C2_CONTROL_BASEADDR,
        .control_c3_address = FT_PCI_EU1_C0_CONTROL_BASEADDR,
        .control_c4_address = FT_PCI_EU1_C1_CONTROL_BASEADDR,
        .control_c5_address = FT_PCI_EU1_C2_CONTROL_BASEADDR,
#ifdef FT_PCI_INTX_EOI
        .intx_peux_stat_address =
        {
            [0] = FT_PCI_INTX_PEU0_STAT,
            [1] = FT_PCI_INTX_PEU1_STAT,
        },
        .intx_control_eux_cx_address =
        {
            [0] = FT_PCI_INTX_EU0_C0_CONTROL,
            [1] = FT_PCI_INTX_EU0_C1_CONTROL,
            [2] = FT_PCI_INTX_EU0_C2_CONTROL,
            [3] = FT_PCI_INTX_EU1_C0_CONTROL,
            [4] = FT_PCI_INTX_EU1_C1_CONTROL,
            [5] = FT_PCI_INTX_EU1_C2_CONTROL,
        },
#endif
        .io_base_addr = FT_PCI_IO_CONFIG_BASEADDR,
        .io_size = FT_PCI_IO_CONFIG_REG_LENGTH,
        .npmem_base_addr = FT_PCI_MEM32_BASEADDR,
        .npmem_size = FT_PCI_MEM32_REG_LENGTH,
        .pmem_base_addr = FT_PCI_MEM64_BASEADDR, /* Prefetchable memory */
        .pmem_size = FT_PCI_MEM64_REG_LENGTH,
        .inta_irq_num = FT_PCI_INTA_IRQ_NUM,
        .intb_irq_num = FT_PCI_INTB_IRQ_NUM,
        .intc_irq_num = FT_PCI_INTC_IRQ_NUM,
        .intd_irq_num = FT_PCI_INTD_IRQ_NUM,
        .need_skip = FT_PCI_NEED_SKIP
    }
};

