/**
 * \file
 *
 * \brief INTC software driver for AVR UC3 devices.
 *
 * Copyright (c) 2009-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <avr32/io.h>
#include "compiler.h"
#include "preprocessor.h"
#include "intc.h"

/**
 * \internal
 * \brief Import the _evba symbol from exception.S
 */
extern void _evba;

/**
 * \internal
 * \brief Import the symbols _int0, _int1, _int2, _int3 defined in exception.S
 */
extern void _int0, _int1, _int2, _int3;

/**
 * \internal
 * \brief Values to store in the interrupt priority registers for the various
 *  interrupt priority levels.
 */
#define IPR_INT0   ((AVR32_INTC_INT0 << AVR32_INTC_IPR_INTLEVEL_OFFSET) \
			| ((int)&_int0 - (int)&_evba))
#define IPR_INT1   ((AVR32_INTC_INT1 << AVR32_INTC_IPR_INTLEVEL_OFFSET) \
			| ((int)&_int1 - (int)&_evba))
#define IPR_INT2   ((AVR32_INTC_INT2 << AVR32_INTC_IPR_INTLEVEL_OFFSET) \
			| ((int)&_int2 - (int)&_evba))
#define IPR_INT3   ((AVR32_INTC_INT3 << AVR32_INTC_IPR_INTLEVEL_OFFSET) \
			| ((int)&_int3 - (int)&_evba))

/**
 * \internal
 * \brief Table of interrupt line handlers per interrupt group in order to
 * optimize RAM space. Each line handler table contains a set of pointers to
 * interrupt handlers.
 */
#if (defined __GNUC__)
#  define DECL_INT_LINE_HANDLER_TABLE(GRP, unused) \
static volatile __int_handler \
	_int_line_handler_table_##GRP[Max(AVR32_INTC_NUM_IRQS_PER_GRP##GRP, 1)];
#elif (defined __ICCAVR32__)
#  define DECL_INT_LINE_HANDLER_TABLE(GRP, unused) \
static volatile __no_init __int_handler \
	_int_line_handler_table_##GRP[Max(AVR32_INTC_NUM_IRQS_PER_GRP##GRP, 1)];
#endif
MREPEAT(AVR32_INTC_NUM_INT_GRPS, DECL_INT_LINE_HANDLER_TABLE, ~);
#undef DECL_INT_LINE_HANDLER_TABLE

/**
 * \internal
 * \brief Table containing for each interrupt group the number of interrupt
 *  request lines and a pointer to the table of interrupt line handlers.
 */
static const struct
{
	unsigned int           num_irqs;
	volatile __int_handler *_int_line_handler_table;
} _int_handler_table[AVR32_INTC_NUM_INT_GRPS] =
{
#define INSERT_INT_LINE_HANDLER_TABLE(GRP, unused) \
	{AVR32_INTC_NUM_IRQS_PER_GRP##GRP, _int_line_handler_table_##GRP},
	MREPEAT(AVR32_INTC_NUM_INT_GRPS, INSERT_INT_LINE_HANDLER_TABLE, ~)
#undef INSERT_INT_LINE_HANDLER_TABLE
};


/**
 * \internal
 * \brief Default interrupt handler.
 */
#if (defined __GNUC__)
__attribute__((__interrupt__))
#elif (defined __ICCAVR32__)
__interrupt
#endif
static void _unhandled_interrupt(void)
{
	// Catch unregistered interrupts.
	while (true);
}


/**
 * \brief Gets the interrupt handler of the current event at the \a int_level
 *        interrupt priority level (called from exception.S).
 *
 * \param int_level Interrupt priority level to handle.
 *
 * \return Interrupt handler to execute.
 */
__int_handler _get_interrupt_handler(uint32_t int_level);
__int_handler _get_interrupt_handler(uint32_t int_level)
{
	/* ICR3 is mapped first, ICR0 last.
	Code in exception.S puts int_level in R12 which is used by the compiler
	to pass a single argument to a function. */
	uint32_t int_grp = AVR32_INTC.icr[AVR32_INTC_INT3 - int_level];
	uint32_t int_req = AVR32_INTC.irr[int_grp];

	/* As an interrupt may disappear while it is being fetched by the CPU
	(spurious interrupt caused by a delayed response from an MCU peripheral
	to an interrupt flag clear or interrupt disable instruction), check if
	there are remaining interrupt lines to process.
	If a spurious interrupt occurs, the status register (SR) contains an
	execution mode and interrupt level masks corresponding to a level 0
	interrupt, whatever the interrupt priority level causing the spurious
	event. This behavior has been chosen because a spurious interrupt has
	not to be a priority one and because it may not cause any trouble to
	other interrupts.
	However, these spurious interrupts place the hardware in an unstable
	state and could give problems in other/future versions of the CPU, so
	the software has to be written so that they never occur. The only safe
	way of achieving this is to always clear or disable peripheral
	interrupts with the following sequence:
	1: Mask the interrupt in the CPU by setting GM (or IxM) in SR.
	2: Perform the bus access to the peripheral register that clears or
	disables the interrupt.
	3: Wait until the interrupt has actually been cleared or disabled by the
	peripheral. This is usually performed by reading from a register in the
	same peripheral (it DOES NOT have to be the same register that was
	accessed in step 2, but it MUST be in the same peripheral), what takes
	bus system latencies into account, but peripheral internal latencies
	(generally 0 cycle) also have to be considered.
	4: Unmask the interrupt in the CPU by clearing GM (or IxM) in SR.
	Note that steps 1 and 4 are useless inside interrupt handlers as the
	corresponding interrupt level is automatically masked by IxM (unless IxM
	is explicitly cleared by the software).*/

	/* Get the right IRQ handler.

	If several interrupt lines are active in the group, the interrupt line
	with the highest number is selected. This is to be coherent with the
	prioritization of interrupt groups performed by the hardware interrupt
	controller.

	If no handler has been registered for the pending interrupt,
	_unhandled_interrupt will be selected thanks to the initialization of
	_int_line_handler_table_x by INTC_init_interrupts.

	exception.S will provide the interrupt handler with a clean interrupt
	stack frame, with nothing more pushed onto the stack. The interrupt
	handler must manage the `rete' instruction, which can be done using
	pure assembly, inline assembly or the `__attribute__((__interrupt__))'
	C function attribute.*/
	return (int_req)
		? _int_handler_table[int_grp]._int_line_handler_table[32
			- clz(int_req) - 1]
		: NULL;
}


/**
 * \internal
 * \brief Init EVBA address. This operation may or may not have been done by the
 * C startup process.
 */
static __inline__ void INTC_init_evba(void)
{
  Set_system_register(AVR32_EVBA, (int32_t)&_evba );
}


/**
 * \brief Initializes the hardware interrupt controller driver.
 *
 */
void INTC_init_interrupts(void)
{
	uint32_t int_grp, int_req;

	INTC_init_evba();

	// For all interrupt groups,
	for (int_grp = 0; int_grp < AVR32_INTC_NUM_INT_GRPS; int_grp++)
	{
		// For all interrupt request lines of each group,
		for (int_req = 0;
			int_req < _int_handler_table[int_grp].num_irqs;
			int_req++)
		{
			/* Assign _unhandled_interrupt as the default interrupt
			handler. */
			_int_handler_table[int_grp]
				._int_line_handler_table[int_req]
					= &_unhandled_interrupt;
		}

		/* Set the interrupt group priority register to its default
		value.
		By default, all interrupt groups are linked to the interrupt
		priority level 0 and to the interrupt vector _int0. */
		AVR32_INTC.ipr[int_grp] = IPR_INT0;
	}
}


/**
 * \brief Registers an interrupt handler.
 *
 * \param handler   Interrupt handler to register.
 * \param irq       IRQ of the interrupt handler to register.
 * \param int_level Interrupt priority level to assign to the group of this IRQ.
 *
 * \warning The interrupt handler must manage the `rete' instruction, which can
 *          be done using pure assembly, inline assembly or the
 *          `__attribute__((__interrupt__))' C function attribute.
 *
 * \warning If several interrupt handlers of a same group are registered with
 *          different priority levels, only the latest priority level set will
 *          be effective.
 *
 */
void INTC_register_interrupt(__int_handler handler, uint32_t irq,
	uint32_t int_level)
{
	// Determine the group of the IRQ.
	uint32_t int_grp = irq / AVR32_INTC_MAX_NUM_IRQS_PER_GRP;

	/* Store in _int_line_handler_table_x the pointer to the interrupt
	handler, so that _get_interrupt_handler can retrieve it when the
	interrupt is vectored. */
	_int_handler_table[int_grp]
		._int_line_handler_table[irq % AVR32_INTC_MAX_NUM_IRQS_PER_GRP]
			= handler;

	/* Program the corresponding IPRX register to set the interrupt priority
	level and the interrupt vector offset that will be fetched by the core
	interrupt system.
	NOTE: The _intx functions are intermediate assembly functions between
	the core interrupt system and the user interrupt handler. */
	if (int_level == AVR32_INTC_INT0) {
		AVR32_INTC.ipr[int_grp] = IPR_INT0;
	} else if (int_level == AVR32_INTC_INT1) {
		AVR32_INTC.ipr[int_grp] = IPR_INT1;
	} else if (int_level == AVR32_INTC_INT2) {
		AVR32_INTC.ipr[int_grp] = IPR_INT2;
	} else {
		AVR32_INTC.ipr[int_grp] = IPR_INT3;
	}
}
