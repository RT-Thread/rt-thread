/*""FILE COMMENT""*******************************************************
* System Name	: RTC Interrupt program for RX62Nxx
* File Name 	: Interrupt_RTC.c
* Version		: 1.02
* Contents		: Interrupt handler for RTC
* Customer		: 
* Model			: 
* Order			: 
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

#include "r_pdl_rtc.h"
#include "r_pdl_definitions.h"
#include "r_pdl_user_definitions.h"

/*""FUNC COMMENT""***************************************************
* Module outline: RTC periodic interrupt processing
*-------------------------------------------------------------------
* Declaration	: void Interrupt_RTC_PRD(void)
*-------------------------------------------------------------------
* Function		: Interrupt processing function for RTC
*-------------------------------------------------------------------
* Argument		: Nothing
*-------------------------------------------------------------------
* Return value	: Nothing
*-------------------------------------------------------------------
* Input			: 
* Output		: 
*-------------------------------------------------------------------
* Use function	: rpdl_RTC_Periodic_callback_func()
*-------------------------------------------------------------------
* Notes			: 
*-------------------------------------------------------------------
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FUNC COMMENT END""**********************************************/
#if FAST_INTC_VECTOR == VECT_RTC_PRD
__fast_interrupt void Interrupt_RTC_PRD(void)
#else
#pragma vector = VECT_RTC_PRD
__interrupt void Interrupt_RTC_PRD(void)
#endif
{
  /* Call the user function */
  if (rpdl_RTC_Periodic_callback_func != PDL_NO_FUNC)
  {
    rpdl_RTC_Periodic_callback_func();
  }
}

/*""FUNC COMMENT""***************************************************
* Module outline: RTC alarm interrupt processing
*-------------------------------------------------------------------
* Declaration	: void Interrupt_RTC_ALM(void)
*-------------------------------------------------------------------
* Function		: Interrupt processing function for RTC
*-------------------------------------------------------------------
* Argument		: Nothing
*-------------------------------------------------------------------
* Return value	: Nothing
*-------------------------------------------------------------------
* Input			: 
* Output		: 
*-------------------------------------------------------------------
* Use function	: rpdl_RTC_Alarm_callback_func()
*-------------------------------------------------------------------
* Notes			: 
*-------------------------------------------------------------------
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FUNC COMMENT END""**********************************************/
#if FAST_INTC_VECTOR == VECT_RTC_ALM
__fast_interrupt void Interrupt_RTC_ALM(void)
#else
#pragma vector = VECT_RTC_ALM
__interrupt void Interrupt_RTC_ALM(void)
#endif
{
  /* Call the user function */
  if (rpdl_RTC_Alarm_callback_func != PDL_NO_FUNC)
  {
    rpdl_RTC_Alarm_callback_func();
  }
}

/*""FUNC COMMENT""***************************************************
* Module outline: RTC Carry interrupt processing
*-------------------------------------------------------------------
* Declaration	: void Interrupt_RTC_CUP(void)
*-------------------------------------------------------------------
* Function		: Interrupt processing function for RTC
*-------------------------------------------------------------------
* Argument		: Nothing
*-------------------------------------------------------------------
* Return value	: Nothing
*-------------------------------------------------------------------
* Input			: 
* Output		: 
*-------------------------------------------------------------------
* Use function	: 
*-------------------------------------------------------------------
* Notes			: This interrupt is not used.
*-------------------------------------------------------------------
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FUNC COMMENT END""**********************************************/
#if FAST_INTC_VECTOR == VECT_RTC_CUP
__fast_interrupt void Interrupt_RTC_CUP(void)
#else
#pragma vector = VECT_RTC_CUP
__interrupt void Interrupt_RTC_CUP(void)
#endif
{
  /* Disable further requests */
  ICU.IER[IER_RTC_CUP].BIT.IEN_RTC_CUP = 0;
}

/* End of file */
