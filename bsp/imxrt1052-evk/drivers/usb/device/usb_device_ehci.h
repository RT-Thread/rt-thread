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

#ifndef __USB_DEVICE_EHCI_H__
#define __USB_DEVICE_EHCI_H__

#include <usb/include/usb_ehci.h>

/*!
 * @addtogroup usb_device_controller_ehci_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief The maximum value of ISO type maximum packet size for HS in USB specification 2.0 */
#define USB_DEVICE_MAX_HS_ISO_MAX_PACKET_SIZE (1024U)

/*! @brief The maximum value of interrupt type maximum packet size for HS in USB specification 2.0 */
#define USB_DEVICE_MAX_HS_INTERUPT_MAX_PACKET_SIZE (1024U)

/*! @brief The maximum value of bulk type maximum packet size for HS in USB specification 2.0 */
#define USB_DEVICE_MAX_HS_BULK_MAX_PACKET_SIZE (512U)

/*! @brief The maximum value of control type maximum packet size for HS in USB specification 2.0 */
#define USB_DEVICE_MAX_HS_CONTROL_MAX_PACKET_SIZE (64U)

/*! @brief EHCI state structure */
typedef struct _usb_device_ehci_state_struct
{
    usb_device_struct_t *deviceHandle; /*!< Device handle used to identify the device object is belonged to */
    USBHS_Type *registerBase;          /*!< The base address of the register */
#if (defined(USB_DEVICE_CONFIG_LOW_POWER_MODE) && (USB_DEVICE_CONFIG_LOW_POWER_MODE > 0U))
    USBPHY_Type *registerPhyBase; /*!< The base address of the PHY register */
#if (defined(FSL_FEATURE_SOC_USBNC_COUNT) && (FSL_FEATURE_SOC_USBNC_COUNT > 0U))
    USBNC_Type *registerNcBase; /*!< The base address of the USBNC register */
#endif
#endif
    usb_device_ehci_qh_struct_t *qh;       /*!< The QH structure base address */
    usb_device_ehci_dtd_struct_t *dtd;     /*!< The DTD structure base address */
    usb_device_ehci_dtd_struct_t *dtdFree; /*!< The idle DTD list head */
    usb_device_ehci_dtd_struct_t
        *dtdHard[USB_DEVICE_CONFIG_ENDPOINTS * 2]; /*!< The transferring DTD list head for each endpoint */
    usb_device_ehci_dtd_struct_t
        *dtdTail[USB_DEVICE_CONFIG_ENDPOINTS * 2]; /*!< The transferring DTD list tail for each endpoint */
    int8_t dtdCount;                               /*!< The idle DTD node count */
    uint8_t endpointCount;                         /*!< The endpoint number of EHCI */
    uint8_t isResetting;                           /*!< Whether a PORT reset is occurring or not  */
    uint8_t controllerId;                          /*!< Controller ID */
    uint8_t speed;                                 /*!< Current speed of EHCI */
    uint8_t isSuspending;                          /*!< Is suspending of the PORT */
} usb_device_ehci_state_struct_t;

#if (defined(USB_DEVICE_CHARGER_DETECT_ENABLE) && (USB_DEVICE_CHARGER_DETECT_ENABLE > 0U)) && \
    (defined(FSL_FEATURE_SOC_USBHSDCD_COUNT) && (FSL_FEATURE_SOC_USBHSDCD_COUNT > 0U))
typedef struct _usb_device_dcd_state_struct
{
    usb_device_struct_t *deviceHandle; /*!< Device handle used to identify the device object belongs to */
    USBHSDCD_Type *dcdRegisterBase;    /*!< The base address of the dcd module */
    uint8_t controllerId;              /*!< Controller ID */
} usb_device_dcd_state_struct_t;
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name USB device EHCI functions
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief Initializes the USB device EHCI instance.
 *
 * This function initializes the USB device EHCI module specified by the controllerId.
 *
 * @param[in] controllerId The controller ID of the USB IP. See the enumeration type usb_controller_index_t.
 * @param[in] handle        Pointer of the device handle used to identify the device object is belonged to.
 * @param[out] ehciHandle   An out parameter used to return the pointer of the device EHCI handle to the caller.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceEhciInit(uint8_t controllerId,
                                usb_device_handle handle,
                                usb_device_controller_handle *ehciHandle);

/*!
 * @brief Deinitializes the USB device EHCI instance.
 *
 * This function deinitializes the USB device EHCI module.
 *
 * @param[in] ehciHandle   Pointer of the device EHCI handle.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceEhciDeinit(usb_device_controller_handle ehciHandle);

/*!
 * @brief Sends data through a specified endpoint.
 *
 * This function sends data through a specified endpoint.
 *
 * @param[in] ehciHandle      Pointer of the device EHCI handle.
 * @param[in] endpointAddress Endpoint index.
 * @param[in] buffer           The memory address to hold the data need to be sent.
 * @param[in] length           The data length to be sent.
 *
 * @return A USB error code or kStatus_USB_Success.
 *
 * @note The return value means whether the sending request is successful or not. The transfer completion is indicated
 * by the
 * corresponding callback function.
 * Currently, only one transfer request can be supported for a specific endpoint.
 * If there is a specific requirement to support multiple transfer requests for a specific endpoint, the application
 * should implement a queue in the application level.
 * The subsequent transfer can begin only when the previous transfer is done (a notification is received through the
 * endpoint
 * callback).
 */
usb_status_t USB_DeviceEhciSend(usb_device_controller_handle ehciHandle,
                                uint8_t endpointAddress,
                                uint8_t *buffer,
                                uint32_t length);

/*!
 * @brief Receive data through a specified endpoint.
 *
 * This function Receives data through a specified endpoint.
 *
 * @param[in] ehciHandle      Pointer of the device EHCI handle.
 * @param[in] endpointAddress Endpoint index.
 * @param[in] buffer           The memory address to save the received data.
 * @param[in] length           The data length want to be received.
 *
 * @return A USB error code or kStatus_USB_Success.
 *
 * @note The return value just means if the receiving request is successful or not; the transfer done is notified by the
 * corresponding callback function.
 * Currently, only one transfer request can be supported for one specific endpoint.
 * If there is a specific requirement to support multiple transfer requests for one specific endpoint, the application
 * should implement a queue in the application level.
 * The subsequent transfer could begin only when the previous transfer is done (get notification through the endpoint
 * callback).
 */
usb_status_t USB_DeviceEhciRecv(usb_device_controller_handle ehciHandle,
                                uint8_t endpointAddress,
                                uint8_t *buffer,
                                uint32_t length);

/*!
 * @brief Cancels the pending transfer in a specified endpoint.
 *
 * The function is used to cancel the pending transfer in a specified endpoint.
 *
 * @param[in] ehciHandle      Pointer of the device EHCI handle.
 * @param[in] ep               Endpoint address, bit7 is the direction of endpoint, 1U - IN, 0U - OUT.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceEhciCancel(usb_device_controller_handle ehciHandle, uint8_t ep);

/*!
 * @brief Controls the status of the selected item.
 *
 * The function is used to control the status of the selected item.
 *
 * @param[in] ehciHandle      Pointer of the device EHCI handle.
 * @param[in] type             The selected item. See enumeration type usb_device_control_type_t.
 * @param[in,out] param            The parameter type is determined by the selected item.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceEhciControl(usb_device_controller_handle ehciHandle,
                                   usb_device_control_type_t type,
                                   void *param);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* __USB_DEVICE_EHCI_H__ */
