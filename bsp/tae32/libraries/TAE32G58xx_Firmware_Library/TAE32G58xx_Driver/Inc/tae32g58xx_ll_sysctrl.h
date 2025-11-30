/**
  ******************************************************************************
  * @file    tae32g58xx_ll_sysctrl.h
  * @author  MCD Application Team
  * @brief   Header file for SYSCTRL LL module
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
#ifndef _TAE32G58XX_LL_SYSCTRL_H_
#define _TAE32G58XX_LL_SYSCTRL_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup SYSCTRL_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup SYSCTRL_LL_Exported_Constants SYSCTRL LL Exported Constants
  * @brief    SYSCTRL LL Exported Constants
  * @{
  */

#define SYSCTRL_FCR3_PLL0BAND_Pos         (30UL)                    /*!< PLL0BAND (Bit 30)                                     */
#define SYSCTRL_FCR3_PLL0BAND_Msk         (0xC0000000UL)            /*!< PLL0BAND (Bitfield-Mask: 0x03)                        */

/**
  * @}
  */



/* Exported Macros -----------------------------------------------------------*/
/** @defgroup SYSCTRL_LL_Exported_Macros SYSCTRL LL Exported Macros
  * @brief    SYSCTRL LL Exported Macros
  * @{
  */

/**
  * @brief  EFLASH Double Bank Switch Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_EFLASHDblBankSwitch_En(__SYSCTRL__)        SET_BIT((__SYSCTRL__)->SYSDCR, 0x1000UL)

/**
  * @brief  EFLASH Double Bank Switch Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_EFLASHDblBankSwitch_Dis(__SYSCTRL__)       CLEAR_BIT((__SYSCTRL__)->SYSDCR, 0x1000UL)

/**
  * @brief  HRPWM Debug Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_HRPWMDbg_En(__SYSCTRL__)                   SET_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_PWMDEN_Msk)

/**
  * @brief  HRPWM Debug Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_HRPWMDbg_Dis(__SYSCTRL__)                  CLEAR_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_PWMDEN_Msk)

/**
  * @brief  WWDG Debug Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_WWDG_Dbg_En(__SYSCTRL__)                   SET_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_WWDGDEN_Msk)

/**
  * @brief  WWDG Debug Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_WWDG_Dbg_Dis(__SYSCTRL__)                  CLEAR_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_WWDGDEN_Msk)

/**
  * @brief  IWDG Debug Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IWDG_Dbg_En(__SYSCTRL__)                   SET_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_IWDGDEN_Msk)

/**
  * @brief  IWDG Debug Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_IWDG_Dbg_Dis(__SYSCTRL__)                  CLEAR_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_IWDGDEN_Msk)

/**
  * @brief  TMR0 Debug Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TMR0_Dbg_En(__SYSCTRL__)                   SET_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_TMR0DEN_Msk)

/**
  * @brief  TMR0 Debug Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TMR0_Dbg_Dis(__SYSCTRL__)                  CLEAR_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_TMR0DEN_Msk)

/**
  * @brief  TMR1 Debug Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TMR1_Dbg_En(__SYSCTRL__)                   SET_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_TMR1DEN_Msk)

/**
  * @brief  TMR1 Debug Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TMR1_Dbg_Dis(__SYSCTRL__)                  CLEAR_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_TMR1DEN_Msk)

/**
  * @brief  TMR2 Debug Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TMR2_Dbg_En(__SYSCTRL__)                   SET_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_TMR2DEN_Msk)

/**
  * @brief  TMR2 Debug Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TMR2_Dbg_Dis(__SYSCTRL__)                  CLEAR_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_TMR2DEN_Msk)

/**
  * @brief  TMR3 Debug Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TMR3_Dbg_En(__SYSCTRL__)                   SET_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_TMR3DEN_Msk)

/**
  * @brief  TMR3 Debug Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TMR3_Dbg_Dis(__SYSCTRL__)                  CLEAR_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_TMR3DEN_Msk)

/**
  * @brief  TMR4 Debug Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TMR4_Dbg_En(__SYSCTRL__)                   SET_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_TMR4DEN_Msk)

/**
  * @brief  TMR4 Debug Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TMR4_Dbg_Dis(__SYSCTRL__)                  CLEAR_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_TMR4DEN_Msk)

/**
  * @brief  TMR7 Debug Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TMR7_Dbg_En(__SYSCTRL__)                   SET_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_TMR7DEN_Msk)

/**
  * @brief  TMR7 Debug Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TMR7_Dbg_Dis(__SYSCTRL__)                  CLEAR_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_TMR7DEN_Msk)

/**
  * @brief  TMR8 Debug Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TMR8_Dbg_En(__SYSCTRL__)                   SET_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_TMR8DEN_Msk)

/**
  * @brief  TMR8 Debug Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TMR8_Dbg_Dis(__SYSCTRL__)                  CLEAR_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_TMR8DEN_Msk)

/**
  * @brief  TMR9 Debug Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TMR9_Dbg_En(__SYSCTRL__)                   SET_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_TMR9DEN_Msk)

/**
  * @brief  TMR9 Debug Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TMR9_Dbg_Dis(__SYSCTRL__)                  CLEAR_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_TMR9DEN_Msk)

/**
  * @brief  TMR10 Debug Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TMR10_Dbg_En(__SYSCTRL__)                  SET_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_TMR10DEN_Msk)

/**
  * @brief  TMR10 Debug Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TMR10_Dbg_Dis(__SYSCTRL__)                 CLEAR_BIT((__SYSCTRL__)->SYSDCR, SYSCTRL_SYSDCR_TMR10DEN_Msk)


/**
  * @brief  PF0 FM+ Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PF0FMPlus_En(__SYSCTRL__)                  \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (SET_BIT((*(__IO uint32_t *)0x40021004UL), 0x8000UL)) : 0)

/**
  * @brief  PF0 FM+ Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PF0FMPlus_Dis(__SYSCTRL__)                 \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (CLEAR_BIT((*(__IO uint32_t *)0x40021004UL), 0x8000UL)) : 0)

/**
  * @brief  PC11 FM+ Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PC11FMPlus_En(__SYSCTRL__)                 \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (SET_BIT((*(__IO uint32_t *)0x40021004UL), 0x4000UL)) : 0)

/**
  * @brief  PC11 FM+ Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PC11FMPlus_Dis(__SYSCTRL__)                \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (CLEAR_BIT((*(__IO uint32_t *)0x40021004UL), 0x4000UL)) : 0)

/**
  * @brief  PC9 FM+ Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PC9FMPlus_En(__SYSCTRL__)                  \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (SET_BIT((*(__IO uint32_t *)0x40021004UL), 0x2000UL)) : 0)

/**
  * @brief  PC9 FM+ Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PC9FMPlus_Dis(__SYSCTRL__)                 \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (CLEAR_BIT((*(__IO uint32_t *)0x40021004UL), 0x2000UL)) : 0)

/**
  * @brief  PC8 FM+ Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PC8FMPlus_En(__SYSCTRL__)                  \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (SET_BIT((*(__IO uint32_t *)0x40021004UL), 0x1000UL)) : 0)

/**
  * @brief  PC8 FM+ Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PC8FMPlus_Dis(__SYSCTRL__)                 \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (CLEAR_BIT((*(__IO uint32_t *)0x40021004UL), 0x1000UL)) : 0)

/**
  * @brief  PC7 FM+ Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PC7FMPlus_En(__SYSCTRL__)                  \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (SET_BIT((*(__IO uint32_t *)0x40021004UL), 0x800UL)) : 0)

/**
  * @brief  PC7 FM+ Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PC7FMPlus_Dis(__SYSCTRL__)                 \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (CLEAR_BIT((*(__IO uint32_t *)0x40021004UL), 0x800UL)) : 0)

/**
  * @brief  PC6 FM+ Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PC6FMPlus_En(__SYSCTRL__)                  \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (SET_BIT((*(__IO uint32_t *)0x40021004UL), 0x400UL)) : 0)

/**
  * @brief  PC6 FM+ Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PC6FMPlus_Dis(__SYSCTRL__)                 \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (CLEAR_BIT((*(__IO uint32_t *)0x40021004UL), 0x400UL)) : 0)

/**
  * @brief  PC4 FM+ Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PC4FMPlus_En(__SYSCTRL__)                  \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (SET_BIT((*(__IO uint32_t *)0x40021004UL), 0x200UL)) : 0)

/**
  * @brief  PC4 FM+ Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PC4FMPlus_Dis(__SYSCTRL__)                 \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (CLEAR_BIT((*(__IO uint32_t *)0x40021004UL), 0x200UL)) : 0)

/**
  * @brief  PB9 FM+ Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PB9FMPlus_En(__SYSCTRL__)                  \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (SET_BIT((*(__IO uint32_t *)0x40021004UL), 0x100UL)) : 0)

/**
  * @brief  PB9 FM+ Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PB9FMPlus_Dis(__SYSCTRL__)                 \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (CLEAR_BIT((*(__IO uint32_t *)0x40021004UL), 0x100UL)) : 0)

/**
  * @brief  PB8 FM+ Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PB8FMPlus_En(__SYSCTRL__)                  \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (SET_BIT((*(__IO uint32_t *)0x40021004UL), 0x80UL)) : 0)

/**
  * @brief  PB8 FM+ Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PB8FMPlus_Dis(__SYSCTRL__)                 \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (CLEAR_BIT((*(__IO uint32_t *)0x40021004UL), 0x80UL)) : 0)

/**
  * @brief  PB7 FM+ Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PB7FMPlus_En(__SYSCTRL__)                  \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (SET_BIT((*(__IO uint32_t *)0x40021004UL), 0x40UL)) : 0)

/**
  * @brief  PB7 FM+ Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PB7FMPlus_Dis(__SYSCTRL__)                 \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (CLEAR_BIT((*(__IO uint32_t *)0x40021004UL), 0x40UL)) : 0)

/**
  * @brief  PB5 FM+ Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PB5FMPlus_En(__SYSCTRL__)                  \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (SET_BIT((*(__IO uint32_t *)0x40021004UL), 0x20UL)) : 0)

/**
  * @brief  PB5 FM+ Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PB5FMPlus_Dis(__SYSCTRL__)                 \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (CLEAR_BIT((*(__IO uint32_t *)0x40021004UL), 0x20UL)) : 0)

/**
  * @brief  PA15 FM+ Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PA15FMPlus_En(__SYSCTRL__)                 \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (SET_BIT((*(__IO uint32_t *)0x40021004UL), 0x10UL)) : 0)

/**
  * @brief  PA15 FM+ Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PA15FMPlus_Dis(__SYSCTRL__)                \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (CLEAR_BIT((*(__IO uint32_t *)0x40021004UL), 0x10UL)) : 0)

/**
  * @brief  PA14 FM+ Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PA14FMPlus_En(__SYSCTRL__)                 \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (SET_BIT((*(__IO uint32_t *)0x40021004UL), 0x8UL)) : 0)

/**
  * @brief  PA14 FM+ Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PA14FMPlus_Dis(__SYSCTRL__)                \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (CLEAR_BIT((*(__IO uint32_t *)0x40021004UL), 0x8UL)) : 0)

/**
  * @brief  PA13 FM+ Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PA13FMPlus_En(__SYSCTRL__)                 \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (SET_BIT((*(__IO uint32_t *)0x40021004UL), 0x4UL)) : 0)

/**
  * @brief  PA13 FM+ Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PA13FMPlus_Dis(__SYSCTRL__)                \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (CLEAR_BIT((*(__IO uint32_t *)0x40021004UL), 0x4UL)) : 0)

/**
  * @brief  PA10 FM+ Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PA10FMPlus_En(__SYSCTRL__)                 \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (SET_BIT((*(__IO uint32_t *)0x40021004UL), 0x2UL)) : 0)

/**
  * @brief  PA10 FM+ Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PA10FMPlus_Dis(__SYSCTRL__)                \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (CLEAR_BIT((*(__IO uint32_t *)0x40021004UL), 0x2UL)) : 0)

/**
  * @brief  PA9 FM+ Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PA9FMPlus_En(__SYSCTRL__)                  \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (SET_BIT((*(__IO uint32_t *)0x40021004UL), 0x1UL)) : 0)

/**
  * @brief  PA9 FM+ Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_PA9FMPlus_Dis(__SYSCTRL__)                 \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) ? (CLEAR_BIT((*(__IO uint32_t *)0x40021004UL), 0x1UL)) : 0)


/**
  * @brief  DMA Request Config Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  pos DMA Request Control Bit
  * @return None
  */
#define __LL_SYSCTRL_DmaReqCfg_Set(__SYSCTRL__, pos)            \
        SET_BIT((__SYSCTRL__)->DMARCR, (0x1UL << (pos & 0x1fUL)) & SYSCTRL_DMARCR_DRCR_Msk)

/**
  * @brief  DMA Request Config Reset
  * @note   The LSB is Request_0 and MSB is Request_31
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  pos DMA Request Control Bit
  * @return None
  */
#define __LL_SYSCTRL_DmaReqCfg_Reset(__SYSCTRL__, pos)          \
        CLEAR_BIT((__SYSCTRL__)->DMARCR, (0x1UL << (pos & 0x1fUL)) & SYSCTRL_DMARCR_DRCR_Msk)

/**
  * @brief  DMA Request Config Get
  * @note   For the sequence of register data bit, LSB is bit19
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return DMA Request Config 
  */
#define __LL_SYSCTRL_DmaReqCfg_Get(__SYSCTRL__)                 READ_REG((__SYSCTRL__)->DMARCR)


/**
  * @brief  FLASH Double Bank Mapping Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  map Bank Mapping @ref SYSCTRL_FlashBankMappingETypeDef
  * @return None
  */
#define __LL_SYSCTRL_BankMapping_Set(__SYSCTRL__, map)          \
        MODIFY_REG((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_FBM_Msk, ((map) & 0x01) << SYSCTRL_SYSCR_FBM_Pos)

/**
  * @brief  FLASH Double Bank Mapping Get
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return Bank Mapping @ref SYSCTRL_FlashBankMappingETypeDef
  * 
  */
#define __LL_SYSCTRL_BankMapping_Get(__SYSCTRL__)               \
        READ_BIT_SHIFT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_FBM_Msk, SYSCTRL_SYSCR_FBM_Pos)

/**
  * @brief  QEI2 Fault Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_QEI2Fault_En(__SYSCTRL__)                  SET_BIT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_QEI2FE_Msk)

/**
  * @brief  QEI2 Fault Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_QEI2Fault_Dis(__SYSCTRL__)                 CLEAR_BIT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_QEI2FE_Msk)

/**
  * @brief  Judge is QEI2 Fault Enable or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_SYSCTRL_IsQEI2FaultEn(__SYSCTRL__)                 READ_BIT_SHIFT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_QEI2FE_Msk, SYSCTRL_SYSCR_QEI2FE_Pos)

/**
  * @brief  QEI1 Fault Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_QEI1Fault_En(__SYSCTRL__)                  SET_BIT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_QEI1FE_Msk)

/**
  * @brief  QEI1 Fault Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_QEI1Fault_Dis(__SYSCTRL__)                 CLEAR_BIT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_QEI1FE_Msk)

/**
  * @brief  Judge is QEI1 Fault Enable or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_SYSCTRL_IsQEI1FaultEn(__SYSCTRL__)                 READ_BIT_SHIFT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_QEI1FE_Msk, SYSCTRL_SYSCR_QEI1FE_Pos)

/**
  * @brief  QEI0 Fault Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_QEI0Fault_En(__SYSCTRL__)                  SET_BIT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_QEI0FE_Msk)

/**
  * @brief  QEI0 Fault Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_QEI0Fault_Dis(__SYSCTRL__)                 CLEAR_BIT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_QEI0FE_Msk)

/**
  * @brief  Judge is QEI0 Fault Enable or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_SYSCTRL_IsQEI0FaultEn(__SYSCTRL__)                 READ_BIT_SHIFT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_QEI0FE_Msk, SYSCTRL_SYSCR_QEI0FE_Pos)

/**
  * @brief  PLL Lock Fault Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PLLLockFault_En(__SYSCTRL__)               SET_BIT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_PLLFE_Msk)

/**
  * @brief  PLL Lock Fault Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_PLLLockFault_Dis(__SYSCTRL__)              CLEAR_BIT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_PLLFE_Msk)

/**
  * @brief  Judge is PLL Lock Fault Enable or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_SYSCTRL_IsPLLLockFaultEn(__SYSCTRL__)              READ_BIT_SHIFT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_PLLFE_Msk, SYSCTRL_SYSCR_PLLFE_Pos)

/**
  * @brief  XOSC Loss Fault Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_XOSCLossFault_En(__SYSCTRL__)              SET_BIT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_OSCFE_Msk)

/**
  * @brief  XOSC Loss Fault Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_XOSCLossFault_Dis(__SYSCTRL__)             CLEAR_BIT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_OSCFE_Msk)

/**
  * @brief  Judge is XOSC Loss Fault Enable or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_SYSCTRL_IsXOSCLossFaultEn(__SYSCTRL__)             READ_BIT_SHIFT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_OSCFE_Msk, SYSCTRL_SYSCR_OSCFE_Pos)

/**
  * @brief  CPU Lockup Fault Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_CPULockupFault_En(__SYSCTRL__)             SET_BIT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_LKFE_Msk)

/**
  * @brief  CPU Lockup Fault Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_CPULockupFault_Dis(__SYSCTRL__)            CLEAR_BIT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_LKFE_Msk)

/**
  * @brief  Judge is CPU Lockup Fault Enable or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_SYSCTRL_IsCPULockupFaultEn(__SYSCTRL__)            READ_BIT_SHIFT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_LKFE_Msk, SYSCTRL_SYSCR_LKFE_Pos)

/**
  * @brief  FLASH nBits ECC Fault Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_NBitECCFault_En(__SYSCTRL__)               SET_BIT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_ECCFE_Msk)

/**
  * @brief  FLASH nBits ECC Fault Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_NBitECCFault_Dis(__SYSCTRL__)              CLEAR_BIT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_ECCFE_Msk)

/**
  * @brief  Judge is CPU Lockup Fault Enable or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 is Disable
  * @retval 1 is Enable
  */
#define __LL_SYSCTRL_IsNBitECCFaultEn(__SYSCTRL__)              READ_BIT_SHIFT((__SYSCTRL__)->SYSCR, SYSCTRL_SYSCR_ECCFE_Msk, SYSCTRL_SYSCR_ECCFE_Pos)


/**
  * @brief  ADC Buffer Source Selection
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  src ADC Buffer Source
  * @return None
  */
#define __LL_SYSCTRL_ADCBufSrc_Sel(__SYSCTRL__, src)            \
        MODIFY_REG((__SYSCTRL__)->SYSATR, SYSCTRL_SYSATR_ABFSRC_Msk, (((src) & 0x1fUL) << SYSCTRL_SYSATR_ABFSRC_Pos))

/**
  * @brief  ADC Buffer Bypass Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ADCBufBypass_En(__SYSCTRL__)               SET_BIT((__SYSCTRL__)->SYSATR, SYSCTRL_SYSATR_ABFBYP_Msk)

/**
  * @brief  ADC Buffer Bypass Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ADCBufBypass_Dis(__SYSCTRL__)              CLEAR_BIT((__SYSCTRL__)->SYSATR, SYSCTRL_SYSATR_ABFBYP_Msk)

/**
  * @brief  ADC Buffer Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ADCBuf_En(__SYSCTRL__)                     SET_BIT((__SYSCTRL__)->SYSATR, SYSCTRL_SYSATR_ABFEN_Msk)

/**
  * @brief  ADC Buffer Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_ADCBuf_Dis(__SYSCTRL__)                    CLEAR_BIT((__SYSCTRL__)->SYSATR, SYSCTRL_SYSATR_ABFEN_Msk)


/**
  * @brief  AVDD Drop Down Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AVDD_DropDown_En(__SYSCTRL__)              SET_BIT((__SYSCTRL__)->PWRCR, SYSCTRL_PWRCR_AVDDDRD_Msk)

/**
  * @brief  AVDD Drop Down Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AVDD_DropDown_Dis(__SYSCTRL__)             CLEAR_BIT((__SYSCTRL__)->PWRCR, SYSCTRL_PWRCR_AVDDDRD_Msk)

/**
  * @brief  VDD Voltage Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  vol VDD Voltage @ref SYSCTRL_VDDVolETypeDef
  * @return None
  */
#define __LL_SYSCTRL_VDD_Vol_Set(__SYSCTRL__, vol)              \
        MODIFY_REG((__SYSCTRL__)->PWRCR, SYSCTRL_PWRCR_VDDSET_Msk, (((vol) & 0xfUL) << SYSCTRL_PWRCR_VDDSET_Pos))

/**
  * @brief  AVDD Voltage Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  vol AVDD Voltage @ref SYSCTRL_AVDDVolETypeDef
  * @return None
  */
#define __LL_SYSCTRL_AVDD_Vol_Set(__SYSCTRL__, vol)             \
        MODIFY_REG((__SYSCTRL__)->PWRCR, SYSCTRL_PWRCR_AVDDSET_Msk, (((vol) & 0x3UL) << SYSCTRL_PWRCR_AVDDSET_Pos))

/**
  * @brief  AVDD Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AVDD_En(__SYSCTRL__)                       SET_BIT((__SYSCTRL__)->PWRCR, SYSCTRL_PWRCR_AVDDEN_Msk)

/**
  * @brief  AVDD Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AVDD_Dis(__SYSCTRL__)                      CLEAR_BIT((__SYSCTRL__)->PWRCR, SYSCTRL_PWRCR_AVDDEN_Msk)

/**
  * @brief  Temperature Sensor Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TempSensor_En(__SYSCTRL__)                 SET_BIT((__SYSCTRL__)->PWRCR, SYSCTRL_PWRCR_TSE_Msk)

/**
  * @brief  Temperature Sensor Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_TempSensor_Dis(__SYSCTRL__)                CLEAR_BIT((__SYSCTRL__)->PWRCR, SYSCTRL_PWRCR_TSE_Msk)


/**
  * @brief  VDD Over Current Threshold Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  thres VDD Over Current Threshold @ref SYSCTRL_VDDOverCurThresETypeDef
  * @return None
  */
#define __LL_SYSCTRL_VDD_OverCurThres_Set(__SYSCTRL__, thres)   \
        MODIFY_REG((__SYSCTRL__)->PLCR, SYSCTRL_PLCR_VDDOCL_Msk, (((thres) & 0x3UL) << SYSCTRL_PLCR_VDDOCL_Pos))

/**
  * @brief  AVCC Low Voltage Threshold Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  thres AVCC Low Voltage Threshold @ref SYSCTRL_AVCCLowVolThresETypeDef
  * @return None
  */
#define __LL_SYSCTRL_AVCC_LowVolThres_Set(__SYSCTRL__, thres)   \
        MODIFY_REG((__SYSCTRL__)->PLCR, SYSCTRL_PLCR_AVCCLVL_Msk, (((thres) & 0x3UL) << SYSCTRL_PLCR_AVCCLVL_Pos))

/**
  * @brief  EFLASH Multi-Bit Error Falut Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_EFLASH_MultiBitErrFlt_En(__SYSCTRL__)      SET_BIT((__SYSCTRL__)->PLCR, 0x100UL)

/**
  * @brief  EFLASH Multi-Bit Error Falut Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_EFLASH_MultiBitErrFlt_Dis(__SYSCTRL__)     CLEAR_BIT((__SYSCTRL__)->PLCR, 0x100UL)

/**
  * @brief  EFLASH Lockup Falut Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_EFLASH_LockupFlt_En(__SYSCTRL__)           SET_BIT((__SYSCTRL__)->PLCR, 0x200UL)

/**
  * @brief  EFLASH Lockup Falut Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  * @deprecated This interface is no longer accessible to users
  */
#define __LL_SYSCTRL_EFLASH_LockupFlt_Dis(__SYSCTRL__)          CLEAR_BIT((__SYSCTRL__)->PLCR, 0x200UL)

/**
  * @brief  VDD Low Voltage Threshold Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  thres VDD Low Voltage Threshold @ref SYSCTRL_VDDLowVolThresETypeDef
  * @return None
  */
#define __LL_SYSCTRL_VDD_LowVolThres_Set(__SYSCTRL__, thres)    \
        MODIFY_REG((__SYSCTRL__)->PLCR, SYSCTRL_PLCR_VDDLVS_Msk, (((thres) & 0x7UL) << SYSCTRL_PLCR_VDDLVS_Pos))

/**
  * @brief  VDD Over Current Detect Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VDD_OverCurDet_En(__SYSCTRL__)             SET_BIT((__SYSCTRL__)->PLCR, SYSCTRL_PLCR_VDDOCE_Msk)

/**
  * @brief  VDD Over Current Detect Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VDD_OverCurDet_Dis(__SYSCTRL__)            CLEAR_BIT((__SYSCTRL__)->PLCR, SYSCTRL_PLCR_VDDOCE_Msk)

/**
  * @brief   Judgs is VDD Over Current Detect Enable or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 VDD Over Current Detect is Disable
  * @retval 1 VDD Over Current Detect is Enable
  */
#define __LL_SYSCTRL_Is_VDD_OverCurDet_En(__SYSCTRL__)          \
        READ_BIT_SHIFT((__SYSCTRL__)->PLCR, SYSCTRL_PLCR_VDDOCE_Msk, SYSCTRL_PLCR_VDDOCE_Pos)

/**
  * @brief  AVCC Low Voltage Detect Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AVCC_LowVolDet_En(__SYSCTRL__)             SET_BIT((__SYSCTRL__)->PLCR, SYSCTRL_PLCR_AVCCLVE_Msk)

/**
  * @brief  AVCC Low Voltage Detect Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AVCC_LowVolDet_Dis(__SYSCTRL__)            CLEAR_BIT((__SYSCTRL__)->PLCR, SYSCTRL_PLCR_AVCCLVE_Msk)

/**
  * @brief   Judgs is AVCC Low Voltage Detect Enable or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 AVCC Low Voltage Detect is Disable
  * @retval 1 AVCC Low Voltage Detect is Enable
  */
#define __LL_SYSCTRL_Is_AVCC_LowVolDet_En(__SYSCTRL__)          \
        READ_BIT_SHIFT((__SYSCTRL__)->PLCR, SYSCTRL_PLCR_AVCCLVE_Msk, SYSCTRL_PLCR_AVCCLVE_Pos)

/**
  * @brief  VCC Low Voltage Detect Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VCC_LowVolDet_En(__SYSCTRL__)              SET_BIT((__SYSCTRL__)->PLCR, SYSCTRL_PLCR_VCCLVE_Msk)

/**
  * @brief  VCC Low Voltage Detect Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VCC_LowVolDet_Dis(__SYSCTRL__)             CLEAR_BIT((__SYSCTRL__)->PLCR, SYSCTRL_PLCR_VCCLVE_Msk)

/**
  * @brief   Judgs is VCC Low Voltage Detect Enable or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 VCC Low Voltage Detect is Disable
  * @retval 1 VCC Low Voltage Detect is Enable
  */
#define __LL_SYSCTRL_Is_VCC_LowVolDet_En(__SYSCTRL__)          \
        READ_BIT_SHIFT((__SYSCTRL__)->PLCR, SYSCTRL_PLCR_VCCLVE_Msk, SYSCTRL_PLCR_VCCLVE_Pos)

/**
  * @brief  VDD Low Voltage Detect Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VDD_LowVolDet_En(__SYSCTRL__)              SET_BIT((__SYSCTRL__)->PLCR, SYSCTRL_PLCR_VDDLVE_Msk)

/**
  * @brief  VDD Low Voltage Detect Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VDD_LowVolDet_Dis(__SYSCTRL__)             CLEAR_BIT((__SYSCTRL__)->PLCR, SYSCTRL_PLCR_VDDLVE_Msk)

/**
  * @brief   Judgs is VDD Low Voltage Detect Enable or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 VDD Low Voltage Detect is Disable
  * @retval 1 VDD Low Voltage Detect is Enable
  */
#define __LL_SYSCTRL_Is_VDD_LowVolDet_En(__SYSCTRL__)          \
        READ_BIT_SHIFT((__SYSCTRL__)->PLCR, SYSCTRL_PLCR_VDDLVE_Msk, SYSCTRL_PLCR_VDDLVE_Pos)


/**
  * @brief  VDD Over Current Braking Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VDD_OverCurBrk_En(__SYSCTRL__)             SET_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_VDDOCBE_Msk)

/**
  * @brief  VDD Over Current Braking Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VDD_OverCurBrk_Dis(__SYSCTRL__)            CLEAR_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_VDDOCBE_Msk)

/**
  * @brief  AVCC Low Voltage Braking Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AVCC_LowVolBrk_En(__SYSCTRL__)             SET_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_AVCCLVBE_Msk)

/**
  * @brief  AVCC Low Voltage Braking Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AVCC_LowVolBrk_Dis(__SYSCTRL__)            CLEAR_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_AVCCLVBE_Msk)

/**
  * @brief  VCC Low Voltage Braking Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VCC_LowVolBrk_En(__SYSCTRL__)              SET_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_VCCLVBE_Msk)

/**
  * @brief  VCC Low Voltage Braking Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VCC_LowVolBrk_Dis(__SYSCTRL__)             CLEAR_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_VCCLVBE_Msk)

/**
  * @brief  VDD Low Voltage Braking Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VDD_LowVolBrk_En(__SYSCTRL__)              SET_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_VDDLVBE_Msk)

/**
  * @brief  VDD Low Voltage Braking Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VDD_LowVolBrk_Dis(__SYSCTRL__)             CLEAR_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_VDDLVBE_Msk)

/**
  * @brief  VDD Over Current Reset Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VDD_OverCurRst_En(__SYSCTRL__)             SET_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_VDDOCRE_Msk)

/**
  * @brief  VDD Over Current Reset Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VDD_OverCurRst_Dis(__SYSCTRL__)            CLEAR_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_VDDOCRE_Msk)

/**
  * @brief  AVCC Low Voltage Reset Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AVCC_LowVolRst_En(__SYSCTRL__)             SET_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_AVCCLVRE_Msk)

/**
  * @brief  AVCC Low Voltage Reset Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AVCC_LowVolRst_Dis(__SYSCTRL__)            CLEAR_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_AVCCLVRE_Msk)

/**
  * @brief  VCC Low Voltage Reset Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VCC_LowVolRst_En(__SYSCTRL__)              SET_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_VCCLVRE_Msk)

/**
  * @brief  VCC Low Voltage Reset Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VCC_LowVolRst_Dis(__SYSCTRL__)             CLEAR_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_VCCLVRE_Msk)

/**
  * @brief  VDD Low Voltage Reset Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VDD_LowVolRst_En(__SYSCTRL__)              SET_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_VDDLVRE_Msk)

/**
  * @brief  VDD Low Voltage Reset Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VDD_LowVolRst_Dis(__SYSCTRL__)             CLEAR_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_VDDLVRE_Msk)

/**
  * @brief  VDD Over Current Interrupt Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VDD_OverCurInt_En(__SYSCTRL__)             SET_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_VDDOCIE_Msk)

/**
  * @brief  VDD Over Current Interrupt Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VDD_OverCurInt_Dis(__SYSCTRL__)            CLEAR_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_VDDOCIE_Msk)

/**
  * @brief  AVCC Low Voltage Interrupt Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AVCC_LowVolInt_En(__SYSCTRL__)             SET_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_AVCCLVIE_Msk)

/**
  * @brief  AVCC Low Voltage Interrupt Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_AVCC_LowVolInt_Dis(__SYSCTRL__)            CLEAR_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_AVCCLVIE_Msk)

/**
  * @brief  VCC Low Voltage Interrupt Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VCC_LowVolInt_En(__SYSCTRL__)              SET_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_VCCLVIE_Msk)

/**
  * @brief  VCC Low Voltage Interrupt Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VCC_LowVolInt_Dis(__SYSCTRL__)             CLEAR_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_VCCLVIE_Msk)

/**
  * @brief  VDD Low Voltage Interrupt Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VDD_LowVolInt_En(__SYSCTRL__)              SET_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_VDDLVIE_Msk)

/**
  * @brief  VDD Low Voltage Interrupt Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VDD_LowVolInt_Dis(__SYSCTRL__)             CLEAR_BIT((__SYSCTRL__)->PECR, SYSCTRL_PECR_VDDLVIE_Msk)


/**
  * @brief  Judge is VDD Over Current or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 VDD isn't Over Current
  * @retval 1 VDD is Over Current
  */
#define __LL_SYSCTRL_IsVDDOverCur(__SYSCTRL__)                  \
        READ_BIT_SHIFT((__SYSCTRL__)->PSR, SYSCTRL_PSR_VDDOCS_Msk, SYSCTRL_PSR_VDDOCS_Pos)

/**
  * @brief  Judge is AVCC Low Voltage or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 AVCC isn't Low Voltage
  * @retval 1 AVCC is Low Voltage
  */
#define __LL_SYSCTRL_IsAVCCLowVol(__SYSCTRL__)                  \
        READ_BIT_SHIFT((__SYSCTRL__)->PSR, SYSCTRL_PSR_AVCCLVS_Msk, SYSCTRL_PSR_AVCCLVS_Pos)

/**
  * @brief  Judge is VCC Low Voltage or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 VCC isn't Low Voltage
  * @retval 1 VCC is Low Voltage
  */
#define __LL_SYSCTRL_IsVCCLowVol(__SYSCTRL__)                   \
        READ_BIT_SHIFT((__SYSCTRL__)->PSR, SYSCTRL_PSR_VCCLVS_Msk, SYSCTRL_PSR_VCCLVS_Pos)

/**
  * @brief  Judge is VDD Low Voltage or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 VDD isn't Low Voltage
  * @retval 1 VDD is Low Voltage
  */
#define __LL_SYSCTRL_IsVDDLowVol(__SYSCTRL__)                   \
        READ_BIT_SHIFT((__SYSCTRL__)->PSR, SYSCTRL_PSR_VDDLVS_Msk, SYSCTRL_PSR_VDDLVS_Pos)


/**
  * @brief  SYSCTRL Chip ID Get
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval Chip ID - 16bit
  */
#define __LL_SYSCTRL_ChipID_Get(__SYSCTRL__)    READ_BIT_SHIFT((__SYSCTRL__)->CIDR, SYSCTRL_CIDR_CID_Msk, SYSCTRL_CIDR_CID_Pos)

/**
  * @brief  SYSCTRL Chip DCN Get
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval Chip DCN - 8bit
  */
#define __LL_SYSCTRL_ChipDCN_Get(__SYSCTRL__)   READ_BIT_SHIFT((__SYSCTRL__)->CIDR, SYSCTRL_CIDR_DCN_Msk, SYSCTRL_CIDR_DCN_Pos)


/**
  * @brief  SYSCTRL System Register Write Unlock
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_SysRegWrite_Unlock(__SYSCTRL__)            WRITE_REG((__SYSCTRL__)->KEYR, 0x87e4)

/**
  * @brief  SYSCTRL System Register Write Lock
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_SysRegWrite_Lock(__SYSCTRL__)              WRITE_REG((__SYSCTRL__)->KEYR, SYSCTRL_KEYR_KST0_Msk)

/**
  * @brief  SYSCTRL Special Register Write Unlock
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_SpRegWrite_Unlock(__SYSCTRL__)             \
        do {                                                    \
            WRITE_REG((__SYSCTRL__)->KEYR, 0x8a3d);             \
            WRITE_REG((__SYSCTRL__)->KEYR, 0x19ec);             \
        } while (0)

/**
  * @brief  SYSCTRL Special Register Write Lock
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_SpRegWrite_Lock(__SYSCTRL__)               WRITE_REG((__SYSCTRL__)->KEYR, SYSCTRL_KEYR_KST1_Msk)


/**
  * @brief  SYSCTRL UID0 Get
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval UID0
  */
#define __LL_SYSCTRL_UID0_Get(__SYSCTRL__)                      READ_REG((__SYSCTRL__)->UID0)


/**
  * @brief  SYSCTRL UID1 Get
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval UID1
  */
#define __LL_SYSCTRL_UID1_Get(__SYSCTRL__)                      READ_REG((__SYSCTRL__)->UID1)


/**
  * @brief  SYSCTRL UID2 Get
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval UID2
  */
#define __LL_SYSCTRL_UID2_Get(__SYSCTRL__)                      READ_REG((__SYSCTRL__)->UID2)


/**
  * @brief  SYSCTRL UID3 Get
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval UID3
  */
#define __LL_SYSCTRL_UID3_Get(__SYSCTRL__)                      READ_REG((__SYSCTRL__)->UID3)

/**
  * @brief  SYSCTRL EFLASH Size Get
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval EFLASH Size in KByte unit
  */
#define __LL_SYSCTRL_EFlashSize_Get(__SYSCTRL__)                READ_BIT_SHIFT((__SYSCTRL__)->UID3, 0xffff0000UL, 16)


/**
  * @brief  SYSCTRL VREFBUF Output Voltage Status Get
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 VREFBUF Output is building
  * @retval 1 VREFBUF Output is done
  */
#define __LL_SYSCTRL_VREFBUFOutputVolSta_Get(__SYSCTRL__)        \
        READ_BIT_SHIFT((__SYSCTRL__)->ATCR, SYSCTRL_ATCR_VBFRDY_Msk, SYSCTRL_ATCR_VBFRDY_Pos)

/**
  * @brief  SYSCTRL internal BGR voltage Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  vol BGR voltage
  * @return None
  */
#define __LL_SYSCTRL_IntBGRVol_Set(__SYSCTRL__, vol)            \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) ?             \
        MODIFY_REG((__SYSCTRL__)->ATCR, 0x7ff00000UL, ((vol) & 0x7ff) << 20UL) : \
        MODIFY_REG((__SYSCTRL__)->ATCR, 0xfff00000UL, ((vol) & 0xfff) << 20UL))
        

/**
  * @brief  SYSCTRL VREFBUF Current Limiting Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VREFBUFCurLimiting_En(__SYSCTRL__)         SET_BIT((__SYSCTRL__)->ATCR, SYSCTRL_ATCR_VBFCL_Msk)

/**
  * @brief  SYSCTRL VREFBUF Current Limiting Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VREFBUFCurLimiting_Dis(__SYSCTRL__)        CLEAR_BIT((__SYSCTRL__)->ATCR, SYSCTRL_ATCR_VBFCL_Msk)

/**
  * @brief  Judge is SYSCTRL VREFBUF Current Limiting Enable or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 Current Limiting is disable
  * @retval 1 Current Limiting is enable
  */
#define __LL_SYSCTRL_IsVREFBUFCurLimitingEn(__SYSCTRL__)        \
        READ_BIT_SHIFT((__SYSCTRL__)->ATCR, SYSCTRL_ATCR_VBFCL_Msk, SYSCTRL_ATCR_VBFCL_Pos)

/**
  * @brief  SYSCTRL VREFBUF Trim Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  trim VREFBUF Trim
  * @return None
  */
#define __LL_SYSCTRL_VREFBUFTrim_Set(__SYSCTRL__, trim)         \
        MODIFY_REG((__SYSCTRL__)->ATCR, SYSCTRL_ATCR_VBFTRIM_Msk, ((trim) & 0x1f) << SYSCTRL_ATCR_VBFTRIM_Pos)

/**
  * @brief  SYSCTRL VREFBUF Output Voltage Set
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  vol VREFBUF Output Voltage
  * @return None
  */
#define __LL_SYSCTRL_VREFBUFOutputVol_Set(__SYSCTRL__, vol)     \
        MODIFY_REG((__SYSCTRL__)->ATCR, SYSCTRL_ATCR_VBFSEL_Msk, ((vol) & 0x1) << SYSCTRL_ATCR_VBFSEL_Pos)

/**
  * @brief  SYSCTRL VREFBUF Enable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VREFBUF_En(__SYSCTRL__)                    SET_BIT((__SYSCTRL__)->ATCR, SYSCTRL_ATCR_VBFEN_Msk)

/**
  * @brief  SYSCTRL VREFBUF Disable
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return None
  */
#define __LL_SYSCTRL_VREFBUF_Dis(__SYSCTRL__)                   CLEAR_BIT((__SYSCTRL__)->ATCR, SYSCTRL_ATCR_VBFEN_Msk)

/**
  * @brief  SYSCTRL REF Reference Current Calibration
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  cur REF Reference Current
  * @return None
  */
#define __LL_SYSCTRL_REFCurrent_Set(__SYSCTRL__, cur)           \
        MODIFY_REG((__SYSCTRL__)->ATCR, SYSCTRL_ATCR_REFITRIM_Msk, ((cur) & 0x3f) << SYSCTRL_ATCR_REFITRIM_Pos)

/**
  * @brief  SYSCTRL REF Reference Voltage Calibration
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @param  vol REF Reference Voltage
  * @return None
  */
#define __LL_SYSCTRL_REFVoltage_Set(__SYSCTRL__, vol)           \
        MODIFY_REG((__SYSCTRL__)->ATCR, SYSCTRL_ATCR_REFVTRIM_Msk, ((vol) & 0x1f) << SYSCTRL_ATCR_REFVTRIM_Pos)


/**
  * @brief  SYSCTRL RC8M Real Value Get
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return RC8M Real Value
  */
#define __LL_SYSCTRL_RC8M_Real_Get(__SYSCTRL__)                 \
        READ_BIT_SHIFT((__SYSCTRL__)->FCR2, SYSCTRL_FCR2_RC8M_Msk, SYSCTRL_FCR2_RC8M_Pos)

/**
  * @brief  Judge is SYSCTRL ADC Conversion Phase Clock Enable or not
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @retval 0 ADC Conversion Phase Clock isn't Enable
  * @retval 1 ADC Conversion Phase Clock is Enable
  */
#define __LL_SYSCTRL_IsADCConvPhaseEn(__SYSCTRL__)              \
        READ_BIT_SHIFT((__SYSCTRL__)->FCR2, SYSCTRL_FCR2_ADCPVEN_Msk, SYSCTRL_FCR2_ADCPVEN_Pos)

/**
  * @brief  SYSCTRL RC8M PLL0 Band Value Get
  * @note   This band value is only used for typical scene which PLL0 analog output 400M
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return RC8M PLL0 Band Value
  */
#define __LL_SYSCTRL_RC8M_PLL0BandValue_Get(__SYSCTRL__)        \
        READ_BIT_SHIFT((__SYSCTRL__)->FCR2, SYSCTRL_FCR2_PLL0BANDy_Msk, SYSCTRL_FCR2_PLL0BANDy_Pos)


/**
  * @brief  SYSCTRL XOSC PLL0 Band Value Get
  * @note   This band value is only used for typical scene which PLL0 analog output 400M
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return XOSC PLL0 Band Value
  */
#define __LL_SYSCTRL_XOSC_PLL0BandValue_Get(__SYSCTRL__)        \
        READ_BIT_SHIFT((__SYSCTRL__)->FCR3, SYSCTRL_FCR3_PLL0BAND_Msk, SYSCTRL_FCR3_PLL0BAND_Pos)

/**
  * @brief  SYSCTRL RC32K Real Value Get
  * @param  __SYSCTRL__ Specifies SYSCTRL peripheral
  * @return RC32K Real Value
  */
#define __LL_SYSCTRL_RC32K_Real_Get(__SYSCTRL__)                \
        READ_BIT_SHIFT((__SYSCTRL__)->FCR5, SYSCTRL_FCR5_RC32K_Msk, SYSCTRL_FCR5_RC32K_Pos)

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup SYSCTRL_LL_Exported_Types SYSCTRL LL Exported Types
  * @brief    SYSCTRL LL Exported Types
  * @{
  */

/**
  * @brief SYSCTRL VDD Voltage Definition
  */
typedef enum {
    SYSCTRL_VDD_VOL_0V88 = 0,               /*!< VDD Voltage 0.88V  */
    SYSCTRL_VDD_VOL_0V92,                   /*!< VDD Voltage 0.92V  */
    SYSCTRL_VDD_VOL_0V96,                   /*!< VDD Voltage 0.96V  */
    SYSCTRL_VDD_VOL_1V,                     /*!< VDD Voltage 1V     */
    SYSCTRL_VDD_VOL_1V04,                   /*!< VDD Voltage 1.04V  */
    SYSCTRL_VDD_VOL_1V08,                   /*!< VDD Voltage 1.08V  */
    SYSCTRL_VDD_VOL_1V12,                   /*!< VDD Voltage 1.12V  */
    SYSCTRL_VDD_VOL_1V16,                   /*!< VDD Voltage 1.16V  */
    SYSCTRL_VDD_VOL_1V2,                    /*!< VDD Voltage 1.20V  */
    SYSCTRL_VDD_VOL_1V24,                   /*!< VDD Voltage 1.24V  */
    SYSCTRL_VDD_VOL_1V28,                   /*!< VDD Voltage 1.28V  */
    SYSCTRL_VDD_VOL_1V32,                   /*!< VDD Voltage 1.32V  */
    SYSCTRL_VDD_VOL_1V36,                   /*!< VDD Voltage 1.36V  */
    SYSCTRL_VDD_VOL_1V4,                    /*!< VDD Voltage 1.40V  */
    SYSCTRL_VDD_VOL_1V44,                   /*!< VDD Voltage 1.44V  */
    SYSCTRL_VDD_VOL_1V48,                   /*!< VDD Voltage 1.48V  */
} SYSCTRL_VDDVolETypeDef;

/**
  * @brief SYSCTRL AVDD Voltage Definition
  */
typedef enum {
    SYSCTRL_AVDD_VOL_1V = 0,                /*!< AVDD Voltage 1V    */
    SYSCTRL_AVDD_VOL_1V1,                   /*!< AVDD Voltage 1.1V  */
    SYSCTRL_AVDD_VOL_1V2,                   /*!< AVDD Voltage 1.2V  */
    SYSCTRL_AVDD_VOL_1V3,                   /*!< AVDD Voltage 1.3V  */
} SYSCTRL_AVDDVolETypeDef;

/**
  * @brief SYSCTRL VDD OverCurrent Threshold Definition
  */
typedef enum {
    SYSCTRL_VDD_OVER_CUR_THRES_150mA = 0,   /*!< VDD OverCurrent Threshold 150mA    */
    SYSCTRL_VDD_OVER_CUR_THRES_175mA,       /*!< VDD OverCurrent Threshold 175mA    */
    SYSCTRL_VDD_OVER_CUR_THRES_200mA,       /*!< VDD OverCurrent Threshold 200mA    */
    SYSCTRL_VDD_OVER_CUR_THRES_225mA,       /*!< VDD OverCurrent Threshold 225mA    */
} SYSCTRL_VDDOverCurThresETypeDef;

/**
  * @brief SYSCTRL AVCC LowVoltage Threshold Definition
  */
typedef enum {
    SYSCTRL_AVCC_LOW_VOL_THRES_2V55 = 0,    /*!< AVCC LowVoltage Threshold 2.55V    */
    SYSCTRL_AVCC_LOW_VOL_THRES_2V7,         /*!< AVCC LowVoltage Threshold 2.7V     */
    SYSCTRL_AVCC_LOW_VOL_THRES_2V85,        /*!< AVCC LowVoltage Threshold 2.85V    */
    SYSCTRL_AVCC_LOW_VOL_THRES_3V,          /*!< AVCC LowVoltage Threshold 3V       */
} SYSCTRL_AVCCLowVolThresETypeDef;

/**
  * @brief SYSCTRL VDD LowVoltage Threshold Definition
  */
typedef enum {
    SYSCTRL_VDD_LOW_VOL_THRES_0V75 = 0,     /*!< VDD LowVoltage Threshold 0.75V     */
    SYSCTRL_VDD_LOW_VOL_THRES_0V8,          /*!< VDD LowVoltage Threshold 0.8V      */
    SYSCTRL_VDD_LOW_VOL_THRES_0V85,         /*!< VDD LowVoltage Threshold 0.85V     */
    SYSCTRL_VDD_LOW_VOL_THRES_0V9,          /*!< VDD LowVoltage Threshold 0.9V      */
    SYSCTRL_VDD_LOW_VOL_THRES_0V95,         /*!< VDD LowVoltage Threshold 0.95V     */
    SYSCTRL_VDD_LOW_VOL_THRES_1V,           /*!< VDD LowVoltage Threshold 1.0V      */
    SYSCTRL_VDD_LOW_VOL_THRES_1V05,         /*!< VDD LowVoltage Threshold 1.05V     */
    SYSCTRL_VDD_LOW_VOL_THRES_1V1,          /*!< VDD LowVoltage Threshold 1.1V      */
} SYSCTRL_VDDLowVolThresETypeDef;

/**
  * @brief SYSCTRL VREFBUF Output Voltage Definition
  */
typedef enum {
    SYSCTRL_VREFBUF_VOL_2V9 = 0,            /* VREFBUF Output Voltage 2.9V  */
    SYSCTRL_VREFBUF_VOL_2V5,                /* VREFBUF Output Voltage 2.5V  */
} SYSCTRL_VREFBUFVolETypeDef;

/**
  * @brief Flash Double Bank Mapping Definition
  */
typedef enum {
    SYSCTRL_FLASH_BANK_MAPPING_0 = 0,       /* Flash Bank Mapping type 0 */
    SYSCTRL_FLASH_BANK_MAPPING_1,           /* Flash Bank Mapping type 1 */
} SYSCTRL_FlashBankMappingETypeDef;


/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup SYSCTRL_LL_Exported_Functions
  * @{
  */

/** @addtogroup SYSCTRL_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_SYSCTRL_Init(SYSCTRL_TypeDef *Instance);
LL_StatusETypeDef LL_SYSCTRL_DeInit(SYSCTRL_TypeDef *Instance);
void LL_SYSCTRL_MspInit(SYSCTRL_TypeDef *Instance);
void LL_SYSCTRL_MspDeInit(SYSCTRL_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup SYSCTRL_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_SYSCTRL_IRQHandler(SYSCTRL_TypeDef *Instance);

void LL_SYSCTRL_VDDOverCurCallback(SYSCTRL_TypeDef *Instance);
void LL_SYSCTRL_VDDLowVolCallback(SYSCTRL_TypeDef *Instance);
void LL_SYSCTRL_VCCLowVolCallback(SYSCTRL_TypeDef *Instance);
void LL_SYSCTRL_AVCCLowVolCallback(SYSCTRL_TypeDef *Instance);
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

#endif /* _TAE32G58XX_LL_SYSCTRL_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

