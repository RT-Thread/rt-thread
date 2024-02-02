/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __FSL_LPSPI_FREERTOS_H__
#define __FSL_LPSPI_FREERTOS_H__

#include "FreeRTOS.h"
#include "portable.h"
#include "semphr.h"

#include "fsl_lpspi.h"

/*!
 * @addtogroup lpspi_freertos_driver LPSPI FreeRTOS Driver
 * @{
 */

/**********************************************************************************************************************
 * Definitions
 *********************************************************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief LPSPI FreeRTOS driver version 2.3.1. */
#define FSL_LPSPI_FREERTOS_DRIVER_VERSION (MAKE_VERSION(2, 3, 1))
/*@}*/

/*!
 * @cond RTOS_PRIVATE
 * @brief LPSPI FreeRTOS handle
 */
typedef struct _lpspi_rtos_handle
{
    LPSPI_Type *base;                 /*!< LPSPI base address */
    lpspi_master_handle_t drv_handle; /*!< Handle of the underlying driver, treated as opaque by the RTOS layer */
    status_t async_status;
    SemaphoreHandle_t mutex; /*!< Mutex to lock the handle during a trasfer */
    SemaphoreHandle_t event; /*!< Semaphore to notify and unblock task when transfer ends */
} lpspi_rtos_handle_t;
/*! \endcond */

/**********************************************************************************************************************
 * API
 *********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name LPSPI RTOS Operation
 * @{
 */

/*!
 * @brief Initializes LPSPI.
 *
 * This function initializes the LPSPI module and related RTOS context.
 *
 * @param handle The RTOS LPSPI handle, the pointer to an allocated space for RTOS context.
 * @param base The pointer base address of the LPSPI instance to initialize.
 * @param masterConfig Configuration structure to set-up LPSPI in master mode.
 * @param srcClock_Hz Frequency of input clock of the LPSPI module.
 * @return status of the operation.
 */
status_t LPSPI_RTOS_Init(lpspi_rtos_handle_t *handle,
                         LPSPI_Type *base,
                         const lpspi_master_config_t *masterConfig,
                         uint32_t srcClock_Hz);

/*!
 * @brief Deinitializes the LPSPI.
 *
 * This function deinitializes the LPSPI module and related RTOS context.
 *
 * @param handle The RTOS LPSPI handle.
 */
status_t LPSPI_RTOS_Deinit(lpspi_rtos_handle_t *handle);

/*!
 * @brief Performs SPI transfer.
 *
 * This function performs an SPI transfer according to data given in the transfer structure.
 *
 * @param handle The RTOS LPSPI handle.
 * @param transfer Structure specifying the transfer parameters.
 * @return status of the operation.
 */
status_t LPSPI_RTOS_Transfer(lpspi_rtos_handle_t *handle, lpspi_transfer_t *transfer);

/*!
 * @}
 */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif /* __FSL_LPSPI_FREERTOS_H__ */
