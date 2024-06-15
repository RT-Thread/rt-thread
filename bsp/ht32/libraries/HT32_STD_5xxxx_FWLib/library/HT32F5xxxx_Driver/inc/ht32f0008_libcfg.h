/*********************************************************************************************************//**
 * @file    ht32f0008_libcfg.h
 * @version $Rev:: 6189         $
 * @date    $Date:: 2022-09-27 #$
 * @brief   The library configuration file.
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
#ifndef __HT32F0008_LIBCFG_H
#define __HT32F0008_LIBCFG_H

/* Settings ------------------------------------------------------------------------------------------------*/

#if !defined(USE_MEM_HT32F0008)
#define USE_MEM_HT32F0008
#endif

#define LIBCFG_MAX_SPEED                  (60000000)

#define LIBCFG_FLASH_PAGESIZE             (1024)

#ifdef USE_MEM_HT32F0008
  #define LIBCFG_FLASH_SIZE               (LIBCFG_FLASH_PAGESIZE * 63)
  #define LIBCFG_RAM_SIZE                 (1024 * 16)
  #define LIBCFG_CHIPNAME                 (0x0008)
#endif

#define LIBCFG_PDMA                       (1)

#define LIBCFG_BFTM1                      (1)

#define LIBCFG_LSE                        (1)
#define LIBCFG_USBD                       (1)
#define LIBCFG_CRC                        (1)
#define LIBCFG_DIV                        (1)
#define LIBCFG_AES                        (1)

#define LIBCFG_GPIOC                      (1)
#define LIBCFG_GPIOF                      (1)

#define LIBCFG_NO_ADC                     (1)
#define LIBCFG_PWM0                       (1)
#define LIBCFG_PWM1                       (1)
#define LIBCFG_AFIO_PWM_MODE4             (1)
#define LIBCFG_CKCU_USB_PLL               (1)
#define LIBCFG_CKCU_SYS_CK_60M            (1)
#define LIBCFG_FMC_PREFETCH               (1)
#define LIBCFG_FMC_WAIT_STATE_2           (1)
#define LIBCFG_CKCU_REFCLK_EXT_PIN        (1)
#define LIBCFG_CKCU_ATM_V01               (1)
#define LIBCFG_CKCU_PLLSRCDIV             (1)
#define LIBCFG_GPIO_DISABLE_DEBUG_PORT    (1)
#define LIBCFG_AES_SWAP                   (1)

#endif
