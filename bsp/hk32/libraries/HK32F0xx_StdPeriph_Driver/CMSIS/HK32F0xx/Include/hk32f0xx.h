/**************************************************************************
* @file hk32f0xx.h
* @version V1.0.1
* @date    2019-08-15
* @brief CMSIS Cortex-M Peripheral Access Layer for HKMicroChip devices
*
*****************************************************************************/
/** @addtogroup hk32f0xx
  * @{
  */
    
#ifndef __HK32F0xx_H
#define __HK32F0xx_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
   
/** @addtogroup Library_configuration_section
  * @{
  */
  

/* Uncomment the line below according to the target HK32 device used in your
   application 
  */

#if !defined (HK32F030x4) && !defined (HK32F030x6) &&  !defined (HK32F030x8) &&\
    !defined (HK32F031x4) && !defined (HK32F031x6) &&                       \
    !defined (HK32F04Ax4) && !defined (HK32F04Ax6) && !defined (HK32F04Ax8) 

#endif
   
/*  Tip: To avoid modifying this file each time you need to switch between these
        devices, you can define the device in your toolchain compiler preprocessor.
  */

/**
  * @brief CMSIS Device version number V2.3.3
  */
#define __HK32F0_DEVICE_VERSION_MAIN   (0x02) /*!< [31:24] main version */
#define __HK32F0_DEVICE_VERSION_SUB1   (0x03) /*!< [23:16] sub1 version */
#define __HK32F0_DEVICE_VERSION_SUB2   (0x03) /*!< [15:8]  sub2 version */
#define __HK32F0_DEVICE_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __HK32F0_DEVICE_VERSION        ((__HK32F0_DEVICE_VERSION_MAIN << 24)\
                                        |(__HK32F0_DEVICE_VERSION_SUB1 << 16)\
                                        |(__HK32F0_DEVICE_VERSION_SUB2 << 8 )\
                                        |(__HK32F0_DEVICE_VERSION_RC))
                                             
/**
  * @}
  */

/** @addtogroup Device_Included
  * @{
  */

#if defined(HK32F030x4)
  #include "hk32f030x4x6x8.h"
#elif defined(HK32F030x6)
  #include "hk32f030x4x6x8.h"
#elif defined(HK32F030x8)
  #include "hk32f030x4x6x8.h"
#elif defined(HK32F031x4)
  #include "hk32f031x4x6.h"
#elif defined(HK32F031x6)
  #include "hk32f031x4x6.h"
#elif defined(HK32F04Ax)
  #include "hk32f04ax4x6x8.h"  
#else
 #error "Please select first the target HK32F0xx device used in your application (in hk32f0xx.h file)"
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
  SET = 1
} FlagStatus, ITStatus;

typedef enum 
{
  DISABLE = 0, 
  ENABLE = 1
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum 
{
  ERROR = 0, 
  SUCCESS = 1
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




  
/** @addtogroup Library_configuration_section
  * @{
  */
  
/**
  * @brief HK32 Family
  */
#if !defined (HK32F0)
#define HK32F0
#endif /* HK32F0 */


/*
 * @brief In the following line adjust the value of External High Speed oscillator (HSE)
   used in your application 
   
   Tip: To avoid modifying this file each time you need to use different HSE, you
        can define the HSE value in your toolchain compiler preprocessor.
  */
#if !defined  (HSE_VALUE)     
#define HSE_VALUE    ((uint32_t)8000000) /*!< Value of the External oscillator in Hz*/
#endif /* HSE_VALUE */

/**
 * @brief In the following line adjust the External High Speed oscillator (HSE) Startup 
   Timeout value 
   */
#if !defined  (HSE_STARTUP_TIMEOUT)
#define HSE_STARTUP_TIMEOUT   ((uint16_t)0xFFFF) /*!< Time out for HSE start up */
#endif /* HSE_STARTUP_TIMEOUT */

/**
 * @brief In the following line adjust the Internal High Speed oscillator (HSI) Startup 
   Timeout value 
   */
#if !defined  (HSI_STARTUP_TIMEOUT)
#define HSI_STARTUP_TIMEOUT   ((uint16_t)0xFFFF) /*!< Time out for HSI start up */
#endif /* HSI_STARTUP_TIMEOUT */

#if !defined  (HSI_VALUE) 
#define HSI_VALUE  ((uint32_t)8000000) /*!< Value of the Internal High Speed oscillator in Hz.
                                             The real value may vary depending on the variations
                                             in voltage and temperature.  */
#endif /* HSI_VALUE */

#if !defined  (HSI14_VALUE) 
#define HSI14_VALUE ((uint32_t)14000000) /*!< Value of the Internal High Speed oscillator for ADC in Hz.
                                             The real value may vary depending on the variations
                                             in voltage and temperature.  */
#endif /* HSI14_VALUE */

#if !defined  (HSI48_VALUE) 
#define HSI48_VALUE ((uint32_t)48000000) /*!< Value of the Internal High Speed oscillator for USB in Hz.
                                             The real value may vary depending on the variations
                                             in voltage and temperature.  */
#endif /* HSI48_VALUE */

#if !defined  (LSI_VALUE) 
#define LSI_VALUE  ((uint32_t)40000)    /*!< Value of the Internal Low Speed oscillator in Hz
                                             The real value may vary depending on the variations
                                             in voltage and temperature.  */
#endif /* LSI_VALUE */

#if !defined  (LSE_VALUE) 
#define LSE_VALUE  ((uint32_t)32768)    /*!< Value of the External Low Speed oscillator in Hz */
#endif /* LSE_VALUE */

/**
 * @brief HK32F0xx Standard Peripheral Library version number V1.4.0
   */
#define __HK32F0XX_STDPERIPH_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __HK32F0XX_STDPERIPH_VERSION_SUB1   (0x05) /*!< [23:16] sub1 version */
#define __HK32F0XX_STDPERIPH_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __HK32F0XX_STDPERIPH_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __HK32F0XX_STDPERIPH_VERSION        ((__HK32F0XX_STDPERIPH_VERSION_MAIN << 24)\
                                             |(__HK32F0XX_STDPERIPH_VERSION_SUB1 << 16)\
                                             |(__HK32F0XX_STDPERIPH_VERSION_SUB2 << 8)\
                                             |(__HK32F0XX_STDPERIPH_VERSION_RC))

#ifdef USE_STDPERIPH_DRIVER
  #include "hk32f0xx_hk_conf.h"
#endif


/*#endif USE_STDPERIPH_DRIVER*/
#endif /*#endif __HK32F0xx_H*/


