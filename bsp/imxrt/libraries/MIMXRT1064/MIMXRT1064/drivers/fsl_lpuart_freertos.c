/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_lpuart_freertos.h"
#include <FreeRTOS.h>
#include <event_groups.h>
#include <semphr.h>

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpuart_freertos"
#endif


static void LPUART_RTOS_Callback(LPUART_Type *base, lpuart_handle_t *state, status_t status, void *param)
{
    lpuart_rtos_handle_t *handle = (lpuart_rtos_handle_t *)param;
    BaseType_t xHigherPriorityTaskWoken, xResult;

    xHigherPriorityTaskWoken = pdFALSE;
    xResult = pdFAIL;

    if (status == kStatus_LPUART_RxIdle)
    {
        xResult = xEventGroupSetBitsFromISR(handle->rxEvent, RTOS_LPUART_COMPLETE, &xHigherPriorityTaskWoken);
    }
    else if (status == kStatus_LPUART_TxIdle)
    {
        xResult = xEventGroupSetBitsFromISR(handle->txEvent, RTOS_LPUART_COMPLETE, &xHigherPriorityTaskWoken);
    }
    else if (status == kStatus_LPUART_RxRingBufferOverrun)
    {
        xResult =
            xEventGroupSetBitsFromISR(handle->rxEvent, RTOS_LPUART_RING_BUFFER_OVERRUN, &xHigherPriorityTaskWoken);
    }
    else if (status == kStatus_LPUART_RxHardwareOverrun)
    {
        /* Clear Overrun flag (OR) in LPUART STAT register */
        LPUART_ClearStatusFlags(base, kLPUART_RxOverrunFlag);
        xResult =
            xEventGroupSetBitsFromISR(handle->rxEvent, RTOS_LPUART_HARDWARE_BUFFER_OVERRUN, &xHigherPriorityTaskWoken);
    }

    if (xResult != pdFAIL)
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_RTOS_Init
 * Description   : Initializes the LPUART instance for application
 *
 *END**************************************************************************/
int LPUART_RTOS_Init(lpuart_rtos_handle_t *handle, lpuart_handle_t *t_handle, const lpuart_rtos_config_t *cfg)
{
    lpuart_config_t defcfg;

    if (NULL == handle)
    {
        return kStatus_InvalidArgument;
    }
    if (NULL == t_handle)
    {
        return kStatus_InvalidArgument;
    }
    if (NULL == cfg)
    {
        return kStatus_InvalidArgument;
    }
    if (NULL == cfg->base)
    {
        return kStatus_InvalidArgument;
    }
    if (0 == cfg->srcclk)
    {
        return kStatus_InvalidArgument;
    }
    if (0 == cfg->baudrate)
    {
        return kStatus_InvalidArgument;
    }

    handle->base = cfg->base;
    handle->t_state = t_handle;
#if (configSUPPORT_STATIC_ALLOCATION == 1)
    handle->txSemaphore = xSemaphoreCreateMutexStatic(&handle->txSemaphoreBuffer);
#else
    handle->txSemaphore = xSemaphoreCreateMutex();
#endif
    if (NULL == handle->txSemaphore)
    {
        return kStatus_Fail;
    }
#if (configSUPPORT_STATIC_ALLOCATION == 1)
    handle->rxSemaphore = xSemaphoreCreateMutexStatic(&handle->rxSemaphoreBuffer);
#else
    handle->rxSemaphore = xSemaphoreCreateMutex();
#endif
    if (NULL == handle->rxSemaphore)
    {
        vSemaphoreDelete(handle->txSemaphore);
        return kStatus_Fail;
    }
#if (configSUPPORT_STATIC_ALLOCATION == 1)
    handle->txEvent = xEventGroupCreateStatic(&handle->txEventBuffer);
#else
    handle->txEvent = xEventGroupCreate();
#endif
    if (NULL == handle->txEvent)
    {
        vSemaphoreDelete(handle->rxSemaphore);
        vSemaphoreDelete(handle->txSemaphore);
        return kStatus_Fail;
    }
#if (configSUPPORT_STATIC_ALLOCATION == 1)
    handle->rxEvent = xEventGroupCreateStatic(&handle->rxEventBuffer);
#else
    handle->rxEvent = xEventGroupCreate();
#endif
    if (NULL == handle->rxEvent)
    {
        vEventGroupDelete(handle->txEvent);
        vSemaphoreDelete(handle->rxSemaphore);
        vSemaphoreDelete(handle->txSemaphore);
        return kStatus_Fail;
    }
    LPUART_GetDefaultConfig(&defcfg);

    defcfg.baudRate_Bps = cfg->baudrate;
    defcfg.parityMode = cfg->parity;
    defcfg.stopBitCount = cfg->stopbits;

    LPUART_Init(handle->base, &defcfg, cfg->srcclk);
    LPUART_TransferCreateHandle(handle->base, handle->t_state, LPUART_RTOS_Callback, handle);
    LPUART_TransferStartRingBuffer(handle->base, handle->t_state, cfg->buffer, cfg->buffer_size);

    LPUART_EnableTx(handle->base, true);
    LPUART_EnableRx(handle->base, true);

    return 0;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_RTOS_Deinit
 * Description   : Deinitializes the LPUART instance and frees resources
 *
 *END**************************************************************************/
int LPUART_RTOS_Deinit(lpuart_rtos_handle_t *handle)
{
    LPUART_Deinit(handle->base);

    vEventGroupDelete(handle->txEvent);
    vEventGroupDelete(handle->rxEvent);

    /* Give the semaphore. This is for functional safety */
    xSemaphoreGive(handle->txSemaphore);
    xSemaphoreGive(handle->rxSemaphore);

    vSemaphoreDelete(handle->txSemaphore);
    vSemaphoreDelete(handle->rxSemaphore);

    /* Invalidate the handle */
    handle->base = NULL;
    handle->t_state = NULL;

    return 0;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_RTOS_Send
 * Description   : Initializes the UART instance for application
 *
 *END**************************************************************************/
int LPUART_RTOS_Send(lpuart_rtos_handle_t *handle, const uint8_t *buffer, uint32_t length)
{
    EventBits_t ev;
    int retval = kStatus_Success;

    if (NULL == handle->base)
    {
        /* Invalid handle. */
        return kStatus_Fail;
    }
    if (0 == length)
    {
        return 0;
    }
    if (NULL == buffer)
    {
        return kStatus_InvalidArgument;
    }

    if (pdFALSE == xSemaphoreTake(handle->txSemaphore, 0))
    {
        /* We could not take the semaphore, exit with 0 data received */
        return kStatus_Fail;
    }

    handle->txTransfer.data = (uint8_t *)buffer;
    handle->txTransfer.dataSize = (uint32_t)length;

    /* Non-blocking call */
    LPUART_TransferSendNonBlocking(handle->base, handle->t_state, &handle->txTransfer);

    ev = xEventGroupWaitBits(handle->txEvent, RTOS_LPUART_COMPLETE, pdTRUE, pdFALSE, portMAX_DELAY);
    if (!(ev & RTOS_LPUART_COMPLETE))
    {
        retval = kStatus_Fail;
    }

    if (pdFALSE == xSemaphoreGive(handle->txSemaphore))
    {
        /* We could not post the semaphore, exit with error */
        retval = kStatus_Fail;
    }

    return retval;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_RTOS_Recv
 * Description   : Receives chars for the application
 *
 *END**************************************************************************/
int LPUART_RTOS_Receive(lpuart_rtos_handle_t *handle, uint8_t *buffer, uint32_t length, size_t *received)
{
    EventBits_t ev;
    size_t n = 0;
    int retval = kStatus_Fail;
    size_t local_received = 0;

    if (NULL == handle->base)
    {
        /* Invalid handle. */
        return kStatus_Fail;
    }
    if (0 == length)
    {
        if (received != NULL)
        {
            *received = n;
        }
        return 0;
    }
    if (NULL == buffer)
    {
        return kStatus_InvalidArgument;
    }

    /* New transfer can be performed only after current one is finished */
    if (pdFALSE == xSemaphoreTake(handle->rxSemaphore, portMAX_DELAY))
    {
        /* We could not take the semaphore, exit with 0 data received */
        return kStatus_Fail;
    }

    handle->rxTransfer.data = buffer;
    handle->rxTransfer.dataSize = (uint32_t)length;

    /* Non-blocking call */
    LPUART_TransferReceiveNonBlocking(handle->base, handle->t_state, &handle->rxTransfer, &n);

    ev = xEventGroupWaitBits(
        handle->rxEvent, RTOS_LPUART_COMPLETE | RTOS_LPUART_RING_BUFFER_OVERRUN | RTOS_LPUART_HARDWARE_BUFFER_OVERRUN,
        pdTRUE, pdFALSE, portMAX_DELAY);
    if (ev & RTOS_LPUART_HARDWARE_BUFFER_OVERRUN)
    {
        /* Stop data transfer to application buffer, ring buffer is still active */
        LPUART_TransferAbortReceive(handle->base, handle->t_state);
        /* Prevent false indication of successful transfer in next call of LPUART_RTOS_Receive.
           RTOS_LPUART_COMPLETE flag could be set meanwhile overrun is handled */
        xEventGroupClearBits(handle->rxEvent, RTOS_LPUART_COMPLETE);
        retval = kStatus_LPUART_RxHardwareOverrun;
        local_received = 0;
    }
    else if (ev & RTOS_LPUART_RING_BUFFER_OVERRUN)
    {
        /* Stop data transfer to application buffer, ring buffer is still active */
        LPUART_TransferAbortReceive(handle->base, handle->t_state);
        /* Prevent false indication of successful transfer in next call of LPUART_RTOS_Receive.
           RTOS_LPUART_COMPLETE flag could be set meanwhile overrun is handled */
        xEventGroupClearBits(handle->rxEvent, RTOS_LPUART_COMPLETE);
        retval = kStatus_LPUART_RxRingBufferOverrun;
        local_received = 0;
    }
    else if (ev & RTOS_LPUART_COMPLETE)
    {
        retval = kStatus_Success;
        local_received = length;
    }

    /* Prevent repetitive NULL check */
    if (received != NULL)
    {
        *received = local_received;
    }

    /* Enable next transfer. Current one is finished */
    if (pdFALSE == xSemaphoreGive(handle->rxSemaphore))
    {
        /* We could not post the semaphore, exit with error */
        retval = kStatus_Fail;
    }
    return retval;
}
