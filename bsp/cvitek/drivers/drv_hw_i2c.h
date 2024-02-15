/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 *2024-02-14      ShichengChu  first version
 */
#ifndef __DRV_HW_I2C_H__
#define __DRV_HW_I2C_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>

#include "pinctrl.h"
#include "mmio.h"

#define I2C0                    0x0
#define I2C1                    0x1
#define I2C2                    0x2
#define I2C3                    0x3
#define I2C4                    0x4

#define I2C0_BASE                0x4000000
#define I2C1_BASE                0x4010000
#define I2C2_BASE                0x4020000
#define I2C3_BASE                0x4030000
#define I2C4_BASE                0x4040000

#define BIT_I2C_CMD_DATA_READ_BIT           (0x01 << 8)
#define BIT_I2C_CMD_DATA_STOP_BIT           (0x01 << 9)

/* bit definition */
#define BIT_I2C_CON_MASTER_MODE              (0x01 << 0)
#define BIT_I2C_CON_STANDARD_SPEED           (0x01 << 1)
#define BIT_I2C_CON_FULL_SPEED               (0x02 << 1)
#define BIT_I2C_CON_HIGH_SPEED               (0x03 << 1)
#define BIT_I2C_CON_10B_ADDR_SLAVE           (0x01 << 3)
#define BIT_I2C_CON_10B_ADDR_MASTER          (0x01 << 4)
#define BIT_I2C_CON_RESTART_EN               (0x01 << 5)
#define BIT_I2C_CON_SLAVE_DIS                (0x01 << 6)

#define BIT_I2C_TAR_10B_ADDR_MASTER     (0x01 << 12)

#define BIT_I2C_INT_RX_UNDER                 (0x01 << 0)
#define BIT_I2C_INT_RX_OVER                  (0x01 << 1)
#define BIT_I2C_INT_RX_FULL                  (0x01 << 2)
#define BIT_I2C_INT_TX_OVER                  (0x01 << 3)
#define BIT_I2C_INT_TX_EMPTY                 (0x01 << 4)
#define BIT_I2C_INT_RD_REQ                   (0x01 << 5)
#define BIT_I2C_INT_TX_ABRT                  (0x01 << 6)
#define BIT_I2C_INT_RX_DONE                  (0x01 << 7)
#define BIT_I2C_INT_ACTIVITY                 (0x01 << 8)
#define BIT_I2C_INT_STOP_DET                 (0x01 << 9)
#define BIT_I2C_INT_START_DET                (0x01 << 10)
#define BIT_I2C_INT_GEN_ALL                  (0x01 << 11)
#define I2C_INTR_MASTER_MASK         (BIT_I2C_INT_TX_ABRT | \
                    BIT_I2C_INT_STOP_DET | \
                    BIT_I2C_INT_RX_FULL | \
                    BIT_I2C_INT_TX_EMPTY)

#define BIT_I2C_INT_RX_UNDER_MASK            (0x01 << 0)
#define BIT_I2C_INT_RX_OVER_MASK             (0x01 << 1)
#define BIT_I2C_INT_RX_FULL_MASK             (0x01 << 2)
#define BIT_I2C_INT_TX_OVER_MASK             (0x01 << 3)
#define BIT_I2C_INT_TX_EMPTY_MASK            (0x01 << 4)
#define BIT_I2C_INT_RD_REQ_MASK              (0x01 << 5)
#define BIT_I2C_INT_TX_ABRT_MASK             (0x01 << 6)
#define BIT_I2C_INT_RX_DONE_MASK             (0x01 << 7)
#define BIT_I2C_INT_ACTIVITY_MASK            (0x01 << 8)
#define BIT_I2C_INT_STOP_DET_MASK            (0x01 << 9)
#define BIT_I2C_INT_START_DET_MASK           (0x01 << 10)
#define BIT_I2C_INT_GEN_ALL_MASK             (0x01 << 11)

#define BIT_I2C_INT_RX_UNDER_RAW             (0x01 << 0)
#define BIT_I2C_INT_RX_OVER_RAW              (0x01 << 1)
#define BIT_I2C_INT_RX_FULL_RAW              (0x01 << 2)
#define BIT_I2C_INT_TX_OVER_RAW              (0x01 << 3)
#define BIT_I2C_INT_TX_EMPTY_RAW             (0x01 << 4)
#define BIT_I2C_INT_RD_REQ_RAW               (0x01 << 5)
#define BIT_I2C_INT_TX_ABRT_RAW              (0x01 << 6)
#define BIT_I2C_INT_RX_DONE_RAW              (0x01 << 7)
#define BIT_I2C_INT_ACTIVITY_RAW             (0x01 << 8)
#define BIT_I2C_INT_STOP_DET_RAW             (0x01 << 9)
#define BIT_I2C_INT_START_DET_RAW            (0x01 << 10)
#define BIT_I2C_INT_GEN_ALL_RAW              (0x01 << 11)

#define BIT_I2C_DMA_CR_TDMAE                 (0x01 << 1)
#define BIT_I2C_DMA_CR_RDMAE                 (0x01 << 0)

struct i2c_regs {
    volatile uint32_t ic_con;        /* 0x00 */
    volatile uint32_t ic_tar;        /* 0x04 */
    volatile uint32_t ic_sar;        /* 0x08 */
    volatile uint32_t ic_hs_maddr;    /* 0x0c */
    volatile uint32_t ic_cmd_data;    /* 0x10 */
    volatile uint32_t ic_ss_scl_hcnt;    /* 0x14 */
    volatile uint32_t ic_ss_scl_lcnt;    /* 0x18 */
    volatile uint32_t ic_fs_scl_hcnt;    /* 0x1c */
    volatile uint32_t ic_fs_scl_lcnt;    /* 0x20 */
    volatile uint32_t ic_hs_scl_hcnt;    /* 0x24 */
    volatile uint32_t ic_hs_scl_lcnt;    /* 0x28 */
    volatile uint32_t ic_intr_stat;    /* 0x2c */
    volatile uint32_t ic_intr_mask;    /* 0x30 */
    volatile uint32_t ic_raw_intr_stat;    /* 0x34 */
    volatile uint32_t ic_rx_tl;        /* 0x38 */
    volatile uint32_t ic_tx_tl;        /* 0x3c */
    volatile uint32_t ic_clr_intr;     /* 0x40 */
    volatile uint32_t ic_clr_rx_under;   /* 0x44 */
    volatile uint32_t ic_clr_rx_over;    /* 0x48 */
    volatile uint32_t ic_clr_tx_over;    /* 0x4c */
    volatile uint32_t ic_clr_rd_req;     /* 0x50 */
    volatile uint32_t ic_clr_tx_abrt;    /* 0x54 */
    volatile uint32_t ic_clr_rx_done;    /* 0x58 */
    volatile uint32_t ic_clr_activity;   /* 0x5c */
    volatile uint32_t ic_clr_stop_det;   /* 0x60 */
    volatile uint32_t ic_clr_start_det;  /* 0x64 */
    volatile uint32_t ic_clr_gen_call;   /* 0x68 */
    volatile uint32_t ic_enable;         /* 0x6c */
    volatile uint32_t ic_status;         /* 0x70 */
    volatile uint32_t ic_txflr;          /* 0x74 */
    volatile uint32_t ic_rxflr;          /* 0x78 */
    volatile uint32_t ic_sda_hold;       /* 0x7c */
    volatile uint32_t ic_tx_abrt_source;    /* 0x80 */
    volatile uint32_t ic_slv_dat_nack_only; /* 0x84 */
    volatile uint32_t ic_dma_cr;      /* 0x88 */
    volatile uint32_t ic_dma_tdlr;    /* 0x8c */
    volatile uint32_t ic_dma_rdlr;    /* 0x90 */
    volatile uint32_t ic_sda_setup;   /* 0x94 */
    volatile uint32_t ic_ack_general_call; /* 0x98 */
    volatile uint32_t ic_enable_status;    /* 0x9c */
    volatile uint32_t ic_fs_spklen;    /* 0xa0 */
    volatile uint32_t ic_hs_spklen;    /* 0xa4 */
};

#if !defined(IC_CLK)
#define IC_CLK            100
#endif

#define NANO_TO_MICRO        1000

/* High and low times in different speed modes (in ns) */
#define MIN_SS_SCL_HIGHTIME    4000
#define MIN_SS_SCL_LOWTIME     4700
#define MIN_FS_SCL_HIGHTIME    600
#define MIN_FS_SCL_LOWTIME     1300
#define MIN_HS100pF_SCL_HIGHTIME 60
#define MIN_HS100pF_SCL_LOWTIME    120
#define MIN_HS400pF_SCL_HIGHTIME   160
#define MIN_HS400pF_SCL_LOWTIME    320

#define CONFIG_SYS_HZ        1000    /* decrementer freq: 1ms ticks */
/* Worst case timeout for 1 byte is kept as 2ms */
#define I2C_BYTE_TO        (CONFIG_SYS_HZ/500)

#define I2C_STOPDET_TO        (CONFIG_SYS_HZ/500)
#define I2C_BYTE_TO_BB        (I2C_BYTE_TO * 16)

/* i2c control register definitions */
#define IC_CON_SD        0x0040
#define IC_CON_RE        0x0020
#define IC_CON_10BITADDRMASTER    0x0010
#define IC_CON_10BITADDR_SLAVE    0x0008
#define IC_CON_SPD_MSK       0x0006
#define IC_CON_SPD_SS        0x0002
#define IC_CON_SPD_FS        0x0004
#define IC_CON_SPD_HS        0x0006
#define IC_CON_MM        0x0001

/* i2c data buffer and command register definitions */
#define IC_CMD            0x0100
#define IC_STOP           0x0200

/* i2c interrupt status register definitions */
#define IC_GEN_CALL        0x0800
#define IC_START_DET       0x0400
#define IC_STOP_DET        0x0200
#define IC_ACTIVITY        0x0100
#define IC_RX_DONE         0x0080
#define IC_TX_ABRT         0x0040
#define IC_RD_REQ          0x0020
#define IC_TX_EMPTY        0x0010
#define IC_TX_OVER         0x0008
#define IC_RX_FULL         0x0004
#define IC_RX_OVER         0x0002
#define IC_RX_UNDER        0x0001

/* fifo threshold register definitions */
#define IC_TL0            0x00
#define IC_TL1            0x01
#define IC_TL2            0x02
#define IC_TL3            0x03
#define IC_TL4            0x04
#define IC_TL5            0x05
#define IC_TL6            0x06
#define IC_TL7            0x07
#define IC_RX_TL        IC_TL0
#define IC_TX_TL        IC_TL0

/* i2c enable register definitions */
#define IC_ENABLE        0x0001

/* i2c status register  definitions */
#define IC_STATUS_SA        0x0040
#define IC_STATUS_MA        0x0020
#define IC_STATUS_RFF       0x0010
#define IC_STATUS_RFNE      0x0008
#define IC_STATUS_TFE       0x0004
#define IC_STATUS_TFNF      0x0002
#define IC_STATUS_ACT       0x0001

/* Speed Selection */
#define IC_SPEED_MODE_STANDARD  1
#define IC_SPEED_MODE_FAST      2
#define IC_SPEED_MODE_MAX       3

#define I2C_MAX_SPEED         3400000
#define I2C_FAST_SPEED        400000
#define I2C_STANDARD_SPEED    100000

#define I2C_SPEED        I2C_FAST_SPEED

#define I2C0_IRQ           (I2C_IRQ_BASE + 0)
#define I2C1_IRQ           (I2C_IRQ_BASE + 1)
#define I2C2_IRQ           (I2C_IRQ_BASE + 2)
#define I2C3_IRQ           (I2C_IRQ_BASE + 3)
#define I2C4_IRQ           (I2C_IRQ_BASE + 4)

int rt_hw_i2c_init(void);

#endif /* __DRV_HW_I2C_H__ */
