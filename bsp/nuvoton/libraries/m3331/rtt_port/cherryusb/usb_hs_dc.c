/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "NuMicro.h"
#include "usbd_core.h"
#include "nu_bitutil.h"

/* Defines / Macros ----------------------------------------------------------*/
#undef LOG_TAG
#define LOG_TAG "drv.usb.hs.dc"
#define DBG_TAG LOG_TAG
#include "drv_log.h"

/* Functions Implementation --------------------------------------------------*/
/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define EPADR_SW2HW(address)    ((address == 0) ? (CEP) : (USB_EP_GET_IDX(address) - 1))
#define EPADR_HW2SW(address)    (address + 1)
#define CEP_BUF_ADR             0
#define CEP_BUF_SIZE            64

/* Endpoint state */
struct usb_dc_ep_state
{
    uint16_t ep_mps;     /* Endpoint max packet size */
    uint8_t  ep_type;    /* Endpoint type */
    uint8_t  ep_stalled; /* Endpoint stall flag */
    uint8_t  ep_enable;  /* Endpoint enable */
    uint8_t  ep_addr;    /* Endpoint address */
    uint8_t *xfer_buf;
    uint32_t xfer_len;
    uint32_t actual_xfer_len;
    uint32_t mps_xfer_len;
};

/* Driver state */
struct usb_dc_config_priv
{
    struct usb_setup_packet setup_pkt;
    uint32_t epUsedBufSize;
    struct usb_dc_ep_state ep[HSUSBD_MAX_EP]; /*!< IN/OUT endpoint parameters*/
} ;

static volatile struct usb_dc_config_priv s_sUDC;

static const char *szGLOBAL[] =
{
    "USBIF",
    "CEPIF"
};

static const char *szUSBIF[] =
{
    "SOFIF",
    "RSTIF",
    "RESUMEIF",
    "SUSPENDIF",
    "HISPDIF",
    "DMADONEIF",
    "PHYCLKVLDIF",
    "BIT7-RESERVED",
    "VBUSDETIF",
    "BIT9-RESERVED"
};

static const char *szCEPIF[] =
{
    "SETUPTKIF",
    "SETUPPKIF",
    "OUTTKIF",
    "INTKIF",
    "PINGIF",
    "TXPKIF",
    "RXPKIF",
    "NAKIF",
    "STALLIF",
    "ERRIF",
    "STSDONEIF",
    "BUFFULLIF",
    "BUFEMPTYIF",
    "BIT9-RESERVED"
};

__STATIC_INLINE uint32_t HSUSBD_GetEpBufAddr(uint32_t u32HWEP)
{
    if (u32HWEP == CEP)
    {
        return HSUSBD->CEPBUFSTART;
    }

    return HSUSBD->EP[u32HWEP].EPBUFSTART;
}

__STATIC_INLINE uint32_t HSUSBD_GetEpBufAddrEnd(uint32_t u32HWEP)
{
    if (u32HWEP == CEP)
    {
        return HSUSBD->CEPBUFEND;
    }

    return HSUSBD->EP[u32HWEP].EPBUFEND;
}

__STATIC_INLINE uint32_t HSUSBD_GetEpDir(uint32_t u32HWEP)
{
    return HSUSBD->EP[u32HWEP].EPCFG & HSUSBD_EPCFG_EPDIR_Msk;
}

static void HSUSBD_DumpEpBufAddr(void)
{
    int i;

    USB_LOG_INFO("CEP@[%08X-%08X]\n", HSUSBD_GetEpBufAddr(CEP), HSUSBD_GetEpBufAddrEnd(CEP));
    for (i = 0; i < HSUSBD_MAX_EP; i++)
    {
        USB_LOG_INFO("EP%c@[%08X-%08X]\n", 'A' + i, HSUSBD_GetEpBufAddr(EPA + i), HSUSBD_GetEpBufAddrEnd(EPA + i));
    }
}

static uint32_t HSUSBD_NewEpBuf(int n)
{
#define DEF_HSUSBD_RAM_SIZE            HSUSBD_RAM_SIZE
#define DEF_HSUSBD_MAX_EP_BUF_SIZE     HSUSBD_MAX_EP_RAM_SIZE

    uint32_t u32Addr;

    if (((s_sUDC.epUsedBufSize + n) > DEF_HSUSBD_RAM_SIZE) || (n > DEF_HSUSBD_MAX_EP_BUF_SIZE))
        return 0;

    u32Addr = s_sUDC.epUsedBufSize;
    s_sUDC.epUsedBufSize += n;

    return u32Addr;
}

static const char *HSUSBD_PrintEpType(uint32_t u32HWType)
{
    switch (u32HWType)
    {
    case HSUSBD_EP_CFG_TYPE_BULK:
        return "BULK";
    case HSUSBD_EP_CFG_TYPE_INT:
        return "INT";
    case HSUSBD_EP_CFG_TYPE_ISO:
        return "ISO";
    default:
        return "UNK";
    }
}

__WEAK void usb_dc_low_level_init(void)
{
}

__WEAK void usb_dc_low_level_deinit(void)
{
}

int usbd_set_remote_wakeup(uint8_t busid)
{
    return -1;
}

int usb_dc_init(uint8_t busid)
{
    int i;
    int32_t i32TimeOutCnt = HSUSBD_TIMEOUT / 1000;

    memset((void *)&s_sUDC, 0, sizeof(s_sUDC));

    usb_dc_low_level_init();

    /*****************************************************/
    /* Initial USB engine */
    HSUSBD_ENABLE_PHY();
    /* wait PHY clock ready */
    while (!(HSUSBD->PHYCTL & HSUSBD_PHYCTL_PHYCLKSTB_Msk))
    {
        if (i32TimeOutCnt-- < 0)
        {
            break;
        }
    }

    HSUSBD->OPER &= ~HSUSBD_OPER_HISPDEN_Msk;   /* full-speed */

    /* Force SE0 */
    HSUSBD_SET_SE0();

    /* Configure USB controller */
    /* Enable USB BUS, CEP global interrupt */
    HSUSBD_ENABLE_USB_INT(HSUSBD_GINTEN_USBIEN_Msk
                          | HSUSBD_GINTEN_CEPIEN_Msk);

    /* Enable BUS interrupt */
    HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_RESUMEIEN_Msk
                          | HSUSBD_BUSINTEN_RSTIEN_Msk
                          | HSUSBD_BUSINTEN_VBUSDETIEN_Msk);

    /* USB start */
    HSUSBD_CLR_SE0();

    /* Enable interrupt */
    NVIC_EnableIRQ(HSUSBD_IRQn);

    HSUSBD_ENABLE_USB();

    return 0;
}

int usb_dc_deinit(uint8_t busid)
{
    HSUSBD_SET_ADDR(0);

    /* Force SE0 */
    HSUSBD_SET_SE0();

    HSUSBD_DISABLE_USB();

    /* Enable interrupt */
    NVIC_DisableIRQ(HSUSBD_IRQn);

    usb_dc_low_level_deinit();

    return 0;
}

static uint8_t g_address = 0;
int usbd_set_address(uint8_t busid, const uint8_t addr)
{
    USB_LOG_DBG("[%s]%d\n", __func__, addr);
    g_address = addr;
    //HSUSBD_SET_ADDR(addr);

    return 0;
}

uint8_t usbd_get_port_speed(uint8_t busid)
{
    if (HSUSBD->OPER & HSUSBD_OPER_CURSPD_Msk)
    {
        USB_LOG_DBG("[%s] HIGH\r\n", __func__);
        return USB_SPEED_HIGH;
    }

    USB_LOG_DBG("[%s] FULL\r\n", __func__);
    return USB_SPEED_FULL;
}

int usbd_ep_open(uint8_t busid, const struct usb_endpoint_descriptor *ep)
{
    uint8_t SWEP = USB_EP_GET_IDX(ep->bEndpointAddress);
    uint8_t HWEP = EPADR_SW2HW(SWEP);

    uint32_t u32MPS = USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize);

    if (SWEP)  // IN/OUT EPs
    {
        uint32_t u32EPType = USB_GET_ENDPOINT_TYPE(ep->bmAttributes);
        uint32_t u32HWEPType;

        switch (u32EPType)
        {
        case USB_ENDPOINT_TYPE_ISOCHRONOUS:
            u32HWEPType = HSUSBD_EP_CFG_TYPE_ISO;
            break;
        case USB_ENDPOINT_TYPE_BULK:
            u32HWEPType = HSUSBD_EP_CFG_TYPE_BULK;
            break;
        case USB_ENDPOINT_TYPE_INTERRUPT:
            u32HWEPType = HSUSBD_EP_CFG_TYPE_INT;
            break;
        default:
            return -1;
        }

        s_sUDC.ep[HWEP].ep_addr = ep->bEndpointAddress;
        s_sUDC.ep[HWEP].ep_mps = u32MPS;
        s_sUDC.ep[HWEP].ep_type = u32EPType;
        s_sUDC.ep[HWEP].ep_enable = true;

        HSUSBD_SetEpBufAddr(HWEP, HSUSBD_NewEpBuf(u32MPS), u32MPS);
        HSUSBD_SET_MAX_PAYLOAD(HWEP, u32MPS);

        if (USB_EP_DIR_IS_IN(ep->bEndpointAddress)) // IN
        {
            HSUSBD_ENABLE_EP_INT(HWEP, HSUSBD_EPINTEN_TXPKIEN_Msk);
            HSUSBD_ConfigEp(HWEP, SWEP, u32HWEPType, HSUSBD_EP_CFG_DIR_IN);
        }
        else //OUT
        {
            HSUSBD_ENABLE_EP_INT(HWEP, HSUSBD_EPINTEN_RXPKIEN_Msk | HSUSBD_EPINTEN_SHORTRXIEN_Msk | HSUSBD_EPINTEN_BUFFULLIEN_Msk);
            HSUSBD_ConfigEp(HWEP, SWEP, u32HWEPType, HSUSBD_EP_CFG_DIR_OUT);
        }

        HSUSBD->EP[HWEP].EPRSPCTL = (HSUSBD->EP[HWEP].EPRSPCTL & HSUSBD_EP_RSPCTL_MODE_MASK) | HSUSBD_EPRSPCTL_FLUSH_Msk;

        HSUSBD->GINTEN |= (0x1UL << (HSUSBD_GINTEN_EPAIEN_Pos + (HWEP - EPA)));

        USB_LOG_INFO("[%s]EpAddr:%02x-> SWEP:%d -> EP%c_Buf@[%08x - %08X], HWEPType:%s\n",
                     __func__,
                     s_sUDC.ep[HWEP].ep_addr,
                     SWEP,
                     'A' + HWEP,
                     HSUSBD_GetEpBufAddr(HWEP), HSUSBD_GetEpBufAddrEnd(HWEP),
                     HSUSBD_PrintEpType(u32HWEPType));

        //HSUSBD_DumpEpBufAddr();

    }
    else if (ep->bEndpointAddress == USB_CONTROL_IN_EP0)
    {
        USB_LOG_INFO("[%s]EP:%02x, SWEP:%d, CEP, MaxPktSize: %d\n", __func__, ep->bEndpointAddress, SWEP, u32MPS);

        /* Control endpoint */
        HSUSBD_SetEpBufAddr(CEP, HSUSBD_NewEpBuf(CEP_BUF_SIZE), CEP_BUF_SIZE);
        HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk
                              | HSUSBD_CEPINTEN_STSDONEIEN_Msk
                              | HSUSBD_CEPINTEN_TXPKIEN_Msk
                              | HSUSBD_CEPINTEN_RXPKIEN_Msk);
        HSUSBD_SET_ADDR(0);

        /* Clear all CEP-BUFEMPTYIF, BUFFULLIF, STSDONEIF, ERRIF, STALLIF, NAKIF, RXPKIF, TXPKIF,
        PINGIF, INTKIF, OUTTKIF flags, unless SETUPPKIF and SETUPTKIF flags. */
        HSUSBD_CLR_CEP_INT_FLAG(0x1ffc);
    }

    return 0;
}

int usbd_ep_close(uint8_t busid, const uint8_t ep)
{
    uint8_t SWEP = USB_EP_GET_IDX(ep);
    uint8_t HWEP = EPADR_SW2HW(SWEP);

    if (USB_EP_GET_IDX(ep))  // IN/OUT EPs
    {
        USB_LOG_DBG("[%s]EP:%02x-> SWEP:%d -> EP%c\n", __func__, ep, SWEP, 'A' + HWEP);
        HSUSBD->EP[HWEP].EPCFG &= ~HSUSBD_EP_CFG_VALID;
    }
    else //CEP
    {
        USB_LOG_DBG("[%s]EP:%02x-> SWEP:%d -> CEP\n", __func__, ep, SWEP);
    }

    return 0;
}

int usbd_ep_set_stall(uint8_t busid, const uint8_t ep)
{
    uint8_t SWEP = USB_EP_GET_IDX(ep);
    uint8_t HWEP = EPADR_SW2HW(SWEP);

    HSUSBD_SetEpStall(HWEP);

    return 0;
}

int usbd_ep_clear_stall(uint8_t busid, const uint8_t ep)
{
    uint8_t SWEP = USB_EP_GET_IDX(ep);
    uint8_t HWEP = EPADR_SW2HW(SWEP);

    HSUSBD_ClearEpStall(HWEP);

    return 0;
}

int usbd_ep_is_stalled(uint8_t busid, const uint8_t ep, uint8_t *stalled)
{
    uint8_t SWEP = USB_EP_GET_IDX(ep);
    uint8_t HWEP = EPADR_SW2HW(SWEP);

    *stalled = HSUSBD_GetEpStall(HWEP) > 0 ? 1 : 0;

    return 0;
}

static uint32_t usbd_ep_xfer(const uint8_t ep_addr, uint8_t *buffer, uint32_t size)
{
    uint32_t i, cnt;
    uint32_t *_buf_word;
    uint8_t  *_buf_byte;
    uint8_t SWEP = USB_EP_GET_IDX(ep_addr);
    uint8_t HWEP = EPADR_SW2HW(SWEP);

    _buf_word = (uint32_t *)buffer;
    cnt = size >> 2;
    _buf_byte = (uint8_t *)((uint8_t *)buffer + (cnt * 4));

    if (SWEP) //EPs
    {
        if (USB_EP_DIR_IS_IN(ep_addr)) //IN
        {
            for (i = 0; i < cnt; i++)
            {
                HSUSBD->EP[HWEP].EPDAT = _buf_word[i];
            }
            for (i = 0; i < (size & 0x3); i++)
            {
                HSUSBD->EP[HWEP].EPDAT_BYTE = _buf_byte[i];
            }

            HSUSBD->EP[HWEP].EPRSPCTL = HSUSBD_EP_RSPCTL_SHORTTXEN; // packet end
            HSUSBD->EP[HWEP].EPTXCNT = size;
        }
        else //OUT
        {
            for (i = 0; i < cnt; i++)
            {
                _buf_word[i] = HSUSBD->EP[HWEP].EPDAT;
            }
            for (i = 0; i < (size & 0x3); i++)
            {
                _buf_byte[i] = HSUSBD->EP[HWEP].EPDAT_BYTE;
            }
        }
    }
    else //CEP
    {
        if (USB_EP_DIR_IS_IN(ep_addr)) //IN
        {
            for (i = 0; i < cnt; i++)
            {
                HSUSBD->CEPDAT = _buf_word[i];
            }
            for (i = 0; i < (size & 0x3); i++)
            {
                HSUSBD->CEPDAT_BYTE = _buf_byte[i];
            }
        }
        else //OUT
        {
            for (i = 0; i < cnt; i++)
            {
                _buf_word[i] = HSUSBD->CEPDAT;
            }
            for (i = 0; i < (size & 0x3); i++)
            {
                _buf_byte[i] = HSUSBD->CEPDAT_BYTE;
            }
        }
    }

    return size;
}

int usbd_ep_start_write(uint8_t busid, const uint8_t ep, const uint8_t *data, uint32_t data_len)
{
    uint8_t SWEP = USB_EP_GET_IDX(ep);
    uint8_t HWEP = EPADR_SW2HW(SWEP);

    USB_LOG_DBG("[W] ep:%02x, %p, len: %d\n", ep, data, data_len);

    if (SWEP)  // IN EPs
    {
        if (!data && data_len)
        {
            return -1;
        }

        if (!s_sUDC.ep[HWEP].ep_enable)
        {
            return -2;
        }

        s_sUDC.ep[HWEP].xfer_buf = (uint8_t *)data;
        s_sUDC.ep[HWEP].xfer_len = data_len;
        s_sUDC.ep[HWEP].actual_xfer_len = 0;

        if (data_len > s_sUDC.ep[HWEP].ep_mps)
        {
            data_len = s_sUDC.ep[HWEP].ep_mps;
        }

        usbd_ep_xfer(ep, s_sUDC.ep[HWEP].xfer_buf, data_len);
    }
    else //CEP
    {
        if (data)
        {
            if (data_len > 0)
            {
                usbd_ep_xfer(ep, (uint8_t *)data, data_len);
                HSUSBD_START_CEP_IN(data_len);
            }
            else
            {
                /* Zero length */
                HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_ZEROLEN);
            }
        }
        else if (data_len == 0)
        {
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
        }
    }

    return 0;
}

int usbd_ep_start_read(uint8_t busid, const uint8_t ep, uint8_t *data, uint32_t data_len)
{
    uint8_t SWEP = USB_EP_GET_IDX(ep);
    uint8_t HWEP = EPADR_SW2HW(SWEP);

    USB_LOG_DBG("[R] ep:%02x, %p, len: %d\n", ep, data, data_len);

    if (SWEP)  // OUT EPs
    {
        if (!s_sUDC.ep[HWEP].ep_enable)
        {
            return -2;
        }

        s_sUDC.ep[HWEP].xfer_buf = (uint8_t *)data;
        s_sUDC.ep[HWEP].xfer_len = data_len;
        s_sUDC.ep[HWEP].actual_xfer_len = 0;

        if (s_sUDC.ep[HWEP].xfer_len < s_sUDC.ep[HWEP].ep_mps)
        {
            s_sUDC.ep[HWEP].mps_xfer_len = s_sUDC.ep[HWEP].xfer_len;
        }
        else
        {
            s_sUDC.ep[HWEP].mps_xfer_len = s_sUDC.ep[HWEP].ep_mps;
        }
    }
    else //CEP
    {
        if (data_len)
        {
            usbd_ep_xfer(ep, data, data_len);
        }
        else
        {
        }
    }

    return 0;
}

static void dump_isr_event(uint32_t idx, const char *Str[], uint32_t u32PoolSize)
{
    if (idx < u32PoolSize)
    {
        if ((szGLOBAL == Str) && (idx >= 2))
        {
            USB_LOG_DBG("[%d]GLOBAL-EP%cIF\r\n", rt_tick_get(), 'A' + idx - 2);
        }
        else
        {
            USB_LOG_DBG("[%d]%s-%s(#%d)\r\n",
                        rt_tick_get(),
                        (Str == szGLOBAL) ? "GLOBAL" : \
                        ((Str == szUSBIF) ? "  USBIF" : "  CEPIF"), \
                        Str[idx],
                        idx);
        }
    }
}

typedef void (*usbif_isr_func)(uint8_t busid);

static void BUS_ISR_SOFIF(uint8_t busid)
{
    /* This bit indicates when a start-of-frame packet has been received */
    HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_SOFIF_Msk);
}

static void BUS_ISR_RSTIF(uint8_t busid)
{
    /* When set, this bit indicates that either the USB root port reset is end. */

    /* Reset DMA engine */
    HSUSBD_ResetDMA();
    s_sUDC.epUsedBufSize = 0;
    /* Set DMA engine, Flush All EPs Buffer. */
    //int i;
    //for (i = 0; i < HSUSBD_MAX_EP; i++)
    //{
    //    HSUSBD->EP[i].EPRSPCTL = HSUSBD_EPRSPCTL_FLUSH_Msk;
    //}
    usbd_event_reset_handler(busid);
    HSUSBD_ENABLE_USB();

    HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_RSTIF_Msk);
}

static void BUS_ISR_RESUMEIF(uint8_t busid)
{
    /* Resume Interrupt */
    /* When set, this bit indicates that a device resume has occurred. */

    /* Enable USBIF - RST, SUSPEND interrupts. */
    HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_RESUMEIF_Msk);
    HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_RSTIEN_Msk | HSUSBD_BUSINTEN_SUSPENDIEN_Msk);

    /* Call CherryUSB resume callback. */
    usbd_event_resume_handler(busid);
}

static void BUS_ISR_SUSPENDIF(uint8_t busid)
{
    /* Suspend Request Interrupt */
    /* This bit is set as default and it has to be cleared by writing ????before the USB reset.
       This bit is also set when a USB Suspend request is detected from the host.  */

    /* Enable USBIF - RST, RESUME, SUSPEND interrupts. */
    HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_RSTIEN_Msk |
                          HSUSBD_BUSINTEN_RESUMEIEN_Msk);
    HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_SUSPENDIF_Msk);

    /* Call CherryUSB suspend callback. */
    usbd_event_suspend_handler(busid);
}

static void BUS_ISR_HISPDIF(uint8_t busid)
{
    /* High-speed Settle Interrupt */
    /*
    0 = No valid high-speed reset protocol is detected.
    1 = Valid high-speed reset protocol is over and the device has settled in high-speed.
    */
    HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_HISPDIF_Msk);
}

static void BUS_ISR_DMADONEIF(uint8_t busid)
{
    /* DMA Completion Interrupt */
    HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_DMADONEIF_Msk);
}

static void BUS_ISR_PHYCLKVLDIF(uint8_t busid)
{
    /* Usable Clock Interrupt */
    HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_PHYCLKVLDIF_Msk);
}

static void BUS_ISR_VBUSDETIF(uint8_t busid)
{
    /* VBUS Detection Interrupt */
    /*  0 = No VBUS is plug-in.
        1 = VBUS is plug-in.  */
    HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_VBUSDETIF_Msk);

    /* Check cable connect status. */
    if (HSUSBD_IS_ATTACHED())
    {
        /* USB Plug In */
        USB_LOG_INFO("USB Plug In!!\r\n");

        HSUSBD->OPER = HSUSBD_OPER_HISPDEN_Msk;   /* high-speed */
        HSUSBD_CLR_SE0();
        HSUSBD->OPER |= HSUSBD_OPER_HISHSEN_Msk;  /* Start high speed handshake*/

        usbd_event_connect_handler(busid);
    }
    else
    {
        /* USB Un-plug */
        USB_LOG_INFO("USB Un-plug!!\r\n");

        HSUSBD_DISABLE_USB();
        usbd_event_disconnect_handler(busid);
    }
}

static void CEP_ISR_SETUPTKIF(uint8_t busid)
{
    HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_SETUPTKIF_Msk);

    /*
    Setup Token Interrupt
    0 = Not a Setup token is received.
    1 = A Setup token is received. Writing 1 clears this status bit
    */
}

static void CEP_ISR_SETUPPKIF(uint8_t busid)
{
    /*
    This bit must be cleared (by writing 1) before the next setup packet can be received. If the bit is not cleared, then the successive setup packets will be overwritten in the setup packet buffer.
    0 = Not a Setup packet has been received from the host.
    1 = A Setup packet has been received from the host.
    */
    s_sUDC.setup_pkt.bmRequestType  = (uint8_t)(HSUSBD->SETUP1_0);
    s_sUDC.setup_pkt.bRequest       = (uint8_t)(HSUSBD->SETUP1_0 >> 8);
    s_sUDC.setup_pkt.wValue         = (uint16_t)(HSUSBD->SETUP3_2);
    s_sUDC.setup_pkt.wIndex         = (uint16_t)(HSUSBD->SETUP5_4);
    s_sUDC.setup_pkt.wLength        = (uint16_t)(HSUSBD->SETUP7_6);

    HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_SETUPPKIF_Msk);

    usbd_event_ep0_setup_complete_handler(busid, (uint8_t *)&s_sUDC.setup_pkt);
}

static void CEP_ISR_OUTTKIF(uint8_t busid)
{
    /*
    0 = The control-endpoint does not receive an OUT token from the host.
    1 = The control-endpoint receives an OUT token from the host.
    */
    HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_OUTTKIF_Msk);
}

static void CEP_ISR_INTKIF(uint8_t busid)
{
    /*
    0 = The control-endpoint does not receive an IN token from the host.
    1 = The control-endpoint receives an IN token from the host.
    */
    HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
}

static void CEP_ISR_PINGIF(uint8_t busid)
{
    /*
    0 = The control-endpoint does not receive a ping token from the host.
    1 = The control-endpoint receives a ping token from the host.
    */
    HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_PINGIF_Msk);
}

static void CEP_ISR_TXPKIF(uint8_t busid)
{
    /*
    Data Packet Transmitted Interrupt
    0 = Not a data packet is successfully transmitted to the host in response to an IN-token and an ACK-token is received for the same.
    1 = A data packet is successfully transmitted to the host in response to an IN-token and an ACK-token is received for the same.
    */
    HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);

    usbd_event_ep_in_complete_handler(busid, USB_CONTROL_IN_EP0, HSUSBD->CEPTXCNT);

    HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_TXPKIF_Msk);
}

static void CEP_ISR_RXPKIF(uint8_t busid)
{
    /*
    Data Packet Received Interrupt
    0 = Not a data packet is successfully received from the host for an OUT-token and an ACK is sent to the host.
    1 = A data packet is successfully received from the host for an OUT-token and an ACK is sent to the host.
    */
    //HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);

    usbd_event_ep_out_complete_handler(busid, USB_CONTROL_OUT_EP0, HSUSBD->CEPRXCNT);

    HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_RXPKIF_Msk);
}

static void CEP_ISR_NAKIF(uint8_t busid)
{
    /*
    NAK Sent Interrupt
    0 = Not a NAK-token is sent in response to an IN/OUT token.
    1 = A NAK-token is sent in response to an IN/OUT token.
    */
    HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_NAKIF_Msk);
}

static void CEP_ISR_STALLIF(uint8_t busid)
{
    /*
    Stall Sent Interrupt
    0 = Not a stall-token is sent in response to an IN/OUT token.
    1 = A stall-token is sent in response to an IN/OUT token.
    */
    HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STALLIF_Msk);
}

static void CEP_ISR_ERRIF(uint8_t busid)
{
    /*
    USB Error Interrupt
    0 = No error had occurred during the transaction.
    1 = An error had occurred during the transaction.
    */
    HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_ERRIF_Msk);
}

static void CEP_ISR_STSDONEIF(uint8_t busid)
{
    if ((g_address > 0) && (HSUSBD_GET_ADDR() == 0))
    {
        HSUSBD_SET_ADDR(g_address);
    }

    /*
    Status Completion Interrupt
    0 = Not a USB transaction has completed successfully.
    1 = The status stage of a USB transaction has completed successfully.
    */
    HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
}

static void CEP_ISR_BUFFULLIF(uint8_t busid)
{
    /*
    Buffer Full Interrupt
    0 = The control-endpoint buffer is not full.
    1 = The control-endpoint buffer is full.
    */
    HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_BUFFULLIF_Msk);
}

static void CEP_ISR_BUFEMPTYIF(uint8_t busid)
{
    /*
    Buffer Empty Interrupt
    0 = The control-endpoint buffer is not empty.
    1 = The control-endpoint buffer is empty.
    */
    HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_BUFEMPTYIF_Msk);
}

static void process_busif(uint8_t busid)
{
    static const usbif_isr_func isr_cb[] =
    {
        BUS_ISR_SOFIF,
        BUS_ISR_RSTIF,
        BUS_ISR_RESUMEIF,
        BUS_ISR_SUSPENDIF,
        BUS_ISR_HISPDIF,
        BUS_ISR_DMADONEIF,
        BUS_ISR_PHYCLKVLDIF,
        NULL,
        BUS_ISR_VBUSDETIF
    };
    __IO rt_uint32_t IrqSt = HSUSBD->BUSINTSTS & HSUSBD->BUSINTEN;
    int i;

    // Find first set.
    while ((i = nu_ctz(IrqSt)) < (sizeof(isr_cb) / sizeof(usbif_isr_func)))
    {
        uint32_t u32BitMask = (1 << i);

        dump_isr_event(i, szUSBIF, sizeof(szUSBIF) / sizeof(char *));

        if (isr_cb[i] != NULL)
            isr_cb[i](busid);

        IrqSt &= ~u32BitMask;
    }
}

static void process_cepif(uint8_t busid)
{
    static const usbif_isr_func isr_cb[] =
    {
        CEP_ISR_SETUPTKIF,
        CEP_ISR_SETUPPKIF,
        CEP_ISR_OUTTKIF,
        CEP_ISR_INTKIF,
        CEP_ISR_PINGIF,
        CEP_ISR_TXPKIF,
        CEP_ISR_RXPKIF,
        CEP_ISR_NAKIF,
        CEP_ISR_STALLIF,
        CEP_ISR_ERRIF,
        CEP_ISR_STSDONEIF,
        CEP_ISR_BUFFULLIF,
        CEP_ISR_BUFEMPTYIF
    };
    __IO rt_uint32_t IrqSt = HSUSBD->CEPINTSTS & HSUSBD->CEPINTEN;
    int i;

    // Find first set.
    while ((i = nu_ctz(IrqSt)) < (sizeof(isr_cb) / sizeof(usbif_isr_func)))
    {
        uint32_t u32BitMask = (1 << i);

        dump_isr_event(i, szCEPIF, sizeof(szCEPIF) / sizeof(char *));

        if (isr_cb[i] != NULL)
            isr_cb[i](busid);

        IrqSt &= ~u32BitMask;
    }
}

static void process_epxif(uint8_t busid)
{
    /* Service EP events */
    uint32_t HWEP, u32EpIntSts;

    u32EpIntSts = ((HSUSBD->GINTSTS & HSUSBD->GINTEN) >> HSUSBD_GINTSTS_EPAIF_Pos) & ((1 << HSUSBD_MAX_EP) - 1);
    while ((HWEP = nu_ctz(u32EpIntSts)) < HSUSBD_MAX_EP)
    {
        uint32_t u32BitMask = (1 << HWEP);
        uint8_t SWEP = EPADR_HW2SW(HWEP);

        uint32_t IrqSt = HSUSBD->EP[HWEP].EPINTSTS & HSUSBD->EP[HWEP].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(HWEP, IrqSt);

        if (HSUSBD_GetEpDir(HWEP) == HSUSBD_EP_CFG_DIR_IN)  // IN ep
        {
            if (s_sUDC.ep[HWEP].xfer_len > s_sUDC.ep[HWEP].ep_mps)
            {
                s_sUDC.ep[HWEP].xfer_buf += s_sUDC.ep[HWEP].ep_mps;
                s_sUDC.ep[HWEP].xfer_len -= s_sUDC.ep[HWEP].ep_mps;
                s_sUDC.ep[HWEP].actual_xfer_len += s_sUDC.ep[HWEP].ep_mps;

                uint16_t min_len = MIN(s_sUDC.ep[HWEP].xfer_len, s_sUDC.ep[HWEP].ep_mps);

                usbd_ep_xfer(s_sUDC.ep[HWEP].ep_addr, s_sUDC.ep[HWEP].xfer_buf, min_len);

            }
            else
            {
                s_sUDC.ep[HWEP].actual_xfer_len += s_sUDC.ep[HWEP].xfer_len;
                s_sUDC.ep[HWEP].xfer_len = 0;

                usbd_event_ep_in_complete_handler(busid, SWEP | 0x80, s_sUDC.ep[HWEP].actual_xfer_len);
            }
        }
        else // OUT
        {
            uint32_t u32Len = HSUSBD->EP[HWEP].EPDATCNT & 0xFFFFUL;

            usbd_ep_xfer(s_sUDC.ep[HWEP].ep_addr, s_sUDC.ep[HWEP].xfer_buf, u32Len);

            s_sUDC.ep[HWEP].xfer_buf += u32Len;
            s_sUDC.ep[HWEP].xfer_len -= u32Len;
            s_sUDC.ep[HWEP].actual_xfer_len += u32Len;

            if ((u32Len < s_sUDC.ep[HWEP].ep_mps) ||
                    (s_sUDC.ep[HWEP].xfer_len == 0))
            {
                usbd_event_ep_out_complete_handler(busid, SWEP, s_sUDC.ep[HWEP].actual_xfer_len);
            }
            else
            {
                if (s_sUDC.ep[HWEP].xfer_len < s_sUDC.ep[HWEP].ep_mps)
                {
                    s_sUDC.ep[HWEP].mps_xfer_len = s_sUDC.ep[HWEP].xfer_len;
                }
                else
                {
                    s_sUDC.ep[HWEP].mps_xfer_len = s_sUDC.ep[HWEP].ep_mps;
                }
            }
        }

        u32EpIntSts &= ~u32BitMask;
    }

}

void CherryUSB_USBD_IRQHandler(uint8_t busid)
{
    __IO rt_uint32_t IrqSt = HSUSBD->GINTSTS & HSUSBD->GINTEN;
    if (IrqSt)
    {
        int i;

        // Find first set.
        while ((i = nu_ctz(IrqSt)) != 32)
        {
            uint32_t u32BitMask = (1 << i);

            dump_isr_event(i, szGLOBAL, 2 + HSUSBD_MAX_EP);

            switch (u32BitMask)
            {
            case HSUSBD_GINTSTS_USBIF_Msk:
                process_busif(busid);
                break;

            case HSUSBD_GINTSTS_CEPIF_Msk:
                process_cepif(busid);
                break;

            default: /* EP interrups */
                process_epxif(busid);
                break;
            }

            IrqSt &= ~u32BitMask;
        }
    }
}
