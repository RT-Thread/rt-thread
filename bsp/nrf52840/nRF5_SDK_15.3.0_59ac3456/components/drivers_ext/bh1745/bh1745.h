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
#ifndef BH1745_H
#define BH1745_H

#include "nrf_twi_sensor.h"
#include "bh1745_internal.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Possible sensor addresses.
 */
#define BH1745_BASE_ADDRESS_LOW     0x38U
#define BH1745_BASE_ADDRESS_HIGH    0x39U

// Minimum nrf_twi_sensor message buffer size and nrf_twi_mngr queue length.
#define BH1745_MIN_QUEUE_SIZE       5

/**
 * @brief Sensor driver usage.
 *
 * Sensor instance has to be defined first in global context using @ref BH1745_INSTANCE DEF.
 * After that it has to be initialized using @ref bh1745_init.
 * At this point sensor instance is ready and all other functions can be used.
 *
 * Configuration functions schedule TWI operation using @ref nrf_twi_sensor module.
 * After calling function, setting will be automatically send to sensor when TWI bus is free.
 *
 * There are designated functions to read status sensor registers e.g. @ref bh1745_sys_ctrl_read
 * As parameters they receive function to be called after register is read, and pointer where
 * register value should be stored. From that value specific parameters can be extracted
 * using @ref NRF_TWI_SENSOR_REG_VAL_GET macro.
 * Example:
 * uint8_t part_id = NRF_TWI_SENSOR_REG_VAL_GET(sys_ctrl_reg,
 *                                              BH1745_PART_ID_MASK,
 *                                              BH1745_PART_ID_POS);
 *
 * Other functions are self-explanatory or have description on their usage.
 */


/**
 * @brief Measurement time.
 */
typedef enum
{
    BH1745_MEAS_TIME_160MS,
    BH1745_MEAS_TIME_320MS,
    BH1745_MEAS_TIME_640MS,
    BH1745_MEAS_TIME_1280MS,
    BH1745_MEAS_TIME_2560MS,
    BH1745_MEAS_TIME_5120MS
} bh1745_meas_time_t;

/**
 * @brief RGBC (red, green, blue, clear) gain setting.
 */
typedef enum
{
    BH1745_GAIN_1X,
    BH1745_GAIN_2X,
    BH1745_GAIN_16X
} bh1745_gain_t;

/**
 * @brief Persistence settings.
 */
typedef enum
{
    BH1745_TOGGLE_EACH_MEASURE,
    BH1745_UPDATE_EACH_MEASURE,
    BH1745_UPDATE_EVERY_FOURTH,
    BH1745_UPDATE_EVERY_EIGHTH
} bh1745_persistence_t;

/**
 * @brief Interrupt source settings.
 */
typedef enum
{
    BH1745_RED_CHANNEL,
    BH1745_GREEN_CHANNEL,
    BH1745_BLUE_CHANNEL,
    BH1745_CLEAR_CHANNEL
} bh1745_int_source_t;

/**
 * @brief Measurement result.
 */
typedef struct
{
    uint16_t red;   //!< Raw red color value.
    uint16_t green; //!< Raw green color value.
    uint16_t blue;  //!< Raw blue color value.
    uint16_t clear; //!< Raw clear color pass value.
    uint8_t  valid; //!< Mode control 2 register value, used for checking data validity.
} bh1745_data_t;

/**
 * @brief RGBC data callback prototype.
 *
 * @param     result      Result of operation (NRF_SUCCESS on success,
 *                        otherwise a relevant error code).
 * @param[in] p_user_data Pointer to color data structure.
 */
typedef void (* bh1745_data_callback_t)(ret_code_t result, bh1745_data_t * p_user_data);

/**
 * @brief Macro that creates sensor instance.
 *
 * @param[in] _bh1745_inst_name Sensor instance name.
 * @param[in] _p_twi_sensor     Pointer to common TWI sensor instance. @ref NRF_TWI_SENSOR_DEF
 * @param[in] _sensor_address   Sensor base address.
 */
#define BH1745_INSTANCE_DEF(_bh1745_inst_name, _p_twi_sensor, _sensor_address) \
    BH1745_INTERNAL_INSTANCE_DEF(_bh1745_inst_name, _p_twi_sensor, _sensor_address)

/**
 * @brief Function for initializing the BH1745 sensor instance.
 *
 * TWI manager queue length has to be at least BH1745_MIN_QUEUE_SIZE.
 *
 * @param[in] p_instance Pointer to the sensor instance.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t bh1745_init(bh1745_instance_t * p_instance);

/**
 * @brief Function for resetting the BH1745 registers.
 *
 * @param[in] p_instance Pointer to the sensor instance.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t bh1745_sw_reset(bh1745_instance_t * p_instance);

/**
 * @brief Function for resetting the interrupt.
 *
 * @param[in] p_instance Pointer to the sensor instance.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t bh1745_int_reset(bh1745_instance_t * p_instance);

/**
 * @brief Function for setting measurement configuration.
 *
 * @param[in] p_instance Pointer to the sensor instance.
 * @param[in] meas_time  Measurement time.
 * @param[in] enable     Enable RGBC measurements.
 * @param[in] gain       Measurement gain.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t bh1745_meas_cfg(bh1745_instance_t * p_instance,
                           bh1745_meas_time_t  meas_time,
                           bool                enable,
                           bh1745_gain_t       gain);

/**
 * @brief Function for setting interrupt configuration.
 *
 * @param p_instance  Pointer to sensor instance.
 * @param latch       INT pin latch.
 * @arg   false       INT pin is latched until INTERRUPT register is read or initialized.
 * @arg   true        INT pin is updated after each measurement.
 * @param source      Interrupt source.
 * @param enable      Enable INT pin.
 * @param persistence Set persistence.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t bh1745_int_cfg(bh1745_instance_t *  p_instance,
                          bool                 latch,
                          bh1745_int_source_t  source,
                          bool                 enable,
                          bh1745_persistence_t persistance);

/**
 * @brief Function for setting high interrupt threshold.
 *
 * @param[in] p_instance Pointer to sensor instance.
 * @param[in] threshold  Threshold value.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t bh1745_high_thr_set(bh1745_instance_t * p_instance,
                               uint16_t            threshold);

/**
 * @brief Function for setting low interrupt threshold.
 *
 * @param[in] p_instance Pointer to sensor instance.
 * @param[in] threshold  Threshold value.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t bh1745_low_thr_set(bh1745_instance_t * p_instance,
                              uint16_t            threshold);

/**
 * @brief Function for getting the BH1745 data.
 *
 * @param[in]  p_instance    Pointer to the sensor instance.
 * @param[in]  user_callback Callback function created by user.
 * @param[out] p_data        The measurement results.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
ret_code_t bh1745_data_read(bh1745_instance_t *      p_instance,
                            bh1745_data_callback_t   user_callback,
                            bh1745_data_t *          p_data);

/**
 * @brief Function for reading system control register.
 *
 * @param[in]  p_instance Pointer to sensor instance.
 * @param[in]  user_cb    Function to be called after register is read.
 * @param[out] reg_val    Register value, single uint8_t.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
__STATIC_INLINE ret_code_t bh1745_sys_ctrl_read(bh1745_instance_t *     p_instance,
                                                nrf_twi_sensor_reg_cb_t user_cb,
                                                uint8_t *               reg_val);

/**
 * @brief Function for reading interrupt register.
 *
 * @param[in]  p_instance Pointer to sensor instance.
 * @param[in]  user_cb    Function to be called after register is read.
 * @param[out] reg_val    Register value, single uint8_t.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
__STATIC_INLINE ret_code_t bh1745_interrupt_read(bh1745_instance_t *     p_instance,
                                                 nrf_twi_sensor_reg_cb_t user_cb,
                                                 uint8_t *               reg_val);

/**
 * @brief Function for reading manufacturer id register.
 *
 * @param[in]  p_instance Pointer to sensor instance.
 * @param[in]  user_cb    Function to be called after register is read.
 * @param[out] reg_val    Register value, single uint8_t.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
__STATIC_INLINE ret_code_t bh1745_manu_id_read(bh1745_instance_t *     p_instance,
                                               nrf_twi_sensor_reg_cb_t user_cb,
                                               uint8_t *               reg_val);

/**
 * @brief Function for checking if RGBC data has been updated after last configuration change.
 *
 * This function should be used in data callback.
 *
 * @param[in] p_instance Pointer to the sensor instance.
 *
 * @return True if data is valid.
 */
__STATIC_INLINE bool bh1745_is_data_valid(bh1745_data_t * p_data);

#ifndef SUPPRESS_INLINE_IMPLEMENTATION

__STATIC_INLINE ret_code_t bh1745_sys_ctrl_read(bh1745_instance_t *     p_instance,
                                                nrf_twi_sensor_reg_cb_t user_cb,
                                                uint8_t *               reg_val)
{
    ASSERT(p_instance != NULL);
    return nrf_twi_sensor_reg_read(p_instance->p_sensor_data,
                                   p_instance->sensor_addr,
                                   BH1745_REG_SYSTEM_CONTROL,
                                   user_cb,
                                   reg_val,
                                   1);
}

__STATIC_INLINE ret_code_t bh1745_interrupt_read(bh1745_instance_t *     p_instance,
                                                 nrf_twi_sensor_reg_cb_t user_cb,
                                                 uint8_t *               reg_val)
{
    ASSERT(p_instance != NULL);
    return nrf_twi_sensor_reg_read(p_instance->p_sensor_data,
                                   p_instance->sensor_addr,
                                   BH1745_REG_INTERRUPT,
                                   user_cb,
                                   reg_val,
                                   1);
}

__STATIC_INLINE ret_code_t bh1745_manu_id_read(bh1745_instance_t *     p_instance,
                                               nrf_twi_sensor_reg_cb_t user_cb,
                                               uint8_t *               reg_val)
{
    ASSERT(p_instance != NULL);
    return nrf_twi_sensor_reg_read(p_instance->p_sensor_data,
                                   p_instance->sensor_addr,
                                   BH1745_REG_MANUFACTURER_ID,
                                   user_cb,
                                   reg_val,
                                   1);
}

__STATIC_INLINE bool bh1745_is_data_valid(bh1745_data_t * p_data)
{
    return NRF_TWI_SENSOR_REG_VAL_GET(p_data->valid,
                                      BH1745_VALID_MASK,
                                      BH1745_VALID_POS);
}

#endif //SUPPRESS_INLINE_IMPLEMENTATION

#ifdef __cplusplus
}
#endif

#endif // BH1745_H
