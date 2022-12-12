////////////////////////////////////////////////////////////////////////////////
/// @file     reg_rcc.h
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

#ifndef __REG_RCC_H
#define __REG_RCC_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif








////////////////////////////////////////////////////////////////////////////////
/// @brief RCC Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_BASE                        (AHBPERIPH_BASE + 0x1000)               ///< Base Address: 0x40021000





////////////////////////////////////////////////////////////////////////////////
/// @brief RCC Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 CR;                                                                ///< Control Register                               offset: 0x00
    __IO u32 CFGR;                                                              ///< Configuration Register                         offset: 0x04
    __IO u32 CIR;                                                               ///< Clock Interrupt Register                       offset: 0x08
    __IO u32 AHB3RSTR;                                                          ///< Advanced High Performance Bus 3 Reset Register offset: 0x0C
    __IO u32 AHB2RSTR;                                                          ///< Advanced High Performance Bus 2 Reset Register offset: 0x10
    __IO u32 AHBRSTR;                                                           ///<  Advanced High Performance Bus 1 Reset Register  offset: 0x14
    __IO u32 APB2RSTR;                                                          ///< Advanced Peripheral Bus 2 Reset Register      offset: 0x18
    __IO u32 APB1RSTR;                                                          ///< Advanced Peripheral Bus 1 Reset Register      offset: 0x1C
    __IO u32 AHB3ENR;                                                           ///< Advanced High Performance Bus 3 Enable Register  offset: 0x20
    __IO u32 AHB2ENR;                                                           ///< Advanced High Performance Bus 2 Enable Register  offset: 0x24
    union {
        __IO u32 AHBENR;                                                        ///< Advanced High Performance Bus 1 Enable Register  offset: 0x28
        __IO u32 AHB1ENR;
    };

    __IO u32 APB2ENR;                                                           ///< Advanced Peripheral Bus 2 Enable Register      offset: 0x2C
    __IO u32 APB1ENR;                                                           ///< Advanced Peripheral Bus 1 Enable Register      offset: 0x30


    __IO u32 BDCR;                                                              ///< Backup Domain Control Register                  offset: 0x34
    __IO u32 CSR;                                                               ///< Control Status Register                         offset: 0x38
    __IO u32 SYSCFGR;                                                           ///< System Configuration Register                   offset: 0x3C
    __IO u32 CFGR2;                                                             ///< System Configuration Register                  offset: 0x40
    __IO u32 ICSCR;                                                             ///< Internal clock source calibration register     offset: 0x44
    __IO u32 PLLCFGR;                                                           ///< PLL configures registers                       offset: 0x48
    u32 Reserved1[13];                                                          ///< Reserved space
    __IO u32 HSIDLY;                                                            ///< HSI delay register                             offset: 0x80
    __IO u32 HSEDLY;                                                            ///< HSE delay register                             offset: 0x84
    __IO u32 PLLDLY;                                                            ///< PLL delay register                             offset: 0x88
} RCC_TypeDef;


////////////////////////////////////////////////////////////////////////////////
/// @brief RCC type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC                             ((RCC_TypeDef*) RCC_BASE)



////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_CR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_CR_HSION_Pos                (0)
#define RCC_CR_HSION                    (0x01U << RCC_CR_HSION_Pos)             ///< Internal High Speed clock enable

#define RCC_CR_HSIRDY_Pos               (1)
#define RCC_CR_HSIRDY                   (0x01U << RCC_CR_HSIRDY_Pos)            ///< Internal High Speed clock ready flag



#define  RCC_CR_HSIDIV_Pos              (11)
#define  RCC_CR_HSIDIV_0                (0x00U << RCC_CR_HSIDIV_Pos)            ///< HSI regardless of frequency
#define  RCC_CR_HSIDIV_2                (0x01U << RCC_CR_HSIDIV_Pos)            ///< HSI 2 frequency division
#define  RCC_CR_HSIDIV_4                (0x02U << RCC_CR_HSIDIV_Pos)            ///< HSI 4 frequency division
#define  RCC_CR_HSIDIV_8                (0x03U << RCC_CR_HSIDIV_Pos)            ///< HSI eight points and frequency
#define  RCC_CR_HSIDIV_16               (0x04U << RCC_CR_HSIDIV_Pos)            ///< HSI 16 points and frequency
#define  RCC_CR_HSIDIV_32               (0x05U << RCC_CR_HSIDIV_Pos)            ///< HSI 32 points and frequency
#define  RCC_CR_HSIDIV_64               (0x06U << RCC_CR_HSIDIV_Pos)            ///< HSI 64 frequency division
#define  RCC_CR_HSIDIV_128              (0x07U << RCC_CR_HSIDIV_Pos)            ///< HSI 128 frequency division
#define  RCC_CR_HSEON_Pos               (16)
#define  RCC_CR_HSEON                   (0x01U << RCC_CR_HSEON_Pos)             ///< External High Speed clock enable
#define  RCC_CR_HSERDY_Pos              (17)
#define  RCC_CR_HSERDY                  (0x01U << RCC_CR_HSERDY_Pos)            ///< External High Speed clock ready flag
#define  RCC_CR_HSEBYP_Pos              (18)
#define  RCC_CR_HSEBYP                  (0x01U << RCC_CR_HSEBYP_Pos)            ///< External High Speed clock Bypass
#define  RCC_CR_CSSON_Pos               (19)
#define  RCC_CR_CSSON                   (0x01U << RCC_CR_CSSON_Pos)             ///< Clock Security System enable


#define  RCC_CR_PLLON_Pos               (24)
#define  RCC_CR_PLLON                   (0x01U << RCC_CR_PLLON_Pos)             ///< PLL enable
#define  RCC_CR_PLLRDY_Pos              (25)
#define  RCC_CR_PLLRDY                  (0x01U << RCC_CR_PLLRDY_Pos)            ///< PLL clock ready flag
////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_CFGR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_CFGR_SW_Pos                 (0)
#define RCC_CFGR_SW                     (0x03U << RCC_CFGR_SW_Pos)              ///< SW[1:0] bits (System clock Switch)
#define RCC_CFGR_SW_HSI_DIV6            (0x00U << RCC_CFGR_SW_Pos)              ///< HSI/6 selected as system clock
#define RCC_CFGR_SW_HSE                 (0x01U << RCC_CFGR_SW_Pos)              ///< HSE selected as system clock
#define RCC_CFGR_SW_PLL                 (0x02U << RCC_CFGR_SW_Pos)              ///< PLL selected as system clock
#define RCC_CFGR_SW_LSI                 (0x03U << RCC_CFGR_SW_Pos)              ///< LSI selected as system clock

#define RCC_CFGR_SWS_Pos                (2)
#define RCC_CFGR_SWS                    (0x03U << RCC_CFGR_SWS_Pos)             ///< SWS[1:0] bits (System Clock Switch Status)
#define RCC_CFGR_SWS_HSI_DIV6           (0x00U << RCC_CFGR_SWS_Pos)             ///< HSI/6 oscillator used as system clock
#define RCC_CFGR_SWS_HSE                (0x01U << RCC_CFGR_SWS_Pos)             ///< HSE oscillator used as system clock
#define RCC_CFGR_SWS_PLL                (0x02U << RCC_CFGR_SWS_Pos)             ///< PLL used as system clock
#define RCC_CFGR_SWS_LSI                (0x03U << RCC_CFGR_SWS_Pos)             ///< LSI used as system clock

#define RCC_CFGR_HPRE_Pos               (4)
#define RCC_CFGR_HPRE                   (0x0FU << RCC_CFGR_HPRE_Pos)            ///< HPRE[3:0] bits (AHB prescaler)
#define RCC_CFGR_PPRE_0                 (0x01U << RCC_CFGR_HPRE_Pos)            ///< Bit 0
#define RCC_CFGR_PPRE_1                 (0x02U << RCC_CFGR_HPRE_Pos)            ///< Bit 1
#define RCC_CFGR_PPRE_2                 (0x04U << RCC_CFGR_HPRE_Pos)            ///< Bit 2
#define RCC_CFGR_PPRE_3                 (0x08U << RCC_CFGR_HPRE_Pos)            ///< Bit 3

#define RCC_CFGR_HPRE_DIV1              (0x00U << RCC_CFGR_HPRE_Pos)            ///< AHB = FCLK = SYSCLK not divided
#define RCC_CFGR_HPRE_DIV2              (0x08U << RCC_CFGR_HPRE_Pos)            ///< AHB = FCLK = SYSCLK divided by 2
#define RCC_CFGR_HPRE_DIV4              (0x09U << RCC_CFGR_HPRE_Pos)            ///< AHB = FCLK = SYSCLK divided by 4
#define RCC_CFGR_HPRE_DIV8              (0x0AU << RCC_CFGR_HPRE_Pos)            ///< AHB = FCLK = SYSCLK divided by 8
#define RCC_CFGR_HPRE_DIV16             (0x0BU << RCC_CFGR_HPRE_Pos)            ///< AHB = FCLK = SYSCLK divided by 16
#define RCC_CFGR_HPRE_DIV64             (0x0CU << RCC_CFGR_HPRE_Pos)            ///< AHB = FCLK = SYSCLK divided by 64
#define RCC_CFGR_HPRE_DIV128            (0x0DU << RCC_CFGR_HPRE_Pos)            ///< AHB = FCLK = SYSCLK divided by 128
#define RCC_CFGR_HPRE_DIV256            (0x0EU << RCC_CFGR_HPRE_Pos)            ///< AHB = FCLK = SYSCLK divided by 256
#define RCC_CFGR_HPRE_DIV512            (0x0FU << RCC_CFGR_HPRE_Pos)            ///< AHB = FCLK = SYSCLK divided by 512

#define RCC_CFGR_PPRE1_Pos              (8)
#define RCC_CFGR_PPRE1                  (0x07U << RCC_CFGR_PPRE1_Pos)           ///< PRE1[2:0] bits (APB1 prescaler)
#define RCC_CFGR_PPRE1_0                (0x01U << RCC_CFGR_PPRE1_Pos)           ///< Bit 0
#define RCC_CFGR_PPRE1_1                (0x02U << RCC_CFGR_PPRE1_Pos)           ///< Bit 1
#define RCC_CFGR_PPRE1_2                (0x04U << RCC_CFGR_PPRE1_Pos)           ///< Bit 2

#define RCC_CFGR_PPRE1_DIV1             (0x00U << RCC_CFGR_PPRE1_Pos)           ///< APB1 = HCLK not divided
#define RCC_CFGR_PPRE1_DIV2             (0x04U << RCC_CFGR_PPRE1_Pos)           ///< APB1 = HCLK divided by 2
#define RCC_CFGR_PPRE1_DIV4             (0x05U << RCC_CFGR_PPRE1_Pos)           ///< APB1 = HCLK divided by 4
#define RCC_CFGR_PPRE1_DIV8             (0x06U << RCC_CFGR_PPRE1_Pos)           ///< APB1 = HCLK divided by 8
#define RCC_CFGR_PPRE1_DIV16            (0x07U << RCC_CFGR_PPRE1_Pos)           ///< APB1 = HCLK divided by 16

#define RCC_CFGR_PPRE2_Pos              (11)
#define RCC_CFGR_PPRE2                  (0x07U << RCC_CFGR_PPRE2_Pos)           ///< PRE2[2:0] bits (APB2 prescaler)
#define RCC_CFGR_PPRE2_0                (0x01U << RCC_CFGR_PPRE2_Pos)           ///< Bit 0
#define RCC_CFGR_PPRE2_1                (0x02U << RCC_CFGR_PPRE2_Pos)           ///< Bit 1
#define RCC_CFGR_PPRE2_2                (0x04U << RCC_CFGR_PPRE2_Pos)           ///< Bit 2

#define RCC_CFGR_PPRE2_DIV1             (0x00U << RCC_CFGR_PPRE2_Pos)           ///< APB2 = HCLK not divided
#define RCC_CFGR_PPRE2_DIV2             (0x04U << RCC_CFGR_PPRE2_Pos)           ///< APB2 = HCLK divided by 2
#define RCC_CFGR_PPRE2_DIV4             (0x05U << RCC_CFGR_PPRE2_Pos)           ///< APB2 = HCLK divided by 4
#define RCC_CFGR_PPRE2_DIV8             (0x06U << RCC_CFGR_PPRE2_Pos)           ///< APB2 = HCLK divided by 8
#define RCC_CFGR_PPRE2_DIV16            (0x07U << RCC_CFGR_PPRE2_Pos)           ///< APB2 = HCLK divided by 16


#define RCC_CFGR_USBPRE_Pos             (22)
#define RCC_CFGR_USBPRE                 (0x03U << RCC_CFGR_USBPRE_Pos)          ///< USB prescaler BIT[1:0]

#define RCC_CFGR_MCO_Pos                (24)
#define RCC_CFGR_MCO                    (0x07U << RCC_CFGR_MCO_Pos)             ///< MCO[2:0] bits (Microcontroller Clock Output)
#define RCC_CFGR_MCO_NOCLOCK            (0x00U << RCC_CFGR_MCO_Pos)             ///< No clock
#define RCC_CFGR_MCO_LSI                (0x02U << RCC_CFGR_MCO_Pos)             ///< LSI clock
#define RCC_CFGR_MCO_LSE                (0x03U << RCC_CFGR_MCO_Pos)             ///< LSE clock
#define RCC_CFGR_MCO_SYSCLK             (0x04U << RCC_CFGR_MCO_Pos)             ///< System clock selected
#define RCC_CFGR_MCO_HSI                (0x05U << RCC_CFGR_MCO_Pos)             ///< Internal 48 MHz RC oscillator clock selected
#define RCC_CFGR_MCO_HSE                (0x06U << RCC_CFGR_MCO_Pos)             ///< External 1-25 MHz oscillator clock selected
#define RCC_CFGR_MCO_PLL                (0x07U << RCC_CFGR_MCO_Pos)             ///< PLL clock divided by 2 selected



////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_CIR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_CIR_LSIRDYF_Pos             (0)
#define RCC_CIR_LSIRDYF                 (0x01U << RCC_CIR_LSIRDYF_Pos)          ///< LSI Ready Interrupt flag

#define RCC_CIR_LSERDYF_Pos             (1)
#define RCC_CIR_LSERDYF                 (0x01U << RCC_CIR_LSERDYF_Pos)          ///< LSE Ready Interrupt flag

#define RCC_CIR_HSIRDYF_Pos             (2)
#define RCC_CIR_HSIRDYF                 (0x01U << RCC_CIR_HSIRDYF_Pos)          ///< HSI Ready Interrupt flag
#define RCC_CIR_HSERDYF_Pos             (3)
#define RCC_CIR_HSERDYF                 (0x01U << RCC_CIR_HSERDYF_Pos)          ///< HSE Ready Interrupt flag

#define RCC_CIR_PLLRDYF_Pos             (4)
#define RCC_CIR_PLLRDYF                 (0x01U << RCC_CIR_PLLRDYF_Pos)          ///< PLL Ready Interrupt flag

#define RCC_CIR_CSSF_Pos                (7)
#define RCC_CIR_CSSF                    (0x01U << RCC_CIR_CSSF_Pos)             ///< Clock Security System Interrupt flag
#define RCC_CIR_LSIRDYIE_Pos            (8)
#define RCC_CIR_LSIRDYIE                (0x01U << RCC_CIR_LSIRDYIE_Pos)         ///< LSI Ready Interrupt Enable

#define RCC_CIR_LSERDYIE_Pos            (9)
#define RCC_CIR_LSERDYIE                (0x01U << RCC_CIR_LSERDYIE_Pos)         ///< LSE Ready Interrupt Enable

#define RCC_CIR_HSIRDYIE_Pos            (10)
#define RCC_CIR_HSIRDYIE                (0x01U << RCC_CIR_HSIRDYIE_Pos)         ///< HSI Ready Interrupt Enable
#define RCC_CIR_HSERDYIE_Pos            (11)
#define RCC_CIR_HSERDYIE                (0x01U << RCC_CIR_HSIRDYIE_Pos)         ///< HSE Ready Interrupt Enable

#define RCC_CIR_PLLRDYIE_Pos            (12)
#define RCC_CIR_PLLRDYIE                (0x01U << RCC_CIR_PLLRDYIE_Pos)         ///< PLL Ready Interrupt Enable

#define RCC_CIR_LSIRDYC_Pos             (16)
#define RCC_CIR_LSIRDYC                 (0x01U << RCC_CIR_LSIRDYC_Pos)          ///< LSI Ready Interrupt Clear

#define RCC_CIR_LSERDYC_Pos             (17)
#define RCC_CIR_LSERDYC                 (0x01U << RCC_CIR_LSERDYC_Pos)          ///< LSE Ready Interrupt Clear

#define RCC_CIR_HSIRDYC_Pos             (18)
#define RCC_CIR_HSIRDYC                 (0x01U << RCC_CIR_HSIRDYC_Pos)          ///< HSI Ready Interrupt Clear
#define RCC_CIR_HSERDYC_Pos             (19)
#define RCC_CIR_HSERDYC                 (0x01U << RCC_CIR_HSERDYC_Pos)          ///< HSE Ready Interrupt Clear

#define RCC_CIR_PLLRDYC_Pos             (20)
#define RCC_CIR_PLLRDYC                 (0x01U << RCC_CIR_PLLRDYC_Pos)          ///< PLL Ready Interrupt Clear

#define RCC_CIR_CSSC_Pos                (23)
#define RCC_CIR_CSSC                    (0x01U << RCC_CIR_CSSC_Pos)             ///< Clock Security System Interrupt Clear

////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_APB2RSTR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_APB2RSTR_TIM1_Pos           (0)
#define RCC_APB2RSTR_TIM1               (0x01U << RCC_APB2RSTR_TIM1_Pos)        ///< TIM1 reset
#define RCC_APB2RSTR_TIM8_Pos           (1)
#define RCC_APB2RSTR_TIM8               (0x01U << RCC_APB2RSTR_TIM8_Pos)        ///< TIM8 reset
#define RCC_APB2RSTR_UART1_Pos          (4)
#define RCC_APB2RSTR_UART1              (0x01U << RCC_APB2RSTR_UART1_Pos)       ///< UART1 reset
#define RCC_APB2RSTR_UART6_Pos          (5)
#define RCC_APB2RSTR_UART6              (0x01U << RCC_APB2RSTR_UART6_Pos)       ///< UART6 reset
#define RCC_APB2RSTR_ADC1_Pos           (8)
#define RCC_APB2RSTR_ADC1               (0x01U << RCC_APB2RSTR_ADC1_Pos)        ///< ADC1 reset
#define RCC_APB2RSTR_ADC2_Pos           (9)
#define RCC_APB2RSTR_ADC2               (0x01U << RCC_APB2RSTR_ADC2_Pos)        ///< ADC2 reset
#define RCC_APB2RSTR_ADC3_Pos           (10)
#define RCC_APB2RSTR_ADC3               (0x01U << RCC_APB2RSTR_ADC3_Pos)        ///< ADC3 reset
#define RCC_APB2RSTR_SPI1_Pos           (12)
#define RCC_APB2RSTR_SPI1               (0x01U << RCC_APB2RSTR_SPI1_Pos)        ///< SPI1 reset
#define RCC_APB2RSTR_SYSCFG_Pos         (14)
#define RCC_APB2RSTR_SYSCFG             (0x01U << RCC_APB2RSTR_SYSCFG_Pos)      ///< SYSCFG reset
#define RCC_APB2RSTR_COMP_Pos           (15)
#define RCC_APB2RSTR_COMP               (0x01U << RCC_APB2RSTR_COMP_Pos)        ///< COMP reset








////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_AHB3RSTR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_AHB3RSTR_FSMC_Pos           (0)
#define RCC_AHB3RSTR_FSMC               (0x01U << RCC_AHB3RSTR_FSMC_Pos)        ///< FSMC reset


////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_APB1RSTR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_APB1RSTR_TIM2_Pos           (0)
#define RCC_APB1RSTR_TIM2               (0x01U << RCC_APB1RSTR_TIM2_Pos)        ///< Timer 2 reset
#define RCC_APB1RSTR_TIM3_Pos           (1)
#define RCC_APB1RSTR_TIM3               (0x01U << RCC_APB1RSTR_TIM3_Pos)        ///< Timer 3 reset

#define RCC_APB1RSTR_TIM4_Pos           (2)
#define RCC_APB1RSTR_TIM4               (0x01U << RCC_APB1RSTR_TIM4_Pos)        ///< Timer 4 reset
#define RCC_APB1RSTR_TIM5_Pos           (3)
#define RCC_APB1RSTR_TIM5               (0x01U << RCC_APB1RSTR_TIM5_Pos)        ///< Timer 5 reset
#define RCC_APB1RSTR_TIM6_Pos           (4)
#define RCC_APB1RSTR_TIM6               (0x01U << RCC_APB1RSTR_TIM6_Pos)        ///< Timer 6 reset
#define RCC_APB1RSTR_TIM7_Pos           (5)
#define RCC_APB1RSTR_TIM7               (0x01U << RCC_APB1RSTR_TIM7_Pos)        ///< Timer 7 reset

#define RCC_APB1RSTR_WWDG_Pos           (11)
#define RCC_APB1RSTR_WWDG               (0x01U << RCC_APB1RSTR_WWDG_Pos)        ///< Window Watchdog reset
#define RCC_APB1RSTR_SPI2_Pos           (14)
#define RCC_APB1RSTR_SPI2               (0x01U << RCC_APB1RSTR_SPI2_Pos)        ///< SPI 2 reset
#define RCC_APB1RSTR_SPI3_Pos           (15)
#define RCC_APB1RSTR_SPI3               (0x01U << RCC_APB1RSTR_SPI3_Pos)        ///< SPI 3 reset

#define RCC_APB1RSTR_UART2_Pos          (17)
#define RCC_APB1RSTR_UART2              (0x01U << RCC_APB1RSTR_UART2_Pos)       ///< UART 2 reset
#define RCC_APB1RSTR_UART3_Pos          (18)
#define RCC_APB1RSTR_UART3              (0x01U << RCC_APB1RSTR_UART3_Pos)       ///< UART 3 reset
#define RCC_APB1RSTR_UART4_Pos          (19)
#define RCC_APB1RSTR_UART4              (0x01U << RCC_APB1RSTR_UART4_Pos)       ///< UART 4 reset
#define RCC_APB1RSTR_UART5_Pos          (20)
#define RCC_APB1RSTR_UART5              (0x01U << RCC_APB1RSTR_UART5_Pos)       ///< UART 5 reset
#define RCC_APB1RSTR_I2C1_Pos           (21)
#define RCC_APB1RSTR_I2C1               (0x01U << RCC_APB1RSTR_I2C1_Pos)        ///< I2C 1 reset
#define RCC_APB1RSTR_I2C2_Pos           (22)
#define RCC_APB1RSTR_I2C2               (0x01U << RCC_APB1RSTR_I2C2_Pos)        ///< I2C 2 reset

#define RCC_APB1RSTR_CRS_Pos            (24)
#define RCC_APB1RSTR_CRS                (0x01U << RCC_APB1RSTR_CRS_Pos)         ///< CRS reset
#define RCC_APB1RSTR_CAN_Pos            (25)
#define RCC_APB1RSTR_CAN                (0x01U << RCC_APB1RSTR_CAN_Pos)         ///< CAN reset

#define RCC_APB1RSTR_BKP_Pos            (27)
#define RCC_APB1RSTR_BKP                (0x01U << RCC_APB1RSTR_BKP_Pos)         ///< Backup interface reset

#define RCC_APB1RSTR_PWR_Pos            (28)
#define RCC_APB1RSTR_PWR                (0x01U << RCC_APB1RSTR_PWR_Pos)         ///< Power interface reset
#define RCC_APB1RSTR_DAC_Pos            (29)
#define RCC_APB1RSTR_DAC                (0x01U << RCC_APB1RSTR_DAC_Pos)         ///< DAC interface reset


#define RCC_APB1RSTR_UART7_Pos          (30)
#define RCC_APB1RSTR_UART7              (0x01U << RCC_APB1RSTR_UART7_Pos)        ///< UART7 reset
#define RCC_APB1RSTR_UART8_Pos          (31)
#define RCC_APB1RSTR_UART8              (0x01U << RCC_APB1RSTR_UART8_Pos)        ///< UART8 reset

////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_AHB2RSTR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_AHB2RSTR_USBFS_Pos          (7)
#define RCC_AHB2RSTR_USBFS              (0x01U << RCC_AHB2RSTR_USBFS_Pos)       ///< USBFS reset
////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_AHB3ENR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_AHB3ENR_FSMC_Pos            (0)
#define RCC_AHB3ENR_FSMC                (0x01U << RCC_AHB3ENR_FSMC_Pos)       ///< FSMC reset

////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_AHB2ENR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_AHB2ENR_USBFS_Pos           (7)
#define RCC_AHB2ENR_USBFS               (0x01U << RCC_AHB2ENR_USBFS_Pos)       ///< USBFS reset

////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_AHBENR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////



#define RCC_AHBENR_GPIOA_Pos             (0)
#define RCC_AHBENR_GPIOA                 (0x01U << RCC_AHBENR_GPIOA_Pos)          ///< GPIOA clock enable
#define RCC_AHBENR_GPIOB_Pos             (1)
#define RCC_AHBENR_GPIOB                 (0x01U << RCC_AHBENR_GPIOB_Pos)          ///< GPIOB clock enable
#define RCC_AHBENR_GPIOC_Pos             (2)
#define RCC_AHBENR_GPIOC                 (0x01U << RCC_AHBENR_GPIOC_Pos)          ///< GPIOC clock enable
#define RCC_AHBENR_GPIOD_Pos             (3)
#define RCC_AHBENR_GPIOD                 (0x01U << RCC_AHBENR_GPIOD_Pos)          ///< GPIOD clock enable
#define RCC_AHBENR_GPIOE_Pos             (4)
#define RCC_AHBENR_GPIOE                 (0x01U << RCC_AHBENR_GPIOE_Pos)          ///< GPIOE clock enable
#define RCC_AHBENR_GPIOF_Pos             (5)
#define RCC_AHBENR_GPIOF                 (0x01U << RCC_AHBENR_GPIOF_Pos)          ///< GPIOF clock enable
#define RCC_AHBENR_GPIOG_Pos             (6)
#define RCC_AHBENR_GPIOG                 (0x01U << RCC_AHBENR_GPIOG_Pos)          ///< GPIOG clock enable
#define RCC_AHBENR_GPIOH_Pos             (7)
#define RCC_AHBENR_GPIOH                 (0x01U << RCC_AHBENR_GPIOH_Pos)          ///< GPIOH clock enable
#define RCC_AHBENR_SDIO_Pos             (10)
#define RCC_AHBENR_SDIO                 (0x01U << RCC_AHBENR_SDIO_Pos)          ///< SDIO clock enable
#define RCC_AHBENR_CRC_Pos              (12)
#define RCC_AHBENR_CRC                  (0x01U << RCC_AHBENR_CRC_Pos)          ///< CRC clock enable
#define RCC_AHBENR_FLASH_Pos            (13)
#define RCC_AHBENR_FLASH                (0x01U << RCC_AHBENR_FLASH_Pos)          ///< FLASH clock enable
#define RCC_AHBENR_SRAM_Pos             (14)
#define RCC_AHBENR_SRAM                 (0x01U << RCC_AHBENR_SRAM_Pos)          ///< SRAM clock enable
#define RCC_AHBENR_DMA1_Pos             (21)
#define RCC_AHBENR_DMA1                 (0x01U << RCC_AHBENR_DMA1_Pos)          ///< DMA1 clock enable
#define RCC_AHBENR_DMA2_Pos             (22)
#define RCC_AHBENR_DMA2                 (0x01U << RCC_AHBENR_DMA2_Pos)          ///< DMA2 clock enable
#define RCC_AHBENR_ETHMAC_Pos           (25)
#define RCC_AHBENR_ETHMAC               (0x01U << RCC_AHBENR_ETHMAC_Pos)        ///< ETHMAC clock enable
////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_APB2ENR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_APB2ENR_TIM1_Pos         (0)
#define RCC_APB2ENR_TIM1             (0x01U << RCC_APB2ENR_TIM1_Pos)          ///< TIM1 enable
#define RCC_APB2ENR_TIM8_Pos         (1)
#define RCC_APB2ENR_TIM8             (0x01U << RCC_APB2ENR_TIM8_Pos)          ///< TIM8 enable
#define RCC_APB2ENR_UART1_Pos        (4)
#define RCC_APB2ENR_UART1            (0x01U << RCC_APB2ENR_UART1_Pos)         ///< UART1 enable
#define RCC_APB2ENR_UART6_Pos        (5)
#define RCC_APB2ENR_UART6            (0x01U << RCC_APB2ENR_UART6_Pos)         ///< UART6 enable
#define RCC_APB2ENR_ADC1_Pos         (8)
#define RCC_APB2ENR_ADC1             (0x01U << RCC_APB2ENR_ADC1_Pos)          ///< ADC1 enable
#define RCC_APB2ENR_ADC2_Pos         (9)
#define RCC_APB2ENR_ADC2             (0x01U << RCC_APB2ENR_ADC2_Pos)          ///< ADC2 enable
#define RCC_APB2ENR_ADC3_Pos         (10)
#define RCC_APB2ENR_ADC3             (0x01U << RCC_APB2ENR_ADC3_Pos)          ///< ADC3 enable
#define RCC_APB2ENR_SPI1_Pos         (12)
#define RCC_APB2ENR_SPI1             (0x01U << RCC_APB2ENR_SPI1_Pos)          ///< SPI1 enable
#define RCC_APB2ENR_EXTI_Pos         (14)
#define RCC_APB2ENR_EXTI             (0x01U << RCC_APB2ENR_EXTI_Pos)          ///< EXTI Block enable
#define RCC_APB2ENR_SYSCFG_Pos       (14)
#define RCC_APB2ENR_SYSCFG           (0x01U << RCC_APB2ENR_SYSCFG_Pos)        ///< SYSCFG enable
#define RCC_APB2ENR_COMP_Pos         (15)
#define RCC_APB2ENR_COMP             (0x01U << RCC_APB2ENR_COMP_Pos)          ///< COMP enable
////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_APB1ENR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_APB1ENR_TIM2_Pos            (0)
#define RCC_APB1ENR_TIM2                (0x01U << RCC_APB1ENR_TIM2_Pos)         ///< Timer 2 clock enable

#define RCC_APB1ENR_TIM3_Pos            (1)
#define RCC_APB1ENR_TIM3                (0x01U << RCC_APB1ENR_TIM3_Pos)         ///< Timer 3 clock enabled

#define RCC_APB1ENR_TIM4_Pos            (2)
#define RCC_APB1ENR_TIM4                (0x01U << RCC_APB1ENR_TIM4_Pos)         ///< Timer 4 clock enable


#define RCC_APB1ENR_TIM5_Pos            (3)
#define RCC_APB1ENR_TIM5                (0x01U << RCC_APB1ENR_TIM5_Pos)        ///< TIM5 Timer clock enable
#define RCC_APB1ENR_TIM6_Pos            (4)
#define RCC_APB1ENR_TIM6                (0x01U << RCC_APB1ENR_TIM6_Pos)        ///< TIM6 Timer clock enable
#define RCC_APB1ENR_TIM7_Pos            (5)
#define RCC_APB1ENR_TIM7                (0x01U << RCC_APB1ENR_TIM7_Pos)        ///< TIM7 Timer clock enable

#define RCC_APB1ENR_WWDG_Pos            (11)
#define RCC_APB1ENR_WWDG                (0x01U << RCC_APB1ENR_WWDG_Pos)         ///< Window Watchdog clock enable


#define RCC_APB1ENR_SPI2_Pos            (14)
#define RCC_APB1ENR_SPI2                (0x01U << RCC_APB1ENR_SPI2_Pos)         ///< SPI 2 clock enable
#define RCC_APB1ENR_SPI3_Pos            (15)
#define RCC_APB1ENR_SPI3                (0x01U << RCC_APB1ENR_SPI3_Pos)         ///< SPI 3 clock enable

#define RCC_APB1ENR_UART2_Pos           (17)
#define RCC_APB1ENR_UART2               (0x01U << RCC_APB1ENR_UART2_Pos)        ///< UART 2 clock enable
#define RCC_APB1ENR_UART3_Pos           (18)
#define RCC_APB1ENR_UART3               (0x01U << RCC_APB1ENR_UART3_Pos)        ///< UART 3 clock enable
#define RCC_APB1ENR_UART4_Pos           (19)
#define RCC_APB1ENR_UART4               (0x01U << RCC_APB1ENR_UART4_Pos)        ///< UART 4 clock enable
#define RCC_APB1ENR_UART5_Pos           (20)
#define RCC_APB1ENR_UART5               (0x01U << RCC_APB1ENR_UART5_Pos)        ///< UART 5 clock enable
#define RCC_APB1ENR_I2C1_Pos            (21)
#define RCC_APB1ENR_I2C1                (0x01U << RCC_APB1ENR_I2C1_Pos)         ///< I2C 1 clock enable
#define RCC_APB1ENR_I2C2_Pos            (22)
#define RCC_APB1ENR_I2C2                (0x01U << RCC_APB1ENR_I2C2_Pos)         ///< I2C 2 clock enable
#define RCC_APB1ENR_CRS_Pos             (24)
#define RCC_APB1ENR_CRS                 (0x01U << RCC_APB1ENR_CRS_Pos)         ///< CRS 4 clock enable
#define RCC_APB1ENR_CAN_Pos             (25)
#define RCC_APB1ENR_CAN                 (0x01U << RCC_APB1ENR_CAN_Pos)         ///< CAN 5 clock enable



#define RCC_APB1ENR_BKP_Pos             (27)
#define RCC_APB1ENR_BKP                 (0x01U << RCC_APB1ENR_BKP_Pos)          ///< Backup interface clock enable

#define RCC_APB1ENR_PWR_Pos             (28)
#define RCC_APB1ENR_PWR                 (0x01U << RCC_APB1ENR_PWR_Pos)          ///< Power interface clock enable

#define RCC_APB1ENR_DBGMCU_Pos          (28)
#define RCC_APB1ENR_DBGMCU              (0x01U << RCC_APB1ENR_DBGMCU_Pos)       ///< DBGMCU clock enable


#define RCC_APB1ENR_DAC_Pos             (29)
#define RCC_APB1ENR_DAC                 (0x01U << RCC_APB1ENR_DAC_Pos)          ///< DAC interface clock enable
#define RCC_APB1ENR_UART7_Pos            (30)
#define RCC_APB1ENR_UART7                (0x01U << RCC_APB1ENR_UART7_Pos)       ///< UART7 interface clock enable
#define RCC_APB1ENR_UART8_Pos            (31)
#define RCC_APB1ENR_UART8                (0x01U << RCC_APB1ENR_UART8_Pos)       ///< UART8 interface clock enable
////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_BDCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_BDCR_LSEON_Pos              (0)
#define RCC_BDCR_LSEON                  (0x01U << RCC_BDCR_LSEON_Pos)           ///< External Low Speed oscillator enable
#define RCC_BDCR_LSERDY_Pos             (1)
#define RCC_BDCR_LSERDY                 (0x01U << RCC_BDCR_LSERDY_Pos)          ///< External Low Speed oscillator Ready
#define RCC_BDCR_LSEBYP_Pos             (2)
#define RCC_BDCR_LSEBYP                 (0x01U << RCC_BDCR_LSEBYP_Pos)          ///< External Low Speed oscillator Bypass

#define RCC_BDCR_RTCSEL_Pos             (8)
#define RCC_BDCR_RTCSEL                 (0x03U << RCC_BDCR_RTCSEL_Pos)          ///< RTCSEL[1:0] bits (RTC clock source selection)
#define RCC_BDCR_RTCSEL_LSE             (0x01U << RCC_BDCR_RTCSEL_Pos)          ///< LSE oscillator clock used as RTC clock
#define RCC_BDCR_RTCSEL_LSI             (0x02U << RCC_BDCR_RTCSEL_Pos)          ///< LSI oscillator clock used as RTC clock
#define RCC_BDCR_RTCSEL_HSE             (0x03U << RCC_BDCR_RTCSEL_Pos)          ///< HSE oscillator clock divided by 128 used as RTC clock

#define RCC_BDCR_RTCEN_Pos              (15)
#define RCC_BDCR_RTCEN                  (0x01U << RCC_BDCR_RTCEN_Pos)           ///< RTC clock enable
#define RCC_BDCR_BDRST_Pos              (16)
#define RCC_BDCR_BDRST                  (0x01U << RCC_BDCR_BDRST_Pos)           ///< Backup domain software reset
#define RCC_BDCR_DBP_Pos                (24)
#define RCC_BDCR_DBP                    (0x01U << RCC_BDCR_DBP_Pos)             ///< DBP clock enable


////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_CSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_CSR_LSION_Pos               (0)
#define RCC_CSR_LSION                   (0x01U << RCC_CSR_LSION_Pos)            ///< Internal Low Speed oscillator enable
#define RCC_CSR_LSIRDY_Pos              (1)
#define RCC_CSR_LSIRDY                  (0x01U << RCC_CSR_LSIRDY_Pos)           ///< Internal Low Speed oscillator Ready
#define RCC_CSR_LSIOENLV_Pos            (5)
#define RCC_CSR_LSIOENLV                (0x01U << RCC_CSR_LSIOENLV_Pos)         ///< LSI output enable lower voltage
#define RCC_CSR_PVDRSTEN_Pos            (6)
#define RCC_CSR_PVDRSTEN                (0x01U << RCC_CSR_PVDRSTEN_Pos)         ///< PVD reset enable
#define RCC_CSR_LOCKUPEN_Pos            (7)
#define RCC_CSR_LOCKUPEN                (0x01U << RCC_CSR_LOCKUPEN_Pos)         ///< CPU lockup reset enable
#define RCC_CSR_VDTRSTNEN_Pos           (8)
#define RCC_CSR_VDTRSTNEN               (0x01U << RCC_CSR_VDTRSTNEN_Pos)        ///< Voltage detect reset enable
#define RCC_CSR_VDTRSTF_Pos             (21)
#define RCC_CSR_VDTRSTF                 (0x01U << RCC_CSR_VDTRSTF_Pos)           ///< Voltage detect reset flag
#define RCC_CSR_PVDRSTF_Pos             (22)
#define RCC_CSR_PVDRSTF                 (0x01U << RCC_CSR_PVDRSTF_Pos)           ///< PVD reset flag
#define RCC_CSR_LOCKUPF_Pos             (23)
#define RCC_CSR_LOCKUPF                 (0x01U << RCC_CSR_LOCKUPF_Pos)           ///< CPU lockup reset flag

#define RCC_CSR_RMVF_Pos                (24)
#define RCC_CSR_RMVF                    (0x01U << RCC_CSR_RMVF_Pos)             ///< Remove reset flag
#define RCC_CSR_PINRSTF_Pos             (26)
#define RCC_CSR_PINRSTF                 (0x01U << RCC_CSR_PINRSTF_Pos)          ///< PIN reset flag

#define RCC_CSR_PORRSTF_Pos             (27)
#define RCC_CSR_PORRSTF                 (0x01U << RCC_CSR_PORRSTF_Pos)          ///< POR/PDR reset flag

#define RCC_CSR_SFTRSTF_Pos             (28)
#define RCC_CSR_SFTRSTF                 (0x01U << RCC_CSR_SFTRSTF_Pos)          ///< Software Reset flag

#define RCC_CSR_IWDGRSTF_Pos            (29)
#define RCC_CSR_IWDGRSTF                (0x01U << RCC_CSR_IWDGRSTF_Pos)         ///< Independent Watchdog reset flag

#define RCC_CSR_WWDGRSTF_Pos            (30)
#define RCC_CSR_WWDGRSTF                (0x01U << RCC_CSR_WWDGRSTF_Pos)         ///< Window watchdog reset flag

////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_AHBRSTR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_AHBRSTR_GPIOA_Pos       (0)
#define RCC_AHBRSTR_GPIOA           (0x01U << RCC_AHBRSTR_GPIOA_Pos)        ///< GPIOA clock reset
#define RCC_AHBRSTR_GPIOB_Pos       (1)
#define RCC_AHBRSTR_GPIOB           (0x01U << RCC_AHBRSTR_GPIOB_Pos)        ///< GPIOB clock reset
#define RCC_AHBRSTR_GPIOC_Pos       (2)
#define RCC_AHBRSTR_GPIOC           (0x01U << RCC_AHBRSTR_GPIOC_Pos)        ///< GPIOC clock reset
#define RCC_AHBRSTR_GPIOD_Pos       (3)
#define RCC_AHBRSTR_GPIOD           (0x01U << RCC_AHBRSTR_GPIOD_Pos)        ///< GPIOD clock reset
#define RCC_AHBRSTR_GPIOE_Pos       (4)
#define RCC_AHBRSTR_GPIOE           (0x01U << RCC_AHBRSTR_GPIOE_Pos)        ///< GPIOE clock reset
#define RCC_AHBRSTR_GPIOF_Pos       (5)
#define RCC_AHBRSTR_GPIOF           (0x01U << RCC_AHBRSTR_GPIOF_Pos)        ///< GPIOF clock reset
#define RCC_AHBRSTR_GPIOG_Pos       (6)
#define RCC_AHBRSTR_GPIOG           (0x01U << RCC_AHBRSTR_GPIOG_Pos)        ///< GPIOG clock reset
#define RCC_AHBRSTR_GPIOH_Pos       (7)
#define RCC_AHBRSTR_GPIOH           (0x01U << RCC_AHBRSTR_GPIOH_Pos)        ///< GPIOH clock reset
#define RCC_AHBRSTR_SDIO_Pos       (10)
#define RCC_AHBRSTR_SDIO           (0x01U << RCC_AHBRSTR_SDIO_Pos)          ///< SDIO clock reset
#define RCC_AHBRSTR_CRC_Pos        (12)
#define RCC_AHBRSTR_CRC            (0x01U << RCC_AHBRSTR_CRC_Pos)           ///< CRC clock reset
#define RCC_AHBRSTR_DMA1_Pos       (21)
#define RCC_AHBRSTR_DMA1           (0x01U << RCC_AHBRSTR_DMA1_Pos)          ///< DMA1 clock reset
#define RCC_AHBRSTR_DMA2_Pos       (22)
#define RCC_AHBRSTR_DMA2           (0x01U << RCC_AHBRSTR_DMA2_Pos)          ///< DMA2 clock reset
#define RCC_AHBRSTR_ETHMAC_Pos     (25)
#define RCC_AHBRSTR_ETHMAC         (0x01U << RCC_AHBRSTR_ETHMAC_Pos)        ///< ETHMAC clock reset
////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_SYSCFG Register Bit Definition
////////////////////////////////////////////////////////////////////////////////

#define RCC_SYSCFG_PROGCHECKEN_Pos       (0)
#define RCC_SYSCFG_PROGCHECKEN           (0x01U << RCC_SYSCFG_PROGCHECKEN_Pos)  ///< Whether to check the number in Flash when writing to Flash
#define RCC_SYSCFG_SECTOR1KCFG_Pos       (1)
#define RCC_SYSCFG_SECTOR1KCFG           (0x01U << RCC_SYSCFG_SECTOR1KCFG_Pos)  ///< The size of the Flash page when erased.
#define RCC_SYSCFG_DATAPREFETCH_Pos      (2)
#define RCC_SYSCFG_DATAPREFETCH          (0x01U << RCC_SYSCFG_DATAPREFETCH_Pos) ///< DATA prefetch module enable bit
#define RCC_SYSCFG_PAD_OSC_TRIM_Pos      (8)
#define RCC_SYSCFG_PAD_OSC_TRIM          (0x1FU << RCC_SYSCFG_PAD_OSC_TRIM_Pos) ///< Calibration value of external crystal vibration
#define RCC_SYSCFG_OSC_LPFEN_Pos         (14)
#define RCC_SYSCFG_OSC_LPFEN             (0x01U << RCC_SYSCFG_OSC_LPFEN_Pos)    ///< External crystal oscillator low pass filtering enables  
////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_CFGR2 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_CFGR2_TIMADVCKSEL_Pos         (1)
#define RCC_CFGR2_TIMADVCKSEL             (0x01U << RCC_CFGR2_TIMADVCKSEL_Pos)    ///< TIMADV_CKSEL
#define RCC_CFGR2_TIMADV_PRE_Pos          (1)    ///< 
#define RCC_CFGR2_TIMADV_PRE              (0x07U << RCC_CFGR2_TIMADV_PRE_Pos)     ///< SYSCLK's advance points are controlled by the software Frequency coefficient
#define RCC_CFGR2_FSMC_PRE_Pos            (8)
#define RCC_CFGR2_FSMC_PRE                (0x1FU << RCC_CFGR2_FSMC_PRE_Pos)       ///< FSMC Output clock frequency division factor
#define RCC_CFGR2_APB1_CLK_HV_PRE_Pos     (16)
#define RCC_CFGR2_APB1_CLK_HV_PRE         (0x0FU << RCC_CFGR2_APB1_CLK_HV_PRE_Pos) ///< APB1 Output clock frequency division factor
////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_ICSCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_ICSCR_TIME_CRS_SEL_Pos         (0)
#define RCC_ICSCR_TIME_CRS_SEL             (0x01U << RCC_ICSCR_TIME_CRS_SEL_Pos) ///< Whether to use the CRS module as source
#define RCC_ICSCR_HSI_CAL_SEL_Pos          (11)    ///< 
#define RCC_ICSCR_HSI_CAL_SEL              (0x1FU << RCC_ICSCR_HSI_CAL_SEL_Pos)  ///< Select the internal high speed clock calibration value
#define RCC_ICSCR_HSI_CAL_SFT_Pos          (16)
#define RCC_ICSCR_HSI_CAL_SFT              (0x3FU << RCC_ICSCR_HSI_CAL_SFT_Pos)  ///< Internal high-speed clock calibration
////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_PLLCFGR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_PLLCFGR_PLLSRC_Pos             (0)
#define RCC_PLLCFGR_PLLSRC                 (0x01U << RCC_PLLCFGR_PLLSRC_Pos)     ///< PLL entry clock source
#define RCC_PLLCFGR_PLLXTPRE_Pos           (1)    ///< 
#define RCC_PLLCFGR_PLLXTPRE               (0x01U << RCC_PLLCFGR_PLLXTPRE_Pos)   ///< HSE divider for PLL entry
#define RCC_PLLCFGR_PLL_ICTRL_Pos          (2)
#define RCC_PLLCFGR_PLL_ICTRL              (0x03U << RCC_PLLCFGR_PLL_ICTRL_Pos)  ///< PLL CP current control signals
#define RCC_PLLCFGR_PLL_LDS_Pos            (4)
#define RCC_PLLCFGR_PLL_LDS                (0x03U << RCC_PLLCFGR_PLL_LDS_Pos)    ///< PLL lock detector accuracy select
#define RCC_PLLCFGR_PLL_DP_Pos             (8)    ///< 
#define RCC_PLLCFGR_PLL_DP                 (0x07U << RCC_PLLCFGR_PLL_DP_Pos)     ///< PLL divider factor DP
#define RCC_PLLCFGR_PLL_DN_Pos             (16)
#define RCC_PLLCFGR_PLL_DN                 (0x7FU << RCC_PLLCFGR_PLL_DN_Pos)     ///< PLL divider factor DN
////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_HSIDLY Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_HSIDLY_HSI_EQU_CNT             (0xFFU)                               ///< HSI delay time
////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_HSEDLY Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_HSEDLY_HSI_EQU_CNT             (0xFFFFU)                               ///< HSE delay time
////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_PLLDLY Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_PLLDLY_HSI_EQU_CNT             (0xFFU)                               ///< PLL delay time



/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
