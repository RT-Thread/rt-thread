/*!
    \file    gd32h7xx_cpdm.h
    \brief   definitions for the CPDM

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

#ifndef GD32H7XX_CPDM_H
#define GD32H7XX_CPDM_H

#include "gd32h7xx.h"

/* CPDM definitions */
#define CPDM_SDIO0                 (SDIO0 + 0x00001000U)          /*!< SDIO0 CPDM base address */
#define CPDM_SDIO1                 (SDIO1 + 0x00000400U)          /*!< SDIO1 CPDM base address */

/* registers definitions */
#define CPDM_CTL(cpdmx)            REG32((cpdmx) + 0x00000000U)   /*!< CPDM control register */
#define CPDM_CFG(cpdmx)            REG32((cpdmx) + 0x00000004U)   /*!< CPDM configuration register */

/* bits definitions */
/* CPDM_CTL */
#define CPDM_CTL_CPDMEN            BIT(0)                         /*!< CPDM enable */
#define CPDM_CTL_DLSEN             BIT(1)                         /*!< CPDM delay line sample module enable */

/* CPDM_CFG */
#define CPDM_CFG_CPSEL             BITS(0,3)                      /*!< select the phase of the output clock */
#define CPDM_CFG_DLSTCNT           BITS(8,14)                     /*!< define a delay step count for a unit delay UNIT */
#define CPDM_CFG_DLLEN             BITS(16,27)                    /*!< delay line length */
#define CPDM_CFG_DLLENF            BIT(31)                        /*!< valid mark of delay line length */

/* constants definitions */
/* output clock phase selection enum definition */
typedef enum
{
    CPDM_OUTPUT_PHASE_SELECTION_0 = 0,                             /*!< output clock phase = input clock */
    CPDM_OUTPUT_PHASE_SELECTION_1,                                 /*!< output clock phase = input clock + 1 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_2,                                 /*!< output clock phase = input clock + 2 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_3,                                 /*!< output clock phase = input clock + 3 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_4,                                 /*!< output clock phase = input clock + 4 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_5,                                 /*!< output clock phase = input clock + 5 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_6,                                 /*!< output clock phase = input clock + 6 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_7,                                 /*!< output clock phase = input clock + 7 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_8,                                 /*!< output clock phase = input clock + 8 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_9,                                 /*!< output clock phase = input clock + 9 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_10,                                /*!< output clock phase = input clock + 10 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_11,                                /*!< output clock phase = input clock + 11 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_12,                                /*!< output clock phase = input clock + 12 * UNIT delay */
}cpdm_output_phase_enum;

#define CPDM_MAX_DELAY_STEP_COUNT  ((uint32_t)0x0000007FU)        /*!< max UNIT value  */
#define CPDM_MAX_PHASE             ((uint32_t)0x0000000CU)        /*!< max select value of the phase */

/* function declarations */
/* deinitialization and initialization functions */
/* enable CPDM */
void cpdm_enable(uint32_t cpdm_periph);
/* disable CPDM */
void cpdm_disable(uint32_t cpdm_periph);
/* enable CPDM delay line sample module */
void cpdm_delayline_sample_enable(uint32_t cpdm_periph);
/* disable CPDM delay line sample module */
void cpdm_delayline_sample_disable(uint32_t cpdm_periph);

/* output clock configuration functions */
/* select CPDM output clock phase */
void cpdm_output_clock_phase_select(uint32_t cpdm_periph, cpdm_output_phase_enum output_clock_phase);
/* get delay line length valid flag */
FlagStatus cpdm_delayline_length_valid_flag_get(uint32_t cpdm_periph);
/* get delay line length */
uint16_t cpdm_delayline_length_get(uint32_t cpdm_periph);

/* clock output function */
/* configure CPDM clock output */
void cpdm_clock_output(uint32_t cpdm_periph, cpdm_output_phase_enum output_clock_phase);

#endif /* GD32H7XX_CPDM_H */
