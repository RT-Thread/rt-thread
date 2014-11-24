/*""FILE COMMENT""*******************************************************
* System Name	: Interrupt program for RX62Nxx
* File Name		: Interrupt_SPI.c
* Version		: 1.02
* Contents		: Interrupt handlers for all SPI channels
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

#include "r_pdl_spi.h"
#include "r_pdl_definitions.h"
#include "r_pdl_user_definitions.h"

/*""FUNC COMMENT""***************************************************
* Module outline: SPIn receive data error interrupt processing
*-------------------------------------------------------------------
* Declaration	: void Interrupt_RSPIn_SPEIn(void)
*-------------------------------------------------------------------
* Function		: 
*-------------------------------------------------------------------
* Argument		: Nothing
*-------------------------------------------------------------------
* Return value	: Nothing
*-------------------------------------------------------------------
* Output		: None
*-------------------------------------------------------------------
* Use function	: rpdl_SPI_callback_func[n]
*-------------------------------------------------------------------
* Notes			: 
*-------------------------------------------------------------------
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FUNC COMMENT END""**********************************************/

#if FAST_INTC_VECTOR == VECT_RSPI0_SPEI0
__fast_interrupt void Interrupt_RSPI0_SPEI0(void)
#else
#pragma vector = VECT_RSPI0_SPEI0
__interrupt void Interrupt_RSPI0_SPEI0(void)
#endif
{
  /* Will the user handle the errors? */
  if (rpdl_SPI_callback_func[0] != PDL_NO_FUNC)
  {
    /* Notify the user */
    rpdl_SPI_callback_func[0]();
  }
}

#if FAST_INTC_VECTOR == VECT_RSPI1_SPEI1
__fast_interrupt void Interrupt_RSPI1_SPEI1(void)
#else
#pragma vector = VECT_RSPI1_SPEI1
__interrupt void Interrupt_RSPI1_SPEI1(void)
#endif
{
  /* Will the user handle the errors? */
  if (rpdl_SPI_callback_func[1] != PDL_NO_FUNC)
  {
    /* Notify the user */
    rpdl_SPI_callback_func[1]();
  }
}

/*""FUNC COMMENT""***************************************************
* Module outline: SPIn receive data interrupt processing
*-------------------------------------------------------------------
* Declaration	: void Interrupt_RSPIn_SPRIn(void)
*-------------------------------------------------------------------
* Function		: 
*-------------------------------------------------------------------
* Argument		: Nothing
*-------------------------------------------------------------------
* Return value	: Nothing
*-------------------------------------------------------------------
* Input			: (I/ ) : SPDCR, SBDR
* Output		: (I/O) : SPCR, SPCR2
*-------------------------------------------------------------------
* Use function	: None
*-------------------------------------------------------------------
* Notes			: 
*-------------------------------------------------------------------
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FUNC COMMENT END""**********************************************/

#if FAST_INTC_VECTOR == VECT_RSPI0_SPRI0
__fast_interrupt void Interrupt_RSPI0_SPRI0(void)
#else
#pragma vector = VECT_RSPI0_SPRI0
__interrupt void Interrupt_RSPI0_SPRI0(void)
#endif
{
  uint8_t frame_count;
  uint32_t received_frame;
  uint8_t spdcr_copy;
  uint8_t splw;
  uint8_t spfc;
  volatile uint32_t * rx_data_ptr;

  /* Ok to process the data? */
  if (rpdl_SPI_method[0] == SPI_USING_IRQ)
  {
    spdcr_copy = RSPI0.SPDCR.BYTE;
    splw = (uint8_t)(spdcr_copy & BIT_5);
    spfc = (uint8_t)(spdcr_copy & 0x03u);
    rx_data_ptr = rpdl_SPI_rx_ptr[0];

    /* Load the data register */
    for (frame_count = 0; frame_count <= spfc; frame_count++)
    {
      if (splw == 0)
      {
        /* Read the data */
        received_frame = (uint32_t)RSPI0.SPDR.WORD.H;
      }
      else
      {
        /* Read the data */
        received_frame = RSPI0.SPDR.LONG;
      }

      /* Store the data? */
      if (rx_data_ptr != PDL_NO_PTR)
      {
        *rx_data_ptr = received_frame;

        /* Increment the address pointer */
        rx_data_ptr ++;
      }

      /* Increment the frame counter */
      rpdl_SPI_rx_frame_counter[0] ++;
    }

    /* Store the updated pointer */
    rpdl_SPI_rx_ptr[0] = rx_data_ptr;

    /* All data read? */
    if (rpdl_SPI_rx_frame_counter[0] == rpdl_SPI_frame_total[0])
    {
      /* Increment the loop counter */
      rpdl_SPI_rx_sequence_counter[0]++;

      /* All loops completed? */
      if (rpdl_SPI_rx_sequence_counter[0] == rpdl_SPI_sequence_count[0])
      {
        /* Disable receive interrupts */
        RSPI0.SPCR.BIT.SPRIE = 0;

        /* Master mode? */
        if (RSPI0.SPCR.BIT.MSTR == 1)
        {
          /* Enable idle interrupts */
          RSPI0.SPCR2.BIT.SPIIE = 1;
        }
        else
        {
          /* Notify the user */
          if (rpdl_SPI_callback_func[0] != PDL_NO_FUNC)
          {
            rpdl_SPI_callback_func[0]();
          }
        }
      }
      else
      {
        /* Reset the frame counter */
        rpdl_SPI_rx_frame_counter[0] = 0;
      }
    }
  }
  else
  {
    /* Notify the user */
    if (rpdl_SPI_callback_func[0] != PDL_NO_FUNC)
    {
      rpdl_SPI_callback_func[0]();
    }
  }
}

#if FAST_INTC_VECTOR == VECT_RSPI1_SPRI1
__fast_interrupt void Interrupt_RSPI1_SPRI1(void)
#else
#pragma vector = VECT_RSPI1_SPRI1
__interrupt void Interrupt_RSPI1_SPRI1(void)
#endif
{
  uint8_t frame_count;
  uint32_t received_frame;
  uint8_t spdcr_copy;
  uint8_t splw;
  uint8_t spfc;
  volatile uint32_t * rx_data_ptr;

  /* Ok to process the data? */
  if (rpdl_SPI_method[1] == SPI_USING_IRQ)
  {
    spdcr_copy = RSPI1.SPDCR.BYTE;
    splw = (uint8_t)(spdcr_copy & BIT_5);
    spfc = (uint8_t)(spdcr_copy & 0x03u);
    rx_data_ptr = rpdl_SPI_rx_ptr[1];

    /* Load the data register */
    for (frame_count = 0; frame_count <= spfc; frame_count++)
    {
      if (splw == 0)
      {
        /* Read the data */
        received_frame = (uint32_t)RSPI1.SPDR.WORD.H;
      }
      else
      {
        /* Read the data */
        received_frame = RSPI1.SPDR.LONG;
      }

      /* Store the data? */
      if (rx_data_ptr != PDL_NO_PTR)
      {
        *rx_data_ptr = received_frame;

        /* Increment the address pointer */
        rx_data_ptr ++;
      }

      /* Increment the frame counter */
      rpdl_SPI_rx_frame_counter[1] ++;
    }

    /* Store the updated pointer */
    rpdl_SPI_rx_ptr[1] = rx_data_ptr;

    /* All data read? */
    if (rpdl_SPI_rx_frame_counter[1] == rpdl_SPI_frame_total[1])
    {
      /* Increment the loop counter */
      rpdl_SPI_rx_sequence_counter[1]++;

      /* All loops completed? */
      if (rpdl_SPI_rx_sequence_counter[1] == rpdl_SPI_sequence_count[1])
      {
        /* Disable receive interrupts */
        RSPI1.SPCR.BIT.SPRIE = 0;

        /* Master mode? */
        if (RSPI1.SPCR.BIT.MSTR == 1)
        {
          /* Enable idle interrupts */
          RSPI1.SPCR2.BIT.SPIIE = 1;
        }
        else
        {
          /* Notify the user */
          if (rpdl_SPI_callback_func[1] != PDL_NO_FUNC)
          {
            rpdl_SPI_callback_func[1]();
          }
        }
      }
      else
      {
        /* Reset the frame counter */
        rpdl_SPI_rx_frame_counter[1] = 0;
      }
    }
  }
  else
  {
    /* Notify the user */
    if (rpdl_SPI_callback_func[1] != PDL_NO_FUNC)
    {
      rpdl_SPI_callback_func[1]();
    }
  }
}

/*""FUNC COMMENT""***************************************************
* Module outline: SPIn transmit data interrupt processing
*-------------------------------------------------------------------
* Declaration	: void Interrupt_RSPIn_SPTIn(void)
*-------------------------------------------------------------------
* Function		: 
*-------------------------------------------------------------------
* Argument		: Nothing
*-------------------------------------------------------------------
* Return value	: Nothing
*-------------------------------------------------------------------
* Input			: (I/ ) : SPDCR
* Output		: ( /O) : SBDR
*				: (I/O) : SPCR, SPCR2
*-------------------------------------------------------------------
* Use function	: 
*-------------------------------------------------------------------
* Notes			: 
*-------------------------------------------------------------------
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FUNC COMMENT END""**********************************************/

#if FAST_INTC_VECTOR == VECT_RSPI0_SPTI0
__fast_interrupt void Interrupt_RSPI0_SPTI0(void)
#else
#pragma vector = VECT_RSPI0_SPTI0
__interrupt void Interrupt_RSPI0_SPTI0(void)
#endif
{
  uint8_t frame_count;
  uint8_t spdcr_copy;
  uint8_t splw;
  uint8_t spfc;
  volatile const uint32_t * tx_data_ptr;

  /* Ok to process the string? */
  if (rpdl_SPI_method[0] == SPI_USING_IRQ)
  {
    spdcr_copy = RSPI0.SPDCR.BYTE;
    splw = (uint8_t)(spdcr_copy & BIT_5);
    spfc = (uint8_t)(spdcr_copy & 0x03u);
    tx_data_ptr = rpdl_SPI_tx_ptr[0];

    /* Load the data register */
    for (frame_count = 0; frame_count <= spfc; frame_count++)
    {
      if (splw == 0)
      {
        RSPI0.SPDR.WORD.H = (uint16_t)*tx_data_ptr;
      }
      else
      {
        RSPI0.SPDR.LONG = *tx_data_ptr;
      }

      /* Increment the address pointer? */
      if (tx_data_ptr != PDL_NO_PTR)
      {
        tx_data_ptr ++;
      }

      /* Increment the frame counter */
      rpdl_SPI_tx_frame_counter[0] ++;
    }

    /* Store the updated pointer */
    rpdl_SPI_tx_ptr[0] = tx_data_ptr;

    /* All data written? */
    if (rpdl_SPI_tx_frame_counter[0] == rpdl_SPI_frame_total[0])
    {
      /* Increment the loop counter */
      rpdl_SPI_tx_sequence_counter[0]++;

      /* All loops completed? */
      if (rpdl_SPI_tx_sequence_counter[0] == rpdl_SPI_sequence_count[0])
      {
        /* Disable transmit interrupts */
        RSPI0.SPCR.BIT.SPTIE = 0;

        /* Transmit only? */
        if (RSPI0.SPCR.BIT.TXMD == 1)
        {
          /* Master mode? */
          if (RSPI0.SPCR.BIT.MSTR == 1)
          {
            /* Enable idle interrupts */
            RSPI0.SPCR2.BIT.SPIIE = 1;
          }
          else
          {
            /* Notify the user */
            if (rpdl_SPI_callback_func[0] != PDL_NO_FUNC)
            {
              rpdl_SPI_callback_func[0]();
            }
          }
        }
      }
      else
      {
        /* Reset the frame counter */
        rpdl_SPI_tx_frame_counter[0] = 0;
      }
    }
  }
  else
  {
    /* Notify the user */
    if (rpdl_SPI_callback_func[0] != PDL_NO_FUNC)
    {
      rpdl_SPI_callback_func[0]();
    }
  }
}

#if FAST_INTC_VECTOR == VECT_RSPI1_SPTI1
__fast_interrupt void Interrupt_RSPI1_SPTI1(void)
#else
#pragma vector = VECT_RSPI1_SPTI1
__interrupt void Interrupt_RSPI1_SPTI1(void)
#endif
{
  uint8_t frame_count;
  uint8_t spdcr_copy;
  uint8_t splw;
  uint8_t spfc;
  volatile const uint32_t * tx_data_ptr;

  /* Ok to process the string? */
  if (rpdl_SPI_method[1] == SPI_USING_IRQ)
  {
    spdcr_copy = RSPI1.SPDCR.BYTE;
    splw = (uint8_t)(spdcr_copy & BIT_5);
    spfc = (uint8_t)(spdcr_copy & 0x03u);
    tx_data_ptr = rpdl_SPI_tx_ptr[1];

    /* Load the data register */
    for (frame_count = 0; frame_count <= spfc; frame_count++)
    {
      if (splw == 0)
      {
        RSPI1.SPDR.WORD.H = (uint16_t)*tx_data_ptr;
      }
      else
      {
        RSPI1.SPDR.LONG = *tx_data_ptr;
      }

      /* Increment the address pointer? */
      if (tx_data_ptr != PDL_NO_PTR)
      {
        tx_data_ptr ++;
      }

      /* Increment the frame counter */
      rpdl_SPI_tx_frame_counter[1] ++;
    }

    /* Store the updated pointer */
    rpdl_SPI_tx_ptr[1] = tx_data_ptr;

    /* All data written? */
    if (rpdl_SPI_tx_frame_counter[1] == rpdl_SPI_frame_total[1])
    {
      /* Increment the loop counter */
      rpdl_SPI_tx_sequence_counter[1]++;

      /* All loops completed? */
      if (rpdl_SPI_tx_sequence_counter[1] == rpdl_SPI_sequence_count[1])
      {
        /* Disable transmit interrupts */
        RSPI1.SPCR.BIT.SPTIE = 0;

        /* Transmit only? */
        if (RSPI1.SPCR.BIT.TXMD == 1)
        {
          /* Master mode? */
          if (RSPI1.SPCR.BIT.MSTR == 1)
          {
            /* Enable idle interrupts */
            RSPI1.SPCR2.BIT.SPIIE = 1;
          }
          else
          {
            /* Notify the user */
            if (rpdl_SPI_callback_func[1] != PDL_NO_FUNC)
            {
              rpdl_SPI_callback_func[1]();
            }
          }
        }
      }
      else
      {
        /* Reset the frame counter */
        rpdl_SPI_tx_frame_counter[1] = 0;
      }
    }
  }
  else
  {
    /* Notify the user */
    if (rpdl_SPI_callback_func[1] != PDL_NO_FUNC)
    {
      rpdl_SPI_callback_func[1]();
    }
  }
}

/*""FUNC COMMENT""***************************************************
* Module outline: SPIn idle interrupt processing
*-------------------------------------------------------------------
* Declaration	: void Interrupt_RSPIn_SPIIn(void)
*-------------------------------------------------------------------
* Function		: 
*-------------------------------------------------------------------
* Argument		: Nothing
*-------------------------------------------------------------------
* Return value	: Nothing
*-------------------------------------------------------------------
* Output		: SPCR, SPCR2
*-------------------------------------------------------------------
* Use function	: rpdl_SPI_callback_func()
*-------------------------------------------------------------------
* Notes			: 
*-------------------------------------------------------------------
* History		: 2011.04.08
*				: Ver 1.02
*				: CS-5 release.
*""FUNC COMMENT END""**********************************************/

#if FAST_INTC_VECTOR == VECT_RSPI0_SPII0
__fast_interrupt void Interrupt_RSPI0_SPII0(void)
#else
#pragma vector = VECT_RSPI0_SPII0
__interrupt void Interrupt_RSPI0_SPII0(void)
#endif
{
  /* Disable the channel */
  RSPI0.SPCR.BIT.SPE = 0;

  /* Disable idle interrupts */
  RSPI0.SPCR2.BIT.SPIIE = 0;

  /* Call the callback function */
  if (rpdl_SPI_callback_func[0] != PDL_NO_FUNC)
  {
    rpdl_SPI_callback_func[0]();
  }
}

#if FAST_INTC_VECTOR == VECT_RSPI1_SPII1
__fast_interrupt void Interrupt_RSPI1_SPII1(void)
#else
#pragma vector = VECT_RSPI1_SPII1
__interrupt void Interrupt_RSPI1_SPII1(void)
#endif
{
  /* Disable the channel */
  RSPI1.SPCR.BIT.SPE = 0;

  /* Disable idle interrupts */
  RSPI1.SPCR2.BIT.SPIIE = 0;

  /* Call the callback function */
  if (rpdl_SPI_callback_func[1] != PDL_NO_FUNC)
  {
    rpdl_SPI_callback_func[1]();
  }
}

/* End of file */
