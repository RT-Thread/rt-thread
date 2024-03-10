/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_lpuart_freertos.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpflexcomm_lpuart_freertos"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

static void LPUART_RTOS_Callback(LPUART_Type *base, lpuart_handle_t *state, status_t status, void *param)
{
    lpuart_rtos_handle_t *handle = (lpuart_rtos_handle_t *)param;
    BaseType_t xHigherPriorityTaskWoken, xResult;

    xHigherPriorityTaskWoken = pdFALSE;
    xResult                  = pdFAIL;

    if (status == kStatus_LPUART_RxIdle)
    {
        xResult = xEventGroupSetBitsFromISR(handle->rxEvent, RTOS_LPUART_RX_COMPLETE, &xHigherPriorityTaskWoken);
    }
    else if (status == kStatus_LPUART_TxIdle)
    {
        xResult = xEventGroupSetBitsFromISR(handle->txEvent, RTOS_LPUART_TX_COMPLETE, &xHigherPriorityTaskWoken);
    }
    else if (status == kStatus_LPUART_RxRingBufferOverrun)
    {
        xResult =
            xEventGroupSetBitsFromISR(handle->rxEvent, RTOS_LPUART_RING_BUFFER_OVERRUN, &xHigherPriorityTaskWoken);
    }
    else if (status == kStatus_LPUART_RxHardwareOverrun)
    {
        /* Clear Overrun flag (OR) in LPUART STAT register */
        (void)LPUART_ClearStatusFlags(base, (uint32_t)kLPUART_RxOverrunFlag);
        xResult =
            xEventGroupSetBitsFromISR(handle->rxEvent, RTOS_LPUART_HARDWARE_BUFFER_OVERRUN, &xHigherPriorityTaskWoken);
    }
    else
    {
        xResult = pdFAIL;
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
/*!
 * brief Initializes an LPUART instance for operation in RTOS.
 *
 * param handle The RTOS LPUART handle, the pointer to an allocated space for RTOS context.
 * param t_handle The pointer to an allocated space to store the transactional layer internal state.
 * param cfg The pointer to the parameters required to configure the LPUART after initialization.
 * return kStatus_Success, others failed
 */
int LPUART_RTOS_Init(lpuart_rtos_handle_t *handle, lpuart_handle_t *t_handle, const lpuart_rtos_config_t *cfg)
{
    status_t status;
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
    if (0u == cfg->srcclk)
    {
        return kStatus_InvalidArgument;
    }
    if (0u == cfg->baudrate)
    {
        return kStatus_InvalidArgument;
    }

    handle->base                     = cfg->base;
    handle->t_state                  = t_handle;
    handle->rx_timeout_constant_ms   = cfg->rx_timeout_constant_ms;
    handle->rx_timeout_multiplier_ms = cfg->rx_timeout_multiplier_ms;
    handle->tx_timeout_constant_ms   = cfg->tx_timeout_constant_ms;
    handle->tx_timeout_multiplier_ms = cfg->tx_timeout_multiplier_ms;

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
    handle->txEvent     = xEventGroupCreate();
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
    handle->rxEvent     = xEventGroupCreate();
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
    defcfg.parityMode   = cfg->parity;
    defcfg.stopBitCount = cfg->stopbits;
#if defined(FSL_FEATURE_LPUART_HAS_MODEM_SUPPORT) && FSL_FEATURE_LPUART_HAS_MODEM_SUPPORT
    defcfg.enableRxRTS = cfg->enableRxRTS;
    defcfg.enableTxCTS = cfg->enableTxCTS;
    defcfg.txCtsSource = cfg->txCtsSource;
    defcfg.txCtsConfig = cfg->txCtsConfig;
#endif
    status = LPUART_Init(handle->base, &defcfg, cfg->srcclk);
    if (status != kStatus_Success)
    {
        vEventGroupDelete(handle->rxEvent);
        vEventGroupDelete(handle->txEvent);
        vSemaphoreDelete(handle->rxSemaphore);
        vSemaphoreDelete(handle->txSemaphore);
        return kStatus_Fail;
    }
    LPUART_TransferCreateHandle(handle->base, handle->t_state, LPUART_RTOS_Callback, handle);
    LPUART_TransferStartRingBuffer(handle->base, handle->t_state, cfg->buffer, cfg->buffer_size);

    LPUART_EnableTx(handle->base, true);
    LPUART_EnableRx(handle->base, true);

    return kStatus_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_RTOS_Deinit
 * Description   : Deinitializes the LPUART instance and frees resources
 *
 *END**************************************************************************/
/*!
 * brief Deinitializes an LPUART instance for operation.
 *
 * This function deinitializes the LPUART module, sets all register value to the reset value,
 * and releases the resources.
 *
 * param handle The RTOS LPUART handle.
 */
int LPUART_RTOS_Deinit(lpuart_rtos_handle_t *handle)
{
    LPUART_Deinit(handle->base);

    vEventGroupDelete(handle->txEvent);
    vEventGroupDelete(handle->rxEvent);

    /* Give the semaphore. This is for functional safety */
    (void)xSemaphoreGive(handle->txSemaphore);
    (void)xSemaphoreGive(handle->rxSemaphore);

    vSemaphoreDelete(handle->txSemaphore);
    vSemaphoreDelete(handle->rxSemaphore);

    /* Invalidate the handle */
    handle->base    = NULL;
    handle->t_state = NULL;

    return 0;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_RTOS_Send
 * Description   : Send chars over LPUART
 *
 *END**************************************************************************/
/*!
 * brief Sends data in the background.
 *
 * This function sends data. It is an synchronous API.
 * If the hardware buffer is full, the task is in the blocked state.
 *
 * param handle The RTOS LPUART handle.
 * param buffer The pointer to buffer to send.
 * param length The number of bytes to send.
 */
int LPUART_RTOS_Send(lpuart_rtos_handle_t *handle, uint8_t *buffer, uint32_t length)
{
    EventBits_t ev;
    int retval = kStatus_Fail;
    status_t status;
    const TickType_t txTickTimeout =
        (length * handle->tx_timeout_multiplier_ms + handle->tx_timeout_constant_ms) / portTICK_PERIOD_MS;

    if (NULL == handle->base)
    {
        /* Invalid handle. */
        return kStatus_Fail;
    }
    if (0u == length)
    {
        return kStatus_Success;
    }
    if (NULL == buffer)
    {
        return kStatus_InvalidArgument;
    }

    if (pdFALSE == xSemaphoreTake(handle->txSemaphore, 0u))
    {
        /* We could not take the semaphore, exit with 0 data received */
        return kStatus_Fail;
    }

    handle->txTransfer.data     = (uint8_t *)buffer;
    handle->txTransfer.dataSize = (uint32_t)length;

    /* Non-blocking call */
    status = LPUART_TransferSendNonBlocking(handle->base, handle->t_state, &handle->txTransfer);
    if (status != kStatus_Success)
    {
        (void)xSemaphoreGive(handle->txSemaphore);
        return kStatus_Fail;
    }

    ev = xEventGroupWaitBits(handle->txEvent, RTOS_LPUART_TX_COMPLETE, pdTRUE, pdFALSE,
                             (txTickTimeout > 0u) ? txTickTimeout : portMAX_DELAY);
    if ((ev & RTOS_LPUART_TX_COMPLETE) != 0u)
    {
        retval = kStatus_Success;
    }
    else /* timeout expired or unknown error*/
    {
        if (txTickTimeout > 0u)
        {
            LPUART_TransferAbortSend(handle->base, handle->t_state);
            (void)xEventGroupClearBits(handle->txEvent, RTOS_LPUART_TX_COMPLETE);
            retval = kStatus_Timeout;
        }
        else
        {
            retval = kStatus_Fail;
        }
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
 * Function Name : LPUART_RTOS_Receive
 * Description   : Receives chars from LPUART
 *
 *END**************************************************************************/
/*!
 * brief Receives data.
 *
 * This function receives data from LPUART. It is an synchronous API. If any data is immediately available
 * it is returned immediately and the number of bytes received.
 *
 * param handle The RTOS LPUART handle.
 * param buffer The pointer to buffer where to write received data.
 * param length The number of bytes to receive.
 * param received The pointer to a variable of size_t where the number of received data is filled.
 */
int LPUART_RTOS_Receive(lpuart_rtos_handle_t *handle, uint8_t *buffer, uint32_t length, size_t *received)
{
    EventBits_t ev;
    size_t n                = 0u;
    int retval              = kStatus_Fail;
    uint32_t local_received = 0u;
    status_t status;
    const TickType_t rxTickTimeout =
        (length * handle->rx_timeout_multiplier_ms + handle->rx_timeout_constant_ms) / portTICK_PERIOD_MS;

    if (NULL == handle->base)
    {
        /* Invalid handle. */
        return kStatus_Fail;
    }
    if (0u == length)
    {
        if (received != NULL)
        {
            *received = n;
        }
        return kStatus_Success;
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

    handle->rxTransfer.data     = buffer;
    handle->rxTransfer.dataSize = (uint32_t)length;

    /* Non-blocking call */
    status = LPUART_TransferReceiveNonBlocking(handle->base, handle->t_state, &handle->rxTransfer, &n);
    if (status != kStatus_Success)
    {
        (void)xSemaphoreGive(handle->rxSemaphore);
        return kStatus_Fail;
    }

    ev = xEventGroupWaitBits(
        handle->rxEvent,
        RTOS_LPUART_RX_COMPLETE | RTOS_LPUART_RING_BUFFER_OVERRUN | RTOS_LPUART_HARDWARE_BUFFER_OVERRUN, pdTRUE,
        pdFALSE, (rxTickTimeout > 0u) ? rxTickTimeout : portMAX_DELAY);
    if ((ev & RTOS_LPUART_HARDWARE_BUFFER_OVERRUN) != 0u)
    {
        /* Stop data transfer to application buffer, ring buffer is still active */
        LPUART_TransferAbortReceive(handle->base, handle->t_state);
        /* Prevent false indication of successful transfer in next call of LPUART_RTOS_Receive.
           RTOS_LPUART_COMPLETE flag could be set meanwhile overrun is handled */
        (void)xEventGroupClearBits(handle->rxEvent, RTOS_LPUART_RX_COMPLETE);
        retval         = kStatus_LPUART_RxHardwareOverrun;
        local_received = 0u;
    }
    else if ((ev & RTOS_LPUART_RING_BUFFER_OVERRUN) != 0u)
    {
        /* Stop data transfer to application buffer, ring buffer is still active */
        LPUART_TransferAbortReceive(handle->base, handle->t_state);
        /* Prevent false indication of successful transfer in next call of LPUART_RTOS_Receive.
           RTOS_LPUART_COMPLETE flag could be set meanwhile overrun is handled */
        (void)xEventGroupClearBits(handle->rxEvent, RTOS_LPUART_RX_COMPLETE);
        retval         = kStatus_LPUART_RxRingBufferOverrun;
        local_received = 0u;
    }
    else if ((ev & RTOS_LPUART_RX_COMPLETE) != 0u)
    {
        retval         = kStatus_Success;
        local_received = length;
    }
    else /* timeout expired or unknown error*/
    {
        if (rxTickTimeout > 0u)
        {
            (void)LPUART_TransferGetReceiveCount(handle->base, handle->t_state, &local_received);
            LPUART_TransferAbortReceive(handle->base, handle->t_state);
            (void)xEventGroupClearBits(handle->rxEvent, RTOS_LPUART_RX_COMPLETE);
            retval = kStatus_Timeout;
        }
        else
        {
            retval         = kStatus_LPUART_Error;
            local_received = 0u;
        }
    }

    /* Prevent repetitive NULL check */
    if (received != NULL)
    {
        *received = (size_t)local_received;
    }

    /* Enable next transfer. Current one is finished */
    if (pdFALSE == xSemaphoreGive(handle->rxSemaphore))
    {
        /* We could not post the semaphore, exit with error */
        retval = kStatus_Fail;
    }
    return retval;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_RTOS_SetRxTimeout
 * Description   : Modify receive timeout value in alreaty initialized LPUART RTOS handle.
 *
 *END**************************************************************************/
/*!
 * brief Set RX timeout in runtime
 *
 * This function can modify RX timeout between initialization and receive.
 *
 * param handle The RTOS LPUART handle.
 * param rx_timeout_constant_ms RX timeout applied per receive.
 * param rx_timeout_multiplier_ms RX timeout added for each byte of the receive.
 */
int LPUART_RTOS_SetRxTimeout(lpuart_rtos_handle_t *handle,
                             uint32_t rx_timeout_constant_ms,
                             uint32_t rx_timeout_multiplier_ms)
{
    if (NULL == handle)
    {
        return kStatus_InvalidArgument;
    }
    handle->rx_timeout_constant_ms   = rx_timeout_constant_ms;
    handle->rx_timeout_multiplier_ms = rx_timeout_multiplier_ms;
    return kStatus_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_RTOS_SetTxTimeout
 * Description   : Modify send timeout value in alreaty initialized LPUART RTOS handle.
 *
 *END**************************************************************************/
/*!
 * brief Set TX timeout in runtime
 *
 * This function can modify TX timeout between initialization and send.
 *
 * param handle The RTOS LPUART handle.
 * param tx_timeout_constant_ms TX timeout applied per transmition.
 * param tx_timeout_multiplier_ms TX timeout added for each byte of the transmition.
 */
int LPUART_RTOS_SetTxTimeout(lpuart_rtos_handle_t *handle,
                             uint32_t tx_timeout_constant_ms,
                             uint32_t tx_timeout_multiplier_ms)
{
    if (NULL == handle)
    {
        return kStatus_InvalidArgument;
    }
    handle->tx_timeout_constant_ms   = tx_timeout_constant_ms;
    handle->tx_timeout_multiplier_ms = tx_timeout_multiplier_ms;
    return kStatus_Success;
}
