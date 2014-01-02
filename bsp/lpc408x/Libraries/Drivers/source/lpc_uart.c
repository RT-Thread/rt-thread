/**********************************************************************
* $Id$      lpc_uart.c          2011-06-02
*//**
* @file     lpc_uart.c
* @brief    Contains all functions support for UART firmware library
*           on LPC
* @version  1.0
* @date     02. June. 2011
* @author   NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup UART
 * @{
 */
#ifdef __BUILD_WITH_EXAMPLE__
#include "lpc_libcfg.h"
#else
#include "lpc_libcfg_default.h"
#endif /* __BUILD_WITH_EXAMPLE__ */
#ifdef _UART

/* Includes ------------------------------------------------------------------- */
#include "lpc_uart.h"
#include "lpc_clkpwr.h"

/* Private Functions ---------------------------------------------------------- */

static Status uart_set_divisors(UART_ID_Type UartID, uint32_t baudrate);
static LPC_UART_TypeDef *uart_get_pointer(UART_ID_Type UartID);


/*********************************************************************//**
 * @brief       Determines best dividers to get a target clock rate
 * @param[in]   UARTx   Pointer to selected UART peripheral, should be:
 *              - UART_0: UART0 peripheral
 *              - UART_1: UART1 peripheral
 *              - UART_2: UART2 peripheral
 *              - UART_3: UART3 peripheral
 *              - UART_4: UART4 peripheral
 * @param[in]   baudrate Desired UART baud rate.
 * @return      Error status, could be:
 *              - SUCCESS
 *              - ERROR
 **********************************************************************/
static Status uart_set_divisors(UART_ID_Type UartID, uint32_t baudrate)
{
    Status errorStatus = ERROR;

    uint32_t uClk;
    uint32_t d, m, bestd, bestm, tmp;
    uint64_t best_divisor, divisor;
    uint32_t current_error, best_error;
    uint32_t recalcbaud;

    /* get UART block clock */
    uClk = CLKPWR_GetCLK(CLKPWR_CLKTYPE_PER);

    /* In the Uart IP block, baud rate is calculated using FDR and DLL-DLM registers
    * The formula is :
    * BaudRate= uClk * (mulFracDiv/(mulFracDiv+dividerAddFracDiv) / (16 * (DLL)
    * It involves floating point calculations. That's the reason the formulae are adjusted with
    * Multiply and divide method.*/
    
    /* The value of mulFracDiv and dividerAddFracDiv should comply to the following expressions:
    * 0 < mulFracDiv <= 15, 0 <= dividerAddFracDiv <= 15 */
    best_error = 0xFFFFFFFF; /* Worst case */
    bestd = 0;
    bestm = 0;
    best_divisor = 0;
    
    for (m = 1 ; m <= 15 ;m++)
    {
        for (d = 0 ; d < m ; d++)
        {
            divisor = ((uint64_t)uClk << 28)*m / (baudrate*(m+d));
            current_error = divisor & 0xFFFFFFFF;

            tmp = divisor>>32;

            /* Adjust error */
            if(current_error > ((uint32_t)1<<31))
            {
                current_error = -current_error;
                tmp++;
            }

            /* Out of range */
            if(tmp < 1 || tmp > 65536)
                continue;

            if( current_error < best_error)
            {
                best_error = current_error;
                best_divisor = tmp;
                bestd = d;
                bestm = m;
                
                if(best_error == 0) 
                    break;
            }
        } /* end of inner for loop */

        if (best_error == 0)
            break;
    } /* end of outer for loop  */

    /* can not find best match */
    if(best_divisor == 0) 
        return ERROR;

    recalcbaud = (uClk >> 4) * bestm / (best_divisor * (bestm + bestd));

    /* reuse best_error to evaluate baud error*/
    if(baudrate > recalcbaud) 
        best_error = baudrate - recalcbaud;
    else 
        best_error = recalcbaud -baudrate;

    best_error = best_error * 100 / baudrate;

    if (best_error < UART_ACCEPTED_BAUDRATE_ERROR)
    {
        if (UartID == UART_1)
        {
            LPC_UART1->LCR |= UART_LCR_DLAB_EN;
            
            LPC_UART1->DLM = UART_LOAD_DLM(best_divisor);
            
            LPC_UART1->DLL = UART_LOAD_DLL(best_divisor);
            
            /* Then reset DLAB bit */
            LPC_UART1->LCR &= (~UART_LCR_DLAB_EN) & UART_LCR_BITMASK;
            
            LPC_UART1->FDR = (UART_FDR_MULVAL(bestm)
                                                    | UART_FDR_DIVADDVAL(bestd)) & UART_FDR_BITMASK;
        }
        else if (UartID == UART_4)
        {
            LPC_UART4->LCR |= UART_LCR_DLAB_EN;
            
            LPC_UART4->DLM = UART_LOAD_DLM(best_divisor);
            
            LPC_UART4->DLL = UART_LOAD_DLL(best_divisor);
            
            /* Then reset DLAB bit */
            LPC_UART4->LCR &= (~UART_LCR_DLAB_EN) & UART_LCR_BITMASK;
            
            LPC_UART4->FDR = (UART_FDR_MULVAL(bestm)
                                                    | UART_FDR_DIVADDVAL(bestd)) & UART_FDR_BITMASK;
        }
            
        else
        {
            LPC_UART_TypeDef *UARTx = uart_get_pointer(UartID);
            UARTx->LCR |= UART_LCR_DLAB_EN;
            
            UARTx->DLM = UART_LOAD_DLM(best_divisor);
            
            UARTx->DLL = UART_LOAD_DLL(best_divisor);
            
            /* Then reset DLAB bit */
            UARTx->LCR &= (~UART_LCR_DLAB_EN) & UART_LCR_BITMASK;
            
            UARTx->FDR = (UART_FDR_MULVAL(bestm) \
                            | UART_FDR_DIVADDVAL(bestd)) & UART_FDR_BITMASK;
        }
        errorStatus = SUCCESS;
    }

    return errorStatus;
}
/*********************************************************************//**
 * @brief       Get the pointer of a given Uart
 * @param[in]   UARTx   Pointer to selected UART peripheral, should be:
 *              - UART_0: UART0 peripheral
 *              - UART_1: UART1 peripheral
 *              - UART_2: UART2 peripheral
 *              - UART_3: UART3 peripheral
 *              - UART_4: UART4 peripheral
 * @return      LPC_UART0~LPC_UART4
 **********************************************************************/
LPC_UART_TypeDef *uart_get_pointer(UART_ID_Type UartID)
{
    LPC_UART_TypeDef *UARTx = NULL;
    switch(UartID)
    {
        case UART_0:
            UARTx = LPC_UART0;
            break;
        case UART_2:
            UARTx = LPC_UART2;
            break;
        case UART_3:
            UARTx = LPC_UART3;
            break;
        default:
            break;
    }
    return UARTx;
}

/* End of Private Functions ---------------------------------------------------- */


/* Public Functions ----------------------------------------------------------- */
/** @addtogroup UART_Public_Functions
 * @{
 */
/* UART Init/DeInit functions -------------------------------------------------*/
/********************************************************************//**
 * @brief       Initializes the UARTx peripheral according to the specified
 *               parameters in the UART_ConfigStruct.
 * @param[in]   UARTx   UART peripheral selected, should be:
 *              - UART_0: UART0 peripheral
 *              - UART_1: UART1 peripheral
 *              - UART_2: UART2 peripheral
 *              - UART_3: UART3 peripheral
 *              - UART_4: UART4 peripheral
 * @param[in]   UART_ConfigStruct Pointer to a UART_CFG_Type structure
*                    that contains the configuration information for the
*                    specified UART peripheral.
 * @return      None
 *********************************************************************/
void UART_Init(UART_ID_Type UartID, UART_CFG_Type *UART_ConfigStruct)
{
    uint32_t tmp;
    switch (UartID)
    {
        case UART_0:
        case UART_2:
        case UART_3:
        {
            LPC_UART_TypeDef *UARTx = uart_get_pointer(UartID);
            if(UartID == UART_0)
                /* Set up clock and power for UART module */
                CLKPWR_ConfigPPWR (CLKPWR_PCONP_PCUART0, ENABLE);
            else if(UartID == UART_2)
                /* Set up clock and power for UART module */
                CLKPWR_ConfigPPWR (CLKPWR_PCONP_PCUART2, ENABLE);
            else if(UartID == UART_3)
                /* Set up clock and power for UART module */
                CLKPWR_ConfigPPWR (CLKPWR_PCONP_PCUART3, ENABLE);;
            /* FIFOs are empty */
            UARTx->FCR = ( UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TX_RS);

            // Disable FIFO
            UARTx->FCR = 0;

            // Dummy reading
            while (UARTx->LSR & UART_LSR_RDR)
            {
                tmp = UARTx->RBR;
            }

            UARTx->TER = UART_TER_TXEN;

            // Wait for current transmit complete
            while (!(UARTx->LSR & UART_LSR_THRE));

            // Disable Tx
            UARTx->TER = 0;

            // Disable interrupt
            UARTx->IER = 0;

            // Set LCR to default state
            UARTx->LCR = 0;

            // Set ACR to default state
            UARTx->ACR = 0;

            // Set RS485 control to default state
            UARTx->RS485CTRL = 0;

            // Set RS485 delay timer to default state
            UARTx->RS485DLY = 0;

            // Set RS485 addr match to default state
            UARTx->ADRMATCH = 0;

            // Dummy reading
            tmp = UARTx->LSR;
        }
        break;
        case UART_1:
        {
            /* Set up clock and power for UART module */
            CLKPWR_ConfigPPWR (CLKPWR_PCONP_PCUART1, ENABLE);

            /* FIFOs are empty */
            LPC_UART1->FCR = ( UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TX_RS);

            // Disable FIFO
            LPC_UART1->FCR = 0;

            // Dummy reading
            while (LPC_UART1->LSR & UART_LSR_RDR)
            {
                tmp = LPC_UART1->RBR;
            }

            LPC_UART1->TER = UART_TER_TXEN;

            // Wait for current transmit complete
            while (!(LPC_UART1->LSR & UART_LSR_THRE));

            // Disable Tx
            LPC_UART1->TER = 0;

            // Disable interrupt
            LPC_UART1->IER = 0;

            // Set LCR to default state
            LPC_UART1->LCR = 0;

            // Set ACR to default state
            LPC_UART1->ACR = 0;

            // Set RS485 control to default state
            LPC_UART1->RS485CTRL = 0;

            // Set RS485 delay timer to default state
            LPC_UART1->RS485DLY = 0;

            // Set RS485 addr match to default state
            LPC_UART1->ADRMATCH = 0;

            // Dummy reading
            tmp = LPC_UART1->LSR;

            // Set Modem Control to default state
            LPC_UART1->MCR = 0;

            //Dummy Reading to Clear Status
            tmp = LPC_UART1->MSR;
        }
        break;
        case UART_4:
        {
            /* Set up clock and power for UART module */
            CLKPWR_ConfigPPWR (CLKPWR_PCONP_PCUART4, ENABLE);

            /* FIFOs are empty */
            LPC_UART4->FCR = ( UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TX_RS);

            // Disable FIFO
            LPC_UART4->FCR = 0;

            // Dummy reading
            while (LPC_UART4->LSR & UART_LSR_RDR)
            {
                tmp = LPC_UART4->RBR;
            }

            LPC_UART4->TER = UART4_TER_TXEN;

            // Wait for current transmit complete
            while (!(LPC_UART4->LSR & UART_LSR_THRE));

            // Disable Tx
            LPC_UART4->TER = 0;

            // Disable interrupt
            LPC_UART4->IER = 0;

            // Set LCR to default state
            LPC_UART4->LCR = 0;

            // Set ACR to default state
            LPC_UART4->ACR = 0;

            // Set RS485 control to default state
            LPC_UART4->RS485CTRL = 0;

            // Set RS485 delay timer to default state
            LPC_UART4->RS485DLY = 0;

            // Set RS485 addr match to default state
            LPC_UART4->ADRMATCH = 0;

            // Dummy reading
            tmp = LPC_UART4->LSR;

            // Set IrDA Mode to default state
            LPC_UART4->ICR = 0;
        }
        break;
    }

    // Set Line Control register ----------------------------

    uart_set_divisors(UartID, (UART_ConfigStruct->Baud_rate));

    if (UartID == UART_1)
    {
        tmp = (LPC_UART1->LCR & (UART_LCR_DLAB_EN | UART_LCR_BREAK_EN)) \
                                                    & UART_LCR_BITMASK;
    }
    else if (UartID == UART_4)
    {
        tmp = (LPC_UART4->LCR & (UART_LCR_DLAB_EN | UART_LCR_BREAK_EN)) \
                                                    & UART_LCR_BITMASK;
    }   
    else
    {
        LPC_UART_TypeDef *UARTx = uart_get_pointer(UartID);
        tmp = (UARTx->LCR & (UART_LCR_DLAB_EN | UART_LCR_BREAK_EN)) & UART_LCR_BITMASK;
    }

    switch (UART_ConfigStruct->Databits)
    {
        case UART_DATABIT_5:
            tmp |= UART_LCR_WLEN5;
            break;

        case UART_DATABIT_6:
            tmp |= UART_LCR_WLEN6;
            break;

        case UART_DATABIT_7:
            tmp |= UART_LCR_WLEN7;
            break;

        case UART_DATABIT_8:

        default:
            tmp |= UART_LCR_WLEN8;
            break;
    }

    if (UART_ConfigStruct->Parity == UART_PARITY_NONE)
    {
        // Do nothing...
    }
    else
    {
        tmp |= UART_LCR_PARITY_EN;
        switch (UART_ConfigStruct->Parity)
        {
            case UART_PARITY_ODD:
                tmp |= UART_LCR_PARITY_ODD;
                break;

            case UART_PARITY_EVEN:
                tmp |= UART_LCR_PARITY_EVEN;
                break;

            case UART_PARITY_SP_1:
                tmp |= UART_LCR_PARITY_F_1;
                break;

            case UART_PARITY_SP_0:
                tmp |= UART_LCR_PARITY_F_0;
                break;

            default:
                break;
        }
    }

    switch (UART_ConfigStruct->Stopbits)
    {
        case UART_STOPBIT_2:
            tmp |= UART_LCR_STOPBIT_SEL;
            break;

        case UART_STOPBIT_1:

        default:
            // Do no thing
            break;
    }


    // Write back to LCR, configure FIFO and Disable Tx
    if (UartID == UART_1)
    {
        LPC_UART1->LCR = (uint8_t)(tmp & UART_LCR_BITMASK);
    }
    else if (UartID == UART_4)
    {
        LPC_UART4->LCR = (uint8_t)(tmp & UART_LCR_BITMASK);
    }   
    else
    {
        LPC_UART_TypeDef *UARTx = uart_get_pointer(UartID);
        UARTx->LCR = (uint8_t)(tmp & UART_LCR_BITMASK);
    }
}

/*********************************************************************//**
 * @brief       De-initializes the UARTx peripheral registers to their
 *                  default reset values.
 * @param[in]   UartID  UART peripheral selected, should be:
 *              - UART_0: UART0 peripheral
 *              - UART_1: UART1 peripheral
 *              - UART_2: UART2 peripheral
 *              - UART_3: UART3 peripheral
 *              - UART_4: UART4 peripheral
 * @return      None
 **********************************************************************/
void UART_DeInit(UART_ID_Type UartID)
{
    UART_TxCmd(UartID, DISABLE);
    if (UartID == UART_0)
    {
        /* Set up clock and power for UART module */
        CLKPWR_ConfigPPWR (CLKPWR_PCONP_PCUART0, DISABLE);
    }

    else if (UartID == UART_1)
    {
        /* Set up clock and power for UART module */
        CLKPWR_ConfigPPWR (CLKPWR_PCONP_PCUART1, DISABLE);
    }

    else if (UartID == UART_2)
    {
        /* Set up clock and power for UART module */
        CLKPWR_ConfigPPWR (CLKPWR_PCONP_PCUART2, DISABLE);
    }

    else if (UartID == UART_3)
    {
        /* Set up clock and power for UART module */
        CLKPWR_ConfigPPWR (CLKPWR_PCONP_PCUART3, DISABLE);
    }
    else if (UartID == UART_4)
    {
        /* Set up clock and power for UART module */
        CLKPWR_ConfigPPWR (CLKPWR_PCONP_PCUART4, DISABLE);
    }
}

/*****************************************************************************//**
* @brief        Fills each UART_InitStruct member with its default value:
*               - 115200 bps
*               - 8-bit data
*               - 1 Stopbit
*               - None Parity
* @param[in]    UART_InitStruct Pointer to a UART_CFG_Type structure
*                    which will be initialized.
* @return       None
*******************************************************************************/
void UART_ConfigStructInit(UART_CFG_Type *UART_InitStruct)
{
    UART_InitStruct->Baud_rate = 115200;

    UART_InitStruct->Databits = UART_DATABIT_8;

    UART_InitStruct->Parity = UART_PARITY_NONE;

    UART_InitStruct->Stopbits = UART_STOPBIT_1;
}

/* UART Send/Recieve functions -------------------------------------------------*/
/*********************************************************************//**
 * @brief       Transmit a single data through UART peripheral
 * @param[in]   UARTx   UART peripheral selected, should be:
 *              - UART_0: UART0 peripheral
 *              - UART_1: UART1 peripheral
 *              - UART_2: UART2 peripheral
 *              - UART_3: UART3 peripheral
 *              - UART_4: UART4 peripheral
 * @param[in]   Data    Data to transmit (must be 8-bit long)
 * @return      None
 **********************************************************************/
void UART_SendByte(UART_ID_Type UartID, uint8_t Data)
{
    switch (UartID)
    {
        case UART_0:
            LPC_UART0->THR = Data & UART_THR_MASKBIT;
            break;
        case UART_1:
            LPC_UART1->THR = Data & UART_THR_MASKBIT;
            break;  
        case UART_2:
            LPC_UART2->THR = Data & UART_THR_MASKBIT;
            break;
        case UART_3:
            LPC_UART3->THR = Data & UART_THR_MASKBIT;
            break;
        case UART_4:
            LPC_UART4->THR = Data & UART_THR_MASKBIT;
            break;
    }

}


/*********************************************************************//**
 * @brief       Receive a single data from UART peripheral
 * @param[in]   UARTx   UART peripheral selected, should be:
 *              - UART_0: UART0 peripheral
 *              - UART_1: UART1 peripheral
 *              - UART_2: UART2 peripheral
 *              - UART_3: UART3 peripheral
 *              - UART_4: UART4 peripheral
 * @return      Data received
 **********************************************************************/
uint8_t UART_ReceiveByte(UART_ID_Type UartID)
{
    switch (UartID)
    {
        case UART_0:
            return (LPC_UART0->RBR & UART_RBR_MASKBIT);
        case UART_1:
            return (LPC_UART1->RBR & UART_RBR_MASKBIT); 
        case UART_2:
            return (LPC_UART2->RBR & UART_RBR_MASKBIT);
        case UART_3:
            return (LPC_UART3->RBR & UART_RBR_MASKBIT);
        case UART_4:
            return (LPC_UART4->RBR & UART_RBR_MASKBIT);
    }
    return 0x00;
}

/*********************************************************************//**
 * @brief       Send a block of data via UART peripheral
 * @param[in]   UARTx   Selected UART peripheral used to send data, should be:
 *              - UART_0: UART0 peripheral
 *              - UART_1: UART1 peripheral
 *              - UART_2: UART2 peripheral
 *              - UART_3: UART3 peripheral
 *              - UART_4: UART4 peripheral
 * @param[in]   txbuf   Pointer to Transmit buffer
 * @param[in]   buflen  Length of Transmit buffer
 * @param[in]   flag    Flag used in  UART transfer, should be
 *                      NONE_BLOCKING or BLOCKING
 * @return      Number of bytes sent.
 *
 * Note: when using UART in BLOCKING mode, a time-out condition is used
 * via defined symbol UART_BLOCKING_TIMEOUT.
 **********************************************************************/
uint32_t UART_Send(UART_ID_Type UartID, uint8_t *txbuf,
                            uint32_t buflen, TRANSFER_BLOCK_Type flag)
{
    uint32_t bToSend, bSent, timeOut, fifo_cnt;
    uint8_t *pChar = txbuf;
    __IO uint32_t *LSR = NULL;

    switch (UartID)
    {
        case UART_0:
            LSR = (__IO uint32_t *)&LPC_UART0->LSR;
            break;
        case UART_1:
            LSR = (__IO uint32_t *)&LPC_UART1->LSR;
            break;
        case UART_2:
            LSR = (__IO uint32_t *)&LPC_UART2->LSR;
            break;
        case UART_3:
            LSR = (__IO uint32_t *)&LPC_UART3->LSR;
            break;
        case UART_4:
            LSR = (__IO uint32_t *)&LPC_UART4->LSR;
            break;
    }

    bToSend = buflen;

    // blocking mode
    if (flag == BLOCKING)
    {
        bSent = 0;
        while (bToSend)
        {
            timeOut = UART_BLOCKING_TIMEOUT;

            // Wait for THR empty with timeout
            while (!(*LSR & UART_LSR_THRE))
            {
                if (timeOut == 0)
                    break;

                timeOut--;
            }

            // Time out!
            if(timeOut == 0)
                break;

            fifo_cnt = UART_TX_FIFO_SIZE;

            while (fifo_cnt && bToSend)
            {
                UART_SendByte(UartID, (*pChar++));

                fifo_cnt--;

                bToSend--;

                bSent++;
            }
        }
    }

    // None blocking mode
    else
    {
        bSent = 0;
        while (bToSend)
        {
            if (bToSend == 0)
                break;

            if (!(*LSR & UART_LSR_THRE))
            {
                break;
            }

            fifo_cnt = UART_TX_FIFO_SIZE;

            while (fifo_cnt && bToSend)
            {
                UART_SendByte(UartID, (*pChar++));

                bToSend--;

                fifo_cnt--;

                bSent++;
            }
        }
    }

    return bSent;
}

/*********************************************************************//**
 * @brief       Receive a block of data via UART peripheral
 * @param[in]   UARTx   Selected UART peripheral used to send data,
 *              should be:
 *              - UART_0: UART0 peripheral
 *              - UART_1: UART1 peripheral
 *              - UART_2: UART2 peripheral
 *              - UART_3: UART3 peripheral
 *              - UART_4: UART4 peripheral
 * @param[out]  rxbuf   Pointer to Received buffer
 * @param[in]   buflen  Length of Received buffer
 * @param[in]   flag    Flag mode, should be NONE_BLOCKING or BLOCKING

 * @return      Number of bytes received
 *
 * Note: when using UART in BLOCKING mode, a time-out condition is used
 * via defined symbol UART_BLOCKING_TIMEOUT.
 **********************************************************************/
uint32_t UART_Receive(UART_ID_Type UartID, uint8_t *rxbuf,
                                uint32_t buflen, TRANSFER_BLOCK_Type flag)
{
    uint32_t bToRecv, bRecv, timeOut;
    uint8_t *pChar = rxbuf;
    __IO uint32_t *LSR = NULL;

    switch (UartID)
    {
        case UART_0:
            LSR = (__IO uint32_t *)&LPC_UART0->LSR;
            break;
        case UART_1:
            LSR = (__IO uint32_t *)&LPC_UART1->LSR;
            break;
        case UART_2:
            LSR = (__IO uint32_t *)&LPC_UART2->LSR;
            break;
        case UART_3:
            LSR = (__IO uint32_t *)&LPC_UART3->LSR;
            break;
        case UART_4:
            LSR = (__IO uint32_t *)&LPC_UART4->LSR;
            break;
    }
    
    bToRecv = buflen;

    // Blocking mode
    if (flag == BLOCKING)
    {
        bRecv = 0;
        while (bToRecv)
        {
            timeOut = UART_BLOCKING_TIMEOUT;
            while (!(*LSR & UART_LSR_RDR))
            {
                if (timeOut == 0)
                    break;

                timeOut--;
            }

            // Time out!
            if(timeOut == 0)
                break;

            // Get data from the buffer
            (*pChar++) = UART_ReceiveByte(UartID);

            bToRecv--;

            bRecv++;
        }
    }
    // None blocking mode
    else
    {
        bRecv = 0;
        while (bToRecv)
        {
            if (!(*LSR & UART_LSR_RDR))
            {
                break;
            }
            else
            {
                (*pChar++) = UART_ReceiveByte(UartID);

                bRecv++;

                bToRecv--;
            }
        }
    }

    return bRecv;
}

/*********************************************************************//**
 * @brief       Force BREAK character on UART line, output pin UARTx TXD is
                forced to logic 0.
 * @param[in]   UARTx   UART peripheral selected, should be:
 *              - UART_0: UART0 peripheral
 *              - UART_1: UART1 peripheral
 *              - UART_2: UART2 peripheral
 *              - UART_3: UART3 peripheral
 *              - UART_4: UART4 peripheral
 * @return      None
 **********************************************************************/
void UART_ForceBreak(UART_ID_Type UartID)
{
    switch (UartID)
    {
        case UART_0:
            LPC_UART0->LCR |= UART_LCR_BREAK_EN;
            break;
        case UART_1:
            LPC_UART1->LCR |= UART_LCR_BREAK_EN;
            break;
        case UART_2:
            LPC_UART2->LCR |= UART_LCR_BREAK_EN;
            break;
        case UART_3:
            LPC_UART3->LCR |= UART_LCR_BREAK_EN;
            break;
        case UART_4:
            LPC_UART4->LCR |= UART_LCR_BREAK_EN;
            break;
    }
}


/********************************************************************//**
 * @brief       Enable or disable specified UART interrupt.
 * @param[in]   UARTx   UART peripheral selected, should be
 *              - UART_0: UART0 peripheral
 *              - UART_1: UART1 peripheral
 *              - UART_2: UART2 peripheral
 *              - UART_3: UART3 peripheral
 *              - UART_4: UART4 peripheral
 * @param[in]   UARTIntCfg  Specifies the interrupt flag,
 *              should be one of the following:
                - UART_INTCFG_RBR   :  RBR Interrupt enable
                - UART_INTCFG_THRE  :  THR Interrupt enable
                - UART_INTCFG_RLS   :  RX line status interrupt enable
                - UART1_INTCFG_MS   :  Modem status interrupt enable (UART1 only)
                - UART1_INTCFG_CTS  :  CTS1 signal transition interrupt enable (UART1 only)
                - UART_INTCFG_ABEO  :  Enables the end of auto-baud interrupt
                - UART_INTCFG_ABTO  :  Enables the auto-baud time-out interrupt
 * @param[in]   NewState New state of specified UART interrupt type,
 *              should be:
 *              - ENALBE: Enable this UART interrupt type.
*               - DISALBE: Disable this UART interrupt type.
 * @return      None
 *********************************************************************/
void UART_IntConfig(UART_ID_Type UartID, UART_INT_Type UARTIntCfg, FunctionalState NewState)
{
    uint32_t tmp;
    __IO uint32_t *IER = NULL;
    uint32_t IERMask = 0;

    switch (UartID)
    {
        case UART_0:
            IER = &LPC_UART0->IER;
            IERMask = UART_IER_BITMASK;
            break;
        case UART_1:
            IER = &LPC_UART1->IER;
            IERMask = UART1_IER_BITMASK;
            break;
        case UART_2:
            IER = &LPC_UART2->IER;
            IERMask = UART_IER_BITMASK;
            break;
        case UART_3:
            IER = &LPC_UART3->IER;
            IERMask = UART_IER_BITMASK;
            break;
        case UART_4:
            IER = &LPC_UART4->IER;
            IERMask = UART_IER_BITMASK;
            break;
    }


    switch(UARTIntCfg)
    {
        case UART_INTCFG_RBR:
            tmp = UART_IER_RBRINT_EN;
            break;

        case UART_INTCFG_THRE:
            tmp = UART_IER_THREINT_EN;
            break;

        case UART_INTCFG_RLS:
            tmp = UART_IER_RLSINT_EN;
            break;

        case UART_INTCFG_MS:
            tmp = UART1_IER_MSINT_EN;
            break;

        case UART_INTCFG_CTS:
            tmp = UART1_IER_CTSINT_EN;
            break;

        case UART_INTCFG_ABEO:
            tmp = UART_IER_ABEOINT_EN;
            break;

        case UART_INTCFG_ABTO:
            tmp = UART_IER_ABTOINT_EN;
            break;
    }

    if (NewState == ENABLE)
    {
        *IER |= tmp& IERMask;
    }
    else
    {
        *IER &= (~tmp) & IERMask;
    }
}


/********************************************************************//**
 * @brief       Get current value of Line Status register in UART peripheral.
 * @param[in]   UARTx   UART peripheral selected, should be:
 *              - UART_0: UART0 peripheral
 *              - UART_1: UART1 peripheral
 *              - UART_2: UART2 peripheral
 *              - UART_3: UART3 peripheral
 *              - UART_4: UART4 peripheral
 * @return      Current value of Line Status register in UART peripheral.
 * Note:    The return value of this function must be ANDed with each member in
 *          UART_LS_Type enumeration to determine current flag status
 *          corresponding to each Line status type. Because some flags in
 *          Line Status register will be cleared after reading, the next reading
 *          Line Status register could not be correct. So this function used to
 *          read Line status register in one time only, then the return value
 *          used to check all flags.
 *********************************************************************/
uint8_t UART_GetLineStatus(UART_ID_Type UartID)
{
    switch (UartID)
    {
        case UART_0:
            return ((LPC_UART0->LSR) & UART_LSR_BITMASK);
        case UART_1:
            return ((LPC_UART1->LSR) & UART_LSR_BITMASK);
        case UART_2:
            return ((LPC_UART2->LSR) & UART_LSR_BITMASK);
        case UART_3:
            return ((LPC_UART3->LSR) & UART_LSR_BITMASK);
        case UART_4:
            return ((LPC_UART4->LSR) & UART_LSR_BITMASK);
    }
    return 0;
}

/********************************************************************//**
 * @brief       Get Interrupt Identification value
 * @param[in]   UARTx   UART peripheral selected, should be:
 *              - UART_0: UART0 peripheral
 *              - UART_1: UART1 peripheral
 *              - UART_2: UART2 peripheral
 *              - UART_3: UART3 peripheral
 *              - UART_4: UART4 peripheral
 * @return      Current value of UART UIIR register in UART peripheral.
 *********************************************************************/
uint32_t UART_GetIntId(UART_ID_Type UartID)
{
    switch (UartID)
    {
        case UART_0:
            return ((LPC_UART0->IIR) & UART_IIR_BITMASK);
        case UART_1:
            return ((LPC_UART1->IIR) & UART_IIR_BITMASK);
        case UART_2:
            return ((LPC_UART2->IIR) & UART_IIR_BITMASK);
        case UART_3:
            return ((LPC_UART3->IIR) & UART_IIR_BITMASK);
        case UART_4:
            return ((LPC_UART4->IIR) & UART_IIR_BITMASK);
    }
    return 0;
}

/*********************************************************************//**
 * @brief       Check whether if UART is busy or not
 * @param[in]   UARTx   UART peripheral selected, should be:
 *              - UART_0: UART0 peripheral
 *              - UART_1: UART1 peripheral
 *              - UART_2: UART2 peripheral
 *              - UART_3: UART3 peripheral
 *              - UART_4: UART4 peripheral
 * @return      RESET if UART is not busy, otherwise return SET.
 **********************************************************************/
FlagStatus UART_CheckBusy(UART_ID_Type UartID)
{
    uint32_t LSR = 0;
    switch (UartID)
    {
        case UART_0:
            LSR = (LPC_UART0)->LSR & UART_LSR_TEMT;
            break;
        case UART_1:
            LSR = (LPC_UART1)->LSR & UART_LSR_TEMT;
            break;
        case UART_2:
            LSR = (LPC_UART2)->LSR & UART_LSR_TEMT;
            break;
        case UART_3:
            LSR = (LPC_UART3)->LSR & UART_LSR_TEMT;
            break;
        case UART_4:
            LSR = (LPC_UART4)->LSR & UART_LSR_TEMT;
            break;
    }
    
    if (LSR & UART_LSR_TEMT)
    {
        return RESET;
    }
    return SET;
}


/*********************************************************************//**
 * @brief       Configure FIFO function on selected UART peripheral
 * @param[in]   UARTx   UART peripheral selected, should be:
 *              - UART_0: UART0 peripheral
 *              - UART_1: UART1 peripheral
 *              - UART_2: UART2 peripheral
 *              - UART_3: UART3 peripheral
 *              - UART_4: UART4 peripheral
 * @param[in]   FIFOCfg Pointer to a UART_FIFO_CFG_Type Structure that
 *                      contains specified information about FIFO configuration
 * @return      none
 **********************************************************************/
void UART_FIFOConfig(UART_ID_Type UartID, UART_FIFO_CFG_Type *FIFOCfg)
{
    uint8_t tmp = 0;

    tmp |= UART_FCR_FIFO_EN;

    switch (FIFOCfg->FIFO_Level)
    {
        case UART_FIFO_TRGLEV0:
            tmp |= UART_FCR_TRG_LEV0;
            break;

        case UART_FIFO_TRGLEV1:
            tmp |= UART_FCR_TRG_LEV1;
            break;

        case UART_FIFO_TRGLEV2:
            tmp |= UART_FCR_TRG_LEV2;
            break;

        case UART_FIFO_TRGLEV3:

        default:
            tmp |= UART_FCR_TRG_LEV3;
            break;
    }

    if (FIFOCfg->FIFO_ResetTxBuf == ENABLE)
    {
        tmp |= UART_FCR_TX_RS;
    }

    if (FIFOCfg->FIFO_ResetRxBuf == ENABLE)
    {
        tmp |= UART_FCR_RX_RS;
    }

    if (FIFOCfg->FIFO_DMAMode == ENABLE)
    {
        tmp |= UART_FCR_DMAMODE_SEL;
    }


    //write to FIFO control register
    switch (UartID)
    {
        case UART_0:
            LPC_UART0->FCR = tmp & UART_FCR_BITMASK;
            break;
        case UART_1:
            LPC_UART1->FCR = tmp & UART_FCR_BITMASK;
            break;
        case UART_2:
            LPC_UART2->FCR = tmp & UART_FCR_BITMASK;
            break;
        case UART_3:
            LPC_UART3->FCR = tmp & UART_FCR_BITMASK;
            break;
        case UART_4:
            LPC_UART4->FCR = tmp & UART_FCR_BITMASK;
            break;
    }
}

/*****************************************************************************//**
* @brief        Fills each UART_FIFOInitStruct member with its default value:
*               - FIFO_DMAMode = DISABLE
*               - FIFO_Level = UART_FIFO_TRGLEV0
*               - FIFO_ResetRxBuf = ENABLE
*               - FIFO_ResetTxBuf = ENABLE
*               - FIFO_State = ENABLE
* @param[in]    UART_FIFOInitStruct Pointer to a UART_FIFO_CFG_Type structure
*                    which will be initialized.
* @return       None
*******************************************************************************/
void UART_FIFOConfigStructInit(UART_FIFO_CFG_Type *UART_FIFOInitStruct)
{
    UART_FIFOInitStruct->FIFO_DMAMode = DISABLE;

    UART_FIFOInitStruct->FIFO_Level = UART_FIFO_TRGLEV0;

    UART_FIFOInitStruct->FIFO_ResetRxBuf = ENABLE;

    UART_FIFOInitStruct->FIFO_ResetTxBuf = ENABLE;
}


/*********************************************************************//**
 * @brief       Start/Stop Auto Baudrate activity
 * @param[in]   UARTx   UART peripheral selected, should be
 *              - UART_0: UART0 peripheral
 *              - UART_1: UART1 peripheral
 *              - UART_2: UART2 peripheral
 *              - UART_3: UART3 peripheral
 *              - UART_4: UART4 peripheral
 * @param[in]   ABConfigStruct  A pointer to UART_AB_CFG_Type structure that
 *                              contains specified information about UART
 *                              auto baudrate configuration
 * @param[in]   NewState New State of Auto baudrate activity, should be:
 *              - ENABLE: Start this activity
 *              - DISABLE: Stop this activity
 * Note:        Auto-baudrate mode enable bit will be cleared once this mode
 *              completed.
 * @return      none
 **********************************************************************/
void UART_ABCmd(UART_ID_Type UartID, UART_AB_CFG_Type *ABConfigStruct,
                            FunctionalState NewState)
{
    uint32_t tmp;

    tmp = 0;
    if (NewState == ENABLE)
    {
        if (ABConfigStruct->ABMode == UART_AUTOBAUD_MODE1)
        {
            tmp |= UART_ACR_MODE;
        }
        if (ABConfigStruct->AutoRestart == ENABLE)
        {
            tmp |= UART_ACR_AUTO_RESTART;
        }
    }

    if (UartID == UART_1)
    {
        if (NewState == ENABLE)
        {
            // Clear DLL and DLM value
            LPC_UART1->LCR |= UART_LCR_DLAB_EN;

            LPC_UART1->DLL = 0;

            LPC_UART1->DLM = 0;

            LPC_UART1->LCR &= ~UART_LCR_DLAB_EN;

            // FDR value must be reset to default value
            LPC_UART1->FDR = 0x10;

            LPC_UART1->ACR = UART_ACR_START | tmp;
        }
        else
        {
            LPC_UART1->ACR = 0;
        }
    }
    else if (UartID == UART_4)
    {
        if (NewState == ENABLE)
        {
            // Clear DLL and DLM value
            LPC_UART4->LCR |= UART_LCR_DLAB_EN;

            LPC_UART4->DLL = 0;

            LPC_UART4->DLM = 0;

            LPC_UART4->LCR &= ~UART_LCR_DLAB_EN;

            // FDR value must be reset to default value
            LPC_UART4->FDR = 0x10;

            LPC_UART4->ACR = UART_ACR_START | tmp;
        }
        else
        {
            LPC_UART4->ACR = 0;
        }
    }
    else
    {
        LPC_UART_TypeDef *UARTx = uart_get_pointer(UartID);
        if (NewState == ENABLE)
        {
            // Clear DLL and DLM value
            UARTx->LCR |= UART_LCR_DLAB_EN;

            UARTx->DLL = 0;

            UARTx->DLM = 0;

            UARTx->LCR &= ~UART_LCR_DLAB_EN;

            // FDR value must be reset to default value
            UARTx->FDR = 0x10;

            UARTx->ACR = UART_ACR_START | tmp;
        }
        else
        {
            UARTx->ACR = 0;
        }
    }
}

/*********************************************************************//**
 * @brief       Clear Autobaud Interrupt Pending
 * @param[in]   UARTx   UART peripheral selected, should be
 *              - UART_0: UART0 peripheral
 *              - UART_1: UART1 peripheral
 *              - UART_2: UART2 peripheral
 *              - UART_3: UART3 peripheral
 *              - UART_4: UART4 peripheral
 * @param[in]   ABIntType   type of auto-baud interrupt, should be:
 *              - UART_AUTOBAUD_INTSTAT_ABEO: End of Auto-baud interrupt
 *              - UART_AUTOBAUD_INTSTAT_ABTO: Auto-baud time out interrupt
 * @return      none
 **********************************************************************/
void UART_ABClearIntPending(UART_ID_Type UartID, UART_ABEO_Type ABIntType)
{
    if (UartID == UART_1)
    {
        LPC_UART1->ACR |= ABIntType;
    }
    else if (UartID == UART_4)
    {
        LPC_UART4->ACR |= ABIntType;
    }
    else
    {   
        LPC_UART_TypeDef *UARTx = uart_get_pointer(UartID);
        UARTx->ACR |= ABIntType;
    }
}

/*********************************************************************//**
 * @brief       Enable/Disable transmission on UART TxD pin
 * @param[in]   UARTx   UART peripheral selected, should be:
 *              - UART_0: UART0 peripheral
 *              - UART_1: UART1 peripheral
 *              - UART_2: UART2 peripheral
 *              - UART_3: UART3 peripheral
 *              - UART_4: UART4 peripheral
 * @param[in]   NewState New State of Tx transmission function, should be:
 *              - ENABLE: Enable this function
                - DISABLE: Disable this function
 * @return none
 **********************************************************************/
void UART_TxCmd(UART_ID_Type UartID, FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        if (UartID == UART_1)
        {
            LPC_UART1->TER |= UART_TER_TXEN;
        }
        else if (UartID == UART_4)
        {
            LPC_UART4->TER |= UART4_TER_TXEN;
        }
        else
        {
            LPC_UART_TypeDef *UARTx = uart_get_pointer(UartID);
            UARTx->TER |= UART_TER_TXEN;
        }
    }
    else
    {
        if (UartID == UART_1)                     
        {
            LPC_UART1->TER &= (~UART_TER_TXEN) & UART_TER_BITMASK;
        }
        else if (UartID == UART_4)
        {
            LPC_UART4->TER &= (~UART4_TER_TXEN) & UART4_TER_BITMASK;
        }
        else
        {
            LPC_UART_TypeDef *UARTx = uart_get_pointer(UartID);
            UARTx->TER &= (~UART_TER_TXEN) & UART_TER_BITMASK;
        }
    }
}

/* UART IrDA functions ---------------------------------------------------*/
/*********************************************************************//**
 * @brief       Enable or disable inverting serial input function of IrDA
 *              on UART peripheral.
 * @param[in]   UARTx UART peripheral selected, should be LPC_UART4 (only)
 * @param[in]   NewState New state of inverting serial input, should be:
 *              - ENABLE: Enable this function.
 *              - DISABLE: Disable this function.
 * @return none
 **********************************************************************/
void UART_IrDAInvtInputCmd(UART_ID_Type UartID, FunctionalState NewState)
{
    if (UartID != UART_4)
        return;
    
    if (NewState == ENABLE)
    {
        LPC_UART4->ICR |= UART_ICR_IRDAINV;
    }
    else if (NewState == DISABLE)
    {
        LPC_UART4->ICR &= (~UART_ICR_IRDAINV) & UART_ICR_BITMASK;
    }
    
}


/*********************************************************************//**
 * @brief       Enable or disable IrDA function on UART peripheral.
 * @param[in]   UARTx UART peripheral selected, should be LPC_UART4 (only)
 * @param[in]   NewState New state of IrDA function, should be:
 *              - ENABLE: Enable this function.
 *              - DISABLE: Disable this function.
 * @return none
 **********************************************************************/
void UART_IrDACmd(UART_ID_Type UartID, FunctionalState NewState)
{
    if (UartID != UART_4)
        return;
    
    if (NewState == ENABLE)
    {
        LPC_UART4->ICR |= UART_ICR_IRDAEN;
    }
    else
    {
        LPC_UART4->ICR &= (~UART_ICR_IRDAEN) & UART_ICR_BITMASK;
    }
}


/*********************************************************************//**
 * @brief       Configure Pulse divider for IrDA function on UART peripheral.
 * @param[in]   UARTx UART peripheral selected, should be LPC_UART4 (only)
 * @param[in]   PulseDiv Pulse Divider value from Peripheral clock,
 *              should be one of the following:
                - UART_IrDA_PULSEDIV2   : Pulse width = 2 * Tpclk
                - UART_IrDA_PULSEDIV4   : Pulse width = 4 * Tpclk
                - UART_IrDA_PULSEDIV8   : Pulse width = 8 * Tpclk
                - UART_IrDA_PULSEDIV16  : Pulse width = 16 * Tpclk
                - UART_IrDA_PULSEDIV32  : Pulse width = 32 * Tpclk
                - UART_IrDA_PULSEDIV64  : Pulse width = 64 * Tpclk
                - UART_IrDA_PULSEDIV128 : Pulse width = 128 * Tpclk
                - UART_IrDA_PULSEDIV256 : Pulse width = 256 * Tpclk

 * @return none
 **********************************************************************/
void UART_IrDAPulseDivConfig(UART_ID_Type UartID, UART_IrDA_PULSE_Type PulseDiv)
{
    uint32_t tmp, tmp1;

    if (UartID != UART_4)
        return;

    tmp1 = UART_ICR_PULSEDIV(PulseDiv);

    tmp = LPC_UART4->ICR & (~ UART_ICR_PULSEDIV(7));

    tmp |= tmp1 | UART_ICR_FIXPULSE_EN;

    LPC_UART4->ICR = tmp & UART_ICR_BITMASK;
}

/* UART1 FullModem function ---------------------------------------------*/

/*********************************************************************//**
 * @brief       Force pin DTR/RTS corresponding to given state (Full modem mode)
 * @param[in]   UARTx   LPC_UART1 (only)
 * @param[in]   Pin Pin that NewState will be applied to, should be:
 *              - UART1_MODEM_PIN_DTR: DTR pin.
 *              - UART1_MODEM_PIN_RTS: RTS pin.
 * @param[in]   NewState New State of DTR/RTS pin, should be:
 *              - INACTIVE: Force the pin to inactive signal.
                - ACTIVE: Force the pin to active signal.
 * @return none
 **********************************************************************/
void UART_FullModemForcePinState(UART_ID_Type UartID,
                                                    UART_MODEM_PIN_Type Pin,
                                                    UART1_SignalState NewState)
{
    uint8_t tmp = 0;
    if (UartID != UART_1)
        return;
    switch (Pin)
    {
        case UART1_MODEM_PIN_DTR:
            tmp = UART1_MCR_DTR_CTRL;
            break;

        case UART1_MODEM_PIN_RTS:
            tmp = UART1_MCR_RTS_CTRL;
            break;

        default:
            break;
    }

    if (NewState == ACTIVE)
    {
        LPC_UART1->MCR |= tmp;
    }
    else
    {
        LPC_UART1->MCR &= (~tmp) & UART1_MCR_BITMASK;
    }
}


/*********************************************************************//**
 * @brief       Configure Full Modem mode for UART peripheral
 * @param[in]   UARTx   LPC_UART1 (only)
 * @param[in]   Mode Full Modem mode, should be:
 *              - UART1_MODEM_MODE_LOOPBACK: Loop back mode.
 *              - UART1_MODEM_MODE_AUTO_RTS: Auto-RTS mode.
 *              - UART1_MODEM_MODE_AUTO_CTS: Auto-CTS mode.
 * @param[in]   NewState New State of this mode, should be:
 *              - ENABLE: Enable this mode.
                - DISABLE: Disable this mode.
 * @return none
 **********************************************************************/
void UART_FullModemConfigMode(UART_ID_Type UartID, UART_MODEM_MODE_Type Mode,
                                            FunctionalState NewState)
{
    uint8_t tmp;

    if(UartID != UART_1)
        return;
    
    switch(Mode)
    {
        case UART1_MODEM_MODE_LOOPBACK:
            tmp = UART1_MCR_LOOPB_EN;
            break;

        case UART1_MODEM_MODE_AUTO_RTS:
            tmp = UART1_MCR_AUTO_RTS_EN;
            break;

        case UART1_MODEM_MODE_AUTO_CTS:
            tmp = UART1_MCR_AUTO_CTS_EN;
            break;

        default:
            break;
    }

    if (NewState == ENABLE)
    {
        LPC_UART1->MCR |= tmp;
    }
    else
    {
        LPC_UART1->MCR &= (~tmp) & UART1_MCR_BITMASK;
    }
}


/*********************************************************************//**
 * @brief       Get current status of modem status register
 * @param[in]   UARTx   LPC_UART1 (only)
 * @return      Current value of modem status register
 * Note:    The return value of this function must be ANDed with each member
 *          UART_MODEM_STAT_type enumeration to determine current flag status
 *          corresponding to each modem flag status. Because some flags in
 *          modem status register will be cleared after reading, the next reading
 *          modem register could not be correct. So this function used to
 *          read modem status register in one time only, then the return value
 *          used to check all flags.
 **********************************************************************/
uint8_t UART_FullModemGetStatus(UART_ID_Type UartID)
{
    if(UartID != UART_1)
        return  0;
    
    return ((LPC_UART1->MSR) & UART1_MSR_BITMASK);
}


/* UART RS485 functions --------------------------------------------------------------*/
/*********************************************************************//**
 * @brief       Configure UART peripheral in RS485 mode according to the specified
*               parameters in the RS485ConfigStruct.
 * @param[in]   UARTx   LPC_UART0 ~LPC_UART4
 * @param[in]   RS485ConfigStruct Pointer to a UART1_RS485_CTRLCFG_Type structure
*                    that contains the configuration information for specified UART
*                    in RS485 mode.
 * @return      None
 **********************************************************************/
void UART_RS485Config(UART_ID_Type UartID, UART1_RS485_CTRLCFG_Type *RS485ConfigStruct)
{
    uint32_t tmp;
    __IO uint32_t *RS485DLY, *ADRMATCH, *RS485CTRL, *LCR;

    tmp = 0;
    if (UartID == UART_1)
    {
        RS485DLY = (__IO uint32_t *)&LPC_UART1->RS485DLY;
        ADRMATCH = (__IO uint32_t *)&LPC_UART1->ADRMATCH;
        LCR = (__IO uint32_t *)&LPC_UART1->LCR;
        RS485CTRL =  (__IO uint32_t *)&LPC_UART1->RS485CTRL;
    }
    else if (UartID == UART_4)
    {
        RS485DLY = (__IO uint32_t *)&LPC_UART4->RS485DLY;
        ADRMATCH = (__IO uint32_t *)&LPC_UART4->ADRMATCH;
        LCR = (__IO uint32_t *)&LPC_UART4->LCR;
        RS485CTRL =  (__IO uint32_t *)&LPC_UART4->RS485CTRL;
    }
    else
    {
        LPC_UART_TypeDef *UARTx = uart_get_pointer(UartID);
        RS485DLY = (__IO uint32_t *)&UARTx->RS485DLY;
        ADRMATCH = (__IO uint32_t *)&UARTx->ADRMATCH;
        LCR = (__IO uint32_t *)&UARTx->LCR;
         RS485CTRL =  (__IO uint32_t *)&UARTx->RS485CTRL;
    }
    // If Auto Direction Control is enabled -  This function is used in Master mode
    if (RS485ConfigStruct->AutoDirCtrl_State == ENABLE)
    {
        tmp |= UART_RS485CTRL_DCTRL_EN;

        // Set polar
        if (RS485ConfigStruct->DirCtrlPol_Level == SET)
        {
            tmp |= UART_RS485CTRL_OINV_1;
        }

        // Set pin according to. This condition is only with UART1. The others are used
        // OE pin as default for control the direction of RS485 buffer IC
        if ((RS485ConfigStruct->DirCtrlPin == UART_RS485_DIRCTRL_DTR) &&
             (UartID == UART_1))
        {
            tmp |= UART_RS485CTRL_SEL_DTR;
        }

        // Fill delay time
        *RS485DLY = RS485ConfigStruct->DelayValue & UART_RS485DLY_BITMASK;
    }
     
    // MultiDrop mode is enable
    if (RS485ConfigStruct->NormalMultiDropMode_State == ENABLE)
    {
        tmp |= UART_RS485CTRL_NMM_EN;
    }

    // Auto Address Detect function
    if (RS485ConfigStruct->AutoAddrDetect_State == ENABLE)
    {
        tmp |= UART_RS485CTRL_AADEN;

        // Fill Match Address
        *ADRMATCH = RS485ConfigStruct->MatchAddrValue & UART_RS485ADRMATCH_BITMASK;
    }

    // Receiver is disable
    if (RS485ConfigStruct->Rx_State == DISABLE)
    {
        tmp |= UART_RS485CTRL_RX_DIS;
    }
     
    // write back to RS485 control register
    *RS485CTRL = tmp & UART_RS485CTRL_BITMASK;

    // Enable Parity function and leave parity in stick '0' parity as default
    *LCR |= (UART_LCR_PARITY_F_0 | UART_LCR_PARITY_EN);
}

/*********************************************************************//**
 * @brief       Enable/Disable receiver in RS485 module in UART1
 * @param[in]   UARTx   LPC_UART1 (only)
 * @param[in]   NewState    New State of command, should be:
 *                          - ENABLE: Enable this function.
 *                          - DISABLE: Disable this function.
 * @return      None
 **********************************************************************/
void UART_RS485ReceiverCmd(UART_ID_Type UartID, FunctionalState NewState)
{
    __IO uint32_t *RS485CTRL;
    if (UartID == UART_1)
    {
        RS485CTRL = (__IO uint32_t *)&LPC_UART1->RS485DLY;
    }
    else if (UartID == UART_4)
    {
        RS485CTRL = (__IO uint32_t *)&LPC_UART4->RS485DLY;
    }
    else
    {
        LPC_UART_TypeDef *UARTx = uart_get_pointer(UartID);
        RS485CTRL = (__IO uint32_t *)&UARTx->RS485DLY;
    }
    if (NewState == ENABLE)
    {
        *RS485CTRL &= ~UART_RS485CTRL_RX_DIS;
    }
    else
    {
        *RS485CTRL |= UART_RS485CTRL_RX_DIS;
    }
}

/*********************************************************************//**
 * @brief       Send data on RS485 bus with specified parity stick value (9-bit mode).
 * @param[in]   UARTx   LPC_UART1 (only)
 * @param[in]   pDatFrm     Pointer to data frame.
 * @param[in]   size        Size of data.
 * @param[in]   ParityStick Parity Stick value, should be 0 or 1.
 * @return      None
 **********************************************************************/
uint32_t UART_RS485Send(UART_ID_Type UartID, uint8_t *pDatFrm,
                                            uint32_t size, uint8_t ParityStick)
{
    uint8_t tmp, save;
    uint32_t cnt;
    __IO uint32_t *LCR, *LSR;
    if (UartID == UART_1)
    {
        LCR = (__IO uint32_t *)&LPC_UART1->LCR;
        LSR = (__IO uint32_t *)&LPC_UART1->LSR;
    }
    else if (UartID == UART_4)
    {
        LCR = (__IO uint32_t *)&LPC_UART4->LCR;
        LSR = (__IO uint32_t *)&LPC_UART4->LSR;
    }
    else
    {
        LPC_UART_TypeDef *UARTx = uart_get_pointer(UartID);
        LCR = (__IO uint32_t *)&UARTx->LCR;
        LSR = (__IO uint32_t *)&UARTx->LSR;
    }

    if (ParityStick)
    {
        save = tmp = *LCR & UART_LCR_BITMASK;

        tmp &= ~(UART_LCR_PARITY_EVEN);

        *LCR = tmp;

        cnt = UART_Send(UartID, pDatFrm, size, BLOCKING);

        while (!(*LSR & UART_LSR_TEMT));

        *LCR = save;
    }
    else
    {
        cnt = UART_Send(UartID, pDatFrm, size, BLOCKING);

        while (!(*LSR & UART_LSR_TEMT));
    }

    return cnt;
}

/*********************************************************************//**
 * @brief       Send Slave address frames on RS485 bus.
 * @param[in]   UARTx   LPC_UART1 (only)
 * @param[in]   SlvAddr Slave Address.
 * @return      None
 **********************************************************************/
void UART_RS485SendSlvAddr(UART_ID_Type UartID, uint8_t SlvAddr)
{
    UART_RS485Send(UartID, &SlvAddr, 1, 1);
}

/*********************************************************************//**
 * @brief       Send Data frames on RS485 bus.
 * @param[in]   UARTx   LPC_UART1 (only)
 * @param[in]   pData Pointer to data to be sent.
 * @param[in]   size Size of data frame to be sent.
 * @return      None
 **********************************************************************/
uint32_t UART_RS485SendData(UART_ID_Type UartID, uint8_t *pData, uint32_t size)
{
    return (UART_RS485Send(UartID, pData, size, 0));
}

/**
 * @}
 */
#endif /*_UART*/
/**
 * @}
 */
/* --------------------------------- End Of File ------------------------------ */

