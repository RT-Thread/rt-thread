/**
 *******************************************************************************
 * @file  template/source/hc32f4xx_conf.h
 * @brief This file contains HC32 Series Device Driver Library usage management.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32F4XX_CONF_H__
#define __HC32F4XX_CONF_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtconfig.h>

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @brief This is the list of modules to be used in the Device Driver Library.
 * Select the modules you need to use to DDL_ON.
 * @note LL_ICG_ENABLE must be turned on(DDL_ON) to ensure that the chip works
 * properly.
 * @note LL_UTILITY_ENABLE must be turned on(DDL_ON) if using Device Driver
 * Library.
 * @note LL_PRINT_ENABLE must be turned on(DDL_ON) if using printf function.
 */
#define LL_ICG_ENABLE                               (DDL_ON)
#define LL_UTILITY_ENABLE                           (DDL_ON)
#define LL_PRINT_ENABLE                             (DDL_OFF)

#define LL_ADC_ENABLE                               (DDL_ON)
#define LL_AES_ENABLE                               (DDL_ON)
#define LL_AOS_ENABLE                               (DDL_ON)
#define LL_CAN_ENABLE                               (DDL_ON)
#define LL_CLK_ENABLE                               (DDL_ON)
#define LL_CMP_ENABLE                               (DDL_ON)
#define LL_CRC_ENABLE                               (DDL_ON)
#define LL_CTC_ENABLE                               (DDL_ON)
#define LL_DAC_ENABLE                               (DDL_ON)
#define LL_DBGC_ENABLE                              (DDL_OFF)
#define LL_DCU_ENABLE                               (DDL_ON)
#define LL_DMA_ENABLE                               (DDL_ON)
#define LL_DMC_ENABLE                               (DDL_ON)
#define LL_DVP_ENABLE                               (DDL_ON)
#define LL_EFM_ENABLE                               (DDL_ON)
#define LL_EMB_ENABLE                               (DDL_ON)
#define LL_ETH_ENABLE                               (DDL_ON)
#define LL_EVENT_PORT_ENABLE                        (DDL_OFF)
#define LL_FCG_ENABLE                               (DDL_ON)
#define LL_FCM_ENABLE                               (DDL_ON)
#define LL_FMAC_ENABLE                              (DDL_ON)
#define LL_GPIO_ENABLE                              (DDL_ON)
#define LL_HASH_ENABLE                              (DDL_ON)
#define LL_HRPWM_ENABLE                             (DDL_ON)
#define LL_I2C_ENABLE                               (DDL_ON)
#define LL_I2S_ENABLE                               (DDL_ON)
#define LL_INTERRUPTS_ENABLE                        (DDL_ON)
#define LL_INTERRUPTS_SHARE_ENABLE                  (DDL_ON)
#define LL_KEYSCAN_ENABLE                           (DDL_ON)
#define LL_MAU_ENABLE                               (DDL_ON)
#define LL_MPU_ENABLE                               (DDL_ON)
#define LL_NFC_ENABLE                               (DDL_ON)
#define LL_OTS_ENABLE                               (DDL_ON)
#define LL_PWC_ENABLE                               (DDL_ON)
#define LL_QSPI_ENABLE                              (DDL_ON)
#define LL_RMU_ENABLE                               (DDL_ON)
#define LL_RTC_ENABLE                               (DDL_ON)
#define LL_SDIOC_ENABLE                             (DDL_ON)
#define LL_SMC_ENABLE                               (DDL_ON)
#define LL_SPI_ENABLE                               (DDL_ON)
#define LL_SRAM_ENABLE                              (DDL_ON)
#define LL_SWDT_ENABLE                              (DDL_ON)
#define LL_TMR0_ENABLE                              (DDL_ON)
#define LL_TMR2_ENABLE                              (DDL_ON)
#define LL_TMR4_ENABLE                              (DDL_ON)
#define LL_TMR6_ENABLE                              (DDL_ON)
#define LL_TMRA_ENABLE                              (DDL_ON)
#define LL_TRNG_ENABLE                              (DDL_ON)
#define LL_USART_ENABLE                             (DDL_ON)
#define LL_USB_ENABLE                               (DDL_ON)
#define LL_WDT_ENABLE                               (DDL_ON)

/**
 * @brief The following is a list of currently supported BSP boards.
 */
#define BSP_EV_HC32F4A0_LQFP176                     (1U)

/**
 * @brief The macro BSP_EV_HC32F4XX is used to specify the BSP board currently
 * in use.
 * The value should be set to one of the list of currently supported BSP boards.
 * @note  If there is no supported BSP board or the BSP function is not used,
 * the value needs to be set to 0U.
 */
#define BSP_EV_HC32F4XX                             (0U)

/**
 * @brief This is the list of BSP components to be used.
 * Select the components you need to use to DDL_ON.
 */
#define BSP_24CXX_ENABLE                            (DDL_OFF)
#define BSP_GT9XX_ENABLE                            (DDL_OFF)
#define BSP_IS42S16400J7TLI_ENABLE                  (DDL_OFF)
#define BSP_IS62WV51216_ENABLE                      (DDL_OFF)
#define BSP_MT29F2G08AB_ENABLE                      (DDL_OFF)
#define BSP_NT35510_ENABLE                          (DDL_OFF)
#define BSP_OV5640_ENABLE                           (DDL_OFF)
#define BSP_TCA9539_ENABLE                          (DDL_OFF)
#define BSP_W25QXX_ENABLE                           (DDL_OFF)
#define BSP_WM8731_ENABLE                           (DDL_OFF)

/**
 * @brief Ethernet and PHY Configuration.
 */
/* MAC ADDRESS */
#define ETH_MAC_ADDR0                               (0x02U)
#define ETH_MAC_ADDR1                               (0x00U)
#define ETH_MAC_ADDR2                               (0x00U)
#define ETH_MAC_ADDR3                               (0x00U)
#define ETH_MAC_ADDR4                               (0x00U)
#define ETH_MAC_ADDR5                               (0x00U)

#if defined (ETH_PHY_USING_RTL8201F)
/* PHY(RTL8201F) Address*/
#define ETH_PHY_ADDR                                (0x01U)

/* PHY Status Register */
#define PHY_SR                                      (0x00U)     /*!< PHY status register */
#define PHY_DUPLEX_STATUS                           (0x0100U)   /*!< PHY Duplex mask     */
#define PHY_SPEED_STATUS                            (0x2000U)   /*!< PHY Speed mask      */

#endif

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4XX_CONF_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
