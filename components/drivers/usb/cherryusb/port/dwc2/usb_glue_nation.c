/*
 * Copyright (c) 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbh_core.h"

__WEAK void USBD_IRQHandler(uint8_t busid)
{
}

__WEAK void USBH_IRQHandler(uint8_t busid)
{
}

#if defined(N32H473) || defined(N32H474) || defined(N32H475) || defined(N32H482) || defined(N32H487)
#include "n32h47x_48x_rcc.h"
#include "n32h47x_48x_gpio.h"
#include "misc.h"
#include "usb_dwc2_param.h"

typedef void (*usb_dwc2_irq)(uint8_t busid);

static usb_dwc2_irq g_usb_dwc2_irq;
static volatile uint8_t g_usb_dwc2_busid = 0;

static void usbhs_common_init(void)
{
    RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_GPIOA | RCC_AHB_PERIPHEN_GPIOB, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
#if (HSE_VALUE == 8000000)
    /* System PLL = 240 MHz; divide by 15 to produce 16 MHz USB PHY reference. */
    RCC_ConfigUSBPLLPresClk(RCC_USBPLLCLK_SRC_PLL, RCC_USBPLLCLK_DIV15);
    RCC_ConfigUSBHSBandwidth(RCC_USBHS_BW_16M);
    RCC_ConfigUSBHSFrequency(RCC_USBHS_FREQ_16_OR_32M);
    RCC_ConfigUSBHSClk(RCC_USBHS_CLKSRC_PLLPRES);
#else /* HSE 16 MHz — feed directly to USBHS */
    RCC_ConfigUSBHSBandwidth(RCC_USBHS_BW_16M);
    RCC_ConfigUSBHSFrequency(RCC_USBHS_FREQ_16_OR_32M);
    RCC_ConfigUSBHSClk(RCC_USBHS_CLKSRC_HSE);
#endif
    RCC_EnableAHBPeriphReset(RCC_AHBPRST_USBHSPHYRST);
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPHEN_USBHS, ENABLE);

    /* TX analog tuning for 8-bit UTMI PHY (N32H47x_48x USBHSCTRL2 layout). */
    RCC->USBHSCTRL2 = (RCC->USBHSCTRL2 & (~(0xF << 4))) | (0x5 << 4);   /* TX vref TUNE [7:4]        */
    RCC->USBHSCTRL2 = (RCC->USBHSCTRL2 & (~(0x3 << 12))) | (0x3 << 12); /* TX Rise TUNE [13:12]      */
    RCC->USBHSCTRL2 = (RCC->USBHSCTRL2 & (~(0x3 << 14))) | (0x3 << 14); /* TX Res TUNE  [15:14]      */
    RCC->USBHSCTRL2 = (RCC->USBHSCTRL2 & (~(0x3 << 16))) | (0x3 << 16); /* TX preempamp TUNE [17:16] */

    NVIC_InitType NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = USB_HS_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/* Override in the board layer to configure USB DM/DP alternate-function pins.
 * In host mode, also drive any VBUS power-switch GPIO here (e.g. board/ports/usb_gpio.c). */
__weak void n32h47x_48x_usbhs_gpio_init(void)
{
}

void usb_dc_low_level_init(uint8_t busid)
{
    g_usb_dwc2_irq = USBD_IRQHandler;
    g_usb_dwc2_busid = busid;

    n32h47x_48x_usbhs_gpio_init();
    usbhs_common_init();

    RCC->USBHSCTRL2 |= (uint32_t)0x01 << 19;
    RCC->USBHSCTRL1 |= (uint32_t)0x01 << 31;
}

void usb_dc_low_level_deinit(uint8_t busid)
{
    NVIC_InitType NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = USB_HS_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStructure);

    RCC_EnableAHBPeriphReset(RCC_AHBPRST_USBHSPHYRST);
    /* Disable the USBHS peripheral clock. */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPHEN_USBHS, DISABLE);
}

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    g_usb_dwc2_irq = USBH_IRQHandler;
    g_usb_dwc2_busid = 0;

    n32h47x_48x_usbhs_gpio_init();
    usbhs_common_init();

    RCC->USBHSCTRL2 &= ~(uint32_t)0x01 << 19;
    RCC->USBHSCTRL1 |= (uint32_t)0x01 << 31;
}

void usb_hc_low_level_deinit(struct usbh_bus *bus)
{
    NVIC_InitType NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = USB_HS_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStructure);

    RCC_EnableAHBPeriphReset(RCC_AHBPRST_USBHSPHYRST);
    /* Disable the USBHS peripheral clock. */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPHEN_USBHS, DISABLE);
}

uint32_t usbd_get_dwc2_gccfg_conf(uint32_t reg_base)
{
    return 0;
}

uint32_t usbh_get_dwc2_gccfg_conf(uint32_t reg_base)
{
    return 0;
}

void USB_HS_IRQHandler(void)
{
    g_usb_dwc2_irq(g_usb_dwc2_busid);
}

void usbd_dwc2_delay_ms(uint8_t ms)
{
    RCC_ClocksType RCC_clocks = { 0 };

    RCC_GetClocksFreqValue(&RCC_clocks);

    uint32_t count = RCC_clocks.SysclkFreq / 1000 * ms;
    while (count--) {
        __asm volatile("nop");
    }
}

uint32_t usbd_dwc2_get_system_clock(void)
{
    RCC_ClocksType RCC_clocks = { 0 };

    RCC_GetClocksFreqValue(&RCC_clocks);
    return RCC_clocks.SysclkFreq;
}

/*
 * N32H47x_48x USBHS has 4 KB (1024 x 32-bit words) of dedicated FIFO RAM;
 * GRXFSIZ.RXFDEP max = 1024.
 *
 * Internal HS UTMI+ PHY, 8-bit data bus (GCFG.PHYIF = 0).
 * PHY is configured via RCC USBHSCTRL registers, not DWC2 GCCFG,
 * so device_gccfg / host_gccfg are both zero.
 *
 * Device FIFO layout (1024 words, 4096 bytes):
 *   RX shared        512 words  (2048 bytes)
 *   EP0 IN TX         64 words  ( 256 bytes) — control
 *   EP1 IN TX        256 words  (1024 bytes) — bulk / isochronous HS
 *   EP2 IN TX         64 words  ( 256 bytes)
 *   EP3 IN TX         64 words  ( 256 bytes)
 *   EP4 IN TX         64 words  ( 256 bytes)
 *   Total           1024 words  (4096 bytes)
 *
 * Host FIFO layout (1024 words, 4096 bytes):
 *   RX              512 words  (2048 bytes)
 *   Non-periodic TX 256 words  (1024 bytes)
 *   Periodic TX     256 words  (1024 bytes)
 *   Total          1024 words  (4096 bytes)
 *
 */
static const struct dwc2_user_params param_n32h47x_48x = {
    /* Built-in HS UTMI+ PHY; sets GUSBCFG.ULPI_UTMI_SEL = 0. */
    .phy_type = DWC2_PHY_TYPE_PARAM_UTMI,

    /* 8-bit UTMI data bus (USBHS_GCFG.PHYIF = 0).
     * USB_CoreInit() in usbhs_core.c explicitly clears PHYIF.
     * CherryUSB only sets GUSBCFG.PHYIF16 when this field == 16. */
    .phy_utmi_width = 8,

/* Slave mode vs DMA mode; controlled by CONFIG_USB_DWC2_DMA_ENABLE.
     * DMA mode frees the CPU from FIFO polling but requires aligned buffers. */
#ifdef CONFIG_USB_DWC2_DMA_ENABLE
    .device_dma_enable = true,
#else
    .device_dma_enable = false,
#endif

    /* Scatter-Gather descriptor DMA: not supported by this hardware
     * (GHWCFG4.DESC_DMA_ENABLED = 0). */
    .device_dma_desc_enable = false,

    /* Shared RX FIFO depth for device mode, in 32-bit words.
     * All OUT endpoints and SETUP packets share this single FIFO.
     * Minimum formula:
     *   RX >= (5*ctrl_eps + 8) + (max_pkt/4 + 1) + (2*OUT_eps) + 1
     *   With HS MPS=512 and 7 OUT eps: (5+8) + (129) + (14) + 1 = 157 words min.
     * 512 words (2048 bytes) matches Nations CDC demo (RX_FIFO_HS_SIZE=512).
     * Hardware limit: GRXFSIZ.RXFDEP max = 1024.
     * To redistribute, define CONFIG_USB_DWC2_CUSTOM_FIFO; keep total <= 1024. */
    .device_rx_fifo_size = 512,

    /* Per-IN-endpoint dedicated TX FIFO depths, in 32-bit words.
     * Index matches endpoint number: [0]=EP0, [1]=EP1, ..., [8]=EP8.
     * N32H47x_48x has EP0 (control) + EP1..EP8 (IN); [9]..[15] unused.
     *
     * Current allocation (512 words TX + 512 words RX = 1024 words total):
     *   [0] EP0:  64 words (256 bytes) -- control, buffers 4x 64-byte HS packets.
     *             Matches Nations TX0_FIFO_HS_SIZE = 64.
     *   [1] EP1: 256 words (1024 bytes) -- primary HS bulk/isochronous endpoint.
     *             Double-buffers one HS bulk packet (512 bytes max).
     *             Matches Nations TX1_FIFO_HS_SIZE = 256.
     *   [2] EP2:  64 words (256 bytes) -- interrupt or secondary bulk.
     *   [3] EP3:  64 words (256 bytes) -- same.
     *   [4] EP4:  64 words (256 bytes) -- same.
     *   [5]..[8]: 0 -- EP5..EP8 unallocated by default.
     *             Use CONFIG_USB_DWC2_CUSTOM_FIFO to add more IN endpoints;
     *             sum of all TX entries must stay <= (1024 - device_rx_fifo_size).
     * Per-FIFO hardware limit: INEPTXFDEP max = 768 words. */
    .device_tx_fifo_size = {
        [0] = 64,  /* EP0:  256 bytes, control */
        [1] = 256, /* EP1: 1024 bytes, HS bulk/iso primary */
        [2] = 64,  /* EP2:  256 bytes */
        [3] = 64,  /* EP3:  256 bytes */
        [4] = 64,  /* EP4:  256 bytes */
        [5] = 0,   /* EP5..EP8: unallocated, use CUSTOM_FIFO to enable */
        [6] = 0,
        [7] = 0,
        [8] = 0,
        [9] = 0, /* [9]..[15]: invalid for N32H47x_48x (only EP0..EP8 exist) */
        [10] = 0,
        [11] = 0,
        [12] = 0,
        [13] = 0,
        [14] = 0,
        [15] = 0,
    },

    /* Host descriptor DMA: not supported, same reason as device_dma_desc_enable. */
    .host_dma_desc_enable = false,

    /* Host mode shared RX FIFO depth, in 32-bit words.
     * All host channel IN data shares this single FIFO.
     * Minimum formula:
     *   Host RX >= (max_pkt/4 + 1) + 1
     *   With HS MPS=1024: (256 + 1) + 1 = 258 words min.
     * 512 words matches Nations Host demo (RX_FIFO_HS_SIZE=512). */
    .host_rx_fifo_size = 512,

    /* Host non-periodic TX FIFO depth (control + bulk OUT), in 32-bit words.
     * Recommended >= max_nonperiodic_pkt/4; double for pipelining.
     *   HS MPS=512: 512/4 = 128 words min; 256 words provides double-buffering.
     * Matches Nations Host demo (TXH_NP_HS_FIFOSIZE=256).
     * Hardware limit: NPTXFDEP max = 1024. */
    .host_nperio_tx_fifo_size = 256,

    /* Host periodic TX FIFO depth (interrupt + isochronous OUT), in 32-bit words.
     * Recommended >= max_periodic_pkt/4; double for isochronous.
     *   HS iso MPS=1024: 1024/4 = 256 words min.
     * Matches Nations Host demo (TXH_P_HS_FIFOSIZE=256).
     * Host FIFO total: 512 + 256 + 256 = 1024 words, fills the 4 KB RAM exactly. */
    .host_perio_tx_fifo_size = 256,

    /* Extra bits OR'd into GCCFG for device mode.
     * Some DWC2 platforms use GCCFG to enable VBUS sensing via an external PHY.
     * N32H47x_48x PHY is controlled through RCC USBHSCTRL1/2, not GCCFG,
     * so no additional bits are needed. */
    .device_gccfg = 0,

    /* Same as device_gccfg but applied in host mode. */
    .host_gccfg = 0,

    /* Set to true to bypass VBUS hardware sensing on boards that do not route
     * USB VBUS to a GPIO sense pin.  false = rely on hardware VBUS detection. */
    .b_session_valid_override = true,

    /* Total FIFO RAM depth, in 32-bit words.
     * CherryUSB asserts at init: device_rx + sum(device_tx) <= total_fifo_size.
     * N32H47x_48x has 4 KB dedicated FIFO RAM = 1024 x 32-bit words;
     * GRXFSIZ.RXFDEP max = 1024. */
    .total_fifo_size = 1024,
};

#ifndef CONFIG_USB_DWC2_CUSTOM_PARAM
void dwc2_get_user_params(uint32_t reg_base, struct dwc2_user_params *params)
{
    memcpy(params, &param_n32h47x_48x, sizeof(struct dwc2_user_params));
#ifdef CONFIG_USB_DWC2_CUSTOM_FIFO
    struct usb_dwc2_user_fifo_config s_dwc2_fifo_config;

    dwc2_get_user_fifo_config(reg_base, &s_dwc2_fifo_config);

    params->device_rx_fifo_size = s_dwc2_fifo_config.device_rx_fifo_size;
    for (uint8_t i = 0; i < MAX_EPS_CHANNELS; i++) {
        params->device_tx_fifo_size[i] = s_dwc2_fifo_config.device_tx_fifo_size[i];
    }
#endif /* CONFIG_USB_DWC2_CUSTOM_FIFO */
}
#endif /* CONFIG_USB_DWC2_CUSTOM_PARAM */

#elif defined(N32H49X)

/*
 * N32H49x series: single USBHS controller, internal HS UTMI+ PHY (8-bit bus).
 *
 * FIFO RAM: 4 KB (1024 x 32-bit words).
 * USBHS base address: 0x40040000 (AHBPERIPH_BASE + 0x20000).
 * IRQ: USB_HS_IRQn (62), USB_HS_WKUP_IRQn (84).
 */

#include "n32h49x_rcc.h"
#include "n32h49x_gpio.h"
#include "misc.h"
#include "usb_dwc2_param.h"

typedef void (*usb_dwc2_irq)(uint8_t busid);

static usb_dwc2_irq g_usb_dwc2_irq;
static volatile uint8_t g_usb_dwc2_busid = 0;

static void usbhs_common_init(void)
{
    RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_GPIOA | RCC_AHB_PERIPHEN_GPIOB, ENABLE);
#if (HSE_VALUE == 8000000)
    /* System PLL = 240 MHz; divide by 15 to produce 16 MHz USB PHY reference. */
    RCC_ConfigUSBPLLPresClk(RCC_USBPLLCLK_SRC_PLL, RCC_USBPLLCLK_DIV15);
    RCC_ConfigUSBHSBandwidth(RCC_USBHS_BW_16M);
    RCC_ConfigUSBHSFrequency(RCC_USBHS_FREQ_16_OR_32M);
    RCC_ConfigUSBHSClk(RCC_USBHS_CLKSRC_PLLPRES);
#else /* HSE 16 MHz — feed directly to USBHS */
    RCC_ConfigUSBHSBandwidth(RCC_USBHS_BW_16M);
    RCC_ConfigUSBHSFrequency(RCC_USBHS_FREQ_16_OR_32M);
    RCC_ConfigUSBHSClk(RCC_USBHS_CLKSRC_HSE);
#endif
    RCC_EnableAHBPeriphReset(RCC_AHBPRST_USBHSPHYRST);
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPHEN_USBHS, ENABLE);

    /* TX analog tuning for 8-bit UTMI PHY (N32H49x USBHSCTRL layout). */
    RCC->USBHSCTRL2 = (RCC->USBHSCTRL2 & (~(0xF << 4))) | (0xB << 4);   /* HDCVTRIM[7:4]              */
    RCC->USBHSCTRL1 = (RCC->USBHSCTRL1 & (~(0x7 << 12))) | (0x5 << 12); /* USBHSCTRL1[14:12]          */
    RCC->USBHSCTRL2 = (RCC->USBHSCTRL2 & (~(0x3 << 12))) | (0x0 << 14); /* RFTRIM[13:12] = 0 (clear)  */
    RCC->USBHSCTRL2 = (RCC->USBHSCTRL2 & (~(0x3 << 16))) | (0x1 << 16); /* USBHSCTRL2[17:16]          */

    NVIC_InitType NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = USB_HS_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/* Override in the board layer to configure USB DM/DP alternate-function pins.
 * In host mode, also drive any VBUS power-switch GPIO here (e.g. board/ports/usb_gpio.c). */
__weak void n32h49x_usbhs_gpio_init(void)
{
}

void usb_dc_low_level_init(uint8_t busid)
{
    g_usb_dwc2_irq = USBD_IRQHandler;
    g_usb_dwc2_busid = busid;

    n32h49x_usbhs_gpio_init();
    usbhs_common_init();

    RCC->USBHSCTRL2 |= (uint32_t)0x01 << 19;
    RCC->USBHSCTRL1 |= (uint32_t)0x01 << 31;
}

void usb_dc_low_level_deinit(uint8_t busid)
{
    NVIC_InitType NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = USB_HS_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStructure);

    RCC_EnableAHBPeriphReset(RCC_AHBPRST_USBHSPHYRST);
    /* Disable the USBHS peripheral clock. */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPHEN_USBHS, DISABLE);
}

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    g_usb_dwc2_irq = USBH_IRQHandler;
    g_usb_dwc2_busid = 0;

    n32h49x_usbhs_gpio_init();
    usbhs_common_init();

    RCC->USBHSCTRL2 &= ~(uint32_t)0x01 << 19;
    RCC->USBHSCTRL1 |= (uint32_t)0x01 << 31;
}

void usb_hc_low_level_deinit(struct usbh_bus *bus)
{
    NVIC_InitType NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = USB_HS_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStructure);

    RCC_EnableAHBPeriphReset(RCC_AHBPRST_USBHSPHYRST);
    /* Disable the USBHS peripheral clock. */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPHEN_USBHS, DISABLE);
}

uint32_t usbd_get_dwc2_gccfg_conf(uint32_t reg_base)
{
    return 0;
}

uint32_t usbh_get_dwc2_gccfg_conf(uint32_t reg_base)
{
    return 0;
}

void USB_HS_IRQHandler(void)
{
    g_usb_dwc2_irq(g_usb_dwc2_busid);
}

void usbd_dwc2_delay_ms(uint8_t ms)
{
    RCC_ClocksType RCC_clocks = { 0 };

    RCC_GetClocksFreqValue(&RCC_clocks);
    uint32_t count = RCC_clocks.SysclkFreq / 1000U * ms;
    while (count--) {
        __asm volatile("nop");
    }
}

uint32_t usbd_dwc2_get_system_clock(void)
{
    RCC_ClocksType RCC_clocks = { 0 };

    RCC_GetClocksFreqValue(&RCC_clocks);
    return RCC_clocks.SysclkFreq;
}

/*
 * N32H49x USBHS has 4 KB (1024 x 32-bit words) of dedicated FIFO RAM.
 *
 * Internal HS UTMI+ PHY, 8-bit data bus (GCFG.PHYIF = 0).
 * PHY is configured via RCC USBHSCTRL1/2, not DWC2 GCCFG,
 * so device_gccfg / host_gccfg are both zero.
 *
 * FIFO layout matches N32H47x_48x CDC demo (same FIFO sizes confirmed):
 *   RX shared        512 words  (2048 bytes)
 *   EP0 IN TX         64 words  ( 256 bytes)
 *   EP1 IN TX        256 words  (1024 bytes)
 *   EP2 IN TX         64 words  ( 256 bytes)
 *   EP3 IN TX         64 words  ( 256 bytes)
 *   EP4 IN TX         64 words  ( 256 bytes)
 *   Total           1024 words  (4096 bytes)
 *
 * Host FIFO layout:
 *   RX              512 words  (2048 bytes)
 *   Non-periodic TX 256 words  (1024 bytes)
 *   Periodic TX     256 words  (1024 bytes)
 *   Total          1024 words  (4096 bytes)
 */
static const struct dwc2_user_params param_n32h49x = {
    .phy_type = DWC2_PHY_TYPE_PARAM_UTMI,

    /* 8-bit UTMI data bus (GCFG.PHYIF = 0).
     * USB_CoreInit() in usbhs_core.c explicitly clears PHYIF. */
    .phy_utmi_width = 8,

#ifdef CONFIG_USB_DWC2_DMA_ENABLE
    .device_dma_enable = true,
#else
    .device_dma_enable = false,
#endif

    /* Scatter-Gather descriptor DMA: not supported (GHWCFG4.DESC_DMA_ENABLED = 0). */
    .device_dma_desc_enable = false,

    /* Shared RX FIFO: 512 words (2048 bytes). */
    .device_rx_fifo_size = 512,

    .device_tx_fifo_size = {
        [0] = 64,  /* EP0:  256 bytes, control */
        [1] = 256, /* EP1: 1024 bytes, HS bulk/iso primary */
        [2] = 64,  /* EP2:  256 bytes */
        [3] = 64,  /* EP3:  256 bytes */
        [4] = 64,  /* EP4:  256 bytes */
        [5] = 0,   /* EP5..EP8: unallocated, use CUSTOM_FIFO to enable */
        [6] = 0,
        [7] = 0,
        [8] = 0,
        [9] = 0, /* [9]..[15]: invalid for N32H49x (only EP0..EP8 exist) */
        [10] = 0,
        [11] = 0,
        [12] = 0,
        [13] = 0,
        [14] = 0,
        [15] = 0,
    },

    /* Host descriptor DMA: not supported, same reason as device_dma_desc_enable. */
    .host_dma_desc_enable = false,

    /* Host RX: 512 words (2048 bytes). */
    .host_rx_fifo_size = 512,

    /* Host non-periodic TX (control + bulk OUT): 256 words (1024 bytes). */
    .host_nperio_tx_fifo_size = 256,

    /* Host periodic TX (interrupt + iso OUT): 256 words.
     * Host FIFO total: 512 + 256 + 256 = 1024 words, fills 4 KB RAM exactly. */
    .host_perio_tx_fifo_size = 256,

    /* N32H49x PHY is controlled through RCC USBHSCTRL1/2, not DWC2 GCCFG. */
    .device_gccfg = 0,
    .host_gccfg = 0,

    /* Set to true to bypass VBUS hardware sensing on boards that do not route
     * USB VBUS to a GPIO sense pin.  false = rely on hardware VBUS detection. */
    .b_session_valid_override = true,

    /* 4 KB dedicated FIFO RAM = 1024 x 32-bit words. */
    .total_fifo_size = 1024,
};

#ifndef CONFIG_USB_DWC2_CUSTOM_PARAM
void dwc2_get_user_params(uint32_t reg_base, struct dwc2_user_params *params)
{
    memcpy(params, &param_n32h49x, sizeof(struct dwc2_user_params));
#ifdef CONFIG_USB_DWC2_CUSTOM_FIFO
    struct usb_dwc2_user_fifo_config s_dwc2_fifo_config;

    dwc2_get_user_fifo_config(reg_base, &s_dwc2_fifo_config);

    params->device_rx_fifo_size = s_dwc2_fifo_config.device_rx_fifo_size;
    for (uint8_t i = 0; i < MAX_EPS_CHANNELS; i++) {
        params->device_tx_fifo_size[i] = s_dwc2_fifo_config.device_tx_fifo_size[i];
    }
#endif /* CONFIG_USB_DWC2_CUSTOM_FIFO */
}
#endif /* CONFIG_USB_DWC2_CUSTOM_PARAM */

#elif defined(N32H73x) || defined(N32H76x) || defined(N32H73x_76x) || defined(N32H78x)

/*
 * N32H7xx series: dual USBHS controllers (USBHS1 + USBHS2).
 *
 * Each controller is a DWC2 IP core with an internal HS UTMI+ PHY
 * accessed through a Wrapper register block (WRPCFG / WRPCTRL).
 * The PHY uses a 16-bit UTMI data bus (GCFG.PHYIF = 1).
 *
 * Controller base addresses:
 *   USBHS1 core:    0x40100000    wrapper: 0x40140000
 *   USBHS2 core:    0x40060000    wrapper: 0x400A0000
 *
 * busid convention used by this glue layer:
 *   busid 0 -> USBHS1  (PA11=DM, PA12=DP, USB1_HS_IRQn, EXTI_LINE62)
 *   busid 1 -> USBHS2  (PB14=DM, PB15=DP, USB2_HS_IRQn, EXTI_LINE63)
 *
 * For usb_hc_low_level_init the controller is identified by bus->hcd.reg_base
 * rather than busid to avoid aliasing with the device busid namespace in
 * dual-USB (one host + one device) configurations.
 *
 * Both controllers share identical DWC2 hardware parameters and
 * 4 KB (1024-word) dedicated FIFO RAM.
 */

#include "n32h7xx_rcc.h"
#include "n32h7xx_gpio.h"
#include "n32h7xx_pwr.h"
#include "misc.h"
#include "n32h7xx.h"
#include "usb_dwc2_param.h"

#define N32H7XX_USBHS1_BASE 0x40100000U
#define N32H7XX_USBHS2_BASE 0x40060000U
#define N32H7XX_USBHS1_WRAP 0x40140000U
#define N32H7XX_USBHS2_WRAP 0x400A0000U

typedef void (*usb_dwc2_irq_fn)(uint8_t busid);

/* Per-controller IRQ dispatch: index 0 = USBHS1, index 1 = USBHS2. */
static struct
{
    usb_dwc2_irq_fn fn;
    uint8_t busid;
} g_n32h7xx_irq[2];

void usbd_dwc2_delay_ms(uint8_t ms)
{
    RCC_ClocksTypeDef RCC_Clocks = { 0 };

    RCC_GetClocksFreqValue(&RCC_Clocks);
    uint32_t count = RCC_Clocks.SysClkFreq / 1000U * ms;
    while (count--) {
        __asm volatile("nop");
    }
}

uint32_t usbd_dwc2_get_system_clock(void)
{
    RCC_ClocksTypeDef RCC_Clocks = { 0 };

    RCC_GetClocksFreqValue(&RCC_Clocks);
    return RCC_Clocks.SysClkFreq;
}

/*
 * Wrapper register init: configure PHY PLL clock source, enable PLL,
 * set IDSIG (device/host role), enable ID-pin detection, then pulse
 * the PHY power-on reset.
 *
 * IDSIG MUST be set here, before USB_CoreInit() runs.
 * USB_CoreInitHost() does NOT clear IDSIG, so if left at 1 the host
 * controller cannot operate.  When two controllers run simultaneously
 * (one host + one device) failing to clear IDSIG on the host is the
 * root cause of host malfunction.
 *
 * is_device: true  -> IDSIG = 1 (device role)
 *            false -> IDSIG = 0 (host role)
 * is_usbhs1: selects the RCC PHY reset register (AHB2 vs AHB1).
 */
static void n32h7xx_wrapper_init(uint32_t wrap_base, bool is_device, bool is_usbhs1)
{
    USB_Wrapper_Registers *wrap = (USB_Wrapper_Registers *)wrap_base;
    uint32_t wrpcfg;
    uint32_t wrpctrl;

    wrpcfg = wrap->WRPCFG;
    wrpcfg &= ~USBHS_WRPCFG_PHYCLKSEL;

#if (HSE_VALUE == 10000000U)
    wrpcfg |= USBHS_WRPCFG_PHYCLKSEL_10M;
#elif (HSE_VALUE == 12000000U)
    wrpcfg |= USBHS_WRPCFG_PHYCLKSEL_12M;
#elif (HSE_VALUE == 19200000U)
    wrpcfg |= USBHS_WRPCFG_PHYCLKSEL_19_2M;
#elif (HSE_VALUE == 24000000U)
    wrpcfg |= USBHS_WRPCFG_PHYCLKSEL_24M;
#elif (HSE_VALUE == 25000000U)
    wrpcfg |= USBHS_WRPCFG_PHYCLKSEL_25M;
#elif (HSE_VALUE == 27000000U)
    wrpcfg |= USBHS_WRPCFG_PHYCLKSEL_27M;
#elif (HSE_VALUE == 30000000U)
    wrpcfg |= USBHS_WRPCFG_PHYCLKSEL_30M;
#elif (HSE_VALUE == 40000000U)
    wrpcfg |= USBHS_WRPCFG_PHYCLKSEL_40M;
#else
#error "Unsupported HSE_VALUE for N32H7xx USBHS PHY. Supported: 10/12/19.2/24/25/27/30/40 MHz."
#endif

    wrpcfg |= USBHS_WRPCFG_PLLEN;

    if (is_device) {
        wrpcfg |= USBHS_WRPCFG_IDSIG;
    } else {
        wrpcfg &= ~USBHS_WRPCFG_IDSIG;
    }

    wrap->WRPCFG = wrpcfg;

    wrpctrl = wrap->WRPCTRL;
    wrpctrl |= USBHS_WRPCTRL_PINDETEN;
    wrap->WRPCTRL = wrpctrl;

    if (is_usbhs1) {
        RCC_EnableAHB2PeriphReset1(RCC_AHB2_PERIPHRST_USB1POR);
    } else {
        RCC_EnableAHB1PeriphReset1(RCC_AHB1_PERIPHRST_USB2POR);
    }

    usbd_dwc2_delay_ms(1);
}

/* -----------------------------------------------------------------------
 * GPIO init: weak stubs — override in your board layer.
 * Implement n32h7xx_usbhs1_gpio_init / n32h7xx_usbhs2_gpio_init to configure
 * the DM/DP pins (and optionally SOF/ID) for your specific board.
 * In host mode, also drive any VBUS power-switch GPIO here.
 * ----------------------------------------------------------------------- */
__weak void n32h7xx_usbhs1_gpio_init(void)
{
}
__weak void n32h7xx_usbhs2_gpio_init(void)
{
}

/* -----------------------------------------------------------------------
 * NVIC + init
 * ----------------------------------------------------------------------- */
static void n32h7xx_usbhs1_irq_enable(void)
{
    NVIC_InitType nvic;

    nvic.NVIC_IRQChannel = USB1_HS_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 3;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
}

static void n32h7xx_usbhs2_irq_enable(void)
{
    NVIC_InitType nvic;

    nvic.NVIC_IRQChannel = USB2_HS_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 3;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
}

/* -----------------------------------------------------------------------
 * Per-controller hardware bringup
 * ----------------------------------------------------------------------- */
static void n32h7xx_usbhs1_hw_init(uint8_t busid, usb_dwc2_irq_fn irq_fn)
{
    /* AFIO alternate-function remapping clock */
    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_M7_AFIO, ENABLE);

    n32h7xx_usbhs1_gpio_init();

    /* Route HSE directly to the USB PHY reference clock input.
     * HSE must already be running (done by system clock init).
     * PHYCLKSEL in WRPCFG must match the resulting frequency. */
    RCC_ConfigUSBRefClk(RCC_USBREFCLK_HSE_DIV1);

    /* PWR peripheral clock is required before calling PWR_MoudlePowerEnable. */
    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_PWR, ENABLE);

    /* Enable USBHS1 peripheral clock (AHB2). */
    RCC_EnableAHB2PeriphClk1(RCC_AHB2_PERIPHEN_M7_USB1, ENABLE);

    /* Power up the USBHS1 hardware module.  Without this the USB core
     * registers are inaccessible and the PHY will not start. */
    PWR_MoudlePowerEnable(HSC1_USB1_PWRCTRL, ENABLE);

    g_n32h7xx_irq[0].fn = irq_fn;
    g_n32h7xx_irq[0].busid = busid;
    n32h7xx_usbhs1_irq_enable();
}

static void n32h7xx_usbhs2_hw_init(uint8_t busid, usb_dwc2_irq_fn irq_fn)
{
    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_M7_AFIO, ENABLE);

    n32h7xx_usbhs2_gpio_init();

    RCC_ConfigUSBRefClk(RCC_USBREFCLK_HSE_DIV1);

    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_PWR, ENABLE);

    /* Enable USBHS2 peripheral clock (AHB1). */
    RCC_EnableAHB1PeriphClk1(RCC_AHB1_PERIPHEN_M7_USB2, ENABLE);

    /* Power up the USBHS2 hardware module. */
    PWR_MoudlePowerEnable(HSC2_USB2_PWRCTRL, ENABLE);

    g_n32h7xx_irq[1].fn = irq_fn;
    g_n32h7xx_irq[1].busid = busid;
    n32h7xx_usbhs2_irq_enable();
}

/* -----------------------------------------------------------------------
 * Device mode
 * ----------------------------------------------------------------------- */
void usb_dc_low_level_init(uint8_t busid)
{
    /* Identify the controller by reg_base, not busid.
     * busid is a user-assigned index and does not imply a fixed controller mapping. */
    if (g_usbdev_bus[busid].reg_base == N32H7XX_USBHS1_BASE) {
        n32h7xx_usbhs1_hw_init(busid, USBD_IRQHandler);
        n32h7xx_wrapper_init(N32H7XX_USBHS1_WRAP, true, true);
    } else {
        n32h7xx_usbhs2_hw_init(busid, USBD_IRQHandler);
        n32h7xx_wrapper_init(N32H7XX_USBHS2_WRAP, true, false);
    }
}

void usb_dc_low_level_deinit(uint8_t busid)
{
    NVIC_InitType nvic;

    if (g_usbdev_bus[busid].reg_base == N32H7XX_USBHS1_BASE) {
        nvic.NVIC_IRQChannel = USB1_HS_IRQn;
        nvic.NVIC_IRQChannelCmd = DISABLE;
        NVIC_Init(&nvic);
        RCC_EnableAHB2PeriphReset1(RCC_AHB2_PERIPHRST_USB1POR);
        RCC_EnableAHB2PeriphClk1(RCC_AHB2_PERIPHEN_M7_USB1, DISABLE);
    } else {
        nvic.NVIC_IRQChannel = USB2_HS_IRQn;
        nvic.NVIC_IRQChannelCmd = DISABLE;
        NVIC_Init(&nvic);
        RCC_EnableAHB1PeriphReset1(RCC_AHB1_PERIPHRST_USB2POR);
        RCC_EnableAHB1PeriphClk1(RCC_AHB1_PERIPHEN_M7_USB2, DISABLE);
    }
}

/* -----------------------------------------------------------------------
 * Host mode
 * ----------------------------------------------------------------------- */
void usb_hc_low_level_init(struct usbh_bus *bus)
{
    if (bus->hcd.reg_base == N32H7XX_USBHS1_BASE) {
        n32h7xx_usbhs1_hw_init(bus->busid, USBH_IRQHandler);
        n32h7xx_wrapper_init(N32H7XX_USBHS1_WRAP, false, true);
    } else {
        n32h7xx_usbhs2_hw_init(bus->busid, USBH_IRQHandler);
        n32h7xx_wrapper_init(N32H7XX_USBHS2_WRAP, false, false);
    }
}

void usb_hc_low_level_deinit(struct usbh_bus *bus)
{
    NVIC_InitType nvic;

    if (bus->hcd.reg_base == N32H7XX_USBHS1_BASE) {
        nvic.NVIC_IRQChannel = USB1_HS_IRQn;
        nvic.NVIC_IRQChannelCmd = DISABLE;
        NVIC_Init(&nvic);
        RCC_EnableAHB2PeriphReset1(RCC_AHB2_PERIPHRST_USB1POR);
        RCC_EnableAHB2PeriphClk1(RCC_AHB2_PERIPHEN_M7_USB1, DISABLE);
    } else {
        nvic.NVIC_IRQChannel = USB2_HS_IRQn;
        nvic.NVIC_IRQChannelCmd = DISABLE;
        NVIC_Init(&nvic);
        RCC_EnableAHB1PeriphReset1(RCC_AHB1_PERIPHRST_USB2POR);
        RCC_EnableAHB1PeriphClk1(RCC_AHB1_PERIPHEN_M7_USB2, DISABLE);
    }
}

/* PHY is controlled via Wrapper registers, not GCCFG. */
uint32_t usbd_get_dwc2_gccfg_conf(uint32_t reg_base)
{
    return 0;
}

uint32_t usbh_get_dwc2_gccfg_conf(uint32_t reg_base)
{
    return 0;
}

/* -----------------------------------------------------------------------
 * IRQ handlers -- one per controller, fixed at link time.
 * ----------------------------------------------------------------------- */
void USB1_HS_IRQHandler(void)
{
    g_n32h7xx_irq[0].fn(g_n32h7xx_irq[0].busid);
}

void USB2_HS_IRQHandler(void)
{
    g_n32h7xx_irq[1].fn(g_n32h7xx_irq[1].busid);
}

/*
 * N32H7xx USBHS DWC2 parameters (applies to both USBHS1 and USBHS2).
 *
 * Both controllers have identical hardware: 4 KB FIFO RAM (1024 words),
 * 16-bit UTMI PHY, no descriptor DMA.  Differs from N32H47x_48x only in
 * phy_utmi_width = 16 (GCFG.PHYIF = 1).
 *
 * Device FIFO layout (1024 words, 4096 bytes):
 *   RX shared        512 words  (2048 bytes)
 *   EP0 IN TX         64 words  ( 256 bytes) -- control
 *   EP1 IN TX        256 words  (1024 bytes) -- primary HS bulk/iso
 *   EP2 IN TX         64 words  ( 256 bytes)
 *   EP3 IN TX         64 words  ( 256 bytes)
 *   EP4 IN TX         64 words  ( 256 bytes)
 *   Total           1024 words  (4096 bytes)
 *
 * Host FIFO layout (1024 words, 4096 bytes):
 *   RX              512 words  (2048 bytes)
 *   Non-periodic TX 256 words  (1024 bytes)
 *   Periodic TX     256 words  (1024 bytes)
 *   Total          1024 words  (4096 bytes)
 *
 * Adjust via CONFIG_USB_DWC2_CUSTOM_FIFO or CONFIG_USB_DWC2_CUSTOM_PARAM;
 * keep RX + sum(TX) <= 1024 words.
 */
static const struct dwc2_user_params param_n32h7xx = {
    /* Built-in HS UTMI+ PHY; GUSBCFG.ULPI_UTMI_SEL = 0. */
    .phy_type = DWC2_PHY_TYPE_PARAM_UTMI,

    /* 16-bit UTMI data bus (GCFG.PHYIF = 1).
     * USB_CoreInit() sets PHYIF via USBHS_GCFG_PHYIF.
     * CherryUSB sets GUSBCFG.PHYIF16 only when phy_utmi_width == 16.
     * GCFG.PHYIF: 0 = 8-bit bus, 1 = 16-bit bus. */
    .phy_utmi_width = 16,

#ifdef CONFIG_USB_DWC2_DMA_ENABLE
    .device_dma_enable = true,
#else
    .device_dma_enable = false,
#endif

    /* Scatter-Gather descriptor DMA: not supported (GHWCFG4.DESC_DMA_ENABLED = 0). */
    .device_dma_desc_enable = false,

    /* Shared RX FIFO depth for device mode, in 32-bit words.
     * Minimum formula: (5+8) + (512/4+1) + (2*7) + 1 = 157 words.
     * 512 words matches Nations CDC demo (RX_FIFO_HS_SIZE = 512).
     * Hardware limit: RXFDEP max = 1024 words. */
    .device_rx_fifo_size = 512,

    /* Per-IN-endpoint TX FIFO depths, in 32-bit words.
     * 512 TX + 512 RX = 1024 words total.
     * Per-FIFO hardware limit: INEPTXFDEP max = 768 words. */
    .device_tx_fifo_size = {
        [0] = 64,  /* EP0:  256 bytes, control; matches TX0_FIFO_HS_SIZE = 64 */
        [1] = 256, /* EP1: 1024 bytes, HS bulk/iso; matches TX1_FIFO_HS_SIZE = 256 */
        [2] = 64,  /* EP2:  256 bytes */
        [3] = 64,  /* EP3:  256 bytes */
        [4] = 64,  /* EP4:  256 bytes */
        [5] = 0,   /* EP5..EP8: unallocated; use CONFIG_USB_DWC2_CUSTOM_FIFO to enable */
        [6] = 0,
        [7] = 0,
        [8] = 0,
        [9] = 0,
        [10] = 0,
        [11] = 0,
        [12] = 0,
        [13] = 0,
        [14] = 0,
        [15] = 0,
    },

    .host_dma_desc_enable = false,

    /* Host RX FIFO: 512 words (min formula: (1024/4+1)+1 = 258 words). */
    .host_rx_fifo_size = 512,

    /* Host NP TX FIFO: 256 words (double-buffer, HS MPS = 512 bytes).
     * Matches Nations Host demo (TXH_NP_HS_FIFOSIZE = 256). */
    .host_nperio_tx_fifo_size = 256,

    /* Host periodic TX FIFO: 256 words (HS iso MPS = 1024: 1024/4 = 256 min).
     * Matches Nations Host demo (TXH_P_HS_FIFOSIZE = 256).
     * Host total: 512 + 256 + 256 = 1024 words. */
    .host_perio_tx_fifo_size = 256,

    /* PHY controlled via Wrapper registers (WRPCFG/WRPCTRL), not GCCFG. */
    .device_gccfg = 0,
    .host_gccfg = 0,

    /* Set to true to bypass VBUS hardware sensing on boards that do not route
     * USB VBUS to a GPIO sense pin.  false = rely on hardware VBUS detection. */
    .b_session_valid_override = true,

    /* 4 KB dedicated FIFO RAM = 1024 x 32-bit words; GRXFSIZ.RXFDEP max = 1024. */
    .total_fifo_size = 1024,
};

#ifndef CONFIG_USB_DWC2_CUSTOM_PARAM
void dwc2_get_user_params(uint32_t reg_base, struct dwc2_user_params *params)
{
    memcpy(params, &param_n32h7xx, sizeof(struct dwc2_user_params));
#ifdef CONFIG_USB_DWC2_CUSTOM_FIFO
    struct usb_dwc2_user_fifo_config s_dwc2_fifo_config;

    dwc2_get_user_fifo_config(reg_base, &s_dwc2_fifo_config);
    params->device_rx_fifo_size = s_dwc2_fifo_config.device_rx_fifo_size;
    for (uint8_t i = 0; i < MAX_EPS_CHANNELS; i++) {
        params->device_tx_fifo_size[i] = s_dwc2_fifo_config.device_tx_fifo_size[i];
    }
#endif /* CONFIG_USB_DWC2_CUSTOM_FIFO */
}
#endif /* CONFIG_USB_DWC2_CUSTOM_PARAM */

#endif /* N32H73x || N32H76x || N32H78x */

/* USB DMA buffers reside in AXI SRAM (D-Cache enabled).
 * The DWC2 AHB DMA master cannot reach DTCM/TCM, so buffers are placed in
 * normal cached SRAM.  Cache coherency is maintained via CMSIS SCB helpers:
 *   clean      -- flush CPU write-buffer to SRAM before DMA TX
 *   invalidate -- discard stale cache lines after DMA RX
 *   flush      -- clean + invalidate (bi-directional transfers) */
#ifdef CONFIG_USB_DCACHE_ENABLE
void usb_dcache_clean(uintptr_t addr, size_t size)
{
    SCB_CleanDCache_by_Addr((void *)addr, size);
}

void usb_dcache_invalidate(uintptr_t addr, size_t size)
{
    SCB_InvalidateDCache_by_Addr((void *)addr, size);
}

void usb_dcache_flush(uintptr_t addr, size_t size)
{
    SCB_CleanInvalidateDCache_by_Addr((void *)addr, size);
}
#endif
