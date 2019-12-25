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
#ifndef BH1745_INTERNAL_H
#define BH1745_INTERNAL_H

#include "nrf_twi_sensor.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Possible sensor addresses.
 */
#define BH1745_BASE_ADDRESS_LOW     0x38U
#define BH1745_BASE_ADDRESS_HIGH    0x39U

#define BH1745_MIN_QUEUE_SIZE       5

/**
 * @brief Sensor registers.
 */
#define BH1745_REG_SYSTEM_CONTROL   0x40
#define BH1745_REG_MODE_CONTROL1    0x41
#define BH1745_REG_MODE_CONTROL2    0x42
#define BH1745_REG_RED_DATA_LSB     0x50
#define BH1745_REG_DINT_DATA_LSB    0x58
#define BH1745_REG_INTERRUPT        0x60
#define BH1745_REG_PERSISTENCE      0x61
#define BH1745_REG_TH_LSB           0x62
#define BH1745_REG_TL_LSB           0x64
#define BH1745_REG_MANUFACTURER_ID  0x92

#define BH1745_DATA_REG_NUM         8

#define BH1745_MANU_ID              0xE0
#define BH1745_PART_ID              0x0B


/**
 * @brief System Control register bitmasks.
 */

// Default value for system control register.
#define BH1745_DEF_SYSTEM_CONTROL       0x0B

// Bitmasks for sw reset.
#define BH1745_SW_RESET_POS             7
#define BH1745_SW_RESET_MASK            (1 << BH1745_SW_RESET_POS)

// Bitmasks for int reset.
#define BH1745_INT_RESET_POS            6
#define BH1745_INT_RESET_MASK           (1 << BH1745_INT_RESET_POS)

// Bitmasks for part id.
#define BH1745_PART_ID_POS              0
#define BH1745_PART_ID_MASK             (0x3F << BH1745_PART_ID_POS)


/**
 * @brief Mode Control 1 register bitmasks.
 */

// Bitmasks for meas time.
#define BH1745_MEAS_TIME_POS            0
#define BH1745_MEAS_TIME_MASK           (0x07 << BH1745_MEAS_TIME_POS)


/**
 * @brief Mode Control 2 register bitmasks.
 */

// Bitmasks for valid.
#define BH1745_VALID_POS                7
#define BH1745_VALID_MASK               (1 << BH1745_VALID_POS)

// Bitmasks for rgbc en.
#define BH1745_RGBC_EN_POS              4
#define BH1745_RGBC_EN_MASK             (1 << BH1745_RGBC_EN_POS)

// Bitmasks for adc gain.
#define BH1745_ADC_GAIN_POS             0
#define BH1745_ADC_GAIN_MASK            (3 << BH1745_ADC_GAIN_POS)


/**
 * @brief Interrupt register bitmasks.
 */

// Bitmasks for int status.
#define BH1745_INT_STATUS_POS           7
#define BH1745_INT_STATUS_MASK          (1 << BH1745_INT_STATUS_POS)

// Bitmasks for int latch.
#define BH1745_INT_LATCH_POS            4
#define BH1745_INT_LATCH_MASK           (1 << BH1745_INT_LATCH_POS)

// Bitmasks for int source.
#define BH1745_INT_SOURCE_POS           2
#define BH1745_INT_SOURCE_MASK          (3 << BH1745_INT_SOURCE_POS)

// Bitmasks for int enable.
#define BH1745_INT_ENABLE_POS           0
#define BH1745_INT_ENABLE_MASK          (1 << BH1745_INT_ENABLE_POS)


/**
 * @brief Persistence register bitmasks.
 */

// Default value for persistence register.
#define BH1745_DEF_PERSISTENCE          0x01

// Bitmasks for persistence.
#define BH1745_PERSISTENCE_POS          0
#define BH1745_PERSISTENCE_MASK         (3 << BH1745_PERSISTENCE_POS)

// Default value for high threshold registers.
#define BH1745_DEF_TH                   0xFFFF


/**
 * @brief Sensor instance information.
 */
typedef struct
{
    nrf_twi_sensor_t * const p_sensor_data;
    uint8_t const            sensor_addr;
} bh1745_instance_t;


#define BH1745_INTERNAL_INSTANCE_DEF(_bh1745_inst_name, _p_twi_sensor, _sensor_address)         \
    static bh1745_instance_t _bh1745_inst_name =                                                \
    {                                                                                           \
        .p_sensor_data = _p_twi_sensor,                                                         \
        .sensor_addr   = _sensor_address                                                        \
    }

#ifdef __cplusplus
}
#endif

#endif // BH1745_INTERNAL_H
