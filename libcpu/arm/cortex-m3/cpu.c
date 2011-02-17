/******************************************************************//**
 * @file 		cpu.c
 * @brief 	This file is part of RT-Thread RTOS
 * 	COPYRIGHT (C) 2009, RT-Thread Development Team
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
/* Private function prototypes ---------------------------------------------------*/
/* Private functions ------------------------------------------------------------*/
/**
 * reset cpu by dog's time-out
 *
 */
void rt_hw_cpu_reset()
{
	/*NOTREACHED*/
}

/**
 *  shutdown CPU
 *
 */
void rt_hw_cpu_shutdown()
{
	rt_kprintf("shutdown...\n");

	RT_ASSERT(0);
}

/******************************************************************//**
 * @}
*********************************************************************/
