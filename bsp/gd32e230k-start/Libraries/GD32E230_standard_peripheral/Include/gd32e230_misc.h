/*!
    \file  gd32e230_misc.h
    \brief definitions for the MISC
    
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

#ifndef GD32E230_MISC_H
#define GD32E230_MISC_H

#include "gd32e230.h"

/* constants definitions */
/* set the RAM and FLASH base address */
#define NVIC_VECTTAB_RAM            ((uint32_t)0x20000000)                      /*!< RAM base address */
#define NVIC_VECTTAB_FLASH          ((uint32_t)0x08000000)                      /*!< Flash base address */

/* set the NVIC vector table offset mask */
#define NVIC_VECTTAB_OFFSET_MASK    ((uint32_t)0x1FFFFF80)                      /*!< NVIC vector table offset mask */

/* the register key mask, if you want to do the write operation, you should write 0x5FA to VECTKEY bits */
#define NVIC_AIRCR_VECTKEY_MASK     ((uint32_t)0x05FA0000)                      /*!< NVIC VECTKEY mask */

/* choose the method to enter or exit the lowpower mode */
#define SCB_SCR_SLEEPONEXIT         ((uint8_t)0x02)                             /*!< choose the the system whether enter low power mode by exiting from ISR */
#define SCB_SCR_SLEEPDEEP           ((uint8_t)0x04)                             /*!< choose the the system enter the DEEPSLEEP mode or SLEEP mode */
#define SCB_SCR_SEVONPEND           ((uint8_t)0x10)                             /*!< choose the interrupt source that can wake up the lowpower mode */

#define SCB_LPM_SLEEP_EXIT_ISR      SCB_SCR_SLEEPONEXIT                         /*!< low power mode by exiting from ISR */
#define SCB_LPM_DEEPSLEEP           SCB_SCR_SLEEPDEEP                           /*!< DEEPSLEEP mode or SLEEP mode */
#define SCB_LPM_WAKE_BY_ALL_INT     SCB_SCR_SEVONPEND                           /*!< wakeup by all interrupt */

/* choose the systick clock source */
#define SYSTICK_CLKSOURCE_HCLK_DIV8 ((uint32_t)0xFFFFFFFBU)                     /*!< systick clock source is from HCLK/8 */
#define SYSTICK_CLKSOURCE_HCLK      ((uint32_t)0x00000004U)                     /*!< systick clock source is from HCLK */

/* function declarations */

/* enable NVIC request */
void nvic_irq_enable(uint8_t nvic_irq, uint8_t nvic_irq_priority);
/* disable NVIC request */
void nvic_irq_disable(uint8_t nvic_irq);
/* initiates a system reset request to reset the MCU */
void nvic_system_reset(void);

/* set the NVIC vector table base address */
void nvic_vector_table_set(uint32_t nvic_vict_tab, uint32_t offset);

/* set the state of the low power mode */
void system_lowpower_set(uint8_t lowpower_mode);
/* reset the state of the low power mode */
void system_lowpower_reset(uint8_t lowpower_mode);

/* set the systick clock source */
void systick_clksource_set(uint32_t systick_clksource);

#endif /* GD32E230_MISC_H */
