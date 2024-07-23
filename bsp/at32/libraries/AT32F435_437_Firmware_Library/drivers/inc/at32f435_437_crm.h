/**
  **************************************************************************
  * @file     at32f435_437_crm.h
  * @brief    at32f435_437 crm header file
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F435_437_CRM_H
#define __AT32F435_437_CRM_H

#ifdef __cplusplus
extern "C" {
#endif


/* includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_periph_driver
  * @{
  */

/** @addtogroup CRM
  * @{
  */

#define CRM_REG(value)                   PERIPH_REG(CRM_BASE, value)
#define CRM_REG_BIT(value)               PERIPH_REG_BIT(value)

/** @defgroup CRM_flags_definition
  * @brief crm flag
  * @{
  */

#define CRM_HICK_STABLE_FLAG             MAKE_VALUE(0x00, 1)  /*!< high speed internal clock stable flag */
#define CRM_HEXT_STABLE_FLAG             MAKE_VALUE(0x00, 17) /*!< high speed external crystal stable flag */
#define CRM_PLL_STABLE_FLAG              MAKE_VALUE(0x00, 25) /*!< phase locking loop stable flag */
#define CRM_LEXT_STABLE_FLAG             MAKE_VALUE(0x70, 1)  /*!< low speed external crystal stable flag */
#define CRM_LICK_STABLE_FLAG             MAKE_VALUE(0x74, 1)  /*!< low speed internal clock stable flag */
#define CRM_ALL_RESET_FLAG               MAKE_VALUE(0x74, 24) /*!< all reset flag */
#define CRM_NRST_RESET_FLAG              MAKE_VALUE(0x74, 26) /*!< nrst pin reset flag */
#define CRM_POR_RESET_FLAG               MAKE_VALUE(0x74, 27) /*!< power on reset flag */
#define CRM_SW_RESET_FLAG                MAKE_VALUE(0x74, 28) /*!< software reset flag */
#define CRM_WDT_RESET_FLAG               MAKE_VALUE(0x74, 29) /*!< watchdog timer reset flag */
#define CRM_WWDT_RESET_FLAG              MAKE_VALUE(0x74, 30) /*!< window watchdog timer reset flag */
#define CRM_LOWPOWER_RESET_FLAG          MAKE_VALUE(0x74, 31) /*!< low-power reset flag */
#define CRM_LICK_READY_INT_FLAG          MAKE_VALUE(0x0C, 0)  /*!< low speed internal clock stable interrupt ready flag */
#define CRM_LEXT_READY_INT_FLAG          MAKE_VALUE(0x0C, 1)  /*!< low speed external crystal stable interrupt ready flag */
#define CRM_HICK_READY_INT_FLAG          MAKE_VALUE(0x0C, 2)  /*!< high speed internal clock stable interrupt ready flag */
#define CRM_HEXT_READY_INT_FLAG          MAKE_VALUE(0x0C, 3)  /*!< high speed external crystal stable interrupt ready flag */
#define CRM_PLL_READY_INT_FLAG           MAKE_VALUE(0x0C, 4)  /*!< phase locking loop stable interrupt ready flag */
#define CRM_CLOCK_FAILURE_INT_FLAG       MAKE_VALUE(0x0C, 7)  /*!< clock failure interrupt ready flag */

/**
  * @}
  */

/** @defgroup CRM_interrupts_definition
  * @brief crm interrupt
  * @{
  */

#define CRM_LICK_STABLE_INT              ((uint32_t)0x00000100) /*!< low speed internal clock stable interrupt */
#define CRM_LEXT_STABLE_INT              ((uint32_t)0x00000200) /*!< low speed external crystal stable interrupt */
#define CRM_HICK_STABLE_INT              ((uint32_t)0x00000400) /*!< high speed internal clock stable interrupt */
#define CRM_HEXT_STABLE_INT              ((uint32_t)0x00000800) /*!< high speed external crystal stable interrupt */
#define CRM_PLL_STABLE_INT               ((uint32_t)0x00001000) /*!< phase locking loop stable interrupt */
#define CRM_CLOCK_FAILURE_INT            ((uint32_t)0x00800000) /*!< clock failure interrupt */

/**
  * @}
  */

/** @defgroup CRM_exported_types
  * @{
  */

/**
  * @brief crm periph clock
  */
typedef enum
{
#if defined (AT32F435xx)
  /* ahb periph1 */
  CRM_GPIOA_PERIPH_CLOCK                 = MAKE_VALUE(0x30, 0),  /*!< gpioa periph clock */
  CRM_GPIOB_PERIPH_CLOCK                 = MAKE_VALUE(0x30, 1),  /*!< gpiob periph clock */
  CRM_GPIOC_PERIPH_CLOCK                 = MAKE_VALUE(0x30, 2),  /*!< gpioc periph clock */
  CRM_GPIOD_PERIPH_CLOCK                 = MAKE_VALUE(0x30, 3),  /*!< gpiod periph clock */
  CRM_GPIOE_PERIPH_CLOCK                 = MAKE_VALUE(0x30, 4),  /*!< gpioe periph clock */
  CRM_GPIOF_PERIPH_CLOCK                 = MAKE_VALUE(0x30, 5),  /*!< gpiof periph clock */
  CRM_GPIOG_PERIPH_CLOCK                 = MAKE_VALUE(0x30, 6),  /*!< gpiog periph clock */
  CRM_GPIOH_PERIPH_CLOCK                 = MAKE_VALUE(0x30, 7),  /*!< gpioh periph clock */
  CRM_CRC_PERIPH_CLOCK                   = MAKE_VALUE(0x30, 12), /*!< crc periph clock */
  CRM_EDMA_PERIPH_CLOCK                  = MAKE_VALUE(0x30, 21), /*!< edma periph clock */
  CRM_DMA1_PERIPH_CLOCK                  = MAKE_VALUE(0x30, 22), /*!< dma1 periph clock */
  CRM_DMA2_PERIPH_CLOCK                  = MAKE_VALUE(0x30, 24), /*!< dma2 periph clock */
  CRM_OTGFS2_PERIPH_CLOCK                = MAKE_VALUE(0x30, 29), /*!< otgfs2 periph clock */
  /* ahb periph2 */
  CRM_DVP_PERIPH_CLOCK                   = MAKE_VALUE(0x34, 0),  /*!< dvp periph clock */
  CRM_OTGFS1_PERIPH_CLOCK                = MAKE_VALUE(0x34, 7),  /*!< otgfs1 periph clock */
  CRM_SDIO1_PERIPH_CLOCK                 = MAKE_VALUE(0x34, 15), /*!< sdio1 periph clock */
  /* ahb periph3 */
  CRM_XMC_PERIPH_CLOCK                   = MAKE_VALUE(0x38, 0),  /*!< xmc periph clock */
  CRM_QSPI1_PERIPH_CLOCK                 = MAKE_VALUE(0x38, 1),  /*!< qspi1 periph clock */
  CRM_QSPI2_PERIPH_CLOCK                 = MAKE_VALUE(0x38, 14), /*!< qspi2 periph clock */
  CRM_SDIO2_PERIPH_CLOCK                 = MAKE_VALUE(0x38, 15), /*!< sdio2 periph clock */
  /* apb1 periph */
  CRM_TMR2_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 0),  /*!< tmr2 periph clock */
  CRM_TMR3_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 1),  /*!< tmr3 periph clock */
  CRM_TMR4_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 2),  /*!< tmr4 periph clock */
  CRM_TMR5_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 3),  /*!< tmr5 periph clock */
  CRM_TMR6_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 4),  /*!< tmr6 periph clock */
  CRM_TMR7_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 5),  /*!< tmr7 periph clock */
  CRM_TMR12_PERIPH_CLOCK                 = MAKE_VALUE(0x40, 6),  /*!< tmr12 periph clock */
  CRM_TMR13_PERIPH_CLOCK                 = MAKE_VALUE(0x40, 7),  /*!< tmr13 periph clock */
  CRM_TMR14_PERIPH_CLOCK                 = MAKE_VALUE(0x40, 8),  /*!< tmr14 periph clock */
  CRM_WWDT_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 11), /*!< wwdt periph clock */
  CRM_SPI2_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 14), /*!< spi2 periph clock */
  CRM_SPI3_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 15), /*!< spi3 periph clock */
  CRM_USART2_PERIPH_CLOCK                = MAKE_VALUE(0x40, 17), /*!< usart2 periph clock */
  CRM_USART3_PERIPH_CLOCK                = MAKE_VALUE(0x40, 18), /*!< usart3 periph clock */
  CRM_UART4_PERIPH_CLOCK                 = MAKE_VALUE(0x40, 19), /*!< uart4 periph clock */
  CRM_UART5_PERIPH_CLOCK                 = MAKE_VALUE(0x40, 20), /*!< uart5 periph clock */
  CRM_I2C1_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 21), /*!< i2c1 periph clock */
  CRM_I2C2_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 22), /*!< i2c2 periph clock */
  CRM_I2C3_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 23), /*!< i2c3 periph clock */
  CRM_CAN1_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 25), /*!< can1 periph clock */
  CRM_CAN2_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 26), /*!< can2 periph clock */
  CRM_PWC_PERIPH_CLOCK                   = MAKE_VALUE(0x40, 28), /*!< pwc periph clock */
  CRM_DAC_PERIPH_CLOCK                   = MAKE_VALUE(0x40, 29), /*!< dac periph clock */
  CRM_UART7_PERIPH_CLOCK                 = MAKE_VALUE(0x40, 30), /*!< uart7 periph clock */
  CRM_UART8_PERIPH_CLOCK                 = MAKE_VALUE(0x40, 31), /*!< uart8 periph clock */
  /* apb2 periph */
  CRM_TMR1_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 0),  /*!< tmr1 periph clock */
  CRM_TMR8_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 1),  /*!< tmr8 periph clock */
  CRM_USART1_PERIPH_CLOCK                = MAKE_VALUE(0x44, 4),  /*!< usart1 periph clock */
  CRM_USART6_PERIPH_CLOCK                = MAKE_VALUE(0x44, 5),  /*!< usart6 periph clock */
  CRM_ADC1_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 8),  /*!< adc1 periph clock */
  CRM_ADC2_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 9),  /*!< adc2 periph clock */
  CRM_ADC3_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 10), /*!< adc3 periph clock */
  CRM_SPI1_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 12), /*!< spi1 periph clock */
  CRM_SPI4_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 13), /*!< spi4 periph clock */
  CRM_SCFG_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 14), /*!< scfg periph clock */
  CRM_TMR9_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 16), /*!< tmr9 periph clock */
  CRM_TMR10_PERIPH_CLOCK                 = MAKE_VALUE(0x44, 17), /*!< tmr10 periph clock */
  CRM_TMR11_PERIPH_CLOCK                 = MAKE_VALUE(0x44, 18), /*!< tmr11 periph clock */
  CRM_TMR20_PERIPH_CLOCK                 = MAKE_VALUE(0x44, 20), /*!< tmr20 periph clock */
  CRM_ACC_PERIPH_CLOCK                   = MAKE_VALUE(0x44, 29)  /*!< acc periph clock */
#endif

#if defined (AT32F437xx)
  /* ahb periph1 */
  CRM_GPIOA_PERIPH_CLOCK                 = MAKE_VALUE(0x30, 0),  /*!< gpioa periph clock */
  CRM_GPIOB_PERIPH_CLOCK                 = MAKE_VALUE(0x30, 1),  /*!< gpiob periph clock */
  CRM_GPIOC_PERIPH_CLOCK                 = MAKE_VALUE(0x30, 2),  /*!< gpioc periph clock */
  CRM_GPIOD_PERIPH_CLOCK                 = MAKE_VALUE(0x30, 3),  /*!< gpiod periph clock */
  CRM_GPIOE_PERIPH_CLOCK                 = MAKE_VALUE(0x30, 4),  /*!< gpioe periph clock */
  CRM_GPIOF_PERIPH_CLOCK                 = MAKE_VALUE(0x30, 5),  /*!< gpiof periph clock */
  CRM_GPIOG_PERIPH_CLOCK                 = MAKE_VALUE(0x30, 6),  /*!< gpiog periph clock */
  CRM_GPIOH_PERIPH_CLOCK                 = MAKE_VALUE(0x30, 7),  /*!< gpioh periph clock */
  CRM_CRC_PERIPH_CLOCK                   = MAKE_VALUE(0x30, 12), /*!< crc periph clock */
  CRM_EDMA_PERIPH_CLOCK                  = MAKE_VALUE(0x30, 21), /*!< edma periph clock */
  CRM_DMA1_PERIPH_CLOCK                  = MAKE_VALUE(0x30, 22), /*!< dma1 periph clock */
  CRM_DMA2_PERIPH_CLOCK                  = MAKE_VALUE(0x30, 24), /*!< dma2 periph clock */
  CRM_EMAC_PERIPH_CLOCK                  = MAKE_VALUE(0x30, 25), /*!< emac periph clock */
  CRM_EMACTX_PERIPH_CLOCK                = MAKE_VALUE(0x30, 26), /*!< emac tx periph clock */
  CRM_EMACRX_PERIPH_CLOCK                = MAKE_VALUE(0x30, 27), /*!< emac rx periph clock */
  CRM_EMACPTP_PERIPH_CLOCK               = MAKE_VALUE(0x30, 28), /*!< emac ptp periph clock */
  CRM_OTGFS2_PERIPH_CLOCK                = MAKE_VALUE(0x30, 29), /*!< otgfs2 periph clock */
  /* ahb periph2 */
  CRM_DVP_PERIPH_CLOCK                   = MAKE_VALUE(0x34, 0),  /*!< dvp periph clock */
  CRM_OTGFS1_PERIPH_CLOCK                = MAKE_VALUE(0x34, 7),  /*!< otgfs1 periph clock */
  CRM_SDIO1_PERIPH_CLOCK                 = MAKE_VALUE(0x34, 15), /*!< sdio1 periph clock */
  /* ahb periph3 */
  CRM_XMC_PERIPH_CLOCK                   = MAKE_VALUE(0x38, 0),  /*!< xmc periph clock */
  CRM_QSPI1_PERIPH_CLOCK                 = MAKE_VALUE(0x38, 1),  /*!< qspi1 periph clock */
  CRM_QSPI2_PERIPH_CLOCK                 = MAKE_VALUE(0x38, 14), /*!< qspi2 periph clock */
  CRM_SDIO2_PERIPH_CLOCK                 = MAKE_VALUE(0x38, 15), /*!< sdio2 periph clock */
  /* apb1 periph */
  CRM_TMR2_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 0),  /*!< tmr2 periph clock */
  CRM_TMR3_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 1),  /*!< tmr3 periph clock */
  CRM_TMR4_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 2),  /*!< tmr4 periph clock */
  CRM_TMR5_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 3),  /*!< tmr5 periph clock */
  CRM_TMR6_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 4),  /*!< tmr6 periph clock */
  CRM_TMR7_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 5),  /*!< tmr7 periph clock */
  CRM_TMR12_PERIPH_CLOCK                 = MAKE_VALUE(0x40, 6),  /*!< tmr12 periph clock */
  CRM_TMR13_PERIPH_CLOCK                 = MAKE_VALUE(0x40, 7),  /*!< tmr13 periph clock */
  CRM_TMR14_PERIPH_CLOCK                 = MAKE_VALUE(0x40, 8),  /*!< tmr14 periph clock */
  CRM_WWDT_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 11), /*!< wwdt periph clock */
  CRM_SPI2_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 14), /*!< spi2 periph clock */
  CRM_SPI3_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 15), /*!< spi3 periph clock */
  CRM_USART2_PERIPH_CLOCK                = MAKE_VALUE(0x40, 17), /*!< usart2 periph clock */
  CRM_USART3_PERIPH_CLOCK                = MAKE_VALUE(0x40, 18), /*!< usart3 periph clock */
  CRM_UART4_PERIPH_CLOCK                 = MAKE_VALUE(0x40, 19), /*!< uart4 periph clock */
  CRM_UART5_PERIPH_CLOCK                 = MAKE_VALUE(0x40, 20), /*!< uart5 periph clock */
  CRM_I2C1_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 21), /*!< i2c1 periph clock */
  CRM_I2C2_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 22), /*!< i2c2 periph clock */
  CRM_I2C3_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 23), /*!< i2c3 periph clock */
  CRM_CAN1_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 25), /*!< can1 periph clock */
  CRM_CAN2_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 26), /*!< can2 periph clock */
  CRM_PWC_PERIPH_CLOCK                   = MAKE_VALUE(0x40, 28), /*!< pwc periph clock */
  CRM_DAC_PERIPH_CLOCK                   = MAKE_VALUE(0x40, 29), /*!< dac periph clock */
  CRM_UART7_PERIPH_CLOCK                 = MAKE_VALUE(0x40, 30), /*!< uart7 periph clock */
  CRM_UART8_PERIPH_CLOCK                 = MAKE_VALUE(0x40, 31), /*!< uart8 periph clock */
  /* apb2 periph */
  CRM_TMR1_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 0),  /*!< tmr1 periph clock */
  CRM_TMR8_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 1),  /*!< tmr8 periph clock */
  CRM_USART1_PERIPH_CLOCK                = MAKE_VALUE(0x44, 4),  /*!< usart1 periph clock */
  CRM_USART6_PERIPH_CLOCK                = MAKE_VALUE(0x44, 5),  /*!< usart6 periph clock */
  CRM_ADC1_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 8),  /*!< adc1 periph clock */
  CRM_ADC2_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 9),  /*!< adc2 periph clock */
  CRM_ADC3_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 10), /*!< adc3 periph clock */
  CRM_SPI1_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 12), /*!< spi1 periph clock */
  CRM_SPI4_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 13), /*!< spi4 periph clock */
  CRM_SCFG_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 14), /*!< scfg periph clock */
  CRM_TMR9_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 16), /*!< tmr9 periph clock */
  CRM_TMR10_PERIPH_CLOCK                 = MAKE_VALUE(0x44, 17), /*!< tmr10 periph clock */
  CRM_TMR11_PERIPH_CLOCK                 = MAKE_VALUE(0x44, 18), /*!< tmr11 periph clock */
  CRM_TMR20_PERIPH_CLOCK                 = MAKE_VALUE(0x44, 20), /*!< tmr20 periph clock */
  CRM_ACC_PERIPH_CLOCK                   = MAKE_VALUE(0x44, 29)  /*!< acc periph clock */
#endif

} crm_periph_clock_type;

/**
  * @brief crm periph reset
  */
typedef enum
{
#if defined (AT32F435xx)
  /* ahb periph1 */
  CRM_GPIOA_PERIPH_RESET                 = MAKE_VALUE(0x10, 0),  /*!< gpioa periph reset */
  CRM_GPIOB_PERIPH_RESET                 = MAKE_VALUE(0x10, 1),  /*!< gpiob periph reset */
  CRM_GPIOC_PERIPH_RESET                 = MAKE_VALUE(0x10, 2),  /*!< gpioc periph reset */
  CRM_GPIOD_PERIPH_RESET                 = MAKE_VALUE(0x10, 3),  /*!< gpiod periph reset */
  CRM_GPIOE_PERIPH_RESET                 = MAKE_VALUE(0x10, 4),  /*!< gpioe periph reset */
  CRM_GPIOF_PERIPH_RESET                 = MAKE_VALUE(0x10, 5),  /*!< gpiof periph reset */
  CRM_GPIOG_PERIPH_RESET                 = MAKE_VALUE(0x10, 6),  /*!< gpiog periph reset */
  CRM_GPIOH_PERIPH_RESET                 = MAKE_VALUE(0x10, 7),  /*!< gpioh periph reset */
  CRM_CRC_PERIPH_RESET                   = MAKE_VALUE(0x10, 12), /*!< crc periph reset */
  CRM_EDMA_PERIPH_RESET                  = MAKE_VALUE(0x10, 21), /*!< edma periph reset */
  CRM_DMA1_PERIPH_RESET                  = MAKE_VALUE(0x10, 22), /*!< dma1 periph reset */
  CRM_DMA2_PERIPH_RESET                  = MAKE_VALUE(0x10, 24), /*!< dma2 periph reset */
  CRM_OTGFS2_PERIPH_RESET                = MAKE_VALUE(0x10, 29), /*!< otgfs2 periph reset */
  /* ahb periph2 */
  CRM_DVP_PERIPH_RESET                   = MAKE_VALUE(0x14, 0),  /*!< dvp periph reset */
  CRM_OTGFS1_PERIPH_RESET                = MAKE_VALUE(0x14, 7),  /*!< otgfs1 periph reset */
  CRM_SDIO1_PERIPH_RESET                 = MAKE_VALUE(0x14, 15), /*!< sdio1 periph reset */
  /* ahb periph3 */
  CRM_XMC_PERIPH_RESET                   = MAKE_VALUE(0x18, 0),  /*!< xmc periph reset */
  CRM_QSPI1_PERIPH_RESET                 = MAKE_VALUE(0x18, 1),  /*!< qspi1 periph reset */
  CRM_QSPI2_PERIPH_RESET                 = MAKE_VALUE(0x18, 14), /*!< qspi2 periph reset */
  CRM_SDIO2_PERIPH_RESET                 = MAKE_VALUE(0x18, 15), /*!< sdio2 periph reset */
  /* apb1 periph */
  CRM_TMR2_PERIPH_RESET                  = MAKE_VALUE(0x20, 0),  /*!< tmr2 periph reset */
  CRM_TMR3_PERIPH_RESET                  = MAKE_VALUE(0x20, 1),  /*!< tmr3 periph reset */
  CRM_TMR4_PERIPH_RESET                  = MAKE_VALUE(0x20, 2),  /*!< tmr4 periph reset */
  CRM_TMR5_PERIPH_RESET                  = MAKE_VALUE(0x20, 3),  /*!< tmr5 periph reset */
  CRM_TMR6_PERIPH_RESET                  = MAKE_VALUE(0x20, 4),  /*!< tmr6 periph reset */
  CRM_TMR7_PERIPH_RESET                  = MAKE_VALUE(0x20, 5),  /*!< tmr7 periph reset */
  CRM_TMR12_PERIPH_RESET                 = MAKE_VALUE(0x20, 6),  /*!< tmr12 periph reset */
  CRM_TMR13_PERIPH_RESET                 = MAKE_VALUE(0x20, 7),  /*!< tmr13 periph reset */
  CRM_TMR14_PERIPH_RESET                 = MAKE_VALUE(0x20, 8),  /*!< tmr14 periph reset */
  CRM_WWDT_PERIPH_RESET                  = MAKE_VALUE(0x20, 11), /*!< wwdt periph reset */
  CRM_SPI2_PERIPH_RESET                  = MAKE_VALUE(0x20, 14), /*!< spi2 periph reset */
  CRM_SPI3_PERIPH_RESET                  = MAKE_VALUE(0x20, 15), /*!< spi3 periph reset */
  CRM_USART2_PERIPH_RESET                = MAKE_VALUE(0x20, 17), /*!< usart2 periph reset */
  CRM_USART3_PERIPH_RESET                = MAKE_VALUE(0x20, 18), /*!< usart3 periph reset */
  CRM_UART4_PERIPH_RESET                 = MAKE_VALUE(0x20, 19), /*!< uart4 periph reset */
  CRM_UART5_PERIPH_RESET                 = MAKE_VALUE(0x20, 20), /*!< uart5 periph reset */
  CRM_I2C1_PERIPH_RESET                  = MAKE_VALUE(0x20, 21), /*!< i2c1 periph reset */
  CRM_I2C2_PERIPH_RESET                  = MAKE_VALUE(0x20, 22), /*!< i2c2 periph reset */
  CRM_I2C3_PERIPH_RESET                  = MAKE_VALUE(0x20, 23), /*!< i2c3 periph reset */
  CRM_CAN1_PERIPH_RESET                  = MAKE_VALUE(0x20, 25), /*!< can1 periph reset */
  CRM_CAN2_PERIPH_RESET                  = MAKE_VALUE(0x20, 26), /*!< can2 periph reset */
  CRM_PWC_PERIPH_RESET                   = MAKE_VALUE(0x20, 28), /*!< pwc periph reset */
  CRM_DAC_PERIPH_RESET                   = MAKE_VALUE(0x20, 29), /*!< dac periph reset */
  CRM_UART7_PERIPH_RESET                 = MAKE_VALUE(0x20, 30), /*!< uart7 periph reset */
  CRM_UART8_PERIPH_RESET                 = MAKE_VALUE(0x20, 31), /*!< uart8 periph reset */
  /* apb2 periph */
  CRM_TMR1_PERIPH_RESET                  = MAKE_VALUE(0x24, 0),  /*!< tmr1 periph reset */
  CRM_TMR8_PERIPH_RESET                  = MAKE_VALUE(0x24, 1),  /*!< tmr8 periph reset */
  CRM_USART1_PERIPH_RESET                = MAKE_VALUE(0x24, 4),  /*!< usart1 periph reset */
  CRM_USART6_PERIPH_RESET                = MAKE_VALUE(0x24, 5),  /*!< usart6 periph reset */
  CRM_ADC_PERIPH_RESET                   = MAKE_VALUE(0x24, 8),  /*!< adc periph reset */
  CRM_SPI1_PERIPH_RESET                  = MAKE_VALUE(0x24, 12), /*!< spi1 periph reset */
  CRM_SPI4_PERIPH_RESET                  = MAKE_VALUE(0x24, 13), /*!< spi4 periph reset */
  CRM_SCFG_PERIPH_RESET                  = MAKE_VALUE(0x24, 14), /*!< scfg periph reset */
  CRM_TMR9_PERIPH_RESET                  = MAKE_VALUE(0x24, 16), /*!< tmr9 periph reset */
  CRM_TMR10_PERIPH_RESET                 = MAKE_VALUE(0x24, 17), /*!< tmr10 periph reset */
  CRM_TMR11_PERIPH_RESET                 = MAKE_VALUE(0x24, 18), /*!< tmr11 periph reset */
  CRM_TMR20_PERIPH_RESET                 = MAKE_VALUE(0x24, 20), /*!< tmr20 periph reset */
  CRM_ACC_PERIPH_RESET                   = MAKE_VALUE(0x24, 29)  /*!< acc periph reset */
#endif

#if defined (AT32F437xx)
  /* ahb periph1 */
  CRM_GPIOA_PERIPH_RESET                 = MAKE_VALUE(0x10, 0),  /*!< gpioa periph reset */
  CRM_GPIOB_PERIPH_RESET                 = MAKE_VALUE(0x10, 1),  /*!< gpiob periph reset */
  CRM_GPIOC_PERIPH_RESET                 = MAKE_VALUE(0x10, 2),  /*!< gpioc periph reset */
  CRM_GPIOD_PERIPH_RESET                 = MAKE_VALUE(0x10, 3),  /*!< gpiod periph reset */
  CRM_GPIOE_PERIPH_RESET                 = MAKE_VALUE(0x10, 4),  /*!< gpioe periph reset */
  CRM_GPIOF_PERIPH_RESET                 = MAKE_VALUE(0x10, 5),  /*!< gpiof periph reset */
  CRM_GPIOG_PERIPH_RESET                 = MAKE_VALUE(0x10, 6),  /*!< gpiog periph reset */
  CRM_GPIOH_PERIPH_RESET                 = MAKE_VALUE(0x10, 7),  /*!< gpioh periph reset */
  CRM_CRC_PERIPH_RESET                   = MAKE_VALUE(0x10, 12), /*!< crc periph reset */
  CRM_EDMA_PERIPH_RESET                  = MAKE_VALUE(0x10, 21), /*!< edma periph reset */
  CRM_DMA1_PERIPH_RESET                  = MAKE_VALUE(0x10, 22), /*!< dma1 periph reset */
  CRM_DMA2_PERIPH_RESET                  = MAKE_VALUE(0x10, 24), /*!< dma2 periph reset */
  CRM_EMAC_PERIPH_RESET                  = MAKE_VALUE(0x10, 25), /*!< emac periph reset */
  CRM_OTGFS2_PERIPH_RESET                = MAKE_VALUE(0x10, 29), /*!< otgfs2 periph reset */
  /* ahb periph2 */
  CRM_DVP_PERIPH_RESET                   = MAKE_VALUE(0x14, 0),  /*!< dvp periph reset */
  CRM_OTGFS1_PERIPH_RESET                = MAKE_VALUE(0x14, 7),  /*!< otgfs1 periph reset */
  CRM_SDIO1_PERIPH_RESET                 = MAKE_VALUE(0x14, 15), /*!< sdio1 periph reset */
  /* ahb periph3 */
  CRM_XMC_PERIPH_RESET                   = MAKE_VALUE(0x18, 0),  /*!< xmc periph reset */
  CRM_QSPI1_PERIPH_RESET                 = MAKE_VALUE(0x18, 1),  /*!< qspi1 periph reset */
  CRM_QSPI2_PERIPH_RESET                 = MAKE_VALUE(0x18, 14), /*!< qspi2 periph reset */
  CRM_SDIO2_PERIPH_RESET                 = MAKE_VALUE(0x18, 15), /*!< sdio2 periph reset */
  /* apb1 periph */
  CRM_TMR2_PERIPH_RESET                  = MAKE_VALUE(0x20, 0),  /*!< tmr2 periph reset */
  CRM_TMR3_PERIPH_RESET                  = MAKE_VALUE(0x20, 1),  /*!< tmr3 periph reset */
  CRM_TMR4_PERIPH_RESET                  = MAKE_VALUE(0x20, 2),  /*!< tmr4 periph reset */
  CRM_TMR5_PERIPH_RESET                  = MAKE_VALUE(0x20, 3),  /*!< tmr5 periph reset */
  CRM_TMR6_PERIPH_RESET                  = MAKE_VALUE(0x20, 4),  /*!< tmr6 periph reset */
  CRM_TMR7_PERIPH_RESET                  = MAKE_VALUE(0x20, 5),  /*!< tmr7 periph reset */
  CRM_TMR12_PERIPH_RESET                 = MAKE_VALUE(0x20, 6),  /*!< tmr12 periph reset */
  CRM_TMR13_PERIPH_RESET                 = MAKE_VALUE(0x20, 7),  /*!< tmr13 periph reset */
  CRM_TMR14_PERIPH_RESET                 = MAKE_VALUE(0x20, 8),  /*!< tmr14 periph reset */
  CRM_WWDT_PERIPH_RESET                  = MAKE_VALUE(0x20, 11), /*!< wwdt periph reset */
  CRM_SPI2_PERIPH_RESET                  = MAKE_VALUE(0x20, 14), /*!< spi2 periph reset */
  CRM_SPI3_PERIPH_RESET                  = MAKE_VALUE(0x20, 15), /*!< spi3 periph reset */
  CRM_USART2_PERIPH_RESET                = MAKE_VALUE(0x20, 17), /*!< usart2 periph reset */
  CRM_USART3_PERIPH_RESET                = MAKE_VALUE(0x20, 18), /*!< usart3 periph reset */
  CRM_UART4_PERIPH_RESET                 = MAKE_VALUE(0x20, 19), /*!< uart4 periph reset */
  CRM_UART5_PERIPH_RESET                 = MAKE_VALUE(0x20, 20), /*!< uart5 periph reset */
  CRM_I2C1_PERIPH_RESET                  = MAKE_VALUE(0x20, 21), /*!< i2c1 periph reset */
  CRM_I2C2_PERIPH_RESET                  = MAKE_VALUE(0x20, 22), /*!< i2c2 periph reset */
  CRM_I2C3_PERIPH_RESET                  = MAKE_VALUE(0x20, 23), /*!< i2c3 periph reset */
  CRM_CAN1_PERIPH_RESET                  = MAKE_VALUE(0x20, 25), /*!< can1 periph reset */
  CRM_CAN2_PERIPH_RESET                  = MAKE_VALUE(0x20, 26), /*!< can2 periph reset */
  CRM_PWC_PERIPH_RESET                   = MAKE_VALUE(0x20, 28), /*!< pwc periph reset */
  CRM_DAC_PERIPH_RESET                   = MAKE_VALUE(0x20, 29), /*!< dac periph reset */
  CRM_UART7_PERIPH_RESET                 = MAKE_VALUE(0x20, 30), /*!< uart7 periph reset */
  CRM_UART8_PERIPH_RESET                 = MAKE_VALUE(0x20, 31), /*!< uart8 periph reset */
  /* apb2 periph */
  CRM_TMR1_PERIPH_RESET                  = MAKE_VALUE(0x24, 0),  /*!< tmr1 periph reset */
  CRM_TMR8_PERIPH_RESET                  = MAKE_VALUE(0x24, 1),  /*!< tmr8 periph reset */
  CRM_USART1_PERIPH_RESET                = MAKE_VALUE(0x24, 4),  /*!< usart1 periph reset */
  CRM_USART6_PERIPH_RESET                = MAKE_VALUE(0x24, 5),  /*!< usart6 periph reset */
  CRM_ADC_PERIPH_RESET                   = MAKE_VALUE(0x24, 8),  /*!< adc periph reset */
  CRM_SPI1_PERIPH_RESET                  = MAKE_VALUE(0x24, 12), /*!< spi1 periph reset */
  CRM_SPI4_PERIPH_RESET                  = MAKE_VALUE(0x24, 13), /*!< spi4 periph reset */
  CRM_SCFG_PERIPH_RESET                  = MAKE_VALUE(0x24, 14), /*!< scfg periph reset */
  CRM_TMR9_PERIPH_RESET                  = MAKE_VALUE(0x24, 16), /*!< tmr9 periph reset */
  CRM_TMR10_PERIPH_RESET                 = MAKE_VALUE(0x24, 17), /*!< tmr10 periph reset */
  CRM_TMR11_PERIPH_RESET                 = MAKE_VALUE(0x24, 18), /*!< tmr11 periph reset */
  CRM_TMR20_PERIPH_RESET                 = MAKE_VALUE(0x24, 20), /*!< tmr20 periph reset */
  CRM_ACC_PERIPH_RESET                   = MAKE_VALUE(0x24, 29)  /*!< acc periph reset */
#endif

} crm_periph_reset_type;

/**
  * @brief crm periph clock in low power mode
  */
typedef enum
{
#if defined (AT32F435xx)
  /* ahb periph1 */
  CRM_GPIOA_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 0),  /*!< gpioa sleep mode periph clock */
  CRM_GPIOB_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 1),  /*!< gpiob sleep mode periph clock */
  CRM_GPIOC_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 2),  /*!< gpioc sleep mode periph clock */
  CRM_GPIOD_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 3),  /*!< gpiod sleep mode periph clock */
  CRM_GPIOE_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 4),  /*!< gpioe sleep mode periph clock */
  CRM_GPIOF_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 5),  /*!< gpiof sleep mode periph clock */
  CRM_GPIOG_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 6),  /*!< gpiog sleep mode periph clock */
  CRM_GPIOH_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 7),  /*!< gpioh sleep mode periph clock */
  CRM_CRC_PERIPH_LOWPOWER                = MAKE_VALUE(0x50, 12), /*!< crc sleep mode periph clock */
  CRM_FLASH_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 15), /*!< flash sleep mode periph clock */
  CRM_SRAM1_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 16), /*!< sram1 sleep mode periph clock */
  CRM_SRAM2_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 17), /*!< sram2 sleep mode periph clock */
  CRM_EDMA_PERIPH_LOWPOWER               = MAKE_VALUE(0x50, 21), /*!< edma sleep mode periph clock */
  CRM_DMA1_PERIPH_LOWPOWER               = MAKE_VALUE(0x50, 22), /*!< dma1 sleep mode periph clock */
  CRM_DMA2_PERIPH_LOWPOWER               = MAKE_VALUE(0x50, 24), /*!< dma2 sleep mode periph clock */
  CRM_OTGFS2_PERIPH_LOWPOWER             = MAKE_VALUE(0x50, 29), /*!< otgfs2 sleep mode periph clock */
  /* ahb periph2 */
  CRM_DVP_PERIPH_LOWPOWER                = MAKE_VALUE(0x54, 0),  /*!< dvp sleep mode periph clock */
  CRM_OTGFS1_PERIPH_LOWPOWER             = MAKE_VALUE(0x54, 7),  /*!< otgfs1 sleep mode periph clock */
  CRM_SDIO1_PERIPH_LOWPOWER              = MAKE_VALUE(0x54, 15), /*!< sdio1 sleep mode periph clock */
  /* ahb periph3 */
  CRM_XMC_PERIPH_LOWPOWER                = MAKE_VALUE(0x58, 0),  /*!< xmc sleep mode periph clock */
  CRM_QSPI1_PERIPH_LOWPOWER              = MAKE_VALUE(0x58, 1),  /*!< qspi1 sleep mode periph clock */
  CRM_QSPI2_PERIPH_LOWPOWER              = MAKE_VALUE(0x58, 14), /*!< qspi2 sleep mode periph clock */
  CRM_SDIO2_PERIPH_LOWPOWER              = MAKE_VALUE(0x58, 15), /*!< sdio2 sleep mode periph clock */
  /* apb1 periph */
  CRM_TMR2_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 0),  /*!< tmr2 sleep mode periph clock */
  CRM_TMR3_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 1),  /*!< tmr3 sleep mode periph clock */
  CRM_TMR4_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 2),  /*!< tmr4 sleep mode periph clock */
  CRM_TMR5_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 3),  /*!< tmr5 sleep mode periph clock */
  CRM_TMR6_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 4),  /*!< tmr6 sleep mode periph clock */
  CRM_TMR7_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 5),  /*!< tmr7 sleep mode periph clock */
  CRM_TMR12_PERIPH_LOWPOWER              = MAKE_VALUE(0x60, 6),  /*!< tmr12 sleep mode periph clock */
  CRM_TMR13_PERIPH_LOWPOWER              = MAKE_VALUE(0x60, 7),  /*!< tmr13 sleep mode periph clock */
  CRM_TMR14_PERIPH_LOWPOWER              = MAKE_VALUE(0x60, 8),  /*!< tmr14 sleep mode periph clock */
  CRM_WWDT_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 11), /*!< wwdt sleep mode periph clock */
  CRM_SPI2_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 14), /*!< spi2 sleep mode periph clock */
  CRM_SPI3_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 15), /*!< spi3 sleep mode periph clock */
  CRM_USART2_PERIPH_LOWPOWER             = MAKE_VALUE(0x60, 17), /*!< usart2 sleep mode periph clock */
  CRM_USART3_PERIPH_LOWPOWER             = MAKE_VALUE(0x60, 18), /*!< usart3 sleep mode periph clock */
  CRM_UART4_PERIPH_LOWPOWER              = MAKE_VALUE(0x60, 19), /*!< uart4 sleep mode periph clock */
  CRM_UART5_PERIPH_LOWPOWER              = MAKE_VALUE(0x60, 20), /*!< uart5 sleep mode periph clock */
  CRM_I2C1_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 21), /*!< i2c1 sleep mode periph clock */
  CRM_I2C2_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 22), /*!< i2c2 sleep mode periph clock */
  CRM_I2C3_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 23), /*!< i2c3 sleep mode periph clock */
  CRM_CAN1_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 25), /*!< can1 sleep mode periph clock */
  CRM_CAN2_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 26), /*!< can2 sleep mode periph clock */
  CRM_PWC_PERIPH_LOWPOWER                = MAKE_VALUE(0x60, 28), /*!< pwc sleep mode periph clock */
  CRM_DAC_PERIPH_LOWPOWER                = MAKE_VALUE(0x60, 29), /*!< dac sleep mode periph clock */
  CRM_UART7_PERIPH_LOWPOWER              = MAKE_VALUE(0x60, 30), /*!< uart7 sleep mode periph clock */
  CRM_UART8_PERIPH_LOWPOWER              = MAKE_VALUE(0x60, 31), /*!< uart8 sleep mode periph clock */
  /* apb2 periph */
  CRM_TMR1_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 0),  /*!< tmr1 sleep mode periph clock */
  CRM_TMR8_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 1),  /*!< tmr8 sleep mode periph clock */
  CRM_USART1_PERIPH_LOWPOWER             = MAKE_VALUE(0x64, 4),  /*!< usart1 sleep mode periph clock */
  CRM_USART6_PERIPH_LOWPOWER             = MAKE_VALUE(0x64, 5),  /*!< usart6 sleep mode periph clock */
  CRM_ADC1_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 8),  /*!< adc1 sleep mode periph clock */
  CRM_ADC2_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 9),  /*!< adc2 sleep mode periph clock */
  CRM_ADC3_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 10), /*!< adc3 sleep mode periph clock */
  CRM_SPI1_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 12), /*!< spi1 sleep mode periph clock */
  CRM_SPI4_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 13), /*!< spi4 sleep mode periph clock */
  CRM_SCFG_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 14), /*!< scfg sleep mode periph clock */
  CRM_TMR9_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 16), /*!< tmr9 sleep mode periph clock */
  CRM_TMR10_PERIPH_LOWPOWER              = MAKE_VALUE(0x64, 17), /*!< tmr10 sleep mode periph clock */
  CRM_TMR11_PERIPH_LOWPOWER              = MAKE_VALUE(0x64, 18), /*!< tmr11 sleep mode periph clock */
  CRM_TMR20_PERIPH_LOWPOWER              = MAKE_VALUE(0x64, 20), /*!< tmr20 sleep mode periph clock */
  CRM_ACC_PERIPH_LOWPOWER                = MAKE_VALUE(0x64, 29)  /*!< acc sleep mode periph clock */
#endif

#if defined (AT32F437xx)
  /* ahb periph1 */
  CRM_GPIOA_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 0),  /*!< gpioa sleep mode periph clock */
  CRM_GPIOB_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 1),  /*!< gpiob sleep mode periph clock */
  CRM_GPIOC_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 2),  /*!< gpioc sleep mode periph clock */
  CRM_GPIOD_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 3),  /*!< gpiod sleep mode periph clock */
  CRM_GPIOE_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 4),  /*!< gpioe sleep mode periph clock */
  CRM_GPIOF_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 5),  /*!< gpiof sleep mode periph clock */
  CRM_GPIOG_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 6),  /*!< gpiog sleep mode periph clock */
  CRM_GPIOH_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 7),  /*!< gpioh sleep mode periph clock */
  CRM_CRC_PERIPH_LOWPOWER                = MAKE_VALUE(0x50, 12), /*!< crc sleep mode periph clock */
  CRM_FLASH_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 15), /*!< flash sleep mode periph clock */
  CRM_SRAM1_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 16), /*!< sram1 sleep mode periph clock */
  CRM_SRAM2_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 17), /*!< sram2 sleep mode periph clock */
  CRM_EDMA_PERIPH_LOWPOWER               = MAKE_VALUE(0x50, 21), /*!< edma sleep mode periph clock */
  CRM_DMA1_PERIPH_LOWPOWER               = MAKE_VALUE(0x50, 22), /*!< dma1 sleep mode periph clock */
  CRM_DMA2_PERIPH_LOWPOWER               = MAKE_VALUE(0x50, 24), /*!< dma2 sleep mode periph clock */
  CRM_EMAC_PERIPH_LOWPOWER               = MAKE_VALUE(0x50, 25), /*!< emac sleep mode periph clock */
  CRM_EMACTX_PERIPH_LOWPOWER             = MAKE_VALUE(0x50, 26), /*!< emac tx sleep mode periph clock */
  CRM_EMACRX_PERIPH_LOWPOWER             = MAKE_VALUE(0x50, 27), /*!< emac rx sleep mode periph clock */
  CRM_EMACPTP_PERIPH_LOWPOWER            = MAKE_VALUE(0x50, 28), /*!< emac ptp sleep mode periph clock */
  CRM_OTGFS2_PERIPH_LOWPOWER             = MAKE_VALUE(0x50, 29), /*!< otgfs2 sleep mode periph clock */
  /* ahb periph2 */
  CRM_DVP_PERIPH_LOWPOWER                = MAKE_VALUE(0x54, 0),  /*!< dvp sleep mode periph clock */
  CRM_OTGFS1_PERIPH_LOWPOWER             = MAKE_VALUE(0x54, 7),  /*!< otgfs1 sleep mode periph clock */
  CRM_SDIO1_PERIPH_LOWPOWER              = MAKE_VALUE(0x54, 15), /*!< sdio1 sleep mode periph clock */
  /* ahb periph3 */
  CRM_XMC_PERIPH_LOWPOWER                = MAKE_VALUE(0x58, 0),  /*!< xmc sleep mode periph clock */
  CRM_QSPI1_PERIPH_LOWPOWER              = MAKE_VALUE(0x58, 1),  /*!< qspi1 sleep mode periph clock */
  CRM_QSPI2_PERIPH_LOWPOWER              = MAKE_VALUE(0x58, 14), /*!< qspi2 sleep mode periph clock */
  CRM_SDIO2_PERIPH_LOWPOWER              = MAKE_VALUE(0x58, 15), /*!< sdio2 sleep mode periph clock */
  /* apb1 periph */
  CRM_TMR2_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 0),  /*!< tmr2 sleep mode periph clock */
  CRM_TMR3_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 1),  /*!< tmr3 sleep mode periph clock */
  CRM_TMR4_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 2),  /*!< tmr4 sleep mode periph clock */
  CRM_TMR5_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 3),  /*!< tmr5 sleep mode periph clock */
  CRM_TMR6_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 4),  /*!< tmr6 sleep mode periph clock */
  CRM_TMR7_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 5),  /*!< tmr7 sleep mode periph clock */
  CRM_TMR12_PERIPH_LOWPOWER              = MAKE_VALUE(0x60, 6),  /*!< tmr12 sleep mode periph clock */
  CRM_TMR13_PERIPH_LOWPOWER              = MAKE_VALUE(0x60, 7),  /*!< tmr13 sleep mode periph clock */
  CRM_TMR14_PERIPH_LOWPOWER              = MAKE_VALUE(0x60, 8),  /*!< tmr14 sleep mode periph clock */
  CRM_WWDT_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 11), /*!< wwdt sleep mode periph clock */
  CRM_SPI2_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 14), /*!< spi2 sleep mode periph clock */
  CRM_SPI3_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 15), /*!< spi3 sleep mode periph clock */
  CRM_USART2_PERIPH_LOWPOWER             = MAKE_VALUE(0x60, 17), /*!< usart2 sleep mode periph clock */
  CRM_USART3_PERIPH_LOWPOWER             = MAKE_VALUE(0x60, 18), /*!< usart3 sleep mode periph clock */
  CRM_UART4_PERIPH_LOWPOWER              = MAKE_VALUE(0x60, 19), /*!< uart4 sleep mode periph clock */
  CRM_UART5_PERIPH_LOWPOWER              = MAKE_VALUE(0x60, 20), /*!< uart5 sleep mode periph clock */
  CRM_I2C1_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 21), /*!< i2c1 sleep mode periph clock */
  CRM_I2C2_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 22), /*!< i2c2 sleep mode periph clock */
  CRM_I2C3_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 23), /*!< i2c3 sleep mode periph clock */
  CRM_CAN1_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 25), /*!< can1 sleep mode periph clock */
  CRM_CAN2_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 26), /*!< can2 sleep mode periph clock */
  CRM_PWC_PERIPH_LOWPOWER                = MAKE_VALUE(0x60, 28), /*!< pwc sleep mode periph clock */
  CRM_DAC_PERIPH_LOWPOWER                = MAKE_VALUE(0x60, 29), /*!< dac sleep mode periph clock */
  CRM_UART7_PERIPH_LOWPOWER              = MAKE_VALUE(0x60, 30), /*!< uart7 sleep mode periph clock */
  CRM_UART8_PERIPH_LOWPOWER              = MAKE_VALUE(0x60, 31), /*!< uart8 sleep mode periph clock */
  /* apb2 periph */
  CRM_TMR1_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 0),  /*!< tmr1 sleep mode periph clock */
  CRM_TMR8_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 1),  /*!< tmr8 sleep mode periph clock */
  CRM_USART1_PERIPH_LOWPOWER             = MAKE_VALUE(0x64, 4),  /*!< usart1 sleep mode periph clock */
  CRM_USART6_PERIPH_LOWPOWER             = MAKE_VALUE(0x64, 5),  /*!< usart6 sleep mode periph clock */
  CRM_ADC1_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 8),  /*!< adc1 sleep mode periph clock */
  CRM_ADC2_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 9),  /*!< adc2 sleep mode periph clock */
  CRM_ADC3_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 10), /*!< adc3 sleep mode periph clock */
  CRM_SPI1_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 12), /*!< spi1 sleep mode periph clock */
  CRM_SPI4_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 13), /*!< spi4 sleep mode periph clock */
  CRM_SCFG_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 14), /*!< scfg sleep mode periph clock */
  CRM_TMR9_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 16), /*!< tmr9 sleep mode periph clock */
  CRM_TMR10_PERIPH_LOWPOWER              = MAKE_VALUE(0x64, 17), /*!< tmr10 sleep mode periph clock */
  CRM_TMR11_PERIPH_LOWPOWER              = MAKE_VALUE(0x64, 18), /*!< tmr11 sleep mode periph clock */
  CRM_TMR20_PERIPH_LOWPOWER              = MAKE_VALUE(0x64, 20), /*!< tmr20 sleep mode periph clock */
  CRM_ACC_PERIPH_LOWPOWER                = MAKE_VALUE(0x64, 29)  /*!< acc sleep mode periph clock */
#endif

} crm_periph_clock_lowpower_type;

/**
  * @brief crm pll clock source
  */
typedef enum
{
  CRM_PLL_SOURCE_HICK                    = 0x00, /*!< high speed internal clock as pll reference clock source */
  CRM_PLL_SOURCE_HEXT                    = 0x01  /*!< high speed external crystal as pll reference clock source */
} crm_pll_clock_source_type;

/**
  * @brief crm pll fr
  */
typedef enum
{
  CRM_PLL_FR_1                           = 0x00, /*!< pll post-division div1 */
  CRM_PLL_FR_2                           = 0x01, /*!< pll post-division div2 */
  CRM_PLL_FR_4                           = 0x02, /*!< pll post-division div4 */
  CRM_PLL_FR_8                           = 0x03, /*!< pll post-division div8 */
  CRM_PLL_FR_16                          = 0x04, /*!< pll post-division div16 */
  CRM_PLL_FR_32                          = 0x05  /*!< pll post-division div32 */
} crm_pll_fr_type;

/**
  * @brief crm clock source
  */
typedef enum
{
  CRM_CLOCK_SOURCE_HICK                  = 0x00, /*!< high speed internal clock */
  CRM_CLOCK_SOURCE_HEXT                  = 0x01, /*!< high speed external crystal */
  CRM_CLOCK_SOURCE_PLL                   = 0x02, /*!< phase locking loop */
  CRM_CLOCK_SOURCE_LEXT                  = 0x03, /*!< low speed external crystal */
  CRM_CLOCK_SOURCE_LICK                  = 0x04  /*!< low speed internal clock */
} crm_clock_source_type;

/**
  * @brief crm ahb division
  */
typedef enum
{
  CRM_AHB_DIV_1                          = 0x00, /*!< sclk div1 to ahbclk */
  CRM_AHB_DIV_2                          = 0x08, /*!< sclk div2 to ahbclk */
  CRM_AHB_DIV_4                          = 0x09, /*!< sclk div4 to ahbclk */
  CRM_AHB_DIV_8                          = 0x0A, /*!< sclk div8 to ahbclk */
  CRM_AHB_DIV_16                         = 0x0B, /*!< sclk div16 to ahbclk */
  CRM_AHB_DIV_64                         = 0x0C, /*!< sclk div64 to ahbclk */
  CRM_AHB_DIV_128                        = 0x0D, /*!< sclk div128 to ahbclk */
  CRM_AHB_DIV_256                        = 0x0E, /*!< sclk div256 to ahbclk */
  CRM_AHB_DIV_512                        = 0x0F  /*!< sclk div512 to ahbclk */
} crm_ahb_div_type;

/**
  * @brief crm apb1 division
  */
typedef enum
{
  CRM_APB1_DIV_1                         = 0x00, /*!< ahbclk div1 to apb1clk */
  CRM_APB1_DIV_2                         = 0x04, /*!< ahbclk div2 to apb1clk */
  CRM_APB1_DIV_4                         = 0x05, /*!< ahbclk div4 to apb1clk */
  CRM_APB1_DIV_8                         = 0x06, /*!< ahbclk div8 to apb1clk */
  CRM_APB1_DIV_16                        = 0x07  /*!< ahbclk div16 to apb1clk */
} crm_apb1_div_type;

/**
  * @brief crm apb2 division
  */
typedef enum
{
  CRM_APB2_DIV_1                         = 0x00, /*!< ahbclk div1 to apb2clk */
  CRM_APB2_DIV_2                         = 0x04, /*!< ahbclk div2 to apb2clk */
  CRM_APB2_DIV_4                         = 0x05, /*!< ahbclk div4 to apb2clk */
  CRM_APB2_DIV_8                         = 0x06, /*!< ahbclk div8 to apb2clk */
  CRM_APB2_DIV_16                        = 0x07  /*!< ahbclk div16 to apb2clk */
} crm_apb2_div_type;

/**
  * @brief crm usb division
  */
typedef enum
{
  CRM_USB_DIV_1_5                        = 0x00, /*!< pllclk div1.5 to usbclk */
  CRM_USB_DIV_1                          = 0x01, /*!< pllclk div1 to usbclk */
  CRM_USB_DIV_2_5                        = 0x02, /*!< pllclk div2.5 to usbclk */
  CRM_USB_DIV_2                          = 0x03, /*!< pllclk div2 to usbclk */
  CRM_USB_DIV_3_5                        = 0x04, /*!< pllclk div3.5 to usbclk */
  CRM_USB_DIV_3                          = 0x05, /*!< pllclk div3 to usbclk */
  CRM_USB_DIV_4_5                        = 0x06, /*!< pllclk div4.5 to usbclk */
  CRM_USB_DIV_4                          = 0x07, /*!< pllclk div4 to usbclk */
  CRM_USB_DIV_5_5                        = 0x08, /*!< pllclk div5.5 to usbclk */
  CRM_USB_DIV_5                          = 0x09, /*!< pllclk div5 to usbclk */
  CRM_USB_DIV_6_5                        = 0x0A, /*!< pllclk div6.5 to usbclk */
  CRM_USB_DIV_6                          = 0x0B, /*!< pllclk div6 to usbclk */
  CRM_USB_DIV_7                          = 0x0C  /*!< pllclk div7 to usbclk */
} crm_usb_div_type;

/**
  * @brief crm ertc clock
  */
typedef enum
{
  CRM_ERTC_CLOCK_NOCLK                   = 0x000, /*!< no clock as ertc clock source */
  CRM_ERTC_CLOCK_LEXT                    = 0x001, /*!< low speed external crystal as ertc clock source */
  CRM_ERTC_CLOCK_LICK                    = 0x002, /*!< low speed internal clock as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_2              = 0x023, /*!< high speed external crystal div2 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_3              = 0x033, /*!< high speed external crystal div3 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_4              = 0x043, /*!< high speed external crystal div4 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_5              = 0x053, /*!< high speed external crystal div5 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_6              = 0x063, /*!< high speed external crystal div6 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_7              = 0x073, /*!< high speed external crystal div7 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_8              = 0x083, /*!< high speed external crystal div8 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_9              = 0x093, /*!< high speed external crystal div9 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_10             = 0x0A3, /*!< high speed external crystal div10 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_11             = 0x0B3, /*!< high speed external crystal div11 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_12             = 0x0C3, /*!< high speed external crystal div12 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_13             = 0x0D3, /*!< high speed external crystal div13 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_14             = 0x0E3, /*!< high speed external crystal div14 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_15             = 0x0F3, /*!< high speed external crystal div15 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_16             = 0x103, /*!< high speed external crystal div16 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_17             = 0x113, /*!< high speed external crystal div17 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_18             = 0x123, /*!< high speed external crystal div18 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_19             = 0x133, /*!< high speed external crystal div19 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_20             = 0x143, /*!< high speed external crystal div20 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_21             = 0x153, /*!< high speed external crystal div21 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_22             = 0x163, /*!< high speed external crystal div22 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_23             = 0x173, /*!< high speed external crystal div23 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_24             = 0x183, /*!< high speed external crystal div24 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_25             = 0x193, /*!< high speed external crystal div25 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_26             = 0x1A3, /*!< high speed external crystal div26 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_27             = 0x1B3, /*!< high speed external crystal div27 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_28             = 0x1C3, /*!< high speed external crystal div28 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_29             = 0x1D3, /*!< high speed external crystal div29 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_30             = 0x1E3, /*!< high speed external crystal div30 as ertc clock source */
  CRM_ERTC_CLOCK_HEXT_DIV_31             = 0x1F3  /*!< high speed external crystal div31 as ertc clock source */
} crm_ertc_clock_type;

/**
  * @brief crm hick 48mhz division
  */
typedef enum
{
  CRM_HICK48_DIV6                        = 0x00, /*!< fixed 8 mhz when hick is selected as sclk */
  CRM_HICK48_NODIV                       = 0x01  /*!< 8 mhz or 48 mhz depend on hickdiv when hick is selected as sclk */
} crm_hick_div_6_type;

/**
  * @brief crm sclk select
  */
typedef enum
{
  CRM_SCLK_HICK                          = 0x00, /*!< select high speed internal clock as sclk */
  CRM_SCLK_HEXT                          = 0x01, /*!< select high speed external crystal as sclk */
  CRM_SCLK_PLL                           = 0x02  /*!< select phase locking loop clock as sclk */
} crm_sclk_type;

/**
  * @brief crm clkout index
  */
typedef enum
{
  CRM_CLKOUT_INDEX_1                     = 0x00, /*!< clkout1 */
  CRM_CLKOUT_INDEX_2                     = 0x01  /*!< clkout2 */
} crm_clkout_index_type;

/**
  * @brief crm clkout1 select
  */
typedef enum
{
  CRM_CLKOUT1_HICK                       = 0x00, /*!< output high speed internal clock to clkout1 pin */
  CRM_CLKOUT1_LEXT                       = 0x01, /*!< output low speed external crystal to clkout1 pin */
  CRM_CLKOUT1_HEXT                       = 0x02, /*!< output high speed external crystal to clkout1 pin */
  CRM_CLKOUT1_PLL                        = 0x03  /*!< output phase locking loop clock to clkout1 pin */
} crm_clkout1_select_type;

/**
  * @brief crm clkout2 select
  */
typedef enum
{
  CRM_CLKOUT2_SCLK                       = 0x00,  /*!< output system clock to clkout2 pin */
  CRM_CLKOUT2_HEXT                       = 0x02,  /*!< output high speed external crystal to clkout2 pin */
  CRM_CLKOUT2_PLL                        = 0x03,  /*!< output phase locking loop clock to clkout2 pin */
  CRM_CLKOUT2_USB                        = 0x10, /*!< output usbclk to clkout2 pin */
  CRM_CLKOUT2_ADC                        = 0x11, /*!< output adcclk to clkout2 pin */
  CRM_CLKOUT2_HICK                       = 0x12, /*!< output high speed internal clock to clkout2 pin */
  CRM_CLKOUT2_LICK                       = 0x13, /*!< output low speed internal clock to clkout2 pin */
  CRM_CLKOUT2_LEXT                       = 0x14  /*!< output low speed external crystal to clkout2 pin */
} crm_clkout2_select_type;

/**
  * @brief crm clkout division1
  */
typedef enum
{
  CRM_CLKOUT_DIV1_1                      = 0x00, /*!< clkout division1 div1 */
  CRM_CLKOUT_DIV1_2                      = 0x04, /*!< clkout division1 div2 */
  CRM_CLKOUT_DIV1_3                      = 0x05, /*!< clkout division1 div3 */
  CRM_CLKOUT_DIV1_4                      = 0x06, /*!< clkout division1 div4 */
  CRM_CLKOUT_DIV1_5                      = 0x07  /*!< clkout division1 div5 */
} crm_clkout_div1_type;

/**
  * @brief crm clkout division2
  */
typedef enum
{
  CRM_CLKOUT_DIV2_1                      = 0x00, /*!< clkout division2 div1 */
  CRM_CLKOUT_DIV2_2                      = 0x08, /*!< clkout division2 div2 */
  CRM_CLKOUT_DIV2_4                      = 0x09, /*!< clkout division2 div4 */
  CRM_CLKOUT_DIV2_8                      = 0x0A, /*!< clkout division2 div8 */
  CRM_CLKOUT_DIV2_16                     = 0x0B, /*!< clkout division2 div16 */
  CRM_CLKOUT_DIV2_64                     = 0x0C, /*!< clkout division2 div64 */
  CRM_CLKOUT_DIV2_128                    = 0x0D, /*!< clkout division2 div128 */
  CRM_CLKOUT_DIV2_256                    = 0x0E, /*!< clkout division2 div256 */
  CRM_CLKOUT_DIV2_512                    = 0x0F  /*!< clkout division2 div512 */
} crm_clkout_div2_type;

/**
  * @brief crm auto step mode
  */
typedef enum
{
  CRM_AUTO_STEP_MODE_DISABLE             = 0x00, /*!< disable auto step mode */
  CRM_AUTO_STEP_MODE_ENABLE              = 0x03  /*!< enable auto step mode */
} crm_auto_step_mode_type;

/**
  * @brief crm usb 48 mhz clock source select
  */
typedef enum
{
  CRM_USB_CLOCK_SOURCE_PLL               = 0x00, /*!< select phase locking loop clock as usb clock source */
  CRM_USB_CLOCK_SOURCE_HICK              = 0x01  /*!< select high speed internal clock as usb clock source */
} crm_usb_clock_source_type;

/**
  * @brief crm hick as system clock frequency select
  */
typedef enum
{
  CRM_HICK_SCLK_8MHZ                     = 0x00, /*!< fixed 8 mhz when hick is selected as sclk */
  CRM_HICK_SCLK_48MHZ                    = 0x01  /*!< 8 mhz or 48 mhz depend on hickdiv when hick is selected as sclk */
} crm_hick_sclk_frequency_type;

/**
  * @brief crm emac output pulse width
  */
typedef enum
{
  CRM_EMAC_PULSE_125MS                   = 0x00, /*!< emac output pulse width 125ms */
  CRM_EMAC_PULSE_1SCLK                   = 0x01  /*!< emac output pulse width 1 system clock */
} crm_emac_output_pulse_type;

/**
  * @brief crm clocks freqency structure
  */
typedef struct
{
  uint32_t sclk_freq; /*!< system clock frequency */
  uint32_t ahb_freq;  /*!< ahb bus clock frequency */
  uint32_t apb2_freq; /*!< apb2 bus clock frequency */
  uint32_t apb1_freq; /*!< apb1 bus clock frequency */
} crm_clocks_freq_type;

/**
  * @brief type define crm register all
  */
typedef struct
{
  /**
    * @brief crm ctrl register, offset:0x00
    */
  union
  {
    __IO uint32_t ctrl;
    struct
    {
      __IO uint32_t hicken               : 1; /* [0] */
      __IO uint32_t hickstbl             : 1; /* [1] */
      __IO uint32_t hicktrim             : 6; /* [7:2] */
      __IO uint32_t hickcal              : 8; /* [15:8] */
      __IO uint32_t hexten               : 1; /* [16] */
      __IO uint32_t hextstbl             : 1; /* [17] */
      __IO uint32_t hextbyps             : 1; /* [18] */
      __IO uint32_t cfden                : 1; /* [19] */
      __IO uint32_t reserved1            : 4; /* [23:20] */
      __IO uint32_t pllen                : 1; /* [24] */
      __IO uint32_t pllstbl              : 1; /* [25] */
      __IO uint32_t reserved2            : 6; /* [31:26] */
    } ctrl_bit;
  };

  /**
    * @brief crm pllcfg register, offset:0x04
    */
  union
  {
    __IO uint32_t pllcfg;
    struct
    {
      __IO uint32_t pllms                : 4; /* [3:0] */
      __IO uint32_t reserved1            : 2; /* [5:4] */
      __IO uint32_t pllns                : 9; /* [14:6] */
      __IO uint32_t reserved2            : 1; /* [15] */
      __IO uint32_t pllfr                : 3; /* [18:16] */
      __IO uint32_t reserved3            : 3; /* [21:19] */
      __IO uint32_t pllrcs               : 1; /* [22] */
      __IO uint32_t reserved4            : 9; /* [31:23] */
    } pllcfg_bit;
  };

  /**
    * @brief crm cfg register, offset:0x08
    */
  union
  {
    __IO uint32_t cfg;
    struct
    {
      __IO uint32_t sclksel              : 2; /* [1:0] */
      __IO uint32_t sclksts              : 2; /* [3:2] */
      __IO uint32_t ahbdiv               : 4; /* [7:4] */
      __IO uint32_t reserved1            : 2; /* [9:8] */
      __IO uint32_t apb1div              : 3; /* [12:10] */
      __IO uint32_t apb2div              : 3; /* [15:13] */
      __IO uint32_t ertcdiv              : 5; /* [20:16] */
      __IO uint32_t clkout1_sel          : 2; /* [22:21] */
      __IO uint32_t reserved2            : 1; /* [23] */
      __IO uint32_t clkout1div1          : 3; /* [26:24] */
      __IO uint32_t clkout2div1          : 3; /* [29:27] */
      __IO uint32_t clkout2_sel1         : 2; /* [31:30] */
    } cfg_bit;
  };

  /**
    * @brief crm clkint register, offset:0x0C
    */
  union
  {
    __IO uint32_t clkint;
    struct
    {
      __IO uint32_t lickstblf            : 1; /* [0] */
      __IO uint32_t lextstblf            : 1; /* [1] */
      __IO uint32_t hickstblf            : 1; /* [2] */
      __IO uint32_t hextstblf            : 1; /* [3] */
      __IO uint32_t pllstblf             : 1; /* [4] */
      __IO uint32_t reserved1            : 2; /* [6:5] */
      __IO uint32_t cfdf                 : 1; /* [7] */
      __IO uint32_t lickstblien          : 1; /* [8] */
      __IO uint32_t lextstblien          : 1; /* [9] */
      __IO uint32_t hickstblien          : 1; /* [10] */
      __IO uint32_t hextstblien          : 1; /* [11] */
      __IO uint32_t pllstblien           : 1; /* [12] */
      __IO uint32_t reserved2            : 3; /* [15:13] */
      __IO uint32_t lickstblfc           : 1; /* [16] */
      __IO uint32_t lextstblfc           : 1; /* [17] */
      __IO uint32_t hickstblfc           : 1; /* [18] */
      __IO uint32_t hextstblfc           : 1; /* [19] */
      __IO uint32_t pllstblfc            : 1; /* [20] */
      __IO uint32_t reserved3            : 2; /* [22:21] */
      __IO uint32_t cfdfc                : 1; /* [23] */
      __IO uint32_t reserved4            : 8; /* [31:24] */
    } clkint_bit;
  };

  /**
    * @brief crm ahbrst1 register, offset:0x10
    */
  union
  {
    __IO uint32_t ahbrst1;
#if defined (AT32F435xx)
    struct
    {
      __IO uint32_t gpioarst             : 1; /* [0] */
      __IO uint32_t gpiobrst             : 1; /* [1] */
      __IO uint32_t gpiocrst             : 1; /* [2] */
      __IO uint32_t gpiodrst             : 1; /* [3] */
      __IO uint32_t gpioerst             : 1; /* [4] */
      __IO uint32_t gpiofrst             : 1; /* [5] */
      __IO uint32_t gpiogrst             : 1; /* [6] */
      __IO uint32_t gpiohrst             : 1; /* [7] */
      __IO uint32_t reserved1            : 4; /* [11:8] */
      __IO uint32_t crcrst               : 1; /* [12] */
      __IO uint32_t reserved2            : 8; /* [20:13] */
      __IO uint32_t edmarst              : 1; /* [21] */
      __IO uint32_t dma1rst              : 1; /* [22] */
      __IO uint32_t reserved3            : 1; /* [23] */
      __IO uint32_t dma2rst              : 1; /* [24] */
      __IO uint32_t reserved4            : 4; /* [28:25] */
      __IO uint32_t otgfs2rst            : 1; /* [29] */
      __IO uint32_t reserved5            : 2; /* [31:30] */
    } ahbrst1_bit;
#endif

#if defined (AT32F437xx)
    struct
    {
      __IO uint32_t gpioarst             : 1; /* [0] */
      __IO uint32_t gpiobrst             : 1; /* [1] */
      __IO uint32_t gpiocrst             : 1; /* [2] */
      __IO uint32_t gpiodrst             : 1; /* [3] */
      __IO uint32_t gpioerst             : 1; /* [4] */
      __IO uint32_t gpiofrst             : 1; /* [5] */
      __IO uint32_t gpiogrst             : 1; /* [6] */
      __IO uint32_t gpiohrst             : 1; /* [7] */
      __IO uint32_t reserved1            : 4; /* [11:8] */
      __IO uint32_t crcrst               : 1; /* [12] */
      __IO uint32_t reserved2            : 8; /* [20:13] */
      __IO uint32_t edmarst              : 1; /* [21] */
      __IO uint32_t dma1rst              : 1; /* [22] */
      __IO uint32_t reserved3            : 1; /* [23] */
      __IO uint32_t dma2rst              : 1; /* [24] */
      __IO uint32_t emacrst              : 1; /* [25] */
      __IO uint32_t reserved4            : 3; /* [28:26] */
      __IO uint32_t otgfs2rst            : 1; /* [29] */
      __IO uint32_t reserved5            : 2; /* [31:30] */
    } ahbrst1_bit;
#endif
  };

  /**
    * @brief crm ahbrst2 register, offset:0x14
    */
  union
  {
    __IO uint32_t ahbrst2;
    struct
    {
      __IO uint32_t dvprst               : 1; /* [0] */
      __IO uint32_t reserved1            : 6; /* [6:1] */
      __IO uint32_t otgfs1rst            : 1; /* [7] */
      __IO uint32_t reserved2            : 7; /* [14:8] */
      __IO uint32_t sdio1rst             : 1; /* [15] */
      __IO uint32_t reserved3            : 16;/* [31:16] */
    } ahbrst2_bit;
  };

  /**
    * @brief crm ahbrst3 register, offset:0x18
    */
  union
  {
    __IO uint32_t ahbrst3;
    struct
    {
      __IO uint32_t xmcrst               : 1; /* [0] */
      __IO uint32_t qspi1rst             : 1; /* [1] */
      __IO uint32_t reserved1            : 12;/* [13:2] */
      __IO uint32_t qspi2rst             : 1; /* [14] */
      __IO uint32_t sdio2rst             : 1; /* [15] */
      __IO uint32_t reserved3            : 16;/* [31:16] */
    } ahbrst3_bit;
  };

  /**
    * @brief crm reserved1 register, offset:0x1C
    */
  __IO uint32_t reserved1;

  /**
    * @brief crm apb1rst register, offset:0x20
    */
  union
  {
    __IO uint32_t apb1rst;
    struct
    {
      __IO uint32_t tmr2rst              : 1; /* [0] */
      __IO uint32_t tmr3rst              : 1; /* [1] */
      __IO uint32_t tmr4rst              : 1; /* [2] */
      __IO uint32_t tmr5rst              : 1; /* [3] */
      __IO uint32_t tmr6rst              : 1; /* [4] */
      __IO uint32_t tmr7rst              : 1; /* [5] */
      __IO uint32_t tmr12rst             : 1; /* [6] */
      __IO uint32_t tmr13rst             : 1; /* [7] */
      __IO uint32_t adc14rst             : 1; /* [8] */
      __IO uint32_t reserved1            : 2; /* [10:9] */
      __IO uint32_t wwdtrst              : 1; /* [11] */
      __IO uint32_t reserved2            : 2; /* [13:12] */
      __IO uint32_t spi2rst              : 1; /* [14] */
      __IO uint32_t spi3rst              : 1; /* [15] */
      __IO uint32_t reserved3            : 1; /* [16] */
      __IO uint32_t usart2rst            : 1; /* [17] */
      __IO uint32_t usart3rst            : 1; /* [18] */
      __IO uint32_t uart4rst             : 1; /* [19] */
      __IO uint32_t uart5rst             : 1; /* [20] */
      __IO uint32_t i2c1rst              : 1; /* [21] */
      __IO uint32_t i2c2rst              : 1; /* [22] */
      __IO uint32_t i2c3rst              : 1; /* [23] */
      __IO uint32_t reserved4            : 1; /* [24] */
      __IO uint32_t can1rst              : 1; /* [25] */
      __IO uint32_t can2rst              : 1; /* [26] */
      __IO uint32_t reserved5            : 1; /* [27] */
      __IO uint32_t pwcrst               : 1; /* [28] */
      __IO uint32_t dacrst               : 1; /* [29] */
      __IO uint32_t uart7rst             : 1; /* [30] */
      __IO uint32_t uart8rst             : 1; /* [31] */
    } apb1rst_bit;
  };

  /**
    * @brief crm apb2rst register, offset:0x24
    */
  union
  {
    __IO uint32_t apb2rst;
    struct
    {
      __IO uint32_t tmr1rst              : 1; /* [0] */
      __IO uint32_t tmr8rst              : 1; /* [1] */
      __IO uint32_t reserved1            : 2; /* [3:2] */
      __IO uint32_t usart1rst            : 1; /* [4] */
      __IO uint32_t usart6rst            : 1; /* [5] */
      __IO uint32_t reserved2            : 2; /* [7:6] */
      __IO uint32_t adcrst               : 1; /* [8] */
      __IO uint32_t reserved3            : 3; /* [11:9] */
      __IO uint32_t spi1rst              : 1; /* [12] */
      __IO uint32_t spi4rst              : 1; /* [13] */
      __IO uint32_t scfgrst              : 1; /* [14] */
      __IO uint32_t reserved4            : 1; /* [15] */
      __IO uint32_t tmr9rst              : 1; /* [16] */
      __IO uint32_t tmr10rst             : 1; /* [17] */
      __IO uint32_t tmr11rst             : 1; /* [18] */
      __IO uint32_t reserved5            : 1; /* [19] */
      __IO uint32_t tmr20rst             : 1; /* [20] */
      __IO uint32_t reserved6            : 8; /* [28:21] */
      __IO uint32_t accrst               : 1; /* [29] */
      __IO uint32_t reserved7            : 2; /* [31:30] */
    } apb2rst_bit;
  };

  /**
    * @brief crm reserved2 register, offset:0x28~0x2C
    */
  __IO uint32_t reserved2[2];

  /**
    * @brief crm ahben1 register, offset:0x30
    */
  union
  {
    __IO uint32_t ahben1;
#if defined (AT32F435xx)
    struct
    {
      __IO uint32_t gpioaen              : 1; /* [0] */
      __IO uint32_t gpioben              : 1; /* [1] */
      __IO uint32_t gpiocen              : 1; /* [2] */
      __IO uint32_t gpioden              : 1; /* [3] */
      __IO uint32_t gpioeen              : 1; /* [4] */
      __IO uint32_t gpiofen              : 1; /* [5] */
      __IO uint32_t gpiogen              : 1; /* [6] */
      __IO uint32_t gpiohen              : 1; /* [7] */
      __IO uint32_t reserved1            : 4; /* [11:8] */
      __IO uint32_t crcen                : 1; /* [12] */
      __IO uint32_t reserved2            : 8; /* [20:13] */
      __IO uint32_t edmaen               : 1; /* [21] */
      __IO uint32_t dma1en               : 1; /* [22] */
      __IO uint32_t reserved3            : 1; /* [23] */
      __IO uint32_t dma2en               : 1; /* [24] */
      __IO uint32_t reserved4            : 4; /* [28:25] */
      __IO uint32_t otgfs2en             : 1; /* [29] */
      __IO uint32_t reserved5            : 2; /* [31:30] */
    } ahben1_bit;
#endif

#if defined (AT32F437xx)
    struct
    {
      __IO uint32_t gpioaen              : 1; /* [0] */
      __IO uint32_t gpioben              : 1; /* [1] */
      __IO uint32_t gpiocen              : 1; /* [2] */
      __IO uint32_t gpioden              : 1; /* [3] */
      __IO uint32_t gpioeen              : 1; /* [4] */
      __IO uint32_t gpiofen              : 1; /* [5] */
      __IO uint32_t gpiogen              : 1; /* [6] */
      __IO uint32_t gpiohen              : 1; /* [7] */
      __IO uint32_t reserved1            : 4; /* [11:8] */
      __IO uint32_t crcen                : 1; /* [12] */
      __IO uint32_t reserved2            : 8; /* [20:13] */
      __IO uint32_t edmaen               : 1; /* [21] */
      __IO uint32_t dma1en               : 1; /* [22] */
      __IO uint32_t reserved3            : 1; /* [23] */
      __IO uint32_t dma2en               : 1; /* [24] */
      __IO uint32_t emacen               : 1; /* [25] */
      __IO uint32_t emactxen             : 1; /* [26] */
      __IO uint32_t emacrxen             : 1; /* [27] */
      __IO uint32_t emacptpen            : 1; /* [28] */
      __IO uint32_t otgfs2en             : 1; /* [29] */
      __IO uint32_t reserved4            : 2; /* [31:30] */
    } ahben1_bit;
#endif
  };

  /**
    * @brief crm ahben2 register, offset:0x34
    */
  union
  {
    __IO uint32_t ahben2;
    struct
    {
      __IO uint32_t dvpen                : 1; /* [0] */
      __IO uint32_t reserved1            : 6; /* [6:1] */
      __IO uint32_t otgfs1en             : 1; /* [7] */
      __IO uint32_t reserved2            : 7; /* [14:8] */
      __IO uint32_t sdio1en              : 1; /* [15] */
      __IO uint32_t reserved3            : 16;/* [31:16] */
    } ahben2_bit;
  };

  /**
    * @brief crm ahben3 register, offset:0x38
    */
  union
  {
    __IO uint32_t ahben3;
    struct
    {
      __IO uint32_t xmcen                : 1; /* [0] */
      __IO uint32_t qspi1en              : 1; /* [1] */
      __IO uint32_t reserved1            : 12;/* [13:2] */
      __IO uint32_t qspi2en              : 1; /* [14] */
      __IO uint32_t sdio2en              : 1; /* [15] */
      __IO uint32_t reserved3            : 16;/* [31:16] */
    } ahben3_bit;
  };

  /**
    * @brief crm reserved3 register, offset:0x3C
    */
  __IO uint32_t reserved3;

  /**
    * @brief crm apb1en register, offset:0x40
    */
  union
  {
    __IO uint32_t apb1en;
    struct
    {
      __IO uint32_t tmr2en               : 1; /* [0] */
      __IO uint32_t tmr3en               : 1; /* [1] */
      __IO uint32_t tmr4en               : 1; /* [2] */
      __IO uint32_t tmr5en               : 1; /* [3] */
      __IO uint32_t tmr6en               : 1; /* [4] */
      __IO uint32_t tmr7en               : 1; /* [5] */
      __IO uint32_t tmr12en              : 1; /* [6] */
      __IO uint32_t tmr13en              : 1; /* [7] */
      __IO uint32_t adc14en              : 1; /* [8] */
      __IO uint32_t reserved1            : 2; /* [10:9] */
      __IO uint32_t wwdten               : 1; /* [11] */
      __IO uint32_t reserved2            : 2; /* [13:12] */
      __IO uint32_t spi2en               : 1; /* [14] */
      __IO uint32_t spi3en               : 1; /* [15] */
      __IO uint32_t reserved3            : 1; /* [16] */
      __IO uint32_t usart2en             : 1; /* [17] */
      __IO uint32_t usart3en             : 1; /* [18] */
      __IO uint32_t uart4en              : 1; /* [19] */
      __IO uint32_t uart5en              : 1; /* [20] */
      __IO uint32_t i2c1en               : 1; /* [21] */
      __IO uint32_t i2c2en               : 1; /* [22] */
      __IO uint32_t i2c3en               : 1; /* [23] */
      __IO uint32_t reserved4            : 1; /* [24] */
      __IO uint32_t can1en               : 1; /* [25] */
      __IO uint32_t can2en               : 1; /* [26] */
      __IO uint32_t reserved5            : 1; /* [27] */
      __IO uint32_t pwcen                : 1; /* [28] */
      __IO uint32_t dacen                : 1; /* [29] */
      __IO uint32_t uart7en              : 1; /* [30] */
      __IO uint32_t uart8en              : 1; /* [31] */
    } apb1en_bit;
  };

  /**
    * @brief crm apb2en register, offset:0x44
    */
  union
  {
    __IO uint32_t apb2en;
    struct
    {
      __IO uint32_t tmr1en               : 1; /* [0] */
      __IO uint32_t tmr8en               : 1; /* [1] */
      __IO uint32_t reserved1            : 2; /* [3:2] */
      __IO uint32_t usart1en             : 1; /* [4] */
      __IO uint32_t usart6en             : 1; /* [5] */
      __IO uint32_t reserved2            : 2; /* [7:6] */
      __IO uint32_t adcen                : 1; /* [8] */
      __IO uint32_t reserved3            : 3; /* [11:9] */
      __IO uint32_t spi1en               : 1; /* [12] */
      __IO uint32_t spi4en               : 1; /* [13] */
      __IO uint32_t scfgen               : 1; /* [14] */
      __IO uint32_t reserved4            : 1; /* [15] */
      __IO uint32_t tmr9en               : 1; /* [16] */
      __IO uint32_t tmr10en              : 1; /* [17] */
      __IO uint32_t tmr11en              : 1; /* [18] */
      __IO uint32_t reserved5            : 1; /* [19] */
      __IO uint32_t tmr20en              : 1; /* [20] */
      __IO uint32_t reserved6            : 8; /* [28:21] */
      __IO uint32_t accen                : 1; /* [29] */
      __IO uint32_t reserved7            : 2; /* [31:30] */
    } apb2en_bit;
  };

  /**
    * @brief crm reserved4 register, offset:0x48~0x4C
    */
  __IO uint32_t reserved4[2];

  /**
    * @brief crm ahblpen1 register, offset:0x50
    */
  union
  {
    __IO uint32_t ahblpen1;
#if defined (AT32F435xx)
    struct
    {
      __IO uint32_t gpioalpen            : 1; /* [0] */
      __IO uint32_t gpioblpen            : 1; /* [1] */
      __IO uint32_t gpioclpen            : 1; /* [2] */
      __IO uint32_t gpiodlpen            : 1; /* [3] */
      __IO uint32_t gpioelpen            : 1; /* [4] */
      __IO uint32_t gpioflpen            : 1; /* [5] */
      __IO uint32_t gpioglpen            : 1; /* [6] */
      __IO uint32_t gpiohlpen            : 1; /* [7] */
      __IO uint32_t reserved1            : 4; /* [11:8] */
      __IO uint32_t crclpen              : 1; /* [12] */
      __IO uint32_t reserved2            : 8; /* [20:13] */
      __IO uint32_t edmalpen             : 1; /* [21] */
      __IO uint32_t dma1lpen             : 1; /* [22] */
      __IO uint32_t reserved3            : 1; /* [23] */
      __IO uint32_t dma2lpen             : 1; /* [24] */
      __IO uint32_t reserved4            : 4; /* [28:25] */
      __IO uint32_t otgfs2lpen           : 1; /* [29] */
      __IO uint32_t reserved5            : 2; /* [31:30] */
    } ahblpen1_bit;
#endif

#if defined (AT32F437xx)
    struct
    {
      __IO uint32_t gpioalpen            : 1; /* [0] */
      __IO uint32_t gpioblpen            : 1; /* [1] */
      __IO uint32_t gpioclpen            : 1; /* [2] */
      __IO uint32_t gpiodlpen            : 1; /* [3] */
      __IO uint32_t gpioelpen            : 1; /* [4] */
      __IO uint32_t gpioflpen            : 1; /* [5] */
      __IO uint32_t gpioglpen            : 1; /* [6] */
      __IO uint32_t gpiohlpen            : 1; /* [7] */
      __IO uint32_t reserved1            : 4; /* [11:8] */
      __IO uint32_t crclpen              : 1; /* [12] */
      __IO uint32_t reserved2            : 8; /* [20:13] */
      __IO uint32_t edmalpen             : 1; /* [21] */
      __IO uint32_t dma1lpen             : 1; /* [22] */
      __IO uint32_t reserved3            : 1; /* [23] */
      __IO uint32_t dma2lpen             : 1; /* [24] */
      __IO uint32_t emaclpen             : 1; /* [25] */
      __IO uint32_t emactxlpen           : 1; /* [26] */
      __IO uint32_t emacrxlpen           : 1; /* [27] */
      __IO uint32_t emacptplpen          : 1; /* [28] */
      __IO uint32_t otgfs2lpen           : 1; /* [29] */
      __IO uint32_t reserved4            : 2; /* [31:30] */
    } ahblpen1_bit;
#endif
  };

  /**
    * @brief crm ahblpen2 register, offset:0x54
    */
  union
  {
    __IO uint32_t ahblpen2;
    struct
    {
      __IO uint32_t dvplpen              : 1; /* [0] */
      __IO uint32_t reserved1            : 6; /* [6:1] */
      __IO uint32_t otgfs1lpen           : 1; /* [7] */
      __IO uint32_t reserved2            : 7; /* [14:8] */
      __IO uint32_t sdio1lpen            : 1; /* [15] */
      __IO uint32_t reserved3            : 16;/* [31:16] */
    } ahblpen2_bit;
  };

  /**
    * @brief crm ahblpen3 register, offset:0x58
    */
  union
  {
    __IO uint32_t ahblpen3;
    struct
    {
      __IO uint32_t xmclpen              : 1; /* [0] */
      __IO uint32_t qspi1lpen            : 1; /* [1] */
      __IO uint32_t reserved1            : 12;/* [13:2] */
      __IO uint32_t qspi2lpen            : 1; /* [14] */
      __IO uint32_t sdio2lpen            : 1; /* [15] */
      __IO uint32_t reserved3            : 16;/* [31:16] */
    } ahblpen3_bit;
  };

  /**
    * @brief crm reserved5 register, offset:0x5C
    */
  __IO uint32_t reserved5;

  /**
    * @brief crm apb1lpen register, offset:0x60
    */
  union
  {
    __IO uint32_t apb1lpen;
    struct
    {
      __IO uint32_t tmr2lpen             : 1; /* [0] */
      __IO uint32_t tmr3lpen             : 1; /* [1] */
      __IO uint32_t tmr4lpen             : 1; /* [2] */
      __IO uint32_t tmr5lpen             : 1; /* [3] */
      __IO uint32_t tmr6lpen             : 1; /* [4] */
      __IO uint32_t tmr7lpen             : 1; /* [5] */
      __IO uint32_t tmr12lpen            : 1; /* [6] */
      __IO uint32_t tmr13lpen            : 1; /* [7] */
      __IO uint32_t adc14lpen            : 1; /* [8] */
      __IO uint32_t reserved1            : 2; /* [10:9] */
      __IO uint32_t wwdtlpen             : 1; /* [11] */
      __IO uint32_t reserved2            : 2; /* [13:12] */
      __IO uint32_t spi2lpen             : 1; /* [14] */
      __IO uint32_t spi3lpen             : 1; /* [15] */
      __IO uint32_t reserved3            : 1; /* [16] */
      __IO uint32_t usart2lpen           : 1; /* [17] */
      __IO uint32_t usart3lpen           : 1; /* [18] */
      __IO uint32_t uart4lpen            : 1; /* [19] */
      __IO uint32_t uart5lpen            : 1; /* [20] */
      __IO uint32_t i2c1lpen             : 1; /* [21] */
      __IO uint32_t i2c2lpen             : 1; /* [22] */
      __IO uint32_t i2c3lpen             : 1; /* [23] */
      __IO uint32_t reserved4            : 1; /* [24] */
      __IO uint32_t can1lpen             : 1; /* [25] */
      __IO uint32_t can2lpen             : 1; /* [26] */
      __IO uint32_t reserved5            : 1; /* [27] */
      __IO uint32_t pwclpen              : 1; /* [28] */
      __IO uint32_t daclpen              : 1; /* [29] */
      __IO uint32_t uart7lpen            : 1; /* [30] */
      __IO uint32_t uart8lpen            : 1; /* [31] */
    } apb1lpen_bit;
  };

  /**
    * @brief crm apb2lpen register, offset:0x64
    */
  union
  {
    __IO uint32_t apb2lpen;
    struct
    {
      __IO uint32_t tmr1lpen             : 1; /* [0] */
      __IO uint32_t tmr8lpen             : 1; /* [1] */
      __IO uint32_t reserved1            : 2; /* [3:2] */
      __IO uint32_t usart1lpen           : 1; /* [4] */
      __IO uint32_t usart6lpen           : 1; /* [5] */
      __IO uint32_t reserved2            : 2; /* [7:6] */
      __IO uint32_t adclpen              : 1; /* [8] */
      __IO uint32_t reserved3            : 3; /* [11:9] */
      __IO uint32_t spi1lpen             : 1; /* [12] */
      __IO uint32_t spi4lpen             : 1; /* [13] */
      __IO uint32_t scfglpen             : 1; /* [14] */
      __IO uint32_t reserved4            : 1; /* [15] */
      __IO uint32_t tmr9lpen             : 1; /* [16] */
      __IO uint32_t tmr10lpen            : 1; /* [17] */
      __IO uint32_t tmr11lpen            : 1; /* [18] */
      __IO uint32_t reserved5            : 1; /* [19] */
      __IO uint32_t tmr20lpen            : 1; /* [20] */
      __IO uint32_t reserved6            : 8; /* [28:21] */
      __IO uint32_t acclpen              : 1; /* [29] */
      __IO uint32_t reserved7            : 2; /* [31:30] */
    } apb2lpen_bit;
  };

  /**
    * @brief crm reserved6 register, offset:0x68~0x6C
    */
  __IO uint32_t reserved6[2];

  /**
    * @brief crm bpdc register, offset:0x70
    */
  union
  {
    __IO uint32_t bpdc;
    struct
    {
      __IO uint32_t lexten               : 1; /* [0] */
      __IO uint32_t lextstbl             : 1; /* [1] */
      __IO uint32_t lextbyps             : 1; /* [2] */
      __IO uint32_t reserved1            : 5; /* [7:3] */
      __IO uint32_t ertcsel              : 2; /* [9:8] */
      __IO uint32_t reserved2            : 5; /* [14:10] */
      __IO uint32_t ertcen               : 1; /* [15] */
      __IO uint32_t bpdrst               : 1; /* [16] */
      __IO uint32_t reserved3            : 15;/* [31:17] */
    } bpdc_bit;
  };

  /**
    * @brief crm ctrlsts register, offset:0x74
    */
  union
  {
    __IO uint32_t ctrlsts;
    struct
    {
      __IO uint32_t licken               : 1; /* [0] */
      __IO uint32_t lickstbl             : 1; /* [1] */
      __IO uint32_t reserved1            : 22;/* [23:2] */
      __IO uint32_t rstfc                : 1; /* [24] */
      __IO uint32_t reserved2            : 1; /* [25] */
      __IO uint32_t nrstf                : 1; /* [26] */
      __IO uint32_t porrstf              : 1; /* [27] */
      __IO uint32_t swrstf               : 1; /* [28] */
      __IO uint32_t wdtrstf              : 1; /* [29] */
      __IO uint32_t wwdtrstf             : 1; /* [30] */
      __IO uint32_t lprstf               : 1; /* [31] */
    } ctrlsts_bit;
  };

  /**
    * @brief crm reserved7 register, offset:0x78~0x9C
    */
  __IO uint32_t reserved7[10];

  /**
    * @brief crm misc1 register, offset:0xA0
    */
  union
  {
    __IO uint32_t misc1;
    struct
    {
      __IO uint32_t hickcal_key          : 8; /* [7:0] */
      __IO uint32_t reserved1            : 4; /* [11:8] */
      __IO uint32_t hickdiv              : 1; /* [12] */
      __IO uint32_t hick_to_usb          : 1; /* [13] */
      __IO uint32_t hick_to_sclk         : 1; /* [14] */
      __IO uint32_t reserved2            : 1; /* [15] */
      __IO uint32_t clkout2_sel2         : 4; /* [19:16] */
      __IO uint32_t reserved3            : 4; /* [23:20] */
      __IO uint32_t clkout1div2          : 4; /* [27:24] */
      __IO uint32_t clkout2div2          : 4; /* [31:28] */
    } misc1_bit;
  };

  /**
    * @brief crm misc2 register, offset:0xA4
    */
  union
  {
    __IO uint32_t misc2;
    struct
    {
      __IO uint32_t reserved1            : 4; /* [3:0] */
      __IO uint32_t auto_step_en         : 2; /* [5:4] */
      __IO uint32_t reserved2            : 2; /* [7:6] */
      __IO uint32_t clk_to_tmr           : 1; /* [8] */
      __IO uint32_t emac_pps_sel         : 1; /* [9] */
      __IO uint32_t reserved3            : 2; /* [11:10] */
      __IO uint32_t usbdiv               : 4; /* [15:12] */
      __IO uint32_t reserved4            : 16;/* [31:16] */
    } misc2_bit;
  };

} crm_type;

/**
  * @}
  */

#define CRM                              ((crm_type *) CRM_BASE)

/** @defgroup CRM_exported_functions
  * @{
  */

void crm_reset(void);
void crm_lext_bypass(confirm_state new_state);
void crm_hext_bypass(confirm_state new_state);
flag_status crm_flag_get(uint32_t flag);
flag_status crm_interrupt_flag_get(uint32_t flag);
error_status crm_hext_stable_wait(void);
void crm_hick_clock_trimming_set(uint8_t trim_value);
void crm_hick_clock_calibration_set(uint8_t cali_value);
void crm_periph_clock_enable(crm_periph_clock_type value, confirm_state new_state);
void crm_periph_reset(crm_periph_reset_type value, confirm_state new_state);
void crm_periph_lowpower_mode_enable(crm_periph_clock_lowpower_type value, confirm_state new_state);
void crm_clock_source_enable(crm_clock_source_type source, confirm_state new_state);
void crm_flag_clear(uint32_t flag);
void crm_ertc_clock_select(crm_ertc_clock_type value);
void crm_ertc_clock_enable(confirm_state new_state);
void crm_ahb_div_set(crm_ahb_div_type value);
void crm_apb1_div_set(crm_apb1_div_type value);
void crm_apb2_div_set(crm_apb2_div_type value);
void crm_usb_clock_div_set(crm_usb_div_type value);
void crm_clock_failure_detection_enable(confirm_state new_state);
void crm_battery_powered_domain_reset(confirm_state new_state);
void crm_auto_step_mode_enable(confirm_state new_state);
void crm_hick_divider_select(crm_hick_div_6_type value);
void crm_hick_sclk_frequency_select(crm_hick_sclk_frequency_type value);
void crm_usb_clock_source_select(crm_usb_clock_source_type value);
void crm_clkout_to_tmr10_enable(confirm_state new_state);
void crm_pll_config(crm_pll_clock_source_type clock_source, uint16_t pll_ns, \
                    uint16_t pll_ms, crm_pll_fr_type pll_fr);
void crm_sysclk_switch(crm_sclk_type value);
crm_sclk_type crm_sysclk_switch_status_get(void);
void crm_clocks_freq_get(crm_clocks_freq_type *clocks_struct);
void crm_clock_out1_set(crm_clkout1_select_type clkout);
void crm_clock_out2_set(crm_clkout2_select_type clkout);
void crm_clkout_div_set(crm_clkout_index_type index, crm_clkout_div1_type div1, crm_clkout_div2_type div2);
void crm_emac_output_pulse_set(crm_emac_output_pulse_type width);
void crm_interrupt_enable(uint32_t crm_int, confirm_state new_state);
error_status crm_pll_parameter_calculate(crm_pll_clock_source_type pll_rcs, uint32_t target_sclk_freq, \
                                         uint16_t *ret_ms, uint16_t *ret_ns, uint16_t *ret_fr);

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

#endif
