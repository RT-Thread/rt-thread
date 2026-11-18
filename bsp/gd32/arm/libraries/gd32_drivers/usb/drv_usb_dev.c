/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-11-07     RealThread   the first version
 */

#include "drv_usb_hw.h"
#include "drv_usb_dev.h"

#include <stdio.h>

#if defined(BSP_USING_USB) && defined(RT_USING_USB_DEVICE)

/* endpoint 0 max packet length */
static const uint8_t EP0_MAXLEN[4] = {
    [DSTAT_EM_HS_PHY_30MHZ_60MHZ] = EP0MPL_64,
    [DSTAT_EM_FS_PHY_30MHZ_60MHZ] = EP0MPL_64,
    [DSTAT_EM_FS_PHY_48MHZ] = EP0MPL_64,
    [DSTAT_EM_LS_PHY_6MHZ] = EP0MPL_8
};

/* USB endpoint TX FIFO size */
static uint16_t USBHS_TX_FIFO_SIZE[USBHS_MAX_EP_COUNT] = {
    (uint16_t)USB_DEV_TX0_FIFO_SIZE,
    (uint16_t)USB_DEV_TX1_FIFO_SIZE,
    (uint16_t)USB_DEV_TX2_FIFO_SIZE,
    (uint16_t)USB_DEV_TX3_FIFO_SIZE,
    (uint16_t)USB_DEV_TX4_FIFO_SIZE,
    (uint16_t)USB_DEV_TX5_FIFO_SIZE,
    (uint16_t)USB_DEV_TX6_FIFO_SIZE,
    (uint16_t)USB_DEV_TX7_FIFO_SIZE,
};

/*!
    \brief      initialize USB core registers for device mode
    \param[in]  udev: pointer to USB device
    \param[out] none
    \retval     operation status
*/
usb_status usb_devcore_init(usb_core_driver *udev)
{
    uint8_t i = 0U;

    /* restart the PHY clock (maybe don't need to...) */
    *udev->regs.PWRCLKCTL = 0U;

    /* configure periodic frame interval to default value */
    udev->regs.dr->DCFG &= ~DCFG_EOPFT;
    udev->regs.dr->DCFG |= FRAME_INTERVAL_80;

    udev->regs.dr->DCFG &= ~DCFG_DS;

    if (USB_EMBEDDED_PHY_HS == udev->bp.phy_itf)
    {
        udev->regs.dr->DCFG |= USB_SPEED_INP_HIGH;
    }
    else if (USB_EMBEDDED_PHY_FS == udev->bp.phy_itf)
    {
        udev->regs.dr->DCFG |= USB_SPEED_INP_FULL;
    }
    else
    {
        /* no operation */
    }

    /* set RX FIFO size */
    usb_set_rxfifo(&udev->regs, (uint16_t)USB_DEV_RX_FIFO_SIZE);

    /* set endpoint 0 to 3's TX FIFO length and RAM address */
    for (i = 0U; i < USBHS_MAX_EP_COUNT; i++)
    {
        usb_set_txfifo(&udev->regs, i, USBHS_TX_FIFO_SIZE[i]);
    }

    /* make sure all FIFOs are flushed */

    /* flush all TX FIFOs */
    (void)usb_txfifo_flush(&udev->regs, 0x10U);

    /* flush entire RX FIFO */
    (void)usb_rxfifo_flush(&udev->regs);

    /* clear all pending device interrupts */
    udev->regs.dr->DIEPINTEN = 0U;
    udev->regs.dr->DOEPINTEN = 0U;
    udev->regs.dr->DAEPINT = 0xFFFFFFFFU;
    udev->regs.dr->DAEPINTEN = 0U;

    /* configure all IN/OUT endpoints */
    for (i = 0U; i < udev->bp.num_ep; i++)
    {
        if (udev->regs.er_in[i]->DIEPCTL & DEPCTL_EPEN)
        {
            udev->regs.er_in[i]->DIEPCTL |= DEPCTL_EPD | DEPCTL_SNAK;
        }
        else
        {
            udev->regs.er_in[i]->DIEPCTL = 0U;
        }

        /* set IN endpoint transfer length to 0 */
        udev->regs.er_in[i]->DIEPLEN = 0U;

        /* clear all pending IN endpoint interrupts */
        udev->regs.er_in[i]->DIEPINTF = 0xFFU;

        if (udev->regs.er_out[i]->DOEPCTL & DEPCTL_EPEN)
        {
            udev->regs.er_out[i]->DOEPCTL |= DEPCTL_EPD | DEPCTL_SNAK;
        }
        else
        {
            udev->regs.er_out[i]->DOEPCTL = 0U;
        }

        /* set OUT endpoint transfer length to 0 */
        udev->regs.er_out[i]->DOEPLEN = 0U;

        /* clear all pending OUT endpoint interrupts */
        udev->regs.er_out[i]->DOEPINTF = 0xFFU;
    }

    udev->regs.dr->DIEPINTEN |= DIEPINTEN_EPTXFUDEN;

    (void)usb_devint_enable(udev);

    /* configure LPM function */
    if (1U == udev->bp.lpm_enable)
    {
        udev->dev.pm.lpm_state = LPM_L0;
        udev->regs.gr->GLPMCFG = GLPMCFG_LPMEN | GLPMCFG_ACKLPM | GLPMCFG_BESLEN;
    }

    return USB_OK;
}

/*!
    \brief      enable the USB device mode interrupts
    \param[in]  udev: pointer to USB device
    \param[out] none
    \retval     operation status
*/
usb_status usb_devint_enable(usb_core_driver *udev)
{
    /* clear any pending USB OTG interrupts */
    udev->regs.gr->GOTGINTF = 0xFFFFFFFFU;

    /* clear any pending interrupts */
    udev->regs.gr->GINTF = 0xBFFFFFFFU;

    /* enable the USB wakeup and suspend interrupts */
    udev->regs.gr->GINTEN = GINTEN_WKUPIE | GINTEN_SPIE;

    /* enable device_mode-related interrupts */
    if ((uint8_t)USB_USE_FIFO == udev->bp.transfer_mode)
    {
        udev->regs.gr->GINTEN |= GINTEN_RXFNEIE;
    }

    udev->regs.gr->GINTEN |= GINTEN_RSTIE | GINTEN_ENUMFIE | GINTEN_IEPIE |
                             GINTEN_OEPIE | GINTEN_SOFIE | GINTEN_ISOONCIE | GINTEN_ISOINCIE;

#ifdef VBUS_SENSING_ENABLED
    udev->regs.gr->GINTEN |= GINTEN_SESIE | GINTEN_OTGIE;
#endif /* VBUS_SENSING_ENABLED */

    if (1U == udev->bp.lpm_enable)
    {
        udev->regs.gr->GINTEN |= GINTEN_LPMIE;
    }

    return USB_OK;
}

/*!
    \brief      active the USB endpoint0 transaction
    \param[in]  udev: pointer to USB device
    \param[in]  transc: the USB endpoint0 transaction
    \param[out] none
    \retval     operation status
*/
usb_status usb_transc0_active(usb_core_driver *udev, usb_transc *transc)
{
    __IO uint32_t *reg_addr = NULL;

    uint32_t enum_speed = udev->regs.dr->DSTAT & DSTAT_ES;

    /* get the endpoint number */
    uint8_t ep_num = transc->ep_addr.num;

    if (ep_num)
    {
        /* not endpoint 0 */
        return USB_FAIL;
    }

    if (transc->ep_addr.dir)
    {
        reg_addr = &udev->regs.er_in[0]->DIEPCTL;
    }
    else
    {
        reg_addr = &udev->regs.er_out[0]->DOEPCTL;
    }

    /* endpoint 0 is activated after USB clock is enabled */
    *reg_addr &= ~(DEPCTL_MPL | DEPCTL_EPTYPE | DIEPCTL_TXFNUM);

    /* set endpoint 0 maximum packet length */
    *reg_addr |= EP0_MAXLEN[enum_speed];

    /* activate endpoint */
    *reg_addr |= ((uint32_t)transc->ep_type << 18) | ((uint32_t)ep_num << 22) | DEPCTL_SD0PID | DEPCTL_EPACT;

    return USB_OK;
}

/*!
    \brief      active the USB transaction
    \param[in]  udev: pointer to USB device
    \param[in]  transc: the USB transaction
    \param[out] none
    \retval     status
*/
usb_status usb_ep_active(usb_core_driver *udev, uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_attr)
{
    __IO uint32_t *reg_addr = NULL;
    uint32_t epinten = 0U;
    uint32_t enum_speed = udev->regs.dr->DSTAT & DSTAT_ES;

    usb_transc *transc = NULL;

    /* get the endpoint number */
    uint8_t ep_num = EP_ID(ep_addr);

    /* enable endpoint interrupt number */
    if (EP_DIR(ep_addr))
    {
        reg_addr = &udev->regs.er_in[ep_num]->DIEPCTL;
        epinten = 1U << ep_num;
        transc = &udev->dev.transc_in[ep_num];
    }
    else
    {
        reg_addr = &udev->regs.er_out[ep_num]->DOEPCTL;
        epinten = 1U << (16U + ep_num);
        transc = &udev->dev.transc_out[ep_num];
    }

    *transc = (usb_transc){ 0 };
    transc->ep_addr.num = ep_num;
    transc->ep_addr.dir = EP_DIR(ep_addr) ? 1U : 0U;
    transc->max_len = ep_mps;
    transc->ep_type = ep_attr & USB_EPTYPE_MASK;

    /* if the endpoint is not active, need change the endpoint control register */
    if (!(*reg_addr & DEPCTL_EPACT))
    {
        *reg_addr &= ~(DEPCTL_MPL | DEPCTL_EPTYPE | DIEPCTL_TXFNUM);

        /* set endpoint maximum packet length */
        if (0U == ep_num)
        {
            *reg_addr |= EP0_MAXLEN[enum_speed];
        }
        else
        {
            *reg_addr |= transc->max_len;
        }

        /* activate endpoint */
        *reg_addr |= ((uint32_t)transc->ep_type << 18) | ((uint32_t)ep_num << 22) | DEPCTL_SD0PID | DEPCTL_EPACT;
    }

#ifdef USB_DEDICATED_EP1_ENABLED
    if (1U == ep_num)
    {
        udev->regs.dr->DEP1INTEN |= epinten;
    }
    else
#endif
    {
        /* enable the interrupts for this endpoint */
        udev->regs.dr->DAEPINTEN |= epinten;
    }

    return USB_OK;
}

/*!
    \brief      deactivate the USB transaction
    \param[in]  udev: pointer to USB device
    \param[in]  transc: the USB transaction
    \param[out] none
    \retval     status
*/
usb_status usb_ep_deactivate(usb_core_driver *udev, uint8_t ep_addr)
{
    uint32_t epinten = 0U;

    uint8_t ep_num = EP_ID(ep_addr);

    /* disable endpoint interrupt number */
    if (EP_DIR(ep_addr))
    {
        epinten = 1U << ep_num;

        udev->regs.er_in[ep_num]->DIEPCTL &= ~DEPCTL_EPACT;
    }
    else
    {
        epinten = 1U << (ep_num + 16U);

        udev->regs.er_out[ep_num]->DOEPCTL &= ~DEPCTL_EPACT;
    }

#ifdef USB_DEDICATED_EP1_ENABLED
    if (1U == ep_num)
    {
        udev->regs.dr->DEP1INTEN &= ~epinten;
    }
    else
#endif
    {
        /* disable the interrupts for this endpoint */
        udev->regs.dr->DAEPINTEN &= ~epinten;
    }

    return USB_OK;
}

/*!
    \brief      configure USB transaction to start IN transfer
    \param[in]  udev: pointer to USB device
    \param[in]  transc: the USB IN transaction
    \param[out] none
    \retval     operation status
*/
usb_status usb_ep_inxfer(usb_core_driver *udev, uint8_t ep_addr, uint8_t *buf, uint16_t count)
{
    usb_status status = USB_OK;
    uint8_t ep_num = EP_ID(ep_addr);

    __IO uint32_t epctl = udev->regs.er_in[ep_num]->DIEPCTL;
    __IO uint32_t eplen = udev->regs.er_in[ep_num]->DIEPLEN;

    usb_transc *transc = &udev->dev.transc_in[ep_num];

    eplen &= ~(DEPLEN_TLEN | DEPLEN_PCNT);

    transc->xfer_len = count;
    transc->xfer_buf = buf;
    transc->xfer_count = 0U;

    /* zero length packet or endpoint 0 */
    if (0U == count)
    {
        /* set transfer packet count to 1 */
        eplen |= 1U << 19;
    }
    else
    {
        /* set transfer packet count */
        if (0U == ep_num)
        {
            transc->xfer_len = USB_MIN(count, transc->max_len);

            eplen |= 1U << 19;
        }
        else
        {
            eplen |= ((count - 1 + transc->max_len) / transc->max_len) << 19;
        }

        /* set endpoint transfer length */
        eplen |= count;

        if ((uint8_t)USB_EPTYPE_ISOC == transc->ep_type)
        {
            eplen |= DIEPLEN_MCNT & (1U << 29);
        }
    }

    udev->regs.er_in[ep_num]->DIEPLEN = eplen;

    if ((uint8_t)USB_EPTYPE_ISOC == transc->ep_type)
    {
        if (((udev->regs.dr->DSTAT & DSTAT_FNRSOF) >> 8) & 0x01U)
        {
            epctl |= DEPCTL_SEVNFRM;
        }
        else
        {
            epctl |= DEPCTL_SODDFRM;
        }
    }

    if ((uint8_t)USB_USE_DMA == udev->bp.transfer_mode)
    {
        udev->regs.er_in[ep_num]->DIEPDMAADDR = transc->dma_addr;
    }

    /* enable the endpoint and clear the NAK */
    epctl |= DEPCTL_CNAK | DEPCTL_EPEN;

    udev->regs.er_in[ep_num]->DIEPCTL = epctl;

    if ((uint8_t)USB_USE_FIFO == udev->bp.transfer_mode)
    {
        if ((uint8_t)USB_EPTYPE_ISOC != transc->ep_type)
        {
            /* enable the TX FIFO empty interrupt for this endpoint */
            if (count > 0U)
            {
                udev->regs.dr->DIEPFEINTEN |= 1U << ep_num;
            }
        }
        else
        {
            (void)usb_txfifo_write(&udev->regs, transc->xfer_buf, ep_num, (uint16_t)transc->xfer_len);
        }
    }

    return status;
}

/*!
    \brief      configure USB transaction to start OUT transfer
    \param[in]  udev: pointer to USB device
    \param[in]  transc: the USB OUT transaction
    \param[out] none
    \retval     status
*/
usb_status usb_ep_outxfer(usb_core_driver *udev, uint8_t ep_addr, uint8_t *buf, uint16_t count)
{
    usb_status status = USB_OK;

    uint8_t ep_num = EP_ID(ep_addr);

    uint32_t epctl = udev->regs.er_out[ep_num]->DOEPCTL;
    uint32_t eplen = udev->regs.er_out[ep_num]->DOEPLEN;

    usb_transc *transc = &udev->dev.transc_out[ep_num];

    transc->xfer_buf = buf;
    transc->xfer_len = count;

    eplen &= ~(DEPLEN_TLEN | DEPLEN_PCNT);

    /* zero length packet or endpoint 0 */
    if ((0U == count) || (0U == ep_num))
    {
        /* set the transfer length to max packet size */
        eplen |= transc->max_len;

        /* set the transfer packet count to 1 */
        eplen |= 1U << 19;
    }
    else
    {
        /* configure the transfer size and packet count as follows:
         * pktcnt = N
         * xfersize = N * maxpacket
         */
        uint32_t packet_count = (count + transc->max_len - 1) / transc->max_len;

        eplen |= packet_count << 19;
        eplen |= packet_count * transc->max_len;
    }

    udev->regs.er_out[ep_num]->DOEPLEN = eplen;

    if ((uint8_t)USB_USE_DMA == udev->bp.transfer_mode)
    {
        udev->regs.er_out[ep_num]->DOEPDMAADDR = transc->dma_addr;
    }

    if ((uint8_t)USB_EPTYPE_ISOC == transc->ep_type)
    {
        if (transc->frame_num)
        {
            epctl |= DEPCTL_SD1PID;
        }
        else
        {
            epctl |= DEPCTL_SD0PID;
        }
    }

    /* enable the endpoint and clear the NAK */
    epctl |= DEPCTL_EPEN | DEPCTL_CNAK;

    udev->regs.er_out[ep_num]->DOEPCTL = epctl;

    return status;
}

/*!
    \brief      set the USB transaction STALL status
    \param[in]  udev: pointer to USB device
    \param[in]  transc: the USB transaction
    \param[out] none
    \retval     status
*/
usb_status usb_ep_stall(usb_core_driver *udev, uint8_t ep_addr)
{
    __IO uint32_t *reg_addr = NULL;

    uint8_t ep_num = EP_ID(ep_addr);

    if (EP_DIR(ep_addr))
    {
        reg_addr = &(udev->regs.er_in[ep_num]->DIEPCTL);

        /* set the endpoint disable bit */
        if (*reg_addr & DEPCTL_EPEN)
        {
            *reg_addr |= DEPCTL_EPD;
        }
    }
    else
    {
        /* set the endpoint STALL bit */
        reg_addr = &(udev->regs.er_out[ep_num]->DOEPCTL);
    }

    /* set the endpoint STALL bit */
    *reg_addr |= DEPCTL_STALL;

    return USB_OK;
}

/*!
    \brief      clear the USB transaction STALL status
    \param[in]  udev: pointer to USB device
    \param[in]  transc: the USB transaction
    \param[out] none
    \retval     operation status
*/
usb_status usb_ep_clrstall(usb_core_driver *udev, uint8_t ep_addr)
{
    __IO uint32_t *reg_addr = NULL;
    uint32_t ep_type = 0U;

    uint8_t ep_num = EP_ID(ep_addr);

    if (EP_DIR(ep_addr))
    {
        reg_addr = &(udev->regs.er_in[ep_num]->DIEPCTL);
    }
    else
    {
        reg_addr = &(udev->regs.er_out[ep_num]->DOEPCTL);
    }

    /* clear the endpoint STALL bit */
    *reg_addr &= ~DEPCTL_STALL;

    ep_type = (DEPCTL_EPTYPE & *reg_addr) >> 18;

    /* reset data PID of the periodic endpoints */
    if (((uint8_t)USB_EPTYPE_INTR == ep_type) || ((uint8_t)USB_EPTYPE_BULK == ep_type))
    {
        *reg_addr |= DEPCTL_SD0PID;
    }

    return USB_OK;
}

/*!
    \brief      read device IN endpoint interrupt flag register
    \param[in]  udev: pointer to USB device
    \param[in]  ep_num: endpoint number
    \param[out] none
    \retval     interrupt value
*/
uint32_t usb_iepintr_read(usb_core_driver *udev, uint8_t ep_num)
{
    __IO uint32_t value = 0U;
    uint32_t fifoemptymask, commonintmask;

    commonintmask = udev->regs.dr->DIEPINTEN;
    fifoemptymask = udev->regs.dr->DIEPFEINTEN;

    /* check FIFO empty interrupt enable bit */
    commonintmask |= ((fifoemptymask >> ep_num) & 0x1U) << 7;

    value = udev->regs.er_in[ep_num]->DIEPINTF & commonintmask;

    return value;
}

/*!
    \brief      configures OUT endpoint 0 to receive SETUP packets
    \param[in]  udev: pointer to USB device
    \param[out] none
    \retval     none
*/
void usb_ctlep_startout(usb_core_driver *udev)
{
    /* set OUT endpoint 0 receive length to 24 bytes, 1 packet and 3 SETUP packets */
    udev->regs.er_out[0]->DOEPLEN = DOEP0_TLEN(8U * 3U) | DOEP0_PCNT(1U) | DOEP0_STPCNT(3U);

    if ((uint8_t)USB_USE_DMA == udev->bp.transfer_mode)
    {
        udev->regs.er_out[0]->DOEPDMAADDR = (uint32_t)&udev->dev.control.req;

        /* endpoint enable */
        udev->regs.er_out[0]->DOEPCTL |= DEPCTL_EPACT | DEPCTL_EPEN;
    }
}

/*!
    \brief      active remote wakeup signaling
    \param[in]  udev: pointer to USB device
    \param[out] none
    \retval     none
*/
void usb_rwkup_active(usb_core_driver *udev)
{
    if (udev->dev.pm.dev_remote_wakeup)
    {
        if (udev->regs.dr->DSTAT & DSTAT_SPST)
        {
            if (udev->bp.low_power)
            {
                /* ungate USB core clock */
                *udev->regs.PWRCLKCTL &= ~(PWRCLKCTL_SHCLK | PWRCLKCTL_SUCLK);
            }

            /* active remote wakeup signaling */
            udev->regs.dr->DCTL |= DCTL_RWKUP;

            usb_mdelay(5U);

            udev->regs.dr->DCTL &= ~DCTL_RWKUP;
        }
    }
}

/*!
    \brief      USB device suspend
    \param[in]  udev: pointer to USB device
    \param[out] none
    \retval     none
*/
void usb_dev_suspend(usb_core_driver *udev)
{
    __IO uint32_t devstat = udev->regs.dr->DSTAT;

    if ((devstat & DSTAT_SPST) && (udev->bp.low_power))
    {
        /* switch-off the USB clocks */
        *udev->regs.PWRCLKCTL |= PWRCLKCTL_SHCLK;

        /* enter DEEP_SLEEP mode with LDO in low power mode */
        pmu_to_deepsleepmode(WFI_CMD);
    }
}

/*!
    \brief      stop the device and clean up FIFOs
    \param[in]  udev: pointer to USB device
    \param[out] none
    \retval     none
*/
void usb_dev_stop(usb_core_driver *udev)
{
    uint32_t i;

    udev->dev.cur_status = 1U;

    /* clear all interrupt flag and enable bits */
    for (i = 0U; i < udev->bp.num_ep; i++)
    {
        udev->regs.er_in[i]->DIEPINTF = 0xFFU;
        udev->regs.er_out[i]->DOEPINTF = 0xFFU;
    }

    udev->regs.dr->DIEPINTEN = 0U;
    udev->regs.dr->DOEPINTEN = 0U;
    udev->regs.dr->DAEPINTEN = 0U;
    udev->regs.dr->DAEPINT = 0xFFFFFFFFU;

    /* flush the FIFO */
    (void)usb_rxfifo_flush(&udev->regs);
    (void)usb_txfifo_flush(&udev->regs, 0x10U);
}

/*!
    \brief      usb battery charging detect operation
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     bcd type
*/
bcd_type usbd_bcd_detect(usb_core_driver *udev)
{
    udev->regs.gr->GCCFG |= GCCFG_DCDEN;

    usb_mdelay(1000U);

    if (0U == (udev->regs.gr->GCCFG & GCCFG_DCDF))
    {
        udev->regs.gr->GCCFG &= ~GCCFG_DCDEN;

        return BCD_ERROR;
    }

    udev->regs.gr->GCCFG &= ~GCCFG_DCDEN;
    usb_mdelay(20U);
    udev->regs.gr->GCCFG |= GCCFG_PEMEN;
    usb_mdelay(50U);

    if (udev->regs.gr->GCCFG & GCCFG_PDF)
    {
        udev->regs.gr->GCCFG &= ~GCCFG_PEMEN;
        usb_mdelay(20U);
        udev->regs.gr->GCCFG |= GCCFG_SDMEN;
        usb_mdelay(50U);

        if (udev->regs.gr->GCCFG & GCCFG_SDF)
        {
            udev->regs.gr->GCCFG &= ~GCCFG_SDMEN;
            usb_mdelay(20U);

            return BCD_DCP;
        }
        else
        {
            udev->regs.gr->GCCFG &= ~GCCFG_SDMEN;
            usb_mdelay(20U);

            return BCD_CDP;
        }
    }
    else if (udev->regs.gr->GCCFG & GCCFG_PS2F)
    {
        udev->regs.gr->GCCFG &= ~GCCFG_PEMEN;
        usb_mdelay(20U);

        return BCD_PS2;
    }
    else
    {
        udev->regs.gr->GCCFG &= ~GCCFG_PEMEN;
        usb_mdelay(20U);

        return BCD_SDP;
    }
}

#endif /* BSP_USING_USB && RT_USING_USB_DEVICE */
