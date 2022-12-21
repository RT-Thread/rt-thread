/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __FSL_SPI_FREERTOS_H__
#define __FSL_SPI_FREERTOS_H__

#include "FreeRTOS.h"
#include "portable.h"
#include "semphr.h"

#include "fsl_spi.h"

/*!
 * @addtogroup spi_freertos_driver
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief SPI FreeRTOS driver version 2.1.0. */
#define FSL_SPI_FREERTOS_DRIVER_VERSION (MAKE_VERSION(2, 1, 0))
/*@}*/

/*! @brief SPI FreeRTOS handle */
typedef struct _spi_rtos_handle
{
    SPI_Type *base;                 /*!< SPI base address */
    spi_master_handle_t drv_handle; /*!< Handle of the underlying driver, treated as opaque by the RTOS layer */
    status_t async_status;
    SemaphoreHandle_t mutex; /*!< Mutex to lock the handle during a trasfer */
    SemaphoreHandle_t event; /*!< Semaphore to notify and unblock task when transfer ends */
} spi_rtos_handle_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name SPI RTOS Operation
 * @{
 */

/*!
 * @brief Initializes SPI.
 *
 * This function initializes the SPI module and related RTOS context.
 *
 * @param handle The RTOS SPI handle, the pointer to an allocated space for RTOS context.
 * @param base The pointer base address of the SPI instance to initialize.
 * @param masterConfig Configuration structure to set-up SPI in master mode.
 * @param srcClock_Hz Frequency of input clock of the SPI module.
 * @return status of the operation.
 */
status_t SPI_RTOS_Init(spi_rtos_handle_t *handle,
                       SPI_Type *base,
                       const spi_master_config_t *masterConfig,
                       uint32_t srcClock_Hz);

/*!
 * @brief Deinitializes the SPI.
 *
 * This function deinitializes the SPI module and related RTOS context.
 *
 * @param handle The RTOS SPI handle.
 */
status_t SPI_RTOS_Deinit(spi_rtos_handle_t *handle);

/*!
 * @brief Performs SPI transfer.
 *
 * This function performs an SPI transfer according to data given in the transfer structure.
 *
 * @param handle The RTOS SPI handle.
 * @param transfer Structure specifying the transfer parameters.
 * @return status of the operation.
 */
status_t SPI_RTOS_Transfer(spi_rtos_handle_t *handle, spi_transfer_t *transfer);

/*!
 * @}
 */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif /* __FSL_SPI_FREERTOS_H__ */
