/**************************************************************************//**
 * @file     system_fm33lc0xx.h
 * @brief    CMSIS Cortex-M0 Device Peripheral Access Layer Header File for
 *           Device FM33LC0XX
 * @version  V2.0.0
 * @date     15. Mar 2021
 *
 * @note
 *
 ******************************************************************************/
/* Copyright (c) 2012 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/

#ifndef SYSTEM_FM33LC0XX_H
#define SYSTEM_FM33LC0XX_H

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief CMSIS Device version number
  */
#define __FM33LC0xx_CMSIS_VERSION_MAIN      (0x02) /*!< [31:24] main version */
#define __FM33LC0xx_CMSIS_VERSION_SUB1      (0x03) /*!< [23:16] sub1 version */
#define __FM33LC0xx_CMSIS_VERSION_SUB2      (0x01) /*!< [15:0]  sub2 version */
#define __FM33LC0xx_CMSIS_VERSION           ((__FM33LC0xx_CMSIS_VERSION_MAIN  << 24)\
                                             |(__FM33LC0xx_CMSIS_VERSION_SUB1 << 16)\
                                             |(__FM33LC0xx_CMSIS_VERSION_SUB2))

/* Configurations ------------------------------------------------------------*/
/**
 *  @brief LSCLK source
 *  @note  Comment the following line to use only LPOSC as LSCLK source, and also
 *         disable LSCLK auto switch function.
 */
#define USE_LSCLK_CLOCK_SRC_XTLF

#ifdef USE_LSCLK_CLOCK_SRC_XTLF

/**
 *  @brief LSCLK source
 *  @note  Comment the following line to disable LSCLK auto switch function.
 */
#define USE_LSCLK_AUTO_SWITCH

#endif  /* USE_LSCLK_CLOCK_SRC_XTLF */

/**
 *  @brief Open IWDT on program startup
 *  @note  Uncomment the following line to use IWDT on startup. User can modify
 *         the IWDT_OVERFLOW_PERIOD to change the IDWT overflow period.
 */
/* #define USE_IWDT_ON_STARTUP */

#ifdef USE_IWDT_ON_STARTUP
/*
    Valid value of IWDT_OVERFLOW_PERIOD:
    - 0x0: 125ms
    - 0x1: 250ms
    - 0x2: 500ms
    - 0x3: 1s
    - 0x4: 2s
    - 0x5: 4s
    - 0x6: 8s
    - 0x7: 16s
 */
#define IWDT_OVERFLOW_PERIOD  0x7
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Device Includes -----------------------------------------------------------*/
#include "fm33lc0xx.h"

/* Trim Values ---------------------------------------------------------------*/
/* Validate Function */
#define LDT_CHECK(_N_VALUE_, _T_VALUE_)                         \
                            ((((_N_VALUE_ >> 16) & 0xFFFFU) ==   \
                            (~(_N_VALUE_) & 0xFFFFU)) ? (_N_VALUE_) : (_T_VALUE_))

/* Trim Values Address */
#define LPOSC_LDT_TRIM      (*(uint32_t *)0x1FFFFB20U)   /* LPOSC trim value */
#define RCHF8M_LDT_TRIM     (*(uint32_t *)0x1FFFFB40U)   /* RC8M  trim value */
#define RCHF16M_LDT_TRIM    (*(uint32_t *)0x1FFFFB3CU)   /* RC16M trim value */
#define RCHF24M_LDT_TRIM    (*(uint32_t *)0x1FFFFB38U)   /* RC24M trim value */
#define RCMF4M_LDT_TRIM     (*(uint32_t *)0x1FFFFB44U)   /* RCMF  trim value */

/* Trim Values */
#define LPOSC_TRIM          (LDT_CHECK(LPOSC_LDT_TRIM,   0x80) & 0xFFU)
#define RCMF4M_TRIM         (LDT_CHECK(RCMF4M_LDT_TRIM,  0x40) & 0x7FU)
#define RCHF8M_TRIM         (LDT_CHECK(RCHF8M_LDT_TRIM,  0x40) & 0x7FU)
#define RCHF16M_TRIM        (LDT_CHECK(RCHF16M_LDT_TRIM, 0x40) & 0x7FU)
#define RCHF24M_TRIM        (LDT_CHECK(RCHF24M_LDT_TRIM, 0x40) & 0x7FU)

/* Default Clock Frequency Values --------------------------------------------*/

#define XTHF_DEFAULT_VALUE    ((uint32_t)8000000U)  /*!< Default value of XTHF in Hz */
#define XTLF_DEFAULT_VALUE    ((uint32_t)32768U)    /*!< Default value of XTLF in Hz */

/* Default system core clock value */
#define HCLK_DEFAULT_VALUE    ((uint32_t)8000000U)

/* Exported Clock Frequency Variables --------------------------------------- */
/*
    - [SystemCoreClock] holds the value of CPU operation clock freqency, and is initialized
        to HCLK_DEFAULT_VALUE;
    - [XTLFClock] holds the value of external low-frequency oscillator(XTLF),
        and is initialized to XTLF_DEFAULT_VALUE;
    - [XTHFClock] holds the value of external high_frequency oscillator(XTHF),
        and is initialized to XTHF_DEFAULT_VALUE;

    NOTE: If users are using these two external oscillators, they should modify the
    value of XTLFClock and XTHFClock to the correct value, and call the SystemCoreClockUpdate()
    to update the SystemCoreClock variable, otherwise those codes which rely on
    the SystemCoreClock variable will fail to run.
 */
extern uint32_t XTLFClock;        /*!< External Low-freq Osc Clock Frequency (XTLF) */
extern uint32_t XTHFClock;        /*!< External High-freq Osc Clock Frequency (XTHF) */
extern uint32_t SystemCoreClock;  /*!< System Clock Frequency (Core Clock) */

/**
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit(void);

/**
 * @brief  Updates the SystemCoreClock with current core Clock
 *         retrieved from cpu registers.
 */
void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_FM33LC0XX_H */
