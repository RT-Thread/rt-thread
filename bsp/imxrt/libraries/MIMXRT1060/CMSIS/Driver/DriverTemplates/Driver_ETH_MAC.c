/*
 * Copyright (c) 2013-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Driver_ETH_MAC.h"

#define ARM_ETH_MAC_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(2, 0) /* driver version */

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
    ARM_ETH_MAC_API_VERSION,
    ARM_ETH_MAC_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_ETH_MAC_CAPABILITIES DriverCapabilities = {
    0, /* 1 = IPv4 header checksum verified on receive */
    0, /* 1 = IPv6 checksum verification supported on receive */
    0, /* 1 = UDP payload checksum verified on receive */
    0, /* 1 = TCP payload checksum verified on receive */
    0, /* 1 = ICMP payload checksum verified on receive */
    0, /* 1 = IPv4 header checksum generated on transmit */
    0, /* 1 = IPv6 checksum generation supported on transmit */
    0, /* 1 = UDP payload checksum generated on transmit */
    0, /* 1 = TCP payload checksum generated on transmit */
    0, /* 1 = ICMP payload checksum generated on transmit */
    0, /* Ethernet Media Interface type */
    0, /* 1 = driver provides initial valid MAC address */
    0, /* 1 = callback event \ref ARM_ETH_MAC_EVENT_RX_FRAME generated */
    0, /* 1 = callback event \ref ARM_ETH_MAC_EVENT_TX_FRAME generated */
    0, /* 1 = wakeup event \ref ARM_ETH_MAC_EVENT_WAKEUP generated */
    0  /* 1 = Precision Timer supported */
};

//
//  Functions
//

ARM_DRIVER_VERSION ARM_ETH_MAC_GetVersion(void)
{
}

ARM_ETH_MAC_CAPABILITIES ARM_ETH_MAC_GetCapabilities(void)
{
}

int32_t ARM_ETH_MAC_Initialize(ARM_ETH_MAC_SignalEvent_t cb_event)
{
}

int32_t ARM_ETH_MAC_Uninitialize(void)
{
}

int32_t ARM_ETH_MAC_PowerControl(ARM_POWER_STATE state)
{
    switch (state)
    {
    case ARM_POWER_OFF:
        break;

    case ARM_POWER_LOW:
        break;

    case ARM_POWER_FULL:
        break;

    default:
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }
}

int32_t ARM_ETH_MAC_GetMacAddress(ARM_ETH_MAC_ADDR *ptr_addr)
{
}

int32_t ARM_ETH_MAC_SetMacAddress(const ARM_ETH_MAC_ADDR *ptr_addr)
{
}

int32_t ARM_ETH_MAC_SetAddressFilter(const ARM_ETH_MAC_ADDR *ptr_addr, uint32_t num_addr)
{
}

int32_t ARM_ETH_MAC_SendFrame(const uint8_t *frame, uint32_t len, uint32_t flags)
{
}

int32_t ARM_ETH_MAC_ReadFrame(uint8_t *frame, uint32_t len)
{
}

uint32_t ARM_ETH_MAC_GetRxFrameSize(void)
{
}

int32_t ARM_ETH_MAC_GetRxFrameTime(ARM_ETH_MAC_TIME *time)
{
}

int32_t ARM_ETH_MAC_GetTxFrameTime(ARM_ETH_MAC_TIME *time)
{
}

int32_t ARM_ETH_MAC_Control(uint32_t control, uint32_t arg)
{
    switch (control)
    {
    case ARM_ETH_MAC_CONFIGURE:

        switch (arg & ARM_ETH_MAC_SPEED_Msk)
        {
        case ARM_ETH_MAC_SPEED_10M:
            break;
        case ARM_ETH_SPEED_100M:
            break;
        default:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
        }

        switch (arg & ARM_ETH_MAC_DUPLEX_Msk)
        {
        case ARM_ETH_MAC_DUPLEX_FULL:
            break;
        }

        if (arg & ARM_ETH_MAC_LOOPBACK)
        {
        }

        if ((arg & ARM_ETH_MAC_CHECKSUM_OFFLOAD_RX) ||
            (arg & ARM_ETH_MAC_CHECKSUM_OFFLOAD_TX))
        {
            return ARM_DRIVER_ERROR_UNSUPPORTED;
        }

        if (!(arg & ARM_ETH_MAC_ADDRESS_BROADCAST))
        {
        }

        if (arg & ARM_ETH_MAC_ADDRESS_MULTICAST)
        {
        }

        if (arg & ARM_ETH_MAC_ADDRESS_ALL)
        {
        }

        break;

    case ARM_ETH_MAC_CONTROL_TX:
        break;

    case ARM_ETH_MAC_CONTROL_RX:
        break;

    case ARM_ETH_MAC_FLUSH:
        if (arg & ARM_ETH_MAC_FLUSH_RX)
        {
        }
        if (arg & ARM_ETH_MAC_FLUSH_TX)
        {
        }
        break;

    case ARM_ETH_MAC_SLEEP:
        break;

    case ARM_ETH_MAC_VLAN_FILTER:
        break;

    default:
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }
}

int32_t ARM_ETH_MAC_ControlTimer(uint32_t control, ARM_ETH_MAC_TIME *time)
{
}

int32_t ARM_ETH_MAC_PHY_Read(uint8_t phy_addr, uint8_t reg_addr, uint16_t *data)
{
}

int32_t ARM_ETH_MAC_PHY_Write(uint8_t phy_addr, uint8_t reg_addr, uint16_t data)
{
}

void ARM_ETH_MAC_SignalEvent(uint32_t event)
{
}

// End ETH MAC Interface

ARM_DRIVER_ETH_MAC Driver_ETH_MAC =
{
    ARM_ETH_MAC_GetVersion,
    ARM_ETH_MAC_GetCapabilities,
    ARM_ETH_MAC_Initialize,
    ARM_ETH_MAC_Uninitialize,
    ARM_ETH_MAC_PowerControl,
    ARM_ETH_MAC_GetMacAddress,
    ARM_ETH_MAC_SetMacAddress,
    ARM_ETH_MAC_SetAddressFilter,
    ARM_ETH_MAC_SendFrame,
    ARM_ETH_MAC_ReadFrame,
    ARM_ETH_MAC_GetRxFrameSize,
    ARM_ETH_MAC_GetRxFrameTime,
    ARM_ETH_MAC_GetTxFrameTime,
    ARM_ETH_MAC_ControlTimer,
    ARM_ETH_MAC_Control,
    ARM_ETH_MAC_PHY_Read,
    ARM_ETH_MAC_PHY_Write
};
