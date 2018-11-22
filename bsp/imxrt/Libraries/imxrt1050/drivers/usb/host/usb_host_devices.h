/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
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

#ifndef _USB_HOST_DEV_MNG_H_
#define _USB_HOST_DEV_MNG_H_

#include "usb_host.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @addtogroup usb_host_drv
 * @{
 */
/*! @brief States of device instances enumeration */
typedef enum _usb_host_device_enumeration_status
{
    kStatus_DEV_Notinit = 0, /*!< Device is invalid */
    kStatus_DEV_Initial,     /*!< Device has been processed by host driver */
    kStatus_DEV_GetDes8,     /*!< Enumeration process: get 8 bytes' device descriptor */
    kStatus_DEV_SetAddress,  /*!< Enumeration process: set device address */
    kStatus_DEV_GetDes,      /*!< Enumeration process: get device descriptor */
    kStatus_DEV_GetCfg9,     /*!< Enumeration process: get 9 bytes' configuration descriptor */
    kStatus_DEV_GetCfg,      /*!< Enumeration process: get configuration descriptor */
    kStatus_DEV_SetCfg,      /*!< Enumeration process: set configuration */
    kStatus_DEV_EnumDone,    /*!< Enumeration is done */
    kStatus_DEV_AppUsed,     /*!< This device has been used by application */
} usb_host_device_enumeration_status_t;

/*! @brief States of device's interface */
typedef enum _usb_host_interface_state
{
    kStatus_interface_Attached = 1, /*!< Interface's default status */
    kStatus_interface_Opened,       /*!< Interface is used by application */
    kStatus_interface_Detached,     /*!< Interface is not used by application */
} usb_host_interface_state_t;

/*! @brief States of device */
typedef enum _usb_host_device_state
{
    kStatus_device_Detached = 0, /*!< Device is used by application */
    kStatus_device_Attached,     /*!< Device's default status */
} usb_host_device_state_t;

/*! @brief Device instance */
typedef struct _usb_host_device_instance
{
    struct _usb_host_device_instance *next;    /*!< Next device, or NULL */
    usb_host_handle hostHandle;                /*!< Host handle */
    usb_host_configuration_t configuration;    /*!< Parsed configuration information for the device */
    usb_descriptor_device_t *deviceDescriptor; /*!< Standard device descriptor */
    usb_host_pipe_handle controlPipe;          /*!< Device's control pipe */
    uint8_t *configurationDesc;                /*!< Configuration descriptor pointer */
    uint16_t configurationLen;                 /*!< Configuration descriptor length */
    uint16_t configurationValue;               /*!< Configuration index */
    uint8_t interfaceStatus[USB_HOST_CONFIG_CONFIGURATION_MAX_INTERFACE]; /*!< Interfaces' status, please reference to
                                                                             #usb_host_interface_state_t */
    uint8_t *enumBuffer;                                                  /*!< Buffer for enumeration */
    uint8_t state;                                                        /*!< Device state for enumeration */
    uint8_t enumRetries;       /*!< Re-enumeration when error in control transfer */
    uint8_t stallRetries;      /*!< Re-transfer when stall */
    uint8_t speed;             /*!< Device speed */
    uint8_t allocatedAddress;  /*!< Temporary address for the device. When set address request succeeds, setAddress is
                                  a value, 1 - 127 */
    uint8_t setAddress;        /*!< The address has been set to the device successfully, 1 - 127 */
    uint8_t deviceAttachState; /*!< See the usb_host_device_state_t */
#if ((defined USB_HOST_CONFIG_HUB) && (USB_HOST_CONFIG_HUB))
    /* hub related */
    uint8_t hubNumber;   /*!< Device's first connected hub address (root hub = 0) */
    uint8_t portNumber;  /*!< Device's first connected hub's port no (1 - 8) */
    uint8_t hsHubNumber; /*!< Device's first connected high-speed hub's address (1 - 8) */
    uint8_t hsHubPort;   /*!< Device's first connected high-speed hub's port no (1 - 8) */
    uint8_t level;       /*!< Device's level (root device = 0) */
#endif
} usb_host_device_instance_t;

typedef struct _usb_host_enum_process_entry
{
    uint8_t successState; /*!< When the last step is successful, the next state value */
    uint8_t retryState;   /*!< When the last step need retry, the next state value */
    usb_status_t (*process)(usb_host_device_instance_t *deviceInstance); /*!< When the last step transfer is done, the
                                                                            function is used to process the transfer
                                                                            data */
} usb_host_enum_process_entry_t;

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief Calls this function when device attach.
 *
 * @param hostHandle    Host instance handle.
 * @param speed         Device speed.
 * @param hubNumber     Device hub no. root device's hub no. is 0.
 * @param portNumber    Device port no. root device's port no. is 0.
 * @param level         Device level. root device's level is 1.
 * @param deviceHandle  Return device handle.
 *
 * @return kStatus_USB_Success or error codes.
 */
extern usb_status_t USB_HostAttachDevice(usb_host_handle hostHandle,
                                         uint8_t speed,
                                         uint8_t hubNumber,
                                         uint8_t portNumber,
                                         uint8_t level,
                                         usb_device_handle *deviceHandle);

/*!
 * @brief Call this function when device detaches.
 *
 * @param hostHandle   Host instance handle.
 * @param hubNumber    Device hub no. root device's hub no. is 0.
 * @param portNumber   Device port no. root device's port no. is 0.
 *
 * @return kStatus_USB_Success or error codes.
 */
extern usb_status_t USB_HostDetachDevice(usb_host_handle hostHandle, uint8_t hubNumber, uint8_t portNumber);

/*!
 * @brief Call this function when device detaches.
 *
 * @param hostHandle    Host instance handle.
 * @param deviceHandle  Device handle.
 *
 * @return kStatus_USB_Success or error codes.
 */
extern usb_status_t USB_HostDetachDeviceInternal(usb_host_handle hostHandle, usb_device_handle deviceHandle);

/*!
 * @brief Gets the device attach/detach state.
 *
 * @param deviceHandle    Device handle.
 *
 * @return 0x01 - attached; 0x00 - detached.
 */
extern uint8_t USB_HostGetDeviceAttachState(usb_device_handle deviceHandle);

/*!
 * @brief Determine whether the device is attached.
 *
 * @param hostHandle    Host instance pointer.
 * @param deviceHandle    Device handle.
 *
 * @return kStatus_USB_Success or error codes.
 */
extern usb_status_t USB_HostValidateDevice(usb_host_handle hostHandle, usb_device_handle deviceHandle);

/*! @}*/
#endif /* _USB_HOST_DEV_MNG_H_ */
