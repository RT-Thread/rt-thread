/*""FILE COMMENT""*******************************************************
* System Name	: Interrupt program for RX62N
* File Name		: Interrupt_POE.c
* Version		: 1.02
* Contents		: Interrupt handlers for the Port Output Enable module
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

#include "r_pdl_poe.h"
#include "r_pdl_definitions.h"
#include "r_pdl_user_definitions.h"

/*""FUNC COMMENT""***************************************************
* Module outline : POE interrupt processing
*-------------------------------------------------------------------
* Declaration	: void Interrupt_OEIn(void)
*-------------------------------------------------------------------
* Function		: Interrupt processing function for POE interrupt n
*-------------------------------------------------------------------
* Argument		: Nothing
*-------------------------------------------------------------------
* Return value	: Nothing
*-------------------------------------------------------------------
* Input			: 
* Output		: 
*-------------------------------------------------------------------
* Use function	: POE_callback_func[n]
*-------------------------------------------------------------------
* Notes			: 
*-------------------------------------------------------------------
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FUNC COMMENT END""**********************************************/

#if FAST_INTC_VECTOR == VECT_POE_OEI1
__fast_interrupt void Interrupt_OEI1(void)
#else
#pragma vector = VECT_POE_OEI1
__interrupt void Interrupt_OEI1(void)
#endif
{
#ifdef DEVICE_PACKAGE_TFLGA_85
  /* This peripheral is not available on the 85-pin package */
  nop();
#else
  /* Call the user function */
  if (rpdl_POE_callback_func[0] != PDL_NO_FUNC)
  {
    rpdl_POE_callback_func[0]();
  }
#endif
}

#if FAST_INTC_VECTOR == VECT_POE_OEI2
__fast_interrupt void Interrupt_OEI2(void)
#else
#pragma vector = VECT_POE_OEI2
__interrupt void Interrupt_OEI2(void)
#endif
{
#ifdef DEVICE_PACKAGE_TFLGA_85
  /* This peripheral is not available on the 85-pin package */
  nop();
#else
  /* Call the user function */
  if (rpdl_POE_callback_func[2] != PDL_NO_FUNC)
  {
    rpdl_POE_callback_func[2]();
  }
#endif
}

#if FAST_INTC_VECTOR == VECT_POE_OEI3
__fast_interrupt void Interrupt_OEI3(void)
#else
#pragma vector = VECT_POE_OEI3
__interrupt void Interrupt_OEI3(void)
#endif
{
#ifdef DEVICE_PACKAGE_TFLGA_85
  /* This peripheral is not available on the 85-pin package */
  nop();
#else
  /* Call the user function */
  if (rpdl_POE_callback_func[1] != PDL_NO_FUNC)
  {
    rpdl_POE_callback_func[1]();
  }
#endif
}

#if FAST_INTC_VECTOR == VECT_POE_OEI4
__fast_interrupt void Interrupt_OEI4(void)
#else
#pragma vector = VECT_POE_OEI4
__interrupt void Interrupt_OEI4(void)
#endif
{
#ifdef DEVICE_PACKAGE_TFLGA_85
  /* This peripheral is not available on the 85-pin package */
  nop();
#else
  /* Call the user function */
  if (rpdl_POE_callback_func[3] != PDL_NO_FUNC)
  {
    rpdl_POE_callback_func[3]();
  }
#endif
}

/* End of file */
