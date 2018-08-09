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
#ifndef HTS221_H
#define HTS221_H

#include "nrf_twi_sensor.h"
#include "hts221_internal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Possible sensor addresses.
 */
#define HTS221_BASE_ADDRESS             0x5FU

// Who am I default value.
#define HTS221_WHO_AM_I                 0xBC

// Minimal TWI Manager queue size needed for sensor.
#define HTS221_MIN_QUEUE_SIZE           4

/**
 * @brief Sensor driver usage.
 *
 * Sensor instance has to be defined first in global context using @ref HTS221_INSTANCE_DEF.
 * After that it has to be initialized using @ref hts221_init.
 * At this point sensor instance is ready and all other functions can be used.
 *
 * Configuration functions schedule TWI operation using @ref nrf_twi_sensor module.
 * After calling function, setting will be automatically send to sensor when TWI bus is free.
 *
 * There are designated functions to read status sensor registers e.g. @ref hts221_status_read
 * As parameters they receive function to be called after register is read, and pointer where
 * register value should be stored. From that value specific parameters can be extracted
 * using @ref NRF_TWI_SENSOR_REG_VAL_GET macro.
 * Example:
 * uint8_t h_da = NRF_TWI_SENSOR_REG_VAL_GET(status, HTS221_H_DA_MASK, HTS221_H_DA_POS);
 *
 * Other functions are self-explanatory or have description on their usage.
 */

/**
 * @brief Temperature average setting.
 */

typedef enum
{
    HTS221_TEMP_SAMPLES_2,
    HTS221_TEMP_SAMPLES_4,
    HTS221_TEMP_SAMPLES_8,
    HTS221_TEMP_SAMPLES_16,
    HTS221_TEMP_SAMPLES_32,
    HTS221_TEMP_SAMPLES_64,
    HTS221_TEMP_SAMPLES_128,
    HTS221_TEMP_SAMPLES_256
} hts221_temp_avg_samples_t;

/**
 * @brief Humidity average setting.
 */
typedef enum
{
    HTS221_HUMIDITY_SAMPLES_4,
    HTS221_HUMIDITY_SAMPLES_8,
    HTS221_HUMIDITY_SAMPLES_16,
    HTS221_HUMIDITY_SAMPLES_32,
    HTS221_HUMIDITY_SAMPLES_64,
    HTS221_HUMIDITY_SAMPLES_128,
    HTS221_HUMIDITY_SAMPLES_256,
    HTS221_HUMIDITY_SAMPLES_512
} hts221_hum_avg_samples_t;

/**
 * @brief Output data rate settings.
 */
typedef enum
{
    HTS221_ODR_ONESHOT,
    HTS221_ODR_1HZ,
    HTS221_ODR_7HZ,
    HTS221_ODR_12_5HZ,
} hts221_odr_t;

/**
 * @brief Data callback prototype.
 *
 * @param[in] result            Return error code from TWI manager and underlying drivers.
 * @param[in] p_data            Pointer to sensor data.
 */
typedef void (* hts221_data_callback_t)(ret_code_t result, int16_t * p_data);

/**
 * @brief Macro creating hts221 sensor instance.
 *
 * @param[in] _hts221_inst_name Sensor instance name.
 * @param[in] _p_twi_sensor     Pointer to common TWI sensor instance. @ref NRF_TWI_SENSOR_DEF
 * @param[in] _sensor_address   Sensor base address.
 */
#define HTS221_INSTANCE_DEF(_hts221_inst_name, _p_twi_sensor, _sensor_address) \
    HTS221_INTERNAL_INSTANCE_DEF(_hts221_inst_name, _p_twi_sensor, _sensor_address)

/**
 * @brief Function initializing hts221 sensor
 *
 * Writes configuration from sensor instance into sensor.
 *
 * @param[in] p_instance Pointer to sensor instance created by macro
 *
 * @note TWI manager queue size has to be at least
 *       HTS221_MIN_QUEUE_SIZE element long.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t hts221_init(hts221_instance_t * p_instance);

/**
 * @brief Function for setting average configuration.
 *
 * @param[in] p_instance Pointer to sensor instance.
 * @param[in] temp_avg   Number of temperature average samples.
 * @param[in] hum_avg    Number of humidity average samples.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t hts221_avg_cfg(hts221_instance_t *       p_instance,
                          hts221_temp_avg_samples_t temp_avg,
                          hts221_hum_avg_samples_t  hum_avg);

/**
 * @brief Function for setting power down mode
 *
 * @param[in] p_instance    Pointer to sensor instance.
 * @param[in] enable        True if device is powered, false if power down.
 *
 * @note    Changes made by this function don't take effect before @ref hts221_cfg_commit
 */
ret_code_t hts221_pd_enable(hts221_instance_t * p_instance, bool enable);

/**
 * @brief Function for rebooting sensor.
 *
 * @param[in] p_instance    Pointer to sensor instance.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t hts221_boot(hts221_instance_t * p_instance);

/**
 * @brief Function for setting heater.
 *
 * @param[in] p_instance    Pointer to sensor instance.
 * @param[in] enable        True if heater is on.
 *
 * @note    Changes made by this function don't take effect before @ref hts221_cfg_commit
 */
ret_code_t hts221_heater_enable(hts221_instance_t * p_instance, bool enable);

/**
 * @brief Function for setting one shot mode
 *
 * @param[in] p_instance    Pointer to sensor instance.
 * @param[in] enable        True if one shot mode is on.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t hts221_oneshot(hts221_instance_t * p_instance);

/**
 * @brief Function for setting sensor_data ready output signal.
 *
 * @param[in] p_instance    Pointer to sensor instance.
 * @param[in] active_low    True if active low, false if active high.
 * @param[in] open_drain    True if open drain, false if push-pull.
 * @param[in] drdy_enable   True if pin is enabled.
 *
 * @note    Changes made by this function don't take effect before @ref hts221_cfg_commit
 */
ret_code_t hts221_drdy_pin_cfg(hts221_instance_t * p_instance,
                               bool                active_low,
                               bool                operation,
                               bool                drdy_enable);

/**
 * @brief Function for setting output data rate.
 *
 * @param[in] p_instance    Pointer to sensor instance.
 * @param[in] odr           Desired output data rate.
 *
 * @note    Changes made by this function don't take effect before @ref hts221_cfg_commit
 */
ret_code_t hts221_data_rate_cfg(hts221_instance_t * p_instance, hts221_odr_t odr);

/**
 * @brief Function for reading sensors temperature.
 *
 * @param[in]  p_instance    Pointer to sensor instance.
 * @param[in]  user_callback Function to be called when sensor data is gathered.
 * @param[out] p_temp        Pointer for raw temperature value, single int16_t.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
ret_code_t hts221_temp_read(hts221_instance_t *       p_instance,
                            hts221_data_callback_t    user_callback,
                            int16_t *                 p_temp);

/**
 * @brief Function for calculating temperature based on sensors calibration data.
 *
 * @param[in]  p_instance   Pointer to sensor instance.
 * @param[in]  raw_temp     Raw temperature in.
 *
 * @return                  Temperature * 8
 */
int16_t hts221_temp_process(hts221_instance_t * p_instance, int16_t raw_temp);

/**
 * @brief Function for reading sensors humidity.
 *
 * @param[in]  p_instance    Pointer to sensor instance.
 * @param[in]  user_callback Function to be called when data is gathered.
 * @param[out] p_hum         Pointer for raw humidity value, single int16_t.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
ret_code_t hts221_hum_read(hts221_instance_t *       p_instance,
                           hts221_data_callback_t    user_callback,
                           int16_t *                 p_hum);

/**
 * @brief Function for calculating humidity based on sensors calibration data.
 *
 * @param[in]  p_instance   Pointer to sensor instance.
 * @param[in]  raw_hum      Raw humidity in.
 *
 * @return                  Humidity * 2
 */
int16_t hts221_hum_process(hts221_instance_t * p_instance, int16_t raw_hum);

/**
 * @brief Function for reading WHO_AM_I register.
 *
 * @param[in]  p_instance Pointer to sensor instance.
 * @param[in]  user_cb    Function to be called after register is read.
 * @param[out] reg_val    Register value, single uint8_t.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
__STATIC_INLINE ret_code_t hts221_who_am_i_read(hts221_instance_t *     p_instance,
                                                nrf_twi_sensor_reg_cb_t user_cb,
                                                uint8_t *               reg_val);

/**
 * @brief Function for reading status register.
 *
 * @param[in]  p_instance Pointer to sensor instance.
 * @param[in]  user_cb    Function to be called after register is read.
 * @param[out] reg_val    Register value, single uint8_t.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
__STATIC_INLINE ret_code_t hts221_status_read(hts221_instance_t *     p_instance,
                                              nrf_twi_sensor_reg_cb_t user_cb,
                                              uint8_t *               reg_val);


#ifdef __cplusplus
}
#endif

#endif // HTS221_H
