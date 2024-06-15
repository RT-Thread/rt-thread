/*********************************************************************************************************//**
 * @file    ht32f52357_67_libcfg.h
 * @version $Rev:: 7167         $
 * @date    $Date:: 2023-08-25 #$
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
#ifndef __HT32F52357_67_LIBCFG_H
#define __HT32F52357_67_LIBCFG_H

/* Settings ------------------------------------------------------------------------------------------------*/

#if !defined(USE_MEM_HT32F52357) && !defined(USE_MEM_HT32F52367)
#define USE_MEM_HT32F52367
#endif

#define LIBCFG_MAX_SPEED                  (60000000)

#define LIBCFG_FLASH_PAGESIZE             (1024)

#ifdef USE_MEM_HT32F52357
  #define LIBCFG_FLASH_SIZE               (LIBCFG_FLASH_PAGESIZE * 128)
  #define LIBCFG_RAM_SIZE                 (1024 * 16)
  #define LIBCFG_CHIPNAME                 (0x52357)
#endif

#ifdef USE_MEM_HT32F52367
  #define LIBCFG_FLASH_SIZE               (LIBCFG_FLASH_PAGESIZE * 255)
  #define LIBCFG_RAM_SIZE                 (1024 * 32)
  #define LIBCFG_CHIPNAME                 (0x52367)
#endif

#define LIBCFG_ADC_CH8_11                 (1)
#define LIBCFG_ADC_IVREF                  (1)
#define LIBCFG_ADC_MVDDA                  (1)
#define LIBCFG_AES                        (1)
#define LIBCFG_AES_KEYSIZE_256B           (1)
#define LIBCFG_BAKREG                     (1)
#define LIBCFG_BFTM1                      (1)
#define LIBCFG_CKCU_ATM_V01               (1)
#define LIBCFG_CKCU_PLLSRCDIV             (1)
#define LIBCFG_CKCU_REFCLK_EXT_PIN        (1)
#define LIBCFG_CKCU_SYS_CK_60M            (1)
#define LIBCFG_CKCU_USB_PLL               (1)
#define LIBCFG_CMP                        (1)
#define LIBCFG_CRC                        (1)
#define LIBCFG_DAC0                       (1)
#define LIBCFG_DIV                        (1)
#define LIBCFG_EBI                        (1)
#define LIBCFG_FLASH_2PAGE_PER_WPBIT      (1)
#define LIBCFG_FMC_BRANCHCACHE            (1)
#define LIBCFG_FMC_PREFETCH               (1)
#define LIBCFG_FMC_WAIT_STATE_2           (1)
#define LIBCFG_GPIOC                      (1)
#define LIBCFG_GPIOD                      (1)
#define LIBCFG_GPIOE                      (1)
#define LIBCFG_I2C1                       (1)
#define LIBCFG_I2S                        (1)
#define LIBCFG_LSE                        (1)
#define LIBCFG_MCTM0                      (1)
#define LIBCFG_PDMA                       (1)
#define LIBCFG_PDMA_CH3FIX                (1)
#define LIBCFG_PWM0                       (1)
#define LIBCFG_PWM1                       (1)
#define LIBCFG_QSPI                       (1)
#define LIBCFG_SCI0                       (1)
#define LIBCFG_SCI1                       (1)
#define LIBCFG_SCTM0                      (1)
#define LIBCFG_SCTM1                      (1)
#define LIBCFG_SPI1                       (1)
#define LIBCFG_UART1                      (1)
#define LIBCFG_UART2                      (1)
#define LIBCFG_UART3                      (1)
#define LIBCFG_USART1                     (1)
#define LIBCFG_USBD                       (1)

#define UART0_IRQHandler UART0_UART2_IRQHandler
#define UART2_IRQHandler UART0_UART2_IRQHandler
#define UART1_IRQHandler UART1_UART3_IRQHandler
#define UART3_IRQHandler UART1_UART3_IRQHandler

#endif
