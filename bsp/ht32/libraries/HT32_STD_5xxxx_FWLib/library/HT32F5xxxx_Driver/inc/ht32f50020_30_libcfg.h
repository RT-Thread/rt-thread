/*********************************************************************************************************//**
 * @file    ht32f50020_30_libcfg.h
 * @version $Rev:: 6386         $
 * @date    $Date:: 2022-10-27 #$
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
#ifndef __ht32f50020_30_LIBCFG_H
#define __ht32f50020_30_LIBCFG_H

/* Settings ------------------------------------------------------------------------------------------------*/

#if !defined(USE_MEM_HT32F50020) && !defined(USE_MEM_HT32F50030)
#define USE_MEM_HT32F50030
#endif

#define LIBCFG_MAX_SPEED                  (16000000)

#define LIBCFG_FLASH_PAGESIZE             (1024)

#ifdef USE_MEM_HT32F50020
  #define LIBCFG_FLASH_SIZE               (LIBCFG_FLASH_PAGESIZE * 16)
  #define LIBCFG_RAM_SIZE                 (1024 * 2)
  #define LIBCFG_CHIPNAME                 (0x50020)
#endif

#ifdef USE_MEM_HT32F50030
  #define LIBCFG_FLASH_SIZE               (LIBCFG_FLASH_PAGESIZE * 31)
  #define LIBCFG_RAM_SIZE                 (1024 * 2)
  #define LIBCFG_CHIPNAME                 (0x50030)
#endif

#define LIBCFG_GPIOC                      (1)
#define LIBCFG_GPIOF                      (1)
#define LIBCFG_LEDC                       (1)
#define LIBCFG_LSE                        (1)
#define LIBCFG_SCTM0                      (1)
#define LIBCFG_SCTM1                      (1)
#define LIBCFG_SCTM2                      (1)
#define LIBCFG_UART1                      (1)
#define LIBCFG_NO_GPTM0                   (1)
#define LIBCFG_NO_USART0                  (1)

#define LIBCFG_ADC_CH8_11                 (1)
#define LIBCFG_ADC_IVREF                  (1)
#define LIBCFG_ADC_IVREF_LEVEL_TYPE2      (1)
#define LIBCFG_ADC_MVDDA                  (1)
#define LIBCFG_ADC_VREFBUF                (1)
#define LIBCFG_ADC_NO_DISCON_MODE         (1)
#define LIBCFG_ADC_NO_SEQ_4_7             (1)
#define LIBCFG_ADC_NO_WDT                 (1)
#define LIBCFG_ADC_SW_TRIGGER_ONLY        (1)
#define LIBCFG_AFIO_LEDC_MODE3            (1)
#define LIBCFG_AFIO_MODE_0_7              (1)
#define LIBCFG_AFIO_SCTM_MODE4            (1)
#define LIBCFG_AFIO_SYSTEM_MODE1          (1)
#define LIBCFG_BFTM_16BIT_COUNTER         (1)
#define LIBCFG_CKCU_NO_APB_PRESCALER      (1)
#define LIBCFG_CKCU_NO_AUTO_TRIM          (1)
#define LIBCFG_CKCU_NO_LPCR               (1)
#define LIBCFG_EXTI_8BIT_DEBOUNCE_COUNTER (1)
#define LIBCFG_EXTI_8CH                   (1)
#define LIBCFG_EXTI_DEBCNTPRE             (1)
#define LIBCFG_GPIO_PR_STRONG_UP          (1)
#define LIBCFG_I2C_PRESCALER_2BIT         (1)
#define LIBCFG_I2C_TOUT_COUNT_8BIT        (1)
#define LIBCFG_I2C_TWO_DEV_ADDR           (1)
#define LIBCFG_I2C_NO_10BIT_MODE          (1)
#define LIBCFG_I2C_NO_ADDR_MASK           (1)
#define LIBCFG_I2C_NO_ARBLOS              (1)
#define LIBCFG_LEDC_NO_COM_8_11           (1)
#define LIBCFG_NO_PLL                     (1)
#define LIBCFG_NO_PWRCU_TEST_REG          (1)
#define LIBCFG_PWRCU_PORF                 (1)
#define LIBCFG_PWRCU_VDD_5V               (1)
#define LIBCFG_PWRCU_WAKEUP_V01           (1)
#define LIBCFG_PWRCU_WAKEUP1              (1)
#define LIBCFG_PWRCU_NO_VDDPORF           (1)
#define LIBCFG_PWRCU_NO_PD_MODE           (1)
#define LIBCFG_PWRCU_NO_PDF               (1)
#define LIBCFG_SPI_CLK_PRE_V01            (1)
#define LIBCFG_SPI_DATA_LENGTH_V01        (1)
#define LIBCFG_SPI_FIFO_DEPTH_V01         (1)
#define LIBCFG_SPI_NO_DUAL                (1)
#define LIBCFG_SPI_NO_MULTI_MASTER        (1)
#define LIBCFG_SPI_TIMEOUT_LENGTH_V01     (1)
#define LIBCFG_TM_CKDIV_8                 (1)
#define LIBCFG_TM_PRESCALER_8BIT          (1)
#define LIBCFG_TM_SCTM_2CHANNEL           (1)

#endif
