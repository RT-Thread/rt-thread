/**
    *****************************************************************************
    * @file     cmem7_usb.c
    *
    * @brief    CMEM7 USB source file
    *
    *
    * @version  V1.0
    * @date     3. September 2013
    *
    * @note
    *
    *****************************************************************************
    * @attention
    *
    * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
    * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
    * TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
    * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
    * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
    * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
    *
    * <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
    *****************************************************************************
    */

#include "cmem7_usb.h"

static void USB_SET_REG_HPRT(const USB_REG_HPRT *clr, const USB_REG_HPRT *set)
{
    USB_REG_HPRT hprt;
    hprt.HPRT = USB->__HPRT;                    // @0x41300440
    hprt.HPRT_b.POC = hprt.HPRT_b.PEDC = hprt.HPRT_b.PE = hprt.HPRT_b.PCD = 0;
    if (clr)
        hprt.HPRT &= (~clr->HPRT);
    if (set)
        hprt.HPRT |= (set->HPRT);
    USB->__HPRT = hprt.HPRT;
}

void USB_coreInit(uint32_t type)
{
    USB->GINTEN = 0;
    USB->GINTSTS = ~0;
    GLOBAL_CTRL->USB_PHY_CTRL_b.CKISEL = 0;     // Crystal
    // core initialization
    // choose PHY and soft reset
    USB->GUSBCFG_b.PHY_IF = 0;                  // 60MHz, 8bit
    USB->GUSBCFG_b.ULPI_UTMI_SEL = 0;           // UTMI
    USB->GUSBCFG_b.PHY_SEL = 0;                 // USB 2.0 HS UTMI+
    USB->GRSTCTL_b.CORE_SOFT_RST = 1;
    while (USB->GRSTCTL_b.CORE_SOFT_RST == 1) ;
    while (USB->GRSTCTL_b.AHB_IDLE == 0) ;

    USB->GAHBCFG_b.DMA_EN = 1;
    USB->GAHBCFG_b.GLBL_INTR_EN = 1;
    USB->GAHBCFG_b.BST_LEN = 0x1;               // INCR

    USB->GINTEN_b.RFNE = FALSE;

    USB->GUSBCFG_b.USB_TRD_TIM = 0x9;           // 8-bit UTMI+
    USB->GUSBCFG_b.SRP_CAP = (type & 0x10) ? 1 : 0;
    USB->GUSBCFG_b.HNP_CAP = (type & 0x20) ? 1 : 0;
    if (type & 0x1) {
        USB->GUSBCFG_b.FORCE_HOST_MODE = 1;
        USB->GUSBCFG_b.FORCE_DEVICE_MODE = 0;
    } else if (type & 0x2) {
        USB->GUSBCFG_b.FORCE_DEVICE_MODE = 1;
        USB->GUSBCFG_b.FORCE_HOST_MODE = 0;
    }
    udelay(50000);
}

void USB_EnableInt(BOOL enable)
{
    USB->GAHBCFG_b.GLBL_INTR_EN = enable;
}

void USB_FlushFIFO(uint32_t num)
{
    if (num < 0x10) {
        USB->GRSTCTL_b.TX_FIFO_FLUSH_NUM = num;
        USB->GRSTCTL_b.TX_FIFO_FLUSH = 1;
        while (USB->GRSTCTL_b.TX_FIFO_FLUSH);
    } else if (num > 0x10) {
        USB->GRSTCTL_b.RX_FIFO_FLUSH = 1;
        while (USB->GRSTCTL_b.RX_FIFO_FLUSH);
    } else {
        USB->GRSTCTL_b.TX_FIFO_FLUSH_NUM = 0;
        USB->GRSTCTL_b.TX_FIFO_ALL = 1;
        USB->GRSTCTL_b.TX_FIFO_FLUSH = 1;
        while (USB->GRSTCTL_b.TX_FIFO_FLUSH);
    }
}

BOOL USB_ogtIsBdevID()
{
    return USB->GOTGCTL_b.CON_ID_STS ? TRUE : FALSE;
}

BOOL USB_hostVBus(uint32_t opt)
{
    if (opt & 0x2) {
        USB_REG_HPRT hprt;
        hprt.HPRT = 0;
        hprt.HPRT_b.PP = 1;
        if (opt & 0x1)
            USB_SET_REG_HPRT(NULL, &hprt);
        else
            USB_SET_REG_HPRT(&hprt, NULL);
    }
    return USB->__HPRT_b.PP ? TRUE : FALSE;
}

void USB_hostInit()
{
    USB_REG_HPRT hprt;
    // HOST MODE
    USB->HCFG_b.FS_LS_PCS = 0x0;                // PHY clock is running at 30/60 MHz
    USB->HCFG_b.FS_LS_SUPPORT = 0x0;            // HS/FS/LS
    USB->HCFG_b.EN_SG_DMA = 0x1;                // Enable Scatter/Gather DMA
    hprt.HPRT = 0;
    hprt.HPRT_b.PP = 1;
    USB_SET_REG_HPRT(NULL, &hprt);
}

void USB_HostResetPort(BOOL rst)
{
    USB_REG_HPRT hprt;
    hprt.HPRT = 0;
    hprt.HPRT_b.PRESET = 1;
    if (rst)
        USB_SET_REG_HPRT(NULL, &hprt);
    else
        USB_SET_REG_HPRT(&hprt, NULL);
}

uint16_t USB_HostGetCurFrame()
{
    return USB->HFNUM_b.FN;
}

void USB_HostSuspendPort()
{
    USB_REG_HPRT hprt;
    hprt.HPRT = 0;
    hprt.HPRT_b.PS = 1;
    USB_SET_REG_HPRT(NULL, &hprt);
}

USB_ENUM_SPEED USB_hostGetEnumSpd()
{
    return (USB_ENUM_SPEED)USB->__HPRT_b.SPEED;
}

BOOL USB_hostPrtConn()
{
    return USB->__HPRT_b.PCS ? TRUE : FALSE;
}

void USB_hostCH0(uint32_t devaddr, OTG_DESCRIPTOR *desc, uint32_t ctd, uint32_t ntd, BOOL ping, uint32_t pid, uint32_t mps, uint32_t epnum, BOOL in, USB_EP_TYPE eptype, USB_ENUM_SPEED speed)
{
    USB->HCDMA0_b.ADDR = SET_HCDMA_DESC_ADDR(desc);
    USB->HCDMA0_b.CTD = ctd;
    USB->HCTSIZ0_b.PING = ping ? 1 : 0;
    USB->HCTSIZ0_b.NTD = ntd;
    USB->HCTSIZ0_b.PID = pid;
    USB->HCC0_b.MPS = mps;
    USB->HCC0_b.EP_NUM = epnum;
    USB->HCC0_b.EP_DIR = in ? 1 : 0;
    USB->HCC0_b.LSD = (USB_ENUM_SPEED_LS == speed) ? 1 : 0;
    USB->HCC0_b.EP_TYPE = eptype;
    USB->HCC0_b.EC = 0;
    USB->HCC0_b.DA = devaddr;
    USB->HCC0_b.CE = 1;
}

void USB_hostCH1(uint32_t devaddr, OTG_DESCRIPTOR *desc, uint32_t ctd, uint32_t ntd, BOOL ping, uint32_t pid, uint32_t mps, uint32_t epnum, BOOL in, USB_EP_TYPE eptype, USB_ENUM_SPEED speed)
{
    USB->HCDMA1_b.ADDR = SET_HCDMA_DESC_ADDR(desc);
    USB->HCDMA1_b.CTD = ctd;
    USB->HCTSIZ1_b.PING = ping ? 1 : 0;
    USB->HCTSIZ1_b.NTD = ntd;
    USB->HCTSIZ1_b.PID = pid;
    USB->HCC1_b.MPS = mps;
    USB->HCC1_b.EP_NUM = epnum;
    USB->HCC1_b.EP_DIR = in ? 1 : 0;
    USB->HCC1_b.LSD = (USB_ENUM_SPEED_LS == speed) ? 1 : 0;
    USB->HCC1_b.EP_TYPE = eptype;
    USB->HCC1_b.EC = 0;
    USB->HCC1_b.DA = devaddr;
    USB->HCC1_b.CE = 1;
}

void USB_hostCH2(uint32_t devaddr, OTG_DESCRIPTOR *desc, uint32_t ctd, uint32_t ntd, BOOL ping, uint32_t pid, uint32_t mps, uint32_t epnum, BOOL in, USB_EP_TYPE eptype, USB_ENUM_SPEED speed)
{
    USB->HCDMA2_b.ADDR = SET_HCDMA_DESC_ADDR(desc);
    USB->HCDMA2_b.CTD = ctd;
    USB->HCTSIZ2_b.PING = ping ? 1 : 0;
    USB->HCTSIZ2_b.NTD = ntd;
    USB->HCTSIZ2_b.PID = pid;
    USB->HCC2_b.MPS = mps;
    USB->HCC2_b.EP_NUM = epnum;
    USB->HCC2_b.EP_DIR = in ? 1 : 0;
    USB->HCC2_b.LSD = (USB_ENUM_SPEED_LS == speed) ? 1 : 0;
    USB->HCC2_b.EP_TYPE = eptype;
    USB->HCC2_b.EC = 0;
    USB->HCC2_b.DA = devaddr;
    USB->HCC2_b.CE = 1;
}

int USB_hostCHn(uint32_t ch, uint32_t devaddr, OTG_DESCRIPTOR *desc, uint32_t ctd, uint32_t ntd, BOOL ping, uint32_t pid, uint32_t mps, uint32_t epnum, BOOL in, USB_EP_TYPE eptype, USB_ENUM_SPEED speed)
{
    USB_Type *USBn = (USB_Type *)(((char *)USB) + (ch * 0x20));

    if (ch > 15)
        return -1;
    USBn->HCDMA0_b.ADDR = SET_HCDMA_DESC_ADDR(desc);
    USBn->HCDMA0_b.CTD = ctd;
    USBn->HCTSIZ0_b.PING = ping ? 1 : 0;
    USBn->HCTSIZ0_b.NTD = ntd;
    USBn->HCTSIZ0_b.PID = pid;
    USBn->HCC0_b.MPS = mps;
    USBn->HCC0_b.EP_NUM = epnum;
    USBn->HCC0_b.EP_DIR = in ? 1 : 0;
    USBn->HCC0_b.LSD = (USB_ENUM_SPEED_LS == speed) ? 1 : 0;
    USBn->HCC0_b.EP_TYPE = eptype;
    USBn->HCC0_b.EC = 0;
    USBn->HCC0_b.DA = devaddr;
    USBn->HCC0_b.CE = 1;
    return 0;
}

int USB_hostCHnHalt(uint32_t ch)
{
    uint32_t hcchar;
    USB_Type *USBn = (USB_Type *)(((char *)USB) + (ch * 0x20));

    if (ch > 15)
        return -1;
    hcchar = USBn->HCC0;
    hcchar |= (0x3 << 30);
    USBn->HCC0 = hcchar;
    return 0;
}

BOOL USB_hostPortDisable(BOOL dis)
{
    if (dis) {
        USB_REG_HPRT hprt;
        hprt.HPRT = 0;
        hprt.HPRT_b.PE = 1;
        USB_SET_REG_HPRT(&hprt, NULL);
    }
    return USB->__HPRT_b.PE ? FALSE : TRUE;
}

BOOL USB_roleIsHost()
{
    return USB->GINTSTS_b.CUR_MOD ? TRUE : FALSE;
}

void USB_hostINT_enConn(BOOL en)
{
    USB->GINTEN_b.HP = en;
}

BOOL USB_hostINT_isConn()
{
    return USB->GINTSTS_b.HP ? TRUE : FALSE;
}

BOOL USB_hostINT_isPCD()
{
    return USB->__HPRT_b.PCD ? TRUE : FALSE;
}

void USB_hostINT_clrPCD()
{
    USB_REG_HPRT hprt;
    hprt.HPRT = 0;
    hprt.HPRT_b.PCD = 1;
    USB_SET_REG_HPRT(NULL, &hprt);
}

BOOL USB_hostINT_isPEDC()
{
    return USB->__HPRT_b.PEDC ? TRUE : FALSE;
}

void USB_hostINT_clrPEDC()
{
    USB_REG_HPRT hprt;
    hprt.HPRT = 0;
    hprt.HPRT_b.PEDC = 1;
    USB_SET_REG_HPRT(NULL, &hprt);
}

int USB_hostINT_enDone(uint32_t ch, BOOL en)
{
    USB_Type *USBn = (USB_Type *)(((char *)USB) + (ch * 0x20));

    if (ch > 15)
        return -1;

    if (en) {
        USB->GINTEN_b.HC = 1;
        USB->HAINT_EN_b.EN |= BIT(ch);
    } else
        USB->HAINT_EN_b.EN &= ~BIT(ch);

    USBn->HCINT_EN0_b.TC = USBn->HCINT_EN0_b.CH_HALT = USBn->HCINT_EN0_b.BNA = en ? 1 : 0;
    return 0;
}

uint32_t USB_hostINT_isDone(uint32_t ch)
{
    uint32_t retval = 0;

    if (ch > 15)
        return 0;

    if ((USB->GINTSTS_b.HC) && ((USB->HAINT & BIT(ch)))) {
        USB_Type *USBn = (USB_Type *)(((char *)USB) + (ch * 0x20));
        if (USBn->HCINT0_b.TC) {
            USBn->HCINT0 = BIT(0);
            retval |= 0x1;
        }
        if (USBn->HCINT0_b.BNA) {
            USBn->HCINT0 = BIT(11);
            retval |= 0x2;
        }
        if (USBn->HCINT0_b.CH_HALT) {
            USBn->HCINT0 = BIT(1);
            retval |= 0x4;
        }
        if (USBn->HCINT0_b.ETE) {
            USBn->HCINT0 = BIT(12);
            retval |= 0x8;
        }
    }
    return retval;
}

uint32_t USB_hostINT_isPend(uint32_t ch)
{
    uint32_t retval = 0;

    if (ch > 15)
        return 0;

    if ((USB->GINTSTS_b.HC) && ((USB->HAINT & BIT(ch)))) {
        USB_Type *USBn = (USB_Type *)(((char *)USB) + (ch * 0x20));
        retval = USBn->HCINT0;
        USBn->HCINT0 = retval;
    }
    return retval;
}

void USB_devInit()
{
    // If still has some int needed to be enable
    USB->GINTEN_b.MODE_MIS = TRUE;
    USB->GINTEN_b.OTG_INT = TRUE;

    // DEVICE MODE
    USB->GINTEN_b.RFNE = FALSE;                 // REG_CS(0x018/*GINTMSK*/, BIT(5)/*NPTxFEmpMsk*/ | BIT(4)/*RxFLvlMsk*/, 0);
    USB->GINTEN_b.NPTFE = FALSE;
    USB->DCFG_b.DSPEED = 0;                     // HS DEV
    USB->DCFG_b.NZLSOH = 0;                     // REG_CS(0x800/*DCFG*/, BIT(2)/*NZStsOUTHShk*/ | BIT(1) | BIT(0)/*DevSpd: HS*/, BIT(23)/*DescDMA*/ | BIT(13)/*EnDevOutNak*/);
    USB->DCFG_b.EN_SG_DMA = 1;
    USB->DCFG_b.EDON = 1;
    USB->DCTL_b.SD = 0;
}

USB_ENUM_SPEED USB_devGetEnumSpd()
{
    return (USB_ENUM_SPEED)USB->DSTS_b.SPEED;
}

void USB_devSetAddress(uint32_t addr)
{
    USB->DCFG_b.DEVICE_ADDR = addr;
}

void USB_devEP0out(uint32_t size, uint32_t pktcnt, uint32_t stpcnt, void *desc, BOOL snoop)
{
    USB->DOEPTSIZ0_b.SIZE = size;
    USB->DOEPTSIZ0_b.PACKET_CNT = pktcnt;
    USB->DOEPTSIZ0_b.SETUP_CNT = stpcnt;
    USB->DOEPDMA0 = (uint32_t)(desc);
    USB->DOEPCTL0_b.SNOOP = snoop;
    USB->DOEPCTL0_b.CNAK = 1;
    USB->DOEPCTL0_b.EPE = 1;                    // REG_CS(0xB00/*DOEPCTL0*/, 0, BIT(31)/*EPEna*/);
}

BOOL USB_devEP0in(uint32_t size, uint32_t pktcnt, void *desc, uint32_t mps/*8,16,32,64-byte*/)
{
    switch (mps) {
        case 64:    mps = 0x0; break;
        case 32:    mps = 0x1; break;
        case 16:    mps = 0x2; break;
        case 8:     mps = 0x3; break;
        default:    return FALSE;
    }
    USB->DIEPTSIZ0_b.SIZE = size;
    USB->DIEPTSIZ0_b.PACKET_CNT = pktcnt;
    USB->DIEPDMA0 = (uint32_t)(desc);
    USB->DIEPCTL0_b.MPS = mps;
    USB->DIEPCTL0_b.TX_FIFO_NUM = 0;
    USB->DIEPCTL0_b.CNAK = 1;
    USB->DIEPCTL0_b.EPE = 1;                    // REG_CS(0xB00/*DOEPCTL0*/, 0, BIT(31)/*EPEna*/);
    return TRUE;
}

void USB_devActEP1(const BOOL in, const uint32_t mps, USB_EP_TYPE type)
{
    if (in) {
        USB->DIEPCTL1_b.MPS = mps;
        USB->DIEPCTL1_b.EP_TYPE = type;
        USB->DIEPCTL1_b.UAE = (mps != 0) ? 1 : 0;
    } else {
        USB->DOEPCTL1_b.MPS = mps;
        USB->DOEPCTL1_b.EP_TYPE = type;
        USB->DOEPCTL1_b.UAE = (mps != 0) ? 1 : 0;
    }
}

void USB_devActEP2(const BOOL in, const uint32_t mps, USB_EP_TYPE type)
{
    if (in) {
        USB->DIEPCTL2_b.MPS = mps;
        USB->DIEPCTL2_b.EP_TYPE = type;
        USB->DIEPCTL2_b.UAE = (mps != 0) ? 1 : 0;
    } else {
        USB->DOEPCTL2_b.MPS = mps;
        USB->DOEPCTL2_b.EP_TYPE = type;
        USB->DOEPCTL2_b.UAE = (mps != 0) ? 1 : 0;
    }
}

void USB_devEP1in(uint32_t size, uint32_t pktcnt, uint32_t pid, void *desc)
{
    USB->DIEPTSIZ1_b.SIZE = size;
    USB->DIEPTSIZ1_b.PACKET_CNT = pktcnt;
    USB->DIEPDMA1 = (uint32_t)(desc);
    USB->DIEPCTL1_b.CNAK = 1;
    USB->DIEPCTL1_b.SET_D0_PID = (pid >> 0) & 0x1;
    USB->DIEPCTL1_b.SET_D1_PID = (pid >> 1) & 0x1;
    USB->DIEPCTL1_b.EPE = 1;
}

void USB_devEP1out(uint32_t size, uint32_t pktcnt, uint32_t pid, uint32_t stpcnt, void *desc, BOOL snoop)
{
    USB->DOEPTSIZ1_b.SIZE = size;
    USB->DOEPTSIZ1_b.PACKET_CNT = pktcnt;
    USB->DOEPTSIZ1_b.SETUPCNT_PID = stpcnt;
    USB->DOEPDMA1 = (uint32_t)(desc);
    USB->DOEPCTL1_b.EC = snoop;
    USB->DOEPCTL1_b.CNAK = 1;
    USB->DOEPCTL1_b.SET_D0_PID = (pid >> 0) & 0x1;
    USB->DOEPCTL1_b.SET_D1_PID = (pid >> 1) & 0x1;
    USB->DOEPCTL1_b.EPE = 1;
}


void USB_devEP2in(uint32_t size, uint32_t pktcnt, uint32_t pid, void *desc)
{
    USB->DIEPTSIZ2_b.SIZE = size;
    USB->DIEPTSIZ2_b.PACKET_CNT = pktcnt;
    USB->DIEPDMA2 = (uint32_t)(desc);
    USB->DIEPCTL2_b.CNAK = 1;
    USB->DIEPCTL2_b.SET_D0_PID = (pid >> 0) & 0x1;
    USB->DIEPCTL2_b.SET_D1_PID = (pid >> 1) & 0x1;
    USB->DIEPCTL2_b.EPE = 1;
}

void USB_devEP2out(uint32_t size, uint32_t pktcnt, uint32_t pid, uint32_t stpcnt, void *desc, BOOL snoop)
{
    USB->DOEPTSIZ2_b.SIZE = size;
    USB->DOEPTSIZ2_b.PACKET_CNT = pktcnt;
    USB->DOEPTSIZ2_b.SETUPCNT_PID = stpcnt;
    USB->DOEPDMA2 = (uint32_t)(desc);
    USB->DOEPCTL2_b.EC = snoop;
    USB->DOEPCTL2_b.CNAK = 1;
    USB->DOEPCTL2_b.SET_D0_PID = (pid >> 0) & 0x1;
    USB->DOEPCTL2_b.SET_D1_PID = (pid >> 1) & 0x1;
    USB->DOEPCTL2_b.EPE = 1;
}

void USB_devNAKhandshake(uint32_t ep, BOOL in, BOOL en)
{
    switch (ep) {
    case 0:
        if (in) {
            if (en) USB->DIEPCTL0_b.SNAK = 1; else USB->DIEPCTL0_b.CNAK = 1;
        } else {
            if (en) USB->DOEPCTL0_b.SNAK = 1; else USB->DOEPCTL0_b.CNAK = 1;
        }
        break;
    case 1:
        if (in) {
            if (en) USB->DIEPCTL1_b.SNAK = 1; else USB->DIEPCTL1_b.CNAK = 1;
        } else {
            if (en) USB->DOEPCTL1_b.SNAK = 1; else USB->DOEPCTL1_b.CNAK = 1;
        }
        break;
    case 2:
        if (in) {
            if (en) USB->DIEPCTL2_b.SNAK = 1; else USB->DIEPCTL2_b.CNAK = 1;
        } else {
            if (en) USB->DOEPCTL2_b.SNAK = 1; else USB->DOEPCTL2_b.CNAK = 1;
        }
        break;
    default:
        break;
    }
}

BOOL USB_devSTALLhandshake(uint32_t ep, BOOL in, BOOL en)
{
    BOOL retval = FALSE;
    switch (ep) {
    case 0:
        if (in) {
            retval = USB->DIEPCTL0_b.STALL;
            USB->DIEPCTL0_b.STALL = en ? 1 : 0;
        } else {
            retval = USB->DOEPCTL0_b.STALL;
            USB->DOEPCTL0_b.STALL = en ? 1 : 0;
        }
        break;
    case 1:
        if (in) {
            retval = USB->DIEPCTL1_b.STALL;
            USB->DIEPCTL1_b.STALL = en ? 1 : 0;
        } else {
            retval = USB->DOEPCTL1_b.STALL;
            USB->DOEPCTL1_b.STALL = en ? 1 : 0;
        }
        break;
    case 2:
        if (in) {
            retval = USB->DIEPCTL2_b.STALL;
            USB->DIEPCTL2_b.STALL = en ? 1 : 0;
        } else {
            retval = USB->DOEPCTL2_b.STALL;
            USB->DOEPCTL2_b.STALL = en ? 1 : 0;
        }
        break;
    default:
        break;
    }
    return retval;
}

void USB_devINT_enDone(uint32_t ep, BOOL in, BOOL en)
{
    if (in) {
        USB->DIEPEN_b.TIMEOUT = en ? 1 : 0;
        USB->DIEPEN_b.TC = en ? 1 : 0;
        if (en) {
            USB->GINTEN_b.IEP_INT = 1;
            USB->DAINT_EN_b.IN_EN |= BIT(ep);
        } else
            USB->DAINT_EN_b.IN_EN &= ~BIT(ep);
    } else {
        USB->DOEPEN_b.SPD = en ? 1 : 0;
        USB->DOEPEN_b.TC = en ? 1 : 0;
        if (en) {
            USB->GINTEN_b.OEP_INT = 1;
            USB->DAINT_EN_b.OUT_EN |= BIT(ep);
        } else
            USB->DAINT_EN_b.OUT_EN &= ~BIT(ep);
    }
}

uint32_t USB_devINT_isDone(uint32_t ep, BOOL in)
{
    int32_t retval = 0;
    if (in) {
        if (USB->GINTSTS_b.IEP_INT)
        switch (ep) {
        case 0:
            if (USB->DIEPINT0_b.TC) {
                retval |= 0x1;
                USB->DIEPINT0 = BIT(0);
            }
            if (USB->DIEPINT0_b.BNA) {
                retval |= 0x2;
                USB->DIEPINT0 = BIT(9);
            }
            break;
        case 1:
            if (USB->DIEPINT1_b.TC) {
                retval |= 0x1;
                USB->DIEPINT1 = BIT(0);
            }
            if (USB->DIEPINT1_b.BNA) {
                retval |= 0x2;
                USB->DIEPINT1 = BIT(9);
            }
            break;
        case 2:
            if (USB->DIEPINT2_b.TC) {
                retval |= 0x1;
                USB->DIEPINT2 = BIT(0);
            }
            if (USB->DIEPINT2_b.BNA) {
                retval |= 0x2;
                USB->DIEPINT2 = BIT(9);
            }
        default:
            break;
        }
    } else {
        if (USB->GINTSTS_b.OEP_INT)
        switch (ep) {
        case 0:
            if (USB->DOEPINT0_b.TC) {
                retval |= 0x1;
                USB->DOEPINT0 = BIT(0);
            }
            if (USB->DOEPINT0_b.SETUP) {
                retval |= 0x4;
                USB->DOEPINT0 = BIT(3);
            }
            break;
        case 1:
            if (USB->DOEPINT1_b.TC) {
                retval |= 0x1;
                USB->DOEPINT1 = BIT(0);
            }
            if (USB->DOEPINT1_b.BNA) {
                retval |= 0x2;
                USB->DOEPINT1 = BIT(9);
            }
            break;
        case 2:
            if (USB->DOEPINT2_b.TC) {
                retval |= 0x1;
                USB->DOEPINT2 = BIT(0);
            }
            if (USB->DOEPINT2_b.BNA) {
                retval |= 0x2;
                USB->DOEPINT2 = BIT(9);
            }
            break;
        default:
            break;
        }
    }
    return retval;
}

void USB_INT_enOTG(BOOL en)
{
    USB->GINTEN_b.OTG_INT = en;
}

BOOL USB_INT_isOTG()
{
    return USB->GINTSTS_b.OTG_INT ? TRUE : FALSE;
}

BOOL USB_INT_isOTGon(USB_INT_OTG otg)
{
    switch (otg) {
    case USB_INT_OTG_SESEND:
        return USB->GOTGINT_b.SES_END_DET ? TRUE : FALSE;
        break;
    case USB_INT_OTG_STANDAUP:
        return USB->GOTGINT_b.A_DEV_TOUT_CHG ? TRUE : FALSE;
        break;
    case USB_INT_OTG_HNDETECT:
        return USB->GOTGINT_b.HST_NEG_DET ? TRUE : FALSE;
        break;
    case USB_INT_OTG_HNSUCCHG:
        return USB->GOTGINT_b.HST_NEG_SUC_STS_CHNG ? TRUE : FALSE;
        break;
    case USB_INT_OTG_KEEPAPP:
        return USB->GOTGINT_b.DBNCE_DONE ? TRUE : FALSE;
        break;
    default:
        break;
    }
    return FALSE;
}

void USB_INT_clrOTGon(USB_INT_OTG otg)
{
    switch (otg) {
    case USB_INT_OTG_SESEND:
        USB->GOTGINT = BIT(2);
        break;
    case USB_INT_OTG_STANDAUP:
        USB->GOTGINT = BIT(18);
        break;
    case USB_INT_OTG_HNDETECT:
        USB->GOTGINT = BIT(17);
        break;
    case USB_INT_OTG_HNSUCCHG:
        USB->GOTGINT = BIT(9);
        break;
    case USB_INT_OTG_KEEPAPP:
        USB->GOTGINT = BIT(19);
        break;
    default:
        break;
    }
}

void USB_INT_enGP(USB_INT_GP name, BOOL en)
{
    switch (name) {
    case USB_INT_GP_HOST_DISC:
        USB->GINTEN_b.DD = en ? 1 : 0;
        break;
    case USB_INT_GP_DEV_RESET:
        USB->GINTEN_b.USB_RST = en ? 1 : 0;
        break;
    case USB_INT_GP_DEV_ENUMDONE:
        USB->GINTEN_b.ENUM_DONE = en ? 1 : 0;
        break;
    case USB_INT_GP_DEV_SUSP:
        USB->GINTEN_b.USB_SUS = en ? 1 : 0;
        break;
    case USB_INT_GP_DEV_EARLY:
        USB->GINTEN_b.EARLY_SUS = en ? 1 : 0;
        break;
    case USB_INT_GP_SOF:
        USB->GINTEN_b.SOF = en ? 1 : 0;
        break;
    case USB_INT_GP_MIS:
        USB->GINTEN_b.MODE_MIS = en ? 1 : 0;
        break;
    case USB_INT_GP_IDCHG:
        USB->GINTEN_b.CIDSC = en ? 1 : 0;
        break;
    case USB_INT_GP_SESSREQ:
        USB->GINTEN_b.SR = en ? 1 : 0;
        break;
    default:
        break;
    }
}

BOOL USB_INT_isGP(USB_INT_GP name)
{
    switch (name) {
    case USB_INT_GP_HOST_DISC:
        return USB->GINTSTS_b.DD ? TRUE : FALSE;
        break;
    case USB_INT_GP_DEV_RESET:
        return USB->GINTSTS_b.USB_RST ? TRUE : FALSE;
        break;
    case USB_INT_GP_DEV_ENUMDONE:
        return USB->GINTSTS_b.ENUM_DONE ? TRUE : FALSE;
        break;
    case USB_INT_GP_DEV_SUSP:
        return USB->GINTSTS_b.USB_SUS ? TRUE : FALSE;
        break;
    case USB_INT_GP_DEV_EARLY:
        return USB->GINTSTS_b.EARLY_SUS ? TRUE : FALSE;
        break;
    case USB_INT_GP_SOF:
        return USB->GINTSTS_b.SOF ? TRUE : FALSE;
        break;
    case USB_INT_GP_MIS:
        return USB->GINTSTS_b.MODE_MIS ? TRUE : FALSE;
        break;
    case USB_INT_GP_IDCHG:
        return USB->GINTSTS_b.CIDSC ? TRUE : FALSE;
        break;
    case USB_INT_GP_SESSREQ:
        return USB->GINTSTS_b.SR ? TRUE : FALSE;
        break;
    default:
        break;
    }
    return FALSE;
}

void USB_INT_clrGP(USB_INT_GP name)
{
    switch (name) {
    case USB_INT_GP_HOST_DISC:
        USB->GINTSTS = BIT(29);
        break;
    case USB_INT_GP_DEV_RESET:
        USB->GINTSTS = BIT(12);
        break;
    case USB_INT_GP_DEV_ENUMDONE:
        USB->GINTSTS = BIT(13);
        break;
    case USB_INT_GP_DEV_SUSP:
        USB->GINTSTS = BIT(11);
        break;
    case USB_INT_GP_DEV_EARLY:
        USB->GINTSTS = BIT(10);
        break;
    case USB_INT_GP_SOF:
        USB->GINTSTS = BIT(3);
        break;
    case USB_INT_GP_MIS:
        USB->GINTSTS = BIT(1);
        break;
    case USB_INT_GP_IDCHG:
        USB->GINTSTS = BIT(28);
        break;
    case USB_INT_GP_SESSREQ:
        USB->GINTSTS = BIT(30);
        break;
    default:
        break;
    }
}

BOOL USB_otgControl(USB_OTG_CTL ctl, BOOL val)
{
    BOOL retval = FALSE;
    switch (ctl) {
    case USB_OTG_DEV_HNSUCC:
        retval = USB->GOTGCTL_b.HST_NEG_SCS ? TRUE : FALSE;
        break;
    case USB_OTG_DEV_HNPREQ:
        retval = USB->GOTGCTL_b.HNP_REQ ? TRUE : FALSE;
        USB->GOTGCTL_b.HNP_REQ = val ? 1 : 0;
        break;
    case USB_OTG_HST_HNPENABLE:
        retval = USB->GOTGCTL_b.HST_SET_HNP_EN ? TRUE : FALSE;
        USB->GOTGCTL_b.HST_SET_HNP_EN = val ? 1 : 0;
        break;
    case USB_OTG_DEV_HNPENABLE:
        retval = USB->GOTGCTL_b.DEV_HNP_EN ? TRUE : FALSE;
        USB->GOTGCTL_b.DEV_HNP_EN = val ? 1 : 0;
        break;
    default:
        break;
    }
    return retval;
}
