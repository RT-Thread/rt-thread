/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-08-22     Emuzit            first version
 */
#include <rthw.h>
#include <rtdebug.h>
#include <drivers/usb_common.h>
#include <drivers/usb_device.h>
#include "ch56x_usbhs.h"
#include "ch56x_sys.h"
#include "isr_sp.h"

/*--------------------------------------------------------*/
/* Warning : Not fully tested, use at your own discretion */
/*--------------------------------------------------------*/

#ifdef SOC_SERIES_CH569
#define _attr_uepdma        __attribute__((section(".dmadata"), aligned(16)))
#define _ep0_setup_dmabuf   _dmadata_start
#else
#define _attr_uepdma        __attribute__((aligned(4)))
#define _ep0_setup_dmabuf   _dmadata_start
#define usbhs_irq_handler   usb1_irq_handler
#define USBHS_IRQn          USB1_IRQn
#define USBHS_REG_BASE      USB1_REG_BASE
#define RAMX_BASE_ADDRESS   RAMS_BASE_ADDRESS
#define UEP0_RT_DMA         UEP_DMA[0]
#endif

#define UEP_MPS_64          64
#define UEP_MPS_512         512

#define _get_ep_idx(address)    ((address) & USB_EPNO_MASK)
#define _get_ep_dir(address)    ((address) & USB_DIR_MASK)

#define uep_dir_is_in(address)  (_get_ep_dir(address) == USB_DIR_IN)
#define uep_dir_is_out(address) (_get_ep_dir(address) == USB_DIR_OUT)

extern uint32_t _dmadata_start[];

static uint32_t ep0_dmabuf[UEP_MPS_64 / 4] _attr_uepdma;
static uint32_t epx_dmabuf[UEP_ADDRESS_MAX][UEP_MPS_512 / 4] _attr_uepdma;

static struct ep_id usbhs_ep_pool[] =
{
    {0x0,  USB_EP_ATTR_CONTROL,   USB_DIR_INOUT, 64,  ID_ASSIGNED},
    {0x1,  USB_EP_ATTR_BULK,      USB_DIR_IN,    512, ID_UNASSIGNED},
    {0x1,  USB_EP_ATTR_BULK,      USB_DIR_OUT,   512, ID_UNASSIGNED},
    {0x2,  USB_EP_ATTR_INT,       USB_DIR_IN,    512, ID_UNASSIGNED},
    {0x2,  USB_EP_ATTR_INT,       USB_DIR_OUT,   512, ID_UNASSIGNED},
    {0x3,  USB_EP_ATTR_BULK,      USB_DIR_IN,    512, ID_UNASSIGNED},
    {0x3,  USB_EP_ATTR_BULK,      USB_DIR_OUT,   512, ID_UNASSIGNED},
#ifdef SOC_SERIES_CH569
    /* FIXME: not sure how to deal with EP4, no UEP4_DMA register */
    {0x4,  USB_EP_ATTR_INT,       USB_DIR_IN,    512, ID_UNASSIGNED},
    {0x4,  USB_EP_ATTR_INT,       USB_DIR_OUT,   512, ID_UNASSIGNED},
    {0x5,  USB_EP_ATTR_BULK,      USB_DIR_IN,    512, ID_UNASSIGNED},
    {0x5,  USB_EP_ATTR_BULK,      USB_DIR_OUT,   512, ID_UNASSIGNED},
    {0x6,  USB_EP_ATTR_INT,       USB_DIR_IN,    512, ID_UNASSIGNED},
    {0x6,  USB_EP_ATTR_INT,       USB_DIR_OUT,   512, ID_UNASSIGNED},
    {0x7,  USB_EP_ATTR_BULK,      USB_DIR_IN,    512, ID_UNASSIGNED},
    {0x7,  USB_EP_ATTR_BULK,      USB_DIR_OUT,   512, ID_UNASSIGNED},
#endif
    {0xff, USB_EP_ATTR_TYPE_MASK, USB_DIR_MASK,  0,   ID_ASSIGNED},
};

static struct udcd udc_device;

static uint8_t setup_set_address;

static rt_err_t udc_set_address(uint8_t address)
{
    /* DEV_AD should be updated after status stage IN token of SET_ADDRESS
     * such that that IN token could still reach our device.
    */
    setup_set_address = address | 0x80;
    return RT_EOK;
}

static rt_err_t udc_set_config(uint8_t address)
{
    return RT_EOK;
}

static rt_err_t udc_ep_set_stall(uint8_t address)
{
    volatile struct usbhs_registers *usbhs = (void *)USBHS_REG_BASE;

    uint8_t ep_idx = _get_ep_idx(address);

    if (uep_dir_is_in(address))
        usbhs->UEP_CTRL[ep_idx].TX_CTRL.res_mask = UEP_RES_STALL;
    else
        usbhs->UEP_CTRL[ep_idx].RX_CTRL.res_mask = UEP_RES_STALL;

    return RT_EOK;
}

static rt_err_t udc_ep_clear_stall(uint8_t address)
{
    volatile struct usbhs_registers *usbhs = (void *)USBHS_REG_BASE;

    uint8_t ep_idx = _get_ep_idx(address);

    if (uep_dir_is_in(address))
        usbhs->UEP_CTRL[ep_idx].TX_CTRL.res_mask = UEP_RES_NAK;
    else
        usbhs->UEP_CTRL[ep_idx].RX_CTRL.res_mask = UEP_RES_NAK;

    return RT_EOK;
}

static rt_err_t udc_ep_enable(struct uendpoint *ep)
{
    volatile struct usbhs_registers *usbhs = (void *)USBHS_REG_BASE;

    uint8_t ep_idx, address, mod;

    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);

    address = EP_ADDRESS(ep);
    ep_idx = _get_ep_idx(address);

    if (ep_idx > 0 && ep_idx <= UEP_ADDRESS_MAX)
    {
        mod = uep_dir_is_in(address) ? RB_UEP_TX_EN : RB_UEP_RX_EN;
        mod = _uep_mod_get(usbhs, ep_idx) | mod;
        _uep_mod_set(usbhs, ep_idx, mod);
    }

    return RT_EOK;
}

static rt_err_t udc_ep_disable(struct uendpoint *ep)
{
    volatile struct usbhs_registers *usbhs = (void *)USBHS_REG_BASE;

    uint8_t ep_idx, address, mod;

    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);

    address = EP_ADDRESS(ep);
    ep_idx = _get_ep_idx(address);

    if (ep_idx > 0 && ep_idx <= UEP_ADDRESS_MAX)
    {
        mod = uep_dir_is_in(address) ? RB_UEP_TX_EN : RB_UEP_RX_EN;
        mod = _uep_mod_get(usbhs, ep_idx) & ~mod;
        _uep_mod_set(usbhs, ep_idx, mod);
    }

    return RT_EOK;
}

static rt_ssize_t udc_ep_read_prepare(uint8_t address, void *buffer, rt_size_t size)
{
    volatile struct usbhs_registers *usbhs = (void *)USBHS_REG_BASE;

    uint8_t ep_idx = _get_ep_idx(address);

    uint32_t dmabuf = (uint32_t)buffer;

    if (uep_dir_is_in(address))
        return 0;

    if (size > (ep_idx ? UEP_MPS_512 : UEP_MPS_64))
        size = (ep_idx ? UEP_MPS_512 : UEP_MPS_64);

    /* need extra `buffer` copy if H/W requirement not met
     *   CH565/CH569 : DMA buffer resides in RAMX, 16-byte aligned
     *   CH567/CH568 : 4-byte aligned
     */
#ifdef SOC_SERIES_CH569
    if (size > 0 && (dmabuf < RAMX_BASE_ADDRESS || (dmabuf & 0xf)))
    {
        dmabuf = (uint32_t)(ep_idx ? epx_dmabuf[ep_idx] : ep0_dmabuf);
    }
    /* Note : usbhs->UEP_RX_DMA[0] maps to usbhs->UEP0_RT_DMA actually */
    usbhs->UEP_RX_DMA[ep_idx] = dmabuf & UEP_RT_DMA_MASK;
#else
    if (size > 0 && (dmabuf & 3))
    {
        dmabuf = (uint32_t)(ep_idx ? epx_dmabuf[ep_idx] : ep0_dmabuf);
    }
    usbhs->UEP_DMA[ep_idx] = dmabuf & UEP_RT_DMA_MASK;
#endif

    if (ep_idx == 0 && size == 0)
    {
        /* SETUP status stage, expect DATA1 */
        usbhs->UEP_CTRL[0].RX_CTRL.reg = RB_UEP_RES_ACK | RB_UEP_TOG_DATA1;
    }
    else
    {
        /* keep TOG_MASK & AUTOTOG */
        usbhs->UEP_CTRL[ep_idx].RX_CTRL.res_mask = UEP_RES_ACK;
    }

    return size;
}

static rt_ssize_t udc_ep_read(uint8_t address, void *buffer)
{
    volatile struct usbhs_registers *usbhs = (void *)USBHS_REG_BASE;

    uint8_t ep_idx = _get_ep_idx(address);

    uint32_t dmabuf;
    rt_size_t size;

    if (uep_dir_is_in(address))
        return 0;

#ifdef SOC_SERIES_CH569
    /* Note : usbhs->UEP_RX_DMA[0] maps to usbhs->UEP0_RT_DMA actually */
    dmabuf = usbhs->UEP_RX_DMA[ep_idx] & UEP_RT_DMA_MASK;
#else
    dmabuf = usbhs->UEP_DMA[ep_idx] & UEP_RT_DMA_MASK;
#endif
    size = usbhs->RX_LEN;

    /* copy if proxy buffer */
    if (size > 0 && ((uint32_t)buffer & UEP_RT_DMA_MASK) != dmabuf)
    {
        dmabuf |= RAMX_BASE_ADDRESS;
        rt_memcpy(buffer, (void *)dmabuf, size);
    }

    return size;
}

static rt_ssize_t udc_ep_write(uint8_t address, void *buffer, rt_size_t size)
{
    volatile struct usbhs_registers *usbhs = (void *)USBHS_REG_BASE;

    uint8_t ep_idx = _get_ep_idx(address);

    uint32_t dmabuf = (uint32_t)buffer;

    union _uh_rt_ctrl ctrl;

    if (uep_dir_is_out(address))
        return 0;

    if (size > (ep_idx ? UEP_MPS_512 : UEP_MPS_64))
        size = (ep_idx ? UEP_MPS_512 : UEP_MPS_64);

    /* need extra `buffer` copy if H/W requirement not met
     *   CH565/CH569 : DMA buffer resides in RAMX, 16-byte aligned
     *   CH567/CH568 : 4-byte aligned
     */
#ifdef SOC_SERIES_CH569
    if (size > 0 && (dmabuf < RAMX_BASE_ADDRESS || (dmabuf & 0xf)))
    {
        dmabuf = (uint32_t)(ep_idx ? epx_dmabuf[ep_idx] : ep0_dmabuf);
        rt_memcpy((void *)dmabuf, buffer, size);
    }
    if (ep_idx == 0)
        usbhs->UEP0_RT_DMA = dmabuf & UEP_RT_DMA_MASK;
    else
        usbhs->UEP_TX_DMA[ep_idx] = dmabuf & UEP_RT_DMA_MASK;
#else
    if (size > 0 && (dmabuf & 3))
    {
        dmabuf = (uint32_t)(ep_idx ? epx_dmabuf[ep_idx] : ep0_dmabuf);
        rt_memcpy((void *)dmabuf, buffer, size);
    }
    usbhs->UEP_DMA[ep_idx] = dmabuf & UEP_RT_DMA_MASK;
#endif
    usbhs->UEP_CTRL[ep_idx].t_len = size;

    /* keep TOG_MASK & AUTOTOG */
    usbhs->UEP_CTRL[ep_idx].TX_CTRL.res_mask = UEP_RES_ACK;

    return size;
}

static rt_err_t udc_ep0_send_status(void)
{
    volatile struct usbhs_registers *usbhs = (void *)USBHS_REG_BASE;

    /* SETUP status stage : zero data length, always DATA1 */
    usbhs->UEP_CTRL[0].t_len = 0;
    /* This is the only case UEP0_RT_DMA is set to 0. */
    usbhs->UEP0_RT_DMA = 0;
    usbhs->UEP_CTRL[0].TX_CTRL.reg = RB_UEP_RES_ACK | RB_UEP_TOG_DATA1;
    return RT_EOK;
}

static rt_err_t udc_suspend(void)
{
    return RT_EOK;
}

static rt_err_t udc_wakeup(void)
{
    return RT_EOK;
}

static const struct udcd_ops udcd_ops =
{
    .set_address = udc_set_address,
    .set_config = udc_set_config,
    .ep_set_stall = udc_ep_set_stall,
    .ep_clear_stall = udc_ep_clear_stall,
    .ep_enable = udc_ep_enable,
    .ep_disable = udc_ep_disable,
    .ep_read_prepare = udc_ep_read_prepare,
    .ep_read = udc_ep_read,
    .ep_write = udc_ep_write,
    .ep0_send_status = udc_ep0_send_status,
    .suspend = udc_suspend,
    .wakeup = udc_wakeup,
};

static void _hsbhs_device_mode_init(volatile struct usbhs_registers *usbhs)
{
    uint8_t ep_idx;

    /* disable all endpoints, use single buffer mode (BUF_MOD : 0) */
    usbhs->UHOST_CTRL.reg = 0;
    usbhs->SUSPEND.reg = 0;
    usbhs->R32_UEP_MOD = 0;
    usbhs->DEV_AD = 0;

    usbhs->CTRL.reg = RB_USB_RESET_SIE | RB_USB_CLR_ALL;
    usbhs->CTRL.reg = RB_USB_DEVICE_MODE |
                      RB_SPTP_HIGH_SPEED |
                      RB_DEV_PU_EN |
                      RB_USB_INT_BUSY |
                      RB_USB_DMA_EN;

    usbhs->INT_EN.reg = RB_USB_IE_BUSRST |
                        RB_USB_IE_TRANS |
                        RB_USB_IE_FIFOOV |
                        RB_USB_IE_SETUPACT;

    usbhs->UEP_MAX_LEN[0].reg = UEP_MPS_64;
    /*
     * It seems EP0 SETUP uses the first 8 bytes of RAMX as dmabuf and
     * handles DATA0 transfer & ACK on its own. Here we still needs to
     * RES_NAK TX/RX to block SETUP data stage till dma data is ready.
     */
    usbhs->UEP_CTRL[0].TX_CTRL.reg = RB_UEP_RES_NAK | RB_UEP_TOG_DATA1;
    usbhs->UEP_CTRL[0].RX_CTRL.reg = RB_UEP_RES_NAK | RB_UEP_TOG_DATA1;

    for (ep_idx = 1; ep_idx <= UEP_ADDRESS_MAX; ep_idx++)
    {
        usbhs->UEP_MAX_LEN[ep_idx].reg = UEP_MPS_512;
        /* set to DATA0, remains to be initialized (SET_CONFIGURATION...) */
        usbhs->UEP_CTRL[ep_idx].TX_CTRL.reg = RB_UEP_RES_NAK | RB_UEP_AUTOTOG;
        usbhs->UEP_CTRL[ep_idx].RX_CTRL.reg = RB_UEP_RES_NAK | RB_UEP_AUTOTOG;
    }
}

static rt_err_t udc_device_init(struct rt_device *device)
{
    volatile struct usbhs_registers *usbhs = device->user_data;

    sys_clk_off_by_irqn(USBHS_IRQn, SYS_SLP_CLK_ON);

    _hsbhs_device_mode_init(usbhs);

    rt_hw_interrupt_umask(USBHS_IRQn);

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
static struct rt_device_ops device_ops;
#endif

static int rt_hw_usbd_init(void)
{
    int ret;

    udc_device.parent.type = RT_Device_Class_USBDevice;
#ifdef RT_USING_DEVICE_OPS
    device_ops.init = udc_device_init;
    udc_device.parent.ops = &device_ops;
#else
    udc_device.parent.init = udc_device_init;
#endif
    udc_device.parent.user_data = (void *)USBHS_REG_BASE;
    udc_device.ops = &udcd_ops;
    udc_device.ep_pool = usbhs_ep_pool;
    udc_device.ep0.id = &usbhs_ep_pool[0];
    udc_device.device_is_hs = RT_TRUE;

    ret = rt_device_register(&udc_device.parent, "usbd", 0);
    if (ret == RT_EOK)
        ret = rt_usb_device_init();

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_usbd_init);

rt_inline uint8_t _uep_tog_datax(uint8_t tog)
{
    /* Note: treat tog as RB_UEP_TOG_DATA0 if not RB_UEP_TOG_DATA1 */
    return (tog == RB_UEP_TOG_DATA1) ? RB_UEP_TOG_DATA0 : RB_UEP_TOG_DATA1;
}

static void _isr_ep_stall(volatile struct usbhs_registers *usbhs)
{
    uint8_t ep_idx = usbhs->INT_ST.dev_endp_mask;

    usbhs->UEP_CTRL[ep_idx].TX_CTRL.res_mask == UEP_RES_STALL;
    usbhs->UEP_CTRL[ep_idx].RX_CTRL.res_mask == UEP_RES_STALL;
}

static void _isr_handle_setup(volatile struct usbhs_registers *usbhs)
{
    struct urequest setup, *packet;

    uint8_t ep_idx, xctrl, recipient;

    /* RES_NAK to block data stage, will expect or response DATA1 */
    usbhs->UEP_CTRL[0].TX_CTRL.reg = RB_UEP_RES_NAK | RB_UEP_TOG_DATA1;
    usbhs->UEP_CTRL[0].RX_CTRL.reg = RB_UEP_RES_NAK | RB_UEP_TOG_DATA1;

    packet = (struct urequest *)_ep0_setup_dmabuf;

    setup.request_type = packet->request_type;
    setup.bRequest = packet->bRequest;
    setup.wValue = packet->wValue;
    setup.wIndex = packet->wIndex;
    setup.wLength = packet->wLength;

    /* Init data toggle bit. Not sure if it has been done by h/w.*/
    xctrl = RB_UEP_RES_NAK | RB_UEP_AUTOTOG | RB_UEP_TOG_DATA0;
    recipient = setup.request_type & USB_REQ_TYPE_RECIPIENT_MASK;
    if (recipient == USB_REQ_TYPE_DEVICE &&
        setup.bRequest == USB_REQ_SET_CONFIGURATION)
    {
        for (ep_idx = 1; ep_idx <= UEP_ADDRESS_MAX; ep_idx++)
        {
            usbhs->UEP_CTRL[ep_idx].TX_CTRL.reg = xctrl;
            usbhs->UEP_CTRL[ep_idx].RX_CTRL.reg = xctrl;
        }
    }
    else if (recipient == USB_REQ_TYPE_ENDPOINT &&
             setup.bRequest == USB_REQ_CLEAR_FEATURE &&
             setup.wValue == USB_EP_HALT)
    {
        ep_idx = setup.wIndex;
        if (ep_idx > 0 && ep_idx <= UEP_ADDRESS_MAX)
        {
            usbhs->UEP_CTRL[ep_idx].TX_CTRL.reg = xctrl;
            usbhs->UEP_CTRL[ep_idx].RX_CTRL.reg = xctrl;
        }
    }

    rt_usbd_ep0_setup_handler(&udc_device, &setup);
}

static void _isr_handle_transfer(volatile struct usbhs_registers *usbhs)
{
    rt_size_t size;

    uint8_t ep_idx, token, tog;

    ep_idx = usbhs->INT_ST.dev_endp_mask;
    token = usbhs->INT_ST.dev_token_mask;

    if (ep_idx == 0)
    {
        if (token == DEV_TOKEN_IN)
        {
            /* UEP0 does not support AUTOTOG, generate DATAx manually */
            tog = usbhs->UEP_CTRL[0].TX_CTRL.reg & RB_UEP_TOG_MASK;
            tog = _uep_tog_datax(tog);
            /* wait for udc_ep_write or udc_ep0_send_status to RES_ACK */
            usbhs->UEP_CTRL[0].TX_CTRL.reg = RB_UEP_RES_NAK | tog;

            if (setup_set_address != 0 && usbhs->UEP_CTRL[0].t_len == 0)
            {
                usbhs->DEV_AD = setup_set_address & 0x7f;
                setup_set_address = 0;
            }
            /* don't call in_handler if send_status */
            if (usbhs->UEP0_RT_DMA != 0)
            {
                rt_usbd_ep0_in_handler(&udc_device);
            }
        }
        else if (token == DEV_TOKEN_OUT)
        {
            if (usbhs->INT_ST.st_togok)
            {
                /* UEP0 does not support AUTOTOG, generate DATAx manually */
                tog = usbhs->UEP_CTRL[0].RX_CTRL.reg & RB_UEP_TOG_MASK;
                tog = _uep_tog_datax(tog);
                /* wait for udc_ep_read_prepare to RES_ACK */
                usbhs->UEP_CTRL[0].RX_CTRL.reg = RB_UEP_RES_NAK | tog;
                rt_usbd_ep0_out_handler(&udc_device, usbhs->RX_LEN);
            }
            else
            {
                /* Corrupted ACK Handshake => ignore data, keep sequence bit */
                usbhs->UEP_CTRL[0].RX_CTRL.res_mask = UEP_RES_NAK;
            }
        }
    }
    else if (token == DEV_TOKEN_IN)
    {
        /* wait for udc_ep_write to RES_ACK */
        usbhs->UEP_CTRL[ep_idx].TX_CTRL.res_mask = UEP_RES_NAK;
        size = usbhs->UEP_CTRL[ep_idx].t_len;
        rt_usbd_ep_in_handler(&udc_device, ep_idx | USB_DIR_IN, size);
    }
    else if (token == DEV_TOKEN_OUT)
    {
        /* wait for udc_ep_read_prepare to RES_ACK */
        usbhs->UEP_CTRL[ep_idx].RX_CTRL.res_mask = UEP_RES_NAK;
        /* ignore data if Corrupted ACK Handshake */
        if (usbhs->INT_ST.st_togok)
        {
            /* size:0 to trigger dcd_ep_read() in _data_notify() */
            rt_usbd_ep_out_handler(&udc_device, ep_idx | USB_DIR_OUT, 0);
        }
    }
}

/*
 * CAVEAT: The usbd design of ch56x relies on instant isr to RES_NAK
 * UEP_CTRL[n].TX_CTRL/RX_CTRL. A long tarried isr may leave RES_ACK
 * in UEP_CTRL[n] and starts unintended DMA upon arrival of IN/OUT.
 */
void usbhs_irq_handler(void) __attribute__((interrupt()));
void usbhs_irq_handler(void)
{
    volatile struct usbhs_registers *usbhs;
    union _usb_int_fg intflag;

    isr_sp_enter();
    rt_interrupt_enter();

    usbhs = (struct usbhs_registers *)USBHS_REG_BASE;
    intflag.reg = usbhs->INT_FG.reg;

    if (intflag.fifoov)
    {
        /* FIXME: fifo overflow */
        _isr_ep_stall(usbhs);
    }
    else
    {
        if (intflag.transfer)
            _isr_handle_transfer(usbhs);

        if (intflag.setupact)
            _isr_handle_setup(usbhs);
    }

    if (intflag.busrst)
    {
        _hsbhs_device_mode_init(usbhs);
        rt_usbd_reset_handler(&udc_device);
    }

    /* clear all pending intflag (suspend, isoact & nak ignored) */
    usbhs->INT_FG.reg = intflag.reg;

    rt_interrupt_leave();
    isr_sp_leave();
}
