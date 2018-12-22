/*!
    \file  usbh_int.c
    \brief USB host mode interrupt handler file
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.1, firmware for GD32F4xx
*/

#include "usb_core.h"
#include "usb_defines.h"
#include "usbh_int.h"

static uint32_t usbh_intf_sof                 (usb_core_handle_struct *pudev);
static uint32_t usbh_intf_port                (usb_core_handle_struct *pudev);
static uint32_t usbh_intf_hc                  (usb_core_handle_struct *pudev);
static uint32_t usbh_intf_hc_in               (usb_core_handle_struct *pudev, uint8_t channel_num);
static uint32_t usbh_intf_hc_out              (usb_core_handle_struct *pudev, uint8_t channel_num);
static uint32_t usbh_intf_rxfifo_noempty      (usb_core_handle_struct *pudev);
static uint32_t usbh_intf_nptxfifo_empty      (usb_core_handle_struct *pudev);
static uint32_t usbh_intf_ptxfifo_empty       (usb_core_handle_struct *pudev);
static uint32_t usbh_intf_disconnect          (usb_core_handle_struct *pudev);
static uint32_t usbh_intf_iso_incomplete_xfer (usb_core_handle_struct *pudev);

/*!
    \brief      handle global host interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
uint32_t usbh_isr (usb_core_handle_struct *pudev)
{
    uint32_t retval = 0U;
    uint32_t int_flag = 0U;

    /* check if host mode */
    if (USB_CURRENT_MODE_GET() == HOST_MODE) {
        USB_CORE_INTR_READ(int_flag);

        if (!int_flag) {
            return 0U;
        }
        
        /* start of frame interrupt handle */
        if (int_flag & GINTF_SOF) {
            retval |= usbh_intf_sof (pudev);
        }

        /* Rx FIFO non-empty interrupt handle */
        if (int_flag & GINTF_RXFNEIF) {
            retval |= usbh_intf_rxfifo_noempty (pudev);
        }

        /* Non-Periodic Tx FIFO empty interrupt hanlde */
        if (int_flag & GINTF_NPTXFEIF) {
            retval |= usbh_intf_nptxfifo_empty (pudev);
        }

        /* periodic Tx FIFO empty interrupt handle */
        if (int_flag & GINTF_PTXFEIF) {
            retval |= usbh_intf_ptxfifo_empty (pudev);
        }

        /* host channels interrupt handle */
        if (int_flag & GINTF_HCIF) {
            retval |= usbh_intf_hc (pudev);
        }

        /* host port interrupt handle */
        if (int_flag & GINTF_HPIF) {
            retval |= usbh_intf_port (pudev);
        }

        /* disconnect interrupt handle */
        if (int_flag & GINTF_DISCIF) {
            retval |= usbh_intf_disconnect (pudev);
        }

        /* isochronous IN transfer not complete interrupt handle */
        if (int_flag & GINTF_ISOONCIF) {
            retval |= usbh_intf_iso_incomplete_xfer (pudev);
        }
    }

    return retval;
}

/*!
    \brief      handle the start-of-frame interrupt in host mode
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbh_intf_sof (usb_core_handle_struct *pudev)
{
    usbh_hcd_int_fops->sof(pudev);

    /* clear interrupt */
    USB_GINTF = GINTF_SOF;

    return 1U;
}

/*!
    \brief      handle all host channels interrupt in host mode
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbh_intf_hc (usb_core_handle_struct *pudev)
{
    uint8_t i = 0U;
    uint32_t retval = 0U;

    for (i = 0U; i < pudev->cfg.host_channel_num; i++) {
        if ((USB_HACHINT & HACHINT_HACHINT) & ((uint32_t)1U << i)) {
            if ((USB_HCHxCTL((uint16_t)i) & HCHCTL_EPDIR) >> 15U) {
                retval |= usbh_intf_hc_in (pudev, i);
            } else {
                retval |= usbh_intf_hc_out (pudev, i);
            }
        }
    }

    return retval;
}

/*!
    \brief      handle the disconnect interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbh_intf_disconnect (usb_core_handle_struct *pudev)
{
    usbh_hcd_int_fops->device_disconnected(pudev);

    /* clear interrupt */
    USB_GINTF = GINTF_DISCIF;

    return 1U;
}

/*!
    \brief      handle the non-periodic tx fifo empty interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbh_intf_nptxfifo_empty (usb_core_handle_struct *pudev)
{
    uint8_t channel_num = 0U;
    uint32_t dword_len = 0U, len = 0U;
    usb_hostchannel_struct *puhc;

    channel_num = (uint8_t)((USB_HNPTFQSTAT & HNPTFQSTAT_CNUM) >> 27U);
    puhc = &pudev->host.host_channel[channel_num];
    dword_len = (puhc->xfer_len + 3U) / 4U;

    while (((USB_HNPTFQSTAT & HNPTFQSTAT_NPTXFS) > dword_len) && (0U != puhc->xfer_len)) {
        len = (USB_HNPTFQSTAT & HNPTFQSTAT_NPTXFS) * 4U;

        if (len > puhc->xfer_len) {
            /* last packet */
            len = (uint16_t)puhc->xfer_len;

            USB_GINTEN &= ~GINTF_NPTXFEIF;

        }

        dword_len = (puhc->xfer_len + 3U) / 4U;
        usb_fifo_write (puhc->xfer_buff, channel_num, (uint16_t)len);

        puhc->xfer_buff += len;
        puhc->xfer_len -= len;
        puhc->xfer_count += len;
    }

    return 1U;
}

/*!
    \brief      handle the periodic tx fifo empty interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbh_intf_ptxfifo_empty (usb_core_handle_struct *pudev)
{
    uint8_t channel_num = 0U;
    uint32_t dword_len = 0U, len = 0U;
    usb_hostchannel_struct *puhc; 

    channel_num = (uint8_t)((USB_HPTFQSTAT & HPTFQSTAT_CNUM) >> 27U);
    puhc = &pudev->host.host_channel[channel_num];
    dword_len = (puhc->xfer_len + 3U) / 4U;

    while (((USB_HPTFQSTAT & HPTFQSTAT_PTXFS) > dword_len) && (0U != puhc->xfer_len)) {
        len = (USB_HPTFQSTAT & HPTFQSTAT_PTXFS) * 4U;

        if (len > puhc->xfer_len) {
            len = puhc->xfer_len;

            /* last packet */
            USB_GINTEN &= ~GINTF_PTXFEIF;
        }

        dword_len = (puhc->xfer_len + 3U) / 4U;
        usb_fifo_write (puhc->xfer_buff, channel_num, (uint16_t)len);

        puhc->xfer_buff += len;
        puhc->xfer_len -= len;
        puhc->xfer_count += len;
    }

    return 1U;
}

/*!
    \brief      handle the host port interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbh_intf_port (usb_core_handle_struct *pudev)
{
    uint8_t port_speed = 0U;
    uint8_t port_reset = 0U;
    uint32_t retval = 0U;
    __IO uint32_t hostportdup = USB_HPCS;

    /* clear the interrupt bits in gintsts */
    hostportdup &= ~HPCS_PE;
    hostportdup &= ~HPCS_PCD;
    hostportdup &= ~HPCS_PEDC;

    /* port connect detected */
    if (USB_HPCS & HPCS_PCD) {
        hostportdup |= HPCS_PCD;
        usbh_hcd_int_fops->device_connected(pudev);
        retval |= 1U;
    }

    /* port enable changed */
    if (USB_HPCS & HPCS_PEDC) {
        hostportdup |= HPCS_PEDC;

        if (USB_HPCS & HPCS_PE) {
            port_speed = (uint8_t)((USB_HPCS & HPCS_PS) >> 17U);

            if (HPRT_PRTSPD_LOW_SPEED == port_speed) {
                USB_HFT = 6000U;

                if (HCTLR_6_MHZ != (USB_HCTL & HCTL_CLKSEL)) {
                    if (USB_CORE_EMBEDDED_PHY == pudev->cfg.phy_interface) {
                        USB_FSLSCLOCK_INIT(HCTLR_6_MHZ);
                    }
                    port_reset = 1U;
                }
            } else if(HPRT_PRTSPD_FULL_SPEED == port_speed) {
                USB_HFT = 48000U;

                if (HCTLR_48_MHZ != (USB_HCTL & HCTL_CLKSEL)) {
                    if (USB_CORE_EMBEDDED_PHY == pudev->cfg.phy_interface) {
                        USB_FSLSCLOCK_INIT(HCTLR_48_MHZ);
                    }
                    port_reset = 1U;
                }
            } else {
                /* for high speed device and others */
                port_reset = 1U;
            }


        }
    }

    if (port_reset) {
        usb_port_reset(pudev);
    }

    /* clear port interrupts */
    USB_HPCS = hostportdup;

    return retval;
}

/*!
    \brief      handle the OUT channel interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[in]  channel_num: host channel number which is in (0..7)
    \param[out] none
    \retval     operation status
*/
static uint32_t usbh_intf_hc_out (usb_core_handle_struct *pudev, uint8_t channel_num)
{
    uint32_t channel_intr = USB_HCHxINTF((uint16_t)channel_num);
    usb_hostchannel_struct *puhc = &pudev->host.host_channel[channel_num];

    channel_intr &= USB_HCHxINTEN((uint16_t)channel_num);

    if (channel_intr & HCHINTF_ACK) {
        if (URB_PING ==  puhc->urb_state) {
            puhc->err_count = 0U;
            USB_HCHxINTEN((uint16_t)channel_num) |= HCHINTEN_CHIE;
            usb_hostchannel_halt(pudev, channel_num);
            USB_HCHxINTF((uint16_t)channel_num) = HCHINTF_TF;
            puhc->status = HC_XF;
        }

        USB_HCHxINTF((uint16_t)channel_num) = HCHINTF_ACK;
    } else if (channel_intr & HCHINTF_REQOVR) {
        USB_HCHxINTEN((uint16_t)channel_num) |= HCHINTEN_CHIE;
        usb_hostchannel_halt(pudev, channel_num);
        USB_HCHxINTF((uint16_t)channel_num) = HCHINTF_REQOVR;
    } else if (channel_intr & HCHINTF_TF) {
        puhc->err_count = 0U;
        USB_HCHxINTEN((uint16_t)channel_num) |= HCHINTEN_CHIE;
        usb_hostchannel_halt(pudev, channel_num);
        USB_HCHxINTF((uint16_t)channel_num) = HCHINTF_TF;
        puhc->status = HC_XF;
    } else if (channel_intr & HCHINTF_STALL) {
        USB_HCHxINTEN((uint16_t)channel_num) |= HCHINTEN_CHIE;
        USB_HCHxINTF((uint16_t)channel_num) = HCHINTF_STALL;
        usb_hostchannel_halt(pudev, channel_num);
        puhc->status = HC_STALL;
    } else if (channel_intr & HCHINTF_NAK) {
        puhc->err_count = 0U;
        USB_HCHxINTEN((uint16_t)channel_num) |= HCHINTEN_CHIE;
        usb_hostchannel_halt(pudev, channel_num);
        USB_HCHxINTF((uint16_t)channel_num) = HCHINTF_NAK;
        puhc->status = HC_NAK;
    } else if (channel_intr & HCHINTF_USBER) {
        USB_HCHxINTEN((uint16_t)channel_num) |= HCHINTEN_CHIE;
        usb_hostchannel_halt(pudev, channel_num);
        puhc->err_count ++;
        puhc->status = HC_TRACERR;
        USB_HCHxINTF((uint16_t)channel_num) = HCHINTF_USBER;
    } else if (channel_intr & HCHINTF_NYET) {
        puhc->err_count = 0U;
        USB_HCHxINTEN((uint16_t)channel_num) |= HCHINTEN_CHIE;
        puhc->status = HC_NYET;
        USB_HCHxINTF((uint16_t)channel_num) = HCHINTF_NYET;
    } else if (channel_intr & HCHINTF_DTER) {
        USB_HCHxINTEN((uint16_t)channel_num) |= HCHINTEN_CHIE;
        usb_hostchannel_halt(pudev, channel_num);
        puhc->status= HC_DTGERR;
        USB_HCHxINTF((uint16_t)channel_num) = HCHINTF_DTER;
    } else if (channel_intr & HCHINTF_CH) {
        USB_HCHxINTEN((uint16_t)channel_num) &= ~HCHINTEN_CHIE;

        switch (puhc->status) {
            case HC_XF:
                puhc->urb_state = URB_DONE;

                if (USB_EPTYPE_BULK == ((USB_HCHxCTL((uint16_t)channel_num) & HCHCTL_EPTYPE) >> 18)) {
                    puhc->data_tg_out ^= 1U; 
                }
                break;
            case HC_NAK:
                if (URB_PING == puhc->urb_state) {
                    usb_hostchannel_ping(pudev, channel_num);
                } else {
                    puhc->urb_state = URB_NOTREADY;
                }
                break;
            case HC_NYET:
                if (1U == puhc->do_ping) {
                    usb_hostchannel_ping(pudev, channel_num);
                    puhc->urb_state = URB_PING;
                }
                break;
            case HC_STALL:
                puhc->urb_state = URB_STALL;
                break;
            case HC_TRACERR:
                if (3U == puhc->err_count) {
                    puhc->urb_state = URB_ERROR;
                    puhc->err_count = 0U;
                }
                break;
            default:
                break;
        }

        USB_HCHxINTF((uint16_t)channel_num) = HCHINTF_CH;
    } else {
        /* no operation */
    }

    return 1U;
}

/*!
    \brief      handle the IN channel interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[in]  channel_num: host channel number which is in (0..7)
    \param[out] none
    \retval     operation status
*/
static uint32_t usbh_intf_hc_in (usb_core_handle_struct *pudev, uint8_t channel_num)
{
    uint8_t endp_type = 0U;
    usb_hostchannel_struct *puhc = &pudev->host.host_channel[channel_num];

    uint32_t channle_intf = USB_HCHxINTF((uint16_t)channel_num);
    __IO uint32_t channel_ctrl = USB_HCHxCTL((uint16_t)channel_num);

    channle_intf &= USB_HCHxINTEN((uint16_t)channel_num);

    endp_type = (uint8_t)((channel_ctrl & HCHCTL_EPTYPE) >> 18U);

    if (channle_intf & HCHINTF_ACK) {
        USB_HCHxINTF((uint16_t)channel_num) = HCHINTF_ACK;
    } else if (channle_intf & HCHINTF_STALL) {
        USB_HCHxINTEN((uint16_t)channel_num) |= HCHINTEN_CHIE;
        puhc->status = HC_STALL;
        USB_HCHxINTF((uint16_t)channel_num) = HCHINTF_NAK;
        USB_HCHxINTF((uint16_t)channel_num) = HCHINTF_STALL;

        /* NOTE: When there is a 'stall', reset also nak,
           else, the pudev->host.status = HC_STALL
           will be overwritten by 'nak' in code below */
        channle_intf &= ~HCHINTF_NAK;

        usb_hostchannel_halt(pudev, channel_num);
    } else if (channle_intf & HCHINTF_DTER) {
        USB_HCHxINTEN((uint16_t)channel_num) |= HCHINTEN_CHIE;
        usb_hostchannel_halt(pudev, channel_num);
        USB_HCHxINTF((uint16_t)channel_num) = HCHINTF_NAK;
        puhc->status = HC_DTGERR; 
        USB_HCHxINTF((uint16_t)channel_num) = HCHINTF_DTER;
    } else {
        /* no operation */
    }

    if (channle_intf & HCHINTF_REQOVR) {
        USB_HCHxINTEN((uint16_t)channel_num) |= HCHINTEN_CHIE;
        usb_hostchannel_halt(pudev, channel_num);
        USB_HCHxINTF((uint16_t)channel_num) = HCHINTF_REQOVR;
    } else if (channle_intf & HCHINTF_TF) {
        if (pudev->cfg.dma_enable == 1U) {
            uint32_t xfer_size = USB_HCHxLEN((uint16_t)channel_num) & HCHLEN_TLEN;
            puhc->xfer_count = puhc->xfer_len - xfer_size;
        }

        puhc->status = HC_XF;
        puhc->err_count = 0U;
        USB_HCHxINTF((uint16_t)channel_num) = HCHINTF_TF;

        if ((USB_EPTYPE_CTRL == endp_type) || (USB_EPTYPE_BULK == endp_type)) {
            USB_HCHxINTEN((uint16_t)channel_num) |= HCHINTEN_CHIE;
            usb_hostchannel_halt(pudev, channel_num);
            USB_HCHxINTF((uint16_t)channel_num) = HCHINTF_NAK;
            puhc->data_tg_in ^= 1U;
        } else if (USB_EPTYPE_INTR == endp_type) {
            channel_ctrl |= HCHCTL_ODDFRM;
            USB_HCHxCTL((uint16_t)channel_num) = channel_ctrl;
            puhc->urb_state = URB_DONE;
        } else {
            /* no operation */
        }
    } else if (channle_intf & HCHINTF_CH) {
        USB_HCHxINTEN((uint16_t)channel_num) &= ~HCHINTEN_CHIE;

        switch (puhc->status) {
            case HC_XF:
                puhc->urb_state = URB_DONE;
                break;
            case HC_TRACERR:
            case HC_DTGERR:
                puhc->err_count = 0U;
                puhc->urb_state = URB_ERROR;
                break;
            case HC_STALL:
                puhc->urb_state = URB_STALL;
                break;
            default:
                if (USB_EPTYPE_INTR == endp_type) {
                    puhc->data_tg_in ^= 1U;
                }
                break;
        }

        USB_HCHxINTF((uint16_t)channel_num) = HCHINTF_CH;
    } else if (channle_intf & HCHINTF_USBER) {
        USB_HCHxINTEN((uint16_t)channel_num) |= HCHINTEN_CHIE;
        (puhc->err_count)++;
        puhc->status = HC_TRACERR;
        usb_hostchannel_halt(pudev, channel_num);
        USB_HCHxINTF((uint16_t)channel_num) = HCHINTF_USBER;
    } else if (channle_intf & HCHINTF_NAK) {
        if (USB_EPTYPE_INTR == endp_type) {
            USB_HCHxINTEN((uint16_t)channel_num) |= HCHINTEN_CHIE;
            usb_hostchannel_halt(pudev, channel_num);
        } else if ((USB_EPTYPE_CTRL == endp_type) || (USB_EPTYPE_BULK == endp_type)) {
            /* re-activate the channel */
            channel_ctrl |= HCHCTL_CEN;
            channel_ctrl &= ~HCHCTL_CDIS;
            USB_HCHxCTL((uint16_t)channel_num) = channel_ctrl;
        } else {
            /* no operation */
        }

        puhc->status = HC_NAK;
        USB_HCHxINTF((uint16_t)channel_num) = HCHINTF_NAK;
    } else {
        /* no operation */
    }

    return 1U;
}

/*!
    \brief      handle the rx fifo non-empty interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbh_intf_rxfifo_noempty (usb_core_handle_struct *pudev)
{
    uint32_t count = 0U;
    __IO uint8_t channel_num = 0U;
    __IO uint32_t rx_status = 0U;
    uint32_t usbh_ch_ctl_reg = 0U;
    usb_hostchannel_struct *puhc;

    /* disable the Rx status queue level interrupt */
    USB_GINTEN &= ~GINTF_RXFNEIF;

    rx_status = USB_GRSTATP;
    channel_num = (uint8_t)(rx_status & GRSTATR_CNUM);
    puhc = &pudev->host.host_channel[channel_num];

    switch ((rx_status & GRSTATR_RPCKST) >> 17) {
        case GRSTATR_RPCKST_IN:
            count = (rx_status & GRSTATR_BCOUNT) >> 4;

            /* read the data into the host buffer. */
            if ((count > 0U) && (puhc->xfer_buff != (void *)0)) {
                usb_fifo_read(puhc->xfer_buff, (uint16_t)count);

                /* manage multiple Xfer */
                puhc->xfer_buff += count;
                puhc->xfer_count += count;

                if (USB_HCHxLEN((uint16_t)channel_num) & HCHLEN_PCNT) {
                    /* re-activate the channel when more packets are expected */
                    usbh_ch_ctl_reg = USB_HCHxCTL((uint16_t)channel_num);
                    usbh_ch_ctl_reg |= HCHCTL_CEN;
                    usbh_ch_ctl_reg &= ~HCHCTL_CDIS;
                    USB_HCHxCTL((uint16_t)channel_num) = usbh_ch_ctl_reg;
                }
            }
            break;
        case GRSTATR_RPCKST_IN_XFER_COMP:
        case GRSTATR_RPCKST_DATA_TOGGLE_ERR:
        case GRSTATR_RPCKST_CH_HALTED:
        default:
            break;
    }

    /* enable the Rx status queue level interrupt */
    USB_GINTEN |= GINTF_RXFNEIF;

    return 1U;
}

/*!
    \brief      handle the incomplete periodic transfer interrupt
    \param[in]  pudev: pointer to usb device instance
    \param[out] none
    \retval     operation status
*/
static uint32_t usbh_intf_iso_incomplete_xfer (usb_core_handle_struct *pudev)
{
    __IO uint32_t gint_flag = 0U;

    gint_flag = USB_HCHxCTL(0U);
    USB_HCHxCTL(0U) = 0U;

    gint_flag = 0U;

    /* clear interrupt */
    gint_flag |= GINTF_ISOONCIF;
    USB_GINTF = gint_flag;

    return 1U;
}
