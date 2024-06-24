/*
 * Copyright 2019-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_SMARTDMA_H_
#define FSL_SMARTDMA_H_

#include "fsl_common.h"

#if defined(MIMXRT533S_SERIES) || defined(MIMXRT555S_SERIES) || defined(MIMXRT595S_cm33_SERIES)
#include "fsl_smartdma_rt500.h"
#elif defined(MCXN546_cm33_core0_SERIES) || defined(MCXN546_cm33_core1_SERIES) ||                                     \
    defined(MCXN547_cm33_core0_SERIES) || defined(MCXN547_cm33_core1_SERIES) || defined(MCXN946_cm33_core0_SERIES) || \
    defined(MCXN946_cm33_core1_SERIES) || defined(MCXN947_cm33_core0_SERIES) || defined(MCXN947_cm33_core1_SERIES) || \
    defined(MCXN236_SERIES) || defined(MCXN235_SERIES)
#include "fsl_smartdma_mcxn.h"
#else
#error "Device not supported"
#endif

/*!
 * @addtogroup smartdma
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief SMARTDMA driver version */
#define FSL_SMARTDMA_DRIVER_VERSION (MAKE_VERSION(2, 9, 1))
/*@}*/

/*! @brief Callback function prototype for the smartdma driver. */
typedef void (*smartdma_callback_t)(void *param);

/*******************************************************************************
 * APIs
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Initialize the SMARTDMA.
 *
 * @param apiMemAddr The address firmware will be copied to.
 * @param firmware The firmware to use.
 * @param firmwareSizeByte Size of firmware.
 * @deprecated Do not use this function. It has been superceded by
 * @ref SMARTDMA_InitWithoutFirmware and @ref SMARTDMA_InstallFirmware.
 */
void SMARTDMA_Init(uint32_t apiMemAddr, const void *firmware, uint32_t firmwareSizeByte);

/*!
 * @brief Initialize the SMARTDMA.
 *
 * This function is similar with @ref SMARTDMA_Init, the difference is this function
 * does not install the firmware, the firmware could be installed using
 * @ref SMARTDMA_InstallFirmware.
 */
void SMARTDMA_InitWithoutFirmware(void);

/*!
 * @brief Install the firmware.
 *
 * @param apiMemAddr The address firmware will be copied to.
 * @param firmware The firmware to use.
 * @param firmwareSizeByte Size of firmware.
 * @note Only call this function when SMARTDMA is not busy.
 */
void SMARTDMA_InstallFirmware(uint32_t apiMemAddr, const void *firmware, uint32_t firmwareSizeByte);

/*!
 * @brief Install the complete callback function.
 *
 * @param callback The callback called when smartdma program finished.
 * @param param Parameter for the callback.
 * @note Only call this function when SMARTDMA is not busy.
 */
void SMARTDMA_InstallCallback(smartdma_callback_t callback, void *param);

/*!
 * @brief Boot the SMARTDMA to run program.
 *
 * @param apiIndex Index of the API to call.
 * @param pParam Pointer to the parameter allocated by caller.
 * @param mask Value set to register SMARTDMA->ARM2EZH[0:1].
 * @note Only call this function when SMARTDMA is not busy.
 * @note The memory *pParam shall not be freed before the SMARTDMA function finished.
 */
void SMARTDMA_Boot(uint32_t apiIndex, void *pParam, uint8_t mask);

/*!
 * @brief Copy SMARTDMA params and Boot to run program.
 *
 * This function is similar with @ref SMARTDMA_Boot, the only difference
 * is, this function copies the *pParam to a local variable, upper layer
 * can free the pParam's memory before the SMARTDMA execution finished,
 * for example, upper layer can define the param as a local variable.
 *
 * @param apiIndex Index of the API to call.
 * @param pParam Pointer to the parameter.
 * @param mask Value set to SMARTDMA_ARM2SMARTDMA[0:1].
 * @note Only call this function when SMARTDMA is not busy.
 */
void SMARTDMA_Boot1(uint32_t apiIndex, const smartdma_param_t *pParam, uint8_t mask);

/*!
 * @brief Deinitialize the SMARTDMA.
 */
void SMARTDMA_Deinit(void);

/*!
 * @brief Reset the SMARTDMA.
 */
void SMARTDMA_Reset(void);

/*!
 * @brief SMARTDMA IRQ.
 */
void SMARTDMA_HandleIRQ(void);

#if defined(__cplusplus)
}
#endif

/* @} */

#endif /* FSL_SMARTDMA_H_ */
