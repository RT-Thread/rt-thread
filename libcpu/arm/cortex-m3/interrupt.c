/******************************************************************//**
 * @file 		interrupt.c
 * @brief 	This file is part of RT-Thread RTOS
 * 	COPYRIGHT (C) 2011, RT-Thread Development Team
 * @author 	Bernard, onelife
 * @version 	0.4 beta
 **********************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file LICENSE in this 
 * distribution or at http://www.rt-thread.org/license/LICENSE
 **********************************************************************
 * @section Change Logs
 * Date			Author		Notes
 * 2009-01-05 	Bernard 		first version
 * 2011-02-14	onelife		Modify for EFM32
 *********************************************************************/
 
/******************************************************************//**
* @addtogroup cortex-m3
* @{
*********************************************************************/

/* Includes -------------------------------------------------------------------*/
#include <rtthread.h>

/* Private typedef -------------------------------------------------------------*/
/* Private define --------------------------------------------------------------*/
/* Private macro --------------------------------------------------------------*/
/* Private variables ------------------------------------------------------------*/
/* exception and interrupt handler table */
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrput_flag;

/* Private function prototypes ---------------------------------------------------*/
/* Private functions ------------------------------------------------------------*/

/******************************************************************//**
 * @}
*********************************************************************/
