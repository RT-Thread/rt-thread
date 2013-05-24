/** @file sci.c 
*   @brief SCI Driver Implementation File
*   @date 23.May.2013
*   @version 03.05.01
*
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */

#include "sci.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */
/** @struct g_sciTransfer
*   @brief Interrupt mode globals
*
*/
static struct g_sciTransfer
{
    uint32   mode;
    uint32   length;
    uint8    * data;
} g_sciTransfer_t[2U];


/** @fn void sciInit(void)
*   @brief Initializes the SCI Driver
*
*   This function initializes the SCI module.
*/
void sciInit(void)
{
/* USER CODE BEGIN (2) */
/* USER CODE END */


    /** @b initialize @b SCILIN */

    /** - bring SCI out of reset */
    scilinREG->GCR0 = 1U;

    /** - Disable all interrupts */
    scilinREG->CLRINT    = 0xFFFFFFFFU;
    scilinREG->CLRINTLVL = 0xFFFFFFFFU;

    /** - global control 1 */
    scilinREG->GCR1 = (1U << 25U)  /* enable transmit */
                  | (1U << 24U)  /* enable receive */
                  | (1U << 5U)   /* internal clock (device has no clock pin) */
                  | ((1U-1U) << 4U)  /* number of stop bits */
                  | (0U << 3U)  /* even parity, otherwise odd */
                  | (0U << 2U)  /* enable parity */
                  | (1U << 1U);  /* asynchronous timing mode */

    /** - set baudrate */
    scilinREG->BRS = 53U;  /* baudrate */

    /** - transmission length */
    scilinREG->FORMAT = 8U - 1U;  /* length */

    /** - set SCI pins functional mode */
    scilinREG->FUN = (1U << 2U)  /* tx pin */
                 | (1U << 1U)  /* rx pin */
                 | (0U);  /* clk pin */

    /** - set SCI pins default output value */
    scilinREG->DOUT = (0U << 2U)  /* tx pin */
                  | (0U << 1U)  /* rx pin */
                  | (0U);  /* clk pin */

    /** - set SCI pins output direction */
    scilinREG->DIR = (0U << 2U)  /* tx pin */
                 | (0U << 1U)  /* rx pin */
                 | (0U);  /* clk pin */

    /** - set SCI pins open drain enable */
    scilinREG->ODR = (0U << 2U)  /* tx pin */
                 | (0U << 1U)  /* rx pin */
                 | (0U);  /* clk pin */

    /** - set SCI pins pullup/pulldown enable */
    scilinREG->PD = (0U << 2U)  /* tx pin */
                | (0U << 1U)  /* rx pin */
                | (0U);  /* clk pin */

    /** - set SCI pins pullup/pulldown select */
    scilinREG->PSL = (1U << 2U)  /* tx pin */
                 | (1U << 1U)  /* rx pin */
                 | (1U);  /* clk pin */

    /** - set interrupt level */
    scilinREG->SETINTLVL = (0U << 26U)  /* Framing error */
                       | (0U << 25U)  /* Overrun error */
                       | (0U << 24U)  /* Parity error */
                       | (0U << 9U)  /* Receive */
                       | (0U << 8U)  /* Transmit */
                       | (0U << 1U)  /* Wakeup */
                       | (0U);  /* Break detect */

    /** - set interrupt enable */
    scilinREG->SETINT = (0U << 26U)  /* Framing error */
                    | (0U << 25U)  /* Overrun error */
                    | (0U << 24U)  /* Parity error */
                    | (1U << 9U)  /* Receive */
                    | (0U << 1U)  /* Wakeup */
                    | (0U);  /* Break detect */

    /** - initialize global transfer variables */
    g_sciTransfer_t[1U].mode   = 0U << 8U;
    g_sciTransfer_t[1U].length = 0U;

    /** - Finaly start SCILIN */
    scilinREG->GCR1 |= (1U << 7U);

/* USER CODE BEGIN (3) */
/* USER CODE END */
}


/** @fn void sciSetFunctional(sciBASE_t *sci, uint32 port)
*   @brief Change functional behavior of pins at runtime.
*   @param[in] sci   - sci module base address
*   @param[in] port  - Value to write to FUN register
*
*   Change the value of the PCFUN register at runtime, this allows to
*   dynamically change the functionality of the SCI pins between functional
*   and GIO mode.
*/
void sciSetFunctional(sciBASE_t *sci, uint32 port)
{
/* USER CODE BEGIN (4) */
/* USER CODE END */

    sci->FUN = port;

/* USER CODE BEGIN (5) */
/* USER CODE END */
}


/** @fn void sciSetBaudrate(sciBASE_t *sci, uint32 baud)
*   @brief Change baudrate at runtime.
*   @param[in] sci  - sci module base address
*   @param[in] baud - baudrate in Hz
*
*   Change the SCI baudrate at runtime.
*/
void sciSetBaudrate(sciBASE_t *sci, uint32 baud)
{
    float64   vclk = 100.000 * 1000000.0;
    uint32 f    = ((sci->GCR1 & 2U) == 2U) ? 16U : 1U;

/* USER CODE BEGIN (6) */
/* USER CODE END */

	/*SAFETYMCUSW 96 S MR:6.1 <REVIEWED> "Calculations including int and float cannot be avoided" */
    sci->BRS = ((uint32)((vclk /(f*baud) + 0.5)) - 1U) & 0x00FFFFFFU;

/* USER CODE BEGIN (7) */
/* USER CODE END */
}


/** @fn uint32 sciIsTxReady(sciBASE_t *sci)
*   @brief Check if Tx buffer empty
*   @param[in] sci - sci module base address
*
*   @return The TX ready flag
*
*   Checks to see if the Tx buffer ready flag is set, returns
*   0 is flags not set otherwise will return the Tx flag itself.
*/
uint32 sciIsTxReady(sciBASE_t *sci)
{
/* USER CODE BEGIN (8) */
/* USER CODE END */

    return sci->FLR & SCI_TX_INT;
}


/** @fn void sciSendByte(sciBASE_t *sci, uint8 byte)
*   @brief Send Byte
*   @param[in] sci  - sci module base address
*   @param[in] byte - byte to transfer
*
*   Sends a single byte in polling mode, will wait in the
*   routine until the transmit buffer is empty before sending
*   the byte.  Use sciIsTxReady to check for Tx buffer empty
*   before calling sciSendByte to avoid waiting.
*/
void sciSendByte(sciBASE_t *sci, uint8 byte)
{
/* USER CODE BEGIN (9) */
/* USER CODE END */

    while ((sci->FLR & SCI_TX_INT) == 0U) 
    { 
	} /* Wait */
    sci->TD = byte;

/* USER CODE BEGIN (10) */
/* USER CODE END */
}


/** @fn void sciSend(sciBASE_t *sci, uint32 length, uint8 * data)
*   @brief Send Data
*   @param[in] sci    - sci module base address
*   @param[in] length - number of data words to transfer
*   @param[in] data   - pointer to data to send
*
*   Send a block of data pointed to by 'data' and 'length' bytes
*   long.  If interrupts have been enabled the data is sent using
*   interrupt mode, otherwise polling mode is used.  In interrupt
*   mode transmission of the first byte is started and the routine
*   returns immediately, sciSend must not be called again until the
*   transfer is complete, when the sciNotification callback will
*   be called.  In polling mode, sciSend will not return  until 
*   the transfer is complete.
*
*   @note if data word is less than 8 bits, then the data must be left
*         aligned in the data byte.
*/
void sciSend(sciBASE_t *sci, uint32 length, uint8 * data)
{
    uint32 index = sci == sciREG ? 0U : 1U;

/* USER CODE BEGIN (11) */
/* USER CODE END */

    if ((g_sciTransfer_t[index].mode & SCI_TX_INT) != 0U)
    {
        /* we are in interrupt mode */
        
        g_sciTransfer_t[index].length = length;
        g_sciTransfer_t[index].data   = data;

        /* start transmit by sending first byte */        
        sci->TD     = *g_sciTransfer_t[index].data++ ;
        sci->SETINT = SCI_TX_INT;
    }
    else
    {
        /* send the data */
        while (length-- > 0U)
        {
            while ((sci->FLR & SCI_TX_INT) == 0U)
            { 
	        } /* Wait */
            sci->TD = *data++;
        }
    }

/* USER CODE BEGIN (12) */
/* USER CODE END */
}


/** @fn uint32 sciIsRxReady(sciBASE_t *sci)
*   @brief Check if Rx buffer full
*   @param[in] sci - sci module base address
*
*   @return The Rx ready flag
*
*   Checks to see if the Rx buffer full flag is set, returns
*   0 is flags not set otherwise will return the Rx flag itself.
*/
uint32 sciIsRxReady(sciBASE_t *sci)
{
/* USER CODE BEGIN (13) */
/* USER CODE END */

    return sci->FLR & SCI_RX_INT;
}

/** @fn uint32 sciIsIdleDetected(sciBASE_t *sci)
*   @brief Check if Idle Period is Detected
*   @param[in] sci - sci module base address
*
*   @return The Idle flag
*
*   Checks to see if the SCI Idle flag is set, returns 0 is flags 
*   not set otherwise will return the Ilde flag itself.
*/
uint32 sciIsIdleDetected(sciBASE_t *sci)
{
/* USER CODE BEGIN (14) */
/* USER CODE END */

    return sci->FLR & SCI_IDLE;
}


/** @fn uint32 sciRxError(sciBASE_t *sci)
*   @brief Return Rx Error flags
*   @param[in] sci - sci module base address
*
*   @return The Rx error flags
*
*   Returns the Rx framing, overrun and parity errors flags,
*   also clears the error flags before returning.
*/
uint32 sciRxError(sciBASE_t *sci)
{
    uint32 status = sci->FLR & (SCI_FE_INT | SCI_OE_INT |SCI_PE_INT);

/* USER CODE BEGIN (15) */
/* USER CODE END */

    sci->FLR = SCI_FE_INT | SCI_OE_INT | SCI_PE_INT;
    return status;
}


/** @fn uint32 sciReceiveByte(sciBASE_t *sci)
*   @brief Receive Byte
*   @param[in] sci - sci module base address
*
*   @return Received byte
*
*    Receives a single byte in polling mode.  If there is
*    not a byte in the receive buffer the routine will wait
*    until one is received.   Use sciIsRxReady to check to
*    see if the buffer is full to avoid waiting.
*/
uint32 sciReceiveByte(sciBASE_t *sci)
{
/* USER CODE BEGIN (16) */
/* USER CODE END */

    while ((sci->FLR & SCI_RX_INT) == 0U) 
    { 
	} /* Wait */

    return (sci->RD & 0x000000FFU);
}


/** @fn void sciReceive(sciBASE_t *sci, uint32 length, uint8 * data)
*   @brief Receive Data
*   @param[in] sci    - sci module base address
*   @param[in] length - number of data words to transfer
*   @param[in] data   - pointer to data buffer
*
*   Receive a block of 'length' bytes long and place it into the 
*   data buffer pointed to by 'data'.  If interrupts have been 
*   enabled the data is received using interrupt mode, otherwise
*   polling mode is used.  In interrupt mode receive is setup and
*   the routine returns immediately, sciReceive must not be called 
*   again until the transfer is complete, when the sciNotification 
*   callback will be called.  In polling mode, sciReceive will not
*   return  until the transfer is complete.
*/
void sciReceive(sciBASE_t *sci, uint32 length, uint8 * data)
{
/* USER CODE BEGIN (17) */
/* USER CODE END */

    if ((sci->SETINT & SCI_RX_INT) == SCI_RX_INT)
    {
        /* we are in interrupt mode */
        uint32 index = sci == sciREG ? 0U : 1U;
        
        /* clear error flags */
        sci->FLR = SCI_FE_INT | SCI_OE_INT | SCI_PE_INT;

        g_sciTransfer_t[index].length = length;
        g_sciTransfer_t[index].data   = data;
    }
    else
    {   
        while (length-- > 0U)
        {
            while ((sci->FLR & SCI_RX_INT) == 0U) 
		    { 
	        } /* Wait */
            *data++ = (uint8)(sci->RD & 0x000000FFU);
        }
    }
/* USER CODE BEGIN (18) */
/* USER CODE END */
}

/** @fn void sciEnableLoopback(sciBASE_t *sci, loopBackType_t Loopbacktype)
*   @brief Enable Loopback mode for self test
*   @param[in] sci        - sci module base address
*   @param[in] Loopbacktype  - Digital or Analog
*
*   This function enables the Loopback mode for self test.
*/
void sciEnableLoopback(sciBASE_t *sci, loopBackType_t Loopbacktype)
{
/* USER CODE BEGIN (19) */
/* USER CODE END */
    
	/* Clear Loopback incase enabled already */
	sci->IODFTCTRL = 0U;
	
	/* Enable Loopback either in Analog or Digital Mode */
    sci->IODFTCTRL = 0x00000A00U
                   | (Loopbacktype << 1U);
	
/* USER CODE BEGIN (20) */
/* USER CODE END */
}

/** @fn void sciDisableLoopback(sciBASE_t *sci)
*   @brief Enable Loopback mode for self test
*   @param[in] sci        - sci module base address
*
*   This function disable the Loopback mode.
*/
void sciDisableLoopback(sciBASE_t *sci)
{
/* USER CODE BEGIN (21) */
/* USER CODE END */
    
	/* Disable Loopback Mode */
    sci->IODFTCTRL = 0x00000500U;
	
/* USER CODE BEGIN (22) */
/* USER CODE END */
}

/** @fn sciEnableNotification(sciBASE_t *sci, uint32 flags)
*   @brief Enable interrupts
*   @param[in] sci   - sci module base address
*   @param[in] flags - Interrupts to be enabled, can be ored value of:
*                      SCI_FE_INT    - framing error,
*                      SCI_OE_INT    - overrun error,
*                      SCI_PE_INT    - parity error,
*                      SCI_RX_INT    - receive buffer ready,
*                      SCI_TX_INT    - transmit buffer ready,
*                      SCI_WAKE_INT  - wakeup,
*                      SCI_BREAK_INT - break detect
*/
void sciEnableNotification(sciBASE_t *sci, uint32 flags)
{
    uint32 index = sci == sciREG ? 0U : 1U;

/* USER CODE BEGIN (23) */
/* USER CODE END */

    g_sciTransfer_t[index].mode |= (flags & SCI_TX_INT);
    sci->SETINT                = (flags & (~(SCI_TX_INT)));

/* USER CODE BEGIN (24) */
/* USER CODE END */
}


/** @fn sciDisableNotification(sciBASE_t *sci, uint32 flags)
*   @brief Disable interrupts
*   @param[in] sci   - sci module base address
*   @param[in] flags - Interrupts to be disabled, can be ored value of:
*                      SCI_FE_INT    - framing error,
*                      SCI_OE_INT    - overrun error,
*                      SCI_PE_INT    - parity error,
*                      SCI_RX_INT    - receive buffer ready,
*                      SCI_TX_INT    - transmit buffer ready,
*                      SCI_WAKE_INT  - wakeup,
*                      SCI_BREAK_INT - break detect
*/
void sciDisableNotification(sciBASE_t *sci, uint32 flags)
{
    uint32 index = sci == sciREG ? 0U : 1U;

/* USER CODE BEGIN (25) */
/* USER CODE END */

    g_sciTransfer_t[index].mode &= ~(flags & SCI_TX_INT);
    sci->CLRINT                = (flags & (~SCI_TX_INT));

/* USER CODE BEGIN (26) */
/* USER CODE END */
}

/** @fn void linHighLevelInterrupt(void)
*   @brief Level 0 Interrupt for SCILIN
*/
void linHighLevelInterrupt(void)
{
    uint32 vec = scilinREG->INTVECT0;

/* USER CODE BEGIN (35) */
/* USER CODE END */

    switch (vec)
    {
    case 1U:
        sciNotification(scilinREG, SCI_WAKE_INT);
        break;
    case 3U:
        sciNotification(scilinREG, SCI_PE_INT);
        break;
    case 6U:
        sciNotification(scilinREG, SCI_FE_INT);
        break;
    case 7U:
        sciNotification(scilinREG, SCI_BREAK_INT);
        break;
    case 9U:
        sciNotification(scilinREG, SCI_OE_INT);
        break;

    case 11U:
        /* receive */
        {   uint32 byte = (scilinREG->RD & 0x000000FFU);

            if (g_sciTransfer_t[1U].length > 0U)
            {
                *g_sciTransfer_t[1U].data++ = byte;
                g_sciTransfer_t[1U].length--;
                if (g_sciTransfer_t[1U].length == 0U)
                {
                    sciNotification(scilinREG, SCI_RX_INT);
                }
            }
        }
        break;

    case 12U:
        /* transmit */
        if (--g_sciTransfer_t[1U].length > 0U)
        {
            scilinREG->TD = *g_sciTransfer_t[1U].data++;
        }
        else
        {
            scilinREG->CLRINT = SCI_TX_INT;
            sciNotification(scilinREG, SCI_TX_INT);
        }
        break;

    default:
        /* phantom interrupt, clear flags and return */
        scilinREG->FLR = ~scilinREG->SETINTLVL & 0x07000303U;
        break;
    }
/* USER CODE BEGIN (36) */
/* USER CODE END */
}
/* USER CODE BEGIN (37) */
/* USER CODE END */

