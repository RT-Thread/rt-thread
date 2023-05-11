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
 * FilePath: fpcie_dma.h
 * Date: 2022-08-10 14:55:11
 * LastEditTime: 2022-08-18 08:57:51
 * Description: This file is for pcie dma definition.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe  2022/8/18   init commit
 */

#ifndef FPCIE_DMA_H
#define FPCIE_DMA_H

#include "ftypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

/***************************** Include Files *********************************/

/************************** Constant Definitions *****************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define DMA_XFER_START (0x01 << 0)
#define DMA_READ (0x00 << 1)
#define DMA_WRITE (0x01 << 1)

#define DMA_CHANNEL_READ_DONE (0x01 << 0)
#define DMA_CHANNEL_WRITE_DONE (0x01 << 1)
#define DMA_CHANNEL_READ_ERROR (0x01 << 8)
#define DMA_CHANNEL_WRITE_ERROR (0x01 << 9)

#define DMA_CHANNEL_READ_DONE_ENABLE (0x01 << 0)
#define DMA_CHANNEL_WRITE_DONE_ENABLE (0x01 << 1)
#define DMA_CHANNEL_READ_ERROR_ENABLE (0x01 << 8)
#define DMA_CHANNEL_WRITE_ERROR_ENABLE (0x01 << 9)
/************************** Function Prototypes ******************************/


/**************************** Type Definitions *******************************/

struct FPcieDmaDescriptor
{
    volatile u64 axi_base_address;           /* 0x00 */
    volatile u32 axi_address_phase_controls; /* 0x08 */
    volatile u64 pcie_base_address;          /* 0x12 */
    volatile u64 pcie_tlp_header_attributes; /* 0x20 */
    volatile u32 transfer_control;           /* 0x28 */
    volatile u8 axi_bus_status;              /* 0x32 */
    volatile u8 pcie_bus_status;             /* 0x33 */
    volatile u8 channel_status;              /* 0x34 */
    volatile u8 reserve;                     /* 0x35 */
    volatile u64 next_descriptor;            /* 0x36 */
} __attribute__((packed)) __attribute__((aligned(128)));

#ifdef __cplusplus
}
#endif

#endif // !