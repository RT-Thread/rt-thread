/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021, 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_INPUTMUX_H_
#define FSL_INPUTMUX_H_

#include "fsl_inputmux_connections.h"
#include "fsl_common.h"

/*!
 * @addtogroup inputmux_driver
 * @{
 */

/*! @file */
/*! @file fsl_inputmux_connections.h */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief Group interrupt driver version for SDK */
#define FSL_INPUTMUX_DRIVER_VERSION (MAKE_VERSION(2, 0, 7))
/*! @} */

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief	Initialize INPUTMUX peripheral.

 * This function enables the INPUTMUX clock.
 *
 * @param base Base address of the INPUTMUX peripheral.
 *
 * @retval None.
 */
void INPUTMUX_Init(INPUTMUX_Type *base);

/*!
 * @brief Attaches a signal
 *
 * This function attaches multiplexed signals from INPUTMUX to target signals.
 * For example, to attach GPIO PORT0 Pin 5 to PINT peripheral, do the following:
 * @code
 *      INPUTMUX_AttachSignal(INPUTMUX, 2, kINPUTMUX_GpioPort0Pin5ToPintsel);
 * @endcode
 * In this example, INTMUX has 8 registers for PINT, PINT_SEL0~PINT_SEL7.
 * With parameter @p index specified as 2, this function configures register PINT_SEL2.
 *
 * @param base Base address of the INPUTMUX peripheral.
 * @param index The serial number of destination register in the group of INPUTMUX registers with same name.
 * @param connection Applies signal from source signals collection to target signal.
 *
 * @retval None.
 */
void INPUTMUX_AttachSignal(INPUTMUX_Type *base, uint32_t index, inputmux_connection_t connection);

#if defined(FSL_FEATURE_INPUTMUX_HAS_SIGNAL_ENA)
/*!
 * @brief Enable/disable a signal
 *
 * This function gates the INPUTPMUX clock.
 *
 * @param base Base address of the INPUTMUX peripheral.
 * @param signal Enable signal register id and bit offset.
 * @param enable Selects enable or disable.
 *
 * @retval None.
 */
void INPUTMUX_EnableSignal(INPUTMUX_Type *base, inputmux_signal_t signal, bool enable);
#endif

/*!
 * @brief	Deinitialize INPUTMUX peripheral.

 * This function disables the INPUTMUX clock.
 *
 * @param base Base address of the INPUTMUX peripheral.
 *
 * @retval None.
 */
void INPUTMUX_Deinit(INPUTMUX_Type *base);

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* FSL_INPUTMUX_H_ */
