/*""FILE COMMENT""*******************************************************
* System Name	: Interrupt program for RX62Nxx
* File Name		: Interrupt_WDT.c
* Version		: 1.02
* Contents		: Interrupt handler for the Watchdog timer
* Customer		: 
* Model		 	:
* Order		 	:
* CPU			: RX
* Compiler		: RXC
* OS			: Nothing
* Programmer	: 
* Note			: 
************************************************************************
* Copyright, 2011. Renesas Electronics Corporation
* and Renesas Solutions Corporation
************************************************************************
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FILE COMMENT END""**************************************************/

#include "r_pdl_wdt.h"
#include "r_pdl_definitions.h"
#include "r_pdl_user_definitions.h"

/*""FUNC COMMENT""***************************************************
* Module outline : Timer interrupt processing
*-------------------------------------------------------------------
* Declaration	: void Interrupt_WDT(void)
*-------------------------------------------------------------------
* Function		: Interrupt processing function for the WDT
*-------------------------------------------------------------------
* Argument		: Nothing
*-------------------------------------------------------------------
* Return value	: Nothing
*-------------------------------------------------------------------
* Input			:
* Output		: 
*-------------------------------------------------------------------
* Use function	: WDT_callback_func
*-------------------------------------------------------------------
* Notes			:
*-------------------------------------------------------------------
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FUNC COMMENT END""**********************************************/

#if FAST_INTC_VECTOR == VECT_WDT_WOVI
__fast_interrupt void Interrupt_WDT(void)
#else
#pragma vector = VECT_WDT_WOVI
__interrupt void Interrupt_WDT(void)
#endif
{
  /* Call the user function */
  if (rpdl_WDT_callback_func != PDL_NO_FUNC)
  {
    rpdl_WDT_callback_func();
  }
}
/* End of file */
