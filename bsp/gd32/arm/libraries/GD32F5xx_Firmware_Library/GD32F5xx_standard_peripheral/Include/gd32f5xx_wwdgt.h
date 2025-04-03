/*!
    \file    gd32f5xx_wwdgt.h
    \brief   definitions for the WWDGT

    \version 2024-07-31, V1.1.0, firmware for GD32F5xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

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

#ifndef GD32F5XX_WWDGT_H
#define GD32F5XX_WWDGT_H

#include "gd32f5xx.h"

/* WWDGT definitions */
#define WWDGT                       WWDGT_BASE                                 /*!< WWDGT base address */

/* registers definitions */
#define WWDGT_CTL                   REG32((WWDGT) + 0x00U)                     /*!< WWDGT control register */
#define WWDGT_CFG                   REG32((WWDGT) + 0x04U)                     /*!< WWDGT configuration register */
#define WWDGT_STAT                  REG32((WWDGT) + 0x08U)                     /*!< WWDGT status register */

/* bits definitions */
/* WWDGT_CTL */
#define WWDGT_CTL_CNT               BITS(0,6)                                  /*!< WWDGT counter value */
#define WWDGT_CTL_WDGTEN            BIT(7)                                     /*!< WWDGT counter enable */

/* WWDGT_CFG */
#define WWDGT_CFG_WIN               BITS(0,6)                                  /*!< WWDGT counter window value */
#define WWDGT_CFG_PSC               (BITS(7,8) | BITS(10,12))                    /*!< WWDGT prescaler divider value */
#define WWDGT_CFG_EWIE              BIT(9)                                     /*!< early wakeup interrupt enable */

/* WWDGT_STAT */
#define WWDGT_STAT_EWIF             BIT(0)                                     /*!< early wakeup interrupt flag */

/* constants definitions */
#define CFG_PSCL(regval)            (BITS(7,8) & ((uint32_t)(regval) << 7))   /*!< write value to WWDGT_CFG_PSC bit field */
#define CFG_PSCH(regval)            (BITS(10,12) & ((uint32_t)(regval) << 10)) /*!< write value to WWDGT_CFG_PSC bit field */
#define WWDGT_CFG_PSC_DIV1          CFG_PSCL(0)                               /*!< the time base of WWDGT = (PCLK1/4096)/1 */
#define WWDGT_CFG_PSC_DIV2          CFG_PSCL(1)                               /*!< the time base of WWDGT = (PCLK1/4096)/2 */
#define WWDGT_CFG_PSC_DIV4          CFG_PSCL(2)                               /*!< the time base of WWDGT = (PCLK1/4096)/4 */
#define WWDGT_CFG_PSC_DIV8          CFG_PSCL(3)                               /*!< the time base of WWDGT = (PCLK1/4096)/8 */
#define WWDGT_CFG_PSC_DIV16         (CFG_PSCH(1)|CFG_PSCL(0))                 /*!< the time base of WWDGT = (PCLK1/4096)/16 */
#define WWDGT_CFG_PSC_DIV32         (CFG_PSCH(1)|CFG_PSCL(1))                 /*!< the time base of WWDGT = (PCLK1/4096)/32 */
#define WWDGT_CFG_PSC_DIV64         (CFG_PSCH(1)|CFG_PSCL(2))                 /*!< the time base of WWDGT = (PCLK1/4096)/64 */
#define WWDGT_CFG_PSC_DIV128        (CFG_PSCH(1)|CFG_PSCL(3))                 /*!< the time base of WWDGT = (PCLK1/4096)/128 */
#define WWDGT_CFG_PSC_DIV256        (CFG_PSCH(2)|CFG_PSCL(0))                 /*!< the time base of WWDGT = (PCLK1/4096)/256 */
#define WWDGT_CFG_PSC_DIV512        (CFG_PSCH(2)|CFG_PSCL(1))                 /*!< the time base of WWDGT = (PCLK1/4096)/512 */
#define WWDGT_CFG_PSC_DIV1024       (CFG_PSCH(2)|CFG_PSCL(2))                 /*!< the time base of WWDGT = (PCLK1/4096)/1024 */
#define WWDGT_CFG_PSC_DIV2048       (CFG_PSCH(2)|CFG_PSCL(3))                 /*!< the time base of WWDGT = (PCLK1/4096)/2048 */
#define WWDGT_CFG_PSC_DIV4096       (CFG_PSCH(3)|CFG_PSCL(0))                 /*!< the time base of WWDGT = (PCLK1/4096)/4096 */
#define WWDGT_CFG_PSC_DIV8192       (CFG_PSCH(3)|CFG_PSCL(1))                 /*!< the time base of WWDGT = (PCLK1/4096)/8192 */
#define WWDGT_CFG_PSC_DIV16384      (CFG_PSCH(3)|CFG_PSCL(2))                 /*!< the time base of WWDGT = (PCLK1/4096)/16384 */
#define WWDGT_CFG_PSC_DIV32768      (CFG_PSCH(3)|CFG_PSCL(3))                 /*!< the time base of WWDGT = (PCLK1/4096)/32768 */
#define WWDGT_CFG_PSC_DIV65536      (CFG_PSCH(4)|CFG_PSCL(0))                 /*!< the time base of WWDGT = (PCLK1/4096)/65536 */
#define WWDGT_CFG_PSC_DIV131072     (CFG_PSCH(4)|CFG_PSCL(1))                 /*!< the time base of WWDGT = (PCLK1/4096)/131072 */
#define WWDGT_CFG_PSC_DIV262144     (CFG_PSCH(4)|CFG_PSCL(2))                 /*!< the time base of WWDGT = (PCLK1/4096)/262144 */

/* write value to WWDGT_CTL_CNT bit field */
#define CTL_CNT(regval)             (BITS(0,6) & ((uint32_t)(regval) << 0))
/* write value to WWDGT_CFG_WIN bit field */
#define CFG_WIN(regval)             (BITS(0,6) & ((uint32_t)(regval) << 0))

/* function declarations */
/* reset the window watchdog timer configuration */
void wwdgt_deinit(void);
/* start the window watchdog timer counter */
void wwdgt_enable(void);

/* configure the window watchdog timer counter value */
void wwdgt_counter_update(uint16_t counter_value);
/* configure counter value, window value, and prescaler divider value */
void wwdgt_config(uint16_t counter, uint16_t window, uint32_t prescaler);

/* check early wakeup interrupt state of WWDGT */
FlagStatus wwdgt_flag_get(void);
/* clear early wakeup interrupt state of WWDGT */
void wwdgt_flag_clear(void);
/* enable early wakeup interrupt of WWDGT */
void wwdgt_interrupt_enable(void);

#endif /* GD32F5XX_WWDGT_H */
