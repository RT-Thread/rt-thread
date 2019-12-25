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

#ifndef LPS22HB_INTERNAL_H
#define LPS22HB_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

#define LPS22HB_BYTES_PER_SAMPLE        5

/**
 * @brief LPS22HB sensor registers.
 */
#define LPS22HB_REG_INTERRUPT_CONFIG    0x0B
#define LPS22HB_REG_THS_P_L             0x0C
#define LPS22HB_REG_THS_P_H             0x0D
#define LPS22HB_REG_WHO_AM_I            0x0F
#define LPS22HB_REG_CTRL1               0x10
#define LPS22HB_REG_CTRL2               0x11
#define LPS22HB_REG_CTRL3               0x12
#define LPS22HB_REG_FIFO_CTRL           0x14
#define LPS22HB_REG_REF_P_XL            0x15
#define LPS22HB_REG_REF_P_L             0x16
#define LPS22HB_REG_REF_P_H             0x17
#define LPS22HB_REG_RPDS_L              0x18
#define LPS22HB_REG_RPDS_H              0x19
#define LPS22HB_REG_RES_CONF            0x1A
#define LPS22HB_REG_INT_SOURCE          0x25
#define LPS22HB_REG_FIFO_STATUS         0x26
#define LPS22HB_REG_STATUS              0x27
#define LPS22HB_REG_PRESS_OUT_XL        0x28
#define LPS22HB_REG_PRESS_OUT_L         0x29
#define LPS22HB_REG_PRESS_OUT_H         0x2A
#define LPS22HB_REG_TEMP_OUT_L          0x2B
#define LPS22HB_REG_TEMP_OUT_H          0x2C
#define LPS22HB_REG_LPFP_RES            0x33
/**
 * @brief Interrupt config register bitmasks.
 */

// Bitmasks for AUTORIFP.
#define LPS22HB_AUTORIFP_POS            7
#define LPS22HB_AUTORIFP_MASK           (1 << LPS22HB_AUTORIFP_POS)

// Bitmasks for RESET_ARP.
#define LPS22HB_RESET_ARP_POS           6
#define LPS22HB_RESET_ARP_MASK          (1 << LPS22HB_RESET_ARP_POS)

// Bitmasks for AUTOZERO.
#define LPS22HB_AUTOZERO_POS            5
#define LPS22HB_AUTOZERO_MASK           (1 << LPS22HB_AUTOZERO_POS)

// Bitmasks for RESET_AZ.
#define LPS22HB_RESET_AZ_POS            4
#define LPS22HB_RESET_AZ_MASK           (1 << LPS22HB_RESET_AZ_POS)

// Bitmasks for DIFF_EN.
#define LPS22HB_DIFF_EN_POS             3
#define LPS22HB_DIFF_EN_MASK            (1 << LPS22HB_DIFF_EN_POS)

// Bitmasks for LIR.
#define LPS22HB_LIR_POS                 2
#define LPS22HB_LIR_MASK                (1 << LPS22HB_LIR_POS)

// Bitmasks for PLE.
#define LPS22HB_PLE_POS                 1
#define LPS22HB_PLE_MASK                (1 << LPS22HB_PLE_POS)

// Bitmasks for PHE.
#define LPS22HB_PHE_POS                 0
#define LPS22HB_PHE_MASK                (1 << LPS22HB_PHE_POS)


/**
 * @brief Control register 1 bitmasks.
 */

// Register validity bitmask.
#define LPS22HB_CTRL1_VALID_MASK        0x80

// Bitmasks for ODR.
#define LPS22HB_ODR_POS                 4
#define LPS22HB_ODR_MASK                (7 << LPS22HB_ODR_POS)

// Bitmasks for EN_LPFP.
#define LPS22HB_EN_LPFP_POS             3
#define LPS22HB_EN_LPFP_MASK            (1 << LPS22HB_EN_LPFP_POS)

// Bitmasks for LPFP_CFG.
#define LPS22HB_LPFP_CFG_POS            2
#define LPS22HB_LPFP_CFG_MASK           (1 << LPS22HB_LPFP_CFG_POS)

// Bitmasks for BDU.
#define LPS22HB_BDU_POS                 1
#define LPS22HB_BDU_MASK                (1 << LPS22HB_BDU_POS)

// Bitmasks for SIM.
#define LPS22HB_SIM_POS                 0
#define LPS22HB_SIM_MASK                (1 << LPS22HB_SIM_POS)


/**
 * @brief Control register 2 bitmasks.
 */

// Register validity bitmask.
#define LPS22HB_CTRL2_VALID_MASK        0x02

// Bitmasks for BOOT.
#define LPS22HB_BOOT_POS                7
#define LPS22HB_BOOT_MASK               (1 << LPS22HB_BOOT_POS)

// Bitmasks for FIFO_EN.
#define LPS22HB_FIFO_EN_POS             6
#define LPS22HB_FIFO_EN_MASK            (1 << LPS22HB_FIFO_EN_POS)

// Bitmasks for STOP_ON_FTH.
#define LPS22HB_STOP_ON_FTH_POS         5
#define LPS22HB_STOP_ON_FTH_MASK        (1 << LPS22HB_STOP_ON_FTH_POS)

// Bitmasks for IF_ADD_INC.
#define LPS22HB_IF_ADD_INC_POS          4
#define LPS22HB_IF_ADD_INC_MASK         (1 << LPS22HB_IF_ADD_INC_POS)

// Bitmasks for I2C_DIS.
#define LPS22HB_I2C_DIS_POS             3
#define LPS22HB_I2C_DIS_MASK            (1 << LPS22HB_I2C_DIS_POS)

// Bitmasks for SWRESET.
#define LPS22HB_SWRESET_POS             2
#define LPS22HB_SWRESET_MASK            (1 << LPS22HB_SWRESET_POS)

// Bitmasks for ONE_SHOT.
#define LPS22HB_ONE_SHOT_POS            0
#define LPS22HB_ONE_SHOT_MASK           (1 << LPS22HB_ONE_SHOT_POS)


/**
 * @brief Control register 3 bitmasks.
 */

// Bitmasks for INT_H_L.
#define LPS22HB_INT_H_L_POS             7
#define LPS22HB_INT_H_L_MASK            (1 << LPS22HB_INT_H_L_POS)

// Bitmasks for PP_OD.
#define LPS22HB_PP_OD_POS               6
#define LPS22HB_PP_OD_MASK              (1 << LPS22HB_PP_OD_POS)

// Bitmasks for F_FSS5.
#define LPS22HB_F_FSS5_POS              5
#define LPS22HB_F_FSS5_MASK             (1 << LPS22HB_F_FSS5_POS)

// Bitmasks for F_FTH.
#define LPS22HB_F_FTH_POS               4
#define LPS22HB_F_FTH_MASK              (1 << LPS22HB_F_FTH_POS)

// Bitmasks for F_OVR.
#define LPS22HB_F_OVR_POS               3
#define LPS22HB_F_OVR_MASK              (1 << LPS22HB_F_OVR_POS)

// Bitmasks for DRDY.
#define LPS22HB_DRDY_POS                2
#define LPS22HB_DRDY_MASK               (1 << LPS22HB_DRDY_POS)

// Bitmasks for INT_S.
#define LPS22HB_INT_S_POS               0
#define LPS22HB_INT_S_MASK              (3 << LPS22HB_INT_S_POS)


/**
 * @brief Fifo control register bitmasks.
 */

// Bitmasks for F_MODE.
#define LPS22HB_F_MODE_POS              5
#define LPS22HB_F_MODE_MASK             (7 << LPS22HB_F_MODE_POS)

// Bitmasks for WTM
#define LPS22HB_WTM_POS                 0
#define LPS22HB_WTM_MASK                (0x1F << LPS22HB_WTM_POS)


/**
 * @brief Low power mode register bitmasks.
 */

// Register validity bitmask.
#define LPS22HB_RES_CONF_VALID_MASK     0xFE

// Bitmasks for LC_EN
#define LPS22HB_LC_EN_POS               0
#define LPS22HB_LC_EN_MASK              (1 << LPS22HB_LC_EN_POS)


/**
 * @brief INT source register bitmasks.
 */

// Bitmasks for IA
#define LPS22HB_IA_POS                  2
#define LPS22HB_IA_MASK                 (1 << LPS22HB_IA_POS)

// Bitmasks for PL
#define LPS22HB_PL_POS                  1
#define LPS22HB_PL_MASK                 (1 << LPS22HB_PL_POS)

// Bitmasks for PH
#define LPS22HB_PH_POS                  0
#define LPS22HB_PH_MASK                 (1 << LPS22HB_PH_POS)


/**
 * @brief FIFO status register bitmasks.
 */

// Bitmasks for FTH_FIFO
#define LPS22HB_FTH_FIFO_POS            7
#define LPS22HB_FTH_FIFO_MASK           (1 << LPS22HB_FTH_FIFO_POS)

// Bitmasks for OVR
#define LPS22HB_OVR_POS                 6
#define LPS22HB_OVR_MASK                (1 << LPS22HB_OVR_POS)

// Bitmasks for stored data level
#define LPS22HB_FSS_POS                 0
#define LPS22HB_FSS_MASK                (0x3F << LPS22HB_FSS_POS)


/**
 * @brief Status register bitmasks.
 */

// Bitmasks for T_OR.
#define LPS22HB_T_OR_POS                5
#define LPS22HB_T_OR_MASK               (1 << LPS22HB_T_OR_POS)

// Bitmasks for P_OR.
#define LPS22HB_P_OR_POS                4
#define LPS22HB_P_OR_MASK               (1 << LPS22HB_P_OR_POS)

// Bitmasks for T_DA.
#define LPS22HB_T_DA_POS                1
#define LPS22HB_T_DA_MASK               (1 << LPS22HB_T_DA_POS)

// Bitmasks for P_DA.
#define LPS22HB_P_DA_POS                0
#define LPS22HB_P_DA_MASK               (1 << LPS22HB_P_DA_POS)

/**
 * @brief Config registers defaults.
 */
#define LPS22HB_CTRL_REG2_DEFAULT       0x10

/**
 * @brief Raw pressure and temperature data.
 *
 * @note  For internal use only.
 */
typedef struct
{
    uint8_t press_out_xl;
    uint8_t press_out_l;
    uint8_t press_out_h;
    uint8_t temp_out_l;
    uint8_t temp_out_h;
} lps22hb_raw_data_t;

/**
 * @brief Structure holding sensor instance
 *
 * @note  For internal use only.
 */
typedef struct
{
    nrf_twi_sensor_t * const p_sensor_data;
    uint8_t const            sensor_addr;

    uint8_t interrupt_cfg;
    uint8_t ctrl_reg[3];
    uint8_t fifo_ctrl;
} lps22hb_instance_t;

#define LPS22HB_INTERNAL_INSTANCE_DEF(_lps22hb_inst_name, _p_twi_sensor, _sensor_address)          \
    static lps22hb_instance_t _lps22hb_inst_name =                                                 \
    {                                                                                              \
        .p_sensor_data = _p_twi_sensor,                                                            \
        .sensor_addr   = _sensor_address,                                                          \
    }

#define LPS22HB_INTERNAL_INT_CFG(_s, _diff_en, _lir, _ple, _phe)                                   \
    NRF_TWI_SENSOR_REG_SET(_s.interrupt_cfg, LPS22HB_DIFF_EN_MASK, LPS22HB_DIFF_EN_POS, _diff_en); \
    NRF_TWI_SENSOR_REG_SET(_s.interrupt_cfg, LPS22HB_LIR_MASK, LPS22HB_LIR_POS, _lir);             \
    NRF_TWI_SENSOR_REG_SET(_s.interrupt_cfg, LPS22HB_PLE_MASK, LPS22HB_PLE_POS, _ple);             \
    NRF_TWI_SENSOR_REG_SET(_s.interrupt_cfg, LPS22HB_PHE_MASK, LPS22HB_PHE_POS, _phe);

#define LPS22HB_INTERNAL_DATA_CFG(_s, _odr, _f_en, _f_cfg)                                         \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl_reg[0], LPS22HB_ODR_MASK, LPS22HB_ODR_POS, _odr);               \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl_reg[0], LPS22HB_EN_LPFP_MASK, LPS22HB_EN_LPFP_POS, _f_en);      \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl_reg[0], LPS22HB_LPFP_CFG_MASK, LPS22HB_LPFP_CFG_POS, _f_cfg);


#define LPS22HB_INTERNAL_FIFO_CFG(_s, _f_mode, _f_en, _f_stop, _f_wtm)                             \
    NRF_TWI_SENSOR_REG_SET(_s.fifo_ctrl, LPS22HB_F_MODE_MASK, LPS22HB_F_MODE_POS, _f_mode);        \
    NRF_TWI_SENSOR_REG_SET(_s.fifo_ctrl, LPS22HB_WTM_MASK, LPS22HB_WTM_POS, _f_wtm);               \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl_reg[1], LPS22HB_FIFO_EN_MASK, LPS22HB_FIFO_EN_POS, _f_en);      \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl_reg[1],                                                         \
                           LPS22HB_STOP_ON_FTH_MASK,                                               \
                           LPS22HB_STOP_ON_FTH_POS,                                                \
                           _f_stop)

#define LPS22HB_INTERNAL_DRDY_CFG(_s, _activ, _pp_od, _fss, _fth, _ovr, _drdy, _high, _low)        \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl_reg[2], LPS22HB_INT_H_L_MASK, LPS22HB_INT_H_L_POS, _activ);     \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl_reg[2], LPS22HB_PP_OD_MASK, LPS22HB_PP_OD_POS, _pp_od);         \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl_reg[2], LPS22HB_F_FSS5_MASK, LPS22HB_F_FSS5_POS, _fss);         \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl_reg[2], LPS22HB_F_FTH_MASK, LPS22HB_F_FTH_POS, _fth);           \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl_reg[2], LPS22HB_F_OVR_MASK, LPS22HB_F_OVR_POS, _ovr);           \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl_reg[2],                                                         \
                           LPS22HB_INT_S_MASK,                                                     \
                           LPS22HB_INT_S_MASK,                                                     \
                           (_low << 1) + _high);
#ifdef __cplusplus
}
#endif

#endif // LPS22HB_INTERNAL_H
