/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-09     QT-one       first version
 */

#include "drv_usbd.h"

#ifdef RT_USING_USB_DEVICE
#if !defined(BSP_USING_USBD)
    #error "Please define at least one BSP_USING_USBD"
#endif

#if defined(BSP_USING_USBD)
    #include "usb_port.h"
#endif

struct ht32_usbd
{
    char *name;
    USBDCore_TypeDef *p_usbd_code;
    IRQn_Type irq;
};

__ALIGN4 USBDCore_TypeDef p_usbd;
/* internal mount point */
static struct ht32_usbd *p_usbd_instance = RT_NULL;

/* Endpoint Function List */
static struct ep_id endpoint_pool[] =
{
    {0x00, USB_EP_ATTR_CONTROL,   USB_DIR_INOUT, 64, ID_ASSIGNED  },
    {0x01, USB_EP_ATTR_BULK,      USB_DIR_IN,    64, ID_UNASSIGNED},
    {0x02, USB_EP_ATTR_BULK,      USB_DIR_OUT,   64, ID_UNASSIGNED},
    {0x03, USB_EP_ATTR_INT,       USB_DIR_IN,    64, ID_UNASSIGNED},
    {0x04, USB_EP_ATTR_INT,       USB_DIR_OUT,   64, ID_UNASSIGNED},
    {0x05, USB_EP_ATTR_ISOC,      USB_DIR_IN,    64, ID_UNASSIGNED},
    {0x06, USB_EP_ATTR_ISOC,      USB_DIR_OUT,   64, ID_UNASSIGNED},
    {0x07, USB_EP_ATTR_TYPE_MASK, USB_DIR_MASK,  64, ID_UNASSIGNED},
};

/* usbd Peripheral List */
static struct ht32_usbd usbd_config[] =
{
#ifdef BSP_USING_USBD
    {
        .name           = BSP_USING_USBD_NAME,
        .p_usbd_code    = NULL,
        .irq            = USB_IRQn,
    },
#endif
};

/* Start of Frame (SOF) interrupt callbacks */
void usbd_sof_callback(USBDCore_TypeDef *pCore)
{
    udcd_t udcd = (udcd_t)pCore->pdata;
    rt_usbd_sof_handler(udcd);
}
/* USB reset interrupt */
void usbd_reset_callback(USBDCore_TypeDef *pCore)
{
    udcd_t udcd = (udcd_t)pCore->pdata;
    rt_usbd_reset_handler(udcd);
}

/* USB Suspend (Disconnect) Interrupt */
void usbd_suspend_callback(USBDCore_TypeDef *pCore)
{
    udcd_t udcd = (udcd_t)pCore->pdata;
    rt_usbd_disconnect_handler(udcd);
}

/* USB recovery (reconnect) interrupt */
void usbd_resume_callback(USBDCore_TypeDef *pCore)
{
    udcd_t udcd = (udcd_t)pCore->pdata;
    rt_usbd_connect_handler(udcd);
}

/* USB endpoint 0 interrupt */
void usbd_setup_callback(USBDCore_TypeDef *pCore)
{
    udcd_t udcd = (udcd_t)pCore->pdata;
    rt_usbd_ep0_setup_handler(udcd, (struct urequest *)&pCore->Device.Request);
}

/* Endpoint 0 input interrupt£¨Can be classified as other endpoint input interrupt£© */
void usbd_ep0_in_callback(USBDCore_TypeDef *pCore)
{
    udcd_t udcd = (udcd_t)pCore->pdata;
    rt_usbd_ep0_in_handler(udcd);
}

/* Endpoint 0 output interrupt£¨Can be classified as other endpoint input interrupt£© */
void usbd_ep0_out_callback(USBDCore_TypeDef *pCore)
{
    udcd_t udcd = (udcd_t)pCore->pdata;
    pCore->Device.Transfer.sByteLength = pCore->Device.Request.wLength;
    rt_usbd_ep0_out_handler(udcd, pCore->Device.Transfer.sByteLength);
}

/* Other endpoint input interrupt */
void usbd_ep_in_callback(USBDCore_TypeDef *pCore, USBD_EPTn_Enum EPTn)
{
    udcd_t udcd = (udcd_t)pCore->pdata;
    pCore->Device.Transfer.sByteLength = 0;
    rt_usbd_ep_in_handler(udcd, EPTn | 0x80, pCore->Device.Transfer.sByteLength);
}

/* Other Endpoint Output Interrupt */
void usbd_ep_out_callback(USBDCore_TypeDef *pCore, USBD_EPTn_Enum EPTn)
{
    udcd_t udcd = (udcd_t)pCore->pdata;
    rt_usbd_ep_out_handler(udcd, EPTn, pCore->ept_io->trans_len);
}

/* Setting the address */
static rt_err_t ht32_set_address(rt_uint8_t address)
{
    /* Setting the device address */
    p_usbd_instance->p_usbd_code->Info.CurrentStatus = USER_USB_STATE_ADDRESS;
    API_USB_SET_ADDR(address);
    return RT_EOK;
}
/* Configuration settings */
static rt_err_t ht32_set_config(rt_uint8_t address)
{
    return RT_EOK;
}
/* endpoint pause */
static rt_err_t ht32_ep_set_stall(rt_uint8_t address)
{
    if (0 == (address & 0x7f))
        API_USB_EPTn_SEND_STALL((USBD_EPTn_Enum)(address & 0x7f));
    else
        API_USB_EPTn_SET_HALT((USBD_EPTn_Enum)(address & 0x7f));
    return RT_EOK;
}
/* Endpoint reboot*/
static rt_err_t ht32_ep_clear_stall(rt_uint8_t address)
{
    if (0 != (address & 0x7f))
    {
        API_USB_EPTn_CLR_HALT((USBD_EPTn_Enum)(address & 0x7f));
        API_USB_EPTn_CLR_DTG((USBD_EPTn_Enum)(address & 0x7f));
    }
    return RT_EOK;
}
/* endpoint enable */
static rt_err_t ht32_ep_enable(struct uendpoint *ep)
{
    /* Functions not found in the firmware library at the moment */
    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);
    usbd_ep_enable(p_usbd_instance->p_usbd_code, ep->ep_desc->bEndpointAddress);
    return RT_EOK;
}
/* endpoint incapacity */
static rt_err_t ht32_ep_disable(struct uendpoint *ep)
{
    /* Functions not found in the firmware library at the moment */
    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);
    usbd_ep_disable(p_usbd_instance->p_usbd_code, ep->ep_desc->bEndpointAddress);
    return RT_EOK;
}
/* Endpoint Receive Data Preparation */
static rt_ssize_t ht32_ep_read_prepare(rt_uint8_t address, void *buffer, rt_size_t size)
{
    USBDCore_EPTReadOUTData((USBD_EPTn_Enum)(address & 0x7f), (uint32_t *)buffer, size);
    return size;
}
/* Endpoint reading data */
static rt_ssize_t ht32_ep_read(rt_uint8_t address, void *buffer)
{
    /* Do not read data from this function */
    rt_size_t size = 0;
    RT_ASSERT(buffer != RT_NULL);
    return size;
}
/* Endpoint Write Data */
static rt_ssize_t ht32_ep_write(rt_uint8_t address, void *buffer, rt_size_t size)
{
    /* Use this function to write data to a USB endpoint */
    return USBDCore_EPTWriteINData((USBD_EPTn_Enum)(address & 0x7f), (uint32_t *)buffer, size);
}
/* Endpoint 0 transmit status */
static rt_err_t ht32_ep0_send_status(void)
{
    uint8_t Date = 0;
    /* State of send endpoint 0 */
    API_USB_EPTn_WRITE_IN(USBD_EPT0, (u32*)&Date, 0);
    return RT_EOK;
}
/* USB pause */
static rt_err_t ht32_suspend(void)
{
    return RT_EOK;
}
/* USB awakens */
static rt_err_t ht32_wakeup(void)
{
    return RT_EOK;
}

/* USB device interface function */
const static struct udcd_ops _udc_ops =
{
    .set_address            = ht32_set_address,
    .set_config             = ht32_set_config,
    .ep_set_stall           = ht32_ep_set_stall,
    .ep_clear_stall         = ht32_ep_clear_stall,
    .ep_enable              = ht32_ep_enable,
    .ep_disable             = ht32_ep_disable,
    .ep_read_prepare        = ht32_ep_read_prepare,
    .ep_read                = ht32_ep_read,
    .ep_write               = ht32_ep_write,
    .ep0_send_status        = ht32_ep0_send_status,
    .suspend                = ht32_suspend,
    .wakeup                 = ht32_wakeup,
};

static void usbd_mainroutine(void)
{
    USBDCore_MainRoutine(p_usbd_instance->p_usbd_code);
}
/* USB Device Initialisation Functions */
static rt_err_t ht32_dcd_init(rt_device_t device)
{
    /* USB object and interface initialisation, and turning on USB interrupts */
    USB_Configuration(p_usbd_instance->p_usbd_code);
    rt_thread_idle_sethook(usbd_mainroutine);
    return RT_EOK;
}

/* USB device registration function */
int ht32_usbd_register(void)
{
    rt_size_t obj_num;
    rt_err_t result = 0;
    int index;
    USBDCore_TypeDef *p_usbd_core = &p_usbd;
    /* Calculate how many USB devices */
    obj_num = sizeof(usbd_config) / sizeof(struct ht32_usbd);

    for (index = 0; index < obj_num; index++)
    {
        /* Request a udcd object memory and clear it. */
        udcd_t udcd = (udcd_t)rt_malloc(sizeof(struct udcd));
        if (udcd == RT_NULL)
        {
            rt_kprintf("udcd malloc failed\r\n");
            return -RT_ERROR;
        }
        rt_memset((void *)udcd, 0, sizeof(struct udcd));

        /* Assigning a value to the requested udcd object */
        udcd->parent.type = RT_Device_Class_USBDevice;
        udcd->parent.init = ht32_dcd_init;
        udcd->parent.user_data = p_usbd_core;
        udcd->ops = &_udc_ops;

        p_usbd_core->pdata = udcd;
        usbd_config[index].p_usbd_code = p_usbd_core;

        /* register endpoint infomation */
        udcd->ep_pool = endpoint_pool;
        udcd->ep0.id = &endpoint_pool[0];

        result = rt_device_register((rt_device_t)udcd, usbd_config[index].name, 0);
        RT_ASSERT(result == RT_EOK);

        p_usbd_instance = &usbd_config[index];

        result = rt_usb_device_init();
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}
INIT_DEVICE_EXPORT(ht32_usbd_register);


void USB_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    /* interrupt callback function */
    usbd_irq_handler(p_usbd_instance->p_usbd_code);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* RT_USING_USB_DEVICE */
