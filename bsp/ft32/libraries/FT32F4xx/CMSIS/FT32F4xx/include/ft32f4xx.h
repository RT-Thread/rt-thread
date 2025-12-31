/**
  ******************************************************************************
  * @file               ft32f4xx.h
  * @author             FMD AE
  * @brief              CMSIS FT32F4xx Device Peripheral Access Layer Header File.
  * @version            V1.0.0
  * @data                   2025-03-04
  ******************************************************************************
  */

#ifndef __FT32F4xx_H
#define __FT32F4xx_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#if !defined  (FT32F4)
#define FT32F4
#endif /* FT32F4 */



/**
  * @brief CMSIS Device version number V2.3.3
  */
#define __FT32F4_DEVICE_VERSION_MAIN   (0x02) /*!< [31:24] main version */
#define __FT32F4_DEVICE_VERSION_SUB1   (0x03) /*!< [23:16] sub1 version */
#define __FT32F4_DEVICE_VERSION_SUB2   (0x03) /*!< [15:8]  sub2 version */
#define __FT32F4_DEVICE_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __FT32F4_DEVICE_VERSION        ((__FT32F4_DEVICE_VERSION_MAIN << 24)\
                                        |(__FT32F4_DEVICE_VERSION_SUB1 << 16)\
                                        |(__FT32F4_DEVICE_VERSION_SUB2 << 8 )\
                                        |(__FT32F4_DEVICE_VERSION_RC))


/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
//void assert_failed(uint8_t* file, uint32_t line);
void assert_failed(uint8_t *file, uint32_t line)
{
    printf("Wrong parameters value: file %s on line %d\r\n", file, line);
}
#else
#define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */


#if !defined(UNUSED)
#define UNUSED(x) ((void)(x))
#endif


#if defined(FT32F407xE)
#include "ft32f407xe.h"
#else
#error "Please select first the target FT32F4xx device used in your application (in ft32f4xx.h file)"
#endif

/**
  * @}
  */

#if defined(__CC_ARM)  // AC5 ARMCC 
#define WEAK __weak
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)  // AC6 ARMclang
#define WEAK __attribute__((weak))
#else
#define WEAK __attribute__((weak))
#endif



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

#endif /* __FT32F4xx_H */
/**
  * @}
  */

/**
  * @}
  */




/*****************************END OF FILE****/
