/**
  **************************************************************************
  * @file     at32m412_416_cmp.h
  * @brief    at32m412_416 cmp header file
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
#ifndef __AT32M412_416_CMP_H
#define __AT32M412_416_CMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "at32m412_416.h"

/** @addtogroup AT32M412_416_periph_driver
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
  CMP_NON_INVERTING_INP0                 = 0x00, /*!< comparator non-inverting connect to inp0 */
  CMP_NON_INVERTING_INP1                 = 0x01, /*!< comparator non-inverting connect to inp1 */
  CMP_NON_INVERTING_INP2                 = 0x02, /*!< comparator non-inverting connect to inp2 */
  CMP_NON_INVERTING_INP3                 = 0x03, /*!< comparator non-inverting connect to inp3 */
} cmp_non_inverting_type;

/**
  * @brief cmp inverting type
  */
typedef enum
{
  CMP_INVERTING_INM0                     = 0x00, /*!< comparator inverting connect to inm0 */
  CMP_INVERTING_INM1                     = 0x01, /*!< comparator inverting connect to inm1 */
  CMP_INVERTING_INM2                     = 0x02, /*!< comparator inverting connect to inm2 */
  CMP_INVERTING_INM3                     = 0x03, /*!< comparator inverting connect to inm3 */
  CMP_INVERTING_INM4                     = 0x04, /*!< comparator inverting connect to inm4 */
  CMP_INVERTING_INM5                     = 0x05, /*!< comparator inverting connect to inm5 */
  CMP_INVERTING_INM6                     = 0x06, /*!< comparator inverting connect to inm6 */
  CMP_INVERTING_INM7                     = 0x07  /*!< comparator inverting connect to inm7 */
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
  CMP_BLANKING_TMR1_CH5                  = 0x02, /*!< comparator selected tmr1 ch5 as blanking */
  CMP_BLANKING_TMR3_CH3                  = 0x08, /*!< comparator selected tmr3 ch3 as blanking */
  CMP_BLANKING_TMR9_CH2                  = 0x10, /*!< comparator selected tmr9 ch2 as blanking */
  CMP_BLANKING_TMR9_CH1                  = 0x20, /*!< comparator selected tmr9 ch1 as blanking */
  CMP_BLANKING_TMR4_CH3                  = 0x40  /*!< comparator selected tmr4 ch3 as blanking */
} cmp_blanking_type;

/**
  * @brief cmp selection type
  */
typedef enum
{
  CMP1_SELECTION                         = 0x01, /*!< select comparator 1 */
  CMP2_SELECTION                         = 0x02, /*!< select comparator 1 */
} cmp_sel_type;

/**
  * @brief cmp init type
  */
typedef struct
{
  cmp_non_inverting_type                 cmp_non_inverting;  /*!< comparator non-inverting input selection */
  cmp_inverting_type                     cmp_inverting;      /*!< comparator inverting selection */
  cmp_speed_type                         cmp_speed;          /*!< comparator speed selection */
  cmp_polarity_type                      cmp_polarity;       /*!< comparator polarity selection */
  cmp_hysteresis_type                    cmp_hysteresis;     /*!< comparator hysteresis selection */
}cmp_init_type;

/**
  * @brief type define cmp register all
  */
typedef struct
{  
  /**
    * @brief cmp1 control and status register, offset:0x30
    */
  union
  {
    __IO uint32_t cmp1_ctrlsts;
    struct
    {
      __IO uint32_t cmpen                : 1; /* [0] */
      __IO uint32_t reserved1            : 1; /* [1] */
      __IO uint32_t cmpssel              : 2; /* [3:2] */
      __IO uint32_t cmpinvsel            : 3; /* [6:4] */
      __IO uint32_t reserved2            : 1; /* [7] */
      __IO uint32_t cmpninvsel           : 2; /* [9:8] */
      __IO uint32_t reserved3            : 5; /* [14:10] */
      __IO uint32_t cmpp                 : 1; /* [15] */
      __IO uint32_t cmphyst              : 2; /* [17:16] */
      __IO uint32_t reserved4            : 1; /* [18] */
      __IO uint32_t cmpblanking          : 7; /* [25:19] */
      __IO uint32_t reserved5            : 4; /* [29:26] */      
      __IO uint32_t cmpvalue             : 1; /* [30] */
      __IO uint32_t cmpwp                : 1; /* [31] */
    } cmp1_ctrlsts_bit;
  };

  /**
    * @brief cmp1 Glitch filter enable register, offset:0x34
    */
  union
  {
    __IO uint32_t cmp1_g_filter_en;
    struct
    {
      __IO uint32_t gfe                  : 1; /* [0] */
      __IO uint32_t reserved1            : 31;/* [31:1] */
    } cmp1_g_filter_en_bit;
  };

  /**
    * @brief cmp1 high pulse count register, offset:0x38
    */
  union
  {
    __IO uint32_t cmp1_high_pulse;
    struct
    {
      __IO uint32_t h_pulse_cnt          : 6; /* [5:0] */
      __IO uint32_t reserved1            : 26;/* [31:6] */
    } cmp1_high_pulse_bit;
  };

  /**
    * @brief cmp1 low pulse count register, offset:0x3C
    */
  union
  {
    __IO uint32_t cmp1_low_pulse;
    struct
    {
      __IO uint32_t l_pulse_cnt          : 6; /* [5:0] */
      __IO uint32_t reserved1            : 26;/* [31:6] */
    } cmp1_low_pulse_bit;
  };

  /**
    * @brief cmp2 control and status register, offset:0x40
    */
  union
  {
    __IO uint32_t cmp2_ctrlsts;
    struct
    {
      __IO uint32_t cmpen                : 1; /* [0] */
      __IO uint32_t reserved1            : 1; /* [1] */
      __IO uint32_t cmpssel              : 2; /* [3:2] */
      __IO uint32_t cmpinvsel            : 3; /* [6:4] */
      __IO uint32_t reserved2            : 1; /* [7] */
      __IO uint32_t cmpninvsel           : 2; /* [9:8] */
      __IO uint32_t reserved3            : 5; /* [14:10] */
      __IO uint32_t cmpp                 : 1; /* [15] */
      __IO uint32_t cmphyst              : 2; /* [17:16] */
      __IO uint32_t reserved4            : 1; /* [18] */
      __IO uint32_t cmpblanking          : 7; /* [25:19] */
      __IO uint32_t reserved5            : 4; /* [29:26] */      
      __IO uint32_t cmpvalue             : 1; /* [30] */
      __IO uint32_t cmpwp                : 1; /* [31] */
    } cmp2_ctrlsts_bit;
  };

  /**
    * @brief cmp2 Glitch filter enable register, offset:0x44
    */
  union
  {
    __IO uint32_t cmp2_g_filter_en;
    struct
    {
      __IO uint32_t gfe                  : 1; /* [0] */
      __IO uint32_t reserved1            : 31;/* [31:1] */
    } cmp2_g_filter_en_bit;
  };

  /**
    * @brief cmp2 high pulse count register, offset:0x48
    */
  union
  {
    __IO uint32_t cmp2_high_pulse;
    struct
    {
      __IO uint32_t h_pulse_cnt          : 6; /* [5:0] */
      __IO uint32_t reserved1            : 26;/* [31:6] */
    } cmp2_high_pulse_bit;
  };

  /**
    * @brief cmp2 low pulse count register, offset:0x4C
    */
  union
  {
    __IO uint32_t cmp2_low_pulse;
    struct
    {
      __IO uint32_t l_pulse_cnt          : 6; /* [5:0] */
      __IO uint32_t reserved1            : 26;/* [31:6] */
    } cmp2_low_pulse_bit;
  };
} cmp_type;

/**
  * @}
  */

#define CMP                             ((cmp_type *) (CMP_BASE + 0x30))

/** @defgroup CMP_exported_functions
  * @{
  */

void cmp_init(cmp_sel_type cmp_sel, cmp_init_type* cmp_init_struct);
void cmp_default_para_init(cmp_init_type *cmp_init_struct);
void cmp_enable(cmp_sel_type cmp_sel, confirm_state new_state);
uint32_t cmp_output_value_get(cmp_sel_type cmp_sel);
void cmp_write_protect_enable(cmp_sel_type cmp_sel);
void cmp_filter_config(cmp_sel_type cmp_sel, uint16_t high_pulse_cnt, uint16_t low_pulse_cnt, confirm_state new_state);
void cmp_blanking_config(cmp_sel_type cmp_sel, cmp_blanking_type blank_sel);

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
