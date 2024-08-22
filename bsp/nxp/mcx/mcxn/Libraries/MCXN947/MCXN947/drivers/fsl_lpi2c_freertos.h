/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FSL_LPI2C_FREERTOS_H__
#define __FSL_LPI2C_FREERTOS_H__

#include "FreeRTOS.h"
#include "portable.h"
#include "semphr.h"

#include "fsl_lpi2c.h"

/*!
 * @addtogroup lpi2c_freertos_driver LPI2C FreeRTOS Driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief LPI2C FreeRTOS driver version 2.0.0. */
#define FSL_LPI2C_FREERTOS_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/*! @brief LPI2C FreeRTOS handle */
typedef struct _lpi2c_rtos_handle
{
    LPI2C_Type *base;                 /*!< LPI2C base address */
    lpi2c_master_handle_t drv_handle; /*!< A handle of the underlying driver, treated as opaque by the RTOS layer */
    status_t async_status;            /*!< Transactional state of the underlying driver */
    SemaphoreHandle_t mutex;          /*!< A mutex to lock the handle during a transfer */
    SemaphoreHandle_t semaphore;      /*!< A semaphore to notify and unblock task when the transfer ends */
#if (configSUPPORT_STATIC_ALLOCATION == 1)
    StaticSemaphore_t mutexBuffer;     /*!< Statically allocated memory for mutex */
    StaticSemaphore_t semaphoreBuffer; /*!< Statically allocated memory for semaphore */
#endif
} lpi2c_rtos_handle_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name LPI2C RTOS Operation
 * @{
 */

/*!
 * @brief Initializes LPI2C.
 *
 * This function initializes the LPI2C module and the related RTOS context.
 *
 * @param handle The RTOS LPI2C handle, the pointer to an allocated space for RTOS context.
 * @param base The pointer base address of the LPI2C instance to initialize.
 * @param masterConfig Configuration structure to set-up LPI2C in master mode.
 * @param srcClock_Hz Frequency of input clock of the LPI2C module.
 * @return status of the operation.
 */
status_t LPI2C_RTOS_Init(lpi2c_rtos_handle_t *handle,
                         LPI2C_Type *base,
                         const lpi2c_master_config_t *masterConfig,
                         uint32_t srcClock_Hz);

/*!
 * @brief Deinitializes the LPI2C.
 *
 * This function deinitializes the LPI2C module and the related RTOS context.
 *
 * @param handle The RTOS LPI2C handle.
 */
status_t LPI2C_RTOS_Deinit(lpi2c_rtos_handle_t *handle);

/*!
 * @brief Performs LPI2C transfer.
 *
 * This function performs an LPI2C transfer according to data given in the transfer structure.
 *
 * @param handle The RTOS LPI2C handle.
 * @param transfer Structure specifying the transfer parameters.
 * @return status of the operation.
 */
status_t LPI2C_RTOS_Transfer(lpi2c_rtos_handle_t *handle, lpi2c_master_transfer_t *transfer);

/*!
 * @}
 */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif /* __FSL_LPI2C_FREERTOS_H__ */
