/*
 * The Clear BSD License
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "usb_device_config.h"
#include "usb.h"

#include "usb_device.h"
#include "usb_device_dci.h"
#include "usb_device_ch9.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Standard request callback function typedef.
 *
 * This function is used to handle the standard request.
 *
 * @param handle          The device handle. It equals the value returned from USB_DeviceInit.
 * @param setup           The pointer of the setup packet.
 * @param buffer          It is an out parameter, is used to save the buffer address to response the host's request.
 * @param length          It is an out parameter, the data length.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
typedef usb_status_t (*usb_standard_request_callback_t)(usb_device_handle handle,
                                                        usb_setup_struct_t *setup,
                                                        uint8_t **buffer,
                                                        uint32_t *length);

/*******************************************************************************
* Prototypes
******************************************************************************/
/*!
 * @brief Get the setup packet buffer.
 *
 * The function is used to get the setup packet buffer to save the setup packet data.
 *
 * @param handle              The device handle.
 * @param setupBuffer        It is an OUT parameter, return the setup buffer address to the caller.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
extern usb_status_t USB_DeviceGetSetupBuffer(usb_device_handle handle, usb_setup_struct_t **setupBuffer);

/*!
 * @brief Handle the class request.
 *
 * The function is used to handle the class request.
 *
 * @param handle              The device handle.
 * @param setup               The setup packet buffer address.
 * @param length              It is an OUT parameter, return the data length need to be sent to host.
 * @param buffer              It is an OUT parameter, return the data buffer address.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
extern usb_status_t USB_DeviceProcessClassRequest(usb_device_handle handle,
                                                  usb_setup_struct_t *setup,
                                                  uint32_t *length,
                                                  uint8_t **buffer);

/*!
 * @brief Get the buffer to save the class specific data sent from host.
 *
 * The function is used to get the buffer to save the class specific data sent from host.
 * The function will be called when the device receives a setup pakcet, and the host needs to send data to the device in
 * the data stage.
 *
 * @param handle              The device handle.
 * @param setup               The setup packet buffer address.
 * @param length              Pass the length the host needs to sent.
 * @param buffer              It is an OUT parameter, return the data buffer address to save the host's data.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
extern usb_status_t USB_DeviceGetClassReceiveBuffer(usb_device_handle handle,
                                                    usb_setup_struct_t *setup,
                                                    uint32_t *length,
                                                    uint8_t **buffer);

/* standard request */
/*!
 * @brief Get the descritpor.
 *
 * The function is used to get the descritpor, including the device descritpor, configuration descriptor, and string
 * descriptor, etc.
 *
 * @param handle              The device handle.
 * @param setup               The setup packet buffer address.
 * @param length              It is an OUT parameter, return the data length need to be sent to host.
 * @param buffer              It is an OUT parameter, return the data buffer address.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
extern usb_status_t USB_DeviceGetDescriptor(usb_device_handle handle,
                                            usb_setup_struct_t *setup,
                                            uint32_t *length,
                                            uint8_t **buffer);

/*!
 * @brief Set the device configuration.
 *
 * The function is used to set the device configuration.
 *
 * @param handle              The device handle.
 * @param configure           The configuration value.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
extern usb_status_t USB_DeviceSetConfigure(usb_device_handle handle, uint8_t configure);

/*!
 * @brief Get the device configuration.
 *
 * The function is used to get the device configuration.
 *
 * @param handle              The device handle.
 * @param configure           It is an OUT parameter, save the current configuration value.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
extern usb_status_t USB_DeviceGetConfigure(usb_device_handle handle, uint8_t *configure);

/*!
 * @brief Set an interface alternate setting.
 *
 * The function is used to set an interface alternate setting.
 *
 * @param handle              The device handle.
 * @param interface           The interface index.
 * @param alternateSetting   The new alternate setting value.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
extern usb_status_t USB_DeviceSetInterface(usb_device_handle handle, uint8_t interface, uint8_t alternateSetting);

/*!
 * @brief Get an interface alternate setting.
 *
 * The function is used to get an interface alternate setting.
 *
 * @param handle              The device handle.
 * @param interface           The interface index.
 * @param alternateSetting   It is an OUT parameter, save the new alternate setting value of the interface.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
extern usb_status_t USB_DeviceGetInterface(usb_device_handle handle, uint8_t interface, uint8_t *alternateSetting);

/*!
 * @brief Configure a specified endpoint status.
 *
 * The function is used to configure a specified endpoint status, idle or halt.
 *
 * @param handle              The device handle.
 * @param endpointAddress    The endpoint address, the BIT7 is the direction, 0 - USB_OUT, 1 - USB_IN.
 * @param status              The new status of the endpoint, 0 - idle, 1 - halt.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
extern usb_status_t USB_DeviceConfigureEndpointStatus(usb_device_handle handle,
                                                      uint8_t endpointAddress,
                                                      uint8_t status);

/*!
 * @brief Configure the device remote wakeup feature.
 *
 * The function is used to configure the device remote wakeup feature, enable or disbale the remote wakeup feature.
 *
 * @param handle              The device handle.
 * @param enable              The new feature value of the device remote wakeup, 0 - disable, 1 - enable.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
extern usb_status_t USB_DeviceConfigureRemoteWakeup(usb_device_handle handle, uint8_t enable);

static usb_status_t USB_DeviceCh9GetStatus(usb_device_handle handle,
                                           usb_setup_struct_t *setup,
                                           uint8_t **buffer,
                                           uint32_t *length);
static usb_status_t USB_DeviceCh9SetClearFeature(usb_device_handle handle,
                                                 usb_setup_struct_t *setup,
                                                 uint8_t **buffer,
                                                 uint32_t *length);
static usb_status_t USB_DeviceCh9SetAddress(usb_device_handle handle,
                                            usb_setup_struct_t *setup,
                                            uint8_t **buffer,
                                            uint32_t *length);
static usb_status_t USB_DeviceCh9GetDescriptor(usb_device_handle handle,
                                               usb_setup_struct_t *setup,
                                               uint8_t **buffer,
                                               uint32_t *length);
static usb_status_t USB_DeviceCh9GetConfiguration(usb_device_handle handle,
                                                  usb_setup_struct_t *setup,
                                                  uint8_t **buffer,
                                                  uint32_t *length);
static usb_status_t USB_DeviceCh9SetConfiguration(usb_device_handle handle,
                                                  usb_setup_struct_t *setup,
                                                  uint8_t **buffer,
                                                  uint32_t *length);
static usb_status_t USB_DeviceCh9GetInterface(usb_device_handle handle,
                                              usb_setup_struct_t *setup,
                                              uint8_t **buffer,
                                              uint32_t *length);
static usb_status_t USB_DeviceCh9SetInterface(usb_device_handle handle,
                                              usb_setup_struct_t *setup,
                                              uint8_t **buffer,
                                              uint32_t *length);
static usb_status_t USB_DeviceCh9SynchFrame(usb_device_handle handle,
                                            usb_setup_struct_t *setup,
                                            uint8_t **buffer,
                                            uint32_t *length);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* The function list to handle the standard request. */
static const usb_standard_request_callback_t s_UsbDeviceStandardRequest[] = {
    USB_DeviceCh9GetStatus,
    USB_DeviceCh9SetClearFeature,
    (usb_standard_request_callback_t)NULL,
    USB_DeviceCh9SetClearFeature,
    (usb_standard_request_callback_t)NULL,
    USB_DeviceCh9SetAddress,
    USB_DeviceCh9GetDescriptor,
    (usb_standard_request_callback_t)NULL, /* USB_DeviceCh9SetDescriptor */
    USB_DeviceCh9GetConfiguration,
    USB_DeviceCh9SetConfiguration,
    USB_DeviceCh9GetInterface,
    USB_DeviceCh9SetInterface,
    USB_DeviceCh9SynchFrame,
};

/*
 * The internal global variable.
 * This variable is used in:
 *           get status request
 *           get configuration request
 *           get interface request
 *           set interface request
 *           get sync frame request
 */
static uint16_t s_UsbDeviceStandardRx;

/*******************************************************************************
* Code
******************************************************************************/
/*!
 * @brief Handle get status request.
 *
 * This function is used to handle get status request.
 *
 * @param handle          The device handle. It equals the value returned from USB_DeviceInit.
 * @param setup           The pointer of the setup packet.
 * @param buffer          It is an out parameter, is used to save the buffer address to response the host's request.
 * @param length          It is an out parameter, the data length.
 *
 * @retval kStatus_USB_Success              The requst is handled successfully.
 * @retval kStatus_USB_InvalidRequest       The request can not be handle in current device state,
 *                                          or, the request is unsupported.
 */
static usb_status_t USB_DeviceCh9GetStatus(usb_device_handle handle,
                                           usb_setup_struct_t *setup,
                                           uint8_t **buffer,
                                           uint32_t *length)
{
    usb_status_t error = kStatus_USB_InvalidRequest;
    uint8_t state;

    USB_DeviceGetStatus(handle, kUSB_DeviceStatusDeviceState, &state);

    if ((kUSB_DeviceStateAddress != state) && (kUSB_DeviceStateConfigured != state))
    {
        return error;
    }

    if ((setup->bmRequestType & USB_REQUEST_TYPE_RECIPIENT_MASK) == USB_REQUEST_TYPE_RECIPIENT_DEVICE)
    {
        /* Get the device status */
        error = USB_DeviceGetStatus(handle, kUSB_DeviceStatusDevice, &s_UsbDeviceStandardRx);
        s_UsbDeviceStandardRx = s_UsbDeviceStandardRx & USB_GET_STATUS_DEVICE_MASK;
        s_UsbDeviceStandardRx = USB_SHORT_TO_LITTLE_ENDIAN(s_UsbDeviceStandardRx);
        /* The device status length must be USB_DEVICE_STATUS_SIZE. */
        *length = USB_DEVICE_STATUS_SIZE;
    }
    else if ((setup->bmRequestType & USB_REQUEST_TYPE_RECIPIENT_MASK) == USB_REQUEST_TYPE_RECIPIENT_INTERFACE)
    {
        /* Get the interface status */
        error = kStatus_USB_Success;
        s_UsbDeviceStandardRx = 0U;
        /* The interface status length must be USB_INTERFACE_STATUS_SIZE. */
        *length = USB_INTERFACE_STATUS_SIZE;
    }
    else if ((setup->bmRequestType & USB_REQUEST_TYPE_RECIPIENT_MASK) == USB_REQUEST_TYPE_RECIPIENT_ENDPOINT)
    {
        /* Get the endpoint status */
        usb_device_endpoint_status_struct_t endpointStatus;
        endpointStatus.endpointAddress = (uint8_t)setup->wIndex;
        endpointStatus.endpointStatus = kUSB_DeviceEndpointStateIdle;
        error = USB_DeviceGetStatus(handle, kUSB_DeviceStatusEndpoint, &endpointStatus);
        s_UsbDeviceStandardRx = endpointStatus.endpointStatus & USB_GET_STATUS_ENDPOINT_MASK;
        s_UsbDeviceStandardRx = USB_SHORT_TO_LITTLE_ENDIAN(s_UsbDeviceStandardRx);
        /* The endpoint status length must be USB_INTERFACE_STATUS_SIZE. */
        *length = USB_ENDPOINT_STATUS_SIZE;
    }
    else
    {
    }
    *buffer = (uint8_t *)&s_UsbDeviceStandardRx;

    return error;
}

/*!
 * @brief Handle set or clear device feature request.
 *
 * This function is used to handle set or clear device feature request.
 *
 * @param handle          The device handle. It equals the value returned from USB_DeviceInit.
 * @param setup           The pointer of the setup packet.
 * @param buffer          It is an out parameter, is used to save the buffer address to response the host's request.
 * @param length          It is an out parameter, the data length.
 *
 * @retval kStatus_USB_Success              The requst is handled successfully.
 * @retval kStatus_USB_InvalidRequest       The request can not be handle in current device state,
 *                                          or, the request is unsupported.
 */
static usb_status_t USB_DeviceCh9SetClearFeature(usb_device_handle handle,
                                                 usb_setup_struct_t *setup,
                                                 uint8_t **buffer,
                                                 uint32_t *length)
{
    usb_status_t error = kStatus_USB_InvalidRequest;
    uint8_t state;
    uint8_t isSet = 0U;

    USB_DeviceGetStatus(handle, kUSB_DeviceStatusDeviceState, &state);

    if ((kUSB_DeviceStateAddress != state) && (kUSB_DeviceStateConfigured != state))
    {
        return error;
    }

    /* Identify the request is set or clear the feature. */
    if (USB_REQUEST_STANDARD_SET_FEATURE == setup->bRequest)
    {
        isSet = 1U;
    }

    if ((setup->bmRequestType & USB_REQUEST_TYPE_RECIPIENT_MASK) == USB_REQUEST_TYPE_RECIPIENT_DEVICE)
    {
        /* Set or Clear the device featrue. */
        if (USB_REQUEST_STANDARD_FEATURE_SELECTOR_DEVICE_REMOTE_WAKEUP == setup->wValue)
        {
            /* Set or Clear the device remote wakeup featrue. */
            error = USB_DeviceConfigureRemoteWakeup(handle, isSet);
        }
#if (defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0U)) && \
    (defined(USB_DEVICE_CONFIG_EHCI_TEST_MODE) && (USB_DEVICE_CONFIG_EHCI_TEST_MODE > 0U))
        else if (USB_REQUEST_STANDARD_FEATURE_SELECTOR_DEVICE_TEST_MODE == setup->wValue)
        {
            state = kUSB_DeviceStateTestMode;
            error = USB_DeviceSetStatus(classHandle->handle, kUSB_DeviceStatusDeviceState, &state);
        }
#endif
        else
        {
        }
    }
    else if ((setup->bmRequestType & USB_REQUEST_TYPE_RECIPIENT_MASK) == USB_REQUEST_TYPE_RECIPIENT_ENDPOINT)
    {
        /* Set or Clear the endpoint featrue. */
        if (USB_REQUEST_STANDARD_FEATURE_SELECTOR_ENDPOINT_HALT == setup->wValue)
        {
            if (USB_CONTROL_ENDPOINT == (setup->wIndex & USB_ENDPOINT_NUMBER_MASK))
            {
                /* Set or Clear the control endpoint status(halt or not). */
                if (isSet)
                {
                    USB_DeviceStallEndpoint(handle, (uint8_t)setup->wIndex);
                }
                else
                {
                    USB_DeviceUnstallEndpoint(handle, (uint8_t)setup->wIndex);
                }
            }

            /* Set or Clear the endpoint status featrue. */
            error = USB_DeviceConfigureEndpointStatus(handle, setup->wIndex, isSet);
        }
        else
        {
        }
    }
    else
    {
    }

    return error;
}

/*!
 * @brief Handle set address request.
 *
 * This function is used to handle set address request.
 *
 * @param handle          The device handle. It equals the value returned from USB_DeviceInit.
 * @param setup           The pointer of the setup packet.
 * @param buffer          It is an out parameter, is used to save the buffer address to response the host's request.
 * @param length          It is an out parameter, the data length.
 *
 * @retval kStatus_USB_Success              The requst is handled successfully.
 * @retval kStatus_USB_InvalidRequest       The request can not be handle in current device state.
 */
static usb_status_t USB_DeviceCh9SetAddress(usb_device_handle handle,
                                            usb_setup_struct_t *setup,
                                            uint8_t **buffer,
                                            uint32_t *length)
{
    usb_status_t error = kStatus_USB_InvalidRequest;
    uint8_t state;

    USB_DeviceGetStatus(handle, kUSB_DeviceStatusDeviceState, &state);

    if ((kUSB_DeviceStateAddressing != state) && (kUSB_DeviceStateAddress != state) &&
        (kUSB_DeviceStateDefault != state))
    {
        return error;
    }

    if (kUSB_DeviceStateAddressing != state)
    {
        /* If the device address is not setting, pass the address and the device state will change to
         * kUSB_DeviceStateAddressing internally. */
        state = setup->wValue & 0xFFU;
        error = USB_DeviceSetStatus(handle, kUSB_DeviceStatusAddress, &state);
    }
    else
    {
        /* If the device address is setting, set device address and the address will be write into the controller
         * internally. */
        error = USB_DeviceSetStatus(handle, kUSB_DeviceStatusAddress, NULL);
        /* And then change the device state to kUSB_DeviceStateAddress. */
        if (kStatus_USB_Success == error)
        {
            state = kUSB_DeviceStateAddress;
            error = USB_DeviceSetStatus(handle, kUSB_DeviceStatusDeviceState, &state);
        }
    }

    return error;
}

/*!
 * @brief Handle get descriptor request.
 *
 * This function is used to handle get descriptor request.
 *
 * @param handle          The device handle. It equals the value returned from USB_DeviceInit.
 * @param setup           The pointer of the setup packet.
 * @param buffer          It is an out parameter, is used to save the buffer address to response the host's request.
 * @param length          It is an out parameter, the data length.
 *
 * @retval kStatus_USB_Success              The requst is handled successfully.
 * @retval kStatus_USB_InvalidRequest       The request can not be handle in current device state,
 *                                          or, the request is unsupported.
 */
static usb_status_t USB_DeviceCh9GetDescriptor(usb_device_handle handle,
                                               usb_setup_struct_t *setup,
                                               uint8_t **buffer,
                                               uint32_t *length)
{
    uint8_t state;

    USB_DeviceGetStatus(handle, kUSB_DeviceStatusDeviceState, &state);

    if ((kUSB_DeviceStateAddress != state) && (kUSB_DeviceStateConfigured != state) &&
        (kUSB_DeviceStateDefault != state))
    {
        return kStatus_USB_InvalidRequest;
    }

    return USB_DeviceGetDescriptor(handle, setup, length, buffer);
}

/*!
 * @brief Handle get current configuration request.
 *
 * This function is used to handle get current configuration request.
 *
 * @param handle          The device handle. It equals the value returned from USB_DeviceInit.
 * @param setup           The pointer of the setup packet.
 * @param buffer          It is an out parameter, is used to save the buffer address to response the host's request.
 * @param length          It is an out parameter, the data length.
 *
 * @retval kStatus_USB_Success              The requst is handled successfully.
 * @retval kStatus_USB_InvalidRequest       The request can not be handle in current device state,
 *                                          or, the request is unsupported.
 */
static usb_status_t USB_DeviceCh9GetConfiguration(usb_device_handle handle,
                                                  usb_setup_struct_t *setup,
                                                  uint8_t **buffer,
                                                  uint32_t *length)
{
    uint8_t state;

    USB_DeviceGetStatus(handle, kUSB_DeviceStatusDeviceState, &state);

    if ((kUSB_DeviceStateAddress != state) && ((kUSB_DeviceStateConfigured != state)))
    {
        return kStatus_USB_InvalidRequest;
    }

    *length = USB_CONFIGURE_SIZE;
    *buffer = (uint8_t *)&s_UsbDeviceStandardRx;
    return USB_DeviceGetConfigure(handle, (uint8_t *)&s_UsbDeviceStandardRx);
}

/*!
 * @brief Handle set current configuration request.
 *
 * This function is used to handle set current configuration request.
 *
 * @param handle          The device handle. It equals the value returned from USB_DeviceInit.
 * @param setup           The pointer of the setup packet.
 * @param buffer          It is an out parameter, is used to save the buffer address to response the host's request.
 * @param length          It is an out parameter, the data length.
 *
 * @retval kStatus_USB_Success              The requst is handled successfully.
 * @retval kStatus_USB_InvalidRequest       The request can not be handle in current device state,
 *                                          or, the request is unsupported.
 */
static usb_status_t USB_DeviceCh9SetConfiguration(usb_device_handle handle,
                                                  usb_setup_struct_t *setup,
                                                  uint8_t **buffer,
                                                  uint32_t *length)
{
    uint8_t state;

    USB_DeviceGetStatus(handle, kUSB_DeviceStatusDeviceState, &state);

    if ((kUSB_DeviceStateAddress != state) && (kUSB_DeviceStateConfigured != state))
    {
        return kStatus_USB_InvalidRequest;
    }

    /* The device state is changed to kUSB_DeviceStateConfigured */
    state = kUSB_DeviceStateConfigured;
    USB_DeviceSetStatus(handle, kUSB_DeviceStatusDeviceState, &state);
    if (!setup->wValue)
    {
        /* If the new configuration is zero, the device state is changed to kUSB_DeviceStateAddress */
        state = kUSB_DeviceStateAddress;
        USB_DeviceSetStatus(handle, kUSB_DeviceStatusDeviceState, &state);
    }

    return USB_DeviceSetConfigure(handle, setup->wValue);
}

/*!
 * @brief Handle get the alternate setting of a interface request.
 *
 * This function is used to handle get the alternate setting of a interface request.
 *
 * @param handle          The device handle. It equals the value returned from USB_DeviceInit.
 * @param setup           The pointer of the setup packet.
 * @param buffer          It is an out parameter, is used to save the buffer address to response the host's request.
 * @param length          It is an out parameter, the data length.
 *
 * @retval kStatus_USB_Success              The requst is handled successfully.
 * @retval kStatus_USB_InvalidRequest       The request can not be handle in current device state,
 *                                          or, the request is unsupported.
 */
static usb_status_t USB_DeviceCh9GetInterface(usb_device_handle handle,
                                              usb_setup_struct_t *setup,
                                              uint8_t **buffer,
                                              uint32_t *length)
{
    usb_status_t error = kStatus_USB_InvalidRequest;
    uint8_t state;

    USB_DeviceGetStatus(handle, kUSB_DeviceStatusDeviceState, &state);

    if (state != kUSB_DeviceStateConfigured)
    {
        return error;
    }
    *length = USB_INTERFACE_SIZE;
    *buffer = (uint8_t *)&s_UsbDeviceStandardRx;

    return USB_DeviceGetInterface(handle, setup->wIndex & 0xFFU, (uint8_t *)&s_UsbDeviceStandardRx);
}

/*!
 * @brief Handle set the alternate setting of a interface request.
 *
 * This function is used to handle set the alternate setting of a interface request.
 *
 * @param handle          The device handle. It equals the value returned from USB_DeviceInit.
 * @param setup           The pointer of the setup packet.
 * @param buffer          It is an out parameter, is used to save the buffer address to response the host's request.
 * @param length          It is an out parameter, the data length.
 *
 * @retval kStatus_USB_Success              The requst is handled successfully.
 * @retval kStatus_USB_InvalidRequest       The request can not be handle in current device state,
 *                                          or, the request is unsupported.
 */
static usb_status_t USB_DeviceCh9SetInterface(usb_device_handle handle,
                                              usb_setup_struct_t *setup,
                                              uint8_t **buffer,
                                              uint32_t *length)
{
    uint8_t state;

    USB_DeviceGetStatus(handle, kUSB_DeviceStatusDeviceState, &state);

    if (state != kUSB_DeviceStateConfigured)
    {
        return kStatus_USB_InvalidRequest;
    }

    return USB_DeviceSetInterface(handle, (setup->wIndex & 0xFFU), (setup->wValue & 0xFFU));
}

/*!
 * @brief Handle get sync frame request.
 *
 * This function is used to handle get sync frame request.
 *
 * @param handle          The device handle. It equals the value returned from USB_DeviceInit.
 * @param setup           The pointer of the setup packet.
 * @param buffer          It is an out parameter, is used to save the buffer address to response the host's request.
 * @param length          It is an out parameter, the data length.
 *
 * @retval kStatus_USB_Success              The requst is handled successfully.
 * @retval kStatus_USB_InvalidRequest       The request can not be handle in current device state,
 *                                          or, the request is unsupported.
 */
static usb_status_t USB_DeviceCh9SynchFrame(usb_device_handle handle,
                                            usb_setup_struct_t *setup,
                                            uint8_t **buffer,
                                            uint32_t *length)
{
    usb_status_t error = kStatus_USB_InvalidRequest;
    uint8_t state;

    USB_DeviceGetStatus(handle, kUSB_DeviceStatusDeviceState, &state);

    if (state != kUSB_DeviceStateConfigured)
    {
        return error;
    }

    s_UsbDeviceStandardRx = setup->wIndex;
    /* Get the sync frame value */
    error = USB_DeviceGetStatus(handle, kUSB_DeviceStatusSynchFrame, &s_UsbDeviceStandardRx);
    *buffer = (uint8_t *)&s_UsbDeviceStandardRx;
    *length = sizeof(s_UsbDeviceStandardRx);

    return error;
}

/*!
 * @brief Send the reponse to the host.
 *
 * This function is used to send the reponse to the host.
 *
 * There are two cases this function will be called.
 * Case one when a setup packet is received in control endpoint callback function:
 *        1. If there is not data phase in the setup transfer, the function will prime an IN transfer with the data
 * length is zero for status phase.
 *        2. If there is an IN data phase, the function will prime an OUT transfer with the actual length to need to
 * send for data phase. And then prime an IN transfer with the data length is zero for status phase.
 *        3. If there is an OUT data phase, the function will prime an IN transfer with the actual length to want to
 * receive for data phase.
 *
 * Case two when is not a setup packet received in control endpoint callback function:
 *        1. The function will prime an IN transfer with data length is zero for status phase.
 *
 * @param handle          The device handle. It equals the value returned from USB_DeviceInit.
 * @param setup           The pointer of the setup packet.
 * @param error           The error code returned from the standard request fucntion.
 * @param stage           The stage of the control transfer.
 * @param buffer          It is an out parameter, is used to save the buffer address to response the host's request.
 * @param length          It is an out parameter, the data length.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
static usb_status_t USB_DeviceControlCallbackFeedback(usb_device_handle handle,
                                                      usb_setup_struct_t *setup,
                                                      usb_status_t error,
                                                      usb_device_control_read_write_sequence_t stage,
                                                      uint8_t **buffer,
                                                      uint32_t *length)
{
    usb_status_t errorCode = kStatus_USB_Error;
    uint8_t direction = USB_IN;

    if (kStatus_USB_InvalidRequest == error)
    {
        /* Stall the control pipe when the request is unsupported. */
        if ((!((setup->bmRequestType & USB_REQUEST_TYPE_TYPE_MASK) == USB_REQUEST_TYPE_TYPE_STANDARD)) &&
            ((setup->bmRequestType & USB_REQUEST_TYPE_DIR_MASK) == USB_REQUEST_TYPE_DIR_OUT) && (setup->wLength) &&
            (kUSB_DeviceControlPipeSetupStage == stage))
        {
            direction = USB_OUT;
        }
        errorCode = USB_DeviceStallEndpoint(
            handle,
            (USB_CONTROL_ENDPOINT) | (uint8_t)((uint32_t)direction << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT));
    }
    else
    {
        if (*length > setup->wLength)
        {
            *length = setup->wLength;
        }
        errorCode = USB_DeviceSendRequest(handle, (USB_CONTROL_ENDPOINT), *buffer, *length);

        if ((kStatus_USB_Success == errorCode) &&
            (USB_REQUEST_TYPE_DIR_IN == (setup->bmRequestType & USB_REQUEST_TYPE_DIR_MASK)))
        {
            errorCode = USB_DeviceRecvRequest(handle, (USB_CONTROL_ENDPOINT), (uint8_t *)NULL, 0U);
        }
    }
    return errorCode;
}

/*!
 * @brief Control endpoint callback function.
 *
 * This callback function is used to notify uplayer the tranfser result of a transfer.
 * This callback pointer is passed when a sepcified endpoint initialied by calling API USB_DeviceInitEndpoint.
 *
 * @param handle          The device handle. It equals the value returned from USB_DeviceInit.
 * @param message         The result of a transfer, includes transfer buffer, transfer length and whether is in setup
 * phase for control pipe.
 * @param callbackParam  The paramter for this callback. It is same with
 * usb_device_endpoint_callback_struct_t::callbackParam.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceControlCallback(usb_device_handle handle,
                                       usb_device_endpoint_callback_message_struct_t *message,
                                       void *callbackParam)
{
    usb_setup_struct_t *deviceSetup;
    uint8_t *setupOutBuffer;
    uint8_t *buffer = (uint8_t *)NULL;
    uint32_t length = 0U;
    usb_status_t error = kStatus_USB_InvalidRequest;
    uint8_t state;

    if (USB_UNINITIALIZED_VAL_32 == message->length)
    {
        return error;
    }

    USB_DeviceGetSetupBuffer(handle, &deviceSetup);
    USB_DeviceGetStatus(handle, kUSB_DeviceStatusDeviceState, &state);

    if (message->isSetup)
    {
        if ((USB_SETUP_PACKET_SIZE != message->length) || (NULL == message->buffer))
        {
            /* If a invalid setup is received, the control pipes should be de-init and init again.
             * Due to the IP can not meet this require, it is revesed for feature.
             */
            /*
            USB_DeviceDeinitEndpoint(handle,
                         USB_CONTROL_ENDPOINT | (USB_IN << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT));
            USB_DeviceDeinitEndpoint(handle,
                         USB_CONTROL_ENDPOINT | (USB_OUT << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT));
            USB_DeviceControlPipeInit(handle);
            */
            return error;
        }
        /* Receive a setup request */
        usb_setup_struct_t *setup = (usb_setup_struct_t *)(message->buffer);
        /* Copy the setup packet to the application buffer */
        deviceSetup->wValue = USB_SHORT_FROM_LITTLE_ENDIAN(setup->wValue);
        deviceSetup->wIndex = USB_SHORT_FROM_LITTLE_ENDIAN(setup->wIndex);
        deviceSetup->wLength = USB_SHORT_FROM_LITTLE_ENDIAN(setup->wLength);
        deviceSetup->bRequest = setup->bRequest;
        deviceSetup->bmRequestType = setup->bmRequestType;

        if ((deviceSetup->bmRequestType & USB_REQUEST_TYPE_TYPE_MASK) == USB_REQUEST_TYPE_TYPE_STANDARD)
        {
            /* Handle the standard request */
            if (s_UsbDeviceStandardRequest[deviceSetup->bRequest] != (usb_standard_request_callback_t)NULL)
            {
                error = s_UsbDeviceStandardRequest[deviceSetup->bRequest](handle, deviceSetup, &buffer, &length);
            }
        }
        else
        {
            if ((deviceSetup->wLength) &&
                ((deviceSetup->bmRequestType & USB_REQUEST_TYPE_DIR_MASK) == USB_REQUEST_TYPE_DIR_OUT))
            {
                /* Class or vendor request with the OUT data phase. */
                if ((deviceSetup->wLength) &&
                    ((deviceSetup->bmRequestType & USB_REQUEST_TYPE_TYPE_CLASS) == USB_REQUEST_TYPE_TYPE_CLASS))
                {
                    /* Get data buffer to receive the data from the host. */
                    length = deviceSetup->wLength;
                    error = USB_DeviceGetClassReceiveBuffer(handle, deviceSetup, &length, &setupOutBuffer);
                    length = 0U;
                }
                else
                {
                }
                if (kStatus_USB_Success == error)
                {
                    /* Prime an OUT transfer */
                    error = USB_DeviceRecvRequest(handle, USB_CONTROL_ENDPOINT, setupOutBuffer, deviceSetup->wLength);
                    return error;
                }
            }
            else
            {
                /* Class or vendor request with the IN data phase. */
                if (((deviceSetup->bmRequestType & USB_REQUEST_TYPE_TYPE_CLASS) == USB_REQUEST_TYPE_TYPE_CLASS))
                {
                    /* Get data buffer to response the host. */
                    error = USB_DeviceProcessClassRequest(handle, deviceSetup, &length, &buffer);
                }
                else
                {
                }
            }
        }
        /* Send the reponse to the host. */
        error = USB_DeviceControlCallbackFeedback(handle, deviceSetup, error, kUSB_DeviceControlPipeSetupStage, &buffer,
                                                  &length);
    }
    else if (kUSB_DeviceStateAddressing == state)
    {
        /* Set the device address to controller. */
        error = s_UsbDeviceStandardRequest[deviceSetup->bRequest](handle, deviceSetup, &buffer, &length);
    }
#if (defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0U)) && \
    (defined(USB_DEVICE_CONFIG_EHCI_TEST_MODE) && (USB_DEVICE_CONFIG_EHCI_TEST_MODE > 0U))
    else if (kUSB_DeviceStateTestMode == state)
    {
        uint8_t portTestControl = (uint8_t)(deviceSetup->wIndex >> 8);
        /* Set the controller.into test mode. */
        error = USB_DeviceSetStatus(handle, kUSB_DeviceStatusTestMode, &portTestControl);
    }
#endif
    else if ((message->length) && (deviceSetup->wLength) &&
             ((deviceSetup->bmRequestType & USB_REQUEST_TYPE_DIR_MASK) == USB_REQUEST_TYPE_DIR_OUT))
    {
        if (((deviceSetup->bmRequestType & USB_REQUEST_TYPE_TYPE_CLASS) == USB_REQUEST_TYPE_TYPE_CLASS))
        {
            /* Data received in OUT phase, and notify the class driver. */
            error = USB_DeviceProcessClassRequest(handle, deviceSetup, &message->length, &message->buffer);
        }
        else
        {
        }
        /* Send the reponse to the host. */
        error = USB_DeviceControlCallbackFeedback(handle, deviceSetup, error, kUSB_DeviceControlPipeDataStage, &buffer,
                                                  &length);
    }
    else
    {
    }
    return error;
}

/*!
 * @brief Control endpoint initialization function.
 *
 * This callback function is used to initialize the control pipes.
 *
 * @param handle          The device handle. It equals the value returned from USB_DeviceInit.
 * @param param           The up layer handle.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceControlPipeInit(usb_device_handle handle)
{
    usb_device_endpoint_init_struct_t epInitStruct;
    usb_device_endpoint_callback_struct_t endpointCallback;
    usb_status_t error;

    endpointCallback.callbackFn = USB_DeviceControlCallback;
    endpointCallback.callbackParam = handle;

    epInitStruct.zlt = 1U;
    epInitStruct.transferType = USB_ENDPOINT_CONTROL;
    epInitStruct.endpointAddress = USB_CONTROL_ENDPOINT | (USB_IN << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT);
    epInitStruct.maxPacketSize = USB_CONTROL_MAX_PACKET_SIZE;
    /* Initialize the control IN pipe */
    error = USB_DeviceInitEndpoint(handle, &epInitStruct, &endpointCallback);

    if (kStatus_USB_Success != error)
    {
        return error;
    }
    epInitStruct.endpointAddress = USB_CONTROL_ENDPOINT | (USB_OUT << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT);
    /* Initialize the control OUT pipe */
    error = USB_DeviceInitEndpoint(handle, &epInitStruct, &endpointCallback);

    if (kStatus_USB_Success != error)
    {
        USB_DeviceDeinitEndpoint(handle,
                                 USB_CONTROL_ENDPOINT | (USB_IN << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT));
        return error;
    }

    return kStatus_USB_Success;
}
