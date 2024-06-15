/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
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

#ifndef __FSL_USB_DEVICE_H__
#define __FSL_USB_DEVICE_H__

/*!
 * @addtogroup usb_device_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Defines Get/Set status Types */
typedef enum _usb_device_status
{
    kUSB_DeviceStatusTestMode = 1U,  /*!< Test mode */
    kUSB_DeviceStatusSpeed,          /*!< Current speed */
    kUSB_DeviceStatusOtg,            /*!< OTG status */
    kUSB_DeviceStatusDevice,         /*!< Device status */
    kUSB_DeviceStatusEndpoint,       /*!< Endpoint state usb_device_endpoint_status_t */
    kUSB_DeviceStatusDeviceState,    /*!< Device state */
    kUSB_DeviceStatusAddress,        /*!< Device address */
    kUSB_DeviceStatusSynchFrame,     /*!< Current frame */
    kUSB_DeviceStatusBus,            /*!< Bus status */
    kUSB_DeviceStatusBusSuspend,     /*!< Bus suspend */
    kUSB_DeviceStatusBusSleep,       /*!< Bus suspend */
    kUSB_DeviceStatusBusResume,      /*!< Bus resume */
    kUSB_DeviceStatusRemoteWakeup,   /*!< Remote wakeup state */
    kUSB_DeviceStatusBusSleepResume, /*!< Bus resume */
} usb_device_status_t;

/*! @brief Defines USB 2.0 device state */
typedef enum _usb_device_state
{
    kUSB_DeviceStateConfigured = 0U, /*!< Device state, Configured*/
    kUSB_DeviceStateAddress,         /*!< Device state, Address*/
    kUSB_DeviceStateDefault,         /*!< Device state, Default*/
    kUSB_DeviceStateAddressing,      /*!< Device state, Address setting*/
    kUSB_DeviceStateTestMode,        /*!< Device state, Test mode*/
} usb_device_state_t;

#if (defined(USB_DEVICE_CHARGER_DETECT_ENABLE) && (USB_DEVICE_CHARGER_DETECT_ENABLE > 0U))
typedef enum _usb_dcd_detection_sequence_status
{
    kUSB_DcdDetectionNotEnabled = 0x0U,
    kUSB_DcdDataPinDetectionCompleted = 0x01U,
    kUSB_DcdChargingPortDetectionCompleted = 0x02U,
    kUSB_DcdChargerTypeDetectionCompleted = 0x03U,
} usb_dcd_detection_sequence_status_t;

typedef enum _usb_dcd_detection_sequence_results
{
    kUSB_DcdDetectionNoResults = 0x0U,
    kUSB_DcdDetectionStandardHost = 0x01U,
    kUSB_DcdDetectionChargingPort = 0x02U,
    kUSB_DcdDetectionDedicatedCharger = 0x03U,
} usb_dcd_detection_sequence_results_t;
#endif

/*! @brief Defines endpoint state */
typedef enum _usb_endpoint_status
{
    kUSB_DeviceEndpointStateIdle = 0U, /*!< Endpoint state, idle*/
    kUSB_DeviceEndpointStateStalled,   /*!< Endpoint state, stalled*/
} usb_device_endpoint_status_t;

/*! @brief Control endpoint index */
#define USB_CONTROL_ENDPOINT (0U)
/*! @brief Control endpoint maxPacketSize */
#define USB_CONTROL_MAX_PACKET_SIZE (64U)

#if (USB_DEVICE_CONFIG_EHCI && (USB_CONTROL_MAX_PACKET_SIZE != (64U)))
#error For high speed, USB_CONTROL_MAX_PACKET_SIZE must be 64!!!
#endif

/*! @brief The setup packet size of USB control transfer. */
#define USB_SETUP_PACKET_SIZE (8U)
/*! @brief  USB endpoint mask */
#define USB_ENDPOINT_NUMBER_MASK (0x0FU)

/*! @brief Default invalid value or the endpoint callback length of cancelled transfer */
#define USB_UNINITIALIZED_VAL_32 (0xFFFFFFFFU)

/*! @brief Available common EVENT types in device callback */
typedef enum _usb_device_event
{
    kUSB_DeviceEventBusReset = 1U, /*!< USB bus reset signal detected */
    kUSB_DeviceEventSuspend,       /*!< USB bus suspend signal detected */
    kUSB_DeviceEventResume,    /*!< USB bus resume signal detected. The resume signal is driven by itself or a host */
    kUSB_DeviceEventSleeped,   /*!< USB bus LPM suspend signal detected */
    kUSB_DeviceEventLPMResume, /*!< USB bus LPM resume signal detected. The resume signal is driven by itself or a host
                                  */
    kUSB_DeviceEventError,     /*!< An error is happened in the bus. */
    kUSB_DeviceEventDetach,    /*!< USB device is disconnected from a host. */
    kUSB_DeviceEventAttach,    /*!< USB device is connected to a host. */
    kUSB_DeviceEventSetConfiguration, /*!< Set configuration. */
    kUSB_DeviceEventSetInterface,     /*!< Set interface. */

    kUSB_DeviceEventGetDeviceDescriptor,          /*!< Get device descriptor. */
    kUSB_DeviceEventGetConfigurationDescriptor,   /*!< Get configuration descriptor. */
    kUSB_DeviceEventGetStringDescriptor,          /*!< Get string descriptor. */
    kUSB_DeviceEventGetHidDescriptor,             /*!< Get HID descriptor. */
    kUSB_DeviceEventGetHidReportDescriptor,       /*!< Get HID report descriptor. */
    kUSB_DeviceEventGetHidPhysicalDescriptor,     /*!< Get HID physical descriptor. */
    kUSB_DeviceEventGetBOSDescriptor,             /*!< Get configuration descriptor. */
    kUSB_DeviceEventGetDeviceQualifierDescriptor, /*!< Get device qualifier descriptor. */
    kUSB_DeviceEventVendorRequest,                /*!< Vendor request. */
    kUSB_DeviceEventSetRemoteWakeup,              /*!< Enable or disable remote wakeup function. */
    kUSB_DeviceEventGetConfiguration,             /*!< Get current configuration index */
    kUSB_DeviceEventGetInterface,                 /*!< Get current interface alternate setting value */
    kUSB_DeviceEventSetBHNPEnable,
#if (defined(USB_DEVICE_CHARGER_DETECT_ENABLE) && (USB_DEVICE_CHARGER_DETECT_ENABLE > 0U))
    kUSB_DeviceEventDcdTimeOut,               /*!< Dcd detect result is timeout */
    kUSB_DeviceEventDcdUnknownType,           /*!< Dcd detect result is unknown type */
    kUSB_DeviceEventSDPDetected,              /*!< The SDP facility is detected */
    kUSB_DeviceEventChargingPortDetected,     /*!< The charging port is detected */
    kUSB_DeviceEventChargingHostDetected,     /*!< The CDP facility is detected */
    kUSB_DeviceEventDedicatedChargerDetected, /*!< The DCP facility is detected */
#endif
} usb_device_event_t;

/*! @brief Endpoint callback message structure */
typedef struct _usb_device_endpoint_callback_message_struct
{
    uint8_t *buffer; /*!< Transferred buffer */
    uint32_t length; /*!< Transferred data length */
    uint8_t isSetup; /*!< Is in a setup phase */
} usb_device_endpoint_callback_message_struct_t;

/*!
 * @brief Endpoint callback function typedef.
 *
 * This callback function is used to notify the upper layer what the transfer result is.
 * This callback pointer is passed when a specified endpoint is initialized by calling API #USB_DeviceInitEndpoint.
 *
 * @param handle          The device handle. It equals to the value returned from #USB_DeviceInit.
 * @param message         The result of a transfer, which includes transfer buffer, transfer length, and whether is in a
 * setup phase.
 * phase for control pipe.
 * @param callbackParam  The parameter for this callback. It is same with
 * usb_device_endpoint_callback_struct_t::callbackParam.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
typedef usb_status_t (*usb_device_endpoint_callback_t)(usb_device_handle handle,
                                                       usb_device_endpoint_callback_message_struct_t *message,
                                                       void *callbackParam);

/*!
 * @brief Device callback function typedef.
 *
 * This callback function is used to notify the upper layer that the device status has changed.
 * This callback pointer is passed by calling API #USB_DeviceInit.
 *
 * @param handle          The device handle. It equals the value returned from #USB_DeviceInit.
 * @param callbackEvent  The callback event type. See enumeration #usb_device_event_t.
 * @param eventParam     The event parameter for this callback. The parameter type is determined by the callback event.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
typedef usb_status_t (*usb_device_callback_t)(usb_device_handle handle, uint32_t callbackEvent, void *eventParam);

/*! @brief Endpoint callback structure */
typedef struct _usb_device_endpoint_callback_struct
{
    usb_device_endpoint_callback_t callbackFn; /*!< Endpoint callback function*/
    void *callbackParam;                       /*!< Parameter for callback function*/
    uint8_t isBusy;
} usb_device_endpoint_callback_struct_t;

/*! @brief Endpoint initialization structure */
typedef struct _usb_device_endpoint_init_struct
{
    uint16_t maxPacketSize;  /*!< Endpoint maximum packet size */
    uint8_t endpointAddress; /*!< Endpoint address*/
    uint8_t transferType;    /*!< Endpoint transfer type*/
    uint8_t zlt;             /*!< ZLT flag*/
} usb_device_endpoint_init_struct_t;

/*! @brief Endpoint status structure */
typedef struct _usb_device_endpoint_status_struct
{
    uint8_t endpointAddress; /*!< Endpoint address */
    uint16_t endpointStatus; /*!< Endpoint status : idle or stalled */
} usb_device_endpoint_status_struct_t;

#if (defined(USB_DEVICE_CHARGER_DETECT_ENABLE) && (USB_DEVICE_CHARGER_DETECT_ENABLE > 0U))
/*! @brief USB DCD charge timing specification structure */
typedef struct _usb_device_dcd_charging_time
{
    uint16_t dcdSeqInitTime;      /*!< The dcd sequence init time */
    uint16_t dcdDbncTime;         /*!< The debounce time period on DP signal */
    uint16_t dcdDpSrcOnTime;      /*!< The time period comparator enabled */
    uint16_t dcdTimeWaitAfterPrD; /*!< The time period between primary and secondary detection */
    uint8_t dcdTimeDMSrcOn;       /*!< The amount of time that the modules enable the Vdm_src */
} usb_device_dcd_charging_time_t;
#endif

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @name USB device APIs
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief Initializes the USB device stack.
 *
 * This function initializes the USB device module specified by the controllerId.
 *
 * @param[in] controllerId   The controller ID of the USB IP. See the enumeration #usb_controller_index_t.
 * @param[in] deviceCallback Function pointer of the device callback.
 * @param[out] handle          It is an out parameter used to return the pointer of the device handle to the caller.
 *
 * @retval kStatus_USB_Success              The device is initialized successfully.
 * @retval kStatus_USB_InvalidHandle        The handle is a NULL pointer.
 * @retval kStatus_USB_Busy                 Cannot allocate a device handle.
 * @retval kStatus_USB_ControllerNotFound   Cannot find the controller according to the controller id.
 * @retval kStatus_USB_InvalidControllerInterface  The controller driver interfaces is invalid. There is an empty
 *                                                  interface entity.
 * @retval kStatus_USB_Error                The macro USB_DEVICE_CONFIG_ENDPOINTS is more than the IP's endpoint number.
 *                                          Or, the device has been initialized.
 *                                          Or, the mutex or message queue is created failed.
 */
extern usb_status_t USB_DeviceInit(uint8_t controllerId,
                                   usb_device_callback_t deviceCallback,
                                   usb_device_handle *handle);

/*!
 * @brief Enables the device functionality.
 *
 * The function enables the device functionality, so that the device can be recognized by the host when the device
 * detects that it has been connected to a host.
 *
 * @param[in] handle The device handle got from #USB_DeviceInit.
 *
 * @retval kStatus_USB_Success              The device is run successfully.
 * @retval kStatus_USB_ControllerNotFound   Cannot find the controller.
 * @retval kStatus_USB_InvalidHandle        The device handle is a NULL pointer. Or the controller handle is invalid.
 *
 */
extern usb_status_t USB_DeviceRun(usb_device_handle handle);

/*!
 * @brief Disables the device functionality.
 *
 * The function disables the device functionality. After this function called, even if the device is detached to the
 * host,
 * it can't work.
 *
 * @param[in] handle The device handle received from #USB_DeviceInit.
 *
 * @retval kStatus_USB_Success              The device is stopped successfully.
 * @retval kStatus_USB_ControllerNotFound   Cannot find the controller.
 * @retval kStatus_USB_InvalidHandle        The device handle is a NULL pointer or the controller handle is invalid.
 */
extern usb_status_t USB_DeviceStop(usb_device_handle handle);

/*!
 * @brief De-initializes the device controller.
 *
 * The function de-initializes the device controller specified by the handle.
 *
 * @param[in] handle The device handle got from #USB_DeviceInit.
 *
 * @retval kStatus_USB_Success              The device is stopped successfully.
 * @retval kStatus_USB_InvalidHandle        The device handle is a NULL pointer or the controller handle is invalid.
 */
extern usb_status_t USB_DeviceDeinit(usb_device_handle handle);

/*!
 * @brief Sends data through a specified endpoint.
 *
 * The function is used to send data through a specified endpoint.
 *
 * @param[in] handle The device handle got from #USB_DeviceInit.
 * @param[in] endpointAddress Endpoint index.
 * @param[in] buffer The memory address to hold the data need to be sent. The function is not reentrant.
 * @param[in] length The data length need to be sent.
 *
 * @retval kStatus_USB_Success              The send request is sent successfully.
 * @retval kStatus_USB_InvalidHandle        The handle is a NULL pointer. Or the controller handle is invalid.
 * @retval kStatus_USB_Busy                 Cannot allocate DTDS for current transfer in EHCI driver.
 * @retval kStatus_USB_ControllerNotFound   Cannot find the controller.
 * @retval kStatus_USB_Error                The device is doing reset.
 *
 * @note The return value indicates whether the sending request is successful or not. The transfer done is notified by
 * the
 * corresponding callback function.
 * Currently, only one transfer request can be supported for one specific endpoint.
 * If there is a specific requirement to support multiple transfer requests for one specific endpoint, the application
 * should implement a queue on the application level.
 * The subsequent transfer can begin only when the previous transfer is done (get notification through the endpoint
 * callback).
 */
extern usb_status_t USB_DeviceSendRequest(usb_device_handle handle,
                                          uint8_t endpointAddress,
                                          uint8_t *buffer,
                                          uint32_t length);

/*!
 * @brief Receives data through a specified endpoint.
 *
 * The function is used to receive data through a specified endpoint. The function is not reentrant.
 *
 * @param[in] handle The device handle got from #USB_DeviceInit.
 * @param[in] endpointAddress Endpoint index.
 * @param[in] buffer The memory address to save the received data.
 * @param[in] length The data length want to be received.
 *
 * @retval kStatus_USB_Success              The receive request is sent successfully.
 * @retval kStatus_USB_InvalidHandle        The handle is a NULL pointer. Or the controller handle is invalid.
 * @retval kStatus_USB_Busy                 Cannot allocate DTDS for current transfer in EHCI driver.
 * @retval kStatus_USB_ControllerNotFound   Cannot find the controller.
 * @retval kStatus_USB_Error                The device is doing reset.
 *
 * @note The return value indicates whether the receiving request is successful or not. The transfer done is notified by
 * the
 * corresponding callback function.
 * Currently, only one transfer request can be supported for one specific endpoint.
 * If there is a specific requirement to support multiple transfer requests for one specific endpoint, the application
 * should implement a queue on the application level.
 * The subsequent transfer can begin only when the previous transfer is done (get notification through the endpoint
 * callback).
 */
extern usb_status_t USB_DeviceRecvRequest(usb_device_handle handle,
                                          uint8_t endpointAddress,
                                          uint8_t *buffer,
                                          uint32_t length);

/*!
 * @brief Cancels the pending transfer in a specified endpoint.
 *
 * The function is used to cancel the pending transfer in a specified endpoint.
 *
 * @param[in] handle The device handle got from #USB_DeviceInit.
 * @param[in] endpointAddress Endpoint address, bit7 is the direction of endpoint, 1U - IN, and 0U - OUT.
 *
 * @retval kStatus_USB_Success              The transfer is cancelled.
 * @retval kStatus_USB_InvalidHandle        The handle is a NULL pointer or the controller handle is invalid.
 * @retval kStatus_USB_ControllerNotFound   Cannot find the controller.
 */
extern usb_status_t USB_DeviceCancel(usb_device_handle handle, uint8_t endpointAddress);

/*!
 * @brief Initializes a specified endpoint.
 *
 * The function is used to initialize a specified endpoint. The corresponding endpoint callback is also initialized.
 *
 * @param[in] handle The device handle received from #USB_DeviceInit.
 * @param[in] epInit Endpoint initialization structure. See the structure usb_device_endpoint_init_struct_t.
 * @param[in] epCallback Endpoint callback structure. See the structure
 * usb_device_endpoint_callback_struct_t.
 *
 * @retval kStatus_USB_Success              The endpoint is initialized successfully.
 * @retval kStatus_USB_InvalidHandle        The handle is a NULL pointer. Or the controller handle is invalid.
 * @retval kStatus_USB_InvalidParameter     The epInit or epCallback is NULL pointer. Or the endpoint number is
 * more than USB_DEVICE_CONFIG_ENDPOINTS.
 * @retval kStatus_USB_Busy                 The endpoint is busy in EHCI driver.
 * @retval kStatus_USB_ControllerNotFound   Cannot find the controller.
 */
extern usb_status_t USB_DeviceInitEndpoint(usb_device_handle handle,
                                           usb_device_endpoint_init_struct_t *epInit,
                                           usb_device_endpoint_callback_struct_t *epCallback);

/*!
 * @brief Deinitializes a specified endpoint.
 *
 * The function is used to deinitializes a specified endpoint.
 *
 * @param[in] handle The device handle got from #USB_DeviceInit.
 * @param[in] endpointAddress Endpoint address, bit7 is the direction of endpoint, 1U - IN, and 0U - OUT.
 *
 * @retval kStatus_USB_Success              The endpoint is de-initialized successfully.
 * @retval kStatus_USB_InvalidHandle        The handle is a NULL pointer. Or the controller handle is invalid.
 * @retval kStatus_USB_InvalidParameter     The endpoint number is more than USB_DEVICE_CONFIG_ENDPOINTS.
 * @retval kStatus_USB_Busy                 The endpoint is busy in EHCI driver.
 * @retval kStatus_USB_ControllerNotFound   Cannot find the controller.
 */
extern usb_status_t USB_DeviceDeinitEndpoint(usb_device_handle handle, uint8_t endpointAddress);

/*!
 * @brief Stalls a specified endpoint.
 *
 * The function is used to stall a specified endpoint.
 *
 * @param[in] handle The device handle received from #USB_DeviceInit.
 * @param[in] endpointAddress Endpoint address, bit7 is the direction of endpoint, 1U - IN, and 0U - OUT.
 *
 * @retval kStatus_USB_Success              The endpoint is stalled successfully.
 * @retval kStatus_USB_InvalidHandle        The handle is a NULL pointer. Or the controller handle is invalid.
 * @retval kStatus_USB_InvalidParameter     The endpoint number is more than USB_DEVICE_CONFIG_ENDPOINTS.
 * @retval kStatus_USB_ControllerNotFound   Cannot find the controller.
 */
extern usb_status_t USB_DeviceStallEndpoint(usb_device_handle handle, uint8_t endpointAddress);

/*!
 * @brief Unstalls a specified endpoint.
 *
 * The function is used to unstall a specified endpoint.
 *
 * @param[in] handle The device handle received from #USB_DeviceInit.
 * @param[in] endpointAddress Endpoint address, bit7 is the direction of endpoint, 1U - IN, and 0U - OUT.
 *
 * @retval kStatus_USB_Success              The endpoint is unstalled successfully.
 * @retval kStatus_USB_InvalidHandle        The handle is a NULL pointer. Or the controller handle is invalid.
 * @retval kStatus_USB_InvalidParameter     The endpoint number is more than USB_DEVICE_CONFIG_ENDPOINTS.
 * @retval kStatus_USB_ControllerNotFound   Cannot find the controller.
 */
extern usb_status_t USB_DeviceUnstallEndpoint(usb_device_handle handle, uint8_t endpointAddress);

/*!
 * @brief Gets the status of the selected item.
 *
 * The function is used to get the status of the selected item.
 *
 * @param[in] handle The device handle got from #USB_DeviceInit.
 * @param[in] type   The selected item. See the structure #usb_device_status_t.
 * @param[out] param  The parameter type is determined by the selected item.
 *
 * @retval kStatus_USB_Success              Get status successfully.
 * @retval kStatus_USB_InvalidHandle        The handle is a NULL pointer. Or the controller handle is invalid.
 * @retval kStatus_USB_InvalidParameter     The parameter is NULL pointer.
 * @retval kStatus_USB_ControllerNotFound   Cannot find the controller.
 * @retval kStatus_USB_Error                Unsupported type.
 */
extern usb_status_t USB_DeviceGetStatus(usb_device_handle handle, usb_device_status_t type, void *param);

/*!
 * @brief Sets the status of the selected item.
 *
 * The function is used to set the status of the selected item.
 *
 * @param[in] handle The device handle got from #USB_DeviceInit.
 * @param[in] type The selected item. See the structure #usb_device_status_t.
 * @param[in] param The parameter type is determined by the selected item.
 *
 * @retval kStatus_USB_Success              Set status successfully.
 * @retval kStatus_USB_InvalidHandle        The handle is a NULL pointer. Or the controller handle is invalid.
 * @retval kStatus_USB_ControllerNotFound   Cannot find the controller.
 * @retval kStatus_USB_Error                Unsupported type or the parameter is NULL pointer.
 */
extern usb_status_t USB_DeviceSetStatus(usb_device_handle handle, usb_device_status_t type, void *param);

#if (defined(USB_DEVICE_CHARGER_DETECT_ENABLE) && (USB_DEVICE_CHARGER_DETECT_ENABLE > 0U))
/*!
 * @brief Initializes the device dcd module.
 *
 * The function initializes the device dcd module.
 *
 * @param[in] handle The device handle got from #USB_DeviceInit.
 * @param[in] time_param The time parameter used to config the dcd timing registers.
 *
 * @retval kStatus_USB_Success              The device is run successfully.
 * @retval kStatus_USB_ControllerNotFound   Cannot find the controller.
 * @retval kStatus_USB_InvalidHandle        The device handle is a NULL pointer. Or the controller handle is invalid.
 *
 */
extern usb_status_t USB_DeviceDcdInitModule(usb_device_handle handle, void *time_param);

/*!
 * @brief De-initializes the device dcd module.
 *
 * The function de-initializes the device dcd module specified by the handle.
 *
 * @param[in] handle The device handle got from #USB_DeviceInit.
 *
 * @retval kStatus_USB_Success           The device is stopped successfully.
 * @retval kStatus_USB_InvalidHandle         The device handle is a NULL pointer or the controller handle is invalid.
 */
extern usb_status_t USB_DeviceDcdDeinitModule(usb_device_handle handle);
#endif
/*!
 * @brief Device task function.
 *
 * The function is used to handle the controller message.
 * This function should not be called in the application directly.
 *
 * @param[in] deviceHandle The device handle got from #USB_DeviceInit.
 */
extern void USB_DeviceTaskFunction(void *deviceHandle);

#if ((defined(USB_DEVICE_CONFIG_KHCI)) && (USB_DEVICE_CONFIG_KHCI > 0U))
/*!
 * @brief Device KHCI task function.
 *
 * The function is used to handle the KHCI controller message.
 * In the bare metal environment, this function should be called periodically in the main function.
 * In the RTOS environment, this function should be used as a function entry to create a task.
 *
 * @param[in] deviceHandle The device handle got from #USB_DeviceInit.
 */
#define USB_DeviceKhciTaskFunction(deviceHandle) USB_DeviceTaskFunction(deviceHandle)
#endif

#if ((defined(USB_DEVICE_CONFIG_EHCI)) && (USB_DEVICE_CONFIG_EHCI > 0U))
/*!
 * @brief Device EHCI task function.
 *
 * The function is used to handle the EHCI controller message.
 * In the bare metal environment, this function should be called periodically in the main function.
 * In the RTOS environment, this function should be used as a function entry to create a task.
 *
 * @param[in] deviceHandle The device handle got from #USB_DeviceInit.
 */
#define USB_DeviceEhciTaskFunction(deviceHandle) USB_DeviceTaskFunction(deviceHandle)
#if (defined(USB_DEVICE_CHARGER_DETECT_ENABLE) && (USB_DEVICE_CHARGER_DETECT_ENABLE > 0U))
/*!
 * @brief Device EHCI DCD ISR function.
 *
 * The function is the EHCI DCD interrupt service routine.
 *
 * @param[in] deviceHandle The device handle got from #USB_DeviceInit.
 */
extern void USB_DeviceDcdHSIsrFunction(void *deviceHandle);
#endif
#endif

#if (((defined(USB_DEVICE_CONFIG_LPCIP3511FS)) && (USB_DEVICE_CONFIG_LPCIP3511FS > 0U)) || \
     ((defined(USB_DEVICE_CONFIG_LPCIP3511HS)) && (USB_DEVICE_CONFIG_LPCIP3511HS > 0U)))
/*!
 * @brief Device LPC ip3511 controller task function.
 *
 * The function is used to handle the LPC ip3511 controller message.
 * In the bare metal environment, this function should be called periodically in the main function.
 * In the RTOS environment, this function should be used as a function entry to create a task.
 *
 * @param[in] deviceHandle The device handle got from #USB_DeviceInit.
 */
#define USB_DeviceLpcIp3511TaskFunction(deviceHandle) USB_DeviceTaskFunction(deviceHandle)
#endif

#if ((defined(USB_DEVICE_CONFIG_KHCI)) && (USB_DEVICE_CONFIG_KHCI > 0U))
/*!
 * @brief Device KHCI ISR function.
 *
 * The function is the KHCI interrupt service routine.
 *
 * @param[in] deviceHandle The device handle got from #USB_DeviceInit.
 */
extern void USB_DeviceKhciIsrFunction(void *deviceHandle);
#if (defined(USB_DEVICE_CHARGER_DETECT_ENABLE) && (USB_DEVICE_CHARGER_DETECT_ENABLE > 0U))
/*!
 * @brief Device KHCI DCD ISR function.
 *
 * The function is the KHCI DCD interrupt service routine.
 *
 * @param[in] deviceHandle The device handle got from #USB_DeviceInit.
 */
extern void USB_DeviceDcdIsrFunction(void *deviceHandle);
#endif
#endif

#if ((defined(USB_DEVICE_CONFIG_EHCI)) && (USB_DEVICE_CONFIG_EHCI > 0U))
/*!
 * @brief Device EHCI ISR function.
 *
 * The function is the EHCI interrupt service routine.
 *
 * @param[in] deviceHandle The device handle got from #USB_DeviceInit.
 */
extern void USB_DeviceEhciIsrFunction(void *deviceHandle);
#endif

#if (((defined(USB_DEVICE_CONFIG_LPCIP3511FS)) && (USB_DEVICE_CONFIG_LPCIP3511FS > 0U)) || \
     ((defined(USB_DEVICE_CONFIG_LPCIP3511HS)) && (USB_DEVICE_CONFIG_LPCIP3511HS > 0U)))
/*!
 * @brief Device LPC USB ISR function.
 *
 * The function is the LPC USB interrupt service routine.
 *
 * @param[in] deviceHandle The device handle got from #USB_DeviceInit.
 */
extern void USB_DeviceLpcIp3511IsrFunction(void *deviceHandle);
#endif

/*!
 * @brief Gets the device stack version function.
 *
 * The function is used to get the device stack version.
 *
 * @param[out] version The version structure pointer to keep the device stack version.
 *
 */
extern void USB_DeviceGetVersion(uint32_t *version);

#if ((defined(USB_DEVICE_CONFIG_REMOTE_WAKEUP)) && (USB_DEVICE_CONFIG_REMOTE_WAKEUP > 0U))
/*!
 * @brief Update the hardware tick.
 *
 * The function is used to update the hardware tick.
 *
 * @param[in] handle The device handle got from #USB_DeviceInit.
 * @param[in] tick Current hardware tick(uint is ms).
 *
 */
extern usb_status_t USB_DeviceUpdateHwTick(usb_device_handle handle, uint64_t tick);
#endif

/*! @}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* __USB_DEVICE_H__ */
