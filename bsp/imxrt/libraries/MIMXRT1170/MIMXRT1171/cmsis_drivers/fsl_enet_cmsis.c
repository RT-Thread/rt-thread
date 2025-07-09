/*
 * Copyright (c) 2013-2016 ARM Limited. All rights reserved.
 * Copyright (c) 2016, Freescale Semiconductor, Inc. Not a Contribution.
 * Copyright 2016-2021, 2023, 2025 NXP. Not a Contribution.
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

#include "fsl_enet_cmsis.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.enet_cmsis"
#endif

#define ARM_ETH_MAC_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(2, 4)

/* Define the alignment macro. */
#if defined(FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL) && FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL
#if defined(FSL_FEATURE_L2CACHE_LINESIZE_BYTE) && \
    ((!defined(FSL_SDK_DISBLE_L2CACHE_PRESENT)) || (FSL_SDK_DISBLE_L2CACHE_PRESENT == 0))
#define CMSIS_CACHE_LINESIZE_MAX  MAX(FSL_FEATURE_L1DCACHE_LINESIZE_BYTE, FSL_FEATURE_L2CACHE_LINESIZE_BYTE)
#define CMSIS_ENET_BUFF_ALIGNMENT MAX(ENET_BUFF_ALIGNMENT, CMSIS_CACHE_LINESIZE_MAX)
#elif defined(FSL_FEATURE_L1DCACHE_LINESIZE_BYTE)
#define CMSIS_ENET_BUFF_ALIGNMENT MAX(ENET_BUFF_ALIGNMENT, FSL_FEATURE_L1DCACHE_LINESIZE_BYTE)
#endif
#else
#define CMSIS_ENET_BUFF_ALIGNMENT ENET_BUFF_ALIGNMENT
#endif
/* Define the ENET buffer information. */
#define ENET_RXBD_NUM    (4)
#define ENET_TXBD_NUM    (4)
#define ENET_RXBUFF_SIZE (ENET_FRAME_MAX_FRAMELEN)
#define ENET_TXBUFF_SIZE (ENET_FRAME_MAX_FRAMELEN)
/* Define the timeout macro. */
#define ENET_SMI_TIMEOUT_COUNT 0xffff

typedef struct _cmsis_enet_mac_driver_state
{
    cmsis_enet_mac_resource_t *resource;  /*!< Basic enet resource. */
    enet_handle_t *handle;                /*!< ENET handler. */
    enet_buffer_config_t *buffers;        /*!< Buffers res*/
    ARM_ETH_MAC_SignalEvent_t cb_event;   /*!< Callback function. */
    volatile enet_tx_bd_struct_t *txBdTs; /*!< Tx timestamp index. */
    uint8_t flags;                        /*!< Control and state flags. */
} cmsis_enet_mac_driver_state_t;

static const ARM_DRIVER_VERSION s_enetDriverVersion = {ARM_ETH_MAC_API_VERSION, ARM_ETH_MAC_DRV_VERSION};

/* Driver Capabilities */
static const ARM_ETH_MAC_CAPABILITIES s_enetDriverCapabilities = {
    0,                                                                /* checksum_offload_rx_ip4  */
    0,                                                                /* checksum_offload_rx_ip6  */
    0,                                                                /* checksum_offload_rx_udp  */
    0,                                                                /* checksum_offload_rx_tcp  */
    0,                                                                /* checksum_offload_rx_icmp */
    0,                                                                /* checksum_offload_tx_ip4  */
    0,                                                                /* checksum_offload_tx_ip6  */
    0,                                                                /* checksum_offload_tx_udp  */
    0,                                                                /* checksum_offload_tx_tcp  */
    0,                                                                /* checksum_offload_tx_icmp */
    (RTE_ENET_RMII) ? ARM_ETH_INTERFACE_RMII : ARM_ETH_INTERFACE_MII, /* media_interface          */
    0,                                                                /* mac_address              */
    1,                                                                /* event_rx_frame           */
    1,                                                                /* event_tx_frame           */
    1,                                                                /* event_wakeup             */
    0                                                                 /* precision_timer          */
};

static ARM_DRIVER_VERSION ENETx_GetVersion(void)
{
    return s_enetDriverVersion;
}

static ARM_ETH_MAC_CAPABILITIES ENETx_GetCapabilities(void)
{
    return s_enetDriverCapabilities;
}

static int32_t ENET_CommonInitialize(ARM_ETH_MAC_SignalEvent_t cb_event, cmsis_enet_mac_driver_state_t *enet)
{
    if ((enet->flags & ENET_FLAG_INIT) == 0U)
    {
        enet->cb_event = cb_event;
        enet->flags    = ENET_FLAG_INIT;
    }

    return ARM_DRIVER_OK;
}

static void ENET_SetInterruptCallback(ENET_Type *base,
                                      enet_handle_t *handle,
#if FSL_FEATURE_ENET_QUEUE > 1
                                      uint32_t ringId,
#endif
                                      enet_event_t event,
                                      enet_frame_info_t *frameInfo,
                                      void *userData)
{
    uint32_t newEvent;

    switch (event)
    {
        case kENET_RxEvent:
            newEvent = ARM_ETH_MAC_EVENT_RX_FRAME;
            break;
        case kENET_TxEvent:
            newEvent = ARM_ETH_MAC_EVENT_TX_FRAME;
            break;
        case kENET_WakeUpEvent:
            newEvent = ARM_ETH_MAC_EVENT_WAKEUP;
            break;
        case kENET_TimeStampEvent:
            newEvent = ARM_ETH_MAC_EVENT_TIMER_ALARM;
            break;
        default:
            newEvent = ETH_MAC_EVENT_OTHERS;
            break;
    }

    /* User data is actually CMSIS driver callback. */
    if (userData != NULL)
    {
        ((ARM_ETH_MAC_SignalEvent_t)userData)(newEvent);
    }
}

static int32_t ENET_CommonUninitialize(cmsis_enet_mac_driver_state_t *enet)
{
    enet->flags = ENET_FLAG_UNINIT;
    return ARM_DRIVER_OK;
}

static int32_t ENET_CommonControl(uint32_t control, uint32_t arg, cmsis_enet_mac_driver_state_t *enet)
{
    int32_t result = ARM_DRIVER_OK;

    if (enet->flags == ENET_FLAG_UNINIT)
    {
        return ARM_DRIVER_ERROR;
    }

    switch (control)
    {
        case (uint32_t)ARM_ETH_MAC_CONFIGURE:
        {
            uint32_t rcr = enet->resource->base->RCR;
            uint32_t tcr = enet->resource->base->TCR;
#if defined(FSL_FEATURE_ENET_HAS_AVB) && FSL_FEATURE_ENET_HAS_AVB
            uint32_t ecr = enet->resource->base->ECR;
            if (FSL_FEATURE_ENET_INSTANCE_HAS_AVBn(enet->resource->base) > 0)
            {
                ecr &= ~ENET_ECR_SPEED_MASK;
            }
#endif /* FSL_FEATURE_ENET_HAS_AVB */

            switch (arg & (uint32_t)ARM_ETH_MAC_SPEED_Msk)
            {
                case (uint32_t)ARM_ETH_MAC_SPEED_10M:
                    rcr |= ENET_RCR_RMII_10T_MASK;
                    break;
                case (uint32_t)ARM_ETH_MAC_SPEED_100M:
                    rcr &= ~ENET_RCR_RMII_10T_MASK;
                    break;
#if defined(FSL_FEATURE_ENET_HAS_AVB) && FSL_FEATURE_ENET_HAS_AVB
                case (uint32_t)ARM_ETH_MAC_SPEED_1G:
                    /* If the selected enet doesn't support 1G, return unsupported status */
                    if (FSL_FEATURE_ENET_INSTANCE_HAS_AVBn(enet->resource->base) > 0)
                    {
                        ecr |= ENET_ECR_SPEED_MASK;
                        rcr &= ~ENET_RCR_RMII_10T_MASK;
                    }
                    else
                    {
                        result = ARM_DRIVER_ERROR_UNSUPPORTED;
                    }
                    break;
#endif /* FSL_FEATURE_ENET_HAS_AVB */
                default:
                    result = ARM_DRIVER_ERROR_UNSUPPORTED;
                    break;
            }
            if (result != ARM_DRIVER_OK)
            {
                return result;
            }
            switch (arg & ARM_ETH_MAC_DUPLEX_Msk)
            {
                case (uint32_t)ARM_ETH_MAC_DUPLEX_HALF:
                    rcr |= ENET_RCR_DRT_MASK;
                    tcr &= ~ENET_TCR_FDEN_MASK;
                    break;
                case (uint32_t)ARM_ETH_MAC_DUPLEX_FULL:
                    rcr &= ~ENET_RCR_DRT_MASK;
                    tcr |= ENET_TCR_FDEN_MASK;
                    break;
                default:
                    result = ARM_DRIVER_ERROR_UNSUPPORTED;
                    break;
            }
            if (result != ARM_DRIVER_OK)
            {
                return result;
            }

            if ((arg & (ARM_ETH_MAC_CHECKSUM_OFFLOAD_RX | ARM_ETH_MAC_CHECKSUM_OFFLOAD_TX)) != 0U)
            {
                return ARM_DRIVER_ERROR_UNSUPPORTED;
            }

            if ((arg & ARM_ETH_MAC_ADDRESS_BROADCAST) != 0U)
            {
                rcr &= ~ENET_RCR_BC_REJ_MASK;
            }
            else
            {
                rcr |= ENET_RCR_BC_REJ_MASK;
            }

            if ((arg & ARM_ETH_MAC_ADDRESS_MULTICAST) != 0U)
            {
                return ARM_DRIVER_ERROR_UNSUPPORTED;
            }

            if ((arg & ARM_ETH_MAC_ADDRESS_ALL) != 0U)
            {
                rcr |= ENET_RCR_PROM_MASK;
            }

            if ((arg & ARM_ETH_MAC_LOOPBACK) != 0U)
            {
                /* Loop back only supported on MII mode. */
                if ((rcr & ENET_RCR_RMII_MODE_MASK) == 0U)
                {
                    rcr |= ENET_RCR_LOOP_MASK;
                    rcr &= ~ENET_RCR_DRT_MASK;
                }
            }

            enet->resource->base->RCR = rcr;
            enet->resource->base->TCR = tcr;
#if defined(FSL_FEATURE_ENET_HAS_AVB) && FSL_FEATURE_ENET_HAS_AVB
            if (FSL_FEATURE_ENET_INSTANCE_HAS_AVBn(enet->resource->base) > 0)
            {
                enet->resource->base->ECR = ecr;
            }
#endif /* FSL_FEATURE_ENET_HAS_AVB */
        }
        break;
        case (uint32_t)ARM_ETH_MAC_CONTROL_TX:
            if (arg != 0U)
            {
                enet->resource->base->TDAR = ENET_TDAR_TDAR_MASK;
            }
            else
            {
                enet->resource->base->TDAR &= ~ENET_TDAR_TDAR_MASK;
            }
            break;
        case (uint32_t)ARM_ETH_MAC_CONTROL_RX:
            if (arg != 0U)
            {
                ENET_ActiveRead(enet->resource->base);
            }
            else
            {
                enet->resource->base->RDAR &= ~ENET_RDAR_RDAR_MASK;
            }
            break;
        case (uint32_t)ARM_ETH_MAC_SLEEP:
            ENET_EnableSleepMode(enet->resource->base, (bool)arg);
            break;
        default:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
    }
    return result;
}

static int32_t ENET_CommonPowerControl(ARM_POWER_STATE state, cmsis_enet_mac_driver_state_t *enet)
{
    int32_t result = ARM_DRIVER_OK;
    ARM_ETH_MAC_CAPABILITIES capabilities;

    switch (state)
    {
        case ARM_POWER_OFF:
            if ((enet->flags & ENET_FLAG_POWER) != 0U)
            {
                (void)ENET_CommonControl(ARM_ETH_MAC_CONTROL_TX, 0, enet);
                (void)ENET_CommonControl(ARM_ETH_MAC_CONTROL_RX, 0, enet);
                ENET_Reset(enet->resource->base);
                ENET_Deinit(enet->resource->base);

                enet->flags = ENET_FLAG_INIT;
            }
            break;
        case ARM_POWER_LOW:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
        case ARM_POWER_FULL:
        {
            if (enet->flags == ENET_FLAG_UNINIT)
            {
                return ARM_DRIVER_ERROR;
            }

            if ((enet->flags & ENET_FLAG_POWER) != 0U)
            {
                /* Driver already powered */
                break;
            }

            enet_config_t config;
            uint8_t macAddr[6] = {0};
            uint32_t freq;

            /* Get default configuration. */
            ENET_GetDefaultConfig(&config);
            /* Change the MII interface mode according to the MII interface macro. */
            capabilities = ENETx_GetCapabilities();
            if (capabilities.media_interface == (uint32_t)ARM_ETH_INTERFACE_MII)
            {
                config.miiMode = kENET_MiiMode;
            }
            else if (capabilities.media_interface == (uint32_t)ARM_ETH_INTERFACE_RMII)
            {
#if defined(RTE_ENET_RGMII) && RTE_ENET_RGMII
#if defined(FSL_FEATURE_ENET_HAS_AVB) && FSL_FEATURE_ENET_HAS_AVB
                if (FSL_FEATURE_ENET_INSTANCE_HAS_AVBn(enet->resource->base) > 0)
                {
                    config.miiMode = kENET_RgmiiMode;
                }
                else
                {
                    result = ARM_DRIVER_ERROR_UNSUPPORTED;
                    break;
                }
#endif /* FSL_FEATURE_ENET_HAS_AVB */
#else
                config.miiMode = kENET_RmiiMode;
#endif /* RTE_ENET_RGMII */
            }
            else
            {
                /* Intentional empty */
            }

            /* Enable the tx/rx interrupt mode. */
            config.interrupt = (uint32_t)kENET_TxFrameInterrupt | (uint32_t)kENET_RxFrameInterrupt;
            /* Enable tx accelerate function. */
            config.txAccelerConfig = (uint8_t)kENET_TxAccelIpCheckEnabled | (uint8_t)kENET_TxAccelProtoCheckEnabled;
            /* Callback setup */
            config.callback  = ENET_SetInterruptCallback;
            config.userData = (void *)enet->cb_event;
            /* Initialize Ethernet Mac. */
            freq = enet->resource->GetFreq();
            (void)ENET_Init(enet->resource->base, enet->handle, &config, enet->buffers, &macAddr[0], freq);
            enet->flags |= ENET_FLAG_POWER;
            break;
        }
        default:
            result = ARM_DRIVER_ERROR_UNSUPPORTED;
            break;
    }
    return result;
}

static int32_t ENET_Phy_Write(cmsis_enet_mac_resource_t *enet, uint8_t phy_addr, uint8_t reg_addr, uint16_t data)
{
    uint32_t counter;

    /* Clear the SMI interrupt event. */
    ENET_ClearInterruptStatus(enet->base, ENET_EIR_MII_MASK);

    /* Starts a SMI write command. */
    ENET_StartSMIWrite(enet->base, phy_addr, reg_addr, kENET_MiiWriteValidFrame, data);

    /* Wait for SMI complete. */
    for (counter = ENET_SMI_TIMEOUT_COUNT; counter > 0U; counter--)
    {
        if ((ENET_GetInterruptStatus(enet->base) & ENET_EIR_MII_MASK) != 0U)
        {
            break;
        }
    }

    /* Check for timeout. */
    if (counter == 0U)
    {
        return ARM_DRIVER_ERROR;
    }

    /* Clear MII interrupt event. */
    ENET_ClearInterruptStatus(enet->base, ENET_EIR_MII_MASK);

    return ARM_DRIVER_OK;
}

static int32_t ENET_Phy_Read(cmsis_enet_mac_resource_t *enet, uint8_t phy_addr, uint8_t reg_addr, uint16_t *data)
{
    assert(data);

    uint32_t counter;

    /* Clear the MII interrupt event. */
    ENET_ClearInterruptStatus(enet->base, ENET_EIR_MII_MASK);

    /* Starts a SMI read command operation. */
    ENET_StartSMIRead(enet->base, phy_addr, reg_addr, kENET_MiiReadValidFrame);

    /* Wait for MII complete. */
    for (counter = ENET_SMI_TIMEOUT_COUNT; counter > 0U; counter--)
    {
        if ((ENET_GetInterruptStatus(enet->base) & ENET_EIR_MII_MASK) != 0U)
        {
            break;
        }
    }

    /* Check for timeout. */
    if (counter == 0U)
    {
        return ARM_DRIVER_ERROR;
    }

    /* Get data from MII register. */
    *data = (uint16_t)ENET_ReadSMIData(enet->base);

    /* Clear MII interrupt event. */
    ENET_ClearInterruptStatus(enet->base, ENET_EIR_MII_MASK);

    return ARM_DRIVER_OK;
}

static int32_t ENET_CommonSendFrame(cmsis_enet_mac_driver_state_t *enet,
                                    const uint8_t *frame,
                                    uint32_t len,
                                    uint32_t flags)
{
    status_t status;

    /* The SDK send frame driver is send with a whole frame and
     * the timestamp will be enabled automatically when it is a PTP frame
     * by parse the frame.
     */
    if ((flags & (ARM_ETH_MAC_TX_FRAME_FRAGMENT | ARM_ETH_MAC_TX_FRAME_TIMESTAMP)) != 0U)
    {
        return ARM_DRIVER_ERROR;
    }

    status = ENET_SendFrame(enet->resource->base, enet->handle, frame, len, 0, false, NULL);
    if (status == kStatus_ENET_TxFrameOverLen)
    {
        return ARM_DRIVER_ERROR_PARAMETER;
    }
    else if (status == kStatus_ENET_TxFrameBusy)
    {
        return ARM_DRIVER_ERROR_BUSY;
    }
    else if (status == kStatus_ENET_TxFrameFail)
    {
        return ARM_DRIVER_ERROR;
    }
    else
    {
        return ARM_DRIVER_OK;
    }
}

static uint32_t ENET_CommonGetFrameSize(cmsis_enet_mac_driver_state_t *enet)
{
    status_t status;
    uint32_t length = 0;

    status = ENET_GetRxFrameSize(enet->handle, &length, 0);
    if (status == kStatus_ENET_RxFrameError)
    {
        /* Should update the buffers. */
        (void)ENET_ReadFrame(enet->resource->base, enet->handle, NULL, 0, 0, NULL);
    }
    return length;
}

static int32_t ENET_CommonReadFrame(cmsis_enet_mac_driver_state_t *enet, uint8_t *frame, uint32_t len)
{
    status_t status;

    /* Check if len exceeds int32_t maximum value. */
    if (len > 0x7FFFFFFFU)
    {
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    status = ENET_ReadFrame(enet->resource->base, enet->handle, frame, len, 0, NULL);
    if (status != kStatus_Success)
    {
        return ARM_DRIVER_ERROR;
    }

    return (int32_t)len;
}

#if RTE_ENET

/*! @brief Buffer descriptors should be in non-cacheable region and should be align to "ENET_BUFF_ALIGNMENT". */
AT_NONCACHEABLE_SECTION_ALIGN(static enet_rx_bd_struct_t g_rxBuffDescrip[ENET_RXBD_NUM], ENET_BUFF_ALIGNMENT);
AT_NONCACHEABLE_SECTION_ALIGN(static enet_tx_bd_struct_t g_txBuffDescrip[ENET_TXBD_NUM], ENET_BUFF_ALIGNMENT);
/*! @brief The data buffers can be in cacheable region or in non-cacheable region.
 * If use cacheable region, the alignment size should be the maximum size of "CACHE LINE SIZE" and "ENET_BUFF_ALIGNMENT"
 * If use non-cache region, the alignment size is the "ENET_BUFF_ALIGNMENT".
 */
SDK_ALIGN(static uint8_t g_rxDataBuff[ENET_RXBD_NUM][SDK_SIZEALIGN(ENET_RXBUFF_SIZE, CMSIS_ENET_BUFF_ALIGNMENT)],
          CMSIS_ENET_BUFF_ALIGNMENT);
SDK_ALIGN(static uint8_t g_txDataBuff[ENET_TXBD_NUM][SDK_SIZEALIGN(ENET_TXBUFF_SIZE, CMSIS_ENET_BUFF_ALIGNMENT)],
          CMSIS_ENET_BUFF_ALIGNMENT);

extern cmsis_enet_mac_resource_t ENET0_Resource;

extern void ENET0_InitPins(void);
extern void ENET0_DeinitPins(void);

static enet_handle_t ENET0_Handle;
static enet_buffer_config_t ENET0_BuffConfig = {ENET_RXBD_NUM,
                                                ENET_TXBD_NUM,
                                                SDK_SIZEALIGN(ENET_RXBUFF_SIZE, CMSIS_ENET_BUFF_ALIGNMENT),
                                                SDK_SIZEALIGN(ENET_TXBUFF_SIZE, CMSIS_ENET_BUFF_ALIGNMENT),
                                                &g_rxBuffDescrip[0],
                                                &g_txBuffDescrip[0],
                                                &g_rxDataBuff[0][0],
                                                &g_txDataBuff[0][0],
                                                (bool)true,
                                                (bool)true,
                                                NULL};

static cmsis_enet_mac_driver_state_t ENET0_DriverState = {&ENET0_Resource, &ENET0_Handle, &ENET0_BuffConfig};

static int32_t ENET0_Initialize(ARM_ETH_MAC_SignalEvent_t cb_event)
{
    ENET0_InitPins();
    return ENET_CommonInitialize(cb_event, &ENET0_DriverState);
}

static int32_t ENET0_Uninitialize(void)
{
    ENET0_DeinitPins();
    return ENET_CommonUninitialize(&ENET0_DriverState);
}

static int32_t ENET0_PowerControl(ARM_POWER_STATE state)
{
    return ENET_CommonPowerControl(state, &ENET0_DriverState);
}

static int32_t ENET0_GetMacAddress(ARM_ETH_MAC_ADDR *ptr_addr)
{
    ENET_GetMacAddr(ENET0_Resource.base, &ptr_addr->b[0]);

    return ARM_DRIVER_OK;
}

static int32_t ENET0_SetMacAddress(const ARM_ETH_MAC_ADDR *ptr_addr)
{
    uint8_t mac[6];
    (void)memcpy((void *)&mac[0], (const void *)ptr_addr, 6);
    ENET_SetMacAddr(ENET0_Resource.base, &mac[0]);

    return ARM_DRIVER_OK;
}

static int32_t ENET0_TransmitFrame(const uint8_t *frame, uint32_t len, uint32_t flags)
{
    return ENET_CommonSendFrame(&ENET0_DriverState, frame, len, flags);
}

static uint32_t ENET0_GetReceiveFrameSize(void)
{
    return ENET_CommonGetFrameSize(&ENET0_DriverState);
}

static int32_t ENET0_ReceiveFrame(uint8_t *frame, uint32_t len)
{
    return ENET_CommonReadFrame(&ENET0_DriverState, frame, len);
}

static int32_t ENET0_Control(uint32_t control, uint32_t arg)
{
    return ENET_CommonControl(control, arg, &ENET0_DriverState);
}

static int32_t ENET0_PhyWrite(uint8_t phy_addr, uint8_t reg_addr, uint16_t data)
{
    return ENET_Phy_Write(&ENET0_Resource, phy_addr, reg_addr, data);
}

static int32_t ENET0_PhyRead(uint8_t phy_addr, uint8_t reg_addr, uint16_t *data)
{
    return ENET_Phy_Read(&ENET0_Resource, phy_addr, reg_addr, data);
}

static int32_t ENET0_SetAddressFilter(const ARM_ETH_MAC_ADDR *ptr_addr, uint32_t num_addr)
{
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t ENET0_GetRxFrameTime(ARM_ETH_MAC_TIME *time)
{
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t ENET0_GetTxFrameTime(ARM_ETH_MAC_TIME *time)
{
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static int32_t ENET0_ControlTimer(uint32_t control, ARM_ETH_MAC_TIME *time)
{
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

ARM_DRIVER_ETH_MAC Driver_ETH_MAC0 = {ENETx_GetVersion,
                                      ENETx_GetCapabilities,
                                      ENET0_Initialize,
                                      ENET0_Uninitialize,
                                      ENET0_PowerControl,
                                      ENET0_GetMacAddress,
                                      ENET0_SetMacAddress,
                                      ENET0_SetAddressFilter,
                                      ENET0_TransmitFrame,
                                      ENET0_ReceiveFrame,
                                      ENET0_GetReceiveFrameSize,
                                      ENET0_GetRxFrameTime,
                                      ENET0_GetTxFrameTime,
                                      ENET0_ControlTimer,
                                      ENET0_Control,
                                      ENET0_PhyRead,
                                      ENET0_PhyWrite};
#endif
