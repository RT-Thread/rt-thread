/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_MIPI_CSI_DRV_H
#define HPM_MIPI_CSI_DRV_H

/**
 * @brief MIPI_CSI APIs
 * @defgroup mipi_csi_interface MIPI_CSI driver APIs
 * @ingroup mipi_csi_interfaces
 * @{
 */

#include "hpm_common.h"
#include "hpm_soc.h"
#include "hpm_mipi_csi_regs.h"

#define MIPI_CSI_PHY_STOP_MASK_CLK_LANE (0x01u<<16)
#define MIPI_CSI_PHY_STOP_MASK_DATA1_LANE (0x01u<<1)
#define MIPI_CSI_PHY_STOP_MASK_DATA0_LANE (0x01u<<0)


typedef enum mipi_csi_data_type {
    mipi_csi_data_type_yuv420_8bit = 0x18,
    mipi_csi_data_type_yuv422_8bit = 0x1e,
    mipi_csi_data_type_rgb565 = 0x22,
    mipi_csi_data_type_rgb666 = 0x23,
    mipi_csi_data_type_rgb888 = 0x24,
} mipi_csi_data_type_t;

typedef struct mipi_csi_config {
    uint8_t lanes; /* !< max: 2. number of lane*/
    mipi_csi_data_type_t data_type;
} mipi_csi_config_t;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief get MIPI_CSI default config
 *
 * @param cfg: MIPI_CSI default config
 */
void mipi_csi_get_defconfig(mipi_csi_config_t *cfg);

/**
 * @brief MIPI_CSI init
 *
 * @param ptr MIPI_CSI base address
 * @param cfg config of MIPI_CSI
 */
void mipi_csi_init(MIPI_CSI_Type *ptr, mipi_csi_config_t *cfg);

/**
 * @brief MIPI_CSI phy interface power on
 *
 * @param ptr MIPI_DCI base address
 */
void mipi_csi_phy_poweron(MIPI_CSI_Type *ptr);

/**
 * @brief MIPI_CSI phy interface power down
 *
 * @param ptr MIPI_CSI base address
 */
void mipi_csi_phy_powerdown(MIPI_CSI_Type *ptr);

/**
 * @brief MIPI_CSI check clklane whether on HS state
 *
 * @param ptr MIPI_DCI base address
 * @return: true on HS or false not on HS.
 */
static inline bool mipi_csi_clklane_is_entry_hs(MIPI_CSI_Type *ptr)
{
    return !!(ptr->PHY_RX & MIPI_CSI_PHY_RX_PHY_RXCLKACTIVEHS_MASK);
}


#ifdef __cplusplus
}
#endif

/**
 * @}
 */
#endif /* HPM_MIPI_CSI_DRV_H */
