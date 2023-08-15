/*
 * Copyright (c) 2021-2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_FEMC_DRV_H
#define _HPM_FEMC_DRV_H
#include "hpm_femc_regs.h"

/**
 * @brief femc driver APIs
 * @defgroup dram_interface femc driver APIs
 * @ingroup io_interfaces
 * @{
 *
 */

#define FEMC_SDRAM_MAX_BURST_LENGTH_IN_BYTE (8UL)
/* @brief femc sdram column address bit width */
#define FEMC_SDRAM_COLUMN_ADDR_12_BITS (0U)
#define FEMC_SDRAM_COLUMN_ADDR_11_BITS (1U)
#define FEMC_SDRAM_COLUMN_ADDR_10_BITS (2U)
#define FEMC_SDRAM_COLUMN_ADDR_9_BITS (3U)
#define FEMC_SDRAM_COLUMN_ADDR_8_BITS (4U)
/* @brief cas latency */
#define FEMC_SDRAM_CAS_LATENCY_1 (1U)
#define FEMC_SDRAM_CAS_LATENCY_2 (2U)
#define FEMC_SDRAM_CAS_LATENCY_3 (3U)
/* @brief iomux options */
#define FEMC_IO_MUX_NOT_USED (0U)
#define FEMC_IO_MUX_CSX0 (1U)
#define FEMC_IO_MUX_CSX1 (2U)
#define FEMC_IO_MUX_CSX2 (3U)
#define FEMC_IO_MUX_CSX3 (4U)
#define FEMC_IO_MUX_RDY (5U)
/* @brief sdram bank number */
#define FEMC_SDRAM_BANK_NUM_4 (0U)
#define FEMC_SDRAM_BANK_NUM_2 (1U)
/* @brief chip select */
#define FEMC_SDRAM_CS0 (0U)
#define FEMC_SDRAM_CS1 (1U)
/* @brief sdram port size */
#define FEMC_SDRAM_PORT_SIZE_8_BITS (0U)
#define FEMC_SDRAM_PORT_SIZE_16_BITS (1U)
#define FEMC_SDRAM_PORT_SIZE_32_BITS (2U)

#define FEMC_AXI_Q_COUNT (2U)
#define FEMC_AXI_Q_A (0U)
#define FEMC_AXI_Q_B (1U)
/* @brief DQS option */
#define FEMC_DQS_INTERNAL (0U)
#define FEMC_DQS_FROM_PAD (1U)

#define FEMC_BR_COUNT (2U)

#define FEMC_CMD_KEY                   FEMC_IPCMD_KEY_SET(0xA55A)
#define FEMC_CMD_WRITE_FLAG            (1UL << 31)
#define FEMC_CMD_SDRAM_READ            (0x8U)
#define FEMC_CMD_SDRAM_WRITE           (FEMC_CMD_WRITE_FLAG | 0x9U)
#define FEMC_CMD_SDRAM_MODE_SET        (FEMC_CMD_WRITE_FLAG | 0xAU)
#define FEMC_CMD_SDRAM_ACTIVE          (0xBU)
#define FEMC_CMD_SDRAM_AUTO_REFRESH    (0xCU)
#define FEMC_CMD_SDRAM_SELF_REFRESH    (0xDU)
#define FEMC_CMD_SDRAM_PRECHARGE       (0xEU)
#define FEMC_CMD_SDRAM_PRECHARGE_ALL   (0xFU)

/* @brief sram address mode */
#define FEMC_SRAM_AD_MUX_MODE (0U)
#define FEMC_SRAM_AD_NONMUX_MODE (3U)

/* @brief sram adv hold state */
#define FEMC_SRAM_ADV_HOLD_HIGH (0U)
#define FEMC_SRAM_ADV_HOLD_LOW (1U)

/* @brief sram adv polarity */
#define FEMC_SRAM_ADV_ACTIVE_LOW (0U)
#define FEMC_SRAM_ADV_ACTIVE_HIGH (1U)

/* @brief sram port size */
#define FEMC_SRAM_PORT_SIZE_8_BITS (0U)
#define FEMC_SRAM_PORT_SIZE_16_BITS (1U)

/* @brief IO_CSX selection */
#define FEMC_IO_CSX_SDRAM_CS1 (1U)
#define FEMC_IO_CSX_SRAM_CE (6U)

/**
 * @brief Structure for specifying the configuration of AXI queue weight
 */
typedef struct {
    bool enable;                /**< Enable AXI weight setting flag */
    uint8_t qos;
    uint8_t age;
    uint8_t slave_hit_wo_rw;
    uint8_t slave_hit;          /**< only available for queue A */
    uint8_t page_hit;           /**< only available for queue B */
    uint8_t bank_rotation;      /**< only available for queue B */
} femc_axi_q_weight_t;

/**
 * @brief Structure for specifying the configuration of SDRAM
 */
typedef struct {
    uint32_t base_address;              /**< external SDRAM base address */
    uint32_t size_in_byte;              /**< external SDRAM size in byte */
    uint32_t refresh_count;             /**< referesh count */
    uint8_t col_addr_bits;              /**< column address bit count */
    uint8_t cas_latency;                /**< CAS latency */
    uint8_t cs;                         /**< chip select */
    uint8_t cs_mux_pin;                 /**< chip select mux */
    uint8_t bank_num;                   /**< bank number */
    uint8_t prescaler;                  /**< presecaler */
    uint8_t port_size;                  /**< SDRAM port size */
    uint8_t burst_len_in_byte;          /**< 1/2/4/8 bytes */
    uint8_t cke_off_in_ns;              /**< Tcks */
    uint8_t act_to_precharge_in_ns;     /**< Tras */
    uint8_t precharge_to_act_in_ns;     /**< Trp  */
    uint8_t act_to_rw_in_ns;            /**< Trcd */
    uint8_t act_to_act_in_ns;           /**< Trrd */
    uint8_t refresh_to_refresh_in_ns;   /**< Trc */
    uint8_t write_recover_in_ns;        /**< Tdpl */
    uint8_t self_refresh_recover_in_ns; /**< Txsr */
    uint8_t refresh_recover_in_ns;      /**< Txsr */
    uint8_t refresh_in_ms;              /**< Tref */
    uint8_t idle_timeout_in_ns;
    uint8_t data_width_in_byte;
    uint8_t auto_refresh_count_in_one_burst;
    uint8_t delay_cell_value;           /**< Delay cell value */
} femc_sdram_config_t;

/**
 * @brief Structure for specifying the configuration of SRAM
 */
typedef struct {
    uint32_t base_address;              /**< external SRAM base address */
    uint32_t size_in_byte;              /**< external SRAM size in byte */
    uint8_t address_mode;               /**< address mode */
    uint8_t port_size;                  /**< port size */
    uint8_t adv_hold_state;             /**< adv hold level */
    uint8_t adv_polarity;               /**< adv polarity */
    uint8_t oeh_in_ns;                  /**< OE high time */
    uint8_t oel_in_ns;                  /**< OE low time */
    uint8_t weh_in_ns;                  /**< WE high time */
    uint8_t wel_in_ns;                  /**< WE low time */
    uint8_t ah_in_ns;                   /**< address hold time */
    uint8_t as_in_ns;                   /**< address setup time */
    uint8_t ceh_in_ns;                  /**< chip enable hold time */
    uint8_t ces_in_ns;                  /**< chip enable setup time */
} femc_sram_config_t;

/**
 * @brief Structure for specifying the configuration of FEMC
 */
typedef struct {
    uint8_t dqs;                        /**< DQS setting */
    uint8_t cmd_timeout;                /**< command timeout */
    uint8_t bus_timeout;                /**< bus timeout */
    femc_axi_q_weight_t axi_q_weight[FEMC_AXI_Q_COUNT];
} femc_config_t;

/**
 * @brief Structure for FEMC command
 */
typedef struct {
    uint32_t opcode;
    uint32_t data;
} femc_cmd_t;

/*
 * @brief FEMC specific status
 */
enum {
    status_femc_cmd_err = MAKE_STATUS(status_group_femc, 1),
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief femc enable
 *
 * Enable FEMC
 *
 * @param[in] ptr FEMC base address
 */
static inline void femc_enable(FEMC_Type *ptr)
{
    ptr->CTRL &= ~FEMC_CTRL_DIS_MASK;
}

/**
 * @brief femc disable
 *
 * Disable FEMC
 *
 * @param[in] ptr FEMC base address
 */
static inline void femc_disable(FEMC_Type *ptr)
{
    while ((ptr->STAT0 & (uint32_t) FEMC_STAT0_IDLE_MASK) == 0) {
    }
    ptr->CTRL |= FEMC_CTRL_DIS_MASK;
}

/**
 * @brief femc software reset
 *
 * Perform software reset
 *
 * @param[in] ptr FEMC base address
 */
static inline void femc_sw_reset(FEMC_Type *ptr)
{
    ptr->CTRL = FEMC_CTRL_RST_MASK;
    while ((ptr->CTRL & (uint32_t) FEMC_CTRL_RST_MASK) != 0) {
    }
}

/**
 * @brief femc get default config
 *
 * Get FEMC default parameters
 *
 * @param[in] ptr FEMC base address
 * @param[out] config femc_config_t address
 */
void femc_default_config(FEMC_Type *ptr, femc_config_t *config);

/**
 * @brief femc init controller
 *
 * Initialize FEMC with give femc_config_t
 *
 * @param[in] ptr FEMC base address
 * @param[in] config femc_config_t to initialize femc
 */
void femc_init(FEMC_Type *ptr, femc_config_t *config);

/**
 * @brief femc get typical sdram config
 *
 * Fill out the structure of femc_sdram_config_t with typical SDRAM parameters which should work
 * with most SDRAMs.
 *
 * @param[in] ptr FEMC base address
 * @param[out] config femc_sdram_config_t sdram configuration struction to config femc
 */
void femc_get_typical_sdram_config(FEMC_Type *ptr, femc_sdram_config_t *config);

/**
 * @brief femc config sdram
 *
 * Configure FEMC controlling external SDRAM using parameters specified in femc_sdram_config_t
 *
 * @param[in] ptr FEMC base address
 * @param[in] clk_in_hz femc source clock frequency in Hz
 * @param[in] config femc_sdram_config_t sdram configuration struction to config femc
 */
hpm_stat_t femc_config_sdram(FEMC_Type *ptr, uint32_t clk_in_hz, femc_sdram_config_t *config);

/**
 * @brief femc get typical sram config
 *
 * Fill out the structure of femc_sram_config_t with typical SRAM parameters which should work
 * with most SRAMs.
 *
 * @param[in] ptr FEMC base address
 * @param[out] config femc_sdram_config_t sdram configuration struction to config femc
 */
void femc_get_typical_sram_config(FEMC_Type *ptr, femc_sram_config_t *config);

/**
 * @brief femc config sram
 *
 * Configure FEMC controlling external SRAM using parameters specified in femc_sram_config_t
 *
 * @param[in] ptr FEMC base address
 * @param[in] clk_in_hz femc source clock frequency in Hz
 * @param[in] config femc_sram_config_t sram configuration struction to config femc
 */
hpm_stat_t femc_config_sram(FEMC_Type *ptr, uint32_t clk_in_hz, femc_sram_config_t *config);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif    /* _HPM_FEMC_DRV_H */

