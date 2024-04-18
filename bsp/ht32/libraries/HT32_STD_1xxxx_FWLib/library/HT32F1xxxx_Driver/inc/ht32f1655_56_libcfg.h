/*********************************************************************************************************//**
 * @file    ht32f1655_56_libcfg.h
 * @version $Rev:: 2887         $
 * @date    $Date:: 2023-03-02 #$
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
#ifndef __HT32F1655_56_LIBCFG_H
#define __HT32F1655_56_LIBCFG_H

/* Settings ------------------------------------------------------------------------------------------------*/

#if !defined(USE_MEM_HT32F1655) && !defined(USE_MEM_HT32F1656)
#define USE_MEM_HT32F1656
#endif

#define LIBCFG_MAX_SPEED                  (72000000)

#define LIBCFG_FLASH_PAGESIZE             (1024)

#ifdef USE_MEM_HT32F1655
  #define LIBCFG_FLASH_SIZE               (LIBCFG_FLASH_PAGESIZE * 128)
  #define LIBCFG_RAM_SIZE                 (1024 * 32)
  #define LIBCFG_CHIPNAME                 (0x1655)
#endif

#ifdef USE_MEM_HT32F1656
  #define LIBCFG_FLASH_SIZE               (LIBCFG_FLASH_PAGESIZE * 255)
  #define LIBCFG_RAM_SIZE                 (1024 * 32)
  #define LIBCFG_CHIPNAME                 (0x1656)
#endif

#define LIBCFG_CMP_OPA                    (1)
#define LIBCFG_GPIOE                      (1)
#define LIBCFG_SCI0                       (1)

#define LIBCFG_ADC_CH12_15                (1)
#define LIBCFG_ADC_NOENBIT                (1)
#define LIBCFG_CKCU_NO_APB_PRESCALER      (1)
#define LIBCFG_CKCU_CKSWST_LEGACY         (1)
#define LIBCFG_CKCU_HSI_NO_AUTOTRIM       (1)
#define LIBCFG_CKCU_NO_ADCPRE_DIV1        (1)
#define LIBCFG_CKCU_NO_HCLK_LOW_SPEED     (1)
#define LIBCDG_CKCU_PLL_144M              (1)
#define LIBCDG_CKCU_SYSCLK_DIV8_ONLY      (1)
#define LIBCFG_CKCU_USART_PRESCALER       (1)
#define LIBCFG_CKCU_USB_DIV3              (1)
#define LIBCFG_EBI_BYTELAND_ASYNCREADY    (1)
#define LIBCFG_EXTI_8BIT_DEBOUNCE_COUNTER (1)
#define LIBCFG_GPIO_DV_4_8MA_ONLY         (1)
#define LIBCFG_FLASH_2PAGE_PER_WPBIT      (1)
#define LIBCFG_FLASH_HALFCYCYLE           (1)
#define LIBCFG_FLASH_ZWPWESAVING          (1)
#define LIBCFG_NO_CMP_TRIG_ADC            (1)
#define LIBCFG_NO_CMP_HPTRIG_ADC          (1)
#define LIBCFG_PDMA_BLKLEN65536           (1)
#define LIBCFG_PDMA_CH3FIX                (1)
#define LIBCFG_PWRCU_HSI_READY_COUNTER    (1)
#define LIBCFG_PWRCU_LDO_LEGACY           (1)
#define LIBCFG_PWRCU_LVDS_27_35           (1)
#define LIBCFG_RTC_LSI_LOAD_TRIM          (1)
#define LIBCFG_USART_V01                  (1)
#define LIBCFG_WDT_INT                    (1)
#define LIBCFC_WEAK_AF1                   (1)

#endif
