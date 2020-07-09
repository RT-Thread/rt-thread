/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-5-30      Bernard      the first version
 */

#ifndef BOARD_H__
#define BOARD_H__

#include <stdint.h>

extern unsigned char __bss_start__;
extern unsigned char __bss_end__;

#define RT_HW_HEAP_BEGIN    (void*)&__bss_end__
#define RT_HW_HEAP_END      (void*)(0x20000000 + 0x00030000 - 0x1800)

#define BOARD_USDHC0_BASEADDR USDHC0
#define BOARD_USDHC_CD_PORT_BASE PORTC
#define BOARD_USDHC_CD_GPIO_BASE GPIOC
#define BOARD_USDHC_CD_GPIO_PIN 27
#define BOARD_USDHC_CD_PORT_IRQ PORTC_IRQn
#define BOARD_USDHC_CD_PORT_IRQ_HANDLER PORTC_IRQHandler

#define BOARD_USDHC_CD_GPIO_INIT()                                                                                \
    {                                                                                                             \
        gpio_pin_config_t sw_config = {kGPIO_DigitalInput, 0};                                                    \
        GPIO_PinInit(BOARD_USDHC_CD_GPIO_BASE, BOARD_USDHC_CD_GPIO_PIN, &sw_config);                              \
        PORT_SetPinInterruptConfig(BOARD_USDHC_CD_PORT_BASE, BOARD_USDHC_CD_GPIO_PIN, kPORT_InterruptRisingEdge); \
    }

#define BOARD_USDHC_CD_STATUS() (GPIO_ReadPinInput(BOARD_USDHC_CD_GPIO_BASE, BOARD_USDHC_CD_GPIO_PIN))

#define BOARD_USDHC_CD_INTERRUPT_STATUS() (GPIO_GetPinsInterruptFlags(BOARD_USDHC_CD_GPIO_BASE))
#define BOARD_USDHC_CD_CLEAR_INTERRUPT(flag) (GPIO_ClearPinsInterruptFlags(BOARD_USDHC_CD_GPIO_BASE, flag))
#define BOARD_USDHC_CARD_INSERT_CD_LEVEL (1U)
#define BOARD_USDHC0_CLK_FREQ (CLOCK_GetIpFreq(kCLOCK_Sdhc0))

#define BOARD_SD_HOST_BASEADDR BOARD_USDHC0_BASEADDR
#define BOARD_SD_HOST_CLK_FREQ BOARD_USDHC0_CLK_FREQ
#define BOARD_SD_HOST_IRQ USDHC0_IRQn
#define BOARD_SD_SUPPORT_180V (0U)
#define BOARD_MMC_HOST_BASEADDR BOARD_USDHC0_BASEADDR
#define BOARD_MMC_HOST_CLK_FREQ BOARD_USDHC0_CLK_FREQ
#define BOARD_MMC_HOST_IRQ USDHC0_IRQn
#define BOARD_MMC_VCCQ_SUPPLY kMMC_VoltageWindows270to360
#define BOARD_MMC_VCC_SUPPLY kMMC_VoltageWindows270to360
#define BOARD_MMC_PIN_CONFIG(speed, strength)

/* this define not implement, due to EVK board have no power reset circuit */
#define BOARD_SD_POWER_RESET_GPIO ()
#define BOARD_SD_POWER_RESET_GPIO_PIN ()
#define BOARD_USDHC_SDCARD_POWER_CONTROL_INIT()
#define BOARD_USDHC_SDCARD_POWER_CONTROL(state)
#define BOARD_SD_PIN_CONFIG(speed, strength)
#define BOARD_USDHC_MMCCARD_POWER_CONTROL(enable)
#define BOARD_USDHC_MMCCARD_POWER_CONTROL_INIT()

void rt_hw_board_init(void);

#endif
