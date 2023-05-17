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
 * FilePath: fsata_hw.h
 * Date: 2022-02-10 14:55:11
 * LastEditTime: 2022-02-18 09:03:41
 * Description:  This file is for ctrl of sata functions
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/2/10    first release
 * 1.1   wangxiaodong  2022/10/21   improve functions
 */

#ifndef FSATA_HW_H
#define FSATA_HW_H

#include "fkernel.h"
#include "ftypes.h"
#include "fio.h"

#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/
/* SATA register definitions */

/* Global controller registers */
#define FSATA_HOST_CAP          0x00 /* host capabilities */
#define FSATA_HOST_CTL          0x04 /* global host control */
#define FSATA_HOST_IRQ_STAT     0x08 /* interrupt status */
#define FSATA_HOST_PORTS_IMPL   0x0c /* bitmap of implemented ports */
#define FSATA_HOST_VERSION      0x10 /* AHCI spec. version compliancy */
#define FSATA_HOST_CAP2         0x24 /* host capabilities, extended */

/* FSATA_HOST_CTL bits */
#define FSATA_HOST_CAP_NP_MASK  GENMASK(4, 0)  /* Number of Ports (NP) */
#define FSATA_HOST_AHCI_EN      BIT(31) /* AHCI enabled */
#define FSATA_HOST_CAP_SMPS     BIT(28) /* AHCI Supports Mechanical Presence Switch */
#define FSATA_HOST_CAP_SSS      BIT(27) /* AHCI staggered spin-up */
#define FSATA_HOST_CAP_SPM      BIT(17) /* AHCI port multiplier */
#define FSATA_HOST_IRQ_EN       BIT(1)  /* global IRQ enable */
#define FSATA_HOST_RESET        BIT(0)  /* reset controller; self-clear */
#define FSATA_HOST_PORTS_IMPL_MASK(x)   GENMASK(x, 0)  /* Ports Implemented */

/* Registers for each SATA port */
#define FSATA_PORT_LST_ADDR     0x00 /* command list DMA addr */
#define FSATA_PORT_LST_ADDR_HI  0x04 /* command list DMA addr hi */
#define FSATA_PORT_FIS_ADDR     0x08 /* FIS rx buf addr */
#define FSATA_PORT_FIS_ADDR_HI  0x0c /* FIS rx buf addr hi */
#define FSATA_PORT_IRQ_STAT     0x10 /* interrupt status */
#define FSATA_PORT_IRQ_MASK     0x14 /* interrupt enable/disable mask */
#define FSATA_PORT_CMD          0x18 /* port command */
#define FSATA_PORT_TFDATA       0x20 /* taskfile data */
#define FSATA_PORT_SIG          0x24 /* device TF signature */
#define FSATA_PORT_SCR_STAT     0x28 /* SATA phy register: SStatus */
#define FSATA_PORT_SCR_CTL      0x2c /* SATA phy register: SControl */
#define FSATA_PORT_SCR_ERR      0x30 /* SATA phy register: SError */
#define FSATA_PORT_SCR_ACT      0x34 /* SATA phy register: SActive */
#define FSATA_PORT_CMD_ISSUE    0x38 /* command issue */

/* PORT_SCR_STAT bits */
#define FSATA_PORT_SCR_STAT_DET_MASK    GENMASK(3, 0)
#define FSATA_PORT_SCR_STAT_DET_COMINIT 0x1
#define FSATA_PORT_SCR_STAT_DET_PHYRDY  0x3 /* SATA exist and phy connected */

/* PORT_CMD bits */
#define FSATA_PORT_CMD_LIST_ADDR_MASK   GENMASK(31, 10)
#define FSATA_PORT_CMD_FIS_ADDR_MASK    GENMASK(31, 8)
#define FSATA_PORT_CMD_TABLE_ADDR_MASK  GENMASK(31, 7)

#define FSATA_PORT_CMD_ATAPI        BIT(24) /* Device is ATAPI */
#define FSATA_PORT_CMD_LIST_ON      BIT(15) /* cmd list DMA engine running */
#define FSATA_PORT_CMD_FIS_ON       BIT(14) /* FIS DMA engine running */
#define FSATA_PORT_CMD_FIS_RX       BIT(4) /* Enable FIS receive DMA engine */
#define FSATA_PORT_CMD_CLO          BIT(3) /* Command list override */
#define FSATA_PORT_CMD_POWER_ON     BIT(2) /* Power up device */
#define FSATA_PORT_CMD_SPIN_UP      BIT(1) /* Spin up device */
#define FSATA_PORT_CMD_START        BIT(0) /* Enable port DMA engine */

#define FSATA_PORT_CMD_ICC_ACTIVE   BIT(28) /* Put i/f in active state */
#define FSATA_PORT_CMD_ICC_PARTIAL  BIT(29) /* Put i/f in partial state */
#define FSATA_PORT_CMD_ICC_SLUMBER  (0x6 << 28) /* Put i/f in slumber state */

#define FSATA_PORT_TFDATA_ATA_BUSY  BIT(7)  /* BSY status bit */
#define FSATA_PORT_TFDATA_ATA_DRDY  BIT(6)  /* device ready */
#define FSATA_PORT_TFDATA_ATA_DF    BIT(5)  /* device fault */
#define FSATA_PORT_TFDATA_ATA_DRQ   BIT(3)  /* data request i/o */
#define FSATA_PORT_TFDATA_ATA_ERR   BIT(0)  /* have an error */

/* PORT_IRQ_{STAT,MASK} bits */
#define FSATA_PORT_IRQ_COLD_PRES        BIT(31) /* cold presence detect */
#define FSATA_PORT_IRQ_TF_ERR           BIT(30) /* task file error */
#define FSATA_PORT_IRQ_HBUS_ERR         BIT(29) /* host bus fatal error */
#define FSATA_PORT_IRQ_HBUS_DATA_ERR    BIT(28) /* host bus data error */
#define FSATA_PORT_IRQ_IF_ERR           BIT(27) /* interface fatal error */
#define FSATA_PORT_IRQ_IF_NONFATAL      BIT(26) /* interface non-fatal error */
#define FSATA_PORT_IRQ_OVERFLOW         BIT(24) /* xfer exhausted available S/G */
#define FSATA_PORT_IRQ_BAD_PMP          BIT(23) /* incorrect port multiplier */

#define FSATA_PORT_IRQ_PHYRDY       BIT(22) /* PhyRdy changed */
#define FSATA_PORT_IRQ_DEV_ILCK     BIT(7) /* device interlock */
#define FSATA_PORT_IRQ_CONNECT      BIT(6) /* port connect change status */
#define FSATA_PORT_IRQ_SG_DONE      BIT(5) /* descriptor processed */
#define FSATA_PORT_IRQ_UNK_FIS      BIT(4) /* unknown FIS rx'd */
#define FSATA_PORT_IRQ_SDB_FIS      BIT(3) /* Set Device Bits FIS rx'd */
#define FSATA_PORT_IRQ_DMAS_FIS     BIT(2) /* DMA Setup FIS rx'd */
#define FSATA_PORT_IRQ_PIOS_FIS     BIT(1) /* PIO Setup FIS rx'd */
#define FSATA_PORT_IRQ_D2H_REG_FIS  BIT(0) /* D2H Register FIS rx'd */

#define FSATA_PORT_IRQ_FREEZE   FSATA_PORT_IRQ_CONNECT | FSATA_PORT_IRQ_SDB_FIS | \
    FSATA_PORT_IRQ_D2H_REG_FIS | FSATA_PORT_IRQ_PIOS_FIS

#define FSATA_PORT_SCR_ACT_ENABLE    BIT(0) /* Port Serial ATA Active */
#define FSATA_PORT_CMD_ISSUE_ENABLE  BIT(0) /* Port Command Issue enable */

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/**
 * @name: SATA_READ_REG32
 * @msg:  读取SATA寄存器
 * @param {u32} addr 定时器的基地址
 * @param {u32} reg_offset   定时器的寄存器的偏移
 * @return {u32} 寄存器参数
 */
#define FSATA_READ_REG32(addr, reg_offset) FtIn32((addr) + (u32)reg_offset)

/**
 * @name: SATA_WRITE_REG32
 * @msg:  写入SATA寄存器
 * @param {u32} addr 定时器的基地址
 * @param {u32} reg_offset   定时器的寄存器的偏移
 * @param {u32} reg_value    写入寄存器参数
 * @return {void}
 */
#define FSATA_WRITE_REG32(addr, reg_offset, reg_value) FtOut32((addr) + (u32)reg_offset, (u32)reg_value)

#define FSATA_SETBIT(base_addr, reg_offset, data) \
    FtSetBit32((base_addr) + (u32)(reg_offset), (u32)(data))

#define FSATA_CLEARBIT(base_addr, reg_offset, data) \
    FtClearBit32((base_addr) + (u32)(reg_offset), (u32)(data))

#ifdef __cplusplus
}
#endif

#endif