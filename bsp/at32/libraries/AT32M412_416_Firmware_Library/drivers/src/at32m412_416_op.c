/**
  **************************************************************************
  * @file     at32m412_416_op.c
  * @brief    contains all the functions for the gpio firmware library
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

#include "at32m412_416_conf.h"

/** @addtogroup AT32M412_416_periph_driver
  * @{
  */

/** @defgroup OP
  * @brief OP driver modules
  * @{
  */
  
#ifdef OP_MODULE_ENABLED

/** @defgroup OP_private_functions
  * @{
  */

/**
  * @brief  op enable.
  * @param  op_x: to select the OP peripheral.
  *         this parameter can be one of the following values:  
  *         OP1, OP2, OP3, OP4.
  * @param  new_state: OP enable or disable(TRUE or FALSE).
  * @retval none
  */
void op_enable(op_type *op_x, confirm_state new_state)
{
  /* set op enable or disable */
  op_x->ctrl_bit.open = new_state;
}


/**
  * @brief  set the op peripheral mode.
  * @param  op_x: to select the OP peripheral.
  *         this parameter can be one of the following values:  
  *         OP1, OP2, OP3, OP4.
  * @param  mode: OP mode
  *         this parameter can be one of the following values:  
  *         - OP_FUNCTIONAL_MODE
  *         - OP_CALIBRATION_MODE
  * @retval none
  */
void op_set_mode(op_type *op_x, op_mode_type mode)
{
  
  op_x->ctrl_bit.calen = mode;
  
}

/**
  * @brief  set the op functional mode.
  * @param  op_x: to select the OP peripheral.
  *         this parameter can be one of the following values:  
  *         OP1, OP2, OP3, OP4.
  * @param  functional_mode: OP functional mode
  *         this parameter can be one of the following values:  
  *         - OP_STANDALONE_MODE
  *         - OP_FOLLOWER_MODE
  *         - OP_PGA_MODE
  *         - OP_PGA_VINM0_MODE
  *         - OP_PGA_VINM0_BIAS_MODE
  *         - OP_PGA_VINM0_VINM1_BIAS_MODE
  * @retval none
  */
void op_set_functional_mode(op_type *op_x, op_functional_mode_type functional_mode)
{
  /* clear op functional mode bit */
  op_x->ctrl &= (~OP_FUNCTIONAL_MODE_MASK);
  
  /* set op functional mode */
  op_x->ctrl |= functional_mode;
	
	if(OP_FOLLOWER_MODE == functional_mode)
		op_x->tc_bit.vmssel = 0x1;
}

/**
  * @brief  set the op pga gain value.
  * @param  op_x: to select the OP peripheral.
  *         this parameter can be one of the following values:  
  *         OP1, OP2, OP3, OP4.
  * @param  gain: OP pga gain value
  *         this parameter can be one of the following values:  
  *         - OP_PGA_GAIN_2_OR_MINUS_1
  *         - OP_PGA_GAIN_4_OR_MINUS_3
  *         - OP_PGA_GAIN_8_OR_MINUS_7
  *         - OP_PGA_GAIN_16_OR_MINUS_15
  *         - OP_PGA_GAIN_32_OR_MINUS_31
  *         - OP_PGA_GAIN_64_OR_MINUS_63
  * @retval none
  */
void op_set_gain(op_type *op_x, op_gain_type gain)
{
  /* clear op pga gain value bit */
  op_x->ctrl &= (~OP_PGA_GAIN_MASK);
  
  /* set op pga gain value */
  op_x->ctrl |= gain;
}
  
/**
  * @brief  set the OP high speed mode.
  * @param  op_x: to select the OP peripheral.
  *         this parameter can be one of the following values:  
  *         OP1, OP2, OP3, OP4.
  * @param  new_state: new mode of the opa high-speed(TRUE or FALSE).
  * @retval none
  */
void op_set_highspeed_mode_enable(op_type *op_x, confirm_state new_state)
{
  /* set op high speed mode */
  op_x->ctrl_bit.opfstmd = new_state;
}

/**
  * @brief  op non inverted input selection.
  * @param  op_x: to select the OP peripheral.
  *         this parameter can be one of the following values:  
  *         OP1, OP2, OP3, OP4.
  * @param  non_inverting_input: non inverted input
  *         this parameter can be one of the following values:  
  *         - OP_NON_INVERTING_INPUT_VP0
  *         - OP_NON_INVERTING_INPUT_VP1
  *         - OP_NON_INVERTING_INPUT_VP2
  *         - OP_NON_INVERTING_INPUT_VP3
  * @retval none
  */
void op_set_input_non_inverting(op_type *op_x, op_non_inverting_input_type non_inverting_input)
{
  /* set the op non inverted input */
  op_x->ctrl_bit.vpsel = non_inverting_input;
}

/**
  * @brief  OP inverted input selection.
  * @param  op_x: to select the OP peripheral.
  *         this parameter can be one of the following values:  
  *         OP1, OP2, OP3, OP4.
  * @param  inverting_input: OP inverted input
  *         this parameter can be one of the following values:  
  *         - OP_INVERTING_INPUT_VM0
  *         - OP_INVERTING_INPUT_VM1
  *         - OP_INVERTING_INPUT_NONE
  * @retval none
  */
void op_set_input_inverting(op_type *op_x, op_inverting_input_type inverting_input)
{
  /* set the op inverted input */
  op_x->ctrl_bit.vmsel = inverting_input;
}

/**
  * @brief  op non inverted input secondary selection.
  * @param  op_x: to select the OP peripheral.
  *         this parameter can be one of the following values:  
  *         OP1, OP2, OP3, OP4.
  * @param  non_inverting_input: non inverting input secondary 
  *         this parameter can be one of the following values:  
  *         - OP_NON_INVERTING_INPUT_VP0
  *         - OP_NON_INVERTING_INPUT_VP1
  *         - OP_NON_INVERTING_INPUT_VP2
  *         - OP_NON_INVERTING_INPUT_VP3
  * @retval none
  */
void op_input_non_inverting_switch(op_type *op_x, op_non_inverting_input_type non_inverting_input)
{
  /* set the op secondary non inverted input */
  op_x->tc_bit.vpssel = non_inverting_input;
}
  
/**
  * @brief  op inverted input secondary selection.
  * @param  op_x: to select the OP peripheral.
  *         this parameter can be one of the following values:  
  *         OP1, OP2, OP3, OP4.
  * @param  inverting_input: OP inverted input secondary selection source
  *         this parameter can be one of the following values:  
  *         - OP_INVERTING_INPUT_VM0(or PGA mode)
  *         - OP_INVERTING_INPUT_VM1(or FOLLOWER mode)
  * @retval none
  */
void op_input_inverting_switch(op_type *op_x, op_inverting_input_type inverting_input)
{
  /* set the op secondary inverted input */
  op_x->tc_bit.vmssel = inverting_input;
}

/**
  * @brief  set the OP input mux mode.
  * @param  op_x: to select the OP peripheral.
  *         this parameter can be one of the following values:  
  *         OP1, OP2, OP3, OP4.
  * @param  new_state: tmr controlled mux mode new state(TRUE or FALSE).
  * @retval none
  */
void op_input_mux_enable(op_type *op_x, confirm_state new_state)
{
  /* tmr controlled mux mode enable */
  op_x->tc_bit.tmr1en = new_state;
}

/**
  * @brief  op internal output selection.
  * @param  op_x: to select the OP peripheral.
  *         this parameter can be one of the following values:  
  *         OP1, OP2, OP3, OP4.
  * @param  internal_output: OP internal output selection source
  *         this parameter can be one of the following values:  
  *         - OP_INTERNAL_OUTPUT_GPIO
  *         - OP_INTERNAL_OUTPUT_ADC
  * @retval none
  */
void op_internal_output_select(op_type *op_x, op_internal_output_type internal_output)
{
  /* set op internal output(gpio or adc) */
  op_x->ctrl_bit.opoutsel = internal_output;
}

/**
  * @brief  op trimming mode selection.
  * @param  op_x: to select the OP peripheral.
  *         this parameter can be one of the following values:  
  *         OP1, OP2, OP3, OP4.
  * @param  trimming: OP trimming mode selection
  *         this parameter can be one of the following values:  
  *         - OP_TRIMMING_FACTORY
  *         - OP_TRIMMING_USER
  * @retval none
  */
void op_set_trimming_mode(op_type *op_x, op_trimming_type trimming)
{
  op_x->ctrl_bit.usertrim = trimming;
}

/**
  * @brief  op calibration selection.
  * @param  op_x: to select the OP peripheral.
  *         this parameter can be one of the following values:  
  *         OP1, OP2, OP3, OP4.
  * @param  cal_sel: OP calibration selection
  *         this parameter can be one of the following values:  
  *         - OP_TRIMMING_3_3VDDA
  *         - OP_TRIMMING_PMOS
  *         - OP_TRIMMING_50VDDA
  *         - OP_TRIMMING_NMOS
  * @retval none
  */
void op_calibration_select(op_type *op_x, op_calibrate_type cal_sel)
{
  /* set calsel bit for calibration */
  op_x->ctrl_bit.calsel = cal_sel;
}

/**
  * @brief  op calibration output status get.
  * @param  op_x: to select the OP peripheral.
  *         this parameter can be one of the following values:  
  *         OP1, OP2, OP3, OP4.
  * @retval state of calibration output
  */
flag_status op_calout_status_get(op_type *op_x)
{
  flag_status status = RESET;

  if((op_x->ctrl_bit.opcal) != RESET)
  {
    status = SET;
  }
  else
  {
    status = RESET;
  }

  return status;
}

/**
  * @brief  op triming value set.
  * @param  op_x: to select the OP peripheral.
  *         this parameter can be one of the following values:  
  *         OP1, OP2, OP3, OP4.
  * @param  cal_sel: OP calibration selection
  *         this parameter can be one of the following values:  
  *         - OP_TRIMMING_PMOS
  *         - OP_TRIMMING_NMOS
  * @param  triming_value: OP triming value(0x00...0x1f)
  * @retval none
  */
void op_set_triming_value(op_type *op_x, op_calibrate_type cal_sel, uint16_t triming_value)
{
  /* trim for pmos differential pairs */
  if(cal_sel == OP_TRIMMING_PMOS)
  {
    op_x->ctrl_bit.trimvalp = triming_value;
  }
  /* trim for nmos differential pairs */
  else if(cal_sel == OP_TRIMMING_NMOS)
  {
    op_x->ctrl_bit.trimvaln = triming_value;
  }
}

/**
  * @brief  op write protected enable.
  * @param  op_x: to select the OP peripheral.
  *         this parameter can be one of the following values:  
  *         OP1, OP2, OP3, OP4.
  * @param  lock_reg: OP lock register selection
  *         this parameter can be one of the following values:  
  *         - OP_WPC_CSR
  *         - OP_WPC_TMCR
  * @retval none
  */
void op_write_protected_enable(op_type *op_x, op_wpc_type wpc_reg)
{
  if(wpc_reg == OP_WPC_CTRL)
    op_x->ctrl_bit.wpc = TRUE;
  else
    op_x->tc_bit.wpc = TRUE;
}


/**
  * @}
  */

#endif

/**
  * @}
  */

/**
  * @}
  */
