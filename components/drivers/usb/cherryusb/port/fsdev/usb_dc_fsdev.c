/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"

#ifndef CONFIG_USBDEV_FSDEV_PMA_ACCESS
#error "please define CONFIG_USBDEV_FSDEV_PMA_ACCESS in usb_config.h"
#endif

#define PMA_ACCESS CONFIG_USBDEV_FSDEV_PMA_ACCESS
#include "usb_fsdev_reg.h"

#ifndef CONFIG_USB_FSDEV_RAM_SIZE
#define CONFIG_USB_FSDEV_RAM_SIZE 512
#endif

#ifndef CONFIG_USBDEV_EP_NUM
#define CONFIG_USBDEV_EP_NUM 8
#endif

#define USB ((USB_TypeDef *)g_usbdev_bus[0].reg_base)

#define USB_BTABLE_SIZE (8 * CONFIG_USBDEV_EP_NUM)

static void fsdev_write_pma(USB_TypeDef *USBx, uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes);
static void fsdev_read_pma(USB_TypeDef *USBx, uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes);

/* Endpoint state */
struct fsdev_ep_state {
    uint16_t ep_mps;         /* Endpoint max packet size */
    uint8_t ep_type;         /* Endpoint type */
    uint8_t ep_stalled;      /* Endpoint stall flag */
    uint8_t ep_enable;       /* Endpoint enable */
    uint16_t ep_pma_buf_len; /* Previously allocated buffer size */
    uint16_t ep_pma_addr;    /* ep pmd allocated addr */
    uint8_t *xfer_buf;
    uint32_t xfer_len;
    uint32_t actual_xfer_len;
};

/* Driver state */
struct fsdev_udc {
    struct usb_setup_packet setup;
    volatile uint8_t dev_addr;                          /*!< USB Address */
    volatile uint32_t pma_offset;                       /*!< pma offset */
    struct fsdev_ep_state in_ep[CONFIG_USBDEV_EP_NUM];  /*!< IN endpoint parameters*/
    struct fsdev_ep_state out_ep[CONFIG_USBDEV_EP_NUM]; /*!< OUT endpoint parameters */
} g_fsdev_udc;

__WEAK void usb_dc_low_level_init(void)
{
}

__WEAK void usb_dc_low_level_deinit(void)
{
}

int usb_dc_init(uint8_t busid)
{
    usb_dc_low_level_init();

    /* Init Device */
    /* CNTR_FRES = 1 */
    USB->CNTR = (uint16_t)USB_CNTR_FRES;

    /* CNTR_FRES = 0 */
    USB->CNTR = 0U;

    /* Clear pending interrupts */
    USB->ISTR = 0U;

    /*Set Btable Address*/
    USB->BTABLE = BTABLE_ADDRESS;

    uint32_t winterruptmask;

    /* Set winterruptmask variable */
    winterruptmask = USB_CNTR_CTRM | USB_CNTR_WKUPM |
                     USB_CNTR_SUSPM | USB_CNTR_ERRM |
                     USB_CNTR_SOFM | USB_CNTR_ESOFM |
                     USB_CNTR_RESETM;

    /* Set interrupt mask */
    USB->CNTR = (uint16_t)winterruptmask;

    /* Enabling DP Pull-UP bit to Connect internal PU resistor on USB DP line */
    USB->BCDR |= (uint16_t)USB_BCDR_DPPU;

    return 0;
}

int usb_dc_deinit(uint8_t busid)
{
    /* disable all interrupts and force USB reset */
    USB->CNTR = (uint16_t)USB_CNTR_FRES;

    /* clear interrupt status register */
    USB->ISTR = 0U;

    /* switch-off device */
    USB->CNTR = (uint16_t)(USB_CNTR_FRES | USB_CNTR_PDWN);

    usb_dc_low_level_deinit();
    return 0;
}

int usbd_set_address(uint8_t busid, const uint8_t addr)
{
    if (addr == 0U) {
        /* set device address and enable function */
        USB->DADDR = (uint16_t)USB_DADDR_EF;
    }

    g_fsdev_udc.dev_addr = addr;
    return 0;
}

uint8_t usbd_get_port_speed(uint8_t busid)
{
    return USB_SPEED_FULL;
}

int usbd_ep_open(uint8_t busid, const struct usb_endpoint_descriptor *ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep->bEndpointAddress);

    if (ep_idx > (CONFIG_USBDEV_EP_NUM - 1)) {
        USB_LOG_ERR("Ep addr %02x overflow\r\n", ep->bEndpointAddress);
        return -1;
    }

    uint16_t wEpRegVal;

    /* initialize Endpoint */
    switch (USB_GET_ENDPOINT_TYPE(ep->bmAttributes)) {
        case USB_ENDPOINT_TYPE_CONTROL:
            wEpRegVal = USB_EP_CONTROL;
            break;

        case USB_ENDPOINT_TYPE_BULK:
            wEpRegVal = USB_EP_BULK;
            break;

        case USB_ENDPOINT_TYPE_INTERRUPT:
            wEpRegVal = USB_EP_INTERRUPT;
            break;

        case USB_ENDPOINT_TYPE_ISOCHRONOUS:
            wEpRegVal = USB_EP_ISOCHRONOUS;
            break;

        default:
            break;
    }

    PCD_SET_EPTYPE(USB, ep_idx, wEpRegVal);

    PCD_SET_EP_ADDRESS(USB, ep_idx, ep_idx);
    if (USB_EP_DIR_IS_OUT(ep->bEndpointAddress)) {
        g_fsdev_udc.out_ep[ep_idx].ep_mps = USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize);
        g_fsdev_udc.out_ep[ep_idx].ep_type = USB_GET_ENDPOINT_TYPE(ep->bmAttributes);
        g_fsdev_udc.out_ep[ep_idx].ep_enable = true;
        if (g_fsdev_udc.out_ep[ep_idx].ep_mps > g_fsdev_udc.out_ep[ep_idx].ep_pma_buf_len) {
            if (g_fsdev_udc.pma_offset + g_fsdev_udc.out_ep[ep_idx].ep_mps > CONFIG_USB_FSDEV_RAM_SIZE) {
                USB_LOG_ERR("Ep pma %02x overflow\r\n", ep->bEndpointAddress);
                return -1;
            }
            g_fsdev_udc.out_ep[ep_idx].ep_pma_buf_len = USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize);
            g_fsdev_udc.out_ep[ep_idx].ep_pma_addr = g_fsdev_udc.pma_offset;
            /*Set the endpoint Receive buffer address */
            PCD_SET_EP_RX_ADDRESS(USB, ep_idx, g_fsdev_udc.pma_offset);
            g_fsdev_udc.pma_offset += USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize);
        }
        /*Set the endpoint Receive buffer counter*/
        PCD_SET_EP_RX_CNT(USB, ep_idx, USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize));
        PCD_CLEAR_RX_DTOG(USB, ep_idx);
    } else {
        g_fsdev_udc.in_ep[ep_idx].ep_mps = USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize);
        g_fsdev_udc.in_ep[ep_idx].ep_type = USB_GET_ENDPOINT_TYPE(ep->bmAttributes);
        g_fsdev_udc.in_ep[ep_idx].ep_enable = true;
        if (g_fsdev_udc.in_ep[ep_idx].ep_mps > g_fsdev_udc.in_ep[ep_idx].ep_pma_buf_len) {
            if (g_fsdev_udc.pma_offset + g_fsdev_udc.in_ep[ep_idx].ep_mps > CONFIG_USB_FSDEV_RAM_SIZE) {
                USB_LOG_ERR("Ep pma %02x overflow\r\n", ep->bEndpointAddress);
                return -1;
            }
            g_fsdev_udc.in_ep[ep_idx].ep_pma_buf_len = USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize);
            g_fsdev_udc.in_ep[ep_idx].ep_pma_addr = g_fsdev_udc.pma_offset;
            /*Set the endpoint Transmit buffer address */
            PCD_SET_EP_TX_ADDRESS(USB, ep_idx, g_fsdev_udc.pma_offset);
            g_fsdev_udc.pma_offset += USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize);
        }

        PCD_CLEAR_TX_DTOG(USB, ep_idx);
        if (USB_GET_ENDPOINT_TYPE(ep->bmAttributes) != USB_ENDPOINT_TYPE_ISOCHRONOUS) {
            /* Configure NAK status for the Endpoint */
            PCD_SET_EP_TX_STATUS(USB, ep_idx, USB_EP_TX_NAK);
        } else {
            /* Configure TX Endpoint to disabled state */
            PCD_SET_EP_TX_STATUS(USB, ep_idx, USB_EP_TX_DIS);
        }
    }
    return 0;
}

int usbd_ep_close(uint8_t busid, const uint8_t ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (USB_EP_DIR_IS_OUT(ep)) {
        PCD_CLEAR_RX_DTOG(USB, ep_idx);

        /* Configure DISABLE status for the Endpoint*/
        PCD_SET_EP_RX_STATUS(USB, ep_idx, USB_EP_RX_DIS);
    } else {
        PCD_CLEAR_TX_DTOG(USB, ep_idx);

        /* Configure DISABLE status for the Endpoint*/
        PCD_SET_EP_TX_STATUS(USB, ep_idx, USB_EP_TX_DIS);
    }
    return 0;
}

int usbd_ep_set_stall(uint8_t busid, const uint8_t ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (USB_EP_DIR_IS_OUT(ep)) {
        PCD_SET_EP_RX_STATUS(USB, ep_idx, USB_EP_RX_STALL);
    } else {
        PCD_SET_EP_TX_STATUS(USB, ep_idx, USB_EP_TX_STALL);
    }
    return 0;
}

int usbd_ep_clear_stall(uint8_t busid, const uint8_t ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (USB_EP_DIR_IS_OUT(ep)) {
        PCD_CLEAR_RX_DTOG(USB, ep_idx);
        /* Configure VALID status for the Endpoint */
        PCD_SET_EP_RX_STATUS(USB, ep_idx, USB_EP_RX_VALID);
    } else {
        PCD_CLEAR_TX_DTOG(USB, ep_idx);

        if (g_fsdev_udc.in_ep[ep_idx].ep_type != USB_ENDPOINT_TYPE_ISOCHRONOUS) {
            /* Configure NAK status for the Endpoint */
            PCD_SET_EP_TX_STATUS(USB, ep_idx, USB_EP_TX_NAK);
        }
    }
    return 0;
}

int usbd_ep_is_stalled(uint8_t busid, const uint8_t ep, uint8_t *stalled)
{
    if (USB_EP_DIR_IS_OUT(ep)) {
    } else {
    }
    return 0;
}

int usbd_ep_start_write(uint8_t busid, const uint8_t ep, const uint8_t *data, uint32_t data_len)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (!data && data_len) {
        return -1;
    }

    if (!g_fsdev_udc.in_ep[ep_idx].ep_enable) {
        return -2;
    }

    g_fsdev_udc.in_ep[ep_idx].xfer_buf = (uint8_t *)data;
    g_fsdev_udc.in_ep[ep_idx].xfer_len = data_len;
    g_fsdev_udc.in_ep[ep_idx].actual_xfer_len = 0;

    data_len = MIN(data_len, g_fsdev_udc.in_ep[ep_idx].ep_mps);

    fsdev_write_pma(USB, (uint8_t *)data, g_fsdev_udc.in_ep[ep_idx].ep_pma_addr, (uint16_t)data_len);
    PCD_SET_EP_TX_CNT(USB, ep_idx, (uint16_t)data_len);
    PCD_SET_EP_TX_STATUS(USB, ep_idx, USB_EP_TX_VALID);

    return 0;
}

int usbd_ep_start_read(uint8_t busid, const uint8_t ep, uint8_t *data, uint32_t data_len)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (!data && data_len) {
        return -1;
    }
    if (!g_fsdev_udc.out_ep[ep_idx].ep_enable) {
        return -2;
    }

    g_fsdev_udc.out_ep[ep_idx].xfer_buf = data;
    g_fsdev_udc.out_ep[ep_idx].xfer_len = data_len;
    g_fsdev_udc.out_ep[ep_idx].actual_xfer_len = 0;

    PCD_SET_EP_RX_STATUS(USB, ep_idx, USB_EP_RX_VALID);

    return 0;
}

void USBD_IRQHandler(uint8_t busid)
{
    uint16_t wIstr, wEPVal;
    uint8_t ep_idx;
    uint8_t read_count;
    uint16_t write_count;
    uint16_t store_ep[8];

    wIstr = USB->ISTR;
    if (wIstr & USB_ISTR_CTR) {
        while ((USB->ISTR & USB_ISTR_CTR) != 0U) {
            wIstr = USB->ISTR;

            /* extract highest priority endpoint number */
            ep_idx = (uint8_t)(wIstr & USB_ISTR_EP_ID);

            if (ep_idx == 0U) {
                if ((wIstr & USB_ISTR_DIR) == 0U) {
                    PCD_CLEAR_TX_EP_CTR(USB, ep_idx);

                    write_count = PCD_GET_EP_TX_CNT(USB, ep_idx);

                    g_fsdev_udc.in_ep[ep_idx].xfer_buf += write_count;
                    g_fsdev_udc.in_ep[ep_idx].xfer_len -= write_count;
                    g_fsdev_udc.in_ep[ep_idx].actual_xfer_len += write_count;

                    usbd_event_ep_in_complete_handler(0, ep_idx | 0x80, g_fsdev_udc.in_ep[ep_idx].actual_xfer_len);

                    if (g_fsdev_udc.setup.wLength == 0) {
                        /* In status, start reading setup */
                        usbd_ep_start_read(0, 0x00, NULL, 0);
                    } else if (g_fsdev_udc.setup.wLength && ((g_fsdev_udc.setup.bmRequestType & USB_REQUEST_DIR_MASK) == USB_REQUEST_DIR_OUT)) {
                        /* In status, start reading setup */
                        usbd_ep_start_read(0, 0x00, NULL, 0);
                    }

                    if ((g_fsdev_udc.dev_addr > 0U) && (write_count == 0U)) {
                        USB->DADDR = ((uint16_t)g_fsdev_udc.dev_addr | USB_DADDR_EF);
                        g_fsdev_udc.dev_addr = 0U;
                    }

                } else {
                    wEPVal = PCD_GET_ENDPOINT(USB, ep_idx);

                    if ((wEPVal & USB_EP_SETUP) != 0U) {
                        PCD_CLEAR_RX_EP_CTR(USB, ep_idx);

                        read_count = PCD_GET_EP_RX_CNT(USB, ep_idx);
                        fsdev_read_pma(USB, (uint8_t *)&g_fsdev_udc.setup, g_fsdev_udc.out_ep[ep_idx].ep_pma_addr, (uint16_t)read_count);

                        usbd_event_ep0_setup_complete_handler(0, (uint8_t *)&g_fsdev_udc.setup);

                    } else if ((wEPVal & USB_EP_CTR_RX) != 0U) {
                        PCD_CLEAR_RX_EP_CTR(USB, ep_idx);

                        read_count = PCD_GET_EP_RX_CNT(USB, ep_idx);

                        fsdev_read_pma(USB, g_fsdev_udc.out_ep[ep_idx].xfer_buf, g_fsdev_udc.out_ep[ep_idx].ep_pma_addr, (uint16_t)read_count);

                        g_fsdev_udc.out_ep[ep_idx].xfer_buf += read_count;
                        g_fsdev_udc.out_ep[ep_idx].xfer_len -= read_count;
                        g_fsdev_udc.out_ep[ep_idx].actual_xfer_len += read_count;

                        usbd_event_ep_out_complete_handler(0, ep_idx, g_fsdev_udc.out_ep[ep_idx].actual_xfer_len);

                        if (read_count == 0) {
                            /* Out status, start reading setup */
                            usbd_ep_start_read(0, 0x00, NULL, 0);
                        }
                    }
                }
            } else {
                wEPVal = PCD_GET_ENDPOINT(USB, ep_idx);

                if ((wEPVal & USB_EP_CTR_RX) != 0U) {
                    PCD_CLEAR_RX_EP_CTR(USB, ep_idx);
                    read_count = PCD_GET_EP_RX_CNT(USB, ep_idx);
                    fsdev_read_pma(USB, g_fsdev_udc.out_ep[ep_idx].xfer_buf, g_fsdev_udc.out_ep[ep_idx].ep_pma_addr, (uint16_t)read_count);
                    g_fsdev_udc.out_ep[ep_idx].xfer_buf += read_count;
                    g_fsdev_udc.out_ep[ep_idx].xfer_len -= read_count;
                    g_fsdev_udc.out_ep[ep_idx].actual_xfer_len += read_count;

                    if ((read_count < g_fsdev_udc.out_ep[ep_idx].ep_mps) ||
                        (g_fsdev_udc.out_ep[ep_idx].xfer_len == 0)) {
                        usbd_event_ep_out_complete_handler(0, ep_idx, g_fsdev_udc.out_ep[ep_idx].actual_xfer_len);
                    } else {
                        PCD_SET_EP_RX_STATUS(USB, ep_idx, USB_EP_RX_VALID);
                    }
                }

                if ((wEPVal & USB_EP_CTR_TX) != 0U) {
                    PCD_CLEAR_TX_EP_CTR(USB, ep_idx);
                    write_count = PCD_GET_EP_TX_CNT(USB, ep_idx);

                    g_fsdev_udc.in_ep[ep_idx].xfer_buf += write_count;
                    g_fsdev_udc.in_ep[ep_idx].xfer_len -= write_count;
                    g_fsdev_udc.in_ep[ep_idx].actual_xfer_len += write_count;

                    if (g_fsdev_udc.in_ep[ep_idx].xfer_len == 0) {
                        usbd_event_ep_in_complete_handler(0, ep_idx | 0x80, g_fsdev_udc.in_ep[ep_idx].actual_xfer_len);
                    } else {
                        write_count = MIN(g_fsdev_udc.in_ep[ep_idx].xfer_len, g_fsdev_udc.in_ep[ep_idx].ep_mps);
                        fsdev_write_pma(USB, g_fsdev_udc.in_ep[ep_idx].xfer_buf, g_fsdev_udc.in_ep[ep_idx].ep_pma_addr, (uint16_t)write_count);
                        PCD_SET_EP_TX_CNT(USB, ep_idx, write_count);
                        PCD_SET_EP_TX_STATUS(USB, ep_idx, USB_EP_TX_VALID);
                    }
                }
            }
        }
    }
    if (wIstr & USB_ISTR_RESET) {
        memset(&g_fsdev_udc, 0, sizeof(struct fsdev_udc));
        g_fsdev_udc.pma_offset = USB_BTABLE_SIZE;
        usbd_event_reset_handler(0);
        /* start reading setup packet */
        PCD_SET_EP_RX_STATUS(USB, 0, USB_EP_RX_VALID);
        USB->ISTR &= (uint16_t)(~USB_ISTR_RESET);
    }
    if (wIstr & USB_ISTR_PMAOVR) {
        USB->ISTR &= (uint16_t)(~USB_ISTR_PMAOVR);
    }
    if (wIstr & USB_ISTR_ERR) {
        USB->ISTR &= (uint16_t)(~USB_ISTR_ERR);
    }
    if (wIstr & USB_ISTR_WKUP) {
        USB->CNTR &= (uint16_t) ~(USB_CNTR_LP_MODE);
        USB->CNTR &= (uint16_t) ~(USB_CNTR_FSUSP);

        USB->ISTR &= (uint16_t)(~USB_ISTR_WKUP);
    }
    if (wIstr & USB_ISTR_SUSP) {
        /* WA: To Clear Wakeup flag if raised with suspend signal */

        /* Store Endpoint register */
        for (uint8_t i = 0U; i < 8U; i++) {
            store_ep[i] = PCD_GET_ENDPOINT(USB, i);
        }

        /* FORCE RESET */
        USB->CNTR |= (uint16_t)(USB_CNTR_FRES);

        /* CLEAR RESET */
        USB->CNTR &= (uint16_t)(~USB_CNTR_FRES);

        /* wait for reset flag in ISTR */
        while ((USB->ISTR & USB_ISTR_RESET) == 0U) {
        }

        /* Clear Reset Flag */
        USB->ISTR &= (uint16_t)(~USB_ISTR_RESET);
        /* Restore Registre */
        for (uint8_t i = 0U; i < 8U; i++) {
            PCD_SET_ENDPOINT(USB, i, store_ep[i]);
        }

        /* Force low-power mode in the macrocell */
        USB->CNTR |= (uint16_t)USB_CNTR_FSUSP;

        /* clear of the ISTR bit must be done after setting of CNTR_FSUSP */
        USB->ISTR &= (uint16_t)(~USB_ISTR_SUSP);

        USB->CNTR |= (uint16_t)USB_CNTR_LP_MODE;
    }
    if (wIstr & USB_ISTR_SOF) {
        USB->ISTR &= (uint16_t)(~USB_ISTR_SOF);
    }
    if (wIstr & USB_ISTR_ESOF) {
        USB->ISTR &= (uint16_t)(~USB_ISTR_ESOF);
    }
}

static void fsdev_write_pma(USB_TypeDef *USBx, uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes)
{
    uint32_t n = ((uint32_t)wNBytes + 1U) >> 1;
    uint32_t BaseAddr = (uint32_t)USBx;
    uint32_t i, temp1, temp2;
    __IO uint16_t *pdwVal;
    uint8_t *pBuf = pbUsrBuf;

    pdwVal = (__IO uint16_t *)(BaseAddr + 0x400U + ((uint32_t)wPMABufAddr * PMA_ACCESS));

    for (i = n; i != 0U; i--) {
        temp1 = *pBuf;
        pBuf++;
        temp2 = temp1 | ((uint16_t)((uint16_t)*pBuf << 8));
        *pdwVal = (uint16_t)temp2;
        pdwVal++;

#if PMA_ACCESS > 1U
        pdwVal++;
#endif

        pBuf++;
    }
}

/**
  * @brief Copy data from packet memory area (PMA) to user memory buffer
  * @param   USBx USB peripheral instance register address.
  * @param   pbUsrBuf pointer to user memory area.
  * @param   wPMABufAddr address into PMA.
  * @param   wNBytes no. of bytes to be copied.
  * @retval None
  */
static void fsdev_read_pma(USB_TypeDef *USBx, uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes)
{
    uint32_t n = (uint32_t)wNBytes >> 1;
    uint32_t BaseAddr = (uint32_t)USBx;
    uint32_t i, temp;
    __IO uint16_t *pdwVal;
    uint8_t *pBuf = pbUsrBuf;

    pdwVal = (__IO uint16_t *)(BaseAddr + 0x400U + ((uint32_t)wPMABufAddr * PMA_ACCESS));

    for (i = n; i != 0U; i--) {
        temp = *(__IO uint16_t *)pdwVal;
        pdwVal++;
        *pBuf = (uint8_t)((temp >> 0) & 0xFFU);
        pBuf++;
        *pBuf = (uint8_t)((temp >> 8) & 0xFFU);
        pBuf++;

#if PMA_ACCESS > 1U
        pdwVal++;
#endif
    }

    if ((wNBytes % 2U) != 0U) {
        temp = *pdwVal;
        *pBuf = (uint8_t)((temp >> 0) & 0xFFU);
    }
}
