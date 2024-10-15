/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PPI_DRV_H
#define HPM_PPI_DRV_H

#include "hpm_common.h"
#include "hpm_soc_ip_feature.h"
#include "hpm_ppi_regs.h"

/**
 * @brief PPI driver APIs
 * @defgroup ppi_interface PPI driver APIs
 * @ingroup ppi_interfaces
 * @{
 */

/**
 * @brief cs pin idle polarity
 *
 */
typedef enum {
    ppi_cs_idle_pol_low = 0,
    ppi_cs_idle_pol_high
} ppi_cs_idle_polarity_t;    /**< ppi_cs_idle_polarity_t */

/**
 * @brief dm pin valid polarity
 *
 */
typedef enum {
    ppi_dm_valid_pol_high = 0,
    ppi_dm_valid_pol_low
} ppi_dm_valid_polarity_t;    /**< ppi_dm_valid_polarity_t */

/**
 * @brief ctrl pin polarity
 *
 */
typedef enum {
    ppi_ctrl_pol_low = 0,
    ppi_ctrl_pol_high
} ppi_ctrl_polarity_t;    /**< ppi_ctrl_polarity_t */

/**
 * @brief ctrl pin direction
 *
 */
typedef enum {
    ppi_ctrl_pin_dir_input = 0,
    ppi_ctrl_pin_dir_output,
} ppi_ctrl_pin_dir_t;    /**< ppi_ctrl_pin_dir_t */

/**
 * @brief clock pin output mode
 *
 */
typedef enum {
    ppi_clk_output_by_cmd_clk_output = 0,
    ppi_clk_always_output
} ppi_clk_output_mode_t;    /**< ppi_clk_output_mode_t */

/**
 * @brief irq mask
 *
 */
typedef enum {
    ppi_irq_tm_out_mask = PPI_IRQ_EN_IRQ_TMOUT_EN_MASK,
} ppi_irq_mask_t;    /**< ppi_irq_mask_t */

/**
 * @brief port size
 *
 */
typedef enum {
    ppi_port_size_8bits = 0,
    ppi_port_size_16bits,
    ppi_port_size_32bits,
} ppi_port_size_t;    /**< ppi_port_size_t */

/**
 * @brief cmd byte select
 *
 */
typedef enum {
    ppi_byte_sel_0_7_bits = 0,
    ppi_byte_sel_8_15_bits,
    ppi_byte_sel_16_23_bits,
    ppi_byte_sel_24_31_bits
} ppi_byte_sel_t;    /**< ppi_byte_sel_t */

/**
 * @brief cmd address and data function
 *
 */
typedef enum {
    ppi_ad_func_data = 0,
    ppi_ad_func_addr
} ppi_ad_func_t;    /**< ppi_ad_func_t */

/**
 * @brief cmd address and data pins direction
 *
 */
typedef enum {
    ppi_ad_pin_dir_output = 0,
    ppi_ad_pin_dir_input
} ppi_ad_pin_dir_t;    /**< ppi_ad_pin_dir_t */

/**
 * @brief clock pin config structure
 *
 */
typedef struct {
    uint8_t cycle_num;
    uint8_t high_num;
    uint8_t low_num;
    ppi_clk_output_mode_t mode;
    bool revert;
} ppi_clk_pin_config_t;    /**< ppi_clk_pin_config_t */

/**
 * @brief cs pin config structure
 *
 */
typedef struct {
    ppi_port_size_t port_size;
    uint16_t addr_start_high_12bits;    /* address space: 0xF8000000 ~ 0xFFFFFFFF */
    uint16_t addr_end_high_12bits;      /* address space: 0xF8000000 ~ 0xFFFFFFFF */
    uint16_t addr_mask;
    bool sync_clk_en;
    uint8_t sync_clk_sel;
    uint8_t interval_cycle;
    uint8_t rcmd_start0;
    uint8_t rcmd_end0;
    uint8_t rcmd_start1;
    uint8_t rcmd_end1;
    uint8_t wcmd_start0;
    uint8_t wcmd_end0;
    uint8_t wcmd_start1;
    uint8_t wcmd_end1;
#if defined(HPM_IP_FEATURE_PPI_DM_POLARITY_EACH_CS) && HPM_IP_FEATURE_PPI_DM_POLARITY_EACH_CS
    ppi_dm_valid_polarity_t dm_polarity;
#endif
} ppi_cs_pin_config_t;    /**< ppi_cs_pin_config_t */

/**
 * @brief cmd config structure
 *
 */
typedef struct {
    bool cs_pin_value;
    bool clk_output;
    uint8_t cmd_cycle;
    ppi_ad_func_t ad_func_sel[4];
    ppi_ad_pin_dir_t ad_pin_dir[4];
    ppi_byte_sel_t byte_sel[4];
    bool ctrl_pin_value[8];
} ppi_cmd_config_t;    /**< ppi_cmd_config_t */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief set ppi software reset
 *
 * @param[in] ppi PPI base address
 * @param[in] reset true - software reset; false - normal work.
 */
static inline void ppi_set_reset(PPI_Type *ppi, bool reset)
{
    if (reset) {
        ppi->GLB_CFG |= PPI_GLB_CFG_SOFT_RESET_MASK;
    } else {
        ppi->GLB_CFG &= ~PPI_GLB_CFG_SOFT_RESET_MASK;
    }
}

/**
 * @brief config cs pin work valid polarity
 *
 * @param[in] ppi PPI base address
 * @param[in] index cs pin index, value: 0 - 3
 * @param[in] pol @ref ppi_cs_idle_polarity_t
 */
static inline void ppi_config_cs_pin_polarity(PPI_Type *ppi, uint8_t index, ppi_cs_idle_polarity_t pol)
{
    assert(index < 4);
    ppi->PAD_CFG = (ppi->PAD_CFG & ~(((1u << PPI_PAD_CFG_CS_IDLE_ST_SHIFT) << index))) | (((pol << PPI_PAD_CFG_CS_IDLE_ST_SHIFT) << index));
}

/**
 * @brief config dm pin work polarity
 *
 * @param[in] ppi PPI base address
 * @param[in] index If has HPM_IP_FEATURE_PPI_DM_POLARITY_EACH_CS feature, this is cs pin index, value: 0 - 3. Else, not use.
 * @param[in] pol @ref ppi_dm_valid_polarity_t
 */
static inline void ppi_config_dm_pin_polarity(PPI_Type *ppi, uint8_t index, ppi_dm_valid_polarity_t pol)
{
#if defined(HPM_IP_FEATURE_PPI_DM_POLARITY_EACH_CS) && HPM_IP_FEATURE_PPI_DM_POLARITY_EACH_CS
    assert(index < 4);
    ppi->CS[index].CFG2 = (ppi->CS[index].CFG2 & ~PPI_CS_CFG2_DM_POLARITY_MASK) | PPI_CS_CFG2_DM_POLARITY_SET(pol);
#else
    (void)index;
    if (pol == ppi_dm_valid_pol_high) {
        ppi->PAD_CFG &= ~PPI_PAD_CFG_DM_PAD_POL_MASK;
    } else {
        ppi->PAD_CFG |= PPI_PAD_CFG_DM_PAD_POL_MASK;
    }
#endif
}

/**
 * @brief config ctrl pin work polarity, output and input ctrl pin polarity has different meaning
 *
 * @param[in] ppi PPI base address
 * @param[in] index Ctrl pin index, value: 0 - 7
 * @param[in] pol @ref ppi_ctrl_polarity_t
 *   [1] Output: ppi_ctrl_pol_low is output the value in cmd; ppi_ctrl_pol_high is output reversed value in cmd.
 *   [2] Input: ppi_ctrl_pol_low is input low valid; ppi_ctrl_pol_high is input high valid.
 */
static inline void ppi_config_ctrl_pin_polarity(PPI_Type *ppi, uint8_t index, ppi_ctrl_polarity_t pol)
{
    assert(index < 8);
    ppi->PAD_CFG = (ppi->PAD_CFG & ~(((1u << PPI_PAD_CFG_CTRL_PAD_POL_SHIFT) << index))) | (((pol << PPI_PAD_CFG_CTRL_PAD_POL_SHIFT) << index));
}

/**
 * @brief set ctrl pin direction
 *
 * @param[in] ppi PPI base address
 * @param[in] index Ctrl pin index, value: 0 - 7
 * @param[in] dir Ctrl pin direction, @ref ppi_ctrl_pin_dir_t
 */
static inline void ppi_set_ctrl_pin_dir(PPI_Type *ppi, uint8_t index, ppi_ctrl_pin_dir_t dir)
{
    assert(index < 8);
    ppi->PAD_CFG = (ppi->PAD_CFG & ~(((1u << PPI_PAD_CFG_CTRL_PAD_OE_SHIFT) << index))) | (((dir << PPI_PAD_CFG_CTRL_PAD_OE_SHIFT) << index));
}

/**
 * @brief config timeout
 *
 * @param[in] ppi PPI base address
 * @param[in] timeout_cnt timeout counter
 * @param[in] enable true - enable; false - disable
 */
static inline void ppi_config_timeout(PPI_Type *ppi, uint16_t timeout_cnt, bool enable)
{
    ppi->TM_CFG = PPI_TM_CFG_TM_CFG_SET(timeout_cnt) | PPI_TM_CFG_TM_EN_SET(enable);
}

/**
 * @brief set irq enable
 *
 * @param[in] ppi PPI base address
 * @param[in] mask irq mask, @ref ppi_irq_mask_t
 */
static inline void ppi_set_irq_enable(PPI_Type *ppi, uint32_t mask)
{
    ppi->IRQ_EN |= mask;
}

/**
 * @brief set irq disable
 *
 * @param[in] ppi PPI base address
 * @param[in] mask irq mask, @ref ppi_irq_mask_t
 */
static inline void ppi_set_irq_disable(PPI_Type *ppi, uint32_t mask)
{
    ppi->IRQ_EN &= ~mask;
}

/**
 * @brief get irq enable status
 *
 * @param[in] ppi PPI base address
 * @retval irq enable status, @ref ppi_irq_mask_t
 */
static inline uint32_t ppi_get_irq_enable_status(PPI_Type *ppi)
{
    return ppi->IRQ_EN;
}

/**
 * @brief get irq status
 *
 * @param[in] ppi PPI base address
 * @retval irq status, @ref ppi_irq_mask_t
 */
static inline uint32_t ppi_get_irq_status(PPI_Type *ppi)
{
    return ppi->IRQ_STS;
}

/**
 * @brief clear irq flag
 *
 * @param[in] ppi PPI base address
 * @param[in] mask irq mask, @ref ppi_irq_mask_t
 */
static inline void ppi_clear_irq_flag(PPI_Type *ppi, uint32_t mask)
{
    ppi->IRQ_STS = mask;
}

/**
 * @brief set clk pin enable
 *
 * @param[in] ppi PPI base address
 */
static inline void ppi_set_clk_pin_enable(PPI_Type *ppi)
{
    ppi->CLKPIN_CFG |= PPI_CLKPIN_CFG_EN_MASK;
}

/**
 * @brief set clk pin disable
 *
 * @param[in] ppi PPI base address
 */
static inline void ppi_set_clk_pin_disable(PPI_Type *ppi)
{
    ppi->CLKPIN_CFG &= ~PPI_CLKPIN_CFG_EN_MASK;
}

/**
 * @brief config clock pin output
 *
 * @param[in] ppi PPI base address
 * @param[in] config clock pin config structure pointer, @ref ppi_clk_pin_config_t
 */
void ppi_config_clk_pin(PPI_Type *ppi, ppi_clk_pin_config_t *config);

/**
 * @brief config cs pin
 *
 * @param[in] ppi PPI base address
 * @param[in] index cs pin index, value: 0 - 3
 * @param[in] config cs pin config structure pointer, @ref ppi_cs_pin_config_t
 */
void ppi_config_cs_pin(PPI_Type *ppi, uint8_t index, ppi_cs_pin_config_t *config);

/**
 * @brief config cmd
 *
 * @param[in] ppi PPI base address
 * @param[in] index cmd index, value: 0 - 63
 * @param[in] config cmd config structure pointer, @ref ppi_cmd_config_t
 */
void ppi_config_cmd(PPI_Type *ppi, uint8_t index, ppi_cmd_config_t *config);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_PPI_DRV_H */
