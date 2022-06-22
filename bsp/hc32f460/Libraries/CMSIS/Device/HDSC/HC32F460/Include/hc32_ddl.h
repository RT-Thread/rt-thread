/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32_ddl.h
 **
 ** A detailed description is available at
 ** @link Hc32DdlGroup Hc32 Series Ddl description @endlink
 **
 **   - 2018-9-28  CDT  First version for Hc32 Series Device Driver
 **     Library.
 **
 ******************************************************************************/
#ifndef __HC32_DDL_H__
#define __HC32_DDL_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup Hc32DdlGroup Hc32 Series Device Driver Library(HC32DDL)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*! Defined use device driver library */
#if !defined (USE_DEVICE_DRIVER_LIB)
/**
 *******************************************************************************
 ** \brief Comment the line below if you will not use the device driver library.
 ** In this case, the application code will be based on direct access to
 ** peripherals registers.
 ******************************************************************************/
    /* #define USE_DEVICE_DRIVER_LIB */
#endif /* USE_DEVICE_DRIVER_LIB */

/**
 *******************************************************************************
 ** \brief Hc32 Series device driver library version number v1.0.0
 ******************************************************************************/
#define HC32_DDL_VERSION_MAIN                       0x01u ///< [31:24] main version
#define HC32_DDL_VERSION_SUB1                       0x00u ///< [23:16] sub1 version
#define HC32_DDL_VERSION_SUB2                       0x00u ///< [15:8]  sub2 version
#define HC32_DDL_VERSION_RC                         0x00u ///< [7:0]   release candidate
#define HC32_DDL_VERSION                            ((HC32_DDL_VERSION_MAIN << 24) | \
                                                     (HC32_DDL_VERSION_SUB1 << 16) | \
                                                     (HC32_DDL_VERSION_SUB2 << 8 ) | \
                                                     (HC32_DDL_VERSION_RC))

/*! Use device driver library */
#if defined (USE_DEVICE_DRIVER_LIB)
/**
 *******************************************************************************
 ** \brief Include module's header file
 ******************************************************************************/
#if (DDL_ADC_ENABLE == DDL_ON)
#include "hc32f460_adc.h"
#endif /* DDL_ADC_ENABLE */

#if (DDL_AES_ENABLE == DDL_ON)
#include "hc32f460_aes.h"
#endif /* DDL_AES_ENABLE */

#if (DDL_CAN_ENABLE == DDL_ON)
#include "hc32f460_can.h"
#endif /* DDL_CAN_ENABLE */

#if (DDL_CMP_ENABLE == DDL_ON)
#include "hc32f460_cmp.h"
#endif /* DDL_CMP_ENABLE */

#if (DDL_CLK_ENABLE == DDL_ON)
#include "hc32f460_clk.h"
#endif /* DDL_CLK_ENABLE */

#if (DDL_DCU_ENABLE == DDL_ON)
#include "hc32f460_dcu.h"
#endif /* DDL_DCU_ENABLE */

#if (DDL_DMAC_ENABLE == DDL_ON)
#include "hc32f460_dmac.h"
#endif /* DDL_DMAC_ENABLE */

#if (DDL_EFM_ENABLE == DDL_ON)
#include "hc32f460_efm.h"
#endif /* DDL_EFM_ENABLE */

#if (DDL_EMB_ENABLE == DDL_ON)
#include "hc32f460_emb.h"
#endif /* DDL_EMB_ENABLE */

#if (DDL_EXINT_NMI_SWI_ENABLE == DDL_ON)
#include "hc32f460_exint_nmi_swi.h"
#endif /* DDL_EXINT_NMI_SWI_ENABLE */

#if (DDL_GPIO_ENABLE == DDL_ON)
#include "hc32f460_gpio.h"
#endif /* DDL_GPIO_ENABLE */

#if (DDL_HASH_ENABLE == DDL_ON)
#include "hc32f460_hash.h"
#endif /* DDL_HASH_ENABLE */

#if (DDL_I2C_ENABLE == DDL_ON)
#include "hc32f460_i2c.h"
#endif /* DDL_I2C_ENABLE */

#if (DDL_I2S_ENABLE == DDL_ON)
#include "hc32f460_i2s.h"
#endif /* DDL_I2S_ENABLE */

#if (DDL_ICG_ENABLE == DDL_ON)
#include "hc32f460_icg.h"
#endif /* DDL_ICG_ENABLE */

#if (DDL_INTERRUPTS_ENABLE == DDL_ON)
#include "hc32f460_interrupts.h"
#endif /* DDL_INTERRUPTS_ENABLE */

#if (DDL_KEYSCAN_ENABLE == DDL_ON)
#include "hc32f460_keyscan.h"
#endif /* DDL_KEYSCAN_ENABLE */

#if (DDL_MPU_ENABLE == DDL_ON)
#include "hc32f460_mpu.h"
#endif /* DDL_MPU_ENABLE */

#if (DDL_OTS_ENABLE == DDL_ON)
#include "hc32f460_ots.h"
#endif /* DDL_OTS_ENABLE */

#if (DDL_PGA_ENABLE == DDL_ON)
#include "hc32f460_pga.h"
#endif /* DDL_PGA_ENABLE */

#if (DDL_PWC_ENABLE == DDL_ON)
#include "hc32f460_pwc.h"
#endif /* DDL_PWC_ENABLE */

#if (DDL_QSPI_ENABLE == DDL_ON)
#include "hc32f460_qspi.h"
#endif /* DDL_QSPI_ENABLE */

#if (DDL_RMU_ENABLE == DDL_ON)
#include "hc32f460_rmu.h"
#endif /* DDL_RMU_ENABLE */

#if (DDL_RTC_ENABLE == DDL_ON)
#include "hc32f460_rtc.h"
#endif /* DDL_RTC_ENABLE */

#if (DDL_SDIOC_ENABLE == DDL_ON)
#include "hc32f460_sdioc.h"
#endif /* DDL_SDIOC_ENABLE */

#if (DDL_SPI_ENABLE == DDL_ON)
#include "hc32f460_spi.h"
#endif /* DDL_SPI_ENABLE */

#if (DDL_SRAM_ENABLE == DDL_ON)
#include "hc32f460_sram.h"
#endif /* DDL_SRAM_ENABLE */

#if (DDL_SWDT_ENABLE == DDL_ON)
#include "hc32f460_swdt.h"
#endif /* DDL_SWDT_ENABLE */

#if (DDL_TIMER0_ENABLE == DDL_ON)
#include "hc32f460_timer0.h"
#endif /* DDL_TIMER0_ENABLE */

#if (DDL_TIMER4_CNT_ENABLE == DDL_ON)
#include "hc32f460_timer4_cnt.h"
#endif /* DDL_TIMER4_CNT_ENABLE */

#if (DDL_TIMER4_EMB_ENABLE == DDL_ON)
#include "hc32f460_timer4_emb.h"
#endif /* DDL_TIMER4_EMB_ENABLE */

#if (DDL_TIMER4_OCO_ENABLE == DDL_ON)
#include "hc32f460_timer4_oco.h"
#endif /* DDL_TIMER4_OCO_ENABLE */

#if (DDL_TIMER4_PWM_ENABLE == DDL_ON)
#include "hc32f460_timer4_pwm.h"
#endif /* DDL_TIMER4_PWM_ENABLE */

#if (DDL_TIMER4_SEVT_ENABLE == DDL_ON)
#include "hc32f460_timer4_sevt.h"
#endif /* DDL_TIMER4_SEVT_ENABLE */

#if (DDL_TIMER6_ENABLE == DDL_ON)
#include "hc32f460_timer6.h"
#endif /* DDL_TIMER6_ENABLE */

#if (DDL_TIMERA_ENABLE == DDL_ON)
#include "hc32f460_timera.h"
#endif /* DDL_TIMERA_ENABLE */

#if (DDL_TRNG_ENABLE == DDL_ON)
#include "hc32f460_trng.h"
#endif /* DDL_TRNG_ENABLE */

#if (DDL_USART_ENABLE == DDL_ON)
#include "hc32f460_usart.h"
#endif /* DDL_USART_ENABLE */

#if (DDL_USBFS_ENABLE == DDL_ON)
#include "hc32f460_usbfs.h"
#endif /* DDL_USBFS_ENABLE */

#if (DDL_UTILITY_ENABLE == DDL_ON)
#include "hc32f460_utility.h"
#endif /* DDL_UTILITY_ENABLE */

#if (DDL_WDT_ENABLE == DDL_ON)
#include "hc32f460_wdt.h"
#endif /* DDL_WDT_ENABLE */

#endif /* USE_DEVICE_DRIVER_LIB */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/

//@} // Hc32DdlGroup

#ifdef __cplusplus
}
#endif

#endif /* __HC32_DDL_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
