/*********************************************************************************************************//**
 * @file    ht32f1xxxx_rstcu.h
 * @version $Rev:: 2973         $
 * @date    $Date:: 2023-10-30 #$
 * @brief   The header file of the Reset Control Unit library.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F1XXXX_RSTCU_H
#define __HT32F1XXXX_RSTCU_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @addtogroup RSTCU
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup RSTCU_Exported_Types RSTCU exported types
  * @{
  */

/**
 * @brief Enumeration of Global reset status.
 */
typedef enum
{
  RSTCU_FLAG_SYSRST = 0,
  RSTCU_FLAG_EXTRST,
  RSTCU_FLAG_WDTRST,
  RSTCU_FLAG_PORST
} RSTCU_RSTF_TypeDef;

/**
 * @brief Definition of initial structure of peripheral reset.
 */
typedef union
{
  struct
  {
    /*  Definitions of AHB peripheral reset                                                                 */
    unsigned long PDMA       :1;    // Bit 0
    unsigned long            :1;    // Bit 1
    unsigned long            :1;    // Bit 2
    unsigned long            :1;    // Bit 3
#if (LIBCFG_CSIF)
    unsigned long CSIF       :1;    // Bit 4
#else
    unsigned long            :1;    // Bit 4
#endif
    unsigned long USBD       :1;    // Bit 5
    unsigned long EBI        :1;    // Bit 6
    unsigned long CRC        :1;    // Bit 7

    unsigned long PA         :1;    // Bit 8
    unsigned long PB         :1;    // Bit 9
    unsigned long PC         :1;    // Bit 10
    unsigned long PD         :1;    // Bit 11
#if (LIBCFG_GPIOE)
    unsigned long PE         :1;    // Bit 12
#else
    unsigned long            :1;    // Bit 12
#endif
#if (LIBCFG_GPIOF)
    unsigned long PF         :1;    // Bit 13
#else
    unsigned long            :1;    // Bit 13
#endif
#if (LIBCFG_SDIO)
    unsigned long SDIO       :1;    // Bit 14
#else
    unsigned long            :1;    // Bit 14
#endif
#if (LIBCFG_AES)
    unsigned long AES        :1;    // Bit 15
#else
    unsigned long            :1;    // Bit 15
#endif

    unsigned long            :1;    // Bit 16
    unsigned long            :1;    // Bit 17
    unsigned long            :1;    // Bit 18
    unsigned long            :1;    // Bit 19
    unsigned long            :1;    // Bit 20
    unsigned long            :1;    // Bit 21
    unsigned long            :1;    // Bit 22
    unsigned long            :1;    // Bit 23

    unsigned long            :1;    // Bit 24
    unsigned long            :1;    // Bit 25
    unsigned long            :1;    // Bit 26
    unsigned long            :1;    // Bit 27
    unsigned long            :1;    // Bit 28
    unsigned long            :1;    // Bit 29
    unsigned long            :1;    // Bit 30
    unsigned long            :1;    // Bit 31

    /*  Definitions of APB peripheral 0 reset                                                               */
    unsigned long I2C0       :1;    // Bit 0
    unsigned long I2C1       :1;    // Bit 1
    unsigned long            :1;    // Bit 2
    unsigned long            :1;    // Bit 3
    unsigned long SPI0       :1;    // Bit 4
    unsigned long SPI1       :1;    // Bit 5
    unsigned long            :1;    // Bit 6
    unsigned long            :1;    // Bit 7

    unsigned long USART0     :1;    // Bit 8
    unsigned long USART1     :1;    // Bit 9
    unsigned long UART0      :1;    // Bit 10
    unsigned long UART1      :1;    // Bit 11
    unsigned long            :1;    // Bit 12
    unsigned long            :1;    // Bit 13
    unsigned long AFIO       :1;    // Bit 14
    unsigned long EXTI       :1;    // Bit 15

    unsigned long            :1;    // Bit 16
    unsigned long            :1;    // Bit 17
    unsigned long            :1;    // Bit 18
    unsigned long            :1;    // Bit 19
    unsigned long            :1;    // Bit 20
    unsigned long            :1;    // Bit 21
    unsigned long            :1;    // Bit 22
    unsigned long            :1;    // Bit 23

#if (LIBCFG_SCI0)
    unsigned long SCI0       :1;    // Bit 24
#else
    unsigned long            :1;    // Bit 24
#endif
    unsigned long I2S        :1;    // Bit 25
    unsigned long            :1;    // Bit 26
#if (LIBCFG_SCI1)
    unsigned long SCI1       :1;    // Bit 27
#else
    unsigned long            :1;    // Bit 27
#endif
    unsigned long            :1;    // Bit 28
    unsigned long            :1;    // Bit 29
    unsigned long            :1;    // Bit 30
    unsigned long            :1;    // Bit 31

    /* Definitions of APB peripheral 1 reset                                                                */
    unsigned long MCTM0      :1;    // Bit 0
    unsigned long MCTM1      :1;    // Bit 1
    unsigned long            :1;    // Bit 2
    unsigned long            :1;    // Bit 3
    unsigned long WDT        :1;    // Bit 4
    unsigned long            :1;    // Bit 5
    unsigned long            :1;    // Bit 6
    unsigned long            :1;    // Bit 7

    unsigned long GPTM0      :1;    // Bit 8
    unsigned long GPTM1      :1;    // Bit 9
    unsigned long            :1;    // Bit 10
    unsigned long            :1;    // Bit 11
    unsigned long PWM0       :1;    // Bit 12
    unsigned long            :1;    // Bit 13
    unsigned long            :1;    // Bit 14
    unsigned long            :1;    // Bit 15

    unsigned long BFTM0      :1;    // Bit 16
    unsigned long BFTM1      :1;    // Bit 17
    unsigned long            :1;    // Bit 18
    unsigned long            :1;    // Bit 19
    unsigned long            :1;    // Bit 20
    unsigned long            :1;    // Bit 21
#if (LIBCFG_CMP_OPA)
    unsigned long OPA0       :1;    // Bit 22
#else
    unsigned long CMP        :1;    // Bit 22
#endif
#if (LIBCFG_CMP_OPA)
    unsigned long OPA1       :1;    // Bit 23
#else
    unsigned long            :1;    // Bit 23
#endif

    unsigned long ADC0       :1;    // Bit 24
    unsigned long            :1;    // Bit 25
    unsigned long            :1;    // Bit 26
    unsigned long            :1;    // Bit 27
    unsigned long SCTM0      :1;    // Bit 28
    unsigned long SCTM1      :1;    // Bit 29
    unsigned long            :1;    // Bit 30
    unsigned long            :1;    // Bit 31
  } Bit;
  u32 Reg[3];
} RSTCU_PeripReset_TypeDef;

/**
  * @}
  */


/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup RSTCU_Exported_Constants RSTCU exported constants
  * @{
  */

/* Other definitions                                                                                        */
#define IS_RSTCU_FLAG(FLAG)       ((FLAG == RSTCU_FLAG_SYSRST) || \
                                   (FLAG == RSTCU_FLAG_EXTRST) || \
                                   (FLAG == RSTCU_FLAG_WDTRST) || \
                                   (FLAG == RSTCU_FLAG_PORST))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup RSTCU_Exported_Functions RSTCU exported functions
  * @{
  */
FlagStatus RSTCU_GetResetFlagStatus(RSTCU_RSTF_TypeDef RSTCU_RSTF);
void RSTCU_ClearResetFlag(RSTCU_RSTF_TypeDef RSTCU_RSTF);
void RSTCU_ClearAllResetFlag(void);
void RSTCU_PeripReset(RSTCU_PeripReset_TypeDef Reset, ControlStatus Cmd);

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
#endif

#endif
