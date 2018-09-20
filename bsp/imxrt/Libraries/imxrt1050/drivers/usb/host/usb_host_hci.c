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

#include <usb/include/usb_device_config.h>
#include "fsl_common.h"
#include "usb_host.h"
#include "usb_host_hci.h"
#include "usb_host_devices.h"
#include "fsl_device_registers.h"
#if ((defined USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE))
#include "fsl_cache.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if ((defined USB_HOST_CONFIG_HUB) && (USB_HOST_CONFIG_HUB))

extern uint32_t USB_HostHubGetTotalThinkTime(usb_host_handle hostHandle, uint8_t parentHubNo);

extern usb_status_t USB_HostHubSuspendDevice(usb_host_handle hostHandle);

extern usb_status_t USB_HostHubResumeDevice(usb_host_handle hostHandle);
#endif

/*!
 * @brief get the idle host instance.
 *
 * @return  host instance pointer.
 */
static usb_host_instance_t *USB_HostGetInstance(void);

/*!
 * @brief release host instance.
 *
 * @param hostInstance  host instance pointer.
 */
static void USB_HostReleaseInstance(usb_host_instance_t *hostInstance);

/*!
 * @brief get the khci/ehci interface.
 *
 * @param controllerId    controller id.
 * @param controllerTable return controller interface structure.
 */
static void USB_HostGetControllerInterface(uint8_t controllerId,
                                           const usb_host_controller_interface_t **controllerTable);

#if ((defined USB_HOST_CONFIG_COMPLIANCE_TEST) && (USB_HOST_CONFIG_COMPLIANCE_TEST))
#if ((defined USB_HOST_CONFIG_EHCI) && (USB_HOST_CONFIG_EHCI))
extern void USB_HostEhciTestModeInit(usb_device_handle devHandle);
#endif /* USB_HOST_CONFIG_COMPLIANCE_TEST */
#if ((defined USB_HOST_CONFIG_IP3516HS) && (USB_HOST_CONFIG_IP3516HS))
extern void USB_HostIp3516HsTestModeInit(usb_device_handle devHandle);
#endif /* USB_HOST_CONFIG_COMPLIANCE_TEST */
#endif /* USB_HOST_CONFIG_EHCI */

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief USB host instance resource */
usb_host_instance_t g_UsbHostInstance[USB_HOST_CONFIG_MAX_HOST];

#if ((defined USB_HOST_CONFIG_EHCI) && (USB_HOST_CONFIG_EHCI))
#include "usb_host_ehci.h"
static const usb_host_controller_interface_t s_EhciInterface = \
{
    USB_HostEhciCreate,    USB_HostEhciDestory,  USB_HostEhciOpenPipe, USB_HostEhciClosePipe,
    USB_HostEhciWritePipe, USB_HostEhciReadpipe, USB_HostEhciIoctl,
};
#endif /* USB_HOST_CONFIG_EHCI */

#if ((defined USB_HOST_CONFIG_KHCI) && (USB_HOST_CONFIG_KHCI))
#include "usb_host_khci.h"
static const usb_host_controller_interface_t s_KhciInterface = \
{
    USB_HostKhciCreate,    USB_HostKhciDestory,  USB_HostKhciOpenPipe, USB_HostKhciClosePipe,
    USB_HostKhciWritePipe, USB_HostKhciReadpipe, USB_HostKciIoctl,
};
#endif /* USB_HOST_CONFIG_KHCI */

#if ((defined USB_HOST_CONFIG_OHCI) && (USB_HOST_CONFIG_OHCI > 0U))
#include "usb_host_ohci.h"
static const usb_host_controller_interface_t s_OhciInterface = \
{
    USB_HostOhciCreate,    USB_HostOhciDestory,  USB_HostOhciOpenPipe, USB_HostOhciClosePipe,
    USB_HostOhciWritePipe, USB_HostOhciReadPipe, USB_HostOhciIoctl,
};
#endif /* USB_HOST_CONFIG_OHCI */

#if ((defined USB_HOST_CONFIG_IP3516HS) && (USB_HOST_CONFIG_IP3516HS > 0U))
#include "usb_host_ip3516hs.h"
static const usb_host_controller_interface_t s_Ip3516HsInterface = \
{
    USB_HostIp3516HsCreate,    USB_HostIp3516HsDestory,  USB_HostIp3516HsOpenPipe, USB_HostIp3516HsClosePipe,
    USB_HostIp3516HsWritePipe, USB_HostIp3516HsReadPipe, USB_HostIp3516HsIoctl,
};
#endif /* USB_HOST_CONFIG_IP3516HS */

USB_DMA_NONINIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE) static uint8_t s_Setupbuffer[USB_HOST_CONFIG_MAX_HOST][USB_HOST_CONFIG_MAX_TRANSFERS][USB_DATA_ALIGN_SIZE_MULTIPLE(8)];
/*******************************************************************************
* Code
******************************************************************************/

#if ((defined USB_HOST_CONFIG_COMPLIANCE_TEST) && (USB_HOST_CONFIG_COMPLIANCE_TEST))
/*FUNCTION*----------------------------------------------------------------
*
* Function Name  : usb_test_mode_init
* Returned Value : None
* Comments       :
*     This function is called by common class to initialize the class driver. It
*     is called in response to a select interface call by application
*
*END*--------------------------------------------------------------------*/
usb_status_t USB_HostTestModeInit(usb_device_handle deviceHandle)
{
#if (((defined USB_HOST_CONFIG_EHCI) && (USB_HOST_CONFIG_EHCI)) || \
     ((defined USB_HOST_CONFIG_IP3516HS) && (USB_HOST_CONFIG_IP3516HS)))
    usb_host_device_instance_t *deviceInstance = (usb_host_device_instance_t *)deviceHandle;
    usb_host_instance_t *hostInstance = (usb_host_instance_t *)deviceInstance->hostHandle;
#endif
    uint32_t productId;
    uint32_t vendorId;

    usb_echo("usb host test init\r\n");
    USB_HostHelperGetPeripheralInformation(deviceHandle, kUSB_HostGetDevicePID, &productId);
    USB_HostHelperGetPeripheralInformation(deviceHandle, kUSB_HostGetDeviceVID, &vendorId);
    usb_echo(" vendor id :0x%x product id:0x%x \r\n", vendorId, productId);

    if ((productId != 0x0200U) && (productId != 0x0101) && (productId != 0x0102) && (productId != 0x0103) &&
        (productId != 0x0104) && (productId != 0x0105) && (productId != 0x0106) && (productId != 0x0107) &&
        (productId != 0x0108))
    {
        usb_echo("Unsupported Device\r\n");
    }

    if (productId == 0x0200U)
    {
        usb_echo("PET test device attached\r\n");
    }
    else
    {
#if ((defined USB_HOST_CONFIG_EHCI) && (USB_HOST_CONFIG_EHCI))
        if (hostInstance->controllerTable == &s_EhciInterface)
        {
            USB_HostEhciTestModeInit(deviceHandle);
        }
#elif((defined USB_HOST_CONFIG_IP3516HS) && (USB_HOST_CONFIG_IP3516HS))
        if (hostInstance->controllerTable == &s_Ip3516HsInterface)
        {
            USB_HostIp3516HsTestModeInit(deviceHandle);
        }
#endif
    }

    return kStatus_USB_Success;
}
#endif

static usb_host_instance_t *USB_HostGetInstance(void)
{
    uint8_t i = 0;
    uint32_t index = 0;
    USB_OSA_SR_ALLOC();
    USB_OSA_ENTER_CRITICAL();
    for (; i < USB_HOST_CONFIG_MAX_HOST; i++)
    {
        if (g_UsbHostInstance[i].occupied != 1)
        {
            uint8_t *buffer = (uint8_t *)&g_UsbHostInstance[i];
            for (uint32_t j = 0U; j < sizeof(usb_host_instance_t); j++)
            {
                buffer[j] = 0x00U;
            }
            g_UsbHostInstance[i].occupied = 1;
            USB_OSA_EXIT_CRITICAL();
            for (index = 0; index < USB_HOST_CONFIG_MAX_TRANSFERS; ++index)
            {
                g_UsbHostInstance[i].transferList[index].setupPacket =
                    (usb_setup_struct_t *)&(s_Setupbuffer[i][index][0]);
            }
            return &g_UsbHostInstance[i];
        }
    }
    USB_OSA_EXIT_CRITICAL();
    return NULL;
}

static void USB_HostReleaseInstance(usb_host_instance_t *hostInstance)
{
    USB_OSA_SR_ALLOC();
    USB_OSA_ENTER_CRITICAL();
    hostInstance->occupied = 0;
    USB_OSA_EXIT_CRITICAL();
}

static void USB_HostGetControllerInterface(uint8_t controllerId,
                                           const usb_host_controller_interface_t **controllerTable)
{
#if ((defined USB_HOST_CONFIG_KHCI) && (USB_HOST_CONFIG_KHCI))
    if (controllerId == kUSB_ControllerKhci0)
    {
        *controllerTable = &s_KhciInterface;
    }
#endif /* USB_HOST_CONFIG_KHCI */

#if ((defined USB_HOST_CONFIG_EHCI) && (USB_HOST_CONFIG_EHCI))
    if ((controllerId == kUSB_ControllerEhci0) || (controllerId == kUSB_ControllerEhci1))
    {
        *controllerTable = &s_EhciInterface;
    }
#endif /* USB_HOST_CONFIG_EHCI */

#if ((defined USB_HOST_CONFIG_OHCI) && (USB_HOST_CONFIG_OHCI > 0U))
    if (controllerId == kUSB_ControllerOhci0)
    {
        *controllerTable = &s_OhciInterface;
    }
#endif /* USB_HOST_CONFIG_OHCI */

#if ((defined USB_HOST_CONFIG_IP3516HS) && (USB_HOST_CONFIG_IP3516HS > 0U))
    if (controllerId == kUSB_ControllerIp3516Hs0)
    {
        *controllerTable = &s_Ip3516HsInterface;
    }
#endif /* USB_HOST_CONFIG_IP3516HS */
}

usb_status_t USB_HostInit(uint8_t controllerId, usb_host_handle *hostHandle, host_callback_t callbackFn)
{
    usb_status_t status = kStatus_USB_Success;
    usb_host_instance_t *hostInstance = NULL;
    usb_host_transfer_t *transferPrev = NULL;
    uint8_t i = 0;

    hostInstance = USB_HostGetInstance(); /* get one host instance */
    if (hostInstance == NULL)
    {
        return kStatus_USB_InvalidHandle;
    }

    /* get khci/ehci API table */
    USB_HostGetControllerInterface(controllerId, &hostInstance->controllerTable);
    if (hostInstance->controllerTable == NULL)
    {
        USB_HostReleaseInstance(hostInstance);
        return kStatus_USB_ControllerNotFound;
    }

    /* judge the controller interface one time at here */
    if ((hostInstance->controllerTable->controllerCreate == NULL) ||
        (hostInstance->controllerTable->controllerDestory == NULL) ||
        (hostInstance->controllerTable->controllerOpenPipe == NULL) ||
        (hostInstance->controllerTable->controllerClosePipe == NULL) ||
        (hostInstance->controllerTable->controllerWritePipe == NULL) ||
        (hostInstance->controllerTable->controllerReadPipe == NULL) ||
        (hostInstance->controllerTable->controllerIoctl == NULL))
    {
        return kStatus_USB_Error;
    }

    /* HOST instance init*/
    hostInstance->controllerId = controllerId;
    hostInstance->deviceCallback = callbackFn;
    hostInstance->deviceList = NULL;
    if (kStatus_USB_OSA_Success != USB_OsaMutexCreate(&hostInstance->hostMutex))
    {
        USB_HostReleaseInstance(hostInstance);
#ifdef HOST_ECHO
        usb_echo("host init: create host mutex fail\r\n");
#endif
        return kStatus_USB_Error;
    }

    /* initialize transfer list */

    hostInstance->transferHead = &hostInstance->transferList[0];
    transferPrev = hostInstance->transferHead;
    for (i = 1; i < USB_HOST_CONFIG_MAX_TRANSFERS; ++i)
    {
        transferPrev->next = &hostInstance->transferList[i];
        transferPrev = transferPrev->next;
    }

    /* controller create */
    status =
        hostInstance->controllerTable->controllerCreate(controllerId, hostInstance, &(hostInstance->controllerHandle));
    if ((status != kStatus_USB_Success) || (hostInstance->controllerHandle == NULL))
    {
        USB_OsaMutexDestroy(hostInstance->hostMutex);
        USB_HostReleaseInstance(hostInstance);
#ifdef HOST_ECHO
        usb_echo("host init: controller init fail\r\n");
#endif
        return kStatus_USB_Error;
    }

    *hostHandle = hostInstance;
    return kStatus_USB_Success;
}

usb_status_t USB_HostDeinit(usb_host_handle hostHandle)
{
    usb_status_t status = kStatus_USB_Success;
    usb_host_instance_t *hostInstance = (usb_host_instance_t *)hostHandle;
    usb_host_device_instance_t *deviceInstance = NULL;

    if (hostHandle == NULL)
    {
        return kStatus_USB_InvalidHandle;
    }

    /* device list detach */
    deviceInstance = (usb_host_device_instance_t *)hostInstance->deviceList;
    while (deviceInstance != NULL)
    {
        deviceInstance = (usb_host_device_instance_t *)hostInstance->deviceList;
        USB_HostDetachDeviceInternal(hostHandle, deviceInstance);
    }

    /* controller instance destory */
    status = hostInstance->controllerTable->controllerDestory(hostInstance->controllerHandle);
    hostInstance->controllerHandle = NULL;
    if (status != kStatus_USB_Success)
    {
#ifdef HOST_ECHO
        usb_echo("host controller destory fail\r\n");
#endif
    }

    /* resource release */
    if (hostInstance->hostMutex)
    {
        USB_OsaMutexDestroy(hostInstance->hostMutex);
        hostInstance->hostMutex = NULL;
    }
    USB_HostReleaseInstance(hostInstance);

    return status;
}

usb_status_t USB_HostOpenPipe(usb_host_handle hostHandle,
                              usb_host_pipe_handle *pipeHandle,
                              usb_host_pipe_init_t *pipeInit)
{
    usb_status_t status = kStatus_USB_Success;
    usb_host_instance_t *hostInstance = (usb_host_instance_t *)hostHandle;

    if ((hostHandle == NULL) || (pipeInit == NULL))
    {
        return kStatus_USB_InvalidHandle;
    }

    /* call controller open pipe interface */
    status = hostInstance->controllerTable->controllerOpenPipe(hostInstance->controllerHandle, pipeHandle, pipeInit);

    return status;
}

usb_status_t USB_HostClosePipe(usb_host_handle hostHandle, usb_host_pipe_handle pipeHandle)
{
    usb_status_t status = kStatus_USB_Success;
    usb_host_instance_t *hostInstance = (usb_host_instance_t *)hostHandle;

    if ((hostHandle == NULL) || (pipeHandle == NULL))
    {
        return kStatus_USB_InvalidHandle;
    }

    /* call controller close pipe interface */
    status = hostInstance->controllerTable->controllerClosePipe(hostInstance->controllerHandle, pipeHandle);

    return status;
}

usb_status_t USB_HostSend(usb_host_handle hostHandle, usb_host_pipe_handle pipeHandle, usb_host_transfer_t *transfer)
{
    usb_status_t status = kStatus_USB_Success;
    usb_host_instance_t *hostInstance = (usb_host_instance_t *)hostHandle;

    if ((hostHandle == NULL) || (pipeHandle == NULL) || (transfer == NULL))
    {
        return kStatus_USB_InvalidHandle;
    }

    /* initialize transfer */
    transfer->transferSofar = 0;
    transfer->direction = USB_OUT;

    USB_HostLock(); /* This api can be called by host task and app task */
/* keep this code: in normal situation application will guarantee the device is attached when call send/receive function
 */
#if 0
    if ((USB_HostValidateDevice(pipe_ptr->deviceHandle) != kStatus_USB_Success) || (!(USB_HostGetDeviceAttachState(pipe_ptr->deviceHandle))))
    {
        USB_HostUnlock();
        return status;
    }
#endif
/* call controller write pipe interface */
#if ((defined USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE))
    if (transfer->transferLength > 0)
    {
        DCACHE_CleanByRange((uint32_t)transfer->transferBuffer, transfer->transferLength);
    }
#endif
    status = hostInstance->controllerTable->controllerWritePipe(hostInstance->controllerHandle, pipeHandle, transfer);

    USB_HostUnlock();
    return status;
}

usb_status_t USB_HostSendSetup(usb_host_handle hostHandle,
                               usb_host_pipe_handle pipeHandle,
                               usb_host_transfer_t *transfer)
{
    usb_status_t status = kStatus_USB_Success;
    usb_host_instance_t *hostInstance = (usb_host_instance_t *)hostHandle;

    if ((hostHandle == NULL) || (pipeHandle == NULL) || (transfer == NULL))
    {
        return kStatus_USB_InvalidHandle;
    }

    /* initialize transfer */
    transfer->transferSofar = 0;
    transfer->next = NULL;
    transfer->setupStatus = 0;
    if ((transfer->setupPacket->bmRequestType & USB_REQUEST_TYPE_DIR_MASK) == USB_REQUEST_TYPE_DIR_IN)
    {
        transfer->direction = USB_IN;
    }
    else
    {
        transfer->direction = USB_OUT;
    }

    USB_HostLock(); /* This API can be called by host task and application task */
/* keep this code: in normal situation application will guarantee the device is attached when call send/receive function
 */
#if 0
    if ((USB_HostValidateDevice(pipe_ptr->deviceHandle) != kStatus_USB_Success) || (!(USB_HostGetDeviceAttachState(pipe_ptr->deviceHandle))))
    {
        USB_HostUnlock();
        return status;
    }
#endif
/* call controller write pipe interface */
#if ((defined USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE))
    DCACHE_CleanByRange((uint32_t)&transfer->setupPacket->bmRequestType, sizeof(usb_setup_struct_t));
    if (transfer->transferLength > 0)
    {
        DCACHE_CleanInvalidateByRange((uint32_t)transfer->transferBuffer, transfer->transferLength);
    }
#endif
    status = hostInstance->controllerTable->controllerWritePipe(hostInstance->controllerHandle, pipeHandle, transfer);

    USB_HostUnlock();
    return status;
}

usb_status_t USB_HostRecv(usb_host_handle hostHandle, usb_host_pipe_handle pipeHandle, usb_host_transfer_t *transfer)
{
    usb_status_t status = kStatus_USB_Success;
    usb_host_instance_t *hostInstance = (usb_host_instance_t *)hostHandle;

    if ((hostHandle == NULL) || (pipeHandle == NULL) || (transfer == NULL))
    {
        return kStatus_USB_InvalidHandle;
    }

    /* initialize transfer */
    transfer->transferSofar = 0;
    transfer->direction = USB_IN;

    USB_HostLock(); /* This API can be called by host task and application task */
/* keep this code: in normal situation application will guarantee the device is attached when call send/receive function
 */
#if 0
    if ((USB_HostValidateDevice(pipe_ptr->deviceHandle) != kStatus_USB_Success) || (!(USB_HostGetDeviceAttachState(pipe_ptr->deviceHandle))))
    {
        USB_HostUnlock();
        return status;
    }
#endif

#if ((defined USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE))
    if (transfer->transferLength > 0)
    {
        DCACHE_CleanInvalidateByRange((uint32_t)transfer->transferBuffer, transfer->transferLength);
    }
#endif
    status = hostInstance->controllerTable->controllerReadPipe(hostInstance->controllerHandle, pipeHandle, transfer);

    USB_HostUnlock();
    return status;
}

usb_status_t USB_HostCancelTransfer(usb_host_handle hostHandle,
                                    usb_host_pipe_handle pipeHandle,
                                    usb_host_transfer_t *transfer)
{
    usb_status_t status = kStatus_USB_Success;
    usb_host_instance_t *hostInstance = (usb_host_instance_t *)hostHandle;
    usb_host_cancel_param_t cancelParam;

    if ((hostHandle == NULL) || (pipeHandle == NULL))
    {
        return kStatus_USB_InvalidHandle;
    }

    /* initialize cancel parameter */
    cancelParam.pipeHandle = pipeHandle;
    cancelParam.transfer = transfer;

    /* USB_HostLock(); This api can be called by host task and app task */
    status = hostInstance->controllerTable->controllerIoctl(hostInstance->controllerHandle, kUSB_HostCancelTransfer,
                                                            &cancelParam);
    /* USB_HostUnlock(); */

    return status;
}

usb_status_t USB_HostMallocTransfer(usb_host_handle hostHandle, usb_host_transfer_t **transfer)
{
    usb_host_instance_t *hostInstance = (usb_host_instance_t *)hostHandle;

    if ((hostHandle == NULL) || (transfer == NULL))
    {
        return kStatus_USB_InvalidHandle;
    }

    /* get one from the transfer_head */
    USB_HostLock();
    if (hostInstance->transferHead != NULL)
    {
        *transfer = hostInstance->transferHead;
        hostInstance->transferHead = hostInstance->transferHead->next;
        USB_HostUnlock();
        return kStatus_USB_Success;
    }
    else
    {
        *transfer = NULL;
        USB_HostUnlock();
        return kStatus_USB_Error;
    }
}

usb_status_t USB_HostFreeTransfer(usb_host_handle hostHandle, usb_host_transfer_t *transfer)
{
    usb_host_instance_t *hostInstance = (usb_host_instance_t *)hostHandle;

    if (hostHandle == NULL)
    {
        return kStatus_USB_InvalidHandle;
    }
    if (transfer == NULL)
    {
        return kStatus_USB_Success;
    }

    /* release one to the transfer_head */
    USB_HostLock();
    transfer->next = hostInstance->transferHead;
    hostInstance->transferHead = transfer;
    USB_HostUnlock();
    return kStatus_USB_Success;
}

usb_status_t USB_HostHelperGetPeripheralInformation(usb_device_handle deviceHandle,
                                                    uint32_t infoCode,
                                                    uint32_t *infoValue)
{
    usb_host_device_instance_t *deviceInstance = (usb_host_device_instance_t *)deviceHandle;
    if ((deviceHandle == NULL) || (infoValue == NULL))
    {
        return kStatus_USB_InvalidParameter;
    }

    switch (infoCode)
    {
        case kUSB_HostGetDeviceAddress: /* device address */
            *infoValue = (uint32_t)deviceInstance->setAddress;
            break;

        case kUSB_HostGetDeviceControlPipe: /* device control pipe */
            *infoValue = (uint32_t)deviceInstance->controlPipe;
            break;

        case kUSB_HostGetHostHandle: /* device host handle */
            *infoValue = (uint32_t)deviceInstance->hostHandle;
            break;

#if ((defined USB_HOST_CONFIG_HUB) && (USB_HOST_CONFIG_HUB))
        case kUSB_HostGetDeviceHubNumber: /* device hub address */
            *infoValue = (uint32_t)deviceInstance->hubNumber;
            break;

        case kUSB_HostGetDevicePortNumber: /* device port no */
            *infoValue = (uint32_t)deviceInstance->portNumber;
            break;

        case kUSB_HostGetDeviceLevel: /* device level */
            *infoValue = (uint32_t)deviceInstance->level;
            break;

        case kUSB_HostGetDeviceHSHubNumber: /* device high-speed hub address */
            *infoValue = (uint32_t)deviceInstance->hsHubNumber;
            break;

        case kUSB_HostGetDeviceHSHubPort: /* device high-speed hub port no */
            *infoValue = (uint32_t)deviceInstance->hsHubPort;
            break;

        case kUSB_HostGetHubThinkTime: /* device hub think time */
            *infoValue = USB_HostHubGetTotalThinkTime(deviceInstance->hostHandle, deviceInstance->hubNumber);
            break;
#else
        case kUSB_HostGetDeviceHubNumber:   /* device hub address */
        case kUSB_HostGetDevicePortNumber:  /* device port no */
        case kUSB_HostGetDeviceHSHubNumber: /* device high-speed hub address */
        case kUSB_HostGetDeviceHSHubPort:   /* device high-speed hub port no */
        case kUSB_HostGetHubThinkTime:      /* device hub think time */
            *infoValue = 0;
            break;
        case kUSB_HostGetDeviceLevel: /* device level */
            *infoValue = 1;
            break;
#endif /* USB_HOST_CONFIG_HUB */

        case kUSB_HostGetDeviceSpeed: /* device speed */
            *infoValue = (uint32_t)deviceInstance->speed;
            break;

        case kUSB_HostGetDevicePID: /* device pid */
            *infoValue = (uint32_t)USB_SHORT_FROM_LITTLE_ENDIAN_ADDRESS(deviceInstance->deviceDescriptor->idProduct);
            break;

        case kUSB_HostGetDeviceVID: /* device vid */
            *infoValue = (uint32_t)USB_SHORT_FROM_LITTLE_ENDIAN_ADDRESS(deviceInstance->deviceDescriptor->idVendor);
            break;

        case kUSB_HostGetDeviceConfigIndex: /* device config index */
            *infoValue = (uint32_t)deviceInstance->configurationValue - 1U;
            break;

        case kUSB_HostGetConfigurationDes: /* configuration descriptor pointer */
            *infoValue = (uint32_t)deviceInstance->configurationDesc;
            break;

        case kUSB_HostGetConfigurationLength: /* configuration descriptor length */
            *infoValue = (uint32_t)deviceInstance->configurationLen;
            break;

        default:
            return kStatus_USB_Error;
    }

    return kStatus_USB_Success;
}

usb_status_t USB_HostHelperParseAlternateSetting(usb_host_interface_handle interfaceHandle,
                                                 uint8_t alternateSetting,
                                                 usb_host_interface_t *interface)
{
    uint32_t endPosition;
    usb_descriptor_union_t *unionDes;
    usb_host_ep_t *epParse;

    if (interfaceHandle == NULL)
    {
        return kStatus_USB_InvalidHandle;
    }

    if (alternateSetting == 0)
    {
        return kStatus_USB_InvalidParameter;
    }

    /* parse configuration descriptor */
    unionDes = (usb_descriptor_union_t *)((usb_host_interface_t *)interfaceHandle)
                   ->interfaceDesc; /* interface extend descriptor start */
    endPosition =
        (uint32_t)unionDes +
        ((usb_host_interface_t *)interfaceHandle)->interfaceExtensionLength; /* interface extend descriptor end */
    unionDes = (usb_descriptor_union_t *)((uint32_t)unionDes + unionDes->common.bLength);

    /* search for the alternate setting interface descritpor */
    while ((uint32_t)unionDes < endPosition)
    {
        if (unionDes->interface.bDescriptorType == USB_DESCRIPTOR_TYPE_INTERFACE)
        {
            if (unionDes->interface.bAlternateSetting == alternateSetting)
            {
                break;
            }
            else
            {
                unionDes = (usb_descriptor_union_t *)((uint32_t)unionDes + unionDes->common.bLength);
            }
        }
        else
        {
            unionDes = (usb_descriptor_union_t *)((uint32_t)unionDes + unionDes->common.bLength);
        }
    }
    if ((uint32_t)unionDes >= endPosition)
    {
        return kStatus_USB_Error;
    }

    /* initialize interface handle structure instance */
    interface->interfaceDesc = &unionDes->interface;
    interface->alternateSettingNumber = 0;
    interface->epCount = 0;
    interface->interfaceExtension = NULL;
    interface->interfaceExtensionLength = 0;
    interface->interfaceIndex = unionDes->interface.bInterfaceNumber;

    /* search for endpoint descriptor start position */
    unionDes = (usb_descriptor_union_t *)((uint32_t)unionDes + unionDes->common.bLength);
    while ((uint32_t)unionDes < endPosition)
    {
        if ((unionDes->common.bDescriptorType != USB_DESCRIPTOR_TYPE_INTERFACE) &&
            (unionDes->common.bDescriptorType != USB_DESCRIPTOR_TYPE_ENDPOINT))
        {
            if (interface->interfaceExtension == NULL)
            {
                interface->interfaceExtension = (uint8_t *)unionDes;
            }
            interface->interfaceExtensionLength += unionDes->common.bLength;
            unionDes = (usb_descriptor_union_t *)((uint32_t)unionDes + unionDes->common.bLength);
        }
        else
        {
            break;
        }
    }

    /* parse endpoint descriptor */
    if (interface->interfaceDesc->bNumEndpoints != 0)
    {
        if ((unionDes->common.bDescriptorType != USB_DESCRIPTOR_TYPE_ENDPOINT) ||
            (interface->interfaceDesc->bNumEndpoints > USB_HOST_CONFIG_INTERFACE_MAX_EP))
        {
#ifdef HOST_ECHO
            usb_echo("interface descriptor error\n");
#endif
            return kStatus_USB_Error;
        }
        for (; interface->epCount < interface->interfaceDesc->bNumEndpoints; (interface->epCount)++)
        {
            if (((uint32_t)unionDes >= endPosition) ||
                (unionDes->common.bDescriptorType != USB_DESCRIPTOR_TYPE_ENDPOINT))
            {
#ifdef HOST_ECHO
                usb_echo("endpoint descriptor error\n");
#endif
                return kStatus_USB_Error;
            }
            epParse = (usb_host_ep_t *)&interface->epList[interface->epCount];
            epParse->epDesc = (usb_descriptor_endpoint_t *)unionDes;
            epParse->epExtensionLength = 0;
            epParse->epExtension = NULL;
            unionDes = (usb_descriptor_union_t *)((uint32_t)unionDes + unionDes->common.bLength);
            while ((uint32_t)unionDes < endPosition)
            {
                if ((unionDes->common.bDescriptorType != USB_DESCRIPTOR_TYPE_ENDPOINT) &&
                    (unionDes->common.bDescriptorType != USB_DESCRIPTOR_TYPE_INTERFACE))
                {
                    if (epParse->epExtension == NULL)
                    {
                        epParse->epExtension = (uint8_t *)unionDes;
                    }
                    epParse->epExtensionLength += unionDes->common.bLength;
                    unionDes = (usb_descriptor_union_t *)((uint32_t)unionDes + unionDes->common.bLength);
                }
                else
                {
                    break;
                }
            }
        }
    }

    return kStatus_USB_Success;
}

void USB_HostGetVersion(uint32_t *version)
{
    if (version)
    {
        *version =
            (uint32_t)USB_MAKE_VERSION(USB_STACK_VERSION_MAJOR, USB_STACK_VERSION_MINOR, USB_STACK_VERSION_BUGFIX);
    }
}

#if ((defined(USB_HOST_CONFIG_LOW_POWER_MODE)) && (USB_HOST_CONFIG_LOW_POWER_MODE > 0U))
/* Send BUS or specific device suepend request */
usb_status_t USB_HostSuspendDeviceResquest(usb_host_handle hostHandle, usb_device_handle deviceHandle)
{
    usb_host_instance_t *hostInstance;
    usb_host_device_instance_t *deviceInstance;
    usb_status_t status = kStatus_USB_Error;
    usb_host_bus_control_t type = kUSB_HostBusSuspend;

    if (hostHandle == NULL)
    {
        return kStatus_USB_InvalidHandle;
    }
    hostInstance = (usb_host_instance_t *)hostHandle;

    hostInstance->suspendedDevice = (void *)deviceHandle;

    if (NULL == deviceHandle)
    {
#if ((defined USB_HOST_CONFIG_HUB) && (USB_HOST_CONFIG_HUB))
        status = USB_HostHubSuspendDevice(hostInstance);
#else
        status =
            hostInstance->controllerTable->controllerIoctl(hostInstance->controllerHandle, kUSB_HostBusControl, &type);
#endif
    }
    else
    {
#if ((defined USB_HOST_CONFIG_HUB) && (USB_HOST_CONFIG_HUB))
        deviceInstance = (usb_host_device_instance_t *)deviceHandle;
        if (0 == deviceInstance->hubNumber)
        {
#endif
            if (hostInstance->deviceList == deviceHandle)
            {
                status = hostInstance->controllerTable->controllerIoctl(hostInstance->controllerHandle,
                                                                        kUSB_HostBusControl, &type);
            }
#if ((defined USB_HOST_CONFIG_HUB) && (USB_HOST_CONFIG_HUB))
        }
        else
        {
            if (kStatus_USB_Success == USB_HostValidateDevice(hostInstance, deviceHandle))
            {
                status = USB_HostHubSuspendDevice(hostInstance);
            }
        }
#endif
    }
    if (kStatus_USB_Error == status)
    {
        hostInstance->suspendedDevice = NULL;
    }
    return status;
}

/* Send BUS or specific device resume request */
usb_status_t USB_HostResumeDeviceResquest(usb_host_handle hostHandle, usb_device_handle deviceHandle)
{
    usb_host_instance_t *hostInstance;
    usb_host_device_instance_t *deviceInstance;
    usb_status_t status = kStatus_USB_Error;
    usb_host_bus_control_t type = kUSB_HostBusResume;

    if (hostHandle == NULL)
    {
        return kStatus_USB_InvalidHandle;
    }
    hostInstance = (usb_host_instance_t *)hostHandle;

    if (hostInstance->suspendedDevice != deviceHandle)
    {
        return kStatus_USB_InvalidParameter;
    }
    hostInstance->suspendedDevice = (void *)deviceHandle;

    if (NULL == deviceHandle)
    {
        status =
            hostInstance->controllerTable->controllerIoctl(hostInstance->controllerHandle, kUSB_HostBusControl, &type);
    }
    else
    {
#if ((defined USB_HOST_CONFIG_HUB) && (USB_HOST_CONFIG_HUB))
        deviceInstance = (usb_host_device_instance_t *)deviceHandle;
        if (0 == deviceInstance->hubNumber)
        {
#endif
            if (hostInstance->deviceList == deviceHandle)
            {
                status = hostInstance->controllerTable->controllerIoctl(hostInstance->controllerHandle,
                                                                        kUSB_HostBusControl, &type);
            }
#if ((defined USB_HOST_CONFIG_HUB) && (USB_HOST_CONFIG_HUB))
        }
        else
        {
            if (kStatus_USB_Success == USB_HostValidateDevice(hostInstance, deviceHandle))
            {
                status = USB_HostHubResumeDevice(hostInstance);
            }
        }
#endif
    }

    return status;
}
#if ((defined(USB_HOST_CONFIG_LPM_L1)) && (USB_HOST_CONFIG_LPM_L1 > 0U))
/* Send BUS or specific device suepend request */
usb_status_t USB_HostL1SleepDeviceResquest(usb_host_handle hostHandle,
                                           usb_device_handle deviceHandle,
                                           uint8_t sleepType)
{
    usb_host_instance_t *hostInstance;
    usb_status_t status = kStatus_USB_Error;
    usb_host_bus_control_t type = kUSB_HostBusL1Sleep;

    if (hostHandle == NULL)
    {
        return kStatus_USB_InvalidHandle;
    }
    hostInstance = (usb_host_instance_t *)hostHandle;

    hostInstance->suspendedDevice = (void *)deviceHandle;

    if (1U == sleepType)
    {
        /*#if ((defined USB_HOST_CONFIG_HUB) && (USB_HOST_CONFIG_HUB))*/
        /*To do, implete hub L1 suspend device*/
        /*#else*/
        status =
            hostInstance->controllerTable->controllerIoctl(hostInstance->controllerHandle, kUSB_HostBusControl, &type);
        /*#endif*/
    }
    else
    {
#if ((defined USB_HOST_CONFIG_HUB) && (USB_HOST_CONFIG_HUB))
/*To do, if device hub number is 0, need suspend the bus ,else suspend the corresponding device*/
#endif
        if (hostInstance->deviceList == deviceHandle)
        {
            status = hostInstance->controllerTable->controllerIoctl(hostInstance->controllerHandle, kUSB_HostBusControl,
                                                                    &type);
        }
    }
    if (kStatus_USB_Error == status)
    {
        hostInstance->suspendedDevice = NULL;
    }
    return status;
}
/* Send BUS or specific device suepend request */
usb_status_t USB_HostL1SleepDeviceResquestConfig(usb_host_handle hostHandle, uint8_t *lpmParam)
{
    usb_host_instance_t *hostInstance;
    usb_status_t status = kStatus_USB_Error;

    if (hostHandle == NULL)
    {
        return kStatus_USB_InvalidHandle;
    }
    hostInstance = (usb_host_instance_t *)hostHandle;

    status =
        hostInstance->controllerTable->controllerIoctl(hostInstance->controllerHandle, kUSB_HostL1Config, lpmParam);

    return status;
}

/* Send BUS or specific device resume request */
usb_status_t USB_HostL1ResumeDeviceResquest(usb_host_handle hostHandle,
                                            usb_device_handle deviceHandle,
                                            uint8_t sleepType)
{
    usb_host_instance_t *hostInstance;

    usb_status_t status = kStatus_USB_Error;
    usb_host_bus_control_t type = kUSB_HostBusL1Resume;

    if (hostHandle == NULL)
    {
        return kStatus_USB_InvalidHandle;
    }
    hostInstance = (usb_host_instance_t *)hostHandle;

    if (1U == sleepType)
    {
        status =
            hostInstance->controllerTable->controllerIoctl(hostInstance->controllerHandle, kUSB_HostBusControl, &type);
    }
    else
    {
#if ((defined USB_HOST_CONFIG_HUB) && (USB_HOST_CONFIG_HUB))
/*To do, if device hub number is 0, need suspend the bus ,else suspend the corresponding device*/

#endif
        if (hostInstance->deviceList == deviceHandle)
        {
            status = hostInstance->controllerTable->controllerIoctl(hostInstance->controllerHandle, kUSB_HostBusControl,
                                                                    &type);
        }
    }

    return status;
}
#endif
/* Update HW tick(unit is ms) */
usb_status_t USB_HostUpdateHwTick(usb_host_handle hostHandle, uint64_t tick)
{
    usb_host_instance_t *hostInstance;
    usb_status_t status = kStatus_USB_Success;

    if (hostHandle == NULL)
    {
        return kStatus_USB_InvalidHandle;
    }
    hostInstance = (usb_host_instance_t *)hostHandle;

    hostInstance->hwTick = tick;

    return status;
}
#endif
