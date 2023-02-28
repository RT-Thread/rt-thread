/**
  **************************************************************************
  * @file     at32f421_cmp.h
  * @brief    at32f421 cmp header file
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
#ifndef __AT32F421_CMP_H
#define __AT32F421_CMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "at32f421.h"

/** @addtogroup AT32F421_periph_driver
  * @{
  */

/** @addtogroup CMP
  * @{
  */

/** @defgroup CMP_exported_types
  * @{
  */

/**
  * @brief cmp non-inverting type
  */
typedef enum
{
  CMP_NON_INVERTING_PA5                  = 0x00, /*!< comparator non-inverting connect to pa5 */
  CMP_NON_INVERTING_PA1                  = 0x01, /*!< comparator non-inverting connect to pa1 */
  CMP_NON_INVERTING_PA0                  = 0x02, /*!< comparator non-inverting connect to pa0 */
  CMP_NON_INVERTING_VSSA                 = 0x03  /*!< comparator non-inverting connect to vssa */
} cmp_non_inverting_type;

/**
  * @brief cmp inverting type
  */
typedef enum
{
  CMP_INVERTING_1_4VREFINT               = 0x00, /*!< comparator inverting connect to 1_4vrefint */
  CMP_INVERTING_1_2VREFINT               = 0x01, /*!< comparator inverting connect to 1_2vrefint */
  CMP_INVERTING_3_4VREFINT               = 0x02, /*!< comparator inverting connect to 3_4vrefint */
  CMP_INVERTING_VREFINT                  = 0x03, /*!< comparator inverting connect to vrefint */
  CMP_INVERTING_PA4                      = 0x04, /*!< comparator inverting connect to pa4 */
  CMP_INVERTING_PA5                      = 0x05, /*!< comparator inverting connect to pa5 */
  CMP_INVERTING_PA0                      = 0x06, /*!< comparator inverting connect to pa0 */
  CMP_INVERTING_PA2                      = 0x07  /*!< comparator inverting connect to pa2 */
} cmp_inverting_type;

/**
  * @brief cmp speed type
  */
typedef enum
{
  CMP_SPEED_FAST                         = 0x00, /*!< comparator selected fast speed */
  CMP_SPEED_MEDIUM                       = 0x01, /*!< comparator selected medium speed */
  CMP_SPEED_SLOW                         = 0x02, /*!< comparator selected slow speed */
  CMP_SPEED_ULTRALOW                     = 0x03  /*!< comparator selected ultralow speed */
} cmp_speed_type;

/**
  * @brief cmp output type
  */
typedef enum
{
  CMP_OUTPUT_NONE                        = 0x00, /*!< comparator has no output */
  CMP_OUTPUT_TMR1BRK                     = 0x01, /*!< comparator output connect to tmr1brk */
  CMP_OUTPUT_TMR1CH1                     = 0x02, /*!< comparator output connect to tmr1ch1 */
  CMP_OUTPUT_TMR1CHCLR                   = 0x03, /*!< comparator output connect to tmr1chclr */
  CMP_OUTPUT_TMR3CH1                     = 0x06, /*!< comparator output connect to tmr3ch1 */
  CMP_OUTPUT_TMR3CHCLR                   = 0x07  /*!< comparator output connect to tmr3chclr */
} cmp_output_type;

/**
  * @brief cmp polarity type
  */
typedef enum
{
  CMP_POL_NON_INVERTING                  = 0x00, /*!< comparator polarity non-inverting */
  CMP_POL_INVERTING                      = 0x01, /*!< comparator polarity inverting */
} cmp_polarity_type;

/**
  * @brief cmp hysteresis type
  */
typedef enum
{
  CMP_HYSTERESIS_NONE                    = 0x00, /*!< comparator selected no hysteresis */
  CMP_HYSTERESIS_LOW                     = 0x01, /*!< comparator selected low hysteresis */
  CMP_HYSTERESIS_MEDIUM                  = 0x02, /*!< comparator selected medium hysteresis */
  CMP_HYSTERESIS_HIGH                    = 0x03  /*!< comparator selected high hysteresis */
} cmp_hysteresis_type;

/**
  * @brief cmp blanking type
  */
typedef enum
{
  CMP_BLANKING_NONE                      = 0x00, /*!< comparator no blanking */
  CMP_BLANKING_TMR1_CH4                  = 0x01, /*!< comparator selected tmr1 ch4 as blanking */
  CMP_BLANKING_TMR3_CH3                  = 0x03, /*!< comparator selected tmr3 ch3 as blanking */
  CMP_BLANKING_TMR15_CH2                 = 0x04, /*!< comparator selected tmr15 ch2 as blanking */
  CMP_BLANKING_TMR15_CH1                 = 0x06  /*!< comparator selected tmr15 ch1 as blanking */
} cmp_blanking_type;

/**
  * @brief cmp scale voltage and voltage bridge type
  */
typedef enum
{
  CMP_SCAL_BRG_00                        = 0x00, /*!< comparator selected vrefint = 3/4 vrefint = 1/2 vrefint = 1/4 vrefint = 0v */
  CMP_SCAL_BRG_10                        = 0x02, /*!< comparator selected vrefint = 3/4 vrefint = 1/2 vrefint = 1/4 vrefint = 1.2v */
  CMP_SCAL_BRG_11                        = 0x03  /*!< comparator selected vrefint = 1.2v, 3/4 vrefint = 0.9v, 1/2 vrefint = 0.6v, 1/4 vrefint = 0.3v */
} cmp_scal_brg_type;

/**
  * @brief cmp selection type
  */
typedef enum
{
  CMP1_SELECTION                         = 0x00, /*!< select comparator 1 */
} cmp_sel_type;

/**
  * @brief cmp init type
  */
typedef struct
{
  cmp_non_inverting_type                 cmp_non_inverting;  /*!< comparator non-inverting input selection */
  cmp_inverting_type                     cmp_inverting;      /*!< comparator inverting selection */
  cmp_speed_type                         cmp_speed;          /*!< comparator speed selection */
  cmp_output_type                        cmp_output;         /*!< comparator output target selection */
  cmp_polarity_type                      cmp_polarity;       /*!< comparator polarity selection */
  cmp_hysteresis_type                    cmp_hysteresis;     /*!< comparator hysteresis selection */
}cmp_init_type;

/**
  * @brief type define cmp register all
  */
typedef struct
{
  /**
    * @brief cmp control and status register, offset:0x1C
    */
  union
  {
    __IO uint32_t ctrlsts;
    struct
    {
      __IO uint32_t cmpen                : 1; /* [0] */
      __IO uint32_t cmpis                : 1; /* [1] */
      __IO uint32_t cmpssel              : 2; /* [3:2] */
      __IO uint32_t cmpinvsel            : 3; /* [6:4] */
      __IO uint32_t cmpninvsel           : 2; /* [8:7] */
      __IO uint32_t reserved1            : 1; /* [9] */
      __IO uint32_t cmptag               : 3; /* [12:10] */
      __IO uint32_t reserved2            : 2; /* [14:13] */
      __IO uint32_t cmpp                 : 1; /* [15] */
      __IO uint32_t cmphyst              : 2; /* [17:16] */
      __IO uint32_t cmpblanking          : 3; /* [20:18] */
      __IO uint32_t reserved3            : 1; /* [21] */
      __IO uint32_t brgen                : 1; /* [22] */
      __IO uint32_t scalen               : 1; /* [23] */
      __IO uint32_t reserved4            : 6; /* [29:24] */
      __IO uint32_t cmpvalue             : 1; /* [30] */
      __IO uint32_t cmpwp                : 1; /* [31] */
    } ctrlsts_bit;
  };

  /**
    * @brief crm reserved1 register, offset:0x20
    */
  __IO uint32_t reserved1;

  /**
    * @brief cmp Glitch filter enable register, offset:0x24
    */
  union
  {
    __IO uint32_t g_filter_en;
    struct
    {
      __IO uint32_t gfe                  : 1; /* [0] */
      __IO uint32_t reserved1            : 31;/* [31:1] */
    } g_filter_en_bit;
  };

  /**
    * @brief cmp high pulse count register, offset:0x28
    */
  union
  {
    __IO uint32_t high_pulse;
    struct
    {
      __IO uint32_t h_pulse_cnt          : 6; /* [5:0] */
      __IO uint32_t reserved1            : 26;/* [31:6] */
    } high_pulse_bit;
  };

  /**
    * @brief cmp low pulse count register, offset:0x2C
    */
  union
  {
    __IO uint32_t low_pulse;
    struct
    {
      __IO uint32_t l_pulse_cnt          : 6; /* [5:0] */
      __IO uint32_t reserved1            : 26;/* [31:6] */
    } low_pulse_bit;
  };

} cmp_type;

/**
  * @}
  */

#define CMP                             ((cmp_type *) (SCFG_CMP_BASE + 0x1C))

/** @defgroup CMP_exported_functions
  * @{
  */

void cmp_reset(void);
void cmp_init(cmp_sel_type cmp_sel, cmp_init_type* cmp_init_struct);
void cmp_default_para_init(cmp_init_type *cmp_init_struct);
void cmp_enable(cmp_sel_type cmp_sel, confirm_state new_state);
void cmp_input_shift_enable(confirm_state new_state);
uint32_t cmp_output_value_get(cmp_sel_type cmp_sel);
void cmp_write_protect_enable(cmp_sel_type cmp_sel);
void cmp_filter_config(uint16_t high_pulse_cnt, uint16_t low_pulse_cnt, confirm_state new_state);
void cmp_blanking_config(cmp_blanking_type blank_sel);
void cmp_scal_brg_config(uint32_t scal_brg);

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
