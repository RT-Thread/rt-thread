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

#if !defined(__MAX7310_H__)
#define __MAX7310_H__

#include "sdk.h"
#include "i2c/imx_i2c.h"

//! @addtogroup diag_ioexpander
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief An array of I2C requests for all used expanders on the board.
//!
//! This array is used to specify the I2C addresses for the I/O expanders.
extern imx_i2c_request_t max7310_i2c_req_array[];

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initialize the MAX7310.
 *
 * Sets a a default I/O direction and output value. The I2C bus reset on timeout
 * feature is disabled.
 *
 * The MAX7310 has no ID register, so one the timeout register is also initialized
 * with a value of 0xAC. This can be used later to verify the presence of the device.
 *
 * @param slave_id         I/O expander instance number
 * @param io_default_dir   default I/O direction
 * @param out_default_val  default output value
 * 
 * @return 0 on success; non-zero otherwise
 */
int32_t max7310_init(uint32_t slave_id, uint32_t io_default_dir, uint32_t out_default_val);

/*!
 * @brief Controls the MAX7310 output pin state.
 *
 * @param slave_id   I/O expander instance number (0=instance 0,...)
 * @param io_x       I/O number (0=IO_0, 1=IO_1, ...)
 * @param level      I/O state (0=low, 1=high)
 * 
 * @return 0 on success; non-zero otherwise
 */
void max7310_set_gpio_output(uint32_t slave_id, uint32_t io_x, uint32_t level);

#if defined(__cplusplus)
}
#endif

//! @}

#endif // __MAX7310_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
