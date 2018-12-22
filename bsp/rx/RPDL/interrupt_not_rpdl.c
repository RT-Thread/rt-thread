/*""FILE COMMENT""*******************************************************
* System Name	: Interrupt program for RX62Nxx
* File Name		: Interrupt_not_RPDL.c
* Version		: 1.02
* Contents		: Interrupt handlers for peripherals outside the scope
*				: of RPDL
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

#include "r_pdl_common_defs_RX62Nxx.h"
#include "r_pdl_user_definitions.h"

#if FAST_INTC_VECTOR == VECT_FCU_FIFERR
__fast_interrupt void Interrupt_FIFERR(void)
#else
#pragma vector = VECT_FCU_FIFERR
__interrupt void Interrupt_FIFERR(void)
#endif
{
  /* The user can put their own code here */
  nop();
}

#if FAST_INTC_VECTOR == VECT_FCU_FRDYI
__fast_interrupt void Interrupt_FRDYI(void)
#else
#pragma vector = VECT_FCU_FRDYI
__interrupt void Interrupt_FRDYI(void)
#endif
{
  /* The user can put their own code here */
  nop();
}

#if FAST_INTC_VECTOR == VECT_ETHER_EINT
__fast_interrupt void Interrupt_EINT(void)
#else
#pragma vector = VECT_ETHER_EINT
__interrupt void Interrupt_EINT(void)
#endif
{
  /* The user can put their own code here */
  nop();
}

#if FAST_INTC_VECTOR == VECT_USB0_D0FIFO0
__fast_interrupt void Interrupt_D0FIFO0(void)
#else
#pragma vector = VECT_USB0_D0FIFO0
__interrupt void Interrupt_D0FIFO0(void)
#endif
{
  /* The user can put their own code here */
  nop();
}

#if FAST_INTC_VECTOR == VECT_USB0_D1FIFO0
__fast_interrupt void Interrupt_D1FIFO0(void)
#else
#pragma vector = VECT_USB0_D1FIFO0
__interrupt void Interrupt_D1FIFO0(void)
#endif
{
  /* The user can put their own code here */
  nop();
}

#if FAST_INTC_VECTOR == VECT_USB0_USBI0
__fast_interrupt void Interrupt_USBI0(void)
#else
#pragma vector = VECT_USB0_USBI0
__interrupt void Interrupt_USBI0(void)
#endif
{
  /* The user can put their own code here */
  nop();
}

#if FAST_INTC_VECTOR == VECT_USB_USBR0
__fast_interrupt void Interrupt_USBR0(void)
#else
#pragma vector = VECT_USB_USBR0
__interrupt void Interrupt_USBR0(void)
#endif
{
  /* The user can put their own code here */
  nop();
}

#if FAST_INTC_VECTOR == VECT_USB1_D0FIFO1
__fast_interrupt void Interrupt_D0FIFO1(void)
#else
#pragma vector = VECT_USB1_D0FIFO1
__interrupt void Interrupt_D0FIFO1(void)
#endif
{
  /* The user can put their own code here */
  nop();
}

#if FAST_INTC_VECTOR == VECT_USB1_D1FIFO1
__fast_interrupt void Interrupt_D1FIFO1(void)
#else
#pragma vector = VECT_USB1_D1FIFO1
__interrupt void Interrupt_D1FIFO1(void)
#endif
{
  /* The user can put their own code here */
  nop();
}

#if FAST_INTC_VECTOR == VECT_USB1_USBI1
__fast_interrupt void Interrupt_USBI1(void)
#else
#pragma vector = VECT_USB1_USBI1
__interrupt void Interrupt_USBI1(void)
#endif
{
  /* The user can put their own code here */
  nop();
}

#if FAST_INTC_VECTOR == VECT_USB_USBR1
__fast_interrupt void Interrupt_USBR1(void)
#else
#pragma vector = VECT_USB_USBR1
__interrupt void Interrupt_USBR1(void)
#endif
{
  /* The user can put their own code here */
  nop();
}

#if FAST_INTC_VECTOR == VECT_CAN0_ERS0
__fast_interrupt void Interrupt_ERS0(void)
#else
#pragma vector = VECT_CAN0_ERS0
__interrupt void Interrupt_ERS0(void)
#endif
{
  /* The user can put their own code here */
  nop();
}

#if FAST_INTC_VECTOR == VECT_CAN0_RXF0
__fast_interrupt void Interrupt_RXF0(void)
#else
#pragma vector = VECT_CAN0_RXF0
__interrupt void Interrupt_RXF0(void)
#endif
{
  /* The user can put their own code here */
  nop();
}

#if FAST_INTC_VECTOR == VECT_CAN0_TXF0
__fast_interrupt void Interrupt_TXF0(void)
#else
#pragma vector = VECT_CAN0_TXF0
__interrupt void Interrupt_TXF0(void)
#endif
{
  /* The user can put their own code here */
  nop();
}

#if FAST_INTC_VECTOR == VECT_CAN0_RXM0
__fast_interrupt void Interrupt_RXM0(void)
#else
#pragma vector = VECT_CAN0_RXM0
__interrupt void Interrupt_RXM0(void)
#endif
{
  /* The user can put their own code here */
  nop();
}

#if FAST_INTC_VECTOR == VECT_CAN0_TXM0
__fast_interrupt void Interrupt_TXM0(void)
#else
#pragma vector = VECT_CAN0_TXM0
__interrupt void Interrupt_TXM0(void)
#endif
{
  /* The user can put their own code here */
  nop();
}

/* End of file */
