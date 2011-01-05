/******************************************************************************
 * @file:    system_LPC122x.h
 * @purpose: CMSIS Cortex-M0 Device Peripheral Access Layer Header File
 *           for the NXP LPC122x Device Series 
 * @version: V1.0
 * @date:    25. Nov. 2008
 *----------------------------------------------------------------------------
 *
 * Copyright (C) 2008 ARM Limited. All rights reserved.
 *
 * ARM Limited (ARM) is supplying this software for use with Cortex-M0 
 * processor based microcontrollers.  This file can be freely distributed 
 * within development tools that are supporting such ARM based processors. 
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/


#ifndef __SYSTEM_LPC122x_H
#define __SYSTEM_LPC122x_H

/* Vector Table Base ---------------------------------------------------------*/
#define NVIC_VectTab_RAM             (0x10000000)
#define NVIC_VectTab_FLASH           (0x00000000)

extern uint32_t ClockSource;
extern uint32_t SystemFrequency;    /*!< System Clock Frequency (Core Clock)  */
extern uint32_t SystemAHBFrequency;

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemFrequency variable.
 */
extern void SystemInit (void);
#endif
