/*********************************************************************************************************//**
 * @file    ht32f5xxxx_lib.h
 * @version $Rev:: 7319         $
 * @date    $Date:: 2023-10-28 #$
 * @brief   The header file includes all the header files of the libraries.
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
#ifndef __HT32F5XXXX_LIB_H
#define __HT32F5XXXX_LIB_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Settings ------------------------------------------------------------------------------------------------*/
#define HT32_FWLIB_VER                  (0x01009001)
#define HT32_FWLIB_SVN                  (0x7446)

#if defined(USE_HT32F52220_30)
  #include "ht32f52220_30_libcfg.h"
#endif
#if defined(USE_HT32F52231_41)
  #include "ht32f52231_41_libcfg.h"
#endif
#if defined(USE_HT32F52331_41)
  #include "ht32f52331_41_libcfg.h"
#endif
#if defined(USE_HT32F52342_52)
  #include "ht32f52342_52_libcfg.h"
#endif
#if defined(USE_HT32F52243_53)
  #include "ht32f52243_53_libcfg.h"
#endif
#if defined(USE_HT32F5826)
  #include "ht32f5826_libcfg.h"
#endif
#if defined(USE_HT32F0008)
  #include "ht32f0008_libcfg.h"
#endif
#if defined(USE_HT32F50220_30)
  #include "ht32f50220_30_libcfg.h"
#endif
#if defined(USE_HT32F50231_41)
  #include "ht32f50231_41_libcfg.h"
#endif
#if defined(USE_HT32F52344_54)
  #include "ht32f52344_54_libcfg.h"
#endif
#if defined(USE_HT32F0006)
  #include "ht32f0006_libcfg.h"
#endif
#if defined(USE_HT32F52357_67)
  #include "ht32f52357_67_libcfg.h"
#endif
#if defined(USE_HT32F54231_41)
  #include "ht32f54231_41_libcfg.h"
#endif
#if defined(USE_HT32F54243_53)
  #include "ht32f54243_53_libcfg.h"
#endif
#if defined(USE_HT32F57342_52)
  #include "ht32f57342_52_libcfg.h"
#endif
#if defined(USE_HT32F57331_41)
  #include "ht32f57331_41_libcfg.h"
#endif
#if defined(USE_HT32F50343)
  #include "ht32f50343_libcfg.h"
#endif
#if defined(USE_HT32F65230_40)
  #include "ht32f65230_40_libcfg.h"
#endif
#if defined(USE_HT32F65232)
  #include "ht32f65232_libcfg.h"
#endif
#if defined(USE_HT32F61141)
  #include "ht32f61141_libcfg.h"
#endif
#if defined(USE_HT32F61244_45)
  #include "ht32f61244_45_libcfg.h"
#endif
#if defined(USE_HT32F50020_30)
  #include "ht32f50020_30_libcfg.h"
#endif
#if defined(USE_HT32F67041_51)
  #include "ht32f67041_51_libcfg.h"
#endif
#if defined(USE_HT32F50442_52)
  #include "ht32f50442_52_libcfg.h"
#endif
#if defined(USE_HT32F50431_41)
  #include "ht32f50431_41_libcfg.h"
#endif
#if defined(USE_HT32F53242_52)
  #include "ht32f53242_52_libcfg.h"
#endif
#if defined(USE_HT32F53231_41)
  #include "ht32f53231_41_libcfg.h"
#endif
#if defined(USE_HT32F66242)
  #include "ht32f66242_libcfg.h"
#endif
#if defined(USE_HT32F66246)
  #include "ht32f66246_libcfg.h"
#endif
#if defined(USE_HT32F52234_44)
  #include "ht32f52234_44_libcfg.h"
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include "ht32f5xxxx_conf.h"

#if (HT32_LIB_DEBUG == 1)
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *   which reports the name of the source file and the source
  *   line number of the call that failed.
  *   If expr is true, it returns no value.
  * @retval None
  */
#define Assert_Param(expr) ((expr) ? (void)0 : assert_error((u8 *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- ------------------------------*/
void assert_error(u8* file, u32 line);
#else

#define Assert_Param(expr) ((void)0)

#endif /* DEBUG --------------------------------------------------------------------------------------------*/


#if _ADC
  #if defined(USE_HT32F65230_40) || defined(USE_HT32F65232) || defined(USE_HT32F66242) || defined(USE_HT32F66246)
  #include "ht32f65xxx_66xxx_adc.h"
  #else
  #include "ht32f5xxxx_adc.h"
  #endif
#endif

#if _AES && LIBCFG_AES
  #include "ht32f5xxxx_aes.h"
#endif

#if _BFTM
  #include "ht32f5xxxx_bftm.h"
#endif

#if _CAN && LIBCFG_CAN0
  #include "ht32f5xxxx_can.h"
#endif

#if _CKCU
  #include "ht32f5xxxx_ckcu.h"
#endif

#if _CMP && LIBCFG_CMP
  #include "ht32f5xxxx_cmp.h"
#endif

#if _CRC && LIBCFG_CRC
  #include "ht32f5xxxx_crc.h"
#endif

#if _DAC && (LIBCFG_DAC0 || LIBCFG_DAC1)
  #include "ht32f5xxxx_dac.h"
#endif

#if _DAC && LIBCFG_DACDUAL16
  #include "ht32f5xxxx_dac_dual16.h"
#endif

#if _DIV && LIBCFG_DIV
  #include "ht32f5xxxx_div.h"
#endif

#if _EBI && LIBCFG_EBI
  #include "ht32f5xxxx_ebi.h"
#endif

#if _EXTI
  #include "ht32f5xxxx_exti.h"
#endif

#if _FLASH
  #include "ht32f5xxxx_flash.h"
#endif

#if _GPIO
  #include "ht32f5xxxx_gpio.h"
#endif

#if _GPTM
  #include "ht32f5xxxx_tm_type.h"
  #include "ht32f5xxxx_tm.h"
#endif

#if _I2C
  #include "ht32f5xxxx_i2c.h"
#endif

#if _I2S && LIBCFG_I2S
  #include "ht32f5xxxx_i2s.h"
#endif

#if _LCD && LIBCFG_LCD
  #include "ht32f5xxxx_lcd.h"
#endif

#if _LEDC && LIBCFG_LEDC
  #include "ht32f5xxxx_ledc.h"
#endif

#if _MCTM && LIBCFG_MCTM0
  #include "ht32f5xxxx_tm_type.h"
  #include "ht32f5xxxx_tm.h"
  #include "ht32f5xxxx_mctm.h"
#endif

#if _MIDI && LIBCFG_MIDI
  #include "ht32f5xxxx_midi.h"
#endif

#if _OPA && LIBCFG_OPA
  #if defined(USE_HT32F65230_40) || defined(USE_HT32F65232)
  #include "ht32f65xxx_66xxx_opa.h"
  #else
  #endif
#endif

#if _PDMA && LIBCFG_PDMA
  #include "ht32f5xxxx_pdma.h"
#endif

#if _PWRCU
  #include "ht32f5xxxx_pwrcu.h"
#endif

#if _RSTCU
  #include "ht32f5xxxx_rstcu.h"
#endif

#if _RTC
  #include "ht32f5xxxx_rtc.h"
#endif

#if _SCI && LIBCFG_SCI0
  #include "ht32f5xxxx_sci.h"
#endif

#if _SCTM
  #include "ht32f5xxxx_tm_type.h"
  #include "ht32f5xxxx_tm.h"
#endif

#if _SLED && LIBCFG_SLED0
  #include "ht32f5xxxx_sled.h"
#endif

#if _SPI
  #include "ht32f5xxxx_spi.h"
#endif

#if _TKEY && LIBCFG_TKEY
  #include "ht32f5xxxx_tkey.h"
#endif

#if _USART
  #include "ht32f5xxxx_usart.h"
#endif

#if _USB && LIBCFG_USBD
  #include "ht32f5xxxx_usbd.h"
#endif

#if _WDT
  #include "ht32f5xxxx_wdt.h"
#endif

#if _MISC
  #include "ht32_cm0plus_misc.h"
#endif

#if _SERIAL
  #include "ht32_serial.h"
#endif

#if _SWDIV
  #include "ht32_div.h"
#endif

#if _SWRAND
  #include "ht32_rand.h"
#endif

#if (_RETARGET)
  #if defined (__GNUC__)
    #undef getchar
    #define getchar SERIAL_GetChar
  #endif
#endif

#ifdef HTCFG_TIME_IPSEL
#include "ht32_time.h"
#endif

#ifdef __cplusplus
}
#endif

#endif
