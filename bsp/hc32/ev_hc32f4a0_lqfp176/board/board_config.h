/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */


#ifndef __BOARD_CONFIG_H__
#define __BOARD_CONFIG_H__

#include <rtconfig.h>
#include "hc32_ll.h"
#include "drv_config.h"


/************************* XTAL port **********************/
#define XTAL_PORT                       (GPIO_PORT_H)
#define XTAL_IN_PIN                     (GPIO_PIN_01)
#define XTAL_OUT_PIN                    (GPIO_PIN_00)

/************************ USART port **********************/
#if defined(BSP_USING_UART1)
    #define USART1_RX_PORT                  (GPIO_PORT_H)
    #define USART1_RX_PIN                   (GPIO_PIN_13)
    #define USART1_RX_FUNC                  (GPIO_FUNC_33)

    #define USART1_TX_PORT                  (GPIO_PORT_H)
    #define USART1_TX_PIN                   (GPIO_PIN_15)
    #define USART1_TX_FUNC                  (GPIO_FUNC_32)
#endif

#if defined(BSP_USING_UART6)
    #define USART6_RX_PORT                  (GPIO_PORT_H)
    #define USART6_RX_PIN                   (GPIO_PIN_06)
    #define USART6_RX_FUNC                  (GPIO_FUNC_37)

    #define USART6_TX_PORT                  (GPIO_PORT_E)
    #define USART6_TX_PIN                   (GPIO_PIN_06)
    #define USART6_TX_FUNC                  (GPIO_FUNC_36)
#endif

/************************ I2C port **********************/
#if defined(BSP_USING_I2C1)
    #define I2C1_SDA_PORT                   (GPIO_PORT_F)
    #define I2C1_SDA_PIN                    (GPIO_PIN_10)
    #define I2C1_SDA_FUNC                   (GPIO_FUNC_48)

    #define I2C1_SCL_PORT                   (GPIO_PORT_D)
    #define I2C1_SCL_PIN                    (GPIO_PIN_03)
    #define I2C1_SCL_FUNC                   (GPIO_FUNC_49)
#endif

/***********  ADC configure *********/
#if defined(BSP_USING_ADC1)
    #define ADC1_CH_PORT                    (GPIO_PORT_C)
    #define ADC1_CH_PIN                     (GPIO_PIN_00)
#endif

#if defined(BSP_USING_ADC2)
    #define ADC2_CH_PORT                    (GPIO_PORT_C)
    #define ADC2_CH_PIN                     (GPIO_PIN_01)
#endif

#if defined(BSP_USING_ADC3)
    #define ADC3_CH_PORT                    (GPIO_PORT_C)
    #define ADC3_CH_PIN                     (GPIO_PIN_02)
#endif

/***********  DAC configure *********/
#if defined(BSP_USING_DAC1)
    #define DAC1_CH1_PORT                   (GPIO_PORT_A)
    #define DAC1_CH1_PIN                    (GPIO_PIN_04)
    #define DAC1_CH2_PORT                   (GPIO_PORT_A)
    #define DAC1_CH2_PIN                    (GPIO_PIN_05)
#endif

#if defined(BSP_USING_DAC2)
    #define DAC2_CH1_PORT                   (GPIO_PORT_C)
    #define DAC2_CH1_PIN                    (GPIO_PIN_04)
    #define DAC2_CH2_PORT                   (GPIO_PORT_C)
    #define DAC2_CH2_PIN                    (GPIO_PIN_05)
#endif

/***********  CAN configure *********/
#if defined(BSP_USING_CAN1)
    #define CAN1_TX_PORT                    (GPIO_PORT_D)
    #define CAN1_TX_PIN                     (GPIO_PIN_05)
    #define CAN1_TX_PIN_FUNC                (GPIO_FUNC_60)

    #define CAN1_RX_PORT                    (GPIO_PORT_D)
    #define CAN1_RX_PIN                     (GPIO_PIN_04)
    #define CAN1_RX_PIN_FUNC                (GPIO_FUNC_61)
#endif

#if defined(BSP_USING_CAN2)
    #define CAN2_TX_PORT                    (GPIO_PORT_D)
    #define CAN2_TX_PIN                     (GPIO_PIN_07)
    #define CAN2_TX_PIN_FUNC                (GPIO_FUNC_62)

    #define CAN2_RX_PORT                    (GPIO_PORT_D)
    #define CAN2_RX_PIN                     (GPIO_PIN_06)
    #define CAN2_RX_PIN_FUNC                (GPIO_FUNC_63)
#endif

/************************* SPI port ***********************/
#if defined(BSP_USING_SPI1)
    #define SPI1_CS_PORT                (GPIO_PORT_C)
    #define SPI1_CS_PIN                 (GPIO_PIN_07)

    #define SPI1_SCK_PORT               (GPIO_PORT_C)
    #define SPI1_SCK_PIN                (GPIO_PIN_06)
    #define SPI1_SCK_FUNC               (GPIO_FUNC_40)

    #define SPI1_MOSI_PORT              (GPIO_PORT_B)
    #define SPI1_MOSI_PIN               (GPIO_PIN_13)
    #define SPI1_MOSI_FUNC              (GPIO_FUNC_41)

    #define SPI1_MISO_PORT              (GPIO_PORT_B)
    #define SPI1_MISO_PIN               (GPIO_PIN_12)
    #define SPI1_MISO_FUNC              (GPIO_FUNC_42)

    #define SPI1_WP_PORT                (GPIO_PORT_B)
    #define SPI1_WP_PIN                 (GPIO_PIN_10)

    #define SPI1_HOLD_PORT              (GPIO_PORT_B)
    #define SPI1_HOLD_PIN               (GPIO_PIN_02)
#endif

/************************* ETH port ***********************/

#if defined(BSP_USING_ETH)
    #if defined(ETH_INTERFACE_USING_RMII)
        #define ETH_SMI_MDIO_PORT       (GPIO_PORT_A)
        #define ETH_SMI_MDIO_PIN        (GPIO_PIN_02)
        #define ETH_SMI_MDIO_FUNC       (GPIO_FUNC_11)

        #define ETH_SMI_MDC_PORT        (GPIO_PORT_C)
        #define ETH_SMI_MDC_PIN         (GPIO_PIN_01)
        #define ETH_SMI_MDC_FUNC        (GPIO_FUNC_11)

        #define ETH_RMII_TX_EN_PORT     (GPIO_PORT_G)
        #define ETH_RMII_TX_EN_PIN      (GPIO_PIN_11)
        #define ETH_RMII_TX_EN_FUNC     (GPIO_FUNC_11)

        #define ETH_RMII_TXD0_PORT      (GPIO_PORT_G)
        #define ETH_RMII_TXD0_PIN       (GPIO_PIN_13)
        #define ETH_RMII_TXD0_FUNC      (GPIO_FUNC_11)

        #define ETH_RMII_TXD1_PORT      (GPIO_PORT_G)
        #define ETH_RMII_TXD1_PIN       (GPIO_PIN_14)
        #define ETH_RMII_TXD1_FUNC      (GPIO_FUNC_11)

        #define ETH_RMII_REF_CLK_PORT   (GPIO_PORT_A)
        #define ETH_RMII_REF_CLK_PIN    (GPIO_PIN_01)
        #define ETH_RMII_REF_CLK_FUNC   (GPIO_FUNC_11)

        #define ETH_RMII_CRS_DV_PORT    (GPIO_PORT_A)
        #define ETH_RMII_CRS_DV_PIN     (GPIO_PIN_07)
        #define ETH_RMII_CRS_DV_FUNC    (GPIO_FUNC_11)

        #define ETH_RMII_RXD0_PORT      (GPIO_PORT_C)
        #define ETH_RMII_RXD0_PIN       (GPIO_PIN_04)
        #define ETH_RMII_RXD0_FUNC      (GPIO_FUNC_11)

        #define ETH_RMII_RXD1_PORT      (GPIO_PORT_C)
        #define ETH_RMII_RXD1_PIN       (GPIO_PIN_05)
        #define ETH_RMII_RXD1_FUNC      (GPIO_FUNC_11)
    #else
        #define ETH_SMI_MDIO_PORT       (GPIO_PORT_A)
        #define ETH_SMI_MDIO_PIN        (GPIO_PIN_02)
        #define ETH_SMI_MDIO_FUNC       (GPIO_FUNC_11)

        #define ETH_SMI_MDC_PORT        (GPIO_PORT_C)
        #define ETH_SMI_MDC_PIN         (GPIO_PIN_01)
        #define ETH_SMI_MDC_FUNC        (GPIO_FUNC_11)

        #define ETH_MII_TX_CLK_PORT     (GPIO_PORT_B)
        #define ETH_MII_TX_CLK_PIN      (GPIO_PIN_06)
        #define ETH_MII_TX_CLK_FUNC     (GPIO_FUNC_11)

        #define ETH_MII_TX_EN_PORT      (GPIO_PORT_G)
        #define ETH_MII_TX_EN_PIN       (GPIO_PIN_11)
        #define ETH_MII_TX_EN_FUNC      (GPIO_FUNC_11)

        #define ETH_MII_TXD0_PORT       (GPIO_PORT_G)
        #define ETH_MII_TXD0_PIN        (GPIO_PIN_13)
        #define ETH_MII_TXD0_FUNC       (GPIO_FUNC_11)

        #define ETH_MII_TXD1_PORT       (GPIO_PORT_G)
        #define ETH_MII_TXD1_PIN        (GPIO_PIN_14)
        #define ETH_MII_TXD1_FUNC       (GPIO_FUNC_11)

        #define ETH_MII_TXD2_PORT       (GPIO_PORT_B)
        #define ETH_MII_TXD2_PIN        (GPIO_PIN_09)
        #define ETH_MII_TXD2_FUNC       (GPIO_FUNC_11)

        #define ETH_MII_TXD3_PORT       (GPIO_PORT_B)
        #define ETH_MII_TXD3_PIN        (GPIO_PIN_08)
        #define ETH_MII_TXD3_FUNC       (GPIO_FUNC_11)

        #define ETH_MII_RX_CLK_PORT     (GPIO_PORT_A)
        #define ETH_MII_RX_CLK_PIN      (GPIO_PIN_01)
        #define ETH_MII_RX_CLK_FUNC     (GPIO_FUNC_11)

        #define ETH_MII_RX_DV_PORT      (GPIO_PORT_A)
        #define ETH_MII_RX_DV_PIN       (GPIO_PIN_07)
        #define ETH_MII_RX_DV_FUNC      (GPIO_FUNC_11)

        #define ETH_MII_RXD0_PORT       (GPIO_PORT_C)
        #define ETH_MII_RXD0_PIN        (GPIO_PIN_04)
        #define ETH_MII_RXD0_FUNC       (GPIO_FUNC_11)

        #define ETH_MII_RXD1_PORT       (GPIO_PORT_C)
        #define ETH_MII_RXD1_PIN        (GPIO_PIN_05)
        #define ETH_MII_RXD1_FUNC       (GPIO_FUNC_11)

        #define ETH_MII_RXD2_PORT       (GPIO_PORT_B)
        #define ETH_MII_RXD2_PIN        (GPIO_PIN_00)
        #define ETH_MII_RXD2_FUNC       (GPIO_FUNC_11)

        #define ETH_MII_RXD3_PORT       (GPIO_PORT_B)
        #define ETH_MII_RXD3_PIN        (GPIO_PIN_01)
        #define ETH_MII_RXD3_FUNC       (GPIO_FUNC_11)

        #define ETH_MII_RX_ER_PORT      (GPIO_PORT_I)
        #define ETH_MII_RX_ER_PIN       (GPIO_PIN_10)
        #define ETH_MII_RX_ER_FUNC      (GPIO_FUNC_11)

        #define ETH_MII_CRS_PORT        (GPIO_PORT_H)
        #define ETH_MII_CRS_PIN         (GPIO_PIN_02)
        #define ETH_MII_CRS_FUNC        (GPIO_FUNC_11)

        #define ETH_MII_COL_PORT        (GPIO_PORT_H)
        #define ETH_MII_COL_PIN         (GPIO_PIN_03)
        #define ETH_MII_COL_FUNC        (GPIO_FUNC_11)
    #endif
#endif

/************************ NAND port **********************/
#if defined(BSP_USING_NAND)
    #define NAND_CE_PORT                    (GPIO_PORT_C)   /* PC02 - EXMC_CE0 */
    #define NAND_CE_PIN                     (GPIO_PIN_02)
    #define NAND_CE_FUNC                    (GPIO_FUNC_12)

    #define NAND_RE_PORT                    (GPIO_PORT_F)   /* PF11 - EXMC_OE */
    #define NAND_RE_PIN                     (GPIO_PIN_11)
    #define NAND_RE_FUNC                    (GPIO_FUNC_12)

    #define NAND_WE_PORT                    (GPIO_PORT_C)   /* PC00 - EXMC_WE */
    #define NAND_WE_PIN                     (GPIO_PIN_00)
    #define NAND_WE_FUNC                    (GPIO_FUNC_12)

    #define NAND_CLE_PORT                   (GPIO_PORT_I)   /* PI12 - EXMC_CLE */
    #define NAND_CLE_PIN                    (GPIO_PIN_12)
    #define NAND_CLE_FUNC                   (GPIO_FUNC_12)

    #define NAND_ALE_PORT                   (GPIO_PORT_C)   /* PC03 - EXMC_ALE */
    #define NAND_ALE_PIN                    (GPIO_PIN_03)
    #define NAND_ALE_FUNC                   (GPIO_FUNC_12)

    #define NAND_WP_PORT                    (GPIO_PORT_G)   /* PG15 - EXMC_BAA */
    #define NAND_WP_PIN                     (GPIO_PIN_15)
    #define NAND_WP_FUNC                    (GPIO_FUNC_12)

    #define NAND_RB_PORT                    (GPIO_PORT_G)   /* PG06 - EXMC_RB0 */
    #define NAND_RB_PIN                     (GPIO_PIN_06)
    #define NAND_RB_FUNC                    (GPIO_FUNC_12)

    #define NAND_DATA0_PORT                 (GPIO_PORT_D)   /* PD14 - EXMC_DATA0 */
    #define NAND_DATA0_PIN                  (GPIO_PIN_14)
    #define NAND_DATA0_FUNC                 (GPIO_FUNC_12)
    #define NAND_DATA1_PORT                 (GPIO_PORT_D)   /* PD15 - EXMC_DATA1 */
    #define NAND_DATA1_PIN                  (GPIO_PIN_15)
    #define NAND_DATA1_FUNC                 (GPIO_FUNC_12)
    #define NAND_DATA2_PORT                 (GPIO_PORT_D)   /* PD0 - EXMC_DATA2 */
    #define NAND_DATA2_PIN                  (GPIO_PIN_00)
    #define NAND_DATA2_FUNC                 (GPIO_FUNC_12)
    #define NAND_DATA3_PORT                 (GPIO_PORT_D)   /* PD1 - EXMC_DATA3 */
    #define NAND_DATA3_PIN                  (GPIO_PIN_01)
    #define NAND_DATA3_FUNC                 (GPIO_FUNC_12)
    #define NAND_DATA4_PORT                 (GPIO_PORT_E)   /* PE7 - EXMC_DATA4 */
    #define NAND_DATA4_PIN                  (GPIO_PIN_07)
    #define NAND_DATA4_FUNC                 (GPIO_FUNC_12)
    #define NAND_DATA5_PORT                 (GPIO_PORT_E)   /* PE8 - EXMC_DATA5 */
    #define NAND_DATA5_PIN                  (GPIO_PIN_08)
    #define NAND_DATA5_FUNC                 (GPIO_FUNC_12)
    #define NAND_DATA6_PORT                 (GPIO_PORT_E)   /* PE9 - EXMC_DATA6 */
    #define NAND_DATA6_PIN                  (GPIO_PIN_09)
    #define NAND_DATA6_FUNC                 (GPIO_FUNC_12)
    #define NAND_DATA7_PORT                 (GPIO_PORT_E)   /* PE10 - EXMC_DATA7 */
    #define NAND_DATA7_PIN                  (GPIO_PIN_10)
    #define NAND_DATA7_FUNC                 (GPIO_FUNC_12)
#endif

/************************ SDIOC port **********************/
#if defined(BSP_USING_SDIO1)
    #define SDIOC1_CK_PORT                  (GPIO_PORT_C)
    #define SDIOC1_CK_PIN                   (GPIO_PIN_12)
    #define SDIOC1_CK_FUNC                  (GPIO_FUNC_9)

    #define SDIOC1_CMD_PORT                 (GPIO_PORT_D)
    #define SDIOC1_CMD_PIN                  (GPIO_PIN_02)
    #define SDIOC1_CMD_FUNC                 (GPIO_FUNC_9)

    #define SDIOC1_D0_PORT                  (GPIO_PORT_B)
    #define SDIOC1_D0_PIN                   (GPIO_PIN_07)
    #define SDIOC1_D0_FUNC                  (GPIO_FUNC_9)

    #define SDIOC1_D1_PORT                  (GPIO_PORT_A)
    #define SDIOC1_D1_PIN                   (GPIO_PIN_08)
    #define SDIOC1_D1_FUNC                  (GPIO_FUNC_9)

    #define SDIOC1_D2_PORT                  (GPIO_PORT_C)
    #define SDIOC1_D2_PIN                   (GPIO_PIN_10)
    #define SDIOC1_D2_FUNC                  (GPIO_FUNC_9)

    #define SDIOC1_D3_PORT                  (GPIO_PORT_B)
    #define SDIOC1_D3_PIN                   (GPIO_PIN_05)
    #define SDIOC1_D3_FUNC                  (GPIO_FUNC_9)
#endif

/************************ SDRAM port **********************/
#if defined(BSP_USING_SDRAM)
    #define SDRAM_CKE_PORT                  (GPIO_PORT_C)   /* PC03 - EXMC_ALE */
    #define SDRAM_CKE_PIN                   (GPIO_PIN_03)
    #define SDRAM_CKE_FUNC                  (GPIO_FUNC_12)

    #define SDRAM_CLK_PORT                  (GPIO_PORT_G)   /* PD03 - EXMC_CLK */
    #define SDRAM_CLK_PIN                   (GPIO_PIN_08)
    #define SDRAM_CLK_FUNC                  (GPIO_FUNC_12)

    #define SDRAM_DQM0_PORT                 (GPIO_PORT_E)   /* PE00 - EXMC_CE4 */
    #define SDRAM_DQM0_PIN                  (GPIO_PIN_00)
    #define SDRAM_DQM0_FUNC                 (GPIO_FUNC_12)
    #define SDRAM_DQM1_PORT                 (GPIO_PORT_E)   /* PE01 - EXMC_CE5 */
    #define SDRAM_DQM1_PIN                  (GPIO_PIN_01)
    #define SDRAM_DQM1_FUNC                 (GPIO_FUNC_12)

    #define SDRAM_BA0_PORT                  (GPIO_PORT_D)   /* PD11 - EXMC_ADD16 */
    #define SDRAM_BA0_PIN                   (GPIO_PIN_11)
    #define SDRAM_BA0_FUNC                  (GPIO_FUNC_12)
    #define SDRAM_BA1_PORT                  (GPIO_PORT_D)   /* PD12 - EXMC_ADD17 */
    #define SDRAM_BA1_PIN                   (GPIO_PIN_12)
    #define SDRAM_BA1_FUNC                  (GPIO_FUNC_12)

    #define SDRAM_CS_PORT                   (GPIO_PORT_G)   /* PG09 - EXMC_CE1 */
    #define SDRAM_CS_PIN                    (GPIO_PIN_09)
    #define SDRAM_CS_FUNC                   (GPIO_FUNC_12)

    #define SDRAM_RAS_PORT                  (GPIO_PORT_F)   /* PF11 - EXMC_OE */
    #define SDRAM_RAS_PIN                   (GPIO_PIN_11)
    #define SDRAM_RAS_FUNC                  (GPIO_FUNC_12)

    #define SDRAM_CAS_PORT                  (GPIO_PORT_G)   /* PG15 - EXMC_BAA */
    #define SDRAM_CAS_PIN                   (GPIO_PIN_15)
    #define SDRAM_CAS_FUNC                  (GPIO_FUNC_12)

    #define SDRAM_WE_PORT                   (GPIO_PORT_C)   /* PC00 - EXMC_WE */
    #define SDRAM_WE_PIN                    (GPIO_PIN_00)
    #define SDRAM_WE_FUNC                   (GPIO_FUNC_12)

    #define SDRAM_ADD0_PORT                 (GPIO_PORT_F)   /* PF00 - EXMC_ADD0 */
    #define SDRAM_ADD0_PIN                  (GPIO_PIN_00)
    #define SDRAM_ADD0_FUNC                 (GPIO_FUNC_12)

    #define SDRAM_ADD1_PORT                 (GPIO_PORT_F)   /* PF01 - EXMC_ADD1 */
    #define SDRAM_ADD1_PIN                  (GPIO_PIN_01)
    #define SDRAM_ADD1_FUNC                 (GPIO_FUNC_12)

    #define SDRAM_ADD2_PORT                 (GPIO_PORT_F)   /* PF02 - EXMC_ADD2 */
    #define SDRAM_ADD2_PIN                  (GPIO_PIN_02)
    #define SDRAM_ADD2_FUNC                 (GPIO_FUNC_12)

    #define SDRAM_ADD3_PORT                 (GPIO_PORT_F)   /* PF03 - EXMC_ADD3 */
    #define SDRAM_ADD3_PIN                  (GPIO_PIN_03)
    #define SDRAM_ADD3_FUNC                 (GPIO_FUNC_12)

    #define SDRAM_ADD4_PORT                 (GPIO_PORT_F)   /* PF04 - EXMC_ADD4 */
    #define SDRAM_ADD4_PIN                  (GPIO_PIN_04)
    #define SDRAM_ADD4_FUNC                 (GPIO_FUNC_12)

    #define SDRAM_ADD5_PORT                 (GPIO_PORT_F)   /* PF05 - EXMC_ADD5 */
    #define SDRAM_ADD5_PIN                  (GPIO_PIN_05)
    #define SDRAM_ADD5_FUNC                 (GPIO_FUNC_12)

    #define SDRAM_ADD6_PORT                 (GPIO_PORT_F)   /* PF12 - EXMC_ADD6 */
    #define SDRAM_ADD6_PIN                  (GPIO_PIN_12)
    #define SDRAM_ADD6_FUNC                 (GPIO_FUNC_12)

    #define SDRAM_ADD7_PORT                 (GPIO_PORT_F)   /* PF13 - EXMC_ADD7 */
    #define SDRAM_ADD7_PIN                  (GPIO_PIN_13)
    #define SDRAM_ADD7_FUNC                 (GPIO_FUNC_12)

    #define SDRAM_ADD8_PORT                 (GPIO_PORT_F)   /* PF14 - EXMC_ADD8 */
    #define SDRAM_ADD8_PIN                  (GPIO_PIN_14)
    #define SDRAM_ADD8_FUNC                 (GPIO_FUNC_12)

    #define SDRAM_ADD9_PORT                 (GPIO_PORT_F)   /* PF15 - EXMC_ADD9 */
    #define SDRAM_ADD9_PIN                  (GPIO_PIN_15)
    #define SDRAM_ADD9_FUNC                 (GPIO_FUNC_12)

    #define SDRAM_ADD10_PORT                (GPIO_PORT_G)   /* PG00 - EXMC_ADD10 */
    #define SDRAM_ADD10_PIN                 (GPIO_PIN_00)
    #define SDRAM_ADD10_FUNC                (GPIO_FUNC_12)

    #define SDRAM_ADD11_PORT                (GPIO_PORT_G)   /* PG01 - EXMC_ADD11 */
    #define SDRAM_ADD11_PIN                 (GPIO_PIN_01)
    #define SDRAM_ADD11_FUNC                (GPIO_FUNC_12)

    #define SDRAM_DATA0_PORT                (GPIO_PORT_D)   /* PD14 - EXMC_DATA0 */
    #define SDRAM_DATA0_PIN                 (GPIO_PIN_14)
    #define SDRAM_DATA0_FUNC                (GPIO_FUNC_12)
    #define SDRAM_DATA1_PORT                (GPIO_PORT_D)   /* PD15 - EXMC_DATA1 */
    #define SDRAM_DATA1_PIN                 (GPIO_PIN_15)
    #define SDRAM_DATA1_FUNC                (GPIO_FUNC_12)
    #define SDRAM_DATA2_PORT                (GPIO_PORT_D)   /* PD00 - EXMC_DATA2 */
    #define SDRAM_DATA2_PIN                 (GPIO_PIN_00)
    #define SDRAM_DATA2_FUNC                (GPIO_FUNC_12)
    #define SDRAM_DATA3_PORT                (GPIO_PORT_D)   /* PD01 - EXMC_DATA3 */
    #define SDRAM_DATA3_PIN                 (GPIO_PIN_01)
    #define SDRAM_DATA3_FUNC                (GPIO_FUNC_12)
    #define SDRAM_DATA4_PORT                (GPIO_PORT_E)   /* PE07 - EXMC_DATA4 */
    #define SDRAM_DATA4_PIN                 (GPIO_PIN_07)
    #define SDRAM_DATA4_FUNC                (GPIO_FUNC_12)
    #define SDRAM_DATA5_PORT                (GPIO_PORT_E)   /* PE08 - EXMC_DATA5 */
    #define SDRAM_DATA5_PIN                 (GPIO_PIN_08)
    #define SDRAM_DATA5_FUNC                (GPIO_FUNC_12)
    #define SDRAM_DATA6_PORT                (GPIO_PORT_E)   /* PE09 - EXMC_DATA6 */
    #define SDRAM_DATA6_PIN                 (GPIO_PIN_09)
    #define SDRAM_DATA6_FUNC                (GPIO_FUNC_12)
    #define SDRAM_DATA7_PORT                (GPIO_PORT_E)   /* PE10 - EXMC_DATA7 */
    #define SDRAM_DATA7_PIN                 (GPIO_PIN_10)
    #define SDRAM_DATA7_FUNC                (GPIO_FUNC_12)
    #define SDRAM_DATA8_PORT                (GPIO_PORT_E)   /* PE11 - EXMC_DATA8 */
    #define SDRAM_DATA8_PIN                 (GPIO_PIN_11)
    #define SDRAM_DATA8_FUNC                (GPIO_FUNC_12)
    #define SDRAM_DATA9_PORT                (GPIO_PORT_E)   /* PE12 - EXMC_DATA9 */
    #define SDRAM_DATA9_PIN                 (GPIO_PIN_12)
    #define SDRAM_DATA9_FUNC                (GPIO_FUNC_12)
    #define SDRAM_DATA10_PORT               (GPIO_PORT_E)   /* PE13 - EXMC_DATA10 */
    #define SDRAM_DATA10_PIN                (GPIO_PIN_13)
    #define SDRAM_DATA10_FUNC               (GPIO_FUNC_12)
    #define SDRAM_DATA11_PORT               (GPIO_PORT_E)   /* PE14 - EXMC_DATA11 */
    #define SDRAM_DATA11_PIN                (GPIO_PIN_14)
    #define SDRAM_DATA11_FUNC               (GPIO_FUNC_12)
    #define SDRAM_DATA12_PORT               (GPIO_PORT_E)   /* PE15 - EXMC_DATA12 */
    #define SDRAM_DATA12_PIN                (GPIO_PIN_15)
    #define SDRAM_DATA12_FUNC               (GPIO_FUNC_12)
    #define SDRAM_DATA13_PORT               (GPIO_PORT_D)   /* PD08 - EXMC_DATA13 */
    #define SDRAM_DATA13_PIN                (GPIO_PIN_08)
    #define SDRAM_DATA13_FUNC               (GPIO_FUNC_12)
    #define SDRAM_DATA14_PORT               (GPIO_PORT_D)   /* PD09 - EXMC_DATA14 */
    #define SDRAM_DATA14_PIN                (GPIO_PIN_09)
    #define SDRAM_DATA14_FUNC               (GPIO_FUNC_12)
    #define SDRAM_DATA15_PORT               (GPIO_PORT_D)   /* PD10 - EXMC_DATA15 */
    #define SDRAM_DATA15_PIN                (GPIO_PIN_10)
    #define SDRAM_DATA15_FUNC               (GPIO_FUNC_12)
#endif

/************************ RTC/PM *****************************/
#if defined(BSP_USING_RTC) || defined(RT_USING_PM)
    #if defined(BSP_RTC_USING_XTAL32) || defined(RT_USING_PM)
        #define XTAL32_PORT                     (GPIO_PORT_C)
        #define XTAL32_IN_PIN                   (GPIO_PIN_15)
        #define XTAL32_OUT_PIN                  (GPIO_PIN_14)
    #endif
#endif

#if defined(RT_USING_PWM)
    /***********  PWM_TMRA configure *********/
    #if defined(BSP_USING_PWM_TMRA_1)
        #if defined(BSP_USING_PWM_TMRA_1_CH1)
            #define PWM_TMRA_1_CH1_PORT             (GPIO_PORT_A)
            #define PWM_TMRA_1_CH1_PIN              (GPIO_PIN_08)
            #define PWM_TMRA_1_CH1_PIN_FUNC         (GPIO_FUNC_4)
        #endif
        #if defined(BSP_USING_PWM_TMRA_1_CH2)
            #define PWM_TMRA_1_CH2_PORT             (GPIO_PORT_A)
            #define PWM_TMRA_1_CH2_PIN              (GPIO_PIN_09)
            #define PWM_TMRA_1_CH2_PIN_FUNC         (GPIO_FUNC_4)
        #endif
        #if defined(BSP_USING_PWM_TMRA_1_CH3)
            #define PWM_TMRA_1_CH3_PORT             (GPIO_PORT_A)
            #define PWM_TMRA_1_CH3_PIN              (GPIO_PIN_10)
            #define PWM_TMRA_1_CH3_PIN_FUNC         (GPIO_FUNC_4)
        #endif
        #if defined(BSP_USING_PWM_TMRA_1_CH4)
            #define PWM_TMRA_1_CH4_PORT             (GPIO_PORT_A)
            #define PWM_TMRA_1_CH4_PIN              (GPIO_PIN_11)
            #define PWM_TMRA_1_CH4_PIN_FUNC         (GPIO_FUNC_4)
        #endif
    #endif

    /***********  PWM_TMR4 configure *********/
    #if defined(BSP_USING_PWM_TMR4_1)
        #if defined(BSP_USING_PWM_TMR4_1_OUH)
            #define PWM_TMR4_1_OUH_PORT             (GPIO_PORT_E)
            #define PWM_TMR4_1_OUH_PIN              (GPIO_PIN_09)
            #define PWM_TMR4_1_OUH_PIN_FUNC         (GPIO_FUNC_2)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OUL)
            #define PWM_TMR4_1_OUL_PORT             (GPIO_PORT_E)
            #define PWM_TMR4_1_OUL_PIN              (GPIO_PIN_08)
            #define PWM_TMR4_1_OUL_PIN_FUNC         (GPIO_FUNC_2)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OVH)
            #define PWM_TMR4_1_OVH_PORT             (GPIO_PORT_E)
            #define PWM_TMR4_1_OVH_PIN              (GPIO_PIN_11)
            #define PWM_TMR4_1_OVH_PIN_FUNC         (GPIO_FUNC_2)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OVL)
            #define PWM_TMR4_1_OVL_PORT             (GPIO_PORT_E)
            #define PWM_TMR4_1_OVL_PIN              (GPIO_PIN_10)
            #define PWM_TMR4_1_OVL_PIN_FUNC         (GPIO_FUNC_2)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OWH)
            #define PWM_TMR4_1_OWH_PORT             (GPIO_PORT_E)
            #define PWM_TMR4_1_OWH_PIN              (GPIO_PIN_13)
            #define PWM_TMR4_1_OWH_PIN_FUNC         (GPIO_FUNC_2)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OWL)
            #define PWM_TMR4_1_OWL_PORT             (GPIO_PORT_E)
            #define PWM_TMR4_1_OWL_PIN              (GPIO_PIN_12)
            #define PWM_TMR4_1_OWL_PIN_FUNC         (GPIO_FUNC_2)
        #endif
    #endif

    /***********  PWM_TMR6 configure *********/
    #if defined(BSP_USING_PWM_TMR6_1)
        #if defined(BSP_USING_PWM_TMR6_1_A)
            #define PWM_TMR6_1_A_PORT               (GPIO_PORT_F)
            #define PWM_TMR6_1_A_PIN                (GPIO_PIN_13)
            #define PWM_TMR6_1_A_PIN_FUNC           (GPIO_FUNC_3)
        #endif
        #if defined(BSP_USING_PWM_TMR6_1_B)
            #define PWM_TMR6_1_B_PORT               (GPIO_PORT_F)
            #define PWM_TMR6_1_B_PIN                (GPIO_PIN_14)
            #define PWM_TMR6_1_B_PIN_FUNC           (GPIO_FUNC_3)
        #endif
    #endif

#endif

#if defined(BSP_USING_USBD) || defined(BSP_USING_USBH)
    #if defined(BSP_USING_USBFS)
        /* USBFS Core*/
        #define USBF_DP_PORT                    (GPIO_PORT_A)
        #define USBF_DP_PIN                     (GPIO_PIN_12)
        #define USBF_DP_FUNC                    (GPIO_FUNC_10)
        #define USBF_DM_PORT                    (GPIO_PORT_A)
        #define USBF_DM_PIN                     (GPIO_PIN_11)
        #define USBF_DM_FUNC                    (GPIO_FUNC_10)
        #define USBF_VBUS_PORT                  (GPIO_PORT_A)
        #define USBF_VBUS_PIN                   (GPIO_PIN_09)
        #define USBF_VBUS_FUNC                  (GPIO_FUNC_10)
        #define USBF_DRVVBUS_PORT               (GPIO_PORT_C)
        #define USBF_DRVVBUS_PIN                (GPIO_PIN_09)
        #define USBF_DRVVBUS_FUNC               (GPIO_FUNC_10)
    #elif defined(BSP_USING_USBHS)
        /* USBHS Core*/
        #if defined(BSP_USING_USBHS_PHY_EMBED)
            #define USBH_DP_PORT                    (GPIO_PORT_B)
            #define USBH_DP_PIN                     (GPIO_PIN_15)
            #define USBH_DP_FUNC                    (GPIO_FUNC_10)
            #define USBH_DM_PORT                    (GPIO_PORT_B)
            #define USBH_DM_PIN                     (GPIO_PIN_14)
            #define USBH_DM_FUNC                    (GPIO_FUNC_10)
            #define USBH_VBUS_PORT                  (GPIO_PORT_B)
            #define USBH_VBUS_PIN                   (GPIO_PIN_13)
            #define USBH_VBUS_FUNC                  (GPIO_FUNC_12)
            #define USBH_DRVVBUS_PORT               (GPIO_PORT_B)
            #define USBH_DRVVBUS_PIN                (GPIO_PIN_11)
            #define USBH_DRVVBUS_FUNC               (GPIO_FUNC_10)
        #else
            /* USBHS Core, external PHY */
            #define USBH_ULPI_CLK_PORT              (GPIO_PORT_E)
            #define USBH_ULPI_CLK_PIN               (GPIO_PIN_12)
            #define USBH_ULPI_CLK_FUNC              (GPIO_FUNC_10)
            #define USBH_ULPI_DIR_PORT              (GPIO_PORT_C)
            #define USBH_ULPI_DIR_PIN               (GPIO_PIN_02)
            #define USBH_ULPI_DIR_FUNC              (GPIO_FUNC_10)
            #define USBH_ULPI_NXT_PORT              (GPIO_PORT_C)
            #define USBH_ULPI_NXT_PIN               (GPIO_PIN_03)
            #define USBH_ULPI_NXT_FUNC              (GPIO_FUNC_10)
            #define USBH_ULPI_STP_PORT              (GPIO_PORT_C)
            #define USBH_ULPI_STP_PIN               (GPIO_PIN_00)
            #define USBH_ULPI_STP_FUNC              (GPIO_FUNC_10)
            #define USBH_ULPI_D0_PORT               (GPIO_PORT_E)
            #define USBH_ULPI_D0_PIN                (GPIO_PIN_13)
            #define USBH_ULPI_D0_FUNC               (GPIO_FUNC_10)
            #define USBH_ULPI_D1_PORT               (GPIO_PORT_E)
            #define USBH_ULPI_D1_PIN                (GPIO_PIN_14)
            #define USBH_ULPI_D1_FUNC               (GPIO_FUNC_10)
            #define USBH_ULPI_D2_PORT               (GPIO_PORT_E)
            #define USBH_ULPI_D2_PIN                (GPIO_PIN_15)
            #define USBH_ULPI_D2_FUNC               (GPIO_FUNC_10)
            #define USBH_ULPI_D3_PORT               (GPIO_PORT_B)
            #define USBH_ULPI_D3_PIN                (GPIO_PIN_10)
            #define USBH_ULPI_D3_FUNC               (GPIO_FUNC_10)
            #define USBH_ULPI_D4_PORT               (GPIO_PORT_B)
            #define USBH_ULPI_D4_PIN                (GPIO_PIN_11)
            #define USBH_ULPI_D4_FUNC               (GPIO_FUNC_10)
            #define USBH_ULPI_D5_PORT               (GPIO_PORT_B)
            #define USBH_ULPI_D5_PIN                (GPIO_PIN_12)
            #define USBH_ULPI_D5_FUNC               (GPIO_FUNC_10)
            #define USBH_ULPI_D6_PORT               (GPIO_PORT_B)
            #define USBH_ULPI_D6_PIN                (GPIO_PIN_13)
            #define USBH_ULPI_D6_FUNC               (GPIO_FUNC_10)
            #define USBH_ULPI_D7_PORT               (GPIO_PORT_E)
            #define USBH_ULPI_D7_PIN                (GPIO_PIN_11)
            #define USBH_ULPI_D7_FUNC               (GPIO_FUNC_10)
            /* 3300 reset */
            #define USB_3300_RESET_PORT             (EIO_PORT1)
            #define USB_3300_RESET_PIN              (EIO_USB3300_RST)
        #endif
    #endif
#endif

#if defined(BSP_USING_QSPI)
    #ifndef BSP_QSPI_USING_SOFT_CS
        /* QSSN */
        #define QSPI_FLASH_CS_PORT              (GPIO_PORT_C)
        #define QSPI_FLASH_CS_PIN               (GPIO_PIN_07)
        #define QSPI_FLASH_CS_FUNC              (GPIO_FUNC_18)
    #endif
    /* QSCK */
    #define QSPI_FLASH_SCK_PORT             (GPIO_PORT_C)
    #define QSPI_FLASH_SCK_PIN              (GPIO_PIN_06)
    #define QSPI_FLASH_SCK_FUNC             (GPIO_FUNC_18)
    /* QSIO0 */
    #define QSPI_FLASH_IO0_PORT             (GPIO_PORT_B)
    #define QSPI_FLASH_IO0_PIN              (GPIO_PIN_13)
    #define QSPI_FLASH_IO0_FUNC             (GPIO_FUNC_18)
    /* QSIO1 */
    #define QSPI_FLASH_IO1_PORT             (GPIO_PORT_B)
    #define QSPI_FLASH_IO1_PIN              (GPIO_PIN_12)
    #define QSPI_FLASH_IO1_FUNC             (GPIO_FUNC_18)
    /* QSIO2 */
    #define QSPI_FLASH_IO2_PORT             (GPIO_PORT_B)
    #define QSPI_FLASH_IO2_PIN              (GPIO_PIN_10)
    #define QSPI_FLASH_IO2_FUNC             (GPIO_FUNC_18)
    /* QSIO3 */
    #define QSPI_FLASH_IO3_PORT             (GPIO_PORT_B)
    #define QSPI_FLASH_IO3_PIN              (GPIO_PIN_02)
    #define QSPI_FLASH_IO3_FUNC             (GPIO_FUNC_18)
#endif

/*********** TMRA_PULSE_ENCODER configure *********/
#if defined(RT_USING_PULSE_ENCODER)
    #if defined(BSP_USING_TMRA_PULSE_ENCODER)
        #if defined(BSP_USING_PULSE_ENCODER_TMRA_1)
            #define PULSE_ENCODER_TMRA_1_A_PORT      (GPIO_PORT_A)
            #define PULSE_ENCODER_TMRA_1_A_PIN       (GPIO_PIN_08)
            #define PULSE_ENCODER_TMRA_1_A_PIN_FUNC  (GPIO_FUNC_4)
            #define PULSE_ENCODER_TMRA_1_B_PORT      (GPIO_PORT_A)
            #define PULSE_ENCODER_TMRA_1_B_PIN       (GPIO_PIN_09)
            #define PULSE_ENCODER_TMRA_1_B_PIN_FUNC  (GPIO_FUNC_4)
        #endif /* BSP_USING_PULSE_ENCODER_TMRA_1 */
    #endif /* BSP_USING_TMRA_PULSE_ENCODER */

    #if defined(BSP_USING_TMR6_PULSE_ENCODER)
        #if defined(BSP_USING_PULSE_ENCODER_TMR6_1)
            #define PULSE_ENCODER_TMR6_1_A_PORT      (GPIO_PORT_B)
            #define PULSE_ENCODER_TMR6_1_A_PIN       (GPIO_PIN_09)
            #define PULSE_ENCODER_TMR6_1_A_PIN_FUNC  (GPIO_FUNC_3)
            #define PULSE_ENCODER_TMR6_1_B_PORT      (GPIO_PORT_B)
            #define PULSE_ENCODER_TMR6_1_B_PIN       (GPIO_PIN_08)
            #define PULSE_ENCODER_TMR6_1_B_PIN_FUNC  (GPIO_FUNC_3)
        #endif /* BSP_USING_PULSE_ENCODER_TMR6_1 */
    #endif /* BSP_USING_TMR6_PULSE_ENCODER */
#endif /* RT_USING_PULSE_ENCODER */

#endif

