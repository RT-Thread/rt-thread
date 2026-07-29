/**
  ******************************************************************************
  * @file    tae32f53xx_ll_sysctrl.h
  * @author  MCD Application Team
  * @brief   Header file for SYSCTRL LL module.
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
#ifndef _TAE32F53XX_LL_SYSCTRL_H_
#define _TAE32F53XX_LL_SYSCTRL_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup SYSCTRL_LL
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/** @defgroup SYSCTRL_LL_Exported_Macros SYSCTRL LL Exported Macros
  * @brief    SYSCTRL LL Exported Macros
  * @{
  */

/**
  * @brief  PLL0 Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PLL0_En(__SYSCTRL__)           SET_BIT((__SYSCTRL__)->PLL0CR, SYSCTRL_PLL0_EN_Msk)

/**
  * @brief  PLL0 Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PLL0_Dis(__SYSCTRL__)          CLEAR_BIT((__SYSCTRL__)->PLL0CR, SYSCTRL_PLL0_EN_Msk)

/**
  * @brief  Judge PLL0 has Locked or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 PLL0 hasn't Locked
  * @retval 1 PLL0 has Locked
  */
#define __LL_SYSCTRL_PLL0_IsLocked(__SYSCTRL__)     \
        (READ_BIT((__SYSCTRL__)->PLL0CR, SYSCTRL_PLL0_LOCKED_Msk) >> SYSCTRL_PLL0_LOCKED_Pos)

/**
  * @brief  PLL0 LPF Select 8M
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PLL0_LPF_8M(__SYSCTRL__)       CLEAR_BIT((__SYSCTRL__)->PLL0CR, SYSCTRL_PLL0_LPF_Msk)

/**
  * @brief  PLL0 LPF Select 26M
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PLL0_LPF_26M(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->PLL0CR, SYSCTRL_PLL0_LPF_Msk)

/**
  * @brief  PLL0 Band Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  band PLL0 Band
  * @return None
  */
#define __LL_SYSCTRL_PLL0_Band_Set(__SYSCTRL__, band)           \
        MODIFY_REG((__SYSCTRL__)->PLL0CR, SYSCTRL_PLL0_BAND_Msk, band)

/**
  * @brief  PLL0 GVCO Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param vco PLL0 GVCO
  * @return None
  */
#define __LL_SYSCTRL_PLL0_GVCO_Set(__SYSCTRL__, vco)            \
        MODIFY_REG((__SYSCTRL__)->PLL0CR, SYSCTRL_PLL0_GVCO_Msk, vco)

/**
  * @brief  PLL0 DIV Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  div PLL0 Div
  * @return None
  */
#define __LL_SYSCTRL_PLL0_DIV_Set(__SYSCTRL__, div)             \
        MODIFY_REG((__SYSCTRL__)->PLL0CR, SYSCTRL_PLL0_DIV_Msk, (((div-1) & 0xfUL) << SYSCTRL_PLL0_DIV_Pos))

/**
  * @brief  PLL0 Pre Div Set to 2
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PLL0_PreDiv_2(__SYSCTRL__)                 CLEAR_BIT((__SYSCTRL__)->PLL0CR, SYSCTRL_PLL0_PREDIV_Msk)

/**
  * @brief  PLL0 Pre Div Set to 1
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PLL0_PreDiv_1(__SYSCTRL__)                 SET_BIT((__SYSCTRL__)->PLL0CR, SYSCTRL_PLL0_PREDIV_Msk)

/**
  * @brief  PLL0 Ref CLK Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param ref_clk PLL0 Ref CLK
  * @return None
  */
#define __LL_SYSCTRL_PLL0_RefClk_Set(__SYSCTRL__, ref_clk)      \
        MODIFY_REG((__SYSCTRL__)->PLL0CR, SYSCTRL_PLL0_REFCLK_Msk, ref_clk)


/**
  * @brief  PLL1 Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PLL1_En(__SYSCTRL__)                       SET_BIT((__SYSCTRL__)->PLL1CR, SYSCTRL_PLL1_EN_Msk)

/**
  * @brief  PLL1 Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PLL1_Dis(__SYSCTRL__)                      CLEAR_BIT((__SYSCTRL__)->PLL1CR, SYSCTRL_PLL1_EN_Msk)

/**
  * @brief  Judge PLL1 has Locked or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 PLL1 hasn't Locked
  * @retval 1 PLL1 has Locked
  */
#define __LL_SYSCTRL_PLL1_IsLocked(__SYSCTRL__)     \
        (READ_BIT((__SYSCTRL__)->PLL1CR, SYSCTRL_PLL1_LOCKED_Msk) >> SYSCTRL_PLL1_LOCKED_Pos)

/**
  * @brief  PLL1 LPF Select 8M
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PLL1_LPF_8M(__SYSCTRL__)       CLEAR_BIT((__SYSCTRL__)->PLL1CR, SYSCTRL_PLL1_LPF_Msk)

/**
  * @brief  PLL1 LPF Select 26M
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PLL1_LPF_26M(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->PLL1CR, SYSCTRL_PLL1_LPF_Msk)

/**
  * @brief  PLL1 Band Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  band PLL1 Band
  * @return None
  */
#define __LL_SYSCTRL_PLL1_Band_Set(__SYSCTRL__, band)           \
        MODIFY_REG((__SYSCTRL__)->PLL1CR, SYSCTRL_PLL1_BAND_Msk, band)

/**
  * @brief  PLL1 GVCO Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param vco PLL1 GVCO
  * @return None
  */
#define __LL_SYSCTRL_PLL1_GVCO_Set(__SYSCTRL__, vco)            \
        MODIFY_REG((__SYSCTRL__)->PLL1CR, SYSCTRL_PLL1_GVCO_Msk, vco)

/**
  * @brief  PLL1 DIV Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  div PLL1 Div
  * @return None
  */
#define __LL_SYSCTRL_PLL1_DIV_Set(__SYSCTRL__, div)             \
        MODIFY_REG((__SYSCTRL__)->PLL1CR, SYSCTRL_PLL1_DIV_Msk, (((div-1) & 0xfUL) << SYSCTRL_PLL1_DIV_Pos))

/**
  * @brief  PLL1 Pre Div Set to 2
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PLL1_PreDiv_2(__SYSCTRL__)                 CLEAR_BIT((__SYSCTRL__)->PLL1CR, SYSCTRL_PLL1_PREDIV_Msk)

/**
  * @brief  PLL1 Pre Div Set to None
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PLL1_PreDiv_1(__SYSCTRL__)                 SET_BIT((__SYSCTRL__)->PLL1CR, SYSCTRL_PLL1_PREDIV_Msk)

/**
  * @brief  PLL1 Ref CLK Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param ref_clk PLL1 Ref CLK
  * @return None
  */
#define __LL_SYSCTRL_PLL1_RefClk_Set(__SYSCTRL__, ref_clk)      \
        MODIFY_REG((__SYSCTRL__)->PLL1CR, SYSCTRL_PLL1_REFCLK_Msk, ref_clk)


/**
  * @brief  PLL2 Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PLL2_En(__SYSCTRL__)                       SET_BIT((__SYSCTRL__)->PLL2CR, SYSCTRL_PLL2_EN_Msk)

/**
  * @brief  PLL2 Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PLL2_Dis(__SYSCTRL__)                      CLEAR_BIT((__SYSCTRL__)->PLL2CR, SYSCTRL_PLL2_EN_Msk)

/**
  * @brief  Judge PLL2 has Locked or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 PLL2 hasn't Locked
  * @retval 1 PLL2 has Locked
  */
#define __LL_SYSCTRL_PLL2_IsLocked(__SYSCTRL__)     \
        (READ_BIT((__SYSCTRL__)->PLL2CR, SYSCTRL_PLL2_LOCKED_Msk) >> SYSCTRL_PLL2_LOCKED_Pos)

/**
  * @brief  PLL2 LPF Select 8M
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PLL2_LPF_8M(__SYSCTRL__)       CLEAR_BIT((__SYSCTRL__)->PLL2CR, SYSCTRL_PLL2_LPF_Msk)

/**
  * @brief  PLL2 LPF Select 26M
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PLL2_LPF_26M(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->PLL2CR, SYSCTRL_PLL2_LPF_Msk)

/**
  * @brief  PLL2 Band Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  band PLL2 Band
  * @return None
  */
#define __LL_SYSCTRL_PLL2_Band_Set(__SYSCTRL__, band)           \
        MODIFY_REG((__SYSCTRL__)->PLL2CR, SYSCTRL_PLL2_BAND_Msk, band)

/**
  * @brief  PLL2 GVCO Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param vco PLL2 GVCO
  * @return None
  */
#define __LL_SYSCTRL_PLL2_GVCO_Set(__SYSCTRL__, vco)            \
        MODIFY_REG((__SYSCTRL__)->PLL2CR, SYSCTRL_PLL2_GVCO_Msk, vco)

/**
  * @brief  PLL2 DIV Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  div PLL2 Div
  * @return None
  */
#define __LL_SYSCTRL_PLL2_DIV_Set(__SYSCTRL__, div)             \
        MODIFY_REG((__SYSCTRL__)->PLL2CR, SYSCTRL_PLL2_DIV_Msk, (((div-1) & 0xfUL) << SYSCTRL_PLL2_DIV_Pos))

/**
  * @brief  PLL2 Pre Div Set to 2
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PLL2_PreDiv_2(__SYSCTRL__)                 CLEAR_BIT((__SYSCTRL__)->PLL2CR, SYSCTRL_PLL2_PREDIV_Msk)

/**
  * @brief  PLL2 Pre Div Set to None
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PLL2_PreDiv_1(__SYSCTRL__)                 SET_BIT((__SYSCTRL__)->PLL2CR, SYSCTRL_PLL2_PREDIV_Msk)

/**
  * @brief  PLL2 Ref CLK Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param ref_clk PLL2 Ref CLK
  * @return None
  */
#define __LL_SYSCTRL_PLL2_RefClk_Set(__SYSCTRL__, ref_clk)      \
        MODIFY_REG((__SYSCTRL__)->PLL2CR, SYSCTRL_PLL2_REFCLK_Msk, ref_clk)


/**
  * @brief  SYSCLK Div Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  div SYSCLK Div
  * @return None
  */
#define __LL_SYSCTRL_SysClkDiv_Set(__SYSCTRL__, div)            \
        MODIFY_REG((__SYSCTRL__)->SCLKCR, SYSCTRL_SYSCLK_DIV_Msk, (((div-1) & 0xffUL) << SYSCTRL_SYSCLK_DIV_Pos))

/**
  * @brief  SYSCLK Source Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  src SYSCLK Source
  * @return None
  */
#define __LL_SYSCTRL_SysClkSrc_Set(__SYSCTRL__, src)            \
        MODIFY_REG((__SYSCTRL__)->SCLKCR, SYSCTRL_SYSCLK_SRC_Msk, src)


/**
  * @brief  APB1 CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_APB1Clk_En(__SYSCTRL__)        SET_BIT((__SYSCTRL__)->BCLKCR, SYSCTRL_APB1CLK_EN_Msk)

/**
  * @brief  APB1 CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_APB1Clk_Dis(__SYSCTRL__)       CLEAR_BIT((__SYSCTRL__)->BCLKCR, SYSCTRL_APB1CLK_EN_Msk)

/**
  * @brief  APB0 CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_APB0Clk_En(__SYSCTRL__)        SET_BIT((__SYSCTRL__)->BCLKCR, SYSCTRL_APB0CLK_EN_Msk)

/**
  * @brief  APB0 CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_APB0Clk_Dis(__SYSCTRL__)       CLEAR_BIT((__SYSCTRL__)->BCLKCR, SYSCTRL_APB0CLK_EN_Msk)

/**
  * @brief  AHB CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AHBClk_En(__SYSCTRL__)         SET_BIT((__SYSCTRL__)->BCLKCR, SYSCTRL_AHBCLK_EN_Msk)

/**
  * @brief  AHB CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AHBClk_Dis(__SYSCTRL__)        CLEAR_BIT((__SYSCTRL__)->BCLKCR, SYSCTRL_AHBCLK_EN_Msk)

/**
  * @brief  APB1 CLK Div SET
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  div APB1 Div
  * @return None
  */
#define __LL_SYSCTRL_APB1ClkDiv_Set(__SYSCTRL__, div)       \
        MODIFY_REG((__SYSCTRL__)->BCLKCR, SYSCTRL_APB1CLK_DIV_Msk, (((div-1) & 0xffUL) << SYSCTRL_APB1CLK_DIV_Pos))

/**
  * @brief  APB1 CLK Div GET
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return APB1 Div
  */
#define __LL_SYSCTRL_APB1ClkDiv_Get(__SYSCTRL__)            \
        ((READ_BIT((__SYSCTRL__)->BCLKCR, SYSCTRL_APB1CLK_DIV_Msk) >> SYSCTRL_APB1CLK_DIV_Pos) + 1)

/**
  * @brief  APB0 CLK Div SET
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  div APB0 Div
  * @return None
  */
#define __LL_SYSCTRL_APB0ClkDiv_Set(__SYSCTRL__, div)       \
        MODIFY_REG((__SYSCTRL__)->BCLKCR, SYSCTRL_APB0CLK_DIV_Msk, (((div-1) & 0xffUL) << SYSCTRL_APB0CLK_DIV_Pos))

/**
  * @brief  APB0 CLK Div GET
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return APB0 Div
  */
#define __LL_SYSCTRL_APB0ClkDiv_Get(__SYSCTRL__)            \
        ((READ_BIT((__SYSCTRL__)->BCLKCR, SYSCTRL_APB0CLK_DIV_Msk) >> SYSCTRL_APB0CLK_DIV_Pos) + 1)


/**
  * @brief  GPIOD Debounce CLK Source Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  src GPIOD Debounce CLK Source
  * @return None
  */
#define __LL_SYSCTRL_GPIODDbcSrc_Set(__SYSCTRL__, src)      MODIFY_REG((__SYSCTRL__)->FSRCCR, SYSCTRL_GPIOD_DBCCLK_SRC_Msk, src)

/**
  * @brief  GPIOC Debounce CLK Source Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  src GPIOC Debounce CLK Source
  * @return None
  */
#define __LL_SYSCTRL_GPIOCDbcSrc_Set(__SYSCTRL__, src)      MODIFY_REG((__SYSCTRL__)->FSRCCR, SYSCTRL_GPIOC_DBCCLK_SRC_Msk, src)

/**
  * @brief  GPIOB Debounce CLK Source Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  src GPIOB Debounce CLK Source
  * @return None
  */
#define __LL_SYSCTRL_GPIOBDbcSrc_Set(__SYSCTRL__, src)      MODIFY_REG((__SYSCTRL__)->FSRCCR, SYSCTRL_GPIOB_DBCCLK_SRC_Msk, src)

/**
  * @brief  GPIOA Debounce CLK Source Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  src GPIOA Debounce CLK Source
  * @return None
  */
#define __LL_SYSCTRL_GPIOADbcSrc_Set(__SYSCTRL__, src)      MODIFY_REG((__SYSCTRL__)->FSRCCR, SYSCTRL_GPIOA_DBCCLK_SRC_Msk, src)

/**
  * @brief  DFLASH Memory CLK Source Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  src DFLASH Memory CLK Source
  * @return None
  */
#define __LL_SYSCTRL_DFLASHMemClkSrc_Set(__SYSCTRL__, src)  MODIFY_REG((__SYSCTRL__)->FSRCCR, SYSCTRL_DFLASH_MEMCLK_SRC_Msk, src)

/**
  * @brief  EFLASH Memory CLK Source Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  src EFLASH Memory CLK Source
  * @return None
  */
#define __LL_SYSCTRL_EFLASHMemClkSrc_Set(__SYSCTRL__, src)  MODIFY_REG((__SYSCTRL__)->FSRCCR, SYSCTRL_EFLASH_MEMCLK_SRC_Msk, src)

/**
  * @brief  ADC Function CLK Source Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  src ADC Function CLK Source
  * @return None
  */
#define __LL_SYSCTRL_ADCFunClkSrc_Set(__SYSCTRL__, src)     MODIFY_REG((__SYSCTRL__)->FSRCCR, SYSCTRL_ADC_FUNCLK_SRC_Msk, src)

/**
  * @brief  HRPWM Function CLK Source Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  src HRPWM Function CLK Source
  * @return None
  */
#define __LL_SYSCTRL_HRPWMFunClkSrc_Set(__SYSCTRL__, src)   MODIFY_REG((__SYSCTRL__)->FSRCCR, SYSCTRL_HRPWM_FUNCLK_SRC_Msk, src)


/**
  * @brief  DFLASH Memory Clk Div Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  div DFLASH Memory Clk Div
  * @return None
  */
#define __LL_SYSCTRL_DFLASHMemClkDiv_Set(__SYSCTRL__, div)  \
        MODIFY_REG((__SYSCTRL__)->FCD0CR, SYSCTRL_DFLASH_MEMCLK_DIV_Msk, (((div-1) & 0xfUL) << SYSCTRL_DFLASH_MEMCLK_DIV_Pos))

/**
  * @brief  EFLASH Memory Clk Div Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  div EFLASH Memory Clk Div
  * @return None
  */
#define __LL_SYSCTRL_EFLASHMemClkDiv_Set(__SYSCTRL__, div)  \
        MODIFY_REG((__SYSCTRL__)->FCD0CR, SYSCTRL_EFLASH_MEMCLK_DIV_Msk, (((div-1) & 0xfUL) << SYSCTRL_EFLASH_MEMCLK_DIV_Pos))

/**
  * @brief  ADC Function Clk Div Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  div ADC Function Clk Div
  * @return None
  */
#define __LL_SYSCTRL_ADCFunClkDiv_Set(__SYSCTRL__, div)     \
        MODIFY_REG((__SYSCTRL__)->FCD0CR, SYSCTRL_ADC_FUNCLK_DIV_Msk, (((div-1) & 0x3UL) << SYSCTRL_ADC_FUNCLK_DIV_Pos))

/**
  * @brief  HRPWM Function Clk Div Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  div HRPWM Function Clk Div
  * @return None
  */
#define __LL_SYSCTRL_HRPWMFunClkDiv_Set(__SYSCTRL__, div)   \
        MODIFY_REG((__SYSCTRL__)->FCD0CR, SYSCTRL_HRPWM_FUNCLK_DIV_Msk, (((div-1) & 0x3UL) << SYSCTRL_HRPWM_FUNCLK_DIV_Pos))


/**
  * @brief  GPIOD Debounce CLK Div Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  div GPIOD Debounce CLK Div
  * @return None
  */
#define __LL_SYSCTRL_GPIODDbcClkDiv_Set(__SYSCTRL__, div)   \
        MODIFY_REG((__SYSCTRL__)->FCD1CR, SYSCTRL_GPIOD_DBCCLK_DIV_Msk, (((div-1) & 0xffUL) << SYSCTRL_GPIOD_DBCCLK_DIV_Pos))
/**
  * @brief  GPIOC Debounce CLK Div Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  div GPIOC Debounce CLK Div
  * @return None
  */
#define __LL_SYSCTRL_GPIOCDbcClkDiv_Set(__SYSCTRL__, div)   \
        MODIFY_REG((__SYSCTRL__)->FCD1CR, SYSCTRL_GPIOC_DBCCLK_DIV_Msk, (((div-1) & 0xffUL) << SYSCTRL_GPIOC_DBCCLK_DIV_Pos))

/**
  * @brief  GPIOB Debounce CLK Div Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  div GPIOB Debounce CLK Div
  * @return None
  */
#define __LL_SYSCTRL_GPIOBDbcClkDiv_Set(__SYSCTRL__, div)   \
        MODIFY_REG((__SYSCTRL__)->FCD1CR, SYSCTRL_GPIOB_DBCCLK_DIV_Msk, (((div-1) & 0xffUL) << SYSCTRL_GPIOB_DBCCLK_DIV_Pos))

/**
  * @brief  GPIOA Debounce CLK Div Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  div GPIOA Debounce CLK Div
  * @return None
  */
#define __LL_SYSCTRL_GPIOADbcClkDiv_Set(__SYSCTRL__, div)   \
        MODIFY_REG((__SYSCTRL__)->FCD1CR, SYSCTRL_GPIOA_DBCCLK_DIV_Msk, (((div-1) & 0xffUL) << SYSCTRL_GPIOA_DBCCLK_DIV_Pos))


/**
  * @brief  LSTIMER Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_LSTIMERBusClk_En(__SYSCTRL__)  SET_BIT((__SYSCTRL__)->APB0CCR, SYSCTRL_LSTIMER_BUSCLK_EN_Msk)

/**
  * @brief  LSTIMER Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_LSTIMERBusClk_Dis(__SYSCTRL__) CLEAR_BIT((__SYSCTRL__)->APB0CCR, SYSCTRL_LSTIMER_BUSCLK_EN_Msk)

/**
  * @brief  UART1 Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_UART1BusClk_En(__SYSCTRL__)    SET_BIT((__SYSCTRL__)->APB0CCR, SYSCTRL_UART1_BUSCLK_EN_Msk)

/**
  * @brief  UART1 Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_UART1BusClk_Dis(__SYSCTRL__)   CLEAR_BIT((__SYSCTRL__)->APB0CCR, SYSCTRL_UART1_BUSCLK_EN_Msk)

/**
  * @brief  UART0 Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_UART0BusClk_En(__SYSCTRL__)    SET_BIT((__SYSCTRL__)->APB0CCR, SYSCTRL_UART0_BUSCLK_EN_Msk)

/**
  * @brief  UART0 Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_UART0BusClk_Dis(__SYSCTRL__)   CLEAR_BIT((__SYSCTRL__)->APB0CCR, SYSCTRL_UART0_BUSCLK_EN_Msk)

/**
  * @brief  I2C1 Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_I2C1BusClk_En(__SYSCTRL__)     SET_BIT((__SYSCTRL__)->APB0CCR, SYSCTRL_I2C1_BUSCLK_EN_Msk)

/**
  * @brief  I2C1 Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_I2C1BusClk_Dis(__SYSCTRL__)    CLEAR_BIT((__SYSCTRL__)->APB0CCR, SYSCTRL_I2C1_BUSCLK_EN_Msk)

/**
  * @brief  I2C0 Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_I2C0BusClk_En(__SYSCTRL__)     SET_BIT((__SYSCTRL__)->APB0CCR, SYSCTRL_I2C0_BUSCLK_EN_Msk)

/**
  * @brief  I2C0 Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_I2C0BusClk_Dis(__SYSCTRL__)    CLEAR_BIT((__SYSCTRL__)->APB0CCR, SYSCTRL_I2C0_BUSCLK_EN_Msk)


/**
  * @brief  ECU Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ECUBusClk_En(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->APB1CCR, SYSCTRL_ECU_BUSCLK_EN_Msk)

/**
  * @brief  ECU Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ECUBusClk_Dis(__SYSCTRL__)     CLEAR_BIT((__SYSCTRL__)->APB1CCR, SYSCTRL_ECU_BUSCLK_EN_Msk)

/**
  * @brief  IIR4 Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR4BusClk_En(__SYSCTRL__)     SET_BIT((__SYSCTRL__)->APB1CCR, SYSCTRL_IIR4_BUSCLK_EN_Msk)

/**
  * @brief  IIR4 Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR4BusClk_Dis(__SYSCTRL__)    CLEAR_BIT((__SYSCTRL__)->APB1CCR, SYSCTRL_IIR4_BUSCLK_EN_Msk)

/**
  * @brief  IIR3 Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR3BusClk_En(__SYSCTRL__)     SET_BIT((__SYSCTRL__)->APB1CCR, SYSCTRL_IIR3_BUSCLK_EN_Msk)

/**
  * @brief  IIR3 Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR3BusClk_Dis(__SYSCTRL__)    CLEAR_BIT((__SYSCTRL__)->APB1CCR, SYSCTRL_IIR3_BUSCLK_EN_Msk)

/**
  * @brief  IIR2 Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR2BusClk_En(__SYSCTRL__)     SET_BIT((__SYSCTRL__)->APB1CCR, SYSCTRL_IIR2_BUSCLK_EN_Msk)

/**
  * @brief  IIR2 Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR2BusClk_Dis(__SYSCTRL__)    CLEAR_BIT((__SYSCTRL__)->APB1CCR, SYSCTRL_IIR2_BUSCLK_EN_Msk)

/**
  * @brief  IIR1 Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR1BusClk_En(__SYSCTRL__)     SET_BIT((__SYSCTRL__)->APB1CCR, SYSCTRL_IIR1_BUSCLK_EN_Msk)

/**
  * @brief  IIR1 Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR1BusClk_Dis(__SYSCTRL__)    CLEAR_BIT((__SYSCTRL__)->APB1CCR, SYSCTRL_IIR1_BUSCLK_EN_Msk)

/**
  * @brief  IIR0 Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR0BusClk_En(__SYSCTRL__)     SET_BIT((__SYSCTRL__)->APB1CCR, SYSCTRL_IIR0_BUSCLK_EN_Msk)

/**
  * @brief  IIR0 Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR0BusClk_Dis(__SYSCTRL__)    CLEAR_BIT((__SYSCTRL__)->APB1CCR, SYSCTRL_IIR0_BUSCLK_EN_Msk)

/**
  * @brief  DALI Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_DALIBusClk_En(__SYSCTRL__)     SET_BIT((__SYSCTRL__)->APB1CCR, SYSCTRL_DALI_BUSCLK_EN_Msk)

/**
  * @brief  DALI Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_DALIBusClk_Dis(__SYSCTRL__)    CLEAR_BIT((__SYSCTRL__)->APB1CCR, SYSCTRL_DALI_BUSCLK_EN_Msk)



/**
  * @brief  RAM2 Bus Clk Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_RAM2BusClk_En(__SYSCTRL__)     SET_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_RAM2_BUSCLK_EN_Msk)

/**
  * @brief  RAM2 Bus Clk Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_RAM2BusClk_Dis(__SYSCTRL__)    CLEAR_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_RAM2_BUSCLK_EN_Msk)

/**
  * @brief  RAM1 Bus Clk Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_RAM1BusClk_En(__SYSCTRL__)     SET_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_RAM1_BUSCLK_EN_Msk)

/**
  * @brief  RAM1 Bus Clk Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_RAM1BusClk_Dis(__SYSCTRL__)    CLEAR_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_RAM1_BUSCLK_EN_Msk)

/**
  * @brief  RAM0 Bus Clk Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_RAM0BusClk_En(__SYSCTRL__)     SET_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_RAM0_BUSCLK_EN_Msk)

/**
  * @brief  RAM0 Bus Clk Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_RAM0BusClk_Dis(__SYSCTRL__)    CLEAR_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_RAM0_BUSCLK_EN_Msk)

/**
  * @brief  USB Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_USBBusClk_En(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_USB_BUSCLK_EN_Msk)

/**
  * @brief  USB Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_USBBusClk_Dis(__SYSCTRL__)     CLEAR_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_USB_BUSCLK_EN_Msk)

/**
  * @brief  DFLASH Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_DFLASHBusClk_En(__SYSCTRL__)   SET_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_DFLASH_BUSCLK_EN_Msk)

/**
  * @brief  DFLASH Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_DFLASHBusClk_Dis(__SYSCTRL__)  CLEAR_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_DFLASH_BUSCLK_EN_Msk)

/**
  * @brief  EFLASH Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_EFLASHBusClk_En(__SYSCTRL__)   SET_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_EFLASH_BUSCLK_EN_Msk)

/**
  * @brief  EFLASH Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_EFLASHBusClk_Dis(__SYSCTRL__)  CLEAR_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_EFLASH_BUSCLK_EN_Msk)

/**
  * @brief  HRPWM Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_HRPWMBusClk_En(__SYSCTRL__)    SET_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_HRPWM_BUSCLK_EN_Msk)

/**
  * @brief  HRPWM Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_HRPWMBusClk_Dis(__SYSCTRL__)   CLEAR_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_HRPWM_BUSCLK_EN_Msk)

/**
  * @brief  ADC Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ADCBusClk_En(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_ADC_BUSCLK_EN_Msk)

/**
  * @brief  ADC Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ADCBusClk_Dis(__SYSCTRL__)     CLEAR_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_ADC_BUSCLK_EN_Msk)

/**
  * @brief  DAC Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_DACBusClk_En(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_DAC_BUSCLK_EN_Msk)

/**
  * @brief  DAC Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_DACBusClk_Dis(__SYSCTRL__)     CLEAR_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_DAC_BUSCLK_EN_Msk)

/**
  * @brief  CMP Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_CMPBusClk_En(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_CMP_BUSCLK_EN_Msk)

/**
  * @brief  CMP Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_CMPBusClk_Dis(__SYSCTRL__)     CLEAR_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_CMP_BUSCLK_EN_Msk)

/**
  * @brief  GPIOD Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIODBusClk_En(__SYSCTRL__)    SET_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_GPIOD_BUSCLK_EN_Msk)

/**
  * @brief  GPIOD Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIODBusClk_Dis(__SYSCTRL__)   CLEAR_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_GPIOD_BUSCLK_EN_Msk)

/**
  * @brief  GPIOC Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIOCBusClk_En(__SYSCTRL__)    SET_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_GPIOC_BUSCLK_EN_Msk)

/**
  * @brief  GPIOC Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIOCBusClk_Dis(__SYSCTRL__)   CLEAR_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_GPIOC_BUSCLK_EN_Msk)

/**
  * @brief  GPIOB Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIOBBusClk_En(__SYSCTRL__)    SET_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_GPIOB_BUSCLK_EN_Msk)

/**
  * @brief  GPIOB Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIOBBusClk_Dis(__SYSCTRL__)   CLEAR_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_GPIOB_BUSCLK_EN_Msk)

/**
  * @brief  GPIOA Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIOABusClk_En(__SYSCTRL__)    SET_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_GPIOA_BUSCLK_EN_Msk)

/**
  * @brief  GPIOA Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIOABusClk_Dis(__SYSCTRL__)   CLEAR_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_GPIOA_BUSCLK_EN_Msk)

/**
  * @brief  HSTIMER Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_HSTIMERBusClk_En(__SYSCTRL__)  SET_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_HSTIMER_BUSCLK_EN_Msk)

/**
  * @brief  HSTIMER Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_HSTIMERBusClk_Dis(__SYSCTRL__) CLEAR_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_HSTIMER_BUSCLK_EN_Msk)

/**
  * @brief  CAN Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_CANBusClk_En(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_CAN_BUSCLK_EN_Msk)

/**
  * @brief  CAN Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_CANBusClk_Dis(__SYSCTRL__)     CLEAR_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_CAN_BUSCLK_EN_Msk)

/**
  * @brief  DMA Bus CLK Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_DMABusClk_En(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_DMA_BUSCLK_EN_Msk)

/**
  * @brief  DMA Bus CLK Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_DMABusClk_Dis(__SYSCTRL__)     CLEAR_BIT((__SYSCTRL__)->AHBCCR, SYSCTRL_DMA_BUSCLK_EN_Msk)


/**
  * @brief  HRPWM Function Clk Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_HRPWMFunClk_En(__SYSCTRL__)    SET_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_HRPWM_FUNCLK_EN_Msk)

/**
  * @brief  HRPWM Function Clk Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_HRPWMFunClk_Dis(__SYSCTRL__)   CLEAR_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_HRPWM_FUNCLK_EN_Msk)

/**
  * @brief  ADC Function Clk Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ADCFunClk_En(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_ADC_FUNCLK_EN_Msk)

/**
  * @brief  ADC Function Clk Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ADCFunClk_Dis(__SYSCTRL__)     CLEAR_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_ADC_FUNCLK_EN_Msk)

/**
  * @brief  CAN Function Clk Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_CANFunClk_En(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_CAN_FUNCLK_EN_Msk)

/**
  * @brief  CAN Function Clk Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_CANFunClk_Dis(__SYSCTRL__)     CLEAR_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_CAN_FUNCLK_EN_Msk)

/**
  * @brief  ECU Function Clk Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ECUFunClk_En(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_ECU_FUNCLK_EN_Msk)

/**
  * @brief  ECU Function Clk Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ECUFunClk_Dis(__SYSCTRL__)     CLEAR_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_ECU_FUNCLK_EN_Msk)

/**
  * @brief  IIR4 Function Clk Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR4FunClk_En(__SYSCTRL__)     SET_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_IIR4_FUNCLK_EN_Msk)

/**
  * @brief  IIR4 Function Clk Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR4FunClk_Dis(__SYSCTRL__)    CLEAR_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_IIR4_FUNCLK_EN_Msk)

/**
  * @brief  IIR3 Function Clk Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR3FunClk_En(__SYSCTRL__)     SET_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_IIR3_FUNCLK_EN_Msk)

/**
  * @brief  IIR3 Function Clk Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR3FunClk_Dis(__SYSCTRL__)    CLEAR_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_IIR3_FUNCLK_EN_Msk)

/**
  * @brief  IIR2 Function Clk Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR2FunClk_En(__SYSCTRL__)     SET_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_IIR2_FUNCLK_EN_Msk)

/**
  * @brief  IIR2 Function Clk Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR2FunClk_Dis(__SYSCTRL__)    CLEAR_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_IIR2_FUNCLK_EN_Msk)

/**
  * @brief  IIR1 Function Clk Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR1FunClk_En(__SYSCTRL__)     SET_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_IIR1_FUNCLK_EN_Msk)

/**
  * @brief  IIR1 Function Clk Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR1FunClk_Dis(__SYSCTRL__)    CLEAR_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_IIR1_FUNCLK_EN_Msk)

/**
  * @brief  IIR0 Function Clk Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR0FunClk_En(__SYSCTRL__)     SET_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_IIR0_FUNCLK_EN_Msk)

/**
  * @brief  IIR0 Function Clk Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR0FunClk_Dis(__SYSCTRL__)    CLEAR_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_IIR0_FUNCLK_EN_Msk)

/**
  * @brief  USB Function Clk Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_USBFunClk_En(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_USB_FUNCLK_EN_Msk)

/**
  * @brief  USB Function Clk Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_USBFunClk_Dis(__SYSCTRL__)     CLEAR_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_USB_FUNCLK_EN_Msk)

/**
  * @brief  DFLASH Memory Clk Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_DFLASHMemClk_En(__SYSCTRL__)   SET_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_DFLASH_MEMCLK_EN_Msk)

/**
  * @brief  DFLASH Memory Clk Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_DFLASHMemClk_Dis(__SYSCTRL__)  CLEAR_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_DFLASH_MEMCLK_EN_Msk)

/**
  * @brief  EFLASH Memory Clk Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_EFLASHMemClk_En(__SYSCTRL__)   SET_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_EFLASH_MEMCLK_EN_Msk)

/**
  * @brief  EFLASH Memory Clk Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_EFLASHMemClk_Dis(__SYSCTRL__)  CLEAR_BIT((__SYSCTRL__)->FUNCCR, SYSCTRL_EFLASH_MEMCLK_EN_Msk)


/**
  * @brief  GPIOD Debounce Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIODDbcSoftRst_Assert(__SYSCTRL__)    CLEAR_BIT((__SYSCTRL__)->SYSRCR, SYSCTRL_GPIOD_DBC_SOFTRST_Msk)

/**
  * @brief  GPIOD Debounce Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIODDbcSoftRst_Release(__SYSCTRL__)   SET_BIT((__SYSCTRL__)->SYSRCR, SYSCTRL_GPIOD_DBC_SOFTRST_Msk)

/**
  * @brief  GPIOC Debounce Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIOCDbcSoftRst_Assert(__SYSCTRL__)    CLEAR_BIT((__SYSCTRL__)->SYSRCR, SYSCTRL_GPIOC_DBC_SOFTRST_Msk)

/**
  * @brief  GPIOC Debounce Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIOCDbcSoftRst_Release(__SYSCTRL__)   SET_BIT((__SYSCTRL__)->SYSRCR, SYSCTRL_GPIOC_DBC_SOFTRST_Msk)

/**
  * @brief  GPIOB Debounce Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIOBDbcSoftRst_Assert(__SYSCTRL__)    CLEAR_BIT((__SYSCTRL__)->SYSRCR, SYSCTRL_GPIOB_DBC_SOFTRST_Msk)

/**
  * @brief  GPIOB Debounce Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIOBDbcSoftRst_Release(__SYSCTRL__)   SET_BIT((__SYSCTRL__)->SYSRCR, SYSCTRL_GPIOB_DBC_SOFTRST_Msk)

/**
  * @brief  GPIOA Debounce Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIOADbcSoftRst_Assert(__SYSCTRL__)    CLEAR_BIT((__SYSCTRL__)->SYSRCR, SYSCTRL_GPIOA_DBC_SOFTRST_Msk)

/**
  * @brief  GPIOA Debounce Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIOADbcSoftRst_Release(__SYSCTRL__)   SET_BIT((__SYSCTRL__)->SYSRCR, SYSCTRL_GPIOA_DBC_SOFTRST_Msk)

/**
  * @brief  APB1 Bus Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_APB1BusSoftRst_Assert(__SYSCTRL__)     CLEAR_BIT((__SYSCTRL__)->SYSRCR, SYSCTRL_APB1BUS_SOFTRST_Msk)

/**
  * @brief  APB1 Bus Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_APB1BusSoftRst_Release(__SYSCTRL__)    SET_BIT((__SYSCTRL__)->SYSRCR, SYSCTRL_APB1BUS_SOFTRST_Msk)

/**
  * @brief  APB0 Bus Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_APB0BusSoftRst_Assert(__SYSCTRL__)     CLEAR_BIT((__SYSCTRL__)->SYSRCR, SYSCTRL_APB0BUS_SOFTRST_Msk)

/**
  * @brief  APB0 Bus Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_APB0BusSoftRst_Release(__SYSCTRL__)    SET_BIT((__SYSCTRL__)->SYSRCR, SYSCTRL_APB0BUS_SOFTRST_Msk)

/**
  * @brief  AHB Bus Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AHBBusSoftRst_Assert(__SYSCTRL__)      CLEAR_BIT((__SYSCTRL__)->SYSRCR, SYSCTRL_AHBBUS_SOFTRST_Msk)

/**
  * @brief  AHB Bus Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AHBBusSoftRst_Release(__SYSCTRL__)     SET_BIT((__SYSCTRL__)->SYSRCR, SYSCTRL_AHBBUS_SOFTRST_Msk)

/**
  * @brief  System Soft Reset all Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_SysSoftRstAll_Assert(__SYSCTRL__)      WRITE_REG((__SYSCTRL__)->SYSRCR, 0x0)

/**
  * @brief  System Soft Reset all Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_SysSoftRstAll_Release(__SYSCTRL__)     WRITE_REG((__SYSCTRL__)->SYSRCR, 0xffffffffUL)


/**
  * @brief  LSTIMER Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_LSTIMERSoftRst_Assert(__SYSCTRL__)     CLEAR_BIT((__SYSCTRL__)->APB0RCR, SYSCTRL_LSTIMER_SOFTRST_Msk)

/**
  * @brief  LSTIMER Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_LSTIMERSoftRst_Release(__SYSCTRL__)    SET_BIT((__SYSCTRL__)->APB0RCR, SYSCTRL_LSTIMER_SOFTRST_Msk)

/**
  * @brief  UART1 Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_UART1SoftRst_Assert(__SYSCTRL__)       CLEAR_BIT((__SYSCTRL__)->APB0RCR, SYSCTRL_UART1_SOFTRST_Msk)

/**
  * @brief  UART1 Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_UART1SoftRst_Release(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->APB0RCR, SYSCTRL_UART1_SOFTRST_Msk)

/**
  * @brief  UART0 Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_UART0SoftRst_Assert(__SYSCTRL__)       CLEAR_BIT((__SYSCTRL__)->APB0RCR, SYSCTRL_UART0_SOFTRST_Msk)

/**
  * @brief  UART0 Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_UART0SoftRst_Release(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->APB0RCR, SYSCTRL_UART0_SOFTRST_Msk)

/**
  * @brief  I2C1 Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_I2C1SoftRst_Assert(__SYSCTRL__)        CLEAR_BIT((__SYSCTRL__)->APB0RCR, SYSCTRL_I2C1_SOFTRST_Msk)

/**
  * @brief  I2C1 Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_I2C1SoftRst_Release(__SYSCTRL__)       SET_BIT((__SYSCTRL__)->APB0RCR, SYSCTRL_I2C1_SOFTRST_Msk)

/**
  * @brief  I2C0 Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_I2C0SoftRst_Assert(__SYSCTRL__)        CLEAR_BIT((__SYSCTRL__)->APB0RCR, SYSCTRL_I2C0_SOFTRST_Msk)

/**
  * @brief  I2C0 Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_I2C0SoftRst_Release(__SYSCTRL__)       SET_BIT((__SYSCTRL__)->APB0RCR, SYSCTRL_I2C0_SOFTRST_Msk)

/**
  * @brief  APB0 Soft Reset all Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_APB0SoftRstAll_Assert(__SYSCTRL__)     WRITE_REG((__SYSCTRL__)->APB0RCR, 0x0)

/**
  * @brief  APB0 Soft Reset all Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_APB0SoftRstAll_Release(__SYSCTRL__)    WRITE_REG((__SYSCTRL__)->APB0RCR, 0xffffffffUL)


/**
  * @brief  ECU Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ECUSoftRst_Assert(__SYSCTRL__)         CLEAR_BIT((__SYSCTRL__)->APB1RCR, SYSCTRL_ECU_SOFTRST_Msk)

/**
  * @brief  ECU Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ECUSoftRst_Release(__SYSCTRL__)        SET_BIT((__SYSCTRL__)->APB1RCR, SYSCTRL_ECU_SOFTRST_Msk)

/**
  * @brief  IIR4 Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR4SoftRst_Assert(__SYSCTRL__)        CLEAR_BIT((__SYSCTRL__)->APB1RCR, SYSCTRL_IIR4_SOFTRST_Msk)

/**
  * @brief  IIR4 Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR4SoftRst_Release(__SYSCTRL__)       SET_BIT((__SYSCTRL__)->APB1RCR, SYSCTRL_IIR4_SOFTRST_Msk)

/**
  * @brief  IIR3 Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR3SoftRst_Assert(__SYSCTRL__)        CLEAR_BIT((__SYSCTRL__)->APB1RCR, SYSCTRL_IIR3_SOFTRST_Msk)

/**
  * @brief  IIR3 Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR3SoftRst_Release(__SYSCTRL__)       SET_BIT((__SYSCTRL__)->APB1RCR, SYSCTRL_IIR3_SOFTRST_Msk)

/**
  * @brief  IIR2 Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR2SoftRst_Assert(__SYSCTRL__)        CLEAR_BIT((__SYSCTRL__)->APB1RCR, SYSCTRL_IIR2_SOFTRST_Msk)

/**
  * @brief  IIR2 Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR2SoftRst_Release(__SYSCTRL__)       SET_BIT((__SYSCTRL__)->APB1RCR, SYSCTRL_IIR2_SOFTRST_Msk)

/**
  * @brief  IIR1 Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR1SoftRst_Assert(__SYSCTRL__)        CLEAR_BIT((__SYSCTRL__)->APB1RCR, SYSCTRL_IIR1_SOFTRST_Msk)

/**
  * @brief  IIR1 Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR1SoftRst_Release(__SYSCTRL__)       SET_BIT((__SYSCTRL__)->APB1RCR, SYSCTRL_IIR1_SOFTRST_Msk)

/**
  * @brief  IIR0 Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR0SoftRst_Assert(__SYSCTRL__)        CLEAR_BIT((__SYSCTRL__)->APB1RCR, SYSCTRL_IIR0_SOFTRST_Msk)

/**
  * @brief  IIR0 Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IIR0SoftRst_Release(__SYSCTRL__)       SET_BIT((__SYSCTRL__)->APB1RCR, SYSCTRL_IIR0_SOFTRST_Msk)

/**
  * @brief  FPLL2 Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_FPLL2SoftRst_Assert(__SYSCTRL__)       CLEAR_BIT((__SYSCTRL__)->APB1RCR, SYSCTRL_FPLL2_SOFTRST_Msk)

/**
  * @brief  FPLL2 Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_FPLL2SoftRst_Release(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->APB1RCR, SYSCTRL_FPLL2_SOFTRST_Msk)

/**
  * @brief  FPLL1 Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_FPLL1SoftRst_Assert(__SYSCTRL__)       CLEAR_BIT((__SYSCTRL__)->APB1RCR, SYSCTRL_FPLL1_SOFTRST_Msk)

/**
  * @brief  FPLL1 Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_FPLL1SoftRst_Release(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->APB1RCR, SYSCTRL_FPLL1_SOFTRST_Msk)

/**
  * @brief  FPLL0 Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_FPLL0SoftRst_Assert(__SYSCTRL__)       CLEAR_BIT((__SYSCTRL__)->APB1RCR, SYSCTRL_FPLL0_SOFTRST_Msk)

/**
  * @brief  FPLL0 Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_FPLL0SoftRst_Release(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->APB1RCR, SYSCTRL_FPLL0_SOFTRST_Msk)

/**
  * @brief  DALI Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_DALISoftRst_Assert(__SYSCTRL__)        CLEAR_BIT((__SYSCTRL__)->APB1RCR, SYSCTRL_DALI_SOFTRST_Msk)

/**
  * @brief  DALI Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_DALISoftRst_Release(__SYSCTRL__)       SET_BIT((__SYSCTRL__)->APB1RCR, SYSCTRL_DALI_SOFTRST_Msk)

/**
  * @brief  APB1 Soft Reset all Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_APB1SoftRstAll_Assert(__SYSCTRL__)     WRITE_REG((__SYSCTRL__)->APB1RCR, 0x0)

/**
  * @brief  APB1 Soft Reset all Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_APB1SoftRstAll_Release(__SYSCTRL__)    WRITE_REG((__SYSCTRL__)->APB1RCR, 0xffffffffUL)


/**
  * @brief  DFLASH Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_DFLASHSoftRst_Assert(__SYSCTRL__)      CLEAR_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_DFLASH_SOFTRST_Msk)

/**
  * @brief  DFLASH Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_DFLASHSoftRst_Release(__SYSCTRL__)     SET_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_DFLASH_SOFTRST_Msk)

/**
  * @brief  HSTIMER Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_HSTIMERSoftRst_Assert(__SYSCTRL__)     CLEAR_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_HSTIMER_SOFTRST_Msk)

/**
  * @brief  HSTIMER Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_HSTIMERSoftRst_Release(__SYSCTRL__)    SET_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_HSTIMER_SOFTRST_Msk)

/**
  * @brief  GPIOD Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIODSoftRst_Assert(__SYSCTRL__)       CLEAR_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_GPIOD_SOFTRST_Msk)

/**
  * @brief  GPIOD Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIODSoftRst_Release(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_GPIOD_SOFTRST_Msk)

/**
  * @brief  GPIOC Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIOCSoftRst_Assert(__SYSCTRL__)       CLEAR_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_GPIOC_SOFTRST_Msk)

/**
  * @brief  GPIOC Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIOCSoftRst_Release(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_GPIOC_SOFTRST_Msk)

/**
  * @brief  GPIOB Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIOBSoftRst_Assert(__SYSCTRL__)       CLEAR_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_GPIOB_SOFTRST_Msk)

/**
  * @brief  GPIOB Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIOBSoftRst_Release(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_GPIOB_SOFTRST_Msk)

/**
  * @brief  GPIOA Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIOASoftRst_Assert(__SYSCTRL__)       CLEAR_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_GPIOA_SOFTRST_Msk)

/**
  * @brief  GPIOA Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIOASoftRst_Release(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_GPIOA_SOFTRST_Msk)

/**
  * @brief  USB Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_USBSoftRst_Assert(__SYSCTRL__)         CLEAR_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_USB_SOFTRST_Msk)

/**
  * @brief  USB Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_USBSoftRst_Release(__SYSCTRL__)        SET_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_USB_SOFTRST_Msk)

/**
  * @brief  HRPWM Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_HRPWMSoftRst_Assert(__SYSCTRL__)       CLEAR_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_HRPWM_SOFTRST_Msk)

/**
  * @brief  HRPWM Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_HRPWMSoftRst_Release(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_HRPWM_SOFTRST_Msk)

/**
  * @brief  DAC Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_DACSoftRst_Assert(__SYSCTRL__)         CLEAR_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_DAC_SOFTRST_Msk)

/**
  * @brief  DAC Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_DACSoftRst_Release(__SYSCTRL__)        SET_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_DAC_SOFTRST_Msk)

/**
  * @brief  ADC Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ADCSoftRst_Assert(__SYSCTRL__)         CLEAR_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_ADC_SOFTRST_Msk)

/**
  * @brief  ADC Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ADCSoftRst_Release(__SYSCTRL__)        SET_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_ADC_SOFTRST_Msk)

/**
  * @brief  CMP Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_CMPSoftRst_Assert(__SYSCTRL__)         CLEAR_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_CMP_SOFTRST_Msk)

/**
  * @brief  CMP Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_CMPSoftRst_Release(__SYSCTRL__)        SET_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_CMP_SOFTRST_Msk)

/**
  * @brief  EFLASH Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_EFLASHSoftRst_Assert(__SYSCTRL__)      CLEAR_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_EFLASH_SOFTRST_Msk)

/**
  * @brief  EFLASH Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_EFLASHSoftRst_Release(__SYSCTRL__)     SET_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_EFLASH_SOFTRST_Msk)

/**
  * @brief  CAN Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_CANSoftRst_Assert(__SYSCTRL__)         CLEAR_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_CAN_SOFTRST_Msk)

/**
  * @brief  CAN Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_CANSoftRst_Release(__SYSCTRL__)        SET_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_CAN_SOFTRST_Msk)

/**
  * @brief  DMA Soft Reset Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_DMASoftRst_Assert(__SYSCTRL__)         CLEAR_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_DMA_SOFTRST_Msk)

/**
  * @brief  DMA Soft Reset Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_DMASoftRst_Release(__SYSCTRL__)        SET_BIT((__SYSCTRL__)->AHBRCR, SYSCTRL_DMA_SOFTRST_Msk)

/**
  * @brief  AHB Soft Reset all Assert
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AHBSoftRstAll_Assert(__SYSCTRL__)      WRITE_REG((__SYSCTRL__)->AHBRCR, 0x0)

/**
  * @brief  AHB Soft Reset all Release
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AHBSoftRstAll_Release(__SYSCTRL__)     WRITE_REG((__SYSCTRL__)->AHBRCR, 0xffffffffUL)


/**
  * @brief  RC8M Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_RC8M_En(__SYSCTRL__)               SET_BIT((__SYSCTRL__)->XOSCCR, SYSCTRL_RC8M_EN_Msk)

/**
  * @brief  RC8M Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_RC8M_Dis(__SYSCTRL__)              CLEAR_BIT((__SYSCTRL__)->XOSCCR, SYSCTRL_RC8M_EN_Msk)

/**
  * @brief  XOSC Loss IRQ Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_XOSCLossIRQ_En(__SYSCTRL__)        SET_BIT((__SYSCTRL__)->XOSCCR, SYSCTRL_XOSCLOSS_IRQEN_Msk)

/**
  * @brief  XOSC Loss IRQ Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_XOSCLossIRQ_Dis(__SYSCTRL__)       CLEAR_BIT((__SYSCTRL__)->XOSCCR, SYSCTRL_XOSCLOSS_IRQEN_Msk)

/**
  * @brief  XOSC HY Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_XOSC_HY_EN(__SYSCTRL__)            SET_BIT((__SYSCTRL__)->XOSCCR, SYSCTRL_XOSC_HYEN_Msk)

/**
  * @brief  XOSC HY Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_XOSC_HY_Dis(__SYSCTRL__)           CLEAR_BIT((__SYSCTRL__)->XOSCCR, SYSCTRL_XOSC_HYEN_Msk)

/**
  * @brief  XOSC DR Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  cur Current
  * @return None
  */
#define __LL_SYSCTRL_XOSC_DR_Set(__SYSCTRL__, cur)      MODIFY_REG((__SYSCTRL__)->XOSCCR, SYSCTRL_XOSC_DR_Msk, cur)

/**
  * @brief  XOSC CTO Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  cap capacitance Register Value
  * @return None
  */
#define __LL_SYSCTRL_XOSC_CTO_Set(__SYSCTRL__, cap)     \
        MODIFY_REG((__SYSCTRL__)->XOSCCR, SYSCTRL_XOSC_CTO_Msk, ((cap & 0xfUL) << SYSCTRL_XOSC_CTO_Pos))

/**
  * @brief  XOSC CTI Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  cap capacitance Register Value
  * @return None
  */
#define __LL_SYSCTRL_XOSC_CTI_Set(__SYSCTRL__, cap)     \
        MODIFY_REG((__SYSCTRL__)->XOSCCR, SYSCTRL_XOSC_CTI_Msk, ((cap & 0xfUL) << SYSCTRL_XOSC_CTI_Pos))

/**
  * @brief  XOSC CS Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  cap capacitance
  * @return None
  */
#define __LL_SYSCTRL_XOSC_CS_Set(__SYSCTRL__, cap)      MODIFY_REG((__SYSCTRL__)->XOSCCR, SYSCTRL_XOSC_CS_Msk, cap)

/**
  * @brief  XOSC Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_XOSC_En(__SYSCTRL__)               SET_BIT((__SYSCTRL__)->XOSCCR, SYSCTRL_XOSC_EN_Msk)

/**
  * @brief  XOSC Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_XOSC_Dis(__SYSCTRL__)              CLEAR_BIT((__SYSCTRL__)->XOSCCR, SYSCTRL_XOSC_EN_Msk)


/**
  * @brief  Judge XOSC Loss or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 XOSC hasn't loss
  * @retval 1 XOSC has loss
  */
#define __LL_SYSCTRL_IsXOSCLossPending(__SYSCTRL__)     \
        (READ_BIT((__SYSCTRL__)->XASWCR, SYSCTRL_XOSC_LOSS_PENDING_Msk) >> SYSCTRL_XOSC_LOSS_PENDING_Pos)

/**
  * @brief  Clear XOSC Loss Pending
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_XOSCLossPending_Clr(__SYSCTRL__)   SET_BIT((__SYSCTRL__)->XASWCR, SYSCTRL_XOSC_LOSS_PENDING_Msk)

/**
  * @brief  Enable SYSCLK Auto Switch to RC8M When XOSC Fault
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_XOSC_SysclkSw_En(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->XASWCR, SYSCTRL_XOSC_SYSCLK_SWEN_Msk)

/**
  * @brief  Disable SYSCLK Auto Switch to RC8M When XOSC Fault
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_XOSC_SysclkSw_Dis(__SYSCTRL__)     CLEAR_BIT((__SYSCTRL__)->XASWCR, SYSCTRL_XOSC_SYSCLK_SWEN_Msk)

/**
  * @brief  Enable PLL Ref Clk Auto Switch to RC8M When XOSC Fault
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_XOSC_PLLRefClkSw_En(__SYSCTRL__)   SET_BIT((__SYSCTRL__)->XASWCR, SYSCTRL_XOSC_REFCLK_SWEN_Msk)

/**
  * @brief  Disable PLL Ref Clk Auto Switch to RC8M When XOSC Fault
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_XOSC_PLLRefClkSw_Dis(__SYSCTRL__)  CLEAR_BIT((__SYSCTRL__)->XASWCR, SYSCTRL_XOSC_REFCLK_SWEN_Msk)

/**
  * @brief  XOSC MNT Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_XOSC_MNT_En(__SYSCTRL__)           SET_BIT((__SYSCTRL__)->XASWCR, SYSCTRL_XOSC_MNTEN_Msk)

/**
  * @brief  XOSC MNT Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_XOSC_MNT_Dis(__SYSCTRL__)          CLEAR_BIT((__SYSCTRL__)->XASWCR, SYSCTRL_XOSC_MNTEN_Msk)

/**
  * @brief  XOSC AutoSwitch Window Width Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  width Auto Switch Window Width Register Value
  * @return None
  */
#define __LL_SYSCTRL_XOSC_Width_Set(__SYSCTRL__, width)     \
        MODIFY_REG((__SYSCTRL__)->XASWCR, SYSCTRL_XOSC_WIDTH_Msk, ((width & 0xfUL) << SYSCTRL_XOSC_WIDTH_Pos))

/**
  * @brief  XOSC AutoSwitch Function High Limit Value Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  limit High Limit Register Value
  * @return None
  */
#define __LL_SYSCTRL_XOSC_HighLimit_Set(__SYSCTRL__, limit) \
        MODIFY_REG((__SYSCTRL__)->XASWCR, SYSCTRL_XOSC_HIGH_LIMIT_Msk, ((limit & 0x3ffUL) << SYSCTRL_XOSC_HIGH_LIMIT_Pos))

/**
  * @brief  XOSC AutoSwitch Function Low Limit Value Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  limit Low Limit Register Value
  * @return None
  */
#define __LL_SYSCTRL_XOSC_LowLimit_Set(__SYSCTRL__, limit)  \
        MODIFY_REG((__SYSCTRL__)->XASWCR, SYSCTRL_XOSC_LOW_LIMIT_Msk, ((limit & 0x3ffUL) << SYSCTRL_XOSC_LOW_LIMIT_Pos))


/**
  * @brief  ADC Buffer Source Select
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  src ADC Buffer Source
  * @return None
  */
#define __LL_SYSCTRL_ADCBufSrc_Sel(__SYSCTRL__, src)        MODIFY_REG((__SYSCTRL__)->BUFCR, SYSCTRL_ADCBUF_SRCSEL_Msk, src)

/**
  * @brief  ADC Buffer Bypass Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ADCBufBypass_En(__SYSCTRL__)           SET_BIT((__SYSCTRL__)->BUFCR, SYSCTRL_ADCBUF_BYPASS_Msk)

/**
  * @brief  ADC Buffer Bypass Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ADCBufBypass_Dis(__SYSCTRL__)          CLEAR_BIT((__SYSCTRL__)->BUFCR, SYSCTRL_ADCBUF_BYPASS_Msk)

/**
  * @brief  ADC Buffer Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ADCBuf_En(__SYSCTRL__)                 SET_BIT((__SYSCTRL__)->BUFCR, SYSCTRL_ADCBUF_EN_Msk)

/**
  * @brief  ADC Buffer Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ADCBuf_Dis(__SYSCTRL__)                CLEAR_BIT((__SYSCTRL__)->BUFCR, SYSCTRL_ADCBUF_EN_Msk)

/**
  * @brief  TOUT Source Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  src TOUT Source
  * @return None
  */
#define __LL_SYSCTRL_TOUTSrc_Set(__SYSCTRL__, src)          MODIFY_REG((__SYSCTRL__)->BUFCR, SYSCTRL_TOUT_SRC_Msk, src)


/**
  * @brief  ADC Fan Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ADC_Fan_Dis(__SYSCTRL__)           \
        MODIFY_REG((__SYSCTRL__)->SYSCCR, SYSCTRL_ADCCTRL_FANOUT_EN_Msk, (0x0 << SYSCTRL_ADCCTRL_FANOUT_EN_Pos))

/**
  * @brief  ADC Fan Out Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ADC_FanOut_En(__SYSCTRL__)         \
        MODIFY_REG((__SYSCTRL__)->SYSCCR, SYSCTRL_ADCCTRL_FANOUT_EN_Msk, (0x1 << SYSCTRL_ADCCTRL_FANOUT_EN_Pos))

/**
  * @brief  ADC Fan In Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ADC_FanIn_En(__SYSCTRL__)          \
        MODIFY_REG((__SYSCTRL__)->SYSCCR, SYSCTRL_ADCCTRL_FANOUT_EN_Msk, (0x2 << SYSCTRL_ADCCTRL_FANOUT_EN_Pos))

/**
  * @brief  ADC Data Fan Out Source Select ADC0
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ADCDataFanOutSrc_ADC0(__SYSCTRL__) CLEAR_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_ADCDATA_FANOUT_SRC_Msk)

/**
  * @brief  ADC Data Fan Out Source Select ADC1
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ADCDataFanOutSrc_ADC1(__SYSCTRL__) SET_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_ADCDATA_FANOUT_SRC_Msk)

/**
  * @brief  ADC Data Fan Out Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ADCDataFanOut_En(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_ADCDATA_FANOUT_EN_Msk)

/**
  * @brief  ADC Data Fan Out Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ADCDataFanOut_Dis(__SYSCTRL__)     CLEAR_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_ADCDATA_FANOUT_EN_Msk)

/**
  * @brief  I2C1 SMBUS Output Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_I2C1_SMBUSOutput_En(__SYSCTRL__)   SET_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_I2C1_SMBUS_OE_Msk)

/**
  * @brief  I2C1 SMBUS Output Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_I2C1_SMBUSOutput_Dis(__SYSCTRL__)  CLEAR_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_I2C1_SMBUS_OE_Msk)

/**
  * @brief  I2C0 SMBUS Output Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_I2C0_SMBUSOutput_En(__SYSCTRL__)   SET_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_I2C0_SMBUS_OE_Msk)

/**
  * @brief  I2C0 SMBUS Output Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_I2C0_SMBUSOutput_Dis(__SYSCTRL__)  CLEAR_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_I2C0_SMBUS_OE_Msk)

/**
  * @brief  JTAG Bug Fix Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_JTAG_BugFix_En(__SYSCTRL__)        SET_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_JTAG_BUGFIX_EN_Msk)

/**
  * @brief  JTAG Bug Fix Diaable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_JTAG_BugFix_Dis(__SYSCTRL__)       CLEAR_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_JTAG_BUGFIX_EN_Msk)

/**
  * @brief  CAN FD Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_CAN_FD_En(__SYSCTRL__)             SET_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_CANFD_EN_Msk)

/**
  * @brief  CAN FD Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_CAN_FD_Dis(__SYSCTRL__)            CLEAR_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_CANFD_EN_Msk)

/**
  * @brief  CPU Lockup Reset Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_CPU_LockupRst_En(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_CPU_LOCKUPRST_EN_Msk)

/**
  * @brief  CPU Lockup Reset Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_CPU_LockupRst_Dis(__SYSCTRL__)     CLEAR_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_CPU_LOCKUPRST_EN_Msk)

/**
  * @brief  WWDG Debug Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_WWDG_Debug_En(__SYSCTRL__)         SET_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_WWDG_DEBUG_EN_Msk)

/**
  * @brief  WWDG Debug Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_WWDG_Debug_Dis(__SYSCTRL__)        CLEAR_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_WWDG_DEBUG_EN_Msk)

/**
  * @brief  WWDG Timeout Reset Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_WWDG_TimeoutRst_En(__SYSCTRL__)    SET_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_WWDG_TIMEOUTRST_EN_Msk)

/**
  * @brief  WWDG Timeout Reset Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_WWDG_TimeoutRst_Dis(__SYSCTRL__)   CLEAR_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_WWDG_TIMEOUTRST_EN_Msk)

/**
  * @brief  IWDG Debug Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IWDG_Debug_En(__SYSCTRL__)         SET_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_IWDG_DEBUG_EN_Msk)

/**
  * @brief  IWDG Debug Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IWDG_Debug_Dis(__SYSCTRL__)        CLEAR_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_IWDG_DEBUG_EN_Msk)

/**
  * @brief  IWDG Timeout Reset Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IWDG_TimeoutRst_En(__SYSCTRL__)    SET_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_IWDG_TIMEOUTRST_EN_Msk)

/**
  * @brief  IWDG Timeout Reset Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IWDG_TimeoutRst_Dis(__SYSCTRL__)   CLEAR_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_IWDG_TIMEOUTRST_EN_Msk)

/**
  * @brief  HSTMR Debug Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_HSTMR_Debug_En(__SYSCTRL__)        SET_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_HSTMR_DEBUG_EN_Msk)

/**
  * @brief  HSTMR Debug Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_HSTMR_Debug_Dis(__SYSCTRL__)       CLEAR_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_HSTMR_DEBUG_EN_Msk)

/**
  * @brief  LSTMR Debug Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_LSTMR_Debug_En(__SYSCTRL__)        SET_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_LSTMR_DEBUG_EN_Msk)

/**
  * @brief  LSTMR Debug Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_LSTMR_Debug_Dis(__SYSCTRL__)       CLEAR_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_LSTMR_DEBUG_EN_Msk)

/**
  * @brief  GPIO Input NMI Interrupt Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIO_InputNMI_En(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_GPIO_NMIEN_Msk)

/**
  * @brief  GPIO Input NMI Interrupt Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_GPIO_InputNMI_Dis(__SYSCTRL__)     CLEAR_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_GPIO_NMIEN_Msk)

/**
  * @brief  CLK Test Source Select
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  src CLK Test Source
  * @return None
  */
#define __LL_SYSCTRL_CLK_TestSrc_Sel(__SYSCTRL__, src)   MODIFY_REG((__SYSCTRL__)->SYSCCR, SYSCTRL_CLK_TEST_SRC_Msk, src)

/**
  * @brief  CLK Fan Out Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_CLK_FanOut_En(__SYSCTRL__)         SET_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_CLK_FANOUT_EN_Msk)

/**
  * @brief  CLK Fan Out Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_CLK_FanOut_Dis(__SYSCTRL__)        CLEAR_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_CLK_FANOUT_EN_Msk)

/**
  * @brief  PMU Debug1 Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PMU_Debug1_En(__SYSCTRL__)         SET_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_PMU_DEBUG1_EN_Msk)

/**
  * @brief  PMU Debug1 Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PMU_Debug1_Dis(__SYSCTRL__)        CLEAR_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_PMU_DEBUG1_EN_Msk)

/**
  * @brief  PMU Debug0 Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PMU_Debug0_En(__SYSCTRL__)         SET_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_PMU_DEBUG0_EN_Msk)

/**
  * @brief  PMU Debug0 Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PMU_Debug0_Dis(__SYSCTRL__)        CLEAR_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_PMU_DEBUG0_EN_Msk)

/**
  * @brief  TEST CLK In Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TESTClkIn_En(__SYSCTRL__)          SET_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_TEST_CLKIN_EN_Msk)

/**
  * @brief  TEST CLK In Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TESTClkIn_Dis(__SYSCTRL__)         CLEAR_BIT((__SYSCTRL__)->SYSCCR, SYSCTRL_TEST_CLKIN_EN_Msk)


/**
  * @brief  Judge SysReq Reset or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 Isn't SysReq Reset
  * @retval 1 Is SysReq Reset
  */
#define __LL_SYSCTRL_IsSysReqRst(__SYSCTRL__)           \
        (READ_BIT((__SYSCTRL__)->SRSTSR, SYSCTRL_SYSREQ_RST_ST_Msk) >> SYSCTRL_SYSREQ_RST_ST_Pos)

/**
  * @brief  Clear SysReq Reset Pending
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_SysReqRst_Clr(__SYSCTRL__)         SET_BIT((__SYSCTRL__)->SRSTSR, SYSCTRL_SYSREQ_RST_ST_Msk)

/**
  * @brief  Judge MCLR Reset or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 Isn't MCLR Reset
  * @retval 1 Is MCLR Reset
  */
#define __LL_SYSCTRL_IsMCLRRst(__SYSCTRL__)             \
        (READ_BIT((__SYSCTRL__)->SRSTSR, SYSCTRL_MCLR_RST_ST_Msk) >> SYSCTRL_MCLR_RST_ST_Pos)

/**
  * @brief  Clear MCLR Reset Pending
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_MCLRRst_Clr(__SYSCTRL__)           SET_BIT((__SYSCTRL__)->SRSTSR, SYSCTRL_MCLR_RST_ST_Msk)

/**
  * @brief  Judge LVD Reset or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 Isn't LVD Reset
  * @retval 1 Is LVD Reset
  */
#define __LL_SYSCTRL_IsLVDRst(__SYSCTRL__)              \
        (READ_BIT((__SYSCTRL__)->SRSTSR, SYSCTRL_LVD_RST_ST_Msk) >> SYSCTRL_LVD_RST_ST_Pos)

/**
  * @brief  Clear LVD Reset Pending
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_LVDRst_Clr(__SYSCTRL__)            SET_BIT((__SYSCTRL__)->SRSTSR, SYSCTRL_LVD_RST_ST_Msk)

/**
  * @brief  Judge WWDG Reset or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 Isn't WWDG Reset
  * @retval 1 Is WWDG Reset
  */
#define __LL_SYSCTRL_IsWWDGRst(__SYSCTRL__)             \
        (READ_BIT((__SYSCTRL__)->SRSTSR, SYSCTRL_WWDG_RST_ST_Msk) >> SYSCTRL_WWDG_RST_ST_Pos)

/**
  * @brief  Clear WWDG Reset Pending
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_WWDGRst_Clr(__SYSCTRL__)           SET_BIT((__SYSCTRL__)->SRSTSR, SYSCTRL_WWDG_RST_ST_Msk)

/**
  * @brief  Judge IWDG Reset or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 Isn't IWDG Reset
  * @retval 1 Is IWDG Reset
  */
#define __LL_SYSCTRL_IsIWDGRst(__SYSCTRL__)             \
        (READ_BIT((__SYSCTRL__)->SRSTSR, SYSCTRL_IWDG_RST_ST_Msk) >> SYSCTRL_IWDG_RST_ST_Pos)

/**
  * @brief  Clear IWDG Reset Pending
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IWDGRst_Clr(__SYSCTRL__)           SET_BIT((__SYSCTRL__)->SRSTSR, SYSCTRL_IWDG_RST_ST_Msk)


/**
  * @brief  SYSCTRL Control Register Unlock
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_CTRLReg_Unlock(__SYSCTRL__)        WRITE_REG((__SYSCTRL__)->KEY, 0x3fac87e4)

/**
  * @brief  SYSCTRL FLS Register Unlock
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_FLSReg_Unlock(__SYSCTRL__)         WRITE_REG((__SYSCTRL__)->KEY, 0x1f2e3c4a)

/**
  * @brief  SYSCTRL Reg Lock
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_Reg_Lock(__SYSCTRL__)              WRITE_REG((__SYSCTRL__)->KEY, 0x00)

/**
  * @brief  Judge SYSCTRL CTRL Register is unlock or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 SYSCTRL CTRL Register is lock
  * @retval 1 SYSCTRL CTRL Register is unlock
  */
#define __LL_SYSCTRL_IsCTRLRegUnlock(__SYSCTRL__)       (READ_REG((__SYSCTRL__)->KEY) == 0x3fac87e4)

/**
  * @brief  Judge SYSCTRL FLS Register is unlock or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 SYSCTRL FLS Register is lock
  * @retval 1 SYSCTRL FLS Register is unlock
  */
#define __LL_SYSCTRL_IsFLSRegUnlock(__SYSCTRL__)        (READ_REG((__SYSCTRL__)->KEY) == 0x1f2e3c4a)


/**
  * @brief  PMU In Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  val Register Value
  * @return None
  */
#define __LL_SYSCTRL_PMU_In_Set(__SYSCTRL__, val)       \
        MODIFY_REG((__SYSCTRL__)->PMUCR, SYSCTRL_PMU_IN_Msk, ((val & 0x3fUL) << SYSCTRL_PMU_IN_Pos))

/**
  * @brief  CUR Resistance Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  res Resistance Register Value
  * @return None
  */
#define __LL_SYSCTRL_CUR_RES_Set(__SYSCTRL__, res)      \
        MODIFY_REG((__SYSCTRL__)->PMUCR, SYSCTRL_CUR_RES_Msk, ((res & 0x3fUL) << SYSCTRL_CUR_RES_Pos))

/**
  * @brief  CUR CAL Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  val Register Value
  * @return None
  */
#define __LL_SYSCTRL_CUR_CAL_Set(__SYSCTRL__, val)      \
        MODIFY_REG((__SYSCTRL__)->PMUCR, SYSCTRL_CUR_CAL_Msk, ((val & 0x3UL) << SYSCTRL_CUR_CAL_Pos))

/**
  * @brief  AVDD DRD Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AVDD_DRD_En(__SYSCTRL__)           SET_BIT((__SYSCTRL__)->PMUCR, SYSCTRL_AVDD_DRD_Msk)

/**
  * @brief  AVDD DRD Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AVDD_DRD_Dis(__SYSCTRL__)          CLEAR_BIT((__SYSCTRL__)->PMUCR, SYSCTRL_AVDD_DRD_Msk)

/**
  * @brief  AVDD Voltage Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  vol AVDD Voltage
  * @return None
  */
#define __LL_SYSCTRL_AVDD_VOL_Sel(__SYSCTRL__, vol)     MODIFY_REG((__SYSCTRL__)->PMUCR, SYSCTRL_AVDD_SET_Msk, vol)

/**
  * @brief  VDD Voltage Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  vol VDD Voltage
  * @return None
  */
#define __LL_SYSCTRL_VDD_VOL_Sel(__SYSCTRL__, vol)      MODIFY_REG((__SYSCTRL__)->PMUCR, SYSCTRL_VDD_SET_Msk, vol)

/**
  * @brief  CUR Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_CUR_En(__SYSCTRL__)                SET_BIT((__SYSCTRL__)->PMUCR, SYSCTRL_CUR_ENABLE_Msk)

/**
  * @brief  CUR Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_CUR_Dis(__SYSCTRL__)               CLEAR_BIT((__SYSCTRL__)->PMUCR, SYSCTRL_CUR_ENABLE_Msk)

/**
  * @brief  AVDDLDO Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AVDDLDO_En(__SYSCTRL__)            SET_BIT((__SYSCTRL__)->PMUCR, SYSCTRL_AVDDLDO_ENABLE_Msk)

/**
  * @brief  AVDDLDO Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AVDDLDO_Dis(__SYSCTRL__)           CLEAR_BIT((__SYSCTRL__)->PMUCR, SYSCTRL_AVDDLDO_ENABLE_Msk)

/**
  * @brief  Temperature Sensor Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TempSensor_En(__SYSCTRL__)         SET_BIT((__SYSCTRL__)->PMUCR, SYSCTRL_TEMPSENSOR_ENABLE_Msk)

/**
  * @brief  Temperature Sensor Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TempSensor_Dis(__SYSCTRL__)        CLEAR_BIT((__SYSCTRL__)->PMUCR, SYSCTRL_TEMPSENSOR_ENABLE_Msk)

/**
  * @brief  Band Gap Voltage Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  vol Voltage Register Value
  * @return None
  */
#define __LL_SYSCTRL_BandGapVol_Set(__SYSCTRL__, vol)   \
        MODIFY_REG((__SYSCTRL__)->PMUCR, SYSCTRL_BGR_VOL_Msk, ((vol & 0x1fUL) << SYSCTRL_BGR_VOL_Pos))

/**
  * @brief  BGR DRD Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_BGR_DRD_En(__SYSCTRL__)            SET_BIT((__SYSCTRL__)->PMUCR, SYSCTRL_BGR_DRD_Msk)

/**
  * @brief  BGR DRD Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_BGR_DRD_Dis(__SYSCTRL__)           CLEAR_BIT((__SYSCTRL__)->PMUCR, SYSCTRL_BGR_DRD_Msk)

/**
  * @brief  BGR Filter Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_BGR_Filter_En(__SYSCTRL__)         SET_BIT((__SYSCTRL__)->PMUCR, SYSCTRL_BGR_FILTER_Msk)

/**
  * @brief  BGR Filter Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_BGR_Filter_Dis(__SYSCTRL__)        \
        __LL_SYSCTRL_CtrlREG_OPT(CLEAR_BIT((__SYSCTRL__)->PMUCR, SYSCTRL_BGR_FILTER_Msk))


/**
  * @brief  SYSCTRL CTRL Register Operation
  * @param  expression SYSCTRL CTRL Register Read/Write Operation
  * @note   Only Write Operation need Unlock before Operation
  * @return None
  */
#define __LL_SYSCTRL_CtrlREG_OPT(expression)        \
        do {                                        \
            __LL_SYSCTRL_CTRLReg_Unlock(SYSCTRL);   \
            expression;                             \
            __LL_SYSCTRL_Reg_Lock(SYSCTRL);         \
        } while(0)

/**
  * @brief  SYSCTRL FLS Register Operation
  * @param  expression SYSCTRL FLS Register Read/Write Operation
  * @note   Only Write Operation need Unlock before Operation
  * @return None
  */
#define __LL_SYSCTRL_FlsREG_OPT(expression)         \
        do {                                        \
            __LL_SYSCTRL_FLSReg_Unlock(SYSCTRL);    \
            expression;                             \
            __LL_SYSCTRL_Reg_Lock(SYSCTRL);         \
        } while(0)

/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup SYSCTRL_LL_Exported_Types SYSCTRL LL Exported Types
  * @brief    SYSCTRL LL Exported Types
  * @{
  */

/**
  * @brief SYSCTRL CLK Div Definition
  */
typedef enum {
    SYSCTRL_CLK_DIV_IVD = 0,/*!< SYSCTRL CLK DIV IND */
    SYSCTRL_CLK_DIV_1,      /*!< SYSCTRL CLK DIV 1   */
    SYSCTRL_CLK_DIV_2,      /*!< SYSCTRL CLK DIV 2   */
    SYSCTRL_CLK_DIV_3,      /*!< SYSCTRL CLK DIV 3   */
    SYSCTRL_CLK_DIV_4,      /*!< SYSCTRL CLK DIV 4   */
    SYSCTRL_CLK_DIV_5,      /*!< SYSCTRL CLK DIV 5   */
    SYSCTRL_CLK_DIV_6,      /*!< SYSCTRL CLK DIV 6   */
    SYSCTRL_CLK_DIV_7,      /*!< SYSCTRL CLK DIV 7   */
    SYSCTRL_CLK_DIV_8,      /*!< SYSCTRL CLK DIV 8   */
    SYSCTRL_CLK_DIV_9,      /*!< SYSCTRL CLK DIV 9   */
    SYSCTRL_CLK_DIV_10,     /*!< SYSCTRL CLK DIV 10  */
    SYSCTRL_CLK_DIV_11,     /*!< SYSCTRL CLK DIV 11  */
    SYSCTRL_CLK_DIV_12,     /*!< SYSCTRL CLK DIV 12  */
    SYSCTRL_CLK_DIV_13,     /*!< SYSCTRL CLK DIV 13  */
    SYSCTRL_CLK_DIV_14,     /*!< SYSCTRL CLK DIV 14  */
    SYSCTRL_CLK_DIV_15,     /*!< SYSCTRL CLK DIV 15  */
    SYSCTRL_CLK_DIV_16,     /*!< SYSCTRL CLK DIV 16  */
    SYSCTRL_CLK_DIV_17,     /*!< SYSCTRL CLK DIV 17  */
    SYSCTRL_CLK_DIV_18,     /*!< SYSCTRL CLK DIV 18  */
    SYSCTRL_CLK_DIV_19,     /*!< SYSCTRL CLK DIV 19  */
    SYSCTRL_CLK_DIV_20,     /*!< SYSCTRL CLK DIV 20  */
    SYSCTRL_CLK_DIV_21,     /*!< SYSCTRL CLK DIV 21  */
    SYSCTRL_CLK_DIV_22,     /*!< SYSCTRL CLK DIV 22  */
    SYSCTRL_CLK_DIV_23,     /*!< SYSCTRL CLK DIV 23  */
    SYSCTRL_CLK_DIV_24,     /*!< SYSCTRL CLK DIV 24  */
    SYSCTRL_CLK_DIV_25,     /*!< SYSCTRL CLK DIV 25  */
    SYSCTRL_CLK_DIV_26,     /*!< SYSCTRL CLK DIV 26  */
    SYSCTRL_CLK_DIV_27,     /*!< SYSCTRL CLK DIV 27  */
    SYSCTRL_CLK_DIV_28,     /*!< SYSCTRL CLK DIV 28  */
    SYSCTRL_CLK_DIV_29,     /*!< SYSCTRL CLK DIV 29  */
    SYSCTRL_CLK_DIV_30,     /*!< SYSCTRL CLK DIV 30  */
    SYSCTRL_CLK_DIV_31,     /*!< SYSCTRL CLK DIV 31  */
    SYSCTRL_CLK_DIV_32,     /*!< SYSCTRL CLK DIV 32  */
    SYSCTRL_CLK_DIV_33,     /*!< SYSCTRL CLK DIV 33  */
    SYSCTRL_CLK_DIV_34,     /*!< SYSCTRL CLK DIV 34  */
    SYSCTRL_CLK_DIV_35,     /*!< SYSCTRL CLK DIV 35  */
    SYSCTRL_CLK_DIV_36,     /*!< SYSCTRL CLK DIV 36  */
    SYSCTRL_CLK_DIV_37,     /*!< SYSCTRL CLK DIV 37  */
    SYSCTRL_CLK_DIV_38,     /*!< SYSCTRL CLK DIV 38  */
    SYSCTRL_CLK_DIV_39,     /*!< SYSCTRL CLK DIV 39  */
    SYSCTRL_CLK_DIV_40,     /*!< SYSCTRL CLK DIV 40  */
    SYSCTRL_CLK_DIV_41,     /*!< SYSCTRL CLK DIV 41  */
    SYSCTRL_CLK_DIV_42,     /*!< SYSCTRL CLK DIV 42  */
    SYSCTRL_CLK_DIV_43,     /*!< SYSCTRL CLK DIV 43  */
    SYSCTRL_CLK_DIV_44,     /*!< SYSCTRL CLK DIV 44  */
    SYSCTRL_CLK_DIV_45,     /*!< SYSCTRL CLK DIV 45  */
    SYSCTRL_CLK_DIV_46,     /*!< SYSCTRL CLK DIV 46  */
    SYSCTRL_CLK_DIV_47,     /*!< SYSCTRL CLK DIV 47  */
    SYSCTRL_CLK_DIV_48,     /*!< SYSCTRL CLK DIV 48  */
    SYSCTRL_CLK_DIV_49,     /*!< SYSCTRL CLK DIV 49  */
    SYSCTRL_CLK_DIV_50,     /*!< SYSCTRL CLK DIV 50  */
    SYSCTRL_CLK_DIV_51,     /*!< SYSCTRL CLK DIV 51  */
    SYSCTRL_CLK_DIV_52,     /*!< SYSCTRL CLK DIV 52  */
    SYSCTRL_CLK_DIV_53,     /*!< SYSCTRL CLK DIV 53  */
    SYSCTRL_CLK_DIV_54,     /*!< SYSCTRL CLK DIV 54  */
    SYSCTRL_CLK_DIV_55,     /*!< SYSCTRL CLK DIV 55  */
    SYSCTRL_CLK_DIV_56,     /*!< SYSCTRL CLK DIV 56  */
    SYSCTRL_CLK_DIV_57,     /*!< SYSCTRL CLK DIV 57  */
    SYSCTRL_CLK_DIV_58,     /*!< SYSCTRL CLK DIV 58  */
    SYSCTRL_CLK_DIV_59,     /*!< SYSCTRL CLK DIV 59  */
    SYSCTRL_CLK_DIV_60,     /*!< SYSCTRL CLK DIV 60  */
    SYSCTRL_CLK_DIV_61,     /*!< SYSCTRL CLK DIV 61  */
    SYSCTRL_CLK_DIV_62,     /*!< SYSCTRL CLK DIV 62  */
    SYSCTRL_CLK_DIV_63,     /*!< SYSCTRL CLK DIV 63  */
    SYSCTRL_CLK_DIV_64,     /*!< SYSCTRL CLK DIV 64  */
    SYSCTRL_CLK_DIV_65,     /*!< SYSCTRL CLK DIV 65  */
    SYSCTRL_CLK_DIV_66,     /*!< SYSCTRL CLK DIV 66  */
    SYSCTRL_CLK_DIV_67,     /*!< SYSCTRL CLK DIV 67  */
    SYSCTRL_CLK_DIV_68,     /*!< SYSCTRL CLK DIV 68  */
    SYSCTRL_CLK_DIV_69,     /*!< SYSCTRL CLK DIV 69  */
    SYSCTRL_CLK_DIV_70,     /*!< SYSCTRL CLK DIV 70  */
    SYSCTRL_CLK_DIV_71,     /*!< SYSCTRL CLK DIV 71  */
    SYSCTRL_CLK_DIV_72,     /*!< SYSCTRL CLK DIV 72  */
    SYSCTRL_CLK_DIV_73,     /*!< SYSCTRL CLK DIV 73  */
    SYSCTRL_CLK_DIV_74,     /*!< SYSCTRL CLK DIV 74  */
    SYSCTRL_CLK_DIV_75,     /*!< SYSCTRL CLK DIV 75  */
    SYSCTRL_CLK_DIV_76,     /*!< SYSCTRL CLK DIV 76  */
    SYSCTRL_CLK_DIV_77,     /*!< SYSCTRL CLK DIV 77  */
    SYSCTRL_CLK_DIV_78,     /*!< SYSCTRL CLK DIV 78  */
    SYSCTRL_CLK_DIV_79,     /*!< SYSCTRL CLK DIV 79  */
    SYSCTRL_CLK_DIV_80,     /*!< SYSCTRL CLK DIV 80  */
    SYSCTRL_CLK_DIV_81,     /*!< SYSCTRL CLK DIV 81  */
    SYSCTRL_CLK_DIV_82,     /*!< SYSCTRL CLK DIV 82  */
    SYSCTRL_CLK_DIV_83,     /*!< SYSCTRL CLK DIV 83  */
    SYSCTRL_CLK_DIV_84,     /*!< SYSCTRL CLK DIV 84  */
    SYSCTRL_CLK_DIV_85,     /*!< SYSCTRL CLK DIV 85  */
    SYSCTRL_CLK_DIV_86,     /*!< SYSCTRL CLK DIV 86  */
    SYSCTRL_CLK_DIV_87,     /*!< SYSCTRL CLK DIV 87  */
    SYSCTRL_CLK_DIV_88,     /*!< SYSCTRL CLK DIV 88  */
    SYSCTRL_CLK_DIV_89,     /*!< SYSCTRL CLK DIV 89  */
    SYSCTRL_CLK_DIV_90,     /*!< SYSCTRL CLK DIV 90  */
    SYSCTRL_CLK_DIV_91,     /*!< SYSCTRL CLK DIV 91  */
    SYSCTRL_CLK_DIV_92,     /*!< SYSCTRL CLK DIV 92  */
    SYSCTRL_CLK_DIV_93,     /*!< SYSCTRL CLK DIV 93  */
    SYSCTRL_CLK_DIV_94,     /*!< SYSCTRL CLK DIV 94  */
    SYSCTRL_CLK_DIV_95,     /*!< SYSCTRL CLK DIV 95  */
    SYSCTRL_CLK_DIV_96,     /*!< SYSCTRL CLK DIV 96  */
    SYSCTRL_CLK_DIV_97,     /*!< SYSCTRL CLK DIV 97  */
    SYSCTRL_CLK_DIV_98,     /*!< SYSCTRL CLK DIV 98  */
    SYSCTRL_CLK_DIV_99,     /*!< SYSCTRL CLK DIV 99  */
    SYSCTRL_CLK_DIV_100,    /*!< SYSCTRL CLK DIV 100 */
    SYSCTRL_CLK_DIV_101,    /*!< SYSCTRL CLK DIV 101 */
    SYSCTRL_CLK_DIV_102,    /*!< SYSCTRL CLK DIV 102 */
    SYSCTRL_CLK_DIV_103,    /*!< SYSCTRL CLK DIV 103 */
    SYSCTRL_CLK_DIV_104,    /*!< SYSCTRL CLK DIV 104 */
    SYSCTRL_CLK_DIV_105,    /*!< SYSCTRL CLK DIV 105 */
    SYSCTRL_CLK_DIV_106,    /*!< SYSCTRL CLK DIV 106 */
    SYSCTRL_CLK_DIV_107,    /*!< SYSCTRL CLK DIV 107 */
    SYSCTRL_CLK_DIV_108,    /*!< SYSCTRL CLK DIV 108 */
    SYSCTRL_CLK_DIV_109,    /*!< SYSCTRL CLK DIV 109 */
    SYSCTRL_CLK_DIV_110,    /*!< SYSCTRL CLK DIV 110 */
    SYSCTRL_CLK_DIV_111,    /*!< SYSCTRL CLK DIV 111 */
    SYSCTRL_CLK_DIV_112,    /*!< SYSCTRL CLK DIV 112 */
    SYSCTRL_CLK_DIV_113,    /*!< SYSCTRL CLK DIV 113 */
    SYSCTRL_CLK_DIV_114,    /*!< SYSCTRL CLK DIV 114 */
    SYSCTRL_CLK_DIV_115,    /*!< SYSCTRL CLK DIV 115 */
    SYSCTRL_CLK_DIV_116,    /*!< SYSCTRL CLK DIV 116 */
    SYSCTRL_CLK_DIV_117,    /*!< SYSCTRL CLK DIV 117 */
    SYSCTRL_CLK_DIV_118,    /*!< SYSCTRL CLK DIV 118 */
    SYSCTRL_CLK_DIV_119,    /*!< SYSCTRL CLK DIV 119 */
    SYSCTRL_CLK_DIV_120,    /*!< SYSCTRL CLK DIV 120 */
    SYSCTRL_CLK_DIV_121,    /*!< SYSCTRL CLK DIV 121 */
    SYSCTRL_CLK_DIV_122,    /*!< SYSCTRL CLK DIV 122 */
    SYSCTRL_CLK_DIV_123,    /*!< SYSCTRL CLK DIV 123 */
    SYSCTRL_CLK_DIV_124,    /*!< SYSCTRL CLK DIV 124 */
    SYSCTRL_CLK_DIV_125,    /*!< SYSCTRL CLK DIV 125 */
    SYSCTRL_CLK_DIV_126,    /*!< SYSCTRL CLK DIV 126 */
    SYSCTRL_CLK_DIV_127,    /*!< SYSCTRL CLK DIV 127 */
    SYSCTRL_CLK_DIV_128,    /*!< SYSCTRL CLK DIV 128 */
    SYSCTRL_CLK_DIV_129,    /*!< SYSCTRL CLK DIV 129 */
    SYSCTRL_CLK_DIV_130,    /*!< SYSCTRL CLK DIV 130 */
    SYSCTRL_CLK_DIV_131,    /*!< SYSCTRL CLK DIV 131 */
    SYSCTRL_CLK_DIV_132,    /*!< SYSCTRL CLK DIV 132 */
    SYSCTRL_CLK_DIV_133,    /*!< SYSCTRL CLK DIV 133 */
    SYSCTRL_CLK_DIV_134,    /*!< SYSCTRL CLK DIV 134 */
    SYSCTRL_CLK_DIV_135,    /*!< SYSCTRL CLK DIV 135 */
    SYSCTRL_CLK_DIV_136,    /*!< SYSCTRL CLK DIV 136 */
    SYSCTRL_CLK_DIV_137,    /*!< SYSCTRL CLK DIV 137 */
    SYSCTRL_CLK_DIV_138,    /*!< SYSCTRL CLK DIV 138 */
    SYSCTRL_CLK_DIV_139,    /*!< SYSCTRL CLK DIV 139 */
    SYSCTRL_CLK_DIV_140,    /*!< SYSCTRL CLK DIV 140 */
    SYSCTRL_CLK_DIV_141,    /*!< SYSCTRL CLK DIV 141 */
    SYSCTRL_CLK_DIV_142,    /*!< SYSCTRL CLK DIV 142 */
    SYSCTRL_CLK_DIV_143,    /*!< SYSCTRL CLK DIV 143 */
    SYSCTRL_CLK_DIV_144,    /*!< SYSCTRL CLK DIV 144 */
    SYSCTRL_CLK_DIV_145,    /*!< SYSCTRL CLK DIV 145 */
    SYSCTRL_CLK_DIV_146,    /*!< SYSCTRL CLK DIV 146 */
    SYSCTRL_CLK_DIV_147,    /*!< SYSCTRL CLK DIV 147 */
    SYSCTRL_CLK_DIV_148,    /*!< SYSCTRL CLK DIV 148 */
    SYSCTRL_CLK_DIV_149,    /*!< SYSCTRL CLK DIV 149 */
    SYSCTRL_CLK_DIV_150,    /*!< SYSCTRL CLK DIV 150 */
    SYSCTRL_CLK_DIV_151,    /*!< SYSCTRL CLK DIV 151 */
    SYSCTRL_CLK_DIV_152,    /*!< SYSCTRL CLK DIV 152 */
    SYSCTRL_CLK_DIV_153,    /*!< SYSCTRL CLK DIV 153 */
    SYSCTRL_CLK_DIV_154,    /*!< SYSCTRL CLK DIV 154 */
    SYSCTRL_CLK_DIV_155,    /*!< SYSCTRL CLK DIV 155 */
    SYSCTRL_CLK_DIV_156,    /*!< SYSCTRL CLK DIV 156 */
    SYSCTRL_CLK_DIV_157,    /*!< SYSCTRL CLK DIV 157 */
    SYSCTRL_CLK_DIV_158,    /*!< SYSCTRL CLK DIV 158 */
    SYSCTRL_CLK_DIV_159,    /*!< SYSCTRL CLK DIV 159 */
    SYSCTRL_CLK_DIV_160,    /*!< SYSCTRL CLK DIV 160 */
    SYSCTRL_CLK_DIV_161,    /*!< SYSCTRL CLK DIV 161 */
    SYSCTRL_CLK_DIV_162,    /*!< SYSCTRL CLK DIV 162 */
    SYSCTRL_CLK_DIV_163,    /*!< SYSCTRL CLK DIV 163 */
    SYSCTRL_CLK_DIV_164,    /*!< SYSCTRL CLK DIV 164 */
    SYSCTRL_CLK_DIV_165,    /*!< SYSCTRL CLK DIV 165 */
    SYSCTRL_CLK_DIV_166,    /*!< SYSCTRL CLK DIV 166 */
    SYSCTRL_CLK_DIV_167,    /*!< SYSCTRL CLK DIV 167 */
    SYSCTRL_CLK_DIV_168,    /*!< SYSCTRL CLK DIV 168 */
    SYSCTRL_CLK_DIV_169,    /*!< SYSCTRL CLK DIV 169 */
    SYSCTRL_CLK_DIV_170,    /*!< SYSCTRL CLK DIV 170 */
    SYSCTRL_CLK_DIV_171,    /*!< SYSCTRL CLK DIV 171 */
    SYSCTRL_CLK_DIV_172,    /*!< SYSCTRL CLK DIV 172 */
    SYSCTRL_CLK_DIV_173,    /*!< SYSCTRL CLK DIV 173 */
    SYSCTRL_CLK_DIV_174,    /*!< SYSCTRL CLK DIV 174 */
    SYSCTRL_CLK_DIV_175,    /*!< SYSCTRL CLK DIV 175 */
    SYSCTRL_CLK_DIV_176,    /*!< SYSCTRL CLK DIV 176 */
    SYSCTRL_CLK_DIV_177,    /*!< SYSCTRL CLK DIV 177 */
    SYSCTRL_CLK_DIV_178,    /*!< SYSCTRL CLK DIV 178 */
    SYSCTRL_CLK_DIV_179,    /*!< SYSCTRL CLK DIV 179 */
    SYSCTRL_CLK_DIV_180,    /*!< SYSCTRL CLK DIV 180 */
    SYSCTRL_CLK_DIV_181,    /*!< SYSCTRL CLK DIV 181 */
    SYSCTRL_CLK_DIV_182,    /*!< SYSCTRL CLK DIV 182 */
    SYSCTRL_CLK_DIV_183,    /*!< SYSCTRL CLK DIV 183 */
    SYSCTRL_CLK_DIV_184,    /*!< SYSCTRL CLK DIV 184 */
    SYSCTRL_CLK_DIV_185,    /*!< SYSCTRL CLK DIV 185 */
    SYSCTRL_CLK_DIV_186,    /*!< SYSCTRL CLK DIV 186 */
    SYSCTRL_CLK_DIV_187,    /*!< SYSCTRL CLK DIV 187 */
    SYSCTRL_CLK_DIV_188,    /*!< SYSCTRL CLK DIV 188 */
    SYSCTRL_CLK_DIV_189,    /*!< SYSCTRL CLK DIV 189 */
    SYSCTRL_CLK_DIV_190,    /*!< SYSCTRL CLK DIV 190 */
    SYSCTRL_CLK_DIV_191,    /*!< SYSCTRL CLK DIV 191 */
    SYSCTRL_CLK_DIV_192,    /*!< SYSCTRL CLK DIV 192 */
    SYSCTRL_CLK_DIV_193,    /*!< SYSCTRL CLK DIV 193 */
    SYSCTRL_CLK_DIV_194,    /*!< SYSCTRL CLK DIV 194 */
    SYSCTRL_CLK_DIV_195,    /*!< SYSCTRL CLK DIV 195 */
    SYSCTRL_CLK_DIV_196,    /*!< SYSCTRL CLK DIV 196 */
    SYSCTRL_CLK_DIV_197,    /*!< SYSCTRL CLK DIV 197 */
    SYSCTRL_CLK_DIV_198,    /*!< SYSCTRL CLK DIV 198 */
    SYSCTRL_CLK_DIV_199,    /*!< SYSCTRL CLK DIV 199 */
    SYSCTRL_CLK_DIV_200,    /*!< SYSCTRL CLK DIV 200 */
    SYSCTRL_CLK_DIV_201,    /*!< SYSCTRL CLK DIV 201 */
    SYSCTRL_CLK_DIV_202,    /*!< SYSCTRL CLK DIV 202 */
    SYSCTRL_CLK_DIV_203,    /*!< SYSCTRL CLK DIV 203 */
    SYSCTRL_CLK_DIV_204,    /*!< SYSCTRL CLK DIV 204 */
    SYSCTRL_CLK_DIV_205,    /*!< SYSCTRL CLK DIV 205 */
    SYSCTRL_CLK_DIV_206,    /*!< SYSCTRL CLK DIV 206 */
    SYSCTRL_CLK_DIV_207,    /*!< SYSCTRL CLK DIV 207 */
    SYSCTRL_CLK_DIV_208,    /*!< SYSCTRL CLK DIV 208 */
    SYSCTRL_CLK_DIV_209,    /*!< SYSCTRL CLK DIV 209 */
    SYSCTRL_CLK_DIV_210,    /*!< SYSCTRL CLK DIV 210 */
    SYSCTRL_CLK_DIV_211,    /*!< SYSCTRL CLK DIV 211 */
    SYSCTRL_CLK_DIV_212,    /*!< SYSCTRL CLK DIV 212 */
    SYSCTRL_CLK_DIV_213,    /*!< SYSCTRL CLK DIV 213 */
    SYSCTRL_CLK_DIV_214,    /*!< SYSCTRL CLK DIV 214 */
    SYSCTRL_CLK_DIV_215,    /*!< SYSCTRL CLK DIV 215 */
    SYSCTRL_CLK_DIV_216,    /*!< SYSCTRL CLK DIV 216 */
    SYSCTRL_CLK_DIV_217,    /*!< SYSCTRL CLK DIV 217 */
    SYSCTRL_CLK_DIV_218,    /*!< SYSCTRL CLK DIV 218 */
    SYSCTRL_CLK_DIV_219,    /*!< SYSCTRL CLK DIV 219 */
    SYSCTRL_CLK_DIV_220,    /*!< SYSCTRL CLK DIV 220 */
    SYSCTRL_CLK_DIV_221,    /*!< SYSCTRL CLK DIV 221 */
    SYSCTRL_CLK_DIV_222,    /*!< SYSCTRL CLK DIV 222 */
    SYSCTRL_CLK_DIV_223,    /*!< SYSCTRL CLK DIV 223 */
    SYSCTRL_CLK_DIV_224,    /*!< SYSCTRL CLK DIV 224 */
    SYSCTRL_CLK_DIV_225,    /*!< SYSCTRL CLK DIV 225 */
    SYSCTRL_CLK_DIV_226,    /*!< SYSCTRL CLK DIV 226 */
    SYSCTRL_CLK_DIV_227,    /*!< SYSCTRL CLK DIV 227 */
    SYSCTRL_CLK_DIV_228,    /*!< SYSCTRL CLK DIV 228 */
    SYSCTRL_CLK_DIV_229,    /*!< SYSCTRL CLK DIV 229 */
    SYSCTRL_CLK_DIV_230,    /*!< SYSCTRL CLK DIV 230 */
    SYSCTRL_CLK_DIV_231,    /*!< SYSCTRL CLK DIV 231 */
    SYSCTRL_CLK_DIV_232,    /*!< SYSCTRL CLK DIV 232 */
    SYSCTRL_CLK_DIV_233,    /*!< SYSCTRL CLK DIV 233 */
    SYSCTRL_CLK_DIV_234,    /*!< SYSCTRL CLK DIV 234 */
    SYSCTRL_CLK_DIV_235,    /*!< SYSCTRL CLK DIV 235 */
    SYSCTRL_CLK_DIV_236,    /*!< SYSCTRL CLK DIV 236 */
    SYSCTRL_CLK_DIV_237,    /*!< SYSCTRL CLK DIV 237 */
    SYSCTRL_CLK_DIV_238,    /*!< SYSCTRL CLK DIV 238 */
    SYSCTRL_CLK_DIV_239,    /*!< SYSCTRL CLK DIV 239 */
    SYSCTRL_CLK_DIV_240,    /*!< SYSCTRL CLK DIV 240 */
    SYSCTRL_CLK_DIV_241,    /*!< SYSCTRL CLK DIV 241 */
    SYSCTRL_CLK_DIV_242,    /*!< SYSCTRL CLK DIV 242 */
    SYSCTRL_CLK_DIV_243,    /*!< SYSCTRL CLK DIV 243 */
    SYSCTRL_CLK_DIV_244,    /*!< SYSCTRL CLK DIV 244 */
    SYSCTRL_CLK_DIV_245,    /*!< SYSCTRL CLK DIV 245 */
    SYSCTRL_CLK_DIV_246,    /*!< SYSCTRL CLK DIV 246 */
    SYSCTRL_CLK_DIV_247,    /*!< SYSCTRL CLK DIV 247 */
    SYSCTRL_CLK_DIV_248,    /*!< SYSCTRL CLK DIV 248 */
    SYSCTRL_CLK_DIV_249,    /*!< SYSCTRL CLK DIV 249 */
    SYSCTRL_CLK_DIV_250,    /*!< SYSCTRL CLK DIV 250 */
    SYSCTRL_CLK_DIV_251,    /*!< SYSCTRL CLK DIV 251 */
    SYSCTRL_CLK_DIV_252,    /*!< SYSCTRL CLK DIV 252 */
    SYSCTRL_CLK_DIV_253,    /*!< SYSCTRL CLK DIV 253 */
    SYSCTRL_CLK_DIV_254,    /*!< SYSCTRL CLK DIV 254 */
    SYSCTRL_CLK_DIV_255,    /*!< SYSCTRL CLK DIV 255 */
    SYSCTRL_CLK_DIV_256,    /*!< SYSCTRL CLK DIV 256 */
} SYSCTRL_ClkDivETypeDef;

/**
  * @brief SYSCTRL SYSCLK Source Definition
  */
typedef enum {
    SYSCLK_SRC_RC32K      = 0,      /*!< SYSCLK Source RC32K        */
    SYSCLK_SRC_RC8M       = 1,      /*!< SYSCLK Source RC8M         */
    SYSCLK_SRC_PLL0DivClk = 2,      /*!< SYSCLK Source PLL0 Div Clk */
    SYSCLK_SRC_HOSC       = 3,      /*!< SYSCLK Source HOSC         */
} SYSCTRL_SysclkSrcETypeDef;

/**
  * @brief SYSCTRL GPIOA Debounce Clock Source Definition
  */
typedef enum {
    GPIOA_DBC_CLK_SRC_RC8M   = SYSCTRL_GPIOA_DBCCLK_SRC_RC8M,           /*!< GPIOA DBC CLK Source RC8M      */
    GPIOA_DBC_CLK_SRC_XOSC   = SYSCTRL_GPIOA_DBCCLK_SRC_XOSC,           /*!< GPIOA DBC CLK Source XOSC      */
    GPIOA_DBC_CLK_SRC_SYSCLK = SYSCTRL_GPIOA_DBCCLK_SRC_SYSCLK,         /*!< GPIOA DBC CLK Source SYSCLK    */
    GPIOA_DBC_CLK_SRC_RC32K  = SYSCTRL_GPIOA_DBCCLK_SRC_RC32K,          /*!< GPIOA DBC CLK Source RC32K     */
} SYSCTRL_GPIOADbcClkSrcETypeDef;

/**
  * @brief SYSCTRL GPIOB Debounce Clock Source Definition
  */
typedef enum {
    GPIOB_DBC_CLK_SRC_RC8M   = SYSCTRL_GPIOB_DBCCLK_SRC_RC8M,           /*!< GPIOB DBC CLK Source RC8M      */
    GPIOB_DBC_CLK_SRC_XOSC   = SYSCTRL_GPIOB_DBCCLK_SRC_XOSC,           /*!< GPIOB DBC CLK Source XOSC      */
    GPIOB_DBC_CLK_SRC_SYSCLK = SYSCTRL_GPIOB_DBCCLK_SRC_SYSCLK,         /*!< GPIOB DBC CLK Source SYSCLK    */
    GPIOB_DBC_CLK_SRC_RC32K  = SYSCTRL_GPIOB_DBCCLK_SRC_RC32K,          /*!< GPIOB DBC CLK Source RC32K     */
} SYSCTRL_GPIOBDbcClkSrcETypeDef;

/**
  * @brief SYSCTRL GPIOC Debounce Clock Source Definition
  */
typedef enum {
    GPIOC_DBC_CLK_SRC_RC8M   = SYSCTRL_GPIOC_DBCCLK_SRC_RC8M,           /*!< GPIOC DBC CLK Source RC8M      */
    GPIOC_DBC_CLK_SRC_XOSC   = SYSCTRL_GPIOC_DBCCLK_SRC_XOSC,           /*!< GPIOC DBC CLK Source XOSC      */
    GPIOC_DBC_CLK_SRC_SYSCLK = SYSCTRL_GPIOC_DBCCLK_SRC_SYSCLK,         /*!< GPIOC DBC CLK Source SYSCLK    */
    GPIOC_DBC_CLK_SRC_RC32K  = SYSCTRL_GPIOC_DBCCLK_SRC_RC32K,          /*!< GPIOC DBC CLK Source RC32K     */
} SYSCTRL_GPIOCDbcClkSrcETypeDef;

/**
  * @brief SYSCTRL GPIOD Debounce Clock Source Definition
  */
typedef enum {
    GPIOD_DBC_CLK_SRC_RC8M   = SYSCTRL_GPIOD_DBCCLK_SRC_RC8M,           /*!< GPIOD DBC CLK Source RC8M      */
    GPIOD_DBC_CLK_SRC_XOSC   = SYSCTRL_GPIOD_DBCCLK_SRC_XOSC,           /*!< GPIOD DBC CLK Source XOSC      */
    GPIOD_DBC_CLK_SRC_SYSCLK = SYSCTRL_GPIOD_DBCCLK_SRC_SYSCLK,         /*!< GPIOD DBC CLK Source SYSCLK    */
    GPIOD_DBC_CLK_SRC_RC32K  = SYSCTRL_GPIOD_DBCCLK_SRC_RC32K,          /*!< GPIOD DBC CLK Source RC32K     */
} SYSCTRL_GPIODDbcClkSrcETypeDef;

/**
  * @brief SYSCTRL Dflash Clock Source Definition
  */
typedef enum {
    DFLASH_CLK_SRC_RC8M       = SYSCTRL_DFLASH_MEMCLK_SRC_RC8M,         /*!< Dflash CLK Source RC8M         */
    DFLASH_CLK_SRC_PLL0DivClk = SYSCTRL_DFLASH_MEMCLK_SRC_PLL0DivClk,   /*!< Dflash CLK Source PLL0 Div Clk */
    DFLASH_CLK_SRC_PLL1DivClk = SYSCTRL_DFLASH_MEMCLK_SRC_PLL1DivClk,   /*!< Dflash CLK Source PLL1 Div Clk */
    DFLASH_CLK_SRC_PLL2DivClk = SYSCTRL_DFLASH_MEMCLK_SRC_PLL2DivClk,   /*!< Dflash CLK Source PLL2 Div Clk */
} SYSCTRL_DflashClkSrcETypeDef;

/**
  * @brief SYSCTRL Eflash Clock Source Definition
  */
typedef enum {
    EFLASH_CLK_SRC_RC8M       = SYSCTRL_EFLASH_MEMCLK_SRC_RC8M,         /*!< Eflash CLK Source RC8M         */
    EFLASH_CLK_SRC_PLL0DivClk = SYSCTRL_EFLASH_MEMCLK_SRC_PLL0DivClk,   /*!< Eflash CLK Source PLL0 Div Clk */
    EFLASH_CLK_SRC_PLL1DivClk = SYSCTRL_EFLASH_MEMCLK_SRC_PLL1DivClk,   /*!< Eflash CLK Source PLL1 Div Clk */
    EFLASH_CLK_SRC_PLL2DivClk = SYSCTRL_EFLASH_MEMCLK_SRC_PLL2DivClk,   /*!< Eflash CLK Source PLL2 Div Clk */
} SYSCTRL_EflashClkSrcETypeDef;

/**
  * @brief SYSCTRL ADC Function Clock Source Definition
  */
typedef enum {
    ADC_FUNC_CLK_SRC_RC8M = SYSCTRL_ADC_FUNCLK_SRC_RC8M,                /*!< ADC Function CLK Source RC8M   */
    ADC_FUNC_CLK_SRC_HOSC = SYSCTRL_ADC_FUNCLK_SRC_HOSC,                /*!< ADC Function CLK Source HOSC   */
    ADC_FUNC_CLK_SRC_PLL0 = SYSCTRL_ADC_FUNCLK_SRC_PLL0,                /*!< ADC Function CLK Source PLL0   */
    ADC_FUNC_CLK_SRC_PLL1 = SYSCTRL_ADC_FUNCLK_SRC_PLL1,                /*!< ADC Function CLK Source PLL1   */
} SYSCTRL_ADCFuncClkSrcETypeDef;

/**
  * @brief SYSCTRL HRPWM Function Clock Source Definition
  */
typedef enum {
    HRPWM_FUNC_CLK_SRC_RC8M = SYSCTRL_HRPWM_FUNCLK_SRC_RC8M,                /*!< HRPWM Function CLK Source RC8M   */
    HRPWM_FUNC_CLK_SRC_HOSC = SYSCTRL_HRPWM_FUNCLK_SRC_HOSC,                /*!< HRPWM Function CLK Source HOSC   */
    HRPWM_FUNC_CLK_SRC_PLL0 = SYSCTRL_HRPWM_FUNCLK_SRC_PLL0,                /*!< HRPWM Function CLK Source PLL0   */
    HRPWM_FUNC_CLK_SRC_PLL1 = SYSCTRL_HRPWM_FUNCLK_SRC_PLL1,                /*!< HRPWM Function CLK Source PLL1   */
} SYSCTRL_HRPWMFuncClkSrcETypeDef;

/**
  * @brief SYSCTRL PLLCLK Source Definition
  */
typedef enum {
    PLLCLK_SRC_XOSC = 0,            /*!< PLLCLK Source XOSC */
    PLLCLK_SRC_RC8M = 1,            /*!< PLLCLK Source RC8M */
    PLLCLK_SRC_DFT  = 3,            /*!< PLLCLK Source DFT  */
} SYSCTRL_PllClkSrcETypeDef;

/**
  * @brief SYSCTRL SYSCLK Config Definition
  */
typedef struct __SYSCTRL_SysclkUserCfgTypeDef {
    SYSCTRL_SysclkSrcETypeDef sysclk_src;   /*!< SYSCLK Source      */
    SYSCTRL_PllClkSrcETypeDef pll0clk_src;  /*!< PLLCLK Source      */
    uint32_t sysclk_src_freq;               /*!< SYSCLK Source Freq */
    uint32_t pll0clk_src_freq;              /*!< PLLCLK Source Freq */
    uint32_t sysclk_freq;                   /*!< SYSCLK Freq        */
    SYSCTRL_ClkDivETypeDef apb0_clk_div;    /*!< APB0 clock Div     */
    SYSCTRL_ClkDivETypeDef apb1_clk_div;    /*!< APB1 clock Div     */
} SYSCTRL_SysclkUserCfgTypeDef;

/**
  * @brief SYSCTRL PLL1/2 Config Definition
  */
typedef struct __SYSCTRL_PLLUserCfgTypeDef {
    SYSCTRL_PllClkSrcETypeDef pll_clk_src;  /*!< PLLCLK Source      */
    uint32_t pll_in_freq;                   /*!< PLLCLK Input Freq  */
    uint32_t pll_user_freq;                 /*!< PLLCLK User Freq   */
} SYSCTRL_PLLUserCfgTypeDef;

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup SYSCTRL_LL_Exported_Functions SYSCTRL LL Exported Functions
  * @brief    SYSCTRL LL Exported Functions
  * @{
  */

/** @addtogroup SYSCTRL_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_SYSCTRL_SysclkInit(SYSCTRL_TypeDef *Instance, SYSCTRL_SysclkUserCfgTypeDef *sysclk_cfg);
LL_StatusETypeDef LL_SYSCTRL_GPIOA_DbcClkCfg(SYSCTRL_GPIOADbcClkSrcETypeDef src, SYSCTRL_ClkDivETypeDef div);
LL_StatusETypeDef LL_SYSCTRL_GPIOB_DbcClkCfg(SYSCTRL_GPIOBDbcClkSrcETypeDef src, SYSCTRL_ClkDivETypeDef div);
LL_StatusETypeDef LL_SYSCTRL_GPIOC_DbcClkCfg(SYSCTRL_GPIOCDbcClkSrcETypeDef src, SYSCTRL_ClkDivETypeDef div);
LL_StatusETypeDef LL_SYSCTRL_GPIOD_DbcClkCfg(SYSCTRL_GPIODDbcClkSrcETypeDef src, SYSCTRL_ClkDivETypeDef div);
LL_StatusETypeDef LL_SYSCTRL_DFLASH_ClkCfg(SYSCTRL_DflashClkSrcETypeDef src, SYSCTRL_ClkDivETypeDef div);
LL_StatusETypeDef LL_SYSCTRL_EFLASH_ClkCfg(SYSCTRL_EflashClkSrcETypeDef src, SYSCTRL_ClkDivETypeDef div);
LL_StatusETypeDef LL_SYSCTRL_ADC_FuncClkCfg(SYSCTRL_ADCFuncClkSrcETypeDef src, SYSCTRL_ClkDivETypeDef div);
LL_StatusETypeDef LL_SYSCTRL_HRPWM_FuncClkCfg(SYSCTRL_HRPWMFuncClkSrcETypeDef src, SYSCTRL_ClkDivETypeDef div);
uint32_t LL_SYSCTRL_SysclkGet(void);
uint32_t LL_SYSCTRL_AHBClkGet(void);
uint32_t LL_SYSCTRL_APB0ClkGet(void);
uint32_t LL_SYSCTRL_APB1ClkGet(void);
/**
  * @}
  */


/** @addtogroup SYSCTRL_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_SYSCTRL_Pll0Cfg(SYSCTRL_TypeDef *Instance, SYSCTRL_PLLUserCfgTypeDef *pll0_cfg);
LL_StatusETypeDef LL_SYSCTRL_Pll1Cfg(SYSCTRL_TypeDef *Instance, SYSCTRL_PLLUserCfgTypeDef *pll1_cfg);
LL_StatusETypeDef LL_SYSCTRL_Pll2Cfg(SYSCTRL_TypeDef *Instance, SYSCTRL_PLLUserCfgTypeDef *pll2_cfg);
/**
  * @}
  */


/** @addtogroup SYSCTRL_LL_Exported_Functions_Group3
  * @{
  */
void LL_SYSCTRL_LSTMR_ClkEnRstRelease(void);
void LL_SYSCTRL_LSTMR_ClkDisRstAssert(void);
void LL_SYSCTRL_UART1_ClkEnRstRelease(void);
void LL_SYSCTRL_UART1_ClkDisRstAssert(void);
void LL_SYSCTRL_UART0_ClkEnRstRelease(void);
void LL_SYSCTRL_UART0_ClkDisRstAssert(void);
void LL_SYSCTRL_I2C1_ClkEnRstRelease(void);
void LL_SYSCTRL_I2C1_ClkDisRstAssert(void);
void LL_SYSCTRL_I2C0_ClkEnRstRelease(void);
void LL_SYSCTRL_I2C0_ClkDisRstAssert(void);
void LL_SYSCTRL_ECU_ClkEnRstRelease(void);
void LL_SYSCTRL_ECU_ClkDisRstAssert(void);
void LL_SYSCTRL_IIR4_ClkEnRstRelease(void);
void LL_SYSCTRL_IIR4_ClkDisRstAssert(void);
void LL_SYSCTRL_IIR3_ClkEnRstRelease(void);
void LL_SYSCTRL_IIR3_ClkDisRstAssert(void);
void LL_SYSCTRL_IIR2_ClkEnRstRelease(void);
void LL_SYSCTRL_IIR2_ClkDisRstAssert(void);
void LL_SYSCTRL_IIR1_ClkEnRstRelease(void);
void LL_SYSCTRL_IIR1_ClkDisRstAssert(void);
void LL_SYSCTRL_IIR0_ClkEnRstRelease(void);
void LL_SYSCTRL_IIR0_ClkDisRstAssert(void);
void LL_SYSCTRL_DALI_ClkEnRstRelease(void);
void LL_SYSCTRL_DALI_ClkDisRstAssert(void);
void LL_SYSCTRL_FPLL2_RstRelease(void);
void LL_SYSCTRL_FPLL2_RstAssert(void);
void LL_SYSCTRL_FPLL1_RstRelease(void);
void LL_SYSCTRL_FPLL1_RstAssert(void);
void LL_SYSCTRL_FPLL0_RstRelease(void);
void LL_SYSCTRL_FPLL0_RstAssert(void);
void LL_SYSCTRL_USB_ClkEnRstRelease(void);
void LL_SYSCTRL_USB_ClkDisRstAssert(void);
void LL_SYSCTRL_DFLASH_ClkEnRstRelease(void);
void LL_SYSCTRL_DFLASH_ClkDisRstAssert(void);
void LL_SYSCTRL_EFLASH_ClkEnRstRelease(void);
void LL_SYSCTRL_EFLASH_ClkDisRstAssert(void);
void LL_SYSCTRL_HRPWM_ClkEnRstRelease(void);
void LL_SYSCTRL_HRPWM_ClkDisRstAssert(void);
void LL_SYSCTRL_ADC_ClkEnRstRelease(void);
void LL_SYSCTRL_ADC_ClkDisRstAssert(void);
void LL_SYSCTRL_DAC_ClkEnRstRelease(void);
void LL_SYSCTRL_DAC_ClkDisRstAssert(void);
void LL_SYSCTRL_CMP_ClkEnRstRelease(void);
void LL_SYSCTRL_CMP_ClkDisRstAssert(void);
void LL_SYSCTRL_GPIOD_ClkEnRstRelease(void);
void LL_SYSCTRL_GPIOD_ClkDisRstAssert(void);
void LL_SYSCTRL_GPIOC_ClkEnRstRelease(void);
void LL_SYSCTRL_GPIOC_ClkDisRstAssert(void);
void LL_SYSCTRL_GPIOB_ClkEnRstRelease(void);
void LL_SYSCTRL_GPIOB_ClkDisRstAssert(void);
void LL_SYSCTRL_GPIOA_ClkEnRstRelease(void);
void LL_SYSCTRL_GPIOA_ClkDisRstAssert(void);
void LL_SYSCTRL_HSTMR_ClkEnRstRelease(void);
void LL_SYSCTRL_HSTMR_ClkDisRstAssert(void);
void LL_SYSCTRL_CAN_ClkEnRstRelease(void);
void LL_SYSCTRL_CAN_ClkDisRstAssert(void);
void LL_SYSCTRL_DMA_ClkEnRstRelease(void);
void LL_SYSCTRL_DMA_ClkDisRstAssert(void);

void LL_SYSCTRL_AllPeriphRstAssert(void);
void LL_SYSCTRL_AllPeriphRstRelease(void);
/**
  * @}
  */


/** @addtogroup SYSCTRL_LL_Exported_Functions_Group4
  * @{
  */
void LL_SYSCTRL_PMUCfg(void);
/**
  * @}
  */

/**
  * @}
  */


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _TAE32F53XX_LL_SYSCTRL_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

