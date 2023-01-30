/**
  **************************************************************************
  * @file     at32f421_debug.h
  * @brief    at32f421 debug header file
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F421_DEBUG_H
#define __AT32F421_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f421.h"

/** @addtogroup AT32F421_periph_driver
  * @{
  */

/** @addtogroup DEBUG
  * @{
  */

/** @defgroup DEBUG_mode_definition
  * @{
  */

#define DEBUG_SLEEP                      0x00000001 /*!< debug sleep mode */
#define DEBUG_DEEPSLEEP                  0x00000002 /*!< debug deepsleep mode */
#define DEBUG_STANDBY                    0x00000004 /*!< debug standby mode */
#define DEBUG_WDT_PAUSE                  0x00000100 /*!< debug watchdog timer pause */
#define DEBUG_WWDT_PAUSE                 0x00000200 /*!< debug window watchdog timer pause */
#define DEBUG_TMR1_PAUSE                 0x00000400 /*!< debug timer1 pause */
#define DEBUG_TMR3_PAUSE                 0x00001000 /*!< debug timer3 pause */
#define DEBUG_ERTC_PAUSE                 0x00004000 /*!< debug ertc pause */
#define DEBUG_I2C1_SMBUS_TIMEOUT         0x00008000 /*!< debug i2c1 smbus timeout */
#define DEBUG_I2C2_SMBUS_TIMEOUT         0x00010000 /*!< debug i2c2 smbus timeout */
#define DEBUG_TMR6_PAUSE                 0x00080000 /*!< debug timer6 pause */
#define DEBUG_ERTC_512_PAUSE             0x00200000 /*!< debug ertc 512 pause */
#define DEBUG_TMR15_PAUSE                0x00400000 /*!< debug timer15 pause */
#define DEBUG_TMR16_PAUSE                0x00800000 /*!< debug timer16 pause */
#define DEBUG_TMR17_PAUSE                0x01000000 /*!< debug timer17 pause */
#define DEBUG_TMR14_PAUSE                0x08000000 /*!< debug timer14 pause */

/**
  * @}
  */

/** @defgroup DEBUG_exported_types
  * @{
  */

/**
  * @brief type define debug register all
  */
typedef struct
{
  /**
    * @brief debug idcode register, offset:0x00
    */
  union
  {
    __IO uint32_t pid;
    struct
    {
      __IO uint32_t pid                  : 32;/* [31:0] */
    } idcode_bit;
  };

  /**
    * @brief debug ctrl register, offset:0x04
    */
  union
  {
    __IO uint32_t ctrl;
    struct
    {
      __IO uint32_t sleep_debug          : 1;/* [0] */
      __IO uint32_t deepsleep_debug      : 1;/* [1] */
      __IO uint32_t standby_debug        : 1;/* [2] */
      __IO uint32_t reserved1            : 5;/* [7:3] */
      __IO uint32_t wdt_pause            : 1;/* [8] */
      __IO uint32_t wwdt_pause           : 1;/* [9] */
      __IO uint32_t tmr1_pause           : 1;/* [10] */
      __IO uint32_t reserved2            : 1;/* [11] */
      __IO uint32_t tmr3_pause           : 1;/* [12] */
      __IO uint32_t reserved3            : 1;/* [13] */
      __IO uint32_t ertc_pause           : 1;/* [14] */
      __IO uint32_t i2c1_smbus_timeout   : 1;/* [15] */
      __IO uint32_t i2c2_smbus_timeout   : 1;/* [16] */
      __IO uint32_t reserved4            : 2;/* [18:17] */
      __IO uint32_t tmr6_pause           : 1;/* [19] */
      __IO uint32_t reserved5            : 1;/* [20] */
      __IO uint32_t ertc_512_pause       : 1;/* [21] */
      __IO uint32_t tmr15_pause          : 1;/* [22] */
      __IO uint32_t tmr16_pause          : 1;/* [23] */
      __IO uint32_t tmr17_pause          : 1;/* [24] */
      __IO uint32_t reserved6            : 2;/* [26:25] */
      __IO uint32_t tmr14_pause          : 1;/* [27] */
      __IO uint32_t reserved7            : 4;/* [31:28] */
    } ctrl_bit;
  };

} debug_type;

/**
  * @}
  */

#define DEBUGMCU                         ((debug_type *) DEBUG_BASE)

/** @defgroup DEBUG_exported_functions
  * @{
  */

uint16_t debug_device_id_get(void);
void debug_periph_mode_set(uint32_t periph_debug_mode, confirm_state new_state);

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
