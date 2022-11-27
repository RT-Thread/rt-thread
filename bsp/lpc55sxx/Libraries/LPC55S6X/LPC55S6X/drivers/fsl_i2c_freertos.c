/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_i2c_freertos.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flexcomm_i2c_freertos"
#endif

static void I2C_RTOS_Callback(I2C_Type *base, i2c_master_handle_t *drv_handle, status_t status, void *userData)
{
    i2c_rtos_handle_t *handle = (i2c_rtos_handle_t *)userData;
    BaseType_t reschedule;
    handle->async_status = status;
    (void)xSemaphoreGiveFromISR(handle->semaphore, &reschedule);
    portYIELD_FROM_ISR(reschedule);
}

/*!
 * brief Initializes I2C.
 *
 * This function initializes the I2C module and the related RTOS context.
 *
 * param handle The RTOS I2C handle, the pointer to an allocated space for RTOS context.
 * param base The pointer base address of the I2C instance to initialize.
 * param masterConfig Configuration structure to set-up I2C in master mode.
 * param srcClock_Hz Frequency of input clock of the I2C module.
 * return status of the operation.
 */
status_t I2C_RTOS_Init(i2c_rtos_handle_t *handle,
                       I2C_Type *base,
                       const i2c_master_config_t *masterConfig,
                       uint32_t srcClock_Hz)
{
    if (handle == NULL)
    {
        return kStatus_InvalidArgument;
    }

    if (base == NULL)
    {
        return kStatus_InvalidArgument;
    }

    (void)memset(handle, 0, sizeof(i2c_rtos_handle_t));

    handle->mutex = xSemaphoreCreateMutex();
    if (handle->mutex == NULL)
    {
        return kStatus_Fail;
    }

    handle->semaphore = xSemaphoreCreateBinary();
    if (handle->semaphore == NULL)
    {
        vSemaphoreDelete(handle->mutex);
        return kStatus_Fail;
    }

    handle->base = base;

    I2C_MasterInit(handle->base, masterConfig, srcClock_Hz);
    I2C_MasterTransferCreateHandle(base, &handle->drv_handle, I2C_RTOS_Callback, (void *)handle);

    return kStatus_Success;
}

/*!
 * brief Deinitializes the I2C.
 *
 * This function deinitializes the I2C module and the related RTOS context.
 *
 * param handle The RTOS I2C handle.
 */
status_t I2C_RTOS_Deinit(i2c_rtos_handle_t *handle)
{
    I2C_MasterDeinit(handle->base);

    vSemaphoreDelete(handle->semaphore);
    vSemaphoreDelete(handle->mutex);

    return kStatus_Success;
}

/*!
 * brief Performs I2C transfer.
 *
 * This function performs an I2C transfer according to data given in the transfer structure.
 *
 * param handle The RTOS I2C handle.
 * param transfer Structure specifying the transfer parameters.
 * return status of the operation.
 */
status_t I2C_RTOS_Transfer(i2c_rtos_handle_t *handle, i2c_master_transfer_t *transfer)
{
    status_t status;

    /* Lock resource mutex */
    if (xSemaphoreTake(handle->mutex, portMAX_DELAY) != pdTRUE)
    {
        return kStatus_I2C_Busy;
    }

    status = I2C_MasterTransferNonBlocking(handle->base, &handle->drv_handle, transfer);
    if (status != kStatus_Success)
    {
        (void)xSemaphoreGive(handle->mutex);
        return status;
    }

    /* Wait for transfer to finish */
    (void)xSemaphoreTake(handle->semaphore, portMAX_DELAY);

    /* Unlock resource mutex */
    (void)xSemaphoreGive(handle->mutex);

    /* Return status captured by callback function */
    return handle->async_status;
}
