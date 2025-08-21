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

#ifndef DRV_PDMA_H_
#define DRV_PDMA_H_

#include <rtdef.h>
#include "board.h"

/**
 * @brief PDMA channel enumeration
 */
typedef enum pdma_ch {
    PDMA_CH_0 = 0,  /**< Channel 0 */
    PDMA_CH_1 = 1,  /**< Channel 1 */
    PDMA_CH_2 = 2,  /**< Channel 2 */
    PDMA_CH_3 = 3,  /**< Channel 3 */
    PDMA_CH_4 = 4,  /**< Channel 4 */
    PDMA_CH_5 = 5,  /**< Channel 5 */
    PDMA_CH_6 = 6,  /**< Channel 6 */
    PDMA_CH_7 = 7,  /**< Channel 7 */
    PDMA_CH_MAX,    /**< Maximum channel count */
} pdma_ch_e;

/* PDMA Register Access Macros */
#define pdma_write32(addr, val)    writel((val), (volatile void *)(addr))
#define pdma_read32(addr)          readl((volatile void *)(addr))

/* PDMA Configuration Constants */
#define PDMA_MAX_WAIT_MS           2000    /* Maximum wait time in milliseconds */
#define PDMA_MAX_LINE_SIZE         64      /* Maximum data block size per transfer */

/**
 * @brief PDMA Interrupt Mask Definitions
 *
 * These macros define the bitmask values for different PDMA interrupt types.
 * Each interrupt type is represented by a unique bit in the interrupt status register.
 */
#define PDMA_PDONE_INT          0x00000001  /**< Transfer Done interrupt mask */
#define PDMA_PITEM_INT          0x00000100  /**< Item Done interrupt mask */
#define PDMA_PPAUSE_INT         0x00010000  /**< Transfer Paused interrupt mask */
#define PDMA_PTOUT_INT          0x01000000  /**< Transfer Timeout interrupt mask */

/* Combined interrupt masks */
#define PDMA_ALL_INTS       (PDMA_PDONE_INT | PDMA_PITEM_INT | PDMA_PPAUSE_INT | PDMA_PTOUT_INT) /**< All PDMA interrupts mask */

/**
 * @brief PDMA channel interrupt numbers
 */
#define PDMA_CHANNEL0_IRQn     K230_IRQ_PDMA           /**< Channel 0 IRQ number */
#define PDMA_CHANNEL1_IRQn     K230_IRQ_PDMA_CHANNEL1  /**< Channel 1 IRQ number */
#define PDMA_CHANNEL2_IRQn     K230_IRQ_PDMA_CHANNEL2  /**< Channel 2 IRQ number */
#define PDMA_CHANNEL3_IRQn     K230_IRQ_PDMA_CHANNEL3  /**< Channel 3 IRQ number */
#define PDMA_CHANNEL4_IRQn     K230_IRQ_PDMA_CHANNEL4  /**< Channel 4 IRQ number */
#define PDMA_CHANNEL5_IRQn     K230_IRQ_PDMA_CHANNEL5  /**< Channel 5 IRQ number */
#define PDMA_CHANNEL6_IRQn     K230_IRQ_PDMA_CHANNEL6  /**< Channel 6 IRQ number */
#define PDMA_CHANNEL7_IRQn     K230_IRQ_PDMA_CHANNEL7  /**< Channel 7 IRQ number */

/**
 * @brief PDMA channel state enumeration
 */
typedef enum {
    PDMA_STATE_BUSY    = 0x1,    /**< Channel is busy transferring */
    PDMA_STATE_PAUSE   = 0x2,    /**< Channel is paused */
} pdma_state_e;

/**
 * @brief PDMA control command enumeration
 */
typedef enum {
    PDMA_CMD_START     = 0x1,    /**< Start DMA transfer command */
    PDMA_CMD_STOP      = 0x2,    /**< Stop DMA transfer command */
    PDMA_CMD_RESUME    = 0x4,    /**< Resume paused transfer command */
} pdma_cmd_e;

/**
 * @brief PDMA data transfer direction enumeration
 *
 * @param TX Transmit direction: Data flows from system memory to peripheral device
 * @param RX Receive direction: Data flows from peripheral device to system memory
 */
typedef enum pdma_rxtx {
    TX = 0,
    RX = 1,
} pdma_rxtx_e;

/**
 * @brief PDMA burst length configuration
 */
typedef enum pdma_burst_len {
    PBURST_LEN_1 = 0,
    PBURST_LEN_2 = 1,
    PBURST_LEN_3 = 2,
    PBURST_LEN_4 = 3,
    PBURST_LEN_5 = 4,
    PBURST_LEN_6 = 5,
    PBURST_LEN_7 = 6,
    PBURST_LEN_8 = 7,
    PBURST_LEN_9 = 8,
    PBURST_LEN_10 = 9,
    PBURST_LEN_11 = 10,
    PBURST_LEN_12 = 11,
    PBURST_LEN_13 = 12,
    PBURST_LEN_14 = 13,
    PBURST_LEN_15 = 14,
    PBURST_LEN_16 = 15,
} pdma_burst_len_e;

/**
 * @brief Peripheral device selection for PDMA
 */
typedef enum device_sel {
    UART0_TX = 0,
    UART0_RX = 1,
    UART1_TX = 2,
    UART1_RX = 3,
    UART2_TX = 4,
    UART2_RX = 5,
    UART3_TX = 6,
    UART3_RX = 7,
    UART4_TX = 8,
    UART4_RX = 9,
    I2C0_TX = 10,
    I2C0_RX = 11,
    I2C1_TX = 12,
    I2C1_RX = 13,
    I2C2_TX = 14,
    I2C2_RX = 15,
    I2C3_TX = 16,
    I2C3_RX = 17,
    I2C4_TX = 18,
    I2C4_RX = 19,
    AUDIO_TX = 20,
    AUDIO_RX = 21,
    JAMLINK0_TX = 22,
    JAMLINK0_RX = 23,
    JAMLINK1_TX = 24,
    JAMLINK1_RX = 25,
    JAMLINK2_TX = 26,
    JAMLINK2_RX = 27,
    JAMLINK3_TX = 28,
    JAMLINK3_RX = 29,
    ADC0 = 30,
    ADC1 = 31,
    ADC2 = 32,
    PDM_IN = 33,
} device_sel_e;

/**
 * @brief Data endianness configuration
 */
typedef enum pendian {
    PDEFAULT,
    PBYTE2,
    PBYTE4,
    PBYTE8,
} pendian_e;

/**
 * @brief Data transfer size configuration
 */
typedef enum hsize {
    PSBYTE1,
    PSBYTE2,
    PSBYTE4,
} hsize_e;

/**
 * @brief Source address behavior configuration
 */
typedef enum src_type {
    CONTINUE,
    FIXED,
} src_type_e;

/**
 * @brief PDMA channel configuration structure
 */
typedef struct pdma_ch_cfg {
    volatile rt_uint32_t ch_src_type : 1;
    volatile rt_uint32_t ch_dev_hsize : 2;
    volatile rt_uint32_t reserved0 : 1;
    volatile rt_uint32_t ch_dat_endian : 2;
    volatile rt_uint32_t reserved1 : 2;
    volatile rt_uint32_t ch_dev_blen : 4;
    volatile rt_uint32_t ch_priority : 4;
    volatile rt_uint32_t ch_dev_tout : 12;
    volatile rt_uint32_t reserved2 : 4;
} pdma_ch_cfg_t;

/**
 * @brief PDMA channel register structure
 */
typedef struct pdma_ch_reg {
    volatile rt_uint32_t ch_ctl;
    volatile rt_uint32_t ch_status;
    volatile pdma_ch_cfg_t ch_cfg;
    volatile rt_uint32_t ch_llt_saddr;
    volatile rt_uint32_t reserved[4];
} pdma_ch_reg_t;

/**
 * @brief PDMA controller register structure
 */
typedef struct pdma_reg {
    volatile rt_uint32_t pdma_ch_en;
    volatile rt_uint32_t dma_int_mask;
    volatile rt_uint32_t dma_int_stat;
    volatile rt_uint32_t reserved[5];
    volatile pdma_ch_reg_t pdma_ch_reg[8];
    volatile rt_uint32_t ch_peri_dev_sel[8];
} pdma_reg_t;

/**
 * @brief PDMA Linked List Transfer (LLT) node structure
 */
typedef struct pdma_llt {
    rt_uint32_t line_size : 30;    /**< Transfer length in bytes */
    rt_uint32_t pause : 1;         /**< Pause control flag */
    rt_uint32_t node_intr : 1;     /**< Node completion interrupt enable */
    rt_uint32_t src_addr;          /**< Source address */
    rt_uint32_t dst_addr;          /**< Destination address */
    rt_uint32_t next_llt_addr;     /**< Next LLT node address */
} pdma_llt_t;

/**
 * @brief User PDMA configuration structure
 */
typedef struct usr_pdma_cfg {
    device_sel_e device;           /**< Peripheral device selection */
    rt_uint8_t *src_addr;          /**< Source address pointer */
    rt_uint8_t *dst_addr;          /**< Destination address pointer */
    rt_uint32_t line_size;         /**< Transfer block size */
    pdma_ch_cfg_t pdma_ch_cfg;     /**< Channel configuration */
} usr_pdma_cfg_t;

/**
 * @brief DMA transfer event callback function type
 * @param ch DMA channel number where event occurred
 * @param is_done Event type indicator:
 *               - RT_TRUE: Transfer completed successfully
 *               - RT_FALSE: Transfer terminated due to timeout
 * @note This callback will be invoked for both successful completion
 *       and timeout conditions. The is_done parameter distinguishes
 *       between these cases.
 */
typedef void (*k230_pdma_callback_t)(rt_uint8_t ch, rt_bool_t is_done);

/**
 * @brief DMA channel callback structure
 * Contains callback function for DMA channel events
 */
typedef struct {
    k230_pdma_callback_t callback;  /* Callback function pointer */
} k230_pdma_chan_cb_t;

/**
 * @brief PDMA controller structure
 */
typedef struct {
    rt_int32_t hardlock;             /**< Hardware lock for critical sections */
    volatile pdma_reg_t *reg;        /**< PDMA register base address */

    struct {
        rt_uint32_t irq_num;         /**< Interrupt number for this channel */
        void *llt_va;                /**< Virtual address of LLT memory (NULL if not allocated) */
        rt_size_t page_size;         /**< Page size for each channel */
        k230_pdma_chan_cb_t cb;      /**< Channel callback functions */
        rt_bool_t is_hw_configured;  /**< Hardware config flag (must set via k230_pdma_config() before start to avoid BUSY lock) */
        rt_bool_t menuconfig_enabled;/**< Channel enabled in menuconfig */
    } chan[PDMA_CH_MAX];             /**< Channel configuration array */
} pdma_controller_t;

/**
 * @brief Set PDMA callback function for specified channel
 */
rt_err_t k230_pdma_set_callback(rt_uint8_t ch, k230_pdma_callback_t func);

/**
 * @brief Request an available PDMA channel
 */
rt_err_t k230_pdma_request_channel(rt_uint8_t *ch);

/**
 * @brief Release allocated PDMA channel
 */
rt_err_t k230_pdma_release_channel(rt_uint8_t ch);

/**
 * @brief Start PDMA transfer on specified channel
 */
rt_err_t k230_pdma_start(rt_uint8_t ch);

/**
 * @brief Stop PDMA transfer on specified channel
 */
rt_err_t k230_pdma_stop(rt_uint8_t ch);

/**
 * @brief Configure PDMA channel parameters
 */
rt_err_t k230_pdma_config(rt_uint8_t ch, usr_pdma_cfg_t *ucfg);

#endif /* DRV_PDMA_H_ */
