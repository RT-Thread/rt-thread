/*!
    \file    drv_usb_core.c
    \brief   USB core driver which can operate in host and device mode

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

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
#include "drv_usb_hw.h"

/* local function prototypes ('static') */
static void usb_core_reset (usb_core_regs *usb_regs);

/*!
    \brief      configures USB parameters
    \param[in]  udev: pointer to USB core instance
    \param[in]  usb_periph: USBHSx(x=0,1)
    \param[in]  usb_speed: USB speed type (full-speed or high-speed)
    \param[out] none
    \retval     none
*/
void usb_para_init(usb_core_driver *udev, uint32_t usb_periph, uint32_t usb_speed)
{
    usb_core_basic *usb_basic = &udev->bp;

    /* configure USB default transfer mode as FIFO mode */
    usb_basic->transfer_mode = (uint8_t)USB_USE_FIFO;

    /* USB default speed is full-speed */
    usb_basic->core_speed = (uint8_t)USB_SPEED_FULL;

    /* USB basic register address setting */
    switch(usb_periph)
    {
    case USBHS0:
        usb_basic->base_reg = (uint32_t)USBHS0_REG_BASE;
        break;
    case USBHS1:
        usb_basic->base_reg = (uint32_t)USBHS1_REG_BASE;
        break;
    default:
        break;
    }

    /* set the host channel numbers */
    usb_basic->num_pipe = USBHS_MAX_CHANNEL_COUNT;

    /* set the device endpoint numbers */
    usb_basic->num_ep = USBHS_MAX_EP_COUNT;

    if (USB_SPEED_HIGH == usb_speed)
    {
#ifdef USB_EXTERNAL_ULPI_PHY_ENABLED
        usb_basic->phy_itf = USB_ULPI_PHY_EXTERNAL;
#endif /* USB_EXTERNAL_ULPI_PHY_ENABLED */

#ifdef USB_EMBEDDED_HS_PHY_ENABLED
        usb_basic->phy_itf = USB_EMBEDDED_PHY_HS;
#endif /* USB_EMBEDDED_HS_PHY_ENABLED */
    } else if (USB_SPEED_FULL == usb_speed)
    {
#ifdef USB_EMBEDDED_FS_PHY_ENABLED
        usb_basic->phy_itf = USB_EMBEDDED_PHY_FS;
#endif /* USB_EMBEDDED_FS_PHY_ENABLED */
    } else {
        /* no operation */
    }

#ifdef USB_INTERNAL_DMA_ENABLED
    usb_basic->transfer_mode = USB_USE_DMA;
#endif /* USB_INTERNAL_DMA_ENABLED */

    usb_basic->sof_enable = (uint8_t)USB_SOF_OUTPUT;
    usb_basic->low_power = (uint8_t)USB_LOW_POWER;

#if (1U == LPM_ENABLED)
    usb_basic->lpm_enable = 1U;
#endif /* LPM_ENABLED */
}
/*!
    \brief      configure USB core basic
    \param[in]  usb_basic: pointer to USB capabilities
    \param[in]  usb_regs: pointer to USB core registers
    \param[out] none
    \retval     operation status
*/
usb_status usb_basic_init (usb_core_basic *usb_basic, usb_core_regs *usb_regs)
{
    /* assign main registers address */
    *usb_regs = (usb_core_regs)
    {
        .gr          = (usb_gr*) (usb_basic->base_reg + (uint32_t)USB_REG_OFFSET_CORE),
        .hr          = (usb_hr*) (usb_basic->base_reg + (uint32_t)USB_REG_OFFSET_HOST),
        .dr          = (usb_dr*) (usb_basic->base_reg + (uint32_t)USB_REG_OFFSET_DEV),

        .HPCS        = (uint32_t*) (usb_basic->base_reg + (uint32_t)USB_REG_OFFSET_PORT),
        .PWRCLKCTL   = (uint32_t*) (usb_basic->base_reg + (uint32_t)USB_REG_OFFSET_PWRCLKCTL)
    };

    /* assign device endpoint registers address */
    for (uint8_t i = 0U; i < usb_basic->num_ep; i++)
    {
        usb_regs->er_in[i] = (usb_erin *) \
            (usb_basic->base_reg + (uint32_t)USB_REG_OFFSET_EP_IN + (i * (uint32_t)USB_REG_OFFSET_EP));

        usb_regs->er_out[i] = (usb_erout *)\
            (usb_basic->base_reg + (uint32_t)USB_REG_OFFSET_EP_OUT + (i * (uint32_t)USB_REG_OFFSET_EP));
    }

    /* assign host pipe registers address */
    for (uint8_t i = 0U; i < usb_basic->num_pipe; i++)
    {
        usb_regs->pr[i] = (usb_pr *) \
            (usb_basic->base_reg + (uint32_t)USB_REG_OFFSET_CH_INOUT + (i * (uint32_t)USB_REG_OFFSET_CH));

        usb_regs->DFIFO[i] = (uint32_t *) \
            (usb_basic->base_reg + (uint32_t)USB_DATA_FIFO_OFFSET + (i * (uint32_t)USB_DATA_FIFO_SIZE));
    }

    return USB_OK;
}

/*!
    \brief      initializes the USB controller registers and
                prepares the core device mode or host mode operation
    \param[in]  usb_basic: pointer to USB capabilities
    \param[in]  usb_regs: pointer to USB core registers
    \param[out] none
    \retval     operation status
*/
usb_status usb_core_init (usb_core_basic usb_basic, usb_core_regs *usb_regs)
{
    /* disable USB global interrupt */
    usb_regs->gr->GAHBCS &= ~GAHBCS_GINTEN;

    if (USB_ULPI_PHY_EXTERNAL == usb_basic.phy_itf)
    {
        usb_regs->gr->GCCFG &= ~GCCFG_PWRON;

        usb_regs->gr->GUSBCS &= ~(GUSBCS_EMBPHY_HS | GUSBCS_EMBPHY_FS);

        if (usb_basic.sof_enable)
        {
            usb_regs->gr->GCCFG |= GCCFG_SOFOEN;
        }

        /* initialize the ULPI interface */
        usb_regs->gr->GUSBCS &= ~GUSBCS_ULPIEOI;

#ifdef USBHS_EXTERNAL_VBUS_ENABLED
        /* use external VBUS driver */
        usb_regs->gr->GUSBCS |= GUSBCS_ULPIEVD;
#else
        /* use internal VBUS driver */
        usb_regs->gr->GUSBCS &= ~GUSBCS_ULPIEVD;
#endif /* USBHS_EXTERNAL_VBUS_ENABLED */

        /* soft reset the core */
        usb_core_reset (usb_regs);
    } else if (USB_EMBEDDED_PHY_HS == usb_basic.phy_itf)
    {
        usb_regs->gr->GUSBCS |= GUSBCS_EMBPHY_HS;

        /* soft reset the core */
        usb_core_reset (usb_regs);

        usb_regs->gr->GCCFG = 0U;

#ifdef VBUS_SENSING_ENABLED
        /* active the transceiver and enable VBUS sensing */
        usb_regs->gr->GCCFG |=  GCCFG_VDEN | GCCFG_PWRON;
#else
    #ifdef USE_HOST_MODE
        usb_regs->gr->GOTGCS |= GOTGCS_AVOV | GOTGCS_AVOE;
    #endif /* USE_HOST_MODE */

    #ifdef USE_DEVICE_MODE
        usb_regs->gr->GOTGCS |= GOTGCS_BVOV | GOTGCS_BVOE;
    #endif /* USE_DEVICE_MODE */

        /* active the transceiver */
        usb_regs->gr->GCCFG |= GCCFG_PWRON;
#endif /* VBUS_SENSING_ENABLED */

        if (usb_basic.sof_enable)
        {
            usb_regs->gr->GCCFG |= GCCFG_SOFOEN;
        }

        usb_mdelay(20U);
    } else if (USB_EMBEDDED_PHY_FS == usb_basic.phy_itf)
    {
        usb_regs->gr->GUSBCS |= GUSBCS_EMBPHY_FS;

        /* soft reset the core */
        usb_core_reset (usb_regs);

#ifdef VBUS_SENSING_ENABLED
        /* active the transceiver and enable vbus sensing */
        usb_regs->gr->GCCFG |=  GCCFG_VDEN | GCCFG_PWRON;
#else
    #ifdef USE_HOST_MODE
        usb_regs->gr->GOTGCS |= GOTGCS_AVOV | GOTGCS_AVOE;
    #endif /* USE_HOST_MODE */

    #ifdef USE_DEVICE_MODE
        usb_regs->gr->GOTGCS |= GOTGCS_BVOV | GOTGCS_BVOE;
    #endif /* USE_DEVICE_MODE */

        /* active the transceiver */
        usb_regs->gr->GCCFG |= GCCFG_PWRON;
#endif /* VBUS_SENSING_ENABLED */

        /* enable SOF output */
        if (usb_basic.sof_enable)
        {
            usb_regs->gr->GCCFG |= GCCFG_SOFOEN;
        }

        usb_mdelay(20U);
    } else {
        /* no operation */
    }

    if ((uint8_t)USB_USE_DMA == usb_basic.transfer_mode)
    {
        usb_regs->gr->GAHBCS &= ~GAHBCS_BURST;
        usb_regs->gr->GAHBCS |= DMA_INCR8 | GAHBCS_DMAEN;
    }

#ifdef USE_OTG_MODE

    /* enable USB OTG features */
    usb_regs->gr->GUSBCS |= GUSBCS_HNPCEN | GUSBCS_SRPCEN;

    /* enable the USB wakeup and suspend interrupts */
    usb_regs->gr->GINTF = 0xBFFFFFFFU;

    usb_regs->gr->GINTEN = GINTEN_WKUPIE | GINTEN_SPIE | \
                                     GINTEN_OTGIE | GINTEN_SESIE | GINTEN_IDPSCIE;

#endif /* USE_OTG_MODE */

    return USB_OK;
}

/*!
    \brief      write a packet into the TX FIFO associated with the endpoint
    \param[in]  usb_regs: pointer to USB core registers
    \param[in]  src_buf: pointer to source buffer
    \param[in]  fifo_num: FIFO number which is in (0..5)
    \param[in]  byte_count: packet byte count
    \param[out] none
    \retval     operation status
*/
usb_status usb_txfifo_write (usb_core_regs *usb_regs,
                             uint8_t *src_buf,
                             uint8_t  fifo_num,
                             uint16_t byte_count)
{
    uint32_t word_count = (byte_count + 3U) / 4U;
    __IO uint32_t *fifo = usb_regs->DFIFO[fifo_num];

    while (word_count-- > 0U)
    {
        *fifo = *((__IO uint32_t *)src_buf);

        src_buf += 4U;
    }

    return USB_OK;
}

/*!
    \brief      read a packet from the Rx FIFO associated with the endpoint
    \param[in]  usb_regs: pointer to USB core registers
    \param[in]  dest_buf: pointer to destination buffer
    \param[in]  byte_count: packet byte count
    \param[out] none
    \retval     void type pointer
*/
void *usb_rxfifo_read (usb_core_regs *usb_regs, uint8_t *dest_buf, uint16_t byte_count)
{
    __IO uint32_t word_count = (byte_count + 3U) / 4U;
    __IO uint32_t *fifo = usb_regs->DFIFO[0];

    while (word_count-- > 0U)
    {
        *(__IO uint32_t *)dest_buf = *fifo;

        dest_buf += 4U;
    }

    return ((void *)dest_buf);
}

/*!
    \brief      flush a TX FIFO or all TX FIFOs
    \param[in]  usb_regs: pointer to USB core registers
    \param[in]  fifo_num: FIFO number which is in (0..5)
    \param[out] none
    \retval     operation status
*/
usb_status usb_txfifo_flush (usb_core_regs *usb_regs, uint8_t fifo_num)
{
    usb_regs->gr->GRSTCTL = ((uint32_t)fifo_num << 6U) | GRSTCTL_TXFF;

    /* wait for Tx FIFO flush bit is set */
    while (usb_regs->gr->GRSTCTL & GRSTCTL_TXFF)
    {
        /* no operation */
    }

    /* wait for 3 PHY clocks*/
    usb_udelay(3U);

    return USB_OK;
}

/*!
    \brief      flush the entire Rx FIFO
    \param[in]  usb_regs: pointer to USB core registers
    \param[out] none
    \retval     operation status
*/
usb_status usb_rxfifo_flush (usb_core_regs *usb_regs)
{
    usb_regs->gr->GRSTCTL = GRSTCTL_RXFF;

    /* wait for RX FIFO flush bit is set */
    while (usb_regs->gr->GRSTCTL & GRSTCTL_RXFF)
    {
        /* no operation */
    }

    /* wait for 3 PHY clocks */
    usb_udelay(3U);

    return USB_OK;
}

/*!
    \brief      set endpoint or channel TX FIFO size
    \param[in]  usb_regs: pointer to USB core registers
    \param[in]  fifo: TX FIFO number
    \param[in]  size: assigned TX FIFO size
    \param[out] none
    \retval     none
*/
void usb_set_txfifo(usb_core_regs *usb_regs, uint8_t fifo, uint16_t size)
{
    uint32_t tx_offset = usb_regs->gr->GRFLEN;

    if (0U == fifo)
    {
        usb_regs->gr->DIEP0TFLEN_HNPTFLEN = ((uint32_t)size << 16U) | tx_offset;
    } else {
        tx_offset += (usb_regs->gr->DIEP0TFLEN_HNPTFLEN) >> 16U;

        for (uint8_t i = 0U; i < (fifo - 1U); i++)
        {
            tx_offset += (usb_regs->gr->DIEPTFLEN[i] >> 16U);
        }

        usb_regs->gr->DIEPTFLEN[fifo - 1U] = ((uint32_t)size << 16U) | tx_offset;
    }
}

/*!
    \brief      configure USB core to soft reset
    \param[in]  usb_regs: pointer to USB core registers
    \param[out] none
    \retval     none
*/
static void usb_core_reset (usb_core_regs *usb_regs)
{
    /* enable core soft reset */
    usb_regs->gr->GRSTCTL |= GRSTCTL_CSRST;

    /* wait for the core to be soft reset */
    while (usb_regs->gr->GRSTCTL & GRSTCTL_CSRST)
    {
        /* no operation */
    }

    /* wait for additional 3 PHY clocks */
    usb_udelay(3U);
}

