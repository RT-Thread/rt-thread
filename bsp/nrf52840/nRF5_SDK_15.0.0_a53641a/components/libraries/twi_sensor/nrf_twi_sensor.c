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
#include "nrf_twi_sensor.h"
#include <string.h>

#define NRF_LOG_MODULE_NAME twi_sensor
#if NRF_TWI_SENSOR_CONFIG_LOG_ENABLED
    #define NRF_LOG_LEVEL       NRF_TWI_SENSOR_CONFIG_LOG_LEVEL
    #define NRF_LOG_INFO_COLOR  NRF_TWI_SENSOR_CONFIG_INFO_COLOR
    #define NRF_LOG_DEBUG_COLOR NRF_TWI_SENSOR_CONFIG_DEBUG_COLOR
#else
    #define NRF_LOG_LEVEL       0
#endif // NRF_TWI_SENSOR_CONFIG_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();


ret_code_t nrf_twi_sensor_init(nrf_twi_sensor_t * p_twi_sensor)
{
    return nrf_balloc_init(p_twi_sensor->p_pool);
}

static void sensor_read_reg_cb(ret_code_t result, void * p_user_data)
{
    nrf_twi_sensor_read_cmd_t * p_cmd = &((nrf_twi_sensor_cmd_t *) p_user_data)->read;
    NRF_LOG_INFO("Read cb reg addr: 0x%02X, result %d", p_cmd->reg_address, result);
    NRF_LOG_DEBUG("\r\nCallback pointer: %p\r\nData:", p_cmd->user_cb);
    NRF_LOG_HEXDUMP_DEBUG(p_cmd->transfers[1].p_data, p_cmd->transfers[1].length);

    if (p_cmd->user_cb != NULL)
    {
        p_cmd->user_cb(result, (void*)p_cmd->transfers[1].p_data);
    }
    nrf_balloc_free(p_cmd->p_instance->p_pool, p_user_data);
}

ret_code_t nrf_twi_sensor_reg_read(nrf_twi_sensor_t const * p_instance,
                                   uint8_t                  sensor_addr,
                                   uint8_t                  reg_address,
                                   nrf_twi_sensor_reg_cb_t  user_cb,
                                   uint8_t *                p_data,
                                   uint8_t                  length)
{
    ASSERT(p_instance != NULL);
    ASSERT(p_data != NULL);
    NRF_LOG_INFO("Sensor addr: 0x%02X"
                 "\r\nRead reg addr: 0x%02X, bytes %d",
                 sensor_addr,
                 reg_address,
                 length);

    nrf_twi_sensor_read_cmd_t * p_cmd =
            (nrf_twi_sensor_read_cmd_t *) nrf_balloc_alloc(p_instance->p_pool);
    if (p_cmd == NULL)
    {
        NRF_LOG_WARNING("Memory not allocated.");
        return NRF_ERROR_NO_MEM;
    }

    p_cmd->p_instance   = p_instance;
    p_cmd->user_cb      = user_cb;
    p_cmd->reg_address  = reg_address;

    p_cmd->transfers[0] = (nrf_twi_mngr_transfer_t) NRF_TWI_MNGR_WRITE(sensor_addr,
                                                                       &p_cmd->reg_address,
                                                                       1,
                                                                       NRF_TWI_MNGR_NO_STOP);

    p_cmd->transfers[1] = (nrf_twi_mngr_transfer_t) NRF_TWI_MNGR_READ(sensor_addr,
                                                                      p_data,
                                                                      length,
                                                                      NRF_TWI_MNGR_NO_STOP);

    p_cmd->transaction = (nrf_twi_mngr_transaction_t) {
        .callback            = sensor_read_reg_cb,
        .p_user_data         = p_cmd,
        .p_transfers         = p_cmd->transfers,
        .number_of_transfers = ARRAY_SIZE(p_cmd->transfers)
    };

    ret_code_t err_code = nrf_twi_mngr_schedule(p_instance->p_twi_mngr, &p_cmd->transaction);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_WARNING("Transaction not scheduled.\r\nSensor addr: 0x%02X Error code: %d",
                        sensor_addr,
                        err_code);
        nrf_balloc_free(p_instance->p_pool, p_cmd);
    }
    return err_code;
}

static void sensor_write_reg_cb(ret_code_t result, void * p_user_data)
{
    nrf_twi_sensor_write_cmd_t * p_cmd = &((nrf_twi_sensor_cmd_t *) p_user_data)->write;
    NRF_LOG_INFO("Write cb reg addr: 0x%02X, result %d", p_cmd->send_msg[0], result);
    nrf_balloc_free(p_cmd->p_instance->p_pool, p_user_data);
}

ret_code_t nrf_twi_sensor_write(nrf_twi_sensor_t const * p_instance,
                                uint8_t            sensor_addr,
                                uint8_t const *    p_data,
                                uint8_t            length,
                                bool               copy_flag)
{
    ASSERT(p_instance != NULL);
    ASSERT(p_data != NULL);
    NRF_LOG_INFO("Sensor addr: 0x%02X Write length %d", sensor_addr, length);
    NRF_LOG_DEBUG("Data: ");
    NRF_LOG_HEXDUMP_DEBUG(p_data, length);
    nrf_twi_sensor_write_cmd_t * p_cmd =
            (nrf_twi_sensor_write_cmd_t *) nrf_balloc_alloc(p_instance->p_pool);
    if (p_cmd == NULL)
    {
        NRF_LOG_WARNING("Memory not allocated. Sensor addr: 0x%02X",
                        sensor_addr);
        return NRF_ERROR_NO_MEM;
    }

    p_cmd->p_instance = p_instance;

    p_cmd->transfer = (nrf_twi_mngr_transfer_t) NRF_TWI_MNGR_WRITE(sensor_addr,
                                                                   p_data,
                                                                   length,
                                                                   0);

    if (copy_flag == true)
    {
        if (length > NRF_TWI_SENSOR_SEND_BUF_SIZE)
        {
            NRF_LOG_ERROR("Data too long to copy. Sensor addr: 0x%02X"
                          "\r\nRequested write length: %d, max length: %d",
                          sensor_addr,
                          length,
                          NRF_TWI_SENSOR_SEND_BUF_SIZE);
            nrf_balloc_free(p_instance->p_pool, p_cmd);
            return NRF_ERROR_INVALID_LENGTH;
        }
        memcpy(p_cmd->send_msg, p_data, length);
        p_cmd->transfer.p_data = p_cmd->send_msg;
    }

    p_cmd->transaction = (nrf_twi_mngr_transaction_t) {
        .callback            = sensor_write_reg_cb,
        .p_user_data         = p_cmd,
        .p_transfers         = &p_cmd->transfer,
        .number_of_transfers = 1
    };

    ret_code_t err_code = nrf_twi_mngr_schedule(p_instance->p_twi_mngr, &p_cmd->transaction);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_WARNING("Transaction not scheduled.\r\nSensor addr: 0x%02X Error code: %d",
                        sensor_addr,
                        err_code);
        nrf_balloc_free(p_instance->p_pool, p_cmd);
    }
    return err_code;
}

ret_code_t nrf_twi_sensor_reg_write(nrf_twi_sensor_t const * p_instance,
                                    uint8_t                  sensor_addr,
                                    uint8_t                  reg_address,
                                    uint8_t *                p_data,
                                    uint8_t                  length)
{
    ASSERT(p_instance != NULL);
    ASSERT(p_data != NULL);
    NRF_LOG_INFO("Write register: 0x%02X", reg_address);
    if (length > NRF_TWI_SENSOR_SEND_BUF_SIZE - 1) // Subtracting one byte for address
    {
        NRF_LOG_ERROR("Data too long to copy. Sensor addr: 0x%02X"
                      "\r\nRequested write length: %d, max length: %d",
                      sensor_addr,
                      length,
                      NRF_TWI_SENSOR_SEND_BUF_SIZE - 1);
        return NRF_ERROR_INVALID_LENGTH;
    }
    uint8_t buf[NRF_TWI_SENSOR_SEND_BUF_SIZE];

    buf[0] = reg_address;
    memcpy(&buf[1], p_data, length);
    return nrf_twi_sensor_write(p_instance, sensor_addr, buf, length + 1, true);
}
