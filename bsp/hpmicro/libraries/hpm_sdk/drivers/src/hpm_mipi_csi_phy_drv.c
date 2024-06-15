/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_mipi_csi_phy_drv.h"

void mipi_csi_phy_default_config(mipi_csi_phy_config_t *cfg)
{
    cfg->clane_cfg.t_settle_ns = 140;
    cfg->clane_cfg.t_term_en_ns = 30;

    cfg->dlane_cfg.t_settle_ns = 100;
    cfg->dlane_cfg.t_term_en_ns = 30;
}

void mipi_csi_phy_init(MIPI_CSI_PHY_Type *ptr, mipi_csi_phy_config_t *cfg)
{
    ptr->SOFT_RST = 0x03;
    ptr->SOFT_RST = 0x00;

    ptr->CLANE_PARA = (ptr->CLANE_PARA & ~(MIPI_CSI_PHY_CLANE_PARA_T_CLK_TERMEN_MASK |
                        MIPI_CSI_PHY_CLANE_PARA_T_CLK_SETTLE_MASK)) |
                        MIPI_CSI_PHY_CLANE_PARA_T_CLK_TERMEN_SET(cfg->clane_cfg.t_term_en_ns / 10) |
                        MIPI_CSI_PHY_CLANE_PARA_T_CLK_SETTLE_SET(cfg->clane_cfg.t_settle_ns / 10);


    ptr->T_HS_TERMEN = (ptr->T_HS_TERMEN & ~(MIPI_CSI_PHY_T_HS_TERMEN_T_D1_TERMEN_MASK |
                        MIPI_CSI_PHY_T_HS_TERMEN_T_D0_TERMEN_MASK)) |
                        MIPI_CSI_PHY_T_HS_TERMEN_T_D1_TERMEN_SET(cfg->dlane_cfg.t_term_en_ns / 10) |
                        MIPI_CSI_PHY_T_HS_TERMEN_T_D0_TERMEN_SET(cfg->dlane_cfg.t_term_en_ns / 10);

    ptr->T_HS_SETTLE = (ptr->T_HS_SETTLE & ~(MIPI_CSI_PHY_T_HS_SETTLE_T_D1_SETTLE_MASK |
                        MIPI_CSI_PHY_T_HS_SETTLE_T_D0_SETTLE_MASK)) |
                        MIPI_CSI_PHY_T_HS_SETTLE_T_D1_SETTLE_SET(cfg->dlane_cfg.t_settle_ns / 10) |
                        MIPI_CSI_PHY_T_HS_SETTLE_T_D0_SETTLE_SET(cfg->dlane_cfg.t_settle_ns / 10);
}
