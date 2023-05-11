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
 * FilePath: fpcie_misc.c
 * Date: 2022-08-10 14:55:11
 * LastEditTime: 2022-08-18 08:59:17
 * Description: This file is for pcie miscellaneous interrupt operation. 
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe  2022/8/18   init commit
 */


#include "fpcie.h"
#include "fpcie_hw.h"
#include "fassert.h"
#include "fdebug.h"


/***************************** Include Files *********************************/

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FPCIE_INTR_DEBUG_TAG "FPCIE_INTR"
#define FPCIE_INTR_ERROR(format, ...) FT_DEBUG_PRINT_E(FPCIE_INTR_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_INTR_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FPCIE_INTR_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_INTR_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FPCIE_INTR_DEBUG_TAG, format, ##__VA_ARGS__)
/************************** Function Prototypes ******************************/

FError FPcieMiscSetHandler(FPcie *instance_p, u32 handler_type,
                           void *func_pointer, void *call_back_ref)
{
    FError status;
    FASSERT(instance_p != NULL);
    FASSERT(func_pointer != NULL);
    FASSERT(instance_p->is_ready == (u32)FT_COMPONENT_IS_READY);

    switch (handler_type)
    {
        case FPCIE_HANDLER_DMASEND:
            status = FT_SUCCESS;
            instance_p->fpcie_dma_tx_cb = ((FPcieIrqCallBack)(void *)func_pointer);
            instance_p->dma_tx_args = call_back_ref;
            break;
        case FPCIE_HANDLER_DMARECV:
            status = FT_SUCCESS;
            instance_p->fpcie_dma_rx_cb = ((FPcieIrqCallBack)(void *)func_pointer);
            instance_p->dma_rx_args = call_back_ref;
            break;
        case FPCIE_HANDLER_DMASEND_ERROR:
            status = FT_SUCCESS;
            instance_p->fpcie_dma_tx_error_cb = ((FPcieIrqCallBack)(void *)func_pointer);
            instance_p->dma_tx_error_args = call_back_ref;
            break;
        case FPCIE_HANDLER_DMARECV_ERROR:
            status = FT_SUCCESS;
            instance_p->fpcie_dma_rx_error_cb = ((FPcieIrqCallBack)(void *)func_pointer);
            instance_p->dma_rx_error_args = call_back_ref;
            break;
        default:
            status = FPCIE_ERR_INVALID_PARAM;
            break;
    }
    return status;
}

void FPcieMiscIrq(s32 vector, void *args)
{
    FPcie *instance_p = (FPcie *)args;
    uintptr_t control_address;
    u32 reg_value;
    (void)vector;
    FASSERT(instance_p != NULL);

    if (FPCIE_READREG(instance_p->config.peu0_config_address, FPCIE_REG_MISC_INT_STATE_OFFSET) & FPCIE_MISC_STATE_C0_DMA_INT_MASK)
    {
        FPCIE_INTR_DEBUG_I("PEU0 C0 DMA IRQ!");
        control_address = instance_p->config.control_c0_address;
    }
    else if (FPCIE_READREG(instance_p->config.peu0_config_address, FPCIE_REG_MISC_INT_STATE_OFFSET) & FPCIE_MISC_STATE_C1_DMA_INT_MASK)
    {
        FPCIE_INTR_DEBUG_I("PEU0 C1 DMA IRQ!");
        control_address = instance_p->config.control_c1_address;
    }
    else if (FPCIE_READREG(instance_p->config.peu0_config_address, FPCIE_REG_MISC_INT_STATE_OFFSET) & FPCIE_MISC_STATE_C2_DMA_INT_MASK)
    {
        FPCIE_INTR_DEBUG_I("PEU0 C2 DMA IRQ!");
        control_address = instance_p->config.control_c2_address;
    }
    else if (FPCIE_READREG(instance_p->config.peu1_config_address, FPCIE_REG_MISC_INT_STATE_OFFSET) & FPCIE_MISC_STATE_C0_DMA_INT_MASK)
    {
        FPCIE_INTR_DEBUG_I("PEU0 C0 DMA IRQ!");
        control_address = instance_p->config.control_c3_address;
    }
    else if (FPCIE_READREG(instance_p->config.peu1_config_address, FPCIE_REG_MISC_INT_STATE_OFFSET) & FPCIE_MISC_STATE_C1_DMA_INT_MASK)
    {
        FPCIE_INTR_DEBUG_I("PEU0 C1 DMA IRQ!");
        control_address = instance_p->config.control_c4_address;
    }
    else if (FPCIE_READREG(instance_p->config.peu1_config_address, FPCIE_REG_MISC_INT_STATE_OFFSET) & FPCIE_MISC_STATE_C2_DMA_INT_MASK)
    {
        FPCIE_INTR_DEBUG_I("PEU0 C2 DMA IRQ!");
        control_address = instance_p->config.control_c5_address;
    }

    FPCIE_INTR_DEBUG_I("Pcie misc irq!");
    FPCIE_INTR_DEBUG_I("Pcie dma irq status : 0x%08lx", FPCIE_READREG(control_address, FPCIE_REG_DMA_INT_STATUS_OFFSET));

    reg_value = FPCIE_READREG(control_address, FPCIE_REG_DMA_INT_STATUS_OFFSET);

    if (reg_value & FPCIE_CTRL_DMA_INT_STATUS_CH0_DONE_MASK)
    {
        if (instance_p->fpcie_dma_rx_cb)
        {
            instance_p->fpcie_dma_rx_cb(instance_p->dma_rx_args);
        }
    }

    if (reg_value & FPCIE_CTRL_DMA_INT_STATUS_CH1_DONE_MASK)
    {
        if (instance_p->fpcie_dma_tx_cb)
        {
            instance_p->fpcie_dma_tx_cb(instance_p->dma_tx_args);
        }
    }

    if (reg_value & FPCIE_CTRL_DMA_INT_STATUS_CH0_ERR_MASK)
    {
        if (instance_p->fpcie_dma_rx_error_cb)
        {
            instance_p->fpcie_dma_rx_error_cb(instance_p->dma_rx_error_args);
        }
    }

    if (reg_value & FPCIE_CTRL_DMA_INT_STATUS_CH1_ERR_MASK)
    {
        if (instance_p->fpcie_dma_tx_error_cb)
        {
            instance_p->fpcie_dma_tx_error_cb(instance_p->dma_tx_error_args);
        }
    }

    FPCIE_WRITEREG(control_address, FPCIE_REG_DMA_INT_STATUS_OFFSET, FPCIE_CTRL_DMA_INT_STATUS_ALL_MASK);
}