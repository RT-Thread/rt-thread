/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-25     CDT          first version
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtthread.h>
#include <rtdevice.h>

#if defined(BSP_USING_USBH)

//#define DRV_DEBUG
#define LOG_TAG             "drv.usbh"
#include <drv_log.h>

#include "board_config.h"
#include "irq_config.h"
#include "drv_usbh.h"

extern rt_err_t rt_hw_usb_board_init(void);
extern void rt_hw_us_delay(rt_uint32_t us);

static usb_core_instance _hc32_usbh;
static volatile rt_bool_t connect_status = RT_FALSE;
static struct rt_completion urb_completion;


void usb_udelay(const uint32_t usec)
{
    rt_hw_us_delay(usec);
}

void usb_mdelay(const uint32_t msec)
{
    rt_thread_mdelay(msec);
}

void usb_bsp_cfgvbus(usb_core_instance *pdev)
{
    /* reserved */
}
void usb_bsp_drivevbus(usb_core_instance *pdev, uint8_t state)
{
    /* reserved */
}

static void usb_device_connect_callback(usb_core_instance *pdev)
{
    uhcd_t hcd = (uhcd_t)pdev->pData;
    if (!connect_status)
    {
        connect_status = RT_TRUE;
        LOG_D("usb connected");
        rt_usbh_root_hub_connect_handler(hcd, USB_FS_PORT, RT_FALSE);
    }
}

static void usb_device_disconnect_callback(usb_core_instance *pdev)
{
    uhcd_t hcd = (uhcd_t)pdev->pData;
    if (connect_status)
    {
        connect_status = RT_FALSE;
        LOG_D("usb disconnnect");
        rt_usbh_root_hub_disconnect_handler(hcd, USB_FS_PORT);
    }
}

static void usb_host_notify_urbchange_Callback(usb_core_instance *pdev, uint8_t chnum, HOST_CH_XFER_STATE urb_state)
{
    rt_completion_done(&urb_completion);
}

static void usb_host_chx_out_isr(usb_core_instance *pdev, uint8_t chnum)
{
    uint32_t u32hcchar;
    uint32_t u32hcint;
    uint32_t u32hcintmsk;

    u32hcchar = READ_REG32(pdev->regs.HC_REGS[chnum]->HCCHAR);
    u32hcint = READ_REG32(pdev->regs.HC_REGS[chnum]->HCINT);
    u32hcintmsk = READ_REG32(pdev->regs.HC_REGS[chnum]->HCINTMSK);
    u32hcint = u32hcint & u32hcintmsk;

    if (0UL != (u32hcint & USBFS_HCINT_ACK))
    {
        usb_host_clrint(pdev, chnum, USBFS_HCINT_ACK);
    }
#if defined (HC32F4A0)
    else if (0UL != (u32hcint & USBFS_HCINT_AHBERR))
    {
        usb_host_clrint(pdev, chnum, USBFS_HCINT_AHBERR);
        usb_host_int_unmskchhltd(pdev, chnum);
    }
#endif
    else if (0UL != (u32hcint & USBFS_HCINT_FRMOR))
    {
        usb_host_int_unmskchhltd(pdev, chnum);
        usb_hchstop(&pdev->regs, chnum);
        usb_host_clrint(pdev, chnum, USBFS_HCINT_FRMOR);
    }
    else if (0UL != (u32hcint & USBFS_HCINT_XFRC))
    {
        pdev->host.ErrCnt[chnum] = 0U;
        usb_host_int_unmskchhltd(pdev, chnum);
        usb_hchstop(&pdev->regs, chnum);
        usb_host_clrint(pdev, chnum, USBFS_HCINT_XFRC);
        pdev->host.HC_Status[chnum] = HOST_CH_XFERCOMPL;
    }
    else if (0UL != (u32hcint & USBFS_HCINT_STALL))
    {
        usb_host_clrint(pdev, chnum, USBFS_HCINT_STALL);
        usb_host_int_unmskchhltd(pdev, chnum);
        usb_hchstop(&pdev->regs, chnum);
        pdev->host.HC_Status[chnum] = HOST_CH_STALL;
    }
    else if (0UL != (u32hcint & USBFS_HCINT_NAK))
    {
        pdev->host.ErrCnt[chnum] = 0U;
        usb_host_int_unmskchhltd(pdev, chnum);
        usb_hchstop(&pdev->regs, chnum);
        usb_host_clrint(pdev, chnum, USBFS_HCINT_NAK);
        pdev->host.HC_Status[chnum] = HOST_CH_NAK;
    }
    else if (0UL != (u32hcint & USBFS_HCINT_TXERR))
    {
        usb_host_int_unmskchhltd(pdev, chnum);
        usb_hchstop(&pdev->regs, chnum);
        pdev->host.ErrCnt[chnum] ++;
        pdev->host.HC_Status[chnum] = HOST_CH_XACTERR;
        usb_host_clrint(pdev, chnum, USBFS_HCINT_TXERR);
    }
    else if (0UL != (u32hcint & HCINT_NYET))
    {
        pdev->host.ErrCnt[chnum] = 0U;
        usb_host_int_unmskchhltd(pdev, chnum);
        usb_hchstop(&pdev->regs, chnum);
        usb_host_clrint(pdev, chnum, HCINT_NYET);
        pdev->host.HC_Status[chnum] = HOST_CH_NYET;
    }
    else if (0UL != (u32hcint & USBFS_HCINT_DTERR))
    {
        usb_host_int_unmskchhltd(pdev, chnum);
        usb_hchstop(&pdev->regs, chnum);
        usb_host_clrint(pdev, chnum, USBFS_HCINT_NAK);
        pdev->host.HC_Status[chnum] = HOST_CH_DATATGLERR;
        usb_host_clrint(pdev, chnum, USBFS_HCINT_DTERR);
    }
    else if (0UL != (u32hcint & USBFS_HCINT_CHH))
    {
        usb_host_int_mskchhltd(pdev, chnum);
        if (pdev->host.HC_Status[chnum] == HOST_CH_XFERCOMPL)
        {
            pdev->host.URB_State[chnum] = HOST_CH_XFER_DONE;

            if (((u32hcchar & USBFS_HCCHAR_EPTYP) >> USBFS_HCCHAR_EPTYP_POS) == EP_TYPE_BULK)
            {
                pdev->host.hc[chnum].out_toggle ^= 1U;
            }
        }
        else if (pdev->host.HC_Status[chnum] == HOST_CH_NAK)
        {
            pdev->host.URB_State[chnum] = HOST_CH_XFER_UNREADY;
        }
        else if (pdev->host.HC_Status[chnum] == HOST_CH_NYET)
        {
            if (pdev->host.hc[chnum].do_ping == 1U)
            {
                usb_pingtokenissue(&pdev->regs, chnum);
            }
            pdev->host.URB_State[chnum] = HOST_CH_XFER_UNREADY;
        }
        else if (pdev->host.HC_Status[chnum] == HOST_CH_STALL)
        {
            pdev->host.URB_State[chnum] = HOST_CH_XFER_STALL;
        }
        else if (pdev->host.HC_Status[chnum] == HOST_CH_XACTERR)
        {
            pdev->host.URB_State[chnum] = HOST_CH_XFER_ERROR;
            pdev->host.ErrCnt[chnum] = 0UL;
        }
        else
        {
            ;
        }
        usb_host_clrint(pdev, chnum, USBFS_HCINT_CHH);
        usb_host_notify_urbchange_Callback(pdev, chnum, pdev->host.URB_State[chnum]);
    }
    else
    {
        ;
    }
}

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
    if (0UL != (u32hcint & USBFS_HCINT_ACK))
    {
        usb_host_clrint(pdev, chnum, USBFS_HCINT_ACK);
    }
#if defined (HC32F4A0)
    else if (0UL != (u32hcint & USBFS_HCINT_AHBERR))
    {
        usb_host_clrint(pdev, chnum, USBFS_HCINT_AHBERR);
        usb_host_int_unmskchhltd(pdev, chnum);
    }
#endif
    else if (0UL != (u32hcint & USBFS_HCINT_BBERR))
    {
        usb_host_clrint(pdev, chnum, USBFS_HCINT_BBERR);
        pdev->host.HC_Status[chnum] = HOST_CH_BBLERR;
        usb_host_int_unmskchhltd(pdev, chnum);
        usb_hchstop(&pdev->regs, chnum);
    }
    else if (0UL != (u32hcint & USBFS_HCINT_STALL))
    {
        usb_host_int_unmskchhltd(pdev, chnum);
        pdev->host.HC_Status[chnum] = HOST_CH_STALL;
        usb_host_clrint(pdev, chnum, USBFS_HCINT_NAK);
        usb_host_clrint(pdev, chnum, USBFS_HCINT_STALL);
        usb_hchstop(&pdev->regs, chnum);
    }
    else if (0UL != (u32hcint & USBFS_HCINT_DTERR))
    {
        usb_host_int_unmskchhltd(pdev, chnum);
        usb_hchstop(&pdev->regs, chnum);
        usb_host_clrint(pdev, chnum, USBFS_HCINT_NAK);
        pdev->host.HC_Status[chnum] = HOST_CH_DATATGLERR;
        usb_host_clrint(pdev, chnum, USBFS_HCINT_DTERR);
    }
    else if (0UL != (u32hcint & USBFS_HCINT_FRMOR))
    {
        usb_host_int_unmskchhltd(pdev, chnum);
        usb_hchstop(&pdev->regs, chnum);
        usb_host_clrint(pdev, chnum, USBFS_HCINT_FRMOR);
    }
    else if (0UL != (u32hcint & USBFS_HCINT_XFRC))
    {
        if (pdev->basic_cfgs.dmaen == 1U)
        {
            u32hctsiz = READ_REG32(pdev->regs.HC_REGS[chnum]->HCTSIZ);
            pdev->host.XferCnt[chnum] =  pdev->host.hc[chnum].xfer_len - (u32hctsiz & USBFS_HCTSIZ_XFRSIZ);
            pdev->host.hc[chnum].xfer_count += pdev->host.XferCnt[chnum];
        }
        pdev->host.HC_Status[chnum] = HOST_CH_XFERCOMPL;
        pdev->host.ErrCnt [chnum] = 0U;
        usb_host_clrint(pdev, chnum, USBFS_HCINT_XFRC);
        switch (u32eptypetmp)
        {
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
            usb_host_notify_urbchange_Callback(pdev, chnum, pdev->host.URB_State[chnum]);
            break;
        case EP_TYPE_ISOC:
            if (pdev->host.HC_Status[chnum] == HOST_CH_XFERCOMPL)
            {
                pdev->host.URB_State[chnum] = HOST_CH_XFER_DONE;
                usb_host_notify_urbchange_Callback(pdev, chnum, pdev->host.URB_State[chnum]);
            }
            break;
        default:
            break;
        }
    }
    else if (0UL != (u32hcint & USBFS_HCINT_CHH))
    {
        usb_host_int_mskchhltd(pdev, chnum);
        if (pdev->host.HC_Status[chnum] == HOST_CH_XFERCOMPL)
        {
            pdev->host.URB_State[chnum] = HOST_CH_XFER_DONE;
        }
        else if (pdev->host.HC_Status[chnum] == HOST_CH_STALL)
        {
            pdev->host.URB_State[chnum] = HOST_CH_XFER_STALL;
        }
        else if (pdev->host.HC_Status[chnum] == HOST_CH_XACTERR)
        {
            pdev->host.ErrCnt[chnum] = 0U;
            pdev->host.URB_State[chnum] = HOST_CH_XFER_ERROR;
        }
        else if (pdev->host.HC_Status[chnum] == HOST_CH_DATATGLERR)
        {
            pdev->host.ErrCnt[chnum] = 0U;
            pdev->host.URB_State[chnum] = HOST_CH_XFER_ERROR;
        }
        else if (pdev->host.HC_Status[chnum] == HOST_CH_BBLERR)
        {
            pdev->host.ErrCnt[chnum] ++;
            pdev->host.URB_State[chnum] = HOST_CH_XFER_ERROR;
        }
        else if (u32eptypetmp == EP_TYPE_INTR)
        {
            pdev->host.hc[chnum].in_toggle ^= (uint8_t)1;
        }
        else
        {
            ;
        }
        usb_host_clrint(pdev, chnum, USBFS_HCINT_CHH);
        usb_host_notify_urbchange_Callback(pdev, chnum, pdev->host.URB_State[chnum]);
    }
    else if (0UL != (u32hcint & USBFS_HCINT_TXERR))
    {
        usb_host_int_unmskchhltd(pdev, chnum);
        pdev->host.ErrCnt[chnum] ++;
        pdev->host.HC_Status[chnum] = HOST_CH_XACTERR;
        usb_hchstop(&pdev->regs, chnum);
        usb_host_clrint(pdev, chnum, USBFS_HCINT_TXERR);
    }
    else if (0UL != (u32hcint & USBFS_HCINT_NAK))
    {
        if (u32eptypetmp == EP_TYPE_INTR)
        {
            usb_host_int_unmskchhltd(pdev, chnum);
            usb_hchstop(&pdev->regs, chnum);
        }
        else if (u32eptypetmp == EP_TYPE_CTRL)
        {
            u32hcchar |= USBFS_HCCHAR_CHENA;
            u32hcchar &= ~USBFS_HCCHAR_CHDIS;
            WRITE_REG32(pdev->regs.HC_REGS[chnum]->HCCHAR, u32hcchar);
        }
        else if (u32eptypetmp == EP_TYPE_BULK)
        {
            usb_host_int_unmskchhltd(pdev, chnum);
            usb_hchstop(&pdev->regs, chnum);/* stop hc avoid block */
        }
        else
        {
            ;
        }
        pdev->host.HC_Status[chnum] = HOST_CH_NAK;
        usb_host_clrint(pdev, chnum, USBFS_HCINT_NAK);
    }
    else
    {
        ;
    }
}

static void usb_host_hc_isr(usb_core_instance *pdev)
{
    uint32_t u32hcchar;
    uint8_t u8Cnt;
    uint32_t u32haint;

    u32haint = READ_REG32(pdev->regs.HREGS->HAINT);
    for (u8Cnt = 0U; u8Cnt < pdev->basic_cfgs.host_chnum; u8Cnt++)
    {
        if (0UL != (u32haint & (1UL << u8Cnt)))
        {
            u32hcchar = READ_REG32(pdev->regs.HC_REGS[u8Cnt]->HCCHAR);
            if (0UL != ((u32hcchar & USBFS_HCCHAR_EPDIR) >> USBFS_HCCHAR_EPDIR_POS))
            {
                usb_host_chx_in_isr(pdev, u8Cnt);
            }
            else
            {
                usb_host_chx_out_isr(pdev, u8Cnt);
            }
        }
    }
}

static void usb_host_sof_isr(usb_core_instance *pdev)
{
    WRITE_REG32(pdev->regs.GREGS->GINTSTS, USBFS_GINTSTS_SOF);
}

static void usb_host_disconn_isr(usb_core_instance *pdev)
{
    WRITE_REG32(pdev->regs.GREGS->GINTSTS, USBFS_GINTSTS_DISCINT);

    /* flush all the txFIFOs and the whole rxFIFO */
    usb_rxfifoflush(&pdev->regs);
    usb_txfifoflush(&pdev->regs, 0x10UL);

    pdev->host.is_dev_connect = 0U;
    usb_device_disconnect_callback(pdev);
}

#define USBFS_HNPTXSTS_NPTXQTOP_CHEPNUM_POS     (27U)
#define USBFS_HNPTXSTS_NPTXQTOP_CHEPNUM         (0x78000000UL)

static void usb_host_nptxfifoempty_isr(usb_core_instance *pdev)
{
    uint32_t u32hnptxsts;
    uint16_t u16LenWord;
    uint16_t u16Len;
    uint8_t u8ChNum;

    u32hnptxsts = READ_REG32(pdev->regs.GREGS->HNPTXSTS);
    u8ChNum = (uint8_t)((u32hnptxsts & USBFS_HNPTXSTS_NPTXQTOP_CHEPNUM) >> USBFS_HNPTXSTS_NPTXQTOP_CHEPNUM_POS) % USB_MAX_TX_FIFOS;

    u16LenWord = (uint16_t)((pdev->host.hc[u8ChNum].xfer_len + 3UL) / 4UL);
    while (((u32hnptxsts & USBFS_HNPTXSTS_NPTXFSAV) > u16LenWord) && (pdev->host.hc[u8ChNum].xfer_len != 0U))
    {
        u16Len = (uint16_t)((u32hnptxsts & USBFS_HNPTXSTS_NPTXFSAV) * 4UL);
        if (u16Len > pdev->host.hc[u8ChNum].xfer_len)
        {
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

static void usb_host_ptxfifoempty_isr(usb_core_instance *pdev)
{
    uint32_t u32hptxsts;
    uint16_t u16LenWord;
    uint16_t u16Len;
    uint8_t u8ChNum;

    u32hptxsts = READ_REG32(pdev->regs.HREGS->HPTXSTS);
    u8ChNum = (uint8_t)((u32hptxsts & USBFS_HPTXSTS_PTXQTOP_CHNUM) >> USBFS_HPTXSTS_PTXQTOP_CHNUM_POS) % USB_MAX_TX_FIFOS;
    u16LenWord = (uint16_t)((pdev->host.hc[u8ChNum].xfer_len + 3UL) / 4UL);
    while ((((u32hptxsts & USBFS_HPTXSTS_PTXFSAVL)) > u16LenWord) && (pdev->host.hc[u8ChNum].xfer_len != 0U))
    {
        u16Len = (uint16_t)((u32hptxsts & USBFS_HPTXSTS_PTXFSAVL) * 4UL);
        if (u16Len > pdev->host.hc[u8ChNum].xfer_len)
        {
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

static uint32_t host_driver_getvbusdrivestate(usb_core_instance *pdev)
{
    uint32_t u32hppt;
    u32hppt = READ_REG32(*pdev->regs.HPRT);
    return ((u32hppt & USBFS_HPRT_PWPR) >> USBFS_HPRT_PWPR_POS);
}

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
    u32hprt_bk &= ~(USBFS_HPRT_PENA | USBFS_HPRT_PCDET | USBFS_HPRT_PENCHNG);

    /* check if a port connect have been detected */
    if ((u32hprt & USBFS_HPRT_PCDET) != 0UL)
    {
        u32hprt_bk |= USBFS_HPRT_PCDET;
        if (host_driver_getvbusdrivestate(pdev) != 0UL)
        {
            pdev->host.is_dev_connect = 1U;
            usb_device_connect_callback(pdev);
        }
    }
    /* check if port enable or disable change */
    if ((u32hprt & USBFS_HPRT_PENCHNG) != 0UL)
    {
        u32hprt_bk |= USBFS_HPRT_PENCHNG;

        if ((u32hprt & USBFS_HPRT_PENA) != 0UL)
        {
            u8PortSpeed = (uint8_t)((u32hprt & USBFS_HPRT_PSPD) >> USBFS_HPRT_PSPD_POS);
            pdev->host.devspeed = u8PortSpeed;
            if ((u8PortSpeed == PRTSPD_LOW_SPEED) || (u8PortSpeed == PRTSPD_FULL_SPEED))
            {
                u8fslspclksel = (uint8_t)(READ_REG32(pdev->regs.HREGS->HCFG) & USBFS_HCFG_FSLSPCS);
                if (u8PortSpeed == PRTSPD_LOW_SPEED)
                {
                    if (u8fslspclksel != HCFG_6_MHZ)
                    {
                        do_reset = 1U;
                    }
                }
                else
                {
                    /* 1ms*(PHY clock frequency for FS/LS)-1 */
                    WRITE_REG32(pdev->regs.HREGS->HFIR, 48000UL);
                    if (u8fslspclksel != HCFG_48_MHZ)
                    {
                        usb_fslspclkselset(&pdev->regs, HCFG_48_MHZ);
                        do_reset = 1U;
                    }
                }
            }
            else
            {
                do_reset = 1U;
            }
        }
    }

    if (0UL != do_reset)
    {
        /* RTT Will Call Reset */
    }
    WRITE_REG32(*pdev->regs.HPRT, u32hprt_bk);
}

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
    u8chnum = (uint8_t)(u32grxsts & USBFS_GRXSTSP_CHNUM_EPNUM) % USB_MAX_TX_FIFOS;
    u16bcnt = (uint16_t)((u32grxsts & USBFS_GRXSTSP_BCNT) >> USBFS_GRXSTSP_BCNT_POS);
    u32hcchar = READ_REG32(pdev->regs.HC_REGS[u8chnum]->HCCHAR);

    switch ((u32grxsts & USBFS_GRXSTSP_PKTSTS) >> USBFS_GRXSTSP_PKTSTS_POS)
    {
    case 2:              /* IN dat packet received */
        pu8Tmp = pdev->host.hc[u8chnum].xfer_buff;
        if ((u16bcnt > 0U) && (pu8Tmp != (void *)0U))
        {
            usb_rdpkt(&pdev->regs, pdev->host.hc[u8chnum].xfer_buff, u16bcnt);
            pdev->host.hc[u8chnum].xfer_buff += u16bcnt;
            pdev->host.hc[u8chnum].xfer_count  += u16bcnt;
            pdev->host.XferCnt[u8chnum] = pdev->host.hc[u8chnum].xfer_count;

            u32hctsiz = READ_REG32(pdev->regs.HC_REGS[u8chnum]->HCTSIZ);
            if (((u32hctsiz & USBFS_HCTSIZ_PKTCNT) >> USBFS_HCTSIZ_PKTCNT_POS) > 0U)
            {
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

static void usb_host_incomplisoout_isr(usb_core_instance *pdev)
{
    SET_REG32_BIT(pdev->regs.HC_REGS[0]->HCCHAR, USBFS_HCCHAR_CHENA | USBFS_HCCHAR_CHDIS);
    WRITE_REG32(pdev->regs.GREGS->GINTSTS, USBFS_GINTSTS_IPXFR_INCOMPISOOUT);
}

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
static void usb_host_isr(usb_core_instance *pdev)
{
    uint32_t gintstsval;
    if (0U != usb_getcurmod(&pdev->regs))
    {
        gintstsval = usb_getcoreintr(&pdev->regs);
        if (0UL != (gintstsval & USBFS_GINTSTS_SOF))
        {
            usb_host_sof_isr(pdev);
        }
        if (0UL != (gintstsval & USBFS_GINTSTS_RXFNE))
        {
            usb_host_rxflvl_isr(pdev);
        }
        if (0UL != (gintstsval & USBFS_GINTSTS_NPTXFE))
        {
            usb_host_nptxfifoempty_isr(pdev);
        }
        if (0UL != (gintstsval & USBFS_GINTSTS_PTXFE))
        {
            usb_host_ptxfifoempty_isr(pdev);
        }
        if (0UL != (gintstsval & USBFS_GINTSTS_HCINT))
        {
            usb_host_hc_isr(pdev);
        }
        if (0UL != (gintstsval & USBFS_GINTSTS_HPRTINT))
        {
            usb_host_port_isr(pdev);
        }
        if (0UL != (gintstsval & USBFS_GINTSTS_DISCINT))
        {
            usb_host_disconn_isr(pdev);
        }
        if (0UL != (gintstsval & USBFS_GINTSTS_IPXFR_INCOMPISOOUT))
        {
            usb_host_incomplisoout_isr(pdev);
        }
        if (0UL != (gintstsval & USBFS_GINTSTS_WKUINT))
        {
            usb_host_wkupint_isr(pdev);
        }
    }
}

static void usbh_irq_handler(void)
{
    rt_interrupt_enter();
    usb_host_isr(&_hc32_usbh);
    rt_interrupt_leave();
}

static void usb_host_chopen(usb_core_instance *pdev,
                            uint8_t  hc_num,
                            uint8_t  epnum,
                            uint8_t  dev_address,
                            uint8_t  speed,
                            uint8_t  ep_type,
                            uint16_t mps)
{
    pdev->host.channel[hc_num] = epnum; /* assign channel here */
    pdev->host.hc[hc_num].ep_idx     = (uint8_t) pdev->host.channel[hc_num] & 0x7FU;
    pdev->host.hc[hc_num].is_epin    = (uint8_t)((pdev->host.channel[hc_num] & 0x80U) == 0x80U);
    pdev->host.hc[hc_num].dev_addr   = dev_address;
    pdev->host.hc[hc_num].ep_type    = ep_type;
    pdev->host.hc[hc_num].max_packet = mps;
    pdev->host.hc[hc_num].ch_speed   = speed;
    pdev->host.hc[hc_num].in_toggle  = 0U;
    pdev->host.hc[hc_num].out_toggle = 0U;

    (void)usb_inithch(&pdev->regs, hc_num, &pdev->host.hc[hc_num], pdev->basic_cfgs.dmaen);
}

static void usb_host_ch_init(usb_core_instance *pdev,
                             uint8_t  hc_num,
                             uint8_t  epnum,
                             uint8_t  dev_address,
                             uint8_t  speed,
                             uint8_t  ep_type,
                             uint16_t mps)
{
    pdev->host.channel[hc_num] = epnum; /* assign channel here */
    pdev->host.hc[hc_num].ep_idx     = (uint8_t) pdev->host.channel[hc_num] & 0x7FU;
    pdev->host.hc[hc_num].is_epin    = (uint8_t)((pdev->host.channel[hc_num] & 0x80U) == 0x80U);
    pdev->host.hc[hc_num].dev_addr   = dev_address;
    pdev->host.hc[hc_num].ep_type    = ep_type;
    pdev->host.hc[hc_num].max_packet = mps;
    pdev->host.hc[hc_num].ch_speed   = speed;

    (void)usb_inithch(&pdev->regs, hc_num, &pdev->host.hc[hc_num], pdev->basic_cfgs.dmaen);
}

static uint32_t usb_host_submitrequest(usb_core_instance *pdev,
                                       uint8_t ch_num,
                                       uint8_t direction,
                                       uint8_t ep_type,
                                       uint8_t token,
                                       uint8_t *pbuff,
                                       uint16_t length,
                                       uint8_t do_ping)
{
    pdev->host.hc[ch_num].is_epin = direction;
    pdev->host.hc[ch_num].ep_type  = ep_type;

    if (token == 0U)
    {
        pdev->host.hc[ch_num].pid_type = PID_SETUP;
        pdev->host.hc[ch_num].do_ping = do_ping;
    }
    else
    {
        pdev->host.hc[ch_num].pid_type = PID_DATA1;
    }

    /* Manage Data Toggle */
    switch (ep_type)
    {
    case EP_TYPE_CTRL:
        if ((token == 1U) && (direction == 0U)) /*send data */
        {
            if (length == 0U)
            {
                /* For Status OUT stage, Length==0, Status Out PID = 1 */
                pdev->host.hc[ch_num].out_toggle = 1U;
            }
            /* Set the Data Toggle bit as per the Flag */
            if (pdev->host.hc[ch_num].out_toggle == 0U)
            {
                /* Put the PID 0 */
                pdev->host.hc[ch_num].pid_type = PID_DATA0;
            }
            else
            {
                /* Put the PID 1 */
                pdev->host.hc[ch_num].pid_type = PID_DATA1;
            }
        }
        break;
    case EP_TYPE_BULK:
        if (direction == 0U)
        {
            /* Set the Data Toggle bit as per the Flag */
            if (pdev->host.hc[ch_num].out_toggle == 0U)
            {
                /* Put the PID 0 */
                pdev->host.hc[ch_num].pid_type = PID_DATA0;
            }
            else
            {
                /* Put the PID 1 */
                pdev->host.hc[ch_num].pid_type = PID_DATA1;
            }
        }
        else
        {
            if (pdev->host.hc[ch_num].in_toggle == 0U)
            {
                pdev->host.hc[ch_num].pid_type = PID_DATA0;
            }
            else
            {
                pdev->host.hc[ch_num].pid_type = PID_DATA1;
            }
        }
        break;
    case EP_TYPE_INTR:
        if (direction == 0U)
        {
            /* Set the Data Toggle bit as per the Flag */
            if (pdev->host.hc[ch_num].out_toggle == 0U)
            {
                /* Put the PID 0 */
                pdev->host.hc[ch_num].pid_type = PID_DATA0;
            }
            else
            {
                /* Put the PID 1 */
                pdev->host.hc[ch_num].pid_type = PID_DATA1;
            }
        }
        else
        {
            if (pdev->host.hc[ch_num].in_toggle == 0U)
            {
                pdev->host.hc[ch_num].pid_type = PID_DATA0;
            }
            else
            {
                pdev->host.hc[ch_num].pid_type = PID_DATA1;
            }
        }
        break;
    case EP_TYPE_ISOC:
        pdev->host.hc[ch_num].pid_type = PID_DATA0;
        break;
    default:
        break;
    }

    pdev->host.hc[ch_num].xfer_buff = pbuff;
    pdev->host.hc[ch_num].xfer_len  = length;
    pdev->host.hc[ch_num].xfer_count = 0U;
    pdev->host.HC_Status[ch_num] = HOST_CH_IDLE; /* state */
    pdev->host.URB_State[ch_num] = HOST_CH_XFER_IDLE; /* urb state */

    return usb_hchtransbegin(&pdev->regs, ch_num, &pdev->host.hc[ch_num], pdev->basic_cfgs.dmaen);
}

static HOST_CH_XFER_STATE usb_hsot_get_ch_urbstate(usb_core_instance *pdev, uint8_t chnum)
{
    return pdev->host.URB_State[chnum];
}

static HOST_CH_STATUS usb_hsot_get_ch_state(usb_core_instance *pdev, uint8_t chnum)
{
    return pdev->host.HC_Status[chnum];
}

static uint32_t usb_hsot_get_ch_xfercount(usb_core_instance *pdev, uint8_t chnum)
{
    return pdev->host.hc[chnum].xfer_count;
}

static rt_err_t _usbh_reset_port(rt_uint8_t port)
{
    LOG_D("reset port");
    usb_hprtrst(&_hc32_usbh.regs);
    return RT_EOK;
}

static int _usbh_pipe_xfer(upipe_t pipe, rt_uint8_t token, void *buffer, int nbytes, int timeouts)
{
    int timeout = timeouts;
    uint8_t  devspeed;
    uint32_t u32NakCnt = 0;

    if (pipe->pipe_index >= USB_MAX_CH_NUM)
    {
        rt_kprintf("Error: pipe_index %d, Exceeded the max number of host channels\r\n", pipe->pipe_index);
        return -1;
    }

    while (1)
    {
        if (!connect_status)
        {
            return -1;
        }
        rt_completion_init(&urb_completion);
        usb_host_submitrequest(&_hc32_usbh,
                               pipe->pipe_index,
                               (pipe->ep.bEndpointAddress & 0x80) >> 7,
                               pipe->ep.bmAttributes,
                               token,
                               buffer,
                               nbytes,
                               0);
        if ((pipe->ep.bEndpointAddress & 0x80))
        {
            LOG_D("IN");
        }
        else
        {
            LOG_D("OUT");
        }

        rt_completion_wait(&urb_completion, timeout);
        rt_thread_mdelay(1);
        if (usb_hsot_get_ch_state(&_hc32_usbh, pipe->pipe_index) == HOST_CH_NAK)
        {
            LOG_D("nak");
#define  MAX_NAK_CNT    (5U)
            u32NakCnt ++;
            if (u32NakCnt > MAX_NAK_CNT)
            {
                return -1;
            }
            if (pipe->ep.bmAttributes == USB_EP_ATTR_INT)
            {
                rt_thread_delay((pipe->ep.bInterval * RT_TICK_PER_SECOND / 1000) > 0 ? (pipe->ep.bInterval * RT_TICK_PER_SECOND / 1000) : 1);
            }
            /* Get the speed of the connected device */
            devspeed = _hc32_usbh.host.devspeed;
            usb_hchstop(&_hc32_usbh.regs, pipe->pipe_index);
            usb_host_ch_init(&_hc32_usbh,
                             pipe->pipe_index,
                             pipe->ep.bEndpointAddress,
                             pipe->inst->address,
                             devspeed,
                             pipe->ep.bmAttributes,
                             pipe->ep.wMaxPacketSize);


            continue;
        }
        else if (usb_hsot_get_ch_state(&_hc32_usbh, pipe->pipe_index) == HOST_CH_STALL)
        {
            LOG_D("stall");
            pipe->status = UPIPE_STATUS_STALL;
            if (pipe->callback != RT_NULL)
            {
                pipe->callback(pipe);
            }
            return -1;
        }
        else if (usb_hsot_get_ch_urbstate(&_hc32_usbh, pipe->pipe_index) == HOST_CH_XFER_ERROR)
        {
            LOG_D("error");
            pipe->status = UPIPE_STATUS_ERROR;
            if (pipe->callback != RT_NULL)
            {
                pipe->callback(pipe);
            }
            return -1;
        }
        else if (HOST_CH_XFER_DONE == usb_hsot_get_ch_urbstate(&_hc32_usbh, pipe->pipe_index))
        {
            LOG_D("done");
            pipe->status = UPIPE_STATUS_OK;
            if (pipe->callback != RT_NULL)
            {
                pipe->callback(pipe);
            }
            size_t size = usb_hsot_get_ch_xfercount(&_hc32_usbh, pipe->pipe_index);
            if (pipe->ep.bEndpointAddress & 0x80)
            {
                return size;
            }
            return nbytes;
        }
        else
        {
            LOG_D("other");
        }

        continue;
    }
}



static rt_uint16_t pipe_index = 0;
static rt_uint8_t  _usbh_get_free_pipe_index(void)
{
    rt_uint8_t idx;
    for (idx = 0; idx < USB_MAX_CH_NUM; idx++)
    {
        if (!(pipe_index & (0x01 << idx)))
        {
            pipe_index |= (0x01 << idx);
            return idx;
        }
    }
    rt_kprintf("Error: Exceeded the max number of host channels\r\n");
    return USB_MAX_CH_NUM;
}

static void _usbh_free_pipe_index(rt_uint8_t index)
{
    pipe_index &= ~(0x01 << index);
}

static rt_err_t _usbh_open_pipe(upipe_t pipe)
{
    uint8_t  devspeed;
    pipe->pipe_index = _usbh_get_free_pipe_index();

    if (pipe->pipe_index >= USB_MAX_CH_NUM)
    {
        rt_kprintf("Error: pipe_index %d, Exceeded the max number of host channels\r\n", pipe->pipe_index);
        return -RT_ERROR;
    }

    /* Get the speed of the connected device */
    devspeed = _hc32_usbh.host.devspeed;

    usb_host_chopen(&_hc32_usbh,
                    pipe->pipe_index,
                    pipe->ep.bEndpointAddress,
                    pipe->inst->address,
                    devspeed,
                    pipe->ep.bmAttributes,
                    pipe->ep.wMaxPacketSize);
    /* Set DATA0 PID token*/
    if (_hc32_usbh.host.hc[pipe->pipe_index].is_epin)
    {
        _hc32_usbh.host.hc[pipe->pipe_index].in_toggle = 0;
    }
    else
    {
        _hc32_usbh.host.hc[pipe->pipe_index].out_toggle = 0;
    }
    return RT_EOK;
}

static rt_err_t _usbh_close_pipe(upipe_t pipe)
{
    if (pipe->pipe_index >= USB_MAX_CH_NUM)
    {
        rt_kprintf("Error: pipe_index %d, Exceeded the max number of host channels\r\n", pipe->pipe_index);
        return -RT_ERROR;
    }
    usb_hchstop(&_hc32_usbh.regs, pipe->pipe_index);
    _usbh_free_pipe_index(pipe->pipe_index);
    return RT_EOK;
}


static struct uhcd_ops _uhcd_ops =
{
    _usbh_reset_port,
    _usbh_pipe_xfer,
    _usbh_open_pipe,
    _usbh_close_pipe,
};

static void _usbh_driver_init(usb_core_instance *pdev, stc_usb_port_identify *pstcPortIdentify)
{
    uint8_t i;

    pdev->host.is_dev_connect = 0U;
    for (i = 0U; i < USB_MAX_TX_FIFOS; i++)
    {
        pdev->host.ErrCnt[i] = 0U;
        pdev->host.XferCnt[i] = 0U;
        pdev->host.HC_Status[i] = HOST_CH_IDLE;
    }
    pdev->host.hc[0].max_packet = 8U;

    usb_setregaddr(&pdev->regs, pstcPortIdentify, &pdev->basic_cfgs);

    usb_gintdis(&pdev->regs);
    usb_initusbcore(&pdev->regs, &pdev->basic_cfgs);
    /* force to work in host mode*/
    usb_modeset(&pdev->regs, HOST_MODE);
    /* configure charge pump IO */
    usb_bsp_cfgvbus(pdev);
    /* enable or disable the external charge pump */
    usb_bsp_drivevbus(pdev, 1U);
    usb_vbusctrl(&pdev->regs, 1U);
    /* Wait some time for power stable */
    usb_mdelay(100UL);

    usb_hostmodeinit(&pdev->regs, &pdev->basic_cfgs);
    usb_ginten(&pdev->regs);
}

static rt_err_t _usbh_init(rt_device_t device)
{
    stc_usb_port_identify stcPortIdentify;
    struct hc32_irq_config irq_config;
    usb_core_instance *hhcd = (usb_core_instance *)device->user_data;

    /* Fcg config */
#if !defined(BSP_USING_USBHS)
    FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_USBFS, ENABLE);
#else
    FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_USBHS, ENABLE);
#endif
    /* Parameters */
#if !defined(BSP_USING_USBHS)
    stcPortIdentify.u8CoreID = USBFS_CORE_ID;
#else
    stcPortIdentify.u8CoreID = USBHS_CORE_ID;
#endif
#if defined (HC32F4A0)
#if !defined(BSP_USING_USBHS_PHY_EXTERN)
    stcPortIdentify.u8PhyType = USBHS_PHY_EMBED;
#else
    stcPortIdentify.u8PhyType = USBHS_PHY_EXT;
#endif
#endif
    /* BSP Config */
    rt_hw_usb_board_init();
    /* Host driver init */
    _usbh_driver_init(hhcd, &stcPortIdentify);
    /* NVIC config */
    irq_config.irq_num = BSP_USB_GLB_IRQ_NUM;
#if !defined(BSP_USING_USBHS)
    irq_config.int_src = INT_SRC_USBFS_GLB;
#else
    irq_config.int_src = INT_SRC_USBHS_GLB;
#endif
    irq_config.irq_prio = BSP_USB_GLB_IRQ_PRIO;
    /* register interrupt */
    hc32_install_irq_handler(&irq_config,
                             usbh_irq_handler,
                             RT_TRUE);

    return RT_EOK;
}

int rt_hw_usbh_init(void)
{
    rt_err_t res = -RT_ERROR;

    uhcd_t uhcd = (uhcd_t)rt_malloc(sizeof(struct uhcd));
    if (uhcd == RT_NULL)
    {
        rt_kprintf("uhcd malloc failed\r\n");
        return -RT_ERROR;
    }

    rt_memset((void *)uhcd, 0, sizeof(struct uhcd));

    uhcd->parent.type = RT_Device_Class_USBHost;
    uhcd->parent.init = _usbh_init;
    uhcd->parent.user_data = &_hc32_usbh;

    uhcd->ops = &_uhcd_ops;
    uhcd->num_ports = USB_FS_PORT;
    _hc32_usbh.pData = uhcd;

    res = rt_device_register(&uhcd->parent, "usbh", RT_DEVICE_FLAG_DEACTIVATE);
    if (res != RT_EOK)
    {
        rt_kprintf("register usb host failed res = %d\r\n", res);
        return -RT_ERROR;
    }

    rt_usb_host_init("usbh");

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_usbh_init);



#endif /* BSP_USING_USBH */
