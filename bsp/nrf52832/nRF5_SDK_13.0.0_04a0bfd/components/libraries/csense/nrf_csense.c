/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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

#if NRF_MODULE_ENABLED(NRF_CSENSE)

#include <string.h>

#include "nrf_csense.h"
#include "nrf_peripherals.h"
#include "nrf_assert.h"

#if     defined(__CC_ARM)
#elif   defined(__ICCARM__)
#elif   defined(__GNUC__)
    #ifndef __CLZ
        #define __CLZ(x)    __builtin_clz(x)
    #endif
#endif

APP_TIMER_DEF(nrf_csense_timer);

typedef struct
{
    nrf_csense_event_handler_t  event_handler;                        //!< Event handler for module.
    nrf_drv_state_t             state;                                //!< State of module.
    uint32_t                    ticks;                                //!< Timeout ticks of app_timer instance controlling csense module.
    uint16_t                    raw_analog_values[MAX_ANALOG_INPUTS]; //!< Raw values of measurements.
    uint8_t                     enabled_analog_channels_mask;         //!< Mask of enabled channels.
} nrf_csense_t;

/* Module instance. */
static nrf_csense_t m_nrf_csense;

/* First of touch elements instances that creates linked list. */
static nrf_csense_instance_t * mp_nrf_csense_instance_head;

/* Buffer for values got from measurements. */
static uint16_t m_values_buffer[NRF_CSENSE_MAX_PADS_NUMBER];

/**
 * @brief Function for handling time-outs.
 *
 * @param[in] p_context     General purpose pointer. Will be passed to the time-out handler
 *                          when the timer expires.
 */
static void csense_timer_handler(void * p_context)
{
    if (m_nrf_csense.state != NRF_DRV_STATE_POWERED_ON)
    {
        return;
    }

    if (nrf_drv_csense_sample() == NRF_ERROR_BUSY)
    {
        return;
    }
}


/**
 * @brief Function for updating maximum or minimum value.
 *
 * @param [in] p_instance   Pointer to csense instance.
 * @param [in] p_pad        Pointer to pad which should be checked for minimum or maximum value.
 */
__STATIC_INLINE void min_or_max_update(nrf_csense_instance_t const * p_instance,
                                       nrf_csense_pad_t            * p_pad)
{
    uint16_t val = m_nrf_csense.raw_analog_values[p_pad->analog_input_number];

    if (p_instance->min_max[p_pad->pad_index].min_value > val)
    {
        p_instance->min_max[p_pad->pad_index].min_value = val;
    }

    if (p_instance->min_max[p_pad->pad_index].max_value < val)
    {
        p_instance->min_max[p_pad->pad_index].max_value = val;
    }
}


/**
 * @brief Function for calculating proportions on slider pad.
 *
 * @note This function help to self calibrate the pads.
 *
 * @param [in] p_instance   Pointer to csense instance.
 * @param [in] p_pad        Pointer to pad to calculate ratio for.
 *
 * @return Difference between maximum and minimum values read on pads or 0 if minimum is bigger than maximum.
 *
 */
__STATIC_INLINE uint16_t ratio_calculate(nrf_csense_instance_t const * p_instance,
                                        nrf_csense_pad_t            * p_pad)
{
    if (p_instance->min_max[p_pad->pad_index].max_value > p_instance->min_max[p_pad->pad_index].min_value)
    {
        uint16_t scale;
        scale = (uint16_t)(p_instance->min_max[p_pad->pad_index].max_value -
                p_instance->min_max[p_pad->pad_index].min_value);
        return scale;
    }
    else
    {
        return 0;
    }
}


/**
 * @brief Function for calculating step.
 *
 * Function calculates step for slider basing on index of touched pads and values measured on
 * them and neighboring pads.
 *
 * @param[in] p_instance    Pointer to csense instance.
 * @param[in] pad_index     Index of the pad.
 *
 * @return Detected touched step.
 */
static uint16_t calculate_step(nrf_csense_instance_t * p_instance,
                               uint8_t                 pad_index)
{
    uint16_t step = 0;
    uint32_t values_sum;
    uint32_t values_product;

    pad_index += 1;

    values_sum = m_values_buffer[pad_index] + m_values_buffer[pad_index - 1] +
                  m_values_buffer[pad_index + 1];
    values_product = (uint32_t)(p_instance->steps-1) *
                      (m_values_buffer[pad_index - 1] * (pad_index - 2)
                       + m_values_buffer[pad_index] * (pad_index - 1)
                       + m_values_buffer[pad_index + 1] * (pad_index));
    step = 1 + ROUNDED_DIV(values_product, (values_sum * (p_instance->number_of_pads - 1)));    // Add 1 to the result of the division
                                                                                                // to get the appropriate range of values.
    memset((void*)m_values_buffer, 0, sizeof(m_values_buffer));

    return step;
}


/**
 * @brief Function for finding mask of touched pads.
 *
 * @param [in] p_instance                             Pointer to csense instance.
 *
 * @return Mask of touched pads.
 */
static uint32_t find_touched_mask(nrf_csense_instance_t const * p_instance)
{
    uint32_t           touched_mask   = 0;
    uint16_t           max_value = 0;
    uint16_t           ratio;
    nrf_csense_pad_t * p_pad;

    for (p_pad = p_instance->p_nrf_csense_pad; NULL != p_pad; p_pad = p_pad->p_next_pad) // run through all pads and look for those with biggest value
    {
        min_or_max_update(p_instance, p_pad);

        ratio = ratio_calculate(p_instance, p_pad);
        if (ratio == 0)
        {
            return 0;
        }
        uint16_t val =
            (uint16_t)(((uint32_t)(m_nrf_csense.raw_analog_values[p_pad->analog_input_number] -
                        p_instance->min_max[p_pad->pad_index].min_value) *
                        NRF_CSENSE_MAX_VALUE) / ratio);
        m_values_buffer[p_pad->pad_index+1] = val;

        if (val > max_value)
        {
            max_value = val;
            touched_mask   = (1UL << (p_pad->pad_index));
        }
        else if (val == max_value)
        {
            max_value = val;
            touched_mask  |= (1UL << (p_pad->pad_index));
        }
    }

    return touched_mask;
}


/**
 * @brief Function for finding touched pad.
 *
 * If there is more than one pad connected to an analog channel this functions which one was actually touched. This is done by
 * comparing values of neighboring pads.
 *
 * @param [in] instance                             Pointer to csense instance.
 * @param [in] touched_mask                         Mask of touched pads.
 *
 * @return Touched pad.
 */
static uint16_t find_touched_pad(nrf_csense_instance_t const * p_instance,
                                 uint32_t                      touched_mask)
{
    uint8_t         i;
    uint8_t         biggest_deviation = 0;
    uint8_t         temp_biggest      = 0;
    uint16_t        pad               = UINT16_MAX;
    static uint16_t previous_pad      = 0;

    for (i = 0; i < (p_instance->number_of_pads); i++)
     {
         if ((1UL << i) & touched_mask)
         {
             temp_biggest = m_values_buffer[i];
             temp_biggest += m_values_buffer[i + 2];

             if ((i != 0) && (i != ((p_instance->number_of_pads-1))))
             {
                 temp_biggest /= 2;
             }

             if ((temp_biggest > NRF_CSENSE_PAD_DEVIATION) &&
                 (temp_biggest > biggest_deviation))
             {
                 biggest_deviation = temp_biggest;
                 pad               = i;
             }
         }
     }

    if (pad == UINT16_MAX)
    {
        pad = previous_pad;
    }
    else
    {
        previous_pad = pad;
    }

    return pad;
}


/**
 * @brief Function for finding touched step.
 *
 * @param [in] instance     Pointer to csense instance.
 *
 * @return Detected touched step.
 */
static uint16_t find_touched_step(nrf_csense_instance_t * p_instance)
{
    uint32_t touched_mask = 0;
    uint16_t pad          = 0;
    uint16_t step;

    touched_mask = find_touched_mask(p_instance);

    if (touched_mask == 0)
    {
        return UINT16_MAX;
    }

    if ((touched_mask & (-(int32_t)touched_mask)) == touched_mask) // Check if there is only one pad with greatest value.
    {
        pad = 31 - __CLZ(touched_mask);
    }
    else
    {
        pad = find_touched_pad(p_instance, touched_mask);
    }

    step = calculate_step(p_instance, pad);
    return step;
}


/**
 * @brief Event handler for csense.
 *
 * param [in] p_event_struct                            Pointer to event structure.
 */
static void csense_event_handler(nrf_drv_csense_evt_t * p_event_struct)
{
    nrf_csense_evt_t            event;
    static uint16_t             prev_analog_values[MAX_ANALOG_INPUTS];
    bool                        touched = false;
    nrf_csense_instance_t *     instance;
    uint8_t                     i;

    if ((m_nrf_csense.enabled_analog_channels_mask & (1UL << (p_event_struct->analog_channel))) == 0)
    {
        return;
    }

    m_nrf_csense.raw_analog_values[p_event_struct->analog_channel] = p_event_struct->read_value;

    if (nrf_drv_csense_is_busy())
    {
        return;
    }

    for (instance = mp_nrf_csense_instance_head; instance != NULL;
         instance = instance->p_next_instance) // run through all instances
    {
        if (instance->is_active)
        {
            event.p_instance = instance;
            nrf_csense_pad_t * p_pad = instance->p_nrf_csense_pad;

            for (i = 0; i < MAX_ANALOG_INPUTS; i++)
            {
                if ((m_nrf_csense.raw_analog_values[i] <
                    (prev_analog_values[i] - NRF_CSENSE_PAD_HYSTERESIS)) ||
                     (m_nrf_csense.raw_analog_values[i] >
                    (prev_analog_values[i] + NRF_CSENSE_PAD_HYSTERESIS)))
                {
                    touched = true;
                    break;
                }
            }

            if (touched)
            {
                touched = false;

                for (p_pad = instance->p_nrf_csense_pad; p_pad != NULL;
                     p_pad = p_pad->p_next_pad)
                {
                    if (m_nrf_csense.raw_analog_values[p_pad->analog_input_number] >
                        p_pad->threshold)
                    {
                        touched = true;
                        break;
                    }
                }
            }
            else
            {
                continue;
            }

            // Specify the event
            if ((instance->is_touched) && touched)
            {
                // dragged
                if (instance->number_of_pads > 1)
                {
                    event.params.slider.step = find_touched_step(instance);
                    event.nrf_csense_evt_type = NRF_CSENSE_SLIDER_EVT_DRAGGED;

                    m_nrf_csense.event_handler(&event);
                }
            }
            else if ((!(instance->is_touched)) && touched)
            {
                // pressed
                if (instance->number_of_pads > 1)
                {
                    event.params.slider.step = find_touched_step(instance);
                    event.nrf_csense_evt_type = NRF_CSENSE_SLIDER_EVT_PRESSED;
                }
                else
                {
                    event.nrf_csense_evt_type = NRF_CSENSE_BTN_EVT_PRESSED;
                }
                instance->is_touched = true;

                m_nrf_csense.event_handler(&event);
            }
            else if ((instance->is_touched) && (!touched))
            {
                // released
                if (instance->number_of_pads > 1)
                {
                    event.params.slider.step = find_touched_step(instance);
                    event.nrf_csense_evt_type = NRF_CSENSE_SLIDER_EVT_RELEASED;
                }
                else
                {
                    event.nrf_csense_evt_type = NRF_CSENSE_BTN_EVT_RELEASED;
                }
                instance->is_touched = false;

                m_nrf_csense.event_handler(&event);
            }
            else
            {
                // nothing changed
            }
        }

        touched = false;
    }

    memset(m_values_buffer, 0, sizeof(m_values_buffer));
    memcpy(prev_analog_values, m_nrf_csense.raw_analog_values,
           sizeof(m_nrf_csense.raw_analog_values));
}


ret_code_t nrf_csense_init(nrf_csense_event_handler_t event_handler,
                           uint32_t                   ticks)
{
    ASSERT(event_handler != NULL);
    ASSERT(m_nrf_csense.state == NRF_DRV_STATE_UNINITIALIZED);

    ret_code_t err_code;

    static const nrf_drv_csense_config_t m_csense_config =
    {
        .output_pin = NRF_CSENSE_OUTPUT_PIN
    };

    m_nrf_csense.event_handler = event_handler;
    m_nrf_csense.ticks         = ticks;
    mp_nrf_csense_instance_head = NULL;

    err_code = app_timer_create(&nrf_csense_timer, APP_TIMER_MODE_REPEATED, csense_timer_handler);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = nrf_drv_csense_init(&m_csense_config, csense_event_handler);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    m_nrf_csense.state = NRF_DRV_STATE_INITIALIZED;

    return NRF_SUCCESS;
}


ret_code_t nrf_csense_uninit(void)
{
    ASSERT(m_nrf_csense.state != NRF_DRV_STATE_UNINITIALIZED);

    ret_code_t err_code;
    nrf_csense_instance_t ** pp_instance = &mp_nrf_csense_instance_head;

    err_code = nrf_drv_csense_uninit();
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    if (m_nrf_csense.enabled_analog_channels_mask != 0)
    {
        err_code = app_timer_stop(nrf_csense_timer);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }

    while ((*pp_instance) != NULL)
    {
        nrf_csense_instance_t ** pp_instance_next = (&(*pp_instance)->p_next_instance);
        (*pp_instance) = NULL;
        pp_instance = pp_instance_next;
    }

    memset((void *)&m_nrf_csense, 0, sizeof(nrf_csense_t));

    m_nrf_csense.state = NRF_DRV_STATE_UNINITIALIZED;


    return NRF_SUCCESS;
}

ret_code_t nrf_csense_add(nrf_csense_instance_t * const p_instance)
{
    ASSERT(m_nrf_csense.state != NRF_DRV_STATE_UNINITIALIZED);
    ASSERT(p_instance->p_next_instance == NULL);
    ASSERT(p_instance != NULL);

    ret_code_t err_code;

    nrf_csense_instance_t ** pp_instance = &mp_nrf_csense_instance_head;

    while ((*pp_instance) != NULL)
    {
        ASSERT((*pp_instance) != p_instance);
        pp_instance = &((*pp_instance)->p_next_instance);
    }

    *pp_instance = p_instance;

    err_code = nrf_csense_enable(p_instance);
    return err_code;
}

ret_code_t nrf_csense_enable(nrf_csense_instance_t * const p_instance)
{
    ASSERT(m_nrf_csense.state != NRF_DRV_STATE_UNINITIALIZED);
    ASSERT(p_instance != NULL);

    ret_code_t               err_code;
    nrf_csense_pad_t const * p_pad;
    uint8_t                  analog_channels_mask = 0;

    if (m_nrf_csense.enabled_analog_channels_mask == 0)
    {
        err_code = app_timer_start(nrf_csense_timer, m_nrf_csense.ticks, NULL);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }

    p_instance->is_active = true;

    for (p_pad = p_instance->p_nrf_csense_pad; p_pad != NULL; p_pad = p_pad->p_next_pad)
    {
        p_instance->min_max[p_pad->pad_index].min_value = UINT16_MAX;

         // If channel was already enabled skip it.
        if ((m_nrf_csense.enabled_analog_channels_mask & (1UL << (p_pad->analog_input_number))) == 0)
        {
            analog_channels_mask                      |= (1UL << (p_pad->analog_input_number));
            m_nrf_csense.enabled_analog_channels_mask |= (1UL << (p_pad->analog_input_number));
        }
    }

    m_nrf_csense.state = NRF_DRV_STATE_POWERED_ON;
    nrf_drv_csense_channels_enable(analog_channels_mask);

    return NRF_SUCCESS;
}


ret_code_t nrf_csense_disable(nrf_csense_instance_t * const p_instance)
{
    ASSERT(m_nrf_csense.state == NRF_DRV_STATE_POWERED_ON);

    ret_code_t               err_code;
    nrf_csense_instance_t  * p_instance_temp = mp_nrf_csense_instance_head;
    nrf_csense_pad_t const * p_pad;
    uint8_t                  channels_mask = 0;
    uint8_t                  instance_channels_mask = 0;

    for (p_instance_temp = mp_nrf_csense_instance_head; p_instance_temp != NULL;
         p_instance_temp = p_instance_temp->p_next_instance)
    {
        for (p_pad = p_instance_temp->p_nrf_csense_pad; p_pad != NULL; p_pad = p_pad->p_next_pad)
        {
            if (p_instance_temp == p_instance)
            {
                instance_channels_mask |= (1UL << (p_pad->analog_input_number));
                p_instance->is_active   = false;
            }
            else
            {
                channels_mask |= (1UL << (p_pad->analog_input_number));
            }
        }
    }

    nrf_drv_csense_channels_disable((~channels_mask) & instance_channels_mask);

    m_nrf_csense.enabled_analog_channels_mask = channels_mask;

    if (m_nrf_csense.enabled_analog_channels_mask == 0)
    {
        err_code = app_timer_stop(nrf_csense_timer);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
        m_nrf_csense.state = NRF_DRV_STATE_INITIALIZED;
    }

    return NRF_SUCCESS;
}


ret_code_t nrf_csense_ticks_set(uint32_t ticks)
{
    ASSERT(m_nrf_csense.state != NRF_DRV_STATE_UNINITIALIZED);

    ret_code_t err_code;

    if (nrf_drv_csense_is_busy())
    {
        return NRF_ERROR_BUSY;
    }

    m_nrf_csense.ticks = ticks;

    if (m_nrf_csense.state == NRF_DRV_STATE_POWERED_ON)
    {
        err_code = app_timer_stop(nrf_csense_timer);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }

        err_code = app_timer_start(nrf_csense_timer, ticks, NULL);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }

    return NRF_SUCCESS;
}


ret_code_t nrf_csense_steps_set(nrf_csense_instance_t * const p_instance, uint16_t steps)
{
    if (p_instance->is_active)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    p_instance->steps = steps;

    return NRF_SUCCESS;
}
#endif //NRF_MODULE_ENABLED(NRF_CSENSE)
