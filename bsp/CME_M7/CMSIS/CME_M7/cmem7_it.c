/**
	*****************************************************************************
	* @file     cmem7_it.c
	*
	* @brief    CMEM7 system exception file
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
	
#include "cmem7_it.h"

void NMI_Handler(void)
{
	while (1);
}

void HardFault_Handler(void)
{
  if (CoreDebug->DHCSR & 1) { // check C_DEBUGEN == 1-> Debugger Connected
    __breakpoint (0); // halt program execution here
  }
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

void MemManage_Handler(void)
{
  if (CoreDebug->DHCSR & 1) { // check C_DEBUGEN == 1-> Debugger Connected
    __breakpoint (0); // halt program execution here
  }
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

void BusFault_Handler(void)
{
  if (CoreDebug->DHCSR & 1) { // check C_DEBUGEN == 1-> Debugger Connected
    __breakpoint (0); // halt program execution here
  }
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

void UsageFault_Handler(void)
{
  if (CoreDebug->DHCSR & 1) { // check C_DEBUGEN == 1-> Debugger Connected
    __breakpoint (0); // halt program execution here
  }
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
}

