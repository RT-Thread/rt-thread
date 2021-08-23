/*!
    \file  usbd_int.c
    \brief USB device power interrupt routines

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

extern uint32_t g_interrupt_mask;
extern __IO uint8_t g_suspend_enabled;
extern __IO uint8_t g_remote_wakeup_on;
extern __IO uint8_t g_ESOF_count;

#ifdef LPM_ENABLED
__IO uint32_t L1_remote_wakeup = 0U;
__IO uint32_t L1_resume = 0U;
__IO uint32_t besl = 0U;
#endif /* LPM_ENABLED */

static uint8_t  usbd_intf_lpst    (usbd_core_handle_struct *pudev);
static uint8_t  usbd_intf_sof     (usbd_core_handle_struct *pudev);
static uint8_t  usbd_intf_esof    (usbd_core_handle_struct *pudev);
static uint8_t  usbd_intf_reset   (usbd_core_handle_struct *pudev);
static uint8_t  usbd_intf_suspend (usbd_core_handle_struct *pudev);
static uint8_t  usbd_intf_wakeup  (usbd_core_handle_struct *pudev);

/*!
    \brief      USB interrupt events service routine
    \param[in]  none
    \param[out] none
    \retval     none
*/
void  usbd_isr (void)
{
    __IO uint16_t interrupt_flag = 0U;
    __IO uint16_t ctlr = 0U;

    interrupt_flag = USBD_REG_GET(USBD_INTF);

    if (g_interrupt_mask & INTF_STIF & interrupt_flag) {
        /* the endpoint successful transfer interrupt service */
        usbd_intf_lpst(&usb_device_dev);
    }

    if (g_interrupt_mask & INTF_WKUPIF & interrupt_flag) {
        /* clear wakeup interrupt flag in INTF */
        USBD_REG_SET(USBD_INTF, (uint16_t)CLR_WKUPIF);

        /* USB wakeup interrupt handle */
        usbd_intf_wakeup(&usb_device_dev);

#ifdef LPM_ENABLED
        /* clear L1 remote wakeup flag */
        L1_remote_wakeup = 0;
#endif /* LPM_ENABLED */
    }

    if (g_interrupt_mask & INTF_SPSIF & interrupt_flag) {
        if(!(USBD_REG_GET(USBD_CTL) & CTL_RSREQ)) {
            /* process library core layer suspend routine*/
            usbd_intf_suspend(&usb_device_dev);

            /* clear of suspend interrupt flag bit must be done after setting of CTLR_SETSPS */
            USBD_REG_SET(USBD_INTF, (uint16_t)CLR_SPSIF);
        }
    }

    if (g_interrupt_mask & INTF_SOFIF & interrupt_flag) {
        /* clear SOF interrupt flag in INTF */
        USBD_REG_SET(USBD_INTF, (uint16_t)CLR_SOFIF);

        /* USB SOF interrupt handle */
        usbd_intf_sof(&usb_device_dev);
    }

    if (g_interrupt_mask & INTF_ESOFIF & interrupt_flag) {
        /* clear ESOF interrupt flag in INTF */
        USBD_REG_SET(USBD_INTF, (uint16_t)CLR_ESOFIF);

        /* USB ESOF interrupt handle */
        usbd_intf_esof(&usb_device_dev);
    }

    if (g_interrupt_mask & INTF_RSTIF & interrupt_flag) {
        /* clear reset interrupt flag in INTF */
        USBD_REG_SET(USBD_INTF, (uint16_t)CLR_RSTIF);

        /* USB reset interrupt handle */
        usbd_intf_reset(&usb_device_dev);
    }

#ifdef LPM_ENABLED
    if (g_interrupt_mask & INTF_L1REQ & interrupt_flag) {
        /* clear L1 ST bit in LPM INTF */
        USBD_REG_SET(USBD_INTF, CLR_L1REQ);

        /* read BESL field from subendpoint0 register which coressponds to HIRD parameter in LPM spec */
        besl = (USBD_REG_GET(USBD_LPMCS) & LPMCS_BLSTAT) >> 4;

        /* read BREMOTEWAKE bit from subendpoint0 register which corresponding to bRemoteWake bit in LPM request */
        L1_remote_wakeup = (USBD_REG_GET(USBD_LPMCS) & LPMCS_REMWK) >> 8;

        /* process USB device core layer suspend routine */
        /* enter USB model in suspend and system in low power mode (DEEP_SLEEP mode) */
        usbd_intf_suspend(&usb_device_dev);
    }
#endif /* LPM_ENABLED */
}

/*!
    \brief      handle USB high priority successful transfer event 
    \param[in]  pudev: pointer to USB device instance
    \param[out] none
    \retval     USB device operation status
*/
uint8_t  usbd_intf_hpst (usbd_core_handle_struct *pudev)
{
    uint8_t ep_num = 0U;

    __IO uint16_t int_status = 0U;
    __IO uint16_t ep_value = 0U;

    usb_ep_struct *ep = NULL;

    /* wait till interrupts are not pending */
    while (0U != ((int_status = USBD_INTF) & (uint16_t)INTF_STIF)) {
        /* get endpoint number and the value of control and state register */
        ep_num = (uint8_t)(int_status & INTF_EPNUM);
        ep_value = USBD_EPxCS(ep_num);

        if (0U == (int_status & INTF_DIR)) {
            /* handle the in direction transaction */

            ep = &(pudev->in_ep[ep_num]);

            if (0U != (ep_value & EPxCS_TX_ST)) {
                /* clear successful transmit interrupt flag */
                USBD_ENDP_TX_STAT_CLEAR(ep_num);
                
                if (ep_value & EPxCS_TX_DTG) {
                    /* just handle single buffer situation */
                    ep->trs_count = (pbuf_reg + ep_num)->tx_count & EPTCNT_CNT;
                }

                /* maybe mutiple packets */
                ep->trs_buf += ep->trs_count;

                usbd_in_transaction(pudev, ep_num);
            }
        } else {
            /* handle the out direction transaction */

            uint16_t count = 0U;

            ep = &(pudev->out_ep[ep_num]);

            if (0U != (ep_value & EPxCS_RX_ST)) {
                /* clear successful receive interrupt flag */
                USBD_ENDP_RX_STAT_CLEAR(ep_num);

                if (ep_value & EPxCS_TX_DTG) {
                    count = (pbuf_reg + ep_num)->tx_count & (uint16_t)EPRCNT_CNT;

                    if (0U != count) {
                        usbd_ep_data_read(ep->trs_buf, (pbuf_reg + ep_num)->tx_addr, count);
                    }
                } else {
                    count = (pbuf_reg + ep_num)->rx_count & (uint16_t)EPRCNT_CNT;

                    if (0U != count) {
                        usbd_ep_data_read(ep->trs_buf, (pbuf_reg + ep_num)->rx_addr, count);
                    }
                }

                user_buffer_free(ep_num, DBUF_EP_OUT);

                /* maybe mutiple packets */
                ep->trs_count += count;
                ep->trs_buf += count;
                ep->trs_len -= count;

                if ((0U == ep->trs_len) || (count < ep->maxpacket)) {
                    USBD_ENDP_TX_STATUS_SET(ep_num, EPRX_NAK);

                    /* enter data OUT status */
                    usbd_out_transaction(pudev, ep_num);

                    ep->trs_count = 0U;
                }
            }
        }
    }

    return USBD_OK;
}

/*!
    \brief      handle USB low priority successful transfer event 
    \param[in]  pudev: pointer to USB device instance
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t  usbd_intf_lpst (usbd_core_handle_struct *pudev)
{
    uint8_t ep_num = 0U;

    __IO uint16_t int_status = 0U;
    __IO uint16_t ep_value = 0U;

    usb_ep_struct *ep = NULL;

    /* wait till interrupts are not pending */
    while (0U != ((int_status = USBD_REG_GET(USBD_INTF)) & (uint16_t)INTF_STIF)) {
        /* get endpoint number and the value of control and state register */
        ep_num = (uint8_t)(int_status & INTF_EPNUM);
        ep_value = USBD_REG_GET(USBD_EPxCS(ep_num));

        if (0U == (int_status & INTF_DIR)) {
            /* handle the in direction transaction */

            ep = &(pudev->in_ep[ep_num]);

            if (0U != (ep_value & EPxCS_TX_ST)) {
                /* clear successful transmit interrupt flag */
                USBD_ENDP_TX_STAT_CLEAR(ep_num);

                /* just handle single buffer situation */
                ep->trs_count = (pbuf_reg + ep_num)->tx_count & EPTCNT_CNT;

                /* maybe mutiple packets */
                ep->trs_buf += ep->trs_count;

                usbd_in_transaction(pudev, ep_num);
            }
        } else {
            /* handle the out direction transaction */

            uint16_t count = 0U;

            ep = &(pudev->out_ep[ep_num]);

            if (0U != (ep_value & EPxCS_RX_ST)) {
                /* clear successful receive interrupt flag */
                USBD_ENDP_RX_STAT_CLEAR(ep_num);

                count = (pbuf_reg + ep_num)->rx_count & (uint16_t)EPRCNT_CNT;

                if (0U != count) {
                    if (0U != (ep_value & EPxCS_SETUP)) {
                        /* handle setup packet */
                        usbd_ep_data_read(&(pudev->setup_packet[0]), pbuf_reg->rx_addr, count);

                        /* enter setup status */
                        usbd_setup_transaction(pudev);

                        return USBD_OK;
                    } else {
                        usbd_ep_data_read(ep->trs_buf, (pbuf_reg + ep_num)->rx_addr, count);
                    }
                }

                /* maybe mutiple packets */
                ep->trs_count += count;
                ep->trs_buf += count;
                ep->trs_len -= count;

                if ((0U == ep->trs_len) || (count < ep->maxpacket)) {
                    /* enter data OUT status */
                    usbd_out_transaction(pudev, ep_num);

                    ep->trs_count = 0U;
                } else {
                    usbd_ep_rx(pudev, ep_num, ep->trs_buf, (uint16_t)ep->trs_len);
                }
            }
        }   
    }

    return USBD_OK;
}

/*!
    \brief      handle USB SOF event
    \param[in]  pudev: pointer to USB device instance
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t  usbd_intf_sof (usbd_core_handle_struct *pudev)
{
    /* if necessary, user can add code here */
    if (NULL != usbd_int_fops) {
        usbd_int_fops->SOF(pudev);
    }

    return USBD_OK;
}

/*!
    \brief      handle USB expect SOF event
    \param[in]  pudev: pointer to USB device instance
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t  usbd_intf_esof (usbd_core_handle_struct *pudev)
{
    /* control resume time by ESOFs */
    if (g_ESOF_count > 0U) {
        g_ESOF_count--;

        if (0U == g_ESOF_count) {
            if (1U == g_remote_wakeup_on) {
                USBD_REG_SET(USBD_CTL, USBD_REG_GET(USBD_CTL) & ~CTL_RSREQ);

                g_remote_wakeup_on = 0U;
            } else {
                USBD_REG_SET(USBD_CTL, USBD_REG_GET(USBD_CTL) | CTL_RSREQ);

                g_ESOF_count = 3U;
                g_remote_wakeup_on = 1U;
            }
        }
    }

    return USBD_OK;
}

/*!
    \brief      handle USB reset event
    \param[in]  pudev: pointer to USB device instance
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t  usbd_intf_reset (usbd_core_handle_struct *pudev)
{
    uint8_t i;

    g_free_buf_addr = ENDP_BUF_ADDR;

    /* configure endpoint 0 buffer */
    pbuf_reg->tx_addr = (uint16_t)g_free_buf_addr;
    g_free_buf_addr += USBD_EP0_MAX_SIZE;

    pbuf_reg->rx_addr = (uint16_t)g_free_buf_addr;
    g_free_buf_addr += USBD_EP0_MAX_SIZE;

    /* configure endpoint 0 Rx count */
    if (USBD_EP0_MAX_SIZE > 62U) {
        pbuf_reg->rx_count = ((USBD_EP0_MAX_SIZE << 5U) - 1U) | 0x8000U;
    } else {
        pbuf_reg->rx_count = ((USBD_EP0_MAX_SIZE + 1U) & ~1U) << 9U;
    }

    pudev->in_ep[EP0].maxpacket = USBD_EP0_MAX_SIZE;
    pudev->out_ep[EP0].maxpacket = USBD_EP0_MAX_SIZE;

    /* set endpoints address */
    for (i = 0U; i < EP_COUNT; i++)
    {
        _EP_ADDR_SET(i, i);
    }
    
   /* set device address as default address 0 */
    USBD_REG_SET(USBD_DADDR, DADDR_USBEN);

    /* clear endpoint 0 register */
    USBD_REG_SET(USBD_EPxCS(EP0), USBD_EPxCS(EP0));

    USBD_REG_SET(USBD_EPxCS(EP0), EP_CONTROL | EPRX_VALID | EPTX_NAK);

    pudev->status = USBD_DEFAULT;

    return USBD_OK;
}

/*!
    \brief      handle USB suspend event
    \param[in]  pudev: pointer to USB device instance
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t  usbd_intf_suspend (usbd_core_handle_struct *pudev)
{
    /* store the device current status */
    pudev->prev_status = pudev->status;

    /* set device in suspended state */
    pudev->status = USBD_SUSPENDED;

    /* enter USB in suspend and mcu system in low power mode */
    if (g_suspend_enabled) {
        usbd_suspend();
    } else {
        /* if not possible then resume after xx ms */
        g_ESOF_count = 3U;
    }

    return USBD_OK;
}

/*!
    \brief      handle USB wakeup event
    \param[in]  pudev: pointer to USB device instance
    \param[out] none
    \retval     USB device operation status
*/
static uint8_t  usbd_intf_wakeup (usbd_core_handle_struct *pudev)
{
    /* restore the old status */
    pudev->status = pudev->prev_status;

#ifdef LPM_ENABLED
    if ((0U == g_remote_wakeup_on) && (0U == L1_resume)) {
        resume_mcu();
    } else if (1U == g_remote_wakeup_on) {
        /* no operation */
    } else {
        L1_resume = 0U;
    }
#else
    if (0U == g_remote_wakeup_on) {
        resume_mcu();
    }
#endif /* LPM_ENABLED */

    return USBD_OK;
}
