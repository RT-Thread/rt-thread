/*!
    \file    gd32h7xx_lpdts.h
    \brief   definitions for the LPDTS

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
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

#ifndef GD32H7XX_LPDTS_H
#define GD32H7XX_LPDTS_H

#include "gd32h7xx.h"

/* LPDTS definitions */
#define LPDTS                       LPDTS_BASE

/* registers definitions */
#define LPDTS_CFG                   REG32(LPDTS + 0x00000000U)      /*!< LPDTS configuration register */
#define LPDTS_SDATA                 REG32(LPDTS + 0x00000008U)      /*!< LPDTS sensor T0 data register */
#define LPDTS_RDATA                 REG32(LPDTS + 0x00000010U)      /*!< LPDTS ramp data register */
#define LPDTS_IT                    REG32(LPDTS + 0x00000014U)      /*!< LPDTS interrupt threshold register */
#define LPDTS_DATA                  REG32(LPDTS + 0x0000001CU)      /*!< LPDTS temperature data register */
#define LPDTS_STAT                  REG32(LPDTS + 0x00000020U)      /*!< LPDTS temperature sensor status register */
#define LPDTS_INTEN                 REG32(LPDTS + 0x00000024U)      /*!< LPDTS interrupt enable register */
#define LPDTS_INTC                  REG32(LPDTS + 0x00000028U)      /*!< LPDTS interrupt clear flag register */
#define LPDTS_OP                    REG32(LPDTS + 0x0000002CU)      /*!< LPDTS option register */

/* bits definitions */
/* LPDTS_CFG */
#define LPDTS_CFG_TSEN              BIT(0)                          /*!< temperature sensor enable */
#define LPDTS_CFG_TRGS              BIT(4)                          /*!< software trigger */
#define LPDTS_CFG_ITSEL             BITS(8,11)                      /*!< input trigger selection */
#define LPDTS_CFG_SPT               BITS(16,19)                     /*!< sampling time */
#define LPDTS_CFG_REFSEL            BIT(20)                         /*!< reference clock selection */

/* LPDTS_SDATA */
#define LPDTS_SDATA_FREQ            BITS(0,15)                      /*!< frequency value at temperature T0 */
#define LPDTS_SDATA_VAL             BITS(16,17)                     /*!< temperature T0 */

/* LPDTS_RDATA */
#define LPDTS_RDATA_RCVAL           BITS(0,15)                      /*!< ramp coefficient */

/* LPDTS_IT */
#define LPDTS_IT_INTLT              BITS(0,15)                      /*!< interrupt low threshold */
#define LPDTS_IT_INTHT              BITS(16,31)                     /*!< interrupt high threshold */

/* LPDTS_DATA */
#define LPDTS_DATA_COVAL            BITS(0,15)                      /*!< value of the counter output */

/* LPDTS_STAT */
#define LPDTS_STAT_EMIF             BIT(0)                          /*!< end of measurement interrupt flag */
#define LPDTS_STAT_LTIF             BIT(1)                          /*!< low threshold interrupt flag */
#define LPDTS_STAT_HTIF             BIT(2)                          /*!< high threshold interrupt flag */
#define LPDTS_STAT_EMAIF            BIT(4)                          /*!< end of measurement asynchronous interrupt flag */
#define LPDTS_STAT_LTAIF            BIT(5)                          /*!< low threshold asynchronous interrupt flag */
#define LPDTS_STAT_HTAIF            BIT(6)                          /*!< high threshold asynchronous interrupt flag */
#define LPDTS_STAT_TSRF             BIT(15)                         /*!< temperature sensor ready flag */

/* LPDTS_INTEN */
#define LPDTS_INTEN_EMIE            BIT(0)                          /*!< end of measurement interrupt enable */
#define LPDTS_INTEN_LTIE            BIT(1)                          /*!< low threshold interrupt enable */
#define LPDTS_INTEN_HTIE            BIT(2)                          /*!< high threshold interrupt enable */
#define LPDTS_INTEN_EMAIE           BIT(4)                          /*!< end of measurement asynchronous interrupt enable */
#define LPDTS_INTEN_LTAIE           BIT(5)                          /*!< low threshold asynchronous interrupt enable */
#define LPDTS_INTEN_HTAIE           BIT(6)                          /*!< high threshold asynchronous interrupt enable */

/* LPDTS_INTC */
#define LPDTS_INTC_EMIC             BIT(0)                          /*!< end of measurement interrupt clear */
#define LPDTS_INTC_LTIC             BIT(1)                          /*!< low threshold interrupt clear */
#define LPDTS_INTC_HTIC             BIT(2)                          /*!< high threshold interrupt clear */
#define LPDTS_INTC_EMAIC            BIT(4)                          /*!< end of measure asynchronous interrupt clear */
#define LPDTS_INTC_LTAIC            BIT(5)                          /*!< low threshold asynchronous interrupt clear */
#define LPDTS_INTC_HTAIC            BIT(6)                          /*!< high threshold asynchronous interrupt clear */

/* LPDTS_OP */
#define LPDTS_OP_OP                 BITS(0,31)                      /*!< general purpose option */

/* constants definitions */
/* parameter struct definitions */
typedef struct {
    uint32_t ref_clock;                                             /*!< reference clock selection */
    uint32_t trigger_input;                                         /*!< input trigger selection */
    uint32_t sampling_time;                                         /*!< sampling time */
} lpdts_parameter_struct;

/* reference clock definitions */
#define REF_PCLK                    ((uint32_t)0x00000000U)         /*!< high speed reference clock (PCLK) */
#define REF_LXTAL                   LPDTS_CFG_REFSEL                /*!< low speed reference clock (LXTAL) */

/* input trigger selection definitions */
#define TRIGGER_SEL(regval)         (BITS(8,11) & ((uint32_t)(regval) << 8))
#define NO_HARDWARE_TRIGGER         TRIGGER_SEL(0)                  /*!< no hardware trigger signal */
#define LPDTS_TRG                   TRIGGER_SEL(4)                  /*!< select LPDTS_TRG as trigger signal */

/* sampling time definitions */
#define SMP_TIME(regval)            (BITS(16,19) & ((uint32_t)(regval) << 16))
#define SPT_CLOCK_1                 SMP_TIME(1)                     /*!< 1 LXTAL or FM(T) clocks */
#define SPT_CLOCK_2                 SMP_TIME(2)                     /*!< 2 LXTAL or FM(T) clocks */
#define SPT_CLOCK_3                 SMP_TIME(3)                     /*!< 3 LXTAL or FM(T) clocks */
#define SPT_CLOCK_4                 SMP_TIME(4)                     /*!< 4 LXTAL or FM(T) clocks */
#define SPT_CLOCK_5                 SMP_TIME(5)                     /*!< 5 LXTAL or FM(T) clocks */
#define SPT_CLOCK_6                 SMP_TIME(6)                     /*!< 6 LXTAL or FM(T) clocks */
#define SPT_CLOCK_7                 SMP_TIME(7)                     /*!< 7 LXTAL or FM(T) clocks */
#define SPT_CLOCK_8                 SMP_TIME(8)                     /*!< 8 LXTAL or FM(T) clocks */
#define SPT_CLOCK_9                 SMP_TIME(9)                     /*!< 9 LXTAL or FM(T) clocks */
#define SPT_CLOCK_10                SMP_TIME(10)                    /*!< 10 LXTAL or FM(T) clocks */
#define SPT_CLOCK_11                SMP_TIME(11)                    /*!< 11 LXTAL or FM(T) clocks */
#define SPT_CLOCK_12                SMP_TIME(12)                    /*!< 12 LXTAL or FM(T) clocks */
#define SPT_CLOCK_13                SMP_TIME(13)                    /*!< 13 LXTAL or FM(T) clocks */
#define SPT_CLOCK_14                SMP_TIME(14)                    /*!< 14 LXTAL or FM(T) clocks */
#define SPT_CLOCK_15                SMP_TIME(15)                    /*!< 15 LXTAL or FM(T) clocks */

/* LPDTS flags */
#define LPDTS_FLAG_TSR              LPDTS_STAT_TSRF                 /*!< temperature sensor ready flag */
#define LPDTS_INT_FLAG_EM           LPDTS_STAT_EMIF                 /*!< end of measurement interrupt flag */
#define LPDTS_INT_FLAG_LT           LPDTS_STAT_LTIF                 /*!< low threshold interrupt flag */
#define LPDTS_INT_FLAG_HT           LPDTS_STAT_HTIF                 /*!< high threshold interrupt flag */
#define LPDTS_INT_FLAG_EMA          LPDTS_STAT_EMAIF                /*!< end of measurement asynchronous interrupt flag */
#define LPDTS_INT_FLAG_LTA          LPDTS_STAT_LTAIF                /*!< low threshold asynchronous interrupt flag */
#define LPDTS_INT_FLAG_HTA          LPDTS_STAT_HTAIF                /*!< high threshold asynchronous interrupt flag */

/* LPDTS interrupt enable */
#define LPDTS_INT_EM                LPDTS_INTEN_EMIE                /*!< end of measurement interrupt enable */
#define LPDTS_INT_LT                LPDTS_INTEN_LTIE                /*!< low threshold interrupt enable */
#define LPDTS_INT_HT                LPDTS_INTEN_HTIE                /*!< high threshold interrupt enable */
#define LPDTS_INT_EMA               LPDTS_INTEN_EMAIE               /*!< end of measurement asynchronous interrupt enable */
#define LPDTS_INT_LTA               LPDTS_INTEN_LTAIE               /*!< low threshold asynchronous interrupt enable */
#define LPDTS_INT_HTA               LPDTS_INTEN_HTAIE               /*!< high threshold asynchronous interrupt enable */

/* function declarations */
/* initialization functions */
/* reset the LPDTS registers */
void lpdts_deinit(void);
/* initialize the parameters of LPDTS struct with the default values */
void lpdts_struct_para_init(lpdts_parameter_struct *init_struct);
/* initialize the LPDTS */
void lpdts_init(lpdts_parameter_struct *init_struct);

/* configuration functions */
/* enable LPDTS temperature sensor */
void lpdts_enable(void);
/* disable LPDTS temperature sensor */
void lpdts_disable(void);
/* enable LPDTS software trigger */
void lpdts_soft_trigger_enable(void);
/* disable LPDTS software trigger */
void lpdts_soft_trigger_disable(void);
/* configure LPDTS high threshold value */
void lpdts_high_threshold_set(uint16_t value);
/* configure LPDTS low threshold value */
void lpdts_low_threshold_set(uint16_t value);
/* configure LPDTS reference clock selection */
void lpdts_ref_clock_source_config(uint32_t source);
/* get temperature from LPDTS */
int32_t lpdts_temperature_get(void);

/* flag and interrupt functions */
/* get LPDTS flag */
FlagStatus lpdts_flag_get(uint32_t flag);
/* enable LPDTS interrupt */
void lpdts_interrupt_enable(uint32_t interrupt);
/* disable LPDTS interrupt */
void lpdts_interrupt_disable(uint32_t interrupt);
/* get LPDTS interrupt flag */
FlagStatus lpdts_interrupt_flag_get(uint32_t flag);
/* clear the LPDTS interrupt flag */
void lpdts_interrupt_flag_clear(uint32_t flag);

#endif /* GD32H7XX_LPDTS_H */
