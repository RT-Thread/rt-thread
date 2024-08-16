/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_TSI_V6_H_
#define FSL_TSI_V6_H_

#include "fsl_common.h"

/*!
 * @addtogroup tsi_v6_driver
 * @{
 */
/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Array of TSI clock name. */
extern const clock_ip_name_t s_tsiClock[];
/* Array of TSI peripheral base address. */
extern TSI_Type *const s_tsiBases[];
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief TSI driver version */
#define FSL_TSI_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))

/*! @brief TSI status flags macro collection */
#define ALL_FLAGS_MASK (TSI_DATA_EOSF_MASK | TSI_DATA_OUTRGF_MASK)

/*!
 * @brief TSI main clock selection.
 *
 * These constants set the tsi main clock.
 */
typedef enum _tsi_main_clock_selection
{
    kTSI_MainClockSlection_0 = 0U, /*!< Set TSI main clock frequency to 20.72MHz */
    kTSI_MainClockSlection_1 = 1U, /*!< Set TSI main clock frequency to 16.65MHz */
    kTSI_MainClockSlection_2 = 2U, /*!< Set TSI main clock frequency to 13.87MHz */
    kTSI_MainClockSlection_3 = 3U, /*!< Set TSI main clock frequency to 11.91MHz */
} tsi_main_clock_selection_t;

/*!
 * @brief TSI sensing mode selection.
 *
 * These constants set the tsi sensing mode.
 */
typedef enum _tsi_sensing_mode_selection
{
    kTSI_SensingModeSlection_Self   = 0U, /*!< Set TSI sensing mode to self-cap mode */
    kTSI_SensingModeSlection_Mutual = 1U, /*!< Set TSI sensing mode to mutual-cap mode */
} tsi_sensing_mode_selection_t;

/*!
 * @brief TSI DVOLT settings
 *
 * These bits indicate the comparator vp, vm and dvolt voltage.
 */
typedef enum _tsi_dvolt_option
{
    kTSI_DvoltOption_0 = 0U, /*!< DVOLT value option 0, the value may differ on different platforms */
    kTSI_DvoltOption_1 = 1U, /*!< DVOLT value option 1, the value may differ on different platforms */
    kTSI_DvoltOption_2 = 2U, /*!< DVOLT value option 2, the value may differ on different platforms */
    kTSI_DvoltOption_3 = 3U, /*!< DVOLT value option 3, the value may differ on different platforms */
    kTSI_DvoltOption_4 = 4U, /*!< DVOLT value option 4, the value may differ on different platforms */
    kTSI_DvoltOption_5 = 5U  /*!< DVOLT value option 5, the value may differ on different platforms */
} tsi_dvolt_option_t;

/*!
 * @brief TSI sensitivity ajustment (XDN option).
 *
 * These constants define the tsi sensitivity ajustment in self-cap mode, when TSI_MODE[S_SEN] = 1.
 */
typedef enum _tsi_sensitivity_xdn_option
{
    kTSI_SensitivityXdnOption_0 = 0U, /*!< Adjust sensitivity in self-cap mode, 1/16 */
    kTSI_SensitivityXdnOption_1 = 1U, /*!< Adjust sensitivity in self-cap mode, 1/8  */
    kTSI_SensitivityXdnOption_2 = 2U, /*!< Adjust sensitivity in self-cap mode, 1/4  */
    kTSI_SensitivityXdnOption_3 = 3U, /*!< Adjust sensitivity in self-cap mode, 1/2  */
    kTSI_SensitivityXdnOption_4 = 4U, /*!< Adjust sensitivity in self-cap mode, 1/1  */
    kTSI_SensitivityXdnOption_5 = 5U, /*!< Adjust sensitivity in self-cap mode, 2/1  */
    kTSI_SensitivityXdnOption_6 = 6U, /*!< Adjust sensitivity in self-cap mode, 4/1  */
    kTSI_SensitivityXdnOption_7 = 7U, /*!< Adjust sensitivity in self-cap mode, 8/1  */
} tsi_sensitivity_xdn_option_t;

/*!
 * @brief TSI Shield setting (S_W_SHIELD option).
 *
 * These constants define the shield pin used for HW shielding functionality. One or more shield pin can be selected.
 * The involved bitfield is not fix can change from device to device (KE16Z7 and KE17Z7 support 3 shield pins, other KE
 * serials only support 1 shield pin).
 */
typedef enum _tsi_shield
{
    kTSI_shieldAllOff  = 0U, /*!< No pin used */
    kTSI_shield0On     = 1U, /*!< Shield 0   pin used */
    kTSI_shield1On     = 2U, /*!< Shield 1   pin used */
    kTSI_shield1and0On = 3U, /*!< Shield 0,1 pins used */
    kTSI_shield2On     = 4U, /*!< Shield 2   pin used */
    kTSI_shield2and0On = 5U, /*!< Shield 2,0 pins used */
    kTSI_shield2and1On = 6U, /*!< Shield 2,1 pins used */
    kTSI_shieldAllOn   = 7U, /*!< Shield 2,1,0 pins used */
} tsi_shield_t;

/*!
 * @brief TSI sensitivity ajustment (CTRIM option).
 *
 * These constants define the tsi sensitivity ajustment in self-cap mode, when TSI_MODE[S_SEN] = 1.
 */
typedef enum _tsi_sensitivity_ctrim_option
{
    kTSI_SensitivityCtrimOption_0 = 0U, /*!< Adjust sensitivity in self-cap mode, 2.5p  */
    kTSI_SensitivityCtrimOption_1 = 1U, /*!< Adjust sensitivity in self-cap mode, 5.0p  */
    kTSI_SensitivityCtrimOption_2 = 2U, /*!< Adjust sensitivity in self-cap mode, 7.5p  */
    kTSI_SensitivityCtrimOption_3 = 3U, /*!< Adjust sensitivity in self-cap mode, 10.0p */
    kTSI_SensitivityCtrimOption_4 = 4U, /*!< Adjust sensitivity in self-cap mode, 12.5p */
    kTSI_SensitivityCtrimOption_5 = 5U, /*!< Adjust sensitivity in self-cap mode, 15.0p */
    kTSI_SensitivityCtrimOption_6 = 6U, /*!< Adjust sensitivity in self-cap mode, 17.5p */
    kTSI_SensitivityCtrimOption_7 = 7U, /*!< Adjust sensitivity in self-cap mode, 20.0p */
} tsi_sensitivity_ctrim_option_t;

/*!
 * @brief TSI current ajustment (Input current multiple).
 *
 * These constants set the tsi input current multiple in self-cap mode.
 */
typedef enum _tsi_current_multiple_input
{
    kTSI_CurrentMultipleInputValue_0 = 0U, /*!< Adjust input current multiple in self-cap mode, 1/8 */
    kTSI_CurrentMultipleInputValue_1 = 1U, /*!< Adjust input current multiple in self-cap mode, 1/4 */
} tsi_current_multiple_input_t;

/*!
 * @brief TSI current ajustment (Charge/Discharge current multiple).
 *
 * These constants set the tsi charge/discharge current multiple in self-cap mode.
 */
typedef enum _tsi_current_multiple_charge
{
    kTSI_CurrentMultipleChargeValue_0 = 0U, /*!< Adjust charge/discharge current multiple in self-cap mode, 1/16 */
    kTSI_CurrentMultipleChargeValue_1 = 1U, /*!< Adjust charge/discharge current multiple in self-cap mode, 1/8  */
    kTSI_CurrentMultipleChargeValue_2 = 2U, /*!< Adjust charge/discharge current multiple in self-cap mode, 1/4  */
    kTSI_CurrentMultipleChargeValue_3 = 3U, /*!< Adjust charge/discharge current multiple in self-cap mode, 1/2  */
    kTSI_CurrentMultipleChargeValue_4 = 4U, /*!< Adjust charge/discharge current multiple in self-cap mode, 1/1  */
    kTSI_CurrentMultipleChargeValue_5 = 5U, /*!< Adjust charge/discharge current multiple in self-cap mode, 2/1  */
    kTSI_CurrentMultipleChargeValue_6 = 6U, /*!< Adjust charge/discharge current multiple in self-cap mode, 4/1  */
    kTSI_CurrentMultipleChargeValue_7 = 7U, /*!< Adjust charge/discharge current multiple in self-cap mode, 8/1  */
} tsi_current_multiple_charge_t;

/*!
 * @brief TSI current used in vref generator
 *
 * These constants Choose the current used in vref generator.
 */
typedef enum _tsi_mutual_pre_current
{
    kTSI_MutualPreCurrent_1uA = 0U, /*!< Vref generator current is 1uA, used in mutual-cap mode */
    kTSI_MutualPreCurrent_2uA = 1U, /*!< Vref generator current is 2uA, used in mutual-cap mode */
    kTSI_MutualPreCurrent_3uA = 2U, /*!< Vref generator current is 3uA, used in mutual-cap mode */
    kTSI_MutualPreCurrent_4uA = 3U, /*!< Vref generator current is 4uA, used in mutual-cap mode */
    kTSI_MutualPreCurrent_5uA = 4U, /*!< Vref generator current is 5uA, used in mutual-cap mode */
    kTSI_MutualPreCurrent_6uA = 5U, /*!< Vref generator current is 6uA, used in mutual-cap mode */
    kTSI_MutualPreCurrent_7uA = 6U, /*!< Vref generator current is 7uA, used in mutual-cap mode */
    kTSI_MutualPreCurrent_8uA = 7U  /*!< Vref generator current is 8uA, used in mutual-cap mode */
} tsi_mutual_pre_current_t;

/*!
 * @brief TSI resistor used in pre-charge
 *
 * These constants Choose the resistor used in pre-charge.
 */
typedef enum _tsi_mutual_pre_resistor
{
    kTSI_MutualPreResistor_1k = 0U, /*!< Vref generator resistor is 1k, used in mutual-cap mode */
    kTSI_MutualPreResistor_2k = 1U, /*!< Vref generator resistor is 2k, used in mutual-cap mode */
    kTSI_MutualPreResistor_3k = 2U, /*!< Vref generator resistor is 3k, used in mutual-cap mode */
    kTSI_MutualPreResistor_4k = 3U, /*!< Vref generator resistor is 4k, used in mutual-cap mode */
    kTSI_MutualPreResistor_5k = 4U, /*!< Vref generator resistor is 5k, used in mutual-cap mode */
    kTSI_MutualPreResistor_6k = 5U, /*!< Vref generator resistor is 6k, used in mutual-cap mode */
    kTSI_MutualPreResistor_7k = 6U, /*!< Vref generator resistor is 7k, used in mutual-cap mode */
    kTSI_MutualPreResistor_8k = 7U  /*!< Vref generator resistor is 8k, used in mutual-cap mode */
} tsi_mutual_pre_resistor_t;

/*!
 * @brief TSI resistor used in I-sense generator
 *
 * These constants Choose the resistor used in I-sense generator.
 */
typedef enum _tsi_mutual_sense_resistor
{
    kTSI_MutualSenseResistor_2k5  = 0U,  /*!< I-sense resistor is 2.5k , used in mutual-cap mode */
    kTSI_MutualSenseResistor_5k   = 1U,  /*!< I-sense resistor is 5.0k , used in mutual-cap mode */
    kTSI_MutualSenseResistor_7k5  = 2U,  /*!< I-sense resistor is 7.5k , used in mutual-cap mode */
    kTSI_MutualSenseResistor_10k  = 3U,  /*!< I-sense resistor is 10.0k, used in mutual-cap mode */
    kTSI_MutualSenseResistor_12k5 = 4U,  /*!< I-sense resistor is 12.5k, used in mutual-cap mode */
    kTSI_MutualSenseResistor_15k  = 5U,  /*!< I-sense resistor is 15.0k, used in mutual-cap mode */
    kTSI_MutualSenseResistor_17k5 = 6U,  /*!< I-sense resistor is 17.5k, used in mutual-cap mode */
    kTSI_MutualSenseResistor_20k  = 7U,  /*!< I-sense resistor is 20.0k, used in mutual-cap mode */
    kTSI_MutualSenseResistor_22k5 = 8U,  /*!< I-sense resistor is 22.5k, used in mutual-cap mode */
    kTSI_MutualSenseResistor_25k  = 9U,  /*!< I-sense resistor is 25.0k, used in mutual-cap mode */
    kTSI_MutualSenseResistor_27k5 = 10U, /*!< I-sense resistor is 27.5k, used in mutual-cap mode */
    kTSI_MutualSenseResistor_30k  = 11U, /*!< I-sense resistor is 30.0k, used in mutual-cap mode */
    kTSI_MutualSenseResistor_32k5 = 12U, /*!< I-sense resistor is 32.5k, used in mutual-cap mode */
    kTSI_MutualSenseResistor_35k  = 13U, /*!< I-sense resistor is 35.0k, used in mutual-cap mode */
    kTSI_MutualSenseResistor_37k5 = 14U, /*!< I-sense resistor is 37.5k, used in mutual-cap mode */
    kTSI_MutualSenseResistor_40k  = 15U  /*!< I-sense resistor is 40.0k, used in mutual-cap mode */
} tsi_mutual_sense_resistor_t;

/*!
 * @brief TSI TX channel selection in mutual-cap mode
 *
 * These constants Choose the TX channel used in mutual-cap mode.
 */
typedef enum _tsi_mutual_tx_channel
{
    kTSI_MutualTxChannel_0 = 0U, /*!< Select channel 0 as tx0, used in mutual-cap mode */
    kTSI_MutualTxChannel_1 = 1U, /*!< Select channel 1 as tx1, used in mutual-cap mode */
    kTSI_MutualTxChannel_2 = 2U, /*!< Select channel 2 as tx2, used in mutual-cap mode */
    kTSI_MutualTxChannel_3 = 3U, /*!< Select channel 3 as tx3, used in mutual-cap mode */
    kTSI_MutualTxChannel_4 = 4U, /*!< Select channel 4 as tx4, used in mutual-cap mode */
    kTSI_MutualTxChannel_5 = 5U, /*!< Select channel 5 as tx5, used in mutual-cap mode */
} tsi_mutual_tx_channel_t;

/*!
 * @brief TSI RX channel selection in mutual-cap mode
 *
 * These constants Choose the RX channel used in mutual-cap mode.
 */
typedef enum _tsi_mutual_rx_channel
{
    kTSI_MutualRxChannel_6  = 0U, /*!< Select channel 6  as rx6, used in mutual-cap mode */
    kTSI_MutualRxChannel_7  = 1U, /*!< Select channel 7  as rx7, used in mutual-cap mode */
    kTSI_MutualRxChannel_8  = 2U, /*!< Select channel 8  as rx8, used in mutual-cap mode */
    kTSI_MutualRxChannel_9  = 3U, /*!< Select channel 9  as rx9, used in mutual-cap mode */
    kTSI_MutualRxChannel_10 = 4U, /*!< Select channel 10 as rx10, used in mutual-cap mode */
    kTSI_MutualRxChannel_11 = 5U, /*!< Select channel 11 as rx11, used in mutual-cap mode */
} tsi_mutual_rx_channel_t;

/*!
 * @brief TSI sensitivity boost current settings
 *
 * These constants set the sensitivity boost current.
 */
typedef enum _tsi_mutual_sense_boost_current
{
    kTSI_MutualSenseBoostCurrent_0uA  = 0U,  /*!< Sensitivity boost current is 0uA , used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_2uA  = 1U,  /*!< Sensitivity boost current is 2uA , used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_4uA  = 2U,  /*!< Sensitivity boost current is 4uA , used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_6uA  = 3U,  /*!< Sensitivity boost current is 6uA , used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_8uA  = 4U,  /*!< Sensitivity boost current is 8uA , used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_10uA = 5U,  /*!< Sensitivity boost current is 10uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_12uA = 6U,  /*!< Sensitivity boost current is 12uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_14uA = 7U,  /*!< Sensitivity boost current is 14uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_16uA = 8U,  /*!< Sensitivity boost current is 16uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_18uA = 9U,  /*!< Sensitivity boost current is 18uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_20uA = 10U, /*!< Sensitivity boost current is 20uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_22uA = 11U, /*!< Sensitivity boost current is 22uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_24uA = 12U, /*!< Sensitivity boost current is 24uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_26uA = 13U, /*!< Sensitivity boost current is 26uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_28uA = 14U, /*!< Sensitivity boost current is 28uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_30uA = 15U, /*!< Sensitivity boost current is 30uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_32uA = 16U, /*!< Sensitivity boost current is 32uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_34uA = 17U, /*!< Sensitivity boost current is 34uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_36uA = 18U, /*!< Sensitivity boost current is 36uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_38uA = 19U, /*!< Sensitivity boost current is 38uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_40uA = 20U, /*!< Sensitivity boost current is 40uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_42uA = 21U, /*!< Sensitivity boost current is 42uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_44uA = 22U, /*!< Sensitivity boost current is 44uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_46uA = 23U, /*!< Sensitivity boost current is 46uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_48uA = 24U, /*!< Sensitivity boost current is 48uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_50uA = 25U, /*!< Sensitivity boost current is 50uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_52uA = 26U, /*!< Sensitivity boost current is 52uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_54uA = 27U, /*!< Sensitivity boost current is 54uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_56uA = 28U, /*!< Sensitivity boost current is 56uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_58uA = 29U, /*!< Sensitivity boost current is 58uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_60uA = 30U, /*!< Sensitivity boost current is 60uA, used in mutual-cap mode */
    kTSI_MutualSenseBoostCurrent_62uA = 31U  /*!< Sensitivity boost current is 62uA, used in mutual-cap mode */
} tsi_mutual_sense_boost_current_t;

/*!
 * @brief TSI TX drive mode control
 *
 * These constants Choose the TX drive mode control setting.
 */
typedef enum _tsi_mutual_tx_drive_mode
{
    kTSI_MutualTxDriveModeOption_0 = 0U, /*!< TX drive mode is -5v ~ +5v, used in mutual-cap mode */
    kTSI_MutualTxDriveModeOption_1 = 1U, /*!< TX drive mode is  0v ~ +5v, used in mutual-cap mode */
} tsi_mutual_tx_drive_mode_t;

/*!
 * @brief TSI Pmos current mirror selection on the left side
 *
 * These constants set the Pmos current mirror on the left side used in mutual-cap mode.
 */
typedef enum _tsi_mutual_pmos_current_left
{
    kTSI_MutualPmosCurrentMirrorLeft_4  = 0U, /*!< Set Pmos current mirror left value as 4,  used in mutual-cap mode */
    kTSI_MutualPmosCurrentMirrorLeft_8  = 1U, /*!< Set Pmos current mirror left value as 8,  used in mutual-cap mode */
    kTSI_MutualPmosCurrentMirrorLeft_12 = 2U, /*!< Set Pmos current mirror left value as 12, used in mutual-cap mode */
    kTSI_MutualPmosCurrentMirrorLeft_16 = 3U, /*!< Set Pmos current mirror left value as 16, used in mutual-cap mode */
    kTSI_MutualPmosCurrentMirrorLeft_20 = 4U, /*!< Set Pmos current mirror left value as 20, used in mutual-cap mode */
    kTSI_MutualPmosCurrentMirrorLeft_24 = 5U, /*!< Set Pmos current mirror left value as 24, used in mutual-cap mode */
    kTSI_MutualPmosCurrentMirrorLeft_28 = 6U, /*!< Set Pmos current mirror left value as 28, used in mutual-cap mode */
    kTSI_MutualPmosCurrentMirrorLeft_32 = 7U, /*!< Set Pmos current mirror left value as 32, used in mutual-cap mode */
} tsi_mutual_pmos_current_left_t;

/*!
 * @brief TSI Pmos current mirror selection on the right side
 *
 * These constants set the Pmos current mirror on the right side used in mutual-cap mode.
 */
typedef enum _tsi_mutual_pmos_current_right
{
    kTSI_MutualPmosCurrentMirrorRight_1 = 0U, /*!< Set Pmos current mirror right value as 1, used in mutual-cap mode */
    kTSI_MutualPmosCurrentMirrorRight_2 = 1U, /*!< Set Pmos current mirror right value as 2, used in mutual-cap mode */
    kTSI_MutualPmosCurrentMirrorRight_3 = 2U, /*!< Set Pmos current mirror right value as 3, used in mutual-cap mode */
    kTSI_MutualPmosCurrentMirrorRight_4 = 3U, /*!< Set Pmos current mirror right value as 4, used in mutual-cap mode */
} tsi_mutual_pmos_current_right_t;

/*!
 * @brief TSI Nmos current mirror selection
 *
 * These constants set the Nmos current mirror used in mutual-cap mode.
 */
typedef enum _tsi_mutual_nmos_current
{
    kTSI_MutualNmosCurrentMirror_1 = 0U, /*!< Set Nmos current mirror value as 1, used in mutual-cap mode */
    kTSI_MutualNmosCurrentMirror_2 = 1U, /*!< Set Nmos current mirror value as 2, used in mutual-cap mode */
    kTSI_MutualNmosCurrentMirror_3 = 2U, /*!< Set Nmos current mirror value as 3, used in mutual-cap mode */
    kTSI_MutualNmosCurrentMirror_4 = 3U, /*!< Set Nmos current mirror value as 4, used in mutual-cap mode */
} tsi_mutual_nmos_current_t;

/*!
 * @brief TSI SINC cutoff divider setting
 *
 * These bits set the SINC cutoff divider.
 */
typedef enum _tsi_sinc_cutoff_div
{
    kTSI_SincCutoffDiv_1   = 0U, /*!< Set SINC cutoff divider as 1   */
    kTSI_SincCutoffDiv_2   = 1U, /*!< Set SINC cutoff divider as 2   */
    kTSI_SincCutoffDiv_4   = 2U, /*!< Set SINC cutoff divider as 4   */
    kTSI_SincCutoffDiv_8   = 3U, /*!< Set SINC cutoff divider as 8   */
    kTSI_SincCutoffDiv_16  = 4U, /*!< Set SINC cutoff divider as 16  */
    kTSI_SincCutoffDiv_32  = 5U, /*!< Set SINC cutoff divider as 32  */
    kTSI_SincCutoffDiv_64  = 6U, /*!< Set SINC cutoff divider as 64  */
    kTSI_SincCutoffDiv_128 = 7U  /*!< Set SINC cutoff divider as 128 */
} tsi_sinc_cutoff_div_t;

/*!
 * @brief TSI SINC filter order setting
 *
 * These bits set the SINC filter order.
 */
typedef enum _tsi_sinc_filter_order
{
    kTSI_SincFilterOrder_1 = 0U, /*!< Use 1 order SINC filter */
    kTSI_SincFilterOrder_2 = 1U, /*!< Use 1 order SINC filter */
} tsi_sinc_filter_order_t;

/*!
 * @brief TSI SINC decimation value setting
 *
 * These bits set the SINC decimation value.
 */
typedef enum _tsi_sinc_decimation_value
{
    kTSI_SincDecimationValue_1  = 0U,  /*!< The TSI_DATA[TSICH] bits is the counter value of 1  triger period. */
    kTSI_SincDecimationValue_2  = 1U,  /*!< The TSI_DATA[TSICH] bits is the counter value of 2  triger period. */
    kTSI_SincDecimationValue_3  = 2U,  /*!< The TSI_DATA[TSICH] bits is the counter value of 3  triger period. */
    kTSI_SincDecimationValue_4  = 3U,  /*!< The TSI_DATA[TSICH] bits is the counter value of 4  triger period. */
    kTSI_SincDecimationValue_5  = 4U,  /*!< The TSI_DATA[TSICH] bits is the counter value of 5  triger period. */
    kTSI_SincDecimationValue_6  = 5U,  /*!< The TSI_DATA[TSICH] bits is the counter value of 6  triger period. */
    kTSI_SincDecimationValue_7  = 6U,  /*!< The TSI_DATA[TSICH] bits is the counter value of 7  triger period. */
    kTSI_SincDecimationValue_8  = 7U,  /*!< The TSI_DATA[TSICH] bits is the counter value of 8  triger period. */
    kTSI_SincDecimationValue_9  = 8U,  /*!< The TSI_DATA[TSICH] bits is the counter value of 9  triger period. */
    kTSI_SincDecimationValue_10 = 9U,  /*!< The TSI_DATA[TSICH] bits is the counter value of 10 triger period. */
    kTSI_SincDecimationValue_11 = 10U, /*!< The TSI_DATA[TSICH] bits is the counter value of 11 triger period. */
    kTSI_SincDecimationValue_12 = 11U, /*!< The TSI_DATA[TSICH] bits is the counter value of 12 triger period. */
    kTSI_SincDecimationValue_13 = 12U, /*!< The TSI_DATA[TSICH] bits is the counter value of 13 triger period. */
    kTSI_SincDecimationValue_14 = 13U, /*!< The TSI_DATA[TSICH] bits is the counter value of 14 triger period. */
    kTSI_SincDecimationValue_15 = 14U, /*!< The TSI_DATA[TSICH] bits is the counter value of 15 triger period. */
    kTSI_SincDecimationValue_16 = 15U, /*!< The TSI_DATA[TSICH] bits is the counter value of 16 triger period. */
    kTSI_SincDecimationValue_17 = 16U, /*!< The TSI_DATA[TSICH] bits is the counter value of 17 triger period. */
    kTSI_SincDecimationValue_18 = 17U, /*!< The TSI_DATA[TSICH] bits is the counter value of 18 triger period. */
    kTSI_SincDecimationValue_19 = 18U, /*!< The TSI_DATA[TSICH] bits is the counter value of 19 triger period. */
    kTSI_SincDecimationValue_20 = 19U, /*!< The TSI_DATA[TSICH] bits is the counter value of 20 triger period. */
    kTSI_SincDecimationValue_21 = 20U, /*!< The TSI_DATA[TSICH] bits is the counter value of 21 triger period. */
    kTSI_SincDecimationValue_22 = 21U, /*!< The TSI_DATA[TSICH] bits is the counter value of 22 triger period. */
    kTSI_SincDecimationValue_23 = 22U, /*!< The TSI_DATA[TSICH] bits is the counter value of 23 triger period. */
    kTSI_SincDecimationValue_24 = 23U, /*!< The TSI_DATA[TSICH] bits is the counter value of 24 triger period. */
    kTSI_SincDecimationValue_25 = 24U, /*!< The TSI_DATA[TSICH] bits is the counter value of 25 triger period. */
    kTSI_SincDecimationValue_26 = 25U, /*!< The TSI_DATA[TSICH] bits is the counter value of 26 triger period. */
    kTSI_SincDecimationValue_27 = 26U, /*!< The TSI_DATA[TSICH] bits is the counter value of 27 triger period. */
    kTSI_SincDecimationValue_28 = 27U, /*!< The TSI_DATA[TSICH] bits is the counter value of 28 triger period. */
    kTSI_SincDecimationValue_29 = 28U, /*!< The TSI_DATA[TSICH] bits is the counter value of 29 triger period. */
    kTSI_SincDecimationValue_30 = 29U, /*!< The TSI_DATA[TSICH] bits is the counter value of 30 triger period. */
    kTSI_SincDecimationValue_31 = 30U, /*!< The TSI_DATA[TSICH] bits is the counter value of 31 triger period. */
    kTSI_SincDecimationValue_32 = 31U  /*!< The TSI_DATA[TSICH] bits is the counter value of 32 triger period. */
} tsi_sinc_decimation_value_t;

/*!
 * @brief TSI SSC output bit0's period setting(SSC0[CHARGE_NUM])
 *
 * These bits set the SSC output bit0's period setting.
 */
typedef enum _tsi_ssc_charge_num
{
    kTSI_SscChargeNumValue_1  = 0U,  /*!< The SSC output bit 0's period will be 1  clock cycle of system clock. */
    kTSI_SscChargeNumValue_2  = 1U,  /*!< The SSC output bit 0's period will be 2  clock cycle of system clock. */
    kTSI_SscChargeNumValue_3  = 2U,  /*!< The SSC output bit 0's period will be 3  clock cycle of system clock. */
    kTSI_SscChargeNumValue_4  = 3U,  /*!< The SSC output bit 0's period will be 4  clock cycle of system clock. */
    kTSI_SscChargeNumValue_5  = 4U,  /*!< The SSC output bit 0's period will be 5  clock cycle of system clock. */
    kTSI_SscChargeNumValue_6  = 5U,  /*!< The SSC output bit 0's period will be 6  clock cycle of system clock. */
    kTSI_SscChargeNumValue_7  = 6U,  /*!< The SSC output bit 0's period will be 7  clock cycle of system clock. */
    kTSI_SscChargeNumValue_8  = 7U,  /*!< The SSC output bit 0's period will be 8  clock cycle of system clock. */
    kTSI_SscChargeNumValue_9  = 8U,  /*!< The SSC output bit 0's period will be 9  clock cycle of system clock. */
    kTSI_SscChargeNumValue_10 = 9U,  /*!< The SSC output bit 0's period will be 10 clock cycle of system clock. */
    kTSI_SscChargeNumValue_11 = 10U, /*!< The SSC output bit 0's period will be 11 clock cycle of system clock. */
    kTSI_SscChargeNumValue_12 = 11U, /*!< The SSC output bit 0's period will be 12 clock cycle of system clock. */
    kTSI_SscChargeNumValue_13 = 12U, /*!< The SSC output bit 0's period will be 13 clock cycle of system clock. */
    kTSI_SscChargeNumValue_14 = 13U, /*!< The SSC output bit 0's period will be 14 clock cycle of system clock. */
    kTSI_SscChargeNumValue_15 = 14U, /*!< The SSC output bit 0's period will be 15 clock cycle of system clock. */
    kTSI_SscChargeNumValue_16 = 15U, /*!< The SSC output bit 0's period will be 16 clock cycle of system clock. */
} tsi_ssc_charge_num_t;

/*!
 * @brief TSI SSC output bit1's period setting(SSC0[BASE_NOCHARGE_NUM])
 *
 * These bits set the SSC output bit1's period setting.
 */
typedef enum _tsi_ssc_nocharge_num
{
    kTSI_SscNoChargeNumValue_1 = 0U, /*!< The SSC output bit 1's basic period will be 1  clock cycle of system clock. */
    kTSI_SscNoChargeNumValue_2 = 1U, /*!< The SSC output bit 1's basic period will be 2  clock cycle of system clock. */
    kTSI_SscNoChargeNumValue_3 = 2U, /*!< The SSC output bit 1's basic period will be 3  clock cycle of system clock. */
    kTSI_SscNoChargeNumValue_4 = 3U, /*!< The SSC output bit 1's basic period will be 4  clock cycle of system clock. */
    kTSI_SscNoChargeNumValue_5 = 4U, /*!< The SSC output bit 1's basic period will be 5  clock cycle of system clock. */
    kTSI_SscNoChargeNumValue_6 = 5U, /*!< The SSC output bit 1's basic period will be 6  clock cycle of system clock. */
    kTSI_SscNoChargeNumValue_7 = 6U, /*!< The SSC output bit 1's basic period will be 7  clock cycle of system clock. */
    kTSI_SscNoChargeNumValue_8 = 7U, /*!< The SSC output bit 1's basic period will be 8  clock cycle of system clock. */
    kTSI_SscNoChargeNumValue_9 = 8U, /*!< The SSC output bit 1's basic period will be 9  clock cycle of system clock. */
    kTSI_SscNoChargeNumValue_10 =
        9U, /*!< The SSC output bit 1's basic period will be 10 clock cycle of system clock. */
    kTSI_SscNoChargeNumValue_11 =
        10U, /*!< The SSC output bit 1's basic period will be 11 clock cycle of system clock. */
    kTSI_SscNoChargeNumValue_12 =
        11U, /*!< The SSC output bit 1's basic period will be 12 clock cycle of system clock. */
    kTSI_SscNoChargeNumValue_13 =
        12U, /*!< The SSC output bit 1's basic period will be 13 clock cycle of system clock. */
    kTSI_SscNoChargeNumValue_14 =
        13U, /*!< The SSC output bit 1's basic period will be 14 clock cycle of system clock. */
    kTSI_SscNoChargeNumValue_15 =
        14U, /*!< The SSC output bit 1's basic period will be 15 clock cycle of system clock. */
    kTSI_SscNoChargeNumValue_16 =
        15U, /*!< The SSC output bit 1's basic period will be 16 clock cycle of system clock. */
} tsi_ssc_nocharge_num_t;

/*!
 * @brief TSI SSC outsel choosing the length of the PRBS (Pseudo-RandomBinarySequence) method
 * setting(SSC0[TSI_SSC0_PRBS_OUTSEL])
 *
 * These bits set the SSC PRBS length.
 */
typedef enum _tsi_ssc_prbs_outsel
{
    kTSI_SscPrbsOutsel_2  = 2U,  /*!< The length of the PRBS is 2. */
    kTSI_SscPrbsOutsel_3  = 3U,  /*!< The length of the PRBS is 3. */
    kTSI_SscPrbsOutsel_4  = 4U,  /*!< The length of the PRBS is 4. */
    kTSI_SscPrbsOutsel_5  = 5U,  /*!< The length of the PRBS is 5. */
    kTSI_SscPrbsOutsel_6  = 6U,  /*!< The length of the PRBS is 6. */
    kTSI_SscPrbsOutsel_7  = 7U,  /*!< The length of the PRBS is 7. */
    kTSI_SscPrbsOutsel_8  = 8U,  /*!< The length of the PRBS is 8. */
    kTSI_SscPrbsOutsel_9  = 9U,  /*!< The length of the PRBS is 9. */
    kTSI_SscPrbsOutsel_10 = 10U, /*!< The length of the PRBS is 10. */
    kTSI_SscPrbsOutsel_11 = 11U, /*!< The length of the PRBS is 11. */
    kTSI_SscPrbsOutsel_12 = 12U, /*!< The length of the PRBS is 12. */
    kTSI_SscPrbsOutsel_13 = 13U, /*!< The length of the PRBS is 13. */
    kTSI_SscPrbsOutsel_14 = 14U, /*!< The length of the PRBS is 14. */
    kTSI_SscPrbsOutsel_15 = 15U, /*!< The length of the PRBS is 15. */
} tsi_ssc_prbs_outsel_t;

/*! @brief TSI status flags. */
typedef enum _tsi_status_flags
{
    kTSI_EndOfScanFlag  = TSI_DATA_EOSF_MASK,       /*!< End-Of-Scan flag */
    kTSI_OutOfRangeFlag = (int)TSI_DATA_OUTRGF_MASK /*!< Out-Of-Range flag */
} tsi_status_flags_t;

/*! @brief TSI feature interrupt source.*/
typedef enum _tsi_interrupt_enable
{
    kTSI_GlobalInterruptEnable     = 1U, /*!< TSI module global interrupt */
    kTSI_OutOfRangeInterruptEnable = 2U, /*!< Out-Of-Range interrupt */
    kTSI_EndOfScanInterruptEnable  = 4U  /*!< End-Of-Scan interrupt */
} tsi_interrupt_enable_t;

/*!
 * @brief TSI SSC mode selection.
 *
 * These constants set the SSC mode.
 */
typedef enum _tsi_ssc_mode
{
    kTSI_ssc_prbs_method     = 0U, /*!< Using PRBS method generating SSC output bit. */
    kTSI_ssc_up_down_counter = 1U, /*!< Using up-down counter generating SSC output bit. */
    kTSI_ssc_dissable        = 2U, /*!< SSC function is disabled. */
} tsi_ssc_mode_t;

/*!
 * @brief TSI main clock selection.
 *
 * These constants set select the divider ratio for the clock used for generating the SSC output bit.
 */
typedef enum _tsi_ssc_prescaler
{
    kTSI_ssc_div_by_1   = 0x0U,  /*!< Set SSC divider to 00000000 div1(2^0) */
    kTSI_ssc_div_by_2   = 0x1U,  /*!< Set SSC divider to 00000001 div2(2^1) */
    kTSI_ssc_div_by_4   = 0x3U,  /*!< Set SSC divider to 00000011 div4(2^2) */
    kTSI_ssc_div_by_8   = 0x7U,  /*!< Set SSC divider to 00000111 div8(2^3) */
    kTSI_ssc_div_by_16  = 0xfU,  /*!< Set SSC divider to 00001111 div16(2^4) */
    kTSI_ssc_div_by_32  = 0x1fU, /*!< Set SSC divider to 00011111 div32(2^5) */
    kTSI_ssc_div_by_64  = 0x3fU, /*!< Set SSC divider to 00111111 div64(2^6) */
    kTSI_ssc_div_by_128 = 0x7fU, /*!< Set SSC divider to 01111111 div128(2^7) */
    kTSI_ssc_div_by_256 = 0xffU, /*!< Set SSC divider to 11111111 div256(2^8) */
} tsi_ssc_prescaler_t;

/*! @brief TSI calibration data storage. */
typedef struct _tsi_calibration_data
{
    uint16_t calibratedData[FSL_FEATURE_TSI_CHANNEL_COUNT]; /*!< TSI calibration data storage buffer */
} tsi_calibration_data_t;

/*!
 * @brief TSI common configuration structure
 *
 * This structure contains the common settings for TSI self-cap or mutual-cap mode, configurations including
 * the TSI module main clock, sensing mode, DVOLT options, SINC and SSC configurations.
 */
typedef struct _tsi_common_config
{
    tsi_main_clock_selection_t mainClock;   /*!< Set main clock. */
    tsi_sensing_mode_selection_t mode;      /*!< Choose sensing mode. */
    tsi_dvolt_option_t dvolt;               /*!< DVOLT option value.  */
    tsi_sinc_cutoff_div_t cutoff;           /*!< Cutoff divider.  */
    tsi_sinc_filter_order_t order;          /*!< SINC filter order. */
    tsi_sinc_decimation_value_t decimation; /*!< SINC decimation value. */
    tsi_ssc_charge_num_t chargeNum;         /*!< SSC High Width (t1), SSC output bit0's period setting. */
    tsi_ssc_prbs_outsel_t prbsOutsel;   /*!< SSC High Random Width (t2), length of PRBS(Pseudo-RandomBinarySequence),SSC
                                           output bit2's period setting. */
    tsi_ssc_nocharge_num_t noChargeNum; /*!< SSC Low Width (t3), SSC output bit1's period setting. */
    tsi_ssc_mode_t ssc_mode;            /*!< Clock mode selection (basic - from main clock by divider,advanced - using
                                           SSC(Switching Speed Clock) by three configurable intervals. */
    tsi_ssc_prescaler_t ssc_prescaler;  /*!< Set clock divider for basic mode. */
} tsi_common_config_t;

/*!
 * @brief TSI configuration structure for self-cap mode
 *
 * This structure contains the settings for the most common TSI self-cap configurations including
 * the TSI module charge currents, sensitivity configuration and so on.
 */
typedef struct _tsi_selfCap_config
{
    tsi_common_config_t commonConfig;            /*!< Common settings.          */
    bool enableSensitivity;                      /*!< Enable sensitivity boost of self-cap or not. */
    tsi_shield_t enableShield;                   /*!< Enable shield of self-cap mode or not. */
    tsi_sensitivity_xdn_option_t xdn;            /*!< Sensitivity XDN option.   */
    tsi_sensitivity_ctrim_option_t ctrim;        /*!< Sensitivity CTRIM option. */
    tsi_current_multiple_input_t inputCurrent;   /*!< Input current multiple.   */
    tsi_current_multiple_charge_t chargeCurrent; /*!< Charge/Discharge current multiple. */
} tsi_selfCap_config_t;

/*!
 * @brief TSI configuration structure for mutual-cap mode
 *
 * This structure contains the settings for the most common TSI mutual-cap configurations including
 * the TSI module generator settings, sensitivity related current settings and so on.
 */
typedef struct _tsi_mutualCap_config
{
    tsi_common_config_t commonConfig;                 /*!< Common settings.          */
    tsi_mutual_pre_current_t preCurrent;              /*!< Vref generator current.  */
    tsi_mutual_pre_resistor_t preResistor;            /*!< Vref generator resistor. */
    tsi_mutual_sense_resistor_t senseResistor;        /*!< I-sense generator resistor. */
    tsi_mutual_sense_boost_current_t boostCurrent;    /*!< Sensitivity boost current setting. */
    tsi_mutual_tx_drive_mode_t txDriveMode;           /*!< TX drive mode control setting. */
    tsi_mutual_pmos_current_left_t pmosLeftCurrent;   /*!< Pmos current mirror on the left side.  */
    tsi_mutual_pmos_current_right_t pmosRightCurrent; /*!< Pmos current mirror on the right side. */
    bool enableNmosMirror;                            /*!< Enable Nmos current mirror setting or not. */
    tsi_mutual_nmos_current_t nmosCurrent;            /*!< Nmos current mirror setting. */
} tsi_mutualCap_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Get the TSI instance from peripheral base address.
 *
 * @param base TSI peripheral base address.
 * @return TSI instance.
 */
uint32_t TSI_GetInstance(TSI_Type *base);

/*!
 * @brief Initialize hardware to Self-cap mode.
 *
 * @details Initialize the peripheral to the targeted state specified by parameter config,
 *          such as sets sensitivity adjustment, current settings.
 * @param  base    TSI peripheral base address.
 * @param  config  Pointer to TSI self-cap configuration structure.
 * @return none
 */
void TSI_InitSelfCapMode(TSI_Type *base, const tsi_selfCap_config_t *config);

/*!
 * @brief Initialize hardware to Mutual-cap mode.
 *
 * @details Initialize the peripheral to the targeted state specified by parameter config,
 *          such as sets Vref generator setting, sensitivity boost settings, Pmos/Nmos settings.
 * @param  base    TSI peripheral base address.
 * @param  config  Pointer to TSI mutual-cap configuration structure.
 * @return none
 */
void TSI_InitMutualCapMode(TSI_Type *base, const tsi_mutualCap_config_t *config);

/*!
 * @brief De-initialize hardware.
 *
 * @details De-initialize the peripheral to default state.
 *
 * @param  base  TSI peripheral base address.
 * @return none
 */
void TSI_Deinit(TSI_Type *base);

/*!
 * @brief Get TSI self-cap mode user configure structure.
 * This interface sets userConfig structure to a default value. The configuration structure only
 * includes the settings for the whole TSI.
 * The user configure is set to a value:
 * @code
    userConfig->commonConfig.mainClock     = kTSI_MainClockSlection_0;
    userConfig->commonConfig.mode          = kTSI_SensingModeSlection_Self;
    userConfig->commonConfig.dvolt         = kTSI_DvoltOption_2;
    userConfig->commonConfig.cutoff        = kTSI_SincCutoffDiv_1;
    userConfig->commonConfig.order         = kTSI_SincFilterOrder_1;
    userConfig->commonConfig.decimation    = kTSI_SincDecimationValue_8;
    userConfig->commonConfig.chargeNum     = kTSI_SscChargeNumValue_3;
    userConfig->commonConfig.prbsOutsel    = kTSI_SscPrbsOutsel_2;
    userConfig->commonConfig.noChargeNum   = kTSI_SscNoChargeNumValue_2;
    userConfig->commonConfig.ssc_mode      = kTSI_ssc_prbs_method;
    userConfig->commonConfig.ssc_prescaler = kTSI_ssc_div_by_1;
    userConfig->enableSensitivity          = true;
    userConfig->enableShield               = false;
    userConfig->xdn                        = kTSI_SensitivityXdnOption_1;
    userConfig->ctrim                      = kTSI_SensitivityCtrimOption_7;
    userConfig->inputCurrent               = kTSI_CurrentMultipleInputValue_0;
    userConfig->chargeCurrent              = kTSI_CurrentMultipleChargeValue_1;
   @endcode
 *
 * @param userConfig Pointer to TSI user configure structure.
 */
void TSI_GetSelfCapModeDefaultConfig(tsi_selfCap_config_t *userConfig);

/*!
 * @brief Get TSI mutual-cap mode default user configure structure.
 * This interface sets userConfig structure to a default value. The configuration structure only
 * includes the settings for the whole TSI.
 * The user configure is set to a value:
 * @code
    userConfig->commonConfig.mainClock     = kTSI_MainClockSlection_1;
    userConfig->commonConfig.mode          = kTSI_SensingModeSlection_Mutual;
    userConfig->commonConfig.dvolt         = kTSI_DvoltOption_0;
    userConfig->commonConfig.cutoff        = kTSI_SincCutoffDiv_1;
    userConfig->commonConfig.order         = kTSI_SincFilterOrder_1;
    userConfig->commonConfig.decimation    = kTSI_SincDecimationValue_8;
    userConfig->commonConfig.chargeNum     = kTSI_SscChargeNumValue_4;
    userConfig->commonConfig.prbsOutsel    = kTSI_SscPrbsOutsel_2;
    userConfig->commonConfig.noChargeNum   = kTSI_SscNoChargeNumValue_5;
    userConfig->commonConfig.ssc_mode      = kTSI_ssc_prbs_method;
    userConfig->commonConfig.ssc_prescaler = kTSI_ssc_div_by_1;
    userConfig->preCurrent                 = kTSI_MutualPreCurrent_4uA;
    userConfig->preResistor                = kTSI_MutualPreResistor_4k;
    userConfig->senseResistor              = kTSI_MutualSenseResistor_10k;
    userConfig->boostCurrent               = kTSI_MutualSenseBoostCurrent_0uA;
    userConfig->txDriveMode                = kTSI_MutualTxDriveModeOption_0;
    userConfig->pmosLeftCurrent            = kTSI_MutualPmosCurrentMirrorLeft_32;
    userConfig->pmosRightCurrent           = kTSI_MutualPmosCurrentMirrorRight_1;
    userConfig->enableNmosMirror           = true;
    userConfig->nmosCurrent                = kTSI_MutualNmosCurrentMirror_1;
   @endcode
 *
 * @param userConfig Pointer to TSI user configure structure.
 */
void TSI_GetMutualCapModeDefaultConfig(tsi_mutualCap_config_t *userConfig);

/*!
 * @brief Hardware base counter value for calibration.
 *
 * @details Calibrate the peripheral to fetch the initial counter value of
 *          the enabled channels.
 *          This API is mostly used at initial application setup, it shall be called
 *          after the TSI_Init API, then user can use the calibrated
 *          counter values to setup applications(such as to determine
 *          under which counter value we can confirm a touch event occurs).
 *
 * @param   base    TSI peripheral base address.
 * @param   calBuff Data buffer that store the calibrated counter value.
 * @return  none
 * @note    This API is mainly used for self-cap mode;
 * @note    The calibration work in mutual-cap mode shall be done in applications due to different board layout.
 *
 */
void TSI_SelfCapCalibrate(TSI_Type *base, tsi_calibration_data_t *calBuff);

/*!
 * @brief Enables TSI interrupt requests.
 * @param base TSI peripheral base address.
 * @param mask interrupt source
 *     The parameter can be combination of the following source if defined:
 *     @arg kTSI_GlobalInterruptEnable
 *     @arg kTSI_EndOfScanInterruptEnable
 *     @arg kTSI_OutOfRangeInterruptEnable
 */
void TSI_EnableInterrupts(TSI_Type *base, uint32_t mask);

/*!
 * @brief Disables TSI interrupt requests.
 * @param base TSI peripheral base address.
 * @param mask interrupt source
 *     The parameter can be combination of the following source if defined:
 *     @arg kTSI_GlobalInterruptEnable
 *     @arg kTSI_EndOfScanInterruptEnable
 *     @arg kTSI_OutOfRangeInterruptEnable
 */
void TSI_DisableInterrupts(TSI_Type *base, uint32_t mask);

/*!
 * @brief Get interrupt flag.
 * This function get tsi interrupt flags.
 *
 * @param    base  TSI peripheral base address.
 * @return         The mask of these status flags combination.
 */
static inline uint32_t TSI_GetStatusFlags(TSI_Type *base)
{
    return (base->DATA & (uint32_t)((uint32_t)kTSI_EndOfScanFlag | (uint32_t)kTSI_OutOfRangeFlag));
}

/*!
 * @brief Clear interrupt flag.
 *
 * This function clear tsi interrupt flag,
 * automatically cleared flags can not be cleared by this function.
 *
 * @param base TSI peripheral base address.
 * @param mask The status flags to clear.
 */
void TSI_ClearStatusFlags(TSI_Type *base, uint32_t mask);

/*!
 * @brief Get TSI scan trigger mode.
 *
 * @param  base  TSI peripheral base address.
 * @return       Scan trigger mode.
 */
static inline uint32_t TSI_GetScanTriggerMode(TSI_Type *base)
{
    return (base->GENCS & TSI_GENCS_STM_MASK);
}

/*!
 * @brief Enables the TSI Module or not.
 *
 * @param   base   TSI peripheral base address.
 * @param   enable Choose whether to enable or disable module;
 *                 - true   Enable TSI module;
 *                 - false  Disable TSI module;
 * @return  none.
 */
static inline void TSI_EnableModule(TSI_Type *base, bool enable)
{
    if (enable)
    {
        base->DATA  = base->DATA & ~ALL_FLAGS_MASK;
        base->GENCS = base->GENCS | TSI_GENCS_TSIEN_MASK; /* Enable module */
    }
    else
    {
        base->DATA  = base->DATA & ~ALL_FLAGS_MASK;
        base->GENCS = base->GENCS & ~TSI_GENCS_TSIEN_MASK; /* Disable module */
    }
}

/*!
 * @brief Sets the TSI low power STOP mode enable or not.
 *        This enables TSI module function in low power modes.
 *
 * @param    base    TSI peripheral base address.
 * @param    enable  Choose to enable or disable STOP mode.
 *                   - true   Enable module in STOP mode;
 *                   - false  Disable module in STOP mode;
 * @return   none.
 */
static inline void TSI_EnableLowPower(TSI_Type *base, bool enable)
{
    if (enable)
    {
        base->GENCS =
            (base->GENCS & ~ALL_FLAGS_MASK) | TSI_GENCS_STPE_MASK; /* Module enabled in low power stop modes */
    }
    else
    {
        base->GENCS =
            (base->GENCS & ~ALL_FLAGS_MASK) & (~TSI_GENCS_STPE_MASK); /* Module disabled in low power stop modes */
    }
}

/*!
 * @brief Enable the hardware trigger scan or not.
 *
 * @param    base TSI peripheral base address.
 * @param    enable Choose to enable hardware trigger or software trigger scan.
 *                  - true    Enable hardware trigger scan;
 *                  - false   Enable software trigger scan;
 * @return   none.
 */
static inline void TSI_EnableHardwareTriggerScan(TSI_Type *base, bool enable)
{
    if (enable)
    {
        base->DATA  = base->DATA & ~ALL_FLAGS_MASK;
        base->GENCS = base->GENCS | TSI_GENCS_STM_MASK; /* Enable hardware trigger scan */
    }
    else
    {
        base->DATA  = base->DATA & ~ALL_FLAGS_MASK;
        base->GENCS = base->GENCS & ~TSI_GENCS_STM_MASK; /* Enable software trigger scan */
    }
}

/*!
 * @brief Start one sotware trigger measurement (trigger a new measurement).
 *
 * @param    base TSI peripheral base address.
 * @return   none.
 */
static inline void TSI_StartSoftwareTrigger(TSI_Type *base)
{
    base->GENCS |= TSI_GENCS_SWTS_MASK;
}

/*!
 * @brief Set the measured channel number for self-cap mode.
 *
 * @param    base    TSI peripheral base address.
 * @param    channel Channel number 0 ... 24.
 * @return   none.
 * @note     This API can only be used in self-cap mode!
 */
static inline void TSI_SetSelfCapMeasuredChannel(TSI_Type *base, uint8_t channel)
{
    assert(channel < (uint8_t)FSL_FEATURE_TSI_CHANNEL_COUNT);

    base->CONFIG = ((base->CONFIG) & ~TSI_CONFIG_TSICH_MASK) | (TSI_CONFIG_TSICH(channel));
}

/*!
 * @brief Get the current measured channel number, in self-cap mode.
 *
 * @param    base    TSI peripheral base address.
 * @return   uint8_t    Channel number 0 ... 24.
 * @note     This API can only be used in self-cap mode!
 */
static inline uint8_t TSI_GetSelfCapMeasuredChannel(TSI_Type *base)
{
    return (uint8_t)((base->CONFIG & TSI_CONFIG_TSICH_MASK) >> TSI_CONFIG_TSICH_SHIFT);
}

/*!
 * @brief Decide whether to enable End of Scan DMA transfer request only.
 *
 * @param    base TSI peripheral base address.
 * @param    enable  Choose whether to enable End of Scan DMA transfer request only.
 *                   - true  Enable End of Scan DMA transfer request only;
 *                   - false Both End-of-Scan and Out-of-Range can generate DMA transfer request.
 * @return   none.
 */
static inline void TSI_EnableEndOfScanDmaTransferOnly(TSI_Type *base, bool enable)
{
    if (enable)
    {
        base->GENCS = (base->GENCS & ~ALL_FLAGS_MASK) |
                      TSI_GENCS_DMAEN_EOS_MASK; /* Enable End of Scan DMA transfer request only; */
    }
    else
    {
        base->GENCS = (base->GENCS & ~ALL_FLAGS_MASK) &
                      (~TSI_GENCS_DMAEN_EOS_MASK); /* Both types of events can generate DMA transfer request. */
    }
}

/*!
 * @brief Gets the conversion counter value.
 *
 * @param    base TSI peripheral base address.
 * @return   Accumulated scan counter value ticked by the reference clock.
 */
static inline uint16_t TSI_GetCounter(TSI_Type *base)
{
    return (uint16_t)(base->DATA & TSI_DATA_TSICNT_MASK);
}

/*!
 * @brief Set the TSI wake-up channel low threshold.
 *
 * @param    base           TSI peripheral base address.
 * @param    low_threshold  Low counter threshold.
 * @return   none.
 */
static inline void TSI_SetLowThreshold(TSI_Type *base, uint16_t low_threshold)
{
    base->TSHD = ((base->TSHD) & ~TSI_TSHD_THRESL_MASK) | (TSI_TSHD_THRESL(low_threshold));
}

/*!
 * @brief Set the TSI wake-up channel high threshold.
 *
 * @param    base            TSI peripheral base address.
 * @param    high_threshold  High counter threshold.
 * @return   none.
 */
static inline void TSI_SetHighThreshold(TSI_Type *base, uint16_t high_threshold)
{
    base->TSHD = ((base->TSHD) & ~TSI_TSHD_THRESH_MASK) | (TSI_TSHD_THRESH(high_threshold));
}

/*!
 * @brief Set the main clock of the TSI module.
 *
 * @param    base   TSI peripheral base address.
 * @param    mainClock   clock option value.
 * @return   none.
 */
static inline void TSI_SetMainClock(TSI_Type *base, tsi_main_clock_selection_t mainClock)
{
    base->GENCS = ((base->GENCS) & ~TSI_GENCS_SETCLK_MASK) | (TSI_GENCS_SETCLK(mainClock));
}

/*!
 * @brief Set the sensing mode of the TSI module.
 *
 * @param    base   TSI peripheral base address.
 * @param    mode   Mode value.
 * @return   none.
 */
static inline void TSI_SetSensingMode(TSI_Type *base, tsi_sensing_mode_selection_t mode)
{
    base->CONFIG = ((base->CONFIG) & ~TSI_CONFIG_MODE_MASK) | (TSI_CONFIG_MODE(mode));
}

/*!
 * @brief Get the sensing mode of the TSI module.
 *
 * @param    base   TSI peripheral base address.
 * @return   Currently selected sensing mode.
 */
static inline tsi_sensing_mode_selection_t TSI_GetSensingMode(TSI_Type *base)
{
    return (tsi_sensing_mode_selection_t)(uint32_t)((base->CONFIG & TSI_CONFIG_MODE_MASK) >> TSI_CONFIG_MODE_SHIFT);
}

/*!
 * @brief Set the DVOLT settings.
 *
 * @param    base    TSI peripheral base address.
 * @param    dvolt   The voltage rails.
 * @return   none.
 */
static inline void TSI_SetDvolt(TSI_Type *base, tsi_dvolt_option_t dvolt)
{
    base->GENCS = (base->GENCS & ~(TSI_GENCS_DVOLT_MASK | ALL_FLAGS_MASK)) | (TSI_GENCS_DVOLT(dvolt));
}

/*!
 * @brief Enable self-cap mode noise cancellation function or not.
 *
 * @param    base                TSI peripheral base address.
 * @param    enableCancellation  Choose whether to enable noise cancellation in self-cap mode
 *                               - true  Enable noise cancellation;
 *                               - false Disable noise cancellation;
 * @return   none.
 */
static inline void TSI_EnableNoiseCancellation(TSI_Type *base, bool enableCancellation)
{
    base->CONFIG = ((base->CONFIG) & ~TSI_CONFIG_S_NOISE_MASK) | (TSI_CONFIG_S_NOISE(enableCancellation));
}

/*!
 * @brief Set the mutual-cap mode TX channel.
 *
 * @param    base       TSI peripheral base address.
 * @param    txChannel  Mutual-cap mode TX channel number
 * @return   none.
 */
static inline void TSI_SetMutualCapTxChannel(TSI_Type *base, tsi_mutual_tx_channel_t txChannel)
{
    base->CONFIG_MUTUAL =
        ((base->CONFIG_MUTUAL) & ~TSI_CONFIG_MUTUAL_M_SEL_TX_MASK) | (TSI_CONFIG_MUTUAL_M_SEL_TX(txChannel));
}

/*!
 * @brief Get the current measured TX channel number, in mutual-cap mode.
 *
 * @param    base    TSI peripheral base address;
 * @return           Tx Channel number 0 ... 5;
 * @note     This API can only be used in mutual-cap mode!
 */
static inline tsi_mutual_tx_channel_t TSI_GetTxMutualCapMeasuredChannel(TSI_Type *base)
{
    return (tsi_mutual_tx_channel_t)(uint32_t)((base->CONFIG_MUTUAL & TSI_CONFIG_MUTUAL_M_SEL_TX_MASK) >>
                                               TSI_CONFIG_MUTUAL_M_SEL_TX_SHIFT);
}

/*!
 * @brief Set the mutual-cap mode RX channel.
 *
 * @param    base       TSI peripheral base address.
 * @param    rxChannel  Mutual-cap mode RX channel number
 * @return   none.
 */
static inline void TSI_SetMutualCapRxChannel(TSI_Type *base, tsi_mutual_rx_channel_t rxChannel)
{
    base->CONFIG_MUTUAL =
        ((base->CONFIG_MUTUAL) & ~TSI_CONFIG_MUTUAL_M_SEL_RX_MASK) | (TSI_CONFIG_MUTUAL_M_SEL_RX(rxChannel));
}

/*!
 * @brief Get the current measured RX channel number, in mutual-cap mode.
 *
 * @param    base    TSI peripheral base address;
 * @return           Rx Channel number 6 ... 11;
 * @note     This API can only be used in mutual-cap mode!
 */
static inline tsi_mutual_rx_channel_t TSI_GetRxMutualCapMeasuredChannel(TSI_Type *base)
{
    return (tsi_mutual_rx_channel_t)(uint32_t)((base->CONFIG_MUTUAL & TSI_CONFIG_MUTUAL_M_SEL_RX_MASK) >>
                                               TSI_CONFIG_MUTUAL_M_SEL_RX_SHIFT);
}

/*!
 * @brief Set the SSC clock mode of the TSI module.
 *
 * @param    base   TSI peripheral base address.
 * @param    mode   SSC mode option value.
 * @return   none.
 */
static inline void TSI_SetSscMode(TSI_Type *base, tsi_ssc_mode_t mode)
{
    base->SSC0 = ((base->SSC0) & ~TSI_SSC0_SSC_MODE_MASK) | (TSI_SSC0_SSC_MODE(mode));
}

/*!
 * @brief Set the SSC prescaler of the TSI module.
 *
 * @param    base   TSI peripheral base address.
 * @param    prescaler  SSC prescaler option value.
 * @return   none.
 */
static inline void TSI_SetSscPrescaler(TSI_Type *base, tsi_ssc_prescaler_t prescaler)
{
    base->SSC0 = ((base->SSC0) & ~TSI_SSC0_SSC_PRESCALE_NUM_MASK) | (TSI_SSC0_SSC_PRESCALE_NUM(prescaler));
}

/*!
 * @brief Set used mutual-cap TX channel.
 *
 * @param    base       TSI peripheral base address.
 * @param    txChannel  Mutual-cap mode TX channel number
 * @return   none.
 */
static inline void TSI_SetUsedTxChannel(TSI_Type *base, tsi_mutual_tx_channel_t txChannel)
{
    base->MUL = (base->MUL) | (TSI_MUL_M_TX_USED(1UL << (uint8_t)txChannel));
}

/*!
 * @brief Clear used mutual-cap TX channel.
 *
 * @param    base       TSI peripheral base address.
 * @param    txChannel  Mutual-cap mode TX channel number
 * @return   none.
 */
static inline void TSI_ClearUsedTxChannel(TSI_Type *base, tsi_mutual_tx_channel_t txChannel)
{
    base->MUL &= ~TSI_MUL_M_TX_USED(1UL << (uint8_t)txChannel);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*! @}*/

#endif /* FSL_TSI_V6_H_ */
