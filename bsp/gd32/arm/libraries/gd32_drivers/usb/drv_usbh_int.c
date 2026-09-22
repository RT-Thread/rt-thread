/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-11-07     RealThread   the first version
 */

#include "drv_usbh_int.h"
#include "drv_otghs_host.h"

#if defined(__CC_ARM)        /*!< ARM compiler */
#pragma O0
#elif defined(__GNUC__)        /*!< GNU compiler */
#pragma GCC optimize("O0")
#elif defined(__TASKING__)    /*!< TASKING compiler */
#pragma optimize = 0
#endif /* __CC_ARM */

#if defined(BSP_USING_USB) && defined(RT_USING_USB_HOST)

/* local function prototypes ('static') */
static uint32_t usbh_int_port(usb_core_driver *udev);
static uint32_t usbh_int_pipe(usb_core_driver *udev);
static uint32_t usbh_int_pipe_in(usb_core_driver *udev, uint32_t pp_num);
static uint32_t usbh_int_pipe_out(usb_core_driver *udev, uint32_t pp_num);
static uint32_t usbh_int_rxfifonoempty(usb_core_driver *udev);
static uint32_t usbh_int_txfifoempty(usb_core_driver *udev, usb_pipe_mode pp_mode);

/*!
    \brief      handle global host interrupt
    \param[in]  udev: pointer to USB core instance
    \param[out] none
    \retval     operation status
*/
uint32_t usbh_isr(usb_core_driver *udev)
{
    uint32_t retval = 0U;

    __IO uint32_t intr = 0U;

    /* check if host mode */
    if (HOST_MODE == (udev->regs.gr->GINTF & GINTF_COPM))
    {
        intr = usb_coreintr_get(&udev->regs);

        if (!intr)
        {
            return 0U;
        }

        if (intr & GINTF_SOF)
        {
            /* clear interrupt */
            udev->regs.gr->GINTF = GINTF_SOF;
        }

        if (intr & GINTF_RXFNEIF)
        {
            retval |= usbh_int_rxfifonoempty(udev);
        }

        if (intr & GINTF_NPTXFEIF)
        {
            retval |= usbh_int_txfifoempty(udev, PIPE_NON_PERIOD);
        }

        if (intr & GINTF_PTXFEIF)
        {
            retval |= usbh_int_txfifoempty(udev, PIPE_PERIOD);
        }

        if (intr & GINTF_HCIF)
        {
            retval |= usbh_int_pipe(udev);
        }

        if (intr & GINTF_HPIF)
        {
            retval |= usbh_int_port(udev);
        }

        if (intr & GINTF_WKUPIF)
        {
            /* clear interrupt */
            udev->regs.gr->GINTF = GINTF_WKUPIF;
        }

        if (intr & GINTF_DISCIF)
        {
            if ((*udev->regs.HPCS & HPCS_PCST) == 0)
            {
                usbh_disconnect_callback(udev);
            }

            /* clear interrupt */
            udev->regs.gr->GINTF = GINTF_DISCIF;
        }

        if (intr & GINTF_ISOONCIF)
        {
            udev->regs.pr[0]->HCHCTL |= HCHCTL_CEN | HCHCTL_CDIS;

            /* clear interrupt */
            udev->regs.gr->GINTF = GINTF_ISOONCIF;
        }
    }

    return retval;
}

/*!
    \brief      handle USB pipe halt
    \param[in]  udev: pointer to USB core instance
    \param[in]  pp_num: pp_num: host channel number which is in (0..7)
    \param[in]  pp_int: pipe interrupt
    \param[in]  pp_status: pipe status
    \param[out] none
    \retval     none
*/
static inline void usb_pp_halt(usb_core_driver *udev,
                               uint8_t pp_num,
                               uint32_t pp_int,
                               usb_pipe_status pp_status)
{
    udev->regs.pr[pp_num]->HCHINTEN |= HCHINTEN_CHIE;

    usb_pipe_halt(udev, pp_num);

    udev->regs.pr[pp_num]->HCHINTF = pp_int;

    udev->host.pipe[pp_num].pp_status = pp_status;
}

/*!
    \brief      handle the host port interrupt
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     operation status
*/
#if defined(__ICCARM__)      /*!< IAR compiler */
#pragma optimize = none
#endif /* __ICCARM */
static uint32_t usbh_int_port(usb_core_driver *udev)
{
    uint32_t retval = 0U;

    __IO uint32_t port_state = *udev->regs.HPCS;

    __IO uint32_t port_reset = 0U;

    /* clear the interrupt bit in GINTF */
    port_state &= ~(HPCS_PE | HPCS_PCD | HPCS_PEDC);

    /* port connect detected */
    if (*udev->regs.HPCS & HPCS_PCD)
    {
        port_state |= HPCS_PCD;

        if ((*udev->regs.HPCS & HPCS_PCST) == HPCS_PCST)
        {
            usbh_connect_callback(udev);
        }

        retval |= 1U;
    }

    /* port enable changed */
    if (*udev->regs.HPCS & HPCS_PEDC)
    {
        port_state |= HPCS_PEDC;

        if (*udev->regs.HPCS & HPCS_PE)
        {
            uint32_t port_speed = usb_curspeed_get(udev);

            udev->host.connect_status = 1U;

            if (PORT_SPEED_LOW == port_speed)
            {
                udev->regs.hr->HFT = 6000U;
            }
            else if (PORT_SPEED_FULL == port_speed)
            {
                udev->regs.hr->HFT = 48000U;
            }
            else
            {
                /* no operation */
            }

            port_reset = 1U;

            udev->regs.gr->GINTEN |= GINTEN_DISCIE | GINTEN_SOFIE;
        }
        else
        {
            /* no operation */
        }
    }

    if (1U == port_reset)
    {
        usb_port_reset(udev);
    }

    /* clear port interrupts */
    *udev->regs.HPCS = port_state;

    return retval;
}

/*!
    \brief      handle all host channels interrupt
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbh_int_pipe(usb_core_driver *udev)
{
    uint32_t pp_num = 0U;
    uint32_t retval = 0U;

    for (pp_num = 0U; pp_num < udev->bp.num_pipe; pp_num++)
    {
        if ((udev->regs.hr->HACHINT & HACHINT_HACHINT) & (1UL << pp_num))
        {
            if (udev->regs.pr[pp_num]->HCHCTL & HCHCTL_EPDIR)
            {
                retval |= usbh_int_pipe_in(udev, pp_num);
            }
            else
            {
                retval |= usbh_int_pipe_out(udev, pp_num);
            }
        }
    }

    return retval;
}

/*!
    \brief      handle the IN channel interrupt
    \param[in]  udev: pointer to USB device instance
    \param[in]  pp_num: host channel number which is in (0..7)
    \param[out] none
    \retval     operation status
*/
#if defined(__ICCARM__)      /*!< IAR compiler */
#pragma optimize = none
#endif /* __ICCARM */
static uint32_t usbh_int_pipe_in(usb_core_driver *udev, uint32_t pp_num)
{
    usb_pr *pp_reg = udev->regs.pr[pp_num];
    usb_pipe *pp = &udev->host.pipe[pp_num];

    uint32_t intr_pp = pp_reg->HCHINTF;
    intr_pp &= pp_reg->HCHINTEN;

    uint8_t ep_type = (uint8_t)((pp_reg->HCHCTL & HCHCTL_EPTYPE) >> 18);

    if (intr_pp & HCHINTF_ACK)
    {
        pp_reg->HCHINTF = HCHINTF_ACK;
    }
    else if (intr_pp & HCHINTF_STALL)
    {
        usb_pp_halt(udev, (uint8_t)pp_num, HCHINTF_STALL, PIPE_STALL);
        pp_reg->HCHINTF = HCHINTF_NAK;

        /* note: When there is a 'STALL', reset also NAK,
           else, the udev->host.pp_status = HC_STALL
           will be overwritten by 'NAK' in code below */
        intr_pp &= ~HCHINTF_NAK;
    }
    else if (intr_pp & HCHINTF_DTER)
    {
        usb_pp_halt(udev, (uint8_t)pp_num, HCHINTF_DTER, PIPE_DTGERR);
        pp_reg->HCHINTF = HCHINTF_NAK;
    }
    else
    {
        /* no operation */
    }

    if (intr_pp & HCHINTF_REQOVR)
    {
        usb_pp_halt(udev, (uint8_t)pp_num, HCHINTF_REQOVR, PIPE_REQOVR);
    }
    else if (intr_pp & HCHINTF_TF)
    {
        if ((uint8_t)USB_USE_DMA == udev->bp.transfer_mode)
        {
            udev->host.backup_xfercount[pp_num] = pp->xfer_len - (pp_reg->HCHLEN & HCHLEN_TLEN);
        }

        pp->pp_status = PIPE_XF;
        pp->err_count = 0U;

        pp_reg->HCHINTF = HCHINTF_TF;

        switch (ep_type)
        {
        case USB_EPTYPE_CTRL:
        case USB_EPTYPE_BULK:
            usb_pp_halt(udev, (uint8_t)pp_num, HCHINTF_NAK, PIPE_XF);

            pp->data_toggle_in ^= 1U;
            break;

        case USB_EPTYPE_INTR:
        case USB_EPTYPE_ISOC:
            pp_reg->HCHCTL |= HCHCTL_ODDFRM;
            pp->urb_state = URB_DONE;

#ifdef USBH_USE_RTOS
            usbh_hc_notifyurbchange_callback(udev, pp_num, pp->urb_state);
#endif /* USBH_USE_RTOS */
            break;

        default:
            break;
        }
    }
    else if (intr_pp & HCHINTF_CH)
    {
        pp_reg->HCHINTEN &= ~HCHINTEN_CHIE;

        switch (pp->pp_status)
        {
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

            pp->data_toggle_in ^= 1U;
            break;

        case PIPE_IDLE:
        case PIPE_HALTED:
        case PIPE_NAK:
        case PIPE_NYET:
        case PIPE_BBERR:
        case PIPE_REQOVR:
        default:
            if ((uint8_t)USB_EPTYPE_INTR == ep_type)
            {
                pp->data_toggle_in ^= 1U;
            }
            break;
        }

#ifdef USBH_USE_RTOS
        usbh_hc_notifyurbchange_callback(udev, pp_num, pp->urb_state);
#endif /* USBH_USE_RTOS */

        pp_reg->HCHINTF = HCHINTF_CH;
    }
    else if (intr_pp & HCHINTF_USBER)
    {
        pp->err_count++;
        usb_pp_halt(udev, (uint8_t)pp_num, HCHINTF_USBER, PIPE_TRACERR);
    }
    else if (intr_pp & HCHINTF_NAK)
    {
        pp_reg->HCHINTF = HCHINTF_NAK;
        switch (ep_type)
        {
        case USB_EPTYPE_CTRL:
        case USB_EPTYPE_BULK:
            /* re-activate the channel */
            pp_reg->HCHCTL = (pp_reg->HCHCTL | HCHCTL_CEN) & ~HCHCTL_CDIS;
            break;

        case USB_EPTYPE_INTR:
            pp_reg->HCHINTEN |= HCHINTEN_CHIE;

            (void)usb_pipe_halt(udev, (uint8_t)pp_num);
            break;

        default:
            break;
        }

        pp->pp_status = PIPE_NAK;
    }
    else
    {
        /* no operation */
    }

    return 1U;
}

/*!
    \brief      handle the OUT channel interrupt
    \param[in]  udev: pointer to USB device instance
    \param[in]  pp_num: host channel number which is in (0..7)
    \param[out] none
    \retval     operation status
*/
#if defined(__ICCARM__)      /*!< IAR compiler */
#pragma optimize = none
#endif /* __ICCARM */
static uint32_t usbh_int_pipe_out(usb_core_driver *udev, uint32_t pp_num)
{
    usb_pr *pp_reg = udev->regs.pr[pp_num];
    usb_pipe *pp = &udev->host.pipe[pp_num];

    uint32_t intr_pp = pp_reg->HCHINTF;
    intr_pp &= pp_reg->HCHINTEN;

    if (intr_pp & HCHINTF_ACK)
    {
        if (1U == udev->host.pipe[pp_num].do_ping)
        {
            udev->host.pipe[pp_num].do_ping = 0U;
            pp->err_count = 0U;
            usb_pp_halt(udev, (uint8_t)pp_num, HCHINTF_ACK, PIPE_NAK);
        }

        pp_reg->HCHINTF = HCHINTF_ACK;
    }
    else if (intr_pp & HCHINTF_STALL)
    {
        usb_pp_halt(udev, (uint8_t)pp_num, HCHINTF_STALL, PIPE_STALL);
    }
    else if (intr_pp & HCHINTF_DTER)
    {
        usb_pp_halt(udev, (uint8_t)pp_num, HCHINTF_DTER, PIPE_DTGERR);
        pp_reg->HCHINTF = HCHINTF_NAK;
    }
    else if (intr_pp & HCHINTF_REQOVR)
    {
        usb_pp_halt(udev, (uint8_t)pp_num, HCHINTF_REQOVR, PIPE_REQOVR);
    }
    else if (intr_pp & HCHINTF_TF)
    {
        pp->err_count = 0U;
        usb_pp_halt(udev, (uint8_t)pp_num, HCHINTF_TF, PIPE_XF);
    }
    else if (intr_pp & HCHINTF_NAK)
    {
        if (0U == udev->host.pipe[pp_num].do_ping)
        {
            if (1U == udev->host.pipe[pp_num].supp_ping)
            {
                udev->host.pipe[pp_num].do_ping = 1U;
            }
        }

        pp->err_count = 0U;
        if (USB_USE_FIFO == udev->bp.transfer_mode)
        {
            usb_pp_halt(udev, (uint8_t)pp_num, HCHINTF_NAK, PIPE_NAK);
        }
        else
        {
            pp_reg->HCHINTF = HCHINTF_NAK;
        }
        usb_pp_halt(udev, (uint8_t)pp_num, HCHINTF_NAK, PIPE_NAK);
    }
    else if (intr_pp & HCHINTF_USBER)
    {
        pp->err_count++;
        usb_pp_halt(udev, (uint8_t)pp_num, HCHINTF_USBER, PIPE_TRACERR);
    }
    else if (intr_pp & HCHINTF_NYET)
    {
        usb_pp_halt(udev, (uint8_t)pp_num, HCHINTF_NYET, PIPE_NYET);

        pp->err_count = 0U;
    }
    else if (intr_pp & HCHINTF_CH)
    {
        udev->regs.pr[pp_num]->HCHINTEN &= ~HCHINTEN_CHIE;

        switch (pp->pp_status)
        {
        case PIPE_XF:
            pp->urb_state = URB_DONE;

            if ((uint8_t)USB_EPTYPE_BULK == ((pp_reg->HCHCTL & HCHCTL_EPTYPE) >> 18U))
            {
                pp->data_toggle_out ^= 1U;
            }
            break;

        case PIPE_NAK:
            pp->urb_state = URB_NOTREADY;
            break;

        case PIPE_NYET:
            pp->urb_state = URB_DONE;

            if ((uint8_t)USB_EPTYPE_BULK == ((pp_reg->HCHCTL & HCHCTL_EPTYPE) >> 18U))
            {
                pp->data_toggle_out ^= 1U;
            }
            break;

        case PIPE_STALL:
            pp->urb_state = URB_STALL;
            break;

        case PIPE_TRACERR:
            if (3U == pp->err_count)
            {
                pp->urb_state = URB_ERROR;
                pp->err_count = 0U;
            }
            break;

        case PIPE_IDLE:
        case PIPE_HALTED:
        case PIPE_BBERR:
        case PIPE_REQOVR:
        case PIPE_DTGERR:
        default:
            break;
        }

#ifdef USBH_USE_RTOS
        usbh_hc_notifyurbchange_callback(udev, pp_num, pp->urb_state);
#endif /* USBH_USE_RTOS */

        pp_reg->HCHINTF = HCHINTF_CH;
    }
    else
    {
        /* no operation */
    }

    return 1U;
}

/*!
    \brief      handle the RX FIFO non-empty interrupt
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     operation status
*/
#if defined(__ICCARM__)      /*!< IAR compiler */
#pragma optimize = none
#endif /* __ICCARM */
static uint32_t usbh_int_rxfifonoempty(usb_core_driver *udev)
{
    uint32_t count = 0U, xfer_count = 0U;

    __IO uint8_t pp_num = 0U;
    __IO uint32_t rx_stat = 0U;

    /* disable the RX status queue level interrupt */
    udev->regs.gr->GINTEN &= ~GINTEN_RXFNEIE;

    rx_stat = udev->regs.gr->GRSTATP;
    pp_num = (uint8_t)(rx_stat & GRSTATRP_CNUM);

    switch ((rx_stat & GRSTATRP_RPCKST) >> 17)
    {
    case GRXSTS_PKTSTS_IN:
        count = (rx_stat & GRSTATRP_BCOUNT) >> 4;

        /* read the data into the host buffer. */
        if ((NULL != udev->host.pipe[pp_num].xfer_buf) && (count > 0U))
        {
            (void)usb_rxfifo_read(&udev->regs, udev->host.pipe[pp_num].xfer_buf, (uint16_t)count);

            /* manage multiple transfer packet */
            udev->host.pipe[pp_num].xfer_buf += count;
            udev->host.pipe[pp_num].xfer_count += count;

            xfer_count = udev->host.pipe[pp_num].xfer_count;

            udev->host.backup_xfercount[pp_num] = xfer_count;

            if (udev->regs.pr[pp_num]->HCHLEN & HCHLEN_PCNT)
            {
                /* re-activate the channel when more packets are expected */
                uint32_t pp_ctl = udev->regs.pr[pp_num]->HCHCTL;

                pp_ctl |= HCHCTL_CEN;
                pp_ctl &= ~HCHCTL_CDIS;

                udev->regs.pr[pp_num]->HCHCTL = pp_ctl;
            }
        }
        break;

    case GRXSTS_PKTSTS_IN_XFER_COMP:
        break;

    case GRXSTS_PKTSTS_DATA_TOGGLE_ERR:
        count = (rx_stat & GRSTATRP_BCOUNT) >> 4;

        while (count > 0U)
        {
            rx_stat = udev->regs.gr->GRSTATP;
            count--;
        }
        break;

    case GRXSTS_PKTSTS_CH_HALTED:
        break;

    default:
        break;
    }

    /* enable the RX status queue level interrupt */
    udev->regs.gr->GINTEN |= GINTEN_RXFNEIE;

    return 1U;
}

/*!
    \brief      handle the TX FIFO empty interrupt
    \param[in]  udev: pointer to USB device instance
    \param[in]  pp_mode: pipe mode
    \param[out] none
    \retval     operation status
*/
#if defined(__ICCARM__)      /*!< IAR compiler */
#pragma optimize = none
#endif /* __ICCARM */
static uint32_t usbh_int_txfifoempty(usb_core_driver *udev, usb_pipe_mode pp_mode)
{
    uint8_t pp_num = 0U;
    uint16_t word_count = 0U, len = 0U;
    __IO uint32_t *txfiforeg = 0U, txfifostate = 0U;

    if (PIPE_NON_PERIOD == pp_mode)
    {
        txfiforeg = &udev->regs.gr->HNPTFQSTAT;
    }
    else if (PIPE_PERIOD == pp_mode)
    {
        txfiforeg = &udev->regs.hr->HPTFQSTAT;
    }
    else
    {
        return 0U;
    }

    txfifostate = *txfiforeg;

    pp_num = (uint8_t)((txfifostate & TFQSTAT_CNUM) >> 27);

    word_count = (uint16_t)(udev->host.pipe[pp_num].xfer_len + 3U) / 4U;

    while (((txfifostate & TFQSTAT_TXFS) >= word_count) && (0U != udev->host.pipe[pp_num].xfer_len))
    {
        len = (uint16_t)(txfifostate & TFQSTAT_TXFS) * 4U;

        if (len > udev->host.pipe[pp_num].xfer_len)
        {
            /* last packet */
            len = (uint16_t)udev->host.pipe[pp_num].xfer_len;

            if (PIPE_NON_PERIOD == pp_mode)
            {
                udev->regs.gr->GINTEN &= ~GINTEN_NPTXFEIE;
            }
            else
            {
                udev->regs.gr->GINTEN &= ~GINTEN_PTXFEIE;
            }
        }

        word_count = (uint16_t)((udev->host.pipe[pp_num].xfer_len + 3U) / 4U);
        usb_txfifo_write(&udev->regs, udev->host.pipe[pp_num].xfer_buf, pp_num, len);

        udev->host.pipe[pp_num].xfer_buf += len;
        udev->host.pipe[pp_num].xfer_len -= len;
        udev->host.pipe[pp_num].xfer_count += len;

        txfifostate = *txfiforeg;
    }

    return 1U;
}

#endif /* BSP_USING_USB && RT_USING_USB_HOST */
