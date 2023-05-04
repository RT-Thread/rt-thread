/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _USB_HOST_H_
#define _USB_HOST_H_

#include <usb/include/usb.h>
#include <usb/include/usb_misc.h>
#include <usb/include/usb_spec.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

struct _usb_host_transfer; /* for cross reference */

/*!
 * @addtogroup usb_host_drv
 * @{
 */

/*! @brief USB host class handle type define */
typedef void *usb_host_class_handle;

/*! @brief USB host controller handle type define */
typedef void *usb_host_controller_handle;

/*! @brief USB host configuration handle type define */
typedef void *usb_host_configuration_handle;

/*! @brief USB host interface handle type define */
typedef void *usb_host_interface_handle;

/*! @brief USB host pipe handle type define */
typedef void *usb_host_pipe_handle;

/*! @brief Event codes for device attach/detach */
typedef enum _usb_host_event
{
    kUSB_HostEventAttach = 1U,     /*!< Device is attached */
    kUSB_HostEventDetach,          /*!< Device is detached */
    kUSB_HostEventEnumerationDone, /*!< Device's enumeration is done and the device is supported */
    kUSB_HostEventNotSupported,    /*!< Device's enumeration is done and the device is not supported */
    /*! Device's enumeration failed due to errors
     * fail reason is put in the high 2 bytes of callback event code.
     * kStatus_USB_TransferFailed - the transfer failed.
     * kStatus_USB_TransferCancel - transfer is canceled by application.
     * kStatus_USB_Error - parsing descriptor failed, the power cannot satisfy device's requirement,
     *                     device addresss allocation failed, transfer is not enough
     *                     or the transfer API failed.
     * kStatus_USB_AllocFail - malloc failed.
     */
    kUSB_HostEventEnumerationFail,
#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
    kUSB_HostEventNotSuspended,      /*!< Suspend failed */
    kUSB_HostEventSuspended,         /*!< Suspend successful */
    kUSB_HostEventNotResumed,        /*!< Resume failed */
    kUSB_HostEventDetectResume,      /*!< Detect resume signal */
    kUSB_HostEventResumed,           /*!< Resume successful */
    kUSB_HostEventL1Sleeped,         /*!< L1 Sleep successful,state transition was successful (ACK) */
    kUSB_HostEventL1SleepNYET,       /*!< Device was unable to enter the L1 state at this time (NYET)  */
    kUSB_HostEventL1SleepNotSupport, /*!< Device does not support the L1 state (STALL)  */
    kUSB_HostEventL1SleepError,      /*!< Device failed to respond or an error occurred  */
    kUSB_HostEventL1NotResumed,      /*!< Resume failed */
    kUSB_HostEventL1DetectResume,    /*!< Detect resume signal */
    kUSB_HostEventL1Resumed,         /*!< Resume successful */
#endif
} usb_host_event_t;

/*! @brief USB host device information code */
typedef enum _usb_host_dev_info
{
    kUSB_HostGetDeviceAddress = 1U,  /*!< Device's address */
    kUSB_HostGetDeviceHubNumber,     /*!< Device's first hub address */
    kUSB_HostGetDevicePortNumber,    /*!< Device's first hub port number */
    kUSB_HostGetDeviceSpeed,         /*!< Device's speed */
    kUSB_HostGetDeviceHSHubNumber,   /*!< Device's first high-speed hub address */
    kUSB_HostGetDeviceHSHubPort,     /*!< Device's first high-speed hub number */
    kUSB_HostGetDeviceLevel,         /*!< Device's hub level */
    kUSB_HostGetHostHandle,          /*!< Device's host handle */
    kUSB_HostGetDeviceControlPipe,   /*!< Device's control pipe handle */
    kUSB_HostGetDevicePID,           /*!< Device's PID */
    kUSB_HostGetDeviceVID,           /*!< Device's VID */
    kUSB_HostGetHubThinkTime,        /*!< Device's hub total think time */
    kUSB_HostGetDeviceConfigIndex,   /*!< Device's running zero-based config index */
    kUSB_HostGetConfigurationDes,    /*!< Device's configuration descriptor pointer */
    kUSB_HostGetConfigurationLength, /*!< Device's configuration descriptor pointer */
} usb_host_dev_info_t;
/*! @brief Request type */
typedef enum _usb_host_request_type
{
    kRequestDevice = 1U, /*!< Control request object is device */
    kRequestInterface,   /*!< Control request object is interface */
    kRequestEndpoint,    /*!< Control request object is endpoint */
} usb_host_request_type_t;
/*! @brief For USB_REQUEST_STANDARD_GET_DESCRIPTOR and USB_REQUEST_STANDARD_SET_DESCRIPTOR */
typedef struct _usb_host_process_descriptor_param
{
    uint8_t descriptorType;    /*!< See the usb_spec.h, such as the USB_DESCRIPTOR_TYPE_DEVICE */
    uint8_t descriptorIndex;   /*!< The descriptor index is used to select a specific descriptor (only for configuration
                                  and string descriptors) when several descriptors of the same type are implemented in a
                                  device */
    uint16_t languageId;        /*!< It specifies the language ID for string descriptors or is reset to zero for other
                                  descriptors */
    uint8_t *descriptorBuffer; /*!< Buffer pointer */
    uint16_t descriptorLength; /*!< Buffer data length */
} usb_host_process_descriptor_param_t;
/*! @brief For USB_REQUEST_STANDARD_CLEAR_FEATURE and USB_REQUEST_STANDARD_SET_FEATURE */
typedef struct _usb_host_process_feature_param
{
    uint8_t requestType;         /*!< See the #usb_host_request_type_t */
    uint8_t featureSelector;     /*!< Set/cleared feature */
    uint8_t interfaceOrEndpoint; /*!< Interface or end pointer */
} usb_host_process_feature_param_t;
/*! @brief For USB_REQUEST_STANDARD_GET_INTERFACE */
typedef struct _usb_host_get_interface_param
{
    uint8_t interface;                 /*!< Interface number */
    uint8_t *alternateInterfaceBuffer; /*!< Save the transfer result */
} usb_host_get_interface_param_t;

/*! @brief For USB_REQUEST_STANDARD_GET_STATUS */
typedef struct _usb_host_get_status_param
{
    uint16_t statusSelector; /*!< Interface number, the end pointer number or OTG status selector */
    uint8_t requestType;     /*!< See the #usb_host_request_type_t */
    uint8_t *statusBuffer;   /*!< Save the transfer result */
} usb_host_get_status_param_t;

/*! @brief For USB_REQUEST_STANDARD_SET_INTERFACE */
typedef struct _usb_host_set_interface_param
{
    uint8_t alternateSetting; /*!< Alternate setting value */
    uint8_t interface;        /*!< Interface number */
} usb_host_set_interface_param_t;

/*! @brief For USB_REQUEST_STANDARD_SYNCH_FRAME */
typedef struct _usb_host_synch_frame_param
{
    uint8_t endpoint;           /*!< Endpoint number */
    uint8_t *frameNumberBuffer; /*!< Frame number data buffer */
} usb_host_synch_frame_param_t;
/*!
 * @brief Host callback function typedef.
 *
 * This callback function is used to notify application device attach/detach event.
 * This callback pointer is passed when initializing the host.
 *
 * @param deviceHandle           The device handle, which indicates the attached device.
 * @param configurationHandle The configuration handle contains the attached device's configuration information.
 * @param event_code           The callback event code; See the enumeration host_event_t.
 *
 * @return A USB error code or kStatus_USB_Success.
 * @retval kStatus_USB_Success       Application handles the attached device successfully.
 * @retval kStatus_USB_NotSupported  Application don't support the attached device.
 * @retval kStatus_USB_Error         Application handles the attached device falsely.
 */
typedef usb_status_t (*host_callback_t)(usb_device_handle deviceHandle,
                                        usb_host_configuration_handle configurationHandle,
                                        uint32_t eventCode);

/*!
 * @brief Transfer callback function typedef.
 *
 * This callback function is used to notify the upper layer the result of the transfer.
 * This callback pointer is passed when calling the send/receive APIs.
 *
 * @param param     The parameter pointer, which is passed when calling the send/receive APIs.
 * @param data      The data buffer pointer.
 * @param data_len  The result data length.
 * @param status    A USB error code or kStatus_USB_Success.
 */
typedef void (*transfer_callback_t)(void *param, uint8_t *data, uint32_t dataLen, usb_status_t status);

/*!
 * @brief Host stack inner transfer callback function typedef.
 *
 * This callback function is used to notify the upper layer the result of a transfer.
 * This callback pointer is passed when initializing the structure usb_host_transfer_t.
 *
 * @param param     The parameter pointer, which is passed when calling the send/receive APIs.
 * @param transfer  The transfer information; See the structure usb_host_transfer_t.
 * @param status    A USB error code or kStatus_USB_Success.
 */
typedef void (*host_inner_transfer_callback_t)(void *param, struct _usb_host_transfer *transfer, usb_status_t status);

/*! @brief USB host endpoint information structure */
typedef struct _usb_host_ep
{
    usb_descriptor_endpoint_t *epDesc; /*!< Endpoint descriptor pointer*/
    uint8_t *epExtension;              /*!< Endpoint extended descriptor pointer*/
    uint16_t epExtensionLength;        /*!< Extended descriptor length*/
} usb_host_ep_t;

/*! @brief USB host interface information structure */
typedef struct _usb_host_interface
{
    usb_host_ep_t epList[USB_HOST_CONFIG_INTERFACE_MAX_EP]; /*!< Endpoint array*/
    usb_descriptor_interface_t *interfaceDesc;              /*!< Interface descriptor pointer*/
    uint8_t *interfaceExtension;                            /*!< Interface extended descriptor pointer*/
    uint16_t interfaceExtensionLength;                      /*!< Extended descriptor length*/
    uint8_t interfaceIndex;                                 /*!< The interface index*/
    uint8_t alternateSettingNumber;                         /*!< The interface alternate setting value*/
    uint8_t epCount;                                        /*!< Interface's endpoint number*/
} usb_host_interface_t;

/*! @brief USB host configuration information structure */
typedef struct _usb_host_configuration
{
    usb_host_interface_t interfaceList[USB_HOST_CONFIG_CONFIGURATION_MAX_INTERFACE]; /*!< Interface array*/
    usb_descriptor_configuration_t *configurationDesc; /*!< Configuration descriptor pointer*/
    uint8_t *configurationExtension;                   /*!< Configuration extended descriptor pointer*/
    uint16_t configurationExtensionLength;             /*!< Extended descriptor length*/
    uint8_t interfaceCount;                            /*!< The configuration's interface number*/
} usb_host_configuration_t;

/*! @brief USB host pipe common structure */
typedef struct _usb_host_pipe
{
    struct _usb_host_pipe *next;    /*!< Link the idle pipes*/
    usb_device_handle deviceHandle; /*!< This pipe's device's handle*/
    uint16_t currentCount;          /*!< For KHCI transfer*/
    uint16_t nakCount;              /*!< Maximum NAK count*/
    uint16_t maxPacketSize;         /*!< Maximum packet size*/
    uint16_t interval;              /*!< FS/LS: frame unit; HS: micro-frame unit*/
    uint8_t open;                   /*!< 0 - closed, 1 - open*/
    uint8_t nextdata01;             /*!< Data toggle*/
    uint8_t endpointAddress;        /*!< Endpoint address*/
    uint8_t direction;              /*!< Pipe direction*/
    uint8_t pipeType;               /*!< Pipe type, for example USB_ENDPOINT_BULK*/
    uint8_t numberPerUframe;        /*!< Transaction number per micro-frame*/
} usb_host_pipe_t;

/*! @brief USB host transfer structure */
typedef struct _usb_host_transfer
{
    struct _usb_host_transfer *next;           /*!< The next transfer structure*/
    uint8_t *transferBuffer;                   /*!< Transfer data buffer*/
    uint32_t transferLength;                   /*!< Transfer data length*/
    uint32_t transferSofar;                    /*!< Length transferred so far*/
    host_inner_transfer_callback_t callbackFn; /*!< Transfer callback function*/
    void *callbackParam;                       /*!< Transfer callback parameter*/
    usb_host_pipe_t *transferPipe;             /*!< Transfer pipe pointer*/
    usb_setup_struct_t *setupPacket;           /*!< Set up packet buffer*/
    uint8_t direction;                         /*!< Transfer direction; it's values are USB_OUT or USB_IN*/
    uint8_t setupStatus;                       /*!< Set up the transfer status*/
    union
    {
        uint32_t unitHead;      /*!< xTD head for this transfer*/
        int32_t transferResult; /*!< KHCI transfer result */
    } union1;

    union
    {
        uint32_t unitTail; /*!<xTD tail for this transfer*/
        uint32_t frame;    /*!< KHCI transfer frame number */
    } union2;

#if USB_HOST_CONFIG_KHCI
    uint16_t nakTimeout; /*!< KHCI transfer NAK timeout */
    uint16_t retry;      /*!< KHCI transfer retry */
#endif
} usb_host_transfer_t;

/*! @brief USB host pipe information structure for opening pipe */
typedef struct _usb_host_pipe_init
{
    void *devInstance;       /*!< Device instance handle*/
    uint16_t nakCount;       /*!< Maximum NAK retry count. MUST be zero for interrupt*/
    uint16_t maxPacketSize;  /*!< Pipe's maximum packet size*/
    uint8_t interval;        /*!< Pipe's interval*/
    uint8_t endpointAddress; /*!< Endpoint address*/
    uint8_t direction;       /*!< Endpoint direction*/
    uint8_t pipeType;        /*!< Endpoint type, the value is USB_ENDPOINT_INTERRUPT, USB_ENDPOINT_CONTROL,
                                USB_ENDPOINT_ISOCHRONOUS, USB_ENDPOINT_BULK*/
    uint8_t numberPerUframe; /*!< Transaction number for each micro-frame*/
} usb_host_pipe_init_t;

/*! @brief Cancel transfer parameter structure */
typedef struct _usb_host_cancel_param
{
    usb_host_pipe_handle pipeHandle; /*!< Canceling pipe handle*/
    usb_host_transfer_t *transfer;   /*!< Canceling transfer*/
} usb_host_cancel_param_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @name USB host APIs Part 1
 * The following APIs are recommended for application use.
 * @{
 */

/*!
 * @brief Initializes the USB host stack.
 *
 * This function initializes the USB host module specified by the controllerId.
 *
 * @param[in] controllerId    The controller ID of the USB IP. See the enumeration usb_controller_index_t.
 * @param[out] hostHandle     Returns the host handle.
 * @param[in] callbackFn      Host callback function notifies device attach/detach.
 *
 * @retval kStatus_USB_Success              The host is initialized successfully.
 * @retval kStatus_USB_InvalidHandle        The hostHandle is a NULL pointer.
 * @retval kStatus_USB_ControllerNotFound   Cannot find the controller according to the controller ID.
 * @retval kStatus_USB_AllocFail            Allocation memory fail.
 * @retval kStatus_USB_Error                Host mutex create fail; KHCI/EHCI mutex or KHCI/EHCI event create fail,
 *                                          or, KHCI/EHCI IP initialize fail.
 */
extern usb_status_t USB_HostInit(uint8_t controllerId, usb_host_handle *hostHandle, host_callback_t callbackFn);

/*!
 * @brief Deinitializes the USB host stack.
 *
 * This function deinitializes the USB host module specified by the hostHandle.
 *
 * @param[in] hostHandle  The host handle.
 *
 * @retval kStatus_USB_Success              The host is initialized successfully.
 * @retval kStatus_USB_InvalidHandle        The hostHandle is a NULL pointer.
 * @retval kStatus_USB_Error                Controller deinitialization fail.
 */
extern usb_status_t USB_HostDeinit(usb_host_handle hostHandle);

/*!
 * @brief Gets the device information.
 *
 * This function gets the device information.
 *
 * @param[in] deviceHandle   Removing device handle.
 * @param[in] infoCode       See the enumeration host_dev_info_t.
 * @param[out] infoValue     Return the information value.
 *
 * @retval kStatus_USB_Success              Close successfully.
 * @retval kStatus_USB_InvalidParameter     The deviceHandle or info_value is a NULL pointer.
 * @retval kStatus_USB_Error                The info_code is not the host_dev_info_t value.
 */
extern usb_status_t USB_HostHelperGetPeripheralInformation(usb_device_handle deviceHandle,
                                                           uint32_t infoCode,
                                                           uint32_t *infoValue);

/*!
 * @brief Parses the alternate interface descriptor.
 *
 * This function parses the alternate interface descriptor and returns an interface information through the structure
 * usb_host_interface_t.
 *
 * @param[in] interfaceHandle     The whole interface handle.
 * @param[in] alternateSetting    Alternate setting value.
 * @param[out] interface          Return interface information.
 *
 * @retval kStatus_USB_Success              Close successfully.
 * @retval kStatus_USB_InvalidHandle        The interfaceHandle is a NULL pointer.
 * @retval kStatus_USB_InvalidParameter     The alternateSetting is 0.
 * @retval kStatus_USB_Error                The interface descriptor is wrong.
 */
extern usb_status_t USB_HostHelperParseAlternateSetting(usb_host_interface_handle interfaceHandle,
                                                        uint8_t alternateSetting,
                                                        usb_host_interface_t *interface);

/*!
 * @brief Removes the attached device.
 *
 * This function removes the attached device.
 * This function should not be used all the time.
 *
 * @param[in] hostHandle     The host handle.
 * @param[in] deviceHandle   Removing device handle.
 *
 * @retval kStatus_USB_Success              Remove successfully.
 * @retval kStatus_USB_InvalidHandle        The hostHandle or deviceHandle is a NULL pointer.
 * @retval kStatus_USB_InvalidParameter     The deviceHandle instance don't belong to hostHandle instance.
 */
extern usb_status_t USB_HostRemoveDevice(usb_host_handle hostHandle, usb_device_handle deviceHandle);
#if (defined(USB_HOST_CONFIG_KHCI) && (USB_HOST_CONFIG_KHCI > 0U))
/*!
 * @brief KHCI task function.
 *
 * The function is used to handle the KHCI controller message.
 * In the bare metal environment, this function should be called periodically in the main function.
 * In the RTOS environment, this function should be used as a function entry to create a task.
 *
 * @param[in] hostHandle The host handle.
 */
extern void USB_HostKhciTaskFunction(void *hostHandle);
#endif
#if (defined(USB_HOST_CONFIG_EHCI) && (USB_HOST_CONFIG_EHCI > 0U))
/*!
 * @brief EHCI task function.
 *
 * The function is used to handle the EHCI controller message.
 * In the bare metal environment, this function should be called periodically in the main function.
 * In the RTOS environment, this function should be used as a function entry to create a task.
 *
 * @param[in] hostHandle The host handle.
 */
extern void USB_HostEhciTaskFunction(void *hostHandle);
#endif
#if (defined(USB_HOST_CONFIG_OHCI) && (USB_HOST_CONFIG_OHCI > 0U))
/*!
 * @brief OHCI task function.
 *
 * The function is used to handle the OHCI controller message.
 * In the bare metal environment, this function should be called periodically in the main function.
 * In the RTOS environment, this function should be used as a function entry to create a task.
 *
 * @param[in] hostHandle The host handle.
 */
extern void USB_HostOhciTaskFunction(void *hostHandle);
#endif
#if (defined(USB_HOST_CONFIG_IP3516HS) && (USB_HOST_CONFIG_IP3516HS > 0U))
/*!
 * @brief IP3516HS task function.
 *
 * The function is used to handle the IP3516HS controller message.
 * In the bare metal environment, this function should be called periodically in the main function.
 * In the RTOS environment, this function should be used as a function entry to create a task.
 *
 * @param[in] hostHandle The host handle.
 */
extern void USB_HostIp3516HsTaskFunction(void *hostHandle);
#endif
#if (defined(USB_HOST_CONFIG_KHCI) && (USB_HOST_CONFIG_KHCI > 0U))
/*!
 * @brief Device KHCI ISR function.
 *
 * The function is the KHCI interrupt service routine.
 *
 * @param[in] hostHandle The host handle.
 */
extern void USB_HostKhciIsrFunction(void *hostHandle);
#endif
#if (defined(USB_HOST_CONFIG_EHCI) && (USB_HOST_CONFIG_EHCI > 0U))
/*!
 * @brief Device EHCI ISR function.
 *
 * The function is the EHCI interrupt service routine.
 *
 * @param[in] hostHandle The host handle.
 */
extern void USB_HostEhciIsrFunction(void *hostHandle);
#endif
#if (defined(USB_HOST_CONFIG_OHCI) && (USB_HOST_CONFIG_OHCI > 0U))
/*!
 * @brief Device OHCI ISR function.
 *
 * The function is the OHCI interrupt service routine.
 *
 * @param[in] hostHandle The host handle.
 */
extern void USB_HostOhciIsrFunction(void *hostHandle);
#endif
#if (defined(USB_HOST_CONFIG_IP3516HS) && (USB_HOST_CONFIG_IP3516HS > 0U))
/*!
 * @brief Device IP3516HS ISR function.
 *
 * The function is the IP3516HS interrupt service routine.
 *
 * @param[in] hostHandle The host handle.
 */
extern void USB_HostIp3516HsIsrFunction(void *hostHandle);
#endif
/*! @}*/

/*!
 * @name USB host APIs Part 2.
 * The following APIs are not recommended for application use. They are mainly used in the class driver.
 * @{
 */

/*!
 * @brief Opens the USB host pipe.
 *
 * This function opens a pipe according to the pipe_init_ptr parameter.
 *
 * @param[in] hostHandle  The host handle.
 * @param[out] pipeHandle The pipe handle pointer used to return the pipe handle.
 * @param[in] pipeInit    Used to initialize the pipe.
 *
 * @retval kStatus_USB_Success              The host is initialized successfully.
 * @retval kStatus_USB_InvalidHandle        The hostHandle or pipe_handle_ptr is a NULL pointer.
 * @retval kStatus_USB_Error                There is no idle pipe.
 *                                          Or, there is no idle QH for EHCI.
 *                                          Or, bandwidth allocate fail for EHCI.
 */
extern usb_status_t USB_HostOpenPipe(usb_host_handle hostHandle,
                                     usb_host_pipe_handle *pipeHandle,
                                     usb_host_pipe_init_t *pipeInit);

/*!
 * @brief Closes the USB host pipe.
 *
 * This function closes a pipe and frees the related resources.
 *
 * @param[in] hostHandle     The host handle.
 * @param[in] pipeHandle     The closing pipe handle.
 *
 * @retval kStatus_USB_Success              The host is initialized successfully.
 * @retval kStatus_USB_InvalidHandle        The hostHandle or pipeHandle is a NULL pointer.
 */
extern usb_status_t USB_HostClosePipe(usb_host_handle hostHandle, usb_host_pipe_handle pipeHandle);

/*!
 * @brief Sends data to a pipe.
 *
 * This function requests to send the transfer to the specified pipe.
 *
 * @param[in] hostHandle     The host handle.
 * @param[in] pipeHandle     The sending pipe handle.
 * @param[in] transfer        The transfer information.
 *
 * @retval kStatus_USB_Success              Send successfully.
 * @retval kStatus_USB_InvalidHandle        The hostHandle, pipeHandle or transfer is a NULL pointer.
 * @retval kStatus_USB_LackSwapBuffer       There is no swap buffer for KHCI.
 * @retval kStatus_USB_Error                There is no idle QTD/ITD/SITD for EHCI.
 */
extern usb_status_t USB_HostSend(usb_host_handle hostHandle,
                                 usb_host_pipe_handle pipeHandle,
                                 usb_host_transfer_t *transfer);

/*!
 * @brief Sends a setup transfer to the pipe.
 *
 * This function request to send the setup transfer to the specified pipe.
 *
 * @param[in] hostHandle     The host handle.
 * @param[in] pipeHandle     The sending pipe handle.
 * @param[in] transfer        The transfer information.
 *
 * @retval kStatus_USB_Success              Send successfully.
 * @retval kStatus_USB_InvalidHandle        The hostHandle, pipeHandle or transfer is a NULL pointer.
 * @retval kStatus_USB_LackSwapBuffer       There is no swap buffer for KHCI.
 * @retval kStatus_USB_Error                There is no idle QTD/ITD/SITD for EHCI.
 */
extern usb_status_t USB_HostSendSetup(usb_host_handle hostHandle,
                                      usb_host_pipe_handle pipeHandle,
                                      usb_host_transfer_t *transfer);

/*!
 * @brief Receives the data from the pipe.
 *
 * This function requests to receive the transfer from the specified pipe.
 *
 * @param[in] hostHandle     The host handle.
 * @param[in] pipeHandle     The receiving pipe handle.
 * @param[in] transfer        The transfer information.
 *
 * @retval kStatus_USB_Success              Receive successfully.
 * @retval kStatus_USB_InvalidHandle        The hostHandle, pipeHandle or transfer is a NULL pointer.
 * @retval kStatus_USB_LackSwapBuffer       There is no swap buffer for KHCI.
 * @retval kStatus_USB_Error                There is no idle QTD/ITD/SITD for EHCI.
 */
extern usb_status_t USB_HostRecv(usb_host_handle hostHandle,
                                 usb_host_pipe_handle pipeHandle,
                                 usb_host_transfer_t *transfer);

/*!
 * @brief Cancel the pipe's transfers.
 *
 * This function cancels all pipe's transfers when the parameter transfer is NULL or cancels the transfers altogether.
 *
 * @param[in] hostHandle     The host handle.
 * @param[in] pipeHandle     The receiving pipe handle.
 * @param[in] transfer        The transfer information.
 *
 * @retval kStatus_USB_Success              Cancel successfully.
 * @retval kStatus_USB_InvalidHandle        The hostHandle or pipeHandle is a NULL pointer.
 */
extern usb_status_t USB_HostCancelTransfer(usb_host_handle hostHandle,
                                           usb_host_pipe_handle pipeHandle,
                                           usb_host_transfer_t *transfer);

/*!
 * @brief Allocates a transfer resource.
 *
 * This function allocates a transfer. This transfer is used to pass data information to a low level stack.
 *
 * @param[in] hostHandle     The host handle.
 * @param[out] transfer       Return the transfer.
 *
 * @retval kStatus_USB_Success              Allocate successfully.
 * @retval kStatus_USB_InvalidHandle        The hostHandle or transfer is a NULL pointer.
 * @retval kStatus_USB_Error                There is no idle transfer.
 */
extern usb_status_t USB_HostMallocTransfer(usb_host_handle hostHandle, usb_host_transfer_t **transfer);

/*!
 * @brief Frees a transfer resource.
 *
 * This function frees a transfer. This transfer is used to pass data information to a low level stack.
 *
 * @param[in] hostHandle     The host handle.
 * @param[in] transfer        Release the transfer.
 *
 * @retval kStatus_USB_Success              Free successfully.
 * @retval kStatus_USB_InvalidHandle        The hostHandle or transfer is a NULL pointer.
 */
extern usb_status_t USB_HostFreeTransfer(usb_host_handle hostHandle, usb_host_transfer_t *transfer);

/*!
 * @brief Requests the USB standard request.
 *
 * This function sends the USB standard request packet.
 *
 * @param[in] deviceHandle    The device handle for control transfer.
 * @param[in] usbRequest      A USB standard request code. See the usb_spec.h.
 * @param[in] transfer        The used transfer.
 * @param[in] param           The parameter structure is different for different request, see
 * usb_host_framework.h.
 *
 * @retval kStatus_USB_Success              Send successfully.
 * @retval kStatus_USB_InvalidHandle        The deviceHandle is a NULL pointer.
 * @retval kStatus_USB_LackSwapBuffer       There is no swap buffer for KHCI.
 * @retval kStatus_USB_Error                There is no idle QTD/ITD/SITD for EHCI,
 *                                          Or, the request is not standard request.
 */
extern usb_status_t USB_HostRequestControl(usb_device_handle deviceHandle,
                                           uint8_t usbRequest,
                                           usb_host_transfer_t *transfer,
                                           void *param);

/*!
 * @brief Opens the interface.
 *
 * This function opens the interface. It is used to notify the host driver the interface is used by APP or class driver.
 *
 * @param[in] deviceHandle      Removing device handle.
 * @param[in] interfaceHandle   Opening interface handle.
 *
 * @retval kStatus_USB_Success              Open successfully.
 * @retval kStatus_USB_InvalidHandle        The deviceHandle or interfaceHandle is a NULL pointer.
 */
extern usb_status_t USB_HostOpenDeviceInterface(usb_device_handle deviceHandle,
                                                usb_host_interface_handle interfaceHandle);

/*!
 * @brief Closes an interface.
 *
 * This function opens an interface. It is used to notify the host driver the interface is not used by APP or class
 * driver.
 *
 * @param[in] deviceHandle      Removing device handle.
 * @param[in] interfaceHandle   Opening interface handle.
 *
 * @retval kStatus_USB_Success              Close successfully.
 * @retval kStatus_USB_InvalidHandle        The deviceHandle is a NULL pointer.
 */
extern usb_status_t USB_HostCloseDeviceInterface(usb_device_handle deviceHandle,
                                                 usb_host_interface_handle interfaceHandle);

/*!
 * @brief Gets a host stack version function.
 *
 * The function is used to get the host stack version.
 *
 * @param[out] version The version structure pointer to keep the host stack version.
 *
 */
extern void USB_HostGetVersion(uint32_t *version);

#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
/*!
 * @brief Send a bus or device suspend request.
 *
 * This function is used to send a bus or device suspend request.
 *
 * @param[in] hostHandle     The host handle.
 * @param[in] deviceHandle      The device handle.
 *
 * @retval kStatus_USB_Success              Request successfully.
 * @retval kStatus_USB_InvalidHandle        The hostHandle is a NULL pointer. Or the controller handle is invalid.
 * @retval kStatus_USB_Error                There is no idle transfer.
 *                                          Or, the deviceHandle is invalid.
 *                                          Or, the request is invalid.
 */
extern usb_status_t USB_HostSuspendDeviceResquest(usb_host_handle hostHandle, usb_device_handle deviceHandle);

/*!
 * @brief Send a bus or device resume request.
 *
 * This function is used to send a bus or device resume request.
 *
 * @param[in] hostHandle     The host handle.
 * @param[in] deviceHandle      The device handle.
 *
 * @retval kStatus_USB_Success              Request successfully.
 * @retval kStatus_USB_InvalidHandle        The hostHandle is a NULL pointer. Or the controller handle is invalid.
 * @retval kStatus_USB_Error                There is no idle transfer.
 *                                          Or, the deviceHandle is invalid.
 *                                          Or, the request is invalid.
 */
extern usb_status_t USB_HostResumeDeviceResquest(usb_host_handle hostHandle, usb_device_handle deviceHandle);
#if ((defined(USB_HOST_CONFIG_LPM_L1)) && (USB_HOST_CONFIG_LPM_L1 > 0U))
/*!
 * @brief Send a bus or device suspend request.
 *
 * This function is used to send a bus or device suspend request.
 *
 * @param[in] hostHandle     The host handle.
 * @param[in] deviceHandle      The device handle.
 *@param[in] sleeptype      Bus suspend or single device suspend.
 *
 * @retval kStatus_USB_Success              Request successfully.
 * @retval kStatus_USB_InvalidHandle        The hostHandle is a NULL pointer. Or the controller handle is invalid.
 * @retval kStatus_USB_Error                There is no idle transfer.
 *                                          Or, the deviceHandle is invalid.
 *                                          Or, the request is invalid.
 */
extern usb_status_t USB_HostL1SleepDeviceResquest(usb_host_handle hostHandle,
                                                  usb_device_handle deviceHandle,
                                                  uint8_t sleepType);

/*!
 * @brief Send a bus or device resume request.
 *
 * This function is used to send a bus or device resume request.
 *
 * @param[in] hostHandle     The host handle.
 * @param[in] deviceHandle      The device handle.
 * *@param[in] sleeptype      Bus suspend or single device suspend.
 *
 * @retval kStatus_USB_Success              Request successfully.
 * @retval kStatus_USB_InvalidHandle        The hostHandle is a NULL pointer. Or the controller handle is invalid.
 * @retval kStatus_USB_Error                There is no idle transfer.
 *                                          Or, the deviceHandle is invalid.
 *                                          Or, the request is invalid.
 */
extern usb_status_t USB_HostL1ResumeDeviceResquest(usb_host_handle hostHandle,
                                                   usb_device_handle deviceHandle,
                                                   uint8_t sleepType);
/*!
 * @brief Update the lpm param.
 *
 * The function is used to configure the lpm token.
 *
 * @param[in] hostHandle The host handle.
 * @param[in] lpmParam HIRD value and whether enable remotewakeup.
 *
 */
extern usb_status_t USB_HostL1SleepDeviceResquestConfig(usb_host_handle hostHandle, uint8_t *lpmParam);
#endif
/*!
 * @brief Update the hardware tick.
 *
 * The function is used to update the hardware tick.
 *
 * @param[in] hostHandle The host handle.
 * @param[in] tick Current hardware tick(uint is ms).
 *
 */
extern usb_status_t USB_HostUpdateHwTick(usb_host_handle hostHandle, uint64_t tick);

#endif

#if ((defined(USB_HOST_CONFIG_BATTERY_CHARGER)) && (USB_HOST_CONFIG_BATTERY_CHARGER > 0U))
/*!
 * @brief Set the charger type. It is only supported on RT600 currently.
 *
 * The set charger type becomes valid in next attach.
 *
 * @param[in] hostHandle The host handle.
 * @param[in] type.
 *
 */
extern usb_status_t USB_HostSetChargerType(usb_host_handle hostHandle, uint8_t type);
#endif

/*! @}*/

#ifdef __cplusplus
}
#endif

/*! @}*/

#endif /* _USB_HOST_H_ */
