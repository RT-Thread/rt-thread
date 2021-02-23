/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <usb/include/usb_host_config.h>
#include "usb_host.h"
#include "usb_host_hci.h"
#include "usb_host_devices.h"
#include "usb_host_framework.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "middleware.usb.host.fatfs_usb_stack"
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

usb_status_t USB_HostCh9RequestCommon(usb_host_device_instance_t *deviceInstance,
                                      usb_host_transfer_t *transfer,
                                      uint8_t *buffer,
                                      uint32_t bufferLen)
{
    /* initialize transfer */
    transfer->setupPacket->wLength = USB_SHORT_TO_LITTLE_ENDIAN((uint16_t)bufferLen);
    transfer->transferBuffer       = buffer;
    transfer->transferLength       = bufferLen;

    if (USB_HostSendSetup(deviceInstance->hostHandle, deviceInstance->controlPipe, transfer) !=
        kStatus_USB_Success) /* send setup transfer */
    {
#ifdef HOST_ECHO
        usb_echo("failed for USB_HostSendSetup\r\n");
#endif
        (void)USB_HostFreeTransfer(deviceInstance->hostHandle, transfer);
        return kStatus_USB_Error;
    }
    return kStatus_USB_Success;
}

usb_status_t USB_HostStandardGetStatus(usb_host_device_instance_t *deviceInstance,
                                       usb_host_transfer_t *transfer,
                                       void *param)
{
    usb_host_get_status_param_t *statusParam;
    uint8_t length;

    /* initialize transfer */
    statusParam                          = (usb_host_get_status_param_t *)param;
    transfer->setupPacket->bmRequestType = USB_REQUEST_TYPE_DIR_IN | USB_REQUEST_TYPE_TYPE_STANDARD;
    if (statusParam->requestType == (uint8_t)kRequestDevice)
    {
        transfer->setupPacket->bmRequestType |= USB_REQUEST_TYPE_RECIPIENT_DEVICE;
    }
    else if (statusParam->requestType == (uint8_t)kRequestInterface)
    {
        transfer->setupPacket->bmRequestType |= USB_REQUEST_TYPE_RECIPIENT_INTERFACE;
    }
    else
    {
        transfer->setupPacket->bmRequestType |= USB_REQUEST_TYPE_RECIPIENT_ENDPOINT;
    }
    transfer->setupPacket->wIndex = USB_SHORT_TO_LITTLE_ENDIAN(statusParam->statusSelector);

    length = 2;
    if (statusParam->statusSelector == USB_REQUEST_STANDARD_GET_STATUS_OTG_STATUS_SELECTOR)
    {
        length = 1;
    }
    return USB_HostCh9RequestCommon(deviceInstance, transfer, statusParam->statusBuffer, length);
}

usb_status_t USB_HostStandardSetClearFeature(usb_host_device_instance_t *deviceInstance,
                                             usb_host_transfer_t *transfer,
                                             void *param)
{
    usb_host_process_feature_param_t *featureParam;

    /* initialize transfer */
    featureParam = (usb_host_process_feature_param_t *)param;
    if (featureParam->requestType == (uint8_t)kRequestDevice)
    {
        transfer->setupPacket->bmRequestType |= USB_REQUEST_TYPE_RECIPIENT_DEVICE;
    }
    else if (featureParam->requestType == (uint8_t)kRequestInterface)
    {
        transfer->setupPacket->bmRequestType |= USB_REQUEST_TYPE_RECIPIENT_INTERFACE;
    }
    else
    {
        transfer->setupPacket->bmRequestType |= USB_REQUEST_TYPE_RECIPIENT_ENDPOINT;
    }
    transfer->setupPacket->wValue = USB_SHORT_TO_LITTLE_ENDIAN(featureParam->featureSelector);
    transfer->setupPacket->wIndex = USB_SHORT_TO_LITTLE_ENDIAN(featureParam->interfaceOrEndpoint);

    return USB_HostCh9RequestCommon(deviceInstance, transfer, NULL, 0);
}

usb_status_t USB_HostStandardSetAddress(usb_host_device_instance_t *deviceInstance,
                                        usb_host_transfer_t *transfer,
                                        void *param)
{
    uint8_t address;

    /* initialize transfer */
    address                       = *(uint8_t *)param;
    transfer->setupPacket->wValue = USB_SHORT_TO_LITTLE_ENDIAN(address);

    return USB_HostCh9RequestCommon(deviceInstance, transfer, NULL, 0);
}

usb_status_t USB_HostStandardSetGetDescriptor(usb_host_device_instance_t *deviceInstance,
                                              usb_host_transfer_t *transfer,
                                              void *param)
{
    usb_host_process_descriptor_param_t *descriptorParam;

    /* initialize transfer */
    descriptorParam               = (usb_host_process_descriptor_param_t *)param;
    transfer->setupPacket->wValue = USB_SHORT_TO_LITTLE_ENDIAN(
        (uint16_t)((uint16_t)descriptorParam->descriptorType << 8) | descriptorParam->descriptorIndex);
    transfer->setupPacket->wIndex = USB_SHORT_TO_LITTLE_ENDIAN(descriptorParam->languageId);
    return USB_HostCh9RequestCommon(deviceInstance, transfer, descriptorParam->descriptorBuffer,
                                    descriptorParam->descriptorLength);
}

usb_status_t USB_HostStandardGetInterface(usb_host_device_instance_t *deviceInstance,
                                          usb_host_transfer_t *transfer,
                                          void *param)
{
    usb_host_get_interface_param_t *interfaceParam;

    /* initialize transfer */
    interfaceParam = (usb_host_get_interface_param_t *)param;
    transfer->setupPacket->bmRequestType |= USB_REQUEST_TYPE_DIR_IN;
    transfer->setupPacket->bmRequestType |= USB_REQUEST_TYPE_RECIPIENT_INTERFACE;
    transfer->setupPacket->wIndex = USB_SHORT_TO_LITTLE_ENDIAN(interfaceParam->interface);

    return USB_HostCh9RequestCommon(deviceInstance, transfer, interfaceParam->alternateInterfaceBuffer, 1);
}

usb_status_t USB_HostStandardSetInterface(usb_host_device_instance_t *deviceInstance,
                                          usb_host_transfer_t *transfer,
                                          void *param)
{
    usb_host_set_interface_param_t *setParam;

    /* initialize transfer */
    setParam = (usb_host_set_interface_param_t *)param;
    transfer->setupPacket->bmRequestType |= USB_REQUEST_TYPE_RECIPIENT_INTERFACE;
    transfer->setupPacket->wIndex = USB_SHORT_TO_LITTLE_ENDIAN(setParam->interface);
    transfer->setupPacket->wValue = USB_SHORT_TO_LITTLE_ENDIAN(setParam->alternateSetting);

    return USB_HostCh9RequestCommon(deviceInstance, transfer, NULL, 0);
}

usb_status_t USB_HostStandardSyncFrame(usb_host_device_instance_t *deviceInstance,
                                       usb_host_transfer_t *transfer,
                                       void *param)
{
    usb_host_synch_frame_param_t *frameParam;

    /* initialize transfer */
    frameParam = (usb_host_synch_frame_param_t *)param;
    transfer->setupPacket->bmRequestType |= USB_REQUEST_TYPE_DIR_IN;
    transfer->setupPacket->bmRequestType |= USB_REQUEST_TYPE_RECIPIENT_ENDPOINT;
    transfer->setupPacket->wIndex = USB_SHORT_TO_LITTLE_ENDIAN(frameParam->endpoint);

    return USB_HostCh9RequestCommon(deviceInstance, transfer, frameParam->frameNumberBuffer, 2);
}

usb_status_t USB_HostRequestControl(usb_device_handle deviceHandle,
                                    uint8_t usbRequest,
                                    usb_host_transfer_t *transfer,
                                    void *param)
{
    usb_host_device_instance_t *deviceInstance = (usb_host_device_instance_t *)deviceHandle;
    usb_status_t status                        = kStatus_USB_Error;

    if (deviceHandle == NULL)
    {
        return kStatus_USB_InvalidHandle;
    }

    /* reset transfer fields */
    transfer->setupPacket->bmRequestType = 0x00;
    transfer->setupPacket->bRequest      = usbRequest;
    transfer->setupPacket->wIndex        = 0;
    transfer->setupPacket->wLength       = 0;
    transfer->setupPacket->wValue        = 0;

    switch (usbRequest)
    {
        case USB_REQUEST_STANDARD_GET_STATUS: /* standard get status request */
            status = USB_HostStandardGetStatus(deviceInstance, transfer, param);
            break;

        case USB_REQUEST_STANDARD_CLEAR_FEATURE: /* standard clear status request */
        case USB_REQUEST_STANDARD_SET_FEATURE:   /* standard set feature request */
            status = USB_HostStandardSetClearFeature(deviceInstance, transfer, param);
            break;

        case USB_REQUEST_STANDARD_SET_ADDRESS: /* standard set address request */
            status = USB_HostStandardSetAddress(deviceInstance, transfer, param);
            break;

        case USB_REQUEST_STANDARD_GET_DESCRIPTOR: /* standard get descriptor request */
        case USB_REQUEST_STANDARD_SET_DESCRIPTOR: /* standard set descriptor request */
            if (usbRequest == USB_REQUEST_STANDARD_GET_DESCRIPTOR)
            {
                transfer->setupPacket->bmRequestType |= USB_REQUEST_TYPE_DIR_IN;
            }
            status = USB_HostStandardSetGetDescriptor(deviceInstance, transfer, param);
            break;

        case USB_REQUEST_STANDARD_GET_CONFIGURATION: /* standard get configuration descriptor request */
            transfer->setupPacket->bmRequestType |= USB_REQUEST_TYPE_DIR_IN;
            status =
                USB_HostCh9RequestCommon((usb_host_device_instance_t *)deviceHandle, transfer, (uint8_t *)param, 1);
            break;

        case USB_REQUEST_STANDARD_SET_CONFIGURATION: /* standard set configuration request */
            transfer->setupPacket->wValue = USB_SHORT_TO_LITTLE_ENDIAN(*((uint8_t *)param));
            status = USB_HostCh9RequestCommon((usb_host_device_instance_t *)deviceHandle, transfer, NULL, 0);
            break;

        case USB_REQUEST_STANDARD_GET_INTERFACE: /* standard get interface request */
            status = USB_HostStandardGetInterface(deviceInstance, transfer, param);
            break;

        case USB_REQUEST_STANDARD_SET_INTERFACE: /* standard set interface request */
            status = USB_HostStandardSetInterface(deviceInstance, transfer, param);
            break;

        case USB_REQUEST_STANDARD_SYNCH_FRAME: /* standard synch frame request */
            status = USB_HostStandardSyncFrame(deviceInstance, transfer, param);
            break;

        default:
            /*no action*/
            break;
    }

    return status;
}
