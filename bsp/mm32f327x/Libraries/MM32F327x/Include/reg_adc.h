////////////////////////////////////////////////////////////////////////////////
/// @file     reg_adc.h
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

#ifndef __REG_ADC_H
#define __REG_ADC_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif






////////////////////////////////////////////////////////////////////////////////
/// @brief ADC Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC1_BASE                       (APB2PERIPH_BASE + 0x2400)              ///< Base Address: 0x40012400
#define ADC2_BASE                       (APB2PERIPH_BASE + 0x2800)              ///< Base Address: 0x40012800
#define ADC3_BASE                       (APB2PERIPH_BASE + 0x4C00)              ///< Base Address: 0x40014C00





////////////////////////////////////////////////////////////////////////////////
/// @brief Analog-to-Digital Converter register
////////////////////////////////////////////////////////////////////////////////
#define USENCOMBINEREGISTER
#ifdef USENCOMBINEREGISTER

typedef struct {
    union {
        __IO u32 DR;                                                            ///< ADC data register,                             offset: 0x00
        __IO u32 ADDATA;
    };
    union {
        __IO u32 CFGR;                                                          ///< ADC configuration register,                    offset: 0x04
        __IO u32 ADCFG;
    };
    union {
        __IO u32 CR;                                                            ///< ADC control register,                          offset: 0x08
        __IO u32 ADCR;
    };
    union {
        __IO u32 CHSR;                                                          ///< ADC channel selection register,                offset: 0x0C
        __IO u32 ADCHS;
    };
    union {
        __IO u32 CMPR;                                                          ///< ADC window compare register,                   offset: 0x10
        __IO u32 ADCMPR;
    };
    union {
        __IO u32 SR;                                                            ///< ADC status register,                           offset: 0x14
        __IO u32 ADSTA;
    };
    union {
        __IO u32 CH0DR;                                                         ///< ADC channel0 data register,                    offset: 0x18
        __IO u32 ADDR0;
    };
    union {
        __IO u32 CH1DR;                                                         ///< ADC channel1 data register,                    offset: 0x1C
        __IO u32 ADDR1;
    };
    union {
        __IO u32 CH2DR;                                                         ///< ADC channel2 data register,                    offset: 0x20
        __IO u32 ADDR2;
    };
    union {
        __IO u32 CH3DR;                                                         ///< ADC channel3 data register,                    offset: 0x24
        __IO u32 ADDR3;
    };
    union {
        __IO u32 CH4DR;                                                         ///< ADC channel4 data register,                    offset: 0x28
        __IO u32 ADDR4;
    };
    union {
        __IO u32 CH5DR;                                                         ///< ADC channel5 data register,                    offset: 0x2C
        __IO u32 ADDR5;
    };
    union {
        __IO u32 CH6DR;                                                         ///< ADC channel6 data register,                    offset: 0x30
        __IO u32 ADDR6;
    };
    union {
        __IO u32 CH7DR;                                                         ///< ADC channel7 data register,                    offset: 0x34
        __IO u32 ADDR7;
    };
    union {
        __IO u32 CH8DR;                                                         ///< ADC channel8 data register,                    offset: 0x38
        __IO u32 ADDR8;
    };
    union {
        __IO u32 CH9DR;                                                         ///< ADC channel9 data register,                    offset: 0x3C
        __IO u32 ADDR9;
    };
    __IO u32 ADDR10;                                                            ///<                                                offset: 0x40
    __IO u32 ADDR11;                                                            ///<                                                offset: 0x44
    __IO u32 ADDR12;                                                            ///<                                                offset: 0x48
    __IO u32 ADDR13;                                                            ///<                                                offset: 0x4C
    union {
        __IO u32 CH14DR;                                                        ///< ADC channel14 data register,                   offset: 0x50
        __IO u32 ADDR14;
    };
    union {
        __IO u32 CH15DR;                                                        ///< ADC channel15 data register,                   offset: 0x54
        __IO u32 ADDR15;
    };
    __IO u32 SREXT;                                                             ///< ADC Extended Status Register,                  offset: 0x58
    __IO u32 CHANY0;                                                            ///< ADC any Chan Select Register 0,                offset: 0x5C
    __IO u32 CHANY1;                                                            ///< ADC any Chan Select Register 1,                offset: 0x60
    __IO u32 ANYCFG;                                                            ///< ADC any Chan config Register,                  offset: 0x64
    __IO u32 ANYCR;                                                             ///< ADC any Chan control Register,                 offset: 0x68
    __IO u32 RESERVED0;                                                         ///<                                                offset 0x6C
    __IO u32 SMPR1;                                                             ///< Sampling configuration register 1              offset 0x70
    __IO u32 SMPR2;                                                             ///< Sampling configuration register 2              offset 0x74
    __IO u32 RESERVED1;                                                         ///<                                                offset 0x78
    __IO u32 JOFR0;                                                             ///< Injection channel data compensation register 0 offset 0x7C
    __IO u32 JOFR1;                                                             ///< Injection channel data compensation register 1 offset 0x80
    __IO u32 JOFR2;                                                             ///< Injection channel data compensation register 2 offset 0x84
    __IO u32 JOFR3;                                                             ///< Injection channel data compensation register 3 offset 0x88
    __IO u32 JSQR;                                                              ///< Injection sequence register                    offset 0x8C
    __IO u32 JDATA;                                                             ///< Inject data register                           offset 0x90
    __IO u32 RESERVED2;                                                         ///<                                                offset 0x94
    __IO u32 RESERVED3;                                                         ///<                                                offset 0x98
    __IO u32 RESERVED4;                                                         ///<                                                offset 0x9C
    __IO u32 RESERVED5;                                                         ///<                                                offset 0xA0
    __IO u32 RESERVED6;                                                         ///<                                                offset 0xA4
    __IO u32 RESERVED7;                                                         ///<                                                offset 0xA8
    __IO u32 RESERVED8;                                                         ///<                                                offset 0xAC
    __IO u32 JDR0;                                                              ///< Injection channel data register 0              offset 0xB0
    __IO u32 JDR1;                                                              ///< Injection channel data register 1              offset 0xB4
    __IO u32 JDR2;                                                              ///< Injection channel data register 2              offset 0xB8
    __IO u32 JDR3;                                                              ///< Injection channel data register 3              offset 0xBC
} ADC_TypeDef;

#endif
#ifdef USENNEWREGISTER
////////////////////////////////////////////////////////////////////////////////
/// @brief Analog-to-Digital Converter register
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 DR;                                                                ///< ADC data register,                             offset: 0x00
    __IO u32 CFGR;                                                              ///< ADC configuration register,                    offset: 0x04
    __IO u32 CR;                                                                ///< ADC control register,                          offset: 0x08
    __IO u32 CHSR;                                                              ///< ADC channel selection register,                offset: 0x0C
    __IO u32 CMPR;                                                              ///< ADC window compare register,                   offset: 0x10
    __IO u32 SR;                                                                ///< ADC status register,                           offset: 0x14
    __IO u32 CH0DR;                                                             ///< ADC channel0 data register,                    offset: 0x18
    __IO u32 CH1DR;                                                             ///< ADC channel1 data register,                    offset: 0x1C
    __IO u32 CH2DR;                                                             ///< ADC channel2 data register,                    offset: 0x20
    __IO u32 CH3DR;                                                             ///< ADC channel3 data register,                    offset: 0x24
    __IO u32 CH4DR;                                                             ///< ADC channel4 data register,                    offset: 0x28
    __IO u32 CH5DR;                                                             ///< ADC channel5 data register,                    offset: 0x2C
    __IO u32 CH6DR;                                                             ///< ADC channel6 data register,                    offset: 0x30
    __IO u32 CH7DR;                                                             ///< ADC channel7 data register,                    offset: 0x34
    __IO u32 CH8DR;                                                             ///< ADC channel8 data register,                    offset: 0x38
} ADC_TypeDef;
#endif
#ifdef USENOLDREGISTER
typedef struct {
    __IO u32 ADDATA;                                                            ///< ADC data register,                             offset: 0x00
    __IO u32 ADCFG;                                                             ///< ADC configuration register,                    offset: 0x04
    __IO u32 ADCR;                                                              ///< ADC control register,                          offset: 0x08
    __IO u32 ADCHS;                                                             ///< ADC channel selection register,                offset: 0x0C
    __IO u32 ADCMPR;                                                            ///< ADC window compare register,                   offset: 0x10
    __IO u32 ADSTA;                                                             ///< ADC status register,                           offset: 0x14
    __IO u32 ADDR0;                                                             ///< ADC channel0 data register,                    offset: 0x18
    __IO u32 ADDR1;                                                             ///< ADC channel1 data register,                    offset: 0x1C
    __IO u32 ADDR2;                                                             ///< ADC channel2 data register,                    offset: 0x20
    __IO u32 ADDR3;                                                             ///< ADC channel3 data register,                    offset: 0x24
    __IO u32 ADDR4;                                                             ///< ADC channel4 data register,                    offset: 0x28
    __IO u32 ADDR5;                                                             ///< ADC channel5 data register,                    offset: 0x2C
    __IO u32 ADDR6;                                                             ///< ADC channel6 data register,                    offset: 0x30
    __IO u32 ADDR7;                                                             ///< ADC channel7 data register,                    offset: 0x34
    __IO u32 ADDR8;                                                             ///< ADC channel8 data register,                    offset: 0x38
} ADC_TypeDef;
#endif



////////////////////////////////////////////////////////////////////////////////
/// @brief ADC type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC1                            ((ADC_TypeDef*) ADC1_BASE)
#define ADC2                            ((ADC_TypeDef*) ADC2_BASE)
#define ADC3                            ((ADC_TypeDef*) ADC3_BASE)


////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_DR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_DR_DATA_Pos                (0)
#define ADC_DR_DATA                    (0xFFFFU << ADC_DR_DATA_Pos)            ///< ADC 12bit convert data

#define ADC_DR_CH_Pos                  (16)
#define ADC_DR_CH                      (0x0FU <<  ADC_DR_CH_Pos)               ///< CHANNELSEL[19:16] (ADC current channel convert data)

#define ADC_DR_CH0                     (0x00U << ADC_DR_CH_Pos)                ///< ADC Channel select  0
#define ADC_DR_CH1                     (0x01U << ADC_DR_CH_Pos)                ///< ADC Channel select  1
#define ADC_DR_CH2                     (0x02U << ADC_DR_CH_Pos)                ///< ADC Channel select  2
#define ADC_DR_CH3                     (0x03U << ADC_DR_CH_Pos)                ///< ADC Channel select  3
#define ADC_DR_CH4                     (0x04U << ADC_DR_CH_Pos)                ///< ADC Channel select  4
#define ADC_DR_CH5                     (0x05U << ADC_DR_CH_Pos)                ///< ADC Channel select  5
#define ADC_DR_CH6                     (0x06U << ADC_DR_CH_Pos)                ///< ADC Channel select  6
#define ADC_DR_CH7                     (0x07U << ADC_DR_CH_Pos)                ///< ADC Channel select  7

#define ADC_DR_CH8                     (0x08U << ADC_DR_CH_Pos)                ///< ADC Channel select  8

#define ADC_DR_CH10                    (0x0AU << ADC_DR_CH_Pos)                ///< ADC Channel select  10
#define ADC_DR_CH11                    (0x0BU << ADC_DR_CH_Pos)                ///< ADC Channel select  11
#define ADC_DR_CH13                    (0x0CU << ADC_DR_CH_Pos)                ///< ADC Channel select  13

#define ADC_DR_CH9                     (0x09U << ADC_DR_CH_Pos)                ///< ADC Channel select  9
#define ADC_DR_CH14                    (0x0EU << ADC_DR_CH_Pos)                ///< ADC Channel select  14
#define ADC_DR_CH15                    (0x0FU << ADC_DR_CH_Pos)                ///< ADC Channel select  15
#define ADC_DR_OVERRUN_Pos             (20)
#define ADC_DR_OVERRUN                 (0x01U << ADC_DR_OVERRUN_Pos)           ///< ADC data will be cover
#define ADC_DR_VALID_Pos               (21)
#define ADC_DR_VALID                   (0x01U << ADC_DR_VALID_Pos)             ///< ADC data[11:0] is valid

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CFGR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_CFGR_ADEN_Pos              (0)
#define ADC_CFGR_ADEN                  (0x01U << ADC_CFGR_ADEN_Pos)            ///< Enable ADC convert
#define ADC_CFGR_ADWEN_Pos             (1)
#define ADC_CFGR_ADWEN                 (0x01U << ADC_CFGR_ADWEN_Pos)           ///< Enable ADC window compare


#define ADC_CFGR_RSLTCTL_Pos           (7)
#define ADC_CFGR_RSLTCTL               (0x07U << ADC_CFGR_RSLTCTL_Pos)         ///< ADC resolution select
#define ADC_CFGR_RSLTCTL_12            (0x00U << ADC_CFGR_RSLTCTL_Pos)         ///< ADC resolution select 12bit
#define ADC_CFGR_RSLTCTL_11            (0x01U << ADC_CFGR_RSLTCTL_Pos)         ///< ADC resolution select 11bit
#define ADC_CFGR_RSLTCTL_10            (0x02U << ADC_CFGR_RSLTCTL_Pos)         ///< ADC resolution select 10bit
#define ADC_CFGR_RSLTCTL_9             (0x03U << ADC_CFGR_RSLTCTL_Pos)         ///< ADC resolution select 9bit
#define ADC_CFGR_RSLTCTL_8             (0x04U << ADC_CFGR_RSLTCTL_Pos)         ///< ADC resolution select 8bit

#define ADC_CFGR_TEN_Pos               (2)
#define ADC_CFGR_TEN                   (0x01U << ADC_CFGR_TEN_Pos)                 ///< Enable ADC temperature sensor
#define ADC_CFGR_VEN_Pos               (3)
#define ADC_CFGR_VEN                   (0x01U << ADC_CFGR_VEN_Pos)                 ///< Enable ADC voltage reference





#define ADC_CFGR_PRE_Pos                (4)
#define ADC_CFGR_PREL_Pos               (14)
#define ADC_CFGR_PRE                    ((0x07U << ADC_CFGR_PRE_Pos) + (0x01U << ADC_CFGR_PREL_Pos))
#define ADC_CFGR_PRE_2                  (0x00U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 2
#define ADC_CFGR_PRE_4                  (0x01U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 4
#define ADC_CFGR_PRE_6                  (0x02U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 6
#define ADC_CFGR_PRE_8                  (0x03U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 8
#define ADC_CFGR_PRE_10                 (0x04U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 10
#define ADC_CFGR_PRE_12                 (0x05U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 12
#define ADC_CFGR_PRE_14                 (0x06U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 14
#define ADC_CFGR_PRE_16                 (0x07U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 16
#define ADC_CFGR_PRE_3                  ((0x01U << ADC_CFGR_PREL_Pos) + (0x00U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 3
#define ADC_CFGR_PRE_5                  ((0x01U << ADC_CFGR_PREL_Pos) + (0x01U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 5
#define ADC_CFGR_PRE_7                  ((0x01U << ADC_CFGR_PREL_Pos) + (0x02U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 7
#define ADC_CFGR_PRE_9                  ((0x01U << ADC_CFGR_PREL_Pos) + (0x03U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 9
#define ADC_CFGR_PRE_11                 ((0x01U << ADC_CFGR_PREL_Pos) + (0x04U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 11
#define ADC_CFGR_PRE_13                 ((0x01U << ADC_CFGR_PREL_Pos) + (0x05U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 13
#define ADC_CFGR_PRE_15                 ((0x01U << ADC_CFGR_PREL_Pos) + (0x06U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 15
#define ADC_CFGR_PRE_17                 ((0x01U << ADC_CFGR_PREL_Pos) + (0x07U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 17

#define ADC_CFGR_JADWEN_Pos             (16)
#define ADC_CFGR_JADWEN                 (0x01U << ADC_CFGR_JADWEN_Pos)              ///< Inject ADC conversion window comparison enable




////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_CR_ADIE_Pos                (0)
#define ADC_CR_ADIE                    (0x01U << ADC_CR_ADIE_Pos)              ///< ADC interrupt enable
#define ADC_CR_ADWIE_Pos               (1)
#define ADC_CR_ADWIE                   (0x01U << ADC_CR_ADWIE_Pos)             ///< ADC window compare interrupt enable
#define ADC_CR_TRGEN_Pos               (2)
#define ADC_CR_TRGEN                   (0x01U << ADC_CR_TRGEN_Pos)             ///< extranal trigger single start AD convert
#define ADC_CR_DMAEN_Pos               (3)
#define ADC_CR_DMAEN                   (0x01U << ADC_CR_DMAEN_Pos)             ///< ADC DMA enable

#define ADC_CR_ADST_Pos                (8)
#define ADC_CR_ADST                    (0x01U << ADC_CR_ADST_Pos)              ///< ADC start convert data
#define ADC_CR_MODE_Pos                (9)
#define ADC_CR_MODE                    (0x03U << ADC_CR_MODE_Pos)              ///< ADC convert mode
#define ADC_CR_IMM                     (0x00U << ADC_CR_MODE_Pos)              ///< ADC imm convert mode
#define ADC_CR_SCAN                    (0x01U << ADC_CR_MODE_Pos)              ///< ADC scan convert mode
#define ADC_CR_CONTINUE                (0x02U << ADC_CR_MODE_Pos)              ///< ADC continue scan convert mode
#define ADC_CR_ALIGN_Pos               (11)
#define ADC_CR_ALIGN                   (0x01U << ADC_CR_ALIGN_Pos)             ///< ADC data align
#define ADC_CR_LEFT                    (0x01U << ADC_CR_ALIGN_Pos)             ///< ADC data left align
#define ADC_CR_RIGHT                   (0x00U << ADC_CR_ALIGN_Pos)             ///< ADC data right align
#define ADC_CR_CMPCH_Pos               (12)
#define ADC_CR_CMPCH                   (0x0FU << ADC_CR_CMPCH_Pos)             ///< CMPCH[15:12] ADC window compare channel0 convert data
#define ADC_CR_CMPCH_0                 (0x00U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 0 Conversion Results
#define ADC_CR_CMPCH_1                 (0x01U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 1 Conversion Results
#define ADC_CR_CMPCH_2                 (0x02U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 2 Conversion Results
#define ADC_CR_CMPCH_4                 (0x04U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 4 Conversion Results
#define ADC_CR_CMPCH_5                 (0x05U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 5 Conversion Results
#define ADC_CR_CMPCH_6                 (0x06U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 6 Conversion Results
#define ADC_CR_CMPCH_7                 (0x07U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 7 Conversion Results
#define ADC_CR_CMPCH_8                 (0x08U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 8 Conversion Results
#define ADC_CR_CMPCH_9                 (0x09U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 9 Conversion Results
#define ADC_CR_CMPCH_10                (0x0AU << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 10 Conversion Results
#define ADC_CR_CMPCH_11                (0x0BU << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 11 Conversion Results
#define ADC_CR_CMPCH_13                (0x0DU << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 13 Conversion Results
#define ADC_CR_CMPCH_14                (0x0EU << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 14 Conversion Results
#define ADC_CR_CMPCH_ALL               (0x0FU << ADC_CR_CMPCH_Pos)             ///< Select Compare ALL Channel Conversion Results



#define ADC_CR_SCANDIR_Pos              (16)
#define ADC_CR_SCANDIR                  (0x01U << ADC_CR_SCANDIR_Pos)           ///< ADC scan direction
#define ADC_CR_TRGSEL_H_Pos             (17)
#define ADC_CR_TRGSEL_L_Pos             (4)
#define ADC_CR_TRGSEL                   ((0x03U << ADC_CR_TRGSEL_H_Pos) + (0x07U << ADC_CR_TRGSEL_L_Pos))   ///< TRGSEL[6:4][18:17] ADC external trigger source select
#define ADC_CR_T1_CC1                   (0x00U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is T1_CC1
#define ADC_CR_T1_CC2                   (0x01U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is T1_CC2
#define ADC_CR_T1_CC3                   (0x02U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is T1_CC3
#define ADC_CR_T2_CC2                   (0x03U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is T2_CC2
#define ADC_CR_T3_TRIG                  (0x04U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is T3_TRIG
#define ADC_CR_T1_CC4_CC5               (0x05U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is T1_CC4_CC5
#define ADC_CR_T3_CC1                   (0x06U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is T3_CC1
#define ADC_CR_EXTI_11                  (0x07U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is EXTI_11
#define ADC_CR_T1_TRIG                  ((0x01U << ADC_CR_TRGSEL_H_Pos) + (0x00U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is T1_TRIG
#define ADC_CR_T8_CC4               ((0x01U << ADC_CR_TRGSEL_H_Pos) + (0x01U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is T8_CC4
#define ADC_CR_T8_CC4_CC5           ((0x01U << ADC_CR_TRGSEL_H_Pos) + (0x02U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is T8_CC4_CC5
#define ADC_CR_T2_CC1                   ((0x01U << ADC_CR_TRGSEL_H_Pos) + (0x03U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is T2_CC1
#define ADC_CR_T3_CC4                   ((0x01U << ADC_CR_TRGSEL_H_Pos) + (0x04U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is T3_CC4
#define ADC_CR_T2_TRIG                  ((0x01U << ADC_CR_TRGSEL_H_Pos) + (0x05U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is T2_TRIG
#define ADC_CR_T8_CC5                   ((0x01U << ADC_CR_TRGSEL_H_Pos) + (0x06U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is T8_CC5
#define ADC_CR_EXTI_15                  ((0x01U << ADC_CR_TRGSEL_H_Pos) + (0x07U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is EXTI_15
#define ADC_CR_TIM1_CC4                 ((0x02U << ADC_CR_TRGSEL_H_Pos) + (0x00U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is TIM1_CC4
#define ADC_CR_TIM1_CC5                 ((0x02U << ADC_CR_TRGSEL_H_Pos) + (0x01U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is TIM1_CC5

#define ADC_CR_TRGSHIFT_Pos             (19)
#define ADC_CR_TRGSHIFT                 (0x07U << ADC_CR_TRGSHIFT_Pos)          ///< External trigger shift sample
#define ADC_CR_TRGSHIFT_0               (0x00U << ADC_CR_TRGSHIFT_Pos)          ///< No shift
#define ADC_CR_TRGSHIFT_4               (0x01U << ADC_CR_TRGSHIFT_Pos)          ///< Shift 4 period
#define ADC_CR_TRGSHIFT_16              (0x02U << ADC_CR_TRGSHIFT_Pos)          ///< Shift 16 period
#define ADC_CR_TRGSHIFT_32              (0x03U << ADC_CR_TRGSHIFT_Pos)          ///< Shift 32 period
#define ADC_CR_TRGSHIFT_64              (0x04U << ADC_CR_TRGSHIFT_Pos)          ///< Shift 64 period
#define ADC_CR_TRGSHIFT_128             (0x05U << ADC_CR_TRGSHIFT_Pos)          ///< Shift 128 period
#define ADC_CR_TRGSHIFT_256             (0x06U << ADC_CR_TRGSHIFT_Pos)          ///< Shift 256 period
#define ADC_CR_TRGSHIFT_512             (0x07U << ADC_CR_TRGSHIFT_Pos)          ///< Shift 512 period
#define ADC_CR_CALIBEN_Pos              (22)
#define ADC_CR_CALIBEN                  (0x01U << ADC_CR_CALIBEN_Pos)           ///< Self-calibration enable
#define ADC_CR_CALIBSEL_Pos             (23)
#define ADC_CR_CALIBSEL                 (0x01U << ADC_CR_CALIBSEL_Pos)          ///< Self-calibration voltage selection
#define ADC_CR_TRG_EDGE_Pos            (24)
#define ADC_CR_TRG_EDGE                (0x03U << ADC_CR_TRG_EDGE_Pos)          ///< ADC trig edge config
#define ADC_CR_TRG_EDGE_DUAL           (0x00U << ADC_CR_TRG_EDGE_Pos)          ///< ADC dual edge trig mode
#define ADC_CR_TRG_EDGE_DOWN           (0x01U << ADC_CR_TRG_EDGE_Pos)          ///< ADC down edge trig mode
#define ADC_CR_TRG_EDGE_UP             (0x02U << ADC_CR_TRG_EDGE_Pos)          ///< ADC up   edge trig mode
#define ADC_CR_TRG_EDGE_MASK           (0x03U << ADC_CR_TRG_EDGE_Pos)          ///< ADC mask edge trig mode

#define ADC_CR_EOSMPIE_Pos              (26)
#define ADC_CR_EOSMPIE                  (0X01U << ADC_CR_EOSMPIE_Pos)            ///< ADC end sampling flag interrupt enable
#define ADC_CR_EOCIE_Pos                (27)
#define ADC_CR_EOCIE                    (0X01U << ADC_CR_EOCIE_Pos)            ///< ADC end of conversion interrupt enable
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CHSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_CHSR_CH0_Pos               (0)
#define ADC_CHSR_CH0                   (0x01U << ADC_CHSR_CH0_Pos)             ///< Enable ADC channel 0
#define ADC_CHSR_CH1_Pos               (1)
#define ADC_CHSR_CH1                   (0x01U << ADC_CHSR_CH1_Pos)             ///< Enable ADC channel 1
#define ADC_CHSR_CH2_Pos               (2)
#define ADC_CHSR_CH2                   (0x01U << ADC_CHSR_CH2_Pos)             ///< Enable ADC channel 2
#define ADC_CHSR_CH3_Pos               (3)
#define ADC_CHSR_CH3                   (0x01U << ADC_CHSR_CH3_Pos)             ///< Enable ADC channel 3
#define ADC_CHSR_CH4_Pos               (4)
#define ADC_CHSR_CH4                   (0x01U << ADC_CHSR_CH4_Pos)             ///< Enable ADC channel 4
#define ADC_CHSR_CH5_Pos               (5)
#define ADC_CHSR_CH5                   (0x01U << ADC_CHSR_CH5_Pos)             ///< Enable ADC channel 5
#define ADC_CHSR_CH6_Pos               (6)
#define ADC_CHSR_CH6                   (0x01U << ADC_CHSR_CH6_Pos)             ///< Enable ADC channel 6
#define ADC_CHSR_CH7_Pos               (7)
#define ADC_CHSR_CH7                   (0x01U << ADC_CHSR_CH7_Pos)             ///< Enable ADC channel 7

#define ADC_CHSR_CH8_Pos               (8)
#define ADC_CHSR_CH8                   (0x01U << ADC_CHSR_CH8_Pos)             ///< Enable ADC channel 8
#define ADC_CHSR_CH9_Pos               (9)
#define ADC_CHSR_CH9                   (0x01U << ADC_CHSR_CH9_Pos)             ///< Enable ADC channel 9
#define ADC_CHSR_CHT_Pos               (14)
#define ADC_CHSR_CHT                   (0x01U << ADC_CHSR_CHT_Pos)             ///< Enable Temperature Sensor
#define ADC_CHSR_CHV_Pos               (15)
#define ADC_CHSR_CHV                   (0x01U << ADC_CHSR_CHV_Pos)             ///< Enable Voltage Sensor


#define ADC_CHSR_CH10_Pos              (10)
#define ADC_CHSR_CH10                  (0x01U << ADC_CHSR_CH10_Pos)            ///< Enable ADC channel 10
#define ADC_CHSR_CH11_Pos              (11)
#define ADC_CHSR_CH11                  (0x01U << ADC_CHSR_CH11_Pos)            ///< Enable ADC channel 11
#define ADC_CHSR_CH12_Pos              (12)
#define ADC_CHSR_CH12                  (0x01U << ADC_CHSR_CH12_Pos)            ///< Enable ADC channel 12
#define ADC_CHSR_CH13_Pos              (13)
#define ADC_CHSR_CH13                  (0x01U << ADC_CHSR_CH13_Pos)            ///< Enable ADC channel 13
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CMPR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_CMPR_CMPLDATA_Pos          (0)
#define ADC_CMPR_CMPLDATA              (0x0FFFU << ADC_CMPR_CMPLDATA_Pos)      ///< ADC 12bit window compare DOWN LEVEL DATA
#define ADC_CMPR_CMPHDATA_Pos          (16)
#define ADC_CMPR_CMPHDATA              (0x0FFFU << ADC_CMPR_CMPHDATA_Pos)      ///< ADC 12bit window compare UP LEVEL DATA

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_SR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_SR_ADIF_Pos                (0)
#define ADC_SR_ADIF                    (0x01U << ADC_SR_ADIF_Pos)              ///< ADC convert complete flag
#define ADC_SR_ADWIF_Pos               (1)
#define ADC_SR_ADWIF                   (0x01U << ADC_SR_ADWIF_Pos)             ///< ADC compare flag
#define ADC_SR_BUSY_Pos                (2)
#define ADC_SR_BUSY                    (0x01U << ADC_SR_BUSY_Pos)              ///< ADC busy flag
#define ADC_SR_CH_Pos                  (4)
#define ADC_SR_CH                      (0x0FU << ADC_SR_CH_Pos)                ///< CHANNEL[7:4] ADC current channel
#define ADC_SR_CH0                     (0x00U << ADC_SR_CH_Pos)                ///< Channel 0 is the current conversion channel
#define ADC_SR_CH1                     (0x01U << ADC_SR_CH_Pos)                ///< Channel 1 is the current conversion channel
#define ADC_SR_CH2                     (0x02U << ADC_SR_CH_Pos)                ///< Channel 2 is the current conversion channel
#define ADC_SR_CH3                     (0x03U << ADC_SR_CH_Pos)                ///< Channel 3 is the current conversion channel
#define ADC_SR_CH4                     (0x04U << ADC_SR_CH_Pos)                ///< Channel 4 is the current conversion channel
#define ADC_SR_CH5                     (0x05U << ADC_SR_CH_Pos)                ///< Channel 5 is the current conversion channel
#define ADC_SR_CH6                     (0x06U << ADC_SR_CH_Pos)                ///< Channel 6 is the current conversion channel
#define ADC_SR_CH7                     (0x07U << ADC_SR_CH_Pos)                ///< Channel 7 is the current conversion channel
#define ADC_SR_CH8                     (0x08U << ADC_SR_CH_Pos)                ///< Channel 8 is the current conversion channel
#define ADC_SR_CH9                     (0x09U << ADC_SR_CH_Pos)                ///< Channel 9 is the current conversion channel
#define ADC_SR_CH10                    (0x0AU << ADC_SR_CH_Pos)                ///< Channel 10 is the current conversion channel
#define ADC_SR_CH11                    (0x0BU << ADC_SR_CH_Pos)                ///< Channel 11 is the current conversion channel
#define ADC_SR_CH13                    (0x0DU << ADC_SR_CH_Pos)                ///< Channel 13 is the current conversion channel
#define ADC_SR_CH14                    (0x0EU << ADC_SR_CH_Pos)                ///< Channel 14 is the current conversion channel
#define ADC_SR_CH15                    (0x0FU << ADC_SR_CH_Pos)                ///< Channel 15 is the current conversion channel


#define ADC_SR_VALID_Pos               (8)
#define ADC_SR_VALID                   (0x0FFFU << ADC_SR_VALID_Pos)           ///< VALID[19:8] ADC channel 0..11 valid flag
#define ADC_SR_OVERRUN_Pos             (20)
#define ADC_SR_OVERRUN                 (0x0FFFU << ADC_SR_OVERRUN_Pos)         ///< OVERRUN[31:20] ADC channel 0..11 data covered flag

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CHnDR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_CHDR_DATA_Pos          (0)
#define ADC_CHDR_DATA              (0xFFFFU << ADC_CHDR_DATA_Pos)          ///< ADC channel convert data
#define ADC_CHDR_OVERRUN_Pos       (20)
#define ADC_CHDR_OVERRUN           (0x01U << ADC_CHDR_OVERRUN_Pos)         ///< ADC data covered flag
#define ADC_CHDR_VALID_Pos         (21)
#define ADC_CHDR_VALID             (0x01U << ADC_CHDR_VALID_Pos)           ///< ADC data valid flag

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_SREXT Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_SREXT_VALID_Pos             (0)
#define ADC_SREXT_VALID                 (0x0FU << ADC_SREXT_VALID_Pos)          ///< VALID[3:0] ADC channel 12,14..15 valid flag
#define ADC_SREXT_OVERRUN_Pos           (4)
#define ADC_SREXT_OVERRUN               (0x0FU << ADC_SREXT_OVERRUN_Pos)        ///< OVERRUN[7:4] ADC channel 12,14..15 data covered flag


#define ADC_SREXT_EOSMPIF_Pos       (16)
#define ADC_SREXT_EOSMPIF           (0x01U << ADC_SREXT_EOSMPIF_Pos)       ///< End of sampling interrupt flag
#define ADC_SREXT_EOCIF_Pos         (17)
#define ADC_SREXT_EOCIF             (0x01U << ADC_SREXT_EOCIF_Pos)         ///< End of conversion interrupt flag
#define ADC_SREXT_JEOSMPIF_Pos      (18)
#define ADC_SREXT_JEOSMPIF          (0x01U << ADC_SREXT_JEOSMPIF_Pos)      /// Injected channel end of sampling interrupt flag
#define ADC_SREXT_JEOCIF_Pos        (19)
#define ADC_SREXT_JEOCIF            (0x03U << ADC_SREXT_JEOCIF_Pos)        ///< Injected channel end of conversion interrupt flag
#define ADC_SREXT_JEOSIF_Pos        (20)
#define ADC_SREXT_JEOSIF            (0x03U << ADC_SREXT_JEOSIF_Pos)        ///< Injected channel end of sequential conversion interrupt flag
#define ADC_SREXT_JBUSY_Pos         (21)
#define ADC_SREXT_JBUSY             (0x01U << ADC_SREXT_JBUSY_Pos)         ///< Injection mode busy/idle

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CHANY0 select Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC1_CHANY0_SEL0_Pos            (0)                                     ///< CHANY_SEL0 (Bit 0)
#define ADC1_CHANY0_SEL0                (0x0FU << ADC1_CHANY0_SEL0_Pos)         ///< CHANY_SEL0 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY0_SEL1_Pos            (4)                                     ///< CHANY_SEL1 (Bit 4)
#define ADC1_CHANY0_SEL1                (0x0FU << ADC1_CHANY0_SEL1_Pos)         ///< CHANY_SEL1 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY0_SEL2_Pos            (8)                                     ///< CHANY_SEL2 (Bit 8)
#define ADC1_CHANY0_SEL2                (0x0FU << ADC1_CHANY0_SEL2_Pos)         ///< CHANY_SEL2 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY0_SEL3_Pos            (12)                                    ///< CHANY_SEL3 (Bit 12)
#define ADC1_CHANY0_SEL3                (0x0FU << ADC1_CHANY0_SEL3_Pos)         ///< CHANY_SEL3 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY0_SEL4_Pos            (16)                                    ///< CHANY_SEL4 (Bit 16)
#define ADC1_CHANY0_SEL4                (0x0FU << ADC1_CHANY0_SEL4_Pos)         ///< CHANY_SEL4 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY0_SEL5_Pos            (20)                                    ///< CHANY_SEL5 (Bit 20)
#define ADC1_CHANY0_SEL5                (0x0FU << ADC1_CHANY0_SEL5_Pos)         ///< CHANY_SEL5 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY0_SEL6_Pos            (24)                                    ///< CHANY_SEL6 (Bit 24)
#define ADC1_CHANY0_SEL6                (0x0FU << ADC1_CHANY0_SEL6_Pos)         ///< CHANY_SEL6 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY0_SEL7_Pos            (28)                                    ///< CHANY_SEL7 (Bit 28)
#define ADC1_CHANY0_SEL7                (0x0FU << ADC1_CHANY0_SEL7_Pos)         ///< CHANY_SEL7 (Bitfield-Mask: 0x0f)

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CHANY1 select Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC1_CHANY1_SEL8_Pos            (0)                                     ///< CHANY_SEL8 (Bit 0)
#define ADC1_CHANY1_SEL8                (0x0FU << ADC1_CHANY1_SEL8_Pos)         ///< CHANY_SEL8 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY1_SEL9_Pos            (4)                                     ///< CHANY_SEL9 (Bit 4)
#define ADC1_CHANY1_SEL9                (0x0FU << ADC1_CHANY1_SEL9_Pos)         ///< CHANY_SEL9 (Bitfield-Mask: 0x0f)

#define ADC1_CHANY1_SEL14_Pos           (24)                                    ///< CHANY_SEL14 (Bit 24)
#define ADC1_CHANY1_SEL14               (0x0FU << ADC1_CHANY1_SEL14_Pos)        ///< CHANY_SEL14 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY1_SEL15_Pos           (28)                                    ///< CHANY_SEL15 (Bit 28)
#define ADC1_CHANY1_SEL15               (0x0FU << ADC1_CHANY1_SEL15_Pos)        ///< CHANY_SEL15 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY1_SEL10_Pos           (8)                                     ///< CHANY_SEL10 (Bit 8)
#define ADC1_CHANY1_SEL10               (0x0FU << ADC1_CHANY1_SEL10_Pos)        ///< CHANY_SEL10 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY1_SEL11_Pos           (12)                                    ///< CHANY_SEL11 (Bit 12)
#define ADC1_CHANY1_SEL11               (0x0FU << ADC1_CHANY1_SEL11_Pos)        ///< CHANY_SEL11 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY1_SEL12_Pos           (16)                                    ///< CHANY_SEL12 (Bit 16)
#define ADC1_CHANY1_SEL12               (0x0FU << ADC1_CHANY1_SEL12_Pos)        ///< CHANY_SEL12 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY1_SEL13_Pos           (20)                                    ///< CHANY_SEL13 (Bit 20)
#define ADC1_CHANY1_SEL13               (0x0FU << ADC1_CHANY1_SEL13_Pos)        ///< CHANY_SEL13 (Bitfield-Mask: 0x0f)
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CHANY config number Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC1_CHANY_CFG_NUM_Max          (16)                                    ///< CHANY_CFG_NUM Max Value is 16

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CHANY mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC1_CHANY_CR_MDEN_Pos          (0)                                     ///< CHANY_MDEN (Bit 0)
#define ADC1_CHANY_CR_MDEN              (0x01U << ADC1_CHANY_CR_MDEN_Pos)       ///< CHANY_MDEN (Bitfield-Mask: 0x01)


////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_ANY_CR mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_ANY_CR_JTRGEDGE_Pos         (16)                                    ///< Injection mode triggers edge selection
#define ADC_ANY_CR_JTRGEDGE_R_F         (0x00U << ADC_ANY_CR_JTRGEDGE_Pos)      ///< Triggered along both rising and falling edges
#define ADC_ANY_CR_JTRGEDGE_F           (0x01U << ADC_ANY_CR_JTRGEDGE_Pos)      ///< Drop edge trigger
#define ADC_ANY_CR_JTRGEDGE_R           (0x02U << ADC_ANY_CR_JTRGEDGE_Pos)      ///< Rising edge trigger
#define ADC_ANY_CR_JTRGEDGE_S           (0x03U << ADC_ANY_CR_JTRGEDGE_Pos)      ///< Shield trigger

#define ADC_ANY_CR_JTRGSHIFT_Pos        (13)                                    ///< Injection mode external trigger delay sampling
#define ADC_ANY_CR_JTRGSHIFT_0          (0x00U << ADC_ANY_CR_JTRGSHIFT_Pos)     ///< 0   cycle
#define ADC_ANY_CR_JTRGSHIFT_4          (0x01U << ADC_ANY_CR_JTRGSHIFT_Pos)     ///< 4   cycle
#define ADC_ANY_CR_JTRGSHIFT_16         (0x02U << ADC_ANY_CR_JTRGSHIFT_Pos)     ///< 16  cycle
#define ADC_ANY_CR_JTRGSHIFT_32         (0x03U << ADC_ANY_CR_JTRGSHIFT_Pos)     ///< 32  cycle
#define ADC_ANY_CR_JTRGSHIFT_64         (0x04U << ADC_ANY_CR_JTRGSHIFT_Pos)     ///< 64  cycle
#define ADC_ANY_CR_JTRGSHIFT_128        (0x05U << ADC_ANY_CR_JTRGSHIFT_Pos)     ///< 128 cycle
#define ADC_ANY_CR_JTRGSHIFT_256        (0x06U << ADC_ANY_CR_JTRGSHIFT_Pos)     ///< 256 cycle
#define ADC_ANY_CR_JTRGSHIFT_512        (0x07U << ADC_ANY_CR_JTRGSHIFT_Pos)     ///< 512 cycle

#define ADC_ANY_CR_JTRGSEL_Pos          (8)                                     ///< External event select for injected group
#define ADC_ANY_CR_JTRGSEL              (0x07U << ADC_ANY_CR_JTRGSEL_Pos)
#define ADC_ANY_CR_JTRGSEL_TIM1_TRGO    (0x00U << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM1 TRGO     
#define ADC_ANY_CR_JTRGSEL_TIM1_CC4     (0x01U << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM1 CC4      
#define ADC_ANY_CR_JTRGSEL_TIM1_CC4_CC5 (0x02U << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM1 CC4 and CC5  
#define ADC_ANY_CR_JTRGSEL_TIM2_TIM4CC1 (0x03U << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM2 CC1 and TIM4 CC1
#define ADC_ANY_CR_JTRGSEL_TIM3_TIM5CC4 (0x04U << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM3 CC4 and TIM5 CC4
#define ADC_ANY_CR_JTRGSEL_TIM8_CC4     (0x05U << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM8 CC4      
#define ADC_ANY_CR_JTRGSEL_TIM8_CC4_CC5 (0x06U << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM8 CC4 and CC5  
#define ADC_ANY_CR_JTRGSEL_EXTI12       (0x07U << ADC_ANY_CR_JTRGSEL_Pos)       ///< EXTI12        

#define ADC_ANY_CR_JTRGEN_Pos           (7)
#define ADC_ANY_CR_JTRGEN               (0x01U << ADC_ANY_CR_JTRGEN_Pos)        ///< External trigger conversion mode for injected channels
#define ADC_ANY_CR_JADST_Pos            (6)
#define ADC_ANY_CR_JADST                (0x01U << ADC_ANY_CR_JADST_Pos)         ///< Start conversion of injected channels
#define ADC_ANY_CR_JAUTO_Pos            (5)
#define ADC_ANY_CR_JAUTO                (0x01U << ADC_ANY_CR_JAUTO_Pos)         ///<Automatic Injected group conversion
#define ADC_ANY_CR_JEOSIE_Pos           (4)
#define ADC_ANY_CR_JEOSIE               (0x01U << ADC_ANY_CR_JEOSIE_Pos)        ///< Interrupt enable the end of sequence conversion for injected channel
#define ADC_ANY_CR_JEOCIE_Pos           (3)
#define ADC_ANY_CR_JEOCIE               (0x01U << ADC_ANY_CR_JEOCIE_Pos)        ///< Interrupt enable the end of conversion for injected channel
#define ADC_ANY_CR_JEOSMPIE_Pos         (2)
#define ADC_ANY_CR_JEOSMPIE             (0x01U << ADC_ANY_CR_JEOSMPIE_Pos)      ///< Interrupt enable the end of sequence conversion for injected channel
#define ADC_ANY_CR_JCEN_Pos             (1)
#define ADC_ANY_CR_JCEN                 (0x01U << ADC_ANY_CR_JCEN_Pos)          ///< Injected channel enable

#define ADC_ANY_CR_CHANY_MDEN_Pos       (0)
#define ADC_ANY_CR_CHANY_MDEN           (0x01U << ADC_ANY_CR_CHANY_MDEN_Pos)    ///< Enable bits for any channel configuration mode:

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_SMPR1 mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_SMPR_SAMCTL_Pos             (0)                                     ///< Injection mode external trigger delay sampling off_set Position
#define ADC_SMPR_SAMCTL_Msk             (0x0FU << ADC_SMPR_SAMCTL_Pos)          ///< Injection mode external trigger delay sampling mask for Value
#define ADC_SMPR_SAMCTL_2_5             (0x00U << ADC_SMPR_SAMCTL_Pos)          ///< 2.5    cycle
#define ADC_SMPR_SAMCTL_8_5             (0x01U << ADC_SMPR_SAMCTL_Pos)          ///< 8.5    cycle
#define ADC_SMPR_SAMCTL_14_5            (0x02U << ADC_SMPR_SAMCTL_Pos)          ///< 14.5   cycle
#define ADC_SMPR_SAMCTL_29_5            (0x03U << ADC_SMPR_SAMCTL_Pos)          ///< 29.5   cycle
#define ADC_SMPR_SAMCTL_42_5            (0x04U << ADC_SMPR_SAMCTL_Pos)          ///< 42.5   cycle
#define ADC_SMPR_SAMCTL_56_5            (0x05U << ADC_SMPR_SAMCTL_Pos)          ///< 56.5   cycle
#define ADC_SMPR_SAMCTL_72_5            (0x06U << ADC_SMPR_SAMCTL_Pos)          ///< 72.5   cycle
#define ADC_SMPR_SAMCTL_240_5           (0x07U << ADC_SMPR_SAMCTL_Pos)          ///< 240.5  cycle
#define ADC_SMPR_SAMCTL_3_5             (0x08U << ADC_SMPR_SAMCTL_Pos)          ///< 3.5    cycle
#define ADC_SMPR_SAMCTL_4_5             (0x09U << ADC_SMPR_SAMCTL_Pos)          ///< 4.5    cycle
#define ADC_SMPR_SAMCTL_5_5             (0x0AU << ADC_SMPR_SAMCTL_Pos)          ///< 5.5    cycle
#define ADC_SMPR_SAMCTL_6_5             (0x0BU << ADC_SMPR_SAMCTL_Pos)          ///< 6.5    cycle
#define ADC_SMPR_SAMCTL_7_5             (0x0CU << ADC_SMPR_SAMCTL_Pos)          ///< 7.5    cycle


#define ADC_SMPR1_SAMCTL7_Pos           (28)                                    ///< Injection mode external trigger delay sampling
#define ADC_SMPR1_SAMCTL7_Msk           (0x0FU << ADC_SMPR1_SAMCTL7_Pos)        ///< Injection mode external trigger delay sampling mask for Value
#define ADC_SMPR1_SAMCTL7_2_5           (0x00U << ADC_SMPR1_SAMCTL7_Pos)        ///< 2.5    cycle
#define ADC_SMPR1_SAMCTL7_8_5           (0x01U << ADC_SMPR1_SAMCTL7_Pos)        ///< 8.5    cycle
#define ADC_SMPR1_SAMCTL7_14_5          (0x02U << ADC_SMPR1_SAMCTL7_Pos)        ///< 14.5   cycle
#define ADC_SMPR1_SAMCTL7_29_5          (0x03U << ADC_SMPR1_SAMCTL7_Pos)        ///< 29.5   cycle
#define ADC_SMPR1_SAMCTL7_42_5          (0x04U << ADC_SMPR1_SAMCTL7_Pos)        ///< 42.5   cycle
#define ADC_SMPR1_SAMCTL7_56_5          (0x05U << ADC_SMPR1_SAMCTL7_Pos)        ///< 56.5   cycle
#define ADC_SMPR1_SAMCTL7_72_5          (0x06U << ADC_SMPR1_SAMCTL7_Pos)        ///< 72.5   cycle
#define ADC_SMPR1_SAMCTL7_240_5         (0x07U << ADC_SMPR1_SAMCTL7_Pos)        ///< 240.5  cycle
#define ADC_SMPR1_SAMCTL7_3_5           (0x08U << ADC_SMPR1_SAMCTL7_Pos)        ///< 3.5    cycle
#define ADC_SMPR1_SAMCTL7_4_5           (0x09U << ADC_SMPR1_SAMCTL7_Pos)        ///< 4.5    cycle
#define ADC_SMPR1_SAMCTL7_5_5           (0x0AU << ADC_SMPR1_SAMCTL7_Pos)        ///< 5.5    cycle
#define ADC_SMPR1_SAMCTL7_6_5           (0x0BU << ADC_SMPR1_SAMCTL7_Pos)        ///< 6.5    cycle
#define ADC_SMPR1_SAMCTL7_7_5           (0x0CU << ADC_SMPR1_SAMCTL7_Pos)        ///< 7.5    cycle
#define ADC_SMPR1_SAMCTL6_Pos           (24)                                    ///< Injection mode external trigger delay sampling
#define ADC_SMPR1_SAMCTL6_2_5           (0x00U << ADC_SMPR1_SAMCTL6_Pos)        ///< 2.5    cycle
#define ADC_SMPR1_SAMCTL6_8_5           (0x01U << ADC_SMPR1_SAMCTL6_Pos)        ///< 8.5    cycle
#define ADC_SMPR1_SAMCTL6_14_5          (0x02U << ADC_SMPR1_SAMCTL6_Pos)        ///< 14.5   cycle
#define ADC_SMPR1_SAMCTL6_29_5          (0x03U << ADC_SMPR1_SAMCTL6_Pos)        ///< 29.5   cycle
#define ADC_SMPR1_SAMCTL6_42_5          (0x04U << ADC_SMPR1_SAMCTL6_Pos)        ///< 42.5   cycle
#define ADC_SMPR1_SAMCTL6_56_5          (0x05U << ADC_SMPR1_SAMCTL6_Pos)        ///< 56.5   cycle
#define ADC_SMPR1_SAMCTL6_72_5          (0x06U << ADC_SMPR1_SAMCTL6_Pos)        ///< 72.5   cycle
#define ADC_SMPR1_SAMCTL6_240_5         (0x07U << ADC_SMPR1_SAMCTL6_Pos)        ///< 240.5  cycle
#define ADC_SMPR1_SAMCTL6_3_5           (0x08U << ADC_SMPR1_SAMCTL6_Pos)        ///< 3.5    cycle
#define ADC_SMPR1_SAMCTL6_4_5           (0x09U << ADC_SMPR1_SAMCTL6_Pos)        ///< 4.5    cycle
#define ADC_SMPR1_SAMCTL6_5_5           (0x0AU << ADC_SMPR1_SAMCTL6_Pos)        ///< 5.5    cycle
#define ADC_SMPR1_SAMCTL6_6_5           (0x0BU << ADC_SMPR1_SAMCTL6_Pos)        ///< 6.5    cycle
#define ADC_SMPR1_SAMCTL6_7_5           (0x0CU << ADC_SMPR1_SAMCTL6_Pos)        ///< 7.5    cycle
#define ADC_SMPR1_SAMCTL5_Pos           (20)                                    ///< Injection mode external trigger delay sampling
#define ADC_SMPR1_SAMCTL5_2_5           (0x00U << ADC_SMPR1_SAMCTL5_Pos)        ///< 2.5    cycle
#define ADC_SMPR1_SAMCTL5_8_5           (0x01U << ADC_SMPR1_SAMCTL5_Pos)        ///< 8.5    cycle
#define ADC_SMPR1_SAMCTL5_14_5          (0x02U << ADC_SMPR1_SAMCTL5_Pos)        ///< 14.5   cycle
#define ADC_SMPR1_SAMCTL5_29_5          (0x03U << ADC_SMPR1_SAMCTL5_Pos)        ///< 29.5   cycle
#define ADC_SMPR1_SAMCTL5_42_5          (0x04U << ADC_SMPR1_SAMCTL5_Pos)        ///< 42.5   cycle
#define ADC_SMPR1_SAMCTL5_56_5          (0x05U << ADC_SMPR1_SAMCTL5_Pos)        ///< 56.5   cycle
#define ADC_SMPR1_SAMCTL5_72_5          (0x06U << ADC_SMPR1_SAMCTL5_Pos)        ///< 72.5   cycle
#define ADC_SMPR1_SAMCTL5_240_5         (0x07U << ADC_SMPR1_SAMCTL5_Pos)        ///< 240.5  cycle
#define ADC_SMPR1_SAMCTL5_3_5           (0x08U << ADC_SMPR1_SAMCTL5_Pos)        ///< 3.5    cycle
#define ADC_SMPR1_SAMCTL5_4_5           (0x09U << ADC_SMPR1_SAMCTL5_Pos)        ///< 4.5    cycle
#define ADC_SMPR1_SAMCTL5_5_5           (0x0AU << ADC_SMPR1_SAMCTL5_Pos)        ///< 5.5    cycle
#define ADC_SMPR1_SAMCTL5_6_5           (0x0BU << ADC_SMPR1_SAMCTL5_Pos)        ///< 6.5    cycle
#define ADC_SMPR1_SAMCTL5_7_5           (0x0CU << ADC_SMPR1_SAMCTL5_Pos)        ///< 7.5    cycle
#define ADC_SMPR1_SAMCTL4_Pos           (16)                                    ///< Injection mode external trigger delay sampling
#define ADC_SMPR1_SAMCTL4_2_5           (0x00U << ADC_SMPR1_SAMCTL4_Pos)        ///< 2.5    cycle
#define ADC_SMPR1_SAMCTL4_8_5           (0x01U << ADC_SMPR1_SAMCTL4_Pos)        ///< 8.5    cycle
#define ADC_SMPR1_SAMCTL4_14_5          (0x02U << ADC_SMPR1_SAMCTL4_Pos)        ///< 14.5   cycle
#define ADC_SMPR1_SAMCTL4_29_5          (0x03U << ADC_SMPR1_SAMCTL4_Pos)        ///< 29.5   cycle
#define ADC_SMPR1_SAMCTL4_42_5          (0x04U << ADC_SMPR1_SAMCTL4_Pos)        ///< 42.5   cycle
#define ADC_SMPR1_SAMCTL4_56_5          (0x05U << ADC_SMPR1_SAMCTL4_Pos)        ///< 56.5   cycle
#define ADC_SMPR1_SAMCTL4_72_5          (0x06U << ADC_SMPR1_SAMCTL4_Pos)        ///< 72.5   cycle
#define ADC_SMPR1_SAMCTL4_240_5         (0x07U << ADC_SMPR1_SAMCTL4_Pos)        ///< 240.5  cycle
#define ADC_SMPR1_SAMCTL4_3_5           (0x08U << ADC_SMPR1_SAMCTL4_Pos)        ///< 3.5    cycle
#define ADC_SMPR1_SAMCTL4_4_5           (0x09U << ADC_SMPR1_SAMCTL4_Pos)        ///< 4.5    cycle
#define ADC_SMPR1_SAMCTL4_5_5           (0x0AU << ADC_SMPR1_SAMCTL4_Pos)        ///< 5.5    cycle
#define ADC_SMPR1_SAMCTL4_6_5           (0x0BU << ADC_SMPR1_SAMCTL4_Pos)        ///< 6.5    cycle
#define ADC_SMPR1_SAMCTL4_7_5           (0x0CU << ADC_SMPR1_SAMCTL4_Pos)        ///< 7.5    cycle
#define ADC_SMPR1_SAMCTL3_Pos           (12)                                    ///< Injection mode external trigger delay sampling
#define ADC_SMPR1_SAMCTL3_2_5           (0x00U << ADC_SMPR1_SAMCTL3_Pos)        ///< 2.5    cycle
#define ADC_SMPR1_SAMCTL3_8_5           (0x01U << ADC_SMPR1_SAMCTL3_Pos)        ///< 8.5    cycle
#define ADC_SMPR1_SAMCTL3_14_5          (0x02U << ADC_SMPR1_SAMCTL3_Pos)        ///< 14.5   cycle
#define ADC_SMPR1_SAMCTL3_29_5          (0x03U << ADC_SMPR1_SAMCTL3_Pos)        ///< 29.5   cycle
#define ADC_SMPR1_SAMCTL3_42_5          (0x04U << ADC_SMPR1_SAMCTL3_Pos)        ///< 42.5   cycle
#define ADC_SMPR1_SAMCTL3_56_5          (0x05U << ADC_SMPR1_SAMCTL3_Pos)        ///< 56.5   cycle
#define ADC_SMPR1_SAMCTL3_72_5          (0x06U << ADC_SMPR1_SAMCTL3_Pos)        ///< 72.5   cycle
#define ADC_SMPR1_SAMCTL3_240_5         (0x07U << ADC_SMPR1_SAMCTL3_Pos)        ///< 240.5  cycle
#define ADC_SMPR1_SAMCTL3_3_5           (0x08U << ADC_SMPR1_SAMCTL3_Pos)        ///< 3.5    cycle
#define ADC_SMPR1_SAMCTL3_4_5           (0x09U << ADC_SMPR1_SAMCTL3_Pos)        ///< 4.5    cycle
#define ADC_SMPR1_SAMCTL3_5_5           (0x0AU << ADC_SMPR1_SAMCTL3_Pos)        ///< 5.5    cycle
#define ADC_SMPR1_SAMCTL3_6_5           (0x0BU << ADC_SMPR1_SAMCTL3_Pos)        ///< 6.5    cycle
#define ADC_SMPR1_SAMCTL3_7_5           (0x0CU << ADC_SMPR1_SAMCTL3_Pos)        ///< 7.5    cycle
#define ADC_SMPR1_SAMCTL2_Pos           (8)                                     ///< Injection mode external trigger delay sampling
#define ADC_SMPR1_SAMCTL2_2_5           (0x00U << ADC_SMPR1_SAMCTL2_Pos)        ///< 2.5    cycle
#define ADC_SMPR1_SAMCTL2_8_5           (0x01U << ADC_SMPR1_SAMCTL2_Pos)        ///< 8.5    cycle
#define ADC_SMPR1_SAMCTL2_14_5          (0x02U << ADC_SMPR1_SAMCTL2_Pos)        ///< 14.5   cycle
#define ADC_SMPR1_SAMCTL2_29_5          (0x03U << ADC_SMPR1_SAMCTL2_Pos)        ///< 29.5   cycle
#define ADC_SMPR1_SAMCTL2_42_5          (0x04U << ADC_SMPR1_SAMCTL2_Pos)        ///< 42.5   cycle
#define ADC_SMPR1_SAMCTL2_56_5          (0x05U << ADC_SMPR1_SAMCTL2_Pos)        ///< 56.5   cycle
#define ADC_SMPR1_SAMCTL2_72_5          (0x06U << ADC_SMPR1_SAMCTL2_Pos)        ///< 72.5   cycle
#define ADC_SMPR1_SAMCTL2_240_5         (0x07U << ADC_SMPR1_SAMCTL2_Pos)        ///< 240.5  cycle
#define ADC_SMPR1_SAMCTL2_3_5           (0x08U << ADC_SMPR1_SAMCTL2_Pos)        ///< 3.5    cycle
#define ADC_SMPR1_SAMCTL2_4_5           (0x09U << ADC_SMPR1_SAMCTL2_Pos)        ///< 4.5    cycle
#define ADC_SMPR1_SAMCTL2_5_5           (0x0AU << ADC_SMPR1_SAMCTL2_Pos)        ///< 5.5    cycle
#define ADC_SMPR1_SAMCTL2_6_5           (0x0BU << ADC_SMPR1_SAMCTL2_Pos)        ///< 6.5    cycle
#define ADC_SMPR1_SAMCTL2_7_5           (0x0CU << ADC_SMPR1_SAMCTL2_Pos)        ///< 7.5    cycle
#define ADC_SMPR1_SAMCTL1_Pos           (4)                                     ///< Injection mode external trigger delay sampling
#define ADC_SMPR1_SAMCTL1_2_5           (0x00U << ADC_SMPR1_SAMCTL1_Pos)        ///< 2.5    cycle
#define ADC_SMPR1_SAMCTL1_8_5           (0x01U << ADC_SMPR1_SAMCTL1_Pos)        ///< 8.5    cycle
#define ADC_SMPR1_SAMCTL1_14_5          (0x02U << ADC_SMPR1_SAMCTL1_Pos)        ///< 14.5   cycle
#define ADC_SMPR1_SAMCTL1_29_5          (0x03U << ADC_SMPR1_SAMCTL1_Pos)        ///< 29.5   cycle
#define ADC_SMPR1_SAMCTL1_42_5          (0x04U << ADC_SMPR1_SAMCTL1_Pos)        ///< 42.5   cycle
#define ADC_SMPR1_SAMCTL1_56_5          (0x05U << ADC_SMPR1_SAMCTL1_Pos)        ///< 56.5   cycle
#define ADC_SMPR1_SAMCTL1_72_5          (0x06U << ADC_SMPR1_SAMCTL1_Pos)        ///< 72.5   cycle
#define ADC_SMPR1_SAMCTL1_240_5         (0x07U << ADC_SMPR1_SAMCTL1_Pos)        ///< 240.5  cycle
#define ADC_SMPR1_SAMCTL1_3_5           (0x08U << ADC_SMPR1_SAMCTL1_Pos)        ///< 3.5    cycle
#define ADC_SMPR1_SAMCTL1_4_5           (0x09U << ADC_SMPR1_SAMCTL1_Pos)        ///< 4.5    cycle
#define ADC_SMPR1_SAMCTL1_5_5           (0x0AU << ADC_SMPR1_SAMCTL1_Pos)        ///< 5.5    cycle
#define ADC_SMPR1_SAMCTL1_6_5           (0x0BU << ADC_SMPR1_SAMCTL1_Pos)        ///< 6.5    cycle
#define ADC_SMPR1_SAMCTL1_7_5           (0x0CU << ADC_SMPR1_SAMCTL1_Pos)        ///< 7.5    cycle
#define ADC_SMPR1_SAMCTL0_Pos           (0)                                     ///< Injection mode external trigger delay sampling
#define ADC_SMPR1_SAMCTL0_2_5           (0x00U << ADC_SMPR1_SAMCTL0_Pos)        ///< 2.5    cycle
#define ADC_SMPR1_SAMCTL0_8_5           (0x01U << ADC_SMPR1_SAMCTL0_Pos)        ///< 8.5    cycle
#define ADC_SMPR1_SAMCTL0_14_5          (0x02U << ADC_SMPR1_SAMCTL0_Pos)        ///< 14.5   cycle
#define ADC_SMPR1_SAMCTL0_29_5          (0x03U << ADC_SMPR1_SAMCTL0_Pos)        ///< 29.5   cycle
#define ADC_SMPR1_SAMCTL0_42_5          (0x04U << ADC_SMPR1_SAMCTL0_Pos)        ///< 42.5   cycle
#define ADC_SMPR1_SAMCTL0_56_5          (0x05U << ADC_SMPR1_SAMCTL0_Pos)        ///< 56.5   cycle
#define ADC_SMPR1_SAMCTL0_72_5          (0x06U << ADC_SMPR1_SAMCTL0_Pos)        ///< 72.5   cycle
#define ADC_SMPR1_SAMCTL0_240_5         (0x07U << ADC_SMPR1_SAMCTL0_Pos)        ///< 240.5  cycle
#define ADC_SMPR1_SAMCTL0_3_5           (0x08U << ADC_SMPR1_SAMCTL0_Pos)        ///< 3.5    cycle
#define ADC_SMPR1_SAMCTL0_4_5           (0x09U << ADC_SMPR1_SAMCTL0_Pos)        ///< 4.5    cycle
#define ADC_SMPR1_SAMCTL0_5_5           (0x0AU << ADC_SMPR1_SAMCTL0_Pos)        ///< 5.5    cycle
#define ADC_SMPR1_SAMCTL0_6_5           (0x0BU << ADC_SMPR1_SAMCTL0_Pos)        ///< 6.5    cycle
#define ADC_SMPR1_SAMCTL0_7_5           (0x0CU << ADC_SMPR1_SAMCTL0_Pos)        ///< 7.5    cycle
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_SMPR2 mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_SMPR2_SAMCTL15_Pos          (28)                                     ///< Injection mode external trigger delay sampling
#define ADC_SMPR2_SAMCTL15_2_5          (0x00U << ADC_SMPR2_SAMCTL15_Pos)        ///< 2.5    cycle
#define ADC_SMPR2_SAMCTL15_8_5          (0x01U << ADC_SMPR2_SAMCTL15_Pos)        ///< 8.5    cycle
#define ADC_SMPR2_SAMCTL15_14_5         (0x02U << ADC_SMPR2_SAMCTL15_Pos)        ///< 14.5   cycle
#define ADC_SMPR2_SAMCTL15_29_5         (0x03U << ADC_SMPR2_SAMCTL15_Pos)        ///< 29.5   cycle
#define ADC_SMPR2_SAMCTL15_42_5         (0x04U << ADC_SMPR2_SAMCTL15_Pos)        ///< 42.5   cycle
#define ADC_SMPR2_SAMCTL15_56_5         (0x05U << ADC_SMPR2_SAMCTL15_Pos)        ///< 56.5   cycle
#define ADC_SMPR2_SAMCTL15_72_5         (0x06U << ADC_SMPR2_SAMCTL15_Pos)        ///< 72.5   cycle
#define ADC_SMPR2_SAMCTL15_240_5        (0x07U << ADC_SMPR2_SAMCTL15_Pos)        ///< 240.5  cycle
#define ADC_SMPR2_SAMCTL15_3_5          (0x08U << ADC_SMPR2_SAMCTL15_Pos)        ///< 3.5    cycle
#define ADC_SMPR2_SAMCTL15_4_5          (0x09U << ADC_SMPR2_SAMCTL15_Pos)        ///< 4.5    cycle
#define ADC_SMPR2_SAMCTL15_5_5          (0x0AU << ADC_SMPR2_SAMCTL15_Pos)        ///< 5.5    cycle
#define ADC_SMPR2_SAMCTL15_6_5          (0x0BU << ADC_SMPR2_SAMCTL15_Pos)        ///< 6.5    cycle
#define ADC_SMPR2_SAMCTL15_7_5          (0x0CU << ADC_SMPR2_SAMCTL15_Pos)        ///< 7.5    cycle
#define ADC_SMPR2_SAMCTL14_Pos          (24)                                    ///< Injection mode external trigger delay sampling
#define ADC_SMPR2_SAMCTL14_2_5          (0x00U << ADC_SMPR2_SAMCTL14_Pos)        ///< 2.5    cycle
#define ADC_SMPR2_SAMCTL14_8_5          (0x01U << ADC_SMPR2_SAMCTL14_Pos)        ///< 8.5    cycle
#define ADC_SMPR2_SAMCTL14_14_5         (0x02U << ADC_SMPR2_SAMCTL14_Pos)        ///< 14.5   cycle
#define ADC_SMPR2_SAMCTL14_29_5         (0x03U << ADC_SMPR2_SAMCTL14_Pos)        ///< 29.5   cycle
#define ADC_SMPR2_SAMCTL14_42_5         (0x04U << ADC_SMPR2_SAMCTL14_Pos)        ///< 42.5   cycle
#define ADC_SMPR2_SAMCTL14_56_5         (0x05U << ADC_SMPR2_SAMCTL14_Pos)        ///< 56.5   cycle
#define ADC_SMPR2_SAMCTL14_72_5         (0x06U << ADC_SMPR2_SAMCTL14_Pos)        ///< 72.5   cycle
#define ADC_SMPR2_SAMCTL14_240_5        (0x07U << ADC_SMPR2_SAMCTL14_Pos)        ///< 240.5  cycle
#define ADC_SMPR2_SAMCTL14_3_5          (0x08U << ADC_SMPR2_SAMCTL14_Pos)        ///< 3.5    cycle
#define ADC_SMPR2_SAMCTL14_4_5          (0x09U << ADC_SMPR2_SAMCTL14_Pos)        ///< 4.5    cycle
#define ADC_SMPR2_SAMCTL14_5_5          (0x0AU << ADC_SMPR2_SAMCTL14_Pos)        ///< 5.5    cycle
#define ADC_SMPR2_SAMCTL14_6_5          (0x0BU << ADC_SMPR2_SAMCTL14_Pos)        ///< 6.5    cycle
#define ADC_SMPR2_SAMCTL14_7_5          (0x0CU << ADC_SMPR2_SAMCTL14_Pos)        ///< 7.5    cycle
#define ADC_SMPR2_SAMCTL13_Pos          (20)                                    ///< Injection mode external trigger delay sampling
#define ADC_SMPR2_SAMCTL13_2_5          (0x00U << ADC_SMPR2_SAMCTL13_Pos)        ///< 2.5    cycle
#define ADC_SMPR2_SAMCTL13_8_5          (0x01U << ADC_SMPR2_SAMCTL13_Pos)        ///< 8.5    cycle
#define ADC_SMPR2_SAMCTL13_14_5         (0x02U << ADC_SMPR2_SAMCTL13_Pos)        ///< 14.5   cycle
#define ADC_SMPR2_SAMCTL13_29_5         (0x03U << ADC_SMPR2_SAMCTL13_Pos)        ///< 29.5   cycle
#define ADC_SMPR2_SAMCTL13_42_5         (0x04U << ADC_SMPR2_SAMCTL13_Pos)        ///< 42.5   cycle
#define ADC_SMPR2_SAMCTL13_56_5         (0x05U << ADC_SMPR2_SAMCTL13_Pos)        ///< 56.5   cycle
#define ADC_SMPR2_SAMCTL13_72_5         (0x06U << ADC_SMPR2_SAMCTL13_Pos)        ///< 72.5   cycle
#define ADC_SMPR2_SAMCTL13_240_5        (0x07U << ADC_SMPR2_SAMCTL13_Pos)        ///< 240.5  cycle
#define ADC_SMPR2_SAMCTL13_3_5          (0x08U << ADC_SMPR2_SAMCTL13_Pos)        ///< 3.5    cycle
#define ADC_SMPR2_SAMCTL13_4_5          (0x09U << ADC_SMPR2_SAMCTL13_Pos)        ///< 4.5    cycle
#define ADC_SMPR2_SAMCTL13_5_5          (0x0AU << ADC_SMPR2_SAMCTL13_Pos)        ///< 5.5    cycle
#define ADC_SMPR2_SAMCTL13_6_5          (0x0BU << ADC_SMPR2_SAMCTL13_Pos)        ///< 6.5    cycle
#define ADC_SMPR2_SAMCTL13_7_5          (0x0CU << ADC_SMPR2_SAMCTL13_Pos)        ///< 7.5    cycle
#define ADC_SMPR2_SAMCTL12_Pos          (16)                                    ///< Injection mode external trigger delay sampling
#define ADC_SMPR2_SAMCTL12_2_5          (0x00U << ADC_SMPR2_SAMCTL12_Pos)        ///< 2.5    cycle
#define ADC_SMPR2_SAMCTL12_8_5          (0x01U << ADC_SMPR2_SAMCTL12_Pos)        ///< 8.5    cycle
#define ADC_SMPR2_SAMCTL12_14_5         (0x02U << ADC_SMPR2_SAMCTL12_Pos)        ///< 14.5   cycle
#define ADC_SMPR2_SAMCTL12_29_5         (0x03U << ADC_SMPR2_SAMCTL12_Pos)        ///< 29.5   cycle
#define ADC_SMPR2_SAMCTL12_42_5         (0x04U << ADC_SMPR2_SAMCTL12_Pos)        ///< 42.5   cycle
#define ADC_SMPR2_SAMCTL12_56_5         (0x05U << ADC_SMPR2_SAMCTL12_Pos)        ///< 56.5   cycle
#define ADC_SMPR2_SAMCTL12_72_5         (0x06U << ADC_SMPR2_SAMCTL12_Pos)        ///< 72.5   cycle
#define ADC_SMPR2_SAMCTL12_240_5        (0x07U << ADC_SMPR2_SAMCTL12_Pos)        ///< 240.5  cycle
#define ADC_SMPR2_SAMCTL12_3_5          (0x08U << ADC_SMPR2_SAMCTL12_Pos)        ///< 3.5    cycle
#define ADC_SMPR2_SAMCTL12_4_5          (0x09U << ADC_SMPR2_SAMCTL12_Pos)        ///< 4.5    cycle
#define ADC_SMPR2_SAMCTL12_5_5          (0x0AU << ADC_SMPR2_SAMCTL12_Pos)        ///< 5.5    cycle
#define ADC_SMPR2_SAMCTL12_6_5          (0x0BU << ADC_SMPR2_SAMCTL12_Pos)        ///< 6.5    cycle
#define ADC_SMPR2_SAMCTL12_7_5          (0x0CU << ADC_SMPR2_SAMCTL12_Pos)        ///< 7.5    cycle
#define ADC_SMPR2_SAMCTL11_Pos          (12)                                    ///< Injection mode external trigger delay sampling
#define ADC_SMPR2_SAMCTL11_2_5          (0x00U << ADC_SMPR2_SAMCTL11_Pos)        ///< 2.5    cycle
#define ADC_SMPR2_SAMCTL11_8_5          (0x01U << ADC_SMPR2_SAMCTL11_Pos)        ///< 8.5    cycle
#define ADC_SMPR2_SAMCTL11_14_5         (0x02U << ADC_SMPR2_SAMCTL11_Pos)        ///< 14.5   cycle
#define ADC_SMPR2_SAMCTL11_29_5         (0x03U << ADC_SMPR2_SAMCTL11_Pos)        ///< 29.5   cycle
#define ADC_SMPR2_SAMCTL11_42_5         (0x04U << ADC_SMPR2_SAMCTL11_Pos)        ///< 42.5   cycle
#define ADC_SMPR2_SAMCTL11_56_5         (0x05U << ADC_SMPR2_SAMCTL11_Pos)        ///< 56.5   cycle
#define ADC_SMPR2_SAMCTL11_72_5         (0x06U << ADC_SMPR2_SAMCTL11_Pos)        ///< 72.5   cycle
#define ADC_SMPR2_SAMCTL11_240_5        (0x07U << ADC_SMPR2_SAMCTL11_Pos)        ///< 240.5  cycle
#define ADC_SMPR2_SAMCTL11_3_5          (0x08U << ADC_SMPR2_SAMCTL11_Pos)        ///< 3.5    cycle
#define ADC_SMPR2_SAMCTL11_4_5          (0x09U << ADC_SMPR2_SAMCTL11_Pos)        ///< 4.5    cycle
#define ADC_SMPR2_SAMCTL11_5_5          (0x0AU << ADC_SMPR2_SAMCTL11_Pos)        ///< 5.5    cycle
#define ADC_SMPR2_SAMCTL11_6_5          (0x0BU << ADC_SMPR2_SAMCTL11_Pos)        ///< 6.5    cycle
#define ADC_SMPR2_SAMCTL11_7_5          (0x0CU << ADC_SMPR2_SAMCTL11_Pos)        ///< 7.5    cycle
#define ADC_SMPR2_SAMCTL10_Pos          (8)                                     ///< Injection mode external trigger delay sampling
#define ADC_SMPR2_SAMCTL10_2_5          (0x00U << ADC_SMPR2_SAMCTL10_Pos)        ///< 2.5    cycle
#define ADC_SMPR2_SAMCTL10_8_5          (0x01U << ADC_SMPR2_SAMCTL10_Pos)        ///< 8.5    cycle
#define ADC_SMPR2_SAMCTL10_14_5         (0x02U << ADC_SMPR2_SAMCTL10_Pos)        ///< 14.5   cycle
#define ADC_SMPR2_SAMCTL10_29_5         (0x03U << ADC_SMPR2_SAMCTL10_Pos)        ///< 29.5   cycle
#define ADC_SMPR2_SAMCTL10_42_5         (0x04U << ADC_SMPR2_SAMCTL10_Pos)        ///< 42.5   cycle
#define ADC_SMPR2_SAMCTL10_56_5         (0x05U << ADC_SMPR2_SAMCTL10_Pos)        ///< 56.5   cycle
#define ADC_SMPR2_SAMCTL10_72_5         (0x06U << ADC_SMPR2_SAMCTL10_Pos)        ///< 72.5   cycle
#define ADC_SMPR2_SAMCTL10_240_5        (0x07U << ADC_SMPR2_SAMCTL10_Pos)        ///< 240.5  cycle
#define ADC_SMPR2_SAMCTL10_3_5          (0x08U << ADC_SMPR2_SAMCTL10_Pos)        ///< 3.5    cycle
#define ADC_SMPR2_SAMCTL10_4_5          (0x09U << ADC_SMPR2_SAMCTL10_Pos)        ///< 4.5    cycle
#define ADC_SMPR2_SAMCTL10_5_5          (0x0AU << ADC_SMPR2_SAMCTL10_Pos)        ///< 5.5    cycle
#define ADC_SMPR2_SAMCTL10_6_5          (0x0BU << ADC_SMPR2_SAMCTL10_Pos)        ///< 6.5    cycle
#define ADC_SMPR2_SAMCTL10_7_5          (0x0CU << ADC_SMPR2_SAMCTL10_Pos)        ///< 7.5    cycle
#define ADC_SMPR2_SAMCTL9_Pos           (4)                                     ///< Injection mode external trigger delay sampling
#define ADC_SMPR2_SAMCTL9_2_5           (0x00U << ADC_SMPR2_SAMCTL9_Pos)        ///< 2.5    cycle
#define ADC_SMPR2_SAMCTL9_8_5           (0x01U << ADC_SMPR2_SAMCTL9_Pos)        ///< 8.5    cycle
#define ADC_SMPR2_SAMCTL9_14_5          (0x02U << ADC_SMPR2_SAMCTL9_Pos)        ///< 14.5   cycle
#define ADC_SMPR2_SAMCTL9_29_5          (0x03U << ADC_SMPR2_SAMCTL9_Pos)        ///< 29.5   cycle
#define ADC_SMPR2_SAMCTL9_42_5          (0x04U << ADC_SMPR2_SAMCTL9_Pos)        ///< 42.5   cycle
#define ADC_SMPR2_SAMCTL9_56_5          (0x05U << ADC_SMPR2_SAMCTL9_Pos)        ///< 56.5   cycle
#define ADC_SMPR2_SAMCTL9_72_5          (0x06U << ADC_SMPR2_SAMCTL9_Pos)        ///< 72.5   cycle
#define ADC_SMPR2_SAMCTL9_240_5         (0x07U << ADC_SMPR2_SAMCTL9_Pos)        ///< 240.5  cycle
#define ADC_SMPR2_SAMCTL9_3_5           (0x08U << ADC_SMPR2_SAMCTL9_Pos)        ///< 3.5    cycle
#define ADC_SMPR2_SAMCTL9_4_5           (0x09U << ADC_SMPR2_SAMCTL9_Pos)        ///< 4.5    cycle
#define ADC_SMPR2_SAMCTL9_5_5           (0x0AU << ADC_SMPR2_SAMCTL9_Pos)        ///< 5.5    cycle
#define ADC_SMPR2_SAMCTL9_6_5           (0x0BU << ADC_SMPR2_SAMCTL9_Pos)        ///< 6.5    cycle
#define ADC_SMPR2_SAMCTL9_7_5           (0x0CU << ADC_SMPR2_SAMCTL9_Pos)        ///< 7.5    cycle
#define ADC_SMPR2_SAMCTL8_Pos           (0)                                     ///< Injection mode external trigger delay sampling
#define ADC_SMPR2_SAMCTL8_2_5           (0x00U << ADC_SMPR2_SAMCTL8_Pos)        ///< 2.5    cycle
#define ADC_SMPR2_SAMCTL8_8_5           (0x01U << ADC_SMPR2_SAMCTL8_Pos)        ///< 8.5    cycle
#define ADC_SMPR2_SAMCTL8_14_5          (0x02U << ADC_SMPR2_SAMCTL8_Pos)        ///< 14.5   cycle
#define ADC_SMPR2_SAMCTL8_29_5          (0x03U << ADC_SMPR2_SAMCTL8_Pos)        ///< 29.5   cycle
#define ADC_SMPR2_SAMCTL8_42_5          (0x04U << ADC_SMPR2_SAMCTL8_Pos)        ///< 42.5   cycle
#define ADC_SMPR2_SAMCTL8_56_5          (0x05U << ADC_SMPR2_SAMCTL8_Pos)        ///< 56.5   cycle
#define ADC_SMPR2_SAMCTL8_72_5          (0x06U << ADC_SMPR2_SAMCTL8_Pos)        ///< 72.5   cycle
#define ADC_SMPR2_SAMCTL8_240_5         (0x07U << ADC_SMPR2_SAMCTL8_Pos)        ///< 240.5  cycle
#define ADC_SMPR2_SAMCTL8_3_5           (0x08U << ADC_SMPR2_SAMCTL8_Pos)        ///< 3.5    cycle
#define ADC_SMPR2_SAMCTL8_4_5           (0x09U << ADC_SMPR2_SAMCTL8_Pos)        ///< 4.5    cycle
#define ADC_SMPR2_SAMCTL8_5_5           (0x0AU << ADC_SMPR2_SAMCTL8_Pos)        ///< 5.5    cycle
#define ADC_SMPR2_SAMCTL8_6_5           (0x0BU << ADC_SMPR2_SAMCTL8_Pos)        ///< 6.5    cycle
#define ADC_SMPR2_SAMCTL8_7_5           (0x0CU << ADC_SMPR2_SAMCTL8_Pos)        ///< 7.5    cycle
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_JOFR0 mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_JOFR0_JOFR                  (0xFFFU)                                ///< Compensates for the A/D conversion results of the injected channel 0
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_JOFR1 mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_JOFR1_JOFR                  (0xFFFU)                                ///< Compensates for the A/D conversion results of the injected channel 1
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_JOFR2 mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_JOFR2_JOFR                  (0xFFFU)                                ///< Compensates for the A/D conversion results of the injected channel 2
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_JOFR3 mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_JOFR3_JOFR                  (0xFFFU)                                ///< Compensates for the A/D conversion results of the injected channel 3
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_JSQR mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_JSQR_JSQ0_Pos            (0)                                          ///< 1st conversion in injected sequence
#define ADC_JSQR_JSQ0_0             (0x01U << ADC_JSQR_JSQ0_Pos)                  ///< Bit 0
#define ADC_JSQR_JSQ0_1             (0x02U << ADC_JSQR_JSQ0_Pos)                  ///< Bit 1
#define ADC_JSQR_JSQ0_2             (0x04U << ADC_JSQR_JSQ0_Pos)                  ///< Bit 2
#define ADC_JSQR_JSQ0_3             (0x08U << ADC_JSQR_JSQ0_Pos)                  ///< Bit 3
#define ADC_JSQR_JSQ0_4             (0x10U << ADC_JSQR_JSQ0_Pos)                  ///< Bit 4
#define ADC_JSQR_JSQ1_Pos           (5 )                                          ///< 2st conversion in injected sequence
#define ADC_JSQR_JSQ1_0             (0x01U << ADC_JSQR_JSQ1_Pos)                  ///< Bit 0
#define ADC_JSQR_JSQ1_1             (0x02U << ADC_JSQR_JSQ1_Pos)                  ///< Bit 1
#define ADC_JSQR_JSQ1_2             (0x04U << ADC_JSQR_JSQ1_Pos)                  ///< Bit 2
#define ADC_JSQR_JSQ1_3             (0x08U << ADC_JSQR_JSQ1_Pos)                  ///< Bit 3
#define ADC_JSQR_JSQ1_4             (0x10U << ADC_JSQR_JSQ1_Pos)                  ///< Bit 4
#define ADC_JSQR_JSQ2_Pos           (10)                                          ///< 3st conversion in injected sequence
#define ADC_JSQR_JSQ2_0             (0x01U << ADC_JSQR_JSQ2_Pos)                  ///< Bit 0
#define ADC_JSQR_JSQ2_1             (0x02U << ADC_JSQR_JSQ2_Pos)                  ///< Bit 1
#define ADC_JSQR_JSQ2_2             (0x04U << ADC_JSQR_JSQ2_Pos)                  ///< Bit 2
#define ADC_JSQR_JSQ2_3             (0x08U << ADC_JSQR_JSQ2_Pos)                  ///< Bit 3
#define ADC_JSQR_JSQ2_4             (0x10U << ADC_JSQR_JSQ2_Pos)                  ///< Bit 4
#define ADC_JSQR_JSQ3_Pos           (15)                                          ///< 4st conversion in injected sequence
#define ADC_JSQR_JSQ3_0             (0x01U << ADC_JSQR_JSQ3_Pos)                  ///< Bit 0
#define ADC_JSQR_JSQ3_1             (0x02U << ADC_JSQR_JSQ3_Pos)                  ///< Bit 1
#define ADC_JSQR_JSQ3_2             (0x04U << ADC_JSQR_JSQ3_Pos)                  ///< Bit 2
#define ADC_JSQR_JSQ3_3             (0x08U << ADC_JSQR_JSQ3_Pos)                  ///< Bit 3
#define ADC_JSQR_JSQ3_4             (0x10U << ADC_JSQR_JSQ3_Pos)                  ///< Bit 4

#define ADC_JSQR_JL_Pos             (20)                                          ///< Injected Sequence length
#define ADC_JSQR_JL_0               (0x01U << ADC_JSQR_JL_Pos)                    ///< Bit 0
#define ADC_JSQR_JL_1               (0x02U << ADC_JSQR_JL_Pos)                    ///< Bit 1
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_JDATA mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_JDATA_JVALID_Pos          (22)
#define ADC_JDATA_JVALID              (0x01U << ADC_JDATA_JVALID_Pos)               ///< Valid flag
#define ADC_JDATA_JOVERRUN_Pos        (21)
#define ADC_JDATA_JOVERRUN            (0x01U << ADC_JDATA_JOVERRUN_Pos)             ///< Overrun flag
#define ADC_JDATA_JCHANNELSEL_Pos     (16)
#define ADC_JDATA_JCHANNELSEL         (0xFFU << ADC_JDATA_JCHANNELSEL_Pos)          ///< Channel selection
#define ADC_JDATA_JDATA_Pos           (0)
#define ADC_JDATA_JDATA               (0xFFFFU << ADC_JSQR_JSQ0_Pos)                ///< Transfer data
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_JDR0 mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_JDR0_JVALID_Pos          (22)
#define ADC_JDR0_JVALID              (0x01U << ADC_JDATA_JVALID_Pos)               ///< Valid flag
#define ADC_JDR0_JOVERRUN_Pos        (21)
#define ADC_JDR0_JOVERRUN            (0x01U << ADC_JDATA_JOVERRUN_Pos)             ///< Overrun flag
#define ADC_JDR0_JDATA_Pos           (0)
#define ADC_JDR0_JDATA               (0xFFFFU << ADC_JSQR_JSQ0_Pos)                ///< Transfer data
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_JDR1 mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_JDR1_JVALID_Pos          (22)
#define ADC_JDR1_JVALID              (0x01U << ADC_JDATA_JVALID_Pos)               ///< Valid flag
#define ADC_JDR1_JOVERRUN_Pos        (21)
#define ADC_JDR1_JOVERRUN            (0x01U << ADC_JDATA_JOVERRUN_Pos)             ///< Overrun flag
#define ADC_JDR1_JDATA_Pos           (0)
#define ADC_JDR1_JDATA               (0xFFFFU << ADC_JSQR_JSQ0_Pos)                ///< Transfer data
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_JDR2 mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_JDR2_JVALID_Pos          (22)
#define ADC_JDR2_JVALID              (0x01U << ADC_JDATA_JVALID_Pos)               ///< Valid flag
#define ADC_JDR2_JOVERRUN_Pos        (21)
#define ADC_JDR2_JOVERRUN            (0x01U << ADC_JDATA_JOVERRUN_Pos)             ///< Overrun flag
#define ADC_JDR2_JDATA_Pos           (0)
#define ADC_JDR2_JDATA               (0xFFFFU << ADC_JSQR_JSQ0_Pos)                ///< Transfer data
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_JDR3 mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_JDR3_JVALID_Pos          (22)
#define ADC_JDR3_JVALID              (0x01U << ADC_JDATA_JVALID_Pos)               ///< Valid flag
#define ADC_JDR3_JOVERRUN_Pos        (21)
#define ADC_JDR3_JOVERRUN            (0x01U << ADC_JDATA_JOVERRUN_Pos)             ///< Overrun flag
#define ADC_JDR3_JDATA_Pos           (0)
#define ADC_JDR3_JDATA               (0xFFFFU << ADC_JSQR_JSQ0_Pos)                ///< Transfer data
/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
