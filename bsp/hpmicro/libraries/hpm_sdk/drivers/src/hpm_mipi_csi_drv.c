/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_mipi_csi_drv.h"


void mipi_csi_get_defconfig(mipi_csi_config_t *cfg)
{
    cfg->data_type = mipi_csi_data_type_rgb565;
    cfg->lanes = 2;
}

void mipi_csi_init(MIPI_CSI_Type *ptr, mipi_csi_config_t *cfg)
{
    ptr->CSI2_RESETN = 0x01;
    ptr->IPI_SOFTRSTN = 0x01;

    if (cfg->lanes < 1 || cfg->lanes > 2)
        cfg->lanes = 2;
    ptr->N_LANES = MIPI_CSI_N_LANES_N_LANES_SET(cfg->lanes - 1);

    /*
     * only camera mode
     */
    ptr->IPI_MODE = MIPI_CSI_IPI_MODE_IPI_ENABLE_MASK;
    ptr->IPI_DATA_TYPE = (ptr->IPI_DATA_TYPE & ~(MIPI_CSI_IPI_DATA_TYPE_IPI_DATA_TYPE_MASK)) |
                            MIPI_CSI_IPI_DATA_TYPE_IPI_DATA_TYPE_SET(cfg->data_type);

    ptr->IPI_MEM_FLASH |= MIPI_CSI_IPI_MEM_FLASH_IPI_AUTO_FLUSH_MASK;

    /*
     * [16]: 0: Controller selects it automatically
     */
    ptr->IPI_ADV_FEATURES = 0;

    ptr->IPI_HSD_TIME = 20;
    ptr->IPI_HSA_TIME = 0;
}

void mipi_csi_phy_poweron(MIPI_CSI_Type *ptr)
{
    /*
     * MIPI CSI        :   PHY
     * ----------------------------
     * PHY_SHUTDOWNZ   :   ~iddqen
     * DPHY_RSTZ       :   hw_rst_n
     */
    ptr->DPHY_RSTZ = 0x01;
    ptr->PHY_SHUTDOWNZ = 0x01;
}

void mipi_csi_phy_powerdown(MIPI_CSI_Type *ptr)
{
    /*
     * MIPI CSI        :   PHY
     * ----------------------------
     * PHY_SHUTDOWNZ   :   ~iddqen
     * DPHY_RSTZ       :   hw_rst_n
     */
    ptr->DPHY_RSTZ = 0x00;
    ptr->PHY_SHUTDOWNZ = 0x00;
}


