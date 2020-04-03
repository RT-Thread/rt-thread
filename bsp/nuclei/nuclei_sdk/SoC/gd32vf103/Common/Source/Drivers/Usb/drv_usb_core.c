/*!
    \file  drv_usb_core.c
    \brief USB core driver which can operate in host and device mode

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
#include "drv_usb_hw.h"

/*!
    \brief      config USB core to soft reset
    \param[in]  usb_regs: USB core registers
    \param[out] none
    \retval     none
*/
static void usb_core_reset (usb_core_regs *usb_regs)
{
    /* enable core soft reset */
    usb_regs->gr->GRSTCTL |= GRSTCTL_CSRST;

    /* wait for the core to be soft reset */
    while (usb_regs->gr->GRSTCTL & GRSTCTL_CSRST);

    /* wait for addtional 3 PHY clocks */
    usb_udelay(3);
}

/*!
    \brief      config USB core basic 
    \param[in]  usb_basic: pointer to usb capabilities
    \param[in]  usb_regs: USB core registers
    \param[in]  usb_core: USB core
    \param[out] none
    \retval     operation status
*/
usb_status usb_basic_init (usb_core_basic *usb_basic, 
                           usb_core_regs  *usb_regs, 
                           usb_core_enum   usb_core)
{
    uint32_t i = 0, reg_base = 0;

    /* config USB default transfer mode as FIFO mode */
    usb_basic->transfer_mode = USB_USE_FIFO;

    /* USB default speed is full-speed */
    usb_basic->core_speed = USB_SPEED_FULL;

    usb_basic->core_enum = usb_core;

    switch (usb_core) {
    case USB_CORE_ENUM_HS:
        reg_base = USBHS_REG_BASE;

        /* set the host channel numbers */
        usb_basic->num_pipe = USBHS_MAX_CHANNEL_COUNT;

        /* set the device endpoint numbers */
        usb_basic->num_ep = USBHS_MAX_EP_COUNT;

#ifdef USB_ULPI_PHY_ENABLED
        usb_basic->phy_itf = USB_ULPI_PHY;
#else
        usb_basic->phy_itf = USB_EMBEDDED_PHY;
#endif /* USB_ULPI_PHY_ENABLED */

#ifdef USB_HS_INTERNAL_DMA_ENABLED
        bp->transfer_mode = USB_USE_DMA;
#endif /* USB_HS_INTERNAL_DMA_ENABLED */
        break;

    case USB_CORE_ENUM_FS:
        reg_base = USBFS_REG_BASE;

        /* set the host channel numbers */
        usb_basic->num_pipe = USBFS_MAX_CHANNEL_COUNT;

        /* set the device endpoint numbers */
        usb_basic->num_ep = USBFS_MAX_EP_COUNT;

        /* USBFS core use embedded physical layer */
        usb_basic->phy_itf = USB_EMBEDDED_PHY;
        break;

    default:
        return USB_FAIL;
    }

    usb_basic->sof_enable = USB_SOF_OUTPUT;
    usb_basic->low_power = USB_LOW_POWER;

    /* assign main registers address */
    *usb_regs = (usb_core_regs) {
        .gr          = (usb_gr*) (reg_base + USB_REG_OFFSET_CORE),
        .hr          = (usb_hr*) (reg_base + USB_REG_OFFSET_HOST),
        .dr          = (usb_dr*) (reg_base + USB_REG_OFFSET_DEV),

        .HPCS        = (uint32_t*) (reg_base + USB_REG_OFFSET_PORT),
        .PWRCLKCTL   = (uint32_t*) (reg_base + USB_REG_OFFSET_PWRCLKCTL)
    };

    /* assign device endpoint registers address */
    for (i = 0; i < usb_basic->num_ep; i++) {
        usb_regs->er_in[i] = (usb_erin *) \
            (reg_base + USB_REG_OFFSET_EP_IN + (i * USB_REG_OFFSET_EP));

        usb_regs->er_out[i] = (usb_erout *)\
            (reg_base + USB_REG_OFFSET_EP_OUT + (i * USB_REG_OFFSET_EP));
    }

    /* assign host pipe registers address */
    for (i = 0; i < usb_basic->num_pipe; i++) {
        usb_regs->pr[i] = (usb_pr *) \
            (reg_base + USB_REG_OFFSET_CH_INOUT + (i * USB_REG_OFFSET_CH));

        usb_regs->DFIFO[i] = (uint32_t *) \
            (reg_base + USB_DATA_FIFO_OFFSET + (i * USB_DATA_FIFO_SIZE));
    }

    return USB_OK;
}

/*!
    \brief      initializes the USB controller registers and 
                prepares the core device mode or host mode operation
    \param[in]  bp: usb capabilities
    \param[in]  core_regs: usb core registers
    \param[out] none
    \retval     operation status
*/
usb_status usb_core_init (usb_core_basic usb_basic, usb_core_regs *usb_regs)
{
    uint32_t reg_value = usb_regs->gr->GCCFG;

    /* disable USB global interrupt */
    usb_regs->gr->GAHBCS &= ~GAHBCS_GINTEN;

    if (USB_ULPI_PHY == usb_basic.phy_itf) {
        reg_value &= ~GCCFG_PWRON;

        if (usb_basic.sof_enable) {
            reg_value |= GCCFG_SOFOEN;
        }

        usb_regs->gr->GCCFG = GCCFG_SOFOEN;

        /* init the ULPI interface */
        usb_regs->gr->GUSBCS &= ~(GUSBCS_EMBPHY | GUSBCS_ULPIEOI);

#ifdef USBHS_EXTERNAL_VBUS_ENABLED
        /* use external VBUS driver */
        usb_regs->gr->GUSBCS |= GUSBCS_ULPIEVD;
#else
        /* use internal VBUS driver */
        usb_regs->gr->GUSBCS &= ~GUSBCS_ULPIEVD;
#endif

        /* soft reset the core */
        usb_core_reset (usb_regs);
    } else {
        usb_regs->gr->GUSBCS |= GUSBCS_EMBPHY;

        /* soft reset the core */
        usb_core_reset (usb_regs);

        /* active the transceiver and enable vbus sensing */
        reg_value = GCCFG_PWRON | GCCFG_VBUSACEN | GCCFG_VBUSBCEN;

#ifndef VBUS_SENSING_ENABLED
        reg_value |= GCCFG_VBUSIG;
#endif /* VBUS_SENSING_ENABLED */

        /* enable SOF output */
        if (usb_basic.sof_enable) {
            reg_value |= GCCFG_SOFOEN;
        }

        usb_regs->gr->GCCFG = reg_value;

        usb_mdelay(20);
    }

    if (USB_USE_DMA == usb_basic.transfer_mode) {
        usb_regs->gr->GAHBCS |= GAHBCS_DMAEN;
        usb_regs->gr->GAHBCS &= ~GAHBCS_BURST;
        usb_regs->gr->GAHBCS |= DMA_INCR8;
    }

#ifdef USE_OTG_MODE

    /* enable USB OTG features */
    usb_regs->gr->GUSBCS |= GUSBCS_HNPCAP | GUSBCS_SRPCAP;

    /* enable the USB wakeup and suspend interrupts */
    usb_regs->gr->GINTF = 0xBFFFFFFFU;

    usb_regs->gr->GINTEN = GINTEN_WKUPIE | GINTEN_SPIE | \
                                     GINTEN_OTGIE | GINTEN_SESIE | GINTEN_CIDPSCIE;

#endif /* USE_OTG_MODE */

    return USB_OK;
}

/*!
    \brief      write a packet into the Tx FIFO associated with the endpoint
    \param[in]  core_regs: usb core registers
    \param[in]  src_buf: pointer to source buffer
    \param[in]  fifo_num: FIFO number which is in (0..3)
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

    while (word_count-- > 0) {
        *fifo = *(( uint32_t *)src_buf);

        src_buf += 4U;
    }

    return USB_OK;
}

/*!
    \brief      read a packet from the Rx FIFO associated with the endpoint
    \param[in]  core_regs: usb core registers
    \param[in]  dest_buf: pointer to destination buffer
    \param[in]  byte_count: packet byte count
    \param[out] none
    \retval     void type pointer
*/
void *usb_rxfifo_read (usb_core_regs *usb_regs, uint8_t *dest_buf, uint16_t byte_count)
{
    uint32_t word_count = (byte_count + 3U) / 4U;

    __IO uint32_t *fifo = usb_regs->DFIFO[0];

    while (word_count-- > 0) {
        *( uint32_t *)dest_buf = *fifo;

        dest_buf += 4U;
    }

    return ((void *)dest_buf);
}

/*!
    \brief      flush a Tx FIFO or all Tx FIFOs
    \param[in]  core_regs: pointer to usb core registers
    \param[in]  fifo_num: FIFO number which is in (0..3)
    \param[out] none
    \retval     operation status
*/
usb_status usb_txfifo_flush (usb_core_regs *usb_regs, uint8_t fifo_num)
{
    usb_regs->gr->GRSTCTL = ((uint32_t)fifo_num << 6U) | GRSTCTL_TXFF;

    /* wait for Tx FIFO flush bit is set */
    while (usb_regs->gr->GRSTCTL & GRSTCTL_TXFF);

    /* wait for 3 PHY clocks*/
    usb_udelay(3);

    return USB_OK;
}

/*!
    \brief      flush the entire Rx FIFO
    \param[in]  core_regs: pointer to usb core registers
    \param[out] none
    \retval     operation status
*/
usb_status usb_rxfifo_flush (usb_core_regs *usb_regs)
{
    usb_regs->gr->GRSTCTL = GRSTCTL_RXFF;

    /* wait for Rx FIFO flush bit is set */
    while (usb_regs->gr->GRSTCTL & GRSTCTL_RXFF);

    /* wait for 3 PHY clocks */
    usb_udelay(3);

    return USB_OK;
}
