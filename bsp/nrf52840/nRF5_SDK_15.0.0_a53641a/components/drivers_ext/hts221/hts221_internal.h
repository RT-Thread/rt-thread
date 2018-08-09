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
#ifndef HTS221_INTERNAL_H
#define HTS221_INTERNAL_H


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief HTS221 sensor registers.
 */
#define HTS221_REG_WHO_AM_I             0x0F
#define HTS221_REG_AV_CONF              0x10
#define HTS221_REG_CTRL_REG1            0x20
#define HTS221_REG_CTRL_REG2            0x21
#define HTS221_REG_CTRL_REG3            0x22
#define HTS221_REG_STATUS_REG           0x27
#define HTS221_REG_HUM_OUT_L            0x28
#define HTS221_REG_HUM_OUT_H            0x29
#define HTS221_REG_TEMP_OUT_L           0x2A
#define HTS221_REG_TEMP_OUT_H           0x2B

// Calibration registers
#define HTS221_REG_CALIBRATION          0x30

#define HTS221_REG_CALIBRATION_NUM      16
#define HTS221_REG_CTRL_NUM             3

// For auto incrementing address, msb in register address must be set to 1.
#define HTS221_INCR_REG_MASK            0x80

/**
 * @brief AV_CONF register bitmasks.
 */
#define HTS221_DEF_AV_CONF              0x1B

// Register validity bitmask.
#define HTS221_AV_CONF_VALID_MASK       0xC0

// Bitmasks for AVGT.
#define HTS221_AVGT_POS                 3
#define HTS221_AVGT_MASK                (7 << HTS221_AVGT_POS)

// Bitmasks for AVGH.
#define HTS221_AVGH_POS                 0
#define HTS221_AVGH_MASK                (7 << HTS221_AVGH_POS)


/**
 * @brief Control register 1 bitmasks.
 */

// Register validity bitmask.
#define HTS221_CTRL1_VALID_MASK         0x78

// Bitmasks for PD.
#define HTS221_PD_POS                   7
#define HTS221_PD_MASK                  (1 << HTS221_PD_POS)

// Bitmasks for BDU.
#define HTS221_BDU_POS                  2
#define HTS221_BDU_MASK                 (1 << HTS221_BDU_POS)

// Bitmasks for ODR.
#define HTS221_ODR_POS                  0
#define HTS221_ODR_MASK                 (3 << HTS221_ODR_POS)


/**
 * @brief Control register 2 bitmasks.
 */

// Register validity bitmask.
#define HTS221_CTRL2_VALID_MASK         0x7C

// Bitmasks for BOOT.
#define HTS221_BOOT_POS                 7
#define HTS221_BOOT_MASK                (1 << HTS221_BOOT_POS)

// Bitmasks for Heater.
#define HTS221_HEATER_POS               1
#define HTS221_HEATER_MASK              (1 << HTS221_HEATER_POS)

// Bitmasks for ONE_SHOT.
#define HTS221_ONE_SHOT_POS             0
#define HTS221_ONE_SHOT_MASK            (1 << HTS221_ONE_SHOT_POS)


/**
 * @brief Control register 3 bitmasks.
 */

// Register validity bitmask.
#define HTS221_CTRL3_VALID_MASK         0x3B

// Bitmasks for DRDY_H_L.
#define HTS221_DRDY_H_L_POS             7
#define HTS221_DRDY_H_L_MASK            (1 << HTS221_DRDY_H_L_POS)

// Bitmasks for PP_OD
#define HTS221_PP_OD_POS                6
#define HTS221_PP_OD_MASK               (1 << HTS221_PP_OD_POS)

// Bitmasks for DRDY_EN.
#define HTS221_DRDY_EN_POS              2
#define HTS221_DRDY_EN_MASK             (1 << HTS221_DRDY_EN_POS)


/**
 * @brief Status register bitmasks.
 */

// Bitmasks for H_DA.
#define HTS221_H_DA_POS                 1
#define HTS221_H_DA_MASK                (1 << HTS221_H_DA_POS)

// Bitmasks for T_DA
#define HTS221_T_DA_POS                 0
#define HTS221_T_DA_MASK                (1 << HTS221_T_DA_POS)


/**
 * @brief Structure holding calibration information.
 */
typedef struct
{
    uint8_t  H0_rH_x2;
    uint8_t  H1_rH_x2;
    uint16_t T0_degC_x8;
    uint16_t T1_degC_x8;
    int16_t  H0_T0_OUT;
    int16_t  H1_T0_OUT;
    int16_t  T0_OUT;
    int16_t  T1_OUT;
    uint16_t padding; //<- Additional memory needed to store all calibration registers.
} hts221_calib_t;

/**
 * @brief Structure holding sensor instance
 */
typedef struct
{
    nrf_twi_sensor_t * const p_sensor_data;
    uint8_t const            sensor_addr;

    hts221_calib_t calib_info;
    uint8_t        ctrl_reg1;
    uint8_t        ctrl_reg2;

} hts221_instance_t;

/**
 * @brief Macro creating hts221 sensor instance.
 */
#define HTS221_INTERNAL_INSTANCE_DEF(_hts221_inst_name, _p_twi_sensor, _sensor_address)        \
    static hts221_instance_t _hts221_inst_name =                                               \
    {                                                                                          \
        .p_sensor_data = _p_twi_sensor,                                                        \
        .sensor_addr   = _sensor_address,                                                      \
    }

#ifndef SUPPRESS_INLINE_IMPLEMENTATION

__STATIC_INLINE ret_code_t hts221_who_am_i_read(hts221_instance_t *     p_instance,
                                                nrf_twi_sensor_reg_cb_t user_cb,
                                                uint8_t *               reg_val)
{
    ASSERT(p_instance != NULL);
    return nrf_twi_sensor_reg_read(p_instance->p_sensor_data,
                                   p_instance->sensor_addr,
                                   HTS221_REG_WHO_AM_I,
                                   user_cb,
                                   reg_val,
                                   1);
}

__STATIC_INLINE ret_code_t hts221_status_read(hts221_instance_t *     p_instance,
                                              nrf_twi_sensor_reg_cb_t user_cb,
                                              uint8_t *               reg_val)
{
    ASSERT(p_instance != NULL);
    return nrf_twi_sensor_reg_read(p_instance->p_sensor_data,
                                   p_instance->sensor_addr,
                                   HTS221_REG_STATUS_REG,
                                   user_cb,
                                   reg_val,
                                   1);
}

#endif //SUPPRESS_INLINE_IMPLEMENTATION

#ifdef __cplusplus
}
#endif

#endif // HTS221_INTERNAL_H
