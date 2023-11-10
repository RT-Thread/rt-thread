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
 * FilePath: fpciec_dma.h
 * Created Date: 2023-08-02 09:40:08
 * Last Modified: 2023-08-02 10:38:44
 * Description:  This file is for
 *
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 * 1.0     huanghe    2023/08/06        first release
 */
#ifndef FPCIEC_DMA_H
#define FPCIEC_DMA_H

#include "ftypes.h"
#include "fio.h"
#include "ferror_code.h"
#include "fkernel.h"

#ifdef __cplusplus
extern "C"
{
#endif
#define FPCIEC_DMA_ENGINE_OFFSET             0x400
#define FPCIEC_DMA_CH_ENGINE_OFFSET(x)      (x*0x40)

#define FPCIEC_DMA_SRCPARAM_OFFSET 0
#define FPCIEC_DMA_DMA_DESTPARAM_OFFSET      0x4
#define FPCIEC_DMA_SRCADDR_OFFSET            0x8
#define FPCIEC_DMA_SRCADDR_UPPER32_OFFSET    0xC
#define FPCIEC_DMA_DMA_DESTADDR_OFFSET       0x10
#define FPCIEC_DMA_DMA_DESTADDR_UPEER32_OFFSET       0x14
#define FPCIEC_DMA_DMA_LENGTH_OFFSET         0x18
#define FPCIEC_DMA_CONTROL_OFFSET            0x1c
#define FPCIEC_DMA_STATUS_OFFSET             0x20
#define FPCIEC_DMA_PRC_LENGTH_OFFSET               0X24
#define FPCIEC_DMA_SHARE_ACCESS_OFFSET             0x28
#define FPCIEC_DMA_PASID_OFFSET              0x2c
#define FPCIEC_DMA_REG_LENGTH                0x40

/* FPCIEC_DMA_SRCPARAM_OFFSET */
#define FPCIEC_DMA_SRCID_PCIE 0
#define FPCIEC_DMA_SRCID_AXI_MASTER(num) ((num) &0xf)
/* Master Interface */
#define FPCIEC_DMA_SRC_ID_AXI_MASTER_X(x) FPCIEC_DMA_SRCID_AXI_MASTER(0x4 + x)
#define FPCIEC_DMA_SRC_ID_AXI_MASTER_0 FPCIEC_DMA_SRCID_AXI_MASTER(0x4)
#define FPCIEC_DMA_SRC_ID_AXI_MASTER_1 FPCIEC_DMA_SRCID_AXI_MASTER(0x5)
#define FPCIEC_DMA_SRC_ID_AXI_MASTER_2 FPCIEC_DMA_SRCID_AXI_MASTER(0x6)
#define FPCIEC_DMA_SRC_ID_AXI_MASTER_3 FPCIEC_DMA_SRCID_AXI_MASTER(0x7)

/* TRSF_PARAM */
#define FPCIEC_SRC_TRSF_PARAM(num)   (((num)<<16) & 0xfff0000)


/* FPCIEC_DMA_DMA_DESTPARAM_OFFSET */
#define FPCIEC_DMA_DESTID_PCIE 0
#define FPCIEC_DMA_DESTID_AXI_MASTER(num) ((num) &0xff)
/* Master Interface */
#define FPCIEC_DMA_DEST_ID_AXI_MASTER_X(x) FPCIEC_DMA_DESTID_AXI_MASTER(x + 0x4)
#define FPCIEC_DMA_DEST_ID_AXI_MASTER_0 FPCIEC_DMA_DESTID_AXI_MASTER(0x4)
#define FPCIEC_DMA_DEST_ID_AXI_MASTER_0 FPCIEC_DMA_DESTID_AXI_MASTER(0x4)
#define FPCIEC_DMA_DEST_ID_AXI_MASTER_1 FPCIEC_DMA_DESTID_AXI_MASTER(0x5)
#define FPCIEC_DMA_DEST_ID_AXI_MASTER_2 FPCIEC_DMA_DESTID_AXI_MASTER(0x6)
#define FPCIEC_DMA_DEST_ID_AXI_MASTER_3 FPCIEC_DMA_DESTID_AXI_MASTER(0x7)

/* TRSF_PARAM */
#define FPCIEC_DEST_TRSF_PARAM(num)   (((num)<<16) & 0xfff0000)



/* FPCIEC_DMA_CONTROL_OFFSET */
/* Start/Abort */
#define FPCIEC_DMA_START_ABORT_OFFSET 0
/* Pause/Resume */
#define FPCIEC_DMA_PAUSE_RESUME_OFFSET 1
/*  SG mode  */
#define FPCIEC_DMA_ENABLE_SG_MODE_OFFSET 3
#define FPCIEC_DMA_START_MASK (1 << FPCIEC_DMA_START_ABORT_OFFSET)
#define FPCIEC_DMA_PAUSE_MASK (1 << FPCIEC_DMA_PAUSE_RESUME_OFFSET)
#define FPCIEC_DMA_ENABLE_SG_MODE_MASK (1 << FPCIEC_DMA_ENABLE_SG_MODE_OFFSET)


/* Start and End conditions of the DMA */
#define FPCIEC_DMA_SE_COND_OFFSET 4
/* Bit [4] - Reserved */
#define FPCIEC_DMA_RESERVED_SE_COND_OFFSET 4
/* Bit [5] - Stop if DMA_LENGTH is reached */
#define FPCIEC_DMA_STOP_DMA_LENGTH_OFFSET 5
/* Bit [6] - Stop DMA if AXI-Stream Interface's EOP condition (TLAST received) */
#define FPCIEC_DMA_STOP_AXI_STREAM_EOP_OFFSET 6
/* Bit [7] - Abort on error condition */
#define FPCIEC_DMA_ABORT_ON_ERROR_OFFSET 7

#define FPCIEC_DMA_SE_COND_MASK (0xF << FPCIEC_DMA_SE_COND_OFFSET)
#define FPCIEC_DMA_RESERVED_SE_COND_MASK (1 << FPCIEC_DMA_RESERVED_SE_COND_OFFSET)
#define FPCIEC_DMA_STOP_DMA_LENGTH_MASK (1 << FPCIEC_DMA_STOP_DMA_LENGTH_OFFSET)
#define FPCIEC_DMA_STOP_AXI_STREAM_EOP_MASK (1 << FPCIEC_DMA_STOP_AXI_STREAM_EOP_OFFSET)
#define FPCIEC_DMA_ABORT_ON_ERROR_MASK (1 << FPCIEC_DMA_ABORT_ON_ERROR_OFFSET)

/* Defines when an interrupt should be issued */
#define FPCIEC_DMA_IRQ_OFFSET 8

/* Bit [8] - IRQ on DMA end */
#define FPCIEC_DMA_IRQ_END_OFFSET 8
/* Bit [9] - IRQ on error */
#define FPCIEC_DMA_IRQ_ERROR_OFFSET 9
/* Bit [10] - IRQ on source EOP condition */
#define FPCIEC_DMA_IRQ_AXI_STREAM_EOP_OFFSET 10


#define FPCIEC_DMA_IRQ_MASK (0xF << FPCIEC_DMA_IRQ_OFFSET)

#define FPCIEC_DMA_IRQ_END_MASK (1 << FPCIEC_DMA_IRQ_END_OFFSET)
#define FPCIEC_DMA_IRQ_ERROR_MASK (1 << FPCIEC_DMA_IRQ_ERROR_OFFSET)
#define FPCIEC_DMA_IRQ_AXI_STREAM_EOP_MASK (1 << FPCIEC_DMA_IRQ_AXI_STREAM_EOP_OFFSET)

/* Defines on which interface DMA transfer events should be reported */
#define FPCIEC_DMA_IRQ_ID_OFFSET 12
/* Bit [12] - interrupt is issued to the Local Processor (on AXI domain) */
#define FPCIEC_DMA_IRQ_LOCAL_PROC_OFFSET 12
/* Bit [13] - interrupt is issued to the Host Processor (on PCIe domain) */
#define FPCIEC_DMA_IRQ_HOST_PROC_OFFSET 13

#define FPCIEC_DMA_IRQ_ID_MASK (0x3 << FPCIEC_DMA_IRQ_ID_OFFSET)
#define FPCIEC_DMA_IRQ_LOCAL_PROC_MASK (1 << FPCIEC_DMA_IRQ_LOCAL_PROC_OFFSET)
#define FPCIEC_DMA_IRQ_HOST_PROC_MASK (1 << FPCIEC_DMA_IRQ_HOST_PROC_OFFSET)

/* Bit [23] - DESC_UPDT */
#define FPCIEC_DMA_DESC_UPDT_OFFSET 23

#define FPCIEC_DMA_DESC_UPDT_MASK (1 << FPCIEC_DMA_DESC_UPDT_OFFSET)

/* Bit [25:24] - SG_TYPE: defines the Scatter-Gather type for the DMA */
#define FPCIEC_DMA_SG_TYPE_OFFSET 24
#define FPCIEC_DMA_SG_TYPE_MASK (0x3 << FPCIEC_DMA_SG_TYPE_OFFSET)

/* SG_TYPE options */
#define FPCIEC_DMA_SG_TYPE_INDEPENDENT  (0b00 << FPCIEC_DMA_SG_TYPE_OFFSET)
#define FPCIEC_DMA_SG_TYPE_SRC_INCREMENT (0b01 << FPCIEC_DMA_SG_TYPE_OFFSET)
#define FPCIEC_DMA_SG_TYPE_DST_INCREMENT (0b10 << FPCIEC_DMA_SG_TYPE_OFFSET)
#define FPCIEC_DMA_SG_TYPE_BOTH_INCREMENT (0b11 << FPCIEC_DMA_SG_TYPE_OFFSET)

/* Bit [28:26] - SG_ID: define on which interface the descriptors should be read */
#define FPCIEC_DMA_SG_ID_OFFSET 26
#define FPCIEC_DMA_SG_ID_MASK (0x7 << FPCIEC_DMA_SG_ID_OFFSET)

/* SG_ID options */
#define FPCIEC_DMA_SG_ID_PCIE               (0b000 << FPCIEC_DMA_SG_ID_OFFSET )
#define FPCIEC_DMA_SG_ID_AXI_MASTER_DESC    (0b011 << FPCIEC_DMA_SG_ID_OFFSET )
#define FPCIEC_DMA_SG_ID_AXI_MASTER_0       (0b100 << FPCIEC_DMA_SG_ID_OFFSET )
#define FPCIEC_DMA_SG_ID_AXI_MASTER_1       (0b101 << FPCIEC_DMA_SG_ID_OFFSET )
#define FPCIEC_DMA_SG_ID_AXI_MASTER_2       (0b110 << FPCIEC_DMA_SG_ID_OFFSET )
#define FPCIEC_DMA_SG_ID_AXI_MASTER_3       (0b111 << FPCIEC_DMA_SG_ID_OFFSET )

/* Bit [31:29] - SG2_ID: define on which interface the descriptors should be read */
#define FPCIEC_DMA_SG2_ID_OFFSET 29
#define FPCIEC_DMA_SG2_ID_MASK (0x7 << FPCIEC_DMA_SG2_ID_OFFSET)

/* SG2_ID options (Same as SG_ID options) */
#define FPCIEC_DMA_SG2_ID_PCIE               (0b000 << FPCIEC_DMA_SG2_ID_OFFSET )
#define FPCIEC_DMA_SG2_ID_AXI_MASTER_DESC    (0b011 << FPCIEC_DMA_SG2_ID_OFFSET )
#define FPCIEC_DMA_SG2_ID_AXI_MASTER_0       (0b100 << FPCIEC_DMA_SG2_ID_OFFSET )
#define FPCIEC_DMA_SG2_ID_AXI_MASTER_1       (0b101 << FPCIEC_DMA_SG2_ID_OFFSET )
#define FPCIEC_DMA_SG2_ID_AXI_MASTER_2       (0b110 << FPCIEC_DMA_SG2_ID_OFFSET )
#define FPCIEC_DMA_SG2_ID_AXI_MASTER_3       (0b111 << FPCIEC_DMA_SG2_ID_OFFSET )


/* FPCIEC_DMA_STATUS_OFFSET */

#define FPCIEC_DMA_STATUS_MASK 0xFF


/* Status bit definitions */
#define FPCIEC_DMA_STATUS_COMPLETE_WITH_LENGTH_REACHED  (1 << 0)
#define FPCIEC_DMA_STATUS_COMPLETE_WITH_EOP             (1 << 1)
#define FPCIEC_DMA_STATUS_COMPLETE_WITH_EOC             (1 << 2)
#define FPCIEC_DMA_STATUS_COMPLETE_WITH_ERROR           (1 << 3)
#define FPCIEC_DMA_STATUS_COMPLETE_WITH_MORE_THAN_4GB   (1 << 4)
#define FPCIEC_DMA_STATUS_SUCCESSFULLY_STOPPED          (1 << 6)
#define FPCIEC_DMA_STATUS_INCORRECTLY_ENDED             (1 << 7)

/* Bit [15:8] - SRC_ERROR */
#define FPCIEC_DMA_SRC_ERROR_OFFSET 8
#define FPCIEC_DMA_SRC_ERROR_MASK 0xFF00

/* SRC_ERROR bit definitions */
#define FPCIEC_DMA_SRC_ERROR_DATA_READ_TIMEOUT          (1 << 8)
#define FPCIEC_DMA_SRC_ERROR_DATA_READ_CA_DECERR        (1 << 9)
#define FPCIEC_DMA_SRC_ERROR_DATA_READ_UR_EP_SLVERR     (1 << 10)
#define FPCIEC_DMA_SRC_ERROR_DATA_READ_ECRC_AXIERR      (1 << 11)
#define FPCIEC_DMA_SRC_ERROR_RESERVED                   (0xF << 12)

/* Bit [23:16] - DEST_ERROR */
#define FPCIEC_DMA_DEST_ERROR_OFFSET 16
#define FPCIEC_DMA_DEST_ERROR_MASK 0xFF0000

/* DEST_ERROR bit definitions (same as SRC_ERROR) */
#define FPCIEC_DMA_DEST_ERROR_DATA_READ_TIMEOUT      (1 << 16)
#define FPCIEC_DMA_DEST_ERROR_DATA_READ_CA_DECERR    (1 << 17)
#define FPCIEC_DMA_DEST_ERROR_DATA_READ_UR_EP_SLVERR (1 << 18)
#define FPCIEC_DMA_DEST_ERROR_DATA_READ_ECRC_AXIERR  (1 << 19)
#define FPCIEC_DMA_DEST_ERROR_RESERVED              (0xF << 20)

/* Bit [31:24] - DESC_ERROR */
#define FPCIEC_DMA_DESC_ERROR_OFFSET 24
#define FPCIEC_DMA_DESC_ERROR_MASK 0xFF000000

/* DESC_ERROR bit definitions */
#define FPCIEC_DMA_DESC_ERROR_SRC_DESCRIPTOR         (1 << 24)
#define FPCIEC_DMA_DESC_ERROR_DEST_DESCRIPTOR        (1 << 25)
#define FPCIEC_DMA_DESC_ERROR_DESC_READ_TIMEOUT      (1 << 26)
#define FPCIEC_DMA_DESC_ERROR_DESC_READ_CA_DECERR    (1 << 27)
#define FPCIEC_DMA_DESC_ERROR_DESC_READ_UR_EP_SLVERR (1 << 28)
#define FPCIEC_DMA_DESC_ERROR_DESC_READ_ECRC_AXIERR  (1 << 29)
#define FPCIEC_DMA_DESC_ERROR_RESERVED              (0x3 << 30)


/* DMA_SHARE_ACCESS_OFFSET */

/* Bit [0] - DMA Access Locked */
#define FPCIEC_DMA_ACCESS_LOCKED_OFFSET 0
#define FPCIEC_DMA_ACCESS_LOCKED_MASK (1 << FPCIEC_DMA_ACCESS_LOCKED_OFFSET)

/* Bit [1] - DMA Access Granted */
#define FPCIEC_DMA_ACCESS_GRANTED_OFFSET 1
#define FPCIEC_DMA_ACCESS_GRANTED_MASK (1 << FPCIEC_DMA_ACCESS_GRANTED_OFFSET)

/* Bits [12:4] - Virtual function number (1 - 511) */
#define FPCIEC_DMA_VIRTUAL_FUNCTION_OFFSET 4
#define FPCIEC_DMA_VIRTUAL_FUNCTION_MASK (0x1FF << FPCIEC_DMA_VIRTUAL_FUNCTION_OFFSET)

/* Bits [18:13] - Physical function number (0 - 63) */
#define FPCIEC_DMA_PHYSICAL_FUNCTION_OFFSET 13
#define FPCIEC_DMA_PHYSICAL_FUNCTION_MASK (0x3F << FPCIEC_DMA_PHYSICAL_FUNCTION_OFFSET)


/* FPCIEC_DMA_PASID_OFFSET */

/* Bit[0] - PASID enabled */
#define FPCIEC_DMA_PASID_ENABLED_OFFSET 0
#define FPCIEC_DMA_PASID_ENABLED_MASK (1 << FPCIEC_DMA_PASID_ENABLED_OFFSET)

/* Bit[1] - Execute Requested */
#define FPCIEC_DMA_EXECUTE_REQUESTED_OFFSET 1
#define FPCIEC_DMA_EXECUTE_REQUESTED_MASK (1 << FPCIEC_DMA_EXECUTE_REQUESTED_OFFSET)

/* Bit[2] - Privileged Mode Requested */
#define FPCIEC_DMA_PRIVILEGED_MODE_REQUESTED_OFFSET 2
#define FPCIEC_DMA_PRIVILEGED_MODE_REQUESTED_MASK (1 << FPCIEC_DMA_PRIVILEGED_MODE_REQUESTED_OFFSET)

/* Bit[22:3] - Process Address Space ID (PASID) */
#define FPCIEC_DMA_PASID_VALUE_OFFSET 3
#define FPCIEC_DMA_PASID_MASK (0x3FFFFF << FPCIEC_DMA_PASID_VALUE_OFFSET)

struct FPcieDmaChanDesc
{
    u32 desc_status;
    u32 desc_control;
    u32 desc_next_addr_l;
    u32 desc_next_addr_h;
    u32 desc_src_addr_l;
    u32 desc_src_addr_h;
    u32 desc_dst_addr_l;
    u32 desc_dst_addr_h;
} __attribute__((__packed__));


#ifdef __cplusplus
}
#endif

#endif
