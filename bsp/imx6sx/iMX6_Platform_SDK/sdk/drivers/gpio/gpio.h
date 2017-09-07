/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * @file gpio.h
 * @brief  Defines related to the GPIO controller and used by gpio.c
 * @ingroup diag_gpio
 */

#ifndef __GPIO_H__
#define __GPIO_H__


//! @addtogroup diag_gpio
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Available GPIO ports.
typedef enum {
	GPIO_NONE  = 0,
	GPIO_PORT1 = 1,
    GPIO_PORT2 = 2,
    GPIO_PORT3 = 3,
    GPIO_PORT4 = 4,
    GPIO_PORT5 = 5,
    GPIO_PORT6 = 6,
    GPIO_PORT7 = 7,
} GPIO_PORT;

//! @name GPIO bitfield values
//@{
#define GPIO_GDIR_INPUT             0   //!< GPIO pin is input
#define GPIO_GDIR_OUTPUT            1   //!< GPIO pin is output

#define GPIO_LOW_LEVEL              0   //!< GPIO pin is low
#define GPIO_HIGH_LEVEL             1   //!< GPIO pin is high

#define GPIO_ICR_LOW_LEVEL          0   //!< Interrupt is low-level
#define GPIO_ICR_HIGH_LEVEL         1   //!< Interrupt is high-level
#define GPIO_ICR_RISE_EDGE          2   //!< Interrupt is rising edge
#define GPIO_ICR_FALL_EDGE          3   //!< Interrupt is falling edge

#define GPIO_IMR_MASKED             0   //!< Interrupt is masked
#define GPIO_IMR_UNMASKED           1   //!< Interrupt is unmasked

#define GPIO_ISR_NOT_ASSERTED       0   //!< Interrupt is not asserted
#define GPIO_ISR_ASSERTED           1   //!< Interrupt is asserted

#define GPIO_EDGE_SEL_DISABLE       0   //!< Edge select is disabled
#define GPIO_EDGE_SEL_ENABLE        1   //!< Edge select is enabled
//@}

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Returns the number of available GPIO instances.
 * @return An integer number of GPIO instances on this hardware.
 */
int32_t gpio_get_port_count(void);

/*!
 * @brief Sets a GPIO pin to GPIO mode in the IOMUX controller.
 *
 * @retval SUCCESS
 * @retval INVALID_PARAMETER
 */
int gpio_set_gpio(int32_t port, int32_t pin);

/*!
 * @brief Sets the GPIO direction for the specified pin.
 *
 * @param   port GPIO module instance, GPIO_PORT1, GPIO_PORT2, ... gpio_get_port_count().
 * @param   pin GPIO pin 0 to 31.
 * @param   dir Direction for the pin. GPIO_GDIR_INPUT(0) or GPIO_GDIR_OUTPUT(1).
 * @return  INVALID_PARAMETER(-1)
 */
int32_t gpio_set_direction(int32_t port, int32_t pin, int32_t dir);

/*!
 * @brief Returns the current direction for the specified pin.
 *
 * @param   port GPIO module instance, GPIO_PORT1, GPIO_PORT2, ... gpio_get_port_count().
 * @param   pin GPIO pin 0 to 31.
 * @retval GPIO_GDIR_INPUT The pin is currently set as an input.
 * @retval GPIO_GDIR_OUTPUT The pin is currently set as an output.
 */
int32_t gpio_get_direction(int32_t port, int32_t pin);

/*!
 * @brief Sets the GPIO level(high or low) for the specified pin.
 *
 * @warning Fails if pin is not configured as an output.
 *
 * @param   port GPIO module instance, GPIO_PORT1, GPIO_PORT2, ... gpio_get_port_count().
 * @param   pin GPIO pin 0 to 31.
 * @param   level GPIO_LOW_LEVEL(0), GPIO_HIGH_LEVEL(1)
 * @return  INVALID_PARAMETER(-1)
 */
int32_t gpio_set_level(int32_t port, int32_t pin, uint32_t level);

/*!
 *	Gets the GPIO level(high or low) for the specified pin.
 *
 *	@note Returns level for both input and output configured pins.
 *
 * @param   port GPIO module instance, GPIO_PORT1, GPIO_PORT2, ... gpio_get_port_count().
 * @param   pin GPIO pin 0 to 31.
 * @retval  INVALID_PARAMETER(-1),
 * @retval  GPIO_LOW_LEVEL(0),
 * @retval  GPIO_HIGH_LEVEL(1)
*/
int32_t gpio_get_level(int32_t port, int32_t pin);

/*!
 * @brief Configures the interrupt condition for the specified GPIO input pin.
 *
 * @param   port GPIO module instance, GPIO_PORT1, GPIO_PORT2, ... gpio_get_port_count().
 * @param   pin GPIO pin 0 to 31.
 * @param   config Interrupt condition for the pin. GPIO_ICR_LOW_LEVEL(0), GPIO_ICR_HIGH_LEVEL(1),
 *                   GPIO_ICR_RISE_EDGE(2), GPIO_ICR_FALL_EDGE(3)
 * @return INVALID_PARAMETER(-1)
 */
int32_t gpio_set_interrupt_config(int32_t port, int32_t pin, int32_t config);

/*!
 * @brief Enables/Disables the interrupt for the specified GPIO input pin.
 *
 * @param   port GPIO module instance, GPIO_PORT1, GPIO_PORT2, ... gpio_get_port_count().
 * @param   pin GPIO pin 0 to 31.
 * @param   mask interrupt mask for the pin. GPIO_IMR_MASKED(0), GPIO_IMR_UNMASKED(1)
 * @return  INVALID_PARAMETER(-1)
 */
int32_t gpio_set_interrupt_mask(int32_t port, int32_t pin, int32_t mask);

/*!
 * @brief Gets the GPIO interrupt status for the specified pin.
 *
 * @param   port GPIO module instance, GPIO_PORT1, GPIO_PORT2, ... gpio_get_port_count().
 * @param   pin GPIO pin 0 to 31.
 * @return  INVALID_PARAMETER(-1), GPIO_ISR_NOT_ASSERTED(0), GPIO_ISR_ASSERTED(1)
 */
int32_t gpio_get_interrupt_status(int32_t port, int32_t pin);

/*!
 * @brief Clears the GPIO interrupt for the specified pin.
 *
 * @param   port GPIO module instance, GPIO_PORT1, GPIO_PORT2, ... gpio_get_port_count().
 * @param   pin GPIO pin 0 to 31.
 * @return  INVALID_PARAMETER(-1)
 */
int32_t gpio_clear_interrupt(int32_t port, int32_t pin);

#if defined(__cplusplus)
}
#endif

//! @}

#endif //__GPIO_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
