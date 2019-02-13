/*
 * The Clear BSD License
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

#ifndef __USB_DEVICE_CH9_H__
#define __USB_DEVICE_CH9_H__

/*******************************************************************************
* Definitions
******************************************************************************/
/*!
 * @addtogroup usb_device_ch9
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Defines USB device status size when the host request to get device status */
#define USB_DEVICE_STATUS_SIZE (0x02U)

/*! @brief Defines USB device interface status size when the host request to get interface status */
#define USB_INTERFACE_STATUS_SIZE (0x02U)

/*! @brief Defines USB device endpoint status size when the host request to get endpoint status */
#define USB_ENDPOINT_STATUS_SIZE (0x02U)

/*! @brief Defines USB device configuration size when the host request to get current configuration */
#define USB_CONFIGURE_SIZE (0X01U)

/*! @brief Defines USB device interface alternate setting size when the host request to get interface alternate setting
 */
#define USB_INTERFACE_SIZE (0X01U)

/*! @brief Defines USB device status mask */
#define USB_GET_STATUS_DEVICE_MASK (0x03U)

/*! @brief Defines USB device interface status mask */
#define USB_GET_STATUS_INTERFACE_MASK (0x03U)

/*! @brief Defines USB device endpoint status mask */
#define USB_GET_STATUS_ENDPOINT_MASK (0x03U)

/*! @brief Control read and write sequence */
typedef enum _usb_device_control_read_write_sequence
{
    kUSB_DeviceControlPipeSetupStage = 0U, /*!< Setup stage */
    kUSB_DeviceControlPipeDataStage,       /*!< Data stage */
    kUSB_DeviceControlPipeStatusStage,     /*!< status stage */
} usb_device_control_read_write_sequence_t;

/*******************************************************************************
* API
******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief Initialize the control pipes.
 *
 * The function is used to initialize the control pipes. This function should be called when event
 * kUSB_DeviceEventBusReset is received.
 *
 * @param handle      The device handle.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
extern usb_status_t USB_DeviceControlPipeInit(usb_device_handle handle);

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __USB_DEVICE_CH9_H__ */
