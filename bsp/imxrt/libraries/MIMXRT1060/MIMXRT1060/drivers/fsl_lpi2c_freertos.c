/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_lpi2c_freertos.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpi2c_freertos"
#endif

static void LPI2C_RTOS_Callback(LPI2C_Type *base, lpi2c_master_handle_t *drv_handle, status_t status, void *userData)
{
    lpi2c_rtos_handle_t *handle = (lpi2c_rtos_handle_t *)userData;
    BaseType_t reschedule;
    handle->async_status = status;
    (void)xSemaphoreGiveFromISR(handle->semaphore, &reschedule);
    portYIELD_FROM_ISR(reschedule);
}

/*!
 * brief Initializes LPI2C.
 *
 * This function initializes the LPI2C module and related RTOS context.
 *
 * param handle The RTOS LPI2C handle, the pointer to an allocated space for RTOS context.
 * param base The pointer base address of the LPI2C instance to initialize.
 * param masterConfig Configuration structure to set-up LPI2C in master mode.
 * param srcClock_Hz Frequency of input clock of the LPI2C module.
 * return status of the operation.
 */
status_t LPI2C_RTOS_Init(lpi2c_rtos_handle_t *handle,
                         LPI2C_Type *base,
                         const lpi2c_master_config_t *masterConfig,
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

    (void)memset(handle, 0, sizeof(lpi2c_rtos_handle_t));

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

    LPI2C_MasterInit(handle->base, masterConfig, srcClock_Hz);
    LPI2C_MasterTransferCreateHandle(base, &handle->drv_handle, LPI2C_RTOS_Callback, (void *)handle);

    return kStatus_Success;
}

/*!
 * brief Deinitializes the LPI2C.
 *
 * This function deinitializes the LPI2C module and related RTOS context.
 *
 * param handle The RTOS LPI2C handle.
 */
status_t LPI2C_RTOS_Deinit(lpi2c_rtos_handle_t *handle)
{
    LPI2C_MasterDeinit(handle->base);

    vSemaphoreDelete(handle->semaphore);
    vSemaphoreDelete(handle->mutex);

    return kStatus_Success;
}

/*!
 * brief Performs I2C transfer.
 *
 * This function performs an I2C transfer using LPI2C module according to data given in the transfer structure.
 *
 * param handle The RTOS LPI2C handle.
 * param transfer Structure specifying the transfer parameters.
 * return status of the operation.
 */
status_t LPI2C_RTOS_Transfer(lpi2c_rtos_handle_t *handle, lpi2c_master_transfer_t *transfer)
{
    status_t status;

    /* Lock resource mutex */
    if (xSemaphoreTake(handle->mutex, portMAX_DELAY) != pdTRUE)
    {
        return kStatus_LPI2C_Busy;
    }

    status = LPI2C_MasterTransferNonBlocking(handle->base, &handle->drv_handle, transfer);
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
