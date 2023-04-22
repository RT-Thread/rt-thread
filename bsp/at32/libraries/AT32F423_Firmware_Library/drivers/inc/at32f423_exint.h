/**
  **************************************************************************
  * @file     at32f423_exint.h
  * @brief    at32f423 exint header file
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
#ifndef __AT32F423_EXINT_H
#define __AT32F423_EXINT_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f423.h"

/** @addtogroup AT32F423_periph_driver
  * @{
  */

/** @addtogroup EXINT
  * @{
  */

/** @defgroup EXINT_lines
  * @{
  */

#define EXINT_LINE_NONE                  ((uint32_t)0x00000000)
#define EXINT_LINE_0                     ((uint32_t)0x00000001) /*!< external interrupt line 0 */
#define EXINT_LINE_1                     ((uint32_t)0x00000002) /*!< external interrupt line 1 */
#define EXINT_LINE_2                     ((uint32_t)0x00000004) /*!< external interrupt line 2 */
#define EXINT_LINE_3                     ((uint32_t)0x00000008) /*!< external interrupt line 3 */
#define EXINT_LINE_4                     ((uint32_t)0x00000010) /*!< external interrupt line 4 */
#define EXINT_LINE_5                     ((uint32_t)0x00000020) /*!< external interrupt line 5 */
#define EXINT_LINE_6                     ((uint32_t)0x00000040) /*!< external interrupt line 6 */
#define EXINT_LINE_7                     ((uint32_t)0x00000080) /*!< external interrupt line 7 */
#define EXINT_LINE_8                     ((uint32_t)0x00000100) /*!< external interrupt line 8 */
#define EXINT_LINE_9                     ((uint32_t)0x00000200) /*!< external interrupt line 9 */
#define EXINT_LINE_10                    ((uint32_t)0x00000400) /*!< external interrupt line 10 */
#define EXINT_LINE_11                    ((uint32_t)0x00000800) /*!< external interrupt line 11 */
#define EXINT_LINE_12                    ((uint32_t)0x00001000) /*!< external interrupt line 12 */
#define EXINT_LINE_13                    ((uint32_t)0x00002000) /*!< external interrupt line 13 */
#define EXINT_LINE_14                    ((uint32_t)0x00004000) /*!< external interrupt line 14 */
#define EXINT_LINE_15                    ((uint32_t)0x00008000) /*!< external interrupt line 15 */
#define EXINT_LINE_16                    ((uint32_t)0x00010000) /*!< external interrupt line 16 */
#define EXINT_LINE_17                    ((uint32_t)0x00020000) /*!< external interrupt line 17 */
#define EXINT_LINE_18                    ((uint32_t)0x00040000) /*!< external interrupt line 18 */
#define EXINT_LINE_21                    ((uint32_t)0x00200000) /*!< external interrupt line 21 */
#define EXINT_LINE_22                    ((uint32_t)0x00400000) /*!< external interrupt line 22 */
#define EXINT_LINE_23                    ((uint32_t)0x00800000) /*!< external interrupt line 23 */
#define EXINT_LINE_25                    ((uint32_t)0x02000000) /*!< external interrupt line 25 */
#define EXINT_LINE_26                    ((uint32_t)0x04000000) /*!< external interrupt line 26 */
#define EXINT_LINE_28                    ((uint32_t)0x10000000) /*!< external interrupt line 28 */
/**
  * @}
  */

/** @defgroup EXINT_exported_types
  * @{
  */

/**
  * @brief exint line mode type
  */
typedef enum
{
  EXINT_LINE_INTERRUPUT                  = 0x00, /*!< external interrupt line interrupt mode */
  EXINT_LINE_EVENT                       = 0x01  /*!< external interrupt line event mode */
} exint_line_mode_type;

/**
  * @brief exint polarity configuration type
  */
typedef enum
{
  EXINT_TRIGGER_RISING_EDGE              = 0x00, /*!< external interrupt line rising trigger mode */
  EXINT_TRIGGER_FALLING_EDGE             = 0x01, /*!< external interrupt line falling trigger mode */
  EXINT_TRIGGER_BOTH_EDGE                = 0x02  /*!< external interrupt line both rising and falling trigger mode */
} exint_polarity_config_type;

/**
  * @brief exint init type
  */
typedef struct
{
  exint_line_mode_type                   line_mode;     /*!< choose mode event or interrupt mode */
  uint32_t                               line_select;   /*!< select the exint line, availiable for single line or multiple lines */
  exint_polarity_config_type             line_polarity; /*!< select the tregger polarity, with rising edge, falling edge or both edge */
  confirm_state                          line_enable;   /*!< enable or disable exint */
} exint_init_type;

/**
  * @brief type define exint register all
  */
typedef struct
{

  /**
    * @brief exint inten register, offset:0x00
    */
  union
  {
    __IO uint32_t inten;
    struct
    {
      __IO uint32_t intenx               : 29;/* [28:0] */
      __IO uint32_t reserved1            : 3; /* [31:29] */
    } inten_bit;
  };

  /**
    * @brief exint evten register, offset:0x04
    */
  union
  {
    __IO uint32_t evten;
    struct
    {
      __IO uint32_t evtenx               : 29;/* [28:0] */
      __IO uint32_t reserved1            : 3; /* [31:29] */
    } evten_bit;
  };

  /**
    * @brief exint polcfg1 register, offset:0x08
    */
  union
  {
    __IO uint32_t polcfg1;
    struct
    {
      __IO uint32_t rpx                  : 29;/* [28:0] */
      __IO uint32_t reserved1            : 3; /* [31:29] */
    } polcfg1_bit;
  };

  /**
    * @brief exint polcfg2 register, offset:0x0C
    */
  union
  {
    __IO uint32_t polcfg2;
    struct
    {
      __IO uint32_t fpx                  : 29;/* [28:0] */
      __IO uint32_t reserved1            : 3; /* [31:29] */
    } polcfg2_bit;
  };

  /**
    * @brief exint swtrg register, offset:0x10
    */
  union
  {
    __IO uint32_t swtrg;
    struct
    {
      __IO uint32_t swtx                 : 29;/* [28:0] */
      __IO uint32_t reserved1            : 3; /* [31:29] */
    } swtrg_bit;
  };

  /**
    * @brief exint intsts register, offset:0x14
    */
  union
  {
    __IO uint32_t intsts;
    struct
    {
      __IO uint32_t linex                : 29;/* [28:0] */
      __IO uint32_t reserved1            : 3; /* [31:29] */
    } intsts_bit;
  };
} exint_type;

/**
  * @}
  */

#define EXINT                             ((exint_type *) EXINT_BASE)

/** @defgroup EXINT_exported_functions
  * @{
  */

void exint_reset(void);
void exint_default_para_init(exint_init_type *exint_struct);
void exint_init(exint_init_type *exint_struct);
void exint_flag_clear(uint32_t exint_line);
flag_status exint_flag_get(uint32_t exint_line);
void exint_software_interrupt_event_generate(uint32_t exint_line);
void exint_interrupt_enable(uint32_t exint_line, confirm_state new_state);
void exint_event_enable(uint32_t exint_line, confirm_state new_state);

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
