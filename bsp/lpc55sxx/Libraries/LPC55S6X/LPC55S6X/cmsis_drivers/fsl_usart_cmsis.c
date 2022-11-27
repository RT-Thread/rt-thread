/*
 * Copyright (c) 2013-2016 ARM Limited. All rights reserved.
 * Copyright (c) 2016, Freescale Semiconductor, Inc. Not a Contribution.
 * Copyright 2016-2017, 2020 NXP. Not a Contribution.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "fsl_usart_cmsis.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flexcomm_usart_cmsis"
#endif

#if ((defined(RTE_USART0) && RTE_USART0) || (defined(RTE_USART1) && RTE_USART1) ||     \
     (defined(RTE_USART2) && RTE_USART2) || (defined(RTE_USART3) && RTE_USART3) ||     \
     (defined(RTE_USART4) && RTE_USART4) || (defined(RTE_USART5) && RTE_USART5) ||     \
     (defined(RTE_USART6) && RTE_USART6) || (defined(RTE_USART7) && RTE_USART7) ||     \
     (defined(RTE_USART8) && RTE_USART8) || (defined(RTE_USART9) && RTE_USART9) ||     \
     (defined(RTE_USART10) && RTE_USART10) || (defined(RTE_USART11) && RTE_USART11) || \
     (defined(RTE_USART12) && RTE_USART12) || (defined(RTE_USART13) && RTE_USART13))

#define ARM_USART_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR((2), (3))

/*
 * ARMCC does not support split the data section automatically, so the driver
 * needs to split the data to separate sections explicitly, to reduce codesize.
 */
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
#define ARMCC_SECTION(section_name) __attribute__((section(section_name)))
#endif

typedef const struct _cmsis_usart_resource
{
    USART_Type *base;          /*!< usart peripheral base address.       */
    uint32_t (*GetFreq)(void); /*!< Function to get the clock frequency. */
} cmsis_usart_resource_t;

typedef struct _cmsis_usart_non_blocking_driver_state
{
    cmsis_usart_resource_t *resource; /*!< Basic usart resource.      */
    usart_handle_t *handle;           /*!< Interupt transfer handle.  */
    ARM_USART_SignalEvent_t cb_event; /*!< Callback function.         */
    uint8_t flags;                    /*!< Control and state flags. */
} cmsis_usart_non_blocking_driver_state_t;

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)
typedef const struct _cmsis_usart_dma_resource
{
    DMA_Type *txDmaBase;   /*!< DMA peripheral base address for TX.   */
    uint32_t txDmaChannel; /*!< DMA channel for usart TX.             */

    DMA_Type *rxDmaBase;   /*!< DMA peripheral base address for RX.   */
    uint32_t rxDmaChannel; /*!< DMA channel for usart RX.             */
} cmsis_usart_dma_resource_t;

typedef struct _cmsis_usart_dma_driver_state
{
    cmsis_usart_resource_t *resource;        /*!< usart basic resource.       */
    cmsis_usart_dma_resource_t *dmaResource; /*!< usart DMA resource.         */
    usart_dma_handle_t *handle;              /*!< usart DMA transfer handle.  */
    dma_handle_t *rxHandle;                  /*!< DMA RX handle.              */
    dma_handle_t *txHandle;                  /*!< DMA TX handle.              */
    ARM_USART_SignalEvent_t cb_event;        /*!< Callback function.          */
    uint8_t flags;                           /*!< Control and state flags. */
} cmsis_usart_dma_driver_state_t;
#endif

enum _usart_transfer_states
{
    kUSART_TxIdle, /*!< TX idle. */
    kUSART_TxBusy, /*!< TX busy. */
    kUSART_RxIdle, /*!< RX idle. */
    kUSART_RxBusy  /*!< RX busy. */
};

/* Driver Version */
static const ARM_DRIVER_VERSION s_usartDriverVersion = {ARM_USART_API_VERSION, ARM_USART_DRV_VERSION};

static const ARM_USART_CAPABILITIES s_usartDriverCapabilities = {
    1, /* supports usart (Asynchronous) mode */
    0, /* supports Synchronous Master mode */
    0, /* supports Synchronous Slave mode */
    0, /* supports usart Single-wire mode */
    0, /* supports usart IrDA mode */
    0, /* supports usart Smart Card mode */
    0, /* Smart Card Clock generator */
    0, /* RTS Flow Control available */
    0, /* CTS Flow Control available */
    0, /* Transmit completed event: \ref ARM_USART_EVENT_TX_COMPLETE */
    0, /* Signal receive character timeout event: \ref ARM_USART_EVENT_RX_TIMEOUT */
    0, /* RTS Line: 0=not available, 1=available */
    0, /* CTS Line: 0=not available, 1=available */
    0, /* DTR Line: 0=not available, 1=available */
    0, /* DSR Line: 0=not available, 1=available */
    0, /* DCD Line: 0=not available, 1=available */
    0, /* RI Line: 0=not available, 1=available */
    0, /* Signal CTS change event: \ref ARM_USART_EVENT_CTS */
    0, /* Signal DSR change event: \ref ARM_USART_EVENT_DSR */
    0, /* Signal DCD change event: \ref ARM_USART_EVENT_DCD */
    0, /* Signal RI change event: \ref ARM_USART_EVENT_RI */
};

/*
 * Common control function used by usart_NonBlockingControl/usart_DmaControl/usart_EdmaControl
 */
static int32_t USART_CommonControl(uint32_t control,
                                   uint32_t arg,
                                   cmsis_usart_resource_t *resource,
                                   uint8_t *isConfigured)
{
    usart_config_t config;

    USART_GetDefaultConfig(&config);
    int32_t result  = ARM_DRIVER_OK;
    bool isContinue = false;

    switch (control & ARM_USART_CONTROL_Msk)
    {
        case ARM_USART_MODE_ASYNCHRONOUS:
            /* USART Baudrate */
            config.baudRate_Bps = arg;
            isContinue          = true;
            break;

        /* TX/RX IO is controlled in application layer. */
        case ARM_USART_CONTROL_TX:
            if (arg != 0U)
            {
                config.enableTx = true;
            }
            else
            {
                config.enableTx = false;
            }
            result = ARM_DRIVER_OK;
            break;

        case ARM_USART_CONTROL_RX:
            if (arg != 0U)
            {
                config.enableRx = true;
            }
            else
            {
                config.enableRx = false;
            }

            result = ARM_DRIVER_OK;
            break;

        default:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
    }
    if (!isContinue)
    {
        return result;
    }

    switch (control & ARM_USART_PARITY_Msk)
    {
        case ARM_USART_PARITY_NONE:
            config.parityMode = kUSART_ParityDisabled;
            break;
        case ARM_USART_PARITY_EVEN:
            config.parityMode = kUSART_ParityEven;
            break;
        case ARM_USART_PARITY_ODD:
            config.parityMode = kUSART_ParityOdd;
            break;
        default:
            result = ARM_USART_ERROR_PARITY;
            break;
    }

    if (result == ARM_USART_ERROR_PARITY)
    {
        return result;
    }

    switch (control & ARM_USART_STOP_BITS_Msk)
    {
        case ARM_USART_STOP_BITS_1:
            /* The GetDefaultConfig has already set for this case. */
            break;
        case ARM_USART_STOP_BITS_2:
            config.stopBitCount = kUSART_TwoStopBit;
            break;
        default:
            result = ARM_USART_ERROR_STOP_BITS;
            break;
    }
    if (result == ARM_USART_ERROR_STOP_BITS)
    {
        return result;
    }

    /* If usart is already configured, deinit it first. */
    if (((*isConfigured) & (uint8_t)USART_FLAG_CONFIGURED) != 0U)
    {
        USART_Deinit(resource->base);
        *isConfigured &= ~(uint8_t)USART_FLAG_CONFIGURED;
    }

    config.enableTx = true;
    config.enableRx = true;

    if (kStatus_USART_BaudrateNotSupport == USART_Init(resource->base, &config, resource->GetFreq()))
    {
        result = ARM_USART_ERROR_BAUDRATE;
    }
    else
    {
        *isConfigured |= (uint8_t)USART_FLAG_CONFIGURED;
    }

    return result;
}

static ARM_DRIVER_VERSION USARTx_GetVersion(void)
{
    return s_usartDriverVersion;
}

static ARM_USART_CAPABILITIES USARTx_GetCapabilities(void)
{
    return s_usartDriverCapabilities;
}

static int32_t USARTx_SetModemControl(ARM_USART_MODEM_CONTROL control)
{
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static ARM_USART_MODEM_STATUS USARTx_GetModemStatus(void)
{
    ARM_USART_MODEM_STATUS modem_status = {0};

    modem_status.cts      = 0U;
    modem_status.dsr      = 0U;
    modem_status.ri       = 0U;
    modem_status.dcd      = 0U;
    modem_status.reserved = 0U;

    return modem_status;
}

#endif

#if ((defined(RTE_USART0_DMA_EN) && RTE_USART0_DMA_EN) || (defined(RTE_USART1_DMA_EN) && RTE_USART1_DMA_EN) ||     \
     (defined(RTE_USART2_DMA_EN) && RTE_USART2_DMA_EN) || (defined(RTE_USART3_DMA_EN) && RTE_USART3_DMA_EN) ||     \
     (defined(RTE_USART4_DMA_EN) && RTE_USART4_DMA_EN) || (defined(RTE_USART5_DMA_EN) && RTE_USART5_DMA_EN) ||     \
     (defined(RTE_USART6_DMA_EN) && RTE_USART6_DMA_EN) || (defined(RTE_USART7_DMA_EN) && RTE_USART7_DMA_EN) ||     \
     (defined(RTE_USART8_DMA_EN) && RTE_USART8_DMA_EN) || (defined(RTE_USART9_DMA_EN) && RTE_USART9_DMA_EN) ||     \
     (defined(RTE_USART10_DMA_EN) && RTE_USART10_DMA_EN) || (defined(RTE_USART11_DMA_EN) && RTE_USART11_DMA_EN) || \
     (defined(RTE_USART12_DMA_EN) && RTE_USART12_DMA_EN) || (defined(RTE_USART13_DMA_EN) && RTE_USART13_DMA_EN))

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)
static void KSDK_USART_DmaCallback(USART_Type *base, usart_dma_handle_t *handle, status_t status, void *userData)
{
    uint32_t event = 0U;

    if (kStatus_USART_TxIdle == status)
    {
        event = ARM_USART_EVENT_SEND_COMPLETE;
    }

    if (kStatus_USART_RxIdle == status)
    {
        event = ARM_USART_EVENT_RECEIVE_COMPLETE;
    }
    else
    {
        /* Avoid MISRA 2012 15.7 violation */
    }

    /* User data is actually CMSIS driver callback. */
    if (userData != NULL)
    {
        ((ARM_USART_SignalEvent_t)userData)(event);
    }
}

static int32_t USART_DmaInitialize(ARM_USART_SignalEvent_t cb_event, cmsis_usart_dma_driver_state_t *usart)
{
    if (0U == (usart->flags & USART_FLAG_INIT))
    {
        usart->cb_event = cb_event;
        usart->flags    = (uint8_t)USART_FLAG_INIT;
    }

    return ARM_DRIVER_OK;
}

static int32_t USART_DmaUninitialize(cmsis_usart_dma_driver_state_t *usart)
{
    usart->flags = (uint8_t)USART_FLAG_UNINIT;
    return ARM_DRIVER_OK;
}

static int32_t USART_DmaPowerControl(ARM_POWER_STATE state, cmsis_usart_dma_driver_state_t *usart)
{
    usart_config_t config;
    int32_t result = ARM_DRIVER_OK;

    switch (state)
    {
        case ARM_POWER_OFF:
            if ((usart->flags & (uint8_t)USART_FLAG_POWER) != 0U)
            {
                USART_Deinit(usart->resource->base);
                DMA_DisableChannel(usart->dmaResource->rxDmaBase, usart->dmaResource->rxDmaChannel);
                DMA_DisableChannel(usart->dmaResource->txDmaBase, usart->dmaResource->txDmaChannel);
                usart->flags = (uint8_t)USART_FLAG_INIT;
            }
            break;
        case ARM_POWER_LOW:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
        case ARM_POWER_FULL:
            /* Must be initialized first. */
            if (usart->flags == (uint8_t)USART_FLAG_UNINIT)
            {
                result = ARM_DRIVER_ERROR;
                break;
            }

            if ((usart->flags & (uint8_t)USART_FLAG_POWER) != 0U)
            {
                /* Driver already powered */
                break;
            }

            USART_GetDefaultConfig(&config);
            config.enableTx = true;
            config.enableRx = true;

            /* Set up DMA setting. */
            DMA_EnableChannel(usart->dmaResource->txDmaBase, usart->dmaResource->txDmaChannel);
            DMA_EnableChannel(usart->dmaResource->rxDmaBase, usart->dmaResource->rxDmaChannel);

            DMA_CreateHandle(usart->rxHandle, usart->dmaResource->rxDmaBase, usart->dmaResource->rxDmaChannel);
            DMA_CreateHandle(usart->txHandle, usart->dmaResource->txDmaBase, usart->dmaResource->txDmaChannel);

            /* Setup the usart. */
            (void)USART_Init(usart->resource->base, &config, usart->resource->GetFreq());
            (void)USART_TransferCreateHandleDMA(usart->resource->base, usart->handle, KSDK_USART_DmaCallback,
                                                (void *)usart->cb_event, usart->txHandle, usart->rxHandle);

            usart->flags |= ((uint8_t)USART_FLAG_POWER | (uint8_t)USART_FLAG_CONFIGURED);
            break;
        default:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
    }

    return result;
}

static int32_t USART_DmaSend(const void *data, uint32_t num, cmsis_usart_dma_driver_state_t *usart)
{
    int32_t ret;
    status_t status;
    usart_transfer_t xfer;

    xfer.txData   = (const uint8_t *)data;
    xfer.dataSize = num;

    status = USART_TransferSendDMA(usart->resource->base, usart->handle, &xfer);

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_USART_TxBusy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t USART_DmaReceive(void *data, uint32_t num, cmsis_usart_dma_driver_state_t *usart)
{
    int32_t ret;
    status_t status;
    usart_transfer_t xfer;

    xfer.rxData   = (uint8_t *)data;
    xfer.dataSize = num;

    status = USART_TransferReceiveDMA(usart->resource->base, usart->handle, &xfer);

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_USART_RxBusy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t USART_DmaTransfer(const void *data_out,
                                 void *data_in,
                                 uint32_t num,
                                 cmsis_usart_dma_driver_state_t *usart)
{
    /* Only in synchronous mode */
    return ARM_DRIVER_ERROR;
}

static uint32_t USART_DmaGetTxCount(cmsis_usart_dma_driver_state_t *usart)
{
    uint32_t cnt;

    /* If TX not in progress, then the TX count is txDataSizeAll saved in handle. */
    if (kStatus_NoTransferInProgress == USART_TransferGetSendCountDMA(usart->resource->base, usart->handle, &cnt))
    {
        cnt = usart->handle->txDataSizeAll;
    }

    return cnt;
}

static uint32_t USART_DmaGetRxCount(cmsis_usart_dma_driver_state_t *usart)
{
    uint32_t cnt;

    if (kStatus_NoTransferInProgress == USART_TransferGetReceiveCountDMA(usart->resource->base, usart->handle, &cnt))
    {
        cnt = usart->handle->rxDataSizeAll;
    }

    return cnt;
}

static int32_t USART_DmaControl(uint32_t control, uint32_t arg, cmsis_usart_dma_driver_state_t *usart)
{
    int32_t result  = ARM_DRIVER_OK;
    bool isContinue = false;
    /* Must be power on. */
    if (0U == (usart->flags & (uint8_t)USART_FLAG_POWER))
    {
        return ARM_DRIVER_ERROR;
    }

    /* Does not support these features. */
    if ((control & (ARM_USART_FLOW_CONTROL_Msk | ARM_USART_CPOL_Msk | ARM_USART_CPHA_Msk)) != 0U)
    {
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    switch (control & ARM_USART_CONTROL_Msk)
    {
        /* Abort Send */
        case ARM_USART_ABORT_SEND:
            USART_EnableTxDMA(usart->resource->base, false);
            DMA_AbortTransfer(usart->handle->txDmaHandle);
            usart->handle->txState = (uint8_t)kUSART_TxIdle;
            result                 = ARM_DRIVER_OK;
            break;

        /* Abort receive */
        case ARM_USART_ABORT_RECEIVE:
            USART_EnableRxDMA(usart->resource->base, false);
            DMA_AbortTransfer(usart->handle->rxDmaHandle);
            usart->handle->rxState = (uint8_t)kUSART_RxIdle;
            result                 = ARM_DRIVER_OK;
            break;

        default:
            isContinue = true;
            break;
    }
    if (isContinue)
    {
        result = USART_CommonControl(control, arg, usart->resource, &usart->flags);
    }
    return result;
}

static ARM_USART_STATUS USART_DmaGetStatus(cmsis_usart_dma_driver_state_t *usart)
{
    ARM_USART_STATUS stat      = {0};
    uint32_t ksdk_usart_status = usart->resource->base->STAT;

    stat.tx_busy = (((uint8_t)kUSART_TxBusy == usart->handle->txState) ? (1U) : (0U));
    stat.rx_busy = (((uint8_t)kUSART_RxBusy == usart->handle->rxState) ? (1U) : (0U));

    stat.tx_underflow = 0U;
    stat.rx_overflow  = 0U;

    stat.rx_break = (uint32_t)(((ksdk_usart_status & USART_STAT_RXBRK_MASK)) != 0U);

    stat.rx_framing_error = (uint32_t)(((ksdk_usart_status & USART_STAT_FRAMERRINT_MASK)) != 0U);
    stat.rx_parity_error  = (uint32_t)(((ksdk_usart_status & USART_STAT_PARITYERRINT_MASK)) != 0U);
    stat.reserved         = 0U;

    return stat;
}
#endif

#endif

#if ((defined(RTE_USART0) && RTE_USART0 && !(defined(RTE_USART0_DMA_EN) && RTE_USART0_DMA_EN)) ||     \
     (defined(RTE_USART1) && RTE_USART1 && !(defined(RTE_USART1_DMA_EN) && RTE_USART1_DMA_EN)) ||     \
     (defined(RTE_USART2) && RTE_USART2 && !(defined(RTE_USART2_DMA_EN) && RTE_USART2_DMA_EN)) ||     \
     (defined(RTE_USART3) && RTE_USART3 && !(defined(RTE_USART3_DMA_EN) && RTE_USART3_DMA_EN)) ||     \
     (defined(RTE_USART4) && RTE_USART4 && !(defined(RTE_USART4_DMA_EN) && RTE_USART4_DMA_EN)) ||     \
     (defined(RTE_USART5) && RTE_USART5 && !(defined(RTE_USART5_DMA_EN) && RTE_USART5_DMA_EN)) ||     \
     (defined(RTE_USART6) && RTE_USART6 && !(defined(RTE_USART6_DMA_EN) && RTE_USART6_DMA_EN)) ||     \
     (defined(RTE_USART7) && RTE_USART7 && !(defined(RTE_USART7_DMA_EN) && RTE_USART7_DMA_EN)) ||     \
     (defined(RTE_USART8) && RTE_USART8 && !(defined(RTE_USART8_DMA_EN) && RTE_USART8_DMA_EN)) ||     \
     (defined(RTE_USART9) && RTE_USART9 && !(defined(RTE_USART9_DMA_EN) && RTE_USART9_DMA_EN)) ||     \
     (defined(RTE_USART10) && RTE_USART10 && !(defined(RTE_USART10_DMA_EN) && RTE_USART10_DMA_EN)) || \
     (defined(RTE_USART11) && RTE_USART11 && !(defined(RTE_USART11_DMA_EN) && RTE_USART11_DMA_EN)) || \
     (defined(RTE_USART12) && RTE_USART12 && !(defined(RTE_USART12_DMA_EN) && RTE_USART12_DMA_EN)) || \
     (defined(RTE_USART13) && RTE_USART13 && !(defined(RTE_USART13_DMA_EN) && RTE_USART13_DMA_EN)))

static void KSDK_USART_NonBlockingCallback(USART_Type *base, usart_handle_t *handle, status_t status, void *userData)
{
    uint32_t event = 0U;

    switch (status)
    {
        case kStatus_USART_TxIdle:
            event = ARM_USART_EVENT_SEND_COMPLETE;
            break;
        case kStatus_USART_RxIdle:
            event = ARM_USART_EVENT_RECEIVE_COMPLETE;
            break;
        case kStatus_USART_RxError:
            event = ARM_USART_EVENT_RX_OVERFLOW;
            break;
        case kStatus_USART_TxError:
            event = ARM_USART_EVENT_TX_UNDERFLOW;
            break;
        case kStatus_USART_FramingError:
            event = ARM_USART_EVENT_RX_FRAMING_ERROR;
            break;
        case kStatus_USART_ParityError:
            event = ARM_USART_EVENT_RX_PARITY_ERROR;
            break;
        default:
            /* Avoid MISRA 16.4. */
            break;
    }

    /* User data is actually CMSIS driver callback. */
    if (userData != NULL)
    {
        ((ARM_USART_SignalEvent_t)userData)(event);
    }
}

static int32_t USART_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event,
                                           cmsis_usart_non_blocking_driver_state_t *usart)
{
    if (0U == (usart->flags & (uint8_t)USART_FLAG_INIT))
    {
        usart->cb_event = cb_event;
        usart->flags    = (uint8_t)USART_FLAG_INIT;
    }

    return ARM_DRIVER_OK;
}

static int32_t USART_NonBlockingUninitialize(cmsis_usart_non_blocking_driver_state_t *usart)
{
    usart->flags = (uint8_t)USART_FLAG_UNINIT;
    return ARM_DRIVER_OK;
}

static int32_t USART_NonBlockingPowerControl(ARM_POWER_STATE state, cmsis_usart_non_blocking_driver_state_t *usart)
{
    usart_config_t config;
    int32_t result = ARM_DRIVER_OK;

    switch (state)
    {
        case ARM_POWER_OFF:
            if ((usart->flags & (uint8_t)USART_FLAG_POWER) != 0U)
            {
                USART_Deinit(usart->resource->base);
                usart->flags = (uint8_t)USART_FLAG_INIT;
            }
            break;
        case ARM_POWER_LOW:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
        case ARM_POWER_FULL:
            /* Must be initialized first. */
            if (usart->flags == (uint8_t)USART_FLAG_UNINIT)
            {
                result = ARM_DRIVER_ERROR;
                break;
            }

            if ((usart->flags & (uint8_t)USART_FLAG_POWER) != 0U)
            {
                /* Driver already powered */
                break;
            }

            USART_GetDefaultConfig(&config);
            config.enableTx = true;
            config.enableRx = true;

            (void)USART_Init(usart->resource->base, &config, usart->resource->GetFreq());
            (void)USART_TransferCreateHandle(usart->resource->base, usart->handle, KSDK_USART_NonBlockingCallback,
                                             (void *)usart->cb_event);
            usart->flags |= ((uint8_t)USART_FLAG_POWER | (uint8_t)USART_FLAG_CONFIGURED);

            break;
        default:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
    }

    return result;
}

static int32_t USART_NonBlockingSend(const void *data, uint32_t num, cmsis_usart_non_blocking_driver_state_t *usart)
{
    int32_t ret;
    status_t status;
    usart_transfer_t xfer;

    xfer.txData   = (const uint8_t *)data;
    xfer.dataSize = num;

    status = USART_TransferSendNonBlocking(usart->resource->base, usart->handle, &xfer);

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_USART_TxBusy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t USART_NonBlockingReceive(void *data, uint32_t num, cmsis_usart_non_blocking_driver_state_t *usart)
{
    int32_t ret;
    status_t status;
    usart_transfer_t xfer;

    xfer.rxData   = (uint8_t *)data;
    xfer.dataSize = num;

    status = USART_TransferReceiveNonBlocking(usart->resource->base, usart->handle, &xfer, NULL);

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_USART_RxBusy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t USART_NonBlockingTransfer(const void *data_out,
                                         void *data_in,
                                         uint32_t num,
                                         cmsis_usart_non_blocking_driver_state_t *usart)
{
    /* Only in synchronous mode */
    return ARM_DRIVER_ERROR;
}

static uint32_t USART_NonBlockingGetTxCount(cmsis_usart_non_blocking_driver_state_t *usart)
{
    uint32_t cnt;

    /* If TX not in progress, then the TX count is txDataSizeAll saved in handle. */
    if ((uint8_t)kUSART_TxIdle == usart->handle->txState)
    {
        cnt = usart->handle->txDataSizeAll;
    }
    else
    {
        cnt = usart->handle->txDataSizeAll - usart->handle->txDataSize;
    }

    return cnt;
}

static uint32_t USART_NonBlockingGetRxCount(cmsis_usart_non_blocking_driver_state_t *usart)
{
    uint32_t cnt;

    if ((uint8_t)kUSART_RxIdle == usart->handle->rxState)
    {
        cnt = usart->handle->rxDataSizeAll;
    }
    else
    {
        cnt = usart->handle->rxDataSizeAll - usart->handle->rxDataSize;
    }

    return cnt;
}

static int32_t USART_NonBlockingControl(uint32_t control, uint32_t arg, cmsis_usart_non_blocking_driver_state_t *usart)
{
    int32_t result  = ARM_DRIVER_OK;
    bool isContinue = false;
    /* Must be power on. */
    if (0U == (usart->flags & (uint8_t)USART_FLAG_POWER))
    {
        return ARM_DRIVER_ERROR;
    }

    /* Does not support these features. */
    if ((control & (ARM_USART_FLOW_CONTROL_Msk | ARM_USART_CPOL_Msk | ARM_USART_CPHA_Msk)) != 0U)
    {
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    switch (control & ARM_USART_CONTROL_Msk)
    {
        /* Abort Send */
        case ARM_USART_ABORT_SEND:
            usart->resource->base->FIFOINTENSET &= ~USART_FIFOINTENSET_TXLVL_MASK;
            usart->handle->txDataSize = 0;
            usart->handle->txState    = (uint8_t)kUSART_TxIdle;
            result                    = ARM_DRIVER_OK;
            break;

        /* Abort receive */
        case ARM_USART_ABORT_RECEIVE:
            usart->resource->base->FIFOINTENSET &= ~USART_FIFOINTENSET_RXLVL_MASK;
            usart->handle->rxDataSize = 0U;
            usart->handle->rxState    = (uint8_t)kUSART_RxIdle;
            result                    = ARM_DRIVER_OK;
            break;

        default:
            isContinue = true;
            break;
    }

    if (isContinue)
    {
        result = USART_CommonControl(control, arg, usart->resource, &usart->flags);
    }
    return result;
}

static ARM_USART_STATUS USART_NonBlockingGetStatus(cmsis_usart_non_blocking_driver_state_t *usart)
{
    ARM_USART_STATUS stat      = {0};
    uint32_t ksdk_usart_status = usart->resource->base->STAT;

    stat.tx_busy = (((uint8_t)kUSART_TxBusy == usart->handle->txState) ? (1U) : (0U));
    stat.rx_busy = (((uint8_t)kUSART_RxBusy == usart->handle->rxState) ? (1U) : (0U));

    stat.tx_underflow = 0U;
    stat.rx_overflow  = 0U;

    stat.rx_break = (uint32_t)(((ksdk_usart_status & (uint32_t)USART_STAT_RXBRK_MASK)) != 0U);

    stat.rx_framing_error = (uint32_t)(((ksdk_usart_status & USART_STAT_FRAMERRINT_MASK)) != 0U);
    stat.rx_parity_error  = (uint32_t)(((ksdk_usart_status & USART_STAT_PARITYERRINT_MASK)) != 0U);
    stat.reserved         = 0U;

    return stat;
}

#endif

#if defined(USART0) && defined(RTE_USART0) && RTE_USART0

/* User needs to provide the implementation for USART0_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t USART0_GetFreq(void);

static cmsis_usart_resource_t usart0_Resource = {USART0, USART0_GetFreq};

/* usart0 Driver Control Block */

#if defined(RTE_USART0_DMA_EN) && RTE_USART0_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_usart_dma_resource_t usart0_DmaResource = {
    RTE_USART0_DMA_TX_DMA_BASE,
    RTE_USART0_DMA_TX_CH,
    RTE_USART0_DMA_RX_DMA_BASE,
    RTE_USART0_DMA_RX_CH,
};

static usart_dma_handle_t USART0_DmaHandle;
static dma_handle_t USART0_DmaRxHandle;
static dma_handle_t USART0_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart0_dma_driver_state")
static cmsis_usart_dma_driver_state_t usart0_DmaDriverState = {
#else
static cmsis_usart_dma_driver_state_t usart0_DmaDriverState  = {
#endif
    &usart0_Resource, &usart0_DmaResource, &USART0_DmaHandle, &USART0_DmaRxHandle, &USART0_DmaTxHandle,
};

static int32_t USART0_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART0_PIN_INIT
    RTE_USART0_PIN_INIT();
#endif
    return USART_DmaInitialize(cb_event, &usart0_DmaDriverState);
}

static int32_t USART0_DmaUninitialize(void)
{
#ifdef RTE_USART0_PIN_DEINIT
    RTE_USART0_PIN_DEINIT();
#endif
    return USART_DmaUninitialize(&usart0_DmaDriverState);
}

static int32_t USART0_DmaPowerControl(ARM_POWER_STATE state)
{
    return USART_DmaPowerControl(state, &usart0_DmaDriverState);
}

static int32_t USART0_DmaSend(const void *data, uint32_t num)
{
    return USART_DmaSend(data, num, &usart0_DmaDriverState);
}

static int32_t USART0_DmaReceive(void *data, uint32_t num)
{
    return USART_DmaReceive(data, num, &usart0_DmaDriverState);
}

static int32_t USART0_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_DmaTransfer(data_out, data_in, num, &usart0_DmaDriverState);
}

static uint32_t USART0_DmaGetTxCount(void)
{
    return USART_DmaGetTxCount(&usart0_DmaDriverState);
}

static uint32_t USART0_DmaGetRxCount(void)
{
    return USART_DmaGetRxCount(&usart0_DmaDriverState);
}

static int32_t USART0_DmaControl(uint32_t control, uint32_t arg)
{
    return USART_DmaControl(control, arg, &usart0_DmaDriverState);
}

static ARM_USART_STATUS USART0_DmaGetStatus(void)
{
    return USART_DmaGetStatus(&usart0_DmaDriverState);
}

#endif

#else

static usart_handle_t USART0_Handle;
#if defined(USART0_RX_BUFFER_ENABLE) && (USART0_RX_BUFFER_ENABLE == 1)
static uint8_t usart0_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart0_non_blocking_driver_state")
static cmsis_usart_non_blocking_driver_state_t usart0_NonBlockingDriverState = {
#else
static cmsis_usart_non_blocking_driver_state_t usart0_NonBlockingDriverState  = {
#endif
    &usart0_Resource,
    &USART0_Handle,
};

static int32_t USART0_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART0_PIN_INIT
    RTE_USART0_PIN_INIT();
#endif
    return USART_NonBlockingInitialize(cb_event, &usart0_NonBlockingDriverState);
}

static int32_t USART0_NonBlockingUninitialize(void)
{
#ifdef RTE_USART0_PIN_DEINIT
    RTE_USART0_PIN_DEINIT();
#endif
    return USART_NonBlockingUninitialize(&usart0_NonBlockingDriverState);
}

static int32_t USART0_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    int32_t result;

    result = USART_NonBlockingPowerControl(state, &usart0_NonBlockingDriverState);
#if defined(USART0_RX_BUFFER_ENABLE) && (USART0_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (usart0_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        USART_TransferStartRingBuffer(usart0_NonBlockingDriverState.resource->base,
                                      usart0_NonBlockingDriverState.handle, usart0_rxRingBuffer, USART_RX_BUFFER_LEN);
    }
#endif
    return result;
}

static int32_t USART0_NonBlockingSend(const void *data, uint32_t num)
{
    return USART_NonBlockingSend(data, num, &usart0_NonBlockingDriverState);
}

static int32_t USART0_NonBlockingReceive(void *data, uint32_t num)
{
    return USART_NonBlockingReceive(data, num, &usart0_NonBlockingDriverState);
}

static int32_t USART0_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_NonBlockingTransfer(data_out, data_in, num, &usart0_NonBlockingDriverState);
}

static uint32_t USART0_NonBlockingGetTxCount(void)
{
    return USART_NonBlockingGetTxCount(&usart0_NonBlockingDriverState);
}

static uint32_t USART0_NonBlockingGetRxCount(void)
{
    return USART_NonBlockingGetRxCount(&usart0_NonBlockingDriverState);
}

static int32_t USART0_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = USART_NonBlockingControl(control, arg, &usart0_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }
#if defined(USART0_RX_BUFFER_ENABLE) && (USART0_RX_BUFFER_ENABLE == 1)
    /* Start receiving interrupts */
    usart0_NonBlockingDriverState.resource->base->FIFOINTENSET |=
        USART_FIFOINTENSET_RXLVL_MASK | USART_FIFOINTENSET_RXERR_MASK;
#endif
    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS USART0_NonBlockingGetStatus(void)
{
    return USART_NonBlockingGetStatus(&usart0_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART0 = {
    USARTx_GetVersion,      USARTx_GetCapabilities,
#if RTE_USART0_DMA_EN
    USART0_DmaInitialize,   USART0_DmaUninitialize, USART0_DmaPowerControl, USART0_DmaSend,    USART0_DmaReceive,
    USART0_DmaTransfer,     USART0_DmaGetTxCount,   USART0_DmaGetRxCount,   USART0_DmaControl, USART0_DmaGetStatus,
#else
    USART0_NonBlockingInitialize,
    USART0_NonBlockingUninitialize,
    USART0_NonBlockingPowerControl,
    USART0_NonBlockingSend,
    USART0_NonBlockingReceive,
    USART0_NonBlockingTransfer,
    USART0_NonBlockingGetTxCount,
    USART0_NonBlockingGetRxCount,
    USART0_NonBlockingControl,
    USART0_NonBlockingGetStatus,
#endif
    USARTx_SetModemControl, USARTx_GetModemStatus};

#endif /* usart0 */

#if defined(USART1) && defined(RTE_USART1) && RTE_USART1

/* User needs to provide the implementation for USART1_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t USART1_GetFreq(void);

static cmsis_usart_resource_t usart1_Resource = {USART1, USART1_GetFreq};

#if defined(RTE_USART1_DMA_EN) && RTE_USART1_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

cmsis_usart_dma_resource_t usart1_DmaResource = {
    RTE_USART1_DMA_TX_DMA_BASE,
    RTE_USART1_DMA_TX_CH,
    RTE_USART1_DMA_RX_DMA_BASE,
    RTE_USART1_DMA_RX_CH,
};

static usart_dma_handle_t USART1_DmaHandle;
static dma_handle_t USART1_DmaRxHandle;
static dma_handle_t USART1_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart1_dma_driver_state")
static cmsis_usart_dma_driver_state_t usart1_DmaDriverState = {
#else
static cmsis_usart_dma_driver_state_t usart1_DmaDriverState  = {
#endif
    &usart1_Resource, &usart1_DmaResource, &USART1_DmaHandle, &USART1_DmaRxHandle, &USART1_DmaTxHandle,
};

static int32_t USART1_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART1_PIN_INIT
    RTE_USART1_PIN_INIT();
#endif
    return USART_DmaInitialize(cb_event, &usart1_DmaDriverState);
}

static int32_t USART1_DmaUninitialize(void)
{
#ifdef RTE_USART1_PIN_DEINIT
    RTE_USART1_PIN_DEINIT();
#endif
    return USART_DmaUninitialize(&usart1_DmaDriverState);
}

static int32_t USART1_DmaPowerControl(ARM_POWER_STATE state)
{
    return USART_DmaPowerControl(state, &usart1_DmaDriverState);
}

static int32_t USART1_DmaSend(const void *data, uint32_t num)
{
    return USART_DmaSend(data, num, &usart1_DmaDriverState);
}

static int32_t USART1_DmaReceive(void *data, uint32_t num)
{
    return USART_DmaReceive(data, num, &usart1_DmaDriverState);
}

static int32_t USART1_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_DmaTransfer(data_out, data_in, num, &usart1_DmaDriverState);
}

static uint32_t USART1_DmaGetTxCount(void)
{
    return USART_DmaGetTxCount(&usart1_DmaDriverState);
}

static uint32_t USART1_DmaGetRxCount(void)
{
    return USART_DmaGetRxCount(&usart1_DmaDriverState);
}

static int32_t USART1_DmaControl(uint32_t control, uint32_t arg)
{
    return USART_DmaControl(control, arg, &usart1_DmaDriverState);
}

static ARM_USART_STATUS USART1_DmaGetStatus(void)
{
    return USART_DmaGetStatus(&usart1_DmaDriverState);
}

#endif

#else

static usart_handle_t USART1_Handle;
#if defined(USART1_RX_BUFFER_ENABLE) && (USART1_RX_BUFFER_ENABLE == 1)
static uint8_t usart1_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart1_non_blocking_driver_state")
static cmsis_usart_non_blocking_driver_state_t usart1_NonBlockingDriverState = {
#else
static cmsis_usart_non_blocking_driver_state_t usart1_NonBlockingDriverState  = {
#endif
    &usart1_Resource,
    &USART1_Handle,
};

static int32_t USART1_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART1_PIN_INIT
    RTE_USART1_PIN_INIT();
#endif
    return USART_NonBlockingInitialize(cb_event, &usart1_NonBlockingDriverState);
}

static int32_t USART1_NonBlockingUninitialize(void)
{
#ifdef RTE_USART1_PIN_DEINIT
    RTE_USART1_PIN_DEINIT();
#endif
    return USART_NonBlockingUninitialize(&usart1_NonBlockingDriverState);
}

static int32_t USART1_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    int32_t result;

    result = USART_NonBlockingPowerControl(state, &usart1_NonBlockingDriverState);
#if defined(USART1_RX_BUFFER_ENABLE) && (USART1_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (usart1_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        USART_TransferStartRingBuffer(usart1_NonBlockingDriverState.resource->base,
                                      usart1_NonBlockingDriverState.handle, usart1_rxRingBuffer, USART_RX_BUFFER_LEN);
    }
#endif
    return result;
}

static int32_t USART1_NonBlockingSend(const void *data, uint32_t num)
{
    return USART_NonBlockingSend(data, num, &usart1_NonBlockingDriverState);
}

static int32_t USART1_NonBlockingReceive(void *data, uint32_t num)
{
    return USART_NonBlockingReceive(data, num, &usart1_NonBlockingDriverState);
}

static int32_t USART1_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_NonBlockingTransfer(data_out, data_in, num, &usart1_NonBlockingDriverState);
}

static uint32_t USART1_NonBlockingGetTxCount(void)
{
    return USART_NonBlockingGetTxCount(&usart1_NonBlockingDriverState);
}

static uint32_t USART1_NonBlockingGetRxCount(void)
{
    return USART_NonBlockingGetRxCount(&usart1_NonBlockingDriverState);
}

static int32_t USART1_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = USART_NonBlockingControl(control, arg, &usart1_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }
#if defined(USART1_RX_BUFFER_ENABLE) && (USART1_RX_BUFFER_ENABLE == 1)
    /* Start receiving interrupts */
    usart1_NonBlockingDriverState.resource->base->FIFOINTENSET |=
        USART_FIFOINTENSET_RXLVL_MASK | USART_FIFOINTENSET_RXERR_MASK;
#endif
    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS USART1_NonBlockingGetStatus(void)
{
    return USART_NonBlockingGetStatus(&usart1_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART1 = {
    USARTx_GetVersion,      USARTx_GetCapabilities,
#if RTE_USART1_DMA_EN
    USART1_DmaInitialize,   USART1_DmaUninitialize, USART1_DmaPowerControl, USART1_DmaSend,    USART1_DmaReceive,
    USART1_DmaTransfer,     USART1_DmaGetTxCount,   USART1_DmaGetRxCount,   USART1_DmaControl, USART1_DmaGetStatus,
#else
    USART1_NonBlockingInitialize,
    USART1_NonBlockingUninitialize,
    USART1_NonBlockingPowerControl,
    USART1_NonBlockingSend,
    USART1_NonBlockingReceive,
    USART1_NonBlockingTransfer,
    USART1_NonBlockingGetTxCount,
    USART1_NonBlockingGetRxCount,
    USART1_NonBlockingControl,
    USART1_NonBlockingGetStatus,
#endif
    USARTx_SetModemControl, USARTx_GetModemStatus};

#endif /* usart1 */

#if defined(USART2) && defined(RTE_USART2) && RTE_USART2

/* User needs to provide the implementation for USART2_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t USART2_GetFreq(void);

static cmsis_usart_resource_t usart2_Resource = {USART2, USART2_GetFreq};

/* usart2 Driver Control Block */

#if defined(RTE_USART2_DMA_EN) && RTE_USART2_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

cmsis_usart_dma_resource_t usart2_DmaResource = {
    RTE_USART2_DMA_TX_DMA_BASE,
    RTE_USART2_DMA_TX_CH,
    RTE_USART2_DMA_RX_DMA_BASE,
    RTE_USART2_DMA_RX_CH,
};

static usart_dma_handle_t USART2_DmaHandle;
static dma_handle_t USART2_DmaRxHandle;
static dma_handle_t USART2_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart2_dma_driver_state")
static cmsis_usart_dma_driver_state_t usart2_DmaDriverState = {
#else
static cmsis_usart_dma_driver_state_t usart2_DmaDriverState  = {
#endif
    &usart2_Resource, &usart2_DmaResource, &USART2_DmaHandle, &USART2_DmaRxHandle, &USART2_DmaTxHandle,
};

static int32_t USART2_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART2_PIN_INIT
    RTE_USART2_PIN_INIT();
#endif
    return USART_DmaInitialize(cb_event, &usart2_DmaDriverState);
}

static int32_t USART2_DmaUninitialize(void)
{
#ifdef RTE_USART2_PIN_DEINIT
    RTE_USART2_PIN_DEINIT();
#endif
    return USART_DmaUninitialize(&usart2_DmaDriverState);
}

static int32_t USART2_DmaPowerControl(ARM_POWER_STATE state)
{
    return USART_DmaPowerControl(state, &usart2_DmaDriverState);
}

static int32_t USART2_DmaSend(const void *data, uint32_t num)
{
    return USART_DmaSend(data, num, &usart2_DmaDriverState);
}

static int32_t USART2_DmaReceive(void *data, uint32_t num)
{
    return USART_DmaReceive(data, num, &usart2_DmaDriverState);
}

static int32_t USART2_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_DmaTransfer(data_out, data_in, num, &usart2_DmaDriverState);
}

static uint32_t USART2_DmaGetTxCount(void)
{
    return USART_DmaGetTxCount(&usart2_DmaDriverState);
}

static uint32_t USART2_DmaGetRxCount(void)
{
    return USART_DmaGetRxCount(&usart2_DmaDriverState);
}

static int32_t USART2_DmaControl(uint32_t control, uint32_t arg)
{
    return USART_DmaControl(control, arg, &usart2_DmaDriverState);
}

static ARM_USART_STATUS USART2_DmaGetStatus(void)
{
    return USART_DmaGetStatus(&usart2_DmaDriverState);
}

#endif

#else

static usart_handle_t USART2_Handle;
#if defined(USART2_RX_BUFFER_ENABLE) && (USART2_RX_BUFFER_ENABLE == 1)
static uint8_t usart2_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart2_non_blocking_driver_state")
static cmsis_usart_non_blocking_driver_state_t usart2_NonBlockingDriverState = {
#else
static cmsis_usart_non_blocking_driver_state_t usart2_NonBlockingDriverState  = {
#endif
    &usart2_Resource,
    &USART2_Handle,
};

static int32_t USART2_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART2_PIN_INIT
    RTE_USART2_PIN_INIT();
#endif
    return USART_NonBlockingInitialize(cb_event, &usart2_NonBlockingDriverState);
}

static int32_t USART2_NonBlockingUninitialize(void)
{
#ifdef RTE_USART2_PIN_DEINIT
    RTE_USART2_PIN_DEINIT();
#endif
    return USART_NonBlockingUninitialize(&usart2_NonBlockingDriverState);
}

static int32_t USART2_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    int32_t result;

    result = USART_NonBlockingPowerControl(state, &usart2_NonBlockingDriverState);
#if defined(USART2_RX_BUFFER_ENABLE) && (USART2_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (usart2_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        USART_TransferStartRingBuffer(usart2_NonBlockingDriverState.resource->base,
                                      usart2_NonBlockingDriverState.handle, usart2_rxRingBuffer, USART_RX_BUFFER_LEN);
    }
#endif
    return result;
}

static int32_t USART2_NonBlockingSend(const void *data, uint32_t num)
{
    return USART_NonBlockingSend(data, num, &usart2_NonBlockingDriverState);
}

static int32_t USART2_NonBlockingReceive(void *data, uint32_t num)
{
    return USART_NonBlockingReceive(data, num, &usart2_NonBlockingDriverState);
}

static int32_t USART2_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_NonBlockingTransfer(data_out, data_in, num, &usart2_NonBlockingDriverState);
}

static uint32_t USART2_NonBlockingGetTxCount(void)
{
    return USART_NonBlockingGetTxCount(&usart2_NonBlockingDriverState);
}

static uint32_t USART2_NonBlockingGetRxCount(void)
{
    return USART_NonBlockingGetRxCount(&usart2_NonBlockingDriverState);
}

static int32_t USART2_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = USART_NonBlockingControl(control, arg, &usart2_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }
#if defined(USART2_RX_BUFFER_ENABLE) && (USART2_RX_BUFFER_ENABLE == 1)
    /* Start receiving interrupts */
    usart2_NonBlockingDriverState.resource->base->FIFOINTENSET |=
        USART_FIFOINTENSET_RXLVL_MASK | USART_FIFOINTENSET_RXERR_MASK;
#endif
    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS USART2_NonBlockingGetStatus(void)
{
    return USART_NonBlockingGetStatus(&usart2_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART2 = {
    USARTx_GetVersion,      USARTx_GetCapabilities,
#if RTE_USART2_DMA_EN
    USART2_DmaInitialize,   USART2_DmaUninitialize, USART2_DmaPowerControl, USART2_DmaSend,    USART2_DmaReceive,
    USART2_DmaTransfer,     USART2_DmaGetTxCount,   USART2_DmaGetRxCount,   USART2_DmaControl, USART2_DmaGetStatus,
#else
    USART2_NonBlockingInitialize,
    USART2_NonBlockingUninitialize,
    USART2_NonBlockingPowerControl,
    USART2_NonBlockingSend,
    USART2_NonBlockingReceive,
    USART2_NonBlockingTransfer,
    USART2_NonBlockingGetTxCount,
    USART2_NonBlockingGetRxCount,
    USART2_NonBlockingControl,
    USART2_NonBlockingGetStatus,
#endif
    USARTx_SetModemControl, USARTx_GetModemStatus};

#endif /* usart2 */

#if defined(USART3) && defined(RTE_USART3) && RTE_USART3

/* User needs to provide the implementation for USART3_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t USART3_GetFreq(void);

static cmsis_usart_resource_t usart3_Resource = {USART3, USART3_GetFreq};

/* usart3 Driver Control Block */
#if defined(RTE_USART3_DMA_EN) && RTE_USART3_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

cmsis_usart_dma_resource_t usart3_DmaResource = {
    RTE_USART3_DMA_TX_DMA_BASE,
    RTE_USART3_DMA_TX_CH,
    RTE_USART3_DMA_RX_DMA_BASE,
    RTE_USART3_DMA_RX_CH,
};

static usart_dma_handle_t USART3_DmaHandle;
static dma_handle_t USART3_DmaRxHandle;
static dma_handle_t USART3_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart3_dma_driver_state")
static cmsis_usart_dma_driver_state_t usart3_DmaDriverState = {
#else
static cmsis_usart_dma_driver_state_t usart3_DmaDriverState  = {
#endif
    &usart3_Resource, &usart3_DmaResource, &USART3_DmaHandle, &USART3_DmaRxHandle, &USART3_DmaTxHandle,
};

static int32_t USART3_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART3_PIN_INIT
    RTE_USART3_PIN_INIT();
#endif
    return USART_DmaInitialize(cb_event, &usart3_DmaDriverState);
}

static int32_t USART3_DmaUninitialize(void)
{
#ifdef RTE_USART3_PIN_DEINIT
    RTE_USART3_PIN_DEINIT();
#endif
    return USART_DmaUninitialize(&usart3_DmaDriverState);
}

static int32_t USART3_DmaPowerControl(ARM_POWER_STATE state)
{
    return USART_DmaPowerControl(state, &usart3_DmaDriverState);
}

static int32_t USART3_DmaSend(const void *data, uint32_t num)
{
    return USART_DmaSend(data, num, &usart3_DmaDriverState);
}

static int32_t USART3_DmaReceive(void *data, uint32_t num)
{
    return USART_DmaReceive(data, num, &usart3_DmaDriverState);
}

static int32_t USART3_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_DmaTransfer(data_out, data_in, num, &usart3_DmaDriverState);
}

static uint32_t USART3_DmaGetTxCount(void)
{
    return USART_DmaGetTxCount(&usart3_DmaDriverState);
}

static uint32_t USART3_DmaGetRxCount(void)
{
    return USART_DmaGetRxCount(&usart3_DmaDriverState);
}

static int32_t USART3_DmaControl(uint32_t control, uint32_t arg)
{
    return USART_DmaControl(control, arg, &usart3_DmaDriverState);
}

static ARM_USART_STATUS USART3_DmaGetStatus(void)
{
    return USART_DmaGetStatus(&usart3_DmaDriverState);
}

#endif

#else

static usart_handle_t USART3_Handle;
#if defined(USART3_RX_BUFFER_ENABLE) && (USART3_RX_BUFFER_ENABLE == 1)
static uint8_t usart3_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart3_non_blocking_driver_state")
static cmsis_usart_non_blocking_driver_state_t usart3_NonBlockingDriverState = {
#else
static cmsis_usart_non_blocking_driver_state_t usart3_NonBlockingDriverState  = {
#endif
    &usart3_Resource,
    &USART3_Handle,
};

static int32_t USART3_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART3_PIN_INIT
    RTE_USART3_PIN_INIT();
#endif
    return USART_NonBlockingInitialize(cb_event, &usart3_NonBlockingDriverState);
}

static int32_t USART3_NonBlockingUninitialize(void)
{
#ifdef RTE_USART3_PIN_DEINIT
    RTE_USART3_PIN_DEINIT();
#endif
    return USART_NonBlockingUninitialize(&usart3_NonBlockingDriverState);
}

static int32_t USART3_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    int32_t result;

    result = USART_NonBlockingPowerControl(state, &usart3_NonBlockingDriverState);
#if defined(USART3_RX_BUFFER_ENABLE) && (USART3_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (usart3_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        USART_TransferStartRingBuffer(usart3_NonBlockingDriverState.resource->base,
                                      usart3_NonBlockingDriverState.handle, usart3_rxRingBuffer, USART_RX_BUFFER_LEN);
    }
#endif
    return result;
}

static int32_t USART3_NonBlockingSend(const void *data, uint32_t num)
{
    return USART_NonBlockingSend(data, num, &usart3_NonBlockingDriverState);
}

static int32_t USART3_NonBlockingReceive(void *data, uint32_t num)
{
    return USART_NonBlockingReceive(data, num, &usart3_NonBlockingDriverState);
}

static int32_t USART3_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_NonBlockingTransfer(data_out, data_in, num, &usart3_NonBlockingDriverState);
}

static uint32_t USART3_NonBlockingGetTxCount(void)
{
    return USART_NonBlockingGetTxCount(&usart3_NonBlockingDriverState);
}

static uint32_t USART3_NonBlockingGetRxCount(void)
{
    return USART_NonBlockingGetRxCount(&usart3_NonBlockingDriverState);
}

static int32_t USART3_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = USART_NonBlockingControl(control, arg, &usart3_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }
#if defined(USART3_RX_BUFFER_ENABLE) && (USART3_RX_BUFFER_ENABLE == 1)
    /* Start receiving interrupts */
    usart3_NonBlockingDriverState.resource->base->FIFOINTENSET |=
        USART_FIFOINTENSET_RXLVL_MASK | USART_FIFOINTENSET_RXERR_MASK;
#endif
    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS USART3_NonBlockingGetStatus(void)
{
    return USART_NonBlockingGetStatus(&usart3_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART3 = {
    USARTx_GetVersion,      USARTx_GetCapabilities,
#if RTE_USART3_DMA_EN
    USART3_DmaInitialize,   USART3_DmaUninitialize, USART3_DmaPowerControl, USART3_DmaSend,    USART3_DmaReceive,
    USART3_DmaTransfer,     USART3_DmaGetTxCount,   USART3_DmaGetRxCount,   USART3_DmaControl, USART3_DmaGetStatus,
#else
    USART3_NonBlockingInitialize,
    USART3_NonBlockingUninitialize,
    USART3_NonBlockingPowerControl,
    USART3_NonBlockingSend,
    USART3_NonBlockingReceive,
    USART3_NonBlockingTransfer,
    USART3_NonBlockingGetTxCount,
    USART3_NonBlockingGetRxCount,
    USART3_NonBlockingControl,
    USART3_NonBlockingGetStatus,
#endif
    USARTx_SetModemControl, USARTx_GetModemStatus};

#endif /* usart3 */

#if defined(USART4) && defined(RTE_USART4) && RTE_USART4

/* User needs to provide the implementation for USART4_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t USART4_GetFreq(void);

static cmsis_usart_resource_t usart4_Resource = {USART4, USART4_GetFreq};

#if defined(RTE_USART4_DMA_EN) && RTE_USART4_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

cmsis_usart_dma_resource_t usart4_DmaResource = {
    RTE_USART4_DMA_TX_DMA_BASE,
    RTE_USART4_DMA_TX_CH,
    RTE_USART4_DMA_RX_DMA_BASE,
    RTE_USART4_DMA_RX_CH,
};

static usart_dma_handle_t USART4_DmaHandle;
static dma_handle_t USART4_DmaRxHandle;
static dma_handle_t USART4_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart4_dma_driver_state")
static cmsis_usart_dma_driver_state_t usart4_DmaDriverState = {
#else
static cmsis_usart_dma_driver_state_t usart4_DmaDriverState  = {
#endif
    &usart4_Resource, &usart4_DmaResource, &USART4_DmaHandle, &USART4_DmaRxHandle, &USART4_DmaTxHandle,
};

static int32_t USART4_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART4_PIN_INIT
    RTE_USART4_PIN_INIT();
#endif
    return USART_DmaInitialize(cb_event, &usart4_DmaDriverState);
}

static int32_t USART4_DmaUninitialize(void)
{
#ifdef RTE_USART4_PIN_DEINIT
    RTE_USART4_PIN_DEINIT();
#endif
    return USART_DmaUninitialize(&usart4_DmaDriverState);
}

static int32_t USART4_DmaPowerControl(ARM_POWER_STATE state)
{
    return USART_DmaPowerControl(state, &usart4_DmaDriverState);
}

static int32_t USART4_DmaSend(const void *data, uint32_t num)
{
    return USART_DmaSend(data, num, &usart4_DmaDriverState);
}

static int32_t USART4_DmaReceive(void *data, uint32_t num)
{
    return USART_DmaReceive(data, num, &usart4_DmaDriverState);
}

static int32_t USART4_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_DmaTransfer(data_out, data_in, num, &usart4_DmaDriverState);
}

static uint32_t USART4_DmaGetTxCount(void)
{
    return USART_DmaGetTxCount(&usart4_DmaDriverState);
}

static uint32_t USART4_DmaGetRxCount(void)
{
    return USART_DmaGetRxCount(&usart4_DmaDriverState);
}

static int32_t USART4_DmaControl(uint32_t control, uint32_t arg)
{
    return USART_DmaControl(control, arg, &usart4_DmaDriverState);
}

static ARM_USART_STATUS USART4_DmaGetStatus(void)
{
    return USART_DmaGetStatus(&usart4_DmaDriverState);
}

#endif

#else

static usart_handle_t USART4_Handle;
#if defined(USART4_RX_BUFFER_ENABLE) && (USART4_RX_BUFFER_ENABLE == 1)
static uint8_t usart4_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart4_non_blocking_driver_state")
static cmsis_usart_non_blocking_driver_state_t usart4_NonBlockingDriverState = {
#else
static cmsis_usart_non_blocking_driver_state_t usart4_NonBlockingDriverState  = {
#endif
    &usart4_Resource,
    &USART4_Handle,
};

static int32_t USART4_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART4_PIN_INIT
    RTE_USART4_PIN_INIT();
#endif
    return USART_NonBlockingInitialize(cb_event, &usart4_NonBlockingDriverState);
}

static int32_t USART4_NonBlockingUninitialize(void)
{
#ifdef RTE_USART4_PIN_DEINIT
    RTE_USART4_PIN_DEINIT();
#endif
    return USART_NonBlockingUninitialize(&usart4_NonBlockingDriverState);
}

static int32_t USART4_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    uint32_t result;

    result = USART_NonBlockingPowerControl(state, &usart4_NonBlockingDriverState);
#if defined(USART4_RX_BUFFER_ENABLE) && (USART4_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (usart4_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        USART_TransferStartRingBuffer(usart4_NonBlockingDriverState.resource->base,
                                      usart4_NonBlockingDriverState.handle, usart4_rxRingBuffer, USART_RX_BUFFER_LEN);
    }
#endif
    return result;
}

static int32_t USART4_NonBlockingSend(const void *data, uint32_t num)
{
    return USART_NonBlockingSend(data, num, &usart4_NonBlockingDriverState);
}

static int32_t USART4_NonBlockingReceive(void *data, uint32_t num)
{
    return USART_NonBlockingReceive(data, num, &usart4_NonBlockingDriverState);
}

static int32_t USART4_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_NonBlockingTransfer(data_out, data_in, num, &usart4_NonBlockingDriverState);
}

static uint32_t USART4_NonBlockingGetTxCount(void)
{
    return USART_NonBlockingGetTxCount(&usart4_NonBlockingDriverState);
}

static uint32_t USART4_NonBlockingGetRxCount(void)
{
    return USART_NonBlockingGetRxCount(&usart4_NonBlockingDriverState);
}

static int32_t USART4_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = USART_NonBlockingControl(control, arg, &usart4_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }
#if defined(USART4_RX_BUFFER_ENABLE) && (USART4_RX_BUFFER_ENABLE == 1)
    /* Start receiving interrupts */
    usart4_NonBlockingDriverState.resource->base->FIFOINTENSET |=
        USART_FIFOINTENSET_RXLVL_MASK | USART_FIFOINTENSET_RXERR_MASK;
#endif
    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS USART4_NonBlockingGetStatus(void)
{
    return USART_NonBlockingGetStatus(&usart4_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART4 = {
    USARTx_GetVersion,      USARTx_GetCapabilities,
#if RTE_USART4_DMA_EN
    USART4_DmaInitialize,   USART4_DmaUninitialize, USART4_DmaPowerControl, USART4_DmaSend,    USART4_DmaReceive,
    USART4_DmaTransfer,     USART4_DmaGetTxCount,   USART4_DmaGetRxCount,   USART4_DmaControl, USART4_DmaGetStatus,
#else
    USART4_NonBlockingInitialize,
    USART4_NonBlockingUninitialize,
    USART4_NonBlockingPowerControl,
    USART4_NonBlockingSend,
    USART4_NonBlockingReceive,
    USART4_NonBlockingTransfer,
    USART4_NonBlockingGetTxCount,
    USART4_NonBlockingGetRxCount,
    USART4_NonBlockingControl,
    USART4_NonBlockingGetStatus,
#endif
    USARTx_SetModemControl, USARTx_GetModemStatus};

#endif /* usart4 */

#if defined(USART5) && defined(RTE_USART5) && RTE_USART5

/* User needs to provide the implementation for USART5_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t USART5_GetFreq(void);

static cmsis_usart_resource_t usart5_Resource = {USART5, USART5_GetFreq};

#if defined(RTE_USART5_DMA_EN) && RTE_USART5_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

cmsis_usart_dma_resource_t usart5_DmaResource = {
    RTE_USART5_DMA_TX_DMA_BASE,
    RTE_USART5_DMA_TX_CH,
    RTE_USART5_DMA_RX_DMA_BASE,
    RTE_USART5_DMA_RX_CH,
};

static usart_dma_handle_t USART5_DmaHandle;
static dma_handle_t USART5_DmaRxHandle;
static dma_handle_t USART5_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart5_dma_driver_state")
static cmsis_usart_dma_driver_state_t usart5_DmaDriverState = {
#else
static cmsis_usart_dma_driver_state_t usart5_DmaDriverState  = {
#endif
    &usart5_Resource, &usart5_DmaResource, &USART5_DmaHandle, &USART5_DmaRxHandle, &USART5_DmaTxHandle,
};

static int32_t USART5_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART5_PIN_INIT
    RTE_USART5_PIN_INIT();
#endif
    return USART_DmaInitialize(cb_event, &usart5_DmaDriverState);
}

static int32_t USART5_DmaUninitialize(void)
{
#ifdef RTE_USART5_PIN_DEINIT
    RTE_USART5_PIN_DEINIT();
#endif
    return USART_DmaUninitialize(&usart5_DmaDriverState);
}

static int32_t USART5_DmaPowerControl(ARM_POWER_STATE state)
{
    return USART_DmaPowerControl(state, &usart5_DmaDriverState);
}

static int32_t USART5_DmaSend(const void *data, uint32_t num)
{
    return USART_DmaSend(data, num, &usart5_DmaDriverState);
}

static int32_t USART5_DmaReceive(void *data, uint32_t num)
{
    return USART_DmaReceive(data, num, &usart5_DmaDriverState);
}

static int32_t USART5_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_DmaTransfer(data_out, data_in, num, &usart5_DmaDriverState);
}

static uint32_t USART5_DmaGetTxCount(void)
{
    return USART_DmaGetTxCount(&usart5_DmaDriverState);
}

static uint32_t USART5_DmaGetRxCount(void)
{
    return USART_DmaGetRxCount(&usart5_DmaDriverState);
}

static int32_t USART5_DmaControl(uint32_t control, uint32_t arg)
{
    return USART_DmaControl(control, arg, &usart5_DmaDriverState);
}

static ARM_USART_STATUS USART5_DmaGetStatus(void)
{
    return USART_DmaGetStatus(&usart5_DmaDriverState);
}

#endif

#else

static usart_handle_t USART5_Handle;
#if defined(USART5_RX_BUFFER_ENABLE) && (USART5_RX_BUFFER_ENABLE == 1)
static uint8_t usart5_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart5_non_blocking_driver_state")
static cmsis_usart_non_blocking_driver_state_t usart5_NonBlockingDriverState = {
#else
static cmsis_usart_non_blocking_driver_state_t usart5_NonBlockingDriverState  = {
#endif
    &usart5_Resource,
    &USART5_Handle,
};

static int32_t USART5_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART5_PIN_INIT
    RTE_USART5_PIN_INIT();
#endif
    return USART_NonBlockingInitialize(cb_event, &usart5_NonBlockingDriverState);
}

static int32_t USART5_NonBlockingUninitialize(void)
{
#ifdef RTE_USART5_PIN_DEINIT
    RTE_USART5_PIN_DEINIT();
#endif
    return USART_NonBlockingUninitialize(&usart5_NonBlockingDriverState);
}

static int32_t USART5_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    int32_t result;

    result = USART_NonBlockingPowerControl(state, &usart5_NonBlockingDriverState);
#if defined(USART5_RX_BUFFER_ENABLE) && (USART5_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (usart5_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        USART_TransferStartRingBuffer(usart5_NonBlockingDriverState.resource->base,
                                      usart5_NonBlockingDriverState.handle, usart5_rxRingBuffer, USART_RX_BUFFER_LEN);
    }
#endif
    return result;
}

static int32_t USART5_NonBlockingSend(const void *data, uint32_t num)
{
    return USART_NonBlockingSend(data, num, &usart5_NonBlockingDriverState);
}

static int32_t USART5_NonBlockingReceive(void *data, uint32_t num)
{
    return USART_NonBlockingReceive(data, num, &usart5_NonBlockingDriverState);
}

static int32_t USART5_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_NonBlockingTransfer(data_out, data_in, num, &usart5_NonBlockingDriverState);
}

static uint32_t USART5_NonBlockingGetTxCount(void)
{
    return USART_NonBlockingGetTxCount(&usart5_NonBlockingDriverState);
}

static uint32_t USART5_NonBlockingGetRxCount(void)
{
    return USART_NonBlockingGetRxCount(&usart5_NonBlockingDriverState);
}

static int32_t USART5_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = USART_NonBlockingControl(control, arg, &usart5_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }
#if defined(USART5_RX_BUFFER_ENABLE) && (USART5_RX_BUFFER_ENABLE == 1)
    /* Start receiving interrupts */
    usart5_NonBlockingDriverState.resource->base->FIFOINTENSET |=
        USART_FIFOINTENSET_RXLVL_MASK | USART_FIFOINTENSET_RXERR_MASK;
#endif
    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS USART5_NonBlockingGetStatus(void)
{
    return USART_NonBlockingGetStatus(&usart5_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART5 = {
    USARTx_GetVersion,      USARTx_GetCapabilities,
#if RTE_USART5_DMA_EN
    USART5_DmaInitialize,   USART5_DmaUninitialize, USART5_DmaPowerControl, USART5_DmaSend,    USART5_DmaReceive,
    USART5_DmaTransfer,     USART5_DmaGetTxCount,   USART5_DmaGetRxCount,   USART5_DmaControl, USART5_DmaGetStatus,
#else
    USART5_NonBlockingInitialize,
    USART5_NonBlockingUninitialize,
    USART5_NonBlockingPowerControl,
    USART5_NonBlockingSend,
    USART5_NonBlockingReceive,
    USART5_NonBlockingTransfer,
    USART5_NonBlockingGetTxCount,
    USART5_NonBlockingGetRxCount,
    USART5_NonBlockingControl,
    USART5_NonBlockingGetStatus,
#endif
    USARTx_SetModemControl, USARTx_GetModemStatus};

#endif /* usart5 */

#if defined(USART6) && defined(RTE_USART6) && RTE_USART6

/* User needs to provide the implementation for USART6_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t USART6_GetFreq(void);

static cmsis_usart_resource_t usart6_Resource = {USART6, USART6_GetFreq};

#if defined(RTE_USART6_DMA_EN) && RTE_USART6_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

cmsis_usart_dma_resource_t usart6_DmaResource = {
    RTE_USART6_DMA_TX_DMA_BASE,
    RTE_USART6_DMA_TX_CH,
    RTE_USART6_DMA_RX_DMA_BASE,
    RTE_USART6_DMA_RX_CH,
};

static usart_dma_handle_t USART6_DmaHandle;
static dma_handle_t USART6_DmaRxHandle;
static dma_handle_t USART6_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart6_dma_driver_state")
static cmsis_usart_dma_driver_state_t usart6_DmaDriverState = {
#else
static cmsis_usart_dma_driver_state_t usart6_DmaDriverState  = {
#endif
    &usart6_Resource, &usart6_DmaResource, &USART6_DmaHandle, &USART6_DmaRxHandle, &USART6_DmaTxHandle,
};

static int32_t USART6_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART6_PIN_INIT
    RTE_USART6_PIN_INIT();
#endif
    return USART_DmaInitialize(cb_event, &usart6_DmaDriverState);
}

static int32_t USART6_DmaUninitialize(void)
{
#ifdef RTE_USART6_PIN_DEINIT
    RTE_USART6_PIN_DEINIT();
#endif
    return USART_DmaUninitialize(&usart6_DmaDriverState);
}

static int32_t USART6_DmaPowerControl(ARM_POWER_STATE state)
{
    return USART_DmaPowerControl(state, &usart6_DmaDriverState);
}

static int32_t USART6_DmaSend(const void *data, uint32_t num)
{
    return USART_DmaSend(data, num, &usart6_DmaDriverState);
}

static int32_t USART6_DmaReceive(void *data, uint32_t num)
{
    return USART_DmaReceive(data, num, &usart6_DmaDriverState);
}

static int32_t USART6_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_DmaTransfer(data_out, data_in, num, &usart6_DmaDriverState);
}

static uint32_t USART6_DmaGetTxCount(void)
{
    return USART_DmaGetTxCount(&usart6_DmaDriverState);
}

static uint32_t USART6_DmaGetRxCount(void)
{
    return USART_DmaGetRxCount(&usart6_DmaDriverState);
}

static int32_t USART6_DmaControl(uint32_t control, uint32_t arg)
{
    return USART_DmaControl(control, arg, &usart6_DmaDriverState);
}

static ARM_USART_STATUS USART6_DmaGetStatus(void)
{
    return USART_DmaGetStatus(&usart6_DmaDriverState);
}

#endif

#else

static usart_handle_t USART6_Handle;
#if defined(USART6_RX_BUFFER_ENABLE) && (USART6_RX_BUFFER_ENABLE == 1)
static uint8_t usart6_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart6_non_blocking_driver_state")
static cmsis_usart_non_blocking_driver_state_t usart6_NonBlockingDriverState = {
#else
static cmsis_usart_non_blocking_driver_state_t usart6_NonBlockingDriverState  = {
#endif
    &usart6_Resource,
    &USART6_Handle,
};

static int32_t USART6_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART6_PIN_INIT
    RTE_USART6_PIN_INIT();
#endif
    return USART_NonBlockingInitialize(cb_event, &usart6_NonBlockingDriverState);
}

static int32_t USART6_NonBlockingUninitialize(void)
{
#ifdef RTE_USART6_PIN_DEINIT
    RTE_USART6_PIN_DEINIT();
#endif
    return USART_NonBlockingUninitialize(&usart6_NonBlockingDriverState);
}

static int32_t USART6_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    uint32_t result;

    result = USART_NonBlockingPowerControl(state, &usart6_NonBlockingDriverState);
#if defined(USART6_RX_BUFFER_ENABLE) && (USART6_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (usart6_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        USART_TransferStartRingBuffer(usart6_NonBlockingDriverState.resource->base,
                                      usart6_NonBlockingDriverState.handle, usart6_rxRingBuffer, USART_RX_BUFFER_LEN);
    }
#endif
    return result;
}

static int32_t USART6_NonBlockingSend(const void *data, uint32_t num)
{
    return USART_NonBlockingSend(data, num, &usart6_NonBlockingDriverState);
}

static int32_t USART6_NonBlockingReceive(void *data, uint32_t num)
{
    return USART_NonBlockingReceive(data, num, &usart6_NonBlockingDriverState);
}

static int32_t USART6_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_NonBlockingTransfer(data_out, data_in, num, &usart6_NonBlockingDriverState);
}

static uint32_t USART6_NonBlockingGetTxCount(void)
{
    return USART_NonBlockingGetTxCount(&usart6_NonBlockingDriverState);
}

static uint32_t USART6_NonBlockingGetRxCount(void)
{
    return USART_NonBlockingGetRxCount(&usart6_NonBlockingDriverState);
}

static int32_t USART6_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = USART_NonBlockingControl(control, arg, &usart6_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }
#if defined(USART6_RX_BUFFER_ENABLE) && (USART6_RX_BUFFER_ENABLE == 1)
    /* Start receiving interrupts */
    usart6_NonBlockingDriverState.resource->base->FIFOINTENSET |=
        USART_FIFOINTENSET_RXLVL_MASK | USART_FIFOINTENSET_RXERR_MASK;
#endif
    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS USART6_NonBlockingGetStatus(void)
{
    return USART_NonBlockingGetStatus(&usart6_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART6 = {
    USARTx_GetVersion,      USARTx_GetCapabilities,
#if RTE_USART6_DMA_EN
    USART6_DmaInitialize,   USART6_DmaUninitialize, USART6_DmaPowerControl, USART6_DmaSend,    USART6_DmaReceive,
    USART6_DmaTransfer,     USART6_DmaGetTxCount,   USART6_DmaGetRxCount,   USART6_DmaControl, USART6_DmaGetStatus,
#else
    USART6_NonBlockingInitialize,
    USART6_NonBlockingUninitialize,
    USART6_NonBlockingPowerControl,
    USART6_NonBlockingSend,
    USART6_NonBlockingReceive,
    USART6_NonBlockingTransfer,
    USART6_NonBlockingGetTxCount,
    USART6_NonBlockingGetRxCount,
    USART6_NonBlockingControl,
    USART6_NonBlockingGetStatus,
#endif
    USARTx_SetModemControl, USARTx_GetModemStatus};

#endif /* usart6 */

#if defined(USART7) && defined(RTE_USART7) && RTE_USART7

/* User needs to provide the implementation for USART7_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t USART7_GetFreq(void);

static cmsis_usart_resource_t usart7_Resource = {USART7, USART7_GetFreq};

#if defined(RTE_USART7_DMA_EN) && RTE_USART7_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

cmsis_usart_dma_resource_t usart7_DmaResource = {
    RTE_USART7_DMA_TX_DMA_BASE,
    RTE_USART7_DMA_TX_CH,
    RTE_USART7_DMA_RX_DMA_BASE,
    RTE_USART7_DMA_RX_CH,
};

static usart_dma_handle_t USART7_DmaHandle;
static dma_handle_t USART7_DmaRxHandle;
static dma_handle_t USART7_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart7_dma_driver_state")
static cmsis_usart_dma_driver_state_t usart7_DmaDriverState = {
#else
static cmsis_usart_dma_driver_state_t usart7_DmaDriverState  = {
#endif
    &usart7_Resource, &usart7_DmaResource, &USART7_DmaHandle, &USART7_DmaRxHandle, &USART7_DmaTxHandle,
};

static int32_t USART7_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART7_PIN_INIT
    RTE_USART7_PIN_INIT();
#endif
    return USART_DmaInitialize(cb_event, &usart7_DmaDriverState);
}

static int32_t USART7_DmaUninitialize(void)
{
#ifdef RTE_USART7_PIN_DEINIT
    RTE_USART7_PIN_DEINIT();
#endif
    return USART_DmaUninitialize(&usart7_DmaDriverState);
}

static int32_t USART7_DmaPowerControl(ARM_POWER_STATE state)
{
    return USART_DmaPowerControl(state, &usart7_DmaDriverState);
}

static int32_t USART7_DmaSend(const void *data, uint32_t num)
{
    return USART_DmaSend(data, num, &usart7_DmaDriverState);
}

static int32_t USART7_DmaReceive(void *data, uint32_t num)
{
    return USART_DmaReceive(data, num, &usart7_DmaDriverState);
}

static int32_t USART7_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_DmaTransfer(data_out, data_in, num, &usart7_DmaDriverState);
}

static uint32_t USART7_DmaGetTxCount(void)
{
    return USART_DmaGetTxCount(&usart7_DmaDriverState);
}

static uint32_t USART7_DmaGetRxCount(void)
{
    return USART_DmaGetRxCount(&usart7_DmaDriverState);
}

static int32_t USART7_DmaControl(uint32_t control, uint32_t arg)
{
    return USART_DmaControl(control, arg, &usart7_DmaDriverState);
}

static ARM_USART_STATUS USART7_DmaGetStatus(void)
{
    return USART_DmaGetStatus(&usart7_DmaDriverState);
}

#endif

#else

static usart_handle_t USART7_Handle;
#if defined(USART7_RX_BUFFER_ENABLE) && (USART7_RX_BUFFER_ENABLE == 1)
static uint8_t usart7_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart7_non_blocking_driver_state")
static cmsis_usart_non_blocking_driver_state_t usart7_NonBlockingDriverState = {
#else
static cmsis_usart_non_blocking_driver_state_t usart7_NonBlockingDriverState  = {
#endif
    &usart7_Resource,
    &USART7_Handle,
};

static int32_t USART7_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART7_PIN_INIT
    RTE_USART7_PIN_INIT();
#endif
    return USART_NonBlockingInitialize(cb_event, &usart7_NonBlockingDriverState);
}

static int32_t USART7_NonBlockingUninitialize(void)
{
#ifdef RTE_USART7_PIN_DEINIT
    RTE_USART7_PIN_DEINIT();
#endif
    return USART_NonBlockingUninitialize(&usart7_NonBlockingDriverState);
}

static int32_t USART7_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    uint32_t result;

    result = USART_NonBlockingPowerControl(state, &usart7_NonBlockingDriverState);
#if defined(USART7_RX_BUFFER_ENABLE) && (USART7_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (usart7_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        USART_TransferStartRingBuffer(usart7_NonBlockingDriverState.resource->base,
                                      usart7_NonBlockingDriverState.handle, usart7_rxRingBuffer, USART_RX_BUFFER_LEN);
    }
#endif
    return result;
}

static int32_t USART7_NonBlockingSend(const void *data, uint32_t num)
{
    return USART_NonBlockingSend(data, num, &usart7_NonBlockingDriverState);
}

static int32_t USART7_NonBlockingReceive(void *data, uint32_t num)
{
    return USART_NonBlockingReceive(data, num, &usart7_NonBlockingDriverState);
}

static int32_t USART7_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_NonBlockingTransfer(data_out, data_in, num, &usart7_NonBlockingDriverState);
}

static uint32_t USART7_NonBlockingGetTxCount(void)
{
    return USART_NonBlockingGetTxCount(&usart7_NonBlockingDriverState);
}

static uint32_t USART7_NonBlockingGetRxCount(void)
{
    return USART_NonBlockingGetRxCount(&usart7_NonBlockingDriverState);
}

static int32_t USART7_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = USART_NonBlockingControl(control, arg, &usart7_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }
#if defined(USART7_RX_BUFFER_ENABLE) && (USART7_RX_BUFFER_ENABLE == 1)
    /* Start receiving interrupts */
    usart7_NonBlockingDriverState.resource->base->FIFOINTENSET |=
        USART_FIFOINTENSET_RXLVL_MASK | USART_FIFOINTENSET_RXERR_MASK;
#endif
    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS USART7_NonBlockingGetStatus(void)
{
    return USART_NonBlockingGetStatus(&usart7_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART7 = {
    USARTx_GetVersion,      USARTx_GetCapabilities,
#if RTE_USART7_DMA_EN
    USART7_DmaInitialize,   USART7_DmaUninitialize, USART7_DmaPowerControl, USART7_DmaSend,    USART7_DmaReceive,
    USART7_DmaTransfer,     USART7_DmaGetTxCount,   USART7_DmaGetRxCount,   USART7_DmaControl, USART7_DmaGetStatus,
#else
    USART7_NonBlockingInitialize,
    USART7_NonBlockingUninitialize,
    USART7_NonBlockingPowerControl,
    USART7_NonBlockingSend,
    USART7_NonBlockingReceive,
    USART7_NonBlockingTransfer,
    USART7_NonBlockingGetTxCount,
    USART7_NonBlockingGetRxCount,
    USART7_NonBlockingControl,
    USART7_NonBlockingGetStatus,
#endif
    USARTx_SetModemControl, USARTx_GetModemStatus};

#endif /* usart7 */

#if defined(USART8) && defined(RTE_USART8) && RTE_USART8

/* User needs to provide the implementation for USART8_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t USART8_GetFreq(void);

static cmsis_usart_resource_t usart8_Resource = {USART8, USART8_GetFreq};

#if defined(RTE_USART8_DMA_EN) RTE_USART8_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

cmsis_usart_dma_resource_t usart8_DmaResource = {
    RTE_USART8_DMA_TX_DMA_BASE,
    RTE_USART8_DMA_TX_CH,
    RTE_USART8_DMA_RX_DMA_BASE,
    RTE_USART8_DMA_RX_CH,
};

static usart_dma_handle_t USART8_DmaHandle;
static dma_handle_t USART8_DmaRxHandle;
static dma_handle_t USART8_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart8_dma_driver_state")
static cmsis_usart_dma_driver_state_t usart8_DmaDriverState = {
#else
static cmsis_usart_dma_driver_state_t usart8_DmaDriverState  = {
#endif
    &usart8_Resource, &usart8_DmaResource, &USART8_DmaHandle, &USART8_DmaRxHandle, &USART8_DmaTxHandle,
};

static int32_t USART8_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART8_PIN_INIT
    RTE_USART8_PIN_INIT();
#endif
    return USART_DmaInitialize(cb_event, &usart8_DmaDriverState);
}

static int32_t USART8_DmaUninitialize(void)
{
#ifdef RTE_USART8_PIN_DEINIT
    RTE_USART8_PIN_DEINIT();
#endif
    return USART_DmaUninitialize(&usart8_DmaDriverState);
}

static int32_t USART8_DmaPowerControl(ARM_POWER_STATE state)
{
    return USART_DmaPowerControl(state, &usart8_DmaDriverState);
}

static int32_t USART8_DmaSend(const void *data, uint32_t num)
{
    return USART_DmaSend(data, num, &usart8_DmaDriverState);
}

static int32_t USART8_DmaReceive(void *data, uint32_t num)
{
    return USART_DmaReceive(data, num, &usart8_DmaDriverState);
}

static int32_t USART8_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_DmaTransfer(data_out, data_in, num, &usart8_DmaDriverState);
}

static uint32_t USART8_DmaGetTxCount(void)
{
    return USART_DmaGetTxCount(&usart8_DmaDriverState);
}

static uint32_t USART8_DmaGetRxCount(void)
{
    return USART_DmaGetRxCount(&usart8_DmaDriverState);
}

static int32_t USART8_DmaControl(uint32_t control, uint32_t arg)
{
    return USART_DmaControl(control, arg, &usart8_DmaDriverState);
}

static ARM_USART_STATUS USART8_DmaGetStatus(void)
{
    return USART_DmaGetStatus(&usart8_DmaDriverState);
}

#endif

#else

static usart_handle_t USART8_Handle;
#if defined(USART8_RX_BUFFER_ENABLE) && (USART8_RX_BUFFER_ENABLE == 1)
static uint8_t usart8_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart8_non_blocking_driver_state")
static cmsis_usart_non_blocking_driver_state_t usart8_NonBlockingDriverState = {
#else
static cmsis_usart_non_blocking_driver_state_t usart8_NonBlockingDriverState  = {
#endif
    &usart8_Resource,
    &USART8_Handle,
};

static int32_t USART8_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART8_PIN_INIT
    RTE_USART8_PIN_INIT();
#endif
    return USART_NonBlockingInitialize(cb_event, &usart8_NonBlockingDriverState);
}

static int32_t USART8_NonBlockingUninitialize(void)
{
#ifdef RTE_USART8_PIN_DEINIT
    RTE_USART8_PIN_DEINIT();
#endif
    return USART_NonBlockingUninitialize(&usart8_NonBlockingDriverState);
}

static int32_t USART8_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    uint32_t result;

    result = USART_NonBlockingPowerControl(state, &usart8_NonBlockingDriverState);
#if defined(USART8_RX_BUFFER_ENABLE) && (USART8_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (usart8_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        USART_TransferStartRingBuffer(usart8_NonBlockingDriverState.resource->base,
                                      usart8_NonBlockingDriverState.handle, usart8_rxRingBuffer, USART_RX_BUFFER_LEN);
    }
#endif

    return result;
}

static int32_t USART8_NonBlockingSend(const void *data, uint32_t num)
{
    return USART_NonBlockingSend(data, num, &usart8_NonBlockingDriverState);
}

static int32_t USART8_NonBlockingReceive(void *data, uint32_t num)
{
    return USART_NonBlockingReceive(data, num, &usart8_NonBlockingDriverState);
}

static int32_t USART8_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_NonBlockingTransfer(data_out, data_in, num, &usart8_NonBlockingDriverState);
}

static uint32_t USART8_NonBlockingGetTxCount(void)
{
    return USART_NonBlockingGetTxCount(&usart8_NonBlockingDriverState);
}

static uint32_t USART8_NonBlockingGetRxCount(void)
{
    return USART_NonBlockingGetRxCount(&usart8_NonBlockingDriverState);
}

static int32_t USART8_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = USART_NonBlockingControl(control, arg, &usart8_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }
#if defined(USART8_RX_BUFFER_ENABLE) && (USART8_RX_BUFFER_ENABLE == 1)
    /* Start receiving interrupts */
    usart8_NonBlockingDriverState.resource->base->FIFOINTENSET |=
        USART_FIFOINTENSET_RXLVL_MASK | USART_FIFOINTENSET_RXERR_MASK;
#endif
    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS USART8_NonBlockingGetStatus(void)
{
    return USART_NonBlockingGetStatus(&usart8_NonBlockingDriverState);
}

#endif

/* usart8 Driver Control Block */
ARM_DRIVER_USART Driver_USART8 = {
    USARTx_GetVersion,      USARTx_GetCapabilities,
#if RTE_USART8_DMA_EN
    USART8_DmaInitialize,   USART8_DmaUninitialize, USART8_DmaPowerControl, USART8_DmaSend,    USART8_DmaReceive,
    USART8_DmaTransfer,     USART8_DmaGetTxCount,   USART8_DmaGetRxCount,   USART8_DmaControl, USART8_DmaGetStatus,
#else
    USART8_NonBlockingInitialize,
    USART8_NonBlockingUninitialize,
    USART8_NonBlockingPowerControl,
    USART8_NonBlockingSend,
    USART8_NonBlockingReceive,
    USART8_NonBlockingTransfer,
    USART8_NonBlockingGetTxCount,
    USART8_NonBlockingGetRxCount,
    USART8_NonBlockingControl,
    USART8_NonBlockingGetStatus,
#endif
    USARTx_SetModemControl, USARTx_GetModemStatus};

#endif /* usart8 */

#if defined(USART9) && defined(RTE_USART9) && RTE_USART9

/* User needs to provide the implementation for USART9_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t USART9_GetFreq(void);

static cmsis_usart_resource_t usart9_Resource = {USART9, USART9_GetFreq};

#if defined(RTE_USART9_DMA_EN) && RTE_USART9_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

cmsis_usart_dma_resource_t usart9_DmaResource = {
    RTE_USART9_DMA_TX_DMA_BASE,
    RTE_USART9_DMA_TX_CH,
    RTE_USART9_DMA_RX_DMA_BASE,
    RTE_USART9_DMA_RX_CH,
};

static usart_dma_handle_t USART9_DmaHandle;
static dma_handle_t USART9_DmaRxHandle;
static dma_handle_t USART9_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart9_dma_driver_state")
static cmsis_usart_dma_driver_state_t usart9_DmaDriverState = {
#else
static cmsis_usart_dma_driver_state_t usart9_DmaDriverState  = {
#endif
    &usart9_Resource, &usart9_DmaResource, &USART9_DmaHandle, &USART9_DmaRxHandle, &USART9_DmaTxHandle,
};

static int32_t USART9_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART9_PIN_INIT
    RTE_USART9_PIN_INIT();
#endif
    return USART_DmaInitialize(cb_event, &usart9_DmaDriverState);
}

static int32_t USART9_DmaUninitialize(void)
{
#ifdef RTE_USART9_PIN_DEINIT
    RTE_USART9_PIN_DEINIT();
#endif
    return USART_DmaUninitialize(&usart9_DmaDriverState);
}

static int32_t USART9_DmaPowerControl(ARM_POWER_STATE state)
{
    return USART_DmaPowerControl(state, &usart9_DmaDriverState);
}

static int32_t USART9_DmaSend(const void *data, uint32_t num)
{
    return USART_DmaSend(data, num, &usart9_DmaDriverState);
}

static int32_t USART9_DmaReceive(void *data, uint32_t num)
{
    return USART_DmaReceive(data, num, &usart9_DmaDriverState);
}

static int32_t USART9_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_DmaTransfer(data_out, data_in, num, &usart9_DmaDriverState);
}

static uint32_t USART9_DmaGetTxCount(void)
{
    return USART_DmaGetTxCount(&usart9_DmaDriverState);
}

static uint32_t USART9_DmaGetRxCount(void)
{
    return USART_DmaGetRxCount(&usart9_DmaDriverState);
}

static int32_t USART9_DmaControl(uint32_t control, uint32_t arg)
{
    return USART_DmaControl(control, arg, &usart9_DmaDriverState);
}

static ARM_USART_STATUS USART9_DmaGetStatus(void)
{
    return USART_DmaGetStatus(&usart9_DmaDriverState);
}

#endif

#else

static usart_handle_t USART9_Handle;
#if defined(USART9_RX_BUFFER_ENABLE) && (USART9_RX_BUFFER_ENABLE == 1)
static uint8_t usart9_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart9_non_blocking_driver_state")
static cmsis_usart_non_blocking_driver_state_t usart9_NonBlockingDriverState = {
#else
static cmsis_usart_non_blocking_driver_state_t usart9_NonBlockingDriverState  = {
#endif
    &usart9_Resource,
    &USART9_Handle,
};

static int32_t USART9_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART9_PIN_INIT
    RTE_USART9_PIN_INIT();
#endif
    return USART_NonBlockingInitialize(cb_event, &usart9_NonBlockingDriverState);
}

static int32_t USART9_NonBlockingUninitialize(void)
{
#ifdef RTE_USART9_PIN_DEINIT
    RTE_USART9_PIN_DEINIT();
#endif
    return USART_NonBlockingUninitialize(&usart9_NonBlockingDriverState);
}

static int32_t USART9_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    uint32_t result;

    result = USART_NonBlockingPowerControl(state, &usart9_NonBlockingDriverState);
#if defined(USART9_RX_BUFFER_ENABLE) && (USART9_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (usart9_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        USART_TransferStartRingBuffer(usart9_NonBlockingDriverState.resource->base,
                                      usart9_NonBlockingDriverState.handle, usart9_rxRingBuffer, USART_RX_BUFFER_LEN);
    }
#endif

    return result;
}

static int32_t USART9_NonBlockingSend(const void *data, uint32_t num)
{
    return USART_NonBlockingSend(data, num, &usart9_NonBlockingDriverState);
}

static int32_t USART9_NonBlockingReceive(void *data, uint32_t num)
{
    return USART_NonBlockingReceive(data, num, &usart9_NonBlockingDriverState);
}

static int32_t USART9_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_NonBlockingTransfer(data_out, data_in, num, &usart9_NonBlockingDriverState);
}

static uint32_t USART9_NonBlockingGetTxCount(void)
{
    return USART_NonBlockingGetTxCount(&usart9_NonBlockingDriverState);
}

static uint32_t USART9_NonBlockingGetRxCount(void)
{
    return USART_NonBlockingGetRxCount(&usart9_NonBlockingDriverState);
}

static int32_t USART9_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = USART_NonBlockingControl(control, arg, &usart9_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }
#if defined(USART9_RX_BUFFER_ENABLE) && (USART9_RX_BUFFER_ENABLE == 1)
    /* Start receiving interrupts */
    usart9_NonBlockingDriverState.resource->base->FIFOINTENSET |=
        USART_FIFOINTENSET_RXLVL_MASK | USART_FIFOINTENSET_RXERR_MASK;
#endif
    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS USART9_NonBlockingGetStatus(void)
{
    return USART_NonBlockingGetStatus(&usart9_NonBlockingDriverState);
}

#endif

/* usart9 Driver Control Block */
ARM_DRIVER_USART Driver_USART9 = {
    USARTx_GetVersion,      USARTx_GetCapabilities,
#if RTE_USART9_DMA_EN
    USART9_DmaInitialize,   USART9_DmaUninitialize, USART9_DmaPowerControl, USART9_DmaSend,    USART9_DmaReceive,
    USART9_DmaTransfer,     USART9_DmaGetTxCount,   USART9_DmaGetRxCount,   USART9_DmaControl, USART9_DmaGetStatus,
#else
    USART9_NonBlockingInitialize,
    USART9_NonBlockingUninitialize,
    USART9_NonBlockingPowerControl,
    USART9_NonBlockingSend,
    USART9_NonBlockingReceive,
    USART9_NonBlockingTransfer,
    USART9_NonBlockingGetTxCount,
    USART9_NonBlockingGetRxCount,
    USART9_NonBlockingControl,
    USART9_NonBlockingGetStatus,
#endif
    USARTx_SetModemControl, USARTx_GetModemStatus};

#endif /* usart9 */

#if defined(USART10) && defined(RTE_USART10) && RTE_USART10

/* User needs to provide the implementation for USART10_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t USART10_GetFreq(void);

static cmsis_usart_resource_t usart10_Resource = {USART10, USART10_GetFreq};

#if defined(RTE_USART10_DMA_EN) && RTE_USART10_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

cmsis_usart_dma_resource_t usart10_DmaResource = {
    RTE_USART10_DMA_TX_DMA_BASE,
    RTE_USART10_DMA_TX_CH,
    RTE_USART10_DMA_RX_DMA_BASE,
    RTE_USART10_DMA_RX_CH,
};

static usart_dma_handle_t USART10_DmaHandle;
static dma_handle_t USART10_DmaRxHandle;
static dma_handle_t USART10_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart10_dma_driver_state")
static cmsis_usart_dma_driver_state_t usart10_DmaDriverState = {
#else
static cmsis_usart_dma_driver_state_t usart10_DmaDriverState = {
#endif
    &usart10_Resource, &usart10_DmaResource, &USART10_DmaHandle, &USART10_DmaRxHandle, &USART10_DmaTxHandle,
};

static int32_t USART10_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART10_PIN_INIT
    RTE_USART10_PIN_INIT();
#endif
    return USART_DmaInitialize(cb_event, &usart10_DmaDriverState);
}

static int32_t USART10_DmaUninitialize(void)
{
#ifdef RTE_USART10_PIN_DEINIT
    RTE_USART10_PIN_DEINIT();
#endif
    return USART_DmaUninitialize(&usart10_DmaDriverState);
}

static int32_t USART10_DmaPowerControl(ARM_POWER_STATE state)
{
    return USART_DmaPowerControl(state, &usart10_DmaDriverState);
}

static int32_t USART10_DmaSend(const void *data, uint32_t num)
{
    return USART_DmaSend(data, num, &usart10_DmaDriverState);
}

static int32_t USART10_DmaReceive(void *data, uint32_t num)
{
    return USART_DmaReceive(data, num, &usart10_DmaDriverState);
}

static int32_t USART10_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_DmaTransfer(data_out, data_in, num, &usart10_DmaDriverState);
}

static uint32_t USART10_DmaGetTxCount(void)
{
    return USART_DmaGetTxCount(&usart10_DmaDriverState);
}

static uint32_t USART10_DmaGetRxCount(void)
{
    return USART_DmaGetRxCount(&usart10_DmaDriverState);
}

static int32_t USART10_DmaControl(uint32_t control, uint32_t arg)
{
    return USART_DmaControl(control, arg, &usart10_DmaDriverState);
}

static ARM_USART_STATUS USART10_DmaGetStatus(void)
{
    return USART_DmaGetStatus(&usart10_DmaDriverState);
}

#endif

#else

static usart_handle_t USART10_Handle;
#if defined(USART10_RX_BUFFER_ENABLE) && (USART10_RX_BUFFER_ENABLE == 1)
static uint8_t usart10_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart10_non_blocking_driver_state")
static cmsis_usart_non_blocking_driver_state_t usart10_NonBlockingDriverState = {
#else
static cmsis_usart_non_blocking_driver_state_t usart10_NonBlockingDriverState = {
#endif
    &usart10_Resource,
    &USART10_Handle,
};

static int32_t USART10_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART10_PIN_INIT
    RTE_USART10_PIN_INIT();
#endif
    return USART_NonBlockingInitialize(cb_event, &usart10_NonBlockingDriverState);
}

static int32_t USART10_NonBlockingUninitialize(void)
{
#ifdef RTE_USART10_PIN_DEINIT
    RTE_USART10_PIN_DEINIT();
#endif
    return USART_NonBlockingUninitialize(&usart10_NonBlockingDriverState);
}

static int32_t USART10_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    uint32_t result;

    result = USART_NonBlockingPowerControl(state, &usart10_NonBlockingDriverState);
#if defined(USART10_RX_BUFFER_ENABLE) && (USART10_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (usart10_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        USART_TransferStartRingBuffer(usart10_NonBlockingDriverState.resource->base,
                                      usart10_NonBlockingDriverState.handle, usart10_rxRingBuffer, USART_RX_BUFFER_LEN);
    }
#endif
    return result;
}

static int32_t USART10_NonBlockingSend(const void *data, uint32_t num)
{
    return USART_NonBlockingSend(data, num, &usart10_NonBlockingDriverState);
}

static int32_t USART10_NonBlockingReceive(void *data, uint32_t num)
{
    return USART_NonBlockingReceive(data, num, &usart10_NonBlockingDriverState);
}

static int32_t USART10_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_NonBlockingTransfer(data_out, data_in, num, &usart10_NonBlockingDriverState);
}

static uint32_t USART10_NonBlockingGetTxCount(void)
{
    return USART_NonBlockingGetTxCount(&usart10_NonBlockingDriverState);
}

static uint32_t USART10_NonBlockingGetRxCount(void)
{
    return USART_NonBlockingGetRxCount(&usart10_NonBlockingDriverState);
}

static int32_t USART10_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = USART_NonBlockingControl(control, arg, &usart10_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }
#if defined(USART10_RX_BUFFER_ENABLE) && (USART10_RX_BUFFER_ENABLE == 1)
    /* Start receiving interrupts */
    usart10_NonBlockingDriverState.resource->base->FIFOINTENSET |=
        USART_FIFOINTENSET_RXLVL_MASK | USART_FIFOINTENSET_RXERR_MASK;
#endif
    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS USART10_NonBlockingGetStatus(void)
{
    return USART_NonBlockingGetStatus(&usart10_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART10 = {
    USARTx_GetVersion,      USARTx_GetCapabilities,
#if RTE_USART10_DMA_EN
    USART10_DmaInitialize,  USART10_DmaUninitialize, USART10_DmaPowerControl, USART10_DmaSend,    USART10_DmaReceive,
    USART10_DmaTransfer,    USART10_DmaGetTxCount,   USART10_DmaGetRxCount,   USART10_DmaControl, USART10_DmaGetStatus,
#else
    USART10_NonBlockingInitialize,
    USART10_NonBlockingUninitialize,
    USART10_NonBlockingPowerControl,
    USART10_NonBlockingSend,
    USART10_NonBlockingReceive,
    USART10_NonBlockingTransfer,
    USART10_NonBlockingGetTxCount,
    USART10_NonBlockingGetRxCount,
    USART10_NonBlockingControl,
    USART10_NonBlockingGetStatus,
#endif
    USARTx_SetModemControl, USARTx_GetModemStatus};

#endif /* usart10 */

#if defined(USART11) && defined(RTE_USART11) && RTE_USART11

/* User needs to provide the implementation for USART11_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t USART11_GetFreq(void);

static cmsis_usart_resource_t usart11_Resource = {USART11, USART11_GetFreq};

#if defined(RTE_USART11_DMA_EN) && RTE_USART11_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

cmsis_usart_dma_resource_t usart11_DmaResource = {
    RTE_USART11_DMA_TX_DMA_BASE,
    RTE_USART11_DMA_TX_CH,
    RTE_USART11_DMA_RX_DMA_BASE,
    RTE_USART11_DMA_RX_CH,
};

static usart_dma_handle_t USART11_DmaHandle;
static dma_handle_t USART11_DmaRxHandle;
static dma_handle_t USART11_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart11_dma_driver_state")
static cmsis_usart_dma_driver_state_t usart11_DmaDriverState = {
#else
static cmsis_usart_dma_driver_state_t usart11_DmaDriverState = {
#endif
    &usart11_Resource, &usart11_DmaResource, &USART11_DmaHandle, &USART11_DmaRxHandle, &USART11_DmaTxHandle,
};

static int32_t USART11_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART11_PIN_INIT
    RTE_USART11_PIN_INIT();
#endif
    return USART_DmaInitialize(cb_event, &usart11_DmaDriverState);
}

static int32_t USART11_DmaUninitialize(void)
{
#ifdef RTE_USART11_PIN_DEINIT
    RTE_USART11_PIN_DEINIT();
#endif
    return USART_DmaUninitialize(&usart11_DmaDriverState);
}

static int32_t USART11_DmaPowerControl(ARM_POWER_STATE state)
{
    return USART_DmaPowerControl(state, &usart11_DmaDriverState);
}

static int32_t USART11_DmaSend(const void *data, uint32_t num)
{
    return USART_DmaSend(data, num, &usart11_DmaDriverState);
}

static int32_t USART11_DmaReceive(void *data, uint32_t num)
{
    return USART_DmaReceive(data, num, &usart11_DmaDriverState);
}

static int32_t USART11_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_DmaTransfer(data_out, data_in, num, &usart11_DmaDriverState);
}

static uint32_t USART11_DmaGetTxCount(void)
{
    return USART_DmaGetTxCount(&usart11_DmaDriverState);
}

static uint32_t USART11_DmaGetRxCount(void)
{
    return USART_DmaGetRxCount(&usart11_DmaDriverState);
}

static int32_t USART11_DmaControl(uint32_t control, uint32_t arg)
{
    return USART_DmaControl(control, arg, &usart11_DmaDriverState);
}

static ARM_USART_STATUS USART11_DmaGetStatus(void)
{
    return USART_DmaGetStatus(&usart11_DmaDriverState);
}

#endif

#else

static usart_handle_t USART11_Handle;
#if defined(USART11_RX_BUFFER_ENABLE) && (USART11_RX_BUFFER_ENABLE == 1)
static uint8_t usart11_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart11_non_blocking_driver_state")
static cmsis_usart_non_blocking_driver_state_t usart11_NonBlockingDriverState = {
#else
static cmsis_usart_non_blocking_driver_state_t usart11_NonBlockingDriverState = {
#endif
    &usart11_Resource,
    &USART11_Handle,
};

static int32_t USART11_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART11_PIN_INIT
    RTE_USART11_PIN_INIT();
#endif
    return USART_NonBlockingInitialize(cb_event, &usart11_NonBlockingDriverState);
}

static int32_t USART11_NonBlockingUninitialize(void)
{
#ifdef RTE_USART11_PIN_DEINIT
    RTE_USART11_PIN_DEINIT();
#endif
    return USART_NonBlockingUninitialize(&usart11_NonBlockingDriverState);
}

static int32_t USART11_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    uint32_t result;

    result = USART_NonBlockingPowerControl(state, &usart11_NonBlockingDriverState);
#if defined(USART11_RX_BUFFER_ENABLE) && (USART11_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (usart11_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        USART_TransferStartRingBuffer(usart11_NonBlockingDriverState.resource->base,
                                      usart11_NonBlockingDriverState.handle, usart11_rxRingBuffer, USART_RX_BUFFER_LEN);
    }
#endif
    return result;
}

static int32_t USART11_NonBlockingSend(const void *data, uint32_t num)
{
    return USART_NonBlockingSend(data, num, &usart11_NonBlockingDriverState);
}

static int32_t USART11_NonBlockingReceive(void *data, uint32_t num)
{
    return USART_NonBlockingReceive(data, num, &usart11_NonBlockingDriverState);
}

static int32_t USART11_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_NonBlockingTransfer(data_out, data_in, num, &usart11_NonBlockingDriverState);
}

static uint32_t USART11_NonBlockingGetTxCount(void)
{
    return USART_NonBlockingGetTxCount(&usart11_NonBlockingDriverState);
}

static uint32_t USART11_NonBlockingGetRxCount(void)
{
    return USART_NonBlockingGetRxCount(&usart11_NonBlockingDriverState);
}

static int32_t USART11_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = USART_NonBlockingControl(control, arg, &usart11_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }
#if defined(USART11_RX_BUFFER_ENABLE) && (USART11_RX_BUFFER_ENABLE == 1)
    /* Start receiving interrupts */
    usart11_NonBlockingDriverState.resource->base->FIFOINTENSET |=
        USART_FIFOINTENSET_RXLVL_MASK | USART_FIFOINTENSET_RXERR_MASK;
#endif
    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS USART11_NonBlockingGetStatus(void)
{
    return USART_NonBlockingGetStatus(&usart11_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART11 = {
    USARTx_GetVersion,      USARTx_GetCapabilities,
#if RTE_USART11_DMA_EN
    USART11_DmaInitialize,  USART11_DmaUninitialize, USART11_DmaPowerControl, USART11_DmaSend,    USART11_DmaReceive,
    USART11_DmaTransfer,    USART11_DmaGetTxCount,   USART11_DmaGetRxCount,   USART11_DmaControl, USART11_DmaGetStatus,
#else
    USART11_NonBlockingInitialize,
    USART11_NonBlockingUninitialize,
    USART11_NonBlockingPowerControl,
    USART11_NonBlockingSend,
    USART11_NonBlockingReceive,
    USART11_NonBlockingTransfer,
    USART11_NonBlockingGetTxCount,
    USART11_NonBlockingGetRxCount,
    USART11_NonBlockingControl,
    USART11_NonBlockingGetStatus,
#endif
    USARTx_SetModemControl, USARTx_GetModemStatus};

#endif /* usart11 */

#if defined(USART12) && defined(RTE_USART12) && RTE_USART12

/* User needs to provide the implementation for USART12_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t USART12_GetFreq(void);

static cmsis_usart_resource_t usart12_Resource = {USART12, USART12_GetFreq};

#if defined(RTE_USART12_DMA_EN) && RTE_USART12_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

cmsis_usart_dma_resource_t usart12_DmaResource = {
    RTE_USART12_DMA_TX_DMA_BASE,
    RTE_USART12_DMA_TX_CH,
    RTE_USART12_DMA_RX_DMA_BASE,
    RTE_USART12_DMA_RX_CH,
};

static usart_dma_handle_t USART12_DmaHandle;
static dma_handle_t USART12_DmaRxHandle;
static dma_handle_t USART12_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart12_dma_driver_state")
static cmsis_usart_dma_driver_state_t usart12_DmaDriverState = {
#else
static cmsis_usart_dma_driver_state_t usart12_DmaDriverState = {
#endif
    &usart12_Resource, &usart12_DmaResource, &USART12_DmaHandle, &USART12_DmaRxHandle, &USART12_DmaTxHandle,
};

static int32_t USART12_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART12_PIN_INIT
    RTE_USART12_PIN_INIT();
#endif
    return USART_DmaInitialize(cb_event, &usart12_DmaDriverState);
}

static int32_t USART12_DmaUninitialize(void)
{
#ifdef RTE_USART12_PIN_DEINIT
    RTE_USART12_PIN_DEINIT();
#endif
    return USART_DmaUninitialize(&usart12_DmaDriverState);
}

static int32_t USART12_DmaPowerControl(ARM_POWER_STATE state)
{
    return USART_DmaPowerControl(state, &usart12_DmaDriverState);
}

static int32_t USART12_DmaSend(const void *data, uint32_t num)
{
    return USART_DmaSend(data, num, &usart12_DmaDriverState);
}

static int32_t USART12_DmaReceive(void *data, uint32_t num)
{
    return USART_DmaReceive(data, num, &usart12_DmaDriverState);
}

static int32_t USART12_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_DmaTransfer(data_out, data_in, num, &usart12_DmaDriverState);
}

static uint32_t USART12_DmaGetTxCount(void)
{
    return USART_DmaGetTxCount(&usart12_DmaDriverState);
}

static uint32_t USART12_DmaGetRxCount(void)
{
    return USART_DmaGetRxCount(&usart12_DmaDriverState);
}

static int32_t USART12_DmaControl(uint32_t control, uint32_t arg)
{
    return USART_DmaControl(control, arg, &usart12_DmaDriverState);
}

static ARM_USART_STATUS USART12_DmaGetStatus(void)
{
    return USART_DmaGetStatus(&usart12_DmaDriverState);
}

#endif

#else

static usart_handle_t USART12_Handle;
#if defined(USART12_RX_BUFFER_ENABLE) && (USART12_RX_BUFFER_ENABLE == 1)
static uint8_t usart12_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart12_non_blocking_driver_state")
static cmsis_usart_non_blocking_driver_state_t usart12_NonBlockingDriverState = {
#else
static cmsis_usart_non_blocking_driver_state_t usart12_NonBlockingDriverState = {
#endif
    &usart12_Resource,
    &USART12_Handle,
};

static int32_t USART12_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART12_PIN_INIT
    RTE_USART12_PIN_INIT();
#endif
    return USART_NonBlockingInitialize(cb_event, &usart12_NonBlockingDriverState);
}

static int32_t USART12_NonBlockingUninitialize(void)
{
#ifdef RTE_USART12_PIN_DEINIT
    RTE_USART12_PIN_DEINIT();
#endif
    return USART_NonBlockingUninitialize(&usart12_NonBlockingDriverState);
}

static int32_t USART12_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    uint32_t result;

    result = USART_NonBlockingPowerControl(state, &usart12_NonBlockingDriverState);
#if defined(USART12_RX_BUFFER_ENABLE) && (USART12_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (usart12_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        USART_TransferStartRingBuffer(usart12_NonBlockingDriverState.resource->base,
                                      usart12_NonBlockingDriverState.handle, usart12_rxRingBuffer, USART_RX_BUFFER_LEN);
    }
#endif
    return result;
}

static int32_t USART12_NonBlockingSend(const void *data, uint32_t num)
{
    return USART_NonBlockingSend(data, num, &usart12_NonBlockingDriverState);
}

static int32_t USART12_NonBlockingReceive(void *data, uint32_t num)
{
    return USART_NonBlockingReceive(data, num, &usart12_NonBlockingDriverState);
}

static int32_t USART12_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_NonBlockingTransfer(data_out, data_in, num, &usart12_NonBlockingDriverState);
}

static uint32_t USART12_NonBlockingGetTxCount(void)
{
    return USART_NonBlockingGetTxCount(&usart12_NonBlockingDriverState);
}

static uint32_t USART12_NonBlockingGetRxCount(void)
{
    return USART_NonBlockingGetRxCount(&usart12_NonBlockingDriverState);
}

static int32_t USART12_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = USART_NonBlockingControl(control, arg, &usart12_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }
#if defined(USART12_RX_BUFFER_ENABLE) && (USART12_RX_BUFFER_ENABLE == 1)
    /* Start receiving interrupts */
    usart12_NonBlockingDriverState.resource->base->FIFOINTENSET |=
        USART_FIFOINTENSET_RXLVL_MASK | USART_FIFOINTENSET_RXERR_MASK;
#endif
    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS USART12_NonBlockingGetStatus(void)
{
    return USART_NonBlockingGetStatus(&usart12_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART12 = {
    USARTx_GetVersion,      USARTx_GetCapabilities,
#if RTE_USART12_DMA_EN
    USART12_DmaInitialize,  USART12_DmaUninitialize, USART12_DmaPowerControl, USART12_DmaSend,    USART12_DmaReceive,
    USART12_DmaTransfer,    USART12_DmaGetTxCount,   USART12_DmaGetRxCount,   USART12_DmaControl, USART12_DmaGetStatus,
#else
    USART12_NonBlockingInitialize,
    USART12_NonBlockingUninitialize,
    USART12_NonBlockingPowerControl,
    USART12_NonBlockingSend,
    USART12_NonBlockingReceive,
    USART12_NonBlockingTransfer,
    USART12_NonBlockingGetTxCount,
    USART12_NonBlockingGetRxCount,
    USART12_NonBlockingControl,
    USART12_NonBlockingGetStatus,
#endif
    USARTx_SetModemControl, USARTx_GetModemStatus};

#endif /* usart12 */

#if defined(USART13) && defined(RTE_USART13) && RTE_USART13

/* User needs to provide the implementation for USART13_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t USART13_GetFreq(void);

static cmsis_usart_resource_t usart13_Resource = {USART13, USART13_GetFreq};

#if defined(RTE_USART13_DMA_EN) && RTE_USART13_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

cmsis_usart_dma_resource_t usart13_DmaResource = {
    RTE_USART13_DMA_TX_DMA_BASE,
    RTE_USART13_DMA_TX_CH,
    RTE_USART13_DMA_RX_DMA_BASE,
    RTE_USART13_DMA_RX_CH,
};

static usart_dma_handle_t USART13_DmaHandle;
static dma_handle_t USART13_DmaRxHandle;
static dma_handle_t USART13_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart13_dma_driver_state")
static cmsis_usart_dma_driver_state_t usart13_DmaDriverState = {
#else
static cmsis_usart_dma_driver_state_t usart13_DmaDriverState = {
#endif
    &usart13_Resource, &usart13_DmaResource, &USART13_DmaHandle, &USART13_DmaRxHandle, &USART13_DmaTxHandle,
};

static int32_t USART13_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART13_PIN_INIT
    RTE_USART13_PIN_INIT();
#endif
    return USART_DmaInitialize(cb_event, &usart13_DmaDriverState);
}

static int32_t USART13_DmaUninitialize(void)
{
#ifdef RTE_USART13_PIN_DEINIT
    RTE_USART13_PIN_DEINIT();
#endif
    return USART_DmaUninitialize(&usart13_DmaDriverState);
}

static int32_t USART13_DmaPowerControl(ARM_POWER_STATE state)
{
    return USART_DmaPowerControl(state, &usart13_DmaDriverState);
}

static int32_t USART13_DmaSend(const void *data, uint32_t num)
{
    return USART_DmaSend(data, num, &usart13_DmaDriverState);
}

static int32_t USART13_DmaReceive(void *data, uint32_t num)
{
    return USART_DmaReceive(data, num, &usart13_DmaDriverState);
}

static int32_t USART13_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_DmaTransfer(data_out, data_in, num, &usart13_DmaDriverState);
}

static uint32_t USART13_DmaGetTxCount(void)
{
    return USART_DmaGetTxCount(&usart13_DmaDriverState);
}

static uint32_t USART13_DmaGetRxCount(void)
{
    return USART_DmaGetRxCount(&usart13_DmaDriverState);
}

static int32_t USART13_DmaControl(uint32_t control, uint32_t arg)
{
    return USART_DmaControl(control, arg, &usart13_DmaDriverState);
}

static ARM_USART_STATUS USART13_DmaGetStatus(void)
{
    return USART_DmaGetStatus(&usart13_DmaDriverState);
}

#endif

#else

static usart_handle_t USART13_Handle;
#if defined(USART13_RX_BUFFER_ENABLE) && (USART13_RX_BUFFER_ENABLE == 1)
static uint8_t usart13_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("usart13_non_blocking_driver_state")
static cmsis_usart_non_blocking_driver_state_t usart13_NonBlockingDriverState = {
#else
static cmsis_usart_non_blocking_driver_state_t usart13_NonBlockingDriverState = {
#endif
    &usart13_Resource,
    &USART13_Handle,
};

static int32_t USART13_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART13_PIN_INIT
    RTE_USART13_PIN_INIT();
#endif
    return USART_NonBlockingInitialize(cb_event, &usart13_NonBlockingDriverState);
}

static int32_t USART13_NonBlockingUninitialize(void)
{
#ifdef RTE_USART13_PIN_DEINIT
    RTE_USART13_PIN_DEINIT();
#endif
    return USART_NonBlockingUninitialize(&usart13_NonBlockingDriverState);
}

static int32_t USART13_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    uint32_t result;

    result = USART_NonBlockingPowerControl(state, &usart13_NonBlockingDriverState);
#if defined(USART13_RX_BUFFER_ENABLE) && (USART13_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (usart13_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        USART_TransferStartRingBuffer(usart13_NonBlockingDriverState.resource->base,
                                      usart13_NonBlockingDriverState.handle, usart13_rxRingBuffer, USART_RX_BUFFER_LEN);
    }
#endif
    return result;
}

static int32_t USART13_NonBlockingSend(const void *data, uint32_t num)
{
    return USART_NonBlockingSend(data, num, &usart13_NonBlockingDriverState);
}

static int32_t USART13_NonBlockingReceive(void *data, uint32_t num)
{
    return USART_NonBlockingReceive(data, num, &usart13_NonBlockingDriverState);
}

static int32_t USART13_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return USART_NonBlockingTransfer(data_out, data_in, num, &usart13_NonBlockingDriverState);
}

static uint32_t USART13_NonBlockingGetTxCount(void)
{
    return USART_NonBlockingGetTxCount(&usart13_NonBlockingDriverState);
}

static uint32_t USART13_NonBlockingGetRxCount(void)
{
    return USART_NonBlockingGetRxCount(&usart13_NonBlockingDriverState);
}

static int32_t USART13_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = USART_NonBlockingControl(control, arg, &usart13_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }
#if defined(USART13_RX_BUFFER_ENABLE) && (USART13_RX_BUFFER_ENABLE == 1)
    /* Start receiving interrupts */
    usart13_NonBlockingDriverState.resource->base->FIFOINTENSET |=
        USART_FIFOINTENSET_RXLVL_MASK | USART_FIFOINTENSET_RXERR_MASK;
#endif
    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS USART13_NonBlockingGetStatus(void)
{
    return USART_NonBlockingGetStatus(&usart13_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART13 = {
    USARTx_GetVersion,      USARTx_GetCapabilities,
#if RTE_USART13_DMA_EN
    USART13_DmaInitialize,  USART13_DmaUninitialize, USART13_DmaPowerControl, USART13_DmaSend,    USART13_DmaReceive,
    USART13_DmaTransfer,    USART13_DmaGetTxCount,   USART13_DmaGetRxCount,   USART13_DmaControl, USART13_DmaGetStatus,
#else
    USART13_NonBlockingInitialize,
    USART13_NonBlockingUninitialize,
    USART13_NonBlockingPowerControl,
    USART13_NonBlockingSend,
    USART13_NonBlockingReceive,
    USART13_NonBlockingTransfer,
    USART13_NonBlockingGetTxCount,
    USART13_NonBlockingGetRxCount,
    USART13_NonBlockingControl,
    USART13_NonBlockingGetStatus,
#endif
    USARTx_SetModemControl, USARTx_GetModemStatus};

#endif /* usart13 */
