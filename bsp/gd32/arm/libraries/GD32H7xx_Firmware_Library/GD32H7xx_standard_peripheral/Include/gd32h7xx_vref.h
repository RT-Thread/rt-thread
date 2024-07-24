/*!
    \file    gd32h7xx_vref.h
    \brief   definitions for the VREF

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

#ifndef GD32H7XX_VREF_H
#define GD32H7XX_VREF_H

#include "gd32h7xx.h"

/* VREF definitions */
#define VREF                         VREF_BASE                                  /*!< VREF base address */

/* registers definitions */
#define VREF_CS                      REG32(VREF + 0x00000000U)                  /*!< VREF Control and status register */
#define VREF_CALIB                   REG32(VREF + 0x00000004U)                  /*!< VREF Calibration register */

/* bits definitions */
/* VREF_CS */
#define VREF_CS_VREFEN               BIT(0)                                     /*!< VREF enable */
#define VREF_CS_HIPM                 BIT(1)                                     /*!< High impedance mode */
#define VREF_CS_VREFRDY              BIT(3)                                     /*!< VREF ready */
#define VREF_CS_VREFS                BITS(4,5)                                  /*!< VREF voltage reference select */

/* VREF_CALIB */
#define VREF_CALIB_VREFCAL           BITS(0,5)                                  /*!< VREF calibration */

/* constants definitions */
/* VREF bit devinitions */
#define VREF_EN                      VREF_CS_VREFEN                             /*!< VREF enable */
#define VREF_HIGH_IMPEDANCE_MODE     VREF_CS_HIPM                               /*!< High impedance mode */
#define VREF_RDY                     VREF_CS_VREFRDY                            /*!< VREF ready */

/* VREF voltage reference select */
#define CS_VREFS(regval)             (BITS(4,5) & ((uint32_t)(regval) << 4U))
#define VREF_VOLTAGE_SEL_2_5V        CS_VREFS(0)                                /*!< VREF voltage reference select 2.5 V */
#define VREF_VOLTAGE_SEL_2_048V      CS_VREFS(1)                                /*!< VREF voltage reference select 2.048 V */
#define VREF_VOLTAGE_SEL_1_8V        CS_VREFS(2)                                /*!< VREF voltage reference select 1.8 V */
#define VREF_VOLTAGE_SEL_1_5V        CS_VREFS(3)                                /*!< VREF voltage reference select 1.5 V */

/* function declarations */
/* deinitialize the VREF */
void vref_deinit(void);
/* enable VREF */
void vref_enable(void);
/* disable VREF */
void vref_disable(void);
/* enable VREF high impendance mode */
void vref_high_impedance_mode_enable(void);
/* disable VREF high impendance mode */
void vref_high_impedance_mode_disable(void);
/* get the status of VREF */
FlagStatus vref_status_get(void);
/* select the VREF voltage reference */
void vref_voltage_select(uint32_t vref_voltage);
/* set the calibration value of VREF */
void vref_calib_value_set(uint8_t value);
/* get the calibration value of VREF */
uint8_t vref_calib_value_get(void);

#endif /* GD32H7XX_VREF_H */
