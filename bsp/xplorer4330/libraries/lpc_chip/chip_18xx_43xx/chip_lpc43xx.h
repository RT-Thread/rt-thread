/*
 * @brief LPC43xx basic chip inclusion file
 *
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __CHIP_LPC43XX_H_
#define __CHIP_LPC43XX_H_

#include "lpc_types.h"
#include "sys_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(CORE_M4) && !defined(CORE_M0)
#error CORE_M4 or CORE_M0 is not defined for the LPC43xx architecture
#error CORE_M4 or CORE_M0 should be defined as part of your compiler define list
#endif

#ifndef CHIP_LPC43XX
#error The LPC43XX Chip include path is used for this build, but
#error CHIP_LPC43XX is not defined!
#endif

#include "adc_001.h"
#include "atimer_001.h"
#include "ccan_001.h"
#include "dac_001.h"
#include "emc_001.h"
#include "enet_001.h"
#include "gima_001.h"
#include "gpdma_001.h"
#include "gpiogrpint_001.h"
#include "gpiopinint_001.h"
#include "gpio_001.h"
#include "i2c_001.h"
#include "i2s_001.h"
#include "lcd_001.h"
#include "mcpwm_001.h"
#include "pmc_001.h"
#include "qei_001.h"
#include "regfile_001.h"
#include "ritimer_001.h"
#include "rtc_001.h"
#include "sct_001.h"
#include "sdmmc_001.h"
#include "sgpio_001.h"
#include "spi_001.h"
#include "ssp_001.h"
#include "timer_001.h"
#include "usart_001.h"
#include "usbhs_001.h"
#include "wwdt_001.h"
#include "spifi_001.h"
#include "rgu_18xx_43xx.h"
#include "cguccu_18xx_43xx.h"

/** @defgroup PERIPH_43XX_BASE CHIP: LPC43xx Peripheral addresses and register set declarations
 * @ingroup CHIP_18XX_43XX_Drivers
 * @{
 */

#define LPC_SCT_BASE              0x40000000
#define LPC_GPDMA_BASE            0x40002000
#define LPC_SDMMC_BASE            0x40004000
#define LPC_EMC_BASE              0x40005000
#define LPC_USB0_BASE             0x40006000
#define LPC_USB1_BASE             0x40007000
#define LPC_LCD_BASE              0x40008000
#define LPC_ETHERNET_BASE         0x40010000
#define LPC_ATIMER_BASE           0x40040000
#define LPC_REGFILE_BASE          0x40041000
#define LPC_PMC_BASE              0x40042000
#define LPC_CREG_BASE             0x40043000
#define LPC_EVRT_BASE             0x40044000
#define LPC_RTC_BASE              0x40046000
#define LPC_CGU_BASE              0x40050000
#define LPC_CCU1_BASE             0x40051000
#define LPC_CCU2_BASE             0x40052000
#define LPC_RGU_BASE              0x40053000
#define LPC_WWDT_BASE             0x40080000
#define LPC_USART0_BASE           0x40081000
#define LPC_USART2_BASE           0x400C1000
#define LPC_USART3_BASE           0x400C2000
#define LPC_UART1_BASE            0x40082000
#define LPC_SSP0_BASE             0x40083000
#define LPC_SSP1_BASE             0x400C5000
#define LPC_TIMER0_BASE           0x40084000
#define LPC_TIMER1_BASE           0x40085000
#define LPC_TIMER2_BASE           0x400C3000
#define LPC_TIMER3_BASE           0x400C4000
#define LPC_SCU_BASE              0x40086000
#define LPC_GPIO_PIN_INT_BASE     0x40087000
#define LPC_GPIO_GROUP_INT0_BASE  0x40088000
#define LPC_GPIO_GROUP_INT1_BASE  0x40089000
#define LPC_MCPWM_BASE            0x400A0000
#define LPC_I2C0_BASE             0x400A1000
#define LPC_I2C1_BASE             0x400E0000
#define LPC_I2S0_BASE             0x400A2000
#define LPC_I2S1_BASE             0x400A3000
#define LPC_C_CAN1_BASE           0x400A4000
#define LPC_RITIMER_BASE          0x400C0000
#define LPC_QEI_BASE              0x400C6000
#define LPC_GIMA_BASE             0x400C7000
#define LPC_DAC_BASE              0x400E1000
#define LPC_C_CAN0_BASE           0x400E2000
#define LPC_ADC0_BASE             0x400E3000
#define LPC_ADC1_BASE             0x400E4000
#define LPC_GPIO_PORT_BASE        0x400F4000
#define LPC_SPI_BASE              0x40100000
#define LPC_SGPIO_BASE            0x40101000

/* Normalize types */
typedef IP_SCT_001_Type LPC_SCT_Type;
typedef IP_GPDMA_001_Type LPC_GPDMA_Type;
typedef IP_SDMMC_001_Type LPC_SDMMC_Type;
typedef IP_EMC_001_Type LPC_EMC_Type;
typedef IP_USBHS_001_Type LPC_USBHS_Type;
typedef IP_ENET_001_Type LPC_ENET_Type;
typedef IP_ATIMER_001_Type LPC_ATIMER_Type;
typedef IP_REGFILE_001_T LPC_REGFILE_Type;
typedef IP_PMC_001_Type LPC_PMC_Type;
typedef IP_RTC_001_T LPC_RTC_Type;
typedef IP_WWDT_001_Type LPC_WWDT_Type;
typedef IP_USART_001_Type LPC_USART_Type;
typedef IP_SSP_001_Type LPC_SSP_Type;
typedef IP_TIMER_001_Type LPC_TIMER_Type;
typedef IP_GPIOPININT_001_Type LPC_GPIOPININT_Type;
typedef IP_MCPWM_001_Type LPC_MCPWM_Type;
typedef IP_I2C_001_Type LPC_I2C_Type;
typedef IP_I2S_001_Type LPC_I2S_Type;
typedef IP_CCAN_001_Type LPC_CCAN_Type;
typedef IP_RITIMER_001_Type LPC_RITIMER_Type;
typedef IP_QEI_001_Type LPC_QEI_Type;
typedef IP_GIMA_001_Type LPC_GIMA_Type;
typedef IP_DAC_001_Type LPC_DAC_Type;
typedef IP_ADC_001_Type LPC_ADC_Type;
typedef IP_GPIO_001_Type LPC_GPIO_Type;
typedef IP_SPI_001_Type LPC_SPI_Type;
typedef IP_SGPIO_001_Type LPC_SGPIO_Type;
typedef IP_LCD_001_Type LPC_LCD_Type;

#define LPC_SCT                   ((IP_SCT_001_Type              *) LPC_SCT_BASE)
#define LPC_GPDMA                 ((IP_GPDMA_001_Type            *) LPC_GPDMA_BASE)
#define LPC_SDMMC                 ((IP_SDMMC_001_Type            *) LPC_SDMMC_BASE)
#define LPC_EMC                   ((IP_EMC_001_Type              *) LPC_EMC_BASE)
#define LPC_USB0                  ((IP_USBHS_001_Type            *) LPC_USB0_BASE)
#define LPC_USB1                  ((IP_USBHS_001_Type            *) LPC_USB1_BASE)
#define LPC_LCD                   ((IP_LCD_001_Type              *) LPC_LCD_BASE)
#define LPC_ETHERNET              ((IP_ENET_001_Type             *) LPC_ETHERNET_BASE)
#define LPC_ATIMER                ((IP_ATIMER_001_Type           *) LPC_ATIMER_BASE)
#define LPC_REGFILE               ((IP_REGFILE_001_T             *) LPC_REGFILE_BASE)
#define LPC_PMC                   ((IP_PMC_001_Type              *) LPC_PMC_BASE)
#define LPC_EVRT                  ((LPC_EVRT_Type                *) LPC_EVRT_BASE)
#define LPC_RTC                   ((IP_RTC_001_T                 *) LPC_RTC_BASE)
#define LPC_CGU                   ((LPC_CGU_T                    *) LPC_CGU_BASE)
#define LPC_CCU1                  ((LPC_CCU1_Type                *) LPC_CCU1_BASE)
#define LPC_CCU2                  ((LPC_CCU2_Type                *) LPC_CCU2_BASE)
#define LPC_CREG                  ((LPC_CREG_T                   *) LPC_CREG_BASE)
#define LPC_RGU                   ((LPC_RGU_T                    *) LPC_RGU_BASE)
#define LPC_WWDT                  ((IP_WWDT_001_Type             *) LPC_WWDT_BASE)
#define LPC_USART0                ((IP_USART_001_Type            *) LPC_USART0_BASE)
#define LPC_USART2                ((IP_USART_001_Type            *) LPC_USART2_BASE)
#define LPC_USART3                ((IP_USART_001_Type            *) LPC_USART3_BASE)
#define LPC_UART1                 ((IP_USART_001_Type            *) LPC_UART1_BASE)
#define LPC_SSP0                  ((IP_SSP_001_Type              *) LPC_SSP0_BASE)
#define LPC_SSP1                  ((IP_SSP_001_Type              *) LPC_SSP1_BASE)
#define LPC_TIMER0                ((IP_TIMER_001_Type            *) LPC_TIMER0_BASE)
#define LPC_TIMER1                ((IP_TIMER_001_Type            *) LPC_TIMER1_BASE)
#define LPC_TIMER2                ((IP_TIMER_001_Type            *) LPC_TIMER2_BASE)
#define LPC_TIMER3                ((IP_TIMER_001_Type            *) LPC_TIMER3_BASE)
#define LPC_SCU                   ((LPC_SCU_Type                 *) LPC_SCU_BASE)
#define LPC_GPIO_PIN_INT          ((IP_GPIOPININT_001_Type       *) LPC_GPIO_PIN_INT_BASE)
#define LPC_GPIO_GROUP_INT0       ((IP_GPIOGROUPINT_001_Type     *) LPC_GPIO_GROUP_INT0_BASE)
#define LPC_GPIO_GROUP_INT1       ((IP_GPIOGROUPINT_001_Type     *) LPC_GPIO_GROUP_INT1_BASE)
#define LPC_MCPWM                 ((IP_MCPWM_001_Type            *) LPC_MCPWM_BASE)
#define LPC_I2C0                  ((IP_I2C_001_Type              *) LPC_I2C0_BASE)
#define LPC_I2C1                  ((IP_I2C_001_Type              *) LPC_I2C1_BASE)
#define LPC_I2S0                  ((IP_I2S_001_Type              *) LPC_I2S0_BASE)
#define LPC_I2S1                  ((IP_I2S_001_Type              *) LPC_I2S1_BASE)
#define LPC_C_CAN1                ((IP_CCAN_001_Type             *) LPC_C_CAN1_BASE)
#define LPC_RITIMER               ((IP_RITIMER_001_Type          *) LPC_RITIMER_BASE)
#define LPC_QEI                   ((IP_QEI_001_Type              *) LPC_QEI_BASE)
#define LPC_GIMA                  ((IP_GIMA_001_Type             *) LPC_GIMA_BASE)
#define LPC_DAC                   ((IP_DAC_001_Type              *) LPC_DAC_BASE)
#define LPC_C_CAN0                ((IP_CCAN_001_Type             *) LPC_C_CAN0_BASE)
#define LPC_ADC0                  ((IP_ADC_001_Type              *) LPC_ADC0_BASE)
#define LPC_ADC1                  ((IP_ADC_001_Type              *) LPC_ADC1_BASE)
#define LPC_GPIO_PORT             ((IP_GPIO_001_Type             *) LPC_GPIO_PORT_BASE)
#define LPC_SPI                   ((IP_SPI_001_Type              *) LPC_SPI_BASE)
#define LPC_SGPIO                 ((IP_SGPIO_001_Type            *) LPC_SGPIO_BASE)

/**
 * @}
 */

#include "clock_18xx_43xx.h"
#include "gpio_18xx_43xx.h"
#include "scu_18xx_43xx.h"
#include "uart_18xx_43xx.h"
#include "gpdma_18xx_43xx.h"
#include "enet_18xx_43xx.h"
#include "rgu_18xx_43xx.h"
#include "i2c_18xx_43xx.h"
#include "i2s_18xx_43xx.h"
#include "ssp_18xx_43xx.h"
#include "rtc_18xx_43xx.h"
#include "evrt_18xx_43xx.h"
#include "atimer_18xx_43xx.h"
#include "wwdt_18xx_43xx.h"
#include "ritimer_18xx_43xx.h"
#include "emc_18xx_43xx.h"
#include "lcd_18xx_43xx.h"
#include "adc_18xx_43xx.h"
#include "timer_18xx_43xx.h"
#include "sdmmc_18xx_43xx.h"
#include "fpu_init.h"
#include "creg_18xx_43xx.h"

#ifdef __cplusplus
}
#endif

#endif /* __CHIP_LPC43XX_H_ */
