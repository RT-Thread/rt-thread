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

#ifndef LPS22HB_H
#define LPS22HB_H

#include "nrf_twi_sensor.h"
#include "lps22hb_internal.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Possible sensor addresses.
 */
#define LPS22HB_BASE_ADDRESS_LOW        0x5CU
#define LPS22HB_BASE_ADDRESS_HIGH       0x5DU

// WHO_AM_I register value
#define LPS22HB_WHO_AM_I                0xB1

// Minimum nrf_twi_sensor message buffer size and nrf_twi_mngr queue length.
#define LPS22HB_MIN_QUEUE_SIZE          4

/**
 * @brief Sensor driver usage.
 *
 * Sensor instance has to be defined first in global context using @ref LPS22HB_INSTANCE DEF.
 * After that it has to be initialized using @ref lps22hb_init.
 * At this point sensor instance is ready and all other functions can be used.
 *
 * There are two ways in which sensor settings are set:
 *
 * First one are asynchronous macros, using them does not change real sensor settings
 * until @ref lps22hb_cfg_commit is called.
 * Example:
 * LPS22HB_DATA_CFG(m_sensor1, LPS22HB_ODR_POWERDOWN, false, false);
 * LPS22HB_FIFO_CFG(m_sensor1, LPS22HB_STREAM, true, false, 15);
 * lps22hb_cfg_commit(&m_sensor1);
 *
 * Second way are functions, functions schedule TWI operation using @ref nrf_twi_sensor module.
 * After calling function, setting will be automatically send to sensor when TWI bus is free.
 * Example:
 * lps22hb_low_power_enable(&m_sensor1, true);
 * lps22hb_offset_set(&m_sensor1, -27);
 *
 * There are designated functions to read status sensor registers e.g. @ref lps22hb_int_source_read
 * As parameters they receive function to be called after register is read, and pointer where
 * register value should be stored. From that value specific parameters can be extracted
 * using @ref NRF_TWI_SENSOR_REG_VAL_GET macro.
 * Example:
 * uint8_t ia = NRF_TWI_SENSOR_REG_VAL_GET(int_source_reg, LPS22HB_IA_MASK, LPS22HB_IA_POS);
 *
 * Other functions are self-explanatory or have description on their usage.
 */


/**
 * @brief Output data rate settings.
 */
typedef enum
{
    LPS22HB_ODR_POWERDOWN,
    LPS22HB_ODR_1HZ,
    LPS22HB_ODR_10HZ,
    LPS22HB_ODR_25HZ,
    LPS22HB_ODR_50HZ,
    LPS22HB_ODR_75HZ
} lps22hb_odr_t;

/**
 * @brief Fifo mode settings.
 */
typedef enum
{
    LPS22HB_BYPASS,
    LPS22HB_FIFO,
    LPS22HB_STREAM,
    LPS22HB_STREAM_TO_FIFO,
    LPS22HB_BYPASS_TO_STREAM,
    LPS22HB_RESERVED_FIFO,
    LPS22HB_DYNAMIC_STREAM,
    LPS22HB_BYPASS_TO_FIFO
} lps22hb_fifo_mode_t;

/**
 * @brief Low pass filter configuration.
 */
typedef enum
{
    LPS22HB_LPFP_DISABLE = 1,
    LPS22HB_LPFP_ODR_DIV_9,
    LPS22HB_LPFP_ODR_DIV_20
} lps22hb_lpfp_t;

/**
 * @brief Pressure and temperature output data.
 *
 * @note  To get pressure in hPa it has to be divided by 4096.
 *        To get temperature in degrees it has to be divided by 100.
 */
typedef struct
{
    int32_t pressure;
    int16_t temperature;
} lps22hb_data_t;

/**
 * @brief Data callback prototype.
 *
 * @param[in] result      Result of operation (NRF_SUCCESS on success,
 *                        otherwise a relevant error code).
 * @param[in] p_raw_data  Pointer to raw sensor data structure.
 */

typedef void (* lps22hb_data_callback_t)(ret_code_t result, lps22hb_data_t * p_raw_data);


/**
 * @brief Macro creating lps22hb sensor instance.
 *
 * @param[in] _lps22hb_inst_name    Sensor instance name.
 * @param[in] _p_twi_sensor         Pointer to common TWI sensor instance.
 * @param[in] _sensor_address       Sensor base address.
 */
#define LPS22HB_INSTANCE_DEF(_lps22hb_inst_name, _p_twi_sensor, _sensor_address)                \
    LPS22HB_INTERNAL_INSTANCE_DEF(_lps22hb_inst_name, _p_twi_sensor, _sensor_address)

/**
 * ===============================================================================================
 * @brief Sensor configuration macros.
 *
 * @note  After setting configuration using these macros, it has to be committed to sensor
 *        using @ref lps22hb_cfg_commit
 */

/**
 * @brief Macro for interrupt configuration.
 *
 * @param[in] _s       Sensor instance.
 * @param[in] _diff_en Enable interrupt generation. True if enabled.
 * @param[in] _lir     Latch interrupt request to INT_SOURCE register. True if enabled.
 * @param[in] _ple     Enable interrupt generation on pressure low event. True if enabled.
 * @param[in] _phe     Enable interrupt generation on pressure high event. True if enabled.
 */
#define LPS22HB_INT_CFG(_s, _diff_en, _lir, _ple, _phe)\
    LPS22HB_INTERNAL_INT_CFG(_s, _diff_en, _lir, _ple, _phe)
/**
 * @brief Macro for data acquisition configuration.
 *
 * @param[in] _s     Sensor instance.
 * @param[in] _odr   Desired output data rate. @ref lps22hb_odr_t
 * @param[in] _f_en  Enables filter. True if enabled.
 * @param[in] _f_cfg Filter configuration.
 * @arg       true   Filter bandwidth is ODR/20
 * @arg       false  Filter bandwidth is ODR/9
 */
#define LPS22HB_DATA_CFG(_s, _odr, _f_en, _f_cfg)\
    LPS22HB_INTERNAL_DATA_CFG(_s, _odr, _f_en, _f_cfg)

/**
 * @brief Macro for FIFO configuration.
 *
 * @param[in] _s      Sensor instance.
 * @param[in] _f_mode FIFO mode. @ref lps22hb_fifo_mode_t
 * @param[in] _f_en   Enable FIFO. True if enabled.
 * @param[in] _f_stop Stop on FIFO watermark. True if enabled.
 * @param[in] _f_wtm  FIFO watermark value. Between 0 and 31.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
#define LPS22HB_FIFO_CFG(_s, _f_mode, _f_en, _f_stop, _f_wtm)\
    LPS22HB_INTERNAL_FIFO_CFG(_s, _f_mode, _f_en, _f_stop, _f_wtm)

/**
 * @brief Macro for INT_DRDY pin configuration.
 * @param[in] _s     Sensor instance.
 * @param[in] _activ Active state.
 * @arg       true   Active low.
 * @arg       false  Active high.
 * @param[in] _pp_od Pin operation.
 * @arg       true   Open drain.
 * @arg       false  Push-pull.
 * @param[in] _fss   FIFO full flag. True if enabled.
 * @param[in] _fth   FIFO watermark status. True if enabled.
 * @param[in] _ovr   FIFO overrun interrupt. True if enabled.
 * @param[in] _drdy  Data Ready signal. True if enabled.
 * @param[in] _high  Pressure higher than interrupt threshold. True if enabled.
 * @param[in] _low   Pressure lower than interrupt threshold. True if enabled.
 */
#define LPS22HB_DRDY_CFG(_s, _activ, _pp_od, _fss, _fth, _ovr, _drdy, _high, _low)\
    LPS22HB_INTERNAL_DRDY_CFG(_s, _activ, _pp_od, _fss, _fth, _ovr, _drdy, _high, _low)
/**
 * ===============================================================================================
 */


/**
 * @brief Function for initializing lps22hb sensor.
 *
 * Writes configuration data in sensor instance to sensor.
 *
 * @param[in] p_instance    Pointer to sensor instance created by macro
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t lps22hb_init(lps22hb_instance_t * p_instance);

/**
 * @brief Function for enabling autorifp.
 *
 * @param[in] p_instance Pointer to sensor instance
 * @param[in] enable     Autorifp setting.
 * @arg       true       Autorifp is enabled.
 * @arg       false      Autorifp is disabled and reset.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t lps22hb_autorifp_enable(lps22hb_instance_t * p_instance, bool enable);

/**
 * @brief Function for enabling autozero.
 *
 * @param[in] p_instance Pointer to sensor instance
 * @param[in] enable     Autozero setting.
 * @arg       true       Autozero is enabled.
 * @arg       false      Autozero is disabled and reset.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t lps22hb_autozero_enable(lps22hb_instance_t * p_instance, bool enable);

/**
 * @brief Function performing software reset.
 *
 * @param[in] p_instance    Pointer to sensor instance.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t lps22hb_sw_reset(lps22hb_instance_t * p_instance);

/**
 * @brief Function performing boot.
 *
 * @param[in] p_instance    Pointer to sensor instance.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t lps22hb_boot(lps22hb_instance_t * p_instance);

/**
 * @brief Function setting oneshot.
 *
 * @param[in] p_instance    Pointer to sensor instance.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t lps22hb_oneshot(lps22hb_instance_t * p_instance);

/**
 * @brief Function for reading pressure and temperature data.
 *
 * @param[in]  p_instance    Pointer to sensor instance.
 * @param[in]  user_callback Function to be called when data is gathered.
 * @param[out] p_out_data    Pointer to raw data buffer.
 * @param[in]  samples       Number of data samples to read.
 *
 * @note Data can be read in two ways. With or without sensors FIFO.
 *       FIFO mode depends on FIFO mode set using lps22hb_fifo_mode_set function.
 *       FIFO is enabled using lps22hb_fifo_enable function.
 *       Without FIFO only one sample can be acquired, p_out_data can be pointer to single variable.
 *       With FIFO enabled, data can be read in burst mode, p_out_data table has to be same
 *       or bigger than number of samples to read.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
ret_code_t lps22hb_data_read(lps22hb_instance_t *       p_instance,
                             lps22hb_data_callback_t    user_callback,
                             lps22hb_data_t *           p_out_data,
                             uint8_t                    samples);

/**
 * @brief Function for converting raw sensor data to real.
 *
 * @param[in/out] p_data    Pointer to data to be processed.
 * @param[in]     samples   Number of samples to be processed.
 *
 * @note After data is processed, structure contains pressure in hPa*4096
 *       and temperature in Celsius degrees*100
 */
void lps22hb_data_decode(lps22hb_data_t * p_data, uint8_t samples);

/**
 * @brief Function for setting reference pressure.
 *
 * @param[in] p_instance    Pointer to sensor instance.
 * @param[in] pressure      Reference pressure in hPa*4096
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t lps22hb_ref_pressure_set(lps22hb_instance_t * p_instance, int32_t pressure);

/**
 * @brief Function for setting pressure offset.
 *
 * @param[in] p_instance    Pointer to sensor instance.
 * @param[in] offset        Pressure offset in hPa.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t lps22hb_offset_set(lps22hb_instance_t * p_instance, int16_t offset);

/**
 * @brief Function for setting interrupt threshold.
 *
 * @param[in] p_instance    Pointer to sensor instance.
 * @param[in] threshold     Interrupt threshold in hPa.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t lps22hb_threshold_set(lps22hb_instance_t * p_instance, uint16_t threshold);

/**
 * @brief Function for enabling low power mode.
 *
 * @param[in] p_instance Pointer to sensor instance.
 * @param[in] enable     Enable low power mode. True if enabled.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t lps22hb_low_power_enable(lps22hb_instance_t * p_instance, bool enable);

/**
 * @brief Function for setting sensor configuration.
 *
 * @param[in] p_instance    Pointer to sensor instance.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t lps22hb_cfg_commit(lps22hb_instance_t * p_instance);

/**
 * @brief Function for resetting filter.
 *
 * @param[in] p_instance Pointer to sensor instance.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
__STATIC_INLINE ret_code_t lps22hb_reset_filter(lps22hb_instance_t * p_instance);

/**
 * @brief Function for reading who am i register.
 *
 * @param[in]  p_instance Pointer to sensor instance.
 * @param[in]  user_cb    Function to be called after register is read.
 * @param[out] reg_val    Register value, single uint8_t.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
__STATIC_INLINE ret_code_t lps22hb_who_am_i_read(lps22hb_instance_t *    p_instance,
                                                 nrf_twi_sensor_reg_cb_t user_cb,
                                                 uint8_t *               reg_val);

/**
 * @brief Function for reading interrupt source register.
 *
 * @param[in]  p_instance Pointer to sensor instance.
 * @param[in]  user_cb    Function to be called after register is read.
 * @param[out] reg_val    Register value, single uint8_t.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
__STATIC_INLINE ret_code_t lps22hb_int_source_read(lps22hb_instance_t *    p_instance,
                                                   nrf_twi_sensor_reg_cb_t user_cb,
                                                   uint8_t *               reg_val);

/**
 * @brief Function for reading fifo status register.
 *
 * @param[in]  p_instance Pointer to sensor instance.
 * @param[in]  user_cb    Function to be called after register is read.
 * @param[out] reg_val    Register value, single uint8_t.
 *
 * @return Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
__STATIC_INLINE ret_code_t lps22hb_fifo_status_read(lps22hb_instance_t *    p_instance,
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
__STATIC_INLINE ret_code_t lps22hb_status_read(lps22hb_instance_t *    p_instance,
                                               nrf_twi_sensor_reg_cb_t user_cb,
                                               uint8_t *               reg_val);

#ifndef SUPPRESS_INLINE_IMPLEMENTATION

__STATIC_INLINE ret_code_t lps22hb_reset_filter(lps22hb_instance_t * p_instance)
{
    ASSERT(p_instance != NULL);
    static uint8_t temp;
    return nrf_twi_sensor_reg_read(p_instance->p_sensor_data,
                                   p_instance->sensor_addr,
                                   LPS22HB_REG_LPFP_RES,
                                   NULL,
                                   &temp,
                                   1);
}

__STATIC_INLINE ret_code_t lps22hb_who_am_i_read(lps22hb_instance_t *    p_instance,
                                                 nrf_twi_sensor_reg_cb_t user_cb,
                                                 uint8_t *               reg_val)
{
    ASSERT(p_instance != NULL);
    return nrf_twi_sensor_reg_read(p_instance->p_sensor_data,
                                   p_instance->sensor_addr,
                                   LPS22HB_REG_WHO_AM_I,
                                   user_cb,
                                   reg_val,
                                   1);
}

__STATIC_INLINE ret_code_t lps22hb_int_source_read(lps22hb_instance_t *    p_instance,
                                                   nrf_twi_sensor_reg_cb_t user_cb,
                                                   uint8_t *               reg_val)
{
    ASSERT(p_instance != NULL);
    return nrf_twi_sensor_reg_read(p_instance->p_sensor_data,
                                   p_instance->sensor_addr,
                                   LPS22HB_REG_INT_SOURCE,
                                   user_cb,
                                   reg_val,
                                   1);
}

__STATIC_INLINE ret_code_t lps22hb_fifo_status_read(lps22hb_instance_t *    p_instance,
                                                    nrf_twi_sensor_reg_cb_t user_cb,
                                                    uint8_t *               reg_val)
{
    ASSERT(p_instance != NULL);
    return nrf_twi_sensor_reg_read(p_instance->p_sensor_data,
                                   p_instance->sensor_addr,
                                   LPS22HB_REG_FIFO_STATUS,
                                   user_cb,
                                   reg_val,
                                   1);
}

__STATIC_INLINE ret_code_t lps22hb_status_read(lps22hb_instance_t *    p_instance,
                                               nrf_twi_sensor_reg_cb_t user_cb,
                                               uint8_t *               reg_val)
{
    ASSERT(p_instance != NULL);
    return nrf_twi_sensor_reg_read(p_instance->p_sensor_data,
                                   p_instance->sensor_addr,
                                   LPS22HB_REG_STATUS,
                                   user_cb,
                                   reg_val,
                                   1);
}

#endif //SUPPRESS_INLINE_IMPLEMENTATION

#ifdef __cplusplus
}
#endif

#endif // LPS22HB_H
