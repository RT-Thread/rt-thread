/**
  ******************************************************************************
  * @file    tae32g58xx_ll_rcu.h
  * @author  MCD Application Team
  * @brief   Header file for RCU LL module
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32G58XX_LL_RCU_H_
#define _TAE32G58XX_LL_RCU_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup RCU_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup RCU_LL_Exported_Macros RCU LL Exported Macros
  * @brief    RCU LL Exported Macros
  * @{
  */

/**
  * @brief  PLL0 Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PLL0_En(__RCU__)                   SET_BIT((__RCU__)->PLL0CR, RCU_PLL0CR_EN_Msk)

/**
  * @brief  PLL0 Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PLL0_Dis(__RCU__)                  CLEAR_BIT((__RCU__)->PLL0CR, RCU_PLL0CR_EN_Msk)

/**
  * @brief  Judge PLL0 has Locked or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 PLL0 hasn't Locked
  * @retval 1 PLL0 has Locked
  */
#define __LL_RCU_PLL0_IsLocked(__RCU__)             READ_BIT_SHIFT((__RCU__)->PLL0CR, RCU_PLL0CR_LKF_Msk, RCU_PLL0CR_LKF_Pos)

/**
  * @brief  PLL0 GVCO Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param vco PLL0 GVCO
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_RCU_PLL0_GVCO_Set(__RCU__, vco)        \
        MODIFY_REG((__RCU__)->PLL0CR, 0xc000UL, (((vco) & 0x3UL) << (14UL)))

/**
  * @brief  PLL0 Pre Div Set to 1
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PLL0_PreDiv_1(__RCU__)             CLEAR_BIT((__RCU__)->PLL0CR, RCU_PLL0CR_RFD_Msk)

/**
  * @brief  PLL0 Pre Div Set to 2
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PLL0_PreDiv_2(__RCU__)             SET_BIT((__RCU__)->PLL0CR, RCU_PLL0CR_RFD_Msk)

/**
  * @brief  PLL0 LPF 12M High Set
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PLL0_12MHigh_Set(__RCU__)          SET_BIT((__RCU__)->PLL0CR, RCU_PLL0CR_LPF_Msk)

/**
  * @brief  PLL0 LPF 12M Low Set
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PLL0_12MLow_Set(__RCU__)           CLEAR_BIT((__RCU__)->PLL0CR, RCU_PLL0CR_LPF_Msk)

/**
  * @brief  PLL0 Band Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  band PLL0 Band
  * @return None
  */
#define __LL_RCU_PLL0_Band_Set(__RCU__, band)       \
        MODIFY_REG((__RCU__)->PLL0CR, RCU_PLL0CR_BDS_Msk, (((band) & 0x3UL) << RCU_PLL0CR_BDS_Pos))

/**
  * @brief  PLL0 Update Generate
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PLL0_UpdateGen(__RCU__)            SET_BIT((__RCU__)->PLL0CR, RCU_PLL0CR_UG_Msk)

/**
  * @brief  PLL0 AutoReload Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PLL0_AutoReload_En(__RCU__)        SET_BIT((__RCU__)->PLL0CR, RCU_PLL0CR_ARE_Msk)

/**
  * @brief  PLL0 AutoReload Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PLL0_AutoReload_Dis(__RCU__)       CLEAR_BIT((__RCU__)->PLL0CR, RCU_PLL0CR_ARE_Msk)

/**
  * @brief  PLL0 Ref CLK Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param ref_clk PLL0 Ref CLK
  * @return None
  */
#define __LL_RCU_PLL0_RefClk_Set(__RCU__, ref_clk)  \
        MODIFY_REG((__RCU__)->PLL0CR, RCU_PLL0CR_RCS_Msk, (((ref_clk) & 0x3U) << RCU_PLL0CR_RCS_Pos))


/**
  * @brief  PLL0 Div Integer Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  integer PLL0 Div Integer
  * @return None
  */
#define __LL_RCU_PLL0_DivInt_Set(__RCU__, integer)  \
        MODIFY_REG((__RCU__)->PLL0FR, RCU_PLL0FR_INT_Msk, ((integer & 0x3fffUL) << RCU_PLL0FR_INT_Pos))

/**
  * @brief  PLL0 Div Fraction Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  frac PLL0 Div Fraction
  * @return None
  */
#define __LL_RCU_PLL0_DivFrac_Set(__RCU__, frac)    \
        MODIFY_REG((__RCU__)->PLL0FR, RCU_PLL0FR_FRAC_Msk, ((frac & 0xffffUL) << RCU_PLL0FR_FRAC_Pos))

/**
  * @brief  Lowpower Auto Clock Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_RCU_LowPowerAutoClk_En(__RCU__)        SET_BIT((__RCU__)->CCR, 0x100000UL)

/**
  * @brief  Lowpower Auto Clock Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_RCU_LowPowerAutoClk_Dis(__RCU__)       CLEAR_BIT((__RCU__)->CCR, 0x100000UL)

/**
  * @brief  AHB1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_RCU_AHB1Clk_En(__RCU__)                SET_BIT((__RCU__)->CCR, 0x80000UL)

/**
  * @brief  AHB1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_RCU_AHB1Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->CCR, 0x80000UL)

/**
  * @brief  AHB0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_RCU_AHB0Clk_En(__RCU__)                SET_BIT((__RCU__)->CCR, 0x40000UL)

/**
  * @brief  AHB0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_RCU_AHB0Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->CCR, 0x40000UL)

/**
  * @brief  APB1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_RCU_APB1Clk_En(__RCU__)                SET_BIT((__RCU__)->CCR, 0x20000UL)

/**
  * @brief  APB1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_RCU_APB1Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->CCR, 0x20000UL)

/**
  * @brief  APB0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_RCU_APB0Clk_En(__RCU__)                SET_BIT((__RCU__)->CCR, 0x10000UL)

/**
  * @brief  APB0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_RCU_APB0Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->CCR, 0x10000UL)

/**
  * @brief  APB1 CLK Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div APB1 Div
  * @return None
  */
#define __LL_RCU_APB1ClkDiv_Set(__RCU__, div)       \
        MODIFY_REG((__RCU__)->CCR, RCU_CCR_P1PSC_Msk, (((div-1) & 0xfUL) << RCU_CCR_P1PSC_Pos))

/**
  * @brief  APB1 CLK Div Get
  * @param  __RCU__ Specifies RCU peripheral
  * @return APB1 Div
  */
#define __LL_RCU_APB1ClkDiv_Get(__RCU__)            (READ_BIT_SHIFT((__RCU__)->CCR, RCU_CCR_P1PSC_Msk, RCU_CCR_P1PSC_Pos) + 1)

/**
  * @brief  APB0 CLK Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div APB0 Div
  * @return None
  */
#define __LL_RCU_APB0ClkDiv_Set(__RCU__, div)       \
        MODIFY_REG((__RCU__)->CCR, RCU_CCR_P0PSC_Msk, (((div-1) & 0xfUL) << RCU_CCR_P0PSC_Pos))

/**
  * @brief  APB0 CLK Div Get
  * @param  __RCU__ Specifies RCU peripheral
  * @return APB0 Div
  */
#define __LL_RCU_APB0ClkDiv_Get(__RCU__)            (READ_BIT_SHIFT((__RCU__)->CCR, RCU_CCR_P0PSC_Msk, RCU_CCR_P0PSC_Pos) + 1)

/**
  * @brief  AHB CLK Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div AHB Div
  * @return None
  */
#define __LL_RCU_AHBClkDiv_Set(__RCU__, div)        \
        MODIFY_REG((__RCU__)->CCR, RCU_CCR_HPSC_Msk, (((div-1) & 0x3fUL) << RCU_CCR_HPSC_Pos))

/**
  * @brief  AHB CLK Div Get
  * @param  __RCU__ Specifies RCU peripheral
  * @return AHB Div
  */
#define __LL_RCU_AHBClkDiv_Get(__RCU__)             (READ_BIT_SHIFT((__RCU__)->CCR, RCU_CCR_HPSC_Msk, RCU_CCR_HPSC_Pos) + 1)

/**
  * @brief  SYSCLK Source Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  src SYSCLK Source
  * @return None
  */
#define __LL_RCU_SysClkSrc_Set(__RCU__, src)        \
        MODIFY_REG((__RCU__)->CCR, RCU_CCR_SCS_Msk, (((src) & 0x3U) << RCU_CCR_SCS_Pos))

/**
  * @brief  SYSCLK Source Get
  * @param  __RCU__ Specifies RCU peripheral
  * @return SYSCLK Source
  */
#define __LL_RCU_SysClkSrc_Get(__RCU__)             READ_BIT_SHIFT((__RCU__)->CCR, RCU_CCR_SCS_Msk, RCU_CCR_SCS_Pos)


/**
  * @brief  LPTMR CLK Source Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  src LPTMR CLK Source
  * @return None
  */
#define __LL_RCU_LPTMRClkSrc_Set(__RCU__, src)        \
        MODIFY_REG((__RCU__)->PCSR, RCU_PCSR_TMR6CS_Msk, (((src) & 0x3U) << RCU_PCSR_TMR6CS_Pos))

/**
  * @brief  LPTMR CLK Source Get
  * @param  __RCU__ Specifies RCU peripheral
  * @return LPTMR CLK Source
  */
#define __LL_RCU_LPTMRClkSrc_Get(__RCU__)             \
        READ_BIT_SHIFT((__RCU__)->PCSR, RCU_PCSR_TMR6CS_Msk, RCU_PCSR_TMR6CS_Pos)

/**
  * @brief  CAN CLK Source Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  src CAN CLK Source
  * @return None
  */
#define __LL_RCU_CANClkSrc_Set(__RCU__, src)        \
        MODIFY_REG((__RCU__)->PCSR, RCU_PCSR_CANCS_Msk, (((src) & 0x3U) << RCU_PCSR_CANCS_Pos))

/**
  * @brief  CAN CLK Source Get
  * @param  __RCU__ Specifies RCU peripheral
  * @return CAN CLK Source
  */
#define __LL_RCU_CANClkSrc_Get(__RCU__)             \
        READ_BIT_SHIFT((__RCU__)->PCSR, RCU_PCSR_CANCS_Msk, RCU_PCSR_CANCS_Pos)

/**
  * @brief  USB CLK Source Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  src USB CLK Source
  * @return None
  */
#define __LL_RCU_USBClkSrc_Set(__RCU__, src)        \
        MODIFY_REG((__RCU__)->PCSR, RCU_PCSR_USBCS_Msk, (((src) & 0x3U) << RCU_PCSR_USBCS_Pos))

/**
  * @brief  USB CLK Source Get
  * @param  __RCU__ Specifies RCU peripheral
  * @return USB CLK Source
  */
#define __LL_RCU_USBClkSrc_Get(__RCU__)             \
        READ_BIT_SHIFT((__RCU__)->PCSR, RCU_PCSR_USBCS_Msk, RCU_PCSR_USBCS_Pos)

/**
  * @brief  ADC CLK Source Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  src ADC CLK Source
  * @return None
  */
#define __LL_RCU_ADCClkSrc_Set(__RCU__, src)        \
        MODIFY_REG((__RCU__)->PCSR, RCU_PCSR_ADCCS_Msk, (((src) & 0x3U) << RCU_PCSR_ADCCS_Pos))

/**
  * @brief  ADC CLK Source Get
  * @param  __RCU__ Specifies RCU peripheral
  * @return ADC CLK Source
  */
#define __LL_RCU_ADCClkSrc_Get(__RCU__)             \
        READ_BIT_SHIFT((__RCU__)->PCSR, RCU_PCSR_ADCCS_Msk, RCU_PCSR_ADCCS_Pos)

/**
  * @brief  HRPWM CLK Source Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  src HRPWM CLK Source
  * @return None
  */
#define __LL_RCU_HRPWMClkSrc_Set(__RCU__, src)      \
        MODIFY_REG((__RCU__)->PCSR, RCU_PCSR_PWMCS_Msk, (((src) & 0x3U) << RCU_PCSR_PWMCS_Pos))

/**
  * @brief  HRPWM CLK Source Get
  * @param  __RCU__ Specifies RCU peripheral
  * @return HRPWM CLK Source
  */
#define __LL_RCU_HRPWMClkSrc_Get(__RCU__)           \
        READ_BIT_SHIFT((__RCU__)->PCSR, RCU_PCSR_PWMCS_Msk, RCU_PCSR_PWMCS_Pos)


/**
  * @brief  GPIOD Debounce CLK Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div GPIOD Debounce CLK Div
  * @return None
  */
#define __LL_RCU_GPIODDbcClkDiv_Set(__RCU__, div)   \
        MODIFY_REG((__RCU__)->PCDR0, RCU_PCDR0_PDDIV_Msk, (((div-1) & 0xffUL) << RCU_PCDR0_PDDIV_Pos))

/**
  * @brief  GPIOC Debounce CLK Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div GPIOC Debounce CLK Div
  * @return None
  */
#define __LL_RCU_GPIOCDbcClkDiv_Set(__RCU__, div)   \
        MODIFY_REG((__RCU__)->PCDR0, RCU_PCDR0_PCDIV_Msk, (((div-1) & 0xffUL) << RCU_PCDR0_PCDIV_Pos))

/**
  * @brief  GPIOB Debounce CLK Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div GPIOB Debounce CLK Div
  * @return None
  */
#define __LL_RCU_GPIOBDbcClkDiv_Set(__RCU__, div)   \
        MODIFY_REG((__RCU__)->PCDR0, RCU_PCDR0_PBDIV_Msk, (((div-1) & 0xffUL) << RCU_PCDR0_PBDIV_Pos))

/**
  * @brief  GPIOA Debounce CLK Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div GPIOA Debounce CLK Div
  * @return None
  */
#define __LL_RCU_GPIOADbcClkDiv_Set(__RCU__, div)   \
        MODIFY_REG((__RCU__)->PCDR0, RCU_PCDR0_PADIV_Msk, (((div-1) & 0xffUL) << RCU_PCDR0_PADIV_Pos))


/**
  * @brief  GPIOE Debounce CLK Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div GPIOE Debounce CLK Div
  * @return None
  */
#define __LL_RCU_GPIOEDbcClkDiv_Set(__RCU__, div)   \
        MODIFY_REG((__RCU__)->PCDR1, RCU_PCDR1_PEDIV_Msk, (((div-1) & 0xffUL) << RCU_PCDR1_PEDIV_Pos))

/**
  * @brief  GPIOF Debounce CLK Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div GPIOF Debounce CLK Div
  * @return None
  */
#define __LL_RCU_GPIOFDbcClkDiv_Set(__RCU__, div)   \
        MODIFY_REG((__RCU__)->PCDR1, RCU_PCDR1_PFDIV_Msk, (((div-1) & 0xffUL) << RCU_PCDR1_PFDIV_Pos))


/**
  * @brief  CAN Clk Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div CAN Clk Div
  * @return None
  */
#define __LL_RCU_CANClkDiv_Set(__RCU__, div)        \
        MODIFY_REG((__RCU__)->PCDR2, RCU_PCDR2_CANDIV_Msk, (((div-1) & 0xfUL) << RCU_PCDR2_CANDIV_Pos))

/**
  * @brief  CAN Clk Div Get
  * @param  __RCU__ Specifies RCU peripheral
  * @return CAN Clk Div
  */
#define __LL_RCU_CANClkDiv_Get(__RCU__)             \
        (READ_BIT_SHIFT((__RCU__)->PCDR2, RCU_PCDR2_CANDIV_Msk, RCU_PCDR2_CANDIV_Pos) + 1)

/**
  * @brief  USB Clk Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div USB Clk Div
  * @return None
  */
#define __LL_RCU_USBClkDiv_Set(__RCU__, div)        \
        MODIFY_REG((__RCU__)->PCDR2, RCU_PCDR2_USBDIV_Msk, (((div-1) & 0xfUL) << RCU_PCDR2_USBDIV_Pos))

/**
  * @brief  USB Clk Div Get
  * @param  __RCU__ Specifies RCU peripheral
  * @return USB Clk Div
  */
#define __LL_RCU_USBClkDiv_Get(__RCU__)             \
        (READ_BIT_SHIFT((__RCU__)->PCDR2, RCU_PCDR2_USBDIV_Msk, RCU_PCDR2_USBDIV_Pos) + 1)

/**
  * @brief  ADC Clk Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div ADC Clk Div
  * @return None
  */
#define __LL_RCU_ADCClkDiv_Set(__RCU__, div)        \
        MODIFY_REG((__RCU__)->PCDR2, RCU_PCDR2_ADCDIV_Msk, (((div-1) & 0xfUL) << RCU_PCDR2_ADCDIV_Pos))

/**
  * @brief  ADC Clk Div Get
  * @param  __RCU__ Specifies RCU peripheral
  * @return ADC Clk Div
  */
#define __LL_RCU_ADCClkDiv_Get(__RCU__)             \
        (READ_BIT_SHIFT((__RCU__)->PCDR2, RCU_PCDR2_ADCDIV_Msk, RCU_PCDR2_ADCDIV_Pos) + 1)

/**
  * @brief  HRPWM Clk Div Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  div HRPWM Clk Div
  * @return None
  */
#define __LL_RCU_HRPWMClkDiv_Set(__RCU__, div)      \
        MODIFY_REG((__RCU__)->PCDR2, RCU_PCDR2_PWMDIV_Msk, (((div-1) & 0xfUL) << RCU_PCDR2_PWMDIV_Pos))

/**
  * @brief  HRPWM Clk Div Get
  * @param  __RCU__ Specifies RCU peripheral
  * @return HRPWM Clk Div
  */
#define __LL_RCU_HRPWMClkDiv_Get(__RCU__)           \
        (READ_BIT_SHIFT((__RCU__)->PCDR2, RCU_PCDR2_PWMDIV_Msk, RCU_PCDR2_PWMDIV_Pos) + 1)


/**
  * @brief  TMR6 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR6FunClk_En(__RCU__)             SET_BIT((__RCU__)->PCENR, RCU_PCENR_TMR6FEN_Msk)

/**
  * @brief  TMR6 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR6FunClk_Dis(__RCU__)            CLEAR_BIT((__RCU__)->PCENR, RCU_PCENR_TMR6FEN_Msk)

/**
  * @brief  Judge is TMR6 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsTMR6FunClkEn(__RCU__)            READ_BIT_SHIFT((__RCU__)->PCENR, RCU_PCENR_TMR6FEN_Msk, RCU_PCENR_TMR6FEN_Pos)

/**
  * @brief  CAN1 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CAN1FunClk_En(__RCU__)             SET_BIT((__RCU__)->PCENR, RCU_PCENR_CAN1FEN_Msk)

/**
  * @brief  CAN1 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CAN1FunClk_Dis(__RCU__)            CLEAR_BIT((__RCU__)->PCENR, RCU_PCENR_CAN1FEN_Msk)

/**
  * @brief  Judge is CAN1 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsCAN1FunClkEn(__RCU__)            READ_BIT_SHIFT((__RCU__)->PCENR, RCU_PCENR_CAN1FEN_Msk, RCU_PCENR_CAN1FEN_Pos)

/**
  * @brief  CAN0 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CAN0FunClk_En(__RCU__)             SET_BIT((__RCU__)->PCENR, RCU_PCENR_CAN0FEN_Msk)

/**
  * @brief  CAN0 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CAN0FunClk_Dis(__RCU__)            CLEAR_BIT((__RCU__)->PCENR, RCU_PCENR_CAN0FEN_Msk)

/**
  * @brief  Judge is CAN0 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsCAN0FunClkEn(__RCU__)            READ_BIT_SHIFT((__RCU__)->PCENR, RCU_PCENR_CAN0FEN_Msk, RCU_PCENR_CAN0FEN_Pos)

/**
  * @brief  USB Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_USBFunClk_En(__RCU__)              SET_BIT((__RCU__)->PCENR, RCU_PCENR_USBFEN_Msk)

/**
  * @brief  USB Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_USBFunClk_Dis(__RCU__)             CLEAR_BIT((__RCU__)->PCENR, RCU_PCENR_USBFEN_Msk)

/**
  * @brief  Judge is USB Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsUSBFunClkEn(__RCU__)             READ_BIT_SHIFT((__RCU__)->PCENR, RCU_PCENR_USBFEN_Msk, RCU_PCENR_USBFEN_Pos)

/**
  * @brief  HRPWM7 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM7FunClk_En(__RCU__)           SET_BIT((__RCU__)->PCENR, RCU_PCENR_PWM7FEN_Msk)

/**
  * @brief  HRPWM7 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM7FunClk_Dis(__RCU__)          CLEAR_BIT((__RCU__)->PCENR, RCU_PCENR_PWM7FEN_Msk)

/**
  * @brief  Judge is HRPWM7 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsHRPWM7FunClkEn(__RCU__)          READ_BIT_SHIFT((__RCU__)->PCENR, RCU_PCENR_PWM7FEN_Msk, RCU_PCENR_PWM7FEN_Pos)

/**
  * @brief  HRPWM6 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM6FunClk_En(__RCU__)           SET_BIT((__RCU__)->PCENR, RCU_PCENR_PWM6FEN_Msk)

/**
  * @brief  HRPWM6 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM6FunClk_Dis(__RCU__)          CLEAR_BIT((__RCU__)->PCENR, RCU_PCENR_PWM6FEN_Msk)

/**
  * @brief  Judge is HRPWM6 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsHRPWM6FunClkEn(__RCU__)          READ_BIT_SHIFT((__RCU__)->PCENR, RCU_PCENR_PWM6FEN_Msk, RCU_PCENR_PWM6FEN_Pos)

/**
  * @brief  HRPWM5 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM5FunClk_En(__RCU__)           SET_BIT((__RCU__)->PCENR, RCU_PCENR_PWM5FEN_Msk)

/**
  * @brief  HRPWM5 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM5FunClk_Dis(__RCU__)          CLEAR_BIT((__RCU__)->PCENR, RCU_PCENR_PWM5FEN_Msk)

/**
  * @brief  Judge is HRPWM5 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsHRPWM5FunClkEn(__RCU__)          READ_BIT_SHIFT((__RCU__)->PCENR, RCU_PCENR_PWM5FEN_Msk, RCU_PCENR_PWM5FEN_Pos)

/**
  * @brief  HRPWM4 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM4FunClk_En(__RCU__)           SET_BIT((__RCU__)->PCENR, RCU_PCENR_PWM4FEN_Msk)

/**
  * @brief  HRPWM4 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM4FunClk_Dis(__RCU__)          CLEAR_BIT((__RCU__)->PCENR, RCU_PCENR_PWM4FEN_Msk)

/**
  * @brief  Judge is HRPWM4 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsHRPWM4FunClkEn(__RCU__)          READ_BIT_SHIFT((__RCU__)->PCENR, RCU_PCENR_PWM4FEN_Msk, RCU_PCENR_PWM4FEN_Pos)

/**
  * @brief  HRPWM3 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM3FunClk_En(__RCU__)           SET_BIT((__RCU__)->PCENR, RCU_PCENR_PWM3FEN_Msk)

/**
  * @brief  HRPWM3 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM3FunClk_Dis(__RCU__)          CLEAR_BIT((__RCU__)->PCENR, RCU_PCENR_PWM3FEN_Msk)

/**
  * @brief  Judge is HRPWM3 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsHRPWM3FunClkEn(__RCU__)          READ_BIT_SHIFT((__RCU__)->PCENR, RCU_PCENR_PWM3FEN_Msk, RCU_PCENR_PWM3FEN_Pos)

/**
  * @brief  HRPWM2 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM2FunClk_En(__RCU__)           SET_BIT((__RCU__)->PCENR, RCU_PCENR_PWM2FEN_Msk)

/**
  * @brief  HRPWM2 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM2FunClk_Dis(__RCU__)          CLEAR_BIT((__RCU__)->PCENR, RCU_PCENR_PWM2FEN_Msk)

/**
  * @brief  Judge is HRPWM2 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsHRPWM2FunClkEn(__RCU__)          READ_BIT_SHIFT((__RCU__)->PCENR, RCU_PCENR_PWM2FEN_Msk, RCU_PCENR_PWM2FEN_Pos)

/**
  * @brief  HRPWM1 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM1FunClk_En(__RCU__)           SET_BIT((__RCU__)->PCENR, RCU_PCENR_PWM1FEN_Msk)

/**
  * @brief  HRPWM1 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM1FunClk_Dis(__RCU__)          CLEAR_BIT((__RCU__)->PCENR, RCU_PCENR_PWM1FEN_Msk)

/**
  * @brief  Judge is HRPWM1 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsHRPWM1FunClkEn(__RCU__)          READ_BIT_SHIFT((__RCU__)->PCENR, RCU_PCENR_PWM1FEN_Msk, RCU_PCENR_PWM1FEN_Pos)

/**
  * @brief  HRPWM0 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM0FunClk_En(__RCU__)           SET_BIT((__RCU__)->PCENR, RCU_PCENR_PWM0FEN_Msk)

/**
  * @brief  HRPWM0 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM0FunClk_Dis(__RCU__)          CLEAR_BIT((__RCU__)->PCENR, RCU_PCENR_PWM0FEN_Msk)

/**
  * @brief  Judge is HRPWM0 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsHRPWM0FunClkEn(__RCU__)          READ_BIT_SHIFT((__RCU__)->PCENR, RCU_PCENR_PWM0FEN_Msk, RCU_PCENR_PWM0FEN_Pos)

/**
  * @brief  ADC3 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_ADC3FunClk_En(__RCU__)             SET_BIT((__RCU__)->PCENR, RCU_PCENR_ADC3FEN_Msk)

/**
  * @brief  ADC3 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_ADC3FunClk_Dis(__RCU__)            CLEAR_BIT((__RCU__)->PCENR, RCU_PCENR_ADC3FEN_Msk)

/**
  * @brief  Judge is ADC3 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsADC3FunClkEn(__RCU__)            READ_BIT_SHIFT((__RCU__)->PCENR, RCU_PCENR_ADC3FEN_Msk, RCU_PCENR_ADC3FEN_Pos)

/**
  * @brief  ADC2 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_ADC2FunClk_En(__RCU__)             SET_BIT((__RCU__)->PCENR, RCU_PCENR_ADC2FEN_Msk)

/**
  * @brief  ADC2 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_ADC2FunClk_Dis(__RCU__)            CLEAR_BIT((__RCU__)->PCENR, RCU_PCENR_ADC2FEN_Msk)

/**
  * @brief  Judge is ADC2 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsADC2FunClkEn(__RCU__)            READ_BIT_SHIFT((__RCU__)->PCENR, RCU_PCENR_ADC2FEN_Msk, RCU_PCENR_ADC2FEN_Pos)

/**
  * @brief  ADC1 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_ADC1FunClk_En(__RCU__)             SET_BIT((__RCU__)->PCENR, RCU_PCENR_ADC1FEN_Msk)

/**
  * @brief  ADC1 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_ADC1FunClk_Dis(__RCU__)            CLEAR_BIT((__RCU__)->PCENR, RCU_PCENR_ADC1FEN_Msk)

/**
  * @brief  Judge is ADC1 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsADC1FunClkEn(__RCU__)            READ_BIT_SHIFT((__RCU__)->PCENR, RCU_PCENR_ADC1FEN_Msk, RCU_PCENR_ADC1FEN_Pos)

/**
  * @brief  ADC0 Function Clk Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_ADC0FunClk_En(__RCU__)             SET_BIT((__RCU__)->PCENR, RCU_PCENR_ADC0FEN_Msk)

/**
  * @brief  ADC0 Function Clk Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_ADC0FunClk_Dis(__RCU__)            CLEAR_BIT((__RCU__)->PCENR, RCU_PCENR_ADC0FEN_Msk)

/**
  * @brief  Judge is ADC0 Function CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsADC0FunClkEn(__RCU__)            READ_BIT_SHIFT((__RCU__)->PCENR, RCU_PCENR_ADC0FEN_Msk, RCU_PCENR_ADC0FEN_Pos)


/**
  * @brief  TMR6 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR6Clk_En(__RCU__)                SET_BIT((__RCU__)->APB0ENR, RCU_APB0ENR_TMR6EN_Msk)

/**
  * @brief  TMR6 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR6Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->APB0ENR, RCU_APB0ENR_TMR6EN_Msk)

/**
  * @brief  Judge is TMR6 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsTMR6ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->APB0ENR, RCU_APB0ENR_TMR6EN_Msk, RCU_APB0ENR_TMR6EN_Pos)


/**
  * @brief  TMR8 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR8Clk_En(__RCU__)                SET_BIT((__RCU__)->APB0ENR, RCU_APB0ENR_TMR8EN_Msk)

/**
  * @brief  TMR8 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR8Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->APB0ENR, RCU_APB0ENR_TMR8EN_Msk)

/**
  * @brief  Judge is TMR8 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsTMR8ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->APB0ENR, RCU_APB0ENR_TMR8EN_Msk, RCU_APB0ENR_TMR8EN_Pos)

/**
  * @brief  TMR7 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR7Clk_En(__RCU__)                SET_BIT((__RCU__)->APB0ENR, RCU_APB0ENR_TMR7EN_Msk)

/**
  * @brief  TMR7 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR7Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->APB0ENR, RCU_APB0ENR_TMR7EN_Msk)

/**
  * @brief  Judge is TMR7 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsTMR7ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->APB0ENR, RCU_APB0ENR_TMR7EN_Msk, RCU_APB0ENR_TMR7EN_Pos)

/**
  * @brief  UART2 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_UART2Clk_En(__RCU__)               SET_BIT((__RCU__)->APB0ENR, RCU_APB0ENR_UART2EN_Msk)

/**
  * @brief  UART2 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_UART2Clk_Dis(__RCU__)              CLEAR_BIT((__RCU__)->APB0ENR, RCU_APB0ENR_UART2EN_Msk)

/**
  * @brief  Judge is UART2 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsUART2ClkEn(__RCU__)              READ_BIT_SHIFT((__RCU__)->APB0ENR, RCU_APB0ENR_UART2EN_Msk, RCU_APB0ENR_UART2EN_Pos)

/**
  * @brief  UART1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_UART1Clk_En(__RCU__)               SET_BIT((__RCU__)->APB0ENR, RCU_APB0ENR_UART1EN_Msk)

/**
  * @brief  UART1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_UART1Clk_Dis(__RCU__)              CLEAR_BIT((__RCU__)->APB0ENR, RCU_APB0ENR_UART1EN_Msk)

/**
  * @brief  Judge is UART1 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsUART1ClkEn(__RCU__)              READ_BIT_SHIFT((__RCU__)->APB0ENR, RCU_APB0ENR_UART1EN_Msk, RCU_APB0ENR_UART1EN_Pos)

/**
  * @brief  UART0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_UART0Clk_En(__RCU__)               SET_BIT((__RCU__)->APB0ENR, RCU_APB0ENR_UART0EN_Msk)

/**
  * @brief  UART0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_UART0Clk_Dis(__RCU__)              CLEAR_BIT((__RCU__)->APB0ENR, RCU_APB0ENR_UART0EN_Msk)

/**
  * @brief  Judge is UART0 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsUART0ClkEn(__RCU__)              READ_BIT_SHIFT((__RCU__)->APB0ENR, RCU_APB0ENR_UART0EN_Msk, RCU_APB0ENR_UART0EN_Pos)

/**
  * @brief  I2C2 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_I2C2Clk_En(__RCU__)                SET_BIT((__RCU__)->APB0ENR, RCU_APB0ENR_I2C2EN_Msk)

/**
  * @brief  I2C2 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_I2C2Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->APB0ENR, RCU_APB0ENR_I2C2EN_Msk)

/**
  * @brief  Judge is I2C2 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsI2C2ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->APB0ENR, RCU_APB0ENR_I2C2EN_Msk, RCU_APB0ENR_I2C2EN_Pos)

/**
  * @brief  I2C1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_I2C1Clk_En(__RCU__)                SET_BIT((__RCU__)->APB0ENR, RCU_APB0ENR_I2C1EN_Msk)

/**
  * @brief  I2C1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_I2C1Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->APB0ENR, RCU_APB0ENR_I2C1EN_Msk)

/**
  * @brief  Judge is I2C1 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsI2C1ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->APB0ENR, RCU_APB0ENR_I2C1EN_Msk, RCU_APB0ENR_I2C1EN_Pos)

/**
  * @brief  I2C0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_I2C0Clk_En(__RCU__)                SET_BIT((__RCU__)->APB0ENR, RCU_APB0ENR_I2C0EN_Msk)

/**
  * @brief  I2C0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_I2C0Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->APB0ENR, RCU_APB0ENR_I2C0EN_Msk)

/**
  * @brief  Judge is I2C0 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsI2C0ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->APB0ENR, RCU_APB0ENR_I2C0EN_Msk, RCU_APB0ENR_I2C0EN_Pos)


/**
  * @brief  TMR2 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR2Clk_En(__RCU__)                SET_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_TMR2EN_Msk)

/**
  * @brief  TMR2 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR2Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_TMR2EN_Msk)

/**
  * @brief  Judge is TMR2 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsTMR2ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->APB1ENR, RCU_APB1ENR_TMR2EN_Msk, RCU_APB1ENR_TMR2EN_Pos)

/**
  * @brief  TMR1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR1Clk_En(__RCU__)                SET_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_TMR1EN_Msk)

/**
  * @brief  TMR1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR1Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_TMR1EN_Msk)

/**
  * @brief  Judge is TMR1 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsTMR1ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->APB1ENR, RCU_APB1ENR_TMR1EN_Msk, RCU_APB1ENR_TMR1EN_Pos)

/**
  * @brief  TMR0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR0Clk_En(__RCU__)                SET_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_TMR0EN_Msk)

/**
  * @brief  TMR0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR0Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_TMR0EN_Msk)

/**
  * @brief  Judge is TMR0 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsTMR0ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->APB1ENR, RCU_APB1ENR_TMR0EN_Msk, RCU_APB1ENR_TMR0EN_Pos)

/**
  * @brief  PDM3 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PDM3Clk_En(__RCU__)                SET_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_PDM3EN_Msk)

/**
  * @brief  PDM3 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PDM3Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_PDM3EN_Msk)

/**
  * @brief  Judge is PDM3 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsPDM3ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->APB1ENR, RCU_APB1ENR_PDM3EN_Msk, RCU_APB1ENR_PDM3EN_Pos)

/**
  * @brief  PDM2 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PDM2Clk_En(__RCU__)                SET_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_PDM2EN_Msk)

/**
  * @brief  PDM2 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PDM2Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_PDM2EN_Msk)

/**
  * @brief  Judge is PDM2 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsPDM2ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->APB1ENR, RCU_APB1ENR_PDM2EN_Msk, RCU_APB1ENR_PDM2EN_Pos)

/**
  * @brief  PDM1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PDM1Clk_En(__RCU__)                SET_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_PDM1EN_Msk)

/**
  * @brief  PDM1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PDM1Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_PDM1EN_Msk)

/**
  * @brief  Judge is PDM1 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsPDM1ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->APB1ENR, RCU_APB1ENR_PDM1EN_Msk, RCU_APB1ENR_PDM1EN_Pos)

/**
  * @brief  PDM0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PDM0Clk_En(__RCU__)                SET_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_PDM0EN_Msk)

/**
  * @brief  PDM0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PDM0Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_PDM0EN_Msk)

/**
  * @brief  Judge is PDM0 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsPDM0ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->APB1ENR, RCU_APB1ENR_PDM0EN_Msk, RCU_APB1ENR_PDM0EN_Pos)

/**
  * @brief  XIF CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_XIFClk_En(__RCU__)                 SET_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_XIFEN_Msk)

/**
  * @brief  XIF CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_XIFClk_Dis(__RCU__)                CLEAR_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_XIFEN_Msk)

/**
  * @brief  Judge is XIF CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsXIFClkEn(__RCU__)                READ_BIT_SHIFT((__RCU__)->APB1ENR, RCU_APB1ENR_XIFEN_Msk, RCU_APB1ENR_XIFEN_Pos)

/**
  * @brief  CAN1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CAN1Clk_En(__RCU__)                SET_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_CAN1EN_Msk)

/**
  * @brief  CAN1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CAN1Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_CAN1EN_Msk)

/**
  * @brief  Judge is CAN1 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsCAN1ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->APB1ENR, RCU_APB1ENR_CAN1EN_Msk, RCU_APB1ENR_CAN1EN_Pos)

/**
  * @brief  CAN0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CAN0Clk_En(__RCU__)                SET_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_CAN0EN_Msk)

/**
  * @brief  CAN0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CAN0Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_CAN0EN_Msk)

/**
  * @brief  Judge is CAN0 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsCAN0ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->APB1ENR, RCU_APB1ENR_CAN0EN_Msk, RCU_APB1ENR_CAN0EN_Pos)

/**
  * @brief  SPI1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_SPI1Clk_En(__RCU__)                SET_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_SPI1EN_Msk)

/**
  * @brief  SPI1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_SPI1Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_SPI1EN_Msk)

/**
  * @brief  Judge is SPI1 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsSPI1ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->APB1ENR, RCU_APB1ENR_SPI1EN_Msk, RCU_APB1ENR_SPI1EN_Pos)

/**
  * @brief  SPI0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_SPI0Clk_En(__RCU__)                SET_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_SPI0EN_Msk)

/**
  * @brief  SPI0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_SPI0Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_SPI0EN_Msk)

/**
  * @brief  Judge is SPI0 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsSPI0ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->APB1ENR, RCU_APB1ENR_SPI0EN_Msk, RCU_APB1ENR_SPI0EN_Pos)

/**
  * @brief  UART4 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_UART4Clk_En(__RCU__)               SET_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_UART4EN_Msk)

/**
  * @brief  UART4 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_UART4Clk_Dis(__RCU__)              CLEAR_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_UART4EN_Msk)

/**
  * @brief  Judge is UART4 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsUART4ClkEn(__RCU__)              READ_BIT_SHIFT((__RCU__)->APB1ENR, RCU_APB1ENR_UART4EN_Msk, RCU_APB1ENR_UART4EN_Pos)

/**
  * @brief  UART3 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_UART3Clk_En(__RCU__)               SET_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_UART3EN_Msk)

/**
  * @brief  UART3 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_UART3Clk_Dis(__RCU__)              CLEAR_BIT((__RCU__)->APB1ENR, RCU_APB1ENR_UART3EN_Msk)

/**
  * @brief  Judge is UART3 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsUART3ClkEn(__RCU__)              READ_BIT_SHIFT((__RCU__)->APB1ENR, RCU_APB1ENR_UART3EN_Msk, RCU_APB1ENR_UART3EN_Pos)


/**
  * @brief  QEI2 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_QEI2Clk_En(__RCU__)                SET_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_QEI2EN_Msk)

/**
  * @brief  QEI2 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_QEI2Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_QEI2EN_Msk)

/**
  * @brief  Judge is QEI2 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsQEI2ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->AHB0ENR, RCU_AHB0ENR_QEI2EN_Msk, RCU_AHB0ENR_QEI2EN_Pos)

/**
  * @brief  QEI1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_QEI1Clk_En(__RCU__)                SET_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_QEI1EN_Msk)

/**
  * @brief  QEI1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_QEI1Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_QEI1EN_Msk)

/**
  * @brief  Judge is QEI1 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsQEI1ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->AHB0ENR, RCU_AHB0ENR_QEI1EN_Msk, RCU_AHB0ENR_QEI1EN_Pos)

/**
  * @brief  QEI0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_QEI0Clk_En(__RCU__)                SET_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_QEI0EN_Msk)

/**
  * @brief  QEI0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_QEI0Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_QEI0EN_Msk)

/**
  * @brief  Judge is QEI0 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsQEI0ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->AHB0ENR, RCU_AHB0ENR_QEI0EN_Msk, RCU_AHB0ENR_QEI0EN_Pos)

/**
  * @brief  TMR4 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR4Clk_En(__RCU__)                SET_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_TMR4EN_Msk)

/**
  * @brief  TMR4 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR4Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_TMR4EN_Msk)

/**
  * @brief  Judge is TMR4 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsTMR4ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->AHB0ENR, RCU_AHB0ENR_TMR4EN_Msk, RCU_AHB0ENR_TMR4EN_Pos)

/**
  * @brief  TMR3 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR3Clk_En(__RCU__)                SET_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_TMR3EN_Msk)

/**
  * @brief  TMR3 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR3Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_TMR3EN_Msk)

/**
  * @brief  Judge is TMR3 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsTMR3ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->AHB0ENR, RCU_AHB0ENR_TMR3EN_Msk, RCU_AHB0ENR_TMR3EN_Pos)

/**
  * @brief  GPIOF CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIOFClk_En(__RCU__)               SET_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_PFEN_Msk)

/**
  * @brief  GPIOF CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIOFClk_Dis(__RCU__)              CLEAR_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_PFEN_Msk)

/**
  * @brief  Judge is GPIOF CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsGPIOFClkEn(__RCU__)              READ_BIT_SHIFT((__RCU__)->AHB0ENR, RCU_AHB0ENR_PFEN_Msk, RCU_AHB0ENR_PFEN_Pos)

/**
  * @brief  GPIOE CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIOEClk_En(__RCU__)               SET_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_PEEN_Msk)

/**
  * @brief  GPIOE CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIOEClk_Dis(__RCU__)              CLEAR_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_PEEN_Msk)

/**
  * @brief  Judge is GPIOE CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsGPIOEClkEn(__RCU__)              READ_BIT_SHIFT((__RCU__)->AHB0ENR, RCU_AHB0ENR_PEEN_Msk, RCU_AHB0ENR_PEEN_Pos)

/**
  * @brief  GPIOD CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIODClk_En(__RCU__)               SET_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_PDEN_Msk)

/**
  * @brief  GPIOD CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIODClk_Dis(__RCU__)              CLEAR_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_PDEN_Msk)

/**
  * @brief  Judge is GPIOD CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsGPIODClkEn(__RCU__)              READ_BIT_SHIFT((__RCU__)->AHB0ENR, RCU_AHB0ENR_PDEN_Msk, RCU_AHB0ENR_PDEN_Pos)

/**
  * @brief  GPIOC CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIOCClk_En(__RCU__)               SET_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_PCEN_Msk)

/**
  * @brief  GPIOC CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIOCClk_Dis(__RCU__)              CLEAR_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_PCEN_Msk)

/**
  * @brief  Judge is GPIOC CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsGPIOCClkEn(__RCU__)              READ_BIT_SHIFT((__RCU__)->AHB0ENR, RCU_AHB0ENR_PCEN_Msk, RCU_AHB0ENR_PCEN_Pos)

/**
  * @brief  GPIOB CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIOBClk_En(__RCU__)               SET_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_PBEN_Msk)

/**
  * @brief  GPIOB CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIOBClk_Dis(__RCU__)              CLEAR_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_PBEN_Msk)

/**
  * @brief  Judge is GPIOB CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsGPIOBClkEn(__RCU__)              READ_BIT_SHIFT((__RCU__)->AHB0ENR, RCU_AHB0ENR_PBEN_Msk, RCU_AHB0ENR_PBEN_Pos)

/**
  * @brief  GPIOA CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIOAClk_En(__RCU__)               SET_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_PAEN_Msk)

/**
  * @brief  GPIOA CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIOAClk_Dis(__RCU__)              CLEAR_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_PAEN_Msk)

/**
  * @brief  Judge is GPIOA CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsGPIOAClkEn(__RCU__)              READ_BIT_SHIFT((__RCU__)->AHB0ENR, RCU_AHB0ENR_PAEN_Msk, RCU_AHB0ENR_PAEN_Pos)

/**
  * @brief  EFLASH CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_EFLASHClk_En(__RCU__)              SET_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_FLSEN_Msk)

/**
  * @brief  EFLASH CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_EFLASHClk_Dis(__RCU__)             CLEAR_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_FLSEN_Msk)

/**
  * @brief  Judge is EFLASH CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsEFLASHClkEn(__RCU__)             READ_BIT_SHIFT((__RCU__)->AHB0ENR, RCU_AHB0ENR_FLSEN_Msk, RCU_AHB0ENR_FLSEN_Pos)

/**
  * @brief  DMA CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_DMAClk_En(__RCU__)                 SET_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_DMAEN_Msk)

/**
  * @brief  DMA CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_DMAClk_Dis(__RCU__)                CLEAR_BIT((__RCU__)->AHB0ENR, RCU_AHB0ENR_DMAEN_Msk)

/**
  * @brief  Judge is DMA CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsDMAClkEn(__RCU__)                READ_BIT_SHIFT((__RCU__)->AHB0ENR, RCU_AHB0ENR_DMAEN_Msk, RCU_AHB0ENR_DMAEN_Pos)


/**
  * @brief  CORDIC CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CORDICClk_En(__RCU__)              SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_CORDICEN_Msk)

/**
  * @brief  CORDIC CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CORDICClk_Dis(__RCU__)             CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_CORDICEN_Msk)

/**
  * @brief  Judge is CORDIC CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsCORDICClkEn(__RCU__)             READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_CORDICEN_Msk, RCU_AHB1ENR_CORDICEN_Pos)

/**
  * @brief  IIR5 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR5Clk_En(__RCU__)                SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_IIR5EN_Msk)

/**
  * @brief  IIR5 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR5Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_IIR5EN_Msk)

/**
  * @brief  Judge is IIR5 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsIIR5ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_IIR5EN_Msk, RCU_AHB1ENR_IIR5EN_Pos)

/**
  * @brief  IIR4 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR4Clk_En(__RCU__)                SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_IIR4EN_Msk)

/**
  * @brief  IIR4 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR4Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_IIR4EN_Msk)

/**
  * @brief  Judge is IIR4 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsIIR4ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_IIR4EN_Msk, RCU_AHB1ENR_IIR4EN_Pos)

/**
  * @brief  IIR3 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR3Clk_En(__RCU__)                SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_IIR3EN_Msk)

/**
  * @brief  IIR3 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR3Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_IIR3EN_Msk)

/**
  * @brief  Judge is IIR3 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsIIR3ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_IIR3EN_Msk, RCU_AHB1ENR_IIR3EN_Pos)

/**
  * @brief  IIR2 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR2Clk_En(__RCU__)                SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_IIR2EN_Msk)

/**
  * @brief  IIR2 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR2Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_IIR2EN_Msk)

/**
  * @brief  Judge is IIR2 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsIIR2ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_IIR2EN_Msk, RCU_AHB1ENR_IIR2EN_Pos)

/**
  * @brief  IIR1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR1Clk_En(__RCU__)                SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_IIR1EN_Msk)

/**
  * @brief  IIR1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR1Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_IIR1EN_Msk)

/**
  * @brief  Judge is IIR1 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsIIR1ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_IIR1EN_Msk, RCU_AHB1ENR_IIR1EN_Pos)

/**
  * @brief  IIR0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR0Clk_En(__RCU__)                SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_IIR0EN_Msk)

/**
  * @brief  IIR0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR0Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_IIR0EN_Msk)

/**
  * @brief  Judge is IIR0 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsIIR0ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_IIR0EN_Msk, RCU_AHB1ENR_IIR0EN_Pos)

/**
  * @brief  HRPWM7 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM7Clk_En(__RCU__)              SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM7EN_Msk)

/**
  * @brief  HRPWM7 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM7Clk_Dis(__RCU__)             CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM7EN_Msk)

/**
  * @brief  Judge is HRPWM7 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsHRPWM7ClkEn(__RCU__)             READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM7EN_Msk, RCU_AHB1ENR_PWM7EN_Pos)

/**
  * @brief  HRPWM6 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM6Clk_En(__RCU__)              SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM6EN_Msk)

/**
  * @brief  HRPWM6 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM6Clk_Dis(__RCU__)             CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM6EN_Msk)

/**
  * @brief  Judge is HRPWM6 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsHRPWM6ClkEn(__RCU__)             READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM6EN_Msk, RCU_AHB1ENR_PWM6EN_Pos)

/**
  * @brief  HRPWM5 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM5Clk_En(__RCU__)              SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM5EN_Msk)

/**
  * @brief  HRPWM5 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM5Clk_Dis(__RCU__)             CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM5EN_Msk)

/**
  * @brief  Judge is HRPWM5 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsHRPWM5ClkEn(__RCU__)             READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM5EN_Msk, RCU_AHB1ENR_PWM5EN_Pos)

/**
  * @brief  HRPWM4 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM4Clk_En(__RCU__)              SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM4EN_Msk)

/**
  * @brief  HRPWM4 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM4Clk_Dis(__RCU__)             CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM4EN_Msk)

/**
  * @brief  Judge is HRPWM4 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsHRPWM4ClkEn(__RCU__)             READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM4EN_Msk, RCU_AHB1ENR_PWM4EN_Pos)

/**
  * @brief  HRPWM3 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM3Clk_En(__RCU__)              SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM3EN_Msk)

/**
  * @brief  HRPWM3 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM3Clk_Dis(__RCU__)             CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM3EN_Msk)

/**
  * @brief  Judge is HRPWM3 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsHRPWM3ClkEn(__RCU__)             READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM3EN_Msk, RCU_AHB1ENR_PWM3EN_Pos)

/**
  * @brief  HRPWM2 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM2Clk_En(__RCU__)              SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM2EN_Msk)

/**
  * @brief  HRPWM2 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM2Clk_Dis(__RCU__)             CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM2EN_Msk)

/**
  * @brief  Judge is HRPWM2 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsHRPWM2ClkEn(__RCU__)             READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM2EN_Msk, RCU_AHB1ENR_PWM2EN_Pos)

/**
  * @brief  HRPWM1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM1Clk_En(__RCU__)              SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM1EN_Msk)

/**
  * @brief  HRPWM1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM1Clk_Dis(__RCU__)             CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM1EN_Msk)

/**
  * @brief  Judge is HRPWM1 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsHRPWM1ClkEn(__RCU__)             READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM1EN_Msk, RCU_AHB1ENR_PWM1EN_Pos)

/**
  * @brief  HRPWM0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM0Clk_En(__RCU__)              SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM0EN_Msk)

/**
  * @brief  HRPWM0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWM0Clk_Dis(__RCU__)             CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM0EN_Msk)

/**
  * @brief  Judge is HRPWM0 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsHRPWM0ClkEn(__RCU__)             READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_PWM0EN_Msk, RCU_AHB1ENR_PWM0EN_Pos)

/**
  * @brief  Judge is HRPWM0/1/2/3/4/5/6/7 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 HRPWM0/1/2/3/4/5/6/7 CLK is Disable
  * @retval 1 HRPWM0/1/2/3/4/5/6/7 CLK is Enable
  */
#define __LL_RCU_IsHRPWMClkEn(__RCU__)              (!!READ_BIT_SHIFT((__RCU__)->AHB1ENR, 0x1FE00UL, RCU_AHB1ENR_PWM0EN_Pos))

/**
  * @brief  CMP CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CMPClk_En(__RCU__)                 SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_CMPxEN_Msk)

/**
  * @brief  CMP CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CMPClk_Dis(__RCU__)                CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_CMPxEN_Msk)

/**
  * @brief  Judge is CMP CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsCMPClkEn(__RCU__)                READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_CMPxEN_Msk, RCU_AHB1ENR_CMPxEN_Pos)

/**
  * @brief  DAC CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_DACClk_En(__RCU__)                 SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_DACxEN_Msk)

/**
  * @brief  DAC CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_DACClk_Dis(__RCU__)                CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_DACxEN_Msk)

/**
  * @brief  Judge is DAC CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsDACClkEn(__RCU__)                READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_DACxEN_Msk, RCU_AHB1ENR_DACxEN_Pos)

/**
  * @brief  ADC3 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_ADC3Clk_En(__RCU__)                SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_ADC3EN_Msk)

/**
  * @brief  ADC3 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_ADC3Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_ADC3EN_Msk)

/**
  * @brief  Judge is ADC3 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsADC3ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_ADC3EN_Msk, RCU_AHB1ENR_ADC3EN_Pos)

/**
  * @brief  ADC2 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_ADC2Clk_En(__RCU__)                SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_ADC2EN_Msk)

/**
  * @brief  ADC2 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_ADC2Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_ADC2EN_Msk)

/**
  * @brief  Judge is ADC2 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsADC2ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_ADC2EN_Msk, RCU_AHB1ENR_ADC2EN_Pos)

/**
  * @brief  ADC1 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_ADC1Clk_En(__RCU__)                SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_ADC1EN_Msk)

/**
  * @brief  ADC1 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_ADC1Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_ADC1EN_Msk)

/**
  * @brief  Judge is ADC1 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsADC1ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_ADC1EN_Msk, RCU_AHB1ENR_ADC1EN_Pos)

/**
  * @brief  ADC0 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_ADC0Clk_En(__RCU__)                SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_ADC0EN_Msk)

/**
  * @brief  ADC0 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_ADC0Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_ADC0EN_Msk)

/**
  * @brief  Judge is ADC0 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsADC0ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_ADC0EN_Msk, RCU_AHB1ENR_ADC0EN_Pos)

/**
  * @brief  Judge is ADC0/1/2/3 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 ADC0/1/2/3 CLK is Disable
  * @retval 1 ADC0/1/2/3 CLK is Enable
  */
#define __LL_RCU_IsADCClkEn(__RCU__)                (!!READ_BIT_SHIFT((__RCU__)->AHB1ENR, 0x78UL, RCU_AHB1ENR_ADC0EN_Pos))

/**
  * @brief  USB CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_USBClk_En(__RCU__)                 SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_USBEN_Msk)

/**
  * @brief  USB CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_USBClk_Dis(__RCU__)                CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_USBEN_Msk)

/**
  * @brief  Judge is USB CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsUSBClkEn(__RCU__)                READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_USBEN_Msk, RCU_AHB1ENR_USBEN_Pos)

/**
  * @brief  TMR10 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR10Clk_En(__RCU__)               SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_TMR10EN_Msk)

/**
  * @brief  TMR10 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR10Clk_Dis(__RCU__)              CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_TMR10EN_Msk)

/**
  * @brief  Judge is TMR10 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsTMR10ClkEn(__RCU__)              READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_TMR10EN_Msk, RCU_AHB1ENR_TMR10EN_Pos)

/**
  * @brief  TMR9 CLK Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR9Clk_En(__RCU__)                SET_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_TMR9EN_Msk)

/**
  * @brief  TMR9 CLK Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR9Clk_Dis(__RCU__)               CLEAR_BIT((__RCU__)->AHB1ENR, RCU_AHB1ENR_TMR9EN_Msk)

/**
  * @brief  Judge is TMR9 CLK Enable or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_RCU_IsTMR9ClkEn(__RCU__)               READ_BIT_SHIFT((__RCU__)->AHB1ENR, RCU_AHB1ENR_TMR9EN_Msk, RCU_AHB1ENR_TMR9EN_Pos)


/**
  * @brief  TMR6 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR6SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->APB0RSTR, RCU_APB0RSTR_TMR6RST_Msk)

/**
  * @brief  TMR6 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR6SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->APB0RSTR, RCU_APB0RSTR_TMR6RST_Msk)

/**
  * @brief  Judge is TMR6 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsTMR6SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->APB0RSTR, RCU_APB0RSTR_TMR6RST_Msk, RCU_APB0RSTR_TMR6RST_Pos)

/**
  * @brief  TMR8 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR8SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->APB0RSTR, RCU_APB0RSTR_TMR8RST_Msk)

/**
  * @brief  TMR8 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR8SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->APB0RSTR, RCU_APB0RSTR_TMR8RST_Msk)

/**
  * @brief  Judge is TMR8 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsTMR8SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->APB0RSTR, RCU_APB0RSTR_TMR8RST_Msk, RCU_APB0RSTR_TMR8RST_Pos)

/**
  * @brief  TMR7 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR7SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->APB0RSTR, RCU_APB0RSTR_TMR7RST_Msk)

/**
  * @brief  TMR7 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR7SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->APB0RSTR, RCU_APB0RSTR_TMR7RST_Msk)

/**
  * @brief  Judge is TMR7 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsTMR7SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->APB0RSTR, RCU_APB0RSTR_TMR7RST_Msk, RCU_APB0RSTR_TMR7RST_Pos)

/**
  * @brief  UART2 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_UART2SoftRst_Assert(__RCU__)       CLEAR_BIT((__RCU__)->APB0RSTR, RCU_APB0RSTR_UART2RST_Msk)

/**
  * @brief  UART2 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_UART2SoftRst_Release(__RCU__)      SET_BIT((__RCU__)->APB0RSTR, RCU_APB0RSTR_UART2RST_Msk)

/**
  * @brief  Judge is UART2 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsUART2SoftRstRelease(__RCU__)     READ_BIT_SHIFT((__RCU__)->APB0RSTR, RCU_APB0RSTR_UART2RST_Msk, RCU_APB0RSTR_UART2RST_Pos)

/**
  * @brief  UART1 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_UART1SoftRst_Assert(__RCU__)       CLEAR_BIT((__RCU__)->APB0RSTR, RCU_APB0RSTR_UART1RST_Msk)

/**
  * @brief  UART1 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_UART1SoftRst_Release(__RCU__)      SET_BIT((__RCU__)->APB0RSTR, RCU_APB0RSTR_UART1RST_Msk)

/**
  * @brief  Judge is UART1 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsUART1SoftRstRelease(__RCU__)     READ_BIT_SHIFT((__RCU__)->APB0RSTR, RCU_APB0RSTR_UART1RST_Msk, RCU_APB0RSTR_UART1RST_Pos)

/**
  * @brief  UART0 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_UART0SoftRst_Assert(__RCU__)       CLEAR_BIT((__RCU__)->APB0RSTR, RCU_APB0RSTR_UART0RST_Msk)

/**
  * @brief  UART0 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_UART0SoftRst_Release(__RCU__)      SET_BIT((__RCU__)->APB0RSTR, RCU_APB0RSTR_UART0RST_Msk)

/**
  * @brief  Judge is UART0 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsUART0SoftRstRelease(__RCU__)     READ_BIT_SHIFT((__RCU__)->APB0RSTR, RCU_APB0RSTR_UART0RST_Msk, RCU_APB0RSTR_UART0RST_Pos)

/**
  * @brief  I2C2 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_I2C2SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->APB0RSTR, RCU_APB0RSTR_I2C2RST_Msk)

/**
  * @brief  I2C2 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_I2C2SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->APB0RSTR, RCU_APB0RSTR_I2C2RST_Msk)

/**
  * @brief  Judge is I2C2 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsI2C2SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->APB0RSTR, RCU_APB0RSTR_I2C2RST_Msk, RCU_APB0RSTR_I2C2RST_Pos)

/**
  * @brief  I2C1 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_I2C1SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->APB0RSTR, RCU_APB0RSTR_I2C1RST_Msk)

/**
  * @brief  I2C1 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_I2C1SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->APB0RSTR, RCU_APB0RSTR_I2C1RST_Msk)

/**
  * @brief  Judge is I2C1 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsI2C1SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->APB0RSTR, RCU_APB0RSTR_I2C1RST_Msk, RCU_APB0RSTR_I2C1RST_Pos)

/**
  * @brief  I2C0 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_I2C0SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->APB0RSTR, RCU_APB0RSTR_I2C0RST_Msk)

/**
  * @brief  I2C0 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_I2C0SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->APB0RSTR, RCU_APB0RSTR_I2C0RST_Msk)

/**
  * @brief  Judge is I2C0 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsI2C0SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->APB0RSTR, RCU_APB0RSTR_I2C0RST_Msk, RCU_APB0RSTR_I2C0RST_Pos)

/**
  * @brief  APB0 Soft Reset all Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_APB0SoftRstAll_Assert(__RCU__)     WRITE_REG((__RCU__)->APB0RSTR, 0x0)

/**
  * @brief  APB0 Soft Reset all Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_APB0SoftRstAll_Release(__RCU__)    WRITE_REG((__RCU__)->APB0RSTR, 0xffffffffUL)

/**
  * @brief  Judge is APB0 Soft Reset all Assert or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 isn't APB0 Soft Reset all Assert
  * @retval 1 is APB0 Soft Reset all Assert
  */
#define __LL_RCU_IsAPB0SoftRstAllAssert(__RCU__)    ((READ_REG((__RCU__)->APB0RSTR) & 0xffUL) == 0x00)

/**
  * @brief  Judge is APB0 Soft Reset all Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 isn't APB0 Soft Reset all Release
  * @retval 1 is APB0 Soft Reset all Release
  */
#define __LL_RCU_IsAPB0SoftRstAllRelease(__RCU__)   ((READ_REG((__RCU__)->APB0RSTR) & 0xffUL) == 0xffUL)


/**
  * @brief  TMR2 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR2SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_TMR2RST_Msk)

/**
  * @brief  TMR2 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR2SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_TMR2RST_Msk)

/**
  * @brief  Judge is TMR2 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsTMR2SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->APB1RSTR, RCU_APB1RSTR_TMR2RST_Msk, RCU_APB1RSTR_TMR2RST_Pos)

/**
  * @brief  TMR1 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR1SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_TMR1RST_Msk)

/**
  * @brief  TMR1 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR1SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_TMR1RST_Msk)

/**
  * @brief  Judge is TMR1 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsTMR1SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->APB1RSTR, RCU_APB1RSTR_TMR1RST_Msk, RCU_APB1RSTR_TMR1RST_Pos)

/**
  * @brief  TMR0 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR0SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_TMR0RST_Msk)

/**
  * @brief  TMR0 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR0SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_TMR0RST_Msk)

/**
  * @brief  Judge is TMR0 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsTMR0SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->APB1RSTR, RCU_APB1RSTR_TMR0RST_Msk, RCU_APB1RSTR_TMR0RST_Pos)

/**
  * @brief  PDM3 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PDM3SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_PDM3RST_Msk)

/**
  * @brief  PDM3 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PDM3SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_PDM3RST_Msk)

/**
  * @brief  Judge is PDM3 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsPDM3SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->APB1RSTR, RCU_APB1RSTR_PDM3RST_Msk, RCU_APB1RSTR_PDM3RST_Pos)

/**
  * @brief  PDM2 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PDM2SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_PDM2RST_Msk)

/**
  * @brief  PDM2 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PDM2SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_PDM2RST_Msk)

/**
  * @brief  Judge is PDM2 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsPDM2SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->APB1RSTR, RCU_APB1RSTR_PDM2RST_Msk, RCU_APB1RSTR_PDM2RST_Pos)

/**
  * @brief  PDM1 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PDM1SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_PDM1RST_Msk)

/**
  * @brief  PDM1 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PDM1SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_PDM1RST_Msk)

/**
  * @brief  Judge is PDM1 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsPDM1SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->APB1RSTR, RCU_APB1RSTR_PDM1RST_Msk, RCU_APB1RSTR_PDM1RST_Pos)

/**
  * @brief  PDM0 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PDM0SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_PDM0RST_Msk)

/**
  * @brief  PDM0 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_PDM0SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_PDM0RST_Msk)

/**
  * @brief  Judge is PDM0 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsPDM0SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->APB1RSTR, RCU_APB1RSTR_PDM0RST_Msk, RCU_APB1RSTR_PDM0RST_Pos)

/**
  * @brief  XIF Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_XIFSoftRst_Assert(__RCU__)         CLEAR_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_XIFRST_Msk)

/**
  * @brief  XIF Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_XIFSoftRst_Release(__RCU__)        SET_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_XIFRST_Msk)

/**
  * @brief  Judge is XIF Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsXIFSoftRstRelease(__RCU__)       READ_BIT_SHIFT((__RCU__)->APB1RSTR, RCU_APB1RSTR_XIFRST_Msk, RCU_APB1RSTR_XIFRST_Pos)

/**
  * @brief  CAN1 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CAN1SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_CAN1RST_Msk)

/**
  * @brief  CAN1 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CAN1SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_CAN1RST_Msk)

/**
  * @brief  Judge is CAN1 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsCAN1SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->APB1RSTR, RCU_APB1RSTR_CAN1RST_Msk, RCU_APB1RSTR_CAN1RST_Pos)

/**
  * @brief  CAN0 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CAN0SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_CAN0RST_Msk)

/**
  * @brief  CAN0 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CAN0SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_CAN0RST_Msk)

/**
  * @brief  Judge is CAN0 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsCAN0SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->APB1RSTR, RCU_APB1RSTR_CAN0RST_Msk, RCU_APB1RSTR_CAN0RST_Pos)

/**
  * @brief  SPI1 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_SPI1SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_SPI1RST_Msk)

/**
  * @brief  SPI1 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_SPI1SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_SPI1RST_Msk)

/**
  * @brief  Judge is SPI1 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsSPI1SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->APB1RSTR, RCU_APB1RSTR_SPI1RST_Msk, RCU_APB1RSTR_SPI1RST_Pos)

/**
  * @brief  SPI0 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_SPI0SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_SPI0RST_Msk)

/**
  * @brief  SPI0 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_SPI0SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_SPI0RST_Msk)

/**
  * @brief  Judge is SPI0 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsSPI0SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->APB1RSTR, RCU_APB1RSTR_SPI0RST_Msk, RCU_APB1RSTR_SPI0RST_Pos)

/**
  * @brief  UART4 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_UART4SoftRst_Assert(__RCU__)       CLEAR_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_UART4RST_Msk)

/**
  * @brief  UART4 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_UART4SoftRst_Release(__RCU__)      SET_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_UART4RST_Msk)

/**
  * @brief  Judge is UART4 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsUART4SoftRstRelease(__RCU__)     READ_BIT_SHIFT((__RCU__)->APB1RSTR, RCU_APB1RSTR_UART4RST_Msk, RCU_APB1RSTR_UART4RST_Pos)

/**
  * @brief  UART3 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_UART3SoftRst_Assert(__RCU__)       CLEAR_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_UART3RST_Msk)

/**
  * @brief  UART3 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_UART3SoftRst_Release(__RCU__)      SET_BIT((__RCU__)->APB1RSTR, RCU_APB1RSTR_UART3RST_Msk)

/**
  * @brief  Judge is UART3 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsUART3SoftRstRelease(__RCU__)     READ_BIT_SHIFT((__RCU__)->APB1RSTR, RCU_APB1RSTR_UART3RST_Msk, RCU_APB1RSTR_UART3RST_Pos)

/**
  * @brief  APB1 Soft Reset all Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_APB1SoftRstAll_Assert(__RCU__)     WRITE_REG((__RCU__)->APB1RSTR, 0x0)

/**
  * @brief  APB1 Soft Reset all Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_APB1SoftRstAll_Release(__RCU__)    WRITE_REG((__RCU__)->APB1RSTR, 0xffffffffUL)

/**
  * @brief  Judge is APB1 Soft Reset all Assert or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 isn't APB1 Soft Reset all Assert
  * @retval 1 is APB1 Soft Reset all Assert
  */
#define __LL_RCU_IsAPB1SoftRstAllAssert(__RCU__)    ((READ_REG((__RCU__)->APB1RSTR) & 0x3fffUL) == 0x00)

/**
  * @brief  Judge is APB1 Soft Reset all Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 isn't APB1 Soft Reset all Release
  * @retval 1 is APB1 Soft Reset all Release
  */
#define __LL_RCU_IsAPB1SoftRstAllRelease(__RCU__)   ((READ_REG((__RCU__)->APB1RSTR) & 0x3fffUL) == 0x3fffUL)


/**
  * @brief  QEI2 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_QEI2SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_QEI2RST_Msk)

/**
  * @brief  QEI2 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_QEI2SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_QEI2RST_Msk)

/**
  * @brief  Judge is QEI2 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsQEI2SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_QEI2RST_Msk, RCU_AHB0RSTR_QEI2RST_Pos)

/**
  * @brief  QEI1 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_QEI1SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_QEI1RST_Msk)

/**
  * @brief  QEI1 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_QEI1SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_QEI1RST_Msk)

/**
  * @brief  Judge is QEI1 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsQEI1SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_QEI1RST_Msk, RCU_AHB0RSTR_QEI1RST_Pos)

/**
  * @brief  QEI0 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_QEI0SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_QEI0RST_Msk)

/**
  * @brief  QEI0 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_QEI0SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_QEI0RST_Msk)

/**
  * @brief  Judge is QEI0 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsQEI0SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_QEI0RST_Msk, RCU_AHB0RSTR_QEI0RST_Pos)

/**
  * @brief  TMR4 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR4SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_TMR4RST_Msk)

/**
  * @brief  TMR4 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR4SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_TMR4RST_Msk)

/**
  * @brief  Judge is TMR4 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsTMR4SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_TMR4RST_Msk, RCU_AHB0RSTR_TMR4RST_Pos)

/**
  * @brief  TMR3 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR3SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_TMR3RST_Msk)

/**
  * @brief  TMR3 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR3SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_TMR3RST_Msk)

/**
  * @brief  Judge is TMR3 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsTMR3SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_TMR3RST_Msk, RCU_AHB0RSTR_TMR3RST_Pos)

/**
  * @brief  GPIOF Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIOFSoftRst_Assert(__RCU__)       CLEAR_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_PFRST_Msk)

/**
  * @brief  GPIOF Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIOFSoftRst_Release(__RCU__)      SET_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_PFRST_Msk)

/**
  * @brief  Judge is GPIOF Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsGPIOFSoftRstRelease(__RCU__)     READ_BIT_SHIFT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_PFRST_Msk, RCU_AHB0RSTR_PFRST_Pos)

/**
  * @brief  GPIOE Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIOESoftRst_Assert(__RCU__)       CLEAR_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_PERST_Msk)

/**
  * @brief  GPIOE Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIOESoftRst_Release(__RCU__)      SET_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_PERST_Msk)

/**
  * @brief  Judge is GPIOE Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsGPIOESoftRstRelease(__RCU__)     READ_BIT_SHIFT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_PERST_Msk, RCU_AHB0RSTR_PERST_Pos)

/**
  * @brief  GPIOD Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIODSoftRst_Assert(__RCU__)       CLEAR_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_PDRST_Msk)

/**
  * @brief  GPIOD Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIODSoftRst_Release(__RCU__)      SET_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_PDRST_Msk)

/**
  * @brief  Judge is GPIOD Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsGPIODSoftRstRelease(__RCU__)     READ_BIT_SHIFT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_PDRST_Msk, RCU_AHB0RSTR_PDRST_Pos)

/**
  * @brief  GPIOC Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIOCSoftRst_Assert(__RCU__)       CLEAR_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_PCRST_Msk)

/**
  * @brief  GPIOC Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIOCSoftRst_Release(__RCU__)      SET_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_PCRST_Msk)

/**
  * @brief  Judge is GPIOC Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsGPIOCSoftRstRelease(__RCU__)     READ_BIT_SHIFT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_PCRST_Msk, RCU_AHB0RSTR_PCRST_Pos)

/**
  * @brief  GPIOB Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIOBSoftRst_Assert(__RCU__)       CLEAR_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_PBRST_Msk)

/**
  * @brief  GPIOB Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIOBSoftRst_Release(__RCU__)      SET_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_PBRST_Msk)

/**
  * @brief  Judge is GPIOB Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsGPIOBSoftRstRelease(__RCU__)     READ_BIT_SHIFT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_PBRST_Msk, RCU_AHB0RSTR_PBRST_Pos)

/**
  * @brief  GPIOA Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIOASoftRst_Assert(__RCU__)       CLEAR_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_PARST_Msk)

/**
  * @brief  GPIOA Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_GPIOASoftRst_Release(__RCU__)      SET_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_PARST_Msk)

/**
  * @brief  Judge is GPIOA Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsGPIOASoftRstRelease(__RCU__)     READ_BIT_SHIFT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_PARST_Msk, RCU_AHB0RSTR_PARST_Pos)

/**
  * @brief  EFLASH Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_EFLASHSoftRst_Assert(__RCU__)      CLEAR_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_FLSRST_Msk)

/**
  * @brief  EFLASH Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_EFLASHSoftRst_Release(__RCU__)     SET_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_FLSRST_Msk)

/**
  * @brief  Judge is EFLASH Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsEFLASHSoftRstRelease(__RCU__)    READ_BIT_SHIFT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_FLSRST_Msk, RCU_AHB0RSTR_FLSRST_Pos)

/**
  * @brief  DMA Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_DMASoftRst_Assert(__RCU__)         CLEAR_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_DMARST_Msk)

/**
  * @brief  DMA Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_DMASoftRst_Release(__RCU__)        SET_BIT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_DMARST_Msk)

/**
  * @brief  Judge is DMA Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsDMASoftRstRelease(__RCU__)       READ_BIT_SHIFT((__RCU__)->AHB0RSTR, RCU_AHB0RSTR_DMARST_Msk, RCU_AHB0RSTR_DMARST_Pos)

/**
  * @brief  AHB0 Soft Reset all Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_AHB0SoftRstAll_Assert(__RCU__)     WRITE_REG((__RCU__)->AHB0RSTR, 0x0)

/**
  * @brief  AHB0 Soft Reset all Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_AHB0SoftRstAll_Release(__RCU__)    WRITE_REG((__RCU__)->AHB0RSTR, 0xffffffffUL)

/**
  * @brief  Judge is AHB0 Soft Reset all Assert or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 isn't AHB0 Soft Reset all Assert
  * @retval 1 is AHB0 Soft Reset all Assert
  */
#define __LL_RCU_IsAHB0SoftRstAllAssert(__RCU__)    ((READ_REG((__RCU__)->AHB0RSTR) & 0x1fffUL) == 0x00)

/**
  * @brief  Judge is AHB0 Soft Reset all Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 isn't AHB0 Soft Reset all Release
  * @retval 1 is AHB0 Soft Reset all Release
  */
#define __LL_RCU_IsAHB0SoftRstAllRelease(__RCU__)   ((READ_REG((__RCU__)->AHB0RSTR) & 0x1fffUL) == 0x1fffUL)


/**
  * @brief  CORDIC Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CORDICSoftRst_Assert(__RCU__)      CLEAR_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_CORDICRST_Msk)

/**
  * @brief  CORDIC Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CORDICSoftRst_Release(__RCU__)     SET_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_CORDICRST_Msk)

/**
  * @brief  Judge is CORDIC Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsCORDICSoftRstRelease(__RCU__)    READ_BIT_SHIFT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_CORDICRST_Msk, RCU_AHB1RSTR_CORDICRST_Pos)

/**
  * @brief  IIR5 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR5SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_IIR5RST_Msk)

/**
  * @brief  IIR5 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR5SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_IIR5RST_Msk)

/**
  * @brief  Judge is IIR5 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsIIR5SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_IIR5RST_Msk, RCU_AHB1RSTR_IIR5RST_Pos)

/**
  * @brief  IIR4 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR4SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_IIR4RST_Msk)

/**
  * @brief  IIR4 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR4SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_IIR4RST_Msk)

/**
  * @brief  Judge is IIR4 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsIIR4SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_IIR4RST_Msk, RCU_AHB1RSTR_IIR4RST_Pos)

/**
  * @brief  IIR3 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR3SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_IIR3RST_Msk)

/**
  * @brief  IIR3 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR3SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_IIR3RST_Msk)

/**
  * @brief  Judge is IIR3 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsIIR3SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_IIR3RST_Msk, RCU_AHB1RSTR_IIR3RST_Pos)

/**
  * @brief  IIR2 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR2SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_IIR2RST_Msk)

/**
  * @brief  IIR2 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR2SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_IIR2RST_Msk)

/**
  * @brief  Judge is IIR2 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsIIR2SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_IIR2RST_Msk, RCU_AHB1RSTR_IIR2RST_Pos)

/**
  * @brief  IIR1 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR1SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_IIR1RST_Msk)

/**
  * @brief  IIR1 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR1SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_IIR1RST_Msk)

/**
  * @brief  Judge is IIR1 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsIIR1SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_IIR1RST_Msk, RCU_AHB1RSTR_IIR1RST_Pos)

/**
  * @brief  IIR0 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR0SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_IIR0RST_Msk)

/**
  * @brief  IIR0 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IIR0SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_IIR0RST_Msk)

/**
  * @brief  Judge is IIR0 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsIIR0SoftRstRelease(__RCU__)      READ_BIT_SHIFT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_IIR0RST_Msk, RCU_AHB1RSTR_IIR0RST_Pos)

/**
  * @brief  HRPWM Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWMSoftRst_Assert(__RCU__)       CLEAR_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_PWMRST_Msk)

/**
  * @brief  HRPWM Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HRPWMSoftRst_Release(__RCU__)      SET_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_PWMRST_Msk)

/**
  * @brief  Judge is HRPWM Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsHRPWMSoftRstRelease(__RCU__)     READ_BIT_SHIFT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_PWMRST_Msk, RCU_AHB1RSTR_PWMRST_Pos)

/**
  * @brief  CMP Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CMPSoftRst_Assert(__RCU__)         CLEAR_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_CMPRST_Msk)

/**
  * @brief  CMP Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CMPSoftRst_Release(__RCU__)        SET_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_CMPRST_Msk)

/**
  * @brief  Judge is CMP Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsCMPSoftRstRelease(__RCU__)       READ_BIT_SHIFT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_CMPRST_Msk, RCU_AHB1RSTR_CMPRST_Pos)

/**
  * @brief  DAC Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_DACSoftRst_Assert(__RCU__)         CLEAR_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_DACRST_Msk)

/**
  * @brief  DAC Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_DACSoftRst_Release(__RCU__)        SET_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_DACRST_Msk)

/**
  * @brief  Judge is DAC Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsDACSoftRstRelease(__RCU__)       READ_BIT_SHIFT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_DACRST_Msk, RCU_AHB1RSTR_DACRST_Pos)

/**
  * @brief  ADC Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_ADCSoftRst_Assert(__RCU__)         CLEAR_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_ADCRST_Msk)

/**
  * @brief  ADC Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_ADCSoftRst_Release(__RCU__)        SET_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_ADCRST_Msk)

/**
  * @brief  Judge is ADC Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsADCSoftRstRelease(__RCU__)       READ_BIT_SHIFT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_ADCRST_Msk, RCU_AHB1RSTR_ADCRST_Pos)

/**
  * @brief  USB Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_USBSoftRst_Assert(__RCU__)         CLEAR_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_USBRST_Msk)

/**
  * @brief  USB Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_USBSoftRst_Release(__RCU__)        SET_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_USBRST_Msk)

/**
  * @brief  Judge is USB Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsUSBSoftRstRelease(__RCU__)       READ_BIT_SHIFT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_USBRST_Msk, RCU_AHB1RSTR_USBRST_Pos)

/**
  * @brief  TMR10 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR10SoftRst_Assert(__RCU__)       CLEAR_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_TMR10RST_Msk)

/**
  * @brief  TMR10 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR10SoftRst_Release(__RCU__)      SET_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_TMR10RST_Msk)

/**
  * @brief  Judge is TMR10 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsTMR10SoftRstRelease(__RCU__)     READ_BIT_SHIFT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_TMR10RST_Msk, RCU_AHB1RSTR_TMR10RST_Pos)

/**
  * @brief  TMR9 Soft Reset Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR9SoftRst_Assert(__RCU__)        CLEAR_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_TMR9RST_Msk)

/**
  * @brief  TMR9 Soft Reset Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_TMR9SoftRst_Release(__RCU__)       SET_BIT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_TMR9RST_Msk)

/**
  * @brief  Judge is TMR9 Soft Reset Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Reset is Assert
  * @retval 1 Reset is Release
  */
#define __LL_RCU_IsTMR9SoftRstRelease(__RCU__)       READ_BIT_SHIFT((__RCU__)->AHB1RSTR, RCU_AHB1RSTR_TMR9RST_Msk, RCU_AHB1RSTR_TMR9RST_Pos)

/**
  * @brief  AHB1 Soft Reset all Assert
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_AHB1SoftRstAll_Assert(__RCU__)     WRITE_REG((__RCU__)->AHB1RSTR, 0x0)

/**
  * @brief  AHB1 Soft Reset all Release
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_AHB1SoftRstAll_Release(__RCU__)    WRITE_REG((__RCU__)->AHB1RSTR, 0xffffffffUL)

/**
  * @brief  Judge is AHB1 Soft Reset all Assert or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 isn't AHB1 Soft Reset all Assert
  * @retval 1 is AHB1 Soft Reset all Assert
  */
#define __LL_RCU_IsAHB1SoftRstAllAssert(__RCU__)    ((READ_REG((__RCU__)->AHB1RSTR) & 0x3fffUL) == 0x00)

/**
  * @brief  Judge is AHB1 Soft Reset all Release or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 isn't AHB1 Soft Reset all Release
  * @retval 1 is AHB1 Soft Reset all Release
  */
#define __LL_RCU_IsAHB1SoftRstAllRelease(__RCU__)   ((READ_REG((__RCU__)->AHB1RSTR) & 0x3fffUL) == 0x3fffUL)


/**
  * @brief  HSI Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HSI_En(__RCU__)                    SET_BIT((__RCU__)->XOSCCR, RCU_XOSCCR_HEN_Msk)

/**
  * @brief  HSI Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HSI_Dis(__RCU__)                   CLEAR_BIT((__RCU__)->XOSCCR, RCU_XOSCCR_HEN_Msk)

/**
  * @brief  XOSC DR Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  cur Current
  * @return None
  */
#define __LL_RCU_XOSC_DR_Set(__RCU__, cur)          \
        MODIFY_REG((__RCU__)->XOSCCR, RCU_XOSCCR_XDR_Msk, (((cur) & 0x7U) << RCU_XOSCCR_XDR_Pos))

/**
  * @brief  HSE Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HSE_En(__RCU__)                    SET_BIT((__RCU__)->XOSCCR, RCU_XOSCCR_XEN_Msk)

/**
  * @brief  HSE Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_HSE_Dis(__RCU__)                   CLEAR_BIT((__RCU__)->XOSCCR, RCU_XOSCCR_XEN_Msk)


/**
  * @brief  SYSCLK Switch Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_SysclkSwitch_En(__RCU__)           SET_BIT((__RCU__)->CSSCR, RCU_CSSCR_SSE_Msk)

/**
  * @brief  SYSCLK Switch Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_SysclkSwitch_Dis(__RCU__)          CLEAR_BIT((__RCU__)->CSSCR, RCU_CSSCR_SSE_Msk)

/**
  * @brief  Judge is XOSC Loss Pending or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 isn't XOSC Loss Pending
  * @retval 1 is XOSC Loss Pending
  */
#define __LL_RCU_IsXOSCLossPnd(__RCU__)             READ_BIT_SHIFT((__RCU__)->CSSCR, RCU_CSSCR_LPD_Msk, RCU_CSSCR_LPD_Pos)

/**
  * @brief  XOSC Loss NMI Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_XOSC_LossNMI_En(__RCU__)           SET_BIT((__RCU__)->CSSCR, RCU_CSSCR_LPE_Msk)

/**
  * @brief  XOSC Loss NMI Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_XOSC_LossNMI_Dis(__RCU__)          CLEAR_BIT((__RCU__)->CSSCR, RCU_CSSCR_LPE_Msk)

/**
  * @brief  XOSC Securce Switch Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_XOSC_SecSwitch_En(__RCU__)         SET_BIT((__RCU__)->CSSCR, RCU_CSSCR_SWE_Msk)

/**
  * @brief  XOSC Securce Switch Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_XOSC_SecSwitch_Dis(__RCU__)        CLEAR_BIT((__RCU__)->CSSCR, RCU_CSSCR_SWE_Msk)


/**
  * @brief  External Clock Input Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_ExtClkInput_En(__RCU__)            SET_BIT((__RCU__)->DBGCR, RCU_DBGCR_ECIE_Msk)

/**
  * @brief  External Clock Input Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_ExtClkInput_Dis(__RCU__)           CLEAR_BIT((__RCU__)->DBGCR, RCU_DBGCR_ECIE_Msk)

/**
  * @brief  Internal Clock Fanout Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IntClkFanout_En(__RCU__)           SET_BIT((__RCU__)->DBGCR, RCU_DBGCR_MCOEN_Msk)

/**
  * @brief  Internal Clock Fanout Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IntClkFanout_Dis(__RCU__)          CLEAR_BIT((__RCU__)->DBGCR, RCU_DBGCR_MCOEN_Msk)

/**
  * @brief  Internal Clock Fanout Source Set
  * @param  __RCU__ Specifies RCU peripheral
  * @param  src Internal Clock Fanout Source @ref RCU_IntClkFaoutSrcETypeDef
  * @return None
  */
#define __LL_RCU_IntClkFanoutSrc_Set(__RCU__, src)  \
        MODIFY_REG((__RCU__)->DBGCR, RCU_DBGCR_MCO_Msk, (((src) & 0x7UL) << RCU_DBGCR_MCO_Pos))


/**
  * @brief  IWDG Reset Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IWDG_Rst_En(__RCU__)               MODIFY_REG((__RCU__)->SRSTSR, 0x3fUL | RCU_SRSTSR_IWRSTE_Msk, RCU_SRSTSR_IWRSTE_Msk)

/**
  * @brief  IWDG Reset Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IWDG_Rst_Dis(__RCU__)              MODIFY_REG((__RCU__)->SRSTSR, 0x3fUL | RCU_SRSTSR_IWRSTE_Msk, 0)

/**
  * @brief  WWDG Reset Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_WWDG_Rst_En(__RCU__)               MODIFY_REG((__RCU__)->SRSTSR, 0x3fUL | RCU_SRSTSR_WWRSTE_Msk, RCU_SRSTSR_WWRSTE_Msk)

/**
  * @brief  WWDG Reset Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_WWDG_Rst_Dis(__RCU__)              MODIFY_REG((__RCU__)->SRSTSR, 0x3fUL | RCU_SRSTSR_WWRSTE_Msk, 0)

/**
  * @brief  CPU LockUp Reset Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CPU_LockUpRst_En(__RCU__)          MODIFY_REG((__RCU__)->SRSTSR, 0x3fUL | RCU_SRSTSR_LKRSTE_Msk, RCU_SRSTSR_LKRSTE_Msk)

/**
  * @brief  CPU LockUp Reset Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CPU_LockUpRst_Dis(__RCU__)         MODIFY_REG((__RCU__)->SRSTSR, 0x3fUL | RCU_SRSTSR_LKRSTE_Msk, 0)

/**
  * @brief  CPU SystemREQ Reset Enable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CPU_SystemReqRst_En(__RCU__)       MODIFY_REG((__RCU__)->SRSTSR, 0x3fUL | RCU_SRSTSR_SQRSTE_Msk, RCU_SRSTSR_SQRSTE_Msk)

/**
  * @brief  CPU SystemREQ Reset Disable
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CPU_SystemReqRst_Dis(__RCU__)      MODIFY_REG((__RCU__)->SRSTSR, 0x3fUL | RCU_SRSTSR_SQRSTE_Msk, 0)

/**
  * @brief  Judge WWDG Reset or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Isn't WWDG Reset
  * @retval 1 Is WWDG Reset
  */
#define __LL_RCU_IsWWDGRst(__RCU__)                                                         \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) ?                                         \
        (READ_BIT_SHIFT((__RCU__)->SRSR, RCU_SRSR_WWR_Msk, RCU_SRSR_WWR_Pos)) :             \
        (READ_BIT_SHIFT((__RCU__)->SRSTSR, RCU_SRSTSR_WWR_Msk, RCU_SRSTSR_WWR_Pos)))

/**
  * @brief  Clear WWDG Reset Pending
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_WWDGRst_Clr(__RCU__)                                                       \
        do {                                                                                \
            MODIFY_REG((__RCU__)->SRSR, 0x3fUL, RCU_SRSR_WWR_Msk);                          \
            MODIFY_REG((__RCU__)->SRSTSR, 0x3fUL, RCU_SRSTSR_WWR_Msk);                      \
        } while(0)          

/**
  * @brief  Judge IWDG Reset or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Isn't IWDG Reset
  * @retval 1 Is IWDG Reset
  */
#define __LL_RCU_IsIWDGRst(__RCU__)                                                         \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) ?                                         \
        (READ_BIT_SHIFT((__RCU__)->SRSR, RCU_SRSR_IWR_Msk, RCU_SRSR_IWR_Pos)) :             \
        (READ_BIT_SHIFT((__RCU__)->SRSTSR, RCU_SRSTSR_IWR_Msk, RCU_SRSTSR_IWR_Pos))) 

/**
  * @brief  Clear IWDG Reset Pending
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_IWDGRst_Clr(__RCU__)                                                       \
        do {                                                                                \
            MODIFY_REG((__RCU__)->SRSR, 0x3fUL, RCU_SRSR_IWR_Msk);                          \
            MODIFY_REG((__RCU__)->SRSTSR, 0x3fUL, RCU_SRSTSR_IWR_Msk);                      \
        } while(0)    

/**
  * @brief  Judge CPU LockUp Reset or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Isn't CPU LockUp Reset
  * @retval 1 Is CPU LockUp Reset
  */
#define __LL_RCU_IsCPULockUpRst(__RCU__)                                                    \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) ?                                         \
        (READ_BIT_SHIFT((__RCU__)->SRSR, RCU_SRSR_LKR_Msk, RCU_SRSR_LKR_Pos)) :             \
        (READ_BIT_SHIFT((__RCU__)->SRSTSR, RCU_SRSTSR_LKR_Msk, RCU_SRSTSR_LKR_Pos)))

/**
  * @brief  Clear CPU LockUp Reset Pending
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CPULockUpRst_Clr(__RCU__)                                                  \
        do {                                                                                \
            MODIFY_REG((__RCU__)->SRSR, 0x3fUL, RCU_SRSR_LKR_Msk);                          \
            MODIFY_REG((__RCU__)->SRSTSR, 0x3fUL, RCU_SRSTSR_LKR_Msk);                      \
        } while(0)   

/**
  * @brief  Judge CPU SystemREQ Reset or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Isn't CPU SystemREQ Reset
  * @retval 1 Is CPU SystemREQ Reset
  */
#define __LL_RCU_IsCPUSystemReqRst(__RCU__)                                                 \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) ?                                         \
        (READ_BIT_SHIFT((__RCU__)->SRSR, RCU_SRSR_SQR_Msk, RCU_SRSR_SQR_Pos)) :             \
        (READ_BIT_SHIFT((__RCU__)->SRSTSR, RCU_SRSTSR_SQR_Msk, RCU_SRSTSR_SQR_Pos)))

/**
  * @brief  Clear CPU SystemREQ Reset Pending
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_CPUSystemReqRst_Clr(__RCU__)                                               \
        do {                                                                                \
            MODIFY_REG((__RCU__)->SRSR, 0x3fUL, RCU_SRSR_SQR_Msk);                          \
            MODIFY_REG((__RCU__)->SRSTSR, 0x3fUL, RCU_SRSTSR_SQR_Msk);                      \
        } while(0)   

/**
  * @brief  Judge LowPower Reset or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Isn't LowPower Reset
  * @retval 1 Is LowPower Reset
  */
#define __LL_RCU_IsLowPowerRst(__RCU__)                                                     \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) ?                                         \
        (READ_BIT_SHIFT((__RCU__)->SRSR, RCU_SRSR_LPR_Msk, RCU_SRSR_LPR_Pos)) :             \
        (READ_BIT_SHIFT((__RCU__)->SRSTSR, RCU_SRSTSR_LPR_Msk, RCU_SRSTSR_LPR_Pos)))

/**
  * @brief  Clear LowPower Reset Pending
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_LowPowerRst_Clr(__RCU__)                                                   \
        do {                                                                                \
            MODIFY_REG((__RCU__)->SRSR, 0x3fUL, RCU_SRSR_LPR_Msk);                          \
            MODIFY_REG((__RCU__)->SRSTSR, 0x3fUL, RCU_SRSTSR_LPR_Msk);                      \
        } while(0)  

/**
  * @brief  Judge MCLR Reset or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 Isn't MCLR Reset
  * @retval 1 Is MCLR Reset
  */
#define __LL_RCU_IsMclrRst(__RCU__)                                                         \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) ?                                         \
        (READ_BIT_SHIFT((__RCU__)->SRSR, RCU_SRSR_MCR_Msk, RCU_SRSR_MCR_Pos)) :             \
        (READ_BIT_SHIFT((__RCU__)->SRSTSR, RCU_SRSTSR_MCR_Msk, RCU_SRSTSR_MCR_Pos)))

/**
  * @brief  Clear MCLR Reset Pending
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_MclrRst_Clr(__RCU__)                                                       \
        do {                                                                                \
            MODIFY_REG((__RCU__)->SRSR, 0x3fUL, RCU_SRSR_MCR_Msk);                          \
            MODIFY_REG((__RCU__)->SRSTSR, 0x3fUL, RCU_SRSTSR_MCR_Msk);                      \
        } while(0)  


/**
  * @brief  RCU Register Write Unlock
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_RegWrite_Unlock(__RCU__)           WRITE_REG((__RCU__)->KEYR, 0x3fac87e4)

/**
  * @brief  RCU Register Write Lock
  * @param  __RCU__ Specifies RCU peripheral
  * @return None
  */
#define __LL_RCU_RegWrite_Lock(__RCU__)             WRITE_REG((__RCU__)->KEYR, 0x1)

/**
  * @brief  Judge RCU Register is unlock or not
  * @param  __RCU__ Specifies RCU peripheral
  * @retval 0 RCU Register is lock
  * @retval 1 RCU Register is unlock
  */
#define __LL_RCU_IsRegWriteUnlock(__RCU__)          READ_BIT_SHIFT((__RCU__)->KEYR, RCU_KEYR_KEY_Msk, RCU_KEYR_KEY_Pos)


/**
  * @brief  RCU Register Write Operation
  * @param  expression RCU Register Read/Write Operation
  * @note   Only Write Operation need Unlock before Operation
  * @return None
  */
#define __LL_RCU_RegWrite_OPT(expression)   \
        do {                                \
            __LL_RCU_RegWrite_Unlock(RCU);  \
            expression;                     \
            __LL_RCU_RegWrite_Lock(RCU);    \
        } while(0)

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup RCU_LL_Exported_Types RCU LL Exported Types
  * @brief    RCU LL Exported Types
  * @{
  */

/**
  * @brief RCU CLK Div Definition
  */
typedef enum {
    RCU_CLK_DIV_IVD = 0,/*!< RCU CLK DIV IVD */
    RCU_CLK_DIV_1,      /*!< RCU CLK DIV 1   */
    RCU_CLK_DIV_2,      /*!< RCU CLK DIV 2   */
    RCU_CLK_DIV_3,      /*!< RCU CLK DIV 3   */
    RCU_CLK_DIV_4,      /*!< RCU CLK DIV 4   */
    RCU_CLK_DIV_5,      /*!< RCU CLK DIV 5   */
    RCU_CLK_DIV_6,      /*!< RCU CLK DIV 6   */
    RCU_CLK_DIV_7,      /*!< RCU CLK DIV 7   */
    RCU_CLK_DIV_8,      /*!< RCU CLK DIV 8   */
    RCU_CLK_DIV_9,      /*!< RCU CLK DIV 9   */
    RCU_CLK_DIV_10,     /*!< RCU CLK DIV 10  */
    RCU_CLK_DIV_11,     /*!< RCU CLK DIV 11  */
    RCU_CLK_DIV_12,     /*!< RCU CLK DIV 12  */
    RCU_CLK_DIV_13,     /*!< RCU CLK DIV 13  */
    RCU_CLK_DIV_14,     /*!< RCU CLK DIV 14  */
    RCU_CLK_DIV_15,     /*!< RCU CLK DIV 15  */
    RCU_CLK_DIV_16,     /*!< RCU CLK DIV 16  */
    RCU_CLK_DIV_17,     /*!< RCU CLK DIV 17  */
    RCU_CLK_DIV_18,     /*!< RCU CLK DIV 18  */
    RCU_CLK_DIV_19,     /*!< RCU CLK DIV 19  */
    RCU_CLK_DIV_20,     /*!< RCU CLK DIV 20  */
    RCU_CLK_DIV_21,     /*!< RCU CLK DIV 21  */
    RCU_CLK_DIV_22,     /*!< RCU CLK DIV 22  */
    RCU_CLK_DIV_23,     /*!< RCU CLK DIV 23  */
    RCU_CLK_DIV_24,     /*!< RCU CLK DIV 24  */
    RCU_CLK_DIV_25,     /*!< RCU CLK DIV 25  */
    RCU_CLK_DIV_26,     /*!< RCU CLK DIV 26  */
    RCU_CLK_DIV_27,     /*!< RCU CLK DIV 27  */
    RCU_CLK_DIV_28,     /*!< RCU CLK DIV 28  */
    RCU_CLK_DIV_29,     /*!< RCU CLK DIV 29  */
    RCU_CLK_DIV_30,     /*!< RCU CLK DIV 30  */
    RCU_CLK_DIV_31,     /*!< RCU CLK DIV 31  */
    RCU_CLK_DIV_32,     /*!< RCU CLK DIV 32  */
    RCU_CLK_DIV_33,     /*!< RCU CLK DIV 33  */
    RCU_CLK_DIV_34,     /*!< RCU CLK DIV 34  */
    RCU_CLK_DIV_35,     /*!< RCU CLK DIV 35  */
    RCU_CLK_DIV_36,     /*!< RCU CLK DIV 36  */
    RCU_CLK_DIV_37,     /*!< RCU CLK DIV 37  */
    RCU_CLK_DIV_38,     /*!< RCU CLK DIV 38  */
    RCU_CLK_DIV_39,     /*!< RCU CLK DIV 39  */
    RCU_CLK_DIV_40,     /*!< RCU CLK DIV 40  */
    RCU_CLK_DIV_41,     /*!< RCU CLK DIV 41  */
    RCU_CLK_DIV_42,     /*!< RCU CLK DIV 42  */
    RCU_CLK_DIV_43,     /*!< RCU CLK DIV 43  */
    RCU_CLK_DIV_44,     /*!< RCU CLK DIV 44  */
    RCU_CLK_DIV_45,     /*!< RCU CLK DIV 45  */
    RCU_CLK_DIV_46,     /*!< RCU CLK DIV 46  */
    RCU_CLK_DIV_47,     /*!< RCU CLK DIV 47  */
    RCU_CLK_DIV_48,     /*!< RCU CLK DIV 48  */
    RCU_CLK_DIV_49,     /*!< RCU CLK DIV 49  */
    RCU_CLK_DIV_50,     /*!< RCU CLK DIV 50  */
    RCU_CLK_DIV_51,     /*!< RCU CLK DIV 51  */
    RCU_CLK_DIV_52,     /*!< RCU CLK DIV 52  */
    RCU_CLK_DIV_53,     /*!< RCU CLK DIV 53  */
    RCU_CLK_DIV_54,     /*!< RCU CLK DIV 54  */
    RCU_CLK_DIV_55,     /*!< RCU CLK DIV 55  */
    RCU_CLK_DIV_56,     /*!< RCU CLK DIV 56  */
    RCU_CLK_DIV_57,     /*!< RCU CLK DIV 57  */
    RCU_CLK_DIV_58,     /*!< RCU CLK DIV 58  */
    RCU_CLK_DIV_59,     /*!< RCU CLK DIV 59  */
    RCU_CLK_DIV_60,     /*!< RCU CLK DIV 60  */
    RCU_CLK_DIV_61,     /*!< RCU CLK DIV 61  */
    RCU_CLK_DIV_62,     /*!< RCU CLK DIV 62  */
    RCU_CLK_DIV_63,     /*!< RCU CLK DIV 63  */
    RCU_CLK_DIV_64,     /*!< RCU CLK DIV 64  */
    RCU_CLK_DIV_65,     /*!< RCU CLK DIV 65  */
    RCU_CLK_DIV_66,     /*!< RCU CLK DIV 66  */
    RCU_CLK_DIV_67,     /*!< RCU CLK DIV 67  */
    RCU_CLK_DIV_68,     /*!< RCU CLK DIV 68  */
    RCU_CLK_DIV_69,     /*!< RCU CLK DIV 69  */
    RCU_CLK_DIV_70,     /*!< RCU CLK DIV 70  */
    RCU_CLK_DIV_71,     /*!< RCU CLK DIV 71  */
    RCU_CLK_DIV_72,     /*!< RCU CLK DIV 72  */
    RCU_CLK_DIV_73,     /*!< RCU CLK DIV 73  */
    RCU_CLK_DIV_74,     /*!< RCU CLK DIV 74  */
    RCU_CLK_DIV_75,     /*!< RCU CLK DIV 75  */
    RCU_CLK_DIV_76,     /*!< RCU CLK DIV 76  */
    RCU_CLK_DIV_77,     /*!< RCU CLK DIV 77  */
    RCU_CLK_DIV_78,     /*!< RCU CLK DIV 78  */
    RCU_CLK_DIV_79,     /*!< RCU CLK DIV 79  */
    RCU_CLK_DIV_80,     /*!< RCU CLK DIV 80  */
    RCU_CLK_DIV_81,     /*!< RCU CLK DIV 81  */
    RCU_CLK_DIV_82,     /*!< RCU CLK DIV 82  */
    RCU_CLK_DIV_83,     /*!< RCU CLK DIV 83  */
    RCU_CLK_DIV_84,     /*!< RCU CLK DIV 84  */
    RCU_CLK_DIV_85,     /*!< RCU CLK DIV 85  */
    RCU_CLK_DIV_86,     /*!< RCU CLK DIV 86  */
    RCU_CLK_DIV_87,     /*!< RCU CLK DIV 87  */
    RCU_CLK_DIV_88,     /*!< RCU CLK DIV 88  */
    RCU_CLK_DIV_89,     /*!< RCU CLK DIV 89  */
    RCU_CLK_DIV_90,     /*!< RCU CLK DIV 90  */
    RCU_CLK_DIV_91,     /*!< RCU CLK DIV 91  */
    RCU_CLK_DIV_92,     /*!< RCU CLK DIV 92  */
    RCU_CLK_DIV_93,     /*!< RCU CLK DIV 93  */
    RCU_CLK_DIV_94,     /*!< RCU CLK DIV 94  */
    RCU_CLK_DIV_95,     /*!< RCU CLK DIV 95  */
    RCU_CLK_DIV_96,     /*!< RCU CLK DIV 96  */
    RCU_CLK_DIV_97,     /*!< RCU CLK DIV 97  */
    RCU_CLK_DIV_98,     /*!< RCU CLK DIV 98  */
    RCU_CLK_DIV_99,     /*!< RCU CLK DIV 99  */
    RCU_CLK_DIV_100,    /*!< RCU CLK DIV 100 */
    RCU_CLK_DIV_101,    /*!< RCU CLK DIV 101 */
    RCU_CLK_DIV_102,    /*!< RCU CLK DIV 102 */
    RCU_CLK_DIV_103,    /*!< RCU CLK DIV 103 */
    RCU_CLK_DIV_104,    /*!< RCU CLK DIV 104 */
    RCU_CLK_DIV_105,    /*!< RCU CLK DIV 105 */
    RCU_CLK_DIV_106,    /*!< RCU CLK DIV 106 */
    RCU_CLK_DIV_107,    /*!< RCU CLK DIV 107 */
    RCU_CLK_DIV_108,    /*!< RCU CLK DIV 108 */
    RCU_CLK_DIV_109,    /*!< RCU CLK DIV 109 */
    RCU_CLK_DIV_110,    /*!< RCU CLK DIV 110 */
    RCU_CLK_DIV_111,    /*!< RCU CLK DIV 111 */
    RCU_CLK_DIV_112,    /*!< RCU CLK DIV 112 */
    RCU_CLK_DIV_113,    /*!< RCU CLK DIV 113 */
    RCU_CLK_DIV_114,    /*!< RCU CLK DIV 114 */
    RCU_CLK_DIV_115,    /*!< RCU CLK DIV 115 */
    RCU_CLK_DIV_116,    /*!< RCU CLK DIV 116 */
    RCU_CLK_DIV_117,    /*!< RCU CLK DIV 117 */
    RCU_CLK_DIV_118,    /*!< RCU CLK DIV 118 */
    RCU_CLK_DIV_119,    /*!< RCU CLK DIV 119 */
    RCU_CLK_DIV_120,    /*!< RCU CLK DIV 120 */
    RCU_CLK_DIV_121,    /*!< RCU CLK DIV 121 */
    RCU_CLK_DIV_122,    /*!< RCU CLK DIV 122 */
    RCU_CLK_DIV_123,    /*!< RCU CLK DIV 123 */
    RCU_CLK_DIV_124,    /*!< RCU CLK DIV 124 */
    RCU_CLK_DIV_125,    /*!< RCU CLK DIV 125 */
    RCU_CLK_DIV_126,    /*!< RCU CLK DIV 126 */
    RCU_CLK_DIV_127,    /*!< RCU CLK DIV 127 */
    RCU_CLK_DIV_128,    /*!< RCU CLK DIV 128 */
    RCU_CLK_DIV_129,    /*!< RCU CLK DIV 129 */
    RCU_CLK_DIV_130,    /*!< RCU CLK DIV 130 */
    RCU_CLK_DIV_131,    /*!< RCU CLK DIV 131 */
    RCU_CLK_DIV_132,    /*!< RCU CLK DIV 132 */
    RCU_CLK_DIV_133,    /*!< RCU CLK DIV 133 */
    RCU_CLK_DIV_134,    /*!< RCU CLK DIV 134 */
    RCU_CLK_DIV_135,    /*!< RCU CLK DIV 135 */
    RCU_CLK_DIV_136,    /*!< RCU CLK DIV 136 */
    RCU_CLK_DIV_137,    /*!< RCU CLK DIV 137 */
    RCU_CLK_DIV_138,    /*!< RCU CLK DIV 138 */
    RCU_CLK_DIV_139,    /*!< RCU CLK DIV 139 */
    RCU_CLK_DIV_140,    /*!< RCU CLK DIV 140 */
    RCU_CLK_DIV_141,    /*!< RCU CLK DIV 141 */
    RCU_CLK_DIV_142,    /*!< RCU CLK DIV 142 */
    RCU_CLK_DIV_143,    /*!< RCU CLK DIV 143 */
    RCU_CLK_DIV_144,    /*!< RCU CLK DIV 144 */
    RCU_CLK_DIV_145,    /*!< RCU CLK DIV 145 */
    RCU_CLK_DIV_146,    /*!< RCU CLK DIV 146 */
    RCU_CLK_DIV_147,    /*!< RCU CLK DIV 147 */
    RCU_CLK_DIV_148,    /*!< RCU CLK DIV 148 */
    RCU_CLK_DIV_149,    /*!< RCU CLK DIV 149 */
    RCU_CLK_DIV_150,    /*!< RCU CLK DIV 150 */
    RCU_CLK_DIV_151,    /*!< RCU CLK DIV 151 */
    RCU_CLK_DIV_152,    /*!< RCU CLK DIV 152 */
    RCU_CLK_DIV_153,    /*!< RCU CLK DIV 153 */
    RCU_CLK_DIV_154,    /*!< RCU CLK DIV 154 */
    RCU_CLK_DIV_155,    /*!< RCU CLK DIV 155 */
    RCU_CLK_DIV_156,    /*!< RCU CLK DIV 156 */
    RCU_CLK_DIV_157,    /*!< RCU CLK DIV 157 */
    RCU_CLK_DIV_158,    /*!< RCU CLK DIV 158 */
    RCU_CLK_DIV_159,    /*!< RCU CLK DIV 159 */
    RCU_CLK_DIV_160,    /*!< RCU CLK DIV 160 */
    RCU_CLK_DIV_161,    /*!< RCU CLK DIV 161 */
    RCU_CLK_DIV_162,    /*!< RCU CLK DIV 162 */
    RCU_CLK_DIV_163,    /*!< RCU CLK DIV 163 */
    RCU_CLK_DIV_164,    /*!< RCU CLK DIV 164 */
    RCU_CLK_DIV_165,    /*!< RCU CLK DIV 165 */
    RCU_CLK_DIV_166,    /*!< RCU CLK DIV 166 */
    RCU_CLK_DIV_167,    /*!< RCU CLK DIV 167 */
    RCU_CLK_DIV_168,    /*!< RCU CLK DIV 168 */
    RCU_CLK_DIV_169,    /*!< RCU CLK DIV 169 */
    RCU_CLK_DIV_170,    /*!< RCU CLK DIV 170 */
    RCU_CLK_DIV_171,    /*!< RCU CLK DIV 171 */
    RCU_CLK_DIV_172,    /*!< RCU CLK DIV 172 */
    RCU_CLK_DIV_173,    /*!< RCU CLK DIV 173 */
    RCU_CLK_DIV_174,    /*!< RCU CLK DIV 174 */
    RCU_CLK_DIV_175,    /*!< RCU CLK DIV 175 */
    RCU_CLK_DIV_176,    /*!< RCU CLK DIV 176 */
    RCU_CLK_DIV_177,    /*!< RCU CLK DIV 177 */
    RCU_CLK_DIV_178,    /*!< RCU CLK DIV 178 */
    RCU_CLK_DIV_179,    /*!< RCU CLK DIV 179 */
    RCU_CLK_DIV_180,    /*!< RCU CLK DIV 180 */
    RCU_CLK_DIV_181,    /*!< RCU CLK DIV 181 */
    RCU_CLK_DIV_182,    /*!< RCU CLK DIV 182 */
    RCU_CLK_DIV_183,    /*!< RCU CLK DIV 183 */
    RCU_CLK_DIV_184,    /*!< RCU CLK DIV 184 */
    RCU_CLK_DIV_185,    /*!< RCU CLK DIV 185 */
    RCU_CLK_DIV_186,    /*!< RCU CLK DIV 186 */
    RCU_CLK_DIV_187,    /*!< RCU CLK DIV 187 */
    RCU_CLK_DIV_188,    /*!< RCU CLK DIV 188 */
    RCU_CLK_DIV_189,    /*!< RCU CLK DIV 189 */
    RCU_CLK_DIV_190,    /*!< RCU CLK DIV 190 */
    RCU_CLK_DIV_191,    /*!< RCU CLK DIV 191 */
    RCU_CLK_DIV_192,    /*!< RCU CLK DIV 192 */
    RCU_CLK_DIV_193,    /*!< RCU CLK DIV 193 */
    RCU_CLK_DIV_194,    /*!< RCU CLK DIV 194 */
    RCU_CLK_DIV_195,    /*!< RCU CLK DIV 195 */
    RCU_CLK_DIV_196,    /*!< RCU CLK DIV 196 */
    RCU_CLK_DIV_197,    /*!< RCU CLK DIV 197 */
    RCU_CLK_DIV_198,    /*!< RCU CLK DIV 198 */
    RCU_CLK_DIV_199,    /*!< RCU CLK DIV 199 */
    RCU_CLK_DIV_200,    /*!< RCU CLK DIV 200 */
    RCU_CLK_DIV_201,    /*!< RCU CLK DIV 201 */
    RCU_CLK_DIV_202,    /*!< RCU CLK DIV 202 */
    RCU_CLK_DIV_203,    /*!< RCU CLK DIV 203 */
    RCU_CLK_DIV_204,    /*!< RCU CLK DIV 204 */
    RCU_CLK_DIV_205,    /*!< RCU CLK DIV 205 */
    RCU_CLK_DIV_206,    /*!< RCU CLK DIV 206 */
    RCU_CLK_DIV_207,    /*!< RCU CLK DIV 207 */
    RCU_CLK_DIV_208,    /*!< RCU CLK DIV 208 */
    RCU_CLK_DIV_209,    /*!< RCU CLK DIV 209 */
    RCU_CLK_DIV_210,    /*!< RCU CLK DIV 210 */
    RCU_CLK_DIV_211,    /*!< RCU CLK DIV 211 */
    RCU_CLK_DIV_212,    /*!< RCU CLK DIV 212 */
    RCU_CLK_DIV_213,    /*!< RCU CLK DIV 213 */
    RCU_CLK_DIV_214,    /*!< RCU CLK DIV 214 */
    RCU_CLK_DIV_215,    /*!< RCU CLK DIV 215 */
    RCU_CLK_DIV_216,    /*!< RCU CLK DIV 216 */
    RCU_CLK_DIV_217,    /*!< RCU CLK DIV 217 */
    RCU_CLK_DIV_218,    /*!< RCU CLK DIV 218 */
    RCU_CLK_DIV_219,    /*!< RCU CLK DIV 219 */
    RCU_CLK_DIV_220,    /*!< RCU CLK DIV 220 */
    RCU_CLK_DIV_221,    /*!< RCU CLK DIV 221 */
    RCU_CLK_DIV_222,    /*!< RCU CLK DIV 222 */
    RCU_CLK_DIV_223,    /*!< RCU CLK DIV 223 */
    RCU_CLK_DIV_224,    /*!< RCU CLK DIV 224 */
    RCU_CLK_DIV_225,    /*!< RCU CLK DIV 225 */
    RCU_CLK_DIV_226,    /*!< RCU CLK DIV 226 */
    RCU_CLK_DIV_227,    /*!< RCU CLK DIV 227 */
    RCU_CLK_DIV_228,    /*!< RCU CLK DIV 228 */
    RCU_CLK_DIV_229,    /*!< RCU CLK DIV 229 */
    RCU_CLK_DIV_230,    /*!< RCU CLK DIV 230 */
    RCU_CLK_DIV_231,    /*!< RCU CLK DIV 231 */
    RCU_CLK_DIV_232,    /*!< RCU CLK DIV 232 */
    RCU_CLK_DIV_233,    /*!< RCU CLK DIV 233 */
    RCU_CLK_DIV_234,    /*!< RCU CLK DIV 234 */
    RCU_CLK_DIV_235,    /*!< RCU CLK DIV 235 */
    RCU_CLK_DIV_236,    /*!< RCU CLK DIV 236 */
    RCU_CLK_DIV_237,    /*!< RCU CLK DIV 237 */
    RCU_CLK_DIV_238,    /*!< RCU CLK DIV 238 */
    RCU_CLK_DIV_239,    /*!< RCU CLK DIV 239 */
    RCU_CLK_DIV_240,    /*!< RCU CLK DIV 240 */
    RCU_CLK_DIV_241,    /*!< RCU CLK DIV 241 */
    RCU_CLK_DIV_242,    /*!< RCU CLK DIV 242 */
    RCU_CLK_DIV_243,    /*!< RCU CLK DIV 243 */
    RCU_CLK_DIV_244,    /*!< RCU CLK DIV 244 */
    RCU_CLK_DIV_245,    /*!< RCU CLK DIV 245 */
    RCU_CLK_DIV_246,    /*!< RCU CLK DIV 246 */
    RCU_CLK_DIV_247,    /*!< RCU CLK DIV 247 */
    RCU_CLK_DIV_248,    /*!< RCU CLK DIV 248 */
    RCU_CLK_DIV_249,    /*!< RCU CLK DIV 249 */
    RCU_CLK_DIV_250,    /*!< RCU CLK DIV 250 */
    RCU_CLK_DIV_251,    /*!< RCU CLK DIV 251 */
    RCU_CLK_DIV_252,    /*!< RCU CLK DIV 252 */
    RCU_CLK_DIV_253,    /*!< RCU CLK DIV 253 */
    RCU_CLK_DIV_254,    /*!< RCU CLK DIV 254 */
    RCU_CLK_DIV_255,    /*!< RCU CLK DIV 255 */
    RCU_CLK_DIV_256,    /*!< RCU CLK DIV 256 */
} RCU_ClkDivETypeDef;

/**
  * @brief RCU PLL GVCO Definition
  */
typedef enum {
    PLL_GVCO_0 = 0,             /*!< RCU PLL GVCO 0 */
    PLL_GVCO_1,                 /*!< RCU PLL GVCO 1 */
    PLL_GVCO_2,                 /*!< RCU PLL GVCO 2 */
    PLL_GVCO_3,                 /*!< RCU PLL GVCO 3 */
} RCU_PllGvcoETypeDef;

/**
  * @brief RCU PLL Band Definition
  */
typedef enum {
    PLL_BAND_0 = 0,         /*!< RCU PLL Band 0: 200~280    */
    PLL_BAND_1,             /*!< RCU PLL Band 1: 260~380    */
    PLL_BAND_2,             /*!< RCU PLL Band 2: 320~430    */
    PLL_BAND_3,             /*!< RCU PLL Band 3: 400~500    */
} RCU_PllBandETypeDef;

/**
  * @brief RCU PLLCLK Source Definition
  */
typedef enum {
    PLLCLK_SRC_HSE = 0,         /*!< PLLCLK Source HSE  */
    PLLCLK_SRC_HSI = 1,         /*!< PLLCLK Source HSI  */
    PLLCLK_SRC_EXT = 3,         /*!< PLLCLK Source EXT  */
} RCU_PllClkSrcETypeDef;

/**
  * @brief RCU SYSCLK Source Definition
  */
typedef enum {
    SYSCLK_SRC_RC8M = 0,        /*!< RCU SYSCLK Source RC8M     */
    SYSCLK_SRC_RC32K,           /*!< RCU SYSCLK Source RC32K    */
    SYSCLK_SRC_PLL0DivClk,      /*!< RCU SYSCLK Source PLL0/N   */
    SYSCLK_SRC_XOSC,            /*!< RCU SYSCLK Source XOSC     */
} RCU_SysclkSrcETypeDef;

/**
  * @brief RCU Clock Source Definition
  */
typedef enum {
    RCU_CLK_SRC_RC8M = 0,       /*!< RCU CLK Source RC8M    */
    RCU_CLK_SRC_PLL0,           /*!< RCU CLK Source PLL0    */
} RCU_ClkSrcETypeDef;

/**
  * @brief RCU Clock Source Extend Definition
  */
typedef enum {
    RCU_CLK_SRC_EX_HSI = 0,             /*!< LPTMR CLK Source HSI     */
    RCU_CLK_SRC_EX_APB0CLK = 1,         /*!< LPTMR CLK Source APB0CLK */
    RCU_CLK_SRC_EX_HSE = 2,             /*!< LPTMR CLK Source HSE     */
    RCU_CLK_SRC_EX_LSI = 3,             /*!< LPTMR CLK Source LSI     */
} RCU_ClkSrcExETypeDef;

/**
  * @brief RCU Internal Clock Faout Source Definition
  */
typedef enum {
    RCU_INT_CLK_FAOUT_SRC_RC32K = 0,    /*!< RCU Internal Clock Faout Source RC32K      */
    RCU_INT_CLK_FAOUT_SRC_RC8M,         /*!< RCU Internal Clock Faout Source RC8M       */
    RCU_INT_CLK_FAOUT_SRC_XOSC,         /*!< RCU Internal Clock Faout Source XOSC       */
    RCU_INT_CLK_FAOUT_SRC_SYSCLK,       /*!< RCU Internal Clock Faout Source SYSCLK     */
    RCU_INT_CLK_FAOUT_SRC_PLL0_DIV16,   /*!< RCU Internal Clock Faout Source PLL0_DIV16 */
    RCU_INT_CLK_FAOUT_SRC_RSV0,         /*!< RCU Internal Clock Faout Source RSV0 */
    RCU_INT_CLK_FAOUT_SRC_FCLK,         /*!< RCU Internal Clock Faout Source FCLK       */
    RCU_INT_CLK_FAOUT_SRC_ATECLK,       /*!< RCU Internal Clock Faout Source ATECLK     */
} RCU_IntClkFaoutSrcETypeDef;


/**
  * @brief RCU SYSCLK Config Definition
  */
typedef struct __RCU_SysclkUserCfgTypeDef {
    RCU_SysclkSrcETypeDef sysclk_src;   /*!< SYSCLK Source      */
    RCU_PllClkSrcETypeDef pll0clk_src;  /*!< PLLCLK Source      */
    uint32_t sysclk_freq;               /*!< SYSCLK Freq        */
    uint32_t pll0clk_src_freq;          /*!< PLLCLK Source Freq */
    RCU_ClkDivETypeDef apb0_clk_div;    /*!< APB0 clock Div     */
    RCU_ClkDivETypeDef apb1_clk_div;    /*!< APB1 clock Div     */
    RCU_ClkDivETypeDef ahb_clk_div;     /*!< AHB0&1 clock Div   */
} RCU_SysclkUserCfgTypeDef;

/**
  * @brief RCU PLL Config Definition
  */
typedef struct __RCU_PLLUserCfgTypeDef {
    RCU_PllClkSrcETypeDef pll_clk_src;  /*!< PLLCLK Source      */
    uint32_t pll_in_freq;               /*!< PLLCLK Input Freq  */
    uint32_t pll_user_freq;             /*!< PLLCLK User Freq   */
} RCU_PLLUserCfgTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup RCU_LL_Exported_Functions
  * @{
  */

/** @addtogroup RCU_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_RCU_SysclkInit(RCU_TypeDef *Instance, RCU_SysclkUserCfgTypeDef *sysclk_cfg);
LL_StatusETypeDef LL_RCU_ADC_ClkCfg(RCU_ClkSrcETypeDef src, RCU_ClkDivETypeDef div);
LL_StatusETypeDef LL_RCU_HRPWM_ClkCfg(RCU_ClkSrcETypeDef src, RCU_ClkDivETypeDef div);
LL_StatusETypeDef LL_RCU_CAN_ClkCfg(RCU_ClkSrcETypeDef src, RCU_ClkDivETypeDef div);
LL_StatusETypeDef LL_RCU_USB_ClkCfg(RCU_ClkSrcETypeDef src, RCU_ClkDivETypeDef div);
LL_StatusETypeDef LL_RCU_LPTMR_ClkCfg(RCU_ClkSrcExETypeDef src);
uint32_t LL_RCU_SysclkGet(void);
uint32_t LL_RCU_AHBClkGet(void);
uint32_t LL_RCU_APB0ClkGet(void);
uint32_t LL_RCU_APB1ClkGet(void);
/**
  * @}
  */


/** @addtogroup RCU_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_RCU_Pll0Cfg(RCU_TypeDef *Instance, RCU_PLLUserCfgTypeDef *pll0_cfg);
/**
  * @}
  */


/** @addtogroup RCU_LL_Exported_Functions_Group3
  * @{
  */
/* Internal Class Peripheral */
void LL_RCU_EFLASH_ClkEnRstRelease(void);
void LL_RCU_EFLASH_ClkDisRstAssert(void);
void LL_RCU_DMA_ClkEnRstRelease(void);
void LL_RCU_DMA_ClkDisRstAssert(void);
void LL_RCU_CORDIC_ClkEnRstRelease(void);
void LL_RCU_CORDIC_ClkDisRstAssert(void);
void LL_RCU_TMR0_ClkEnRstRelease(void);
void LL_RCU_TMR0_ClkDisRstAssert(void);
void LL_RCU_TMR1_ClkEnRstRelease(void);
void LL_RCU_TMR1_ClkDisRstAssert(void);
void LL_RCU_TMR2_ClkEnRstRelease(void);
void LL_RCU_TMR2_ClkDisRstAssert(void);
void LL_RCU_TMR3_ClkEnRstRelease(void);
void LL_RCU_TMR3_ClkDisRstAssert(void);
void LL_RCU_TMR4_ClkEnRstRelease(void);
void LL_RCU_TMR4_ClkDisRstAssert(void);
void LL_RCU_TMR7_ClkEnRstRelease(void);
void LL_RCU_TMR7_ClkDisRstAssert(void);
void LL_RCU_TMR8_ClkEnRstRelease(void);
void LL_RCU_TMR8_ClkDisRstAssert(void);
void LL_RCU_TMR9_ClkEnRstRelease(void);
void LL_RCU_TMR9_ClkDisRstAssert(void);
void LL_RCU_TMR10_ClkEnRstRelease(void);
void LL_RCU_TMR10_ClkDisRstAssert(void);
void LL_RCU_TMR6_ClkEnRstRelease(void);
void LL_RCU_TMR6_ClkDisRstAssert(void);
void LL_RCU_QEI0_ClkEnRstRelease(void);
void LL_RCU_QEI0_ClkDisRstAssert(void);
void LL_RCU_QEI1_ClkEnRstRelease(void);
void LL_RCU_QEI1_ClkDisRstAssert(void);
void LL_RCU_QEI2_ClkEnRstRelease(void);
void LL_RCU_QEI2_ClkDisRstAssert(void);
void LL_RCU_IIR0_ClkEnRstRelease(void);
void LL_RCU_IIR0_ClkDisRstAssert(void);
void LL_RCU_IIR1_ClkEnRstRelease(void);
void LL_RCU_IIR1_ClkDisRstAssert(void);
void LL_RCU_IIR2_ClkEnRstRelease(void);
void LL_RCU_IIR2_ClkDisRstAssert(void);
void LL_RCU_IIR3_ClkEnRstRelease(void);
void LL_RCU_IIR3_ClkDisRstAssert(void);
void LL_RCU_IIR4_ClkEnRstRelease(void);
void LL_RCU_IIR4_ClkDisRstAssert(void);
void LL_RCU_IIR5_ClkEnRstRelease(void);
void LL_RCU_IIR5_ClkDisRstAssert(void);

/* Interface Class Peripheral */
void LL_RCU_GPIOA_ClkEnRstRelease(void);
void LL_RCU_GPIOA_ClkDisRstAssert(void);
void LL_RCU_GPIOB_ClkEnRstRelease(void);
void LL_RCU_GPIOB_ClkDisRstAssert(void);
void LL_RCU_GPIOC_ClkEnRstRelease(void);
void LL_RCU_GPIOC_ClkDisRstAssert(void);
void LL_RCU_GPIOD_ClkEnRstRelease(void);
void LL_RCU_GPIOD_ClkDisRstAssert(void);
void LL_RCU_GPIOE_ClkEnRstRelease(void);
void LL_RCU_GPIOE_ClkDisRstAssert(void);
void LL_RCU_GPIOF_ClkEnRstRelease(void);
void LL_RCU_GPIOF_ClkDisRstAssert(void);
void LL_RCU_I2C0_ClkEnRstRelease(void);
void LL_RCU_I2C0_ClkDisRstAssert(void);
void LL_RCU_I2C1_ClkEnRstRelease(void);
void LL_RCU_I2C1_ClkDisRstAssert(void);
void LL_RCU_I2C2_ClkEnRstRelease(void);
void LL_RCU_I2C2_ClkDisRstAssert(void);
void LL_RCU_UART0_ClkEnRstRelease(void);
void LL_RCU_UART0_ClkDisRstAssert(void);
void LL_RCU_UART1_ClkEnRstRelease(void);
void LL_RCU_UART1_ClkDisRstAssert(void);
void LL_RCU_UART2_ClkEnRstRelease(void);
void LL_RCU_UART2_ClkDisRstAssert(void);
void LL_RCU_UART3_ClkEnRstRelease(void);
void LL_RCU_UART3_ClkDisRstAssert(void);
void LL_RCU_UART4_ClkEnRstRelease(void);
void LL_RCU_UART4_ClkDisRstAssert(void);
void LL_RCU_SPI0_ClkEnRstRelease(void);
void LL_RCU_SPI0_ClkDisRstAssert(void);
void LL_RCU_SPI1_ClkEnRstRelease(void);
void LL_RCU_SPI1_ClkDisRstAssert(void);
void LL_RCU_CAN0_ClkEnRstRelease(void);
void LL_RCU_CAN0_ClkDisRstAssert(void);
void LL_RCU_CAN1_ClkEnRstRelease(void);
void LL_RCU_CAN1_ClkDisRstAssert(void);
void LL_RCU_USB_ClkEnRstRelease(void);
void LL_RCU_USB_ClkDisRstAssert(void);
void LL_RCU_XIF_ClkEnRstRelease(void);
void LL_RCU_XIF_ClkDisRstAssert(void);

/* Analog Class Peripheral */
void LL_RCU_ADC0_ClkEnRstRelease(void);
void LL_RCU_ADC0_ClkDisRstAssert(void);
void LL_RCU_ADC1_ClkEnRstRelease(void);
void LL_RCU_ADC1_ClkDisRstAssert(void);
void LL_RCU_ADC2_ClkEnRstRelease(void);
void LL_RCU_ADC2_ClkDisRstAssert(void);
void LL_RCU_ADC3_ClkEnRstRelease(void);
void LL_RCU_ADC3_ClkDisRstAssert(void);
void LL_RCU_DAC_ClkEnRstRelease(void);
void LL_RCU_DAC_ClkDisRstAssert(void);
void LL_RCU_CMP_ClkEnRstRelease(void);
void LL_RCU_CMP_ClkDisRstAssert(void);
void LL_RCU_HRPWM_ClkEnRstRelease(void);
void LL_RCU_HRPWM_ClkDisRstAssert(void);
void LL_RCU_HRPWM0_ClkEnRstRelease(void);
void LL_RCU_HRPWM0_ClkDisRstAssert(void);
void LL_RCU_HRPWM1_ClkEnRstRelease(void);
void LL_RCU_HRPWM1_ClkDisRstAssert(void);
void LL_RCU_HRPWM2_ClkEnRstRelease(void);
void LL_RCU_HRPWM2_ClkDisRstAssert(void);
void LL_RCU_HRPWM3_ClkEnRstRelease(void);
void LL_RCU_HRPWM3_ClkDisRstAssert(void);
void LL_RCU_HRPWM4_ClkEnRstRelease(void);
void LL_RCU_HRPWM4_ClkDisRstAssert(void);
void LL_RCU_HRPWM5_ClkEnRstRelease(void);
void LL_RCU_HRPWM5_ClkDisRstAssert(void);
void LL_RCU_HRPWM6_ClkEnRstRelease(void);
void LL_RCU_HRPWM6_ClkDisRstAssert(void);
void LL_RCU_HRPWM7_ClkEnRstRelease(void);
void LL_RCU_HRPWM7_ClkDisRstAssert(void);
void LL_RCU_PDM0_ClkEnRstRelease(void);
void LL_RCU_PDM0_ClkDisRstAssert(void);
void LL_RCU_PDM1_ClkEnRstRelease(void);
void LL_RCU_PDM1_ClkDisRstAssert(void);
void LL_RCU_PDM2_ClkEnRstRelease(void);
void LL_RCU_PDM2_ClkDisRstAssert(void);
void LL_RCU_PDM3_ClkEnRstRelease(void);
void LL_RCU_PDM3_ClkDisRstAssert(void);

void LL_RCU_AllPeriphRstAssert(void);
void LL_RCU_AllPeriphRstRelease(void);
/**
  * @}
  */

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_RCU_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

