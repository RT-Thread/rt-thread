/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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

    xSemaphoreGiveFromISR(handle->semaphore, &reschedule);
    portYIELD_FROM_ISR(reschedule);
}

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

    memset(handle, 0, sizeof(lpi2c_rtos_handle_t));

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

status_t LPI2C_RTOS_Deinit(lpi2c_rtos_handle_t *handle)
{
    LPI2C_MasterDeinit(handle->base);

    vSemaphoreDelete(handle->semaphore);
    vSemaphoreDelete(handle->mutex);

    return kStatus_Success;
}

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
        xSemaphoreGive(handle->mutex);
        return status;
    }

    /* Wait for transfer to finish */
    xSemaphoreTake(handle->semaphore, portMAX_DELAY);

    /* Unlock resource mutex */
    xSemaphoreGive(handle->mutex);

    /* Return status captured by callback function */
    return handle->async_status;
}
