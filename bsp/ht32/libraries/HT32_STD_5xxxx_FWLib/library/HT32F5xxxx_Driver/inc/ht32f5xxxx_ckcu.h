/*********************************************************************************************************//**
 * @file    ht32f5xxxx_ckcu.h
 * @version $Rev:: 7108         $
 * @date    $Date:: 2023-08-09 #$
 * @brief   The header file of the Clock Control Unit library.
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
#ifndef __HT32F5XXXX_CKCU_H
#define __HT32F5XXXX_CKCU_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup CKCU
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup CKCU_Exported_Types CKCU exported types
  * @{
  */

#if (!LIBCFG_CKCU_NO_APB_PRESCALER)
/**
 * @brief Enumeration of APB peripheral prescaler.
 */
typedef enum
{
  CKCU_APBCLKPRE_DIV1 = 0,
  CKCU_APBCLKPRE_DIV2,
  CKCU_APBCLKPRE_DIV4,
  CKCU_APBCLKPRE_DIV8,
  CKCU_APBCLKPRE_DIV16,
  CKCU_APBCLKPRE_DIV32
} CKCU_APBCLKPRE_TypeDef;
#endif

/**
 * @brief Enumeration of CK_REF prescaler.
 */
typedef enum
{
  CKCU_CKREFPRE_DIV2 = 0,
  CKCU_CKREFPRE_DIV4,
  CKCU_CKREFPRE_DIV6,
  CKCU_CKREFPRE_DIV8,
  CKCU_CKREFPRE_DIV10,
  CKCU_CKREFPRE_DIV12,
  CKCU_CKREFPRE_DIV14,
  CKCU_CKREFPRE_DIV16,
  CKCU_CKREFPRE_DIV18,
  CKCU_CKREFPRE_DIV20,
  CKCU_CKREFPRE_DIV22,
  CKCU_CKREFPRE_DIV24,
  CKCU_CKREFPRE_DIV26,
  CKCU_CKREFPRE_DIV28,
  CKCU_CKREFPRE_DIV30,
  CKCU_CKREFPRE_DIV32,
  CKCU_CKREFPRE_DIV34,
  CKCU_CKREFPRE_DIV36,
  CKCU_CKREFPRE_DIV38,
  CKCU_CKREFPRE_DIV40,
  CKCU_CKREFPRE_DIV42,
  CKCU_CKREFPRE_DIV44,
  CKCU_CKREFPRE_DIV46,
  CKCU_CKREFPRE_DIV48,
  CKCU_CKREFPRE_DIV50,
  CKCU_CKREFPRE_DIV52,
  CKCU_CKREFPRE_DIV54,
  CKCU_CKREFPRE_DIV56,
  CKCU_CKREFPRE_DIV58,
  CKCU_CKREFPRE_DIV60,
  CKCU_CKREFPRE_DIV62,
  CKCU_CKREFPRE_DIV64
} CKCU_CKREFPRE_TypeDef;

#if (!LIBCFG_NO_PLL)
/**
 * @brief Enumeration of PLL clock source.
 */
typedef enum
{
  CKCU_PLLSRC_HSE = 0,
  CKCU_PLLSRC_HSI
} CKCU_PLLSRC_TypeDef;

#define IS_PLL_CLKSRC(SRC)      ((SRC == CKCU_PLLSRC_HSE) || \
                                 (SRC == CKCU_PLLSRC_HSI))
#endif

#if (LIBCFG_CKCU_USB_PLL)
/**
 * @brief Enumeration of CK_USB clock source.
 */
typedef enum
{
  CKCU_CKPLL    = 0,
  CKCU_CKUSBPLL
} CKCU_USBSRC_TypeDef;
#endif

#if (LIBCFG_CKCU_LCD_SRC)
/**
 * @brief Enumeration of CK_LCD clock source.
 */
typedef enum
{
  CKCU_LCDSRC_LSI = 0,
  #if (LIBCFG_LSE)
  CKCU_LCDSRC_LSE,
  #endif
  CKCU_LCDSRC_HSI,
  CKCU_LCDSRC_HSE
} CKCU_LCDSRC_TypeDef;
#endif

#if (LIBCFG_CKCU_MCTM_SRC)
/**
 * @brief Enumeration of MCTM clock source.
 */
typedef enum
{
  CKCU_MCTMSRC_AHB = 0,
  CKCU_MCTMSRC_USBPLL
} CKCU_MCTMSRC_TypeDef;

#define IS_MCTM_SRC(SRC)        ((SRC == CKCU_MCTMSRC_AHB) || \
                                 (SRC == CKCU_MCTMSRC_USBPLL))
#endif


#if (((LIBCFG_LSE) || (LIBCFG_USBD) || (LIBCFG_CKCU_REFCLK_EXT_PIN)) && (!LIBCFG_CKCU_NO_AUTO_TRIM))
/**
 * @brief Enumeration of HSI auto-trim clock source.
 */
typedef enum
{
  #if (LIBCFG_LSE)
  CKCU_ATC_LSE = 0,
  #endif
  #if (LIBCFG_USBD)
  CKCU_ATC_USB = 1,
  #endif
  #if (LIBCFG_CKCU_REFCLK_EXT_PIN)
  CKCU_ATC_CKIN = 2,
  #endif
} CKCU_ATC_TypeDef;
#endif

#if (LIBCFG_CKCU_ATM_V01)
/**
 * @brief Enumeration of ATC search algorithm.
 */
typedef enum
{
  CKCU_ATC_BINARY_SEARCH = 0,
  CKCU_ATC_LINEAR_SEARCH = 8
} CKCU_ATCSearchAlgorithm_TypeDef;

/**
 * @brief Enumeration of ATC frequency tolerance.
 */
typedef enum
{
  CKCU_ATC_DOUBLE_PRECISION = 0,
  CKCU_ATC_SINGLE_PRECISION = 4
} CKCU_ATCFrqTolerance_TypeDef;
#endif

/**
 * @brief Enumeration of CK_AHB prescaler.
 */
typedef enum
{
  CKCU_SYSCLK_DIV1 = 0,
  CKCU_SYSCLK_DIV2,
  CKCU_SYSCLK_DIV4,
  CKCU_SYSCLK_DIV8,
  CKCU_SYSCLK_DIV16,
  CKCU_SYSCLK_DIV32
} CKCU_SYSCLKDIV_TypeDef;

/**
 * @brief Enumeration of CK_ADC prescaler.
 */
typedef enum
{
  #if (LIBCFG_CKCU_NO_ADCPRE_DIV1)
  #else
  CKCU_ADCPRE_DIV1 = 0,
  #endif
  CKCU_ADCPRE_DIV2 = 1,
  CKCU_ADCPRE_DIV4,
  CKCU_ADCPRE_DIV8,
  CKCU_ADCPRE_DIV16,
  CKCU_ADCPRE_DIV32,
  CKCU_ADCPRE_DIV64,
  CKCU_ADCPRE_DIV3
} CKCU_ADCPRE_TypeDef;

/**
 * @brief Enumeration of CK_ADCn.
 */
typedef enum
{
  CKCU_ADCPRE_ADC0 = 16,
  #if (LIBCFG_ADC1)
  CKCU_ADCPRE_ADC1 = 20,
  #endif
} CKCU_ADCPRE_ADCn_TypeDef;

#if (LIBCFG_LCD)
/**
 * @brief Enumeration of CK_LCD prescaler.
 */
typedef enum
{
  CKCU_LCDPRE_DIV1 = 0,
  CKCU_LCDPRE_DIV2,
  CKCU_LCDPRE_DIV4,
  CKCU_LCDPRE_DIV8,
  CKCU_LCDPRE_DIV16,
} CKCU_LCDPRE_TypeDef;
#endif

#if (LIBCFG_MIDI)
/**
 * @brief Enumeration of CK_MIDI prescaler.
 */
typedef enum
{
  CKCU_MIDIPRE_DIV16 = 0,
  CKCU_MIDIPRE_DIV13,
  CKCU_MIDIPRE_DIV11,
  CKCU_MIDIPRE_DIV9,
  CKCU_MIDIPRE_DIV8,
} CKCU_MIDIPRE_TypeDef;
#endif

/**
 * @brief Enumeration of System clock source.
 */
typedef enum
{
#if (!LIBCFG_NO_PLL)
  CKCU_SW_PLL = 1,
#endif
  CKCU_SW_HSE = 2,
  CKCU_SW_HSI = 3,
  #if (LIBCFG_LSE)
  CKCU_SW_LSE = 6,
  #endif
  CKCU_SW_LSI = 7
} CKCU_SW_TypeDef;

/**
 * @brief Enumeration of CKOUT clock source.
 */
typedef enum
{
  CKCU_CKOUTSRC_REFCK       = 0,
  CKCU_CKOUTSRC_HCLK_DIV16  = 1,
  CKCU_CKOUTSRC_SYSCK_DIV16 = 2,
  CKCU_CKOUTSRC_HSECK_DIV16 = 3,
  CKCU_CKOUTSRC_HSICK_DIV16 = 4,
  #if (LIBCFG_LSE)
  CKCU_CKOUTSRC_LSECK       = 5,
  #endif
  CKCU_CKOUTSRC_LSICK       = 6
} CKCU_CKOUTSRC_TypeDef;

#if (!LIBCFG_NO_PLL)
/**
 * @brief Enumeration of PLL clock source status.
 */
typedef enum
{
  CKCU_PLLST_SYSCK  = 1,
  #if (LIBCFG_USBD)
  CKCU_PLLST_USB    = 4,
  #endif
  CKCU_PLLST_REFCK  = 8
} CKCU_PLLST_TypeDef;
#endif

/**
 * @brief Enumeration of HSI clock source status.
 */
typedef enum
{
  CKCU_HSIST_SYSCK  = 1,
#if (!LIBCFG_NO_PLL)
  CKCU_HSIST_PLL    = 2,
#endif
  CKCU_HSIST_CKM    = 4
} CKCU_HSIST_TypeDef;

/**
 * @brief Enumeration of HSE clock source status.
 */
typedef enum
{
  CKCU_HSEST_SYSCK  = 1,
#if (!LIBCFG_NO_PLL)
  CKCU_HSEST_PLL
#endif
} CKCU_HSEST_TypeDef;

/**
 * @brief Definition of CKOUT Init Structure.
 */
typedef struct
{
  CKCU_CKOUTSRC_TypeDef CKOUTSRC;
} CKCU_CKOUTInitTypeDef;

#if (!LIBCFG_NO_PLL)
/**
 * @brief Definition of PLL Init Structure.
 */
typedef struct
{
  u32 CFG;
  CKCU_PLLSRC_TypeDef ClockSource;
  ControlStatus BYPASSCmd;
} CKCU_PLLInitTypeDef;
#endif

/**
 * @brief Definition of structure for clock frequency.
 */
typedef struct
{
#if (!LIBCFG_NO_PLL)
  u32 PLL_Freq;
#endif
  u32 SYSCK_Freq;
  u32 HCLK_Freq;
#if (HT32_LIB_ENABLE_GET_CK_ADC)
#if (!LIBCFG_NO_ADC)
  u32 ADC0_Freq;
#endif
#if (LIBCFG_ADC1)
  u32 ADC1_Freq;
#endif
#endif
} CKCU_ClocksTypeDef;

#if (LIBCFG_CKCU_ATM_V01)
/**
 * @brief Definition of ATC Init Structure.
 */
typedef struct
{
  CKCU_ATCSearchAlgorithm_TypeDef SearchAlgorithm;
  CKCU_ATCFrqTolerance_TypeDef FrqTolerance;
} CKCU_ATCInitTypeDef;
#endif

/**
 * @brief Definition of initial structure of peripheral clock control.
 */
typedef union
{
  struct
  {
    /* Definitions of AHB clock control                                                                     */
    unsigned long FMC        :1;    // Bit 0
    unsigned long            :1;    // Bit 1
    unsigned long SRAM       :1;    // Bit 2
    unsigned long            :1;    // Bit 3
    unsigned long PDMA       :1;    // Bit 4
    unsigned long BM         :1;    // Bit 5
    unsigned long APB        :1;    // Bit 6
    unsigned long            :1;    // Bit 7

    unsigned long            :1;    // Bit 8
    unsigned long            :1;    // Bit 9
    unsigned long USBD       :1;    // Bit 10
    unsigned long CKREF      :1;    // Bit 11
    unsigned long EBI        :1;    // Bit 12
    unsigned long CRC        :1;    // Bit 13
    unsigned long            :1;    // Bit 14
    unsigned long AES        :1;    // Bit 15

    unsigned long PA         :1;    // Bit 16
    unsigned long PB         :1;    // Bit 17
    unsigned long PC         :1;    // Bit 18
    unsigned long PD         :1;    // Bit 19
    unsigned long PE         :1;    // Bit 20
    unsigned long PF         :1;    // Bit 21
    unsigned long            :1;    // Bit 22
    unsigned long            :1;    // Bit 23

    unsigned long DIV        :1;    // Bit 24
    unsigned long QSPI       :1;    // Bit 25
    unsigned long RF         :1;    // Bit 26
    unsigned long            :1;    // Bit 27
    unsigned long            :1;    // Bit 28
    unsigned long            :1;    // Bit 29
    unsigned long            :1;    // Bit 30
    unsigned long            :1;    // Bit 31

    /* Definitions of APB0 clock control                                                                    */
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

    /* Definitions of APB1 clock control                                                                    */
    unsigned long MCTM0      :1;    // Bit 0
    unsigned long            :1;    // Bit 1
    unsigned long            :1;    // Bit 2
    unsigned long            :1;    // Bit 3
    unsigned long WDT        :1;    // Bit 4
    unsigned long            :1;    // Bit 5
    unsigned long BKP        :1;    // Bit 6
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
    unsigned long LCDR       :1;    // Bit 19
    unsigned long LCDC       :1;    // Bit 20
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
} CKCU_PeripClockConfig_TypeDef;

#define CKCU_APBPCSR_OFFSET      (5)
#define CKCU_APBPCSR0            (0 << CKCU_APBPCSR_OFFSET)
#define CKCU_APBPCSR1            (1 << CKCU_APBPCSR_OFFSET)
#define CKCU_APBPCSR2            (4 << CKCU_APBPCSR_OFFSET)
typedef enum
{
  CKCU_PCLK_I2C0     = (CKCU_APBPCSR0 | 0),
  #if (LIBCFG_I2C1)
  CKCU_PCLK_I2C1     = (CKCU_APBPCSR0 | 2),
  #endif
  CKCU_PCLK_SPI0     = (CKCU_APBPCSR0 | 4),
  #if (LIBCFG_SPI1)
  CKCU_PCLK_SPI1     = (CKCU_APBPCSR0 | 6),
  #endif
  #if (LIBCFG_UART2)
  CKCU_PCLK_UART2    = (CKCU_APBPCSR0 | 8),
  #endif
  #if (LIBCFG_UART3)
  CKCU_PCLK_UART3    = (CKCU_APBPCSR0 | 10),
  #endif
  CKCU_PCLK_BFTM0    = (CKCU_APBPCSR0 | 12),
  #if (LIBCFG_BFTM1)
  CKCU_PCLK_BFTM1    = (CKCU_APBPCSR0 | 14),
  #endif
  #if (LIBCFG_MCTM0)
  CKCU_PCLK_MCTM0    = (CKCU_APBPCSR0 | 16),
  #endif
  #if (!LIBCFG_NO_GPTM0)
  CKCU_PCLK_GPTM0    = (CKCU_APBPCSR0 | 20),
  #endif
  #if (LIBCFG_GPTM1)
  CKCU_PCLK_GPTM1    = (CKCU_APBPCSR0 | 22),
  #endif
  #if (!LIBCFG_NO_USART0)
  CKCU_PCLK_USART0   = (CKCU_APBPCSR0 | 24),
  #endif
  #if (LIBCFG_USART1)
  CKCU_PCLK_USART1   = (CKCU_APBPCSR0 | 26),
  #endif
  CKCU_PCLK_UART0    = (CKCU_APBPCSR0 | 28),
  #if (LIBCFG_UART1)
  CKCU_PCLK_UART1    = (CKCU_APBPCSR0 | 30),
  #endif
  CKCU_PCLK_AFIO     = (CKCU_APBPCSR1 | 0),
  CKCU_PCLK_EXTI     = (CKCU_APBPCSR1 | 2),
  #if (!LIBCFG_NO_ADC)
  CKCU_PCLK_ADC0     = (CKCU_APBPCSR1 | 4),
  #endif
  #if (LIBCFG_ADC1)
  CKCU_PCLK_ADC1     = (CKCU_APBPCSR1 | 6),
  #endif
  #if (LIBCFG_CMP)
  CKCU_PCLK_CMP      = (CKCU_APBPCSR1 | 8),
  #endif
  #if (LIBCFG_OPA)
  CKCU_PCLK_OPA      = (CKCU_APBPCSR1 | 10),
  #endif
  CKCU_PCLK_WDTR     = (CKCU_APBPCSR1 | 12),
  CKCU_PCLK_BKPR     = (CKCU_APBPCSR1 | 14),
  #if (LIBCFG_SCI0)
  CKCU_PCLK_SCI0     = (CKCU_APBPCSR1 | 16),
  #endif
  #if (LIBCFG_SCI1)
  CKCU_PCLK_SCI1     = (CKCU_APBPCSR1 | 18),
  #endif
  #if (LIBCFG_I2S)
  CKCU_PCLK_I2S      = (CKCU_APBPCSR1 | 20),
  #endif
  #if (LIBCFG_I2C2)
  CKCU_PCLK_I2C2     = (CKCU_APBPCSR1 | 22),
  #endif
  #if (LIBCFG_SCTM0)
  CKCU_PCLK_SCTM0    = (CKCU_APBPCSR1 | 24),
  #endif
  #if (LIBCFG_SCTM1)
  CKCU_PCLK_SCTM1    = (CKCU_APBPCSR1 | 26),
  #endif
  #if (LIBCFG_SCTM2)
  CKCU_PCLK_SCTM2    = (CKCU_APBPCSR1 | 28),
  #endif
  #if (LIBCFG_SCTM3)
  CKCU_PCLK_SCTM3    = (CKCU_APBPCSR1 | 30),
  #endif
  #if (LIBCFG_AFE0006)
  CKCU_PCLK_AFE      = (CKCU_APBPCSR2 | 0),
  #endif
  #if (LIBCFG_DACDUAL16) || (LIBCFG_DAC0)
  CKCU_PCLK_DAC0     = (CKCU_APBPCSR2 | 2),
  #endif
  #if (LIBCFG_LEDC)
  CKCU_PCLK_LEDC     = (CKCU_APBPCSR2 | 6),
  #endif
  #if (LIBCFG_MIDI)
  CKCU_PCLK_MIDI     = (CKCU_APBPCSR2 | 8),
  #endif
  #if (LIBCFG_TKEY)
  CKCU_PCLK_TKEY     = (CKCU_APBPCSR2 | 10),
  #endif
  #if (LIBCFG_SLED0)
  CKCU_PCLK_SLED0    = (CKCU_APBPCSR2 | 12),
  #endif
  #if (LIBCFG_SLED1)
  CKCU_PCLK_SLED1    = (CKCU_APBPCSR2 | 14),
  #endif
  #if (LIBCFG_PWM0)
  CKCU_PCLK_PWM0     = (CKCU_APBPCSR2 | 16),
  #endif
  #if (LIBCFG_PWM1)
  CKCU_PCLK_PWM1     = (CKCU_APBPCSR2 | 18),
  #endif
  #if (LIBCFG_PWM2)
  CKCU_PCLK_PWM2     = (CKCU_APBPCSR2 | 20),
  #endif
  #if (LIBCFG_CAN0)
  CKCU_PCLK_CAN0     = (CKCU_APBPCSR2 | 20),
  #endif
  #if (LIBCFG_DAC1)
  CKCU_PCLK_DAC1     = (CKCU_APBPCSR2 | 24),
  #endif
} CKCU_PeripPrescaler_TypeDef;

#define CKCU_PCLK_ADC CKCU_PCLK_ADC0
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup CKCU_Exported_Constants CKCU exported constants
  * @{
  */

/* Definitions of clock ready flag                                                                          */
#if (LIBCFG_CKCU_USB_PLL)
#define CKCU_FLAG_USBPLLRDY     (1UL)
#endif
#if (!LIBCFG_NO_PLL)
#define CKCU_FLAG_PLLRDY        (1UL << 1)
#endif
#define CKCU_FLAG_HSERDY        (1UL << 2)
#define CKCU_FLAG_HSIRDY        (1UL << 3)
#if (LIBCFG_LSE)
#define CKCU_FLAG_LSERDY        (1UL << 4)
#endif
#define CKCU_FLAG_LSIRDY        (1UL << 5)

#define IS_CKCU_FLAG(FLAG)      (((FLAG & 0xFFFFFFC0) == 0) && (FLAG != 0))

/* Definitions of clock interrupt & flag                                                                    */
#define CKCU_INT_CKS            (1UL)
#define IS_CKCU_INT_FLAG(FLAG)  (FLAG == CKCU_INT_CKS)

#define CKCU_INT_CKSIE          (1UL << 16)
#define IS_CKCU_INT(INT)        (((INT & 0xFFFEFFFF) == 0) && (INT != 0))

#if (!LIBCFG_NO_PLL)
/* Definitions of PLL frequency                                                                             */
#define CKCU_PLL_4M_48M         ((12UL << 23) | (0UL << 21))
#define CKCU_PLL_4M_40M         ((10UL << 23) | (0UL << 21))
#define CKCU_PLL_8M_48M         (( 6UL << 23) | (0UL << 21))
#define CKCU_PLL_8M_40M         (( 5UL << 23) | (0UL << 21))
#define CKCU_PLL_8M_32M         (( 4UL << 23) | (0UL << 21))
#define CKCU_PLL_12M_48M        (( 4UL << 23) | (0UL << 21))
#define CKCU_PLL_16M_48M        (( 3UL << 23) | (0UL << 21))

#if (LIBCFG_CKCU_SYS_CK_60M)
#define CKCU_PLL_4M_60M         ((0UL << 28) | (15UL << 23) | (0UL << 21))
#define CKCU_PLL_8M_60M         ((1UL << 28) | (15UL << 23) | (0UL << 21))
#define CKCU_PLL_12M_60M        ((0UL << 28) | ( 5UL << 23) | (0UL << 21))
#define CKCU_PLL_16M_56M        ((1UL << 28) | ( 7UL << 23) | (0UL << 21))
#endif

#define IS_PLL_CFG(CFG)         (((CFG & 0xE81FFFFF) == 0x0) && (CFG != 0))
#endif

#if (LIBCFG_CKCU_USB_PLL)
/* Definitions of USBPLL frequency                                                                          */
#if (LIBCFG_CKCU_USB_PLL_96M)
#define CKCU_USBPLL_4M_96M      ((24UL << 7) | (0UL << 5))
#define CKCU_USBPLL_8M_96M      ((12UL << 7) | (0UL << 5))
#define CKCU_USBPLL_12M_96M     (( 8UL << 7) | (0UL << 5))
#define CKCU_USBPLL_16M_96M     (( 6UL << 7) | (0UL << 5))
#else
#define CKCU_USBPLL_4M_48M      ((12UL << 7) | (0UL << 5))
#define CKCU_USBPLL_8M_48M      (( 6UL << 7) | (0UL << 5))
#define CKCU_USBPLL_12M_48M     (( 4UL << 7) | (0UL << 5))
#define CKCU_USBPLL_16M_48M     (( 3UL << 7) | (0UL << 5))
#endif

#define IS_USBPLL_CFG(CFG)      (((CFG & 0xFFFFF81F) == 0x0) && (CFG != 0))
#endif




/* Definitions of MCU debug control                                                                         */
#define CKCU_DBG_SLEEP          (1UL)
#define CKCU_DBG_DEEPSLEEP1     (1UL << 1)
#define CKCU_DBG_POWERDOWN      (1UL << 2)
#define CKCU_DBG_WDT_HALT       (1UL << 3)

#if (LIBCFG_MCTM0)
#define CKCU_DBG_MCTM0_HALT     (1UL << 4)
#endif

#if (!LIBCFG_NO_GPTM0)
#define CKCU_DBG_GPTM0_HALT     (1UL << 6)
#endif

#if (LIBCFG_GPTM1)
#define CKCU_DBG_GPTM1_HALT     (1UL << 7)
#endif

#if (!LIBCFG_NO_USART0)
#define CKCU_DBG_USART0_HALT    (1UL << 8)
#endif

#if (LIBCFG_USART1)
#define CKCU_DBG_USART1_HALT    (1UL << 9)
#endif

#define CKCU_DBG_SPI0_HALT      (1UL << 10)

#if (LIBCFG_SPI1)
#define CKCU_DBG_SPI1_HALT      (1UL << 11)
#endif

#if defined(USE_HT32F0006) || defined(USE_HT32F61244_45)
#define CKCU_DBG_QSPI_HALT      (1UL << 11)
#endif

#define CKCU_DBG_I2C0_HALT      (1UL << 12)

#if (LIBCFG_I2C1)
#define CKCU_DBG_I2C1_HALT      (1UL << 13)
#endif

#define CKCU_DBG_DEEPSLEEP2     (1UL << 14)

#if (LIBCFG_SCI0)
#define CKCU_DBG_SCI0_HALT      (1UL << 15)
#endif

#define CKCU_DBG_BFTM0_HALT     (1UL << 16)

#if (LIBCFG_BFTM1)
#define CKCU_DBG_BFTM1_HALT     (1UL << 17)
#endif

#define CKCU_DBG_UART0_HALT     (1UL << 18)

#if (LIBCFG_UART1)
#define CKCU_DBG_UART1_HALT     (1UL << 19)
#endif

#if (LIBCFG_SCI1)
#define CKCU_DBG_SCI1_HALT      (1UL << 21)
#endif

#if (LIBCFG_SCTM0)
#define CKCU_DBG_SCTM0_HALT     (1UL << 22)
#endif

#if (LIBCFG_SCTM1)
#define CKCU_DBG_SCTM1_HALT     (1UL << 23)
#endif

#if (LIBCFG_SCTM2)
#define CKCU_DBG_SCTM2_HALT     (1UL << 24)
#endif

#if (LIBCFG_SCTM3)
#define CKCU_DBG_SCTM3_HALT     (1UL << 25)
#endif

#if (LIBCFG_CAN0)
#define CKCU_DBG_CAN0_HALT      (1UL << 26)
#endif

#if (LIBCFG_UART2)
#define CKCU_DBG_UART2_HALT     (1UL << 26)
#endif

#if (LIBCFG_UART3)
#define CKCU_DBG_UART3_HALT     (1UL << 27)
#endif

#if (LIBCFG_I2C2)
#define CKCU_DBG_I2C2_HALT      (1UL << 28)
#endif

#if (LIBCFG_PWM2)
#define CKCU_DBG_PWM2_HALT      (1UL << 29)
#endif

#if defined(USE_HT32F52357_67)
#define CKCU_DBG_QSPI_HALT      (1UL << 29)
#endif

#if (LIBCFG_PWM0)
#define CKCU_DBG_PWM0_HALT      (1UL << 30)
#endif

#if (LIBCFG_PWM1)
#define CKCU_DBG_PWM1_HALT      (1UL << 31)
#endif

#define IS_CKCU_DBG(MODE)       (((MODE & ~(0xFFEFFFDF)) == 0) && (MODE != 0))

/* Definitions of AHB clock control                                                                         */
#define CKCU_AHBEN_SLEEP_FMC    (1UL)
#define CKCU_AHBEN_SLEEP_SRAM   (1UL << 2)
#define CKCU_AHBEN_SLEEP_BM     (1UL << 5)
#define CKCU_AHBEN_SLEEP_APB0   (1UL << 6)

#define IS_CKCU_SLEEP_AHB(PERIPH)  (((PERIPH & 0xFFFFFF9A) == 0) && (PERIPH != 0))

/* Definitions of HSI Ready Counter Value                                                                   */
#if (LIBCFG_CKCU_HSIRDYCR)
#define IS_COUNTER_VALUE(VALUE) ((VALUE) < 0x20)
#endif
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup CKCU_Exported_Functions CKCU exported functions
  * @{
  */
void CKCU_DeInit(void);

void CKCU_HSICmd(ControlStatus Cmd);
void CKCU_HSECmd(ControlStatus Cmd);
bool CKCU_IS_HSI_USED(CKCU_HSIST_TypeDef Target);
bool CKCU_IS_HSE_USED(CKCU_HSEST_TypeDef Target);
FlagStatus CKCU_GetClockReadyStatus(u32 CKCU_FLAG);
ErrStatus CKCU_WaitHSEReady(void);

ErrStatus CKCU_SysClockConfig(CKCU_SW_TypeDef CLKSRC);
u32 CKCU_GetSysClockSource(void);

void CKCU_PeripClockConfig(CKCU_PeripClockConfig_TypeDef Clock, ControlStatus Cmd);

#if (LIBCFG_NO_PLL)
#else
void CKCU_PLLInit(CKCU_PLLInitTypeDef *PLL_InitStruct);
void CKCU_PLLCmd(ControlStatus Cmd);
bool CKCU_IS_PLL_USED(CKCU_PLLST_TypeDef Target);
#endif

#if (LIBCFG_CKCU_USB_PLL)
void CKCU_USBPLLInit(CKCU_PLLInitTypeDef *USBPLL_InitStruct);
void CKCU_USBPLLCmd(ControlStatus Cmd);
void CKCU_USBClockConfig(CKCU_USBSRC_TypeDef USBSRC);
#endif

#if (LIBCFG_CKCU_LCD_SRC)
void CKCU_LCDClockConfig(CKCU_LCDSRC_TypeDef LCDSRC);
#endif

#if (LIBCFG_CKCU_MCTM_SRC)
void CKCU_MCTMClockConfig(CKCU_MCTMSRC_TypeDef CKCU_MCTMSRC_x);
#endif

void CKCU_SleepClockConfig(u32 CKCU_CLK, ControlStatus Cmd);

void CKCU_SetHCLKPrescaler(CKCU_SYSCLKDIV_TypeDef HCLKPRE);
void CKCU_SetCKREFPrescaler(CKCU_CKREFPRE_TypeDef CKREFPRE);
void CKCU_SetADCnPrescaler(CKCU_ADCPRE_ADCn_TypeDef CKCU_ADCPRE_ADCn, CKCU_ADCPRE_TypeDef CKCU_ADCPRE_DIVn);
#define CKCU_SetADCPrescaler(DIV) CKCU_SetADCnPrescaler(CKCU_ADCPRE_ADC0, DIV)

#if (LIBCFG_MIDI)
void CKCU_SetMIDIPrescaler(CKCU_MIDIPRE_TypeDef MIDIPRE);
#endif

#if (!LIBCFG_CKCU_NO_APB_PRESCALER)
void CKCU_SetPeripPrescaler(CKCU_PeripPrescaler_TypeDef Perip, CKCU_APBCLKPRE_TypeDef PCLKPRE);
#endif

void CKCU_GetClocksFrequency(CKCU_ClocksTypeDef* CKCU_Clk);
u32 CKCU_GetPLLFrequency(void);
u32 CKCU_GetPeripFrequency(CKCU_PeripPrescaler_TypeDef Perip);

void CKCU_CKMCmd(ControlStatus Cmd);
void CKCU_PSRCWKUPCmd(ControlStatus Cmd);

#if (!LIBCFG_CKCU_NO_LPCR)
void CKCU_BKISOCmd(ControlStatus Cmd);
#endif

void CKCU_CKOUTConfig(CKCU_CKOUTInitTypeDef *CKOUTInit);
void CKCU_MCUDBGConfig(u32 CKCU_DBGx, ControlStatus Cmd);

void CKCU_IntConfig(u32 CKCU_INT, ControlStatus Cmd);
FlagStatus CKCU_GetIntStatus(u32 CKCU_INT);
void CKCU_ClearIntFlag(u32 CKCU_INT);

#if (((LIBCFG_LSE) || (LIBCFG_USBD)) && (!LIBCFG_CKCU_NO_AUTO_TRIM))
#if (LIBCFG_CKCU_ATM_V01)
void CKCU_ATCInit(CKCU_ATCInitTypeDef* ATC_InitStruct);
#endif
void CKCU_HSIAutoTrimClkConfig(CKCU_ATC_TypeDef CLKSRC);
void CKCU_HSIAutoTrimCmd(ControlStatus Cmd);
bool CKCU_HSIAutoTrimIsReady(void);
#endif

#if (LIBCFG_CKCU_HSIRDYCR)
void CKCU_Set_HSIReadyCounter(u8 value);
#endif
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
