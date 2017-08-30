/**
 * \file
 *
 * \brief I2C Master Interrupt Driver for SAMB
 *
 * Copyright (C) 2015 Atmel Corporation. All rights reserved.
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

#ifndef I2C_MASTER_INTERRUPT_H_INCLUDED
#define I2C_MASTER_INTERRUPT_H_INCLUDED

#include "i2c_master.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup asfdoc_samb_i2c_group
 * @{
 *
 */

/**
 * \name Callbacks
 * @{
 */
#if !defined(__DOXYGEN__)
extern void *_i2c_instances;
void _i2c_master_isr_handler(void);
#endif

void i2c_master_register_callback(
		struct i2c_master_module *const module,
		i2c_master_callback_t callback,
		enum i2c_master_callback callback_type);

void i2c_master_unregister_callback(
		struct i2c_master_module *const module,
		enum i2c_master_callback callback_type);

/**
 * \brief Enables callback
 *
 * Enables the callback specified by the callback_type.
 *
 * \param[in,out] module         Pointer to the software module struct
 * \param[in]     callback_type  Callback type to enable
 */
static inline void i2c_master_enable_callback(
		struct i2c_master_module *const module,
		enum i2c_master_callback callback_type)
{
	/* Sanity check. */
	Assert(module);
	Assert(module->hw);

	/* Mark callback as enabled. */
	module->enabled_callback |= (1 << callback_type);
}

/**
 * \brief Disables callback
 *
 * Disables the callback specified by the callback_type.
 *
 * \param[in,out] module         Pointer to the software module struct
 * \param[in]     callback_type  Callback type to disable
 */
static inline void i2c_master_disable_callback(
		struct i2c_master_module *const module,
		enum i2c_master_callback callback_type)
{
	/* Sanity check. */
	Assert(module);
	Assert(module->hw);

	/* Mark callback as disabled. */
	module->enabled_callback &= ~(1 << callback_type);
}

/** @} */


/**
 * \name Read and Write, Interrupt-Driven
 * @{
 */
 
enum status_code i2c_master_read_packet_job(
		struct i2c_master_module *const module,
		struct i2c_master_packet *const packet);

enum status_code i2c_master_read_packet_job_no_stop(
		struct i2c_master_module *const module,
		struct i2c_master_packet *const packet);

enum status_code i2c_master_write_packet_job(
		struct i2c_master_module *const module,
		struct i2c_master_packet *const packet);

enum status_code i2c_master_write_packet_job_no_stop(
		struct i2c_master_module *const module,
		struct i2c_master_packet *const packet);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* I2C_MASTER_INTERRUPT_H_INCLUDED */
