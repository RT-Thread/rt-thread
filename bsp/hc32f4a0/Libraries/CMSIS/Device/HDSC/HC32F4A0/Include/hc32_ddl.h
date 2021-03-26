/**
 *******************************************************************************
 * @file  hc32_ddl.h
 * @brief This file contains HC32 Series Device Driver Library file call
 *        management.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Yangjp          First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_DDL_H__
#define __HC32_DDL_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Defined use Device Driver Library */
#if !defined (USE_DDL_DRIVER)
/**
 * @brief Comment the line below if you will not use the Device Driver Library.
 * In this case, the application code will be based on direct access to
 * peripherals registers.
 */
    /* #define USE_DDL_DRIVER */
#endif /* USE_DDL_DRIVER */

/**
 * @brief HC32 Series Device Driver Library version number
 */
#define HC32_DDL_VERSION_MAIN           0x01U  /*!< [31:24] main version */
#define HC32_DDL_VERSION_SUB1           0x00U  /*!< [23:16] sub1 version */
#define HC32_DDL_VERSION_SUB2           0x04U  /*!< [15:8]  sub2 version */
#define HC32_DDL_VERSION_RC             0x00U  /*!< [7:0]   release candidate */
#define HC32_DDL_VERSION                ((HC32_DDL_VERSION_MAIN << 24) | \
                                         (HC32_DDL_VERSION_SUB1 << 16) | \
                                         (HC32_DDL_VERSION_SUB2 << 8 ) | \
                                         (HC32_DDL_VERSION_RC))

/* Use Device Driver Library */
#if defined (USE_DDL_DRIVER)

/**
 * @brief Include peripheral module's header file
 */
#if (DDL_ADC_ENABLE == DDL_ON)
    #include "hc32f4a0_adc.h"
#endif /* DDL_ADC_ENABLE */

#if (DDL_AES_ENABLE == DDL_ON)
    #include "hc32f4a0_aes.h"
#endif /* DDL_AES_ENABLE */

#if (DDL_CAN_ENABLE == DDL_ON)
    #include "hc32f4a0_can.h"
#endif /* DDL_CAN_ENABLE */

#if (DDL_CLK_ENABLE == DDL_ON)
    #include "hc32f4a0_clk.h"
#endif /* DDL_CLK_ENABLE */

#if (DDL_CMP_ENABLE == DDL_ON)
    #include "hc32f4a0_cmp.h"
#endif /* DDL_CMP_ENABLE */

#if (DDL_CRC_ENABLE == DDL_ON)
    #include "hc32f4a0_crc.h"
#endif /* DDL_CRC_ENABLE */

#if (DDL_CTC_ENABLE == DDL_ON)
    #include "hc32f4a0_ctc.h"
#endif /* DDL_CTC_ENABLE */

#if (DDL_DAC_ENABLE == DDL_ON)
    #include "hc32f4a0_dac.h"
#endif /* DDL_DAC_ENABLE */

#if (DDL_DCU_ENABLE == DDL_ON)
    #include "hc32f4a0_dcu.h"
#endif /* DDL_DCU_ENABLE */

#if (DDL_DMA_ENABLE == DDL_ON)
    #include "hc32f4a0_dma.h"
#endif /* DDL_DMA_ENABLE */

#if (DDL_DMC_ENABLE == DDL_ON)
    #include "hc32f4a0_dmc.h"
#endif /* DDL_DMC_ENABLE */

#if (DDL_DVP_ENABLE == DDL_ON)
    #include "hc32f4a0_dvp.h"
#endif /* DDL_DVP_ENABLE */

#if (DDL_EFM_ENABLE == DDL_ON)
    #include "hc32f4a0_efm.h"
#endif /* DDL_EFM_ENABLE */

#if (DDL_EMB_ENABLE == DDL_ON)
    #include "hc32f4a0_emb.h"
#endif /* DDL_EMB_ENABLE */

#if (DDL_ETH_ENABLE == DDL_ON)
    #include "hc32f4a0_eth.h"
#endif /* DDL_ETH_ENABLE */

#if (DDL_EVENT_PORT_ENABLE == DDL_ON)
    #include "hc32f4a0_event_port.h"
#endif /* DDL_EVENT_PORT_ENABLE */

#if (DDL_FCM_ENABLE == DDL_ON)
    #include "hc32f4a0_fcm.h"
#endif /* DDL_FCM_ENABLE */

#if (DDL_FMAC_ENABLE == DDL_ON)
    #include "hc32f4a0_fmac.h"
#endif /* DDL_FMAC_ENABLE */

#if (DDL_GPIO_ENABLE == DDL_ON)
    #include "hc32f4a0_gpio.h"
#endif /* DDL_GPIO_ENABLE */

#if (DDL_HASH_ENABLE == DDL_ON)
    #include "hc32f4a0_hash.h"
#endif /* DDL_HASH_ENABLE */

#if (DDL_I2C_ENABLE == DDL_ON)
    #include "hc32f4a0_i2c.h"
#endif /* DDL_I2C_ENABLE */

#if (DDL_I2S_ENABLE == DDL_ON)
    #include "hc32f4a0_i2s.h"
#endif /* DDL_I2S_ENABLE */

#if (DDL_ICG_ENABLE == DDL_ON)
    #include "hc32f4a0_icg.h"
#endif /* DDL_ICG_ENABLE */

#if (DDL_INTERRUPTS_ENABLE == DDL_ON)
    #include "hc32f4a0_interrupts.h"
#endif /* DDL_INTERRUPTS_ENABLE */

#if (DDL_KEYSCAN_ENABLE == DDL_ON)
    #include "hc32f4a0_keyscan.h"
#endif /* DDL_KEYSCAN_ENABLE */

#if (DDL_MAU_ENABLE == DDL_ON)
    #include "hc32f4a0_mau.h"
#endif /* DDL_MAU_ENABLE */

#if (DDL_MPU_ENABLE == DDL_ON)
    #include "hc32f4a0_mpu.h"
#endif /* DDL_MPU_ENABLE */

#if (DDL_NFC_ENABLE == DDL_ON)
    #include "hc32f4a0_nfc.h"
#endif /* DDL_NFC_ENABLE */

#if (DDL_OTS_ENABLE == DDL_ON)
    #include "hc32f4a0_ots.h"
#endif /* DDL_OTS_ENABLE */

#if (DDL_PWC_ENABLE == DDL_ON)
    #include "hc32f4a0_pwc.h"
#endif /* DDL_PWC_ENABLE */

#if (DDL_QSPI_ENABLE == DDL_ON)
    #include "hc32f4a0_qspi.h"
#endif /* DDL_QSPI_ENABLE */

#if (DDL_RMU_ENABLE == DDL_ON)
    #include "hc32f4a0_rmu.h"
#endif /* DDL_RMU_ENABLE */

#if (DDL_RTC_ENABLE == DDL_ON)
    #include "hc32f4a0_rtc.h"
#endif /* DDL_RTC_ENABLE */

#if (DDL_SDIOC_ENABLE == DDL_ON)
    #include "hc32f4a0_sdioc.h"
#endif /* DDL_SDIOC_ENABLE */

#if (DDL_SMC_ENABLE == DDL_ON)
    #include "hc32f4a0_smc.h"
#endif /* DDL_SMC_ENABLE */

#if (DDL_SPI_ENABLE == DDL_ON)
    #include "hc32f4a0_spi.h"
#endif /* DDL_SPI_ENABLE */

#if (DDL_SRAM_ENABLE == DDL_ON)
    #include "hc32f4a0_sram.h"
#endif /* DDL_SRAM_ENABLE */

#if (DDL_SWDT_ENABLE == DDL_ON)
    #include "hc32f4a0_swdt.h"
#endif /* DDL_SWDT_ENABLE */

#if (DDL_TMR0_ENABLE == DDL_ON)
    #include "hc32f4a0_tmr0.h"
#endif /* DDL_TMR0_ENABLE */

#if (DDL_TMR2_ENABLE == DDL_ON)
    #include "hc32f4a0_tmr2.h"
#endif /* DDL_TMR2_ENABLE */

#if (DDL_TMR4_ENABLE == DDL_ON)
    #include "hc32f4a0_tmr4.h"
#endif /* DDL_TMR4_ENABLE */

#if (DDL_TMR6_ENABLE == DDL_ON)
    #include "hc32f4a0_tmr6.h"
#endif /* DDL_TMR6_ENABLE */

#if (DDL_TMRA_ENABLE == DDL_ON)
    #include "hc32f4a0_tmra.h"
#endif /* DDL_TMRA_ENABLE */

#if (DDL_TRNG_ENABLE == DDL_ON)
    #include "hc32f4a0_trng.h"
#endif /* DDL_TRNG_ENABLE */

#if (DDL_USART_ENABLE == DDL_ON)
    #include "hc32f4a0_usart.h"
#endif /* DDL_USART_ENABLE */

#if (DDL_USBFS_ENABLE == DDL_ON)
    #include "hc32f4a0_usbfs.h"
#endif /* DDL_USBFS_ENABLE */

#if (DDL_USBHS_ENABLE == DDL_ON)
    #include "hc32f4a0_usbhs.h"
#endif /* DDL_USBHS_ENABLE */

#if (DDL_UTILITY_ENABLE == DDL_ON)
    #include "hc32f4a0_utility.h"
#endif /* DDL_UTILITY_ENABLE */

#if (DDL_WDT_ENABLE == DDL_ON)
    #include "hc32f4a0_wdt.h"
#endif /* DDL_WDT_ENABLE */

#if (DDL_HRPWM_ENABLE == DDL_ON)
    #include "hc32f4a0_hrpwm.h"
#endif /* DDL_HRPWM_ENABLE */


/**
 * @brief Include BSP board's header file
 */
#if (BSP_EV_HC32F4A0_LQFP176 == BSP_EV_HC32F4A0)
    #include "ev_hc32f4a0_lqfp176.h"
#endif /* BSP_EV_HC32F4A0_LQFP176 */

#if (BSP_MS_HC32F4A0_LQFP176_050_MEM == BSP_EV_HC32F4A0)
    #include "ms_hc32f4a0_lqfp176_050_mem.h"
#endif /* BSP_MS_HC32F4A0_LQFP176_050_MEM */


/**
 * @brief Include BSP device component's header file
 */
#if (BSP_CY62167EV30LL_ENABLE == BSP_ON)
    #include "cy62167ev30ll.h"
#endif /* BSP_CY62167EV30LL_ENABLE */

#if (BSP_IS42S16400J7TLI_ENABLE == BSP_ON)
    #include "is42s16400j7tli.h"
#endif /* BSP_IS42S16400J7TLI_ENABLE */

#if (BSP_IS62WV51216_ENABLE == BSP_ON)
    #include "is62wv51216.h"
#endif /* BSP_IS62WV51216_ENABLE */

#if (BSP_MT29F2G08AB_ENABLE == BSP_ON)
    #include "mt29f2g08ab.h"
#endif /* BSP_MT29F2G08AB_ENABLE */

#if (BSP_NT35510_ENABLE == BSP_ON)
    #include "nt35510.h"
#endif /* BSP_NT35510_ENABLE */

#if (BSP_OV5640_ENABLE == BSP_ON)
    #include "ov5640.h"
#endif /* BSP_OV5640_ENABLE */

#if (BSP_S29GL064N90TFI03_ENABLE == BSP_ON)
    #include "s29gl064n90tfi03.h"
#endif /* BSP_S29GL064N90TFI03_ENABLE */

#if (BSP_TCA9539_ENABLE == BSP_ON)
    #include "ev_hc32f4a0_lqfp176_tca9539.h"
    #include "tca9539.h"
#endif /* BSP_TCA9539_ENABLE */

#if (BSP_W25QXX_ENABLE == BSP_ON)
    #include "w25qxx.h"
#endif /* BSP_W25QXX_ENABLE */

#if (BSP_WM8731_ENABLE == BSP_ON)
    #include "wm8731.h"
#endif /* BSP_WM8731_ENABLE */

#endif /* USE_DDL_DRIVER */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __HC32_DDL_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
