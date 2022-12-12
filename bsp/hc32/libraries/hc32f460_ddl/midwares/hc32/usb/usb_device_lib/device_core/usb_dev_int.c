/**
 *******************************************************************************
 * @file  usb_dev_int.c
 * @brief Peripheral Device interrupt subroutines.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usb_dev_int.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_CORE
 * @{
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  read the endpoint flags
 * @param  [in] pdev        device instance
 * @param  [in] epnum       endpoint number
 * @retval status
 */
static uint32_t usb_rddevinep(usb_core_instance *pdev, uint8_t epnum)
{
    uint32_t u32diepmsk;
    uint32_t u32diepempmsk;
    u32diepmsk = READ_REG32(pdev->regs.DREGS->DIEPMSK);
    u32diepempmsk = READ_REG32(pdev->regs.DREGS->DIEPEMPMSK);
    u32diepmsk |= (((u32diepempmsk >> epnum) & 0x1UL) << 7U);
    return (READ_REG32(pdev->regs.INEP_REGS[epnum]->DIEPINT) & u32diepmsk);
}

/**
 * @brief  check FIFO for the next packet to be loaded
 * @param  [in] pdev        device instance
 * @param  [in] epnum       endpoint number
 * @retval None
 */
static void usb_wrblanktxfifo(usb_core_instance *pdev, uint32_t epnum)
{
    USB_DEV_EP *ep;
    uint32_t u32Len;
    uint32_t u32Len32b;
    uint16_t u16spclen;
    uint32_t u32diepempmsk;

    ep  = &pdev->dev.in_ep[epnum];
    u32Len = ep->xfer_len - ep->xfer_count;
    if (u32Len > ep->maxpacket) {
        u32Len = ep->maxpacket;
    }
    u32Len32b = (u32Len + 3UL) >> 2;
    u16spclen = usb_rdineptxfspcavail(pdev, epnum);
    while ((u16spclen >= u32Len32b) && (ep->xfer_count < ep->xfer_len)) {
        u32Len = ep->xfer_len - ep->xfer_count;

        if (u32Len > ep->maxpacket) {
            u32Len = ep->maxpacket;
        }
        u32Len32b = (u32Len + 3UL) >> 2;
        usb_wrpkt(&pdev->regs, ep->xfer_buff, (uint8_t)epnum, (uint16_t)u32Len, pdev->basic_cfgs.dmaen);
        ep->xfer_buff  += u32Len;
        ep->xfer_count += u32Len;
        u16spclen = usb_rdineptxfspcavail(pdev, epnum);
    }

    if (u32Len == 0UL) {
        u32diepempmsk = 0x01UL << epnum;
        CLR_REG32_BIT(pdev->regs.DREGS->DIEPEMPMSK, u32diepempmsk);
    }
}

#ifdef VBUS_SENSING_ENABLED
/**
 * @brief  Indicates that the USB_OTG controller has detected a connection
 * @param  [in] pdev        device instance
 * @retval None
 */
static void usb_sessionrequest_isr(usb_core_instance *pdev)
{
    dev_int_cbkpr->devctrlconnect(pdev, 1U);

    WRITE_REG32(pdev->regs.GREGS->GINTSTS, USBFS_GINTSTS_VBUSVINT);

    if (0U != pdev->basic_cfgs.low_power) {
        CLR_REG32_BIT(*pdev->regs.GCCTL, USBFS_GCCTL_STPPCLK | USBFS_GCCTL_GATEHCLK);
    }
}
#endif

/**
 * @brief  Indicates that the controller has detected a resume or remote Wake-up sequence
 * @param  [in] pdev        device instance
 * @retval None
 */
static void usb_resume_isr(usb_core_instance *pdev)
{
    if (0U != pdev->basic_cfgs.low_power) {
        CLR_REG32_BIT(*pdev->regs.GCCTL, USBFS_GCCTL_STPPCLK | USBFS_GCCTL_GATEHCLK);
    }

    CLR_REG32_BIT(pdev->regs.DREGS->DCTL, USBFS_DCTL_RWUSIG);

    dev_int_cbkpr->Resume(pdev);

    WRITE_REG32(pdev->regs.GREGS->GINTSTS, USBFS_GINTSTS_WKUINT);
}

/**
 * @brief  Indicates that SUSPEND state has been detected on the USB
 * @param  [in] pdev        device instance
 * @retval None
 */
static void usb_susp_isr(usb_core_instance *pdev)
{
    uint32_t u32dsts;
    uint8_t u8PrevStatus;

    dev_int_cbkpr->Suspend(pdev);
    u32dsts = READ_REG32(pdev->regs.DREGS->DSTS);
    WRITE_REG32(pdev->regs.GREGS->GINTSTS, USBFS_GINTSTS_USBSUSP);

    u8PrevStatus = pdev->dev.device_cur_status;
    if ((u8PrevStatus == USB_DEV_CONFIGURED) &&
            (0U != pdev->basic_cfgs.low_power) && ((u32dsts & 1UL) != 0UL)  &&
            (pdev->dev.connection_status == 1U)) {
        SET_REG32_BIT(*pdev->regs.GCCTL, USBFS_GCCTL_STPPCLK);
        SET_REG32_BIT(*pdev->regs.GCCTL, USBFS_GCCTL_GATEHCLK);
    }
}

/**
 * @brief  Indicates that at leadt one IN EP has a pending interrupt
 * @param  [in] pdev        device instance
 * @retval None
 */
static void usb_inep_isr(usb_core_instance *pdev)
{
    uint32_t u32diepint;
    uint32_t u32EpIntr;
    uint8_t u8epnum;
    uint32_t u32diepempmsk;

    u32EpIntr = usb_getalliepintr(&pdev->regs);
    u8epnum = 0U;
    while ((0U != u32EpIntr) && (u8epnum <= USB_MAX_TX_FIFOS)) {
        if ((u32EpIntr & 0x1UL) != 0UL) {
            u32diepint = usb_rddevinep(pdev, u8epnum);
            if ((u32diepint & XFER_COMPL) != 0UL) {
                u32diepempmsk = 1UL << u8epnum;
                CLR_REG32_BIT(pdev->regs.DREGS->DIEPEMPMSK, u32diepempmsk);
                WRITE_REG32(pdev->regs.INEP_REGS[u8epnum]->DIEPINT, XFER_COMPL);
                dev_int_cbkpr->DataInStage(pdev, u8epnum);
                if (pdev->basic_cfgs.dmaen == 1U) {
                    if ((u8epnum == 0U) && (pdev->dev.device_state == USB_EP0_STATUS_IN)) {
                        pdev->dev.out_ep[0].xfer_len = 64U;
                        pdev->dev.out_ep[0].rem_data_len = 64U;
                        pdev->dev.out_ep[0].total_data_len = 64U;
                        usb_ep0revcfg(&pdev->regs, pdev->basic_cfgs.dmaen, pdev->dev.setup_pkt_buf);
                        pdev->dev.device_state = USB_EP0_IDLE;
                    }
                }
            }
            if ((u32diepint & EPDISABLED) != 0UL) {
                WRITE_REG32(pdev->regs.INEP_REGS[u8epnum]->DIEPINT, EPDISABLED);
            }
            if ((u32diepint & TIME_OUT) != 0UL) {
                WRITE_REG32(pdev->regs.INEP_REGS[u8epnum]->DIEPINT, TIME_OUT);
            }
            if ((u32diepint & INTKNTXFEMP) != 0UL) {
                WRITE_REG32(pdev->regs.INEP_REGS[u8epnum]->DIEPINT, INTKNTXFEMP);
            }
            if ((u32diepint & INEPNAKEFF) != 0UL) {
                WRITE_REG32(pdev->regs.INEP_REGS[u8epnum]->DIEPINT, INEPNAKEFF);
            }
            if ((u32diepint & TXFEMP) != 0UL) {
                usb_wrblanktxfifo(pdev, u8epnum);
                WRITE_REG32(pdev->regs.INEP_REGS[u8epnum]->DIEPINT, TXFEMP);
            }
        }
        u8epnum++;
        u32EpIntr >>= 1U;
    }
}

/**
 * @brief  Indicates that an OUT EP has a pending Interrupt
 * @param  [in] pdev        device instance
 * @retval None
 */
static void usb_outep_isr(usb_core_instance *pdev)
{
    uint32_t u32EpIntr;
    uint32_t u32doepint;
    uint8_t u8epnum = 0U;
    uint32_t u8Xfer;
    uint32_t u32ReadEpSize;

    u32EpIntr = usb_getalloepintr(&pdev->regs);
    while ((u32EpIntr != 0UL) && (u8epnum <= USB_MAX_TX_FIFOS)) {
        if ((u32EpIntr & 0x1UL) != 0UL) {
            u32doepint = usb_getoepintbit(&pdev->regs, u8epnum);
            if ((u32doepint & XFER_COMPL) != 0UL) {
                WRITE_REG32(pdev->regs.OUTEP_REGS[u8epnum]->DOEPINT, XFER_COMPL);
                if (pdev->basic_cfgs.dmaen == 1U) {
                    u32ReadEpSize = (READ_REG32(pdev->regs.OUTEP_REGS[u8epnum]->DOEPTSIZ) & USBFS_DOEPTSIZ_XFRSIZ);
                    u8Xfer = LL_MIN(pdev->dev.out_ep[u8epnum].maxpacket, pdev->dev.out_ep[u8epnum].xfer_len);
                    pdev->dev.out_ep[u8epnum].xfer_count = u8Xfer - u32ReadEpSize;
                    if (u8epnum != 0U) {
                        pdev->dev.out_ep[u8epnum].xfer_count = pdev->dev.out_ep[u8epnum].xfer_len - u32ReadEpSize;
                    }
                }
                dev_int_cbkpr->DataOutStage(pdev, u8epnum);
                if (pdev->basic_cfgs.dmaen == 1U) {
                    if ((u8epnum == 0U) && (pdev->dev.device_state == USB_EP0_STATUS_OUT)) {
                        pdev->dev.out_ep[0].xfer_len       = 64U;
                        pdev->dev.out_ep[0].rem_data_len   = 64U;
                        pdev->dev.out_ep[0].total_data_len = 64U;
                        usb_ep0revcfg(&pdev->regs, pdev->basic_cfgs.dmaen, pdev->dev.setup_pkt_buf);
                        pdev->dev.device_state = USB_EP0_IDLE;
                    }
                }
            }
            if ((u32doepint & EPDISABLED) != 0UL) {
                WRITE_REG32(pdev->regs.OUTEP_REGS[u8epnum]->DOEPINT, EPDISABLED);
            }
            if (u8epnum == 0U) {
                u32doepint = usb_getoepintbit(&pdev->regs, u8epnum);
                if ((u32doepint & SETUP_BIT) != 0UL) {
                    dev_int_cbkpr->SetupStage(pdev);
                    WRITE_REG32(pdev->regs.OUTEP_REGS[u8epnum]->DOEPINT, SETUP_BIT);
                }
            }
        }
        u8epnum++;
        u32EpIntr >>= 1U;
    }
}

/**
 * @brief  Handles the SOF Interrupts
 * @param  [in] pdev        device instance
 * @retval None
 */
static void usb_sof_isr(usb_core_instance *pdev)
{
    dev_int_cbkpr->SOF(pdev);
    WRITE_REG32(pdev->regs.GREGS->GINTSTS, USBFS_GINTSTS_SOF);
}

/**
 * @brief  Handles the Rx Status Queue Level Interrupt
 * @param  [in] pdev        device instance
 * @retval status
 */
static void usb_rxstsqlvl_isr(usb_core_instance *pdev)
{
    uint32_t u32grxsts;
    USB_DEV_EP *ep;
    uint8_t u8epnum;
    uint8_t u8PktStatus;
    uint16_t u16ByteCnt;

    CLR_REG32_BIT(pdev->regs.GREGS->GINTMSK, USBFS_GINTMSK_RXFNEM);

    u32grxsts  = READ_REG32(pdev->regs.GREGS->GRXSTSP);
    u8epnum = (uint8_t)(u32grxsts & USBFS_GRXSTSP_CHNUM_EPNUM);
    u8PktStatus = (uint8_t)((u32grxsts & USBFS_GRXSTSP_PKTSTS) >> USBFS_GRXSTSP_PKTSTS_POS);
    u16ByteCnt = (uint16_t)((u32grxsts & USBFS_GRXSTSP_BCNT) >> USBFS_GRXSTSP_BCNT_POS);
    ep = &pdev->dev.out_ep[u8epnum];
    switch (u8PktStatus) {
        case STS_DATA_UPDT:
            if (0U != u16ByteCnt) {
                usb_rdpkt(&pdev->regs, ep->xfer_buff, u16ByteCnt);
                ep->xfer_buff += u16ByteCnt;
                ep->xfer_count += u16ByteCnt;
            } else {
                ;
            }
            break;
        case STS_SETUP_UPDT:
            /* Copy the setup packet received in FIFO into the setup buffer in RAM */
            usb_rdpkt(&pdev->regs, pdev->dev.setup_pkt_buf, 8U);
            ep->xfer_count += u16ByteCnt;
            break;
        case STS_GOUT_NAK:
        case STS_XFER_COMP:
        case STS_SETUP_COMP:
            break;
        default:
            break;
    }
    SET_REG32_BIT(pdev->regs.GREGS->GINTMSK, USBFS_GINTMSK_RXFNEM);
}

/**
 * @brief  This interrupt occurs when a USB Reset is detected
 * @param  [in] pdev        device instance
 * @retval None
 */
static void usb_reset_isr(usb_core_instance *pdev)
{
    uint32_t i;

    CLR_REG32_BIT(pdev->regs.DREGS->DCTL, USBFS_DCTL_RWUSIG);
    usb_txfifoflush(&pdev->regs, 0UL);
    for (i = 0UL; i < pdev->basic_cfgs.dev_epnum ; i++) {
        WRITE_REG32(pdev->regs.INEP_REGS[i]->DIEPINT, 0xFFUL);
        WRITE_REG32(pdev->regs.OUTEP_REGS[i]->DOEPINT, 0xFFUL);
    }
    WRITE_REG32(pdev->regs.DREGS->DAINT, 0xFFFFFFFFUL);
    WRITE_REG32(pdev->regs.DREGS->DAINTMSK, 1UL | (1UL << USBFS_DAINTMSK_OEPINTM_POS));
    //todo: bit5 if need be set?
    WRITE_REG32(pdev->regs.DREGS->DOEPMSK, USBFS_DOEPMSK_STUPM | USBFS_DOEPMSK_XFRCM | USBFS_DOEPMSK_EPDM);
#ifdef USB_OTG_HS_DEDICATED_EP1_ENABLED
    WRITE_REG32(pdev->regs.DREGS->DOUTEP1MSK, USBFS_DOEPMSK_STUPM | USBFS_DOEPMSK_XFRCM | USBFS_DOEPMSK_EPDM);
#endif

    WRITE_REG32(pdev->regs.DREGS->DIEPMSK, USBFS_DIEPMSK_XFRCM | USBFS_DIEPMSK_TOM | USBFS_DIEPMSK_EPDM);
#ifdef USB_OTG_HS_DEDICATED_EP1_ENABLED
    WRITE_REG32(pdev->regs.DREGS->DINEP1MSK, USBFS_DIEPMSK_XFRCM | USBFS_DIEPMSK_TOM | USBFS_DIEPMSK_EPDM);
#endif

    CLR_REG32_BIT(pdev->regs.DREGS->DCFG, USBFS_DCFG_DAD);
    pdev->dev.out_ep[0].xfer_len       = 64U;
    pdev->dev.out_ep[0].rem_data_len   = 64U;
    pdev->dev.out_ep[0].total_data_len = 64U;
    usb_ep0revcfg(&pdev->regs, pdev->basic_cfgs.dmaen, pdev->dev.setup_pkt_buf);
    WRITE_REG32(pdev->regs.GREGS->GINTSTS, USBFS_GINTSTS_USBRST);

    dev_int_cbkpr->Reset(pdev);
}

/**
 * @brief  Read the device status register and set the device speed
 * @param  [in] pdev        device instance
 * @retval None
 */
static void usb_enumfinish_isr(usb_core_instance *pdev)
{
    usb_ep0activate(&pdev->regs);
    usb_setaroundtim(pdev);
    WRITE_REG32(pdev->regs.GREGS->GINTSTS, USBFS_GINTSTS_ENUMDNE);
}

/**
 * @brief  handle the ISO IN incomplete interrupt
 * @param  [in] pdev        device instance
 * @retval None
 */
static void usb_isoinincomplt_isr(usb_core_instance *pdev)
{
    dev_int_cbkpr->IsoINIncomplete(pdev);
    WRITE_REG32(pdev->regs.GREGS->GINTSTS, USBFS_GINTSTS_IISOIXFR);
}

/**
 * @brief  handle the ISO OUT incomplete interrupt
 * @param  [in] pdev        device instance
 * @retval None
 */
static void usb_isooutincomplt_isr(usb_core_instance *pdev)
{
    dev_int_cbkpr->IsoOUTIncomplete(pdev);
    WRITE_REG32(pdev->regs.GREGS->GINTSTS, USBFS_GINTSTS_IPXFR_INCOMPISOOUT);
}

/**
 * @brief  handles all USB Interrupts
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_isr_handler(usb_core_instance *pdev)
{
    uint32_t u32gintsts;

    if (0U == usb_getcurmod(&pdev->regs)) {
        u32gintsts = usb_getcoreintr(&pdev->regs);
        if (u32gintsts == 0UL) {
            return;
        }
        if ((u32gintsts & OUTEP_INT) != 0UL) {
            usb_outep_isr(pdev);
        }
        if ((u32gintsts & INEP_INT) != 0UL) {
            usb_inep_isr(pdev);
        }
        if ((u32gintsts & MODEMIS_INT) != 0UL) {
            WRITE_REG32(pdev->regs.GREGS->GINTSTS, MODEMIS_INT);
        }
        if ((u32gintsts & WAKEUP_INT) != 0UL) {
            usb_resume_isr(pdev);
        }
        if ((u32gintsts & USBSUSP_INT) != 0UL) {
            usb_susp_isr(pdev);
        }
        if ((u32gintsts & SOF_INT) != 0UL) {
            usb_sof_isr(pdev);
        }
        if ((u32gintsts & RXFLVL_INT) != 0UL) {
            usb_rxstsqlvl_isr(pdev);
        }
        if ((u32gintsts & USBRST_INT) != 0UL) {
            usb_reset_isr(pdev);
        }
        if ((u32gintsts & ENUMDONE_INT) != 0UL) {
            usb_enumfinish_isr(pdev);
        }
        if ((u32gintsts & INCOMPLSOIN) != 0UL) {
            usb_isoinincomplt_isr(pdev);
        }
        if ((u32gintsts & INCOMPLSOOUT) != 0UL) {
            usb_isooutincomplt_isr(pdev);
        }
#ifdef VBUS_SENSING_ENABLED
        if ((u32gintsts & VBUSV_INT) != 0UL) {
            usb_sessionrequest_isr(pdev);
        }
#endif
    }
}

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
