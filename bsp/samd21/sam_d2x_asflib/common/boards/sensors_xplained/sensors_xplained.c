/**
 * \file
 *
 * \brief SENSORS_XPLAINED_BOARD extension board adaptation.
 *
 * Copyright (c) 2011-2015 Atmel Corporation. All rights reserved.
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

#include    "sensors_xplained.h"
#include    <sysclk.h>

#if UC3
#   include <eic.h>
#endif

#if UC3
#   define PIN_OUTPUT_FLAGS         (GPIO_DIR_OUTPUT | GPIO_INIT_HIGH)
#   define PIN_INPUT_FLAGS          (GPIO_DIR_INPUT)
#elif XMEGA
#   define PIN_OUTPUT_FLAGS         (IOPORT_DIR_OUTPUT | IOPORT_INIT_HIGH)
#   define PIN_INPUT_FLAGS          (IOPORT_DIR_INPUT)
#endif

#if defined(__AVR32__) || defined(__ICCAVR32__)
#  if !defined(AVR32_GPIO_IRQ_GROUP)
#   define AVR32_GPIO_IRQ_GROUP     (AVR32_GPIO_IRQ_0 / 32)
#  endif

#  if  defined(CONFIG_GPIO_INT_LVL)
#    define GPIO_INT_LVL            CONFIG_GPIO_INT_LVL
#  else
#    define GPIO_INT_LVL            0
#  endif

#  if !defined(AVR32_EIC_IRQ_GROUP)
#    if UC3L
#      define AVR32_EIC_IRQ_GROUP   (AVR32_EIC_IRQ_1 / 32)
#    else
#      define AVR32_EIC_IRQ_GROUP   (AVR32_EIC_IRQ_0 / 32)
#    endif
#  endif

#  if  defined(CONFIG_EIC_INT_LVL)
#    define EIC_INT_LVL             CONFIG_EIC_INT_LVL
#  else
#    define EIC_INT_LVL             0
#  endif
#endif /* (__AVR32__) || (__ICCAVR32__) */

/* Don't include interrupt definitions without a valid board configuration. */

#if defined(SENSORS_XPLAINED_BOARD) && defined(COMMON_SENSOR_PLATFORM)

/*! \internal
 * \name Sensor Board GPIO interrupt handler callback pointers
 * @{
 */
static SENSOR_IRQ_HANDLER sensor_pin3_handler;
static volatile void *sensor_pin3_arg;

static SENSOR_IRQ_HANDLER sensor_pin4_handler;
static volatile void *sensor_pin4_arg;

static SENSOR_IRQ_HANDLER sensor_pin5_handler;
static volatile void *sensor_pin5_arg;
/*! @} */

#if UC3

/*! \internal Sensor Board GPIO interrupt handler
 *
 * This is the default ISR for the Xplained Sensor board GPIO pins.  If
 * an external interrupt interface is available, the corresponding
 * eic_pinX_handler will be used instead.
 *
 * \return  Nothing.
 */
ISR(gpio_irq_handler, AVR32_GPIO_IRQ_GROUP, GPIO_INT_LVL)
{
	if (gpio_get_pin_interrupt_flag(SENSOR_BOARD_PIN3)) {
		sensor_pin3_handler(sensor_pin3_arg);

		gpio_clear_pin_interrupt_flag(SENSOR_BOARD_PIN3);
	} else if (gpio_get_pin_interrupt_flag(SENSOR_BOARD_PIN4)) {
		sensor_pin4_handler(sensor_pin4_arg);

		gpio_clear_pin_interrupt_flag(SENSOR_BOARD_PIN4);
	} else if (gpio_get_pin_interrupt_flag(SENSOR_BOARD_PIN5)) {
		sensor_pin5_handler(sensor_pin5_arg);

		gpio_clear_pin_interrupt_flag(SENSOR_BOARD_PIN5);
	}
}

#elif XMEGA

/*! \internal Sensor Board GPIO interrupt handler
 *
 * This is the default ISR for the Xplained Sensor board GPIO pins.  The
 * installed handler routine for the particular pin will be called with
 * the argument specified when the handler was installed..
 *
 * \return  Nothing.
 */
ISR(SENSOR_BOARD_PORT_vect)
{
	PORT_t *const port = &(SENSOR_BOARD_PORT);

	/* Call the interrupt handler (if any). */
	if (sensor_pin3_handler && (port->IN & PIN2_bm)) {
		/* Note: header pin 3 = io port pin 2 */
		sensor_pin3_handler(sensor_pin3_arg);
	} else if (sensor_pin4_handler && (port->IN & PIN3_bm)) {
		/* Note: header pin 4 = io port pin 3 */
		sensor_pin4_handler(sensor_pin4_arg);
	} else if (sensor_pin5_handler && (port->IN & PIN4_bm)) {
		/* Note: header pin 5 = io port pin 4 */
		sensor_pin5_handler(sensor_pin5_arg);
	}

	/* Clear the port interrupt flag */
	port->INTFLAGS = PORT_INT0IF_bm;
}
#endif

#if defined(SENSOR_PIN3_EIC_LINE)

/*! \internal Sensor Board external interrupt handler - PIN3
 *
 * This is the ISR for the Xplained Sensor board GPIO PIN3 for configurations
 * in which it can generate an external interrupt.
 *
 * \return  Nothing.
 */
ISR(eic_pin3_handler, AVR32_EIC_IRQ_GROUP, EIC_INT_LVL)
{
	sensor_pin3_handler(sensor_pin3_arg);     /* call handler in driver */

	eic_clear_interrupt_line(&AVR32_EIC, SENSOR_PIN3_EIC_LINE);
}
#endif

#if defined(SENSOR_PIN4_EIC_LINE)

/*! \internal Sensor Board external interrupt handler - PIN4
 *
 * This is the ISR for the Xplained Sensor board GPIO PIN4 for configurations
 * in which it can generate an external interrupt.
 *
 * \return  Nothing.
 */
ISR(eic_pin4_handler, AVR32_EIC_IRQ_GROUP, EIC_INT_LVL)
{
	sensor_pin4_handler(sensor_pin4_arg);     /* call handler in driver */

	eic_clear_interrupt_line(&AVR32_EIC, SENSOR_PIN4_EIC_LINE);
}
#endif

#if defined(SENSOR_PIN5_EIC_LINE)

/*! \internal Sensor Board external interrupt handler - PIN5
 *
 * This is the ISR for the Xplained Sensor board GPIO PIN5 for configurations
 * in which it can generate an external interrupt.
 *
 * \return  Nothing.
 */
ISR(eic_pin5_handler, AVR32_EIC_IRQ_GROUP, EIC_INT_LVL)
{
	sensor_pin5_handler(sensor_pin5_arg);     /* call handler in driver */

	eic_clear_interrupt_line(&AVR32_EIC, SENSOR_PIN5_EIC_LINE);
}
#endif

#if UC3

/*! \internal Enable a general purpose I/O pin interrupt.
 *
 * This routine enables interrupts on a specified general purpose I/O pin.
 *
 * \param gpio_pin      GPIO pin interface to the MCU
 * \param gpio_irq      IRQ of the interrupt handler
 */
static void gpio_irq_connect(uint32_t gpio_pin, uint32_t gpio_irq)
{
	irq_register_handler(gpio_irq_handler, gpio_irq, GPIO_INT_LVL);
	gpio_enable_pin_interrupt(gpio_pin, GPIO_RISING_EDGE);
}

#endif

#if defined(SYSCLK_EIC)

/*! \brief Enable an EIC interrupt line.
 *
 * This routine maps a GPIO pin and peripheral function to a specified EIC line.
 *
 * \param eic_line      Line number to enable
 * \param eic_pin       GPIO module pin
 * \param eic_func      GPIO module function
 * \param eic_irq       IRQ of the interrupt handler
 * \param eic_handler   Interrupt handler to register
 */
static void eic_irq_connect(uint32_t eic_line, uint32_t eic_pin,
		uint32_t eic_func, uint32_t eic_irq, __int_handler eic_handler)
{
	eic_options_t const eic_options = {
		.eic_line   = eic_line,
		.eic_mode   = EIC_MODE_EDGE_TRIGGERED,
		.eic_edge   = EIC_EDGE_RISING_EDGE,
		.eic_level  = EIC_LEVEL_HIGH_LEVEL,
		.eic_filter = EIC_FILTER_ENABLED,
		.eic_async  = EIC_ASYNCH_MODE
	};

	sysclk_enable_pba_module(SYSCLK_EIC);

	gpio_enable_module_pin(eic_pin, eic_func);
	irq_register_handler(eic_handler, eic_irq, 0);

	eic_init(&AVR32_EIC, &eic_options, 1);
	eic_enable_line(&AVR32_EIC, eic_line);
	eic_enable_interrupt_line(&AVR32_EIC, eic_line);
}

#endif

/*! \brief Install a sensor interrupt handler
 *
 * The Sensors Xplained add-on boards route sensor device I/O pins to GPIO
 * pins for the MCU installed on an Xplained platform board.  Some sensor
 * devices can be configured to generate interrupts on these pins to indicate
 * the availability of new sensor data or the occurrence of configurable
 * events related to sensor data thresholds, for example.
 *
 * This routine will enable interrupts on the GPIO pin specified by the
 * \c gpio_pin parameter and call a user-defined callback \c handler when an
 * interrupt is detected.  The \c arg parameter is used to pass the address
 * of user-defined input and output storage for the callback handler.  Calling
 * the routine with the \c handler parameter set to 0 (the NULL pointer) will
 * fail with \c false returned to the caller.
 *
 * \param   gpio_pin    Board-specific GPIO pin interface to the MCU.
 * \param   handler     The address of a driver-defined interrupt handler.
 * \param   arg         An optional address passed to the interrupt handler.
 *
 * \return  bool        true if the call succeeds, else false.
 */
bool sensor_board_irq_connect(uint32_t gpio_pin,
		SENSOR_IRQ_HANDLER handler, void *arg)
{
	bool status = false;

#if XMEGA
	PORT_t *sensor_port;
#endif

	/* Ensure that the caller has specified a function address. */

	if (handler == NULL) {
		return status;
	}

	/* Save the interrupt flag state and disable MCU interrupts. */

	irqflags_t const irq_flags = cpu_irq_save();

	cpu_irq_disable();

	/* Initialize an interrupt for a specified I/O pin. */

	if (SENSOR_BOARD_PIN3 == gpio_pin) {
		sensor_pin3_handler = handler;
		sensor_pin3_arg     = arg;

#if UC3
#  if defined(SENSOR_PIN3_EIC_LINE)
		eic_irq_connect(SENSOR_PIN3_EIC_LINE, SENSOR_PIN3_EIC_PIN,
				SENSOR_PIN3_EIC_FUNC, SENSOR_PIN3_EIC_IRQ,
				eic_pin3_handler);
#  else
		gpio_irq_connect(gpio_pin, SENSOR_PIN3_IRQ);
#  endif
#elif XMEGA
		sensor_port = ioport_pin_to_port(SENSOR_BOARD_PIN3);
		sensor_port->INTCTRL   = PORT_INT0LVL_LO_gc;
		sensor_port->INT0MASK |= ioport_pin_to_mask(SENSOR_BOARD_PIN3);
		/* Some Xplained kits have limited asynchronous sensing on most
		 * pins, which requires them to be sensing on both edges.
		 */
		ioport_set_pin_sense_mode(SENSOR_BOARD_PIN3,
				IOPORT_SENSE_BOTHEDGES);
#endif
		status = true;
	} else if (SENSOR_BOARD_PIN4 == gpio_pin) {
		sensor_pin4_handler = handler;
		sensor_pin4_arg     = arg;

#if UC3
#  if defined(SENSOR_PIN4_EIC_LINE)
		eic_irq_connect(SENSOR_PIN4_EIC_LINE, SENSOR_PIN4_EIC_PIN,
				SENSOR_PIN4_EIC_FUNC, SENSOR_PIN4_EIC_IRQ,
				eic_pin4_handler);
#  else
		gpio_irq_connect(gpio_pin, SENSOR_PIN4_IRQ);
#  endif
#elif XMEGA
		sensor_port = ioport_pin_to_port(SENSOR_BOARD_PIN4);
		sensor_port->INTCTRL   = PORT_INT0LVL_LO_gc;
		sensor_port->INT0MASK |= ioport_pin_to_mask(SENSOR_BOARD_PIN4);
		/* Some Xplained kits have limited asynchronous sensing on most
		 * pins, which requires them to be sensing on both edges.
		 */
		ioport_set_pin_sense_mode(SENSOR_BOARD_PIN4,
				IOPORT_SENSE_BOTHEDGES);
#endif
		status = true;
	} else if (SENSOR_BOARD_PIN5 == gpio_pin) {
		sensor_pin5_handler = handler;
		sensor_pin5_arg     = arg;

#if UC3
#  if defined(SENSOR_PIN5_EIC_LINE)
		eic_irq_connect(SENSOR_PIN5_EIC_LINE, SENSOR_PIN5_EIC_PIN,
				SENSOR_PIN5_EIC_FUNC, SENSOR_PIN5_EIC_IRQ,
				eic_pin5_handler);
#  else
		gpio_irq_connect(gpio_pin, SENSOR_PIN5_IRQ);
#  endif
#elif XMEGA
		sensor_port = ioport_pin_to_port(SENSOR_BOARD_PIN5);
		sensor_port->INTCTRL   = PORT_INT0LVL_LO_gc;
		sensor_port->INT0MASK |= ioport_pin_to_mask(SENSOR_BOARD_PIN5);
		/* Some Xplained kits have limited asynchronous sensing on most
		 * pins, which requires them to be sensing on both edges.
		 */
		ioport_set_pin_sense_mode(SENSOR_BOARD_PIN5,
				IOPORT_SENSE_BOTHEDGES);
#endif
		status = true;
	}

	/* Restore the MCU interrupt flag state. */

	cpu_irq_restore(irq_flags);

	return status;
}

#endif /* defined(SENSORS_XPLAINED_BOARD) && defined(COMMON_SENSOR_PLATFORM) */

/*! \brief Initialize sensor board target resources
 *
 * This function should be called to ensure proper initialization
 * of sensor hardware connected to an Atmel AVR32 or XMEGA platform.
 *
 * \return  Nothing.
 */
void sensor_board_init(void)
{
	/* Configure all defined Xplained Sensor board I/O pins.
	 *
	 * \todo
	 * Determine whether the interrupt event flag (rising edge, falling
	 * edge, toggle, etc.) should be a statically configurable parameter
	 * for devices requiring more flexibility in how events are detected.
	 */
#if (EXT_BOARD == SENSORS_XPLAINED_INERTIAL_1) || \
	(EXT_BOARD == SENSORS_XPLAINED_INERTIAL_2) || \
	(EXT_BOARD == SENSORS_XPLAINED_INERTIAL_A1)

	gpio_configure_pin(SENSOR_BOARD_PIN3, PIN_INPUT_FLAGS);
	gpio_configure_pin(SENSOR_BOARD_PIN4, PIN_INPUT_FLAGS);
	gpio_configure_pin(SENSOR_BOARD_PIN5, PIN_INPUT_FLAGS);

#elif (EXT_BOARD == SENSORS_XPLAINED_PRESSURE_1)
	gpio_configure_pin(SENSOR_BOARD_PIN3, PIN_OUTPUT_FLAGS);
	gpio_configure_pin(SENSOR_BOARD_PIN4, PIN_INPUT_FLAGS);

#elif (EXT_BOARD == SENSORS_XPLAINED_LIGHTPROX_1)
	gpio_configure_pin(SENSOR_BOARD_PIN3, PIN_INPUT_FLAGS);

#elif (EXT_BOARD == SENSORS_XPLAINED_BREADBOARD)
	gpio_configure_pin(SENSOR_BOARD_PIN4, PIN_INPUT_FLAGS);
#endif

	/* Global Interrupt Disable */
	cpu_irq_disable();

	/* Initialize interrupt vector table support. */
	irq_initialize_vectors();

	/* Global Interrupt Enable */
	cpu_irq_enable();
}
