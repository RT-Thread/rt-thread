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
#include "sx1509b.h"

static sx1509b_instance_t * m_p_instances;
static uint8_t m_max_instance_count;
static uint8_t m_inst_count;

#define RETURN_IF_ERR(_err) \
    if (_err != NRF_SUCCESS)\
    {                       \
        return _err;        \
    }

/**
 * ===============================================================================================
 * @brief General expander utility functions.
 */

void sx1509b_init(sx1509b_instance_t * p_instances, uint8_t count)
{
    ASSERT(p_instances != NULL);
    m_p_instances = p_instances;
    m_max_instance_count = count;
    m_inst_count = 0;
}

static void sx1509b_default_cfg_set(uint8_t instance_num)
{
    m_p_instances[instance_num].start_addr  = 0x00;
    for (uint8_t i = SX1509B_REG_INPUT_DISABLE_B; i < SX1509B_REG_DIR_B; i++)
    {
        m_p_instances[instance_num].registers[i] = 0;
    }
    for (uint8_t i = SX1509B_REG_DIR_B; i < SX1509B_REG_SENSE_H_B; i++)
    {
        m_p_instances[instance_num].registers[i] = 0xFF;
    }
    for (uint8_t i = SX1509B_REG_SENSE_H_B; i < SX1509B_REG_KEY_DATA_1; i++)
    {
        m_p_instances[instance_num].registers[i] = 0;
    }
    m_p_instances[instance_num].registers[SX1509B_REG_KEY_DATA_1] = 0xFF;
    m_p_instances[instance_num].registers[SX1509B_REG_KEY_DATA_2] = 0xFF;
    m_p_instances[instance_num].registers[SX1509B_REG_MISC]       = 0x01;
    m_p_instances[instance_num].high_input[0] = 0;
    m_p_instances[instance_num].high_input[1] = 0;

}
ret_code_t sx1509b_add_instance(nrf_twi_sensor_t * p_twi_sensor,
                                uint8_t            sensor_address)
{
    ASSERT(p_twi_sensor != NULL);
    if (m_p_instances == NULL)
    {
        return NRF_ERROR_MODULE_NOT_INITIALIZED;
    }
    if (m_inst_count >= m_max_instance_count)
    {
        return NRF_ERROR_STORAGE_FULL;
    }
    m_p_instances[m_inst_count].p_sensor_data = p_twi_sensor;
    m_p_instances[m_inst_count].sensor_addr = sensor_address;
    sx1509b_default_cfg_set(m_inst_count);
    m_inst_count++;
    ret_code_t err_code = sx1509b_cfg_write(m_inst_count - 1);

    return err_code;
}

ret_code_t sx1509b_cfg_write(uint8_t instance_num)
{
    if (instance_num >= m_inst_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    ret_code_t err = nrf_twi_sensor_reg_write(m_p_instances[instance_num].p_sensor_data,
                                              m_p_instances[instance_num].sensor_addr,
                                              SX1509B_REG_HIGH_INPUT_B,
                                              m_p_instances[instance_num].high_input,
                                              2);
    RETURN_IF_ERR(err);
    return nrf_twi_sensor_write(m_p_instances[instance_num].p_sensor_data,
                                m_p_instances[instance_num].sensor_addr,
                                &m_p_instances[instance_num].start_addr,
                                SX1509B_REG_COUNT + 1,
                                false);
}

ret_code_t sx1509b_cfg_read(uint8_t instance_num)
{
    if (instance_num >= m_inst_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    ret_code_t err = nrf_twi_sensor_reg_read(m_p_instances[instance_num].p_sensor_data,
                                             m_p_instances[instance_num].sensor_addr,
                                             SX1509B_REG_HIGH_INPUT_B,
                                             NULL,
                                             m_p_instances[instance_num].high_input,
                                             2);
    RETURN_IF_ERR(err);
    return nrf_twi_sensor_reg_read(m_p_instances[instance_num].p_sensor_data,
                                   m_p_instances[instance_num].sensor_addr,
                                   m_p_instances[instance_num].start_addr,
                                   NULL,
                                   m_p_instances[instance_num].registers,
                                   SX1509B_REG_COUNT);
}

ret_code_t sx1509b_clock_set(uint8_t instance_num, sx1509b_clock_t source, bool oscio_set, uint8_t oscio_freq)
{
    if (instance_num >= m_inst_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    uint8_t * p_reg_val = &m_p_instances[instance_num].registers[SX1509B_REG_CLOCK];

    NRF_TWI_SENSOR_REG_SET(*p_reg_val, SX1509B_OSC_SRC_MASK, SX1509B_OSC_SRC_POS, source);
    NRF_TWI_SENSOR_REG_SET(*p_reg_val, SX1509B_OSCIO_PIN_MASK, SX1509B_OSCIO_PIN_POS, oscio_set);
    NRF_TWI_SENSOR_REG_SET(*p_reg_val,
                           SX1509B_OSCOUT_FREQ_MASK,
                           SX1509B_OSCOUT_FREQ_POS,
                           oscio_freq);

    uint8_t send_msg[] = {
        SX1509B_REG_CLOCK,
        *p_reg_val
    };
    return nrf_twi_sensor_write(m_p_instances[instance_num].p_sensor_data,
                                m_p_instances[instance_num].sensor_addr,
                                send_msg,
                                ARRAY_SIZE(send_msg),
                                true);
}

ret_code_t sx1509b_misc_set(uint8_t instance_num,
                            bool nreset_func,
                            sx1509b_debounce_t debounce_time,
                            bool autoclear_nint)
{
    if (instance_num >= m_inst_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    uint8_t * p_reg_val = &m_p_instances[instance_num].registers[SX1509B_REG_MISC];

    NRF_TWI_SENSOR_REG_SET(*p_reg_val, SX1509B_NRESET_PIN_MASK, SX1509B_NRESET_PIN_POS, nreset_func);
    NRF_TWI_SENSOR_REG_SET(*p_reg_val,
                           SX1509B_AUTO_CLEAR_NINT_MASK,
                           SX1509B_AUTO_CLEAR_NINT_POS,
                           autoclear_nint);
    uint8_t send_msg[] = {
        SX1509B_REG_MISC,
        *p_reg_val
    };
    ret_code_t err = nrf_twi_sensor_write(m_p_instances[instance_num].p_sensor_data,
                                          m_p_instances[instance_num].sensor_addr,
                                          send_msg,
                                          ARRAY_SIZE(send_msg),
                                          true);
    RETURN_IF_ERR(err);
    m_p_instances[instance_num].registers[SX1509B_REG_DEBOUNCE_CONFIG] = debounce_time;
    send_msg[0] = SX1509B_REG_DEBOUNCE_CONFIG;
    send_msg[1] = debounce_time;

    return nrf_twi_sensor_write(m_p_instances[instance_num].p_sensor_data,
                                m_p_instances[instance_num].sensor_addr,
                                send_msg,
                                ARRAY_SIZE(send_msg),
                                true);

}

ret_code_t sx1509b_sw_reset(uint8_t instance_num)
{
    if (instance_num >= m_inst_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    uint8_t send_msg[] = {
        SX1509B_REG_SW_RESET,
        SX1509B_INNER_RESET_BYTE1
    };
    ret_code_t err = nrf_twi_sensor_write(m_p_instances[instance_num].p_sensor_data,
                                          m_p_instances[instance_num].sensor_addr,
                                          send_msg,
                                          ARRAY_SIZE(send_msg),
                                          true);
    RETURN_IF_ERR(err);
    send_msg[1] = SX1509B_INNER_RESET_BYTE2;
    err = nrf_twi_sensor_write(m_p_instances[instance_num].p_sensor_data,
                               m_p_instances[instance_num].sensor_addr,
                               send_msg,
                               ARRAY_SIZE(send_msg),
                               true);
    RETURN_IF_ERR(err);
    sx1509b_default_cfg_set(instance_num);
    return err;
}

ret_code_t sx1509b_pin_cfg_reg_set(sx1509b_registers_t reg, uint32_t pin, uint8_t set)
{
    if (pin >= SX1509B_INNER_PIN_COUNT * m_inst_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    uint8_t inst_num = pin / SX1509B_INNER_PIN_COUNT;
    pin %= SX1509B_INNER_PIN_COUNT;
    uint8_t * p_reg_val;

    uint8_t reg_addr = reg;
    uint32_t mask = 1;
    if (reg_addr == SX1509B_REG_LEVEL_SHIFTER_1)
    {
        mask = 3; // Level shifter register parameter is 2 bits long.
        pin %= SX1509B_INNER_NEXT_BANK;
        pin *= 2;
    }
    if (reg_addr == SX1509B_REG_SENSE_H_B)
    {
        reg_addr += 3 - (pin / SX1509B_INNER_SENSE_REG_NUM); // Setting correct sense register
        pin %= SX1509B_INNER_SENSE_REG_NUM;
        pin *= 2; // Multiplying by 2 to make space for 2 bits.
        mask = 3; // Sense register parameter is 2 bits long.
    }
    else
    {
        if (pin >= SX1509B_INNER_NEXT_BANK)
        {
            reg_addr = reg;
            pin -= SX1509B_INNER_NEXT_BANK;
        }
        else
        {
            reg_addr = reg + 1; // Moving to bank A registers

        }
    }

    p_reg_val = &m_p_instances[inst_num].registers[reg_addr];

    NRF_TWI_SENSOR_REG_SET(*p_reg_val, (mask<<pin), pin, set);
    uint8_t send_msg[] = {
        reg_addr,
        *p_reg_val
    };
    return nrf_twi_sensor_write(m_p_instances[inst_num].p_sensor_data,
                                m_p_instances[inst_num].sensor_addr,
                                send_msg,
                                ARRAY_SIZE(send_msg),
                                true);
}

uint8_t sx1509b_pin_cfg_reg_get(sx1509b_registers_t reg, uint32_t pin)
{
    if (pin >= SX1509B_INNER_PIN_COUNT * m_inst_count)
    {
        return 0xFF;
    }

    uint8_t inst_num = pin / SX1509B_INNER_PIN_COUNT;
    pin %= SX1509B_INNER_PIN_COUNT;
    uint8_t * p_reg_val;
    uint8_t reg_addr = reg;
    uint8_t mask = 1;
    if (reg_addr == SX1509B_REG_LEVEL_SHIFTER_1)
    {
        mask = 3; // Level shifter register parameter is 2 bits long.
        pin %= SX1509B_INNER_NEXT_BANK;
        pin *= 2;
    }
    if (reg_addr >= SX1509B_REG_SENSE_H_B && reg_addr <= SX1509B_REG_SENSE_L_A)
    {
        reg_addr += 3 - (pin / SX1509B_INNER_SENSE_REG_NUM); // Setting correct sense register
        pin %= SX1509B_INNER_SENSE_REG_NUM;
        pin *= 2; // Multiplying by 2 to make space for 2 bits.
        mask = 3; // Sense register parameter is 2 bits long.
    }
    else
    {
        reg_addr += (pin >= SX1509B_INNER_NEXT_BANK) ? 0 : 1;
        pin %= SX1509B_INNER_NEXT_BANK;
    }
    p_reg_val = &m_p_instances[inst_num].registers[reg_addr];

    return NRF_TWI_SENSOR_REG_VAL_GET(*p_reg_val,(mask<<pin),pin);
}

ret_code_t sx1509b_port_cfg_reg_set(sx1509b_registers_t reg,
                                    uint32_t            port,
                                    uint8_t             mask,
                                    sx1509b_port_op_t   flag)
{
    if (port >= SX1509B_INNER_PORT_COUNT * m_inst_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    uint8_t inst_num = port / SX1509B_INNER_PORT_COUNT;
    port %= SX1509B_INNER_PORT_COUNT;
    uint8_t reg_addr = reg + !port;

    uint8_t * reg_val = &m_p_instances[inst_num].registers[reg_addr];

    switch (flag)
    {
        case SX1509B_PORT_WRITE:
            *reg_val = mask;
            break;
        case SX1509B_PORT_CLEAR:
            *reg_val &= ~mask;
            break;
        case SX1509B_PORT_SET:
            *reg_val |= mask;
            break;
        default:
            return NRF_ERROR_INVALID_PARAM;
    }
    uint8_t send_msg[] = {
        reg_addr,
        *reg_val
    };
    return nrf_twi_sensor_write(m_p_instances[inst_num].p_sensor_data, m_p_instances[inst_num].sensor_addr, send_msg, ARRAY_SIZE(send_msg), true);
}

uint8_t sx1509b_port_cfg_reg_get(sx1509b_registers_t reg, uint32_t port)
{
    if (port >= SX1509B_INNER_PORT_COUNT * m_inst_count)
    {
        return 0;
    }

    uint8_t inst_num = port / SX1509B_INNER_PORT_COUNT;
    port %= SX1509B_INNER_PORT_COUNT;
    uint8_t reg_addr = reg + !port;
    return m_p_instances[inst_num].registers[reg_addr];
}

ret_code_t sx1509b_pin_data_update(nrf_twi_sensor_reg_cb_t user_cb)
{
    ret_code_t err_code;
    for (uint8_t i = 0; i < m_inst_count - 1; i++)
    {
        err_code = nrf_twi_sensor_reg_read(m_p_instances[i].p_sensor_data,
                                           m_p_instances[i].sensor_addr,
                                           SX1509B_REG_DATA_B,
                                           NULL,
                                           &m_p_instances[i].registers[SX1509B_REG_DATA_B],
                                           2);
        RETURN_IF_ERR(err_code);
    }
    return nrf_twi_sensor_reg_read(m_p_instances[m_inst_count - 1].p_sensor_data,
                                   m_p_instances[m_inst_count - 1].sensor_addr,
                                   SX1509B_REG_DATA_B,
                                   user_cb,
                                   &m_p_instances[m_inst_count - 1].registers[SX1509B_REG_DATA_B],
                                   2);
}

ret_code_t sx1509b_pin_latch_update(nrf_twi_sensor_reg_cb_t user_cb)
{
    ret_code_t err_code;
    for (uint8_t i = 0; i < m_inst_count - 1; i++) // -1 so last read triggers callback
    {
        err_code = nrf_twi_sensor_reg_read(m_p_instances[i].p_sensor_data,
                                           m_p_instances[i].sensor_addr,
                                           SX1509B_REG_INT_SRC_B,
                                           NULL,
                                           &m_p_instances[i].registers[SX1509B_REG_INT_SRC_B],
                                           2);
        RETURN_IF_ERR(err_code);
    }
    return nrf_twi_sensor_reg_read(m_p_instances[m_inst_count - 1].p_sensor_data,
                                   m_p_instances[m_inst_count - 1].sensor_addr,
                                   SX1509B_REG_INT_SRC_B,
                                   user_cb,
                                   &m_p_instances[m_inst_count - 1].registers[SX1509B_REG_INT_SRC_B],
                                   2);
}




ret_code_t sx1509b_pin_high_input(uint32_t pin_number, bool set)
{
    if (pin_number >= SX1509B_INNER_PIN_COUNT * m_inst_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    uint8_t inst_num = pin_number / SX1509B_INNER_PIN_COUNT;
    pin_number %= SX1509B_INNER_PIN_COUNT;
    uint8_t reg_addr;
    uint8_t * p_reg_val;
    if (pin_number < SX1509B_INNER_NEXT_BANK)
    {
        reg_addr = SX1509B_REG_HIGH_INPUT_A;
        p_reg_val = &m_p_instances[inst_num].high_input[1];
    }
    else
    {
        reg_addr = SX1509B_REG_HIGH_INPUT_B;
        p_reg_val = &m_p_instances[inst_num].high_input[0];
        pin_number -= SX1509B_INNER_NEXT_BANK;
    }
    NRF_TWI_SENSOR_REG_SET(*p_reg_val, (1U << pin_number), pin_number, set);
    uint8_t send_msg[] = {
        reg_addr,
        *p_reg_val
    };
    return nrf_twi_sensor_write(m_p_instances[inst_num].p_sensor_data,
                                m_p_instances[inst_num].sensor_addr,
                                send_msg,
                                ARRAY_SIZE(send_msg),
                                true);
}


ret_code_t sx1509b_port_high_input(uint8_t port_num, uint8_t out_mask, sx1509b_port_op_t flag)
{
    if (port_num >= SX1509B_INNER_PORT_COUNT * m_inst_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    uint8_t inst_num = port_num / SX1509B_INNER_PORT_COUNT;
    port_num %= SX1509B_INNER_PORT_COUNT;
    uint8_t reg_addr = SX1509B_REG_HIGH_INPUT_B + !port_num;

    uint8_t * reg_val = &m_p_instances[inst_num].high_input[!port_num];

    switch (flag)
    {
        case SX1509B_PORT_WRITE:
            *reg_val = out_mask;
            break;
        case SX1509B_PORT_CLEAR:
            *reg_val &= ~out_mask;
            break;
        case SX1509B_PORT_SET:
            *reg_val |= out_mask;
            break;
        default:
            return NRF_ERROR_INVALID_PARAM;
    }
    uint8_t send_msg[] = {
        reg_addr,
        *reg_val
    };
    return nrf_twi_sensor_write(m_p_instances[inst_num].p_sensor_data,
                                m_p_instances[inst_num].sensor_addr,
                                send_msg,
                                ARRAY_SIZE(send_msg),
                                true);

}

/**
 * ===============================================================================================
 * @brief Functions compatible with nrf_gpio
 */



ret_code_t sx1509b_pin_cfg_input(uint32_t pin_number, sx1509b_pin_pull_t pull_config)
{
    ret_code_t err_code = sx1509b_pin_cfg_reg_set(SX1509B_REG_DIR_B, pin_number, SX1509B_PIN_DIR_INPUT);
    RETURN_IF_ERR(err_code);
    err_code = sx1509b_pin_cfg_reg_set(SX1509B_REG_INPUT_DISABLE_B, pin_number, 0);
    RETURN_IF_ERR(err_code);
    switch (pull_config)
    {
        case SX1509B_PIN_NOPULL:
            err_code = sx1509b_pin_cfg_reg_set(SX1509B_REG_PULL_DOWN_B, pin_number, 0);
            RETURN_IF_ERR(err_code);
            err_code = sx1509b_pin_cfg_reg_set(SX1509B_REG_PULL_UP_B,   pin_number, 0);
            break;
        case SX1509B_PIN_PULLDOWN:
            err_code = sx1509b_pin_cfg_reg_set(SX1509B_REG_PULL_DOWN_B, pin_number, 1);
            RETURN_IF_ERR(err_code);
            err_code = sx1509b_pin_cfg_reg_set(SX1509B_REG_PULL_UP_B,   pin_number, 0);
            break;
        case SX1509B_PIN_PULLUP:
            err_code = sx1509b_pin_cfg_reg_set(SX1509B_REG_PULL_DOWN_B, pin_number, 0);
            RETURN_IF_ERR(err_code);
            err_code = sx1509b_pin_cfg_reg_set(SX1509B_REG_PULL_UP_B,   pin_number, 1);
            break;
    };
    return err_code;
}

ret_code_t sx1509b_pin_cfg_default(uint32_t pin_number)
{
    if (pin_number >= SX1509B_INNER_PIN_COUNT * m_inst_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    uint8_t inst_num = pin_number / SX1509B_INNER_PIN_COUNT;
    pin_number %= SX1509B_INNER_PIN_COUNT;
    uint8_t reg = (pin_number >= SX1509B_INNER_NEXT_BANK) ? 0 : 1;
    pin_number %= SX1509B_INNER_NEXT_BANK;

    ret_code_t err_code = NRF_SUCCESS;
    for (uint8_t i = SX1509B_REG_INPUT_DISABLE_B + reg; i < SX1509B_REG_DIR_B; i += 2)
    {
        if (IS_SET(m_p_instances[inst_num].registers[i], pin_number) == 1)
        {
            CLR_BIT(m_p_instances[inst_num].registers[i], pin_number);
            err_code = nrf_twi_sensor_reg_write(m_p_instances[inst_num].p_sensor_data,
                                                m_p_instances[inst_num].sensor_addr,
                                                i,
                                                &m_p_instances[inst_num].registers[i],
                                                1);
        }
    }
    for (uint8_t i = SX1509B_REG_DIR_B + reg; i < SX1509B_REG_SENSE_H_B; i += 2)
    {
        if (IS_SET(m_p_instances[inst_num].registers[i], pin_number) == 0)
        {
            SET_BIT(m_p_instances[inst_num].registers[i], pin_number);
            err_code = nrf_twi_sensor_reg_write(m_p_instances[inst_num].p_sensor_data,
                                                m_p_instances[inst_num].sensor_addr,
                                                i,
                                                &m_p_instances[inst_num].registers[i],
                                                1);
        }
    }
    for (uint8_t i = SX1509B_REG_SENSE_H_B + reg; i < SX1509B_REG_KEY_DATA_1; i += 2)
    {
        if (IS_SET(m_p_instances[inst_num].registers[i], pin_number) == 1)
        {
            CLR_BIT(m_p_instances[inst_num].registers[i], pin_number);
            err_code = nrf_twi_sensor_reg_write(m_p_instances[inst_num].p_sensor_data,
                                                m_p_instances[inst_num].sensor_addr,
                                                i,
                                                &m_p_instances[inst_num].registers[i],
                                                1);
        }
    }
    return err_code;
}

ret_code_t sx1509b_pin_cfg_sense_input(uint32_t            pin_number,
                                       sx1509b_pin_pull_t  pull_config,
                                       sx1509b_pin_sense_t sense_config)
{
    ret_code_t err_code = sx1509b_pin_cfg_input(pin_number, pull_config);
    RETURN_IF_ERR(err_code);
    return sx1509b_pin_cfg_sense_set(pin_number, sense_config);
}


ret_code_t sx1509b_pin_cfg_sense_set(uint32_t pin_number, sx1509b_pin_sense_t sense_config)
{
    ret_code_t err;
    if (sense_config == SX1509B_PIN_NOSENSE)
    {
        err = sx1509b_pin_cfg_reg_set(SX1509B_REG_INT_MASK_B, pin_number, 1);
        RETURN_IF_ERR(err);
    }
    else
    {
        err = sx1509b_pin_cfg_reg_set(SX1509B_REG_INT_MASK_B, pin_number, 0);
        RETURN_IF_ERR(err);
    }
    return sx1509b_pin_cfg_reg_set(SX1509B_REG_SENSE_H_B, pin_number, sense_config);
}

ret_code_t sx1509b_pin_dir_set(uint32_t pin_number, sx1509b_pin_dir_t direction)
{
    if (direction == SX1509B_PIN_DIR_INPUT)
    {
        return sx1509b_pin_cfg_input(pin_number, SX1509B_PIN_NOPULL);
    }
    else
    {
        return sx1509b_pin_cfg_output(pin_number);
    }
}

ret_code_t sx1509b_ports_read(uint8_t start_port, uint32_t length, uint8_t * p_masks)
{
    if (start_port + length > SX1509B_INNER_PORT_COUNT * m_inst_count)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    for (uint8_t i = 0; i < length; i++)
    {
        p_masks[i] = sx1509b_port_in_read(start_port + i);
    }
    return NRF_SUCCESS;
}

ret_code_t sx1509b_latches_read(uint8_t start_port, uint32_t length, uint8_t * p_masks)
{
    if (start_port + length > SX1509B_INNER_PORT_COUNT * m_inst_count)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    for (uint8_t i = 0; i < length; i++)
    {
        p_masks[i] = sx1509b_port_cfg_reg_get(SX1509B_REG_INT_SRC_B, start_port + i);
    }
    return NRF_SUCCESS;
}

ret_code_t sx1509b_pin_latch_clear(uint32_t pin_number)
{
    ret_code_t err_code = sx1509b_pin_cfg_reg_set(SX1509B_REG_INT_SRC_B, pin_number, 1);
    RETURN_IF_ERR(err_code);
    uint8_t inst_num = pin_number / SX1509B_INNER_PIN_COUNT;
    pin_number %= SX1509B_INNER_PIN_COUNT;
    uint8_t reg = SX1509B_REG_INT_SRC_B;
    reg += (pin_number >= SX1509B_INNER_NEXT_BANK) ? 0 : 1;
    pin_number %= SX1509B_INNER_NEXT_BANK;
    CLR_BIT(m_p_instances[inst_num].registers[reg], pin_number);
    return err_code;
}

/**
 * ===============================================================================================
 * @brief Led driver functions.
 */

ret_code_t sx1509b_led_driver_enable(uint8_t instance_num, bool clock_internal, uint8_t frequency)
{
    if (instance_num >= m_inst_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    NRF_TWI_SENSOR_REG_SET(m_p_instances[instance_num].registers[SX1509B_REG_CLOCK],
                           SX1509B_OSC_SRC_MASK,
                           SX1509B_OSC_SRC_POS,
                           (clock_internal == 1) ? 2 : 1);
    NRF_TWI_SENSOR_REG_SET(m_p_instances[instance_num].registers[SX1509B_REG_MISC],
                           SX1509B_LED_FREQ_MASK,
                           SX1509B_LED_FREQ_POS,
                           frequency);
    uint8_t send_msg[] = {
        SX1509B_REG_CLOCK,
        m_p_instances[instance_num].registers[SX1509B_REG_CLOCK],
        m_p_instances[instance_num].registers[SX1509B_REG_MISC]
    };
    return nrf_twi_sensor_write(m_p_instances[instance_num].p_sensor_data,
                                m_p_instances[instance_num].sensor_addr,
                                send_msg,
                                ARRAY_SIZE(send_msg),
                                true);
}

ret_code_t sx1509b_led_mode(uint8_t port_num, bool mode)
{
    if (port_num >= SX1509B_INNER_PORT_COUNT * m_inst_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    uint8_t inst_num = port_num / SX1509B_INNER_PORT_COUNT;
    port_num %= SX1509B_INNER_PORT_COUNT;
    uint8_t *p_reg_val = &m_p_instances[inst_num].registers[SX1509B_REG_MISC];

    if (port_num == 1)
    {
        NRF_TWI_SENSOR_REG_SET(*p_reg_val, SX1509B_LED_MODE_B_MASK, SX1509B_LED_MODE_B_POS, mode);
    }
    else
    {
        NRF_TWI_SENSOR_REG_SET(*p_reg_val, SX1509B_LED_MODE_A_MASK, SX1509B_LED_MODE_A_POS, mode);
    }
    uint8_t send_msg[] = {
        SX1509B_REG_MISC,
        *p_reg_val
    };
    return nrf_twi_sensor_write(m_p_instances[inst_num].p_sensor_data,
                                m_p_instances[inst_num].sensor_addr,
                                send_msg,
                                ARRAY_SIZE(send_msg),
                                true);
}

uint8_t sx1509b_led_driver_get_reg(uint32_t pin_number)
{
    uint8_t reg;
    bool fade_reg = false;
    if (pin_number >= SX1509B_INNER_NEXT_BANK)
    {
        pin_number %= SX1509B_INNER_NEXT_BANK;
        if (pin_number >= SX1509B_LED_DRIVER_TIME_REG_NUM)
        {
            reg = SX1509B_REG_LED_FADE_B_START;
            fade_reg = true;
        }
        else
        {
            reg = SX1509B_REG_LED_BANK_B_START;
        }
    }
    else
    {
        if (pin_number >= SX1509B_LED_DRIVER_TIME_REG_NUM)
        {
            reg = SX1509B_REG_LED_FADE_A_START;
            fade_reg = true;
        }
        else
        {
            reg = SX1509B_REG_LED_BANK_A_START;
        }
    }

    if (fade_reg == true)
    {
        pin_number %= SX1509B_LED_DRIVER_FADE_REG_NUM;
        reg += SX1509B_LED_DRIVER_FADE_REG_LEN * pin_number;
    }
    else
    {
        pin_number %= SX1509B_LED_DRIVER_TIME_REG_NUM;
        reg += SX1509B_LED_DRIVER_TIME_REG_LEN * pin_number;
    }

    return reg;
}

ret_code_t sx1509b_led_pin_time(uint32_t pin_number,
                                uint8_t  on_time,
                                uint8_t  on_intensity,
                                uint8_t  off_time,
                                uint8_t  off_intensity)
{
    uint8_t inst_num = pin_number / SX1509B_INNER_PIN_COUNT;
    if (inst_num >= m_inst_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    pin_number %= SX1509B_INNER_PIN_COUNT;
    uint8_t reg = sx1509b_led_driver_get_reg(pin_number);
    uint8_t send_msg[] = {
        reg,
        on_time & 0x1F,
        on_intensity,
        (off_time << SX1509B_OFF_TIME_POS) | (off_intensity & SX1509B_OFF_INTENSITY_MASK)
    };
    return nrf_twi_sensor_write(m_p_instances[inst_num].p_sensor_data,
                                m_p_instances[inst_num].sensor_addr,
                                send_msg,
                                ARRAY_SIZE(send_msg),
                                true);
}

ret_code_t sx1509b_led_pin_fade(uint32_t pin_number, uint8_t fade_in, uint8_t fade_out)
{
    if ((pin_number % SX1509B_INNER_NEXT_BANK) <= SX1509B_LED_DRIVER_TIME_REG_LEN)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    uint8_t inst_num = pin_number / SX1509B_INNER_PIN_COUNT;
    if (inst_num >= m_inst_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    pin_number %= SX1509B_INNER_PIN_COUNT;
    uint8_t reg = sx1509b_led_driver_get_reg(pin_number) + SX1509B_LED_DRIVER_T_RISE;
    uint8_t send_msg[] = {
        reg,
        fade_in & 0x1F,
        fade_out & 0x1F
    };
    return nrf_twi_sensor_write(m_p_instances[inst_num].p_sensor_data,
                                m_p_instances[inst_num].sensor_addr,
                                send_msg,
                                ARRAY_SIZE(send_msg),
                                true);
}

ret_code_t sx1509b_led_pin_enable(uint32_t pin_number)
{
    uint8_t inst_num = pin_number / SX1509B_INNER_PIN_COUNT;
    if (inst_num >= m_inst_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    pin_number %= SX1509B_INNER_PIN_COUNT;
    uint8_t reg_add = (pin_number > SX1509B_INNER_NEXT_BANK) ? 0 : 1;
    pin_number %= SX1509B_INNER_NEXT_BANK;
    SET_BIT(m_p_instances[inst_num].registers[SX1509B_REG_INPUT_DISABLE_B + reg_add],  pin_number);
    CLR_BIT(m_p_instances[inst_num].registers[SX1509B_REG_PULL_UP_B + reg_add],        pin_number);
    SET_BIT(m_p_instances[inst_num].registers[SX1509B_REG_OPEN_DRAIN_B + reg_add],     pin_number);
    CLR_BIT(m_p_instances[inst_num].registers[SX1509B_REG_DIR_B + reg_add],            pin_number);
    CLR_BIT(m_p_instances[inst_num].registers[SX1509B_REG_DATA_B + reg_add],           pin_number);
    SET_BIT(m_p_instances[inst_num].registers[SX1509B_REG_LED_DRV_ENABLE_B + reg_add], pin_number);
    return nrf_twi_sensor_write(m_p_instances[inst_num].p_sensor_data,
                                m_p_instances[inst_num].sensor_addr,
                                &m_p_instances[inst_num].start_addr,
                                SX1509B_REG_DEBOUNCE_CONFIG + 1, // + 1 byte for address
                                false);
}

ret_code_t sx1509b_led_pin_disable(uint32_t pin_number)
{
    uint8_t inst_num = pin_number / SX1509B_INNER_PIN_COUNT;
    if (inst_num >= m_inst_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    pin_number %= SX1509B_INNER_PIN_COUNT;
    uint8_t reg_add = (pin_number > SX1509B_INNER_NEXT_BANK) ? 0 : 1;
    pin_number %= SX1509B_INNER_NEXT_BANK;
    CLR_BIT(m_p_instances[inst_num].registers[SX1509B_REG_INPUT_DISABLE_B + reg_add],  pin_number);
    CLR_BIT(m_p_instances[inst_num].registers[SX1509B_REG_OPEN_DRAIN_B + reg_add],     pin_number);
    SET_BIT(m_p_instances[inst_num].registers[SX1509B_REG_DIR_B + reg_add],            pin_number);
    SET_BIT(m_p_instances[inst_num].registers[SX1509B_REG_DATA_B + reg_add],           pin_number);
    CLR_BIT(m_p_instances[inst_num].registers[SX1509B_REG_LED_DRV_ENABLE_B + reg_add], pin_number);
    return nrf_twi_sensor_write(m_p_instances[inst_num].p_sensor_data,
                                m_p_instances[inst_num].sensor_addr,
                                &m_p_instances[inst_num].start_addr,
                                SX1509B_REG_DEBOUNCE_CONFIG + 1, // + 1 byte for address
                                false);
}

/**
 * ===============================================================================================
 * @brief Key Engine functions.
 */
ret_code_t sx1509b_key_engine_enable(uint8_t             instance_num,
                                     uint8_t             rows,
                                     uint8_t             columns,
                                     sx1509b_key_sleep_t sleep_time,
                                     sx1509b_key_scan_t  scan_time,
                                     sx1509b_debounce_t  debounce_time)
{
    if (instance_num >= m_inst_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    if (rows < 2)
    {
        NRF_TWI_SENSOR_REG_SET(m_p_instances[instance_num].registers[SX1509B_REG_KEY_CONFIG_2],
                               SX1509B_ROW_NUM_MASK,
                               SX1509B_ROW_NUM_POS,
                               0);
        uint8_t send_msg[] = {
            SX1509B_REG_KEY_CONFIG_2,
            m_p_instances[instance_num].registers[SX1509B_REG_KEY_CONFIG_2]
        };
        return nrf_twi_sensor_write(m_p_instances[instance_num].p_sensor_data,
                                    m_p_instances[instance_num].sensor_addr,
                                    send_msg,
                                    ARRAY_SIZE(send_msg),
                                    true);
    }

    uint8_t in_mask = 0, out_mask = 0;
    uint8_t in_port = 0 + instance_num * SX1509B_INNER_PORT_COUNT;
    uint8_t out_port = 1 + instance_num * SX1509B_INNER_PORT_COUNT;
    for (uint8_t i = 0; i < rows; i++)
    {
        in_mask <<= 1;
        in_mask |= 1;
    }

    for (uint8_t i = 0; i < columns; i++)
    {
        out_mask <<= 1;
        out_mask |= 1;
    }

    ret_code_t err = sx1509b_port_dir_output_set(in_port, in_mask);
    RETURN_IF_ERR(err);
    err = sx1509b_port_dir_input_set(out_port, out_mask);
    RETURN_IF_ERR(err);
    err = sx1509b_port_open_drain(out_port, out_mask, SX1509B_PORT_SET);
    RETURN_IF_ERR(err);
    err = sx1509b_port_pull_up(in_port, in_mask, SX1509B_PORT_SET);
    RETURN_IF_ERR(err);

    m_p_instances[instance_num].registers[SX1509B_REG_DEBOUNCE_CONFIG] =  debounce_time;
    m_p_instances[instance_num].registers[SX1509B_REG_DEBOUNCE_EN_B] |= in_mask;
    NRF_TWI_SENSOR_REG_SET(m_p_instances[instance_num].registers[SX1509B_REG_KEY_CONFIG_1],
                           SX1509B_SLEEP_TIME_MASK,
                           SX1509B_SLEEP_TIME_POS,
                           sleep_time);
    NRF_TWI_SENSOR_REG_SET(m_p_instances[instance_num].registers[SX1509B_REG_KEY_CONFIG_1],
                           SX1509B_SCAN_TIME_MASK,
                           SX1509B_SCAN_TIME_POS,
                           scan_time);
    NRF_TWI_SENSOR_REG_SET(m_p_instances[instance_num].registers[SX1509B_REG_KEY_CONFIG_2],
                           SX1509B_ROW_NUM_MASK,
                           SX1509B_ROW_NUM_POS,
                           rows - 1);
    NRF_TWI_SENSOR_REG_SET(m_p_instances[instance_num].registers[SX1509B_REG_KEY_CONFIG_2],
                           SX1509B_COL_NUM_MASK,
                           SX1509B_COL_NUM_POS,
                           columns - 1);
    uint8_t send_msg[] = {
        SX1509B_REG_DEBOUNCE_CONFIG,
        m_p_instances[instance_num].registers[SX1509B_REG_DEBOUNCE_CONFIG],
        m_p_instances[instance_num].registers[SX1509B_REG_DEBOUNCE_EN_B],
        m_p_instances[instance_num].registers[SX1509B_REG_DEBOUNCE_EN_A],
        m_p_instances[instance_num].registers[SX1509B_REG_KEY_CONFIG_1],
        m_p_instances[instance_num].registers[SX1509B_REG_KEY_CONFIG_2]
    };
    return nrf_twi_sensor_write(m_p_instances[instance_num].p_sensor_data,
                                m_p_instances[instance_num].sensor_addr,
                                send_msg,
                                ARRAY_SIZE(send_msg),
                                true);
}

ret_code_t sx1509b_key_data_update(uint8_t instance_num, nrf_twi_sensor_reg_cb_t user_cb)
{
    if (instance_num >= m_inst_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    return nrf_twi_sensor_reg_read(m_p_instances[instance_num].p_sensor_data,
                                   m_p_instances[instance_num].sensor_addr,
                                   SX1509B_REG_KEY_DATA_1,
                                   user_cb,
                                   &m_p_instances[instance_num].registers[SX1509B_REG_KEY_DATA_1],
                                   2);
}

static uint8_t sx1509b_key_get_bit_pos(uint8_t reg)
{
    uint8_t ret_val = 0xFF;
    for(uint8_t i = 0; i < 8; i++)
    {
        if (IS_SET(reg, 0) == 1)
        {
            ret_val = i;
            break;
        }
        reg >>= 1;
    }
    return ret_val;
}

uint8_t sx1509b_key_column_get(uint8_t instance_num)
{
    if (instance_num >= m_inst_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    uint8_t reg_val = ~m_p_instances[instance_num].registers[SX1509B_REG_KEY_DATA_1];

    return sx1509b_key_get_bit_pos(reg_val);

}

uint8_t sx1509b_key_row_get(uint8_t instance_num)
{
    if (instance_num >= m_inst_count)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    uint8_t reg_val = ~m_p_instances[instance_num].registers[SX1509B_REG_KEY_DATA_2];

    return sx1509b_key_get_bit_pos(reg_val);
}
