/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_LVB_DRV_H
#define HPM_LVB_DRV_H

/**
 * @brief LVB APIs
 * @defgroup lvb_interface LVB driver APIs
 * @ingroup lvb_interfaces
 * @{
 */

#include "hpm_common.h"
#include "hpm_soc.h"
#include "hpm_lvb_regs.h"

/**
 * @brief LVB DI vsync polarity
 */
typedef enum lvb_di_vsync_polarity {
    lvb_di_vsync_polarity_active_high = 0,
    lvb_di_vsync_polarity_active_low
} lvb_di_vsync_polarity_t;

/**
 * @brief Shift the LVDS TX PHY clock in relation to the data
 */
typedef enum lvb_txclk_shift {
    lvb_txclk_shift_1100011 = 0,
    lvb_txclk_shift_1110001,
    lvb_txclk_shift_1111000,
    lvb_txclk_shift_1000111,
    lvb_txclk_shift_0001111,
    lvb_txclk_shift_0011110,
    lvb_txclk_shift_0111100,
} lvb_txclk_shift_t;

/**
 * @brief LVB config
 */
typedef struct lvb_config {
    bool split_ch_is_reverse; /*!< Just for split mode, reverse two channel data */
    bool split_ch_data_is_unaligned; /*!< Just for split mode, two channel pixel data are aligned */
    bool split_hswhbp_width_is_even; /*!< Just for split mode, the sum of HSW and HBP width is even */
    bool split_mode_en; /*!< Note: when using split mode, ch0/1 should be enabled, and should select same DI */
    lvb_di_vsync_polarity_t di1_vsync_polarity; /*!< lvb di1 vsync polarity */
    lvb_di_vsync_polarity_t di0_vsync_polarity; /*!< lvb di0 vsync polarity */
    lvb_txclk_shift_t txclk_shift; /*!< Shift the LVDS TX PHY clock in relation to the data */
} lvb_config_t;

/**
 * @brief LVB channel pixel data mapping
 */
typedef enum lvb_ch_mapping {
    lvb_ch_mapping_vesa = 0,
    lvb_ch_mapping_jeida,
} lvb_ch_mapping_t;

/**
 * @brief LVB channel pixel data source
 */
typedef enum lvb_ch_data_source {
    lvb_ch_data_source_di0 = 0,
    lvb_ch_data_source_di1,
} lv_ch_data_source_t;

/**
 * @brief LVB channel number
 */
typedef enum lvb_ch_num {
    lvb_ch_num_0 = 0,
    lvb_ch_num_1 = 1
} lvb_ch_num_t;

/**
 * @brief LVB channel config
 */
typedef struct lvb_ch_config {
    lvb_ch_mapping_t map;
    lv_ch_data_source_t data_src;
} lvb_ch_config_t;

typedef enum lvb_lvds_lane_phase_sel {
    lvb_lvds_lane_phase_sel_0_ui = 0,
    lvb_lvds_lane_phase_sel_1_16_ui,
    lvb_lvds_lane_phase_sel_2_16_ui,
    lvb_lvds_lane_phase_sel_3_16_ui,
    lvb_lvds_lane_phase_sel_4_16_ui,
    lvb_lvds_lane_phase_sel_5_16_ui,
    lvb_lvds_lane_phase_sel_6_16_ui,
    lvb_lvds_lane_phase_sel_7_16_ui,
    lvb_lvds_lane_phase_sel_8_16_ui,
    lvb_lvds_lane_phase_sel_9_16_ui,
    lvb_lvds_lane_phase_sel_10_16_ui,
    lvb_lvds_lane_phase_sel_11_16_ui,
    lvb_lvds_lane_phase_sel_12_16_ui,
    lvb_lvds_lane_phase_sel_13_16_ui,
    lvb_lvds_lane_phase_sel_14_16_ui,
    lvb_lvds_lane_phase_sel_15_16_ui,
} lvb_lvds_lane_phase_sel_t;

typedef enum lvb_lvds_lane_amp {
    lvb_lvds_lane_amp_50_mv = 0,
    lvb_lvds_lane_amp_100_mv,
    lvb_lvds_lane_amp_150_mv,
    lvb_lvds_lane_amp_200_mv,
    lvb_lvds_lane_amp_250_mv,
    lvb_lvds_lane_amp_300_mv,
    lvb_lvds_lane_amp_350_mv,
    lvb_lvds_lane_amp_400_mv,
    lvb_lvds_lane_amp_450_mv,
    lvb_lvds_lane_amp_500_mv,
    lvb_lvds_lane_amp_550_mv,
    lvb_lvds_lane_amp_600_mv
} lvb_lvds_lane_amp_t;

typedef enum lvb_lvds_lane_vcom {
    lvb_lvds_lane_vcom_0_7_v = 0,
    lvb_lvds_lane_vcom_0_8_v,
    lvb_lvds_lane_vcom_0_9_v,
    lvb_lvds_lane_vcom_1_0_v,
    lvb_lvds_lane_vcom_1_1_v,
    lvb_lvds_lane_vcom_1_2_v,
    lvb_lvds_lane_vcom_1_3_v,
    lvb_lvds_lane_vcom_1_4_v,
    lvb_lvds_lane_vcom_1_5_v,
} lvb_lvds_lane_vcom_t;

typedef struct lvb_lvds_phy_lane_config {
    bool rterm_enable;
    bool tx_idle;
    lvb_lvds_lane_phase_sel_t phase_sel;
    lvb_lvds_lane_amp_t amp;
    lvb_lvds_lane_vcom_t vcom;
    bool fvco_div4;
} lvb_lvds_phy_lane_config_t;

typedef enum lvb_lvds_lane_idx {
    lvb_lvds_lane_idx_lvds0_tx0 = LVB_TX_PHY_LVDS0_TX0,
    lvb_lvds_lane_idx_lvds0_tx1 = LVB_TX_PHY_LVDS0_TX1,
    lvb_lvds_lane_idx_lvds0_tx2 = LVB_TX_PHY_LVDS0_TX2,
    lvb_lvds_lane_idx_lvds0_tx3 = LVB_TX_PHY_LVDS0_TX3,
    lvb_lvds_lane_idx_lvds0_txck = LVB_TX_PHY_LVDS0_TXCK,
    lvb_lvds_lane_idx_lvds1_tx0 = LVB_TX_PHY_LVDS1_TX0,
    lvb_lvds_lane_idx_lvds1_tx1 = LVB_TX_PHY_LVDS1_TX1,
    lvb_lvds_lane_idx_lvds1_tx2 = LVB_TX_PHY_LVDS1_TX2,
    lvb_lvds_lane_idx_lvds1_tx3 = LVB_TX_PHY_LVDS1_TX3,
    lvb_lvds_lane_idx_lvds1_txck = LVB_TX_PHY_LVDS1_TXCK,
} lvb_lvds_lane_idx_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief get LVB of default config
 *
 * @param[out] cfg config of LVB
 */
void lvb_get_default_config(lvb_config_t *cfg);

/**
 * @brief LVB init
 *
 * @param[in] ptr LVB base address
 * @param[in] cfg config of LVB
 */
void lvb_init(LVB_Type *ptr, lvb_config_t *cfg);

/**
 * @brief get LVB channel of default config
 *
 * @param[out] ch_cfg config of LVB
 */
void lvb_get_ch_default_config(lvb_ch_config_t *ch_cfg);

/**
 * @brief LVB channel config
 *
 * @param[in] ptr LVB base address
 * @param[in] ch_num LVB channel number
 * @param[in] ch_cfg config of LVB channel
 */
void lvb_ch_config(LVB_Type *ptr, lvb_ch_num_t ch_num, lvb_ch_config_t *ch_cfg);

/**
 * @brief LVB channel enable
 *
 * @param[in] ptr LVB base address
 * @param[in] ch_num LVB channel number
 */
void lvb_ch_enable(LVB_Type *ptr, lvb_ch_num_t ch_num);

/**
 * @brief LVB channel disable
 *
 * @param[in] ptr LVB base address
 * @param[in] ch_num LVB channel number
 */
void lvb_ch_disable(LVB_Type *ptr, lvb_ch_num_t ch_num);

/**
 * @brief check LVB phy0 is lock
 *
 * @param[in] ptr LVB base address
 */
static inline bool lvb_lvds_phy0_pll_is_lock(LVB_Type *ptr)
{
    return !!LVB_PHY_STAT_LVDS0_TX_PHY_PLL_LOCK_GET(ptr->PHY_STAT);
}

/**
 * @brief check LVB phy1 is lock
 *
 * @param[in] ptr LVB base address
 */
static inline bool lvb_lvds_phy1_pll_is_lock(LVB_Type *ptr)
{
    return !!LVB_PHY_STAT_LVDS1_TX_PHY_PLL_LOCK_GET(ptr->PHY_STAT);
}

/**
 * @brief check LVB phy0 and phy1 is lock
 *
 * @param[in] ptr LVB base address
 */
static inline bool lvb_lvds_phy_split_pll_is_lock(LVB_Type *ptr)
{
    return !!LVB_PHY_STAT_LVDS0_TX_PHY_PLL_LOCK_GET(ptr->PHY_STAT) &&
            !!LVB_PHY_STAT_LVDS1_TX_PHY_PLL_LOCK_GET(ptr->PHY_STAT);
}

/**
 * @brief lvb lvds lane get default config
 *
 * @param[out] cfg lvds lane config @ref lvb_lvds_phy_lane_config_t
 */
void lvb_lvds_phy_lane_get_default_config(lvb_lvds_phy_lane_config_t *cfg);

/**
 * @brief lvb lvds lane init and config
 *
 * @param[in] ptr LVB base address
 * @param[in] tx_index lvds phy lane index @ref lvb_lvds_lane_idx_t
 * @param[in] cfg lvds lane config @ref lvb_lvds_phy_lane_config_t
 */
void lvb_lvds_phy_lane_init(LVB_Type *ptr, lvb_lvds_lane_idx_t tx_index, lvb_lvds_phy_lane_config_t *cfg);

/**
 * @brief power on LVB phy0
 *
 * @param[in] ptr LVB base address
 */
void lvb_lvds_phy0_poweron(LVB_Type *ptr);

/**
 * @brief power on LVB phy1
 *
 * @param[in] ptr LVB base address
 */
void lvb_lvds_phy1_poweron(LVB_Type *ptr);

/**
 * @brief power down LVB phy0
 *
 * @param[in] ptr LVB base address
 */
void lvb_lvds_phy0_powerdown(LVB_Type *ptr);

/**
 * @brief power down LVB phy0
 *
 * @param[in] ptr LVB base address
 */
void lvb_lvds_phy1_powerdown(LVB_Type *ptr);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */
#endif /* HPM_LVB_DRV_H */
