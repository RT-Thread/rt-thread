/*!
    \file  usbd_core.c
    \brief USB device driver

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

uint32_t g_interrupt_mask = 0U;
uint32_t g_free_buf_addr = ENDP_BUF_ADDR;

usbd_ep_buf_struct *pbuf_reg = (usbd_ep_buf_struct *)USBD_RAM;

/*!
    \brief      device core register initialization
    \param[in]  none
    \param[out] none
    \retval     none
*/
void  usbd_core_init (usbd_core_handle_struct *pudev)
{
    /* disable remote wakeup feature */
    pudev->remote_wakeup = 0U;

    /* just reset the CLOSE bit */
    USBD_REG_SET(USBD_CTL, CTL_SETRST);

    /* may be need wait some time(tSTARTUP) ... */

    /* clear SETRST bit in USBD_CTL register */
    USBD_REG_SET(USBD_CTL, 0U);

    /* clear all pending interrupts */
    USBD_REG_SET(USBD_INTF, 0U);

    /* set allocation buffer address */
    USBD_REG_SET(USBD_BADDR, BUFFER_ADDRESS & 0xFFF8U);

    g_interrupt_mask = IER_MASK;

#ifdef LPM_ENABLED
    /* enable L1REQ interrupt */
    USBD_REG_SET(USBD_LPMCS, LPMCS_LPMACK | LPMCS_LPMEN);
#endif /* LPM_ENABLED */

    /* enable all interrupts mask bits */
    USBD_REG_SET(USBD_CTL, g_interrupt_mask);
}

/*!
    \brief      free buffer used from application by toggling the SW_BUF byte
    \param[in]  ep_num: endpoint identifier (0..7)
    \param[in]  dir: endpoint direction which can be OUT(0) or IN(1)
    \param[out] none
    \retval     None
*/
void  user_buffer_free (uint8_t ep_num, uint8_t dir)
{
    if (DBUF_EP_OUT == dir) {
        USBD_SWBUF_RX_TOGGLE(ep_num);
    } else if (DBUF_EP_IN == dir) {
        USBD_SWBUF_TX_TOGGLE(ep_num);
    } else {
        /* no operation */
    }
}

/*!
    \brief      device core register configure when stop device
    \param[in]  none
    \param[out] none
    \retval     none
*/
void  usbd_core_deinit (void)
{
    /* disable all interrupts and set USB reset */
    USBD_REG_SET(USBD_CTL, CTL_SETRST);

    /* clear all interrupt flags */
    USBD_REG_SET(USBD_INTF, 0U);

    /* close device */
    USBD_REG_SET(USBD_CTL, CTL_SETRST | CTL_CLOSE);
}

/*!
    \brief      endpoint initialization
    \param[in]  pudev: pointer to USB core instance
    \param[in]  buf_kind: kind of buffer
    \param[in]  pep_desc: pointer to endpoint descriptor
    \param[out] none
    \retval     none
*/
void  usbd_ep_init (usbd_core_handle_struct *pudev, usbd_epkind_enum buf_kind, void *ep_desc)
{
    usb_descriptor_endpoint_struct *desc_ep = (usb_descriptor_endpoint_struct *)ep_desc;

    uint8_t ep_num = desc_ep->bEndpointAddress & 0x0FU;
    uint32_t reg_value = 0;

    /* set the endpoint type */
    switch (desc_ep->bmAttributes & USB_EPTYPE_MASK) {
    case ENDP_CONTROL:
        reg_value = EP_CONTROL;
        break;
    case ENDP_BULK:
        reg_value = EP_BULK;
        break;
    case ENDP_INT:
        reg_value = EP_INTERRUPT;
        break;
    case ENDP_ISOC:
        reg_value = EP_ISO;
        break;
    default:
        break;
    }

    USBD_REG_SET(USBD_EPxCS(ep_num), reg_value | ep_num);

    reg_value = desc_ep->wMaxPacketSize;

    if (desc_ep->bEndpointAddress >> 7U) {
        usb_ep_struct *ep = &pudev->in_ep[ep_num];

        ep->maxpacket = reg_value;

        /* set the endpoint transmit buffer address */
        (pbuf_reg + ep_num)->tx_addr = (uint16_t)g_free_buf_addr;

        reg_value = (reg_value + 1U) & ~1U;

        g_free_buf_addr += reg_value;

        if (ENDP_DBL_BUF == buf_kind) {
            USBD_ENDP_DOUBLE_BUF_SET(ep_num);

            (pbuf_reg + ep_num)->rx_addr = (uint16_t)g_free_buf_addr;

            g_free_buf_addr += reg_value;

            USBD_ENDP_TX_STATUS_SET(ep_num, EPTX_VALID);
            USBD_ENDP_RX_STATUS_SET(ep_num, EPRX_DISABLED);
        } else {
            /* configure the endpoint status as NAK status */
            USBD_ENDP_TX_STATUS_SET(ep_num, EPTX_NAK);
        }
    } else {
        usb_ep_struct *ep = &pudev->out_ep[ep_num];

        ep->maxpacket = reg_value;

        if (ENDP_DBL_BUF == buf_kind) {
            USBD_ENDP_DOUBLE_BUF_SET(ep_num);

            USBD_DTG_TX_TOGGLE(ep_num);

            /* set the endpoint transmit buffer address */
            (pbuf_reg + ep_num)->tx_addr = (uint16_t)g_free_buf_addr;

            if (reg_value > 62U) {
                reg_value = (reg_value + 31U) & ~31U;
                (pbuf_reg + ep_num)->tx_count = (uint16_t)(((reg_value << 5U) - 1U) | 0x8000U);
            } else {
                reg_value = (reg_value + 1U) & ~1U;
                (pbuf_reg + ep_num)->tx_count = (uint16_t)(reg_value << 9U);
            }

            g_free_buf_addr += reg_value;
        }

        reg_value = desc_ep->wMaxPacketSize;

        /* set the endpoint receive buffer address */
        (pbuf_reg + ep_num)->rx_addr = (uint16_t)g_free_buf_addr;

        if (reg_value > 62U) {
            reg_value = (reg_value + 31U) & ~31U;
            (pbuf_reg + ep_num)->rx_count = (uint16_t)(((reg_value << 5U) - 1U) | 0x8000U);
        } else {
            reg_value = (reg_value + 1U) & ~1U;
            (pbuf_reg + ep_num)->rx_count = (uint16_t)(reg_value << 9U);
        }

        if (ENDP_DBL_BUF == buf_kind) {
            USBD_ENDP_RX_STATUS_SET(ep_num, EPRX_DISABLED);
            USBD_ENDP_TX_STATUS_SET(ep_num, EPTX_NAK);
        } else {
            /* configure the endpoint status as NAK status */
            USBD_ENDP_RX_STATUS_SET(ep_num, EPRX_NAK);
        }
    }
}

/*!
    \brief      configure the endpoint when it is disabled
    \param[in]  pudev: pointer to USB core instance
    \param[in]  ep_addr: endpoint address
                  in this parameter:
                    bit0..bit6: endpoint number (0..7)
                    bit7: endpoint direction which can be IN(1) or OUT(0)
    \param[out] none
    \retval     none
*/
void  usbd_ep_deinit (usbd_core_handle_struct *pudev, uint8_t ep_addr)
{
    uint8_t ep_num = ep_addr & 0x7F;

    if (ep_addr >> 7) {
        USBD_DTG_TX_CLEAR(ep_num);

        /* configure the endpoint status as DISABLED */
        USBD_ENDP_TX_STATUS_SET(ep_num, EPTX_DISABLED); 
    } else {
        USBD_DTG_RX_CLEAR(ep_num);

        /* configure the endpoint status as DISABLED */
        USBD_ENDP_RX_STATUS_SET(ep_num, EPRX_DISABLED);
    }
}

/*!
    \brief      endpoint prepare to receive data
    \param[in]  pudev: pointer to usb core instance
    \param[in]  ep_addr: endpoint address
                  in this parameter:
                    bit0..bit6: endpoint number (0..7)
                    bit7: endpoint direction which can be IN(1) or OUT(0)
    \param[in]  pbuf: user buffer address pointer
    \param[in]  buf_len: buffer length
    \param[out] none
    \retval     none
*/
void  usbd_ep_rx (usbd_core_handle_struct *pudev, uint8_t ep_addr, uint8_t *pbuf, uint16_t buf_len)
{
    usb_ep_struct *ep;
    uint8_t ep_num = ep_addr & 0x7FU;

    ep = &pudev->out_ep[ep_num];

    /* configure the transaction level parameters */
    ep->trs_buf = pbuf;
    ep->trs_len = buf_len;

    /* enable endpoint to receive */
    USBD_ENDP_RX_STATUS_SET(ep_num, EPRX_VALID);
}

/*!
    \brief      endpoint prepare to transmit data
    \param[in]  pudev: pointer to USB core instance
    \param[in]  ep_addr: endpoint address
                  in this parameter:
                    bit0..bit6: endpoint number (0..7)
                    bit7: endpoint direction which can be IN(1) or OUT(0)
    \param[in]  pbuf: transmit buffer address pointer
    \param[in]  buf_len: buffer length
    \param[out] none
    \retval     none
*/
void  usbd_ep_tx (usbd_core_handle_struct *pudev, uint8_t ep_addr, uint8_t *pbuf, uint16_t buf_len)
{
    __IO uint32_t len = 0U;
    uint8_t ep_num = ep_addr & 0x7FU;
    usb_ep_struct *ep = &pudev->in_ep[ep_num];

    /* configure the transaction level parameters */
    ep->trs_buf = pbuf;
    ep->trs_len = buf_len;
    ep->trs_count = 0U;

    /* transmit length is more than one packet */
    if (ep->trs_len > ep->maxpacket) {
        len = ep->maxpacket;
    } else {
        len = ep->trs_len;
    }

    usbd_ep_data_write(ep->trs_buf, (pbuf_reg + ep_num)->tx_addr, (uint16_t)len);
    (pbuf_reg + ep_num)->tx_count = (uint16_t)len;

    /* enable endpoint to transmit */
    USBD_ENDP_TX_STATUS_SET(ep_num, EPTX_VALID);
}

/*!
    \brief      set an endpoint to stall status
    \param[in]  pudev: pointer to usb core instance
    \param[in]  ep_addr: endpoint address
                  in this parameter:
                    bit0..bit6: endpoint number (0..7)
                    bit7: endpoint direction which can be IN(1) or OUT(0)
    \param[out] none
    \retval     none
*/
void  usbd_ep_stall (usbd_core_handle_struct *pudev, uint8_t ep_addr)
{
    uint8_t ep_num = ep_addr & 0x7FU;
    usb_ep_struct *ep;

    if (ep_addr >> 7U) {
        ep = &pudev->in_ep[ep_num];

        USBD_ENDP_TX_STATUS_SET(ep_num, EPTX_STALL);
    } else {
        ep = &pudev->out_ep[ep_num];

        USBD_ENDP_RX_STATUS_SET(ep_num, EPRX_STALL);
    }

    ep->stall = 1U;

    if (0U == ep_num) {
        /* control endpoint need to be stalled in two directions */
        USBD_ENDP_RX_TX_STATUS_SET(ep_num, EPRX_STALL, EPTX_STALL); 
    }
}

/*!
    \brief      clear endpoint stalled status
    \param[in]  pudev: pointer to usb core instance
    \param[in]  ep_addr: endpoint address
                  in this parameter:
                    bit0..bit6: endpoint number (0..7)
                    bit7: endpoint direction which can be IN(1) or OUT(0)
    \param[out] none
    \retval     none
*/
void  usbd_ep_clear_stall (usbd_core_handle_struct *pudev, uint8_t ep_addr)
{
    uint8_t ep_num = ep_addr & 0x7FU;
    usb_ep_struct *ep;

    if (ep_addr >> 7U) {
        ep = &pudev->in_ep[ep_num];

        /* clear endpoint data toggle bit */
        USBD_DTG_TX_CLEAR(ep_num);

        /* clear endpoint stall status */
        USBD_ENDP_TX_STATUS_SET(ep_num, EPTX_VALID);
    } else {
        ep = &pudev->out_ep[ep_num];

        /* clear endpoint data toggle bit */
        USBD_DTG_RX_CLEAR(ep_num);

        /* clear endpoint stall status */
        USBD_ENDP_RX_STATUS_SET(ep_num, EPRX_VALID);
    }

    ep->stall = 0U;
}

/*!
    \brief      get the endpoint status
    \param[in]  pudev: pointer to usb core instance
    \param[in]  ep_addr: endpoint address
                  in this parameter:
                    bit0..bit6: endpoint number (0..7)
                    bit7: endpoint direction which can be IN(1) or OUT(0)
    \param[out] none
    \retval     endpoint status
*/
uint8_t  usbd_ep_status_get (usbd_core_handle_struct *pudev, uint8_t ep_addr)
{
    if (ep_addr >> 7U) {
        return (uint8_t)USBD_ENDP_TX_STATUS_GET((ep_addr & 0x7FU));
    } else {
        return (uint8_t)USBD_ENDP_RX_STATUS_GET(ep_addr);
    }
}

/*!
    \brief      write datas from user fifo to USBRAM
    \param[in]  user_fifo: pointer to user fifo
    \param[in]  usbram_addr: the allocation buffer address of the endpoint
    \param[in]  bytes: the bytes count of the write datas
    \param[out] none
    \retval     none
*/
void  usbd_ep_data_write(uint8_t *user_fifo, uint16_t usbram_addr, uint16_t bytes)
{
    uint32_t n;
    uint32_t *write_addr = (uint32_t *)((uint32_t)(usbram_addr * 2U + USBD_RAM));

    for (n = 0U; n < (bytes + 1U) / 2U; n++) {
        *write_addr++ = *((__packed uint16_t*)user_fifo);
        user_fifo += 2U;
    }
}

/*!
    \brief      read datas from USBRAM to user fifo
    \param[in]  user_fifo: pointer to user fifo
    \param[in]  usbram_addr: the allocation buffer address of the endpoint
    \param[in]  bytes: the bytes count of the read datas
    \param[out] none
    \retval     none
*/
void  usbd_ep_data_read(uint8_t *user_fifo, uint16_t usbram_addr, uint16_t bytes)
{
    uint32_t n;
    uint32_t *read_addr = (uint32_t *)((uint32_t)(usbram_addr * 2U + USBD_RAM));

    for (n = 0U; n < (bytes + 1U) / 2U; n++) {
        *((__packed uint16_t*)user_fifo) = (uint16_t)*read_addr++;
        user_fifo += 2U;
    }
}

/*!
    \brief      get the received data length
    \param[in]  pudev: pointer to USB core instance
    \param[in]  ep_num: endpoint identifier which is in (0..7)
    \param[out] none
    \retval     received data length
*/
uint16_t  usbd_rx_count_get (usbd_core_handle_struct *pudev, uint8_t ep_num)
{
    return (uint16_t)pudev->out_ep[ep_num].trs_count;
}
