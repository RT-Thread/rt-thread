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

/**@file
 *
 * @defgroup nrf_twi_sensor TWI Sensor module.
 * @{
 * @ingroup app_common
 */

#ifndef NRF_TWI_SENSOR_H
#define NRF_TWI_SENSOR_H

#include "nrf_twi_mngr.h"
#include "nrf_balloc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Internal write operation buffer length.
 *
 * Defines how many bytes can be stored internally.
 * 16 bytes were selected so that nrf_twi_sensor_write_cmd_t size
 * matches nrf_twi_sensor_read_cmd_t size.
 */
#define NRF_TWI_SENSOR_SEND_BUF_SIZE   16

/**
 * @brief Register read callback prototype.
 *
 * @param[in] result            Return error code from TWI manager and underlying drivers.
 * @param[in] p_register_data   Pointer to register value.
 */
typedef void (* nrf_twi_sensor_reg_cb_t)(ret_code_t result, void * p_register_data);


/**
 * @brief Structure holding sensor instance
 */
typedef struct
{
    nrf_twi_mngr_t const * const p_twi_mngr;
    nrf_balloc_t const * const   p_pool;


} nrf_twi_sensor_t;

/**
 * @brief Struct describing sensor read command.
 *
 * @note For internal use only.
 */
typedef struct
{
    uint8_t                     reg_address;
    nrf_twi_mngr_transfer_t     transfers[2];
    nrf_twi_mngr_transaction_t  transaction;
    nrf_twi_sensor_reg_cb_t     user_cb;
    nrf_twi_sensor_t const *    p_instance;
} nrf_twi_sensor_read_cmd_t;

/**
 * @brief Struct describing sensor write command.
 *
 * @note  For internal use only.
 */
typedef struct
{
    uint8_t                     send_msg[NRF_TWI_SENSOR_SEND_BUF_SIZE];
    nrf_twi_mngr_transfer_t     transfer;
    nrf_twi_mngr_transaction_t  transaction;
    nrf_twi_sensor_t const *    p_instance;
} nrf_twi_sensor_write_cmd_t;

/**
 * @brief Union for sensor commands. Needed in buffer definition.
 *
 * @note For internal use only.
 */
typedef union
{
    nrf_twi_sensor_read_cmd_t  read;
    nrf_twi_sensor_write_cmd_t write;
} nrf_twi_sensor_cmd_t;


/**
 * @brief Macro creating common twi sensor instance.
 *
 * Data in structure is used for basic communication with sensors.
 * THere should be one instance per TWI bus.
 *
 * @param[in] twi_sensor_name   TWI common sensor instance name.
 * @param[in] p_nrf_twi_mngr    Pointer to TWI Manager instance. @ref NRF_TWI_MNGR_DEF
 * @param[in] msg_buff_size     Size of buffer used in communication
 *
 * @note Buffer size should be less or equal to TWI manager queue size.
 *       Minimum buffer size can be found after checking utilization of sensor buffer.
 */
#define NRF_TWI_SENSOR_DEF(twi_sensor_name, p_nrf_twi_mngr, msg_buff_size) \
    NRF_BALLOC_DEF(CONCAT_2(twi_sensor_name,_pool), sizeof(nrf_twi_sensor_cmd_t), msg_buff_size);\
    static nrf_twi_sensor_t twi_sensor_name =                                                    \
    {                                                                                            \
        .p_twi_mngr = p_nrf_twi_mngr,                                                            \
        .p_pool     = &CONCAT_2(twi_sensor_name,_pool)                                           \
    }

/**
 * @brief Macro for defining TWI manager read transfer.
 *
 * @note  For internal use only.
 */
#define NRF_TWI_SENSOR_READ(p_reg_addr, p_buffer, byte_cnt) \
    NRF_TWI_MNGR_WRITE(0x00, p_reg_addr, 1,        NRF_TWI_MNGR_NO_STOP), \
    NRF_TWI_MNGR_READ (0x00, p_buffer,   byte_cnt, 0)

/**
 * @brief Macro for defining TWI manager write transfer.
 *
 * @note  For internal use only.
 */
#define NRF_TWI_SENSOR_WRITE(p_buffer, byte_cnt) \
    NRF_TWI_MNGR_WRITE(0x00, p_buffer, byte_cnt, 0)


/**
 * @brief Macro for assigning sensor address to transfers.
 *
 * @param[in] _transfers   Transfers array.
 * @param[in] _sensor_addr Desired sensor address.
 *
 * @note  For internal use only.
 */
#define NRF_TWI_SENSOR_ADDRESS_SET(_transfers, _sensor_addr)                                \
    for (uint8_t i = 0; i < ARRAY_SIZE(_transfers); i++)                                    \
    {                                                                                       \
        if (i % 2 == 0)                                                                     \
        {                                                                                   \
            transfers[i].operation = NRF_TWI_MNGR_WRITE_OP(_sensor_addr);                   \
        }                                                                                   \
        else                                                                                \
        {                                                                                   \
            transfers[i].operation = NRF_TWI_MNGR_READ_OP(_sensor_addr);                    \
        }                                                                                   \
    }

/**
 * @brief Macro for setting parameters in sensor register.
 *
 * @param[in,out] _register Register to be altered.
 * @param[in]     _msk      Parameter mask.
 * @param[in]     _pos      Parameter position.
 * @param[in]     _val      Parameter value to be set.
 */
#define NRF_TWI_SENSOR_REG_SET(_register, _msk, _pos, _val)   \
    _register &= ~(_msk);                                  \
    _register |= ((_msk) & ((_val) << (_pos)))


/**
 * @brief Macro for getting parameters from sensor register.
 *
 * @param[in] _register Register to be processed.
 * @param[in] _msk      Parameter mask.
 * @param[in] _pos      Parameter position.
 *
 * @note For usage with registers read using nrf_twi_sensor_register_read function.
 *
 * @return  Parameter value
 */
#define NRF_TWI_SENSOR_REG_VAL_GET(_register, _msk, _pos) \
    (((_register) & (_msk)) >> (_pos))

/**
 * @brief Function for initialization of sensor common instance.
 *
 * @note TWI Manager should be initialized before @ref nrf_twi_mngr_init
 * @param[in] p_twi_sensor Pointer to sensor common instance.
 *
 * @return Error code from nrf_balloc @ref nrf_balloc_init
 */
ret_code_t nrf_twi_sensor_init(nrf_twi_sensor_t * p_twi_sensor);

/**
 * @brief Function for reading sensor register.
 *
 * @param[in]  p_instance       Pointer to sensor instance.
 * @param[in]  sensor_addr      Sensor address.
 * @param[in]  reg_address      Register address.
 * @param[in]  user_cb          User callback.
 * @param[out] p_data           Pointer to data save location.
 * @param[in]  length           Number of bytes to read.
 *
 * @retval NRF_ERROR_NO_MEM         If there is no memory in sensor buffer
 * @retval NRF_SUCCESS              If the operation was successful.
 * @retval other                    Error code from TWI manager @ref nrf_twi_mngr_schedule.
 */
ret_code_t nrf_twi_sensor_reg_read(nrf_twi_sensor_t const * p_instance,
                                   uint8_t                  sensor_addr,
                                   uint8_t                  reg_address,
                                   nrf_twi_sensor_reg_cb_t  user_cb,
                                   uint8_t *                p_data,
                                   uint8_t                  length);

/**
 * @brief Function for writing to sensor.
 *
 * @param[in] p_instance    Pointer to sensor instance.
 * @param[in] sensor_addr   Sensor address.
 * @param[in] p_data        Pointer to data to be written.
 * @param[in] length        Number of bytes to write.
 * @param[in] copy_flag     If true, p_data is copied into internal static buffer.
 *
 * @note   Most of the time, to write to sensors register, first byte in p_data has to be
 *         register address.
 *
 * @retval NRF_ERROR_NO_MEM         If there is no memory in sensor buffer
 * @retval NRF_ERROR_INVALID_LENGTH If trying to copy more bytes than
 *                                  NRF_TWI_SENSOR_SEND_BUF_SIZE.
 * @retval NRF_SUCCESS              If the operation was successful.
 * @retval other                    Error code from TWI manager @ref nrf_twi_mngr_schedule.
 */
ret_code_t nrf_twi_sensor_write(nrf_twi_sensor_t const * p_instance,
                                uint8_t                  sensor_addr,
                                uint8_t const *          p_data,
                                uint8_t                  length,
                                bool                     copy_flag);
                                
/**
 * @brief Function for writing to sensor register.
 *
 * @param[in] p_instance    Pointer to sensor instance.
 * @param[in] sensor_addr   Sensor address.
 * @param[in] reg_address   Register address.
 * @param[in] p_data        Pointer to data to be written.
 * @param[in] length        Number of bytes to write.
 *
 * @note   Data is copied into internal buffer.
 *         Length has to be less than NRF_TWI_SENSOR_SEND_BUF_SIZE.
 *
 * @retval NRF_ERROR_NO_MEM         If there is no memory in sensor buffer
 * @retval NRF_ERROR_INVALID_LENGTH If trying to copy more bytes than
 *                                  NRF_TWI_SENSOR_SEND_BUF_SIZE - 1.
 *                                  One byte reserved for register address.
 * @retval NRF_SUCCESS              If the operation was successful.
 * @retval other                    Error code from TWI manager @ref nrf_twi_mngr_schedule.
 */
ret_code_t nrf_twi_sensor_reg_write(nrf_twi_sensor_t const * p_instance,
                                    uint8_t                  sensor_addr,
                                    uint8_t                  reg_address,
                                    uint8_t *                p_data,
                                    uint8_t                  length);

/**
 * @brief Function for getting maximum utilization of sensor buffer.
 *
 * @param[in] p_twi_sensor Pointer to sensor buffer.
 *
 * @return Maximum utilization.
 */
__STATIC_INLINE uint8_t nrf_twi_sensor_max_util_get(nrf_twi_sensor_t const * p_twi_sensor);
#ifndef SUPPRESS_INLINE_IMPLEMENTATION
__STATIC_INLINE uint8_t nrf_twi_sensor_max_util_get(nrf_twi_sensor_t const * p_twi_sensor)
{
    return nrf_balloc_max_utilization_get(p_twi_sensor->p_pool);
}
#endif //SUPPRESS_INLINE_IMPLEMENTATION

#ifdef __cplusplus
}
#endif

#endif // NRF_SENSOR_COMMON_H

/** @} */
