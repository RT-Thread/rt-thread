/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_DRAM_DRV_H
#define _HPM_DRAM_DRV_H
#include "hpm_dram_regs.h"

/**
 * @brief DRAM driver APIs
 * @defgroup dram_interface DRAM driver APIs
 * @ingroup io_interfaces
 * @{
 *
 */

#define DRAM_SDRAM_MAX_BURST_LENGTH_IN_BYTE (8UL)
/* @brief dram sdram column address bit width */
#define DRAM_SDRAM_COLUMN_ADDR_12_BITS (0U)
#define DRAM_SDRAM_COLUMN_ADDR_11_BITS (1U)
#define DRAM_SDRAM_COLUMN_ADDR_10_BITS (2U)
#define DRAM_SDRAM_COLUMN_ADDR_9_BITS (3U)
#define DRAM_SDRAM_COLUMN_ADDR_8_BITS (4U)
/* @brief cas latency */
#define DRAM_SDRAM_CAS_LATENCY_1 (1U)
#define DRAM_SDRAM_CAS_LATENCY_2 (2U)
#define DRAM_SDRAM_CAS_LATENCY_3 (3U)
/* @brief iomux options */
#define DRAM_IO_MUX_NOT_USED (0U)
#define DRAM_IO_MUX_CSX0 (1U)
#define DRAM_IO_MUX_CSX1 (2U)
#define DRAM_IO_MUX_CSX2 (3U)
#define DRAM_IO_MUX_CSX3 (4U)
#define DRAM_IO_MUX_RDY (5U)
/* @brief sdram bank number */
#define DRAM_SDRAM_BANK_NUM_4 (0U)
#define DRAM_SDRAM_BANK_NUM_2 (1U)
/* @brief chip select */
#define DRAM_SDRAM_CS0 (0U)
#define DRAM_SDRAM_CS1 (1U)
/* @brief sdram port size */
#define DRAM_SDRAM_PORT_SIZE_8_BITS (0U)
#define DRAM_SDRAM_PORT_SIZE_16_BITS (1U)
#define DRAM_SDRAM_PORT_SIZE_32_BITS (2U)

#define DRAM_AXI_Q_COUNT (2U)
#define DRAM_AXI_Q_A (0U)
#define DRAM_AXI_Q_B (1U)
/* @brief DQS option */
#define DRAM_DQS_INTERNAL (0U)
#define DRAM_DQS_FROM_PAD (1U)

#define DRAM_BR_COUNT (2U)

#define DRAM_CMD_KEY                   DRAM_IPCMD_KEY_SET(0xA55A)
#define DRAM_CMD_WRITE_FLAG            (1UL << 31)
#define DRAM_CMD_SDRAM_READ            (0x8U)
#define DRAM_CMD_SDRAM_WRITE           (DRAM_CMD_WRITE_FLAG | 0x9U)
#define DRAM_CMD_SDRAM_MODE_SET        (DRAM_CMD_WRITE_FLAG | 0xAU)
#define DRAM_CMD_SDRAM_ACTIVE          (0xBU)
#define DRAM_CMD_SDRAM_AUTO_REFRESH    (0xCU)
#define DRAM_CMD_SDRAM_SELF_REFRESH    (0xDU)
#define DRAM_CMD_SDRAM_PRECHARGE       (0xEU)
#define DRAM_CMD_SDRAM_PRECHARGE_ALL   (0xFU)

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
} dram_axi_q_weight_t;

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
} dram_sdram_config_t;

/**
 * @brief Structure for specifying the configuration of DRAM
 */
typedef struct {
    uint8_t dqs;                        /**< DQS setting */
    uint8_t cmd_timeout;                /**< command timeout */
    uint8_t bus_timeout;                /**< bus timeout */
    dram_axi_q_weight_t axi_q_weight[DRAM_AXI_Q_COUNT];
} dram_config_t;

/**
 * @brief Structure for DRAM command
 */
typedef struct {
    uint32_t opcode;
    uint32_t data;
} dram_cmd_t;

/*
 * @brief DRAM specific status
 */
enum {
    status_dram_cmd_err = MAKE_STATUS(status_group_dram, 1),
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief dram enable
 *
 * Enable DRAM
 *
 * @param[in] ptr DRAM base address
 */
static inline void dram_enable(DRAM_Type *ptr)
{
    ptr->CTRL &= ~DRAM_CTRL_DIS_MASK;
}

/**
 * @brief dram disable
 *
 * Disable DRAM
 *
 * @param[in] ptr DRAM base address
 */
static inline void dram_disable(DRAM_Type *ptr)
{
    while((ptr->STAT0 & (uint32_t) DRAM_STAT0_IDLE_MASK) == 0) {}
    ptr->CTRL |= DRAM_CTRL_DIS_MASK;
}

/**
 * @brief dram software reset
 *
 * Perform software reset
 *
 * @param[in] ptr DRAM base address
 */
static inline void dram_sw_reset(DRAM_Type *ptr)
{
    ptr->CTRL = DRAM_CTRL_RST_MASK;
    while((ptr->CTRL & (uint32_t) DRAM_CTRL_RST_MASK) != 0) {}
}

/**
 * @brief dram get default config
 *
 * Get DRAM default parameters
 *
 * @param[in] ptr DRAM base address
 * @param[out] config dram_config_t address
 */
void dram_default_config(DRAM_Type *ptr, dram_config_t *config);

/**
 * @brief dram init controller
 *
 * Initialize DRAM with give dram_config_t
 *
 * @param[in] ptr DRAM base address
 * @param[in] config dram_config_t to initialize dram
 */
void dram_init(DRAM_Type *ptr, dram_config_t *config);

/**
 * @brief dram get typical sdram config
 *
 * Fill out the structure of dram_sdram_config_t with typical SDRAM parameters which should work
 * with most SDRAMs.
 *
 * @param[in] ptr DRAM base address
 * @param[out] config dram_sdram_config_t sdram configuration struction to config dram
 */
void dram_get_typical_sdram_config(DRAM_Type *ptr, dram_sdram_config_t *config);

/**
 * @brief dram config sdram
 *
 * Configure DRAM controlling external SDRAM using parameters specified in dram_sdram_config
 *
 * @param[in] ptr DRAM base address
 * @param[in] clk_in_hz dram source clock frequency in Hz
 * @param[in] config dram_sdram_config_t sdram configuration struction to config dram
 */
hpm_stat_t dram_config_sdram(DRAM_Type *ptr, uint32_t clk_in_hz, dram_sdram_config_t *config);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif    /* _HPM_DRAM_DRV_H */

