/*!
    \file  usbd_core.c
    \brief USB device mode core driver

    \version 2014-12-26, V1.0.0, firmware for GD32F10x
    \version 2017-06-20, V2.0.0, firmware for GD32F10x
    \version 2018-07-31, V2.1.0, firmware for GD32F10x
*/

/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.

    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
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
    \param[in]  ep_desc: pointer to usb endpoint descriptor 
    \param[out] none
    \retval     none
*/
void usbd_ep_init (usb_core_handle_struct *pudev, const usb_descriptor_endpoint_struct *ep_desc)
{
    usb_ep_struct *ep;
    usb_dir_enum ep_dir;

    uint32_t devepinten = 0U;
    uint32_t devepctl = 0U;

    uint8_t  ep_num  = ep_desc->bEndpointAddress & 0x7FU;
    uint8_t  ep_type = ep_desc->bmAttributes & USB_EPTYPE_MASK;
    uint16_t ep_mps  = ep_desc->wMaxPacketSize;

    if (ep_desc->bEndpointAddress >> 7U) {
        ep = &pudev->dev.in_ep[ep_num];

        devepinten |= 1U << ep_num;
        devepctl = USB_DIEPxCTL((uint16_t)ep_num);

        ep_dir = USB_TX;
    } else {
        ep = &pudev->dev.out_ep[ep_num];

        devepinten |= (1U << ep_num) << 16U;
        devepctl = USB_DOEPxCTL((uint16_t)ep_num);

        ep_dir = USB_RX;
    }

    /* if the endpoint is not active, need change the endpoint control register */
    if (!(devepctl & DEPCTL_EPACT)) {
        devepctl &= ~DEPCTL_MPL;
        devepctl |= ep_mps;

        devepctl &= ~DEPCTL_EPTYPE;
        devepctl |= (uint32_t)ep_type << 18U;

        if (USB_TX == ep_dir) {
            devepctl &= ~DIEPCTL_TXFNUM;
            devepctl |= (uint32_t)ep_num << 22U;
        }

        devepctl |= DEPCTL_SD0PID;
        devepctl |= DEPCTL_EPACT;
    }

    if (USB_TX == ep_dir) {
        USB_DIEPxCTL((uint16_t)ep_num) = devepctl;
    } else if (USB_RX == ep_dir) {
        USB_DOEPxCTL((uint16_t)ep_num) = devepctl;
    } else {
        /* no operation */
    }

    ep->endp_mps = ep_mps;
    ep->endp_type = ep_type;

    /* enable the interrupts for this endpoint */
    USB_DAEPINTEN |= devepinten;
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
    uint32_t devepinten = 0U;
    uint8_t ep_num = ep_addr & 0x7FU;

    if (ep_addr >> 7U) {
        devepinten |= 1U << ep_num;

        USB_DIEPxCTL((uint16_t)ep_num) &= ~DEPCTL_EPACT;
    } else {
        devepinten |= (1U << ep_num) << 16U;

        USB_DOEPxCTL((uint16_t)ep_num) &= ~DEPCTL_EPACT;
    }

    /* disable the interrupts for this endpoint */
    USB_DAEPINTEN &= ~devepinten;
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
    uint8_t ep_num = ep_addr & 0x7FU;
    uint32_t devepctl = 0U, devepxlen = 0U;

    ep = &pudev->dev.out_ep[ep_num];

    /* setup and start the Xfer */
    ep->xfer_buff = pbuf;
    ep->xfer_len = buf_len;
    ep->xfer_count = 0U;

    devepctl = USB_DOEPxCTL((uint16_t)ep_num);
    devepxlen = USB_DOEPxLEN((uint16_t)ep_num);

    devepxlen &= ~DEPLEN_TLEN;
    devepxlen &= ~DEPLEN_PCNT;

    /* zero length packet */
    if (0U == ep->xfer_len) {
        /* set the transfer length to max packet size */
        devepxlen |= ep->endp_mps;

        /* set the transfer packet count to 1 */
        devepxlen |= 1U << 19U;
    } else {
      
        if (0U == ep_num) {
            /* set the transfer length to max packet size */
            devepxlen |= ep->endp_mps;

            /* set the transfer packet count to 1 */
            devepxlen |= 1U << 19U;
        } else {
            /* configure the transfer size and packet count as follows:
             * pktcnt = N
             * xfersize = N * maxpacket
             */
            devepxlen |= ((ep->xfer_len + ep->endp_mps - 1U) / ep->endp_mps) << 19U;
            devepxlen |= ((devepxlen & DEPLEN_PCNT) >> 19U) * ep->endp_mps;
        }
    }

    USB_DOEPxLEN((uint16_t)ep_num) = devepxlen;

    if (USB_EPTYPE_ISOC == ep->endp_type) {
        if (ep->endp_frame) {
            devepctl |= DEPCTL_SODDFRM;
        } else {
            devepctl |= DEPCTL_SEVNFRM;
        }
    }

    /* enable the endpoint and clear the NAK */
    devepctl |= DEPCTL_EPEN | DEPCTL_CNAK;

    USB_DOEPxCTL((uint16_t)ep_num) = devepctl;
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
    uint8_t ep_num = ep_addr & 0x7FU;
    __IO uint32_t devepctl = 0U;
    __IO uint32_t deveplen = 0U;

    ep = &pudev->dev.in_ep[ep_num];

    /* setup and start the transfer */
    ep->xfer_buff = pbuf;
    ep->xfer_len = buf_len;
    ep->xfer_count = 0U;

    devepctl = USB_DIEPxCTL((uint16_t)ep_num);
    deveplen = USB_DIEPxLEN((uint16_t)ep_num);

    /* clear transfer length to 0 */
    deveplen &= ~DEPLEN_TLEN;

    /* clear transfer packet to 0 */
    deveplen &= ~DEPLEN_PCNT;

    /* zero length packet */
    if (0U == ep->xfer_len) {
        /* set transfer packet count to 1 */
        deveplen |= 1U << 19U;
    } else {
        if (0U == ep_num) {
            if (ep->xfer_len > ep->endp_mps) {
                ep->xfer_len = ep->endp_mps;
            }

            deveplen |= 1U << 19U;
        } else {
            deveplen |= ((ep->xfer_len - 1U + ep->endp_mps) / ep->endp_mps) << 19U;
        }

        /* configure the transfer size and packet count as follows: 
         * xfersize = N * maxpacket + short_packet 
         * pktcnt = N + (short_packet exist ? 1 : 0)
         */
        deveplen |= ep->xfer_len;

        if (USB_EPTYPE_ISOC == ep->endp_type) {
            deveplen |= DIEPLEN_MCNT & (1U << 29U);
        }
    }

    USB_DIEPxLEN((uint16_t)ep_num) = deveplen;

    if (USB_EPTYPE_ISOC == ep->endp_type) {
        if (0U == (((USB_DSTAT & DSTAT_FNRSOF) >> 8U) & 0x1U)) {
            devepctl |= DEPCTL_SODDFRM;
        } else {
            devepctl |= DEPCTL_SEVNFRM;
        }
    }

    /* enable the endpoint and clear the NAK */
    devepctl |= DEPCTL_EPEN | DEPCTL_CNAK;

    USB_DIEPxCTL((uint16_t)ep_num) = devepctl;

    if (USB_EPTYPE_ISOC != ep->endp_type) {
        /* enable the Tx FIFO empty interrupt for this endpoint */
        if (ep->xfer_len > 0U) {
            USB_DIEPFEINTEN |= 1U << ep_num;
        }
    } else {
        usb_fifo_write(ep->xfer_buff, ep_num, (uint16_t)ep->xfer_len);
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
    uint8_t ep_num = ep_addr & 0x7FU;
    __IO uint32_t devepctl = 0U;

    if (ep_addr >> 7U) {
        devepctl = USB_DIEPxCTL((uint16_t)ep_num);

        /* set the endpoint disable bit */
        if (devepctl & DEPCTL_EPEN) {
            devepctl |= DEPCTL_EPD;
        }

        /* set the endpoint stall bit */
        devepctl |= DEPCTL_STALL;

        USB_DIEPxCTL((uint16_t)ep_num) = devepctl;
    } else {
        /* set the endpoint stall bit */
        USB_DOEPxCTL((uint16_t)ep_num) |= DEPCTL_STALL;
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
    uint8_t ep_num = ep_addr & 0x7FU;
    __IO uint32_t devepctl = 0U;

    if(ep_addr >> 7U){
        ep = &pudev->dev.in_ep[ep_num];

        devepctl = USB_DIEPxCTL((uint16_t)ep_num);

        /* clear the in endpoint stall bits */
        devepctl &= ~DEPCTL_STALL;

        if ((USB_EPTYPE_INTR == ep->endp_type) || (USB_EPTYPE_BULK == ep->endp_type)) {
            devepctl |= DEPCTL_SEVNFRM;
        }

        USB_DIEPxCTL((uint16_t)ep_num) = devepctl;
    } else {
        ep = &pudev->dev.out_ep[ep_num];

        devepctl = USB_DOEPxCTL((uint16_t)ep_num);

        /* clear the out endpoint stall bits */
        devepctl &= ~DEPCTL_STALL;

        if ((USB_EPTYPE_INTR == ep->endp_type) || (USB_EPTYPE_BULK == ep->endp_type)) {
            devepctl |= DEPCTL_SEVNFRM;
        }

        USB_DOEPxCTL((uint16_t)ep_num) = devepctl;
    }
}

/*!
    \brief      flushes the fifos
    \param[in]  pudev: pointer to usb device instance
    \param[in]  ep_addr: endpoint address
    \param[out] none
    \retval     none
*/
void  usbd_ep_fifo_flush (usb_core_handle_struct *pudev, uint8_t ep_addr)
{
    if (ep_addr >> 7U) {
        usb_txfifo_flush(pudev, ep_addr & 0x7FU);
    } else {
        usb_rxfifo_flush(pudev);
    }
}

/*!
    \brief      get the received data length
    \param[in]  pudev: pointer to usb device instance
    \param[in]  ep_num: endpoint identifier which is in (0..3)
    \param[out] none
    \retval     received data length
*/
uint16_t  usbd_rxcount_get (usb_core_handle_struct *pudev, uint8_t ep_num)
{
    return (uint16_t)pudev->dev.out_ep[ep_num].xfer_count;
}
