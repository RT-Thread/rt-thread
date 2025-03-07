/*
 * Copyright (c) 2023, Artinchip Technology Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtconfig.h>
#include "usbd_core.h"
#include "usb_dc_aic_reg.h"

// clang-format off
#ifndef   __UNALIGNED_UINT32_WRITE
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  __PACKED_STRUCT T_UINT32_WRITE { uint32_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT32_WRITE(addr, val)    (void)((((struct T_UINT32_WRITE *)(void *)(addr))->v) = (val))
#endif
#ifndef   __UNALIGNED_UINT32_READ
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpacked"
  #pragma GCC diagnostic ignored "-Wattributes"
  __PACKED_STRUCT T_UINT32_READ { uint32_t v; };
  #pragma GCC diagnostic pop
  #define __UNALIGNED_UINT32_READ(addr)          (((const struct T_UINT32_READ *)(const void *)(addr))->v)
#endif
// clang-format on

#define FS_PORT 0
#define HS_PORT 1

#ifndef CONFIG_USB_AIC_DC_PORT
#error "please select CONFIG_USB_AIC_DC_PORT with FS_PORT or HS_PORT"
#endif

#ifndef USB_BASE
#define USB_BASE CONFIG_USB_AIC_DC_BASE
#endif

#ifdef LPKG_CHERRYUSB_DEVICE_HID_IO_TEMPLATE
#define USB_RAM_SIZE 1024 /* define with maximum value*/
#else
#define USB_RAM_SIZE 512  /* define with maximum value*/
#endif

#ifndef USB_NUM_BIDIR_ENDPOINTS
#define USB_NUM_BIDIR_ENDPOINTS 5 /* define with minimum value*/
#endif

#define AIC_UDC_REG      ((AIC_UDC_RegDef *)(USB_BASE))
#define AIC_EP_FIFO(i)  *(__IO uint32_t *)(USB_BASE + AIC_EP_FIFO_BASE + ((i)*AIC_EP_FIFO_SIZE))

static uint8_t g_aic_udc_ibuf[USB_RAM_SIZE] __ALIGNED(CACHE_LINE_SIZE);
static uint8_t g_aic_udc_obuf[USB_RAM_SIZE] __ALIGNED(CACHE_LINE_SIZE);

/* Endpoint state */
struct aic_ep_state {
    uint16_t ep_mps;    /* Endpoint max packet size */
    uint8_t ep_type;    /* Endpoint type */
    uint8_t ep_stalled; /* Endpoint stall flag */
    uint8_t *xfer_buf;
#ifdef CONFIG_USB_AIC_DMA_ENABLE
    uint8_t *xfer_align_buf;
    uint32_t xfer_align_len;
#endif
    uint32_t xfer_len;
    uint32_t actual_xfer_len;
};

extern uint32_t usbd_clk;

/* Driver state */
/*USB_NOCACHE_RAM_SECTION*/ struct aic_udc {
    USB_MEM_ALIGNX struct usb_setup_packet setup;
    USB_MEM_ALIGNX struct aic_ep_state in_ep[USB_NUM_BIDIR_ENDPOINTS];  /*!< IN endpoint parameters*/
    struct aic_ep_state out_ep[USB_NUM_BIDIR_ENDPOINTS]; /*!< OUT endpoint parameters */
    uint32_t tx_fifo_map;
} g_aic_udc;

uint8_t rst_allow = 0;
uint8_t ep0_ctrl_stage = 0; /* 1 = setup stage, 2 = data stage, 3 = status stage */

#ifdef CONFIG_USB_AIC_DMA_ENABLE
void aic_udc_dcache_clean(uintptr_t addr, uint32_t len)
{
    aicos_dcache_clean_range((size_t *)addr, len);
}

void aic_udc_dcache_invalidate(uintptr_t addr, uint32_t len)
{
    aicos_dcache_invalid_range((size_t *)addr, len);
}

void aic_udc_dcache_clean_invalidate(uintptr_t addr, uint32_t len)
{
    aicos_dcache_clean_invalid_range((size_t *)addr, len);
}

static int aic_udc_ep_buf_alloc(struct aic_ep_state *ep, uint32_t len,
                                uint8_t *sbuf)
{
    ep->xfer_len = len;
    if (len % CACHE_LINE_SIZE)
        ep->xfer_align_len = ALIGN_UP(len, CACHE_LINE_SIZE);
    else
        ep->xfer_align_len = len;

    if (ep->xfer_align_len > USB_RAM_SIZE) {
        ep->xfer_align_buf = aicos_malloc_align(0, ep->xfer_align_len,
                                                CACHE_LINE_SIZE);
        if (!ep->xfer_align_buf) {
            USB_LOG_ERR("alloc error.\r\n");
            return -5;
        }
    } else {
        ep->xfer_align_buf = sbuf;
    }

    return 0;
}

static void aic_udc_ep_buf_free(struct aic_ep_state *ep, uint8_t *sbuf)
{
    if (!ep->xfer_align_buf)
        return;

    /* Whether the buf is allocated dynamically */
    if (ep->xfer_align_buf != sbuf)
        aicos_free_align(0, ep->xfer_align_buf);

    ep->xfer_align_buf = NULL;
    ep->xfer_align_len = 0;
}

static int aic_udc_ibuf_alloc(struct aic_ep_state *ep, uint32_t len)
{
    return aic_udc_ep_buf_alloc(ep, len, g_aic_udc_ibuf);
}

static int aic_udc_obuf_alloc(struct aic_ep_state *ep, uint32_t len)
{
    return aic_udc_ep_buf_alloc(ep, len, g_aic_udc_obuf);
}

static void aic_udc_ibuf_free(struct aic_ep_state *ep)
{
    aic_udc_ep_buf_free(ep, g_aic_udc_ibuf);
}

static void aic_udc_obuf_free(struct aic_ep_state *ep)
{
    aic_udc_ep_buf_free(ep, g_aic_udc_obuf);
}
#else
#define aic_udc_dcache_clean(addr, len)
#define aic_udc_dcache_invalidate(addr, len)
#define aic_udc_dcache_clean_invalidate(addr, len)
#endif

static void aic_set_dma_nextep(void)
{
    uint32_t i;

    /* dma to set the next-endpoint pointer. */
    for (i = 0; i < USB_NUM_BIDIR_ENDPOINTS; i++) {
        uint32_t next = ((i + 1) % USB_NUM_BIDIR_ENDPOINTS) << DEPCTL_NEXT_EP_BIT;

        AIC_UDC_REG->inepcfg[i] &= ~DEPCTL_NEXT_EP_MASK;
        AIC_UDC_REG->inepcfg[i] |= next;
    }
}

static inline int aic_reset(void)
{
    uint32_t count = 0U;

    /* Wait for AHB master IDLE state. */
    do {
        if (++count > 200000U) {
            return -1;
        }
    } while ((AIC_UDC_REG->ahbbasic & AHBBASIC_AHBIDLE) == 0U);

    /* Core Soft Reset */
    count = 0U;
    AIC_UDC_REG->usbdevinit |= USBDEVINIT_CSFTRST;

    do {
        if (++count > 200000U) {
            return -1;
        }
    } while ((AIC_UDC_REG->usbdevinit & USBDEVINIT_CSFTRST) == USBDEVINIT_CSFTRST);

    return 0;
}

static inline int aic_core_init(void)
{
    int ret;
    uint32_t usb_gusbcfg =
        0 << 19     /* ULPI Clock SuspendM */
        | 0 << 18   /* ULPI Phy Auto Resume */
        | 0 << 15   /* PHY Low Power Clock sel */
        | 0x5 << 10 /* USB Turnaround time (0x5 for HS phy) */
        | 0 << 7    /* ULPI DDR sel 0:single 8bit, 1:double 4bit */
        /*| 0 << 6   0: high speed utmi+, 1: full speed serial*/
#ifdef FPGA_BOARD_ARTINCHIP
        | 1 << 4    /* 0: utmi+, 1:ulpi*/
#else
        | 0 << 4    /* 0: utmi+, 1:ulpi*/
#endif
        | 0 << 3    /* UTMI+ PHY  0:8bit, 1:16bit (ULPI PHY set 8bit) */
        | 0x7 << 0; /* HS/FS timeout calibration**/

    /* Reset after a PHY select */
    ret = aic_reset();

    /* Activate the USB Transceiver */
    AIC_UDC_REG->usbphyif = usb_gusbcfg;

    aic_set_dma_nextep();

    return ret;
}

static inline int aic_flush_rxfifo(void)
{
    uint32_t count = 0;

    AIC_UDC_REG->usbdevinit |= USBDEVINIT_RXFFLSH;

    do {
        if (++count > 200000U) {
            return -1;
        }
    } while ((AIC_UDC_REG->usbdevinit & USBDEVINIT_RXFFLSH) == USBDEVINIT_RXFFLSH);

    return 0;
}

static inline int aic_flush_txfifo(uint32_t num)
{
    uint32_t count = 0U;

    AIC_UDC_REG->usbdevinit |= USBDEVINIT_TXFNUM(num & USBDEVINIT_TXFNUM_LIMIT);

    do {
        if (++count > 200000U) {
            return -1;
        }
    } while ((AIC_UDC_REG->usbdevinit & USBDEVINIT_TXFFLSH) == USBDEVINIT_TXFFLSH);

    return 0;
}

static void aic_set_turnaroundtime(uint32_t hclk, uint8_t speed)
{
    uint32_t UsbTrd;

    /* The USBTRD is configured according to the tables below, depending on AHB frequency
  used by application. In the low AHB frequency range it is used to stretch enough the USB response
  time to IN tokens, the USB turnaround time, so to compensate for the longer AHB read access
  latency to the Data FIFO */
    if (speed == USB_ENUM_SPEED_FULL) {
        if ((hclk >= 14200000U) && (hclk < 15000000U)) {
            /* hclk Clock Range between 14.2-15 MHz */
            UsbTrd = 0xFU;
        } else if ((hclk >= 15000000U) && (hclk < 16000000U)) {
            /* hclk Clock Range between 15-16 MHz */
            UsbTrd = 0xEU;
        } else if ((hclk >= 16000000U) && (hclk < 17200000U)) {
            /* hclk Clock Range between 16-17.2 MHz */
            UsbTrd = 0xDU;
        } else if ((hclk >= 17200000U) && (hclk < 18500000U)) {
            /* hclk Clock Range between 17.2-18.5 MHz */
            UsbTrd = 0xCU;
        } else if ((hclk >= 18500000U) && (hclk < 20000000U)) {
            /* hclk Clock Range between 18.5-20 MHz */
            UsbTrd = 0xBU;
        } else if ((hclk >= 20000000U) && (hclk < 21800000U)) {
            /* hclk Clock Range between 20-21.8 MHz */
            UsbTrd = 0xAU;
        } else if ((hclk >= 21800000U) && (hclk < 24000000U)) {
            /* hclk Clock Range between 21.8-24 MHz */
            UsbTrd = 0x9U;
        } else if ((hclk >= 24000000U) && (hclk < 27700000U)) {
            /* hclk Clock Range between 24-27.7 MHz */
            UsbTrd = 0x8U;
        } else if ((hclk >= 27700000U) && (hclk < 32000000U)) {
            /* hclk Clock Range between 27.7-32 MHz */
            UsbTrd = 0x7U;
        } else {/* if(hclk >= 32000000) */
            /* hclk Clock Range between 32-200 MHz */
            UsbTrd = 0x6U;
        }
    } else if (speed == USB_ENUM_SPEED_HIGH) {
        UsbTrd = USBPHYIF_HS_TRDT_VALUE;
    } else {
        UsbTrd = USBPHYIF_DEFAULT_TRDT_VALUE;
    }

    AIC_UDC_REG->usbphyif |= USBPHYIF_TOUTCAL_LIMIT;

    AIC_UDC_REG->usbphyif &= ~USBPHYIF_USBTRDTIM_MASK;
    AIC_UDC_REG->usbphyif |= (uint32_t)((UsbTrd << USBPHYIF_USBTRDTIM_SHIFT)
                                        & USBPHYIF_USBTRDTIM_MASK);
}

#if 0
static void aic_set_txfifo(uint8_t fifo, uint16_t size)
{
    uint8_t i;
    uint32_t Tx_Offset;

    /*  TXn min size = 16 words. (n  : Transmit FIFO index)
      When a TxFIFO is not used, the Configuration should be as follows:
          case 1 :  n > m    and Txn is not used    (n,m  : Transmit FIFO indexes)
         --> Txm can use the space allocated for Txn.
         case2  :  n < m    and Txn is not used    (n,m  : Transmit FIFO indexes)
         --> Txn should be configured with the minimum space of 16 words
     The FIFO is used optimally when used TxFIFOs are allocated in the top
         of the FIFO.Ex: use EP1 and EP2 as IN instead of EP1 and EP3 as IN ones.
     When DMA is used 3n * FIFO locations should be reserved for internal DMA registers */

    Tx_Offset = AIC_UDC_REG->rxfifosiz;

    if (fifo == 0U) {
        AIC_UDC_REG->nptxfifosiz = ((uint32_t)size << 16) | Tx_Offset;
    } else {
        Tx_Offset += (AIC_UDC_REG->nptxfifosiz) >> 16;
        for (i = 0U; i < (fifo - 1U); i++) {
            Tx_Offset += (AIC_UDC_REG->txfifosiz[i] >> 16);
        }

        /* Multiply Tx_Size by 2 to get higher performance */
        AIC_UDC_REG->txfifosiz[fifo - 1U] = ((uint32_t)size << 16) | Tx_Offset;
    }
}
#endif

static uint8_t aic_get_devspeed(void)
{
    uint8_t speed;
    uint32_t DevEnumSpeed = AIC_UDC_REG->usblinests & USB_ENUM_SPEED_MASK;

    if (DevEnumSpeed == USB_HIGH_30_60MHZ) {
        speed = USB_ENUM_SPEED_HIGH;
    } else if (DevEnumSpeed == USB_FULL_30_60MHZ) {
        speed = USB_ENUM_SPEED_FULL;
    } else {
        speed = 0xFU;
    }

    return speed;
}

static void aic_ep0_start_read_setup(uint8_t *psetup)
{
    g_aic_udc.out_ep[0].xfer_buf = psetup;
    g_aic_udc.out_ep[0].xfer_len = 8;
    ep0_ctrl_stage = 1;

    aic_udc_dcache_invalidate((uintptr_t)psetup, CACHE_LINE_SIZE);

    AIC_UDC_REG->outeptsfsiz[0] = 0U;
    AIC_UDC_REG->outeptsfsiz[0] |= (DXEPTSIZ_PKT_CNT_MASK & (1U << 19));
    AIC_UDC_REG->outeptsfsiz[0] |= (3U * 8U);
    AIC_UDC_REG->outeptsfsiz[0] |= DXEPTSIZ_MULCNT_MASK;

#ifdef CONFIG_USB_AIC_DMA_ENABLE
    AIC_UDC_REG->outepdmaaddr[0] = (uint32_t)(uintptr_t)psetup;
#endif

    /* EP enable */
    AIC_UDC_REG->outepcfg[0] |= DEPCTL_CNAK | DEPCTL_EPENA | DEPCTL_USBACTEP;
}

void aic_ep_write(uint8_t ep_idx, uint8_t *src, uint16_t len)
{
    uint32_t *pSrc = (uint32_t *)src;
    uint32_t count32b, i;

    count32b = ((uint32_t)len + 3U) / 4U;
    for (i = 0U; i < count32b; i++) {
        AIC_EP_FIFO(ep_idx) = __UNALIGNED_UINT32_READ(pSrc);
        pSrc++;
    }
}

void aic_ep_read(uint8_t *dest, uint16_t len)
{
    uint32_t *pDest = (uint32_t *)dest;
    uint32_t i;
    uint32_t count32b = ((uint32_t)len + 3U) / 4U;

    for (i = 0U; i < count32b; i++) {
        __UNALIGNED_UINT32_WRITE(pDest, AIC_EP_FIFO(0U));
        pDest++;
    }
}

#ifndef CONFIG_USB_AIC_DMA_ENABLE
static void aic_tx_fifo_empty_procecss(uint8_t ep_idx)
{
    uint32_t len;
    //uint32_t len32b;

    len = g_aic_udc.in_ep[ep_idx].xfer_len - g_aic_udc.in_ep[ep_idx].actual_xfer_len;
    if (len > g_aic_udc.in_ep[ep_idx].ep_mps) {
        len = g_aic_udc.in_ep[ep_idx].ep_mps;
    }

    //len32b = (len + 3U) / 4U;

    while (/*((AIC_UDC_REG->ineptxsts[ep_idx] & INEPTXSTS_IN_EP_TXFIFO_STS) >= len32b) &&*/
           (g_aic_udc.in_ep[ep_idx].actual_xfer_len < g_aic_udc.in_ep[ep_idx].xfer_len) && (g_aic_udc.in_ep[ep_idx].xfer_len != 0U)) {
        /* Write the FIFO */
        len = g_aic_udc.in_ep[ep_idx].xfer_len - g_aic_udc.in_ep[ep_idx].actual_xfer_len;
        if (len > g_aic_udc.in_ep[ep_idx].ep_mps) {
            len = g_aic_udc.in_ep[ep_idx].ep_mps;
        }

        aic_ep_write(ep_idx, g_aic_udc.in_ep[ep_idx].xfer_buf, len);
        g_aic_udc.in_ep[ep_idx].xfer_buf += len;
        g_aic_udc.in_ep[ep_idx].actual_xfer_len += len;
    }
}
#endif

/**
  * @brief  aic_get_glb_intstatus: return the global USB interrupt status
  * @retval status
  */
static inline uint32_t aic_get_glb_intstatus(void)
{
    uint32_t tmpreg;

    tmpreg = AIC_UDC_REG->usbintsts;
    tmpreg &= AIC_UDC_REG->usbintmsk;

    return tmpreg;
}

/**
  * @brief  aic_get_outeps_intstatus: return the USB device OUT endpoints interrupt status
  * @retval status
  */
static inline uint32_t aic_get_outeps_intstatus(void)
{
    uint32_t tmpreg;

    tmpreg = AIC_UDC_REG->usbepint;
    tmpreg &= AIC_UDC_REG->usbepintmsk;

    return ((tmpreg & 0xffff0000U) >> 16);
}

/**
  * @brief  aic_get_ineps_intstatus: return the USB device IN endpoints interrupt status
  * @retval status
  */
static inline uint32_t aic_get_ineps_intstatus(void)
{
    uint32_t tmpreg;

    tmpreg = AIC_UDC_REG->usbepint;
    tmpreg &= AIC_UDC_REG->usbepintmsk;

    return ((tmpreg & 0xFFFFU));
}

/**
  * @brief  Returns Device OUT EP Interrupt register
  * @param  epnum  endpoint number
  *          This parameter can be a value from 0 to 15
  * @retval Device OUT EP Interrupt register
  */
static inline uint32_t aic_get_outep_intstatus(uint8_t epnum)
{
    uint32_t tmpreg;

    tmpreg = AIC_UDC_REG->outepint[epnum];
    tmpreg &= AIC_UDC_REG->outepintmsk;

    return tmpreg;
}

/**
  * @brief  Returns Device IN EP Interrupt register
  * @param  epnum  endpoint number
  *          This parameter can be a value from 0 to 15
  * @retval Device IN EP Interrupt register
  */
static inline uint32_t aic_get_inep_intstatus(uint8_t epnum)
{
    uint32_t tmpreg;

    tmpreg = AIC_UDC_REG->inepint[epnum];
    tmpreg &= AIC_UDC_REG->inepintmsk;

    return tmpreg;
}

__WEAK void usb_dc_low_level_init(void)
{
}

__WEAK void usb_dc_low_level_deinit(void)
{
}

int usb_dc_rst(void)
{
    for (uint8_t i = 0U; i < USB_NUM_BIDIR_ENDPOINTS; i++) {
        if (i == 0U) {
            AIC_UDC_REG->inepcfg[i] = DEPCTL_SNAK;
            AIC_UDC_REG->outepcfg[i] = DEPCTL_SNAK;
        } else {
            usbd_ep_close(i);
            usbd_ep_close(i | 0x80);
        }
        AIC_UDC_REG->ineptsfsiz[i] = 0U;
        AIC_UDC_REG->inepint[i] = 0xFBFFU;
        AIC_UDC_REG->outeptsfsiz[i] = 0U;
        AIC_UDC_REG->outepint[i] = 0xFBFFU;
    }

    AIC_UDC_REG->usbepintmsk |= 0x10001U;
    AIC_UDC_REG->outepintmsk = CTRL_OUT_EP_SETUP_PHASE_DONE | TRANSFER_DONE;
    AIC_UDC_REG->inepintmsk = TRANSFER_DONE;
#ifndef CONFIG_USB_AIC_DMA_ENABLE
    AIC_UDC_REG->inepintmsk |= INTKN_TXFEMP;
#endif

    aic_flush_txfifo(0x10U);
    aic_flush_rxfifo();

    aic_set_dma_nextep();

#ifdef CONFIG_USB_AIC_DMA_ENABLE
    for (uint8_t i = 0U; i < USB_NUM_BIDIR_ENDPOINTS; i++) {
        aic_udc_obuf_free(&g_aic_udc.out_ep[i]);
        aic_udc_ibuf_free(&g_aic_udc.in_ep[i]);
    }
#endif

    memset(&g_aic_udc, 0, sizeof(struct aic_udc));
    usbd_event_reset_handler(0);
    /* Start reading setup */
    aic_ep0_start_read_setup((uint8_t *)&g_aic_udc.setup);

    return 0;
}

int usb_dc_init(uint8_t busid)
{
    int ret;
    uint32_t base = 0;

    memset(&g_aic_udc, 0, sizeof(struct aic_udc));

    usb_dc_low_level_init();

    /* Disconnect */
    AIC_UDC_REG->usbdevfunc |= USBDEVFUNC_SFTDISCON;
    /* Disable Interrupt */
    AIC_UDC_REG->usbdevinit &= ~USBDEVINIT_GLBL_INTR_EN;

    ret = aic_core_init();

    for (uint8_t i = 0U; i < 2U; i++) {
        AIC_UDC_REG->txfifosiz[i] = 0U;
    }

    /* Device mode configuration */
    AIC_UDC_REG->usbdevconf |= PERIOD_FRAME_INTERVAL_80;

#if defined(CONFIG_USB_HS)
    /* Set Core speed to High speed mode */
    AIC_UDC_REG->usbdevconf |= DEV_SPEED_HIGH_SPEED_20;
#else

    AIC_UDC_REG->usbdevconf |= DEV_SPEED_FULL_SPEED_20;
#endif

    ret = aic_flush_txfifo(0x10U);
    ret = aic_flush_rxfifo();

    /* Clear all pending Device Interrupts */
    AIC_UDC_REG->inepintmsk = 0U;
    AIC_UDC_REG->outepintmsk = 0U;
    AIC_UDC_REG->usbepintmsk = 0U;

    /* Disable all interrupts. */
    AIC_UDC_REG->usbintmsk = 0U;
    /* Clear any pending interrupts */
    AIC_UDC_REG->usbintsts = 0xBFFFFFFFU;

    /* Enable interrupts matching to the Device mode ONLY */
    AIC_UDC_REG->usbintmsk = INT_RESET | INT_ENUMDONE |
                             INT_OUT_EP | INT_IN_EP |
                             INT_INCOMP_ISO_IN_INT | INT_INCOMP_ISO_OUT_INT;

#ifdef CONFIG_USB_AIC_DMA_ENABLE
    AIC_UDC_REG->usbdevinit |= (USBDEVINIT_HBSTLEN_INCR4 << USBDEVINIT_HBSTLEN_SHIFT);
    AIC_UDC_REG->usbdevinit |= USBDEVINIT_DMA_EN;
#else
    AIC_UDC_REG->usbintmsk |= INT_RX_FIFO_NOT_EMPTY;
#endif

    /* Assign FIFO */
    base = 0;
    AIC_UDC_REG->rxfifosiz = AIC_RX_FIFO_SIZE;
    base += AIC_RX_FIFO_SIZE;
    AIC_UDC_REG->nptxfifosiz = (AIC_NP_TX_FIFO_SIZE << 16) | base;
    base += AIC_NP_TX_FIFO_SIZE;
    AIC_UDC_REG->txfifosiz[0] = (AIC_PERIOD_TX_FIFO1_SIZE << 16) | base;
    base += AIC_PERIOD_TX_FIFO1_SIZE;
    AIC_UDC_REG->txfifosiz[1] = (AIC_PERIOD_TX_FIFO2_SIZE << 16) | base;

    usb_dc_rst();

    /* Enable Interrupt */
    AIC_UDC_REG->usbdevinit |= USBDEVINIT_GLBL_INTR_EN;
    /* Connect */
    AIC_UDC_REG->usbdevfunc &= ~USBDEVFUNC_SFTDISCON;

    return ret;
}

int usb_dc_deinit(uint8_t busid)
{
    /* Clear Pending interrupt */
    for (uint8_t i = 0U; i < USB_NUM_BIDIR_ENDPOINTS; i++) {
        AIC_UDC_REG->outepint[i] = 0xFB7FU;
        AIC_UDC_REG->inepint[i] = 0xFB7FU;
    }

    /* Clear interrupt masks */
    AIC_UDC_REG->inepintmsk = 0U;
    AIC_UDC_REG->outepintmsk = 0U;
    AIC_UDC_REG->usbepintmsk = 0U;

    /* Flush the FIFO */
    aic_flush_txfifo(0x10U);
    aic_flush_rxfifo();

    AIC_UDC_REG->usbdevfunc |= USBDEVFUNC_SFTDISCON;

    usb_dc_low_level_deinit();
    return 0;
}

int usbd_set_address(uint8_t busid, const uint8_t addr)
{
    AIC_UDC_REG->usbdevconf &= ~(DEVICE_ADDRESS_MASK);
    AIC_UDC_REG->usbdevconf |= ((uint32_t)addr << 4) & DEVICE_ADDRESS_MASK;

    rst_allow = 1;
    return 0;
}

int usbd_set_remote_wakeup(uint8_t busid)
{
    return -1;
}

uint8_t usbd_get_port_speed(uint8_t busid)
{
    uint8_t speed;
    uint32_t DevEnumSpeed = AIC_UDC_REG->usblinests & USB_ENUM_SPEED_MASK;

    if (DevEnumSpeed == USB_HIGH_30_60MHZ) {
        speed = USB_SPEED_HIGH;
    } else if (DevEnumSpeed == USB_FULL_30_60MHZ) {
        speed = USB_SPEED_FULL;
    } else {
        speed = USB_SPEED_FULL;
    }

    return speed;
}

int usbd_ep_open(uint8_t busid, const struct usb_endpoint_descriptor *ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep->bEndpointAddress);
    uint16_t ep_mps;
    uint8_t tx_fifo_num = 0;
    uint32_t i;

    if (ep_idx > (USB_NUM_BIDIR_ENDPOINTS - 1)) {
        USB_LOG_ERR("Ep addr %d overflow\r\n", ep->bEndpointAddress);
        return -1;
    }

    if (USB_EP_DIR_IS_OUT(ep->bEndpointAddress)) {
        g_aic_udc.out_ep[ep_idx].ep_mps = USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize);
        g_aic_udc.out_ep[ep_idx].ep_type = USB_GET_ENDPOINT_TYPE(ep->bmAttributes);

        AIC_UDC_REG->usbepintmsk |= DAINT_OUT_MASK & (uint32_t)(1UL << (16 + ep_idx));

        ep_mps = USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize);
        if (ep_idx == 0) {
            switch (ep_mps) {
                case 8:
                    ep_mps = DEPCTL0_MPS_8;
                    break;
                case 16:
                    ep_mps = DEPCTL0_MPS_16;
                    break;
                case 32:
                    ep_mps = DEPCTL0_MPS_32;
                    break;
                case 64:
                    ep_mps = DEPCTL0_MPS_64;
                    break;
            }
        }

        AIC_UDC_REG->outepcfg[ep_idx] |= (ep_mps & DEPCTL_MPS_MASK) |
                                          ((uint32_t)USB_GET_ENDPOINT_TYPE(ep->bmAttributes) << 18) |
                                          DEPCTL_SETD0PID |
                                          DEPCTL_USBACTEP;
    } else {
        g_aic_udc.in_ep[ep_idx].ep_mps = USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize);
        g_aic_udc.in_ep[ep_idx].ep_type = USB_GET_ENDPOINT_TYPE(ep->bmAttributes);

        AIC_UDC_REG->usbepintmsk |= DAINT_IN_MASK & (uint32_t)(1UL << ep_idx);

        /* Period IN EP alloc fifo num */
        if (( USB_GET_ENDPOINT_TYPE(ep->bmAttributes) == USB_ENDPOINT_TYPE_INTERRUPT) ||
            ( USB_GET_ENDPOINT_TYPE(ep->bmAttributes) == USB_ENDPOINT_TYPE_ISOCHRONOUS)) {
            for (i=1; i<=2; i++) {
                if (g_aic_udc.tx_fifo_map & (1<<i))
                    continue;
                g_aic_udc.tx_fifo_map |= (1 << i);
                tx_fifo_num = i;
                break;
            }

            if (tx_fifo_num == 0)
                return -1;

            aic_flush_txfifo(tx_fifo_num);
        }

        AIC_UDC_REG->inepcfg[ep_idx] |= (USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize) & DEPCTL_MPS_MASK) |
                                         ((uint32_t)USB_GET_ENDPOINT_TYPE(ep->bmAttributes) << 18) |
                                         (tx_fifo_num << 22) |
                                         DEPCTL_SETD0PID |
                                         DEPCTL_USBACTEP;
    }
    return 0;
}

int usbd_ep_close(uint8_t busid, const uint8_t ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);
    uint8_t tx_fifo_num = 0;
    int i = 0;
    #define DIS_EP_TIMOUT 100

    if (USB_EP_DIR_IS_OUT(ep)) {
        if (AIC_UDC_REG->outepcfg[ep_idx] & DEPCTL_EPENA) {
            /* (1) Wait for global nak to take effect */
            if (!(AIC_UDC_REG->usbintsts & INT_GOUTNAKEFF))
                AIC_UDC_REG->usbdevfunc |= USBDEVFUNC_SGOUTNAK;

            for (i = 0; i < DIS_EP_TIMOUT; i++) {
                if (AIC_UDC_REG->usbintsts & INT_GOUTNAKEFF)
                    break;
                aic_udelay(1);
            }

            if (i == DIS_EP_TIMOUT)
                USB_LOG_ERR("%s: timeout USBINTSTS.GOUTNAKEFF\n", __func__);

            /* (2) Disable ep */
            AIC_UDC_REG->outepcfg[ep_idx] |= DEPCTL_SNAK;
            AIC_UDC_REG->outepcfg[ep_idx] |= DEPCTL_EPDIS;

            for (i = 0; i < DIS_EP_TIMOUT; i++) {
                if (AIC_UDC_REG->outepint[ep_idx] & EPDISBLD)
                    break;
                aic_udelay(1);
            }

            if (i == DIS_EP_TIMOUT)
                USB_LOG_ERR("%s: timeout OUTEPCFG.EPDisable\n", __func__);

            /* Clear EPDISBLD interrupt */
            AIC_UDC_REG->outepint[ep_idx] |= EPDISBLD;

            /* (3) Remove global NAKs */
            AIC_UDC_REG->usbdevfunc |= USBDEVFUNC_CGOUTNAK;
        }

        AIC_UDC_REG->usbepintmsk &= ~(DAINT_OUT_MASK & (uint32_t)(1UL << (16 + ep_idx)));
        AIC_UDC_REG->outepcfg[ep_idx] = 0;
    } else {
        tx_fifo_num = (AIC_UDC_REG->inepcfg[ep_idx] & DEPCTL_TXFIFONUM_MASK) >> DEPCTL_TXFIFONUM_SHIFT;

        if (AIC_UDC_REG->inepcfg[ep_idx] & DEPCTL_EPENA) {
            if (tx_fifo_num) {
                /* (1) Wait for Nak effect */
                AIC_UDC_REG->inepcfg[ep_idx] |= DEPCTL_SNAK;

                for (i = 0; i < DIS_EP_TIMOUT; i++) {
                    if (AIC_UDC_REG->inepint[ep_idx] & INEP_NAKEFF)
                        break;
                    aic_udelay(1);
                }

                if (i == DIS_EP_TIMOUT)
                    USB_LOG_ERR("%s: timeout INEPINT.NAKEFF\n", __func__);
            } else {
                /* (1) Wait for Nak effect */
                AIC_UDC_REG->usbdevfunc |= USBDEVFUNC_SGNPINNAK;

                for (i = 0; i < DIS_EP_TIMOUT; i++) {
                    if (AIC_UDC_REG->usbintsts & INT_GINNAKEFF)
                        break;
                    aic_udelay(1);
                }

                if (i == DIS_EP_TIMOUT)
                    USB_LOG_ERR("%s: timeout USBINTSTS.GOUTNAKEFF\n", __func__);
            }

            /* (2) Disable ep */
            AIC_UDC_REG->inepcfg[ep_idx] |= DEPCTL_SNAK;
            AIC_UDC_REG->inepcfg[ep_idx] |= DEPCTL_EPDIS;

            for (i = 0; i < DIS_EP_TIMOUT; i++) {
                if (AIC_UDC_REG->inepint[ep_idx] & EPDISBLD)
                    break;
                aic_udelay(1);
            }

            if (i == DIS_EP_TIMOUT)
                USB_LOG_ERR("%s: timeout OUTEPCFG.EPDisable\n", __func__);

            /* Clear EPDISBLD interrupt */
            AIC_UDC_REG->inepint[ep_idx] |= EPDISBLD;

            /* (3) Clear Global In NP NAK in Shared FIFO for non periodic ep */
            if (!tx_fifo_num)
                AIC_UDC_REG->usbdevfunc |= USBDEVFUNC_CGNPINNAK;
        }

        AIC_UDC_REG->usbepintmsk &= ~(DAINT_OUT_MASK & (uint32_t)(1UL << ep_idx));
        AIC_UDC_REG->inepcfg[ep_idx] = 0;

        /* Flush TX FIFO */
        aic_flush_txfifo(tx_fifo_num);

        /* Period IN EP free fifo num */
        if (tx_fifo_num > 0)
            g_aic_udc.tx_fifo_map &= ~(1<<tx_fifo_num);
    }

#ifdef CONFIG_USB_AIC_DMA_ENABLE
    if (USB_EP_DIR_IS_OUT(ep)) {
        aic_udc_obuf_free(&g_aic_udc.out_ep[ep_idx]);
    } else {
        aic_udc_ibuf_free(&g_aic_udc.in_ep[ep_idx]);
    }
#endif

    return 0;
}

int usbd_ep_set_stall(uint8_t busid, const uint8_t ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (USB_EP_DIR_IS_OUT(ep)) {
        if (((AIC_UDC_REG->outepcfg[ep_idx] & DEPCTL_EPENA) == 0U) && (ep_idx != 0U)) {
            AIC_UDC_REG->outepcfg[ep_idx] &= ~(DEPCTL_EPDIS);
        }
        AIC_UDC_REG->outepcfg[ep_idx] |= DEPCTL_STALL;
    } else {
        if (((AIC_UDC_REG->inepcfg[ep_idx] & DEPCTL_EPENA) == 0U) && (ep_idx != 0U)) {
            AIC_UDC_REG->inepcfg[ep_idx] &= ~(DEPCTL_EPDIS);
        }
        AIC_UDC_REG->inepcfg[ep_idx] |= DEPCTL_STALL;
    }

#ifdef CONFIG_USB_AIC_DMA_ENABLE
    if (ep_idx == 0) {
        aic_ep0_start_read_setup((uint8_t *)&g_aic_udc.setup);
    }
#endif
    return 0;
}

int usbd_ep_clear_stall(uint8_t busid, const uint8_t ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (USB_EP_DIR_IS_OUT(ep)) {
        AIC_UDC_REG->outepcfg[ep_idx] &= ~DEPCTL_STALL;
        if ((g_aic_udc.out_ep[ep_idx].ep_type == USB_ENDPOINT_TYPE_INTERRUPT) ||
            (g_aic_udc.out_ep[ep_idx].ep_type == USB_ENDPOINT_TYPE_BULK)) {
            AIC_UDC_REG->outepcfg[ep_idx] |= DEPCTL_SETD0PID; /* DATA0 */
        }
    } else {
        AIC_UDC_REG->inepcfg[ep_idx] &= ~DEPCTL_STALL;
        if ((g_aic_udc.in_ep[ep_idx].ep_type == USB_ENDPOINT_TYPE_INTERRUPT) ||
            (g_aic_udc.in_ep[ep_idx].ep_type == USB_ENDPOINT_TYPE_BULK)) {
            AIC_UDC_REG->inepcfg[ep_idx] |= DEPCTL_SETD0PID; /* DATA0 */
        }
    }

    return 0;
}

int usbd_ep_is_stalled(uint8_t busid, const uint8_t ep, uint8_t *stalled)
{
    if (USB_EP_DIR_IS_OUT(ep)) {
    } else {
    }
    return 0;
}

int usbd_ep_start_write(uint8_t busid, const uint8_t ep, const uint8_t *data, uint32_t data_len)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);
    uint32_t pktcnt = 0;

    if (!data && data_len) {
        return -1;
    }
    if (AIC_UDC_REG->inepcfg[ep_idx] & DEPCTL_EPENA) {
        return -2;
    }
    if (ep_idx && !(AIC_UDC_REG->inepcfg[ep_idx] & DEPCTL_MPS_MASK)) {
        return -3;
    }
    if ((uint32_t)(uintptr_t)data & 0x03) {
        return -4;
    }

    g_aic_udc.in_ep[ep_idx].xfer_buf = (uint8_t *)data;
    g_aic_udc.in_ep[ep_idx].xfer_len = data_len;
    g_aic_udc.in_ep[ep_idx].actual_xfer_len = 0;

#ifdef CONFIG_USB_AIC_DMA_ENABLE
    if ((ep_idx != 0) && (data_len > 0) &&
        ((((uint32_t)(uintptr_t)data % CACHE_LINE_SIZE) != 0) ||
         (((uint32_t)(uintptr_t)(data + data_len) % CACHE_LINE_SIZE) != 0))) {

        if (g_aic_udc.in_ep[ep_idx].xfer_align_len != data_len) {
            int ret = 0;

            aic_udc_ibuf_free(&g_aic_udc.in_ep[ep_idx]);
            ret = aic_udc_ibuf_alloc(&g_aic_udc.in_ep[ep_idx], data_len);
            if (ret)
                return ret;
        }
        memcpy(g_aic_udc.in_ep[ep_idx].xfer_align_buf, data, data_len);
        data = g_aic_udc.in_ep[ep_idx].xfer_align_buf;
    } else {
        aic_udc_ibuf_free(&g_aic_udc.in_ep[ep_idx]);
    }

    if (data_len>0)
        aic_udc_dcache_clean((uintptr_t)data, ALIGN_UP(data_len, CACHE_LINE_SIZE));
#endif

    AIC_UDC_REG->ineptsfsiz[ep_idx] &= ~(DXEPTSIZ_PKT_CNT_MASK);
    AIC_UDC_REG->ineptsfsiz[ep_idx] &= ~(DXEPTSIZ_XFER_SIZE_MASK);
    AIC_UDC_REG->ineptsfsiz[ep_idx] &= ~(DXEPTSIZ_MULCNT_MASK);

    if (data_len == 0) {
        AIC_UDC_REG->ineptsfsiz[ep_idx] |= (DXEPTSIZ_PKT_CNT_MASK & (1U << 19));
        AIC_UDC_REG->inepcfg[ep_idx] |= (DEPCTL_CNAK | DEPCTL_EPENA);
        return 0;
    }

    if (ep_idx == 0) {
        if (data_len > g_aic_udc.in_ep[ep_idx].ep_mps) {
            data_len = g_aic_udc.in_ep[ep_idx].ep_mps;
        }
        g_aic_udc.in_ep[ep_idx].xfer_len = data_len;
        AIC_UDC_REG->ineptsfsiz[ep_idx] |= (DXEPTSIZ_PKT_CNT_MASK & (1U << 19));
        AIC_UDC_REG->ineptsfsiz[ep_idx] |= (DXEPTSIZ_XFER_SIZE_MASK & data_len);
    } else {
        pktcnt = (uint16_t)((data_len + g_aic_udc.in_ep[ep_idx].ep_mps - 1U) / g_aic_udc.in_ep[ep_idx].ep_mps);

        AIC_UDC_REG->ineptsfsiz[ep_idx] |= (DXEPTSIZ_PKT_CNT_MASK & (pktcnt << 19));
        AIC_UDC_REG->ineptsfsiz[ep_idx] |= (DXEPTSIZ_XFER_SIZE_MASK & data_len);
    }

    if ((g_aic_udc.in_ep[ep_idx].ep_type == USB_ENDPOINT_TYPE_ISOCHRONOUS) ||
        (g_aic_udc.in_ep[ep_idx].ep_type == USB_ENDPOINT_TYPE_INTERRUPT)) {
        AIC_UDC_REG->ineptsfsiz[ep_idx] |= (1<<DXEPTSIZ_MULCNT_SHIFT);
    }

    if (g_aic_udc.in_ep[ep_idx].ep_type == USB_ENDPOINT_TYPE_ISOCHRONOUS) {
        if ((AIC_UDC_REG->usblinests & (1U << 8)) == 0U) {
            AIC_UDC_REG->inepcfg[ep_idx] &= ~DEPCTL_SETD0PID;
            AIC_UDC_REG->inepcfg[ep_idx] |= DEPCTL_SETD1PID;
        } else {
            AIC_UDC_REG->inepcfg[ep_idx] &= ~DEPCTL_SETD1PID;
            AIC_UDC_REG->inepcfg[ep_idx] |= DEPCTL_SETD0PID;
        }
        AIC_UDC_REG->ineptsfsiz[ep_idx] &= ~(DXEPTSIZ_MULCNT_MASK);
        AIC_UDC_REG->ineptsfsiz[ep_idx] |= (1U << DXEPTSIZ_MULCNT_SHIFT);
    } else if (g_aic_udc.in_ep[ep_idx].ep_type == USB_ENDPOINT_TYPE_INTERRUPT) {
        AIC_UDC_REG->ineptsfsiz[ep_idx] &= ~(DXEPTSIZ_MULCNT_MASK);
        AIC_UDC_REG->ineptsfsiz[ep_idx] |= (1U << DXEPTSIZ_MULCNT_SHIFT);
    }

#ifdef CONFIG_USB_AIC_DMA_ENABLE
    AIC_UDC_REG->inepdmaaddr[ep_idx] = (uint32_t)(uintptr_t)data;
#endif

    AIC_UDC_REG->inepcfg[ep_idx] |= (DEPCTL_CNAK | DEPCTL_EPENA);

    return 0;
}

int usbd_ep_start_read(uint8_t busid, const uint8_t ep, uint8_t *data, uint32_t data_len)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);
    uint32_t pktcnt = 0;

    if (!data && data_len) {
        return -1;
    }
    if (AIC_UDC_REG->outepcfg[ep_idx] & DEPCTL_EPENA) {
        return -2;
    }
    if (ep_idx && !(AIC_UDC_REG->outepcfg[ep_idx] & DEPCTL_MPS_MASK)) {
        return -3;
    }
    if (((uint32_t)(uintptr_t)data) & 0x03) {
        return -4;
    }

    g_aic_udc.out_ep[ep_idx].xfer_buf = (uint8_t *)data;
    g_aic_udc.out_ep[ep_idx].xfer_len = data_len;
    g_aic_udc.out_ep[ep_idx].actual_xfer_len = 0;

#ifdef CONFIG_USB_AIC_DMA_ENABLE
    if ((ep_idx != 0) && (data_len > 0) &&
        ((((uint32_t)(uintptr_t)data % CACHE_LINE_SIZE) != 0) ||
         (((uint32_t)(uintptr_t)(data + data_len) % CACHE_LINE_SIZE) != 0))) {

        if (g_aic_udc.out_ep[ep_idx].xfer_align_len != data_len) {
            int ret = 0;

            aic_udc_obuf_free(&g_aic_udc.out_ep[ep_idx]);
            ret = aic_udc_obuf_alloc(&g_aic_udc.out_ep[ep_idx], data_len);
            if (ret)
                return ret;
        }
        data = g_aic_udc.out_ep[ep_idx].xfer_align_buf;
    } else {
        aic_udc_obuf_free(&g_aic_udc.out_ep[ep_idx]);
    }

    if (data_len > 0)
        aic_udc_dcache_invalidate((uintptr_t)data, ALIGN_UP(data_len, CACHE_LINE_SIZE));
#endif

    AIC_UDC_REG->outeptsfsiz[ep_idx] &= ~(DXEPTSIZ_PKT_CNT_MASK);
    AIC_UDC_REG->outeptsfsiz[ep_idx] &= ~(DXEPTSIZ_XFER_SIZE_MASK);
    if (data_len == 0) {
        AIC_UDC_REG->outeptsfsiz[ep_idx] |= (DXEPTSIZ_PKT_CNT_MASK & (1 << 19));
        AIC_UDC_REG->outeptsfsiz[ep_idx] |= (DXEPTSIZ_XFER_SIZE_MASK & g_aic_udc.out_ep[ep_idx].ep_mps);
        AIC_UDC_REG->outepcfg[ep_idx] |= (DEPCTL_CNAK | DEPCTL_EPENA);
        return 0;
    }

    if (ep_idx == 0) {
        if (data_len > g_aic_udc.out_ep[ep_idx].ep_mps) {
            data_len = g_aic_udc.out_ep[ep_idx].ep_mps;
        }
        g_aic_udc.out_ep[ep_idx].xfer_len = data_len;
        AIC_UDC_REG->outeptsfsiz[ep_idx] |= (DXEPTSIZ_PKT_CNT_MASK & (1U << 19));
        AIC_UDC_REG->outeptsfsiz[ep_idx] |= (DXEPTSIZ_XFER_SIZE_MASK & data_len);
    } else {
        pktcnt = (uint16_t)((data_len + g_aic_udc.out_ep[ep_idx].ep_mps - 1U) / g_aic_udc.out_ep[ep_idx].ep_mps);

        AIC_UDC_REG->outeptsfsiz[ep_idx] |= (DXEPTSIZ_PKT_CNT_MASK & (pktcnt << 19));
        AIC_UDC_REG->outeptsfsiz[ep_idx] |= (DXEPTSIZ_XFER_SIZE_MASK & data_len);
    }

#ifdef CONFIG_USB_AIC_DMA_ENABLE
    AIC_UDC_REG->outepdmaaddr[ep_idx] = (uint32_t)(uintptr_t)data;
#endif
    if (g_aic_udc.out_ep[ep_idx].ep_type == USB_ENDPOINT_TYPE_ISOCHRONOUS) {
        if ((AIC_UDC_REG->usblinests & (1U << 8)) == 0U) {
            AIC_UDC_REG->outepcfg[ep_idx] &= ~DEPCTL_SETD0PID;
            AIC_UDC_REG->outepcfg[ep_idx] |= DEPCTL_SETD1PID;
        } else {
            AIC_UDC_REG->outepcfg[ep_idx] &= ~DEPCTL_SETD1PID;
            AIC_UDC_REG->outepcfg[ep_idx] |= DEPCTL_SETD0PID;
        }
    }
    AIC_UDC_REG->outepcfg[ep_idx] |= (DEPCTL_CNAK | DEPCTL_EPENA);
    return 0;
}

void USBD_IRQHandler(void)
{
    uint32_t gint_status, ep_idx, ep_intr, epint, daintmask;
    gint_status = aic_get_glb_intstatus();

    /* Avoid spurious interrupt */
    if (gint_status == 0) {
        return;
    }

#ifndef CONFIG_USB_AIC_DMA_ENABLE
    uint32_t temp;
    uint32_t read_count;

    /* Handle RxQLevel Interrupt */
    if (gint_status & INT_RX_FIFO_NOT_EMPTY) {
        AIC_UDC_REG->usbintmsk &= ~(INT_RX_FIFO_NOT_EMPTY);

        temp = AIC_UDC_REG->rxfifosts_pop;
        ep_idx = temp & RXFIFOSTS_EPNUM_MASK;

        if ((temp & RXFIFOSTS_PKTSTS_MASK)  == PKTSTS_OUT_DATA_PKT_REC) {
            read_count = (temp & RXFIFOSTS_BCNT_MASK) >> 4;
            if (read_count != 0) {
                aic_ep_read(g_aic_udc.out_ep[ep_idx].xfer_buf, read_count);
                g_aic_udc.out_ep[ep_idx].xfer_buf += read_count;
            }
        } else if ((temp & RXFIFOSTS_PKTSTS_MASK) == PKTSTS_SETUP_DATA_PKT_REC) {
            read_count = (temp & RXFIFOSTS_BCNT_MASK) >> 4;
            aic_ep_read((uint8_t *)&g_aic_udc.setup, read_count);
        } else {
            /* ... */
        }
        AIC_UDC_REG->usbintmsk |= INT_RX_FIFO_NOT_EMPTY;
    }
#endif
    if (gint_status & INT_OUT_EP) {
        ep_idx = 0;
        ep_intr = aic_get_outeps_intstatus();
        while (ep_intr != 0U) {
            if ((ep_intr & 0x1U) != 0U) {
                epint = aic_get_outep_intstatus(ep_idx);
                uint32_t DoepintReg = AIC_UDC_REG->outepint[ep_idx];
                AIC_UDC_REG->outepint[ep_idx] = DoepintReg;

                struct aic_ep_state *ep = &g_aic_udc.out_ep[ep_idx];
                if ((epint & TRANSFER_DONE) == TRANSFER_DONE) {
                    #ifdef CONFIG_USB_AIC_DMA_ENABLE
                    if (ep->xfer_align_buf)
                        memcpy(ep->xfer_buf, ep->xfer_align_buf, ep->xfer_len);
                    #endif
                    if ((ep_idx == 0)) {
                        if (ep0_ctrl_stage == 1) {
                            ep0_ctrl_stage = 2;
                            usbd_event_ep0_setup_complete_handler(0, (uint8_t *)&g_aic_udc.setup);
                        } else {
                            if (ep->xfer_len == 0) {
                                /* Out status, start reading setup */
                                aic_ep0_start_read_setup((uint8_t *)&g_aic_udc.setup);
                            } else {
                                ep->actual_xfer_len = ep->xfer_len - ((AIC_UDC_REG->outeptsfsiz[ep_idx]) & DXEPTSIZ_XFER_SIZE_MASK);
                                ep->xfer_len = 0;
                                usbd_event_ep_out_complete_handler(0, 0x00, ep->actual_xfer_len);
                            }
                        }
                    } else {
                        ep->actual_xfer_len = ep->xfer_len - ((AIC_UDC_REG->outeptsfsiz[ep_idx]) & DXEPTSIZ_XFER_SIZE_MASK);
                        ep->xfer_len = 0;
                        usbd_event_ep_out_complete_handler(0, ep_idx, ep->actual_xfer_len);
                    }
                }

                if ((epint & CTRL_OUT_EP_SETUP_PHASE_DONE) == CTRL_OUT_EP_SETUP_PHASE_DONE) {
                    if (ep0_ctrl_stage == 1) {
                        ep0_ctrl_stage = 2;
                        usbd_event_ep0_setup_complete_handler(0, (uint8_t *)&g_aic_udc.setup);
                    }
                }
            }
            ep_intr >>= 1U;
            ep_idx++;
        }
    }

#ifndef CONFIG_USB_AIC_DMA_ENABLE
    if (gint_status & INT_NP_TX_FIFO_EMPTY) {
        AIC_UDC_REG->usbintmsk &= ~(INT_NP_TX_FIFO_EMPTY);
        aic_tx_fifo_empty_procecss(0);
    }
#endif

    if (gint_status & INT_IN_EP) {
        ep_idx = 0U;
        ep_intr = aic_get_ineps_intstatus();
        while (ep_intr != 0U) {
            if ((ep_intr & 0x1U) != 0U) {
                epint = aic_get_inep_intstatus(ep_idx);
                uint32_t DiepintReg = AIC_UDC_REG->inepint[ep_idx];
                AIC_UDC_REG->inepint[ep_idx] = DiepintReg;

                if ((epint & TRANSFER_DONE) == TRANSFER_DONE) {
                    if (ep_idx == 0) {
                        g_aic_udc.in_ep[ep_idx].actual_xfer_len = g_aic_udc.in_ep[ep_idx].xfer_len - ((AIC_UDC_REG->ineptsfsiz[ep_idx]) & DXEPTSIZ_XFER_SIZE_MASK);
                        g_aic_udc.in_ep[ep_idx].xfer_len = 0;
                        usbd_event_ep_in_complete_handler(0, 0x80, g_aic_udc.in_ep[ep_idx].actual_xfer_len);

                        if (g_aic_udc.setup.wLength && ((g_aic_udc.setup.bmRequestType & USB_REQUEST_DIR_MASK) == USB_REQUEST_DIR_OUT)) {
                            /* In status, start reading setup */
                            aic_ep0_start_read_setup((uint8_t *)&g_aic_udc.setup);
                        } else if (g_aic_udc.setup.wLength == 0) {
                            /* In status, start reading setup */
                            aic_ep0_start_read_setup((uint8_t *)&g_aic_udc.setup);
                        }
                    } else {
                        g_aic_udc.in_ep[ep_idx].actual_xfer_len = g_aic_udc.in_ep[ep_idx].xfer_len - ((AIC_UDC_REG->ineptsfsiz[ep_idx]) & DXEPTSIZ_XFER_SIZE_MASK);
                        g_aic_udc.in_ep[ep_idx].xfer_len = 0;
                        usbd_event_ep_in_complete_handler(0, ep_idx | 0x80, g_aic_udc.in_ep[ep_idx].actual_xfer_len);
                    }
                }

                #ifndef CONFIG_USB_AIC_DMA_ENABLE
                if ((epint & INTKN_TXFEMP) == INTKN_TXFEMP) {
                    aic_tx_fifo_empty_procecss(ep_idx);
                }
                #endif
            }
            ep_intr >>= 1U;
            ep_idx++;
        }
    }
    if (gint_status & INT_RESET) {
        AIC_UDC_REG->usbintsts |= INT_RESET;
        AIC_UDC_REG->usbdevfunc &= ~USBDEVFUNC_RMTWKUPSIG;

        usb_dc_rst();
    }

    if (gint_status & INT_ENUMDONE) {
        AIC_UDC_REG->usbintsts |= INT_ENUMDONE;
        aic_set_turnaroundtime(usbd_clk, aic_get_devspeed());

        AIC_UDC_REG->usbdevfunc |= USBDEVFUNC_CGNPINNAK;
    }
    if (gint_status & INT_INCOMP_ISO_OUT_INT) {
        daintmask = AIC_UDC_REG->usbepintmsk;
        daintmask >>= 16;

        for (ep_idx = 1; ep_idx < USB_NUM_BIDIR_ENDPOINTS; ep_idx++) {
            if ((BIT(ep_idx) & ~daintmask) || (g_aic_udc.out_ep[ep_idx].ep_type != USB_ENDPOINT_TYPE_ISOCHRONOUS))
                continue;
            if (!(AIC_UDC_REG->outepcfg[ep_idx] & DEPCTL_USBACTEP))
                continue;

            if ((AIC_UDC_REG->usblinests & (1U << 8)) != 0U) {
                AIC_UDC_REG->outepcfg[ep_idx] |= DEPCTL_SETD0PID;
                AIC_UDC_REG->outepcfg[ep_idx] &= ~DEPCTL_SETD1PID;
            } else {
                AIC_UDC_REG->outepcfg[ep_idx] &= ~DEPCTL_SETD0PID;
                AIC_UDC_REG->outepcfg[ep_idx] |= DEPCTL_SETD1PID;
            }
        }

        AIC_UDC_REG->usbintsts |= INT_INCOMP_ISO_OUT_INT;
    }

    if (gint_status & INT_INCOMP_ISO_IN_INT) {
        daintmask = AIC_UDC_REG->usbepintmsk;
        daintmask >>= 16;

        for (ep_idx = 1; ep_idx < USB_NUM_BIDIR_ENDPOINTS; ep_idx++) {
            if (((BIT(ep_idx) & ~daintmask)) || (g_aic_udc.in_ep[ep_idx].ep_type != USB_ENDPOINT_TYPE_ISOCHRONOUS))
                continue;

            if (!(AIC_UDC_REG->inepcfg[ep_idx] & DEPCTL_USBACTEP))
                continue;

            if ((AIC_UDC_REG->usblinests & (1U << 8)) != 0U) {
                AIC_UDC_REG->inepcfg[ep_idx] |= DEPCTL_SETD0PID;
                AIC_UDC_REG->inepcfg[ep_idx] &= ~DEPCTL_SETD1PID;
            } else {
                AIC_UDC_REG->inepcfg[ep_idx] &= ~DEPCTL_SETD0PID;
                AIC_UDC_REG->inepcfg[ep_idx] |= DEPCTL_SETD1PID;
            }
        }
        AIC_UDC_REG->usbintsts |= INT_INCOMP_ISO_IN_INT;
    }

    if (gint_status & INT_SOF) {
        AIC_UDC_REG->usbintsts |= INT_SOF;
    }
    if (gint_status & INT_SUSPEND) {
        AIC_UDC_REG->usbintsts |= INT_SUSPEND;
    }
    if (gint_status & INT_RESUME) {
        AIC_UDC_REG->usbintsts |= INT_RESUME;
    }
}
