/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file ddl_config.h
 **
 ** A detailed description is available at
 ** @link DdlConfigGroup Ddl Config description @endlink
 **
 **   - 2018-10-18  CDT  First version for Device Driver Library config.
 **
 ******************************************************************************/
#ifndef __DDL_CONFIG_H__
#define __DDL_CONFIG_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup DdlConfigGroup Device Driver Library config(DDLCONFIG)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*! Chip module on-off define */
#define DDL_ON                                      (1u)
#define DDL_OFF                                     (0u)

/**
 *******************************************************************************
 ** \brief This is the list of modules to be used in the device driver library
 ** Select the modules you need to use to DDL_ON.
 **
 ** \note DDL_ICG_ENABLE must be turned on(DDL_ON) to ensure that the chip works
 ** properly.
 **
 ** \note DDL_UTILITY_ENABLE must be turned on(DDL_ON) if using Device Driver
 ** Library.
 **
 ** \note DDL_PRINT_ENABLE must be turned on(DDL_ON) if using printf function.
 ******************************************************************************/
#define DDL_ICG_ENABLE                              (DDL_ON)
#define DDL_UTILITY_ENABLE                          (DDL_ON)
#define DDL_PRINT_ENABLE                            (DDL_ON)

#define DDL_ADC_ENABLE                              (DDL_OFF)
#define DDL_AES_ENABLE                              (DDL_OFF)
#define DDL_CAN_ENABLE                              (DDL_OFF)
#define DDL_CLK_ENABLE                              (DDL_ON)
#define DDL_CMP_ENABLE                              (DDL_OFF)
#define DDL_CRC_ENABLE                              (DDL_OFF)
#define DDL_DCU_ENABLE                              (DDL_OFF)
#define DDL_DMAC_ENABLE                             (DDL_ON)
#define DDL_EFM_ENABLE                              (DDL_ON)
#define DDL_EMB_ENABLE                              (DDL_OFF)
#define DDL_EVENT_PORT_ENABLE                       (DDL_OFF)
#define DDL_EXINT_NMI_SWI_ENABLE                    (DDL_ON)
#define DDL_GPIO_ENABLE                             (DDL_ON)
#define DDL_HASH_ENABLE                             (DDL_OFF)
#define DDL_I2C_ENABLE                              (DDL_OFF)
#define DDL_I2S_ENABLE                              (DDL_OFF)
#define DDL_INTERRUPTS_ENABLE                       (DDL_ON)
#define DDL_KEYSCAN_ENABLE                          (DDL_OFF)
#define DDL_MPU_ENABLE                              (DDL_OFF)
#define DDL_OTS_ENABLE                              (DDL_OFF)
#define DDL_PWC_ENABLE                              (DDL_ON)
#define DDL_QSPI_ENABLE                             (DDL_OFF)
#define DDL_RMU_ENABLE                              (DDL_OFF)
#define DDL_RTC_ENABLE                              (DDL_ON)
#define DDL_SDIOC_ENABLE                            (DDL_OFF)
#define DDL_SPI_ENABLE                              (DDL_OFF)
#define DDL_SRAM_ENABLE                             (DDL_ON)
#define DDL_SWDT_ENABLE                             (DDL_OFF)
#define DDL_TIMER0_ENABLE                           (DDL_ON)
#define DDL_TIMER4_CNT_ENABLE                       (DDL_OFF)
#define DDL_TIMER4_EMB_ENABLE                       (DDL_OFF)
#define DDL_TIMER4_OCO_ENABLE                       (DDL_OFF)
#define DDL_TIMER4_PWM_ENABLE                       (DDL_OFF)
#define DDL_TIMER4_SEVT_ENABLE                      (DDL_OFF)
#define DDL_TIMER6_ENABLE                           (DDL_OFF)
#define DDL_TIMERA_ENABLE                           (DDL_OFF)
#define DDL_TRNG_ENABLE                             (DDL_OFF)
#define DDL_USART_ENABLE                            (DDL_ON)
#define DDL_USBFS_ENABLE                            (DDL_OFF)
#define DDL_WDT_ENABLE                              (DDL_OFF)


/*! Midware module on-off define */
#define MW_ON                                       (1u)
#define MW_OFF                                      (0u)

/**
 *******************************************************************************
 ** \brief This is the list of Midware modules to use
 ** Select the modules you need to use to MW_ON.
 ******************************************************************************/
#define MW_SD_CARD_ENABLE                           (MW_OFF)
#define MW_FS_ENABLE                                (MW_OFF)
#define MW_W25QXX_ENABLE                            (MW_OFF)
#define MW_WM8731_ENABLE                            (MW_OFF)

/* BSP on-off define */
#define BSP_ON                                      (1u)
#define BSP_OFF                                     (0u)

/**
 * @brief The following is a list of currently supported BSP boards.
 */
#define BSP_EV_HC32F460_LQFP100_V1                  (1u)
#define BSP_EV_HC32F460_LQFP100_V2                  (2u)

/**
 * @brief The macro BSP_EV_HC32F460 is used to specify the BSP board currently
 * in use.
 * The value should be set to one of the list of currently supported BSP boards.
 * @note  If there is no supported BSP board or the BSP function is not used,
 * the value needs to be set to BSP_EV_HC32F460.
 */
#define BSP_EV_HC32F460                             (BSP_EV_HC32F460)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/

//@} // DdlConfigGroup

#ifdef __cplusplus
}
#endif

#endif /* __DDL_CONFIG_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
