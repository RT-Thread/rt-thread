/**
 * \file
 *
 * \brief DFLL management
 *
 * Copyright (c) 2010-2015 Atmel Corporation. All rights reserved.
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
#ifndef CLK_DFLL_H_INCLUDED
#define CLK_DFLL_H_INCLUDED

#include <parts.h>
#include "conf_clock.h"

#if UC3L
# include "uc3l/dfll.h"
#elif SAM4L
# include "sam4l/dfll.h"
#else
# error Unsupported chip type
#endif

/**
 * \ingroup clk_group
 * \defgroup dfll_group DFLL Management
 *
 * A Digital Frequency Locked Loop can be used to generate a highly
 * accurate frequency from a slower-running reference clock, in much the
 * same way as a PLL. DFLLs typically have shorter startup times and
 * less jitter. They can also be used in open-loop mode to generate a
 * less accurate frequency without the use of a reference clock.
 *
 * There may be significant variations between platforms in the support
 * for certain features.
 *
 * \par Example: Setting up DFLL0 with default parameters and dithering enabled
 *
 * The following example shows how to configure and enable DFLL0 in
 * closed-loop mode using the default parameters specified through
 * configuration symbols.
 * \code
	dfll_enable_config_defaults(0); \endcode
 *
 * To configure and enable DFLL0 in closed-loop mode using the default
 * parameters and to enable specific feature like dithering for better accuracy,
 * you can use this initialization process.
 * \code
	struct dfll_config dfllcfg;

	dfll_enable_source(CONFIG_DFLL0_SOURCE);
	dfll_config_defaults(&dfllcfg, 0);
	dfll_config_enable_dithering(&dfllcfg);
	dfll_enable(&dfllcfg, 0);
	dfll_wait_for_accurate_lock(0); \endcode
 *
 * When the last function call returns, DFLL0 is running at a frequency
 * which matches the default configuration as accurately as possible.
 * Any additional alterations to the default configuration can be added
 * at the same place as the call to dfll_config_enable_dithering(), but
 * note that the DFLL will never achieve "accurate" lock if dithering is
 * disabled.
 *
 * @{
 */

//! \name Chip-specific DFLL characteristics
//@{
/**
 * \def NR_DFLLS
 * \brief Number of on-chip DFLLs.
 */
/**
 * \def DFLL_MIN_HZ
 * \brief Minimum frequency that the DFLL can generate.
 */
/**
 * \def DFLL_MAX_HZ
 * \brief Maximum frequency that the DFLL can generate.
 */
//@}

/**
 * \typedef dfll_refclk_t
 * \brief Type used for identifying a reference clock source for the DFLL.
 */

//! \name DFLL Configuration
//@{

/**
 * \struct dfll_config
 * \brief Hardware-specific representation of DFLL configuration.
 *
 * This structure contains one or more device-specific values
 * representing the current DFLL configuration. The contents of this
 * structure is typically different from platform to platform, and the
 * user should not access any fields except through the DFLL
 * configuration API.
 */

/**
 * \fn void dfll_config_init_open_loop_mode(struct dfll_config *cfg)
 * \brief Configure the DFLL configuration \a cfg for open-loop mode.
 *
 * \param cfg The DFLL configuration to be initialized.
 */
/**
 * \fn void dfll_config_init_closed_loop_mode(struct dfll_config *cfg,
 *              dfll_refclk_t refclk, uint16_t div, uint16_t mul)
 * \brief Configure the DFLL configuration \a cfg for closed-loop mode.
 *
 * \param cfg The DFLL configuration to be initialized.
 * \param refclk The reference clock source.
 * \param div Reference clock divider.
 * \param mul Multiplier (integer part only).
 */
/**
 * \def dfll_config_defaults(cfg, dfll_id)
 * \brief Initialize DFLL configuration using default parameters.
 *
 * After this function returns, \a cfg will contain a configuration
 * which will make the DFLL run at (CONFIG_DFLLx_MUL / CONFIG_DFLLx_DIV)
 * times the frequency of CONFIG_DFLLx_SOURCE. The default configuration
 * will always use closed-loop mode with no fractional multiplier.
 *
 * \param cfg The DFLL configuration to be initialized.
 * \param dfll_id Use defaults for this DFLL.
 */
/**
 * \def dfll_get_default_rate(dfll_id)
 * \brief Return the default rate in Hz of \a dfll_id.
 */

/**
 * \fn void dfll_config_set_fractional_multiplier(struct dfll_config *cfg,
 *              uint16_t mul_i, uint16_t mul_f)
 * \brief Set a fractional multiplier.
 *
 * This function has no effect in open-loop mode, and is only available
 * on devices which support fractional multipliers.
 *
 * The fractional part of the multiplier is assumed to be 16 bits. The
 * low-level driver will make sure to shift this value to match the
 * hardware if necessary.
 *
 * \param cfg The DFLL configuration to be modified.
 * \param mul_i Integer part of multiplier.
 * \param mul_f Fractional part of multiplier.
 */
/**
 * \fn void dfll_config_enable_dithering(struct dfll_config *cfg)
 * \brief Enable dithering for more accurate frequency generation.
 *
 * The fine LSB input to the VCO is dithered to achieve fractional
 * approximation to the correct multiplication ratio.
 *
 * \param cfg The DFLL configuration to be modified.
 */
/**
 * \fn void dfll_config_disable_dithering(struct dfll_config *cfg)
 * \brief Disable dithering.
 *
 * \see dfll_config_enable_dithering()
 *
 * \param cfg The DFLL configuration to be modified.
 */
/**
 * \fn void dfll_config_set_initial_tuning(struct dfll_config *cfg,
 *              uint16_t coarse, uint16_t fine)
 * \brief Set initial VCO tuning.
 *
 * In open loop mode, this will determine the frequency of the output.
 *
 * In closed loop mode, this will provide an initial estimate of the VCO
 * tuning. While the DFLL will automatically adjust these values to
 * match the desired output frequency, careful selection of initial
 * values might reduce the time to achieve coarse and fine lock.
 *
 * \param cfg The DFLL configuration to be modified.
 * \param coarse Coarse tuning of the frequency generator.
 * \param fine Fine tuning of the frequency generator.
 */
/**
 * \fn void dfll_config_set_max_step(struct dfll_config *cfg,
 *              uint16_t coarse, uint16_t fine)
 * \brief Set the maximum VCO tuning step size.
 *
 * This function has no effect in open-loop mode.
 *
 * By default, both of these values are set to 50% of their respective
 * maximums.  It is not recommended to set the values any higher than
 * this, but setting them lower might reduce the frequency overshoot at
 * the expense of longer time to achieve coarse and/or fine lock.
 *
 * \param cfg The DFLL configuration to be modified
 * \param coarse The maximum step size of the coarse VCO tuning.
 * \param fine The maximum step size of the fine VCO tuning.
 */
/**
 * \fn void dfll_config_enable_ssg(struct dfll_config *cfg,
 *              uint16_t amplitude, uint16_t step_size)
 * \brief Enable Spread Spectrum Generator.
 *
 * \param cfg The DFLL configuration to be modified.
 * \param amplitude The amplitude of the spread spectrum.
 * \param step_size The step size of the spread spectrum.
 */
/**
 * \fn void dfll_config_disable_ssg(struct dfll_config *cfg)
 * \brief Disable Spread Spectrum Generator.
 *
 * \param cfg The DFLL configuration to be modified.
 */
//@}

//! \name Interaction with the DFLL hardware
//@{
/**
 * \fn void dfll_enable_open_loop(const struct dfll_config *cfg,
 *              unsigned int dfll_id)
 * \brief Activate the configuration \a cfg and enable DFLL \a dfll_id
 * in open-loop mode.
 *
 * \pre The configuration in \a cfg must represent an open-loop
 * configuration.
 *
 * \param cfg The configuration to be activated.
 * \param dfll_id The ID of the DFLL to be enabled.
 */
/**
 * \fn void dfll_enable_closed_loop(const struct dfll_config *cfg,
 *              unsigned int dfll_id)
 * \brief Activate the configuration \a cfg and enable DFLL \a dfll_id
 * in closed-loop mode.
 *
 * \pre The configuration in \a cfg must represent a closed-loop
 * configuration.
 *
 * \param cfg The configuration to be activated.
 * \param dfll_id The ID of the DFLL to be enabled.
 */
/**
 * \fn void dfll_disable_open_loop(unsigned int dfll_id)
 * \brief Disable the DFLL identified by \a dfll_id.
 *
 * \pre The DFLL must have been enabled in open loop mode.
 *
 * \param dfll_id The ID of the DFLL to be disabled.
 */
/**
 * \fn void dfll_disable_closed_loop(unsigned int dfll_id)
 * \brief Disable the DFLL identified by \a dfll_id.
 *
 * \pre The DFLL must have been enabled in closed loop mode.
 *
 * \param dfll_id The ID of the DFLL to be disabled.
 */
/**
 * \fn bool dfll_is_coarse_locked(unsigned int dfll_id)
 * \brief Determine whether or not a DFLL has achieved coarse lock.
 *
 * \param dfll_id The ID of the DFLL to check.
 *
 * \retval true The DFLL has determined the final value of the coarse
 * VCO tuning value.
 * \retval false The DFLL has not yet determined the coarse VCO tuning
 * value, or has not been enabled.
 */
/**
 * \fn bool dfll_is_fine_locked(unsigned int dfll_id)
 * \brief Determine whether or not a DFLL has achieved fine lock.
 *
 * \param dfll_id The ID of the DFLL to check.
 *
 * \retval true The DFLL has determined the final value of the fine VCO
 * tuning value.
 * \retval false The DFLL has not yet determined the fine VCO tuning
 * value, or has not been enabled.
 */
/**
 * \fn bool dfll_is_accurate_locked(unsigned int dfll_id)
 * \brief Determine whether or not a DFLL has achieved accurate lock.
 *
 * \param dfll_id The ID of the DFLL to check.
 *
 * \retval true The DFLL has determined the final dithering duty cycle.
 * \retval false The DFLL has not yet determined the dithering duty
 * cycle, or has not been enabled with dithering enabled.
 */
/**
 * \fn void dfll_enable_source(enum dfll_refclk_t src)
 * \brief Enable the source of the dfll.
 * The source is enabled, if the source is not already running.
 *
 * \param dfll_source src The ID of the DFLL source to enable.
 */
/**
 * \fn void dfll_enable_config_defaults(unsigned int dfll_id)
 * \brief Enable the dfll with the default configuration.
 * DFLL is enabled, if the DFLL is not already locked.
 *
 * \param dfll_id The ID of the DFLL to enable.
 */

/**
 * \brief Wait for the DFLL identified by \a dfll_id to achieve coarse
 * lock.
 *
 * \param dfll_id The ID of the DFLL to wait for.
 *
 * \retval STATUS_OK The DFLL has achieved coarse lock.
 * \retval ERR_TIMEOUT Timed out waiting for lock.
 */
static inline int dfll_wait_for_coarse_lock(unsigned int dfll_id)
{
	/* TODO: Add timeout mechanism */
	while (!dfll_is_coarse_locked(dfll_id)) {
		/* Do nothing */
	}

	return 0;
}

/**
 * \brief Wait for the DFLL identified by \a dfll_id to achieve fine
 * lock.
 *
 * \param dfll_id The ID of the DFLL to wait for.
 *
 * \retval STATUS_OK The DFLL has achieved fine lock.
 * \retval ERR_TIMEOUT Timed out waiting for lock.
 */
static inline int dfll_wait_for_fine_lock(unsigned int dfll_id)
{
	/* TODO: Add timeout mechanism */
	while (!dfll_is_fine_locked(dfll_id)) {
		/* Do nothing */
	}

	return 0;
}

/**
 * \brief Wait for the DFLL identified by \a dfll_id to achieve accurate
 * lock.
 *
 * \param dfll_id The ID of the DFLL to wait for.
 *
 * \retval STATUS_OK The DFLL has achieved accurate lock.
 * \retval ERR_TIMEOUT Timed out waiting for lock.
 */
static inline int dfll_wait_for_accurate_lock(unsigned int dfll_id)
{
	/* TODO: Add timeout mechanism */
	while (!dfll_is_accurate_locked(dfll_id)) {
		/* Do nothing */
	}

	return 0;
}

//@}
//! @}

#endif /* CLK_DFLL_H_INCLUDED */
