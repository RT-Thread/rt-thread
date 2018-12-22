/*""FILE COMMENT""*******************************************************
* System Name	: Interrupt program for RX62Nxx
* File Name 	: Interrupt_ADC_10.c
* Version		: 1.02
* Contents		: Interrupt handlers for the ADC units
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

#include "r_pdl_adc_10.h"
#include "r_pdl_definitions.h"
#include "r_pdl_user_definitions.h"

/*""FUNC COMMENT""***************************************************
* Module outline: ADC interrupt processing
*-------------------------------------------------------------------
* Declaration	: void Interrupt_ADCn(void)
*-------------------------------------------------------------------
* Function		: Interrupt processing function for ADC unit n
*-------------------------------------------------------------------
* Argument		: Nothing
*-------------------------------------------------------------------
* Return value	: Nothing
*-------------------------------------------------------------------
* Input			: 
* Output		: 
*-------------------------------------------------------------------
* Use function	: ADC_callback_func[n]()
*-------------------------------------------------------------------
* Notes			: 
*-------------------------------------------------------------------
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FUNC COMMENT END""**********************************************/

#if FAST_INTC_VECTOR == VECT_AD0_ADI0
__fast_interrupt void Interrupt_ADC0(void)
#else
#pragma vector = VECT_AD0_ADI0
__interrupt void Interrupt_ADC0(void)
#endif
{
  /* Call the user function */
  if (rpdl_ADC_10_callback_func[0] != PDL_NO_FUNC)
  {
    rpdl_ADC_10_callback_func[0]();
  }
}

#if FAST_INTC_VECTOR == VECT_AD1_ADI1
__fast_interrupt void Interrupt_ADC1(void)
#else
#pragma vector = VECT_AD1_ADI1
__interrupt void Interrupt_ADC1(void)
#endif
{
  /* Call the user function */
  if (rpdl_ADC_10_callback_func[1] != PDL_NO_FUNC)
  {
    rpdl_ADC_10_callback_func[1]();
  }
}

/* End of file */
