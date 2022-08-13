/*
 * Copyright 2020-2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FSL_DCDC_H__
#define __FSL_DCDC_H__

#include "fsl_common.h"

/*!
 * @addtogroup dcdc_soc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief DCDC driver version. */
#define FSL_DCDC_DRIVER_VERSION (MAKE_VERSION(2, 1, 1)) /*!< Version 2.1.1. */

/*! @brief The array of VDD1P0 target voltage in standby mode. */
#define STANDBY_MODE_VDD1P0_TARGET_VOLTAGE                                                                             \
    {                                                                                                                  \
        625, 650, 675, 700, 725, 750, 775, 800, 825, 850, 875, 900, 925, 950, 975, 1000, 1025, 1050, 1075, 1100, 1125, \
            1150, 1175, 1200, 1225, 1250, 1275, 1300, 1325, 1350, 1375, 1400                                           \
    }

/*! @brief The array of VDD1P8 target voltage in standby mode. */
#define STANDBY_MODE_VDD1P8_TARGET_VOLTAGE                                                                          \
    {                                                                                                               \
        1525, 1550, 1575, 1600, 1625, 1650, 1675, 1700, 1725, 1750, 1775, 1800, 1825, 1850, 1875, 1900, 1925, 1950, \
            1975, 2000, 2025, 2050, 2075, 2100, 2125, 2150, 2175, 2200, 2225, 2250, 2275, 2300                      \
    }

/*! @brief The array of VDD1P0 target voltage in buck mode. */
#define BUCK_MODE_VDD1P0_TARGET_VOLTAGE                                                                               \
    {                                                                                                                 \
        600, 625, 650, 675, 700, 725, 750, 775, 800, 825, 850, 875, 900, 925, 950, 975, 1000, 1025, 1050, 1075, 1100, \
            1125, 1150, 1175, 1200, 1225, 1250, 1275, 1300, 1325, 1350, 1375                                          \
    }

/*! @brief The array of VDD1P8 target voltage in buck mode. */
#define BUCK_MODE_VDD1P8_TARGET_VOLTAGE                                                                             \
    {                                                                                                               \
        1500, 1525, 1550, 1575, 1600, 1625, 1650, 1675, 1700, 1725, 1750, 1775, 1800, 1825, 1850, 1875, 1900, 1925, \
            1950, 1975, 2000, 2025, 2050, 2075, 2100, 2125, 2150, 2175, 2200, 2225, 2250, 2275                      \
    }

/*!
 * @brief The enumeration of DCDC status flags.
 */
enum _dcdc_status_flags
{
    kDCDC_AlreadySettledStatusFlag = DCDC_REG0_STS_DC_OK_MASK, /*!< Indicate DCDC status.
                                                            1'b1: DCDC already settled
                                                            1'b0: DCDC is settling. */
};

/*!
 * @brief System setpoints enumeration.
 */
enum _dcdc_setpoint_map
{
    kDCDC_SetPoint0  = 1UL << 0UL,  /*!< Set point 0. */
    kDCDC_SetPoint1  = 1UL << 1UL,  /*!< Set point 1. */
    kDCDC_SetPoint2  = 1UL << 2UL,  /*!< Set point 2. */
    kDCDC_SetPoint3  = 1UL << 3UL,  /*!< Set point 3. */
    kDCDC_SetPoint4  = 1UL << 4UL,  /*!< Set point 4. */
    kDCDC_SetPoint5  = 1UL << 5UL,  /*!< Set point 5. */
    kDCDC_SetPoint6  = 1UL << 6UL,  /*!< Set point 6. */
    kDCDC_SetPoint7  = 1UL << 7UL,  /*!< Set point 7. */
    kDCDC_SetPoint8  = 1UL << 8UL,  /*!< Set point 8. */
    kDCDC_SetPoint9  = 1UL << 9UL,  /*!< Set point 9. */
    kDCDC_SetPoint10 = 1UL << 10UL, /*!< Set point 10. */
    kDCDC_SetPoint11 = 1UL << 11UL, /*!< Set point 11. */
    kDCDC_SetPoint12 = 1UL << 12UL, /*!< Set point 12. */
    kDCDC_SetPoint13 = 1UL << 13UL, /*!< Set point 13. */
    kDCDC_SetPoint14 = 1UL << 14UL, /*!< Set point 14. */
    kDCDC_SetPoint15 = 1UL << 15UL  /*!< Set point 15. */
};

/*!
 * @brief DCDC control mode, including setpoint control mode and static control mode.
 */
typedef enum _dcdc_control_mode
{
    kDCDC_StaticControl   = 0U, /*!< Static control. */
    kDCDC_SetPointControl = 1U, /*!< Controlled by GPC set points. */
} dcdc_control_mode_t;

/*!
 * @brief DCDC trim input mode, including sample trim input and hold trim input.
 */
typedef enum _dcdc_trim_input_mode
{
    kDCDC_SampleTrimInput = 0U, /*!< Sample trim input. */
    kDCDC_HoldTrimInput   = 1U, /*!< Hold trim input. */
} dcdc_trim_input_mode_t;

/*!
 * @brief The enumeration VDD1P0's target voltage value in standby mode.
 */
typedef enum _dcdc_standby_mode_1P0_target_vol
{
    kDCDC_1P0StbyTarget0P625V = 0U, /*!< In standby mode, the target voltage value of VDD1P0 is 0.625V. */
    kDCDC_1P0StbyTarget0P65V,       /*!< In standby mode, the target voltage value of VDD1P0 is 0.65V. */
    kDCDC_1P0StbyTarget0P675V,      /*!< In standby mode, the target voltage value of VDD1P0 is 0.675V. */

    kDCDC_1P0StbyTarget0P7V,   /*!< In standby mode, the target voltage value of VDD1P0 is 0.7V. */
    kDCDC_1P0StbyTarget0P725V, /*!< In standby mode, the target voltage value of VDD1P0 is 0.725V. */
    kDCDC_1P0StbyTarget0P75V,  /*!< In standby mode, the target voltage value of VDD1P0 is 0.75V. */
    kDCDC_1P0StbyTarget0P775V, /*!< In standby mode, the target voltage value of VDD1P0 is 0.775V. */

    kDCDC_1P0StbyTarget0P8V,   /*!< In standby mode, the target voltage value of VDD1P0 is 0.8V. */
    kDCDC_1P0StbyTarget0P825V, /*!< In standby mode, the target voltage value of VDD1P0 is 0.825V. */
    kDCDC_1P0StbyTarget0P85V,  /*!< In standby mode, the target voltage value of VDD1P0 is 0.85V. */
    kDCDC_1P0StbyTarget0P875V, /*!< In standby mode, the target voltage value of VDD1P0 is 0.875V. */

    kDCDC_1P0StbyTarget0P9V,   /*!< In standby mode, the target voltage value of VDD1P0 is 0.9V. */
    kDCDC_1P0StbyTarget0P925V, /*!< In standby mode, the target voltage value of VDD1P0 is 0.925V. */
    kDCDC_1P0StbyTarget0P95V,  /*!< In standby mode, the target voltage value of VDD1P0 is 0.95V. */
    kDCDC_1P0StbyTarget0P975V, /*!< In standby mode, the target voltage value of VDD1P0 is 0.975V. */

    kDCDC_1P0StbyTarget1P0V,   /*!< In standby mode, the target voltage value of VDD1P0 is 1.0V. */
    kDCDC_1P0StbyTarget1P025V, /*!< In standby mode, the target voltage value of VDD1P0 is 1.025V. */
    kDCDC_1P0StbyTarget1P05V,  /*!< In standby mode, the target voltage value of VDD1P0 is 1.05V. */
    kDCDC_1P0StbyTarget1P075V, /*!< In standby mode, the target voltage value of VDD1P0 is 1.075V. */

    kDCDC_1P0StbyTarget1P1V,   /*!< In standby mode, the target voltage value of VDD1P0 is 1.1V. */
    kDCDC_1P0StbyTarget1P125V, /*!< In standby mode, the target voltage value of VDD1P0 is 1.125V. */
    kDCDC_1P0StbyTarget1P15V,  /*!< In standby mode, the target voltage value of VDD1P0 is 1.15V. */
    kDCDC_1P0StbyTarget1P175V, /*!< In standby mode, the target voltage value of VDD1P0 is 1.175V. */

    kDCDC_1P0StbyTarget1P2V,   /*!< In standby mode, the target voltage value of VDD1P0 is 1.2V. */
    kDCDC_1P0StbyTarget1P225V, /*!< In standby mode, the target voltage value of VDD1P0 is 1.225V. */
    kDCDC_1P0StbyTarget1P25V,  /*!< In standby mode, the target voltage value of VDD1P0 is 1.25V. */
    kDCDC_1P0StbyTarget1P275V, /*!< In standby mode, the target voltage value of VDD1P0 is 1.275V. */

    kDCDC_1P0StbyTarget1P3V,   /*!< In standby mode, the target voltage value of VDD1P0 is 1.3V. */
    kDCDC_1P0StbyTarget1P325V, /*!< In standby mode, the target voltage value of VDD1P0 is 1.325V. */
    kDCDC_1P0StbyTarget1P35V,  /*!< In standby mode, the target voltage value of VDD1P0 is 1.35V. */
    kDCDC_1P0StbyTarget1P375V, /*!< In standby mode, the target voltage value of VDD1P0 is 1.375V. */

    kDCDC_1P0StbyTarget1P4V = 0x1FU, /*!< In standby mode, The target voltage value of VDD1P0 is 1.4V */
} dcdc_standby_mode_1P0_target_vol_t;

/*!
 * @brief The enumeration VDD1P8's target voltage value in standby mode.
 */
typedef enum _dcdc_standby_mode_1P8_target_vol
{
    kDCDC_1P8StbyTarget1P525V = 0U, /*!< In standby mode, the target voltage value of VDD1P8 is 1.525V. */
    kDCDC_1P8StbyTarget1P55V,       /*!< In standby mode, the target voltage value of VDD1P8 is 1.55V. */
    kDCDC_1P8StbyTarget1P575V,      /*!< In standby mode, the target voltage value of VDD1P8 is 1.575V. */

    kDCDC_1P8StbyTarget1P6V,   /*!< In standby mode, the target voltage value of VDD1P8 is 1.6V. */
    kDCDC_1P8StbyTarget1P625V, /*!< In standby mode, the target voltage value of VDD1P8 is 1.625V. */
    kDCDC_1P8StbyTarget1P65V,  /*!< In standby mode, the target voltage value of VDD1P8 is 1.65V. */
    kDCDC_1P8StbyTarget1P675V, /*!< In standby mode, the target voltage value of VDD1P8 is 1.675V. */

    kDCDC_1P8StbyTarget1P7V,   /*!< In standby mode, the target voltage value of VDD1P8 is 1.7V. */
    kDCDC_1P8StbyTarget1P725V, /*!< In standby mode, the target voltage value of VDD1P8 is 1.725V. */
    kDCDC_1P8StbyTarget1P75V,  /*!< In standby mode, the target voltage value of VDD1P8 is 1.75V. */
    kDCDC_1P8StbyTarget1P775V, /*!< In standby mode, the target voltage value of VDD1P8 is 1.775V. */

    kDCDC_1P8StbyTarget1P8V,   /*!< In standby mode, the target voltage value of VDD1P8 is 1.8V. */
    kDCDC_1P8StbyTarget1P825V, /*!< In standby mode, the target voltage value of VDD1P8 is 1.825V. */
    kDCDC_1P8StbyTarget1P85V,  /*!< In standby mode, the target voltage value of VDD1P8 is 1.85V. */
    kDCDC_1P8StbyTarget1P875V, /*!< In standby mode, the target voltage value of VDD1P8 is 1.875V. */

    kDCDC_1P8StbyTarget1P9V,   /*!< In standby mode, the target voltage value of VDD1P8 is 1.9V. */
    kDCDC_1P8StbyTarget1P925V, /*!< In standby mode, the target voltage value of VDD1P8 is 1.925V. */
    kDCDC_1P8StbyTarget1P95V,  /*!< In standby mode, the target voltage value of VDD1P8 is 1.95V. */
    kDCDC_1P8StbyTarget1P975V, /*!< In standby mode, the target voltage value of VDD1P8 is 1.975V. */

    kDCDC_1P8StbyTarget2P0V,   /*!< In standby mode, the target voltage value of VDD1P8 is 2.0V. */
    kDCDC_1P8StbyTarget2P025V, /*!< In standby mode, the target voltage value of VDD1P8 is 2.025V. */
    kDCDC_1P8StbyTarget2P05V,  /*!< In standby mode, the target voltage value of VDD1P8 is 2.05V. */
    kDCDC_1P8StbyTarget2P075V, /*!< In standby mode, the target voltage value of VDD1P8 is 2.075V. */

    kDCDC_1P8StbyTarget2P1V,   /*!< In standby mode, the target voltage value of VDD1P8 is 2.1V. */
    kDCDC_1P8StbyTarget2P125V, /*!< In standby mode, the target voltage value of VDD1P8 is 2.125V. */
    kDCDC_1P8StbyTarget2P15V,  /*!< In standby mode, the target voltage value of VDD1P8 is 2.15V. */
    kDCDC_1P8StbyTarget2P175V, /*!< In standby mode, the target voltage value of VDD1P8 is 2.175V. */

    kDCDC_1P8StbyTarget2P2V,   /*!< In standby mode, the target voltage value of VDD1P8 is 2.2V. */
    kDCDC_1P8StbyTarget2P225V, /*!< In standby mode, the target voltage value of VDD1P8 is 2.225V. */
    kDCDC_1P8StbyTarget2P25V,  /*!< In standby mode, the target voltage value of VDD1P8 is 2.25V. */
    kDCDC_1P8StbyTarget2P275V, /*!< In standby mode, the target voltage value of VDD1P8 is 2.275V. */

    kDCDC_1P8StbyTarget2P3V = 0x1FU, /*!< In standby mode, the target voltage value is 2.3V. */
} dcdc_standby_mode_1P8_target_vol_t;

/*!
 * @brief The enumeration VDD1P0's target voltage value in buck mode.
 */
typedef enum _dcdc_buck_mode_1P0_target_vol
{
    kDCDC_1P0BuckTarget0P6V = 0U, /*!< In buck mode, the target voltage value of VDD1P0 is 0.6V. */
    kDCDC_1P0BuckTarget0P625V,    /*!< In buck mode, the target voltage value of VDD1P0 is 0.625V. */
    kDCDC_1P0BuckTarget0P65V,     /*!< In buck mode, the target voltage value of VDD1P0 is 0.65V. */
    kDCDC_1P0BuckTarget0P675V,    /*!< In buck mode, the target voltage value of VDD1P0 is 0.675V. */

    kDCDC_1P0BuckTarget0P7V,   /*!< In buck mode, the target voltage value of VDD1P0 is 0.7V. */
    kDCDC_1P0BuckTarget0P725V, /*!< In buck mode, the target voltage value of VDD1P0 is 0.725V. */
    kDCDC_1P0BuckTarget0P75V,  /*!< In buck mode, the target voltage value of VDD1P0 is 0.75V. */
    kDCDC_1P0BuckTarget0P775V, /*!< In buck mode, the target voltage value of VDD1P0 is 0.775V. */

    kDCDC_1P0BuckTarget0P8V,   /*!< In buck mode, the target voltage value of VDD1P0 is 0.8V. */
    kDCDC_1P0BuckTarget0P825V, /*!< In buck mode, the target voltage value of VDD1P0 is 0.825V. */
    kDCDC_1P0BuckTarget0P85V,  /*!< In buck mode, the target voltage value of VDD1P0 is 0.85V. */
    kDCDC_1P0BuckTarget0P875V, /*!< In buck mode, the target voltage value of VDD1P0 is 0.875V. */

    kDCDC_1P0BuckTarget0P9V,   /*!< In buck mode, the target voltage value of VDD1P0 is 0.9V. */
    kDCDC_1P0BuckTarget0P925V, /*!< In buck mode, the target voltage value of VDD1P0 is 0.925V. */
    kDCDC_1P0BuckTarget0P95V,  /*!< In buck mode, the target voltage value of VDD1P0 is 0.95V. */
    kDCDC_1P0BuckTarget0P975V, /*!< In buck mode, the target voltage value of VDD1P0 is 0.975V. */

    kDCDC_1P0BuckTarget1P0V,   /*!< In buck mode, the target voltage value of VDD1P0 is 1.0V. */
    kDCDC_1P0BuckTarget1P025V, /*!< In buck mode, the target voltage value of VDD1P0 is 1.025V. */
    kDCDC_1P0BuckTarget1P05V,  /*!< In buck mode, the target voltage value of VDD1P0 is 1.05V. */
    kDCDC_1P0BuckTarget1P075V, /*!< In buck mode, the target voltage value of VDD1P0 is 1.075V. */

    kDCDC_1P0BuckTarget1P1V,   /*!< In buck mode, the target voltage value of VDD1P0 is 1.1V. */
    kDCDC_1P0BuckTarget1P125V, /*!< In buck mode, the target voltage value of VDD1P0 is 1.125V. */
    kDCDC_1P0BuckTarget1P15V,  /*!< In buck mode, the target voltage value of VDD1P0 is 1.15V. */
    kDCDC_1P0BuckTarget1P175V, /*!< In buck mode, the target voltage value of VDD1P0 is 1.175V. */

    kDCDC_1P0BuckTarget1P2V,   /*!< In buck mode, the target voltage value of VDD1P0 is 1.2V. */
    kDCDC_1P0BuckTarget1P225V, /*!< In buck mode, the target voltage value of VDD1P0 is 1.225V. */
    kDCDC_1P0BuckTarget1P25V,  /*!< In buck mode, the target voltage value of VDD1P0 is 1.25V. */
    kDCDC_1P0BuckTarget1P275V, /*!< In buck mode, the target voltage value of VDD1P0 is 1.275V. */

    kDCDC_1P0BuckTarget1P3V,           /*!< In buck mode, the target voltage value of VDD1P0 is 1.3V. */
    kDCDC_1P0BuckTarget1P325V,         /*!< In buck mode, the target voltage value of VDD1P0 is 1.325V. */
    kDCDC_1P0BuckTarget1P35V,          /*!< In buck mode, the target voltage value of VDD1P0 is 1.35V. */
    kDCDC_1P0BuckTarget1P375V = 0x1FU, /*!< In buck mode, the target voltage value of VDD1P0 is 1.375V. */
} dcdc_buck_mode_1P0_target_vol_t;

/*!
 * @brief The enumeration VDD1P8's target voltage value in buck mode.
 */
typedef enum _dcdc_buck_mode_1P8_target_vol
{
    kDCDC_1P8BuckTarget1P5V = 0U, /*!< In buck mode, the target voltage value of VDD1P0 is 1.5V. */
    kDCDC_1P8BuckTarget1P525V,    /*!< In buck mode, the target voltage value of VDD1P0 is 1.525V. */
    kDCDC_1P8BuckTarget1P55V,     /*!< In buck mode, the target voltage value of VDD1P0 is 1.55V. */
    kDCDC_1P8BuckTarget1P575V,    /*!< In buck mode, the target voltage value of VDD1P0 is 1.575V. */

    kDCDC_1P8BuckTarget1P6V,   /*!< In buck mode, the target voltage value of VDD1P0 is 1.6V. */
    kDCDC_1P8BuckTarget1P625V, /*!< In buck mode, the target voltage value of VDD1P0 is 1.625V. */
    kDCDC_1P8BuckTarget1P65V,  /*!< In buck mode, the target voltage value of VDD1P0 is 1.65V. */
    kDCDC_1P8BuckTarget1P675V, /*!< In buck mode, the target voltage value of VDD1P0 is 1.675V. */

    kDCDC_1P8BuckTarget1P7V,   /*!< In buck mode, the target voltage value of VDD1P0 is 1.7V. */
    kDCDC_1P8BuckTarget1P725V, /*!< In buck mode, the target voltage value of VDD1P0 is 1.725V. */
    kDCDC_1P8BuckTarget1P75V,  /*!< In buck mode, the target voltage value of VDD1P0 is 1.75V. */
    kDCDC_1P8BuckTarget1P775V, /*!< In buck mode, the target voltage value of VDD1P0 is 1.775V. */

    kDCDC_1P8BuckTarget1P8V,   /*!< In buck mode, the target voltage value of VDD1P0 is 1.8V. */
    kDCDC_1P8BuckTarget1P825V, /*!< In buck mode, the target voltage value of VDD1P0 is 1.825V. */
    kDCDC_1P8BuckTarget1P85V,  /*!< In buck mode, the target voltage value of VDD1P0 is 1.85V. */
    kDCDC_1P8BuckTarget1P875V, /*!< In buck mode, the target voltage value of VDD1P0 is 1.875V. */

    kDCDC_1P8BuckTarget1P9V,   /*!< In buck mode, the target voltage value of VDD1P0 is 1.9V. */
    kDCDC_1P8BuckTarget1P925V, /*!< In buck mode, the target voltage value of VDD1P0 is 1.925V. */
    kDCDC_1P8BuckTarget1P95V,  /*!< In buck mode, the target voltage value of VDD1P0 is 1.95V. */
    kDCDC_1P8BuckTarget1P975V, /*!< In buck mode, the target voltage value of VDD1P0 is 1.975V. */

    kDCDC_1P8BuckTarget2P0V,   /*!< In buck mode, the target voltage value of VDD1P0 is 2.0V. */
    kDCDC_1P8BuckTarget2P025V, /*!< In buck mode, the target voltage value of VDD1P0 is 2.025V. */
    kDCDC_1P8BuckTarget2P05V,  /*!< In buck mode, the target voltage value of VDD1P0 is 2.05V. */
    kDCDC_1P8BuckTarget2P075V, /*!< In buck mode, the target voltage value of VDD1P0 is 2.075V. */

    kDCDC_1P8BuckTarget2P1V,   /*!< In buck mode, the target voltage value of VDD1P0 is 2.1V. */
    kDCDC_1P8BuckTarget2P125V, /*!< In buck mode, the target voltage value of VDD1P0 is 2.125V. */
    kDCDC_1P8BuckTarget2P15V,  /*!< In buck mode, the target voltage value of VDD1P0 is 2.15V. */
    kDCDC_1P8BuckTarget2P175V, /*!< In buck mode, the target voltage value of VDD1P0 is 2.175V. */

    kDCDC_1P8BuckTarget2P2V,           /*!< In buck mode, the target voltage value of VDD1P0 is 2.2V. */
    kDCDC_1P8BuckTarget2P225V,         /*!< In buck mode, the target voltage value of VDD1P0 is 2.225V. */
    kDCDC_1P8BuckTarget2P25V,          /*!< In buck mode, the target voltage value of VDD1P0 is 2.25V. */
    kDCDC_1P8BuckTarget2P275V = 0x1FU, /*!< In buck mode, the target voltage value of VDD1P0 is 2.275V. */
} dcdc_buck_mode_1P8_target_vol_t;

/*!
 * @brief The current bias of low power comparator.
 */
typedef enum _dcdc_comparator_current_bias
{
    kDCDC_ComparatorCurrentBias50nA  = 0U, /*!< The current bias of low power comparator is 50nA. */
    kDCDC_ComparatorCurrentBias100nA = 1U, /*!< The current bias of low power comparator is 100nA. */
    kDCDC_ComparatorCurrentBias200nA = 2U, /*!< The current bias of low power comparator is 200nA. */
    kDCDC_ComparatorCurrentBias400nA = 3U, /*!< The current bias of low power comparator is 400nA. */
} dcdc_comparator_current_bias_t;

/*!
 * @brief The threshold if peak current detection.
 */
typedef enum _dcdc_peak_current_threshold
{
    kDCDC_PeakCurrentRunMode250mALPMode1P5A = 0U, /*!< Over peak current threshold in low power mode is 250mA,
                                                      in run mode is 1.5A */
    kDCDC_PeakCurrentRunMode200mALPMode1P5A,      /*!< Over peak current threshold in low power mode is 200mA,
                                                           in run mode is 1.5A */
    kDCDC_PeakCurrentRunMode250mALPMode2A,        /*!< Over peak current threshold in low power mode is 250mA,
                                                             in run mode is 2A */
    kDCDC_PeakCurrentRunMode200mALPMode2A,        /*!< Over peak current threshold in low power mode is 200mA,
                                                             in run mode is 2A */
} dcdc_peak_current_threshold_t;

/*!
 * @brief Oscillator clock option.
 */
typedef enum _dcdc_clock_source
{
    kDCDC_ClockAutoSwitch  = 0U, /*!< Automatic clock switch from internal oscillator to external clock. */
    kDCDC_ClockInternalOsc = 1U, /*!< Use internal oscillator. */
    kDCDC_ClockExternalOsc = 2U, /*!< Use external 24M crystal oscillator. */
} dcdc_clock_source_t;

/*!
 * @brief Voltage output option.
 */
typedef enum _dcdc_voltage_output_sel
{
    kDCDC_VoltageOutput1P8 = 0U, /*!< 1.8V output. */
    kDCDC_VoltageOutput1P0 = 1U, /*!< 1.0V output. */
} dcdc_voltage_output_sel_t;

/*!
 * @brief Configuration for DCDC.
 */
typedef struct _dcdc_config
{
    dcdc_control_mode_t controlMode;      /*!< DCDC control mode. */
    dcdc_trim_input_mode_t trimInputMode; /*!< Hold trim input. */
    bool enableDcdcTimeout;               /*!< Enable internal count for DCDC_OK timeout. */
    bool enableSwitchingConverterOutput;  /*!< Enable the VDDIO switching converter output.*/
} dcdc_config_t;

/*!
 * @brief Configuration for min power setting.
 */
typedef struct _dcdc_min_power_config
{
    bool enableUseHalfFreqForContinuous; /*!< Set DCDC clock to half frequency for the continuous mode. */
} dcdc_min_power_config_t;

/*!
 * @brief Configuration for DCDC detection.
 */
typedef struct _dcdc_detection_config
{
    bool enableXtalokDetection;               /*!< Enable xtalok detection circuit. */
    bool powerDownOverVoltageVdd1P8Detection; /*!< Power down over-voltage detection comparator for VDD1P8. */
    bool powerDownOverVoltageVdd1P0Detection; /*!< Power down over-voltage detection comparator for VDD1P0. */
    bool powerDownLowVoltageDetection;        /*!< Power down low-voltage detection comparator. */
    bool powerDownOverCurrentDetection;       /*!< Power down over-current detection. */
    bool powerDownPeakCurrentDetection;       /*!< Power down peak-current detection. */
    bool powerDownZeroCrossDetection; /*!< Power down the zero cross detection function for discontinuous conductor
                                         mode. */
    dcdc_peak_current_threshold_t PeakCurrentThreshold; /*!< The threshold of peak current detection. */
} dcdc_detection_config_t;

/*!
 * @brief Configuration for the loop control.
 */
typedef struct _dcdc_loop_control_config
{
    bool enableCommonHysteresis;         /*!< Enable hysteresis in switching converter common mode analog comparators.
                                              This feature will improve transient supply ripple and efficiency. */
    bool enableCommonThresholdDetection; /*!< Increase the threshold detection for common mode analog comparator. */
    bool enableDifferentialHysteresis;   /*!< Enable hysteresis in switching converter differential mode analog
                                              comparators. This feature will improve transient supply ripple and
                                              efficiency. */
    bool enableDifferentialThresholdDetection; /*!< Increase the threshold detection for differential mode analog
                                                    comparators. */
    bool enableInvertHysteresisSign;           /*!< Invert the sign of the hysteresis in DC-DC analog comparators. */
    bool enableRCThresholdDetection;           /*!< Increase the threshold detection for RC scale circuit. */
    uint32_t enableRCScaleCircuit;      /*!< Available range is 0~7. Enable analog circuit of DC-DC converter to respond
                                             faster under transient load conditions. */
    uint32_t complementFeedForwardStep; /*!< Available range is 0~7. Two's complement feed forward step in duty cycle in
                                           the switching DC-DC converter. Each time this field makes a transition from
                                           0x0, the loop filter of the DC-DC converter is stepped once by a value
                                           proportional to the change. This can be used to force a certain control loop
                                           behavior, such as improving response under known heavy load transients. */
    uint32_t controlParameterMagnitude; /*!< Available range is 0~15. Magnitude of proportional control parameter in the
                                           switching DC-DC converter control loop. */
    uint32_t integralProportionalRatio; /*!< Available range is 0~3.Ratio of integral control parameter to proportional
                                           control parameter in the switching DC-DC converter, and can be used to
                                           optimize efficiency and loop response. */
} dcdc_loop_control_config_t;

/*!
 * @brief Configuration for DCDC internal regulator.
 */
typedef struct _dcdc_internal_regulator_config
{
    uint32_t feedbackPoint; /*!< Available range is 0~3. Select the feedback point of the internal regulator. */
} dcdc_internal_regulator_config_t;

/*!
 * @brief Configuration for DCDC low power.
 */
typedef struct _dcdc_low_power_config
{
    bool enableAdjustHystereticValue; /*!< Adjust hysteretic value in low power from 12.5mV to 25mV. */
} dcdc_low_power_config_t;

/*!
 * @brief DCDC configuration in set point mode.
 */
typedef struct _dcdc_setpoint_config
{
    uint32_t enableDCDCMap;     /*!< The setpoint map that enable the DCDC module. Should be the OR'ed value of @ref
                                   _dcdc_setpoint_map. */
    uint32_t enableDigLogicMap; /*!< The setpoint map that enable the DCDC dig logic. Should be the OR'ed value of @ref
                                   _dcdc_setpoint_map. */
    uint32_t lowpowerMap; /*!< The setpoint map that enable the DCDC Low powermode. Should be the OR'ed value of @ref
                              _dcdc_setpoint_map. */
    uint32_t standbyMap;  /*!< The setpoint map that enable the DCDC standby mode. Should be the OR'ed value of @ref
                              _dcdc_setpoint_map. */
    uint32_t standbyLowpowerMap; /*!< The setpoint map that enable the DCDC low power mode, when the related setpoint is
                                    in standby mode. Please refer to @ref _dcdc_setpoint_map. */
    dcdc_buck_mode_1P8_target_vol_t *buckVDD1P8TargetVoltage; /*!< Point to the array that store the target voltage
                                                                 level of VDD1P8 in buck mode, please refer to
                                                                 @ref dcdc_buck_mode_1P8_target_vol_t. Note that the
                                                                 pointed array must have 16 elements. */
    dcdc_buck_mode_1P0_target_vol_t *buckVDD1P0TargetVoltage; /*!< Point to the array that store the target voltage
                                                                 level of VDD1P0 in buck mode, please refer to
                                                                 @ref dcdc_buck_mode_1P0_target_vol_t. Note that the
                                                                 pointed array must have 16 elements. */
    dcdc_standby_mode_1P8_target_vol_t *standbyVDD1P8TargetVoltage; /*!< Point to the array that store the target
                                                                voltage level of VDD1P8 in standby mode, please
                                                                refer to @ref dcdc_standby_mode_1P8_target_vol_t.
                                                                Note that the pointed array must have 16 elements. */
    dcdc_standby_mode_1P0_target_vol_t *standbyVDD1P0TargetVoltage; /*!< Point to the array that store the target
                                                                voltage level of VDD1P0 in standby mode, please
                                                                refer to @ref dcdc_standby_mode_1P0_target_vol_t.
                                                                Note that the pointed array must have 16 elements. */
} dcdc_setpoint_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @name Initialization and De-initialization Interfaces
 * @{
 */

/*!
 * @brief Initializes the basic resource of DCDC module, such as control mode, etc.
 *
 * @param base DCDC peripheral base address.
 * @param config Pointer to the @ref dcdc_config_t structure.
 */
void DCDC_Init(DCDC_Type *base, const dcdc_config_t *config);

/*!
 * @brief De-initializes the DCDC module.
 *
 * @param base DCDC peripheral base address.
 */
void DCDC_Deinit(DCDC_Type *base);

/*!
 * @brief Gets the default setting for DCDC, such as control mode, etc.
 *
 * This function initializes the user configuration structure to a default value. The default values are:
 * @code
 *   config->controlMode                    = kDCDC_StaticControl;
 *   config->trimInputMode                  = kDCDC_SampleTrimInput;
 *   config->enableDcdcTimeout              = false;
 *   config->enableSwitchingConverterOutput = false;
 * @endcode
 *
 * @param config Pointer to configuration structure. See to @ref dcdc_config_t.
 */
void DCDC_GetDefaultConfig(dcdc_config_t *config);

/*! @} */

/*!
 * @name Power Mode Related Interfaces
 * @{
 */

/*!
 * @brief Makes the DCDC enter into low power mode for GPC standby request or not.
 *
 * @param base DCDC peripheral base address.
 * @param enable Used to control the behavior.
 *           - \b true Makes DCDC enter into low power mode for GPC standby mode.
 */
static inline void DCDC_EnterLowPowerModeViaStandbyRequest(DCDC_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL0 |= DCDC_CTRL0_STBY_LP_MODE_EN_MASK;
    }
    else
    {
        base->CTRL0 &= ~DCDC_CTRL0_STBY_LP_MODE_EN_MASK;
    }
}

/*!
 * @brief Makes DCDC enter into low power mode or not, before entering low power mode must disable stepping for VDD1P8
 * and VDD1P0.
 *
 * @param base DCDC peripheral base address.
 * @param enable Used to control the behavior.
 *           - \b true Makes DCDC enter into low power mode.
 */
static inline void DCDC_EnterLowPowerMode(DCDC_Type *base, bool enable)
{
    if (enable)
    {
        base->REG3 |= DCDC_REG3_VDD1P8CTRL_DISABLE_STEP_MASK | DCDC_REG3_VDD1P0CTRL_DISABLE_STEP_MASK;
        base->CTRL0 |= DCDC_CTRL0_LP_MODE_EN_MASK;
    }
    else
    {
        base->CTRL0 &= ~DCDC_CTRL0_LP_MODE_EN_MASK;
    }
}

/*!
 * @brief Makes DCDC enter into standby mode or not.
 *
 * @param base DCDC peripheral base address.
 * @param enable Used to control the behavior.
 *          - \b true Makes DCDC enter into standby mode.
 */
static inline void DCDC_EnterStandbyMode(DCDC_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL0 |= DCDC_CTRL0_STBY_EN_MASK;
    }
    else
    {
        base->CTRL0 &= ~DCDC_CTRL0_STBY_EN_MASK;
    }
}

/*! @} */

/*!
 * @name Outputs' Target Voltage Related Interfaces
 * @{
 */

/*!
 * @brief Sets the target value(ranges from 0.625V to 1.4V) of VDD1P0 in standby mode, 25mV each step.
 *
 * @param base DCDC peripheral base address.
 * @param targetVoltage The target value of VDD1P0 in standby mode, see @ref dcdc_standby_mode_1P0_target_vol_t.
 */
static inline void DCDC_SetVDD1P0StandbyModeTargetVoltage(DCDC_Type *base,
                                                          dcdc_standby_mode_1P0_target_vol_t targetVoltage)
{
    base->REG3 &= ~DCDC_REG3_VDD1P0CTRL_DISABLE_STEP_MASK;
    base->CTRL1 =
        ((base->CTRL1) & (~DCDC_CTRL1_VDD1P0CTRL_STBY_TRG_MASK)) | DCDC_CTRL1_VDD1P0CTRL_STBY_TRG(targetVoltage);
    while (DCDC_REG0_STS_DC_OK_MASK != (DCDC_REG0_STS_DC_OK_MASK & base->REG0))
    {
    }
}

/*!
 * @brief Gets the target value of VDD1P0 in standby mode, the result takes "mV" as the unit.
 *
 * @param base DCDC peripheral base address.
 *
 * @return The VDD1P0's voltage value in standby mode and the unit is "mV".
 */
static inline uint16_t DCDC_GetVDD1P0StandbyModeTargetVoltage(DCDC_Type *base)
{
    const uint16_t vdd1P0TargetVoltage[] = STANDBY_MODE_VDD1P0_TARGET_VOLTAGE;
    uint32_t voltageValue = (base->CTRL1 & DCDC_CTRL1_VDD1P0CTRL_STBY_TRG_MASK) >> DCDC_CTRL1_VDD1P0CTRL_STBY_TRG_SHIFT;

    return vdd1P0TargetVoltage[voltageValue];
}

/*!
 * @brief Sets the target value(ranges from 1.525V to 2.3V) of VDD1P8 in standby mode, 25mV each step.
 *
 * @param base DCDC peripheral base address.
 * @param targetVoltage The target value of VDD1P8 in standby mode, see @ref dcdc_standby_mode_1P8_target_vol_t.
 */
static inline void DCDC_SetVDD1P8StandbyModeTargetVoltage(DCDC_Type *base,
                                                          dcdc_standby_mode_1P8_target_vol_t targetVoltage)
{
    base->REG3 &= ~DCDC_REG3_VDD1P8CTRL_DISABLE_STEP_MASK;
    base->CTRL1 =
        ((base->CTRL1) & (~DCDC_CTRL1_VDD1P0CTRL_STBY_TRG_MASK)) | DCDC_CTRL1_VDD1P0CTRL_STBY_TRG(targetVoltage);
    while (DCDC_REG0_STS_DC_OK_MASK != (DCDC_REG0_STS_DC_OK_MASK & base->REG0))
    {
    }
}

/*!
 * @brief Gets the target value of VDD1P8 in standby mode, the result takes "mV" as the unit.
 *
 * @param base DCDC peripheral base address.
 *
 * @return The VDD1P8's voltage value in standby mode and the unit is "mV".
 */
static inline uint16_t DCDC_GetVDD1P8StandbyModeTargetVoltage(DCDC_Type *base)
{
    const uint16_t vdd1P8TargetVoltage[] = STANDBY_MODE_VDD1P8_TARGET_VOLTAGE;
    uint32_t voltageValue = (base->CTRL1 & DCDC_CTRL1_VDD1P8CTRL_STBY_TRG_MASK) >> DCDC_CTRL1_VDD1P8CTRL_STBY_TRG_SHIFT;

    return vdd1P8TargetVoltage[voltageValue];
}

/*!
 * @brief Sets the target value(ranges from 0.6V to 1.375V) of VDD1P0 in buck mode, 25mV each step.
 *
 * @param base DCDC peripheral base address.
 * @param targetVoltage The target value of VDD1P0 in buck mode, see @ref dcdc_buck_mode_1P0_target_vol_t.
 */
static inline void DCDC_SetVDD1P0BuckModeTargetVoltage(DCDC_Type *base, dcdc_buck_mode_1P0_target_vol_t targetVoltage)
{
    base->REG3 &= ~DCDC_REG3_VDD1P0CTRL_DISABLE_STEP_MASK;
    base->CTRL1 = ((base->CTRL1 & (~DCDC_CTRL1_VDD1P0CTRL_TRG_MASK)) | DCDC_CTRL1_VDD1P0CTRL_TRG(targetVoltage));
    while (DCDC_REG0_STS_DC_OK_MASK != (DCDC_REG0_STS_DC_OK_MASK & base->REG0))
    {
    }
}

/*!
 * @brief Gets the target value of VDD1P0 in buck mode, the result takes "mV" as the unit.
 *
 * @param base DCDC peripheral base address.
 *
 * @return The VDD1P0's voltage value in buck mode and the unit is "mV".
 */
static inline uint16_t DCDC_GetVDD1P0BuckModeTargetVoltage(DCDC_Type *base)
{
    const uint16_t vdd1P0TargetVoltage[] = BUCK_MODE_VDD1P0_TARGET_VOLTAGE;
    uint32_t voltageValue = (base->CTRL1 & DCDC_CTRL1_VDD1P0CTRL_TRG_MASK) >> DCDC_CTRL1_VDD1P0CTRL_TRG_SHIFT;

    return vdd1P0TargetVoltage[voltageValue];
}

/*!
 * @brief Sets the target value(ranges from 1.5V to 2.275V) of VDD1P8 in buck mode, 25mV each step.
 *
 * @param base DCDC peripheral base address.
 * @param targetVoltage The target value of VDD1P8 in buck mode, see @ref dcdc_buck_mode_1P8_target_vol_t.
 */
static inline void DCDC_SetVDD1P8BuckModeTargetVoltage(DCDC_Type *base, dcdc_buck_mode_1P8_target_vol_t targetVoltage)
{
    base->REG3 &= ~DCDC_REG3_VDD1P8CTRL_DISABLE_STEP_MASK;
    base->CTRL1 = ((base->CTRL1 & (~DCDC_CTRL1_VDD1P8CTRL_TRG_MASK)) | DCDC_CTRL1_VDD1P8CTRL_TRG(targetVoltage));
    while (DCDC_REG0_STS_DC_OK_MASK != (DCDC_REG0_STS_DC_OK_MASK & base->REG0))
    {
    }
}

/*!
 * @brief Gets the target value of VDD1P8 in buck mode, the result takes "mV" as the unit.
 *
 * @param base DCDC peripheral base address.
 *
 * @return The VDD1P8's voltage value in buck mode and the unit is "mV".
 */
static inline uint16_t DCDC_GetVDD1P8BuckModeTargetVoltage(DCDC_Type *base)
{
    const uint16_t vdd1P8TargetVoltage[] = BUCK_MODE_VDD1P8_TARGET_VOLTAGE;
    uint32_t voltageValue = (base->CTRL1 & DCDC_CTRL1_VDD1P8CTRL_TRG_MASK) >> DCDC_CTRL1_VDD1P8CTRL_TRG_SHIFT;

    return vdd1P8TargetVoltage[voltageValue];
}

/*!
 * @brief Enables/Disables stepping for VDD1P0, before entering low power modes the stepping for VDD1P0 must be
 * disabled.
 *
 * @param base DCDC peripheral base address.
 * @param enable Used to control the behavior.
 *            - \b true Enables stepping for VDD1P0.
 *            - \b false Disables stepping for VDD1P0.
 */
static inline void DCDC_EnableVDD1P0TargetVoltageStepping(DCDC_Type *base, bool enable)
{
    if (enable)
    {
        base->REG3 &= ~DCDC_REG3_VDD1P0CTRL_DISABLE_STEP_MASK;
    }
    else
    {
        base->REG3 |= DCDC_REG3_VDD1P0CTRL_DISABLE_STEP_MASK;
    }
}

/*!
 * @brief Enables/Disables stepping for VDD1P8, before entering low power modes the stepping for VDD1P8 must be
 * disabled.
 *
 * @param base DCDC peripheral base address.
 * @param enable Used to control the behavior.
 *            - \b true Enables stepping for VDD1P8.
 *            - \b false Disables stepping for VDD1P8.
 */
static inline void DCDC_EnableVDD1P8TargetVoltageStepping(DCDC_Type *base, bool enable)
{
    if (enable)
    {
        base->REG3 &= ~DCDC_REG3_VDD1P8CTRL_DISABLE_STEP_MASK;
    }
    else
    {
        base->REG3 |= DCDC_REG3_VDD1P8CTRL_DISABLE_STEP_MASK;
    }
}

/*! @} */

/*!
 * @name Detection Related Inferfaces
 * @{
 */

/*!
 * @brief Gets the default setting for detection configuration.
 *
 * The default configuration are set according to responding registers' setting when powered on.
 * They are:
 * @code
 *   config->enableXtalokDetection = false;
 *   config->powerDownOverVoltageVdd1P8Detection = true;
 *   config->powerDownOverVoltageVdd1P0Detection = true;
 *   config->powerDownLowVoltageDetection  = false;
 *   config->powerDownOverCurrentDetection = true;
 *   config->powerDownPeakCurrentDetection = true;
 *   config->powerDownZeroCrossDetection   = true;
 *   config->OverCurrentThreshold          = kDCDC_OverCurrentThresholdAlt0;
 *   config->PeakCurrentThreshold          = kDCDC_PeakCurrentThresholdAlt0;
 * @endcode
 *
 * @param config Pointer to configuration structure. See to @ref dcdc_detection_config_t.
 */
void DCDC_GetDefaultDetectionConfig(dcdc_detection_config_t *config);

/*!
 * @brief Configures the DCDC detection.
 *
 * @param base DCDC peripheral base address.
 * @param config Pointer to configuration structure. See to @ref dcdc_detection_config_t.
 */
void DCDC_SetDetectionConfig(DCDC_Type *base, const dcdc_detection_config_t *config);

/*! @} */

/*!
 * @name DCDC Miscellaneous Inferfaces
 * @{
 */

/*!
 * @brief Enables/Disables the output range comparator.
 *
 * The output range comparator is disabled by default.
 *
 * @param base DCDC peripheral base address.
 * @param enable Enable the feature or not.
 *             - \b true Enable the output range comparator.
 *             - \b false Disable the output range comparator.
 */
static inline void DCDC_EnableOutputRangeComparator(DCDC_Type *base, bool enable)
{
    if (enable)
    {
        base->REG0 &= ~DCDC_REG0_PWD_CMP_OFFSET_MASK;
    }
    else
    {
        base->REG0 |= DCDC_REG0_PWD_CMP_OFFSET_MASK;
    }
}

/*!
 * @brief Configures the DCDC clock source.
 *
 * @param base DCDC peripheral base address.
 * @param clockSource Clock source for DCDC. See to @ref dcdc_clock_source_t.
 */
void DCDC_SetClockSource(DCDC_Type *base, dcdc_clock_source_t clockSource);

/*!
 * @brief Gets the default setting for low power configuration.
 *
 * The default configuration are set according to responding registers' setting when powered on.
 * They are:
 * @code
 *   config->enableAdjustHystereticValue = false;
 * @endcode
 *
 * @param config Pointer to configuration structure. See to @ref dcdc_low_power_config_t.
 */
void DCDC_GetDefaultLowPowerConfig(dcdc_low_power_config_t *config);

/*!
 * @brief Configures the DCDC low power.
 *
 * @param base DCDC peripheral base address.
 * @param config Pointer to configuration structure. See to @ref dcdc_low_power_config_t.
 */
void DCDC_SetLowPowerConfig(DCDC_Type *base, const dcdc_low_power_config_t *config);

/*!
 * @brief Sets the bangap trim value(0~31) to trim bandgap voltage.
 *
 * @param base DCDC peripheral base address.
 * @param trimValue The bangap trim value. Available range is 0U-31U.
 */
static inline void DCDC_SetBandgapVoltageTrimValue(DCDC_Type *base, uint32_t trimValue)
{
    base->REG1 &= ~DCDC_REG1_VBG_TRIM_MASK;
    base->REG1 |= DCDC_REG1_VBG_TRIM(trimValue);
}

/*!
 * @brief Gets the default setting for loop control configuration.
 *
 * The default configuration are set according to responding registers' setting when powered on.
 * They are:
 * @code
 *   config->enableCommonHysteresis = false;
 *   config->enableCommonThresholdDetection = false;
 *   config->enableInvertHysteresisSign = false;
 *   config->enableRCThresholdDetection = false;
 *   config->enableRCScaleCircuit = 0U;
 *   config->complementFeedForwardStep = 0U;
 *   config->controlParameterMagnitude = 2U;
 *   config->integralProportionalRatio = 2U;
 * @endcode
 *
 * @param config Pointer to configuration structure. See to @ref dcdc_loop_control_config_t.
 */
void DCDC_GetDefaultLoopControlConfig(dcdc_loop_control_config_t *config);

/*!
 * @brief Configures the DCDC loop control.
 *
 * @param base DCDC peripheral base address.
 * @param config Pointer to configuration structure. See to @ref dcdc_loop_control_config_t.
 */
void DCDC_SetLoopControlConfig(DCDC_Type *base, const dcdc_loop_control_config_t *config);

/*!
 * @brief Configures for the min power.
 *
 * @param base DCDC peripheral base address.
 * @param config Pointer to configuration structure. See to @ref dcdc_min_power_config_t.
 */
void DCDC_SetMinPowerConfig(DCDC_Type *base, const dcdc_min_power_config_t *config);

/*!
 * @brief Sets the current bias of low power comparator.
 *
 * @param base DCDC peripheral base address.
 * @param biasValue The current bias of low power comparator. Refer to @ref dcdc_comparator_current_bias_t.
 */
static inline void DCDC_SetLPComparatorBiasValue(DCDC_Type *base, dcdc_comparator_current_bias_t biasValue)
{
    base->REG1 &= ~DCDC_REG1_LP_CMP_ISRC_SEL_MASK;
    base->REG1 |= DCDC_REG1_LP_CMP_ISRC_SEL(biasValue);
}

/*!
 * @brief Configures the DCDC internal regulator.
 *
 * @param base DCDC peripheral base address.
 * @param config Pointer to configuration structure. See to @ref dcdc_internal_regulator_config_t.
 */
void DCDC_SetInternalRegulatorConfig(DCDC_Type *base, const dcdc_internal_regulator_config_t *config);

/*!
 * @brief Adjusts delay to reduce ground noise.
 *
 * @param base DCDC peripheral base address.
 * @param enable Enable the feature or not.
 */
static inline void DCDC_EnableAdjustDelay(DCDC_Type *base, bool enable)
{
    if (enable)
    {
        base->REG3 |= DCDC_REG3_MISC_DELAY_TIMING_MASK;
    }
    else
    {
        base->REG3 &= ~DCDC_REG3_MISC_DELAY_TIMING_MASK;
    }
}

/*!
 * @brief Enables/Disables to improve the transition from heavy load to light load.
 *
 * @note It is valid while zero cross detection is enabled. If ouput exceeds the threshold, DCDC would return CCM from
 * DCM.
 *
 * @param base DCDC peripheral base address.
 * @param enable Enable the feature or not.
 */
static inline void DCDC_EnableImproveTransition(DCDC_Type *base, bool enable)
{
    if (enable)
    {
        base->REG2 |= DCDC_REG2_DCM_SET_CTRL_MASK;
    }
    else
    {
        base->REG2 &= ~DCDC_REG2_DCM_SET_CTRL_MASK;
    }
}
/*! @} */

/*!
 * @name Setpoint Control Related Interfaces
 */

/*!
 * @brief Initializes DCDC module when the control mode selected as setpoint mode.
 *
 * @note The function should be invoked in the initial step to config the
 *       DCDC via setpoint control mode.
 *
 * @param base DCDC peripheral base address.
 * @param config The pointer to the structure @ref dcdc_setpoint_config_t.
 */
void DCDC_SetPointInit(DCDC_Type *base, const dcdc_setpoint_config_t *config);

/*!
 * @brief Disable DCDC module when the control mode selected as setpoint mode.
 *
 * @param base DCDC peripheral base address.
 * @param setpointMap The map of the setpoint to disable the DCDC module,
 *                      Should be the OR'ed value of _dcdc_setpoint_map.
 */
static inline void DCDC_SetPointDeinit(DCDC_Type *base, uint32_t setpointMap)
{
    base->REG4 &= ~setpointMap;
}

/*! @} */

/*!
 * @name DCDC Status Related Interfaces
 * @{
 */

/*!
 * @brief Get DCDC status flags.
 *
 * @param base peripheral base address.
 * @return Mask of asserted status flags. See to @ref _dcdc_status_flags.
 */
static inline uint32_t DCDC_GetStatusFlags(DCDC_Type *base)
{
    return (base->REG0 & DCDC_REG0_STS_DC_OK_MASK);
}

/* @} */

/*!
 * @name Application Guideline Interfaces
 * @{
 */

/*!
 * @brief Boots DCDC into DCM(discontinous conduction mode).
 *
 * @code
 *  pwd_zcd=0x0;
 *  DM_CTRL = 1'b1;
 *  pwd_cmp_offset=0x0;
 *  dcdc_loopctrl_en_rcscale=0x3 or 0x5;
 *  DCM_set_ctrl=1'b1;
 * @endcode
 *
 * @param base DCDC peripheral base address.
 */
void DCDC_BootIntoDCM(DCDC_Type *base);

/*!
 * @brief Boots DCDC into CCM(continous conduction mode).
 *
 * @code
 *  pwd_zcd=0x1;
 *  pwd_cmp_offset=0x0;
 *  dcdc_loopctrl_en_rcscale=0x3;
 * @endcode
 *
 * @param base DCDC peripheral base address.
 */
void DCDC_BootIntoCCM(DCDC_Type *base);

/*! @} */

/*!
 * @}
 */

#endif /* __FSL_DCDC_H__ */
