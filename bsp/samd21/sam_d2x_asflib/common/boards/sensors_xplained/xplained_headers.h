/**
 * \file
 *
 * \brief Xplained I/O Expansion Header Pin Mapping
 *
 * The Atmel Xplained evaluation boards have four 10-pin, 100mil headers that
 * are used to access spare analog and digital pins on the board
 * microcontroller.  This file provides a common set of definitions mapping
 * the Xplained expansion header \c J1, \c J2, \c J3, and \c J4 pins to spare
 * pins on the board microcontroller.  Software can then use these common
 * definitions to configure I/O for peripherals and expansion boards connected
 * to the Xplained header blocks.
 *
 * For each board type, the pin definitions are specified for the pins in
 * each of the four headers.  For UC3 based boards, if a pin can be used as
 * an external interrupt source, the interrupt and GPIO pin mapping settings
 * that are needed for initializing the external interrupt controller (EIC)
 * are also provided.
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef _xplained_headers_h_
#define _xplained_headers_h_

#include <board.h>
#include <gpio.h>

#ifdef __cplusplus
extern "C" {
#endif


#define INVALID_PIN_NUMBER              ((unsigned int) -1)


//! \name Xplained I/O Expansion Header Pin Mapping
// @{
#if (BOARD == UC3_A3_XPLAINED)
#   define XPLD_HEADER_J1_PIN1          (AVR32_PIN_PA25)
#   define XPLD_HEADER_J1_PIN2          (AVR32_PIN_PA26)
#   define XPLD_HEADER_J1_PIN3          (AVR32_PIN_PX57)
#   define XPLD_HEADER_J1_PIN4          (AVR32_PIN_PX58)
#   define XPLD_HEADER_J1_PIN5          (AVR32_PIN_PB09)
#   define XPLD_HEADER_J1_PIN6          (AVR32_PIN_PB10)
#   define XPLD_HEADER_J1_PIN7          (AVR32_PIN_PB08)
#   define XPLD_HEADER_J1_PIN8          (AVR32_PIN_PB07)

#   define XPLD_HEADER_J2_PIN1          (AVR32_PIN_PA21)
#   define XPLD_HEADER_J2_PIN2          (AVR32_PIN_PA22)
#   define XPLD_HEADER_J2_PIN3          (AVR32_PIN_PA23)
#   define XPLD_HEADER_J2_PIN4          (AVR32_PIN_PA24)
#   define XPLD_HEADER_J2_PIN5          (AVR32_PIN_PA20)
#   define XPLD_HEADER_J2_PIN6          (AVR32_PIN_PA19)
#   define XPLD_HEADER_J2_PIN7          (AVR32_PIN_PA18)
#   define XPLD_HEADER_J2_PIN8          (AVR32_PIN_PA17)

#   define XPLD_HEADER_J3_PIN1          (AVR32_PIN_PA31)
#   define XPLD_HEADER_J3_PIN2          (AVR32_PIN_PA30)
#   define XPLD_HEADER_J3_PIN3          (AVR32_PIN_PA29)
#   define XPLD_HEADER_J3_PIN4          (AVR32_PIN_PA28)
#   define XPLD_HEADER_J3_PIN5          (AVR32_PIN_PA27)
#   define XPLD_HEADER_J3_PIN6          (AVR32_PIN_PB00)
#   define XPLD_HEADER_J3_PIN7          (AVR32_PIN_PB04)
#   define XPLD_HEADER_J3_PIN8          (AVR32_PIN_PX19)

#   define XPLD_HEADER_J4_PIN1          (AVR32_PIN_PA15)
#   define XPLD_HEADER_J4_PIN2          (AVR32_PIN_PA14)
#   define XPLD_HEADER_J4_PIN3          (AVR32_PIN_PA05)
#   define XPLD_HEADER_J4_PIN4          (AVR32_PIN_PA06)
#   define XPLD_HEADER_J4_PIN5          (AVR32_PIN_PA07)
#   define XPLD_HEADER_J4_PIN6          (AVR32_PIN_PA10)
#   define XPLD_HEADER_J4_PIN7          (AVR32_PIN_PA11)
#   define XPLD_HEADER_J4_PIN8          (AVR32_PIN_PA08)

#elif (BOARD == UC3_L0_XPLAINED)
#   define XPLD_HEADER_J1_PIN1          (AVR32_PIN_PA21)
#   define XPLD_HEADER_J1_PIN2          (AVR32_PIN_PB05)
#   define XPLD_HEADER_J1_PIN3          (AVR32_PIN_PB11)
#   define XPLD_HEADER_J1_PIN4          (AVR32_PIN_PB10)
#   define XPLD_HEADER_J1_PIN5          (AVR32_PIN_PA08)
#   define XPLD_HEADER_J1_PIN6          (AVR32_PIN_PB03)
#   define XPLD_HEADER_J1_PIN7          (AVR32_PIN_PB02)
#   define XPLD_HEADER_J1_PIN8          (AVR32_PIN_PB01)

#   define XPLD_HEADER_J2_PIN1          (AVR32_PIN_PA14)
#   define XPLD_HEADER_J2_PIN2          (AVR32_PIN_PA15)
#   define XPLD_HEADER_J2_PIN3          (AVR32_PIN_PA16)
#   define XPLD_HEADER_J2_PIN4          (AVR32_PIN_PA18)
#   define XPLD_HEADER_J2_PIN5          (AVR32_PIN_PB07)
#   define XPLD_HEADER_J2_PIN6          (AVR32_PIN_PB08)
#   define XPLD_HEADER_J2_PIN7          (AVR32_PIN_PB06)
#   define XPLD_HEADER_J2_PIN8          (AVR32_PIN_PA19)

#   define XPLD_HEADER_J3_PIN1          (AVR32_PIN_PA13)
#   define XPLD_HEADER_J3_PIN2          (AVR32_PIN_PA17)
#   define XPLD_HEADER_J3_PIN3          (AVR32_PIN_PA20)
#   define XPLD_HEADER_J3_PIN4          (AVR32_PIN_PA22)
#   define XPLD_HEADER_J3_PIN5          (AVR32_PIN_PB12)
#   define XPLD_HEADER_J3_PIN6          (AVR32_PIN_PB09)
#   define XPLD_HEADER_J3_PIN7          (AVR32_PIN_PB04)
#   define XPLD_HEADER_J3_PIN8          (AVR32_PIN_PA11)

#   define XPLD_HEADER_J4_PIN1          (AVR32_PIN_PA21)
#   define XPLD_HEADER_J4_PIN2          (AVR32_PIN_PB05)
#   define XPLD_HEADER_J4_PIN3          (AVR32_PIN_PB11)
#   define XPLD_HEADER_J4_PIN4          (AVR32_PIN_PB10)
#   define XPLD_HEADER_J4_PIN5          (AVR32_PIN_PB00)
#   define XPLD_HEADER_J4_PIN6          (AVR32_PIN_PB03)
#   define XPLD_HEADER_J4_PIN7          (AVR32_PIN_PB02)
#   define XPLD_HEADER_J4_PIN8          (AVR32_PIN_PB01)

#elif (BOARD == XMEGA_A1_XPLAINED)
#   define XPLD_HEADER_J1_PIN1          IOPORT_CREATE_PIN(PORTF,0)
#   define XPLD_HEADER_J1_PIN2          IOPORT_CREATE_PIN(PORTF,1)
#   define XPLD_HEADER_J1_PIN3          IOPORT_CREATE_PIN(PORTF,2)
#   define XPLD_HEADER_J1_PIN4          IOPORT_CREATE_PIN(PORTF,3)
#   define XPLD_HEADER_J1_PIN5          IOPORT_CREATE_PIN(PORTF,4)
#   define XPLD_HEADER_J1_PIN6          IOPORT_CREATE_PIN(PORTF,5)
#   define XPLD_HEADER_J1_PIN7          IOPORT_CREATE_PIN(PORTF,6)
#   define XPLD_HEADER_J1_PIN8          IOPORT_CREATE_PIN(PORTF,7)

#   define XPLD_HEADER_J2_PIN1          IOPORT_CREATE_PIN(PORTA,0)
#   define XPLD_HEADER_J2_PIN2          IOPORT_CREATE_PIN(PORTA,1)
#   define XPLD_HEADER_J2_PIN3          IOPORT_CREATE_PIN(PORTA,2)
#   define XPLD_HEADER_J2_PIN4          IOPORT_CREATE_PIN(PORTA,3)
#   define XPLD_HEADER_J2_PIN5          IOPORT_CREATE_PIN(PORTA,4)
#   define XPLD_HEADER_J2_PIN6          IOPORT_CREATE_PIN(PORTA,5)
#   define XPLD_HEADER_J2_PIN7          IOPORT_CREATE_PIN(PORTA,6)
#   define XPLD_HEADER_J2_PIN8          IOPORT_CREATE_PIN(PORTA,7)

#   define XPLD_HEADER_J3_PIN1          IOPORT_CREATE_PIN(PORTD,0)
#   define XPLD_HEADER_J3_PIN2          IOPORT_CREATE_PIN(PORTD,1)
#   define XPLD_HEADER_J3_PIN3          IOPORT_CREATE_PIN(PORTD,2)
#   define XPLD_HEADER_J3_PIN4          IOPORT_CREATE_PIN(PORTD,3)
#   define XPLD_HEADER_J3_PIN5          IOPORT_CREATE_PIN(PORTD,4)
#   define XPLD_HEADER_J3_PIN6          IOPORT_CREATE_PIN(PORTD,5)
#   define XPLD_HEADER_J3_PIN7          IOPORT_CREATE_PIN(PORTR,0)
#   define XPLD_HEADER_J3_PIN8          IOPORT_CREATE_PIN(PORTR,1)

#   define XPLD_HEADER_J4_PIN1          IOPORT_CREATE_PIN(PORTC,0)
#   define XPLD_HEADER_J4_PIN2          IOPORT_CREATE_PIN(PORTC,1)
#   define XPLD_HEADER_J4_PIN3          IOPORT_CREATE_PIN(PORTC,2)
#   define XPLD_HEADER_J4_PIN4          IOPORT_CREATE_PIN(PORTC,3)
#   define XPLD_HEADER_J4_PIN5          IOPORT_CREATE_PIN(PORTC,4)
#   define XPLD_HEADER_J4_PIN6          IOPORT_CREATE_PIN(PORTC,5)
#   define XPLD_HEADER_J4_PIN7          IOPORT_CREATE_PIN(PORTC,6)
#   define XPLD_HEADER_J4_PIN8          IOPORT_CREATE_PIN(PORTC,7)

#elif (BOARD == XMEGA_B1_XPLAINED)
#   define XPLD_HEADER_J1_PIN1          IOPORT_CREATE_PIN(PORTC,0)
#   define XPLD_HEADER_J1_PIN2          IOPORT_CREATE_PIN(PORTC,1)
#   define XPLD_HEADER_J1_PIN3          IOPORT_CREATE_PIN(PORTC,2)
#   define XPLD_HEADER_J1_PIN4          IOPORT_CREATE_PIN(PORTC,3)
#   define XPLD_HEADER_J1_PIN5          IOPORT_CREATE_PIN(PORTC,4)
#   define XPLD_HEADER_J1_PIN6          IOPORT_CREATE_PIN(PORTC,5)
#   define XPLD_HEADER_J1_PIN7          IOPORT_CREATE_PIN(PORTC,6)
#   define XPLD_HEADER_J1_PIN8          IOPORT_CREATE_PIN(PORTC,7)

#   define XPLD_HEADER_J2_PIN1          IOPORT_CREATE_PIN(PORTA,0)
#   define XPLD_HEADER_J2_PIN2          IOPORT_CREATE_PIN(PORTA,1)
#   define XPLD_HEADER_J2_PIN3          IOPORT_CREATE_PIN(PORTA,2)
#   define XPLD_HEADER_J2_PIN4          IOPORT_CREATE_PIN(PORTA,3)
#   define XPLD_HEADER_J2_PIN5          IOPORT_CREATE_PIN(PORTA,4)
#   define XPLD_HEADER_J2_PIN6          IOPORT_CREATE_PIN(PORTA,5)
#   define XPLD_HEADER_J2_PIN7          IOPORT_CREATE_PIN(PORTA,6)
#   define XPLD_HEADER_J2_PIN8          IOPORT_CREATE_PIN(PORTA,7)

#   define XPLD_HEADER_J3_PIN1          IOPORT_CREATE_PIN(PORTB,0)
#   define XPLD_HEADER_J3_PIN2          IOPORT_CREATE_PIN(PORTB,1)
#   define XPLD_HEADER_J3_PIN3          IOPORT_CREATE_PIN(PORTB,2)
#   define XPLD_HEADER_J3_PIN4          IOPORT_CREATE_PIN(PORTB,3)
#   define XPLD_HEADER_J3_PIN5          IOPORT_CREATE_PIN(PORTB,4)
#   define XPLD_HEADER_J3_PIN6          IOPORT_CREATE_PIN(PORTB,5)
#   define XPLD_HEADER_J3_PIN7          IOPORT_CREATE_PIN(PORTB,6)
#   define XPLD_HEADER_J3_PIN8          IOPORT_CREATE_PIN(PORTB,7)

#   define XPLD_HEADER_J4_PIN1          IOPORT_CREATE_PIN(PORTE,0)
#   define XPLD_HEADER_J4_PIN2          IOPORT_CREATE_PIN(PORTE,1)
#   define XPLD_HEADER_J4_PIN3          IOPORT_CREATE_PIN(PORTE,2)
#   define XPLD_HEADER_J4_PIN4          IOPORT_CREATE_PIN(PORTE,3)
#   define XPLD_HEADER_J4_PIN5          IOPORT_CREATE_PIN(PORTE,4)
#   define XPLD_HEADER_J4_PIN6          IOPORT_CREATE_PIN(PORTE,5)
#   define XPLD_HEADER_J4_PIN7          IOPORT_CREATE_PIN(PORTE,6)
#   define XPLD_HEADER_J4_PIN8          IOPORT_CREATE_PIN(PORTE,7)

#elif (BOARD == XMEGA_A3BU_XPLAINED)
#   define XPLD_HEADER_J1_PIN1          IOPORT_CREATE_PIN(PORTC,0)
#   define XPLD_HEADER_J1_PIN2          IOPORT_CREATE_PIN(PORTC,1)
#   define XPLD_HEADER_J1_PIN3          IOPORT_CREATE_PIN(PORTC,2)
#   define XPLD_HEADER_J1_PIN4          IOPORT_CREATE_PIN(PORTC,3)
#   define XPLD_HEADER_J1_PIN5          IOPORT_CREATE_PIN(PORTC,4)
#   define XPLD_HEADER_J1_PIN6          IOPORT_CREATE_PIN(PORTC,5)
#   define XPLD_HEADER_J1_PIN7          IOPORT_CREATE_PIN(PORTC,6)
#   define XPLD_HEADER_J1_PIN8          IOPORT_CREATE_PIN(PORTC,7)

#   define XPLD_HEADER_J2_PIN1          IOPORT_CREATE_PIN(PORTB,0)
#   define XPLD_HEADER_J2_PIN2          IOPORT_CREATE_PIN(PORTB,1)
#   define XPLD_HEADER_J2_PIN3          IOPORT_CREATE_PIN(PORTB,2)
#   define XPLD_HEADER_J2_PIN4          IOPORT_CREATE_PIN(PORTB,3)
#   define XPLD_HEADER_J2_PIN5          IOPORT_CREATE_PIN(PORTA,4)
#   define XPLD_HEADER_J2_PIN6          IOPORT_CREATE_PIN(PORTA,5)
#   define XPLD_HEADER_J2_PIN7          IOPORT_CREATE_PIN(PORTA,6)
#   define XPLD_HEADER_J2_PIN8          IOPORT_CREATE_PIN(PORTA,7)

#   define XPLD_HEADER_J3_PIN1          IOPORT_CREATE_PIN(PORTA,0)
#   define XPLD_HEADER_J3_PIN2          IOPORT_CREATE_PIN(PORTA,1)
#   define XPLD_HEADER_J3_PIN3          IOPORT_CREATE_PIN(PORTA,2)
#   define XPLD_HEADER_J3_PIN4          IOPORT_CREATE_PIN(PORTA,3)
#   define XPLD_HEADER_J3_PIN5          IOPORT_CREATE_PIN(PORTB,4)
#   define XPLD_HEADER_J3_PIN6          IOPORT_CREATE_PIN(PORTB,5)
#   define XPLD_HEADER_J3_PIN7          IOPORT_CREATE_PIN(PORTB,6)
#   define XPLD_HEADER_J3_PIN8          IOPORT_CREATE_PIN(PORTB,7)

#   define XPLD_HEADER_J4_PIN1          IOPORT_CREATE_PIN(PORTE,0)
#   define XPLD_HEADER_J4_PIN2          IOPORT_CREATE_PIN(PORTE,1)
#   define XPLD_HEADER_J4_PIN3          IOPORT_CREATE_PIN(PORTE,2)
#   define XPLD_HEADER_J4_PIN4          IOPORT_CREATE_PIN(PORTE,3)
#   define XPLD_HEADER_J4_PIN5          IOPORT_CREATE_PIN(PORTD,0)
#   define XPLD_HEADER_J4_PIN6          IOPORT_CREATE_PIN(PORTD,3)
#   define XPLD_HEADER_J4_PIN7          IOPORT_CREATE_PIN(PORTD,2)
#   define XPLD_HEADER_J4_PIN8          IOPORT_CREATE_PIN(PORTD,1)

#else
#   warning "The BOARD constant does not define a supported Xplained board."
#   define XPLD_HEADER_J1_PIN1          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J1_PIN2          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J1_PIN3          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J1_PIN4          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J1_PIN5          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J1_PIN6          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J1_PIN7          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J1_PIN8          INVALID_PIN_NUMBER

#   define XPLD_HEADER_J2_PIN1          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J2_PIN2          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J2_PIN3          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J2_PIN4          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J2_PIN5          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J2_PIN6          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J2_PIN7          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J2_PIN8          INVALID_PIN_NUMBER

#   define XPLD_HEADER_J3_PIN1          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J3_PIN2          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J3_PIN3          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J3_PIN4          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J3_PIN5          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J3_PIN6          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J3_PIN7          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J3_PIN8          INVALID_PIN_NUMBER

#   define XPLD_HEADER_J4_PIN1          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J4_PIN2          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J4_PIN3          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J4_PIN4          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J4_PIN5          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J4_PIN6          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J4_PIN7          INVALID_PIN_NUMBER
#   define XPLD_HEADER_J4_PIN8          INVALID_PIN_NUMBER
#endif
// @}


//! \name Xplained Expansion Header External Interrupt Controller Pin Mapping
// @{
#if (BOARD == UC3_A3_XPLAINED)
#   define XPLD_HEADER_J2_PIN1_EIC_LINE (AVR32_EIC_INT0)
#   define XPLD_HEADER_J2_PIN1_EIC_IRQ  (AVR32_EIC_IRQ_0)
#   define XPLD_HEADER_J2_PIN1_EIC_PIN  (AVR32_EIC_EXTINT_0_PIN)
#   define XPLD_HEADER_J2_PIN1_EIC_FUNC (AVR32_EIC_EXTINT_0_FUNCTION)

#   define XPLD_HEADER_J2_PIN2_EIC_LINE (AVR32_EIC_INT1)
#   define XPLD_HEADER_J2_PIN2_EIC_IRQ  (AVR32_EIC_IRQ_1)
#   define XPLD_HEADER_J2_PIN2_EIC_PIN  (AVR32_EIC_EXTINT_1_PIN)
#   define XPLD_HEADER_J2_PIN2_EIC_FUNC (AVR32_EIC_EXTINT_1_FUNCTION)

#   define XPLD_HEADER_J2_PIN3_EIC_LINE (AVR32_EIC_INT2)
#   define XPLD_HEADER_J2_PIN3_EIC_IRQ  (AVR32_EIC_IRQ_2)
#   define XPLD_HEADER_J2_PIN3_EIC_PIN  (AVR32_EIC_EXTINT_2_PIN)
#   define XPLD_HEADER_J2_PIN3_EIC_FUNC (AVR32_EIC_EXTINT_2_FUNCTION)

#   define XPLD_HEADER_J2_PIN4_EIC_LINE (AVR32_EIC_INT3)
#   define XPLD_HEADER_J2_PIN4_EIC_IRQ  (AVR32_EIC_IRQ_3)
#   define XPLD_HEADER_J2_PIN4_EIC_PIN  (AVR32_EIC_EXTINT_3_PIN)
#   define XPLD_HEADER_J2_PIN4_EIC_FUNC (AVR32_EIC_EXTINT_3_FUNCTION)

#   define XPLD_HEADER_J2_PIN5_EIC_LINE (8) // NMI
#   define XPLD_HEADER_J2_PIN5_EIC_IRQ  (0) // NMI - special handler required
#   define XPLD_HEADER_J2_PIN5_EIC_PIN  (AVR32_EIC_EXTINT_8_PIN)
#   define XPLD_HEADER_J2_PIN5_EIC_FUNC (AVR32_EIC_EXTINT_8_FUNCTION)

#elif (BOARD == UC3_L0_XPLAINED)
#   define XPLD_HEADER_J1_PIN3_EIC_LINE (AVR32_EIC_INT5)
#   define XPLD_HEADER_J1_PIN3_EIC_IRQ  (AVR32_EIC_IRQ_5)
#   define XPLD_HEADER_J1_PIN3_EIC_PIN  (AVR32_EIC_EXTINT_5_1_PIN)
#   define XPLD_HEADER_J1_PIN3_EIC_FUNC (AVR32_EIC_EXTINT_5_1_FUNCTION)

#   define XPLD_HEADER_J1_PIN4_EIC_LINE (AVR32_EIC_INT4)
#   define XPLD_HEADER_J1_PIN4_EIC_IRQ  (AVR32_EIC_IRQ_4)
#   define XPLD_HEADER_J1_PIN4_EIC_PIN  (AVR32_EIC_EXTINT_4_1_PIN)
#   define XPLD_HEADER_J1_PIN4_EIC_FUNC (AVR32_EIC_EXTINT_4_1_FUNCTION)

#   define XPLD_HEADER_J2_PIN2_EIC_LINE (AVR32_EIC_INT3)
#   define XPLD_HEADER_J2_PIN2_EIC_IRQ  (AVR32_EIC_IRQ_3)
#   define XPLD_HEADER_J2_PIN2_EIC_PIN  (AVR32_EIC_EXTINT_3_0_PIN)
#   define XPLD_HEADER_J2_PIN2_EIC_FUNC (AVR32_EIC_EXTINT_3_0_FUNCTION)

#   define XPLD_HEADER_J2_PIN3_EIC_LINE (AVR32_EIC_INT4)
#   define XPLD_HEADER_J2_PIN3_EIC_IRQ  (AVR32_EIC_IRQ_4)
#   define XPLD_HEADER_J2_PIN3_EIC_PIN  (AVR32_EIC_EXTINT_4_0_PIN)
#   define XPLD_HEADER_J2_PIN3_EIC_FUNC (AVR32_EIC_EXTINT_4_0_FUNCTION)

#   define XPLD_HEADER_J2_PIN4_EIC_LINE (AVR32_EIC_INT5)
#   define XPLD_HEADER_J2_PIN4_EIC_IRQ  (AVR32_EIC_IRQ_5)
#   define XPLD_HEADER_J2_PIN4_EIC_PIN  (AVR32_EIC_EXTINT_5_0_PIN)
#   define XPLD_HEADER_J2_PIN4_EIC_FUNC (AVR32_EIC_EXTINT_5_0_FUNCTION)

#   define XPLD_HEADER_J2_PIN5_EIC_LINE (AVR32_EIC_INT1)
#   define XPLD_HEADER_J2_PIN5_EIC_IRQ  (AVR32_EIC_IRQ_1)
#   define XPLD_HEADER_J2_PIN5_EIC_PIN  (AVR32_EIC_EXTINT_1_1_PIN)
#   define XPLD_HEADER_J2_PIN5_EIC_FUNC (AVR32_EIC_EXTINT_1_1_FUNCTION)

#   define XPLD_HEADER_J2_PIN6_EIC_LINE (AVR32_EIC_INT2)
#   define XPLD_HEADER_J2_PIN6_EIC_IRQ  (AVR32_EIC_IRQ_2)
#   define XPLD_HEADER_J2_PIN6_EIC_PIN  (AVR32_EIC_EXTINT_2_1_PIN)
#   define XPLD_HEADER_J2_PIN6_EIC_FUNC (AVR32_EIC_EXTINT_2_1_FUNCTION)

#   define XPLD_HEADER_J2_PIN7_EIC_LINE (AVR32_EIC_INT0)
#   define XPLD_HEADER_J2_PIN7_EIC_IRQ  (AVR32_EIC_IRQ_0)
#   define XPLD_HEADER_J2_PIN7_EIC_PIN  (AVR32_EIC_EXTINT_0_1_PIN)
#   define XPLD_HEADER_J2_PIN7_EIC_FUNC (AVR32_EIC_EXTINT_0_1_FUNCTION)

#   define XPLD_HEADER_J3_PIN1_EIC_LINE (AVR32_EIC_INT2)
#   define XPLD_HEADER_J3_PIN1_EIC_IRQ  (AVR32_EIC_IRQ_2)
#   define XPLD_HEADER_J3_PIN1_EIC_PIN  (AVR32_EIC_EXTINT_2_0_PIN)
#   define XPLD_HEADER_J3_PIN1_EIC_FUNC (AVR32_EIC_EXTINT_2_0_FUNCTION)

#   define XPLD_HEADER_J3_PIN6_EIC_LINE (AVR32_EIC_INT3)
#   define XPLD_HEADER_J3_PIN6_EIC_IRQ  (AVR32_EIC_IRQ_3)
#   define XPLD_HEADER_J3_PIN6_EIC_PIN  (AVR32_EIC_EXTINT_3_1_PIN)
#   define XPLD_HEADER_J3_PIN6_EIC_FUNC (AVR32_EIC_EXTINT_3_1_FUNCTION)

#   define XPLD_HEADER_J4_PIN3_EIC_LINE (AVR32_EIC_INT5)
#   define XPLD_HEADER_J4_PIN3_EIC_IRQ  (AVR32_EIC_IRQ_5)
#   define XPLD_HEADER_J4_PIN3_EIC_PIN  (AVR32_EIC_EXTINT_5_1_PIN)
#   define XPLD_HEADER_J4_PIN3_EIC_FUNC (AVR32_EIC_EXTINT_5_1_FUNCTION)

#   define XPLD_HEADER_J4_PIN4_EIC_LINE (AVR32_EIC_INT4)
#   define XPLD_HEADER_J4_PIN4_EIC_IRQ  (AVR32_EIC_IRQ_4)
#   define XPLD_HEADER_J4_PIN4_EIC_PIN  (AVR32_EIC_EXTINT_4_1_PIN)
#   define XPLD_HEADER_J4_PIN4_EIC_FUNC (AVR32_EIC_EXTINT_4_1_FUNCTION)

#elif (BOARD == XMEGA_A1_XPLAINED)
#   define XPLD_HEADER_J1_PORT          (PORTF)
#   define XPLD_HEADER_J1_INT0_vect     (PORTF_INT0_vect)
#   define XPLD_HEADER_J1_INT1_vect     (PORTF_INT1_vect)

#   define XPLD_HEADER_J2_PORT          (PORTA)
#   define XPLD_HEADER_J2_INT0_vect     (PORTA_INT0_vect)
#   define XPLD_HEADER_J2_INT1_vect     (PORTA_INT1_vect)

#   define XPLD_HEADER_J3_PORT          (PORTD)
#   define XPLD_HEADER_J3_INT0_vect     (PORTD_INT0_vect)
#   define XPLD_HEADER_J3_INT1_vect     (PORTD_INT1_vect)

#   define XPLD_HEADER_J4_PORT          (PORTC)
#   define XPLD_HEADER_J4_INT0_vect     (PORTC_INT0_vect)
#   define XPLD_HEADER_J4_INT1_vect     (PORTC_INT1_vect)

#elif (BOARD == XMEGA_B1_XPLAINED)
#   define XPLD_HEADER_J1_PORT          (PORTC)
#   define XPLD_HEADER_J1_INT0_vect     (PORTC_INT0_vect)
#   define XPLD_HEADER_J1_INT1_vect     (PORTC_INT1_vect)

#   define XPLD_HEADER_J2_PORT          (PORTA)
#   define XPLD_HEADER_J2_INT0_vect     (PORTA_INT0_vect)
#   define XPLD_HEADER_J2_INT1_vect     (PORTA_INT1_vect)

#   define XPLD_HEADER_J3_PORT          (PORTB)
#   define XPLD_HEADER_J3_INT0_vect     (PORTB_INT0_vect)
#   define XPLD_HEADER_J3_INT1_vect     (PORTB_INT1_vect)

#   define XPLD_HEADER_J4_PORT          (PORTE)
#   define XPLD_HEADER_J4_INT0_vect     (PORTE_INT0_vect)
#   define XPLD_HEADER_J4_INT1_vect     (PORTE_INT1_vect)

#elif (BOARD == XMEGA_A3BU_XPLAINED)
#   define XPLD_HEADER_J1_PORT          (PORTC)
#   define XPLD_HEADER_J1_INT0_vect     (PORTC_INT0_vect)
#   define XPLD_HEADER_J1_INT1_vect     (PORTC_INT1_vect)

#endif
// @}


#ifdef __cplusplus
}
#endif

#endif /* _xplained_headers_h_ */
