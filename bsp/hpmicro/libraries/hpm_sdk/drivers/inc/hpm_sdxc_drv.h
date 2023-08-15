/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_SDXC_DRV_H
#define HPM_SDXC_DRV_H

/**
 *
 * @brief SDXC driver APIs
 * @defgroup sdxc_interface SDXC driver APIs
 *  @ingroup sdxc_interfaces
 * @{
 *
 */

#include "hpm_common.h"
#include "hpm_sdxc_regs.h"
#include "hpm_sdxc_soc_drv.h"


/**
 * @brief Command Response Type Selection
 */
#define SDXC_CMD_RESP_TYPE_NO_RESP (0U)         /**< No Response */
#define SDXC_CMD_RESP_TYPE_RESP_LEN_136 (1U)    /**< Response Length 136 */
#define SDXC_CMD_RESP_TYPE_RESP_LEN_48 (2U)     /**< Response Length 48 */
#define SDXC_CMD_RESP_TYPE_RESP_LEN_48B (3U)    /**< Response Length 48; Check busy after response */


#define SDXC_STS_CMD_ERR (SDXC_INT_STAT_CMD_TOUT_ERR_MASK | SDXC_INT_STAT_CMD_CRC_ERR_MASK |\
            SDXC_INT_STAT_CMD_END_BIT_ERR_MASK | SDXC_INT_STAT_CMD_IDX_ERR_MASK | SDXC_INT_STAT_AUTO_CMD_ERR_MASK)
#define SDXC_STS_DATA_ERR (SDXC_INT_STAT_DATA_TOUT_ERR_MASK | SDXC_INT_STAT_DATA_CRC_ERR_MASK | \
            SDXC_INT_STAT_DATA_END_BIT_ERR_MASK)
#define SDXC_STS_CARD_ERR (SDXC_INT_STAT_CARD_REMOVAL_MASK)
#define SDXC_STS_ERROR (SDXC_INT_STAT_ERR_INTERRUPT_MASK | SDXC_STS_CMD_ERR | SDXC_STS_DATA_ERR | SDXC_STS_CARD_ERR)
#define SDXC_STS_CMD_FLAGS (SDXC_STS_CMD_ERR | SDXC_INT_STAT_CMD_COMPLETE_MASK)

#define SDXC_STS_ALL_FLAGS (SDXC_INT_STAT_ERR_INTERRUPT_MASK | SDXC_INT_STAT_CQE_EVENT_MASK | \
            SDXC_INT_STAT_FX_EVENT_MASK | SDXC_INT_STAT_RE_TUNE_EVENT_MASK | SDXC_INT_STAT_CARD_INTERRUPT_MASK | \
            SDXC_INT_STAT_CARD_REMOVAL_MASK | SDXC_INT_STAT_CARD_INSERTION_MASK | SDXC_INT_STAT_BUF_RD_READY_MASK | \
            SDXC_INT_STAT_BUF_WR_READY_MASK | SDXC_INT_STAT_DMA_INTERRUPT_MASK | SDXC_INT_STAT_BGAP_EVENT_MASK | \
            SDXC_INT_STAT_XFER_COMPLETE_MASK | SDXC_INT_STAT_CMD_COMPLETE_MASK | SDXC_INT_STAT_BOOT_ACK_ERR_MASK |  \
            SDXC_INT_STAT_RESP_ERR_MASK | SDXC_INT_STAT_TUNING_ERR_MASK | SDXC_INT_STAT_ADMA_ERR_MASK |   \
            SDXC_INT_STAT_AUTO_CMD_ERR_MASK | SDXC_INT_STAT_CUR_LMT_ERR_MASK | SDXC_INT_STAT_DATA_END_BIT_ERR_MASK |\
            SDXC_INT_STAT_DATA_CRC_ERR_MASK | SDXC_INT_STAT_DATA_TOUT_ERR_MASK | SDXC_INT_STAT_CMD_IDX_ERR_MASK |\
            SDXC_INT_STAT_CMD_END_BIT_ERR_MASK | SDXC_INT_STAT_CMD_CRC_ERR_MASK | SDXC_INT_STAT_CMD_TOUT_ERR_MASK)


/**
 * @brief Software reset flag definitions
 */
typedef enum _sdxc_software_reset {
    sdxc_reset_all,                 /**< Reset both command line and data line */
    sdxc_reset_cmd_line,            /**< Reset command line */
    sdxc_reset_data_line,           /**< Reset data line */
} sdxc_sw_reset_type_t;

/**
 * @brief SDXC Bus voltage options
 */
typedef enum _sdxc_bus_voltage_option {
    sdxc_bus_voltage_sd_1v8 = 0x01U,
    sdxc_bus_voltage_sd_3v3 = 0x00U,
    sdxc_bus_voltage_emmc_1v8 = 0x01U,
    sdxc_bus_voltage_emmc_3v3 = 0x00U,
} sdxc_bus_voltage_option_t;

/**
 * @brief SDXC wakeup events
 */
typedef enum _sdxc_wakeup_event {
    sdxc_wakeup_card_removal = 0x4U,        /**< Wake-up event: Card removal */
    sdxc_wakeup_card_insert = 0x02U,        /**< Wake-up event: Card insertion */
    sdxc_wakeup_card_interrupt = 0x01U,     /**< Wake-up event: Card interrupt */
} sdxc_wakeup_event_t;

/**
 * @brief SDXC DMA types
 */
typedef enum _sdxc_dma_type {
    sdxc_dmasel_sdma = 0U,          /**< SDXC DMA type: SDMA */
    sdxc_dmasel_adma2 = 2U,         /**< SDXC DMA type: ADMA2 */
    sdxc_dmasel_adma2_or_3 = 3U,    /**< SDXC DMA type: ADMA2 or ADMA3 */
    sdxc_dmasel_nodma = 0xFU,
} sdxc_dma_type_t;

/**
 * @brief SDXC Bus width options
 */
typedef enum _sdxc_bus_width {
    sdxc_bus_width_1bit,            /**< SDXC bus width: 1 bit */
    sdxc_bus_width_4bit,            /**< SDXC bus width: 4 bits */
    sdxc_bus_width_8bit,            /**< SDXC bus width: 8 bits */
} sdxc_bus_width_t;

/**
 * @brief SDXC Speed mode options
 */
typedef enum _sdxc_speed_mode {
    sdxc_sd_speed_sdr12 = 0U,                   /**< SDXC speed: SDR12 */
    sdxc_sd_speed_sdr25 = 1U,                   /**< SDXC speed: SDR25 */
    sdxc_sd_speed_sdr50 = 2U,                   /**< SDXC speed: SDR50 */
    sdxc_sd_speed_sdr104 = 3U,                  /**< SDXC speed: SDR104 */
    sdxc_sd_speed_ddr50 = 4U,                   /**< SDXC speed: DDR50 */
    sdxc_sd_speed_normal = sdxc_sd_speed_sdr12, /**< SDXC speed: Normal Speed */
    sdxc_sd_speed_high = sdxc_sd_speed_sdr25,   /**< SDXC speed: High Speed */

    sdxc_emmc_speed_legacy = 0U,                /**< SDXC speed: MMC legacy speed */
    sdxc_emmc_speed_high_speed_sdr = 1U,        /**< SDXC speed: MMC High Speed */
    sdxc_emmc_speed_hs200 = 3U,                 /**< SDXC speed: MMC HS200 speed */
    sdxc_emmc_speed_high_speed_ddr = 4U,        /**< SDXC speed: MMC High Speed DDR */
    sdxc_emmc_speed_hs400 = 7U,                 /**< SDXC speed: MMC HS400 */

    sdxc_sdmmc_speed_card_init = 0x10,

} sdxc_speed_mode_t;

/**
 * @brief SDXC auto command types
 */
typedef enum _sdxc_auto_cmd_sel {
    sdxc_auto_cmd_disabled = 0U,            /**< Auto Command type: Disabled */
    sdxc_auto_cmd12_enabled = 1U,           /**< Auto Command type: CMD12 enabled */
    sdxc_auto_cmd23_enabled = 2U,           /**< Auto Command type: CMD23 enabled */
    sdxc_auto_cmd_auto_select = 3U,         /**< Auto Command type: AUto selected */
} sdxc_auto_cmd_sel_t;

/**
 * @brief SDXC trnasfer direction options
 */
typedef enum _sdxc_xfer_direction {
    sdxc_xfer_dir_write,
    sdxc_xfer_dir_read,
} sdxc_xfer_direction_t;

/**
 * @brief SDXC Command types
 */
typedef enum _sdxc_command_type {
    sdxc_cmd_type_normal_cmd = 0U,
    sdxc_cmd_type_suspend_cmd,
    sdxc_cmd_tye_resume_cmd,
    sdxc_cmd_type_abort_cmd,
    sdxc_cmd_type_empty,

} sdxc_command_type_t;

/**
 * @brief Command Type
 */
#define SDXC_CMD_TYPE_NORMAL (0UL << SDXC_CMD_XFER_CMD_TYPE_SHIFT)
#define SDXC_CMD_TYPE_SUSPEND (1UL << SDXC_CMD_XFER_CMD_TYPE_SHIFT)
#define SDXC_CMD_TYPE_RESUME (2UL << SDXC_CMD_XFER_CMD_TYPE_SHIFT)
#define SDXC_CMD_TYPE_ABORT (3UL << SDXC_CMD_XFER_CMD_TYPE_SHIFT)

/**
 * @brief SDXC boot mode types
 */
typedef enum _sdxc_boot_mode {
    sdxc_boot_mode_normal = 0,
    sdxc_boot_mode_alternative
} sdxc_boot_mode_t;

/**
 * @brief SDXC response types
 */
typedef enum _sdxc_response_type {
    sdxc_response_type_no_resp,
    sdxc_response_type_resp_len_136bit,
    sdxc_response_type_resp_len_48bit,
    sdxc_response_type_resp_len_48bit_check_busy,
} sdxc_response_type_t;

#define SDXC_CMD_RESP_NO_RESPONSE (0UL << SDXC_CMD_XFER_RESP_TYPE_SELECT_SHIFT)
#define SDXC_CMD_RESP_LEN_136 (1UL << SDXC_CMD_XFER_RESP_TYPE_SELECT_SHIFT)
#define SDXC_CMD_RESP_LEN_48 (2UL << SDXC_CMD_XFER_RESP_TYPE_SELECT_SHIFT)
#define SDXC_CMD_RESP_LEN_48B (3UL << SDXC_CMD_XFER_RESP_TYPE_SELECT_SHIFT)

#define SDXC_CMD_CMD_IS_MAIN_CMD (0U)
#define SDXC_CMD_CMD_IS_SUB_CMD (SDXC_CMD_XFER_SUB_CMD_FLAG_MASK)

#define SDXC_CMD_CMD_CRC_CHK_EN (SDXC_CMD_XFER_CMD_CRC_CHK_ENABLE_MASK)
#define SDXC_CMD_CMD_CRC_CHK_DIS (0U)

#define SDXC_CMD_CMD_IDX_CHK_EN (SDXC_CMD_XFER_CMD_IDX_CHK_ENABLE_MASK)
#define SDXC_CMD_CMD_IDX_CHK_DIS (0U)

#define SDXC_CMD_DATA_PRESENT (SDXC_CMD_XFER_DATA_PRESENT_SEL_MASK)
#define SDXC_CMD_DATA_NO_PRESENT (0U)

#define SDXC_CMD_CMD_TYPE_NORMAL (0U)
#define SDXC_CMD_CMD_TYPE_SUSPEND (1UL << SDXC_CMD_XFER_CMD_TYPE_SHIFT)
#define SDXC_CMD_CMD_TYPE_RESUME (2U << SDXC_CMD_XFER_CMD_TYPE_SHIFT)
#define SDXC_CMD_CMD_TYPE_ABORT (3U << SDXC_CMD_XFER_CMD_TYPE_SHIFT)

/**
 * @brief SDXC error codes
 */
enum {
    status_sdxc_busy = MAKE_STATUS(status_group_sdxc, 0),                               /**< SDXC is busy */
    status_sdxc_error = MAKE_STATUS(status_group_sdxc, 1),                              /**< SDXC error */
    status_sdxc_send_cmd_failed = MAKE_STATUS(status_group_sdxc, 2),                    /**< SDXC command failed */
    status_sdxc_cmd_timeout_error = MAKE_STATUS(status_group_sdxc, 3),                  /**< SDXC command timed out */
    status_sdxc_cmd_crc_error = MAKE_STATUS(status_group_sdxc, 4),                      /**< SDXC command CRC error */
    status_sdxc_cmd_end_bit_error = MAKE_STATUS(status_group_sdxc, 5),                  /**< SDXC command end bit error */
    status_sdxc_cmd_index_error = MAKE_STATUS(status_group_sdxc, 6),                    /**< SDXC command index error */
    status_sdxc_data_timeout_error = MAKE_STATUS(status_group_sdxc, 7),                 /**< SDXC data timeout error */
    status_sdxc_data_crc_error = MAKE_STATUS(status_group_sdxc, 8),                     /**< SDXC data CRC error */
    status_sdxc_data_end_bit_error = MAKE_STATUS(status_group_sdxc, 9),                 /**< SDXC data end bit error */
    status_sdxc_auto_cmd_error = MAKE_STATUS(status_group_sdxc, 10),                    /**< SDXC auto command error */
    status_sdxc_adma_error = MAKE_STATUS(status_group_sdxc, 11),                        /**< SDXC ADMA error */
    status_sdxc_tuning_error = MAKE_STATUS(status_group_sdxc, 12),                      /**< SDXC tuning error */
    status_sdxc_response_error = MAKE_STATUS(status_group_sdxc, 13),                    /**< SDXC response error */
    status_sdxc_boot_ack_error = MAKE_STATUS(status_group_sdxc, 14),                    /**< SDXC boot ack error */
    status_sdxc_retuning_request = MAKE_STATUS(status_group_sdxc, 15),                  /**< SDXC retuning request */
    status_sdxc_autocmd_cmd12_not_exec = MAKE_STATUS(status_group_sdxc, 16),            /**< SDXC Auto CMD12 command not executed */
    status_sdxc_autocmd_cmd_timeout_error = MAKE_STATUS(status_group_sdxc, 17),         /**< SDXC Auto CMD timed out */
    status_sdxc_autocmd_cmd_crc_error = MAKE_STATUS(status_group_sdxc, 18),             /**< SDXC Auto CMD crc error */
    status_sdxc_autocmd_end_bit_error = MAKE_STATUS(status_group_sdxc, 19),             /**< SDXC Auto CMD end bit error */
    status_sdxc_autocmd_cmd_index_error = MAKE_STATUS(status_group_sdxc, 20),           /**< SDXC Auto CMD index error */
    status_sdxc_autocmd_cmd_response_error = MAKE_STATUS(status_group_sdxc, 21),        /**< SDXC Auto CMD response error */
    status_sdxc_autocmd_cmd_not_issued_auto_cmd12 = MAKE_STATUS(status_group_sdxc, 22), /**< SDXC Auto CMD not issued auto CMD12 */
    status_sdxc_unsupported = MAKE_STATUS(status_group_sdxc, 23),                       /**< SDXC unsupported operation */
    status_sdxc_transfer_data_completed = MAKE_STATUS(status_group_sdxc, 24),           /**< SDXC transfer data completed */
    status_sdxc_send_cmd_successful = MAKE_STATUS(status_group_sdxc, 25),               /**< SDXC send command succedded */
    status_sdxc_transfer_dma_completed = MAKE_STATUS(status_group_sdxc, 26),            /**< SDXC transfer DMA completed */
    status_sdxc_transfer_data_failed = MAKE_STATUS(status_group_sdxc, 27),              /**< SDXC transfer data failed */
    status_sdxc_dma_addr_unaligned = MAKE_STATUS(status_group_sdxc, 28),                /**< SDXC DMA address unaligned */
    status_sdxc_tuning_failed = MAKE_STATUS(status_group_sdxc, 29),                     /**< SDXC tuning failed */
    status_sdxc_card_removed = MAKE_STATUS(status_group_sdxc, 30),                      /**< SDXC Card removed */
    status_sdxc_non_recoverable_error = MAKE_STATUS(status_group_sdxc, 30),             /**< SDXC non-recoverable error */
    status_sdxc_recoverable_error = MAKE_STATUS(status_group_sdxc, 31),                 /**< SDXC recoverable error */
};

/**
 * @brief SDXC Capacities
 */
typedef struct {
    union {
        struct {
            uint32_t tout_clk_freq: 6;                  /**< Timeout clock frequency */
            uint32_t : 1;
            uint32_t tout_clk_unit: 1;                  /**< Timeout clock unit */
            uint32_t base_clk_freq: 8;                  /**< Base clock frequency */
            uint32_t max_blk_len: 2;                    /**< Maximum Block length */
            uint32_t embedded_8_bit_support: 1;         /**< Embedded 8-bit support */
            uint32_t adma2_support: 1;                  /**< ADMA2 support */
            uint32_t : 1;
            uint32_t high_speed_support: 1;             /**< High speed support */
            uint32_t sdma_support: 1;                   /**< SDMA support */
            uint32_t suspend_resume_support: 1;         /**< Suspend resume support */
            uint32_t voltage_3v3_support: 1;            /**< 3.3v support */
            uint32_t voltage_3v0_support: 1;            /**< 3.0v support */
            uint32_t voltage_1v8_support: 1;            /**< 1.8v support */
            uint32_t sys_addr_64_bit_v4_support: 1;     /**< SD Host Version 4 support */
            uint32_t sys_addr_64_bit_v3_support: 1;     /**< SD Host Version 3 support */
            uint32_t asysnc_interrupt_support: 1;       /**< Asynchronous interrupt support */
            uint32_t slot_type_r: 2;                    /**< Slot type */
        };
        uint32_t U;
    } capabilities1;

    union {
        struct {
            uint32_t sdr50_support: 1;                  /**< SDR50 support */
            uint32_t sdr104_support: 1;                 /**< SDR104 support */
            uint32_t ddr50_support: 1;                  /**< DDR50 support */
            uint32_t uhs2_support: 1;                   /**< UHS2 support */
            uint32_t drv_type_a: 1;                     /**< Drive TypeA support */
            uint32_t drv_type_c: 1;                     /**< Drive TypeC support */
            uint32_t drv_type_d: 1;                     /**< Drive TypeD support */
            uint32_t reserved0: 1;
            uint32_t retune_cnt: 4;                     /**< Retune count support */
            uint32_t : 1;
            uint32_t use_tuning_sdr50: 1;               /**< Use tuning sdr50 support */
            uint32_t re_tuning_modes: 2;                /**< Retune modes */
            uint32_t clk_mul: 8;                        /**< Clock multiplier */
            uint32_t : 3;
            uint32_t adma3_support: 1;                  /**< ADMA3 support */
            uint32_t vdd2_1v8_support: 1;               /**< VDD2 1v8 support */
            uint32_t : 3;
        };
        uint32_t U;
    } capabilities2;

    union {
        struct {
            uint32_t max_current_3v3: 8;            /**< Maximum current at 3.3V */
            uint32_t max_current_3v0: 8;            /**< Maximum current at 3.0V */
            uint32_t max_current_1v8: 8;            /**< Maximum current at 1.8V */
            uint32_t reserved: 8;
        };
        uint32_t U;
    } curr_capabilities1;

    union {
        struct {
            uint32_t max_current_vdd2_1v8: 8;      /**< Maximum current at VDD2 1.8V */
            uint32_t reserved: 24;
        };
        uint32_t U;
    } curr_capabilities2;

} sdxc_capabilities_t;

/**
 * @brief SDXC Device response type
 */
typedef enum _sdxc_dev_resp_type {
    sdxc_dev_resp_none = 0,
    sdxc_dev_resp_r1,
    sdxc_dev_resp_r1b,
    sdxc_dev_resp_r2,
    sdxc_dev_resp_r3,
    sdxc_dev_resp_r4,
    sdxc_dev_resp_r5,
    sdxc_dev_resp_r5b,
    sdxc_dev_resp_r6,
    sdxc_dev_resp_r7,
} sdxc_dev_resp_type_t;

/**
 * @brief SDXC command structure
 */
typedef struct _sdxc_command {
    uint32_t cmd_index;                     /**< Command index */
    uint32_t cmd_argument;                  /**< Command argument */
    uint32_t cmd_flags;                     /**< Command flags */
    sdxc_command_type_t cmd_type;           /**< Command type */
    sdxc_dev_resp_type_t resp_type;         /**< Command response type */
    uint32_t resp_error_flags;              /**< Command response error flags */
    uint32_t response[4];                   /**< Response buffer */
    uint32_t auto_cmd_resp;                 /**< Auto command response */
    uint32_t cmd_timeout_ms;                /**< Command Timeout in ms, 0 - means use default short timeout */
} sdxc_command_t;

/**
 * @brief SDXC data list
 */
typedef struct _sdxc_data_list {
    uint32_t *data_addr;
    uint32_t data_size;
    struct _sdxc_data_list *data_list;
} sdxc_data_list_t;

/**
 * @brief SDXC data structure
 */
typedef struct _sdxc_data {
    bool enable_auto_cmd12;
    bool enable_auto_cmd23;
    bool enable_ignore_error;
    uint8_t data_type;
    uint32_t block_size;
    uint32_t block_cnt;
    uint32_t *rx_data;
    const uint32_t *tx_data;
} sdxc_data_t;

/**
 * @brief SDXC transfer data type
 */
enum {
    sdxc_xfer_data_normal = 0U,         /**< Transfer normal read/write data */
    sdxc_xfer_data_boot = 1U,           /**< Transfer boot data */
    sdxc_xfer_data_boot_continuous = 2U, /**< Transfer boot data continuously */
};

/**
 * @brief SDXC transfer context
 */
typedef struct _sdxc_xfer {
    sdxc_data_t *data;
    sdxc_command_t *command;
} sdxc_xfer_t;

/**
 * @brief SDXC ADMA configuration
 */
typedef struct _sdxc_adma_config {
    sdxc_dma_type_t dma_type;
    uint32_t *adma_table;
    uint32_t adma_table_words;
} sdxc_adma_config_t;

enum {
    sdxc_adma_desc_single_flag = 0U,
    sdxc_adma_desc_multi_flag = 1U,
};

/**
 * @brief SDXC configuration
 */
typedef struct _sdxc_config {
    uint32_t data_timeout; /**< Data timeout in milliseconds */
} sdxc_config_t;

/**
 * @brief SDXC ADMA2 descriptor
 */
typedef struct _sdxc_adma2_descriptor {
    union {
        struct {
            uint32_t valid: 1;          /**< Valid flag */
            uint32_t end: 1;            /**< End flag */
            uint32_t interrupt: 1;      /**< Interrupt flag */
            uint32_t act: 3;            /**<Act mode */
            uint32_t len_upper: 10;     /**< Length upper 10-bit */
            uint32_t len_lower: 16;     /**< Length lower 16-bit */
        };
        uint32_t len_attr;
    };
    const uint32_t *addr;              /**< Data Address */
} sdxc_adma2_descriptor_t;

#define SDXC_ADMA2_DESC_VALID_FLAG (1UL << 0)
#define SDXC_ADMA2_DESC_END_FLAG (1UL << 1)
#define SDXC_ADMA2_DESC_INTERRUPT_FLAG (1UL << 2)
#define SDXC_ADMA2_DESC_ACT0_FLAG (1UL << 3)
#define SDXC_ADMA2_DESC_ACT1_FLAG (1UL << 4)
#define SDXC_ADMA2_DESC_ACT2_FLAG (1UL << 5)

#define SDXC_ADMA2_ADDR_LEN (4U)
#define SDXC_ADMA2_LEN_ALIGN (4U)

#define SDXC_ADMA2_DESC_TYPE_NOP (0U)
#define SDXC_ADMA2_DESC_TYPE_TRANS (4U)
#define SDXC_ADMA2_DESC_TYPE_LINK (6U)
#define SDXC_ADMA3_DESC_TYPE_FOR_SD_MODE (0x1U)
#define SDXC_AMDA3_DESC_TYPE_INTEGRATED_LINKER (7U)

#define SDXC_ADMA3_CMD_FOR_SD_DESC_ATTR (0x09U)
#define SDXC_ADMA3_INTEGRATED_DESC_ATTR (0x39U)

#define SDXC_ADMA3_CMD_DESC_IDX_32BIT_BLK_CNT (0U)
#define SDXC_ADMA3_CMD_DESC_IDX_BLK_SIZE (1U)
#define SDXC_ADMA3_CMD_DESC_IDX_ARG (2U)
#define SDXC_ADMA3_CMD_DESC_IDX_CMD_XFER (3U)

/**
 * @brief ADMA3 command descriptor
 */
typedef struct _sdxc_adma3_cmd_sd_desc {
    struct {
        uint32_t attr;
        uint32_t data;
    } entry[4];
} sdxc_adma3_cmd_sd_desc_t;

/**
 * @brief SDXC ADMA3 Integrated Descriptor
 */
typedef struct _sdxc_adma3_integrated_desc {
    uint32_t attr;
    sdxc_adma3_cmd_sd_desc_t *cmd_desc_ptr;
} sdxc_adma3_integrated_desc_t;

/**
 * @brief SDXC Boot confituration
 */
typedef struct _sdxc_boot_config {
    uint32_t ack_timeout_cnt;
    sdxc_boot_mode_t boot_mode;
    uint32_t block_cnt;
    uint32_t block_size;
    bool enable_boot_ack;
    bool enable_auto_stop_at_block_gap;
} sdxc_boot_config_t;


#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @brief Get the SDXC interrupt status
 * @param [in] base SDXC base address
 * @retval SDXC inaterrupt status
 */
static inline uint32_t sdxc_get_interrupt_status(SDXC_Type *base)
{
    return base->INT_STAT;
}

/**
 * @brief Check whether SD card is inserted
 * @retval SD Card instertion status
 *  @arg true SD Card is inserted
 *  @arg false SD card is not inserted
 */
static inline bool sdxc_is_card_inserted(SDXC_Type *base)
{
    return IS_HPM_BITMASK_SET(base->PSTATE, SDXC_PSTATE_CARD_INSERTED_MASK);
}

/**
 * @brief Clear SDXC interrupt status
 * @param [in] base SDXC base address
 * @param [in] status_mask the status mask to be cleared
 */
static inline void sdxc_clear_interrupt_status(SDXC_Type *base, uint32_t status_mask)
{
    base->INT_STAT = status_mask;
}

/**
 * @brief Enable SDXC interrupt status
 * @param [in] base SDXC base address
 * @param [in] mask SDXC interrupt status mask
 * @param [in] enable Interrupt status enable flag
 */
static inline void sdxc_enable_interrupt_status(SDXC_Type *base, uint32_t mask, bool enable)
{
    if (enable) {
        base->INT_STAT_EN |= mask;
    } else {
        base->INT_STAT_EN &= ~mask;
    }
}

/**
 * @brief Enable SDXC interrupt signal
 * @param [in] base SDXC base address
 * @param [in] mask SDXC interrupt signal mask
 * @param [in] enable Interrupt signal enable flag
 */
static inline void sdxc_enable_interrupt_signal(SDXC_Type *base, uint32_t mask, bool enable)
{
    if (enable) {
        base->INT_SIGNAL_EN |= mask;
    } else {
        base->INT_SIGNAL_EN &= ~mask;
    }
}

/**
 * @brief Get SDXC capabilities
 * @param [in] base SDXC base address
 * @param [out] capabilities buffer
 */
hpm_stat_t sdxc_get_capabilities(SDXC_Type *base, sdxc_capabilities_t *capabilities);


/**
 * @brief Get SDXC ADMA error status
 * @param [in] base SDXC base address
 * @retval AMDA error status register value
 */
static inline uint8_t sdxc_get_adma_error_status(SDXC_Type *base)
{
    return base->ADMA_ERR_STAT;
}

/**
 * @brief Configure SDXC data timeout interal
 * @param [in] base SDXC base address
 * @param [in] timeout SDXC data timeout option
 */
static inline void sdxc_configure_data_timeout(SDXC_Type *base, uint8_t timeout)
{
    base->SYS_CTRL = (base->SYS_CTRL & ~SDXC_SYS_CTRL_TOUT_CNT_MASK) | SDXC_SYS_CTRL_TOUT_CNT_SET(timeout);
}

/**
 * @brief Configure SDXC interrupt at block gap
 * @param [in] base SDXC base address
 * @param [in] enable Enable Interrupt_at_Block_Gap flag
 */
static inline void sdxc_interrupt_at_block_gap(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->PROT_CTRL |= SDXC_PROT_CTRL_INT_AT_BGAP_MASK;
    } else {
        base->PROT_CTRL &= ~SDXC_PROT_CTRL_INT_AT_BGAP_MASK;
    }
}

/**
 * @brief Enable or Disable SDXC Read Wait
 * @param [in] base SDXC base address
 * @param [in] enable Enable SDXC Read Wait flag
 */
static inline void sdxc_read_wait_control(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->PROT_CTRL |= SDXC_PROT_CTRL_RD_WAIT_CTRL_MASK;
    } else {
        base->PROT_CTRL &= ~SDXC_PROT_CTRL_RD_WAIT_CTRL_MASK;
    }
}

/**
 * @brief Configure SDXC continue request
 * @param [in] base SDXC base address
 * @param [in] enable Flag to enable/disable SDXC continue request
 */
static inline void sdxc_continue_request(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->PROT_CTRL |= SDXC_PROT_CTRL_CONTINUE_REQ_MASK;
    } else {
        base->PROT_CTRL &= ~SDXC_PROT_CTRL_CONTINUE_REQ_MASK;
    }
}

/**
 * @brief Configure SDXC StopAtBlockGap request
 * @param [in] base SDXC base address
 * @param [in] enable Flag to enable/disable StopAtBlockGap request
 */
static inline void sdxc_stop_at_block_gap_request(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->PROT_CTRL |= SDXC_PROT_CTRL_STOP_BG_REQ_MASK;
    } else {
        base->PROT_CTRL &= ~SDXC_PROT_CTRL_STOP_BG_REQ_MASK;
    }
}

/**
 * @brief Control the SDXC high-speed support
 * @param [in] base SDXC base address
 * @param [in] enable flag to Enable/disable SDXC high-speed support
 */
static inline void sdxc_enable_high_speed(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->PROT_CTRL |= SDXC_PROT_CTRL_HIGH_SPEED_EN_MASK;
    } else {
        base->PROT_CTRL &= ~SDXC_PROT_CTRL_HIGH_SPEED_EN_MASK;
    }
}

/**
 * @brief Enable SDXC asynchronous interrupt support
 * @param [in] base SDXC base address
 * @param [in] enable Flag to enable/disable SDXC asynchronous interrupt support
 */
static inline void sdxc_enable_async_interrupt(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->AC_HOST_CTRL |= SDXC_AC_HOST_CTRL_ASYNC_INT_ENABLE_MASK;
    } else {
        base->AC_HOST_CTRL &= ~SDXC_AC_HOST_CTRL_ASYNC_INT_ENABLE_MASK;
    }
}

/**
 * @brief Enable SDXC Preset support
 * @param [in] base SDXC base address
 * @param [in] enable flag to enable/disable SDXC Preset support
 */
static inline void sdxc_enable_preset(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->AC_HOST_CTRL |= SDXC_AC_HOST_CTRL_PRESET_VAL_ENABLE_MASK;
    } else {
        base->AC_HOST_CTRL &= ~SDXC_AC_HOST_CTRL_PRESET_VAL_ENABLE_MASK;
    }
}

/**
 * @brief Enable SD Host version 4
 * @param [in] base SDXC base address
 * @param [in] enable flag to enable/disable SD Host version 4 support
 */
static inline void sdxc_enable_host_version4(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->AC_HOST_CTRL |= SDXC_AC_HOST_CTRL_HOST_VER4_ENABLE_MASK;
    } else {
        base->AC_HOST_CTRL &= ~SDXC_AC_HOST_CTRL_HOST_VER4_ENABLE_MASK;
    }
}

/**
 * @brief Start SDXC tuning process
 * @param [in] base SDXC base address
 */
static inline void sdxc_execute_tuning(SDXC_Type *base)
{
    base->AC_HOST_CTRL |= SDXC_AC_HOST_CTRL_EXEC_TUNING_MASK | SDXC_AC_HOST_CTRL_SAMPLE_CLK_SEL_MASK;
}

/**
 * @brief Enable SDXC software tuning process
 * @param [in] base SDXC base address
 * @param [in] enable flag to enable/disable SDXC software tuning
 */
static inline void sdxc_enable_software_tuning(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->AUTO_TUNING_CTRL |= SDXC_AUTO_TUNING_CTRL_SW_TUNE_EN_MASK;
    } else {
        base->AUTO_TUNING_CTRL &= ~SDXC_AUTO_TUNING_CTRL_SW_TUNE_EN_MASK;
    }
}

/**
 * @brief Reset SDXC tuning engine
 * @param [in] base SDXC base address
 */
static inline void sdxc_reset_tuning_engine(SDXC_Type *base)
{
    base->AC_HOST_CTRL &= ~SDXC_AC_HOST_CTRL_SAMPLE_CLK_SEL_MASK;
}

/**
 * @brief Switch SDXC to 1.8V signaling mode
 * @param [in] base SDXC base address
 * @param [in] enable Flag to switch to 1.8v signaling mode/stay at 3.0v signaling mode
 */
static inline void sdxc_switch_to_1v8_signal(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->AC_HOST_CTRL |= SDXC_AC_HOST_CTRL_SIGNALING_EN_MASK;
    } else {
        base->AC_HOST_CTRL &= ~SDXC_AC_HOST_CTRL_SIGNALING_EN_MASK;
    }
}

/**
 * @brief Enable/Disable SDXC internal clock
 * @param[in] base SDXC base address
 * @param [in] enable Flag to enable/disable SDXC internal clock
 */
static inline void sdxc_enable_internal_clock(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->SYS_CTRL |= SDXC_SYS_CTRL_INTERNAL_CLK_EN_MASK;
    } else {
        base->SYS_CTRL &= ~SDXC_SYS_CTRL_INTERNAL_CLK_EN_MASK;
    }
}

/**
 * @brief Get Present status register value
 * @param [in] base SDXC base address
 * @retval SDXC PRESENT register value
 */
static inline uint32_t sdxc_get_present_status(SDXC_Type *base)
{
    return base->PSTATE;
}

/**
 * @brief Check whether the Data Buffer is writable or not
 * @param [in] base SDXC base address
 * @retval true Data buffer is writeable
 * @retval false Data buffer write is disabled
 */
static inline bool sdxc_is_data_buf_writable(SDXC_Type *base)
{
    return ((base->PSTATE & SDXC_PSTATE_BUF_WR_ENABLE_MASK) != 0U);
}

/**
 * @brief Check whether the data buffer is readable
 * @param [in] base SDXC base address
 * @retval true There are data available in data buffer
 * @retval false there is no data available in data buffer, read is disabled
 */
static inline bool sdxc_is_data_buf_readable(SDXC_Type *base)
{
    return ((base->PSTATE & SDXC_PSTATE_BUF_RD_ENABLE_MASK) != 0U);
}

/**
 * @brief Read data from SDXC using non-DMA mode
 * @param [in] base SDXC base address
 * @retval Data read from SDXC
 */
static inline uint32_t sdxc_read_data(SDXC_Type *base)
{
    return base->BUF_DATA;
}

/**
 * @brief Write data to SDXC using non-DMA mode
 * @param [in] base SDXC base address
 * @param [in] data Data to be written to SDXC
 */
static inline void sdxc_write_data(SDXC_Type *base, uint32_t data)
{
    base->BUF_DATA = data;
}

/**
 * @brief Get SDXC DATA3-DATA0 IO level
 * @param [in] base SDXC base address
 * @retval SDXC data3-data0 IO level
 */
static inline uint32_t sdxc_get_data3_0_level(SDXC_Type *base)
{
    return SDXC_PSTATE_DAT_3_0_GET(base->PSTATE);
}

/**
 * @brief Enable SDXC auto tuning
 * @param [in] base SDXC base address
 * @param [in] enable Flag to enable/disable SDXC auto tuning
 */
static inline void sdxc_enable_auto_tuning(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->AUTO_TUNING_CTRL |= SDXC_AUTO_TUNING_CTRL_AT_EN_MASK;
    } else {
        base->AUTO_TUNING_CTRL &= ~SDXC_AUTO_TUNING_CTRL_AT_EN_MASK;
    }
}

/**
 * @brief Enable/Disable SDXC MMC boot
 * @param [in] base SDXC base address
 * @param [in] enable FLag to enable/disable SDXC MMC boot
 */
static inline void sdxc_enable_mmc_boot(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->EMMC_BOOT_CTRL |= SDXC_EMMC_BOOT_CTRL_MAN_BOOT_EN_MASK;
    } else {
        base->EMMC_BOOT_CTRL &= ~SDXC_EMMC_BOOT_CTRL_MAN_BOOT_EN_MASK;
    }
}

/**
 * @brief Set SDXC force event
 * @param [in] base SDXC base address
 * @param [in] mask SDXC event mask
 */
static inline void sdxc_force_event(SDXC_Type *base, uint32_t mask)
{
    base->FORCE_EVENT = mask;
}

/**
 * @brief Enable/disable SDXC SD clock output
 * @param [in] base SDXC base address
 * @param [in] enable Flag to enable/disable SDXC SD clock output
 */
static inline void sdxc_enable_sd_clock(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->SYS_CTRL |= SDXC_SYS_CTRL_SD_CLK_EN_MASK;
        while (!IS_HPM_BITMASK_SET(base->SYS_CTRL, SDXC_SYS_CTRL_SD_CLK_EN_MASK)) {
        }
    } else {
        base->SYS_CTRL &= ~SDXC_SYS_CTRL_SD_CLK_EN_MASK;
        while (IS_HPM_BITMASK_SET(base->SYS_CTRL, SDXC_SYS_CTRL_SD_CLK_EN_MASK)) {
        }
    }
}

/**
 * @brief Set SDXC center phase code
 * @param [in] base SDXC base address
 * @param [in] value SDXC center phase value
 */
static inline void sdxc_set_center_phase_code(SDXC_Type *base, uint32_t value)
{
    base->AUTO_TUNING_STAT = (base->AUTO_TUNING_STAT & ~SDXC_AUTO_TUNING_STAT_CENTER_PH_CODE_MASK) |
                             SDXC_AUTO_TUNING_STAT_CENTER_PH_CODE_SET(value);
}

/**
 * @brief Enable SDXC enhanced strobe
 * @param [in] base SDXC base address
 * @param [in] enable flag to enable/disable SSDXC enhanced strobe
 */
static inline void sdxc_enable_enhanced_strobe(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->EMMC_BOOT_CTRL |= SDXC_EMMC_BOOT_CTRL_ENH_STROBE_ENABLE_MASK;
    } else {
        base->EMMC_BOOT_CTRL &= ~SDXC_EMMC_BOOT_CTRL_ENH_STROBE_ENABLE_MASK;
    }
}

/**
 * @brief Set MMC boot configuration
 * @param [in] base SDXC base address
 * @param [in] config MMC boot configuration
 */
void sdxc_set_mmc_boot_config(SDXC_Type *base, const sdxc_boot_config_t *config);

/**
 * @brief Send Command via SDXC
 * @param [in] base SDXC base address
 * @param [in] cmd Command
 * @retval status_timeout Sending command timed out
 * @retval status_success Command was sent out successfully
 */
hpm_stat_t sdxc_send_command(SDXC_Type *base, sdxc_command_t *cmd);

/**
 * @brief Receive command response
 * @param [in] base SDXC base address
 * @param [in/out] cmd Command
 * @return status_success if no error happened
 */
hpm_stat_t sdxc_receive_cmd_response(SDXC_Type *base, sdxc_command_t *cmd);

/**
 * @brief Parse the SDXC interrupt status to HPM encoded status
 * @param [in] base SDXC base status
 * @return status_success if no error happened
 */
hpm_stat_t sdxc_parse_interrupt_status(SDXC_Type *base);

/**
 * @brief Wait until SDXC command completes
 * @param [in] base SDXC base address
 * @param [in] cmd Command
 * @param [out] polling_cmd_done flag to determine whether to use blocking wait
 * @retval SDXC command execution status
 */
hpm_stat_t sdxc_wait_cmd_done(SDXC_Type *base, sdxc_command_t *cmd, bool polling_cmd_done);

/**
 * @brief Set Data transfer configuration
 * @param [in] base SDXC base address
 * @param [in] data_dir Data transfer direction
 * @param [in] block_cnt Block count for data transfer
 * @param [in] block_size Block size for data transfer
 */
void sdxc_set_data_config(SDXC_Type *base, sdxc_xfer_direction_t data_dir, uint32_t block_cnt, uint32_t block_size);

/**
 * @brief Set ADMA table configuration
 * @param [in] base SDXC base address
 * @param [in] dma_cfg DMA configuration
 * @param [in] data_cfg Data configuration
 * @param [in] flags Flags for AMDA transfer
 * @retval API execution status
 */
hpm_stat_t sdxc_set_adma_table_config(SDXC_Type *base, sdxc_adma_config_t *dma_cfg,
                                      sdxc_data_t *data_cfg, uint32_t flags);

/**
 * @brief Set ADMA2 descriptor
 * @param [in] adma_tbl ADMA2 table
 * @param [in] adma_table_words ADMA2 table size in words
 * @param [in] data_buf pointer to the Data to be trnasferred
 * @param [in] data_bytes Data size for transfer
 * @param [in] flags Flags for ADMA2 descriptor
 * @retval API execution status
 */
hpm_stat_t sdxc_set_adma2_desc(uint32_t *adma_tbl, uint32_t adma_table_words, const uint32_t *data_buf,
                               uint32_t data_bytes, uint32_t flags);

/**
 * @brief Set DMA configuration
 * @param [in] base SDXC base address
 * @param [in] dma_cfg DMA configuration data structure
 * @param [in] data_addr Buffer holds incoming/outgoing data
 * @param [in] enable_auto_cmd23 Flag to determine whether to enable auto CMD23 or not
 * @retval API execution status
 */
hpm_stat_t sdxc_set_dma_config(SDXC_Type *base, sdxc_adma_config_t *dma_cfg, const uint32_t *data_addr,
                               bool enable_auto_cmd23);

/**
 * @brief Initialize SDXC controller
 * @param [in] base SDXC base address
 * @param [in] config SDXC configuration
 */
void sdxc_init(SDXC_Type *base, const sdxc_config_t *config);

/**
 * @brief Set the Data Timeout Counter value for an SD/eMMC device
 * @param [in] base SDXC base address
 * @param [in] timeout_in_ms Required timeout value in milliseconds, maximum value is 131,072ms
 * @param [out] actual_timeout_us Actual timeout in milliseconds, reported by this API
 */
void sdxc_set_data_timeout(SDXC_Type *base, uint32_t timeout_in_ms, uint32_t *actual_timeout_ms);

/**
 * @brief Set SDXC speed mode
 * @param [in] base SDXC base address
 * @param [in] mode SDXC speed mode option
 */
void sdxc_set_speed_mode(SDXC_Type *base, sdxc_speed_mode_t mode);


/**
 * @brief Set SDXC Data bus width
 * @param [in] base SDXC base address
 * @param [in] width SDXC bus width option
 */
void sdxc_set_data_bus_width(SDXC_Type *base, sdxc_bus_width_t width);

/**
 * @brief Get SDXC Data bus width
 * @param [in] base SDXC base address
 * @return Actual bus width, valid value: 1 / 4 / 8
 */
uint32_t sdxc_get_data_bus_width(SDXC_Type *base);

/**
 * @brief Set SDXC IO voltage
 * @param [in] base SDXC base address
 * @param [option] SDXC voltage option
 */
void sdxc_select_voltage(SDXC_Type *base, sdxc_bus_voltage_option_t option);

/**
 * @brief Reset SDXC
 * @param [in] base SDXC base address
 * @param [in] reset_type SDXC reset type
 * @param [in] timeout timeout ticks
 * @retval SDXC reset result
 */
bool sdxc_reset(SDXC_Type *base, sdxc_sw_reset_type_t reset_type, uint32_t timeout);

/**
 * @brief Enable SDXC wakeup interrupt
 * @param [in] base SDXC base address
 * @param [in] evt SDXC wakeup interrupt
 * @param [in] enable Flag to control whether to enable SDXC wakeup event
 */
void sdxc_enable_wakeup_event(SDXC_Type *base, sdxc_wakeup_event_t evt, bool enable);

/**
 * @brief Start SDXC transfer in blocking way
 * @param [in] base SDXC base address
 * @param [in] dma_config SDXC DMA configuration
 * @param [in] xfer SDXC transfer context
 * @retval SDXC transfer status
 */
hpm_stat_t sdxc_transfer_blocking(SDXC_Type *base, sdxc_adma_config_t *dma_config, sdxc_xfer_t *xfer);

/**
 * @brief Start SDXC transfer in nonblocking way
 * @param [in] base SDXC base address
 * @param [in] dma_config SDXC DMA configuration
 * @param [in] xfer SDXC transfer context
 * @retval SDXC transfer status
 */
hpm_stat_t sdxc_transfer_nonblocking(SDXC_Type *base, sdxc_adma_config_t *dma_config, sdxc_xfer_t *xfer);

/**
 * @brief SDXC Error recovery
 * @param [in] base SDXC base address
 * @retval SDXC error recovery status
 */
hpm_stat_t sdxc_error_recovery(SDXC_Type *base);

/**
 * @brief Perform SDXC tuning flow sequence
 * @param [in] base SDXC base address
 * @param [in] tuning_cmd Tuning command
 * @retval Tuning status
 */
hpm_stat_t sdxc_perform_tuning_flow_sequence(SDXC_Type *base, uint8_t tuning_cmd);

/**
 * @brief Perform SDXC software tuning
 * @param [in] base SDXC base address
 * @param [in] tuning_cmd Tuning command
 * @retval Tuning status
 */
hpm_stat_t sdxc_perform_software_tuning(SDXC_Type *base, uint8_t tuning_cmd);

/**
 * @brief Perform SDXC auto tuning
 * @param [in] base SDXC base address
 * @param [in] tuning_cmd tuning command
 * @retval Tuning status
 */
hpm_stat_t sdxc_perform_auto_tuning(SDXC_Type *base, uint8_t tuning_cmd);

#if defined(__cplusplus)
}
#endif

/**
 * @}
 */

#endif /*HPM_SDXC_DRV_H */
