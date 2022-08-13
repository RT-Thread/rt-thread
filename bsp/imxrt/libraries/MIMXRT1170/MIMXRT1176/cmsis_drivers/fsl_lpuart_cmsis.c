/*
 * Copyright (c) 2013-2016 ARM Limited. All rights reserved.
 * Copyright (c) 2016, Freescale Semiconductor, Inc. Not a Contribution.
 * Copyright 2016-2017,2020,2021 NXP. Not a Contribution.
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

#include "fsl_lpuart_cmsis.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpuart_cmsis"
#endif

/* Re-mapping for LPUART & UART indexing. */
#if (FSL_FEATURE_SOC_LPUART_COUNT == 1) && FSL_FEATURE_SOC_UART_COUNT

#ifdef RTE_USART0
#undef RTE_USART0
#endif
#ifdef RTE_USART0_DMA_EN
#undef RTE_USART0_DMA_EN
#endif
#ifdef RTE_USART0_DMA_TX_CH
#undef RTE_USART0_DMA_TX_CH
#endif
#ifdef RTE_USART0_DMA_TX_PERI_SEL
#undef RTE_USART0_DMA_TX_PERI_SEL
#endif
#ifdef RTE_USART0_DMA_TX_DMAMUX_BASE
#undef RTE_USART0_DMA_TX_DMAMUX_BASE
#endif
#ifdef RTE_USART0_DMA_TX_DMA_BASE
#undef RTE_USART0_DMA_TX_DMA_BASE
#endif
#ifdef RTE_USART0_DMA_RX_CH
#undef RTE_USART0_DMA_RX_CH
#endif
#ifdef RTE_USART0_DMA_RX_PERI_SEL
#undef RTE_USART0_DMA_RX_PERI_SEL
#endif
#ifdef RTE_USART0_DMA_RX_DMAMUX_BASE
#undef RTE_USART0_DMA_RX_DMAMUX_BASE
#endif
#ifdef RTE_USART0_DMA_RX_DMA_BASE
#undef RTE_USART0_DMA_RX_DMA_BASE
#endif
#ifdef USART0_RX_BUFFER_ENABLE
#undef USART0_RX_BUFFER_ENABLE
#endif

#if (FSL_FEATURE_SOC_UART_COUNT == 3)

#ifdef RTE_USART3
#define RTE_USART0 RTE_USART3
#endif
#ifdef RTE_USART3_DMA_EN
#define RTE_USART0_DMA_EN RTE_USART3_DMA_EN
#endif
#ifdef RTE_USART3_DMA_TX_CH
#define RTE_USART0_DMA_TX_CH RTE_USART3_DMA_TX_CH
#endif
#ifdef RTE_USART3_DMA_TX_PERI_SEL
#define RTE_USART0_DMA_TX_PERI_SEL RTE_USART3_DMA_TX_PERI_SEL
#endif
#ifdef RTE_USART3_DMA_TX_DMAMUX_BASE
#define RTE_USART0_DMA_TX_DMAMUX_BASE RTE_USART3_DMA_TX_DMAMUX_BASE
#endif
#ifdef RTE_USART3_DMA_TX_DMA_BASE
#define RTE_USART0_DMA_TX_DMA_BASE RTE_USART3_DMA_TX_DMA_BASE
#endif
#ifdef RTE_USART3_DMA_RX_CH
#define RTE_USART0_DMA_RX_CH RTE_USART3_DMA_RX_CH
#endif
#ifdef RTE_USART3_DMA_RX_PERI_SEL
#define RTE_USART0_DMA_RX_PERI_SEL RTE_USART3_DMA_RX_PERI_SEL
#endif
#ifdef RTE_USART3_DMA_RX_DMAMUX_BASE
#define RTE_USART0_DMA_RX_DMAMUX_BASE RTE_USART3_DMA_RX_DMAMUX_BASE
#endif
#ifdef RTE_USART3_DMA_RX_DMA_BASE
#define RTE_USART0_DMA_RX_DMA_BASE RTE_USART3_DMA_RX_DMA_BASE
#endif
#ifdef USART3_RX_BUFFER_ENABLE
#define USART0_RX_BUFFER_ENABLE USART3_RX_BUFFER_ENABLE
#endif
#ifdef RTE_USART3_PIN_INIT
#define RTE_USART0_PIN_INIT RTE_USART3_PIN_INIT
#endif
#ifdef RTE_USART3_PIN_DEINIT
#define RTE_USART0_PIN_DEINIT RTE_USART3_PIN_DEINIT
#endif

#endif /* FSL_FEATURE_SOC_UART_COUNT == 3 */

#if (FSL_FEATURE_SOC_UART_COUNT == 4)

#ifdef RTE_USART4
#define RTE_USART0 RTE_USART4
#endif
#ifdef RTE_USART4_DMA_EN
#define RTE_USART0_DMA_EN RTE_USART4_DMA_EN
#endif
#ifdef RTE_USART4_DMA_TX_CH
#define RTE_USART0_DMA_TX_CH RTE_USART4_DMA_TX_CH
#endif
#ifdef RTE_USART4_DMA_TX_PERI_SEL
#define RTE_USART0_DMA_TX_PERI_SEL RTE_USART4_DMA_TX_PERI_SEL
#endif
#ifdef RTE_USART4_DMA_TX_DMAMUX_BASE
#define RTE_USART0_DMA_TX_DMAMUX_BASE RTE_USART4_DMA_TX_DMAMUX_BASE
#endif
#ifdef RTE_USART4_DMA_TX_DMA_BASE
#define RTE_USART0_DMA_TX_DMA_BASE RTE_USART4_DMA_TX_DMA_BASE
#endif
#ifdef RTE_USART4_DMA_RX_CH
#define RTE_USART0_DMA_RX_CH RTE_USART4_DMA_RX_CH
#endif
#ifdef RTE_USART4_DMA_RX_PERI_SEL
#define RTE_USART0_DMA_RX_PERI_SEL RTE_USART4_DMA_RX_PERI_SEL
#endif
#ifdef RTE_USART4_DMA_RX_DMAMUX_BASE
#define RTE_USART0_DMA_RX_DMAMUX_BASE RTE_USART4_DMA_RX_DMAMUX_BASE
#endif
#ifdef RTE_USART4_DMA_RX_DMA_BASE
#define RTE_USART0_DMA_RX_DMA_BASE RTE_USART4_DMA_RX_DMA_BASE
#endif
#ifdef USART4_RX_BUFFER_ENABLE
#define USART0_RX_BUFFER_ENABLE USART4_RX_BUFFER_ENABLE
#endif
#ifdef RTE_USART4_PIN_INIT
#define RTE_USART0_PIN_INIT RTE_USART4_PIN_INIT
#endif
#ifdef RTE_USART4_PIN_DEINIT
#define RTE_USART0_PIN_DEINIT RTE_USART4_PIN_DEINIT
#endif

#endif /* FSL_FEATURE_SOC_UART_COUNT == 4 */

#if (FSL_FEATURE_SOC_UART_COUNT == 5)

#ifdef RTE_USART5
#define RTE_USART0 RTE_USART5
#endif
#ifdef RTE_USART5_DMA_EN
#define RTE_USART0_DMA_EN RTE_USART5_DMA_EN
#endif
#ifdef RTE_USART5_DMA_TX_CH
#define RTE_USART0_DMA_TX_CH RTE_USART5_DMA_TX_CH
#endif
#ifdef RTE_USART5_DMA_TX_PERI_SEL
#define RTE_USART0_DMA_TX_PERI_SEL RTE_USART5_DMA_TX_PERI_SEL
#endif
#ifdef RTE_USART5_DMA_TX_DMAMUX_BASE
#define RTE_USART0_DMA_TX_DMAMUX_BASE RTE_USART5_DMA_TX_DMAMUX_BASE
#endif
#ifdef RTE_USART5_DMA_TX_DMA_BASE
#define RTE_USART0_DMA_TX_DMA_BASE RTE_USART5_DMA_TX_DMA_BASE
#endif
#ifdef RTE_USART5_DMA_RX_CH
#define RTE_USART0_DMA_RX_CH RTE_USART5_DMA_RX_CH
#endif
#ifdef RTE_USART5_DMA_RX_PERI_SEL
#define RTE_USART0_DMA_RX_PERI_SEL RTE_USART5_DMA_RX_PERI_SEL
#endif
#ifdef RTE_USART5_DMA_RX_DMAMUX_BASE
#define RTE_USART0_DMA_RX_DMAMUX_BASE RTE_USART5_DMA_RX_DMAMUX_BASE
#endif
#ifdef RTE_USART5_DMA_RX_DMA_BASE
#define RTE_USART0_DMA_RX_DMA_BASE RTE_USART5_DMA_RX_DMA_BASE
#endif
#ifdef USART5_RX_BUFFER_ENABLE
#define USART0_RX_BUFFER_ENABLE USART5_RX_BUFFER_ENABLE
#endif
#ifdef RTE_USART5_PIN_INIT
#define RTE_USART0_PIN_INIT RTE_USART5_PIN_INIT
#endif
#ifdef RTE_USART5_PIN_DEINIT
#define RTE_USART0_PIN_DEINIT RTE_USART5_PIN_DEINIT
#endif

#endif /* FSL_FEATURE_SOC_UART_COUNT == 3 */

#endif /* (FSL_FEATURE_SOC_LPUART_COUNT == 1) && FSL_FEATURE_SOC_UART_COUNT */

#if ((defined(RTE_USART0) && RTE_USART0 && defined(LPUART0)) || \
     (defined(RTE_USART1) && RTE_USART1 && defined(LPUART1)) || \
     (defined(RTE_USART2) && RTE_USART2 && defined(LPUART2)) || \
     (defined(RTE_USART3) && RTE_USART3 && defined(LPUART3)) || \
     (defined(RTE_USART4) && RTE_USART4 && defined(LPUART4)) || \
     (defined(RTE_USART5) && RTE_USART5 && defined(LPUART5)) || \
     (defined(RTE_USART6) && RTE_USART6 && defined(LPUART6)))

#define ARM_LPUART_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR((2), (2))

/*
 * ARMCC does not support split the data section automatically, so the driver
 * needs to split the data to separate sections explicitly, to reduce codesize.
 */
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
#define ARMCC_SECTION(section_name) __attribute__((section(section_name)))
#endif

typedef const struct _cmsis_lpuart_resource
{
    LPUART_Type *base;         /*!< LPUART peripheral base address.      */
    uint32_t (*GetFreq)(void); /*!< Function to get the clock frequency. */
} cmsis_lpuart_resource_t;

typedef struct _cmsis_lpuart_non_blocking_driver_state
{
    cmsis_lpuart_resource_t *resource; /*!< Basic LPUART resource. */
    lpuart_handle_t *handle;           /*!< Interupt transfer handle. */
    ARM_USART_SignalEvent_t cb_event;  /*!< Callback function.     */
    uint8_t flags;                     /*!< Control and state flags. */
} cmsis_lpuart_non_blocking_driver_state_t;

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)
typedef struct _cmsis_lpuart_dma_resource
{
    DMA_Type *txDmaBase;   /*!< DMA peripheral base address for TX.    */
    uint32_t txDmaChannel; /*!< DMA channel for LPUART TX.             */
    uint8_t txDmaRequest;  /*!< TX DMA request source.                 */

    DMA_Type *rxDmaBase;   /*!< DMA peripheral base address for RX.    */
    uint32_t rxDmaChannel; /*!< DMA channel for LPUART RX.             */
    uint8_t rxDmaRequest;  /*!< RX DMA request source.                 */

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    DMAMUX_Type *txDmamuxBase; /*!< DMAMUX peripheral base address for TX. */
    DMAMUX_Type *rxDmamuxBase; /*!< DMAMUX peripheral base address for RX. */
#endif

#if FSL_FEATURE_DMA_MODULE_CHANNEL != FSL_FEATURE_DMAMUX_MODULE_CHANNEL
    uint32_t txDmamuxChannel; /*!< DMAMUX channel for LPUART TX.             */
    uint32_t rxDmamuxChannel; /*!< DMAMUX channel for LPUART TX.             */
#endif
} cmsis_lpuart_dma_resource_t;

typedef struct _cmsis_lpuart_dma_driver_state
{
    cmsis_lpuart_resource_t *resource;        /*!< LPUART basic resource.      */
    cmsis_lpuart_dma_resource_t *dmaResource; /*!< LPUART DMA resource.        */
    lpuart_dma_handle_t *handle;              /*!< LPUART DMA transfer handle. */
    dma_handle_t *rxHandle;                   /*!< DMA RX handle.              */
    dma_handle_t *txHandle;                   /*!< DMA TX handle.              */
    ARM_USART_SignalEvent_t cb_event;         /*!< Callback function.     */
    uint8_t flags;                            /*!< Control and state flags. */
} cmsis_lpuart_dma_driver_state_t;
#endif

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
typedef struct _cmsis_lpuart_edma_resource
{
    DMA_Type *txEdmaBase;   /*!< EDMA peripheral base address for TX.    */
    uint32_t txEdmaChannel; /*!< EDMA channel for LPUART TX.             */
    uint8_t txDmaRequest;   /*!< TX EDMA request source.                 */

    DMA_Type *rxEdmaBase;   /*!< EDMA peripheral base address for RX.    */
    uint32_t rxEdmaChannel; /*!< EDMA channel for LPUART RX.             */
    uint8_t rxDmaRequest;   /*!< RX EDMA request source.                 */

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    DMAMUX_Type *txDmamuxBase; /*!< DMAMUX peripheral base address for TX. */
    DMAMUX_Type *rxDmamuxBase; /*!< DMAMUX peripheral base address for RX. */
#endif
} cmsis_lpuart_edma_resource_t;

typedef struct _cmsis_lpuart_edma_driver_state
{
    cmsis_lpuart_resource_t *resource;         /*!< LPUART basic resource.      */
    cmsis_lpuart_edma_resource_t *dmaResource; /*!< LPUART EDMA resource.        */
    lpuart_edma_handle_t *handle;              /*!< LPUART EDMA transfer handle. */
    edma_handle_t *rxHandle;                   /*!< EDMA RX handle.              */
    edma_handle_t *txHandle;                   /*!< EDMA TX handle.              */
    ARM_USART_SignalEvent_t cb_event;          /*!< Callback function.     */
    uint8_t flags;                             /*!< Control and state flags. */
} cmsis_lpuart_edma_driver_state_t;
#endif

enum _lpuart_transfer_states
{
    kLPUART_TxIdle, /*!< TX idle. */
    kLPUART_TxBusy, /*!< TX busy. */
    kLPUART_RxIdle, /*!< RX idle. */
    kLPUART_RxBusy  /*!< RX busy. */
};

/* Driver Version */
static const ARM_DRIVER_VERSION s_lpuartDriverVersion = {ARM_USART_API_VERSION, ARM_LPUART_DRV_VERSION};

static const ARM_USART_CAPABILITIES s_lpuartDriverCapabilities = {
    1, /* supports LPUART (Asynchronous) mode */
    0, /* supports Synchronous Master mode */
    0, /* supports Synchronous Slave mode */
    0, /* supports LPUART Single-wire mode */
    0, /* supports LPUART IrDA mode */
    0, /* supports LPUART Smart Card mode */
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
 * Common control function used by LPUART_NonBlockingControl/LPUART_DmaControl/LPUART_EdmaControl
 */
static int32_t LPUART_CommonControl(uint32_t control,
                                    uint32_t arg,
                                    cmsis_lpuart_resource_t *resource,
                                    uint8_t *isConfigured)
{
    lpuart_config_t config;
    int32_t result  = ARM_DRIVER_OK;
    bool isContinue = false;

    LPUART_GetDefaultConfig(&config);

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
                LPUART_EnableTx(resource->base, true);
            }
            else
            {
                LPUART_EnableTx(resource->base, false);
            }
            result = ARM_DRIVER_OK;
            break;

        case ARM_USART_CONTROL_RX:
            if (arg != 0U)
            {
                LPUART_EnableRx(resource->base, true);
            }
            else
            {
                LPUART_EnableRx(resource->base, false);
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

    switch (control & ARM_USART_DATA_BITS_Msk)
    {
#if defined(FSL_FEATURE_LPUART_HAS_7BIT_DATA_SUPPORT) && FSL_FEATURE_LPUART_HAS_7BIT_DATA_SUPPORT
        case ARM_USART_DATA_BITS_7:
            config.dataBitsCount = kLPUART_SevenDataBits;
            break;
#endif
        case ARM_USART_DATA_BITS_8:
            config.dataBitsCount = kLPUART_EightDataBits;
            break;

        default:
            result = ARM_USART_ERROR_DATA_BITS;
            break;
    }

    if (result == ARM_USART_ERROR_DATA_BITS)
    {
        return result;
    }

    switch (control & ARM_USART_PARITY_Msk)
    {
        case ARM_USART_PARITY_NONE:
            config.parityMode = kLPUART_ParityDisabled;
            break;
        case ARM_USART_PARITY_EVEN:
            config.parityMode = kLPUART_ParityEven;
            break;
        case ARM_USART_PARITY_ODD:
            config.parityMode = kLPUART_ParityOdd;
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
#if defined(FSL_FEATURE_LPUART_HAS_STOP_BIT_CONFIG_SUPPORT) && FSL_FEATURE_LPUART_HAS_STOP_BIT_CONFIG_SUPPORT
        case ARM_USART_STOP_BITS_2:
            config.stopBitCount = kLPUART_TwoStopBit;
            break;
#endif
        default:
            result = ARM_USART_ERROR_STOP_BITS;
            break;
    }

    if (result == ARM_USART_ERROR_STOP_BITS)
    {
        return result;
    }

    /* If LPUART is already configured, deinit it first. */
    if (((*isConfigured) & (uint8_t)USART_FLAG_CONFIGURED) != 0U)
    {
        LPUART_Deinit(resource->base);
        *isConfigured &= ~(uint8_t)USART_FLAG_CONFIGURED;
    }

    config.enableTx = true;
    config.enableRx = true;

    if (kStatus_LPUART_BaudrateNotSupport == LPUART_Init(resource->base, &config, resource->GetFreq()))
    {
        result = ARM_USART_ERROR_BAUDRATE;
    }
    else
    {
        *isConfigured |= (uint8_t)USART_FLAG_CONFIGURED;
    }

    return result;
}

static ARM_DRIVER_VERSION LPUARTx_GetVersion(void)
{
    return s_lpuartDriverVersion;
}

static ARM_USART_CAPABILITIES LPUARTx_GetCapabilities(void)
{
    return s_lpuartDriverCapabilities;
}

static int32_t LPUARTx_SetModemControl(ARM_USART_MODEM_CONTROL control)
{
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static ARM_USART_MODEM_STATUS LPUARTx_GetModemStatus(void)
{
    ARM_USART_MODEM_STATUS modem_status = {0};

    return modem_status;
}

#endif

#if ((defined(RTE_USART0_DMA_EN) && RTE_USART0_DMA_EN && defined(LPUART0)) || \
     (defined(RTE_USART1_DMA_EN) && RTE_USART1_DMA_EN && defined(LPUART1)) || \
     (defined(RTE_USART2_DMA_EN) && RTE_USART2_DMA_EN && defined(LPUART2)) || \
     (defined(RTE_USART3_DMA_EN) && RTE_USART3_DMA_EN && defined(LPUART3)) || \
     (defined(RTE_USART4_DMA_EN) && RTE_USART4_DMA_EN && defined(LPUART4)) || \
     (defined(RTE_USART5_DMA_EN) && RTE_USART5_DMA_EN && defined(LPUART5)) || \
     (defined(RTE_USART6_DMA_EN) && RTE_USART6_DMA_EN && defined(LPUART6)))

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)
static void KSDK_LPUART_DmaCallback(LPUART_Type *base, lpuart_dma_handle_t *handle, status_t status, void *userData)
{
    uint32_t event = 0U;

    if (kStatus_LPUART_TxIdle == status)
    {
        event = ARM_USART_EVENT_SEND_COMPLETE;
    }
    else if (kStatus_LPUART_RxIdle == status)
    {
        event = ARM_USART_EVENT_RECEIVE_COMPLETE;
    }
    else
    {
        /* Avoid MISRA 2012 15.7 violation */
    }

    /* User data is actually CMSIS driver callback. */
    if ((0U != event) && (userData != NULL))
    {
        ((ARM_USART_SignalEvent_t)userData)(event);
    }
}

static int32_t LPUART_DmaInitialize(ARM_USART_SignalEvent_t cb_event, cmsis_lpuart_dma_driver_state_t *lpuart)
{
    if (0U == (lpuart->flags & (uint8_t)USART_FLAG_INIT))
    {
        lpuart->cb_event = cb_event;
        lpuart->flags    = (uint8_t)USART_FLAG_INIT;
    }

    return ARM_DRIVER_OK;
}

static int32_t LPUART_DmaUninitialize(cmsis_lpuart_dma_driver_state_t *lpuart)
{
    lpuart->flags = (uint8_t)USART_FLAG_UNINIT;
    return ARM_DRIVER_OK;
}

static int32_t LPUART_DmaPowerControl(ARM_POWER_STATE state, cmsis_lpuart_dma_driver_state_t *lpuart)
{
    lpuart_config_t config;
    cmsis_lpuart_dma_resource_t *dmaResource;
    int32_t result = ARM_DRIVER_OK;

    switch (state)
    {
        case ARM_POWER_OFF:
            if ((lpuart->flags & (uint8_t)USART_FLAG_POWER) != 0U)
            {
                LPUART_Deinit(lpuart->resource->base);
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
#if FSL_FEATURE_DMA_MODULE_CHANNEL != FSL_FEATURE_DMAMUX_MODULE_CHANNEL
                DMAMUX_DisableChannel(lpuart->dmaResource->rxDmamuxBase, lpuart->dmaResource->rxDmamuxChannel);
                DMAMUX_DisableChannel(lpuart->dmaResource->txDmamuxBase, lpuart->dmaResource->txDmamuxChannel);
#else
                DMAMUX_DisableChannel(lpuart->dmaResource->rxDmamuxBase, lpuart->dmaResource->rxDmaChannel);
                DMAMUX_DisableChannel(lpuart->dmaResource->txDmamuxBase, lpuart->dmaResource->txDmaChannel);
#endif
#endif
                lpuart->flags = (uint8_t)USART_FLAG_INIT;
            }
            break;
        case ARM_POWER_LOW:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
        case ARM_POWER_FULL:
            /* Must be initialized first. */
            if (lpuart->flags == (uint8_t)USART_FLAG_UNINIT)
            {
                result = ARM_DRIVER_ERROR;
                break;
            }

            if ((lpuart->flags & (uint8_t)USART_FLAG_POWER) != 0U)
            {
                /* Driver already powered */
                break;
            }

            LPUART_GetDefaultConfig(&config);
            config.enableTx = true;
            config.enableRx = true;

            dmaResource = lpuart->dmaResource;

            /* Set up DMA setting. */
            DMA_CreateHandle(lpuart->rxHandle, dmaResource->rxDmaBase, dmaResource->rxDmaChannel);

            DMA_CreateHandle(lpuart->txHandle, dmaResource->txDmaBase, dmaResource->txDmaChannel);
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
#if FSL_FEATURE_DMA_MODULE_CHANNEL != FSL_FEATURE_DMAMUX_MODULE_CHANNEL
            DMAMUX_SetSource(dmaResource->rxDmamuxBase, dmaResource->rxDmamuxChannel, dmaResource->rxDmaRequest);
            DMAMUX_EnableChannel(dmaResource->rxDmamuxBase, dmaResource->rxDmamuxChannel);

            DMAMUX_SetSource(dmaResource->txDmamuxBase, dmaResource->txDmamuxChannel, dmaResource->txDmaRequest);
            DMAMUX_EnableChannel(dmaResource->txDmamuxBase, dmaResource->txDmamuxChannel);
#else
            DMAMUX_SetSource(dmaResource->rxDmamuxBase, dmaResource->rxDmaChannel, dmaResource->rxDmaRequest);
            DMAMUX_EnableChannel(dmaResource->rxDmamuxBase, dmaResource->rxDmaChannel);

            DMAMUX_SetSource(dmaResource->txDmamuxBase, dmaResource->txDmaChannel, dmaResource->txDmaRequest);
            DMAMUX_EnableChannel(dmaResource->txDmamuxBase, dmaResource->txDmaChannel);
#endif
#endif
            /* Setup the LPUART. */
            (void)LPUART_Init(lpuart->resource->base, &config, lpuart->resource->GetFreq());
            LPUART_TransferCreateHandleDMA(lpuart->resource->base, lpuart->handle, KSDK_LPUART_DmaCallback,
                                           (void *)lpuart->cb_event, lpuart->txHandle, lpuart->rxHandle);

            lpuart->flags |= ((uint8_t)USART_FLAG_POWER | (uint8_t)USART_FLAG_CONFIGURED);
            break;
        default:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
    }

    return result;
}

static int32_t LPUART_DmaSend(const void *data, uint32_t num, cmsis_lpuart_dma_driver_state_t *lpuart)
{
    int32_t ret;
    status_t status;
    lpuart_transfer_t xfer;

    xfer.data     = (uint8_t *)data;
    xfer.dataSize = num;

    status = LPUART_TransferSendDMA(lpuart->resource->base, lpuart->handle, &xfer);

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_LPUART_RxBusy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t LPUART_DmaReceive(void *data, uint32_t num, cmsis_lpuart_dma_driver_state_t *lpuart)
{
    int32_t ret;
    status_t status;
    lpuart_transfer_t xfer;

    xfer.data     = (uint8_t *)data;
    xfer.dataSize = num;

    status = LPUART_TransferReceiveDMA(lpuart->resource->base, lpuart->handle, &xfer);

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_LPUART_TxBusy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t LPUART_DmaTransfer(const void *data_out,
                                  void *data_in,
                                  uint32_t num,
                                  cmsis_lpuart_dma_driver_state_t *lpuart)
{
    /* Only in synchronous mode */
    return ARM_DRIVER_ERROR;
}

static uint32_t LPUART_DmaGetTxCount(cmsis_lpuart_dma_driver_state_t *lpuart)
{
    uint32_t cnt;

    /* If TX not in progress, then the TX count is txDataSizeAll saved in handle. */
    if (kStatus_NoTransferInProgress == LPUART_TransferGetSendCountDMA(lpuart->resource->base, lpuart->handle, &cnt))
    {
        cnt = lpuart->handle->txDataSizeAll;
    }

    return cnt;
}

static uint32_t LPUART_DmaGetRxCount(cmsis_lpuart_dma_driver_state_t *lpuart)
{
    uint32_t cnt;

    if (kStatus_NoTransferInProgress == LPUART_TransferGetReceiveCountDMA(lpuart->resource->base, lpuart->handle, &cnt))
    {
        cnt = lpuart->handle->rxDataSizeAll;
    }

    return cnt;
}

static int32_t LPUART_DmaControl(uint32_t control, uint32_t arg, cmsis_lpuart_dma_driver_state_t *lpuart)
{
    int32_t result  = ARM_DRIVER_OK;
    bool isContinue = false;
    /* Must be power on. */
    if (0U == (lpuart->flags & (uint8_t)USART_FLAG_POWER))
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
            LPUART_TransferAbortSendDMA(lpuart->resource->base, lpuart->handle);
            result = ARM_DRIVER_OK;
            break;

        /* Abort receive */
        case ARM_USART_ABORT_RECEIVE:
            LPUART_TransferAbortReceiveDMA(lpuart->resource->base, lpuart->handle);
            result = ARM_DRIVER_OK;
            break;

        default:
            isContinue = true;
            break;
    }

    if (isContinue)
    {
        result = LPUART_CommonControl(control, arg, lpuart->resource, &lpuart->flags);
    }
    return result;
}

static ARM_USART_STATUS LPUART_DmaGetStatus(cmsis_lpuart_dma_driver_state_t *lpuart)
{
    ARM_USART_STATUS stat       = {0};
    uint32_t ksdk_lpuart_status = LPUART_GetStatusFlags(lpuart->resource->base);

    stat.tx_busy = (((uint8_t)kLPUART_TxBusy == lpuart->handle->txState) ? (1U) : (0U));
    stat.rx_busy = (((uint8_t)kLPUART_RxBusy == lpuart->handle->rxState) ? (1U) : (0U));

    stat.tx_underflow = 0U;
    stat.rx_overflow  = (uint32_t)(((ksdk_lpuart_status & (uint32_t)kLPUART_RxOverrunFlag)) != 0U);
#if defined(FSL_FEATURE_LPUART_HAS_LIN_BREAK_DETECT) && FSL_FEATURE_LPUART_HAS_LIN_BREAK_DETECT
    stat.rx_break = (uint32_t)(((ksdk_lpuart_status & (uint32_t)kLPUART_LinBreakFlag)) != 0U);
#else
    stat.rx_break = 0U;
#endif
    stat.rx_framing_error = (uint32_t)(((ksdk_lpuart_status & (uint32_t)kLPUART_FramingErrorFlag)) != 0U);
    stat.rx_parity_error  = (uint32_t)(((ksdk_lpuart_status & (uint32_t)kLPUART_ParityErrorFlag)) != 0U);
    stat.reserved         = 0U;

    return stat;
}
#endif

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
static void KSDK_LPUART_EdmaCallback(LPUART_Type *base, lpuart_edma_handle_t *handle, status_t status, void *userData)
{
    uint32_t event = 0U;

    if (kStatus_LPUART_TxIdle == status)
    {
        event = ARM_USART_EVENT_SEND_COMPLETE;
    }
    if (kStatus_LPUART_RxIdle == status)
    {
        event = ARM_USART_EVENT_RECEIVE_COMPLETE;
    }

    /* User data is actually CMSIS driver callback. */
    if ((0U != event) && (userData != NULL))
    {
        ((ARM_USART_SignalEvent_t)userData)(event);
    }
}

static int32_t LPUART_EdmaInitialize(ARM_USART_SignalEvent_t cb_event, cmsis_lpuart_edma_driver_state_t *lpuart)
{
    if (0U == (lpuart->flags & (uint8_t)USART_FLAG_INIT))
    {
        lpuart->cb_event = cb_event;
        lpuart->flags    = (uint8_t)USART_FLAG_INIT;
    }

    return ARM_DRIVER_OK;
}

static int32_t LPUART_EdmaUninitialize(cmsis_lpuart_edma_driver_state_t *lpuart)
{
    lpuart->flags = (uint8_t)USART_FLAG_UNINIT;
    return ARM_DRIVER_OK;
}

static int32_t LPUART_EdmaPowerControl(ARM_POWER_STATE state, cmsis_lpuart_edma_driver_state_t *lpuart)
{
    lpuart_config_t config;
    cmsis_lpuart_edma_resource_t *dmaResource;
    int32_t result = ARM_DRIVER_OK;
    switch (state)
    {
        case ARM_POWER_OFF:
            if ((lpuart->flags & (uint8_t)USART_FLAG_POWER) != 0U)
            {
                LPUART_Deinit(lpuart->resource->base);

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
                DMAMUX_DisableChannel(lpuart->dmaResource->rxDmamuxBase, lpuart->dmaResource->rxEdmaChannel);
                DMAMUX_DisableChannel(lpuart->dmaResource->txDmamuxBase, lpuart->dmaResource->txEdmaChannel);
#endif
                lpuart->flags = (uint8_t)USART_FLAG_INIT;
            }
            break;
        case ARM_POWER_LOW:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
        case ARM_POWER_FULL:
            /* Must be initialized first. */
            if (lpuart->flags == (uint8_t)USART_FLAG_UNINIT)
            {
                result = ARM_DRIVER_ERROR;
                break;
            }

            if ((lpuart->flags & (uint8_t)USART_FLAG_POWER) != 0U)
            {
                /* Driver already powered */
                break;
            }

            LPUART_GetDefaultConfig(&config);
            config.enableTx = true;
            config.enableRx = true;

            dmaResource = lpuart->dmaResource;

            /* Set up EDMA setting. */
            EDMA_CreateHandle(lpuart->rxHandle, dmaResource->rxEdmaBase, dmaResource->rxEdmaChannel);
            EDMA_CreateHandle(lpuart->txHandle, dmaResource->txEdmaBase, dmaResource->txEdmaChannel);

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
            DMAMUX_SetSource(dmaResource->rxDmamuxBase, dmaResource->rxEdmaChannel, dmaResource->rxDmaRequest);
            DMAMUX_EnableChannel(dmaResource->rxDmamuxBase, dmaResource->rxEdmaChannel);

            DMAMUX_SetSource(dmaResource->txDmamuxBase, dmaResource->txEdmaChannel, dmaResource->txDmaRequest);
            DMAMUX_EnableChannel(dmaResource->txDmamuxBase, dmaResource->txEdmaChannel);
#endif
            /* Setup the LPUART. */
            (void)LPUART_Init(lpuart->resource->base, &config, lpuart->resource->GetFreq());
            LPUART_TransferCreateHandleEDMA(lpuart->resource->base, lpuart->handle, KSDK_LPUART_EdmaCallback,
                                            (void *)lpuart->cb_event, lpuart->txHandle, lpuart->rxHandle);

            lpuart->flags |= ((uint8_t)USART_FLAG_POWER | (uint8_t)USART_FLAG_CONFIGURED);
            break;
        default:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
    }

    return result;
}

static int32_t LPUART_EdmaSend(const void *data, uint32_t num, cmsis_lpuart_edma_driver_state_t *lpuart)
{
    int32_t ret;
    status_t status;
    lpuart_transfer_t xfer;

    xfer.data     = (uint8_t *)data;
    xfer.dataSize = num;

    status = LPUART_SendEDMA(lpuart->resource->base, lpuart->handle, &xfer);

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_LPUART_RxBusy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t LPUART_EdmaReceive(void *data, uint32_t num, cmsis_lpuart_edma_driver_state_t *lpuart)
{
    int32_t ret;
    status_t status;
    lpuart_transfer_t xfer;

    xfer.data     = (uint8_t *)data;
    xfer.dataSize = num;

    status = LPUART_ReceiveEDMA(lpuart->resource->base, lpuart->handle, &xfer);

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_LPUART_TxBusy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t LPUART_EdmaTransfer(const void *data_out,
                                   void *data_in,
                                   uint32_t num,
                                   cmsis_lpuart_edma_driver_state_t *lpuart)
{
    /* Only in synchronous mode */
    return ARM_DRIVER_ERROR;
}

static uint32_t LPUART_EdmaGetTxCount(cmsis_lpuart_edma_driver_state_t *lpuart)
{
    uint32_t cnt;

    if (kStatus_NoTransferInProgress == LPUART_TransferGetSendCountEDMA(lpuart->resource->base, lpuart->handle, &cnt))
    {
        cnt = lpuart->handle->txDataSizeAll;
    }

    return cnt;
}

static uint32_t LPUART_EdmaGetRxCount(cmsis_lpuart_edma_driver_state_t *lpuart)
{
    uint32_t cnt;

    if (kStatus_NoTransferInProgress ==
        LPUART_TransferGetReceiveCountEDMA(lpuart->resource->base, lpuart->handle, &cnt))
    {
        cnt = lpuart->handle->rxDataSizeAll;
    }

    return cnt;
}

static int32_t LPUART_EdmaControl(uint32_t control, uint32_t arg, cmsis_lpuart_edma_driver_state_t *lpuart)
{
    int32_t result  = ARM_DRIVER_OK;
    bool isContinue = false;
    /* Must be power on. */
    if (0U == (lpuart->flags & (uint8_t)USART_FLAG_POWER))
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
            LPUART_TransferAbortSendEDMA(lpuart->resource->base, lpuart->handle);
            result = ARM_DRIVER_OK;
            break;

        /* Abort receive */
        case ARM_USART_ABORT_RECEIVE:
            LPUART_TransferAbortReceiveEDMA(lpuart->resource->base, lpuart->handle);
            result = ARM_DRIVER_OK;
            break;

        default:
            isContinue = true;
            break;
    }
    if (isContinue)
    {
        result = LPUART_CommonControl(control, arg, lpuart->resource, &lpuart->flags);
    }
    return result;
}

static ARM_USART_STATUS LPUART_EdmaGetStatus(cmsis_lpuart_edma_driver_state_t *lpuart)
{
    ARM_USART_STATUS stat       = {0};
    uint32_t ksdk_lpuart_status = LPUART_GetStatusFlags(lpuart->resource->base);

    stat.tx_busy = (((uint8_t)kLPUART_TxBusy == lpuart->handle->txState) ? (1U) : (0U));
    stat.rx_busy = (((uint8_t)kLPUART_RxBusy == lpuart->handle->rxState) ? (1U) : (0U));

    stat.tx_underflow = 0U;
    stat.rx_overflow  = (uint32_t)(((ksdk_lpuart_status & (uint32_t)kLPUART_RxOverrunFlag)) != 0U);
#if defined(FSL_FEATURE_LPUART_HAS_LIN_BREAK_DETECT) && FSL_FEATURE_LPUART_HAS_LIN_BREAK_DETECT
    stat.rx_break = (uint32_t)(((ksdk_lpuart_status & (uint32_t)kLPUART_LinBreakFlag)) != 0U);
#else
    stat.rx_break = 0U;
#endif
    stat.rx_framing_error = (uint32_t)(((ksdk_lpuart_status & (uint32_t)kLPUART_FramingErrorFlag)) != 0U);
    stat.rx_parity_error  = (uint32_t)(((ksdk_lpuart_status & (uint32_t)kLPUART_ParityErrorFlag)) != 0U);
    stat.reserved         = 0U;

    return stat;
}
#endif

#endif

#if (((defined(RTE_USART0) && RTE_USART0 && !(defined(RTE_USART0_DMA_EN) && RTE_USART0_DMA_EN)) && \
      defined(LPUART0)) ||                                                                         \
     ((defined(RTE_USART1) && RTE_USART1 && !(defined(RTE_USART1_DMA_EN) && RTE_USART1_DMA_EN)) && \
      defined(LPUART1)) ||                                                                         \
     ((defined(RTE_USART2) && RTE_USART2 && !(defined(RTE_USART2_DMA_EN) && RTE_USART2_DMA_EN)) && \
      defined(LPUART2)) ||                                                                         \
     ((defined(RTE_USART3) && RTE_USART3 && !(defined(RTE_USART3_DMA_EN) && RTE_USART3_DMA_EN)) && \
      defined(LPUART3)) ||                                                                         \
     ((defined(RTE_USART4) && RTE_USART4 && !(defined(RTE_USART4_DMA_EN) && RTE_USART4_DMA_EN)) && \
      defined(LPUART4)) ||                                                                         \
     ((defined(RTE_USART5) && RTE_USART5 && !(defined(RTE_USART5_DMA_EN) && RTE_USART5_DMA_EN)) && \
      defined(LPUART5)) ||                                                                         \
     ((defined(RTE_USART6) && RTE_USART6 && !(defined(RTE_USART6_DMA_EN) && RTE_USART6_DMA_EN)) && defined(LPUART6)))

static void KSDK_LPUART_NonBlockingCallback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    uint32_t event = 0U;

    if (kStatus_LPUART_TxIdle == status)
    {
        event = ARM_USART_EVENT_SEND_COMPLETE;
    }
    if (kStatus_LPUART_RxIdle == status)
    {
        event = ARM_USART_EVENT_RECEIVE_COMPLETE;
    }
    if (kStatus_LPUART_RxHardwareOverrun == status)
    {
        event = ARM_USART_EVENT_RX_OVERFLOW;
    }

    /* User data is actually CMSIS driver callback. */
    if ((0U != event) && (userData != NULL))
    {
        ((ARM_USART_SignalEvent_t)userData)(event);
    }
}

static int32_t LPUART_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event,
                                            cmsis_lpuart_non_blocking_driver_state_t *lpuart)
{
    if (0U == (lpuart->flags & (uint8_t)USART_FLAG_INIT))
    {
        lpuart->cb_event = cb_event;
        lpuart->flags    = (uint8_t)USART_FLAG_INIT;
    }

    return ARM_DRIVER_OK;
}

static int32_t LPUART_NonBlockingUninitialize(cmsis_lpuart_non_blocking_driver_state_t *lpuart)
{
    lpuart->flags = (uint8_t)USART_FLAG_UNINIT;
    return ARM_DRIVER_OK;
}

static int32_t LPUART_NonBlockingPowerControl(ARM_POWER_STATE state, cmsis_lpuart_non_blocking_driver_state_t *lpuart)
{
    lpuart_config_t config;
    int32_t result = ARM_DRIVER_OK;

    switch (state)
    {
        case ARM_POWER_OFF:
            if ((lpuart->flags & (uint8_t)USART_FLAG_POWER) != 0U)
            {
                LPUART_Deinit(lpuart->resource->base);
                lpuart->flags = (uint8_t)USART_FLAG_INIT;
            }
            break;
        case ARM_POWER_LOW:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
        case ARM_POWER_FULL:
            /* Must be initialized first. */
            if (lpuart->flags == (uint8_t)USART_FLAG_UNINIT)
            {
                result = ARM_DRIVER_ERROR;
                break;
            }

            if ((lpuart->flags & (uint8_t)USART_FLAG_POWER) != 0U)
            {
                /* Driver already powered */
                break;
            }

            LPUART_GetDefaultConfig(&config);
            config.enableTx = true;
            config.enableRx = true;

            (void)LPUART_Init(lpuart->resource->base, &config, lpuart->resource->GetFreq());
            LPUART_TransferCreateHandle(lpuart->resource->base, lpuart->handle, KSDK_LPUART_NonBlockingCallback,
                                        (void *)lpuart->cb_event);
            lpuart->flags |= ((uint8_t)USART_FLAG_POWER | (uint8_t)USART_FLAG_CONFIGURED);

            break;
        default:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
    }

    return result;
}

static int32_t LPUART_NonBlockingSend(const void *data, uint32_t num, cmsis_lpuart_non_blocking_driver_state_t *lpuart)
{
    int32_t ret;
    status_t status;
    lpuart_transfer_t xfer;

    xfer.data     = (uint8_t *)data;
    xfer.dataSize = num;

    status = LPUART_TransferSendNonBlocking(lpuart->resource->base, lpuart->handle, &xfer);

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_LPUART_RxBusy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t LPUART_NonBlockingReceive(void *data, uint32_t num, cmsis_lpuart_non_blocking_driver_state_t *lpuart)
{
    int32_t ret;
    status_t status;
    lpuart_transfer_t xfer;

    xfer.data     = (uint8_t *)data;
    xfer.dataSize = num;

    status = LPUART_TransferReceiveNonBlocking(lpuart->resource->base, lpuart->handle, &xfer, NULL);

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_LPUART_TxBusy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t LPUART_NonBlockingTransfer(const void *data_out,
                                          void *data_in,
                                          uint32_t num,
                                          cmsis_lpuart_non_blocking_driver_state_t *lpuart)
{
    /* Only in synchronous mode */
    return ARM_DRIVER_ERROR;
}

static uint32_t LPUART_NonBlockingGetTxCount(cmsis_lpuart_non_blocking_driver_state_t *lpuart)
{
    uint32_t cnt;

    /* If TX not in progress, then the TX count is txDataSizeAll saved in handle. */
    if (kStatus_NoTransferInProgress == LPUART_TransferGetSendCount(lpuart->resource->base, lpuart->handle, &cnt))
    {
        cnt = lpuart->handle->txDataSizeAll;
    }

    return cnt;
}

static uint32_t LPUART_NonBlockingGetRxCount(cmsis_lpuart_non_blocking_driver_state_t *lpuart)
{
    uint32_t cnt;

    if (kStatus_NoTransferInProgress == LPUART_TransferGetReceiveCount(lpuart->resource->base, lpuart->handle, &cnt))
    {
        cnt = lpuart->handle->rxDataSizeAll;
    }

    return cnt;
}

static int32_t LPUART_NonBlockingControl(uint32_t control,
                                         uint32_t arg,
                                         cmsis_lpuart_non_blocking_driver_state_t *lpuart)
{
    int32_t result  = ARM_DRIVER_OK;
    bool isContinue = false;
    /* Must be power on. */
    if (0U == (lpuart->flags & (uint8_t)USART_FLAG_POWER))
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
            LPUART_TransferAbortSend(lpuart->resource->base, lpuart->handle);
            result = ARM_DRIVER_OK;
            break;

        /* Abort receive */
        case ARM_USART_ABORT_RECEIVE:
            LPUART_TransferAbortReceive(lpuart->resource->base, lpuart->handle);
            result = ARM_DRIVER_OK;
            break;

        default:
            isContinue = true;
            break;
    }
    if (isContinue)
    {
        result = LPUART_CommonControl(control, arg, lpuart->resource, &lpuart->flags);
    }
    return result;
}

static ARM_USART_STATUS LPUART_NonBlockingGetStatus(cmsis_lpuart_non_blocking_driver_state_t *lpuart)
{
    ARM_USART_STATUS stat       = {0};
    uint32_t ksdk_lpuart_status = LPUART_GetStatusFlags(lpuart->resource->base);

    stat.tx_busy = (((uint8_t)kLPUART_TxBusy == lpuart->handle->txState) ? (1U) : (0U));
    stat.rx_busy = (((uint8_t)kLPUART_RxBusy == lpuart->handle->rxState) ? (1U) : (0U));

    stat.tx_underflow = 0U;
    stat.rx_overflow  = (uint32_t)(((ksdk_lpuart_status & (uint32_t)kLPUART_RxOverrunFlag)) != 0U);
#if defined(FSL_FEATURE_LPUART_HAS_LIN_BREAK_DETECT) && FSL_FEATURE_LPUART_HAS_LIN_BREAK_DETECT
    stat.rx_break = (uint32_t)(((ksdk_lpuart_status & (uint32_t)kLPUART_LinBreakFlag)) != 0U);
#else
    stat.rx_break = 0U;
#endif
    stat.rx_framing_error = (uint32_t)(((ksdk_lpuart_status & (uint32_t)kLPUART_FramingErrorFlag)) != 0U);
    stat.rx_parity_error  = (uint32_t)(((ksdk_lpuart_status & (uint32_t)kLPUART_ParityErrorFlag)) != 0U);
    stat.reserved         = 0U;

    return stat;
}

#endif

#if defined(LPUART0) && defined(RTE_USART0) && RTE_USART0

/* User needs to provide the implementation for LPUART0_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPUART0_GetFreq(void);

static cmsis_lpuart_resource_t LPUART0_Resource = {LPUART0, LPUART0_GetFreq};

#if defined(RTE_USART0_DMA_EN) && RTE_USART0_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_lpuart_dma_resource_t LPUART0_DmaResource = {
    RTE_USART0_DMA_TX_DMA_BASE,    RTE_USART0_DMA_TX_CH,          RTE_USART0_DMA_TX_PERI_SEL,
    RTE_USART0_DMA_RX_DMA_BASE,    RTE_USART0_DMA_RX_CH,          RTE_USART0_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART0_DMA_TX_DMAMUX_BASE, RTE_USART0_DMA_RX_DMAMUX_BASE,
#endif
#if FSL_FEATURE_DMA_MODULE_CHANNEL != FSL_FEATURE_DMAMUX_MODULE_CHANNEL
    RTE_USART0_DMAMUX_TX_CH,       RTE_USART0_DMAMUX_RX_CH
#endif
};

static lpuart_dma_handle_t LPUART0_DmaHandle;
static dma_handle_t LPUART0_DmaRxHandle;
static dma_handle_t LPUART0_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart0_dma_driver_state")
static cmsis_lpuart_dma_driver_state_t LPUART0_DmaDriverState = {
#else
static cmsis_lpuart_dma_driver_state_t LPUART0_DmaDriverState = {
#endif
    &LPUART0_Resource, &LPUART0_DmaResource, &LPUART0_DmaHandle, &LPUART0_DmaRxHandle, &LPUART0_DmaTxHandle,
};

static int32_t LPUART0_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART0_PIN_INIT
    RTE_USART0_PIN_INIT();
#endif
    return LPUART_DmaInitialize(cb_event, &LPUART0_DmaDriverState);
}

static int32_t LPUART0_DmaUninitialize(void)
{
#ifdef RTE_USART0_PIN_DEINIT
    RTE_USART0_PIN_DEINIT();
#endif
    return LPUART_DmaUninitialize(&LPUART0_DmaDriverState);
}

static int32_t LPUART0_DmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_DmaPowerControl(state, &LPUART0_DmaDriverState);
}

static int32_t LPUART0_DmaSend(const void *data, uint32_t num)
{
    return LPUART_DmaSend(data, num, &LPUART0_DmaDriverState);
}

static int32_t LPUART0_DmaReceive(void *data, uint32_t num)
{
    return LPUART_DmaReceive(data, num, &LPUART0_DmaDriverState);
}

static int32_t LPUART0_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_DmaTransfer(data_out, data_in, num, &LPUART0_DmaDriverState);
}

static uint32_t LPUART0_DmaGetTxCount(void)
{
    return LPUART_DmaGetTxCount(&LPUART0_DmaDriverState);
}

static uint32_t LPUART0_DmaGetRxCount(void)
{
    return LPUART_DmaGetRxCount(&LPUART0_DmaDriverState);
}

static int32_t LPUART0_DmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_DmaControl(control, arg, &LPUART0_DmaDriverState);
}

static ARM_USART_STATUS LPUART0_DmaGetStatus(void)
{
    return LPUART_DmaGetStatus(&LPUART0_DmaDriverState);
}

#endif

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)

static cmsis_lpuart_edma_resource_t LPUART0_EdmaResource = {
    RTE_USART0_DMA_TX_DMA_BASE,    RTE_USART0_DMA_TX_CH,          RTE_USART0_DMA_TX_PERI_SEL,

    RTE_USART0_DMA_RX_DMA_BASE,    RTE_USART0_DMA_RX_CH,          RTE_USART0_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART0_DMA_TX_DMAMUX_BASE, RTE_USART0_DMA_RX_DMAMUX_BASE,
#endif
};

static lpuart_edma_handle_t LPUART0_EdmaHandle;
static edma_handle_t LPUART0_EdmaRxHandle;
static edma_handle_t LPUART0_EdmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart0_edma_driver_state")
static cmsis_lpuart_edma_driver_state_t LPUART0_EdmaDriverState = {
#else
static cmsis_lpuart_edma_driver_state_t LPUART0_EdmaDriverState = {
#endif
    &LPUART0_Resource, &LPUART0_EdmaResource, &LPUART0_EdmaHandle, &LPUART0_EdmaRxHandle, &LPUART0_EdmaTxHandle,
};

static int32_t LPUART0_EdmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART0_PIN_INIT
    RTE_USART0_PIN_INIT();
#endif
    return LPUART_EdmaInitialize(cb_event, &LPUART0_EdmaDriverState);
}

static int32_t LPUART0_EdmaUninitialize(void)
{
#ifdef RTE_USART0_PIN_DEINIT
    RTE_USART0_PIN_DEINIT();
#endif
    return LPUART_EdmaUninitialize(&LPUART0_EdmaDriverState);
}

static int32_t LPUART0_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_EdmaPowerControl(state, &LPUART0_EdmaDriverState);
}

static int32_t LPUART0_EdmaSend(const void *data, uint32_t num)
{
    return LPUART_EdmaSend(data, num, &LPUART0_EdmaDriverState);
}

static int32_t LPUART0_EdmaReceive(void *data, uint32_t num)
{
    return LPUART_EdmaReceive(data, num, &LPUART0_EdmaDriverState);
}

static int32_t LPUART0_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_EdmaTransfer(data_out, data_in, num, &LPUART0_EdmaDriverState);
}

static uint32_t LPUART0_EdmaGetTxCount(void)
{
    return LPUART_EdmaGetTxCount(&LPUART0_EdmaDriverState);
}

static uint32_t LPUART0_EdmaGetRxCount(void)
{
    return LPUART_EdmaGetRxCount(&LPUART0_EdmaDriverState);
}

static int32_t LPUART0_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_EdmaControl(control, arg, &LPUART0_EdmaDriverState);
}

static ARM_USART_STATUS LPUART0_EdmaGetStatus(void)
{
    return LPUART_EdmaGetStatus(&LPUART0_EdmaDriverState);
}

#endif

#else

static lpuart_handle_t LPUART0_Handle;

#if defined(USART0_RX_BUFFER_ENABLE) && (USART0_RX_BUFFER_ENABLE == 1)
static uint8_t lpuart0_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(USART1_RX_BUFFER_ENABLE) && (USART1_RX_BUFFER_ENABLE == 1)
static uint8_t lpuart1_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart0_non_blocking_driver_state")
static cmsis_lpuart_non_blocking_driver_state_t LPUART0_NonBlockingDriverState = {
#else
static cmsis_lpuart_non_blocking_driver_state_t LPUART0_NonBlockingDriverState  = {
#endif
    &LPUART0_Resource,
    &LPUART0_Handle,
};

static int32_t LPUART0_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART0_PIN_INIT
    RTE_USART0_PIN_INIT();
#endif
    return LPUART_NonBlockingInitialize(cb_event, &LPUART0_NonBlockingDriverState);
}

static int32_t LPUART0_NonBlockingUninitialize(void)
{
#ifdef RTE_USART0_PIN_DEINIT
    RTE_USART0_PIN_DEINIT();
#endif
    return LPUART_NonBlockingUninitialize(&LPUART0_NonBlockingDriverState);
}

static int32_t LPUART0_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    int32_t result;

    result = LPUART_NonBlockingPowerControl(state, &LPUART0_NonBlockingDriverState);

#if defined(USART0_RX_BUFFER_ENABLE) && (USART0_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (LPUART0_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        LPUART_TransferStartRingBuffer(LPUART0_NonBlockingDriverState.resource->base,
                                       LPUART0_NonBlockingDriverState.handle, lpuart0_rxRingBuffer,
                                       USART_RX_BUFFER_LEN);
    }
#endif

    return result;
}

static int32_t LPUART0_NonBlockingSend(const void *data, uint32_t num)
{
    return LPUART_NonBlockingSend(data, num, &LPUART0_NonBlockingDriverState);
}

static int32_t LPUART0_NonBlockingReceive(void *data, uint32_t num)
{
    return LPUART_NonBlockingReceive(data, num, &LPUART0_NonBlockingDriverState);
}

static int32_t LPUART0_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_NonBlockingTransfer(data_out, data_in, num, &LPUART0_NonBlockingDriverState);
}

static uint32_t LPUART0_NonBlockingGetTxCount(void)
{
    return LPUART_NonBlockingGetTxCount(&LPUART0_NonBlockingDriverState);
}

static uint32_t LPUART0_NonBlockingGetRxCount(void)
{
    return LPUART_NonBlockingGetRxCount(&LPUART0_NonBlockingDriverState);
}

static int32_t LPUART0_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = LPUART_NonBlockingControl(control, arg, &LPUART0_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }

    /* Enable the receive interrupts if ring buffer is used */
    if (LPUART0_NonBlockingDriverState.handle->rxRingBuffer != NULL)
    {
        LPUART_EnableInterrupts(
            LPUART0_NonBlockingDriverState.resource->base,
            (uint32_t)kLPUART_RxDataRegFullInterruptEnable | (uint32_t)kLPUART_RxOverrunInterruptEnable);
    }

    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS LPUART0_NonBlockingGetStatus(void)
{
    return LPUART_NonBlockingGetStatus(&LPUART0_NonBlockingDriverState);
}

#endif

#if (FSL_FEATURE_SOC_LPUART_COUNT == 1)
#if (FSL_FEATURE_SOC_UART_COUNT == 3)
ARM_DRIVER_USART Driver_USART3 = {
#elif (FSL_FEATURE_SOC_UART_COUNT == 4)
ARM_DRIVER_USART Driver_USART4 = {
#elif (FSL_FEATURE_SOC_UART_COUNT == 5)
ARM_DRIVER_USART Driver_USART5 = {
#else
ARM_DRIVER_USART Driver_USART0 = {
#endif
#else
ARM_DRIVER_USART Driver_USART0 = {
#endif

    LPUARTx_GetVersion,      LPUARTx_GetCapabilities,
#if defined(RTE_USART0_DMA_EN) && RTE_USART0_DMA_EN
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
    LPUART0_EdmaInitialize,  LPUART0_EdmaUninitialize, LPUART0_EdmaPowerControl, LPUART0_EdmaSend,
    LPUART0_EdmaReceive,     LPUART0_EdmaTransfer,     LPUART0_EdmaGetTxCount,   LPUART0_EdmaGetRxCount,
    LPUART0_EdmaControl,     LPUART0_EdmaGetStatus,
#else
    LPUART0_DmaInitialize,   LPUART0_DmaUninitialize, LPUART0_DmaPowerControl, LPUART0_DmaSend,    LPUART0_DmaReceive,
    LPUART0_DmaTransfer,     LPUART0_DmaGetTxCount,   LPUART0_DmaGetRxCount,   LPUART0_DmaControl, LPUART0_DmaGetStatus,
#endif
#else
    LPUART0_NonBlockingInitialize,
    LPUART0_NonBlockingUninitialize,
    LPUART0_NonBlockingPowerControl,
    LPUART0_NonBlockingSend,
    LPUART0_NonBlockingReceive,
    LPUART0_NonBlockingTransfer,
    LPUART0_NonBlockingGetTxCount,
    LPUART0_NonBlockingGetRxCount,
    LPUART0_NonBlockingControl,
    LPUART0_NonBlockingGetStatus,
#endif
    LPUARTx_SetModemControl, LPUARTx_GetModemStatus};

#endif /* LPUART0 */

#if defined(LPUART1) && defined(RTE_USART1) && RTE_USART1

/* User needs to provide the implementation for LPUART1_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPUART1_GetFreq(void);

static cmsis_lpuart_resource_t LPUART1_Resource = {LPUART1, LPUART1_GetFreq};

#if defined(RTE_USART1_DMA_EN) && RTE_USART1_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_lpuart_dma_resource_t LPUART1_DmaResource = {
    RTE_USART1_DMA_TX_DMA_BASE,    RTE_USART1_DMA_TX_CH,          RTE_USART1_DMA_TX_PERI_SEL,
    RTE_USART1_DMA_RX_DMA_BASE,    RTE_USART1_DMA_RX_CH,          RTE_USART1_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART1_DMA_TX_DMAMUX_BASE, RTE_USART1_DMA_RX_DMAMUX_BASE,
#endif
#if FSL_FEATURE_DMA_MODULE_CHANNEL != FSL_FEATURE_DMAMUX_MODULE_CHANNEL
    RTE_USART1_DMAMUX_TX_CH,       RTE_USART1_DMAMUX_RX_CH
#endif
};

static lpuart_dma_handle_t LPUART1_DmaHandle;
static dma_handle_t LPUART1_DmaRxHandle;
static dma_handle_t LPUART1_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart1_dma_driver_state")
static cmsis_lpuart_dma_driver_state_t LPUART1_DmaDriverState = {
#else
static cmsis_lpuart_dma_driver_state_t LPUART1_DmaDriverState = {
#endif
    &LPUART1_Resource, &LPUART1_DmaResource, &LPUART1_DmaHandle, &LPUART1_DmaRxHandle, &LPUART1_DmaTxHandle,
};

static int32_t LPUART1_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART1_PIN_INIT
    RTE_USART1_PIN_INIT();
#endif
    return LPUART_DmaInitialize(cb_event, &LPUART1_DmaDriverState);
}

static int32_t LPUART1_DmaUninitialize(void)
{
#ifdef RTE_USART1_PIN_DEINIT
    RTE_USART1_PIN_DEINIT();
#endif
    return LPUART_DmaUninitialize(&LPUART1_DmaDriverState);
}

static int32_t LPUART1_DmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_DmaPowerControl(state, &LPUART1_DmaDriverState);
}

static int32_t LPUART1_DmaSend(const void *data, uint32_t num)
{
    return LPUART_DmaSend(data, num, &LPUART1_DmaDriverState);
}

static int32_t LPUART1_DmaReceive(void *data, uint32_t num)
{
    return LPUART_DmaReceive(data, num, &LPUART1_DmaDriverState);
}

static int32_t LPUART1_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_DmaTransfer(data_out, data_in, num, &LPUART1_DmaDriverState);
}

static uint32_t LPUART1_DmaGetTxCount(void)
{
    return LPUART_DmaGetTxCount(&LPUART1_DmaDriverState);
}

static uint32_t LPUART1_DmaGetRxCount(void)
{
    return LPUART_DmaGetRxCount(&LPUART1_DmaDriverState);
}

static int32_t LPUART1_DmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_DmaControl(control, arg, &LPUART1_DmaDriverState);
}

static ARM_USART_STATUS LPUART1_DmaGetStatus(void)
{
    return LPUART_DmaGetStatus(&LPUART1_DmaDriverState);
}

#endif

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)

static cmsis_lpuart_edma_resource_t LPUART1_EdmaResource = {
    RTE_USART1_DMA_TX_DMA_BASE,    RTE_USART1_DMA_TX_CH,          RTE_USART1_DMA_TX_PERI_SEL,
    RTE_USART1_DMA_RX_DMA_BASE,    RTE_USART1_DMA_RX_CH,          RTE_USART1_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART1_DMA_TX_DMAMUX_BASE, RTE_USART1_DMA_RX_DMAMUX_BASE,
#endif
};

static lpuart_edma_handle_t LPUART1_EdmaHandle;
static edma_handle_t LPUART1_EdmaRxHandle;
static edma_handle_t LPUART1_EdmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart1_edma_driver_state")
static cmsis_lpuart_edma_driver_state_t LPUART1_EdmaDriverState = {
#else
static cmsis_lpuart_edma_driver_state_t LPUART1_EdmaDriverState = {
#endif
    &LPUART1_Resource, &LPUART1_EdmaResource, &LPUART1_EdmaHandle, &LPUART1_EdmaRxHandle, &LPUART1_EdmaTxHandle,
};

static int32_t LPUART1_EdmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART1_PIN_INIT
    RTE_USART1_PIN_INIT();
#endif
    return LPUART_EdmaInitialize(cb_event, &LPUART1_EdmaDriverState);
}

static int32_t LPUART1_EdmaUninitialize(void)
{
#ifdef RTE_USART1_PIN_DEINIT
    RTE_USART1_PIN_DEINIT();
#endif
    return LPUART_EdmaUninitialize(&LPUART1_EdmaDriverState);
}

static int32_t LPUART1_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_EdmaPowerControl(state, &LPUART1_EdmaDriverState);
}

static int32_t LPUART1_EdmaSend(const void *data, uint32_t num)
{
    return LPUART_EdmaSend(data, num, &LPUART1_EdmaDriverState);
}

static int32_t LPUART1_EdmaReceive(void *data, uint32_t num)
{
    return LPUART_EdmaReceive(data, num, &LPUART1_EdmaDriverState);
}

static int32_t LPUART1_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_EdmaTransfer(data_out, data_in, num, &LPUART1_EdmaDriverState);
}

static uint32_t LPUART1_EdmaGetTxCount(void)
{
    return LPUART_EdmaGetTxCount(&LPUART1_EdmaDriverState);
}

static uint32_t LPUART1_EdmaGetRxCount(void)
{
    return LPUART_EdmaGetRxCount(&LPUART1_EdmaDriverState);
}

static int32_t LPUART1_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_EdmaControl(control, arg, &LPUART1_EdmaDriverState);
}

static ARM_USART_STATUS LPUART1_EdmaGetStatus(void)
{
    return LPUART_EdmaGetStatus(&LPUART1_EdmaDriverState);
}

#endif

#else

static lpuart_handle_t LPUART1_Handle;

#if defined(USART1_RX_BUFFER_ENABLE) && (USART1_RX_BUFFER_ENABLE == 1)
static uint8_t lpuart1_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(USART2_RX_BUFFER_ENABLE) && (USART2_RX_BUFFER_ENABLE == 1)
static uint8_t lpuart2_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart1_non_blocking_driver_state")
static cmsis_lpuart_non_blocking_driver_state_t LPUART1_NonBlockingDriverState = {
#else
static cmsis_lpuart_non_blocking_driver_state_t LPUART1_NonBlockingDriverState  = {
#endif
    &LPUART1_Resource,
    &LPUART1_Handle,
};

static int32_t LPUART1_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART1_PIN_INIT
    RTE_USART1_PIN_INIT();
#endif
    return LPUART_NonBlockingInitialize(cb_event, &LPUART1_NonBlockingDriverState);
}

static int32_t LPUART1_NonBlockingUninitialize(void)
{
#ifdef RTE_USART1_PIN_DEINIT
    RTE_USART1_PIN_DEINIT();
#endif
    return LPUART_NonBlockingUninitialize(&LPUART1_NonBlockingDriverState);
}

static int32_t LPUART1_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    int32_t result;

    result = LPUART_NonBlockingPowerControl(state, &LPUART1_NonBlockingDriverState);

#if defined(USART1_RX_BUFFER_ENABLE) && (USART1_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (LPUART1_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        LPUART_TransferStartRingBuffer(LPUART1_NonBlockingDriverState.resource->base,
                                       LPUART1_NonBlockingDriverState.handle, lpuart1_rxRingBuffer,
                                       USART_RX_BUFFER_LEN);
    }
#endif

    return result;
}

static int32_t LPUART1_NonBlockingSend(const void *data, uint32_t num)
{
    return LPUART_NonBlockingSend(data, num, &LPUART1_NonBlockingDriverState);
}

static int32_t LPUART1_NonBlockingReceive(void *data, uint32_t num)
{
    return LPUART_NonBlockingReceive(data, num, &LPUART1_NonBlockingDriverState);
}

static int32_t LPUART1_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_NonBlockingTransfer(data_out, data_in, num, &LPUART1_NonBlockingDriverState);
}

static uint32_t LPUART1_NonBlockingGetTxCount(void)
{
    return LPUART_NonBlockingGetTxCount(&LPUART1_NonBlockingDriverState);
}

static uint32_t LPUART1_NonBlockingGetRxCount(void)
{
    return LPUART_NonBlockingGetRxCount(&LPUART1_NonBlockingDriverState);
}

static int32_t LPUART1_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = LPUART_NonBlockingControl(control, arg, &LPUART1_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }

    /* Enable the receive interrupts if ring buffer is used */
    if (LPUART1_NonBlockingDriverState.handle->rxRingBuffer != NULL)
    {
        LPUART_EnableInterrupts(
            LPUART1_NonBlockingDriverState.resource->base,
            (uint32_t)kLPUART_RxDataRegFullInterruptEnable | (uint32_t)kLPUART_RxOverrunInterruptEnable);
    }

    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS LPUART1_NonBlockingGetStatus(void)
{
    return LPUART_NonBlockingGetStatus(&LPUART1_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART1 = {LPUARTx_GetVersion,      LPUARTx_GetCapabilities,
#if defined(RTE_USART1_DMA_EN) && RTE_USART1_DMA_EN
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
                                  LPUART1_EdmaInitialize,  LPUART1_EdmaUninitialize, LPUART1_EdmaPowerControl,
                                  LPUART1_EdmaSend,        LPUART1_EdmaReceive,      LPUART1_EdmaTransfer,
                                  LPUART1_EdmaGetTxCount,  LPUART1_EdmaGetRxCount,   LPUART1_EdmaControl,
                                  LPUART1_EdmaGetStatus,
#else
                                  LPUART1_DmaInitialize,   LPUART1_DmaUninitialize, LPUART1_DmaPowerControl,
                                  LPUART1_DmaSend,         LPUART1_DmaReceive,      LPUART1_DmaTransfer,
                                  LPUART1_DmaGetTxCount,   LPUART1_DmaGetRxCount,   LPUART1_DmaControl,
                                  LPUART1_DmaGetStatus,
#endif
#else
                                  LPUART1_NonBlockingInitialize,
                                  LPUART1_NonBlockingUninitialize,
                                  LPUART1_NonBlockingPowerControl,
                                  LPUART1_NonBlockingSend,
                                  LPUART1_NonBlockingReceive,
                                  LPUART1_NonBlockingTransfer,
                                  LPUART1_NonBlockingGetTxCount,
                                  LPUART1_NonBlockingGetRxCount,
                                  LPUART1_NonBlockingControl,
                                  LPUART1_NonBlockingGetStatus,
#endif
                                  LPUARTx_SetModemControl, LPUARTx_GetModemStatus};

#endif /* LPUART1 */

#if defined(LPUART2) && defined(RTE_USART2) && RTE_USART2

/* User needs to provide the implementation for LPUART2_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPUART2_GetFreq(void);

static cmsis_lpuart_resource_t LPUART2_Resource = {LPUART2, LPUART2_GetFreq};

#if defined(RTE_USART2_DMA_EN) && RTE_USART2_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_lpuart_dma_resource_t LPUART2_DmaResource = {
    RTE_USART2_DMA_TX_DMA_BASE,    RTE_USART2_DMA_TX_CH,          RTE_USART2_DMA_TX_PERI_SEL,
    RTE_USART2_DMA_RX_DMA_BASE,    RTE_USART2_DMA_RX_CH,          RTE_USART2_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART2_DMA_TX_DMAMUX_BASE, RTE_USART2_DMA_RX_DMAMUX_BASE,
#endif
#if FSL_FEATURE_DMA_MODULE_CHANNEL != FSL_FEATURE_DMAMUX_MODULE_CHANNEL
    RTE_USART2_DMAMUX_TX_CH,       RTE_USART2_DMAMUX_RX_CH
#endif
};

static lpuart_dma_handle_t LPUART2_DmaHandle;
static dma_handle_t LPUART2_DmaRxHandle;
static dma_handle_t LPUART2_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart2_dma_driver_state")
static cmsis_lpuart_dma_driver_state_t LPUART2_DmaDriverState = {
#else
static cmsis_lpuart_dma_driver_state_t LPUART2_DmaDriverState = {
#endif
    &LPUART2_Resource, &LPUART2_DmaResource, &LPUART2_DmaHandle, &LPUART2_DmaRxHandle, &LPUART2_DmaTxHandle,
};

static int32_t LPUART2_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART2_PIN_INIT
    RTE_USART2_PIN_INIT();
#endif
    return LPUART_DmaInitialize(cb_event, &LPUART2_DmaDriverState);
}

static int32_t LPUART2_DmaUninitialize(void)
{
#ifdef RTE_USART2_PIN_DEINIT
    RTE_USART2_PIN_DEINIT();
#endif
    return LPUART_DmaUninitialize(&LPUART2_DmaDriverState);
}

static int32_t LPUART2_DmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_DmaPowerControl(state, &LPUART2_DmaDriverState);
}

static int32_t LPUART2_DmaSend(const void *data, uint32_t num)
{
    return LPUART_DmaSend(data, num, &LPUART2_DmaDriverState);
}

static int32_t LPUART2_DmaReceive(void *data, uint32_t num)
{
    return LPUART_DmaReceive(data, num, &LPUART2_DmaDriverState);
}

static int32_t LPUART2_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_DmaTransfer(data_out, data_in, num, &LPUART2_DmaDriverState);
}

static uint32_t LPUART2_DmaGetTxCount(void)
{
    return LPUART_DmaGetTxCount(&LPUART2_DmaDriverState);
}

static uint32_t LPUART2_DmaGetRxCount(void)
{
    return LPUART_DmaGetRxCount(&LPUART2_DmaDriverState);
}

static int32_t LPUART2_DmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_DmaControl(control, arg, &LPUART2_DmaDriverState);
}

static ARM_USART_STATUS LPUART2_DmaGetStatus(void)
{
    return LPUART_DmaGetStatus(&LPUART2_DmaDriverState);
}

#endif

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)

static cmsis_lpuart_edma_resource_t LPUART2_EdmaResource = {
    RTE_USART2_DMA_TX_DMA_BASE,    RTE_USART2_DMA_TX_CH,          RTE_USART2_DMA_TX_PERI_SEL,
    RTE_USART2_DMA_RX_DMA_BASE,    RTE_USART2_DMA_RX_CH,          RTE_USART2_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART2_DMA_TX_DMAMUX_BASE, RTE_USART2_DMA_RX_DMAMUX_BASE,
#endif
};

static lpuart_edma_handle_t LPUART2_EdmaHandle;
static edma_handle_t LPUART2_EdmaRxHandle;
static edma_handle_t LPUART2_EdmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart2_edma_driver_state")
static cmsis_lpuart_edma_driver_state_t LPUART2_EdmaDriverState = {
#else
static cmsis_lpuart_edma_driver_state_t LPUART2_EdmaDriverState = {
#endif
    &LPUART2_Resource, &LPUART2_EdmaResource, &LPUART2_EdmaHandle, &LPUART2_EdmaRxHandle, &LPUART2_EdmaTxHandle,
};

static int32_t LPUART2_EdmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART2_PIN_INIT
    RTE_USART2_PIN_INIT();
#endif
    return LPUART_EdmaInitialize(cb_event, &LPUART2_EdmaDriverState);
}

static int32_t LPUART2_EdmaUninitialize(void)
{
#ifdef RTE_USART2_PIN_DEINIT
    RTE_USART2_PIN_DEINIT();
#endif
    return LPUART_EdmaUninitialize(&LPUART2_EdmaDriverState);
}

static int32_t LPUART2_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_EdmaPowerControl(state, &LPUART2_EdmaDriverState);
}

static int32_t LPUART2_EdmaSend(const void *data, uint32_t num)
{
    return LPUART_EdmaSend(data, num, &LPUART2_EdmaDriverState);
}

static int32_t LPUART2_EdmaReceive(void *data, uint32_t num)
{
    return LPUART_EdmaReceive(data, num, &LPUART2_EdmaDriverState);
}

static int32_t LPUART2_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_EdmaTransfer(data_out, data_in, num, &LPUART2_EdmaDriverState);
}

static uint32_t LPUART2_EdmaGetTxCount(void)
{
    return LPUART_EdmaGetTxCount(&LPUART2_EdmaDriverState);
}

static uint32_t LPUART2_EdmaGetRxCount(void)
{
    return LPUART_EdmaGetRxCount(&LPUART2_EdmaDriverState);
}

static int32_t LPUART2_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_EdmaControl(control, arg, &LPUART2_EdmaDriverState);
}

static ARM_USART_STATUS LPUART2_EdmaGetStatus(void)
{
    return LPUART_EdmaGetStatus(&LPUART2_EdmaDriverState);
}

#endif

#else

static lpuart_handle_t LPUART2_Handle;

#if defined(USART2_RX_BUFFER_ENABLE) && (USART2_RX_BUFFER_ENABLE == 1)
static uint8_t lpuart2_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(USART3_RX_BUFFER_ENABLE) && (USART3_RX_BUFFER_ENABLE == 1)
static uint8_t lpuart3_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart2_non_blocking_driver_state")
static cmsis_lpuart_non_blocking_driver_state_t LPUART2_NonBlockingDriverState = {
#else
static cmsis_lpuart_non_blocking_driver_state_t LPUART2_NonBlockingDriverState  = {
#endif
    &LPUART2_Resource,
    &LPUART2_Handle,
};

static int32_t LPUART2_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART2_PIN_INIT
    RTE_USART2_PIN_INIT();
#endif
    return LPUART_NonBlockingInitialize(cb_event, &LPUART2_NonBlockingDriverState);
}

static int32_t LPUART2_NonBlockingUninitialize(void)
{
#ifdef RTE_USART2_PIN_DEINIT
    RTE_USART2_PIN_DEINIT();
#endif
    return LPUART_NonBlockingUninitialize(&LPUART2_NonBlockingDriverState);
}

static int32_t LPUART2_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    int32_t result;

    result = LPUART_NonBlockingPowerControl(state, &LPUART2_NonBlockingDriverState);

#if defined(USART2_RX_BUFFER_ENABLE) && (USART2_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (LPUART2_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        LPUART_TransferStartRingBuffer(LPUART2_NonBlockingDriverState.resource->base,
                                       LPUART2_NonBlockingDriverState.handle, lpuart2_rxRingBuffer,
                                       USART_RX_BUFFER_LEN);
    }
#endif

    return result;
}

static int32_t LPUART2_NonBlockingSend(const void *data, uint32_t num)
{
    return LPUART_NonBlockingSend(data, num, &LPUART2_NonBlockingDriverState);
}

static int32_t LPUART2_NonBlockingReceive(void *data, uint32_t num)
{
    return LPUART_NonBlockingReceive(data, num, &LPUART2_NonBlockingDriverState);
}

static int32_t LPUART2_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_NonBlockingTransfer(data_out, data_in, num, &LPUART2_NonBlockingDriverState);
}

static uint32_t LPUART2_NonBlockingGetTxCount(void)
{
    return LPUART_NonBlockingGetTxCount(&LPUART2_NonBlockingDriverState);
}

static uint32_t LPUART2_NonBlockingGetRxCount(void)
{
    return LPUART_NonBlockingGetRxCount(&LPUART2_NonBlockingDriverState);
}

static int32_t LPUART2_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = LPUART_NonBlockingControl(control, arg, &LPUART2_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }

    /* Enable the receive interrupts if ring buffer is used */
    if (LPUART2_NonBlockingDriverState.handle->rxRingBuffer != NULL)
    {
        LPUART_EnableInterrupts(
            LPUART2_NonBlockingDriverState.resource->base,
            (uint32_t)kLPUART_RxDataRegFullInterruptEnable | (uint32_t)kLPUART_RxOverrunInterruptEnable);
    }

    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS LPUART2_NonBlockingGetStatus(void)
{
    return LPUART_NonBlockingGetStatus(&LPUART2_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART2 = {LPUARTx_GetVersion,      LPUARTx_GetCapabilities,
#if defined(RTE_USART2_DMA_EN) && RTE_USART2_DMA_EN
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
                                  LPUART2_EdmaInitialize,  LPUART2_EdmaUninitialize, LPUART2_EdmaPowerControl,
                                  LPUART2_EdmaSend,        LPUART2_EdmaReceive,      LPUART2_EdmaTransfer,
                                  LPUART2_EdmaGetTxCount,  LPUART2_EdmaGetRxCount,   LPUART2_EdmaControl,
                                  LPUART2_EdmaGetStatus,
#else
                                  LPUART2_DmaInitialize,   LPUART2_DmaUninitialize, LPUART2_DmaPowerControl,
                                  LPUART2_DmaSend,         LPUART2_DmaReceive,      LPUART2_DmaTransfer,
                                  LPUART2_DmaGetTxCount,   LPUART2_DmaGetRxCount,   LPUART2_DmaControl,
                                  LPUART2_DmaGetStatus,
#endif
#else
                                  LPUART2_NonBlockingInitialize,
                                  LPUART2_NonBlockingUninitialize,
                                  LPUART2_NonBlockingPowerControl,
                                  LPUART2_NonBlockingSend,
                                  LPUART2_NonBlockingReceive,
                                  LPUART2_NonBlockingTransfer,
                                  LPUART2_NonBlockingGetTxCount,
                                  LPUART2_NonBlockingGetRxCount,
                                  LPUART2_NonBlockingControl,
                                  LPUART2_NonBlockingGetStatus,
#endif
                                  LPUARTx_SetModemControl, LPUARTx_GetModemStatus};

#endif /* LPUART2 */

#if defined(LPUART3) && defined(RTE_USART3) && RTE_USART3

/* User needs to provide the implementation for LPUART3_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPUART3_GetFreq(void);

static cmsis_lpuart_resource_t LPUART3_Resource = {LPUART3, LPUART3_GetFreq};

#if defined(RTE_USART3_DMA_EN) && RTE_USART3_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_lpuart_dma_resource_t LPUART3_DmaResource = {
    RTE_USART3_DMA_TX_DMA_BASE,    RTE_USART3_DMA_TX_CH,          RTE_USART3_DMA_TX_PERI_SEL,
    RTE_USART3_DMA_RX_DMA_BASE,    RTE_USART3_DMA_RX_CH,          RTE_USART3_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART3_DMA_TX_DMAMUX_BASE, RTE_USART3_DMA_RX_DMAMUX_BASE,
#endif
#if FSL_FEATURE_DMA_MODULE_CHANNEL != FSL_FEATURE_DMAMUX_MODULE_CHANNEL
    RTE_USART3_DMAMUX_TX_CH,       RTE_USART3_DMAMUX_RX_CH
#endif
};

static lpuart_dma_handle_t LPUART3_DmaHandle;
static dma_handle_t LPUART3_DmaRxHandle;
static dma_handle_t LPUART3_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart3_dma_driver_state")
static cmsis_lpuart_dma_driver_state_t LPUART3_DmaDriverState = {
#else
static cmsis_lpuart_dma_driver_state_t LPUART3_DmaDriverState = {
#endif
    &LPUART3_Resource, &LPUART3_DmaResource, &LPUART3_DmaHandle, &LPUART3_DmaRxHandle, &LPUART3_DmaTxHandle,
};

static int32_t LPUART3_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART3_PIN_INIT
    RTE_USART3_PIN_INIT();
#endif
    return LPUART_DmaInitialize(cb_event, &LPUART3_DmaDriverState);
}

static int32_t LPUART3_DmaUninitialize(void)
{
#ifdef RTE_USART3_PIN_DEINIT
    RTE_USART3_PIN_DEINIT();
#endif
    return LPUART_DmaUninitialize(&LPUART3_DmaDriverState);
}

static int32_t LPUART3_DmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_DmaPowerControl(state, &LPUART3_DmaDriverState);
}

static int32_t LPUART3_DmaSend(const void *data, uint32_t num)
{
    return LPUART_DmaSend(data, num, &LPUART3_DmaDriverState);
}

static int32_t LPUART3_DmaReceive(void *data, uint32_t num)
{
    return LPUART_DmaReceive(data, num, &LPUART3_DmaDriverState);
}

static int32_t LPUART3_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_DmaTransfer(data_out, data_in, num, &LPUART3_DmaDriverState);
}

static uint32_t LPUART3_DmaGetTxCount(void)
{
    return LPUART_DmaGetTxCount(&LPUART3_DmaDriverState);
}

static uint32_t LPUART3_DmaGetRxCount(void)
{
    return LPUART_DmaGetRxCount(&LPUART3_DmaDriverState);
}

static int32_t LPUART3_DmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_DmaControl(control, arg, &LPUART3_DmaDriverState);
}

static ARM_USART_STATUS LPUART3_DmaGetStatus(void)
{
    return LPUART_DmaGetStatus(&LPUART3_DmaDriverState);
}

#endif

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)

static cmsis_lpuart_edma_resource_t LPUART3_EdmaResource = {
    RTE_USART3_DMA_TX_DMA_BASE,    RTE_USART3_DMA_TX_CH,          RTE_USART3_DMA_TX_PERI_SEL,
    RTE_USART3_DMA_RX_DMA_BASE,    RTE_USART3_DMA_RX_CH,          RTE_USART3_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART3_DMA_TX_DMAMUX_BASE, RTE_USART3_DMA_RX_DMAMUX_BASE,
#endif
};

static lpuart_edma_handle_t LPUART3_EdmaHandle;
static edma_handle_t LPUART3_EdmaRxHandle;
static edma_handle_t LPUART3_EdmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart3_edma_driver_state")
static cmsis_lpuart_edma_driver_state_t LPUART3_EdmaDriverState = {
#else
static cmsis_lpuart_edma_driver_state_t LPUART3_EdmaDriverState = {
#endif
    &LPUART3_Resource, &LPUART3_EdmaResource, &LPUART3_EdmaHandle, &LPUART3_EdmaRxHandle, &LPUART3_EdmaTxHandle,
};

static int32_t LPUART3_EdmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART3_PIN_INIT
    RTE_USART3_PIN_INIT();
#endif
    return LPUART_EdmaInitialize(cb_event, &LPUART3_EdmaDriverState);
}

static int32_t LPUART3_EdmaUninitialize(void)
{
#ifdef RTE_USART3_PIN_DEINIT
    RTE_USART3_PIN_DEINIT();
#endif
    return LPUART_EdmaUninitialize(&LPUART3_EdmaDriverState);
}

static int32_t LPUART3_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_EdmaPowerControl(state, &LPUART3_EdmaDriverState);
}

static int32_t LPUART3_EdmaSend(const void *data, uint32_t num)
{
    return LPUART_EdmaSend(data, num, &LPUART3_EdmaDriverState);
}

static int32_t LPUART3_EdmaReceive(void *data, uint32_t num)
{
    return LPUART_EdmaReceive(data, num, &LPUART3_EdmaDriverState);
}

static int32_t LPUART3_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_EdmaTransfer(data_out, data_in, num, &LPUART3_EdmaDriverState);
}

static uint32_t LPUART3_EdmaGetTxCount(void)
{
    return LPUART_EdmaGetTxCount(&LPUART3_EdmaDriverState);
}

static uint32_t LPUART3_EdmaGetRxCount(void)
{
    return LPUART_EdmaGetRxCount(&LPUART3_EdmaDriverState);
}

static int32_t LPUART3_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_EdmaControl(control, arg, &LPUART3_EdmaDriverState);
}

static ARM_USART_STATUS LPUART3_EdmaGetStatus(void)
{
    return LPUART_EdmaGetStatus(&LPUART3_EdmaDriverState);
}

#endif

#else

static lpuart_handle_t LPUART3_Handle;

#if defined(USART3_RX_BUFFER_ENABLE) && (USART3_RX_BUFFER_ENABLE == 1)
static uint8_t lpuart3_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(USART4_RX_BUFFER_ENABLE) && (USART4_RX_BUFFER_ENABLE == 1)
static uint8_t lpuart4_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart3_non_blocking_driver_state")
static cmsis_lpuart_non_blocking_driver_state_t LPUART3_NonBlockingDriverState = {
#else
static cmsis_lpuart_non_blocking_driver_state_t LPUART3_NonBlockingDriverState  = {
#endif
    &LPUART3_Resource,
    &LPUART3_Handle,
};

static int32_t LPUART3_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART3_PIN_INIT
    RTE_USART3_PIN_INIT();
#endif
    return LPUART_NonBlockingInitialize(cb_event, &LPUART3_NonBlockingDriverState);
}

static int32_t LPUART3_NonBlockingUninitialize(void)
{
#ifdef RTE_USART3_PIN_DEINIT
    RTE_USART3_PIN_DEINIT();
#endif
    return LPUART_NonBlockingUninitialize(&LPUART3_NonBlockingDriverState);
}

static int32_t LPUART3_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    int32_t result;

    result = LPUART_NonBlockingPowerControl(state, &LPUART3_NonBlockingDriverState);

#if defined(USART3_RX_BUFFER_ENABLE) && (USART3_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (LPUART3_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        LPUART_TransferStartRingBuffer(LPUART3_NonBlockingDriverState.resource->base,
                                       LPUART3_NonBlockingDriverState.handle, lpuart3_rxRingBuffer,
                                       USART_RX_BUFFER_LEN);
    }
#endif

    return result;
}

static int32_t LPUART3_NonBlockingSend(const void *data, uint32_t num)
{
    return LPUART_NonBlockingSend(data, num, &LPUART3_NonBlockingDriverState);
}

static int32_t LPUART3_NonBlockingReceive(void *data, uint32_t num)
{
    return LPUART_NonBlockingReceive(data, num, &LPUART3_NonBlockingDriverState);
}

static int32_t LPUART3_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_NonBlockingTransfer(data_out, data_in, num, &LPUART3_NonBlockingDriverState);
}

static uint32_t LPUART3_NonBlockingGetTxCount(void)
{
    return LPUART_NonBlockingGetTxCount(&LPUART3_NonBlockingDriverState);
}

static uint32_t LPUART3_NonBlockingGetRxCount(void)
{
    return LPUART_NonBlockingGetRxCount(&LPUART3_NonBlockingDriverState);
}

static int32_t LPUART3_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = LPUART_NonBlockingControl(control, arg, &LPUART3_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }

    /* Enable the receive interrupts if ring buffer is used */
    if (LPUART3_NonBlockingDriverState.handle->rxRingBuffer != NULL)
    {
        LPUART_EnableInterrupts(
            LPUART3_NonBlockingDriverState.resource->base,
            (uint32_t)kLPUART_RxDataRegFullInterruptEnable | (uint32_t)kLPUART_RxOverrunInterruptEnable);
    }

    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS LPUART3_NonBlockingGetStatus(void)
{
    return LPUART_NonBlockingGetStatus(&LPUART3_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART3 = {LPUARTx_GetVersion,      LPUARTx_GetCapabilities,
#if defined(RTE_USART3_DMA_EN) && RTE_USART3_DMA_EN
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
                                  LPUART3_EdmaInitialize,  LPUART3_EdmaUninitialize, LPUART3_EdmaPowerControl,
                                  LPUART3_EdmaSend,        LPUART3_EdmaReceive,      LPUART3_EdmaTransfer,
                                  LPUART3_EdmaGetTxCount,  LPUART3_EdmaGetRxCount,   LPUART3_EdmaControl,
                                  LPUART3_EdmaGetStatus,
#else
                                  LPUART3_DmaInitialize,   LPUART3_DmaUninitialize, LPUART3_DmaPowerControl,
                                  LPUART3_DmaSend,         LPUART3_DmaReceive,      LPUART3_DmaTransfer,
                                  LPUART3_DmaGetTxCount,   LPUART3_DmaGetRxCount,   LPUART3_DmaControl,
                                  LPUART3_DmaGetStatus,
#endif
#else
                                  LPUART3_NonBlockingInitialize,
                                  LPUART3_NonBlockingUninitialize,
                                  LPUART3_NonBlockingPowerControl,
                                  LPUART3_NonBlockingSend,
                                  LPUART3_NonBlockingReceive,
                                  LPUART3_NonBlockingTransfer,
                                  LPUART3_NonBlockingGetTxCount,
                                  LPUART3_NonBlockingGetRxCount,
                                  LPUART3_NonBlockingControl,
                                  LPUART3_NonBlockingGetStatus,
#endif
                                  LPUARTx_SetModemControl, LPUARTx_GetModemStatus};

#endif /* LPUART3 */

#if defined(LPUART4) && defined(RTE_USART4) && RTE_USART4

/* User needs to provide the implementation for LPUART4_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPUART4_GetFreq(void);

static cmsis_lpuart_resource_t LPUART4_Resource = {LPUART4, LPUART4_GetFreq};

#if defined(RTE_USART4_DMA_EN) && RTE_USART4_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_lpuart_dma_resource_t LPUART4_DmaResource = {
    RTE_USART4_DMA_TX_DMA_BASE,    RTE_USART4_DMA_TX_CH,          RTE_USART4_DMA_TX_PERI_SEL,
    RTE_USART4_DMA_RX_DMA_BASE,    RTE_USART4_DMA_RX_CH,          RTE_USART4_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART4_DMA_TX_DMAMUX_BASE, RTE_USART4_DMA_RX_DMAMUX_BASE,
#endif
#if FSL_FEATURE_DMA_MODULE_CHANNEL != FSL_FEATURE_DMAMUX_MODULE_CHANNEL
    RTE_USART4_DMAMUX_TX_CH,       RTE_USART4_DMAMUX_RX_CH
#endif
};

static lpuart_dma_handle_t LPUART4_DmaHandle;
static dma_handle_t LPUART4_DmaRxHandle;
static dma_handle_t LPUART4_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart4_dma_driver_state")
static cmsis_lpuart_dma_driver_state_t LPUART4_DmaDriverState = {
#else
static cmsis_lpuart_dma_driver_state_t LPUART4_DmaDriverState = {
#endif
    &LPUART4_Resource, &LPUART4_DmaResource, &LPUART4_DmaHandle, &LPUART4_DmaRxHandle, &LPUART4_DmaTxHandle};

static int32_t LPUART4_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART4_PIN_INIT
    RTE_USART4_PIN_INIT();
#endif
    return LPUART_DmaInitialize(cb_event, &LPUART4_DmaDriverState);
}

static int32_t LPUART4_DmaUninitialize(void)
{
#ifdef RTE_USART4_PIN_DEINIT
    RTE_USART4_PIN_DEINIT();
#endif
    return LPUART_DmaUninitialize(&LPUART4_DmaDriverState);
}

static int32_t LPUART4_DmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_DmaPowerControl(state, &LPUART4_DmaDriverState);
}

static int32_t LPUART4_DmaSend(const void *data, uint32_t num)
{
    return LPUART_DmaSend(data, num, &LPUART4_DmaDriverState);
}

static int32_t LPUART4_DmaReceive(void *data, uint32_t num)
{
    return LPUART_DmaReceive(data, num, &LPUART4_DmaDriverState);
}

static int32_t LPUART4_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_DmaTransfer(data_out, data_in, num, &LPUART4_DmaDriverState);
}

static uint32_t LPUART4_DmaGetTxCount(void)
{
    return LPUART_DmaGetTxCount(&LPUART4_DmaDriverState);
}

static uint32_t LPUART4_DmaGetRxCount(void)
{
    return LPUART_DmaGetRxCount(&LPUART4_DmaDriverState);
}

static int32_t LPUART4_DmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_DmaControl(control, arg, &LPUART4_DmaDriverState);
}

static ARM_USART_STATUS LPUART4_DmaGetStatus(void)
{
    return LPUART_DmaGetStatus(&LPUART4_DmaDriverState);
}

#endif

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)

static cmsis_lpuart_edma_resource_t LPUART4_EdmaResource = {
    RTE_USART4_DMA_TX_DMA_BASE,    RTE_USART4_DMA_TX_CH,          RTE_USART4_DMA_TX_PERI_SEL,
    RTE_USART4_DMA_RX_DMA_BASE,    RTE_USART4_DMA_RX_CH,          RTE_USART4_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART4_DMA_TX_DMAMUX_BASE, RTE_USART4_DMA_RX_DMAMUX_BASE,
#endif
};

static lpuart_edma_handle_t LPUART4_EdmaHandle;
static edma_handle_t LPUART4_EdmaRxHandle;
static edma_handle_t LPUART4_EdmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart4_edma_driver_state")
static cmsis_lpuart_edma_driver_state_t LPUART4_EdmaDriverState = {
#else
static cmsis_lpuart_edma_driver_state_t LPUART4_EdmaDriverState = {
#endif
    &LPUART4_Resource, &LPUART4_EdmaResource, &LPUART4_EdmaHandle, &LPUART4_EdmaRxHandle, &LPUART4_EdmaTxHandle};

static int32_t LPUART4_EdmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART4_PIN_INIT
    RTE_USART4_PIN_INIT();
#endif
    return LPUART_EdmaInitialize(cb_event, &LPUART4_EdmaDriverState);
}

static int32_t LPUART4_EdmaUninitialize(void)
{
#ifdef RTE_USART4_PIN_DEINIT
    RTE_USART4_PIN_DEINIT();
#endif
    return LPUART_EdmaUninitialize(&LPUART4_EdmaDriverState);
}

static int32_t LPUART4_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_EdmaPowerControl(state, &LPUART4_EdmaDriverState);
}

static int32_t LPUART4_EdmaSend(const void *data, uint32_t num)
{
    return LPUART_EdmaSend(data, num, &LPUART4_EdmaDriverState);
}

static int32_t LPUART4_EdmaReceive(void *data, uint32_t num)
{
    return LPUART_EdmaReceive(data, num, &LPUART4_EdmaDriverState);
}

static int32_t LPUART4_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_EdmaTransfer(data_out, data_in, num, &LPUART4_EdmaDriverState);
}

static uint32_t LPUART4_EdmaGetTxCount(void)
{
    return LPUART_EdmaGetTxCount(&LPUART4_EdmaDriverState);
}

static uint32_t LPUART4_EdmaGetRxCount(void)
{
    return LPUART_EdmaGetRxCount(&LPUART4_EdmaDriverState);
}

static int32_t LPUART4_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_EdmaControl(control, arg, &LPUART4_EdmaDriverState);
}

static ARM_USART_STATUS LPUART4_EdmaGetStatus(void)
{
    return LPUART_EdmaGetStatus(&LPUART4_EdmaDriverState);
}

#endif

#else

static lpuart_handle_t LPUART4_Handle;

#if defined(USART4_RX_BUFFER_ENABLE) && (USART4_RX_BUFFER_ENABLE == 1)
static uint8_t lpuart4_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(USART5_RX_BUFFER_ENABLE) && (USART5_RX_BUFFER_ENABLE == 1)
static uint8_t lpuart5_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart4_non_blocking_driver_state")
static cmsis_lpuart_non_blocking_driver_state_t LPUART4_NonBlockingDriverState = {
#else
static cmsis_lpuart_non_blocking_driver_state_t LPUART4_NonBlockingDriverState  = {
#endif
    &LPUART4_Resource,
    &LPUART4_Handle,
};

static int32_t LPUART4_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART4_PIN_INIT
    RTE_USART4_PIN_INIT();
#endif
    return LPUART_NonBlockingInitialize(cb_event, &LPUART4_NonBlockingDriverState);
}

static int32_t LPUART4_NonBlockingUninitialize(void)
{
#ifdef RTE_USART4_PIN_DEINIT
    RTE_USART4_PIN_DEINIT();
#endif
    return LPUART_NonBlockingUninitialize(&LPUART4_NonBlockingDriverState);
}

static int32_t LPUART4_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    int32_t result;

    result = LPUART_NonBlockingPowerControl(state, &LPUART4_NonBlockingDriverState);

#if defined(USART4_RX_BUFFER_ENABLE) && (USART4_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (LPUART4_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        LPUART_TransferStartRingBuffer(LPUART4_NonBlockingDriverState.resource->base,
                                       LPUART4_NonBlockingDriverState.handle, lpuart4_rxRingBuffer,
                                       USART_RX_BUFFER_LEN);
    }
#endif

    return result;
}

static int32_t LPUART4_NonBlockingSend(const void *data, uint32_t num)
{
    return LPUART_NonBlockingSend(data, num, &LPUART4_NonBlockingDriverState);
}

static int32_t LPUART4_NonBlockingReceive(void *data, uint32_t num)
{
    return LPUART_NonBlockingReceive(data, num, &LPUART4_NonBlockingDriverState);
}

static int32_t LPUART4_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_NonBlockingTransfer(data_out, data_in, num, &LPUART4_NonBlockingDriverState);
}

static uint32_t LPUART4_NonBlockingGetTxCount(void)
{
    return LPUART_NonBlockingGetTxCount(&LPUART4_NonBlockingDriverState);
}

static uint32_t LPUART4_NonBlockingGetRxCount(void)
{
    return LPUART_NonBlockingGetRxCount(&LPUART4_NonBlockingDriverState);
}

static int32_t LPUART4_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = LPUART_NonBlockingControl(control, arg, &LPUART4_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }

    /* Enable the receive interrupts if ring buffer is used */
    if (LPUART4_NonBlockingDriverState.handle->rxRingBuffer != NULL)
    {
        LPUART_EnableInterrupts(
            LPUART4_NonBlockingDriverState.resource->base,
            (uint32_t)kLPUART_RxDataRegFullInterruptEnable | (uint32_t)kLPUART_RxOverrunInterruptEnable);
    }

    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS LPUART4_NonBlockingGetStatus(void)
{
    return LPUART_NonBlockingGetStatus(&LPUART4_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART4 = {LPUARTx_GetVersion,      LPUARTx_GetCapabilities,
#if defined(RTE_USART4_DMA_EN) && RTE_USART4_DMA_EN
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
                                  LPUART4_EdmaInitialize,  LPUART4_EdmaUninitialize, LPUART4_EdmaPowerControl,
                                  LPUART4_EdmaSend,        LPUART4_EdmaReceive,      LPUART4_EdmaTransfer,
                                  LPUART4_EdmaGetTxCount,  LPUART4_EdmaGetRxCount,   LPUART4_EdmaControl,
                                  LPUART4_EdmaGetStatus,
#else
                                  LPUART4_DmaInitialize,   LPUART4_DmaUninitialize, LPUART4_DmaPowerControl,
                                  LPUART4_DmaSend,         LPUART4_DmaReceive,      LPUART4_DmaTransfer,
                                  LPUART4_DmaGetTxCount,   LPUART4_DmaGetRxCount,   LPUART4_DmaControl,
                                  LPUART4_DmaGetStatus,
#endif
#else
                                  LPUART4_NonBlockingInitialize,
                                  LPUART4_NonBlockingUninitialize,
                                  LPUART4_NonBlockingPowerControl,
                                  LPUART4_NonBlockingSend,
                                  LPUART4_NonBlockingReceive,
                                  LPUART4_NonBlockingTransfer,
                                  LPUART4_NonBlockingGetTxCount,
                                  LPUART4_NonBlockingGetRxCount,
                                  LPUART4_NonBlockingControl,
                                  LPUART4_NonBlockingGetStatus,
#endif
                                  LPUARTx_SetModemControl, LPUARTx_GetModemStatus};

#endif /* LPUART4 */

#if defined(LPUART5) && defined(RTE_USART5) && RTE_USART5

/* User needs to provide the implementation for LPUART5_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPUART5_GetFreq(void);

static cmsis_lpuart_resource_t LPUART5_Resource = {LPUART5, LPUART5_GetFreq};

#if defined(RTE_USART5_DMA_EN) && RTE_USART5_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_lpuart_dma_resource_t LPUART5_DmaResource = {
    RTE_USART5_DMA_TX_DMA_BASE,    RTE_USART5_DMA_TX_CH,          RTE_USART5_DMA_TX_PERI_SEL,
    RTE_USART5_DMA_RX_DMA_BASE,    RTE_USART5_DMA_RX_CH,          RTE_USART5_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART5_DMA_TX_DMAMUX_BASE, RTE_USART5_DMA_RX_DMAMUX_BASE,
#endif
#if FSL_FEATURE_DMA_MODULE_CHANNEL != FSL_FEATURE_DMAMUX_MODULE_CHANNEL
    RTE_USART5_DMAMUX_TX_CH,       RTE_USART5_DMAMUX_RX_CH
#endif
};

static lpuart_dma_handle_t LPUART5_DmaHandle;
static dma_handle_t LPUART5_DmaRxHandle;
static dma_handle_t LPUART5_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart5_dma_driver_state")
static cmsis_lpuart_dma_driver_state_t LPUART5_DmaDriverState = {
#else
static cmsis_lpuart_dma_driver_state_t LPUART5_DmaDriverState = {
#endif
    &LPUART5_Resource, &LPUART5_DmaResource, &LPUART5_DmaHandle, &LPUART5_DmaRxHandle, &LPUART5_DmaTxHandle,
};

static int32_t LPUART5_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART5_PIN_INIT
    RTE_USART5_PIN_INIT();
#endif
    return LPUART_DmaInitialize(cb_event, &LPUART5_DmaDriverState);
}

static int32_t LPUART5_DmaUninitialize(void)
{
#ifdef RTE_USART5_PIN_DEINIT
    RTE_USART5_PIN_DEINIT();
#endif
    return LPUART_DmaUninitialize(&LPUART5_DmaDriverState);
}

static int32_t LPUART5_DmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_DmaPowerControl(state, &LPUART5_DmaDriverState);
}

static int32_t LPUART5_DmaSend(const void *data, uint32_t num)
{
    return LPUART_DmaSend(data, num, &LPUART5_DmaDriverState);
}

static int32_t LPUART5_DmaReceive(void *data, uint32_t num)
{
    return LPUART_DmaReceive(data, num, &LPUART5_DmaDriverState);
}

static int32_t LPUART5_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_DmaTransfer(data_out, data_in, num, &LPUART5_DmaDriverState);
}

static uint32_t LPUART5_DmaGetTxCount(void)
{
    return LPUART_DmaGetTxCount(&LPUART5_DmaDriverState);
}

static uint32_t LPUART5_DmaGetRxCount(void)
{
    return LPUART_DmaGetRxCount(&LPUART5_DmaDriverState);
}

static int32_t LPUART5_DmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_DmaControl(control, arg, &LPUART5_DmaDriverState);
}

static ARM_USART_STATUS LPUART5_DmaGetStatus(void)
{
    return LPUART_DmaGetStatus(&LPUART5_DmaDriverState);
}

/* LPUART5 Driver Control Block */

#endif

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)

static cmsis_lpuart_edma_resource_t LPUART5_EdmaResource = {
    RTE_USART5_DMA_TX_DMA_BASE,    RTE_USART5_DMA_TX_CH,          RTE_USART5_DMA_TX_PERI_SEL,
    RTE_USART5_DMA_RX_DMA_BASE,    RTE_USART5_DMA_RX_CH,          RTE_USART5_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART5_DMA_TX_DMAMUX_BASE, RTE_USART5_DMA_RX_DMAMUX_BASE,
#endif
};

static lpuart_edma_handle_t LPUART5_EdmaHandle;
static edma_handle_t LPUART5_EdmaRxHandle;
static edma_handle_t LPUART5_EdmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart5_edma_driver_state")
static cmsis_lpuart_edma_driver_state_t LPUART5_EdmaDriverState = {
#else
static cmsis_lpuart_edma_driver_state_t LPUART5_EdmaDriverState = {
#endif
    &LPUART5_Resource, &LPUART5_EdmaResource, &LPUART5_EdmaHandle, &LPUART5_EdmaRxHandle, &LPUART5_EdmaTxHandle,
};

static int32_t LPUART5_EdmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART5_PIN_INIT
    RTE_USART5_PIN_INIT();
#endif
    return LPUART_EdmaInitialize(cb_event, &LPUART5_EdmaDriverState);
}

static int32_t LPUART5_EdmaUninitialize(void)
{
#ifdef RTE_USART5_PIN_DEINIT
    RTE_USART5_PIN_DEINIT();
#endif
    return LPUART_EdmaUninitialize(&LPUART5_EdmaDriverState);
}

static int32_t LPUART5_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_EdmaPowerControl(state, &LPUART5_EdmaDriverState);
}

static int32_t LPUART5_EdmaSend(const void *data, uint32_t num)
{
    return LPUART_EdmaSend(data, num, &LPUART5_EdmaDriverState);
}

static int32_t LPUART5_EdmaReceive(void *data, uint32_t num)
{
    return LPUART_EdmaReceive(data, num, &LPUART5_EdmaDriverState);
}

static int32_t LPUART5_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_EdmaTransfer(data_out, data_in, num, &LPUART5_EdmaDriverState);
}

static uint32_t LPUART5_EdmaGetTxCount(void)
{
    return LPUART_EdmaGetTxCount(&LPUART5_EdmaDriverState);
}

static uint32_t LPUART5_EdmaGetRxCount(void)
{
    return LPUART_EdmaGetRxCount(&LPUART5_EdmaDriverState);
}

static int32_t LPUART5_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_EdmaControl(control, arg, &LPUART5_EdmaDriverState);
}

static ARM_USART_STATUS LPUART5_EdmaGetStatus(void)
{
    return LPUART_EdmaGetStatus(&LPUART5_EdmaDriverState);
}

#endif

#else

static lpuart_handle_t LPUART5_Handle;

#if defined(USART5_RX_BUFFER_ENABLE) && (USART5_RX_BUFFER_ENABLE == 1)
static uint8_t lpuart5_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart5_non_blocking_driver_state")
static cmsis_lpuart_non_blocking_driver_state_t LPUART5_NonBlockingDriverState = {
#else
static cmsis_lpuart_non_blocking_driver_state_t LPUART5_NonBlockingDriverState  = {
#endif
    &LPUART5_Resource,
    &LPUART5_Handle,
};

static int32_t LPUART5_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART5_PIN_INIT
    RTE_USART5_PIN_INIT();
#endif
    return LPUART_NonBlockingInitialize(cb_event, &LPUART5_NonBlockingDriverState);
}

static int32_t LPUART5_NonBlockingUninitialize(void)
{
#ifdef RTE_USART5_PIN_DEINIT
    RTE_USART5_PIN_DEINIT();
#endif
    return LPUART_NonBlockingUninitialize(&LPUART5_NonBlockingDriverState);
}

static int32_t LPUART5_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    int32_t result;

    result = LPUART_NonBlockingPowerControl(state, &LPUART5_NonBlockingDriverState);

#if defined(USART5_RX_BUFFER_ENABLE) && (USART5_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (LPUART5_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        LPUART_TransferStartRingBuffer(LPUART5_NonBlockingDriverState.resource->base,
                                       LPUART5_NonBlockingDriverState.handle, lpuart5_rxRingBuffer,
                                       USART_RX_BUFFER_LEN);
    }
#endif

    return result;
}

static int32_t LPUART5_NonBlockingSend(const void *data, uint32_t num)
{
    return LPUART_NonBlockingSend(data, num, &LPUART5_NonBlockingDriverState);
}

static int32_t LPUART5_NonBlockingReceive(void *data, uint32_t num)
{
    return LPUART_NonBlockingReceive(data, num, &LPUART5_NonBlockingDriverState);
}

static int32_t LPUART5_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_NonBlockingTransfer(data_out, data_in, num, &LPUART5_NonBlockingDriverState);
}

static uint32_t LPUART5_NonBlockingGetTxCount(void)
{
    return LPUART_NonBlockingGetTxCount(&LPUART5_NonBlockingDriverState);
}

static uint32_t LPUART5_NonBlockingGetRxCount(void)
{
    return LPUART_NonBlockingGetRxCount(&LPUART5_NonBlockingDriverState);
}

static int32_t LPUART5_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = LPUART_NonBlockingControl(control, arg, &LPUART5_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }

    /* Enable the receive interrupts if ring buffer is used */
    if (LPUART5_NonBlockingDriverState.handle->rxRingBuffer != NULL)
    {
        LPUART_EnableInterrupts(
            LPUART5_NonBlockingDriverState.resource->base,
            (uint32_t)kLPUART_RxDataRegFullInterruptEnable | (uint32_t)kLPUART_RxOverrunInterruptEnable);
    }

    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS LPUART5_NonBlockingGetStatus(void)
{
    return LPUART_NonBlockingGetStatus(&LPUART5_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART5 = {LPUARTx_GetVersion,      LPUARTx_GetCapabilities,
#if defined(RTE_USART5_DMA_EN) && RTE_USART5_DMA_EN
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
                                  LPUART5_EdmaInitialize,  LPUART5_EdmaUninitialize, LPUART5_EdmaPowerControl,
                                  LPUART5_EdmaSend,        LPUART5_EdmaReceive,      LPUART5_EdmaTransfer,
                                  LPUART5_EdmaGetTxCount,  LPUART5_EdmaGetRxCount,   LPUART5_EdmaControl,
                                  LPUART5_EdmaGetStatus,
#else
                                  LPUART5_DmaInitialize,   LPUART5_DmaUninitialize, LPUART5_DmaPowerControl,
                                  LPUART5_DmaSend,         LPUART5_DmaReceive,      LPUART5_DmaTransfer,
                                  LPUART5_DmaGetTxCount,   LPUART5_DmaGetRxCount,   LPUART5_DmaControl,
                                  LPUART5_DmaGetStatus,
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */
#else
                                  LPUART5_NonBlockingInitialize,
                                  LPUART5_NonBlockingUninitialize,
                                  LPUART5_NonBlockingPowerControl,
                                  LPUART5_NonBlockingSend,
                                  LPUART5_NonBlockingReceive,
                                  LPUART5_NonBlockingTransfer,
                                  LPUART5_NonBlockingGetTxCount,
                                  LPUART5_NonBlockingGetRxCount,
                                  LPUART5_NonBlockingControl,
                                  LPUART5_NonBlockingGetStatus,
#endif /* RTE_USART5_DMA_EN */
                                  LPUARTx_SetModemControl, LPUARTx_GetModemStatus};

#endif /* LPUART5 */

#if defined(LPUART6) && defined(RTE_USART6) && RTE_USART6

/* User needs to provide the implementation for LPUART5_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPUART6_GetFreq(void);

static cmsis_lpuart_resource_t LPUART6_Resource = {LPUART6, LPUART6_GetFreq};

#if defined(RTE_USART6_DMA_EN) && RTE_USART6_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_lpuart_dma_resource_t LPUART6_DmaResource = {
    RTE_USART6_DMA_TX_DMA_BASE,    RTE_USART6_DMA_TX_CH,          RTE_USART6_DMA_TX_PERI_SEL,
    RTE_USART6_DMA_RX_DMA_BASE,    RTE_USART6_DMA_RX_CH,          RTE_USART6_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART6_DMA_TX_DMAMUX_BASE, RTE_USART6_DMA_RX_DMAMUX_BASE,
#endif
#if FSL_FEATURE_DMA_MODULE_CHANNEL != FSL_FEATURE_DMAMUX_MODULE_CHANNEL
    RTE_USART6_DMAMUX_TX_CH,       RTE_USART6_DMAMUX_RX_CH
#endif
};

static lpuart_dma_handle_t LPUART6_DmaHandle;
static dma_handle_t LPUART6_DmaRxHandle;
static dma_handle_t LPUART6_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart5_dma_driver_state")
static cmsis_lpuart_dma_driver_state_t LPUART6_DmaDriverState = {
#else
static cmsis_lpuart_dma_driver_state_t LPUART6_DmaDriverState = {
#endif
    &LPUART6_Resource, &LPUART6_DmaResource, &LPUART6_DmaHandle, &LPUART6_DmaRxHandle, &LPUART6_DmaTxHandle,
};

static int32_t LPUART6_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART6_PIN_INIT
    RTE_USART6_PIN_INIT();
#endif
    return LPUART_DmaInitialize(cb_event, &LPUART6_DmaDriverState);
}

static int32_t LPUART6_DmaUninitialize(void)
{
#ifdef RTE_USART6_PIN_DEINIT
    RTE_USART6_PIN_DEINIT();
#endif
    return LPUART_DmaUninitialize(&LPUART6_DmaDriverState);
}

static int32_t LPUART6_DmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_DmaPowerControl(state, &LPUART6_DmaDriverState);
}

static int32_t LPUART6_DmaSend(const void *data, uint32_t num)
{
    return LPUART_DmaSend(data, num, &LPUART6_DmaDriverState);
}

static int32_t LPUART6_DmaReceive(void *data, uint32_t num)
{
    return LPUART_DmaReceive(data, num, &LPUART6_DmaDriverState);
}

static int32_t LPUART6_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_DmaTransfer(data_out, data_in, num, &LPUART6_DmaDriverState);
}

static uint32_t LPUART6_DmaGetTxCount(void)
{
    return LPUART_DmaGetTxCount(&LPUART6_DmaDriverState);
}

static uint32_t LPUART6_DmaGetRxCount(void)
{
    return LPUART_DmaGetRxCount(&LPUART6_DmaDriverState);
}

static int32_t LPUART6_DmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_DmaControl(control, arg, &LPUART6_DmaDriverState);
}

static ARM_USART_STATUS LPUART6_DmaGetStatus(void)
{
    return LPUART_DmaGetStatus(&LPUART6_DmaDriverState);
}

/* LPUART6 Driver Control Block */

#endif

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)

static cmsis_lpuart_edma_resource_t LPUART6_EdmaResource = {
    RTE_USART6_DMA_TX_DMA_BASE,    RTE_USART6_DMA_TX_CH,          RTE_USART6_DMA_TX_PERI_SEL,
    RTE_USART6_DMA_RX_DMA_BASE,    RTE_USART6_DMA_RX_CH,          RTE_USART6_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART6_DMA_TX_DMAMUX_BASE, RTE_USART6_DMA_RX_DMAMUX_BASE,
#endif
};

static lpuart_edma_handle_t LPUART6_EdmaHandle;
static edma_handle_t LPUART6_EdmaRxHandle;
static edma_handle_t LPUART6_EdmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart6_edma_driver_state")
static cmsis_lpuart_edma_driver_state_t LPUART6_EdmaDriverState = {
#else
static cmsis_lpuart_edma_driver_state_t LPUART6_EdmaDriverState = {
#endif
    &LPUART6_Resource, &LPUART6_EdmaResource, &LPUART6_EdmaHandle, &LPUART6_EdmaRxHandle, &LPUART6_EdmaTxHandle,
};

static int32_t LPUART6_EdmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART6_PIN_INIT
    RTE_USART6_PIN_INIT();
#endif
    return LPUART_EdmaInitialize(cb_event, &LPUART6_EdmaDriverState);
}

static int32_t LPUART6_EdmaUninitialize(void)
{
#ifdef RTE_USART6_PIN_DEINIT
    RTE_USART6_PIN_DEINIT();
#endif
    return LPUART_EdmaUninitialize(&LPUART6_EdmaDriverState);
}

static int32_t LPUART6_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_EdmaPowerControl(state, &LPUART6_EdmaDriverState);
}

static int32_t LPUART6_EdmaSend(const void *data, uint32_t num)
{
    return LPUART_EdmaSend(data, num, &LPUART6_EdmaDriverState);
}

static int32_t LPUART6_EdmaReceive(void *data, uint32_t num)
{
    return LPUART_EdmaReceive(data, num, &LPUART6_EdmaDriverState);
}

static int32_t LPUART6_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_EdmaTransfer(data_out, data_in, num, &LPUART6_EdmaDriverState);
}

static uint32_t LPUART6_EdmaGetTxCount(void)
{
    return LPUART_EdmaGetTxCount(&LPUART6_EdmaDriverState);
}

static uint32_t LPUART6_EdmaGetRxCount(void)
{
    return LPUART_EdmaGetRxCount(&LPUART6_EdmaDriverState);
}

static int32_t LPUART6_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_EdmaControl(control, arg, &LPUART6_EdmaDriverState);
}

static ARM_USART_STATUS LPUART6_EdmaGetStatus(void)
{
    return LPUART_EdmaGetStatus(&LPUART6_EdmaDriverState);
}

#endif

#else

static lpuart_handle_t LPUART6_Handle;

#if defined(USART6_RX_BUFFER_ENABLE) && (USART6_RX_BUFFER_ENABLE == 1)
static uint8_t lpuart6_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart6_non_blocking_driver_state")
static cmsis_lpuart_non_blocking_driver_state_t LPUART6_NonBlockingDriverState = {
#else
static cmsis_lpuart_non_blocking_driver_state_t LPUART6_NonBlockingDriverState  = {
#endif
    &LPUART6_Resource,
    &LPUART6_Handle,
};

static int32_t LPUART6_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART6_PIN_INIT
    RTE_USART6_PIN_INIT();
#endif
    return LPUART_NonBlockingInitialize(cb_event, &LPUART6_NonBlockingDriverState);
}

static int32_t LPUART6_NonBlockingUninitialize(void)
{
#ifdef RTE_USART6_PIN_DEINIT
    RTE_USART6_PIN_DEINIT();
#endif
    return LPUART_NonBlockingUninitialize(&LPUART6_NonBlockingDriverState);
}

static int32_t LPUART6_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    int32_t result;

    result = LPUART_NonBlockingPowerControl(state, &LPUART6_NonBlockingDriverState);

#if defined(USART6_RX_BUFFER_ENABLE) && (USART6_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (LPUART6_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        LPUART_TransferStartRingBuffer(LPUART6_NonBlockingDriverState.resource->base,
                                       LPUART6_NonBlockingDriverState.handle, lpuart6_rxRingBuffer,
                                       USART_RX_BUFFER_LEN);
    }
#endif

    return result;
}

static int32_t LPUART6_NonBlockingSend(const void *data, uint32_t num)
{
    return LPUART_NonBlockingSend(data, num, &LPUART6_NonBlockingDriverState);
}

static int32_t LPUART6_NonBlockingReceive(void *data, uint32_t num)
{
    return LPUART_NonBlockingReceive(data, num, &LPUART6_NonBlockingDriverState);
}

static int32_t LPUART6_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_NonBlockingTransfer(data_out, data_in, num, &LPUART6_NonBlockingDriverState);
}

static uint32_t LPUART6_NonBlockingGetTxCount(void)
{
    return LPUART_NonBlockingGetTxCount(&LPUART6_NonBlockingDriverState);
}

static uint32_t LPUART6_NonBlockingGetRxCount(void)
{
    return LPUART_NonBlockingGetRxCount(&LPUART6_NonBlockingDriverState);
}

static int32_t LPUART6_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = LPUART_NonBlockingControl(control, arg, &LPUART6_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }

    /* Enable the receive interrupts if ring buffer is used */
    if (LPUART6_NonBlockingDriverState.handle->rxRingBuffer != NULL)
    {
        LPUART_EnableInterrupts(
            LPUART6_NonBlockingDriverState.resource->base,
            (uint32_t)kLPUART_RxDataRegFullInterruptEnable | (uint32_t)kLPUART_RxOverrunInterruptEnable);
    }

    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS LPUART6_NonBlockingGetStatus(void)
{
    return LPUART_NonBlockingGetStatus(&LPUART6_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART6 = {LPUARTx_GetVersion,      LPUARTx_GetCapabilities,
#if defined(RTE_USART6_DMA_EN) && RTE_USART6_DMA_EN
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
                                  LPUART6_EdmaInitialize,  LPUART6_EdmaUninitialize, LPUART6_EdmaPowerControl,
                                  LPUART6_EdmaSend,        LPUART6_EdmaReceive,      LPUART6_EdmaTransfer,
                                  LPUART6_EdmaGetTxCount,  LPUART6_EdmaGetRxCount,   LPUART6_EdmaControl,
                                  LPUART6_EdmaGetStatus,
#else
                                  LPUART6_DmaInitialize,   LPUART6_DmaUninitialize, LPUART6_DmaPowerControl,
                                  LPUART6_DmaSend,         LPUART6_DmaReceive,      LPUART6_DmaTransfer,
                                  LPUART6_DmaGetTxCount,   LPUART6_DmaGetRxCount,   LPUART6_DmaControl,
                                  LPUART6_DmaGetStatus,
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */
#else
                                  LPUART6_NonBlockingInitialize,
                                  LPUART6_NonBlockingUninitialize,
                                  LPUART6_NonBlockingPowerControl,
                                  LPUART6_NonBlockingSend,
                                  LPUART6_NonBlockingReceive,
                                  LPUART6_NonBlockingTransfer,
                                  LPUART6_NonBlockingGetTxCount,
                                  LPUART6_NonBlockingGetRxCount,
                                  LPUART6_NonBlockingControl,
                                  LPUART6_NonBlockingGetStatus,
#endif /* RTE_USART6_DMA_EN */
                                  LPUARTx_SetModemControl, LPUARTx_GetModemStatus};

#endif /* LPUART6 */

#if defined(LPUART7) && defined(RTE_USART7) && RTE_USART7

/* User needs to provide the implementation for LPUART5_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPUART7_GetFreq(void);

static cmsis_lpuart_resource_t LPUART7_Resource = {LPUART7, LPUART7_GetFreq};

#if defined(RTE_USART7_DMA_EN) && RTE_USART7_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_lpuart_dma_resource_t LPUART7_DmaResource = {
    RTE_USART7_DMA_TX_DMA_BASE,    RTE_USART7_DMA_TX_CH,          RTE_USART7_DMA_TX_PERI_SEL,
    RTE_USART7_DMA_RX_DMA_BASE,    RTE_USART7_DMA_RX_CH,          RTE_USART7_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART7_DMA_TX_DMAMUX_BASE, RTE_USART7_DMA_RX_DMAMUX_BASE,
#endif
#if FSL_FEATURE_DMA_MODULE_CHANNEL != FSL_FEATURE_DMAMUX_MODULE_CHANNEL
    RTE_USART7_DMAMUX_TX_CH,       RTE_USART7_DMAMUX_RX_CH
#endif
};

static lpuart_dma_handle_t LPUART7_DmaHandle;
static dma_handle_t LPUART7_DmaRxHandle;
static dma_handle_t LPUART7_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart5_dma_driver_state")
static cmsis_lpuart_dma_driver_state_t LPUART7_DmaDriverState = {
#else
static cmsis_lpuart_dma_driver_state_t LPUART7_DmaDriverState = {
#endif
    &LPUART7_Resource, &LPUART7_DmaResource, &LPUART7_DmaHandle, &LPUART7_DmaRxHandle, &LPUART7_DmaTxHandle,
};

static int32_t LPUART7_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART7_PIN_INIT
    RTE_USART7_PIN_INIT();
#endif
    return LPUART_DmaInitialize(cb_event, &LPUART7_DmaDriverState);
}

static int32_t LPUART7_DmaUninitialize(void)
{
#ifdef RTE_USART7_PIN_DEINIT
    RTE_USART7_PIN_DEINIT();
#endif
    return LPUART_DmaUninitialize(&LPUART7_DmaDriverState);
}

static int32_t LPUART7_DmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_DmaPowerControl(state, &LPUART7_DmaDriverState);
}

static int32_t LPUART7_DmaSend(const void *data, uint32_t num)
{
    return LPUART_DmaSend(data, num, &LPUART7_DmaDriverState);
}

static int32_t LPUART7_DmaReceive(void *data, uint32_t num)
{
    return LPUART_DmaReceive(data, num, &LPUART7_DmaDriverState);
}

static int32_t LPUART7_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_DmaTransfer(data_out, data_in, num, &LPUART7_DmaDriverState);
}

static uint32_t LPUART7_DmaGetTxCount(void)
{
    return LPUART_DmaGetTxCount(&LPUART7_DmaDriverState);
}

static uint32_t LPUART7_DmaGetRxCount(void)
{
    return LPUART_DmaGetRxCount(&LPUART7_DmaDriverState);
}

static int32_t LPUART7_DmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_DmaControl(control, arg, &LPUART7_DmaDriverState);
}

static ARM_USART_STATUS LPUART7_DmaGetStatus(void)
{
    return LPUART_DmaGetStatus(&LPUART7_DmaDriverState);
}

/* LPUART7 Driver Control Block */

#endif

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)

static cmsis_lpuart_edma_resource_t LPUART7_EdmaResource = {
    RTE_USART7_DMA_TX_DMA_BASE,    RTE_USART7_DMA_TX_CH,          RTE_USART7_DMA_TX_PERI_SEL,
    RTE_USART7_DMA_RX_DMA_BASE,    RTE_USART7_DMA_RX_CH,          RTE_USART7_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART7_DMA_TX_DMAMUX_BASE, RTE_USART7_DMA_RX_DMAMUX_BASE,
#endif
};

static lpuart_edma_handle_t LPUART7_EdmaHandle;
static edma_handle_t LPUART7_EdmaRxHandle;
static edma_handle_t LPUART7_EdmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart7_edma_driver_state")
static cmsis_lpuart_edma_driver_state_t LPUART7_EdmaDriverState = {
#else
static cmsis_lpuart_edma_driver_state_t LPUART7_EdmaDriverState = {
#endif
    &LPUART7_Resource, &LPUART7_EdmaResource, &LPUART7_EdmaHandle, &LPUART7_EdmaRxHandle, &LPUART7_EdmaTxHandle,
};

static int32_t LPUART7_EdmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART7_PIN_INIT
    RTE_USART7_PIN_INIT();
#endif
    return LPUART_EdmaInitialize(cb_event, &LPUART7_EdmaDriverState);
}

static int32_t LPUART7_EdmaUninitialize(void)
{
#ifdef RTE_USART7_PIN_DEINIT
    RTE_USART7_PIN_DEINIT();
#endif
    return LPUART_EdmaUninitialize(&LPUART7_EdmaDriverState);
}

static int32_t LPUART7_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_EdmaPowerControl(state, &LPUART7_EdmaDriverState);
}

static int32_t LPUART7_EdmaSend(const void *data, uint32_t num)
{
    return LPUART_EdmaSend(data, num, &LPUART7_EdmaDriverState);
}

static int32_t LPUART7_EdmaReceive(void *data, uint32_t num)
{
    return LPUART_EdmaReceive(data, num, &LPUART7_EdmaDriverState);
}

static int32_t LPUART7_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_EdmaTransfer(data_out, data_in, num, &LPUART7_EdmaDriverState);
}

static uint32_t LPUART7_EdmaGetTxCount(void)
{
    return LPUART_EdmaGetTxCount(&LPUART7_EdmaDriverState);
}

static uint32_t LPUART7_EdmaGetRxCount(void)
{
    return LPUART_EdmaGetRxCount(&LPUART7_EdmaDriverState);
}

static int32_t LPUART7_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_EdmaControl(control, arg, &LPUART7_EdmaDriverState);
}

static ARM_USART_STATUS LPUART7_EdmaGetStatus(void)
{
    return LPUART_EdmaGetStatus(&LPUART7_EdmaDriverState);
}

#endif

#else

static lpuart_handle_t LPUART7_Handle;

#if defined(USART7_RX_BUFFER_ENABLE) && (USART7_RX_BUFFER_ENABLE == 1)
static uint8_t lpuart7_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart7_non_blocking_driver_state")
static cmsis_lpuart_non_blocking_driver_state_t LPUART7_NonBlockingDriverState = {
#else
static cmsis_lpuart_non_blocking_driver_state_t LPUART7_NonBlockingDriverState  = {
#endif
    &LPUART7_Resource,
    &LPUART7_Handle,
};

static int32_t LPUART7_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART7_PIN_INIT
    RTE_USART7_PIN_INIT();
#endif
    return LPUART_NonBlockingInitialize(cb_event, &LPUART7_NonBlockingDriverState);
}

static int32_t LPUART7_NonBlockingUninitialize(void)
{
#ifdef RTE_USART7_PIN_DEINIT
    RTE_USART7_PIN_DEINIT();
#endif
    return LPUART_NonBlockingUninitialize(&LPUART7_NonBlockingDriverState);
}

static int32_t LPUART7_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    int32_t result;

    result = LPUART_NonBlockingPowerControl(state, &LPUART7_NonBlockingDriverState);

#if defined(USART7_RX_BUFFER_ENABLE) && (USART7_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (LPUART7_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        LPUART_TransferStartRingBuffer(LPUART7_NonBlockingDriverState.resource->base,
                                       LPUART7_NonBlockingDriverState.handle, lpuart7_rxRingBuffer,
                                       USART_RX_BUFFER_LEN);
    }
#endif

    return result;
}

static int32_t LPUART7_NonBlockingSend(const void *data, uint32_t num)
{
    return LPUART_NonBlockingSend(data, num, &LPUART7_NonBlockingDriverState);
}

static int32_t LPUART7_NonBlockingReceive(void *data, uint32_t num)
{
    return LPUART_NonBlockingReceive(data, num, &LPUART7_NonBlockingDriverState);
}

static int32_t LPUART7_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_NonBlockingTransfer(data_out, data_in, num, &LPUART7_NonBlockingDriverState);
}

static uint32_t LPUART7_NonBlockingGetTxCount(void)
{
    return LPUART_NonBlockingGetTxCount(&LPUART7_NonBlockingDriverState);
}

static uint32_t LPUART7_NonBlockingGetRxCount(void)
{
    return LPUART_NonBlockingGetRxCount(&LPUART7_NonBlockingDriverState);
}

static int32_t LPUART7_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = LPUART_NonBlockingControl(control, arg, &LPUART7_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }

    /* Enable the receive interrupts if ring buffer is used */
    if (LPUART7_NonBlockingDriverState.handle->rxRingBuffer != NULL)
    {
        LPUART_EnableInterrupts(
            LPUART7_NonBlockingDriverState.resource->base,
            (uint32_t)kLPUART_RxDataRegFullInterruptEnable | (uint32_t)kLPUART_RxOverrunInterruptEnable);
    }

    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS LPUART7_NonBlockingGetStatus(void)
{
    return LPUART_NonBlockingGetStatus(&LPUART7_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART7 = {LPUARTx_GetVersion,      LPUARTx_GetCapabilities,
#if defined(RTE_USART7_DMA_EN) && RTE_USART7_DMA_EN
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
                                  LPUART7_EdmaInitialize,  LPUART7_EdmaUninitialize, LPUART7_EdmaPowerControl,
                                  LPUART7_EdmaSend,        LPUART7_EdmaReceive,      LPUART7_EdmaTransfer,
                                  LPUART7_EdmaGetTxCount,  LPUART7_EdmaGetRxCount,   LPUART7_EdmaControl,
                                  LPUART7_EdmaGetStatus,
#else
                                  LPUART7_DmaInitialize,   LPUART7_DmaUninitialize, LPUART7_DmaPowerControl,
                                  LPUART7_DmaSend,         LPUART7_DmaReceive,      LPUART7_DmaTransfer,
                                  LPUART7_DmaGetTxCount,   LPUART7_DmaGetRxCount,   LPUART7_DmaControl,
                                  LPUART7_DmaGetStatus,
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */
#else
                                  LPUART7_NonBlockingInitialize,
                                  LPUART7_NonBlockingUninitialize,
                                  LPUART7_NonBlockingPowerControl,
                                  LPUART7_NonBlockingSend,
                                  LPUART7_NonBlockingReceive,
                                  LPUART7_NonBlockingTransfer,
                                  LPUART7_NonBlockingGetTxCount,
                                  LPUART7_NonBlockingGetRxCount,
                                  LPUART7_NonBlockingControl,
                                  LPUART7_NonBlockingGetStatus,
#endif /* RTE_USART7_DMA_EN */
                                  LPUARTx_SetModemControl, LPUARTx_GetModemStatus};

#endif /* LPUART7 */

#if defined(LPUART8) && defined(RTE_USART8) && RTE_USART8

/* User needs to provide the implementation for LPUART5_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPUART8_GetFreq(void);

static cmsis_lpuart_resource_t LPUART8_Resource = {LPUART8, LPUART8_GetFreq};

#if defined(RTE_USART8_DMA_EN) && RTE_USART8_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_lpuart_dma_resource_t LPUART8_DmaResource = {
    RTE_USART8_DMA_TX_DMA_BASE,    RTE_USART8_DMA_TX_CH,          RTE_USART8_DMA_TX_PERI_SEL,
    RTE_USART8_DMA_RX_DMA_BASE,    RTE_USART8_DMA_RX_CH,          RTE_USART8_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART8_DMA_TX_DMAMUX_BASE, RTE_USART8_DMA_RX_DMAMUX_BASE,
#endif
#if FSL_FEATURE_DMA_MODULE_CHANNEL != FSL_FEATURE_DMAMUX_MODULE_CHANNEL
    RTE_USART8_DMAMUX_TX_CH,       RTE_USART8_DMAMUX_RX_CH
#endif
};

static lpuart_dma_handle_t LPUART8_DmaHandle;
static dma_handle_t LPUART8_DmaRxHandle;
static dma_handle_t LPUART8_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart5_dma_driver_state")
static cmsis_lpuart_dma_driver_state_t LPUART8_DmaDriverState = {
#else
static cmsis_lpuart_dma_driver_state_t LPUART8_DmaDriverState = {
#endif
    &LPUART8_Resource, &LPUART8_DmaResource, &LPUART8_DmaHandle, &LPUART8_DmaRxHandle, &LPUART8_DmaTxHandle,
};

static int32_t LPUART8_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART8_PIN_INIT
    RTE_USART8_PIN_INIT();
#endif
    return LPUART_DmaInitialize(cb_event, &LPUART8_DmaDriverState);
}

static int32_t LPUART8_DmaUninitialize(void)
{
#ifdef RTE_USART8_PIN_DEINIT
    RTE_USART8_PIN_DEINIT();
#endif
    return LPUART_DmaUninitialize(&LPUART8_DmaDriverState);
}

static int32_t LPUART8_DmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_DmaPowerControl(state, &LPUART8_DmaDriverState);
}

static int32_t LPUART8_DmaSend(const void *data, uint32_t num)
{
    return LPUART_DmaSend(data, num, &LPUART8_DmaDriverState);
}

static int32_t LPUART8_DmaReceive(void *data, uint32_t num)
{
    return LPUART_DmaReceive(data, num, &LPUART8_DmaDriverState);
}

static int32_t LPUART8_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_DmaTransfer(data_out, data_in, num, &LPUART8_DmaDriverState);
}

static uint32_t LPUART8_DmaGetTxCount(void)
{
    return LPUART_DmaGetTxCount(&LPUART8_DmaDriverState);
}

static uint32_t LPUART8_DmaGetRxCount(void)
{
    return LPUART_DmaGetRxCount(&LPUART8_DmaDriverState);
}

static int32_t LPUART8_DmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_DmaControl(control, arg, &LPUART8_DmaDriverState);
}

static ARM_USART_STATUS LPUART8_DmaGetStatus(void)
{
    return LPUART_DmaGetStatus(&LPUART8_DmaDriverState);
}

/* LPUART8 Driver Control Block */

#endif

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)

static cmsis_lpuart_edma_resource_t LPUART8_EdmaResource = {
    RTE_USART8_DMA_TX_DMA_BASE,    RTE_USART8_DMA_TX_CH,          RTE_USART8_DMA_TX_PERI_SEL,
    RTE_USART8_DMA_RX_DMA_BASE,    RTE_USART8_DMA_RX_CH,          RTE_USART8_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART8_DMA_TX_DMAMUX_BASE, RTE_USART8_DMA_RX_DMAMUX_BASE,
#endif
};

static lpuart_edma_handle_t LPUART8_EdmaHandle;
static edma_handle_t LPUART8_EdmaRxHandle;
static edma_handle_t LPUART8_EdmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart8_edma_driver_state")
static cmsis_lpuart_edma_driver_state_t LPUART8_EdmaDriverState = {
#else
static cmsis_lpuart_edma_driver_state_t LPUART8_EdmaDriverState = {
#endif
    &LPUART8_Resource, &LPUART8_EdmaResource, &LPUART8_EdmaHandle, &LPUART8_EdmaRxHandle, &LPUART8_EdmaTxHandle,
};

static int32_t LPUART8_EdmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART8_PIN_INIT
    RTE_USART8_PIN_INIT();
#endif
    return LPUART_EdmaInitialize(cb_event, &LPUART8_EdmaDriverState);
}

static int32_t LPUART8_EdmaUninitialize(void)
{
#ifdef RTE_USART8_PIN_DEINIT
    RTE_USART8_PIN_DEINIT();
#endif
    return LPUART_EdmaUninitialize(&LPUART8_EdmaDriverState);
}

static int32_t LPUART8_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_EdmaPowerControl(state, &LPUART8_EdmaDriverState);
}

static int32_t LPUART8_EdmaSend(const void *data, uint32_t num)
{
    return LPUART_EdmaSend(data, num, &LPUART8_EdmaDriverState);
}

static int32_t LPUART8_EdmaReceive(void *data, uint32_t num)
{
    return LPUART_EdmaReceive(data, num, &LPUART8_EdmaDriverState);
}

static int32_t LPUART8_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_EdmaTransfer(data_out, data_in, num, &LPUART8_EdmaDriverState);
}

static uint32_t LPUART8_EdmaGetTxCount(void)
{
    return LPUART_EdmaGetTxCount(&LPUART8_EdmaDriverState);
}

static uint32_t LPUART8_EdmaGetRxCount(void)
{
    return LPUART_EdmaGetRxCount(&LPUART8_EdmaDriverState);
}

static int32_t LPUART8_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_EdmaControl(control, arg, &LPUART8_EdmaDriverState);
}

static ARM_USART_STATUS LPUART8_EdmaGetStatus(void)
{
    return LPUART_EdmaGetStatus(&LPUART8_EdmaDriverState);
}

#endif

#else

static lpuart_handle_t LPUART8_Handle;

#if defined(USART8_RX_BUFFER_ENABLE) && (USART8_RX_BUFFER_ENABLE == 1)
static uint8_t lpuart8_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart8_non_blocking_driver_state")
static cmsis_lpuart_non_blocking_driver_state_t LPUART8_NonBlockingDriverState = {
#else
static cmsis_lpuart_non_blocking_driver_state_t LPUART8_NonBlockingDriverState  = {
#endif
    &LPUART8_Resource,
    &LPUART8_Handle,
};

static int32_t LPUART8_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART8_PIN_INIT
    RTE_USART8_PIN_INIT();
#endif
    return LPUART_NonBlockingInitialize(cb_event, &LPUART8_NonBlockingDriverState);
}

static int32_t LPUART8_NonBlockingUninitialize(void)
{
#ifdef RTE_USART8_PIN_DEINIT
    RTE_USART8_PIN_DEINIT();
#endif
    return LPUART_NonBlockingUninitialize(&LPUART8_NonBlockingDriverState);
}

static int32_t LPUART8_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    int32_t result;

    result = LPUART_NonBlockingPowerControl(state, &LPUART8_NonBlockingDriverState);

#if defined(USART8_RX_BUFFER_ENABLE) && (USART8_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (LPUART8_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        LPUART_TransferStartRingBuffer(LPUART8_NonBlockingDriverState.resource->base,
                                       LPUART8_NonBlockingDriverState.handle, lpuart8_rxRingBuffer,
                                       USART_RX_BUFFER_LEN);
    }
#endif

    return result;
}

static int32_t LPUART8_NonBlockingSend(const void *data, uint32_t num)
{
    return LPUART_NonBlockingSend(data, num, &LPUART8_NonBlockingDriverState);
}

static int32_t LPUART8_NonBlockingReceive(void *data, uint32_t num)
{
    return LPUART_NonBlockingReceive(data, num, &LPUART8_NonBlockingDriverState);
}

static int32_t LPUART8_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_NonBlockingTransfer(data_out, data_in, num, &LPUART8_NonBlockingDriverState);
}

static uint32_t LPUART8_NonBlockingGetTxCount(void)
{
    return LPUART_NonBlockingGetTxCount(&LPUART8_NonBlockingDriverState);
}

static uint32_t LPUART8_NonBlockingGetRxCount(void)
{
    return LPUART_NonBlockingGetRxCount(&LPUART8_NonBlockingDriverState);
}

static int32_t LPUART8_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = LPUART_NonBlockingControl(control, arg, &LPUART8_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }

    /* Enable the receive interrupts if ring buffer is used */
    if (LPUART8_NonBlockingDriverState.handle->rxRingBuffer != NULL)
    {
        LPUART_EnableInterrupts(
            LPUART8_NonBlockingDriverState.resource->base,
            (uint32_t)kLPUART_RxDataRegFullInterruptEnable | (uint32_t)kLPUART_RxOverrunInterruptEnable);
    }

    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS LPUART8_NonBlockingGetStatus(void)
{
    return LPUART_NonBlockingGetStatus(&LPUART8_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART8 = {LPUARTx_GetVersion,      LPUARTx_GetCapabilities,
#if defined(RTE_USART8_DMA_EN) && RTE_USART8_DMA_EN
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
                                  LPUART8_EdmaInitialize,  LPUART8_EdmaUninitialize, LPUART8_EdmaPowerControl,
                                  LPUART8_EdmaSend,        LPUART8_EdmaReceive,      LPUART8_EdmaTransfer,
                                  LPUART8_EdmaGetTxCount,  LPUART8_EdmaGetRxCount,   LPUART8_EdmaControl,
                                  LPUART8_EdmaGetStatus,
#else
                                  LPUART8_DmaInitialize,   LPUART8_DmaUninitialize, LPUART8_DmaPowerControl,
                                  LPUART8_DmaSend,         LPUART8_DmaReceive,      LPUART8_DmaTransfer,
                                  LPUART8_DmaGetTxCount,   LPUART8_DmaGetRxCount,   LPUART8_DmaControl,
                                  LPUART8_DmaGetStatus,
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */
#else
                                  LPUART8_NonBlockingInitialize,
                                  LPUART8_NonBlockingUninitialize,
                                  LPUART8_NonBlockingPowerControl,
                                  LPUART8_NonBlockingSend,
                                  LPUART8_NonBlockingReceive,
                                  LPUART8_NonBlockingTransfer,
                                  LPUART8_NonBlockingGetTxCount,
                                  LPUART8_NonBlockingGetRxCount,
                                  LPUART8_NonBlockingControl,
                                  LPUART8_NonBlockingGetStatus,
#endif /* RTE_USART8_DMA_EN */
                                  LPUARTx_SetModemControl, LPUARTx_GetModemStatus};

#endif /* LPUART8 */

#if defined(LPUART9) && defined(RTE_USART9) && RTE_USART9

/* User needs to provide the implementation for LPUART5_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPUART9_GetFreq(void);

static cmsis_lpuart_resource_t LPUART9_Resource = {LPUART9, LPUART9_GetFreq};

#if defined(RTE_USART9_DMA_EN) && RTE_USART9_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_lpuart_dma_resource_t LPUART9_DmaResource = {
    RTE_USART9_DMA_TX_DMA_BASE,    RTE_USART9_DMA_TX_CH,          RTE_USART9_DMA_TX_PERI_SEL,
    RTE_USART9_DMA_RX_DMA_BASE,    RTE_USART9_DMA_RX_CH,          RTE_USART9_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART9_DMA_TX_DMAMUX_BASE, RTE_USART9_DMA_RX_DMAMUX_BASE,
#endif
#if FSL_FEATURE_DMA_MODULE_CHANNEL != FSL_FEATURE_DMAMUX_MODULE_CHANNEL
    RTE_USART9_DMAMUX_TX_CH,       RTE_USART9_DMAMUX_RX_CH
#endif
};

static lpuart_dma_handle_t LPUART9_DmaHandle;
static dma_handle_t LPUART9_DmaRxHandle;
static dma_handle_t LPUART9_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart5_dma_driver_state")
static cmsis_lpuart_dma_driver_state_t LPUART9_DmaDriverState = {
#else
static cmsis_lpuart_dma_driver_state_t LPUART9_DmaDriverState = {
#endif
    &LPUART9_Resource, &LPUART9_DmaResource, &LPUART9_DmaHandle, &LPUART9_DmaRxHandle, &LPUART9_DmaTxHandle,
};

static int32_t LPUART9_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART9_PIN_INIT
    RTE_USART9_PIN_INIT();
#endif
    return LPUART_DmaInitialize(cb_event, &LPUART9_DmaDriverState);
}

static int32_t LPUART9_DmaUninitialize(void)
{
#ifdef RTE_USART9_PIN_DEINIT
    RTE_USART9_PIN_DEINIT();
#endif
    return LPUART_DmaUninitialize(&LPUART9_DmaDriverState);
}

static int32_t LPUART9_DmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_DmaPowerControl(state, &LPUART9_DmaDriverState);
}

static int32_t LPUART9_DmaSend(const void *data, uint32_t num)
{
    return LPUART_DmaSend(data, num, &LPUART9_DmaDriverState);
}

static int32_t LPUART9_DmaReceive(void *data, uint32_t num)
{
    return LPUART_DmaReceive(data, num, &LPUART9_DmaDriverState);
}

static int32_t LPUART9_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_DmaTransfer(data_out, data_in, num, &LPUART9_DmaDriverState);
}

static uint32_t LPUART9_DmaGetTxCount(void)
{
    return LPUART_DmaGetTxCount(&LPUART9_DmaDriverState);
}

static uint32_t LPUART9_DmaGetRxCount(void)
{
    return LPUART_DmaGetRxCount(&LPUART9_DmaDriverState);
}

static int32_t LPUART9_DmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_DmaControl(control, arg, &LPUART9_DmaDriverState);
}

static ARM_USART_STATUS LPUART9_DmaGetStatus(void)
{
    return LPUART_DmaGetStatus(&LPUART9_DmaDriverState);
}

/* LPUART9 Driver Control Block */

#endif

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)

static cmsis_lpuart_edma_resource_t LPUART9_EdmaResource = {
    RTE_USART9_DMA_TX_DMA_BASE,    RTE_USART9_DMA_TX_CH,          RTE_USART9_DMA_TX_PERI_SEL,
    RTE_USART9_DMA_RX_DMA_BASE,    RTE_USART9_DMA_RX_CH,          RTE_USART9_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART9_DMA_TX_DMAMUX_BASE, RTE_USART9_DMA_RX_DMAMUX_BASE,
#endif
};

static lpuart_edma_handle_t LPUART9_EdmaHandle;
static edma_handle_t LPUART9_EdmaRxHandle;
static edma_handle_t LPUART9_EdmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart9_edma_driver_state")
static cmsis_lpuart_edma_driver_state_t LPUART9_EdmaDriverState = {
#else
static cmsis_lpuart_edma_driver_state_t LPUART9_EdmaDriverState = {
#endif
    &LPUART9_Resource, &LPUART9_EdmaResource, &LPUART9_EdmaHandle, &LPUART9_EdmaRxHandle, &LPUART9_EdmaTxHandle,
};

static int32_t LPUART9_EdmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART9_PIN_INIT
    RTE_USART9_PIN_INIT();
#endif
    return LPUART_EdmaInitialize(cb_event, &LPUART9_EdmaDriverState);
}

static int32_t LPUART9_EdmaUninitialize(void)
{
#ifdef RTE_USART9_PIN_DEINIT
    RTE_USART9_PIN_DEINIT();
#endif
    return LPUART_EdmaUninitialize(&LPUART9_EdmaDriverState);
}

static int32_t LPUART9_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_EdmaPowerControl(state, &LPUART9_EdmaDriverState);
}

static int32_t LPUART9_EdmaSend(const void *data, uint32_t num)
{
    return LPUART_EdmaSend(data, num, &LPUART9_EdmaDriverState);
}

static int32_t LPUART9_EdmaReceive(void *data, uint32_t num)
{
    return LPUART_EdmaReceive(data, num, &LPUART9_EdmaDriverState);
}

static int32_t LPUART9_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_EdmaTransfer(data_out, data_in, num, &LPUART9_EdmaDriverState);
}

static uint32_t LPUART9_EdmaGetTxCount(void)
{
    return LPUART_EdmaGetTxCount(&LPUART9_EdmaDriverState);
}

static uint32_t LPUART9_EdmaGetRxCount(void)
{
    return LPUART_EdmaGetRxCount(&LPUART9_EdmaDriverState);
}

static int32_t LPUART9_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_EdmaControl(control, arg, &LPUART9_EdmaDriverState);
}

static ARM_USART_STATUS LPUART9_EdmaGetStatus(void)
{
    return LPUART_EdmaGetStatus(&LPUART9_EdmaDriverState);
}

#endif

#else

static lpuart_handle_t LPUART9_Handle;

#if defined(USART9_RX_BUFFER_ENABLE) && (USART9_RX_BUFFER_ENABLE == 1)
static uint9_t lpuart9_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart9_non_blocking_driver_state")
static cmsis_lpuart_non_blocking_driver_state_t LPUART9_NonBlockingDriverState = {
#else
static cmsis_lpuart_non_blocking_driver_state_t LPUART9_NonBlockingDriverState  = {
#endif
    &LPUART9_Resource,
    &LPUART9_Handle,
};

static int32_t LPUART9_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART9_PIN_INIT
    RTE_USART9_PIN_INIT();
#endif
    return LPUART_NonBlockingInitialize(cb_event, &LPUART9_NonBlockingDriverState);
}

static int32_t LPUART9_NonBlockingUninitialize(void)
{
#ifdef RTE_USART9_PIN_DEINIT
    RTE_USART9_PIN_DEINIT();
#endif
    return LPUART_NonBlockingUninitialize(&LPUART9_NonBlockingDriverState);
}

static int32_t LPUART9_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    int32_t result;

    result = LPUART_NonBlockingPowerControl(state, &LPUART9_NonBlockingDriverState);

#if defined(USART9_RX_BUFFER_ENABLE) && (USART9_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (LPUART9_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        LPUART_TransferStartRingBuffer(LPUART9_NonBlockingDriverState.resource->base,
                                       LPUART9_NonBlockingDriverState.handle, lpuart9_rxRingBuffer,
                                       USART_RX_BUFFER_LEN);
    }
#endif

    return result;
}

static int32_t LPUART9_NonBlockingSend(const void *data, uint32_t num)
{
    return LPUART_NonBlockingSend(data, num, &LPUART9_NonBlockingDriverState);
}

static int32_t LPUART9_NonBlockingReceive(void *data, uint32_t num)
{
    return LPUART_NonBlockingReceive(data, num, &LPUART9_NonBlockingDriverState);
}

static int32_t LPUART9_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_NonBlockingTransfer(data_out, data_in, num, &LPUART9_NonBlockingDriverState);
}

static uint32_t LPUART9_NonBlockingGetTxCount(void)
{
    return LPUART_NonBlockingGetTxCount(&LPUART9_NonBlockingDriverState);
}

static uint32_t LPUART9_NonBlockingGetRxCount(void)
{
    return LPUART_NonBlockingGetRxCount(&LPUART9_NonBlockingDriverState);
}

static int32_t LPUART9_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = LPUART_NonBlockingControl(control, arg, &LPUART9_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }

    /* Enable the receive interrupts if ring buffer is used */
    if (LPUART9_NonBlockingDriverState.handle->rxRingBuffer != NULL)
    {
        LPUART_EnableInterrupts(
            LPUART9_NonBlockingDriverState.resource->base,
            (uint32_t)kLPUART_RxDataRegFullInterruptEnable | (uint32_t)kLPUART_RxOverrunInterruptEnable);
    }

    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS LPUART9_NonBlockingGetStatus(void)
{
    return LPUART_NonBlockingGetStatus(&LPUART9_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART9 = {LPUARTx_GetVersion,      LPUARTx_GetCapabilities,
#if defined(RTE_USART9_DMA_EN) && RTE_USART9_DMA_EN
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
                                  LPUART9_EdmaInitialize,  LPUART9_EdmaUninitialize, LPUART9_EdmaPowerControl,
                                  LPUART9_EdmaSend,        LPUART9_EdmaReceive,      LPUART9_EdmaTransfer,
                                  LPUART9_EdmaGetTxCount,  LPUART9_EdmaGetRxCount,   LPUART9_EdmaControl,
                                  LPUART9_EdmaGetStatus,
#else
                                  LPUART9_DmaInitialize,   LPUART9_DmaUninitialize, LPUART9_DmaPowerControl,
                                  LPUART9_DmaSend,         LPUART9_DmaReceive,      LPUART9_DmaTransfer,
                                  LPUART9_DmaGetTxCount,   LPUART9_DmaGetRxCount,   LPUART9_DmaControl,
                                  LPUART9_DmaGetStatus,
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */
#else
                                  LPUART9_NonBlockingInitialize,
                                  LPUART9_NonBlockingUninitialize,
                                  LPUART9_NonBlockingPowerControl,
                                  LPUART9_NonBlockingSend,
                                  LPUART9_NonBlockingReceive,
                                  LPUART9_NonBlockingTransfer,
                                  LPUART9_NonBlockingGetTxCount,
                                  LPUART9_NonBlockingGetRxCount,
                                  LPUART9_NonBlockingControl,
                                  LPUART9_NonBlockingGetStatus,
#endif /* RTE_USART9_DMA_EN */
                                  LPUARTx_SetModemControl, LPUARTx_GetModemStatus};

#endif /* LPUART9 */

#if defined(LPUART10) && defined(RTE_USART10) && RTE_USART10

/* User needs to provide the implementation for LPUART5_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPUART10_GetFreq(void);

static cmsis_lpuart_resource_t LPUART10_Resource = {LPUART10, LPUART10_GetFreq};

#if defined(RTE_USART10_DMA_EN) && RTE_USART10_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_lpuart_dma_resource_t LPUART10_DmaResource = {
    RTE_USART10_DMA_TX_DMA_BASE,    RTE_USART10_DMA_TX_CH,          RTE_USART10_DMA_TX_PERI_SEL,
    RTE_USART10_DMA_RX_DMA_BASE,    RTE_USART10_DMA_RX_CH,          RTE_USART10_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART10_DMA_TX_DMAMUX_BASE, RTE_USART10_DMA_RX_DMAMUX_BASE,
#endif
#if FSL_FEATURE_DMA_MODULE_CHANNEL != FSL_FEATURE_DMAMUX_MODULE_CHANNEL
    RTE_USART10_DMAMUX_TX_CH,       RTE_USART10_DMAMUX_RX_CH
#endif
};

static lpuart_dma_handle_t LPUART10_DmaHandle;
static dma_handle_t LPUART10_DmaRxHandle;
static dma_handle_t LPUART10_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart5_dma_driver_state")
static cmsis_lpuart_dma_driver_state_t LPUART10_DmaDriverState = {
#else
static cmsis_lpuart_dma_driver_state_t LPUART10_DmaDriverState = {
#endif
    &LPUART10_Resource, &LPUART10_DmaResource, &LPUART10_DmaHandle, &LPUART10_DmaRxHandle, &LPUART10_DmaTxHandle,
};

static int32_t LPUART10_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART10_PIN_INIT
    RTE_USART10_PIN_INIT();
#endif
    return LPUART_DmaInitialize(cb_event, &LPUART10_DmaDriverState);
}

static int32_t LPUART10_DmaUninitialize(void)
{
#ifdef RTE_USART10_PIN_DEINIT
    RTE_USART10_PIN_DEINIT();
#endif
    return LPUART_DmaUninitialize(&LPUART10_DmaDriverState);
}

static int32_t LPUART10_DmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_DmaPowerControl(state, &LPUART10_DmaDriverState);
}

static int32_t LPUART10_DmaSend(const void *data, uint32_t num)
{
    return LPUART_DmaSend(data, num, &LPUART10_DmaDriverState);
}

static int32_t LPUART10_DmaReceive(void *data, uint32_t num)
{
    return LPUART_DmaReceive(data, num, &LPUART10_DmaDriverState);
}

static int32_t LPUART10_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_DmaTransfer(data_out, data_in, num, &LPUART10_DmaDriverState);
}

static uint32_t LPUART10_DmaGetTxCount(void)
{
    return LPUART_DmaGetTxCount(&LPUART10_DmaDriverState);
}

static uint32_t LPUART10_DmaGetRxCount(void)
{
    return LPUART_DmaGetRxCount(&LPUART10_DmaDriverState);
}

static int32_t LPUART10_DmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_DmaControl(control, arg, &LPUART10_DmaDriverState);
}

static ARM_USART_STATUS LPUART10_DmaGetStatus(void)
{
    return LPUART_DmaGetStatus(&LPUART10_DmaDriverState);
}

/* LPUART10 Driver Control Block */

#endif

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)

static cmsis_lpuart_edma_resource_t LPUART10_EdmaResource = {
    RTE_USART10_DMA_TX_DMA_BASE,    RTE_USART10_DMA_TX_CH,          RTE_USART10_DMA_TX_PERI_SEL,
    RTE_USART10_DMA_RX_DMA_BASE,    RTE_USART10_DMA_RX_CH,          RTE_USART10_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART10_DMA_TX_DMAMUX_BASE, RTE_USART10_DMA_RX_DMAMUX_BASE,
#endif
};

static lpuart_edma_handle_t LPUART10_EdmaHandle;
static edma_handle_t LPUART10_EdmaRxHandle;
static edma_handle_t LPUART10_EdmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart10_edma_driver_state")
static cmsis_lpuart_edma_driver_state_t LPUART10_EdmaDriverState = {
#else
static cmsis_lpuart_edma_driver_state_t LPUART10_EdmaDriverState = {
#endif
    &LPUART10_Resource, &LPUART10_EdmaResource, &LPUART10_EdmaHandle, &LPUART10_EdmaRxHandle, &LPUART10_EdmaTxHandle,
};

static int32_t LPUART10_EdmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART10_PIN_INIT
    RTE_USART10_PIN_INIT();
#endif
    return LPUART_EdmaInitialize(cb_event, &LPUART10_EdmaDriverState);
}

static int32_t LPUART10_EdmaUninitialize(void)
{
#ifdef RTE_USART10_PIN_DEINIT
    RTE_USART10_PIN_DEINIT();
#endif
    return LPUART_EdmaUninitialize(&LPUART10_EdmaDriverState);
}

static int32_t LPUART10_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_EdmaPowerControl(state, &LPUART10_EdmaDriverState);
}

static int32_t LPUART10_EdmaSend(const void *data, uint32_t num)
{
    return LPUART_EdmaSend(data, num, &LPUART10_EdmaDriverState);
}

static int32_t LPUART10_EdmaReceive(void *data, uint32_t num)
{
    return LPUART_EdmaReceive(data, num, &LPUART10_EdmaDriverState);
}

static int32_t LPUART10_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_EdmaTransfer(data_out, data_in, num, &LPUART10_EdmaDriverState);
}

static uint32_t LPUART10_EdmaGetTxCount(void)
{
    return LPUART_EdmaGetTxCount(&LPUART10_EdmaDriverState);
}

static uint32_t LPUART10_EdmaGetRxCount(void)
{
    return LPUART_EdmaGetRxCount(&LPUART10_EdmaDriverState);
}

static int32_t LPUART10_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_EdmaControl(control, arg, &LPUART10_EdmaDriverState);
}

static ARM_USART_STATUS LPUART10_EdmaGetStatus(void)
{
    return LPUART_EdmaGetStatus(&LPUART10_EdmaDriverState);
}

#endif

#else

static lpuart_handle_t LPUART10_Handle;

#if defined(USART10_RX_BUFFER_ENABLE) && (USART10_RX_BUFFER_ENABLE == 1)
static uint10_t lpuart10_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart10_non_blocking_driver_state")
static cmsis_lpuart_non_blocking_driver_state_t LPUART10_NonBlockingDriverState = {
#else
static cmsis_lpuart_non_blocking_driver_state_t LPUART10_NonBlockingDriverState = {
#endif
    &LPUART10_Resource,
    &LPUART10_Handle,
};

static int32_t LPUART10_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART10_PIN_INIT
    RTE_USART10_PIN_INIT();
#endif
    return LPUART_NonBlockingInitialize(cb_event, &LPUART10_NonBlockingDriverState);
}

static int32_t LPUART10_NonBlockingUninitialize(void)
{
#ifdef RTE_USART10_PIN_DEINIT
    RTE_USART10_PIN_DEINIT();
#endif
    return LPUART_NonBlockingUninitialize(&LPUART10_NonBlockingDriverState);
}

static int32_t LPUART10_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    int32_t result;

    result = LPUART_NonBlockingPowerControl(state, &LPUART10_NonBlockingDriverState);

#if defined(USART10_RX_BUFFER_ENABLE) && (USART10_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (LPUART10_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        LPUART_TransferStartRingBuffer(LPUART10_NonBlockingDriverState.resource->base,
                                       LPUART10_NonBlockingDriverState.handle, lpuart10_rxRingBuffer,
                                       USART_RX_BUFFER_LEN);
    }
#endif

    return result;
}

static int32_t LPUART10_NonBlockingSend(const void *data, uint32_t num)
{
    return LPUART_NonBlockingSend(data, num, &LPUART10_NonBlockingDriverState);
}

static int32_t LPUART10_NonBlockingReceive(void *data, uint32_t num)
{
    return LPUART_NonBlockingReceive(data, num, &LPUART10_NonBlockingDriverState);
}

static int32_t LPUART10_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_NonBlockingTransfer(data_out, data_in, num, &LPUART10_NonBlockingDriverState);
}

static uint32_t LPUART10_NonBlockingGetTxCount(void)
{
    return LPUART_NonBlockingGetTxCount(&LPUART10_NonBlockingDriverState);
}

static uint32_t LPUART10_NonBlockingGetRxCount(void)
{
    return LPUART_NonBlockingGetRxCount(&LPUART10_NonBlockingDriverState);
}

static int32_t LPUART10_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = LPUART_NonBlockingControl(control, arg, &LPUART10_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }

    /* Enable the receive interrupts if ring buffer is used */
    if (LPUART10_NonBlockingDriverState.handle->rxRingBuffer != NULL)
    {
        LPUART_EnableInterrupts(
            LPUART10_NonBlockingDriverState.resource->base,
            (uint32_t)kLPUART_RxDataRegFullInterruptEnable | (uint32_t)kLPUART_RxOverrunInterruptEnable);
    }

    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS LPUART10_NonBlockingGetStatus(void)
{
    return LPUART_NonBlockingGetStatus(&LPUART10_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART10 = {LPUARTx_GetVersion,      LPUARTx_GetCapabilities,
#if defined(RTE_USART10_DMA_EN) && RTE_USART10_DMA_EN
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
                                   LPUART10_EdmaInitialize, LPUART10_EdmaUninitialize, LPUART10_EdmaPowerControl,
                                   LPUART10_EdmaSend,       LPUART10_EdmaReceive,      LPUART10_EdmaTransfer,
                                   LPUART10_EdmaGetTxCount, LPUART10_EdmaGetRxCount,   LPUART10_EdmaControl,
                                   LPUART10_EdmaGetStatus,
#else
                                   LPUART10_DmaInitialize,  LPUART10_DmaUninitialize, LPUART10_DmaPowerControl,
                                   LPUART10_DmaSend,        LPUART10_DmaReceive,      LPUART10_DmaTransfer,
                                   LPUART10_DmaGetTxCount,  LPUART10_DmaGetRxCount,   LPUART10_DmaControl,
                                   LPUART10_DmaGetStatus,
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */
#else
                                  LPUART10_NonBlockingInitialize,
                                  LPUART10_NonBlockingUninitialize,
                                  LPUART10_NonBlockingPowerControl,
                                  LPUART10_NonBlockingSend,
                                  LPUART10_NonBlockingReceive,
                                  LPUART10_NonBlockingTransfer,
                                  LPUART10_NonBlockingGetTxCount,
                                  LPUART10_NonBlockingGetRxCount,
                                  LPUART10_NonBlockingControl,
                                  LPUART10_NonBlockingGetStatus,
#endif /* RTE_USART10_DMA_EN */
                                   LPUARTx_SetModemControl, LPUARTx_GetModemStatus};

#endif /* LPUART10 */

#if defined(LPUART11) && defined(RTE_USART11) && RTE_USART11

/* User needs to provide the implementation for LPUART5_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPUART11_GetFreq(void);

static cmsis_lpuart_resource_t LPUART11_Resource = {LPUART11, LPUART11_GetFreq};

#if defined(RTE_USART11_DMA_EN) && RTE_USART11_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_lpuart_dma_resource_t LPUART11_DmaResource = {
    RTE_USART11_DMA_TX_DMA_BASE,    RTE_USART11_DMA_TX_CH,          RTE_USART11_DMA_TX_PERI_SEL,
    RTE_USART11_DMA_RX_DMA_BASE,    RTE_USART11_DMA_RX_CH,          RTE_USART11_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART11_DMA_TX_DMAMUX_BASE, RTE_USART11_DMA_RX_DMAMUX_BASE,
#endif
#if FSL_FEATURE_DMA_MODULE_CHANNEL != FSL_FEATURE_DMAMUX_MODULE_CHANNEL
    RTE_USART11_DMAMUX_TX_CH,       RTE_USART101_DMAMUX_RX_CH
#endif
};

static lpuart_dma_handle_t LPUART11_DmaHandle;
static dma_handle_t LPUART11_DmaRxHandle;
static dma_handle_t LPUART11_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart5_dma_driver_state")
static cmsis_lpuart_dma_driver_state_t LPUART11_DmaDriverState = {
#else
static cmsis_lpuart_dma_driver_state_t LPUART11_DmaDriverState = {
#endif
    &LPUART11_Resource, &LPUART11_DmaResource, &LPUART11_DmaHandle, &LPUART11_DmaRxHandle, &LPUART11_DmaTxHandle,
};

static int32_t LPUART11_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART11_PIN_INIT
    RTE_USART11_PIN_INIT();
#endif
    return LPUART_DmaInitialize(cb_event, &LPUART11_DmaDriverState);
}

static int32_t LPUART11_DmaUninitialize(void)
{
#ifdef RTE_USART11_PIN_DEINIT
    RTE_USART11_PIN_DEINIT();
#endif
    return LPUART_DmaUninitialize(&LPUART11_DmaDriverState);
}

static int32_t LPUART11_DmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_DmaPowerControl(state, &LPUART11_DmaDriverState);
}

static int32_t LPUART11_DmaSend(const void *data, uint32_t num)
{
    return LPUART_DmaSend(data, num, &LPUART11_DmaDriverState);
}

static int32_t LPUART11_DmaReceive(void *data, uint32_t num)
{
    return LPUART_DmaReceive(data, num, &LPUART11_DmaDriverState);
}

static int32_t LPUART11_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_DmaTransfer(data_out, data_in, num, &LPUART11_DmaDriverState);
}

static uint32_t LPUART11_DmaGetTxCount(void)
{
    return LPUART_DmaGetTxCount(&LPUART11_DmaDriverState);
}

static uint32_t LPUART11_DmaGetRxCount(void)
{
    return LPUART_DmaGetRxCount(&LPUART11_DmaDriverState);
}

static int32_t LPUART11_DmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_DmaControl(control, arg, &LPUART11_DmaDriverState);
}

static ARM_USART_STATUS LPUART11_DmaGetStatus(void)
{
    return LPUART_DmaGetStatus(&LPUART11_DmaDriverState);
}

/* LPUART11 Driver Control Block */

#endif

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)

static cmsis_lpuart_edma_resource_t LPUART11_EdmaResource = {
    RTE_USART11_DMA_TX_DMA_BASE,    RTE_USART11_DMA_TX_CH,          RTE_USART11_DMA_TX_PERI_SEL,
    RTE_USART11_DMA_RX_DMA_BASE,    RTE_USART11_DMA_RX_CH,          RTE_USART11_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART11_DMA_TX_DMAMUX_BASE, RTE_USART11_DMA_RX_DMAMUX_BASE,
#endif
};

static lpuart_edma_handle_t LPUART11_EdmaHandle;
static edma_handle_t LPUART11_EdmaRxHandle;
static edma_handle_t LPUART11_EdmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart11_edma_driver_state")
static cmsis_lpuart_edma_driver_state_t LPUART11_EdmaDriverState = {
#else
static cmsis_lpuart_edma_driver_state_t LPUART11_EdmaDriverState = {
#endif
    &LPUART11_Resource, &LPUART11_EdmaResource, &LPUART11_EdmaHandle, &LPUART11_EdmaRxHandle, &LPUART11_EdmaTxHandle,
};

static int32_t LPUART11_EdmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART11_PIN_INIT
    RTE_USART11_PIN_INIT();
#endif
    return LPUART_EdmaInitialize(cb_event, &LPUART11_EdmaDriverState);
}

static int32_t LPUART11_EdmaUninitialize(void)
{
#ifdef RTE_USART11_PIN_DEINIT
    RTE_USART11_PIN_DEINIT();
#endif
    return LPUART_EdmaUninitialize(&LPUART11_EdmaDriverState);
}

static int32_t LPUART11_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_EdmaPowerControl(state, &LPUART11_EdmaDriverState);
}

static int32_t LPUART11_EdmaSend(const void *data, uint32_t num)
{
    return LPUART_EdmaSend(data, num, &LPUART11_EdmaDriverState);
}

static int32_t LPUART11_EdmaReceive(void *data, uint32_t num)
{
    return LPUART_EdmaReceive(data, num, &LPUART11_EdmaDriverState);
}

static int32_t LPUART11_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_EdmaTransfer(data_out, data_in, num, &LPUART11_EdmaDriverState);
}

static uint32_t LPUART11_EdmaGetTxCount(void)
{
    return LPUART_EdmaGetTxCount(&LPUART11_EdmaDriverState);
}

static uint32_t LPUART11_EdmaGetRxCount(void)
{
    return LPUART_EdmaGetRxCount(&LPUART11_EdmaDriverState);
}

static int32_t LPUART11_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_EdmaControl(control, arg, &LPUART11_EdmaDriverState);
}

static ARM_USART_STATUS LPUART11_EdmaGetStatus(void)
{
    return LPUART_EdmaGetStatus(&LPUART11_EdmaDriverState);
}

#endif

#else

static lpuart_handle_t LPUART11_Handle;

#if defined(USART11_RX_BUFFER_ENABLE) && (USART11_RX_BUFFER_ENABLE == 1)
static uint11_t lpuart11_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart11_non_blocking_driver_state")
static cmsis_lpuart_non_blocking_driver_state_t LPUART11_NonBlockingDriverState = {
#else
static cmsis_lpuart_non_blocking_driver_state_t LPUART11_NonBlockingDriverState = {
#endif
    &LPUART11_Resource,
    &LPUART11_Handle,
};

static int32_t LPUART11_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART11_PIN_INIT
    RTE_USART11_PIN_INIT();
#endif
    return LPUART_NonBlockingInitialize(cb_event, &LPUART11_NonBlockingDriverState);
}

static int32_t LPUART11_NonBlockingUninitialize(void)
{
#ifdef RTE_USART11_PIN_DEINIT
    RTE_USART11_PIN_DEINIT();
#endif
    return LPUART_NonBlockingUninitialize(&LPUART11_NonBlockingDriverState);
}

static int32_t LPUART11_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    int32_t result;

    result = LPUART_NonBlockingPowerControl(state, &LPUART11_NonBlockingDriverState);

#if defined(USART11_RX_BUFFER_ENABLE) && (USART11_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (LPUART11_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        LPUART_TransferStartRingBuffer(LPUART11_NonBlockingDriverState.resource->base,
                                       LPUART11_NonBlockingDriverState.handle, lpuart11_rxRingBuffer,
                                       USART_RX_BUFFER_LEN);
    }
#endif

    return result;
}

static int32_t LPUART11_NonBlockingSend(const void *data, uint32_t num)
{
    return LPUART_NonBlockingSend(data, num, &LPUART11_NonBlockingDriverState);
}

static int32_t LPUART11_NonBlockingReceive(void *data, uint32_t num)
{
    return LPUART_NonBlockingReceive(data, num, &LPUART11_NonBlockingDriverState);
}

static int32_t LPUART11_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_NonBlockingTransfer(data_out, data_in, num, &LPUART11_NonBlockingDriverState);
}

static uint32_t LPUART11_NonBlockingGetTxCount(void)
{
    return LPUART_NonBlockingGetTxCount(&LPUART11_NonBlockingDriverState);
}

static uint32_t LPUART11_NonBlockingGetRxCount(void)
{
    return LPUART_NonBlockingGetRxCount(&LPUART11_NonBlockingDriverState);
}

static int32_t LPUART11_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = LPUART_NonBlockingControl(control, arg, &LPUART11_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }

    /* Enable the receive interrupts if ring buffer is used */
    if (LPUART11_NonBlockingDriverState.handle->rxRingBuffer != NULL)
    {
        LPUART_EnableInterrupts(
            LPUART11_NonBlockingDriverState.resource->base,
            (uint32_t)kLPUART_RxDataRegFullInterruptEnable | (uint32_t)kLPUART_RxOverrunInterruptEnable);
    }

    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS LPUART11_NonBlockingGetStatus(void)
{
    return LPUART_NonBlockingGetStatus(&LPUART11_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART11 = {LPUARTx_GetVersion,      LPUARTx_GetCapabilities,
#if defined(RTE_USART11_DMA_EN) && RTE_USART11_DMA_EN
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
                                   LPUART11_EdmaInitialize, LPUART11_EdmaUninitialize, LPUART11_EdmaPowerControl,
                                   LPUART11_EdmaSend,       LPUART11_EdmaReceive,      LPUART11_EdmaTransfer,
                                   LPUART11_EdmaGetTxCount, LPUART11_EdmaGetRxCount,   LPUART11_EdmaControl,
                                   LPUART11_EdmaGetStatus,
#else
                                   LPUART11_DmaInitialize,  LPUART11_DmaUninitialize, LPUART11_DmaPowerControl,
                                   LPUART11_DmaSend,        LPUART11_DmaReceive,      LPUART11_DmaTransfer,
                                   LPUART11_DmaGetTxCount,  LPUART11_DmaGetRxCount,   LPUART11_DmaControl,
                                   LPUART11_DmaGetStatus,
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */
#else
                                  LPUART11_NonBlockingInitialize,
                                  LPUART11_NonBlockingUninitialize,
                                  LPUART11_NonBlockingPowerControl,
                                  LPUART11_NonBlockingSend,
                                  LPUART11_NonBlockingReceive,
                                  LPUART11_NonBlockingTransfer,
                                  LPUART11_NonBlockingGetTxCount,
                                  LPUART11_NonBlockingGetRxCount,
                                  LPUART11_NonBlockingControl,
                                  LPUART11_NonBlockingGetStatus,
#endif /* RTE_USART11_DMA_EN */
                                   LPUARTx_SetModemControl, LPUARTx_GetModemStatus};

#endif /* LPUART11 */

#if defined(LPUART12) && defined(RTE_USART12) && RTE_USART12

/* User needs to provide the implementation for LPUART5_GetFreq/InitPins/DeinitPins
in the application for enabling according instance. */
extern uint32_t LPUART12_GetFreq(void);

static cmsis_lpuart_resource_t LPUART12_Resource = {LPUART12, LPUART12_GetFreq};

#if defined(RTE_USART12_DMA_EN) && RTE_USART12_DMA_EN

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

static cmsis_lpuart_dma_resource_t LPUART12_DmaResource = {
    RTE_USART12_DMA_TX_DMA_BASE,    RTE_USART12_DMA_TX_CH,          RTE_USART12_DMA_TX_PERI_SEL,
    RTE_USART12_DMA_RX_DMA_BASE,    RTE_USART12_DMA_RX_CH,          RTE_USART12_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART12_DMA_TX_DMAMUX_BASE, RTE_USART12_DMA_RX_DMAMUX_BASE,
#endif
#if FSL_FEATURE_DMA_MODULE_CHANNEL != FSL_FEATURE_DMAMUX_MODULE_CHANNEL
    RTE_USART12_DMAMUX_TX_CH,       RTE_USART12_DMAMUX_RX_CH
#endif
};

static lpuart_dma_handle_t LPUART12_DmaHandle;
static dma_handle_t LPUART12_DmaRxHandle;
static dma_handle_t LPUART12_DmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart5_dma_driver_state")
static cmsis_lpuart_dma_driver_state_t LPUART12_DmaDriverState = {
#else
static cmsis_lpuart_dma_driver_state_t LPUART12_DmaDriverState = {
#endif
    &LPUART12_Resource, &LPUART12_DmaResource, &LPUART12_DmaHandle, &LPUART12_DmaRxHandle, &LPUART12_DmaTxHandle,
};

static int32_t LPUART12_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART12_PIN_INIT
    RTE_USART12_PIN_INIT();
#endif
    return LPUART_DmaInitialize(cb_event, &LPUART12_DmaDriverState);
}

static int32_t LPUART12_DmaUninitialize(void)
{
#ifdef RTE_USART12_PIN_DEINIT
    RTE_USART12_PIN_DEINIT();
#endif
    return LPUART_DmaUninitialize(&LPUART12_DmaDriverState);
}

static int32_t LPUART12_DmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_DmaPowerControl(state, &LPUART12_DmaDriverState);
}

static int32_t LPUART12_DmaSend(const void *data, uint32_t num)
{
    return LPUART_DmaSend(data, num, &LPUART12_DmaDriverState);
}

static int32_t LPUART12_DmaReceive(void *data, uint32_t num)
{
    return LPUART_DmaReceive(data, num, &LPUART12_DmaDriverState);
}

static int32_t LPUART12_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_DmaTransfer(data_out, data_in, num, &LPUART12_DmaDriverState);
}

static uint32_t LPUART12_DmaGetTxCount(void)
{
    return LPUART_DmaGetTxCount(&LPUART12_DmaDriverState);
}

static uint32_t LPUART12_DmaGetRxCount(void)
{
    return LPUART_DmaGetRxCount(&LPUART12_DmaDriverState);
}

static int32_t LPUART12_DmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_DmaControl(control, arg, &LPUART12_DmaDriverState);
}

static ARM_USART_STATUS LPUART12_DmaGetStatus(void)
{
    return LPUART_DmaGetStatus(&LPUART12_DmaDriverState);
}

/* LPUART12 Driver Control Block */

#endif

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)

static cmsis_lpuart_edma_resource_t LPUART12_EdmaResource = {
    RTE_USART12_DMA_TX_DMA_BASE,    RTE_USART12_DMA_TX_CH,          RTE_USART12_DMA_TX_PERI_SEL,
    RTE_USART12_DMA_RX_DMA_BASE,    RTE_USART12_DMA_RX_CH,          RTE_USART12_DMA_RX_PERI_SEL,

#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    RTE_USART12_DMA_TX_DMAMUX_BASE, RTE_USART12_DMA_RX_DMAMUX_BASE,
#endif
};

static lpuart_edma_handle_t LPUART12_EdmaHandle;
static edma_handle_t LPUART12_EdmaRxHandle;
static edma_handle_t LPUART12_EdmaTxHandle;

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart12_edma_driver_state")
static cmsis_lpuart_edma_driver_state_t LPUART12_EdmaDriverState = {
#else
static cmsis_lpuart_edma_driver_state_t LPUART12_EdmaDriverState = {
#endif
    &LPUART12_Resource, &LPUART12_EdmaResource, &LPUART12_EdmaHandle, &LPUART12_EdmaRxHandle, &LPUART12_EdmaTxHandle,
};

static int32_t LPUART12_EdmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART12_PIN_INIT
    RTE_USART12_PIN_INIT();
#endif
    return LPUART_EdmaInitialize(cb_event, &LPUART12_EdmaDriverState);
}

static int32_t LPUART12_EdmaUninitialize(void)
{
#ifdef RTE_USART12_PIN_DEINIT
    RTE_USART12_PIN_DEINIT();
#endif
    return LPUART_EdmaUninitialize(&LPUART12_EdmaDriverState);
}

static int32_t LPUART12_EdmaPowerControl(ARM_POWER_STATE state)
{
    return LPUART_EdmaPowerControl(state, &LPUART12_EdmaDriverState);
}

static int32_t LPUART12_EdmaSend(const void *data, uint32_t num)
{
    return LPUART_EdmaSend(data, num, &LPUART12_EdmaDriverState);
}

static int32_t LPUART12_EdmaReceive(void *data, uint32_t num)
{
    return LPUART_EdmaReceive(data, num, &LPUART12_EdmaDriverState);
}

static int32_t LPUART12_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_EdmaTransfer(data_out, data_in, num, &LPUART12_EdmaDriverState);
}

static uint32_t LPUART12_EdmaGetTxCount(void)
{
    return LPUART_EdmaGetTxCount(&LPUART12_EdmaDriverState);
}

static uint32_t LPUART12_EdmaGetRxCount(void)
{
    return LPUART_EdmaGetRxCount(&LPUART12_EdmaDriverState);
}

static int32_t LPUART12_EdmaControl(uint32_t control, uint32_t arg)
{
    return LPUART_EdmaControl(control, arg, &LPUART12_EdmaDriverState);
}

static ARM_USART_STATUS LPUART12_EdmaGetStatus(void)
{
    return LPUART_EdmaGetStatus(&LPUART12_EdmaDriverState);
}

#endif

#else

static lpuart_handle_t LPUART12_Handle;

#if defined(USART12_RX_BUFFER_ENABLE) && (USART12_RX_BUFFER_ENABLE == 1)
static uint12_t lpuart12_rxRingBuffer[USART_RX_BUFFER_LEN];
#endif

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
ARMCC_SECTION("lpuart12_non_blocking_driver_state")
static cmsis_lpuart_non_blocking_driver_state_t LPUART12_NonBlockingDriverState = {
#else
static cmsis_lpuart_non_blocking_driver_state_t LPUART12_NonBlockingDriverState = {
#endif
    &LPUART12_Resource,
    &LPUART12_Handle,
};

static int32_t LPUART12_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
#ifdef RTE_USART12_PIN_INIT
    RTE_USART12_PIN_INIT();
#endif
    return LPUART_NonBlockingInitialize(cb_event, &LPUART12_NonBlockingDriverState);
}

static int32_t LPUART12_NonBlockingUninitialize(void)
{
#ifdef RTE_USART12_PIN_DEINIT
    RTE_USART12_PIN_DEINIT();
#endif
    return LPUART_NonBlockingUninitialize(&LPUART12_NonBlockingDriverState);
}

static int32_t LPUART12_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    int32_t result;

    result = LPUART_NonBlockingPowerControl(state, &LPUART12_NonBlockingDriverState);

#if defined(USART12_RX_BUFFER_ENABLE) && (USART12_RX_BUFFER_ENABLE == 1)
    if ((state == ARM_POWER_FULL) && (LPUART12_NonBlockingDriverState.handle->rxRingBuffer == NULL))
    {
        LPUART_TransferStartRingBuffer(LPUART12_NonBlockingDriverState.resource->base,
                                       LPUART12_NonBlockingDriverState.handle, lpuart12_rxRingBuffer,
                                       USART_RX_BUFFER_LEN);
    }
#endif

    return result;
}

static int32_t LPUART12_NonBlockingSend(const void *data, uint32_t num)
{
    return LPUART_NonBlockingSend(data, num, &LPUART12_NonBlockingDriverState);
}

static int32_t LPUART12_NonBlockingReceive(void *data, uint32_t num)
{
    return LPUART_NonBlockingReceive(data, num, &LPUART12_NonBlockingDriverState);
}

static int32_t LPUART12_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return LPUART_NonBlockingTransfer(data_out, data_in, num, &LPUART12_NonBlockingDriverState);
}

static uint32_t LPUART12_NonBlockingGetTxCount(void)
{
    return LPUART_NonBlockingGetTxCount(&LPUART12_NonBlockingDriverState);
}

static uint32_t LPUART12_NonBlockingGetRxCount(void)
{
    return LPUART_NonBlockingGetRxCount(&LPUART12_NonBlockingDriverState);
}

static int32_t LPUART12_NonBlockingControl(uint32_t control, uint32_t arg)
{
    int32_t result;

    result = LPUART_NonBlockingControl(control, arg, &LPUART12_NonBlockingDriverState);
    if (ARM_DRIVER_OK != result)
    {
        return result;
    }

    /* Enable the receive interrupts if ring buffer is used */
    if (LPUART12_NonBlockingDriverState.handle->rxRingBuffer != NULL)
    {
        LPUART_EnableInterrupts(
            LPUART12_NonBlockingDriverState.resource->base,
            (uint32_t)kLPUART_RxDataRegFullInterruptEnable | (uint32_t)kLPUART_RxOverrunInterruptEnable);
    }

    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS LPUART12_NonBlockingGetStatus(void)
{
    return LPUART_NonBlockingGetStatus(&LPUART12_NonBlockingDriverState);
}

#endif

ARM_DRIVER_USART Driver_USART12 = {LPUARTx_GetVersion,      LPUARTx_GetCapabilities,
#if defined(RTE_USART12_DMA_EN) && RTE_USART12_DMA_EN
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
                                   LPUART12_EdmaInitialize, LPUART12_EdmaUninitialize, LPUART12_EdmaPowerControl,
                                   LPUART12_EdmaSend,       LPUART12_EdmaReceive,      LPUART12_EdmaTransfer,
                                   LPUART12_EdmaGetTxCount, LPUART12_EdmaGetRxCount,   LPUART12_EdmaControl,
                                   LPUART12_EdmaGetStatus,
#else
                                   LPUART12_DmaInitialize,  LPUART12_DmaUninitialize, LPUART12_DmaPowerControl,
                                   LPUART12_DmaSend,        LPUART12_DmaReceive,      LPUART12_DmaTransfer,
                                   LPUART12_DmaGetTxCount,  LPUART12_DmaGetRxCount,   LPUART12_DmaControl,
                                   LPUART12_DmaGetStatus,
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */
#else
                                  LPUART12_NonBlockingInitialize,
                                  LPUART12_NonBlockingUninitialize,
                                  LPUART12_NonBlockingPowerControl,
                                  LPUART12_NonBlockingSend,
                                  LPUART12_NonBlockingReceive,
                                  LPUART12_NonBlockingTransfer,
                                  LPUART12_NonBlockingGetTxCount,
                                  LPUART12_NonBlockingGetRxCount,
                                  LPUART12_NonBlockingControl,
                                  LPUART12_NonBlockingGetStatus,
#endif /* RTE_USART12_DMA_EN */
                                   LPUARTx_SetModemControl, LPUARTx_GetModemStatus};

#endif /* LPUART12 */
