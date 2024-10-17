/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usb_kinetis_reg.h"

#define USB_OTG_DEV ((KINETIS_TypeDef *)g_usbdev_bus[busid].reg_base)

/* Endpoint state */
struct kinetis_ep_state {
    uint16_t ep_mps;    /* Endpoint max packet size */
    uint8_t ep_type;    /* Endpoint type */
    uint8_t ep_stalled; /* Endpoint stall flag */
    uint8_t ep_enable;  /* Endpoint enable */
    bool ep_odd;        /* Endpoint odd */
    uint8_t *xfer_buf;
    uint32_t xfer_len;
    uint32_t actual_xfer_len;
};

/* Driver state */
struct kinetis_udc {
    uint8_t dev_addr;
    struct kinetis_ep_state in_ep[CONFIG_USBDEV_EP_NUM];  /*!< IN endpoint parameters*/
    struct kinetis_ep_state out_ep[CONFIG_USBDEV_EP_NUM]; /*!< OUT endpoint parameters */
} g_kinetis_udc[CONFIG_USBDEV_MAX_BUS];

USB_NOCACHE_RAM_SECTION __attribute__((aligned(512))) kinetis_bd_table_t g_kinetis_bdt[CONFIG_USBDEV_MAX_BUS];
USB_NOCACHE_RAM_SECTION __attribute__((aligned(32))) uint8_t setup_packet[CONFIG_USBDEV_MAX_BUS][8];

static int kinetis_start_transfer(uint8_t busid, uint8_t ep, uint8_t *buffer, uint16_t buflen)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);
    uint8_t dir;
    uint8_t odd;
    uint16_t ep_mps;
    kinetis_bd_t *bd;
    kinetis_bd_t *next;

    if (USB_EP_DIR_IS_OUT(ep)) {
        dir = 0;
        odd = g_kinetis_udc[busid].out_ep[ep_idx].ep_odd;
        ep_mps = g_kinetis_udc[busid].out_ep[ep_idx].ep_mps;
    } else {
        dir = 1;
        odd = g_kinetis_udc[busid].in_ep[ep_idx].ep_odd;
        ep_mps = g_kinetis_udc[busid].in_ep[ep_idx].ep_mps;
    }

    bd = &g_kinetis_bdt[busid].table[ep_idx][dir][odd];

    if (bd->own) {
        USB_LOG_INFO("ep%02x is busy\r\n", ep);
        return -1;
    }

    bd->bc = buflen >= ep_mps ? ep_mps : buflen;
    bd->addr = (uint32_t)buffer;
    bd->own = 1;
    return 0;
}

static void kinetis_read_setup(uint8_t busid)
{
    uint8_t out_odd = g_kinetis_udc[busid].out_ep[0].ep_odd;
    uint8_t in_odd = g_kinetis_udc[busid].in_ep[0].ep_odd;

    if (g_kinetis_bdt[busid].table[0][0][out_odd].own) {
        USB_LOG_INFO("ep0 is busy\r\n");
        return;
    }

    g_kinetis_bdt[busid].table[0][0][out_odd].data = 0;
    g_kinetis_bdt[busid].table[0][0][out_odd ^ 1].data = 1;
    g_kinetis_bdt[busid].table[0][1][in_odd].data = 1;
    g_kinetis_bdt[busid].table[0][1][in_odd ^ 1].data = 0;

    kinetis_start_transfer(busid, USB_CONTROL_OUT_EP0, setup_packet[busid], 8);
}

__WEAK void usb_dc_low_level_init(uint8_t busid)
{
}

__WEAK void usb_dc_low_level_deinit(uint8_t busid)
{
}

int usb_dc_init(uint8_t busid)
{
    usb_dc_low_level_init(busid);

    memset(&g_kinetis_udc[busid], 0, sizeof(g_kinetis_udc[busid]));

    USB_OTG_DEV->BDTPAGE1 = (uint8_t)((uintptr_t)&g_kinetis_bdt[busid] >> 8);
    USB_OTG_DEV->BDTPAGE2 = (uint8_t)((uintptr_t)&g_kinetis_bdt[busid] >> 16);
    USB_OTG_DEV->BDTPAGE3 = (uint8_t)((uintptr_t)&g_kinetis_bdt[busid] >> 24);

    USB_OTG_DEV->INTEN = USB_INTEN_USBRSTEN_MASK | USB_INTEN_TOKDNEEN_MASK |
                         USB_INTEN_SLEEPEN_MASK | USB_INTEN_RESUMEEN_MASK |
                         USB_INTEN_ERROREN_MASK;

    USB_OTG_DEV->CTL |= USB_CTL_USBENSOFEN_MASK;
    return 0;
}

int usb_dc_deinit(uint8_t busid)
{
    usb_dc_low_level_deinit(busid);
    return 0;
}

int usbd_set_address(uint8_t busid, const uint8_t addr)
{
    g_kinetis_udc[busid].dev_addr = addr;

    if (addr == 0) {
        USB_OTG_DEV->ADDR = 0;
    }
    return 0;
}

int usbd_set_remote_wakeup(uint8_t busid)
{
    USB_OTG_DEV->CTL |= USB_CTL_RESUME_MASK;

    usbd_kinetis_delay_ms(10);

    USB_OTG_DEV->CTL &= ~USB_CTL_RESUME_MASK;

    return 0;
}

uint8_t usbd_get_port_speed(uint8_t busid)
{
    return USB_SPEED_FULL;
}

int usbd_ep_open(uint8_t busid, const struct usb_endpoint_descriptor *ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep->bEndpointAddress);
    uint8_t odd;
    uint8_t dir;
    kinetis_bd_t *bd;
    uint8_t regval;

    /* Must not exceed max endpoint number */
    if (ep_idx >= CONFIG_USBDEV_EP_NUM) {
        return -1;
    }

    if (USB_EP_DIR_IS_OUT(ep->bEndpointAddress)) {
        g_kinetis_udc[busid].out_ep[ep_idx].ep_mps = USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize);
        g_kinetis_udc[busid].out_ep[ep_idx].ep_type = USB_GET_ENDPOINT_TYPE(ep->bmAttributes);
        g_kinetis_udc[busid].out_ep[ep_idx].ep_enable = true;

        dir = 0;
        odd = g_kinetis_udc[busid].out_ep[ep_idx].ep_odd;
    } else {
        g_kinetis_udc[busid].in_ep[ep_idx].ep_mps = USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize);
        g_kinetis_udc[busid].in_ep[ep_idx].ep_type = USB_GET_ENDPOINT_TYPE(ep->bmAttributes);
        g_kinetis_udc[busid].in_ep[ep_idx].ep_enable = true;

        dir = 1;
        odd = g_kinetis_udc[busid].in_ep[ep_idx].ep_odd;
    }

    if (ep_idx != 0) {
        regval = USB_ENDPT_EPCTLDIS_MASK;
        regval |= (USB_GET_ENDPOINT_TYPE(ep->bmAttributes) != USB_ENDPOINT_TYPE_ISOCHRONOUS) ? USB_ENDPT_EPHSHK_MASK : 0;
        regval |= dir ? USB_ENDPT_EPTXEN_MASK : USB_ENDPT_EPRXEN_MASK;
        USB_OTG_DEV->ENDPOINT[ep_idx].ENDPT |= regval;

        if (USB_GET_ENDPOINT_TYPE(ep->bmAttributes) != USB_ENDPOINT_TYPE_ISOCHRONOUS) {
            bd = &g_kinetis_bdt[busid].table[ep_idx][dir][odd];
            bd->dts = 1;
            bd->data = 0;

            bd = &g_kinetis_bdt[busid].table[ep_idx][dir][odd ^ 1];
            bd->dts = 1;
            bd->data = 1;
        }
    }

    return 0;
}

int usbd_ep_close(uint8_t busid, const uint8_t ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);
    uint8_t dir;
    kinetis_bd_t *bd;

    if (USB_EP_DIR_IS_OUT(ep)) {
        g_kinetis_udc[busid].out_ep[ep_idx].ep_enable = false;
        dir = 0;
    } else {
        g_kinetis_udc[busid].in_ep[ep_idx].ep_enable = false;
        dir = 1;
    }

    bd = &g_kinetis_bdt[busid].table[ep_idx][dir][0];
    bd->head = 0;

    bd = &g_kinetis_bdt[busid].table[ep_idx][dir][1];
    bd->head = 0;

    USB_OTG_DEV->ENDPOINT[ep_idx].ENDPT &= ~(dir ? USB_ENDPT_EPTXEN_MASK : USB_ENDPT_EPRXEN_MASK);
    return 0;
}

int usbd_ep_set_stall(uint8_t busid, const uint8_t ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);
    kinetis_bd_t *bd;
    uint8_t odd;
    uint8_t dir;

    if (0 == ep_idx) {
        USB_OTG_DEV->ENDPOINT[ep_idx].ENDPT |= USB_ENDPT_EPSTALL_MASK;

        if (ep_idx == 0) {
            kinetis_read_setup(busid);
        }
    } else {
        if (USB_EP_DIR_IS_OUT(ep)) {
            dir = 0;
            odd = g_kinetis_udc[busid].out_ep[ep_idx].ep_odd;
        } else {
            dir = 1;
            odd = g_kinetis_udc[busid].in_ep[ep_idx].ep_odd;
        }

        bd = &g_kinetis_bdt[busid].table[ep_idx][dir][odd];

        bd->bdt_stall = 1;
        bd->own = 1;
    }
    return 0;
}

int usbd_ep_clear_stall(uint8_t busid, const uint8_t ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);
    kinetis_bd_t *bd;
    uint8_t odd;
    uint8_t dir;

    if (USB_EP_DIR_IS_OUT(ep)) {
        dir = 0;
        odd = g_kinetis_udc[busid].out_ep[ep_idx].ep_odd;
    } else {
        dir = 1;
        odd = g_kinetis_udc[busid].in_ep[ep_idx].ep_odd;
    }

    bd = &g_kinetis_bdt[busid].table[ep_idx][dir][odd];

    bd->own = 0;
    bd->bdt_stall = 0;
    bd->data = 0;

    bd = &g_kinetis_bdt[busid].table[ep_idx][dir][odd ^ 1];
    bd->data = 1;

    uint8_t regval = USB_OTG_DEV->ENDPOINT[ep_idx].ENDPT;
    if (regval & USB_ENDPT_EPSTALL_MASK) {
        USB_OTG_DEV->ENDPOINT[ep_idx].ENDPT = regval & ~USB_ENDPT_EPSTALL_MASK;
    }

    return 0;
}

int usbd_ep_is_stalled(uint8_t busid, const uint8_t ep, uint8_t *stalled)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    uint8_t regval = USB_OTG_DEV->ENDPOINT[ep_idx].ENDPT;
    if (regval & USB_ENDPT_EPSTALL_MASK) {
        *stalled = 1;
    } else {
        *stalled = 0;
    }

    return 0;
}

int usbd_ep_start_write(uint8_t busid, const uint8_t ep, const uint8_t *data,
                        uint32_t data_len)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (!data && data_len) {
        return -1;
    }
    if (!g_kinetis_udc[busid].in_ep[ep_idx].ep_enable) {
        return -2;
    }

    g_kinetis_udc[busid].in_ep[ep_idx].xfer_buf = (uint8_t *)data;
    g_kinetis_udc[busid].in_ep[ep_idx].xfer_len = data_len;
    g_kinetis_udc[busid].in_ep[ep_idx].actual_xfer_len = 0;

    return kinetis_start_transfer(busid, ep, (uint8_t *)data, MIN(data_len, g_kinetis_udc[busid].in_ep[ep_idx].ep_mps));
}

int usbd_ep_start_read(uint8_t busid, const uint8_t ep, uint8_t *data,
                       uint32_t data_len)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (!data && data_len) {
        return -1;
    }
    if (!g_kinetis_udc[busid].out_ep[ep_idx].ep_enable) {
        return -2;
    }

    g_kinetis_udc[busid].out_ep[ep_idx].xfer_buf = (uint8_t *)data;
    g_kinetis_udc[busid].out_ep[ep_idx].xfer_len = data_len;
    g_kinetis_udc[busid].out_ep[ep_idx].actual_xfer_len = 0;

    return kinetis_start_transfer(busid, ep, (uint8_t *)data, MIN(data_len, g_kinetis_udc[busid].out_ep[ep_idx].ep_mps));
}

void USBD_IRQHandler(uint8_t busid)
{
    uint8_t s;
    uint8_t pid;
    uint8_t ep_idx;
    uint8_t dir;
    uint8_t odd;
    uint16_t bc;
    uint8_t is = USB_OTG_DEV->ISTAT;
    uint8_t mask = USB_OTG_DEV->INTEN;
    kinetis_bd_t *bd;

    USB_OTG_DEV->ISTAT = is & ~mask;
    is &= mask;

    if (is & USB_ISTAT_ERROR_MASK) {
        uint32_t es = USB_OTG_DEV->ERRSTAT;
        USB_OTG_DEV->ERRSTAT = es;
        USB_OTG_DEV->ISTAT = is;
    }

    if (is & USB_ISTAT_USBRST_MASK) {
        USB_OTG_DEV->ISTAT = is;
        USB_OTG_DEV->CTL |= USB_CTL_ODDRST_MASK;
        USB_OTG_DEV->ADDR = 0;

        USB_OTG_DEV->ENDPOINT[0].ENDPT = USB_ENDPT_EPHSHK_MASK | USB_ENDPT_EPRXEN_MASK | USB_ENDPT_EPTXEN_MASK;
        for (uint8_t i = 1; i < 16; i++) {
            USB_OTG_DEV->ENDPOINT[i].ENDPT = 0;
        }

        memset(&g_kinetis_bdt[busid], 0, sizeof(g_kinetis_bdt[busid]));
        memset(g_kinetis_udc[busid].in_ep, 0, sizeof(struct kinetis_ep_state) * CONFIG_USBDEV_EP_NUM);
        memset(g_kinetis_udc[busid].out_ep, 0, sizeof(struct kinetis_ep_state) * CONFIG_USBDEV_EP_NUM);
        usbd_event_reset_handler(busid);

        kinetis_read_setup(busid);

        USB_OTG_DEV->CTL &= ~USB_CTL_ODDRST_MASK;
    }

    if (is & USB_ISTAT_SLEEP_MASK) {
        USB_OTG_DEV->ISTAT = USB_ISTAT_SLEEP_MASK;
    }

    if (is & USB_ISTAT_RESUME_MASK) {
        USB_OTG_DEV->ISTAT = USB_ISTAT_RESUME_MASK;
    }

    if (is & USB_ISTAT_SOFTOK_MASK) {
        USB_OTG_DEV->ISTAT = USB_ISTAT_SOFTOK_MASK;
    }

    if (is & USB_ISTAT_STALL_MASK) {
        USB_OTG_DEV->ISTAT = USB_ISTAT_STALL_MASK;
    }

    if (is & USB_ISTAT_TOKDNE_MASK) {
        s = USB_OTG_DEV->STAT;
        USB_OTG_DEV->ISTAT = USB_ISTAT_TOKDNE_MASK; /* must be cleared after get STAT */

        ep_idx = (s & USB_STAT_ENDP_MASK) >> USB_STAT_ENDP_SHIFT;
        dir = (s & USB_STAT_TX_MASK) >> USB_STAT_TX_SHIFT;
        odd = (s & USB_STAT_ODD_MASK) >> USB_STAT_ODD_SHIFT;

        bd = &g_kinetis_bdt[busid].table[ep_idx][dir][odd];

        pid = bd->tok_pid;
        bc = bd->bc;

        bd->bdt_stall = 0;
        bd->dts = 1;
        bd->ninc = 0;
        bd->keep = 0;

        if (dir) {
            g_kinetis_udc[busid].in_ep[ep_idx].ep_odd = odd ^ 1;
        } else {
            g_kinetis_udc[busid].out_ep[ep_idx].ep_odd = odd ^ 1;
        }

        if (pid == USB_TOKEN_PID_SETUP) {
            USB_OTG_DEV->CTL &= ~USB_CTL_TXSUSPENDTOKENBUSY_MASK;
            usbd_event_ep0_setup_complete_handler(busid, (uint8_t *)bd->addr);
            return;
        }

        if (dir) {
            g_kinetis_udc[busid].in_ep[ep_idx].xfer_buf += bc;
            g_kinetis_udc[busid].in_ep[ep_idx].xfer_len -= bc;
            g_kinetis_udc[busid].in_ep[ep_idx].actual_xfer_len += bc;

            if (g_kinetis_udc[busid].in_ep[ep_idx].xfer_len == 0) {
                usbd_event_ep_in_complete_handler(busid, ep_idx | 0x80, g_kinetis_udc[busid].in_ep[ep_idx].actual_xfer_len);
            } else {
                kinetis_start_transfer(busid, ep_idx | 0x80, g_kinetis_udc[busid].in_ep[ep_idx].xfer_buf,
                                           MIN(g_kinetis_udc[busid].in_ep[ep_idx].xfer_len, g_kinetis_udc[busid].in_ep[ep_idx].ep_mps));
            }
        } else {
            g_kinetis_udc[busid].out_ep[ep_idx].xfer_buf += bc;
            g_kinetis_udc[busid].out_ep[ep_idx].xfer_len -= bc;
            g_kinetis_udc[busid].out_ep[ep_idx].actual_xfer_len += bc;

            if ((bc < g_kinetis_udc[busid].out_ep[ep_idx].ep_mps) || (g_kinetis_udc[busid].out_ep[ep_idx].xfer_len == 0)) {
                usbd_event_ep_out_complete_handler(busid, ep_idx, g_kinetis_udc[busid].out_ep[ep_idx].actual_xfer_len);
            } else {
                kinetis_start_transfer(busid, ep_idx, g_kinetis_udc[busid].out_ep[ep_idx].xfer_buf,
                                           MIN(g_kinetis_udc[busid].out_ep[ep_idx].xfer_len, g_kinetis_udc[busid].out_ep[ep_idx].ep_mps));
            }
        }

        if ((bc == 0) && (ep_idx == 0)) {
            if ((g_kinetis_udc[busid].dev_addr > 0) && dir) {
                USB_OTG_DEV->ADDR = g_kinetis_udc[busid].dev_addr;
                g_kinetis_udc[busid].dev_addr = 0;
            }

            kinetis_read_setup(busid);
        }
    }
}