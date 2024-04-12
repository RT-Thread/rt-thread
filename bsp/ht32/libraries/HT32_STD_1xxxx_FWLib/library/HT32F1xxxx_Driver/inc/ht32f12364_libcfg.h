/*********************************************************************************************************//**
 * @file    ht32f12364_libcfg.h
 * @version $Rev:: 2805         $
 * @date    $Date:: 2022-12-01 #$
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
#ifndef __HT32F12364_LIBCFG_H
#define __HT32F12364_LIBCFG_H

/* Settings ------------------------------------------------------------------------------------------------*/

#if !defined(USE_MEM_HT32F12364)
#define USE_MEM_HT32F12364
#endif

#define LIBCFG_MAX_SPEED                  (72000000)

#define LIBCFG_FLASH_PAGESIZE             (1024)

#ifdef USE_MEM_HT32F12364
  #define LIBCFG_FLASH_SIZE               (LIBCFG_FLASH_PAGESIZE * 255)
  #define LIBCFG_RAM_SIZE                 (1024 * 128)
  #define LIBCFG_CHIPNAME                 (0x12364)
#endif

#define LIBCFG_ADC_V01                    (1)
#define LIBCFG_ADC_IVREF                  (1)
#define LIBCFG_AES                        (1)
#define LIBCFG_CKCU_APBPCSR2              (1)
#define LIBCFG_CKCU_ADCPRE_DIV5           (1)
#define LIBCFG_CKCU_ATM_V01               (1)
#define LIBCFG_CKCU_USB_PLL               (1)
#define LIBCFG_EBI_V01                    (1)
#define LIBCFG_FLASH_2PAGE_PER_WPBIT      (1)
#define LIBCFG_FMC_WAIT_STATE_3           (1)
#define LIBCFG_GPIOF                      (1)
#define LIBCFG_NO_ADC_CH8_15              (1)
#define LIBCFG_NO_BACK_DOMAIN             (1)
#define LIBCFG_NO_CKCU_USBPRE             (1)
#define LIBCFG_NO_CMP_TRIG_ADC            (1)
#define LIBCFG_NO_CMP_HPTRIG_ADC          (1)
#define LIBCFG_NO_GPTM1                   (1)
#define LIBCFG_NO_I2S                     (1)
#define LIBCFG_NO_MCTM0                   (1)
#define LIBCFG_NO_MCTM1                   (1)
#define LIBCFG_NO_PDMA_CH6_11             (1)
#define LIBCFG_NO_USART1                  (1)
#define LIBCFG_PDMA_V01                   (1)
#define LIBCFG_PWM0                       (1)
#define LIBCFG_PWRCU_LVDS_17_31           (1)
#define LIBCFG_SCI0                       (1)
#define LIBCFG_SCTM0                      (1)
#define LIBCFG_SCTM1                      (1)
#define LIBCFG_SPI_CLK_PRE_V01            (1)

#endif
