/**
 * \file
 *
 * \brief SAM Analog Front-End Controller (AFEC)
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#include <hpl_adc_sync.h>
#include <hpl_adc_async.h>
#include <utils_repeat_macro.h>
#include <utils_assert.h>
#include <utils.h>

#include "hpl_afec_config.h"

#ifndef CONF_AFEC_0_ENABLE
#define CONF_AFEC_0_ENABLE 0
#endif
#ifndef CONF_AFEC_1_ENABLE
#define CONF_AFEC_1_ENABLE 0
#endif

#define AFEC_CHANNEL_AMOUNT 12

/** Build configuration from header macros. */
#define AFEC_CONFIGURATION(n)                                                                                          \
	{                                                                                                                  \
		(n),                                                                                                           \
		    (uint32_t)(((uint32_t)(CONF_AFEC_##n##_USEQ) << 31) | (AFEC_MR_TRANSFER(CONF_AFEC_##n##_TRANSFER))         \
		               | (AFEC_MR_TRACKTIM(CONF_AFEC_##n##_TRACKTIM)) | (AFEC_MR_ONE)                                  \
		               | (AFEC_MR_STARTUP(CONF_AFEC_##n##_STARTUP)) | (AFEC_MR_PRESCAL(CONF_AFEC_##n##_PRESCAL))       \
		               | (CONF_AFEC_##n##_FREERUN << 7) | (CONF_AFEC_##n##_FWUP << 6) | (CONF_AFEC_##n##_SLEEP << 5)   \
		               | (AFEC_MR_TRGSEL(CONF_AFEC_##n##_TRGSEL)) | (CONF_AFEC_##n##_TRGEN << 0)),                     \
		    (uint32_t)((AFEC_EMR_SIGNMODE(CONF_AFEC_##n##_SIGNMODE)) | (CONF_AFEC_##n##_STM << 25)                     \
		               | (CONF_AFEC_##n##_TAG << 24) | (AFEC_EMR_RES(CONF_AFEC_##n##_RES))                             \
		               | (CONF_AFEC_##n##_CMPALL << 9) | (AFEC_EMR_CMPSEL(CONF_AFEC_##n##_CMPSEL))                     \
		               | (AFEC_EMR_CMPMODE(CONF_AFEC_##n##_CMPMODE))),                                                 \
		    (uint32_t)(0 | (AFEC_SEQ1R_USCH0(CONF_AFEC_##n##_USCH0)) | (AFEC_SEQ1R_USCH1(CONF_AFEC_##n##_USCH1))       \
		               | (AFEC_SEQ1R_USCH2(CONF_AFEC_##n##_USCH2)) | (AFEC_SEQ1R_USCH3(CONF_AFEC_##n##_USCH3))         \
		               | (AFEC_SEQ1R_USCH4(CONF_AFEC_##n##_USCH4)) | (AFEC_SEQ1R_USCH5(CONF_AFEC_##n##_USCH5))         \
		               | (AFEC_SEQ1R_USCH6(CONF_AFEC_##n##_USCH6)) | (AFEC_SEQ1R_USCH7(CONF_AFEC_##n##_USCH7))),       \
		    (uint32_t)(0 | (AFEC_SEQ2R_USCH8(CONF_AFEC_##n##_USCH8)) | (AFEC_SEQ2R_USCH9(CONF_AFEC_##n##_USCH9))       \
		               | (AFEC_SEQ2R_USCH10(CONF_AFEC_##n##_USCH10)) | (AFEC_SEQ2R_USCH11(CONF_AFEC_##n##_USCH11))),   \
		    (uint32_t)((AFEC_CWR_HIGHTHRES(CONF_AFEC_##n##_HIGHTHRES))                                                 \
		               | (AFEC_CWR_LOWTHRES(CONF_AFEC_##n##_LOWTHRES))),                                               \
		    (uint32_t)(0 | (AFEC_CGR_GAIN0(CONF_AFEC_##n##_GAIN0)) | (AFEC_CGR_GAIN1(CONF_AFEC_##n##_GAIN1))           \
		               | (AFEC_CGR_GAIN2(CONF_AFEC_##n##_GAIN2)) | (AFEC_CGR_GAIN3(CONF_AFEC_##n##_GAIN3))             \
		               | (AFEC_CGR_GAIN4(CONF_AFEC_##n##_GAIN4)) | (AFEC_CGR_GAIN5(CONF_AFEC_##n##_GAIN5))             \
		               | (AFEC_CGR_GAIN6(CONF_AFEC_##n##_GAIN6)) | (AFEC_CGR_GAIN7(CONF_AFEC_##n##_GAIN7))             \
		               | (AFEC_CGR_GAIN8(CONF_AFEC_##n##_GAIN8)) | (AFEC_CGR_GAIN9(CONF_AFEC_##n##_GAIN9))             \
		               | (AFEC_CGR_GAIN10(CONF_AFEC_##n##_GAIN10)) | (AFEC_CGR_GAIN11(CONF_AFEC_##n##_GAIN11))),       \
		    (uint32_t)(0 | (CONF_AFEC_##n##_DIFF0 << 0) | (CONF_AFEC_##n##_DIFF1 << 1) | (CONF_AFEC_##n##_DIFF2 << 2)  \
		               | (CONF_AFEC_##n##_DIFF3 << 3) | (CONF_AFEC_##n##_DIFF4 << 4) | (CONF_AFEC_##n##_DIFF5 << 5)    \
		               | (CONF_AFEC_##n##_DIFF6 << 6) | (CONF_AFEC_##n##_DIFF7 << 7) | (CONF_AFEC_##n##_DIFF8 << 8)    \
		               | (CONF_AFEC_##n##_DIFF9 << 9) | (CONF_AFEC_##n##_DIFF10 << 10)                                 \
		               | (CONF_AFEC_##n##_DIFF11 << 11)),                                                              \
		    (uint32_t)(AFEC_ACR_IBCTL(CONF_AFEC_##n##_IBCTL) | (AFEC_ACR_PGA0EN | AFEC_ACR_PGA1EN)),                   \
		    (uint32_t)(0 | (CONF_AFEC_##n##_DUAL0 << 0) | (CONF_AFEC_##n##_DUAL1 << 1) | (CONF_AFEC_##n##_DUAL2 << 2)  \
		               | (CONF_AFEC_##n##_DUAL3 << 3) | (CONF_AFEC_##n##_DUAL4 << 4) | (CONF_AFEC_##n##_DUAL5 << 5)    \
		               | (CONF_AFEC_##n##_DUAL6 << 6) | (CONF_AFEC_##n##_DUAL7 << 7) | (CONF_AFEC_##n##_DUAL8 << 8)    \
		               | (CONF_AFEC_##n##_DUAL9 << 9) | (CONF_AFEC_##n##_DUAL10 << 10)                                 \
		               | (CONF_AFEC_##n##_DUAL11 << 11)),                                                              \
		    (uint32_t)(CONF_AFEC_##n##_COSR_CSEL),                                                                     \
		    (uint32_t)(AFEC_CVR_GAINCORR(CONF_AFEC_##n##_OFFSETCORR)                                                   \
		               | (AFEC_CVR_OFFSETCORR(CONF_AFEC_##n##_GAINCORR))),                                             \
		    (uint32_t)(0 | (CONF_AFEC_##n##_ECORR0 << 0) | (CONF_AFEC_##n##_ECORR1 << 1)                               \
		               | (CONF_AFEC_##n##_ECORR2 << 2) | (CONF_AFEC_##n##_ECORR3 << 3) | (CONF_AFEC_##n##_ECORR4 << 4) \
		               | (CONF_AFEC_##n##_ECORR5 << 5) | (CONF_AFEC_##n##_ECORR6 << 6) | (CONF_AFEC_##n##_ECORR7 << 7) \
		               | (CONF_AFEC_##n##_ECORR8 << 8) | (CONF_AFEC_##n##_ECORR9 << 9)                                 \
		               | (CONF_AFEC_##n##_ECORR10 << 10) | (CONF_AFEC_##n##_ECORR11 << 11)),                           \
		    {                                                                                                          \
		        (uint32_t)AFEC_COCR_AOFF(CONF_AFEC_##n##_AOFF0),                                                       \
		        (uint32_t)AFEC_COCR_AOFF(CONF_AFEC_##n##_AOFF1),                                                       \
		        (uint32_t)AFEC_COCR_AOFF(CONF_AFEC_##n##_AOFF2),                                                       \
		        (uint32_t)AFEC_COCR_AOFF(CONF_AFEC_##n##_AOFF3),                                                       \
		        (uint32_t)AFEC_COCR_AOFF(CONF_AFEC_##n##_AOFF4),                                                       \
		        (uint32_t)AFEC_COCR_AOFF(CONF_AFEC_##n##_AOFF5),                                                       \
		        (uint32_t)AFEC_COCR_AOFF(CONF_AFEC_##n##_AOFF6),                                                       \
		        (uint32_t)AFEC_COCR_AOFF(CONF_AFEC_##n##_AOFF7),                                                       \
		        (uint32_t)AFEC_COCR_AOFF(CONF_AFEC_##n##_AOFF8),                                                       \
		        (uint32_t)AFEC_COCR_AOFF(CONF_AFEC_##n##_AOFF9),                                                       \
		        (uint32_t)AFEC_COCR_AOFF(CONF_AFEC_##n##_AOFF10),                                                      \
		        (uint32_t)AFEC_COCR_AOFF(CONF_AFEC_##n##_AOFF11),                                                      \
		    },                                                                                                         \
	}

/**
 * \brief AFEC configuration
 */
struct afec_configuration {
	uint8_t  number;
	uint32_t mr;
	uint32_t emr;
	uint32_t seq1r;
	uint32_t seq2r;
	uint32_t cwr;
	uint32_t cgr;
	uint32_t diffr;
	uint32_t acr;
	uint32_t shmr;
	uint32_t cosr;
	uint32_t cvr;
	uint32_t cecr;
	uint32_t cocr[AFEC_CHANNEL_AMOUNT];
};

#define AFEC_AMOUNT (CONF_AFEC_0_ENABLE + CONF_AFEC_1_ENABLE)

#if AFEC_AMOUNT < 1
/** Dummy array for compiling. */
static const struct afec_configuration _afecs[1] = {{0}};
#else
/**
 * \brief Array of AFEC configurations
 */
static const struct afec_configuration _afecs[] = {
#if CONF_AFEC_0_ENABLE == 1
    AFEC_CONFIGURATION(0),
#endif
#if CONF_AFEC_1_ENABLE == 1
    AFEC_CONFIGURATION(1),
#endif
};
#endif

/**
 * \brief Retrieve ordinal number of the given afec hardware instance
 */
static uint8_t _afec_get_hardware_index(const void *const hw)
{
	if (hw == AFEC0) {
		return 0;
	} else if (hw == AFEC1) {
		return 1;
	}

	ASSERT(false);
	return 0;
}

/** \brief Return the pointer to register settings of specific afec
 *  \param[in] hw_addr The hardware register base address.
 *  \return Pointer to register settings of specific afec.
 */
static uint8_t _afec_get_regs(const uint32_t hw_addr)
{
	uint8_t n = _afec_get_hardware_index((const void *)hw_addr);
	uint8_t i;

	for (i = 0; i < sizeof(_afecs) / sizeof(struct afec_configuration); i++) {
		if (_afecs[i].number == n) {
			return i;
		}
	}

	return 0;
}

/**
 * \brief Retrieve IRQ number for the given hardware instance
 */
static IRQn_Type _afec_get_irq_num(const struct _adc_async_device *const device)
{
	if (device->hw == AFEC0) {
		return AFEC0_IRQn;
	} else if (device->hw == AFEC1) {
		return AFEC1_IRQn;
	}

	return (IRQn_Type)-1;
}

/**
 * \brief Init irq param with the given afec hardware instance
 */
static void _afec_init_irq_param(const void *const hw, struct _adc_async_device *dev)
{
}

/**
 * \brief Initialize ADC
 *
 * \param[in] hw The pointer to hardware instance
 * \param[in] i The number of hardware instance
 */
static int32_t _afec_init(void *const hw, const uint8_t i)
{
	uint8_t cnt;

	hri_afec_write_MR_reg(hw, _afecs[i].mr);
	hri_afec_write_EMR_reg(hw, _afecs[i].emr);
	hri_afec_write_SEQ1R_reg(hw, _afecs[i].seq1r);
	hri_afec_write_SEQ2R_reg(hw, _afecs[i].seq2r);
	hri_afec_write_CWR_reg(hw, _afecs[i].cwr);
	hri_afec_write_CGR_reg(hw, _afecs[i].cgr);
	hri_afec_write_DIFFR_reg(hw, _afecs[i].diffr);
	hri_afec_write_ACR_reg(hw, _afecs[i].acr);
	hri_afec_write_SHMR_reg(hw, _afecs[i].shmr);
	hri_afec_write_COSR_reg(hw, _afecs[i].cosr);
	hri_afec_write_CVR_reg(hw, _afecs[i].cvr);
	hri_afec_write_CECR_reg(hw, _afecs[i].cecr);

	for (cnt = 0; cnt < AFEC_CHANNEL_AMOUNT; cnt++) {
		hri_afec_write_CSELR_reg(hw, cnt);
		hri_afec_write_COCR_reg(hw, _afecs[i].cocr[cnt]);
	}

	return ERR_NONE;
}

/**
 * \brief De-initialize ADC
 *
 * \param[in] hw The pointer to hardware instance
 */
static inline void _afec_deinit(void *hw)
{
	hri_afec_clear_CHSR_reg(hw, AFEC_CHDR_MASK);
	hri_afec_write_CR_reg(hw, AFEC_CR_SWRST);
}

/**
 * \internal ADC interrupt handler
 *
 * \param[in] p The pointer to interrupt parameter
 */
static void _afec_interrupt_handler(struct _adc_async_device *device)
{
	void *const       hw = device->hw;
	volatile uint32_t status;
	uint8_t           cnt = 0;

	status = hri_afec_read_ISR_reg(hw) & hri_afec_read_IMR_reg(hw);
	if (status & AFEC_IMR_COMPE) {
		device->adc_async_cb.window_cb(device, cnt);
	}
	if (status & AFEC_IMR_GOVRE) {
		device->adc_async_cb.error_cb(device, cnt);
	}
	status &= 0xFFFu;
	cnt = 32 - clz(status);
	while (cnt) {
		cnt--;
		hri_afec_write_CSELR_reg(device->hw, cnt);
		device->adc_async_ch_cb.convert_done(device, cnt, hri_afec_read_CDR_reg(device->hw));
		status &= ~(1 << cnt);
		cnt = 32 - clz(status);
	}
}

/**
 * \brief Initialize ADC
 */
int32_t _adc_sync_init(struct _adc_sync_device *const device, void *const hw)
{
	ASSERT(device);

	device->hw = hw;

	return _afec_init(hw, _afec_get_regs((uint32_t)hw));
}

/**
 * \brief Initialize ADC
 */
int32_t _adc_async_init(struct _adc_async_device *const device, void *const hw)
{
	int32_t init_status;

	ASSERT(device);

	init_status = _afec_init(hw, _afec_get_regs((uint32_t)hw));
	if (init_status) {
		return init_status;
	}

	device->hw = hw;
	_afec_init_irq_param(hw, device);
	NVIC_DisableIRQ(_afec_get_irq_num(device));
	NVIC_ClearPendingIRQ(_afec_get_irq_num(device));
	NVIC_EnableIRQ(_afec_get_irq_num(device));

	return ERR_NONE;
}

/**
 * \brief De-initialize ADC
 */
void _adc_sync_deinit(struct _adc_sync_device *const device)
{
	_afec_deinit(device->hw);
}

/**
 * \brief De-initialize ADC
 */
void _adc_async_deinit(struct _adc_async_device *const device)
{
	NVIC_DisableIRQ(_afec_get_irq_num(device));
	NVIC_ClearPendingIRQ(_afec_get_irq_num(device));

	_afec_deinit(device->hw);
}

/**
 * \brief Enable ADC
 */
void _adc_sync_enable_channel(struct _adc_sync_device *const device, const uint8_t channel)
{
	hri_afec_set_CHSR_reg(device->hw, (1 << channel));
}

/**
 * \brief Enable ADC
 */
void _adc_async_enable_channel(struct _adc_async_device *const device, const uint8_t channel)
{
	hri_afec_set_CHSR_reg(device->hw, (1 << channel));
}

/**
 * \brief Disable ADC
 */
void _adc_sync_disable_channel(struct _adc_sync_device *const device, const uint8_t channel)
{
	hri_afec_clear_CHSR_reg(device->hw, (1 << channel));
}

/**
 * \brief Disable ADC
 */
void _adc_async_disable_channel(struct _adc_async_device *const device, const uint8_t channel)
{
	hri_afec_clear_CHSR_reg(device->hw, (1 << channel));
}

/**
 * \brief Retrieve ADC conversion data size
 */
uint8_t _adc_sync_get_data_size(const struct _adc_sync_device *const device)
{
	(void)device;

	return 2;
}

/**
 * \brief Retrieve ADC conversion data size
 */
uint8_t _adc_async_get_data_size(const struct _adc_async_device *const device)
{
	(void)device;

	return 2;
}

/**
 * \brief Check if conversion is done
 */
bool _adc_sync_is_channel_conversion_done(const struct _adc_sync_device *const device, const uint8_t channel)
{
	return hri_afec_get_ISR_reg(device->hw, (1 << channel));
}

/**
 * \brief Check if conversion is done
 */
bool _adc_async_is_channel_conversion_done(const struct _adc_async_device *const device, const uint8_t channel)
{
	return hri_afec_get_ISR_reg(device->hw, (1 << channel));
}

/**
 * \brief Make conversion
 */
void _adc_sync_convert(struct _adc_sync_device *const device)
{
	hri_afec_write_CR_reg(device->hw, AFEC_CR_START);
}

/**
 * \brief Make conversion
 */
void _adc_async_convert(struct _adc_async_device *const device)
{
	hri_afec_write_CR_reg(device->hw, AFEC_CR_START);
}

/**
 * \brief Retrieve the conversion result
 */
uint16_t _adc_sync_read_channel_data(const struct _adc_sync_device *const device, const uint8_t channel)
{
	hri_afec_write_CSELR_reg(device->hw, channel);

	return hri_afec_read_CDR_reg(device->hw);
}

/**
 * \brief Retrieve the conversion result
 */
uint16_t _adc_async_read_channel_data(const struct _adc_async_device *const device, const uint8_t channel)
{
	hri_afec_write_CSELR_reg(device->hw, channel);

	return hri_afec_read_CDR_reg(device->hw);
}

/**
 * \brief Set reference source
 */
void _adc_sync_set_reference_source(struct _adc_sync_device *const device, const adc_reference_t reference)
{
	(void)device;
	(void)reference;
}

/**
 * \brief Set reference source
 */
void _adc_async_set_reference_source(struct _adc_async_device *const device, const adc_reference_t reference)
{
	(void)device;
	(void)reference;
}

/**
 * \brief Set resolution
 */
void _adc_sync_set_resolution(struct _adc_sync_device *const device, const adc_resolution_t resolution)
{
	hri_afec_write_EMR_RES_bf(device->hw, resolution);
}

/**
 * \brief Set resolution
 */
void _adc_async_set_resolution(struct _adc_async_device *const device, const adc_resolution_t resolution)
{
	hri_afec_write_EMR_RES_bf(device->hw, resolution);
}

/**
 * \brief Set channels input sources
 */
void _adc_sync_set_inputs(struct _adc_sync_device *const device, const adc_pos_input_t pos_input,
                          const adc_neg_input_t neg_input, const uint8_t channel)
{
	(void)device;
	(void)pos_input;
	(void)neg_input;
	(void)channel;
}

/**
 * \brief Set channels input sources
 */
void _adc_async_set_inputs(struct _adc_async_device *const device, const adc_pos_input_t pos_input,
                           const adc_neg_input_t neg_input, const uint8_t channel)
{
	(void)device;
	(void)pos_input;
	(void)neg_input;
	(void)channel;
}

/**
 * \brief Set thresholds
 */
void _adc_sync_set_thresholds(struct _adc_sync_device *const device, const adc_threshold_t low_threshold,
                              const adc_threshold_t up_threshold)
{
	hri_afec_write_CWR_LOWTHRES_bf(device->hw, low_threshold);
	hri_afec_write_CWR_HIGHTHRES_bf(device->hw, up_threshold);
}

/**
 * \brief Set thresholds
 */
void _adc_async_set_thresholds(struct _adc_async_device *const device, const adc_threshold_t low_threshold,
                               const adc_threshold_t up_threshold)
{
	hri_afec_write_CWR_LOWTHRES_bf(device->hw, low_threshold);
	hri_afec_write_CWR_HIGHTHRES_bf(device->hw, up_threshold);
}

/**
 * \brief Set gain
 */
void _adc_sync_set_channel_gain(struct _adc_sync_device *const device, const uint8_t channel, const adc_gain_t gain)
{
	hri_afec_clear_CGR_reg(device->hw, (0x3u << (channel * 2)));
	hri_afec_set_CGR_reg(device->hw, (gain << (channel * 2)));
}

/**
 * \brief Set gain
 */
void _adc_async_set_channel_gain(struct _adc_async_device *const device, const uint8_t channel, const adc_gain_t gain)
{
	hri_afec_clear_CGR_reg(device->hw, (0x3u << (channel * 2)));
	hri_afec_set_CGR_reg(device->hw, (gain << (channel * 2)));
}

/**
 * \brief Set conversion mode
 */
void _adc_sync_set_conversion_mode(struct _adc_sync_device *const device, const enum adc_conversion_mode mode)
{
	if (ADC_CONVERSION_MODE_FREERUN == mode) {
		hri_afec_set_MR_FREERUN_bit(device->hw);
	} else {
		hri_afec_clear_MR_FREERUN_bit(device->hw);
	}
}

/**
 * \brief Set conversion mode
 */
void _adc_async_set_conversion_mode(struct _adc_async_device *const device, const enum adc_conversion_mode mode)
{
	if (ADC_CONVERSION_MODE_FREERUN == mode) {
		hri_afec_set_MR_FREERUN_bit(device->hw);
	} else {
		hri_afec_clear_MR_FREERUN_bit(device->hw);
	}
}

/**
 * \brief Set differential mode
 */
void _adc_sync_set_channel_differential_mode(struct _adc_sync_device *const device, const uint8_t channel,
                                             const enum adc_differential_mode mode)
{
	if (ADC_DIFFERENTIAL_MODE_DIFFERENTIAL == mode) {
		hri_afec_set_DIFFR_reg(device->hw, (0x1u << channel));
	} else {
		hri_afec_clear_DIFFR_reg(device->hw, (0x1u << channel));
	}
}

/**
 * \brief Set differential mode
 */
void _adc_async_set_channel_differential_mode(struct _adc_async_device *const device, const uint8_t channel,
                                              const enum adc_differential_mode mode)
{
	ASSERT(!(channel % 2));

	if (ADC_DIFFERENTIAL_MODE_DIFFERENTIAL == mode) {
		hri_afec_set_DIFFR_reg(device->hw, (0x3u << channel));
	} else {
		hri_afec_clear_DIFFR_reg(device->hw, (0x3u << channel));
	}
}

/**
 * \brief Set window mode
 */
void _adc_sync_set_window_mode(struct _adc_sync_device *const device, const adc_window_mode_t mode)
{
	hri_afec_write_EMR_CMPMODE_bf(device->hw, mode);
}

/**
 * \brief Set window mode
 */
void _adc_async_set_window_mode(struct _adc_async_device *const device, const adc_window_mode_t mode)
{
	hri_afec_write_EMR_CMPMODE_bf(device->hw, mode);
}

/**
 * \brief Retrieve threshold state
 */
void _adc_sync_get_threshold_state(const struct _adc_sync_device *const device, adc_threshold_status_t *const state)
{
	*state = hri_afec_get_ISR_COMPE_bit(device->hw);
}

/**
 * \brief Retrieve threshold state
 */
void _adc_async_get_threshold_state(const struct _adc_async_device *const device, adc_threshold_status_t *const state)
{
	*state = hri_afec_get_ISR_COMPE_bit(device->hw);
}

/**
 * \brief Enable/disable ADC interrupt
 *
 * param[in] device The pointer to ADC device instance
 * param[in] type The type of interrupt to disable/enable if applicable
 * param[in] state Enable or disable
 */
void _adc_async_set_irq_state(struct _adc_async_device *const device, const uint8_t channel,
                              const enum _adc_async_callback_type type, const bool state)
{
	void *const hw = device->hw;

	if (ADC_ASYNC_DEVICE_MONITOR_CB == type) {
		hri_afec_write_IMR_COMPE_bit(hw, state);
	} else if (ADC_ASYNC_DEVICE_ERROR_CB == type) {
		hri_afec_write_IMR_GOVRE_bit(hw, state);
	} else if (ADC_ASYNC_DEVICE_CONVERT_CB == type) {
		if (state) {
			hri_afec_set_IMR_reg(hw, (0x1u << channel));
		} else {
			hri_afec_clear_IMR_reg(hw, (0x1u << channel));
		}
	}
}
