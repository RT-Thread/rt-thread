/*!
    \file    gd32f30x.h
    \brief   general definitions for GD32F30x

    \version 2017-02-10, V1.0.0, firmware for GD32F30x
    \version 2018-10-10, V1.1.0, firmware for GD32F30x
    \version 2018-12-25, V2.0.0, firmware for GD32F30x
    \version 2020-09-30, V2.1.0, firmware for GD32F30x
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#ifndef GD32F30X_H
#define GD32F30X_H

#ifdef __cplusplus
 extern "C" {
#endif

/* define GD32F30x */
#if !defined (GD32F30X_HD) && !defined (GD32F30X_XD) && !defined (GD32F30X_CL)
  /* #define GD32F30X_HD */
  /* #define GD32F30X_XD */
  /* #define GD32F30X_CL */
#endif /* define GD32F30x */

#if !defined (GD32F30X_HD) && !defined (GD32F30X_XD) && !defined (GD32F30X_CL)
 #error "Please select the target GD32F30x device in gd32f30x.h file"
#endif /* undefine GD32F30x tip */

/* define value of high speed crystal oscillator (HXTAL) in Hz */
#if !defined  HXTAL_VALUE
#ifdef GD32F30X_CL
#define HXTAL_VALUE    ((uint32_t)25000000) /*!< value of the external oscillator in Hz */
#else
#define HXTAL_VALUE    ((uint32_t)8000000) /* !< from 4M to 32M *!< value of the external oscillator in Hz*/
#endif /* HXTAL_VALUE */
#endif /* high speed crystal oscillator value */

/* define startup timeout value of high speed crystal oscillator (HXTAL) */
#if !defined  (HXTAL_STARTUP_TIMEOUT)
#define HXTAL_STARTUP_TIMEOUT   ((uint16_t)0xFFFF)
#endif /* high speed crystal oscillator startup timeout */

/* define value of internal 48MHz RC oscillator (IRC48M) in Hz */
#if !defined  (IRC48M_VALUE)
#define IRC48M_VALUE  ((uint32_t)48000000)
#endif /* internal 48MHz RC oscillator value */

/* define value of internal 8MHz RC oscillator (IRC8M) in Hz */
#if !defined  (IRC8M_VALUE)
#define IRC8M_VALUE  ((uint32_t)8000000)
#endif /* internal 8MHz RC oscillator value */

/* define startup timeout value of internal 8MHz RC oscillator (IRC8M) */
#if !defined  (IRC8M_STARTUP_TIMEOUT)
#define IRC8M_STARTUP_TIMEOUT   ((uint16_t)0x0500)
#endif /* internal 8MHz RC oscillator startup timeout */

/* define value of internal 40KHz RC oscillator(IRC40K) in Hz */
#if !defined  (IRC40K_VALUE)
#define IRC40K_VALUE  ((uint32_t)40000)
#endif /* internal 40KHz RC oscillator value */

/* define value of low speed crystal oscillator (LXTAL)in Hz */
#if !defined  (LXTAL_VALUE)
#define LXTAL_VALUE  ((uint32_t)32768)
#endif /* low speed crystal oscillator value */

/* GD32F30x firmware library version number V1.0 */
#define __GD32F30x_STDPERIPH_VERSION_MAIN   (0x01) /*!< [31:24] main version     */
#define __GD32F30x_STDPERIPH_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version     */
#define __GD32F30x_STDPERIPH_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version     */
#define __GD32F30x_STDPERIPH_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __GD32F30x_STDPERIPH_VERSION        ((__GD32F30x_STDPERIPH_VERSION_MAIN << 24)\
                                            |(__GD32F30x_STDPERIPH_VERSION_SUB1 << 16)\
                                            |(__GD32F30x_STDPERIPH_VERSION_SUB2 << 8)\
                                            |(__GD32F30x_STDPERIPH_VERSION_RC))

/* configuration of the Cortex-M4 processor and core peripherals */
#define __CM4_REV                 0x0001   /*!< Core revision r0p1                                       */
#define __MPU_PRESENT             1        /*!< GD32F30x provide MPU                                     */
#define __NVIC_PRIO_BITS          4        /*!< GD32F30x uses 4 bits for the priority levels             */
#define __Vendor_SysTickConfig    0        /*!< set to 1 if different sysTick config is used             */
#define __FPU_PRESENT             1        /*!< FPU present                                              */
/* define interrupt number */
typedef enum IRQn
{
    /* Cortex-M4 processor exceptions numbers */
    NonMaskableInt_IRQn          = -14,    /*!< 2 non maskable interrupt                                 */
    MemoryManagement_IRQn        = -12,    /*!< 4 Cortex-M4 memory management interrupt                  */
    BusFault_IRQn                = -11,    /*!< 5 Cortex-M4 bus fault interrupt                          */
    UsageFault_IRQn              = -10,    /*!< 6 Cortex-M4 usage fault interrupt                        */
    SVCall_IRQn                  = -5,     /*!< 11 Cortex-M4 SV call interrupt                           */
    DebugMonitor_IRQn            = -4,     /*!< 12 Cortex-M4 debug monitor interrupt                     */
    PendSV_IRQn                  = -2,     /*!< 14 Cortex-M4 pend SV interrupt                           */
    SysTick_IRQn                 = -1,     /*!< 15 Cortex-M4 system tick interrupt                       */
    /* interruput numbers */
    WWDGT_IRQn                   = 0,      /*!< window watchDog timer interrupt                          */
    LVD_IRQn                     = 1,      /*!< LVD through EXTI line detect interrupt                   */
    TAMPER_IRQn                  = 2,      /*!< tamper through EXTI line detect                          */
    RTC_IRQn                     = 3,      /*!< RTC through EXTI line interrupt                          */
    FMC_IRQn                     = 4,      /*!< FMC interrupt                                            */
    RCU_CTC_IRQn                 = 5,      /*!< RCU and CTC interrupt                                    */
    EXTI0_IRQn                   = 6,      /*!< EXTI line 0 interrupt                                    */
    EXTI1_IRQn                   = 7,      /*!< EXTI line 1 interrupt                                    */
    EXTI2_IRQn                   = 8,      /*!< EXTI line 2 interrupt                                    */
    EXTI3_IRQn                   = 9,      /*!< EXTI line 3 interrupt                                    */
    EXTI4_IRQn                   = 10,     /*!< EXTI line 4 interrupt                                    */
    DMA0_Channel0_IRQn           = 11,     /*!< DMA0 channel0 interrupt                                  */
    DMA0_Channel1_IRQn           = 12,     /*!< DMA0 channel1 interrupt                                  */
    DMA0_Channel2_IRQn           = 13,     /*!< DMA0 channel2 interrupt                                  */
    DMA0_Channel3_IRQn           = 14,     /*!< DMA0 channel3 interrupt                                  */
    DMA0_Channel4_IRQn           = 15,     /*!< DMA0 channel4 interrupt                                  */
    DMA0_Channel5_IRQn           = 16,     /*!< DMA0 channel5 interrupt                                  */
    DMA0_Channel6_IRQn           = 17,     /*!< DMA0 channel6 interrupt                                  */
    ADC0_1_IRQn                  = 18,     /*!< ADC0 and ADC1 interrupt                                  */
#ifdef GD32F30X_HD
    USBD_HP_CAN0_TX_IRQn         = 19,     /*!< CAN0 TX interrupts                                       */
    USBD_LP_CAN0_RX0_IRQn        = 20,     /*!< CAN0 RX0 interrupts                                      */
    CAN0_RX1_IRQn                = 21,     /*!< CAN0 RX1 interrupt                                       */
    CAN0_EWMC_IRQn               = 22,     /*!< CAN0 EWMC interrupt                                      */
    EXTI5_9_IRQn                 = 23,     /*!< EXTI[9:5] interrupts                                     */
    TIMER0_BRK_IRQn              = 24,     /*!< TIMER0 break interrupt                                   */
    TIMER0_UP_IRQn               = 25,     /*!< TIMER0 update interrupt                                  */
    TIMER0_TRG_CMT_IRQn          = 26,     /*!< TIMER0 trigger and commutation interrupt                 */
    TIMER0_Channel_IRQn          = 27,     /*!< TIMER0 channel capture compare interrupt                 */
    TIMER1_IRQn                  = 28,     /*!< TIMER1 interrupt                                         */
    TIMER2_IRQn                  = 29,     /*!< TIMER2 interrupt                                         */
    TIMER3_IRQn                  = 30,     /*!< TIMER3 interrupt                                         */
    I2C0_EV_IRQn                 = 31,     /*!< I2C0 event interrupt                                     */
    I2C0_ER_IRQn                 = 32,     /*!< I2C0 error interrupt                                     */
    I2C1_EV_IRQn                 = 33,     /*!< I2C1 event interrupt                                     */
    I2C1_ER_IRQn                 = 34,     /*!< I2C1 error interrupt                                     */
    SPI0_IRQn                    = 35,     /*!< SPI0 interrupt                                           */
    SPI1_IRQn                    = 36,     /*!< SPI1 interrupt                                           */
    USART0_IRQn                  = 37,     /*!< USART0 interrupt                                         */
    USART1_IRQn                  = 38,     /*!< USART1 interrupt                                         */
    USART2_IRQn                  = 39,     /*!< USART2 interrupt                                         */
    EXTI10_15_IRQn               = 40,     /*!< EXTI[15:10] interrupts                                   */
    RTC_Alarm_IRQn               = 41,     /*!< RTC alarm interrupt                                      */
    USBD_WKUP_IRQn               = 42,     /*!< USBD Wakeup interrupt                                    */
    TIMER7_BRK_IRQn              = 43,     /*!< TIMER7 break interrupt                                   */
    TIMER7_UP_IRQn               = 44,     /*!< TIMER7 update interrupt                                  */
    TIMER7_TRG_CMT_IRQn          = 45,     /*!< TIMER7 trigger and commutation interrupt                 */
    TIMER7_Channel_IRQn          = 46,     /*!< TIMER7 channel capture compare interrupt                 */
    ADC2_IRQn                    = 47,     /*!< ADC2 global interrupt                                    */
    EXMC_IRQn                    = 48,     /*!< EXMC global interrupt                                    */
    SDIO_IRQn                    = 49,     /*!< SDIO global interrupt                                    */
    TIMER4_IRQn                  = 50,     /*!< TIMER4 global interrupt                                  */
    SPI2_IRQn                    = 51,     /*!< SPI2 global interrupt                                    */
    UART3_IRQn                   = 52,     /*!< UART3 global interrupt                                   */
    UART4_IRQn                   = 53,     /*!< UART4 global interrupt                                   */
    TIMER5_IRQn                  = 54,     /*!< TIMER5 global interrupt                                  */
    TIMER6_IRQn                  = 55,     /*!< TIMER6 global interrupt                                  */
    DMA1_Channel0_IRQn           = 56,     /*!< DMA1 channel0 global interrupt                           */
    DMA1_Channel1_IRQn           = 57,     /*!< DMA1 channel1 global interrupt                           */
    DMA1_Channel2_IRQn           = 58,     /*!< DMA1 channel2 global interrupt                           */
    DMA1_Channel3_Channel4_IRQn  = 59,     /*!< DMA1 channel3 and channel4 global Interrupt              */
#endif /* GD32F30X_HD */

#ifdef GD32F30X_XD
    USBD_HP_CAN0_TX_IRQn         = 19,     /*!< CAN0 TX interrupts                                       */
    USBD_LP_CAN0_RX0_IRQn        = 20,     /*!< CAN0 RX0 interrupts                                      */
    CAN0_RX1_IRQn                = 21,     /*!< CAN0 RX1 interrupt                                       */
    CAN0_EWMC_IRQn               = 22,     /*!< CAN0 EWMC interrupt                                      */
    EXTI5_9_IRQn                 = 23,     /*!< EXTI[9:5] interrupts                                     */
    TIMER0_BRK_TIMER8_IRQn       = 24,     /*!< TIMER0 break and TIMER8 interrupt                        */
    TIMER0_UP_TIMER9_IRQn        = 25,     /*!< TIMER0 update and TIMER9 interrupt                       */
    TIMER0_TRG_CMT_TIMER10_IRQn  = 26,     /*!< TIMER0 trigger and commutation and TIMER10 interrupt     */
    TIMER0_Channel_IRQn          = 27,     /*!< TIMER0 channel capture compare interrupt                 */
    TIMER1_IRQn                  = 28,     /*!< TIMER1 interrupt                                         */
    TIMER2_IRQn                  = 29,     /*!< TIMER2 interrupt                                         */
    TIMER3_IRQn                  = 30,     /*!< TIMER3 interrupt                                         */
    I2C0_EV_IRQn                 = 31,     /*!< I2C0 event interrupt                                     */
    I2C0_ER_IRQn                 = 32,     /*!< I2C0 error interrupt                                     */
    I2C1_EV_IRQn                 = 33,     /*!< I2C1 event interrupt                                     */
    I2C1_ER_IRQn                 = 34,     /*!< I2C1 error interrupt                                     */
    SPI0_IRQn                    = 35,     /*!< SPI0 interrupt                                           */
    SPI1_IRQn                    = 36,     /*!< SPI1 interrupt                                           */
    USART0_IRQn                  = 37,     /*!< USART0 interrupt                                         */
    USART1_IRQn                  = 38,     /*!< USART1 interrupt                                         */
    USART2_IRQn                  = 39,     /*!< USART2 interrupt                                         */
    EXTI10_15_IRQn               = 40,     /*!< EXTI[15:10] interrupts                                   */
    RTC_Alarm_IRQn               = 41,     /*!< RTC alarm interrupt                                      */
    USBD_WKUP_IRQn               = 42,     /*!< USBD wakeup interrupt                                    */
    TIMER7_BRK_TIMER11_IRQn      = 43,     /*!< TIMER7 break and TIMER11 interrupt                       */
    TIMER7_UP_TIMER12_IRQn       = 44,     /*!< TIMER7 update and TIMER12 interrupt                      */
    TIMER7_TRG_CMT_TIMER13_IRQn  = 45,     /*!< TIMER7 trigger and commutation and TIMER13 interrupt     */
    TIMER7_Channel_IRQn          = 46,     /*!< TIMER7 channel capture compare interrupt                 */
    ADC2_IRQn                    = 47,     /*!< ADC2 global interrupt                                    */
    EXMC_IRQn                    = 48,     /*!< EXMC global interrupt                                    */
    SDIO_IRQn                    = 49,     /*!< SDIO global interrupt                                    */
    TIMER4_IRQn                  = 50,     /*!< TIMER4 global interrupt                                  */
    SPI2_IRQn                    = 51,     /*!< SPI2 global interrupt                                    */
    UART3_IRQn                   = 52,     /*!< UART3 global interrupt                                   */
    UART4_IRQn                   = 53,     /*!< UART4 global interrupt                                   */
    TIMER5_IRQn                  = 54,     /*!< TIMER5 global interrupt                                  */
    TIMER6_IRQn                  = 55,     /*!< TIMER6 global interrupt                                  */
    DMA1_Channel0_IRQn           = 56,     /*!< DMA1 channel0 global interrupt                           */
    DMA1_Channel1_IRQn           = 57,     /*!< DMA1 channel1 global interrupt                           */
    DMA1_Channel2_IRQn           = 58,     /*!< DMA1 channel2 global interrupt                           */
    DMA1_Channel3_Channel4_IRQn  = 59,     /*!< DMA1 channel3 and channel4 global interrupt              */
#endif /* GD32F30X_XD */

#ifdef GD32F30X_CL
    CAN0_TX_IRQn                 = 19,     /*!< CAN0 TX interrupt                                        */
    CAN0_RX0_IRQn                = 20,     /*!< CAN0 RX0 interrupt                                       */
    CAN0_RX1_IRQn                = 21,     /*!< CAN0 RX1 interrupt                                       */
    CAN0_EWMC_IRQn               = 22,     /*!< CAN0 EWMC interrupt                                      */
    EXTI5_9_IRQn                 = 23,     /*!< EXTI[9:5] interrupts                                     */
    TIMER0_BRK_TIMER8_IRQn       = 24,     /*!< TIMER0 break and TIMER8 interrupt                        */
    TIMER0_UP_TIMER9_IRQn        = 25,     /*!< TIMER0 update and TIMER9 interrupt                       */
    TIMER0_TRG_CMT_TIMER10_IRQn  = 26,     /*!< TIMER0 trigger and commutation and TIMER10 interrupt     */
    TIMER0_Channel_IRQn          = 27,     /*!< TIMER0 channel capture compare interrupt                 */
    TIMER1_IRQn                  = 28,     /*!< TIMER1 interrupt                                         */
    TIMER2_IRQn                  = 29,     /*!< TIMER2 interrupt                                         */
    TIMER3_IRQn                  = 30,     /*!< TIMER3 interrupt                                         */
    I2C0_EV_IRQn                 = 31,     /*!< I2C0 event interrupt                                     */
    I2C0_ER_IRQn                 = 32,     /*!< I2C0 error interrupt                                     */
    I2C1_EV_IRQn                 = 33,     /*!< I2C1 event interrupt                                     */
    I2C1_ER_IRQn                 = 34,     /*!< I2C1 error interrupt                                     */
    SPI0_IRQn                    = 35,     /*!< SPI0 interrupt                                           */
    SPI1_IRQn                    = 36,     /*!< SPI1 interrupt                                           */
    USART0_IRQn                  = 37,     /*!< USART0 interrupt                                         */
    USART1_IRQn                  = 38,     /*!< USART1 interrupt                                         */
    USART2_IRQn                  = 39,     /*!< USART2 interrupt                                         */
    EXTI10_15_IRQn               = 40,     /*!< EXTI[15:10] interrupts                                   */
    RTC_ALARM_IRQn               = 41,     /*!< RTC alarm interrupt                                      */
    USBFS_WKUP_IRQn              = 42,     /*!< USBFS wakeup interrupt                                   */
    TIMER7_BRK_TIMER11_IRQn      = 43,     /*!< TIMER7 break and TIMER11 interrupt                       */
    TIMER7_UP_TIMER12_IRQn       = 44,     /*!< TIMER7 update and TIMER12 interrupt                      */
    TIMER7_TRG_CMT_TIMER13_IRQn  = 45,     /*!< TIMER7 trigger and commutation and TIMER13 interrupt     */
    TIMER7_Channel_IRQn          = 46,     /*!< TIMER7 channel capture compare interrupt                 */
    EXMC_IRQn                    = 48,     /*!< EXMC global interrupt                                    */
    TIMER4_IRQn                  = 50,     /*!< TIMER4 global interrupt                                  */
    SPI2_IRQn                    = 51,     /*!< SPI2 global interrupt                                    */
    UART3_IRQn                   = 52,     /*!< UART3 global interrupt                                   */
    UART4_IRQn                   = 53,     /*!< UART4 global interrupt                                   */
    TIMER5_IRQn                  = 54,     /*!< TIMER5 global interrupt                                  */
    TIMER6_IRQn                  = 55,     /*!< TIMER6 global interrupt                                  */
    DMA1_Channel0_IRQn           = 56,     /*!< DMA1 channel0 global interrupt                           */
    DMA1_Channel1_IRQn           = 57,     /*!< DMA1 channel1 global interrupt                           */
    DMA1_Channel2_IRQn           = 58,     /*!< DMA1 channel2 global interrupt                           */
    DMA1_Channel3_IRQn           = 59,     /*!< DMA1 channel3 global interrupt                           */
    DMA1_Channel4_IRQn           = 60,     /*!< DMA1 channel3 global interrupt                           */
    ENET_IRQn                    = 61,     /*!< ENET global interrupt                                    */
    ENET_WKUP_IRQn               = 62,     /*!< ENET Wakeup interrupt                                    */
    CAN1_TX_IRQn                 = 63,     /*!< CAN1 TX interrupt                                        */
    CAN1_RX0_IRQn                = 64,     /*!< CAN1 RX0 interrupt                                       */
    CAN1_RX1_IRQn                = 65,     /*!< CAN1 RX1 interrupt                                       */
    CAN1_EWMC_IRQn               = 66,     /*!< CAN1 EWMC interrupt                                      */
    USBFS_IRQn                   = 67,     /*!< USBFS global interrupt                                   */
#endif /* GD32F30X_CL */

} IRQn_Type;

/* includes */
#include "core_cm4.h"
#include "system_gd32f30x.h"
#include <stdint.h>

/* enum definitions */
typedef enum {DISABLE = 0, ENABLE = !DISABLE} EventStatus, ControlStatus;
typedef enum {RESET = 0, SET = !RESET} FlagStatus;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrStatus;

/* bit operations */
#define REG32(addr)                  (*(volatile uint32_t *)(uint32_t)(addr))
#define REG16(addr)                  (*(volatile uint16_t *)(uint32_t)(addr))
#define REG8(addr)                   (*(volatile uint8_t *)(uint32_t)(addr))
#define BIT(x)                       ((uint32_t)((uint32_t)0x01U<<(x)))
#define BITS(start, end)             ((0xFFFFFFFFUL << (start)) & (0xFFFFFFFFUL >> (31U - (uint32_t)(end))))
#define GET_BITS(regval, start, end) (((regval) & BITS((start),(end))) >> (start))

/* main flash and SRAM memory map */
#define FLASH_BASE            ((uint32_t)0x08000000U)        /*!< main FLASH base address          */
#define SRAM_BASE             ((uint32_t)0x20000000U)        /*!< SRAM0 base address               */
#define OB_BASE               ((uint32_t)0x1FFFF800U)        /*!< OB base address                  */
#define DBG_BASE              ((uint32_t)0xE0042000U)        /*!< DBG base address                 */
#define EXMC_BASE             ((uint32_t)0xA0000000U)        /*!< EXMC register base address       */

/* peripheral memory map */
#define APB1_BUS_BASE         ((uint32_t)0x40000000U)        /*!< apb1 base address                */
#define APB2_BUS_BASE         ((uint32_t)0x40010000U)        /*!< apb2 base address                */
#define AHB1_BUS_BASE         ((uint32_t)0x40018000U)        /*!< ahb1 base address                */
#define AHB3_BUS_BASE         ((uint32_t)0x60000000U)        /*!< ahb3 base address                */

/* advanced peripheral bus 1 memory map */
#define TIMER_BASE            (APB1_BUS_BASE + 0x00000000U)  /*!< TIMER base address               */
#define RTC_BASE              (APB1_BUS_BASE + 0x00002800U)  /*!< RTC base address                 */
#define WWDGT_BASE            (APB1_BUS_BASE + 0x00002C00U)  /*!< WWDGT base address               */
#define FWDGT_BASE            (APB1_BUS_BASE + 0x00003000U)  /*!< FWDGT base address               */
#define SPI_BASE              (APB1_BUS_BASE + 0x00003800U)  /*!< SPI base address                 */
#define USART_BASE            (APB1_BUS_BASE + 0x00004400U)  /*!< USART base address               */
#define I2C_BASE              (APB1_BUS_BASE + 0x00005400U)  /*!< I2C base address                 */
#define USBD_BASE             (APB1_BUS_BASE + 0x00005C00U)  /*!< USBD base address                */
#define USBD_RAM_BASE         (APB1_BUS_BASE + 0x00006000U)  /*!< USBD RAM base address            */
#define CAN_BASE              (APB1_BUS_BASE + 0x00006400U)  /*!< CAN base address                 */
#define BKP_BASE              (APB1_BUS_BASE + 0x00006C00U)  /*!< BKP base address                 */
#define PMU_BASE              (APB1_BUS_BASE + 0x00007000U)  /*!< PMU base address                 */
#define DAC_BASE              (APB1_BUS_BASE + 0x00007400U)  /*!< DAC base address                 */
#define CTC_BASE              (APB1_BUS_BASE + 0x0000C800U)  /*!< CTC base address                 */

/* advanced peripheral bus 2 memory map */
#define AFIO_BASE             (APB2_BUS_BASE + 0x00000000U)  /*!< AFIO base address                */
#define EXTI_BASE             (APB2_BUS_BASE + 0x00000400U)  /*!< EXTI base address                */
#define GPIO_BASE             (APB2_BUS_BASE + 0x00000800U)  /*!< GPIO base address                */
#define ADC_BASE              (APB2_BUS_BASE + 0x00002400U)  /*!< ADC base address                 */

/* advanced high performance bus 1 memory map */
#define SDIO_BASE             (AHB1_BUS_BASE + 0x00000000U)  /*!< SDIO base address                */
#define DMA_BASE              (AHB1_BUS_BASE + 0x00008000U)  /*!< DMA base address                 */
#define RCU_BASE              (AHB1_BUS_BASE + 0x00009000U)  /*!< RCU base address                 */
#define FMC_BASE              (AHB1_BUS_BASE + 0x0000A000U)  /*!< FMC base address                 */
#define CRC_BASE              (AHB1_BUS_BASE + 0x0000B000U)  /*!< CRC base address                 */
#define ENET_BASE             (AHB1_BUS_BASE + 0x00010000U)  /*!< ENET base address                */
#define USBFS_BASE            (AHB1_BUS_BASE + 0x0FFE8000U)  /*!< USBFS base address               */

/* define marco USE_STDPERIPH_DRIVER */
#if !defined  USE_STDPERIPH_DRIVER
#define USE_STDPERIPH_DRIVER
#endif
#ifdef USE_STDPERIPH_DRIVER
#include "gd32f30x_libopt.h"
#endif /* USE_STDPERIPH_DRIVER */

#ifdef __cplusplus
}
#endif
#endif
