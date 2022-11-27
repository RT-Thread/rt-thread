/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __FSL_I2C_FREERTOS_H__
#define __FSL_I2C_FREERTOS_H__

#include "FreeRTOS.h"
#include "portable.h"
#include "semphr.h"

#include "fsl_i2c.h"

/*!
 * @addtogroup i2c_freertos_driver I2C FreeRTOS Driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief I2C FreeRTOS driver version 2.0.8. */
#define FSL_I2C_FREERTOS_DRIVER_VERSION (MAKE_VERSION(2, 0, 8))
/*@}*/

/*! @brief I2C FreeRTOS handle */
typedef struct _i2c_rtos_handle
{
    I2C_Type *base;                 /*!< I2C base address */
    i2c_master_handle_t drv_handle; /*!< A handle of the underlying driver, treated as opaque by the RTOS layer */
    status_t async_status;          /*!< Transactional state of the underlying driver */
    SemaphoreHandle_t mutex;        /*!< A mutex to lock the handle during a transfer */
    SemaphoreHandle_t semaphore;    /*!< A semaphore to notify and unblock task when the transfer ends */
#if (configSUPPORT_STATIC_ALLOCATION == 1)
    StaticSemaphore_t mutexBuffer;     /*!< Statically allocated memory for mutex */
    StaticSemaphore_t semaphoreBuffer; /*!< Statically allocated memory for semaphore */
#endif
} i2c_rtos_handle_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name I2C RTOS Operation
 * @{
 */

/*!
 * @brief Initializes I2C.
 *
 * This function initializes the I2C module and the related RTOS context.
 *
 * @param handle The RTOS I2C handle, the pointer to an allocated space for RTOS context.
 * @param base The pointer base address of the I2C instance to initialize.
 * @param masterConfig Configuration structure to set-up I2C in master mode.
 * @param srcClock_Hz Frequency of input clock of the I2C module.
 * @return status of the operation.
 */
status_t I2C_RTOS_Init(i2c_rtos_handle_t *handle,
                       I2C_Type *base,
                       const i2c_master_config_t *masterConfig,
                       uint32_t srcClock_Hz);

/*!
 * @brief Deinitializes the I2C.
 *
 * This function deinitializes the I2C module and the related RTOS context.
 *
 * @param handle The RTOS I2C handle.
 */
status_t I2C_RTOS_Deinit(i2c_rtos_handle_t *handle);

/*!
 * @brief Performs I2C transfer.
 *
 * This function performs an I2C transfer according to data given in the transfer structure.
 *
 * @param handle The RTOS I2C handle.
 * @param transfer Structure specifying the transfer parameters.
 * @return status of the operation.
 */
status_t I2C_RTOS_Transfer(i2c_rtos_handle_t *handle, i2c_master_transfer_t *transfer);

/*!
 * @}
 */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif /* __FSL_I2C_FREERTOS_H__ */
