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
#include "hts221.h"
#include <string.h>

#define HTS221_WRITE(p_instance, msg)                   \
    nrf_twi_sensor_write(p_instance->p_sensor_data,     \
                         p_instance->sensor_addr,       \
                         msg,                           \
                         ARRAY_SIZE(msg),               \
                         true)

static void hts221_init_cb(ret_code_t result, void * p_register_data)
{
    hts221_calib_t * calib_info = (hts221_calib_t *) p_register_data;
    uint8_t calib_raw[HTS221_REG_CALIBRATION_NUM];
    memcpy(calib_raw, calib_info, HTS221_REG_CALIBRATION_NUM);

    calib_info->H0_rH_x2   = calib_raw[0];
    calib_info->H1_rH_x2   = calib_raw[1];
    calib_info->T0_degC_x8 = (uint16_t)calib_raw[2]
                             + ((uint16_t)(calib_raw[5] & 0x03) << 8);
    calib_info->T1_degC_x8 = (uint16_t)calib_raw[3]
                             + ((uint16_t)((calib_raw[5] >> 2) & 0x03) << 8);
    calib_info->H0_T0_OUT  = (int16_t)calib_raw[6]  + ((int16_t)calib_raw[7]  << 8);
    calib_info->H1_T0_OUT  = (int16_t)calib_raw[10] + ((int16_t)calib_raw[11] << 8);
    calib_info->T0_OUT     = (int16_t)calib_raw[12] + ((int16_t)calib_raw[13] << 8);
    calib_info->T1_OUT     = (int16_t)calib_raw[14] + ((int16_t)calib_raw[15] << 8);

}

ret_code_t hts221_init(hts221_instance_t * p_instance)
{
    ASSERT(p_instance != NULL);
    if (p_instance->p_sensor_data->p_twi_mngr->p_queue->size < HTS221_MIN_QUEUE_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    p_instance->ctrl_reg1 = 0;
    uint8_t send_msg[] = {
        HTS221_REG_AV_CONF,
        HTS221_DEF_AV_CONF,
        0,
        0,
        0
    };

    ret_code_t err = HTS221_WRITE(p_instance, send_msg);
    if (err != NRF_SUCCESS)
    {
        return err;
    }

    return nrf_twi_sensor_reg_read(p_instance->p_sensor_data,
                                   p_instance->sensor_addr,
                                   HTS221_REG_CALIBRATION | HTS221_INCR_REG_MASK,
                                   hts221_init_cb,
                                   (uint8_t *) &p_instance->calib_info,
                                   HTS221_REG_CALIBRATION_NUM);
}

ret_code_t hts221_avg_cfg(hts221_instance_t *       p_instance,
                          hts221_temp_avg_samples_t temp_avg,
                          hts221_hum_avg_samples_t  hum_avg)
{
    ASSERT(p_instance != NULL);
    uint8_t reg_val = 0;
    NRF_TWI_SENSOR_REG_SET(reg_val, HTS221_AVGT_MASK, HTS221_AVGT_POS, temp_avg);
    NRF_TWI_SENSOR_REG_SET(reg_val, HTS221_AVGH_MASK, HTS221_AVGH_POS, hum_avg);

    uint8_t send_msg[] = {
        HTS221_REG_AV_CONF,
        reg_val
    };

    return HTS221_WRITE(p_instance, send_msg);
}

ret_code_t hts221_data_rate_cfg(hts221_instance_t * p_instance, hts221_odr_t odr)
{
    ASSERT(p_instance != NULL);
    NRF_TWI_SENSOR_REG_SET(p_instance->ctrl_reg1, HTS221_ODR_MASK, HTS221_ODR_POS, odr);

    uint8_t send_msg[] = {
        HTS221_REG_CTRL_REG1,
        p_instance->ctrl_reg1
    };

    return HTS221_WRITE(p_instance, send_msg);
}

ret_code_t hts221_pd_enable(hts221_instance_t * p_instance, bool enable)
{
    ASSERT(p_instance != NULL);
    NRF_TWI_SENSOR_REG_SET(p_instance->ctrl_reg1, HTS221_PD_MASK, HTS221_PD_POS, enable);
    uint8_t send_msg[] = {
       HTS221_REG_CTRL_REG1,
       p_instance->ctrl_reg1
    };

    return HTS221_WRITE(p_instance, send_msg);
}



ret_code_t hts221_boot(hts221_instance_t * p_instance)
{
    ASSERT(p_instance != NULL);
    uint8_t reg_val = p_instance->ctrl_reg2;
    NRF_TWI_SENSOR_REG_SET(reg_val, HTS221_BOOT_MASK, HTS221_BOOT_POS, 1);
    uint8_t send_msg[] = {
        HTS221_REG_CTRL_REG2,
        reg_val
    };

    return HTS221_WRITE(p_instance, send_msg);
}

ret_code_t hts221_heater_enable(hts221_instance_t * p_instance, bool enable)
{
    ASSERT(p_instance != NULL);
    NRF_TWI_SENSOR_REG_SET(p_instance->ctrl_reg2, HTS221_HEATER_MASK, HTS221_HEATER_POS, enable);

    uint8_t send_msg[] = {
       HTS221_REG_CTRL_REG2,
       p_instance->ctrl_reg2
    };

    return HTS221_WRITE(p_instance, send_msg);
}

ret_code_t hts221_oneshot(hts221_instance_t * p_instance)
{
    ASSERT(p_instance != NULL);
    uint8_t reg_val = p_instance->ctrl_reg2;
    NRF_TWI_SENSOR_REG_SET(reg_val, HTS221_ONE_SHOT_MASK, HTS221_ONE_SHOT_POS, true);
    uint8_t send_msg[] = {
        HTS221_REG_CTRL_REG2,
        reg_val
    };

    return HTS221_WRITE(p_instance, send_msg);
}

ret_code_t hts221_drdy_pin_cfg(hts221_instance_t * p_instance,
                               bool                active_low,
                               bool                operation,
                               bool                drdy_enable)
{
    ASSERT(p_instance != NULL);
    uint8_t reg_val = 0;
    NRF_TWI_SENSOR_REG_SET(reg_val, HTS221_DRDY_H_L_MASK, HTS221_DRDY_H_L_POS, active_low);
    NRF_TWI_SENSOR_REG_SET(reg_val, HTS221_PP_OD_MASK, HTS221_PP_OD_POS, operation);
    NRF_TWI_SENSOR_REG_SET(reg_val, HTS221_DRDY_EN_MASK, HTS221_DRDY_EN_POS, drdy_enable);

    uint8_t send_msg[] = {
        HTS221_REG_CTRL_REG3,
        reg_val
    };

    return HTS221_WRITE(p_instance, send_msg);
}

ret_code_t hts221_temp_read(hts221_instance_t *       p_instance,
                            hts221_data_callback_t    user_callback,
                            int16_t *                 p_temp)
{
    ASSERT(p_instance != NULL);
    return nrf_twi_sensor_reg_read(p_instance->p_sensor_data,
                                   p_instance->sensor_addr,
                                   HTS221_REG_TEMP_OUT_L | HTS221_INCR_REG_MASK,
                                   (nrf_twi_sensor_reg_cb_t) user_callback,
                                   (uint8_t *) p_temp,
                                   2);
}

int16_t hts221_temp_process(hts221_instance_t * p_instance, int16_t raw_temp)
{
    ASSERT(p_instance != NULL);
    int32_t y;
    int32_t x0 = p_instance->calib_info.T0_OUT;
    int32_t x1 = p_instance->calib_info.T1_OUT;
    int32_t y0 = p_instance->calib_info.T0_degC_x8;
    int32_t y1 = p_instance->calib_info.T1_degC_x8;

    y = ((y0 * (x1 - raw_temp)) + (y1 * (raw_temp - x0))) / (x1 - x0);

    return y;
}

ret_code_t hts221_hum_read(hts221_instance_t *       p_instance,
                           hts221_data_callback_t    user_callback,
                           int16_t *                 p_hum)
{
    ASSERT(p_instance != NULL);
    return nrf_twi_sensor_reg_read(p_instance->p_sensor_data,
                                   p_instance->sensor_addr,
                                   HTS221_REG_HUM_OUT_L | HTS221_INCR_REG_MASK,
                                   (nrf_twi_sensor_reg_cb_t) user_callback,
                                   (uint8_t *) p_hum,
                                   2);
}

int16_t hts221_hum_process(hts221_instance_t * p_instance, int16_t raw_hum)
{
    ASSERT(p_instance != NULL);
    int32_t y;
    int32_t x0 = p_instance->calib_info.H0_T0_OUT;
    int32_t x1 = p_instance->calib_info.H1_T0_OUT;
    int32_t y0 = p_instance->calib_info.H0_rH_x2;
    int32_t y1 = p_instance->calib_info.H1_rH_x2;

    y = ((y0 * (x1 - raw_hum)) + (y1 * (raw_hum - x0))) / (x1 - x0);

    return y;
}


