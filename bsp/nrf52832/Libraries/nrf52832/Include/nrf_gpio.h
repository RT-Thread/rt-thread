#ifndef NRF_GPIO_H__
#define NRF_GPIO_H__

#include "nrf.h"
#include <stdbool.h>

/**
 * @defgroup nrf_gpio GPIO abstraction
 * @{
 * @ingroup nrf_drivers
 * @brief GPIO pin abstraction and port abstraction for reading and writing byte-wise to GPIO ports.
 *
 * Here, the GPIO ports are defined as follows:
 * - Port 0 -> pin 0-7
 * - Port 1 -> pin 8-15
 * - Port 2 -> pin 16-23
 * - Port 3 -> pin 24-31
 */

#define NUMBER_OF_PINS 32

/**
 * @brief Enumerator used for selecting between port 0 - 3.
 */
typedef enum
{
    NRF_GPIO_PORT_SELECT_PORT0 = 0,           ///<  Port 0 (GPIO pin 0-7)
    NRF_GPIO_PORT_SELECT_PORT1,               ///<  Port 1 (GPIO pin 8-15)
    NRF_GPIO_PORT_SELECT_PORT2,               ///<  Port 2 (GPIO pin 16-23)
    NRF_GPIO_PORT_SELECT_PORT3,               ///<  Port 3 (GPIO pin 24-31)
} nrf_gpio_port_select_t;

/**
 * @brief Enumerator used for setting the direction of a GPIO port.
 */
typedef enum
{
    NRF_GPIO_PORT_DIR_OUTPUT,       ///<  Output
    NRF_GPIO_PORT_DIR_INPUT         ///<  Input
} nrf_gpio_port_dir_t;

/**
 * @brief Pin direction definitions.
 */
typedef enum
{
    NRF_GPIO_PIN_DIR_INPUT  = GPIO_PIN_CNF_DIR_Input,   ///< Input
    NRF_GPIO_PIN_DIR_OUTPUT = GPIO_PIN_CNF_DIR_Output   ///< Output
} nrf_gpio_pin_dir_t;

/**
 * @brief Connection of input buffer
 */
typedef enum
{
    NRF_GPIO_PIN_INPUT_CONNECT    = GPIO_PIN_CNF_INPUT_Connect,   ///< Connect input buffer
    NRF_GPIO_PIN_INPUT_DISCONNECT = GPIO_PIN_CNF_INPUT_Disconnect ///< Disconnect input buffer
} nrf_gpio_pin_input_t;

/**
 * @brief Enumerator used for selecting the pin to be pulled down or up at the time of pin configuration
 */
typedef enum
{
    NRF_GPIO_PIN_NOPULL   = GPIO_PIN_CNF_PULL_Disabled,                 ///<  Pin pullup resistor disabled
    NRF_GPIO_PIN_PULLDOWN = GPIO_PIN_CNF_PULL_Pulldown,                 ///<  Pin pulldown resistor enabled
    NRF_GPIO_PIN_PULLUP   = GPIO_PIN_CNF_PULL_Pullup,                   ///<  Pin pullup resistor enabled
} nrf_gpio_pin_pull_t;

/**
 * @brief Enumerator used for selecting output drive mode
 */
typedef enum
{
    NRF_GPIO_PIN_S0S1 = GPIO_PIN_CNF_DRIVE_S0S1, ///< !< Standard '0', standard '1'
    NRF_GPIO_PIN_H0S1 = GPIO_PIN_CNF_DRIVE_H0S1, ///< !< High drive '0', standard '1'
    NRF_GPIO_PIN_S0H1 = GPIO_PIN_CNF_DRIVE_S0H1, ///< !< Standard '0', high drive '1'
    NRF_GPIO_PIN_H0H1 = GPIO_PIN_CNF_DRIVE_H0H1, ///< !< High drive '0', high 'drive '1''
    NRF_GPIO_PIN_D0S1 = GPIO_PIN_CNF_DRIVE_D0S1, ///< !< Disconnect '0' standard '1'
    NRF_GPIO_PIN_D0H1 = GPIO_PIN_CNF_DRIVE_D0H1, ///< !< Disconnect '0', high drive '1'
    NRF_GPIO_PIN_S0D1 = GPIO_PIN_CNF_DRIVE_S0D1, ///< !< Standard '0'. disconnect '1'
    NRF_GPIO_PIN_H0D1 = GPIO_PIN_CNF_DRIVE_H0D1, ///< !< High drive '0', disconnect '1'
} nrf_gpio_pin_drive_t;

/**
 * @brief Enumerator used for selecting the pin to sense high or low level on the pin input.
 */
typedef enum
{
    NRF_GPIO_PIN_NOSENSE    = GPIO_PIN_CNF_SENSE_Disabled,              ///<  Pin sense level disabled.
    NRF_GPIO_PIN_SENSE_LOW  = GPIO_PIN_CNF_SENSE_Low,                   ///<  Pin sense low level.
    NRF_GPIO_PIN_SENSE_HIGH = GPIO_PIN_CNF_SENSE_High,                  ///<  Pin sense high level.
} nrf_gpio_pin_sense_t;


/**
 * @brief Function for configuring the GPIO pin range as outputs with normal drive strength.
 *        This function can be used to configure pin range as simple output with gate driving GPIO_PIN_CNF_DRIVE_S0S1 (normal cases).
 *
 * @param pin_range_start specifies the start number (inclusive) in the range of pin numbers to be configured (allowed values 0-30)
 *
 * @param pin_range_end specifies the end number (inclusive) in the range of pin numbers to be configured (allowed values 0-30)
 *
 * @note For configuring only one pin as output use @ref nrf_gpio_cfg_output
 *       Sense capability on the pin is disabled, and input is disconnected from the buffer as the pins are configured as output.
 */
__STATIC_INLINE void nrf_gpio_range_cfg_output(uint32_t pin_range_start, uint32_t pin_range_end);

/**
 * @brief Function for configuring the GPIO pin range as inputs with given initial value set, hiding inner details.
 *        This function can be used to configure pin range as simple input.
 *
 * @param pin_range_start specifies the start number (inclusive) in the range of pin numbers to be configured (allowed values 0-30)
 *
 * @param pin_range_end specifies the end number (inclusive) in the range of pin numbers to be configured (allowed values 0-30)
 *
 * @param pull_config State of the pin range pull resistor (no pull, pulled down or pulled high)
 *
 * @note  For configuring only one pin as input use @ref nrf_gpio_cfg_input
 *        Sense capability on the pin is disabled, and input is connected to buffer so that the GPIO->IN register is readable
 */
__STATIC_INLINE void nrf_gpio_range_cfg_input(uint32_t pin_range_start, uint32_t pin_range_end, nrf_gpio_pin_pull_t pull_config);

/**
 * @brief Pin configuration function
 *
 * The main pin configuration function.
 * This function allows to set any aspect in PIN_CNF register.
 * @param pin_number Specifies the pin number (allowed values 0-31).
 * @param dir   Pin direction
 * @param input Connect or disconnect input buffer
 * @param pull  Pull configuration
 * @param drive Drive configuration
 * @param sense Pin sensing mechanism
 */
__STATIC_INLINE void nrf_gpio_cfg(
        uint32_t             pin_number,
        nrf_gpio_pin_dir_t   dir,
        nrf_gpio_pin_input_t input,
        nrf_gpio_pin_pull_t  pull,
        nrf_gpio_pin_drive_t drive,
        nrf_gpio_pin_sense_t sense);

/**
 * @brief Function for configuring the given GPIO pin number as output with given initial value set, hiding inner details.
 *        This function can be used to configure pin range as simple input with gate driving GPIO_PIN_CNF_DRIVE_S0S1 (normal cases).
 *
 * @param pin_number specifies the pin number (allowed values 0-31)
 *
 * @note  Sense capability on the pin is disabled, and input is disconnected from the buffer as the pins are configured as output.
 */
__STATIC_INLINE void nrf_gpio_cfg_output(uint32_t pin_number);

/**
 * @brief Function for configuring the given GPIO pin number as input with given initial value set, hiding inner details.
 *        This function can be used to configure pin range as simple input with gate driving GPIO_PIN_CNF_DRIVE_S0S1 (normal cases).
 *
 * @param pin_number Specifies the pin number (allowed values 0-30).
 * @param pull_config State of the pin range pull resistor (no pull, pulled down or pulled high).
 *
 * @note  Sense capability on the pin is disabled, and input is connected to buffer so that the GPIO->IN register is readable
 */
__STATIC_INLINE void nrf_gpio_cfg_input(uint32_t pin_number, nrf_gpio_pin_pull_t pull_config);

/**
 * @brief Function for reseting pin configuration to its default state.
 *
 * @param pin_number Specifies the pin number (allowed values 0-31).
 */
__STATIC_INLINE void nrf_gpio_cfg_default(uint32_t pin_number);

/**
 * @brief Function for configuring the given GPIO pin number as a watcher. Only input is connected.
 *
 * @param pin_number Specifies the pin number (allowed values 0-31).
 *
 */
__STATIC_INLINE void nrf_gpio_cfg_watcher(uint32_t pin_number);

/**
 * @brief Function for disconnecting input for the given GPIO.
 *
 * @param pin_number Specifies the pin number (allowed values 0-31).
 *
 */
__STATIC_INLINE void nrf_gpio_input_disconnect(uint32_t pin_number);

/**
 * @brief Function for configuring the given GPIO pin number as input with given initial value set, hiding inner details.
 *        This function can be used to configure pin range as simple input with gate driving GPIO_PIN_CNF_DRIVE_S0S1 (normal cases).
 *        Sense capability on the pin is configurable, and input is connected to buffer so that the GPIO->IN register is readable.
 *
 * @param pin_number   Specifies the pin number (allowed values 0-30).
 * @param pull_config  State of the pin pull resistor (no pull, pulled down or pulled high).
 * @param sense_config Sense level of the pin (no sense, sense low or sense high).
 */
__STATIC_INLINE void nrf_gpio_cfg_sense_input(uint32_t pin_number, nrf_gpio_pin_pull_t pull_config, nrf_gpio_pin_sense_t sense_config);

/**
 * @brief Function for configuring sense level for the given GPIO.
 *
 * @param pin_number   Specifies the pin number of gpio pin numbers to be configured (allowed values 0-30).
 * @param sense_config Sense configuration.
 *
 */
__STATIC_INLINE void nrf_gpio_cfg_sense_set(uint32_t pin_number, nrf_gpio_pin_sense_t sense_config);

/**
 * @brief Function for setting the direction for a GPIO pin.
 *
 * @param pin_number specifies the pin number [0:31] for which to
 * set the direction.
 *
 * @param direction specifies the direction
 */
__STATIC_INLINE void nrf_gpio_pin_dir_set(uint32_t pin_number, nrf_gpio_pin_dir_t direction);

/**
 * @brief Function for setting a GPIO pin.
 *
 * Note that the pin must be configured as an output for this
 * function to have any effect.
 *
 * @param pin_number specifies the pin number [0:31] to
 * set.
 */
__STATIC_INLINE void nrf_gpio_pin_set(uint32_t pin_number);

/**
 * @brief Function for clearing a GPIO pin.
 *
 * Note that the pin must be configured as an output for this
 * function to have any effect.
 *
 * @param pin_number specifies the pin number [0:31] to
 * clear.
 */
__STATIC_INLINE void nrf_gpio_pin_clear(uint32_t pin_number);

/**
 * @brief Function for toggling a GPIO pin.
 *
 * Note that the pin must be configured as an output for this
 * function to have any effect.
 *
 * @param pin_number specifies the pin number [0:31] to
 * toggle.
 */
__STATIC_INLINE void nrf_gpio_pin_toggle(uint32_t pin_number);

/**
 * @brief Function for writing a value to a GPIO pin.
 *
 * Note that the pin must be configured as an output for this
 * function to have any effect.
 *
 * @param pin_number specifies the pin number [0:31] to
 * write.
 *
 * @param value specifies the value to be written to the pin.
 * @arg 0 clears the pin
 * @arg >=1 sets the pin.
 */
__STATIC_INLINE void nrf_gpio_pin_write(uint32_t pin_number, uint32_t value);

/**
 * @brief Function for reading the input level of a GPIO pin.
 *
 * Note that the pin must have input connected for the value
 * returned from this function to be valid.
 *
 * @param pin_number specifies the pin number [0:31] to
 * read.
 *
 * @return
 * @retval 0 if the pin input level is low.
 * @retval 1 if the pin input level is high.
 * @retval > 1 should never occur.
 */
__STATIC_INLINE uint32_t nrf_gpio_pin_read(uint32_t pin_number);

/**
 * @brief Function for reading the input level of all GPIO pins.
 *
 * Note that the pin must have input connected for the value
 * returned from this function to be valid.
 *
 * @retval Status of input of all pins
 */
__STATIC_INLINE uint32_t nrf_gpio_pins_read(void);

/**
 * @brief Function for reading the sense configuration of a GPIO pin.
 *
 * @param pin_number specifies the pin number [0:31] to
 * read.
 *
 * @retval Sense configuration
 */
__STATIC_INLINE nrf_gpio_pin_sense_t nrf_gpio_pin_sense_get(uint32_t pin_number);

/**
 * @brief Generic function for writing a single byte of a 32 bit word at a given
 * address.
 *
 * This function should not be called from outside the nrf_gpio
 * abstraction layer.
 *
 * @param word_address is the address of the word to be written.
 *
 * @param byte_no is the word byte number (0-3) to be written.
 *
 * @param value is the value to be written to byte "byte_no" of word
 * at address "word_address"
 */
__STATIC_INLINE void nrf_gpio_word_byte_write(volatile uint32_t * word_address, uint8_t byte_no, uint8_t value);

/**
 * @brief Generic function for reading a single byte of a 32 bit word at a given
 * address.
 *
 * This function should not be called from outside the nrf_gpio
 * abstraction layer.
 *
 * @param word_address is the address of the word to be read.
 *
 * @param byte_no is the byte number (0-3) of the word to be read.
 *
 * @return byte "byte_no" of word at address "word_address".
 */
__STATIC_INLINE uint8_t nrf_gpio_word_byte_read(const volatile uint32_t* word_address, uint8_t byte_no);

/**
 * @brief Function for setting the direction of a port.
 *
 * @param port is the port for which to set the direction.
 *
 * @param dir direction to be set for this port.
 */
__STATIC_INLINE void nrf_gpio_port_dir_set(nrf_gpio_port_select_t port, nrf_gpio_port_dir_t dir);

/**
 * @brief Function for reading a GPIO port.
 *
 * @param port is the port to read.
 *
 * @return the input value on this port.
 */
__STATIC_INLINE uint8_t nrf_gpio_port_read(nrf_gpio_port_select_t port);

/**
 * @brief Function for writing to a GPIO port.
 *
 * @param port is the port to write.
 *
 * @param value is the value to write to this port.
 *
 * @sa nrf_gpio_port_dir_set()
 */
__STATIC_INLINE void nrf_gpio_port_write(nrf_gpio_port_select_t port, uint8_t value);

/**
 * @brief Function for setting individual pins on GPIO port.
 *
 * @param port is the port for which to set the pins.
 *
 * @param set_mask is a mask specifying which pins to set. A bit
 * set to 1 indicates that the corresponding port pin shall be
 * set.
 *
 * @sa nrf_gpio_port_dir_set()
 */
__STATIC_INLINE void nrf_gpio_port_set(nrf_gpio_port_select_t port, uint8_t set_mask);

/**
 * @brief Function for clearing individual pins on GPIO port.
 *
 * @param port is the port for which to clear the pins.
 *
 * @param clr_mask is a mask specifying which pins to clear. A bit
 * set to 1 indicates that the corresponding port pin shall be
 * cleared.
 *
 * @sa nrf_gpio_port_dir_set()
 */
__STATIC_INLINE void nrf_gpio_port_clear(nrf_gpio_port_select_t port, uint8_t clr_mask);

#ifndef SUPPRESS_INLINE_IMPLEMENTATION
__STATIC_INLINE void nrf_gpio_range_cfg_output(uint32_t pin_range_start, uint32_t pin_range_end)
{
    /*lint -e{845} // A zero has been given as right argument to operator '|'" */
    for (; pin_range_start <= pin_range_end; pin_range_start++)
    {
        nrf_gpio_cfg_output(pin_range_start);
    }
}

__STATIC_INLINE void nrf_gpio_range_cfg_input(uint32_t pin_range_start, uint32_t pin_range_end, nrf_gpio_pin_pull_t pull_config)
{
    /*lint -e{845} // A zero has been given as right argument to operator '|'" */
    for (; pin_range_start <= pin_range_end; pin_range_start++)
    {
        nrf_gpio_cfg_input(pin_range_start, pull_config);
    }
}

__STATIC_INLINE void nrf_gpio_cfg(
        uint32_t             pin_number,
        nrf_gpio_pin_dir_t   dir,
        nrf_gpio_pin_input_t input,
        nrf_gpio_pin_pull_t  pull,
        nrf_gpio_pin_drive_t drive,
        nrf_gpio_pin_sense_t sense)
{
    NRF_GPIO->PIN_CNF[pin_number] = ((uint32_t)dir   << GPIO_PIN_CNF_DIR_Pos)
                                  | ((uint32_t)input << GPIO_PIN_CNF_INPUT_Pos)
                                  | ((uint32_t)pull  << GPIO_PIN_CNF_PULL_Pos)
                                  | ((uint32_t)drive << GPIO_PIN_CNF_DRIVE_Pos)
                                  | ((uint32_t)sense << GPIO_PIN_CNF_SENSE_Pos);
}

__STATIC_INLINE void nrf_gpio_cfg_output(uint32_t pin_number)
{
    nrf_gpio_cfg(
            pin_number,
            NRF_GPIO_PIN_DIR_OUTPUT,
            NRF_GPIO_PIN_INPUT_DISCONNECT,
            NRF_GPIO_PIN_NOPULL,
            NRF_GPIO_PIN_S0S1,
            NRF_GPIO_PIN_NOSENSE);
}

__STATIC_INLINE void nrf_gpio_cfg_input(uint32_t pin_number, nrf_gpio_pin_pull_t pull_config)
{
    nrf_gpio_cfg(
            pin_number,
            NRF_GPIO_PIN_DIR_INPUT,
            NRF_GPIO_PIN_INPUT_CONNECT,
            pull_config,
            NRF_GPIO_PIN_S0S1,
            NRF_GPIO_PIN_NOSENSE);
}

__STATIC_INLINE void nrf_gpio_cfg_default(uint32_t pin_number)
{
    nrf_gpio_cfg(
            pin_number,
            NRF_GPIO_PIN_DIR_INPUT,
            NRF_GPIO_PIN_INPUT_DISCONNECT,
            NRF_GPIO_PIN_NOPULL,
            NRF_GPIO_PIN_S0S1,
            NRF_GPIO_PIN_NOSENSE);
}

__STATIC_INLINE void nrf_gpio_cfg_watcher(uint32_t pin_number)
{
    /*lint -e{845} // A zero has been given as right argument to operator '|'" */
    uint32_t cnf = NRF_GPIO->PIN_CNF[pin_number] & ~GPIO_PIN_CNF_INPUT_Msk;
    NRF_GPIO->PIN_CNF[pin_number] = cnf | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos);
}

__STATIC_INLINE void nrf_gpio_input_disconnect(uint32_t pin_number)
{
    /*lint -e{845} // A zero has been given as right argument to operator '|'" */
    uint32_t cnf = NRF_GPIO->PIN_CNF[pin_number] & ~GPIO_PIN_CNF_INPUT_Msk;
    NRF_GPIO->PIN_CNF[pin_number] = cnf | (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos);
}

__STATIC_INLINE void nrf_gpio_cfg_sense_input(uint32_t pin_number, nrf_gpio_pin_pull_t pull_config, nrf_gpio_pin_sense_t sense_config)
{
    nrf_gpio_cfg(
            pin_number,
            NRF_GPIO_PIN_DIR_INPUT,
            NRF_GPIO_PIN_INPUT_CONNECT,
            pull_config,
            NRF_GPIO_PIN_S0S1,
            sense_config);
}

__STATIC_INLINE void nrf_gpio_cfg_sense_set(uint32_t pin_number, nrf_gpio_pin_sense_t sense_config)
{
    /*lint -e{845} // A zero has been given as right argument to operator '|'" */
    //uint32_t cnf = NRF_GPIO->PIN_CNF[pin_number] & ~GPIO_PIN_CNF_SENSE_Msk;
    NRF_GPIO->PIN_CNF[pin_number] &= ~GPIO_PIN_CNF_SENSE_Msk;
    NRF_GPIO->PIN_CNF[pin_number] |= (sense_config << GPIO_PIN_CNF_SENSE_Pos);
}

__STATIC_INLINE void nrf_gpio_pin_dir_set(uint32_t pin_number, nrf_gpio_pin_dir_t direction)
{
    if(direction == NRF_GPIO_PIN_DIR_INPUT)
    {
        nrf_gpio_cfg(
                pin_number,
                NRF_GPIO_PIN_DIR_INPUT,
                NRF_GPIO_PIN_INPUT_CONNECT,
                NRF_GPIO_PIN_NOPULL,
                NRF_GPIO_PIN_S0S1,
                NRF_GPIO_PIN_NOSENSE);
    }
    else
    {
        NRF_GPIO->DIRSET = (1UL << pin_number);
    }
}

__STATIC_INLINE void nrf_gpio_pin_set(uint32_t pin_number)
{
    NRF_GPIO->OUTSET = (1UL << pin_number);
}

__STATIC_INLINE void nrf_gpio_pin_clear(uint32_t pin_number)
{
    NRF_GPIO->OUTCLR = (1UL << pin_number);
}

__STATIC_INLINE void nrf_gpio_pin_toggle(uint32_t pin_number)
{
    const uint32_t pin_bit   = 1UL << pin_number;
    const uint32_t pin_state = ((NRF_GPIO->OUT >> pin_number) & 1UL);

    if (pin_state == 0)
    {
        // Current state low, set high.
        NRF_GPIO->OUTSET = pin_bit;
    }
    else
    {
        // Current state high, set low.
        NRF_GPIO->OUTCLR = pin_bit;
    }
}

__STATIC_INLINE void nrf_gpio_pin_write(uint32_t pin_number, uint32_t value)
{
    if (value == 0)
    {
        nrf_gpio_pin_clear(pin_number);
    }
    else
    {
        nrf_gpio_pin_set(pin_number);
    }
}

__STATIC_INLINE uint32_t nrf_gpio_pin_read(uint32_t pin_number)
{
    return  ((NRF_GPIO->IN >> pin_number) & 1UL);
}

__STATIC_INLINE uint32_t nrf_gpio_pins_read(void)
{
    return NRF_GPIO->IN;
}

__STATIC_INLINE nrf_gpio_pin_sense_t nrf_gpio_pin_sense_get(uint32_t pin_number)
{
    return (nrf_gpio_pin_sense_t)((NRF_GPIO->PIN_CNF[pin_number] & GPIO_PIN_CNF_SENSE_Msk) >> GPIO_PIN_CNF_SENSE_Pos);
}

__STATIC_INLINE void nrf_gpio_word_byte_write(volatile uint32_t * word_address, uint8_t byte_no, uint8_t value)
{
    *((volatile uint8_t*)(word_address) + byte_no) = value;
}

__STATIC_INLINE uint8_t nrf_gpio_word_byte_read(const volatile uint32_t* word_address, uint8_t byte_no)
{
    return (*((const volatile uint8_t*)(word_address) + byte_no));
}

__STATIC_INLINE void nrf_gpio_port_dir_set(nrf_gpio_port_select_t port, nrf_gpio_port_dir_t dir)
{
    if (dir == NRF_GPIO_PORT_DIR_OUTPUT)
    {
        nrf_gpio_word_byte_write(&NRF_GPIO->DIRSET, port, 0xFF);
    }
    else
    {
        nrf_gpio_range_cfg_input(port*8, (port+1)*8-1, NRF_GPIO_PIN_NOPULL);
    }
}

__STATIC_INLINE uint8_t nrf_gpio_port_read(nrf_gpio_port_select_t port)
{
    return nrf_gpio_word_byte_read(&NRF_GPIO->IN, port);
}

__STATIC_INLINE void nrf_gpio_port_write(nrf_gpio_port_select_t port, uint8_t value)
{
    nrf_gpio_word_byte_write(&NRF_GPIO->OUT, port, value);
}

__STATIC_INLINE void nrf_gpio_port_set(nrf_gpio_port_select_t port, uint8_t set_mask)
{
    nrf_gpio_word_byte_write(&NRF_GPIO->OUTSET, port, set_mask);
}

__STATIC_INLINE void nrf_gpio_port_clear(nrf_gpio_port_select_t port, uint8_t clr_mask)
{
    nrf_gpio_word_byte_write(&NRF_GPIO->OUTCLR, port, clr_mask);
}
#endif //SUPPRESS_INLINE_IMPLEMENTATION
/** @} */

#endif
