/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef HPM_ROMAPI_XPI_DEF_H
#define HPM_ROMAPI_XPI_DEF_H

/**
 * @brief XPI ROM APIs
 * @defgroup xpi_interface XPI driver APIs
 * @{
 */

#include "hpm_common.h"

/**
 *  @brief XPI_Type definitions for
 *  @note For compatibility
 */
typedef uint32_t XPI_Type;

/**
 * @brief XPI Read Sample Clock source options
 */
typedef enum {
    xpi_rxclksrc_internal_loopback = 0, /**< Internal loopback */
    xpi_rxclksrc_dqs_loopback = 1,      /**< Loopback from DQS pad */
    xpi_rxclksrc_external_dqs = 3,      /**< Read is driven by External DQS pad */
} xpi_rxclksrc_type_t;


/**
 * @brief XPI pad definitions
 */
#define XPI_1PAD    (0U)    /**< Single pad */
#define XPI_2PADS   (1U)    /**< Dual pads */
#define XPI_4PADS   (2U)    /**< Quad pads */
#define XPI_8PADS   (3U)    /**< Octal pads */

/**
 * @brief XPI IO pin group options
 */
typedef enum {
    xpi_io_1st_group,       /**< First/Primary group */
    xpi_io_2nd_group,       /**< Second/Secondary group */
} xpi_io_group_t;

/**
 * @brief XPI Transfer Channel type definitions
 */
typedef enum {
    xpi_xfer_channel_a1,                    /**< The address is based on the device connected to Channel A1 */
    xpi_xfer_channel_a2,                    /**< The address is based on the device connected to Channel A2 */
    xpi_xfer_channel_b1,                    /**< The address is based on the device connected to Channel B1 */
    xpi_xfer_channel_b2,                    /**< The address is based on the device connected to Channel B2 */
    xpi_xfer_channel_auto,                  /**< The channel is auto determined */
} xpi_xfer_channel_t;

/**
 * @brief XPI Channel definitions
 */
typedef enum {
    xpi_channel_a1,        /**< Port:  Channel A1 */
    xpi_channel_a2,        /**< Port:  Channel A2 */
    xpi_channel_b1,        /**< Port:  Channel B1 */
    xpi_channel_b2,        /**< Port:  Channel B2 */
} xpi_channel_t;

/**
 * @brief XPI APB Transfer type
 */
typedef enum {
    xpi_apb_xfer_type_cmd,          /**< APB Command Type: Command only */
    xpi_apb_xfer_type_config,       /**< APB Command Type: Configuration */
    xpi_apb_xfer_type_read,         /**< APB Command Type: Read */
    xpi_apb_xfer_type_write,        /**< APB Command Type: Write */
} xpi_apb_xfer_type_t;

/**
 * @brief XPI Xfer Mode
 */
typedef enum {
    xpi_xfer_mode_polling,      /**< Transfer mode: Polling */
    xpi_xfer_mode_dma,          /**< Transfer mode: DMA */
    xpi_xfer_mode_interrupt,    /**< Transfer mode: Interrupt */
} xpi_xfer_mode_t;

/**
 * @brief XPI Xfer context
 */
typedef struct {
    uint32_t addr;          /**< device address for XPI transfer */
    uint8_t channel;           /**< channel for XPI transfer */
    uint8_t cmd_type;       /**< command type for XPI transfer */
    uint8_t seq_idx;        /**< Sequence index for XPI transfer */
    uint8_t seq_num;        /**< Sequence number for XPI transfer */
    uint32_t *buf;          /**< Buffer for XPI transfer */
    uint32_t xfer_size;     /**< Transfer size in bytes */
} xpi_xfer_ctx_t;

/**
 * @brief XPI instruction sequence
 */
typedef struct {
    uint32_t entry[4];
} xpi_instr_seq_t;

/**
 * @brief XPI Phase definitions
 */
#define XPI_PHASE_STOP            (0x00U)   /**< Phase: Stop */
#define XPI_PHASE_CMD_SDR         (0x01U)   /**< Phase: Send CMD in SDR mode */
#define XPI_PHASE_RADDR_SDR       (0x02U)   /**< Phase: Send Row Address in SDR Mode */
#define XPI_PHASE_CADDR_SDR       (0x03U)   /**< Phase: Send Column Address in SDR Mode */
#define XPI_PHASE_MODE4_SDR       (0x06U)   /**< Phase: Send Mode 4 in SDR Mode */
#define XPI_PHASE_MODE8_SDR       (0x07U)   /**< Phase: Send Mode 8 in SDR Mode */
#define XPI_PHASE_WRITE_SDR       (0x08U)   /**< Phase: Write data in SDR Mode */
#define XPI_PHASE_READ_SDR        (0x09U)   /**< Phase: Read data in SDR Mode */
#define XPI_PHASE_DUMMY_SDR       (0X0CU)   /**< Phase: Send Dummy in SDR Mode */
#define XPI_PHASE_DUMMY_RWDS_SDR  (0x0DU)   /**< Phase: Send Dummy RWDS  in SDR Mode */

#define XPI_PHASE_CMD_DDR         (0x21U)   /**< Phase: Send CMD in DDR Mode */
#define XPI_PHASE_RADDR_DDR       (0x22U)   /**< Phase: Send Raw Address in DDR Mode */
#define XPI_PHASE_CADDR_DDR       (0x23U)   /**< Phase: Send Column address in DDR Mode */
#define XPI_PHASE_MODE4_DDR       (0x26U)   /**< Phase: Send Mode 4 in DDR Mode */
#define XPI_PHASE_MODE8_DDR       (0x27U)   /**< Phase: Send Mode 8 in DDR Mode */
#define XPI_PHASE_WRITE_DDR       (0x28U)   /**< Phase: Write data in DDR Mode */
#define XPI_PHASE_READ_DDR        (0x29U)   /**< Phase: Read data in SDR Mode */
#define XPI_PHASE_DUMMY_DDR       (0x2CU)   /**< Phase: Send DUMMY in DDR Mode */
#define XPI_PHASE_DUMMY_RWDS_DDR  (0x2DU)   /**< Phase: Send DUMMY RWDS in DDR Mode */

/**
 * @brief XPI API command error codes
 */
enum {
    status_xpi_apb_jump_on_cs = MAKE_STATUS(status_group_xpi, 1),
    status_xpi_apb_unknown_inst = MAKE_STATUS(status_group_xpi, 2),
    status_xpi_apb_dummy_sdr_in_ddr_seq = MAKE_STATUS(status_group_xpi, 3),
    status_xpi_apb_dummy_ddr_in_sdr_seq = MAKE_STATUS(status_group_xpi, 4),
    status_xpi_apb_exceed_addr_range = MAKE_STATUS(status_group_xpi, 5),
    status_xpi_apb_seq_timeout = MAKE_STATUS(status_group_xpi, 6),
    status_xpi_apb_cross_boundary = MAKE_STATUS(status_group_xpi, 7),
};

/**
 * @brief Delay line definitions
 */
enum {
    xpi_dll_half_cycle = 0xFU,
    xpi_dll_quarter_cycle = 0x7U,
    xpi_dll_sdr_default_cycle = xpi_dll_half_cycle,
    xpi_dll_ddr_default_cycle = xpi_dll_quarter_cycle,
};

/**
 * @brief XPI configuration structure
 */
typedef struct {
    uint8_t rxclk_src;                      /**< Read sample clock source */
    uint8_t reserved0[7];                   /**< Reserved */
    uint8_t tx_watermark_in_dwords;         /**< Tx watermark in double words */
    uint8_t rx_watermark_in_dwords;         /**< Rx watermark in double words */
    uint8_t enable_differential_clk;        /**< Enable differential clock */
    uint8_t reserved1[5];                   /**< Reserved */
    uint32_t access_flags;                  /**< Access flags */
} xpi_config_t;

/**
 * @brief XPI Device Configuration structure
 */
typedef struct {
    uint32_t size_in_kbytes;                /**< Device size in kbytes */
    uint32_t serial_root_clk_freq;          /**< XPI serial root clock frequency */

    uint8_t enable_write_mask;              /**< Enable write mask, typically for PSRAM/HyperRAM */
    uint8_t data_valid_time;                /**< Data valid time, Unit 0.1ns */
    uint8_t reserved0[2];

    uint8_t cs_hold_time;                   /**< CS hold time, cycles in terms of FLASH clock */
    uint8_t cs_setup_time;                  /**< CS setup time, cycles in terms of FLASH clock */
    uint16_t cs_interval;                   /**< CS interval, cycles in terms of FLASH clock */

    uint8_t reserved1;
    uint8_t column_addr_size;               /**< Column address bits */
    uint8_t enable_word_address;            /**< Enable word address, for HyperFLASH/HyperRAM */
    uint8_t dly_target;                     /**< Delay target */

    uint8_t ahb_write_seq_idx;              /**< AHB write sequence index */
    uint8_t ahb_write_seq_num;              /**< AHB write sequence number */
    uint8_t ahb_read_seq_idx;               /**< AHB read sequence index */
    uint8_t ahb_read_seq_num;               /**< AHB read sequence number */

    uint8_t ahb_write_wait_interval;        /**< AHB write wait interval, in terms of FLASH clock */
    uint8_t reserved2[3];
} xpi_device_config_t;

/**
 * @brief SUB Instruction
 * @param [in] phase Phase
 * @param [in] pad  Pad for Phase
 * @param [in] op   Operand for Phase
 */
#define SUB_INSTR(phase, pad, op) ((uint32_t)(((uint16_t)(phase) << 10) | ((uint16_t)(pad) << 8) | ((uint16_t)(op))))
/**
 * @brief Generate a single word INSTRUCTION sequence word
 * @note  Here intentionally use the MACRO because when the arguments are constant value, the compiler
 *        can generate the const entry word during pre-processing
 */
#define XPI_INSTR_SEQ(phase0, pad0, op0, phase1, pad1, op1) (SUB_INSTR(phase0, pad0, op0) | (SUB_INSTR(phase1, pad1, op1)<<16))


/**
 * @}
 */

#endif /* HPM_ROMAPI_XPI_DEF_H */
