/*!
    \file    gd32e50x.h
    \brief   general definitions for GD32E50x

;    \version 2023-12-31, V1.4.0, firmware for GD32E50x
*/

/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
 * Copyright (c) 2023, GigaDevice Semiconductor Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* This file refers the CMSIS standard, some adjustments are made according to GigaDevice chips */

#ifndef GD32E50X_H
#define GD32E50X_H

#ifdef __cplusplus
 extern "C" {
#endif

/* define GD32E50X */
#if !defined (GD32EPRT) && !defined (GD32E50X_HD) && !defined (GD32E50X_CL) && !defined (GD32E508)
 #error "Please select chip type in project configuration"
  /* #define GD32EPRT */
  /* #define GD32E50X_HD */
  /* #define GD32E50X_CL */
  /* #define GD32E508 */
#endif /* define GD32E50X */

#if !defined (GD32E50X)
 #error "Please select the target GD32E50x device used in your application (in gd32e50x.h file)"
#endif /* undefine GD32E50X tip */

/* define value of high speed crystal oscillator (HXTAL) in Hz */
#if !defined  HXTAL_VALUE
#if defined (GD32E50X_CL) || defined (GD32E508)
#define HXTAL_VALUE    ((uint32_t)25000000) /*!< value of the external oscillator in Hz */
#else
#define HXTAL_VALUE    ((uint32_t)8000000) /* !< from 4M to 32M *!< value of the external oscillator in Hz*/
#endif /* HXTAL_VALUE */
#endif /* high speed crystal oscillator value */

/* define startup timeout value of high speed crystal oscillator (HXTAL) */
#if !defined  (HXTAL_STARTUP_TIMEOUT)
#define HXTAL_STARTUP_TIMEOUT   ((uint16_t)0x0FFFF)
#endif /* high speed crystal oscillator startup timeout */

/* define value of internal 8MHz RC oscillator (IRC8M) in Hz */
#if !defined  (IRC8M_VALUE)
#define IRC8M_VALUE  ((uint32_t)8000000)
#endif /* internal 8MHz RC oscillator value */

/* define startup timeout value of internal 8MHz RC oscillator (IRC8M) */
#if !defined  (IRC8M_STARTUP_TIMEOUT)
#define IRC8M_STARTUP_TIMEOUT   ((uint16_t)0x0500)
#endif /* internal 8MHz RC oscillator startup timeout */

/* define value of internal 48MHz RC oscillator (IRC48M) in Hz */
#if !defined  (IRC48M_VALUE)
#define IRC48M_VALUE  ((uint32_t)48000000)
#endif /* internal 48MHz RC oscillator value */

/* define value of internal 40KHz RC oscillator(IRC40K) in Hz */
#if !defined  (IRC40K_VALUE)
#define IRC40K_VALUE  ((uint32_t)40000)
#endif /* internal 40KHz RC oscillator value */

/* define value of low speed crystal oscillator (LXTAL)in Hz */
#if !defined  (LXTAL_VALUE)
#define LXTAL_VALUE  ((uint32_t)32768)
#endif /* low speed crystal oscillator value */

/* GD32E50x firmware library version number V1.0 */
#define __GD32E50X_STDPERIPH_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __GD32E50X_STDPERIPH_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __GD32E50X_STDPERIPH_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __GD32E50X_STDPERIPH_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __GD32E50X_STDPERIPH_VERSION        ((__GD32E50X_STDPERIPH_VERSION_MAIN << 24)\
                                            |(__GD32E50X_STDPERIPH_VERSION_SUB1 << 16)\
                                            |(__GD32E50X_STDPERIPH_VERSION_SUB2 << 8)\
                                            |(__GD32E50X_STDPERIPH_VERSION_RC))

/* configuration of the Cortex-M33 processor and core peripherals */
#define __CM33_REV                0x0003U   /*!< Core revision r0p3 */
#define __SAUREGION_PRESENT       0U        /*!< SAU regions are not present */
#define __MPU_PRESENT             1U        /*!< MPU is present */
#define __VTOR_PRESENT            1U        /*!< VTOR is present */
#define __NVIC_PRIO_BITS          4U        /*!< Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0U        /*!< Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             1         /*!< FPU present */
#define __DSP_PRESENT             1         /*!< DSP present */

/* define interrupt number */
typedef enum IRQn
{
    /* Cortex-M33 processor exceptions numbers */
    NonMaskableInt_IRQn          = -14,    /*!< non mask-able interrupt */
    HardFault_IRQn               = -13,    /*!< hard-fault interrupt */
    MemoryManagement_IRQn        = -12,    /*!< 4 Cortex-M33 memory management interrupt */
    BusFault_IRQn                = -11,    /*!< 5 Cortex-M33 bus fault interrupt */
    UsageFault_IRQn              = -10,    /*!< 6 Cortex-M33 usage fault interrupt */
    SVCall_IRQn                  = -5,     /*!< 11 Cortex-M33 sv call interrupt */
    DebugMonitor_IRQn            = -4,     /*!< 12 Cortex-M33 debug monitor interrupt */
    PendSV_IRQn                  = -2,     /*!< 14 Cortex-M33 pend sv interrupt */
    SysTick_IRQn                 = -1,     /*!< 15 Cortex-M33 system tick interrupt */
    /* interrupt numbers */
    WWDGT_IRQn                   = 0,      /*!< window watchDog timer interrupt */
    LVD_IRQn                     = 1,      /*!< LVD through EXTI line detect interrupt */
    TAMPER_IRQn                  = 2,      /*!< tamper through EXTI line detect */
    RTC_IRQn                     = 3,      /*!< RTC through EXTI line interrupt */
    FMC_IRQn                     = 4,      /*!< FMC interrupt */
    RCU_CTC_IRQn                 = 5,      /*!< RCU and CTC interrupt */
    EXTI0_IRQn                   = 6,      /*!< EXTI line 0 interrupt */
    EXTI1_IRQn                   = 7,      /*!< EXTI line 1 interrupt */
    EXTI2_IRQn                   = 8,      /*!< EXTI line 2 interrupt */
    EXTI3_IRQn                   = 9,      /*!< EXTI line 3 interrupt */
    EXTI4_IRQn                   = 10,     /*!< EXTI line 4 interrupt */
    DMA0_Channel0_IRQn           = 11,     /*!< DMA0 channel0 interrupt */
    DMA0_Channel1_IRQn           = 12,     /*!< DMA0 channel1 interrupt */
    DMA0_Channel2_IRQn           = 13,     /*!< DMA0 channel2 interrupt */
    DMA0_Channel3_IRQn           = 14,     /*!< DMA0 channel3 interrupt */
    DMA0_Channel4_IRQn           = 15,     /*!< DMA0 channel4 interrupt */
    DMA0_Channel5_IRQn           = 16,     /*!< DMA0 channel5 interrupt */
    DMA0_Channel6_IRQn           = 17,     /*!< DMA0 channel6 interrupt */
    ADC0_1_IRQn                  = 18,     /*!< ADC0 and ADC1 interrupt */

#ifdef GD32EPRT
    USBD_HP_IRQn                 = 19,     /*!< USBD High Priority interrupts */
    USBD_LP_IRQn                 = 20,     /*!< USBD Low Priority interrupts */
    EXTI5_9_IRQn                 = 23,     /*!< EXTI[9:5] interrupts */
    TIMER0_BRK_IRQn              = 24,     /*!< TIMER0 break interrupt */
    TIMER0_UP_IRQn               = 25,     /*!< TIMER0 update interrupt */
    TIMER0_TRG_CMT_IRQn          = 26,     /*!< TIMER0 trigger and commutation interrupt */
    TIMER0_Channel_IRQn          = 27,     /*!< TIMER0 channel capture compare interrupt */
    TIMER1_IRQn                  = 28,     /*!< TIMER1 interrupt */
    TIMER2_IRQn                  = 29,     /*!< TIMER2 interrupt */
    TIMER3_IRQn                  = 30,     /*!< TIMER3 interrupt */
    I2C0_EV_IRQn                 = 31,     /*!< I2C0 event interrupt */
    I2C0_ER_IRQn                 = 32,     /*!< I2C0 error interrupt */
    I2C1_EV_IRQn                 = 33,     /*!< I2C1 event interrupt */
    I2C1_ER_IRQn                 = 34,     /*!< I2C1 error interrupt */
    SPI0_IRQn                    = 35,     /*!< SPI0 interrupt */
    SPI1_I2S1ADD_IRQn            = 36,     /*!< SPI1 or I2S1ADD interrupt */
    USART0_IRQn                  = 37,     /*!< USART0 interrupt */
    USART1_IRQn                  = 38,     /*!< USART1 interrupt */
    USART2_IRQn                  = 39,     /*!< USART2 interrupt */
    EXTI10_15_IRQn               = 40,     /*!< EXTI[15:10] interrupts */
    RTC_Alarm_IRQn               = 41,     /*!< RTC alarm interrupt */
    USBD_WKUP_IRQn               = 42,     /*!< USBD Wakeup interrupt */
    TIMER7_BRK_IRQn              = 43,     /*!< TIMER7 break interrupt */
    TIMER7_UP_IRQn               = 44,     /*!< TIMER7 update interrupt */
    TIMER7_TRG_CMT_IRQn          = 45,     /*!< TIMER7 trigger and commutation interrupt */
    TIMER7_Channel_IRQn          = 46,     /*!< TIMER7 channel capture compare interrupt */
    ADC2_IRQn                    = 47,     /*!< ADC2 global interrupt */
    EXMC_IRQn                    = 48,     /*!< EXMC global interrupt */
    TIMER4_IRQn                  = 50,     /*!< TIMER4 global interrupt */
    SPI2_I2S2ADD_IRQn            = 51,     /*!< SPI2 or I2S2ADD global interrupt */
    UART3_IRQn                   = 52,     /*!< UART3 global interrupt */
    UART4_IRQn                   = 53,     /*!< UART4 global interrupt */
    TIMER5_DAC_IRQn              = 54,     /*!< TIMER5 or DAC global interrupt */
    TIMER6_IRQn                  = 55,     /*!< TIMER6 global interrupt */
    DMA1_Channel0_IRQn           = 56,     /*!< DMA1 channel0 global interrupt */
    DMA1_Channel1_IRQn           = 57,     /*!< DMA1 channel1 global interrupt */
    DMA1_Channel2_IRQn           = 58,     /*!< DMA1 channel2 global interrupt */
    DMA1_Channel3_Channel4_IRQn  = 59,     /*!< DMA1 channel3 and channel4 global Interrupt */
    ENET_IRQn                    = 61,     /*!< ENET global interrupt */
    ENET_WKUP_IRQn               = 62,     /*!< ENET Wakeup interrupt */
    I2C2_EV_IRQn                 = 82,     /*!< I2C2 EV interrupt */
    I2C2_ER_IRQn                 = 83,     /*!< I2C2 ER interrupt */
    USART5_IRQn                  = 84,     /*!< USART5 interrupt */
    I2C2_WKUP_IRQn               = 85,     /*!< I2C2 Wakeup interrupt */
    USART5_WKUP_IRQn             = 86,     /*!< USART5 Wakeup interrupt */
#endif /* GD32EPRT */

#ifdef GD32E50X_HD
    USBD_HP_CAN0_TX_IRQn         = 19,     /*!< USBD High Priority or CAN0 TX interrupts */
    USBD_LP_CAN0_RX0_IRQn        = 20,     /*!< USBD Low Priority or CAN0 RX0 interrupts */
    CAN0_RX1_IRQn                = 21,     /*!< CAN0 RX1 interrupt */
    CAN0_EWMC_IRQn               = 22,     /*!< CAN0 EWMC interrupt */
    EXTI5_9_IRQn                 = 23,     /*!< EXTI[9:5] interrupts */
    TIMER0_BRK_TIMER8_IRQn       = 24,     /*!< TIMER0 break and TIMER8 interrupt */
    TIMER0_UP_TIMER9_IRQn        = 25,     /*!< TIMER0 update and TIMER9 interrupt */
    TIMER0_TRG_CMT_TIMER10_IRQn  = 26,     /*!< TIMER0 trigger and commutation and TIMER10 interrupt */
    TIMER0_Channel_IRQn          = 27,     /*!< TIMER0 channel capture compare interrupt */
    TIMER1_IRQn                  = 28,     /*!< TIMER1 interrupt */
    TIMER2_IRQn                  = 29,     /*!< TIMER2 interrupt */
    TIMER3_IRQn                  = 30,     /*!< TIMER3 interrupt */
    I2C0_EV_IRQn                 = 31,     /*!< I2C0 event interrupt */
    I2C0_ER_IRQn                 = 32,     /*!< I2C0 error interrupt */
    I2C1_EV_IRQn                 = 33,     /*!< I2C1 event interrupt */
    I2C1_ER_IRQn                 = 34,     /*!< I2C1 error interrupt */
    SPI0_IRQn                    = 35,     /*!< SPI0 interrupt */
    SPI1_I2S1ADD_IRQn            = 36,     /*!< SPI1 or I2S1ADD interrupt */
    USART0_IRQn                  = 37,     /*!< USART0 interrupt */
    USART1_IRQn                  = 38,     /*!< USART1 interrupt */
    USART2_IRQn                  = 39,     /*!< USART2 interrupt */
    EXTI10_15_IRQn               = 40,     /*!< EXTI[15:10] interrupts */
    RTC_Alarm_IRQn               = 41,     /*!< RTC alarm interrupt */
    USBD_WKUP_IRQn               = 42,     /*!< USBD wakeup interrupt */
    TIMER7_BRK_TIMER11_IRQn      = 43,     /*!< TIMER7 break and TIMER11 interrupt */
    TIMER7_UP_TIMER12_IRQn       = 44,     /*!< TIMER7 update and TIMER12 interrupt */
    TIMER7_TRG_CMT_TIMER13_IRQn  = 45,     /*!< TIMER7 trigger and commutation and TIMER13 interrupt */
    TIMER7_Channel_IRQn          = 46,     /*!< TIMER7 channel capture compare interrupt */
    ADC2_IRQn                    = 47,     /*!< ADC2 global interrupt */
    EXMC_IRQn                    = 48,     /*!< EXMC global interrupt */
    SDIO_IRQn                    = 49,     /*!< SDIO global interrupt */
    TIMER4_IRQn                  = 50,     /*!< TIMER4 global interrupt */
    SPI2_I2S2ADD_IRQn            = 51,     /*!< SPI2 or I2S2ADD global interrupt */
    UART3_IRQn                   = 52,     /*!< UART3 global interrupt */
    UART4_IRQn                   = 53,     /*!< UART4 global interrupt */
    TIMER5_DAC_IRQn              = 54,     /*!< TIMER5 or DAC global interrupt */
    TIMER6_IRQn                  = 55,     /*!< TIMER6 global interrupt */
    DMA1_Channel0_IRQn           = 56,     /*!< DMA1 channel0 global interrupt */
    DMA1_Channel1_IRQn           = 57,     /*!< DMA1 channel1 global interrupt */
    DMA1_Channel2_IRQn           = 58,     /*!< DMA1 channel2 global interrupt */
    DMA1_Channel3_Channel4_IRQn  = 59,     /*!< DMA1 channel3 and channel4 global interrupt */
    CAN1_TX_IRQn                 = 63,     /*!< CAN1 TX interrupt */
    CAN1_RX0_IRQn                = 64,     /*!< CAN1 RX0 interrupt */
    CAN1_RX1_IRQn                = 65,     /*!< CAN1 RX1 interrupt */
    CAN1_EWMC_IRQn               = 66,     /*!< CAN1 EWMC interrupt */
    SHRTIMER_IRQ2_IRQn           = 69,     /*!< SHRTIMER_IRQ2 interrupt */
    SHRTIMER_IRQ3_IRQn           = 70,     /*!< SHRTIMER_IRQ3 interrupt */
    SHRTIMER_IRQ4_IRQn           = 71,     /*!< SHRTIMER_IRQ4 interrupt */
    SHRTIMER_IRQ5_IRQn           = 72,     /*!< SHRTIMER_IRQ5 interrupt */
    SHRTIMER_IRQ6_IRQn           = 73,     /*!< SHRTIMER_IRQ6 interrupt */
    SHRTIMER_IRQ0_IRQn           = 76,     /*!< SHRTIMER_IRQ0 interrupt */
    SHRTIMER_IRQ1_IRQn           = 77,     /*!< SHRTIMER_IRQ1 interrupt */
    I2C2_EV_IRQn                 = 82,     /*!< I2C2 EV interrupt */
    I2C2_ER_IRQn                 = 83,     /*!< I2C2 ER interrupt */
    USART5_IRQn                  = 84,     /*!< USART5 interrupt */
    I2C2_WKUP_IRQn               = 85,     /*!< I2C2 Wakeup interrupt */
    USART5_WKUP_IRQn             = 86,     /*!< USART5 Wakeup interrupt */
#endif /* GD32E50X_HD */

#ifdef GD32E50X_CL
    CAN0_TX_IRQn                 = 19,     /*!< CAN0 TX interrupt */
    CAN0_RX0_IRQn                = 20,     /*!< CAN0 RX0 interrupt */
    CAN0_RX1_IRQn                = 21,     /*!< CAN0 RX1 interrupt */
    CAN0_EWMC_IRQn               = 22,     /*!< CAN0 EWMC interrupt */
    EXTI5_9_IRQn                 = 23,     /*!< EXTI[9:5] interrupts */
    TIMER0_BRK_TIMER8_IRQn       = 24,     /*!< TIMER0 break and TIMER8 interrupt */
    TIMER0_UP_TIMER9_IRQn        = 25,     /*!< TIMER0 update and TIMER9 interrupt */
    TIMER0_TRG_CMT_TIMER10_IRQn  = 26,     /*!< TIMER0 trigger and commutation and TIMER10 interrupt */
    TIMER0_Channel_IRQn          = 27,     /*!< TIMER0 channel capture compare interrupt */
    TIMER1_IRQn                  = 28,     /*!< TIMER1 interrupt */
    TIMER2_IRQn                  = 29,     /*!< TIMER2 interrupt */
    TIMER3_IRQn                  = 30,     /*!< TIMER3 interrupt */
    I2C0_EV_IRQn                 = 31,     /*!< I2C0 event interrupt */
    I2C0_ER_IRQn                 = 32,     /*!< I2C0 error interrupt */
    I2C1_EV_IRQn                 = 33,     /*!< I2C1 event interrupt */
    I2C1_ER_IRQn                 = 34,     /*!< I2C1 error interrupt */
    SPI0_IRQn                    = 35,     /*!< SPI0 interrupt */
    SPI1_I2S1ADD_IRQn            = 36,     /*!< SPI1 or I2S1ADD interrupt */
    USART0_IRQn                  = 37,     /*!< USART0 interrupt */
    USART1_IRQn                  = 38,     /*!< USART1 interrupt */
    USART2_IRQn                  = 39,     /*!< USART2 interrupt */
    EXTI10_15_IRQn               = 40,     /*!< EXTI[15:10] interrupts */
    RTC_Alarm_IRQn               = 41,     /*!< RTC alarm interrupt */
    USBHS_WKUP_IRQn              = 42,     /*!< USBHS wakeup interrupt */
    TIMER7_BRK_TIMER11_IRQn      = 43,     /*!< TIMER7 break and TIMER11 interrupt */
    TIMER7_UP_TIMER12_IRQn       = 44,     /*!< TIMER7 update and TIMER12 interrupt */
    TIMER7_TRG_CMT_TIMER13_IRQn  = 45,     /*!< TIMER7 trigger and commutation and TIMER13 interrupt */
    TIMER7_Channel_IRQn          = 46,     /*!< TIMER7 channel capture compare interrupt */
    EXMC_IRQn                    = 48,     /*!< EXMC global interrupt */
    TIMER4_IRQn                  = 50,     /*!< TIMER4 global interrupt */
    SPI2_I2S2ADD_IRQn            = 51,     /*!< SPI2 or I2S2ADD global interrupt */
    UART3_IRQn                   = 52,     /*!< UART3 global interrupt */
    UART4_IRQn                   = 53,     /*!< UART4 global interrupt */
    TIMER5_DAC_IRQn              = 54,     /*!< TIMER5 or DAC global interrupt */
    TIMER6_IRQn                  = 55,     /*!< TIMER6 global interrupt */
    DMA1_Channel0_IRQn           = 56,     /*!< DMA1 channel0 global interrupt */
    DMA1_Channel1_IRQn           = 57,     /*!< DMA1 channel1 global interrupt */
    DMA1_Channel2_IRQn           = 58,     /*!< DMA1 channel2 global interrupt */
    DMA1_Channel3_IRQn           = 59,     /*!< DMA1 channel3 global interrupt */
    DMA1_Channel4_IRQn           = 60,     /*!< DMA1 channel3 global interrupt */
    ENET_IRQn                    = 61,     /*!< ENET global interrupt */
    ENET_WKUP_IRQn               = 62,     /*!< ENET Wakeup interrupt */
    CAN1_TX_IRQn                 = 63,     /*!< CAN1 TX interrupt */
    CAN1_RX0_IRQn                = 64,     /*!< CAN1 RX0 interrupt */
    CAN1_RX1_IRQn                = 65,     /*!< CAN1 RX1 interrupt */
    CAN1_EWMC_IRQn               = 66,     /*!< CAN1 EWMC interrupt */
    USBHS_IRQn                   = 67,     /*!< USBHS global interrupt */
    SHRTIMER_IRQ2_IRQn           = 69,     /*!< SHRTIMER_IRQ2 interrupt */
    SHRTIMER_IRQ3_IRQn           = 70,     /*!< SHRTIMER_IRQ3 interrupt */
    SHRTIMER_IRQ4_IRQn           = 71,     /*!< SHRTIMER_IRQ4 interrupt */
    SHRTIMER_IRQ5_IRQn           = 72,     /*!< SHRTIMER_IRQ5 interrupt */
    SHRTIMER_IRQ6_IRQn           = 73,     /*!< SHRTIMER_IRQ6 interrupt */
    USBHS_EP1_OUT_IRQn           = 74,     /*!< USBHS end point 1 out interrupt */
    USBHS_EP1_IN_IRQn            = 75,     /*!< USBHS end point 1 in interrupt */
    SHRTIMER_IRQ0_IRQn           = 76,     /*!< SHRTIMER_IRQ0 interrupt */
    SHRTIMER_IRQ1_IRQn           = 77,     /*!< SHRTIMER_IRQ1 interrupt */
    CAN2_TX_IRQn                 = 78,     /*!< CAN2 TX interrupt */
    CAN2_RX0_IRQn                = 79,     /*!< CAN2 RX0 interrupt */
    CAN2_RX1_IRQn                = 80,     /*!< CAN2 RX1 interrupt */
    CAN2_EWMC_IRQn               = 81,     /*!< CAN2 EWMC interrupt */
    I2C2_EV_IRQn                 = 82,     /*!< I2C2 EV interrupt */
    I2C2_ER_IRQn                 = 83,     /*!< I2C2 ER interrupt */
    USART5_IRQn                  = 84,     /*!< USART5 global interrupt */
    I2C2_WKUP_IRQn               = 85,     /*!< I2C2 Wakeup interrupt */
    USART5_WKUP_IRQn             = 86,     /*!< USART5 Wakeup interrupt */
    TMU_IRQn                     = 87,     /*!< TMU interrupt */
#endif /* GD32E50X_CL */

#ifdef GD32E508
    CAN0_TX_IRQn                 = 19,     /*!< CAN0 TX interrupt */
    CAN0_RX0_IRQn                = 20,     /*!< CAN0 RX0 interrupt */
    CAN0_RX1_IRQn                = 21,     /*!< CAN0 RX1 interrupt */
    CAN0_EWMC_IRQn               = 22,     /*!< CAN0 EWMC interrupt */
    EXTI5_9_IRQn                 = 23,     /*!< EXTI[9:5] interrupts */
    TIMER0_BRK_TIMER8_IRQn       = 24,     /*!< TIMER0 break and TIMER8 interrupt */
    TIMER0_UP_TIMER9_IRQn        = 25,     /*!< TIMER0 update and TIMER9 interrupt */
    TIMER0_TRG_CMT_TIMER10_IRQn  = 26,     /*!< TIMER0 trigger and commutation and TIMER10 interrupt */
    TIMER0_Channel_IRQn          = 27,     /*!< TIMER0 channel capture compare interrupt */
    TIMER1_IRQn                  = 28,     /*!< TIMER1 interrupt */
    TIMER2_IRQn                  = 29,     /*!< TIMER2 interrupt */
    TIMER3_IRQn                  = 30,     /*!< TIMER3 interrupt */
    I2C0_EV_IRQn                 = 31,     /*!< I2C0 event interrupt */
    I2C0_ER_IRQn                 = 32,     /*!< I2C0 error interrupt */
    I2C1_EV_IRQn                 = 33,     /*!< I2C1 event interrupt */
    I2C1_ER_IRQn                 = 34,     /*!< I2C1 error interrupt */
    SPI0_IRQn                    = 35,     /*!< SPI0 interrupt */
    SPI1_I2S1ADD_IRQn            = 36,     /*!< SPI1 or I2S1ADD interrupt */
    USART0_IRQn                  = 37,     /*!< USART0 interrupt */
    USART1_IRQn                  = 38,     /*!< USART1 interrupt */
    USART2_IRQn                  = 39,     /*!< USART2 interrupt */
    EXTI10_15_IRQn               = 40,     /*!< EXTI[15:10] interrupts */
    RTC_Alarm_IRQn               = 41,     /*!< RTC alarm interrupt */
    USBHS_WKUP_IRQn              = 42,     /*!< USBHS wakeup interrupt */
    TIMER7_BRK_TIMER11_IRQn      = 43,     /*!< TIMER7 break and TIMER11 interrupt */
    TIMER7_UP_TIMER12_IRQn       = 44,     /*!< TIMER7 update and TIMER12 interrupt */
    TIMER7_TRG_CMT_TIMER13_IRQn  = 45,     /*!< TIMER7 trigger and commutation and TIMER13 interrupt */
    TIMER7_Channel_IRQn          = 46,     /*!< TIMER7 channel capture compare interrupt */
    EXMC_IRQn                    = 48,     /*!< EXMC global interrupt */
    TIMER4_IRQn                  = 50,     /*!< TIMER4 global interrupt */
    SPI2_I2S2ADD_IRQn            = 51,     /*!< SPI2 or I2S2ADD global interrupt */
    UART3_IRQn                   = 52,     /*!< UART3 global interrupt */
    UART4_IRQn                   = 53,     /*!< UART4 global interrupt */
    TIMER5_DAC_IRQn              = 54,     /*!< TIMER5 or DAC global interrupt */
    TIMER6_IRQn                  = 55,     /*!< TIMER6 global interrupt */
    DMA1_Channel0_IRQn           = 56,     /*!< DMA1 channel0 global interrupt */
    DMA1_Channel1_IRQn           = 57,     /*!< DMA1 channel1 global interrupt */
    DMA1_Channel2_IRQn           = 58,     /*!< DMA1 channel2 global interrupt */
    DMA1_Channel3_IRQn           = 59,     /*!< DMA1 channel3 global interrupt */
    DMA1_Channel4_IRQn           = 60,     /*!< DMA1 channel3 global interrupt */
    ENET_IRQn                    = 61,     /*!< ENET global interrupt */
    ENET_WKUP_IRQn               = 62,     /*!< ENET Wakeup interrupt */
    CAN1_TX_IRQn                 = 63,     /*!< CAN1 TX interrupt */
    CAN1_RX0_IRQn                = 64,     /*!< CAN1 RX0 interrupt */
    CAN1_RX1_IRQn                = 65,     /*!< CAN1 RX1 interrupt */
    CAN1_EWMC_IRQn               = 66,     /*!< CAN1 EWMC interrupt */
    USBHS_IRQn                   = 67,     /*!< USBHS global interrupt */
    SHRTIMER_IRQ2_IRQn           = 69,     /*!< SHRTIMER_IRQ2 interrupt */
    SHRTIMER_IRQ3_IRQn           = 70,     /*!< SHRTIMER_IRQ3 interrupt */
    SHRTIMER_IRQ4_IRQn           = 71,     /*!< SHRTIMER_IRQ4 interrupt */
    SHRTIMER_IRQ5_IRQn           = 72,     /*!< SHRTIMER_IRQ5 interrupt */
    SHRTIMER_IRQ6_IRQn           = 73,     /*!< SHRTIMER_IRQ6 interrupt */
    USBHS_EP1_OUT_IRQn           = 74,     /*!< USBHS end point 1 out interrupt */
    USBHS_EP1_IN_IRQn            = 75,     /*!< USBHS end point 1 in interrupt */
    SHRTIMER_IRQ0_IRQn           = 76,     /*!< SHRTIMER_IRQ0 interrupt */
    SHRTIMER_IRQ1_IRQn           = 77,     /*!< SHRTIMER_IRQ1 interrupt */
    CAN2_TX_IRQn                 = 78,     /*!< CAN2 TX interrupt */
    CAN2_RX0_IRQn                = 79,     /*!< CAN2 RX0 interrupt */
    CAN2_RX1_IRQn                = 80,     /*!< CAN2 RX1 interrupt */
    CAN2_EWMC_IRQn               = 81,     /*!< CAN2 EWMC interrupt */
    I2C2_EV_IRQn                 = 82,     /*!< I2C2 EV interrupt */
    I2C2_ER_IRQn                 = 83,     /*!< I2C2 ER interrupt */
    USART5_IRQn                  = 84,     /*!< USART5 global interrupt */
    I2C2_WKUP_IRQn               = 85,     /*!< I2C2 Wakeup interrupt */
    USART5_WKUP_IRQn             = 86,     /*!< USART5 Wakeup interrupt */
    TMU_IRQn                     = 87,     /*!< TMU interrupt */
#endif /* GD32E508 */
} IRQn_Type;

/* includes */
#include "core_cm33.h"
#include "system_gd32e50x.h"
#include <stdint.h>

/* enum definitions */
typedef enum {DISABLE = 0, ENABLE = !DISABLE} EventStatus, ControlStatus;
typedef enum {RESET = 0, SET = !RESET} FlagStatus;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrStatus;

/* bit operations */
#define REG64(addr)                  (*(volatile uint64_t *)(uint32_t)(addr))
#define REG32(addr)                  (*(volatile uint32_t *)(uint32_t)(addr))
#define REG16(addr)                  (*(volatile uint16_t *)(uint32_t)(addr))
#define REG8(addr)                   (*(volatile uint8_t *)(uint32_t)(addr))
#define BIT(x)                       ((uint32_t)((uint32_t)0x01U<<(x)))
#define BITS(start, end)             ((0xFFFFFFFFUL << (start)) & (0xFFFFFFFFUL >> (31U - (uint32_t)(end))))
#define GET_BITS(regval, start, end) (((regval) & BITS((start),(end))) >> (start))

/* main flash and SRAM memory map */
#define FLASH_BASE            ((uint32_t)0x08000000U)       /*!< main FLASH base address */
#define SRAM_BASE             ((uint32_t)0x20000000U)       /*!< SRAM base address */

/* peripheral memory map */
#define APB1_BUS_BASE         ((uint32_t)0x40000000U)       /*!< apb1 base address */
#define APB2_BUS_BASE         ((uint32_t)0x40010000U)       /*!< apb2 base address */
#define AHB1_BUS_BASE         ((uint32_t)0x40018000U)       /*!< ahb1 base address */
#define AHB3_BUS_BASE         ((uint32_t)0x60000000U)       /*!< ahb3 base address */

/* advanced peripheral bus 1 memory map */
#define TIMER_BASE            (APB1_BUS_BASE + 0x00000000U) /*!< TIMER base address */
#define RTC_BASE              (APB1_BUS_BASE + 0x00002800U) /*!< RTC base address */
#define WWDGT_BASE            (APB1_BUS_BASE + 0x00002C00U) /*!< WWDGT base address */
#define FWDGT_BASE            (APB1_BUS_BASE + 0x00003000U) /*!< FWDGT base address */
#define I2S_ADD_BASE          (APB1_BUS_BASE + 0x00003400U) /*!< I2S_add base address */
#define SPI_BASE              (APB1_BUS_BASE + 0x00003800U) /*!< SPI base address */
#define USART_BASE            (APB1_BUS_BASE + 0x00004400U) /*!< USART base address */
#define I2C_BASE              (APB1_BUS_BASE + 0x00005400U) /*!< I2C base address */
#define USBD_BASE             (APB1_BUS_BASE + 0x00005C00U) /*!< USBD base address */
#define USBD_RAM_BASE         (APB1_BUS_BASE + 0x00006000U) /*!< USBD RAM base address */
#define CAN_BASE              (APB1_BUS_BASE + 0x00006400U) /*!< CAN base address */
#define BKP_BASE              (APB1_BUS_BASE + 0x00006C00U) /*!< BKP base address */
#define PMU_BASE              (APB1_BUS_BASE + 0x00007000U) /*!< PMU base address */
#define DAC_BASE              (APB1_BUS_BASE + 0x00007400U) /*!< DAC base address */
#define CTC_BASE              (APB1_BUS_BASE + 0x0000C800U) /*!< CTC base address */

/* advanced peripheral bus 2 memory map */
#define AFIO_BASE             (APB2_BUS_BASE + 0x00000000U) /*!< AFIO base address */
#define EXTI_BASE             (APB2_BUS_BASE + 0x00000400U) /*!< EXTI base address */
#define GPIO_BASE             (APB2_BUS_BASE + 0x00000800U) /*!< GPIO base address */
#define ADC_BASE              (APB2_BUS_BASE + 0x00002400U) /*!< ADC base address */
#define SHRTIMER_BASE         (APB2_BUS_BASE + 0x00007400U) /*!< SHRTIMER base address */
#define CMP_BASE              (APB2_BUS_BASE + 0x00007C00U) /*!< CMP base address */

/* advanced high performance bus 1 memory map */
#define SDIO_BASE             (AHB1_BUS_BASE + 0x00000000U) /*!< SDIO base address */
#define DMA_BASE              (AHB1_BUS_BASE + 0x00008000U) /*!< DMA base address */
#define RCU_BASE              (AHB1_BUS_BASE + 0x00009000U) /*!< RCU base address */
#define FMC_BASE              (AHB1_BUS_BASE + 0x0000A000U) /*!< FMC base address */
#define CRC_BASE              (AHB1_BUS_BASE + 0x0000B000U) /*!< CRC base address */
#define ENET_BASE             (AHB1_BUS_BASE + 0x00010000U) /*!< ENET base address */
#define TMU_BASE              (AHB1_BUS_BASE + 0x00068000U) /*!< TMU base address */
#define USBHS_BASE            (AHB1_BUS_BASE + 0x0FFE8000U) /*!< USBHS base address */

/* advanced high performance bus 3 memory map */
#define EXMC_BASE             (AHB3_BUS_BASE + 0x40000000U) /*!< EXMC base address */

/* option byte and debug memory map */
#define OB_BASE               ((uint32_t)0x1FFFF800U)       /*!< OB base address */
#define DBG_BASE              ((uint32_t)0xE0044000U)       /*!< DBG base address */
#define SQPI_BASE             ((uint32_t)0xA0001000U)       /*!< SQPI base address */
#include "gd32e50x_libopt.h"

#ifdef __cplusplus
}
#endif

#endif /* GD32E50X_H */
