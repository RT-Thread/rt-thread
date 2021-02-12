/**
 * @file
 * @brief   This files defines the driver API including definitions, data types
 *          and function prototypes.
 */

/* ****************************************************************************
 * Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
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
 * $Date: 2019-10-07 11:05:30 -0500 (Mon, 07 Oct 2019) $
 * $Revision: 47429 $
 *
 *************************************************************************** */


#ifndef _UART_H_
#define _UART_H_

/***** Includes *****/
#include <stdint.h>
#include "uart_regs.h"
#include "mxc_sys.h"

/***** Definitions *****/

/**
 * @brief      Alternate clock rate. (7.3728MHz) */
#define UART_ALTERNATE_CLOCK_HZ 7372800
/**
 * @defgroup uart UART
 * @ingroup periphlibs
 * @{
 */
/**
 * @brief Parity settings type */
typedef enum {
    UART_PARITY_DISABLE = 0,                                /**< Parity disabled */
    UART_PARITY_EVEN_0  = (MXC_F_UART_CTRL_PARITY_EN |
                           MXC_S_UART_CTRL_PARITY_EVEN |
                           MXC_F_UART_CTRL_PARMD),          /**< Use for even parity 0 */
    UART_PARITY_EVEN_1  = (MXC_F_UART_CTRL_PARITY_EN |
                           MXC_S_UART_CTRL_PARITY_EVEN),    /**< Use for even parity 1 */
    UART_PARITY_EVEN    = UART_PARITY_EVEN_1,               /**< Conventional even parity */
    UART_PARITY_ODD_0   = (MXC_F_UART_CTRL_PARITY_EN |
                           MXC_S_UART_CTRL_PARITY_ODD |
                           MXC_F_UART_CTRL_PARMD),          /**< Use for odd parity 0 */
    UART_PARITY_ODD_1   = (MXC_F_UART_CTRL_PARITY_EN |
                           MXC_S_UART_CTRL_PARITY_ODD),     /**< Use for odd parity 1 */
    UART_PARITY_ODD     = UART_PARITY_ODD_1,                /**< Conventional odd parity */
    UART_PARITY_MARK_0  = (MXC_F_UART_CTRL_PARITY_EN |
                           MXC_S_UART_CTRL_PARITY_MARK |
                           MXC_F_UART_CTRL_PARMD),          /**< Use for mark parity 0 */
    UART_PARITY_MARK_1  = (MXC_F_UART_CTRL_PARITY_EN |
                           MXC_S_UART_CTRL_PARITY_MARK),    /**< Use for mark parity 1 */
    UART_PARITY_MARK    = UART_PARITY_MARK_1,               /**< Conventional mark parity */
    UART_PARITY_SPACE_0 = (MXC_F_UART_CTRL_PARITY_EN |
                           MXC_S_UART_CTRL_PARITY_SPACE |
                           MXC_F_UART_CTRL_PARMD),          /**< Use for space parity 0 */
    UART_PARITY_SPACE_1 = (MXC_F_UART_CTRL_PARITY_EN |
                           MXC_S_UART_CTRL_PARITY_SPACE),   /**< Use for space parity 1 */
    UART_PARITY_SPACE   = UART_PARITY_SPACE_1,              /**< Conventional space parity */
} uart_parity_t;

/**
 * @brief      Message size settings */
typedef enum {
    UART_DATA_SIZE_5_BITS = MXC_S_UART_CTRL_CHAR_SIZE_5,   /**< Data Size 5 Bits */
    UART_DATA_SIZE_6_BITS = MXC_S_UART_CTRL_CHAR_SIZE_6,   /**< Data Size 6 Bits */
    UART_DATA_SIZE_7_BITS = MXC_S_UART_CTRL_CHAR_SIZE_7,   /**< Data Size 7 Bits */
    UART_DATA_SIZE_8_BITS = MXC_S_UART_CTRL_CHAR_SIZE_8,   /**< Data Size 8 Bits */
} uart_size_t;

/**
 * @brief      Stop bit settings */
typedef enum {
    UART_STOP_1   = 0,                                      /**< UART Stop 1 clock cycle */
    UART_STOP_1P5 = MXC_F_UART_CTRL_STOPBITS,               /**< UART Stop 1.5 clock cycle */
    UART_STOP_2   = MXC_F_UART_CTRL_STOPBITS,               /**< UART Stop 2 clock cycle */
} uart_stop_t;

/**
 * @brief      Flow control */
typedef enum {
    UART_FLOW_CTRL_DIS = 0,                                 /**< RTS/CTS flow is disabled */
    UART_FLOW_CTRL_EN  = MXC_F_UART_CTRL_FLOW_CTRL,         /**< RTS/CTS flow is enabled */
} uart_flow_ctrl_t;

/**
 * @brief      Flow control Polarity */
typedef enum {
    UART_FLOW_POL_DIS = 0,                                  /**< RTS/CTS asserted is low */
    UART_FLOW_POL_EN  = MXC_F_UART_CTRL_FLOW_POL,           /**< RTS/CTS asserted is high */
} uart_flow_pol_t;

#if (TARGET != 32660)
/**
 * @brief      Clock Source Select */
typedef enum {
    UART_CLKSEL_SYSTEM = 0,                                 /**< Peripheral clock will be used as the bit rate clock */
    UART_CLKSEL_ALTERNATE = MXC_F_UART_CTRL_CLKSEL,         /**< Use the device's alternate UART bit rate clock. */
} uart_clksel_t;
#endif

/**
 * @brief      UART configuration type. */
typedef struct {
    uart_parity_t parity;  /**        Configure parity checking */
    uart_size_t size;      /**        Configure character size */
    uart_stop_t stop;      /**        Configure the number of stop bits to use */
    uart_flow_ctrl_t flow; /**        Configure hardware flow control */
    uart_flow_pol_t pol;   /**        Configure hardware flow control */
    uint32_t baud;         /**        Configure baud rate */
#if (TARGET != 32660)
    uart_clksel_t clksel;  /**        Configure hardware clock source */
#endif
} uart_cfg_t;

/**
 * @brief      Non-blocking UART transaction request. */
typedef struct uart_req uart_req_t;
struct uart_req {
    uint8_t *data;    /**       Data buffer for characters */
    int len;          /**       Length of characters in data to send or receive */
    int num;          /**       Number of characters actually sent or received */

    /**
     * @brief   Callback for asynchronous request.
     *
     * @param   uart_req_t*  Pointer to the transaction request.
     * @param   int          Error code.
     *
     */
    void(*callback)(uart_req_t*, int);
};


/***** Functions Prototypes *****/


/**
 * @brief   Initialize and enable UART module.
 * @param   uart        Pointer to the UART registers.
 * @param   cfg         Pointer to UART configuration.
 * @param   sys_cfg     Pointer to system configuration object
 * @returns #E_NO_ERROR UART initialized successfully, @ref MXC_Error_Codes "error" if
 *             unsuccessful.
 */
int UART_Init(mxc_uart_regs_t *uart, const uart_cfg_t *cfg, const sys_cfg_uart_t* sys_cfg);

/**
 * @brief   Shutdown UART module.
 * @param   uart    Pointer to the UART registers.
 * @returns #E_NO_ERROR UART shutdown successfully, @ref MXC_Error_Codes "error" if
 *             unsuccessful.
 */
int UART_Shutdown(mxc_uart_regs_t *uart);

/**
 * @brief      UART interrupt handler.
 * @details    This function should be called by the application from the
 *             interrupt handler if UART interrupts are enabled. Alternately,
 *             this function can be periodically called by the application if
 *             UART interrupts are disabled. It is only necessary to call this
 *             when using asynchronous functions.
 *
 * @param      uart  Pointer to the UART registers.
 */
void UART_Handler(mxc_uart_regs_t *uart);

/**
 * @brief      Read UART data, <em>blocking</em> until transaction is complete.
 *
 * @param      uart  Pointer to the UART registers.
 * @param      data  Pointer to buffer to save the data read.
 * @param      len   Number of bytes to read.
 * @param      num   Pointer to store the number of bytes actually read, pass NULL if not needed.
 *
 * @return     Number of bytes read, @ref MXC_Error_Codes "error" if unsuccessful.
 */
int UART_Read(mxc_uart_regs_t *uart, uint8_t *data, int len, int *num);

/**
 * @brief      Write UART data. This function blocks until the write transaction
 *             is complete.
 * @param      uart  Pointer to the UART registers.
 * @param      data  Pointer to buffer for write data.
 * @param      len   Number of bytes to write.
 * @note       This function will return once data has been put into FIFO, not necessarily
 *             transmitted.
 * @return     Number of bytes written if successful, @ref MXC_Error_Codes "error" if unsuccessful.
 */
int UART_Write(mxc_uart_regs_t *uart, const uint8_t *data, int len);

/**
 * @brief      Asynchronously read UART data.
 *
 * @param      uart  Pointer to the UART registers.
 * @param      req   Pointer to request for a UART transaction, see #uart_req.
 * @note       Request struct must remain allocated until callback function specified in 'req' is called.
 *
 * @return     #E_NO_ERROR Asynchronous read successfully started, @ref MXC_Error_Codes "error" if unsuccessful.
 */
int UART_ReadAsync(mxc_uart_regs_t *uart, uart_req_t *req);

/**
 * @brief      Asynchronously write/transmit UART data.
 *
 * @param      uart  Pointer to the UART registers.
 * @param      req   Request for a UART transaction, see #uart_req.
 * @note       Request struct must remain allocated until callback function specified in 'req' is called.
 *
 * @return     #E_NO_ERROR Asynchronous write successfully started, @ref
 *             MXC_Error_Codes "error" if unsuccessful.
 */
int UART_WriteAsync(mxc_uart_regs_t *uart, uart_req_t *req);

/**
 * @brief      Read a single byte from the UART.
 * @note       This function will block until a character is available.
 *
 * @param      uart  Pointer to the UART registers.
 * @return     The byte read.
 */
uint8_t UART_ReadByte(mxc_uart_regs_t *uart);

/**
 * @brief      Write one byte at a time to the UART.
 * @note       This function will block until the character has been placed in the transmit FIFO.
 *             It may return before the character is actually transmitted.
 *
 * @param      uart  Pointer to the UART registers.
 * @param      data  The byte to write.
 */
void UART_WriteByte(mxc_uart_regs_t *uart, uint8_t data);

/**
 * @brief      Check to see if the UART is busy.
 *
 * @param      uart  Pointer to the UART registers.
 *
 * @return     #E_NO_ERROR if the UART is idle, #E_BUSY if the UART is in use.
 */
int UART_Busy(mxc_uart_regs_t *uart);

/**
 * @brief      Prepare the UART for entry into a Low-Power mode (DEEPSLEEP/BACKUP).
 * @details    Checks for any ongoing transactions. Disables interrupts if the
 *             UART is idle.
 *
 * @param      uart         Pointer to the UART registers.
 * @return     #E_NO_ERROR  UART is ready to enter Low-Power modes (DEEPSLEEP/BACKUP).
 * @return     #E_BUSY      UART is active and busy and not ready to enter a
 *                          Low-Power mode (DEEPSLEEP/BACKUP).
 *
 */
int UART_PrepForSleep(mxc_uart_regs_t *uart);

/**
 * @brief      Abort asynchronous request.
 *
 * @param      req   Pointer to the request to abort. See #uart_req.
 *
 * @return     #E_NO_ERROR if the asynchronous request aborted successfully started, @ref
 *             MXC_Error_Codes "error" if unsuccessful.
 */
int UART_AbortAsync(uart_req_t *req);

/**
 * @brief      Returns the number of bytes still pending transmission in the UART TX FIFO.
 *
 * @param      uart  Pointer to the UART registers.
 *
 * @return     Number of unused bytes in the TX FIFO.
 */
unsigned UART_NumWriteAvail(mxc_uart_regs_t *uart);

/**
 * @brief      Returns the number of bytes available to be read from the RX FIFO.
 *
 * @param      uart  Pointer to the UART registers.
 *
 * @return     The number of bytes available to read in the RX FIFO.
 */
unsigned UART_NumReadAvail(mxc_uart_regs_t *uart);

/**
 * @brief      Clears the specified interrupt flags.
 *
 * @param      uart  Pointer to the UART registers.
 * @param      mask  Mask of the UART interrupts to clear, see
 *                   @ref UART_INT_FL Register.
 */
void UART_ClearFlags(mxc_uart_regs_t *uart, uint32_t mask);

/**
 * @brief      Get the UART interrupt flags.
 *
 * @param      uart  Pointer to the UART registers.
 *
 * @return     Mask of active flags.
 */
unsigned UART_GetFlags(mxc_uart_regs_t *uart);

/**
 * @brief      Enables the UART.
 * @note       This function does not change the existing UART configuration.
 *
 * @param      uart  Pointer to the UART registers.
 */
void UART_Enable(mxc_uart_regs_t *uart);

/**
 * @brief      Disables the UART.
 * @note       This function does not change the existing UART configuration.
 *
 * @param      uart  Pointer to the UART registers.
 */
void UART_Disable(mxc_uart_regs_t *uart);

/**
 * @brief      Drains/empties and data in the RX FIFO, discarding any bytes not yet consumed.
 *
 * @param      uart  Pointer to the UART registers.
 */
void UART_DrainRX(mxc_uart_regs_t *uart);

/**
 * @brief      Drains/empties any data in the TX FIFO, discarding any bytes not yet transmitted.
 *
 * @param      uart  Pointer to the UART registers.
 */
void UART_DrainTX(mxc_uart_regs_t *uart);

/**@} end of group uart */

#endif /* _UART_H_ */
