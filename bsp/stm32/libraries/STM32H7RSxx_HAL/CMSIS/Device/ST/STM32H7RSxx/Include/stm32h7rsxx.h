/**
  ******************************************************************************
  * @file    stm32h7rsxx.h
  * @author  MCD Application Team
  * @brief   CMSIS STM32H7RSxx Device Peripheral Access Layer Header File.
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *           - Configuration section that allows to select:
  *              - The STM32H7RSxx device used in the target application
  *              - To use or not the peripherals drivers in application code(i.e.
  *                code will be based on direct access to peripherals registers
  *                rather than drivers API), this option is controlled by
  *                "#define USE_HAL_DRIVER"
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32h7rsxx
  * @{
  */

#ifndef STM32H7RSxx_H
#define STM32H7RSxx_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/** @addtogroup Library_configuration_section
  * @{
  */

/**
  * @brief STM32 Family
  */
#if !defined (STM32H7RS)
#define STM32H7RS
#endif /* STM32H7RS */

/* Uncomment the line below according to the target STM32H7RS device used in your
   application
  */

#if !defined (STM32H7R7xx) && !defined (STM32H7R3xx) && !defined (STM32H7S3xx) && !defined (STM32H7S7xx)
  /* #define STM32H7R3xx */   /*!< STM32H7R3xx Devices */
  /* #define STM32H7R7xx */   /*!< STM32H7R7xx Devices */
  /* #define STM32H7S3xx */   /*!< STM32H7S3xx Devices */
  /* #define STM32H7S7xx */   /*!< STM32H7S7xx Devices */
#endif

/*  Tip: To avoid modifying this file each time you need to switch between these
        devices, you can define the device in your toolchain compiler preprocessor.
  */
#if !defined  (USE_HAL_DRIVER)
/**
 * @brief Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will
   be based on direct access to peripherals registers
   */
  /*#define USE_HAL_DRIVER */
#endif /* USE_HAL_DRIVER */

/**
  * @brief CMSIS Device version number
  */
#define __STM32H7RS_CMSIS_VERSION_MAIN   (0x01U) /*!< [31:24] main version */
#define __STM32H7RS_CMSIS_VERSION_SUB1   (0x00U) /*!< [23:16] sub1 version */
#define __STM32H7RS_CMSIS_VERSION_SUB2   (0x00U) /*!< [15:8]  sub2 version */
#define __STM32H7RS_CMSIS_VERSION_RC     (0x00U) /*!< [7:0]  release candidate */
#define __STM32H7RS_CMSIS_VERSION      ((__STM32H7RS_CMSIS_VERSION_MAIN << 24U)\
                                       |(__STM32H7RS_CMSIS_VERSION_SUB1 << 16U)\
                                       |(__STM32H7RS_CMSIS_VERSION_SUB2 << 8U )\
                                       |(__STM32H7RS_CMSIS_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Device_Included
  * @{
  */

#if defined(STM32H7R3xx)
  #include "stm32h7r3xx.h"
#elif defined(STM32H7R7xx)
  #include "stm32h7r7xx.h"
#elif defined(STM32H7S3xx)
  #include "stm32h7s3xx.h"
#elif defined(STM32H7S7xx)
  #include "stm32h7s7xx.h"
#else
 #error "Please select first the target STM32H7RSxx device used in your application (in stm32h7rsxx.h file)"
#endif

/**
  * @}
  */

/** @addtogroup Exported_types
  * @{
  */
typedef enum
{
  RESET = 0,
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum
{
  DISABLE = 0,
  ENABLE = !DISABLE
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum
{
  SUCCESS = 0,
  ERROR = !SUCCESS
} ErrorStatus;

/**
  * @}
  */


/** @addtogroup Exported_macros
  * @{
  */
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL)))

/* Use of CMSIS compiler intrinsics for register exclusive access */
/* Atomic 32-bit register access macro to set one or several bits */
#define ATOMIC_SET_BIT(REG, BIT)                             \
  do {                                                       \
    uint32_t val;                                            \
    do {                                                     \
      val = __LDREXW((__IO uint32_t *)&(REG)) | (BIT);       \
    } while ((__STREXW(val,(__IO uint32_t *)&(REG))) != 0U); \
  } while(0)

/* Atomic 32-bit register access macro to clear one or several bits */
#define ATOMIC_CLEAR_BIT(REG, BIT)                           \
  do {                                                       \
    uint32_t val;                                            \
    do {                                                     \
      val = __LDREXW((__IO uint32_t *)&(REG)) & ~(BIT);      \
    } while ((__STREXW(val,(__IO uint32_t *)&(REG))) != 0U); \
  } while(0)

/* Atomic 32-bit register access macro to clear and set one or several bits */
#define ATOMIC_MODIFY_REG(REG, CLEARMSK, SETMASK)                          \
  do {                                                                     \
    uint32_t val;                                                          \
    do {                                                                   \
      val = (__LDREXW((__IO uint32_t *)&(REG)) & ~(CLEARMSK)) | (SETMASK); \
    } while ((__STREXW(val,(__IO uint32_t *)&(REG))) != 0U);               \
  } while(0)

/* Atomic 16-bit register access macro to set one or several bits */
#define ATOMIC_SETH_BIT(REG, BIT)                            \
  do {                                                       \
    uint16_t val;                                            \
    do {                                                     \
      val = __LDREXH((__IO uint16_t *)&(REG)) | (BIT);       \
    } while ((__STREXH(val,(__IO uint16_t *)&(REG))) != 0U); \
  } while(0)

/* Atomic 16-bit register access macro to clear one or several bits */
#define ATOMIC_CLEARH_BIT(REG, BIT)                          \
  do {                                                       \
    uint16_t val;                                            \
    do {                                                     \
      val = __LDREXH((__IO uint16_t *)&(REG)) & ~(BIT);      \
    } while ((__STREXH(val,(__IO uint16_t *)&(REG))) != 0U); \
  } while(0)

/* Atomic 16-bit register access macro to clear and set one or several bits */
#define ATOMIC_MODIFYH_REG(REG, CLEARMSK, SETMASK)                         \
  do {                                                                     \
    uint16_t val;                                                          \
    do {                                                                   \
      val = (__LDREXH((__IO uint16_t *)&(REG)) & ~(CLEARMSK)) | (SETMASK); \
    } while ((__STREXH(val,(__IO uint16_t *)&(REG))) != 0U);               \
  } while(0)

/**
  * @}
  */

#if defined (USE_HAL_DRIVER)
 #include "stm32h7rsxx_hal.h"
#endif /* USE_HAL_DRIVER */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7RSxx_H */
/**
  * @}
  */

/**
  * @}
  */
