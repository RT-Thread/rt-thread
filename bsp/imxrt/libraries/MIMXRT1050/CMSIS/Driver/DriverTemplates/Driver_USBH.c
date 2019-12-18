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
 
#include "Driver_USBH.h"

/* USB Host Driver */

#define ARM_USBH_DRV_VERSION    ARM_DRIVER_VERSION_MAJOR_MINOR(2, 0) /* driver version */

/* Driver Version */
static const ARM_DRIVER_VERSION usbh_driver_version = { 
    ARM_USBH_API_VERSION,
    ARM_USBH_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_USBH_CAPABILITIES usbd_driver_capabilities = {
    0x0001, /* Root HUB available Ports Mask   */
    0,      /* Automatic SPLIT packet handling */
    0,      /* Signal Connect event */
    0,      /* Signal Disconnect event */
    0       /* Signal Overcurrent event */
};

//
// Functions
//

ARM_DRIVER_VERSION ARM_USBH_GetVersion(void)
{
}

ARM_USBH_CAPABILITIES ARM_USBH_GetCapabilities(void)
{
}

int32_t ARM_USBH_Initialize(ARM_USBH_SignalPortEvent_t cb_port_event,
                            ARM_USBH_SignalEndpointEvent_t cb_endpoint_event)
{
}

int32_t ARM_USBH_Uninitialize(void)
{
}

int32_t ARM_USBH_PowerControl(ARM_POWER_STATE state)
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

int32_t ARM_USBH_PortVbusOnOff(uint8_t port, bool vbus)
{
}

int32_t ARM_USBH_PortReset(uint8_t port)
{
}

int32_t ARM_USBH_PortSuspend(uint8_t port)
{
}

int32_t ARM_USBH_PortResume(uint8_t port)
{
}

ARM_USBH_PORT_STATE ARM_USBH_PortGetState(uint8_t port)
{
}

ARM_USBH_EP_HANDLE ARM_USBH_EndpointCreate(uint8_t dev_addr,
                                           uint8_t dev_speed,
                                           uint8_t hub_addr,
                                           uint8_t hub_port,
                                           uint8_t ep_addr,
                                           uint8_t ep_type,
                                           uint16_t ep_max_packet_size,
                                           uint8_t ep_interval)
{
}

int32_t ARM_USBH_EndpointModify(ARM_USBH_EP_HANDLE ep_hndl,
                                uint8_t dev_addr,
                                uint8_t dev_speed,
                                uint8_t hub_addr,
                                uint8_t hub_port,
                                uint16_t ep_max_packet_size)
{
}

int32_t ARM_USBH_EndpointDelete(ARM_USBH_EP_HANDLE ep_hndl)
{
}

int32_t ARM_USBH_EndpointReset(ARM_USBH_EP_HANDLE ep_hndl)
{
}

int32_t ARM_USBH_EndpointTransfer(ARM_USBH_EP_HANDLE ep_hndl,
                                  uint32_t packet,
                                  uint8_t *data,
                                  uint32_t num)
{
}

uint32_t ARM_USBH_EndpointTransferGetResult(ARM_USBH_EP_HANDLE ep_hndl)
{
}

int32_t ARM_USBH_EndpointTransferAbort(ARM_USBH_EP_HANDLE ep_hndl)
{
}

uint16_t ARM_USBH_GetFrameNumber(void)
{
}

void ARM_USBH_SignalPortEvent(uint8_t port, uint32_t event)
{
    // function body
}

void ARM_USBH_SignalEndpointEvent(ARM_USBH_EP_HANDLE ep_hndl, uint32_t event)
{
    // function body
}

/* USB Host HCI (OHCI/EHCI) Driver */

/* Driver Version */
static const ARM_DRIVER_VERSION usbh_hci_driver_version = { 
    ARM_USBH_API_VERSION,
    ARM_USBH_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_USBH_HCI_CAPABILITIES usbh_hci_driver_capabilities = {
    0x0001  /* Root HUB available Ports Mask   */
};

//
// Functions
//

ARM_DRIVER_VERSION ARM_USBH_HCI_GetVersion(void)
{
}

ARM_USBH_HCI_CAPABILITIES ARM_USBH_HCI_GetCapabilities(void)
{
}

int32_t ARM_USBH_HCI_Initialize(ARM_USBH_HCI_Interrupt_t cb_interrupt)
{
}

int32_t ARM_USBH_HCI_Uninitialize(void)
{
}

int32_t ARM_USBH_HCI_PowerControl(ARM_POWER_STATE state)
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

int32_t ARM_USBH_HCI_PortVbusOnOff(uint8_t port, bool vbus)
{
}

void ARM_USBH_HCI_Interrupt(void)
{
    // function body
}

// End USBH Interface

ARM_DRIVER_USBH_HCI Driver_USBH_HCI = {
    ARM_USBH_HCI_GetVersion,
    ARM_USBH_HCI_GetCapabilities,
    ARM_USBH_HCI_Initialize,
    ARM_USBH_HCI_Uninitialize,
    ARM_USBH_HCI_PowerControl,
    ARM_USBH_HCI_PortVbusOnOff
};
