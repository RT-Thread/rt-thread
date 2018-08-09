/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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
#include "ccs811.h"

#define SWAP_16(arg) ((arg) = (MSB_16(arg) | (LSB_16(arg) << 8)))

ret_code_t ccs811_init(ccs811_instance_t const * p_instance)
{
    ASSERT(p_instance != NULL);
    if (p_instance->p_sensor_data->p_twi_mngr->p_queue->size < CCS811_MIN_QUEUE_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    static uint8_t const send_msg[] = {
        CCS811_REG_APP_START
    };
    ret_code_t err = nrf_twi_sensor_write(p_instance->p_sensor_data,
                                          p_instance->sensor_addr,
                                          send_msg,
                                          ARRAY_SIZE(send_msg),
                                          true);
    err = ccs811_drive_mode_set(p_instance, CCS811_MODE_0, false, false);
    if (err != NRF_SUCCESS)
    {
        return err;
    }
    err = ccs811_env_set(p_instance, CCS811_DEFAULT_TEMPERATURE, 0, CCS811_DEFAULT_HUMIDITY, 0);
    if (err != NRF_SUCCESS)
    {
        return err;
    }
    return ccs811_thr_cfg(p_instance,
                          CCS811_DEFAULT_LOW_THR,
                          CCS811_DEFAULT_HIGH_THR,
                          CCS811_DEFAULT_HYSTERESIS);
}

ret_code_t ccs811_drive_mode_set(ccs811_instance_t const * p_instance,
                                 ccs811_drive_mode_t       mode,
                                 bool                      drdy_en,
                                 bool                      thr_en)
{
    ASSERT(p_instance != NULL);
    uint8_t reg = 0;
    NRF_TWI_SENSOR_REG_SET(reg, CCS811_DRIVE_MODE_MASK, CCS811_DRIVE_MODE_POS, mode);
    NRF_TWI_SENSOR_REG_SET(reg, CCS811_DATA_READY_MASK, CCS811_DATA_READY_POS, drdy_en);
    NRF_TWI_SENSOR_REG_SET(reg, CCS811_THRESH_MASK,     CCS811_THRESH_POS,     thr_en);

    uint8_t send_msg[] = {
        CCS811_REG_MEAS_MODE,
        reg
    };

    return nrf_twi_sensor_write(p_instance->p_sensor_data,
                                p_instance->sensor_addr,
                                send_msg,
                                ARRAY_SIZE(send_msg),
                                true);
}

ret_code_t ccs811_alg_data_read(ccs811_instance_t const * p_instance,
                                ccs811_data_callback_t    user_cb,
                                ccs811_alg_data_t *       p_alg_data,
                                ccs811_last_data_byte_t   last)
{
    ASSERT(p_instance != NULL);
    ASSERT(p_alg_data != NULL);

    return nrf_twi_sensor_reg_read(p_instance->p_sensor_data,
                                   p_instance->sensor_addr,
                                   CCS811_REG_ALG_RESULT_DATA,
                                   (nrf_twi_sensor_reg_cb_t) user_cb,
                                   (uint8_t *) p_alg_data,
                                   last);
}

void ccs811_alg_data_process(ccs811_alg_data_t * p_alg_data)
{
    ASSERT(p_alg_data != NULL);

    SWAP_16(p_alg_data->eco2);
    SWAP_16(p_alg_data->tvoc);
    SWAP_16(p_alg_data->raw);
}

ret_code_t ccs811_env_set(ccs811_instance_t const * p_instance,
                          int8_t                    temp_value,
                          uint16_t                  temp_fraction,
                          uint8_t                   hum_percent,
                          uint16_t                  hum_fraction)
{
    ASSERT(p_instance != NULL);
    temp_value += CCS811_TEMPERATURE_OFFSET;
    if(temp_value < 0)
    {
        temp_value = 0;
    }
    uint16_t env_temp = ( *((uint16_t *) &temp_value) << CCS811_ENV_TEMP_VALUE_POS)
                        | (temp_fraction & CCS811_ENV_TEMP_FRACTION_MASK);
    uint16_t env_hum  = ( *((uint16_t *) &hum_percent)  << CCS811_ENV_HUM_PERCENT_POS)
                        | (hum_fraction  & CCS811_ENV_HUM_FRACTION_MASK);

    uint8_t send_msg[] = {
        CCS811_REG_ENV_DATA,
        MSB_16(env_temp),
        LSB_16(env_temp),
        MSB_16(env_hum),
        LSB_16(env_hum)
    };

    return nrf_twi_sensor_write(p_instance->p_sensor_data,
                                p_instance->sensor_addr,
                                send_msg,
                                ARRAY_SIZE(send_msg),
                                true);
}

ret_code_t ccs811_thr_cfg(ccs811_instance_t const * p_instance,
                          uint16_t                  l_to_m,
                          uint16_t                  m_to_h,
                          uint8_t                   hysteresis)
{
    ASSERT(p_instance != NULL);
    uint8_t send_msg[] = {
        CCS811_REG_THRESHOLDS,
        MSB_16(l_to_m),
        LSB_16(l_to_m),
        MSB_16(m_to_h),
        LSB_16(m_to_h),
        hysteresis
    };

    return nrf_twi_sensor_write(p_instance->p_sensor_data,
                                p_instance->sensor_addr,
                                send_msg,
                                ARRAY_SIZE(send_msg),
                                true);
}

ret_code_t ccs811_baseline_read(ccs811_instance_t const * p_instance,
                                nrf_twi_sensor_reg_cb_t   user_cb,
                                uint16_t *                p_baseline)
{
    ASSERT(p_instance != NULL);
    ASSERT(p_baseline != NULL);
    return nrf_twi_sensor_reg_read(p_instance->p_sensor_data,
                                   p_instance->sensor_addr,
                                   CCS811_REG_BASELINE,
                                   user_cb,
                                   (uint8_t *) p_baseline,
                                   2);
}

ret_code_t ccs811_baseline_set(ccs811_instance_t const * p_instance, uint16_t baseline)
{
    ASSERT(p_instance != NULL);
    uint8_t * p_base = (uint8_t *) &baseline;
    uint8_t send_msg[] = {
        CCS811_REG_BASELINE,
        p_base[0],
        p_base[1]
    };

    return nrf_twi_sensor_write(p_instance->p_sensor_data,
                                p_instance->sensor_addr,
                                send_msg,
                                ARRAY_SIZE(send_msg),
                                true);
}

ret_code_t ccs811_sw_reset(ccs811_instance_t const * p_instance)
{
    ASSERT(p_instance != NULL);
    static uint8_t const send_msg[] = {
        CCS811_REG_SW_RESET,
        CCS811_SW_RESET_BYTE0,
        CCS811_SW_RESET_BYTE1,
        CCS811_SW_RESET_BYTE2,
        CCS811_SW_RESET_BYTE3
    };

    return nrf_twi_sensor_write(p_instance->p_sensor_data,
                                p_instance->sensor_addr,
                                send_msg,
                                ARRAY_SIZE(send_msg),
                                true);
}

