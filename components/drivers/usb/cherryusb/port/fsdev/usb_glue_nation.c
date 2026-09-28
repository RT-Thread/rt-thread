/*
 * Copyright (c) 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"

/* N32H4x family detection (N32H47x_48x + N32H49x): same part-macro list as
 * the SDKs (n32h47x_48x.h typedef enum IRQn, n32h49x.h) and as
 * usb_fsdev_reg.h.  Defined here locally so this file never needs to include
 * usb_fsdev_reg.h next to the SDK headers (which would re-define e.g.
 * USB_EP_SETUP). */
#if defined(N32H473) || defined(N32H474) || defined(N32H475) || \
    defined(N32H481) || defined(N32H482) || defined(N32H480) || \
    defined(N32H487) || defined(N32H488) || defined(N32H49X)
#define N32H4X_FSDEV 1
#endif

#if defined(N32H4X_FSDEV)

#if defined(N32H473) || defined(N32H474) || defined(N32H475) || \
    defined(N32H481) || defined(N32H482) || defined(N32H480) || \
    defined(N32H487) || defined(N32H488)
#include "n32h47x_48x_rcc.h"
#include "n32h47x_48x_gpio.h"
#include "misc.h"

#define USBFS_REG_BASE  0x40004800UL
#define USBFS_SRAM_BASE 0x40004C00UL
#define USBFS_APB1_CLK  RCC_APB1_PERIPH_USBFS

#elif defined(N32H49X)
#include "n32h49x_rcc.h"
#include "n32h49x_gpio.h"
#include "misc.h"

#define USBFS_REG_BASE  0x40004800UL
#define USBFS_SRAM_BASE 0x40004C00UL
#define USBFS_APB1_CLK  RCC_APB1_PERIPHEN_USBFS

#else
#error "unsupported N32H4x part: define a N32H47x_48x part macro (N32H473/474/475/481/482/480/487/488) or N32H49X"
#endif /* N32H473..N32H488 (48x SDK) / N32H49X (49x SDK) */

/*
 * N32H4x (N32H47x_48x / N32H49x) USB Full-Speed Device (USB_FS_Device).
 *
 * The USBFS core is the same Synopsys USBFS as STM32, but Nations re-arranged
 * every register/bit field.  The re-map lives in usb_fsdev_reg.h; this file
 * only does the chip-level bring-up (clock, GPIO, NVIC, interrupt dispatch)
 * and mirrors the Nations USBFSD examples (HID_CDC_Composite): hw_config.c
 * (USBFS_IO_Configure / Set_USBClock / USB_Config) and n32h47x_48x_it.c /
 * n32h49x_it.c (USB_FS_LP_IRQHandler).
 *
 * USBFS:
 *   - register base : 0x40004800 (USB_BASE)
 *   - packet buffer : 0x40004C00 (USB_SRAM_BASE, 512 bytes)
 *   - APB1 peripheral; USBFS needs a precise 48 MHz USB clock derived from
 *     PLLCLK (48/96/144/192/240 MHz -> DIV1/2/3/4/5).
 *   - IRQ : USB_FS_LP_IRQn (20, low priority, used here) ; USB_FS_HP_IRQn
 *     (19, high priority, iso/double-buffer only) 
 */

/**
 * @brief Configure the USBFS 48 MHz clock from the actual PLLCLK.
 *
 * The prescaler source is derived from SystemCoreClock at runtime, so the
 * divider always matches the frequency the board is actually running at
 * (no per-part compile-time table to keep in sync with the PLL setup).
 * Supported PLLCLK values: 48/96/144/192/240 MHz -> DIV1/2/3/4/5.
 * Unsupported frequencies leave the prescaler untouched and must be fixed
 * in the board clock configuration (48 MHz USB clock is then not guaranteed).
 */
static void Set_USBClock(void)
{
    switch (SystemCoreClock) {
    case 48000000: /* SYSCLK_VALUE_48MHz  -> DIV1 */
        RCC_ConfigUSBPLLPresClk(RCC_USBPLLCLK_SRC_PLL, RCC_USBPLLCLK_DIV1);
        RCC->CFG3 &= ~RCC_CFG3_USBFSTM;
        break;

    case 96000000: /* SYSCLK_VALUE_96MHz  -> DIV2 */
        RCC_ConfigUSBPLLPresClk(RCC_USBPLLCLK_SRC_PLL, RCC_USBPLLCLK_DIV2);
        RCC->CFG3 &= ~RCC_CFG3_USBFSTM;
        break;

    case 144000000: /* SYSCLK_VALUE_144MHz -> DIV3 */
        RCC_ConfigUSBPLLPresClk(RCC_USBPLLCLK_SRC_PLL, RCC_USBPLLCLK_DIV3);
        RCC->CFG3 |= RCC_CFG3_USBFSTM;
        break;

    case 192000000: /* SYSCLK_VALUE_192MHz -> DIV4 */
        RCC_ConfigUSBPLLPresClk(RCC_USBPLLCLK_SRC_PLL, RCC_USBPLLCLK_DIV4);
        RCC->CFG3 |= RCC_CFG3_USBFSTM;
        break;

    case 240000000: /* SYSCLK_VALUE_240MHz -> DIV5 */
        RCC_ConfigUSBPLLPresClk(RCC_USBPLLCLK_SRC_PLL, RCC_USBPLLCLK_DIV5);
        RCC->CFG3 |= RCC_CFG3_USBFSTM;
        break;

    default:
        USB_LOG_ERR("Unsupported system clock %u Hz for USBFS 48 MHz clock (supported: 48/96/144/192/240 MHz)\r\n",
                    (unsigned int)SystemCoreClock);
        break;
    }
}

/**
 * @brief Configure the USB DM/DP pins.
 *
 * Defaults to the EVAL board mapping (PA11 = DM, PA12 = DP, AF10).
 * Marked __WEAK so the board layer can override it for other pin maps.
 */
__WEAK void n32h4xx_usbfs_gpio_init(void)
{
    RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_GPIOA, ENABLE);

    GPIO_InitType GPIO_InitStructure;
    GPIO_InitStruct(&GPIO_InitStructure);

    GPIO_InitStructure.Pin            = GPIO_PIN_11;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF10;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = GPIO_PIN_12;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF10;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}

/**
 * @brief Low-level USBFS initialization: clock, GPIO and interrupt channel.
 *
 * Signature must match the __WEAK stub in usb_dc_fsdev.c (no parameter),
 * so the fsdev port always talks to bus 0.
 */
void usb_dc_low_level_init(void)
{
    if (g_usbdev_bus[0].reg_base != USBFS_REG_BASE) {
        return;
    }

    /* 1. USBFS 48 MHz clock: source select, PLL prescaler, APB1 enable. */
    RCC_ConfigUSBFSClk(RCC_USBFS_CLKSRC_PLLPRES);
    Set_USBClock();
    RCC_EnableAPB1PeriphClk(USBFS_APB1_CLK, ENABLE);

    /* 2. USB DM/DP pins (weak hook, override in the board layer). */
    n32h4xx_usbfs_gpio_init();

    /* 3. Low-priority USB FS interrupt (all FS device events, including the
     *    USB_STS.WKUP/SUSPD bits handled by usb_dc_fsdev.c).  Priority-group
     *    selection stays with the board/application startup code. */
    NVIC_InitType NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel                   = USB_FS_LP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief Low-level USBFS deinitialization: disable interrupt and APB1 clock.
 */
void usb_dc_low_level_deinit(void)
{
    if (g_usbdev_bus[0].reg_base != USBFS_REG_BASE) {
        return;
    }

    NVIC_InitType NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel    = USB_FS_LP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStructure);

    RCC_EnableAPB1PeriphClk(USBFS_APB1_CLK, DISABLE);
}

/**
 * @brief Low-priority USB FS interrupt: dispatches all FS device events.
 */
void USB_FS_LP_IRQHandler(void)
{
    USBD_IRQHandler(0);
}

#endif /* N32H4X_FSDEV */
