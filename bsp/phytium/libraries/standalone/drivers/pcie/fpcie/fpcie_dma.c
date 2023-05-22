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
 * FilePath: fpcie_dma.c
 * Date: 2022-08-10 14:55:11
 * LastEditTime: 2022-08-18 08:57:38
 * Description: This file is for pcie dma implementation.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe  2022/8/18   init commit
 */


#include "fpcie_hw.h"
#include "fpcie_dma.h"
#include "fpcie.h"
#include "ftypes.h"
#include "fcache.h"
#include "fkernel.h"
#include "fdebug.h"
/***************************** Include Files *********************************/

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/


#define FPCIE_DMA_DEBUG_TAG "FPCIE_DMA"
#define FPCIE_DMA_ERROR(format, ...) FT_DEBUG_PRINT_E(FPCIE_DMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_DMA_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FPCIE_DMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_DMA_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FPCIE_DMA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_DMA_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FPCIE_DMA_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/

/**
 * @name: FPcieDmaDescSet
 * @msg:  PCIE DMA descriptor group packet
 * @param {uintptr} axi_addr is memory address
 * @param {uintptr} bar_addr is Base Address Register value
 * @param {u32} length want to send byte length
 * @param {struct FPcieDmaDescriptor *}  desc Desc is the descriptor to be configured
 * @param {struct FPcieDmaDescriptor *}  next_desc is the next descriptor that needs to be sent
 * @return {FError}
 */
FError FPcieDmaDescSet(uintptr axi_addr,
                       uintptr bar_addr,
                       u32 length,
                       struct FPcieDmaDescriptor *desc,
                       struct FPcieDmaDescriptor *next_desc)
{
    /* 设置内存地址 */
    desc->axi_base_address = axi_addr;
    desc->axi_address_phase_controls = 0x00;

    /* 设置pcie空间地址 */
    desc->pcie_base_address = bar_addr;
    desc->pcie_tlp_header_attributes = 0x01;

    /* 设置数据长度， 设置dma完成中断 */
    desc->transfer_control = length;

    desc->axi_bus_status = 0x00;
    desc->pcie_bus_status = 0x00;
    desc->channel_status = 0x00;

    if (next_desc != NULL)
    {
        /* 使能链表模式 */
        desc->transfer_control &= ~(BIT(24));
        desc->transfer_control |= BIT(29);

        /* 设置下一级链表地址 */
        desc->next_descriptor = (uintptr)next_desc;
    }
    else
    {
        desc->transfer_control |= BIT(24);
        desc->transfer_control &= ~(BIT(29));
        desc->next_descriptor = 0;
    }

    return 0;
}

/**
 * @name: FPcieDmaRead
 * @msg:  Pcie reads through dma
 * @param {uintptr} bar_addr is Base Address Register value
 * @param {FPcieDmaDescriptor} *desc is first address of the receive descriptor
 */
void FPcieDmaRead(uintptr bar_address, struct FPcieDmaDescriptor *desc)
{
    /* The enable channel is interrupted */
    FPCIE_WRITEREG(bar_address, FPCIE_REG_DMA_INT_ENABLE_OFFSET, FPCIE_CTRL_DMA_INT_ENABLE_CH0_DONE_MASK | FPCIE_CTRL_DMA_INT_ENABLE_CH0_ERR_MASK);

    FPCIE_WRITEREG(bar_address, FPCIE_REG_DMA_CH0_SP_L_OFFSET, (u32)((uintptr)desc & 0xffffffffU));
#ifdef __aarch64__
    FPCIE_WRITEREG(bar_address, FPCIE_REG_DMA_CH0_SP_H_OFFSET, (u32)(((uintptr)desc >> 32) & 0xffffffffU));
#else
    FPCIE_WRITEREG(bar_address, FPCIE_REG_DMA_CH0_SP_H_OFFSET, 0);
#endif

    FPCIE_WRITEREG(bar_address, FPCIE_REG_DMA_CH0_CTRL_OFFSET, FPCIE_CTRL_DMA_CH0_CTRL_GO_MASK);
}

/**
 * @name: FPcieDmaWrite
 * @msg:  Pcie writes through dma
 * @param {uintptr} bar_address is Base Address Register value
 * @param {FPcieDmaDescriptor} *desc is first address of the send descriptor
 */

void FPcieDmaWrite(uintptr bar_address, struct FPcieDmaDescriptor *desc)
{
    /* The enable channel is interrupted */
    FPCIE_WRITEREG(bar_address, FPCIE_REG_DMA_INT_ENABLE_OFFSET, FPCIE_CTRL_DMA_INT_ENABLE_CH1_DONE_MASK | FPCIE_CTRL_DMA_INT_ENABLE_CH1_ERR_MASK);

    FPCIE_WRITEREG(bar_address, FPCIE_REG_DMA_CH1_SP_L_OFFSET, (u32)((uintptr)desc & 0xffffffffU));
#ifdef __aarch64__
    FPCIE_WRITEREG(bar_address, FPCIE_REG_DMA_CH1_SP_H_OFFSET, (u32)(((uintptr)desc >> 32) & 0xffffffffU));
#else
    FPCIE_WRITEREG(bar_address, FPCIE_REG_DMA_CH1_SP_H_OFFSET, 0);
#endif
    FPCIE_WRITEREG(bar_address, FPCIE_REG_DMA_CH1_CTRL_OFFSET, FPCIE_CTRL_DMA_CH1_CTRL_GO_MASK | FPCIE_CTRL_DMA_CH1_CTRL_OBNOTIB_MASK);
}

/**
 * @name: FPcieDmaPollDone
 * @msg:  Polling waits for DMA to complete
 * @param {FPcieDmaDescriptor *} desc is the current need to wait for dma to complete
 * @param {u32} wait_cnt is the count that needs to wait to end
 * @return FError
 */
FError FPcieDmaPollDone(struct FPcieDmaDescriptor *desc, u32 wait_cnt)
{
    FPCIE_DMA_DEBUG_I("Desc axi_bus_status :[0x%02x].", desc->axi_bus_status);
    FPCIE_DMA_DEBUG_I("Desc pcie_bus_status:[0x%02x].", desc->pcie_bus_status);
    FPCIE_DMA_DEBUG_I("Desc channel_status :[0x%02x].", desc->channel_status);

    while (wait_cnt > 0)
    {
        if (desc->channel_status == 0x1)
        {
            FPCIE_DMA_DEBUG_I("Dma channel transfer done.");
            return FT_SUCCESS;
        }
        wait_cnt--;
    }

    return FPCIE_ERR_TIMEOUT;
}
