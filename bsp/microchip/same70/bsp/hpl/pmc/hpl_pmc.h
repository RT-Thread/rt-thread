/**
 * \file
 *
 * \brief Power Management Controller register vG related functionality.
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

#ifndef _HPL_PMC_E70_H_INCLUDED
#define _HPL_PMC_E70_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define PLL_COUNT 0x3fU

#ifndef PMC_PCR_GCLKEN
#define PMC_PCR_GCLKEN (0x1u << 29)
#endif

#ifndef PMC_PCR_GCLKDIV
#define PMC_PCR_GCLKDIV_Pos 20
#define PMC_PCR_GCLKDIV_Msk (0xffu << PMC_PCR_GCLKDIV_Pos)
#define PMC_PCR_GCLKDIV(value) ((PMC_PCR_GCLKDIV_Msk & ((value) << PMC_PCR_GCLKDIV_Pos)))
#endif

#ifndef PMC_PCR_GCLKCSS
#define PMC_PCR_GCLKCSS_Pos 8
#define PMC_PCR_GCLKCSS_Msk (0x07u << PMC_PCR_GCLKCSS_Pos)
#define PMC_PCR_GCLKCSS(value) ((PMC_PCR_GCLKCSS_Msk & ((value) << PMC_PCR_GCLKCSS_Pos)))
#endif

/**
 * \brief Initializes cortex M7 core clock
 *
 */
void _pmc_init(void);

/**
 * \brief Enable the specified peripheral clock.
 *
 * \note The ID must not be shifted (i.e., 1 << ID_xxx).
 *
 * \param periph_id Peripheral ID
 *
 */
static inline void _pmc_enable_periph_clock(uint32_t periph_id)
{
	if (periph_id < 32) {
		if (!hri_pmc_get_PCSR0_reg(PMC, (1 << periph_id))) {
			hri_pmc_set_PCSR0_reg(PMC, (1 << periph_id));
		}
	} else if (periph_id < 64) {
		periph_id -= 32;
		if (!hri_pmc_get_PCSR1_reg(PMC, (1 << periph_id))) {
			hri_pmc_set_PCSR1_reg(PMC, (1 << periph_id));
		}
	} else {
		uint32_t tmp;
		hri_pmc_write_PCR_reg(PMC, PMC_PCR_PID(periph_id));
		tmp = hri_pmc_read_PCR_reg(PMC);
		tmp |= PMC_PCR_CMD | PMC_PCR_EN;
		hri_pmc_write_PCR_reg(PMC, tmp);
	}
}

/**
 * \brief Disable the specified peripheral clock.
 *
 * \note The ID must not be shifted (i.e., 1 << ID_xxx).
 *
 * \param periph_id Peripheral ID
 *
 */
static inline void _pmc_disable_periph_clock(uint32_t periph_id)
{
	if (periph_id < 32) {
		if (hri_pmc_get_PCSR0_reg(PMC, (1 << periph_id))) {
			hri_pmc_clear_PCSR0_reg(PMC, (1 << periph_id));
		}
	} else if (periph_id < 64) {
		periph_id -= 32;
		if (hri_pmc_get_PCSR1_reg(PMC, (1 << periph_id))) {
			hri_pmc_clear_PCSR1_reg(PMC, (1 << periph_id));
		}
	} else {
		uint32_t tmp;
		hri_pmc_write_PCR_reg(PMC, PMC_PCR_PID(periph_id));
		tmp = hri_pmc_read_PCR_reg(PMC);
		tmp |= PMC_PCR_CMD;
		tmp &= ~PMC_PCR_EN;
		hri_pmc_write_PCR_reg(PMC, tmp);
	}
}

/**
 * \brief Enable the gclk clock of I2SC.
 *
 * \note The ID must not be shifted (i.e., 1 << ID_xxx).
 *
 * \param periph_id Peripheral ID
 * \param gclk_css  Generic Clock Source Selection
 * \param gclk_div  Generic Clock Division Ratio. Generic clock is the selected
 *                  clock period divided by GCLKDIV + 1.
 *
 */
static inline void _pmc_enable_gclk_clock(uint32_t periph_id, uint8_t gclk_css, uint8_t gclk_div)
{
	hri_pmc_write_PCR_reg(PMC, PMC_PCR_PID(periph_id));
	if (!(hri_pmc_read_PCR_reg(PMC) & PMC_PCR_EN)) {
		hri_pmc_write_PCR_reg(PMC,
		                      (PMC_PCR_GCLKEN | PMC_PCR_EN | PMC_PCR_CMD | PMC_PCR_GCLKDIV(gclk_div - 1)
		                       | PMC_PCR_GCLKCSS(gclk_css) | PMC_PCR_PID(periph_id)));
	}
}

/**
 * \brief Disable the gclk clock of I2SC.
 *
 * \note The ID must not be shifted (i.e., 1 << ID_xxx).
 *
 * \param periph_id Peripheral ID
 *
 */
static inline void _pmc_disable_gclk_clock(uint32_t periph_id)
{
	hri_pmc_write_PCR_reg(PMC, PMC_PCR_PID(periph_id));
	if ((hri_pmc_read_PCR_reg(PMC) & PMC_PCR_EN)) {
		hri_pmc_write_PCR_reg(PMC, (PMC_PCR_CMD | PMC_PCR_PID(periph_id)));
	}
}

#ifdef __cplusplus
}
#endif

#endif
