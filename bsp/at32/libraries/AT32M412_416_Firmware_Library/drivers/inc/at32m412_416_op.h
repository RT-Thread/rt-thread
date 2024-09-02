/**
  **************************************************************************
  * @file     at32m412_416_op.h
  * @brief    at32m412_416 OP header file
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
#ifndef __AT32M412_416_OP_H
#define __AT32M412_416_OP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "at32m412_416.h"

/** @addtogroup AT32M412_416_periph_driver
  * @{
  */

/** @addtogroup OP
  * @{
  */
  
/** @defgroup op_functional_mode_definition
  * @brief op functional mode
  * @{
  */
  
#define OP_FUNCTIONAL_MODE_MASK          ((uint32_t)0x00060860) /*!< op functional mode mask */

typedef enum
{
  OP_STANDALONE_MODE                     = ((uint32_t)0x00000000), /*!< op functional mode, in standalone */
  OP_FOLLOWER_MODE                       = ((uint32_t)0x00000060), /*!< op functional mode, in follower mode and vm_sel[1:0]=0x3 */
  OP_PGA_MODE                            = ((uint32_t)0x00000040), /*!< op functional mode, in pga mode and vm_sel[1:0]=0x2 */
  OP_PGA_VINM0_MODE                      = ((uint32_t)0x00040040), /*!< op functional mode, in pga mode and the inverting input is connected to vinm0 for filtering */
  OP_PGA_VINM0_BIAS_MODE                 = ((uint32_t)0x00020040), /*!< op functional mode, in pga mode and the inverting input is connected to vinm0
                                                                        - input signal on vinm0, bias on vinpx: negative gain
                                                                        - bias on vinm0, input signal on vinpx: positive gain */
  OP_PGA_VINM0_VINM1_BIAS_MODE           = ((uint32_t)0x00060040), /*!< op functional mode, in pga mode and the inverting input is connected to vinm0
                                                                        - input signal on vinm0, bias on vinpx: negative gain
                                                                        - bias on vinm0, input signal on vinpx: positive gain 
                                                                        and vinm1 is connected to for filtering */
} op_functional_mode_type;
/**
  * @}
  */

/** @defgroup op_pga_gain_value_definition
  * @brief op pga gain value
  * @{
  */

#define OP_PGA_GAIN_MASK                 ((uint32_t)0x0001C000) /*!< op pga gain value mask */

typedef enum
{
  OP_PGA_GAIN_2_OR_MINUS_1               = ((uint32_t)0x00000000), /*!< op pga inverting gain = -1 / non inverting gain =2 */
  OP_PGA_GAIN_4_OR_MINUS_3               = ((uint32_t)0x00004000), /*!< op pga inverting gain = -3 / non inverting gain =4 */
  OP_PGA_GAIN_8_OR_MINUS_7               = ((uint32_t)0x00008000), /*!< op pga inverting gain = -7 / non inverting gain =8 */
  OP_PGA_GAIN_16_OR_MINUS_15             = ((uint32_t)0x0000C000), /*!< op pga inverting gain = -15 / non inverting gain =16 */
  OP_PGA_GAIN_32_OR_MINUS_31             = ((uint32_t)0x00010000), /*!< op pga inverting gain = -31 / non inverting gain =32 */
  OP_PGA_GAIN_64_OR_MINUS_63             = ((uint32_t)0x00014000), /*!< op pga inverting gain = -63 / non inverting gain =64 */
} op_gain_type;


/**
  * @}
  */

/**
  * @brief op mode select
  */
typedef enum
{
  OP_FUNCTIONAL_MODE                     = 0x00, /*!< op functional mode */
  OP_CALIBRATION_MODE                    = 0x01, /*!< op calibration mode */
} op_mode_type;
  
/**
  * @}
  */  
  
/**
  * @brief op non-inverting input connection
  */
typedef enum
{
  OP_NON_INVERTING_INPUT_VP0             = 0x00, /*!< vinp0 pin connected to op vinp input */
  OP_NON_INVERTING_INPUT_VP1             = 0x01, /*!< vinp1 pin connected to op vinp input */
  OP_NON_INVERTING_INPUT_VP2             = 0x02, /*!< vinp2 pin connected to op vinp input */
  OP_NON_INVERTING_INPUT_VP3             = 0x03, /*!< vinp3 pin connected to op vinp input */
} op_non_inverting_input_type;
  
/**
  * @}
  */    
  
/**
  * @brief op inverting input connection
  */
typedef enum
{
  OP_INVERTING_INPUT_VM0                 = 0x00, /*!< vinm0 pin connected to op vinm input */
  OP_INVERTING_INPUT_VM1                 = 0x01, /*!< vinm1 pin connected to op vinm input */
  OP_INVERTING_INPUT_NONE                = 0x02, /*!< none pin connected to op vinm input,pga mode or follower mode */
} op_inverting_input_type;
  
/**
  * @}
  */

/**
  * @brief op internal output select
  */
typedef enum
{
  OP_INTERNAL_OUTPUT_GPIO                = 0x00, /*!< the op output is connected to the output pin */
  OP_INTERNAL_OUTPUT_ADC                 = 0x01, /*!< the op output is connected internally to an adc channel */
} op_internal_output_type;
  
/**
  * @}
  */ 

/**
  * @brief op trimming mode select
  */
typedef enum
{
  OP_TRIMMING_FACTORY                    = 0x00, /*!< factory trim code used */
  OP_TRIMMING_USER                       = 0x01, /*!< user trim code used */
} op_trimming_type;
  
/**
  * @}
  */ 

/**
  * @brief op calibrate select
  */
typedef enum
{
  OP_TRIMMING_3_3VDDA                    = 0x00, /*!< 0.033*vdda applied on op inputs */
  OP_TRIMMING_PMOS                       = 0x01, /*!< 0.1*vdda applied on op inputs (for pmos calibration) */
  OP_TRIMMING_50VDDA                     = 0x02, /*!< 0.5*vdda applied on op inputs */
  OP_TRIMMING_NMOS                       = 0x03, /*!< 0.9*vdda applied on op inputs (for nmos calibration) */
} op_calibrate_type;
  
/**
  * @}
  */

/**
  * @brief op wpc register select
  */
typedef enum
{
  OP_WPC_CTRL                            = 0x00, /*!< op ctrl register write protected */
  OP_WPC_TC                              = 0x01, /*!< op tc register write protected */
} op_wpc_type;
  
/**
  * @}
  */ 
  
typedef struct
{
  /**
    * @brief op ctrl register, offset:0x00
    */
  union
  {
    __IO uint32_t ctrl;
    struct
    {
      __IO uint32_t open                 : 1; /* [0] */
      __IO uint32_t vrfsel               : 1; /* [1] */
      __IO uint32_t vpsel                : 2; /* [3:2] */
      __IO uint32_t usertrim             : 1; /* [4] */
      __IO uint32_t vmsel                : 2; /* [6:5] */
      __IO uint32_t opfstmd              : 1; /* [7] */
      __IO uint32_t opoutsel             : 1; /* [8] */
      __IO uint32_t reserved1            : 2; /* [10:9] */
      __IO uint32_t calen                : 1; /* [11] */
      __IO uint32_t calsel               : 2; /* [13:12] */
      __IO uint32_t opgain               : 5; /* [18:14] */
      __IO uint32_t trimvalp             : 5; /* [23:19] */
      __IO uint32_t trimvaln             : 5; /* [28:24] */
      __IO uint32_t reserved2            : 1; /* [29] */
      __IO uint32_t opcal                : 1; /* [30] */
      __IO uint32_t wpc                  : 1; /* [31] */
    } ctrl_bit;
  };
  
  /**
    * @brief reserved, offset:0x04~0x14
    */
  __IO uint32_t reserved1[5];
  
  /**
    * @brief op tcmr register, offset:0x18
    */
  union
  {
    __IO uint32_t tc;
    struct
    {
      __IO uint32_t vmssel               : 1; /* [0] */
      __IO uint32_t vpssel               : 2; /* [2:1] */
      __IO uint32_t tmr1en               : 1; /* [3] */
      __IO uint32_t reserved1            : 27; /* [30:4] */
      __IO uint32_t wpc                  : 1; /* [31] */
    } tc_bit;
  };
  
}op_type;  
  
  
#define OP1                              ((op_type*)OP1_BASE)
#define OP2                              ((op_type*)OP2_BASE)
#define OP3                              ((op_type*)OP3_BASE)
#define OP4                              ((op_type*)OP4_BASE)

void op_enable(op_type *op_x, confirm_state new_state);
void op_set_mode(op_type *op_x, op_mode_type mode);
void op_set_functional_mode(op_type *op_x, op_functional_mode_type functional_mode);  
void op_set_gain(op_type *op_x, op_gain_type gain);
void op_set_highspeed_mode_enable(op_type *op_x, confirm_state new_state);
void op_set_input_non_inverting(op_type *op_x, op_non_inverting_input_type non_inverting_input);
void op_set_input_inverting(op_type *op_x, op_inverting_input_type inverting_input);
void op_input_non_inverting_switch(op_type *op_x, op_non_inverting_input_type non_inverting_input);
void op_input_inverting_switch(op_type *op_x, op_inverting_input_type inverting_input);
void op_input_mux_enable(op_type *op_x, confirm_state new_state);
void op_internal_output_select(op_type *op_x, op_internal_output_type internal_output);
void op_set_trimming_mode(op_type *op_x, op_trimming_type trimming);
void op_calibration_select(op_type *op_x, op_calibrate_type cal_sel);
flag_status op_calout_status_get(op_type *op_x);
void op_set_triming_value(op_type *op_x, op_calibrate_type cal_sel, uint16_t triming_value);
void op_write_protected_enable(op_type *op_x, op_wpc_type wpc_reg);
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
