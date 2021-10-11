/**
  ******************************************************************************
  * @file    stm32l1xx.h
  * @author  MCD Application Team
  * @brief   CMSIS STM32L1xx Device Peripheral Access Layer Header File. 
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *            - Configuration section that allows to select:
  *              - The STM32L1xx device used in the target application
  *              - To use or not the peripheral’s drivers in application code(i.e. 
  *                code will be based on direct access to peripheral’s registers 
  *                rather than drivers API), this option is controlled by 
  *                "#define USE_HAL_DRIVER"
  *  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32l1xx
  * @{
  */
    
#ifndef __STM32L1XX_H
#define __STM32L1XX_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
  
/** @addtogroup Library_configuration_section
  * @{
  */

/**
  * @brief STM32 Family
  */
#if !defined (STM32L1)
#define STM32L1
#endif /* STM32L1 */


/* Uncomment the line below according to the target STM32L device used in your 
   application 
  */

#if !defined (STM32L100xB) && !defined (STM32L100xBA) && !defined (STM32L100xC) && \
    !defined (STM32L151xB) && !defined (STM32L151xBA) && !defined (STM32L151xC) && !defined (STM32L151xCA) && !defined (STM32L151xD) && !defined (STM32L151xDX) && !defined (STM32L151xE) && \
    !defined (STM32L152xB) && !defined (STM32L152xBA) && !defined (STM32L152xC) && !defined (STM32L152xCA) && !defined (STM32L152xD) && !defined (STM32L152xDX) && !defined (STM32L152xE) && \
    !defined (STM32L162xC) && !defined (STM32L162xCA) && !defined (STM32L162xD) && !defined (STM32L162xDX) && !defined (STM32L162xE)
  /* #define STM32L100xB  */   /*!< STM32L100C6, STM32L100R and STM32L100RB Devices */
  /* #define STM32L100xBA */   /*!< STM32L100C6-A, STM32L100R8-A and STM32L100RB-A Devices */
  /* #define STM32L100xC  */   /*!< STM32L100RC Devices */
  /* #define STM32L151xB  */   /*!< STM32L151C6, STM32L151R6, STM32L151C8, STM32L151R8, STM32L151V8, STM32L151CB, STM32L151RB and STM32L151VB */
  /* #define STM32L151xBA */   /*!< STM32L151C6-A, STM32L151R6-A, STM32L151C8-A, STM32L151R8-A, STM32L151V8-A, STM32L151CB-A, STM32L151RB-A and STM32L151VB-A */ 
  /* #define STM32L151xC  */   /*!< STM32L151CC, STM32L151UC, STM32L151RC and STM32L151VC */
  /* #define STM32L151xCA */   /*!< STM32L151RC-A, STM32L151VC-A, STM32L151QC and STM32L151ZC */
  /* #define STM32L151xD  */   /*!< STM32L151QD, STM32L151RD, STM32L151VD & STM32L151ZD */
  /* #define STM32L151xDX */   /*!< STM32L151VD-X Devices */
  /* #define STM32L151xE  */   /*!< STM32L151QE, STM32L151RE, STM32L151VE and STM32L151ZE */
  /* #define STM32L152xB  */   /*!< STM32L152C6, STM32L152R6, STM32L152C8, STM32L152R8, STM32L152V8, STM32L152CB, STM32L152RB and STM32L152VB */
  /* #define STM32L152xBA */   /*!< STM32L152C6-A, STM32L152R6-A, STM32L152C8-A, STM32L152R8-A, STM32L152V8-A, STM32L152CB-A, STM32L152RB-A and STM32L152VB-A */
  /* #define STM32L152xC  */   /*!< STM32L152CC, STM32L152UC, STM32L152RC and STM32L152VC */
  /* #define STM32L152xCA */   /*!< STM32L152RC-A, STM32L152VC-A, STM32L152QC and STM32L152ZC */
  /* #define STM32L152xD  */   /*!< STM32L152QD, STM32L152RD, STM32L152VD and STM32L152ZD */
  /* #define STM32L152xDX */   /*!< STM32L152VD-X Devices */
  /* #define STM32L152xE  */   /*!< STM32L152QE, STM32L152RE, STM32L152VE and STM32L152ZE */
  /* #define STM32L162xC  */   /*!< STM32L162RC and STM32L162VC */
  /* #define STM32L162xCA */   /*!< STM32L162RC-A, STM32L162VC-A, STM32L162QC and STM32L162ZC */
  /* #define STM32L162xD  */   /*!< STM32L162QD, STM32L162RD, STM32L162VD and STM32L162ZD */
  /* #define STM32L162xDX */   /*!< STM32L162VD-X Devices */
  /* #define STM32L162xE  */   /*!< STM32L162RE, STM32L162VE and STM32L162ZE */
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
  * @brief CMSIS Device version number V2.3.2
  */
#define __STM32L1xx_CMSIS_VERSION_MAIN   (0x02) /*!< [31:24] main version */
#define __STM32L1xx_CMSIS_VERSION_SUB1   (0x03) /*!< [23:16] sub1 version */
#define __STM32L1xx_CMSIS_VERSION_SUB2   (0x02) /*!< [15:8]  sub2 version */
#define __STM32L1xx_CMSIS_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __STM32L1xx_CMSIS_VERSION        ((__STM32L1xx_CMSIS_VERSION_MAIN << 24)\
                                         |(__STM32L1xx_CMSIS_VERSION_SUB1 << 16)\
                                         |(__STM32L1xx_CMSIS_VERSION_SUB2 << 8 )\
                                         |(__STM32L1xx_CMSIS_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Device_Included
  * @{
  */

#if defined(STM32L100xB)
  #include "stm32l100xb.h"
#elif defined(STM32L100xBA)
  #include "stm32l100xba.h"
#elif defined(STM32L100xC)
  #include "stm32l100xc.h"
#elif defined(STM32L151xB)
  #include "stm32l151xb.h"
#elif defined(STM32L151xBA)
  #include "stm32l151xba.h"
#elif defined(STM32L151xC)
  #include "stm32l151xc.h"
#elif defined(STM32L151xCA)
  #include "stm32l151xca.h"
#elif defined(STM32L151xD)
  #include "stm32l151xd.h"
#elif defined(STM32L151xDX)
  #include "stm32l151xdx.h"
#elif defined(STM32L151xE)
  #include "stm32l151xe.h"
#elif defined(STM32L152xB)
  #include "stm32l152xb.h"
#elif defined(STM32L152xBA)
  #include "stm32l152xba.h"
#elif defined(STM32L152xC)
  #include "stm32l152xc.h"
#elif defined(STM32L152xCA)
  #include "stm32l152xca.h"
#elif defined(STM32L152xD)
  #include "stm32l152xd.h"
#elif defined(STM32L152xDX)
  #include "stm32l152xdx.h"
#elif defined(STM32L152xE)
  #include "stm32l152xe.h"
#elif defined(STM32L162xC)
  #include "stm32l162xc.h"
#elif defined(STM32L162xCA)
  #include "stm32l162xca.h"
#elif defined(STM32L162xD)
  #include "stm32l162xd.h"
#elif defined(STM32L162xDX)
  #include "stm32l162xdx.h"
#elif defined(STM32L162xE)
  #include "stm32l162xe.h"
#else
 #error "Please select first the target STM32L1xx device used in your application (in stm32l1xx.h file)"
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

#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL))) 


/**
  * @}
  */

#if defined (USE_HAL_DRIVER)
 #include "stm32l1xx_hal.h"
#endif /* USE_HAL_DRIVER */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STM32L1xx_H */
/**
  * @}
  */

/**
  * @}
  */
  



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
