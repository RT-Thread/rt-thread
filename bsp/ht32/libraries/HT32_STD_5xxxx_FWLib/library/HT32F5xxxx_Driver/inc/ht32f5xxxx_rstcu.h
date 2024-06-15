/*********************************************************************************************************//**
 * @file    ht32f5xxxx_rstcu.h
 * @version $Rev:: 7115         $
 * @date    $Date:: 2023-08-11 #$
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
#ifndef __HT32F5XXXX_RSTCU_H
#define __HT32F5XXXX_RSTCU_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
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
    unsigned long            :1;    // Bit 4
    unsigned long USBD       :1;    // Bit 5
    unsigned long EBI        :1;    // Bit 6
    unsigned long CRC        :1;    // Bit 7

    unsigned long PA         :1;    // Bit 8
    unsigned long PB         :1;    // Bit 9
    unsigned long PC         :1;    // Bit 10
    unsigned long PD         :1;    // Bit 11
    unsigned long PE         :1;    // Bit 12
    unsigned long PF         :1;    // Bit 13
    unsigned long            :1;    // Bit 14
    unsigned long AES        :1;    // Bit 15

    #ifdef USE_HT32F65230_40
    unsigned long DIV        :1;    // Bit 16
    #else
    unsigned long            :1;    // Bit 16
    #endif
    unsigned long            :1;    // Bit 17
    unsigned long            :1;    // Bit 18
    unsigned long            :1;    // Bit 19
    unsigned long            :1;    // Bit 20
    unsigned long            :1;    // Bit 21
    unsigned long            :1;    // Bit 22
    unsigned long            :1;    // Bit 23

    #ifndef USE_HT32F65230_40
    unsigned long DIV        :1;    // Bit 24
    #else
    unsigned long            :1;    // Bit 24
    #endif
    unsigned long QSPI       :1;    // Bit 25
    unsigned long RF         :1;    // Bit 26
    unsigned long            :1;    // Bit 27
    unsigned long            :1;    // Bit 28
    unsigned long            :1;    // Bit 29
    unsigned long            :1;    // Bit 30
    unsigned long            :1;    // Bit 31

    /*  Definitions of APB peripheral 0 reset                                                               */
    unsigned long I2C0       :1;    // Bit 0
    unsigned long I2C1       :1;    // Bit 1
    unsigned long I2C2       :1;    // Bit 2
    unsigned long            :1;    // Bit 3
    unsigned long SPI0       :1;    // Bit 4
    unsigned long SPI1       :1;    // Bit 5
    unsigned long            :1;    // Bit 6
    unsigned long            :1;    // Bit 7

    unsigned long USART0     :1;    // Bit 8
    unsigned long USART1     :1;    // Bit 9
    unsigned long UART0      :1;    // Bit 10
    unsigned long UART1      :1;    // Bit 11
    unsigned long UART2      :1;    // Bit 12
    unsigned long UART3      :1;    // Bit 13
    unsigned long AFIO       :1;    // Bit 14
    unsigned long EXTI       :1;    // Bit 15

    unsigned long            :1;    // Bit 16
    unsigned long            :1;    // Bit 17
    unsigned long            :1;    // Bit 18
    unsigned long            :1;    // Bit 19
    unsigned long            :1;    // Bit 20
    unsigned long            :1;    // Bit 21
    unsigned long SLED0      :1;    // Bit 22
    unsigned long SLED1      :1;    // Bit 23

    unsigned long SCI0       :1;    // Bit 24
    unsigned long I2S        :1;    // Bit 25
    unsigned long            :1;    // Bit 26
    unsigned long SCI1       :1;    // Bit 27
    unsigned long MIDI       :1;    // Bit 28
    unsigned long LEDC       :1;    // Bit 29
    unsigned long CAN0       :1;    // Bit 30
    unsigned long            :1;    // Bit 31

    /* Definitions of APB peripheral 1 reset                                                                */
    unsigned long MCTM0      :1;    // Bit 0
    unsigned long            :1;    // Bit 1
    unsigned long            :1;    // Bit 2
    unsigned long            :1;    // Bit 3
    unsigned long WDT        :1;    // Bit 4
    unsigned long            :1;    // Bit 5
    unsigned long            :1;    // Bit 6
    unsigned long DAC1       :1;    // Bit 7

    unsigned long GPTM0      :1;    // Bit 8
    unsigned long GPTM1      :1;    // Bit 9
    unsigned long            :1;    // Bit 10
    unsigned long            :1;    // Bit 11
    unsigned long PWM0       :1;    // Bit 12
    unsigned long PWM1       :1;    // Bit 13
    unsigned long PWM2       :1;    // Bit 14
    unsigned long            :1;    // Bit 15

    unsigned long BFTM0      :1;    // Bit 16
    unsigned long BFTM1      :1;    // Bit 17
    unsigned long TKEY       :1;    // Bit 18
    unsigned long LCD        :1;    // Bit 19
    unsigned long            :1;    // Bit 20
    unsigned long DAC0       :1;    // Bit 21
    unsigned long CMP        :1;    // Bit 22
    unsigned long OPA        :1;    // Bit 23

    unsigned long ADC0       :1;    // Bit 24
    unsigned long ADC1       :1;    // Bit 25
    unsigned long            :1;    // Bit 26
    unsigned long            :1;    // Bit 27
    unsigned long SCTM0      :1;    // Bit 28
    unsigned long SCTM1      :1;    // Bit 29
    unsigned long SCTM2      :1;    // Bit 30
    unsigned long SCTM3      :1;    // Bit 31
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
