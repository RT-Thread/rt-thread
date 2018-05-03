/*""FILE COMMENT""*******************************************************
* System Name	: Interrupt program for RX62N
* File Name		: Interrupt_DMAC.c
* Version		: 1.02
* Contents		: Interrupt handlers for the DMAC channels
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

#include "r_pdl_dmac.h"
#include "r_pdl_definitions.h"
#include "r_pdl_user_definitions.h"

/*""FUNC COMMENT""***************************************************
* Module outline : DMAC interrupt processing
*-------------------------------------------------------------------
* Declaration	: void Interrupt_DMACn(void)
*-------------------------------------------------------------------
* Function		: Interrupt processing function for DMAC channel n
*-------------------------------------------------------------------
* Argument		: Nothing
*-------------------------------------------------------------------
* Return value	: Nothing
*-------------------------------------------------------------------
* Input			: 
* Output		: 
*-------------------------------------------------------------------
* Use function	: DMAC_callback_func[n]
*-------------------------------------------------------------------
* Notes			: 
*-------------------------------------------------------------------
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FUNC COMMENT END""**********************************************/

#if FAST_INTC_VECTOR == VECT_DMAC_DMAC0I
__fast_interrupt void Interrupt_DMAC0(void)
#else
#pragma vector = VECT_DMAC_DMAC0I
__interrupt void Interrupt_DMAC0(void)
#endif
{
  /* Call the user function */
  if (rpdl_DMAC_callback_func[0] != PDL_NO_FUNC)
  {
    rpdl_DMAC_callback_func[0]();
  }
}

#if FAST_INTC_VECTOR == VECT_DMAC_DMAC1I
__fast_interrupt void Interrupt_DMAC1(void)
#else
#pragma vector = VECT_DMAC_DMAC1I
__interrupt void Interrupt_DMAC1(void)
#endif
{
  /* Call the user function */
  if (rpdl_DMAC_callback_func[1] != PDL_NO_FUNC)
  {
    rpdl_DMAC_callback_func[1]();
  }
}

#if FAST_INTC_VECTOR == VECT_DMAC_DMAC2I
__fast_interrupt void Interrupt_DMAC2(void)
#else
#pragma vector = VECT_DMAC_DMAC2I
__interrupt void Interrupt_DMAC2(void)
#endif
{
  /* Call the user function */
  if (rpdl_DMAC_callback_func[2] != PDL_NO_FUNC)
  {
    rpdl_DMAC_callback_func[2]();
  }
}

#if FAST_INTC_VECTOR == VECT_DMAC_DMAC3I
__fast_interrupt void Interrupt_DMAC3(void)
#else
#pragma vector = VECT_DMAC_DMAC3I
__interrupt void Interrupt_DMAC3(void)
#endif
{
  /* Call the user function */
  if (rpdl_DMAC_callback_func[3] != PDL_NO_FUNC)
  {
    rpdl_DMAC_callback_func[3]();
  }
}
/* End of file */
