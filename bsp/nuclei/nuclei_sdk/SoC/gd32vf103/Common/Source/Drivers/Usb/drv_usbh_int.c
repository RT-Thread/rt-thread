/*!
    \file  drv_usbh_int.c
    \brief USB host mode interrupt handler file

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

#include "drv_usb_core.h"
#include "drv_usb_host.h"
#include "drv_usbh_int.h"

#if defined (__GNUC__)        /*!< GNU compiler */
    #pragma GCC optimize ("O0")
#endif /* __GNUC__ */

static uint32_t usbh_int_port           (usb_core_driver *pudev);
static uint32_t usbh_int_pipe           (usb_core_driver *pudev);
static uint32_t usbh_int_pipe_in        (usb_core_driver *pudev, uint32_t pp_num);
static uint32_t usbh_int_pipe_out       (usb_core_driver *pudev, uint32_t pp_num);
static uint32_t usbh_int_rxfifonoempty  (usb_core_driver *pudev);
static uint32_t usbh_int_txfifoempty    (usb_core_driver *pudev, usb_pipe_mode pp_mode);

static inline void usb_pp_halt (usb_core_driver *pudev, 
                                uint8_t pp_num, 
                                uint32_t pp_int,
                                usb_pipe_staus pp_status)
{
    pudev->regs.pr[pp_num]->HCHINTEN |= HCHINTEN_CHIE;

    usb_pipe_halt(pudev, pp_num);

    pudev->regs.pr[pp_num]->HCHINTF = pp_int;

    pudev->host.pipe[pp_num].pp_status = pp_status;
}

/*!
    \brief      handle global host interrupt
    \param[in]  pudev: pointer to usb core instance
    \param[out] none
    \retval     operation status
*/
uint32_t usbh_isr (usb_core_driver *pudev)
{
    uint32_t Retval = 0U;

    __IO uint32_t intr = 0U;

    /* check if host mode */
    if (HOST_MODE == (pudev->regs.gr->GINTF & GINTF_COPM)) {
        intr = usb_coreintr_get(&pudev->regs);

        if (!intr) {
            return 0;
        }

        if (intr & GINTF_SOF) {
            usbh_int_fop->SOF(pudev);

            /* clear interrupt */
            pudev->regs.gr->GINTF = GINTF_SOF;
        }

        if (intr & GINTF_RXFNEIF) {
            Retval |= usbh_int_rxfifonoempty (pudev);
        }

        if (intr & GINTF_NPTXFEIF) {
            Retval |= usbh_int_txfifoempty (pudev, PIPE_NON_PERIOD);
        }

        if (intr & GINTF_PTXFEIF) {
            Retval |= usbh_int_txfifoempty (pudev, PIPE_PERIOD);
        }

        if (intr & GINTF_HCIF) {
            Retval |= usbh_int_pipe (pudev);
        }

        if (intr & GINTF_HPIF) {
            Retval |= usbh_int_port (pudev);
        }

        if (intr & GINTF_DISCIF) {
            pudev->host.connect_status = 0U;

            /* clear interrupt */
            pudev->regs.gr->GINTF = GINTF_DISCIF;
        }

        if (intr & GINTF_ISOONCIF) {
            pudev->regs.pr[0]->HCHCTL |= HCHCTL_CEN | HCHCTL_CDIS;

            /* clear interrupt */
            pudev->regs.gr->GINTF = GINTF_ISOONCIF;
        }
    }

    return Retval;
}

/*!
    \brief      handle all host channels interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbh_int_pipe (usb_core_driver *pudev)
{
    uint32_t pp_num = 0U;
    uint32_t retval = 0U;

    for (pp_num = 0U; pp_num < pudev->bp.num_pipe; pp_num++) {
        if ((pudev->regs.hr->HACHINT & HACHINT_HACHINT) & (1U << pp_num)) {
            if (pudev->regs.pr[pp_num]->HCHCTL & HCHCTL_EPDIR) {
                retval |= usbh_int_pipe_in (pudev, pp_num);
            } else {
                retval |= usbh_int_pipe_out (pudev, pp_num);
            }
        }
    }

    return retval;
}

/*!
    \brief      handle the TX FIFO empty interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbh_int_txfifoempty (usb_core_driver *pudev, usb_pipe_mode pp_mode)
{
    uint8_t pp_num = 0U;
    uint16_t word_count = 0U, len = 0U;
    __IO uint32_t *txfiforeg = 0U, txfifostate = 0U;

    if (PIPE_NON_PERIOD == pp_mode) {
        txfiforeg = &pudev->regs.gr->HNPTFQSTAT;
    } else if (PIPE_PERIOD == pp_mode) {
        txfiforeg = &pudev->regs.hr->HPTFQSTAT;
    } else {
        return 0U;
    }

    txfifostate = *txfiforeg;

    pp_num = (txfifostate & TFQSTAT_CNUM) >> 27U;

    word_count = (pudev->host.pipe[pp_num].xfer_len + 3U) / 4U;

    while (((txfifostate & TFQSTAT_TXFS) > word_count) && (0U != pudev->host.pipe[pp_num].xfer_len)) {
        len = (txfifostate & TFQSTAT_TXFS) * 4U;

        if (len > pudev->host.pipe[pp_num].xfer_len) {
            /* last packet */
            len = pudev->host.pipe[pp_num].xfer_len;

            if (PIPE_NON_PERIOD == pp_mode) {
                pudev->regs.gr->GINTEN &= ~GINTEN_NPTXFEIE;
            } else {
                pudev->regs.gr->GINTEN &= ~GINTEN_PTXFEIE;
            }
        }

        word_count = (pudev->host.pipe[pp_num].xfer_len + 3U) / 4U;
        usb_txfifo_write (&pudev->regs, pudev->host.pipe[pp_num].xfer_buf, pp_num, len);

        pudev->host.pipe[pp_num].xfer_buf += len;
        pudev->host.pipe[pp_num].xfer_len -= len;
        pudev->host.pipe[pp_num].xfer_count += len;

        txfifostate = *txfiforeg;
    }

    return 1;
}

/*!
    \brief      handle the host port interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbh_int_port (usb_core_driver *pudev)
{
    uint32_t retval = 0U;

    __IO uint32_t port_state = *pudev->regs.HPCS;

    /* clear the interrupt bits in GINTSTS */
    port_state &= ~(HPCS_PE | HPCS_PCD | HPCS_PEDC);

    /* port connect detected */
    if (*pudev->regs.HPCS & HPCS_PCD) {
        port_state |= HPCS_PCD;

        pudev->host.connect_status = 1U;

        retval |= 1U;
    }

    /* port enable changed */
    if (*pudev->regs.HPCS & HPCS_PEDC) {
        port_state |= HPCS_PEDC;

        if (*pudev->regs.HPCS & HPCS_PE) {
            uint32_t port_speed = usb_curspeed_get(pudev);
            uint32_t clock_type = pudev->regs.hr->HCTL & HCTL_CLKSEL;

            pudev->host.connect_status = 1U;

            if (PORT_SPEED_LOW == port_speed) {
                pudev->regs.hr->HFT = 6000U;

                if (HCTL_6MHZ != clock_type) {
                    if (USB_EMBEDDED_PHY == pudev->bp.phy_itf) {
                        usb_phyclock_config (pudev, HCTL_6MHZ);
                    }
                }
            } else if (PORT_SPEED_FULL == port_speed) {
                pudev->regs.hr->HFT = 48000U;

                if (HCTL_48MHZ != clock_type) {
                    usb_phyclock_config (pudev, HCTL_48MHZ);
                }
            } else {
                /* for high speed device and others */
            }

            pudev->host.port_enabled = 1U;

            pudev->regs.gr->GINTEN |= GINTEN_DISCIE;
        } else {
            pudev->host.port_enabled = 0U;
        }
    }

    /* clear port interrupts */
    *pudev->regs.HPCS = port_state;

    return retval;
}

/*!
    \brief      handle the OUT channel interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[in]  pp_num: host channel number which is in (0..7)
    \param[out] none
    \retval     operation status
*/
uint32_t usbh_int_pipe_out (usb_core_driver *pudev, uint32_t pp_num)
{
    usb_pr *pp_reg = pudev->regs.pr[pp_num];

    usb_pipe *pp = &pudev->host.pipe[pp_num];

    uint32_t intr_pp = pp_reg->HCHINTF & pp_reg->HCHINTEN;

    if (intr_pp & HCHINTF_ACK) {
        pp_reg->HCHINTF = HCHINTF_ACK;
    } else if (intr_pp & HCHINTF_STALL) {
        usb_pp_halt (pudev, pp_num, HCHINTF_STALL, PIPE_STALL);
    } else if (intr_pp & HCHINTF_DTER) {
        usb_pp_halt (pudev, pp_num, HCHINTF_DTER, PIPE_DTGERR);
        pp_reg->HCHINTF = HCHINTF_NAK;
    } else if (intr_pp & HCHINTF_REQOVR) {
        usb_pp_halt (pudev, pp_num, HCHINTF_REQOVR, PIPE_REQOVR);
    } else if (intr_pp & HCHINTF_TF) {
        pp->err_count = 0U;
        usb_pp_halt (pudev, pp_num, HCHINTF_TF, PIPE_XF);
    } else if (intr_pp & HCHINTF_NAK) {
        pp->err_count = 0U;
        usb_pp_halt (pudev, pp_num, HCHINTF_NAK, PIPE_NAK);
    } else if (intr_pp & HCHINTF_USBER) {
        pp->err_count++;
        usb_pp_halt (pudev, pp_num, HCHINTF_USBER, PIPE_TRACERR);
    } else if (intr_pp & HCHINTF_NYET) {
        pp->err_count = 0U;
        usb_pp_halt (pudev, pp_num, HCHINTF_NYET, PIPE_NYET);
    } else if (intr_pp & HCHINTF_CH) {
        pudev->regs.pr[pp_num]->HCHINTEN &= ~HCHINTEN_CHIE;

        switch (pp->pp_status) {
        case PIPE_XF:
            pp->urb_state = URB_DONE;

            if (USB_EPTYPE_BULK == ((pp_reg->HCHCTL & HCHCTL_EPTYPE) >> 18U)) {
                pp->data_toggle_out ^= 1U; 
            }
            break;

        case PIPE_NAK:
            pp->urb_state = URB_NOTREADY;
            break;

        case PIPE_NYET:
            if (1U == pudev->host.pipe[pp_num].ping) {
                usb_pipe_ping (pudev, pp_num);
            }

            pp->urb_state = URB_NOTREADY;
            break;

        case PIPE_STALL:
            pp->urb_state = URB_STALL;
            break;

        case PIPE_TRACERR:
            if (3U == pp->err_count) {
                pp->urb_state = URB_ERROR;
                pp->err_count = 0U;
            }
            break;

        default:
            break;
        }

        pp_reg->HCHINTF = HCHINTF_CH;
    }

    return 1;
}

/*!
    \brief      handle the IN channel interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[in]  pp_num: host channel number which is in (0..7)
    \param[out] none
    \retval     operation status
*/
uint32_t usbh_int_pipe_in (usb_core_driver *pudev, uint32_t pp_num)
{
    usb_pr *pp_reg = pudev->regs.pr[pp_num];

    usb_pipe *pp = &pudev->host.pipe[pp_num];

    __IO uint32_t intr_pp = pp_reg->HCHINTF & pp_reg->HCHINTEN;

    uint8_t ep_type = (pp_reg->HCHCTL & HCHCTL_EPTYPE) >> 18U;

    if (intr_pp & HCHINTF_ACK) {
        pp_reg->HCHINTF = HCHINTF_ACK;
    } else if (intr_pp & HCHINTF_STALL) {
        usb_pp_halt (pudev, pp_num, HCHINTF_STALL, PIPE_STALL);
        pp_reg->HCHINTF = HCHINTF_NAK;

        /* note: When there is a 'STALL', reset also nak,
           else, the pudev->host.pp_status = HC_STALL
           will be overwritten by 'NAK' in code below */
        intr_pp &= ~HCHINTF_NAK;
    } else if (intr_pp & HCHINTF_DTER) {
        usb_pp_halt (pudev, pp_num, HCHINTF_DTER, PIPE_DTGERR);
        pp_reg->HCHINTF = HCHINTF_NAK;
    }

    if (intr_pp & HCHINTF_REQOVR) {
        usb_pp_halt (pudev, pp_num, HCHINTF_REQOVR, PIPE_REQOVR);
    } else if (intr_pp & HCHINTF_TF) {
        if (USB_USE_DMA == pudev->bp.transfer_mode) {
            pudev->host.backup_xfercount[pp_num] = pp->xfer_len - pp_reg->HCHLEN & HCHLEN_TLEN;
        }

        pp->pp_status = PIPE_XF;
        pp->err_count = 0U;

        pp_reg->HCHINTF = HCHINTF_TF;

        switch (ep_type) {
        case USB_EPTYPE_CTRL:
        case USB_EPTYPE_BULK:
            usb_pp_halt (pudev, pp_num, HCHINTF_NAK, PIPE_XF);

            pp->data_toggle_in ^= 1U;
            break;

        case USB_EPTYPE_INTR:
            pp_reg->HCHCTL |= HCHCTL_ODDFRM;
            pp->urb_state = URB_DONE;
            break;

        default:
            break;
        }
    } else if (intr_pp & HCHINTF_CH) {
        pp_reg->HCHINTEN &= ~HCHINTEN_CHIE;

        switch (pp->pp_status) {
        case PIPE_XF:
            pp->urb_state = URB_DONE;
            break;

        case PIPE_STALL:
            pp->urb_state = URB_STALL;
            break;

        case PIPE_TRACERR:
        case PIPE_DTGERR:
            pp->err_count = 0U;
            pp->urb_state = URB_ERROR;
            break;

        default:
            if(USB_EPTYPE_INTR == ep_type) {
                pp->data_toggle_in ^= 1U;
            }
            break;
        }

        pp_reg->HCHINTF = HCHINTF_CH;
    } else if (intr_pp & HCHINTF_BBER) {
        pp->err_count++;
        usb_pp_halt (pudev, pp_num, HCHINTF_BBER, PIPE_TRACERR);
    } else if (intr_pp & HCHINTF_NAK) {
        switch (ep_type) {
        case USB_EPTYPE_CTRL:
        case USB_EPTYPE_BULK:
            /* re-activate the channel */
            pp_reg->HCHCTL = (pp_reg->HCHCTL | HCHCTL_CEN) & ~HCHCTL_CDIS;
            break;

        case USB_EPTYPE_INTR:
            pp_reg->HCHINTEN |= HCHINTEN_CHIE;

            usb_pipe_halt(pudev, pp_num);
            break;

        default:
            break;
        }

        pp->pp_status = PIPE_NAK;

        pp_reg->HCHINTF = HCHINTF_NAK;
    }

    return 1;
}

/*!
    \brief      handle the rx fifo non-empty interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbh_int_rxfifonoempty (usb_core_driver *pudev)
{
    uint32_t count = 0U;

    __IO uint8_t pp_num = 0U;
    __IO uint32_t rx_stat = 0U;

    /* disable the rx status queue level interrupt */
    pudev->regs.gr->GINTEN &= ~GINTEN_RXFNEIE;

    rx_stat = pudev->regs.gr->GRSTATP;
    pp_num = rx_stat & GRSTATRP_CNUM;

    switch ((rx_stat & GRSTATRP_RPCKST) >> 17U) {
        case GRXSTS_PKTSTS_IN:
            count = (rx_stat & GRSTATRP_BCOUNT) >> 4U;

            /* read the data into the host buffer. */
            if ((count > 0U) && (NULL != pudev->host.pipe[pp_num].xfer_buf)) {
                usb_rxfifo_read (&pudev->regs, pudev->host.pipe[pp_num].xfer_buf, count);

                /* manage multiple transfer packet */
                pudev->host.pipe[pp_num].xfer_buf += count;
                pudev->host.pipe[pp_num].xfer_count += count;

                pudev->host.backup_xfercount[pp_num] = pudev->host.pipe[pp_num].xfer_count;

                if (pudev->regs.pr[pp_num]->HCHLEN & HCHLEN_PCNT) {
                    /* re-activate the channel when more packets are expected */
                    __IO uint32_t pp_ctl = pudev->regs.pr[pp_num]->HCHCTL;

                    pp_ctl |= HCHCTL_CEN;
                    pp_ctl &= ~HCHCTL_CDIS;

                    pudev->regs.pr[pp_num]->HCHCTL = pp_ctl;
                }
            }
            break;

        case GRXSTS_PKTSTS_IN_XFER_COMP:
            break;

        case GRXSTS_PKTSTS_DATA_TOGGLE_ERR:
            count = (rx_stat & GRSTATRP_BCOUNT) >> 4U;

            while (count > 0U) {
                rx_stat = pudev->regs.gr->GRSTATP;
                count--;
            }
            break;

        case GRXSTS_PKTSTS_CH_HALTED:
            break;

        default:
            break;
    }

    /* enable the rx status queue level interrupt */
    pudev->regs.gr->GINTEN |= GINTEN_RXFNEIE;

    return 1;
}
