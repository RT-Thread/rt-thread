/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-07 13:26:58
 * @Description:  This files is for i2c register definition
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef FT_BSP_I2C_HW_H
#define FT_BSP_I2C_HW_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ft_types.h"
#include "ft_io.h"

/* i2c 1~4 reg base address */
#define I2C0_BASE_ADDRESS 0x28006000U
#define I2C1_BASE_ADDRESS 0x28007000U
#define I2C2_BASE_ADDRESS 0x28008000U
#define I2C3_BASE_ADDRESS 0x28009000U

/* defines */
#define I2C_TIMEOUT 5000

#define I2C_MAX_READ_SIZE 1
#define SEM_TIMEOUT 2

    /* Register Definition */

#define I2C_CON 0x00
#define I2C_TAR 0x04
#define I2C_SAR 0x08
#define I2C_HS_MADDR 0x0C
#define I2C_DATA_CMD 0x10
#define I2C_SS_SCL_HCNT 0x14
#define I2C_SS_SCL_LCNT 0x18
#define I2C_FS_SCL_HCNT 0x1C
#define I2C_FS_SCL_LCNT 0x20
#define I2C_HS_SCL_HCNT 0x24
#define I2C_HS_SCL_LCNT 0x28
#define I2C_INTR_STAT 0x2C
#define I2C_INTR_MASK 0x30
#define I2C_RAW_INTR_STAT 0x34
#define I2C_RX_TL 0x38
#define I2C_TX_TL 0x3C
#define I2C_CLR_INTR 0x40
#define I2C_CLR_RX_UNDER 0x44
#define I2C_CLR_RX_OVER 0x48
#define I2C_CLR_TX_OVER 0x4C
#define I2C_CLR_RD_REQ 0x50
#define I2C_CLR_TX_ABRT 0x54
#define I2C_CLR_RX_DONE 0x58
#define I2C_CLR_ACTIVITY 0x5c
#define I2C_CLR_STOP_DET 0x60
#define I2C_CLR_START_DET 0x64
#define I2C_CLR_GEN_CALL 0x68
#define I2C_ENABLE 0x6C
#define I2C_STATUS 0x70
#define I2C_TXFLR 0x74
#define I2C_RXFLR 0x78
#define I2C_TX_ABRT_SOURCE 0x80
#define I2C_SLV_DATA_NACK_ONLY 0x84
#define I2C_DMA_CR 0x88
#define I2C_DMA_TDLR 0x8c
#define I2C_DMA_RDLR 0x90
#define I2C_SDA_SETUP 0x94
#define I2C_ACK_GENERAL_CALL 0x98
#define I2C_ENABLE_STATUS 0x9C
#define I2C_COMP_PARAM_1 0xf4
#define I2C_COMP_VERSION 0xf8
#define I2C_COMP_TYPE 0xfc

#define I2C_RAW_INTR_STAT_RX_UNDER 0x1
#define I2C_RAW_INTR_STAT_RX_OVER 0x2
#define I2C_RAW_INTR_STAT_RX_FULL 0x4
#define I2C_RAW_INTR_STAT_TX_OVER 0x8
#define I2C_RAW_INTR_STAT_TX_EMPTY 0x10

    /* Default parameters */

#define I2C_CON_ME (0x1 << 0)
#define I2C_CON_MS_SS (0x1 << 1)
#define I2C_CON_MS_FS (0x2 << 1)
#define I2C_CON_MS_HS (0x3 << 1)
#define I2C_CON_SLAVE_ADR_7BIT (0x0 << 3)
#define I2C_CON_SLAVE_ADR_10BIT (0x1 << 3)
#define I2C_CON_MASTER_ADR_7BIT (0x0 << 4)
#define I2C_CON_MASTER_ADR_10BIT (0x1 << 4)
#define I2C_CON_RESTART_EN (0x1 << 5)
#define I2C_CON_SLAVE_DISABLE (0x1 << 6)

/* 0110 0011 0x63 */
#define I2C_CON_DEFAULT_MASTER (I2C_CON_ME | I2C_CON_MS_FS /*I2C_CON_MS_SS*/ /* | I2C_CON_RESTART_EN*/ | \
                                I2C_CON_SLAVE_ADR_7BIT | I2C_CON_SLAVE_DISABLE)
#define I2C_CTR_DEFAULT (I2C_CON_ME | I2C_CON_MASTER_ADR_7BIT | \
                         I2C_CON_SLAVE_DISABLE)

#define I2C_IRQ_NONE_MASK 0x0
#define I2C_IRQ_ALL_MASK 0x8ff

#define I2C_TAR_STARTBYTE (0x1 << 10)
#define I2C_TAR_SPECIAL_STARTBYTE (0x1 << 11)
#define I2C_TAR_ADR_7BIT (0x0 << 12)
#define I2C_TAR_ADR_10BIT (0x1 << 12)
#define I2C_TAR_ADR_MASK 0x3ff /* bit [9: 0] */

#define I2C_SLAVE_DISABLE_DEFAULT 0
#define I2C_RESTART_EN_DEFAULT 1
#define I2C_10BITADDR_MASTER_DEFAULT 0
#define I2C_10BITADDR_SLAVE_DEFAULT 1
#define I2C_MAX_SPEED_MODE_DEFAULT 3
#define I2C_MASTER_MODE_DEFAULT 1

#define I2C_STANDARD_SPEED_MASK (0x01 << 1)
#define I2C_FAST_SPEED_MASK (0x02 << 1)
#define I2C_HIGH_SPEED_MASK (0x03 << 1)

#define I2C_DEFAULT_TAR_ADDR_DEFAULT 0x055
#define I2C_DEFAULT_SLAVE_ADDR_DEFAULT 0x055
#define I2C_COMP_VERSION_DEFAULT 0x3131352A

#define I2C_HS_MASTER_CODE_DEFAULT 1
#define I2C_SS_SCL_HIGH_COUNT_DEFAULT 0x0190
#define I2C_SS_SCL_LOW_COUNT_DEFAULT 0x01d6
#define I2C_FS_SCL_HIGH_COUNT_DEFAULT 0x003c
#define I2C_FS_SCL_LOW_COUNT_DEFAULT 0x0082
#define I2C_HS_SCL_HIGH_COUNT_DEFAULT 0x006
#define I2C_HS_SCL_LOW_COUNT_DEFAULT 0x0010
#define I2C_RX_TL_DEFAULT 0
#define I2C_TX_TL_DEFAULT 0
#define I2C_DEFAULT_SDA_SETUP_DEFAULT 0x64
#define I2C_DEFAULT_ACK_GENERAL_CALL_DEFAULT 1
#define I2C_DYNAMI2C_TAR_UPDATE_DEFAULT 1
#define I2C_RX_BUFFER_DEPTH_DEFAULT 8
#define I2C_TX_BUFFER_DEPTH_DEFAULT 8
#define I2C_ADD_ENCODED_PARAMS_DEFAULT 1
#define I2C_HAS_DMA_DEFAULT 0
#define I2C_INTR_IO_DEFAULT 0
#define I2C_HC_COUNT_VALUES_DEFAULT 0
#define APB_DATA_WIDTH_DEFAULT 0
#define I2C_SLV_DATA_NACK_ONLY_DEFAULT 0
#define I2C_USE_COUNTS_DEFAULT 0
#define I2C_CLK_TYPE_DEFAULT 1
#define I2C_CLOCK_PERIOD_DEFAULT 10

    /* Raw Interrupt Status */

#define I2C_IRQ_NONE (0x0)
#define I2C_IRQ_RX_UNDER (0x01 << 0)
#define I2C_IRQ_RX_OVER (0x01 << 1)
#define I2C_IRQ_RX_FULL (0x01 << 2)
#define I2C_IRQ_TX_OVER (0x01 << 3)
#define I2C_IRQ_TX_EMPTY (0x01 << 4)
#define I2C_IRQ_RD_REQ (0x01 << 5)
#define I2C_IRQ_TX_ABRT (0x01 << 6)
#define I2C_IRQ_RX_DONE (0x01 << 7)
#define I2C_IRQ_ACTIVITY (0x01 << 8)
#define I2C_IRQ_STOP_DET (0x01 << 9)
#define I2C_IRQ_START_DET (0x01 << 10)
#define I2C_IRQ_GEN_CALL (0x01 << 11)
#define I2C_IRQ_ALL 0xFFF

    /* Default IRQ Mask Bit Setting */

#define I2C_IRQ_DEFAULT_MASK (I2C_IRQ_RX_FULL | I2C_IRQ_TX_EMPTY | \
                              I2C_IRQ_TX_ABRT | I2C_IRQ_STOP_DET | \
                              I2C_IRQ_START_DET)

    /* Data command stop bit */

#define I2C_DATA_CMD_WR_STOP_BIT (0x02 << 8) /* bit 8=0:W, bit 9=1: stop */
#define I2C_DATA_CMD_RD_STOP_BIT (0x03 << 8) /* bit 8=1:R, bit 9=1: stop */
#define I2C_DATA_CMD_DAT_MASK 0xff           /* bit [7:0] , TX and RX data */
#define I2C_DATA_CMD_WR (0x00 << 8)
#define I2C_DATA_CMD_RD (0x01 << 8)
#define I2C_DATA_CMD_STOP (0x01 << 9)
#define I2C_DATA_CMD_RESTART (0X01 << 10)

    /* I2C TX Abort Source*/

#define I2C_ABRT_7B_ADDR_NOACK 0x001
#define I2C_ABRT_10_ADDR1_NOACK 0x002
#define I2C_ABRT_10_ADDR2_NOACK 0x004
#define I2C_ABRT_TXDATA_NOACK 0x008
#define I2C_ABRT_GCALL_NOACK 0x010
#define I2C_ABRT_GCALL_READ 0x020
#define I2C_ABRT_HS_ACKDET 0x040
#define I2C_ABRT_SBYTE_ACKDET 0x080
#define I2C_ABRT_HS_NORSTRT 0x100
#define I2C_ABRT_SBYTE_NORSTRT 0x200
#define I2C_ABRT_10B_RD_NORSTRT 0x400
#define I2C_ABRT_MASTER_DIS 0x800
#define I2C_ABRT_ARB_LOST 0x1000
#define I2C_ABRT_SLVFLUSH_TXFIFO 0x2000
#define I2C_ABRT_SLV_ARBLOST 0x5000
#define I2C_ABRT_SLVRD_INTX 0x8000

    /* Minimum High and Low period in nanosecends */

#define SS_MIN_SCL_HIGH 4000
#define SS_MIN_SCL_LOW 4700
#define FS_MIN_SCL_HIGH 600
#define FS_MIN_SCL_LOW 1300
#define HS_MIN_SCL_HIGH_100PF 60
#define HS_MIN_SCL_LOW_100PF 120

    /* I2C_STATUS (RO) */

#define I2C_STATUS_ACTIVITY (0x1 << 0)     /* I2C ctrl is enabled */
#define I2C_STATUS_TFNF (0x1 << 1)         /* TX FIFO is not full */
#define I2C_STATUS_TFE (0x1 << 2)          /* TX FIFO is empty */
#define I2C_STATUS_RFNE (0x1 << 3)         /* RX FIFO is not empty */
#define I2C_STATUS_RFF (0x1 << 4)          /* RX FIFO is full */
#define I2C_STATUS_MST_ACTIVITY (0x1 << 5) /* Master is not idle */
#define I2C_STATUS_SLV_ACTIVITY (0x1 << 6) /* Slave is not idle */

    /* Interrupts status */

#define I2C_INTR_RX_UNDER (0x1 << 0)
#define I2C_INTR_RX_OVER (0x1 << 1)
#define I2C_INTR_RX_FULL (0x1 << 2)
#define I2C_INTR_TX_OVER (0x1 << 3)
#define I2C_INTR_TX_EMPTY (0x1 << 4)
#define I2C_INTR_RD_REQ (0x1 << 5)
#define I2C_INTR_TX_ABRT (0x1 << 6)
#define I2C_INTR_RX_DONE (0x1 << 7)
#define I2C_INTR_ACTIVITY (0x1 << 8)
#define I2C_INTR_STOP_DET (0x1 << 9)
#define I2C_INTR_START_DET (0x1 << 10)
#define I2C_INTR_GEN_CALL (0x1 << 11)

#define I2C_TX_BUFFER_DEPTH_MASK 0xFF0000 /* bit [23: 16] */
#define I2C_RX_BUFFER_DEPTH_MASK 0x00FF00 /* bit [15: 8] */

#define I2C_INTR_MAX_BITS 12

#define I2C_ENABLE_CONTROLLER 0x01
#define I2C_DISABLE_CONTROLLER 0x00

#define I2C_DATA_CMD_READ (0x01 << 8)
#define I2C_DATA_CMD_WRITE (0x00 << 8)

#define I2C_TAR_DEFAULT_ADDR 0x55
#define FT2000_I2C_CLK (48000000) /* I2C clock       */
/**
 * @name: FI2c_WriteReg
 * @msg:  write i2c register
 * @param {u32} BaseAddress base addr of i2c
 * @param {u32} RegOffset   addr offset of i2c register
 * @param {u32} RegisterValue val to be write into register
 * @return {void}
 */
#define FI2C_WriteReg(BaseAddress, RegOffset, RegisterValue) Ft_out32(BaseAddress + (u32)RegOffset, (u32)RegisterValue)

/**
 * @name: FI2c_ReadReg
 * @msg:  read i2c register
 * @param {u32} BaseAddress base addr of i2c
 * @param {u32} RegOffset   addr offset of i2c register
 * @return {u32} val read from register
 */
#define FI2C_ReadReg(BaseAddress, RegOffset) Ft_in32(BaseAddress + (u32)RegOffset)

    /*
* the following macros convert from BCD to binary and back.
* Be careful that the arguments are chars, only char width returned.
*/

#define BCD_TO_BIN(bcd) ((((((bcd)&0xf0) >> 4) * 10) + ((bcd)&0xf)) & 0xff)
#define BIN_TO_BCD(bin) (((((bin) / 10) << 4) + ((bin) % 10)) & 0xff)

#define FI2C_GET_BASE_ADDR(pDev) ((pDev)->Config.BaseAddress)
#define FI2C_ENABLE_I2C_BUS(pDev) (FI2C_WriteReg(FI2C_GET_BASE_ADDR(pDev), I2C_ENABLE, I2C_ENABLE_CONTROLLER))
#define FI2C_DISABLE_I2C_BUS(pDev) (FI2C_WriteReg(FI2C_GET_BASE_ADDR(pDev), I2C_ENABLE, I2C_DISABLE_CONTROLLER))
#define FI2C_IS_I2C_BUS_ENABLED(pDev) (FI2C_ReadReg(FI2C_GET_BASE_ADDR(pDev), I2C_ENABLE))

#define FI2C_GET_STATUS(pDev) (FI2C_ReadReg(FI2C_GET_BASE_ADDR(pDev), I2C_STATUS))
#define FI2C_CHECK_STATUS(pDev, stMask) (FI2C_GET_STATUS(pDev) & (stMask))
#define FI2C_CLR_ALL_IRQ_STATUS(pDev) (FI2C_ReadReg(FI2C_GET_BASE_ADDR(pDev), I2C_CLR_INTR))
#define FI2C_GET_IRQ_STATUS(pDev) (FI2C_ReadReg(FI2C_GET_BASE_ADDR(pDev), I2C_INTR_STAT))
#define FI2C_GET_IRQ_MASK(pDev) (FI2C_ReadReg(FI2C_GET_BASE_ADDR(pDev), I2C_INTR_MASK))
#define FI2C_SET_IRQ_MASK(pDev, mask) (FI2C_WriteReg(FI2C_GET_BASE_ADDR(pDev), I2C_INTR_MASK, (mask)))

#define FI2C_GET_TX_TL(pDev) (FI2C_ReadReg(FI2C_GET_BASE_ADDR(pDev), I2C_TX_TL))
#define FI2C_GET_RX_TL(pDev) (FI2C_ReadReg(FI2C_GET_BASE_ADDR(pDev), I2C_RX_TL))
#define FI2C_SET_TX_TL(pDev, TxThres) (FI2C_WriteReg(FI2C_GET_BASE_ADDR(pDev), I2C_TX_TL, (TxThres)))
#define FI2C_SET_RX_TL(pDev, RxThres) (FI2C_WriteReg(FI2C_GET_BASE_ADDR(pDev), I2C_RX_TL, (RxThres)))

#define FI2C_GET_TXFLR(pDev) (FI2C_ReadReg(FI2C_GET_BASE_ADDR(pDev), I2C_TXFLR))
#define FI2C_GET_RXFLR(pDev) (FI2C_ReadReg(FI2C_GET_BASE_ADDR(pDev), I2C_RXFLR))

#define FI2C_CLR_IRQ_RX_OVER(pDev) (FI2C_ReadReg(FI2C_GET_BASE_ADDR(pDev), I2C_CLR_RX_OVER))
#define FI2C_CLR_IRQ_TX_OVER(pDev) (FI2C_ReadReg(FI2C_GET_BASE_ADDR(pDev), I2C_CLR_TX_OVER))

#define FI2C_GET_COMP_PARAM_1(pDev) (FI2C_ReadReg(FI2C_GET_BASE_ADDR(pDev), I2C_COMP_PARAM_1))
#define FI2C_GET_TX_BUFFER_DEPTH(pDev) ((I2C_TX_BUFFER_DEPTH_MASK & FI2C_GET_COMP_PARAM_1(pDev)) >> 16)
#define FI2C_GET_RX_BUFFER_DEPTH(pDev) ((I2C_RX_BUFFER_DEPTH_MASK & FI2C_GET_COMP_PARAM_1(pDev)) >> 8)

#define FI2C_SEND_TX_STOP_CMD(pDev) (FI2C_WriteReg(FI2C_GET_BASE_ADDR(pDev), I2C_DATA_CMD, I2C_DATA_CMD_STOP))
#define FI2C_SET_TX_DATA(pDev, data) (FI2C_WriteReg(FI2C_GET_BASE_ADDR(pDev), I2C_DATA_CMD, ((u32)(data)&I2C_DATA_CMD_DAT_MASK)))
#define FI2C_GET_RX_DATA(pDev) (u8)(I2C_DATA_CMD_DAT_MASK & (FI2C_ReadReg(FI2C_GET_BASE_ADDR(pDev), I2C_DATA_CMD)))
#define FI2C_SEND_RX_NEXT_CMD(pDev) (FI2C_WriteReg(FI2C_GET_BASE_ADDR(pDev), I2C_DATA_CMD, I2C_DATA_CMD_STOP | I2C_DATA_CMD_RESTART | I2C_DATA_CMD_RD))
#define FI2C_SEND_RX_STOP_CMD(pDev) (FI2C_WriteReg(FI2C_GET_BASE_ADDR(pDev), I2C_DATA_CMD, I2C_DATA_CMD_STOP | I2C_DATA_CMD_RD))

    void FI2C_resetReg(u32 BaseAddr);

#ifdef __cplusplus
}
#endif

#endif
