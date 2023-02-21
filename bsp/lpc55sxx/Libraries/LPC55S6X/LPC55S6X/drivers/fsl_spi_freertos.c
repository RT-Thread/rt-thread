/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_spi_freertos.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flexcomm_spi_freertos"
#endif

static void SPI_RTOS_Callback(SPI_Type *base, spi_master_handle_t *drv_handle, status_t status, void *userData)
{
    spi_rtos_handle_t *handle = (spi_rtos_handle_t *)userData;
    BaseType_t reschedule;
    handle->async_status = status;
    (void)xSemaphoreGiveFromISR(handle->event, &reschedule);
    portYIELD_FROM_ISR(reschedule);
}

/*!
 * brief Initializes SPI.
 *
 * This function initializes the SPI module and related RTOS context.
 *
 * param handle The RTOS SPI handle, the pointer to an allocated space for RTOS context.
 * param base The pointer base address of the SPI instance to initialize.
 * param masterConfig Configuration structure to set-up SPI in master mode.
 * param srcClock_Hz Frequency of input clock of the SPI module.
 * return status of the operation.
 */
status_t SPI_RTOS_Init(spi_rtos_handle_t *handle,
                       SPI_Type *base,
                       const spi_master_config_t *masterConfig,
                       uint32_t srcClock_Hz)
{
    status_t status;

    if (handle == NULL)
    {
        return kStatus_InvalidArgument;
    }

    if (base == NULL)
    {
        return kStatus_InvalidArgument;
    }

    (void)memset(handle, 0, sizeof(spi_rtos_handle_t));

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

    (void)SPI_MasterInit(handle->base, masterConfig, srcClock_Hz);
    status = SPI_MasterTransferCreateHandle(handle->base, &handle->drv_handle, SPI_RTOS_Callback, (void *)handle);

    return status;
}

/*!
 * brief Deinitializes the SPI.
 *
 * This function deinitializes the SPI module and related RTOS context.
 *
 * param handle The RTOS SPI handle.
 */
status_t SPI_RTOS_Deinit(spi_rtos_handle_t *handle)
{
    SPI_Deinit(handle->base);
    vSemaphoreDelete(handle->event);
    vSemaphoreDelete(handle->mutex);

    return kStatus_Success;
}

/*!
 * brief Performs SPI transfer.
 *
 * This function performs an SPI transfer according to data given in the transfer structure.
 *
 * param handle The RTOS SPI handle.
 * param transfer Structure specifying the transfer parameters.
 * return status of the operation.
 */
status_t SPI_RTOS_Transfer(spi_rtos_handle_t *handle, spi_transfer_t *transfer)
{
    status_t status;

    /* Lock resource mutex */
    if (xSemaphoreTake(handle->mutex, portMAX_DELAY) != pdTRUE)
    {
        return kStatus_SPI_Busy;
    }

    /* Initiate transfer */
    status = SPI_MasterTransferNonBlocking(handle->base, &handle->drv_handle, transfer);
    if (status != kStatus_Success)
    {
        (void)xSemaphoreGive(handle->mutex);
        return status;
    }

    /* Wait for transfer to finish */
    if (xSemaphoreTake(handle->event, portMAX_DELAY) != pdTRUE)
    {
        return kStatus_SPI_Error;
    }

    /* Retrieve status before releasing mutex */
    status = handle->async_status;

    /* Unlock resource mutex */
    (void)xSemaphoreGive(handle->mutex);

    /* Translate status of underlying driver */
    if (status == kStatus_SPI_Idle)
    {
        status = kStatus_Success;
    }

    return status;
}
