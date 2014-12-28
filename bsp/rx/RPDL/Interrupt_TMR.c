/*""FILE COMMENT""*******************************************************
* System Name	: Interrupt program for RX62Nxx
* File Name		: Interrupt_TMR.c
* Version		: 1.02
* Contents		: Interrupt handlers for the Timer units
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

#include "r_pdl_tmr.h"
#include "r_pdl_definitions.h"
#include "r_pdl_user_definitions.h"

/*""FUNC COMMENT""***************************************************
* Module outline : Timer interrupt processing
*-------------------------------------------------------------------
* Declaration	: void Interrupt_TMRn_XXX(void)
*-------------------------------------------------------------------
* Function		: Interrupt processing function for Timer TMR channel n
*-------------------------------------------------------------------
* Argument		: Nothing
*-------------------------------------------------------------------
* Return value	: Nothing
*-------------------------------------------------------------------
* Input			: 
* Output		: 
*-------------------------------------------------------------------
* Use function	: R_TmrOverflowFunc[n](), R_TmrCMAFunc[n]() or
*				: R_TmrCMBFunc[n]() as appropriate.
*-------------------------------------------------------------------
* Notes			: 
*-------------------------------------------------------------------
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FUNC COMMENT END""**********************************************/

#if FAST_INTC_VECTOR == VECT_TMR0_CMIA0
__fast_interrupt void Interrupt_TMR0_CMA(void)
#else
#pragma vector = VECT_TMR0_CMIA0
__interrupt void Interrupt_TMR0_CMA(void)
#endif
{
  /* Call the user function? */
  if (rpdl_TMR_CMA_callback_func[0] != PDL_NO_FUNC)
  {
    /* Call the user function */
    rpdl_TMR_CMA_callback_func[0]();
  }
}

#if FAST_INTC_VECTOR == VECT_TMR0_CMIB0
__fast_interrupt void Interrupt_TMR0_CMB(void)
#else
#pragma vector = VECT_TMR0_CMIB0
__interrupt void Interrupt_TMR0_CMB(void)
#endif
{
  if (rpdl_TMR_one_shot[0] != false)
  {
    /* Channel mode? */
    if (rpdl_TMR_one_shot[0] == CHANNEL_MODE)
    {
      /* Stop the channel 0 clock input */
      TMR0.TCCR.BYTE = 0x00u;
    }
    /* Unit mode? */
    else
    {
      /* Stop the channel 1 clock input */
      TMR1.TCCR.BYTE = 0x00u;
    }

    rpdl_TMR_one_shot[0] = false;

    /* Clear the interrupt request flag (the timer may have set it again) */
    ICU.IR[VECT_TMR0_CMIB0].BIT.IR = 0;
  }

  /* Call the user function? */
  if (rpdl_TMR_CMB_callback_func[0] != PDL_NO_FUNC)
  {
    rpdl_TMR_CMB_callback_func[0]();
  }
}

#if FAST_INTC_VECTOR == VECT_TMR0_OVI0
__fast_interrupt void Interrupt_TMR0_OV(void)
#else
#pragma vector = VECT_TMR0_OVI0
__interrupt void Interrupt_TMR0_OV(void)
#endif
{
  /* Call the user function */
  if (rpdl_TMR_Overflow_callback_func[0] != PDL_NO_FUNC)
  {
    rpdl_TMR_Overflow_callback_func[0]();
  }
}

#if FAST_INTC_VECTOR == VECT_TMR1_CMIA1
__fast_interrupt void Interrupt_TMR1_CMA(void)
#else
#pragma vector = VECT_TMR1_CMIA1
__interrupt void Interrupt_TMR1_CMA(void)
#endif
{
  /* Call the user function? */
  if (rpdl_TMR_CMA_callback_func[1] != PDL_NO_FUNC)
  {
    /* Call the user function */
    rpdl_TMR_CMA_callback_func[1]();
  }
}

#if FAST_INTC_VECTOR == VECT_TMR1_CMIB1
__fast_interrupt void Interrupt_TMR1_CMB(void)
#else
#pragma vector = VECT_TMR1_CMIB1
__interrupt void Interrupt_TMR1_CMB(void)
#endif
{
  if (rpdl_TMR_one_shot[1] != false)
  {
    /* Stop the channel 1 clock input */
    TMR1.TCCR.BYTE = 0x00u;

    rpdl_TMR_one_shot[1] = false;

    /* Clear the interrupt request flag (the timer may have set it again) */
    ICU.IR[VECT_TMR1_CMIB1].BIT.IR = 0u;
  }

  /* Call the user function? */
  if (rpdl_TMR_CMB_callback_func[1] != PDL_NO_FUNC)
  {
    rpdl_TMR_CMB_callback_func[1]();
  }
}

#if FAST_INTC_VECTOR == VECT_TMR1_OVI1
__fast_interrupt void Interrupt_TMR1_OV(void)
#else
#pragma vector = VECT_TMR1_OVI1
__interrupt void Interrupt_TMR1_OV(void)
#endif
{
  /* Call the user function */
  if (rpdl_TMR_Overflow_callback_func[1] != PDL_NO_FUNC)
  {
    rpdl_TMR_Overflow_callback_func[1]();
  }
}

#if FAST_INTC_VECTOR == VECT_TMR2_CMIA2
__fast_interrupt void Interrupt_TMR2_CMA(void)
#else
#pragma vector = VECT_TMR2_CMIA2
__interrupt void Interrupt_TMR2_CMA(void)
#endif
{
  /* Call the user function? */
  if (rpdl_TMR_CMA_callback_func[2] != PDL_NO_FUNC)
  {
    /* Call the user function */
    rpdl_TMR_CMA_callback_func[2]();
  }
}

#if FAST_INTC_VECTOR == VECT_TMR2_CMIB2
__fast_interrupt void Interrupt_TMR2_CMB(void)
#else
#pragma vector = VECT_TMR2_CMIB2
__interrupt void Interrupt_TMR2_CMB(void)
#endif
{
  if (rpdl_TMR_one_shot[2] != false)
  {
    /* Channel mode? */
    if (rpdl_TMR_one_shot[2] == CHANNEL_MODE)
    {
      /* Stop the channel 2 clock input */
      TMR2.TCCR.BYTE = 0x00u;
    }
    /* Unit mode? */
    else
    {
      /* Stop the channel 3 clock input */
      TMR3.TCCR.BYTE = 0x00u;
    }

    rpdl_TMR_one_shot[2] = false;

    /* Clear the interrupt request flag (the timer may have set it again) */
    ICU.IR[VECT_TMR2_CMIB2].BIT.IR = 0;
  }

  /* Call the user function? */
  if (rpdl_TMR_CMB_callback_func[2] != PDL_NO_FUNC)
  {
    rpdl_TMR_CMB_callback_func[2]();
  }
}

#if FAST_INTC_VECTOR == VECT_TMR2_OVI2
__fast_interrupt void Interrupt_TMR2_OV(void)
#else
#pragma vector = VECT_TMR2_OVI2
__interrupt void Interrupt_TMR2_OV(void)
#endif
{
  /* Call the user function */
  if (rpdl_TMR_Overflow_callback_func[2] != PDL_NO_FUNC)
  {
    rpdl_TMR_Overflow_callback_func[2]();
  }
}

#if FAST_INTC_VECTOR == VECT_TMR3_CMIA3
__fast_interrupt void Interrupt_TMR3_CMA(void)
#else
#pragma vector = VECT_TMR3_CMIA3
__interrupt void Interrupt_TMR3_CMA(void)
#endif
{
  /* Call the user function? */
  if (rpdl_TMR_CMA_callback_func[3] != PDL_NO_FUNC)
  {
    /* Call the user function */
    rpdl_TMR_CMA_callback_func[3]();
  }
}

#if FAST_INTC_VECTOR == VECT_TMR3_CMIB3
__fast_interrupt void Interrupt_TMR3_CMB(void)
#else
#pragma vector = VECT_TMR3_CMIB3
__interrupt void Interrupt_TMR3_CMB(void)
#endif
{
  if (rpdl_TMR_one_shot[3] != false)
  {
    /* Stop the channel 3 clock input */
    TMR3.TCCR.BYTE = 0x00u;

    rpdl_TMR_one_shot[3] = false;

    /* Clear the interrupt request flag (the timer may have set it again) */
    ICU.IR[VECT_TMR3_CMIB3].BIT.IR = 0;
  }

  /* Call the user function? */
  if (rpdl_TMR_CMB_callback_func[3] != PDL_NO_FUNC)
  {
    rpdl_TMR_CMB_callback_func[3]();
  }
}

#if FAST_INTC_VECTOR == VECT_TMR3_OVI3
__fast_interrupt void Interrupt_TMR3_OV(void)
#else
#pragma vector = VECT_TMR3_OVI3
__interrupt void Interrupt_TMR3_OV(void)
#endif
{
  /* Call the user function */
  if (rpdl_TMR_Overflow_callback_func[3] != PDL_NO_FUNC)
  {
    rpdl_TMR_Overflow_callback_func[3]();
  }
}
/* End of file */
