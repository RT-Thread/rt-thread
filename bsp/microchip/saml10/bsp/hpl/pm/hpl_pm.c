
/**
 * \file
 *
 * \brief SAM Power manager
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#include <hpl_sleep.h>
#include <hpl_reset.h>
#include <hpl_init.h>

/**
 * \brief Retrieve the reset reason
 */
enum reset_reason _get_reset_reason(void)
{
	return (enum reset_reason)hri_rstc_read_RCAUSE_reg(RSTC);
}

/**
 * \brief Set the sleep mode for the device
 */
int32_t _set_sleep_mode(const uint8_t mode)
{
	switch (mode) {
	case 2: /* IDLE */
	case 4: /* STANDBY */
	case 6: /* OFF */
		hri_pm_write_SLEEPCFG_SLEEPMODE_bf(PM, mode);
		break;
	default:
		return ERR_INVALID_ARG;
	}

	return ERR_NONE;
}

/**
 * \brief Set performance level
 */
void _set_performance_level(const uint8_t level)
{
	if (hri_pm_get_PLCFG_PLSEL_bf(PM, PM_PLCFG_PLSEL_Msk) != level) {
		hri_pm_clear_INTFLAG_reg(PM, 0xFF);
		hri_pm_write_PLCFG_PLSEL_bf(PM, level);
		while (!hri_pm_read_INTFLAG_reg(PM))
			;
	}
}
