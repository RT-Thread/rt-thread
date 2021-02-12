/* ****************************************************************************
 * Copyright (C) 2014-2018 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2020-09-08 13:28:39 -0500 (Tue, 08 Sep 2020) $
 * $Revision: 55611 $
 *
 *************************************************************************** */

/* **** Includes **** */
#include <stdint.h>
#include <string.h>
#include "mxc_config.h"
#include "mxc_assert.h"
#include "uart_regs.h"
#include "uart.h"
#include "mxc_lock.h"
#include "mxc_sys.h"

/* **** Definitions **** */

#define UART_ER_IF (MXC_F_UART_INT_FL_RX_FRAME_ERROR | \
                    MXC_F_UART_INT_FL_RX_PARITY_ERROR | \
                    MXC_F_UART_INT_FL_RX_OVERRUN)

#define UART_ER_IE (MXC_F_UART_INT_EN_RX_FRAME_ERROR | \
                    MXC_F_UART_INT_EN_RX_PARITY_ERROR | \
                    MXC_F_UART_INT_EN_RX_OVERRUN )

#define UART_RX_IF (MXC_F_UART_INT_FL_RX_FIFO_THRESH)

#define UART_RX_IE (MXC_F_UART_INT_EN_RX_FIFO_THRESH)

#define UART_TX_IF (MXC_F_UART_INT_FL_TX_FIFO_ALMOST_EMPTY | \
                    MXC_F_UART_INT_FL_TX_FIFO_THRESH)

#define UART_TX_IE (MXC_F_UART_INT_EN_TX_FIFO_ALMOST_EMPTY | \
                    MXC_F_UART_INT_EN_TX_FIFO_THRESH)

#if (TARGET == 32660) || (TARGET == 32665)
#define MAX_FACTOR 3
#else
#define MAX_FACTOR 7
#endif

/* **** File Scope Data **** */

// Saves the state of the non-blocking read requests.
static uart_req_t *rx_states[MXC_UART_INSTANCES];

// Saves the state of the non-blocking write requests.
static uart_req_t *tx_states[MXC_UART_INSTANCES];


/* **** Functions **** */
static void UART_WriteHandler(mxc_uart_regs_t *uart, uart_req_t *req, int uart_num);
static void UART_ReadHandler(mxc_uart_regs_t *uart, uart_req_t *req, int uart_num,
                             uint32_t flags);
static uint32_t uart_error_check(mxc_uart_regs_t *uart);
static void uart_error_clear(mxc_uart_regs_t *uart);

/* ************************************************************************* */
uint32_t uart_error_check(mxc_uart_regs_t *uart)
{
    return (uart->int_fl & UART_ER_IF);
}

/* ************************************************************************* */
void uart_error_clear(mxc_uart_regs_t *uart)
{
    UART_ClearFlags(uart,UART_ER_IF);
}

/* ************************************************************************* */
int UART_Init(mxc_uart_regs_t *uart, const uart_cfg_t *cfg, const sys_cfg_uart_t* sys_cfg)
{
    int err;
    int uart_num;
    
    uint32_t baud0 = 0, baud1 = 0,div;
    int32_t factor = -1;
    
    // Get the state array index
    uart_num = MXC_UART_GET_IDX(uart);
    if (uart_num == -1) {
        return E_BAD_PARAM;
    }
    
    if ((err = SYS_UART_Init(uart, sys_cfg)) != E_NO_ERROR) {
        return err;
    }
    
    // Initialize state pointers
    rx_states[uart_num] = NULL;
    tx_states[uart_num] = NULL;
    
    // Drain FIFOs, enable UART, and set configuration
    uart->ctrl = (MXC_F_UART_CTRL_ENABLE | cfg->parity | cfg->size | cfg->stop | cfg->flow | cfg->pol);
    
    // Set the baud rate
    // Calculate divisor
#if (TARGET != 32660)
    uart->ctrl |=  cfg->clksel;
    if (cfg->clksel == UART_CLKSEL_ALTERNATE) {
        div = UART_ALTERNATE_CLOCK_HZ / ((cfg->baud)); 
    } else {
        div = PeripheralClock / ((cfg->baud));
    }
#else
    div = PeripheralClock / ((cfg->baud));
#endif
    // Search for integer and fractional baud rate registers based on divisor
    do {
	factor += 1;
	baud0 = div >> (7-factor); // divide by 128,64,32,16 to extract integer part
	baud1 = ((div << factor) - (baud0 << 7)); //subtract factor corrected div - integer parts
    } while ((baud0 == 0) && (factor < MAX_FACTOR));

    uart->baud0 = ((factor << MXC_F_UART_BAUD0_FACTOR_POS) | baud0);
#if (TARGET == 32660) || (TARGET == 32665) || (TARGET == 32650)
    /* Erratum:
     *   Hardware bug causes exact baud rates to generate framing error. Slightly mis-adjust timing
     *   to help avoid this bug.
     */
    if (baud1 > 3) {
	uart->baud1 = baud1 - 3;
    } else {
	uart->baud1 = baud1 + 3;
    }
#else
    uart->baud1 = baud1;
#endif

    // Clear pending requests
    rx_states[uart_num] = NULL;
    tx_states[uart_num] = NULL;

    return E_NO_ERROR;
}

/* ************************************************************************* */
int UART_Shutdown(mxc_uart_regs_t *uart)
{
    int uart_num;
    uart_req_t *temp_req;

    // Get the state array index
    uart_num = MXC_UART_GET_IDX(uart);
    if (uart_num < 0) {
        return E_BAD_PARAM;
    }

    // Disable interrupts
    uart->int_en = 0;

    // Flush RX and TX FIFOS
    uart->ctrl |= (MXC_F_UART_CTRL_TX_FLUSH | MXC_F_UART_CTRL_RX_FLUSH);

    // Call all of the pending callbacks for this UART
    if(rx_states[uart_num] != NULL) {

        // Save the request
        temp_req = rx_states[uart_num];

        // Unlock this UART to read
        mxc_free_lock((uint32_t*)&rx_states[uart_num]);

        // Callback if not NULL
        if (temp_req->callback != NULL) {
            temp_req->callback(temp_req, E_SHUTDOWN);
        }
    }

    if (tx_states[uart_num] != NULL) {

        // Save the request
        temp_req = tx_states[uart_num];

        // Unlock this UART to write
        mxc_free_lock((uint32_t*)&tx_states[uart_num]);

        // Callback if not NULL
        if (temp_req->callback != NULL) {
            temp_req->callback(temp_req, E_SHUTDOWN);
        }
    }
    // Wait for not busy
    while (uart->status & (MXC_F_UART_STATUS_TX_BUSY | MXC_F_UART_STATUS_RX_BUSY)) {
        
    }

    // Shutdown the UART
    uart->ctrl = 0;
    
    // Shutdown any system level setup
    SYS_UART_Shutdown(uart);

    // Clear pending requests
    rx_states[uart_num] = NULL;
    tx_states[uart_num] = NULL;
    
    return E_NO_ERROR;
}

/* ************************************************************************* */
void UART_Handler(mxc_uart_regs_t *uart)
{
    int uart_num; // Holds the current index of rx_states or tx_states
    uint32_t intst;

    // Get the state array index
    uart_num = MXC_UART_GET_IDX(uart);
    if (uart_num == -1) {
        return;
    }

    // Read and clear interrupts
    intst = uart->int_fl;
    uart->int_fl = intst;

    // Read interrupt
    if (intst & (UART_RX_IF | UART_ER_IF)) {
        UART_ReadHandler(uart, rx_states[uart_num], uart_num, intst);
    }

    // Write Interrupt
    if (intst & (UART_TX_IF | UART_ER_IF)) {
        UART_WriteHandler(uart, tx_states[uart_num], uart_num);
    }
}

/* ************************************************************************* */
static void UART_WriteHandler(mxc_uart_regs_t *uart, uart_req_t *req, int uart_num)
{
    int remain, avail;
    req = tx_states[uart_num];

    if (req == NULL) {
        // Nothing to do
        uart->int_en &= ~MXC_F_UART_INT_EN_TX_FIFO_ALMOST_EMPTY; // disable interrupt
        return;
    }

    // Refill the TX FIFO
    avail = UART_NumWriteAvail(uart);
    remain = req->len - req->num;

    while (avail && remain) {
        uart->fifo = req->data[req->num++];
        remain--;
        avail--;
    }

    // See if we've sent all of the characters
    if (req->len == req->num) {
        // Disable interrupts
        uart->int_en &= ~MXC_F_UART_INT_EN_TX_FIFO_ALMOST_EMPTY;

        // Deinit state before callback in case another is requested
        tx_states[uart_num] = NULL;
        mxc_free_lock((uint32_t*)&tx_states[uart_num]);

        // Callback when we've written all the characters
        if (req->callback != NULL) {
            req->callback(req, E_NO_ERROR);
        }
    }
    // Enable the interrupts
    uart->int_en |= UART_TX_IE | UART_ER_IE;

}

/* ************************************************************************* */
static void UART_ReadHandler(mxc_uart_regs_t *uart, uart_req_t *req, int uart_num,
                             uint32_t flags)
{
    int remain, avail;

    if (req == NULL) {
        // Nothing to do
        uart->int_en &= ~(UART_RX_IE | UART_ER_IE); // disable interrupts
        return;
    }
    // Save the data in the FIFO while we still need data
    avail = UART_NumReadAvail(uart);
    remain = req->len - req->num;
    while (avail && remain) {
        req->data[req->num++] = uart->fifo;
        remain--;
        avail--;
    }
    // Check for errors
    if (flags & MXC_F_UART_INT_FL_RX_OVERRUN) {

        // Unlock this UART to read
        mxc_free_lock((uint32_t*)&rx_states[uart_num]);

        if (req->callback != NULL) {
            req->callback(req, E_OVERFLOW);
        }

        return;
    }
    if (flags & (MXC_F_UART_INT_FL_RX_FRAME_ERROR |
                MXC_F_UART_INT_FL_RX_PARITY_ERROR)) {

        // Unlock this UART to read
        mxc_free_lock((uint32_t*)&rx_states[uart_num]);

        if (req->callback != NULL)         {
            req->callback(req, E_COMM_ERR);
        }

        return;
    }
    // Check to see if we've received all of the characters.
    if (req->num == req->len) {
        // Disable interrupts
        uart->int_en &= ~(UART_RX_IE | UART_ER_IE);

        // Deinit state before callback in case another is requested
        rx_states[uart_num] = NULL;

        // Call the callback function
        if (req->callback != NULL) {
            req->callback(req, E_NO_ERROR);
        }

        return;
    } else if (req->num > (req->len - MXC_UART_FIFO_DEPTH)) {
        // Set RX threshold less than FIFO_DEPTH characters if needed
        uart->thresh_ctrl = ((req->len - req->num)<<
                       MXC_F_UART_THRESH_CTRL_RX_FIFO_THRESH_POS);
    } else {
        uart->thresh_ctrl = MXC_UART_FIFO_DEPTH<<
                      MXC_F_UART_THRESH_CTRL_RX_FIFO_THRESH_POS;
    }
}

/* ************************************************************************* */
int UART_Read(mxc_uart_regs_t *uart, uint8_t *data, int len, int *num)
{
    int uart_num; // Holds the current index of rx_states
    int char_read = 0; // Holds the number of characters successfully read
    int error_code =0; // Holds the error to return while reading

    // Get the state array index
    uart_num = MXC_UART_GET_IDX(uart);
    if (uart_num < 0) {
        return E_BAD_PARAM;
    }

    // Check to make sure baud rate has been set
    if (uart->baud0 == 0) {
        return E_UNINITIALIZED;
    }

    // Check data pointer
    if (data == NULL) {
        return E_BAD_PARAM;
    }

    // Check if there is already a request in progress
    if (rx_states[uart_num] != NULL) {
        return E_BUSY;
    }

    // Lock this UART from reading
    while (mxc_get_lock((uint32_t*)&rx_states[uart_num], 1) != E_NO_ERROR) {
        
    }

    // Get bytes FIFO
    while (char_read < len) {
        // Wait for RXFIFO to not be empty
        while (uart->status & MXC_F_UART_STATUS_RX_EMPTY) {
            // Check for error
            if (uart_error_check(uart) != E_NO_ERROR) {
                if (uart->int_fl & MXC_F_UART_INT_FL_RX_OVERRUN) {
                    error_code = E_OVERFLOW;
                } else {
                    error_code = E_COMM_ERR;
                }

                uart_error_clear(uart);
                mxc_free_lock((uint32_t*)&rx_states[uart_num]);
                return error_code;
            }
        }
        data[char_read] = uart->fifo;
        char_read++;
    }
    if (num != NULL) {
        *num = char_read;
    }
    // Unlock this UART to read
    mxc_free_lock((uint32_t*)&rx_states[uart_num]);

    return char_read;
}

/* ************************************************************************* */
uint8_t UART_ReadByte(mxc_uart_regs_t *uart)
{

    while (uart->status & MXC_F_UART_STATUS_RX_EMPTY) {}

    return uart->fifo;
}

/* ************************************************************************* */
int UART_Write(mxc_uart_regs_t *uart, const uint8_t *data, int len)
{
    int uart_num; // Holds the current index of tx_states
    int char_written = 0;  // Holds the number of characters successfully written

    // Get the state array index
    uart_num = MXC_UART_GET_IDX(uart);
    if (uart_num < 0) {
        return E_BAD_PARAM;
    }

    // Check to make sure baud rate has been set
    if (uart->baud0 == 0) {
        return E_UNINITIALIZED;
    }

    // Check data pointer
    if (data == NULL) {
        return E_BAD_PARAM;
    }

    // Check if there is already a request in progress
    if (tx_states[uart_num] != NULL) {
        return E_BUSY;
    }

    // Lock this UART from writing
    while (mxc_get_lock((uint32_t*)&tx_states[uart_num], 1) != E_NO_ERROR) {
        
    }

    // Clear errors
    uart_error_clear(uart);

    // Put bytes into FIFO
    while (char_written < len) {
        UART_WriteByte(uart,data[char_written]);
        char_written++;
    }

    // Unlock this UART to write
    mxc_free_lock((uint32_t*)&tx_states[uart_num]);

    return char_written;
}

/* ************************************************************************* */
void UART_WriteByte(mxc_uart_regs_t *uart, uint8_t data)
{

    // Wait for TXFIFO if full
    while (uart->status & MXC_F_UART_STATUS_TX_FULL) {
        
    }

    // Put data into fifo
    uart->fifo = data;
}

/* ************************************************************************* */
int UART_ReadAsync(mxc_uart_regs_t *uart, uart_req_t *req)
{
    int uart_num; // Holds the current index of tx_states
    uint32_t flags;  // Holds the Interrupt flags

    // Check data pointer
    if (req == NULL) {
        return E_BAD_PARAM;
    }

    // Get the state array index
    uart_num = MXC_UART_GET_IDX(uart);
    if (uart_num < 0) {
        return E_BAD_PARAM;
    }

    if (req->data == NULL) {
        return E_NULL_PTR;
    }
    // Check to make sure baud rate has been set
    if (uart->baud0 == 0) {
        return E_UNINITIALIZED;
    }

    // Check if there is already a request in progress
    if (rx_states[uart_num] != NULL) {
        return E_BUSY;
    }

    if (!(req->len > 0)) {
        return E_NO_ERROR;
    }

    // Attempt to register this write request
    if (mxc_get_lock((uint32_t*)&rx_states[uart_num], (uint32_t)req) != E_NO_ERROR) {
        return E_BUSY;
    }

    // Clear the data counter
    req->num = 0;

    // Clear Interrupt Flags
    flags = uart->int_fl;
    uart->int_fl = flags;
    UART_ReadHandler(uart,req,uart_num,flags);

    // Enable the interrupts
    uart->int_en |= UART_RX_IE | UART_ER_IE;

    return E_NO_ERROR;
}

/* ************************************************************************* */
int UART_WriteAsync(mxc_uart_regs_t *uart, uart_req_t *req)
{
    int uart_num;  // Holds the current index of tx_states

    // Check data pointer
    if (req == NULL) {
        return E_BAD_PARAM;
    }

    // Get the state array index
    uart_num = MXC_UART_GET_IDX(uart);
    if (uart_num < 0) {
        return E_BAD_PARAM;
    }

    if (req->data == NULL) {
        return E_NULL_PTR;
    }
    // Check to make sure baud rate has been set
    if (uart->baud0 == 0) {
        return E_UNINITIALIZED;
    }

    // Check if there is already a request in progress
    if (tx_states[uart_num] != NULL) {
        return E_BUSY;
    }
    if (!(req->len > 0)) {
        return E_NO_ERROR;
    }
    // Attempt to register this write request
    if (mxc_get_lock((uint32_t*)&tx_states[uart_num], (uint32_t)req) != E_NO_ERROR) {
        return E_BUSY;
    }

    // Clear the data counter
    req->num = 0;
    UART_WriteHandler(uart, req, uart_num);

    return E_NO_ERROR;
}

/* ************************************************************************* */
int UART_Busy(mxc_uart_regs_t *uart)
{
    int uart_num = MXC_UART_GET_IDX(uart);  // Holds the current index of tx_states
    MXC_ASSERT(uart_num >= 0);
    if ((uart->status & MXC_F_UART_STATUS_TX_BUSY) || (uart->status & MXC_F_UART_STATUS_RX_BUSY)) {
        return E_BUSY;
    }
    // Check to see if there are any ongoing transactions and the UART has room in its FIFO
    if ((tx_states[uart_num] == NULL) &&
            !(uart->status & MXC_F_UART_STATUS_TX_FULL)) {

        return E_NO_ERROR;
    }

    return E_BUSY;
}

/* ************************************************************************* */
int UART_PrepForSleep(mxc_uart_regs_t *uart)
{
    if (UART_Busy(uart) != E_NO_ERROR) {
        return E_BUSY;
    }

    // Leave read interrupts enabled, if already enabled
    uart->int_en &= (UART_RX_IE | UART_ER_IE);

    return E_NO_ERROR;
}

/* ************************************************************************* */
int UART_AbortAsync(uart_req_t *req)
{
    int uart_num;

    // Figure out if this was a read or write request, find the request, set to NULL
    for (uart_num = 0; uart_num < MXC_UART_INSTANCES; uart_num++) {
        if (req == rx_states[uart_num]) {

            // Disable read interrupts, clear flags.
            MXC_UART_GET_UART(uart_num)->int_en &= ~(UART_RX_IE | UART_ER_IE);
            MXC_UART_GET_UART(uart_num)->int_fl = (UART_RX_IF | UART_ER_IF);

            // Unlock this UART to read
            mxc_free_lock((uint32_t*)&rx_states[uart_num]);

            // Callback if not NULL
            if (req->callback != NULL) {
                req->callback(req, E_ABORT);
            }

            return E_NO_ERROR;
        }

        if (req == tx_states[uart_num]) {

            // Disable write interrupts, clear flags.
            MXC_UART_GET_UART(uart_num)->int_en &= ~(UART_TX_IE | UART_ER_IE);
            MXC_UART_GET_UART(uart_num)->int_fl = (UART_TX_IF | UART_ER_IF);

            // Unlock this UART to write
            mxc_free_lock((uint32_t*)&tx_states[uart_num]);

            // Callback if not NULL
            if (req->callback != NULL) {
                req->callback(req, E_ABORT);
            }

            return E_NO_ERROR;
        }
    }

    return E_BAD_PARAM;
}

/* ************************************************************************* */
unsigned UART_NumWriteAvail(mxc_uart_regs_t *uart)
{
    return MXC_UART_FIFO_DEPTH - ((uart->status & MXC_F_UART_STATUS_TX_FIFO_CNT) >>
                                  MXC_F_UART_STATUS_TX_FIFO_CNT_POS);
}

/* ************************************************************************* */
unsigned UART_NumReadAvail(mxc_uart_regs_t *uart)
{
    return ((uart->status & MXC_F_UART_STATUS_RX_FIFO_CNT) >>
            MXC_F_UART_STATUS_RX_FIFO_CNT_POS);
}

/* ************************************************************************* */
unsigned UART_GetFlags(mxc_uart_regs_t *uart)
{
    return (uart->int_fl);
}

/* ************************************************************************* */
void UART_ClearFlags(mxc_uart_regs_t *uart, uint32_t mask)
{
    uart->int_fl = mask;
}

/* ************************************************************************* */
void UART_Enable(mxc_uart_regs_t *uart)
{
    uart->ctrl |= MXC_F_UART_CTRL_ENABLE;
}

/* ************************************************************************* */
void UART_Disable(mxc_uart_regs_t *uart)
{
    uart->ctrl &= ~MXC_F_UART_CTRL_ENABLE;
}

/* ************************************************************************* */
void UART_DrainRX(mxc_uart_regs_t *uart)
{
    uart->ctrl |= MXC_F_UART_CTRL_RX_FLUSH;
}

/* ************************************************************************* */
void UART_DrainTX(mxc_uart_regs_t *uart)
{
    uart->ctrl |= MXC_F_UART_CTRL_TX_FLUSH;
}
