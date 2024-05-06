/**
  **************************************************************************
  * @file     at32a423_mcudbg.h
  * @brief    at32a423 mcudbg header file
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
#ifndef __AT32A423_MCUDBG_H
#define __AT32A423_MCUDBG_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32a423.h"

/** @addtogroup AT32A423_periph_driver
  * @{
  */

/** @addtogroup DEBUG
  * @{
  */

/** @defgroup DEBUG_mode_definition
  * @{
  */

/* debug ctrl register bit */
#define DEBUG_SLEEP                      0x00000001 /*!< debug sleep mode */
#define DEBUG_DEEPSLEEP                  0x00000002 /*!< debug deepsleep mode */
#define DEBUG_STANDBY                    0x00000004 /*!< debug standby mode */

/* debug apb1 frz register bit */
#define DEBUG_TMR2_PAUSE                 0x00000001 /*!< debug timer2 pause */
#define DEBUG_TMR3_PAUSE                 0x00000002 /*!< debug timer3 pause */
#define DEBUG_TMR4_PAUSE                 0x00000004 /*!< debug timer4 pause */
#define DEBUG_TMR6_PAUSE                 0x00000010 /*!< debug timer6 pause */
#define DEBUG_TMR7_PAUSE                 0x00000020 /*!< debug timer7 pause */
#define DEBUG_TMR12_PAUSE                0x00000040 /*!< debug timer12 pause */
#define DEBUG_TMR13_PAUSE                0x00000080 /*!< debug timer13 pause */
#define DEBUG_TMR14_PAUSE                0x00000100 /*!< debug timer14 pause */
#define DEBUG_ERTC_PAUSE                 0x00000400 /*!< debug ertc pause */
#define DEBUG_WWDT_PAUSE                 0x00000800 /*!< debug window watchdog timer pause */
#define DEBUG_WDT_PAUSE                  0x00001000 /*!< debug watchdog timer pause */
#define DEBUG_ERTC_512_PAUSE             0x00008000 /*!< debug ertc_512 pause */
#define DEBUG_I2C1_SMBUS_TIMEOUT         0x01000000 /*!< debug i2c1 smbus timeout */
#define DEBUG_I2C2_SMBUS_TIMEOUT         0x08000000 /*!< debug i2c2 smbus timeout */
#define DEBUG_I2C3_SMBUS_TIMEOUT         0x10000000 /*!< debug i2c3 smbus timeout */
#define DEBUG_CAN1_PAUSE                 0x02000000 /*!< debug can1 pause */
#define DEBUG_CAN2_PAUSE                 0x04000000 /*!< debug can2 pause */

/* debug apb2 frz register bit */
#define DEBUG_TMR1_PAUSE                 0x00000001 /*!< debug timer1 pause */
#define DEBUG_TMR9_PAUSE                 0x00010000 /*!< debug timer9 pause */
#define DEBUG_TMR10_PAUSE                0x00020000 /*!< debug timer10 pause */
#define DEBUG_TMR11_PAUSE                0x00040000 /*!< debug timer11 pause */

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
      __IO uint32_t reserved1            : 29;/* [31:3] */
    } ctrl_bit;
  };

  /**
    * @brief debug apb1 frz register, offset:0x08
    */
  union
  {
    __IO uint32_t apb1_frz;
    struct
    {
      __IO uint32_t tmr2_pause           : 1;/* [0] */
      __IO uint32_t tmr3_pause           : 1;/* [1] */
      __IO uint32_t tmr4_pause           : 1;/* [2] */
      __IO uint32_t reserved1            : 1;/* [3] */
      __IO uint32_t tmr6_pause           : 1;/* [4] */
      __IO uint32_t tmr7_pause           : 1;/* [5] */
      __IO uint32_t tmr12_pause          : 1;/* [6] */
      __IO uint32_t tmr13_pause          : 1;/* [7] */
      __IO uint32_t tmr14_pause          : 1;/* [8] */
      __IO uint32_t reserved2            : 1;/* [9] */
      __IO uint32_t ertc_pause           : 1;/* [10] */
      __IO uint32_t wwdt_pause           : 1;/* [11] */
      __IO uint32_t wdt_pause            : 1;/* [12] */
      __IO uint32_t reserved3            : 2;/* [14:13] */
      __IO uint32_t ertc_512_pause       : 1;/* [15] */
      __IO uint32_t reserved4            : 8;/* [23:16] */
      __IO uint32_t i2c1_smbus_timeout   : 1;/* [24] */
      __IO uint32_t can1_pause           : 1;/* [25] */
      __IO uint32_t can2_pause           : 1;/* [26] */
      __IO uint32_t i2c2_smbus_timeout   : 1;/* [27] */
      __IO uint32_t i2c3_smbus_timeout   : 1;/* [28] */
      __IO uint32_t reserved5            : 3;/* [31:29] */
    } apb1_frz_bit;
  };

  /**
    * @brief debug apb2 frz register, offset:0x0C
    */
  union
  {
    __IO uint32_t apb2_frz;
    struct
    {
      __IO uint32_t tmr1_pause           : 1;/* [0] */
      __IO uint32_t reserved1            : 1;/* [1] */
      __IO uint32_t reserved2            : 4;/* [5:2] */
      __IO uint32_t reserved3            : 1;/* [6] */
      __IO uint32_t reserved4            : 9;/* [15:7] */
      __IO uint32_t tmr9_pause           : 1;/* [16] */
      __IO uint32_t tmr10_pause          : 1;/* [17] */
      __IO uint32_t tmr11_pause          : 1;/* [18] */
      __IO uint32_t reserved5            : 13;/* [31:19] */
    } apb2_frz_bit;
  };

  /**
    * @brief debug reserved1 register, offset:0x10~0x1C
    */
  __IO uint32_t reserved1[4];

  /**
    * @brief debug ser id register, offset:0x20
    */
  union
  {
    __IO uint32_t ser_id;
    struct
    {
      __IO uint32_t rev_id               : 3;/* [2:0] */
      __IO uint32_t reserved1            : 5;/* [7:3] */
      __IO uint32_t ser_id               : 8;/* [15:8] */
      __IO uint32_t reserved2            : 16;/* [31:16] */
    } ser_id_bit;
  };

} debug_type;

/**
  * @}
  */

#define DEBUGMCU                         ((debug_type *) DEBUG_BASE)

/** @defgroup DEBUG_exported_functions
  * @{
  */

uint32_t debug_device_id_get(void);
void debug_low_power_mode_set(uint32_t low_power_mode, confirm_state new_state);
void debug_apb1_periph_mode_set(uint32_t apb1_periph, confirm_state new_state);
void debug_apb2_periph_mode_set(uint32_t apb2_periph, confirm_state new_state);

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
