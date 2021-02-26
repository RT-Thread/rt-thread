/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_I2C_H
#define _HARDWARE_STRUCTS_I2C_H

#include "hardware/address_mapped.h"
#include "hardware/regs/i2c.h"

typedef struct {
    io_rw_32 con;
    io_rw_32 tar;
    io_rw_32 sar;
    uint32_t _pad0;
    io_rw_32 data_cmd;
    io_rw_32 ss_scl_hcnt;
    io_rw_32 ss_scl_lcnt;
    io_rw_32 fs_scl_hcnt;
    io_rw_32 fs_scl_lcnt;
    uint32_t _pad1[2];
    io_rw_32 intr_stat;
    io_rw_32 intr_mask;
    io_rw_32 raw_intr_stat;
    io_rw_32 rx_tl;
    io_rw_32 tx_tl;
    io_rw_32 clr_intr;
    io_rw_32 clr_rx_under;
    io_rw_32 clr_rx_over;
    io_rw_32 clr_tx_over;
    io_rw_32 clr_rd_req;
    io_rw_32 clr_tx_abrt;
    io_rw_32 clr_rx_done;
    io_rw_32 clr_activity;
    io_rw_32 clr_stop_det;
    io_rw_32 clr_start_det;
    io_rw_32 clr_gen_call;
    io_rw_32 enable;
    io_rw_32 status;
    io_rw_32 txflr;
    io_rw_32 rxflr;
    io_rw_32 sda_hold;
    io_rw_32 tx_abrt_source;
    io_rw_32 slv_data_nack_only;
    io_rw_32 dma_cr;
    io_rw_32 dma_tdlr;
    io_rw_32 dma_rdlr;
    io_rw_32 sda_setup;
    io_rw_32 ack_general_call;
    io_rw_32 enable_status;
    io_rw_32 fs_spklen;
    uint32_t _pad2;
    io_rw_32 clr_restart_det;
} i2c_hw_t;

#define i2c0_hw ((i2c_hw_t *const)I2C0_BASE)
#define i2c1_hw ((i2c_hw_t *const)I2C1_BASE)

// List of configuration constants for the Synopsys I2C hardware (you may see
// references to these in I2C register header; these are *fixed* values,
// set at hardware design time):

// SLAVE_INTERFACE_TYPE .............. 0
// REG_TIMEOUT_WIDTH ................. 4
// REG_TIMEOUT_VALUE ................. 8
// IC_ULTRA_FAST_MODE ................ 0x0
// IC_UFM_TBUF_CNT_DEFAULT ........... 0x8
// IC_UFM_SCL_HIGH_COUNT ............. 0x0006
// IC_TX_TL .......................... 0x0
// IC_STOP_DET_IF_MASTER_ACTIVE ...... 0x0
// IC_SS_SCL_LOW_COUNT ............... 0x01d6
// IC_HAS_DMA ........................ 0x1
// IC_RX_FULL_GEN_NACK ............... 0x0
// IC_CLOCK_PERIOD ................... 100
// IC_EMPTYFIFO_HOLD_MASTER_EN ....... 1
// IC_SMBUS_ARP ...................... 0x0
// IC_FIRST_DATA_BYTE_STATUS ......... 0x1
// IC_INTR_IO ........................ 0x1
// IC_MASTER_MODE .................... 0x1
// IC_DEFAULT_ACK_GENERAL_CALL ....... 0x0
// IC_INTR_POL ....................... 0x1
// IC_OPTIONAL_SAR ................... 0x0
// IC_DEFAULT_TAR_SLAVE_ADDR ......... 0x055
// IC_DEFAULT_SLAVE_ADDR ............. 0x055
// IC_DEFAULT_HS_SPKLEN .............. 0x1
// IC_FS_SCL_HIGH_COUNT .............. 0x003c
// IC_HS_SCL_LOW_COUNT ............... 0x0010
// IC_DEVICE_ID_VALUE ................ 0x0
// IC_10BITADDR_MASTER ............... 0x0
// IC_CLK_FREQ_OPTIMIZATION .......... 0x0
// IC_DEFAULT_FS_SPKLEN .............. 0xf
// IC_ADD_ENCODED_PARAMS ............. 0x1
// IC_DEFAULT_SDA_HOLD ............... 0x000001
// IC_DEFAULT_SDA_SETUP .............. 0x64
// IC_AVOID_RX_FIFO_FLUSH_ON_TX_ABRT . 0x0
// SLVERR_RESP_EN .................... 0
// IC_RESTART_EN ..................... 0x1
// IC_TX_CMD_BLOCK ................... 0x1
// HC_REG_TIMEOUT_VALUE .............. 0
// IC_BUS_CLEAR_FEATURE .............. 0x1
// IC_CAP_LOADING .................... 100
// IC_HAS_ASYNC_FIFO ................. 0x0
// IC_FS_SCL_LOW_COUNT ............... 0x0082
// APB_DATA_WIDTH .................... 32
// IC_SDA_STUCK_TIMEOUT_DEFAULT ...... 0xffffffff
// IC_SLV_DATA_NACK_ONLY ............. 0x1
// IC_10BITADDR_SLAVE ................ 0x0
// IC_TX_BUFFER_DEPTH ................ 32
// IC_DEFAULT_UFM_SPKLEN ............. 0x1
// IC_CLK_TYPE ....................... 0x0
// IC_TX_CMD_BLOCK_DEFAULT ........... 0x0
// IC_SMBUS_UDID_MSB ................. 0x0
// IC_SMBUS_SUSPEND_ALERT ............ 0x0
// IC_HS_SCL_HIGH_COUNT .............. 0x0006
// IC_SLV_RESTART_DET_EN ............. 0x1
// IC_SMBUS .......................... 0x1
// IC_STAT_FOR_CLK_STRETCH ........... 0x1
// IC_MAX_SPEED_MODE ................. 0x2
// IC_OPTIONAL_SAR_DEFAULT ........... 0x0
// IC_PERSISTANT_SLV_ADDR_DEFAULT .... 0x0
// IC_USE_COUNTS ..................... 0x1
// IC_RX_BUFFER_DEPTH ................ 32
// IC_SCL_STUCK_TIMEOUT_DEFAULT ...... 0xffffffff
// IC_RX_FULL_HLD_BUS_EN ............. 0x1
// IC_SLAVE_DISABLE .................. 0x1
// IC_RX_TL .......................... 0x0
// IC_DEVICE_ID ...................... 0x0
// IC_HC_COUNT_VALUES ................ 0x0
// I2C_DYNAMIC_TAR_UPDATE ............ 1
// IC_SMBUS_CLK_LOW_MEXT_DEFAULT ..... 0xffffffff
// IC_SMBUS_CLK_LOW_SEXT_DEFAULT ..... 0xffffffff
// IC_HS_MASTER_CODE ................. 0x1
// IC_SMBUS_RST_IDLE_CNT_DEFAULT ..... 0xffff
// IC_UFM_SCL_LOW_COUNT .............. 0x0008
// IC_SMBUS_UDID_HC .................. 0x1
// IC_SMBUS_UDID_LSB_DEFAULT ......... 0xffffffff
// IC_SS_SCL_HIGH_COUNT .............. 0x0190

#endif
