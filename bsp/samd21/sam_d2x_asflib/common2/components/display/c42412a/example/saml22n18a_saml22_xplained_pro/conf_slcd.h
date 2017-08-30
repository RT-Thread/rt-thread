/**
 * \file
 *
 * \brief SAM SLCD Driver Configuration Header
 *
 * Copyright (C) 2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#ifndef CONF_SLCD_H_INCLUDED
#define CONF_SLCD_H_INCLUDED

/** Select SLCD clock. Use 32.768KHz OSCULP32K or XOSC32K for SLCD clock.
 *  0 : From OSCULP32K
 *  1 : From XOSC32K
 */
#define CONF_SLCD_CLOCK_SOURCE    0

/** SLCD Duty Setting
 *  0:Static duty
 *  1:1/2 duty
 *  2:1/3 duty
 *  3:1/4 duty
*/
#define CONF_SLCD_DUTY         3

/**
 * SLCD Bias Setting.
 *  0:Static bias
 *  1:1/2 bias
 *  2:1/3 bias
 *  3:1/4 bias
 */
#define CONF_SLCD_BIAS         2

/**
 * SLCD Frame Frequency.
 * The optimal frame frequency should be in range from 30Hz up to 100Hz
 * to avoid flickering and ghosting effect.
 * To get the frame frequency, CLK_SLCD_OSC is first divided by a prescaler
 * from 16 to 128 then divided by 1 up to 8 as following.
 * 
 * FrameRate = CLK_SLCD_OSC / (PVAL*(CKDIV+1)(DUTY+1))
 *
 * SLCD Prescaler Value (PVAL).
 * 0 : 16 prescaler
 * 1 : 32 prescaler
 * 2 : 64 prescaler
 * 3 : 128 prescaler
 *
 * SLCD Clock divider (CKDIV)
 * 0 : CKDIV is 0
 * 1 : CKDIV is 1
 * 2 : CKDIV is 2
 * 3 : CKDIV is 3
 * 4 : CKDIV is 4
 * 5 : CKDIV is 5
 * 6 : CKDIV is 6
 * 7 : CKDIV is 7
 */
#define CONF_SLCD_PVAL         0
#define CONF_SLCD_CKDIV        7

/** Internal/External VLCD selection.
* 0 : Internal VLCD generation
* 1 : External VLCD generation
*/
#define CONF_SLCD_VLCD_SEL        0

/** Reference refresh frequency. 
*  0: Bias Reference refresh frequency is 2KHz
*  1: Bias Reference refresh frequency is 1KHz
*  2: Bias Reference refresh frequency is 500Hz
*  3: Bias Reference refresh frequency is 250Hz
*  4: Bias Reference refresh frequency is 125Hz
*  5: Bias Reference refresh frequency is 62.5Hz
*/
#define CONF_SLCD_REF_REFRESH_FREQ        0

/** Power fefresh frequency.
*  0: Charge pump refresh frequency is 2KHz
*  1: Charge pump refresh frequency is 1KHz
*  2: Charge pump refresh frequency is 500Hz
*  3: Charge pump refresh frequency is 250Hz
 */
#define CONF_SLCD_POWER_REFRESH_FREQ       0
 
/** LCD Working Power Mode.
 * 0:LCD power automatically select regualation mode or pump mode.
 * 1:LCD power use step-up pump loop only.
 * 2:LCD power use step-down drop-out regulation loop only.
 */ 
#define CONF_SLCD_POWER_MODE       0

/** COM/SEG PIN Selection.
 * There are 52 LCD pins, but SLCD can drive up to 48 LCD pins which can be
 * individually enabled or disabled according to the LCD glass. The number of LCD pins
 * enabled should not be higher than the maximum of COM and SEG lines supported.
 * COM and SEG lines are always assigned in ascending order.
 * CONF_SLCD_PIN_L_MASK is pin mask [31,0]
 * CONF_SLCD_PIN_H_MASK is pin mask [51,32]
 */ 
#define CONF_SLCD_PIN_L_MASK       0xCFFFC3C0
#define CONF_SLCD_PIN_H_MASK       0x00000FF0
#endif
