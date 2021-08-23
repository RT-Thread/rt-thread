/*!
    \file  usbd_int.c 
    \brief USB device mode interrupt routines

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

#include "usbd_int.h"
#include "usbd_std.h"

/* interrupt handlers */
static uint32_t usbd_intf_outep               (usb_core_handle_struct *pudev);
static uint32_t usbd_intf_inep                (usb_core_handle_struct *pudev);
static uint32_t usbd_intf_earlysuspend        (usb_core_handle_struct *pudev);
static uint32_t usbd_intf_suspend             (usb_core_handle_struct *pudev);
static uint32_t usbd_intf_resume              (usb_core_handle_struct *pudev);
static uint32_t usbd_intf_sof                 (usb_core_handle_struct *pudev);
static uint32_t usbd_intf_rxfifo              (usb_core_handle_struct *pudev);
static uint32_t usbd_intf_reset               (usb_core_handle_struct *pudev);
static uint32_t usbd_intf_enumfinish          (usb_core_handle_struct *pudev);
static uint32_t usbd_intf_isoinincomplete     (usb_core_handle_struct *pudev);
static uint32_t usbd_intf_isooutincomplete    (usb_core_handle_struct *pudev);

static uint32_t usbd_emptytxfifo_write        (usb_core_handle_struct *pudev, uint8_t ep_num);

#ifdef VBUS_SENSING_ENABLED

    static uint32_t usbd_intf_otg             (usb_core_handle_struct *pudev);
    static uint32_t usbd_intf_sessionrequest  (usb_core_handle_struct *pudev);

#endif /* VBUS_SENSING_ENABLED */

static usb_speed_enum USB_SPEED[4] = {
    [DSTAT_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ] = USB_SPEED_HIGH,
    [DSTAT_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ] = USB_SPEED_FULL,
    [DSTAT_ENUMSPD_FS_PHY_48MHZ] = USB_SPEED_FULL,
    [DSTAT_ENUMSPD_LS_PHY_6MHZ] = USB_SPEED_LOW
};

static const uint8_t EP0_MAXLEN[4] = {
    [DSTAT_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ] = EP0MPL_64,
    [DSTAT_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ] = EP0MPL_64,
    [DSTAT_ENUMSPD_FS_PHY_48MHZ] = EP0MPL_64,
    [DSTAT_ENUMSPD_LS_PHY_6MHZ] = EP0MPL_8
};

/*!
    \brief      USB device-mode interrupts global service routine handler
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
uint32_t usbd_isr (usb_core_handle_struct *pudev)
{
    uint32_t retval = 0U;
    uint32_t int_status = 0U, gintf = USB_GINTF, ginten = USB_GINTEN;

    /* ensure the core is in device mode */
    if (DEVICE_MODE == USB_CURRENT_MODE_GET()) {
        int_status = gintf & ginten;

        /* there are no interrupts, avoid spurious interrupt */
        if (!int_status) {
            return 0U;
        }

        /* OUT endpoints interrupts */
        if (int_status & GINTF_OEPIF) {
            retval |= usbd_intf_outep(pudev);
        }

        /* IN endpoints interrupts */
        if (int_status & GINTF_IEPIF) {
            retval |= usbd_intf_inep(pudev);
        }

        /* mode mismatch interrupt */
        if (int_status & GINTF_MFIF) {
            /* clear interrupt */
            USB_GINTF = GINTF_MFIF;
        }

        /* early suspend interrupt */
        if (int_status & GINTF_ESP) {
            retval |= usbd_intf_earlysuspend(pudev);
        }

        /* suspend interrupt */
        if (int_status & GINTF_SP) {
            retval |= usbd_intf_suspend(pudev);
        }

        /* wakeup interrupt */
        if (int_status & GINTF_WKUPIF) {
            retval |= usbd_intf_resume(pudev);
        }

        /* start of frame interrupt */
        if (int_status & GINTF_SOF) {
            retval |= usbd_intf_sof(pudev);
        }

        /* reveive fifo not empty interrupt */
        if (int_status & GINTF_RXFNEIF) {
            retval |= usbd_intf_rxfifo(pudev);
        }

        /* USB reset interrupt */
        if (int_status & GINTF_RST) {
            retval |= usbd_intf_reset(pudev);
        }

        /* enumeration has been finished interrupt */
        if (int_status & GINTF_ENUMF) {
            retval |= usbd_intf_enumfinish(pudev);
        }

        /* incomplete synchronization in transfer interrupt*/
        if (int_status & GINTF_ISOINCIF) {
            retval |= usbd_intf_isoinincomplete(pudev);
        }

        /* incomplete synchronization out transfer interrupt*/
        if (int_status & GINTF_ISOONCIF) {
            retval |= usbd_intf_isooutincomplete(pudev);
        }

#ifdef VBUS_SENSING_ENABLED

        /* session request interrupt */
        if (int_status & GINTF_SESIF) {
            retval |= usbd_intf_sessionrequest(pudev);
        }

        /* OTG mode interrupt */
        if (int_status & GINTF_OTGIF) {
            retval |= usbd_intf_otg(pudev);
        }
#endif /* VBUS_SENSING_ENABLED */
    }

    return retval;
}

/*!
    \brief      indicates that an OUT endpoint has a pending interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbd_intf_outep (usb_core_handle_struct *pudev)
{
    uint8_t endp_num = 0U;
    uint32_t endp_intr = 0U;

    __IO uint32_t out_endp_intr = 0U;

    /* read in the device interrupt bits */
    USB_DAOEP_INTR_READ(endp_intr);

    while (endp_intr) {
        if (endp_intr & 0x1U) {
            USB_DOEP_INTR_READ(out_endp_intr, (uint16_t)endp_num);

            /* transfer complete interrupt */
            if (out_endp_intr & DOEPINTF_TF) {
                USB_DOEPxINTF((uint16_t)endp_num) = DOEPINTF_TF;

                /* data receive is completed */
                usbd_out_transaction(pudev, endp_num);
            }

            /* endpoint disable interrupt */
            if (out_endp_intr & DOEPINTF_EPDIS) {
                USB_DOEPxINTF((uint16_t)endp_num) = DOEPINTF_EPDIS;
            }

            /* setup phase finished interrupt (just for control endpoints) */
            if (out_endp_intr & DOEPINTF_STPF) {
                /* setup phase is completed */
                usbd_setup_transaction(pudev);

                USB_DOEPxINTF((uint16_t)endp_num) = DOEPINTF_STPF;
            }

            /* back to back setup packets received */
            if (out_endp_intr & DOEPINTF_BTBSTP) {
                USB_DOEPxINTF((uint16_t)endp_num) = DOEPINTF_BTBSTP;
            }
        }

        endp_num ++;
        endp_intr >>= 1;
    }

    return 1U;
}

/*!
    \brief      indicates that an in endpoint has a pending interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbd_intf_inep(usb_core_handle_struct *pudev)
{
    uint8_t endp_num = 0U;
    uint32_t endp_intr = 0U;

    __IO uint32_t in_endp_intr = 0U;

    /* get all in endpoints which have interrupts */
    USB_DAIEP_INTR_READ(endp_intr);

    while (endp_intr) {
        if (endp_intr & 0x1U) {
            USB_DIEP_INTR_READ(in_endp_intr, (uint16_t)endp_num);

            if (in_endp_intr & DIEPINTF_TF) {
                /* disable the fifo empty interrupt for the endpoint */
                USB_DIEPFEINTEN &= ~(0x1U << endp_num);

                USB_DIEPxINTF((uint16_t)endp_num) = DIEPINTF_TF;

                /* data transmittion is completed */
                usbd_in_transaction(pudev, endp_num);
            }

            if (in_endp_intr & DIEPINTF_CITO) {
                USB_DIEPxINTF((uint16_t)endp_num) = DIEPINTF_CITO;
            }

            if (in_endp_intr & DIEPINTF_IEPNE) {
                USB_DIEPxINTF((uint16_t)endp_num) = DIEPINTF_IEPNE;
            }

            if (in_endp_intr & DIEPINTF_EPDIS) {
                USB_DIEPxINTF((uint16_t)endp_num) = DIEPINTF_EPDIS;
            }

            if (in_endp_intr & DIEPINTF_TXFE) {
                usbd_emptytxfifo_write(pudev, endp_num);
                USB_DIEPxINTF((uint16_t)endp_num) = DIEPINTF_TXFE;
            }
        }

        endp_num ++;
        endp_intr >>= 1;
    }

    return 1U;
}

/*!
    \brief      indicates that early suspend state has been detected on the USB
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbd_intf_earlysuspend (usb_core_handle_struct *pudev)
{
    USB_GINTEN &= ~GINTEN_ESPIE;
    USB_GINTF = GINTF_ESP;

    return 1U;
}

/*!
    \brief      indicates that suspend state has been detected on the USB
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbd_intf_suspend(usb_core_handle_struct *pudev)
{
    __IO uint8_t low_power = pudev->cfg.low_power;
    __IO uint8_t suspend = (uint8_t)(USB_DSTAT & DSTAT_SPST);
    __IO uint8_t is_configured = (pudev->dev.status == USB_STATUS_CONFIGURED)? 1U : 0U;

    pudev->dev.prev_status = pudev->dev.status;
    pudev->dev.status = USB_STATUS_SUSPENDED;

    if (low_power && suspend && is_configured) {
        /* switch-off the otg clocks */
        USB_PWRCLKCTL |= PWRCLKCTL_SUCLK | PWRCLKCTL_SHCLK;

        /* enter DEEP_SLEEP mode with LDO in low power mode */
        pmu_to_deepsleepmode(PMU_LDO_LOWPOWER, WFI_CMD);
    }

    /* clear interrupt */
    USB_GINTF = GINTF_SP;

    return 1U;
}

/*!
    \brief      indicates that the USB controller has detected a resume or remote Wake-up sequence
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbd_intf_resume (usb_core_handle_struct *pudev)
{
    pudev->dev.status = pudev->dev.prev_status;
    pudev->dev.status = USB_STATUS_CONFIGURED;

    /* clear interrupt */
    USB_GINTF = GINTF_WKUPIF;

    return 1U;
}

/*!
    \brief      handle the SOF interrupts
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbd_intf_sof(usb_core_handle_struct *pudev)
{
    if (NULL != usbd_int_fops) {
        usbd_int_fops->SOF(pudev);
    }

    USB_GINTF = GINTF_SOF;

    return 1U;
}

/*!
    \brief      handle the rx status queue level interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbd_intf_rxfifo (usb_core_handle_struct *pudev)
{
    usb_ep_struct *ep;
    uint8_t data_pid = 0U, endp_num = 0U;
    uint32_t bcount = 0U, packet_num = 0U;

    /* get the status from the top of the fifo (must be read to a variable) */
    __IO uint32_t rx_status = USB_GRSTATP;

    /* disable the rx fifo non-empty interrupt */
    USB_GINTEN &= ~GINTEN_RXFNEIE;

    endp_num = (uint8_t)(rx_status & GRSTATRP_EPNUM);
    bcount = (rx_status & GRSTATRP_BCOUNT) >> 4U;
    data_pid = (uint8_t)((rx_status & GRSTATRP_DPID) >> 15U);

    /* ensure no-DMA mode can work */
    packet_num = USB_DOEPxLEN((uint16_t)endp_num) & DEPLEN_PCNT;
    if ((1U == endp_num) && (0U == packet_num)) {
        uint32_t devepctl = USB_DOEPxCTL((uint16_t)endp_num);

        devepctl |= DEPCTL_SNAK;
        devepctl &= ~DEPCTL_EPEN;
        devepctl &= ~DEPCTL_EPD;

        USB_DOEPxCTL((uint16_t)endp_num) = devepctl;
    }

    ep = &pudev->dev.out_ep[endp_num];

    switch ((rx_status & GRSTATRP_RPCKST) >> 17U) {
        case RXSTAT_GOUT_NAK:
            break;
        case RXSTAT_DATA_UPDT:
            if (bcount > 0U) {
                usb_fifo_read(ep->xfer_buff, (uint16_t)bcount);
                ep->xfer_buff += bcount;
                ep->xfer_count += bcount;
            }
            break;
        case RXSTAT_XFER_COMP:
            break;
        case RXSTAT_SETUP_COMP:
            break;
        case RXSTAT_SETUP_UPDT:
            *(uint32_t *)0x5000081CU |= 0x00020000U;
            if ((0U == endp_num) && (8U == bcount) && (DPID_DATA0 == data_pid)) {
                /* copy the setup packet received in fifo into the setup buffer in ram */
                usb_fifo_read(pudev->dev.setup_packet, 8U);

                ep->xfer_count += bcount;
            }
            break;
        default:
            break;
    }

    /* enable the rx fifo non-empty interrupt */
    USB_GINTEN |= GINTEN_RXFNEIE;

    return 1U;
}

/*!
    \brief      handle USB reset interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     status
*/
static uint32_t usbd_intf_reset(usb_core_handle_struct *pudev)
{
    uint8_t i = 0U;
    usb_ep_struct *ep;

    /* clear the remote wakeup signaling */
    USB_DCTL &= ~DCTL_RWKUP;

    /* flush the tx fifo */
    usb_txfifo_flush(pudev, 0U);

    for (i = 0U; i < pudev->cfg.dev_endp_num; i++) {
        USB_DIEPxINTF((uint16_t)i) = 0xFFU;
        USB_DOEPxINTF((uint16_t)i) = 0xFFU;
    }

    /* clear all pending device endpoint interrupts */
    USB_DAEPINT = 0xFFFFFFFFU;

    /* enable endpoint 0 interrupts */
    USB_DAEPINTEN &= ~DAEPINTEN_OEPIE;
    USB_DAEPINTEN &= ~DAEPINTEN_IEPIE;
    USB_DAEPINTEN = (1U << 16) | 1U;

    /* enable out endpoint interrupts */
    USB_DOEPINTEN = DOEPINTEN_STPFEN | DOEPINTEN_TFEN | DOEPINTEN_EPDISEN;

    /* enable in endpoint interrupts */
    USB_DIEPINTEN = DIEPINTEN_TFEN | DIEPINTEN_CITOEN | DIEPINTEN_EPDISEN;

    /* reset device address */
    USB_DCFG &= ~DCFG_DAR;
    USB_DCFG |= 0U << 4U;

    /* configure endpoint 0 to receive setup packets */
    usb_ep0_startout(pudev);

    /* clear usb reset interrupt */
    USB_GINTF = GINTF_RST;

    /* open EP0 IN */
    ep = &pudev->dev.in_ep[0];

    USB_DIEPxCTL(0U) &= ~DEP0CTL_MPL;
    USB_DIEPxCTL(0U) &= ~DEPCTL_EPTYPE;
    USB_DIEPxCTL(0U) &= ~DIEPCTL_TXFNUM;

    if (!(USB_DIEPxCTL(0U) & DEP0CTL_EPACT)) {
        USB_DIEPxCTL(0U) |= USB_MAX_EP0_SIZE;
        USB_DIEPxCTL(0U) |= (USB_EPTYPE_CTRL << 18U);
        USB_DIEPxCTL(0U) |= DEP0CTL_EPACT;
    }

    ep->endp_mps = USB_MAX_EP0_SIZE;
    ep->endp_type = USB_EPTYPE_CTRL;

    /* open EP0 OUT */
    ep = &pudev->dev.out_ep[0];

    USB_DOEPxCTL(0U) &= ~DEP0CTL_MPL;
    USB_DOEPxCTL(0U) &= ~DEPCTL_EPTYPE;

    if (!(USB_DOEPxCTL(0U) & DEP0CTL_EPACT)) {
        USB_DOEPxCTL(0U) |= USB_MAX_EP0_SIZE;
        USB_DOEPxCTL(0U) |= (USB_EPTYPE_CTRL << 18U);
        USB_DOEPxCTL(0U) |= DEP0CTL_EPACT;
    }

    ep->endp_mps = USB_MAX_EP0_SIZE;
    ep->endp_type = USB_EPTYPE_CTRL;

    pudev->dev.status = USB_STATUS_DEFAULT;

    return 1U;
}

/*!
    \brief      handle enumeration finish interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     status
*/
static uint32_t usbd_intf_enumfinish(usb_core_handle_struct *pudev)
{
    uint8_t enum_speed = (uint8_t)((USB_DSTAT & DSTAT_ES) >> 1U);

    /* set the max packet size of devie in endpoint based on the enumeration speed */
    USB_DIEPxCTL(0U) |= EP0_MAXLEN[enum_speed];

    /* clear global in NAK */
    USB_DCTL &= ~DCTL_CGINAK;
    USB_DCTL |= DCTL_CGINAK;

    /* set USB turn-around time based on device speed and PHY interface */
    if (USB_SPEED_HIGH == USB_SPEED[enum_speed]) {
        pudev->cfg.core_speed = USB_CORE_SPEED_HIGH;
        pudev->cfg.max_packet_size = USBHS_MAX_PACKET_SIZE;

        USB_GUSBCS &= ~GUSBCS_UTT;
        USB_GUSBCS |= 0x09U << 10;
    } else {
        pudev->cfg.core_speed = USB_CORE_SPEED_FULL;
        pudev->cfg.max_packet_size = USBFS_MAX_PACKET_SIZE;

        USB_GUSBCS &= ~GUSBCS_UTT;
        USB_GUSBCS |= 0x05U << 10;
    }

    /* clear interrupt */
    USB_GINTF = GINTF_ENUMF;

    return 1U;
}

/*!
    \brief      handle the ISO in incomplete interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     status
*/
static uint32_t usbd_intf_isoinincomplete(usb_core_handle_struct *pudev)
{

    /* clear interrupt */
    USB_GINTF = GINTF_ISOINCIF;

    return 1U;
}

/*!
    \brief      handle the ISO OUT incomplete interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     status
*/
static uint32_t usbd_intf_isooutincomplete(usb_core_handle_struct *pudev)
{
    /* clear interrupt */
    USB_GINTF = GINTF_ISOONCIF;

    return 1U;
}

/*!
    \brief      check FIFO for the next packet to be loaded
    \param[in]  pudev: pointer to usb device instance
    \param[in]  ep_id: endpoint identifier which is in (0..3)
    \param[out] none
    \retval     status
*/
static uint32_t usbd_emptytxfifo_write(usb_core_handle_struct *pudev, uint8_t ep_num)
{
    uint32_t len = 0U, word_len = 0U, fifo_empty_mask = 0U;
    usb_ep_struct *ep;

    ep = &pudev->dev.in_ep[ep_num];
    len = ep->xfer_len - ep->xfer_count;

    if (len > ep->endp_mps) {
        len = ep->endp_mps;
    }

    word_len = (len + 3U) / 4U;

    while (((USB_DIEPxTFSTAT((uint16_t)ep_num) & DIEPTFSTAT_IEPTFS) > word_len) &&
            (ep->xfer_count < ep->xfer_len)) {
        /* write the FIFO */
        len = ep->xfer_len - ep->xfer_count;

        if (len > ep->endp_mps) {
            len = ep->endp_mps;
        }

        word_len = (len + 3U) / 4U;

        usb_fifo_write (ep->xfer_buff, ep_num, (uint16_t)len);

        ep->xfer_buff += len;
        ep->xfer_count += len;
        
        if(ep->xfer_len == ep->xfer_count) {
            fifo_empty_mask = 0x1U << ep_num;
            USB_DIEPFEINTEN &= ~fifo_empty_mask;
        }
    }

    return 1U;
}

#ifdef VBUS_SENSING_ENABLED

/*!
    \brief      indicates that the USB_OTG controller has detected a connection
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     status
*/
static uint32_t usbd_intf_sessionrequest(usb_core_handle_struct *pudev)
{
    pudev->dev.connection_status = 1U;

    /* clear the interrupt bit */
    USB_GINTF = GINTF_SESIF;

    return 1;
}

/*!
    \brief      indicates that the USB_OTG controller has detected an OTG event
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     status
*/
static uint32_t usbd_intf_otg(usb_core_handle_struct *pudev)
{
    if (USB_GOTGINTF & GOTGINTF_SESEND) {
        pudev->dev.class_deinit(pudev, 0);
        pudev->dev.connection_status = 0;
    }

    /* clear OTG interrupt */
    USB_GOTGINTF |= GOTGINTF_SESEND;

    return 1;
}

#endif /* VBUS_SENSING_ENABLED */
