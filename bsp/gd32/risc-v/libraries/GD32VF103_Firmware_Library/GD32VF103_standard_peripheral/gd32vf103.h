/*!
    \file    gd32vf103.h
    \brief   general definitions for GD32VF103

    \version 2019-06-05, V1.0.0, firmware for GD32VF103
    \version 2020-08-04, V1.1.0, firmware for GD32VF103
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

#ifndef GD32VF103_H
#define GD32VF103_H

#ifdef __cplusplus
 extern "C" {
#endif

 /* IO definitions (access restrictions to peripheral registers) */
 /**

     <strong>IO Type Qualifiers</strong> are used
     \li to specify the access to peripheral variables.
     \li for automatic generation of peripheral register debug information.
 */
 #ifdef __cplusplus
   #define   __I     volatile             /*!< Defines 'read only' permissions                 */
 #else
   #define   __I     volatile const       /*!< Defines 'read only' permissions                 */
 #endif
 #define     __O     volatile             /*!< Defines 'write only' permissions                */
 #define     __IO    volatile             /*!< Defines 'read / write' permissions              */

 /* define value of high speed crystal oscillator (HXTAL) in Hz */
 #if !defined  HXTAL_VALUE
   #ifdef GD32VF103R_START
   #define HXTAL_VALUE    ((uint32_t)25000000) /*!< value of the external oscillator in Hz */
   #define HXTAL_VALUE_8M  HXTAL_VALUE
#elif defined(GD32VF103V_EVAL) || defined(GD32VF103C_START) || defined(GD32VF103T_START)
   #define HXTAL_VALUE    ((uint32_t)8000000) /*!< value of the external oscillator in Hz */
   #define HXTAL_VALUE_25M  HXTAL_VALUE
   #else
   #error "Please select the target board type used in your application (in gd32vf103.h file)"
   #endif
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

/* define interrupt number */
typedef enum IRQn
{

    CLIC_INT_RESERVED            = 0,       /*!< RISC-V reserved                                        */
    CLIC_INT_SFT                 = 3,       /*!< Software interrupt                                     */
    CLIC_INT_TMR                 = 7,       /*!< CPU Timer interrupt                                    */
    CLIC_INT_BWEI                = 17,      /*!< Bus Error interrupt                                    */
    CLIC_INT_PMOVI               = 18,      /*!< Performance Monitor                                    */

    /* interruput numbers */
    WWDGT_IRQn                   = 19,      /*!< window watchDog timer interrupt                         */
    LVD_IRQn                     = 20,      /*!< LVD through EXTI line detect interrupt                  */
    TAMPER_IRQn                  = 21,      /*!< tamper through EXTI line detect                         */
    RTC_IRQn                     = 22,      /*!< RTC alarm interrupt                                     */
    FMC_IRQn                     = 23,      /*!< FMC interrupt                                           */
    RCU_CTC_IRQn                 = 24,      /*!< RCU and CTC interrupt                                   */
    EXTI0_IRQn                   = 25,      /*!< EXTI line 0 interrupts                                  */
    EXTI1_IRQn                   = 26,      /*!< EXTI line 1 interrupts                                  */
    EXTI2_IRQn                   = 27,      /*!< EXTI line 2 interrupts                                  */
    EXTI3_IRQn                   = 28,      /*!< EXTI line 3 interrupts                                  */
    EXTI4_IRQn                   = 29,     /*!< EXTI line 4 interrupts                                   */
    DMA0_Channel0_IRQn           = 30,     /*!< DMA0 channel0 interrupt                                  */
    DMA0_Channel1_IRQn           = 31,     /*!< DMA0 channel1 interrupt                                  */
    DMA0_Channel2_IRQn           = 32,     /*!< DMA0 channel2 interrupt                                  */
    DMA0_Channel3_IRQn           = 33,     /*!< DMA0 channel3 interrupt                                  */
    DMA0_Channel4_IRQn           = 34,     /*!< DMA0 channel4 interrupt                                  */
    DMA0_Channel5_IRQn           = 35,     /*!< DMA0 channel5 interrupt                                  */
    DMA0_Channel6_IRQn           = 36,     /*!< DMA0 channel6 interrupt                                  */
    ADC0_1_IRQn                  = 37,     /*!< ADC0 and ADC1 interrupt                                  */
    CAN0_TX_IRQn                 = 38,     /*!< CAN0 TX interrupts                                       */
    CAN0_RX0_IRQn                = 39,     /*!< CAN0 RX0 interrupts                                      */
    CAN0_RX1_IRQn                = 40,     /*!< CAN0 RX1 interrupts                                      */
    CAN0_EWMC_IRQn               = 41,     /*!< CAN0 EWMC interrupts                                     */
    EXTI5_9_IRQn                 = 42,     /*!< EXTI[9:5] interrupts                                     */
    TIMER0_BRK_IRQn              = 43,     /*!< TIMER0 break interrupts                                  */
    TIMER0_UP_IRQn               = 44,     /*!< TIMER0 update interrupts                                 */
    TIMER0_TRG_CMT_IRQn          = 45,     /*!< TIMER0 trigger and commutation interrupts                */
    TIMER0_Channel_IRQn          = 46,     /*!< TIMER0 channel capture compare interrupts                */
    TIMER1_IRQn                  = 47,     /*!< TIMER1 interrupt                                         */
    TIMER2_IRQn                  = 48,     /*!< TIMER2 interrupt                                         */
    TIMER3_IRQn                  = 49,     /*!< TIMER3 interrupts                                        */
    I2C0_EV_IRQn                 = 50,     /*!< I2C0 event interrupt                                     */
    I2C0_ER_IRQn                 = 51,     /*!< I2C0 error interrupt                                     */
    I2C1_EV_IRQn                 = 52,     /*!< I2C1 event interrupt                                     */
    I2C1_ER_IRQn                 = 53,     /*!< I2C1 error interrupt                                     */
    SPI0_IRQn                    = 54,     /*!< SPI0 interrupt                                           */
    SPI1_IRQn                    = 55,     /*!< SPI1 interrupt                                           */
    USART0_IRQn                  = 56,     /*!< USART0 interrupt                                         */
    USART1_IRQn                  = 57,     /*!< USART1 interrupt                                         */
    USART2_IRQn                  = 58,     /*!< USART2 interrupt                                         */
    EXTI10_15_IRQn               = 59,     /*!< EXTI[15:10] interrupts                                   */
    RTC_ALARM_IRQn               = 60,     /*!< RTC alarm interrupt EXTI                                 */
    USBFS_WKUP_IRQn              = 61,     /*!< USBFS wakeup interrupt                                   */

    EXMC_IRQn                    = 67,     /*!< EXMC global interrupt                                    */

    TIMER4_IRQn                  = 69,     /*!< TIMER4 global interrupt                                  */
    SPI2_IRQn                    = 70,     /*!< SPI2 global interrupt                                    */
    UART3_IRQn                   = 71,     /*!< UART3 global interrupt                                   */
    UART4_IRQn                   = 72,     /*!< UART4 global interrupt                                   */
    TIMER5_IRQn                  = 73,     /*!< TIMER5 global interrupt                                  */
    TIMER6_IRQn                  = 74,     /*!< TIMER6 global interrupt                                  */
    DMA1_Channel0_IRQn           = 75,     /*!< DMA1 channel0 global interrupt                           */
    DMA1_Channel1_IRQn           = 76,     /*!< DMA1 channel1 global interrupt                           */
    DMA1_Channel2_IRQn           = 77,     /*!< DMA1 channel2 global interrupt                           */
    DMA1_Channel3_IRQn           = 78,     /*!< DMA1 channel3 global interrupt                           */
    DMA1_Channel4_IRQn           = 79,     /*!< DMA1 channel3 global interrupt                           */

    CAN1_TX_IRQn                 = 82,     /*!< CAN1 TX interrupt                                        */
    CAN1_RX0_IRQn                = 83,     /*!< CAN1 RX0 interrupt                                       */
    CAN1_RX1_IRQn                = 84,     /*!< CAN1 RX1 interrupt                                       */
    CAN1_EWMC_IRQn               = 85,     /*!< CAN1 EWMC interrupt                                      */
    USBFS_IRQn                   = 86,     /*!< USBFS global interrupt                                   */

    ECLIC_NUM_INTERRUPTS
} IRQn_Type;

/* includes */
#include "system_gd32vf103.h"
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
#define CAN_BASE              (APB1_BUS_BASE + 0x00006400U)  /*!< CAN base address                 */
#define BKP_BASE              (APB1_BUS_BASE + 0x00006C00U)  /*!< BKP base address                 */
#define PMU_BASE              (APB1_BUS_BASE + 0x00007000U)  /*!< PMU base address                 */
#define DAC_BASE              (APB1_BUS_BASE + 0x00007400U)  /*!< DAC base address                 */

/* advanced peripheral bus 2 memory map */
#define AFIO_BASE             (APB2_BUS_BASE + 0x00000000U)  /*!< AFIO base address                */
#define EXTI_BASE             (APB2_BUS_BASE + 0x00000400U)  /*!< EXTI base address                */
#define GPIO_BASE             (APB2_BUS_BASE + 0x00000800U)  /*!< GPIO base address                */
#define ADC_BASE              (APB2_BUS_BASE + 0x00002400U)  /*!< ADC base address                 */

/* advanced high performance bus 1 memory map */
#define DMA_BASE              (AHB1_BUS_BASE + 0x00008000U)  /*!< DMA base address                 */
#define RCU_BASE              (AHB1_BUS_BASE + 0x00009000U)  /*!< RCU base address                 */
#define FMC_BASE              (AHB1_BUS_BASE + 0x0000A000U)  /*!< FMC base address                 */
#define CRC_BASE              (AHB1_BUS_BASE + 0x0000B000U)  /*!< CRC base address                 */
#define USBFS_BASE            (AHB1_BUS_BASE + 0x0FFE8000U)  /*!< USBFS base address               */

/* define marco USE_STDPERIPH_DRIVER */
#if !defined  USE_STDPERIPH_DRIVER
#define USE_STDPERIPH_DRIVER
#endif
#ifdef USE_STDPERIPH_DRIVER
#include "gd32vf103_libopt.h"
#endif /* USE_STDPERIPH_DRIVER */

#ifdef __cplusplus
}
#endif
#endif
