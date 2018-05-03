//*****************************************************************************
//
// sdram.c - Example demonstrating how to configure the EPI bus in SDRAM
// mode.
//
// Copyright (c) 2010 Texas Instruments Incorporated.  All rights reserved.
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
// This is part of revision 5961 of the Stellaris Firmware Development Package.
//
//*****************************************************************************

#include <rthw.h>
#include <rtthread.h>
#include <board.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_epi.h"
#include "inc/hw_gpio.h"
#include "driverlib/epi.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

//*****************************************************************************
//
//! \addtogroup epi_examples_list
//! <h1>EPI SDRAM Mode (sdram)</h1>
//!
//! This example shows how to configure the EPI bus in SDRAM mode.  This
//! example has been written to be compatible with the Texas Instruments 8MB
//! SDRAM expansion card for the DK-LM3S9B96.
//!
//! For the EPI SDRAM mode, the pinout is as follows:
//!     Address11:0 - EPI0S11:0
//!     Bank1:0     - EPI0S14:13
//!     Data15:0    - EPI0S15:0
//!     DQML        - EPI0S16
//!     DQMH        - EPI0S17
//!     /CAS        - EPI0S18
//!     /RAS        - EPI0S19
//!     /WE         - EPI0S28
//!     /CS         - EPI0S29
//!     SDCKE       - EPI0S30
//!     SDCLK       - EPI0S31
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - EPI0 peripheral
//! - GPIO Port C peripheral (for EPI0 pins)
//! - GPIO Port E peripheral (for EPI0 pins)
//! - GPIO Port F peripheral (for EPI0 pins)
//! - GPIO Port G peripheral (for EPI0 pins)
//! - GPIO Port H peripheral (for EPI0 pins)
//! - GPIO Port J peripheral (for EPI0 pins)
//! - EPI0S0 - PH3
//! - EPI0S1 - PH2
//! - EPI0S2 - PC4
//! - EPI0S3 - PC5
//! - EPI0S4 - PC6
//! - EPI0S5 - PC7
//! - EPI0S6 - PH0
//! - EPI0S7 - PH1
//! - EPI0S8 - PE0
//! - EPI0S9 - PE1
//! - EPI0S10 - PH4
//! - EPI0S11 - PH5
//! - EPI0S12 - PF4
//! - EPI0S13 - PG0
//! - EPI0S14 - PG1
//! - EPI0S15 - PF5
//! - EPI0S16 - PJ0
//! - EPI0S17 - PJ1
//! - EPI0S18 - PJ2
//! - EPI0S19 - PJ3
//! - EPI0S28 - PJ4
//! - EPI0S29 - PJ5
//! - EPI0S30 - PJ6
//! - EPI0S31 - PG7
//!
//! The following UART signals are configured only for displaying console
//! messages for this example.  These are not required for operation of EPI0.
//! - UART0 peripheral
//! - GPIO Port A peripheral (for UART0 pins)
//! - UART0RX - PA0
//! - UART0TX - PA1
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - None.
//!
//
//*****************************************************************************

//*****************************************************************************
//
// Use the following to specify the GPIO pins used by the SDRAM EPI bus.
//
//*****************************************************************************
#define EPI_PORTC_PINS (GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_5 | GPIO_PIN_4)
#define EPI_PORTE_PINS (GPIO_PIN_1 | GPIO_PIN_0)
#define EPI_PORTF_PINS (GPIO_PIN_5 | GPIO_PIN_4)
#define EPI_PORTG_PINS (GPIO_PIN_7 | GPIO_PIN_1 | GPIO_PIN_0)
#define EPI_PORTH_PINS (GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2 | \
                        GPIO_PIN_1 | GPIO_PIN_0)
#define EPI_PORTJ_PINS (GPIO_PIN_6 | GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 | \
                        GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0)

//*****************************************************************************
//
// The starting and ending address for the 8MB SDRAM chip (4Meg x 16bits) on
// the SDRAM daughter board.
//
//*****************************************************************************
#define SDRAM_START_ADDRESS 0x000000
#define SDRAM_END_ADDRESS 0x3FFFFF

//*****************************************************************************
//

//*****************************************************************************
//
// Configure EPI0 in SDRAM mode.  The EPI memory space is setup using an a
// simple C array.  This example shows how to read and write to an SDRAM card
// using the EPI bus in SDRAM mode.
//
//*****************************************************************************
void rt_hw_sdram_init(void)
{
    //
    // The EPI0 peripheral must be enabled for use.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EPI0);

    //
    // For this example EPI0 is used with multiple pins on PortC, E, F, G, H,
    // and J.  The actual port and pins used may be different on your part,
    // consult the data sheet for more information.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);

    //
    // This step configures the internal pin muxes to set the EPI pins for use
    // with EPI.  This step is only required because the default function of
    // these pins may not be to function in EPI mode.  Please reference the
    // datasheet for more information about pin muxing.  Note that EPI0S27:20
    // are not used for the EPI SDRAM implementation.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PH3_EPI0S0);
    GPIOPinConfigure(GPIO_PH2_EPI0S1);
    GPIOPinConfigure(GPIO_PC4_EPI0S2);
    GPIOPinConfigure(GPIO_PC5_EPI0S3);
    GPIOPinConfigure(GPIO_PC6_EPI0S4);
    GPIOPinConfigure(GPIO_PC7_EPI0S5);
    GPIOPinConfigure(GPIO_PH0_EPI0S6);
    GPIOPinConfigure(GPIO_PH1_EPI0S7);
    GPIOPinConfigure(GPIO_PE0_EPI0S8);
    GPIOPinConfigure(GPIO_PE1_EPI0S9);
    GPIOPinConfigure(GPIO_PH4_EPI0S10);
    GPIOPinConfigure(GPIO_PH5_EPI0S11);
    GPIOPinConfigure(GPIO_PF4_EPI0S12);
    GPIOPinConfigure(GPIO_PG0_EPI0S13);
    GPIOPinConfigure(GPIO_PG1_EPI0S14);
    GPIOPinConfigure(GPIO_PF5_EPI0S15);
    GPIOPinConfigure(GPIO_PJ0_EPI0S16);
    GPIOPinConfigure(GPIO_PJ1_EPI0S17);
    GPIOPinConfigure(GPIO_PJ2_EPI0S18);
    GPIOPinConfigure(GPIO_PJ3_EPI0S19);
    GPIOPinConfigure(GPIO_PJ4_EPI0S28);
    GPIOPinConfigure(GPIO_PJ5_EPI0S29);
    GPIOPinConfigure(GPIO_PJ6_EPI0S30);
    GPIOPinConfigure(GPIO_PG7_EPI0S31);

    //
    // Configure the GPIO pins for EPI mode.  All the EPI pins require 8mA
    // drive strength in push-pull operation.  This step also gives control of
    // pins to the EPI module.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeEPI(GPIO_PORTC_BASE, EPI_PORTC_PINS);
    GPIOPinTypeEPI(GPIO_PORTE_BASE, EPI_PORTE_PINS);
    GPIOPinTypeEPI(GPIO_PORTF_BASE, EPI_PORTF_PINS);
    GPIOPinTypeEPI(GPIO_PORTG_BASE, EPI_PORTG_PINS);
    GPIOPinTypeEPI(GPIO_PORTH_BASE, EPI_PORTH_PINS);
    GPIOPinTypeEPI(GPIO_PORTJ_BASE, EPI_PORTJ_PINS);

    //
    // Sets the clock divider for the EPI module.  In this case set the
    // divider to 0, making the EPIClock = SysClk.
    //
    EPIDividerSet(EPI0_BASE, 1);

    //
    // Sets the usage mode of the EPI module.  For this example we will use
    // the SDRAM mode to talk to the external 8MB SDRAM daughter card.
    //
    EPIModeSet(EPI0_BASE, EPI_MODE_SDRAM);

    //
    // Configure the SDRAM mode.  We configure the SDRAM according to our core
    // clock frequency, in this case we are in the 15 MHz < clk <= 30 MHz
    // range (i.e 16Mhz crystal).  We will use the normal (or full power)
    // operating state which means we will not use the low power self-refresh
    // state.  Set the SDRAM size to 8MB (or 64Mb) with a refresh counter of
    // 1024 clock ticks.
    // TODO: change this to select the proper clock frequency and SDRAM
    // refresh counter.
    //
    EPIConfigSDRAMSet(EPI0_BASE, EPI_SDRAM_CORE_FREQ_15_30 |
                      EPI_SDRAM_FULL_POWER | EPI_SDRAM_SIZE_64MBIT, 1024);

    //
    // Set the address map.  The EPI0 is mapped from 0x60000000 to 0xCFFFFFFF.
    // For this example, we will start from a base address of 0x60000000 with
    // a size of 16MB.  We use 16MB so we have the ability to access the
    // entire 8MB SDRAM daughter card.  Since there is no 8MB option, so we
    // use the next closest one.  If you attempt to access an address higher
    // than 4Meg (since SDRAM mode uses 16-bit data, you have 4Meg of
    // of addresses by 16-bits of data) a fault will not occur since we
    // configured the EPI for 16MB addressability.  In the case that you do
    // access an address higher than 0x3FFFFF, the MSb of the address gets
    // ignored.
    //
    EPIAddressMapSet(EPI0_BASE, EPI_ADDR_RAM_SIZE_16MB | EPI_ADDR_RAM_BASE_6);

    //
    // Wait for the SDRAM wake-up to complete by polling the SDRAM
    // initialization sequence bit.  This bit is true when the SDRAM interface
    // is going through the initialization and false when the SDRAM interface
    // it is not in a wake-up period.
    //
    while(HWREG(EPI0_BASE + EPI_O_STAT) &  EPI_STAT_INITSEQ)
    {
    }
}
