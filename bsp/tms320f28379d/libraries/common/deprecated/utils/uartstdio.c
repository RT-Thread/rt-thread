//###########################################################################
//
// FILE:   uartstdio.c
//
// TITLE:  Utility driver to provide simple UART console functions.
//
//###########################################################################
// $TI Release: F2837xD Support Library v3.05.00.00 $
// $Release Date: Tue Jun 26 03:15:23 CDT 2018 $
// $Copyright:
// Copyright (C) 2013-2018 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

//
// Included Files
//
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_uart.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

//*****************************************************************************
//
//! \addtogroup uartstdio_api
//! @{
//
//*****************************************************************************

//
// If buffered mode is defined, set aside RX and TX buffers and read/write
// pointers to control them.
//
#ifdef UART_BUFFERED

//
// This global controls whether or not we are echoing characters back to the
// transmitter.  By default, echo is enabled but if using this module as a
// convenient method of implementing a buffered serial interface over which
// you will be running an application protocol, you are likely to want to
// disable echo by calling UARTEchoSet(false).
//
static bool g_bDisableEcho;

//
// Output ring buffer.  Buffer is full if g_ui32UARTTxReadIndex is one ahead of
// g_ui32UARTTxWriteIndex.  Buffer is empty if the two indices are the same.
//
static unsigned char g_pcUARTTxBuffer[UART_TX_BUFFER_SIZE];
static volatile uint32_t g_ui32UARTTxWriteIndex = 0;
static volatile uint32_t g_ui32UARTTxReadIndex = 0;

//
// Input ring buffer.  Buffer is full if g_ui32UARTTxReadIndex is one ahead of
// g_ui32UARTTxWriteIndex.  Buffer is empty if the two indices are the same.
//
static unsigned char g_pcUARTRxBuffer[UART_RX_BUFFER_SIZE];
static volatile uint32_t g_ui32UARTRxWriteIndex = 0;
static volatile uint32_t g_ui32UARTRxReadIndex = 0;

//
// Macros to determine number of free and used bytes in the transmit buffer.
//
#define TX_BUFFER_USED          (GetBufferCount(&g_ui32UARTTxReadIndex,  \
                                                &g_ui32UARTTxWriteIndex, \
                                                UART_TX_BUFFER_SIZE))
#define TX_BUFFER_FREE          (UART_TX_BUFFER_SIZE - TX_BUFFER_USED)
#define TX_BUFFER_EMPTY         (IsBufferEmpty(&g_ui32UARTTxReadIndex,   \
                                               &g_ui32UARTTxWriteIndex))
#define TX_BUFFER_FULL          (IsBufferFull(&g_ui32UARTTxReadIndex,  \
                                              &g_ui32UARTTxWriteIndex, \
                                              UART_TX_BUFFER_SIZE))
#define ADVANCE_TX_BUFFER_INDEX(Index) \
                                (Index) = ((Index) + 1) % UART_TX_BUFFER_SIZE

//
// Macros to determine number of free and used bytes in the receive buffer.
//
#define RX_BUFFER_USED          (GetBufferCount(&g_ui32UARTRxReadIndex,  \
                                                &g_ui32UARTRxWriteIndex, \
                                                UART_RX_BUFFER_SIZE))
#define RX_BUFFER_FREE          (UART_RX_BUFFER_SIZE - RX_BUFFER_USED)
#define RX_BUFFER_EMPTY         (IsBufferEmpty(&g_ui32UARTRxReadIndex,   \
                                               &g_ui32UARTRxWriteIndex))
#define RX_BUFFER_FULL          (IsBufferFull(&g_ui32UARTRxReadIndex,  \
                                              &g_ui32UARTRxWriteIndex, \
                                              UART_RX_BUFFER_SIZE))
#define ADVANCE_RX_BUFFER_INDEX(Index) \
                                (Index) = ((Index) + 1) % UART_RX_BUFFER_SIZE
#endif

//
// The base address of the chosen UART.
//
static uint32_t g_ui32Base = 0;

//
// A mapping from an integer between 0 and 15 to its ASCII character
// equivalent.
//
static const char * const g_pcHex = "0123456789abcdef";

//
// The list of possible base addresses for the console UART.
//
static const uint32_t g_ui32UARTBase[4] =
{
    UARTA_BASE, UARTB_BASE, UARTC_BASE, UARTD_BASE
};

#ifdef UART_BUFFERED
//
// The list of possible interrupts for the console UART.
//
static const uint32_t g_ui32UARTInt[3] =
{
    INT_UART0, INT_UART1, INT_UART2
};

//
// The port number in use.
//
static uint32_t g_ui32PortNum;
#endif

//
// The list of UART peripherals.
//
static const uint32_t g_ui32UARTPeriph[3] =
{
    SYSCTL_PERIPH_SCI1, SYSCTL_PERIPH_SCI2, SYSCTL_PERIPH_SCI3
};

//*****************************************************************************
//
//! Determines whether the ring buffer whose pointers and size are provided
//! is full or not.
//!
//! \param pui32Read points to the read index for the buffer.
//! \param pui32Write points to the write index for the buffer.
//! \param ui32Size is the size of the buffer in bytes.
//!
//! This function is used to determine whether or not a given ring buffer is
//! full.  The structure of the code is specifically to ensure that we do not
//! see warnings from the compiler related to the order of volatile accesses
//! being undefined.
//!
//! \return Returns \b true if the buffer is full or \b false otherwise.
//
//*****************************************************************************
#ifdef UART_BUFFERED
static bool
IsBufferFull(volatile uint32_t *pui32Read,
             volatile uint32_t *pui32Write, uint32_t ui32Size)
{
    uint32_t ui32Write;
    uint32_t ui32Read;

    ui32Write = *pui32Write;
    ui32Read = *pui32Read;

    return((((ui32Write + 1) % ui32Size) == ui32Read) ? true : false);
}
#endif

//*****************************************************************************
//
//! Determines whether the ring buffer whose pointers and size are provided
//! is empty or not.
//!
//! \param pui32Read points to the read index for the buffer.
//! \param pui32Write points to the write index for the buffer.
//!
//! This function is used to determine whether or not a given ring buffer is
//! empty.  The structure of the code is specifically to ensure that we do not
//! see warnings from the compiler related to the order of volatile accesses
//! being undefined.
//!
//! \return Returns \b true if the buffer is empty or \b false otherwise.
//
//*****************************************************************************
#ifdef UART_BUFFERED
static bool
IsBufferEmpty(volatile uint32_t *pui32Read,
              volatile uint32_t *pui32Write)
{
    uint32_t ui32Write;
    uint32_t ui32Read;

    ui32Write = *pui32Write;
    ui32Read = *pui32Read;

    return((ui32Write == ui32Read) ? true : false);
}
#endif

//*****************************************************************************
//
//! Determines the number of bytes of data contained in a ring buffer.
//!
//! \param pui32Read points to the read index for the buffer.
//! \param pui32Write points to the write index for the buffer.
//! \param ui32Size is the size of the buffer in bytes.
//!
//! This function is used to determine how many bytes of data a given ring
//! buffer currently contains.  The structure of the code is specifically to
//! ensure that we do not see warnings from the compiler related to the order
//! of volatile accesses being undefined.
//!
//! \return Returns the number of bytes of data currently in the buffer.
//
//*****************************************************************************
#ifdef UART_BUFFERED
static uint32_t
GetBufferCount(volatile uint32_t *pui32Read,
               volatile uint32_t *pui32Write, uint32_t ui32Size)
{
    uint32_t ui32Write;
    uint32_t ui32Read;

    ui32Write = *pui32Write;
    ui32Read = *pui32Read;

    return((ui32Write >= ui32Read) ? (ui32Write - ui32Read) :
           (ui32Size - (ui32Read - ui32Write)));
}
#endif

//*****************************************************************************
//
// Take as many bytes from the transmit buffer as we have space for and move
// them into the UART transmit FIFO.
//
//*****************************************************************************
#ifdef UART_BUFFERED
static void
UARTPrimeTransmit(uint32_t ui32Base)
{
    //
    // Do we have any data to transmit?
    //
    if(!TX_BUFFER_EMPTY)
    {
        //
        // Disable the UART interrupt.  If we don't do this there is a race
        // condition which can cause the read index to be corrupted.
        //
        MAP_IntDisable(g_ui32UARTInt[g_ui32PortNum]);

        //
        // Yes - take some characters out of the transmit buffer and feed
        // them to the UART transmit FIFO.
        //
        while(MAP_UARTSpaceAvail(ui32Base) && !TX_BUFFER_EMPTY)
        {
            MAP_UARTCharPutNonBlocking(ui32Base,
                                      g_pcUARTTxBuffer[g_ui32UARTTxReadIndex]);
            ADVANCE_TX_BUFFER_INDEX(g_ui32UARTTxReadIndex);
        }

        //
        // Reenable the UART interrupt.
        //
        MAP_IntEnable(g_ui32UARTInt[g_ui32PortNum]);
    }
}
#endif

//*****************************************************************************
//
//! Configures the UART console.
//!
//! \param ui32PortNum is the number of UART port to use for the serial console
//! (0-2)
//! \param ui32Baud is the bit rate that the UART is to be configured to use.
//! \param ui32SrcClock is the frequency of the source clock for the UART
//! module.
//!
//! This function will configure the specified serial port to be used as a
//! serial console.  The serial parameters are set to the baud rate
//! specified by the \e ui32Baud parameter and use 8 bit, no parity, and 1 stop
//! bit.
//!
//! This function must be called prior to using any of the other UART console
//! functions: UARTprintf() or UARTgets().  This function assumes that the
//! caller has previously configured the relevant UART pins for operation as a
//! UART rather than as GPIOs.
//!
//! \return None.
//
//*****************************************************************************
void
UARTStdioConfig(uint32_t ui32PortNum, uint32_t ui32Baud, uint32_t ui32SrcClock)
{
    //
    // Check the arguments.
    //
    ASSERT((ui32PortNum == 0) || (ui32PortNum == 1) ||
           (ui32PortNum == 2));

#ifdef UART_BUFFERED
    //
    // In buffered mode, we only allow a single instance to be opened.
    //
    ASSERT(g_ui32Base == 0);
#endif

    //
    // Check to make sure the UART peripheral is present.
    //
    if(!MAP_SysCtlPeripheralPresent(g_ui32UARTPeriph[ui32PortNum]))
    {
        return;
    }

    //
    // Select the base address of the UART.
    //
    g_ui32Base = g_ui32UARTBase[ui32PortNum];

    //
    // Enable the UART peripheral for use.
    //
    MAP_SysCtlPeripheralEnable(g_ui32UARTPeriph[ui32PortNum]);

    //
    // Configure the UART for 115200, n, 8, 1
    //
    MAP_UARTConfigSetExpClk(g_ui32Base, ui32SrcClock, ui32Baud,
                            (UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_WLEN_8));

#ifdef UART_BUFFERED
    //
    // Set the UART to interrupt whenever the TX FIFO is almost empty or
    // when any character is received.
    //
    MAP_UARTFIFOLevelSet(g_ui32Base, UART_FIFO_TX1_8, UART_FIFO_RX1_8);

    //
    // Flush both the buffers.
    //
    UARTFlushRx();
    UARTFlushTx(true);

    //
    // Remember which interrupt we are dealing with.
    //
    g_ui32PortNum = ui32PortNum;

    //
    // We are configured for buffered output so enable the master interrupt
    // for this UART and the receive interrupts.  We don't actually enable the
    // transmit interrupt in the UART itself until some data has been placed
    // in the transmit buffer.
    //
    MAP_UARTIntDisable(g_ui32Base, 0xFFFFFFFF);
    MAP_UARTIntEnable(g_ui32Base, UART_INT_RX | UART_INT_RT);
    MAP_IntEnable(g_ui32UARTInt[ui32PortNum]);
#endif

    //
    // Enable the UART operation.
    //
    MAP_UARTEnable(g_ui32Base);
}

//*****************************************************************************
//
//! Writes a string of characters to the UART output.
//!
//! \param pcBuf points to a buffer containing the string to transmit.
//! \param ui32Len is the length of the string to transmit.
//!
//! This function will transmit the string to the UART output.  The number of
//! characters transmitted is determined by the \e ui32Len parameter.  This
//! function does no interpretation or translation of any characters.  Since
//! the output is sent to a UART, any LF (/n) characters encountered will be
//! replaced with a CRLF pair.
//!
//! Besides using the \e ui32Len parameter to stop transmitting the string, if
//! a null character (0) is encountered, then no more characters will be
//! transmitted and the function will return.
//!
//! In non-buffered mode, this function is blocking and will not return until
//! all the characters have been written to the output FIFO.  In buffered mode,
//! the characters are written to the UART transmit buffer and the call returns
//! immediately.  If insufficient space remains in the transmit buffer,
//! additional characters are discarded.
//!
//! \return Returns the count of characters written.
//
//*****************************************************************************
int
UARTwrite(const char *pcBuf, uint32_t ui32Len)
{
#ifdef UART_BUFFERED
    unsigned int uIdx;

    //
    // Check for valid arguments.
    //
    ASSERT(pcBuf != 0);
    ASSERT(g_ui32Base != 0);

    //
    // Send the characters
    //
    for(uIdx = 0; uIdx < ui32Len; uIdx++)
    {
        //
        // If the character to the UART is \n, then add a \r before it so that
        // \n is translated to \n\r in the output.
        //
        if(pcBuf[uIdx] == '\n')
        {
            if(!TX_BUFFER_FULL)
            {
                g_pcUARTTxBuffer[g_ui32UARTTxWriteIndex] = '\r';
                ADVANCE_TX_BUFFER_INDEX(g_ui32UARTTxWriteIndex);
            }
            else
            {
                //
                // Buffer is full - discard remaining characters and return.
                //
                break;
            }
        }

        //
        // Send the character to the UART output.
        //
        if(!TX_BUFFER_FULL)
        {
            g_pcUARTTxBuffer[g_ui32UARTTxWriteIndex] = pcBuf[uIdx];
            ADVANCE_TX_BUFFER_INDEX(g_ui32UARTTxWriteIndex);
        }
        else
        {
            //
            // Buffer is full - discard remaining characters and return.
            //
            break;
        }
    }

    //
    // If we have anything in the buffer, make sure that the UART is set
    // up to transmit it.
    //
    if(!TX_BUFFER_EMPTY)
    {
        UARTPrimeTransmit(g_ui32Base);
        MAP_UARTIntEnable(g_ui32Base, UART_INT_TX);
    }

    //
    // Return the number of characters written.
    //
    return(uIdx);
#else
    unsigned int uIdx;

    //
    // Check for valid UART base address, and valid arguments.
    //
    ASSERT(g_ui32Base != 0);
    ASSERT(pcBuf != 0);

    //
    // Send the characters
    //
    for(uIdx = 0; uIdx < ui32Len; uIdx++)
    {
        //
        // If the character to the UART is \n, then add a \r before it so that
        // \n is translated to \n\r in the output.
        //
        if(pcBuf[uIdx] == '\n')
        {
            MAP_UARTCharPut(g_ui32Base, '\r');
        }

        //
        // Send the character to the UART output.
        //
        MAP_UARTCharPut(g_ui32Base, pcBuf[uIdx]);
    }

    //
    // Return the number of characters written.
    //
    return(uIdx);
#endif
}

//*****************************************************************************
//
//! A simple UART based get string function, with some line processing.
//!
//! \param pcBuf points to a buffer for the incoming string from the UART.
//! \param ui32Len is the length of the buffer for storage of the string,
//! including the trailing 0.
//!
//! This function will receive a string from the UART input and store the
//! characters in the buffer pointed to by \e pcBuf.  The characters will
//! continue to be stored until a termination character is received.  The
//! termination characters are CR, LF, or ESC.  A CRLF pair is treated as a
//! single termination character.  The termination characters are not stored in
//! the string.  The string will be terminated with a 0 and the function will
//! return.
//!
//! In both buffered and unbuffered modes, this function will block until
//! a termination character is received.  If non-blocking operation is required
//! in buffered mode, a call to UARTPeek() may be made to determine whether
//! a termination character already exists in the receive buffer prior to
//! calling UARTgets().
//!
//! Since the string will be null terminated, the user must ensure that the
//! buffer is sized to allow for the additional null character.
//!
//! \return Returns the count of characters that were stored, not including
//! the trailing 0.
//
//*****************************************************************************
int
UARTgets(char *pcBuf, uint32_t ui32Len)
{
#ifdef UART_BUFFERED
    uint32_t ui32Count = 0;
    int8_t cChar;

    //
    // Check the arguments.
    //
    ASSERT(pcBuf != 0);
    ASSERT(ui32Len != 0);
    ASSERT(g_ui32Base != 0);

    //
    // Adjust the length back by 1 to leave space for the trailing
    // null terminator.
    //
    ui32Len--;

    //
    // Process characters until a newline is received.
    //
    while(1)
    {
        //
        // Read the next character from the receive buffer.
        //
        if(!RX_BUFFER_EMPTY)
        {
            cChar = g_pcUARTRxBuffer[g_ui32UARTRxReadIndex];
            ADVANCE_RX_BUFFER_INDEX(g_ui32UARTRxReadIndex);

            //
            // See if a newline or escape character was received.
            //
            if((cChar == '\r') || (cChar == '\n') || (cChar == 0x1b))
            {
                //
                // Stop processing the input and end the line.
                //
                break;
            }

            //
            // Process the received character as long as we are not at the end
            // of the buffer.  If the end of the buffer has been reached then
            // all additional characters are ignored until a newline is
            // received.
            //
            if(ui32Count < ui32Len)
            {
                //
                // Store the character in the caller supplied buffer.
                //
                pcBuf[ui32Count] = cChar;

                //
                // Increment the count of characters received.
                //
                ui32Count++;
            }
        }
    }

    //
    // Add a null termination to the string.
    //
    pcBuf[ui32Count] = 0;

    //
    // Return the count of int8_ts in the buffer, not counting the trailing 0.
    //
    return(ui32Count);
#else
    uint32_t ui32Count = 0;
    int8_t cChar;
    static int8_t bLastWasCR = 0;

    //
    // Check the arguments.
    //
    ASSERT(pcBuf != 0);
    ASSERT(ui32Len != 0);
    ASSERT(g_ui32Base != 0);

    //
    // Adjust the length back by 1 to leave space for the trailing
    // null terminator.
    //
    ui32Len--;

    //
    // Process characters until a newline is received.
    //
    while(1)
    {
        //
        // Read the next character from the console.
        //
        cChar = MAP_UARTCharGet(g_ui32Base);

        //
        // See if the backspace key was pressed.
        //
        if(cChar == '\b')
        {
            //
            // If there are any characters already in the buffer, then delete
            // the last.
            //
            if(ui32Count)
            {
                //
                // Rub out the previous character.
                //
                UARTwrite("\b \b", 3);

                //
                // Decrement the number of characters in the buffer.
                //
                ui32Count--;
            }

            //
            // Skip ahead to read the next character.
            //
            continue;
        }

        //
        // If this character is LF and last was CR, then just gobble up the
        // character because the EOL processing was taken care of with the CR.
        //
        if((cChar == '\n') && bLastWasCR)
        {
            bLastWasCR = 0;
            continue;
        }

        //
        // See if a newline or escape character was received.
        //
        if((cChar == '\r') || (cChar == '\n') || (cChar == 0x1b))
        {
            //
            // If the character is a CR, then it may be followed by a LF which
            // should be paired with the CR.  So remember that a CR was
            // received.
            //
            if(cChar == '\r')
            {
                bLastWasCR = 1;
            }

            //
            // Stop processing the input and end the line.
            //
            break;
        }

        //
        // Process the received character as long as we are not at the end of
        // the buffer.  If the end of the buffer has been reached then all
        // additional characters are ignored until a newline is received.
        //
        if(ui32Count < ui32Len)
        {
            //
            // Store the character in the caller supplied buffer.
            //
            pcBuf[ui32Count] = cChar;

            //
            // Increment the count of characters received.
            //
            ui32Count++;

            //
            // Reflect the character back to the user.
            //
            MAP_UARTCharPut(g_ui32Base, cChar);
        }
    }

    //
    // Add a null termination to the string.
    //
    pcBuf[ui32Count] = 0;

    //
    // Send a CRLF pair to the terminal to end the line.
    //
    UARTwrite("\r\n", 2);

    //
    // Return the count of int8_ts in the buffer, not counting the trailing 0.
    //
    return(ui32Count);
#endif
}

//*****************************************************************************
//
//! Read a single character from the UART, blocking if necessary.
//!
//! This function will receive a single character from the UART and store it at
//! the supplied address.
//!
//! In both buffered and unbuffered modes, this function will block until a
//! character is received.  If non-blocking operation is required in buffered
//! mode, a call to UARTRxAvail() may be made to determine whether any
//! characters are currently available for reading.
//!
//! \return Returns the character read.
//
//*****************************************************************************
unsigned char
UARTgetc(void)
{
#ifdef UART_BUFFERED
    unsigned char cChar;

    //
    // Wait for a character to be received.
    //
    while(RX_BUFFER_EMPTY)
    {
        //
        // Block waiting for a character to be received (if the buffer is
        // currently empty).
        //
    }

    //
    // Read a character from the buffer.
    //
    cChar = g_pcUARTRxBuffer[g_ui32UARTRxReadIndex];
    ADVANCE_RX_BUFFER_INDEX(g_ui32UARTRxReadIndex);

    //
    // Return the character to the caller.
    //
    return(cChar);
#else
    //
    // Block until a character is received by the UART then return it to
    // the caller.
    //
    return(MAP_UARTCharGet(g_ui32Base));
#endif
}

//*****************************************************************************
//
//! A simple UART based vprintf function supporting \%c, \%d, \%p, \%s, \%u,
//! \%x, and \%X.
//!
//! \param pcString is the format string.
//! \param vaArgP is a variable argument list pointer whose content will depend
//! upon the format string passed in \e pcString.
//!
//! This function is very similar to the C library <tt>vprintf()</tt> function.
//! All of its output will be sent to the UART.  Only the following formatting
//! characters are supported:
//!
//! - \%c to print a character
//! - \%d or \%i to print a decimal value
//! - \%l to print a long decimal value
//! - \%s to print a string
//! - \%u to print an unsigned decimal value
//! - \%x to print a hexadecimal value using lower case letters
//! - \%X to print a hexadecimal value using lower case letters (not upper case
//! letters as would typically be used)
//! - \%p to print a pointer as a hexadecimal value
//! - \%\% to print out a \% character
//!
//! For \%s, \%d, \%i, \%u, \%p, \%x, and \%X, an optional number may reside
//! between the \% and the format character, which specifies the minimum number
//! of characters to use for that value; if preceded by a 0 then the extra
//! characters will be filled with zeros instead of spaces.  For example,
//! ``\%8d'' will use eight characters to print the decimal value with spaces
//! added to reach eight; ``\%08d'' will use eight characters as well but will
//! add zeroes instead of spaces.
//!
//! The type of the arguments in the variable arguments list must match the
//! requirements of the format string.  For example, if an integer was passed
//! where a string was expected, an error of some kind will most likely occur.
//!
//! \return None.
//
//*****************************************************************************
void
UARTvprintf(const char *pcString, va_list vaArgP)
{
    uint32_t ui32Idx, ui32Value, ui32Pos, ui32Count, ui32Base, ui32Neg;
    char *pcStr, pcBuf[16], cFill;

    //
    // Check the arguments.
    //
    ASSERT(pcString != 0);

    //
    // Loop while there are more characters in the string.
    //
    while(*pcString)
    {
        //
        // Find the first non-% character, or the end of the string.
        //
        for(ui32Idx = 0;
            (pcString[ui32Idx] != '%') && (pcString[ui32Idx] != '\0');
            ui32Idx++)
        {
        }

        //
        // Write this portion of the string.
        //
        UARTwrite(pcString, ui32Idx);

        //
        // Skip the portion of the string that was written.
        //
        pcString += ui32Idx;

        //
        // See if the next character is a %.
        //
        if(*pcString == '%')
        {
            //
            // Skip the %.
            //
            pcString++;

            //
            // Set the digit count to zero, and the fill character to space
            // (in other words, to the defaults).
            //
            ui32Count = 0;
            cFill = ' ';

            //
            // It may be necessary to get back here to process more characters.
            // Goto's aren't pretty, but effective.  I feel extremely dirty for
            // using not one but two of the beasts.
            //
again:

            //
            // Determine how to handle the next character.
            //
            switch(*pcString++)
            {
                //
                // Handle the digit characters.
                //
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                {
                    //
                    // If this is a zero, and it is the first digit, then the
                    // fill character is a zero instead of a space.
                    //
                    if((pcString[-1] == '0') && (ui32Count == 0))
                    {
                        cFill = '0';
                    }

                    //
                    // Update the digit count.
                    //
                    ui32Count *= 10;
                    ui32Count += pcString[-1] - '0';

                    //
                    // Get the next character.
                    //
                    goto again;
                }

                //
                // Handle the %c command.
                //
                case 'c':
                {
                    //
                    // Get the value from the varargs.
                    //
                    ui32Value = va_arg(vaArgP, uint32_t);

                    //
                    // Print out the character.
                    //
                    UARTwrite((char *)&ui32Value, 1);

                    //
                    // This command has been handled.
                    //
                    break;
                }

                //
                // Handle the %d and %i commands.
                //
                case 'd':
                case 'i':
                {
                    //
                    // Get the value from the varargs.
                    //
                    ui32Value = va_arg(vaArgP, uint16_t);

                    //
                    // Reset the buffer position.
                    //
                    ui32Pos = 0;

                    //
                    // If the value is negative, make it positive and indicate
                    // that a minus sign is needed.
                    //
                    if((int32_t)ui32Value < 0)
                    {
                        //
                        // Make the value positive.
                        //
                        ui32Value = -(int32_t)ui32Value;

                        //
                        // Indicate that the value is negative.
                        //
                        ui32Neg = 1;
                    }
                    else
                    {
                        //
                        // Indicate that the value is positive so that a minus
                        // sign isn't inserted.
                        //
                        ui32Neg = 0;
                    }

                    //
                    // Set the base to 10.
                    //
                    ui32Base = 10;

                    //
                    // Convert the value to ASCII.
                    //
                    goto convert;
                }

                //
                // Handle the %l command.
                //
                case 'l':
                {
                	//
                    // Get the value from the varargs.
                    //
                    ui32Value = va_arg(vaArgP, uint32_t);

                    //
                    // Reset the buffer position.
                    //
                    ui32Pos = 0;

                    //
                    // If the value is negative, make it positive and indicate
                    // that a minus sign is needed.
                    //
                    if((int32_t)ui32Value < 0)
                    {
                    	//
                    	// Make the value positive.
                    	//
                    	ui32Value = -(int32_t)ui32Value;

                    	//
                    	// Indicate that the value is negative.
                    	//
                    	ui32Neg = 1;
                    }
                    else
                    {
                    	//
                    	// Indicate that the value is positive so that a minus
                    	// sign isn't inserted.
                    	//
                    	ui32Neg = 0;
                    }

                    //
                    // Set the base to 10.
                    //
                    ui32Base = 10;

                    //
                    // Convert the value to ASCII.
                    //
                    goto convert;
                }

                //
                // Handle the %s command.
                //
                case 's':
                {
                    //
                    // Get the string pointer from the varargs.
                    //
                    pcStr = va_arg(vaArgP, char *);

                    //
                    // Determine the length of the string.
                    //
                    for(ui32Idx = 0; pcStr[ui32Idx] != '\0'; ui32Idx++)
                    {
                    }

                    //
                    // Write the string.
                    //
                    UARTwrite(pcStr, ui32Idx);

                    //
                    // Write any required padding spaces
                    //
                    if(ui32Count > ui32Idx)
                    {
                        ui32Count -= ui32Idx;
                        while(ui32Count--)
                        {
                            UARTwrite(" ", 1);
                        }
                    }

                    //
                    // This command has been handled.
                    //
                    break;
                }

                //
                // Handle the %u command.
                //
                case 'u':
                {
                    //
                    // Get the value from the varargs.
                    //
                    ui32Value = va_arg(vaArgP, uint32_t);

                    //
                    // Reset the buffer position.
                    //
                    ui32Pos = 0;

                    //
                    // Set the base to 10.
                    //
                    ui32Base = 10;

                    //
                    // Indicate that the value is positive so that a minus sign
                    // isn't inserted.
                    //
                    ui32Neg = 0;

                    //
                    // Convert the value to ASCII.
                    //
                    goto convert;
                }

                //
                // Handle the %x and %X commands.  Note that they are treated
                // identically; in other words, %X will use lower case letters
                // for a-f instead of the upper case letters it should use.  We
                // also alias %p to %x.
                //
                case 'x':
                case 'X':
                case 'p':
                {
                    //
                    // Get the value from the varargs.
                    //
                    ui32Value = va_arg(vaArgP, uint32_t);

                    //
                    // Reset the buffer position.
                    //
                    ui32Pos = 0;

                    //
                    // Set the base to 16.
                    //
                    ui32Base = 16;

                    //
                    // Indicate that the value is positive so that a minus sign
                    // isn't inserted.
                    //
                    ui32Neg = 0;

                    //
                    // Determine the number of digits in the string version of
                    // the value.
                    //
convert:
                    for(ui32Idx = 1;
                        (((ui32Idx * ui32Base) <= ui32Value) &&
                         (((ui32Idx * ui32Base) / ui32Base) == ui32Idx));
                        ui32Idx *= ui32Base, ui32Count--)
                    {
                    }

                    //
                    // If the value is negative, reduce the count of padding
                    // characters needed.
                    //
                    if(ui32Neg)
                    {
                        ui32Count--;
                    }

                    //
                    // If the value is negative and the value is padded with
                    // zeros, then place the minus sign before the padding.
                    //
                    if(ui32Neg && (cFill == '0'))
                    {
                        //
                        // Place the minus sign in the output buffer.
                        //
                        pcBuf[ui32Pos++] = '-';

                        //
                        // The minus sign has been placed, so turn off the
                        // negative flag.
                        //
                        ui32Neg = 0;
                    }

                    //
                    // Provide additional padding at the beginning of the
                    // string conversion if needed.
                    //
                    if((ui32Count > 1) && (ui32Count < 16))
                    {
                        for(ui32Count--; ui32Count; ui32Count--)
                        {
                            pcBuf[ui32Pos++] = cFill;
                        }
                    }

                    //
                    // If the value is negative, then place the minus sign
                    // before the number.
                    //
                    if(ui32Neg)
                    {
                        //
                        // Place the minus sign in the output buffer.
                        //
                        pcBuf[ui32Pos++] = '-';
                    }

                    //
                    // Convert the value into a string.
                    //
                    for(; ui32Idx; ui32Idx /= ui32Base)
                    {
                        pcBuf[ui32Pos++] =
                            g_pcHex[(ui32Value / ui32Idx) % ui32Base];
                    }

                    //
                    // Write the string.
                    //
                    UARTwrite(pcBuf, ui32Pos);

                    //
                    // This command has been handled.
                    //
                    break;
                }

                //
                // Handle the %% command.
                //
                case '%':
                {
                    //
                    // Simply write a single %.
                    //
                    UARTwrite(pcString - 1, 1);

                    //
                    // This command has been handled.
                    //
                    break;
                }

                //
                // Handle all other commands.
                //
                default:
                {
                    //
                    // Indicate an error.
                    //
                    UARTwrite("ERROR", 5);

                    //
                    // This command has been handled.
                    //
                    break;
                }
            }
        }
    }
}

//*****************************************************************************
//
//! A simple UART based printf function supporting \%c, \%d, \%p, \%s, \%u,
//! \%x, and \%X.
//!
//! \param pcString is the format string.
//! \param ... are the optional arguments, which depend on the contents of the
//! format string.
//!
//! This function is very similar to the C library <tt>fprintf()</tt> function.
//! All of its output will be sent to the UART.  Only the following formatting
//! characters are supported:
//!
//! - \%c to print a character
//! - \%d or \%i to print a decimal value
//! - \%s to print a string
//! - \%u to print an unsigned decimal value
//! - \%x to print a hexadecimal value using lower case letters
//! - \%X to print a hexadecimal value using lower case letters (not upper case
//! letters as would typically be used)
//! - \%p to print a pointer as a hexadecimal value
//! - \%\% to print out a \% character
//!
//! For \%s, \%d, \%i, \%u, \%p, \%x, and \%X, an optional number may reside
//! between the \% and the format character, which specifies the minimum number
//! of characters to use for that value; if preceded by a 0 then the extra
//! characters will be filled with zeros instead of spaces.  For example,
//! ``\%8d'' will use eight characters to print the decimal value with spaces
//! added to reach eight; ``\%08d'' will use eight characters as well but will
//! add zeroes instead of spaces.
//!
//! The type of the arguments after \e pcString must match the requirements of
//! the format string.  For example, if an integer was passed where a string
//! was expected, an error of some kind will most likely occur.
//!
//! \return None.
//
//*****************************************************************************
void
UARTprintf(const char *pcString, ...)
{
    va_list vaArgP;

    //
    // Start the varargs processing.
    //
    va_start(vaArgP, pcString);

    UARTvprintf(pcString, vaArgP);

    //
    // We're finished with the varargs now.
    //
    va_end(vaArgP);
}

//*****************************************************************************
//
//! Returns the number of bytes available in the receive buffer.
//!
//! This function, available only when the module is built to operate in
//! buffered mode using \b UART_BUFFERED, may be used to determine the number
//! of bytes of data currently available in the receive buffer.
//!
//! \return Returns the number of available bytes.
//
//*****************************************************************************
#if defined(UART_BUFFERED) || defined(DOXYGEN)
int
UARTRxBytesAvail(void)
{
    return(RX_BUFFER_USED);
}
#endif

#if defined(UART_BUFFERED) || defined(DOXYGEN)
//*****************************************************************************
//
//! Returns the number of bytes free in the transmit buffer.
//!
//! This function, available only when the module is built to operate in
//! buffered mode using \b UART_BUFFERED, may be used to determine the amount
//! of space currently available in the transmit buffer.
//!
//! \return Returns the number of free bytes.
//
//*****************************************************************************
int
UARTTxBytesFree(void)
{
    return(TX_BUFFER_FREE);
}
#endif

//*****************************************************************************
//
//! Looks ahead in the receive buffer for a particular character.
//!
//! \param ucChar is the character that is to be searched for.
//!
//! This function, available only when the module is built to operate in
//! buffered mode using \b UART_BUFFERED, may be used to look ahead in the
//! receive buffer for a particular character and report its position if found.
//! It is typically used to determine whether a complete line of user input is
//! available, in which case ucChar should be set to CR ('\\r') which is used
//! as the line end marker in the receive buffer.
//!
//! \return Returns -1 to indicate that the requested character does not exist
//! in the receive buffer.  Returns a non-negative number if the character was
//! found in which case the value represents the position of the first instance
//! of \e ucChar relative to the receive buffer read pointer.
//
//*****************************************************************************
#if defined(UART_BUFFERED) || defined(DOXYGEN)
int
UARTPeek(unsigned char ucChar)
{
    int iCount;
    int iAvail;
    uint32_t ui32ReadIndex;

    //
    // How many characters are there in the receive buffer?
    //
    iAvail = (int)RX_BUFFER_USED;
    ui32ReadIndex = g_ui32UARTRxReadIndex;

    //
    // Check all the unread characters looking for the one passed.
    //
    for(iCount = 0; iCount < iAvail; iCount++)
    {
        if(g_pcUARTRxBuffer[ui32ReadIndex] == ucChar)
        {
            //
            // We found it so return the index
            //
            return(iCount);
        }
        else
        {
            //
            // This one didn't match so move on to the next character.
            //
            ADVANCE_RX_BUFFER_INDEX(ui32ReadIndex);
        }
    }

    //
    // If we drop out of the loop, we didn't find the character in the receive
    // buffer.
    //
    return(-1);
}
#endif

//*****************************************************************************
//
//! Flushes the receive buffer.
//!
//! This function, available only when the module is built to operate in
//! buffered mode using \b UART_BUFFERED, may be used to discard any data
//! received from the UART but not yet read using UARTgets().
//!
//! \return None.
//
//*****************************************************************************
#if defined(UART_BUFFERED) || defined(DOXYGEN)
void
UARTFlushRx(void)
{
    uint32_t ui32Int;

    //
    // Temporarily turn off interrupts.
    //
    ui32Int = MAP_IntMasterDisable();

    //
    // Flush the receive buffer.
    //
    g_ui32UARTRxReadIndex = 0;
    g_ui32UARTRxWriteIndex = 0;

    //
    // If interrupts were enabled when we turned them off, turn them
    // back on again.
    //
    if(!ui32Int)
    {
        MAP_IntMasterEnable();
    }
}
#endif

//*****************************************************************************
//
//! Flushes the transmit buffer.
//!
//! \param bDiscard indicates whether any remaining data in the buffer should
//! be discarded (\b true) or transmitted (\b false).
//!
//! This function, available only when the module is built to operate in
//! buffered mode using \b UART_BUFFERED, may be used to flush the transmit
//! buffer, either discarding or transmitting any data received via calls to
//! UARTprintf() that is waiting to be transmitted.  On return, the transmit
//! buffer will be empty.
//!
//! \return None.
//
//*****************************************************************************
#if defined(UART_BUFFERED) || defined(DOXYGEN)
void
UARTFlushTx(bool bDiscard)
{
    uint32_t ui32Int;

    //
    // Should the remaining data be discarded or transmitted?
    //
    if(bDiscard)
    {
        //
        // The remaining data should be discarded, so temporarily turn off
        // interrupts.
        //
        ui32Int = MAP_IntMasterDisable();

        //
        // Flush the transmit buffer.
        //
        g_ui32UARTTxReadIndex = 0;
        g_ui32UARTTxWriteIndex = 0;

        //
        // If interrupts were enabled when we turned them off, turn them
        // back on again.
        //
        if(!ui32Int)
        {
            MAP_IntMasterEnable();
        }
    }
    else
    {
        //
        // Wait for all remaining data to be transmitted before returning.
        //
        while(!TX_BUFFER_EMPTY)
        {
        }
    }
}
#endif

//*****************************************************************************
//
//! Enables or disables echoing of received characters to the transmitter.
//!
//! \param bEnable must be set to \b true to enable echo or \b false to
//! disable it.
//!
//! This function, available only when the module is built to operate in
//! buffered mode using \b UART_BUFFERED, may be used to control whether or not
//! received characters are automatically echoed back to the transmitter.  By
//! default, echo is enabled and this is typically the desired behavior if
//! the module is being used to support a serial command line.  In applications
//! where this module is being used to provide a convenient, buffered serial
//! interface over which application-specific binary protocols are being run,
//! however, echo may be undesirable and this function can be used to disable
//! it.
//!
//! \return None.
//
//*****************************************************************************
#if defined(UART_BUFFERED) || defined(DOXYGEN)
void
UARTEchoSet(bool bEnable)
{
    g_bDisableEcho = !bEnable;
}
#endif

//*****************************************************************************
//
//! Handles UART interrupts.
//!
//! This function handles interrupts from the UART.  It will copy data from the
//! transmit buffer to the UART transmit FIFO if space is available, and it
//! will copy data from the UART receive FIFO to the receive buffer if data is
//! available.
//!
//! \return None.
//
//*****************************************************************************
#if defined(UART_BUFFERED) || defined(DOXYGEN)
void
UARTStdioIntHandler(void)
{
    uint32_t ui32Ints;
    int8_t cChar;
    int32_t i32Char;
    static bool bLastWasCR = false;

    //
    // Get and clear the current interrupt source(s)
    //
    ui32Ints = MAP_UARTIntStatus(g_ui32Base, true);
    MAP_UARTIntClear(g_ui32Base, ui32Ints);

    //
    // Are we being interrupted because the TX FIFO has space available?
    //
    if(ui32Ints & UART_INT_TX)
    {
        //
        // Move as many bytes as we can into the transmit FIFO.
        //
        UARTPrimeTransmit(g_ui32Base);

        //
        // If the output buffer is empty, turn off the transmit interrupt.
        //
        if(TX_BUFFER_EMPTY)
        {
            MAP_UARTIntDisable(g_ui32Base, UART_INT_TX);
        }
    }

    //
    // Are we being interrupted due to a received character?
    //
    if(ui32Ints & (UART_INT_RX | UART_INT_RT))
    {
        //
        // Get all the available characters from the UART.
        //
        while(MAP_UARTCharsAvail(g_ui32Base))
        {
            //
            // Read a character
            //
            i32Char = MAP_UARTCharGetNonBlocking(g_ui32Base);
            cChar = (unsigned char)(i32Char & 0xFF);

            //
            // If echo is disabled, we skip the various text filtering
            // operations that would typically be required when supporting a
            // command line.
            //
            if(!g_bDisableEcho)
            {
                //
                // Handle backspace by erasing the last character in the
                // buffer.
                //
                if(cChar == '\b')
                {
                    //
                    // If there are any characters already in the buffer, then
                    // delete the last.
                    //
                    if(!RX_BUFFER_EMPTY)
                    {
                        //
                        // Rub out the previous character on the users
                        // terminal.
                        //
                        UARTwrite("\b \b", 3);

                        //
                        // Decrement the number of characters in the buffer.
                        //
                        if(g_ui32UARTRxWriteIndex == 0)
                        {
                            g_ui32UARTRxWriteIndex = UART_RX_BUFFER_SIZE - 1;
                        }
                        else
                        {
                            g_ui32UARTRxWriteIndex--;
                        }
                    }

                    //
                    // Skip ahead to read the next character.
                    //
                    continue;
                }

                //
                // If this character is LF and last was CR, then just gobble up
                // the character since we already echoed the previous CR and we
                // don't want to store 2 characters in the buffer if we don't
                // need to.
                //
                if((cChar == '\n') && bLastWasCR)
                {
                    bLastWasCR = false;
                    continue;
                }

                //
                // See if a newline or escape character was received.
                //
                if((cChar == '\r') || (cChar == '\n') || (cChar == 0x1b))
                {
                    //
                    // If the character is a CR, then it may be followed by an
                    // LF which should be paired with the CR.  So remember that
                    // a CR was received.
                    //
                    if(cChar == '\r')
                    {
                        bLastWasCR = 1;
                    }

                    //
                    // Regardless of the line termination character received,
                    // put a CR in the receive buffer as a marker telling
                    // UARTgets() where the line ends.  We also send an
                    // additional LF to ensure that the local terminal echo
                    // receives both CR and LF.
                    //
                    cChar = '\r';
                    UARTwrite("\n", 1);
                }
            }

            //
            // If there is space in the receive buffer, put the character
            // there, otherwise throw it away.
            //
            if(!RX_BUFFER_FULL)
            {
                //
                // Store the new character in the receive buffer
                //
                g_pcUARTRxBuffer[g_ui32UARTRxWriteIndex] =
                    (unsigned char)(i32Char & 0xFF);
                ADVANCE_RX_BUFFER_INDEX(g_ui32UARTRxWriteIndex);

                //
                // If echo is enabled, write the character to the transmit
                // buffer so that the user gets some immediate feedback.
                //
                if(!g_bDisableEcho)
                {
                    UARTwrite((const char *)&cChar, 1);
                }
            }
        }

        //
        // If we wrote anything to the transmit buffer, make sure it actually
        // gets transmitted.
        //
        UARTPrimeTransmit(g_ui32Base);
        MAP_UARTIntEnable(g_ui32Base, UART_INT_TX);
    }
}
#endif

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//
// End of file
//
