/*""FILE COMMENT""*******************************************************
* System Name	: Interrupt program for RX62N
* File Name		: Interrupt_EXDMAC.c
* Version		: 1.02
* Contents		: Interrupt handlers for the EXDMAC channels
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

#include "r_pdl_exdmac.h"
#include "r_pdl_definitions.h"
#include "r_pdl_user_definitions.h"

/*""FUNC COMMENT""***************************************************
* Module outline : EXDMAC interrupt processing
*-------------------------------------------------------------------
* Declaration	: void Interrupt_EXDMACn(void)
*-------------------------------------------------------------------
* Function		: Interrupt processing function for EXDMAC channel n
*-------------------------------------------------------------------
* Argument		: Nothing
*-------------------------------------------------------------------
* Return value	: Nothing
*-------------------------------------------------------------------
* Input			: 
* Output		: 
*-------------------------------------------------------------------
* Use function	: EXDMAC_callback_func[n]
*-------------------------------------------------------------------
* Notes			: 
*-------------------------------------------------------------------
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FUNC COMMENT END""**********************************************/

#if FAST_INTC_VECTOR == VECT_EXDMAC_EXDMAC0I
__fast_interrupt void Interrupt_EXDMAC0(void)
#else
#pragma vector = VECT_EXDMAC_EXDMAC0I
__interrupt void Interrupt_EXDMAC0(void)
#endif
{
#if defined(DEVICE_PACKAGE_LQFP_100) || defined(DEVICE_PACKAGE_TFLGA_85)
  /* This peripheral is not available on the 100-pin or 85-pin packages */
  nop();
#else
  /* Call the user function */
  if (rpdl_EXDMAC_callback_func[0] != PDL_NO_FUNC)
  {
    rpdl_EXDMAC_callback_func[0]();
  }
#endif
}

#if FAST_INTC_VECTOR == VECT_EXDMAC_EXDMAC1I
__fast_interrupt void Interrupt_EXDMAC1(void)
#else
#pragma vector = VECT_EXDMAC_EXDMAC1I
__interrupt void Interrupt_EXDMAC1(void)
#endif
{
#if defined(DEVICE_PACKAGE_LQFP_100) || defined(DEVICE_PACKAGE_TFLGA_85)
  /* This peripheral is not available on the 100-pin or 85-pin packages */
  nop();
#else
  /* Call the user function */
  if (rpdl_EXDMAC_callback_func[1] != PDL_NO_FUNC)
  {
    rpdl_EXDMAC_callback_func[1]();
  }
#endif
}

/* End of file */
