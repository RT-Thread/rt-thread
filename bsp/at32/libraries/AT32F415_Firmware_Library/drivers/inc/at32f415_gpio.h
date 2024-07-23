/**
  **************************************************************************
  * @file     at32f415_gpio.h
  * @brief    at32f415 gpio header file
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
#ifndef __AT32F415_GPIO_H
#define __AT32F415_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif


/* includes ------------------------------------------------------------------*/
#include "at32f415.h"

/** @addtogroup AT32F415_periph_driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */

/** @defgroup GPIO_pins_number_definition
  * @{
  */

#define GPIO_PINS_0                      0x0001 /*!< gpio pins number 0 */
#define GPIO_PINS_1                      0x0002 /*!< gpio pins number 1 */
#define GPIO_PINS_2                      0x0004 /*!< gpio pins number 2 */
#define GPIO_PINS_3                      0x0008 /*!< gpio pins number 3 */
#define GPIO_PINS_4                      0x0010 /*!< gpio pins number 4 */
#define GPIO_PINS_5                      0x0020 /*!< gpio pins number 5 */
#define GPIO_PINS_6                      0x0040 /*!< gpio pins number 6 */
#define GPIO_PINS_7                      0x0080 /*!< gpio pins number 7 */
#define GPIO_PINS_8                      0x0100 /*!< gpio pins number 8 */
#define GPIO_PINS_9                      0x0200 /*!< gpio pins number 9 */
#define GPIO_PINS_10                     0x0400 /*!< gpio pins number 10 */
#define GPIO_PINS_11                     0x0800 /*!< gpio pins number 11 */
#define GPIO_PINS_12                     0x1000 /*!< gpio pins number 12 */
#define GPIO_PINS_13                     0x2000 /*!< gpio pins number 13 */
#define GPIO_PINS_14                     0x4000 /*!< gpio pins number 14 */
#define GPIO_PINS_15                     0x8000 /*!< gpio pins number 15 */
#define GPIO_PINS_ALL                    0xFFFF /*!< gpio all pins */

/**
  * @}
  */

#define IOMUX_MAKE_VALUE(reg_offset, bit_addr ,bit_num, bit_val) \
        (uint32_t)(((reg_offset) << 24) | ((bit_addr) << 16) | ((bit_num) << 8) | (bit_val))

/** @defgroup IOMUX_map_definition
  * @brief iomux map definitions
  * @{
  */

#define SPI1_MUX_01                      SPI1_GMUX_0001    /*!< spi1_cs/i2s1_ws(pa15), spi1_sck/i2s1_ck(pb3), spi1_miso(pb4), spi1_mosi/i2s1_sd(pb5), i2s1_mck(pb6) */
#define I2C1_MUX                         I2C1_GMUX_0001    /*!< i2c1_scl(pb8), i2c1_sda(pb9), i2c1_smba(pb5) */
#define USART1_MUX                       USART1_GMUX_0001  /*!< usart1_tx(pb6), usart1_rx(pb7) */
#define USART3_MUX_01                    USART3_GMUX_0001  /*!< usart3_tx(pc10), usart3_rx(pc11), usart3_ck(pc12), usart3_cts(pb13), usart3_rts(pb14) */
#define USART3_MUX_10                    USART3_GMUX_0010  /*!< usart3_tx(pa7), usart3_rx(pa6), usart3_ck(pa5), usart3_cts(pb1), usart3_rts(pb0) */
#define TMR1_MUX_01                      TMR1_GMUX_0001    /*!< tmr1_ext(pa12), tmr1_ch1(pa8), tmr1_ch2(pa9), tmr1_ch3(pa10), tmr1_ch4(pa11), tmr1_brkin(pa6), tmr1_ch1c(pa7), tmr1_ch2c(pb0), tmr1_ch3c(pb1) */
#define TMR2_MUX_01                      TMR2_GMUX_001     /*!< tmr2_ch1_ext(pa15), tmr2_ch2(pb3),   tmr2_ch3(pa2),   tmr2_ch4(pa3) */
#define TMR2_MUX_10                      TMR2_GMUX_010     /*!< tmr2_ch1_ext(pa0),  tmr2_ch2(pa1),   tmr2_ch3(pb10),  tmr2_ch4(pb11) */
#define TMR2_MUX_11                      TMR2_GMUX_011     /*!< tmr2_ch1_ext(pa15), tmr2_ch2(pb3),   tmr2_ch3(pb10),  tmr2_ch4(pb11) */
#define TMR3_MUX_10                      TMR3_GMUX_0010    /*!< tmr3_ch1(pb4), tmr3_ch2(pb5), tmr3_ch3(pb0), tmr3_ch4(pb1) */
#define TMR3_MUX_11                      TMR3_GMUX_0011    /*!< tmr3_ch1(pc6), tmr3_ch2(pc7), tmr3_ch3(pc8), tmr3_ch4(pc9) */
#define CAN_MUX_10                       CAN1_GMUX_0010    /*!< can_rx(pb8), can_tx(pb9) */
#define PD01_MUX                         PD01_GMUX         /*!< pd0/pd1 mapping on osc_in/osc_out */
#define TMR5CH4_MUX                      TMR5CH4_GMUX      /*!< lick connected to tmr5_ch4 input capture for calibration */
#define ADC1_ETP_MUX                     ADC1_ETP_GMUX     /*!< adc1 external trigger preempted conversion muxing */
#define ADC1_ETO_MUX                     ADC1_ETO_GMUX     /*!< adc1 external trigger ordinary conversion muxing */
#define SWJTAG_MUX_001                   SWJTAG_GMUX_001   /*!< full swj enabled  (jtag-dp  +  sw-dp)  but without jtrst */
#define SWJTAG_MUX_010                   SWJTAG_GMUX_010   /*!< jtag-dp disabled and sw-dp enabled */
#define SWJTAG_MUX_100                   SWJTAG_GMUX_100   /*!< full swj disabled  (jtag-dp  +  sw-dp) */

/**
  * @}
  */

/** @defgroup IOMUX_map2_definition
  * @brief iomux map2 definitions
  * @{
  */

#define CMP_MUX_01                       IOMUX_MAKE_VALUE(0x1C, 26, 2, 0x01)          /*!< cmp1_out connect pa6, cmp2_out connect pa7 */
#define CMP_MUX_10                       IOMUX_MAKE_VALUE(0x1C, 26, 2, 0x02)          /*!< cmp1_out connect pa11, cmp2_out connect pa12 */

/**
  * @}
  */

/** @defgroup IOMUX_map3_definition
  * @brief iomux map3 definitions
  * @{
  */

#define TMR9_GMUX                        IOMUX_MAKE_VALUE(0x20, 0, 4, 0x02) /*!< tmr9_ch1(pb14),  tmr9_ch2(pb15) */
#define TMR10_GMUX                       IOMUX_MAKE_VALUE(0x20, 4, 4, 0x02) /*!< tmr10_ch1(pa6) */
#define TMR11_GMUX                       IOMUX_MAKE_VALUE(0x20, 8, 4, 0x02) /*!< tmr11_ch1(pa7) */

/**
  * @}
  */

/** @defgroup IOMUX_map4_definition
  * @brief iomux map4 definitions
  * @{
  */

#define TMR1_GMUX_0001                   IOMUX_MAKE_VALUE(0x24, 0, 4, 0x01)  /*!< tmr1_ext(pa12), tmr1_ch1(pa8), tmr1_ch2(pa9), tmr1_ch3(pa10), tmr1_ch4(pa11), tmr1_brkin(pa6), tmr1_ch1c(pa7), tmr1_ch2c(pb0), tmr1_ch3c(pb1) */
#define TMR1_GMUX_0010                   IOMUX_MAKE_VALUE(0x24, 0, 4, 0x02)  /*!< tmr1_ext(pa0),  tmr1_ch1(pc6), tmr1_ch2(pc7), tmr1_ch3(pc8), tmr1_ch4(pc9), tmr1_brkin(pa6), tmr1_ch1c(pa7), tmr1_ch2c(pb0), tmr1_ch3c(pb1) */
#define TMR2_GMUX_001                    IOMUX_MAKE_VALUE(0x24, 4, 3, 0x01)  /*!< tmr2_ch1_ext(pa15), tmr2_ch2(pb3), tmr2_ch3(pa2),  tmr2_ch4(pa3) */
#define TMR2_GMUX_010                    IOMUX_MAKE_VALUE(0x24, 4, 3, 0x02)  /*!< tmr2_ch1_ext(pa0),  tmr2_ch2(pa1), tmr2_ch3(pb10), tmr2_ch4(pb11) */
#define TMR2_GMUX_011                    IOMUX_MAKE_VALUE(0x24, 4, 3, 0x03)  /*!< tmr2_ch1_ext(pa15), tmr2_ch2(pb3), tmr2_ch3(pb10), tmr2_ch4(pb11) */
#define TMR3_GMUX_0010                   IOMUX_MAKE_VALUE(0x24, 8, 4, 0x02)  /*!< tmr3_ch1(pb4), tmr3_ch2(pb5), tmr3_ch3(pb0), tmr3_ch4(pb1) */
#define TMR3_GMUX_0011                   IOMUX_MAKE_VALUE(0x24, 8, 4, 0x03)  /*!< tmr3_ch1(pc6), tmr3_ch2(pc7), tmr3_ch3(pc8), tmr3_ch4(pc9) */
#define TMR5_GMUX_001                    IOMUX_MAKE_VALUE(0x24, 16, 3, 0x01) /*!< tmr5_ch1(pf4), tmr5_ch2(pf5), tmr5_ch3(pa2), tmr5_ch4(pa3) */
#define TMR5CH4_GMUX                     IOMUX_MAKE_VALUE(0x24, 19, 1, 0x01) /*!< lick connected to tmr5_ch4 input capture for calibration */

/**
  * @}
  */

/** @defgroup IOMUX_map5_definition
  * @brief iomux map5 definitions
  * @{
  */

#define I2C1_GMUX_0001                   IOMUX_MAKE_VALUE(0x28, 4, 4, 0x01)  /*!< i2c1_scl(pb8), i2c1_sda(pb9), i2c1_smba(pb5) */
#define I2C1_GMUX_0010                   IOMUX_MAKE_VALUE(0x28, 4, 4, 0x02)  /*!< i2c1_scl(pf6), i2c1_sda(pf7), i2c1_smba(pb5) */
#define I2C2_GMUX_0001                   IOMUX_MAKE_VALUE(0x28, 8, 4, 0x01)  /*!< i2c2_scl(pa8), i2c2_sda(pc9), i2c2_smba(pa9) */
#define I2C2_GMUX_0010                   IOMUX_MAKE_VALUE(0x28, 8, 4, 0x02)  /*!< i2c2_scl(pa8), i2c2_sda(pb4), i2c2_smba(pa9) */
#define I2C2_GMUX_0011                   IOMUX_MAKE_VALUE(0x28, 8, 4, 0x03)  /*!< i2c2_scl(pf6), i2c2_sda(pf7), i2c2_smba(pa9) */
#define SPI1_GMUX_0001                   IOMUX_MAKE_VALUE(0x28, 16, 4, 0x01) /*!< spi1_cs/i2s1_ws(pa15), spi1_sck/i2s1_ck(pb3), spi1_miso(pb4), spi1_mosi/i2s1_sd(pb5), i2s1_mck(pb6) */
#define SPI2_GMUX_0001                   IOMUX_MAKE_VALUE(0x28, 20, 4, 0x01) /*!< spi2_cs/i2s2_ws(pa15), spi2_sck/i2s2_ck(pb3), spi2_miso(pb4), spi2_mosi/i2s2_sd(pb5), i2s2_mck(pc7) */

/**
  * @}
  */

/** @defgroup IOMUX_map6_definition
  * @brief iomux map6 definitions
  * @{
  */

#define CAN1_GMUX_0010                   IOMUX_MAKE_VALUE(0x2C, 0, 4, 0x02)  /*!< can_rx(pb8),   can_tx(pb9) */
#define SDIO1_GMUX_0100                  IOMUX_MAKE_VALUE(0x2C, 8, 4, 0x04)  /*!< sdio1_ck(pc4), sdio1_cmd(pc5), sdio1_d0(pc0), sdio1_d1(pc1), sdio1_d2(pc2), sdio1_d3(pc3), sdio1_d4(pa4), sdio1_d5(pa5), sdio1_d6(pa6), sdio1_d7(pa7) */
#define SDIO1_GMUX_0101                  IOMUX_MAKE_VALUE(0x2C, 8, 4, 0x05)  /*!< sdio1_ck(pc4), sdio1_cmd(pc5), sdio1_d0(pa4), sdio1_d1(pa5), sdio1_d2(pa6), sdio1_d3(pa7) */
#define SDIO1_GMUX_0110                  IOMUX_MAKE_VALUE(0x2C, 8, 4, 0x06)  /*!< sdio1_ck(pa2), sdio1_cmd(pa3), sdio1_d0(pc0), sdio1_d1(pc1), sdio1_d2(pc2), sdio1_d3(pc3), sdio1_d4(pa4), sdio1_d5(pa5), sdio1_d6(pa6), sdio1_d7(pa7) */
#define SDIO1_GMUX_0111                  IOMUX_MAKE_VALUE(0x2C, 8, 4, 0x07)  /*!< sdio1_ck(pa2), sdio1_cmd(pa3), sdio1_d0(pa4), sdio1_d1(pa5), sdio1_d2(pa6), sdio1_d3(pa7) */
#define USART1_GMUX_0001                 IOMUX_MAKE_VALUE(0x2C, 16, 4, 0x01) /*!< usart1_tx(pb6), usart1_rx(pb7) */
#define USART3_GMUX_0001                 IOMUX_MAKE_VALUE(0x2C, 24, 4, 0x01) /*!< usart3_tx(pc10), usart3_rx(pc11), usart3_ck(pc12), usart3_cts(pb13), usart3_rts(pb14) */
#define USART3_GMUX_0010                 IOMUX_MAKE_VALUE(0x2C, 24, 4, 0x02) /*!< usart3_tx(pa7),  usart3_rx(pa6),  usart3_ck(pa5), usart3_cts(pb1), usart3_rts(pb0) */
#define UART4_GMUX_0001                  IOMUX_MAKE_VALUE(0x2C, 28, 4, 0x01) /*!< uart4_tx(pf4),   uart4_rx(pf5) */

/**
  * @}
  */

/** @defgroup IOMUX_map7_definition
  * @brief iomux map7 definitions
  * @{
  */

#define ADC1_ETP_GMUX                    IOMUX_MAKE_VALUE(0x30, 4, 1, 0x01)  /*!< adc1 external trigger preempted conversion muxing */
#define ADC1_ETO_GMUX                    IOMUX_MAKE_VALUE(0x30, 5, 1, 0x01)  /*!< adc1 external trigger ordinary conversion muxing */
#define SWJTAG_GMUX_001                  IOMUX_MAKE_VALUE(0x30, 16, 3, 0x01) /*!< full swj enabled  (jtag-dp  +  sw-dp)  but without jtrst */
#define SWJTAG_GMUX_010                  IOMUX_MAKE_VALUE(0x30, 16, 3, 0x02) /*!< jtag-dp disabled and sw-dp enabled */
#define SWJTAG_GMUX_100                  IOMUX_MAKE_VALUE(0x30, 16, 3, 0x04) /*!< full swj disabled  (jtag-dp  +  sw-dp) */
#define PD01_GMUX                        IOMUX_MAKE_VALUE(0x30, 20, 1, 0x01) /*!< pd0/pd1 mapping on osc_in/osc_out */

/**
  * @}
  */

/** @defgroup IOMUX_map8_definition
  * @brief iomux map8 definitions
  * @{
  */

#define TMR1_BK1_CMP_GMUX_10             IOMUX_MAKE_VALUE(0x34, 0, 2, 0x02) /*!< cmp tmr1_bpr1 connect tmr1 bk1 */
#define TMR1_BK1_CMP_GMUX_11             IOMUX_MAKE_VALUE(0x34, 0, 2, 0x03) /*!< cmp tmr1_bpr1 and io connect tmr1 bk1 */
#define TMR1_CH1_CMP_GMUX_10             IOMUX_MAKE_VALUE(0x34, 2, 2, 0x02) /*!< cmp connect tmr1 ch1 */
#define TMR1_CH1_CMP_GMUX_11             IOMUX_MAKE_VALUE(0x34, 2, 2, 0x03) /*!< cmp and io connect tmr1 ch1 */
#define TMR2_CH4_CMP_GMUX_10             IOMUX_MAKE_VALUE(0x34, 4, 2, 0x02) /*!< cmp connect tmr2 ch4 */
#define TMR2_CH4_CMP_GMUX_11             IOMUX_MAKE_VALUE(0x34, 4, 2, 0x03) /*!< cmp and io connect tmr2 ch4 */
#define TMR3_CH1_CMP_GMUX_10             IOMUX_MAKE_VALUE(0x34, 6, 2, 0x02) /*!< cmp connect tmr3 ch1 */
#define TMR3_CH1_CMP_GMUX_11             IOMUX_MAKE_VALUE(0x34, 6, 2, 0x03) /*!< cmp and io connect tmr3 ch1 */

/**
  * @}
  */

/** @defgroup GPIO_exported_types
  * @{
  */

/**
  * @brief gpio mode select
  */
typedef enum
{
  GPIO_MODE_INPUT                        = 0x00, /*!< gpio input mode */
  GPIO_MODE_OUTPUT                       = 0x10, /*!< gpio output mode */
  GPIO_MODE_MUX                          = 0x08, /*!< gpio mux function mode */
  GPIO_MODE_ANALOG                       = 0x03  /*!< gpio analog in/out mode */
} gpio_mode_type;

/**
  * @brief gpio output drive strength select
  */
typedef enum
{
  GPIO_DRIVE_STRENGTH_STRONGER           = 0x01, /*!< stronger sourcing/sinking strength */
  GPIO_DRIVE_STRENGTH_MODERATE           = 0x02, /*!< moderate sourcing/sinking strength */
  GPIO_DRIVE_STRENGTH_MAXIMUM            = 0x03  /*!< maximum sourcing/sinking strength */
} gpio_drive_type;

/**
  * @brief gpio output type
  */
typedef enum
{
  GPIO_OUTPUT_PUSH_PULL                  = 0x00, /*!< output push-pull */
  GPIO_OUTPUT_OPEN_DRAIN                 = 0x04  /*!< output open-drain */
} gpio_output_type;

/**
  * @brief gpio pull type
  */
typedef enum
{
  GPIO_PULL_NONE                         = 0x0004, /*!< floating for input, no pull for output */
  GPIO_PULL_UP                           = 0x0018, /*!< pull-up */
  GPIO_PULL_DOWN                         = 0x0028  /*!< pull-down */
} gpio_pull_type;

/**
  * @brief gpio pins source type
  */
typedef enum
{
  GPIO_PINS_SOURCE0                      = 0x00, /*!< gpio pins source number 0 */
  GPIO_PINS_SOURCE1                      = 0x01, /*!< gpio pins source number 1 */
  GPIO_PINS_SOURCE2                      = 0x02, /*!< gpio pins source number 2 */
  GPIO_PINS_SOURCE3                      = 0x03, /*!< gpio pins source number 3 */
  GPIO_PINS_SOURCE4                      = 0x04, /*!< gpio pins source number 4 */
  GPIO_PINS_SOURCE5                      = 0x05, /*!< gpio pins source number 5 */
  GPIO_PINS_SOURCE6                      = 0x06, /*!< gpio pins source number 6 */
  GPIO_PINS_SOURCE7                      = 0x07, /*!< gpio pins source number 7 */
  GPIO_PINS_SOURCE8                      = 0x08, /*!< gpio pins source number 8 */
  GPIO_PINS_SOURCE9                      = 0x09, /*!< gpio pins source number 9 */
  GPIO_PINS_SOURCE10                     = 0x0A, /*!< gpio pins source number 10 */
  GPIO_PINS_SOURCE11                     = 0x0B, /*!< gpio pins source number 11 */
  GPIO_PINS_SOURCE12                     = 0x0C, /*!< gpio pins source number 12 */
  GPIO_PINS_SOURCE13                     = 0x0D, /*!< gpio pins source number 13 */
  GPIO_PINS_SOURCE14                     = 0x0E, /*!< gpio pins source number 14 */
  GPIO_PINS_SOURCE15                     = 0x0F  /*!< gpio pins source number 15 */
} gpio_pins_source_type;

/**
  * @brief gpio port source type
  */
typedef enum
{
  GPIO_PORT_SOURCE_GPIOA                 = 0x00, /*!< gpio port source gpioa */
  GPIO_PORT_SOURCE_GPIOB                 = 0x01, /*!< gpio port source gpiob */
  GPIO_PORT_SOURCE_GPIOC                 = 0x02, /*!< gpio port source gpioc */
  GPIO_PORT_SOURCE_GPIOD                 = 0x03, /*!< gpio port source gpiod */
  GPIO_PORT_SOURCE_GPIOF                 = 0x05, /*!< gpio port source gpiof */
} gpio_port_source_type;

/**
  * @brief gpio init type
  */
typedef struct
{
  uint32_t                               gpio_pins;           /*!< pins number selection */
  gpio_output_type                       gpio_out_type;       /*!< output type selection */
  gpio_pull_type                         gpio_pull;           /*!< pull type selection */
  gpio_mode_type                         gpio_mode;           /*!< mode selection */
  gpio_drive_type                        gpio_drive_strength; /*!< drive strength selection */
} gpio_init_type;

/**
  * @brief type define gpio register all
  */
typedef struct
{
  /**
    * @brief gpio cfglr register, offset:0x00
    */
  union
  {
    __IO uint32_t cfglr;
    struct
    {
      __IO uint32_t iomc0                : 2; /* [1:0] */
      __IO uint32_t iofc0                : 2; /* [3:2] */
      __IO uint32_t iomc1                : 2; /* [5:4] */
      __IO uint32_t iofc1                : 2; /* [7:6] */
      __IO uint32_t iomc2                : 2; /* [9:8] */
      __IO uint32_t iofc2                : 2; /* [11:10] */
      __IO uint32_t iomc3                : 2; /* [13:12] */
      __IO uint32_t iofc3                : 2; /* [15:14] */
      __IO uint32_t iomc4                : 2; /* [17:16] */
      __IO uint32_t iofc4                : 2; /* [19:18] */
      __IO uint32_t iomc5                : 2; /* [21:20] */
      __IO uint32_t iofc5                : 2; /* [23:22] */
      __IO uint32_t iomc6                : 2; /* [25:24] */
      __IO uint32_t iofc6                : 2; /* [27:26] */
      __IO uint32_t iomc7                : 2; /* [29:28] */
      __IO uint32_t iofc7                : 2; /* [31:30] */
    } cfglr_bit;
  };

  /**
    * @brief gpio cfghr register, offset:0x04
    */
  union
  {
    __IO uint32_t cfghr;
    struct
    {
      __IO uint32_t iomc8                : 2; /* [1:0] */
      __IO uint32_t iofc8                : 2; /* [3:2] */
      __IO uint32_t iomc9                : 2; /* [5:4] */
      __IO uint32_t iofc9                : 2; /* [7:6] */
      __IO uint32_t iomc10               : 2; /* [9:8] */
      __IO uint32_t iofc10               : 2; /* [11:10] */
      __IO uint32_t iomc11               : 2; /* [13:12] */
      __IO uint32_t iofc11               : 2; /* [15:14] */
      __IO uint32_t iomc12               : 2; /* [17:16] */
      __IO uint32_t iofc12               : 2; /* [19:18] */
      __IO uint32_t iomc13               : 2; /* [21:20] */
      __IO uint32_t iofc13               : 2; /* [23:22] */
      __IO uint32_t iomc14               : 2; /* [25:24] */
      __IO uint32_t iofc14               : 2; /* [27:26] */
      __IO uint32_t iomc15               : 2; /* [29:28] */
      __IO uint32_t iofc15               : 2; /* [31:30] */
    } cfghr_bit;
  };

  /**
    * @brief gpio idt register, offset:0x08
    */
  union
  {
    __IO uint32_t idt;
    struct
    {
      __IO uint32_t idt0                 : 1; /* [0] */
      __IO uint32_t idt1                 : 1; /* [1] */
      __IO uint32_t idt2                 : 1; /* [2] */
      __IO uint32_t idt3                 : 1; /* [3] */
      __IO uint32_t idt4                 : 1; /* [4] */
      __IO uint32_t idt5                 : 1; /* [5] */
      __IO uint32_t idt6                 : 1; /* [6] */
      __IO uint32_t idt7                 : 1; /* [7] */
      __IO uint32_t idt8                 : 1; /* [8] */
      __IO uint32_t idt9                 : 1; /* [9] */
      __IO uint32_t idt10                : 1; /* [10] */
      __IO uint32_t idt11                : 1; /* [11] */
      __IO uint32_t idt12                : 1; /* [12] */
      __IO uint32_t idt13                : 1; /* [13] */
      __IO uint32_t idt14                : 1; /* [14] */
      __IO uint32_t idt15                : 1; /* [15] */
      __IO uint32_t reserved1            : 16;/* [31:16] */
    } idt_bit;
  };

  /**
    * @brief gpio odt register, offset:0x0C
    */
  union
  {
    __IO uint32_t odt;
    struct
    {
      __IO uint32_t odt0                 : 1; /* [0] */
      __IO uint32_t odt1                 : 1; /* [1] */
      __IO uint32_t odt2                 : 1; /* [2] */
      __IO uint32_t odt3                 : 1; /* [3] */
      __IO uint32_t odt4                 : 1; /* [4] */
      __IO uint32_t odt5                 : 1; /* [5] */
      __IO uint32_t odt6                 : 1; /* [6] */
      __IO uint32_t odt7                 : 1; /* [7] */
      __IO uint32_t odt8                 : 1; /* [8] */
      __IO uint32_t odt9                 : 1; /* [9] */
      __IO uint32_t odt10                : 1; /* [10] */
      __IO uint32_t odt11                : 1; /* [11] */
      __IO uint32_t odt12                : 1; /* [12] */
      __IO uint32_t odt13                : 1; /* [13] */
      __IO uint32_t odt14                : 1; /* [14] */
      __IO uint32_t odt15                : 1; /* [15] */
      __IO uint32_t reserved1            : 16;/* [31:16] */
    } odt_bit;
  };

  /**
    * @brief gpio scr register, offset:0x10
    */
  union
  {
    __IO uint32_t scr;
    struct
    {
      __IO uint32_t iosb0                : 1; /* [0] */
      __IO uint32_t iosb1                : 1; /* [1] */
      __IO uint32_t iosb2                : 1; /* [2] */
      __IO uint32_t iosb3                : 1; /* [3] */
      __IO uint32_t iosb4                : 1; /* [4] */
      __IO uint32_t iosb5                : 1; /* [5] */
      __IO uint32_t iosb6                : 1; /* [6] */
      __IO uint32_t iosb7                : 1; /* [7] */
      __IO uint32_t iosb8                : 1; /* [8] */
      __IO uint32_t iosb9                : 1; /* [9] */
      __IO uint32_t iosb10               : 1; /* [10] */
      __IO uint32_t iosb11               : 1; /* [11] */
      __IO uint32_t iosb12               : 1; /* [12] */
      __IO uint32_t iosb13               : 1; /* [13] */
      __IO uint32_t iosb14               : 1; /* [14] */
      __IO uint32_t iosb15               : 1; /* [15] */
      __IO uint32_t iocb0                : 1; /* [16] */
      __IO uint32_t iocb1                : 1; /* [17] */
      __IO uint32_t iocb2                : 1; /* [18] */
      __IO uint32_t iocb3                : 1; /* [19] */
      __IO uint32_t iocb4                : 1; /* [20] */
      __IO uint32_t iocb5                : 1; /* [21] */
      __IO uint32_t iocb6                : 1; /* [22] */
      __IO uint32_t iocb7                : 1; /* [23] */
      __IO uint32_t iocb8                : 1; /* [24] */
      __IO uint32_t iocb9                : 1; /* [25] */
      __IO uint32_t iocb10               : 1; /* [26] */
      __IO uint32_t iocb11               : 1; /* [27] */
      __IO uint32_t iocb12               : 1; /* [28] */
      __IO uint32_t iocb13               : 1; /* [29] */
      __IO uint32_t iocb14               : 1; /* [30] */
      __IO uint32_t iocb15               : 1; /* [31] */
    } scr_bit;
  };

  /**
    * @brief gpio clr register, offset:0x14
    */
  union
  {
    __IO uint32_t clr;
    struct
    {
      __IO uint32_t iocb0                : 1; /* [0] */
      __IO uint32_t iocb1                : 1; /* [1] */
      __IO uint32_t iocb2                : 1; /* [2] */
      __IO uint32_t iocb3                : 1; /* [3] */
      __IO uint32_t iocb4                : 1; /* [4] */
      __IO uint32_t iocb5                : 1; /* [5] */
      __IO uint32_t iocb6                : 1; /* [6] */
      __IO uint32_t iocb7                : 1; /* [7] */
      __IO uint32_t iocb8                : 1; /* [8] */
      __IO uint32_t iocb9                : 1; /* [9] */
      __IO uint32_t iocb10               : 1; /* [10] */
      __IO uint32_t iocb11               : 1; /* [11] */
      __IO uint32_t iocb12               : 1; /* [12] */
      __IO uint32_t iocb13               : 1; /* [13] */
      __IO uint32_t iocb14               : 1; /* [14] */
      __IO uint32_t iocb15               : 1; /* [15] */
      __IO uint32_t reserved1            : 16;/* [31:16] */
    } clr_bit;
  };

  /**
    * @brief gpio wpr register, offset:0x18
    */
  union
  {
    __IO uint32_t wpr;
    struct
    {
      __IO uint32_t wpen0                : 1; /* [0] */
      __IO uint32_t wpen1                : 1; /* [1] */
      __IO uint32_t wpen2                : 1; /* [2] */
      __IO uint32_t wpen3                : 1; /* [3] */
      __IO uint32_t wpen4                : 1; /* [4] */
      __IO uint32_t wpen5                : 1; /* [5] */
      __IO uint32_t wpen6                : 1; /* [6] */
      __IO uint32_t wpen7                : 1; /* [7] */
      __IO uint32_t wpen8                : 1; /* [8] */
      __IO uint32_t wpen9                : 1; /* [9] */
      __IO uint32_t wpen10               : 1; /* [10] */
      __IO uint32_t wpen11               : 1; /* [11] */
      __IO uint32_t wpen12               : 1; /* [12] */
      __IO uint32_t wpen13               : 1; /* [13] */
      __IO uint32_t wpen14               : 1; /* [14] */
      __IO uint32_t wpen15               : 1; /* [15] */
      __IO uint32_t wpseq                : 1; /* [16] */
      __IO uint32_t reserved1            : 15;/* [31:17] */
    } wpr_bit;
  };

} gpio_type;

/**
  * @brief type define iomux register all
  */
typedef struct
{
  /**
    * @brief mux event control register, offset:0x00
    */
  union
  {
    __IO uint32_t evtout;
    struct
    {
      __IO uint32_t selpin               : 4; /* [3:0] */
      __IO uint32_t selport              : 3; /* [6:4] */
      __IO uint32_t evoen                : 1; /* [7]   */
      __IO uint32_t reserved1            : 24;/* [31:8] */
    } evtout_bit;
  };

  /**
    * @brief iomux remap register, offset:0x04
    */
  union
  {
    __IO uint32_t remap;
    struct
    {
      __IO uint32_t spi1_mux_l           : 1; /* [0] */
      __IO uint32_t i2c1_mux             : 1; /* [1] */
      __IO uint32_t usart1_mux           : 1; /* [2] */
      __IO uint32_t reserved1            : 1; /* [3] */
      __IO uint32_t usart3_mux           : 2; /* [5:4] */
      __IO uint32_t tmr1_mux             : 2; /* [7:6] */
      __IO uint32_t tmr2_mux             : 2; /* [9:8] */
      __IO uint32_t tmr3_mux             : 2; /* [11:10] */
      __IO uint32_t reserved2            : 1; /* [12] */
      __IO uint32_t can_mux              : 2; /* [14:13] */
      __IO uint32_t pd01_mux             : 1; /* [15] */
      __IO uint32_t tmr5ch4_mux          : 1; /* [16] */
      __IO uint32_t adc1_extrgpre_mux    : 1; /* [17] */
      __IO uint32_t adc1_extrgord_mux    : 1; /* [18] */
      __IO uint32_t reserved3            : 5; /* [23:19] */
      __IO uint32_t swjtag_conf          : 3; /* [26:24] */
      __IO uint32_t reserved4            : 4; /* [30:27] */
      __IO uint32_t spi1_mux_h           : 1; /* [31] */
    } remap_bit;
  };

  /**
    * @brief mux external interrupt configuration register 1, offset:0x08
    */
  union
  {
    __IO uint32_t exintc1;
    struct
    {
      __IO uint32_t exint0              : 4; /* [3:0] */
      __IO uint32_t exint1              : 4; /* [7:4] */
      __IO uint32_t exint2              : 4; /* [11:8] */
      __IO uint32_t exint3              : 4; /* [15:12] */
      __IO uint32_t reserved1           : 16;/* [31:16] */
    } exintc1_bit;
  };

  /**
    * @brief mux external interrupt configuration register 2, offset:0x0c
    */
  union
  {
    __IO uint32_t exintc2;
    struct
    {
      __IO uint32_t exint4              : 4; /* [3:0] */
      __IO uint32_t exint5              : 4; /* [7:4] */
      __IO uint32_t exint6              : 4; /* [11:8] */
      __IO uint32_t exint7              : 4; /* [15:12] */
      __IO uint32_t reserved1           : 16;/* [31:16] */
    } exintc2_bit;
  };

  /**
    * @brief mux external interrupt configuration register 3, offset:0x10
    */
  union
  {
    __IO uint32_t exintc3;
    struct
    {
      __IO uint32_t exint8              : 4; /* [3:0] */
      __IO uint32_t exint9              : 4; /* [7:4] */
      __IO uint32_t exint10             : 4; /* [11:8] */
      __IO uint32_t exint11             : 4; /* [15:12] */
      __IO uint32_t reserved1           : 16;/* [31:16] */
    } exintc3_bit;
  };

  /**
    * @brief mux external interrupt configuration register 4, offset:0x14
    */
  union
  {
    __IO uint32_t exintc4;
    struct
    {
      __IO uint32_t exint12             : 4; /* [3:0] */
      __IO uint32_t exint13             : 4; /* [7:4] */
      __IO uint32_t exint14             : 4; /* [11:8] */
      __IO uint32_t exint15             : 4; /* [15:12] */
      __IO uint32_t reserved1           : 16;/* [31:16] */
    } exintc4_bit;
  };

  /**
    * @brief iomux reserved1 register, offset:0x18
    */
  __IO uint32_t reserved1;

  /**
    * @brief iomux remap register 2, offset:0x1C
    */
  union
  {
    __IO uint32_t remap2;
    struct
    {
      __IO uint32_t reserved1            : 26;/* [25:0] */
      __IO uint32_t cmp_mux              : 2; /* [27:26] */
      __IO uint32_t reserved2            : 4; /* [31:28] */
    } remap2_bit;
  };

  /**
    * @brief iomux remap register 3, offset:0x20
    */
  union
  {
    __IO uint32_t remap3;
    struct
    {
      __IO uint32_t tmr9_gmux            : 4; /* [3:0] */
      __IO uint32_t tmr10_gmux           : 4; /* [7:4] */
      __IO uint32_t tmr11_gmux           : 4; /* [11:8] */
      __IO uint32_t reserved1            : 20;/* [31:12] */
    } remap3_bit;
  };

  /**
    * @brief iomux remap register 4, offset:0x24
    */
  union
  {
    __IO uint32_t remap4;
    struct
    {
      __IO uint32_t tmr1_gmux            : 4; /* [3:0] */
      __IO uint32_t tmr2_gmux            : 3; /* [6:4] */
      __IO uint32_t reserved1            : 1; /* [7] */
      __IO uint32_t tmr3_gmux            : 4; /* [11:8] */
      __IO uint32_t reserved2            : 4; /* [15:12] */
      __IO uint32_t tmr5_gmux            : 3; /* [18:16] */
      __IO uint32_t tmr5ch4_gmux         : 1; /* [19] */
      __IO uint32_t reserved3            : 12;/* [31:20] */
    } remap4_bit;
  };

  /**
    * @brief iomux remap register 5, offset:0x28
    */
  union
  {
    __IO uint32_t remap5;
    struct
    {
      __IO uint32_t reserved1            : 4; /* [3:0] */
      __IO uint32_t i2c1_gmux            : 4; /* [7:4] */
      __IO uint32_t i2c2_gmux            : 4; /* [11:8] */
      __IO uint32_t reserved2            : 4; /* [15:12] */
      __IO uint32_t spi1_gmux            : 4; /* [19:16] */
      __IO uint32_t spi2_gmux            : 4; /* [23:20] */
      __IO uint32_t reserved3            : 8; /* [31:24] */
    } remap5_bit;
  };

  /**
    * @brief iomux remap register 6, offset:0x2C
    */
  union
  {
    __IO uint32_t remap6;
    struct
    {
      __IO uint32_t can1_gmux            : 4; /* [3:0] */
      __IO uint32_t reserved1            : 4; /* [7:4] */
      __IO uint32_t sdio1_gmux           : 4; /* [11:8] */
      __IO uint32_t reserved2            : 4; /* [15:12] */
      __IO uint32_t usart1_gmux          : 4; /* [19:16] */
      __IO uint32_t reserved3            : 4; /* [23:20] */
      __IO uint32_t usart3_gmux          : 4; /* [27:24] */
      __IO uint32_t uart4_gmux           : 4; /* [31:28] */
    } remap6_bit;
  };

  /**
    * @brief iomux remap register 7, offset:0x30
    */
  union
  {
    __IO uint32_t remap7;
    struct
    {
      __IO uint32_t reserved1            : 4; /* [3:0] */
      __IO uint32_t adc1_etp_gmux        : 1; /* [4] */
      __IO uint32_t adc1_eto_gmux        : 1; /* [5] */
      __IO uint32_t reserved2            : 10;/* [15:6] */
      __IO uint32_t swjtag_gmux          : 3; /* [18:16] */
      __IO uint32_t reserved3            : 1; /* [19] */
      __IO uint32_t pd01_gmux            : 1; /* [20] */
      __IO uint32_t reserved4            : 11;/* [31:21] */
    } remap7_bit;
  };

  /**
    * @brief iomux remap register 8, offset:0x34
    */
  union
  {
    __IO uint32_t remap8;
    struct
    {
      __IO uint32_t tmr1_bk1_cmp_gmux    : 2; /* [1:0] */
      __IO uint32_t tmr1_ch1_cmp_gmux    : 2; /* [3:2] */
      __IO uint32_t tmr2_ch4_cmp_gmux    : 2; /* [5:4] */
      __IO uint32_t tmr3_ch1_cmp_gmux    : 2; /* [7:6] */
      __IO uint32_t reserved1            : 24;/* [31:8] */
    } remap8_bit;
  };
} iomux_type;

/**
  * @}
  */

#define GPIOA                            ((gpio_type *) GPIOA_BASE)
#define GPIOB                            ((gpio_type *) GPIOB_BASE)
#define GPIOC                            ((gpio_type *) GPIOC_BASE)
#define GPIOD                            ((gpio_type *) GPIOD_BASE)
#define GPIOF                            ((gpio_type *) GPIOF_BASE)
#define IOMUX                            ((iomux_type *) IOMUX_BASE)

/** @defgroup GPIO_exported_functions
  * @{
  */

void gpio_reset(gpio_type *gpio_x);
void gpio_iomux_reset(void);
void gpio_init(gpio_type *gpio_x, gpio_init_type *gpio_init_struct);
void gpio_default_para_init(gpio_init_type *gpio_init_struct);
flag_status gpio_input_data_bit_read(gpio_type *gpio_x, uint16_t pins);
uint16_t gpio_input_data_read(gpio_type *gpio_x);
flag_status gpio_output_data_bit_read(gpio_type *gpio_x, uint16_t pins);
uint16_t gpio_output_data_read(gpio_type *gpio_x);
void gpio_bits_set(gpio_type *gpio_x, uint16_t pins);
void gpio_bits_reset(gpio_type *gpio_x, uint16_t pins);
void gpio_bits_write(gpio_type *gpio_x, uint16_t pins, confirm_state bit_state);
void gpio_port_write(gpio_type *gpio_x, uint16_t port_value);
void gpio_pin_wp_config(gpio_type *gpio_x, uint16_t pins);
void gpio_event_output_config(gpio_port_source_type gpio_port_source, gpio_pins_source_type gpio_pin_source);
void gpio_event_output_enable(confirm_state new_state);
void gpio_pin_remap_config(uint32_t gpio_remap, confirm_state new_state);
void gpio_exint_line_config(gpio_port_source_type gpio_port_source, gpio_pins_source_type gpio_pin_source);

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
