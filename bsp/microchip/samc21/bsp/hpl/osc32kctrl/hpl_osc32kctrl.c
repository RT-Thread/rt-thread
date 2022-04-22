/**
 * \file
 *
 * \brief SAM 32k Oscillators Controller.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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
#include <hpl_init.h>
#include <compiler.h>
#include <hpl_osc32kctrl_config.h>

/**
 * \brief Initialize 32 kHz clock sources
 */
void _osc32kctrl_init_sources(void)
{
	void *   hw    = (void *)OSC32KCTRL;
	uint16_t calib = 0;

#if CONF_XOSC32K_CONFIG == 1
	hri_osc32kctrl_write_XOSC32K_reg(
	    hw,
	    OSC32KCTRL_XOSC32K_STARTUP(CONF_XOSC32K_STARTUP) | (CONF_XOSC32K_ONDEMAND << OSC32KCTRL_XOSC32K_ONDEMAND_Pos)
	        | (CONF_XOSC32K_RUNSTDBY << OSC32KCTRL_XOSC32K_RUNSTDBY_Pos)
	        | (CONF_XOSC32K_EN1K << OSC32KCTRL_XOSC32K_EN1K_Pos) | (CONF_XOSC32K_EN32K << OSC32KCTRL_XOSC32K_EN32K_Pos)
	        | (CONF_XOSC32K_XTALEN << OSC32KCTRL_XOSC32K_XTALEN_Pos)
	        | (CONF_XOSC32K_ENABLE << OSC32KCTRL_XOSC32K_ENABLE_Pos));

	hri_osc32kctrl_write_CFDCTRL_reg(hw,
	                                 (CONF_XOSC32K_CFDEN << OSC32KCTRL_CFDCTRL_CFDEN_Pos)
	                                     | (CONF_XOSC32K_SWBEN << OSC32KCTRL_CFDCTRL_SWBACK_Pos));

	hri_osc32kctrl_write_EVCTRL_reg(hw, (CONF_XOSC32K_CFDEO << OSC32KCTRL_EVCTRL_CFDEO_Pos));
#endif

#if CONF_OSC32K_CONFIG == 1
	/* OSC32K calibration value at bit 18:12 of memory 0x00806020 */
	calib = (*((uint32_t *)0x00806020) & 0x007F000) >> 12;
	hri_osc32kctrl_write_OSC32K_reg(
	    hw,
#if CONF_OSC32K_CALIB_ENABLE == 1
	    OSC32KCTRL_OSC32K_CALIB(CONF_OSC32K_CALIB) |
#else
	    OSC32KCTRL_OSC32K_CALIB(calib) |
#endif
	        OSC32KCTRL_OSC32K_STARTUP(CONF_OSC32K_STARTUP) | (CONF_OSC32K_ONDEMAND << OSC32KCTRL_OSC32K_ONDEMAND_Pos)
	        | (CONF_OSC32K_RUNSTDBY << OSC32KCTRL_OSC32K_RUNSTDBY_Pos)
	        | (CONF_OSC32K_EN1K << OSC32KCTRL_OSC32K_EN1K_Pos) | (CONF_OSC32K_EN32K << OSC32KCTRL_OSC32K_EN32K_Pos)
	        | (CONF_OSC32K_ENABLE << OSC32KCTRL_OSC32K_ENABLE_Pos));
#endif
#if CONF_OSCULP32K_CONFIG == 1
	calib = hri_osc32kctrl_read_OSCULP32K_CALIB_bf(hw);
	hri_osc32kctrl_write_OSCULP32K_reg(hw,
#if CONF_OSC32K_CALIB_ENABLE == 1
	                                   OSC32KCTRL_OSCULP32K_CALIB(CONF_OSC32K_CALIB)
#else
	                                   OSC32KCTRL_OSCULP32K_CALIB(calib)
#endif
	);
#endif

#if CONF_XOSC32K_CONFIG
#if CONF_XOSC32K_ENABLE == 1 && CONF_XOSC32K_ONDEMAND == 0
	while (!hri_osc32kctrl_get_STATUS_XOSC32KRDY_bit(hw))
		;
#endif
#if CONF_OSCULP32K_ULP32KSW == 1
	hri_osc32kctrl_set_OSCULP32K_reg(hw, OSC32KCTRL_OSCULP32K_ULP32KSW);
	while (!hri_osc32kctrl_get_STATUS_ULP32KSW_bit(hw))
		;
#endif
#endif

#if CONF_OSC32K_CONFIG == 1
#if CONF_OSC32K_ENABLE == 1 && CONF_OSC32K_ONDEMAND == 0
	while (!hri_osc32kctrl_get_STATUS_OSC32KRDY_bit(hw))
		;
#endif
#endif
	hri_osc32kctrl_write_RTCCTRL_reg(hw, OSC32KCTRL_RTCCTRL_RTCSEL(CONF_RTCCTRL));
	(void)calib;
}
