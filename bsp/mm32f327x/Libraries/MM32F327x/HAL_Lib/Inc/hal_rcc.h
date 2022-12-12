////////////////////////////////////////////////////////////////////////////////
/// @file     hal_rcc.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE RCC
///           FIRMWARE LIBRARY.
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
#ifndef __HAL_RCC_H
#define __HAL_RCC_H

// Files includes
#include "types.h"
#include "reg_common.h"
#include "mm32_reg.h"


////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup RCC_HAL
/// @brief RCC HAL modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup RCC_Exported_Types
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup RCC_Exported_Constants
/// @{


/// @}



////////////////////////////////////////////////////////////////////////////////
/// @defgroup RCC_Exported_Enumeration
/// @{


////////////////////////////////////////////////////////////////////////////////
/// @brief HSE configuration
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    RCC_HSE_OFF    = 0,             // HSE OFF
    RCC_HSE_ON     = RCC_CR_HSEON,  // HSE ON
    RCC_HSE_Bypass = RCC_CR_HSEBYP  // HSE Bypass
} RCCHSE_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief Used for flags
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    CR_REG_INDEX   = 1,     //
    BDCR_REG_INDEX = 2,     //
    CSR_REG_INDEX  = 3,     //
    RCC_FLAG_MASK  = 0x1FU  //
} RCC_RegisterFlag_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief RCC Flag
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    // Flags in the CR register
    RCC_FLAG_HSIRDY = ((u8)((CR_REG_INDEX << 5U) | RCC_CR_HSIRDY_Pos)),         ///< Internal High Speed clock ready flag
    RCC_FLAG_HSERDY = ((u8)((CR_REG_INDEX << 5U) | RCC_CR_HSERDY_Pos)),         ///< External High Speed clock ready flag

    RCC_FLAG_PLLRDY = ((u8)((CR_REG_INDEX << 5U) | RCC_CR_PLLRDY_Pos)),         ///< PLL clock ready flag

    // Flags in the CSR register
    RCC_FLAG_LSIRDY  = ((u8)((CSR_REG_INDEX << 5U) | RCC_CSR_LSIRDY_Pos)),      ///< Internal Low Speed oscillator Ready
    RCC_FLAG_PINRST  = ((u8)((CSR_REG_INDEX << 5U) | RCC_CSR_PINRSTF_Pos)),     ///< PIN reset flag
    RCC_FLAG_PORRST  = ((u8)((CSR_REG_INDEX << 5U) | RCC_CSR_PORRSTF_Pos)),     ///< POR/PDR reset flag
    RCC_FLAG_SFTRST  = ((u8)((CSR_REG_INDEX << 5U) | RCC_CSR_SFTRSTF_Pos)),     ///< Software Reset flag
    RCC_FLAG_IWDGRST = ((u8)((CSR_REG_INDEX << 5U) | RCC_CSR_IWDGRSTF_Pos)),    ///< Independent Watchdog reset flag
    RCC_FLAG_WWDGRST = ((u8)((CSR_REG_INDEX << 5U) | RCC_CSR_WWDGRSTF_Pos)),    ///< Window watchdog reset flag

    // Flags in the BDCR register
    RCC_FLAG_LSERDY = ((u8)((BDCR_REG_INDEX << 5U) | RCC_BDCR_LSERDY_Pos))      ///< External Low Speed oscillator Ready
} RCC_FLAG_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief System clock source
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    RCC_HSI = 0,  // Set HSI as systemCLOCK
    RCC_HSE = 1,  // Set HSE as systemCLOCK
    RCC_PLL = 2,   // Set PLL as systemCLOCK
    RCC_LSI = 3  // Set LSI as systemCLOCK
} SYSCLK_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief PLL entry clock source
////////////////////////////////////////////////////////////////////////////////

typedef enum {
    RCC_HSI_Div4 = 0,
    RCC_HSI_Div = 0,
    RCC_HSE_Div1 = RCC_PLLCFGR_PLLSRC,
    RCC_HSE_Div2 = (RCC_PLLCFGR_PLLXTPRE | RCC_PLLCFGR_PLLSRC),
} RCC_PLLSource_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief PLL multiplication factor
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    RCC_PLLMul_2  = 0x00000000U,
    RCC_PLLMul_3  = 0x00040000U,
    RCC_PLLMul_4  = 0x00080000U,
    RCC_PLLMul_5  = 0x000C0000U,
    RCC_PLLMul_6  = 0x00100000U,
    RCC_PLLMul_7  = 0x00140000U,
    RCC_PLLMul_8  = 0x00180000U,
    RCC_PLLMul_9  = 0x001C0000U,
    RCC_PLLMul_10 = 0x00200000U,
    RCC_PLLMul_11 = 0x00240000U,
    RCC_PLLMul_12 = 0x00280000U,
    RCC_PLLMul_13 = 0x002C0000U,
    RCC_PLLMul_14 = 0x00300000U,
    RCC_PLLMul_15 = 0x00340000U,
    RCC_PLLMul_16 = 0x00380000U
} RCC_PLLMul_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief AHB clock source
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    RCC_SYSCLK_Div1   = RCC_CFGR_HPRE_DIV1,
    RCC_SYSCLK_Div2   = RCC_CFGR_HPRE_DIV2,
    RCC_SYSCLK_Div4   = RCC_CFGR_HPRE_DIV4,
    RCC_SYSCLK_Div8   = RCC_CFGR_HPRE_DIV8,
    RCC_SYSCLK_Div16  = RCC_CFGR_HPRE_DIV16,
    RCC_SYSCLK_Div64  = RCC_CFGR_HPRE_DIV64,
    RCC_SYSCLK_Div128 = RCC_CFGR_HPRE_DIV128,
    RCC_SYSCLK_Div256 = RCC_CFGR_HPRE_DIV256,
    RCC_SYSCLK_Div512 = RCC_CFGR_HPRE_DIV512
} RCC_AHB_CLK_TypeDef;
////////////////////////////////////////////////////////////////////////////////
/// @brief APB1 and APB2clock source
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    RCC_HCLK_Div1  = RCC_CFGR_PPRE1_DIV1,
    RCC_HCLK_Div2  = RCC_CFGR_PPRE1_DIV2,
    RCC_HCLK_Div4  = RCC_CFGR_PPRE1_DIV4,
    RCC_HCLK_Div8  = RCC_CFGR_PPRE1_DIV8,
    RCC_HCLK_Div16 = RCC_CFGR_PPRE1_DIV16
} RCC_APB1_APB2_CLK_TypeDef;
////////////////////////////////////////////////////////////////////////////////
/// @brief USB Device clock source
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    RCC_USBCLKSource_PLLCLK_Div1 = 0,
    RCC_USBCLKSource_PLLCLK_Div2 = 1,
    RCC_USBCLKSource_PLLCLK_Div3 = 2,
    RCC_USBCLKSource_PLLCLK_Div4 = 3
} RCC_USBCLKSOURCE_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC clock source
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    RCC_PCLK2_Div2 = (0x00000000),
    RCC_PCLK2_Div4 = (0x00004000),
    RCC_PCLK2_Div6 = (0x00008000),
    RCC_PCLK2_Div8 = (0x0000C000)
} RCC_ADCCLKSOURCE_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief LSE configuration
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    RCC_LSE_OFF    = 0,               // LSE OFF
    RCC_LSE_ON     = RCC_BDCR_LSEON,  // LSE ON
    RCC_LSE_Bypass = RCC_BDCR_LSEBYP  // LSE Bypass
} RCC_LSE_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief RTC clock source
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    RCC_RTCCLKSource_LSE        = RCC_BDCR_RTCSEL_LSE,
    RCC_RTCCLKSource_LSI        = RCC_BDCR_RTCSEL_LSI,
    RCC_RTCCLKSource_HSE_Div128 = RCC_BDCR_RTCSEL_HSE
} RCC_RTCCLKSOURCE_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief Clock source to output on MCO pin
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    RCC_MCO_NoClock = RCC_CFGR_MCO_NOCLOCK,
    RCC_MCO_LSI     = RCC_CFGR_MCO_LSI,
    RCC_MCO_LSE = RCC_CFGR_MCO_LSE,
    RCC_MCO_SYSCLK = RCC_CFGR_MCO_SYSCLK,
    RCC_MCO_HSI    = RCC_CFGR_MCO_HSI,
    RCC_MCO_HSE    = RCC_CFGR_MCO_HSE,
    RCC_MCO_PLLCLK_Div2 = RCC_CFGR_MCO_PLL
} RCC_MCO_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief RCC Interrupt source
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    RCC_IT_LSIRDY = RCC_CIR_LSIRDYF,
    RCC_IT_LSERDY = RCC_CIR_LSERDYF,
    RCC_IT_HSIRDY = RCC_CIR_HSIRDYF,
    RCC_IT_HSERDY = RCC_CIR_HSERDYF,
    RCC_IT_PLLRDY = RCC_CIR_PLLRDYF,
    RCC_IT_CSS = RCC_CIR_CSSF
} RCC_IT_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief RCC clock frequency type definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    u32 SYSCLK_Frequency;                                                       ///< returns SYSCLK clock frequency.
    u32 HCLK_Frequency;                                                         ///< returns hclk clock frequency.
    u32 PCLK1_Frequency;                                                        ///< returns PCLK1 clock frequency.
    u32 PCLK2_Frequency;                                                        ///< returns PCLK2 clock frequency.
    u32 ADCCLK_Frequency;                                                       ///< returns ADCCLK clock frequency.
} RCC_ClocksTypeDef;
/// @}

/// @}


////////////////////////////////////////////////////////////////////////////////
/// @defgroup RCC_Exported_Variables
/// @{
#ifdef _HAL_RCC_C_

#define GLOBAL
#else
#define GLOBAL extern
#endif

#undef GLOBAL
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup RCC_Exported_Functions
/// @{
void RCC_DeInit(void);
void RCC_HSEConfig(RCCHSE_TypeDef state);
void RCC_HSICmd(FunctionalState state);
void RCC_SYSCLKConfig(SYSCLK_TypeDef sys_clk_src);
void RCC_PLLDMDNConfig(u32 plldn, u32 plldm);
void RCC_PLLConfig(RCC_PLLSource_TypeDef pll_src, RCC_PLLMul_TypeDef pll_mul);
void RCC_PLLCmd(FunctionalState state);
void RCC_HCLKConfig(RCC_AHB_CLK_TypeDef sys_clk);
void RCC_PCLK1Config(RCC_APB1_APB2_CLK_TypeDef hclk);
void RCC_PCLK2Config(RCC_APB1_APB2_CLK_TypeDef hclk);
void RCC_USBCLKConfig(RCC_USBCLKSOURCE_TypeDef usb_clk_src);
void RCC_ADCCLKConfig(RCC_ADCCLKSOURCE_TypeDef pclk2);
void RCC_LSICmd(FunctionalState state);

void RCC_RTCCLKCmd(FunctionalState state);
void RCC_LSEConfig(RCC_LSE_TypeDef state);
void RCC_RTCCLKConfig(RCC_RTCCLKSOURCE_TypeDef rtc_clk_src);
void RCC_BackupResetCmd(FunctionalState state);

void RCC_GetClocksFreq(RCC_ClocksTypeDef* clk);
void RCC_AHBPeriphClockCmd(u32 ahb_periph, FunctionalState state);
void RCC_AHB2PeriphClockCmd(u32 ahb_periph, FunctionalState state);
void RCC_AHB3PeriphClockCmd(u32 ahb_periph, FunctionalState state);
void RCC_AHBPeriphResetCmd(u32 ahb_periph, FunctionalState state);
void RCC_AHB2PeriphResetCmd(u32 ahb_periph, FunctionalState state);
void RCC_AHB3PeriphResetCmd(u32 ahb_periph, FunctionalState state);
void RCC_APB2PeriphClockCmd(u32 apb2_periph, FunctionalState state);
void RCC_APB1PeriphClockCmd(u32 apb1_periph, FunctionalState state);
void RCC_APB2PeriphResetCmd(u32 apb2_periph, FunctionalState state);
void RCC_APB1PeriphResetCmd(u32 apb1_periph, FunctionalState state);

void RCC_ClockSecuritySystemCmd(FunctionalState state);
void RCC_MCOConfig(RCC_MCO_TypeDef mco_src);
void RCC_ClearFlag(void);
void RCC_ITConfig(RCC_IT_TypeDef it, FunctionalState state);
void RCC_ClearITPendingBit(u8 it);

u8  RCC_GetSYSCLKSource(void);
u32 RCC_GetSysClockFreq(void);
u32 RCC_GetHCLKFreq(void);

u32 RCC_GetPCLK1Freq(void);
u32 RCC_GetPCLK2Freq(void);
FlagStatus  RCC_GetFlagStatus(RCC_FLAG_TypeDef flag);
ErrorStatus RCC_WaitForHSEStartUp(void);
ErrorStatus RCC_WaitForFlagStartUp(RCC_FLAG_TypeDef flag);
ITStatus    RCC_GetITStatus(RCC_IT_TypeDef it);

////////////////////////////////////////////////////////////////////////////////
//          Extended function interface
////////////////////////////////////////////////////////////////////////////////
//ErrorStatus exRCC_Init(RCCInitStruct_TypeDef* para);
void exRCC_SystickDisable(void);
void exRCC_SystickEnable(u32 sys_tick_period);
void exRCC_APB1PeriphReset(u32 apb1_periph);
void exRCC_APB2PeriphReset(u32 apb2_periph);
void exRCC_BackupReset(void);
void RCC_ADC_ClockCmd(ADC_TypeDef* peripheral, FunctionalState state);
void RCC_GPIO_ClockCmd(GPIO_TypeDef* peripheral, FunctionalState state);
/// @}

/// @}

/// @}




////////////////////////////////////////////////////////////////////////////////
#endif // __HAL_RCC_H 
////////////////////////////////////////////////////////////////////////////////


