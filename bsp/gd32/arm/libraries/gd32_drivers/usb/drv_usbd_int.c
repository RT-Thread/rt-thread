/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-11-07     RealThread   the first version
 */

#include "drv_usbd_int.h"
#include "drv_otghs_dev.h"

#include <stdio.h>

#if defined(BSP_USING_USB) && defined(RT_USING_USB_DEVICE)

static const uint8_t USB_SPEED[4] = {
    [DSTAT_EM_HS_PHY_30MHZ_60MHZ] = (uint8_t)USB_SPEED_HIGH,
    [DSTAT_EM_FS_PHY_30MHZ_60MHZ] = (uint8_t)USB_SPEED_FULL,
    [DSTAT_EM_FS_PHY_48MHZ] = (uint8_t)USB_SPEED_FULL,
    [DSTAT_EM_LS_PHY_6MHZ] = (uint8_t)USB_SPEED_LOW
};

/* local function prototypes ('static') */
static uint32_t usbd_int_epout(usb_core_driver *udev);
static uint32_t usbd_int_epin(usb_core_driver *udev);
static uint32_t usbd_int_rxfifo(usb_core_driver *udev);
static uint32_t usbd_int_reset(usb_core_driver *udev);
static uint32_t usbd_int_enumfinish(usb_core_driver *udev);
static uint32_t usbd_int_suspend(usb_core_driver *udev);
static uint32_t usbd_int_wakeup(usb_core_driver *udev);

#if (1U == LPM_ENABLED)
static uint32_t usbd_int_lpm(usb_core_driver *udev, usb_lpm_type active_type);
#endif /* LPM_ENABLED */

static uint32_t usbd_emptytxfifo_write(usb_core_driver *udev, uint32_t ep_num);

/*!
    \brief      USB device-mode interrupts global service routine handler
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
void usbd_isr(usb_core_driver *udev)
{
    if (HOST_MODE != (udev->regs.gr->GINTF & GINTF_COPM))
    {
        uint32_t intr = udev->regs.gr->GINTF;
        intr &= udev->regs.gr->GINTEN;

        /* there are no interrupts, avoid spurious interrupt */
        if (!intr)
        {
            return;
        }

        /* OUT endpoints interrupts */
        if (intr & GINTF_OEPIF)
        {
            (void)usbd_int_epout(udev);
        }

        /* IN endpoints interrupts */
        if (intr & GINTF_IEPIF)
        {
            (void)usbd_int_epin(udev);
        }

        /* suspend interrupt */
        if (intr & GINTF_SP)
        {
            (void)usbd_int_suspend(udev);
        }

        /* wakeup interrupt */
        if (intr & GINTF_WKUPIF)
        {
            (void)usbd_int_wakeup(udev);
        }

        /* start of frame interrupt */
        if (intr & GINTF_SOF)
        {
            /* clear interrupt */
            udev->regs.gr->GINTF = GINTF_SOF;
        }

        /* receive FIFO not empty interrupt */
        if (intr & GINTF_RXFNEIF)
        {
            (void)usbd_int_rxfifo(udev);
        }

        /* USB reset interrupt */
        if (intr & GINTF_RST)
        {
            (void)usbd_int_reset(udev);
        }

        /* enumeration has been done interrupt */
        if (intr & GINTF_ENUMFIF)
        {
            (void)usbd_int_enumfinish(udev);
        }

        /* incomplete synchronization IN transfer interrupt*/
        if (intr & GINTF_ISOINCIF)
        {
            if (NULL != udev->dev.class_core->incomplete_isoc_in)
            {
                (void)udev->dev.class_core->incomplete_isoc_in(udev);
            }

            /* clear interrupt */
            udev->regs.gr->GINTF = GINTF_ISOINCIF;
        }

        /* incomplete synchronization OUT transfer interrupt*/
        if (intr & GINTF_ISOONCIF)
        {
            if (NULL != udev->dev.class_core->incomplete_isoc_out)
            {
                (void)udev->dev.class_core->incomplete_isoc_out(udev);
            }

            /* clear interrupt */
            udev->regs.gr->GINTF = GINTF_ISOONCIF;
        }

#if (1U == LPM_ENABLED)
        if (intr & GINTF_LPMIF)
        {
            /* clear interrupt */
            udev->regs.gr->GINTF = GINTF_LPMIF;

            udev->dev.pm.BESL = (udev->regs.gr->GLPMCFG & GLPMCFG_BESL) >> 2U;
            udev->dev.pm.dev_remote_wakeup = (udev->regs.gr->GLPMCFG & GLPMCFG_REW) >> 6U;

            if (LPM_L0 == udev->dev.pm.lpm_state)
            {
                udev->dev.pm.lpm_state = LPM_L1;
                usbd_int_lpm(udev, LPM_L1_ACTIVE);
            }
            else
            {
                udev->dev.pm.lpm_state = LPM_L0;
                usbd_int_lpm(udev, LPM_L0_ACTIVE);
            }
        }
#endif /* LPM_ENABLED */

#ifdef VBUS_SENSING_ENABLED

        /* session request interrupt */
        if (intr & GINTF_SESIF)
        {
            udev->regs.gr->GINTF = GINTF_SESIF;
        }

        /* OTG mode interrupt */
        if (intr & GINTF_OTGIF)
        {
            if (udev->regs.gr->GOTGINTF & GOTGINTF_SESEND)
            {
            }

            /* clear OTG interrupt */
            udev->regs.gr->GINTF = GINTF_OTGIF;
        }
#endif /* VBUS_SENSING_ENABLED */
    }
}

/*!
    \brief      indicates that an OUT endpoint has a pending interrupt
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbd_int_epout(usb_core_driver *udev)
{
    uint32_t epintnum = 0U;
    uint8_t ep_num = 0U;

    for (epintnum = usb_oepintnum_read(udev); epintnum; epintnum >>= 1)
    {
        if (epintnum & 0x01U)
        {
            __IO uint32_t oepintr = usb_oepintr_read(udev, ep_num);

            /* transfer complete interrupt */
            if (oepintr & DOEPINTF_TF)
            {
                /* clear the bit in DOEPINTF for this interrupt */
                udev->regs.er_out[ep_num]->DOEPINTF = DOEPINTF_TF;

                if ((uint8_t)USB_USE_DMA == udev->bp.transfer_mode)
                {
                    __IO uint32_t eplen = udev->regs.er_out[ep_num]->DOEPLEN;

                    udev->dev.transc_out[ep_num].xfer_count = udev->dev.transc_out[ep_num].max_len -
                                                              (eplen & DEPLEN_TLEN);
                }

                /* inform upper layer: data ready */
                usbd_data_out_stage_callback(ep_num, udev->dev.transc_out[ep_num].xfer_len);

                if ((uint8_t)USB_USE_DMA == udev->bp.transfer_mode)
                {
                    if ((0U == ep_num) && ((uint8_t)USB_CTL_STATUS_OUT == udev->dev.control.ctl_state))
                    {
                        usb_ctlep_startout(udev);
                    }
                }
            }

            /* SETUP phase finished interrupt (control endpoints) */
            if (oepintr & DOEPINTF_STPF)
            {
                /* inform the upper layer that a SETUP packet is available */
                usbd_setup_stage_callback((struct urequest *)&udev->dev.control.req);

                udev->regs.er_out[ep_num]->DOEPINTF = DOEPINTF_STPF;
            }
        }

        ep_num++;
    }

    return 1U;
}

/*!
    \brief      indicates that an IN endpoint has a pending interrupt
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbd_int_epin(usb_core_driver *udev)
{
    uint32_t epintnum = 0U;
    uint8_t ep_num = 0U;

    for (epintnum = usb_iepintnum_read(udev); epintnum; epintnum >>= 1)
    {
        if (epintnum & 0x1U)
        {
            __IO uint32_t iepintr = usb_iepintr_read(udev, ep_num);

            if (iepintr & DIEPINTF_TF)
            {
                udev->regs.er_in[ep_num]->DIEPINTF = DIEPINTF_TF;

                /* data transmission is completed */
                usbd_data_in_stage_callback(ep_num, udev->dev.transc_in[ep_num].xfer_len);

                if ((uint8_t)USB_USE_DMA == udev->bp.transfer_mode)
                {
                    if ((0U == ep_num) && ((uint8_t)USB_CTL_STATUS_IN == udev->dev.control.ctl_state))
                    {
                        usb_ctlep_startout(udev);
                    }
                }
            }

            if (iepintr & DIEPINTF_TXFE)
            {
                usbd_emptytxfifo_write(udev, (uint32_t)ep_num);

                udev->regs.er_in[ep_num]->DIEPINTF = DIEPINTF_TXFE;
            }
        }

        ep_num++;
    }

    return 1U;
}

/*!
    \brief      handle the RX status queue level interrupt
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbd_int_rxfifo(usb_core_driver *udev)
{
    usb_transc *transc = NULL;

    uint8_t data_PID = 0U;
    uint32_t bcount = 0U;

    __IO uint32_t devrxstat = 0U;

    /* disable the RX status queue non-empty interrupt */
    udev->regs.gr->GINTEN &= ~GINTEN_RXFNEIE;

    /* get the status from the top of the FIFO */
    devrxstat = udev->regs.gr->GRSTATP;
    gd_usb_rxfifo_count++;
    gd_usb_last_rx_status = devrxstat;

    uint8_t ep_num = (uint8_t)(devrxstat & GRSTATRP_EPNUM);

    transc = &udev->dev.transc_out[ep_num];

    bcount = (devrxstat & GRSTATRP_BCOUNT) >> 4;
    data_PID = (uint8_t)((devrxstat & GRSTATRP_DPID) >> 15);

    switch ((devrxstat & GRSTATRP_RPCKST) >> 17)
    {
    case RSTAT_GOUT_NAK:
        break;

    case RSTAT_DATA_UPDT:
        if (bcount > 0U)
        {
            (void)usb_rxfifo_read(&udev->regs, transc->xfer_buf, (uint16_t)bcount);

            transc->xfer_buf += bcount;
            transc->xfer_count += bcount;
        }
        break;

    case RSTAT_XFER_COMP:
        /* trigger the OUT endpoint interrupt */
        break;

    case RSTAT_SETUP_COMP:
        /* trigger the OUT endpoint interrupt */
        break;

    case RSTAT_SETUP_UPDT:
        gd_usb_setup_rx_count++;
        if ((0U == transc->ep_addr.num) && (8U == bcount) && (DPID_DATA0 == data_PID))
        {
            /* copy the SETUP packet received in FIFO into the setup buffer in RAM */
            (void)usb_rxfifo_read(&udev->regs, (uint8_t *)&udev->dev.control.req, (uint16_t)bcount);

            transc->xfer_count += bcount;
        }
        break;

    default:
        break;
    }

    /* enable the RX status queue level interrupt */
    udev->regs.gr->GINTEN |= GINTEN_RXFNEIE;

    return 1U;
}

/*!
    \brief      handle USB reset interrupt
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     status
*/
static uint32_t usbd_int_reset(usb_core_driver *udev)
{
    uint32_t i;

    /* clear the remote wakeup signaling */
    udev->regs.dr->DCTL &= ~DCTL_RWKUP;

    /* flush the TX FIFO */
    (void)usb_txfifo_flush(&udev->regs, 0U);

    for (i = 0U; i < udev->bp.num_ep; i++)
    {
        udev->regs.er_in[i]->DIEPINTF = 0xFFU;
        udev->regs.er_out[i]->DOEPINTF = 0xFFU;
    }

    /* clear all pending device endpoint interrupts */
    udev->regs.dr->DAEPINT = 0xFFFFFFFFU;

    /* enable endpoint 0 interrupts */
    udev->regs.dr->DAEPINTEN = 1U | (1U << 16U);

    /* enable OUT endpoint interrupts */
    udev->regs.dr->DOEPINTEN = DOEPINTEN_STPFEN | DOEPINTEN_TFEN;

#ifdef USB_DEDICATED_EP1_ENABLED
    udev->regs.dr->DOEP1INTEN = DOEPINTEN_STPFEN | DOEPINTEN_TFEN;
#endif

    /* enable IN endpoint interrupts */
    udev->regs.dr->DIEPINTEN = DIEPINTEN_TFEN;

#ifdef USB_DEDICATED_EP1_ENABLED
    udev->regs.dr->DIEP1INTEN = DIEPINTEN_TFEN;
#endif

    /* reset device address */
    udev->regs.dr->DCFG &= ~DCFG_DAR;

    /* configure endpoint 0 to receive SETUP packets */
    usb_ctlep_startout(udev);

    /* clear USB reset interrupt */
    udev->regs.gr->GINTF = GINTF_RST;

    usb_ep_active(udev, 0x00, USB_FS_EP0_MAX_LEN, USB_EPTYPE_CTRL);
    usb_ep_active(udev, 0x80, USB_FS_EP0_MAX_LEN, USB_EPTYPE_CTRL);

    usbd_reset_callback();

    return 1U;
}

/*!
    \brief      handle USB speed enumeration finish interrupt
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     status
*/
static uint32_t usbd_int_enumfinish(usb_core_driver *udev)
{
    uint8_t enum_speed = (uint8_t)((udev->regs.dr->DSTAT & DSTAT_ES) >> 1);

    udev->regs.dr->DCTL &= ~DCTL_CGINAK;
    udev->regs.dr->DCTL |= DCTL_CGINAK;

    udev->regs.gr->GUSBCS &= ~GUSBCS_UTT;

    /* set USB turn-around time based on device speed and PHY interface */
    if ((uint8_t)USB_SPEED_HIGH == USB_SPEED[enum_speed])
    {
        udev->bp.core_speed = (uint8_t)USB_SPEED_HIGH;

        udev->regs.gr->GUSBCS |= 0x09U << 10;
    }
    else
    {
        udev->bp.core_speed = (uint8_t)USB_SPEED_FULL;

        udev->regs.gr->GUSBCS |= 0x05U << 10;
    }

    /* clear interrupt */
    udev->regs.gr->GINTF = GINTF_ENUMFIF;

    gd_usb_enum_count++;

    return 1U;
}

/*!
    \brief      USB suspend interrupt handler
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbd_int_suspend(usb_core_driver *udev)
{
    __IO uint8_t low_power = udev->bp.low_power;
    __IO uint8_t suspend = (uint8_t)(udev->regs.dr->DSTAT & DSTAT_SPST);

    udev->dev.backup_status = udev->dev.cur_status;

    if (low_power && suspend)
    {
        /* switch-off the USB clocks */
        *udev->regs.PWRCLKCTL |= PWRCLKCTL_SUCLK | PWRCLKCTL_SHCLK;

        /* enter DEEP_SLEEP mode with LDO in low power mode */
        pmu_to_deepsleepmode(WFI_CMD);
    }

    /* clear interrupt */
    udev->regs.gr->GINTF = GINTF_SP;

    return 1U;
}

/*!
    \brief      USB wakeup interrupt handler
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbd_int_wakeup(usb_core_driver *udev)
{
    __IO uint8_t low_power = udev->bp.low_power;
    __IO uint8_t remote_wakeup = udev->dev.pm.dev_remote_wakeup;

#if (1U == LPM_ENABLED)
    if (LPM_L1 == udev->dev.pm.lpm_state)
    {
        udev->dev.pm.lpm_state = LPM_L0;
        usbd_int_lpm(udev, LPM_L0_ACTIVE);
    }
    else
#endif /* LPM_ENABLED */
    {
        if (remote_wakeup && low_power)
        {
            /* resume MCU CLK */

            /* reset SLEEPDEEP bit of Cortex-M33 system control register */
            SCB->SCR &= ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
        }

        usb_clock_active(udev);

        /* inform upper layer by the resume event */
        udev->dev.cur_status = udev->dev.backup_status;
    }

    /* clear interrupt */
    udev->regs.gr->GINTF = GINTF_WKUPIF;

    return 1U;
}

#ifdef USB_DEDICATED_EP1_ENABLED

/*!
    \brief      USB dedicated OUT endpoint 1 interrupt service routine handler
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     operation status
*/
uint32_t usbd_int_dedicated_ep1out(usb_core_driver *udev)
{
    uint32_t oepintr = 0U;
    uint32_t oeplen = 0U;

    oepintr = udev->regs.er_out[1]->DOEPINTF;
    oepintr &= udev->regs.dr->DOEP1INTEN;

    /* transfer complete */
    if (oepintr & DOEPINTF_TF)
    {
        /* clear the bit in DOEPINTn for this interrupt */
        udev->regs.er_out[1]->DOEPINTF = DOEPINTF_TF;

        if (USB_USE_DMA == udev->bp.transfer_mode)
        {
            oeplen = udev->regs.er_out[1]->DOEPLEN;

            /* ToDo : handle more than one single MPS size packet */
            udev->dev.transc_out[1].xfer_count = udev->dev.transc_out[1].max_len -
                                                 (oeplen & DEPLEN_TLEN);
        }

        /* RX COMPLETE */
        usbd_out_transc(udev, 1U);
    }

    return 1U;
}

/*!
    \brief      USB dedicated IN endpoint 1 interrupt service routine handler
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     operation status
*/
uint32_t usbd_int_dedicated_ep1in(usb_core_driver *udev)
{
    uint32_t inten, intr, emptyen;

    inten = udev->regs.dr->DIEP1INTEN;
    emptyen = udev->regs.dr->DIEPFEINTEN;

    inten |= ((emptyen >> 1U) & 0x1U) << 7U;

    intr = udev->regs.er_in[1]->DIEPINTF & inten;

    if (intr & DIEPINTF_TF)
    {
        udev->regs.dr->DIEPFEINTEN &= ~(0x1U << 1U);

        udev->regs.er_in[1]->DIEPINTF = DIEPINTF_TF;

        /* TX COMPLETE */
        usbd_in_transc(udev, 1U);
    }

    if (intr & DIEPINTF_TXFE)
    {
        usbd_emptytxfifo_write(udev, 1U);

        udev->regs.er_in[1]->DIEPINTF = DIEPINTF_TXFE;
    }

    return 1U;
}

#endif

#if (1U == LPM_ENABLED)

/*!
    \brief      USB LPM interrupt handler
    \param[in]  udev: pointer to USB device instance
    \param[in]  active_type: active type
                only one parameter can be selected which is shown as below:
      \arg        LPM_L0_ACTIVE: select L0 to active
      \arg        LPM_L1_ACTIVE: select L1 to active
    \param[out] none
    \retval     operation status
*/
static uint32_t usbd_int_lpm(usb_core_driver *udev, usb_lpm_type active_type)
{
    __IO uint8_t low_power = udev->bp.low_power;
    __IO uint8_t suspend = (uint8_t)(udev->regs.dr->DSTAT & DSTAT_SPST);
    __IO uint8_t is_configured = (udev->dev.cur_status == (uint8_t)USBD_CONFIGURED) ? 1U : 0U;

    switch (active_type)
    {
    case LPM_L0_ACTIVE:
        udev->dev.cur_status = udev->dev.backup_status;

        /* switch-on the OTG clocks */
        usb_clock_active(udev);

        if (low_power)
        {
            /* resume MCU CLK */

            /* reset SLEEPDEEP bit of Cortex-M7 system control register */
            SCB->SCR &= ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
        }
        break;

    case LPM_L1_ACTIVE:
        udev->dev.backup_status = udev->dev.cur_status;
        udev->dev.cur_status = (uint8_t)USBD_SUSPENDED;

        /* add delay */
        usb_mdelay(300U);

        /* switch-off the OTG clocks */
        *udev->regs.PWRCLKCTL |= PWRCLKCTL_SUCLK | PWRCLKCTL_SHCLK;

        if (low_power)
        {
            /* enter DEEP_SLEEP mode with LDO in low power mode */
            pmu_to_deepsleepmode(WFI_CMD);
        }
        break;
    }

    return 1U;
}

#endif /* LPM_ENABLED */

/*!
    \brief      check FIFO for the next packet to be loaded
    \param[in]  udev: pointer to USB device instance
    \param[in]  ep_num: endpoint identifier which is in (0..5)
    \param[out] none
    \retval     status
*/
static uint32_t usbd_emptytxfifo_write(usb_core_driver *udev, uint32_t ep_num)
{
    uint32_t len;
    uint32_t word_count;

    usb_transc *transc = &udev->dev.transc_in[ep_num];

    len = transc->xfer_len - transc->xfer_count;

    /* get the data length to write */
    if (len > transc->max_len)
    {
        len = transc->max_len;
    }

    word_count = (len + 3U) / 4U;

    while (((udev->regs.er_in[ep_num]->DIEPTFSTAT & DIEPTFSTAT_IEPTFS) >= word_count) &&
           (transc->xfer_count < transc->xfer_len))
    {
        len = transc->xfer_len - transc->xfer_count;

        if (len > transc->max_len)
        {
            len = transc->max_len;
        }

        /* write FIFO in word(4bytes) */
        word_count = (len + 3U) / 4U;

        /* write the FIFO */
        (void)usb_txfifo_write(&udev->regs, transc->xfer_buf, (uint8_t)ep_num, (uint16_t)len);

        transc->xfer_buf += len;
        transc->xfer_count += len;

        if (transc->xfer_count == transc->xfer_len)
        {
            /* disable the device endpoint FIFO empty interrupt */
            udev->regs.dr->DIEPFEINTEN &= ~(0x01U << ep_num);
        }
    }

    return 1U;
}

#endif /* BSP_USING_USB && RT_USING_USB_DEVICE */
