/*********************************************************************************************************//**
 * @file    ht32f1xxxx_lib.h
 * @version $Rev:: 2971         $
 * @date    $Date:: 2023-10-25 #$
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
#ifndef __HT32F1XXXX_LIB_H
#define __HT32F1XXXX_LIB_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Settings ------------------------------------------------------------------------------------------------*/
#define HT32_FWLIB_VER                  (0x01004001)
#define HT32_FWLIB_SVN                  (0x2982)

#if defined(USE_HT32F1653_54)
  #include "ht32f1653_54_libcfg.h"
#endif
#if defined(USE_HT32F1655_56)
  #include "ht32f1655_56_libcfg.h"
#endif
#if defined(USE_HT32F12365_66)
  #include "ht32f12365_66_libcfg.h"
#endif
#if defined(USE_HT32F12345)
  #include "ht32f12345_libcfg.h"
#endif
#if defined(USE_HT32F12364)
  #include "ht32f12364_libcfg.h"
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include "ht32f1xxxx_conf.h"

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
  #include "ht32f1xxxx_adc.h"
#endif

#if _AES && LIBCFG_AES
  #include "ht32f1xxxx_aes.h"
#endif

#if _BFTM
  #include "ht32f1xxxx_bftm.h"
#endif

#if _CKCU
  #include "ht32f1xxxx_ckcu.h"
#endif

#if _CMP_OPA && LIBCFG_CMP_OPA
  #include "ht32f1xxxx_cmp_op.h"
#endif

#if _CMP && (!LIBCFG_CMP_OPA)
  #include "ht32f1xxxx_cmp.h"
#endif

#if _CRC
  #include "ht32f1xxxx_crc.h"
#endif

#if _CSIF && LIBCFG_CSIF
  #include "ht32f2xxxx_csif.h"
#endif

#if _EBI
  #include "ht32f1xxxx_ebi.h"
#endif

#if _EXTI
  #include "ht32f1xxxx_exti.h"
#endif

#if _FLASH
  #include "ht32f1xxxx_flash.h"
#endif

#if _GPIO
  #include "ht32f1xxxx_gpio.h"
#endif

#if _GPTM
  #include "ht32f1xxxx_tm_type.h"
  #include "ht32f1xxxx_tm.h"
#endif

#if _I2C
  #include "ht32f1xxxx_i2c.h"
#endif

#if _I2S
  #include "ht32f1xxxx_i2s.h"
#endif

#if _MCTM && (!LIBCFG_NO_MCTM0)
  #include "ht32f1xxxx_tm_type.h"
  #include "ht32f1xxxx_tm.h"
  #include "ht32f1xxxx_mctm.h"
#endif

#if _PDMA
  #include "ht32f1xxxx_pdma.h"
#endif

#if _PWRCU
  #include "ht32f1xxxx_pwrcu.h"
#endif

#if _PWM
  #include "ht32f1xxxx_tm_type.h"
  #include "ht32f1xxxx_tm.h"
#endif

#if _RSTCU
  #include "ht32f1xxxx_rstcu.h"
#endif

#if _RTC
  #include "ht32f1xxxx_rtc.h"
#endif

#if _SCI && LIBCFG_SCI0
  #include "ht32f1xxxx_sci.h"
#endif

#if _SDIO && LIBCFG_SDIO
  #include "ht32f1xxxx_sdio.h"
#endif

#if _SPI
  #include "ht32f1xxxx_spi.h"
#endif

#if _SCTM
  #include "ht32f1xxxx_tm_type.h"
  #include "ht32f1xxxx_tm.h"
#endif

#if _USART
  #include "ht32f1xxxx_usart.h"
#endif

#if _USB
  #include "ht32f1xxxx_usbd.h"
#endif

#if _WDT
  #include "ht32f1xxxx_wdt.h"
#endif

#if _MISC
  #include "ht32_cm3_misc.h"
#endif

#if _SERIAL
  #include "ht32_serial.h"
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
