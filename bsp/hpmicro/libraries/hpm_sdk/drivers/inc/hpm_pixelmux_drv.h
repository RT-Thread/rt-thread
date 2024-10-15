/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PIXELMUX_DRV_H
#define HPM_PIXELMUX_DRV_H

/**
 * @brief PIXELMUX APIs
 * @defgroup pixelmux_interface PIXELMUX driver APIs
 * @ingroup pixelmux_interfaces
 * @{
 */

#include "hpm_common.h"
#include "hpm_soc.h"
#include "hpm_pixelmux_regs.h"

/**
 * @brief rgb interface pixel data source
 */
typedef enum {
    pixelmux_rgb_sel_lcdc0 = 0,
    pixelmux_rgb_sel_lcdc1
} pixelmux_rgb_select_t;

/**
 * @brief gwc1 pixel data source
 */
typedef enum {
    pixelmux_gwc1_sel_lcdc0 = 0,
    pixelmux_gwc1_sel_lcdc1
} pixelmux_gwc1_select_t;

/**
 * @brief gwc0 pixel data source
 */
typedef enum {
    pixelmux_gwc0_sel_lcdc0 = 0,
    pixelmux_gwc0_sel_lcdc1
} pixelmux_gwc0_select_t;

/**
 * @brief lvb di1 pixel data source
 */
typedef enum {
    pixelmux_lvb_di1_sel_lcdc0 = 0,
    pixelmux_lvb_di1_sel_lcdc1
} pixelmux_lvb_di1_select_t;

/**
 * @brief lvb di0 pixel data source
 */
typedef enum {
    pixelmux_lvb_di0_sel_lcdc0 = 0,
    pixelmux_lvb_di0_sel_lcdc1
} pixelmux_lvb_di0_select_t;

/**
 * @brief mipi dsi1 pixel data source
 */
typedef enum {
    pixelmux_mipi_dsi1_sel_lcdc0 = 0,
    pixelmux_mipi_dsi1_sel_lcdc1
} pixelmux_mipi_dsi1_select_t;

/**
 * @brief mipi dsi0 pixel data source
 */
typedef enum {
    pixelmux_mipi_dsi0_sel_lcdc0 = 0,
    pixelmux_mipi_dsi0_sel_lcdc1
} pixelmux_mipi_dsi0_select_t;

/**
 * @brief mipi dsi pixel data type
 */
typedef enum {
    pixelmux_mipi_dsi_data_type_rgb565 = 0,
    pixelmux_mipi_dsi_data_type_rgb666 = 3,
    pixelmux_mipi_dsi_data_type_rgb666_packed = 4,
    pixelmux_mipi_dsi_data_type_rgb888 = 5,
} pixelmux_mipi_dsi_data_type_t;

/**
 * @brief cam1 pixel data source
 */
typedef enum {
    pixelmux_cam1_sel_dvp = 0,
    pixelmux_cam1_sel_mipi_csi0,
    pixelmux_cam1_sel_mipi_csi1,
    pixelmux_cam1_sel_lcdc0,
    pixelmux_cam1_sel_lcdc1,
    pixelmux_cam1_sel_lcb_do0,
    pixelmux_cam1_sel_lcb_do1,
} pixelmux_cam1_select_t;

/**
 * @brief cam0 pixel data source
 */
typedef enum {
    pixelmux_cam0_sel_dvp = 0,
    pixelmux_cam0_sel_mipi_csi0,
    pixelmux_cam0_sel_mipi_csi1,
    pixelmux_cam0_sel_lcdc0,
    pixelmux_cam0_sel_lcdc1,
    pixelmux_cam0_sel_lcb_do0,
    pixelmux_cam0_sel_lcb_do1,
} pixelmux_cam0_select_t;

#define PIXELMUX_LVDS_TX_PHY_PFD_FREQ_MAX 40000000UL
#define PIXELMUX_LVDS_TX_PHY_PFD_FREQ_MIN 10000000UL

#define PIXELMUX_LVDS_TX_PHY_VCO_FREQ_MAX 4000000000UL
#define PIXELMUX_LVDS_TX_PHY_VCO_FREQ_MIN 2000000000UL

#define PIXELMUX_LVDS_TX_PHY_DATA_LANE_FREQ_MAX 1000000000UL

typedef struct lvds_phy_clk_reg {
    uint32_t rate_lvds; /*!< rate_lvds[1:0] */
    uint32_t data_rate_div4;
    uint32_t refclk_div; /*!< refclk_div[3:0] */
    uint32_t pll_div; /*!< pll_div[14:0] */
} lvds_phy_clk_reg_t;

typedef struct lvds_phy_clk_param {
    lvds_phy_clk_reg_t reg;
    uint32_t fvco_freq_hz;
    uint32_t pfd_freq_hz;
    uint32_t lane_data_rate_hz;
    uint32_t hsclk_freq_hz;
} lvds_phy_clk_param_t;

typedef enum pixelmux_tx_phy_mode {
    pixelmux_tx_phy_mode_gpio = 0,
    pixelmux_tx_phy_mode_lvds = 1,
    pixelmux_tx_phy_mode_mipi = 2
} pixelmux_tx_phy_mode_t;

typedef enum pixelmux_rx_phy_mode {
    pixelmux_rx_phy_mode_gpio = 0,
    pixelmux_rx_phy_mode_lvds = 1,
    pixelmux_rx_phy_mode_mipi = 2,
    pixelmux_rx_phy_mode_lvds_camera = 3
} pixelmux_rx_phy_mode_t;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief select pixel data source and enable for rgb interface
 *
 * @param[in] src rgb pixel data source options
 */
void pixelmux_rgb_data_source_enable(pixelmux_rgb_select_t src);

/**
 * @brief disable rgb interface pixel data source
 */
void pixelmux_rgb_data_source_disable(void);

/**
 * @brief select pixel data source and enable for gwc1
 *
 * @param[in] src gwc1 pixel data source options
 */
void pixelmux_gwc1_data_source_enable(pixelmux_gwc1_select_t src);

/**
 * @brief disable gwc1 pixel data source
 */
void pixelmux_gwc1_data_source_disable(void);

/**
 * @brief select pixel data source and enable for gwc0
 *
 * @param[in] src gwc0 pixel data source options
 */
void pixelmux_gwc0_data_source_enable(pixelmux_gwc0_select_t src);

/**
 * @brief disable gwc0 pixel data source
 */
void pixelmux_gwc0_data_source_disable(void);

/**
 * @brief select pixel data source and enable for lvb di1
 *
 * @param[in] src lvb di1 pixel data source options
 */
void pixelmux_lvb_di1_data_source_enable(pixelmux_lvb_di1_select_t src);

/**
 * @brief disable lvb di1 pixel data source
 */
void pixelmux_lvb_di1_data_source_disable(void);

/**
 * @brief select pixel data source and enable for lvb di0
 *
 * @param[in] src lvb di0 pixel data source options
 */
void pixelmux_lvb_di0_data_source_enable(pixelmux_lvb_di0_select_t src);

/**
 * @brief disable lvb di0 pixel data source
 */
void pixelmux_lvb_di0_data_source_disable(void);

/**
 * @brief select pixel data source and enable for mipi dsi1
 *
 * @param[in] src mipi dsi1 pixel data source options
 */
void pixelmux_mipi_dsi1_data_source_enable(pixelmux_mipi_dsi1_select_t src);

/**
 * @brief disable mipi dis1 pixel data source
 */
void pixelmux_mipi_dsi1_data_source_disable(void);

/**
 * @brief select pixel data source and enable for mipi dsi0
 *
 * @param[in] src mipi dsi0 pixel data source options
 */
void pixelmux_mipi_dsi0_data_source_enable(pixelmux_mipi_dsi0_select_t src);

/**
 * @brief disable mipi dsi0 pixel data source
 */
void pixelmux_mipi_dsi0_data_source_disable(void);

/**
 * @brief set data type for mipi dsi1
 *
 * @param[in] type mipi dsi data type
 */
void pixelmux_mipi_dsi1_set_data_type(pixelmux_mipi_dsi_data_type_t type);

/**
 * @brief set data type for mipi dsi0
 *
 * @param[in] type mipi dsi data type
 */
void pixelmux_mipi_dsi0_set_data_type(pixelmux_mipi_dsi_data_type_t type);

/**
 * @brief select pixel data source and enable for camera1
 *
 * @param[in] src camera1 pixel data source options
 */
void pixelmux_cam1_data_source_enable(pixelmux_cam1_select_t src);

/**
 * @brief disable camera1 pixel data source
 */
void pixelmux_cam1_data_source_disable(void);

/**
 * @brief select pixel data source and enable for camera0
 *
 * @param[in] src camera0 pixel data source options
 */
void pixelmux_cam0_data_source_enable(pixelmux_cam0_select_t src);

/**
 * @brief disable camera0 pixel data source
 */
void pixelmux_cam0_data_source_disable(void);

/**
 * @brief calculate pll config base pixel frequency
 *
 * @param[in] pixel_freq_hz lcdc pixel frequency
 * @param[in] is_split 1: enable split mode, 0: disable split mode
 * @param[out] param use for lvds phy config
 * @return status
 */
hpm_stat_t pixelmux_lvds_phy_calc_pll_cfg(uint32_t pixel_freq_hz, bool is_split, lvds_phy_clk_param_t *param);

/**
 * @brief config tx phy0 mode
 *
 * @param[in] mode phy mode
 */
void pixelmux_config_tx_phy0_mode(pixelmux_tx_phy_mode_t mode);

/**
 * @brief config tx phy1 mode
 *
 * @param[in] mode phy mode
 */
void pixelmux_config_tx_phy1_mode(pixelmux_tx_phy_mode_t mode);

/**
 * @brief config lvds tx phy0 clock
 *
 * @param[in] clk_reg phy register config
 */
void pixelmux_config_lvds_tx_phy0_clk(const lvds_phy_clk_reg_t *clk_reg);

/**
 * @brief config lvds tx phy1 clock
 *
 * @param[in] clk_reg phy register config
 */
void pixelmux_config_lvds_tx_phy1_clk(const lvds_phy_clk_reg_t *clk_reg);

/**
 * @brief config rx phy0 mode
 *
 * @param[in] mode phy mode
 */
void pixelmux_config_rx_phy0_mode(pixelmux_rx_phy_mode_t mode);

/**
 * @brief config rx phy1 mode
 *
 * @param[in] mode phy mode
 */
void pixelmux_config_rx_phy1_mode(pixelmux_rx_phy_mode_t mode);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */
#endif /* HPM_PIXELMUX_DRV_H */
