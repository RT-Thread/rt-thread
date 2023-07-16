//*****************************************************************************
//
// bl_autobaud.c - Automatic baud rate detection code.
//
// Copyright (c) 2006-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
//*****************************************************************************

#include <stdint.h>
#include "bl_config.h"
#include "ti/devices/msp432e4/inc/msp.h"
#include "ti/devices/msp432e4/boot_loader/bl_uart.h"

//*****************************************************************************
//
// If using auto-baud, make sure that the data buffer is large enough.
//
//*****************************************************************************
#if defined(UART_ENABLE_UPDATE) && defined(UART_AUTOBAUD) && (BUFFER_SIZE < 20)
#error ERROR: BUFFER_SIZE must be >= 20!
#endif

//*****************************************************************************
//
//! \addtogroup bl_autobaud_api
//! @{
//
//*****************************************************************************
#if defined(UART_ENABLE_UPDATE) && defined(UART_AUTOBAUD) || defined(DOXYGEN)

//*****************************************************************************
//
// This define holds the multiplier for the pulse detection algorithm.  The
// value is used to generate a fractional difference detection of
// 1 / PULSE_DETECTION_MULT.
//
//*****************************************************************************
#define PULSE_DETECTION_MULT    3

//*****************************************************************************
//
// This define holds the minimum number of edges to successfully sync to a
// pattern of 2 bytes.
//
//*****************************************************************************
#define MIN_EDGE_COUNT          18

//*****************************************************************************
//
// This global holds the number of edges that have been stored in the global
// buffer g_pui32DataBuffer.
//
//*****************************************************************************
static volatile uint32_t g_ui32TickIndex;

//*****************************************************************************
//
// The data buffer that is used for receiving packets is used to hold the edge
// times during auto-baud.  The buffer is not used for receiving packets while
// auto-baud is in progress, so this does not present problems.
//
//*****************************************************************************
extern uint32_t g_pui32DataBuffer[];

//*****************************************************************************
//
//! Handles the UART Rx GPIO interrupt.
//!
//! When an edge is detected on the UART Rx pin, this function is called to
//! save the time of the edge.  These times are later used to determine the
//! ratio of the UART baud rate to the processor clock rate.
//!
//! \return None.
//
//*****************************************************************************
void
GPIOIntHandler(void)
{
    uint32_t ui32Temp;

    //
    // Clear the GPIO interrupt source.
    //
    UART_RXPIN_BASE->ICR = UART_RX;

    //
    // While we still have space in our buffer, store the current system tick
    // count and return from interrupt.
    //
    if(g_ui32TickIndex < 20)
    {
        ui32Temp = SysTick->VAL;
        g_pui32DataBuffer[g_ui32TickIndex++] = ui32Temp;
    }
}

//*****************************************************************************
//
//! Performs auto-baud on the UART port.
//!
//! \param pui32Ratio is the ratio of the processor's crystal frequency to the
//! baud rate being used by the UART port for communications.
//!
//! This function attempts to synchronize to the updater program that is trying
//! to communicate with the boot loader.  The UART port is monitored for edges
//! using interrupts.  Once enough edges are detected, the boot loader
//! determines the ratio of baud rate and crystal frequency needed to program
//! the UART.
//!
//! \return Returns a value of 0 to indicate that this call successfully
//! synchronized with the other device communicating over the UART, and a
//! negative value to indicate that this function did not successfully
//! synchronize with the other UART device.
//
//*****************************************************************************
int
UARTAutoBaud(uint32_t *pui32Ratio)
{
    int32_t i32Pulse, i32ValidPulses, i32Temp, i32Total;
    volatile int32_t i32Delay;

    //
    // Configure and enable SysTick.  Set the reload value to the maximum;
    // there are only 24 bits in the register but loading 32 bits of ones is
    // more efficient.
    //
    SysTick->LOAD = 0xffffffff;
    SysTick->CTRL = NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_ENABLE;

    //
    // Reset the counters that control the pulse detection.
    //
    i32ValidPulses = 0;
    i32Total = 0;
    g_ui32TickIndex = 0;

    //
    // Set the pad(s) for standard push-pull operation.
    //
    UART_RXPIN_BASE->PUR |= UART_RX;
    UART_RXPIN_BASE->DEN |= UART_RX;

    //
    // Interrupt on both edges.
    //
    UART_RXPIN_BASE->IBE = UART_RX;

    //
    // Clear out all of the gpio interrupts in this register.
    //
    UART_RXPIN_BASE->ICR = UART_RX;

    //
    // Enable the GPIO pin corresponding to the UART RX pin.
    //
    UART_RXPIN_BASE->IM = UART_RX;

    //
    // Enable GPIOA Interrupt.
    //
    NVIC->ISER[0] = (1 << GPIOA_IRQn);

    //
    // Wait for MIN_EDGE_COUNT to pass to collect enough edges.
    //
    while(g_ui32TickIndex < MIN_EDGE_COUNT)
    {
    }

    //
    // Disable GPIOA Interrupt.
    //
    NVIC->ICER[0] = (1 << GPIOA_IRQn);

    //
    // Calculate the pulse widths from the array of tick times.
    //
    for(i32Pulse = 0; i32Pulse < (MIN_EDGE_COUNT - 1); i32Pulse++)
    {
        i32Temp = (((int32_t)g_pui32DataBuffer[i32Pulse] -
                    (int32_t)g_pui32DataBuffer[i32Pulse + 1]) & 0x00ffffff);
        g_pui32DataBuffer[i32Pulse] = i32Temp;
    }

    //
    // This loops handles checking for consecutive pulses that have pulse
    // widths that are within an acceptable margin.
    //
    for(i32Pulse = 0; i32Pulse < (MIN_EDGE_COUNT - 1); i32Pulse++)
    {
        //
        // Calculate the absolute difference between two consecutive pulses.
        //
        i32Temp = (int32_t)g_pui32DataBuffer[i32Pulse];
        i32Temp -= (int32_t)g_pui32DataBuffer[i32Pulse + 1];
        if(i32Temp < 0)
        {
            i32Temp *= -1;
        }

        //
        // This pulse detection code uses the following algorithm:
        // If the following is true then we have consecutive acceptable pulses
        // abs(Pulse[n] - Pulse[n + 1]) < Pulse[n + 1] / PULSE_DETECTION_MULT
        // or
        // PULSE_DETECTION_MULT * abs(Pulse[n] - Pulse[n + 1]) < Pulse[n + 1]
        //
        if((i32Temp * PULSE_DETECTION_MULT) <
           (int32_t)g_pui32DataBuffer[i32Pulse + 1])
        {
            i32Total += (int32_t)g_pui32DataBuffer[i32Pulse];
            i32ValidPulses++;
        }
        else
        {
            i32ValidPulses = 0;
            i32Total = 0;
        }

        //
        // Once we have 7 pulses calculate the ratio needed to program the
        // UART.
        //
        if(i32ValidPulses == 7)
        {
            //
            // Add in the last pulse and calculate the ratio.
            //
            i32Total += (int32_t)g_pui32DataBuffer[i32Pulse];
            *pui32Ratio = i32Total >> 1;

            //
            // Wait for at least 2 UART clocks since we only wait for 18 of 20
            // that are coming from the host.  If we don't wait, we can turn
            // on the UART while the last two pulses come down.
            //
            for(i32Delay = i32Total; i32Delay; i32Delay--)
            {
            }

            //
            // Indicate a successful auto baud operation.
            //
            return(0);
        }
    }

    //
    // Automatic baud rate detection failed.
    //
    return(-1);
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
#endif
