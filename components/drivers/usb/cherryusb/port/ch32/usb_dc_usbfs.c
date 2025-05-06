/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usb_ch32_usbfs_reg.h"

#ifdef CONFIG_USB_HS
#error "usb fs do not support hs"
#endif

#ifndef USBD_IRQHandler
#define USBD_IRQHandler OTG_FS_IRQHandler //use actual usb irq name instead
#endif

#ifndef USB_NUM_BIDIR_ENDPOINTS
#define USB_NUM_BIDIR_ENDPOINTS 8
#endif

#define USB_SET_DMA(ep_idx, addr)    (*(volatile uint32_t *)((uint32_t)(&USBFS_DEVICE->UEP0_DMA) + 4 * ep_idx) = addr)
#define USB_SET_TX_LEN(ep_idx, len)  (*(volatile uint16_t *)((uint32_t)(&USBFS_DEVICE->UEP0_TX_LEN) + 4 * ep_idx) = len)
#define USB_GET_TX_LEN(ep_idx)       (*(volatile uint16_t *)((uint32_t)(&USBFS_DEVICE->UEP0_TX_LEN) + 4 * ep_idx))
#define USB_SET_TX_CTRL(ep_idx, val) (*(volatile uint8_t *)((uint32_t)(&USBFS_DEVICE->UEP0_TX_CTRL) + 4 * ep_idx) = val)
#define USB_GET_TX_CTRL(ep_idx)      (*(volatile uint8_t *)((uint32_t)(&USBFS_DEVICE->UEP0_TX_CTRL) + 4 * ep_idx))
#define USB_SET_RX_CTRL(ep_idx, val) (*(volatile uint8_t *)((uint32_t)(&USBFS_DEVICE->UEP0_RX_CTRL) + 4 * ep_idx) = val)
#define USB_GET_RX_CTRL(ep_idx)      (*(volatile uint8_t *)((uint32_t)(&USBFS_DEVICE->UEP0_RX_CTRL) + 4 * ep_idx))

/* Endpoint state */
struct ch32_usbfs_ep_state {
    uint16_t ep_mps;    /* Endpoint max packet size */
    uint8_t ep_type;    /* Endpoint type */
    uint8_t ep_stalled; /* Endpoint stall flag */
    uint8_t ep_enable;  /* Endpoint enable */
    uint8_t *xfer_buf;
    uint32_t xfer_len;
    uint32_t actual_xfer_len;
};

/* Driver state */
struct ch32_usbfs_udc {
    __attribute__((aligned(4))) struct usb_setup_packet setup;
    volatile uint8_t dev_addr;
    struct ch32_usbfs_ep_state in_ep[USB_NUM_BIDIR_ENDPOINTS];                            /*!< IN endpoint parameters*/
    struct ch32_usbfs_ep_state out_ep[USB_NUM_BIDIR_ENDPOINTS];                           /*!< OUT endpoint parameters */
    __attribute__((aligned(4))) uint8_t ep_databuf[USB_NUM_BIDIR_ENDPOINTS - 1][64 + 64]; //epx_out(64)+epx_in(64)
} g_ch32_usbfs_udc;

volatile bool ep0_rx_data_toggle;
volatile bool ep0_tx_data_toggle;

void USBD_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

__WEAK void usb_dc_low_level_init(void)
{
}

__WEAK void usb_dc_low_level_deinit(void)
{
}

int usb_dc_init(uint8_t busid)
{
    usb_dc_low_level_init();

    USBFS_DEVICE->BASE_CTRL = 0x00;

    USBFS_DEVICE->UEP4_1_MOD = USBFS_UEP4_RX_EN | USBFS_UEP4_TX_EN | USBFS_UEP1_RX_EN | USBFS_UEP1_TX_EN;
    USBFS_DEVICE->UEP2_3_MOD = USBFS_UEP2_RX_EN | USBFS_UEP2_TX_EN | USBFS_UEP3_RX_EN | USBFS_UEP3_TX_EN;
    USBFS_DEVICE->UEP5_6_MOD = USBFS_UEP5_RX_EN | USBFS_UEP5_TX_EN | USBFS_UEP6_RX_EN | USBFS_UEP6_TX_EN;
    USBFS_DEVICE->UEP7_MOD = USBFS_UEP7_RX_EN | USBFS_UEP7_TX_EN;

    USBFS_DEVICE->UEP1_DMA = (uint32_t)g_ch32_usbfs_udc.ep_databuf[0];
    USBFS_DEVICE->UEP2_DMA = (uint32_t)g_ch32_usbfs_udc.ep_databuf[1];
    USBFS_DEVICE->UEP3_DMA = (uint32_t)g_ch32_usbfs_udc.ep_databuf[2];
    USBFS_DEVICE->UEP4_DMA = (uint32_t)g_ch32_usbfs_udc.ep_databuf[3];
    USBFS_DEVICE->UEP5_DMA = (uint32_t)g_ch32_usbfs_udc.ep_databuf[4];
    USBFS_DEVICE->UEP6_DMA = (uint32_t)g_ch32_usbfs_udc.ep_databuf[5];
    USBFS_DEVICE->UEP7_DMA = (uint32_t)g_ch32_usbfs_udc.ep_databuf[6];

    USBFS_DEVICE->INT_FG = 0xFF;
    USBFS_DEVICE->INT_EN = USBFS_UIE_SUSPEND | USBFS_UIE_BUS_RST | USBFS_UIE_TRANSFER;
    USBFS_DEVICE->DEV_ADDR = 0x00;

    USBFS_DEVICE->BASE_CTRL = USBFS_UC_DEV_PU_EN | USBFS_UC_INT_BUSY | USBFS_UC_DMA_EN;
    USBFS_DEVICE->UDEV_CTRL = USBFS_UD_PD_DIS | USBFS_UD_PORT_EN;
    return 0;
}

int usb_dc_deinit(uint8_t busid)
{
    return 0;
}

int usbd_set_address(uint8_t busid, const uint8_t addr)
{
    if (addr == 0) {
        USBFS_DEVICE->DEV_ADDR = (USBFS_DEVICE->DEV_ADDR & USBFS_UDA_GP_BIT) | 0;
    }
    g_ch32_usbfs_udc.dev_addr = addr;
    return 0;
}

int usbd_set_remote_wakeup(uint8_t busid)
{
    return -1;
}

uint8_t usbd_get_port_speed(uint8_t busid)
{
    return USB_SPEED_FULL;
}

int usbd_ep_open(uint8_t busid, const struct usb_endpoint_descriptor *ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep->bEndpointAddress);

    if (USB_EP_DIR_IS_OUT(ep->bEndpointAddress)) {
        g_ch32_usbfs_udc.out_ep[ep_idx].ep_mps = USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize);
        g_ch32_usbfs_udc.out_ep[ep_idx].ep_type = USB_GET_ENDPOINT_TYPE(ep->bmAttributes);
        g_ch32_usbfs_udc.out_ep[ep_idx].ep_enable = true;
        USB_SET_RX_CTRL(ep_idx, USBFS_UEP_R_RES_NAK | USBFS_UEP_AUTO_TOG);
    } else {
        g_ch32_usbfs_udc.in_ep[ep_idx].ep_mps = USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize);
        g_ch32_usbfs_udc.in_ep[ep_idx].ep_type = USB_GET_ENDPOINT_TYPE(ep->bmAttributes);
        g_ch32_usbfs_udc.in_ep[ep_idx].ep_enable = true;
        USB_SET_TX_CTRL(ep_idx, USBFS_UEP_T_RES_NAK | USBFS_UEP_AUTO_TOG);
    }
    return 0;
}
int usbd_ep_close(uint8_t busid, const uint8_t ep)
{
    return 0;
}
int usbd_ep_set_stall(uint8_t busid, const uint8_t ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (USB_EP_DIR_IS_OUT(ep)) {
        if (ep_idx == 0) {
            USBFS_DEVICE->UEP0_RX_CTRL = USBFS_UEP_R_TOG | USBFS_UEP_R_RES_STALL;
        } else {
            USB_SET_RX_CTRL(ep_idx, (USB_GET_RX_CTRL(ep_idx) & ~USBFS_UEP_R_RES_MASK) | USBFS_UEP_R_RES_STALL);
        }
    } else {
        if (ep_idx == 0) {
            USBFS_DEVICE->UEP0_TX_CTRL = USBFS_UEP_T_TOG | USBFS_UEP_T_RES_STALL;
        } else {
            USB_SET_TX_CTRL(ep_idx, (USB_GET_TX_CTRL(ep_idx) & ~USBFS_UEP_T_RES_MASK) | USBFS_UEP_T_RES_STALL);
        }
    }

    if (ep_idx == 0) {
        USB_SET_DMA(ep_idx, (uint32_t)&g_ch32_usbfs_udc.setup);
        USB_SET_RX_CTRL(ep_idx, USBFS_UEP_R_RES_ACK);
    }
    return 0;
}

int usbd_ep_clear_stall(uint8_t busid, const uint8_t ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (ep_idx == 0) {
        return 0;
    }

    if (USB_EP_DIR_IS_OUT(ep)) {
        USB_SET_RX_CTRL(ep_idx, (USB_GET_RX_CTRL(ep_idx) & ~(USBFS_UEP_R_TOG | USBFS_UEP_R_RES_MASK)) | USBFS_UEP_R_RES_ACK);
    } else {
        USB_SET_TX_CTRL(ep_idx, (USB_GET_TX_CTRL(ep_idx) & ~(USBFS_UEP_T_TOG | USBFS_UEP_T_RES_MASK)) | USBFS_UEP_T_RES_NAK);
    }
    return 0;
}

int usbd_ep_is_stalled(uint8_t busid, const uint8_t ep, uint8_t *stalled)
{
    return 0;
}

int usbd_ep_start_write(uint8_t busid, const uint8_t ep, const uint8_t *data, uint32_t data_len)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (!data && data_len) {
        return -1;
    }
    if (!g_ch32_usbfs_udc.in_ep[ep_idx].ep_enable) {
        return -2;
    }

    if ((uint32_t)data & 0x03) {
        printf("data do not align4\r\n");
        return -3;
    }

    g_ch32_usbfs_udc.in_ep[ep_idx].xfer_buf = (uint8_t *)data;
    g_ch32_usbfs_udc.in_ep[ep_idx].xfer_len = data_len;
    g_ch32_usbfs_udc.in_ep[ep_idx].actual_xfer_len = 0;

    if (ep_idx == 0) {
        if (data_len == 0) {
            USB_SET_TX_LEN(ep_idx, 0);
        } else {
            data_len = MIN(data_len, g_ch32_usbfs_udc.in_ep[ep_idx].ep_mps);
            USB_SET_TX_LEN(ep_idx, data_len);
            USB_SET_DMA(ep_idx, (uint32_t)data);
        }
        if (ep0_tx_data_toggle) {
            USB_SET_TX_CTRL(ep_idx, USBFS_UEP_T_TOG | USBFS_UEP_T_RES_ACK);
        } else {
            USB_SET_TX_CTRL(ep_idx, USBFS_UEP_T_RES_ACK);
        }

    } else {
        if (data_len == 0) {
            USB_SET_TX_LEN(ep_idx, 0);
        } else {
            data_len = MIN(data_len, g_ch32_usbfs_udc.in_ep[ep_idx].ep_mps);
            USB_SET_TX_LEN(ep_idx, data_len);
            memcpy(&g_ch32_usbfs_udc.ep_databuf[ep_idx - 1][64], data, data_len);
        }
        USB_SET_TX_CTRL(ep_idx, (USB_GET_TX_CTRL(ep_idx) & ~USBFS_UEP_T_RES_MASK) | USBFS_UEP_T_RES_ACK);
    }
    return 0;
}

int usbd_ep_start_read(uint8_t busid, const uint8_t ep, uint8_t *data, uint32_t data_len)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (!data && data_len) {
        return -1;
    }
    if (!g_ch32_usbfs_udc.out_ep[ep_idx].ep_enable) {
        return -2;
    }
    if ((uint32_t)data & 0x03) {
        printf("data do not align4\r\n");
        return -3;
    }

    g_ch32_usbfs_udc.out_ep[ep_idx].xfer_buf = (uint8_t *)data;
    g_ch32_usbfs_udc.out_ep[ep_idx].xfer_len = data_len;
    g_ch32_usbfs_udc.out_ep[ep_idx].actual_xfer_len = 0;

    if (ep_idx == 0) {
        if (data_len == 0) {
        } else {
            USB_SET_DMA(ep_idx, (uint32_t)data);
        }
        if (ep0_rx_data_toggle) {
            USB_SET_RX_CTRL(ep_idx, USBFS_UEP_R_TOG | USBFS_UEP_R_RES_ACK);
        } else {
            USB_SET_RX_CTRL(ep_idx, USBFS_UEP_R_RES_ACK);
        }
        return 0;
    } else {
        USB_SET_RX_CTRL(ep_idx, (USB_GET_RX_CTRL(ep_idx) & ~USBFS_UEP_R_RES_MASK) | USBFS_UEP_R_RES_ACK);
    }

    return 0;
}

void USBD_IRQHandler(void)
{
    uint32_t ep_idx = 0, token, write_count, read_count;
    uint8_t intflag = 0;

    intflag = USBFS_DEVICE->INT_FG;

    if (intflag & USBFS_UIF_TRANSFER) {
        token = USBFS_DEVICE->INT_ST & USBFS_UIS_TOKEN_MASK;
        ep_idx = USBFS_DEVICE->INT_ST & USBFS_UIS_ENDP_MASK;
        switch (token) {
            case USBFS_UIS_TOKEN_SETUP:
                USB_SET_RX_CTRL(ep_idx, USBFS_UEP_R_RES_NAK);
                usbd_event_ep0_setup_complete_handler(0, (uint8_t *)&g_ch32_usbfs_udc.setup);
                break;

            case USBFS_UIS_TOKEN_IN:
                if (ep_idx == 0x00) {
                    if (g_ch32_usbfs_udc.in_ep[ep_idx].xfer_len >= g_ch32_usbfs_udc.in_ep[ep_idx].ep_mps) {
                        g_ch32_usbfs_udc.in_ep[ep_idx].xfer_len -= g_ch32_usbfs_udc.in_ep[ep_idx].ep_mps;
                        g_ch32_usbfs_udc.in_ep[ep_idx].actual_xfer_len += g_ch32_usbfs_udc.in_ep[ep_idx].ep_mps;
                        ep0_tx_data_toggle ^= 1;
                    } else {
                        g_ch32_usbfs_udc.in_ep[ep_idx].actual_xfer_len += g_ch32_usbfs_udc.in_ep[ep_idx].xfer_len;
                        g_ch32_usbfs_udc.in_ep[ep_idx].xfer_len = 0;
                        ep0_tx_data_toggle = true;
                    }

                    usbd_event_ep_in_complete_handler(0, ep_idx | 0x80, g_ch32_usbfs_udc.in_ep[ep_idx].actual_xfer_len);

                    if (g_ch32_usbfs_udc.dev_addr > 0) {
                        USBFS_DEVICE->DEV_ADDR = (USBFS_DEVICE->DEV_ADDR & USBFS_UDA_GP_BIT) | g_ch32_usbfs_udc.dev_addr;
                        g_ch32_usbfs_udc.dev_addr = 0;
                    }

                    if (g_ch32_usbfs_udc.setup.wLength && ((g_ch32_usbfs_udc.setup.bmRequestType & USB_REQUEST_DIR_MASK) == USB_REQUEST_DIR_OUT)) {
                        /* In status, start reading setup */
                        USB_SET_DMA(ep_idx, (uint32_t)&g_ch32_usbfs_udc.setup);
                        USB_SET_RX_CTRL(ep_idx, USBFS_UEP_R_RES_ACK);
                        ep0_tx_data_toggle = true;

                    } else if (g_ch32_usbfs_udc.setup.wLength == 0) {
                        /* In status, start reading setup */
                        USB_SET_DMA(ep_idx, (uint32_t)&g_ch32_usbfs_udc.setup);
                        USB_SET_RX_CTRL(ep_idx, USBFS_UEP_R_RES_ACK);
                        ep0_tx_data_toggle = true;
                    }
                } else {
                    USB_SET_TX_CTRL(ep_idx, (USB_GET_TX_CTRL(ep_idx) & ~USBFS_UEP_T_RES_MASK) | USBFS_UEP_T_RES_NAK);

                    if (g_ch32_usbfs_udc.in_ep[ep_idx].xfer_len > g_ch32_usbfs_udc.in_ep[ep_idx].ep_mps) {
                        g_ch32_usbfs_udc.in_ep[ep_idx].xfer_buf += g_ch32_usbfs_udc.in_ep[ep_idx].ep_mps;
                        g_ch32_usbfs_udc.in_ep[ep_idx].xfer_len -= g_ch32_usbfs_udc.in_ep[ep_idx].ep_mps;
                        g_ch32_usbfs_udc.in_ep[ep_idx].actual_xfer_len += g_ch32_usbfs_udc.in_ep[ep_idx].ep_mps;

                        write_count = MIN(g_ch32_usbfs_udc.in_ep[ep_idx].xfer_len, g_ch32_usbfs_udc.in_ep[ep_idx].ep_mps);
                        USB_SET_TX_LEN(ep_idx, write_count);
                        memcpy(&g_ch32_usbfs_udc.ep_databuf[ep_idx - 1][64], g_ch32_usbfs_udc.in_ep[ep_idx].xfer_buf, write_count);

                        USB_SET_TX_CTRL(ep_idx, (USB_GET_TX_CTRL(ep_idx) & ~USBFS_UEP_T_RES_MASK) | USBFS_UEP_T_RES_ACK);
                    } else {
                        g_ch32_usbfs_udc.in_ep[ep_idx].actual_xfer_len += g_ch32_usbfs_udc.in_ep[ep_idx].xfer_len;
                        g_ch32_usbfs_udc.in_ep[ep_idx].xfer_len = 0;
                        usbd_event_ep_in_complete_handler(0, ep_idx | 0x80, g_ch32_usbfs_udc.in_ep[ep_idx].actual_xfer_len);
                    }
                }
                break;
            case USBFS_UIS_TOKEN_OUT:
                if (ep_idx == 0x00) {
                    USB_SET_RX_CTRL(ep_idx, USBFS_UEP_R_RES_NAK);

                    read_count = USBFS_DEVICE->RX_LEN;

                    g_ch32_usbfs_udc.out_ep[ep_idx].actual_xfer_len += read_count;
                    g_ch32_usbfs_udc.out_ep[ep_idx].xfer_len -= read_count;

                    usbd_event_ep_out_complete_handler(0, 0x00, g_ch32_usbfs_udc.out_ep[ep_idx].actual_xfer_len);

                    if (read_count == 0) {
                        /* Out status, start reading setup */
                        USB_SET_DMA(ep_idx, (uint32_t)&g_ch32_usbfs_udc.setup);
                        USB_SET_RX_CTRL(ep_idx, USBFS_UEP_R_RES_ACK);
                        ep0_rx_data_toggle = true;
                        ep0_tx_data_toggle = true;
                    } else {
                        ep0_rx_data_toggle ^= 1;
                    }
                } else {
                    if (USBFS_DEVICE->INT_ST & USBFS_UIS_TOG_OK) {
                        USB_SET_RX_CTRL(ep_idx, (USB_GET_RX_CTRL(ep_idx) & ~USBFS_UEP_R_RES_MASK) | USBFS_UEP_R_RES_NAK);
                        read_count = USBFS_DEVICE->RX_LEN;

                        memcpy(g_ch32_usbfs_udc.out_ep[ep_idx].xfer_buf, &g_ch32_usbfs_udc.ep_databuf[ep_idx - 1][0], read_count);

                        g_ch32_usbfs_udc.out_ep[ep_idx].xfer_buf += read_count;
                        g_ch32_usbfs_udc.out_ep[ep_idx].actual_xfer_len += read_count;
                        g_ch32_usbfs_udc.out_ep[ep_idx].xfer_len -= read_count;

                        if ((read_count < g_ch32_usbfs_udc.out_ep[ep_idx].ep_mps) || (g_ch32_usbfs_udc.out_ep[ep_idx].xfer_len == 0)) {
                            usbd_event_ep_out_complete_handler(0, ep_idx, g_ch32_usbfs_udc.out_ep[ep_idx].actual_xfer_len);
                        } else {
                            USB_SET_RX_CTRL(ep_idx, (USB_GET_RX_CTRL(ep_idx) & ~USBFS_UEP_R_RES_MASK) | USBFS_UEP_R_RES_ACK);
                        }
                    }
                }
                break;

            case USBFS_UIS_TOKEN_SOF:

                break;

            default:
                break;
        }

        USBFS_DEVICE->INT_FG = USBFS_UIF_TRANSFER;
    } else if (intflag & USBFS_UIF_BUS_RST) {
        USBFS_DEVICE->UEP0_TX_LEN = 0;
        USBFS_DEVICE->UEP0_TX_CTRL = USBFS_UEP_T_RES_NAK;
        USBFS_DEVICE->UEP0_RX_CTRL = USBFS_UEP_R_RES_NAK;

        for (uint8_t ep_idx = 1; ep_idx < USB_NUM_BIDIR_ENDPOINTS; ep_idx++) {
            USB_SET_TX_LEN(ep_idx, 0);
            USB_SET_TX_CTRL(ep_idx, USBFS_UEP_T_RES_NAK | USBFS_UEP_AUTO_TOG);
            USB_SET_RX_CTRL(ep_idx, USBFS_UEP_R_RES_NAK | USBFS_UEP_AUTO_TOG);
        }

        ep0_tx_data_toggle = true;
        ep0_rx_data_toggle = true;

        memset(&g_ch32_usbfs_udc, 0, sizeof(struct ch32_usbfs_udc));
        usbd_event_reset_handler(0);
        USB_SET_DMA(ep_idx, (uint32_t)&g_ch32_usbfs_udc.setup);
        USB_SET_RX_CTRL(ep_idx, USBFS_UEP_R_RES_ACK);

        USBFS_DEVICE->INT_FG |= USBFS_UIF_BUS_RST;
    } else if (intflag & USBFS_UIF_SUSPEND) {
        if (USBFS_DEVICE->MIS_ST & USBFS_UMS_SUSPEND) {
        } else {
        }
        USBFS_DEVICE->INT_FG = USBFS_UIF_SUSPEND;
    } else {
        USBFS_DEVICE->INT_FG = intflag;
    }
}
