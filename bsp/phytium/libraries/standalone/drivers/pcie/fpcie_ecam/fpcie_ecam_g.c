/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
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
 * FilePath: fpcie_ecam_g.c
 * Created Date: 2023-08-01 08:59:53
 * Last Modified: 2023-08-08 19:14:03
 * Description:  This file is for
 *
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 * 1.0     huanghe    2023/08/06        first release
 */

#include "fpcie_ecam.h"
#include "fparameters.h"



FPcieEcamConfig FPcieEcamConfigTable[FPCIE_ECAM_INSTANCE_NUM] =
{
    {
        .instance_id = FPCIE_ECAM_INSTANCE0,
        .ecam = FPCI_ECAM_CONFIG_BASE_ADDR,

        .io_base_addr = FPCI_ECAM_IO_CONFIG_BASE_ADDR,
        .io_size  = FPCI_ECAM_IO_CONFIG_REG_LENGTH,
        .npmem_base_addr = FPCI_ECAM_MEM32_BASE_ADDR,
        .npmem_size = FPCI_ECAM_MEM32_REG_LENGTH,
        .pmem_base_addr = FPCI_ECAM_MEM64_BASE_ADDR, /* Prefetchable memory */
        .pmem_size = FPCI_ECAM_MEM64_REG_LENGTH,

        .inta_irq_num = FPCIE_ECAM_INTA_IRQ_NUM,
        .intb_irq_num = FPCIE_ECAM_INTB_IRQ_NUM,
        .intc_irq_num = FPCIE_ECAM_INTC_IRQ_NUM,
        .intd_irq_num = FPCIE_ECAM_INTD_IRQ_NUM,


        .max_bus_num = FPCIE_ECAM_CFG_MAX_NUM_OF_BUS,
        .max_dev_num = FPCIE_ECAM_CFG_MAX_NUM_OF_DEV,
        .max_fun_num = FPCIE_ECAM_CFG_MAX_NUM_OF_FUN,
#ifdef FPCI_ECAM_INTX_NEED_EOI

        .control_intx_base =
        {
            [0] = FPCI_ECAM_INTX_CONTROL_STATUS_REG0,
            [1] = FPCI_ECAM_INTX_CONTROL_STATUS_REG1
        },
        .config_intx_base =
        {
            [0] = FPCI_ECAM_INTX_CONFIG_ISTATUS_REG0,
            [1] = FPCI_ECAM_INTX_CONFIG_ISTATUS_REG1,
            [2] = FPCI_ECAM_INTX_CONFIG_ISTATUS_REG2,
            [3] = FPCI_ECAM_INTX_CONFIG_ISTATUS_REG3,
            [4] = FPCI_ECAM_INTX_CONFIG_ISTATUS_REG4,
            [5] = FPCI_ECAM_INTX_CONFIG_ISTATUS_REG5,
        },
#endif

    }
};