/*!
    \file    drv_usb_host.c
    \brief   USB host mode low level driver

    \version 2020-08-04, V1.1.0, firmware for GD32VF103
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

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

#include "drv_usb_hw.h"
#include "drv_usb_core.h"
#include "drv_usb_host.h"

const uint32_t PIPE_DPID[2] = {
    PIPE_DPID_DATA0,
    PIPE_DPID_DATA1
};

/*!
    \brief      initializes USB core for host mode
    \param[in]  pudev: pointer to selected usb host
    \param[out] none
    \retval     operation status
*/
usb_status usb_host_init (usb_core_driver *pudev)
{
    uint32_t i = 0U, inten = 0U;

    uint32_t nptxfifolen = 0U;
    uint32_t ptxfifolen = 0U;

    /* restart the PHY Clock */
    *pudev->regs.PWRCLKCTL = 0U;

    /* support FS/LS only */
    pudev->regs.hr->HCTL &= ~HCTL_SPDFSLS;

    /* configure data FIFOs size */
#ifdef USB_FS_CORE
    if (USB_CORE_ENUM_FS == pudev->bp.core_enum) {
        /* set Rx FIFO size */
        pudev->regs.gr->GRFLEN = USB_RX_FIFO_FS_SIZE;

        /* set non-periodic Tx FIFO size and address */
        nptxfifolen |= USB_RX_FIFO_FS_SIZE;
        nptxfifolen |= USB_HTX_NPFIFO_FS_SIZE << 16U;
        pudev->regs.gr->DIEP0TFLEN_HNPTFLEN = nptxfifolen;

        /* set periodic Tx FIFO size and address */
        ptxfifolen |= USB_RX_FIFO_FS_SIZE + USB_HTX_NPFIFO_FS_SIZE;
        ptxfifolen |= USB_HTX_PFIFO_FS_SIZE << 16U;
        pudev->regs.gr->HPTFLEN = ptxfifolen;
    }
#endif /* USB_FS_CORE */

#ifdef USE_OTG_MODE

    /* clear host set hnp enable in the usb_otg control register */
    pudev->regs.gr->GOTGCS &= ~GOTGCS_HHNPEN;

#endif /* USE_OTG_MODE */

    /* make sure the FIFOs are flushed */

    /* flush all Tx FIFOs in device or host mode */
    usb_txfifo_flush (&pudev->regs, 0x10U);

    /* flush the entire Rx FIFO */
    usb_rxfifo_flush (&pudev->regs);

    /* disable all interrupts */
    pudev->regs.gr->GINTEN = 0U;

    /* clear any pending USB OTG interrupts */
    pudev->regs.gr->GOTGINTF = 0xFFFFFFFFU;

    /* enable the USB wakeup and suspend interrupts */
    pudev->regs.gr->GINTF = 0xBFFFFFFFU;

    /* clear all pending host channel interrupts */
    for (i = 0U; i < pudev->bp.num_pipe; i++) {
        pudev->regs.pr[i]->HCHINTF = 0xFFFFFFFFU;
        pudev->regs.pr[i]->HCHINTEN = 0U;
    }

#ifndef USE_OTG_MODE
    usb_portvbus_switch (pudev, 1U);
#endif /* USE_OTG_MODE */

    pudev->regs.gr->GINTEN = GINTEN_WKUPIE | GINTEN_SPIE;

    /* enable host_mode-related interrupts */
    if (USB_USE_FIFO == pudev->bp.transfer_mode) {
        inten = GINTEN_RXFNEIE;
    }

    inten |= GINTEN_SESIE | GINTEN_HPIE | GINTEN_HCIE | GINTEN_ISOINCIE;

    pudev->regs.gr->GINTEN |= inten;

    inten = GINTEN_DISCIE | GINTEN_SOFIE;

    pudev->regs.gr->GINTEN &= ~inten;

    return USB_OK;
}

/*!
    \brief      control the VBUS to power
    \param[in]  pudev: pointer to selected usb host
    \param[in]  state: VBUS state
    \param[out] none
    \retval     none
*/
void usb_portvbus_switch (usb_core_driver *pudev, uint8_t state)
{
    uint32_t port = 0U;

    /* enable or disable the external charge pump */
    usb_vbus_drive (state);

    /* turn on the host port power. */
    port = usb_port_read (pudev);

    if (!(port & HPCS_PP) && (1U == state)) {
        port |= HPCS_PP;
    }

    if ((port & HPCS_PP) && (0U == state)) {
        port &= ~HPCS_PP;
    }

    *pudev->regs.HPCS = port;

    usb_mdelay (200U);
}

/*!
    \brief      reset host port
    \param[in]  pudev: pointer to usb device
    \param[out] none
    \retval     operation status
*/
uint32_t usb_port_reset (usb_core_driver *pudev)
{
    __IO uint32_t port = usb_port_read (pudev);

    *pudev->regs.HPCS = port | HPCS_PRST;

    usb_mdelay(20U); /* see note */

    *pudev->regs.HPCS = port & ~HPCS_PRST;

    usb_mdelay(20U);

    return 1U;
}

/*!
    \brief      initialize host pipe
    \param[in]  pudev: pointer to usb device
    \param[in]  pipe_num: host pipe number which is in (0..7)
    \param[out] none
    \retval     operation status
*/
usb_status usb_pipe_init (usb_core_driver *pudev, uint8_t pipe_num)
{
    usb_status status = USB_OK;

    __IO uint32_t pp_ctl = 0U;
    __IO uint32_t pp_inten = HCHINTEN_TFIE;

    usb_pipe *pp = &pudev->host.pipe[pipe_num];

    /* clear old interrupt conditions for this host channel */
    pudev->regs.pr[pipe_num]->HCHINTF = 0xFFFFFFFFU;

    if (USB_USE_DMA == pudev->bp.transfer_mode) {
        pp_inten |= HCHINTEN_DMAERIE;
    }

    if (pp->ep.dir) {
        pp_inten |= HCHINTEN_BBERIE;
    }

    /* enable channel interrupts required for this transfer */
    switch (pp->ep.type) {
    case USB_EPTYPE_CTRL:
    case USB_EPTYPE_BULK:
        pp_inten |= HCHINTEN_STALLIE | HCHINTEN_USBERIE \
                    | HCHINTEN_DTERIE | HCHINTEN_NAKIE;

        if (!pp->ep.dir) {
            pp_inten |= HCHINTEN_NYETIE;

            if (pp->ping) {
                pp_inten |= HCHINTEN_ACKIE;
            }
        }
        break;

    case USB_EPTYPE_INTR:
        pp_inten |= HCHINTEN_STALLIE | HCHINTEN_USBERIE | HCHINTEN_DTERIE \
                     | HCHINTEN_NAKIE | HCHINTEN_REQOVRIE;
        break;

    case USB_EPTYPE_ISOC:
        pp_inten |= HCHINTEN_REQOVRIE | HCHINTEN_ACKIE;

        if (pp->ep.dir) {
            pp_inten |= HCHINTEN_USBERIE;
        }
        break;

    default:
        break;
    }

    pudev->regs.pr[pipe_num]->HCHINTEN = pp_inten;

    /* enable the top level host channel interrupt */
    pudev->regs.hr->HACHINTEN |= 1U << pipe_num;

    /* make sure host channel interrupts are enabled */
    pudev->regs.gr->GINTEN |= GINTEN_HCIE;

    /* program the host channel control register */
    pp_ctl |= PIPE_CTL_DAR(pp->dev_addr);
    pp_ctl |= PIPE_CTL_EPNUM(pp->ep.num);
    pp_ctl |= PIPE_CTL_EPDIR(pp->ep.dir);
    pp_ctl |= PIPE_CTL_EPTYPE(pp->ep.type);
    pp_ctl |= PIPE_CTL_LSD(pp->dev_speed == PORT_SPEED_LOW);

    pp_ctl |= pp->ep.mps;
    pp_ctl |= ((uint32_t)(pp->ep.type == USB_EPTYPE_INTR) << 29U) & HCHCTL_ODDFRM;

    pudev->regs.pr[pipe_num]->HCHCTL = pp_ctl;

    return status;
}

/*!
    \brief      prepare host channel for transferring packets
    \param[in]  pudev: pointer to usb device
    \param[in]  pipe_num: host pipe number which is in (0..7)
    \param[out] none
    \retval     operation status
*/
usb_status usb_pipe_xfer (usb_core_driver *pudev, uint8_t pipe_num)
{
    usb_status status = USB_OK;

    uint16_t dword_len = 0U;
    uint16_t packet_count = 0U;

    __IO uint32_t pp_ctl = 0U;

    usb_pipe *pp = &pudev->host.pipe[pipe_num];

    uint16_t max_packet_len = pp->ep.mps;

    /* compute the expected number of packets associated to the transfer */
    if (pp->xfer_len > 0U) {
        packet_count = (uint16_t)((pp->xfer_len + max_packet_len - 1U) / max_packet_len);

        if (packet_count > HC_MAX_PACKET_COUNT) {
            packet_count = HC_MAX_PACKET_COUNT;
            pp->xfer_len = (uint16_t)(packet_count * max_packet_len);
        }
    } else {
        packet_count = 1U;
    }

    if (pp->ep.dir) {
        pp->xfer_len = (uint16_t)(packet_count * max_packet_len);
    }

    /* initialize the host channel transfer information */
    pudev->regs.pr[pipe_num]->HCHLEN = pp->xfer_len | pp->DPID | PIPE_XFER_PCNT(packet_count);

    if (USB_USE_DMA == pudev->bp.transfer_mode) {
        pudev->regs.pr[pipe_num]->HCHDMAADDR = (unsigned int)pp->xfer_buf;
    }

    pp_ctl = pudev->regs.pr[pipe_num]->HCHCTL;

    if (usb_frame_even(pudev)) {
        pp_ctl |= HCHCTL_ODDFRM;
    } else {
        pp_ctl &= ~HCHCTL_ODDFRM;
    }

    /* set host channel enabled */
    pp_ctl |= HCHCTL_CEN;
    pp_ctl &= ~HCHCTL_CDIS;

    pudev->regs.pr[pipe_num]->HCHCTL = pp_ctl;

    if (USB_USE_FIFO == pudev->bp.transfer_mode) {
        if ((0U == pp->ep.dir) && (pp->xfer_len > 0U)) {
            switch (pp->ep.type) {
            /* non-periodic transfer */
            case USB_EPTYPE_CTRL:
            case USB_EPTYPE_BULK:
                dword_len = (uint16_t)((pp->xfer_len + 3U) / 4U);

                /* check if there is enough space in fifo space */
                if (dword_len > (pudev->regs.gr->HNPTFQSTAT & HNPTFQSTAT_NPTXFS)) {
                    /* need to process data in nptxfempty interrupt */
                    pudev->regs.gr->GINTEN |= GINTEN_NPTXFEIE;
                }
                break;

            /* periodic transfer */
            case USB_EPTYPE_INTR:
            case USB_EPTYPE_ISOC:
                dword_len = (uint16_t)((pp->xfer_len + 3U) / 4U);

                /* check if there is enough space in fifo space */
                if (dword_len > (pudev->regs.hr->HPTFQSTAT & HPTFQSTAT_PTXFS)) {
                    /* need to process data in ptxfempty interrupt */
                    pudev->regs.gr->GINTEN |= GINTEN_PTXFEIE;
                }
                break;

            default:
                break;
            }

            /* write packet into the tx fifo. */
            usb_txfifo_write (&pudev->regs, pp->xfer_buf, pipe_num, (uint16_t)pp->xfer_len);
        }
    }

    return status;
}

/*!
    \brief      halt pipe
    \param[in]  pudev: pointer to usb device
    \param[in]  pipe_num: host pipe number which is in (0..7)
    \param[out] none
    \retval     operation status
*/
usb_status usb_pipe_halt (usb_core_driver *pudev, uint8_t pipe_num)
{
    __IO uint32_t pp_ctl = pudev->regs.pr[pipe_num]->HCHCTL;

    uint8_t ep_type = (uint8_t)((pp_ctl & HCHCTL_EPTYPE) >> 18U);

    pp_ctl |= HCHCTL_CEN | HCHCTL_CDIS;

    switch (ep_type) {
    case USB_EPTYPE_CTRL:
    case USB_EPTYPE_BULK:
        if (0U == (pudev->regs.gr->HNPTFQSTAT & HNPTFQSTAT_NPTXFS)) {
            pp_ctl &= ~HCHCTL_CEN;
        }
        break;

    case USB_EPTYPE_INTR:
    case USB_EPTYPE_ISOC:
        if (0U == (pudev->regs.hr->HPTFQSTAT & HPTFQSTAT_PTXFS)) {
            pp_ctl &= ~HCHCTL_CEN;
        }
        break;

    default:
        break;
    }

    pudev->regs.pr[pipe_num]->HCHCTL = pp_ctl;

    return USB_OK;
}

/*!
    \brief      configure host pipe to do ping operation
    \param[in]  pudev: pointer to usb device
    \param[in]  pipe_num: host pipe number which is in (0..7)
    \param[out] none
    \retval     operation status
*/
usb_status usb_pipe_ping (usb_core_driver *pudev, uint8_t pipe_num)
{
    uint32_t pp_ctl = 0U;

    pudev->regs.pr[pipe_num]->HCHLEN = HCHLEN_PING | (HCHLEN_PCNT & (1U << 19U));

    pp_ctl = pudev->regs.pr[pipe_num]->HCHCTL;

    pp_ctl |= HCHCTL_CEN;
    pp_ctl &= ~HCHCTL_CDIS;

    pudev->regs.pr[pipe_num]->HCHCTL = pp_ctl;

    return USB_OK;
}

/*!
    \brief      stop the USB host and clean up FIFO
    \param[in]  pudev: pointer to usb device
    \param[out] none
    \retval     none
*/
void usb_host_stop (usb_core_driver *pudev)
{
    uint32_t i;
    __IO uint32_t pp_ctl = 0U;

    pudev->regs.hr->HACHINTEN = 0x0U;
    pudev->regs.hr->HACHINT = 0xFFFFFFFFU;

    /* flush out any leftover queued requests. */
    for (i = 0U; i < pudev->bp.num_pipe; i++) {
        pp_ctl = pudev->regs.pr[i]->HCHCTL;

        pp_ctl &= ~(HCHCTL_CEN | HCHCTL_EPDIR);
        pp_ctl |= HCHCTL_CDIS;

        pudev->regs.pr[i]->HCHCTL = pp_ctl;
    }

    /* flush the FIFO */
    usb_rxfifo_flush (&pudev->regs);
    usb_txfifo_flush (&pudev->regs, 0x10U);
}
