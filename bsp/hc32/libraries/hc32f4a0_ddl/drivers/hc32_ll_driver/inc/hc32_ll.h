/**
 *******************************************************************************
 * @file  hc32_ll.h
 * @brief This file contains HC32 Series Device Driver Library file call
 *        management.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_H__
#define __HC32_LL_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_Global
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup LL_Global_Macros LL Global Macros
 * @{
 */

/**
 * @defgroup Peripheral_Register_WP_Local_Macros Peripheral Register Write Protection Local Macros
 * @{
 */
#define LL_PERIPH_EFM           (1UL << 0U)
#define LL_PERIPH_FCG           (1UL << 1U)
#define LL_PERIPH_GPIO          (1UL << 2U)
#define LL_PERIPH_INTC          (1UL << 3U)
#define LL_PERIPH_LVD           (1UL << 4U)
#define LL_PERIPH_MPU           (1UL << 5U)
#define LL_PERIPH_PWC_CLK_RMU   (1UL << 6U)
#define LL_PERIPH_SRAM          (1UL << 7U)
#define LL_PERIPH_ALL           (LL_PERIPH_EFM | LL_PERIPH_FCG | LL_PERIPH_GPIO | LL_PERIPH_INTC  | \
                                 LL_PERIPH_LVD | LL_PERIPH_MPU | LL_PERIPH_SRAM | LL_PERIPH_PWC_CLK_RMU)
/**
 * @}
 */

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
* @defgroup HC32_Series_DDL_Version HC32 Series Device Driver Library Version
* @{
*/
#define HC32_DDL_VER_MAIN               0x01U  /*!< [31:24] main version  */
#define HC32_DDL_VER_SUB1               0x00U  /*!< [23:16] sub1 version  */
#define HC32_DDL_VER_SUB2               0x00U  /*!< [15:8]  sub2 version  */
#define HC32_DDL_VER_PATCH              0x00U  /*!< [7:0]   patch version */
#define HC32_DDL_VER                    ((HC32_DDL_VER_MAIN << 24) | (HC32_DDL_VER_SUB1 << 16) | \
                                         (HC32_DDL_VER_SUB2 << 8 ) | (HC32_DDL_VER_PATCH))
/**
 * @}
 */

/**
* @defgroup HC32_Series_DDL_Release_Version HC32 Series DDL Release Version
* @{
*/
#define HC32_DDL_REV_MAIN               0x02U  /*!< [31:24] main version  */
#define HC32_DDL_REV_SUB1               0x00U  /*!< [23:16] sub1 version  */
#define HC32_DDL_REV_SUB2               0x00U  /*!< [15:8]  sub2 version  */
#define HC32_DDL_REV_PATCH              0x00U  /*!< [7:0]   patch version */
#define HC32_DDL_REV                    ((HC32_DDL_REV_MAIN << 24) | (HC32_DDL_REV_SUB1 << 16) | \
                                         (HC32_DDL_REV_SUB2 << 8 ) | (HC32_DDL_REV_PATCH))
/**
 * @}
 */

/**
 * @}
 */

/* Use Device Driver Library */
#if defined (USE_DDL_DRIVER)

/**
 * @brief Include peripheral module's header file
 */
#if (LL_ADC_ENABLE == DDL_ON)
#include "hc32_ll_adc.h"
#endif /* LL_ADC_ENABLE */

#if (LL_AES_ENABLE == DDL_ON)
#include "hc32_ll_aes.h"
#endif /* LL_AES_ENABLE */

#if (LL_AOS_ENABLE == DDL_ON)
#include "hc32_ll_aos.h"
#endif /* LL_AOS_ENABLE */

#if (LL_CAN_ENABLE == DDL_ON)
#include "hc32_ll_can.h"
#endif /* LL_CAN_ENABLE */

#if (LL_CLK_ENABLE == DDL_ON)
#include "hc32_ll_clk.h"
#endif /* LL_CLK_ENABLE */

#if (LL_CMP_ENABLE == DDL_ON)
#include "hc32_ll_cmp.h"
#endif /* LL_CMP_ENABLE */

#if (LL_CRC_ENABLE == DDL_ON)
#include "hc32_ll_crc.h"
#endif /* LL_CRC_ENABLE */

#if (LL_CTC_ENABLE == DDL_ON)
#include "hc32_ll_ctc.h"
#endif /* LL_CTC_ENABLE */

#if (LL_DAC_ENABLE == DDL_ON)
#include "hc32_ll_dac.h"
#endif /* LL_DAC_ENABLE */

#if (LL_DCU_ENABLE == DDL_ON)
#include "hc32_ll_dcu.h"
#endif /* LL_DCU_ENABLE */

#if (LL_DMA_ENABLE == DDL_ON)
#include "hc32_ll_dma.h"
#endif /* LL_DMA_ENABLE */

#if (LL_DMC_ENABLE == DDL_ON)
#include "hc32_ll_dmc.h"
#endif /* LL_DMC_ENABLE */

#if (LL_DVP_ENABLE == DDL_ON)
#include "hc32_ll_dvp.h"
#endif /* LL_DVP_ENABLE */

#if (LL_EFM_ENABLE == DDL_ON)
#include "hc32_ll_efm.h"
#endif /* LL_EFM_ENABLE */

#if (LL_EMB_ENABLE == DDL_ON)
#include "hc32_ll_emb.h"
#endif /* LL_EMB_ENABLE */

#if (LL_ETH_ENABLE == DDL_ON)
#include "hc32_ll_eth.h"
#endif /* LL_ETH_ENABLE */

#if (LL_EVENT_PORT_ENABLE == DDL_ON)
#include "hc32_ll_event_port.h"
#endif /* LL_EVENT_PORT_ENABLE */

#if (LL_FCG_ENABLE == DDL_ON)
#include "hc32_ll_fcg.h"
#endif /* LL_FCG_ENABLE */

#if (LL_FCM_ENABLE == DDL_ON)
#include "hc32_ll_fcm.h"
#endif /* LL_FCM_ENABLE */

#if (LL_FMAC_ENABLE == DDL_ON)
#include "hc32_ll_fmac.h"
#endif /* LL_FMAC_ENABLE */

#if (LL_GPIO_ENABLE == DDL_ON)
#include "hc32_ll_gpio.h"
#endif /* LL_GPIO_ENABLE */

#if (LL_HASH_ENABLE == DDL_ON)
#include "hc32_ll_hash.h"
#endif /* LL_HASH_ENABLE */

#if (LL_HRPWM_ENABLE == DDL_ON)
#include "hc32_ll_hrpwm.h"
#endif /* LL_HRPWM_ENABLE */

#if (LL_I2C_ENABLE == DDL_ON)
#include "hc32_ll_i2c.h"
#endif /* LL_I2C_ENABLE */

#if (LL_I2S_ENABLE == DDL_ON)
#include "hc32_ll_i2s.h"
#endif /* LL_I2S_ENABLE */

#if (LL_ICG_ENABLE == DDL_ON)
#include "hc32_ll_icg.h"
#endif /* LL_ICG_ENABLE */

#if (LL_INTERRUPTS_ENABLE == DDL_ON)
#include "hc32_ll_interrupts.h"
#endif /* LL_INTERRUPTS_ENABLE */

#if (LL_INTERRUPTS_SHARE_ENABLE == DDL_ON)
#include "hc32f4a0_ll_interrupts_share.h"
#endif /* LL_INTERRUPTS_ENABLE */

#if (LL_KEYSCAN_ENABLE == DDL_ON)
#include "hc32_ll_keyscan.h"
#endif /* LL_KEYSCAN_ENABLE */

#if (LL_MAU_ENABLE == DDL_ON)
#include "hc32_ll_mau.h"
#endif /* LL_MAU_ENABLE */

#if (LL_MPU_ENABLE == DDL_ON)
#include "hc32_ll_mpu.h"
#endif /* LL_MPU_ENABLE */

#if (LL_NFC_ENABLE == DDL_ON)
#include "hc32_ll_nfc.h"
#endif /* LL_NFC_ENABLE */

#if (LL_OTS_ENABLE == DDL_ON)
#include "hc32_ll_ots.h"
#endif /* LL_OTS_ENABLE */

#if (LL_PWC_ENABLE == DDL_ON)
#include "hc32_ll_pwc.h"
#endif /* LL_PWC_ENABLE */

#if (LL_QSPI_ENABLE == DDL_ON)
#include "hc32_ll_qspi.h"
#endif /* LL_QSPI_ENABLE */

#if (LL_RMU_ENABLE == DDL_ON)
#include "hc32_ll_rmu.h"
#endif /* LL_RMU_ENABLE */

#if (LL_RTC_ENABLE == DDL_ON)
#include "hc32_ll_rtc.h"
#endif /* LL_RTC_ENABLE */

#if (LL_SDIOC_ENABLE == DDL_ON)
#include "hc32_ll_sdioc.h"
#endif /* LL_SDIOC_ENABLE */

#if (LL_SMC_ENABLE == DDL_ON)
#include "hc32_ll_smc.h"
#endif /* LL_SMC_ENABLE */

#if (LL_SPI_ENABLE == DDL_ON)
#include "hc32_ll_spi.h"
#endif /* LL_SPI_ENABLE */

#if (LL_SRAM_ENABLE == DDL_ON)
#include "hc32_ll_sram.h"
#endif /* LL_SRAM_ENABLE */

#if (LL_SWDT_ENABLE == DDL_ON)
#include "hc32_ll_swdt.h"
#endif /* LL_SWDT_ENABLE */

#if (LL_TMR0_ENABLE == DDL_ON)
#include "hc32_ll_tmr0.h"
#endif /* LL_TMR0_ENABLE */

#if (LL_TMR2_ENABLE == DDL_ON)
#include "hc32_ll_tmr2.h"
#endif /* LL_TMR2_ENABLE */

#if (LL_TMR4_ENABLE == DDL_ON)
#include "hc32_ll_tmr4.h"
#endif /* LL_TMR4_ENABLE */

#if (LL_TMR6_ENABLE == DDL_ON)
#include "hc32_ll_tmr6.h"
#endif /* LL_TMR6_ENABLE */

#if (LL_TMRA_ENABLE == DDL_ON)
#include "hc32_ll_tmra.h"
#endif /* LL_TMRA_ENABLE */

#if (LL_TRNG_ENABLE == DDL_ON)
#include "hc32_ll_trng.h"
#endif /* LL_TRNG_ENABLE */

#if (LL_USART_ENABLE == DDL_ON)
#include "hc32_ll_usart.h"
#endif /* LL_USART_ENABLE */

#if (LL_UTILITY_ENABLE == DDL_ON)
#include "hc32_ll_utility.h"
#endif /* LL_UTILITY_ENABLE */

#if (LL_USB_ENABLE == DDL_ON)
#include "hc32_ll_usb.h"
#endif /* LL_USB_ENABLE */

#if (LL_WDT_ENABLE == DDL_ON)
#include "hc32_ll_wdt.h"
#endif /* LL_WDT_ENABLE */

#endif /* USE_DDL_DRIVER */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup LL_Global_Functions
 * @{
 */
void LL_PERIPH_WE(uint32_t u32Peripheral);
void LL_PERIPH_WP(uint32_t u32Peripheral);
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

#endif /* __HC32_DDL_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
