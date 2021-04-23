/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PLATFORM_BOOTROM_H
#define _PLATFORM_BOOTROM_H

#include "pico.h"

/** \file bootrom.h
 * \defgroup pico_bootrom pico_bootrom
 * Access to functions and data in the RP2040 bootrom
 */


/*! \brief Return a bootrom lookup code based on two ASCII characters
 * \ingroup pico_bootrom
 *
 * These codes are uses to lookup data or function addresses in the bootrom
 * 
 * \param c1 the first character
 * \param c2 the second character
 * \return the 'code' to use in rom_func_lookup() or rom_data_lookup()
 */
static inline uint32_t rom_table_code(char c1, char c2) {
    return (c2 << 8u) | c1;
}

/*!
 * \brief Lookup a bootrom function by code
 * \ingroup pico_bootrom
 * \param code the code
 * \return a pointer to the function, or NULL if the code does not match any bootrom function
 */
void *rom_func_lookup(uint32_t code);

/*!
 * \brief Lookup a bootrom address by code
 * \ingroup pico_bootrom
 * \param code the code
 * \return a pointer to the data, or NULL if the code does not match any bootrom function
 */
void *rom_data_lookup(uint32_t code);

/*!
 * \brief Helper function to lookup the addresses of multiple bootrom functions
 * \ingroup pico_bootrom
 *
 * This method looks up the 'codes' in the table, and convert each table entry to the looked up
 * function pointer, if there is a function for that code in the bootrom.
 *
 * \param table an IN/OUT array, elements are codes on input, function pointers on success.
 * \param count the number of elements in the table
 * \return true if all the codes were found, and converted to function pointers, false otherwise
 */
bool rom_funcs_lookup(uint32_t *table, unsigned int count);

typedef void __attribute__((noreturn)) (*reset_usb_boot_fn)(uint32_t, uint32_t);

/*!
 * \brief Reboot the device into BOOTSEL mode
 * \ingroup pico_bootrom
 *
 * This function reboots the device into the BOOTSEL mode ('usb boot").
 *
 * Facilities are provided to enable an "activity light" via GPIO attached LED for the USB Mass Storage Device,
 * and to limit the USB interfaces exposed.
 *
 * \param usb_activity_gpio_pin_mask 0 No pins are used as per a cold boot. Otherwise a single bit set indicating which
 *                               GPIO pin should be set to output and raised whenever there is mass storage activity
 *                               from the host.
 * \param disable_interface_mask value to control exposed interfaces
 *  - 0 To enable both interfaces (as per a cold boot)
 *  - 1 To disable the USB Mass Storage Interface
 *  - 2 To disable the USB PICOBOOT Interface
 */
static inline void __attribute__((noreturn)) reset_usb_boot(uint32_t usb_activity_gpio_pin_mask,
                                                            uint32_t disable_interface_mask) {
    reset_usb_boot_fn func = (reset_usb_boot_fn) rom_func_lookup(rom_table_code('U', 'B'));
    func(usb_activity_gpio_pin_mask, disable_interface_mask);
}

#endif
