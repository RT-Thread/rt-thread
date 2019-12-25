/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_DRV_CSENSE)
#include "nrf_drv_csense.h"
#include "nrf_peripherals.h"
#include "nrf_gpio.h"
#include "app_error.h"
#include "app_util_platform.h"
#include "nrf_assert.h"
#include "string.h"
#include <stdio.h>

#if defined(__CORTEX_M) && (__CORTEX_M < 4)
#ifndef ARM_MATH_CM0PLUS
#define ARM_MATH_CM0PLUS
#endif
/*lint -save -e689 */
#include "arm_math.h"
/*lint -restore */
#endif

#if USE_COMP
#include "nrf_drv_comp.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#endif //USE_COMP

#if USE_COMP == 0
#ifdef ADC_PRESENT
#include "nrfx_adc.h"

/**
 * @defgroup adc_defines ADC defines to count input voltage.
 * @{
 */
#define ADC_RES_10BIT           1024
#define ADC_INPUT_PRESCALER     3
#define ADC_REF_VBG_VOLTAGE     1.2
/* @} */

/* ADC channel used to call conversion. */
static nrfx_adc_channel_t adc_channel = NRFX_ADC_DEFAULT_CHANNEL(NRF_ADC_CONFIG_INPUT_0);
#elif defined(SAADC_PRESENT)
#include "nrf_drv_saadc.h"

/**
 * @defgroup saadc_defines SAADC defines to count input voltage.
 * @{
 */
#define SAADC_RES_10BIT           1024
#define SAADC_INPUT_PRESCALER     3
#define SAADC_REF_VBG_VOLTAGE     0.6
/* @} */

/* SAADC channel used to call conversion. */
static nrf_saadc_channel_config_t saadc_channel = NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN0);
#endif //ADC_PRESENT
#endif //USE_COMP

#if USE_COMP
/* Number of channels required by PPI. */
#define PPI_REQUIRED_CHANNELS 3

/* Array of PPI channels. */
static nrf_ppi_channel_t m_ppi_channels[PPI_REQUIRED_CHANNELS];


/**
 * @defgroup timer_instances Timer instances.
 * @{
 */
static const nrf_drv_timer_t m_timer0 = NRF_DRV_TIMER_INSTANCE(TIMER0_FOR_CSENSE);
static const nrf_drv_timer_t m_timer1 = NRF_DRV_TIMER_INSTANCE(TIMER1_FOR_CSENSE);
/* @} */
#endif //USE_COMP

/* Configuration of the capacitive sensor module. */
typedef struct
{
    volatile nrfx_drv_state_t       module_state;                       /**< State of the module. */
    nrf_drv_csense_event_handler_t  event_handler;                      /**< Event handler for capacitor sensor events. */
    uint16_t                        analog_values[MAX_ANALOG_INPUTS];   /**< Array containing analog values measured on the corresponding COMP/ADC channel. */
    volatile bool                   busy;                               /**< Indicates state of module - busy if there are ongoing conversions. */
    volatile uint8_t                cur_chann_idx;                      /**< Current channel to be read if enabled. */
    volatile uint8_t                adc_channels_input_mask;            /**< Enabled channels. */
    uint8_t                         output_pin;                         /**< Pin to generate signal charging capacitors. */
    uint8_t                         channels_to_read;                   /**< Mask of channels remaining to be read in the current measurement. */
    volatile bool                   timers_powered_on;                  /**< Flag to indicate if timers were already started. */
}csense_t;

static csense_t m_csense;

/**
 * @brief Function for determining the next analog channel to be read.
 */
__STATIC_INLINE void calculate_next_channel(void)
{
    m_csense.cur_chann_idx = 31 - __CLZ(m_csense.channels_to_read);
}

/**
 * @brief Function for handling conversion values.
 *
 * @param[in] val                Value received from ADC or COMP.
 */
static void conversion_handler(uint16_t val)
{
    nrf_drv_csense_evt_t event_struct;

#if USE_COMP == 0
    nrf_gpio_pin_set(m_csense.output_pin);
#endif //USE_COMP

    m_csense.analog_values[m_csense.cur_chann_idx] = val;

    event_struct.read_value = val;
    event_struct.analog_channel = m_csense.cur_chann_idx;

    m_csense.channels_to_read &= ~(1UL<<m_csense.cur_chann_idx);

    // decide if there will be more conversions
    if (m_csense.channels_to_read == 0)
    {
        m_csense.busy = false;
#if USE_COMP == 0 && defined(SAADC_PRESENT)
        nrf_saadc_disable();
#endif
    }

    m_csense.event_handler(&event_struct);

    if (m_csense.channels_to_read > 0)     // Start new conversion.
    {
        ret_code_t err_code;
        calculate_next_channel();
        err_code = nrf_drv_csense_sample();
        if (err_code != NRF_SUCCESS)
        {
            return;
        }
    }
}

#if USE_COMP
/**
 * @brief Timer0 interrupt handler.
 *
 * @param[in] event_type Timer event.
 * @param[in] p_context  General purpose parameter set during initialization of
 *                       the timer. This parameter can be used to pass
 *                       additional information to the handler function, for
 *                       example, the timer ID.
 */
static void counter_compare_handler(nrf_timer_event_t event_type, void* p_context)
{
    if (event_type == NRF_TIMER_EVENT_COMPARE0)
    {
        uint16_t val =  nrf_drv_timer_capture_get(&m_timer1, NRF_TIMER_CC_CHANNEL1);
        nrf_drv_timer_pause(&m_timer1);
        nrf_drv_timer_clear(&m_timer1);

        /* Handle finished measurement. */
        conversion_handler(val);
    }
}

/**
 * @brief Dummy handler.
 *
 * @param[in] event_type Timer event.
 * @param[in] p_context  General purpose parameter set during initialization of
 *                       the timer. This parameter can be used to pass
 *                       additional information to the handler function, for
 *                       example, the timer ID.
 */
static void dummy_handler(nrf_timer_event_t event_type, void* p_context){}

/**
 * @brief Function for initializing timers.
 *
 * @retval NRF_ERROR_INTERNAL            If there were error initializing timers.
 * @retval NRF_SUCCESS                   If timers were initialized successfully.
 */
static ret_code_t timer_init(void)
{
    ret_code_t err_code;

    //set first timer in timer mode to get period of relaxation oscillator
    nrf_drv_timer_config_t timer_config = NRF_DRV_TIMER_DEFAULT_CONFIG;
    timer_config.mode = NRF_TIMER_MODE_TIMER;
    err_code = nrf_drv_timer_init(&m_timer1, &timer_config, dummy_handler);
    if (err_code != NRF_SUCCESS)
    {
        return NRF_ERROR_INTERNAL;
    }

    //set second timer in counter mode and generate event on tenth period
    timer_config.mode = NRF_TIMER_MODE_COUNTER;
    err_code = nrf_drv_timer_init(&m_timer0, &timer_config, counter_compare_handler);
    if (err_code != NRF_SUCCESS)
    {
        return NRF_ERROR_INTERNAL;
    }
    nrf_drv_timer_extended_compare(&m_timer0, NRF_TIMER_CC_CHANNEL0, MEASUREMENT_PERIOD, (nrf_timer_short_mask_t)(NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK | NRF_TIMER_SHORT_COMPARE0_STOP_MASK), true);

    return NRF_SUCCESS;
}

/**
 * @brief Function for initializing and enabling PPI channels.
 *
 * @retval NRF_ERROR_INTERNAL            If there were error initializing or enabling PPI channels.
 * @retval NRF_SUCCESS                   If PPI channels were initialized and enabled successfully.
 */
static ret_code_t ppi_init(void)
{
    ret_code_t err_code;
    uint8_t i;

    err_code = nrf_drv_ppi_init();
    if ((err_code != NRF_SUCCESS) && (err_code != NRF_ERROR_MODULE_ALREADY_INITIALIZED))
    {
        return NRF_ERROR_INTERNAL;
    }

    for (i = 0; i < PPI_REQUIRED_CHANNELS ; i++)
    {
        err_code = nrf_drv_ppi_channel_alloc(&m_ppi_channels[i]);
        if (NRF_SUCCESS != err_code)
        {
            return NRF_ERROR_INTERNAL;
        }
    }

    err_code = nrf_drv_ppi_channel_assign(m_ppi_channels[0], nrf_drv_comp_event_address_get(NRF_COMP_EVENT_CROSS), nrf_drv_timer_task_address_get(&m_timer0, NRF_TIMER_TASK_COUNT));
    if (NRF_SUCCESS != err_code)
    {
       return NRF_ERROR_INTERNAL;
    }
    err_code = nrf_drv_ppi_channel_assign(m_ppi_channels[1], nrf_drv_timer_event_address_get(&m_timer0, NRF_TIMER_EVENT_COMPARE0), nrf_drv_timer_task_address_get(&m_timer1, NRF_TIMER_TASK_CAPTURE1));
    if (NRF_SUCCESS != err_code)
    {
       return NRF_ERROR_INTERNAL;
    }
    err_code = nrf_drv_ppi_channel_fork_assign(m_ppi_channels[1], nrf_drv_comp_task_address_get(NRF_COMP_TASK_STOP));
    if (NRF_SUCCESS != err_code)
    {
       return NRF_ERROR_INTERNAL;
    }
    err_code = nrf_drv_ppi_channel_assign(m_ppi_channels[2], nrf_drv_comp_event_address_get(NRF_COMP_EVENT_READY), nrf_drv_timer_task_address_get(&m_timer0, NRF_TIMER_TASK_CLEAR));
    if (NRF_SUCCESS != err_code)
    {
       return NRF_ERROR_INTERNAL;
    }
    err_code = nrf_drv_ppi_channel_fork_assign(m_ppi_channels[2], nrf_drv_timer_task_address_get(&m_timer1, NRF_TIMER_TASK_CLEAR));
    if (NRF_SUCCESS != err_code)
    {
       return NRF_ERROR_INTERNAL;
    }

    for (i = 0; i < PPI_REQUIRED_CHANNELS ; i++)
    {
        err_code = nrf_drv_ppi_channel_enable(m_ppi_channels[i]);
        if (NRF_SUCCESS != err_code)
        {
            return NRF_ERROR_INTERNAL;
        }
    }

    return NRF_SUCCESS;
}

/**
 * @brief Dummy handler for COMP events.
 *
 * @param[in] event         COMP event.
 */
static void comp_event_handler(nrf_comp_event_t event){}

/**
 * @brief Function for initializing COMP module in relaxation oscillator mode.
 *
 * @note The frequency of the oscillator depends on threshold voltages, current source and capacitance of pad and can be calculated as f_OSC = I_SOURCE / (2CÂ·(VUP-VDOWN) ).
 *
 * @retval NRF_ERROR_INTERNAL                If there were error while initializing COMP driver.
 * @retval NRF_SUCCESS                       If the COMP driver initialization was successful.
 */
static ret_code_t comp_init(void)
{
    ret_code_t err_code;
    nrf_drv_comp_config_t m_comp_config = NRF_DRV_COMP_DEFAULT_CONFIG(NRF_COMP_INPUT_0);

    /* Workaround for Errata 12 "COMP: Reference ladder is not correctly calibrated" found at the Errata document
       for your device located at https://infocenter.nordicsemi.com/ */
    *(volatile uint32_t *)0x40013540 = (*(volatile uint32_t *)0x10000324 & 0x00001F00) >> 8;

    m_comp_config.isource = NRF_COMP_ISOURCE_Ien10uA;

    err_code = nrf_drv_comp_init(&m_comp_config, comp_event_handler);
    if (err_code != NRF_SUCCESS)
    {
        return NRF_ERROR_INTERNAL;
    }

    return NRF_SUCCESS;
}
#endif //USE_COMP

#if USE_COMP == 0
#ifdef ADC_PRESENT
/**
 * @brief ADC handler.
 *
 * @param[in] p_event                Pointer to analog-to-digital converter driver event.
 */
void adc_handler(nrfx_adc_evt_t const * p_event)
{
    nrf_gpio_pin_set(m_csense.output_pin);
    uint16_t val;
    val = (uint16_t)(p_event->data.sample.sample *
                     ADC_REF_VBG_VOLTAGE * 1000 *
                     ADC_INPUT_PRESCALER / ADC_RES_10BIT);
    conversion_handler(val);
}

/**
 * @brief Function for initializing ADC.
 */
static ret_code_t adc_init(void)
{
    ret_code_t err_code;

    adc_channel.config.config.input = NRF_ADC_CONFIG_SCALING_INPUT_ONE_THIRD;

    nrfx_adc_config_t const adc_config = NRFX_ADC_DEFAULT_CONFIG;
    err_code = nrfx_adc_init(&adc_config, adc_handler);
    if (err_code != NRF_SUCCESS)
    {
        return NRF_ERROR_INTERNAL;
    }

    nrf_gpio_pin_set(m_csense.output_pin);

    return NRF_SUCCESS;
}
#elif defined(SAADC_PRESENT)
/**
 * @brief SAADC handler.
 *
 * @param[in] p_event                Pointer to analog-to-digital converter driver event.
 */
void saadc_handler(nrf_drv_saadc_evt_t const * p_event)
{
    nrf_gpio_pin_set(m_csense.output_pin);
    uint16_t val;
    (void)nrf_drv_saadc_buffer_convert(p_event->data.done.p_buffer, 1);
    val = (uint16_t)(*p_event->data.done.p_buffer *
                      SAADC_REF_VBG_VOLTAGE * 1000 *
                      SAADC_INPUT_PRESCALER / SAADC_RES_10BIT);
    conversion_handler(val);
}

/**
 * @brief Function for initializing SAADC.
 */
static ret_code_t saadc_init(void)
{
    ret_code_t err_code;
    static nrf_saadc_value_t saadc_value;

    saadc_channel.gain = NRF_SAADC_GAIN1_3;

   err_code = nrf_drv_saadc_init(NULL, saadc_handler);
   if (err_code != NRF_SUCCESS)
   {
       return NRF_ERROR_INTERNAL;
   }

    nrf_gpio_pin_set(m_csense.output_pin);

    err_code = nrf_drv_saadc_channel_init(0, &saadc_channel);
    if (err_code != NRF_SUCCESS)
    {
        return NRF_ERROR_INTERNAL;
    }

    err_code = nrf_drv_saadc_buffer_convert(&saadc_value, 1);
    if (err_code != NRF_SUCCESS)
    {
        return NRF_ERROR_INTERNAL;
    }

    nrf_saadc_disable();

    return NRF_SUCCESS;
}
#endif //ADC_PRESENT
#endif //USE_COMP

ret_code_t nrf_drv_csense_init(nrf_drv_csense_config_t const * p_config, nrf_drv_csense_event_handler_t event_handler)
{
    ASSERT(m_csense.module_state == NRFX_DRV_STATE_UNINITIALIZED);
    ASSERT(p_config->output_pin <= NUMBER_OF_PINS);

    ret_code_t err_code;

    if (p_config == NULL)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    if (event_handler == NULL)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    m_csense.busy = false;

#if USE_COMP == 0
    m_csense.output_pin = p_config->output_pin;
    nrf_gpio_cfg_output(m_csense.output_pin);
    nrf_gpio_pin_set(m_csense.output_pin);
#endif //COMP_PRESENT

    m_csense.event_handler = event_handler;

#if USE_COMP
    err_code = comp_init();
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    err_code = timer_init();
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    err_code = ppi_init();
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
#else
#ifdef ADC_PRESENT
    err_code = adc_init();
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
#elif defined(SAADC_PRESENT)
    err_code = saadc_init();
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
#endif //ADC_PRESENT
#endif //USE_COMP

    m_csense.module_state = NRFX_DRV_STATE_INITIALIZED;

    return NRF_SUCCESS;
}

ret_code_t nrf_drv_csense_uninit(void)
{
    ASSERT(m_csense.module_state != NRFX_DRV_STATE_UNINITIALIZED);

    nrf_drv_csense_channels_disable(0xFF);

#if USE_COMP
    ret_code_t err_code;
    uint8_t i;

    nrf_drv_timer_uninit(&m_timer0);
    nrf_drv_timer_uninit(&m_timer1);
    nrf_drv_comp_uninit();
    for (i =0; i < 3; i++)
    {
        err_code = nrf_drv_ppi_channel_free(m_ppi_channels[i]);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }
    err_code = nrf_drv_ppi_uninit();
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
#else
#ifdef ADC_PRESENT
    nrfx_adc_uninit();
#elif defined(SAADC_PRESENT)
    nrf_drv_saadc_uninit();
#endif //ADC_PRESENT
#endif //USE_COMP

    m_csense.module_state = NRFX_DRV_STATE_UNINITIALIZED;

    memset((void*)&m_csense, 0, sizeof(m_csense));

    return NRF_SUCCESS;
}

void nrf_drv_csense_channels_enable(uint8_t channels_mask)
{
    ASSERT(m_csense.module_state != NRFX_DRV_STATE_UNINITIALIZED);

    m_csense.busy = true;

    m_csense.module_state = NRFX_DRV_STATE_POWERED_ON;

    m_csense.adc_channels_input_mask |= channels_mask;

    m_csense.busy = false;
}

void nrf_drv_csense_channels_disable(uint8_t channels_mask)
{
    ASSERT(m_csense.module_state == NRFX_DRV_STATE_POWERED_ON);

    m_csense.adc_channels_input_mask &= ~channels_mask;

    if (m_csense.adc_channels_input_mask == 0)
    {
        m_csense.module_state = NRFX_DRV_STATE_INITIALIZED;
    }
}

uint16_t nrf_drv_csense_channel_read(uint8_t csense_channel)
{
    return m_csense.analog_values[csense_channel];
}

ret_code_t nrf_drv_csense_sample(void)
{
    ASSERT(m_csense.module_state == NRFX_DRV_STATE_POWERED_ON);

    if (m_csense.adc_channels_input_mask != 0)
    {
        if (m_csense.channels_to_read == 0)
        {
#if USE_COMP == 0 && defined(SAADC_PRESENT)
            nrf_saadc_enable();
#endif
            if (nrf_drv_csense_is_busy() == true)
            {
                return NRF_ERROR_BUSY;
            }
            m_csense.busy = true;
            m_csense.channels_to_read = m_csense.adc_channels_input_mask;
            calculate_next_channel();
        }

#if USE_COMP
        if (!m_csense.timers_powered_on)
        {
            nrf_drv_timer_enable(&m_timer0);
            nrf_drv_timer_enable(&m_timer1);
            m_csense.timers_powered_on = true;
        }
        else
        {
            nrf_drv_timer_resume(&m_timer0);
            nrf_drv_timer_resume(&m_timer1);
        }
        nrf_drv_comp_pin_select((nrf_comp_input_t)m_csense.cur_chann_idx);
        nrf_drv_comp_start(0, 0);
#else
        ret_code_t err_code;
#ifdef ADC_PRESENT
        adc_channel.config.config.ain = (nrf_adc_config_input_t)(1<<m_csense.cur_chann_idx);
        nrf_gpio_pin_clear(m_csense.output_pin);
        err_code = nrfx_adc_sample_convert(&adc_channel, NULL);
#elif defined(SAADC_PRESENT)
        saadc_channel.pin_p = (nrf_saadc_input_t)(m_csense.cur_chann_idx + 1);
        nrf_saadc_channel_input_set(0, saadc_channel.pin_p, NRF_SAADC_INPUT_DISABLED);
        nrf_gpio_pin_clear(m_csense.output_pin);
        err_code = nrf_drv_saadc_sample();
#endif //ADC_PRESENT
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
#endif //USE_COMP
    }

    return NRF_SUCCESS;
}

bool nrf_drv_csense_is_busy(void)
{
    return m_csense.busy;
}
#endif //NRF_MODULE_ENABLED(NRF_DRV_CSENSE)
