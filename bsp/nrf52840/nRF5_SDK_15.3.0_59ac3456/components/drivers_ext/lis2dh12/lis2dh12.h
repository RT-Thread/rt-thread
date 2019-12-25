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
#ifndef LIS2DH12_H
#define LIS2DH12_H

#include "nrf_twi_sensor.h"
#include "lis2dh12_internal.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Possible sensor addresses.
 */
#define LIS2DH12_BASE_ADDRESS_LOW       0x18U
#define LIS2DH12_BASE_ADDRESS_HIGH      0x19U

// WHO_AM_I register value.
#define LIS2DH12_WHO_AM_I               0x33

/**
 * @brief Sensor driver usage.
 *
 * Sensor instance has to be defined first in global context using @ref LIS2DH12_INSTANCE DEF.
 * After that it has to be initialized using @ref lis2dh12_init.
 * At this point sensor instance is ready and all other functions can be used.
 *
 * Sensor settings are modified using asynchronous macros, using them does not change
 * real sensor settings until @ref lis2dh12_cfg_commit is called.
 * Example:
 * LIS2DH12_DATA_CFG(m_sensor, LIS2DH12_ODR_200HZ, false, true, true, true, LIS2DH12_SCALE_2G, 1);
 * lis2dh12_cfg_commit(&m_sensor);
 *
 * There are designated functions to read status sensor registers e.g. @ref lis2dh12_status_read
 * As parameters they receive function to be called after register is read, and pointer where
 * register value should be stored. From that value specific parameters can be extracted
 * using @ref NRF_TWI_SENSOR_REG_VAL_GET macro. For specific bitmasks, check lis2dh12_internal.h
 * Example:
 * bool zyxor = NRF_TWI_SENSOR_REG_VAL_GET(status_reg, LIS2DH12_ZYXOR_MASK, LIS2DH12_ZYXOR_POS);
 *
 * Other functions are self-explanatory or have description on their usage.
 */

/**
 * @brief Output data rate settings.
 */
typedef enum
{
    LIS2DH12_ODR_POWERDOWN,
    LIS2DH12_ODR_1HZ,
    LIS2DH12_ODR_10HZ,
    LIS2DH12_ODR_25HZ,
    LIS2DH12_ODR_50HZ,
    LIS2DH12_ODR_100HZ,
    LIS2DH12_ODR_200HZ,
    LIS2DH12_ODR_400HZ,
    LIS2DH12_ODR_1620HZ,
    LIS2DH12_ODR_1344_5376HZ
} lis2dh12_odr_t;

/**
 * @brief Fifo mode settings.
 */
typedef enum
{
    LIS2DH12_BYPASS,
    LIS2DH12_FIFO,
    LIS2DH12_STREAM,
    LIS2DH12_STREAM_TO_FIFO
} lis2dh12_fifo_mode_t;

/**
 * @brief Filter mode setting.
 */
typedef enum
{
    LIS2DH12_FILTER_MODE_NORMAL_W_RESET,
    LIS2DH12_FILTER_MODE_REFERENCE,
    LIS2DH12_FILTER_MODE_NORMAL,
    LIS2DH12_FILTER_MODE_AUTO_RESET
} lis2dh12_filter_mode_t;

/**
 * @brief Filter frequency setting.
 */
typedef enum
{
    LIS2DH12_FILTER_FREQ_1,
    LIS2DH12_FILTER_FREQ_2,
    LIS2DH12_FILTER_FREQ_3,
    LIS2DH12_FILTER_FREQ_4
} lis2dh12_filter_freq_t;

/**
 * @brief Accelerometer scale setting.
 */
typedef enum
{
    LIS2DH12_SCALE_2G,
    LIS2DH12_SCALE_4G,
    LIS2DH12_SCALE_8G,
    LIS2DH12_SCALE_16G
} lis2dh12_scale_t;

/**
 * @brief Structure containing accelerometer data.
 */
typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
} lis2dh12_data_t;

/**
 * @brief Data callback prototype.
 *
 * @param[in] result Result of operation (NRF_SUCCESS on success,
 *                   otherwise a relevant error code).
 * @param[in] p_data Pointer to raw sensor data structure.
 */
typedef void (* lis2dh12_data_cb_t)(ret_code_t result, lis2dh12_data_t * p_data);

/**
 * @brief Temperature callback prototype.
 *
 * @param[in] result Result of operation (NRF_SUCCESS on success,
 *                   otherwise a relevant error code).
 * @param[in] p_temp Temperature value.
 */
typedef void (* lis2dh12_temp_cb_t)(ret_code_t result, int16_t * p_temp);

/**
 * @brief Macro for defining sensor instance.
 *
 * @param[in] _lis2dh12_inst_name   Sensor instance name.
 * @param[in] _p_twi_sensor         Pointer to common TWI sensor instance.
 * @param[in] _sensor_address       Sensor base address.
 */
#define LIS2DH12_INSTANCE_DEF(_lis2dh12_inst_name, _p_twi_sensor, _sensor_address) \
    LIS2DH12_INTERNAL_INSTANCE_DEF(_lis2dh12_inst_name, _p_twi_sensor, _sensor_address)

/**
 * @brief Macro for setting data acquisition configuration.
 *
 * @param[in] _s        Sensor instance.
 * @param[in] _odr      Data rate. @ref lis2dh12_odr_t
 * @param[in] _lp       Power mode. True if low power mode is enabled.
 * @param[in] _z_en     Enable measure in z-axis. True if enabled.
 * @param[in] _y_en     Enable measure in y-axis. True if enabled.
 * @param[in] _x_en     Enable measure in x-axis. True if enabled.
 * @param[in] _scale    Measurement scale. @ref lis2dh12_scale_t
 * @param[in] _high_res High resolution mode. True if enabled.
 *                      Low power can't be enabled when in high resolution mode.
 */
#define LIS2DH12_DATA_CFG(_s, _odr, _lp, _z_en, _y_en, _x_en, _scale, _high_res) \
    LIS2DH12_INTERNAL_DATA_CFG(_s, _odr, _lp, _z_en, _y_en, _x_en, _scale, _high_res)

/**
 * @brief Function for setting filter configuration.
 *
 * @param[in] _s     Sensor instance.
 * @param[in] _mode  Filter mode. @ref lis2dh12_filter_mode_t
 * @param[in] _freq  Filter frequency. @ref lis2dh12_filter_freq_t
 * @param[in] _d_en  Enable filter for data acquisition.
 * @param[in] _c_en  Enable filter for click interrupt.
 * @param[in] _i1_en Enable filter for interrupt 1 aoi.
 * @param[in] _i2_en Enable filter for interrupt 2 aoi.
 */
#define LIS2DH12_FILTER_CFG(_s, _mode, _freq, _d_en, _c_en, _i1_en, _i2_en) \
    LIS2DH12_INTERNAL_FILTER_CFG(_s, _mode, _freq, _d_en, _c_en, _i1_en, _i2_en)

/**
 * @brief Macro for configuring INT1 pin.
 *
 * @param[in] _s     Sensor instance.
 * @param[in] _cl    Enable CLICK interrupt on pin.
 * @param[in] _ia1   Enable IA1 interrupt on pin.
 * @param[in] _ia2   Enable IA2 interrupt on pin.
 * @param[in] _zyxda Enable ZYXDA interrupt on pin.
 * @param[in] _wtm   Enable FIFO watermark interrupt on pin.
 * @param[in] _ovr   Enable FIFO overrun interrupt on pin.
 * @param[in] _pol   Pin active state. Affects also int2 pin.
 * @arg       true   Pin is active low.
 * @arg       false  Pin is active high
 * @param[in] _d4d   Enable 4D detection on INT1 pin when 6D is enabled on interrupt 1.
 */
#define LIS2DH12_INT1_PIN_CFG(_s, _cl, _ia1, _ia2, _zyxda, _wtm, _ovr, _pol, _d4d) \
    LIS2DH12_INTERNAL_INT1_PIN_CFG(_s, _cl, _ia1, _ia2, _zyxda, _wtm, _ovr, _pol, _d4d)

/**
 * @brief Macro for configuring INT2 pin.
 *
 * @param[in] _s     Sensor instance.
 * @param[in] _cl    Enable CLICK interrupt on pin.
 * @param[in] _ia1   Enable IA1 interrupt on pin.
 * @param[in] _ia2   Enable IA2 interrupt on pin.
 * @param[in] _boot  Enable boot on pin.
 * @param[in] _avt   Enable activity interrupt on pin.
 * @param[in] _pol   Pin active state. Affects also int1 pin.
 * @arg       true   Pin is active low.
 * @arg       false  Pin is active high
 * @param[in] _d4d   Enable 4D detection on INT2 pin when 6D is enabled on interrupt 2.
 */
#define LIS2DH12_INT2_PIN_CFG(_s, _cl, _ia1, _ia2, _boot, _act, _pol, _d4d) \
    LIS2DH12_INTERNAL_INT2_PIN_CFG(_s, _cl, _ia1, _ia2, _boot, _act, _pol, _d4d)

 /**
  * @brief Macro for configuring interrupt 1.
  *
  * @param[in] _s   Sensor instance.
  * @param[in] _thr Interrupt threshold.
  * @param[in] _dur Interrupt duration.
  * @param[in] _aoi And/Or combination of interrupt events. True if and.
  * @param[in] _6d  6-direction detection enable. True if enabled.
  * @param[in] _zh  Enable interrupt on Z high event or direction recognition.
  * @param[in] _zl  Enable interrupt on Z low event or direction recognition.
  * @param[in] _yh  Enable interrupt on Y high event or direction recognition.
  * @param[in] _yl  Enable interrupt on Y low event or direction recognition.
  * @param[in] _xh  Enable interrupt on X high event or direction recognition.
  * @param[in] _xl  Enable interrupt on X low event or direction recognition.
  * @param[in] _lir Latch interrupt 1 request. True if enabled.
  */
#define LIS2DH12_INT1_CFG(_s, _thr, _dur, _aoi, _6d, _zh, _zl, _yh, yl, _xh, _xl, _lir) \
    LIS2DH12_INTERNAL_INT1_CFG(_s, _thr, _dur, _aoi, _6d, _zh, _zl, _yh, yl, _xh, _xl, _lir)

/**
 * @brief Macro for configuring interrupt 2.
 *
 * @param[in] _s   Sensor instance.
 * @param[in] _thr Interrupt threshold.
 * @param[in] _dur Interrupt duration.
 * @param[in] _aoi And/Or combination of interrupt events. True if and.
 * @param[in] _6d  6-direction detection enable. True if enabled.
 * @param[in] _zh  Enable interrupt on Z high event or direction recognition.
 * @param[in] _zl  Enable interrupt on Z low event or direction recognition.
 * @param[in] _yh  Enable interrupt on Y high event or direction recognition.
 * @param[in] _yl  Enable interrupt on Y low event or direction recognition.
 * @param[in] _xh  Enable interrupt on X high event or direction recognition.
 * @param[in] _xl  Enable interrupt on X low event or direction recognition.
 * @param[in] _lir Latch interrupt 1 request. True if enabled.
 */
#define LIS2DH12_INT2_CFG(_s, _thr, _dur, _aoi, _6d, _zh, _zl, _yh, yl, _xh, _xl, _lir) \
    LIS2DH12_INTERNAL_INT2_CFG(_s, _thr, _dur, _aoi, _6d, _zh, _zl, _yh, yl, _xh, _xl, _lir)

/**
  * @brief Function for setting click configuration.
  *
  * @param[in] _s    Sensor instance.
  * @param[in] _zd   Enable interrupt double-click on Z-axis.
  * @param[in] _zs   Enable interrupt single-click on Z-axis.
  * @param[in] _yd   Enable interrupt double-click on Y-axis.
  * @param[in] _ys   Enable interrupt single-click on Y-axis.
  * @param[in] _xd   Enable interrupt double-click on X-axis.
  * @param[in] _xs   Enable interrupt single-click on X-axis.
  * @param[in] _lir  Keep high until CLICK_SRC is read.
  * @arg       true  Interrupt is kept high until CLICK_SRC is read.
  * @arg       false Interrupt is kept high for the duration of latency window.
  * @param[in] _ths  Click threshold.
  * @param[in] _lim  Click time limit.
  * @param[in] _ltc  Click time latency.
  * @param[in] _win  Click time window.
  */
#define LIS2DH12_CLICK_CFG(_s, _zd, _zs, _yd, _ys, _xd, _xs, _lir, _ths, _lim, _ltc, _win) \
    LIS2DH12_INTERNAL_CLICK_CFG(_s, _zd, _zs, _yd, _ys, _xd, _xs, _lir, _ths, _lim, _ltc, _win)

 /**
  * @brief Macro for setting sleep configuration.
  *
  * @param[in] _s   Sensor instance.
  * @param[in] _ths Sleep-to-wake, return-to-sleep activation threshold in low-power mode.
  * @param[in] _dur Sleep-to-wake, return-to-sleep duration.
  */
#define LIS2DH12_SLEEP_CFG(_s, _ths, _dur) \
    LIS2DH12_INTERNAL_SLEEP_CFG(_s, _ths, _dur)

/**
 * @brief Macro for setting reference value for interrupt generation.
 *
 * @param[in] _s   Sensor instance.
 * @param[in] _ref Reference value.
 */
#define LIS2DH_REF_SET(_s, _ref) \
    LIS2DH_INTERNAL_REF_SET(_s, _ref)

/**
 * @brief Macro for setting FIFO configuration.
 *
 * @param[in] _s     Sensor instance.
 * @param[in] _en    Enables FIFO. True if enabled. False clears FIFO setting.
 * @param[in] _mode  FIFO mode. @ref lis2dh12_fifo_mode_t
 * @param[in] _t_sel Trigger event pin selection. True if int2 pin, false if int1 pin.
 * @param[in] _t_thr Trigger threshold.
 */
#define LIS2DH12_FIFO_CFG(_s, _en, _mode, _t_sel, _t_thr) \
    LIS2DH12_INTERNAL_FIFO_CFG(_s, _en, _mode, _t_sel, _t_thr)

/**
 * @brief Function for initializing LIS2DH12 instance.
 *
 * @param[in] p_inst Pointer to sensor instance defined by macro. @ref LIS2DH12_INSTANCE_DEF
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t lis2dh12_init(lis2dh12_instance_t * p_inst);

/**
 * @brief Function for writing configuration to sensor.
 *
 * @param[in] p_inst Pointer to sensor instance.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t lis2dh12_cfg_commit(lis2dh12_instance_t * p_inst);

/**
 * @brief Function for reading accelerometer data.
 *
 * @param[in] p_inst  Pointer to sensor instance.
 * @param[in] user_cb Function to be called after data read is complete.
 * @param[in] p_data  Pointer to data structure.
 * @param[in] samples Number of samples to read.
 *
 * @note When trying to read more than one sample and FIFO is disabled,
 *       current output value will be copied to all read samples.
 *       When trying to read more samples than there is currently in FIFO,
 *       excess samples will be equal to 0.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
ret_code_t lis2dh12_data_read(lis2dh12_instance_t * p_inst,
                              lis2dh12_data_cb_t    user_cb,
                              lis2dh12_data_t *     p_data,
                              uint8_t               samples);

/**
 * @brief Function for enabling temperature measurement.
 *
 * @param[in] p_inst  Pointer to sensor instance.
 * @param[in] temp_en Temperature measure enable. True if enabled.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_write
 */
ret_code_t lis2dh12_temp_enable(lis2dh12_instance_t * p_inst, bool temp_en);

/**
 * @brief Function for reading temperature data.
 *
 * @param[in] p_inst  Pointer to sensor instance.
 * @param[in] user_cb Function to be called after temperature read is complete.
 * @param[in] p_temp  Temperature value. Pointer to single int16_t.
 *
 * @return  Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
ret_code_t lis2dh12_temp_read(lis2dh12_instance_t * p_inst,
                              lis2dh12_temp_cb_t    user_cb,
                              int16_t *             p_temp);

/**
 * @brief Function for reading temperature status register.
 *
 * @param[in] p_inst  Pointer to sensor instance.
 * @param[in] user_cb Function to be called after register read.
 * @param[in] p_data  Pointer to register data. Single uint8_t.
 *
 * @return    Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
__STATIC_INLINE ret_code_t lis2dh12_temp_status_read(lis2dh12_instance_t *     p_inst,
                                                     nrf_twi_sensor_reg_cb_t   user_cb,
                                                     uint8_t *                 p_data);

/**
 * @brief Function for reading WHO_AM_I register.
 *
 * @param[in] p_inst  Pointer to sensor instance.
 * @param[in] user_cb Function to be called after register read.
 * @param[in] p_data  Pointer to register data. Single uint8_t.
 *
 * @return    Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
__STATIC_INLINE ret_code_t lis2dh12_who_am_i_read(lis2dh12_instance_t *     p_inst,
                                                  nrf_twi_sensor_reg_cb_t   user_cb,
                                                  uint8_t *                 p_data);

/**
 * @brief Function for reading status register.
 *
 * @param[in] p_inst  Pointer to sensor instance.
 * @param[in] user_cb Function to be called after register read.
 * @param[in] p_data  Pointer to register data. Single uint8_t.
 *
 * @return    Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
__STATIC_INLINE ret_code_t lis2dh12_status_read(lis2dh12_instance_t *     p_inst,
                                                nrf_twi_sensor_reg_cb_t   user_cb,
                                                uint8_t *                 p_data);

/**
 * @brief Function for reading FIFO source register.
 *
 * @param[in] p_inst  Pointer to sensor instance.
 * @param[in] user_cb Function to be called after register read.
 * @param[in] p_data  Pointer to register data. Single uint8_t.
 *
 * @return    Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
__STATIC_INLINE ret_code_t lis2dh12_fifo_src_read(lis2dh12_instance_t *     p_inst,
                                                  nrf_twi_sensor_reg_cb_t   user_cb,
                                                  uint8_t *                 p_data);

/**
 * @brief Function for reading interrupt 1 source register.
 *
 * @param[in] p_inst  Pointer to sensor instance.
 * @param[in] user_cb Function to be called after register read.
 * @param[in] p_data  Pointer to register data. Single uint8_t.
 *
 * @return    Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
__STATIC_INLINE ret_code_t lis2dh12_int1_src_read(lis2dh12_instance_t *     p_inst,
                                                  nrf_twi_sensor_reg_cb_t   user_cb,
                                                  uint8_t *                 p_data);

/**
 * @brief Function for reading interrupt 2 source register.
 *
 * @param[in] p_inst  Pointer to sensor instance.
 * @param[in] user_cb Function to be called after register read.
 * @param[in] p_data  Pointer to register data. Single uint8_t.
 *
 * @return    Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
__STATIC_INLINE ret_code_t lis2dh12_int2_src_read(lis2dh12_instance_t *     p_inst,
                                                  nrf_twi_sensor_reg_cb_t   user_cb,
                                                  uint8_t *                 p_data);

/**
 * @brief Function for reading click source register.
 *
 * @param[in] p_inst  Pointer to sensor instance.
 * @param[in] user_cb Function to be called after register read.
 * @param[in] p_data  Pointer to register data. Single uint8_t.
 *
 * @return    Return error code from nrf_twi_sensor @ref nrf_twi_sensor_reg_read
 */
__STATIC_INLINE ret_code_t lis2dh12_click_src_read(lis2dh12_instance_t *     p_inst,
                                                   nrf_twi_sensor_reg_cb_t   user_cb,
                                                   uint8_t *                 p_data);

#ifdef __cplusplus
}
#endif

#endif // LIS2DH12_H
