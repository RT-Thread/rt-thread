/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-11-07     RealThread   the first version
 */

#include "drv_otghs_dev.h"
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_usb_hw.h"

#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#if defined(BSP_USING_USB) && defined(RT_USING_USB_DEVICE)

usb_core_driver gd_usb_device_core;
#define gd_usb_core gd_usb_device_core

static struct udcd _gd_udc;

volatile rt_uint32_t gd_usb_irq_count;
volatile rt_uint32_t gd_usb_reset_count;
volatile rt_uint32_t gd_usb_enum_count;
volatile rt_uint32_t gd_usb_setup_count;
volatile rt_uint32_t gd_usb_ep0_in_count;
volatile rt_uint32_t gd_usb_ep0_out_count;
volatile rt_uint32_t gd_usb_rxfifo_count;
volatile rt_uint32_t gd_usb_setup_rx_count;
volatile rt_uint32_t gd_usb_last_rx_status;

#if defined(BSP_USB_DEVICE_USING_FS)
static struct ep_id _ep_pool[] = {
    { 0x0, USB_EP_ATTR_CONTROL, USB_DIR_INOUT, 64, ID_ASSIGNED },
    { 0x1, USB_EP_ATTR_BULK, USB_DIR_IN, 64, ID_UNASSIGNED },
    { 0x1, USB_EP_ATTR_BULK, USB_DIR_OUT, 64, ID_UNASSIGNED },
    { 0x2, USB_EP_ATTR_INT, USB_DIR_IN, 64, ID_UNASSIGNED },
    { 0x2, USB_EP_ATTR_INT, USB_DIR_OUT, 64, ID_UNASSIGNED },
    { 0x3, USB_EP_ATTR_BULK, USB_DIR_IN, 64, ID_UNASSIGNED },
    { 0x3, USB_EP_ATTR_BULK, USB_DIR_OUT, 64, ID_UNASSIGNED },
    { 0xFF, USB_EP_ATTR_TYPE_MASK, USB_DIR_MASK, 0, ID_ASSIGNED },
};
#elif defined(BSP_USB_DEVICE_USING_HS)
static struct ep_id _ep_pool[] = {
    { 0x0, USB_EP_ATTR_CONTROL, USB_DIR_INOUT, 64, ID_ASSIGNED },
    { 0x1, USB_EP_ATTR_BULK, USB_DIR_IN, 64, ID_UNASSIGNED },
    { 0x1, USB_EP_ATTR_BULK, USB_DIR_OUT, 512, ID_UNASSIGNED },
    { 0x2, USB_EP_ATTR_INT, USB_DIR_IN, 512, ID_UNASSIGNED },
    { 0x2, USB_EP_ATTR_INT, USB_DIR_OUT, 512, ID_UNASSIGNED },
    { 0x3, USB_EP_ATTR_BULK, USB_DIR_IN, 512, ID_UNASSIGNED },
    { 0x3, USB_EP_ATTR_BULK, USB_DIR_OUT, 512, ID_UNASSIGNED },
    { 0xFF, USB_EP_ATTR_TYPE_MASK, USB_DIR_MASK, 0, ID_ASSIGNED },
};
#endif

void usbd_reset_callback(void)
{
    gd_usb_reset_count++;
    rt_usbd_reset_handler(&_gd_udc);
}

void usbd_setup_stage_callback(struct urequest *setup_packet)
{
    gd_usb_setup_count++;
    rt_usbd_ep0_setup_handler(&_gd_udc, setup_packet);
}

void usbd_data_in_stage_callback(uint8_t epnum, uint16_t data_count)
{
    if (epnum == 0)
    {
        gd_usb_ep0_in_count++;
        rt_usbd_ep0_in_handler(&_gd_udc);
    }
    else
    {
        rt_usbd_ep_in_handler(&_gd_udc, 0x80 | epnum, data_count);
    }
}

void usbd_connect_callback(void)
{
    rt_usbd_connect_handler(&_gd_udc);
}

void usbd_sof_callback(void)
{
    rt_usbd_sof_handler(&_gd_udc);
}

void usbd_disconnect_callback(void)
{
    rt_usbd_disconnect_handler(&_gd_udc);
}

void usbd_data_out_stage_callback(uint8_t epnum, uint16_t data_count)
{
    if (epnum == 0)
    {
        gd_usb_ep0_out_count++;
        rt_usbd_ep0_out_handler(&_gd_udc, data_count);
    }
    else
    {
        rt_usbd_ep_out_handler(&_gd_udc, epnum, data_count);
    }
}

void usbd_set_connection_state(uint8_t state)
{
    if (state == 1)
    {
        usb_dev_connect(&gd_usb_core);

        usb_mdelay(3);
    }
    else
    {
        usb_dev_disconnect(&gd_usb_core);

        usb_mdelay(3);
    }
}

static rt_err_t _ep_set_stall(rt_uint8_t address)
{
    usb_ep_stall(&gd_usb_core, address);

    return RT_EOK;
}

static rt_err_t _ep_clear_stall(rt_uint8_t address)
{
    usb_ep_clrstall(&gd_usb_core, address);

    return RT_EOK;
}

static rt_err_t _set_address(rt_uint8_t address)
{
    usb_devaddr_set(&gd_usb_core, address);

    return RT_EOK;
}

static rt_err_t _set_config(rt_uint8_t address)
{
    return RT_EOK;
}

static rt_err_t _ep_enable(uep_t ep)
{
    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);

    usb_ep_active(&gd_usb_core,
                  ep->ep_desc->bEndpointAddress,
                  ep->ep_desc->wMaxPacketSize,
                  ep->ep_desc->bmAttributes);

    return RT_EOK;
}

static rt_err_t _ep_disable(uep_t ep)
{
    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);

    usb_ep_deactivate(&gd_usb_core, ep->ep_desc->bEndpointAddress);

    return RT_EOK;
}

static rt_ssize_t _ep_read(rt_uint8_t address, void *buffer)
{
    rt_size_t size = 0;
    RT_ASSERT(buffer != RT_NULL);

    return size;
}

static rt_ssize_t _ep_read_prepare(rt_uint8_t address, void *buffer, rt_size_t size)
{
    usb_ep_outxfer(&gd_usb_core, address, buffer, size);

    return size;
}

static rt_ssize_t _ep_write(rt_uint8_t address, void *buffer, rt_size_t size)
{
    usb_ep_inxfer(&gd_usb_core, address, buffer, size);

    return size;
}

static rt_err_t _ep0_send_status(void)
{
    usb_ep_inxfer(&gd_usb_core, 0, NULL, 0);

    usb_ctlep_startout(&gd_usb_core);

    return RT_EOK;
}

static rt_err_t _suspend(void)
{
    return RT_EOK;
}

static rt_err_t _wakeup(void)
{
    return RT_EOK;
}

static rt_err_t _init(rt_device_t device)
{
    usb_rcu_config(USBHS0);

#if defined(BSP_USB_DEVICE_USING_HS)
    usb_para_init(&gd_usb_core, USBHS0, USB_SPEED_HIGH, DEVICE_MODE);
#else
    usb_para_init(&gd_usb_core, USBHS0, USB_SPEED_FULL, DEVICE_MODE);
#endif

    /* configure USB capabilites */
    usb_basic_init(&gd_usb_core.bp, &gd_usb_core.regs);

    usb_globalint_disable(&gd_usb_core.regs);

    /* initailizes the USB core*/
    usb_core_init(gd_usb_core.bp, &gd_usb_core.regs);

    /* set device disconnect */
    usbd_set_connection_state(0);

    usb_curmode_set(&gd_usb_core.regs, DEVICE_MODE);

    /* initailizes device mode */
    usb_devcore_init(&gd_usb_core);

#if defined(BSP_USB_DEVICE_USING_HS)
    pllusb_rcu_config(USBHS0);
#endif

    usb_intr_config(USBHS0);

    usb_globalint_enable(&gd_usb_core.regs);

    /* connect only after the PHY clock and interrupt are ready */
    usbd_set_connection_state(1);

    return RT_EOK;
}

const static struct udcd_ops _udc_ops = {
    _set_address,
    _set_config,
    _ep_set_stall,
    _ep_clear_stall,
    _ep_enable,
    _ep_disable,
    _ep_read_prepare,
    _ep_read,
    _ep_write,
    _ep0_send_status,
    _suspend,
    _wakeup,
};

int gd_usbd_register(void)
{
    rt_memset((void *)&_gd_udc, 0, sizeof(struct udcd));
    _gd_udc.parent.type = RT_Device_Class_USBDevice;
    _gd_udc.parent.init = _init;
    _gd_udc.parent.user_data = NULL;
    _gd_udc.ops = &_udc_ops;
    /* Register endpoint infomation */
    _gd_udc.ep_pool = _ep_pool;
    _gd_udc.ep0.id = &_ep_pool[0];

    rt_device_register((rt_device_t)&_gd_udc, "usbd", 0);
    rt_usb_device_init();
    return RT_EOK;
}
INIT_DEVICE_EXPORT(gd_usbd_register);

#ifdef RT_USING_FINSH
static void usbstat(void)
{
    rt_kprintf("usb irq=%u reset=%u enum=%u setup=%u ep0in=%u ep0out=%u\n",
               gd_usb_irq_count, gd_usb_reset_count, gd_usb_enum_count,
               gd_usb_setup_count, gd_usb_ep0_in_count, gd_usb_ep0_out_count);
    rt_kprintf("rx fifo=%u setup=%u last=%08x\n",
               gd_usb_rxfifo_count, gd_usb_setup_rx_count, gd_usb_last_rx_status);
    rt_kprintf("core GAHBCS=%08x GUSBCS=%08x GINTF=%08x GINTEN=%08x\n",
               gd_usb_core.regs.gr->GAHBCS, gd_usb_core.regs.gr->GUSBCS,
               gd_usb_core.regs.gr->GINTF, gd_usb_core.regs.gr->GINTEN);
    rt_kprintf("fifo GRSTCTL=%08x GRFLEN=%08x TX0=%08x GCCFG=%08x GOTGCS=%08x\n",
               gd_usb_core.regs.gr->GRSTCTL, gd_usb_core.regs.gr->GRFLEN,
               gd_usb_core.regs.gr->DIEP0TFLEN_HNPTFLEN,
               gd_usb_core.regs.gr->GCCFG, gd_usb_core.regs.gr->GOTGCS);
    rt_kprintf("dev  DCFG=%08x DCTL=%08x DSTAT=%08x DAEPINT=%08x DAEPINTEN=%08x\n",
               gd_usb_core.regs.dr->DCFG, gd_usb_core.regs.dr->DCTL,
               gd_usb_core.regs.dr->DSTAT, gd_usb_core.regs.dr->DAEPINT,
               gd_usb_core.regs.dr->DAEPINTEN);
    rt_kprintf("ep0o CTL=%08x LEN=%08x INTF=%08x\n",
               gd_usb_core.regs.er_out[0]->DOEPCTL,
               gd_usb_core.regs.er_out[0]->DOEPLEN,
               gd_usb_core.regs.er_out[0]->DOEPINTF);
    rt_kprintf("ep0i CTL=%08x LEN=%08x INTF=%08x\n",
               gd_usb_core.regs.er_in[0]->DIEPCTL,
               gd_usb_core.regs.er_in[0]->DIEPLEN,
               gd_usb_core.regs.er_in[0]->DIEPINTF);
    rt_kprintf("nvic enable=%u pending=%u active=%u pll=%08x\n",
               NVIC_GetEnableIRQ(USBHS0_IRQn), NVIC_GetPendingIRQ(USBHS0_IRQn),
               NVIC_GetActive(USBHS0_IRQn), RCU_ADDCTL1);
}
MSH_CMD_EXPORT(usbstat, show USB device enumeration status);
#endif

#ifdef RT_USB_DEVICE_HID

void usbd_hid_send(uint8_t *buffer, uint16_t size)
{
    struct hid_s
    {
        struct rt_device parent;
        struct ufunction *func;
        uep_t ep_in;
        uep_t ep_out;
        int status;
        rt_uint16_t protocol;
        rt_uint8_t report_buf[64];
        struct rt_messagequeue hid_mq;
    };

    udevice_t device = RT_NULL;
    uintf_t intf;
    ufunction_t func;

    struct hid_s *hiddev;

    device = rt_usbd_find_device(&_gd_udc);

    intf = rt_usbd_find_interface(device, 0, &func);

    if (RT_NULL != intf)
    {
        hiddev = (struct hid_s *)func->user_data;

        hiddev->parent.write(&hiddev->parent, 0, buffer, size);
    }
}

#endif

#endif /* BSP_USING_USB && RT_USING_USB_DEVICE */
