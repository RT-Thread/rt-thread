/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_lpspi_freertos.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpspi_freertos"
#endif

static void LPSPI_RTOS_Callback(LPSPI_Type *base, lpspi_master_handle_t *drv_handle, status_t status, void *userData)
{
    lpspi_rtos_handle_t *handle = (lpspi_rtos_handle_t *)userData;
    BaseType_t reschedule;
    handle->async_status = status;
    (void)xSemaphoreGiveFromISR(handle->event, &reschedule);
    portYIELD_FROM_ISR(reschedule);
}

/*!
 * brief Initializes LPSPI.
 *
 * This function initializes the LPSPI module and related RTOS context.
 *
 * param handle The RTOS LPSPI handle, the pointer to an allocated space for RTOS context.
 * param base The pointer base address of the LPSPI instance to initialize.
 * param masterConfig Configuration structure to set-up LPSPI in master mode.
 * param srcClock_Hz Frequency of input clock of the LPSPI module.
 * return status of the operation.
 */
status_t LPSPI_RTOS_Init(lpspi_rtos_handle_t *handle,
                         LPSPI_Type *base,
                         const lpspi_master_config_t *masterConfig,
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

    (void)memset(handle, 0, sizeof(lpspi_rtos_handle_t));

    handle->mutex = xSemaphoreCreateMutex();
    if (handle->mutex == NULL)
    {
        return kStatus_Fail;
    }

    handle->event = xSemaphoreCreateBinary();
    if (handle->event == NULL)
    {
        vSemaphoreDelete(handle->mutex);
        return kStatus_Fail;
    }

    handle->base = base;

    LPSPI_MasterInit(handle->base, masterConfig, srcClock_Hz);
    LPSPI_MasterTransferCreateHandle(handle->base, &handle->drv_handle, LPSPI_RTOS_Callback, (void *)handle);

    return kStatus_Success;
}

/*!
 * brief Deinitializes the LPSPI.
 *
 * This function deinitializes the LPSPI module and related RTOS context.
 *
 * param handle The RTOS LPSPI handle.
 */
status_t LPSPI_RTOS_Deinit(lpspi_rtos_handle_t *handle)
{
    LPSPI_Deinit(handle->base);
    vSemaphoreDelete(handle->event);
    vSemaphoreDelete(handle->mutex);

    return kStatus_Success;
}

/*!
 * brief Performs SPI transfer.
 *
 * This function performs an SPI transfer according to data given in the transfer structure.
 *
 * param handle The RTOS LPSPI handle.
 * param transfer Structure specifying the transfer parameters.
 * return status of the operation.
 */
status_t LPSPI_RTOS_Transfer(lpspi_rtos_handle_t *handle, lpspi_transfer_t *transfer)
{
    status_t status;

    /* Lock resource mutex */
    if (xSemaphoreTake(handle->mutex, portMAX_DELAY) != pdTRUE)
    {
        return kStatus_LPSPI_Busy;
    }

    status = LPSPI_MasterTransferNonBlocking(handle->base, &handle->drv_handle, transfer);
    if (status != kStatus_Success)
    {
        (void)xSemaphoreGive(handle->mutex);
        return status;
    }

    /* Wait for transfer to finish */
    if (xSemaphoreTake(handle->event, portMAX_DELAY) != pdTRUE)
    {
        return kStatus_LPSPI_Error;
    }

    /* Unlock resource mutex */
    (void)xSemaphoreGive(handle->mutex);

    /* Return status captured by callback function */
    return handle->async_status;
}
