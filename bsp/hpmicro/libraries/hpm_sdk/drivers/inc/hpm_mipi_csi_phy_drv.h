/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_MIPI_CSI_PHY_DRV_H
#define HPM_MIPI_CSI_PHY_DRV_H

/**
 * @brief MIPI_CSI_PHY APIs
 * @defgroup mipi_csi_phy_interface MIPI_CSI_PHY driver APIs
 * @ingroup mipi_csi_phy_interfaces
 * @{
 */

#include "hpm_common.h"
#include "hpm_soc.h"
#include "hpm_mipi_csi_phy_regs.h"


typedef struct mipi_csi_phy_clane_config {
    uint16_t t_term_en_ns; /* !< unit:  nanosecond. Time for the Clock Lane receiver to enable the HS line termination, starting from the time point when Dn crosses VIL,MAX */
    uint16_t t_settle_ns; /* !< unit:  nanosecond. Time interval during which the HS receiver should ignore any  Clock Lane HS transitions, starting from the beginning of TCLK-PREPARE */
} mipi_csi_phy_clane_config_t;

typedef struct mipi_csi_phy_dlane_config {
    uint16_t t_term_en_ns; /* !< unit:  nanosecond. Time for the Data Lane receiver to enable the HS line termination, starting from the time point when Dn crosses VIL,MAX */
    uint16_t t_settle_ns;  /* !< unit:  nanosecond. Time interval during which the HS receiver shall ignore any Data Lane HS transitions, starting from the beginning of THS-PREPARE */
} mipi_csi_phy_dlane_config_t;

typedef struct mipi_csi_phy_config {
    mipi_csi_phy_clane_config_t clane_cfg; /*!< clk lane config */
    mipi_csi_phy_dlane_config_t dlane_cfg; /*!< data lane config */
} mipi_csi_phy_config_t;



/**
 * @brief get MIPI CSI PHY of default config
 *
 * @param[out] cfg config of MIPI CSI PHY
 */
void mipi_csi_phy_default_config(mipi_csi_phy_config_t *cfg);

/**
 * @brief MIPI_CSI_PHY init
 *
 * @param ptr MIPI_CSI_PHY base address
 * @param cfg config of MIPI_CSI_PHY
 */
void mipi_csi_phy_init(MIPI_CSI_PHY_Type *ptr, mipi_csi_phy_config_t *cfg);

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

/**
 * @}
 */
#endif /* HPM_MIPI_CSI_PHY_DRV_H */
