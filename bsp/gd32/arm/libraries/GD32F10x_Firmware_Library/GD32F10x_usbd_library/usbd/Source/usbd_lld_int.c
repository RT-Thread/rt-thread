 /*!
    \file    usbd_lld_int.c
    \brief   USB device low level interrupt routines

    \version 2020-07-17, V3.0.0, firmware for GD32F10x
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

#include "usbd_lld_int.h"
#include "usbd_lld_core.h"

/* local function prototypes ('static') */
static void usbd_int_suspend (usb_dev *udev);

/*!
    \brief      handle USB high priority successful transfer event
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
void usbd_int_hpst (usb_dev *udev)
{
    __IO uint16_t int_status = 0U;

    /* wait till interrupts are not pending */
    while ((int_status = (uint16_t)USBD_INTF) & (uint16_t)INTF_STIF) {
        /* get endpoint number */
        uint8_t ep_num = (uint8_t)(int_status & INTF_EPNUM);

        uint8_t transc_num = (uint8_t)TRANSC_UNKNOWN;

        if (int_status & INTF_DIR) {
            if (USBD_EPxCS(ep_num) & EPxCS_RX_ST) {
                uint16_t count = 0U;

                usb_transc *transc = &udev->transc_out[ep_num];

                /* clear successful receive interrupt flag */
                USBD_EP_RX_ST_CLEAR(ep_num);

                count = udev->drv_handler->ep_read (transc->xfer_buf, ep_num, (uint8_t)EP_BUF_DBL);

                user_buffer_free(ep_num, (uint8_t)DBUF_EP_OUT);

                transc->xfer_buf += count;
                transc->xfer_count += count;
                transc->xfer_len -= count;

                if ((0U == transc->xfer_len) || (count < transc->max_len)) {
                    USBD_EP_RX_STAT_SET(ep_num, EPRX_NAK);

                    transc_num = (uint8_t)TRANSC_OUT;
                }
            }
        } else {
            /* handle the in direction transaction */
            if (USBD_EPxCS(ep_num) & EPxCS_TX_ST) {
                /* clear successful transmit interrupt flag */
                USBD_EP_TX_ST_CLEAR(ep_num);

                transc_num = (uint8_t)TRANSC_IN;
            }
        }

        if ((uint8_t)TRANSC_UNKNOWN != transc_num) {
            udev->ep_transc[ep_num][transc_num](udev, ep_num);
        }
    }
}

/*!
    \brief      USB interrupt events service routine
    \param[in]  none
    \param[out] none
    \retval     none
*/
void usbd_isr (void)
{
    __IO uint16_t int_status = (uint16_t)USBD_INTF;
    __IO uint16_t int_flag = (uint16_t)(USBD_INTF & (USBD_CTL & USBD_INTEN));

    usb_dev *udev = usbd_core.dev;

    if (INTF_STIF & int_flag) {
        /* wait till interrupts are not pending */
        while ((int_status = (uint16_t)USBD_INTF) & (uint16_t)INTF_STIF) {
            /* get endpoint number */
            uint8_t ep_num = (uint8_t)(int_status & INTF_EPNUM);

            if (int_status & INTF_DIR) {
                /* handle the USB OUT direction transaction */
                if (USBD_EPxCS(ep_num) & EPxCS_RX_ST) {
                    /* clear successful receive interrupt flag */
                    USBD_EP_RX_ST_CLEAR(ep_num);

                    if (USBD_EPxCS(ep_num) & EPxCS_SETUP) {

                        if (ep_num == 0U) {
                            udev->ep_transc[ep_num][TRANSC_SETUP](udev, ep_num);
                        } else {
                            return;
                        }
                    } else {
                        usb_transc *transc = &udev->transc_out[ep_num];

                        uint16_t count = udev->drv_handler->ep_read (transc->xfer_buf, ep_num, (uint8_t)EP_BUF_SNG);

                        transc->xfer_buf += count;
                        transc->xfer_count += count;

                        if ((transc->xfer_count >= transc->xfer_len) || (count < transc->max_len)) {
                            if (udev->ep_transc[ep_num][TRANSC_OUT]) {
                                udev->ep_transc[ep_num][TRANSC_OUT](udev, ep_num);
                            }
                        } else {
                            udev->drv_handler->ep_rx_enable(udev, ep_num);
                        }
                    }
                }
            } else {
                /* handle the USB IN direction transaction */
                if (USBD_EPxCS(ep_num) & EPxCS_TX_ST) {
                    /* clear successful transmit interrupt flag */
                    USBD_EP_TX_ST_CLEAR(ep_num);

                    usb_transc *transc = &udev->transc_in[ep_num];

                    if (transc->xfer_len == 0U) {
                        if (udev->ep_transc[ep_num][TRANSC_IN]) {
                            udev->ep_transc[ep_num][TRANSC_IN](udev, ep_num);
                        }
                    } else {
                        usbd_ep_send(udev, ep_num, transc->xfer_buf, transc->xfer_len);
                    }
                }
            }
        }
    }

    if (INTF_WKUPIF & int_flag) {
        /* clear wakeup interrupt flag in INTF */
        CLR(WKUPIF);

        /* restore the old cur_status */
        udev->cur_status = udev->backup_status;

#ifdef LPM_ENABLED
        if ((0U == udev->pm.remote_wakeup_on) && (0U == udev->lpm.L1_resume)) {
            resume_mcu(udev);
        } else if (1U == udev->pm.remote_wakeup_on) {
            /* no operation */
        } else {
            udev->lpm.L1_resume = 0U;
        }

        /* clear L1 remote wakeup flag */
        udev->lpm.L1_remote_wakeup = 0U;
#else
        if (0U == udev->pm.remote_wakeup_on) {
            resume_mcu(udev);
        }
#endif /* LPM_ENABLED */
    }

    if (INTF_SPSIF & int_flag) {
        if(!(USBD_CTL & CTL_RSREQ)) {
            usbd_int_suspend (udev);

            /* clear of suspend interrupt flag bit must be done after setting of CTLR_SETSPS */
            CLR(SPSIF);
        }
    }

    if (INTF_SOFIF & int_flag) {
        /* clear SOF interrupt flag in INTF */
        CLR(SOFIF);

        /* if necessary, user can add code here */
        if (NULL != usbd_int_fops) {
            (void)usbd_int_fops->SOF(udev);
        }
    }

    if (INTF_ESOFIF & int_flag) {
        /* clear ESOF interrupt flag in INTF */
        CLR(ESOFIF);

        /* control resume time by ESOFs */
        if (udev->pm.esof_count > 0U) {
            if (0U == --udev->pm.esof_count) {
                if (udev->pm.remote_wakeup_on) {
                    USBD_CTL &= ~CTL_RSREQ;

                    udev->pm.remote_wakeup_on = 0U;
                } else {
                    USBD_CTL |= CTL_RSREQ;

                    udev->pm.esof_count = 3U;
                    udev->pm.remote_wakeup_on = 1U;
                }
            }
        }
    }

    if (INTF_RSTIF & int_flag) {
        /* clear reset interrupt flag in INTF */
        CLR(RSTIF);

        udev->drv_handler->ep_reset(udev);
    }

#ifdef LPM_ENABLED
    if (INTF_L1REQ & int_flag) {
        /* clear L1 ST bit in LPM INTF */
        USBD_INTF = CLR(L1REQ);

        /* read BESL field from subendpoint0 register which corresponds to HIRD parameter in LPM spec */
        udev->lpm.besl = (USBD_LPMCS & LPMCS_BLSTAT) >> 4;

        /* read BREMOTEWAKE bit from subendpoint0 register which corresponding to bRemoteWake bit in LPM request */
        udev->lpm.L1_remote_wakeup = (USBD_LPMCS & LPMCS_REMWK) >> 3;

        /* process USB device core layer suspend routine */
        usbd_int_suspend(udev);
    }
#endif /* LPM_ENABLED */
}

/*!
    \brief      handle USB suspend event
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
static void usbd_int_suspend (usb_dev *udev)
{
    /* store the device current status */
    udev->backup_status = udev->cur_status;

    /* set device in suspended state */
    udev->cur_status = (uint8_t)USBD_SUSPENDED;

    /* usb enter in suspend mode and mcu system in low power mode */
    if (udev->pm.suspend_enabled) {
        usbd_to_suspend(udev);
    } else {
        /* if not possible then resume after xx ms */
        udev->pm.esof_count = 3U;
    }
}
