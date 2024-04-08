/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_soc_mipi_csi2rx.h"
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.soc_mipi_csi2rx"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

void MIPI_CSI2RX_SoftwareReset(MIPI_CSI2RX_Type *base, bool reset)
{
    if (reset)
    {
        IOMUXC_GPR->GPR59 &= ~IOMUXC_GPR_GPR59_MIPI_CSI_SOFT_RST_N_MASK;
    }
    else
    {
        IOMUXC_GPR->GPR59 |= IOMUXC_GPR_GPR59_MIPI_CSI_SOFT_RST_N_MASK;
    }
}

void MIPI_CSI2RX_InitInterface(MIPI_CSI2RX_Type *base, uint8_t tHsSettle_EscClk)
{
    /* Pixel link control */
    VIDEO_MUX->PLM_CTRL.RW = 0U;

    IOMUXC_GPR->GPR59 = (IOMUXC_GPR->GPR59 & ~(IOMUXC_GPR_GPR59_MIPI_CSI_S_PRG_RXHS_SETTLE_MASK)) |
                        IOMUXC_GPR_GPR59_MIPI_CSI_RX_ENABLE_MASK |  /* Enable RX. */
                        IOMUXC_GPR_GPR59_MIPI_CSI_AUTO_PD_EN_MASK | /* Auto power down unused lanes. */
                        IOMUXC_GPR_GPR59_MIPI_CSI_SOFT_RST_N_MASK | IOMUXC_GPR_GPR59_MIPI_CSI_PD_RX_MASK |
                        IOMUXC_GPR_GPR59_MIPI_CSI_DDRCLK_EN_MASK |      /* Enable the DDR clock. */
                        IOMUXC_GPR_GPR59_MIPI_CSI_CONT_CLK_MODE_MASK | /* Continue clock. */
                        IOMUXC_GPR_GPR59_MIPI_CSI_S_PRG_RXHS_SETTLE(tHsSettle_EscClk - 1UL); /* T(HS-SETTLE) */

    /* Don't mask any data type */
    VIDEO_MUX->CFG_DT_DISABLE.RW = 0U;

    /* Enable pixel link master. */
    VIDEO_MUX->PLM_CTRL.SET = (VIDEO_MUX_PLM_CTRL_ENABLE_MASK | VIDEO_MUX_PLM_CTRL_VALID_OVERRIDE_MASK);

    /* Power up PHY. */
    IOMUXC_GPR->GPR59 &= ~IOMUXC_GPR_GPR59_MIPI_CSI_PD_RX_MASK;
}

void MIPI_CSI2RX_DeinitInterface(MIPI_CSI2RX_Type *base)
{
    IOMUXC_GPR->GPR59 = (IOMUXC_GPR->GPR59 & (~IOMUXC_GPR_GPR59_MIPI_CSI_RX_ENABLE_MASK)) | IOMUXC_GPR_GPR59_MIPI_CSI_PD_RX_MASK;

    /* Pixel link control */
    VIDEO_MUX->PLM_CTRL.RW = 0U;
}
