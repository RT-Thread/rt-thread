/**
  ******************************************************************************
  * @file    tae32f53xx_ll_def.h
  * @author  MCD Application Team
  * @brief   This file contains LL common defines, enumeration, macros and
  *          structures definitions.
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
#ifndef _TAE32F53XX_LL_DEF_H_
#define _TAE32F53XX_LL_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <stddef.h>
#include "tae32f53xx.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @defgroup DEFINE_LL DEFINE LL
  * @brief    DEFINE LL
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup DEFINE_LL_Exported_Constants DEFINE LL Exported Constants
  * @brief    DEFINE LL Exported Constants
  * @{
  */

/**
  * @brief LL wait forever time definition
  */
#define LL_WAIT_FOREVER                     0xFFFFFFFFUL

/**
  * @brief LL wait max delay time definition
  */
#define LL_MAX_DELAY                        (LL_WAIT_FOREVER - 1U)

/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup DEFINE_LL_Exported_Types DEFINE LL Exported Types
  * @brief    DEFINE LL Exported Types
  * @{
  */

/**
  * @brief  LL Status type definition
  */
typedef enum {
    LL_OK       = 0x00U,    /*! LL status OK                    */
    LL_ERROR    = 0x01U,    /*! LL status ERROR                 */
    LL_BUSY     = 0x02U,    /*! LL status BUSY                  */
    LL_TIMEOUT  = 0x03U,    /*! LL status TIMEOUT               */
    LL_FAILED   = 0x04U,    /*! LL status FAILED                */
} LL_StatusETypeDef;

/**
  * @brief LL Flag status type definition
  */
typedef enum {
    RESET = 0,              /*!< LL flag status RESET           */
    SET   = !RESET,         /*!< LL flag status SET             */
} LL_FlagStatusETypeDef;

/**
  * @brief LL Functional status type definition
  */
typedef enum {
    DISABLE = 0,            /*!< LL functional status DISABLE   */
    ENABLE  = !DISABLE,     /*!< LL functional status ENABLE    */
} LL_FuncStatusETypeDef;

/**
  * @brief LL Error status type definiton
  */
typedef enum {
    SUCCESS = 0U,           /*!< LL error status SUCCESS        */
    ERROR   = !SUCCESS,     /*!< LL error status ERROR          */
} LL_ErrStatusETypeDef;

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup DEFINE_LL_Exported_Macros DEFINE LL Exported Macros
  * @brief    DEFINE LL Exported Macros
  * @{
  */

/* Compiler ALIAS and WEAK attribute definition */
#if   defined (__CC_ARM)                                        /*!< AC5 Compiler */
#define __ALIAS_FUNC(FUNC)                      __attribute__ ((weak, alias(#FUNC)))
#define __WEAK_ALIAS_FUNC(FUNC, FUNC_ALIAS)     void FUNC(void) __attribute__ ((weak, alias(#FUNC_ALIAS)));
#elif defined (__ICCARM__)                                      /*!< IAR Compiler */
#define __WEAK_ALIAS_FUNC(FUNC, FUNC_ALIAS)     void FUNC(void);_Pragma(_STRINGIFY(_WEAK_ALIAS_FUNC(FUNC, FUNC_ALIAS)))
#define _WEAK_ALIAS_FUNC(FUNC, FUNC_ALIAS)      weak WEAK_ALIAS_FUNC(FUNC, FUNC_ALIAS)
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)  /*!< AC6 Compiler */
#define __ALIAS_FUNC(FUNC)                      __attribute__ ((weak, alias(#FUNC)))
#define __WEAK_ALIAS_FUNC(FUNC, FUNC_ALIAS)     void FUNC(void) __attribute__ ((weak, alias(#FUNC_ALIAS)));
#elif defined (__GNUC__)                                        /*!< GCC Compiler */
#define __ALIAS_FUNC(FUNC)                      __attribute__ ((weak, alias(#FUNC)))
#define __WEAK_ALIAS_FUNC(FUNC, FUNC_ALIAS)     void FUNC(void) __attribute__ ((weak, alias(#FUNC_ALIAS)));
#else
#error Not supported compiler type
#endif


/* Macro to get variable aligned on 4-bytes, for __ICCARM__ the directive "#pragma data_alignment=4" must be used instead */
/* Compiler aligned on 4-bytes attribute definition */
#if defined ( __GNUC__ ) && !defined (__CC_ARM)         /* GNU Compiler */
#ifndef __ALIGN_END
#define __ALIGN_END                 __attribute__ ((aligned (4)))
#endif

#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN
#endif

#else

#ifndef __ALIGN_END
#define __ALIGN_END
#endif

#ifndef __ALIGN_BEGIN
#if defined   (__CC_ARM)                        /* ARM Compiler */
#define __ALIGN_BEGIN           __align(4)
#elif defined (__ICCARM__)                      /* IAR Compiler */
#define __ALIGN_BEGIN
#endif
#endif
#endif


/* Compiler __NOINLINE attribute definition */
#if   defined (__CC_ARM) || defined (__GNUC__)          /* ARM & GNUCompiler */
#define __NOINLINE                      __attribute__ ( (noinline) )
#elif defined (__ICCARM__)                              /* ICCARM Compiler */
#define __NOINLINE                      _Pragma("optimize = no_inline")
#endif


/* Compiler misc attribute definition */
#if   defined (__CC_ARM)                                        /*!< AC5 Compiler */
#define __NO_INIT                       __attribute__((zero_init))
#define __AT(n)                         __attribute__((at(n)))
#define __SECTION(SECT)                 __attribute__((section(#SECT)))
#elif defined (__ICCARM__)                                      /*!< IAR Compiler */
#define __NO_INIT                       __no_init
#define __AT(n)                         @(n)
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)  /*!< AC6 Compiler */
#define __NO_INIT
#define __AT(n)                         __attribute__ ((section(".ARM.__at_"#n)))
#define __SECTION(SECT)                 __attribute__((section(#SECT)))
#elif defined (__GNUC__)                                        /*!< GCC Compiler */
#define __NO_INIT                       __attribute__((zero_init))
#define __AT(n)
#define __SECTION(SECT)                 __attribute__((section(#SECT)))
#endif


/**
  * @brief  Bit left shift definition
  * @param  pos left shift position
  * @return Bit left shift value
  */
#define BIT(pos)                            (1U << (pos))

/**
  * @brief  Set bit definition
  * @param  REG register
  * @param  BIT Bit to set
  * @return None
  */
#define SET_BIT(REG, BIT)                   ((REG) |= (BIT))

/**
  * @brief  Clear bit definition
  * @param  REG register
  * @param  BIT Bit to clear
  * @return None
  */
#define CLEAR_BIT(REG, BIT)                 ((REG) &= ~(BIT))

/**
  * @brief  Read bit definition
  * @param  REG register
  * @param  BIT Bit to read
  * @return None
  */
#define READ_BIT(REG, BIT)                  ((REG) & (BIT))

/**
  * @brief  Clear register definiton
  * @param  REG register
  * @return None
  */
#define CLEAR_REG(REG)                      ((REG) = (0x0))

/**
  * @brief  Write register definiton
  * @param  REG register
  * @param  VAL write value
  * @return None
  */
#define WRITE_REG(REG, VAL)                 ((REG) = (VAL))

/**
  * @brief  Read register definition
  * @param  REG register
  * @return None
  */
#define READ_REG(REG)                       ((REG))

/**
  * @brief  Modify register definition
  * @param  REG register
  * @param  CLEARMASK clear mask
  * @param  SETMASK set mask
  * @return None
  */
#define MODIFY_REG(REG, CLEARMASK, SETMASK) WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

/**
  * @brief  Position value definition
  * @param  VAL value
  * @return None
  */
#define POSITION_VAL(VAL)                   (__CLZ(__RBIT(VAL)))



/**
  * @brief  To avoid gcc/g++ warnings
  * @param  X avoid warning param
  * @return None
  */
#define LL_UNUSED(X)                        (void)X

/**
  * @brief  Macro for counting the element number of an array
  * @param  a Array to be Counted
  * @return size of Array
  */
#define ARRAY_SIZE(a)                       (sizeof((a)) / sizeof((a)[0]))

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
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


#endif /* _TAE32F53XX_LL_DEF_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

