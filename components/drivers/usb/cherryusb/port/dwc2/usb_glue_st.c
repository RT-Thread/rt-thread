/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbh_core.h"

#if __has_include("stm32f1xx_hal.h")
#include "stm32f1xx_hal.h"
#elif __has_include("stm32f2xx_hal.h")
#include "stm32f2xx_hal.h"
#elif __has_include("stm32f4xx_hal.h")
#include "stm32f4xx_hal.h"
#elif __has_include("stm32f7xx_hal.h")
#include "stm32f7xx_hal.h"
#elif __has_include("stm32h7xx_hal.h")
#include "stm32h7xx_hal.h"
#elif __has_include("stm32h7rsxx_hal.h")
#include "stm32h7rsxx_hal.h"
#elif __has_include("stm32l4xx_hal.h")
#include "stm32l4xx_hal.h"
#endif

#if !defined(HAL_HCD_MODULE_ENABLED) && !defined(HAL_PCD_MODULE_ENABLED)
#error please define HAL_HCD_MODULE_ENABLED or HAL_PCD_MODULE_ENABLED in stm32xxx_hal_conf.h
#endif

typedef void (*usb_dwc2_irq)(uint8_t busid);

struct dwc2_instance {
    USB_OTG_GlobalTypeDef *Instance;
};

static usb_dwc2_irq g_usb_dwc2_irq[2];
static uint8_t g_usb_dwc2_busid[2] = { 0, 0 };
static struct dwc2_instance g_dwc2_instance;

#ifdef HAL_PCD_MODULE_ENABLED
void usb_dc_low_level_init(uint8_t busid)
{
    if (g_usbdev_bus[busid].reg_base == 0x40040000UL) { // USB_OTG_HS_PERIPH_BASE
        g_usb_dwc2_busid[1] = busid;
        g_usb_dwc2_irq[1] = USBD_IRQHandler;
    } else {
        g_usb_dwc2_busid[0] = busid;
        g_usb_dwc2_irq[0] = USBD_IRQHandler;
    }

    g_dwc2_instance.Instance = (USB_OTG_GlobalTypeDef *)g_usbdev_bus[busid].reg_base;
    HAL_PCD_MspInit((PCD_HandleTypeDef *)&g_dwc2_instance);
}

void usb_dc_low_level_deinit(uint8_t busid)
{
    if (g_usbdev_bus[busid].reg_base == 0x40040000UL) { // USB_OTG_HS_PERIPH_BASE
        g_usb_dwc2_busid[1] = 0;
        g_usb_dwc2_irq[1] = NULL;
    } else {
        g_usb_dwc2_busid[0] = 0;
        g_usb_dwc2_irq[0] = NULL;
    }

    g_dwc2_instance.Instance = (USB_OTG_GlobalTypeDef *)g_usbdev_bus[busid].reg_base;
    HAL_PCD_MspDeInit((PCD_HandleTypeDef *)&g_dwc2_instance);
}
#endif

#ifdef HAL_HCD_MODULE_ENABLED
void usb_hc_low_level_init(struct usbh_bus *bus)
{
    if (bus->hcd.reg_base == 0x40040000UL) { // USB_OTG_HS_PERIPH_BASE
        g_usb_dwc2_busid[1] = bus->hcd.hcd_id;
        g_usb_dwc2_irq[1] = USBH_IRQHandler;
    } else {
        g_usb_dwc2_busid[0] = bus->hcd.hcd_id;
        g_usb_dwc2_irq[0] = USBH_IRQHandler;
    }

    g_dwc2_instance.Instance = (USB_OTG_GlobalTypeDef *)bus->hcd.reg_base;
    HAL_HCD_MspInit((HCD_HandleTypeDef *)&g_dwc2_instance);
}

void usb_hc_low_level_deinit(struct usbh_bus *bus)
{
    if (bus->hcd.reg_base == 0x40040000UL) { // USB_OTG_HS_PERIPH_BASE
        g_usb_dwc2_busid[1] = 0;
        g_usb_dwc2_irq[1] = NULL;
    } else {
        g_usb_dwc2_busid[0] = 0;
        g_usb_dwc2_irq[0] = NULL;
    }

    g_dwc2_instance.Instance = (USB_OTG_GlobalTypeDef *)bus->hcd.reg_base;
    HAL_HCD_MspDeInit((HCD_HandleTypeDef *)&g_dwc2_instance);
}
#endif
/* you can find this config in function: USB_DevInit, file:stm32xxx_ll_usb.c, for example:
 *
 *  USBx->GCCFG |= USB_OTG_GCCFG_PWRDWN;
 *  USBx->GCCFG |= USB_OTG_GCCFG_NOVBUSSENS;
 *  USBx->GCCFG &= ~USB_OTG_GCCFG_VBUSBSEN;
 *  USBx->GCCFG &= ~USB_OTG_GCCFG_VBUSASEN;
 *
*/

#if defined(STM32F722xx) || defined(STM32F723xx) || defined(STM32F730xx) || defined(STM32F732xx) || defined(STM32F733xx)
/**
  * @brief  Enables control of a High Speed USB PHY
  *         Init the low level hardware : GPIO, CLOCK, NVIC...
  * @param  USBx  Selected device
  * @retval HAL status
  */
static int usb_hsphy_init(uint32_t hse_value)
{
    __IO uint32_t count = 0U;

    /* Enable LDO */
    USB_HS_PHYC->USB_HS_PHYC_LDO |= USB_HS_PHYC_LDO_ENABLE;

    /* wait for LDO Ready */
    while ((USB_HS_PHYC->USB_HS_PHYC_LDO & USB_HS_PHYC_LDO_STATUS) == 0U) {
        count++;

        if (count > 200000U) {
            return -1;
        }
    }

    /* Controls PHY frequency operation selection */
    if (hse_value == 12000000U) /* HSE = 12MHz */
    {
        USB_HS_PHYC->USB_HS_PHYC_PLL = (0x0U << 1);
    } else if (hse_value == 12500000U) /* HSE = 12.5MHz */
    {
        USB_HS_PHYC->USB_HS_PHYC_PLL = (0x2U << 1);
    } else if (hse_value == 16000000U) /* HSE = 16MHz */
    {
        USB_HS_PHYC->USB_HS_PHYC_PLL = (0x3U << 1);
    } else if (hse_value == 24000000U) /* HSE = 24MHz */
    {
        USB_HS_PHYC->USB_HS_PHYC_PLL = (0x4U << 1);
    } else if (hse_value == 25000000U) /* HSE = 25MHz */
    {
        USB_HS_PHYC->USB_HS_PHYC_PLL = (0x5U << 1);
    } else if (hse_value == 32000000U) /* HSE = 32MHz */
    {
        USB_HS_PHYC->USB_HS_PHYC_PLL = (0x7U << 1);
    } else {
        /* ... */
    }

    /* Control the tuning interface of the High Speed PHY */
    USB_HS_PHYC->USB_HS_PHYC_TUNE |= USB_HS_PHYC_TUNE_VALUE;

    /* Enable PLL internal PHY */
    USB_HS_PHYC->USB_HS_PHYC_PLL |= USB_HS_PHYC_PLL_PLLEN;

    /* 2ms Delay required to get internal phy clock stable */
    HAL_Delay(2U);

    return 0;
}
#endif

uint32_t usbd_get_dwc2_gccfg_conf(uint32_t reg_base)
{
#if __has_include("stm32h7xx.h") || __has_include("stm32f7xx.h") || __has_include("stm32l4xx.h")
#define USB_OTG_GLB ((USB_OTG_GlobalTypeDef *)(reg_base))
    /* B-peripheral session valid override enable */
    USB_OTG_GLB->GOTGCTL |= USB_OTG_GOTGCTL_BVALOEN;
    USB_OTG_GLB->GOTGCTL |= USB_OTG_GOTGCTL_BVALOVAL;
#endif

#ifdef CONFIG_USB_HS
#if defined(STM32F722xx) || defined(STM32F723xx) || defined(STM32F730xx) || defined(STM32F732xx) || defined(STM32F733xx)
    USB_OTG_GLB->GCCFG = (1 << 23);
    usb_hsphy_init(25000000U);
    return (1 << 23); /* Enable USB HS PHY USBx->GCCFG |= USB_OTG_GCCFG_PHYHSEN;*/
#elif __has_include("stm32h7rsxx.h")
    return ((1 << 23) | (1 << 24));
#else
    return 0;
#endif
#else
#if __has_include("stm32h7xx.h") || __has_include("stm32f7xx.h") || __has_include("stm32l4xx.h")
    return (1 << 16);
#else
    return ((1 << 16) | (1 << 21));
#endif
#endif
}

uint32_t usbh_get_dwc2_gccfg_conf(uint32_t reg_base)
{
#if __has_include("stm32h7xx.h") || __has_include("stm32f7xx.h") || __has_include("stm32l4xx.h")
#define USB_OTG_GLB ((USB_OTG_GlobalTypeDef *)(reg_base))
    /* B-peripheral session valid override enable */
    USB_OTG_GLB->GOTGCTL &= ~USB_OTG_GOTGCTL_BVALOEN;
    USB_OTG_GLB->GOTGCTL &= ~USB_OTG_GOTGCTL_BVALOVAL;
#endif

#ifdef CONFIG_USB_HS
#if defined(STM32F722xx) || defined(STM32F723xx) || defined(STM32F730xx) || defined(STM32F732xx) || defined(STM32F733xx)
    USB_OTG_GLB->GCCFG = (1 << 23);
    usb_hsphy_init(25000000U);
    return (1 << 23); /* Enable USB HS PHY USBx->GCCFG |= USB_OTG_GCCFG_PHYHSEN;*/
#elif __has_include("stm32h7rsxx.h")
    return (1 << 25);
#else
    return 0;
#endif
#else
#if __has_include("stm32h7xx.h") || __has_include("stm32f7xx.h") || __has_include("stm32l4xx.h")
    return (1 << 16);
#else
    return ((1 << 16) | (1 << 21));
#endif
#endif
}

extern uint32_t SystemCoreClock;

void usbd_dwc2_delay_ms(uint8_t ms)
{
    uint32_t count = SystemCoreClock / 1000 * ms;
    while (count--) {
        __asm volatile("nop");
    }
}

void OTG_FS_IRQHandler(void)
{
    g_usb_dwc2_irq[0](g_usb_dwc2_busid[0]);
}

void OTG_HS_IRQHandler(void)
{
    g_usb_dwc2_irq[1](g_usb_dwc2_busid[1]);
}

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
