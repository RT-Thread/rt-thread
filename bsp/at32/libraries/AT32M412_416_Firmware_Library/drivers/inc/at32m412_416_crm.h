/**
  **************************************************************************
  * @file     at32m412_416_crm.h
  * @brief    at32m412_416 crm header file
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
#ifndef __AT32M412_416_CRM_H
#define __AT32M412_416_CRM_H

#ifdef __cplusplus
extern "C" {
#endif


/* includes ------------------------------------------------------------------*/
#include "at32m412_416.h"

/** @addtogroup AT32M412_416_periph_driver
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
#define CRM_PLLU_STABLE_FLAG             MAKE_VALUE(0x00, 26) /*!< phase locking loop usb path stable flag */
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
  /* ahb periph1 */
  CRM_GPIOA_PERIPH_CLOCK                 = MAKE_VALUE(0x30, 0),  /*!< gpioa periph clock */
  CRM_GPIOB_PERIPH_CLOCK                 = MAKE_VALUE(0x30, 1),  /*!< gpiob periph clock */
  CRM_GPIOC_PERIPH_CLOCK                 = MAKE_VALUE(0x30, 2),  /*!< gpioc periph clock */
  CRM_GPIOF_PERIPH_CLOCK                 = MAKE_VALUE(0x30, 5),  /*!< gpiof periph clock */
  CRM_CRC_PERIPH_CLOCK                   = MAKE_VALUE(0x30, 12), /*!< crc periph clock */
  CRM_DMA1_PERIPH_CLOCK                  = MAKE_VALUE(0x30, 22), /*!< dma1 periph clock */
  /* apb1 periph */
  CRM_TMR3_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 1),  /*!< tmr3 periph clock */
  CRM_TMR4_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 2),  /*!< tmr4 periph clock */
  CRM_TMR6_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 4),  /*!< tmr6 periph clock */
  CRM_TMR7_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 5),  /*!< tmr7 periph clock */
  CRM_WWDT_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 11), /*!< wwdt periph clock */
  CRM_SPI2_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 14), /*!< spi2 periph clock */
  CRM_USART2_PERIPH_CLOCK                = MAKE_VALUE(0x40, 17), /*!< usart2 periph clock */
  CRM_I2C1_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 21), /*!< i2c1 periph clock */
  CRM_I2C2_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 22), /*!< i2c2 periph clock */
  CRM_CAN1_PERIPH_CLOCK                  = MAKE_VALUE(0x40, 25), /*!< can1 periph clock */
  CRM_PWC_PERIPH_CLOCK                   = MAKE_VALUE(0x40, 28), /*!< pwc periph clock */
  CRM_DAC_PERIPH_CLOCK                   = MAKE_VALUE(0x40, 29), /*!< dac periph clock */
  /* apb2 periph */
  CRM_TMR1_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 0),  /*!< tmr1 periph clock */
  CRM_USART1_PERIPH_CLOCK                = MAKE_VALUE(0x44, 4),  /*!< usart1 periph clock */
  CRM_ADC1_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 8),  /*!< adc1 periph clock */
  CRM_ADC2_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 9),  /*!< adc2 periph clock */
  CRM_SPI1_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 12), /*!< spi1 periph clock */
  CRM_SCFG_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 14), /*!< scfg cmp opamp periph clock */
  CRM_TMR9_PERIPH_CLOCK                  = MAKE_VALUE(0x44, 16), /*!< tmr9 periph clock */
  CRM_TMR10_PERIPH_CLOCK                 = MAKE_VALUE(0x44, 17), /*!< tmr10 periph clock */
  CRM_TMR11_PERIPH_CLOCK                 = MAKE_VALUE(0x44, 18)  /*!< tmr11 periph clock */

} crm_periph_clock_type;

/**
  * @brief crm periph reset
  */
typedef enum
{
  /* ahb periph1 */
  CRM_GPIOA_PERIPH_RESET                 = MAKE_VALUE(0x10, 0),  /*!< gpioa periph reset */
  CRM_GPIOB_PERIPH_RESET                 = MAKE_VALUE(0x10, 1),  /*!< gpiob periph reset */
  CRM_GPIOC_PERIPH_RESET                 = MAKE_VALUE(0x10, 2),  /*!< gpioc periph reset */
  CRM_GPIOF_PERIPH_RESET                 = MAKE_VALUE(0x10, 5),  /*!< gpiof periph reset */
  CRM_CRC_PERIPH_RESET                   = MAKE_VALUE(0x10, 12), /*!< crc periph reset */
  CRM_DMA1_PERIPH_RESET                  = MAKE_VALUE(0x10, 22), /*!< dma1 periph reset */
  /* apb1 periph */
  CRM_TMR3_PERIPH_RESET                  = MAKE_VALUE(0x20, 1),  /*!< tmr3 periph reset */
  CRM_TMR4_PERIPH_RESET                  = MAKE_VALUE(0x20, 2),  /*!< tmr4 periph reset */
  CRM_TMR6_PERIPH_RESET                  = MAKE_VALUE(0x20, 4),  /*!< tmr6 periph reset */
  CRM_TMR7_PERIPH_RESET                  = MAKE_VALUE(0x20, 5),  /*!< tmr7 periph reset */
  CRM_WWDT_PERIPH_RESET                  = MAKE_VALUE(0x20, 11), /*!< wwdt periph reset */
  CRM_SPI2_PERIPH_RESET                  = MAKE_VALUE(0x20, 14), /*!< spi2 periph reset */
  CRM_USART2_PERIPH_RESET                = MAKE_VALUE(0x20, 17), /*!< usart2 periph reset */
  CRM_I2C1_PERIPH_RESET                  = MAKE_VALUE(0x20, 21), /*!< i2c1 periph reset */
  CRM_I2C2_PERIPH_RESET                  = MAKE_VALUE(0x20, 22), /*!< i2c2 periph reset */
  CRM_CAN1_PERIPH_RESET                  = MAKE_VALUE(0x20, 25), /*!< can1 periph reset */
  CRM_PWC_PERIPH_RESET                   = MAKE_VALUE(0x20, 28), /*!< pwc periph reset */
  CRM_DAC_PERIPH_RESET                   = MAKE_VALUE(0x20, 29), /*!< dac periph reset */
  /* apb2 periph */
  CRM_TMR1_PERIPH_RESET                  = MAKE_VALUE(0x24, 0),  /*!< tmr1 periph reset */
  CRM_USART1_PERIPH_RESET                = MAKE_VALUE(0x24, 4),  /*!< usart1 periph reset */
  CRM_ADC_PERIPH_RESET                   = MAKE_VALUE(0x24, 8),  /*!< adc periph reset */
  CRM_SPI1_PERIPH_RESET                  = MAKE_VALUE(0x24, 12), /*!< spi1 periph reset */
  CRM_SCFG_PERIPH_RESET                  = MAKE_VALUE(0x24, 14), /*!< scfg cmp opamp periph reset */
  CRM_TMR9_PERIPH_RESET                  = MAKE_VALUE(0x24, 16), /*!< tmr9 periph reset */
  CRM_TMR10_PERIPH_RESET                 = MAKE_VALUE(0x24, 17), /*!< tmr10 periph reset */
  CRM_TMR11_PERIPH_RESET                 = MAKE_VALUE(0x24, 18)  /*!< tmr11 periph reset */

} crm_periph_reset_type;

/**
  * @brief crm periph clock in low power mode
  */
typedef enum
{
  /* ahb periph1 */
  CRM_GPIOA_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 0),  /*!< gpioa sleep mode periph clock */
  CRM_GPIOB_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 1),  /*!< gpiob sleep mode periph clock */
  CRM_GPIOC_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 2),  /*!< gpioc sleep mode periph clock */
  CRM_GPIOF_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 5),  /*!< gpiof sleep mode periph clock */
  CRM_CRC_PERIPH_LOWPOWER                = MAKE_VALUE(0x50, 12), /*!< crc sleep mode periph clock */
  CRM_FLASH_PERIPH_LOWPOWER              = MAKE_VALUE(0x50, 15), /*!< flash sleep mode periph clock */
  CRM_SRAM_PERIPH_LOWPOWER               = MAKE_VALUE(0x50, 16), /*!< sram sleep mode periph clock */
  CRM_DMA1_PERIPH_LOWPOWER               = MAKE_VALUE(0x50, 22), /*!< dma1 sleep mode periph clock */
  /* apb1 periph */
  CRM_TMR3_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 1),  /*!< tmr3 sleep mode periph clock */
  CRM_TMR4_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 2),  /*!< tmr4 sleep mode periph clock */
  CRM_TMR6_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 4),  /*!< tmr6 sleep mode periph clock */
  CRM_TMR7_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 5),  /*!< tmr7 sleep mode periph clock */
  CRM_WWDT_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 11), /*!< wwdt sleep mode periph clock */
  CRM_SPI2_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 14), /*!< spi2 sleep mode periph clock */
  CRM_USART2_PERIPH_LOWPOWER             = MAKE_VALUE(0x60, 17), /*!< usart2 sleep mode periph clock */
  CRM_I2C1_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 21), /*!< i2c1 sleep mode periph clock */
  CRM_I2C2_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 22), /*!< i2c2 sleep mode periph clock */
  CRM_CAN1_PERIPH_LOWPOWER               = MAKE_VALUE(0x60, 25), /*!< can1 sleep mode periph clock */
  CRM_PWC_PERIPH_LOWPOWER                = MAKE_VALUE(0x60, 28), /*!< pwc sleep mode periph clock */
  CRM_DAC_PERIPH_LOWPOWER                = MAKE_VALUE(0x60, 29), /*!< dac sleep mode periph clock */
  /* apb2 periph */
  CRM_TMR1_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 0),  /*!< tmr1 sleep mode periph clock */
  CRM_USART1_PERIPH_LOWPOWER             = MAKE_VALUE(0x64, 4),  /*!< usart1 sleep mode periph clock */
  CRM_ADC1_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 8),  /*!< adc1 sleep mode periph clock */
  CRM_ADC2_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 9),  /*!< adc2 sleep mode periph clock */
  CRM_SPI1_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 12), /*!< spi1 sleep mode periph clock */
  CRM_SCFG_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 14), /*!< scfg cmp opamp sleep mode periph clock */
  CRM_TMR9_PERIPH_LOWPOWER               = MAKE_VALUE(0x64, 16), /*!< tmr9 sleep mode periph clock */
  CRM_TMR10_PERIPH_LOWPOWER              = MAKE_VALUE(0x64, 17), /*!< tmr10 sleep mode periph clock */
  CRM_TMR11_PERIPH_LOWPOWER              = MAKE_VALUE(0x64, 18)  /*!< tmr11 sleep mode periph clock */

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
  * @brief crm apb3 division
  */
typedef enum
{
  CRM_APB3_DIV_1                         = 0x00, /*!< ahbclk div1 to apb3clk */
  CRM_APB3_DIV_2                         = 0x04, /*!< ahbclk div2 to apb3clk */
  CRM_APB3_DIV_4                         = 0x05, /*!< ahbclk div4 to apb3clk */
  CRM_APB3_DIV_8                         = 0x06, /*!< ahbclk div8 to apb3clk */
  CRM_APB3_DIV_16                        = 0x07  /*!< ahbclk div16 to apb3clk */
} crm_apb3_div_type;

/**
  * @brief crm vbat ahb division
  */
typedef enum
{
  CRM_VBATH_DIV_1                         = 0x00, /*!< ahbclk div1 to vbatclk */
  CRM_VBATH_DIV_2                         = 0x02, /*!< ahbclk div2 to vbatclk */
  CRM_VBATH_DIV_4                         = 0x03  /*!< ahbclk div4 to vbatclk */
} crm_vbath_div_type;

/**
  * @brief crm hext to sysclk division
  */
typedef enum
{
  CRM_HEXT_SCLK_DIV_1                    = 0x00, /*!< hext div1 to sysclk */
  CRM_HEXT_SCLK_DIV_2                    = 0x01, /*!< hext div2 to sysclk */
  CRM_HEXT_SCLK_DIV_4                    = 0x02, /*!< hext div4 to sysclk */
  CRM_HEXT_SCLK_DIV_8                    = 0x03, /*!< hext div8 to sysclk */
  CRM_HEXT_SCLK_DIV_16                   = 0x04, /*!< hext div16 to sysclk */
  CRM_HEXT_SCLK_DIV_32                   = 0x05  /*!< hext div32 to sysclk */
} crm_hext_sclk_div_type;                

/**
  * @brief crm hick to sysclk division
  */
typedef enum
{
  CRM_HICK_SCLK_DIV_1                    = 0x00, /*!< hick div1 to sysclk */
  CRM_HICK_SCLK_DIV_2                    = 0x01, /*!< hick div2 to sysclk */
  CRM_HICK_SCLK_DIV_4                    = 0x02, /*!< hick div4 to sysclk */
  CRM_HICK_SCLK_DIV_8                    = 0x03, /*!< hick div8 to sysclk */
  CRM_HICK_SCLK_DIV_16                   = 0x04  /*!< hick div16 to sysclk */
} crm_hick_sclk_div_type;

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
  * @brief crm clkout select
  */
typedef enum
{
  CRM_CLKOUT_SCLK                        = 0x00, /*!< output system clock to clkout pin */
  CRM_CLKOUT_HEXT                        = 0x02, /*!< output high speed external crystal to clkout pin */
  CRM_CLKOUT_PLL                         = 0x03, /*!< output phase locking loop P clock to clkout pin */
  CRM_CLKOUT_USBFS                       = 0x10, /*!< output usbfsclk to clkout pin */
  CRM_CLKOUT_ADC                         = 0x11, /*!< output adcclk to clkout pin */
  CRM_CLKOUT_HICK                        = 0x12, /*!< output high speed internal clock to clkout pin */
  CRM_CLKOUT_LICK                        = 0x13, /*!< output low speed internal clock to clkout pin */
  CRM_CLKOUT_LEXT                        = 0x14  /*!< output low speed external crystal to clkout pin */
} crm_clkout_select_type;

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
  * @brief crm can index
  */
typedef enum
{
  CRM_CAN1                               = 0x00  /*!< can1 */
} crm_can_type;

/**
  * @brief crm usart clock source
  */
typedef enum
{
  CRM_CAN_CLOCK_SOURCE_HEXT              = 0x00, /*!< select hext clock as can clock source */
  CRM_CAN_CLOCK_SOURCE_PLL               = 0x01, /*!< select pll clock as can clock source */
  CRM_CAN_CLOCK_SOURCE_PCLK              = 0x02  /*!< select high speed external clock as can clock source */
} crm_can_clock_source_type;

/**
  * @brief crm hick as system clock frequency select
  */
typedef enum
{
  CRM_HICK_SCLK_8MHZ                     = 0x00, /*!< fixed 8 mhz when hick is selected as sclk */
  CRM_HICK_SCLK_48MHZ                    = 0x01  /*!< 8 mhz or 48 mhz depend on hickdiv when hick is selected as sclk */
} crm_hick_sclk_frequency_type;

/**
  * @brief crm external crystal driving strength
  */
typedef enum
{
  CRM_DRV_STRENGTH_LOW                   = 0x00, /*!< driving strength low */
  CRM_DRV_STRENGTH_MEDIUM_LOW            = 0x01, /*!< driving strength medium low */
  CRM_DRV_STRENGTH_MEDIUM_HIGH           = 0x02, /*!< driving strength medium high */
  CRM_DRV_STRENGTH_HIGH                  = 0x03  /*!< driving strength high */
} crm_drv_strength_type;

/**
  * @brief crm clocks freqency structure
  */
typedef struct
{
  uint32_t                               sclk_freq; /*!< system clock frequency */
  uint32_t                               ahb_freq;  /*!< ahb bus clock frequency */
  uint32_t                               apb2_freq; /*!< apb2 bus clock frequency */
  uint32_t                               apb1_freq; /*!< apb1 bus clock frequency */
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
      __IO uint32_t reserved2            : 6; /* [26:21] */
      __IO uint32_t clkoutdiv1           : 3; /* [29:27] */
      __IO uint32_t clkout_sel1          : 2; /* [31:30] */
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
    struct
    {
      __IO uint32_t gpioarst             : 1; /* [0] */
      __IO uint32_t gpiobrst             : 1; /* [1] */
      __IO uint32_t gpiocrst             : 1; /* [2] */
      __IO uint32_t reserved1            : 2; /* [4:3] */
      __IO uint32_t gpiofrst             : 1; /* [5] */
      __IO uint32_t reserved2            : 6; /* [11:6] */
      __IO uint32_t crcrst               : 1; /* [12] */
      __IO uint32_t reserved3            : 9; /* [21:13] */
      __IO uint32_t dma1rst              : 1; /* [22] */
      __IO uint32_t reserved4            : 9; /* [31:23] */
    } ahbrst1_bit;
  };

  /**
    * @brief crm reserved1 register, offset:0x14 ~ 0x1C
    */
  __IO uint32_t reserved1[3];

  /**
    * @brief crm apb1rst register, offset:0x20
    */
  union
  {
    __IO uint32_t apb1rst;
    struct
    {
      __IO uint32_t reserved1            : 1; /* [0] */
      __IO uint32_t tmr3rst              : 1; /* [1] */
      __IO uint32_t tmr4rst              : 1; /* [2] */
      __IO uint32_t reserved2            : 1; /* [3] */
      __IO uint32_t tmr6rst              : 1; /* [4] */
      __IO uint32_t tmr7rst              : 1; /* [5] */
      __IO uint32_t reserved3            : 5; /* [10:6] */
      __IO uint32_t wwdtrst              : 1; /* [11] */
      __IO uint32_t reserved4            : 2; /* [13:12] */
      __IO uint32_t spi2rst              : 1; /* [14] */
      __IO uint32_t reserved5            : 2; /* [16:15] */
      __IO uint32_t usart2rst            : 1; /* [17] */
      __IO uint32_t reserved6            : 3; /* [20:18] */
      __IO uint32_t i2c1rst              : 1; /* [21] */
      __IO uint32_t i2c2rst              : 1; /* [22] */
      __IO uint32_t reserved7            : 2; /* [24:23] */
      __IO uint32_t can1rst              : 1; /* [25] */
      __IO uint32_t reserved8            : 2; /* [27:26] */
      __IO uint32_t pwcrst               : 1; /* [28] */
      __IO uint32_t dacrst               : 1; /* [29] */
      __IO uint32_t reserved9            : 2; /* [31:30] */
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
      __IO uint32_t reserved1            : 3; /* [3:1] */
      __IO uint32_t usart1rst            : 1; /* [4] */
      __IO uint32_t reserved2            : 3; /* [7:5] */
      __IO uint32_t adcrst               : 1; /* [8] */
      __IO uint32_t reserved3            : 3; /* [11:9] */
      __IO uint32_t spi1rst              : 1; /* [12] */
      __IO uint32_t reserved4            : 1; /* [13] */
      __IO uint32_t scfgrst              : 1; /* [14] */
      __IO uint32_t reserved5            : 1; /* [15] */
      __IO uint32_t tmr9rst              : 1; /* [16] */
      __IO uint32_t tmr10rst             : 1; /* [17] */
      __IO uint32_t tmr11rst             : 1; /* [18] */
      __IO uint32_t reserved6            : 13;/* [31:19] */
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
    struct
    {
      __IO uint32_t gpioaen              : 1; /* [0] */
      __IO uint32_t gpioben              : 1; /* [1] */
      __IO uint32_t gpiocen              : 1; /* [2] */
      __IO uint32_t reserved1            : 2; /* [4:3] */
      __IO uint32_t gpiofen              : 1; /* [5] */
      __IO uint32_t reserved2            : 6; /* [11:6] */
      __IO uint32_t crcen                : 1; /* [12] */
      __IO uint32_t reserved3            : 9; /* [21:13] */
      __IO uint32_t dma1en               : 1; /* [22] */
      __IO uint32_t reserved4            : 9; /* [31:23] */
    } ahben1_bit;
  };

  /**
    * @brief crm reserved3 register, offset:0x34 ~ 0x3C
    */
  __IO uint32_t reserved3[3];

  /**
    * @brief crm apb1en register, offset:0x40
    */
  union
  {
    __IO uint32_t apb1en;
    struct
    {
      __IO uint32_t reserved1            : 1; /* [0] */
      __IO uint32_t tmr3en               : 1; /* [1] */
      __IO uint32_t tmr4en               : 1; /* [2] */
      __IO uint32_t reserved2            : 1; /* [3] */
      __IO uint32_t tmr6en               : 1; /* [4] */
      __IO uint32_t tmr7en               : 1; /* [5] */
      __IO uint32_t reserved3            : 5; /* [10:6] */
      __IO uint32_t wwdten               : 1; /* [11] */
      __IO uint32_t reserved4            : 2; /* [13:12] */
      __IO uint32_t spi2en               : 1; /* [14] */
      __IO uint32_t reserved5            : 2; /* [16:15] */
      __IO uint32_t usart2en             : 1; /* [17] */
      __IO uint32_t reserved6            : 3; /* [20:18] */
      __IO uint32_t i2c1en               : 1; /* [21] */
      __IO uint32_t i2c2en               : 1; /* [22] */
      __IO uint32_t reserved7            : 2; /* [24:23] */
      __IO uint32_t can1en               : 1; /* [25] */
      __IO uint32_t reserved8            : 2; /* [27:26] */
      __IO uint32_t pwcen                : 1; /* [28] */
      __IO uint32_t dacen                : 1; /* [29] */
      __IO uint32_t reserved9            : 2; /* [31:30] */
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
      __IO uint32_t reserved1            : 3; /* [3:1] */
      __IO uint32_t usart1en             : 1; /* [4] */
      __IO uint32_t reserved2            : 3; /* [7:5] */
      __IO uint32_t adc1en               : 1; /* [8] */
      __IO uint32_t adc2en               : 1; /* [9] */
      __IO uint32_t reserved3            : 2; /* [11:10] */
      __IO uint32_t spi1en               : 1; /* [12] */
      __IO uint32_t reserved4            : 1; /* [13] */
      __IO uint32_t scfgen               : 1; /* [14] */
      __IO uint32_t reserved5            : 1; /* [15] */
      __IO uint32_t tmr9en               : 1; /* [16] */
      __IO uint32_t tmr10en              : 1; /* [17] */
      __IO uint32_t tmr11en              : 1; /* [18] */
      __IO uint32_t reserved6            : 13;/* [31:19] */
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
    struct
    {
      __IO uint32_t gpioalpen            : 1; /* [0] */
      __IO uint32_t gpioblpen            : 1; /* [1] */
      __IO uint32_t gpioclpen            : 1; /* [2] */
      __IO uint32_t reserved1            : 2; /* [4:3] */
      __IO uint32_t gpioflpen            : 1; /* [5] */
      __IO uint32_t reserved2            : 6; /* [11:6] */
      __IO uint32_t crclpen              : 1; /* [12] */
      __IO uint32_t reserved3            : 2; /* [14:13] */
      __IO uint32_t flashlpen            : 1; /* [15] */
      __IO uint32_t sramlpen             : 1; /* [16] */
      __IO uint32_t reserved4            : 5; /* [21:17] */
      __IO uint32_t dma1lpen             : 1; /* [22] */
      __IO uint32_t reserved5            : 9; /* [31:23] */
    } ahblpen1_bit;
  };

  /**
    * @brief crm reserved5 register, offset:0x54 ~ 0x5C
    */
  __IO uint32_t reserved5[3];

  /**
    * @brief crm apb1lpen register, offset:0x60
    */
  union
  {
    __IO uint32_t apb1lpen;
    struct
    {
      __IO uint32_t reserved1            : 1; /* [0] */
      __IO uint32_t tmr3lpen             : 1; /* [1] */
      __IO uint32_t tmr4lpen             : 1; /* [2] */
      __IO uint32_t reserved2            : 1; /* [3] */
      __IO uint32_t tmr6lpen             : 1; /* [4] */
      __IO uint32_t tmr7lpen             : 1; /* [5] */
      __IO uint32_t reserved3            : 5; /* [10:6] */
      __IO uint32_t wwdtlpen             : 1; /* [11] */
      __IO uint32_t reserved4            : 2; /* [13:12] */
      __IO uint32_t spi2lpen             : 1; /* [14] */
      __IO uint32_t reserved5            : 2; /* [16:15] */
      __IO uint32_t usart2lpen           : 1; /* [17] */
      __IO uint32_t reserved6            : 3; /* [20:18] */
      __IO uint32_t i2c1lpen             : 1; /* [21] */
      __IO uint32_t i2c2lpen             : 1; /* [22] */
      __IO uint32_t reserved7            : 2; /* [24:23] */
      __IO uint32_t can1lpen             : 1; /* [25] */
      __IO uint32_t reserved8            : 2; /* [27:26] */
      __IO uint32_t pwclpen              : 1; /* [28] */
      __IO uint32_t daclpen              : 1; /* [29] */
      __IO uint32_t reserved9            : 2; /* [31:30] */
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
      __IO uint32_t reserved1            : 3; /* [3:1] */
      __IO uint32_t usart1lpen           : 1; /* [4] */
      __IO uint32_t reserved2            : 3; /* [7:5] */
      __IO uint32_t adc1lpen             : 1; /* [8] */
      __IO uint32_t adc2lpen             : 1; /* [9] */
      __IO uint32_t reserved3            : 2; /* [11:10] */
      __IO uint32_t spi1lpen             : 1; /* [12] */
      __IO uint32_t reserved4            : 1; /* [13] */
      __IO uint32_t scfglpen             : 1; /* [14] */
      __IO uint32_t reserved5            : 1; /* [15] */
      __IO uint32_t tmr9lpen             : 1; /* [16] */
      __IO uint32_t tmr10lpen            : 1; /* [17] */
      __IO uint32_t tmr11lpen            : 1; /* [18] */
      __IO uint32_t reserved6            : 13;/* [31:19] */
    } apb2lpen_bit;
  };

  /**
    * @brief crm piclks register, offset:0x68
    */
  union
  {
    __IO uint32_t piclks;
    struct
    {
      __IO uint32_t reserved1            : 24;/* [23:0] */
      __IO uint32_t can1sel              : 2; /* [25:24] */
      __IO uint32_t reserved2            : 6; /* [31:26] */
    } piclks_bit;
  };

  /**
    * @brief crm reserved6 register, offset:0x6C
    */
  __IO uint32_t reserved6;

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
      __IO uint32_t lextdrv              : 2; /* [4:3] */
      __IO uint32_t reserved1            : 3; /* [7:5] */
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
      __IO uint32_t reserved2            : 1; /* [13] */
      __IO uint32_t hick_to_sclk         : 1; /* [14] */
      __IO uint32_t reserved3            : 1; /* [15] */
      __IO uint32_t clkout_sel2          : 4; /* [19:16] */
      __IO uint32_t reserved4            : 8; /* [27:20] */
      __IO uint32_t clkoutdiv2           : 4; /* [31:28] */
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
      __IO uint32_t reserved2            : 6; /* [11:6] */
      __IO uint32_t apb3div              : 3; /* [14:12] */
      __IO uint32_t reserved3            : 1; /* [15] */
      __IO uint32_t hick_to_sclk_div     : 3; /* [18:16] */
      __IO uint32_t hext_to_sclk_div     : 3; /* [21:19] */
      __IO uint32_t hextdrv              : 2; /* [23:22] */
      __IO uint32_t vbathdiv             : 2; /* [25:24] */
      __IO uint32_t reserved5            : 6; /* [31:26] */
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
void crm_hext_sclk_div_set(crm_hext_sclk_div_type value);
void crm_hick_sclk_div_set(crm_hick_sclk_div_type value);
void crm_clock_failure_detection_enable(confirm_state new_state);
void crm_battery_powered_domain_reset(confirm_state new_state);
void crm_auto_step_mode_enable(confirm_state new_state);
void crm_hick_sclk_frequency_select(crm_hick_sclk_frequency_type value);
void crm_can_clock_select(crm_can_type can_index, crm_can_clock_source_type value);
crm_can_clock_source_type crm_can_clock_get(crm_can_type can_index);
void crm_pll_config(crm_pll_clock_source_type clock_source, uint16_t pll_ns, \
                    uint16_t pll_ms, crm_pll_fr_type pll_fr);
void crm_sysclk_switch(crm_sclk_type value);
crm_sclk_type crm_sysclk_switch_status_get(void);
void crm_clocks_freq_get(crm_clocks_freq_type *clocks_struct);
void crm_clock_out_set(crm_clkout_select_type clkout);
void crm_clkout_div_set(crm_clkout_div1_type div1, crm_clkout_div2_type div2);
void crm_interrupt_enable(uint32_t crm_int, confirm_state new_state);
error_status crm_pll_parameter_calculate(crm_pll_clock_source_type pll_rcs, uint32_t target_sclk_freq, \
                                         uint16_t *ret_ms, uint16_t *ret_ns, uint16_t *ret_fr);
void crm_apb3_div_set(crm_apb3_div_type value);
void crm_vbath_div_set(crm_vbath_div_type value);
void crm_lextdrv_set(crm_drv_strength_type value);
void crm_hextdrv_set(crm_drv_strength_type value);

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
