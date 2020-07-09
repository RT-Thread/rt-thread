/**
 * Copyright (c) 2009 - 2017, Nordic Semiconductor ASA
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
#ifndef SYNAPTICS_TOUCHPAD_H
#define SYNAPTICS_TOUCHPAD_H

/*lint ++flb "Enter library region" */

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @file
* @brief Synaptics Touchpad driver
*
*
* @defgroup nrf_drivers_synaptics_touchpad Synaptics Touchpad driver
* @{
* @ingroup ext_drivers
* @brief Synaptics Touchpad driver.
*/

/**
  Touchpad register addresses.
*/
#define TOUCHPAD_INT_STATUS    0x14    //!< Interrupt status register
#define TOUCHPAD_BUTTON_STATUS 0x41    //!< Button status register
#define TOUCHPAD_FINGER0_REL   0x30    //!< First register in finger delta block
#define TOUCHPAD_GESTURE_FLAGS 0x3A    //!< Gesture flags 0
#define TOUCHPAD_SCROLL        0x3F    //!< Scroll zone X / horizontal multifinger scroll
#define TOUCHPAD_CONTROL       0x42    //!< Device control register
#define TOUCHPAD_COMMAND       0x8F    //!< Device command register

#define TOUCHPAD_RESET 0x54 //!< Address of reset
#define TOUCHPAD_PAGESELECT 0xFF //!< Address of page select (can be found in every page at the same address)
#define TOUCHPAD_PRODUCT_ID 0xA2 //!< Address of product ID string

/**
  Operational states
*/
typedef enum
{
  SleepmodeNormal        = 0x00,  //!< Normal operation
  SleepmodeSensorSleep   = 0x01  //!< Low power operation
} TouchpadSleepMode_t;

/**
  @brief Function for Touchpad initialization.
  @param device_address TWI address of the device in bits [6:0]
  @retval true Touchpad was successfully identified and initialized
  @retval false Unexpected product ID or communication failure
*/
bool touchpad_init(uint8_t device_address);

/**
  @brief Function for attempting to soft-reset the device.
  @retval true Reset succeeded
  @retval false Reset failed
*/
bool touchpad_reset(void);

/**
  @brief Function for reading the interrupt status register of the device. This clears all interrupts.
  @param interrupt_status Address to store interrupt status to.
  @retval true Register contents read successfully to interrupt_status
  @retval false Reading failed
*/
bool touchpad_interrupt_status_read(uint8_t *interrupt_status);

/**
  @brief Function for sleep mode configuration.
  @note In low power mode the touchpad do not generate interrupts from touch sensing.
  @param[in] mode Operational mode
  @retval true Sleep mode set successfully
  @retval false Sleep mode setting failed
*/
bool touchpad_set_sleep_mode(TouchpadSleepMode_t mode);

/**
  @brief Function for reading a touchpad register contents over TWI.
  @param[in] register_address Register address
  @param[out] value Pointer to a data buffer where read data will be stored
  @retval true Register read succeeded
  @retval false Register read failed
*/
bool touchpad_read_register(uint8_t register_address, uint8_t *value);

/**
  @brief Function for writing a touchpad register contents over TWI.
  @param[in]  register_address Register address
  @param[in] value Value to write to register
  @retval true Register write succeeded
  @retval false Register write failed
*/
bool touchpad_write_register(uint8_t register_address, uint8_t value);

/**
  @brief Function for writing touchpad register contents over TWI.
  Writes one or more consecutive registers.
  @param[out] product_id Pointer to a address to store product ID. Memory must be allocated for product_id_bytes number of bytes.
  @param[in]  product_id_bytes Number of bytes to read
  @retval true Product ID read succeeded
  @retval false Product ID read failed
*/
bool touchpad_product_id_read(uint8_t *product_id, uint8_t product_id_bytes);

/**
  @brief Function for reading and verifying touchpad's product ID.
  @retval true Product ID is what was expected
  @retval false Product ID was not what was expected
*/
bool touchpad_product_id_verify(void);

/**
 *@}
 **/

/*lint --flb "Leave library region" */


#ifdef __cplusplus
}
#endif

#endif /* __TOUCHPAD_H__ */
