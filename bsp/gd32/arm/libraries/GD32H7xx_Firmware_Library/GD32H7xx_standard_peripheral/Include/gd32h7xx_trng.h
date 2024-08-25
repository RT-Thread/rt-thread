/*!
    \file    gd32h7xx_trng.h
    \brief   definitions for the TRNG

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

#ifndef GD32H7XX_TRNG_H
#define GD32H7XX_TRNG_H

#include "gd32h7xx.h"

/* TRNG definitions */
#define TRNG                        TRNG_BASE

/* registers definitions */
#define TRNG_CTL                    REG32(TRNG + 0x00000000U)  /*!< control register */
#define TRNG_STAT                   REG32(TRNG + 0x00000004U)  /*!< status register */
#define TRNG_DATA                   REG32(TRNG + 0x00000008U)  /*!< data register */
#define TRNG_HTCFG                  REG32(TRNG + 0x00000010U)  /*!< health tests configure register */

/* bits definitions */
/* TRNG_CTL */
#define TRNG_CTL_TRNGEN             BIT(2)                     /*!< TRNG enable bit */
#define TRNG_CTL_IE                 BIT(3)                     /*!< interrupt enable bit */
#define TRNG_CTL_MODSEL             BIT(4)                     /*!< TRNG working mode config bit */
#define TRNG_CTL_CED                BIT(5)                     /*!< clock error detect enable bit */
#define TRNG_CTL_RTEN               BIT(7)                     /*!< replace test enable */
#define TRNG_CTL_INIT               BIT(8)                     /*!< HASH algorithm init */
#define TRNG_CTL_PPEN               BIT(9)                     /*!< TRNG post-porcessing module enable */
#define TRNG_CTL_CONDEN             BIT(10)                    /*!< TRNG conditioning module enable */
#define TRNG_CTL_ALGO               BITS(12,13)                /*!< TRNG conditioning module hash algo select */
#define TRNG_CTL_OUTMOD             BIT(14)                    /*!< TRNG conditioning output width config bit */
#define TRNG_CTL_INMOD              BIT(15)                    /*!< TRNG conditioning input width config bit */
#define TRNG_CTL_CLKDIV             BITS(16,19)                /*!< TRNG clock divider */
#define TRNG_CTL_NR                 BITS(24,25)                /*!< TRNG analog power mode bits */
#define TRNG_CTL_CONDRST            BIT(30)                    /*!< reset TRNG conditioning logic */
#define TRNG_CTL_LK                 BIT(31)                    /*!< TRNG_CTL register lock bit */

/* TRNG_STAT */
#define TRNG_STAT_DRDY              BIT(0)                     /*!< random data ready status bit */
#define TRNG_STAT_CECS              BIT(1)                     /*!< clock error current status */
#define TRNG_STAT_SECS              BIT(2)                     /*!< seed error current status */
#define TRNG_STAT_ERRSTA            BIT(3)                     /*!< NIST mode error status */
#define TRNG_STAT_CEIF              BIT(5)                     /*!< clock error interrupt flag */
#define TRNG_STAT_SEIF              BIT(6)                     /*!< seed error interrupt flag */

/* TRNG_DATA */
#define TRNG_DATA_TRNDATA           BITS(0,31)                 /*!< 32-Bit Random data */

/* TRNG_HTCFG */
#define TRNG_HTCFG_RCTTH            BITS(0,6)                  /*!< repetition (00/11) count test threshold */
#define TRNG_HTCFG_APTTH            BITS(16,25)                /*!< adaptive proportion test threshold */

/* TRNG clock division */
#define CTL_ALGO(regval)            (BITS(12,13) & ((uint32_t)(regval) << 12U))
#define TRNG_ALGO_SHA1              CTL_ALGO(0)                /*!< TRNG conditioning module hash SHA1 */
#define TRNG_ALGO_MD5               CTL_ALGO(1)                /*!< TRNG conditioning module hash MD5 */
#define TRNG_ALGO_SHA224            CTL_ALGO(2)                /*!< TRNG conditioning module hash SHA224 */
#define TRNG_ALGO_SHA256            CTL_ALGO(3)                /*!< TRNG conditioning module hash SHA256 */

/* TRNG clock division */
#define CTL_CLKDIV(regval)          (BITS(16,19) & ((uint32_t)(regval) << 16U))
#define TRNG_CLK_DIV1               CTL_CLKDIV(0)              /*!< TRNG clock TRNG_CLK divider 1 */
#define TRNG_CLK_DIV2               CTL_CLKDIV(1)              /*!< TRNG clock TRNG_CLK divider 2 */
#define TRNG_CLK_DIV4               CTL_CLKDIV(2)              /*!< TRNG clock TRNG_CLK divider 4 */
#define TRNG_CLK_DIV8               CTL_CLKDIV(3)              /*!< TRNG clock TRNG_CLK divider 8 */
#define TRNG_CLK_DIV16              CTL_CLKDIV(4)              /*!< TRNG clock TRNG_CLK divider 16 */
#define TRNG_CLK_DIV32              CTL_CLKDIV(5)              /*!< TRNG clock TRNG_CLK divider 32 */
#define TRNG_CLK_DIV64              CTL_CLKDIV(6)              /*!< TRNG clock TRNG_CLK divider 64 */
#define TRNG_CLK_DIV128             CTL_CLKDIV(7)              /*!< TRNG clock TRNG_CLK divider 128 */
#define TRNG_CLK_DIV256             CTL_CLKDIV(8)              /*!< TRNG clock TRNG_CLK divider 256 */
#define TRNG_CLK_DIV512             CTL_CLKDIV(9)              /*!< TRNG clock TRNG_CLK divider 512 */
#define TRNG_CLK_DIV1024            CTL_CLKDIV(10)             /*!< TRNG clock TRNG_CLK divider 1024 */
#define TRNG_CLK_DIV2048            CTL_CLKDIV(11)             /*!< TRNG clock TRNG_CLK divider 2048 */
#define TRNG_CLK_DIV4096            CTL_CLKDIV(12)             /*!< TRNG clock TRNG_CLK divider 4096 */
#define TRNG_CLK_DIV8192            CTL_CLKDIV(13)             /*!< TRNG clock TRNG_CLK divider 8192 */
#define TRNG_CLK_DIV16384           CTL_CLKDIV(14)             /*!< TRNG clock TRNG_CLK divider 16384 */
#define TRNG_CLK_DIV32768           CTL_CLKDIV(15)             /*!< TRNG clock TRNG_CLK divider 32768 */

/* TRNG power mode */
#define CTL_NR(regval)              (BITS(24,25) & ((uint32_t)(regval) << 24U))
#define TRNG_NR_ULTRALOW            CTL_NR(0)                  /*!< TRNG analog power mode ultralow  */
#define TRNG_NR_LOW                 CTL_NR(1)                  /*!< TRNG analog power mode low  */
#define TRNG_NR_MEDIUM              CTL_NR(2)                  /*!< TRNG analog power mode medium  */
#define TRNG_NR_HIGH                CTL_NR(3)                  /*!< TRNG analog power mode high  */

/* constants definitions */
/* trng input mode */
typedef enum
{
    TRNG_INMOD_256BIT = 0,                                     /*!< conditioning module input bitwidth 256bits */
    TRNG_INMOD_440BIT = TRNG_CTL_INMOD                         /*!< conditioning module input bitwidth 440bits */
}trng_inmod_enum;

/* trng output mode */
typedef enum
{
    TRNG_OUTMOD_128BIT = 0,                                    /*!< conditioning module output bitwidth 128bits */
    TRNG_OUTMOD_256BIT = TRNG_CTL_OUTMOD                       /*!< conditioning module output bitwidth 256bits */
}trng_outmod_enum;

/* trng working mode */
typedef enum
{
    TRNG_MODSEL_LFSR = 0,                                      /*!< TRNG working in LFSR mode */
    TRNG_MODSEL_NIST = TRNG_CTL_MODSEL                         /*!< TRNG working in NIST mode */
}trng_modsel_enum;

/* trng status flag */
typedef enum
{
    TRNG_FLAG_DRDY = TRNG_STAT_DRDY,                           /*!< random Data ready status */
    TRNG_FLAG_CECS = TRNG_STAT_CECS,                           /*!< clock error current status */
    TRNG_FLAG_SECS = TRNG_STAT_SECS                            /*!< seed error current status */
}trng_flag_enum;

/* trng interrupt flag */
typedef enum
{
    TRNG_INT_FLAG_CEIF = TRNG_STAT_CEIF,                       /*!< clock error interrupt flag */
    TRNG_INT_FLAG_SEIF = TRNG_STAT_SEIF                        /*!< seed error interrupt flag */
}trng_int_flag_enum;


/* function declarations */
/* initialization functions */
/* deinitialize the TRNG */
void trng_deinit(void);
/* enable the TRNG interface */
void trng_enable(void);
/* disable the TRNG interface */
void trng_disable(void);
/* lock the TRNG control bits */
void trng_lock(void);
/* configure TRNG working mode */
void trng_mode_config(trng_modsel_enum mode_select);
/* enable the TRNG post-processing module */
void trng_postprocessing_enable(void);
/* disable the TRNG post-processing module */
void trng_postprocessing_disable(void);
/* enable the TRNG conditioning module */
void trng_conditioning_enable(void);
/* disable the TRNG conditioning module */
void trng_conditioning_disable(void);
/* configure TRNG conditioning module input bitwidth */
void trng_conditioning_input_bitwidth(trng_inmod_enum input_bitwidth);
/* configure TRNG conditioning module output bitwidth */
void trng_conditioning_output_bitwidth(trng_outmod_enum output_bitwidth);
/* enable TRNG replace test */
void trng_replace_test_enable(void);
/* disable TRNG replace test */
void trng_replace_test_disable(void);
/* enable hash algorithm init when conditioning module enabled */
void trng_hash_init_enable(void);
/* disable hash algorithm init when conditioning module enabled */
void trng_hash_init_disable(void);
/* configure TRNG analog power mode */
void trng_powermode_config(uint32_t powermode);
/* configure TRNG clock divider */
void trng_clockdiv_config(uint32_t clkdiv);
/* enable the TRNG clock error detection */
void trng_clockerror_detection_enable(void);
/* disable the TRNG clock error detection */
void trng_clockerror_detection_disable(void);
/* get the true random data */
uint32_t trng_get_true_random_data(void);

/* conditioning configration */
/* enable the conditioning logic reset */
void trng_conditioning_reset_enable(void);
/* disable the conditioning logic reset */
void trng_conditioning_reset_disable(void);
/* configure the conditioning module hash algorithm */
void trng_conditioning_algo_config(uint32_t module_algo);
/* configure health tests default value */
void trng_health_tests_config(uint32_t adpo_threshold, uint8_t rep_threshold);

/* flag & interrupt functions */
/* get the TRNG status flags */
FlagStatus trng_flag_get(trng_flag_enum flag);
/* enable TRNG interrupt */
void trng_interrupt_enable(void);
/* disable TRNG interrupt */
void trng_interrupt_disable(void);
/* get the TRNG interrupt flags */
FlagStatus trng_interrupt_flag_get(trng_int_flag_enum int_flag);
/* clear the TRNG interrupt flags */
void trng_interrupt_flag_clear(trng_int_flag_enum int_flag);

#endif /* GD32H7XX_TRNG_H */
