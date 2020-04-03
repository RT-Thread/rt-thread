/*!
    \file  drv_usbd_int.c
    \brief USB device mode interrupt routines

    \version 2019-6-5, V1.0.0, firmware for GD32 USBFS&USBHS
*/

/*
    Copyright (c) 2019, GigaDevice Semiconductor Inc.

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
#include "gd32vf103_libopt.h"
//#include "usbd_conf.h"
#include "drv_usbd_int.h"
#include "usbd_transc.h"

static uint32_t usbd_int_epout                 (usb_core_driver *udev);
static uint32_t usbd_int_epin                  (usb_core_driver *udev);
static uint32_t usbd_int_rxfifo                (usb_core_driver *udev);
static uint32_t usbd_int_reset                 (usb_core_driver *udev);
static uint32_t usbd_int_enumfinish            (usb_core_driver *udev);
static uint32_t usbd_int_suspend               (usb_core_driver *udev);

static uint32_t usbd_emptytxfifo_write         (usb_core_driver *udev, uint32_t ep_num);

static const uint8_t USB_SPEED[4] = {
    [DSTAT_EM_HS_PHY_30MHZ_60MHZ] = USB_SPEED_HIGH,
    [DSTAT_EM_FS_PHY_30MHZ_60MHZ] = USB_SPEED_FULL,
    [DSTAT_EM_FS_PHY_48MHZ] = USB_SPEED_FULL,
    [DSTAT_EM_LS_PHY_6MHZ] = USB_SPEED_LOW
};

__IO uint8_t setupc_flag = 0U;

#ifdef USB_OTG_HS_DEDICATED_EP1_ENABLED

/*!
    \brief      USB dedicated OUT endpoint 1 interrupt service routine handler
    \param[in]  udev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
uint32_t USBD_OTG_EP1OUT_ISR_Handler (usb_core_driver *udev)
{
    uint32_t oepintr = 0U;
    uint32_t oeplen = 0U;

    oepintr = udev->regs.er_out[1]->DOEPINTF;
    oepintr &= udev->regs.dr->DOEP1INTEN;

    /* Transfer complete */
    if (oepintr & DOEPINTF_TF)
    {
        /* Clear the bit in DOEPINTn for this interrupt */
        udev->regs.er_out[1]->DOEPINTF = DOEPINTF_TF;

        if (USB_USE_DMA == udev->bp.transfer_mode)
        {
            oeplen = udev->regs.er_out[1]->DOEPLEN;

            /* ToDo : handle more than one single MPS size packet */
            udev->dev.transc_out[1].xfer_count = udev->dev.transc_out[1].usb_transc - \
                                    oeplen & DEPLEN_TLEN;
        }

        /* RX COMPLETE */
        USBD_DCD_INT_fops->DataOutStage(udev, 1);
    }

    return 1;
}

/*!
    \brief      USB dedicated IN endpoint 1 interrupt service routine handler
    \param[in]  udev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
uint32_t USBD_OTG_EP1IN_ISR_Handler (usb_core_driver *udev)
{
    uint32_t inten, intr, emptyen;

    inten = udev->regs.dr->DIEP1INTEN;
    emptyen = udev->regs.dr->DIEPFEINTEN;

    inten |= ((emptyen >> 1 ) & 0x1) << 7;

    intr = udev->regs.er_in[1]->DIEPINTF & inten;

    if (intr & DIEPINTF_TF)
    {
        udev->regs.dr->DIEPFEINTEN &= ~(0x1 << 1);

        udev->regs.er_in[1]->DIEPINTF = DIEPINTF_TF;

        /* TX COMPLETE */
        USBD_DCD_INT_fops->DataInStage(udev, 1);
    }

    if (intr & DIEPINTF_TXFE)
    {
        DCD_WriteEmptyTxFifo(udev, 1);

        udev->regs.er_in[1]->DIEPINTF = DIEPINTF_TXFE;
    }

    return 1;
}

#endif


/*!
    \brief      USB device-mode interrupts global service routine handler
    \param[in]  udev: pointer to usb device instance
    \param[out] none
    \retval     none
*/
void usbd_isr (usb_core_driver *udev)
{
    if (HOST_MODE != (udev->regs.gr->GINTF & GINTF_COPM)) {
        uint32_t intr = udev->regs.gr->GINTF & udev->regs.gr->GINTEN;

        /* there are no interrupts, avoid spurious interrupt */
        if (!intr) {
            return;
        }

        /* OUT endpoints interrupts */
        if (intr & GINTF_OEPIF) {
            usbd_int_epout (udev);
        }

        /* IN endpoints interrupts */
        if (intr & GINTF_IEPIF) {
            usbd_int_epin (udev);
        }

        /* suspend interrupt */
        if (intr & GINTF_SP) {
            usbd_int_suspend (udev);
        }

        /* wakeup interrupt */
        if (intr & GINTF_WKUPIF) {
            /* inform upper layer by the resume event */
            udev->dev.cur_status = udev->dev.backup_status;

            /* clear interrupt */
            udev->regs.gr->GINTF = GINTF_WKUPIF;
        }

        /* wakeup interrupt */
        if (intr & GINTF_MFIF) {

            /* clear interrupt */
            udev->regs.gr->GINTF = GINTF_MFIF;
        }

        /* start of frame interrupt */
        if (intr & GINTF_SOF) {
            if (udev->dev.class_core->SOF) {
                udev->dev.class_core->SOF(udev); 
            }

            if (0U != setupc_flag) {
                setupc_flag ++;

                if (setupc_flag >= 3U) {
                    usbd_setup_transc (udev);

                    setupc_flag = 0U;
                }
            }

            /* clear interrupt */
            udev->regs.gr->GINTF = GINTF_SOF;
        }

        /* receive FIFO not empty interrupt */
        if (intr & GINTF_RXFNEIF) {
            usbd_int_rxfifo (udev);
        }

        /* USB reset interrupt */
        if (intr & GINTF_RST) {
            usbd_int_reset (udev);
        }

        /* enumeration has been done interrupt */
        if (intr & GINTF_ENUMFIF) {
            usbd_int_enumfinish (udev);
        }

        /* incomplete synchronization IN transfer interrupt*/
        if (intr & GINTF_ISOINCIF) {
            if (NULL != udev->dev.class_core->incomplete_isoc_in) {
                udev->dev.class_core->incomplete_isoc_in(udev);
            }

            /* Clear interrupt */
            udev->regs.gr->GINTF = GINTF_ISOINCIF;
        }

        /* incomplete synchronization OUT transfer interrupt*/
        if (intr & GINTF_ISOONCIF) {
            if (NULL != udev->dev.class_core->incomplete_isoc_out) {
                udev->dev.class_core->incomplete_isoc_out(udev);
            }

            /* clear interrupt */
            udev->regs.gr->GINTF = GINTF_ISOONCIF;
        }

#ifdef VBUS_SENSING_ENABLED

        /* Session request interrupt */
        if (intr & GINTF_SESIF) {
            udev->regs.gr->GINTF = GINTF_SESIF;
        }

        /* OTG mode interrupt */
        if (intr & GINTF_OTGIF) {
            if(udev->regs.gr->GOTGINTF & GOTGINTF_SESEND) {

            }

            /* Clear OTG interrupt */
            udev->regs.gr->GINTF = GINTF_OTGIF;
        }
#endif
    }
}

/*!
    \brief      indicates that an OUT endpoint has a pending interrupt
    \param[in]  udev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbd_int_epout (usb_core_driver *udev)
{
    uint32_t epintnum = 0U;
    uint32_t ep_num = 0U;

    for (epintnum = usb_oepintnum_read (udev); epintnum; epintnum >>= 1, ep_num++) {
        if (epintnum & 0x1) {
            __IO uint32_t oepintr = usb_oepintr_read (udev, ep_num);

            /* transfer complete interrupt */
            if (oepintr & DOEPINTF_TF) {
                /* clear the bit in DOEPINTF for this interrupt */
                udev->regs.er_out[ep_num]->DOEPINTF = DOEPINTF_TF;

                if (USB_USE_DMA == udev->bp.transfer_mode) {
                    __IO uint32_t eplen = udev->regs.er_out[ep_num]->DOEPLEN;

                    udev->dev.transc_out[ep_num].xfer_count = udev->dev.transc_out[ep_num].max_len - \
                                                                eplen & DEPLEN_TLEN;
                }

                /* inform upper layer: data ready */
                usbd_out_transc (udev, ep_num);

                if (USB_USE_DMA == udev->bp.transfer_mode) {
                    if ((0U == ep_num) && (USB_CTL_STATUS_OUT == udev->dev.control.ctl_state)) {
                        usb_ctlep_startout (udev);
                    }
                }
            }

            /* setup phase finished interrupt (control endpoints) */
            if (oepintr & DOEPINTF_STPF) {
                /* inform the upper layer that a setup packet is available */
                if ((0U == ep_num) && (0U != setupc_flag)) {
                    usbd_setup_transc (udev);

                    setupc_flag = 0U;

                    udev->regs.er_out[ep_num]->DOEPINTF = DOEPINTF_STPF;
                }
            }
        }
    }

    return 1;
}

/*!
    \brief      indicates that an IN endpoint has a pending interrupt
    \param[in]  udev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbd_int_epin (usb_core_driver *udev)
{
    uint32_t epintnum = 0U;
    uint32_t ep_num = 0U;

    for (epintnum = usb_iepintnum_read (udev); epintnum; epintnum >>= 1, ep_num++) {
        if (epintnum & 0x1U) {
            __IO uint32_t iepintr = usb_iepintr_read (udev, ep_num);

            if (iepintr & DIEPINTF_TF) {
                udev->regs.er_in[ep_num]->DIEPINTF = DIEPINTF_TF;

                /* data transmittion is completed */
                usbd_in_transc (udev, ep_num);

                if (USB_USE_DMA == udev->bp.transfer_mode) {
                    if ((0U == ep_num) && (USB_CTL_STATUS_IN == udev->dev.control.ctl_state)) {
                        usb_ctlep_startout (udev);
                    }
                }
            }

            if (iepintr & DIEPINTF_TXFE) {
                usbd_emptytxfifo_write (udev, ep_num);

                udev->regs.er_in[ep_num]->DIEPINTF = DIEPINTF_TXFE;
            }
        }
    }

    return 1;
}

/*!
    \brief      handle the RX status queue level interrupt
    \param[in]  udev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbd_int_rxfifo (usb_core_driver *udev)
{
    usb_transc *transc = NULL;

    uint8_t data_PID = 0;
    uint32_t bcount = 0;

    __IO uint32_t devrxstat = 0;

    /* disable the Rx status queue non-empty interrupt */
    udev->regs.gr->GINTEN &= ~GINTEN_RXFNEIE;

    /* get the status from the top of the FIFO */
    devrxstat = udev->regs.gr->GRSTATP;

    transc = &udev->dev.transc_out[devrxstat & GRSTATRP_EPNUM];

    bcount = (devrxstat & GRSTATRP_BCOUNT) >> 4;
    data_PID = (devrxstat & GRSTATRP_DPID) >> 15;

    switch ((devrxstat & GRSTATRP_RPCKST) >> 17) {
        case RSTAT_GOUT_NAK:
            break;

        case RSTAT_DATA_UPDT:
            if (bcount > 0) {
                usb_rxfifo_read (&udev->regs, transc->xfer_buf, bcount);

                transc->xfer_buf += bcount;
                transc->xfer_count += bcount;
            }
            break;

        case RSTAT_XFER_COMP:
            /* trigger the OUT enpoint interrupt */
            break;

        case RSTAT_SETUP_COMP:
            /* trigger the OUT enpoint interrupt */
            break;

        case RSTAT_SETUP_UPDT:
            if ((transc->ep_addr.num == 0) && (bcount == 8) && (data_PID == DPID_DATA0)) {
                /* copy the setup packet received in FIFO into the setup buffer in RAM */
                usb_rxfifo_read (&udev->regs, (uint8_t *)&udev->dev.control.req, bcount);

                transc->xfer_count += bcount;

                setupc_flag = 1;
            }
            break;

        default:
            break;
    }

    /* enable the Rx status queue level interrupt */
    udev->regs.gr->GINTEN |= GINTEN_RXFNEIE;

    return 1;
}

/*!
    \brief      handle USB reset interrupt
    \param[in]  udev: pointer to usb device instance
    \param[out] none
    \retval     status
*/
static uint32_t usbd_int_reset (usb_core_driver *udev)
{
    uint32_t i;

    /* clear the remote wakeup signaling */
    udev->regs.dr->DCTL &= ~DCTL_RWKUP;

    /* flush the Tx FIFO */
    usb_txfifo_flush (&udev->regs, 0);

    for (i = 0; i < udev->bp.num_ep; i++) {
        udev->regs.er_in[i]->DIEPINTF = 0xFFU;
        udev->regs.er_out[i]->DOEPINTF = 0xFFU;
    }

    /* clear all pending device endpoint interrupts */
    udev->regs.dr->DAEPINT = 0xFFFFFFFFU;

    /* enable endpoint 0 interrupts */
    udev->regs.dr->DAEPINTEN = 1U | (1U << 16);

    /* enable OUT endpoint interrupts */
    udev->regs.dr->DOEPINTEN = DOEPINTEN_STPFEN | DOEPINTEN_TFEN;

    /* enable IN endpoint interrupts */
    udev->regs.dr->DIEPINTEN = DIEPINTEN_TFEN;

    /* reset device address */
    udev->regs.dr->DCFG &= ~DCFG_DAR;
    udev->dev.dev_addr = 0U;

    /* configure endpoint 0 to receive SETUP packets */
    usb_ctlep_startout (udev);

    /* clear USB reset interrupt */
    udev->regs.gr->GINTF = GINTF_RST;

    udev->dev.transc_out[0] = (usb_transc) {
        .ep_type = USB_EPTYPE_CTRL,
        .max_len = USB_FS_EP0_MAX_LEN
    };

    usb_transc_active (udev, &udev->dev.transc_out[0]);

    udev->dev.transc_in[0] = (usb_transc) {
        .ep_addr = {
            .dir = 1
        },

        .ep_type = USB_EPTYPE_CTRL,
        .max_len = USB_FS_EP0_MAX_LEN
    };

    usb_transc_active (udev, &udev->dev.transc_in[0]);

    /* upon reset call usr call back */
    udev->dev.cur_status = USBD_DEFAULT;

    return 1;
}

/*!
    \brief      handle USB speed enumeration finish interrupt
    \param[in]  udev: pointer to usb device instance
    \param[out] none
    \retval     status
*/
static uint32_t usbd_int_enumfinish (usb_core_driver *udev)
{
    uint8_t enum_speed = (uint8_t)((udev->regs.dr->DSTAT & DSTAT_ES) >> 1U);

    udev->regs.dr->DCTL &= ~DCTL_CGINAK;
    udev->regs.dr->DCTL |= DCTL_CGINAK;

    udev->regs.gr->GUSBCS &= ~GUSBCS_UTT;

    /* set USB turn-around time based on device speed and PHY interface */
    if (USB_SPEED[enum_speed] == USB_SPEED_HIGH) {
        udev->bp.core_speed = USB_SPEED_HIGH;

        udev->regs.gr->GUSBCS |= 0x09 << 10;
    } else {
        udev->bp.core_speed = USB_SPEED_FULL;

        udev->regs.gr->GUSBCS |= 0x05 << 10;
    }

    /* clear interrupt */
    udev->regs.gr->GINTF = GINTF_ENUMFIF;

    return 1;
}

/*!
    \brief      USB suspend interrupt handler
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbd_int_suspend (usb_core_driver *udev)
{
    __IO uint8_t low_power = udev->bp.low_power;
    __IO uint8_t suspend = (uint8_t)(udev->regs.dr->DSTAT & DSTAT_SPST);
    __IO uint8_t is_configured = (udev->dev.cur_status == USBD_CONFIGURED)? 1U : 0U;

    udev->dev.backup_status = udev->dev.cur_status;
    udev->dev.cur_status = USBD_SUSPENDED;

    if (low_power && suspend && is_configured) {
        /* switch-off the otg clocks */
        *udev->regs.PWRCLKCTL |= PWRCLKCTL_SUCLK | PWRCLKCTL_SHCLK;

        /* enter DEEP_SLEEP mode with LDO in low power mode */
        pmu_to_deepsleepmode(PMU_LDO_LOWPOWER, WFI_CMD);
    }

    /* clear interrupt */
    udev->regs.gr->GINTF = GINTF_SP;

    return 1U;
}

/*!
    \brief      check FIFO for the next packet to be loaded
    \param[in]  udev: pointer to usb device instance
    \param[in]  ep_num: endpoint identifier which is in (0..3)
    \param[out] none
    \retval     status
*/
static uint32_t usbd_emptytxfifo_write (usb_core_driver *udev, uint32_t ep_num)
{
    usb_transc *transc = NULL;

    uint32_t len = 0;
    uint32_t word_count = 0;

    transc = &udev->dev.transc_in[ep_num];

    len = transc->xfer_len - transc->xfer_count;

    /* get the data length to write */
    if (len > transc->max_len) {
        len = transc->max_len;
    }

    word_count = (len + 3) / 4;

    while (((udev->regs.er_in[ep_num]->DIEPTFSTAT & DIEPTFSTAT_IEPTFS) > word_count) && \
        (transc->xfer_count < transc->xfer_len)) {
        len = transc->xfer_len - transc->xfer_count;

        if (len > transc->max_len) {
            len = transc->max_len;
        }

        /* write FIFO in word(4bytes) */
        word_count = (len + 3) / 4;

        /* write the FIFO */
        usb_txfifo_write (&udev->regs, transc->xfer_buf, ep_num, len);

        transc->xfer_buf += len;
        transc->xfer_count += len;

        if (transc->xfer_count == transc->xfer_len) {
            /* disable the device endpoint FIFO empty interrupt */
            udev->regs.dr->DIEPFEINTEN &= ~(0x01 << ep_num);
        }
    }

    return 1;
}
