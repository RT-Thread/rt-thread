
/**
 * \file
 *
 * \brief SAM Analog Digital Converter
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

#include <hpl_adc_async.h>
#include <hpl_adc_dma.h>
#include <hpl_adc_sync.h>
#include <utils_assert.h>
#include <utils_repeat_macro.h>
#include <hpl_adc_config.h>

#ifndef CONF_ADC_0_ENABLE
#define CONF_ADC_0_ENABLE 0
#endif
#ifndef CONF_ADC_1_ENABLE
#define CONF_ADC_1_ENABLE 0
#endif

/**
 * \brief Macro is used to fill ADC configuration structure based on its number
 *
 * \param[in] n The number of structures
 */
#define ADC_CONFIGURATION(n)                                                                                           \
	{                                                                                                                  \
		(n),                                                                                                           \
		    (CONF_ADC_##n##_RUNSTDBY << ADC_CTRLA_RUNSTDBY_Pos) | (CONF_ADC_##n##_ONDEMAND << ADC_CTRLA_ONDEMAND_Pos), \
		    ADC_CTRLB_PRESCALER(CONF_ADC_##n##_PRESCALER),                                                             \
		    (CONF_ADC_##n##_REFCOMP << ADC_REFCTRL_REFCOMP_Pos) | ADC_REFCTRL_REFSEL(CONF_ADC_##n##_REFSEL),           \
		    (CONF_ADC_##n##_WINMONEO << ADC_EVCTRL_WINMONEO_Pos)                                                       \
		        | (CONF_ADC_##n##_RESRDYEO << ADC_EVCTRL_RESRDYEO_Pos)                                                 \
		        | (CONF_ADC_##n##_STARTINV << ADC_EVCTRL_STARTINV_Pos)                                                 \
		        | (CONF_ADC_##n##_FLUSHINV << ADC_EVCTRL_FLUSHINV_Pos)                                                 \
		        | (CONF_ADC_##n##_STARTEI << ADC_EVCTRL_STARTEI_Pos)                                                   \
		        | (CONF_ADC_##n##_FLUSHEI << ADC_EVCTRL_FLUSHEI_Pos),                                                  \
		    ADC_INPUTCTRL_MUXNEG(CONF_ADC_##n##_MUXNEG) | ADC_INPUTCTRL_MUXPOS(CONF_ADC_##n##_MUXPOS),                 \
		    ADC_CTRLC_WINMODE(CONF_ADC_##n##_WINMODE) | ADC_CTRLC_RESSEL(CONF_ADC_##n##_RESSEL)                        \
		        | (CONF_ADC_##n##_CORREN << ADC_CTRLC_CORREN_Pos) | (CONF_ADC_##n##_FREERUN << ADC_CTRLC_FREERUN_Pos)  \
		        | (CONF_ADC_##n##_LEFTADJ << ADC_CTRLC_LEFTADJ_Pos)                                                    \
		        | (CONF_ADC_##n##_DIFFMODE << ADC_CTRLC_DIFFMODE_Pos),                                                 \
		    ADC_AVGCTRL_ADJRES(CONF_ADC_##n##_ADJRES) | ADC_AVGCTRL_SAMPLENUM(CONF_ADC_##n##_SAMPLENUM),               \
		    (CONF_ADC_##n##_OFFCOMP << ADC_SAMPCTRL_OFFCOMP_Pos) | ADC_SAMPCTRL_SAMPLEN(CONF_ADC_##n##_SAMPLEN),       \
		    ADC_WINLT_WINLT(CONF_ADC_##n##_WINLT), ADC_WINUT_WINUT(CONF_ADC_##n##_WINUT),                              \
		    ADC_GAINCORR_GAINCORR(CONF_ADC_##n##_GAINCORR), ADC_OFFSETCORR_OFFSETCORR(CONF_ADC_##n##_OFFSETCORR),      \
		    CONF_ADC_##n##_DBGRUN << ADC_DBGCTRL_DBGRUN_Pos, ADC_SEQCTRL_SEQEN(CONF_ADC_##n##_SEQEN),                  \
	}

/**
 * \brief ADC configuration
 */
struct adc_configuration {
	uint8_t                  number;
	hri_adc_ctrla_reg_t      ctrl_a;
	hri_adc_ctrlb_reg_t      ctrl_b;
	hri_adc_refctrl_reg_t    ref_ctrl;
	hri_adc_evctrl_reg_t     ev_ctrl;
	hri_adc_inputctrl_reg_t  input_ctrl;
	hri_adc_ctrlc_reg_t      ctrl_c;
	hri_adc_avgctrl_reg_t    avg_ctrl;
	hri_adc_sampctrl_reg_t   samp_ctrl;
	hri_adc_winlt_reg_t      win_lt;
	hri_adc_winut_reg_t      win_ut;
	hri_adc_gaincorr_reg_t   gain_corr;
	hri_adc_offsetcorr_reg_t offset_corr;
	hri_adc_dbgctrl_reg_t    dbg_ctrl;
	hri_adc_seqctrl_reg_t    seq_ctrl;
};

#define ADC_AMOUNT (CONF_ADC_0_ENABLE + CONF_ADC_1_ENABLE)

/**
 * \brief Array of ADC configurations
 */
static const struct adc_configuration _adcs[] = {
#if CONF_ADC_0_ENABLE == 1
    ADC_CONFIGURATION(0),
#endif
#if CONF_ADC_1_ENABLE == 1
    ADC_CONFIGURATION(1),
#endif
};

static void _adc_set_reference_source(void *const hw, const adc_reference_t reference);

/**
 * \brief Retrieve ordinal number of the given adc hardware instance
 */
static uint8_t _adc_get_hardware_index(const void *const hw)
{

	(void)hw;
	return 0;
}

/** \brief Return the pointer to register settings of specific ADC
 *  \param[in] hw_addr The hardware register base address.
 *  \return Pointer to register settings of specific ADC.
 */
static uint8_t _adc_get_regs(const uint32_t hw_addr)
{
	uint8_t n = _adc_get_hardware_index((const void *)hw_addr);
	uint8_t i;

	for (i = 0; i < sizeof(_adcs) / sizeof(struct adc_configuration); i++) {
		if (_adcs[i].number == n) {
			return i;
		}
	}

	ASSERT(false);
	return 0;
}

/**
 * \brief Retrieve IRQ number for the given hardware instance
 */
static uint8_t _adc_get_irq_num(const struct _adc_async_device *const device)
{

	(void)device;
	return ADC_OTHER_IRQn;
}

/**
 * \brief Init irq param with the given afec hardware instance
 */
static void _adc_init_irq_param(const void *const hw, struct _adc_async_device *dev)
{
}

/**
 * \brief Initialize ADC
 *
 * \param[in] hw The pointer to hardware instance
 * \param[in] i The number of hardware instance
 */
static int32_t _adc_init(void *const hw, const uint8_t i)
{
	uint16_t calib_reg = 0;
	calib_reg          = ADC_CALIB_BIASREFBUF((*(uint32_t *)ADC_FUSES_BIASREFBUF_ADDR >> ADC_FUSES_BIASREFBUF_Pos))
	            | ADC_CALIB_BIASCOMP((*(uint32_t *)ADC_FUSES_BIASCOMP_ADDR >> ADC_FUSES_BIASCOMP_Pos));

	ASSERT(hw == ADC);

	if (!hri_adc_is_syncing(hw, ADC_SYNCBUSY_SWRST)) {
		if (hri_adc_get_CTRLA_reg(hw, ADC_CTRLA_ENABLE)) {
			hri_adc_clear_CTRLA_ENABLE_bit(hw);
			hri_adc_wait_for_sync(hw, ADC_SYNCBUSY_ENABLE);
		}
		hri_adc_write_CTRLA_reg(hw, ADC_CTRLA_SWRST);
	}
	hri_adc_wait_for_sync(hw, ADC_SYNCBUSY_SWRST);

	hri_adc_write_CALIB_reg(hw, calib_reg);
	hri_adc_write_CTRLB_reg(hw, _adcs[i].ctrl_b);
	hri_adc_write_REFCTRL_reg(hw, _adcs[i].ref_ctrl);
	hri_adc_write_EVCTRL_reg(hw, _adcs[i].ev_ctrl);
	hri_adc_write_INPUTCTRL_reg(hw, _adcs[i].input_ctrl);
	hri_adc_write_CTRLC_reg(hw, _adcs[i].ctrl_c);
	hri_adc_write_AVGCTRL_reg(hw, _adcs[i].avg_ctrl);
	hri_adc_write_SAMPCTRL_reg(hw, _adcs[i].samp_ctrl);
	hri_adc_write_WINLT_reg(hw, _adcs[i].win_lt);
	hri_adc_write_WINUT_reg(hw, _adcs[i].win_ut);
	hri_adc_write_GAINCORR_reg(hw, _adcs[i].gain_corr);
	hri_adc_write_OFFSETCORR_reg(hw, _adcs[i].offset_corr);
	hri_adc_write_DBGCTRL_reg(hw, _adcs[i].dbg_ctrl);
	hri_adc_write_SEQCTRL_reg(hw, _adcs[i].seq_ctrl);
	hri_adc_write_CTRLA_reg(hw, _adcs[i].ctrl_a);

	return ERR_NONE;
}

/**
 * \brief De-initialize ADC
 *
 * \param[in] hw The pointer to hardware instance
 */
static inline void _adc_deinit(void *hw)
{
	hri_adc_clear_CTRLA_ENABLE_bit(hw);
	hri_adc_set_CTRLA_SWRST_bit(hw);
}

/**
 * \brief Initialize ADC
 */
int32_t _adc_sync_init(struct _adc_sync_device *const device, void *const hw)
{
	ASSERT(device);

	device->hw = hw;

	return _adc_init(hw, _adc_get_regs((uint32_t)hw));
}

/**
 * \brief Initialize ADC
 */
int32_t _adc_async_init(struct _adc_async_device *const device, void *const hw)
{
	int32_t init_status;

	ASSERT(device);

	init_status = _adc_init(hw, _adc_get_regs((uint32_t)hw));
	if (init_status) {
		return init_status;
	}
	device->hw = hw;
	_adc_init_irq_param(hw, device);
	NVIC_DisableIRQ(_adc_get_irq_num(device) + 0);
	NVIC_ClearPendingIRQ(_adc_get_irq_num(device) + 0);
	NVIC_EnableIRQ(_adc_get_irq_num(device) + 0);
	NVIC_DisableIRQ(_adc_get_irq_num(device) + 1);
	NVIC_ClearPendingIRQ(_adc_get_irq_num(device) + 1);
	NVIC_EnableIRQ(_adc_get_irq_num(device) + 1);
	return ERR_NONE;
}

/**
 * \brief Initialize ADC
 */
int32_t _adc_dma_init(struct _adc_dma_device *const device, void *const hw)
{
	ASSERT(device);

	device->hw = hw;

	return _adc_init(hw, _adc_get_regs((uint32_t)hw));
}

/**
 * \brief De-initialize ADC
 */
void _adc_sync_deinit(struct _adc_sync_device *const device)
{
	_adc_deinit(device->hw);
}

/**
 * \brief De-initialize ADC
 */
void _adc_async_deinit(struct _adc_async_device *const device)
{
	NVIC_DisableIRQ(_adc_get_irq_num(device));
	NVIC_ClearPendingIRQ(_adc_get_irq_num(device));

	_adc_deinit(device->hw);
}

/**
 * \brief De-initialize ADC
 */
void _adc_dma_deinit(struct _adc_dma_device *const device)
{
	_adc_deinit(device->hw);
}

/**
 * \brief Enable ADC
 */
void _adc_sync_enable_channel(struct _adc_sync_device *const device, const uint8_t channel)
{
	(void)channel;

	hri_adc_set_CTRLA_ENABLE_bit(device->hw);
}

/**
 * \brief Enable ADC
 */
void _adc_async_enable_channel(struct _adc_async_device *const device, const uint8_t channel)
{
	(void)channel;

	hri_adc_set_CTRLA_ENABLE_bit(device->hw);
}

/**
 * \brief Enable ADC
 */
void _adc_dma_enable_channel(struct _adc_dma_device *const device, const uint8_t channel)
{
	(void)channel;

	hri_adc_set_CTRLA_ENABLE_bit(device->hw);
}

/**
 * \brief Disable ADC
 */
void _adc_sync_disable_channel(struct _adc_sync_device *const device, const uint8_t channel)
{
	(void)channel;

	hri_adc_clear_CTRLA_ENABLE_bit(device->hw);
}

/**
 * \brief Disable ADC
 */
void _adc_async_disable_channel(struct _adc_async_device *const device, const uint8_t channel)
{
	(void)channel;

	hri_adc_clear_CTRLA_ENABLE_bit(device->hw);
}

/**
 * \brief Disable ADC
 */
void _adc_dma_disable_channel(struct _adc_dma_device *const device, const uint8_t channel)
{
	(void)channel;

	hri_adc_clear_CTRLA_ENABLE_bit(device->hw);
}

/**
 * \brief Return address of ADC DMA source
 */
uint32_t _adc_get_source_for_dma(struct _adc_dma_device *const device)
{
	return (uint32_t) & (((Adc *)(device->hw))->RESULT.reg);
}

/**
 * \brief Retrieve ADC conversion data size
 */
uint8_t _adc_sync_get_data_size(const struct _adc_sync_device *const device)
{
	return hri_adc_read_CTRLC_RESSEL_bf(device->hw) == ADC_CTRLC_RESSEL_8BIT_Val ? 1 : 2;
}

/**
 * \brief Retrieve ADC conversion data size
 */
uint8_t _adc_async_get_data_size(const struct _adc_async_device *const device)
{
	return hri_adc_read_CTRLC_RESSEL_bf(device->hw) == ADC_CTRLC_RESSEL_8BIT_Val ? 1 : 2;
}

/**
 * \brief Retrieve ADC conversion data size
 */
uint8_t _adc_dma_get_data_size(const struct _adc_dma_device *const device)
{
	return hri_adc_read_CTRLC_RESSEL_bf(device->hw) == ADC_CTRLC_RESSEL_8BIT_Val ? 1 : 2;
}

/**
 * \brief Check if conversion is done
 */
bool _adc_sync_is_channel_conversion_done(const struct _adc_sync_device *const device, const uint8_t channel)
{
	(void)channel;

	return hri_adc_get_interrupt_RESRDY_bit(device->hw);
}

/**
 * \brief Check if conversion is done
 */
bool _adc_async_is_channel_conversion_done(const struct _adc_async_device *const device, const uint8_t channel)
{
	(void)channel;

	return hri_adc_get_interrupt_RESRDY_bit(device->hw);
}

/**
 * \brief Check if conversion is done
 */
bool _adc_dma_is_conversion_done(const struct _adc_dma_device *const device)
{
	return hri_adc_get_interrupt_RESRDY_bit(device->hw);
}

/**
 * \brief Make conversion
 */
void _adc_sync_convert(struct _adc_sync_device *const device)
{
	hri_adc_set_SWTRIG_START_bit(device->hw);
}

/**
 * \brief Make conversion
 */
void _adc_async_convert(struct _adc_async_device *const device)
{
	hri_adc_set_SWTRIG_START_bit(device->hw);
}

/**
 * \brief Make conversion
 */
void _adc_dma_convert(struct _adc_dma_device *const device)
{
	hri_adc_set_SWTRIG_START_bit(device->hw);
}

/**
 * \brief Retrieve the conversion result
 */
uint16_t _adc_sync_read_channel_data(const struct _adc_sync_device *const device, const uint8_t channel)
{
	(void)channel;

	return hri_adc_read_RESULT_reg(device->hw);
}

/**
 * \brief Retrieve the conversion result
 */
uint16_t _adc_async_read_channel_data(const struct _adc_async_device *const device, const uint8_t channel)
{
	(void)channel;

	return hri_adc_read_RESULT_reg(device->hw);
}

/**
 * \brief Set reference source
 */
void _adc_sync_set_reference_source(struct _adc_sync_device *const device, const adc_reference_t reference)
{
	_adc_set_reference_source(device->hw, reference);
}

/**
 * \brief Set reference source
 */
void _adc_async_set_reference_source(struct _adc_async_device *const device, const adc_reference_t reference)
{
	_adc_set_reference_source(device->hw, reference);
}

/**
 * \brief Set reference source
 */
void _adc_dma_set_reference_source(struct _adc_dma_device *const device, const adc_reference_t reference)
{
	_adc_set_reference_source(device->hw, reference);
}

/**
 * \brief Set resolution
 */
void _adc_sync_set_resolution(struct _adc_sync_device *const device, const adc_resolution_t resolution)
{
	hri_adc_write_CTRLC_RESSEL_bf(device->hw, resolution);
}

/**
 * \brief Set resolution
 */
void _adc_async_set_resolution(struct _adc_async_device *const device, const adc_resolution_t resolution)
{
	hri_adc_write_CTRLC_RESSEL_bf(device->hw, resolution);
}

/**
 * \brief Set resolution
 */
void _adc_dma_set_resolution(struct _adc_dma_device *const device, const adc_resolution_t resolution)
{
	hri_adc_write_CTRLC_RESSEL_bf(device->hw, resolution);
}

/**
 * \brief Set channels input sources
 */
void _adc_sync_set_inputs(struct _adc_sync_device *const device, const adc_pos_input_t pos_input,
                          const adc_neg_input_t neg_input, const uint8_t channel)
{
	(void)channel;

	hri_adc_write_INPUTCTRL_MUXPOS_bf(device->hw, pos_input);
	hri_adc_write_INPUTCTRL_MUXNEG_bf(device->hw, neg_input);
}

/**
 * \brief Set channels input sources
 */
void _adc_async_set_inputs(struct _adc_async_device *const device, const adc_pos_input_t pos_input,
                           const adc_neg_input_t neg_input, const uint8_t channel)
{
	(void)channel;

	hri_adc_write_INPUTCTRL_MUXPOS_bf(device->hw, pos_input);
	hri_adc_write_INPUTCTRL_MUXNEG_bf(device->hw, neg_input);
}

/**
 * \brief Set channels input source
 */
void _adc_dma_set_inputs(struct _adc_dma_device *const device, const adc_pos_input_t pos_input,
                         const adc_neg_input_t neg_input, const uint8_t channel)
{
	(void)channel;

	hri_adc_write_INPUTCTRL_MUXPOS_bf(device->hw, pos_input);
	hri_adc_write_INPUTCTRL_MUXNEG_bf(device->hw, neg_input);
}

/**
 * \brief Set thresholds
 */
void _adc_sync_set_thresholds(struct _adc_sync_device *const device, const adc_threshold_t low_threshold,
                              const adc_threshold_t up_threshold)
{
	hri_adc_write_WINLT_reg(device->hw, low_threshold);
	hri_adc_write_WINUT_reg(device->hw, up_threshold);
}

/**
 * \brief Set thresholds
 */
void _adc_async_set_thresholds(struct _adc_async_device *const device, const adc_threshold_t low_threshold,
                               const adc_threshold_t up_threshold)
{
	hri_adc_write_WINLT_reg(device->hw, low_threshold);
	hri_adc_write_WINUT_reg(device->hw, up_threshold);
}

/**
 * \brief Set thresholds
 */
void _adc_dma_set_thresholds(struct _adc_dma_device *const device, const adc_threshold_t low_threshold,
                             const adc_threshold_t up_threshold)
{
	hri_adc_write_WINLT_reg(device->hw, low_threshold);
	hri_adc_write_WINUT_reg(device->hw, up_threshold);
}

/**
 * \brief Set gain
 */
void _adc_sync_set_channel_gain(struct _adc_sync_device *const device, const uint8_t channel, const adc_gain_t gain)
{
	(void)device, (void)channel, (void)gain;
}

/**
 * \brief Set gain
 */
void _adc_async_set_channel_gain(struct _adc_async_device *const device, const uint8_t channel, const adc_gain_t gain)
{
	(void)device, (void)channel, (void)gain;
}

/**
 * \brief Set gain
 */
void _adc_dma_set_channel_gain(struct _adc_dma_device *const device, const uint8_t channel, const adc_gain_t gain)
{
	(void)device, (void)channel, (void)gain;
}

/**
 * \brief Set conversion mode
 */
void _adc_sync_set_conversion_mode(struct _adc_sync_device *const device, const enum adc_conversion_mode mode)
{
	if (ADC_CONVERSION_MODE_FREERUN == mode) {
		hri_adc_set_CTRLC_FREERUN_bit(device->hw);
	} else {
		hri_adc_clear_CTRLC_FREERUN_bit(device->hw);
	}
}

/**
 * \brief Set conversion mode
 */
void _adc_async_set_conversion_mode(struct _adc_async_device *const device, const enum adc_conversion_mode mode)
{
	if (ADC_CONVERSION_MODE_FREERUN == mode) {
		hri_adc_set_CTRLC_FREERUN_bit(device->hw);
	} else {
		hri_adc_clear_CTRLC_FREERUN_bit(device->hw);
	}
}

/**
 * \brief Set conversion mode
 */
void _adc_dma_set_conversion_mode(struct _adc_dma_device *const device, const enum adc_conversion_mode mode)
{
	if (ADC_CONVERSION_MODE_FREERUN == mode) {
		hri_adc_set_CTRLC_FREERUN_bit(device->hw);
	} else {
		hri_adc_clear_CTRLC_FREERUN_bit(device->hw);
	}
}

/**
 * \brief Set differential mode
 */
void _adc_sync_set_channel_differential_mode(struct _adc_sync_device *const device, const uint8_t channel,
                                             const enum adc_differential_mode mode)
{
	(void)channel;

	if (ADC_DIFFERENTIAL_MODE_DIFFERENTIAL == mode) {
		hri_adc_set_CTRLC_DIFFMODE_bit(device->hw);
	} else {
		hri_adc_clear_CTRLC_DIFFMODE_bit(device->hw);
	}
}

/**
 * \brief Set differential mode
 */
void _adc_async_set_channel_differential_mode(struct _adc_async_device *const device, const uint8_t channel,
                                              const enum adc_differential_mode mode)
{
	(void)channel;

	if (ADC_DIFFERENTIAL_MODE_DIFFERENTIAL == mode) {
		hri_adc_set_CTRLC_DIFFMODE_bit(device->hw);
	} else {
		hri_adc_clear_CTRLC_DIFFMODE_bit(device->hw);
	}
}

/**
 * \brief Set differential mode
 */
void _adc_dma_set_channel_differential_mode(struct _adc_dma_device *const device, const uint8_t channel,
                                            const enum adc_differential_mode mode)
{
	(void)channel;

	if (ADC_DIFFERENTIAL_MODE_DIFFERENTIAL == mode) {
		hri_adc_set_CTRLC_DIFFMODE_bit(device->hw);
	} else {
		hri_adc_clear_CTRLC_DIFFMODE_bit(device->hw);
	}
}

/**
 * \brief Set window mode
 */
void _adc_sync_set_window_mode(struct _adc_sync_device *const device, const adc_window_mode_t mode)
{
	hri_adc_write_CTRLC_WINMODE_bf(device->hw, mode);
}

/**
 * \brief Set window mode
 */
void _adc_async_set_window_mode(struct _adc_async_device *const device, const adc_window_mode_t mode)
{
	hri_adc_write_CTRLC_WINMODE_bf(device->hw, mode);
}

/**
 * \brief Set window mode
 */
void _adc_dma_set_window_mode(struct _adc_dma_device *const device, const adc_window_mode_t mode)
{
	hri_adc_write_CTRLC_WINMODE_bf(device->hw, mode);
}

/**
 * \brief Retrieve threshold state
 */
void _adc_sync_get_threshold_state(const struct _adc_sync_device *const device, adc_threshold_status_t *const state)
{
	*state = hri_adc_get_interrupt_WINMON_bit(device->hw);
}

/**
 * \brief Retrieve threshold state
 */
void _adc_async_get_threshold_state(const struct _adc_async_device *const device, adc_threshold_status_t *const state)
{
	*state = hri_adc_get_interrupt_WINMON_bit(device->hw);
}

/**
 * \brief Retrieve threshold state
 */
void _adc_dma_get_threshold_state(const struct _adc_dma_device *const device, adc_threshold_status_t *const state)
{
	*state = hri_adc_get_interrupt_WINMON_bit(device->hw);
}

/**
 * \brief Enable/disable ADC channel interrupt
 */
void _adc_async_set_irq_state(struct _adc_async_device *const device, const uint8_t channel,
                              const enum _adc_async_callback_type type, const bool state)
{
	(void)channel;

	void *const hw = device->hw;

	if (ADC_ASYNC_DEVICE_MONITOR_CB == type) {
		hri_adc_write_INTEN_WINMON_bit(hw, state);
	} else if (ADC_ASYNC_DEVICE_ERROR_CB == type) {
		hri_adc_write_INTEN_OVERRUN_bit(hw, state);
	} else if (ADC_ASYNC_DEVICE_CONVERT_CB == type) {
		hri_adc_write_INTEN_RESRDY_bit(hw, state);
	}
}

/**
 * \brief Retrieve ADC sync helper functions
 */
void *_adc_get_adc_sync(void)
{
	return (void *)NULL;
}

/**
 * \brief Retrieve ADC async helper functions
 */
void *_adc_get_adc_async(void)
{
	return (void *)NULL;
}

/**
 * \brief Set ADC reference source
 *
 * \param[in] hw The pointer to hardware instance
 * \param[in] reference The reference to set
 */
static void _adc_set_reference_source(void *const hw, const adc_reference_t reference)
{
	bool enabled = hri_adc_get_CTRLA_ENABLE_bit(hw);

	hri_adc_clear_CTRLA_ENABLE_bit(hw);
	hri_adc_write_REFCTRL_REFSEL_bf(hw, reference);

	if (enabled) {
		hri_adc_set_CTRLA_ENABLE_bit(hw);
	}
}
