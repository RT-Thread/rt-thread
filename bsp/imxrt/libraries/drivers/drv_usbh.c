/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017-10-30     ZYH               the first version
 * 2019-12-19     tyustli           port to stm32 series
 * 2021-01-19     Leslie Lee        port to imxrt series
 */
#include <rtthread.h>

#if defined(BSP_USB0_HOST) || defined(BSP_USB1_HOST)
#include "drv_usbh.h"
#include <usb/include/usb_host_config.h>
#include <usb/include/usb.h>
#include <usb/phy/usb_phy.h>
#include <usb/host/usb_host.h>
#include <usb/host/usb_host_hci.h>
#include <usb/host/usb_host_ehci.h>
#include <rtdevice.h>


/* USB PHY configuration */
#ifndef BOARD_USB_PHY_D_CAL
#define BOARD_USB_PHY_D_CAL (0x0CU)
#endif
#ifndef BOARD_USB_PHY_TXCAL45DP
#define BOARD_USB_PHY_TXCAL45DP (0x06U)
#endif
#ifndef BOARD_USB_PHY_TXCAL45DM
#define BOARD_USB_PHY_TXCAL45DM (0x06U)
#endif

#define USB_HOST_INTERRUPT_PRIORITY 3

enum
{
#ifdef BSP_USB0_HOST
    USBH0_INDEX,
#endif
#ifdef BSP_USB1_HOST
    USBH1_INDEX,
#endif
};

struct imxrt_usb_host_pipe
{
    usb_host_pipe_handle pipe_handle;
    struct rt_completion urb_completion;
    usb_status_t transfer_status;
};

struct imxrt_usb_host
{
    struct uhcd uhcd;
    usb_host_handle host_handle;
    usb_device_handle device_handle;
    struct imxrt_usb_host_pipe pipes[16];
    volatile rt_bool_t connect_status;
    char *name;
};

static struct imxrt_usb_host imxrt_usb_host_obj[] =
{
#ifdef BSP_USB0_HOST
    {
        .connect_status = RT_FALSE,
        .name           = "usbh0"
    },
#endif
#ifdef BSP_USB1_HOST
    {
        .connect_status = RT_FALSE,
        .name           = "usbh1"
    },
#endif
};

static void _imxrt_usb_host_send_callback(void *param, usb_host_transfer_t *transfer, usb_status_t status)
{
    struct imxrt_usb_host_pipe *pipe = (struct imxrt_usb_host_pipe *)param;
    pipe->transfer_status = status;
    rt_completion_done(&pipe->urb_completion);
}


/*!
 * @brief Initializes USB specific setting that was not set by the Clocks tool.
 */
static void USB_HostClockInit(usb_controller_index_t controller_id)
{
    usb_phy_config_struct_t phyConfig = {
        BOARD_USB_PHY_D_CAL, BOARD_USB_PHY_TXCAL45DP, BOARD_USB_PHY_TXCAL45DM,
    };
    uint32_t notUsed = 0;

    if (controller_id == kUSB_ControllerEhci0)
    {
        CLOCK_EnableUsbhs0PhyPllClock(kCLOCK_Usbphy480M, 480000000U);
        CLOCK_EnableUsbhs0Clock(kCLOCK_Usb480M, 480000000U);
    }
    else
    {
        CLOCK_EnableUsbhs1PhyPllClock(kCLOCK_Usbphy480M, 480000000U);
        CLOCK_EnableUsbhs1Clock(kCLOCK_Usb480M, 480000000U);
    }

    USB_EhciPhyInit(controller_id, 24000000U, &phyConfig);
}

/*!
 * @brief Enables interrupt service routines for device.
 */
void USB_HostIsrEnable(usb_controller_index_t controller_id)
{
    uint8_t irqNumber;
#if ((defined USB_HOST_CONFIG_EHCI) && (USB_HOST_CONFIG_EHCI > 0U))
    IRQn_Type usbHOSTEhciIrq[] = USBHS_IRQS;
    irqNumber = usbHOSTEhciIrq[controller_id - kUSB_ControllerEhci0];
#endif
/* Install isr, set priority, and enable IRQ. */
#if defined(__GIC_PRIO_BITS)
    GIC_SetPriority((IRQn_Type)irqNumber, USB_HOST_INTERRUPT_PRIORITY);
#else
    NVIC_SetPriority((IRQn_Type)irqNumber, USB_HOST_INTERRUPT_PRIORITY);
#endif
    EnableIRQ((IRQn_Type)irqNumber);
}

#ifdef BSP_USB0_HOST
void USB_OTG1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    USB_HostEhciIsrFunction(imxrt_usb_host_obj[USBH0_INDEX].host_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}

static rt_err_t _ehci0_reset_port(rt_uint8_t port)
{
    // No reset port function available
    return RT_EOK;
}

static uint8_t _ehci0_pipe_buf[64];
static uint8_t _ehci0_pipe_idx;

static int _ehci0_pipe_xfer(upipe_t pipe, rt_uint8_t token, void *buffer, int nbytes, int timeouts)
{
    int timeout = timeouts;

    if (!imxrt_usb_host_obj[USBH0_INDEX].connect_status)
    {
        return -1;
    }
    usb_host_transfer_t *transfer;
    if (imxrt_usb_host_obj[USBH0_INDEX].pipes[pipe->pipe_index].pipe_handle == NULL)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("error operation on null pipe\n"));
        return -1;
    }
    if (USB_HostMallocTransfer(imxrt_usb_host_obj[USBH0_INDEX].host_handle, &transfer) != kStatus_USB_Success)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("error to get transfer\n"));
        return -1;
    }
    transfer->transferBuffer      = buffer;
    transfer->transferLength      = nbytes;
    transfer->transferSofar       = 0;
    transfer->callbackFn          = _imxrt_usb_host_send_callback;
    transfer->callbackParam       = &(imxrt_usb_host_obj[USBH0_INDEX].pipes[pipe->pipe_index]);
    transfer->direction         = (pipe->ep.bEndpointAddress & USB_DIR_IN) ? USB_IN : USB_OUT;
    if (pipe->ep.bmAttributes == USB_ENDPOINT_CONTROL)
    {
        if (token == USBH_PID_SETUP)
        {
            struct urequest *setup = (struct urequest *)buffer;
            transfer->setupStatus = 0;
            transfer->setupPacket->bmRequestType = setup->request_type;
            transfer->setupPacket->bRequest = setup->bRequest;
            transfer->setupPacket->wIndex = setup->wIndex;
            transfer->setupPacket->wLength = setup->wLength;
            transfer->setupPacket->wValue = setup->wValue;
            transfer->transferBuffer    = RT_NULL;
            transfer->transferLength    = 0;
            transfer->next = RT_NULL;
            if ((transfer->setupPacket->bmRequestType & USB_REQUEST_TYPE_DIR_MASK) == USB_REQUEST_TYPE_DIR_IN)
            {
                transfer->direction = USB_IN;
                transfer->transferBuffer = _ehci0_pipe_buf;
                transfer->transferLength = setup->wLength;
                _ehci0_pipe_idx = 0;
            }
            else
            {
                transfer->direction = USB_OUT;
            }
        }
        else
        {
            rt_memcpy(buffer, _ehci0_pipe_buf + _ehci0_pipe_idx, nbytes);
            imxrt_usb_host_obj[USBH0_INDEX].pipes[pipe->pipe_index].transfer_status = kStatus_USB_Success;
            transfer->transferSofar = nbytes;
            _ehci0_pipe_idx += nbytes;
            if (_ehci0_pipe_idx >= 64)
            {
                _ehci0_pipe_idx = 0;
            }
            goto _ehci0_pipe_xfer_finish;
        }

    }
    rt_completion_init(&(imxrt_usb_host_obj[USBH0_INDEX].pipes[pipe->pipe_index].urb_completion));
    if (USB_HostEhciWritePipe(((usb_host_instance_t *)imxrt_usb_host_obj[USBH0_INDEX].host_handle)->controllerHandle, imxrt_usb_host_obj[USBH0_INDEX].pipes[pipe->pipe_index].pipe_handle, transfer) != kStatus_USB_Success)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("usb host failed to send\n"));
        (void)USB_HostFreeTransfer(imxrt_usb_host_obj[USBH0_INDEX].host_handle, transfer);
        return -1;
    }
    if (-RT_ETIMEOUT == rt_completion_wait(&(imxrt_usb_host_obj[USBH0_INDEX].pipes[pipe->pipe_index].urb_completion), RT_WAITING_FOREVER))
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("usb transfer timeout\n"));
        (void)USB_HostFreeTransfer(imxrt_usb_host_obj[USBH0_INDEX].host_handle, transfer);
        return -1;
    }
    _ehci0_pipe_xfer_finish:
    switch (imxrt_usb_host_obj[USBH0_INDEX].pipes[pipe->pipe_index].transfer_status)
    {
    case kStatus_USB_Success:
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("ok\n"));
        pipe->status = UPIPE_STATUS_OK;
        if (pipe->callback != RT_NULL)
        {
            pipe->callback(pipe);
        }
        size_t size = transfer->transferSofar;
        (void)USB_HostFreeTransfer(imxrt_usb_host_obj[USBH0_INDEX].host_handle, transfer);
        if (pipe->ep.bEndpointAddress & 0x80)
        {
            return size;
        }
        else if (pipe->ep.bEndpointAddress & 0x00)
        {
            return size;
        }
        return nbytes;
        break;
    }
    case kStatus_USB_TransferStall:
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("stall\n"));
        pipe->status = UPIPE_STATUS_STALL;
        if (pipe->callback != RT_NULL)
        {
            pipe->callback(pipe);
        }
        (void)USB_HostFreeTransfer(imxrt_usb_host_obj[USBH0_INDEX].host_handle, transfer);
        return -1;
        break;
    }
    case kStatus_USB_TransferFailed:
    default:
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("error\n"));
        pipe->status = UPIPE_STATUS_ERROR;
        if (pipe->callback != RT_NULL)
        {
            pipe->callback(pipe);
        }
        (void)USB_HostFreeTransfer(imxrt_usb_host_obj[USBH0_INDEX].host_handle, transfer);
        return -1;
        break;
    }
    }
}

static rt_uint16_t _ehci0_pipe_index = 0;
static rt_uint8_t  _ehci0_get_free_pipe_index(void)
{
    rt_uint8_t idx;
    for (idx = 1; idx < 16; idx++)
    {
        if (!(_ehci0_pipe_index & (0x01 << idx)))
        {
            _ehci0_pipe_index |= (0x01 << idx);
            return idx;
        }
    }
    return 0xff;
}

static void _ehci0_free_pipe_index(rt_uint8_t index)
{
    _ehci0_pipe_index &= ~(0x01 << index);
}

static rt_err_t _ehci0_open_pipe(upipe_t pipe)
{
    pipe->pipe_index = _ehci0_get_free_pipe_index();
    if (pipe->pipe_index == 0xFF)
    {
        return -RT_ERROR;
    }
    usb_host_pipe_init_t pipe_init =
    {
        .devInstance = imxrt_usb_host_obj[USBH0_INDEX].device_handle,
        .pipeType = pipe->ep.bmAttributes,
        .direction = (pipe->ep.bEndpointAddress & USB_DIR_IN) ? USB_IN : USB_OUT,
        .endpointAddress = (pipe->ep.bEndpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_NUMBER_MASK),
        .interval = pipe->ep.bInterval,
        .maxPacketSize = (uint16_t)(pipe->ep.wMaxPacketSize & USB_DESCRIPTOR_ENDPOINT_MAXPACKETSIZE_SIZE_MASK),
        .numberPerUframe = (uint8_t)(pipe->ep.wMaxPacketSize & USB_DESCRIPTOR_ENDPOINT_MAXPACKETSIZE_MULT_TRANSACTIONS_MASK),
        .nakCount = USB_HOST_CONFIG_MAX_NAK,
    };
    USB_HostOpenPipe(imxrt_usb_host_obj[USBH0_INDEX].host_handle, &imxrt_usb_host_obj[USBH0_INDEX].pipes[pipe->pipe_index].pipe_handle, &pipe_init);
    return RT_EOK;
}

static rt_err_t _ehci0_close_pipe(upipe_t pipe)
{
    (void)USB_HostClosePipe(imxrt_usb_host_obj[USBH0_INDEX].host_handle, imxrt_usb_host_obj[USBH0_INDEX].pipes[pipe->pipe_index].pipe_handle);
    _ehci0_free_pipe_index(pipe->pipe_index);
    return RT_EOK;
}

static struct uhcd_ops _ehci0_uhcd_ops =
{
    _ehci0_reset_port,
    _ehci0_pipe_xfer,
    _ehci0_open_pipe,
    _ehci0_close_pipe,
};

static usb_status_t usb0_host_callback(usb_device_handle handle, usb_host_configuration_handle config_handle, rt_uint32_t event_code)
{
    usb_status_t status = kStatus_USB_Success;

    switch (event_code)
    {
    case kUSB_HostEventAttach:
        if (!imxrt_usb_host_obj[USBH0_INDEX].connect_status)
        {
            imxrt_usb_host_obj[USBH0_INDEX].connect_status = RT_TRUE;
            imxrt_usb_host_obj[USBH0_INDEX].device_handle = handle;
            RT_DEBUG_LOG(RT_DEBUG_USB, ("usb connected\n"));
            rt_usbh_root_hub_connect_handler(&(imxrt_usb_host_obj[USBH0_INDEX].uhcd), OTG_PORT, RT_TRUE);
        }
        break;

    case kUSB_HostEventNotSupported:
        RT_DEBUG_LOG(RT_DEBUG_USB, ("usb device not supported\n"));
        break;

    case kUSB_HostEventEnumerationDone:
        RT_DEBUG_LOG(RT_DEBUG_USB, ("enumeration done\n"));
        break;

    case kUSB_HostEventDetach:
        if (imxrt_usb_host_obj[USBH0_INDEX].connect_status)
        {
            imxrt_usb_host_obj[USBH0_INDEX].connect_status = RT_FALSE;
            imxrt_usb_host_obj[USBH0_INDEX].device_handle = handle;
            RT_DEBUG_LOG(RT_DEBUG_USB, ("usb disconnnect\n"));
            rt_usbh_root_hub_disconnect_handler(&(imxrt_usb_host_obj[USBH0_INDEX].uhcd), OTG_PORT);
            (void)USB_HostCloseDeviceInterface(handle, NULL);
        }
        break;

    default:
        break;
    }
    return status;
}

rt_thread_t usbh0_thread;

static void _ehci0_usbh_thread(void* param)
{
    while (1)
    {
        USB_HostEhciTaskFunction(imxrt_usb_host_obj[USBH0_INDEX].host_handle);
    }
}

static rt_err_t _ehci0_usbh_init(rt_device_t device)
{
    USB_HostClockInit(kUSB_ControllerEhci0);

    if (kStatus_USB_Success == USB_HostInit(kUSB_ControllerEhci0, &imxrt_usb_host_obj[USBH0_INDEX].host_handle, usb0_host_callback))
    {
        usbh0_thread = rt_thread_create("ehci0", _ehci0_usbh_thread, RT_NULL, 500, 4, 9999999);
        rt_thread_startup(usbh0_thread);
        USB_HostIsrEnable(kUSB_ControllerEhci0);
    }
    else
    {
        rt_kprintf("USB_HostInit ehci0 error\r\n");
        return -RT_ERROR;
    }
    return RT_EOK;
}
#endif

#ifdef BSP_USB1_HOST
void USB_OTG2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    USB_HostEhciIsrFunction(imxrt_usb_host_obj[USBH1_INDEX].host_handle);
    /* leave interrupt */
    rt_interrupt_leave();
}

static rt_err_t _ehci1_reset_port(rt_uint8_t port)
{
    // No reset port function available
    return RT_EOK;
}

static uint8_t _ehci1_pipe_buf[64];
static uint8_t _ehci1_pipe_idx;

static int _ehci1_pipe_xfer(upipe_t pipe, rt_uint8_t token, void *buffer, int nbytes, int timeouts)
{
    int timeout = timeouts;

    if (!imxrt_usb_host_obj[USBH1_INDEX].connect_status)
    {
        return -1;
    }
    usb_host_transfer_t *transfer;
    if (imxrt_usb_host_obj[USBH1_INDEX].pipes[pipe->pipe_index].pipe_handle == NULL)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("error operation on null pipe\n"));
        return -1;
    }
    if (USB_HostMallocTransfer(imxrt_usb_host_obj[USBH1_INDEX].host_handle, &transfer) != kStatus_USB_Success)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("error to get transfer\n"));
        return -1;
    }
    transfer->transferBuffer      = buffer;
    transfer->transferLength      = nbytes;
    transfer->transferSofar       = 0;
    transfer->callbackFn          = _imxrt_usb_host_send_callback;
    transfer->callbackParam       = &(imxrt_usb_host_obj[USBH1_INDEX].pipes[pipe->pipe_index]);
    transfer->direction         = (pipe->ep.bEndpointAddress & USB_DIR_IN) ? USB_IN : USB_OUT;
    if (pipe->ep.bmAttributes == USB_ENDPOINT_CONTROL)
    {
        if (token == USBH_PID_SETUP)
        {
            struct urequest *setup = (struct urequest *)buffer;
            transfer->setupStatus = 0;
            transfer->setupPacket->bmRequestType = setup->request_type;
            transfer->setupPacket->bRequest = setup->bRequest;
            transfer->setupPacket->wIndex = setup->wIndex;
            transfer->setupPacket->wLength = setup->wLength;
            transfer->setupPacket->wValue = setup->wValue;
            transfer->transferBuffer    = RT_NULL;
            transfer->transferLength    = 0;
            transfer->next = RT_NULL;
            if ((transfer->setupPacket->bmRequestType & USB_REQUEST_TYPE_DIR_MASK) == USB_REQUEST_TYPE_DIR_IN)
            {
                transfer->direction = USB_IN;
                transfer->transferBuffer = _ehci1_pipe_buf;
                transfer->transferLength = setup->wLength;
                _ehci1_pipe_idx = 0;
            }
            else
            {
                transfer->direction = USB_OUT;
            }
        }
        else
        {
            rt_memcpy(buffer, _ehci1_pipe_buf + _ehci1_pipe_idx, nbytes);
            imxrt_usb_host_obj[USBH1_INDEX].pipes[pipe->pipe_index].transfer_status = kStatus_USB_Success;
            transfer->transferSofar = nbytes;
            _ehci1_pipe_idx += nbytes;
            if (_ehci1_pipe_idx >= 64)
            {
                _ehci1_pipe_idx = 0;
            }
            goto _ehci1_pipe_xfer_finish;
        }

    }
    rt_completion_init(&(imxrt_usb_host_obj[USBH1_INDEX].pipes[pipe->pipe_index].urb_completion));
    if (USB_HostEhciWritePipe(((usb_host_instance_t *)imxrt_usb_host_obj[USBH1_INDEX].host_handle)->controllerHandle, imxrt_usb_host_obj[USBH1_INDEX].pipes[pipe->pipe_index].pipe_handle, transfer) != kStatus_USB_Success)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("usb host failed to send\n"));
        (void)USB_HostFreeTransfer(imxrt_usb_host_obj[USBH1_INDEX].host_handle, transfer);
        return -1;
    }
    if (-RT_ETIMEOUT == rt_completion_wait(&(imxrt_usb_host_obj[USBH1_INDEX].pipes[pipe->pipe_index].urb_completion), RT_WAITING_FOREVER))
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("usb transfer timeout\n"));
        (void)USB_HostFreeTransfer(imxrt_usb_host_obj[USBH1_INDEX].host_handle, transfer);
        return -1;
    }
    // rt_thread_mdelay(1);
    _ehci1_pipe_xfer_finish:
    switch (imxrt_usb_host_obj[USBH1_INDEX].pipes[pipe->pipe_index].transfer_status)
    {
    case kStatus_USB_Success:
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("ok\n"));
        pipe->status = UPIPE_STATUS_OK;
        if (pipe->callback != RT_NULL)
        {
            pipe->callback(pipe);
        }
        size_t size = transfer->transferSofar;
        (void)USB_HostFreeTransfer(imxrt_usb_host_obj[USBH1_INDEX].host_handle, transfer);
        if (pipe->ep.bEndpointAddress & 0x80)
        {
            return size;
        }
        else if (pipe->ep.bEndpointAddress & 0x00)
        {
            return size;
        }
        return nbytes;
        break;
    }
    case kStatus_USB_TransferStall:
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("stall\n"));
        pipe->status = UPIPE_STATUS_STALL;
        if (pipe->callback != RT_NULL)
        {
            pipe->callback(pipe);
        }
        (void)USB_HostFreeTransfer(imxrt_usb_host_obj[USBH1_INDEX].host_handle, transfer);
        return -1;
        break;
    }
    case kStatus_USB_TransferFailed:
    default:
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("error\n"));
        pipe->status = UPIPE_STATUS_ERROR;
        if (pipe->callback != RT_NULL)
        {
            pipe->callback(pipe);
        }
        (void)USB_HostFreeTransfer(imxrt_usb_host_obj[USBH1_INDEX].host_handle, transfer);
        return -1;
        break;
    }
    }
}

static rt_uint16_t _ehci1_pipe_index = 0;
static rt_uint8_t  _ehci1_get_free_pipe_index(void)
{
    rt_uint8_t idx;
    for (idx = 1; idx < 16; idx++)
    {
        if (!(_ehci1_pipe_index & (0x01 << idx)))
        {
            _ehci1_pipe_index |= (0x01 << idx);
            return idx;
        }
    }
    return 0xff;
}

static void _ehci1_free_pipe_index(rt_uint8_t index)
{
    _ehci1_pipe_index &= ~(0x01 << index);
}

static rt_err_t _ehci1_open_pipe(upipe_t pipe)
{
    pipe->pipe_index = _ehci1_get_free_pipe_index();
    if (pipe->pipe_index == 0xFF)
    {
        return -RT_ERROR;
    }
    usb_host_pipe_init_t pipe_init =
    {
        .devInstance = imxrt_usb_host_obj[USBH1_INDEX].device_handle,
        .pipeType = pipe->ep.bmAttributes,
        .direction = (pipe->ep.bEndpointAddress & USB_DIR_IN) ? USB_IN : USB_OUT,
        .endpointAddress = (pipe->ep.bEndpointAddress & USB_DESCRIPTOR_ENDPOINT_ADDRESS_NUMBER_MASK),
        .interval = pipe->ep.bInterval,
        .maxPacketSize = (uint16_t)(pipe->ep.wMaxPacketSize & USB_DESCRIPTOR_ENDPOINT_MAXPACKETSIZE_SIZE_MASK),
        .numberPerUframe = (uint8_t)(pipe->ep.wMaxPacketSize & USB_DESCRIPTOR_ENDPOINT_MAXPACKETSIZE_MULT_TRANSACTIONS_MASK),
        .nakCount = USB_HOST_CONFIG_MAX_NAK,
    };
    USB_HostOpenPipe(imxrt_usb_host_obj[USBH1_INDEX].host_handle, &imxrt_usb_host_obj[USBH1_INDEX].pipes[pipe->pipe_index].pipe_handle, &pipe_init);
    return RT_EOK;
}

static rt_err_t _ehci1_close_pipe(upipe_t pipe)
{
    (void)USB_HostClosePipe(imxrt_usb_host_obj[USBH1_INDEX].host_handle, imxrt_usb_host_obj[USBH1_INDEX].pipes[pipe->pipe_index].pipe_handle);
    _ehci1_free_pipe_index(pipe->pipe_index);
    return RT_EOK;
}

static struct uhcd_ops _ehci1_uhcd_ops =
{
    _ehci1_reset_port,
    _ehci1_pipe_xfer,
    _ehci1_open_pipe,
    _ehci1_close_pipe,
};

static usb_status_t usb1_host_callback(usb_device_handle handle, usb_host_configuration_handle config_handle, rt_uint32_t event_code)
{
    usb_status_t status = kStatus_USB_Success;

    switch (event_code)
    {
    case kUSB_HostEventAttach:
        if (!imxrt_usb_host_obj[USBH1_INDEX].connect_status)
        {
            imxrt_usb_host_obj[USBH1_INDEX].connect_status = RT_TRUE;
            imxrt_usb_host_obj[USBH1_INDEX].device_handle = handle;
            RT_DEBUG_LOG(RT_DEBUG_USB, ("usb connected\n"));
            rt_usbh_root_hub_connect_handler(&(imxrt_usb_host_obj[USBH1_INDEX].uhcd), OTG_PORT, RT_TRUE);
        }
        break;

    case kUSB_HostEventNotSupported:
        RT_DEBUG_LOG(RT_DEBUG_USB, ("usb device not supported\n"));
        break;

    case kUSB_HostEventEnumerationDone:
        RT_DEBUG_LOG(RT_DEBUG_USB, ("enumeration done\n"));
        break;

    case kUSB_HostEventDetach:
        if (imxrt_usb_host_obj[USBH1_INDEX].connect_status)
        {
            imxrt_usb_host_obj[USBH1_INDEX].connect_status = RT_FALSE;
            imxrt_usb_host_obj[USBH1_INDEX].device_handle = handle;
            RT_DEBUG_LOG(RT_DEBUG_USB, ("usb disconnnect\n"));
            rt_usbh_root_hub_disconnect_handler(&(imxrt_usb_host_obj[USBH1_INDEX].uhcd), OTG_PORT);
            (void)USB_HostCloseDeviceInterface(handle, NULL);
        }
        break;

    default:
        break;
    }
    return status;
}

rt_thread_t usbh1_thread;

static void _ehci1_usbh_thread(void* param)
{
    while (1)
    {
        USB_HostEhciTaskFunction(imxrt_usb_host_obj[USBH1_INDEX].host_handle);
    }
}

static rt_err_t _ehci1_usbh_init(rt_device_t device)
{
    USB_HostClockInit(kUSB_ControllerEhci1);

    if (kStatus_USB_Success == USB_HostInit(kUSB_ControllerEhci1, &imxrt_usb_host_obj[USBH1_INDEX].host_handle, usb1_host_callback))
    {
        usbh1_thread = rt_thread_create("ehci1", _ehci1_usbh_thread, RT_NULL, 500, 4, 9999999);
        rt_thread_startup(usbh1_thread);
        USB_HostIsrEnable(kUSB_ControllerEhci1);
    }
    else
    {
        rt_kprintf("USB_HostInit ehci1 error\r\n");
        return -RT_ERROR;
    }
    return RT_EOK;
}
#endif

int imxrt_usbh_register(void)
{
    rt_err_t res = -RT_ERROR;
    struct imxrt_usb_host *usb_host_obj;

#ifdef BSP_USB0_HOST
    usb_host_obj = &(imxrt_usb_host_obj[USBH0_INDEX]);
    rt_memset((void *)(&(usb_host_obj->uhcd)), 0, sizeof(struct uhcd));
    usb_host_obj->uhcd.parent.type = RT_Device_Class_USBHost;
    usb_host_obj->uhcd.parent.init = _ehci0_usbh_init;
    usb_host_obj->uhcd.parent.user_data = usb_host_obj;
    usb_host_obj->uhcd.ops = &_ehci0_uhcd_ops;
    usb_host_obj->uhcd.num_ports = OTG_PORT;
    res = rt_device_register(&(usb_host_obj->uhcd.parent), usb_host_obj->name, RT_DEVICE_FLAG_DEACTIVATE);
    if (res != RT_EOK)
    {
        rt_kprintf("register usb0 host failed res = %d\r\n", res);
        return -RT_ERROR;
    }

    rt_usb_host_init(usb_host_obj->name);
#endif
#ifdef BSP_USB1_HOST
    usb_host_obj = &(imxrt_usb_host_obj[USBH1_INDEX]);
    rt_memset((void *)(&(usb_host_obj->uhcd)), 0, sizeof(struct uhcd));
    usb_host_obj->uhcd.parent.type = RT_Device_Class_USBHost;
    usb_host_obj->uhcd.parent.init = _ehci1_usbh_init;
    usb_host_obj->uhcd.parent.user_data = usb_host_obj;
    usb_host_obj->uhcd.ops = &_ehci1_uhcd_ops;
    usb_host_obj->uhcd.num_ports = OTG_PORT;
    res = rt_device_register(&(usb_host_obj->uhcd.parent), usb_host_obj->name, RT_DEVICE_FLAG_DEACTIVATE);
    if (res != RT_EOK)
    {
        rt_kprintf("register usb0 host failed res = %d\r\n", res);
        return -RT_ERROR;
    }

    rt_usb_host_init(usb_host_obj->name);
#endif
    return RT_EOK;
}
INIT_DEVICE_EXPORT(imxrt_usbh_register);

#endif
