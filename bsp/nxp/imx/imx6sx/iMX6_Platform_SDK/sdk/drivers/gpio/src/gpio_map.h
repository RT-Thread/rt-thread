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
 * @file gpio_map.h
 * @brief 
 * @ingroup diag_gpio
 */

#ifndef __GPIO_MAP_H__
#define __GPIO_MAP_H__

#include <stdint.h>
#include "registers/regsgpio.h"

//! @addtogroup diag_gpio
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Number of pins per GPIO bank.
#define GPIO_PIN_COUNT (32)

//! @brief Table to map GPIO pins to their mux control register addresses.
//!
//! First subscript is bank, second is pin within the bank. There are always 32 pin
//! entries per bank. If a pin does not have an assigned GPIO, its address is 0.
//!
//! Example code to set GPIO 3,12 to GPIO mode:
//! @code
//!     uint32_t addr = k_gpio_mux_registers[3][12];
//!     volatile uint32_t * reg = (volatile uint32_t *)addr;
//!     *reg = (*reg & ~BM_IOMUXC_SW_MUX_CTL_PAD_GPIO00_MUX_MODE)
//!             | BF_IOMUXC_SW_MUX_CTL_PAD_GPIO00_MUX_MODE_V(ALT5);
//! @endcode
//!
//! The code above uses the bit field macros from an arbitrary mux register definition.
extern const uint32_t k_gpio_mux_registers[HW_GPIO_INSTANCE_COUNT][GPIO_PIN_COUNT];

//! @}

#endif //__GPIO_MAP_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
