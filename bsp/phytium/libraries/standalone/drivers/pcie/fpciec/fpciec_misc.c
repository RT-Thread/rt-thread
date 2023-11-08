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
 * FilePath: fpciec_misc.c
 * Created Date: 2023-07-06 16:20:15
 * Last Modified: 2023-08-08 10:16:09
 * Description:  This file is for pciec misc interrupt handler functions
 *
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 * 1.0     huanghe    2023/08/06        first release
 */


#include "fpciec_hw.h"
#include "fpciec.h"
#include "fassert.h"

#include "fdrivers_port.h"


#define FPCIE_MISC_DEBUG_TAG "FPCIE_MISC"
#define FPCIE_MISC_ERROR(format, ...) FT_DEBUG_PRINT_E(FPCIE_MISC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_MISC_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FPCIE_MISC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_MISC_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FPCIE_MISC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_MISC_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FPCIE_MISC_DEBUG_TAG, format, ##__VA_ARGS__)



#define FPCIEC_MISC_IRQ_MASK 0xffffffffU

FError FPcieCMiscIrqRegister(FPcieC *instance_p, FPcieCMiscIrqCallBack misc_irq, void *args)
{
    FASSERT(instance_p != NULL);

    instance_p->misc_irq =  misc_irq ;
    instance_p->args =  args ;

    return FT_SUCCESS ;
}

void FPcieCMiscIrq(s32 vector, void *args)
{
    FPcieC *instance_p = (FPcieC *)(args) ;
    u32 mask_reg, status_reg ;
    uintptr_t control_space ;
    control_space = instance_p->config.control_space ;

    /* check dma engine */
    mask_reg = FPCIEC_HW_READW(control_space, FPCIEC_IMASK_LOCAL_REG) ;
    status_reg = FPCIEC_HW_READW(control_space, FPCIEC_ISTATUS_LOCAL_REG) ;
    if ((mask_reg & FPCIEC_IMASK_HOST_DMAX_END(0xff)))
    {
        FPCIEC_HW_WRITEW(instance_p->config.config_space, 0xd0, 1 << 6) ;
        status_reg &= mask_reg ;
        for (size_t i = 0; i < 8; i++)
        {
            if (mask_reg & (1 << i))
            {
                instance_p->misc_irq(i, instance_p->args)  ;
            }
        }
    }

}

/**
 * @name: FPcieCMiscIrqConfig
 * @msg: Configures interrupt masking for miscellaneous interrupt types.
 * @param {FPcieC *} instance_p - Pointer to the FPcieC instance.
 * @param {u32} irq_type - The type of miscellaneous interrupt to configure.
 * @param {bool} set - If true, set the interrupt mask; otherwise, clear it.
 * @return {FError} - Returns FT_SUCCESS if successful, or an error code.
 */
FError FPcieCMiscIrqConfig(FPcieC *instance_p, u32 irq_type, bool set)
{
    u32 reg ;
    uintptr_t control_space = 0 ;
    FASSERT(instance_p != NULL);
    control_space = instance_p->config.control_space ;
    FASSERT(control_space != (uintptr_t)NULL) ;

    if (irq_type > FPCIEC_MISC_TYPE_DMA7_ERROR)
    {
        return FPCIEC_MISC_IRQ_OUTRANGE;
    }


    reg = FPCIEC_HW_READW(control_space, FPCIEC_IMASK_LOCAL_REG) ;

    if (set)
    {
        reg |= (1 << irq_type) ;
        FPCIEC_HW_WRITEW(instance_p->config.config_space, 0xc4, 1 << 6) ;
        FPCIEC_HW_WRITEW(instance_p->config.config_space, 0xc8, 1 << 6) ;
    }
    else
    {
        reg &= ~(1 << irq_type) ;
        FPCIEC_HW_WRITEW(instance_p->config.config_space, 0xc4, 0) ;
        FPCIEC_HW_WRITEW(instance_p->config.config_space, 0xc8, 0) ;
    }

    FPCIEC_HW_WRITEW(control_space, FPCIEC_IMASK_LOCAL_REG, reg) ;

    return FT_SUCCESS ;
}


void FPcieCMiscIrqInit(FPcieC *instance_p)
{
    uintptr_t control_space = 0 ;
    FASSERT(instance_p != NULL);
    control_space = instance_p->config.control_space ;
    FASSERT(control_space != (uintptr_t)NULL) ;

    /* close all irq */
    FPCIEC_HW_WRITEW(control_space, FPCIEC_IMASK_LOCAL_REG, 0) ;
    FPCIEC_HW_WRITEW(control_space, FPCIEC_IMASK_HOST_REG, 0) ;
    /* clear all status */
    FPCIEC_HW_WRITEW(control_space, FPCIEC_ISTATUS_LOCAL_REG, FPCIEC_MISC_IRQ_MASK) ;
    FPCIEC_HW_WRITEW(control_space, FPCIEC_ISTATUS_HOST_REG, FPCIEC_MISC_IRQ_MASK) ;
}
