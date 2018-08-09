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
#include "bh1745.h"

#define BH1745_SENSOR_WRITE(p_instance, msg)                                                       \
    nrf_twi_sensor_write(p_instance->p_sensor_data,                                                \
                         p_instance->sensor_addr,                                                  \
                         msg,                                                                      \
                         ARRAY_SIZE(msg),                                                          \
                         true)

ret_code_t bh1745_init(bh1745_instance_t * p_instance)
{
    ASSERT(p_instance != NULL);
    if (p_instance->p_sensor_data->p_twi_mngr->p_queue->size < BH1745_MIN_QUEUE_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    static const uint8_t msg1[] = {
        BH1745_REG_MODE_CONTROL1,
        0x00,
        0x00,
        0x00
    };
    ret_code_t err = BH1745_SENSOR_WRITE(p_instance, msg1);
    if (err != NRF_SUCCESS)
    {
        return err;
    }

    static const uint8_t msg2[] = {
        BH1745_REG_INTERRUPT,
        0x00,
        0x01,
        0xFF,
        0xFF,
        0x00,
        0x00
    };
    return BH1745_SENSOR_WRITE(p_instance, msg2);
}

ret_code_t bh1745_sw_reset(bh1745_instance_t * p_instance)
{
    ASSERT(p_instance != NULL);

    static const uint8_t send_msg[] = {
        BH1745_REG_SYSTEM_CONTROL,
        BH1745_SW_RESET_MASK
    };
    return BH1745_SENSOR_WRITE(p_instance, send_msg);
}

ret_code_t bh1745_int_reset(bh1745_instance_t * p_instance)
{
    ASSERT(p_instance != NULL);

    static const uint8_t send_msg[] = {
        BH1745_REG_SYSTEM_CONTROL,
        BH1745_INT_RESET_MASK
    };
    return BH1745_SENSOR_WRITE(p_instance, send_msg);
}

ret_code_t bh1745_meas_cfg(bh1745_instance_t * p_instance,
                           bh1745_meas_time_t  meas_time,
                           bool                enable,
                           bh1745_gain_t       gain)
{
    ASSERT(p_instance != NULL);
    if (meas_time > BH1745_MEAS_TIME_5120MS)
    {
        meas_time = BH1745_MEAS_TIME_5120MS;
    }
    if (gain > BH1745_GAIN_16X)
    {
        gain = BH1745_GAIN_16X;
    }

    uint8_t send_msg[] = {
        BH1745_REG_MODE_CONTROL1,
        0,
        0,
        0x02
    };
    NRF_TWI_SENSOR_REG_SET(send_msg[1], BH1745_MEAS_TIME_MASK, BH1745_MEAS_TIME_POS, meas_time);
    NRF_TWI_SENSOR_REG_SET(send_msg[2], BH1745_RGBC_EN_MASK,   BH1745_RGBC_EN_POS,   enable);
    NRF_TWI_SENSOR_REG_SET(send_msg[2], BH1745_ADC_GAIN_MASK,  BH1745_ADC_GAIN_POS,  gain);

    return BH1745_SENSOR_WRITE(p_instance, send_msg);
}

ret_code_t bh1745_data_read(bh1745_instance_t *      p_instance,
                            bh1745_data_callback_t   user_callback,
                            bh1745_data_t *          p_data)
{
    ASSERT(p_instance != NULL);
    ASSERT(p_data != NULL);
    ret_code_t err_code;
    err_code = nrf_twi_sensor_reg_read(p_instance->p_sensor_data,
                                       p_instance->sensor_addr,
                                       BH1745_REG_MODE_CONTROL2,
                                       NULL,
                                       &p_data->valid,
                                       1);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    err_code = nrf_twi_sensor_reg_read(p_instance->p_sensor_data,
                                       p_instance->sensor_addr,
                                       BH1745_REG_RED_DATA_LSB,
                                       (nrf_twi_sensor_reg_cb_t) user_callback,
                                       (uint8_t *) &p_data->red,
                                       BH1745_DATA_REG_NUM);
    return err_code;
}

ret_code_t bh1745_int_cfg(bh1745_instance_t *  p_instance,
                          bool                 latch,
                          bh1745_int_source_t  source,
                          bool                 enable,
                          bh1745_persistence_t persistance)
{
    ASSERT(p_instance != NULL);

    uint8_t int_reg = 0;
    NRF_TWI_SENSOR_REG_SET(int_reg, BH1745_INT_ENABLE_MASK, BH1745_INT_ENABLE_POS, enable);
    NRF_TWI_SENSOR_REG_SET(int_reg, BH1745_INT_SOURCE_MASK, BH1745_INT_SOURCE_POS, source);
    NRF_TWI_SENSOR_REG_SET(int_reg, BH1745_INT_LATCH_MASK,  BH1745_INT_LATCH_POS,  latch);

    uint8_t send_msg[] = {
        BH1745_REG_INTERRUPT,
        int_reg,
        persistance
    };

    return BH1745_SENSOR_WRITE(p_instance, send_msg);
}

ret_code_t bh1745_high_thr_set(bh1745_instance_t * p_instance,
                               uint16_t            threshold)
{
    ASSERT(p_instance != NULL);
    uint8_t send_msg[] = {
        BH1745_REG_TH_LSB,
        LSB_16(threshold),
        MSB_16(threshold)
    };

    return BH1745_SENSOR_WRITE(p_instance, send_msg);
}

ret_code_t bh1745_low_thr_set(bh1745_instance_t * p_instance,
                              uint16_t            threshold)
{
    ASSERT(p_instance != NULL);
    uint8_t send_msg[] = {
        BH1745_REG_TL_LSB,
        LSB_16(threshold),
        MSB_16(threshold)
    };

    return BH1745_SENSOR_WRITE(p_instance, send_msg);
}
