/*********************************************************************************************************//**
 * @file    ht32f53242_52_libcfg.h
 * @version $Rev:: 7265         $
 * @date    $Date:: 2023-10-02 #$
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
#ifndef __HT32F53242_52_LIBCFG_H
#define __HT32F53242_52_LIBCFG_H

/* Settings ------------------------------------------------------------------------------------------------*/

#if !defined(USE_MEM_HT32F53242) && !defined(USE_MEM_HT32F53252)
#define USE_MEM_HT32F53252
#endif

#define LIBCFG_MAX_SPEED                  (60000000)

#define LIBCFG_FLASH_PAGESIZE             (1024)

#ifdef USE_MEM_HT32F53242
  #define LIBCFG_FLASH_SIZE               (LIBCFG_FLASH_PAGESIZE * 64)
  #define LIBCFG_RAM_SIZE                 (1024 * 8)
  #define LIBCFG_CHIPNAME                 (0x53242)
#endif

#ifdef USE_MEM_HT32F53252
  #define LIBCFG_FLASH_SIZE               (LIBCFG_FLASH_PAGESIZE * 127)
  #define LIBCFG_RAM_SIZE                 (1024 * 16)
  #define LIBCFG_CHIPNAME                 (0x53252)
#endif

#define LIBCFG_PDMA                       (1)
#define LIBCFG_ADC_CH8_11                 (1)
#define LIBCFG_CMP                        (1)

#define LIBCFG_BFTM1                      (1)
#define LIBCFG_MCTM0                      (1)
#define LIBCFG_PWM0                       (1)
#define LIBCFG_PWM1                       (1)

#define LIBCFG_LSE                        (1)
#define LIBCFG_EBI                        (1)
#define LIBCFG_LEDC                       (1)
#define LIBCFG_CRC                        (1)
#define LIBCFG_DIV                        (1)
#define LIBCFG_CAN0                       (1)

#define LIBCFG_USART1                     (1)
#define LIBCFG_UART1                      (1)
#define LIBCFG_SPI1                       (1)
#define LIBCFG_I2C1                       (1)

#define LIBCFG_GPIOC                      (1)
#define LIBCFG_GPIOD                      (1)

#define LIBCFG_FMC_WAIT_STATE_2           (1)
#define LIBCFG_FMC_PREFETCH               (1)
#define LIBCFG_CKCU_PLLSRCDIV             (1)
#define LIBCFG_CKCU_AUTO_TRIM_LEGACY      (1)
#define LIBCFG_CKCU_ATM_V01               (1)
#define LIBCFG_CKCU_SYS_CK_60M            (1)
#define LIBCFG_CKCU_REFCLK_EXT_PIN        (1)
#define LIBCFG_PWRCU_VDD_5V               (1)
#define LIBCFG_PWRCU_WAKEUP1              (1)
#define LIBCFG_PWRCU_WAKEUP_V01           (1)
#define LIBCFG_PWRCU_NO_VDDPORF           (1)
#define LIBCFG_PWRCU_NO_PDF               (1)
#define LIBCFG_PWRCU_PORF                 (1)
#define LIBCFG_PWRCU_NO_PD_MODE           (1)
#define LIBCFG_NO_PWRCU_TEST_REG          (1)
#define LIBCFG_LEDC_NO_COM_8_11           (1)
#define LIBCFG_ADC_IVREF                  (1)
#define LIBCFG_ADC_IVREF_LEVEL_TYPE2      (1)
#define LIBCFG_ADC_MVDDA                  (1)
#define LIBCFG_USART_LIN                  (1)
#define LIBCFG_USART_SINGLE_WIRE          (1)
#define LIBCFG_GPIO_SINK_CURREMT_ENHANCED (1)

#endif
