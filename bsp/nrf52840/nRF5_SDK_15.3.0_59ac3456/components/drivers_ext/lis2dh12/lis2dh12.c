/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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

#include "lis2dh12.h"

#define RETURN_IF_ERR(err)  \
    if (err != NRF_SUCCESS) \
    {                       \
        return err;         \
    }

ret_code_t lis2dh12_init(lis2dh12_instance_t * p_inst)
{
    ASSERT(p_inst != NULL);
    memset(&p_inst->temp_cfg, 0, &p_inst->act_dur - &p_inst->temp_cfg);
    p_inst->ctrl0     = LIS2DH12_CTRL_REG0_VALID_SET;
    p_inst->ctrl1     = 0x07;
    p_inst->ctrl4     = 0x80;

    return lis2dh12_cfg_commit(p_inst);
}

ret_code_t lis2dh12_cfg_commit(lis2dh12_instance_t * p_inst)
{
    ASSERT(p_inst != NULL);
    ret_code_t err;
    p_inst->ctrl0 &= ~LIS2DH12_CTRL_REG0_VALID_MASK;
    p_inst->ctrl0 |= LIS2DH12_CTRL_REG0_VALID_SET;

    uint8_t ctrl_msg[] = {
        LIS2DH12_REG_CTRL_REG0 | LIS2DH12_AUTO_INCR_MASK,
        p_inst->ctrl0,
        p_inst->temp_cfg,
        p_inst->ctrl1,
        p_inst->ctrl2,
        p_inst->ctrl3,
        p_inst->ctrl4,
        p_inst->ctrl5,
        p_inst->ctrl6,
        p_inst->reference
    };
    err = nrf_twi_sensor_write(p_inst->p_sensor_data,
                               p_inst->sensor_addr,
                               ctrl_msg,
                               ARRAY_SIZE(ctrl_msg),
                               true);
    RETURN_IF_ERR(err);
    uint8_t fifo_msg[] = {
        LIS2DH12_REG_FIFO_CTRL | LIS2DH12_AUTO_INCR_MASK,
        p_inst->fifo_ctrl,
        0,
        p_inst->int1_cfg,
        0,
        p_inst->int1_ths,
        p_inst->int1_dur,
        p_inst->int2_cfg,
        0,
        p_inst->int2_ths,
        p_inst->int2_dur,
        p_inst->click_cfg
    };
    err = nrf_twi_sensor_write(p_inst->p_sensor_data,
                               p_inst->sensor_addr,
                               fifo_msg,
                               ARRAY_SIZE(fifo_msg),
                               true);
    RETURN_IF_ERR(err);

    uint8_t time_msg[] = {
        LIS2DH12_REG_CLICK_THS | LIS2DH12_AUTO_INCR_MASK,
        p_inst->click_ths,
        p_inst->time_lim,
        p_inst->latency,
        p_inst->time_win,
        p_inst->act_ths,
        p_inst->act_dur
    };
    err = nrf_twi_sensor_write(p_inst->p_sensor_data,
                               p_inst->sensor_addr,
                               time_msg,
                               ARRAY_SIZE(time_msg),
                               true);
    return err;
}

ret_code_t lis2dh12_data_read(lis2dh12_instance_t * p_inst,
                              lis2dh12_data_cb_t    user_cb,
                              lis2dh12_data_t *     p_data,
                              uint8_t               samples)
{
    ASSERT(p_inst != NULL);
    return nrf_twi_sensor_reg_read(p_inst->p_sensor_data,
                                   p_inst->sensor_addr,
                                   LIS2DH12_REG_OUT_X_L | LIS2DH12_AUTO_INCR_MASK,
                                   (nrf_twi_sensor_reg_cb_t) user_cb,
                                   (uint8_t *) p_data,
                                   samples * LIS2DH12_BYTES_PER_SAMPLE);
}

ret_code_t lis2dh12_temp_enable(lis2dh12_instance_t * p_inst, bool temp_en)
{
    ASSERT(p_inst != NULL);
    if (temp_en == true)
    {
        NRF_TWI_SENSOR_REG_SET(p_inst->temp_cfg, LIS2DH12_TEMP_EN_MASK, LIS2DH12_TEMP_EN_POS, 3);
    }
    else
    {
        NRF_TWI_SENSOR_REG_SET(p_inst->temp_cfg, LIS2DH12_TEMP_EN_MASK, LIS2DH12_TEMP_EN_POS, 0);
    }

    uint8_t send_msg[] = {
        LIS2DH12_REG_TEMP_CFG_REG,
        p_inst->temp_cfg
    };

    return nrf_twi_sensor_write(p_inst->p_sensor_data,
                                p_inst->sensor_addr,
                                send_msg,
                                ARRAY_SIZE(send_msg),
                                true);

}

ret_code_t lis2dh12_temp_read(lis2dh12_instance_t * p_inst,
                              lis2dh12_temp_cb_t    user_cb,
                              int16_t *             p_temp)
{
    ASSERT(p_inst != NULL);
    return nrf_twi_sensor_reg_read(p_inst->p_sensor_data,
                                   p_inst->sensor_addr,
                                   LIS2DH12_REG_OUT_TEMP_L | LIS2DH12_AUTO_INCR_MASK,
                                   (nrf_twi_sensor_reg_cb_t) user_cb,
                                   (uint8_t *) p_temp,
                                   LIS2DH12_BYTES_PER_TEMP);
}
