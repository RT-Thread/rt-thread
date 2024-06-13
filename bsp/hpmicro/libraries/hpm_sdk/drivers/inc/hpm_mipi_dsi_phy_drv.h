/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_MIPI_DSI_PHY_DRV_H
#define HPM_MIPI_DSI_PHY_DRV_H

/**
 * @brief MIPI_DSI_PHY APIs
 * @defgroup mipi_dsi_phy_interface MIPI_DSI_PHY driver APIs
 * @ingroup mipi_dsi_phy_interfaces
 * @{
 */

#include "hpm_common.h"
#include "hpm_soc.h"
#include "hpm_mipi_dsi_phy_regs.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct mipi_dsi_phy_config {
    uint32_t lane_mbps; /*!< lane speed */
    uint8_t lanes;      /*!< number of lane */
} mipi_dsi_phy_config_t;

/**
 * @brief MIPI_DSI_PHY init
 *
 * @param ptr MIPI_DSI_PHY base address
 * @param cfg config of MIPI_DSI_PHY
 */
void mipi_dsi_phy_init(MIPI_DSI_PHY_Type *ptr, mipi_dsi_phy_config_t *cfg);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */
#endif /* HPM_MIPI_DSI_PHY_DRV_H */
