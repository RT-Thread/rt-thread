/*!
    \file  usbd_core.c
    \brief USB device-mode core driver
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#include "usbd_core.h"
#include "usbd_std.h"

/*!
    \brief      initailizes the USB device-mode handler stack
    \param[in]  pudev: pointer to usb device instance
    \param[in]  core_id: USB core ID
    \param[out] none
    \retval     none
*/
void usbd_init (usb_core_handle_struct *pudev, usb_core_id_enum core_id)
{
    /* select USB core */
    usb_core_select (pudev, core_id);

    pudev->dev.status = USB_STATUS_DEFAULT;

    /* disable USB global interrupt */
    USB_GLOBAL_INT_DISABLE();

    /* init the core (common init.) */
    usb_core_init(pudev);

    /* force device mode*/
    usb_mode_set(pudev, DEVICE_MODE);

    /* set device disconnect */
    USB_SOFT_DISCONNECT_ENABLE();

    if ((void *)0 != pudev->mdelay) {
        pudev->mdelay(3U);
    }

    /* init device */
    usb_devcore_init(pudev);

    /* set device Connect */
    USB_SOFT_DISCONNECT_DISABLE();

    if ((void *)0 != pudev->mdelay) {
        pudev->mdelay(3U);
    }

    /* enable USB global interrupt */
    USB_GLOBAL_INT_ENABLE();
}

/*!
    \brief      endpoint initialization
    \param[in]  pudev: pointer to usb device instance
    \param[in]  pep_desc: pointer to usb endpoint descriptor 
    \param[out] none
    \retval     none
*/
void usbd_ep_init (usb_core_handle_struct *pudev, const usb_descriptor_endpoint_struct *pep_desc)
{
    usb_ep_struct *ep;

    uint32_t dev_all_ep_int_en = 0U;
    uint32_t dev_ep_ctlr = 0U; 

    uint8_t ep_id = pep_desc->bEndpointAddress & 0x7FU;
    uint8_t ep_type = pep_desc->bmAttributes & USB_EPTYPE_MASK;
    uint16_t ep_mps = pep_desc->wMaxPacketSize;

    if (pep_desc->bEndpointAddress >> 7) {
        ep = &pudev->dev.in_ep[ep_id];

        dev_all_ep_int_en |= 1U << ep_id;
        dev_ep_ctlr = USB_DIEPxCTL((uint16_t)ep_id);

        /* if the endpoint is not active, need change the endpoint control register */
        if (!(dev_ep_ctlr & DIEPCTL_EPACT)) {
            if (0U == ep_id) {
                dev_ep_ctlr &= ~DIEP0CTL_MPL;
            } else {
                dev_ep_ctlr &= ~DIEPCTL_MPL;
            }
            dev_ep_ctlr |= ep_mps;

            dev_ep_ctlr &= ~DIEPCTL_EPTYPE;
            dev_ep_ctlr |= (uint32_t)ep_type << 18;

            dev_ep_ctlr &= ~DIEPCTL_TXFNUM;
            dev_ep_ctlr |= (uint32_t)ep_id << 22;

            if (0U != ep_id) {
                dev_ep_ctlr |= DIEPCTL_SD0PID;
                dev_ep_ctlr |= DIEPCTL_EPACT;
            }

            USB_DIEPxCTL((uint16_t)ep_id) = dev_ep_ctlr;
        }
    } else {
        ep = &pudev->dev.out_ep[ep_id];

        dev_all_ep_int_en |= (1U << ep_id) << 16;
        dev_ep_ctlr = USB_DOEPxCTL((uint16_t)ep_id);

        /* if the endpoint is not active, need change the endpoint control register */
        if (!(dev_ep_ctlr & DOEPCTL_EPACT)) {
            if (0U == ep_id) {
                dev_ep_ctlr &= ~DOEP0CTL_MPL;
            } else {
                dev_ep_ctlr &= ~DOEPCTL_MPL;
            }
            dev_ep_ctlr |= ep_mps;

            dev_ep_ctlr &= ~DOEPCTL_EPTYPE;
            dev_ep_ctlr |= (uint32_t)ep_type << 18;

            if (0U != ep_id) {
                dev_ep_ctlr |= DOEPCTL_SD0PID;
                dev_ep_ctlr |= DOEPCTL_EPACT;
            }

            USB_DOEPxCTL((uint16_t)ep_id) = dev_ep_ctlr;
        }
    }

    ep->endp_mps = ep_mps;
    ep->endp_type = ep_type;

    /* enable the interrupts for this endpoint */
#ifdef USBHS_DEDICATED_EP1_ENABLED
    if ((1 == ep_id) && (USB_HS_CORE_ID == pudev->cfg.core_id)) {
        USB_DEP1INTEN |= dev_all_ep_int_en;
    } else
#endif /* USBHS_DEDICATED_EP1_ENABLED */
    {
        USB_DAEPINTEN |= dev_all_ep_int_en;
    }
}

/*!
    \brief      endpoint deinitialize
    \param[in]  pudev: pointer to usb device instance
    \param[in]  ep_addr: endpoint address
    \param[out] none
    \retval     none
*/
void usbd_ep_deinit (usb_core_handle_struct *pudev, uint8_t ep_addr)
{
    uint32_t dev_all_ep_int_en = 0U;
    uint8_t ep_id = ep_addr & 0x7FU;

    if (ep_addr >> 7) {
        dev_all_ep_int_en |= 1U << ep_id;

        USB_DIEPxCTL((uint16_t)ep_id) &= ~DIEPCTL_EPACT;
    } else {
        dev_all_ep_int_en |= (1U << ep_id) << 16U;

        USB_DOEPxCTL((uint16_t)ep_id) &= ~DOEPCTL_EPACT;
    }

    /* disable the interrupts for this endpoint */
#ifdef USBHS_DEDICATED_EP1_ENABLED
    if ((1U == ep_id) && (USB_HS_CORE_ID == pudev->cfg.core_id)) {
        USB_DEP1INTEN &= ~dev_all_ep_int_en;
    } else
#endif /* USBHS_DEDICATED_EP1_ENABLED */
    {
        USB_DAEPINTEN &= ~dev_all_ep_int_en;
    }
}

/*!
    \brief      endpoint prepare to receive data
    \param[in]  pudev: pointer to usb device instance
    \param[in]  ep_addr: endpoint address
    \param[in]  pbuf: pointer to buffer
    \param[in]  buf_len: buffer length
    \param[out] none
    \retval     none
*/
void usbd_ep_rx (usb_core_handle_struct *pudev, uint8_t ep_addr, uint8_t *pbuf, uint16_t buf_len)
{
    usb_ep_struct *ep;
    uint8_t ep_id = ep_addr & 0x7FU;
    uint32_t dev_ep_ctlr = 0U, dev_ep_xlen = 0U;

    ep = &pudev->dev.out_ep[ep_id];

    /* setup and start the Xfer */
    ep->xfer_buff = pbuf;
    ep->xfer_len = buf_len;
    ep->xfer_count = 0U;

    if (1U == pudev->cfg.dma_enable) {
        ep->dma_addr = (uint32_t)pbuf;
    }

    dev_ep_ctlr = USB_DOEPxCTL((uint16_t)ep_id);
    dev_ep_xlen = USB_DOEPxLEN((uint16_t)ep_id);

    dev_ep_xlen &= ~DOEPLEN_TLEN;
    dev_ep_xlen &= ~DOEPLEN_PCNT;

    /* zero length packet */
    if (0U == ep->xfer_len) {
        /* set the transfer length to max packet size */
        dev_ep_xlen |= ep->endp_mps;

        /* set the transfer packet count to 1 */
        dev_ep_xlen |= 1U << 19U;
    } else {
        if (0U == ep_id) {
            /* set the transfer length to max packet size */
            dev_ep_xlen |= ep->endp_mps;

            /* set the transfer packet count to 1 */
            dev_ep_xlen |= 1U << 19U;
        } else {
            /* configure the transfer size and packet count as follows:
             * pktcnt = N
             * xfersize = N * maxpacket
             */
            dev_ep_xlen |= ((ep->xfer_len + ep->endp_mps - 1U) / ep->endp_mps) << 19U;
            dev_ep_xlen |= ((dev_ep_xlen & DOEPLEN_PCNT) >> 19U) * ep->endp_mps;
        }
    }

    USB_DOEPxLEN((uint16_t)ep_id) = dev_ep_xlen;

    if (1U == pudev->cfg.dma_enable) {
        USB_DOEPxDMAADDR((uint16_t)ep_id) = ep->dma_addr;
    }

    if (USB_EPTYPE_ISOC == ep->endp_type) {
        if (ep->endp_frame) {
            dev_ep_ctlr |= DOEPCTL_SODDFRM;
        } else {
            dev_ep_ctlr |= DOEPCTL_SEVNFRM;
        }
    }

    /* enable the endpoint and clear the NAK */
    dev_ep_ctlr |= DOEPCTL_EPEN | DOEPCTL_CNAK;

    USB_DOEPxCTL((uint16_t)ep_id) = dev_ep_ctlr;
}

/*!
    \brief      endpoint prepare to transmit data
    \param[in]  pudev: pointer to usb device instance
    \param[in]  ep_addr: endpoint address
    \param[in]  pbuf: pointer to buffer
    \param[in]  len: buffer length
    \param[out] none
    \retval     none
*/
void  usbd_ep_tx (usb_core_handle_struct *pudev, uint8_t ep_addr, uint8_t *pbuf, uint32_t buf_len)
{
    usb_ep_struct *ep;
    uint8_t ep_id = ep_addr & 0x7FU;
    __IO uint32_t dev_ep_ctlr = 0U;
    __IO uint32_t dev_ep_xlen = 0U;

    ep = &pudev->dev.in_ep[ep_id];

    /* setup and start the transfer */
    ep->xfer_buff = pbuf;
    ep->xfer_len = buf_len;
    ep->xfer_count = 0U;

    if (1U == pudev->cfg.dma_enable) {
        ep->dma_addr = (uint32_t)pbuf;
    }

    dev_ep_ctlr = USB_DIEPxCTL((uint16_t)ep_id);
    dev_ep_xlen = USB_DIEPxLEN((uint16_t)ep_id);

    /* clear transfer length to 0 */
    dev_ep_xlen &= ~DIEPLEN_TLEN;

    /* clear transfer packet to 0 */
    dev_ep_xlen &= ~DIEPLEN_PCNT;

    /* zero length packet */
    if (0U == ep->xfer_len) {
        /* set transfer packet count to 1 */
        dev_ep_xlen |= 1U << 19U;
    } else {
        if (0U == ep_id) {
            if (ep->xfer_len > ep->endp_mps) {
                ep->xfer_len = ep->endp_mps;
            }

            dev_ep_xlen |= 1U << 19U;
        } else {
            dev_ep_xlen |= ((ep->xfer_len - 1U + ep->endp_mps) / ep->endp_mps) << 19U;
        }

        /* configure the transfer size and packet count as follows: 
         * xfersize = N * maxpacket + short_packet 
         * pktcnt = N + (short_packet exist ? 1 : 0)
         */
        dev_ep_xlen |= ep->xfer_len;

        if (USB_EPTYPE_ISOC == ep->endp_type) {
            dev_ep_xlen |= DIEPLEN_MCNT & (1U << 29U);
        }
    }

    USB_DIEPxLEN((uint16_t)ep_id) = dev_ep_xlen;

    if (USB_EPTYPE_ISOC == ep->endp_type) {
        if (0U == (((USB_DSTAT & DSTAT_FNRSOF) >> 8U) & 0x1U)) {
            dev_ep_ctlr |= DIEPCTL_SODDFRM;
        } else {
            dev_ep_ctlr |= DIEPCTL_SEVNFRM;
        }
    }

    if (1U == pudev->cfg.dma_enable) {
        USB_DIEPxDMAADDR((uint16_t)ep_id) = ep->dma_addr;
    }

    /* enable the endpoint and clear the NAK */
    dev_ep_ctlr |= DIEPCTL_EPEN | DIEPCTL_CNAK;

    USB_DIEPxCTL((uint16_t)ep_id) = dev_ep_ctlr;

    if (0U == pudev->cfg.dma_enable) {
        if (USB_EPTYPE_ISOC != ep->endp_type) {
            /* enable the Tx FIFO empty interrupt for this endpoint */
            if (ep->xfer_len > 0U) {
                USB_DIEPFEINTEN |= 1U << ep_id;
            }
        } else {
            usb_fifo_write(ep->xfer_buff, ep_id, (uint16_t)ep->xfer_len);
        }
    }
}

/*!
    \brief      transmit data on the control channel
    \param[in]  pudev: pointer to usb device instance
    \param[in]  pbuf: pointer to buffer
    \param[in]  len: buffer length
    \param[out] none
    \retval     usb device operation status
*/
usbd_status_enum  usbd_ctltx (usb_core_handle_struct *pudev, uint8_t *pbuf, uint16_t len)
{
    usbd_status_enum ret = USBD_OK;

    pudev->dev.sum_len = len;
    pudev->dev.remain_len = len;
    pudev->dev.ctl_status = USB_CTRL_DATA_IN;

    usbd_ep_tx (pudev, 0U, pbuf, (uint32_t)len);

    return ret;
}

/*!
    \brief      receive data on the control channel
    \param[in]  pudev: pointer to usb device instance
    \param[in]  pbuf: pointer to buffer
    \param[in]  len: buffer length
    \param[out] none
    \retval     usb device operation status
*/
usbd_status_enum  usbd_ctlrx (usb_core_handle_struct *pudev, uint8_t *pbuf, uint16_t len)
{
    pudev->dev.sum_len = len;
    pudev->dev.remain_len = len;
    pudev->dev.ctl_status = USB_CTRL_DATA_OUT;

    usbd_ep_rx (pudev, 0U, pbuf, len);

    return USBD_OK;
}

/*!
    \brief      transmit status on the control channel
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     usb device operation status
*/
usbd_status_enum  usbd_ctlstatus_tx (usb_core_handle_struct *pudev)
{
    pudev->dev.ctl_status = USB_CTRL_STATUS_IN;

    usbd_ep_tx (pudev, 0U, NULL, 0U);

    usb_ep0_startout(pudev);

    return USBD_OK;
}

/*!
    \brief      receive status on the control channel
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     usb device operation status
*/
usbd_status_enum  usbd_ctlstatus_rx (usb_core_handle_struct *pudev)
{
    pudev->dev.ctl_status = USB_CTRL_STATUS_OUT;

    usbd_ep_rx (pudev, 0U, NULL, 0U);

    usb_ep0_startout(pudev);

    return USBD_OK;
}

/*!
    \brief      set an endpoint to STALL status
    \param[in]  pudev: pointer to usb device instance
    \param[in]  ep_addr: endpoint address
    \param[out] none
    \retval     none
*/
void  usbd_ep_stall (usb_core_handle_struct *pudev, uint8_t ep_addr)
{
    uint8_t ep_id = ep_addr & 0x7FU;
    __IO uint32_t dev_ep_ctlr = 0U;

    if (ep_addr >> 7U) {
        dev_ep_ctlr = USB_DIEPxCTL((uint16_t)ep_id);

        /* set the endpoint disable bit */
        if (dev_ep_ctlr & DIEPCTL_EPEN) {
            dev_ep_ctlr |= DIEPCTL_EPD;
        }

        /* set the endpoint stall bit */
        dev_ep_ctlr |= DIEPCTL_STALL;

        USB_DIEPxCTL((uint16_t)ep_id) = dev_ep_ctlr;
    } else {
        /* set the endpoint stall bit */
        USB_DOEPxCTL((uint16_t)ep_id) |= DOEPCTL_STALL;
    }
}

/*!
    \brief      clear endpoint stalled status
    \param[in]  pudev: pointer to usb device instance
    \param[in]  ep_addr: endpoint address
    \param[out] none
    \retval     none
*/
void usbd_ep_clear_stall (usb_core_handle_struct *pudev, uint8_t ep_addr)
{
    usb_ep_struct *ep;
    uint8_t ep_id = ep_addr & 0x7FU;
    __IO uint32_t dev_ep_ctlr = 0U;

    if(ep_addr >> 7){
        ep = &pudev->dev.in_ep[ep_id];

        dev_ep_ctlr = USB_DIEPxCTL((uint16_t)ep_id);

        /* clear the IN endpoint stall bits */
        dev_ep_ctlr &= ~DIEPCTL_STALL;

        if ((USB_EPTYPE_INTR == ep->endp_type) || (USB_EPTYPE_BULK == ep->endp_type)) {
            dev_ep_ctlr |= DIEPCTL_SEVNFRM;
        }

        USB_DIEPxCTL((uint16_t)ep_id) = dev_ep_ctlr;
    } else {
        ep = &pudev->dev.out_ep[ep_id];

        dev_ep_ctlr = USB_DOEPxCTL((uint16_t)ep_id);

        /* clear the OUT endpoint stall bits */
        dev_ep_ctlr &= ~DOEPCTL_STALL;

        if ((USB_EPTYPE_INTR == ep->endp_type) || (USB_EPTYPE_BULK == ep->endp_type)) {
            dev_ep_ctlr |= DOEPCTL_SEVNFRM;
        }

        USB_DOEPxCTL((uint16_t)ep_id) = dev_ep_ctlr;
    }
}

/*!
    \brief      flushes the FIFOs
    \param[in]  pudev: pointer to usb device instance
    \param[in]  ep_addr: endpoint address
    \param[out] none
    \retval     none
*/
void  usbd_ep_fifo_flush (usb_core_handle_struct *pudev, uint8_t ep_addr)
{
    if (ep_addr >> 7) {
        usb_txfifo_flush(pudev, ep_addr & 0x7FU);
    } else {
        usb_rxfifo_flush(pudev);
    }
}

/*!
    \brief      get the received data length
    \param[in]  pudev: pointer to usb device instance
    \param[in]  ep_id: endpoint identifier which is in (0..3)
    \param[out] none
    \retval     received data length
*/
uint16_t  usbd_rxcount_get (usb_core_handle_struct *pudev, uint8_t ep_id)
{
    return (uint16_t)pudev->dev.out_ep[ep_id].xfer_count;
}
