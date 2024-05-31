/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_LCB_DRV_H
#define HPM_LCB_DRV_H

/**
 * @brief LCB APIs
 * @defgroup lcb_interface LCB driver APIs
 * @ingroup lcb_interfaces
 * @{
 */

#include "hpm_common.h"
#include "hpm_soc.h"
#include "hpm_lcb_regs.h"

typedef enum lcb_rxclk_sel {
    lcb_rxclk_sel_phy0 = 0,
    lcb_rxclk_sel_phy1 = 1,
} lcb_rxclk_sel_t;

typedef enum lcb_mode {
    lcb_mode_display = 0,
    lcb_mode_cam_link = 1,
} lcb_mode_t;

typedef enum lcb_display_mode_mapping {
    lcb_display_mode_mapping_vesa = 0,
    lcb_display_mode_mapping_jeida = 1,
} lcb_display_mode_mapping_t;

typedef enum lcb_display_mode_data_width {
    lcb_display_mode_data_width_18bit = 0,
    lcb_display_mode_data_width_24bit = 1,
} lcb_display_mode_data_width_t;

typedef struct lcb_display_mode_config {
    lcb_display_mode_mapping_t map;
    lcb_display_mode_data_width_t data_width;
} lcb_display_mode_config_t;

typedef enum lcb_cam_link_mode_data_width {
    lcb_cam_link_mode_data_width_24bit = 0,
    lcb_cam_link_mode_data_width_30bit = 1,
    lcb_cam_link_mode_data_width_36bit = 1,
} lcb_cam_link_mode_data_width_t;

typedef struct lcb_cam_link_mode_config {
    lcb_cam_link_mode_data_width_t data_width;
} lcb_cam_link_mode_config_t;

typedef struct lcb_config {
    lcb_rxclk_sel_t rxclk_sel;
    lcb_mode_t mode;
    union {
        lcb_display_mode_config_t display;
        lcb_cam_link_mode_config_t cam_link;
    };
} lcb_config_t;

/**
 * @brief Terminal impedance regulation
 */
typedef enum lcb_lvds_phy_rterm {
    lcb_lvds_phy_rterm_hi_z = 0,
    lcb_lvds_phy_rterm_150_ohm = 1,
    lcb_lvds_phy_rterm_100_ohm = 8,
    lcb_lvds_phy_rterm_75_ohm = 15,
} lcb_lvds_phy_rterm_t;

typedef struct lcb_lvds_phy_data_lane_config {
    uint8_t dline_adj; /*!< Lane N skew adjustment value between data and clock. 0000000: max; 1111111: min */
    lcb_lvds_phy_rterm_t rterm; /*!< Terminal impedance regulation */
} lcb_lvds_phy_data_lane_config_t;

/**
 * @brief DLL loop delay adjustment minimum frequency
 */
typedef enum lcb_lvds_phy_dll_delay_adj_min_freq {
    lcb_lvds_phy_dll_delay_adj_min_freq_40_70mhz = 0,
    lcb_lvds_phy_dll_delay_adj_min_freq_70_110mhz = 0,
} lcb_lvds_phy_dll_delay_adj_min_freq_t;

typedef struct lcb_lvds_phy_clk_lane_config {
    lcb_lvds_phy_dll_delay_adj_min_freq_t min_adj;
    uint16_t dll_tuning_int; /*!< DLL loop delay coarse adjustment initial value. 00000000: min ; 11111111: max */
    lcb_lvds_phy_rterm_t rterm; /*!< Terminal impedance regulation */
} lcb_lvds_phy_clk_lane_config_t;

typedef enum lcb_lvds_phy_data_lane_id {
    lcb_lvds_phy_data_lane_id_0 = 0,
    lcb_lvds_phy_data_lane_id_1 = 1,
} lcb_lvds_phy_data_lane_id_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief get LCB of default config
 *
 * @param[out] cfg config of LCB
 */
void lcb_get_default_config(lcb_config_t *cfg);

/**
 * @brief LCB init
 *
 * @param[in] ptr LCB base address
 * @param[in] cfg config of LCB
 */
void lcb_init(LCB_Type *ptr, lcb_config_t *cfg);

/**
 * @brief get LCB clk_lane of default config
 *
 * @param[out] cfg config of clk_lane
 */
void lcb_get_phy_clk_lane_default_config(lcb_lvds_phy_clk_lane_config_t *cfg);

/**
 * @brief get LCB data_lane of default config
 *
 * @param[out] cfg config of data_lane
 */
void lcb_get_phy_data_lane_default_config(lcb_lvds_phy_data_lane_config_t *cfg);

/**
 * @brief LCB phy0 data lane config
 *
 * @param[in] ptr LCB base address
 * @param[in] cfg config of phy0 data lane
 * @param[in] lane_id data lane id
 */
void lcb_lvds_phy0_data_lane_config(LCB_Type *ptr, lcb_lvds_phy_data_lane_config_t *cfg, lcb_lvds_phy_data_lane_id_t lane_id);

/**
 * @brief LCB phy0 clk lane config
 *
 * @param[in] ptr LCB base address
 * @param[in] cfg config of phy0 clk lane
 */
void lcb_lvds_phy0_clk_lane_config(LCB_Type *ptr, lcb_lvds_phy_clk_lane_config_t *cfg);

/**
 * @brief LCB phy1 data lane config
 *
 * @param[in] ptr LCB base address
 * @param[in] cfg config of phy1 data lane
 * @param[in] lane_id data lane id
 */
void lcb_lvds_phy1_data_lane_config(LCB_Type *ptr, lcb_lvds_phy_data_lane_config_t *cfg, lcb_lvds_phy_data_lane_id_t lane_id);

/**
 * @brief LCB phy1 clk lane config
 *
 * @param[in] ptr LCB base address
 * @param[in] cfg config of phy1 clk lane
 */
void lcb_lvds_phy1_clk_lane_config(LCB_Type *ptr, lcb_lvds_phy_clk_lane_config_t *cfg);

/**
 * @brief power on LCB phy0
 *
 * @param[in] ptr LCB base address
 */
void lcb_lvds_phy0_poweron(LCB_Type *ptr);

/**
 * @brief power on LCB phy1
 *
 * @param[in] ptr LCB base address
 */
void lcb_lvds_phy1_poweron(LCB_Type *ptr);

/**
 * @brief power down LCB phy0
 *
 * @param[in] ptr LCB base address
 */
void lcb_lvds_phy0_powerdown(LCB_Type *ptr);

/**
 * @brief power on LCB phy1
 *
 * @param[in] ptr LCB base address
 */
void lcb_lvds_phy1_powerdown(LCB_Type *ptr);

/**
 * @brief check LCB phy0 is lock
 *
 * @param[in] ptr LCB base address
 */
static inline bool lcb_lvds_phy0_dll_is_lock(LCB_Type *ptr)
{
    return !!LCB_PHY_STAT_LVDS0_RX_PHY_DLL_LOCK_GET(ptr->PHY_STAT);
}

/**
 * @brief check LCB phy1 is lock
 *
 * @param[in] ptr LCB base address
 */
static inline bool lcb_lvds_phy1_dll_is_lock(LCB_Type *ptr)
{
    return !!LCB_PHY_STAT_LVDS1_RX_PHY_DLL_LOCK_GET(ptr->PHY_STAT);
}

/**
 * @brief check LCB display phy is lock
 *
 * @param[in] ptr LCB base address
 */
static inline bool lcb_lvds_display_phy_dll_is_lock(LCB_Type *ptr)
{
    return !!LCB_PHY_STAT_LVDS0_RX_PHY_DLL_LOCK_GET(ptr->PHY_STAT) &&
            !!LCB_PHY_STAT_LVDS1_RX_PHY_DLL_LOCK_GET(ptr->PHY_STAT);
}


#ifdef __cplusplus
}
#endif

/**
 * @}
 */
#endif /* HPM_LCB_DRV_H */
