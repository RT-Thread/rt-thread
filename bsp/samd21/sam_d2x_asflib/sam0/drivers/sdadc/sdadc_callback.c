/**
 * \file
 *
 * \brief SAM Sigma-Delta Analog-to-Digital Converter Driver
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

#include "sdadc_callback.h"

struct sdadc_module *_sdadc_instances[SDADC_INST_NUM];

static void _sdadc_interrupt_handler(const uint8_t instance)
{
	struct sdadc_module *module = _sdadc_instances[instance];

	/* get interrupt flags and mask out enabled callbacks */
	uint32_t flags = module->hw->INTFLAG.reg;

	if (flags & SDADC_INTFLAG_RESRDY) {
		if ((module->enabled_callback_mask & (1 << SDADC_CALLBACK_READ_BUFFER)) &&
				(module->registered_callback_mask & (1 << SDADC_CALLBACK_READ_BUFFER))) {
			/* clear interrupt flag */
			module->hw->INTFLAG.reg = SDADC_INTFLAG_RESRDY;

			/* store SDADC result in job buffer */
			*(module->job_buffer++) = ((int32_t)(module->hw->RESULT.reg << 8)) >> 8;

			if (--module->remaining_conversions > 0) {
				if (module->software_trigger == true) {
					sdadc_start_conversion(module);
				}
			} else {
				if (module->job_status == STATUS_BUSY) {
					/* job is complete. update status,disable interrupt
					 *and call callback */
					module->job_status = STATUS_OK;
					sdadc_disable_interrupt(module, SDADC_INTERRUPT_RESULT_READY);

					(module->callback[SDADC_CALLBACK_READ_BUFFER])(module);
				}
			}
		}
	}

	if (flags & SDADC_INTFLAG_WINMON) {
		module->hw->INTFLAG.reg = SDADC_INTFLAG_WINMON;
		if ((module->enabled_callback_mask & (1 << SDADC_CALLBACK_WINDOW)) &&
				(module->registered_callback_mask & (1 << SDADC_CALLBACK_WINDOW))) {
			(module->callback[SDADC_CALLBACK_WINDOW])(module);
		}

	}

	if (flags & SDADC_INTFLAG_OVERRUN) {
		module->hw->INTFLAG.reg = SDADC_INTFLAG_OVERRUN;
		if ((module->enabled_callback_mask & (1 << SDADC_CALLBACK_ERROR)) &&
				(module->registered_callback_mask & (1 << SDADC_CALLBACK_ERROR))) {
			(module->callback[SDADC_CALLBACK_ERROR])(module);
		}
	}
}

/** Interrupt handler for the SDADC module. */
void SDADC_Handler(void)
{
	_sdadc_interrupt_handler(0);
}

/**
 * \brief Registers a callback.
 *
 * Registers a callback function which is implemented by the user.
 *
 * \note The callback must be enabled by for the interrupt handler to call it
 * when the condition for the callback is met.
 *
 * \param[in] module         Pointer to SDADC software instance struct
 * \param[in] callback_func  Pointer to callback function
 * \param[in] callback_type  Callback type given by an enum
 *
 */
void sdadc_register_callback(
		struct sdadc_module *const module,
		sdadc_callback_t callback_func,
		enum sdadc_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(callback_func);

	/* Register callback function */
	module->callback[callback_type] = callback_func;

	/* Set the bit corresponding to the callback_type */
	module->registered_callback_mask |= (1 << callback_type);
}

/**
 * \brief Unregisters a callback.
 *
 * Unregisters a callback function which is implemented by the user.
 *
 * \param[in] module         Pointer to SDADC software instance struct
 * \param[in] callback_type  Callback type given by an enum
 *
 */
void sdadc_unregister_callback(
		struct sdadc_module *const module,
		enum sdadc_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	/* Unregister callback function */
	module->callback[callback_type] = NULL;

	/* Clear the bit corresponding to the callback_type */
	module->registered_callback_mask &= ~(1 << callback_type);
}

/**
 * \brief Read multiple samples from SDADC.
 *
 * Read \c samples from the SDADC into the \c buffer.
 * If there is no hardware trigger defined (event action) the
 * driver will retrigger the SDADC conversion whenever a conversion
 * is complete until \c samples has been acquired. To avoid
 * jitter in the sampling frequency using an event trigger is advised.
 *
 * \param[in]  module_inst  Pointer to the SDADC software instance struct
 * \param[in]  samples      Number of samples to acquire
 * \param[out] buffer       Buffer to store the SDADC samples
 *
 * \return Status of the job start.
 * \retval STATUS_OK        The conversion job was started successfully and is
 *                          in progress
 * \retval STATUS_BUSY      The SDADC is already busy with another job
 */
enum status_code sdadc_read_buffer_job(
		struct sdadc_module *const module_inst,
		int32_t *buffer,
		uint16_t samples)
{
	Assert(module_inst);
	Assert(samples);
	Assert(buffer);

	if(module_inst->remaining_conversions != 0 ||
			module_inst->job_status == STATUS_BUSY){
		return STATUS_BUSY;
	}

	module_inst->job_status = STATUS_BUSY;
	module_inst->remaining_conversions = samples;
	module_inst->job_buffer = buffer;

	sdadc_enable_interrupt(module_inst, SDADC_INTERRUPT_RESULT_READY);

	if(module_inst->software_trigger == true) {
		sdadc_start_conversion(module_inst);
	}

	return STATUS_OK;
}

/**
 * \brief Gets the status of a job.
 *
 * Gets the status of an ongoing or the last job.
 *
 * \param [in]  module_inst Pointer to the SDADC software instance struct
 * \param [in]  type        Type of job to abort
 *
 * \return Status of the job.
 */
enum status_code sdadc_get_job_status(
		struct sdadc_module *module_inst,
		enum sdadc_job_type type)
{
	/* Sanity check arguments */
	Assert(module_inst);

	if (type == SDADC_JOB_READ_BUFFER ) {
		return module_inst->job_status;
	} else {
		return STATUS_ERR_INVALID_ARG;
	}
}

/**
 * \brief Aborts an ongoing job.
 *
 * Aborts an ongoing job with given type.
 *
 * \param [in]  module_inst Pointer to the SDADC software instance struct
 * \param [in]  type        Type of job to abort
 */
void sdadc_abort_job(
		struct sdadc_module *module_inst,
		enum sdadc_job_type type)
{
	/* Sanity check arguments */
	Assert(module_inst);

	if (type == SDADC_JOB_READ_BUFFER) {
		/* Disable interrupt */
		sdadc_disable_interrupt(module_inst, SDADC_INTERRUPT_RESULT_READY);
		/* Mark job as aborted */
		module_inst->job_status = STATUS_ABORTED;
		module_inst->remaining_conversions = 0;
	}
}

