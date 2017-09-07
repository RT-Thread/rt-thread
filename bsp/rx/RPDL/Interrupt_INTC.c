/* Adapted for use with IAR Embedded Workbench */
/*""FILE COMMENT""*******************************************************
* System Name   : Interrupt program for RX62Nxx
* File Name     : Interrupt_INTC.c
* Version       : 1.02
* Contents      : Interrupt handlers for the external interrupts
* Customer      :
* Model         :
* Order         :
* CPU           : RX
* Compiler      : RXC
* OS            : Nothing
* Programmer    :
* Note          :
************************************************************************
* Copyright, 2011. Renesas Electronics Corporation
* and Renesas Solutions Corporation
************************************************************************
* History       : 2011.04.08
*               : Ver 1.02
*               : CS-5 release.
*""FILE COMMENT END""**************************************************/

#include "r_pdl_intc.h"
#include "r_pdl_definitions.h"
#include "r_pdl_user_definitions.h"

/* External functions */
extern void PowerON_Reset_PC(void);
extern void rpdl_ADC_10_Start(void);

/* CMT control register definition */
#define CMSTR_ADDRESS(a) ( (volatile uint16_t *)&CMT.CMSTR0 + ( (0x10u * (a >> 1)) / sizeof(uint16_t)) )

/*""FUNC COMMENT""***************************************************
* Module outline: External interrupt processing
*-------------------------------------------------------------------
* Declaration   : void Interrupt_XXXX(void)
*-------------------------------------------------------------------
* Function      : Interrupt processing function for External interrupts
*-------------------------------------------------------------------
* Argument      : Nothing
*-------------------------------------------------------------------
* Return value  : Nothing
*------------------------------------------------------------------
* Input         :
* Output        :
*-------------------------------------------------------------------
* Use function  : rpdl_INTC_callback_func[n]()
*-------------------------------------------------------------------
* Notes         :
*-------------------------------------------------------------------
* History       : 2011.04.08
*               : Ver 1.02
*               : CS-5 release.
*""FUNC COMMENT END""**********************************************/

#if FAST_INTC_VECTOR == VECT_ICU_IRQ0
__fast_interrupt void Interrupt_IRQ0(void)
#else
#pragma vector = VECT_ICU_IRQ0
__interrupt void Interrupt_IRQ0(void)
#endif
{
  /* Call the user function */
  if (rpdl_INTC_callback_func[PDL_INTC_IRQ0] != PDL_NO_FUNC)
  {
    rpdl_INTC_callback_func[PDL_INTC_IRQ0]();
  }
}

#if FAST_INTC_VECTOR == VECT_ICU_IRQ1
__fast_interrupt void Interrupt_IRQ1(void)
#else
#pragma vector = VECT_ICU_IRQ1
__interrupt void Interrupt_IRQ1(void)
#endif
{
  /* Call the user function */
  if (rpdl_INTC_callback_func[PDL_INTC_IRQ1] != PDL_NO_FUNC)
  {
    rpdl_INTC_callback_func[PDL_INTC_IRQ1]();
  }
}

#if FAST_INTC_VECTOR == VECT_ICU_IRQ2
__fast_interrupt void Interrupt_IRQ2(void)
#else
#pragma vector = VECT_ICU_IRQ2
__interrupt void Interrupt_IRQ2(void)
#endif
{
  /* Call the user function */
  if (rpdl_INTC_callback_func[PDL_INTC_IRQ2] != PDL_NO_FUNC)
  {
    rpdl_INTC_callback_func[PDL_INTC_IRQ2]();
  }
}

#if FAST_INTC_VECTOR == VECT_ICU_IRQ3
__fast_interrupt void Interrupt_IRQ3(void)
#else
#pragma vector = VECT_ICU_IRQ3
__interrupt void Interrupt_IRQ3(void)
#endif
{
  /* Call the user function */
  if (rpdl_INTC_callback_func[PDL_INTC_IRQ3] != PDL_NO_FUNC)
  {
    rpdl_INTC_callback_func[PDL_INTC_IRQ3]();
  }
}

#if FAST_INTC_VECTOR == VECT_ICU_IRQ4
__fast_interrupt void Interrupt_IRQ4(void)
#else
#pragma vector = VECT_ICU_IRQ4
__interrupt void Interrupt_IRQ4(void)
#endif
{
  /* Call the user function */
  if (rpdl_INTC_callback_func[PDL_INTC_IRQ4] != PDL_NO_FUNC)
  {
    rpdl_INTC_callback_func[PDL_INTC_IRQ4]();
  }
}

#if FAST_INTC_VECTOR == VECT_ICU_IRQ5
__fast_interrupt void Interrupt_IRQ5(void)
#else
#pragma vector = VECT_ICU_IRQ5
__interrupt void Interrupt_IRQ5(void)
#endif
{
#ifdef DEVICE_PACKAGE_TFLGA_85
  /* This pin is not available on the 85-pin package */
  nop();
#else
  /* Call the user function */
  if (rpdl_INTC_callback_func[PDL_INTC_IRQ5] != PDL_NO_FUNC)
  {
    rpdl_INTC_callback_func[PDL_INTC_IRQ5]();
  }
#endif
}

#if FAST_INTC_VECTOR == VECT_ICU_IRQ6
__fast_interrupt void Interrupt_IRQ6(void)
#else
#pragma vector = VECT_ICU_IRQ6
__interrupt void Interrupt_IRQ6(void)
#endif
{
#ifdef DEVICE_PACKAGE_TFLGA_85
  /* This pin is not available on the 85-pin package */
  nop();
#else
  /* Call the user function */
  if (rpdl_INTC_callback_func[PDL_INTC_IRQ6] != PDL_NO_FUNC)
  {
    rpdl_INTC_callback_func[PDL_INTC_IRQ6]();
  }
#endif
}

#if FAST_INTC_VECTOR == VECT_ICU_IRQ7
__fast_interrupt void Interrupt_IRQ7(void)
#else
#pragma vector = VECT_ICU_IRQ7
__interrupt void Interrupt_IRQ7(void)
#endif
{
#ifdef DEVICE_PACKAGE_TFLGA_85
  /* This pin is not available on the 85-pin package */
  nop();
#else
  /* Call the user function */
  if (rpdl_INTC_callback_func[PDL_INTC_IRQ7] != PDL_NO_FUNC)
  {
    rpdl_INTC_callback_func[PDL_INTC_IRQ7]();
  }
#endif
}

#if FAST_INTC_VECTOR == VECT_ICU_IRQ8
__fast_interrupt void Interrupt_IRQ8(void)
#else
#pragma vector = VECT_ICU_IRQ8
__interrupt void Interrupt_IRQ8(void)
#endif
{
  /* Call the user function */
  if (rpdl_INTC_callback_func[PDL_INTC_IRQ8] != PDL_NO_FUNC)
  {
    rpdl_INTC_callback_func[PDL_INTC_IRQ8]();
  }
}

#if FAST_INTC_VECTOR == VECT_ICU_IRQ9
__fast_interrupt void Interrupt_IRQ9(void)
#else
#pragma vector = VECT_ICU_IRQ9
__interrupt void Interrupt_IRQ9(void)
#endif
{
  /* Call the user function */
  if (rpdl_INTC_callback_func[PDL_INTC_IRQ9] != PDL_NO_FUNC)
  {
    rpdl_INTC_callback_func[PDL_INTC_IRQ9]();
  }
}

#if FAST_INTC_VECTOR == VECT_ICU_IRQ10
__fast_interrupt void Interrupt_IRQ10(void)
#else
#pragma vector = VECT_ICU_IRQ10
__interrupt void Interrupt_IRQ10(void)
#endif
{
  /* Call the user function */
  if (rpdl_INTC_callback_func[PDL_INTC_IRQ10] != PDL_NO_FUNC)
  {
    rpdl_INTC_callback_func[PDL_INTC_IRQ10]();
  }
}

#if FAST_INTC_VECTOR == VECT_ICU_IRQ11
__fast_interrupt void Interrupt_IRQ11(void)
#else
#pragma vector = VECT_ICU_IRQ11
__interrupt void Interrupt_IRQ11(void)
#endif
{
  /* Call the user function */
  if (rpdl_INTC_callback_func[PDL_INTC_IRQ11] != PDL_NO_FUNC)
  {
    rpdl_INTC_callback_func[PDL_INTC_IRQ11]();
  }
}

#if FAST_INTC_VECTOR == VECT_ICU_IRQ12
__fast_interrupt void Interrupt_IRQ12(void)
#else
#pragma vector = VECT_ICU_IRQ12
__interrupt void Interrupt_IRQ12(void)
#endif
{
  /* Call the user function */
  if (rpdl_INTC_callback_func[PDL_INTC_IRQ12] != PDL_NO_FUNC)
  {
    rpdl_INTC_callback_func[PDL_INTC_IRQ12]();
  }
}

#if FAST_INTC_VECTOR == VECT_ICU_IRQ13
__fast_interrupt void Interrupt_IRQ13(void)
#else
#pragma vector = VECT_ICU_IRQ13
__interrupt void Interrupt_IRQ13(void)
#endif
{
  /* Call the user function */
  if (rpdl_INTC_callback_func[PDL_INTC_IRQ13] != PDL_NO_FUNC)
  {
    rpdl_INTC_callback_func[PDL_INTC_IRQ13]();
  }
}

#if FAST_INTC_VECTOR == VECT_ICU_IRQ14
__fast_interrupt void Interrupt_IRQ14(void)
#else
#pragma vector = VECT_ICU_IRQ14
__interrupt void Interrupt_IRQ14(void)
#endif
{
  /* Call the user function */
  if (rpdl_INTC_callback_func[PDL_INTC_IRQ14] != PDL_NO_FUNC)
  {
    rpdl_INTC_callback_func[PDL_INTC_IRQ14]();
  }
}

#if FAST_INTC_VECTOR == VECT_ICU_IRQ15
__fast_interrupt void Interrupt_IRQ15(void)
#else
#pragma vector = VECT_ICU_IRQ15
__interrupt void Interrupt_IRQ15(void)
#endif
{
  /* Call the user function */
  if (rpdl_INTC_callback_func[PDL_INTC_IRQ15] != PDL_NO_FUNC)
  {
    rpdl_INTC_callback_func[PDL_INTC_IRQ15]();
  }
}

/*""FUNC COMMENT""***************************************************
* Module outline: Software interrupt processing
*-------------------------------------------------------------------
* Declaration   : void Interrupt_SWINT(void)
*-------------------------------------------------------------------
* Function      : Interrupt processing function for the software interrupt
*-------------------------------------------------------------------
* Argument      : Nothing
*-------------------------------------------------------------------
* Return value  : Nothing
*------------------------------------------------------------------
* Input         :
* Output        :
*-------------------------------------------------------------------
* Use function  : rpdl_INTC_callback_func[PDL_INTC_SWINT]()
*-------------------------------------------------------------------
* Notes         :
*-------------------------------------------------------------------
* History       : 2011.04.08
*               : Ver 1.02
*               : CS-5 release.
*""FUNC COMMENT END""**********************************************/

/*""FUNC COMMENT""***************************************************
* Module outline: Break interrupt processing
*-------------------------------------------------------------------
* Declaration   : void Interrupt_BRK(void)
*-------------------------------------------------------------------
* Function      : Interrupt processing function for the break interrupt
*-------------------------------------------------------------------
* Argument      : Nothing
*-------------------------------------------------------------------
* Return value  : Nothing
*------------------------------------------------------------------
* Input         :
* Output        :
*-------------------------------------------------------------------
* Use function  :
*-------------------------------------------------------------------
* Notes         :
*-------------------------------------------------------------------
* History       : 2011.04.08
*               : Ver 1.02
*               : CS-5 release.
*""FUNC COMMENT END""**********************************************/
#if 0
#pragma vector = 0
__interrupt void Interrupt_BRK(void)
{
  uint32_t * vector_location;
  volatile uint32_t * stacked_psw_ptr;
  uint32_t psw_copy;
  switch (rpdl_INTC_brk_command)
  {
  case BRK_START_ADC_10:
    rpdl_ADC_10_Start();
    break;
  case BRK_START_ADC_10_AND_SLEEP:
    rpdl_ADC_10_Start();
    /* Prevent all-module clock stop */
    SYSTEM.MSTPCRA.BIT.ACSE = 0;
    /* Select sleep or all-module clock stop */
    SYSTEM.SBYCR.BIT.SSBY = 0;
    /* Prevent out-of-order execution */
    while (SYSTEM.SBYCR.BIT.SSBY != 0);
    wait();
    break;
  case BRK_SLEEP:
    /* Prevent all-module clock stop */
    SYSTEM.MSTPCRA.BIT.ACSE = 0;
    /* Select sleep or all-module clock stop */
    SYSTEM.SBYCR.BIT.SSBY = 0;
    /* Prevent out-of-order execution */
    while (SYSTEM.SBYCR.BIT.SSBY != 0);
    wait();
    break;
  case BRK_ALL_MODULE_CLOCK_STOP:
    /* Select sleep or all-module clock stop */
    SYSTEM.SBYCR.BIT.SSBY = 0;
    /* Prevent out-of-order execution */
    while (SYSTEM.SBYCR.BIT.SSBY != 0);
    wait();
    break;
  case BRK_STANDBY:
    /* Prevent deep standby mode */
    SYSTEM.DPSBYCR.BIT.DPSBY = 0;
    /* Select standby mode */
    SYSTEM.SBYCR.BIT.SSBY = 1;
    /* Prevent out-of-order execution */
    while (SYSTEM.SBYCR.BIT.SSBY != 1);
    wait();
    break;
  case BRK_DEEP_STANDBY:
    /* Stop the RAM clock */
    SYSTEM.MSTPCRC.BIT.MSTPC0 = 1;
    SYSTEM.MSTPCRC.BIT.MSTPC1 = 1;
    /* Select deep standby mode */
    SYSTEM.DPSBYCR.BIT.DPSBY = 1;
    /* Select standby mode */
    SYSTEM.SBYCR.BIT.SSBY = 1;
    /* Prevent out-of-order execution */
    while (SYSTEM.SBYCR.BIT.SSBY != 1);
    wait();
    break;
  case BRK_LOAD_FINTV_REGISTER:
    /* Find the start of the maskable interrupt vector table */
    vector_location = (uint32_t *)get_intb();
    /* Move to the location of the address of the selected interrupt */
    vector_location += ICU.FIR.BIT.FVCT;
    /* Store the address of this vector in the FINTV register */
    set_fintv((__fast_int_f)*vector_location);
    break;
  case BRK_WRITE_IPL:
    /* Find the stacked PSW */
    stacked_psw_ptr = (uint32_t *)(rpdl_INTC_saved_isp) - 1;
    /* Read the stacked PSW */
    psw_copy = *stacked_psw_ptr;
    /* Clear the IPL bits */
    psw_copy &= (uint32_t)(INV_BIT_27 & INV_BIT_26 & INV_BIT_25 & INV_BIT_24);
    /* Modify the IPL bits */
    psw_copy |= (uint32_t)(rpdl_INTC_brk_data8 << 24);
    /* Modify the saved IPL */
    *stacked_psw_ptr = psw_copy;
    break;
  case BRK_CMT_START:
    /* Set STRn to 1 */
    *(CMSTR_ADDRESS(rpdl_INTC_brk_data8)) |= (uint16_t)((rpdl_INTC_brk_data8 & 0x01u) + 1);
    break;
  case BRK_CMT_STOP:
    /* Set STRn to 0 */
    *(CMSTR_ADDRESS(rpdl_INTC_brk_data8)) &= (uint16_t)(0x2u >> (rpdl_INTC_brk_data8 & 0x01u));
    break;
  default:
    /* This must never occur */
    break;
  }
  rpdl_INTC_brk_command = BRK_NO_COMMAND;
}
     #endif
/* Exception (Privileged Instruction) */
__interrupt void __privileged_handler(void)
{
  if (rpdl_INTC_callback_func[PDL_INTC_PRIVILEGED] != PDL_NO_FUNC)
  {
    /* Call the user function */
    rpdl_INTC_callback_func[PDL_INTC_PRIVILEGED]();
  }
}

/* Exception (Undefined Instruction) */
__interrupt void __undefined_handler(void)
{
  if (rpdl_INTC_callback_func[PDL_INTC_UNDEFINED] != PDL_NO_FUNC)
  {
    /* Call the user function */
    rpdl_INTC_callback_func[PDL_INTC_UNDEFINED]();
  }
}

/* Exception(Floating Point) */
__interrupt void __floating_point_handler(void)
{
  if (rpdl_INTC_callback_func[PDL_INTC_FLOATING_POINT] != PDL_NO_FUNC)
  {
    /* Call the user function */
    rpdl_INTC_callback_func[PDL_INTC_FLOATING_POINT]();
  }
}

__interrupt void __NMI_handler(void)
{
  if (rpdl_INTC_callback_func[PDL_INTC_NMI] != PDL_NO_FUNC)
  {
    /* Call the user function */
    rpdl_INTC_callback_func[PDL_INTC_NMI]();
  }
}

/* End of file */
