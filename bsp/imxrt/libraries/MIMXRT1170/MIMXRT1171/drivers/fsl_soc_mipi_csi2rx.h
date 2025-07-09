/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SOC_MIPI_CSI2RX_H_
#define _FSL_SOC_MIPI_CSI2RX_H_

#include "fsl_common.h"

/*! @addtogroup soc_mipi_csi2rx */
/*! @{ */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Driver version. */
#define FSL_SOC_MIPI_CSI2RX_DRIVER_VERSION (MAKE_VERSION(2, 0, 2))

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Assert or deassert CSI2RX reset in system level.
 *
 * @param base The CSI2RX peripheral base address.
 * @param reset Pass in true to set to reset state, false to release reset.
 * @note Don't call this function directly.
 */
void MIPI_CSI2RX_SoftwareReset(MIPI_CSI2RX_Type *base, bool reset);

/*!
 * @brief Initialize the CSI2RX interface.
 *
 * @param base The CSI2RX peripheral base address.
 * @param tHsSettle_EscClk t-HS_SETTLE in esc clock period.
 * @note Don't call this function directly.
 */
void MIPI_CSI2RX_InitInterface(MIPI_CSI2RX_Type *base, uint8_t tHsSettle_EscClk);

/*!
 * @brief Deinitialize the CSI2RX interface.
 *
 * @param base The CSI2RX peripheral base address.
 * @note Don't call this function directly.
 */
void MIPI_CSI2RX_DeinitInterface(MIPI_CSI2RX_Type *base);

/* @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_SOC_MIPI_CSI2RX_H_ */
