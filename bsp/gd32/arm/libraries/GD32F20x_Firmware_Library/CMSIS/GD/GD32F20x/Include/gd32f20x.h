/*!
    \file    gd32f20x.h
    \brief   general definitions for GD32F20x

    \version 2015-07-15, V1.0.0, firmware for GD32F20x
    \version 2017-06-05, V2.0.0, firmware for GD32F20x
    \version 2018-10-31, V2.1.0, firmware for GD32F20x
    \version 2020-09-30, V2.2.0, firmware for GD32F20x
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

#ifndef GD32F20X_H
#define GD32F20X_H

#ifdef cplusplus
 extern "C" {
#endif

/* define GD32F20x */
#if !defined (GD32F20X_CL)
 #error "Please select first the target gd32f20x device used in your application (in gd32f20x.h file)"
#endif /* GD32F20X */

/* define value of high speed crystal oscillator (HXTAL) in Hz */
#if !defined  HXTAL_VALUE
#ifdef GD32F20X_CL
#define HXTAL_VALUE    ((uint32_t)25000000) /*!< value of the external oscillator in Hz */
#endif /* HXTAL_VALUE */
#endif /* high speed crystal oscillator value */

/* define startup timeout value of high speed crystal oscillator (HXTAL) */
#if !defined  (HXTAL_STARTUP_TIMEOUT)
#define HXTAL_STARTUP_TIMEOUT   ((uint16_t)0xFFFF)
#endif /* high speed crystal oscillator startup timeout */

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

/* GD32F20x firmware library version number V2.0 */
#define __GD32F20x_STDPERIPH_VERSION_MAIN   (0x01) /*!< [31:24] main version     */
#define __GD32F20x_STDPERIPH_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version     */
#define __GD32F20x_STDPERIPH_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version     */
#define __GD32F20x_STDPERIPH_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __GD32F20x_STDPERIPH_VERSION        ((__GD32F20x_STDPERIPH_VERSION_MAIN << 24)\
                                            |(__GD32F20x_STDPERIPH_VERSION_SUB1 << 16)\
                                            |(__GD32F20x_STDPERIPH_VERSION_SUB2 << 8)\
                                            |(__GD32F20x_STDPERIPH_VERSION_RC))

/* configuration of the Cortex-M3 processor and core peripherals */
#define __MPU_PRESENT             0        /*!< GD32 devices does not provide an MPU */
#define __NVIC_PRIO_BITS          4        /*!< GD32F20X uses 4 bits for the Priority levels        */
#define __VENDOR_SYSTICKCONFIG    0        /*!< set to 1 if different systick config is used        */

/* define interrupt number */
typedef enum IRQn
{
    /* Cortex-M3 processor exceptions numbers */
    NonMaskableInt_IRQn         = -14,    /*!< 2 non maskable interrupt                                              */
    MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 memory management interrupt                               */
    BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 bus fault interrupt                                       */
    UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 usage fault interrupt                                     */
    SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV call interrupt                                        */
    DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 debug monitor interrupt                                  */
    PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 pend SV interrupt                                        */
    SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 system tick interrupt                                    */
    /* interruput numbers */
    WWDGT_IRQn                  = 0,      /*!< WWDGT interrupt                                                       */
    LVD_IRQn                    = 1,      /*!< LVD from EXTI line interrupt                                          */
    TAMPER_IRQn                 = 2,      /*!< tamper interrupt                                                      */
    RTC_IRQn                    = 3,      /*!< RTC global interrupt                                                  */
    FMC_IRQn                    = 4,      /*!< FMC global interrupt                                                  */
    RCU_IRQn                    = 5,      /*!< RCU global interrupt                                                  */
    EXTI0_IRQn                  = 6,      /*!< EXTI line0 interrupt                                                  */
    EXTI1_IRQn                  = 7,      /*!< EXTI line1 interrupt                                                  */
    EXTI2_IRQn                  = 8,      /*!< EXTI line2 interrupt                                                  */
    EXTI3_IRQn                  = 9,      /*!< EXTI line3 interrupt                                                  */
    EXTI4_IRQn                  = 10,     /*!< EXTI line4 interrupt                                                  */
    DMA0_Channel0_IRQn          = 11,     /*!< DMA0 channel 0 global interrupt                                       */
    DMA0_Channel1_IRQn          = 12,     /*!< DMA0 channel 1 global interrupt                                       */
    DMA0_Channel2_IRQn          = 13,     /*!< DMA0 channel 2 global interrupt                                       */
    DMA0_Channel3_IRQn          = 14,     /*!< DMA0 channel 3 global interrupt                                       */
    DMA0_Channel4_IRQn          = 15,     /*!< DMA0 channel 4 global interrupt                                       */
    DMA0_Channel5_IRQn          = 16,     /*!< DMA0 channel 5 global interrupt                                       */
    DMA0_Channel6_IRQn          = 17,     /*!< DMA0 channel 6 global interrupt                                       */
    ADC0_1_IRQn                 = 18,     /*!< ADC0 and ADC1 global interrupts                                       */
    CAN0_TX_IRQn                = 19,     /*!< CAN0 TX interrupt                                                     */
    CAN0_RX0_IRQn               = 20,     /*!< CAN0 RX0 interrupt                                                    */
    CAN0_RX1_IRQn               = 21,     /*!< CAN0 RX1 interrupt                                                    */
    CAN0_EWMC_IRQn              = 22,     /*!< CAN0 EWMC interrupt                                                   */
    EXTI5_9_IRQn                = 23,     /*!< EXTI[9:5] interrupts                                                  */
    TIMER0_BRK_TIMER8_IRQn      = 24,     /*!< TIMER0 break interrupt and TIMER8 global interrupt                    */
    TIMER0_UP_TIMER9_IRQn       = 25,     /*!< TIMER0 update Interrupt and TIMER9 global interrupt                   */
    TIMER0_TRG_CMT_TIMER10_IRQn = 26,     /*!< TIMER0 trigger and commutation interrupt and TIMER10 global interrupt */
    TIMER0_Channel_IRQn         = 27,     /*!< TIMER0 channel capture compare interrupt                                      */
    TIMER1_IRQn                 = 28,     /*!< TIMER1 global interrupt                                               */
    TIMER2_IRQn                 = 29,     /*!< TIMER2 global interrupt                                               */
    TIMER3_IRQn                 = 30,     /*!< TIMER3 global interrupt                                               */
    I2C0_EV_IRQn                = 31,     /*!< I2C0 event interrupt                                                  */
    I2C0_ER_IRQn                = 32,     /*!< I2C0 error interrupt                                                  */
    I2C1_EV_IRQn                = 33,     /*!< I2C1 event interrupt                                                  */
    I2C1_ER_IRQn                = 34,     /*!< I2C1 error interrupt                                                  */
    SPI0_IRQn                   = 35,     /*!< SPI0 global interrupt                                                 */
    SPI1_IRQn                   = 36,     /*!< SPI1 global interrupt                                                 */
    USART0_IRQn                 = 37,     /*!< USART0 global interrupt                                               */
    USART1_IRQn                 = 38,     /*!< USART1 global interrupt                                               */
    USART2_IRQn                 = 39,     /*!< USART2 global interrupt                                               */
    EXTI10_15_IRQn              = 40,     /*!< EXTI[15:10] interrupts                                                */
    RTC_Alarm_IRQn              = 41,     /*!< RTC alarm from EXTI line interrupt                                    */
    USBFS_WKUP_IRQn             = 42,     /*!< USBFS wakeUp from EXTI line interrupt                                 */
    TIMER7_BRK_TIMER11_IRQn     = 43,     /*!< TIMER7 break interrupt and TIMER11 global interrupt                   */
    TIMER7_UP_TIMER12_IRQn      = 44,     /*!< TIMER7 update interrupt and TIMER12 global interrupt                  */
    TIMER7_TRG_CMT_TIMER13_IRQn = 45,     /*!< TIMER7 trigger and commutation interrupt and TIMER13 global interrupt */
    TIMER7_Channel_IRQn         = 46,     /*!< TIMER7 Channel Capture Compare Interrupt                                      */
    ADC2_IRQn                   = 47,     /*!< ADC2 global interrupt                                                 */
    EXMC_IRQn                   = 48,     /*!< EXMC global interrupt                                                 */
    SDIO_IRQn                   = 49,     /*!< SDIO global interrupt                                                 */
    TIMER4_IRQn                 = 50,     /*!< TIMER4 global interrupt                                               */
    SPI2_IRQn                   = 51,     /*!< SPI2 global interrupt                                                 */
    UART3_IRQn                  = 52,     /*!< UART3 global interrupt                                                */
    UART4_IRQn                  = 53,     /*!< UART4 global interrupt                                                */
    TIMER5_IRQn                 = 54,     /*!< TIMER5 global interrupt                                               */
    TIMER6_IRQn                 = 55,     /*!< TIMER6 global interrupt                                               */
    DMA1_Channel0_IRQn          = 56,     /*!< DMA1 Channel 0 global interrupt                                       */
    DMA1_Channel1_IRQn          = 57,     /*!< DMA1 Channel 1 global interrupt                                       */
    DMA1_Channel2_IRQn          = 58,     /*!< DMA1 Channel 2 global interrupt                                       */
    DMA1_Channel3_IRQn          = 59,     /*!< DMA1 Channel 3 global interrupt                                       */
    DMA1_Channel4_IRQn          = 60,     /*!< DMA1 Channel 4 global interrupt                                       */
    ENET_IRQn                   = 61,     /*!< ENET global interrupt                                                 */
    ENET_WKUP_IRQn              = 62,     /*!< ENET wakeup through EXTI line interrupt                               */
    CAN1_TX_IRQn                = 63,     /*!< CAN1 TX interrupt                                                     */
    CAN1_RX0_IRQn               = 64,     /*!< CAN1 RX0 interrupt                                                    */
    CAN1_RX1_IRQn               = 65,     /*!< CAN1 RX1 interrupt                                                    */
    CAN1_EWMC_IRQn              = 66,     /*!< CAN1 EWMC interrupt                                                   */
    USBFS_IRQn                  = 67,      /*!< USBFS global interrupt                                               */
    DMA1_Channel5_IRQn          = 69,      /*!< DMA1 Channel 5 global interrupt                                      */
    DMA1_Channel6_IRQn          = 70,      /*!< DMA1 Channel 6 global interrupt                                      */
    USART5_IRQn                 = 71,      /*!< USART5 global interrupt                                              */
    I2C2_EV_IRQn                = 72,      /*!< I2C2 event interrupt                                                 */
    I2C2_ER_IRQn                = 73,      /*!< I2C2 error interrupt                                                 */
    DCI_IRQn                    = 78,      /*!< DCI global interrupt                                                 */
    CAU_IRQn                    = 79,      /*!< CAU global interrupt                                                 */
    HAU_TRNG_IRQn               = 80,      /*!< HAU or TRNG global interrupt                                         */
    UART6_IRQn                  = 82,      /*!< UART6 global interrupt                                               */
    UART7_IRQn                  = 83,      /*!< UART7 global interrupt                                               */
    TLI_IRQn                    = 88,      /*!< TLI global interrupt                                                 */
    TLI_ER_IRQn                 = 89       /*!< TLI global error interrupt                                           */
} IRQn_Type;

/* includes */
#include "core_cm3.h"
#include "system_gd32f20x.h"
#include <stdint.h>

/* enum definitions */
typedef enum {DISABLE = 0, ENABLE = !DISABLE} EventStatus, ControlStatus;
typedef enum {FALSE = 0, TRUE = !FALSE} bool;
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
#define FLASH_BASE            ((uint32_t)0x08000000U)        /*!< main FLASH base address                         */
#define SRAM_BASE             ((uint32_t)0x20000000U)        /*!< SRAM base address                               */
#define OB_BASE               ((uint32_t)0x1FFFF800U)        /*!< OB base address                                 */
#define SRAM_BB_BASE          ((uint32_t)0x22000000)         /*!< SRAM base address in the bit-band region        */
#define PERIPH_BB_BASE        ((uint32_t)0x42000000)         /*!< Peripheral base address in the bit-band region  */
#define DBG_BASE              ((uint32_t)0xE0042000U)        /*!< DBG base address                                */
#define EXMC_BASE             ((uint32_t)0xA0000000U)        /*!< EXMC register base address                      */

/* peripheral memory map */
#define APB1_BUS_BASE         ((uint32_t)0x40000000U)        /*!< apb1 base address                               */
#define APB2_BUS_BASE         ((uint32_t)0x40010000U)        /*!< apb2 base address                               */
#define AHB1_BUS_BASE         ((uint32_t)0x40018000U)        /*!< ahb1 base address                               */
#define AHB2_BUS_BASE         ((uint32_t)0x50000000U)        /*!< ahb2 base address                               */

/* advanced peripheral bus 1 memory map */
#define TIMER_BASE            (APB1_BUS_BASE + 0x00000000U)  /*!< TIMER base address                              */
#define RTC_BASE              (APB1_BUS_BASE + 0x00002800U)  /*!< RTC base address                                */
#define WWDGT_BASE            (APB1_BUS_BASE + 0x00002C00U)  /*!< WWDGT base address                              */
#define FWDGT_BASE            (APB1_BUS_BASE + 0x00003000U)  /*!< FWDGT base address                              */
#define SPI_BASE              (APB1_BUS_BASE + 0x00003800U)  /*!< SPI base address                                */
#define USART_BASE            (APB1_BUS_BASE + 0x00004400U)  /*!< USART base address                              */
#define I2C_BASE              (APB1_BUS_BASE + 0x00005400U)  /*!< I2C base address                                */
#define CAN_BASE              (APB1_BUS_BASE + 0x00006400U)  /*!< CAN base address                                */
#define BKP_BASE              (APB1_BUS_BASE + 0x00006C00U)  /*!< BKP base address                                */
#define PMU_BASE              (APB1_BUS_BASE + 0x00007000U)  /*!< PMU base address                                */
#define DAC_BASE              (APB1_BUS_BASE + 0x00007400U)  /*!< DAC base address                                */

/* advanced peripheral bus 2 memory map */
#define AFIO_BASE             (APB2_BUS_BASE + 0x00000000U)  /*!< AFIO base address                               */
#define EXTI_BASE             (APB2_BUS_BASE + 0x00000400U)  /*!< EXTI base address                               */
#define GPIO_BASE             (APB2_BUS_BASE + 0x00000800U)  /*!< GPIO base address                               */
#define ADC_BASE              (APB2_BUS_BASE + 0x00002400U)  /*!< ADC base address                                */
#define TLI_BASE              (APB2_BUS_BASE + 0x00006800U)  /*!< TLI base address                                */

/* advanced high performance bus 1 memory map */
#define SDIO_BASE             (AHB1_BUS_BASE + 0x00000000U)  /*!< SDIO base address                               */
#define DMA_BASE              (AHB1_BUS_BASE + 0x00008000U)  /*!< DMA base address                                */
#define RCU_BASE              (AHB1_BUS_BASE + 0x00009000U)  /*!< RCU base address                                */
#define FMC_BASE              (AHB1_BUS_BASE + 0x0000A000U)  /*!< FMC base address                                */
#define CRC_BASE              (AHB1_BUS_BASE + 0x0000B000U)  /*!< CRC base address                                */
#define ENET_BASE             (AHB1_BUS_BASE + 0x00010000U)  /*!< ENET base address                               */

/* advanced high performance bus 2 memory map */
#define USBFS_BASE            (AHB2_BUS_BASE + 0x00000000U)  /*!< USBFS base address                              */
#define DCI_BASE              (AHB2_BUS_BASE + 0x00050000U)  /*!< DCI base address                                */
#define CAU_BASE              (AHB2_BUS_BASE + 0x00060000U)  /*!< CAU base address                                */
#define HAU_BASE              (AHB2_BUS_BASE + 0x00060400U)  /*!< HAU base address                                */
#define TRNG_BASE             (AHB2_BUS_BASE + 0x00060800U)  /*!< TRNG base address                               */

/* define marco USE_STDPERIPH_DRIVER */
#if !defined  USE_STDPERIPH_DRIVER
#define USE_STDPERIPH_DRIVER
#endif
#ifdef USE_STDPERIPH_DRIVER
#include "gd32f20x_libopt.h"
#endif /* USE_STDPERIPH_DRIVER */

#ifdef cplusplus
}
#endif
#endif
