/**
	*****************************************************************************
	* @file     system_cmem7.c
	*
	* @brief    CMEM7 system initial file
	*
	*
	* @version  V1.0
	* @date     3. September 2013
	*
	* @note      
	*           
	*****************************************************************************
	* @attention
	*
	* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
	* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
	* TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT, 
	* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
	* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
	* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
	*
	* <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
	*****************************************************************************
	*/

#include "cmem7.h"
#include "cmem7_includes.h"

void SystemInit (void) {
	// Generally, we use DLL clock as system clock, not default oscillator
	GLB_SelectSysClkSource(SYS_CLK_SEL_DLL);

	// change NMI to PAD IRQ
	GLB_SetNmiIrqNum(PAD_INT_IRQn);	
	
	return ;
}

