/**
  **************************************************************************
  * @file     at32f415_cmp.h
  * @brief    at32f415 cmp header file
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
#ifndef __AT32F415_CMP_H
#define __AT32F415_CMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "at32f415.h"

/** @addtogroup AT32F415_periph_driver
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
  CMP_NON_INVERTING_PA5_PA7              = 0x00, /*!< comparator1/2 non-inverting connect to pa5/pa7 */
  CMP_NON_INVERTING_PA1_PA3              = 0x01, /*!< comparator1/2 non-inverting connect to pa1/pa3 */
  CMP_NON_INVERTING_PA0_PA2              = 0x02, /*!< comparator1/2 non-inverting connect to pa0/pa2 */
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
  CMP_INVERTING_PA0_PA2                  = 0x06, /*!< comparator1/2 inverting connect to pa0/pa2 */
} cmp_inverting_type;

/**
  * @brief cmp speed type
  */
typedef enum
{
  CMP_SPEED_FAST                         = 0x00, /*!< comparator selected fast speed */
  CMP_SPEED_SLOW                         = 0x01, /*!< comparator selected slow speed */
} cmp_speed_type;

#define  CMP_OUTPUT_TMR1CXORAW_OFF       CMP_OUTPUT_TMR1CHCLR
#define  CMP_OUTPUT_TMR2CXORAW_OFF       CMP_OUTPUT_TMR2CHCLR
#define  CMP_OUTPUT_TMR3CXORAW_OFF       CMP_OUTPUT_TMR3CHCLR
/**
  * @brief cmp output type
  */
typedef enum
{
  CMP_OUTPUT_NONE                        = 0x00, /*!< comparator has no output */
  CMP_OUTPUT_TMR1BRK                     = 0x01, /*!< comparator output connect to tmr1brk */
  CMP_OUTPUT_TMR1CH1                     = 0x02, /*!< comparator output connect to tmr1ch1 */
  CMP_OUTPUT_TMR1CHCLR                   = 0x03, /*!< comparator output connect to tmr1chclr */
  CMP_OUTPUT_TMR2CH4                     = 0x04, /*!< comparator output connect to tmr1chclr */
  CMP_OUTPUT_TMR2CHCLR                   = 0x05, /*!< comparator output connect to tmr1chclr */
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
  * @brief cmp selection type
  */
typedef enum
{
  CMP1_SELECTION                         = 0x00, /*!< select comparator 1 */
  CMP2_SELECTION                         = 0x01, /*!< select comparator 2 */
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
    * @brief cmp control and status register1, offset:0x00
    */
  union
  {
    __IO uint32_t ctrlsts1;
    struct
    {
      __IO uint32_t cmp1en               : 1; /* [0] */
      __IO uint32_t cmp1is               : 1; /* [1] */
      __IO uint32_t cmp1ssel             : 1; /* [2] */
      __IO uint32_t reserved1            : 1; /* [3] */
      __IO uint32_t cmp1invsel           : 3; /* [6:4] */
      __IO uint32_t reserved2            : 1; /* [7] */
      __IO uint32_t cmp1tag              : 3; /* [10:8] */
      __IO uint32_t cmp1p                : 1; /* [11] */
      __IO uint32_t cmp1hyst             : 2; /* [13:12] */
      __IO uint32_t cmp1value            : 1; /* [14] */
      __IO uint32_t cmp1wp               : 1; /* [15] */
      __IO uint32_t cmp2en               : 1; /* [16] */
      __IO uint32_t reserved3            : 1; /* [17] */
      __IO uint32_t cmp2ssel             : 1; /* [18] */
      __IO uint32_t reserved4            : 1; /* [19] */
      __IO uint32_t cmp2invsel           : 3; /* [22:20] */
      __IO uint32_t dcmpen               : 1; /* [23] */
      __IO uint32_t cmp2tag              : 3; /* [26:24] */
      __IO uint32_t cmp2p                : 1; /* [27] */
      __IO uint32_t cmp2hyst             : 2; /* [29:28] */
      __IO uint32_t cmp2value            : 1; /* [30] */
      __IO uint32_t cmp2wp               : 1; /* [31] */
    } ctrlsts1_bit;
  };

  /**
    * @brief cmp control and status register2, offset:0x04
    */
  union
  {
    __IO uint32_t ctrlsts2;
    struct
    {
      __IO uint32_t cmp1ninvsel          : 2; /* [1:0] */
      __IO uint32_t reserved1            : 14;/* [15:2] */
      __IO uint32_t cmp2ninvsel          : 2; /* [17:16] */
      __IO uint32_t reserved2            : 14;/* [31:18] */
    } ctrlsts2_bit;
  };

} cmp_type;

/**
  * @}
  */

#define CMP                             ((cmp_type *) (CMP_BASE))

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
void cmp_double_mode_enable(confirm_state new_state);

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
