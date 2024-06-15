/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-14     CDT          first version
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtthread.h>
#include <rtdevice.h>

#if defined(BSP_USING_USBD)

//#define DRV_DEBUG
#define LOG_TAG             "drv.usbd"
#include <drv_log.h>

#include "board_config.h"
#include "irq_config.h"
#include "drv_usbd.h"

extern rt_err_t rt_hw_usb_board_init(void);
extern void rt_hw_us_delay(rt_uint32_t us);

static usb_core_instance _hc32_usbd;
static struct udcd _hc32_udc;


static struct ep_id _ep_pool[] =
{
    {0x0,  USB_EP_ATTR_CONTROL,     USB_DIR_INOUT,  64, ID_ASSIGNED  },
    {0x1,  USB_EP_ATTR_BULK,        USB_DIR_IN,     64, ID_UNASSIGNED},
    {0x1,  USB_EP_ATTR_BULK,        USB_DIR_OUT,    64, ID_UNASSIGNED},
    {0x2,  USB_EP_ATTR_BULK,        USB_DIR_IN,     64, ID_UNASSIGNED},
    {0x2,  USB_EP_ATTR_BULK,        USB_DIR_OUT,    64, ID_UNASSIGNED},
    {0x3,  USB_EP_ATTR_BULK,        USB_DIR_IN,     64, ID_UNASSIGNED},
    {0x3,  USB_EP_ATTR_BULK,        USB_DIR_OUT,    64, ID_UNASSIGNED},
    {0x4,  USB_EP_ATTR_INT,         USB_DIR_IN,     64, ID_UNASSIGNED},
    {0x4,  USB_EP_ATTR_INT,         USB_DIR_OUT,    64, ID_UNASSIGNED},
    {0x5,  USB_EP_ATTR_ISOC,        USB_DIR_IN,     64, ID_UNASSIGNED},
    {0x5,  USB_EP_ATTR_ISOC,        USB_DIR_OUT,    64, ID_UNASSIGNED},
#if defined (HC32F4A0)
    {0x6,  USB_EP_ATTR_BULK,        USB_DIR_IN,     64, ID_UNASSIGNED},
    {0x6,  USB_EP_ATTR_BULK,        USB_DIR_OUT,    64, ID_UNASSIGNED},
    {0x7,  USB_EP_ATTR_BULK,        USB_DIR_IN,     64, ID_UNASSIGNED},
    {0x7,  USB_EP_ATTR_BULK,        USB_DIR_OUT,    64, ID_UNASSIGNED},
    {0x8,  USB_EP_ATTR_BULK,        USB_DIR_IN,     64, ID_UNASSIGNED},
    {0x8,  USB_EP_ATTR_BULK,        USB_DIR_OUT,    64, ID_UNASSIGNED},
    {0x9,  USB_EP_ATTR_BULK,        USB_DIR_IN,     64, ID_UNASSIGNED},
    {0x9,  USB_EP_ATTR_BULK,        USB_DIR_OUT,    64, ID_UNASSIGNED},
    {0xA,  USB_EP_ATTR_BULK,        USB_DIR_IN,     64, ID_UNASSIGNED},
    {0xA,  USB_EP_ATTR_BULK,        USB_DIR_OUT,    64, ID_UNASSIGNED},
    {0xB,  USB_EP_ATTR_INT,         USB_DIR_IN,     64, ID_UNASSIGNED},
    {0xB,  USB_EP_ATTR_INT,         USB_DIR_OUT,    64, ID_UNASSIGNED},
    {0xC,  USB_EP_ATTR_INT,         USB_DIR_IN,     64, ID_UNASSIGNED},
    {0xC,  USB_EP_ATTR_INT,         USB_DIR_OUT,    64, ID_UNASSIGNED},
    {0xD,  USB_EP_ATTR_INT,         USB_DIR_IN,     64, ID_UNASSIGNED},
    {0xD,  USB_EP_ATTR_INT,         USB_DIR_OUT,    64, ID_UNASSIGNED},
    {0xE,  USB_EP_ATTR_ISOC,        USB_DIR_IN,     64, ID_UNASSIGNED},
    {0xE,  USB_EP_ATTR_ISOC,        USB_DIR_OUT,    64, ID_UNASSIGNED},
    {0xF,  USB_EP_ATTR_ISOC,        USB_DIR_IN,     64, ID_UNASSIGNED},
    {0xF,  USB_EP_ATTR_ISOC,        USB_DIR_OUT,    64, ID_UNASSIGNED},
#endif
    {0xFF, USB_EP_ATTR_TYPE_MASK,   USB_DIR_MASK,   0,  ID_ASSIGNED  },
};

void usb_udelay(const uint32_t usec)
{
    rt_hw_us_delay(usec);
}

void usb_mdelay(const uint32_t msec)
{
    rt_thread_mdelay(msec);
}

static void usb_opendevep(usb_core_instance *pdev, uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_type)
{
    USB_DEV_EP *ep;
    __IO uint8_t tmp_1, tmp_2;

    tmp_1 = ep_addr >> 7;     /* EP type, it is IN(=1) or OUT(=0) */
    tmp_2 = ep_addr & 0x7FU;  /* EP number */
    if (tmp_1 == 1U)
    {
        ep = &pdev->dev.in_ep[tmp_2];
    }
    else
    {
        ep = &pdev->dev.out_ep[tmp_2];
    }

    ep->epidx  = tmp_2;

    ep->ep_dir = tmp_1;
    ep->maxpacket = ep_mps;
    ep->trans_type = ep_type;
    if (tmp_1 == 1U)
    {
        /* Assign a Tx FIFO */
        ep->tx_fifo_num = tmp_2;
    }
    /* Set initial data PID. */
    if (ep_type == EP_TYPE_BULK)
    {
        ep->data_pid_start = 0U;
    }
    usb_epactive(&pdev->regs, ep);
}

static void usb_shutdevep(usb_core_instance *pdev, uint8_t  ep_addr)
{
    USB_DEV_EP *ep;
    __IO uint8_t tmp_1, tmp_2;

    tmp_1 = ep_addr >> 7;     /* EP type, it is IN(=1) or OUT(=0) */
    tmp_2 = ep_addr & 0x7FU;   /* EP number */
    if (tmp_1 == 1U)
    {
        ep = &pdev->dev.in_ep[tmp_2];
    }
    else
    {
        ep = &pdev->dev.out_ep[tmp_2];
    }
    ep->epidx  = tmp_2;
    ep->ep_dir = tmp_1;
    usb_epdeactive(&pdev->regs, ep);
}

static void usb_readytorx(usb_core_instance *pdev, uint8_t ep_addr, uint8_t *pbuf, uint16_t buf_len)
{
    USB_DEV_EP *ep;
    __IO uint8_t tmp_1;

    tmp_1 = ep_addr & 0x7FU;   /* EP number */
    ep = &pdev->dev.out_ep[tmp_1];
    /* setup and start the Xfer */
    ep->xfer_buff = pbuf;
    ep->xfer_len = (uint32_t)buf_len;
    ep->xfer_count = 0UL;
    ep->ep_dir = 0U;
    ep->epidx = tmp_1;

    if (pdev->basic_cfgs.dmaen == 1U)
    {
        ep->dma_addr = (uint32_t)pbuf;
    }

    if (tmp_1 == 0U)
    {
        usb_ep0transbegin(&pdev->regs, ep, pdev->basic_cfgs.dmaen);
    }
    else
    {
        usb_epntransbegin(&pdev->regs, ep, pdev->basic_cfgs.dmaen);
    }
}

static void usb_deveptx(usb_core_instance *pdev, uint8_t ep_addr, uint8_t *pbuf, uint32_t buf_len)
{
    USB_DEV_EP *ep;
    __IO uint8_t tmp_1;

    tmp_1 = ep_addr & 0x7FU;   /* EP number */
    ep = &pdev->dev.in_ep[tmp_1];

    /* Setup and start the Transfer */
    ep->ep_dir = 1U;
    ep->epidx = tmp_1;
    ep->xfer_buff = pbuf;
    ep->dma_addr = (uint32_t)pbuf;
    ep->xfer_count = 0UL;
    ep->xfer_len  = buf_len;

    if (tmp_1 == 0U)
    {
        usb_ep0transbegin(&pdev->regs, ep, pdev->basic_cfgs.dmaen);
    }
    else
    {
        usb_epntransbegin(&pdev->regs, ep, pdev->basic_cfgs.dmaen);
    }
}

static void usb_stalldevep(usb_core_instance *pdev, uint8_t epnum)
{
    USB_DEV_EP *ep;
    __IO uint8_t tmp_1, tmp_2;

    tmp_1 = epnum >> 7;     /* EP type, it is IN(=1) or OUT(=0) */
    tmp_2 = epnum & 0x7FU;  /* EP number */

    if (tmp_1 != 0U)
    {
        ep = &pdev->dev.in_ep[tmp_2];
    }
    else
    {
        ep = &pdev->dev.out_ep[tmp_2];
    }

    ep->ep_stall = 1U;
    ep->epidx    = tmp_2;
    if (tmp_1 != 0U)
    {
        ep->ep_dir = 1U;
    }
    else
    {
        ep->ep_dir = 0U;
    }

    usb_setepstall(&pdev->regs, ep);
}

static void usb_clrstall(usb_core_instance *pdev, uint8_t epnum)
{
    USB_DEV_EP *ep;
    __IO uint8_t tmp_1, tmp_2;

    tmp_1 = epnum >> 7;     /* EP type, it is IN(=1) or OUT(=0) */
    tmp_2 = epnum & 0x7FU;  /* EP number */
    if (tmp_1 != 0U)
    {
        ep = &pdev->dev.in_ep[tmp_2];
    }
    else
    {
        ep = &pdev->dev.out_ep[tmp_2];
    }

    ep->ep_stall = 0U;
    ep->epidx    = tmp_2;
    if (tmp_1 != 0U)
    {
        ep->ep_dir = 1U;
    }
    else
    {
        ep->ep_dir = 0U;
    }

    usb_clearepstall(&pdev->regs, ep);
}

static void usb_dev_rst(usb_core_instance *pdev)
{
    usb_opendevep(pdev, 0x00U, USB_MAX_EP0_SIZE, EP_TYPE_CTRL);
    usb_opendevep(pdev, 0x80U, USB_MAX_EP0_SIZE, EP_TYPE_CTRL);
    rt_usbd_reset_handler(&_hc32_udc);
    LOG_D("USB Reset");
}

static void usb_ctrlconn(usb_core_instance *pdev, uint8_t conn)
{
    __IO uint8_t tmp_1;
    tmp_1 = conn;
    if (tmp_1 != 0U)
    {
        rt_usbd_connect_handler(&_hc32_udc);
        LOG_D("USB Connect");
    }
    else
    {
        rt_usbd_disconnect_handler(&_hc32_udc);
        LOG_D("USB Disconnect");
    }
}

static void usb_dev_susp(usb_core_instance *pdev)
{
    LOG_D("USB Suspend");
}

static void usb_dev_resume(usb_core_instance *pdev)
{
    LOG_D("USB Resume");
}

static void usb_sof_process(usb_core_instance *pdev)
{
    rt_usbd_sof_handler(&_hc32_udc);
}

static void usb_setup_process(usb_core_instance *pdev)
{
    rt_usbd_ep0_setup_handler(&_hc32_udc, (struct urequest *)pdev->dev.setup_pkt_buf);
}

static void usb_dataout_process(usb_core_instance *pdev, uint8_t epnum)
{
    if (epnum != 0)
    {
        rt_usbd_ep_out_handler(&_hc32_udc, epnum, pdev->dev.out_ep[epnum].xfer_count);
    }
    else
    {
        rt_usbd_ep0_out_handler(&_hc32_udc,  pdev->dev.out_ep[0].xfer_count);
    }
}

static void usb_datain_process(usb_core_instance *pdev, uint8_t epnum)
{
    if (epnum == 0)
    {
        rt_usbd_ep0_in_handler(&_hc32_udc);
    }
    else
    {
        rt_usbd_ep_in_handler(&_hc32_udc, 0x80 | epnum, pdev->dev.in_ep[epnum].xfer_count);
    }
}

static void usb_isoinincomplt_process(usb_core_instance *pdev)
{
    /* reserved */
}

static void usb_isooutincomplt_process(usb_core_instance *pdev)
{
    /* reserved */
}

static usb_dev_int_cbk_typedef dev_int_cbk =
{
    &usb_dev_rst,
    &usb_ctrlconn,
    &usb_dev_susp,
    &usb_dev_resume,
    &usb_sof_process,
    &usb_setup_process,
    &usb_dataout_process,
    &usb_datain_process,
    &usb_isoinincomplt_process,
    &usb_isooutincomplt_process
};

static usb_dev_int_cbk_typedef  *dev_int_cbkpr = &dev_int_cbk;

static uint32_t usb_rddevinep(usb_core_instance *pdev, uint8_t epnum)
{
    uint32_t u32diepmsk;
    uint32_t u32diepempmsk;
    u32diepmsk = READ_REG32(pdev->regs.DREGS->DIEPMSK);
    u32diepempmsk = READ_REG32(pdev->regs.DREGS->DIEPEMPMSK);
    u32diepmsk |= (((u32diepempmsk >> epnum) & 0x1UL) << 7U);
    return (READ_REG32(pdev->regs.INEP_REGS[epnum]->DIEPINT) & u32diepmsk);
}

static void usb_wrblanktxfifo(usb_core_instance *pdev, uint32_t epnum)
{
    USB_DEV_EP *ep;
    uint32_t u32Len;
    uint32_t u32Len32b;
    uint16_t u16spclen;
    uint32_t u32diepempmsk;

    ep  = &pdev->dev.in_ep[epnum];
    u32Len = ep->xfer_len - ep->xfer_count;
    if (u32Len > ep->maxpacket)
    {
        u32Len = ep->maxpacket;
    }
    u32Len32b = (u32Len + 3UL) >> 2;
    u16spclen = usb_rdineptxfspcavail(pdev, epnum);
    while ((u16spclen >= u32Len32b) && (ep->xfer_count < ep->xfer_len))
    {
        u32Len = ep->xfer_len - ep->xfer_count;

        if (u32Len > ep->maxpacket)
        {
            u32Len = ep->maxpacket;
        }
        u32Len32b = (u32Len + 3UL) >> 2;
        usb_wrpkt(&pdev->regs, ep->xfer_buff, (uint8_t)epnum, (uint16_t)u32Len, pdev->basic_cfgs.dmaen);
        ep->xfer_buff  += u32Len;
        ep->xfer_count += u32Len;
        u16spclen = usb_rdineptxfspcavail(pdev, epnum);
    }

    if (u32Len == 0UL)
    {
        u32diepempmsk = 0x01UL << epnum;
        CLR_REG32_BIT(pdev->regs.DREGS->DIEPEMPMSK, u32diepempmsk);
    }
}

#ifdef VBUS_SENSING_ENABLED
static void usb_sessionrequest_isr(usb_core_instance *pdev)
{
    dev_int_cbkpr->devctrlconnect(pdev, 1U);

    WRITE_REG32(pdev->regs.GREGS->GINTSTS, USBFS_GINTSTS_VBUSVINT);

    if (0U != pdev->basic_cfgs.low_power)
    {
        CLR_REG32_BIT(*pdev->regs.GCCTL, USBFS_GCCTL_STPPCLK | USBFS_GCCTL_GATEHCLK);
    }
}
#endif

static void usb_resume_isr(usb_core_instance *pdev)
{
    if (0U != pdev->basic_cfgs.low_power)
    {
        CLR_REG32_BIT(*pdev->regs.GCCTL, USBFS_GCCTL_STPPCLK | USBFS_GCCTL_GATEHCLK);
    }

    CLR_REG32_BIT(pdev->regs.DREGS->DCTL, USBFS_DCTL_RWUSIG);

    dev_int_cbkpr->Resume(pdev);

    WRITE_REG32(pdev->regs.GREGS->GINTSTS, USBFS_GINTSTS_WKUINT);
}

static void usb_susp_isr(usb_core_instance *pdev)
{
    uint32_t u32dsts;

    u32dsts = READ_REG32(pdev->regs.DREGS->DSTS);
    if ((u32dsts & 1UL) != 0UL)
    {
        dev_int_cbkpr->Suspend(pdev);
    }
    WRITE_REG32(pdev->regs.GREGS->GINTSTS, USBFS_GINTSTS_USBSUSP);
}

static void usb_inep_isr(usb_core_instance *pdev)
{
    uint32_t u32diepint;
    uint32_t u32EpIntr;
    uint8_t u8epnum;
    uint32_t u32diepempmsk;

    u32EpIntr = usb_getalliepintr(&pdev->regs);
    u8epnum = 0U;
    while ((0U != u32EpIntr) && (u8epnum < USB_MAX_TX_FIFOS))
    {
        if ((u32EpIntr & 0x1UL) != 0UL)
        {
            u32diepint = usb_rddevinep(pdev, u8epnum);
            if ((u32diepint & XFER_COMPL) != 0UL)
            {
                u32diepempmsk = 1UL << u8epnum;
                CLR_REG32_BIT(pdev->regs.DREGS->DIEPEMPMSK, u32diepempmsk);
                WRITE_REG32(pdev->regs.INEP_REGS[u8epnum]->DIEPINT, XFER_COMPL);
                dev_int_cbkpr->DataInStage(pdev, u8epnum);
                if (pdev->basic_cfgs.dmaen == 1U)
                {
                    if ((pdev->dev.device_state == USB_EP0_STATUS_IN) && (u8epnum == 0U))
                    {
                        pdev->dev.out_ep[0].xfer_len = 64U;
                        pdev->dev.out_ep[0].rem_data_len = 64U;
                        pdev->dev.out_ep[0].total_data_len = 64U;
                        usb_ep0revcfg(&pdev->regs, pdev->basic_cfgs.dmaen, pdev->dev.setup_pkt_buf);
                        pdev->dev.device_state = USB_EP0_IDLE;
                    }
                }
            }
            if ((u32diepint & EPDISABLED) != 0UL)
            {
                WRITE_REG32(pdev->regs.INEP_REGS[u8epnum]->DIEPINT, EPDISABLED);
            }
            if ((u32diepint & TIME_OUT) != 0UL)
            {
                WRITE_REG32(pdev->regs.INEP_REGS[u8epnum]->DIEPINT, TIME_OUT);
            }
            if ((u32diepint & INTKNTXFEMP) != 0UL)
            {
                WRITE_REG32(pdev->regs.INEP_REGS[u8epnum]->DIEPINT, INTKNTXFEMP);
            }
            if ((u32diepint & INEPNAKEFF) != 0UL)
            {
                WRITE_REG32(pdev->regs.INEP_REGS[u8epnum]->DIEPINT, INEPNAKEFF);
            }
            if ((u32diepint & TXFEMP) != 0UL)
            {
                usb_wrblanktxfifo(pdev, u8epnum);
                WRITE_REG32(pdev->regs.INEP_REGS[u8epnum]->DIEPINT, TXFEMP);
            }
        }
        u8epnum++;
        u32EpIntr >>= 1U;
    }
}

static void usb_outep_isr(usb_core_instance *pdev)
{
    uint32_t u32EpIntr;
    uint32_t u32doepint;
    uint8_t u8epnum = 0U;
    uint32_t u8Xfer;
    uint32_t u32ReadEpSize;

    u32EpIntr = usb_getalloepintr(&pdev->regs);
    while ((u32EpIntr != 0UL) && (u8epnum < USB_MAX_TX_FIFOS))
    {
        if ((u32EpIntr & 0x1UL) != 0UL)
        {
            u32doepint = usb_getoepintbit(&pdev->regs, u8epnum);
            if ((u32doepint & XFER_COMPL) != 0UL)
            {
                WRITE_REG32(pdev->regs.OUTEP_REGS[u8epnum]->DOEPINT, XFER_COMPL);
                if (pdev->basic_cfgs.dmaen == 1U)
                {
                    u32ReadEpSize = (READ_REG32(pdev->regs.OUTEP_REGS[u8epnum]->DOEPTSIZ) & USBFS_DOEPTSIZ_XFRSIZ);
                    u8Xfer = LL_MIN(pdev->dev.out_ep[u8epnum].maxpacket, pdev->dev.out_ep[u8epnum].xfer_len);
                    pdev->dev.out_ep[u8epnum].xfer_count = u8Xfer - u32ReadEpSize;
                    if (u8epnum != 0U)
                    {
                        pdev->dev.out_ep[u8epnum].xfer_count = pdev->dev.out_ep[u8epnum].xfer_len - u32ReadEpSize;
                    }
                }
                dev_int_cbkpr->DataOutStage(pdev, u8epnum);
                if (pdev->basic_cfgs.dmaen == 1U)
                {
                    if ((pdev->dev.device_state == USB_EP0_STATUS_OUT) && (u8epnum == 0U))
                    {
                        pdev->dev.out_ep[0].xfer_len       = 64U;
                        pdev->dev.out_ep[0].rem_data_len   = 64U;
                        pdev->dev.out_ep[0].total_data_len = 64U;
                        usb_ep0revcfg(&pdev->regs, pdev->basic_cfgs.dmaen, pdev->dev.setup_pkt_buf);
                        pdev->dev.device_state = USB_EP0_IDLE;
                    }
                }
            }
            if ((u32doepint & EPDISABLED) != 0UL)
            {
                WRITE_REG32(pdev->regs.OUTEP_REGS[u8epnum]->DOEPINT, EPDISABLED);
            }
            if (u8epnum == 0U)
            {
                u32doepint = usb_getoepintbit(&pdev->regs, u8epnum);
                if ((u32doepint & SETUP_BIT) != 0UL)
                {
                    dev_int_cbkpr->SetupStage(pdev);
                    WRITE_REG32(pdev->regs.OUTEP_REGS[u8epnum]->DOEPINT, SETUP_BIT);
                }
            }
        }
        u8epnum++;
        u32EpIntr >>= 1U;
    }
}

static void usb_sof_isr(usb_core_instance *pdev)
{
    dev_int_cbkpr->SOF(pdev);
    WRITE_REG32(pdev->regs.GREGS->GINTSTS, USBFS_GINTSTS_SOF);
}

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
    switch (u8PktStatus)
    {
    case STS_DATA_UPDT:
        if (0U != u16ByteCnt)
        {
            usb_rdpkt(&pdev->regs, ep->xfer_buff, u16ByteCnt);
            ep->xfer_buff += u16ByteCnt;
            ep->xfer_count += u16ByteCnt;
        }
        else
        {
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

static void usb_reset_isr(usb_core_instance *pdev)
{
    uint32_t i;

    CLR_REG32_BIT(pdev->regs.DREGS->DCTL, USBFS_DCTL_RWUSIG);
    usb_txfifoflush(&pdev->regs, 0UL);
    for (i = 0UL; i < pdev->basic_cfgs.dev_epnum ; i++)
    {
        WRITE_REG32(pdev->regs.INEP_REGS[i]->DIEPINT, 0xFFUL);
        WRITE_REG32(pdev->regs.OUTEP_REGS[i]->DOEPINT, 0xFFUL);
    }
    WRITE_REG32(pdev->regs.DREGS->DAINT, 0xFFFFFFFFUL);
    WRITE_REG32(pdev->regs.DREGS->DAINTMSK, 1UL | (1UL << USBFS_DAINTMSK_OEPINTM_POS));

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

static void usb_enumfinish_isr(usb_core_instance *pdev)
{
    usb_ep0activate(&pdev->regs);
    usb_setaroundtim(pdev);
    WRITE_REG32(pdev->regs.GREGS->GINTSTS, USBFS_GINTSTS_ENUMDNE);
}

static void usb_isoinincomplt_isr(usb_core_instance *pdev)
{
    dev_int_cbkpr->IsoINIncomplete(pdev);
    WRITE_REG32(pdev->regs.GREGS->GINTSTS, USBFS_GINTSTS_IISOIXFR);
}

static void usb_isooutincomplt_isr(usb_core_instance *pdev)
{
    dev_int_cbkpr->IsoOUTIncomplete(pdev);
    WRITE_REG32(pdev->regs.GREGS->GINTSTS, USBFS_GINTSTS_IPXFR_INCOMPISOOUT);
}

static void usb_isr_handler(usb_core_instance *pdev)
{
    uint32_t u32gintsts;

    if (0U == usb_getcurmod(&pdev->regs))
    {
        u32gintsts = usb_getcoreintr(&pdev->regs);
        if (u32gintsts == 0UL)
        {
            return;
        }
        if ((u32gintsts & OUTEP_INT) != 0UL)
        {
            usb_outep_isr(pdev);
        }
        if ((u32gintsts & INEP_INT) != 0UL)
        {
            usb_inep_isr(pdev);
        }
        if ((u32gintsts & MODEMIS_INT) != 0UL)
        {
            WRITE_REG32(pdev->regs.GREGS->GINTSTS, MODEMIS_INT);
        }
        if ((u32gintsts & WAKEUP_INT) != 0UL)
        {
            usb_resume_isr(pdev);
        }
        if ((u32gintsts & USBSUSP_INT) != 0UL)
        {
            usb_susp_isr(pdev);
        }
        if ((u32gintsts & SOF_INT) != 0UL)
        {
            usb_sof_isr(pdev);
        }
        if ((u32gintsts & RXFLVL_INT) != 0UL)
        {
            usb_rxstsqlvl_isr(pdev);
        }
        if ((u32gintsts & USBRST_INT) != 0UL)
        {
            usb_reset_isr(pdev);
        }
        if ((u32gintsts & ENUMDONE_INT) != 0UL)
        {
            usb_enumfinish_isr(pdev);
        }
        if ((u32gintsts & INCOMPLSOIN) != 0UL)
        {
            usb_isoinincomplt_isr(pdev);
        }
        if ((u32gintsts & INCOMPLSOOUT) != 0UL)
        {
            usb_isooutincomplt_isr(pdev);
        }
#ifdef VBUS_SENSING_ENABLED
        if ((u32gintsts & VBUSV_INT) != 0UL)
        {
            usb_sessionrequest_isr(pdev);
        }
#endif
    }
}

static void usbd_irq_handler(void)
{
    rt_interrupt_enter();
    usb_isr_handler(&_hc32_usbd);
    rt_interrupt_leave();
}

static rt_err_t _usbd_ep_set_stall(rt_uint8_t address)
{
    usb_stalldevep(&_hc32_usbd, address);
    return RT_EOK;
}

static rt_err_t _usbd_ep_clear_stall(rt_uint8_t address)
{
    usb_clrstall(&_hc32_usbd, address);
    return RT_EOK;
}

static rt_err_t _usbd_set_address(rt_uint8_t address)
{
    usb_devaddrset(&_hc32_usbd.regs, address);
    return RT_EOK;
}

static rt_err_t _usbd_set_config(rt_uint8_t address)
{
    return RT_EOK;
}

static rt_err_t _usbd_ep_enable(uep_t ep)
{
    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);
    usb_opendevep(&_hc32_usbd, ep->ep_desc->bEndpointAddress,
                  ep->ep_desc->wMaxPacketSize, ep->ep_desc->bmAttributes);
    return RT_EOK;
}

static rt_err_t _usbd_ep_disable(uep_t ep)
{
    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);
    usb_shutdevep(&_hc32_usbd, ep->ep_desc->bEndpointAddress);
    return RT_EOK;
}

static rt_size_t _usbd_ep_read(rt_uint8_t address, void *buffer)
{
    rt_size_t size = 0;
    RT_ASSERT(buffer != RT_NULL);
    return size;
}

static rt_size_t _usbd_ep_read_prepare(rt_uint8_t address, void *buffer, rt_size_t size)
{
    usb_readytorx(&_hc32_usbd, address, buffer, size);
    return size;
}

static rt_size_t _usbd_ep_write(rt_uint8_t address, void *buffer, rt_size_t size)
{
    usb_deveptx(&_hc32_usbd, address, buffer, size);
    return size;
}

static rt_err_t _usbd_ep0_send_status(void)
{
    usb_deveptx(&_hc32_usbd, 0x00, NULL, 0);
    return RT_EOK;
}

static rt_err_t _usbd_suspend(void)
{
    return RT_EOK;
}

static rt_err_t _usbd_wakeup(void)
{
    return RT_EOK;
}

static rt_err_t _usbd_init(rt_device_t device)
{
    usb_core_instance *pdev;
    stc_usb_port_identify stcPortIdentify;
    struct hc32_irq_config irq_config;

    pdev = (usb_core_instance *)device->user_data;
    rt_hw_usb_board_init();
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
    usb_setregaddr(&pdev->regs, &stcPortIdentify, &pdev->basic_cfgs);

    usb_gintdis(&pdev->regs);
    /*Init the Core (common init.) */
    usb_initusbcore(&pdev->regs, &pdev->basic_cfgs);
    /* Force Device Mode*/
    usb_modeset(&pdev->regs, DEVICE_MODE);
    /* Init Device */
    usb_devmodeinit(&pdev->regs, &pdev->basic_cfgs);
    /* Enable USB Global interrupt */
    usb_ginten(&pdev->regs);
    /* NVIC Config */
    irq_config.irq_num = BSP_USB_GLB_IRQ_NUM;
#if !defined(BSP_USING_USBHS)
    irq_config.int_src = INT_SRC_USBFS_GLB;
#else
    irq_config.int_src = INT_SRC_USBHS_GLB;
#endif
    irq_config.irq_prio = BSP_USB_GLB_IRQ_PRIO;
    /* register interrupt */
    hc32_install_irq_handler(&irq_config,
                             usbd_irq_handler,
                             RT_TRUE);
    return RT_EOK;
}

const static struct udcd_ops _udc_ops =
{
    _usbd_set_address,
    _usbd_set_config,
    _usbd_ep_set_stall,
    _usbd_ep_clear_stall,
    _usbd_ep_enable,
    _usbd_ep_disable,
    _usbd_ep_read_prepare,
    _usbd_ep_read,
    _usbd_ep_write,
    _usbd_ep0_send_status,
    _usbd_suspend,
    _usbd_wakeup,
};

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops _ops =
{
    _usbd_init,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
};
#endif

int rt_hw_usbd_init(void)
{
    rt_memset((void *)&_hc32_udc, 0, sizeof(struct udcd));
    _hc32_udc.parent.type = RT_Device_Class_USBDevice;
#ifdef RT_USING_DEVICE_OPS
    _hc32_udc.parent.ops = &_ops;
#else
    _hc32_udc.parent.init = _usbd_init;
#endif
    _hc32_udc.parent.user_data = &_hc32_usbd;
    _hc32_udc.ops = &_udc_ops;
    /* Register endpoint infomation */
    _hc32_udc.ep_pool = _ep_pool;
    _hc32_udc.ep0.id = &_ep_pool[0];
#ifdef BSP_USBD_SPEED_HS
    _hc32_udc.device_is_hs = RT_TRUE;
#endif
    rt_device_register((rt_device_t)&_hc32_udc, "usbd", 0);
    rt_usb_device_init();
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_usbd_init);

#endif /* BSP_USING_USBD */
