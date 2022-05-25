/**
 *******************************************************************************
 * @file  usb_host_int.c
 * @brief Host driver interrupt subroutines.
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
#include "usb_host_int.h"
#include "usb_host_driver.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_CORE
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
void usb_host_hc_isr(usb_core_instance *pdev);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  processes interrupt for a specific host channel which is used for OUT EP
 * @param  [in] pdev        device instance
 * @param  [in] chnum       channel index
 * @retval None
 */
static void usb_host_chx_out_isr(usb_core_instance *pdev, uint8_t chnum)
{
    uint32_t u32hcchar;
    uint32_t u32hcint;
    uint32_t u32hcintmsk;

    u32hcchar = READ_REG32(pdev->regs.HC_REGS[chnum]->HCCHAR);
    u32hcint = READ_REG32(pdev->regs.HC_REGS[chnum]->HCINT);
    u32hcintmsk = READ_REG32(pdev->regs.HC_REGS[chnum]->HCINTMSK);
    u32hcint = u32hcint & u32hcintmsk;

    if (0UL != (u32hcint & USBFS_HCINT_ACK)) {
        usb_host_clrint(pdev, chnum, USBFS_HCINT_ACK);
    }
#if defined (HC32F4A0)
    else if (0UL != (u32hcint & USBFS_HCINT_AHBERR)) {
        usb_host_clrint(pdev, chnum, USBFS_HCINT_AHBERR);
        usb_host_int_unmskchhltd(pdev, chnum);
    }
#endif
    else if (0UL != (u32hcint & USBFS_HCINT_FRMOR)) {
        usb_host_int_unmskchhltd(pdev, chnum);
        usb_hchstop(&pdev->regs, chnum);
        usb_host_clrint(pdev, chnum, USBFS_HCINT_FRMOR);
    } else if (0UL != (u32hcint & USBFS_HCINT_XFRC)) {
        pdev->host.ErrCnt[chnum] = 0U;
        usb_host_int_unmskchhltd(pdev, chnum);
        usb_hchstop(&pdev->regs, chnum);
        usb_host_clrint(pdev, chnum, USBFS_HCINT_XFRC);
        pdev->host.HC_Status[chnum] = HOST_CH_XFERCOMPL;
    } else if (0UL != (u32hcint & USBFS_HCINT_STALL)) {
        usb_host_clrint(pdev, chnum, USBFS_HCINT_STALL);
        usb_host_int_unmskchhltd(pdev, chnum);
        usb_hchstop(&pdev->regs, chnum);
        pdev->host.HC_Status[chnum] = HOST_CH_STALL;
    } else if (0UL != (u32hcint & USBFS_HCINT_NAK)) {
        pdev->host.ErrCnt[chnum] = 0U;
        usb_host_int_unmskchhltd(pdev, chnum);
        usb_hchstop(&pdev->regs, chnum);
        usb_host_clrint(pdev, chnum, USBFS_HCINT_NAK);
        pdev->host.HC_Status[chnum] = HOST_CH_NAK;
    } else if (0UL != (u32hcint & USBFS_HCINT_TXERR)) {
        usb_host_int_unmskchhltd(pdev, chnum);
        usb_hchstop(&pdev->regs, chnum);
        pdev->host.ErrCnt[chnum] ++;
        pdev->host.HC_Status[chnum] = HOST_CH_XACTERR;
        usb_host_clrint(pdev, chnum, USBFS_HCINT_TXERR);
    } else if (0UL != (u32hcint & HCINT_NYET)) {
        pdev->host.ErrCnt[chnum] = 0U;
        usb_host_int_unmskchhltd(pdev, chnum);
        usb_hchstop(&pdev->regs, chnum);
        usb_host_clrint(pdev, chnum, HCINT_NYET);
        pdev->host.HC_Status[chnum] = HOST_CH_NYET;
    } else if (0UL != (u32hcint & USBFS_HCINT_DTERR)) {
        usb_host_int_unmskchhltd(pdev, chnum);
        usb_hchstop(&pdev->regs, chnum);
        usb_host_clrint(pdev, chnum, USBFS_HCINT_NAK);
        pdev->host.HC_Status[chnum] = HOST_CH_DATATGLERR;
        usb_host_clrint(pdev, chnum, USBFS_HCINT_DTERR);
    } else if (0UL != (u32hcint & USBFS_HCINT_CHH)) {
        usb_host_int_mskchhltd(pdev, chnum);
        if (pdev->host.HC_Status[chnum] == HOST_CH_XFERCOMPL) {
            pdev->host.URB_State[chnum] = HOST_CH_XFER_DONE;

            if (((u32hcchar & USBFS_HCCHAR_EPTYP) >> USBFS_HCCHAR_EPTYP_POS) == EP_TYPE_BULK) {
                pdev->host.hc[chnum].out_toggle ^= 1U;
            }
        } else if (pdev->host.HC_Status[chnum] == HOST_CH_NAK) {
            pdev->host.URB_State[chnum] = HOST_CH_XFER_UNREADY;
        } else if (pdev->host.HC_Status[chnum] == HOST_CH_NYET) {
            if (pdev->host.hc[chnum].do_ping == 1U) {
                usb_pingtokenissue(&pdev->regs, chnum);
            }
            pdev->host.URB_State[chnum] = HOST_CH_XFER_UNREADY;
        } else if (pdev->host.HC_Status[chnum] == HOST_CH_STALL) {
            pdev->host.URB_State[chnum] = HOST_CH_XFER_STALL;
        } else if (pdev->host.HC_Status[chnum] == HOST_CH_XACTERR) {
            if (pdev->host.ErrCnt[chnum] == 3UL) {
                pdev->host.URB_State[chnum] = HOST_CH_XFER_ERROR;
                pdev->host.ErrCnt[chnum] = 0UL;
            }
        } else {
            ;
        }
        usb_host_clrint(pdev, chnum, USBFS_HCINT_CHH);
    } else {
        ;
    }
}

/**
 * @brief  processes interrupt for a specific host Channel which is used for IN EP
 * @param  [in] pdev        device instance
 * @param  [in] chnum       channel index
 * @retval None
 */
static void usb_host_chx_in_isr(usb_core_instance *pdev, uint8_t chnum)
{
    uint32_t u32hcchar;
    uint32_t u32hctsiz;
    uint32_t u32eptypetmp;
    uint32_t u32hcint;
    uint32_t u32hcintmsk;

    u32hcchar = READ_REG32(pdev->regs.HC_REGS[chnum]->HCCHAR);
    u32hcint = READ_REG32(pdev->regs.HC_REGS[chnum]->HCINT);
    u32hcintmsk = READ_REG32(pdev->regs.HC_REGS[chnum]->HCINTMSK);
    u32hcint = u32hcint & u32hcintmsk;

    u32eptypetmp = (u32hcchar & USBFS_HCCHAR_EPTYP) >> USBFS_HCCHAR_EPTYP_POS;
    if (0UL != (u32hcint & USBFS_HCINT_ACK)) {
        usb_host_clrint(pdev, chnum, USBFS_HCINT_ACK);
    }
#if defined (HC32F4A0)
    else if (0UL != (u32hcint & USBFS_HCINT_AHBERR)) {
        usb_host_clrint(pdev, chnum, USBFS_HCINT_AHBERR);
        usb_host_int_unmskchhltd(pdev, chnum);
    }
#endif
    else if (0UL != (u32hcint & USBFS_HCINT_STALL)) {
        usb_host_int_unmskchhltd(pdev, chnum);
        pdev->host.HC_Status[chnum] = HOST_CH_STALL;
        usb_host_clrint(pdev, chnum, USBFS_HCINT_NAK);
        usb_host_clrint(pdev, chnum, USBFS_HCINT_STALL);
        usb_hchstop(&pdev->regs, chnum);
    } else if (0UL != (u32hcint & USBFS_HCINT_DTERR)) {
        usb_host_int_unmskchhltd(pdev, chnum);
        usb_hchstop(&pdev->regs, chnum);
        usb_host_clrint(pdev, chnum, USBFS_HCINT_NAK);
        pdev->host.HC_Status[chnum] = HOST_CH_DATATGLERR;
        usb_host_clrint(pdev, chnum, USBFS_HCINT_DTERR);
    } else if (0UL != (u32hcint & USBFS_HCINT_FRMOR)) {
        usb_host_int_unmskchhltd(pdev, chnum);
        usb_hchstop(&pdev->regs, chnum);
        usb_host_clrint(pdev, chnum, USBFS_HCINT_FRMOR);
    } else if (0UL != (u32hcint & USBFS_HCINT_XFRC)) {
        if (pdev->basic_cfgs.dmaen == 1U) {
            u32hctsiz = READ_REG32(pdev->regs.HC_REGS[chnum]->HCTSIZ);
            pdev->host.XferCnt[chnum] =  pdev->host.hc[chnum].xfer_len - (u32hctsiz & USBFS_HCTSIZ_XFRSIZ);
        }
        pdev->host.HC_Status[chnum] = HOST_CH_XFERCOMPL;
        pdev->host.ErrCnt [chnum] = 0U;
        usb_host_clrint(pdev, chnum, USBFS_HCINT_XFRC);
        switch (u32eptypetmp) {
            case EP_TYPE_CTRL:
            case EP_TYPE_BULK:
                usb_host_int_unmskchhltd(pdev, chnum);
                usb_hchstop(&pdev->regs, chnum);
                usb_host_clrint(pdev, chnum, USBFS_HCINT_NAK);
                pdev->host.hc[chnum].in_toggle ^= (uint8_t)1;
                break;
            case EP_TYPE_INTR:
                u32hcchar |= USBFS_HCCHAR_ODDFRM;
                WRITE_REG32(pdev->regs.HC_REGS[chnum]->HCCHAR, u32hcchar);
                pdev->host.URB_State[chnum] = HOST_CH_XFER_DONE;
                break;
            case EP_TYPE_ISOC:
                if (pdev->host.HC_Status[chnum] == HOST_CH_XFERCOMPL) {
                    pdev->host.URB_State[chnum] = HOST_CH_XFER_DONE;
                }
                break;
            default:
                break;
        }
    } else if (0UL != (u32hcint & USBFS_HCINT_CHH)) {
        usb_host_int_mskchhltd(pdev, chnum);
        if (pdev->host.HC_Status[chnum] == HOST_CH_XFERCOMPL) {
            pdev->host.URB_State[chnum] = HOST_CH_XFER_DONE;
        } else if (pdev->host.HC_Status[chnum] == HOST_CH_STALL) {
            pdev->host.URB_State[chnum] = HOST_CH_XFER_STALL;
        } else if (pdev->host.HC_Status[chnum] == HOST_CH_XACTERR) {
            pdev->host.ErrCnt[chnum] = 0U;
            pdev->host.URB_State[chnum] = HOST_CH_XFER_ERROR;
        } else if (pdev->host.HC_Status[chnum] == HOST_CH_DATATGLERR) {
            pdev->host.ErrCnt[chnum] = 0U;
            pdev->host.URB_State[chnum] = HOST_CH_XFER_ERROR;
        } else if (u32eptypetmp == EP_TYPE_INTR) {
            pdev->host.hc[chnum].in_toggle ^= (uint8_t)1;
        } else {
            ;
        }
        usb_host_clrint(pdev, chnum, USBFS_HCINT_CHH);
    } else if (0UL != (u32hcint & USBFS_HCINT_TXERR)) {
        usb_host_int_unmskchhltd(pdev, chnum);
        pdev->host.ErrCnt[chnum] ++;
        pdev->host.HC_Status[chnum] = HOST_CH_XACTERR;
        usb_hchstop(&pdev->regs, chnum);
        usb_host_clrint(pdev, chnum, USBFS_HCINT_TXERR);
    } else if (0UL != (u32hcint & USBFS_HCINT_NAK)) {
        if (u32eptypetmp == EP_TYPE_INTR) {
            usb_host_int_unmskchhltd(pdev, chnum);
            usb_hchstop(&pdev->regs, chnum);
        } else if ((u32eptypetmp == EP_TYPE_CTRL) || (u32eptypetmp == EP_TYPE_BULK)) {
            u32hcchar |= USBFS_HCCHAR_CHENA;
            u32hcchar &= ~USBFS_HCCHAR_CHDIS;
            WRITE_REG32(pdev->regs.HC_REGS[chnum]->HCCHAR, u32hcchar);
        } else {
            ;
        }
        pdev->host.HC_Status[chnum] = HOST_CH_NAK;
        usb_host_clrint(pdev, chnum, USBFS_HCINT_NAK);
    } else {
        ;
    }
}

/**
 * @brief  this function processes the channel interrupt
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_host_hc_isr(usb_core_instance *pdev)
{
    uint32_t u32hcchar;
    uint8_t u8Cnt;
    uint32_t u32haint;

    u32haint = READ_REG32(pdev->regs.HREGS->HAINT);
    for (u8Cnt = 0U; u8Cnt < pdev->basic_cfgs.host_chnum; u8Cnt++) {
        if (0UL != (u32haint & (1UL << u8Cnt))) {
            u32hcchar = READ_REG32(pdev->regs.HC_REGS[u8Cnt]->HCCHAR);
            if (0UL != ((u32hcchar & USBFS_HCCHAR_EPDIR) >> USBFS_HCCHAR_EPDIR_POS)) {
                usb_host_chx_in_isr(pdev, u8Cnt);
            } else {
                usb_host_chx_out_isr(pdev, u8Cnt);
            }
        }
    }
}

/**
 * @brief  process the start-of-frame interrupt in host mode.
 * @param  [in] pdev        device instance
 * @retval None
 */
static void usb_host_sof_isr(usb_core_instance *pdev)
{
    WRITE_REG32(pdev->regs.GREGS->GINTSTS, USBFS_GINTSTS_SOF);
}

/**
 * @brief  processes disconnect interrupt
 * @param  [in] pdev        device instance
 * @retval None
 */
static void usb_host_disconn_isr(usb_core_instance *pdev)
{
    usb_gintdis(&pdev->regs);
    usb_vbusctrl(&pdev->regs, 0U);
    WRITE_REG32(pdev->regs.GREGS->GINTSTS, USBFS_GINTSTS_DISCINT);

    pdev->host.is_dev_connect = 0U;
}

#define USBFS_HNPTXSTS_NPTXQTOP_CHEPNUM_POS     (27U)
#define USBFS_HNPTXSTS_NPTXQTOP_CHEPNUM         (0x78000000UL)
/**
 * @brief  processes non-periodic txFIFO empty interrupt.
 * @param  [in] pdev        device instance
 * @retval None
 */
static void usb_host_nptxfifoempty_isr(usb_core_instance *pdev)
{
    uint32_t u32hnptxsts;
    uint16_t u16LenWord;
    uint16_t u16Len;
    uint8_t u8ChNum;

    u32hnptxsts = READ_REG32(pdev->regs.GREGS->HNPTXSTS);
    u8ChNum = (uint8_t)((u32hnptxsts & USBFS_HNPTXSTS_NPTXQTOP_CHEPNUM) >> USBFS_HNPTXSTS_NPTXQTOP_CHEPNUM_POS);

    u16LenWord = (uint16_t)((pdev->host.hc[u8ChNum].xfer_len + 3UL) / 4UL);
    while (((u32hnptxsts & USBFS_HNPTXSTS_NPTXFSAV) > u16LenWord) && (pdev->host.hc[u8ChNum].xfer_len != 0U)) {
        u16Len = (uint16_t)((u32hnptxsts & USBFS_HNPTXSTS_NPTXFSAV) * 4UL);
        if (u16Len > pdev->host.hc[u8ChNum].xfer_len) {
            u16Len = (uint16_t)pdev->host.hc[u8ChNum].xfer_len;
            CLR_REG32_BIT(pdev->regs.GREGS->GINTMSK, USBFS_GINTSTS_NPTXFE);
        }
        u16LenWord = (uint16_t)((pdev->host.hc[u8ChNum].xfer_len + 3UL) / 4UL);
        usb_wrpkt(&pdev->regs, pdev->host.hc[u8ChNum].xfer_buff, u8ChNum, u16Len, pdev->basic_cfgs.dmaen);
        pdev->host.hc[u8ChNum].xfer_buff += u16Len;
        pdev->host.hc[u8ChNum].xfer_len -= u16Len;
        pdev->host.hc[u8ChNum].xfer_count += u16Len;
        u32hnptxsts = READ_REG32(pdev->regs.GREGS->HNPTXSTS);
    }
}
#define USBFS_HPTXSTS_PTXQTOP_CHNUM_POS     (27U)
#define USBFS_HPTXSTS_PTXQTOP_CHNUM         (0x78000000UL)
/**
 * @brief  processes periodic txFIFO empty interrupt
 * @param  [in] pdev        device instance
 * @retval None
 */
static void usb_host_ptxfifoempty_isr(usb_core_instance *pdev)
{
    uint32_t u32hptxsts;
    uint16_t u16LenWord;
    uint16_t u16Len;
    uint8_t u8ChNum;

    u32hptxsts = READ_REG32(pdev->regs.HREGS->HPTXSTS);
    u8ChNum = (uint8_t)((u32hptxsts & USBFS_HPTXSTS_PTXQTOP_CHNUM) >> USBFS_HPTXSTS_PTXQTOP_CHNUM_POS);
    u16LenWord = (uint16_t)((pdev->host.hc[u8ChNum].xfer_len + 3UL) / 4UL);
    while ((((u32hptxsts & USBFS_HPTXSTS_PTXFSAVL)) > u16LenWord) && (pdev->host.hc[u8ChNum].xfer_len != 0U)) {
        u16Len = (uint16_t)((u32hptxsts & USBFS_HPTXSTS_PTXFSAVL) * 4UL);
        if (u16Len > pdev->host.hc[u8ChNum].xfer_len) {
            u16Len = (uint16_t)pdev->host.hc[u8ChNum].xfer_len;
            CLR_REG32_BIT(pdev->regs.GREGS->GINTMSK, USBFS_GINTMSK_PTXFEM);
        }
        u16LenWord = (uint16_t)((pdev->host.hc[u8ChNum].xfer_len + 3UL) / 4UL);
        usb_wrpkt(&pdev->regs, pdev->host.hc[u8ChNum].xfer_buff, u8ChNum, u16Len, pdev->basic_cfgs.dmaen);
        pdev->host.hc[u8ChNum].xfer_buff += u16Len;
        pdev->host.hc[u8ChNum].xfer_len -= u16Len;
        pdev->host.hc[u8ChNum].xfer_count += u16Len;
        u32hptxsts = READ_REG32(pdev->regs.HREGS->HPTXSTS);
    }
}

/**
 * @brief  This function determines which interrupt conditions have occurred
 * @param  [in] pdev        device instance
 * @retval None
 */
static void usb_host_port_isr(usb_core_instance *pdev)
{
    uint32_t u32hprt;
    uint32_t u32hprt_bk;
    uint8_t u8fslspclksel;
    uint32_t do_reset = 0UL;
    uint8_t u8PortSpeed;

    u32hprt = READ_REG32(*pdev->regs.HPRT);
    u32hprt_bk = u32hprt;
    /* Clear the interrupt bits in GINTSTS */
    //tmp_hprt_bk.b.prtovrcurrchng = 0U;  //todo don't have this bit
    u32hprt_bk &= ~(USBFS_HPRT_PENA | USBFS_HPRT_PCDET | USBFS_HPRT_PENCHNG);

    /* check if a port connect have been detected */
    if ((u32hprt & USBFS_HPRT_PCDET) != 0UL) {
        u32hprt_bk |= USBFS_HPRT_PCDET;
        if (host_driver_getvbusdrivestate(pdev) != 0UL) {
            pdev->host.is_dev_connect = 1U;
        }
    }
    /* check if port enable or disable change */
    if ((u32hprt & USBFS_HPRT_PENCHNG) != 0UL) {
        u32hprt_bk |= USBFS_HPRT_PENCHNG;

        if ((u32hprt & USBFS_HPRT_PENA) != 0UL) {
            u8PortSpeed = (uint8_t)((u32hprt & USBFS_HPRT_PSPD) >> USBFS_HPRT_PSPD_POS);
            if ((u8PortSpeed == PRTSPD_LOW_SPEED) || (u8PortSpeed == PRTSPD_FULL_SPEED)) {
                u8fslspclksel = (uint8_t)(READ_REG32(pdev->regs.HREGS->HCFG) & USBFS_HCFG_FSLSPCS);
                if (u8PortSpeed == PRTSPD_LOW_SPEED) {
                    if (u8fslspclksel != HCFG_6_MHZ) {
                        do_reset = 1U;
                    }
                } else {
                    /* 1ms*(PHY clock frequency for FS/LS)-1 */
                    WRITE_REG32(pdev->regs.HREGS->HFIR, 48000UL);
                    if (u8fslspclksel != HCFG_48_MHZ) {
                        usb_fslspclkselset(&pdev->regs, HCFG_48_MHZ);
                        do_reset = 1U;
                    }
                }
            } else {
                do_reset = 1U;
            }
        }
    }

    //todo don't have this bit
    //if ((u32hprt & USBFS_HPRT_PRTOVRCURRCHNG) != 0UL) {
    //    u32hprt_bk |= USBFS_HPRT_PRTOVRCURRCHNG;
    //}

    if (0UL != do_reset) {
        usb_hprtrst(&pdev->regs);
    }
    WRITE_REG32(*pdev->regs.HPRT, u32hprt_bk);
}

/**
 * @brief  processes the rxFIFO non-empty interrupt
 * @param  [in] pdev        device instance
 * @retval None
 */
static void usb_host_rxflvl_isr(usb_core_instance *pdev)
{
    uint32_t u32grxsts;
    uint32_t u32hctsiz;
    uint32_t u32hcchar;
    uint8_t u8chnum;
    uint8_t *pu8Tmp;
    uint16_t u16bcnt;

    CLR_REG32_BIT(pdev->regs.GREGS->GINTMSK, USBFS_GINTSTS_RXFNE);

    u32grxsts = READ_REG32(pdev->regs.GREGS->GRXSTSP);
    u8chnum = (uint8_t)(u32grxsts & USBFS_GRXSTSP_CHNUM_EPNUM);
    u16bcnt = (uint16_t)((u32grxsts & USBFS_GRXSTSP_BCNT) >> USBFS_GRXSTSP_BCNT_POS);
    u32hcchar = READ_REG32(pdev->regs.HC_REGS[u8chnum]->HCCHAR);

    switch ((u32grxsts & USBFS_GRXSTSP_PKTSTS) >> USBFS_GRXSTSP_PKTSTS_POS) {
        case 2:              /* IN dat packet received */
            pu8Tmp = pdev->host.hc[u8chnum].xfer_buff;
            if ((u16bcnt > 0U) && (pu8Tmp != (void *)0U)) {
                usb_rdpkt(&pdev->regs, pdev->host.hc[u8chnum].xfer_buff, u16bcnt);
                pdev->host.hc[u8chnum].xfer_buff += u16bcnt;
                pdev->host.hc[u8chnum].xfer_count  += u16bcnt;
                pdev->host.XferCnt[u8chnum] = pdev->host.hc[u8chnum].xfer_count;

                u32hctsiz = READ_REG32(pdev->regs.HC_REGS[u8chnum]->HCTSIZ);
                if (((u32hctsiz & USBFS_HCTSIZ_PKTCNT) >> USBFS_HCTSIZ_PKTCNT_POS) > 0U) {
                    u32hcchar |= USBFS_HCCHAR_CHENA;
                    u32hcchar &= ~USBFS_HCCHAR_CHDIS;
                    WRITE_REG32(pdev->regs.HC_REGS[u8chnum]->HCCHAR, u32hcchar);
                }
            }
            break;

        case 3:              /* IN transfer completed(trigger an interrupt) */
            break;
        case 5:              /* Daat toggle error(trigger an interrupt) */
            break;
        case 7:              /* Channel halted(trigger an interrupt) */
            break;
        default:
            break;
    }

    SET_REG32_BIT(pdev->regs.GREGS->GINTMSK, USBFS_GINTSTS_RXFNE);
}

/**
 * @brief  process the incomplete periodic transfer interrupt(incompIP)
 * @param  [in] pdev        device instance
 * @retval None
 */
static void usb_host_incomplisoout_isr(usb_core_instance *pdev)
{
    SET_REG32_BIT(pdev->regs.HC_REGS[0]->HCCHAR, USBFS_HCCHAR_CHENA | USBFS_HCCHAR_CHDIS);
    WRITE_REG32(pdev->regs.GREGS->GINTSTS, USBFS_GINTSTS_IPXFR_INCOMPISOOUT);
}

/**
 * @brief  process the resume/remote wakeup detected interrupt(WkUpInt)
 * @param  [in] pdev        device instance
 * @retval None
 */
static void usb_host_wkupint_isr(usb_core_instance *pdev)
{
    uint32_t u32hprt;
    u32hprt = usb_rdhprt(&pdev->regs);
    u32hprt &= ~USBFS_HPRT_PRES;
    WRITE_REG32(*pdev->regs.HPRT, u32hprt);
}

/**
 * @brief  This function process all interrupt of USB in host mode
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_host_isr(usb_core_instance *pdev)
{
    uint32_t gintstsval;
    if (0U != usb_getcurmod(&pdev->regs)) {
        gintstsval = usb_getcoreintr(&pdev->regs);
        if (0UL != (gintstsval & USBFS_GINTSTS_SOF)) {
            usb_host_sof_isr(pdev);
        }
        if (0UL != (gintstsval & USBFS_GINTSTS_RXFNE)) {
            usb_host_rxflvl_isr(pdev);
        }
        if (0UL != (gintstsval & USBFS_GINTSTS_NPTXFE)) {
            usb_host_nptxfifoempty_isr(pdev);
        }
        if (0UL != (gintstsval & USBFS_GINTSTS_PTXFE)) {
            usb_host_ptxfifoempty_isr(pdev);
        }
        if (0UL != (gintstsval & USBFS_GINTSTS_HCINT)) {
            usb_host_hc_isr(pdev);
        }
        if (0UL != (gintstsval & USBFS_GINTSTS_HPRTINT)) {
            usb_host_port_isr(pdev);
        }
        if (0UL != (gintstsval & USBFS_GINTSTS_DISCINT)) {
            usb_host_disconn_isr(pdev);
        }
        if (0UL != (gintstsval & USBFS_GINTSTS_IPXFR_INCOMPISOOUT)) {
            usb_host_incomplisoout_isr(pdev);
        }
        if (0UL != (gintstsval & USBFS_GINTSTS_WKUINT)) {
            usb_host_wkupint_isr(pdev);
        }
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
