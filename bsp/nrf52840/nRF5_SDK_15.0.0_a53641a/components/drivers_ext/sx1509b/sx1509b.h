/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#ifndef SX1509B_H
#define SX1509B_H

#include "nrf_twi_sensor.h"
#include "sx1509b_internal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Possible sensor addresses.
 */
#define SX1509B_BASE_ADDRESS_FIRST      0x3Eu
#define SX1509B_BASE_ADDRESS_SECOND     0x3Fu
#define SX1509B_BASE_ADDRESS_THIRD      0x70u
#define SX1509B_BASE_ADDRESS_FOURTH     0x71u

/**
 * @brief Led driver registers.
 */
typedef enum
{
    SX1509B_LED_DRIVER_T_ON,
    SX1509B_LED_DRIVER_I_ON,
    SX1509B_LED_DRIVER_OFF,
    SX1509B_LED_DRIVER_T_RISE,
    SX1509B_LED_DRIVER_T_FALL
} sx1509b_led_driver_set_t;


/**
 * @brief Pin direction setting.
 */
typedef enum
{
    SX1509B_PIN_DIR_OUTPUT,
    SX1509B_PIN_DIR_INPUT
} sx1509b_pin_dir_t;

/**
 * @brief Pin output setting.
 */
typedef enum
{
    SX1509B_PIN_CLR,
    SX1509B_PIN_SET
} sx1509b_pin_set_t;

/**
 * @brief Pin pull setting.
 */
typedef enum
{
    SX1509B_PIN_NOPULL,
    SX1509B_PIN_PULLDOWN,
    SX1509B_PIN_PULLUP
} sx1509b_pin_pull_t;

/**
 * @brief Pin sense setting.
 */
typedef enum
{
    SX1509B_PIN_NOSENSE,
    SX1509B_PIN_SENSE_RISING,
    SX1509B_PIN_SENSE_FALLING,
    SX1509B_PIN_SENSE_BOTH
} sx1509b_pin_sense_t;

/**
 * @brief Port operation setting.
 *
 * SX1509B_PORT_WRITE - mask is written to the port.
 * SX1509B_PORT_CLEAR - positive bits in mask are cleared in port.
 * SX1509B_PORT_SET   - positive bits in mask are set in port.
 */
typedef enum
{
    SX1509B_PORT_WRITE,
    SX1509B_PORT_CLEAR,
    SX1509B_PORT_SET
} sx1509b_port_op_t;

/**
 * @brief Level shifter setting.
 */
typedef enum
{
    SX1509B_LEVEL_OFF,
    SX1509B_LEVEL_A_TO_B,
    SX1509B_LEVEL_B_TO_A
} sx1509b_level_shift_t;


/**
 * @brief Debounce settings.
 */
typedef enum
{
    SX1509B_DEBOUNCE_0_5MS,
    SX1509B_DEBOUNCE_1MS,
    SX1509B_DEBOUNCE_2MS,
    SX1509B_DEBOUNCE_4MS,
    SX1509B_DEBOUNCE_8MS,
    SX1509B_DEBOUNCE_16MS,
    SX1509B_DEBOUNCE_32MS,
    SX1509B_DEBOUNCE_64MS
} sx1509b_debounce_t;


/**
 * @brief Clock setting.
 */
typedef enum
{
    SX1509B_CLOCK_DISABLED,
    SX1509B_CLOCK_EXTERNAL,
    SX1509B_CLOCK_INTERNAL
} sx1509b_clock_t;


/**
 * @brief Key engine sleep time setting.
 */
typedef enum
{
    SX1509B_KEY_TIME_SLEEP_OFF,
    SX1509B_KEY_TIME_SLEEP_128MS,
    SX1509B_KEY_TIME_SLEEP_256MS,
    SX1509B_KEY_TIME_SLEEP_512MS,
    SX1509B_KEY_TIME_SLEEP_1S,
    SX1509B_KEY_TIME_SLEEP_2S,
    SX1509B_KEY_TIME_SLEEP_4S,
    SX1509B_KEY_TIME_SLEEP_8S
} sx1509b_key_sleep_t;


/**
 * @brief Key engine scan time setting.
 */
typedef enum
{
    SX1509B_KEY_TIME_SCAN_1MS,
    SX1509B_KEY_TIME_SCAN_2MS,
    SX1509B_KEY_TIME_SCAN_4MS,
    SX1509B_KEY_TIME_SCAN_8MS,
    SX1509B_KEY_TIME_SCAN_16MS,
    SX1509B_KEY_TIME_SCAN_32MS,
    SX1509B_KEY_TIME_SCAN_64MS,
    SX1509B_KEY_TIME_SCAN_128MS
} sx1509b_key_scan_t;

/**
 * @brief Macro that defines expander module.
 *
 * @param[in] sx1509b_inst_name Name of the instance to be created.
 * @param[in] instance_count    Number of connected expanders.
 */
#define SX1509B_INSTANCES_DEF_START(sx1509b_inst_name, instance_count)\
    static sx1509b_instance_t sx1509b_inst_name[instance_count]


/**
 * ===============================================================================================
 * @brief General expander utility functions.
 */

/**
 * @brief Function initialising expander module.
 *
 * @param[in] p_instances Pointer to expander module.
 * @param[in] Number of connected expanders.
 */
void sx1509b_init(sx1509b_instance_t * p_instances, uint8_t count);

/**
 * @brief Function adding expander instance.
 *
 * @note Should be called for every connected expander.
 *       Order of calls define order of pins and ports.
 *
 * @param[in] p_twi_sensor   Pointer to common sensor instance. @ref NRF_TWI_SENSOR_DEF
 * @param[in] sensor_address Address of expander on I2C bus.
 *
 * @retval NRF_ERROR_MODULE_NOT_INITIALIZED Returned if expander module wasn't initialised
 * @retval NRF_ERROR_STORAGE_FULL           Returned if trying to add more instances than defined.
 * @retval other                            Return error code from nrf_twi_sensor
 *                                          @ref nrf_twi_sensor_write
 */
ret_code_t sx1509b_add_instance(nrf_twi_sensor_t * p_twi_sensor, uint8_t sensor_address);

/**
 * @brief Function for writing current configuration to expander.
 *
 * @param[in] instance_num Number of expander, order is the same as sx1509b_add_instance calls.
 *
 * @retval NRF_ERROR_INVALID_PARAM Returned if there is no expander with given number.
 * @retval other                   Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t sx1509b_cfg_write(uint8_t instance_num);

/**
 * @brief Function for reading current configuration of expander.
 *
 * @param[in] instance_num Number of expander, order is the same as sx1509b_add_instance calls.
 *
 * @retval NRF_ERROR_INVALID_PARAM Returned if there is no expander with given number.
 * @retval other                   Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t sx1509b_cfg_read(uint8_t instance_num);

/**
 * @brief Function for setting clock configuration.
 *
 * @param instance_num Number of expander.
 * @param source       Clock source.
 * @param oscio_set    Oscio pin setting. True if pin is enabled.
 * @param oscio_freq   Oscio frequency divider. Refer to expander documentation.
 *
 * @retval NRF_ERROR_INVALID_PARAM Returned if there is no expander with given number.
 * @retval other                   Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t sx1509b_clock_set(uint8_t         instance_num,
                             sx1509b_clock_t source,
                             bool            oscio_set,
                             uint8_t         oscio_freq);

/*
 * @brief Function for setting nreset and debounce time.
 *
 * @param instance_num   Number of expander.
 * @param nreset_func    Purpose of nreset pin.
 * @arg   true           Pin resets PWM/Blink/Fade counters.
 * @arg   false          Pin is equivalent to POR.
 * @param debounce_time  Debounce time setting.
 * @param autoclear_nint Autoclear nint and interrupt source registers when pin data is read.
 *                       True if disabled.
 *
 * @retval NRF_ERROR_INVALID_PARAM Returned if there is no expander with such number.
 * @retval other                   Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t sx1509b_misc_set(uint8_t            instance_num,
                            bool               nreset_func,
                            sx1509b_debounce_t debounce_time,
                            bool               autoclear_nint);

/**
 * @brief Function sending software reset command to expander.
 *
 * @param instance_num Number of expander.
 *
 * @retval NRF_ERROR_INVALID_PARAM Returned if there is no expander with such number.
 * @retval other                   Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t sx1509b_sw_reset(uint8_t instance_num);

/**
 * @brief Function for setting register configuration of a single pin.
 *
 * @param[in] reg Register address, if register has two banks, address of bank B has to be used.
 * @param[in] pin Pin number.
 * @param[in] set Value to set.
 *
 * @retval NRF_ERROR_INVALID_PARAM Returned if there is no pin with such number.
 * @retval other                   Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t sx1509b_pin_cfg_reg_set(sx1509b_registers_t reg, uint32_t pin, uint8_t set);

/**
 * @brief Function for getting register configuration of a single pin.
 *
 * @param[in] reg Register address, if register has two banks, address of bank B has to be used.
 * @param[in] pin Pin number.
 *
 * @retval 0xFF  Returned if there is no pin with given number.
 * @return other Pin setting value at given register.
 */
uint8_t sx1509b_pin_cfg_reg_get(sx1509b_registers_t reg, uint32_t pin);

/**
 * @brief Function for setting register configuration of a port.
 *
 * @param reg  Register address, if register has two banks, address of bank B has to be used.
 * @param port Port number.
 * @param mask Mask for the operating.
 * @param flag Operation, should the mask be written into register, clear values or set them.
 *
 * @retval NRF_ERROR_INVALID_PARAM Returned if there is no port with such number.
 * @retval other                   Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t sx1509b_port_cfg_reg_set(sx1509b_registers_t reg,
                                    uint32_t            port,
                                    uint8_t             mask,
                                    sx1509b_port_op_t   flag);

/**
 * @brief Function for getting register configuration of a port.
 *
 * @param reg  Register address, if register has two banks, address of bank B has to be used.
 * @param port Port number.
 *
 * @retval Register value.
 */
uint8_t sx1509b_port_cfg_reg_get(sx1509b_registers_t reg, uint32_t port);

/**
 * @brief Function for updating pin data.
 *
 * @param user_cb Function to be called after pin data update is done.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
ret_code_t sx1509b_pin_data_update(nrf_twi_sensor_reg_cb_t user_cb);

/**
 * @brief Function for updating latch data.
 *
 * @param user_cb Function to be called after latch update is done.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
ret_code_t sx1509b_pin_latch_update(nrf_twi_sensor_reg_cb_t user_cb);

/**
 * @brief Function for setting long slew for given pin.
 *
 * @param pin_number Pin number.
 * @param set        Long slew setting.
 * @arg   true       Long slew is enabled.
 * @arg   false      Long slew is disabled.
 *
 * @return Return error code from pin config set @ref sx1509b_pin_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_pin_long_slew(uint32_t pin_number, bool set);

/**
 * @brief Function for setting low drive for given pin.
 *
 * @param pin_number Pin number.
 * @param set        Low drive setting.
 * @arg   true       Low drive is enabled.
 * @arg   false      Low drive is disabled.
 *
 * @return Return error code from pin config set @ref sx1509b_pin_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_pin_low_drive(uint32_t pin_number, bool set);

/**
 * @brief Function for setting open drain for given pin.
 *
 * @param pin_number Pin number.
 * @param set        Open drain setting.
 * @arg   true       Open drain is enabled.
 * @arg   false      Open drain is disabled.
 *
 * @return Return error code from pin config set @ref sx1509b_pin_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_pin_open_drain(uint32_t pin_number, bool set);

/**
 * @brief Function for setting polarity for given pin.
 *
 * @param pin_number Pin number.
 * @param set        Polarity setting.
 * @arg   true       Inverted polarity.
 * @arg   false      Normal polarity.
 *
 * @return Return error code from pin config set @ref sx1509b_pin_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_pin_polarity(uint32_t pin_number, bool set);

/**
 * @brief Function for setting debounce for given pin.
 *
 * @param pin_number Pin number.
 * @param set        Debounce setting.
 * @arg   true       Debouncing is enabled.
 * @arg   false      Debouncing is disabled.
 *
 * @return Return error code from pin config set @ref sx1509b_pin_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_pin_debounce(uint32_t pin_number, bool set);

/**
 * @brief Function for setting high input for given pin.
 *
 * @param pin_number Pin number.
 * @param set        High input setting.
 * @arg   true       High input is enabled.
 * @arg   false      High input is disabled.
 *
 * @retval NRF_ERROR_INVALID_PARAM Returned if there is no pin with such number.
 * @retval other                   Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t sx1509b_pin_high_input(uint32_t pin_number, bool set);
/**
 * @brief Function for setting level shift for given pin.
 *
 * @param pin_number Pin number.
 * @param set        Level shift setting.
 *
 * @return Return error code from pin config set @ref sx1509b_pin_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_pin_level_shifter(uint32_t              pin_number,
                                                     sx1509b_level_shift_t set);

/**
 * @brief Function for setting longslew for given port.
 *
 * @param port_num Port number.
 * @param out_mask Long slew mask.
 * @param flag     Port operation flag. @ref sx1509b_port_op_t
 *
 * @return Return error code from port config set @ref sx1509b_port_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_port_long_slew(uint8_t           port_num,
                                                  uint8_t           out_mask,
                                                  sx1509b_port_op_t flag);

/**
 * @brief Function for setting low drive for given port.
 *
 * @param port_num Port number.
 * @param out_mask Low drive mask.
 * @param flag     Port operation flag. @ref sx1509b_port_op_t
 *
 * @return Return error code from port config set @ref sx1509b_port_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_port_low_drive(uint8_t           port_num,
                                                  uint8_t           out_mask,
                                                  sx1509b_port_op_t flag);

/**
 * @brief Function for setting open drain for given port.
 *
 * @param port_num Port number.
 * @param out_mask Open drain mask.
 * @param flag     Port operation flag. @ref sx1509b_port_op_t
 *
 * @return Return error code from port config set @ref sx1509b_port_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_port_open_drain(uint8_t           port_num,
                                                   uint8_t           out_mask,
                                                   sx1509b_port_op_t flag);

/**
 * @brief Function for setting polarity for given port.
 *
 * @param port_num Port number.
 * @param out_mask Polarity mask.
 * @param flag     Port operation flag. @ref sx1509b_port_op_t
 *
 * @return Return error code from port config set @ref sx1509b_port_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_port_polarity(uint8_t           port_num,
                                                 uint8_t           out_mask,
                                                 sx1509b_port_op_t flag);

/**
 * @brief Function for setting debounce for given port.
 *
 * @param port_num Port number.
 * @param out_mask Debounce mask.
 * @param flag     Port operation flag. @ref sx1509b_port_op_t
 *
 * @return Return error code from port config set @ref sx1509b_port_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_port_debounce(uint8_t           port_num,
                                                 uint8_t           out_mask,
                                                 sx1509b_port_op_t flag);

/**
 * @brief Function for setting high input for given port.
 *
 * @param port_num Port number.
 * @param out_mask High input mask.
 * @param flag     Port operation flag. @ref sx1509b_port_op_t
 *
 * @retval NRF_ERROR_INVALID_PARAM Returned if there is no pin with such number.
 * @retval other                   Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t sx1509b_port_high_input(uint8_t port_num, uint8_t out_mask, sx1509b_port_op_t flag);

/**
 * @brief Function for setting pull up for given port.
 *
 * @param port_num Port number.
 * @param out_mask Pull up mask.
 * @param flag     Port operation flag. @ref sx1509b_port_op_t
 *
 * @return Return error code from port config set @ref sx1509b_port_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_port_pull_up(uint8_t           port_num,
                                                uint8_t           out_mask,
                                                sx1509b_port_op_t flag);

/**
 * @brief Function for setting pull down for given port.
 *
 * @param port_num Port number.
 * @param out_mask Pull down mask.
 * @param flag     Port operation flag. @ref sx1509b_port_op_t
 *
 * @return Return error code from port config set @ref sx1509b_port_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_port_pull_down(uint8_t           port_num,
                                                  uint8_t           out_mask,
                                                  sx1509b_port_op_t flag);

/**
 * ===============================================================================================
 * @brief Functions compatible with nrf_gpio
 */

/**
 * @brief Function for configuring the given GPIO pin number as output, hiding inner details.
 *        This function can be used to configure a pin as simple output with gate driving.
 *
 * @param pin_number Specifies the pin number.
 *
 * @note  Sense capability on the pin is disabled as the pins are configured as output.
 *
 * @return Return error code from pin config set @ref sx1509b_pin_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_pin_cfg_output(uint32_t pin_number);

/**
 * @brief Function for configuring the given GPIO pin number as input, hiding inner details.
 *        This function can be used to configure a pin as simple input.
 *
 * @param pin_number  Specifies the pin number.
 * @param pull_config State of the pin range pull resistor (no pull, pulled down, or pulled high).
 *
 * @note  Sense capability on the pin is disabled and input is connected to buffer.
 *
 * @return Return error code from pin config set @ref sx1509b_pin_cfg_reg_set
 */
ret_code_t sx1509b_pin_cfg_input(uint32_t pin_number, sx1509b_pin_pull_t pull_config);

/**
 * @brief Function for resetting pin configuration to its default state.
 *
 * @param pin_number Specifies the pin number.
 *
 * @return Return error code from pin config set @ref sx1509b_pin_cfg_reg_set
 */
ret_code_t sx1509b_pin_cfg_default(uint32_t pin_number);

/**
 * @brief Function for configuring the given GPIO pin number as a watcher. Only input is connected.
 *
 * @param pin_number Specifies the pin number.
 *
 * @return Return error code from pin config set @ref sx1509b_pin_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_pin_cfg_watcher(uint32_t pin_number); // non

/**
 * @brief Function for disconnecting input for the given GPIO.
 *
 * @param pin_number Specifies the pin number.
 *
 * @return Return error code from pin config set @ref sx1509b_pin_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_pin_cfg_input_disconnect(uint32_t pin_number);

/**
 * @brief Function for configuring the given GPIO pin number as input, hiding inner details.
 *        Sense capability on the pin is configurable and input is connected to buffer.
 *
 * @param pin_number   Specifies the pin number.
 * @param pull_config  State of the pin pull resistor (no pull, pulled down, or pulled high).
 * @param sense_config Sense level of the pin (no sense, sense low, sense high or sense both).
 *
 * @return Return error code from pin config set @ref sx1509b_pin_cfg_reg_set
 */
ret_code_t sx1509b_pin_cfg_sense_input(uint32_t            pin_number,
                                       sx1509b_pin_pull_t  pull_config,
                                       sx1509b_pin_sense_t sense_config);

/**
 * @brief Function for configuring sense level for the given GPIO.
 *
 * @param pin_number   Specifies the pin number.
 * @param sense_config Sense configuration.
 *
 * @return Return error code from pin config set @ref sx1509b_pin_cfg_reg_set
 */
ret_code_t sx1509b_pin_cfg_sense_set(uint32_t pin_number, sx1509b_pin_sense_t sense_config);

/**
 * @brief Function for setting the direction for a GPIO pin.
 *
 * @param pin_number Specifies the pin number for which to set the direction.
 * @param direction  Specifies the direction.
 *
 * @return Return error code from pin config set @ref sx1509b_pin_cfg_reg_set
 */
ret_code_t sx1509b_pin_dir_set(uint32_t pin_number, sx1509b_pin_dir_t direction);

/**
 * @brief Function for setting a GPIO pin.
 *
 * Note that the pin must be configured as an output for this function to have any effect.
 *
 * @param pin_number Specifies the pin number to set.
 *
 * @return Return error code from pin config set @ref sx1509b_pin_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_pin_set(uint32_t pin_number);

/**
 * @brief Function for clearing a GPIO pin.
 *
 * Note that the pin must be configured as an output for this
 * function to have any effect.
 *
 * @param pin_number Specifies the pin number to clear.
 *
 * @return Return error code from pin config set @ref sx1509b_pin_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_pin_clear(uint32_t pin_number);

/**
 * @brief Function for toggling a GPIO pin.
 *
 * Note that the pin must be configured as an output for this
 * function to have any effect.
 *
 * @param pin_number Specifies the pin number to toggle.
 *
 * @return Return error code from pin config set @ref sx1509b_pin_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_pin_toggle(uint32_t pin_number);

/**
 * @brief Function for writing a value to a GPIO pin.
 *
 * Note that the pin must be configured as an output for this
 * function to have any effect.
 *
 * @param pin_number Specifies the pin number to write.
 *
 * @param value Specifies the value to be written to the pin.
 * @arg 0 Clears the pin.
 * @arg >=1 Sets the pin.
 *
 * @return Return error code from pin config set @ref sx1509b_pin_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_pin_write(uint32_t pin_number,  sx1509b_pin_set_t value);

/**
 * @brief Function for reading the input level of a GPIO pin.
 *
 * @note The pin must have input connected for the value
 *       returned from this function to be valid.
 *       Due to specifics of TWI expander, pin data must be updated first
 *       to get current value @ref sx1509b_pin_data_update
 *
 * @param pin_number Specifies the pin number to read.
 *
 * @return 0 if the pin input level is low. Positive value if the pin is high.
 */
__STATIC_INLINE uint32_t sx1509b_pin_read(uint32_t pin_number);



/**
 * @brief Function for reading the output level of a GPIO pin.
 *
 * @param pin_number Specifies the pin number to read.
 *
 * @return 0 if the pin output level is low. Positive value if pin output is high.
 */
__STATIC_INLINE uint32_t sx1509b_pin_out_read(uint32_t pin_number);

/**
 * @brief Function for reading the sense configuration of a GPIO pin.
 *
 * @param pin_number Specifies the pin number to read.
 *
 * @retval Sense configuration.
 */
__STATIC_INLINE sx1509b_pin_sense_t sx1509b_pin_sense_get(uint32_t pin_number);

/**
 * @brief Function for getting expander port number based on pin number.
 *
 * @retval Port number.
 */
__STATIC_INLINE uint8_t sx1509b_pin_port_decode(uint32_t pin_number);

/**
 * @brief Function for setting output direction on selected pins on a given port.
 *
 * @param port_num Port number.
 * @param out_mask Mask specifying the pins to set as output.
 *
 * @return Return error code from port config set @ref sx1509b_port_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_port_dir_output_set(uint8_t port_num, uint8_t out_mask);

/**
 * @brief Function for setting input direction on selected pins on a given port.
 *
 * @param port_num Port number.
 * @param in_mask  Mask specifying the pins to set as input.
 *
 * @return Return error code from port config set @ref sx1509b_port_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_port_dir_input_set(uint8_t port_num, uint8_t in_mask);

/**
 * @brief Function for writing the direction configuration of GPIO pins in a given port.
 *
 * @param port_num Port number.
 * @param dir_mask Mask specifying the direction of pins.
 *                 Bit set means that the given pin is configured as output.
 *
 * @return Return error code from port config set @ref sx1509b_port_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_port_dir_write(uint8_t port_num, uint8_t dir_mask);

/**
 * @brief Function for reading the direction configuration of a GPIO port.
 *
 * @param port_num Port number.
 *
 * @note  Returns 0 if port doesn't exist.
 *
 * @retval Pin configuration of the current direction settings.
 *         Bit set means that the given pin is configured as output.
 */
__STATIC_INLINE uint8_t sx1509b_port_dir_read(uint8_t port_num);

/**
 * @brief Function for reading the input signals of GPIO pins on a given port.
 *
 * @param port_num Port number.
 *
 * @note  Returns 0 if port doesn't exist.
 *
 * @retval Port input values.
 */
__STATIC_INLINE uint8_t sx1509b_port_in_read(uint8_t port_num);

/**
 * @brief Function for reading the output signals of GPIO pins of a given port.
 *
 * @param port_num Port number.
 *
 * @note  Returns 0 if port doesn't exist.
 *
 * @retval Port output values.
 */
__STATIC_INLINE uint8_t sx1509b_port_out_read(uint8_t port_num);

/**
 * @brief Function for writing the GPIO pins output on a given port.
 *
 * @param port_num Port number.
 * @param value Output port mask.
 *
 * @return Return error code from port config set @ref sx1509b_port_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_port_out_write(uint8_t port_num, uint8_t value);

/**
 * @brief Function for setting high level on selected GPIO pins of a given port.
 *
 * @param port_num Port number.
 * @param set_mask Mask with pins to set as logical high level.
 *
 * @return Return error code from port config set @ref sx1509b_port_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_port_out_set(uint8_t port_num, uint8_t set_mask);

/**
 * @brief Function for setting low level on selected GPIO pins of a given port.
 *
 * @param port_num Port number.
 * @param clr_mask Mask with pins to set as logical low level.
 *
 * @return Return error code from port config set @ref sx1509b_port_cfg_reg_set
 */
__STATIC_INLINE ret_code_t sx1509b_port_out_clear(uint8_t port_num, uint8_t clr_mask);

/**
 * @brief Function for reading pins state of multiple consecutive ports.
 *
 * @note  Due to specifics of TWI expander, pin data must be updated first
 *        to get current value @ref sx1509b_pin_data_update
 *
 * @param start_port Index of the first port to read.
 * @param length     Number of ports to read.
 * @param p_masks    Pointer to output array where port states will be stored.
 *
 * @retval NRF_ERROR_INVALID_LENGTH If trying to read more ports than available.
 * @retval NRF_SUCCESS              If operation was successful.
 */
ret_code_t sx1509b_ports_read(uint8_t start_port, uint32_t length, uint8_t * p_masks);

/**
 * @brief Function for reading latch state of multiple consecutive ports.
 *
 * @note  Due to specifics of TWI expander, latch data must be updated first
 *        to get current value @ref sx1509b_pin_latch_update
 *
 * @param start_port Index of the first port to read.
 * @param length     Number of ports to read.
 * @param p_masks    Pointer to output array where latch states will be stored.
 *
 * @retval NRF_ERROR_INVALID_LENGTH If trying to read more ports than available.
 * @retval NRF_SUCCESS              If operation was successful.
 */
ret_code_t sx1509b_latches_read(uint8_t start_port, uint32_t length, uint8_t * p_masks);

/**
 * @brief Function for reading latch state of single pin.
 *
 * @note  Due to specifics of TWI expander, latch data must be updated first
 *        to get current value @ref sx1509b_pin_latch_update
 *
 * @param  pin_number Pin number.
 *
 * @retval 0    Returned if latch is not set
 * @retval 1    Returned if latch is set.
 * @retval other Return from @ref sx1509b_pin_cfg_reg_get
 */
__STATIC_INLINE uint32_t sx1509b_pin_latch_get(uint32_t pin_number);

/**
 * @brief Function for clearing latch state of a single pin.
 *
 * @param pin_number Pin number.
 *
 * @return Return error code from pin config set @ref sx1509b_pin_cfg_reg_set
 */
ret_code_t sx1509b_pin_latch_clear(uint32_t pin_number);

/**
 * ===============================================================================================
 * @brief Led driver functions.
 */

/**
 * @brief Function enabling led driver.
 *
 * @param instance_num   Number of expander instance.
 * @param clock_internal Sets clock source.
 * @arg   true           External clock source
 * @arg   false          Internal 2Mhz clock
 * @param frequency      Frequency divider.
 * @arg   0              Led driver functionality is disabled for all IOs.
 * @arg   Else           Divider value, refer to expander documentation.
 *
 * @retval NRF_ERROR_INVALID_PARAM Returned if given instance isn't present.
 * @retval other                   Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t sx1509b_led_driver_enable(uint8_t instance_num, bool clock_internal, uint8_t frequency);

/**
 * @brief Function for setting led driver mode.
 *
 * @param port_num Port for which mode will be set.
 * @param mode     Led driver mode.
 * @arg   true     Logarithmic mode
 * @arg   false    Linear mode
 *
 * @retval NRF_ERROR_INVALID_PARAM Returned if given port isn't present.
 * @retval other                   Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t sx1509b_led_mode(uint8_t port_num, bool mode);

/**
 * @brief Function for setting led driver pin times.
 *
 * @param pin_number    Pin which settings will be changed.
 * @param on_time       On time of pin. Refer to expander documentation.
 * @param on_intensity  Intensity during on time. Between 0 and 255.
 * @param off_time      Off time of pin. Refer to expander documentation.
 * @param off_intensity Intensity during off time. Between 0 and 7.
 *
 * @retval NRF_ERROR_INVALID_PARAM Returned if there is no pin with given number.
 * @retval other                   Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t sx1509b_led_pin_time(uint32_t pin_number,
                                uint8_t  on_time,
                                uint8_t  on_intensity,
                                uint8_t  off_time,
                                uint8_t  off_intensity);

/**
 * @brief Function for setting led driver pin fade characteristics.
 *
 * @param pin_number    Pin which settings will be changed.
 * @param fade_in       Fade in time of pin. Refer to expander documentation.
 * @param fade_out      Fade out time of pin. Refer to expander documentation.
 *
 * @retval NRF_ERROR_INVALID_PARAM Returned if given pin has no fade capability,
 *                                 or there is no pin with given number.
 * @retval other                   Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t sx1509b_led_pin_fade(uint32_t pin_number, uint8_t fade_in, uint8_t fade_out);

/**
 * @brief Function for enabling led driver on selected pin.
 *
 * @param pin_number Pin number.
 *
 * @retval NRF_ERROR_INVALID_PARAM Returned if there is no pin with given number.
 * @retval other                   Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t sx1509b_led_pin_enable(uint32_t pin_number);

/**
 * @brief Function for disabling led driver on selected pin.
 *
 * @param pin_number Pin number.
 *
 * @retval NRF_ERROR_INVALID_PARAM Returned if there is no pin with given number.
 * @retval other                   Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t sx1509b_led_pin_disable(uint32_t pin_number);

/**
 * @brief Function for getting led driver time on register of selected pin.
 *
 * @param pin_number Pin number.
 *
 * @retval Time on led driver register of selected pin
 */
uint8_t sx1509b_led_driver_get_reg(uint32_t pin_number);

/**
 * ===============================================================================================
 * @brief Key Engine functions.
 */

/**
 * @brief Function enabling key engine.
 *
 * @param instance_num  Number of expander.
 * @param rows          Number of keyboard rows.
 * @arg   <  2          Disable key engine.
 * @arg   >= 2          Number of rows (max 8).
 * @param columns       Number of columns (max 8).
 * @param sleep_time    Time of inactivity before key engine enters sleep mode.
 * @param scan_time     Scan time per column. Must be bigger than debounce time.
 * @param debounce_time Input debounce time.
 *
 * @retval NRF_ERROR_INVALID_PARAM Returned if there is no expander with given number.
 * @retval other                   Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t sx1509b_key_engine_enable(uint8_t             instance_num,
                                     uint8_t             rows,
                                     uint8_t             columns,
                                     sx1509b_key_sleep_t sleep_time,
                                     sx1509b_key_scan_t  scan_time,
                                     sx1509b_debounce_t  debounce_time);

/**
 * @brief Function scheduling key data update.
 *
 * @param instance_num Number of expander to update.
 * @param user_cb      Function called after key data update.
 *
 * @retval NRF_ERROR_INVALID_PARAM Returned if there is no expander with given number.
 * @retval other                   Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t sx1509b_key_data_update(uint8_t instance_num, nrf_twi_sensor_reg_cb_t user_cb);

/**
 * @brief Function returning pressed key column.
 *
 * @param instance_num Number of expander.
 *
 * @retval NRF_ERROR_INVALID_PARAM Returned if there is no expander with given number.
 * @retval 0xFF                    If no key was pressed.
 * @retval 0 - 7                   Column number.
 */
uint8_t sx1509b_key_column_get(uint8_t instance_num);

/**
 * @brief Function returning pressed key row.
 *
 * @param instance_num Number of expander.
 *
 * @retval NRF_ERROR_INVALID_PARAM Returned if there is no expander with given number.
 * @retval 0xFF                    If no key was pressed.
 * @retval 0 - 7                   Row number.
 */
uint8_t sx1509b_key_row_get(uint8_t instance_num);

#ifndef SUPPRESS_INLINE_IMPLEMENTATION

/**
 * ===============================================================================================
 * @brief General expander inline utility functions.
 */

__STATIC_INLINE ret_code_t sx1509b_pin_long_slew(uint32_t pin_number, bool set)
{
    return sx1509b_pin_cfg_reg_set(SX1509B_REG_LONG_SLEW_B, pin_number, set);
}

__STATIC_INLINE ret_code_t sx1509b_pin_low_drive(uint32_t pin_number, bool set)
{
    return sx1509b_pin_cfg_reg_set(SX1509B_REG_LOW_DRIVE_B, pin_number, set);
}

__STATIC_INLINE ret_code_t sx1509b_pin_open_drain(uint32_t pin_number, bool set)
{
    return sx1509b_pin_cfg_reg_set(SX1509B_REG_OPEN_DRAIN_B, pin_number, set);
}

__STATIC_INLINE ret_code_t sx1509b_pin_polarity(uint32_t pin_number, bool set)
{
    return sx1509b_pin_cfg_reg_set(SX1509B_REG_POLARITY_B, pin_number, set);
}

__STATIC_INLINE ret_code_t sx1509b_pin_debounce(uint32_t pin_number, bool set)
{
    return sx1509b_pin_cfg_reg_set(SX1509B_REG_DEBOUNCE_EN_B, pin_number, set);
}

__STATIC_INLINE ret_code_t sx1509b_pin_level_shifter(uint32_t pin_number, sx1509b_level_shift_t set)
{
    return sx1509b_pin_cfg_reg_set(SX1509B_REG_LEVEL_SHIFTER_1, pin_number, set);
}

__STATIC_INLINE ret_code_t sx1509b_port_long_slew(uint8_t           port_num,
                                                  uint8_t           out_mask,
                                                  sx1509b_port_op_t flag)
{
    return sx1509b_port_cfg_reg_set(SX1509B_REG_LONG_SLEW_B, port_num, out_mask, flag);
}

__STATIC_INLINE ret_code_t sx1509b_port_low_drive(uint8_t           port_num,
                                                  uint8_t           out_mask,
                                                  sx1509b_port_op_t flag)
{
    return sx1509b_port_cfg_reg_set(SX1509B_REG_LOW_DRIVE_B, port_num, out_mask, flag);
}

__STATIC_INLINE ret_code_t sx1509b_port_open_drain(uint8_t           port_num,
                                                   uint8_t           out_mask,
                                                   sx1509b_port_op_t flag)
{
    return sx1509b_port_cfg_reg_set(SX1509B_REG_OPEN_DRAIN_B, port_num, out_mask, flag);
}

__STATIC_INLINE ret_code_t sx1509b_port_polarity(uint8_t           port_num,
                                                 uint8_t           out_mask,
                                                 sx1509b_port_op_t flag)
{
    return sx1509b_port_cfg_reg_set(SX1509B_REG_POLARITY_B, port_num, out_mask, flag);
}

__STATIC_INLINE ret_code_t sx1509b_port_debounce(uint8_t           port_num,
                                                 uint8_t           out_mask,
                                                 sx1509b_port_op_t flag)
{
    return sx1509b_port_cfg_reg_set(SX1509B_REG_DEBOUNCE_EN_B, port_num, out_mask, flag);
}

__STATIC_INLINE ret_code_t sx1509b_port_pull_up(uint8_t           port_num,
                                                uint8_t           out_mask,
                                                sx1509b_port_op_t flag)
{
    return sx1509b_port_cfg_reg_set(SX1509B_REG_PULL_UP_B, port_num, out_mask, flag);
}

__STATIC_INLINE ret_code_t sx1509b_port_pull_down(uint8_t           port_num,
                                                  uint8_t           out_mask,
                                                  sx1509b_port_op_t flag)
{
    return sx1509b_port_cfg_reg_set(SX1509B_REG_PULL_DOWN_B, port_num, out_mask, flag);
}

/**
 * ===============================================================================================
 * @brief Inline functions compatible with nrf_gpio
 */
__STATIC_INLINE ret_code_t sx1509b_pin_cfg_output(uint32_t pin_number)
{
    return sx1509b_pin_cfg_reg_set(SX1509B_REG_DIR_B, pin_number, SX1509B_PIN_DIR_OUTPUT);
}

__STATIC_INLINE ret_code_t sx1509b_pin_cfg_watcher(uint32_t pin_number)
{
    return sx1509b_pin_cfg_input(pin_number, SX1509B_PIN_NOPULL);
}

__STATIC_INLINE ret_code_t sx1509b_pin_cfg_input_disconnect(uint32_t pin_number)
{
    return sx1509b_pin_cfg_reg_set(SX1509B_REG_INPUT_DISABLE_B, pin_number, 1);
}

__STATIC_INLINE ret_code_t sx1509b_pin_set(uint32_t pin_number)
{
    return sx1509b_pin_cfg_reg_set(SX1509B_REG_DATA_B, pin_number, SX1509B_PIN_SET);
}

__STATIC_INLINE ret_code_t sx1509b_pin_clear(uint32_t pin_number)
{
    return sx1509b_pin_cfg_reg_set(SX1509B_REG_DATA_B, pin_number, SX1509B_PIN_CLR);
}

__STATIC_INLINE ret_code_t sx1509b_pin_toggle(uint32_t pin_number)
{
    uint8_t val = sx1509b_pin_cfg_reg_get(SX1509B_REG_DATA_B, pin_number);
    val = !val;
    return sx1509b_pin_cfg_reg_set(SX1509B_REG_DATA_B, pin_number, val);
}

__STATIC_INLINE ret_code_t sx1509b_pin_write(uint32_t pin_number, sx1509b_pin_set_t value)
{
    value = (value >= 1) ? 1 : 0;
    return sx1509b_pin_cfg_reg_set(SX1509B_REG_DATA_B, pin_number, value);
}

__STATIC_INLINE uint32_t sx1509b_pin_read(uint32_t pin_number)
{
    return sx1509b_pin_cfg_reg_get(SX1509B_REG_DATA_B, pin_number);
}

__STATIC_INLINE uint32_t sx1509b_pin_out_read(uint32_t pin_number)
{
    return sx1509b_pin_cfg_reg_get(SX1509B_REG_DATA_B, pin_number);
}

__STATIC_INLINE sx1509b_pin_sense_t sx1509b_pin_sense_get(uint32_t pin_number)
{
    return sx1509b_pin_cfg_reg_get(SX1509B_REG_SENSE_H_B, pin_number);
}

__STATIC_INLINE uint8_t sx1509b_pin_port_decode(uint32_t pin_number)
{
    return pin_number / SX1509B_INNER_NEXT_BANK;
}

__STATIC_INLINE ret_code_t sx1509b_port_dir_output_set(uint8_t port_num, uint8_t out_mask)
{
    return sx1509b_port_cfg_reg_set(SX1509B_REG_DIR_B, port_num, out_mask, SX1509B_PORT_CLEAR);
}

__STATIC_INLINE ret_code_t sx1509b_port_dir_input_set(uint8_t port_num, uint8_t in_mask)
{
    return sx1509b_port_cfg_reg_set(SX1509B_REG_DIR_B, port_num, in_mask, SX1509B_PORT_SET);
}

__STATIC_INLINE ret_code_t sx1509b_port_dir_write(uint8_t port_num, uint8_t dir_mask)
{
    return sx1509b_port_cfg_reg_set(SX1509B_REG_DIR_B, port_num, ~dir_mask, SX1509B_PORT_WRITE);
}

__STATIC_INLINE uint8_t sx1509b_port_dir_read(uint8_t port_num)
{
    return ~sx1509b_port_cfg_reg_get(SX1509B_REG_DIR_B, port_num);
}

__STATIC_INLINE uint8_t sx1509b_port_in_read(uint8_t port_num)
{
    return sx1509b_port_cfg_reg_get(SX1509B_REG_DATA_B, port_num);
}

__STATIC_INLINE uint8_t sx1509b_port_out_read(uint8_t port_num)
{
    return sx1509b_port_cfg_reg_get(SX1509B_REG_DATA_B, port_num);
}

__STATIC_INLINE ret_code_t sx1509b_port_out_write(uint8_t port_num, uint8_t value)
{
    return sx1509b_port_cfg_reg_set(SX1509B_REG_DATA_B, port_num, value, SX1509B_PORT_WRITE);
}

__STATIC_INLINE ret_code_t sx1509b_port_out_set(uint8_t port_num, uint8_t set_mask)
{
    return sx1509b_port_cfg_reg_set(SX1509B_REG_DATA_B, port_num, set_mask, SX1509B_PORT_SET);
}

__STATIC_INLINE ret_code_t sx1509b_port_out_clear(uint8_t port_num, uint8_t clr_mask)
{
    return sx1509b_port_cfg_reg_set(SX1509B_REG_DATA_B, port_num, clr_mask, SX1509B_PORT_CLEAR);
}

__STATIC_INLINE uint32_t sx1509b_pin_latch_get(uint32_t pin_number)
{
    return sx1509b_pin_cfg_reg_get(SX1509B_REG_INT_SRC_B, pin_number);
}
#endif //SUPPRESS_INLINE_IMPLEMENTATION

#ifdef __cplusplus
}
#endif

#endif // SX1509B_H
