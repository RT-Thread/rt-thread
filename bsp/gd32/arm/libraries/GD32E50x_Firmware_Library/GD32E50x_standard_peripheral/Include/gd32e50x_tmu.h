/*!
    \file    gd32e50x_tmu.h
    \brief   definitions for the TMU

    \version 2023-12-31, V1.4.0, firmware for GD32E50x
*/

/*
    Copyright (c) 2023, GigaDevice Semiconductor Inc.

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

#ifndef GD32E50X_TMU_H
#define GD32E50X_TMU_H

#include "gd32e50x.h"

#if defined(GD32E50X_CL) || defined(GD32E508)

/* TMU definitions */
#define TMU                             TMU_BASE

/* registers definitions */
#define TMU_IDATA0                      REG32((TMU) + 0x00000000U)        /*!< input data0 register */
#define TMU_IDATA1                      REG32((TMU) + 0x00000004U)        /*!< input data1 register */
#define TMU_CTL                         REG32((TMU) + 0x00000008U)        /*!< control register */
#define TMU_DATA0                       REG32((TMU) + 0x0000000CU)        /*!< data0 register */
#define TMU_DATA1                       REG32((TMU) + 0x00000010U)        /*!< data1 register */
#define TMU_STAT                        REG32((TMU) + 0x00000014U)        /*!< status register */

/* bits definitions */
/* TMU_IDATA0 */
#define TMU_IDATA0_IDATA0               BITS(0,31)                /*!< the value of input data0 register */

/* TMU_IDATA1 */
#define TMU_IDATA1_IDATA1               BITS(0,31)                /*!< the value of input data1 register */

/* TMU_CTL */
#define TMU_CTL_TMUEN                   BIT(0)                    /*!< start TMU calculation */
#define TMU_CTL_MODE                    BITS(1,4)                 /*!< the mode of TMU */
#define TMU_CTL_CFIE                    BIT(5)                    /*!< enable calculation finishes interrupt */
#define TMU_CTL_CFIF                    BIT(6)                    /*!< the flag of calculation finishes interrupt */

/* TMU_DATA0 */
#define TMU_DATA0_DATA0                 BITS(0,31)                /*!< the value of data0 register */

/* TMU_DATA0 */
#define TMU_DATA1_DATA1                 BITS(0,31)                /*!< the value of data1 register */

/* TMU_STAT */
#define TMU_STAT_OVRF                   BIT(0)                    /*!< the status of overflow */
#define TMU_STAT_UDRF                   BIT(1)                    /*!< the status of underflow */

/* constants definitions */
/* TMU mode definitions */
#define TMU_MODE(regval)                (BITS(1,4) & ((uint32_t)(regval) << 1))
#define TMU_MODE0                        TMU_MODE(0)              /*!< the mode0 of TMU */
#define TMU_MODE1                        TMU_MODE(1)              /*!< the mode1 of TMU */
#define TMU_MODE2                        TMU_MODE(2)              /*!< the mode2 of TMU */
#define TMU_MODE3                        TMU_MODE(3)              /*!< the mode3 of TMU */
#define TMU_MODE4                        TMU_MODE(4)              /*!< the mode4 of TMU */
#define TMU_MODE5                        TMU_MODE(5)              /*!< the mode5 of TMU */
#define TMU_MODE6                        TMU_MODE(6)              /*!< the mode6 of TMU */
#define TMU_MODE7                        TMU_MODE(7)              /*!< the mode7 of TMU */
#define TMU_MODE8                        TMU_MODE(8)              /*!< the mode8 of TMU */

/* TMU interrupt flag definitions */
#define TMU_INT_FLAG_CFIF                TMU_CTL_CFIF             /*!< the interrupt flag of calculation finished */

/* TMU flag definitions */
#define TMU_FLAG_OVRF                    TMU_STAT_OVRF            /*!< the flag of TMU overflow */
#define TMU_FLAG_UDRF                    TMU_STAT_UDRF            /*!< the flag of TMU underflow */

/* function declarations */
/* TMU deinitialization and initialization functions */
/* reset the TMU */
void tmu_deinit(void);
/* enable the TMU */
void tmu_enable(void);

/* configure the TMU calculation */
/* configure the TMU mode */
void tmu_mode_set(uint32_t modex);
/* write the data to TMU input data0 regisetr */
void tmu_idata0_write(uint32_t idata0);
/* write the data to TMU input data1 regisetr */
void tmu_idata1_write(uint32_t idata1);
/* read the data from TMU data0 regisetr */
uint32_t tmu_data0_read(void);
/* read the data from TMU data1 regisetr */
uint32_t tmu_data1_read(void);

/* flag and interrupt functions */
/* enable TTMU interrupt */
void tmu_interrupt_enable(void);
/* disable TTMU interrupt */
void tmu_interrupt_disable(void);
/* check teh TMU status flag */
FlagStatus tmu_flag_get(uint32_t flag);
/* check teh TMU interrupt flag */
FlagStatus tmu_interrupt_flag_get(uint32_t int_flag);

#endif /* GD32E50x_CL and GD32E508 */

#endif /* GD32E50X_TMU_H */
