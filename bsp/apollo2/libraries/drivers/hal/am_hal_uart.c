//*****************************************************************************
//
//  am_hal_uart.c
//! @file
//!
//! @brief Functions for interfacing with the UART.
//!
//! @addtogroup uart2 UART
//! @ingroup apollo2hal
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "am_mcu_apollo.h"

//*****************************************************************************
//
// Transmit and receive queue pointers for each UART module.
//
//*****************************************************************************
am_hal_queue_t g_psTxQueue[AM_REG_UART_NUM_MODULES];
am_hal_queue_t g_psRxQueue[AM_REG_UART_NUM_MODULES];

//*****************************************************************************
//
// Power tracking structure
//
//*****************************************************************************
am_hal_uart_pwrsave_t am_hal_uart_pwrsave[AM_REG_UART_NUM_MODULES];

//*****************************************************************************
//
// Set Baud Rate based on the UART clock frequency.
//
//*****************************************************************************

#define BAUDCLK     (32)

static void
config_baudrate(uint32_t ui32Module, uint32_t ui32Baudrate, uint32_t ui32UartClkFreq)
{
    uint64_t ui64FractionDivisorLong;
    uint64_t ui64IntermediateLong;
    uint32_t ui32IntegerDivisor;
    uint32_t ui32FractionDivisor;
    uint32_t ui32BaudClk;

    //
    // Calculate register values.
    //
    ui32BaudClk = BAUDCLK * ui32Baudrate;
    ui32IntegerDivisor = (uint32_t)(ui32UartClkFreq / ui32BaudClk);
    ui64IntermediateLong = (ui32UartClkFreq * 64) / ui32BaudClk;
    ui64FractionDivisorLong = ui64IntermediateLong - (ui32IntegerDivisor * 64);
    ui32FractionDivisor = (uint32_t)ui64FractionDivisorLong;

    //
    // Check the result.
    //
    am_hal_debug_assert_msg(ui32IntegerDivisor > 0, "Integer divisor MUST be greater than or equal to 1.");

    //
    // Write the UART regs.
    //
    AM_REGn(UART, ui32Module, IBRD) = ui32IntegerDivisor;
    AM_REGn(UART, ui32Module, IBRD) = ui32IntegerDivisor;
    AM_REGn(UART, ui32Module, FBRD) = ui32FractionDivisor;
}

//*****************************************************************************
//
//! @brief Set up the UART.
//!
//! @param psConfig pointer to a structure that holds the settings for the UART.
//! @param ui32UartclkFreq is clock frequency that the UART is running at.
//!
//! This function should be used to perform the initial set-up of the UART.
//!
//! @return none.
//
//*****************************************************************************
void
am_hal_uart_config(uint32_t ui32Module, am_hal_uart_config_t *psConfig)

{
    uint32_t ui32ConfigVal = 0;

    //
    // Configure the Baudrate.
    //
    config_baudrate(ui32Module, psConfig->ui32BaudRate, am_hal_clkgen_sysclk_get());

    //
    // OR in the Data bits.
    //
    ui32ConfigVal |= psConfig->ui32DataBits;

    //
    // OR in the Two Stop bit if used.
    //
    ui32ConfigVal |= psConfig->bTwoStopBits ? AM_REG_UART_LCRH_STP2_M : 0;

    //
    // OR in the Parity.
    //
    ui32ConfigVal |= psConfig->ui32Parity;

    //
    // Write config to Line control register.
    //
    AM_REGn(UART, ui32Module, LCRH) |= ui32ConfigVal;

    //
    // Write the flow control settings to the control register.
    //
    AM_REGn(UART, ui32Module, CR) |= psConfig->ui32FlowCtrl;

    //
    // Set the clock select field for 24MHz from the HFRC
    //
    AM_REGn(UART, ui32Module, CR) |= AM_REG_UART_CR_CLKSEL_24MHZ;
}

//*****************************************************************************
//
//! @brief Gets the status.
//!
//! This function returns the current status.
//!
//! @return current status.
//
//*****************************************************************************
uint32_t
am_hal_uart_status_get(uint32_t ui32Module)
{
    //
    // Read and return the Status.
    //
    return AM_REGn(UART, ui32Module, RSR);
}

//*****************************************************************************
//
//! @brief Gets the interrupt status.
//!
//! @param bEnabledOnly - If true returns the enabled interrupt status.
//!
//! This function returns the masked or raw interrupt status.
//!
//! @return Bitwise representation of the current interrupt status.
//!
//! The return value will be the logical OR of one or more of the following
//! values:
//!
//!     AM_HAL_UART_INT_OVER_RUN
//!     AM_HAL_UART_INT_BREAK_ERR
//!     AM_HAL_UART_INT_PARITY_ERR
//!     AM_HAL_UART_INT_FRAME_ERR
//!     AM_HAL_UART_INT_RX_TMOUT
//!     AM_HAL_UART_INT_TX
//!     AM_REG_UART_IER_TXIM_M
//!     AM_HAL_UART_INT_RX
//!     AM_HAL_UART_INT_DSRM
//!     AM_HAL_UART_INT_DCDM
//!     AM_HAL_UART_INT_CTSM
//!     AM_HAL_UART_INT_RIM
//
//*****************************************************************************
uint32_t
am_hal_uart_int_status_get(uint32_t ui32Module, bool bEnabledOnly)
{
    if (bEnabledOnly)
    {
        //
        // Read and return the Masked Interrupt Status.
        //
        return AM_REGn(UART, ui32Module, MIS);
    }
    else
    {
        //
        // Read and return the Raw Interrupt Status.
        //
        return AM_REGn(UART, ui32Module, IES);
    }
}

//*****************************************************************************
//
//! @brief Clears the desired interrupts.
//!
//! @param ui32Interrupt - Interrupt bits to clear.
//!
//! This function clears the desired interrupts.
//!
//! ui32Interrupt should be a logical or of the following:
//!
//!     AM_HAL_UART_INT_OVER_RUN
//!     AM_HAL_UART_INT_BREAK_ERR
//!     AM_HAL_UART_INT_PARITY_ERR
//!     AM_HAL_UART_INT_FRAME_ERR
//!     AM_HAL_UART_INT_RX_TMOUT
//!     AM_HAL_UART_INT_TX
//!     AM_REG_UART_IER_TXIM_M
//!     AM_HAL_UART_INT_RX
//!     AM_HAL_UART_INT_DSRM
//!     AM_HAL_UART_INT_DCDM
//!     AM_HAL_UART_INT_CTSM
//!     AM_HAL_UART_INT_RIM
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_uart_int_clear(uint32_t ui32Module, uint32_t ui32Interrupt)
{
    //
    // Clear the bits.
    //
    AM_REGn(UART, ui32Module, IEC) = ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Disables the desired interrupts.
//!
//! @param ui32Interrupt - Interrupt bits to disable.
//!
//! This function disables the desired interrupts.
//!
//! ui32Interrupt should be a logical or of the following:
//!
//!     AM_HAL_UART_INT_OVER_RUN
//!     AM_HAL_UART_INT_BREAK_ERR
//!     AM_HAL_UART_INT_PARITY_ERR
//!     AM_HAL_UART_INT_FRAME_ERR
//!     AM_HAL_UART_INT_RX_TMOUT
//!     AM_HAL_UART_INT_TX
//!     AM_REG_UART_IER_TXIM_M
//!     AM_HAL_UART_INT_RX
//!     AM_HAL_UART_INT_DSRM
//!     AM_HAL_UART_INT_DCDM
//!     AM_HAL_UART_INT_CTSM
//!     AM_HAL_UART_INT_RIM
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_uart_int_disable(uint32_t ui32Module, uint32_t ui32Interrupt)
{
    //
    // Disable the bits.
    //
    AM_REGn(UART, ui32Module, IER) &= ~ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Enables the desired interrupts.
//!
//! @param ui32Interrupt - Interrupt bits to enable.
//!
//! This function enables the desired interrupts.
//!
//! ui32Interrupt should be a logical or of the following:
//!
//!     AM_HAL_UART_INT_OVER_RUN
//!     AM_HAL_UART_INT_BREAK_ERR
//!     AM_HAL_UART_INT_PARITY_ERR
//!     AM_HAL_UART_INT_FRAME_ERR
//!     AM_HAL_UART_INT_RX_TMOUT
//!     AM_HAL_UART_INT_TX
//!     AM_REG_UART_IER_TXIM_M
//!     AM_HAL_UART_INT_RX
//!     AM_HAL_UART_INT_DSRM
//!     AM_HAL_UART_INT_DCDM
//!     AM_HAL_UART_INT_CTSM
//!     AM_HAL_UART_INT_RIM
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_uart_int_enable(uint32_t ui32Module, uint32_t ui32Interrupt)
{
    //
    // Enable the interrupts.
    //
    AM_REGn(UART, ui32Module, IER) |= ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Returns the enabled interrupts.
//!
//! This function return the enabled interrupts.
//!
//! @return the enabled interrupts. This will be a logical or of the following:
//!
//!     AM_HAL_UART_INT_OVER_RUN
//!     AM_HAL_UART_INT_BREAK_ERR
//!     AM_HAL_UART_INT_PARITY_ERR
//!     AM_HAL_UART_INT_FRAME_ERR
//!     AM_HAL_UART_INT_RX_TMOUT
//!     AM_HAL_UART_INT_TX
//!     AM_REG_UART_IER_TXIM_M
//!     AM_HAL_UART_INT_RX
//!     AM_HAL_UART_INT_DSRM
//!     AM_HAL_UART_INT_DCDM
//!     AM_HAL_UART_INT_CTSM
//!     AM_HAL_UART_INT_RIM
//!
//! @return Returns the enabled interrupts.
//
//*****************************************************************************
uint32_t
am_hal_uart_int_enable_get(uint32_t ui32Module)
{
    //
    // Return the enabled interrupts.
    //
    return AM_REGn(UART, ui32Module, IER);
}

//*****************************************************************************
//
//! @brief Enable the UART, RX, and TX.
//!
//! This function enables the UART, RX, and TX.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_uart_enable(uint32_t ui32Module)
{
    //
    // Enable the UART, RX, and TX.
    //
    AM_REGan_SET(UART, ui32Module, CR, (AM_REG_UART_CR_UARTEN_M   |
                                        AM_REG_UART_CR_RXE_M      |
                                        AM_REG_UART_CR_TXE_M) );
}

//*****************************************************************************
//
//! @brief Disable the UART, RX, and TX.
//!
//! This function disables the UART, RX, and TX.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_uart_disable(uint32_t ui32Module)
{
    //
    // Disable the UART.
    //
    AM_REGan_CLR(UART, ui32Module, CR, (AM_REG_UART_CR_UARTEN_M   |
                                        AM_REG_UART_CR_RXE_M      |
                                        AM_REG_UART_CR_TXE_M) );
}

//*****************************************************************************
//
//! @brief Enable the UART in the power control block.
//!
//! This function enables the UART device in the power control block.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_uart_pwrctrl_enable(uint32_t ui32Module)
{
    //
    // Check to make sure we're acting on a real UART module.
    //
    am_hal_debug_assert_msg(ui32Module < AM_REG_UART_NUM_MODULES,
                            "Trying to disable a UART module that doesn't exist");

    am_hal_pwrctrl_periph_enable(AM_HAL_PWRCTRL_UART0 << ui32Module);
}

//*****************************************************************************
//
//! @brief Disable the UART in the power control block.
//!
//! This function disables the UART device in the power control block.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_uart_pwrctrl_disable(uint32_t ui32Module)
{
    //
    // Check to make sure we're acting on a real UART module.
    //
    am_hal_debug_assert_msg(ui32Module < AM_REG_UART_NUM_MODULES,
                            "Trying to disable a UART module that doesn't exist");

    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_UART0 << ui32Module);
}

//*****************************************************************************
//
//! @brief Enable the UART in the power control block.
//!
//! This function enables the UART device in the power control block.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_uart_power_on_restore(uint32_t ui32Module)
{
    //
    // Check to make sure we're acting on a real UART module.
    //
    am_hal_debug_assert_msg(ui32Module < AM_REG_UART_NUM_MODULES,
                            "Trying to enable a UART module that doesn't exist");

    //
    // Make sure this restore is a companion to a previous save call.
    //
    if ( am_hal_uart_pwrsave[ui32Module].bValid == 0 )
    {
        return;
    }

    //
    // Enable power to the selected UART
    //
    am_hal_pwrctrl_periph_enable(AM_HAL_PWRCTRL_UART0 << ui32Module);

    //
    // Restore the clock settings
    //
    am_hal_clkgen_uarten_set(ui32Module, am_hal_uart_pwrsave[ui32Module].UARTEN);

    //
    // Restore the configuration registers from the global variable in SRAM.
    //
    AM_REGn(UART, ui32Module, ILPR) = am_hal_uart_pwrsave[ui32Module].ILPR;
    AM_REGn(UART, ui32Module, IBRD) = am_hal_uart_pwrsave[ui32Module].IBRD;
    AM_REGn(UART, ui32Module, FBRD) = am_hal_uart_pwrsave[ui32Module].FBRD;
    AM_REGn(UART, ui32Module, LCRH) = am_hal_uart_pwrsave[ui32Module].LCRH;
    AM_REGn(UART, ui32Module, CR)   = am_hal_uart_pwrsave[ui32Module].CR;
    AM_REGn(UART, ui32Module, IFLS) = am_hal_uart_pwrsave[ui32Module].IFLS;
    AM_REGn(UART, ui32Module, IER)  = am_hal_uart_pwrsave[ui32Module].IER;

    //
    // Indicates we have restored the configuration.
    //
    am_hal_uart_pwrsave[ui32Module].bValid = 0;

    return;
}

//*****************************************************************************
//
//! @brief Disable the UART in the power control block.
//!
//! This function disables the UART device in the power control block.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_uart_power_off_save(uint32_t ui32Module)
{
    //
    // Check to make sure we're acting on a real UART module.
    //
    am_hal_debug_assert_msg(ui32Module < AM_REG_UART_NUM_MODULES,
                            "Trying to disable a UART module that doesn't exist");

    //
    // Save all of the configuration register information for the selected
    // UART.
    //
    am_hal_uart_pwrsave[ui32Module].ILPR = AM_REGn(UART, ui32Module, ILPR);
    am_hal_uart_pwrsave[ui32Module].IBRD = AM_REGn(UART, ui32Module, IBRD);
    am_hal_uart_pwrsave[ui32Module].FBRD = AM_REGn(UART, ui32Module, FBRD);
    am_hal_uart_pwrsave[ui32Module].LCRH = AM_REGn(UART, ui32Module, LCRH);
    am_hal_uart_pwrsave[ui32Module].CR = AM_REGn(UART, ui32Module, CR);
    am_hal_uart_pwrsave[ui32Module].IFLS = AM_REGn(UART, ui32Module, IFLS);
    am_hal_uart_pwrsave[ui32Module].IER = AM_REGn(UART, ui32Module, IER);

    //
    // Save the clock setting and disable power to the selected UART.
    // Save the current enable value.
    //
    am_hal_uart_pwrsave[ui32Module].UARTEN =
        (AM_REG(CLKGEN, UARTEN) & AM_HAL_CLKGEN_UARTEN_UARTENn_M(ui32Module)) >>
         AM_HAL_CLKGEN_UARTEN_UARTENn_S(ui32Module);

    //
    // Disable the UART.
    //
    am_hal_clkgen_uarten_set(ui32Module, AM_HAL_CLKGEN_UARTEN_DIS);

    //
    // Indicates we have a valid saved configuration.
    //
    am_hal_uart_pwrsave[ui32Module].bValid = 1;

    //
    // Disable power to the selected UART.
    //
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_UART0 << ui32Module);

    return;
}

//*****************************************************************************
//
//! @brief Enable the UART clock.
//!
//! This function enables the clock to the UART.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_uart_clock_enable(uint32_t ui32Module)
{
    //
    // Set CLKGEN.UARTEN, clear the field then write the desired enable value
    // Valid enable values are DIS, EN, REDUCE_FREQ, EN_POWER_SAV.
    //
    am_hal_clkgen_uarten_set(ui32Module, AM_HAL_CLKGEN_UARTEN_EN);

    //
    // Enable the UART clock.
    //
    AM_REGn(UART, ui32Module, CR) |= AM_REG_UART_CR_CLKEN_M;

    //
    // Select default UART clock source
    //
    AM_REGn(UART, ui32Module, CR) |= AM_REG_UART_CR_CLKSEL_24MHZ;
}

//*****************************************************************************
//
//! @brief Disable the UART clock.
//!
//! This function disables the clock to the UART.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_uart_clock_disable(uint32_t ui32Module)
{
    //
    // Disable the UART clock.
    //
    AM_REGn(UART, ui32Module, CR) &= ~AM_REG_UART_CR_CLKEN_M;

    //
    // Disable the UART clock in the CLKGEN module.
    //
    am_hal_clkgen_uarten_set(ui32Module, AM_HAL_CLKGEN_UARTEN_DIS);
}

//*****************************************************************************
//
//! @brief Set and enable the desired interrupt levels for the RX/TX fifo.
//!
//! @param ui32LvlCfg - Desired FIFO RX/TX levels.
//!
//! This function sets the desired interrupt levels for the RX/TX fifo and
//! enables the use of transmit and receive FIFO buffers.
//!
//! Valid values for ui32LvlCfg are:
//!
//!     AM_HAL_UART_TX_FIFO_1_8
//!     AM_HAL_UART_TX_FIFO_1_4
//!     AM_HAL_UART_TX_FIFO_1_2
//!     AM_HAL_UART_TX_FIFO_3_4
//!     AM_HAL_UART_TX_FIFO_7_8
//!
//!     AM_HAL_UART_RX_FIFO_1_8
//!     AM_HAL_UART_RX_FIFO_1_4
//!     AM_HAL_UART_RX_FIFO_1_2
//!     AM_HAL_UART_RX_FIFO_3_4
//!     AM_HAL_UART_RX_FIFO_7_8
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_uart_fifo_config(uint32_t ui32Module, uint32_t ui32LvlCfg)
{
    //
    // Enable the use of FIFOs.
    //
    AM_REGn(UART, ui32Module, LCRH) |= AM_REG_UART_LCRH_FEN_M;

    //
    // Write the FIFO level register.
    //
    AM_REGn(UART, ui32Module, IFLS) = ui32LvlCfg;
}

//*****************************************************************************
//
//! @brief Return the UART Flags.
//!
//! This function reads and returns the UART flags.
//!
//! @return Returns the Flags.
//
//*****************************************************************************
uint32_t
am_hal_uart_flags_get(uint32_t ui32Module)
{
    //
    // Read and return the Flags.
    //
    return AM_REGn(UART, ui32Module, FR);
}

//*****************************************************************************
//
//! @brief Outputs a single character using polling.
//!
//! @param cChar - Character to send.
//!
//! This function outputs a single character using polling.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_uart_char_transmit_polled(uint32_t ui32Module, char cChar)
{
    //
    // Wait for space, i.e.  TX FIFO EMPTY
    //
    while (AM_BFRn(UART, ui32Module, FR, TXFF));

    //
    // Write the char.
    //
    AM_REGn(UART, ui32Module, DR) = cChar;
}

//*****************************************************************************
//
//! @brief Outputs a zero terminated string using polling.
//!
//! @param pcString - Pointer to character string to send.
//!
//! This function outputs a zero terminated string using polling.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_uart_string_transmit_polled(uint32_t ui32Module, char *pcString)
{
    while (*pcString)
    {
        //
        // Wait for space, i.e.  TX FIFO EMPTY.
        //
        while (AM_BFRn(UART, ui32Module, FR, TXFF));

        //
        // Write the char.
        //
        AM_REGn(UART, ui32Module, DR) = *pcString++;
    }
}

//*****************************************************************************
//
//! @brief Receives a character using polling.
//!
//! @param pcChar - Pointer to character to store received char.
//!
//! This function receives a character using polling.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_uart_char_receive_polled(uint32_t ui32Module, char *pcChar)
{
    //
    // Wait for data, i.e. RX FIFO NOT EMPTY.
    //
    while (AM_BFRn(UART, ui32Module, FR, RXFE));

    //
    // Save the char.
    //
    *pcChar = AM_REGn(UART, ui32Module, DR);
}

//*****************************************************************************
//
//! @brief Receives one line using polling.
//!
//! @param ui32MaxChars - Maximum number of characters to receive.
//! @param pcChar - Pointer to character string to store received line.
//!
//! This function receives a line (delimited by '/n' or '/r') using polling.
//! Line buffer is 0 (NULL) terminated.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_uart_line_receive_polled(uint32_t ui32Module,
                                uint32_t ui32MaxChars,
                                char *pcChar)
{
    char cRecChar;
    uint32_t i;

    //
    // Loop until we receive ui32MaxChars or receive a line ending.
    //
    for (i = 0; i < (ui32MaxChars - 1); i++)
    {
        //
        // Get char.
        //
        am_hal_uart_char_receive_polled(ui32Module, &cRecChar);

        if ((cRecChar == '\n') || (cRecChar == '\r'))
        {
            //
            // Zero terminate the buffer.
            //
            *pcChar = 0;

            return;
        }

        *pcChar++ = cRecChar;
    }
}

//*****************************************************************************
//
//! @brief Initialize the buffered UART.
//!
//! @param pui8RxArray - Pointer to the RX buffer to fill.
//! @param ui32RxSize - size of RX buffer.
//! @param pui8TxArray - Pointer to the TX buffer to fill.
//! @param ui32TxSize - size of TX buffer.
//!
//! This function initializes the buffered UART.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_uart_init_buffered(uint32_t ui32Module,
                          uint8_t *pui8RxArray, uint32_t ui32RxSize,
                          uint8_t *pui8TxArray, uint32_t ui32TxSize)
{
    //
    // Enable the UART RX timeout interrupt.
    //
    AM_REGn(UART, ui32Module, IER) |= (AM_REG_UART_IES_RTRIS_M |
                                       AM_REG_UART_IES_TXRIS_M);

    //
    // Initialize the ring buffers.
    //
    am_hal_queue_init(&g_psTxQueue[ui32Module], pui8TxArray, 1, ui32TxSize);
    am_hal_queue_init(&g_psRxQueue[ui32Module], pui8RxArray, 1, ui32RxSize);
}

//*****************************************************************************
//
//! @brief Get the status of the buffered UART.
//!
//! @param pui32RxSize - Pointer to variable to return the Rx ring data size.
//! @param pui32TxSize - Pointer to variable to return the Tx ring data size.
//!
//! This function gets the status of the buffered UART.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_uart_get_status_buffered(uint32_t ui32Module,
                                uint32_t *pui32RxSize,
                                uint32_t *pui32TxSize)
{
    //
    // Return the current size of ring buffers.
    //
    if ( pui32RxSize )
    {
        *pui32RxSize = am_hal_queue_data_left(&g_psRxQueue[ui32Module]);
    }

    if ( pui32TxSize )
    {
        *pui32TxSize = am_hal_queue_data_left(&g_psTxQueue[ui32Module]);
    }
}


//*****************************************************************************
//
//! @brief Services the buffered UART.
//!
//! @param ui32Status is the contents of the UART interrupt status register.
//!
//! This function is responsible for servicing the buffered UART. Designed to
//! be called from the UART interrupt handler.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_uart_service_buffered(uint32_t ui32Module, uint32_t ui32Status)
{
    uint8_t ui8Character = '\x00';
    uint32_t ui32FifoEntry = 0;

    //
    // Check to see if we have filled the Rx FIFO past the configured limit, or
    // if we have an 'old' character or two sitting in the FIFO.
    //
    if (ui32Status & (AM_REG_UART_IES_RXRIS_M | AM_REG_UART_IES_RTRIS_M))
    {
        //
        // While there's stuff in the RX fifo....
        //
        while (!AM_BFRn(UART, ui32Module, FR, RXFE))
        {
            //
            // Read each character out one by one, and add it to the ring
            // buffer. This will start losing bytes if the fifo ever overflows.
            //
            ui32FifoEntry = AM_REGn(UART, ui32Module , DR);

            //
            // As long as no error bits were set, we should push this byte to
            // the FIFO.
            //
            if ( (ui32FifoEntry & 0xF00) == 0 )
            {
                ui8Character = ui32FifoEntry & 0xFF;
                am_hal_queue_item_add(&g_psRxQueue[ui32Module], &ui8Character, 1);
            }
        }
    }

    //
    // Check to see if our TX buffer has been recently emptied. If so, we
    // should refill it from the TX ring buffer.
    //
    if (ui32Status & AM_REG_UART_IES_TXRIS_M)
    {
        //
        // Keep refilling until the fifo is full, or the ring buffer is empty,
        // whichever happens first.
        //
        while (am_hal_queue_data_left(&g_psTxQueue[ui32Module]) &&
               !AM_BFRn(UART, ui32Module, FR, TXFF))
        {
            am_hal_queue_item_get(&g_psTxQueue[ui32Module], &ui8Character, 1);
            AM_REGn(UART, ui32Module , DR) = ui8Character;
        }
    }
}

//*****************************************************************************
//
//! @brief Services the buffered UART.
//!
//! @param ui32Status is the contents of the UART interrupt status register.
//!
//! This function is responsible for servicing the buffered UART. Designed to
//! be called from the UART interrupt handler.
//!
//! This function behaves exactly like am_hal_uart_service_buffered() \e except
//! it does not completely empty the RX FIFO on every interrupt event. Instead,
//! it will leave at least one byte behind until it receives a UART RX TIMEOUT
//! interrupt. If you use this service routine, you can treat the RX TIMEOUT
//! interrupt as a UART IDLE interrupt. Every time the UART RX line goes IDLE
//! for 32 consecutive bit-times you WILL receive a UART RX TIMEOUT interrupt.
//! This behavior is not guaranteed for am_hal_uart_service_buffered().
//!
//! @return None
//
//*****************************************************************************
void
am_hal_uart_service_buffered_timeout_save(uint32_t ui32Module, uint32_t ui32Status)
{
    uint8_t ui8Character = '\x00';
    uint32_t ui32Count = 0;
    uint32_t ui32FifoEntry = 0;

    //
    // Check to see if we have filled the Rx FIFO past the configured limit, or
    // if we have an 'old' character or two sitting in the FIFO.
    //
    if (ui32Status & (AM_REG_UART_IES_RXRIS_M | AM_REG_UART_IES_RTRIS_M))
    {
        //
        // Check to see what our FIFO configuration setting is.
        //
        uint32_t ui32FifoThreshold;
        uint32_t ui32FifoCfg = AM_BFMn(UART, ui32Module, IFLS, RXIFLSEL);

        //
        // Compute the number of bytes for receive interrupt from the FIFO level
        // register.
        //
        switch(ui32FifoCfg)
        {
            case AM_HAL_UART_RX_FIFO_1_8: ui32FifoThreshold = 4; break;
            case AM_HAL_UART_RX_FIFO_1_4: ui32FifoThreshold = 8; break;
            case AM_HAL_UART_RX_FIFO_1_2: ui32FifoThreshold = 16; break;
            case AM_HAL_UART_RX_FIFO_3_4: ui32FifoThreshold = 24; break;
            case AM_HAL_UART_RX_FIFO_7_8: ui32FifoThreshold = 28; break;
            default:
                ui32FifoThreshold = 32;
        }

        //
        // While there's stuff in the RX fifo....
        //
        while (!AM_BFRn(UART, ui32Module, FR, RXFE))
        {
            //
            // Read each character out one by one, and add it to the ring
            // buffer. This will start losing bytes if the fifo ever overflows.
            //
            ui32FifoEntry = AM_REGn(UART, ui32Module, DR);

            //
            // As long as no error bits were set, we should push this byte to
            // the FIFO.
            //
            if ( (ui32FifoEntry & 0xF00) == 0)
            {
                ui8Character = ui32FifoEntry & 0xFF;
                am_hal_queue_item_add(&g_psRxQueue[ui32Module], &ui8Character, 1);
            }

            //
            // Leave one byte to trigger the RX timeout interrupt.
            //
            if ( ++ui32Count >= (ui32FifoThreshold - 1) )
            {
                break;
            }
        }
    }

    //
    // Check to see if our TX buffer has been recently emptied. If so, we
    // should refill it from the TX ring buffer.
    //
    if (ui32Status & AM_REG_UART_IES_TXRIS_M)
    {
        //
        // Keep refilling until the fifo is full, or the ring buffer is empty,
        // whichever happens first.
        //
        while (am_hal_queue_data_left(&g_psTxQueue[ui32Module]) &&
               !AM_BFRn(UART, ui32Module, FR, TXFF))
        {
            am_hal_queue_item_get(&g_psTxQueue[ui32Module], &ui8Character, 1);
            AM_REGn(UART, ui32Module , DR) = ui8Character;
        }
    }
}

//*****************************************************************************
//
//! @brief Puts a char in the buffer or directly to the fifo if available.
//!
//! @param cChar - Character to send.
//!
//! This function puts a character in the buffer or directly to the fifo.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_uart_char_transmit_buffered(uint32_t ui32Module, char cChar)
{
    //
    // Check the status of the Tx fifo and the Tx ring buffer.
    //
    if (am_hal_queue_empty(&g_psTxQueue[ui32Module]) &&
        !AM_BFRn(UART, ui32Module, FR, TXFF))
    {
        //
        // If the fifo isn't full yet, and the ring buffer isn't being used,
        // just write the new character directly to the fifo.
        //
        AM_REGn(UART, ui32Module, DR) = cChar;
    }
    else
    {
        //
        // If we get here, either the fifo is full, or the ring buffer is
        // already in use. In either case, we need to use the ring buffer
        // to make sure that the transmitted data gets sent in the right
        // order. If the buffer is already full, we will simply lose this
        // byte.
        //
        am_hal_queue_item_add(&g_psTxQueue[ui32Module], &cChar, 1);
    }
}

//*****************************************************************************
//
//! @brief Puts a null terminaled string in the buffer or directly to the fifo.
//!
//! @param pcString - Pointer to buffer used for sending.
//!
//! This function puts a string in the buffer or directly to the fifo if there
//! is space available.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_uart_string_transmit_buffered(uint32_t ui32Module, char *pcString)
{
    //
    // Check the status of the Tx fifo and the Tx ring buffer.
    //
    while (*pcString)
    {
        if (am_hal_queue_empty(&g_psTxQueue[ui32Module]) &&
            !AM_BFRn(UART, ui32Module, FR, TXFF))
        {
            //
            // If the fifo isn't full yet, and the ring buffer isn't being used,
            // just write the new character directly to the fifo.
            //
            AM_REGn(UART, ui32Module, DR) = *pcString;
        }
        else
        {
            //
            // If we get here, either the fifo is full, or the ring buffer is
            // already in use. In either case, we need to use the ring buffer
            // to make sure that the transmitted data gets sent in the right
            // order. If the buffer is already full, we will simply lose this
            // byte.
            //
            am_hal_queue_item_add(&g_psTxQueue[ui32Module], pcString, 1);
        }

        //
        // Move the pointer to the next character.
        //
        pcString++;
    }
}

//*****************************************************************************
//
//! @brief Returns n number of characters from the ring buffer or until empty.
//!
//! @param pcString - Pointer to buffer for putting received characters.
//! @param ui32MaxChars - Maximum number of characters to receive.
//!
//! This function puts a char string in the buffer.
//!
//! @return Returns the number of chars received.
//
//*****************************************************************************
uint32_t
am_hal_uart_char_receive_buffered(uint32_t ui32Module,
                                  char *pcString,
                                  uint32_t ui32MaxChars)
{
    uint32_t ui32NumChars = 0;

    //
    // Loop until ui32MaxChars or until empty.
    //
    while (am_hal_queue_data_left(&g_psRxQueue[ui32Module]) && ui32MaxChars)
    {
        //
        // Pull a char out of the ring buffer.
        //
        am_hal_queue_item_get(&g_psRxQueue[ui32Module], pcString, 1);

        //
        // Subtract from ui32MaxChars.
        // Add to ui32NumChars.
        // Move pointer in buffer.
        //
        ui32MaxChars--;
        ui32NumChars++;
        pcString++;
    }

    //
    // return the number of chars received.
    //
    return ui32NumChars;
}

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
