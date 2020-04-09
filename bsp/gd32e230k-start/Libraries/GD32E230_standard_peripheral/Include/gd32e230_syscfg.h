/*!
    \file  GD32e230_syscfg.h
    \brief definitions for the SYSCFG

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

#ifndef GD32E230_SYSCFG_H
#define GD32E230_SYSCFG_H

#include "gd32e230.h"

/* SYSCFG definitions */
#define SYSCFG                              SYSCFG_BASE

/* registers definitions */
#define SYSCFG_CFG0                         REG32(SYSCFG + 0x00U)               /*!< system configuration register 0 */
#define SYSCFG_EXTISS0                      REG32(SYSCFG + 0x08U)               /*!< EXTI sources selection register 0 */
#define SYSCFG_EXTISS1                      REG32(SYSCFG + 0x0CU)               /*!< EXTI sources selection register 1 */
#define SYSCFG_EXTISS2                      REG32(SYSCFG + 0x10U)               /*!< EXTI sources selection register 2 */
#define SYSCFG_EXTISS3                      REG32(SYSCFG + 0x14U)               /*!< EXTI sources selection register 3 */
#define SYSCFG_CFG2                         REG32(SYSCFG + 0x18U)               /*!< system configuration register 2 */
#define SYSCFG_CPU_IRQ_LAT                  REG32(SYSCFG + 0x100U)              /*!< IRQ Latency register */

/* SYSCFG_CFG0 bits definitions */
#define SYSCFG_CFG0_BOOT_MODE               BITS(0,1)                           /*!< SYSCFG memory remap config */
#define SYSCFG_CFG0_PA11_PA12_RMP           BIT(4)                              /*!< PA11 and PA12 remapping bit for small packages (28 and 20 pins) */
#define SYSCFG_CFG0_ADC_DMA_RMP             BIT(8)                              /*!< ADC DMA remap config */
#define SYSCFG_CFG0_USART0_TX_DMA_RMP       BIT(9)                              /*!< USART0 Tx DMA remap config */
#define SYSCFG_CFG0_USART0_RX_DMA_RMP       BIT(10)                             /*!< USART0 Rx DMA remap config */
#define SYSCFG_CFG0_TIMER15_DMA_RMP         BIT(11)                             /*!< TIMER 15 DMA remap config */
#define SYSCFG_CFG0_TIMER16_DMA_RMP         BIT(12)                             /*!< TIMER 16 DMA remap config */
#define SYSCFG_CFG0_PB9_HCCE                BIT(19)                             /*!< PB9 pin high current capability enable */

/* SYSCFG_EXTISS0 bits definitions */
#define SYSCFG_EXTISS0_EXTI0_SS             BITS(0,3)                           /*!< EXTI 0 configuration */
#define SYSCFG_EXTISS0_EXTI1_SS             BITS(4,7)                           /*!< EXTI 1 configuration */
#define SYSCFG_EXTISS0_EXTI2_SS             BITS(8,11)                          /*!< EXTI 2 configuration */
#define SYSCFG_EXTISS0_EXTI3_SS             BITS(12,15)                         /*!< EXTI 3 configuration */

/* SYSCFG_EXTISS1 bits definitions */
#define SYSCFG_EXTISS1_EXTI4_SS             BITS(0,3)                           /*!< EXTI 4 configuration */
#define SYSCFG_EXTISS1_EXTI5_SS             BITS(4,7)                           /*!< EXTI 5 configuration */
#define SYSCFG_EXTISS1_EXTI6_SS             BITS(8,11)                          /*!< EXTI 6 configuration */
#define SYSCFG_EXTISS1_EXTI7_SS             BITS(12,15)                         /*!< EXTI 7 configuration */

/* SYSCFG_EXTISS2 bits definitions */
#define SYSCFG_EXTISS2_EXTI8_SS             BITS(0,3)                           /*!< EXTI 8 configuration */
#define SYSCFG_EXTISS2_EXTI9_SS             BITS(4,7)                           /*!< EXTI 9 configuration */
#define SYSCFG_EXTISS2_EXTI10_SS            BITS(8,11)                          /*!< EXTI 10 configuration */
#define SYSCFG_EXTISS2_EXTI11_SS            BITS(12,15)                         /*!< EXTI 11 configuration */

/* SYSCFG_EXTISS3 bits definitions */
#define SYSCFG_EXTISS3_EXTI12_SS            BITS(0,3)                           /*!< EXTI 12 configuration */
#define SYSCFG_EXTISS3_EXTI13_SS            BITS(4,7)                           /*!< EXTI 13 configuration */
#define SYSCFG_EXTISS3_EXTI14_SS            BITS(8,11)                          /*!< EXTI 14 configuration */
#define SYSCFG_EXTISS3_EXTI15_SS            BITS(12,15)                         /*!< EXTI 15 configuration */

/* SYSCFG_CFG2 bits definitions */
#define SYSCFG_CFG2_LOCKUP_LOCK             BIT(0)                              /*!< enable and lock the LOCKUP (Hardfault) output of Cortex-M23 with break input of TIMER0/14/15/16 */
#define SYSCFG_CFG2_SRAM_PARITY_ERROR_LOCK  BIT(1)                              /*!< enable and lock the SRAM_PARITY error signal with break input of TIMER0/14/15/16 */
#define SYSCFG_CFG2_LVD_LOCK                BIT(2)                              /*!< enable and lock the LVD connection with TIMER0 break input and also the LVD_EN and LVDSEL[2:0] bits of the power control interface */
#define SYSCFG_CFG2_SRAM_PCEF               BIT(8)                              /*!< SRAM parity check error flag */

/* SYSCFG_CPU_IRQ_LAT bits definitions */
#define SYSCFG_CPU_IRQ_LAT_IRQ_LATENCY      BITS(0,7)                           /*!< IRQ_LATENCY specifies the minimum number of cycles between an interrupt */

/* constants definitions */
/* DMA remap definitions */
#define SYSCFG_PA11_REMAP_PA12              SYSCFG_CFG0_PA11_PA12_RMP           /*!< PA11 PA12 remap */
#define SYSCFG_DMA_REMAP_ADC                SYSCFG_CFG0_ADC_DMA_RMP             /*!< ADC DMA remap */
#define SYSCFG_DMA_REMAP_USART0TX           SYSCFG_CFG0_USART0_TX_DMA_RMP       /*!< USART0_TX DMA remap */
#define SYSCFG_DMA_REMAP_USART0RX           SYSCFG_CFG0_USART0_RX_DMA_RMP       /*!< USART0_RX DMA remap */
#define SYSCFG_DMA_REMAP_TIMER15            SYSCFG_CFG0_TIMER15_DMA_RMP         /*!< TIMER15 DMA remap */
#define SYSCFG_DMA_REMAP_TIMER16            SYSCFG_CFG0_TIMER16_DMA_RMP         /*!< TIMER16 DMA remap */

/* high current definitions */
#define SYSCFG_HIGH_CURRENT_ENABLE          SYSCFG_CFG0_PB9_HCCE                /*!< high current enable */
#define SYSCFG_HIGH_CURRENT_DISABLE         (~SYSCFG_CFG0_PB9_HCCE)             /*!< high current disable */

/* EXTI source select definition */
#define EXTISS0                             ((uint8_t)0x00U)                    /*!< EXTI source select register 0 */
#define EXTISS1                             ((uint8_t)0x01U)                    /*!< EXTI source select register 1 */
#define EXTISS2                             ((uint8_t)0x02U)                    /*!< EXTI source select register 2 */
#define EXTISS3                             ((uint8_t)0x03U)                    /*!< EXTI source select register 3 */

/* EXTI source select mask bits definition */
#define EXTI_SS_MASK                        BITS(0,3)                           /*!< EXTI source select mask */

/* EXTI source select jumping step definition */
#define EXTI_SS_JSTEP                       ((uint8_t)(0x04U))                  /*!< EXTI source select jumping step */

/* EXTI source select moving step definition */
#define EXTI_SS_MSTEP(pin)                  (EXTI_SS_JSTEP * ((pin) % EXTI_SS_JSTEP))   /*!< EXTI source select moving step */

/* EXTI source port definitions */
#define EXTI_SOURCE_GPIOA                   ((uint8_t)0x00U)                    /*!< EXTI GPIOA configuration */
#define EXTI_SOURCE_GPIOB                   ((uint8_t)0x01U)                    /*!< EXTI GPIOB configuration */
#define EXTI_SOURCE_GPIOC                   ((uint8_t)0x02U)                    /*!< EXTI GPIOC configuration */
#define EXTI_SOURCE_GPIOF                   ((uint8_t)0x05U)                    /*!< EXTI GPIOF configuration */

/* EXTI source pin definitions */
#define EXTI_SOURCE_PIN0                    ((uint8_t)0x00U)                    /*!< EXTI GPIO pin0 configuration */
#define EXTI_SOURCE_PIN1                    ((uint8_t)0x01U)                    /*!< EXTI GPIO pin1 configuration */
#define EXTI_SOURCE_PIN2                    ((uint8_t)0x02U)                    /*!< EXTI GPIO pin2 configuration */
#define EXTI_SOURCE_PIN3                    ((uint8_t)0x03U)                    /*!< EXTI GPIO pin3 configuration */
#define EXTI_SOURCE_PIN4                    ((uint8_t)0x04U)                    /*!< EXTI GPIO pin4 configuration */
#define EXTI_SOURCE_PIN5                    ((uint8_t)0x05U)                    /*!< EXTI GPIO pin5 configuration */
#define EXTI_SOURCE_PIN6                    ((uint8_t)0x06U)                    /*!< EXTI GPIO pin6 configuration */
#define EXTI_SOURCE_PIN7                    ((uint8_t)0x07U)                    /*!< EXTI GPIO pin7 configuration */
#define EXTI_SOURCE_PIN8                    ((uint8_t)0x08U)                    /*!< EXTI GPIO pin8 configuration */
#define EXTI_SOURCE_PIN9                    ((uint8_t)0x09U)                    /*!< EXTI GPIO pin9 configuration */
#define EXTI_SOURCE_PIN10                   ((uint8_t)0x0AU)                    /*!< EXTI GPIO pin10 configuration */
#define EXTI_SOURCE_PIN11                   ((uint8_t)0x0BU)                    /*!< EXTI GPIO pin11 configuration */
#define EXTI_SOURCE_PIN12                   ((uint8_t)0x0CU)                    /*!< EXTI GPIO pin12 configuration */
#define EXTI_SOURCE_PIN13                   ((uint8_t)0x0DU)                    /*!< EXTI GPIO pin13 configuration */
#define EXTI_SOURCE_PIN14                   ((uint8_t)0x0EU)                    /*!< EXTI GPIO pin14 configuration */
#define EXTI_SOURCE_PIN15                   ((uint8_t)0x0FU)                    /*!< EXTI GPIO pin15 configuration */

/* lock definitions */
#define SYSCFG_LOCK_LOCKUP                  SYSCFG_CFG2_LOCKUP_LOCK             /*!< LOCKUP output lock */
#define SYSCFG_LOCK_SRAM_PARITY_ERROR       SYSCFG_CFG2_SRAM_PARITY_ERROR_LOCK  /*!< SRAM parity error lock */
#define SYSCFG_LOCK_LVD                     SYSCFG_CFG2_LVD_LOCK                /*!< LVD lock */

/* SRAM parity check error flag definitions */
#define SYSCFG_SRAM_PCEF                    SYSCFG_CFG2_SRAM_PCEF               /*!< SRAM parity check error flag */

/* SYSCFG_CPU_IRQ_LAT register IRQ_LATENCY value */
#define IRQ_LATENCY(regval)                (BITS(0,7) & ((uint32_t)(regval) << 0U))     /*!< write value to IRQ_LATENCY bits field */

/* function declarations */
/* deinit syscfg module */
void syscfg_deinit(void);

/* enable the DMA channels remapping */
void syscfg_dma_remap_enable(uint32_t syscfg_dma_remap);
/* disable the DMA channels remapping */
void syscfg_dma_remap_disable(uint32_t syscfg_dma_remap);

/* enable PB9 high current capability */
void syscfg_high_current_enable(void);
/* disable PB9 high current capability */
void syscfg_high_current_disable(void);

/* configure the GPIO pin as EXTI Line */
void syscfg_exti_line_config(uint8_t exti_port, uint8_t exti_pin);
/* connect TIMER0/14/15/16 break input to the selected parameter */
void syscfg_lock_config(uint32_t syscfg_lock);

/* set the IRQ_LATENCY value */
void irq_latency_set(uint8_t irq_latency);

/* check if the specified flag in SYSCFG_CFG2 is set or not */
FlagStatus syscfg_flag_get(uint32_t syscfg_flag);
/* clear the flag in SYSCFG_CFG2 by writing 1 */
void syscfg_flag_clear(uint32_t syscfg_flag);

#endif /* GD32E230_SYSCFG_H */
