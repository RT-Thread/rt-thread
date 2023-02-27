/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-28     leo          first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"

#if defined(BSP_USING_DEVICE_USBFS1) || defined(BSP_USING_DEVICE_USBFS2)
#include "usbd_int.h"
#include "drv_usbfs.h"
#include "drv_config.h"

static struct at32_usbfs *p_usbfs_instance = RT_NULL;
static struct ep_id endpoint_pool[] =
{
    {0x0,  USB_EP_ATTR_CONTROL,   USB_DIR_INOUT, 64, ID_ASSIGNED  },
    {0x1,  USB_EP_ATTR_BULK,      USB_DIR_IN,    64, ID_UNASSIGNED},
    {0x1,  USB_EP_ATTR_BULK,      USB_DIR_OUT,   64, ID_UNASSIGNED},
    {0x2,  USB_EP_ATTR_INT,       USB_DIR_IN,    64, ID_UNASSIGNED},
    {0x2,  USB_EP_ATTR_INT,       USB_DIR_OUT,   64, ID_UNASSIGNED},
    {0x3,  USB_EP_ATTR_ISOC,      USB_DIR_IN,    64, ID_UNASSIGNED},
    {0x3,  USB_EP_ATTR_ISOC,      USB_DIR_OUT,   64, ID_UNASSIGNED},
    {0xFF, USB_EP_ATTR_TYPE_MASK, USB_DIR_MASK,  0,  ID_ASSIGNED  },
};

enum
{
#ifdef BSP_USING_DEVICE_USBFS1
    USBFS1_INDEX,
#endif
#ifdef BSP_USING_DEVICE_USBFS2
    USBFS2_INDEX,
#endif
};

static struct at32_usbfs usbfsd_config[] = {
#ifdef BSP_USING_DEVICE_USBFS1
    USBFS1_CONFIG,
#endif
#ifdef BSP_USING_DEVICE_USBFS2
    USBFS2_CONFIG,
#endif
};

#ifdef BSP_USING_DEVICE_USBFS1
void OTGFS1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usbd_irq_handler(p_usbfs_instance->p_otg_core);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_DEVICE_USBFS2
void OTGFS2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usbd_irq_handler(p_usbfs_instance->p_otg_core);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

void usbd_reset_callback(usbd_core_type *udev)
{
    udcd_t udcd = (udcd_t)udev->pdata;
    rt_usbd_reset_handler(udcd);
}

void usbd_connectCallback(usbd_core_type *udev)
{
    udcd_t udcd = (udcd_t)udev->pdata;
    rt_usbd_connect_handler(udcd);
}

void usbd_disconnectCallback(usbd_core_type *udev)
{
    udcd_t udcd = (udcd_t)udev->pdata;
    rt_usbd_disconnect_handler(udcd);
}

void usbd_setup_phase_done_callback(usbd_core_type *udev)
{
    udcd_t udcd = (udcd_t)udev->pdata;
    rt_usbd_ep0_setup_handler(udcd, (struct urequest*)udev->setup_buffer);
}

void usbd_data_in_stage_callback(usbd_core_type *udev, uint32_t ept_num)
{
    udcd_t udcd = (udcd_t)udev->pdata;

    if (ept_num == 0)
    {
        rt_usbd_ep0_in_handler(udcd);
    }
    else
    {
        rt_usbd_ep_in_handler(udcd, 0x80 | ept_num, udev->ept_in[ept_num].trans_len);
    }
}

void usbd_sof_callback(usbd_core_type *udev)
{
    udcd_t udcd = (udcd_t)udev->pdata;
    rt_usbd_sof_handler(udcd);
}

void usbd_data_out_stage_callback(usbd_core_type *udev, uint32_t ept_num)
{
    udcd_t udcd = (udcd_t)udev->pdata;

    if (ept_num != 0)
    {
        rt_usbd_ep_out_handler(udcd, ept_num, udev->ept_out[ept_num].trans_len);
    }
    else
    {
        rt_usbd_ep0_out_handler(udcd, udev->ept_out[0].trans_len);
    }
}

static rt_err_t _ep_set_stall(rt_uint8_t address)
{
    usbd_set_stall(&p_usbfs_instance->p_otg_core->dev, address);
    return RT_EOK;
}

static rt_err_t _ep_clear_stall(rt_uint8_t address)
{
    usbd_clear_stall(&p_usbfs_instance->p_otg_core->dev, address);
    return RT_EOK;
}

static rt_err_t _set_address(rt_uint8_t address)
{
    usbd_set_device_addr(&p_usbfs_instance->p_otg_core->dev, address);
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

    usbd_ept_open(&p_usbfs_instance->p_otg_core->dev, ep->ep_desc->bEndpointAddress, \
                  ep->ep_desc->bmAttributes, ep->ep_desc->wMaxPacketSize);
    return RT_EOK;
}

static rt_err_t _ep_disable(uep_t ep)
{
    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);

    usbd_ept_close(&p_usbfs_instance->p_otg_core->dev, ep->ep_desc->bEndpointAddress);
    return RT_EOK;
}

static rt_size_t _ep_read(rt_uint8_t address, void *buffer)
{
    rt_size_t size = 0;
    RT_ASSERT(buffer != RT_NULL);
    return size;
}

static rt_size_t _ep_read_prepare(rt_uint8_t address, void *buffer, rt_size_t size)
{
    usbd_ept_recv(&p_usbfs_instance->p_otg_core->dev, address, buffer, size);
    return size;
}

static rt_size_t _ep_write(rt_uint8_t address, void *buffer, rt_size_t size)
{
    usbd_ept_send(&p_usbfs_instance->p_otg_core->dev, address, buffer, size);
    return size;
}

static rt_err_t _ep0_send_status(void)
{
    usbd_ept_send(&p_usbfs_instance->p_otg_core->dev, 0x00, RT_NULL, 0);
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

static rt_err_t at32_dcd_init(rt_device_t device)
{
    /* usb gpio config */
    at32_msp_usb_init(device);

    /* enable otgfs irq */
    nvic_irq_enable(p_usbfs_instance->irqn, 2, 0);

    /* init usb */
    p_usbfs_instance->p_otg_core->usb_reg = usb_global_select_core(p_usbfs_instance->id);

    /* usb device core config */
    usb_core_config(p_usbfs_instance->p_otg_core, USB_FULL_SPEED_CORE_ID);

    if(p_usbfs_instance->p_otg_core->cfg.sof_out)
    {
      p_usbfs_instance->p_otg_core->usb_reg->gccfg_bit.sofouten = TRUE;
    }

    if(p_usbfs_instance->p_otg_core->cfg.vbusig)
    {
      p_usbfs_instance->p_otg_core->usb_reg->gccfg_bit.vbusig = TRUE;
    }

    /* usb device core init */
    usbd_core_init(&(p_usbfs_instance->p_otg_core->dev), p_usbfs_instance->p_otg_core->usb_reg,
                   USB_FULL_SPEED_CORE_ID);

    return RT_EOK;
}

const static struct udcd_ops _udc_ops =
{
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

int at32_usbd_register(void)
{
    rt_size_t obj_num;
    rt_err_t result = 0;
    int index;

    obj_num = sizeof(usbfsd_config) / sizeof(struct at32_usbfs);

    for (index = 0; index < obj_num; index++) {
        udcd_t udcd = (udcd_t)rt_malloc(sizeof(struct udcd));
        if (udcd == RT_NULL)
        {
            rt_kprintf("uhcd malloc failed\r\n");
            return -RT_ERROR;
        }
        rt_memset((void *)udcd, 0, sizeof(struct udcd));

        otg_core_type *p_otg_core = (otg_core_type *)rt_malloc(sizeof(otg_core_type));
        if (p_otg_core == RT_NULL)
        {
            rt_kprintf("otg_core malloc failed\r\n");
            return -RT_ERROR;
        }
        rt_memset((void *)p_otg_core, 0, sizeof(otg_core_type));

        udcd->parent.type = RT_Device_Class_USBDevice;
        udcd->parent.init = at32_dcd_init;

        udcd->parent.user_data = &(p_otg_core->dev);
        udcd->ops = &_udc_ops;
        p_otg_core->dev.pdata = udcd;
        usbfsd_config[index].p_otg_core = p_otg_core;

        /* register endpoint infomation */
        udcd->ep_pool = endpoint_pool;
        udcd->ep0.id = &endpoint_pool[0];

        result = rt_device_register((rt_device_t)udcd, usbfsd_config[index].name, 0);
        RT_ASSERT(result == RT_EOK);

        p_usbfs_instance = &usbfsd_config[index];

        result = rt_usb_device_init();
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

INIT_DEVICE_EXPORT(at32_usbd_register);

#endif
