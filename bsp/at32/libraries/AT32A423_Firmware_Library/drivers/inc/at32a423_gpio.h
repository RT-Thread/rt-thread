/**
  **************************************************************************
  * @file     at32a423_gpio.h
  * @brief    at32a423 gpio header file
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
#ifndef __AT32A423_GPIO_H
#define __AT32A423_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif


/* includes ------------------------------------------------------------------*/
#include "at32a423.h"

/** @addtogroup AT32A423_periph_driver
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

/** @defgroup GPIO_exported_types
  * @{
  */

/**
  * @brief gpio mode select
  */
typedef enum
{
  GPIO_MODE_INPUT                        = 0x00, /*!< gpio input mode */
  GPIO_MODE_OUTPUT                       = 0x01, /*!< gpio output mode */
  GPIO_MODE_MUX                          = 0x02, /*!< gpio mux function mode */
  GPIO_MODE_ANALOG                       = 0x03  /*!< gpio analog in/out mode */
} gpio_mode_type;

/**
  * @brief gpio output drive strength select
  */
typedef enum
{
  GPIO_DRIVE_STRENGTH_STRONGER           = 0x01, /*!< stronger sourcing/sinking strength */
  GPIO_DRIVE_STRENGTH_MODERATE           = 0x02  /*!< moderate sourcing/sinking strength */
} gpio_drive_type;

/**
  * @brief gpio output type
  */
typedef enum
{
  GPIO_OUTPUT_PUSH_PULL                  = 0x00, /*!< output push-pull */
  GPIO_OUTPUT_OPEN_DRAIN                 = 0x01  /*!< output open-drain */
} gpio_output_type;

/**
  * @brief gpio pull type
  */
typedef enum
{
  GPIO_PULL_NONE                         = 0x00, /*!< floating for input, no pull for output */
  GPIO_PULL_UP                           = 0x01, /*!< pull-up */
  GPIO_PULL_DOWN                         = 0x02  /*!< pull-down */
} gpio_pull_type;

/**
  * @brief gpio init type
  */
typedef struct
{
  uint32_t                               gpio_pins;            /*!< pins number selection */
  gpio_output_type                       gpio_out_type;        /*!< output type selection */
  gpio_pull_type                         gpio_pull;            /*!< pull type selection */
  gpio_mode_type                         gpio_mode;            /*!< mode selection */
  gpio_drive_type                        gpio_drive_strength;  /*!< drive strength selection */
} gpio_init_type;

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
  * @brief  gpio muxing function selection type
  */
typedef enum
{
  GPIO_MUX_0                             = 0x00, /*!< gpio muxing function selection 0 */
  GPIO_MUX_1                             = 0x01, /*!< gpio muxing function selection 1 */
  GPIO_MUX_2                             = 0x02, /*!< gpio muxing function selection 2 */
  GPIO_MUX_3                             = 0x03, /*!< gpio muxing function selection 3 */
  GPIO_MUX_4                             = 0x04, /*!< gpio muxing function selection 4 */
  GPIO_MUX_5                             = 0x05, /*!< gpio muxing function selection 5 */
  GPIO_MUX_6                             = 0x06, /*!< gpio muxing function selection 6 */
  GPIO_MUX_7                             = 0x07, /*!< gpio muxing function selection 7 */
  GPIO_MUX_8                             = 0x08, /*!< gpio muxing function selection 8 */
  GPIO_MUX_9                             = 0x09, /*!< gpio muxing function selection 9 */
  GPIO_MUX_10                            = 0x0A, /*!< gpio muxing function selection 10 */
  GPIO_MUX_11                            = 0x0B, /*!< gpio muxing function selection 11 */
  GPIO_MUX_12                            = 0x0C, /*!< gpio muxing function selection 12 */
  GPIO_MUX_13                            = 0x0D, /*!< gpio muxing function selection 13 */
  GPIO_MUX_14                            = 0x0E, /*!< gpio muxing function selection 14 */
  GPIO_MUX_15                            = 0x0F  /*!< gpio muxing function selection 15 */
} gpio_mux_sel_type;

/**
  * @brief type define gpio register all
  */
typedef struct
{
  /**
    * @brief gpio mode register, offset:0x00
    */
  union
  {
    __IO uint32_t cfgr;
    struct
    {
      __IO uint32_t iomc0                : 2; /* [1:0] */
      __IO uint32_t iomc1                : 2; /* [3:2] */
      __IO uint32_t iomc2                : 2; /* [5:4] */
      __IO uint32_t iomc3                : 2; /* [7:6] */
      __IO uint32_t iomc4                : 2; /* [9:8] */
      __IO uint32_t iomc5                : 2; /* [11:10] */
      __IO uint32_t iomc6                : 2; /* [13:12] */
      __IO uint32_t iomc7                : 2; /* [15:14] */
      __IO uint32_t iomc8                : 2; /* [17:16] */
      __IO uint32_t iomc9                : 2; /* [19:18] */
      __IO uint32_t iomc10               : 2; /* [21:20] */
      __IO uint32_t iomc11               : 2; /* [23:22] */
      __IO uint32_t iomc12               : 2; /* [25:24] */
      __IO uint32_t iomc13               : 2; /* [27:26] */
      __IO uint32_t iomc14               : 2; /* [29:28] */
      __IO uint32_t iomc15               : 2; /* [31:30] */
    } cfgr_bit;
  };

  /**
    * @brief gpio output type register, offset:0x04
    */
  union
  {
    __IO uint32_t omode;
    struct
    {
      __IO uint32_t om0                  : 1; /* [0] */
      __IO uint32_t om1                  : 1; /* [1] */
      __IO uint32_t om2                  : 1; /* [2] */
      __IO uint32_t om3                  : 1; /* [3] */
      __IO uint32_t om4                  : 1; /* [4] */
      __IO uint32_t om5                  : 1; /* [5] */
      __IO uint32_t om6                  : 1; /* [6] */
      __IO uint32_t om7                  : 1; /* [7] */
      __IO uint32_t om8                  : 1; /* [8] */
      __IO uint32_t om9                  : 1; /* [9] */
      __IO uint32_t om10                 : 1; /* [10] */
      __IO uint32_t om11                 : 1; /* [11] */
      __IO uint32_t om12                 : 1; /* [12] */
      __IO uint32_t om13                 : 1; /* [13] */
      __IO uint32_t om14                 : 1; /* [14] */
      __IO uint32_t om15                 : 1; /* [15] */
      __IO uint32_t reserved1            : 16;/* [31:16] */
    } omode_bit;
  };

  /**
    * @brief gpio output driver register, offset:0x08
    */
  union
  {
    __IO uint32_t odrvr;
    struct
    {
      __IO uint32_t odrv0                : 2; /* [1:0] */
      __IO uint32_t odrv1                : 2; /* [3:2] */
      __IO uint32_t odrv2                : 2; /* [5:4] */
      __IO uint32_t odrv3                : 2; /* [7:6] */
      __IO uint32_t odrv4                : 2; /* [9:8] */
      __IO uint32_t odrv5                : 2; /* [11:10] */
      __IO uint32_t odrv6                : 2; /* [13:12] */
      __IO uint32_t odrv7                : 2; /* [15:14] */
      __IO uint32_t odrv8                : 2; /* [17:16] */
      __IO uint32_t odrv9                : 2; /* [19:18] */
      __IO uint32_t odrv10               : 2; /* [21:20] */
      __IO uint32_t odrv11               : 2; /* [23:22] */
      __IO uint32_t odrv12               : 2; /* [25:24] */
      __IO uint32_t odrv13               : 2; /* [27:26] */
      __IO uint32_t odrv14               : 2; /* [29:28] */
      __IO uint32_t odrv15               : 2; /* [31:30] */
    } odrvr_bit;
  };

  /**
    * @brief gpio pull up/down register, offset:0x0C
    */
  union
  {
    __IO uint32_t pull;
    struct
    {
      __IO uint32_t pull0                : 2; /* [1:0] */
      __IO uint32_t pull1                : 2; /* [3:2] */
      __IO uint32_t pull2                : 2; /* [5:4] */
      __IO uint32_t pull3                : 2; /* [7:6] */
      __IO uint32_t pull4                : 2; /* [9:8] */
      __IO uint32_t pull5                : 2; /* [11:10] */
      __IO uint32_t pull6                : 2; /* [13:12] */
      __IO uint32_t pull7                : 2; /* [15:14] */
      __IO uint32_t pull8                : 2; /* [17:16] */
      __IO uint32_t pull9                : 2; /* [19:18] */
      __IO uint32_t pull10               : 2; /* [21:20] */
      __IO uint32_t pull11               : 2; /* [23:22] */
      __IO uint32_t pull12               : 2; /* [25:24] */
      __IO uint32_t pull13               : 2; /* [27:26] */
      __IO uint32_t pull14               : 2; /* [29:28] */
      __IO uint32_t pull15               : 2; /* [31:30] */
    } pull_bit;
  };

  /**
    * @brief gpio input data register, offset:0x10
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
    * @brief gpio output data register, offset:0x14
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
    * @brief gpio scr register, offset:0x18
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
    * @brief gpio wpen register, offset:0x1C
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

  /**
    * @brief gpio muxl register, offset:0x20
    */
  union
  {
    __IO uint32_t muxl;
    struct
    {
      __IO uint32_t muxl0                : 4; /* [3:0] */
      __IO uint32_t muxl1                : 4; /* [7:4] */
      __IO uint32_t muxl2                : 4; /* [11:8] */
      __IO uint32_t muxl3                : 4; /* [15:12] */
      __IO uint32_t muxl4                : 4; /* [19:16] */
      __IO uint32_t muxl5                : 4; /* [23:20] */
      __IO uint32_t muxl6                : 4; /* [27:24] */
      __IO uint32_t muxl7                : 4; /* [31:28] */
    } muxl_bit;
  };

  /**
    * @brief gpio muxh register, offset:0x24
    */
  union
  {
    __IO uint32_t muxh;
    struct
    {
      __IO uint32_t muxh8                : 4; /* [3:0] */
      __IO uint32_t muxh9                : 4; /* [7:4] */
      __IO uint32_t muxh10               : 4; /* [11:8] */
      __IO uint32_t muxh11               : 4; /* [15:12] */
      __IO uint32_t muxh12               : 4; /* [19:16] */
      __IO uint32_t muxh13               : 4; /* [23:20] */
      __IO uint32_t muxh14               : 4; /* [27:24] */
      __IO uint32_t muxh15               : 4; /* [31:28] */
    } muxh_bit;
  };

  /**
    * @brief gpio clr register, offset:0x28
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
  * @brief gpio togr register, offset:0x2C
  */
  union
  {
    __IO uint32_t togr;
    struct
    {
      __IO uint32_t iotb0                : 1; /* [0] */
      __IO uint32_t iotb1                : 1; /* [1] */
      __IO uint32_t iotb2                : 1; /* [2] */
      __IO uint32_t iotb3                : 1; /* [3] */
      __IO uint32_t iotb4                : 1; /* [4] */
      __IO uint32_t iotb5                : 1; /* [5] */
      __IO uint32_t iotb6                : 1; /* [6] */
      __IO uint32_t iotb7                : 1; /* [7] */
      __IO uint32_t iotb8                : 1; /* [8] */
      __IO uint32_t iotb9                : 1; /* [9] */
      __IO uint32_t iotb10               : 1; /* [10] */
      __IO uint32_t iotb11               : 1; /* [11] */
      __IO uint32_t iotb12               : 1; /* [12] */
      __IO uint32_t iotb13               : 1; /* [13] */
      __IO uint32_t iotb14               : 1; /* [14] */
      __IO uint32_t iotb15               : 1; /* [15] */
      __IO uint32_t reserved1            : 16;/* [31:16] */
    } togr_bit;
  };


  /**
    * @brief gpio reserved1 register, offset:0x30~0x38
    */
  __IO uint32_t reserved1[3];

  /**
    * @brief gpio hdrv register, offset:0x3C
    */
  union
  {
    __IO uint32_t hdrv;
    struct
    {
      __IO uint32_t hdrv0                : 1; /* [0] */
      __IO uint32_t hdrv1                : 1; /* [1] */
      __IO uint32_t hdrv2                : 1; /* [2] */
      __IO uint32_t hdrv3                : 1; /* [3] */
      __IO uint32_t hdrv4                : 1; /* [4] */
      __IO uint32_t hdrv5                : 1; /* [5] */
      __IO uint32_t hdrv6                : 1; /* [6] */
      __IO uint32_t hdrv7                : 1; /* [7] */
      __IO uint32_t hdrv8                : 1; /* [8] */
      __IO uint32_t hdrv9                : 1; /* [9] */
      __IO uint32_t hdrv10               : 1; /* [10] */
      __IO uint32_t hdrv11               : 1; /* [11] */
      __IO uint32_t hdrv12               : 1; /* [12] */
      __IO uint32_t hdrv13               : 1; /* [13] */
      __IO uint32_t hdrv14               : 1; /* [14] */
      __IO uint32_t hdrv15               : 1; /* [15] */
      __IO uint32_t reserved1            : 16;/* [31:16] */
    } hdrv_bit;
  };

} gpio_type;

/**
  * @}
  */

#define GPIOA                            ((gpio_type *) GPIOA_BASE)
#define GPIOB                            ((gpio_type *) GPIOB_BASE)
#define GPIOC                            ((gpio_type *) GPIOC_BASE)
#define GPIOD                            ((gpio_type *) GPIOD_BASE)
#define GPIOE                            ((gpio_type *) GPIOE_BASE)
#define GPIOF                            ((gpio_type *) GPIOF_BASE)

/** @defgroup GPIO_exported_functions
  * @{
  */

void gpio_reset(gpio_type *gpio_x);
void gpio_init(gpio_type *gpio_x, gpio_init_type *gpio_init_struct);
void gpio_default_para_init(gpio_init_type *gpio_init_struct);
flag_status gpio_input_data_bit_read(gpio_type *gpio_x, uint16_t pins);
uint16_t gpio_input_data_read(gpio_type *gpio_x);
flag_status gpio_output_data_bit_read(gpio_type *gpio_x, uint16_t pins);
uint16_t gpio_output_data_read(gpio_type *gpio_x);
void gpio_bits_set(gpio_type *gpio_x, uint16_t pins);
void gpio_bits_reset(gpio_type *gpio_x, uint16_t pins);
void gpio_bits_toggle(gpio_type *gpio_x, uint16_t pins);
void gpio_bits_write(gpio_type *gpio_x, uint16_t pins, confirm_state bit_state);
void gpio_port_write(gpio_type *gpio_x, uint16_t port_value);
void gpio_pin_wp_config(gpio_type *gpio_x, uint16_t pins);
void gpio_pins_huge_driven_config(gpio_type *gpio_x, uint16_t pins, confirm_state new_state);
void gpio_pin_mux_config(gpio_type *gpio_x, gpio_pins_source_type gpio_pin_source, gpio_mux_sel_type gpio_mux);

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
