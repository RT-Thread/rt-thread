/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _USB_HOST_HCI_H_
#define _USB_HOST_HCI_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief USB host lock */
#define USB_HostLock() OSA_MutexLock(hostInstance->hostMutex, USB_OSA_WAIT_TIMEOUT)
/*! @brief USB host unlock */
#define USB_HostUnlock() OSA_MutexUnlock(hostInstance->hostMutex)

/*!
 * @addtogroup usb_host_controller_driver
 * @{
 */

/*! @brief USB host controller control code */
typedef enum _usb_host_controller_control
{
    kUSB_HostCancelTransfer = 1U,          /*!< Cancel transfer code */
    kUSB_HostBusControl,                   /*!< Bus control code */
    kUSB_HostGetFrameNumber,               /*!< Get frame number code */
    kUSB_HostUpdateControlEndpointAddress, /*!< Update control endpoint address */
    kUSB_HostUpdateControlPacketSize,      /*!< Update control endpoint maximum  packet size */
    kUSB_HostPortAttachDisable,            /*!< Disable the port attach event */
    kUSB_HostPortAttachEnable,             /*!< Enable the port attach event */
    kUSB_HostL1Config,                     /*!< L1 suspend Bus control code */
    kUSB_HostSetChargerType,               /*!< set charger type */
#if ((defined USB_HOST_CONFIG_COMPLIANCE_TEST) && (USB_HOST_CONFIG_COMPLIANCE_TEST))
    kUSB_HostTestModeInit, /*!< intialize charger type */
#endif
} usb_host_controller_control_t;

/*! @brief USB host controller bus control code */
typedef enum _usb_host_bus_control
{
    kUSB_HostBusReset = 1U,    /*!< Reset bus */
    kUSB_HostBusRestart,       /*!< Restart bus */
    kUSB_HostBusEnableAttach,  /*!< Enable attach */
    kUSB_HostBusDisableAttach, /*!< Disable attach */
    kUSB_HostBusSuspend,       /*!< Suspend BUS */
    kUSB_HostBusResume,        /*!< Resume BUS */
    kUSB_HostBusL1SuspendInit, /*!< L1 Suspend BUS */
    kUSB_HostBusL1Sleep,       /*!< L1 Suspend BUS */
    kUSB_HostBusL1Resume,      /*!< L1 Resume BUS */
} usb_host_bus_control_t;

/*! @brief USB host controller interface structure */
typedef struct _usb_host_controller_interface
{
    usb_status_t (*controllerCreate)(
        uint8_t controllerId,
        usb_host_handle upperLayerHandle,
        usb_host_controller_handle *controllerHandle); /*!< Create a controller instance function prototype*/
    usb_status_t (*controllerDestory)(
        usb_host_controller_handle controllerHandle); /*!< Destroy a controller instance function prototype*/
    usb_status_t (*controllerOpenPipe)(usb_host_controller_handle controllerHandle,
                                       usb_host_pipe_handle *pipeHandle,
                                       usb_host_pipe_init_t *pipeInit); /*!< Open a controller pipe function prototype*/
    usb_status_t (*controllerClosePipe)(
        usb_host_controller_handle controllerHandle,
        usb_host_pipe_handle pipeHandle); /*!< Close a controller pipe function prototype*/
    usb_status_t (*controllerWritePipe)(usb_host_controller_handle controllerHandle,
                                        usb_host_pipe_handle pipeHandle,
                                        usb_host_transfer_t *transfer); /*!< Write data to a pipe function prototype*/
    usb_status_t (*controllerReadPipe)(usb_host_controller_handle controllerHandle,
                                       usb_host_pipe_handle pipeHandle,
                                       usb_host_transfer_t *transfer); /*!< Read data from a pipe function prototype*/
    usb_status_t (*controllerIoctl)(usb_host_controller_handle controllerHandle,
                                    uint32_t ioctlEvent,
                                    void *ioctlParam); /*!< Control a controller function prototype*/
} usb_host_controller_interface_t;
#if ((defined USB_HOST_CONFIG_COMPLIANCE_TEST) && (USB_HOST_CONFIG_COMPLIANCE_TEST))
usb_status_t USB_HostTestModeInit(usb_device_handle deviceHandle);
#endif
/*! @}*/

/*!
 * @addtogroup usb_host_drv
 * @{
 */

/*! @brief USB host instance structure */
typedef struct _usb_host_instance
{
    void *controllerHandle;                                          /*!< The low level controller handle*/
    host_callback_t deviceCallback;                                  /*!< Device attach/detach callback*/
    osa_mutex_handle_t hostMutex;                                    /*!< Host layer mutex*/
    uint32_t mutexBuffer[(OSA_MUTEX_HANDLE_SIZE + 3) / 4];           /*!< Host layer mutex*/
    usb_host_transfer_t transferList[USB_HOST_CONFIG_MAX_TRANSFERS]; /*!< Transfer resource*/
    usb_host_transfer_t *transferHead;                               /*!< Idle transfer head*/
    const usb_host_controller_interface_t *controllerTable;          /*!< KHCI/EHCI interface*/
    void *deviceList;                                                /*!< Device list*/
#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
    void *suspendedDevice;    /*!< Suspended device handle*/
    volatile uint64_t hwTick; /*!< Current hw tick(ms)*/
    uint8_t sleepType;        /*!< L1 LPM device handle*/
#endif
    uint8_t addressBitMap[16]; /*!< Used for address allocation. The first bit is the address 1, second bit is the
                                  address 2*/
    uint8_t occupied;          /*!< 0 - the instance is not occupied; 1 - the instance is occupied*/
    uint8_t controllerId;      /*!< The controller ID*/
} usb_host_instance_t;

extern usb_host_instance_t g_UsbHostInstance[USB_HOST_CONFIG_MAX_HOST];
/*! @}*/

#endif /* _USB_HOST_HCI_H_ */
