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
 * FilePath: fqspi_hw.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 09:00:23
 * Description:  This files is for the qspi register related definition
 *
 * Modify History:
 *  Ver   Who        Date        Changes
 * ----- ------      --------    --------------------------------------
 * 1.0   wangxiaodong  2022/3/29  first release
 * 1.1   wangxiaodong  2022/9/9   improve functions
 * 1.2   zhangyan      2022/12/7  improve functions
 */

#ifndef BSP_DRIVERS_FQSPI_HW_H
#define BSP_DRIVERS_FQSPI_HW_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "fio.h"
#include "fkernel.h"

/* register definition */
#define FQSPI_REG_CAP_OFFSET            (0x00) /* Flash capacity setting register */
#define FQSPI_REG_RD_CFG_OFFSET         (0x04) /* Address access reads configuration registers */
#define FQSPI_REG_WR_CFG_OFFSET         (0x08) /* Write buffer flush register */
#define FQSPI_REG_FLUSH_OFFSET          (0x0C) /* Write buffer flush register */
#define FQSPI_REG_CMD_PORT_OFFSET       (0x10) /* Command port register */
#define FQSPI_REG_ADDR_PORT_OFFSET      (0x14) /* Address port register */
#define FQSPI_REG_HD_PORT_OFFSET        (0x18) /* Upper bit port register */
#define FQSPI_REG_LD_PORT_OFFSET        (0x1C) /* low bit port register */
#define FQSPI_REG_CS_TIMING_SET_OFFSET  (0x20) /* CS setting register  */
#define FQSPI_REG_WIP_RD_OFFSET         (0x24) /* WIP reads the Settings register */
#define FQSPI_REG_WP_OFFSET             (0x28) /* WP register */
#define FQSPI_REG_MODE_OFFSET           (0x2C) /* Mode setting register */

/* FQSPI_CAP */
#define FQSPI_CAP_FLASH_NUM(data)   ((data) << 3) /* Flash number */
#define FQSPI_CAP_FLASH_CAP(data)   ((data) << 0) /* The flash capacity */

#define FQSPI_CAP_FLASH_NUM_MASK   GENMASK(4, 3)
#define FQSPI_CAP_FLASH_CAP_MASK   GENMASK(2, 0)

/* RD_CFG */
#define FQSPI_RD_CFG_CMD(data)          ((data) << 24)  /* Read Command */
#define FQSPI_RD_CFG_THROUGH(data)      ((data) << 23)  /* The programming flag in the status register */
#define FQSPI_RD_CFG_TRANSFER(data)     ((data) << 20)  /* rd_tranfer region */
#define FQSPI_RD_CFG_ADDR_SEL(data)     ((data) << 19)  /* rd_addr_sel region*/
#define FQSPI_RD_CFG_LATENCY(data)      ((data) << 18)  /* rd_latency region*/
#define FQSPI_RD_CFG_MODE_BYTE(data)    ((data) << 17)  /* mode byte region*/
#define FQSPI_RD_CFG_CMD_SIGN(data)     ((data) << 9)   /* cmd_sign region*/
#define FQSPI_RD_CFG_DUMMY(data)        ((data-1) << 4) /* dummy region*/
#define FQSPI_RD_CFG_D_BUFFER(data)     ((data) << 3)   /* d_buffer region*/
#define FQSPI_RD_CFG_SCK_SEL(data)      ((data) << 0)   /* rd_sck_sel region*/

#define FQSPI_RD_CFG_CMD_MASK        GENMASK(31, 24)
#define FQSPI_RD_CFG_SCK_SEL_MASK    GENMASK(2, 0)
#define FQSPI_RD_CFG_TRANSFER_MASK   GENMASK(22, 20)
#define FQSPI_RD_CFG_ADDR_SEL_MASK   FQSPI_RD_CFG_ADDR_SEL(0x1)
#define FQSPI_RD_CFG_DUMMY_MASK      GENMASK(8, 4)

/* FQSPI_WR_CFG */
#define FQSPI_WR_CFG_CMD(data)      ((data) << 24)
#define FQSPI_WR_CFG_WAIT(data)     ((data) << 9)
#define FQSPI_WR_CFG_THROUGH(data)  ((data) << 8)
#define FQSPI_WR_CFG_TRANSFER(data) ((data) << 5)
#define FQSPI_WR_CFG_ADDRSEL(data)  ((data) << 4)
#define FQSPI_WR_CFG_MODE(data)     ((data) << 3)
#define FQSPI_WR_CFG_SCK_SEL(data)  ((data) << 0)

#define FQSPI_WR_CFG_CMD_MASK        GENMASK(31, 24)
#define FQSPI_WR_CFG_SCK_SEL_MASK    GENMASK(2, 0)
#define FQSPI_WR_CFG_ADDRSEL_MASK    FQSPI_WR_CFG_ADDRSEL(0x1)

/* FQSPI_CMD_PORT */
#define FQSPI_CMD_PORT_CMD(data)        ((data) << 24)
#define FQSPI_CMD_PORT_WAIT(data)       ((data) << 22)
#define FQSPI_CMD_PORT_THROUGH(data)    ((data) << 21)
#define FQSPI_CMD_PORT_CS(data)         ((data) << 19)
#define FQSPI_CMD_PORT_TRANSFER(data)   ((data) << 16)
#define FQSPI_CMD_PORT_CMD_ADDR(data)   ((data) << 15)
#define FQSPI_CMD_PORT_LATENCY(data)    ((data) << 14)
#define FQSPI_CMD_PORT_DATA_TRANS(data) ((data) << 13)
#define FQSPI_CMD_PORT_ADDR_SEL(data)   ((data) << 12)
#define FQSPI_CMD_PORT_DUMMY(data)      ((data-1) << 7)
#define FQSPI_CMD_PORT_P_BUFFER(data)   ((data) << 6)
#define FQSPI_CMD_PORT_RW_NUM(data)     ((data) << 3)
#define FQSPI_CMD_PORT_CLK_SEL(data)    ((data) << 0)

#define FQSPI_CMD_PORT_RW_NUM_MASK   GENMASK(5, 3)
#define FQSPI_CMD_PORT_CLK_SEL_MASK  GENMASK(2, 0)
#define FQSPI_CMD_PORT_CS_MASK       GENMASK(20, 19)
#define FQSPI_CMD_PORT_CMD_MASK      GENMASK(31, 24)
#define FQSPI_CMD_PORT_ADDR_SEL_MASK FQSPI_CMD_PORT_ADDR_SEL(0x1)

#define FQSPI_CMD_PORT_CMD_RW_MAX    8

/* FQSPI_CS_TIMING_SET */
#define FQSPI_FUN_SET_CS_HOLD(data)     ((data) << 24)
#define FQSPI_FUN_SET_CS_SETUP(data)    ((data) << 16)
#define FQSPI_FUN_SET_CS_DELAY(data)    ((data) << 0)

/* FQSPI_WIP_RD */
#define FQSPI_WIP_RD_CMD(data)      ((data) << 24)
#define FQSPI_WIP_RD_TRANSFER(data) ((data) << 3)
#define FQSPI_WIP_RD_SCK_SEL(data)  ((data) << 0)

/* FQSPI_WP */
#define FQSPI_WP_EN(data)       ((data) << 17)
#define FQSPI_WP_WP(data)       ((data) << 16)
#define FQSPI_WP_HOLD(data)     ((data) << 8)
#define FQSPI_WP_SETUP(data)    ((data) << 0)

/* FQSPI_MODE */
#define FQSPI_MODE_VALID(data)  ((data) << 8)
#define FQSPI_MODE_MODE(data)   ((data) << 0)

#define FQSPI_QUAD_READ_MODE_ENABLE     0xF0A0 /* enable FLASH XIP MODE */
#define FQSPI_QUAD_READ_MODE_DISABLE    0xF0BF /* disable FLASH XIP MODE */
#define FQSPI_QUAD_READ_MODE_CMD        0xA0  /* FLASH XIP MODE CMD SIGN */

typedef enum
{
    FQSPI_CMD_READ = 0x01,
    FQSPI_CMD_WRITE = 0x02,
} FQspiCmdFlags;

/**
 * @name: FQSPI_READ_REG32
 * @msg:  read FQSPI register
 * @param {u32} addr, base address of FQSPI
 * @param {u32} reg_offset, offset of register
 * @return {u32} register value
 */
#define FQSPI_READ_REG32(addr, reg_offset) FtIn32((addr) + (u32)(reg_offset))

/**
 * @name: FQSPI_WRITE_REG32
 * @msg:  write FQSPI register
 * @param {u32} addr, base address of FQSPI
 * @param {u32} reg_offset, offset of register
 * @param {u32} reg_value, set register value
 * @return {void}
 */
#define FQSPI_WRITE_REG32(addr, reg_offset, reg_value) FtOut32(addr + (u32)reg_offset, (u32)reg_value)

/* FQSPI Data Operations */
#define FQSPI_DAT_WRITE(addr, dat)              FtOut32((addr), (u32)(dat))


/* read ld port data */
void FQspiGetLdPortData(uintptr base_addr, u8 *buf, size_t len);

/* set ld port data */
void FQspiSetLdPortData(uintptr base_addr, const u8 *buf, size_t len);

/* send command port register config */
void FQspiCommandPortSend(uintptr base_addr);

/* address port register config */
void FQspiAddrPortConfig(uintptr base_addr, u32 addr);

/* write flush register */
void FQspiWriteFlush(uintptr base_addr);

/* qspi xip mode set */
void FQspiXIPModeSet(uintptr base_addr, u8 enable);



#ifdef __cplusplus
}
#endif

#endif