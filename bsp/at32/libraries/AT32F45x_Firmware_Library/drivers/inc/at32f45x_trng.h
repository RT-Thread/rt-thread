/**
  **************************************************************************
  * @file     at32f45x_trng.h
  * @brief    at32f45x trng header file
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
#ifndef __AT32F45x_TRNG_H
#define __AT32F45x_TRNG_H

#ifdef __cplusplus
extern "C" {
#endif


/* includes ------------------------------------------------------------------*/
#include "at32f45x.h"

/** @addtogroup AT32F45x_periph_driver
  * @{
  */

/** @addtogroup TRNG
  * @{
  */

/** @defgroup TRNG_flags_definition
  * @brief trng flag
  * @{
  */
#define TRNG_DTRDY_FLAG                  ((uint32_t)0x00000001) /*!< data ready flag */
#define TRNG_CKFES_FLAG                  ((uint32_t)0x00000002) /*!< clock fail event flag */
#define TRNG_ESFES_FLAG                  ((uint32_t)0x00000004) /*!< entropy fail event flag */
#define TRNG_CEFIS_FLAG                  ((uint32_t)0x00000020) /*!< clock fail interrupt flag */
#define TRNG_ESFIS_FLAG                  ((uint32_t)0x00000040) /*!< entropy fail interrupt flag */

/**
  * @}
  */

/** @defgroup TRNG_interrupts_definition
  * @brief trng interrupt
  * @{
  */

#define TRNG_FIE_INT                     ((uint32_t)0x00000008) /*!< trng fail interrupt */
#define TRNG_DTRIE_INT                   ((uint32_t)0x00000010) /*!< trng data port ready interrupt */

/**
  * @}
  */

/** @defgroup TRNG_exported_types
  * @{
  */

/**
  * @brief type define trng register all
  */
typedef struct
{
  /**
    * @brief trng ctrl register, offset:0x00
    */
  union
  {
    __IO uint32_t ctrl;
    struct
    {
      __IO uint32_t reserved1            : 2; /* [1:0] */
      __IO uint32_t nsen                 : 1; /* [2] */
      __IO uint32_t fie                  : 1; /* [3] */
      __IO uint32_t dtrie                : 1; /* [4] */
      __IO uint32_t reserved2            : 11;/* [15:5] */
      __IO uint32_t clkdiv               : 4; /* [19:16] */
      __IO uint32_t ht0                  : 2; /* [21:20] */
      __IO uint32_t reserved3            : 7; /* [28:22] */
      __IO uint32_t fesclr               : 1; /* [29] */
      __IO uint32_t cudis                : 1; /* [30] */
      __IO uint32_t prglk                : 1; /* [31] */
    } ctrl_bit;
  };

  /**
    * @brief trng sts register, offset:0x04
    */
  union
  {
    __IO uint32_t sts;
    struct
    {
      __IO uint32_t dtrdy                : 1; /* [0] */
      __IO uint32_t ckfes                : 1; /* [1] */
      __IO uint32_t esfes                : 1; /* [2] */
      __IO uint32_t reserved1            : 2; /* [4:3] */
      __IO uint32_t ckfis                : 1; /* [5] */
      __IO uint32_t esfis                : 1; /* [6] */
      __IO uint32_t reserved2            : 25;/* [31:7] */
    } sts_bit;
  };

  /**
    * @brief trng dt register, offset:0x08
    */
  union
  {
    __IO uint32_t dt;
    struct
    {
      __IO uint32_t dt                   : 32;/* [31:0] */
    } dt_bit;
  };

  /**
    * @brief trng htctrl register, offset:0x0C
    */
  union
  {
    __IO uint32_t htctrl;
    struct
    {
      __IO uint32_t ht1                  : 20;/* [19:0] */
      __IO uint32_t reserved             : 12;/* [31:20] */
    } htctrl_bit;
  };
} trng_type;

/**
  * @}
  */

#define TRNG                             ((trng_type *) TRNG_BASE)

/** @defgroup TRNG_exported_functions
  * @{
  */

void trng_reset(void);
void trng_enable(confirm_state new_state);
void trng_interrupt_enable(uint32_t trng_int, confirm_state new_state);
void trng_clock_divider_set(uint8_t factor);
void trng_conditioning_and_buffer_enable(confirm_state new_state);
void trng_programing_register_lock(void);
uint32_t trng_value_get(void);
flag_status trng_flag_get(uint32_t flag);
flag_status trng_interrupt_flag_get(uint32_t flag);
void trng_flag_clear(uint32_t flag);

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
