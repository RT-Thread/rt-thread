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
#ifndef CCS811_H
#define CCS811_H

#include "nrf_twi_sensor.h"
#include "ccs811_internal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Possible sensor addresses.
 */
#define CCS811_BASE_ADDRESS_LOW         0x5AU
#define CCS811_BASE_ADDRESS_HIGH        0x5BU

// Minimum nrf_twi_sensor message buffer size and nrf_twi_mngr queue length.
#define CCS811_MIN_QUEUE_SIZE           6

// Hardware ID register value
#define CCS811_HARDWARE_ID              0x81

/**
 * @brief Sensor driver usage.
 *
 * Sensor instance has to be defined first in global context using @ref CCS811_INSTANCE_DEF.
 * After that it has to be initialized using @ref ccs811_init.
 * At this point sensor instance is ready and all other functions can be used.
 *
 * Configuration functions schedule TWI operation using @ref nrf_twi_sensor module.
 * After calling function, setting will be automatically send to sensor when TWI bus is free.
 *
 * There are designated functions to read status sensor registers e.g. @ref ccs811_status_read
 * As parameters they receive function to be called after register is read, and pointer where
 * register value should be stored. From that value specific parameters can be extracted
 * using @ref NRF_TWI_SENSOR_REG_VAL_GET macro.
 * Example:
 * bool drdy = NRF_TWI_SENSOR_REG_VAL_GET(status, CCS811_DATA_READY_MASK, CCS811_DATA_READY_POS);
 *
 * Other functions are self-explanatory or have description on their usage.
 */

/**
 * @brief Drive mode setting.
 */
typedef enum
{
    CCS811_MODE_0,//!< CCS811_MODE_0 - Idle
    CCS811_MODE_1,//!< CCS811_MODE_1 - Constant power, measure every second.
    CCS811_MODE_2,//!< CCS811_MODE_2 - Pulse heating mode, measure every 10 seconds.
    CCS811_MODE_3,//!< CCS811_MODE_3 - Low power pulse heating mode, measure every 60 seconds.
    CCS811_MODE_4 //!< CCS811_MODE_4 - Constant power, measure every 250ms, only raw data.
} ccs811_drive_mode_t;

/**
 * @brief Last byte read from algorithm data.
 *
 * Used with @ref ccs811_alg_data_read function, defines to which byte data should be read.
 */
typedef enum
{
    CCS811_LAST_ECO2 = 2,
    CCS811_LAST_TVOC = 4,
    CCS811_LAST_STATUS,
    CCS811_LAST_ERROR_ID,
    CCS811_LAST_RAW = 8
} ccs811_last_data_byte_t;

/**
 * @brief Structure for holding algorithm data.
 */
typedef struct
{
    uint16_t eco2;      //!< eC02 value in ppm.
    uint16_t tvoc;      //!< TVOC value in ppb.
    uint8_t  status;    //!< Status register data.
    uint8_t  error_id;  //!< Error register data.
    uint16_t raw;       //!< Raw data.
} ccs811_alg_data_t;

/**
 * @brief Data callback prototype.
 *
 * @param[in] result            Return code from TWI manager and underlying drivers.
 * @param[in] p_data            Pointer to sensor data.
 */
typedef void (* ccs811_data_callback_t)(ret_code_t result, ccs811_alg_data_t * p_data);

/**
 * @brief Macro that creates sensor instance.
 *
 * @param[in] _ccs811_inst_name Sensor instance name.
 * @param[in] _p_twi_sensor     Pointer to common TWI sensor instance.
 * @param[in] _sensor_address   Sensor base address.
 */
#define CCS811_INSTANCE_DEF(_ccs811_inst_name, _p_twi_sensor, _sensor_address)                    \
    CCS811_INTERNAL_INSTANCE_DEF(_ccs811_inst_name, _p_twi_sensor, _sensor_address)

/**
 * @brief Function initializing ccs811 sensor
 *
 * TWI manager queue length has to be at least CCS811_MIN_QUEUE_SIZE
 *
 * @param[in] p_instance    Pointer to sensor instance created by macro
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t ccs811_init(ccs811_instance_t const * p_instance);

/**
 * @brief Function for setting drive mode.
 *
 * @param[in] p_instance    Pointer to sensor instance.
 * @param[in] mode          Drive mode.
 * @param[in] drdy_en       Enable data ready pin.
 * @param[in] thr_en        Enable threshold.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t ccs811_drive_mode_set(ccs811_instance_t const * p_instance,
                                 ccs811_drive_mode_t       mode,
                                 bool                      drdy_en,
                                 bool                      thr_en);

/**
 * @brief Function for reading sensor data.
 *
 * @param[in]  p_instance Pointer to sensor instance.
 * @param[in]  user_cb    Function to be called after data read.
 * @param[out] p_alg_data Pointer to structure holding sensor algorithm data.
 * @param[in]  last       Last byte to read.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
ret_code_t ccs811_alg_data_read(ccs811_instance_t const * p_instance,
                                ccs811_data_callback_t    user_cb,
                                ccs811_alg_data_t *       p_alg_data,
                                ccs811_last_data_byte_t   last);

/**
 * @brief Function for processing algorithm data
 *
 * @param[in/out] p_alg_data Pointer to read data to be processed.
 */
void ccs811_alg_data_process(ccs811_alg_data_t * p_alg_data);

/**
 * @brief Function for setting environment temperature.
 *
 * @param[in] p_instance    Pointer to sensor instance.
 * @param[in] temp_value    Temperature value (-25 to 100 degree celsius).
 * @param[in] temp_fraction Temperature fraction.
 * @param[in] hum_percent   Humidity percent.
 * @param[in] hum_fraction  Humidity fraction.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t ccs811_env_set(ccs811_instance_t const * p_instance,
                          int8_t                    temp_value,
                          uint16_t                  temp_fraction,
                          uint8_t                   hum_percent,
                          uint16_t                  hum_fraction);

/**
 * @brief Function for threshold configuration
 *
 * @param[in] p_instance Pointer to sensor instance.
 * @param[in] l_to_m     Low to medium threshold.
 * @param[in] m_to_h     Medium to high threshold.
 * @param[in] hysteresis Hysteresis.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t ccs811_thr_cfg(ccs811_instance_t const * p_instance,
                          uint16_t                  l_to_m,
                          uint16_t                  m_to_h,
                          uint8_t                   hysteresis);

/**
 * @brief Function for reading baseline.
 *
 * @param[in]  p_instance Pointer to sensor instance.
 * @param[in]  user_cb    Function to be called after baseline read.
 * @param[out] baseline   Baseline value, single uint16_t.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
ret_code_t ccs811_baseline_read(ccs811_instance_t const * p_instance,
                                nrf_twi_sensor_reg_cb_t   user_cb,
                                uint16_t *                p_baseline);

/**
 * @brief Function for setting baseline.
 *
 * @param[in] p_instance Pointer to sensor instance.
 * @param[in] baseline   Baseline value.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t ccs811_baseline_set(ccs811_instance_t const * p_instance,
                               uint16_t                  baseline);

/**
 * @brief Function commencing software reset.
 *
 * @param[in] p_instance    Pointer to sensor instance.
 *
 * @note To use sensor after reset, it has to be initialized again using @ref ccs811_init function.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t ccs811_sw_reset(ccs811_instance_t const * p_instance);


/**
 * @brief Function for reading status register.
 *
 * @param[in]  p_instance Pointer to sensor instance.
 * @param[in]  user_cb    Function to be called after register is read.
 * @param[out] p_reg_val  Pointer to register value, single uint8_t.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
__STATIC_INLINE ret_code_t ccs811_status_read(ccs811_instance_t const * p_instance,
                                              nrf_twi_sensor_reg_cb_t   user_cb,
                                              uint8_t *                 p_reg_val);

/**
 * @brief Function for reading hardware id register.
 *
 * @param[in]  p_instance Pointer to sensor instance.
 * @param[in]  user_cb    Function to be called after register is read.
 * @param[out] p_reg_val  Pointer to register value, single uint8_t.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
__STATIC_INLINE ret_code_t ccs811_hw_id_read(ccs811_instance_t const * p_instance,
                                             nrf_twi_sensor_reg_cb_t   user_cb,
                                             uint8_t *                 p_reg_val);

/**
 * @brief Function for reading error id register.
 *
 * @param[in]  p_instance Pointer to sensor instance.
 * @param[in]  user_cb    Function to be called after register is read.
 * @param[out] p_reg_val  Pointer to register value, single uint8_t.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
__STATIC_INLINE ret_code_t ccs811_error_read(ccs811_instance_t const * p_instance,
                                             nrf_twi_sensor_reg_cb_t   user_cb,
                                             uint8_t *                 p_reg_val);

#ifdef __cplusplus
}
#endif

#endif // CCS811_H
