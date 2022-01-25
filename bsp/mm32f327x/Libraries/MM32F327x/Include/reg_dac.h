////////////////////////////////////////////////////////////////////////////////
/// @file     reg_dac.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE SERIES OF
///           MM32 FIRMWARE LIBRARY.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion

#ifndef __REG_DAC_H
#define __REG_DAC_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif








////////////////////////////////////////////////////////////////////////////////
/// @brief DAC Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define DAC_BASE                        (APB1PERIPH_BASE + 0x7400)              ///< Base Address: 0x40007400



////////////////////////////////////////////////////////////////////////////////
/// @brief Digital to analog converter register
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 CR;                                                                ///<  DAC control register,                         offset: 0x00
    __IO u32 SWTRIGR;                                                           ///<  DAC software trigger register,                offset: 0x04
    __IO u32 DHR12R1;                                                           ///<  Channel 1 12-bit right align data register,   offset: 0x08
    __IO u32 DHR12L1;                                                           ///<  Channel 1 12-bit left align data register,    offset: 0x0C
    __IO u32 DHR8R1;                                                            ///<  Channel 1 8-bit right align data register,    offset: 0x10
    __IO u32 DHR12R2;                                                           ///<  Channel 2 12-bit right align data register,   offset: 0x14
    __IO u32 DHR12L2;                                                           ///<  Channel 2 12-bit left align data register,    offset: 0x18
    __IO u32 DHR8R2;                                                            ///<  Channel 2 8-bit right align data register,    offset: 0x1C
    __IO u32 DHR12RD;                                                           ///<  Dual channel 12-bit right align data register,offset: 0x20
    __IO u32 DHR12LD;                                                           ///<  Dual channel 12-bit left align data register, offset: 0x24
    __IO u32 DHR8RD;                                                            ///<  Dual channel 8-bit right align data register, offset: 0x28
    __IO u32 DOR1;                                                              ///<  Channel 1 output register,                    offset: 0x2C
    __IO u32 DOR2;                                                              ///<  Channel 2 output register,                    offset: 0x30
} DAC_TypeDef;



////////////////////////////////////////////////////////////////////////////////
/// @brief DAC type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define DAC                         ((DAC_TypeDef*) DAC_BASE)



////////////////////////////////////////////////////////////////////////////////
/// @brief DAC_CR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define DAC_CR_EN1_Pos              (0)
#define DAC_CR_EN1                  (0x01U << DAC_CR_EN1_Pos)               ///< DAC channel1 enable
#define DAC_CR_BOFF1_Pos            (1)
#define DAC_CR_BOFF1                (0x01U << DAC_CR_BOFF1_Pos)             ///< DAC channel1 output buffer disable
#define DAC_CR_TEN1_Pos             (2)
#define DAC_CR_TEN1                 (0x01U << DAC_CR_TEN1_Pos)              ///< DAC channel1 Trigger enable
#define DAC_CR_TSEL1_Pos            (3)
#define DAC_CR_TSEL1                (0x07U << DAC_CR_TSEL1_Pos)             ///< TSEL1[2:0] (DAC channel1 Trigger selection)
#define DAC_CR_TSEL1_TIM1_TRIG      (0x00U << DAC_CR_TSEL1_Pos)             ///< TIM1_TRIG trigger
#define DAC_CR_TSEL1_TIM3_TRIG      (0x01U << DAC_CR_TSEL1_Pos)             ///< TIM3_TRIG trigger
#define DAC_CR_TSEL1_TIM2_TRIG      (0x04U << DAC_CR_TSEL1_Pos)             ///< TIM2_TRIG trigger
#define DAC_CR_TSEL1_TIM4_TRIG      (0x05U << DAC_CR_TSEL1_Pos)             ///< TIM4_TRIG trigger
#define DAC_CR_TSEL1_EXTI9          (0x06U << DAC_CR_TSEL1_Pos)             ///< External interrupt line 9 trigger
#define DAC_CR_TSEL1_SOFTWARE       (0x07U << DAC_CR_TSEL1_Pos)             ///< Software trigger
#define DAC_CR_WAVE1_Pos            (6)
#define DAC_CR_WAVE1                (0x03U << DAC_CR_WAVE1_Pos)             ///< WAVE1[1:0] (DAC channel1 noise/triangle wave generation enable)
#define DAC_CR_WAVE1_NONE           (0x00U << DAC_CR_WAVE1_Pos)             ///< Turn off waveform generation
#define DAC_CR_WAVE1_NOISE          (0x01U << DAC_CR_WAVE1_Pos)             ///< Noise waveform generation
#define DAC_CR_WAVE1_TRIANGLE       (0x02U << DAC_CR_WAVE1_Pos)             ///< Triangle wave generation
#define DAC_CR_MAMP1_Pos            (8)
#define DAC_CR_MAMP1                (0x0FU << DAC_CR_MAMP1_Pos)             ///< MAMP1[3:0] (DAC channel1 Mask/Amplitude selector)
#define DAC_CR_MAMP1_1              (0x00U << DAC_CR_MAMP1_Pos)             ///< Triangle wave amplitude equal to 1
#define DAC_CR_MAMP1_3              (0x01U << DAC_CR_MAMP1_Pos)             ///< Triangle wave amplitude equal to 3
#define DAC_CR_MAMP1_7              (0x02U << DAC_CR_MAMP1_Pos)             ///< Triangle wave amplitude equal to 7
#define DAC_CR_MAMP1_15             (0x03U << DAC_CR_MAMP1_Pos)             ///< Triangle wave amplitude equal to 15
#define DAC_CR_MAMP1_31             (0x04U << DAC_CR_MAMP1_Pos)             ///< Triangle wave amplitude equal to 31
#define DAC_CR_MAMP1_63             (0x05U << DAC_CR_MAMP1_Pos)             ///< Triangle wave amplitude equal to 63
#define DAC_CR_MAMP1_127            (0x06U << DAC_CR_MAMP1_Pos)             ///< Triangle wave amplitude equal to 127
#define DAC_CR_MAMP1_255            (0x07U << DAC_CR_MAMP1_Pos)             ///< Triangle wave amplitude equal to 255
#define DAC_CR_MAMP1_511            (0x08U << DAC_CR_MAMP1_Pos)             ///< Triangle wave amplitude equal to 511
#define DAC_CR_MAMP1_1023           (0x09U << DAC_CR_MAMP1_Pos)             ///< Triangle wave amplitude equal to 1023
#define DAC_CR_MAMP1_2047           (0x0AU << DAC_CR_MAMP1_Pos)             ///< Triangle wave amplitude equal to 2047
#define DAC_CR_MAMP1_4095           (0x0BU << DAC_CR_MAMP1_Pos)             ///< Triangle wave amplitude equal to 4095
#define DAC_CR_DMAEN1_Pos           (12)
#define DAC_CR_DMAEN1               (0x01U << DAC_CR_DMAEN1_Pos)            ///< DAC channel1 DMA enable
#define DAC_CR_EN2_Pos              (16)
#define DAC_CR_EN2                  (0x01U << DAC_CR_EN2_Pos)               ///< DAC channel2 enable
#define DAC_CR_BOFF2_Pos            (17)
#define DAC_CR_BOFF2                (0x01U << DAC_CR_BOFF2_Pos)             ///< DAC channel2 output buffer disable
#define DAC_CR_TEN2_Pos             (18)
#define DAC_CR_TEN2                 (0x01U << DAC_CR_TEN2_Pos)              ///< DAC channel2 Trigger enable
#define DAC_CR_TSEL2_Pos            (19)
#define DAC_CR_TSEL2                (0x07U << DAC_CR_TSEL2_Pos)             ///< TSEL1[2:0] (DAC channel1 Trigger selection)
#define DAC_CR_TSEL2_TIM1_TRIG      (0x00U << DAC_CR_TSEL2_Pos)             ///< TIM1_TRIG trigger
#define DAC_CR_TSEL2_TIM3_TRIG      (0x01U << DAC_CR_TSEL2_Pos)             ///< TIM3_TRIG trigger
#define DAC_CR_TSEL2_TIM2_TRIG      (0x04U << DAC_CR_TSEL2_Pos)             ///< TIM2_TRIG trigger
#define DAC_CR_TSEL2_TIM4_TRIG      (0x05U << DAC_CR_TSEL2_Pos)             ///< TIM4_TRIG trigger
#define DAC_CR_TSEL2_EXTI9          (0x06U << DAC_CR_TSEL2_Pos)             ///< External interrupt line 9 trigger
#define DAC_CR_TSEL2_SOFTWARE       (0x07U << DAC_CR_TSEL2_Pos)             ///< Software trigger
#define DAC_CR_WAVE2_Pos            (22)
#define DAC_CR_WAVE2                (0x03U << DAC_CR_WAVE2_Pos)             ///< WAVE1[1:0] (DAC channel1 noise/triangle wave generation enable)
#define DAC_CR_WAVE2_NONE           (0x00U << DAC_CR_WAVE2_Pos)             ///< Turn off waveform generation
#define DAC_CR_WAVE2_NOISE          (0x01U << DAC_CR_WAVE2_Pos)             ///< Noise waveform generation
#define DAC_CR_WAVE2_TRIANGLE       (0x02U << DAC_CR_WAVE2_Pos)             ///< Triangle wave generation
#define DAC_CR_MAMP2_Pos            (24)
#define DAC_CR_MAMP2                (0x0FU << DAC_CR_MAMP2_Pos)             ///< MAMP1[3:0] (DAC channel1 Mask/Amplitude selector)
#define DAC_CR_MAMP2_1              (0x00U << DAC_CR_MAMP2_Pos)             ///< Triangle wave amplitude equal to 1
#define DAC_CR_MAMP2_3              (0x01U << DAC_CR_MAMP2_Pos)             ///< Triangle wave amplitude equal to 3
#define DAC_CR_MAMP2_7              (0x02U << DAC_CR_MAMP2_Pos)             ///< Triangle wave amplitude equal to 7
#define DAC_CR_MAMP2_15             (0x03U << DAC_CR_MAMP2_Pos)             ///< Triangle wave amplitude equal to 15
#define DAC_CR_MAMP2_31             (0x04U << DAC_CR_MAMP2_Pos)             ///< Triangle wave amplitude equal to 31
#define DAC_CR_MAMP2_63             (0x05U << DAC_CR_MAMP2_Pos)             ///< Triangle wave amplitude equal to 63
#define DAC_CR_MAMP2_127            (0x06U << DAC_CR_MAMP2_Pos)             ///< Triangle wave amplitude equal to 127
#define DAC_CR_MAMP2_255            (0x07U << DAC_CR_MAMP2_Pos)             ///< Triangle wave amplitude equal to 255
#define DAC_CR_MAMP2_511            (0x08U << DAC_CR_MAMP2_Pos)             ///< Triangle wave amplitude equal to 511
#define DAC_CR_MAMP2_1023           (0x09U << DAC_CR_MAMP2_Pos)             ///< Triangle wave amplitude equal to 1023
#define DAC_CR_MAMP2_2047           (0x0AU << DAC_CR_MAMP2_Pos)             ///< Triangle wave amplitude equal to 2047
#define DAC_CR_MAMP2_4095           (0x0BU << DAC_CR_MAMP2_Pos)             ///< Triangle wave amplitude equal to 4095
#define DAC_CR_DMAEN2_Pos           (28)
#define DAC_CR_DMAEN2               (0x01U << DAC_CR_DMAEN2_Pos)            ///< DAC channel2 DMA enabled

////////////////////////////////////////////////////////////////////////////////
/// @brief DAC_SWTRIGR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define DAC_SWTRIGR_SWTRIG1_Pos     (0)
#define DAC_SWTRIGR_SWTRIG1         (0x01U << DAC_SWTRIGR_SWTRIG1_Pos)      ///< DAC channel1 software trigger
#define DAC_SWTRIGR_SWTRIG2_Pos     (1)
#define DAC_SWTRIGR_SWTRIG2         (0x01U << DAC_SWTRIGR_SWTRIG2_Pos)      ///< DAC channel2 software trigger
#define DAC_SWTRIGR_DACPRE_Pos      (8)
#define DAC_SWTRIGR_DACPRE          (0x7FU << DAC_SWTRIGR_DACPRE_Pos)       ///< DAC prescale

////////////////////////////////////////////////////////////////////////////////
/// @brief DAC_DHR12R1 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define DAC_DHR12R1_DACC1DHR_Pos    (0)
#define DAC_DHR12R1_DACC1DHR        (0xFFFU << DAC_DHR12R1_DACC1DHR_Pos)    ///< DAC channel1 12-bit Right align data

////////////////////////////////////////////////////////////////////////////////
/// @brief DAC_DHR12L1 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define DAC_DHR12L1_DACC1DHR_Pos    (4)
#define DAC_DHR12L1_DACC1DHR        (0xFFFU << DAC_DHR12L1_DACC1DHR_Pos)    ///< DAC channel1 12-bit Left align data

////////////////////////////////////////////////////////////////////////////////
/// @brief DAC_DHR8R1 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define DAC_DHR8R1_DACC1DHR_Pos     (0)
#define DAC_DHR8R1_DACC1DHR         (0xFFU << DAC_DHR8R1_DACC1DHR_Pos)      ///< DAC channel1 8-bit Right align data

////////////////////////////////////////////////////////////////////////////////
/// @brief DAC_DHR12R2 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define DAC_DHR12R2_DACC2DHR_Pos    (0)
#define DAC_DHR12R2_DACC2DHR        (0xFFFU << DAC_DHR12R2_DACC2DHR_Pos)    ///< DAC channel2 12-bit Right align data

////////////////////////////////////////////////////////////////////////////////
/// @brief DAC_DHR12L2 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define DAC_DHR12L2_DACC2DHR_Pos    (4)
#define DAC_DHR12L2_DACC2DHR        (0xFFFU << DAC_DHR12L2_DACC2DHR_Pos)    ///< DAC channel2 12-bit Left align data

////////////////////////////////////////////////////////////////////////////////
/// @brief DAC_DHR8R2 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define DAC_DHR8R2_DACC2DHR_Pos     (0)
#define DAC_DHR8R2_DACC2DHR         (0xFFU << DAC_DHR8R2_DACC2DHR_Pos)      ///< DAC channel2 8-bit Right align data

////////////////////////////////////////////////////////////////////////////////
/// @brief DAC_DHR12RD Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define DAC_DHR12RD_DACC1DHR_Pos    (0)
#define DAC_DHR12RD_DACC1DHR        (0xFFFU << DAC_DHR12RD_DACC1DHR_Pos)    ///< DAC channel1 12-bit Right align data
#define DAC_DHR12RD_DACC2DHR_Pos    (16)
#define DAC_DHR12RD_DACC2DHR        (0xFFFU << DAC_DHR12RD_DACC2DHR_Pos)    ///< DAC channel2 12-bit Right align data

////////////////////////////////////////////////////////////////////////////////
/// @brief DAC_DHR12LD Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define DAC_DHR12LD_DACC1DHR_Pos    (4)
#define DAC_DHR12LD_DACC1DHR        (0xFFFU << DAC_DHR12LD_DACC1DHR_Pos)    ///< DAC channel1 12-bit Right align data
#define DAC_DHR12LD_DACC2DHR_Pos    (20)
#define DAC_DHR12LD_DACC2DHR        (0xFFFU << DAC_DHR12LD_DACC2DHR_Pos)    ///< DAC channel2 12-bit Right align data

////////////////////////////////////////////////////////////////////////////////
/// @brief DAC_DHR8RD Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define DAC_DHR8RD_DACC1DHR_Pos     (0)
#define DAC_DHR8RD_DACC1DHR         (0xFFU << DAC_DHR8RD_DACC1DHR_Pos)      ///< DAC channel1 8-bit Right align data
#define DAC_DHR8RD_DACC2DHR_Pos     (8)
#define DAC_DHR8RD_DACC2DHR         (0xFFU << DAC_DHR8RD_DACC2DHR_Pos)      ///< DAC channel2 8-bit Right align data

////////////////////////////////////////////////////////////////////////////////
/// @brief DAC_DOR1 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define DAC_DOR1_DACC1DOR_Pos       (0)
#define DAC_DOR1_DACC1DOR           (0xFFFU << DAC_DOR1_DACC1DOR_Pos)       ///< DAC channel1 data output

////////////////////////////////////////////////////////////////////////////////
/// @brief DAC_DOR2 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define DAC_DOR2_DACC2DOR_Pos       (0)
#define DAC_DOR2_DACC2DOR           (0xFFFU << DAC_DOR2_DACC2DOR_Pos)       ///< DAC channel2 data output #endif





/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
