/*!
    \file    gd32e230.h
    \brief   general definitions for GD32E230
    
    \version 2018-06-19, V1.0.0, firmware for GD32E230
*/

/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.

    All rights reserved.

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

#ifndef GD32E230_H
#define GD32E230_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* define GD32E230 */
#if !defined (GD32E230)
 #define GD32E230
#endif /* define GD32E230 */
#if !defined (GD32E230)
 #error "Please select the target GD32E230 device used in your application (in gd32e230.h file)"
#endif /* undefine GD32E230 tip */

/* define value of high speed crystal oscillator (HXTAL) in Hz */
#if !defined  (HXTAL_VALUE)
#define HXTAL_VALUE    ((uint32_t)8000000)
#endif /* high speed crystal oscillator value */

/* define startup timeout value of high speed crystal oscillator (HXTAL) */
#if !defined  (HXTAL_STARTUP_TIMEOUT)
#define HXTAL_STARTUP_TIMEOUT   ((uint16_t)0x0800)
#endif /* high speed crystal oscillator startup timeout */

/* define value of internal 8MHz RC oscillator (IRC8M) in Hz */
#if !defined  (IRC8M_VALUE) 
#define IRC8M_VALUE  ((uint32_t)8000000)
#endif /* internal 8MHz RC oscillator value */

/* define startup timeout value of internal 8MHz RC oscillator (IRC8M) */
#if !defined  (IRC8M_STARTUP_TIMEOUT)
#define IRC8M_STARTUP_TIMEOUT   ((uint16_t)0x0500)
#endif /* internal 8MHz RC oscillator startup timeout */

/* define value of internal RC oscillator for ADC in Hz */
#if !defined  (IRC28M_VALUE) 
#define IRC28M_VALUE ((uint32_t)28000000)
#endif /* IRC28M_VALUE */

#if !defined  (IRC48M_VALUE) 
#define IRC48M_VALUE ((uint32_t)48000000)
#endif /* IRC48M_VALUE */

/* define value of internal 40KHz RC oscillator(IRC40K) in Hz */
#if !defined  (IRC40K_VALUE) 
#define IRC40K_VALUE  ((uint32_t)40000)
#endif /* internal 40KHz RC oscillator value */

/* define value of low speed crystal oscillator (LXTAL)in Hz */
#if !defined  (LXTAL_VALUE) 
#define LXTAL_VALUE  ((uint32_t)32768)
#endif /* low speed crystal oscillator value */

/* GD32E1x0 firmware library version number V1.0 */
#define __GD32E230_STDPERIPH_VERSION_MAIN   (0x01) /*!< [31:24] main version     */
#define __GD32E230_STDPERIPH_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version     */
#define __GD32E230_STDPERIPH_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version     */
#define __GD32E230_STDPERIPH_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __GD32E230_STDPERIPH_VERSION        ((__GD32E230_STDPERIPH_VERSION_MAIN << 24)\
                                            |(__GD32E230_STDPERIPH_VERSION_SUB1 << 16)\
                                            |(__GD32E230_STDPERIPH_VERSION_SUB2 << 8)\
                                            |(__GD32E230_STDPERIPH_VERSION_RC))

/* configuration of the Cortex-M23 processor and core peripherals                                        */
#define __CM23_REV                0x0100U   /*!< Core revision r1p0                                      */
#define __SAUREGION_PRESENT       0U        /*!< SAU regions are not present                             */
#define __MPU_PRESENT             0U        /*!< MPU is present                                          */
#define __VTOR_PRESENT            1U        /*!< VTOR is present                                         */
#define __NVIC_PRIO_BITS          2U        /*!< Number of Bits used for Priority Levels                 */
#define __Vendor_SysTickConfig    0U        /*!< Set to 1 if different SysTick Config is used            */

/* define interrupt number */
typedef enum IRQn
{
    /* Cortex-M23 processor exceptions numbers */
    NonMaskableInt_IRQn          = -14,    /*!< non maskable interrupt                                   */
    HardFault_IRQn               = -13,    /*!< hardfault interrupt                                      */

    SVCall_IRQn                  = -5,     /*!< sv call interrupt                                        */

    PendSV_IRQn                  = -2,     /*!< pend sv interrupt                                        */
    SysTick_IRQn                 = -1,     /*!< system tick interrupt                                    */
    /* interruput numbers */
    WWDGT_IRQn                   = 0,      /*!< window watchdog timer interrupt                          */
    LVD_IRQn                     = 1,      /*!< LVD through EXTI line detect interrupt                   */
    RTC_IRQn                     = 2,      /*!< RTC through EXTI line interrupt                          */
    FMC_IRQn                     = 3,      /*!< FMC interrupt                                            */
    RCU_IRQn                     = 4,      /*!< RCU interrupt                                            */
    EXTI0_1_IRQn                 = 5,      /*!< EXTI line 0 and 1 interrupts                             */
    EXTI2_3_IRQn                 = 6,      /*!< EXTI line 2 and 3 interrupts                             */
    EXTI4_15_IRQn                = 7,      /*!< EXTI line 4 to 15 interrupts                             */
    DMA_Channel0_IRQn            = 9,      /*!< DMA channel 0 interrupt                                  */
    DMA_Channel1_2_IRQn          = 10,     /*!< DMA channel 1 and channel 2 interrupts                   */
    DMA_Channel3_4_IRQn          = 11,     /*!< DMA channel 3 and channel 4 interrupts                   */
    ADC_CMP_IRQn                 = 12,     /*!< ADC, CMP interrupts                            */
    TIMER0_BRK_UP_TRG_COM_IRQn   = 13,     /*!< TIMER0 break, update, trigger and commutation interrupts */
    TIMER0_Channel_IRQn          = 14,     /*!< TIMER0 channel capture compare interrupts                */
    TIMER2_IRQn                  = 16,     /*!< TIMER2 interrupt                                         */
    TIMER5_IRQn                  = 17,     /*!< TIMER5 interrupt                                         */
    TIMER13_IRQn                 = 19,     /*!< TIMER13 interrupt                                        */
    TIMER14_IRQn                 = 20,     /*!< TIMER14 interrupt                                        */
    TIMER15_IRQn                 = 21,     /*!< TIMER15 interrupt                                        */
    TIMER16_IRQn                 = 22,     /*!< TIMER16 interrupt                                        */
    I2C0_EV_IRQn                 = 23,     /*!< I2C0 event interrupt                                     */
    I2C1_EV_IRQn                 = 24,     /*!< I2C1 event interrupt                                     */
    SPI0_IRQn                    = 25,     /*!< SPI0 interrupt                                           */
    SPI1_IRQn                    = 26,     /*!< SPI1 interrupt                                           */
    USART0_IRQn                  = 27,     /*!< USART0 interrupt                                         */
    USART1_IRQn                  = 28,     /*!< USART1 interrupt                                         */
    I2C0_ER_IRQn                 = 32,     /*!< I2C0 error interrupt                                     */
    I2C1_ER_IRQn                 = 34,     /*!< I2C1 error interrupt                                     */
} IRQn_Type;

/* includes */
#include "core_cm23.h"
#include "system_gd32e230.h"
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
#define FLASH_BASE            ((uint32_t)0x08000000U)       /*!< main FLASH base address          */
#define SRAM_BASE             ((uint32_t)0x20000000U)       /*!< SRAM base address                */
/* SRAM and peripheral base bit-band region */
#define SRAM_BB_BASE          ((uint32_t)0x22000000U)       /*!< SRAM bit-band base address       */
#define PERIPH_BB_BASE        ((uint32_t)0x42000000U)       /*!< peripheral bit-band base address */
/* peripheral memory map */
#define APB1_BUS_BASE         ((uint32_t)0x40000000U)       /*!< apb1 base address                */
#define APB2_BUS_BASE         ((uint32_t)0x40010000U)       /*!< apb2 base address                */
#define AHB1_BUS_BASE         ((uint32_t)0x40020000U)       /*!< ahb1 base address                */
#define AHB2_BUS_BASE         ((uint32_t)0x48000000U)       /*!< ahb2 base address                */
/* advanced peripheral bus 1 memory map */
#define TIMER_BASE            (APB1_BUS_BASE + 0x00000000U) /*!< TIMER base address               */
#define RTC_BASE              (APB1_BUS_BASE + 0x00002800U) /*!< RTC base address                 */
#define WWDGT_BASE            (APB1_BUS_BASE + 0x00002C00U) /*!< WWDGT base address               */
#define FWDGT_BASE            (APB1_BUS_BASE + 0x00003000U) /*!< FWDGT base address               */
#define SPI_BASE              (APB1_BUS_BASE + 0x00003800U) /*!< SPI base address                 */
#define USART_BASE            (APB1_BUS_BASE + 0x00004400U) /*!< USART base address               */
#define I2C_BASE              (APB1_BUS_BASE + 0x00005400U) /*!< I2C base address                 */
#define PMU_BASE              (APB1_BUS_BASE + 0x00007000U) /*!< PMU base address                 */
/* advanced peripheral bus 2 memory map */
#define SYSCFG_BASE           (APB2_BUS_BASE + 0x00000000U) /*!< SYSCFG base address              */
#define CMP_BASE              (APB2_BUS_BASE + 0x0000001CU) /*!< CMP base address                 */
#define EXTI_BASE             (APB2_BUS_BASE + 0x00000400U) /*!< EXTI base address                */
#define ADC_BASE              (APB2_BUS_BASE + 0x00002400U) /*!< ADC base address                 */
/* advanced high performance bus 1 memory map */
#define DMA_BASE              (AHB1_BUS_BASE + 0x00000000U) /*!< DMA base address                 */
#define DMA_CHANNEL_BASE      (DMA_BASE + 0x00000008U)      /*!< DMA channel base address         */
#define RCU_BASE              (AHB1_BUS_BASE + 0x00001000U) /*!< RCU base address                 */
#define FMC_BASE              (AHB1_BUS_BASE + 0x00002000U) /*!< FMC base address                 */
#define CRC_BASE              (AHB1_BUS_BASE + 0x00003000U) /*!< CRC base address                 */
/* advanced high performance bus 2 memory map */
#define GPIO_BASE             (AHB2_BUS_BASE + 0x00000000U) /*!< GPIO base address                */
/* option byte and debug memory map */
#define OB_BASE               ((uint32_t)0x1FFFF800U)       /*!< OB base address                  */
#define DBG_BASE              ((uint32_t)0x40015800U)       /*!< DBG base address                 */

#include "gd32e230_libopt.h"

#ifdef __cplusplus
}
#endif

#endif /* GD32E230_H */
