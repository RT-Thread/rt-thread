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
#ifndef CCS811_INTERNAL_H
#define CCS811_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief CCS811 sensor registers.
 */
#define CCS811_REG_STATUS               0x00
#define CCS811_REG_MEAS_MODE            0x01
#define CCS811_REG_ALG_RESULT_DATA      0x02
#define CCS811_REG_RAW_DATA             0x03
#define CCS811_REG_ENV_DATA             0x05
#define CCS811_REG_NTC                  0x06
#define CCS811_REG_THRESHOLDS           0x10
#define CCS811_REG_BASELINE             0x11
#define CCS811_REG_HW_ID                0x20
#define CCS811_REG_HW_VER               0x21
#define CCS811_REG_FW_BOOT_VER          0x23
#define CCS811_REG_FW_APP_VER           0x24
#define CCS811_REG_ERROR_ID             0xE0
#define CCS811_REG_SW_RESET             0xFF
#define CCS811_REG_APP_START            0xF4

/**
 * @brief CCS811 Default configuration values.
 */
#define CCS811_DEFAULT_HUMIDITY         50
#define CCS811_DEFAULT_TEMPERATURE      25
#define CCS811_DEFAULT_LOW_THR          1500
#define CCS811_DEFAULT_HIGH_THR         2500
#define CCS811_DEFAULT_HYSTERESIS       50

/**
 * @brief CCS811 Environment temperature offset.
 */
#define CCS811_TEMPERATURE_OFFSET       25

/**
 * @brief Status register bitmasks.
 */

// Bitmasks for FW_MODE.
#define CCS811_FW_MODE_POS              7
#define CCS811_FW_MODE_MASK             (1 << CCS811_FW_MODE_POS)

// Bitmasks for APP_VALID.
#define CCS811_APP_VALID_POS            4
#define CCS811_APP_VALID_MASK           (1 << CCS811_APP_VALID_POS)

// Bitmasks for DATA_READY.
#define CCS811_DATA_READY_POS           3
#define CCS811_DATA_READY_MASK          (1 << CCS811_DATA_READY_POS)

// Bitmasks for ERROR.
#define CCS811_ERROR_POS                0
#define CCS811_ERROR_MASK               (1 << CCS811_ERROR_POS)


/**
 * @brief Meas mode register bitmasks.
 */

// Register validity mask.
#define CCS811_MEAS_MODE_VALID_MASK     0x83U

// Bitmasks for DRIVE_MODE.
#define CCS811_DRIVE_MODE_POS           4
#define CCS811_DRIVE_MODE_MASK          (7 << CCS811_DRIVE_MODE_POS)

// Bitmasks for INTERRUPT.
#define CCS811_INTERRUPT_POS            3
#define CCS811_INTERRUPT_MASK           (1 << CCS811_INTERRUPT_MASK)

// Bitmasks for THRESH.
#define CCS811_THRESH_POS               2
#define CCS811_THRESH_MASK              (1 << CCS811_THRESH_POS)

/**
 * @brief Algorithm results data bytes.
 */

#define CCS811_ALG_RESULT_BYTE_NUM      8
#define CCS811_ALG_ECO2_H_BYTE          0
#define CCS811_ALG_ECO2_L_BYTE          1
#define CCS811_ALG_TVOC_H_BYTE          2
#define CCS811_ALG_TVOC_L_BYTE          3
#define CCS811_ALG_STATUS_BYTE          4
#define CCS811_ALG_ERROR_BYTE           5
#define CCS811_ALG_RAW_DATA1_BYTE       6
#define CCS811_ALG_RAW_DATA2_BYTE       7

/**
 * @brief Environment data register.
 */

#define CCS811_ENV_HUMIDITY_H_BYTE      0

// Humidity percent position.
#define CCS811_ENV_HUM_PERCENT_POS      9

// Bitmasks for humidity fraction.
#define CCS811_ENV_HUM_FRACTION_MASK    (0x01FF)


// Temperature value position.
#define CCS811_ENV_TEMP_VALUE_POS       9

// Bitmasks for temperature fraction.
#define CCS811_ENV_TEMP_FRACTION_MASK   (0x01FF)


/**
 * @brief Error register.
 */

// Bitmasks for HEATER_SUPPLY
#define CCS811_ERROR_HEATER_SUPPLY_POS      5
#define CCS811_ERROR_HEATER_SUPPLY_MASK     (1 << CCS811_ERROR_HEATER_SUPPLY_POS)

// Bitmasks for HEATER_FAULT
#define CCS811_ERROR_HEATER_FAULT_POS       4
#define CCS811_ERROR_HEATER_FAULT_MASK      (1 << CCS811_ERROR_HEATER_FAULT_POS)

// Bitmasks for MAX_RESISTANCE
#define CCS811_ERROR_MAX_RESISTANCE_POS     3
#define CCS811_ERROR_MAX_RESISTANCE_MASK    (1 << CCS811_ERROR_MAX_RESISTANCE_POS)

// Bitmasks for MEASMODE_INVALID
#define CCS811_ERROR_MEAS_MODE_POS          2
#define CCS811_ERROR_MEAS_MODE_MASK         (1 CCS811_ERROR_MEAS_MODE_POS)

// Bitmasks for READ_REG
#define CCS811_ERROR_READ_REG_POS           1
#define CCS811_ERROR_READ_REG_MASK          (1 << CCS811_ERROR_READ_REG_POS)

// Bitmasks for WRITE_REG
#define CCS811_ERROR_WRITE_REG_POS          0
#define CCS811_ERROR_WRITE_REG_MASK         (1 << CCS811_ERROR_WRITE_REG_POS)

/**
 * @brief Software reset register.
 */
#define CCS811_SW_RESET_BYTE0           0x11
#define CCS811_SW_RESET_BYTE1           0xE5
#define CCS811_SW_RESET_BYTE2           0x72
#define CCS811_SW_RESET_BYTE3           0x8A

/**
 * @brief Structure holding sensor instance
 */
typedef struct
{
    nrf_twi_sensor_t * const p_sensor_data;
    uint8_t const            sensor_addr;
} ccs811_instance_t;

/**
 * @brief Macro that creates sensor instance.
 */
#define CCS811_INTERNAL_INSTANCE_DEF(_ccs811_inst_name, _p_twi_sensor, _sensor_address)           \
    static ccs811_instance_t _ccs811_inst_name =                                                  \
    {                                                                                             \
        .p_sensor_data = _p_twi_sensor,                                                           \
        .sensor_addr   = _sensor_address,                                                         \
    }

#ifndef SUPPRESS_INLINE_IMPLEMENTATION

__STATIC_INLINE ret_code_t ccs811_status_read(ccs811_instance_t const * p_instance,
                                              nrf_twi_sensor_reg_cb_t   user_cb,
                                              uint8_t *                 p_reg_val)
{
    ASSERT(p_instance != NULL);
    ASSERT(p_reg_val != NULL);
    return nrf_twi_sensor_reg_read(p_instance->p_sensor_data,
                                   p_instance->sensor_addr,
                                   CCS811_REG_STATUS,
                                   user_cb,
                                   p_reg_val,
                                   1);
}

__STATIC_INLINE ret_code_t ccs811_hw_id_read(ccs811_instance_t const * p_instance,
                                             nrf_twi_sensor_reg_cb_t   user_cb,
                                             uint8_t *                 p_reg_val)
{
    ASSERT(p_instance != NULL);
    ASSERT(p_reg_val != NULL);
    return nrf_twi_sensor_reg_read(p_instance->p_sensor_data,
                                   p_instance->sensor_addr,
                                   CCS811_REG_HW_ID,
                                   user_cb,
                                   p_reg_val,
                                   1);
}

__STATIC_INLINE ret_code_t ccs811_error_read(ccs811_instance_t const * p_instance,
                                             nrf_twi_sensor_reg_cb_t   user_cb,
                                             uint8_t *                 p_reg_val)
{
    ASSERT(p_instance != NULL);
    ASSERT(p_reg_val != NULL);
    return nrf_twi_sensor_reg_read(p_instance->p_sensor_data,
                                   p_instance->sensor_addr,
                                   CCS811_REG_ERROR_ID,
                                   user_cb,
                                   p_reg_val,
                                   1);
}

#endif //SUPPRESS_INLINE_IMPLEMENTATION

#ifdef __cplusplus
}
#endif

#endif // CCS811_INTERNAL_H
