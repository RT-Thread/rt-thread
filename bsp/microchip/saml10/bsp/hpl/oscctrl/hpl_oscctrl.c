/**
 * \file
 *
 * \brief SAM Oscillators Controller.
 *
 * Copyright (c) 2017-2018 Microchip Technology Inc. and its subsidiaries.
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
#include <compiler.h>
#include <hpl_init.h>
#include <hpl_oscctrl_config.h>
#include <hpl_mclk_config.h>

/**
 * \brief Initialize clock sources
 */
void _oscctrl_init_sources(void)
{
	void *hw = (void *)OSCCTRL;

#if CONF_XOSC_CONFIG == 1
	hri_oscctrl_write_XOSCCTRL_reg(
	    hw,
	    OSCCTRL_XOSCCTRL_STARTUP(CONF_XOSC_STARTUP) | (0 << OSCCTRL_XOSCCTRL_AMPGC_Pos)
	        | OSCCTRL_XOSCCTRL_GAIN(CONF_XOSC_GAIN) | (CONF_XOSC_RUNSTDBY << OSCCTRL_XOSCCTRL_RUNSTDBY_Pos)
	        | (CONF_XOSC_SWBEN << OSCCTRL_XOSCCTRL_SWBEN_Pos) | (CONF_XOSC_CFDEN << OSCCTRL_XOSCCTRL_CFDEN_Pos)
	        | (CONF_XOSC_XTALEN << OSCCTRL_XOSCCTRL_XTALEN_Pos) | (CONF_XOSC_ENABLE << OSCCTRL_XOSCCTRL_ENABLE_Pos));

	hri_oscctrl_write_EVCTRL_reg(hw, (CONF_XOSC_CFDEO << OSCCTRL_EVCTRL_CFDEO_Pos));
#endif

#if CONF_OSC16M_CONFIG == 1
	hri_oscctrl_write_OSC16MCTRL_reg(hw,
	                                 (CONF_OSC16M_RUNSTDBY << OSCCTRL_OSC16MCTRL_RUNSTDBY_Pos)
	                                     | (CONF_OSC16M_ENABLE << OSCCTRL_OSC16MCTRL_ENABLE_Pos)
	                                     | OSCCTRL_OSC16MCTRL_FSEL(CONF_OSC16M_FSEL));
#endif

#if CONF_XOSC_CONFIG == 1
#if CONF_XOSC_ENABLE == 1
	while (!hri_oscctrl_get_STATUS_XOSCRDY_bit(hw))
		;
#endif
#if CONF_XOSC_AMPGC == 1
	hri_oscctrl_set_XOSCCTRL_AMPGC_bit(hw);
#endif
#if CONF_XOSC_ONDEMAND == 1
	hri_oscctrl_set_XOSCCTRL_ONDEMAND_bit(hw);
#endif
#endif

#if CONF_OSC16M_CONFIG == 1
#if CONF_OSC16M_ENABLE == 1
	while (!hri_oscctrl_get_STATUS_OSC16MRDY_bit(hw))
		;
#endif
#if CONF_OSC16M_ONDEMAND == 1
	hri_oscctrl_set_OSC16MCTRL_ONDEMAND_bit(hw);
#endif
#endif
	(void)hw;
}

void _oscctrl_init_referenced_generators(void)
{
	void *                        hw  = (void *)OSCCTRL;
	hri_oscctrl_dfllulpctrl_reg_t tmp = 0;

#if CONF_DFLL_CONFIG == 1
	hri_gclk_write_PCHCTRL_reg(
	    GCLK, OSCCTRL_GCLK_ID_DFLLULP, (1 << GCLK_PCHCTRL_CHEN_Pos) | GCLK_PCHCTRL_GEN(CONF_DFLL_GCLK));

	hri_oscctrl_write_DFLLULPDITHER_reg(
	    hw, OSCCTRL_DFLLULPDITHER_STEP(CONF_DFLL_DITHER_STEP) | OSCCTRL_DFLLULPDITHER_PER(CONF_DFLL_DITHER_PER));

	hri_oscctrl_write_DFLLULPDLY_reg(hw, OSCCTRL_DFLLULPDLY_DELAY(CONF_DFLL_DELAY));

	hri_oscctrl_write_DFLLULPRATIO_reg(hw, OSCCTRL_DFLLULPRATIO_RATIO(CONF_DFLL_RATIO));

	/* Get DFLLULP Division Factor from NVM Software Calibration Area */
#if (CONF_PERFORMANCE_LEVEL == 0)
	uint8_t divider
	    = ((*((uint32_t *)FUSES_DFLLULP_DIV_PL0_ADDR) & FUSES_DFLLULP_DIV_PL0_Msk) >> FUSES_DFLLULP_DIV_PL0_Pos);
#else
	uint8_t divider
	    = ((*((uint32_t *)FUSES_DFLLULP_DIV_PL2_ADDR) & FUSES_DFLLULP_DIV_PL2_Msk) >> FUSES_DFLLULP_DIV_PL2_Pos);
#endif

	tmp = (OSCCTRL_DFLLULPCTRL_DIV(divider) | (CONF_DFLL_RUNSTDBY << OSCCTRL_DFLLULPCTRL_RUNSTDBY_Pos)
	       | (CONF_DFLL_DITHER << OSCCTRL_DFLLULPCTRL_DITHER_Pos) | (CONF_DFLL_SAFE << OSCCTRL_DFLLULPCTRL_SAFE_Pos)
	       | (CONF_DFLL_BINSE << OSCCTRL_DFLLULPCTRL_BINSE_Pos) | (CONF_DFLL_ENABLE << OSCCTRL_DFLLULPCTRL_ENABLE_Pos));
	hri_oscctrl_write_DFLLULPCTRL_reg(hw, tmp);
	while (!hri_oscctrl_get_STATUS_DFLLULPRDY_bit(hw))
		;

#endif

#if CONF_DPLL_CONFIG == 1
#if CONF_DPLL_REFCLK == 2
	hri_gclk_write_PCHCTRL_reg(
	    GCLK, OSCCTRL_GCLK_ID_DPLL, (1 << GCLK_PCHCTRL_CHEN_Pos) | GCLK_PCHCTRL_GEN(CONF_DPLL_GCLK));
#endif
	hri_oscctrl_write_DPLLRATIO_reg(
	    hw, OSCCTRL_DPLLRATIO_LDRFRAC(CONF_DPLL_LDRFRAC) | OSCCTRL_DPLLRATIO_LDR(CONF_DPLL_LDR));
	hri_oscctrl_write_DPLLCTRLB_reg(
	    hw,
	    OSCCTRL_DPLLCTRLB_DIV(CONF_DPLL_DIV) | (CONF_DPLL_LBYPASS << OSCCTRL_DPLLCTRLB_LBYPASS_Pos)
	        | OSCCTRL_DPLLCTRLB_LTIME(CONF_DPLL_LTIME) | OSCCTRL_DPLLCTRLB_REFCLK(CONF_DPLL_REFCLK)
	        | (CONF_DPLL_WUF << OSCCTRL_DPLLCTRLB_WUF_Pos) | (CONF_DPLL_LPEN << OSCCTRL_DPLLCTRLB_LPEN_Pos)
	        | OSCCTRL_DPLLCTRLB_FILTER(CONF_DPLL_FILTER));
	hri_oscctrl_write_DPLLPRESC_reg(hw, OSCCTRL_DPLLPRESC_PRESC(CONF_DPLL_PRESC));
	hri_oscctrl_write_DPLLCTRLA_reg(hw,
	                                (0 << OSCCTRL_DPLLCTRLA_ONDEMAND_Pos)
	                                    | (CONF_DPLL_RUNSTDBY << OSCCTRL_DPLLCTRLA_RUNSTDBY_Pos)
	                                    | (CONF_DPLL_ENABLE << OSCCTRL_DPLLCTRLA_ENABLE_Pos));
#endif

#if CONF_DFLL_CONFIG == 1
	while (!hri_oscctrl_get_STATUS_DFLLULPLOCK_bit(hw))
		;

#if CONF_DFLL_ONDEMAND == 1
	hri_oscctrl_set_DFLLULPCTRL_ONDEMAND_bit(hw);
#endif
#endif

#if CONF_DPLL_CONFIG == 1
#if CONF_DPLL_ENABLE == 1
	while (!(hri_oscctrl_get_DPLLSTATUS_LOCK_bit(hw) || hri_oscctrl_get_DPLLSTATUS_CLKRDY_bit(hw)))
		;
#endif
#if CONF_DPLL_ONDEMAND == 1
	hri_oscctrl_set_DPLLCTRLA_ONDEMAND_bit(hw);
#endif
#endif

#if CONF_DFLL_CONFIG == 1
	while (hri_gclk_read_SYNCBUSY_reg(GCLK))
		;
#endif
	(void)hw, (void)tmp;
}
