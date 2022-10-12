/**
  ******************************************************************************
  * @file               ft32f0xx.h
  * @author             FMD AE
  * @brief              CMSIS FT32F0xx Device Peripheral Access Layer Header File.
  * @version            V1.0.0
  * @data                   2021-07-01
  ******************************************************************************
  */

#ifndef __FT32F0xx_H
#define __FT32F0xx_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */


#if !defined  (FT32F0)
#define FT32F0
#endif /* FT32F0 */



/**
  * @brief CMSIS Device version number V2.3.3
  */
#define __FT32F0_DEVICE_VERSION_MAIN   (0x02) /*!< [31:24] main version */
#define __FT32F0_DEVICE_VERSION_SUB1   (0x03) /*!< [23:16] sub1 version */
#define __FT32F0_DEVICE_VERSION_SUB2   (0x03) /*!< [15:8]  sub2 version */
#define __FT32F0_DEVICE_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __FT32F0_DEVICE_VERSION        ((__FT32F0_DEVICE_VERSION_MAIN << 24)\
                                        |(__FT32F0_DEVICE_VERSION_SUB1 << 16)\
                                        |(__FT32F0_DEVICE_VERSION_SUB2 << 8 )\
                                        |(__FT32F0_DEVICE_VERSION_RC))


/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#if defined(FT32F030x6)
  #include "ft32f030x6.h"
#elif defined(FT32F030x8)
  #include "ft32f030x8.h"
#elif defined (FT32F032x6)
  #include "ft32f032x6.h"
#elif defined (FT32F032x8)
  #include "ft32f032x8.h"
#elif defined(FT32F072x8)
  #include "ft32f072x8.h"
#elif defined(FT32F072xB)
  #include "ft32f072xb.h"
#else
 #error "Please select first the target FT32F0xx device used in your application (in ft32f0xx.h file)"
#endif
#include "../../../FT32F0xx_Driver/templates/Inc/ft32f0xx_conf.h"

/**
  * @}
  */



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


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FT32F0xx_H */
/**
  * @}
  */

/**
  * @}
  */




/*****************************END OF FILE****/
