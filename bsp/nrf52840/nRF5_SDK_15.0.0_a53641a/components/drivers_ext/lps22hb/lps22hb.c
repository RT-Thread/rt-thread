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

#include "lps22hb.h"

ret_code_t lps22hb_init(lps22hb_instance_t * p_instance)
{
    ASSERT(p_instance != NULL);
    p_instance->interrupt_cfg = 0;
    p_instance->ctrl_reg[0]   = 0;
    p_instance->ctrl_reg[1]   = LPS22HB_CTRL_REG2_DEFAULT;
    p_instance->ctrl_reg[2]   = 0;
    p_instance->fifo_ctrl     = 0;
    ret_code_t err_code;
    if (p_instance->p_sensor_data->p_twi_mngr->p_queue->size < LPS22HB_MIN_QUEUE_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    err_code = lps22hb_cfg_commit(p_instance);
    return err_code;
}

ret_code_t lps22hb_autorifp_enable(lps22hb_instance_t * p_instance, bool enable)
{
    ASSERT(p_instance != NULL);
    uint8_t reg = p_instance->interrupt_cfg;
    if (enable == true)
    {
        NRF_TWI_SENSOR_REG_SET(reg, LPS22HB_AUTORIFP_MASK, LPS22HB_AUTORIFP_POS, 1);
    }
    else
    {
        NRF_TWI_SENSOR_REG_SET(reg, LPS22HB_RESET_ARP_MASK, LPS22HB_RESET_ARP_POS, 1);
    }
    uint8_t send_msg[] = {
        LPS22HB_REG_INTERRUPT_CONFIG,
        reg
    };
    return nrf_twi_sensor_write(p_instance->p_sensor_data,
                                p_instance->sensor_addr,
                                send_msg,
                                ARRAY_SIZE(send_msg),
                                true);
}

ret_code_t lps22hb_autozero_enable(lps22hb_instance_t * p_instance, bool enable)
{
    ASSERT(p_instance != NULL);
    uint8_t reg = p_instance->interrupt_cfg;
    if (enable == true)
    {
        NRF_TWI_SENSOR_REG_SET(reg, LPS22HB_AUTOZERO_MASK, LPS22HB_AUTOZERO_POS, 1);
    }
    else
    {
        NRF_TWI_SENSOR_REG_SET(reg, LPS22HB_RESET_AZ_MASK, LPS22HB_RESET_AZ_POS, 1);
    }
    uint8_t send_msg[] = {
        LPS22HB_REG_INTERRUPT_CONFIG,
        reg
    };
    return nrf_twi_sensor_write(p_instance->p_sensor_data,
                                p_instance->sensor_addr,
                                send_msg,
                                ARRAY_SIZE(send_msg),
                                true);
}


void lps22hb_data_rate_set(lps22hb_instance_t * p_instance, lps22hb_odr_t odr)
{
    ASSERT(p_instance != NULL);
    NRF_TWI_SENSOR_REG_SET(p_instance->ctrl_reg[0], LPS22HB_ODR_MASK, LPS22HB_ODR_POS, odr);
}

ret_code_t lps22hb_data_read(lps22hb_instance_t *    p_instance,
                             lps22hb_data_callback_t user_callback,
                             lps22hb_data_t *        p_out_data,
                             uint8_t                 samples)
{
    ASSERT(p_instance != NULL);
    ret_code_t err_code;
    err_code = nrf_twi_sensor_reg_read(p_instance->p_sensor_data,
                                       p_instance->sensor_addr,
                                       LPS22HB_REG_PRESS_OUT_XL,
                                       (nrf_twi_sensor_reg_cb_t) user_callback,
                                       (uint8_t *) p_out_data,
                                       samples * LPS22HB_BYTES_PER_SAMPLE);
    return err_code;
}

void lps22hb_data_decode(lps22hb_data_t * p_data, uint8_t samples)
{
    ASSERT(p_data != NULL);
    lps22hb_raw_data_t * p_in_data = (lps22hb_raw_data_t *) p_data;
    uint32_t pres;
    uint16_t temp;
    for (int i = samples-1; i >= 0; i--)
    {
        pres = ((uint32_t) p_in_data[i].press_out_xl) |
               (((uint32_t) p_in_data[i].press_out_l) << 8) |
               (((uint32_t) p_in_data[i].press_out_h) << 16);
        pres <<= 8;
        temp = ((uint16_t) p_in_data[i].temp_out_l) |
               (((uint16_t) p_in_data[i].temp_out_h) << 8);
        // Dividing by 256 because signed integer can't be shifted by 8
        p_data[i].pressure    = *((int32_t *) &pres) / 256;
        p_data[i].temperature = *((int16_t *) &temp);
    }
}

ret_code_t lps22hb_threshold_set(lps22hb_instance_t * p_instance, uint16_t thr)
{
    ASSERT(p_instance != NULL);
    thr *= 16;
    uint8_t send_msg[] = {
        LPS22HB_REG_THS_P_L,
        thr & 0x00FFU,
        thr >> 8
    };
    ret_code_t err_code;
    err_code = nrf_twi_sensor_write(p_instance->p_sensor_data,
                                    p_instance->sensor_addr,
                                    send_msg,
                                    ARRAY_SIZE(send_msg),
                                    true);
    return err_code;
}

ret_code_t lps22hb_ref_pressure_set(lps22hb_instance_t * p_instance, int32_t pressure)
{
    ASSERT(p_instance != NULL);
    // Multiplying by 256 because signed integer can't be shifted by 8
    pressure *= 256;
    uint32_t pres = *((uint32_t *) &pressure);
    pres >>= 8;
    uint8_t send_msg[] = {
        LPS22HB_REG_REF_P_XL,
        pres & 0x00FFU,
        (pres >> 8) & 0x00FFU,
        (pres >> 16) & 0x00FFU
    };
    ret_code_t err_code;
    err_code = nrf_twi_sensor_write(p_instance->p_sensor_data,
                                    p_instance->sensor_addr,
                                    send_msg,
                                    ARRAY_SIZE(send_msg),
                                    true);
    return err_code;
}

ret_code_t lps22hb_offset_set(lps22hb_instance_t * p_instance, int16_t offset)
{
    ASSERT(p_instance != NULL);
    offset *= 16;
    uint16_t off = *((uint16_t *) &offset);
    uint8_t send_msg[] = {
        LPS22HB_REG_RPDS_L,
        off & 0x00FFU,
        off >> 8
    };
    ret_code_t err_code;
    err_code = nrf_twi_sensor_write(p_instance->p_sensor_data,
                                    p_instance->sensor_addr,
                                    send_msg,
                                    ARRAY_SIZE(send_msg),
                                    true);
    return err_code;
}



ret_code_t lps22hb_cfg_commit(lps22hb_instance_t * p_instance)
{
    ASSERT(p_instance != NULL);
    p_instance->ctrl_reg[1] |= LPS22HB_CTRL_REG2_DEFAULT;
    p_instance->ctrl_reg[0] &= ~LPS22HB_CTRL1_VALID_MASK;
    p_instance->ctrl_reg[1] &= ~LPS22HB_CTRL2_VALID_MASK;

    ret_code_t err_code;

    err_code = nrf_twi_sensor_reg_write(p_instance->p_sensor_data,
                                        p_instance->sensor_addr,
                                        LPS22HB_REG_INTERRUPT_CONFIG,
                                        &p_instance->interrupt_cfg,
                                        1);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    err_code = nrf_twi_sensor_reg_write(p_instance->p_sensor_data,
                                        p_instance->sensor_addr,
                                        LPS22HB_REG_CTRL1,
                                        p_instance->ctrl_reg,
                                        3);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    err_code = nrf_twi_sensor_reg_write(p_instance->p_sensor_data,
                                        p_instance->sensor_addr,
                                        LPS22HB_REG_FIFO_CTRL,
                                        &p_instance->fifo_ctrl,
                                        1);
    return err_code;
}

ret_code_t lps22hb_sw_reset(lps22hb_instance_t * p_instance)
{
    ASSERT(p_instance != NULL);
    uint8_t reg_val = p_instance->ctrl_reg[1];
    NRF_TWI_SENSOR_REG_SET(reg_val, LPS22HB_SWRESET_MASK, LPS22HB_SWRESET_POS, 1);

    uint8_t send_msg[] = {
        LPS22HB_REG_CTRL2,
        reg_val
    };
    ret_code_t err_code;
    err_code = nrf_twi_sensor_write(p_instance->p_sensor_data,
                                    p_instance->sensor_addr,
                                    send_msg,
                                    ARRAY_SIZE(send_msg),
                                    true);

    return err_code;
}

ret_code_t lps22hb_boot(lps22hb_instance_t * p_instance)
{
    ASSERT(p_instance != NULL);
    uint8_t reg_val = p_instance->ctrl_reg[1];
    NRF_TWI_SENSOR_REG_SET(reg_val, LPS22HB_BOOT_MASK, LPS22HB_BOOT_POS, 1);

    uint8_t send_msg[] = {
        LPS22HB_REG_CTRL2,
        reg_val
    };
    ret_code_t err_code;
    err_code = nrf_twi_sensor_write(p_instance->p_sensor_data,
                                    p_instance->sensor_addr,
                                    send_msg,
                                    ARRAY_SIZE(send_msg),
                                    true);

    return err_code;
}

ret_code_t lps22hb_oneshot(lps22hb_instance_t * p_instance)
{
    ASSERT(p_instance != NULL);
    uint8_t reg_val = p_instance->ctrl_reg[1];
    NRF_TWI_SENSOR_REG_SET(reg_val, LPS22HB_ONE_SHOT_MASK, LPS22HB_ONE_SHOT_POS, 1);

    uint8_t send_msg[] = {
        LPS22HB_REG_CTRL2,
        reg_val
    };
    ret_code_t err_code;
    err_code = nrf_twi_sensor_write(p_instance->p_sensor_data,
                                    p_instance->sensor_addr,
                                    send_msg,
                                    ARRAY_SIZE(send_msg),
                                    true);

    return err_code;
}

ret_code_t lps22hb_low_power_enable(lps22hb_instance_t * p_instance, bool enable)
{
    ASSERT(p_instance != NULL);
    uint8_t send_msg[] = {
        LPS22HB_REG_RES_CONF,
        enable
    };
    ret_code_t err_code;
    err_code = nrf_twi_sensor_write(p_instance->p_sensor_data,
                                    p_instance->sensor_addr,
                                    send_msg,
                                    ARRAY_SIZE(send_msg),
                                    true);
    return err_code;
}
