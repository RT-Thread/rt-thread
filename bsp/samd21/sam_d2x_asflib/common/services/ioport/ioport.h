/**
 * \file
 *
 * \brief Common IOPORT service main header file for AVR, UC3 and ARM
 *        architectures.
 *
 * Copyright (c) 2012-2016 Atmel Corporation. All rights reserved.
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
#ifndef IOPORT_H
#define IOPORT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <parts.h>
#include <compiler.h>

/**
 * \defgroup ioport_group Common IOPORT API
 *
 * See \ref ioport_quickstart.
 *
 * This is common IOPORT service for GPIO pin configuration and control in a
 * standardized manner across the MEGA, MEGA_RF, XMEGA, UC3 and ARM devices.
 *
 * Port pin control code is optimized for each platform, and should produce
 * both compact and fast execution times when used with constant values.
 *
 * \section dependencies Dependencies
 * This driver depends on the following modules:
 * - \ref sysclk_group for clock speed and functions.
 * @{
 */

/**
 * \def IOPORT_CREATE_PIN(port, pin)
 * \brief Create IOPORT pin number
 *
 * Create a IOPORT pin number for use with the IOPORT functions.
 *
 * \param port IOPORT port (e.g. PORTA, PA or PIOA depending on chosen
 *             architecture)
 * \param pin IOPORT zero-based index of the I/O pin
 */

/** \brief IOPORT pin directions */
enum ioport_direction {
	IOPORT_DIR_INPUT,  /*!< IOPORT input direction */
	IOPORT_DIR_OUTPUT, /*!< IOPORT output direction */
};

/** \brief IOPORT levels */
enum ioport_value {
	IOPORT_PIN_LEVEL_LOW,  /*!< IOPORT pin value low */
	IOPORT_PIN_LEVEL_HIGH, /*!< IOPORT pin value high */
};

#if MEGA_RF
/** \brief IOPORT edge sense modes */
enum ioport_sense {
	IOPORT_SENSE_LEVEL,     /*!< IOPORT sense low level  */
	IOPORT_SENSE_BOTHEDGES, /*!< IOPORT sense both rising and falling edges */
	IOPORT_SENSE_FALLING,   /*!< IOPORT sense falling edges */
	IOPORT_SENSE_RISING,    /*!< IOPORT sense rising edges */
};
#elif SAM && !SAM4L
/** \brief IOPORT edge sense modes */
enum ioport_sense {
	IOPORT_SENSE_BOTHEDGES, /*!< IOPORT sense both rising and falling edges */
	IOPORT_SENSE_FALLING,   /*!< IOPORT sense falling edges */
	IOPORT_SENSE_RISING,    /*!< IOPORT sense rising edges */
	IOPORT_SENSE_LEVEL_LOW, /*!< IOPORT sense low level  */
	IOPORT_SENSE_LEVEL_HIGH,/*!< IOPORT sense High level  */
};
#elif XMEGA
enum ioport_sense {
	IOPORT_SENSE_BOTHEDGES, /*!< IOPORT sense both rising and falling edges */
	IOPORT_SENSE_RISING,    /*!< IOPORT sense rising edges */
	IOPORT_SENSE_FALLING,   /*!< IOPORT sense falling edges */
	IOPORT_SENSE_LEVEL_LOW, /*!< IOPORT sense low level */
};
#else
enum ioport_sense {
	IOPORT_SENSE_BOTHEDGES, /*!< IOPORT sense both rising and falling edges */
	IOPORT_SENSE_RISING,    /*!< IOPORT sense rising edges */
	IOPORT_SENSE_FALLING,   /*!< IOPORT sense falling edges */
};
#endif


#if XMEGA
# include "xmega/ioport.h"
# if defined(IOPORT_XMEGA_COMPAT)
#  include "xmega/ioport_compat.h"
# endif
#elif MEGA
#  include "mega/ioport.h"
#elif UC3
# include "uc3/ioport.h"
#elif SAM
# if SAM4L
#  include "sam/ioport_gpio.h"
# elif (SAMD20 | SAMD21 | SAML21)
#  include "sam0/ioport.h"
# else
#  include "sam/ioport_pio.h"
# endif
#endif

/**
 * \brief Initializes the IOPORT service, ready for use.
 *
 * This function must be called before using any other functions in the IOPORT
 * service.
 */
static inline void ioport_init(void)
{
	arch_ioport_init();
}

/**
 * \brief Enable an IOPORT pin, based on a pin created with \ref
 * IOPORT_CREATE_PIN().
 *
 * \param pin  IOPORT pin to enable
 */
static inline void ioport_enable_pin(ioport_pin_t pin)
{
	arch_ioport_enable_pin(pin);
}

/**
 * \brief Enable multiple pins in a single IOPORT port.
 *
 * \param port IOPORT port to enable
 * \param mask Mask of pins within the port to enable
 */
static inline void ioport_enable_port(ioport_port_t port,
		ioport_port_mask_t mask)
{
	arch_ioport_enable_port(port, mask);
}

/**
 * \brief Disable IOPORT pin, based on a pin created with \ref
 *        IOPORT_CREATE_PIN().
 *
 * \param pin IOPORT pin to disable
 */
static inline void ioport_disable_pin(ioport_pin_t pin)
{
	arch_ioport_disable_pin(pin);
}

/**
 * \brief Disable multiple pins in a single IOPORT port.
 *
 * \param port IOPORT port to disable
 * \param mask Pin mask of pins to disable
 */
static inline void ioport_disable_port(ioport_port_t port,
		ioport_port_mask_t mask)
{
	arch_ioport_disable_port(port, mask);
}

/**
 * \brief Set multiple pin modes in a single IOPORT port, such as pull-up,
 * pull-down, etc. configuration.
 *
 * \param port IOPORT port to configure
 * \param mask Pin mask of pins to configure
 * \param mode Mode masks to configure for the specified pins (\ref
 * ioport_modes)
 */
static inline void ioport_set_port_mode(ioport_port_t port,
		ioport_port_mask_t mask, ioport_mode_t mode)
{
	arch_ioport_set_port_mode(port, mask, mode);
}

/**
 * \brief Set pin mode for one single IOPORT pin.
 *
 * \param pin IOPORT pin to configure
 * \param mode Mode masks to configure for the specified pin (\ref ioport_modes)
 */
static inline void ioport_set_pin_mode(ioport_pin_t pin, ioport_mode_t mode)
{
	arch_ioport_set_pin_mode(pin, mode);
}

/**
 * \brief Reset multiple pin modes in a specified IOPORT port to defaults.
 *
 * \param port IOPORT port to configure
 * \param mask Mask of pins whose mode configuration is to be reset
 */
static inline void ioport_reset_port_mode(ioport_port_t port,
		ioport_port_mask_t mask)
{
	arch_ioport_set_port_mode(port, mask, 0);
}

/**
 * \brief Reset pin mode configuration for a single IOPORT pin
 *
 * \param pin IOPORT pin to configure
 */
static inline void ioport_reset_pin_mode(ioport_pin_t pin)
{
	arch_ioport_set_pin_mode(pin, 0);
}

/**
 * \brief Set I/O direction for a group of pins in a single IOPORT.
 *
 * \param port IOPORT port to configure
 * \param mask Pin mask of pins to configure
 * \param dir Direction to set for the specified pins (\ref ioport_direction)
 */
static inline void ioport_set_port_dir(ioport_port_t port,
		ioport_port_mask_t mask, enum ioport_direction dir)
{
	arch_ioport_set_port_dir(port, mask, dir);
}

/**
 * \brief Set direction for a single IOPORT pin.
 *
 * \param pin IOPORT pin to configure
 * \param dir Direction to set for the specified pin (\ref ioport_direction)
 */
static inline void ioport_set_pin_dir(ioport_pin_t pin,
		enum ioport_direction dir)
{
	arch_ioport_set_pin_dir(pin, dir);
}

/**
 * \brief Set an IOPORT pin to a specified logical value.
 *
 * \param pin IOPORT pin to configure
 * \param level Logical value of the pin
 */
static inline void ioport_set_pin_level(ioport_pin_t pin, bool level)
{
	arch_ioport_set_pin_level(pin, level);
}

/**
 * \brief Set a group of IOPORT pins in a single port to a specified logical
 * value.
 *
 * \param port IOPORT port to write to
 * \param mask Pin mask of pins to modify
 * \param level Level of the pins to be modified
 */
static inline void ioport_set_port_level(ioport_port_t port,
		ioport_port_mask_t mask, enum ioport_value level)
{
	arch_ioport_set_port_level(port, mask, level);
}

/**
 * \brief Get current value of an IOPORT pin, which has been configured as an
 * input.
 *
 * \param pin IOPORT pin to read
 * \return Current logical value of the specified pin
 */
static inline bool ioport_get_pin_level(ioport_pin_t pin)
{
	return arch_ioport_get_pin_level(pin);
}

/**
 * \brief Get current value of several IOPORT pins in a single port, which have
 * been configured as an inputs.
 *
 * \param port IOPORT port to read
 * \param mask Pin mask of pins to read
 * \return Logical levels of the specified pins from the read port, returned as
 * a mask.
 */
static inline ioport_port_mask_t ioport_get_port_level(ioport_pin_t port,
		ioport_port_mask_t mask)
{
	return arch_ioport_get_port_level(port, mask);
}

/**
 * \brief Toggle the value of an IOPORT pin, which has previously configured as
 * an output.
 *
 * \param pin IOPORT pin to toggle
 */
static inline void ioport_toggle_pin_level(ioport_pin_t pin)
{
	arch_ioport_toggle_pin_level(pin);
}

/**
 * \brief Toggle the values of several IOPORT pins located in a single port.
 *
 * \param port IOPORT port to modify
 * \param mask Pin mask of pins to toggle
 */
static inline void ioport_toggle_port_level(ioport_port_t port,
		ioport_port_mask_t mask)
{
	arch_ioport_toggle_port_level(port, mask);
}

/**
 * \brief Set the pin sense mode of a single IOPORT pin.
 *
 * \param pin IOPORT pin to configure
 * \param pin_sense Edge to sense for the pin (\ref ioport_sense)
 */
static inline void ioport_set_pin_sense_mode(ioport_pin_t pin,
		enum ioport_sense pin_sense)
{
	arch_ioport_set_pin_sense_mode(pin, pin_sense);
}

/**
 * \brief Set the pin sense mode of a multiple IOPORT pins on a single port.
 *
 * \param port IOPORT port to configure
 * \param mask Bitmask if pins whose edge sense is to be configured
 * \param pin_sense Edge to sense for the pins (\ref ioport_sense)
 */
static inline void ioport_set_port_sense_mode(ioport_port_t port,
		ioport_port_mask_t mask,
		enum ioport_sense pin_sense)
{
	arch_ioport_set_port_sense_mode(port, mask, pin_sense);
}

/**
 * \brief Convert a pin ID into a its port ID.
 *
 * \param pin IOPORT pin ID to convert
 * \retval Port ID for the given pin ID
 */
static inline ioport_port_t ioport_pin_to_port_id(ioport_pin_t pin)
{
	return arch_ioport_pin_to_port_id(pin);
}

/**
 * \brief Convert a pin ID into a bitmask mask for the given pin on its port.
 *
 * \param pin IOPORT pin ID to convert
 * \retval Bitmask with a bit set that corresponds to the given pin ID in its port
 */
static inline ioport_port_mask_t ioport_pin_to_mask(ioport_pin_t pin)
{
	return arch_ioport_pin_to_mask(pin);
}

/** @} */

/**
 * \page ioport_quickstart Quick start guide for the common IOPORT service
 *
 * This is the quick start guide for the \ref ioport_group, with
 * step-by-step instructions on how to configure and use the service in a
 * selection of use cases.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section ioport_quickstart_basic Basic use case
 * In this use case we will configure one IO pin for button input and one for
 * LED control. Then it will read the button state and output it on the LED.
 *
 * \section ioport_quickstart_basic_setup Setup steps
 *
 * \subsection ioport_quickstart_basic_setup_code Example code
 * \code
	 #define MY_LED    IOPORT_CREATE_PIN(PORTA, 5)
	 #define MY_BUTTON IOPORT_CREATE_PIN(PORTA, 6)

	 ioport_init();

	 ioport_set_pin_dir(MY_LED, IOPORT_DIR_OUTPUT);
	 ioport_set_pin_dir(MY_BUTTON, IOPORT_DIR_INPUT);
	 ioport_set_pin_mode(MY_BUTTON, IOPORT_MODE_PULLUP);
\endcode
 *
 * \subsection ioport_quickstart_basic_setup_flow Workflow
 * -# It's useful to give the GPIOs symbolic names and this can be done with
 *    the \ref IOPORT_CREATE_PIN macro. We define one for a LED and one for a
 *    button.
 *   - \code
	#define MY_LED    IOPORT_CREATE_PIN(PORTA, 5)
	#define MY_BUTTON IOPORT_CREATE_PIN(PORTA, 6)
\endcode
 *   - \note The usefulness of the \ref IOPORT_CREATE_PIN macro and port names
 *           differ between architectures:
 *     - MEGA, MEGA_RF and XMEGA: Use \ref IOPORT_CREATE_PIN macro with port definitions
 *              PORTA, PORTB ...
 *     - UC3: Most convenient to pick up the device header file pin definition
 *            and us it directly. E.g.: AVR32_PIN_PB06
 *     - SAM: Most convenient to pick up the device header file pin definition
 *            and us it directly. E.g.: PIO_PA5_IDX<br>
 *            \ref IOPORT_CREATE_PIN can also be used with port definitions
 *            PIOA, PIOB ...
 * -# Initialize the ioport service. This typically enables the IO module if
 *    needed.
 *   - \code ioport_init(); \endcode
 * -# Set the LED GPIO as output:
 *   - \code ioport_set_pin_dir(MY_LED, IOPORT_DIR_OUTPUT); \endcode
 * -# Set the button GPIO as input:
 *   - \code ioport_set_pin_dir(MY_BUTTON, IOPORT_DIR_INPUT); \endcode
 * -# Enable pull-up for the button GPIO:
 *   - \code ioport_set_pin_mode(MY_BUTTON, IOPORT_MODE_PULLUP); \endcode
 *
 * \section ioport_quickstart_basic_usage Usage steps
 *
 * \subsection ioport_quickstart_basic_usage_code Example code
 * \code
	 bool value;

	 value = ioport_get_pin_level(MY_BUTTON);
	 ioport_set_pin_level(MY_LED, value);
\endcode
 *
 * \subsection ioport_quickstart_basic_usage_flow Workflow
 * -# Define a boolean variable for state storage:
 *   - \code bool value; \endcode
 * -# Read out the button level into variable value:
 *   - \code value = ioport_get_pin_level(MY_BUTTON); \endcode
 * -# Set the LED to read out value from the button:
 *   - \code ioport_set_pin_level(MY_LED, value); \endcode
 *
 * \section ioport_quickstart_advanced Advanced use cases
 * - \subpage ioport_quickstart_use_case_1 : Port access
 */

/**
 * \page ioport_quickstart_use_case_1 Advanced use case doing port access
 *
 * In this case we will read out the pins from one whole port and write the
 * read value to another port.
 *
 * \section ioport_quickstart_use_case_1_setup Setup steps
 *
 * \subsection ioport_quickstart_use_case_1_setup_code Example code
 * \code
	 #define IN_PORT  IOPORT_PORTA
	 #define OUT_PORT IOPORT_PORTB
	 #define MASK     0x00000060

	 ioport_init();

	 ioport_set_port_dir(IN_PORT, MASK, IOPORT_DIR_INPUT);
	 ioport_set_port_dir(OUT_PORT, MASK, IOPORT_DIR_OUTPUT);
\endcode
 *
 * \subsection ioport_quickstart_basic_setup_flow Workflow
 * -# It's useful to give the ports symbolic names:
 *   - \code
	#define IN_PORT  IOPORT_PORTA
	#define OUT_PORT IOPORT_PORTB
\endcode
 *   - \note The port names differ between architectures:
 *     - MEGA_RF, MEGA and XMEGA: There are predefined names for ports: IOPORT_PORTA,
 *              IOPORT_PORTB ...
 *     - UC3: Use the index value of the different IO blocks: 0, 1 ...
 *     - SAM: There are predefined names for ports: IOPORT_PIOA, IOPORT_PIOB
 *            ...
 * -# Also useful to define a mask for the bits to work with:
 *     - \code #define MASK     0x00000060 \endcode
 * -# Initialize the ioport service. This typically enables the IO module if
 *    needed.
 *   - \code ioport_init(); \endcode
 * -# Set one of the ports as input:
 *   - \code ioport_set_pin_dir(IN_PORT, MASK, IOPORT_DIR_INPUT); \endcode
 * -# Set the other port as output:
 *   - \code ioport_set_pin_dir(OUT_PORT, MASK, IOPORT_DIR_OUTPUT); \endcode
 *
 * \section ioport_quickstart_basic_usage Usage steps
 *
 * \subsection ioport_quickstart_basic_usage_code Example code
 * \code
	 ioport_port_mask_t value;

	 value = ioport_get_port_level(IN_PORT, MASK);
	 ioport_set_port_level(OUT_PORT, MASK, value);
\endcode
 *
 * \subsection ioport_quickstart_basic_usage_flow Workflow
 * -# Define a variable for port date storage:
 *   - \code ioport_port_mask_t value; \endcode
 * -# Read out from one port:
 *   - \code value = ioport_get_port_level(IN_PORT, MASK); \endcode
 * -# Put the read data out on the other port:
 *   - \code ioport_set_port_level(OUT_PORT, MASK, value); \endcode
 */

#ifdef __cplusplus
}
#endif

#endif /* IOPORT_H */
