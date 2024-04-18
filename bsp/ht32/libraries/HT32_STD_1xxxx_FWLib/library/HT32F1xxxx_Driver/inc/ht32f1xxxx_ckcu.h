/*********************************************************************************************************//**
 * @file    ht32f1xxxx_ckcu.h
 * @version $Rev:: 2974         $
 * @date    $Date:: 2023-10-30 #$
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
#ifndef __HT32F1XXXX_CKCU_H
#define __HT32F1XXXX_CKCU_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @addtogroup CKCU
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup CKCU_Exported_Types CKCU exported types
  * @{
  */

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

/**
 * @brief Enumeration of PLL clock source.
 */
typedef enum
{
  CKCU_PLLSRC_HSE = 0,
  CKCU_PLLSRC_HSI
} CKCU_PLLSRC_TypeDef;

#if (LIBCFG_CKCU_USART_PRESCALER)
/**
 * @brief Enumeration of CK_USART prescaler.
 */
typedef enum
{
  CKCU_URPRE_DIV1 = 0,
  CKCU_URPRE_DIV2
} CKCU_URPRE_TypeDef;
#endif

#if (!LIBCFG_NO_CKCU_USBPRE)
/**
 * @brief Enumeration of CK_USB prescaler.
 */
typedef enum
{
  CKCU_USBPRE_DIV1 = 0,
  CKCU_USBPRE_DIV2,
#if (LIBCFG_CKCU_USB_DIV3)
  CKCU_USBPRE_DIV3
#endif
} CKCU_USBPRE_TypeDef;
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

/**
 * @brief Enumeration of WDT clock source.
 */
typedef enum
{
  CKCU_WDTSRC_LSI = 0,
  CKCU_WDTSRC_LSE
} CKCU_WDTSRC_TypeDef;



#if (!LIBCFG_CKCU_HSI_NO_AUTOTRIM)
/**
 * @brief Enumeration of HSI auto-trim clock source.
 */
typedef enum
{
  CKCU_ATC_LSE = 0,
  CKCU_ATC_USB = 1,
#if (LIBCFG_CKCU_AUTOTRIM_NOCKIN)
#else
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
#if (LIBCFG_CKCU_SYSCLK_DIV8_ONLY)
#else
  CKCU_SYSCLK_DIV16,
  CKCU_SYSCLK_DIV32
#endif
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
#if (LIBCFG_CKCU_ADCPRE_DIV5)
  CKCU_ADCPRE_DIV5
#else
  CKCU_ADCPRE_DIV6
#endif
} CKCU_ADCPRE_TypeDef;

/**
 * @brief Enumeration of CK_ADCn.
 */
typedef enum
{
  CKCU_ADCPRE_ADC0 = 16,
} CKCU_ADCPRE_ADCn_TypeDef;

/**
 * @brief Enumeration of System clock source.
 */
typedef enum
{
  CKCU_SW_PLL = 1,
  CKCU_SW_HSE = 2,
  CKCU_SW_HSI = 3,
#if (LIBCFG_CKCU_NO_HCLK_LOW_SPEED)
#else
  CKCU_SW_LSE = 6,
  CKCU_SW_LSI = 7
#endif
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
  CKCU_CKOUTSRC_LSECK       = 5,
  CKCU_CKOUTSRC_LSICK       = 6
} CKCU_CKOUTSRC_TypeDef;

/**
 * @brief Enumeration of PLL clock source status.
 */
typedef enum
{
  CKCU_PLLST_SYSCK  = 1,
  CKCU_PLLST_USB    = 4,
  CKCU_PLLST_REFCK  = 8
} CKCU_PLLST_TypeDef;

/**
 * @brief Enumeration of HSI clock source status.
 */
typedef enum
{
  CKCU_HSIST_SYSCK  = 1,
  CKCU_HSIST_PLL    = 2,
  CKCU_HSIST_CKM    = 4
} CKCU_HSIST_TypeDef;

/**
 * @brief Enumeration of HSE clock source status.
 */
typedef enum
{
  CKCU_HSEST_SYSCK  = 1,
  CKCU_HSEST_PLL
} CKCU_HSEST_TypeDef;

/**
 * @brief Definition of CKOUT Init Structure.
 */
typedef struct
{
  CKCU_CKOUTSRC_TypeDef CKOUTSRC;
} CKCU_CKOUTInitTypeDef;

/**
 * @brief Definition of PLL Init Structure.
 */
typedef struct
{
  u32 CFG;
  CKCU_PLLSRC_TypeDef ClockSource;
  ControlStatus BYPASSCmd;
} CKCU_PLLInitTypeDef;

/**
 * @brief Definition of structure for clock frequency.
 */
typedef struct
{
  u32 PLL_Freq;
  u32 SYSCK_Freq;
  u32 HCLK_Freq;
#if (LIBCFG_CKCU_USART_PRESCALER)
  u32 USART_Freq;
#endif
  u32 ADC0_Freq;
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
    unsigned long APB0       :1;    // Bit 6
    unsigned long APB1       :1;    // Bit 7

    unsigned long CSIF       :1;    // Bit 8
    unsigned long CSIFMCLK   :1;    // Bit 9
    unsigned long USBD       :1;    // Bit 10
    unsigned long CKREF      :1;    // Bit 11
    unsigned long EBI        :1;    // Bit 12
    unsigned long CRC        :1;    // Bit 13
    unsigned long SDIO       :1;    // Bit 14
    unsigned long AES        :1;    // Bit 15

    unsigned long PA         :1;    // Bit 16
    unsigned long PB         :1;    // Bit 17
    unsigned long PC         :1;    // Bit 18
    unsigned long PD         :1;    // Bit 19
    unsigned long PE         :1;    // Bit 20
    unsigned long PF         :1;    // Bit 21
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

    /* Definitions of APB0 clock control                                                                    */
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

    unsigned long SCI0       :1;    // Bit 24
    unsigned long I2S        :1;    // Bit 25
    unsigned long            :1;    // Bit 26
    unsigned long SCI1       :1;    // Bit 27
    unsigned long            :1;    // Bit 28
    unsigned long            :1;    // Bit 29
    unsigned long            :1;    // Bit 30
    unsigned long            :1;    // Bit 31

    /* Definitions of APB1 clock control                                                                    */
    unsigned long MCTM0      :1;    // Bit 0
    unsigned long MCTM1      :1;    // Bit 1
    unsigned long            :1;    // Bit 2
    unsigned long            :1;    // Bit 3
    unsigned long WDT        :1;    // Bit 4
    unsigned long            :1;    // Bit 5
    unsigned long BKP        :1;    // Bit 6
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
    unsigned long OPA1       :1;    // Bit 23

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
} CKCU_PeripClockConfig_TypeDef;

#define CKCU_APBPCSR_OFFSET      (5)
#define CKCU_APBPCSR0            (0 << CKCU_APBPCSR_OFFSET)
#define CKCU_APBPCSR1            (1 << CKCU_APBPCSR_OFFSET)
#define CKCU_APBPCSR2            (4 << CKCU_APBPCSR_OFFSET)
typedef enum
{
  CKCU_PCLK_I2C0     = (CKCU_APBPCSR0 | 0),
  CKCU_PCLK_I2C1     = (CKCU_APBPCSR0 | 2),
  CKCU_PCLK_SPI0     = (CKCU_APBPCSR0 | 4),
  CKCU_PCLK_SPI1     = (CKCU_APBPCSR0 | 6),
  CKCU_PCLK_BFTM0    = (CKCU_APBPCSR0 | 12),
  CKCU_PCLK_BFTM1    = (CKCU_APBPCSR0 | 14),
  CKCU_PCLK_MCTM0    = (CKCU_APBPCSR0 | 16),
  CKCU_PCLK_MCTM1    = (CKCU_APBPCSR0 | 18),
  CKCU_PCLK_GPTM0    = (CKCU_APBPCSR0 | 20),
  CKCU_PCLK_GPTM1    = (CKCU_APBPCSR0 | 22),
  CKCU_PCLK_USART0   = (CKCU_APBPCSR0 | 24),
  CKCU_PCLK_USART1   = (CKCU_APBPCSR0 | 26),
  CKCU_PCLK_UART0    = (CKCU_APBPCSR0 | 28),
  CKCU_PCLK_UART1    = (CKCU_APBPCSR0 | 30),
  CKCU_PCLK_AFIO     = (CKCU_APBPCSR1 | 0),
  CKCU_PCLK_EXTI     = (CKCU_APBPCSR1 | 2),
  CKCU_PCLK_ADC      = (CKCU_APBPCSR1 | 4),
  CKCU_PCLK_CMP      = (CKCU_APBPCSR1 | 8),
  CKCU_PCLK_WDTR     = (CKCU_APBPCSR1 | 12),
  CKCU_PCLK_BKPR     = (CKCU_APBPCSR1 | 14),
#if (LIBCFG_SCI0)
  CKCU_PCLK_SCI0     = (CKCU_APBPCSR1 | 16),
#endif
#if (LIBCFG_SCI1)
  CKCU_PCLK_SCI1     = (CKCU_APBPCSR1 | 18),
#endif
  CKCU_PCLK_I2S      = (CKCU_APBPCSR1 | 20),
  CKCU_PCLK_SCTM0    = (CKCU_APBPCSR1 | 24),
  CKCU_PCLK_SCTM1    = (CKCU_APBPCSR1 | 26),
  CKCU_PCLK_PWM0     = (CKCU_APBPCSR2 | 16),
} CKCU_PeripPrescaler_TypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup CKCU_Exported_Constants CKCU exported constants
  * @{
  */

/* Definitions of clock ready flag                                                                          */
#define CKCU_FLAG_PLLRDY        (1UL << 1)
#define CKCU_FLAG_HSERDY        (1UL << 2)
#define CKCU_FLAG_HSIRDY        (1UL << 3)
#define CKCU_FLAG_LSERDY        (1UL << 4)
#define CKCU_FLAG_LSIRDY        (1UL << 5)
#if (LIBCFG_CKCU_USB_PLL)
#define CKCU_FLAG_USBPLLRDY     (1UL)
#define IS_CKCU_FLAG(FLAG)      (((FLAG & 0xFFFFFFC0) == 0) && (FLAG != 0))
#else
#define IS_CKCU_FLAG(FLAG)      (((FLAG & 0xFFFFFFC1) == 0) && (FLAG != 0))
#endif
/* Definitions of clock interrupt & flag                                                                    */
#define CKCU_INT_CKS            (1UL)
#define CKCU_INT_PLLRDY         (1UL << 2)
#define CKCU_INT_HSERDY         (1UL << 3)
#define CKCU_INT_HSIRDY         (1UL << 4)
#define CKCU_INT_LSERDY         (1UL << 5)
#define CKCU_INT_LSIRDY         (1UL << 6)

#if (LIBCFG_CKCU_USB_PLL)
#define CKCU_INT_USBPLLRDY      (1UL << 1)
#define IS_CKCU_INT_FLAG(FLAG)  (((FLAG & 0xFFFFFF80) == 0) && (FLAG != 0))
#else
#define IS_CKCU_INT_FLAG(FLAG)  (((FLAG & 0xFFFFFF82) == 0) && (FLAG != 0))
#endif

#define CKCU_INT_CKSIE          (1UL << 16)
#if (LIBCFG_CKCU_USB_PLL)
#define CKCU_INT_USBPLLRDYIE    (1UL << 17)
#endif
#define CKCU_INT_PLLRDYIE       (1UL << 18)
#define CKCU_INT_HSERDYIE       (1UL << 19)
#define CKCU_INT_HSIRDYIE       (1UL << 20)
#define CKCU_INT_LSERDYIE       (1UL << 21)
#define CKCU_INT_LSIRDYIE       (1UL << 22)

#if (LIBCFG_CKCU_USB_PLL)
#define IS_CKCU_INT(IT)         (((IT & 0xFF80FFFF) == 0) && (IT != 0))
#else
#define IS_CKCU_INT(IT)         (((IT & 0xFF82FFFF) == 0) && (IT != 0))
#endif

#define IS_PLL_CLKSRC(SRC)      ((SRC == CKCU_PLLSRC_HSE) || \
                                 (SRC == CKCU_PLLSRC_HSI))

/* Definitions of PLL frequency                                                                             */
#if (LIBCDG_CKCU_PLL_144M)
#define CKCU_PLL_4M_144M        ((36UL << 23) | (0UL << 21))
#define CKCU_PLL_8M_144M        ((18UL << 23) | (0UL << 21))
#define CKCU_PLL_12M_144M       ((12UL << 23) | (0UL << 21))
#define CKCU_PLL_16M_144M       (( 9UL << 23) | (0UL << 21))
#endif

#define CKCU_PLL_4M_48M         ((12UL << 23) | (0UL << 21))
#define CKCU_PLL_4M_72M         ((18UL << 23) | (0UL << 21))
#define CKCU_PLL_4M_96M         ((24UL << 23) | (0UL << 21))
#define CKCU_PLL_8M_48M         (( 6UL << 23) | (0UL << 21))
#define CKCU_PLL_8M_64M         (( 8UL << 23) | (0UL << 21))
#define CKCU_PLL_8M_72M         (( 9UL << 23) | (0UL << 21))
#define CKCU_PLL_8M_80M         ((10UL << 23) | (0UL << 21))
#define CKCU_PLL_8M_96M         ((12UL << 23) | (0UL << 21))
#define CKCU_PLL_12M_48M        (( 4UL << 23) | (0UL << 21))
#define CKCU_PLL_12M_72M        (( 6UL << 23) | (0UL << 21))
#define CKCU_PLL_12M_96M        (( 8UL << 23) | (0UL << 21))
#define CKCU_PLL_16M_80M        (( 5UL << 23) | (0UL << 21))
#define CKCU_PLL_16M_96M        (( 6UL << 23) | (0UL << 21))

#if (LIBCDG_CKCU_PLL_144M)
#define IS_PLL_CFG(CFG)         (((CFG & 0xE01FFFFF) == 0x0))
#else
#define IS_PLL_CFG(CFG)         (((CFG & 0xF01FFFFF) == 0x0))
#endif

#if (LIBCFG_CKCU_USB_PLL)
/* Definitions of USBPLL frequency                                                                          */
#define CKCU_USBPLL_4M_48M      ((12UL << 7) | (0UL << 5))
#define CKCU_USBPLL_8M_48M      (( 6UL << 7) | (0UL << 5))
#define CKCU_USBPLL_12M_48M     (( 4UL << 7) | (0UL << 5))
#define CKCU_USBPLL_16M_48M     (( 3UL << 7) | (0UL << 5))

#define IS_USBPLL_CFG(CFG)      (((CFG & 0xFFFFF81F) == 0x0))
#endif

/* Definitions of MCU debug control                                                                         */
#define CKCU_DBG_SLEEP          (1UL)
#define CKCU_DBG_DEEPSLEEP1     (1UL << 1)
#define CKCU_DBG_POWERDOWN      (1UL << 2)
#define CKCU_DBG_WDT_HALT       (1UL << 3)
#define CKCU_DBG_MCTM0_HALT     (1UL << 4)
#define CKCU_DBG_MCTM1_HALT     (1UL << 5)
#define CKCU_DBG_GPTM0_HALT     (1UL << 6)
#define CKCU_DBG_GPTM1_HALT     (1UL << 7)
#define CKCU_DBG_USART0_HALT    (1UL << 8)
#define CKCU_DBG_USART1_HALT    (1UL << 9)
#define CKCU_DBG_SPI0_HALT      (1UL << 10)
#define CKCU_DBG_SPI1_HALT      (1UL << 11)
#define CKCU_DBG_I2C0_HALT      (1UL << 12)
#define CKCU_DBG_I2C1_HALT      (1UL << 13)
#define CKCU_DBG_DEEPSLEEP2     (1UL << 14)
#define CKCU_DBG_SCI_HALT       (1UL << 15)
#define CKCU_DBG_BFTM0_HALT     (1UL << 16)
#define CKCU_DBG_BFTM1_HALT     (1UL << 17)
#define CKCU_DBG_UART0_HALT     (1UL << 18)
#define CKCU_DBG_UART1_HALT     (1UL << 19)
#define CKCU_DBG_TRACE_ON       (1UL << 20)

#if (LIBCFG_SCI0)
#define CKCU_DBG_SCI0_HALT      (1UL << 15)
#endif
#if (LIBCFG_SCI1)
#define CKCU_DBG_SCI1_HALT      (1UL << 21)
#endif

#define IS_CKCU_DBG(MODE)       (((MODE & 0xBF200000) == 0) && (MODE != 0))

/* Definitions of AHB clock control                                                                         */
#define CKCU_AHBEN_SLEEP_FMC    (1UL)
#define CKCU_AHBEN_SLEEP_SRAM   (1UL << 2)
#define CKCU_AHBEN_SLEEP_BM     (1UL << 5)
#define CKCU_AHBEN_SLEEP_APB0   (1UL << 6)
#define CKCU_AHBEN_SLEEP_APB1   (1UL << 7)

#define IS_CKCU_SLEEP_AHB(PERIPH)  (((PERIPH & 0xFFFFFF1A) == 0) && (PERIPH != 0))

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

void CKCU_PLLInit(CKCU_PLLInitTypeDef *PLL_InitStruct);
void CKCU_PLLCmd(ControlStatus Cmd);
bool CKCU_IS_PLL_USED(CKCU_PLLST_TypeDef Target);

#if (LIBCFG_CKCU_USB_PLL)
void CKCU_USBPLLInit(CKCU_PLLInitTypeDef *USBPLL_InitStruct);
void CKCU_USBPLLCmd(ControlStatus Cmd);
void CKCU_USBClockConfig(CKCU_USBSRC_TypeDef USBSRC);
#endif

void CKCU_SleepClockConfig(u32 CKCU_CLK, ControlStatus Cmd);

void CKCU_SetHCLKPrescaler(CKCU_SYSCLKDIV_TypeDef HCLKPRE);
void CKCU_SetCKREFPrescaler(CKCU_CKREFPRE_TypeDef CKREFPRE);
void CKCU_SetADCnPrescaler(CKCU_ADCPRE_ADCn_TypeDef CKCU_ADCPRE_ADCn, CKCU_ADCPRE_TypeDef CKCU_ADCPRE_DIVn);
#define CKCU_SetADCPrescaler(DIV) CKCU_SetADCnPrescaler(CKCU_ADCPRE_ADC0, DIV)

#if (LIBCFG_CKCU_USART_PRESCALER)
void CKCU_SetUSARTPrescaler(CKCU_URPRE_TypeDef URPRE);
#endif

#if (!LIBCFG_NO_CKCU_USBPRE)
void CKCU_SetUSBPrescaler(CKCU_USBPRE_TypeDef USBPRE);
#endif

#if (LIBCFG_CKCU_NO_APB_PRESCALER)
#else
void CKCU_SetPeripPrescaler(CKCU_PeripPrescaler_TypeDef Perip, CKCU_APBCLKPRE_TypeDef PCLKPRE);
#endif

void CKCU_GetClocksFrequency(CKCU_ClocksTypeDef* CKCU_Clk);
u32 CKCU_GetPLLFrequency(void);
u32 CKCU_GetPeripFrequency(CKCU_PeripPrescaler_TypeDef Perip);

void CKCU_CKMCmd(ControlStatus Cmd);
void CKCU_PSRCWKUPCmd(ControlStatus Cmd);
void CKCU_BKISOCmd(ControlStatus Cmd);
void CKCU_CKOUTConfig(CKCU_CKOUTInitTypeDef *CKOUTInit);
void CKCU_MCUDBGConfig(u32 CKCU_DBGx, ControlStatus Cmd);

void CKCU_IntConfig(u32 CKCU_INT, ControlStatus Cmd);
FlagStatus CKCU_GetIntStatus(u32 CKCU_INT);
void CKCU_ClearIntFlag(u32 CKCU_INT);

#if (!LIBCFG_CKCU_HSI_NO_AUTOTRIM)
#if (LIBCFG_CKCU_ATM_V01)
void CKCU_ATCInit(CKCU_ATCInitTypeDef* ATC_InitStruct);
void CKCU_HSIAutoTrimAlgorithm(u32 Algo);
void CKCU_HSIAutoTrimFreqTolerance(u32 Tolerance);
#endif
void CKCU_HSIAutoTrimClkConfig(CKCU_ATC_TypeDef CLKSRC);
void CKCU_HSIAutoTrimCmd(ControlStatus Cmd);
bool CKCU_HSIAutoTrimIsReady(void);
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
