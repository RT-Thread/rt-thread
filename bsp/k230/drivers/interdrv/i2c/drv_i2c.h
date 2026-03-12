/* Copyright (c) 2023, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DRV_I2C_H__
#define __DRV_I2C_H__
#include <stdint.h>

#define BIT(x)              (1<<(x))

/* Speed Selection */
#define I2C_SPEED_MODE_STANDARD      1
#define I2C_SPEED_MODE_FAST          2
#define I2C_SPEED_MODE_MAX           3

#define I2C_MAX_SPEED_UP            3400000
#define I2C_FAST_SPEED_UP           1000000
#define I2C_STANDARD_SPEED_UP       100000
#define I2C_DEFAULT_SPEED           400000
#define I2C_DEFAULT_TIMEOUT         8       /* 8ms */

/* i2c data cmd definition */
#define I2C_DATA_CMD_READ            BIT(8)
#define I2C_DATA_CMD_STOP            BIT(9)
#define I2C_DATA_CMD_RESTART         BIT(10)
#define I2C_DATA_CMD_FIRST_DATA_BYTE BIT(11)

/* i2c fifo size */
#define I2C_TX_FIFO_SIZE    32       /* 32 * 32bit */
#define I2C_RX_FIFO_SIZE    32       /* 64 * 8bit */

/* fifo threshold register definitions */
#define I2C_TL0          0x00
#define I2C_TL1          0x01
#define I2C_TL2          0x02
#define I2C_TL3          0x03
#define I2C_TL4          0x04
#define I2C_TL5          0x05
#define I2C_TL6          0x06
#define I2C_TL7          0x07
#define I2C_RX_TL        I2C_TL0
#define I2C_TX_TL        I2C_TL0

/* i2c control register(offset address 0x00) */
typedef struct _i2c_ic_con
{
    uint32_t master_mode                    : 1;
    uint32_t speed                          : 2;
    uint32_t slave_10bit_addr               : 1;
    uint32_t master_10bit_addr              : 1;
    uint32_t restart_en                     : 1;
    uint32_t slave_disable                  : 1;
    uint32_t stop_det_ifaddressed           : 1;
    uint32_t tx_empty_ctrl                  : 1;
    uint32_t rx_fifo_full_hld_ctrl          : 1;
    uint32_t stop_det_if_master_active      : 1;
    uint32_t bus_clear_feature_ctrl         : 1;
    uint32_t rsvd_1                         : 4;    /* reserved */
    uint32_t optional_sar_ctrl              : 1;
    uint32_t smbus_slave_quick_en           : 1;
    uint32_t smbus_arp_en                   : 1;
    uint32_t smbus_persisent_slv_addr_en    : 1;
    uint32_t rsvd_2                         : 12;   /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_con_t;

/* i2c target address register(offset address 0x04) */
typedef struct _i2c_ic_tar
{
    uint32_t tar               : 10;
    uint32_t gc_or_start       : 1;
    uint32_t special           : 1;
    uint32_t master_10bit_addr : 1;
    uint32_t device_id         : 1;
    uint32_t rsvd_1            : 2;     /* reserved */
    uint32_t smbus_quick_cmd   : 1;
    uint32_t rsvd_2            : 15;    /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_tar_t;

/* i2c slave address register(offset address 0x08) */
typedef struct _i2c_ic_sar
{
    uint32_t sar  : 10;
    uint32_t rsvd : 22; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_sar_t;

/* i2c high speed master mode code address register(offset address 0x0c) */
typedef struct _i2c_ic_hs_maddr
{
    uint32_t mar  : 3;
    uint32_t rsvd : 29; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_hs_maddr_t;

/* i2c rx/tx data buffer and command register(offset address 0x10) */
typedef struct _i2c_ic_data_cmd
{
    uint32_t dat             : 8;
    uint32_t cmd             : 1;
    uint32_t stop            : 1;
    uint32_t restart         : 1;
    uint32_t first_data_byte : 1;
    uint32_t rsvd            : 20;  /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_data_cmd_t;

/* i2c standard/ultra-fast speed clock scl high count register(offset address 0x14) */
typedef struct _i2c_ic_ss_ufm_scl_hcnt
{
    uint32_t cnt  : 16;
    uint32_t rsvd : 16; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_ss_ufm_scl_hcnt_t;

/* i2c standard/ultra-fast speed clock scl low count register(offset address 0x18) */
typedef struct _i2c_ic_ss_ufm_scl_lcnt
{
    uint32_t cnt  : 16;
    uint32_t rsvd : 16; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_ss_ufm_scl_lcnt_t;

/* i2c fast mode speed clock scl low count/ultra-fast mode speed tbuf idle count register(offset address 0x1c) */
typedef struct _i2c_ic_fs_scl_hcnt_ufm_tbuf_cnt
{
    uint32_t cnt  : 16;
    uint32_t rsvd : 16; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_fs_scl_hcnt_ufm_tbuf_cnt_t;

/* i2c fast mode clock scl low count register(offset address 0x20) */
typedef struct _i2c_ic_fs_scl_lcnt
{
    uint32_t cnt  : 16;
    uint32_t rsvd : 16; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_fs_scl_lcnt_t;

/* i2c high speed mode clock scl high count register(offset address 0x24) */
typedef struct _i2c_ic_hs_scl_hcnt
{
    uint32_t cnt  : 16;
    uint32_t rsvd : 16; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_hs_scl_hcnt_t;

/* i2c high speed mode clock scl low count register(offset address 0x28) */
typedef struct _i2c_ic_hs_scl_lcnt
{
    uint32_t cnt  : 16;
    uint32_t rsvd : 16; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_hs_scl_lcnt_t;

/* i2c interrupt status register(offset address 0x2c) */
typedef struct _i2c_ic_intr_stat
{
    uint32_t r_rx_under         : 1;
    uint32_t r_rx_over          : 1;
    uint32_t r_rx_full          : 1;
    uint32_t r_tx_over          : 1;
    uint32_t r_tx_empty         : 1;
    uint32_t r_rd_req           : 1;
    uint32_t r_tx_abrt          : 1;
    uint32_t r_rx_done          : 1;
    uint32_t r_activity         : 1;
    uint32_t r_stop_det         : 1;
    uint32_t r_start_det        : 1;
    uint32_t r_gen_call         : 1;
    uint32_t r_restart_det      : 1;
    uint32_t r_master_on_hold   : 1;
    uint32_t r_slc_stuck_at_low : 1;
    uint32_t rsvd               : 17;   /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_intr_stat_t;

/* i2c interrupt mask register(offset address 0x30) */
typedef struct _i2c_ic_intr_mask
{
    uint32_t m_rx_under         : 1;
    uint32_t m_rx_over          : 1;
    uint32_t m_rx_full          : 1;
    uint32_t m_tx_over          : 1;
    uint32_t m_tx_empty         : 1;
    uint32_t m_rd_req           : 1;
    uint32_t m_tx_abrt          : 1;
    uint32_t m_rx_done          : 1;
    uint32_t m_activity         : 1;
    uint32_t m_stop_det         : 1;
    uint32_t m_start_det        : 1;
    uint32_t m_gen_call         : 1;
    uint32_t m_restart_det      : 1;
    uint32_t m_master_on_hold   : 1;
    uint32_t m_slc_stuck_at_low : 1;
    uint32_t rsvd               : 17;   /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_intr_mask_t;

/* i2c raw interrupt status register(offset address 0x34) */
typedef struct _i2c_ic_raw_intr_stat
{
    uint32_t rx_under           : 1;
    uint32_t rx_over            : 1;
    uint32_t rx_full            : 1;
    uint32_t tx_over            : 1;
    uint32_t tx_empty           : 1;
    uint32_t rd_req             : 1;
    uint32_t tx_abrt            : 1;
    uint32_t rx_done            : 1;
    uint32_t activity           : 1;
    uint32_t stop_det           : 1;
    uint32_t start_det          : 1;
    uint32_t gen_call           : 1;
    uint32_t restart_det        : 1;
    uint32_t master_on_hold     : 1;
    uint32_t scl_stuck_at_low   : 1;
    uint32_t rsvd               : 17;   /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_raw_intr_stat_t;

/* i2c receive FIFO threshold register(offset address 0x38) */
typedef struct _i2c_ic_rx_tl
{
    uint32_t tl   : 8;
    uint32_t rsvd : 24;   /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_rx_tl_t;

/* i2c transmit FIFO threshold register(offset address 0x3c) */
typedef struct _i2c_ic_tx_tl
{
    uint32_t tl   : 8;
    uint32_t rsvd : 24; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_tx_tl_t;

/* i2c clear combined and individual interrupt register(offset address 0x40) */
typedef struct _i2c_ic_clr_intr
{
    uint32_t clr  : 1;
    uint32_t rsvd : 31; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_clr_intr_t;

/* i2c clear rx under interrupt register(offset address 0x44) */
typedef struct _i2c_ic_clr_rx_under
{
    uint32_t clr  : 1;
    uint32_t rsvd : 31; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_clr_rx_under_t;

/* i2c clear rx over interrupt register(offset address 0x48) */
typedef struct _i2c_ic_clr_rx_over
{
    uint32_t clr  : 1;
    uint32_t rsvd : 31; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_clr_rx_over_t;

/* i2c clear tx over interrupt register(offset address 0x4c) */
typedef struct _i2c_ic_clr_tx_over
{
    uint32_t clr  : 1;
    uint32_t rsvd : 31; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_clr_tx_over_t;

/* i2c clear rd req interrupt register(offset address 0x50) */
typedef struct _i2c_ic_clr_rd_req
{
    uint32_t clr  : 1;
    uint32_t rsvd : 31; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_clr_rd_req_t;

/* i2c clear tx abrt interrupt register(offset address 0x54) */
typedef struct _i2c_ic_clr_tx_abrt
{
    uint32_t clr  : 1;
    uint32_t rsvd : 31; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_clr_tx_abrt_t;

/* i2c clear rx done interrupt register(offset address 0x58) */
typedef struct _i2c_ic_clr_rx_done
{
    uint32_t clr  : 1;
    uint32_t rsvd : 31; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_clr_rx_done_t;

/* i2c clear activity interrupt register(offset address 0x5c) */
typedef struct _i2c_ic_clr_activity
{
    uint32_t clr  : 1;
    uint32_t rsvd : 31; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_clr_activity_t;

/* i2c clear stop det interrupt register(offset address 0x60) */
typedef struct _i2c_clr_stop_det
{
    uint32_t clr  : 1;
    uint32_t rsvd : 31; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_clr_stop_det_t;

/* i2c clear start det interrupt register(offset address 0x64) */
typedef struct _i2c_ic_clr_start_det
{
    uint32_t clr  : 1;
    uint32_t rsvd : 31; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_clr_start_det_t;

/* i2c clear gen call interrupt register(offset address 0x68) */
typedef struct _i2c_ic_clr_gen_call
{
    uint32_t clr  : 1;
    uint32_t rsvd : 31; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_clr_gen_call_t;

/* i2c enable register(offset address 0x6c) */
typedef struct _i2c_ic_enable
{
    uint32_t enable                    : 1;
    uint32_t abort                     : 1;
    uint32_t tx_cmd_block              : 1;
    uint32_t sda_stuck_recovery_enable : 1;
    uint32_t rsvd_1                    : 12;    /* reserved */
    uint32_t smbus_clk_reset           : 1;
    uint32_t smbus_suspned_en          : 1;
    uint32_t smbus_alert_en            : 1;
    uint32_t rsvd_2                    : 13;    /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_enable_t;

/* i2c status register(offset address 0x70) */
typedef struct _i2c_ic_status
{
    uint32_t activity                  : 1;
    uint32_t tfnf                      : 1;
    uint32_t tfe                       : 1;
    uint32_t rfne                      : 1;
    uint32_t rff                       : 1;
    uint32_t mst_activity              : 1;
    uint32_t slv_activity              : 1;
    uint32_t mst_hold_tx_fifo_empty    : 1;
    uint32_t mst_hold_rx_fifo_full     : 1;
    uint32_t slv_hold_tx_fifo_empty    : 1;
    uint32_t slv_hold_rx_fifo_full     : 1;
    uint32_t sda_stuck_not_recovered   : 1;
    uint32_t rsvd_1                    : 4;     /* reserved */
    uint32_t smbus_quick_cmd_bit       : 1;
    uint32_t smbus_slave_addr_valid    : 1;
    uint32_t smbus_slave_addr_resolved : 1;
    uint32_t smbus_suspend_status      : 1;
    uint32_t smbus_alert               : 1;
    uint32_t rsvd_2                    : 11;    /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_status_t;

/* i2c transmit fifo level register(offset address 0x74) */
typedef struct _i2c_ic_txflr
{
    uint32_t txflr : 5;
    uint32_t rsvd  : 27;    /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_txflr_t;

/* i2c receive fifo level register(offset address 0x78) */
typedef struct _i2c_ic_rxflr
{
    uint32_t rxflr : 5;
    uint32_t rsvd  : 27;    /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_rxflr_t;

/* i2c sda hold time length register(offset address 0x7c) */
typedef struct _i2c_ic_sda_hold
{
    uint32_t tx_hold : 16;
    uint32_t rx_hold : 8;
    uint32_t rsvd    : 8;   /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_sda_hold_t;

/* i2c transmit abort source register(offset address 0x80) */
typedef struct _i2c_ic_tx_abrt_source
{
    uint32_t abrt_7b_addr_noack        : 1;
    uint32_t abrt_10addr1_noack        : 1;
    uint32_t abrt_10addr2_noack        : 1;
    uint32_t abrt_txdata_noack         : 1;
    uint32_t abrt_gcall_noack          : 1;
    uint32_t abrt_gcall_read           : 1;
    uint32_t abrt_hs_ackdet            : 1;
    uint32_t abrt_sbyte_ackdet         : 1;
    uint32_t abrt_hs_norstrt           : 1;
    uint32_t abrt_sbyte_norstrt        : 1;
    uint32_t abrt_10b_rd_norstrt       : 1;
    uint32_t abrt_master_dis           : 1;
    uint32_t abrt_lost                 : 1;
    uint32_t abrt_slvflush_txfifo      : 1;
    uint32_t abrt_slv_arblost          : 1;
    uint32_t abrt_slvrd_intx           : 1;
    uint32_t abrt_user_abrt            : 1;
    uint32_t abrt_sda_stuck_at_low     : 1;
    uint32_t abrt_device_noack         : 1;
    uint32_t abrt_device_slvaddr_noack : 1;
    uint32_t abrt_device_write         : 1;
    uint32_t rsvd                      : 2; /* reserved */
    uint32_t tx_flush_cnt              : 9;
} __attribute__((packed, aligned(4))) i2c_ic_tx_abrt_source_t;

/* i2c generate slave data nack register(offset address 0x84) */
typedef struct _i2c_ic_slv_data_nack_only
{
    uint32_t nack : 1;
    uint32_t rsvd : 31; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_slv_data_nack_only_t;

/* i2c dma control register(offset address 0x88) */
typedef struct _i2c_ic_dma_cr
{
    uint32_t rdmae : 1;
    uint32_t tdmae : 1;
    uint32_t rsvd  : 30;    /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_dma_cr_t;

/* i2c dma transmit data level register(offset address 0x8c) */
typedef struct _i2c_ic_dma_tdlr
{
    uint32_t dmatdl : 5;
    uint32_t rsvd   : 27;   /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_dma_tdlr_t;

/* i2c dma receive data level register(offset address 0x90) */
typedef struct _i2c_ic_dma_rdlr
{
    uint32_t dmardl : 5;
    uint32_t rsvd   : 27;   /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_dma_rdlr_t;

/* i2c sda setup register(offset address 0x94) */
typedef struct _i2c_ic_sda_setup
{
    uint32_t setup : 8;
    uint32_t rsvd  : 24;    /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_sda_setup_t;

/* i2c ack general call register(offset address 0x98) */
typedef struct _i2c_ic_ack_general_call
{
    uint32_t ask  : 1;
    uint32_t rsvd : 31; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_ack_general_call_t;

/* i2c enable status register(offset address 0x9c) */
typedef struct _i2c_ic_enable_status
{
    uint32_t en                      : 1;
    uint32_t slv_disabled_while_busy : 1;
    uint32_t slv_rx_data_lost        : 1;
    uint32_t rsvd                    : 29;  /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_enable_status_t;

/* i2c ss, fs, or fm+/ufm spike suppression limit register(offset address 0xa0) */
typedef struct _i2c_ic_fs_ufm_spklen
{
    uint32_t spklen : 8;
    uint32_t rsvd   : 24;   /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_fs_ufm_spklen_t;

/* i2c hs spike suppression limit register(offset address 0xa4) */
typedef struct _i2c_ic_hs_spklen
{
    uint32_t spklen : 8;
    uint32_t rsvd   : 24;   /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_hs_spklen_t;

/* i2c clear restart det interrupt register(offset address 0xa8) */
typedef struct _i2c_ic_clr_restart_det
{
    uint32_t clr  : 1;
    uint32_t rsvd : 31; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_clr_restart_det_t;

/* i2c scl stuck at low timeout register(offset address 0xac) */
typedef struct _i2c_ic_scl_stuck_at_low_timeout
{
    uint32_t timeout  : 32;
} __attribute__((packed, aligned(4))) i2c_ic_scl_stuck_at_low_timeout_t;

/* i2c sda stuck at low timeout register(offset address 0xb0) */
typedef struct _i2c_ic_sda_stuck_at_low_timeout
{
    uint32_t timeout  : 32;
} __attribute__((packed, aligned(4))) i2c_ic_sda_stuck_at_low_timeout_t;

/* i2c clear scl stuck at low detect interrupt register(offset address 0xb4) */
typedef struct _i2c_ic_clr_slc_stuck_det
{
    uint32_t clr  : 1;
    uint32_t rsvd : 31; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_clr_slc_stuck_det_t;

/* i2c device id register(offset address 0xb8) */
typedef struct _i2c_ic_device_id
{
    uint32_t device_id : 24;
    uint32_t rsvd      : 8; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_device_id_t;

/* i2c smbus slave clock extend timeout register(offset address 0xbc) */
typedef struct _i2c_ic_smbus_clk_low_sext
{
    uint32_t timeout : 32;
} __attribute__((packed, aligned(4))) i2c_ic_smbus_clk_low_sext_t;

/* i2c smbus master clock extend timeout register(offset address 0xc0) */
typedef struct _i2c_ic_smbus_clk_low_mext
{
    uint32_t timeout : 32;
} __attribute__((packed, aligned(4))) i2c_ic_smbus_clk_low_mext_t;

/* i2c smbus master thigh max bus-idle count register(offset address 0xc4) */
typedef struct _i2c_ic_smbus_thigh_max_idle_count
{
    uint32_t cnt  : 16;
    uint32_t rsvd : 16; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_smbus_thigh_max_idle_count_t;

/* i2c smbus interrupt status register(offset address 0xc8) */
typedef struct _i2c_ic_smbus_intr_stat
{
    uint32_t r_slv_clock_extnd_timeout : 1;
    uint32_t r_mst_clock_extnd_timeout : 1;
    uint32_t r_quick_cmd_det           : 1;
    uint32_t r_host_notify_mst_det     : 1;
    uint32_t r_arp_prepare_cmd_det     : 1;
    uint32_t r_arp_rst_cmd_det         : 1;
    uint32_t r_arp_get_udid_cmd_det    : 1;
    uint32_t r_arp_assgn_addr_cmd_det  : 1;
    uint32_t r_slv_rx_pec_nack         : 1;
    uint32_t r_smbus_suspend_det       : 1;
    uint32_t r_smbus_alert_det         : 1;
    uint32_t rsvd                      : 21;    /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_smbus_intr_stat_t;

/* i2c smbus interrupt mask register(offset address 0xcc) */
typedef struct _i2c_ic_smbus_intr_mask
{
    uint32_t m_slv_clock_extnd_timeout : 1;
    uint32_t m_mst_clock_extnd_timeout : 1;
    uint32_t m_quick_cmd_det           : 1;
    uint32_t m_host_notify_mst_det     : 1;
    uint32_t m_arp_prepare_cmd_det     : 1;
    uint32_t m_arp_rst_cmd_det         : 1;
    uint32_t m_arp_get_udid_cmd_det    : 1;
    uint32_t m_arp_assgn_addr_cmd_det  : 1;
    uint32_t m_slv_rx_pec_nack         : 1;
    uint32_t m_smbus_suspend_det       : 1;
    uint32_t m_smbus_alert_det         : 1;
    uint32_t rsvd                      : 21;    /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_smbus_intr_mask_t;

/* i2c smbus raw interrupt status register(offset address 0xd0) */
typedef struct _i2c_ic_smbus_raw_intr_stat
{
    uint32_t slv_clock_extnd_timeout : 1;
    uint32_t mst_clock_extnd_timeout : 1;
    uint32_t quick_cmd_det           : 1;
    uint32_t host_notify_mst_det     : 1;
    uint32_t arp_prepare_cmd_det     : 1;
    uint32_t arp_rst_cmd_det         : 1;
    uint32_t arp_get_udid_cmd_det    : 1;
    uint32_t arp_assgn_addr_cmd_det  : 1;
    uint32_t slv_rx_pec_nack         : 1;
    uint32_t smbus_suspend_det       : 1;
    uint32_t smbus_alert_det         : 1;
    uint32_t rsvd                    : 21;  /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_smbus_raw_intr_stat_t;

/* i2c smbus clear interrupt register(offset address 0xd4) */
typedef struct _i2c_ic_clr_smbus_intr
{
    uint32_t slv_clock_extnd_timeout : 1;
    uint32_t mst_clock_extnd_timeout : 1;
    uint32_t quick_cmd_det           : 1;
    uint32_t host_notify_mst_det     : 1;
    uint32_t arp_prepare_cmd_det     : 1;
    uint32_t arp_rst_cmd_det         : 1;
    uint32_t arp_get_udid_cmd_det    : 1;
    uint32_t arp_assgn_addr_cmd_det  : 1;
    uint32_t slv_rx_pec_nack         : 1;
    uint32_t smbus_suspend_det       : 1;
    uint32_t smbus_alert_det         : 1;
    uint32_t rsvd                    : 21;  /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_clr_smbus_intr_t;

/* i2c optional slave address register(offset address 0xd8) */
typedef struct _i2c_ic_optional_sar
{
    uint32_t sar  : 7;
    uint32_t rsvd : 25; /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_optional_sar_t;

/* i2c smbus udid lsb register(offset address 0xdc) */
typedef struct _i2c_ic_smbus_udid_lsb
{
    uint32_t udid_lsb : 32;
} __attribute__((packed, aligned(4))) i2c_ic_smbus_udid_lsb_t;

/* i2c component parameter 1 register(offset address 0xf4) */
typedef struct _i2c_ic_comp_param_1
{
    uint32_t apb_data_width     : 2;
    uint32_t max_speed_mode     : 2;
    uint32_t hc_count_values    : 1;
    uint32_t intr_io            : 1;
    uint32_t has_dma            : 1;
    uint32_t add_encoded_params : 1;
    uint32_t rx_buffer_depth    : 8;
    uint32_t tx_buffer_depth    : 8;
    uint32_t rsvd               : 8;    /* reserved */
} __attribute__((packed, aligned(4))) i2c_ic_comp_param_1_t;

/* i2c component version register(offset address 0xf8) */
typedef struct _i2c_ic_comp_version
{
    uint32_t version : 32;
} __attribute__((packed, aligned(4))) i2c_ic_comp_version_t;

/* i2c component type register(offset address 0xfc) */
typedef struct _i2c_ic_comp_type
{
    uint32_t type : 32;
} __attribute__((packed, aligned(4))) i2c_ic_comp_type_t;

/* i2c register */
typedef struct _i2c
{
    i2c_ic_con_t                        con;                        /* 0x00 */
    i2c_ic_tar_t                        tar;                        /* 0x04 */
    i2c_ic_sar_t                        sar;                        /* 0x08 */
    i2c_ic_hs_maddr_t                   hs_maddr;                   /* 0x0c */
    i2c_ic_data_cmd_t                   data_cmd;                   /* 0x10 */
    i2c_ic_ss_ufm_scl_hcnt_t            ss_ufm_scl_hcnt;            /* 0x14 */
    i2c_ic_ss_ufm_scl_lcnt_t            ss_ufm_scl_lcnt;            /* 0x18 */
    i2c_ic_fs_scl_hcnt_ufm_tbuf_cnt_t   fs_scl_hcnt_ufm_tbuf_cnt;   /* 0x1c */
    i2c_ic_fs_scl_lcnt_t                fs_scl_lcnt;                /* 0x20 */
    i2c_ic_hs_scl_hcnt_t                hs_scl_hcnt;                /* 0x24 */
    i2c_ic_hs_scl_lcnt_t                hs_scl_lcnt;                /* 0x28 */
    i2c_ic_intr_stat_t                  intr_stat;                  /* 0x2c */
    i2c_ic_intr_mask_t                  intr_mask;                  /* 0x30 */
    i2c_ic_raw_intr_stat_t              raw_intr_stat;              /* 0x34 */
    i2c_ic_rx_tl_t                      rx_tl;                      /* 0x38 */
    i2c_ic_tx_tl_t                      tx_tl;                      /* 0x3c */
    i2c_ic_clr_intr_t                   clr_intr;                   /* 0x40 */
    i2c_ic_clr_rx_under_t               clr_rx_under;               /* 0x44 */
    i2c_ic_clr_rx_over_t                clr_rx_over;                /* 0x48 */
    i2c_ic_clr_tx_over_t                clr_tx_over;                /* 0x4c */
    i2c_ic_clr_rd_req_t                 clr_rd_req;                 /* 0x50 */
    i2c_ic_clr_tx_abrt_t                clr_tx_abrt;                /* 0x54 */
    i2c_ic_clr_rx_done_t                clr_rx_done;                /* 0x58 */
    i2c_ic_clr_activity_t               clr_activity;               /* 0x5c */
    i2c_ic_clr_stop_det_t               clr_stop_det;               /* 0x60 */
    i2c_ic_clr_start_det_t              clr_start_det;              /* 0x64 */
    i2c_ic_clr_gen_call_t               clr_gen_call;               /* 0x68 */
    i2c_ic_enable_t                     enable;                     /* 0x6c */
    i2c_ic_status_t                     status;                     /* 0x70 */
    i2c_ic_txflr_t                      txflr;                      /* 0x74 */
    i2c_ic_rxflr_t                      rxflr;                      /* 0x78 */
    i2c_ic_sda_hold_t                   sda_hold;                   /* 0x7c */
    i2c_ic_tx_abrt_source_t             tx_abrt_source;             /* 0x80 */
    i2c_ic_slv_data_nack_only_t         slv_data_nack_only;         /* 0x84 */
    i2c_ic_dma_cr_t                     dma_cr;                     /* 0x88 */
    i2c_ic_dma_tdlr_t                   dma_tdlr;                   /* 0x8c */
    i2c_ic_dma_rdlr_t                   dma_rdlr;                   /* 0x90 */
    i2c_ic_sda_setup_t                  sda_setup;                  /* 0x94 */
    i2c_ic_ack_general_call_t           ack_general_call;           /* 0x98 */
    i2c_ic_enable_status_t              enable_status;              /* 0x9c */
    i2c_ic_fs_ufm_spklen_t              fs_ufm_spklen;              /* 0xa0 */
    i2c_ic_hs_spklen_t                  hs_spklen;                  /* 0xa4 */
    i2c_ic_clr_restart_det_t            clr_restart_det;            /* 0xa8 */
    i2c_ic_scl_stuck_at_low_timeout_t   scl_stuck_at_low_timeout;   /* 0xac */
    i2c_ic_sda_stuck_at_low_timeout_t   sda_stuck_at_low_timeout;   /* 0xb0 */
    i2c_ic_clr_slc_stuck_det_t          clr_slc_stuck_det;          /* 0xb4 */
    i2c_ic_device_id_t                  device_id;                  /* 0xb8 */
    i2c_ic_smbus_clk_low_sext_t         smbus_clk_low_sext;         /* 0xbc */
    i2c_ic_smbus_clk_low_mext_t         smbus_clk_low_mext;         /* 0xc0 */
    i2c_ic_smbus_thigh_max_idle_count_t smbus_thigh_max_idle_count; /* 0xc4 */
    i2c_ic_smbus_intr_stat_t            smbus_intr_stat;            /* 0xc8 */
    i2c_ic_smbus_intr_mask_t            smbus_intr_mask;            /* 0xcc */
    i2c_ic_smbus_raw_intr_stat_t        smbus_raw_intr_stat;        /* 0xd0 */
    i2c_ic_clr_smbus_intr_t             clr_smbus_intr;             /* 0xd4 */
    i2c_ic_optional_sar_t               optional_sar;               /* 0xd8 */
    i2c_ic_smbus_udid_lsb_t             smbus_udid_lsb;             /* 0xdc */
    uint32_t                            rsvd_1[5];                  /* 0xe0-0xf0 reserved */
    i2c_ic_comp_param_1_t               comp_param_1;               /* 0xf4 */
    i2c_ic_comp_version_t               comp_version;               /* 0xf8 */
    i2c_ic_comp_type_t                  comp_type;                  /* 0xfc */
} __attribute__((packed, aligned(4))) i2c_t;

#endif /* __DRV_I2C_H__ */
