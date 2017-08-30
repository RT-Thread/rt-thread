/**
 *
 * \file
 *
 * \brief SAM Segment Liquid Crystal Display(SLCD) Controller.
 *
 * This file defines a useful set of functions for the SLCD on SAM devices.
 *
 * Copyright (c) 2015-2016 Atmel Corporation. All rights reserved.
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

#include <slcd.h>
#include <conf_slcd.h>

#include <system.h>

#if !defined(CONF_SLCD_CLOCK_SOURCE)
#  warning  SLCD_CLOCK_SOURCE is not defined, assuming 0.
#  define CONF_SLCD_CLOCK_SOURCE 0
#endif

#if !defined(CONF_SLCD_DUTY)
#  warning  CONF_SLCD_DUTY is not defined, assuming 0.
#  define CONF_SLCD_DUTY 0
#endif

#if !defined(CONF_SLCD_BIAS)
#  warning  CONF_SLCD_BIAS is not defined, assuming 0.
#  define CONF_SLCD_BIAS 0
#endif

#if !defined(CONF_SLCD_PVAL)
#  warning  CONF_SLCD_PVAL is not defined, assuming 0.
#  define CONF_SLCD_PVAL 0
#endif

#if !defined(CONF_SLCD_CKDIV)
#  warning  CONF_SLCD_CKDIV is not defined, assuming 0.
#  define CONF_SLCD_CKDIV 0
#endif

#if !defined(CONF_SLCD_VLCD_SEL)
#  warning  CONF_SLCD_VLCD_SEL is not defined, assuming 0.
#  define CONF_SLCD_VLCD_SEL 0
#endif

#if !defined(CONF_SLCD_REF_REFRESH_FREQ)
#  warning  CONF_SLCD_REF_REFRESH_FREQ is not defined, assuming 0.
#  define CONF_SLCD_REF_REFRESH_FREQ 0
#endif

#if !defined(CONF_SLCD_POWER_REFRESH_FREQ)
#  warning  CONF_SLCD_POWER_REFRESH_FREQ is not defined, assuming 0.
#  define CONF_SLCD_POWER_REFRESH_FREQ 0
#endif

#if !defined(CONF_SLCD_POWER_MODE)
#  warning  CONF_SLCD_POWER_MODE is not defined, assuming 0.
#  define CONF_SLCD_POWER_MODE 0
#endif

#if !defined(CONF_SLCD_PIN_L_MASK)
#  warning  CONF_SLCD_PIN_L_MASK is not defined, assuming 0.
#  define CONF_SLCD_PIN_L_MASK 0
#endif

#if !defined(CONF_SLCD_PIN_H_MASK)
#  warning  CONF_SLCD_PIN_H_MASK is not defined, assuming 0.
#  define CONF_SLCD_PIN_H_MASK 0
#endif

/**
 * \brief Initializes SLCD configurations struct to defaults
 *
 * Initailizes SLCD configuration struct to predefined safe default settings.
 *
 * \param[in] config Pointer to an instance of \ref struct slcd_config
 *
 */
void slcd_get_config_defaults(struct slcd_config *config)
{
	Assert(config);

	config->run_in_standby = false;
	config->waveform_mode = SLCD_LOW_POWER_WAVEFORM_MODE;
	config->low_resistance_duration = 0;
	config->enable_low_resistance = false;
	config->bias_buffer_duration = 0;
	config->enable_bias_buffer = false;
}

/**
 * \brief Initialize SLCD module
 *
 * \param[in] config  Pointer to an SLCD configuration structure
 *
 *  \note SLCD cannot be Initialized while it is enabled.
 *
 * \return Status of the configuration procedure.
 * \retval STATUS_OK SLCD configuration went successful
 * \retval STATUS_ERR_INVALID_ARG  If an invalid configuration was supplied
 */
enum status_code slcd_init(struct slcd_config *const config)
{
	if (!config) {
		return STATUS_ERR_INVALID_ARG;
	}
	system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBC, MCLK_APBCMASK_SLCD);

	/* Select SLCD clock */
	OSC32KCTRL->SLCDCTRL.reg = CONF_SLCD_CLOCK_SOURCE & OSC32KCTRL_SLCDCTRL_MASK;

	slcd_disable();
	slcd_reset();

	SLCD->CTRLA.reg = SLCD_CTRLA_DUTY(CONF_SLCD_DUTY) | SLCD_CTRLA_BIAS(CONF_SLCD_BIAS)
					 | SLCD_CTRLA_PRESC(CONF_SLCD_PVAL) | SLCD_CTRLA_CKDIV(CONF_SLCD_CKDIV)
					 | (CONF_SLCD_VLCD_SEL << SLCD_CTRLA_XVLCD_Pos)
					 | (config->run_in_standby << SLCD_CTRLA_RUNSTDBY_Pos)
					 | SLCD_CTRLA_RRF(CONF_SLCD_REF_REFRESH_FREQ)
					 | SLCD_CTRLA_PRF(CONF_SLCD_POWER_REFRESH_FREQ)
					 | (config->waveform_mode << SLCD_CTRLA_WMOD_Pos);
	SLCD->CTRLB.reg = SLCD_CTRLB_BBD(config->bias_buffer_duration)
  					| (config->enable_bias_buffer << SLCD_CTRLB_BBEN_Pos)
  					| SLCD_CTRLB_LRD(config->low_resistance_duration)
  					| (config->enable_low_resistance << SLCD_CTRLB_LREN_Pos);


    SLCD->CTRLC.reg |= SLCD_CTRLC_LPPM(CONF_SLCD_POWER_MODE) | SLCD_CTRLC_CTST(0x0F);

	SLCD->LPENL.reg = CONF_SLCD_PIN_L_MASK & SLCD_LPENL_MASK;
	SLCD->LPENH.reg = CONF_SLCD_PIN_H_MASK & SLCD_LPENH_MASK;

   return STATUS_OK;
}

/**
 * \brief Enables the SLCD module
 *
 * Enables the SLCD module once it has been configured, ready for use. Most
 * module configuration parameters cannot be altered while the module is enabled.
 */

void slcd_enable(void)
{
	SLCD->CTRLA.reg |= SLCD_CTRLA_ENABLE;

	while (slcd_is_syncing()) {
		/* Wait for synchronization */
	}

	while (!slcd_get_vlcd_ready_status()) {
   	}
}

/**
 * \brief Disables the SLCD module
 *
 * Disables the SLCD module.
 */
void slcd_disable(void)
{
	SLCD->INTENCLR.reg = SLCD_INTENCLR_MASK;
	SLCD->INTFLAG.reg = SLCD_INTFLAG_MASK;
	SLCD->CTRLA.reg &= ~(SLCD_CTRLA_ENABLE);
	while (slcd_is_syncing()) {
		/* Wait for synchronization */
	}
}

/**
 * \brief Check if SLCD module is enabled or not
 *
 * Check if SLCD module is enabled or not.
 *
 * \return Enable status.
 * \retval true SLCD module is enabled
 * \retval false SLCD module is disabled
 */

bool slcd_is_enabled(void)
{
	return ((SLCD->CTRLA.reg & SLCD_CTRLA_ENABLE) == SLCD_CTRLA_ENABLE);
}

/**
 * \brief Reset the SLCD module
 *
 * Reset the SLCD module.
 */
void slcd_reset(void)
{
	slcd_disable();
	SLCD->CTRLA.reg |= SLCD_CTRLA_SWRST;
	while (slcd_is_syncing()) {
		/* Wait for synchronization */
	}
}

/**
 * \brief Set the SLCD fine contrast
 *
 * The LCD contrast is defined by the value of VLCD voltage. The higher is the
 * VLCD voltage, the higher is the contrast. The software contrast adjustment
 * is only possible in internal supply mode.
 * In internal supply mode, VLCD is in the range 2.5V to 3.5V. VLCD can be
 * adjusted with 16 steps, each step is 60 mV.The contrast value can be written
 * at any time.
 *
 * \param[in] contrast Contrast value
 *
 * \return Status of set contrast.
 * \retval STATUS_OK               SLCD contrast set successful
 * \retval STATUS_ERR_INVALID_ARG  SLCD is not working in internal supply mode
 */
enum status_code slcd_set_contrast(uint8_t contrast)
{

	if (SLCD->CTRLA.bit.XVLCD) {
		return STATUS_ERR_INVALID_ARG;
	}
	uint16_t temp = SLCD->CTRLC.reg;

	temp &= ~ SLCD_CTRLC_CTST(0xf);
	temp |= SLCD_CTRLC_CTST(contrast);

	SLCD->CTRLC.reg = temp;
	return STATUS_OK;
}

/**
 * \brief Initializes SLCD blink configurations struct to defaults
 *
 * Initailizes SLCD blink configuration struct to predefined safe default settings.
 *
 * \param[in] config Pointer to an instance of \ref struct slcd_blink_config
 *
 */
void slcd_blink_get_config_defaults(struct slcd_blink_config *blink_config)
{
	Assert(blink_config);

	blink_config->fc = SLCD_FRAME_COUNTER_0;
	blink_config->blink_all_seg = true;
}

/**
 * \brief Set SLCD blink mode
 *
 * Set SLCD blink mode.
 *
 *  \note SLCD blink cannot be set while module or blink is enabled.
 *
 * \param[in] config  Pointer to an SLCD blink configuration structure
 *
 * \return Status of the configuration procedure.
 * \retval STATUS_OK               SLCD blink configuration went successful
 * \retval STATUS_ERR_INVALID_ARG  If blink configuration failed
 */

enum status_code  slcd_blink_set_config(struct slcd_blink_config *const blink_config)
{
	if (!blink_config) {
		return STATUS_ERR_INVALID_ARG;
	}

	SLCD->BCFG.bit.MODE = (!(blink_config->blink_all_seg) << SLCD_BCFG_MODE_Pos);
	SLCD->BCFG.bit.FCS	= SLCD_BCFG_FCS(blink_config->fc);
	return STATUS_OK;
}

/**
 * \brief Start an SLCD pixel/segment blinking
 *
 * \param[in] pix_com Pixel/segment COM coordinate
 * \param[in] pix_seg Pixel/segment SEG coordinate (range 0 to 1 inclusive)
 */
void slcd_set_blink_pixel(
		uint8_t pix_com,
		uint8_t pix_seg)
{
	/* Validate parameters. */
	Assert(pix_seg<=1);
	
	if (pix_seg == 0) {
		SLCD->BCFG.reg |= SLCD_BCFG_BSS0(1 << pix_com);
	}

	if (pix_seg == 1) {
		SLCD->BCFG.reg |= SLCD_BCFG_BSS1(1 << pix_com);
	}
}

/**
 * \brief Stop a specified SLCD pixel/segment from blinking
 *
 * \param[in] pix_com Pixel/segment COM coordinate
 * \param[in] pix_seg Pixel/segment SEG coordinate (range 0 to 1 inclusive)
 */
void slcd_clear_blink_pixel(
		uint8_t pix_com,
		uint8_t pix_seg)
{
	/* Validate parameters. */
	Assert(pix_seg<=1);
	
	if (pix_seg == 0) {
		SLCD->BCFG.reg &= ~ SLCD_BCFG_BSS0(1 << pix_com);
	}

	if (pix_seg == 1) {
		SLCD->BCFG.reg &= ~ SLCD_BCFG_BSS1(1 << pix_com);
	}
}

/**
 * \brief Stop all SLCD pixels/segments from blinking
 */
void slcd_clear_blink_all_pixel(void)
{
	SLCD->BCFG.bit.BSS0 = 0;
	SLCD->BCFG.bit.BSS1 = 0;
}


/**
 * \brief Set all bits in the SLCD display memory high
 */
void slcd_set_display_memory(void)
{
	SLCD->SDATAH0.reg = SLCD_SDATAH0_MASK;
	SLCD->SDATAL0.reg = SLCD_SDATAL0_MASK;
	SLCD->SDATAH1.reg = SLCD_SDATAH1_MASK;
	SLCD->SDATAL1.reg = SLCD_SDATAL1_MASK;
	SLCD->SDATAH2.reg = SLCD_SDATAH2_MASK;
	SLCD->SDATAL2.reg = SLCD_SDATAL2_MASK;
	SLCD->SDATAH3.reg = SLCD_SDATAH3_MASK;
	SLCD->SDATAL3.reg = SLCD_SDATAL3_MASK;
	SLCD->SDATAH4.reg = SLCD_SDATAH4_MASK;
	SLCD->SDATAL4.reg = SLCD_SDATAL4_MASK;
	SLCD->SDATAH5.reg = SLCD_SDATAH5_MASK;
	SLCD->SDATAL5.reg = SLCD_SDATAL5_MASK;
	SLCD->SDATAH6.reg = SLCD_SDATAH6_MASK;
	SLCD->SDATAL6.reg = SLCD_SDATAL6_MASK;
	SLCD->SDATAH7.reg = SLCD_SDATAH7_MASK;
	SLCD->SDATAL7.reg = SLCD_SDATAL7_MASK;
}


/**
 * \brief Enable the specified pixel/segment in the SLCD display memory
 *
 * \param[in] pix_com Pixel/segment COM coordinate,within [0-7]
 * \param[in] pix_seg Pixel/segment SEG coordinate within [0-43]
 */
 void slcd_set_pixel(
		uint8_t pix_com,
		uint8_t pix_seg)
{
	if ((pix_com < SLCD_MAX_COM) &&
			(pix_seg < SLCD_MAX_SEG)) {
		switch(pix_com){
			case 0:
				if (pix_seg >= 32) {
					SLCD->SDATAH0.reg |= (1 <<(pix_seg-32));
				} else {
					SLCD->SDATAL0.reg |= 1 <<pix_seg;
				}
				break;
			case 1:
				if (pix_seg >= 32) {
					SLCD->SDATAH1.reg |= (1 <<(pix_seg-32));
				} else {
					SLCD->SDATAL1.reg |= 1 <<pix_seg;
				}
				break;
			case 2:
				if (pix_seg >= 32) {
					SLCD->SDATAH2.reg |= (1 <<(pix_seg-32));
				} else {
					SLCD->SDATAL2.reg |= 1 <<pix_seg;
				}
				break;
			case 3:
				if (pix_seg >= 32) {
					SLCD->SDATAH3.reg |= (1 <<(pix_seg-32));
				} else {
					SLCD->SDATAL3.reg |= 1 <<pix_seg;
				}
				break;
			case 4:
				if (pix_seg >= 32) {
					SLCD->SDATAH4.reg |= (1 <<(pix_seg-32));
				} else {
					SLCD->SDATAL4.reg |= 1 <<pix_seg;
				}
				break;
			case 5:
				if (pix_seg >= 32) {
					SLCD->SDATAH5.reg |= (1 <<(pix_seg-32));
				} else {
					SLCD->SDATAL5.reg |= 1 <<pix_seg;
				}
				break;
			case 6:
				if (pix_seg >= 32) {
					SLCD->SDATAH6.reg |= (1 <<(pix_seg-32));
				} else {
					SLCD->SDATAL6.reg |= 1 <<pix_seg;
				}
				break;
			case 7:
				if (pix_seg >= 32) {
					SLCD->SDATAH7.reg |= (1 <<(pix_seg-32));
				} else {
					SLCD->SDATAL7.reg |= 1 <<pix_seg;
				}
				break;
		}
		while (slcd_get_char_writing_status()) {
		}
	}
}

/**
 * \brief Disable the specified pixel/segment in the SLCD display memory
 *
 * \param[in] pix_com Pixel/segment COM coordinate
 * \param[in] pix_seg Pixel/segment SEG coordinate
 */
 void slcd_clear_pixel(uint8_t pix_com, uint8_t pix_seg)
{
	if ((pix_com < SLCD_MAX_COM) &&
			(pix_seg < SLCD_MAX_SEG)) {
		switch(pix_com){
			case 0:
				if (pix_seg >= 32) {
					SLCD->SDATAH0.reg &= ~(1 <<(pix_seg-32));
				} else {
					SLCD->SDATAL0.reg &= ~(1 <<pix_seg);
				}
				break;
			case 1:
				if (pix_seg >= 32) {
					SLCD->SDATAH1.reg &= ~(1 <<(pix_seg-32));
				} else {
					SLCD->SDATAL1.reg &= ~(1 <<pix_seg);
				}
				break;
			case 2:
				if (pix_seg >= 32) {
					SLCD->SDATAH2.reg &= (1 <<(pix_seg-32));
				} else {
					SLCD->SDATAL2.reg &= ~(1 <<pix_seg);
				}
				break;
			case 3:
				if (pix_seg >= 32) {
					SLCD->SDATAH3.reg &= ~(1 <<(pix_seg-32));
				} else {
					SLCD->SDATAL3.reg &= ~(1 <<pix_seg);
				}
				break;
			case 4:
				if (pix_seg >= 32) {
					SLCD->SDATAH4.reg &= ~(1 <<(pix_seg-32));
				} else {
					SLCD->SDATAL4.reg &= ~(1 <<pix_seg);
				}
				break;
			case 5:
				if (pix_seg >= 32) {
					SLCD->SDATAH5.reg &= ~(1 <<(pix_seg-32));
				} else {
					SLCD->SDATAL5.reg &= ~(1 <<pix_seg);
				}
				break;
			case 6:
				if (pix_seg >= 32) {
					SLCD->SDATAH6.reg &= ~(1 <<(pix_seg-32));
				} else {
					SLCD->SDATAL6.reg &= ~(1 <<pix_seg);
				}
				break;
			case 7:
				if (pix_seg >= 32) {
					SLCD->SDATAH7.reg &= ~(1 <<(pix_seg-32));
				} else {
					SLCD->SDATAL7.reg &= ~(1 <<pix_seg);
				}
				break;
		}
		while (slcd_get_char_writing_status()) {
		}
	}
}

/**
 * \brief Set the specified segment in the SLCD display memory
 *
 * \param[in] pix_seg     Pixel/segment SEG coordinate
 * \param[in] byte_offset Byte offset in display memory
 * \param[in] seg_mask    Byte offset in display memory
 */
void slcd_set_seg_data(uint8_t seg_data,uint8_t byte_offset,uint8_t seg_mask)
{
	SLCD->ISDATA.reg = SLCD_ISDATA_SDATA(seg_data)
					 | SLCD_ISDATA_OFF(byte_offset)
					 | SLCD_ISDATA_SDMASK(seg_mask);

	while (slcd_get_char_writing_status()) {
	}
}

/**
 * \brief Initializes SLCD Automated Character configurations struct to defaults
 *
 * Initailizes SLCD Automated Character configuration struct to predefined safe default settings.
 *
 * \param[in] config Pointer to an instance of \ref struct slcd_automated_char_config
 *
 */
void slcd_automated_char_get_config_default(
		struct slcd_automated_char_config *config)
{
	Assert(config);

	config->order = SLCD_AUTOMATED_CHAR_START_FROM_BOTTOM_RIGHT;
	config->fc = SLCD_FRAME_COUNTER_0;
	config->mode = SLCD_AUTOMATED_CHAR_SEQ;
	config->seg_line_num = 0;
	config->start_seg_line = 0;
	config->row_digit_num = 1;
	config->digit_num = 0;
	config->scrolling_step = 1;
	config->com_line_num = 1;
	config->data_mask = 0;

}

/**
 * \brief Set SLCD automated character
 *
 * Set automated character mode.
 *
 *  \note SLCD automated character mode cannot be set while module or
 * automated character is enabled.
 *
 * \param[in] config  Pointer to an SLCD automated character configuration structure
 *
 * \return Status of the configuration procedure.
 * \retval STATUS_OK               SLCD automated character configuration went successful
 * \retval STATUS_ERR_INVALID_ARG  If automated character  configuration failed
 */
enum status_code slcd_automated_char_set_config(
		struct slcd_automated_char_config *const config)
{
	if (!config) {
		return STATUS_ERR_INVALID_ARG;
	}
	SLCD->CMCFG.reg = SLCD_CMCFG_NSEG(config->seg_line_num)
					 | (config->order  << SLCD_CMCFG_DEC_Pos);
	SLCD->ACMCFG.reg = SLCD_ACMCFG_FCS(config->fc)
					 | (config->mode << SLCD_ACMCFG_MODE_Pos)
					 | SLCD_ACMCFG_STSEG(config->start_seg_line)
					 | SLCD_ACMCFG_NDROW(config->row_digit_num)
					 | SLCD_ACMCFG_NDIG(config->digit_num)
					 | SLCD_ACMCFG_STEPS(config->scrolling_step)
					 | SLCD_ACMCFG_NCOM(config->com_line_num);

	SLCD->CMDMASK.reg = SLCD_CMDMASK_SDMASK(config->data_mask);

	return STATUS_OK;
}

/**
 * \brief Set SLCD character mapping
 *
 * Set Character mode amd SEG line per digit.
 *
 * \param[in] order         Mapping order in char mode
 * \param[in] seg_line_num  Define the number of SEG line per digit,
 *                          it equal to number of SEG line - 1
 */
void slcd_character_map_set(
		enum slcd_automated_char_order order,
		uint8_t seg_line_num)
{
	SLCD->CMCFG.reg = SLCD_CMCFG_NSEG(seg_line_num)
					 | (order  << SLCD_CMCFG_DEC_Pos);
}

/**
 * \brief Write segments data to display memory in character mode
 *
 * \param[in] seg_data       Pixel/segment data
 * \param[in] data_mask      Segments data mask
 * \param[in] com_line_index COM line index
 * \param[in] seg_line_index Segments line index
 */
void slcd_character_write_data(uint8_t com_line_index,
									uint8_t seg_line_index,
									uint32_t seg_data,uint32_t data_mask)
{

	SLCD->CMINDEX.reg = SLCD_CMINDEX_SINDEX(seg_line_index)
						| SLCD_CMINDEX_CINDEX(com_line_index);
	SLCD->CMDMASK.reg = SLCD_CMDMASK_SDMASK(data_mask);
	SLCD->CMDATA.reg = SLCD_CMDATA_SDATA(seg_data);
	while (slcd_get_char_writing_status()) {
	}
}

/**
 * \brief Initializes circular shift configurations struct to defaults
 *
 * Initailizes circular shift configuration struct to predefined safe default settings.
 *
 * \param[in] config Pointer to an instance of \ref struct slcd_circular_shift_config
 *
 */
void slcd_circular_shift_get_config_defaults(
		struct slcd_circular_shift_config *const config)
{
	Assert(config);

	config->fc = SLCD_FRAME_COUNTER_0;
	config->dir = SLCD_CIRCULAR_SHIFT_LEFT;
	config->size = 0;
	config->data = 0;
}

/**
 * \brief Set SLCD circular shift
 *
 * Set circular shift mode.
 *
 * \note SLCD circular shift mode cannot be set while module or circular shift is enabled.
 *
 * \param[in] config  Pointer to an SLCD circular shift configuration structure
 *
 * \return Status of the configuration procedure.
 * \retval STATUS_OK               SLCD circular shift configuration went successful
 * \retval STATUS_ERR_INVALID_ARG  If circular shift configuration failed
 */

enum status_code slcd_circular_shift_set_config(
		struct slcd_circular_shift_config *const config)
{
	if (!config) {
		return STATUS_ERR_INVALID_ARG;
	}
	SLCD->CSRCFG.reg = SLCD_CSRCFG_FCS(config->fc)
					 | (config->dir << SLCD_CSRCFG_DIR_Pos)
					 | SLCD_CSRCFG_SIZE(config->size)
					 | SLCD_CSRCFG_DATA(config->data);

	return STATUS_OK;
}

