/*!
    \file    gd32h7xx_trigsel.h
    \brief   definitions for the TRIGSEL

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

#ifndef GD32H7XX_TRIGSEL_H
#define GD32H7XX_TRIGSEL_H

#include "gd32h7xx.h"

/* TRIGSEL definitions */
#define TRIGSEL                           TRIGSEL_BASE                      /*!< TRIGSEL base address */

/* register definitions */
#define TRIGSEL_EXTOUT0                   REG32((TRIGSEL) + 0x00000000U)    /*!< TRIGSEL trigger selection for EXTOUT0 register */
#define TRIGSEL_EXTOUT1                   REG32((TRIGSEL) + 0x00000004U)    /*!< TRIGSEL trigger selection for EXTOUT1 register */
#define TRIGSEL_EXTOUT2                   REG32((TRIGSEL) + 0x00000008U)    /*!< TRIGSEL trigger selection for EXTOUT2 register */
#define TRIGSEL_EXTOUT3                   REG32((TRIGSEL) + 0x0000000CU)    /*!< TRIGSEL trigger selection for EXTOUT3 register */
#define TRIGSEL_ADC0                      REG32((TRIGSEL) + 0x00000010U)    /*!< TRIGSEL trigger selection for ADC0 register */
#define TRIGSEL_ADC1                      REG32((TRIGSEL) + 0x00000014U)    /*!< TRIGSEL trigger selection for ADC1 register */
#define TRIGSEL_ADC2                      REG32((TRIGSEL) + 0x00000018U)    /*!< TRIGSEL trigger selection for ADC2 register */
#define TRIGSEL_DACOUT0                   REG32((TRIGSEL) + 0x0000001CU)    /*!< TRIGSEL trigger selection for DAC_OUT0 register */
#define TRIGSEL_DACOUT1                   REG32((TRIGSEL) + 0x00000020U)    /*!< TRIGSEL trigger selection for DAC_OUT1 register */
#define TRIGSEL_TIMER0BRKIN               REG32((TRIGSEL) + 0x00000024U)    /*!< TRIGSEL trigger selection for TIMER0_BRKIN register */
#define TRIGSEL_TIMER7BRKIN               REG32((TRIGSEL) + 0x00000028U)    /*!< TRIGSEL trigger selection for TIMER7_BRKIN register */
#define TRIGSEL_TIMER14BRKIN              REG32((TRIGSEL) + 0x0000002CU)    /*!< TRIGSEL trigger selection for TIMER14_BRKIN register */
#define TRIGSEL_TIMER15BRKIN              REG32((TRIGSEL) + 0x00000030U)    /*!< TRIGSEL trigger selection for TIMER15_BRKIN register */
#define TRIGSEL_TIMER16BRKIN              REG32((TRIGSEL) + 0x00000034U)    /*!< TRIGSEL trigger selection for TIMER16_BRKIN register */
#define TRIGSEL_TIMER40BRKIN              REG32((TRIGSEL) + 0x00000038U)    /*!< TRIGSEL trigger selection for TIMER40_BRKIN register */
#define TRIGSEL_TIMER41BRKIN              REG32((TRIGSEL) + 0x0000003CU)    /*!< TRIGSEL trigger selection for TIMER41_BRKIN register */
#define TRIGSEL_TIMER42BRKIN              REG32((TRIGSEL) + 0x00000040U)    /*!< TRIGSEL trigger selection for TIMER42_BRKIN register */
#define TRIGSEL_TIMER43BRKIN              REG32((TRIGSEL) + 0x00000044U)    /*!< TRIGSEL trigger selection for TIMER43_BRKIN register */
#define TRIGSEL_TIMER44BRKIN              REG32((TRIGSEL) + 0x00000048U)    /*!< TRIGSEL trigger selection for TIMER44_BRKIN register */
#define TRIGSEL_CAN0                      REG32((TRIGSEL) + 0x0000004CU)    /*!< TRIGSEL trigger selection for CAN0 register */
#define TRIGSEL_CAN1                      REG32((TRIGSEL) + 0x00000050U)    /*!< TRIGSEL trigger selection for CAN1 register */
#define TRIGSEL_CAN2                      REG32((TRIGSEL) + 0x00000054U)    /*!< TRIGSEL trigger selection for CAN2 register */
#define TRIGSEL_LPDTS                     REG32((TRIGSEL) + 0x00000058U)    /*!< TRIGSEL trigger selection for LPDTS register */
#define TRIGSEL_TIMER0ETI                 REG32((TRIGSEL) + 0x0000005CU)    /*!< TRIGSEL trigger selection for TIMER0_ETI register */
#define TRIGSEL_TIMER1ETI                 REG32((TRIGSEL) + 0x00000060U)    /*!< TRIGSEL trigger selection for TIMER1_ETI register */
#define TRIGSEL_TIMER2ETI                 REG32((TRIGSEL) + 0x00000064U)    /*!< TRIGSEL trigger selection for TIMER2_ETI register */
#define TRIGSEL_TIMER3ETI                 REG32((TRIGSEL) + 0x00000068U)    /*!< TRIGSEL trigger selection for TIMER3_ETI register */
#define TRIGSEL_TIMER4ETI                 REG32((TRIGSEL) + 0x0000006CU)    /*!< TRIGSEL trigger selection for TIMER4_ETI register */
#define TRIGSEL_TIMER7ETI                 REG32((TRIGSEL) + 0x00000070U)    /*!< TRIGSEL trigger selection for TIMER7_ETI register */
#define TRIGSEL_TIMER22ETI                REG32((TRIGSEL) + 0x00000074U)    /*!< TRIGSEL trigger selection for TIMER22_ETI register */
#define TRIGSEL_TIMER23ETI                REG32((TRIGSEL) + 0x00000078U)    /*!< TRIGSEL trigger selection for TIMER23_ETI register */
#define TRIGSEL_TIMER30ETI                REG32((TRIGSEL) + 0x0000007CU)    /*!< TRIGSEL trigger selection for TIMER30_ETI register */
#define TRIGSEL_TIMER31ETI                REG32((TRIGSEL) + 0x00000080U)    /*!< TRIGSEL trigger selection for TIMER31_ETI register */
#define TRIGSEL_EDOUT                     REG32((TRIGSEL) + 0x00000084U)    /*!< TRIGSEL trigger selection for EDOUT register */
#define TRIGSEL_HPDF                      REG32((TRIGSEL) + 0x00000088U)    /*!< TRIGSEL trigger selection for HPDF register */
#define TRIGSEL_TIMER0ITI14               REG32((TRIGSEL) + 0x0000008CU)    /*!< TRIGSEL trigger selection for TIMER0_ITI14 register */
#define TRIGSEL_TIMER1ITI14               REG32((TRIGSEL) + 0x00000090U)    /*!< TRIGSEL trigger selection for TIMER1_ITI14 register */
#define TRIGSEL_TIMER2ITI14               REG32((TRIGSEL) + 0x00000094U)    /*!< TRIGSEL trigger selection for TIMER2_ITI14 register */
#define TRIGSEL_TIMER3ITI14               REG32((TRIGSEL) + 0x00000098U)    /*!< TRIGSEL trigger selection for TIMER3_ITI14 register */
#define TRIGSEL_TIMER4ITI14               REG32((TRIGSEL) + 0x0000009CU)    /*!< TRIGSEL trigger selection for TIMER4_ITI14 register */
#define TRIGSEL_TIMER7ITI14               REG32((TRIGSEL) + 0x000000A0U)    /*!< TRIGSEL trigger selection for TIMER7_ITI14 register */
#define TRIGSEL_TIMER14ITI14              REG32((TRIGSEL) + 0x000000A4U)    /*!< TRIGSEL trigger selection for TIMER14_ITI14 register */
#define TRIGSEL_TIMER22ITI14              REG32((TRIGSEL) + 0x000000A8U)    /*!< TRIGSEL trigger selection for TIMER22_ITI14 register */
#define TRIGSEL_TIMER23ITI14              REG32((TRIGSEL) + 0x000000ACU)    /*!< TRIGSEL trigger selection for TIMER23_ITI14 register */
#define TRIGSEL_TIMER30ITI14              REG32((TRIGSEL) + 0x000000B0U)    /*!< TRIGSEL trigger selection for TIMER30_ITI14 register */
#define TRIGSEL_TIMER31ITI14              REG32((TRIGSEL) + 0x000000B4U)    /*!< TRIGSEL trigger selection for TIMER31_ITI14 register */
#define TRIGSEL_TIMER40ITI14              REG32((TRIGSEL) + 0x000000B8U)    /*!< TRIGSEL trigger selection for TIMER40_ITI14 register */
#define TRIGSEL_TIMER41ITI14              REG32((TRIGSEL) + 0x000000BCU)    /*!< TRIGSEL trigger selection for TIMER41_ITI14 register */
#define TRIGSEL_TIMER42ITI14              REG32((TRIGSEL) + 0x000000C0U)    /*!< TRIGSEL trigger selection for TIMER42_ITI14 register */
#define TRIGSEL_TIMER43ITI14              REG32((TRIGSEL) + 0x000000C4U)    /*!< TRIGSEL trigger selection for TIMER43_ITI14 register */
#define TRIGSEL_TIMER44ITI14              REG32((TRIGSEL) + 0x000000C8U)    /*!< TRIGSEL trigger selection for TIMER44_ITI14 register */

/* bit definitions */
/* trigger input source selection */
#define TRIGSEL_TARGET_INSEL0             BITS(0,7)                         /*!< trigger input source selection for output0 */
#define TRIGSEL_TARGET_INSEL1             BITS(8,15)                        /*!< trigger input source selection for output1 */
#define TRIGSEL_TARGET_INSEL2             BITS(16,23)                       /*!< trigger input source selection for output2 */
#define TRIGSEL_TARGET_LK                 BIT(31)                           /*!< TRIGSEL register lock */

/* constants definitions */
/* trigger source definitions */
typedef enum
{
    TRIGSEL_INPUT_0                       = ((uint8_t)0x00U),               /*!< trigger input source 0 */
    TRIGSEL_INPUT_1                       = ((uint8_t)0x01U),               /*!< trigger input source 1 */
    TRIGSEL_INPUT_TRIGSEL_IN0             = ((uint8_t)0x02U),               /*!< trigger input source TRIGSEL_IN0 pin */
    TRIGSEL_INPUT_TRIGSEL_IN1             = ((uint8_t)0x03U),               /*!< trigger input source TRIGSEL_IN1 pin */
    TRIGSEL_INPUT_TRIGSEL_IN2             = ((uint8_t)0x04U),               /*!< trigger input source TRIGSEL_IN2 pin */
    TRIGSEL_INPUT_TRIGSEL_IN3             = ((uint8_t)0x05U),               /*!< trigger input source TRIGSEL_IN3 pin */
    TRIGSEL_INPUT_TRIGSEL_IN4             = ((uint8_t)0x06U),               /*!< trigger input source TRIGSEL_IN4 pin */
    TRIGSEL_INPUT_TRIGSEL_IN5             = ((uint8_t)0x07U),               /*!< trigger input source TRIGSEL_IN5 pin */
    TRIGSEL_INPUT_TRIGSEL_IN6             = ((uint8_t)0x08U),               /*!< trigger input source TRIGSEL_IN6 pin */
    TRIGSEL_INPUT_TRIGSEL_IN7             = ((uint8_t)0x09U),               /*!< trigger input source TRIGSEL_IN7 pin */
    TRIGSEL_INPUT_TRIGSEL_IN8             = ((uint8_t)0x0AU),               /*!< trigger input source TRIGSEL_IN8 pin */
    TRIGSEL_INPUT_TRIGSEL_IN9             = ((uint8_t)0x0BU),               /*!< trigger input source TRIGSEL_IN9 pin */
    TRIGSEL_INPUT_TRIGSEL_IN10            = ((uint8_t)0x0CU),               /*!< trigger input source TRIGSEL_IN10 pin */
    TRIGSEL_INPUT_TRIGSEL_IN11            = ((uint8_t)0x0DU),               /*!< trigger input source TRIGSEL_IN11 pin */
    TRIGSEL_INPUT_TRIGSEL_IN12            = ((uint8_t)0x0EU),               /*!< trigger input source TRIGSEL_IN12 pin */
    TRIGSEL_INPUT_TRIGSEL_IN13            = ((uint8_t)0x0FU),               /*!< trigger input source TRIGSEL_IN13 pin */
    TRIGSEL_INPUT_LXTAL_TRG               = ((uint8_t)0x10U),               /*!< trigger input source LXTAL_TRG */
    TRIGSEL_INPUT_TIMER0_TRGO0            = ((uint8_t)0x11U),               /*!< trigger input source TIMER0 TRGO0 */
    TRIGSEL_INPUT_TIMER0_TRGO1            = ((uint8_t)0x12U),               /*!< trigger input source TIMER0 TRGO1 */
    TRIGSEL_INPUT_TIMER0_CH0              = ((uint8_t)0x13U),               /*!< trigger input source TIMER0 CH0 */
    TRIGSEL_INPUT_TIMER0_CH1              = ((uint8_t)0x14U),               /*!< trigger input source TIMER0 CH1 */
    TRIGSEL_INPUT_TIMER0_CH2              = ((uint8_t)0x15U),               /*!< trigger input source TIMER0 CH2 */
    TRIGSEL_INPUT_TIMER0_CH3              = ((uint8_t)0x16U),               /*!< trigger input source TIMER0 CH3 */
    TRIGSEL_INPUT_TIMER0_MCH0             = ((uint8_t)0x17U),               /*!< trigger input source TIMER0 MCH0 */
    TRIGSEL_INPUT_TIMER0_MCH1             = ((uint8_t)0x18U),               /*!< trigger input source TIMER0 MCH1 */
    TRIGSEL_INPUT_TIMER0_MCH2             = ((uint8_t)0x19U),               /*!< trigger input source TIMER0 MCH2 */
    TRIGSEL_INPUT_TIMER0_MCH3             = ((uint8_t)0x1AU),               /*!< trigger input source TIMER0 MCH3 */
    TRIGSEL_INPUT_TIMER0_BRKIN0           = ((uint8_t)0x21U),               /*!< trigger input source TIMER0 BRKIN0 */
    TRIGSEL_INPUT_TIMER0_BRKIN1           = ((uint8_t)0x22U),               /*!< trigger input source TIMER0 BRKIN1 */
    TRIGSEL_INPUT_TIMER0_BRKIN2           = ((uint8_t)0x23U),               /*!< trigger input source TIMER0 BRKIN2 */
    TRIGSEL_INPUT_TIMER0_ETI              = ((uint8_t)0x24U),               /*!< trigger input source TIMER0 ETI */
    TRIGSEL_INPUT_TIMER1_TRGO0            = ((uint8_t)0x25U),               /*!< trigger input source TIMER1 TRGO0 */
    TRIGSEL_INPUT_TIMER1_CH0              = ((uint8_t)0x26U),               /*!< trigger input source TIMER1 CH0 */
    TRIGSEL_INPUT_TIMER1_CH1              = ((uint8_t)0x27U),               /*!< trigger input source TIMER1 CH1 */
    TRIGSEL_INPUT_TIMER1_CH2              = ((uint8_t)0x28U),               /*!< trigger input source TIMER1 CH2 */
    TRIGSEL_INPUT_TIMER1_CH3              = ((uint8_t)0x29U),               /*!< trigger input source TIMER1 CH3 */
    TRIGSEL_INPUT_TIMER1_ETI              = ((uint8_t)0x2AU),               /*!< trigger input source TIMER1 ETI */
    TRIGSEL_INPUT_TIMER2_TRGO0            = ((uint8_t)0x2BU),               /*!< trigger input source TIMER2 TRGO0 */
    TRIGSEL_INPUT_TIMER2_CH0              = ((uint8_t)0x2CU),               /*!< trigger input source TIMER2 CH0 */
    TRIGSEL_INPUT_TIMER2_CH1              = ((uint8_t)0x2DU),               /*!< trigger input source TIMER2 CH1 */
    TRIGSEL_INPUT_TIMER2_CH2              = ((uint8_t)0x2EU),               /*!< trigger input source TIMER2 CH2 */
    TRIGSEL_INPUT_TIMER2_CH3              = ((uint8_t)0x2FU),               /*!< trigger input source TIMER2 CH3 */
    TRIGSEL_INPUT_TIMER2_ETI              = ((uint8_t)0x30U),               /*!< trigger input source TIMER2 ETI */
    TRIGSEL_INPUT_TIMER3_TRGO0            = ((uint8_t)0x31U),               /*!< trigger input source TIMER3 TRGO0 */
    TRIGSEL_INPUT_TIMER3_CH0              = ((uint8_t)0x32U),               /*!< trigger input source TIMER3 CH0 */
    TRIGSEL_INPUT_TIMER3_CH1              = ((uint8_t)0x33U),               /*!< trigger input source TIMER3 CH1 */
    TRIGSEL_INPUT_TIMER3_CH2              = ((uint8_t)0x34U),               /*!< trigger input source TIMER3 CH2 */
    TRIGSEL_INPUT_TIMER3_CH3              = ((uint8_t)0x35U),               /*!< trigger input source TIMER3 CH3 */
    TRIGSEL_INPUT_TIMER3_ETI              = ((uint8_t)0x36U),               /*!< trigger input source TIMER3 ETI */
    TRIGSEL_INPUT_TIMER4_TRGO0            = ((uint8_t)0x37U),               /*!< trigger input source TIMER4 TRGO0 */
    TRIGSEL_INPUT_TIMER4_CH0              = ((uint8_t)0x38U),               /*!< trigger input source TIMER4 CH0 */
    TRIGSEL_INPUT_TIMER4_CH1              = ((uint8_t)0x39U),               /*!< trigger input source TIMER4 CH1 */
    TRIGSEL_INPUT_TIMER4_CH2              = ((uint8_t)0x3AU),               /*!< trigger input source TIMER4 CH2 */
    TRIGSEL_INPUT_TIMER4_CH3              = ((uint8_t)0x3BU),               /*!< trigger input source TIMER4 CH3 */
    TRIGSEL_INPUT_TIMER4_ETI              = ((uint8_t)0x3CU),               /*!< trigger input source TIMER4 ETI */
    TRIGSEL_INPUT_TIMER5_TRGO0            = ((uint8_t)0x3DU),               /*!< trigger input source TIMER5 TRGO0 */
    TRIGSEL_INPUT_TIMER6_TRGO0            = ((uint8_t)0x3EU),               /*!< trigger input source TIMER6 TRGO0 */
    TRIGSEL_INPUT_TIMER7_TRGO0            = ((uint8_t)0x3FU),               /*!< trigger input source TIMER7 TRGO0 */
    TRIGSEL_INPUT_TIMER7_TRGO1            = ((uint8_t)0x40U),               /*!< trigger input source TIMER7 TRGO1 */
    TRIGSEL_INPUT_TIMER7_CH0              = ((uint8_t)0x41U),               /*!< trigger input source TIMER7 CH0 */
    TRIGSEL_INPUT_TIMER7_CH1              = ((uint8_t)0x42U),               /*!< trigger input source TIMER7 CH1 */
    TRIGSEL_INPUT_TIMER7_CH2              = ((uint8_t)0x43U),               /*!< trigger input source TIMER7 CH2 */
    TRIGSEL_INPUT_TIMER7_CH3              = ((uint8_t)0x44U),               /*!< trigger input source TIMER7 CH3 */
    TRIGSEL_INPUT_TIMER7_MCH0             = ((uint8_t)0x45U),               /*!< trigger input source TIMER7 MCH0 */
    TRIGSEL_INPUT_TIMER7_MCH1             = ((uint8_t)0x46U),               /*!< trigger input source TIMER7 MCH1 */
    TRIGSEL_INPUT_TIMER7_MCH2             = ((uint8_t)0x47U),               /*!< trigger input source TIMER7 MCH2 */
    TRIGSEL_INPUT_TIMER7_MCH3             = ((uint8_t)0x48U),               /*!< trigger input source TIMER7 MCH3 */
    TRIGSEL_INPUT_TIMER7_BRKIN0           = ((uint8_t)0x4FU),               /*!< trigger input source TIMER7 BRKIN0 */
    TRIGSEL_INPUT_TIMER7_BRKIN1           = ((uint8_t)0x50U),               /*!< trigger input source TIMER7 BRKIN1 */
    TRIGSEL_INPUT_TIMER7_BRKIN2           = ((uint8_t)0x51U),               /*!< trigger input source TIMER7 BRKIN2 */
    TRIGSEL_INPUT_TIMER7_ETI              = ((uint8_t)0x52U),               /*!< trigger input source TIMER7 ETI */
    TRIGSEL_INPUT_TIMER14_TRGO0           = ((uint8_t)0x53U),               /*!< trigger input source TIMER14 TRGO0 */
    TRIGSEL_INPUT_TIMER14_CH0             = ((uint8_t)0x54U),               /*!< trigger input source TIMER14 CH0 */
    TRIGSEL_INPUT_TIMER14_CH1             = ((uint8_t)0x55U),               /*!< trigger input source TIMER14 CH1 */
    TRIGSEL_INPUT_TIMER14_MCH0            = ((uint8_t)0x56U),               /*!< trigger input source TIMER14 MCH0 */
    TRIGSEL_INPUT_TIMER14_BRKIN           = ((uint8_t)0x59U),               /*!< trigger input source TIMER14 BRKIN */
    TRIGSEL_INPUT_TIMER15_CH0             = ((uint8_t)0x5AU),               /*!< trigger input source TIMER15 CH0 */
    TRIGSEL_INPUT_TIMER15_MCH0            = ((uint8_t)0x5BU),               /*!< trigger input source TIMER15 MCH0 */
    TRIGSEL_INPUT_TIMER15_BRKIN           = ((uint8_t)0x5EU),               /*!< trigger input source TIMER15 BRKIN */
    TRIGSEL_INPUT_TIMER16_CH0             = ((uint8_t)0x5FU),               /*!< trigger input source TIMER16 CH0 */
    TRIGSEL_INPUT_TIMER16_MCH0            = ((uint8_t)0x60U),               /*!< trigger input source TIMER16 MCH0 */
    TRIGSEL_INPUT_TIMER16_BRKIN           = ((uint8_t)0x63U),               /*!< trigger input source TIMER16 BRKIN */
    TRIGSEL_INPUT_TIMER22_TRGO0           = ((uint8_t)0x64U),               /*!< trigger input source TIMER22 TRGO0 */
    TRIGSEL_INPUT_TIMER22_CH0             = ((uint8_t)0x65U),               /*!< trigger input source TIMER22 CH0 */
    TRIGSEL_INPUT_TIMER22_CH1             = ((uint8_t)0x66U),               /*!< trigger input source TIMER22 CH1 */
    TRIGSEL_INPUT_TIMER22_CH2             = ((uint8_t)0x67U),               /*!< trigger input source TIMER22 CH2 */
    TRIGSEL_INPUT_TIMER22_CH3             = ((uint8_t)0x68U),               /*!< trigger input source TIMER22 CH3 */
    TRIGSEL_INPUT_TIMER22_ETI             = ((uint8_t)0x69U),               /*!< trigger input source TIMER22 ETI */
    TRIGSEL_INPUT_TIMER23_TRGO0           = ((uint8_t)0x6AU),               /*!< trigger input source TIMER23 TRGO0 */
    TRIGSEL_INPUT_TIMER23_CH0             = ((uint8_t)0x6BU),               /*!< trigger input source TIMER23 CH0 */
    TRIGSEL_INPUT_TIMER23_CH1             = ((uint8_t)0x6CU),               /*!< trigger input source TIMER23 CH1 */
    TRIGSEL_INPUT_TIMER23_CH2             = ((uint8_t)0x6DU),               /*!< trigger input source TIMER23 CH2 */
    TRIGSEL_INPUT_TIMER23_CH3             = ((uint8_t)0x6EU),               /*!< trigger input source TIMER23 CH3 */
    TRIGSEL_INPUT_TIMER23_ETI             = ((uint8_t)0x6FU),               /*!< trigger input source TIMER23 ETI */
    TRIGSEL_INPUT_TIMER30_TRGO0           = ((uint8_t)0x70U),               /*!< trigger input source TIMER30 TRGO0 */
    TRIGSEL_INPUT_TIMER30_CH0             = ((uint8_t)0x71U),               /*!< trigger input source TIMER30 CH0 */
    TRIGSEL_INPUT_TIMER30_CH1             = ((uint8_t)0x72U),               /*!< trigger input source TIMER30 CH1 */
    TRIGSEL_INPUT_TIMER30_CH2             = ((uint8_t)0x73U),               /*!< trigger input source TIMER30 CH2 */
    TRIGSEL_INPUT_TIMER30_CH3             = ((uint8_t)0x74U),               /*!< trigger input source TIMER30 CH3 */
    TRIGSEL_INPUT_TIMER30_ETI             = ((uint8_t)0x75U),               /*!< trigger input source TIMER30 ETI */
    TRIGSEL_INPUT_TIMER31_TRGO0           = ((uint8_t)0x76U),               /*!< trigger input source TIMER31 TRGO0 */
    TRIGSEL_INPUT_TIMER31_CH0             = ((uint8_t)0x77U),               /*!< trigger input source TIMER31 CH0 */
    TRIGSEL_INPUT_TIMER31_CH1             = ((uint8_t)0x78U),               /*!< trigger input source TIMER31 CH1 */
    TRIGSEL_INPUT_TIMER31_CH2             = ((uint8_t)0x79U),               /*!< trigger input source TIMER31 CH2 */
    TRIGSEL_INPUT_TIMER31_CH3             = ((uint8_t)0x7AU),               /*!< trigger input source TIMER31 CH3 */
    TRIGSEL_INPUT_TIMER31_ETI             = ((uint8_t)0x7BU),               /*!< trigger input source TIMER31 ETI */
    TRIGSEL_INPUT_TIMER40_TRGO0           = ((uint8_t)0x7CU),               /*!< trigger input source TIMER40 TRGO0 */
    TRIGSEL_INPUT_TIMER40_CH0             = ((uint8_t)0x7DU),               /*!< trigger input source TIMER40 CH0 */
    TRIGSEL_INPUT_TIMER40_CH1             = ((uint8_t)0x7EU),               /*!< trigger input source TIMER40 CH1 */
    TRIGSEL_INPUT_TIMER40_MCH0            = ((uint8_t)0x7FU),               /*!< trigger input source TIMER40 MCH0 */
    TRIGSEL_INPUT_TIMER40_BRKIN           = ((uint8_t)0x82U),               /*!< trigger input source TIMER40 BRKIN */
    TRIGSEL_INPUT_TIMER41_TRGO0           = ((uint8_t)0x83U),               /*!< trigger input source TIMER41 TRGO0 */
    TRIGSEL_INPUT_TIMER41_CH0             = ((uint8_t)0x84U),               /*!< trigger input source TIMER41 CH0 */
    TRIGSEL_INPUT_TIMER41_CH1             = ((uint8_t)0x85U),               /*!< trigger input source TIMER41 CH1 */
    TRIGSEL_INPUT_TIMER41_MCH0            = ((uint8_t)0x86U),               /*!< trigger input source TIMER41 MCH0 */
    TRIGSEL_INPUT_TIMER41_BRKIN           = ((uint8_t)0x89U),               /*!< trigger input source TIMER41 BRKIN */
    TRIGSEL_INPUT_TIMER42_TRGO0           = ((uint8_t)0x8AU),               /*!< trigger input source TIMER42 TRGO0 */
    TRIGSEL_INPUT_TIMER42_CH0             = ((uint8_t)0x8BU),               /*!< trigger input source TIMER42 CH0 */
    TRIGSEL_INPUT_TIMER42_CH1             = ((uint8_t)0x8CU),               /*!< trigger input source TIMER42 CH1 */
    TRIGSEL_INPUT_TIMER42_MCH0            = ((uint8_t)0x8DU),               /*!< trigger input source TIMER42 MCH0 */
    TRIGSEL_INPUT_TIMER42_BRKIN           = ((uint8_t)0x90U),               /*!< trigger input source TIMER42 BRKIN */
    TRIGSEL_INPUT_TIMER43_TRGO0           = ((uint8_t)0x91U),               /*!< trigger input source TIMER43 TRGO0 */
    TRIGSEL_INPUT_TIMER43_CH0             = ((uint8_t)0x92U),               /*!< trigger input source TIMER43 CH0 */
    TRIGSEL_INPUT_TIMER43_CH1             = ((uint8_t)0x93U),               /*!< trigger input source TIMER43 CH1 */
    TRIGSEL_INPUT_TIMER43_MCH0            = ((uint8_t)0x94U),               /*!< trigger input source TIMER43 MCH0 */
    TRIGSEL_INPUT_TIMER43_BRKIN           = ((uint8_t)0x97U),               /*!< trigger input source TIMER43 BRKIN */
    TRIGSEL_INPUT_TIMER44_TRGO0           = ((uint8_t)0x98U),               /*!< trigger input source TIMER44 TRGO0 */
    TRIGSEL_INPUT_TIMER44_CH0             = ((uint8_t)0x99U),               /*!< trigger input source TIMER44 CH0 */
    TRIGSEL_INPUT_TIMER44_CH1             = ((uint8_t)0x9AU),               /*!< trigger input source TIMER44 CH1 */
    TRIGSEL_INPUT_TIMER44_MCH0            = ((uint8_t)0x9BU),               /*!< trigger input source TIMER44 MCH0 */
    TRIGSEL_INPUT_TIMER44_BRKIN           = ((uint8_t)0x9EU),               /*!< trigger input source TIMER44 BRKIN */
    TRIGSEL_INPUT_TIMER50_TRGO0           = ((uint8_t)0x9FU),               /*!< trigger input source TIMER50 TRGO0 */
    TRIGSEL_INPUT_TIMER51_TRGO0           = ((uint8_t)0xA0U),               /*!< trigger input source TIMER51 TRGO0 */
    TRIGSEL_INPUT_RTC_ALARM               = ((uint8_t)0xA1U),               /*!< trigger input source RTC alarm */
    TRIGSEL_INPUT_RTC_TPTS                = ((uint8_t)0xA2U),               /*!< trigger input source RTC TPTS */
    TRIGSEL_INPUT_ADC0_WD0_OUT            = ((uint8_t)0xA3U),               /*!< trigger input source ADC0 watchdog0 output */
    TRIGSEL_INPUT_ADC0_WD1_OUT            = ((uint8_t)0xA4U),               /*!< trigger input source ADC0 watchdog1 output */
    TRIGSEL_INPUT_ADC0_WD2_OUT            = ((uint8_t)0xA5U),               /*!< trigger input source ADC0 watchdog2 output */
    TRIGSEL_INPUT_ADC1_WD0_OUT            = ((uint8_t)0xA6U),               /*!< trigger input source ADC1 watchdog0 output */
    TRIGSEL_INPUT_ADC1_WD1_OUT            = ((uint8_t)0xA7U),               /*!< trigger input source ADC1 watchdog1 output */
    TRIGSEL_INPUT_ADC1_WD2_OUT            = ((uint8_t)0xA8U),               /*!< trigger input source ADC1 watchdog2 output */
    TRIGSEL_INPUT_ADC2_WD0_OUT            = ((uint8_t)0xA9U),               /*!< trigger input source ADC2 watchdog0 output */
    TRIGSEL_INPUT_ADC2_WD1_OUT            = ((uint8_t)0xAAU),               /*!< trigger input source ADC2 watchdog1 output */
    TRIGSEL_INPUT_ADC2_WD2_OUT            = ((uint8_t)0xABU),               /*!< trigger input source ADC2 watchdog2 output */
    TRIGSEL_INPUT_CMP0_OUT                = ((uint8_t)0xACU),               /*!< trigger input source CMP0_OUT */
    TRIGSEL_INPUT_CMP1_OUT                = ((uint8_t)0xADU),               /*!< trigger input source CMP1_OUT */
    TRIGSEL_INPUT_SAI0_AFS_OUT            = ((uint8_t)0xAEU),               /*!< trigger input source SAI0_AFS_OUT */
    TRIGSEL_INPUT_SAI0_BFS_OUT            = ((uint8_t)0xAFU),               /*!< trigger input source SAI0_BFS_OUT */
    TRIGSEL_INPUT_SAI2_AFS_OUT            = ((uint8_t)0xB0U),               /*!< trigger input source SAI2_AFS_OUT */
    TRIGSEL_INPUT_SAI2_BFS_OUT            = ((uint8_t)0xB1U),               /*!< trigger input source SAI2_BFS_OUT */
}trigsel_source_enum;

/* target peripheral definitions */
typedef enum
{
    TRIGSEL_OUTPUT_TRIGSEL_OUT0           = ((uint8_t)0x00U),               /*!< output target peripheral TRIGSEL_OUT0 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT1           = ((uint8_t)0x01U),               /*!< output target peripheral TRIGSEL_OUT1 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT2           = ((uint8_t)0x04U),               /*!< output target peripheral TRIGSEL_OUT2 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT3           = ((uint8_t)0x05U),               /*!< output target peripheral TRIGSEL_OUT3 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT4           = ((uint8_t)0x08U),               /*!< output target peripheral TRIGSEL_OUT4 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT5           = ((uint8_t)0x09U),               /*!< output target peripheral TRIGSEL_OUT5 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT6           = ((uint8_t)0x0CU),               /*!< output target peripheral TRIGSEL_OUT6 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT7           = ((uint8_t)0x0DU),               /*!< output target peripheral TRIGSEL_OUT7 pin */
    TRIGSEL_OUTPUT_ADC0_REGTRG            = ((uint8_t)0x10U),               /*!< output target peripheral ADC0_REGTRG */
    TRIGSEL_OUTPUT_ADC0_INSTRG            = ((uint8_t)0x11U),               /*!< output target peripheral ADC0_INSTRG */
    TRIGSEL_OUTPUT_ADC1_REGTRG            = ((uint8_t)0x14U),               /*!< output target peripheral ADC1_REGTRG */
    TRIGSEL_OUTPUT_ADC1_INSTRG            = ((uint8_t)0x15U),               /*!< output target peripheral ADC1_INSTRG */
    TRIGSEL_OUTPUT_ADC2_REGTRG            = ((uint8_t)0x18U),               /*!< output target peripheral ADC2_REGTRG */
    TRIGSEL_OUTPUT_ADC2_INSTRG            = ((uint8_t)0x19U),               /*!< output target peripheral ADC2_INSTRG */
    TRIGSEL_OUTPUT_DAC_OUT0_EXTRG         = ((uint8_t)0x1CU),               /*!< output target peripheral DAC_OUT0_EXTRG */
    TRIGSEL_OUTPUT_DAC_OUT1_EXTRG         = ((uint8_t)0x20U),               /*!< output target peripheral DAC_OUT1_EXTRG */
    TRIGSEL_OUTPUT_TIMER0_BRKIN0          = ((uint8_t)0x24U),               /*!< output target peripheral TIMER0_BRKIN0 */
    TRIGSEL_OUTPUT_TIMER0_BRKIN1          = ((uint8_t)0x25U),               /*!< output target peripheral TIMER0_BRKIN1 */
    TRIGSEL_OUTPUT_TIMER0_BRKIN2          = ((uint8_t)0x26U),               /*!< output target peripheral TIMER0_BRKIN2 */
    TRIGSEL_OUTPUT_TIMER7_BRKIN0          = ((uint8_t)0x28U),               /*!< output target peripheral TIMER7_BRKIN0 */
    TRIGSEL_OUTPUT_TIMER7_BRKIN1          = ((uint8_t)0x29U),               /*!< output target peripheral TIMER7_BRKIN1 */
    TRIGSEL_OUTPUT_TIMER7_BRKIN2          = ((uint8_t)0x2AU),               /*!< output target peripheral TIMER7_BRKIN2 */
    TRIGSEL_OUTPUT_TIMER14_BRKIN0         = ((uint8_t)0x2CU),               /*!< output target peripheral TIMER14_BRKIN0 */
    TRIGSEL_OUTPUT_TIMER15_BRKIN0         = ((uint8_t)0x30U),               /*!< output target peripheral TIMER15_BRKIN0 */
    TRIGSEL_OUTPUT_TIMER16_BRKIN0         = ((uint8_t)0x34U),               /*!< output target peripheral TIMER16_BRKIN0 */
    TRIGSEL_OUTPUT_TIMER40_BRKIN0         = ((uint8_t)0x38U),               /*!< output target peripheral TIMER40_BRKIN0 */
    TRIGSEL_OUTPUT_TIMER41_BRKIN0         = ((uint8_t)0x3CU),               /*!< output target peripheral TIMER41_BRKIN0 */
    TRIGSEL_OUTPUT_TIMER42_BRKIN0         = ((uint8_t)0x40U),               /*!< output target peripheral TIMER42_BRKIN0 */
    TRIGSEL_OUTPUT_TIMER43_BRKIN0         = ((uint8_t)0x44U),               /*!< output target peripheral TIMER43_BRKIN0 */
    TRIGSEL_OUTPUT_TIMER44_BRKIN0         = ((uint8_t)0x48U),               /*!< output target peripheral TIMER44_BRKIN0 */
    TRIGSEL_OUTPUT_CAN0_EX_TIME_TICK      = ((uint8_t)0x4CU),               /*!< output target peripheral CAN0_EX_TIME_TICK */
    TRIGSEL_OUTPUT_CAN1_EX_TIME_TICK      = ((uint8_t)0x50U),               /*!< output target peripheral CAN1_EX_TIME_TICK */
    TRIGSEL_OUTPUT_CAN2_EX_TIME_TICK      = ((uint8_t)0x54U),               /*!< output target peripheral CAN2_EX_TIME_TICK */
    TRIGSEL_OUTPUT_LPDTS_TRG              = ((uint8_t)0x58U),               /*!< output target peripheral LPDTS_TRG */
    TRIGSEL_OUTPUT_TIMER0_ETI             = ((uint8_t)0x5CU),               /*!< output target peripheral TIMER0_ETI */
    TRIGSEL_OUTPUT_TIMER1_ETI             = ((uint8_t)0x60U),               /*!< output target peripheral TIMER1_ETI */
    TRIGSEL_OUTPUT_TIMER2_ETI             = ((uint8_t)0x64U),               /*!< output target peripheral TIMER2_ETI */
    TRIGSEL_OUTPUT_TIMER3_ETI             = ((uint8_t)0x68U),               /*!< output target peripheral TIMER3_ETI */
    TRIGSEL_OUTPUT_TIMER4_ETI             = ((uint8_t)0x6CU),               /*!< output target peripheral TIMER4_ETI */
    TRIGSEL_OUTPUT_TIMER7_ETI             = ((uint8_t)0x70U),               /*!< output target peripheral TIMER7_ETI */
    TRIGSEL_OUTPUT_TIMER22_ETI            = ((uint8_t)0x74U),               /*!< output target peripheral TIMER22_ETI */
    TRIGSEL_OUTPUT_TIMER23_ETI            = ((uint8_t)0x78U),               /*!< output target peripheral TIMER23_ETI */
    TRIGSEL_OUTPUT_TIMER30_ETI            = ((uint8_t)0x7CU),               /*!< output target peripheral TIMER30_ETI */
    TRIGSEL_OUTPUT_TIMER31_ETI            = ((uint8_t)0x80U),               /*!< output target peripheral TIMER31_ETI */
    TRIGSEL_OUTPUT_EDOUT_TRG              = ((uint8_t)0x84U),               /*!< output target peripheral EDOUT_TRG */
    TRIGSEL_OUTPUT_HPDF_ITR               = ((uint8_t)0x88U),               /*!< output target peripheral HPDF_ITR */
    TRIGSEL_OUTPUT_TIMER0_ITI14           = ((uint8_t)0x8CU),               /*!< output target peripheral TIMER0_ITI14 */
    TRIGSEL_OUTPUT_TIMER1_ITI14           = ((uint8_t)0x90U),               /*!< output target peripheral TIMER1_ITI14 */
    TRIGSEL_OUTPUT_TIMER2_ITI14           = ((uint8_t)0x94U),               /*!< output target peripheral TIMER2_ITI14 */
    TRIGSEL_OUTPUT_TIMER3_ITI14           = ((uint8_t)0x98U),               /*!< output target peripheral TIMER3_ITI14 */
    TRIGSEL_OUTPUT_TIMER4_ITI14           = ((uint8_t)0x9CU),               /*!< output target peripheral TIMER4_ITI14 */
    TRIGSEL_OUTPUT_TIMER7_ITI14           = ((uint8_t)0xA0U),               /*!< output target peripheral TIMER7_ITI14 */
    TRIGSEL_OUTPUT_TIMER14_ITI14          = ((uint8_t)0xA4U),               /*!< output target peripheral TIMER14_ITI14 */
    TRIGSEL_OUTPUT_TIMER22_ITI14          = ((uint8_t)0xA8U),               /*!< output target peripheral TIMER22_ITI14 */
    TRIGSEL_OUTPUT_TIMER23_ITI14          = ((uint8_t)0xACU),               /*!< output target peripheral TIMER23_ITI14 */
    TRIGSEL_OUTPUT_TIMER30_ITI14          = ((uint8_t)0xB0U),               /*!< output target peripheral TIMER30_ITI14 */
    TRIGSEL_OUTPUT_TIMER31_ITI14          = ((uint8_t)0xB4U),               /*!< output target peripheral TIMER31_ITI14 */
    TRIGSEL_OUTPUT_TIMER40_ITI14          = ((uint8_t)0xB8U),               /*!< output target peripheral TIMER40_ITI14 */
    TRIGSEL_OUTPUT_TIMER41_ITI14          = ((uint8_t)0xBCU),               /*!< output target peripheral TIMER41_ITI14 */
    TRIGSEL_OUTPUT_TIMER42_ITI14          = ((uint8_t)0xC0U),               /*!< output target peripheral TIMER42_ITI14 */
    TRIGSEL_OUTPUT_TIMER43_ITI14          = ((uint8_t)0xC4U),               /*!< output target peripheral TIMER43_ITI14 */
    TRIGSEL_OUTPUT_TIMER44_ITI14          = ((uint8_t)0xC8U),               /*!< output target peripheral TIMER44_ITI14 */
}trigsel_periph_enum;

/* function declarations */
/* deinitialize TRIGSEL */
void trigsel_deinit(void);
/* set the trigger input signal for target peripheral */
void trigsel_init(trigsel_periph_enum target_periph, trigsel_source_enum trigger_source);
/* get the trigger input signal for target peripheral */
trigsel_source_enum trigsel_trigger_source_get(trigsel_periph_enum target_periph);
/* lock the trigger register */
void trigsel_register_lock_set(trigsel_periph_enum target_periph);
/* get the trigger register lock status */
FlagStatus trigsel_register_lock_get(trigsel_periph_enum target_periph);

#endif /* GD32H7XX_TRIGSEL_H */
