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
 * FilePath: fpcie_config.c
 * Date: 2022-08-10 14:55:11
 * LastEditTime: 2022-08-18 08:57:30
 * Description: This file is for pcie miscellaneous interrupt enable or disable. 
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe  2022/8/18   init commit
 */

#include "fpcie.h"
#include "fpcie_hw.h"

/***************************** Include Files *********************************/

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/**
 * @name: FPcieMiscIrqEnable
 * @msg:  开启PCIE 子系统中对应中断源的 misc 中断
 * @param {FPcie} *instance_p
 * @param {fsize_t} peu_num
 */
void FPcieMiscIrqEnable(FPcie *instance_p, fsize_t peu_num)
{
    u64 config_address;
    u32 reg_value;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(peu_num <= FPCIE_PEU1_C2);

    if (peu_num < FPCIE_PEU1_C0)
    {
        config_address = instance_p->config.peu0_config_address;
    }
    else
    {
        config_address = instance_p->config.peu1_config_address;
        peu_num -= FPCIE_PEU1_C0;
    }

    reg_value = FPCIE_READREG(config_address, FPCIE_REG_MISC_INT_ENALBE_OFFSET);
    FPCIE_WRITEREG(config_address, FPCIE_REG_MISC_INT_ENALBE_OFFSET, (reg_value | (1 << peu_num)));
}



/**
 * @name: FPcieMiscIrqDisable
 * @msg:  关闭PCIE 子系统中对应中断的 misc 中断
 * @param {FPcie} *instance_p is a pointer to the FPcie instance.
 * @param {fsize_t} peu_num is pci-e unit controller selection
 */
void FPcieMiscIrqDisable(FPcie *instance_p, fsize_t peu_num)
{
    uintptr_t config_address;
    u32 reg_value;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(peu_num <= FPCIE_PEU1_C2);

    if (peu_num < FPCIE_PEU1_C0)
    {
        config_address = instance_p->config.peu0_config_address;
    }
    else
    {
        config_address = instance_p->config.peu1_config_address;
        peu_num -= FPCIE_PEU1_C0;
    }

    reg_value = FPCIE_READREG(config_address, FPCIE_REG_MISC_INT_ENALBE_OFFSET);
    FPCIE_WRITEREG(config_address, FPCIE_REG_MISC_INT_ENALBE_OFFSET, (reg_value & ~(1 << peu_num)));
}


