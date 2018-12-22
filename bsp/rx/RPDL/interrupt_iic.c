/*""FILE COMMENT""*******************************************************
* System Name	: Interrupt program for RX62Nx
* File Name		: Interrupt_IIC.c
* Version		: 1.02
* Contents		: Interrupt handlers for all IIC channels
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

#include "r_pdl_iic.h"
#include "r_pdl_definitions.h"
#include "r_pdl_user_definitions.h"

/* For DMAC support */
#define DMCNT_ADDRESS(a) ((volatile uint8_t *)&DMAC0.DMCNT + ((0x40u * a) / sizeof( uint8_t)) )

/* External functions */
extern void Store_detected_address(const uint8_t);

/*""FUNC COMMENT""***************************************************
* Module outline: IICn event interrupt processing
*-------------------------------------------------------------------
* Declaration	: void InterruptIIC_ICEEIn(void)
*-------------------------------------------------------------------
* Function		: 
*-------------------------------------------------------------------
* Argument		: Nothing
*-------------------------------------------------------------------
* Return value	: Nothing
*-------------------------------------------------------------------
* Output		: 
*-------------------------------------------------------------------
* Use function	: 
*-------------------------------------------------------------------
* Notes			: 
*-------------------------------------------------------------------
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FUNC COMMENT END""**********************************************/

#if FAST_INTC_VECTOR == VECT_RIIC0_ICEEI0
__fast_interrupt void Interrupt_IIC_ICEEI0(void)
#else
#pragma vector = VECT_RIIC0_ICEEI0
__interrupt void Interrupt_IIC_ICEEI0(void)
#endif
{
  uint8_t valid_flags;
  volatile uint8_t unwanted_byte;

  /* Read the status register */
  valid_flags = RIIC0.ICSR2.BYTE;

  /* Remove any that are not enabled */
  valid_flags &= RIIC0.ICIER.BYTE;

  /* Remove the transmit and receive flags */
  valid_flags &= 0x1Fu;

  /* Start or Repeated Start detected? */
  if ((valid_flags & BIT_2) != 0x0u)
  {
    /* Decide what to send */
    switch(rpdl_IIC_next_state[0])
    {
    case IIC_MASTER_SEND_SLAVE_ADDRESS_7:
      /* Send the slave address */
      RIIC0.ICDRT = rpdl_IIC_slave_address_lower[0];

      /* Transmit mode? */
      if ((rpdl_IIC_slave_address_lower[0] & BIT_0) == 0)
      {
        rpdl_IIC_current_state[0] = IIC_MASTER_SEND_DATA;
      }
      else
      {
        rpdl_IIC_current_state[0] = IIC_MASTER_START_READ;
      }
      break;
    case IIC_MASTER_SEND_SLAVE_ADDRESS_10a:
      rpdl_IIC_current_state[0] = IIC_MASTER_SEND_SLAVE_ADDRESS_10b;

      /* Send the first part of the slave address */
      RIIC0.ICDRT = rpdl_IIC_slave_address_upper[0];
      break;
    default:
      break;
    }

    /* Were we expecting data? */
    if (rpdl_IIC_current_state[0] == IIC_SLAVE_READ_DATA)
    {
      /* Go back to checking for a device address */
      rpdl_IIC_current_state[0] = IIC_SLAVE_MONITOR;

      /* Disable Start detection */
      RIIC0.ICIER.BIT.STIE = 0;
    }

    /* Clear the flag */
    RIIC0.ICSR2.BIT.START = 0;
  }
  /* NACK detected? */
  else if ((valid_flags & BIT_4) != 0x0u)
  {
    /* Disable NACK interrupt request generation */
    RIIC0.ICIER.BIT.NAKIE = 0;

    /* Failed transmission of data? */
    if (rpdl_IIC_current_state[0] == IIC_MASTER_SEND_DATA)
    {
      /* Decrement the counter */
      rpdl_IIC_tx_counter[0]--;

      /* Call the callback function */
      if (rpdl_IIC_callback_func[0] != PDL_NO_FUNC)
      {
        rpdl_IIC_callback_func[0]();
      }
    }
    /* NACK received from the master? */
    else
    {
      /* Do a dummy read to release SCL */
      unwanted_byte = RIIC0.ICDRR;
    }
  }
  else
  {
    /* Disable all interrupt request generation */
    RIIC0.ICIER.BYTE = 0x00u;

    /* Call the callback function */
    if (rpdl_IIC_callback_func[0] != PDL_NO_FUNC)
    {
      rpdl_IIC_callback_func[0]();
    }
  }
}

#if FAST_INTC_VECTOR == VECT_RIIC1_ICEEI1
__fast_interrupt void Interrupt_IIC_ICEEI1(void)
#else
#pragma vector = VECT_RIIC1_ICEEI1
__interrupt void Interrupt_IIC_ICEEI1(void)
#endif
{
#ifdef DEVICE_PACKAGE_LQFP_100
  /* This channel is not available on the 100-pin package */
  nop();
#else
  uint8_t valid_flags;
  volatile uint8_t unwanted_byte;

  /* Read the status register */
  valid_flags = RIIC1.ICSR2.BYTE;
  /* Remove any that are not enabled */
  valid_flags &= RIIC1.ICIER.BYTE;
  /* Remove the transmit and receive flags */
  valid_flags &= 0x1Fu;

  /* Start or Repeated Start detected? */
  if ((valid_flags & BIT_2) != 0x0u)
  {
    /* Decide what to send */
    switch(rpdl_IIC_next_state[1])
    {
    case IIC_MASTER_SEND_SLAVE_ADDRESS_7:
      /* Send the slave address */
      RIIC1.ICDRT = rpdl_IIC_slave_address_lower[1];

      /* Transmit mode? */
      if ((rpdl_IIC_slave_address_lower[1] & BIT_0) == 0)
      {
        rpdl_IIC_current_state[1] = IIC_MASTER_SEND_DATA;
      }
      else
      {
        rpdl_IIC_current_state[1] = IIC_MASTER_START_READ;
      }
      break;
    case IIC_MASTER_SEND_SLAVE_ADDRESS_10a:
      rpdl_IIC_current_state[1] = IIC_MASTER_SEND_SLAVE_ADDRESS_10b;

      /* Send the first part of the slave address */
      RIIC1.ICDRT = rpdl_IIC_slave_address_upper[1];
      break;
    default:
      break;
    }

    /* Were we expecting data? */
    if (rpdl_IIC_current_state[1] == IIC_SLAVE_READ_DATA)
    {
      /* Go back to checking for a device address */
      rpdl_IIC_current_state[1] = IIC_SLAVE_MONITOR;

      /* Disable Start detection */
      RIIC1.ICIER.BIT.STIE = 0;
    }

    /* Clear the flag */
    RIIC1.ICSR2.BIT.START = 0;
  }
  /* NACK detected? */
  else if ((valid_flags & BIT_4) != 0x0u)
  {
    /* Disable NACK interrupt request generation */
    RIIC1.ICIER.BIT.NAKIE = 0;

    /* Failed transmission of data? */
    if (rpdl_IIC_current_state[1] == IIC_MASTER_SEND_DATA)
    {
      /* Decrement the counter */
      rpdl_IIC_tx_counter[1]--;

      /* Call the callback function */
      if (rpdl_IIC_callback_func[1] != PDL_NO_FUNC)
      {
        rpdl_IIC_callback_func[1]();
      }
    }
    /* NACK received from the master? */
    else
    {
      /* Do a dummy read to release SCL */
      unwanted_byte = RIIC1.ICDRR;
    }
  }
  else
  {
    /* Disable all interrupt request generation */
    RIIC1.ICIER.BYTE = 0x00u;

    /* Call the callback function */
    if (rpdl_IIC_callback_func[1] != PDL_NO_FUNC)
    {
      rpdl_IIC_callback_func[1]();
    }
  }
#endif
}

/*""FUNC COMMENT""***************************************************
* Module outline: IICn receive data interrupt processing
*-------------------------------------------------------------------
* Declaration	: void Interrupt_IIC_ICRXIn(void)
*-------------------------------------------------------------------
* Function		: 
*-------------------------------------------------------------------
* Argument		: Nothing
*-------------------------------------------------------------------
* Return value	: Nothing
*-------------------------------------------------------------------
* Output		: ICDRR, ICIER
*-------------------------------------------------------------------
* Use function	: 
*-------------------------------------------------------------------
* Notes			: 
*-------------------------------------------------------------------
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FUNC COMMENT END""**********************************************/
#if FAST_INTC_VECTOR == VECT_RIIC0_ICRXI0
__fast_interrupt void Interrupt_IIC_ICRXI0(void)
#else
#pragma vector = VECT_RIIC0_ICRXI0
__interrupt void Interrupt_IIC_ICRXI0(void)
#endif
{
  volatile uint8_t unwanted_byte;

  switch (rpdl_IIC_current_state[0])
  {
  case IIC_MASTER_START_READ:
    /* Only one byte to be read? */
    if (rpdl_IIC_rx_threshold[0] == 1)
    {
      /* Prepare to signal a NACK to the slave (ACKBT = 1) */
      RIIC0.ICMR3.BIT.ACKBT = 1;
    }
    rpdl_IIC_current_state[0] = IIC_MASTER_READ_DATA;

    /* Do a dummy read */
    unwanted_byte = RIIC0.ICDRR;
    break;
  case IIC_MASTER_READ_DATA:
    /* Is the last byte about to be read from the slave? */
    if (rpdl_IIC_rx_counter[0] == (rpdl_IIC_rx_threshold[0] - 2))
    {
      /* Prepare to signal a NACK to the slave (ACKBT = 1) */
      RIIC0.ICMR3.BIT.ACKBT = 1;
    }
    /* All data read from the slave? */
    else if (rpdl_IIC_rx_counter[0] == (rpdl_IIC_rx_threshold[0] - 1))
    {
      rpdl_IIC_current_state[0] = IIC_MASTER_WAIT_FOR_STOP;

      /* Enable Stop detection */
      RIIC0.ICIER.BIT.SPIE = 1;

      /* Issue a stop condition */
      RIIC0.ICCR2.BIT.SP = 1;
    }

    /* Store the data byte */
    *rpdl_IIC_rx_data_pointer[0] = RIIC0.ICDRR;

    /* Increment the pointer */
    rpdl_IIC_rx_data_pointer[0]++;

    /* Increment the counter */
    rpdl_IIC_rx_counter[0]++;
    break;
  case IIC_SLAVE_MONITOR:
    /* Note the detected address */
    Store_detected_address(0);

    /* Clear the Start flag */
    RIIC0.ICSR2.BIT.START = 0;

    /* Enable Start detection (in case a Repeated Start arrives) */
    RIIC0.ICIER.BIT.STIE = 1;

    /* Will interrupts be used for the transfers? */
    if (rpdl_IIC_rx_transfer_method[0] == IIC_TRANSFER_CPU)
    {
      rpdl_IIC_current_state[0] = IIC_SLAVE_READ_DATA;
    }
    else
    {
      /* Disable ACK / NACK decisions (RDRFS = 0) */
      RIIC0.ICMR3.BIT.RDRFS = 0;
      /* Select DMAC or DTC transfers */
      if (rpdl_IIC_rx_transfer_method[0] == IIC_TRANSFER_DTC)
      {
        ICU.DTCER[DTCE_RIIC0_ICRXI0].BIT.DTCE = 1;
      }
      else	/* DMAC */
      {
        /* Set DTE = 1 */
        *DMCNT_ADDRESS(rpdl_IIC_rx_dmac_channel[0]) = 0x01u;
      }
      /* Prevent further RX-based interrupts */
      ICU.IPR[IPR_RIIC0_ICRXI0].BIT.IPR = 0;
      rpdl_IIC_current_state[0] = IIC_EXIT_LOOP;
    }

    /* Do a dummy read */
    unwanted_byte = RIIC0.ICDRR;
    break;
  case IIC_SLAVE_READ_DATA:
    /* All data received? */
    if (rpdl_IIC_rx_counter[0] == rpdl_IIC_rx_threshold[0])
    {
      /* Do a dummy read */
      unwanted_byte = RIIC0.ICDRR;

      /* Signal a NACK to the master */
      RIIC0.ICMR3.BIT.ACKBT = 1;
    }
    else
    {
      /* Store the data byte */
      *rpdl_IIC_rx_data_pointer[0] = RIIC0.ICDRR;

      /* Increment the pointer */
      rpdl_IIC_rx_data_pointer[0]++;

      /* Increment the counter */
      rpdl_IIC_rx_counter[0]++;

      /* Signal an ACK to the master */
      RIIC0.ICMR3.BIT.ACKBT = 0;
    }
    break;
  case IIC_SLAVE_SEND_DATA:
    /* Call the callback function */
    if (rpdl_IIC_callback_func[0] != PDL_NO_FUNC)
    {
      rpdl_IIC_callback_func[0]();
    }
    break;
  case IIC_EXIT_LOOP:
    /* This will occur if the DMAC/DTC is being used with a callback */
    /* Call the callback function */
    if (rpdl_IIC_callback_func[0] != PDL_NO_FUNC)
    {
      rpdl_IIC_callback_func[0]();
    }
    break;
  default:
    /* Call the callback function */
    if (rpdl_IIC_callback_func[0] != PDL_NO_FUNC)
    {
      rpdl_IIC_callback_func[0]();
    }
    break;
  }
}

#if FAST_INTC_VECTOR == VECT_RIIC1_ICRXI1
__fast_interrupt void Interrupt_IIC_ICRXI1(void)
#else
#pragma vector = VECT_RIIC1_ICRXI1
__interrupt void Interrupt_IIC_ICRXI1(void)
#endif
{
#ifdef DEVICE_PACKAGE_LQFP_100
  /* This channel is not available on the 100-pin package */
  nop();
#else
  volatile uint8_t unwanted_byte;

  switch (rpdl_IIC_current_state[1])
  {
  case IIC_MASTER_START_READ:
    /* Only one byte to be read? */
    if (rpdl_IIC_rx_threshold[1] == 1)
    {
      /* Prepare to signal a NACK to the slave (ACKBT = 1) */
      RIIC1.ICMR3.BIT.ACKBT = 1;
    }
    rpdl_IIC_current_state[1] = IIC_MASTER_READ_DATA;

    /* Do a dummy read */
    unwanted_byte = RIIC1.ICDRR;
    break;
  case IIC_MASTER_READ_DATA:
    /* Is the last byte about to be read from the slave? */
    if (rpdl_IIC_rx_counter[1] == (rpdl_IIC_rx_threshold[1] - 2))
    {
      /* Prepare to signal a NACK to the slave (ACKBT = 1) */
      RIIC1.ICMR3.BIT.ACKBT = 1;
    }
    /* All data read from the slave? */
    else if (rpdl_IIC_rx_counter[1] == (rpdl_IIC_rx_threshold[1] - 1))
    {
      rpdl_IIC_current_state[1] = IIC_MASTER_WAIT_FOR_STOP;

      /* Enable Stop detection */
      RIIC1.ICIER.BIT.SPIE = 1;

      /* Issue a stop condition */
      RIIC1.ICCR2.BIT.SP = 1;
    }

    /* Store the data byte */
    *rpdl_IIC_rx_data_pointer[1] = RIIC1.ICDRR;

    /* Increment the pointer */
    rpdl_IIC_rx_data_pointer[1]++;

    /* Increment the counter */
    rpdl_IIC_rx_counter[1]++;
    break;
  case IIC_SLAVE_MONITOR:
    /* Note the detected address */
    Store_detected_address(1);

    /* Clear the Start flag */
    RIIC1.ICSR2.BIT.START = 0;

    /* Enable Start detection (in case a Repeated Start arrives) */
    RIIC1.ICIER.BIT.STIE = 1;

    /* Will interrupts be used for the transfers? */
    if (rpdl_IIC_rx_transfer_method[1] == IIC_TRANSFER_CPU)
    {
      rpdl_IIC_current_state[1] = IIC_SLAVE_READ_DATA;
    }
    else
    {
      /* Disable ACK / NACK decisions (RDRFS = 0) */
      RIIC1.ICMR3.BIT.RDRFS = 0;
      /* Select DMAC or DTC transfers */
      if (rpdl_IIC_rx_transfer_method[1] == IIC_TRANSFER_DTC)
      {
        ICU.DTCER[DTCE_RIIC1_ICRXI1].BIT.DTCE = 1;
      }
      else	/* DMAC */
      {
        /* Set DTE = 1 */
        *DMCNT_ADDRESS(rpdl_IIC_rx_dmac_channel[1]) = 0x01u;
      }
      /* Prevent further RX-based interrupts */
      ICU.IPR[IPR_RIIC1_ICRXI1].BIT.IPR = 0;
      rpdl_IIC_current_state[1] = IIC_EXIT_LOOP;
    }

    /* Do a dummy read */
    unwanted_byte = RIIC1.ICDRR;
    break;

  case IIC_SLAVE_READ_DATA:
    /* All data received? */
    if (rpdl_IIC_rx_counter[1] == rpdl_IIC_rx_threshold[1])
    {
      /* Do a dummy read */
      unwanted_byte = RIIC1.ICDRR;

      /* Signal a NACK to the master */
      RIIC1.ICMR3.BIT.ACKBT = 1;
    }
    else
    {
      /* Store the data byte */
      *rpdl_IIC_rx_data_pointer[1] = RIIC1.ICDRR;

      /* Increment the pointer */
      rpdl_IIC_rx_data_pointer[1]++;

      /* Increment the counter */
      rpdl_IIC_rx_counter[1]++;

      /* Signal an ACK to the master */
      RIIC1.ICMR3.BIT.ACKBT = 0;
    }
    break;
  case IIC_SLAVE_SEND_DATA:
    /* Call the callback function */
    if (rpdl_IIC_callback_func[1] != PDL_NO_FUNC)
    {
      rpdl_IIC_callback_func[1]();
    }
    break;
  case IIC_EXIT_LOOP:
    /* This will occur if the DMAC/DTC is being used with a callback */
    /* Call the callback function */
    if (rpdl_IIC_callback_func[1] != PDL_NO_FUNC)
    {
      rpdl_IIC_callback_func[1]();
    }
    break;
  default:
    /* Call the callback function */
    if (rpdl_IIC_callback_func[1] != PDL_NO_FUNC)
    {
      rpdl_IIC_callback_func[1]();
    }
    break;
  }
#endif
}

/*""FUNC COMMENT""***************************************************
* Module outline: IICn transmit data interrupt processing
*-------------------------------------------------------------------
* Declaration	: void Interrupt_IIC_ICTXIn(void)
*-------------------------------------------------------------------
* Function		: 
*-------------------------------------------------------------------
* Argument		: Nothing
*-------------------------------------------------------------------
* Return value	: Nothing
*-------------------------------------------------------------------
* Output		: ICDRT, ICIER
*-------------------------------------------------------------------
* Use function	: 
*-------------------------------------------------------------------
* Notes			: 
*-------------------------------------------------------------------
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FUNC COMMENT END""**********************************************/
#if FAST_INTC_VECTOR == VECT_RIIC0_ICTXI0
__fast_interrupt void Interrupt_IIC_ICTXI0(void)
#else
#pragma vector = VECT_RIIC0_ICTXI0
__interrupt void Interrupt_IIC_ICTXI0(void)
#endif
{
  switch (rpdl_IIC_current_state[0])
  {
  case IIC_MASTER_SEND_SLAVE_ADDRESS_10b:
    /* Send the second part of the slave address */
    RIIC0.ICDRT = rpdl_IIC_slave_address_lower[0];

    /* Transmit mode? */
    if ((rpdl_IIC_slave_address_upper[0] & BIT_0) == 0)
    {
      rpdl_IIC_current_state[0] = IIC_MASTER_SEND_DATA;
    }
    else
    {
      rpdl_IIC_current_state[0] = IIC_MASTER_START_READ;

      /* Enable receive interrupt request generation */
      RIIC0.ICIER.BIT.RIE = 1;
    }
    break;
  case IIC_MASTER_SEND_DATA:
    /* All data sent? */
    if (rpdl_IIC_tx_counter[0] == rpdl_IIC_tx_threshold[0])
    {
      rpdl_IIC_current_state[0] = IIC_MASTER_WAIT_FOR_TX_COMPLETE;

      /* Disable ICTXI interrupt request generation */
      RIIC0.ICIER.BIT.TIE = 0;

      /* Ensure the ICTEI IR flag is clear */
      ICU.IR[IR_RIIC0_ICTEI0].BIT.IR = 0;

      /* Enable Transmit End interrupt generation */
      RIIC0.ICIER.BIT.TEIE = 1;
    }
    else
    {
      /* Load the data to be sent */
      RIIC0.ICDRT = *rpdl_IIC_tx_data_pointer[0];

      /* Increment the pointer */
      rpdl_IIC_tx_data_pointer[0]++;

      /* Increment the counter */
      rpdl_IIC_tx_counter[0]++;
    }
    break;
  case IIC_SLAVE_MONITOR:
    /* Note the detected address */
    Store_detected_address(0);

    /* Call the callback function */
    if (rpdl_IIC_callback_func[0] != PDL_NO_FUNC)
    {
      rpdl_IIC_callback_func[0]();
    }
    break;
  case IIC_SLAVE_SEND_DATA:
    /* All data sent? */
    if (rpdl_IIC_tx_counter[0] == rpdl_IIC_tx_threshold[0])
    {
      /* Clear the counter */
      rpdl_IIC_tx_counter[0] = 0;

      /* Loop back to the start */
      rpdl_IIC_tx_data_pointer[0] = rpdl_IIC_tx_data_start[0];
    }

    /* Load the data to be sent */
    RIIC0.ICDRT = *rpdl_IIC_tx_data_pointer[0];

    /* Increment the pointer */
    rpdl_IIC_tx_data_pointer[0]++;

    /* Increment the counter */
    rpdl_IIC_tx_counter[0]++;
    break;
  case IIC_SLAVE_READ_DATA:
    /* Call the callback function */
    if (rpdl_IIC_callback_func[0] != PDL_NO_FUNC)
    {
      rpdl_IIC_callback_func[0]();
    }
    break;
  case IIC_EXIT_LOOP:
    /* This will occur if the DMAC/DTC is being used with a callback */
    /* Call the callback function */
    if (rpdl_IIC_callback_func[0] != PDL_NO_FUNC)
    {
      rpdl_IIC_callback_func[0]();
    }
    break;
  default:
    /* Call the callback function */
    if (rpdl_IIC_callback_func[0] != PDL_NO_FUNC)
    {
      rpdl_IIC_callback_func[0]();
    }
    break;
  }
}

#if FAST_INTC_VECTOR == VECT_RIIC1_ICTXI1
__fast_interrupt void Interrupt_IIC_ICTXI1(void)
#else
#pragma vector = VECT_RIIC1_ICTXI1
__interrupt void Interrupt_IIC_ICTXI1(void)
#endif
{
#ifdef DEVICE_PACKAGE_LQFP_100
  /* This channel is not available on the 100-pin package */
  nop();
#else
  switch (rpdl_IIC_current_state[1])
  {
  case IIC_MASTER_SEND_SLAVE_ADDRESS_10b:
    /* Send the second part of the slave address */
    RIIC1.ICDRT = rpdl_IIC_slave_address_lower[1];

    /* Transmit mode? */
    if ((rpdl_IIC_slave_address_upper[1] & BIT_0) == 0)
    {
      rpdl_IIC_current_state[1] = IIC_MASTER_SEND_DATA;
    }
    else
    {
      rpdl_IIC_current_state[1] = IIC_MASTER_START_READ;

      /* Enable receive interrupt request generation */
      RIIC1.ICIER.BIT.RIE = 1;
    }
    break;
  case IIC_MASTER_SEND_DATA:
    /* All data sent? */
    if (rpdl_IIC_tx_counter[1] == rpdl_IIC_tx_threshold[1])
    {
      rpdl_IIC_current_state[1] = IIC_MASTER_WAIT_FOR_TX_COMPLETE;

      /* Disable ICTXI interrupt request generation */
      RIIC1.ICIER.BIT.TIE = 0;

      /* Ensure the ICTEI IR flag is clear */
      ICU.IR[IR_RIIC1_ICTEI1].BIT.IR = 0;

      /* Enable Transmit End interrupt generation */
      RIIC1.ICIER.BIT.TEIE = 1;
    }
    else
    {
      /* Load the data to be sent */
      RIIC1.ICDRT = *rpdl_IIC_tx_data_pointer[1];

      /* Increment the pointer */
      rpdl_IIC_tx_data_pointer[1]++;

      /* Increment the counter */
      rpdl_IIC_tx_counter[1]++;
    }
    break;
  case IIC_SLAVE_MONITOR:
    /* Note the detected address */
    Store_detected_address(1);

    /* Call the callback function */
    if (rpdl_IIC_callback_func[1] != PDL_NO_FUNC)
    {
      rpdl_IIC_callback_func[1]();
    }
    break;
  case IIC_SLAVE_SEND_DATA:
    /* All data sent? */
    if (rpdl_IIC_tx_counter[1] == rpdl_IIC_tx_threshold[1])
    {
      /* Clear the counter */
      rpdl_IIC_tx_counter[1] = 0;

      /* Loop back to the start */
      rpdl_IIC_tx_data_pointer[1] = rpdl_IIC_tx_data_start[1];
    }

    /* Load the data to be sent */
    RIIC1.ICDRT = *rpdl_IIC_tx_data_pointer[1];

    /* Increment the pointer */
    rpdl_IIC_tx_data_pointer[1]++;

    /* Increment the counter */
    rpdl_IIC_tx_counter[1]++;
    break;
  case IIC_SLAVE_READ_DATA:
    /* Call the callback function */
    if (rpdl_IIC_callback_func[1] != PDL_NO_FUNC)
    {
      rpdl_IIC_callback_func[1]();
    }
    break;
  case IIC_EXIT_LOOP:
    /* This will occur if the DMAC/DTC is being used with a callback */
    /* Call the callback function */
    if (rpdl_IIC_callback_func[1] != PDL_NO_FUNC)
    {
      rpdl_IIC_callback_func[1]();
    }
    break;
  default:
    /* Call the callback function */
    if (rpdl_IIC_callback_func[1] != PDL_NO_FUNC)
    {
      rpdl_IIC_callback_func[1]();
    }
    break;
  }
#endif
}

/*""FUNC COMMENT""***************************************************
* Module outline: IICn transmit end interrupt processing
*-------------------------------------------------------------------
* Declaration	: void InterruptIIC_ICTEIn(void)
*-------------------------------------------------------------------
* Function		: 
*-------------------------------------------------------------------
* Argument		: Nothing
*-------------------------------------------------------------------
* Return value	: Nothing
*-------------------------------------------------------------------
* Output		: ICIER, ICSR2
*-------------------------------------------------------------------
* Use function	: 
*-------------------------------------------------------------------
* Notes			: 
*-------------------------------------------------------------------
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FUNC COMMENT END""**********************************************/

#if FAST_INTC_VECTOR == VECT_RIIC0_ICTEI0
__fast_interrupt void Interrupt_IIC_ICTEI0(void)
#else
#pragma vector = VECT_RIIC0_ICTEI0
__interrupt void Interrupt_IIC_ICTEI0(void)
#endif
{
  /* Disable Transmit End interrupt request generation */
  RIIC0.ICIER.BIT.TEIE = 0;
  /* Clear the flag */
  RIIC0.ICSR2.BIT.TEND = 0;

  /* Stop condition required? */
  if (rpdl_IIC_stop[0] == true)
  {
    rpdl_IIC_current_state[0] = IIC_MASTER_WAIT_FOR_STOP;

    /* Enable Stop detection */
    RIIC0.ICIER.BIT.SPIE = 1;

    /* Issue a stop condition */
    RIIC0.ICCR2.BIT.SP = 1;
  }
  else
  {
    /* Disable all interrupt request generation */
    RIIC0.ICIER.BYTE = 0x00u;

    /* Call the callback function */
    if (rpdl_IIC_callback_func[0] != PDL_NO_FUNC)
    {
      rpdl_IIC_callback_func[0]();
    }
  }
}

#if FAST_INTC_VECTOR == VECT_RIIC1_ICTEI1
__fast_interrupt void Interrupt_IIC_ICTEI1(void)
#else
#pragma vector = VECT_RIIC1_ICTEI1
__interrupt void Interrupt_IIC_ICTEI1(void)
#endif
{
#ifdef DEVICE_PACKAGE_LQFP_100
  /* This channel is not available on the 100-pin package */
  nop();
#else
  /* Disable Transmit End interrupt request generation */
  RIIC1.ICIER.BIT.TEIE = 0;
  /* Clear the flag */
  RIIC1.ICSR2.BIT.TEND = 0;

  /* Stop condition required? */
  if (rpdl_IIC_stop[1] == true)
  {
    rpdl_IIC_current_state[1] = IIC_MASTER_WAIT_FOR_STOP;

    /* Enable Stop detection */
    RIIC1.ICIER.BIT.SPIE = 1;

    /* Issue a stop condition */
    RIIC1.ICCR2.BIT.SP = 1;
  }
  else
  {
    /* Disable all interrupt request generation */
    RIIC1.ICIER.BYTE = 0x00u;

    /* Call the callback function */
    if (rpdl_IIC_callback_func[1] != PDL_NO_FUNC)
    {
      rpdl_IIC_callback_func[1]();
    }
  }
#endif
}
/* End of file */
