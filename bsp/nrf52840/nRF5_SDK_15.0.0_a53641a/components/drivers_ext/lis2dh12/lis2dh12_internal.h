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
#ifndef LIS2DH12_INTERNAL_H
#define LIS2DH12_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif


#define LIS2DH12_AUTO_INCR_MASK         0x80
/**
 * @brief LIS2DH12 sensor registers.
 */
#define LIS2DH12_REG_STATUS_AUX         0x07
#define LIS2DH12_REG_OUT_TEMP_L         0x0C
#define LIS2DH12_REG_OUT_TEMP_H         0x0D
#define LIS2DH12_REG_WHO_AM_I           0x0F
#define LIS2DH12_REG_CTRL_REG0          0x1E
#define LIS2DH12_REG_TEMP_CFG_REG       0x1F
#define LIS2DH12_REG_CTRL_REG1          0x20
#define LIS2DH12_REG_CTRL_REG2          0x21
#define LIS2DH12_REG_CTRL_REG3          0x22
#define LIS2DH12_REG_CTRL_REG4          0x23
#define LIS2DH12_REG_CTRL_REG5          0x24
#define LIS2DH12_REG_CTRL_REG6          0x25
#define LIS2DH12_REG_REFERENCE          0x26
#define LIS2DH12_REG_STATUS             0x27
#define LIS2DH12_REG_OUT_X_L            0x28
#define LIS2DH12_REG_OUT_X_H            0x29
#define LIS2DH12_REG_OUT_Y_L            0x2A
#define LIS2DH12_REG_OUT_Y_H            0x2B
#define LIS2DH12_REG_OUT_Z_L            0x2C
#define LIS2DH12_REG_OUT_Z_H            0x2D
#define LIS2DH12_REG_FIFO_CTRL          0x2E
#define LIS2DH12_REG_FIFO_SRC           0x2F
#define LIS2DH12_REG_INT1_CFG           0x30
#define LIS2DH12_REG_INT1_SRC           0x31
#define LIS2DH12_REG_INT1_THS           0x32
#define LIS2DH12_REG_INT1_DURATION      0x33
#define LIS2DH12_REG_INT2_CFG           0x34
#define LIS2DH12_REG_INT2_SRC           0x35
#define LIS2DH12_REG_INT2_THS           0x36
#define LIS2DH12_REG_INT2_DURATION      0x37
#define LIS2DH12_REG_CLICK_CFG          0x38
#define LIS2DH12_REG_CLICK_SRC          0x39
#define LIS2DH12_REG_CLICK_THS          0x3A
#define LIS2DH12_REG_TIME_LIMIT         0x3B
#define LIS2DH12_REG_TIME_LATENCY       0x3C
#define LIS2DH12_REG_TIME_WINDOW        0x3D
#define LIS2DH12_REG_ACT_THS            0x3E
#define LIS2DH12_REG_ACT_DUR            0x3F


/**
 * @brief Config register defaults.
 */
#define LIS2DH12_DEF_CTRL_REG0          0x10
#define LIS2DH12_DEF_CTRL_REG1          0x07

#define LIS2DH12_BYTES_PER_SAMPLE       6
#define LIS2DH12_BYTES_PER_TEMP         2

/**
 * @brief Status reg aux bitmasks.
 */

// Bitmasks for TOR.
#define LIS2DH12_TOR_POS                6
#define LIS2DH12_TOR_MASK               (1 << LIS2DH12_TOR_POS)

// Bitmasks for TDA.
#define LIS2DH12_TDA_POS                2
#define LIS2DH12_TDA_MASK               (1 << LIS2DH12_TDA_POS)


/**
 * @brief Control register 0 bitmasks
 */
#define LIS2DH12_CTRL_REG0_VALID_MASK   0x7F
#define LIS2DH12_CTRL_REG0_VALID_SET    0x10

// Bitmasks for SDO_PU_DISC.
#define LIS2DH12_SDO_PU_DISC_POS        7
#define LIS2DH12_SDO_PU_DISC_MASK       (1 << LIS2DH12_SDO_PU_DISC_POS)


/**
 * @brief Temp config register bitmasks
 */
#define LIS2DH12_TEMP_CONF_VALID_MASK   0x3F

// Bitmasks for TEMP_EN
#define LIS2DH12_TEMP_EN_POS            6
#define LIS2DH12_TEMP_EN_MASK           (3 << LIS2DH12_TEMP_EN_POS)


/**
 * @brief Control register 1 bitmasks
 */

// Bitmasks for ODR.
#define LIS2DH12_ODR_POS                4
#define LIS2DH12_ODR_MASK               (0x0F << LIS2DH12_ODR_POS)

// Bitmasks for LP_EN
#define LIS2DH12_LP_EN_POS              3
#define LIS2DH12_LP_EN_MASK             (1 << LIS2DH12_LP_EN_POS)

// Bitmasks for Z_EN
#define LIS2DH12_Z_EN_POS               2
#define LIS2DH12_Z_EN_MASK              (1 << LIS2DH12_Z_EN_POS)

// Bitmasks for Y_EN
#define LIS2DH12_Y_EN_POS               1
#define LIS2DH12_Y_EN_MASK              (1 << LIS2DH12_Y_EN_POS)

// Bitmasks for X_EN
#define LIS2DH12_X_EN_POS               0
#define LIS2DH12_X_EN_MASK              (1 << LIS2DH12_X_EN_POS)


/**
 * @brief Control register 2 bitmasks.
 */

// Bitmasks for HPM.
#define LIS2DH12_HPM_POS                6
#define LIS2DH12_HPM_MASK               (3 << LIS2DH12_HPM_POS)

// Bitmasks for HPCF.
#define LIS2DH12_HPCF_POS               4
#define LIS2DH12_HPCF_MASK              (3 << LIS2DH12_HPCF_POS)

// Bitmasks for FDS.
#define LIS2DH12_FDS_POS                3
#define LIS2DH12_FDS_MASK               (1 << LIS2DH12_FDS_POS)

// Bitmasks for HPCLICK.
#define LIS2DH12_HP_C_POS               2
#define LIS2DH12_HP_C_MASK              (1 << LIS2DH12_HP_C_POS)

// Bitmasks for HP_IA2.
#define LIS2DH12_HP_I2_POS              1
#define LIS2DH12_HP_I2_MASK             (1 << LIS2DH12_HP_I2_POS)

// Bitmasks for HP_IA1.
#define LIS2DH12_HP_I1_POS              0
#define LIS2DH12_HP_I1_MASK             (1 << LIS2DH12_HP_I1_POS)


/**
 * @brief Control register 3 bitmasks.
 */

// Bitmasks for I1_CLICK.
#define LIS2DH12_I1_CLICK_POS           7
#define LIS2DH12_I1_CLICK_MASK          (1 << LIS2DH12_I1_CLICK_POS)

// Bitmasks for I1_IA1.
#define LIS2DH12_I1_IA1_POS             6
#define LIS2DH12_I1_IA1_MASK            (1 << LIS2DH12_I1_IA1_POS)

// Bitmasks for I1_IA2.
#define LIS2DH12_I1_IA2_POS             5
#define LIS2DH12_I1_IA2_MASK            (1 << LIS2DH12_I1_IA2_POS)

// Bitmasks for I1_ZYXDA.
#define LIS2DH12_I1_ZYXDA_POS           4
#define LIS2DH12_I1_ZYXDA_MASK          (1 << LIS2DH12_I1_ZYXDA_POS)

// Bitmasks for I1_WTM.
#define LIS2DH12_I1_WTM_POS             2
#define LIS2DH12_I1_WTM_MASK            (1 << LIS2DH12_I1_WTM_POS)

// Bitmasks for I1_OVERRUN.
#define LIS2DH12_I1_OVERRUN_POS         1
#define LIS2DH12_I1_OVERRUN_MASK        (1 << LIS2DH12_I1_OVERRUN_POS)


/**
 * @brief Control register 4 bitmasks.
 */

// Bitmasks for BDU.
#define LIS2DH12_BDU_POS                7
#define LIS2DH12_BDU_MASK               (1 << LIS2DH12_BDU_POS)

// Bitmasks for BLE.
#define LIS2DH12_BLE_POS                6
#define LIS2DH12_BLE_MASK               (1 << LIS2DH12_BLE_POS)

// Bitmasks for FS.
#define LIS2DH12_FS_POS                 4
#define LIS2DH12_FS_MASK                (3 << LIS2DH12_FS_POS)

// Bitmasks for HR.
#define LIS2DH12_HR_POS                 3
#define LIS2DH12_HR_MASK                (1 << LIS2DH12_HR_POS)

// Bitmasks for ST.
#define LIS2DH12_ST_POS                 1
#define LIS2DH12_ST_MASK                (3 << LIS2DH12_ST_POS)

// Bitmasks for SIM.
#define LIS2DH12_SIM_POS                0
#define LIS2DH12_SIM_MASK               (1 << LIS2DH12_SIM_POS)


/**
 * @brief Control register 5 bitmasks.
 */

// Bitmasks for BOOT.
#define LIS2DH12_BOOT_POS               7
#define LIS2DH12_BOOT_MASK              (1 << LIS2DH12_BOOT_POS)

// Bitmasks for FIFO_EN.
#define LIS2DH12_FIFO_EN_POS            6
#define LIS2DH12_FIFO_EN_MASK           (1 << LIS2DH12_FIFO_EN_POS)

// Bitmasks for LIR_INT1.
#define LIS2DH12_LIR_INT1_POS           3
#define LIS2DH12_LIR_INT1_MASK          (1 << LIS2DH12_LIR_INT1_POS)

// Bitmasks for D4D_INT1.
#define LIS2DH12_D4D_INT1_POS           2
#define LIS2DH12_D4D_INT1_MASK          (1 << LIS2DH12_D4D_INT1_POS)

// Bitmasks for LIR_INT2.
#define LIS2DH12_LIR_INT2_POS           1
#define LIS2DH12_LIR_INT2_MASK          (1 << LIS2DH12_LIR_INT2_POS)

// Bitmasks for D4D_INT2.
#define LIS2DH12_D4D_INT2_POS           0
#define LIS2DH12_D4D_INT2_MASK          (1 << LIS2DH12_D4D_INT2_POS)


/**
 * @brief Control register 6 bitmasks.
 */

// Bitmasks for I2_CLICK.
#define LIS2DH12_I2_CLICK_POS           7
#define LIS2DH12_I2_CLICK_MASK          (1 << LIS2DH12_I2_CLICK_POS)

// Bitmasks for I2_IA1.
#define LIS2DH12_I2_IA1_POS             6
#define LIS2DH12_I2_IA1_MASK            (1 << LIS2DH12_I2_IA1_POS)

// Bitmasks for I2_IA2.
#define LIS2DH12_I2_IA2_POS             5
#define LIS2DH12_I2_IA2_MASK            (1 << LIS2DH12_I2_IA2_POS)

// Bitmasks for I2_BOOT.
#define LIS2DH12_I2_BOOT_POS            4
#define LIS2DH12_I2_BOOT_MASK           (1 << LIS2DH12_I2_BOOT_POS)

// Bitmasks for I2_ACT.
#define LIS2DH12_I2_ACT_POS             3
#define LIS2DH12_I2_ACT_MASK            (1 << LIS2DH12_I2_ACT_POS)

// Bitmasks for INT_POLARITY.
#define LIS2DH12_INT_POLARITY_POS       1
#define LIS2DH12_INT_POLARITY_MASK      (1 << LIS2DH12_INT_POLARITY_POS)


/**
 * @brief Status register bitmasks.
 */

// Bitmasks for ZYXOR.
#define LIS2DH12_ZYXOR_POS              7
#define LIS2DH12_ZYXOR_MASK             (1 << LIS2DH12_ZYXOR_POS)

// Bitmasks for ZOR.
#define LIS2DH12_ZOR_POS                6
#define LIS2DH12_ZOR_MASK               (1 << LIS2DH12_ZOR_POS)

// Bitmasks for YOR.
#define LIS2DH12_YOR_POS                5
#define LIS2DH12_YOR_MASK               (1 << LIS2DH12_YOR_POS)

// Bitmasks for XOR.
#define LIS2DH12_XOR_POS                4
#define LIS2DH12_XOR_MASK               (1 << LIS2DH12_XOR_POS)

// Bitmasks for ZYXDA.
#define LIS2DH12_ZYXDA_POS              3
#define LIS2DH12_ZYXDA_MASK             (1 << LIS2DH12_ZYXDA_POS)

// Bitmasks for ZDA.
#define LIS2DH12_ZDA_POS                2
#define LIS2DH12_ZDA_MASK               (1 << LIS2DH12_ZDA_POS)

// Bitmasks for YDA.
#define LIS2DH12_YDA_POS                1
#define LIS2DH12_YDA_MASK               (1 << LIS2DH12_YDA_POS)

// Bitmasks for XDA.
#define LIS2DH12_XDA_POS                0
#define LIS2DH12_XDA_MASK               (1 << LIS2DH12_XDA_POS)
/**
 * @brief FIFO control register bitmasks.
 */

// Bitmasks for FM.
#define LIS2DH12_FM_POS                 6
#define LIS2DH12_FM_MASK                (3 << LIS2DH12_FM_POS)

// Bitmasks for TR.
#define LIS2DH12_TR_POS                 5
#define LIS2DH12_TR_MASK                (1 << LIS2DH12_TR_POS)

// Bitmasks for FTH.
#define LIS2DH12_FTH_POS                0
#define LIS2DH12_FTH_MASK               (0x1F << LIS2DH12_FTH_POS)


/**
 * @brief FIFO source register bitmasks.
 */

// Bitmasks for WTM.
#define LIS2DH12_WTM_POS                7
#define LIS2DH12_WTM_MASK               (1 << LIS2DH12_WTM_POS)

// Bitmasks for OVRN_FIFO.
#define LIS2DH12_OVRN_FIFO_POS          6
#define LIS2DH12_OVRN_FIFO_MASK         (1 << LIS2DH12_OVRN_FIFO_POS)

// Bitmasks for EMPTY.
#define LIS2DH12_EMPTY_POS              5
#define LIS2DH12_EMPTY_MASK             (1 << LIS2DH12_EMPTY_POS)

// Bitmasks for FSS.
#define LIS2DH12_FSS_POS                0
#define LIS2DH12_FSS_MASK               (0x1F << LIS2DH12_FSS_POS)


/**
 * @brief Interrupt config register bitmasks.
 */

// Bitmasks for INT_AOI.
#define LIS2DH12_INT_AOI_POS           7
#define LIS2DH12_INT_AOI_MASK          (1 << LIS2DH12_INT_AOI_POS)

// Bitmasks for INT_6D.
#define LIS2DH12_INT_6D_POS            6
#define LIS2DH12_INT_6D_MASK           (1 << LIS2DH12_INT_6D_POS)

// Bitmasks for INT_ZHIE.
#define LIS2DH12_INT_ZHIE_POS          5
#define LIS2DH12_INT_ZHIE_MASK         (1 << LIS2DH12_INT_ZHIE_POS)

// Bitmasks for INT_ZLIE.
#define LIS2DH12_INT_ZLIE_POS          4
#define LIS2DH12_INT_ZLIE_MASK         (1 << LIS2DH12_INT_ZLIE_POS)

// Bitmasks for INT_YHIE.
#define LIS2DH12_INT_YHIE_POS          3
#define LIS2DH12_INT_YHIE_MASK         (1 << LIS2DH12_INT_YHIE_POS)

// Bitmasks for INT_YLIE.
#define LIS2DH12_INT_YLIE_POS          2
#define LIS2DH12_INT_YLIE_MASK         (1 << LIS2DH12_INT_YLIE_POS)

// Bitmasks for INT_XHIE.
#define LIS2DH12_INT_XHIE_POS          1
#define LIS2DH12_INT_XHIE_MASK         (1 << LIS2DH12_INT_XHIE_POS)

// Bitmasks for INT_XLIE.
#define LIS2DH12_INT_XLIE_POS          0
#define LIS2DH12_INT_XLIE_MASK         (1 << LIS2DH12_INT_XLIE_POS)


/**
 * @brief Interrupt source register bitmasks.
 */

// Bitmasks for IA.
#define LIS2DH12_INT_IA_POS             6
#define LIS2DH12_INT_IA_MASK            (1 << LIS2DH12_INT_IA_POS)

// Bitmasks for ZH.
#define LIS2DH12_INT_ZH_POS             5
#define LIS2DH12_INT_ZH_MASK            (1 << LIS2DH12_INT_ZH_POS)

// Bitmasks for ZL.
#define LIS2DH12_INT_ZL_POS             4
#define LIS2DH12_INT_ZL_MASK            (1 << LIS2DH12_INT_ZL_POS)

// Bitmasks for YH.
#define LIS2DH12_INT_YH_POS             3
#define LIS2DH12_INT_YH_MASK            (1 << LIS2DH12_INT_YH_POS)

// Bitmasks for YL.
#define LIS2DH12_INT_YL_POS             2
#define LIS2DH12_INT_YL_MASK            (1 << LIS2DH12_INT_YL_POS)

// Bitmasks for XH.
#define LIS2DH12_INT_XH_POS             1
#define LIS2DH12_INT_XH_MASK            (1 << LIS2DH12_INT_XH_POS)

// Bitmasks for XL.
#define LIS2DH12_INT_XL_POS             0
#define LIS2DH12_INT_XL_MASK            (1 << LIS2DH12_INT_XL_POS)


/**
 * @brief Interrupt threshold register bitmasks.
 */

// Bitmasks for THS.
#define LIS2DH12_INT_THS_POS            0
#define LIS2DH12_INT_THS_MASK           (0x7F << LIS2DH12_INT_THS_POS)


/**
 * @brief Interrupt duration register bitmasks.
 */

// Bitmasks for DUR.
#define LIS2DH12_INT_DUR_POS            0
#define LIS2DH12_INT_DUR_MASK           (0x7F << LIS2DH12_INT_DUR_POS)


/**
 * @brief Click config register bitmasks.
 */

// Bitmasks for ZD.
#define LIS2DH12_CLICK_ZD_POS           5
#define LIS2DH12_CLICK_ZD_MASK          (1 << LIS2DH12_CLICK_ZD_POS)

// Bitmasks for ZS.
#define LIS2DH12_CLICK_ZS_POS           4
#define LIS2DH12_CLICK_ZS_MASK          (1 << LIS2DH12_CLICK_ZS_POS)

// Bitmasks for YD.
#define LIS2DH12_CLICK_YD_POS           3
#define LIS2DH12_CLICK_YD_MASK          (1 << LIS2DH12_CLICK_YD_POS)

// Bitmasks for YS.
#define LIS2DH12_CLICK_YS_POS           2
#define LIS2DH12_CLICK_YS_MASK          (1 << LIS2DH12_CLICK_YS_POS)

// Bitmasks for XD.
#define LIS2DH12_CLICK_XD_POS           1
#define LIS2DH12_CLICK_XD_MASK          (1 << LIS2DH12_CLICK_XD_POS)

// Bitmasks for XS.
#define LIS2DH12_CLICK_XS_POS           0
#define LIS2DH12_CLICK_XS_MASK          (1 << LIS2DH12_CLICK_XS_POS)


/**
 * @brief Click source register bitmasks.
 */

// Bitmasks for IA.
#define LIS2DH12_CLICK_IA_POS           6
#define LIS2DH12_CLICK_IA_MASK          (1 << LIS2DH12_CLICK_IA_POS)

// Bitmasks for DCLICK.
#define LIS2DH12_CLICK_DCLICK_POS       5
#define LIS2DH12_CLICK_DCLICK_MASK      (1 << LIS2DH12_CLICK_DCLICK_POS)

// Bitmasks for SCLICK.
#define LIS2DH12_CLICK_SCLICK_POS       4
#define LIS2DH12_CLICK_SCLICK_MASK      (1 << LIS2DH12_CLICK_SCLICK_POS)

// Bitmasks for SIGN.
#define LIS2DH12_CLICK_SIGN_POS         3
#define LIS2DH12_CLICK_SIGN_MASK        (1 << LIS2DH12_CLICK_SIGN_POS)

// Bitmasks for Z.
#define LIS2DH12_CLICK_Z_POS            2
#define LIS2DH12_CLICK_Z_MASK           (1 << LIS2DH12_CLICK_Z_POS)

// Bitmasks for Y.
#define LIS2DH12_CLICK_Y_POS            1
#define LIS2DH12_CLICK_Y_MASK           (1 << LIS2DH12_CLICK_Y_POS)

// Bitmasks for X.
#define LIS2DH12_CLICK_X_POS            0
#define LIS2DH12_CLICK_X_MASK           (1 << LIS2DH12_CLICK_X_POS)


/**
 * @brief Click threshold register bitmasks.
 */

// Bitmasks for LIR.
#define LIS2DH12_CLICK_LIR_POS          7
#define LIS2DH12_CLICK_LIR_MASK         (1 << LIS2DH12_CLICK_LIR_POS)

// Bitmasks for THS.
#define LIS2DH12_CLICK_THS_POS          0
#define LIS2DH12_CLICK_THS_MASK         (0x7F << LIS2DH12_CLICK_THS_POS)


/**
 * @brief Click time limit register bitmasks.
 */

// Bitmasks for TLI.
#define LIS2DH12_CLICK_TLI_POS          0
#define LIS2DH12_CLICK_TLI_MASK         (0x7F << LIS2DH12_CLICK_TLI_POS)


/**
 * @brief Activation threshold register bitmasks.
 */

// Bitmasks for THS.
#define LIS2DH12_ACT_THS_POS            0
#define LIS2DH12_ACT_THS_MASK           (0x7F << LIS2DH12_ACT_THS_POS)

/**
 * @brief Structure holding sensor instance
 */
typedef struct
{
    nrf_twi_sensor_t * const p_sensor_data;
    uint8_t const            sensor_addr;

    uint8_t ctrl0;
    uint8_t temp_cfg;
    uint8_t ctrl1;
    uint8_t ctrl2;
    uint8_t ctrl3;
    uint8_t ctrl4;
    uint8_t ctrl5;
    uint8_t ctrl6;
    uint8_t reference;
    uint8_t fifo_ctrl;
    uint8_t int1_cfg;
    uint8_t int1_ths;
    uint8_t int1_dur;
    uint8_t int2_cfg;
    uint8_t int2_ths;
    uint8_t int2_dur;
    uint8_t click_cfg;
    uint8_t click_ths;
    uint8_t time_lim;
    uint8_t latency;
    uint8_t time_win;
    uint8_t act_ths;
    uint8_t act_dur;

} lis2dh12_instance_t;

/**
 * @brief Macro for defining sensor instance.
 */
#define LIS2DH12_INTERNAL_INSTANCE_DEF(_lis2dh12_inst_name, _p_twi_sensor, _sensor_address)       \
    static lis2dh12_instance_t _lis2dh12_inst_name =                                              \
    {                                                                                             \
        .p_sensor_data = _p_twi_sensor,                                                           \
        .sensor_addr   = _sensor_address                                                          \
    }


/**
 * @brief Macro for setting data acquisition configuration.
 */
#define LIS2DH12_INTERNAL_DATA_CFG(_s, _odr, _lp, _z_en, _y_en, _x_en, _scale, _high_res)                   \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl1, LIS2DH12_ODR_MASK,   LIS2DH12_ODR_POS,   _odr);               \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl1, LIS2DH12_LP_EN_MASK, LIS2DH12_LP_EN_POS, _lp);                \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl1, LIS2DH12_Z_EN_MASK,  LIS2DH12_Z_EN_POS,  _z_en);              \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl1, LIS2DH12_Y_EN_MASK,  LIS2DH12_Y_EN_POS,  _y_en);              \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl1, LIS2DH12_X_EN_MASK,  LIS2DH12_X_EN_POS,  _x_en);              \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl4, LIS2DH12_FS_MASK,    LIS2DH12_FS_POS,    _scale);             \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl4, LIS2DH12_HR_MASK,    LIS2DH12_HR_POS,    _high_res)

/**
 * @brief Function for setting filter configuration.
 */
#define LIS2DH12_INTERNAL_FILTER_CFG(_s, _mode, _freq, _d_en, _c_en, _i1_en, _i2_en)                        \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl2, LIS2DH12_HPM_MASK,   LIS2DH12_HPM_POS,   _mode);              \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl2, LIS2DH12_HPCF_MASK,  LIS2DH12_HPCF_POS,  _freq);              \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl2, LIS2DH12_FDS_MASK,   LIS2DH12_FDS_POS,   _d_en);              \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl2, LIS2DH12_HP_C_MASK,  LIS2DH12_HP_C_POS,  _c_en);              \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl2, LIS2DH12_HP_I1_MASK, LIS2DH12_HP_I1_POS, _i1_en);             \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl2, LIS2DH12_HP_I2_MASK, LIS2DH12_HP_I2_POS, _i2_en)

/**
 * @brief Macro for configuring INT1 pin.
 */
#define LIS2DH12_INTERNAL_INT1_PIN_CFG(_s, _cl, _ia1, _ia2, _zyxda, _wtm, _ovr, _pol, _d4d)                 \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl3, LIS2DH12_I1_CLICK_MASK,     LIS2DH12_I1_CLICK_POS,     _cl);  \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl3, LIS2DH12_I1_IA1_MASK,       LIS2DH12_I1_IA1_POS,       _ia1); \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl3, LIS2DH12_I1_IA2_MASK,       LIS2DH12_I1_IA2_POS,       _ia2); \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl3, LIS2DH12_I1_ZYXDA_MASK,     LIS2DH12_I1_ZYXDA_POS,   _zyxda); \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl3, LIS2DH12_I1_WTM_MASK,       LIS2DH12_I1_WTM_POS,       _wtm); \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl3, LIS2DH12_I1_OVERRUN_MASK,   LIS2DH12_I1_OVERRUN_POS,   _ovr); \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl6, LIS2DH12_INT_POLARITY_MASK, LIS2DH12_INT_POLARITY_POS, _pol); \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl5, LIS2DH12_D4D_INT1_MASK,     LIS2DH12_D4D_INT1_POS,     _d4d)

/**
 * @brief Macro for configuring INT2 pin.
 */
#define LIS2DH12_INTERNAL_INT2_PIN_CFG(_s, _cl, _ia1, _ia2, _boot, _act, _pol, _d4d)                        \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl6, LIS2DH12_I2_CLICK_MASK,     LIS2DH12_I2_CLICK_POS,     _cl);  \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl6, LIS2DH12_I2_IA1_MASK,       LIS2DH12_I2_IA1_POS,       _ia1); \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl6, LIS2DH12_I2_IA2_MASK,       LIS2DH12_I2_IA2_POS,       _ia2); \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl6, LIS2DH12_I2_BOOT_MASK,      LIS2DH12_I2_BOOT_POS,      _boot);\
    NRF_TWI_SENSOR_REG_SET(_s.ctrl6, LIS2DH12_I2_ACT_MASK,       LIS2DH12_I2_ACT_POS,       _act); \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl6, LIS2DH12_INT_POLARITY_MASK, LIS2DH12_INT_POLARITY_POS, _pol); \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl5, LIS2DH12_D4D_INT2_MASK,     LIS2DH12_D4D_INT2_POS,     _d4d)

 /**
  * @brief Macro for configuring interrupt 1.
  */
#define LIS2DH12_INTERNAL_INT1_CFG(_s, _thr, _dur, _aoi, _6d, _zh, _zl, _yh, yl, _xh, _xl, _lir)            \
    NRF_TWI_SENSOR_REG_SET(_s.int1_ths, LIS2DH12_INT_THS_MASK,  LIS2DH12_INT_THS_POS,  _thr);      \
    NRF_TWI_SENSOR_REG_SET(_s.int1_dur, LIS2DH12_INT_DUR_MASK,  LIS2DH12_INT_DUR_POS,  _dur);      \
    NRF_TWI_SENSOR_REG_SET(_s.int1_cfg, LIS2DH12_INT_AOI_MASK,  LIS2DH12_INT_AOI_POS,  _aoi);      \
    NRF_TWI_SENSOR_REG_SET(_s.int1_cfg, LIS2DH12_INT_6D_MASK,   LIS2DH12_INT_6D_POS,   _6d);       \
    NRF_TWI_SENSOR_REG_SET(_s.int1_cfg, LIS2DH12_INT_ZHIE_MASK, LIS2DH12_INT_ZHIE_POS, _zh);       \
    NRF_TWI_SENSOR_REG_SET(_s.int1_cfg, LIS2DH12_INT_ZLIE_MASK, LIS2DH12_INT_ZLIE_POS, _zl);       \
    NRF_TWI_SENSOR_REG_SET(_s.int1_cfg, LIS2DH12_INT_YHIE_MASK, LIS2DH12_INT_YHIE_POS, _yh);       \
    NRF_TWI_SENSOR_REG_SET(_s.int1_cfg, LIS2DH12_INT_YLIE_MASK, LIS2DH12_INT_YLIE_POS, _yl);       \
    NRF_TWI_SENSOR_REG_SET(_s.int1_cfg, LIS2DH12_INT_XHIE_MASK, LIS2DH12_INT_XHIE_POS, _xh);       \
    NRF_TWI_SENSOR_REG_SET(_s.int1_cfg, LIS2DH12_INT_XLIE_MASK, LIS2DH12_INT_XLIE_POS, _xl);       \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl5,    LIS2DH12_LIR_INT1_MASK, LIS2DH12_LIR_INT1_POS, _lir)


/**
 * @brief Macro for configuring interrupt 2.
 */
#define LIS2DH12_INTERNAL_INT2_CFG(_s, _thr, _dur, _aoi, _6d, _zh, _zl, _yh, yl, _xh, _xl, _lir)           \
   NRF_TWI_SENSOR_REG_SET(_s.int2_ths, LIS2DH12_INT_THS_MASK,  LIS2DH12_INT_THS_POS,  _thr);      \
   NRF_TWI_SENSOR_REG_SET(_s.int2_dur, LIS2DH12_INT_DUR_MASK,  LIS2DH12_INT_DUR_POS,  _dur);      \
   NRF_TWI_SENSOR_REG_SET(_s.int2_cfg, LIS2DH12_INT_AOI_MASK,  LIS2DH12_INT_AOI_POS,  _aoi);      \
   NRF_TWI_SENSOR_REG_SET(_s.int2_cfg, LIS2DH12_INT_6D_MASK,   LIS2DH12_INT_6D_POS,   _6d);       \
   NRF_TWI_SENSOR_REG_SET(_s.int2_cfg, LIS2DH12_INT_ZHIE_MASK, LIS2DH12_INT_ZHIE_POS, _zh);       \
   NRF_TWI_SENSOR_REG_SET(_s.int2_cfg, LIS2DH12_INT_ZLIE_MASK, LIS2DH12_INT_ZLIE_POS, _zl);       \
   NRF_TWI_SENSOR_REG_SET(_s.int2_cfg, LIS2DH12_INT_YHIE_MASK, LIS2DH12_INT_YHIE_POS, _yh);       \
   NRF_TWI_SENSOR_REG_SET(_s.int2_cfg, LIS2DH12_INT_YLIE_MASK, LIS2DH12_INT_YLIE_POS, _yl);       \
   NRF_TWI_SENSOR_REG_SET(_s.int2_cfg, LIS2DH12_INT_XHIE_MASK, LIS2DH12_INT_XHIE_POS, _xh);       \
   NRF_TWI_SENSOR_REG_SET(_s.int2_cfg, LIS2DH12_INT_XLIE_MASK, LIS2DH12_INT_XLIE_POS, _xl);       \
   NRF_TWI_SENSOR_REG_SET(_s.ctrl5,    LIS2DH12_LIR_INT2_MASK, LIS2DH12_LIR_INT2_POS, _lir)

/**
  * @brief Function for setting click configuration.
  */
#define LIS2DH12_INTERNAL_CLICK_CFG(_s, _zd, _zs, _yd, _ys, _xd, _xs, _lir, _ths, _lim, _ltc, _win)         \
    NRF_TWI_SENSOR_REG_SET(_s.click_cfg, LIS2DH12_CLICK_ZD_MASK,  LIS2DH12_CLICK_ZD_POS,  _zd);    \
    NRF_TWI_SENSOR_REG_SET(_s.click_cfg, LIS2DH12_CLICK_ZS_MASK,  LIS2DH12_CLICK_ZD_POS,  _zd);    \
    NRF_TWI_SENSOR_REG_SET(_s.click_cfg, LIS2DH12_CLICK_YD_MASK,  LIS2DH12_CLICK_YD_POS,  _yd);    \
    NRF_TWI_SENSOR_REG_SET(_s.click_cfg, LIS2DH12_CLICK_YS_MASK,  LIS2DH12_CLICK_YS_POS,  _ys);    \
    NRF_TWI_SENSOR_REG_SET(_s.click_cfg, LIS2DH12_CLICK_XD_MASK,  LIS2DH12_CLICK_XD_POS,  _xd);    \
    NRF_TWI_SENSOR_REG_SET(_s.click_cfg, LIS2DH12_CLICK_XS_MASK,  LIS2DH12_CLICK_XS_POS,  _xs);    \
    NRF_TWI_SENSOR_REG_SET(_s.click_ths, LIS2DH12_CLICK_LIR_MASK, LIS2DH12_CLICK_LIR_POS, _lir);   \
    NRF_TWI_SENSOR_REG_SET(_s.click_ths, LIS2DH12_CLICK_THS_MASK, LIS2DH12_CLICK_THS_POS, _ths);   \
    NRF_TWI_SENSOR_REG_SET(_s.time_lim,  LIS2DH12_CLICK_TLI_MASK, LIS2DH12_CLICK_TLI_POS, _lim);   \
    _s.latency  = _ltc;                                                                            \
    _s.time_win = _win

 /**
  * @brief Macro for setting sleep configuration.
  */
#define LIS2DH12_INTERNAL_SLEEP_CFG(_s, _ths, _dur)                                                         \
    NRF_TWI_SENSOR_REG_SET(_s.act_ths, LIS2DH12_ACT_THS_MASK, LIS2DH12_ACT_THS_POS, _ths);         \
    _s.act_dur = _dur

/**
 * @brief Macro for setting reference value for interrupt generation.
 */
#define LIS2DH12_INTERNAL_REF_SET(_s, _ref) \
    _s.reference = _ref


/**
 * @brief Macro for setting FIFO configuration.
 */
#define LIS2DH12_INTERNAL_FIFO_CFG(_s, _en, _mode, _t_sel, _t_thr)                                          \
    NRF_TWI_SENSOR_REG_SET(_s.fifo_ctrl, LIS2DH12_FM_MASK,      LIS2DH12_FM_POS,      _mode);      \
    NRF_TWI_SENSOR_REG_SET(_s.fifo_ctrl, LIS2DH12_TR_MASK,      LIS2DH12_TR_POS,      _t_sel);     \
    NRF_TWI_SENSOR_REG_SET(_s.fifo_ctrl, LIS2DH12_FTH_MASK,     LIS2DH12_FTH_POS,     _t_thr);     \
    NRF_TWI_SENSOR_REG_SET(_s.ctrl5,     LIS2DH12_FIFO_EN_MASK, LIS2DH12_FIFO_EN_POS, _en)


#ifndef SUPPRESS_INLINE_IMPLEMENTATION

__STATIC_INLINE ret_code_t lis2dh12_temp_status_read(lis2dh12_instance_t *     p_inst,
                                                     nrf_twi_sensor_reg_cb_t   user_cb,
                                                     uint8_t *                 p_data)
{
    ASSERT(p_inst != NULL);
    return nrf_twi_sensor_reg_read(p_inst->p_sensor_data,
                                   p_inst->sensor_addr,
                                   LIS2DH12_REG_STATUS_AUX,
                                   user_cb,
                                   p_data,
                                   1);
}

__STATIC_INLINE ret_code_t lis2dh12_who_am_i_read(lis2dh12_instance_t *     p_inst,
                                                  nrf_twi_sensor_reg_cb_t   user_cb,
                                                  uint8_t *                 p_data)
{
    ASSERT(p_inst != NULL);
    return nrf_twi_sensor_reg_read(p_inst->p_sensor_data,
                                   p_inst->sensor_addr,
                                   LIS2DH12_REG_WHO_AM_I,
                                   user_cb,
                                   p_data,
                                   1);
}

__STATIC_INLINE ret_code_t lis2dh12_status_read(lis2dh12_instance_t *     p_inst,
                                                nrf_twi_sensor_reg_cb_t   user_cb,
                                                uint8_t *                 p_data)
{
    ASSERT(p_inst != NULL);
    return nrf_twi_sensor_reg_read(p_inst->p_sensor_data,
                                   p_inst->sensor_addr,
                                   LIS2DH12_REG_STATUS,
                                   user_cb,
                                   p_data,
                                   1);
}

__STATIC_INLINE ret_code_t lis2dh12_fifo_src_read(lis2dh12_instance_t *     p_inst,
                                                  nrf_twi_sensor_reg_cb_t   user_cb,
                                                  uint8_t *                 p_data)
{
    ASSERT(p_inst != NULL);
    return nrf_twi_sensor_reg_read(p_inst->p_sensor_data,
                                   p_inst->sensor_addr,
                                   LIS2DH12_REG_FIFO_SRC,
                                   user_cb,
                                   p_data,
                                   1);
}

__STATIC_INLINE ret_code_t lis2dh12_int1_src_read(lis2dh12_instance_t *     p_inst,
                                                  nrf_twi_sensor_reg_cb_t   user_cb,
                                                  uint8_t *                 p_data)
{
    ASSERT(p_inst != NULL);
    return nrf_twi_sensor_reg_read(p_inst->p_sensor_data,
                                   p_inst->sensor_addr,
                                   LIS2DH12_REG_INT1_SRC,
                                   user_cb,
                                   p_data,
                                   1);
}

__STATIC_INLINE ret_code_t lis2dh12_int2_src_read(lis2dh12_instance_t *     p_inst,
                                                  nrf_twi_sensor_reg_cb_t   user_cb,
                                                  uint8_t *                 p_data)
{
    ASSERT(p_inst != NULL);
    return nrf_twi_sensor_reg_read(p_inst->p_sensor_data,
                                   p_inst->sensor_addr,
                                   LIS2DH12_REG_INT2_SRC,
                                   user_cb,
                                   p_data,
                                   1);
}

__STATIC_INLINE ret_code_t lis2dh12_click_src_read(lis2dh12_instance_t *     p_inst,
                                                   nrf_twi_sensor_reg_cb_t   user_cb,
                                                   uint8_t *                 p_data)
{
    ASSERT(p_inst != NULL);
    return nrf_twi_sensor_reg_read(p_inst->p_sensor_data,
                                   p_inst->sensor_addr,
                                   LIS2DH12_REG_CLICK_SRC,
                                   user_cb,
                                   p_data,
                                   1);
}

#endif //SUPPRESS_INLINE_IMPLEMENTATION

#ifdef __cplusplus
}
#endif

#endif // LIS2DH12_INTERNAL_H
