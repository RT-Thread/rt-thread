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
#include "n32h47x_48x_exti.h"
#include "misc.h"

typedef void (*usb_dwc2_irq)(uint8_t busid);

static usb_dwc2_irq g_usb_dwc2_irq;
static volatile uint8_t g_usb_dwc2_busid = 0;

static void usbhs_common_init(void)
{
    RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_GPIOA | RCC_AHB_PERIPHEN_GPIOB, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    /* PLL= 240MHz */
#if (HSE_VALUE == 8000000)
    /* Select PLL clock as USBHS clock source , clock 15 divisions  = 16M */
    RCC_ConfigUSBPLLPresClk(RCC_USBPLLCLK_SRC_PLL, RCC_USBPLLCLK_DIV15);

    /* Select the corresponding bandwidth and frequency*/
    RCC_ConfigUSBHSBandwidth(RCC_USBHS_BW_16M);

    /* Select USBHS clock source frequency */
    RCC_ConfigUSBHSFrequency(RCC_USBHS_FREQ_16_OR_32M);

    /* Select PLL as USBHS clock */
    RCC_ConfigUSBHSClk(RCC_USBHS_CLKSRC_PLLPRES);
#else //HSE 16M
    RCC_ConfigUSBHSBandwidth(RCC_USBHS_BW_16M);
    RCC_ConfigUSBHSFrequency(RCC_USBHS_FREQ_16_OR_32M);
    RCC_ConfigUSBHSClk(RCC_USBHS_CLKSRC_HSE);
#endif
    /* Reset the USBHS phy clock*/
    RCC_EnableAHBPeriphReset(RCC_AHBPRST_USBHSPHYRST);
    /* Enables the USBHS peripheral clock*/
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPHEN_USBHS, ENABLE);

    NVIC_InitType NVIC_InitStructure;
    // EXTI_InitType EXTI_InitStructure;

    // NVIC_InitStructure.NVIC_IRQChannel = USB_HS_WKUP_IRQn;
    // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    // NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    // NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = USB_HS_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Configure the EXTI line 23 connected internally to the USBHS IP */
    // EXTI_ClrITPendBit(EXTI_LINE23);
    // EXTI_InitStructure.EXTI_Line = EXTI_LINE23;
    // EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    // EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    // EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    // EXTI_InitPeripheral(&EXTI_InitStructure);
}

static void usbhs_gpio_init(void)
{
    GPIO_InitType GPIO_InitStructure;

    RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_GPIOA | RCC_AHB_PERIPHEN_GPIOB | RCC_AHB_PERIPHEN_GPIOE, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    GPIO_ConfigPinRemap(0, 0, GPIO_RMP_SWJ_SWD);

    GPIO_InitStruct(&GPIO_InitStructure);
#ifdef USBHS_HOST
    GPIO_InitStructure.Pin = GPIO_PIN_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitPeripheral(GPIOE, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOE, GPIO_PIN_1);

    GPIO_InitStructure.Pin = GPIO_PIN_3;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOB, GPIO_PIN_3);
#endif
    // VBUS
    //  GPIO_InitStructure.Pin = GPIO_PIN_13;
    //  GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
    //  GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

    //  // SOF
    //  GPIO_InitStructure.Pin = GPIO_PIN_4;
    //  GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    //  GPIO_InitStructure.GPIO_Alternate = 8; // SOF
    //  GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    //  // ID
    //  GPIO_InitStructure.Pin = GPIO_PIN_12;
    //  GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    //  GPIO_InitStructure.GPIO_Alternate = 14; // ID
    //  GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
}

void usb_dc_low_level_init(uint8_t busid)
{
    g_usb_dwc2_irq = USBD_IRQHandler;
    g_usb_dwc2_busid = busid;

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
    /* Enables the USBHS peripheral clock*/
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPHEN_USBHS, DISABLE);
}

void usb_hc_low_level_init(struct usbh_bus *bus)
{
    g_usb_dwc2_irq = USBH_IRQHandler;
    g_usb_dwc2_busid = 0;

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
    /* Enables the USBHS peripheral clock*/
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

extern uint32_t SystemCoreClock;

void usbd_dwc2_delay_ms(uint8_t ms)
{
    uint32_t count = SystemCoreClock / 1000 * ms;
    while (count--) {
        __asm volatile("nop");
    }
}

#endif
