/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_hub.h"
#include "usb_musb_reg.h"

#define HWREG(x) \
    (*((volatile uint32_t *)(x)))
#define HWREGH(x) \
    (*((volatile uint16_t *)(x)))
#define HWREGB(x) \
    (*((volatile uint8_t *)(x)))

#define USB_BASE (bus->hcd.reg_base)

#if CONFIG_USBHOST_PIPE_NUM != 4
#error musb host ip only supports 4 pipe num
#endif

#ifdef CONFIG_USB_MUSB_SUNXI
#define MUSB_FADDR_OFFSET 0x98
#define MUSB_POWER_OFFSET 0x40
#define MUSB_TXIS_OFFSET  0x44
#define MUSB_RXIS_OFFSET  0x46
#define MUSB_TXIE_OFFSET  0x48
#define MUSB_RXIE_OFFSET  0x4A
#define MUSB_IS_OFFSET    0x4C
#define MUSB_IE_OFFSET    0x50
#define MUSB_EPIDX_OFFSET 0x42

#define MUSB_IND_TXMAP_OFFSET      0x80
#define MUSB_IND_TXCSRL_OFFSET     0x82
#define MUSB_IND_TXCSRH_OFFSET     0x83
#define MUSB_IND_RXMAP_OFFSET      0x84
#define MUSB_IND_RXCSRL_OFFSET     0x86
#define MUSB_IND_RXCSRH_OFFSET     0x87
#define MUSB_IND_RXCOUNT_OFFSET    0x88
#define MUSB_IND_TXTYPE_OFFSET     0x8C
#define MUSB_IND_TXINTERVAL_OFFSET 0x8D
#define MUSB_IND_RXTYPE_OFFSET     0x8E
#define MUSB_IND_RXINTERVAL_OFFSET 0x8F

#define MUSB_FIFO_OFFSET 0x00

#define MUSB_DEVCTL_OFFSET 0x41

#define MUSB_TXFIFOSZ_OFFSET  0x90
#define MUSB_RXFIFOSZ_OFFSET  0x94
#define MUSB_TXFIFOADD_OFFSET 0x92
#define MUSB_RXFIFOADD_OFFSET 0x96

#define MUSB_TXFUNCADDR0_OFFSET 0x98
#define MUSB_TXHUBADDR0_OFFSET  0x9A
#define MUSB_TXHUBPORT0_OFFSET  0x9B
#define MUSB_TXFUNCADDRx_OFFSET 0x98
#define MUSB_TXHUBADDRx_OFFSET  0x9A
#define MUSB_TXHUBPORTx_OFFSET  0x9B
#define MUSB_RXFUNCADDRx_OFFSET 0x9C
#define MUSB_RXHUBADDRx_OFFSET  0x9E
#define MUSB_RXHUBPORTx_OFFSET  0x9F

#define USB_TXADDR_BASE(ep_idx)    (USB_BASE + MUSB_TXFUNCADDRx_OFFSET)
#define USB_TXHUBADDR_BASE(ep_idx) (USB_BASE + MUSB_TXHUBADDRx_OFFSET)
#define USB_TXHUBPORT_BASE(ep_idx) (USB_BASE + MUSB_TXHUBPORTx_OFFSET)
#define USB_RXADDR_BASE(ep_idx)    (USB_BASE + MUSB_RXFUNCADDRx_OFFSET)
#define USB_RXHUBADDR_BASE(ep_idx) (USB_BASE + MUSB_RXHUBADDRx_OFFSET)
#define USB_RXHUBPORT_BASE(ep_idx) (USB_BASE + MUSB_RXHUBPORTx_OFFSET)

#elif defined(CONFIG_USB_MUSB_CUSTOM)
#include "musb_custom.h"
#else
#define MUSB_FADDR_OFFSET 0x00
#define MUSB_POWER_OFFSET 0x01
#define MUSB_TXIS_OFFSET  0x02
#define MUSB_RXIS_OFFSET  0x04
#define MUSB_TXIE_OFFSET  0x06
#define MUSB_RXIE_OFFSET  0x08
#define MUSB_IS_OFFSET    0x0A
#define MUSB_IE_OFFSET    0x0B

#define MUSB_EPIDX_OFFSET 0x0E

#define MUSB_IND_TXMAP_OFFSET      0x10
#define MUSB_IND_TXCSRL_OFFSET     0x12
#define MUSB_IND_TXCSRH_OFFSET     0x13
#define MUSB_IND_RXMAP_OFFSET      0x14
#define MUSB_IND_RXCSRL_OFFSET     0x16
#define MUSB_IND_RXCSRH_OFFSET     0x17
#define MUSB_IND_RXCOUNT_OFFSET    0x18
#define MUSB_IND_TXTYPE_OFFSET     0x1A
#define MUSB_IND_TXINTERVAL_OFFSET 0x1B
#define MUSB_IND_RXTYPE_OFFSET     0x1C
#define MUSB_IND_RXINTERVAL_OFFSET 0x1D

#define MUSB_FIFO_OFFSET 0x20

#define MUSB_DEVCTL_OFFSET 0x60

#define MUSB_TXFIFOSZ_OFFSET  0x62
#define MUSB_RXFIFOSZ_OFFSET  0x63
#define MUSB_TXFIFOADD_OFFSET 0x64
#define MUSB_RXFIFOADD_OFFSET 0x66

#define MUSB_TXFUNCADDR0_OFFSET 0x80
#define MUSB_TXHUBADDR0_OFFSET  0x82
#define MUSB_TXHUBPORT0_OFFSET  0x83
#define MUSB_TXFUNCADDRx_OFFSET 0x88
#define MUSB_TXHUBADDRx_OFFSET  0x8A
#define MUSB_TXHUBPORTx_OFFSET  0x8B
#define MUSB_RXFUNCADDRx_OFFSET 0x8C
#define MUSB_RXHUBADDRx_OFFSET  0x8E
#define MUSB_RXHUBPORTx_OFFSET  0x8F

#define USB_TXADDR_BASE(ep_idx)    (USB_BASE + MUSB_TXFUNCADDR0_OFFSET + 0x8 * ep_idx)
#define USB_TXHUBADDR_BASE(ep_idx) (USB_BASE + MUSB_TXFUNCADDR0_OFFSET + 0x8 * ep_idx + 2)
#define USB_TXHUBPORT_BASE(ep_idx) (USB_BASE + MUSB_TXFUNCADDR0_OFFSET + 0x8 * ep_idx + 3)
#define USB_RXADDR_BASE(ep_idx)    (USB_BASE + MUSB_TXFUNCADDR0_OFFSET + 0x8 * ep_idx + 4)
#define USB_RXHUBADDR_BASE(ep_idx) (USB_BASE + MUSB_TXFUNCADDR0_OFFSET + 0x8 * ep_idx + 6)
#define USB_RXHUBPORT_BASE(ep_idx) (USB_BASE + MUSB_TXFUNCADDR0_OFFSET + 0x8 * ep_idx + 7)
#endif

#define USB_FIFO_BASE(ep_idx) (USB_BASE + MUSB_FIFO_OFFSET + 0x4 * ep_idx)

#ifndef CONIFG_USB_MUSB_PIPE_NUM
#define CONIFG_USB_MUSB_PIPE_NUM 5
#endif

typedef enum {
    USB_EP0_STATE_SETUP = 0x0, /**< SETUP DATA */
    USB_EP0_STATE_IN_DATA,     /**< IN DATA */
    USB_EP0_STATE_IN_STATUS,   /**< IN status*/
    USB_EP0_STATE_OUT_DATA,    /**< OUT DATA */
    USB_EP0_STATE_OUT_STATUS,  /**< OUT status */
} ep0_state_t;

struct musb_pipe {
    uint8_t chidx;
    bool inuse;
    uint32_t xfrd;
    volatile uint8_t ep0_state;
    usb_osal_sem_t waitsem;
    struct usbh_urb *urb;
};

struct musb_hcd {
    volatile bool port_csc;
    volatile bool port_pec;
    volatile bool port_pe;
    struct musb_pipe pipe_pool[CONFIG_USBHOST_PIPE_NUM];
} g_musb_hcd[CONFIG_USBHOST_MAX_BUS];

/* get current active ep */
static uint8_t musb_get_active_ep(struct usbh_bus *bus)
{
    return HWREGB(USB_BASE + MUSB_EPIDX_OFFSET);
}

/* set the active ep */
static void musb_set_active_ep(struct usbh_bus *bus, uint8_t ep_index)
{
    HWREGB(USB_BASE + MUSB_EPIDX_OFFSET) = ep_index;
}

static void musb_fifo_flush(struct usbh_bus *bus, uint8_t ep)
{
    uint8_t ep_idx = ep & 0x7f;
    if (ep_idx == 0) {
        if ((HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) & (USB_CSRL0_RXRDY | USB_CSRL0_TXRDY)) != 0)
            HWREGB(USB_BASE + MUSB_IND_RXCSRL_OFFSET) |= USB_CSRH0_FLUSH;
    } else {
        if (ep & 0x80) {
            if (HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) & USB_TXCSRL1_TXRDY)
                HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) |= USB_TXCSRL1_FLUSH;
        } else {
            if (HWREGB(USB_BASE + MUSB_IND_RXCSRL_OFFSET) & USB_RXCSRL1_RXRDY)
                HWREGB(USB_BASE + MUSB_IND_RXCSRL_OFFSET) |= USB_RXCSRL1_FLUSH;
        }
    }
}

static void musb_write_packet(struct usbh_bus *bus, uint8_t ep_idx, uint8_t *buffer, uint16_t len)
{
    uint32_t *buf32;
    uint8_t *buf8;
    uint32_t count32;
    uint32_t count8;
    int i;

    if ((uint32_t)buffer & 0x03) {
        buf8 = buffer;
        for (i = 0; i < len; i++) {
            HWREGB(USB_FIFO_BASE(ep_idx)) = *buf8++;
        }
    } else {
        count32 = len >> 2;
        count8 = len & 0x03;

        buf32 = (uint32_t *)buffer;

        while (count32--) {
            HWREG(USB_FIFO_BASE(ep_idx)) = *buf32++;
        }

        buf8 = (uint8_t *)buf32;

        while (count8--) {
            HWREGB(USB_FIFO_BASE(ep_idx)) = *buf8++;
        }
    }
}

static void musb_read_packet(struct usbh_bus *bus, uint8_t ep_idx, uint8_t *buffer, uint16_t len)
{
    uint32_t *buf32;
    uint8_t *buf8;
    uint32_t count32;
    uint32_t count8;
    int i;

    if ((uint32_t)buffer & 0x03) {
        buf8 = buffer;
        for (i = 0; i < len; i++) {
            *buf8++ = HWREGB(USB_FIFO_BASE(ep_idx));
        }
    } else {
        count32 = len >> 2;
        count8 = len & 0x03;

        buf32 = (uint32_t *)buffer;

        while (count32--) {
            *buf32++ = HWREG(USB_FIFO_BASE(ep_idx));
        }

        buf8 = (uint8_t *)buf32;

        while (count8--) {
            *buf8++ = HWREGB(USB_FIFO_BASE(ep_idx));
        }
    }
}

void musb_control_urb_init(struct usbh_bus *bus, uint8_t chidx, struct usbh_urb *urb, struct usb_setup_packet *setup, uint8_t *buffer, uint32_t buflen)
{
    uint8_t old_ep_index;
    uint8_t speed = USB_TXTYPE1_SPEED_FULL;

    old_ep_index = musb_get_active_ep(bus);
    musb_set_active_ep(bus, chidx);

    if (urb->hport->speed == USB_SPEED_HIGH) {
        speed = USB_TYPE0_SPEED_HIGH;
    } else if (urb->hport->speed == USB_SPEED_FULL) {
        speed = USB_TYPE0_SPEED_FULL;
    } else if (urb->hport->speed == USB_SPEED_LOW) {
        speed = USB_TYPE0_SPEED_LOW;
    }

    HWREGB(USB_TXADDR_BASE(chidx)) = urb->hport->dev_addr;
    HWREGB(USB_BASE + MUSB_IND_TXTYPE_OFFSET) = speed;
    HWREGB(USB_TXHUBADDR_BASE(chidx)) = 0;
    HWREGB(USB_TXHUBPORT_BASE(chidx)) = 0;

    musb_write_packet(bus, chidx, (uint8_t *)setup, 8);
    HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) = USB_CSRL0_TXRDY | USB_CSRL0_SETUP;
    musb_set_active_ep(bus, old_ep_index);
}

void musb_bulk_urb_init(struct usbh_bus *bus, uint8_t chidx, struct usbh_urb *urb, uint8_t *buffer, uint32_t buflen)
{
    uint8_t old_ep_index;
    uint8_t speed = USB_TXTYPE1_SPEED_FULL;

    old_ep_index = musb_get_active_ep(bus);
    musb_set_active_ep(bus, chidx);

    if (urb->hport->speed == USB_SPEED_HIGH) {
        speed = USB_TXTYPE1_SPEED_HIGH;
    } else if (urb->hport->speed == USB_SPEED_FULL) {
        speed = USB_TXTYPE1_SPEED_FULL;
    } else if (urb->hport->speed == USB_SPEED_LOW) {
        speed = USB_TXTYPE1_SPEED_LOW;
    }

    if (urb->ep->bEndpointAddress & 0x80) {
        HWREGB(USB_RXADDR_BASE(chidx)) = urb->hport->dev_addr;
        HWREGB(USB_BASE + MUSB_IND_RXTYPE_OFFSET) = (urb->ep->bEndpointAddress & 0x0f) | speed | USB_TXTYPE1_PROTO_BULK;
        HWREGB(USB_BASE + MUSB_IND_RXINTERVAL_OFFSET) = 0;
        HWREGB(USB_RXHUBADDR_BASE(chidx)) = 0;
        HWREGB(USB_RXHUBPORT_BASE(chidx)) = 0;
        HWREGB(USB_BASE + MUSB_IND_TXCSRH_OFFSET) &= ~USB_TXCSRH1_MODE;
        HWREGB(USB_BASE + MUSB_IND_RXCSRL_OFFSET) = USB_RXCSRL1_REQPKT;

        HWREGH(USB_BASE + MUSB_RXIE_OFFSET) |= (1 << chidx);
    } else {
        HWREGB(USB_TXADDR_BASE(chidx)) = urb->hport->dev_addr;
        HWREGB(USB_BASE + MUSB_IND_TXTYPE_OFFSET) = (urb->ep->bEndpointAddress & 0x0f) | speed | USB_TXTYPE1_PROTO_BULK;
        HWREGB(USB_BASE + MUSB_IND_TXINTERVAL_OFFSET) = 0;
        HWREGB(USB_TXHUBADDR_BASE(chidx)) = 0;
        HWREGB(USB_TXHUBPORT_BASE(chidx)) = 0;

        if (buflen > USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize)) {
            buflen = USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize);
        }

        musb_write_packet(bus, chidx, buffer, buflen);
        HWREGB(USB_BASE + MUSB_IND_TXCSRH_OFFSET) &= ~USB_TXCSRH1_MODE;
        HWREGB(USB_BASE + MUSB_IND_TXCSRH_OFFSET) |= USB_TXCSRH1_MODE;
        HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) = USB_TXCSRL1_TXRDY;

        HWREGH(USB_BASE + MUSB_TXIE_OFFSET) |= (1 << chidx);
    }
    musb_set_active_ep(bus, old_ep_index);
}

void musb_intr_urb_init(struct usbh_bus *bus, uint8_t chidx, struct usbh_urb *urb, uint8_t *buffer, uint32_t buflen)
{
    uint8_t old_ep_index;
    uint8_t speed = USB_TXTYPE1_SPEED_FULL;

    old_ep_index = musb_get_active_ep(bus);
    musb_set_active_ep(bus, chidx);

    if (urb->hport->speed == USB_SPEED_HIGH) {
        speed = USB_TXTYPE1_SPEED_HIGH;
    } else if (urb->hport->speed == USB_SPEED_FULL) {
        speed = USB_TXTYPE1_SPEED_FULL;
    } else if (urb->hport->speed == USB_SPEED_LOW) {
        speed = USB_TXTYPE1_SPEED_LOW;
    }

    if (urb->ep->bEndpointAddress & 0x80) {
        HWREGB(USB_RXADDR_BASE(chidx)) = urb->hport->dev_addr;
        HWREGB(USB_BASE + MUSB_IND_RXTYPE_OFFSET) = (urb->ep->bEndpointAddress & 0x0f) | speed | USB_TXTYPE1_PROTO_INT;
        HWREGB(USB_BASE + MUSB_IND_RXINTERVAL_OFFSET) = urb->ep->bInterval;
        HWREGB(USB_RXHUBADDR_BASE(chidx)) = 0;
        HWREGB(USB_RXHUBPORT_BASE(chidx)) = 0;
        HWREGB(USB_BASE + MUSB_IND_TXCSRH_OFFSET) &= ~USB_TXCSRH1_MODE;
        HWREGB(USB_BASE + MUSB_IND_RXCSRL_OFFSET) = USB_RXCSRL1_REQPKT;

        HWREGH(USB_BASE + MUSB_RXIE_OFFSET) |= (1 << chidx);
    } else {
        HWREGB(USB_TXADDR_BASE(chidx)) = urb->hport->dev_addr;
        HWREGB(USB_BASE + MUSB_IND_TXTYPE_OFFSET) = (urb->ep->bEndpointAddress & 0x0f) | speed | USB_TXTYPE1_PROTO_INT;
        HWREGB(USB_BASE + MUSB_IND_TXINTERVAL_OFFSET) = urb->ep->bInterval;
        HWREGB(USB_TXHUBADDR_BASE(chidx)) = 0;
        HWREGB(USB_TXHUBPORT_BASE(chidx)) = 0;

        if (buflen > USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize)) {
            buflen = USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize);
        }

        musb_write_packet(bus, chidx, buffer, buflen);
        HWREGB(USB_BASE + MUSB_IND_TXCSRH_OFFSET) &= ~USB_TXCSRH1_MODE;
        HWREGB(USB_BASE + MUSB_IND_TXCSRH_OFFSET) |= USB_TXCSRH1_MODE;
        HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) = USB_TXCSRL1_TXRDY;

        HWREGH(USB_BASE + MUSB_TXIE_OFFSET) |= (1 << chidx);
    }
    musb_set_active_ep(bus, old_ep_index);
}

static int usbh_reset_port(struct usbh_bus *bus, const uint8_t port)
{
    g_musb_hcd[bus->hcd.hcd_id].port_pe = 0;
    HWREGB(USB_BASE + MUSB_POWER_OFFSET) |= USB_POWER_RESET;
    usb_osal_msleep(20);
    HWREGB(USB_BASE + MUSB_POWER_OFFSET) &= ~(USB_POWER_RESET);
    usb_osal_msleep(20);
    g_musb_hcd[bus->hcd.hcd_id].port_pe = 1;
    return 0;
}

static uint8_t usbh_get_port_speed(struct usbh_bus *bus, const uint8_t port)
{
    uint8_t speed = USB_SPEED_UNKNOWN;

    if (HWREGB(USB_BASE + MUSB_POWER_OFFSET) & USB_POWER_HSMODE)
        speed = USB_SPEED_HIGH;
    else if (HWREGB(USB_BASE + MUSB_DEVCTL_OFFSET) & USB_DEVCTL_FSDEV)
        speed = USB_SPEED_FULL;
    else if (HWREGB(USB_BASE + MUSB_DEVCTL_OFFSET) & USB_DEVCTL_LSDEV)
        speed = USB_SPEED_LOW;

    return speed;
}

#if 0
static int musb_pipe_alloc(void)
{
    int chidx;

    for (chidx = 1; chidx < CONFIG_USBHOST_PIPE_NUM; chidx++) {
        if (!g_musb_hcd[bus->hcd.hcd_id].pipe_pool[chidx].inuse) {
            g_musb_hcd[bus->hcd.hcd_id].pipe_pool[chidx].inuse = true;
            return chidx;
        }
    }

    return -1;
}
#endif

static void musb_pipe_free(struct musb_pipe *pipe)
{
#if 0
    pipe->inuse = false;
#endif
}

__WEAK void usb_hc_low_level_init(struct usbh_bus *bus)
{
}

__WEAK void usb_hc_low_level_deinit(struct usbh_bus *bus)
{
}

int usb_hc_init(struct usbh_bus *bus)
{
    uint8_t regval;
    uint32_t fifo_offset = 0;

    memset(&g_musb_hcd[bus->hcd.hcd_id], 0, sizeof(struct musb_hcd));

    for (uint8_t i = 0; i < CONFIG_USBHOST_PIPE_NUM; i++) {
        g_musb_hcd[bus->hcd.hcd_id].pipe_pool[i].waitsem = usb_osal_sem_create(0);
    }

    usb_hc_low_level_init(bus);

    musb_set_active_ep(bus, 0);
    HWREGB(USB_BASE + MUSB_IND_TXINTERVAL_OFFSET) = 0;
    HWREGB(USB_BASE + MUSB_TXFIFOSZ_OFFSET) = USB_TXFIFOSZ_SIZE_64;
    HWREGH(USB_BASE + MUSB_TXFIFOADD_OFFSET) = 0;
    HWREGB(USB_BASE + MUSB_RXFIFOSZ_OFFSET) = USB_TXFIFOSZ_SIZE_64;
    HWREGH(USB_BASE + MUSB_RXFIFOADD_OFFSET) = 0;
    fifo_offset += 64;

    for (uint8_t i = 1; i < CONIFG_USB_MUSB_PIPE_NUM; i++) {
        musb_set_active_ep(bus, i);
        HWREGB(USB_BASE + MUSB_TXFIFOSZ_OFFSET) = USB_TXFIFOSZ_SIZE_512;
        HWREGH(USB_BASE + MUSB_TXFIFOADD_OFFSET) = fifo_offset;
        HWREGB(USB_BASE + MUSB_RXFIFOSZ_OFFSET) = USB_TXFIFOSZ_SIZE_512;
        HWREGH(USB_BASE + MUSB_RXFIFOADD_OFFSET) = fifo_offset;
        fifo_offset += 512;
    }

    /* Enable USB interrupts */
    regval = USB_IE_RESET | USB_IE_CONN | USB_IE_DISCON |
             USB_IE_RESUME | USB_IE_SUSPND |
             USB_IE_BABBLE | USB_IE_SESREQ | USB_IE_VBUSERR;

    HWREGB(USB_BASE + MUSB_IE_OFFSET) = regval;
    HWREGH(USB_BASE + MUSB_TXIE_OFFSET) = USB_TXIE_EP0;
    HWREGH(USB_BASE + MUSB_RXIE_OFFSET) = 0;

    HWREGB(USB_BASE + MUSB_POWER_OFFSET) |= USB_POWER_HSENAB;

    HWREGB(USB_BASE + MUSB_DEVCTL_OFFSET) |= USB_DEVCTL_SESSION;

#ifdef CONFIG_USB_MUSB_SUNXI
    musb_set_active_ep(bus, 0);
    HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) = USB_CSRL0_TXRDY;
#endif
    return 0;
}

int usb_hc_deinit(struct usbh_bus *bus)
{
    HWREGB(USB_BASE + MUSB_IE_OFFSET) = 0;
    HWREGH(USB_BASE + MUSB_TXIE_OFFSET) = 0;
    HWREGH(USB_BASE + MUSB_RXIE_OFFSET) = 0;

    HWREGB(USB_BASE + MUSB_POWER_OFFSET) &= ~USB_POWER_HSENAB;
    HWREGB(USB_BASE + MUSB_DEVCTL_OFFSET) &= ~USB_DEVCTL_SESSION;

    for (uint8_t i = 0; i < CONFIG_USBHOST_PIPE_NUM; i++) {
        usb_osal_sem_delete(g_musb_hcd[bus->hcd.hcd_id].pipe_pool[i].waitsem);
    }

    usb_hc_low_level_deinit(bus);
    return 0;
}

int usbh_roothub_control(struct usbh_bus *bus, struct usb_setup_packet *setup, uint8_t *buf)
{
    uint8_t nports;
    uint8_t port;
    uint32_t status;

    nports = CONFIG_USBHOST_MAX_RHPORTS;
    port = setup->wIndex;
    if (setup->bmRequestType & USB_REQUEST_RECIPIENT_DEVICE) {
        switch (setup->bRequest) {
            case HUB_REQUEST_CLEAR_FEATURE:
                switch (setup->wValue) {
                    case HUB_FEATURE_HUB_C_LOCALPOWER:
                        break;
                    case HUB_FEATURE_HUB_C_OVERCURRENT:
                        break;
                    default:
                        return -USB_ERR_INVAL;
                }
                break;
            case HUB_REQUEST_SET_FEATURE:
                switch (setup->wValue) {
                    case HUB_FEATURE_HUB_C_LOCALPOWER:
                        break;
                    case HUB_FEATURE_HUB_C_OVERCURRENT:
                        break;
                    default:
                        return -USB_ERR_INVAL;
                }
                break;
            case HUB_REQUEST_GET_DESCRIPTOR:
                break;
            case HUB_REQUEST_GET_STATUS:
                memset(buf, 0, 4);
                break;
            default:
                break;
        }
    } else if (setup->bmRequestType & USB_REQUEST_RECIPIENT_OTHER) {
        switch (setup->bRequest) {
            case HUB_REQUEST_CLEAR_FEATURE:
                if (!port || port > nports) {
                    return -USB_ERR_INVAL;
                }

                switch (setup->wValue) {
                    case HUB_PORT_FEATURE_ENABLE:
                        break;
                    case HUB_PORT_FEATURE_SUSPEND:
                    case HUB_PORT_FEATURE_C_SUSPEND:
                        break;
                    case HUB_PORT_FEATURE_POWER:
                        break;
                    case HUB_PORT_FEATURE_C_CONNECTION:
                        g_musb_hcd[bus->hcd.hcd_id].port_csc = 0;
                        break;
                    case HUB_PORT_FEATURE_C_ENABLE:
                        g_musb_hcd[bus->hcd.hcd_id].port_pec = 0;
                        break;
                    case HUB_PORT_FEATURE_C_OVER_CURREN:
                        break;
                    case HUB_PORT_FEATURE_C_RESET:
                        break;
                    default:
                        return -USB_ERR_INVAL;
                }
                break;
            case HUB_REQUEST_SET_FEATURE:
                if (!port || port > nports) {
                    return -USB_ERR_INVAL;
                }

                switch (setup->wValue) {
                    case HUB_PORT_FEATURE_SUSPEND:
                        break;
                    case HUB_PORT_FEATURE_POWER:
                        break;
                    case HUB_PORT_FEATURE_RESET:
                        usbh_reset_port(bus, port);
                        break;

                    default:
                        return -USB_ERR_INVAL;
                }
                break;
            case HUB_REQUEST_GET_STATUS:
                if (!port || port > nports) {
                    return -USB_ERR_INVAL;
                }

                status = 0;
                if (g_musb_hcd[bus->hcd.hcd_id].port_csc) {
                    status |= (1 << HUB_PORT_FEATURE_C_CONNECTION);
                }
                if (g_musb_hcd[bus->hcd.hcd_id].port_pec) {
                    status |= (1 << HUB_PORT_FEATURE_C_ENABLE);
                }

                if (g_musb_hcd[bus->hcd.hcd_id].port_pe) {
                    status |= (1 << HUB_PORT_FEATURE_CONNECTION);
                    status |= (1 << HUB_PORT_FEATURE_ENABLE);
                    if (usbh_get_port_speed(bus, port) == USB_SPEED_LOW) {
                        status |= (1 << HUB_PORT_FEATURE_LOWSPEED);
                    } else if (usbh_get_port_speed(bus, port) == USB_SPEED_HIGH) {
                        status |= (1 << HUB_PORT_FEATURE_HIGHSPEED);
                    }
                }

                memcpy(buf, &status, 4);
                break;
            default:
                break;
        }
    }
    return 0;
}

int usbh_submit_urb(struct usbh_urb *urb)
{
    struct musb_pipe *pipe;
    struct usbh_bus *bus;
    int chidx;
    size_t flags;
    int ret = 0;

    if (!urb || !urb->hport || !urb->ep || !urb->hport->bus) {
        return -USB_ERR_INVAL;
    }

    if (!urb->hport->connected) {
        return -USB_ERR_NOTCONN;
    }

    if (urb->errorcode == -USB_ERR_BUSY) {
        return -USB_ERR_BUSY;
    }

    bus = urb->hport->bus;

    flags = usb_osal_enter_critical_section();

    if (USB_GET_ENDPOINT_TYPE(urb->ep->bmAttributes) == USB_ENDPOINT_TYPE_CONTROL) {
        chidx = 0;
    } else {
        chidx = (urb->ep->bEndpointAddress & 0x0f);

        if (chidx > (CONFIG_USBHOST_PIPE_NUM - 1)) {
            return -USB_ERR_RANGE;
        }
    }

    pipe = &g_musb_hcd[bus->hcd.hcd_id].pipe_pool[chidx];
    pipe->chidx = chidx;
    pipe->urb = urb;

    urb->hcpriv = pipe;
    urb->errorcode = -USB_ERR_BUSY;
    urb->actual_length = 0;

    usb_osal_sem_reset(pipe->waitsem);

    switch (USB_GET_ENDPOINT_TYPE(urb->ep->bmAttributes)) {
        case USB_ENDPOINT_TYPE_CONTROL:
            pipe->ep0_state = USB_EP0_STATE_SETUP;
            musb_control_urb_init(bus, 0, urb, urb->setup, urb->transfer_buffer, urb->transfer_buffer_length);
            break;
        case USB_ENDPOINT_TYPE_BULK:
            musb_bulk_urb_init(bus, chidx, urb, urb->transfer_buffer, urb->transfer_buffer_length);
            break;
        case USB_ENDPOINT_TYPE_INTERRUPT:
            musb_intr_urb_init(bus, chidx, urb, urb->transfer_buffer, urb->transfer_buffer_length);
            break;
        case USB_ENDPOINT_TYPE_ISOCHRONOUS:
            return -USB_ERR_NOTSUPP;
        default:
            break;
    }
    usb_osal_leave_critical_section(flags);

    if (urb->timeout > 0) {
        /* wait until timeout or sem give */
        ret = usb_osal_sem_take(pipe->waitsem, urb->timeout);
        if (ret < 0) {
            goto errout_timeout;
        }
        urb->timeout = 0;
        ret = urb->errorcode;
        /* we can free pipe when waitsem is done */
        musb_pipe_free(pipe);
    }
    return ret;
errout_timeout:
    urb->timeout = 0;
    usbh_kill_urb(urb);
    return ret;
}

int usbh_kill_urb(struct usbh_urb *urb)
{
    struct musb_pipe *pipe;
    struct usbh_bus *bus;
    size_t flags;

    if (!urb || !urb->hcpriv || !urb->hport->bus) {
        return -USB_ERR_INVAL;
    }

    bus = urb->hport->bus;

    ARG_UNUSED(bus);

    flags = usb_osal_enter_critical_section();

    pipe = (struct musb_pipe *)urb->hcpriv;
    urb->hcpriv = NULL;
    urb->errorcode = -USB_ERR_SHUTDOWN;
    pipe->urb = NULL;

    if (urb->timeout) {
        usb_osal_sem_give(pipe->waitsem);
    } else {
        musb_pipe_free(pipe);
    }

    usb_osal_leave_critical_section(flags);
    return 0;
}

static void musb_urb_waitup(struct usbh_urb *urb)
{
    struct musb_pipe *pipe;

    pipe = (struct musb_pipe *)urb->hcpriv;
    pipe->urb = NULL;
    urb->hcpriv = NULL;

    if (urb->timeout) {
        usb_osal_sem_give(pipe->waitsem);
    } else {
        musb_pipe_free(pipe);
    }

    if (urb->complete) {
        if (urb->errorcode < 0) {
            urb->complete(urb->arg, urb->errorcode);
        } else {
            urb->complete(urb->arg, urb->actual_length);
        }
    }
}

void handle_ep0(struct usbh_bus *bus)
{
    uint8_t ep0_status;
    struct musb_pipe *pipe;
    struct usbh_urb *urb;
    uint32_t size;

    pipe = (struct musb_pipe *)&g_musb_hcd[bus->hcd.hcd_id].pipe_pool[0];
    urb = pipe->urb;
    if (urb == NULL) {
        return;
    }

    musb_set_active_ep(bus, 0);
    ep0_status = HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET);
    if (ep0_status & USB_CSRL0_STALLED) {
        HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) &= ~USB_CSRL0_STALLED;
        pipe->ep0_state = USB_EP0_STATE_SETUP;
        urb->errorcode = -USB_ERR_STALL;
        musb_urb_waitup(urb);
        return;
    }
    if (ep0_status & USB_CSRL0_ERROR) {
        HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) &= ~USB_CSRL0_ERROR;
        musb_fifo_flush(bus, 0);
        pipe->ep0_state = USB_EP0_STATE_SETUP;
        urb->errorcode = -USB_ERR_IO;
        musb_urb_waitup(urb);
        return;
    }
    if (ep0_status & USB_CSRL0_STALL) {
        HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) &= ~USB_CSRL0_STALL;
        pipe->ep0_state = USB_EP0_STATE_SETUP;
        urb->errorcode = -USB_ERR_STALL;
        musb_urb_waitup(urb);
        return;
    }

    switch (pipe->ep0_state) {
        case USB_EP0_STATE_SETUP:
            urb->actual_length += 8;
            if (urb->transfer_buffer_length) {
                if (urb->setup->bmRequestType & 0x80) {
                    pipe->ep0_state = USB_EP0_STATE_IN_DATA;
                    HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) = USB_CSRL0_REQPKT;
                } else {
                    pipe->ep0_state = USB_EP0_STATE_OUT_DATA;
                    size = urb->transfer_buffer_length;
                    if (size > USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize)) {
                        size = USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize);
                    }

                    musb_write_packet(bus, 0, urb->transfer_buffer, size);
                    HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) = USB_CSRL0_TXRDY;

                    urb->transfer_buffer += size;
                    urb->transfer_buffer_length -= size;
                    urb->actual_length += size;
                }
            } else {
                pipe->ep0_state = USB_EP0_STATE_IN_STATUS;
                HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) = (USB_CSRL0_REQPKT | USB_CSRL0_STATUS);
            }
            break;
        case USB_EP0_STATE_IN_DATA:
            if (ep0_status & USB_CSRL0_RXRDY) {
                size = urb->transfer_buffer_length;
                if (size > USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize)) {
                    size = USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize);
                }

                size = MIN(size, HWREGH(USB_BASE + MUSB_IND_RXCOUNT_OFFSET));
                musb_read_packet(bus, 0, urb->transfer_buffer, size);
                HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) &= ~USB_CSRL0_RXRDY;
                urb->transfer_buffer += size;
                urb->transfer_buffer_length -= size;
                urb->actual_length += size;

                if ((size < USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize)) || (urb->transfer_buffer_length == 0)) {
                    pipe->ep0_state = USB_EP0_STATE_OUT_STATUS;
                    HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) = (USB_CSRL0_TXRDY | USB_CSRL0_STATUS);
                } else {
                    HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) = USB_CSRL0_REQPKT;
                }
            }
            break;
        case USB_EP0_STATE_OUT_DATA:
            if (urb->transfer_buffer_length > 0) {
                size = urb->transfer_buffer_length;
                if (size > USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize)) {
                    size = USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize);
                }

                musb_write_packet(bus, 0, urb->transfer_buffer, size);
                HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) = USB_CSRL0_TXRDY;

                urb->transfer_buffer += size;
                urb->transfer_buffer_length -= size;
                urb->actual_length += size;
            } else {
                pipe->ep0_state = USB_EP0_STATE_IN_STATUS;
                HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) = (USB_CSRL0_REQPKT | USB_CSRL0_STATUS);
            }
            break;
        case USB_EP0_STATE_OUT_STATUS:
            urb->errorcode = 0;
            musb_urb_waitup(urb);
            break;
        case USB_EP0_STATE_IN_STATUS:
            if (ep0_status & (USB_CSRL0_RXRDY | USB_CSRL0_STATUS)) {
                HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) &= ~(USB_CSRL0_RXRDY | USB_CSRL0_STATUS);
                urb->errorcode = 0;
                musb_urb_waitup(urb);
            }
            break;
    }
}

void USBH_IRQHandler(uint8_t busid)
{
    uint32_t is;
    uint32_t txis;
    uint32_t rxis;
    uint8_t ep_csrl_status;
    // uint8_t ep_csrh_status;
    struct musb_pipe *pipe;
    struct usbh_urb *urb;
    uint8_t ep_idx;
    uint8_t old_ep_idx;
    struct usbh_bus *bus;

    bus = &g_usbhost_bus[busid];
    
    is = HWREGB(USB_BASE + MUSB_IS_OFFSET);
    txis = HWREGH(USB_BASE + MUSB_TXIS_OFFSET);
    rxis = HWREGH(USB_BASE + MUSB_RXIS_OFFSET);

    HWREGB(USB_BASE + MUSB_IS_OFFSET) = is;

    old_ep_idx = musb_get_active_ep(bus);

    if (is & USB_IS_CONN) {
        g_musb_hcd[bus->hcd.hcd_id].port_csc = 1;
        g_musb_hcd[bus->hcd.hcd_id].port_pec = 1;
        g_musb_hcd[bus->hcd.hcd_id].port_pe = 1;
        bus->hcd.roothub.int_buffer[0] = (1 << 1);
        usbh_hub_thread_wakeup(&bus->hcd.roothub);
    }

    if (is & USB_IS_DISCON) {
        g_musb_hcd[bus->hcd.hcd_id].port_csc = 1;
        g_musb_hcd[bus->hcd.hcd_id].port_pec = 1;
        g_musb_hcd[bus->hcd.hcd_id].port_pe = 0;
        bus->hcd.roothub.int_buffer[0] = (1 << 1);
        usbh_hub_thread_wakeup(&bus->hcd.roothub);
    }

    if (is & USB_IS_SOF) {
    }

    if (is & USB_IS_RESUME) {
    }

    if (is & USB_IS_SUSPEND) {
    }

    if (is & USB_IS_VBUSERR) {
    }

    if (is & USB_IS_SESREQ) {
    }

    if (is & USB_IS_BABBLE) {
    }

    txis &= HWREGH(USB_BASE + MUSB_TXIE_OFFSET);
    /* Handle EP0 interrupt */
    if (txis & USB_TXIE_EP0) {
        txis &= ~USB_TXIE_EP0;
        HWREGH(USB_BASE + MUSB_TXIS_OFFSET) = USB_TXIE_EP0;
        handle_ep0(bus);
    }

    for (ep_idx = 1; ep_idx < CONIFG_USB_MUSB_PIPE_NUM; ep_idx++) {
        if (txis & (1 << ep_idx)) {
            HWREGH(USB_BASE + MUSB_TXIS_OFFSET) = (1 << ep_idx);

            pipe = &g_musb_hcd[bus->hcd.hcd_id].pipe_pool[ep_idx];
            urb = pipe->urb;
            musb_set_active_ep(bus, ep_idx);

            ep_csrl_status = HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET);

            if (ep_csrl_status & USB_TXCSRL1_ERROR) {
                HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) &= ~USB_TXCSRL1_ERROR;
                urb->errorcode = -USB_ERR_IO;
                musb_urb_waitup(urb);
            } else if (ep_csrl_status & USB_TXCSRL1_NAKTO) {
                HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) &= ~USB_TXCSRL1_NAKTO;
                urb->errorcode = -USB_ERR_NAK;
                musb_urb_waitup(urb);
            } else if (ep_csrl_status & USB_TXCSRL1_STALL) {
                HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) &= ~USB_TXCSRL1_STALL;
                urb->errorcode = -USB_ERR_STALL;
                musb_urb_waitup(urb);
            } else {
                uint32_t size = urb->transfer_buffer_length;

                if (size > USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize)) {
                    size = USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize);
                }

                urb->transfer_buffer += size;
                urb->transfer_buffer_length -= size;
                urb->actual_length += size;

                if (urb->transfer_buffer_length == 0) {
                    //HWREGH(USB_BASE + MUSB_TXIE_OFFSET) &= ~(1 << ep_idx);
                    urb->errorcode = 0;
                    musb_urb_waitup(urb);
                } else {
                    musb_write_packet(bus, ep_idx, urb->transfer_buffer, size);
                    HWREGB(USB_BASE + MUSB_IND_TXCSRL_OFFSET) = USB_TXCSRL1_TXRDY;
                }
            }
        }
    }

    rxis &= HWREGH(USB_BASE + MUSB_RXIE_OFFSET);
    for (ep_idx = 1; ep_idx < CONIFG_USB_MUSB_PIPE_NUM; ep_idx++) {
        if (rxis & (1 << ep_idx)) {
            HWREGH(USB_BASE + MUSB_RXIS_OFFSET) = (1 << ep_idx); // clear isr flag

            pipe = &g_musb_hcd[bus->hcd.hcd_id].pipe_pool[ep_idx];
            urb = pipe->urb;
            musb_set_active_ep(bus, ep_idx);

            ep_csrl_status = HWREGB(USB_BASE + MUSB_IND_RXCSRL_OFFSET);
            //ep_csrh_status = HWREGB(USB_BASE + MUSB_IND_RXCSRH_OFFSET); // todo:for iso transfer

            if (ep_csrl_status & USB_RXCSRL1_ERROR) {
                HWREGB(USB_BASE + MUSB_IND_RXCSRL_OFFSET) &= ~USB_RXCSRL1_ERROR;
                urb->errorcode = -USB_ERR_IO;
                musb_urb_waitup(urb);
            } else if (ep_csrl_status & USB_RXCSRL1_NAKTO) {
                HWREGB(USB_BASE + MUSB_IND_RXCSRL_OFFSET) &= ~USB_RXCSRL1_NAKTO;
                urb->errorcode = -USB_ERR_NAK;
                musb_urb_waitup(urb);
            } else if (ep_csrl_status & USB_RXCSRL1_STALL) {
                HWREGB(USB_BASE + MUSB_IND_RXCSRL_OFFSET) &= ~USB_RXCSRL1_STALL;
                urb->errorcode = -USB_ERR_STALL;
                musb_urb_waitup(urb);
            } else if (ep_csrl_status & USB_RXCSRL1_RXRDY) {
                uint32_t size = urb->transfer_buffer_length;
                if (size > USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize)) {
                    size = USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize);
                }
                size = MIN(size, HWREGH(USB_BASE + MUSB_IND_RXCOUNT_OFFSET));

                musb_read_packet(bus, ep_idx, urb->transfer_buffer, size);

                HWREGB(USB_BASE + MUSB_IND_RXCSRL_OFFSET) &= ~USB_RXCSRL1_RXRDY;

                urb->transfer_buffer += size;
                urb->transfer_buffer_length -= size;
                urb->actual_length += size;

                if ((size < USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize)) || (urb->transfer_buffer_length == 0)) {
                    //HWREGH(USB_BASE + MUSB_RXIE_OFFSET) &= ~(1 << ep_idx);
                    urb->errorcode = 0;
                    musb_urb_waitup(urb);
                } else {
                    HWREGB(USB_BASE + MUSB_IND_RXCSRL_OFFSET) = USB_RXCSRL1_REQPKT;
                }
            }
        }
    }
    musb_set_active_ep(bus, old_ep_idx);
}
