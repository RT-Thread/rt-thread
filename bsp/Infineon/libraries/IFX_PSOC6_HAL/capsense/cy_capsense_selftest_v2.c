/***************************************************************************//**
* \file cy_capsense_selftest.c
* \version 3.0
*
* \brief
* This file provides the source code to the Built-in Self-test (BIST)
* functions.
*
********************************************************************************
* \copyright
* Copyright 2019-2021, Cypress Semiconductor Corporation (an Infineon company)
* or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include <stddef.h>
#include <string.h>
#include "cycfg_capsense_defines.h"
#include "cy_syslib.h"
#include "cy_capsense_common.h"
#include "cy_capsense_structure.h"
#include "cy_capsense_sensing.h"
#include "cy_capsense_sensing_v2.h"
#include "cy_capsense_lib.h"
#include "cy_capsense_selftest_v2.h"
#include "cy_gpio.h"

#if (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2))

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN)

/*******************************************************************************
* Common local definitions for self-test
*******************************************************************************/

/* Port Data Register macros for BIST */
#define CY_CAPSENSE_BIST_DR_PIN2GND                             (0u)
#define CY_CAPSENSE_BIST_DR_PIN2VDD                             (1u)

#define CY_CAPSENSE_BIST_CP_MAX_VALUE                           (400000u)
#define CY_CAPSENSE_BIST_PROMILLE_FACTOR                        (1000u)
#define CY_CAPSENSE_BIST_SNS_CLK_MIN_DIVIDER                    (4u)
#define CY_CAPSENSE_BIST_SNS_CLK_MAX_DIVIDER                    (4096u)

/* Macros for the electrode capacitance measurement test */
#define CY_CAPSENSE_BIST_ELTD_CAP_MAX_RAW_PROMILLE              (450u)
#define CY_CAPSENSE_BIST_ELTD_CAP_MIN_RAW_PROMILLE              (75u)
#define CY_CAPSENSE_BIST_ELTD_CAP_MAX_RESOLUTION                (15u)
#define CY_CAPSENSE_BIST_ELTD_CAP_MIN_RESOLUTION                (8u)
#define CY_CAPSENSE_BIST_ELTD_CAP_CYCLES_NUM                    (4u)
#define CY_CAPSENSE_BIST_ELTD_CAP_MAX_MODCLK                    (50000000u)
#define CY_CAPSENSE_BIST_SW_DSI_SEL_DEFAULT                     (0x00000000uL)

/* IDAC register mask */
#define CY_CAPSENSE_BIST_IDAC_BITS_TO_WRITE                     (CSD_IDACA_VAL_Msk |\
                                                                 CSD_IDACA_RANGE_Msk |\
                                                                 CSD_IDACA_LEG1_EN_Msk |\
                                                                 CSD_IDACA_LEG2_EN_Msk |\
                                                                 CSD_IDACA_LEG1_MODE_Msk |\
                                                                 CSD_IDACA_LEG2_MODE_Msk)

#define CY_CAPSENSE_BIST_FSM_AZ0_SKIP                           (0x100u)
#define CY_CAPSENSE_BIST_FSM_AZ1_SKIP                           (0x200u)

/*******************************************************************************
* Macros for the external capacitor capacitance measurement test
*******************************************************************************/

#define CY_CAPSENSE_BIST_CAP_MEAS_DUTY_WIDTH                    (10u)
#define CY_CAPSENSE_BIST_CAP_MEAS_MAX_MODCLK                    (12500000u)
#define CY_CAPSENSE_BIST_CAP_MEAS_ACCURACY_FACTOR               (1150u)
#define CY_CAPSENSE_BIST_CAP_MEAS_MIN_RAWCOUNT                  (10u)
#define CY_CAPSENSE_BIST_CAP_MEAS_MAX_CAP                       (25u)
#define CY_CAPSENSE_BIST_CAP_MEAS_CMOD_MAX_VALUE                (5u)
#define CY_CAPSENSE_BIST_CAP_MEAS_CINT_MAX_VALUE                (1u)
#define CY_CAPSENSE_BIST_CAP_MEAS_CSH_MAX_VALUE                 (20u)
#define CY_CAPSENSE_BIST_CAP_MEAS_VREF_MV_DEFAULT               (1200u)
#define CY_CAPSENSE_BIST_CAP_MEAS_WDT_CYCLES_PER_LOOP           (5u)
#define CY_CAPSENSE_BIST_CAP_MEAS_WDT_TIMEOUT                   (3000u)

#define CY_CAPSENSE_BIST_PRECHARGE_MAX_TIME_US                  (6000u)
#define CY_CAPSENSE_BIST_WATCHDOG_MARGIN_COEFF                  (3u)
#define CY_CAPSENSE_BIST_PRECHARGE_WATCHDOG_TIME_US             (CY_CAPSENSE_BIST_PRECHARGE_MAX_TIME_US *\
                                                                 CY_CAPSENSE_BIST_WATCHDOG_MARGIN_COEFF)

/* HW block register values */
#define CY_CAPSENSE_BIST_CAP_SEQ_START_DEFAULT                  (CY_CAPSENSE_CSD_SEQ_START_AZ0_SKIP_MSK | \
                                                                 CY_CAPSENSE_CSD_SEQ_START_AZ1_SKIP_MSK | \
                                                                 CY_CAPSENSE_CSD_SEQ_START_START_MSK)
#define CY_CAPSENSE_BIST_CAP_CSDCMP_DEFAULT                     (CY_CAPSENSE_CSD_CSDCMP_CMP_PHASE_PHI2_MSK | \
                                                                 CY_CAPSENSE_CSD_CSDCMP_CSDCMP_EN_MSK)
#define CY_CAPSENSE_BIST_CAP_SENSE_DUTY_DEFAULT                 (CSD_SENSE_DUTY_OVERLAP_PHI1_Msk | \
                                                                 CSD_SENSE_DUTY_OVERLAP_PHI2_Msk | \
                                                                 CY_CAPSENSE_BIST_CAP_MEAS_DUTY_WIDTH)
#define CY_CAPSENSE_BIST_CAP_SW_BYP_SEL_DEFAULT                 (CY_CAPSENSE_CSD_SW_BYP_SEL_SW_BYA_MSK)
#define CY_CAPSENSE_BIST_CAP_SW_CMP_N_SEL_DEFAULT               (CY_CAPSENSE_CSD_SW_CMP_N_SEL_SW_SCRH_STATIC_CLOSE)
#define CY_CAPSENSE_BIST_CAP_SW_CMP_P_SEL_DEFAULT               (CY_CAPSENSE_CSD_SW_CMP_P_SEL_SW_SFMA_STATIC_CLOSE)
#define CY_CAPSENSE_BIST_CAP_SW_REFGEN_SEL_SRSS_DEFAULT         (CY_CAPSENSE_CSD_SW_REFGEN_SEL_SW_SGR_MSK)
#if (CY_CAPSENSE_PSOC6_FOURTH_GEN)
    #define CY_CAPSENSE_BIST_CAP_SW_REFGEN_SEL_PASS_DEFAULT     (CY_CAPSENSE_CSD_SW_REFGEN_SEL_SW_SGRP_MSK)
    #define CY_CAPSENSE_BIST_CAP_IO_SEL_DEFAULT                 (CY_CAPSENSE_CSD_TX_N_OUT_EN_PHI1 | \
                                                                 CY_CAPSENSE_CSD_TX_N_AMUXA_EN_PHI2)
#endif
#define CY_CAPSENSE_BIST_CAP_REFGEN_DEFAULT                     (CSD_REFGEN_REFGEN_EN_Msk | CSD_REFGEN_RES_EN_Msk)
#define CY_CAPSENSE_BIST_CAP_REFGEN_LOW_VOLTAGE_DEFAULT         (CSD_REFGEN_REFGEN_EN_Msk | CSD_REFGEN_BYPASS_Msk)
#define CY_CAPSENSE_BIST_CAP_CONFIG_DEFAULT                     (CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_48MHZ | \
                                                                 CSD_CONFIG_SENSE_EN_Msk | \
                                                                 CSD_CONFIG_ENABLE_Msk)
#if (CY_CAPSENSE_PSOC6_FOURTH_GEN)
    #define CY_CAPSENSE_BIST_CAP_CONFIG_IREF_DEFAULT            (CY_CAPSENSE_BIST_CAP_CONFIG_DEFAULT | \
                                                                 CY_CAPSENSE_CSD_CONFIG_IREF_SEL_MSK)
#endif
#define CY_CAPSENSE_BIST_CAP_IDAC_MODE_DEFAULT                  (CSD_IDACA_LEG1_MODE_Msk |\
                                                                 CSD_IDACA_LEG2_MODE_Msk)


/*******************************************************************************
* Macros for the VDDA measurement test
*******************************************************************************/

/* SenseClkDivider value for VDDA measurement mode */
#define CY_CAPSENSE_BIST_VDDA_SENSE_DIV_DEFAULT                 (0x4u)
/* Minimal acceptable difference between the VDDA and VREF.
   It is not allowed to have (VDDA - VREF) > CY_CAPSENSE_BIST_VDDA_MIN_DIFF. */
#define CY_CAPSENSE_BIST_VDDA_MIN_DIFF                          (600u)
/* VREF voltage value, used for the VDDA measurement */
#define CY_CAPSENSE_BIST_VDDA_VREF_MIN_MV                       (1200u)
/* VDDA measurement resolution */
#define CY_CAPSENSE_BIST_VDDA_RES                               (2047u)
/* The total capacitance value of reference capacitors */
#define CY_CAPSENSE_BIST_VDDA_CREF                              (21500u)
/* The IDAC gain value, used for the VDDA measurement */
#define CY_CAPSENSE_BIST_VDDA_IDAC_LSB                          (37500u)
/* The MAX possible IDAC code value. */
#define CY_CAPSENSE_BIST_IDAC_MAX                               (127u)
/* The number of initial conversions per sample, used for the VDDA measurement */
#define CY_CAPSENSE_BIST_VDDA_INIT_CYCLES_NUM                   (1u)
/* The number of normal conversions per sample, used for the VDDA measurement */
#define CY_CAPSENSE_BIST_VDDA_NORM_CYCLES_NUM                   (2u)
/* The duration of the Auto-zero stage in microseconds */
#define CY_CAPSENSE_BIST_VDDA_AZ_TIME_US                        (5u)
/* Acquisition time in microseconds */
#define CY_CAPSENSE_BIST_VDDA_ACQ_TIME_US                       (10u)
/* Acquisition time in microseconds */
#define CY_CAPSENSE_BIST_VDDA_MAX_MODCLK                        (50000000u)
/* Configures the count time A to bring Cref1 + Cref2 up from Vssa to Vrefhi with IDACB */
#define CY_CAPSENSE_BIST_VDDA_MEASMODE_VREF                     (0x1uL << CSD_ADC_CTL_ADC_MODE_Pos)
/*
 * Configures count time B to bring Cref1 + Cref2 back up to Vrefhi with IDACB
 * (after bringing them down for time A/2 cycles with IDACB sinking)
 */
#define CY_CAPSENSE_BIST_VDDA_MEASMODE_VREFBY2                  (0x2uL << CSD_ADC_CTL_ADC_MODE_Pos)
/* Configures the HSCMP polarity and count time C to source/sink Cref1 + Cref2 from Vin to Vrefhi */
#define CY_CAPSENSE_BIST_VDDA_MEASMODE_VIN                      (0x3uL << CSD_ADC_CTL_ADC_MODE_Pos)

/* Default HW block operation settings that are required for VDDA measurement */
#define CY_CAPSENSE_BIST_VDDA_CONFIG_DEFAULT                    (CY_CAPSENSE_CSD_CONFIG_ENABLE_MSK |\
                                                                 CY_CAPSENSE_CSD_CONFIG_SAMPLE_SYNC_MSK |\
                                                                 CY_CAPSENSE_CSD_CONFIG_SENSE_EN_MSK |\
                                                                 CY_CAPSENSE_CSD_CONFIG_DSI_COUNT_SEL_MSK)
#define CY_CAPSENSE_BIST_VDDA_AMBUF_DEFAULT                     (0u)
#define CY_CAPSENSE_BIST_VDDA_CSDCMP_DEFAULT                    (0u)
#define CY_CAPSENSE_BIST_VDDA_HSCMP_DEFAULT                     (CY_CAPSENSE_CSD_HSCMP_HSCMP_EN_MSK |\
                                                                 CY_CAPSENSE_CSD_HSCMP_AZ_EN_MSK)
#define CY_CAPSENSE_BIST_VDDA_IDACA_DEFAULT                     (0u)
#define CY_CAPSENSE_BIST_VDDA_IDACB_DEFAULT                     ((CY_CAPSENSE_CSD_IDACB_POL_DYN_DYNAMIC << \
                                                                  CY_CAPSENSE_CSD_IDACB_POL_DYN_POS) |\
                                                                  CY_CAPSENSE_CSD_IDACB_LEG3_EN_MSK)
#define CY_CAPSENSE_BIST_VDDA_SW_RES_DEFAULT                    (0u)
#define CY_CAPSENSE_BIST_VDDA_SENSE_PERIOD_DEFAULT              (CY_CAPSENSE_BIST_VDDA_SENSE_DIV_DEFAULT)
#define CY_CAPSENSE_BIST_VDDA_SENSE_DUTY_DEFAULT                (0u)
#define CY_CAPSENSE_BIST_VDDA_SEQ_INIT_CNT_DEFAULT              (CY_CAPSENSE_BIST_VDDA_INIT_CYCLES_NUM)
#define CY_CAPSENSE_BIST_VDDA_SEQ_NORM_CNT_DEFAULT              (CY_CAPSENSE_BIST_VDDA_NORM_CYCLES_NUM)
#define CY_CAPSENSE_BIST_VDDA_IO_SEL_DEFAULT                    (0u)
#define CY_CAPSENSE_BIST_VDDA_SEQ_START_MEASURE                 (CY_CAPSENSE_CSD_SEQ_START_AZ0_SKIP_MSK |\
                                                                 CY_CAPSENSE_CSD_SEQ_START_START_MSK)
#define CY_CAPSENSE_BIST_VDDA_SW_HS_P_SEL_DEFAULT               (CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMRH_STATIC_CLOSE)
#define CY_CAPSENSE_BIST_VDDA_SW_HS_N_SEL_DEFAULT               (CY_CAPSENSE_CSD_SW_HS_N_SEL_SW_HCCD_STATIC_CLOSE)
#define CY_CAPSENSE_BIST_VDDA_SW_SHIELD_SEL_DEFAULT             (0u)
#define CY_CAPSENSE_BIST_VDDA_SW_AMUXBUF_SEL_DEFAULT            (0u)
#define CY_CAPSENSE_BIST_VDDA_SW_BYP_SEL_DEFAULT                (0u)
#define CY_CAPSENSE_BIST_VDDA_SW_CMP_P_SEL_DEFAULT              (0u)
#define CY_CAPSENSE_BIST_VDDA_SW_CMP_N_SEL_DEFAULT              (0u)
#define CY_CAPSENSE_BIST_VDDA_SW_DSI_SEL_DEFAULT                (0u)
#define CY_CAPSENSE_BIST_VDDA_SW_FW_MOD_SEL_DEFAULT             (CY_CAPSENSE_CSD_SW_FW_MOD_SEL_SW_C1CC_STATIC_CLOSE |\
                                                                 CY_CAPSENSE_CSD_SW_FW_MOD_SEL_SW_C1CD_STATIC_CLOSE)
#define CY_CAPSENSE_BIST_VDDA_SW_FW_TANK_SEL_DEFAULT            (CY_CAPSENSE_CSD_SW_FW_TANK_SEL_SW_C2CC_STATIC_CLOSE |\
                                                                 CY_CAPSENSE_CSD_SW_FW_TANK_SEL_SW_C2CD_STATIC_CLOSE)
#define CY_CAPSENSE_BIST_VDDA_WDT_CYCLES_PER_LOOP               (5u)
#define CY_CAPSENSE_BIST_VDDA_MAX_16_BITS                       (65535u)
/* In milliseconds */
#define CY_CAPSENSE_BIST_VDDA_WDT_TIMEOUT                       (10000u)

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************/
/** \cond SECTION_CAPSENSE_INTERNAL */
/** \addtogroup group_capsense_internal *//** \{ */
/******************************************************************************/

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN)
    /* CRC test-related functions */
    static cy_en_capsense_bist_status_t Cy_CapSense_CheckAllWidgetCRC(
                cy_stc_capsense_context_t * context);
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN) */

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_SHORT_EN)
    /* Check Integrity Sensor Pins test-related functions */
    static cy_en_capsense_bist_status_t Cy_CapSense_SnsShortCheckSensor(
                    uint32_t widgetId,
                    uint32_t sensorId,
                    uint32_t mode,
                    cy_stc_capsense_context_t * context);
    static cy_en_capsense_bist_status_t Cy_CapSense_SnsShortCheckElectrode(
                    uint32_t widgetId,
                    uint32_t ioSnsId,
                    uint32_t mode,
                    const cy_stc_capsense_context_t * context);
    static void Cy_CapSense_SnsShortUpdateTestResult(
                    uint32_t widgetId,
                    uint32_t sensorId,
                    cy_stc_capsense_context_t * context);
    static cy_en_capsense_bist_status_t Cy_CapSense_SnsShortCheckAllSensors(
                    cy_stc_capsense_context_t * context);
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_SHORT_EN) */

#if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN) ||\
     (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN))
    /* Measure Capacitance Sensor and Shield test-related functions */
    static void Cy_CapSense_BistMeasureCapacitanceSensorInit(
                    cy_stc_capsense_context_t * context);
    static void Cy_CapSense_BistMeasureCapacitanceSensorEnable(
                    cy_stc_capsense_context_t * context);
    static cy_en_capsense_bist_status_t Cy_CapSense_BistMeasureCapacitanceSensor(
                    uint32_t * cpPtr,
                    cy_stc_capsense_context_t * context);

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
        static void Cy_CapSense_BistMeasureCapacitanceSensorShieldEnable(
                        cy_stc_capsense_context_t * context);
    #endif

    static cy_en_capsense_bist_status_t Cy_CapSense_BistMeasureCapacitanceSensorRun(
                    cy_stc_capsense_context_t * context);
#endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN) ||\
           (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN)) */

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN)
    static cy_en_capsense_bist_status_t Cy_CapSense_BistMeasureCapacitanceSensorAll(
                    cy_stc_capsense_context_t * context);
#endif

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_EXTERNAL_CAP_EN)
    /* Measure Capacitance Capacitor test-related functions */
    static void Cy_CapSense_BistMeasureCapacitanceCapInit(
                    cy_stc_capsense_context_t * context);
    static void Cy_CapSense_BistMeasureCapacitanceCapEnable(
                    cy_stc_capsense_context_t * context);
    static cy_en_capsense_bist_status_t Cy_CapSense_BistMeasureCapacitanceCapRun(
                    uint32_t * ptrExtCapValue,
                    cy_stc_capsense_context_t * context);
    static cy_en_capsense_bist_status_t Cy_CapSense_BistMeasureCapacitanceCapAll(
                    cy_stc_capsense_context_t * context);
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_EXTERNAL_CAP_EN) */

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_VDDA_EN)
    /* Measure VDDA test-related functions */
    static void Cy_CapSense_BistMeasureVddaInit(
                    cy_stc_capsense_context_t * context);
    static void Cy_CapSense_BistMeasureVddaEnable(
                    cy_stc_capsense_context_t * context);
    static cy_en_capsense_bist_status_t Cy_CapSense_BistMeasureVddaRun(
                    cy_stc_capsense_context_t * context);
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_VDDA_EN) */

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_SHORT_EN)
    static void Cy_CapSense_SetPinDr(
                    cy_stc_capsense_pin_config_t const *ioPtr,
                    uint32_t value);
    static void Cy_CapSense_SetPinPc(
                    cy_stc_capsense_pin_config_t const *ioPtr,
                    uint32_t value);
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_SHORT_EN) */

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_HW_GROUP_EN)
    /* Common functions for all hardware-dependent tests */
    static void Cy_CapSense_BistSwitchHwConfig(
                    cy_en_capsense_bist_hw_config_t hwCfg,
                    cy_stc_capsense_context_t * context);
    static void Cy_CapSense_BistSwitchAllSnsPinState(
                    cy_en_capsense_bist_io_state_t desiredPinState,
                    const cy_stc_capsense_context_t * context);

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
        static void Cy_CapSense_BistSwitchAllShieldPinState(
                        cy_en_capsense_bist_io_state_t desiredPinState,
                        const cy_stc_capsense_context_t * context);
        static void Cy_CapSense_SetShieldPinState(
                        uint32_t desiredDriveMode,
                        uint32_t desiredPinOutput,
                        en_hsiom_sel_t desiredHsiom,
                        const cy_stc_capsense_context_t * context);
    #endif

    static void Cy_CapSense_BistSwitchAllExternalCapPinState(
                    cy_en_capsense_bist_io_state_t desiredPinState,
                    const cy_stc_capsense_context_t * context);
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_HW_GROUP_EN) */

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN)
    static void Cy_CapSense_BistConnectElectrode(
                    uint32_t widgetId,
                    uint32_t electrodeId,
                    const cy_stc_capsense_context_t * context);
    static void Cy_CapSense_BistDisconnectElectrode(
                    uint32_t widgetId,
                    uint32_t electrodeId,
                    const cy_stc_capsense_context_t * context);
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN) */

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN) || \
    (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN)  || \
    (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_EXTERNAL_CAP_EN)
    static uint32_t Cy_CapSense_BistWaitEndOfScan(
                uint32_t watchdogCycleNum,
                const cy_stc_capsense_context_t * context);
#endif

/** \} \endcond */


/*******************************************************************************
* Function Name: Cy_CapSense_RunSelfTest_V2
****************************************************************************//**
*
* Runs built-in self-tests specified by the test enable mask.
*
* The function performs various self-tests on all the enabled widgets
* and sensors in the project. Select the required set of tests
* using the bit-mask in testEnMask parameter.
*
* Use CY_CAPSENSE_TST_RUN_SELF_TEST_MASK to execute all the self-tests or
* any combination of the masks (defined in testEnMask parameter) to specify the
* desired test list.
*
* To execute a single-element test (i.e. for one widget or one sensor),
* the following low-level functions are available:
* - Cy_CapSense_CheckCRCWidget()
* - Cy_CapSense_CheckIntegritySensorPins()
* - Cy_CapSense_MeasureCapacitanceSensor()
* - Cy_CapSense_MeasureCapacitanceShield()
* - Cy_CapSense_MeasureCapacitanceCap_V2()
* - Cy_CapSense_MeasureVdda()
*
* Refer to these functions descriptions for detail information
* on the corresponding test.
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
*
* \param testEnMask
* Specifies the tests to be executed. Each bit corresponds to one test. It is
* possible to launch the function with any combination of the available tests.
* - CY_CAPSENSE_BIST_CRC_WDGT_MASK       - Verifies the RAM widget structure CRC
*                                          for all the widgets.
* - CY_CAPSENSE_BIST_SNS_INTEGRITY_MASK  - Checks all the sensors for a short
*                                          to GND / VDD / other sensors.
* - CY_CAPSENSE_BIST_SNS_CAP_MASK        - Measures all the sensors capacitance.
* - CY_CAPSENSE_BIST_SHIELD_CAP_MASK     - Measures the shield capacitance.
* - CY_CAPSENSE_BIST_EXTERNAL_CAP_MASK   - Measures the capacitance of the
*                                          available external capacitors.
* - CY_CAPSENSE_BIST_VDDA_MASK           - Measures the VDDA voltage.
* - CY_CAPSENSE_BIST_RUN_AVAILABLE_SELF_TEST_MASK
*                                        - Executes all available tests.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a bit-mask with a status of execution of the specified tests:
* - CY_CAPSENSE_BIST_SUCCESS_E      - All the tests passed successfully.
* - CY_CAPSENSE_BIST_BAD_PARAM_E    - A non-defined test was requested in the
*                                     testEnMask parameter or the context is
*                                     a NULL pointer. The function
*                                     was not performed.
* - CY_CAPSENSE_BIST_HW_BUSY_E      - The CSD HW block is busy with a previous
*                                     operation. The function was not performed.
* - CY_CAPSENSE_BIST_ERROR_E        - An unexpected fault occurred during
*                                     the measurement, you may need to repeat
*                                     the measurement.
* - CY_CAPSENSE_BIST_FAIL_E         - Any of tests specified by the testEnMask
*                                     parameters has faulted.
*
*******************************************************************************/
cy_en_capsense_bist_status_t Cy_CapSense_RunSelfTest_V2(
                uint32_t testEnMask,
                cy_stc_capsense_context_t * context)

{
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_BAD_PARAM_E;

    #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN)     || \
        ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_HW_GROUP_EN)     && \
        ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_VDDA_EN)         || \
         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_EXTERNAL_CAP_EN) || \
        ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)       && \
         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN))      || \
         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_SHORT_EN)    || \
         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN))))
    cy_en_capsense_bist_status_t bistStatus;
    #endif

    #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_HW_GROUP_EN) && \
       ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_VDDA_EN) || \
       ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) && \
        (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN))))
        uint32_t tmpVal;
    #endif

    if (0u == (testEnMask & (~CY_CAPSENSE_BIST_RUN_AVAILABLE_SELF_TEST_MASK)))
    {
        if(NULL != context)
        {
            if(CY_CAPSENSE_NOT_BUSY == Cy_CapSense_IsBusy(context))
            {
                #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN)
                    if (0u != (CY_CAPSENSE_BIST_CRC_WDGT_MASK & testEnMask))
                    {
                        bistStatus = Cy_CapSense_CheckAllWidgetCRC(context);
                        if (CY_CAPSENSE_BIST_SUCCESS_E != bistStatus)
                        {
                            result = CY_CAPSENSE_BIST_FAIL_E;
                            context->ptrBistContext->testResultMask |= CY_CAPSENSE_BIST_CRC_WDGT_MASK;
                        }
                    }
                #endif

                #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_HW_GROUP_EN)
                    /* The next group of tests is hardware-dependent, the request is to switch the sense method */
                    if(CY_CAPSENSE_SUCCESS_E == Cy_CapSense_SwitchSensingMode(CY_CAPSENSE_BIST_GROUP, context))
                    {
                        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_VDDA_EN)
                            if (0u != (CY_CAPSENSE_BIST_VDDA_MASK  & testEnMask))
                            {
                                bistStatus = Cy_CapSense_MeasureVdda_V2(&tmpVal, context);
                                if (CY_CAPSENSE_BIST_SUCCESS_E != bistStatus)
                                {
                                    result = CY_CAPSENSE_BIST_FAIL_E;
                                    context->ptrBistContext->testResultMask |= CY_CAPSENSE_BIST_VDDA_MASK;
                                }
                            }
                        #endif

                        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_EXTERNAL_CAP_EN)
                            if (0u != (CY_CAPSENSE_BIST_EXTERNAL_CAP_MASK & testEnMask))
                            {
                                bistStatus = Cy_CapSense_BistMeasureCapacitanceCapAll(context);
                                if (CY_CAPSENSE_BIST_SUCCESS_E != bistStatus)
                                {
                                    result = CY_CAPSENSE_BIST_FAIL_E;
                                    context->ptrBistContext->testResultMask |= CY_CAPSENSE_BIST_EXTERNAL_CAP_MASK;
                                }
                            }
                        #endif

                        #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) && \
                             (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN))
                            if ((0u != (CY_CAPSENSE_BIST_SHIELD_CAP_MASK & testEnMask)) &&
                                (CY_CAPSENSE_ENABLE == context->ptrCommonConfig->csdShieldEn))
                            {
                                bistStatus = Cy_CapSense_MeasureCapacitanceShield(&tmpVal, context);
                                if (CY_CAPSENSE_BIST_SUCCESS_E != bistStatus)
                                {
                                    result = CY_CAPSENSE_BIST_FAIL_E;
                                    context->ptrBistContext->testResultMask |= CY_CAPSENSE_BIST_SHIELD_CAP_MASK;
                                }
                            }
                        #endif

                        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_SHORT_EN)
                            if (0u != (CY_CAPSENSE_BIST_SNS_INTEGRITY_MASK & testEnMask))
                            {
                                bistStatus = Cy_CapSense_SnsShortCheckAllSensors(context);
                                if (CY_CAPSENSE_BIST_SUCCESS_E != bistStatus)
                                {
                                    result = CY_CAPSENSE_BIST_FAIL_E;
                                    context->ptrBistContext->testResultMask |= CY_CAPSENSE_BIST_SNS_INTEGRITY_MASK;
                                }
                            }
                        #endif

                        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN)
                            if (0u != (CY_CAPSENSE_BIST_SNS_CAP_MASK & testEnMask))
                            {
                                bistStatus = Cy_CapSense_BistMeasureCapacitanceSensorAll(context);
                                if (CY_CAPSENSE_BIST_SUCCESS_E != bistStatus)
                                {
                                    result = CY_CAPSENSE_BIST_FAIL_E;
                                    context->ptrBistContext->testResultMask |= CY_CAPSENSE_BIST_SNS_CAP_MASK;
                                }
                            }
                        #endif

                    }
                    else
                    {
                        result = CY_CAPSENSE_BIST_ERROR_E;
                    }
                #endif

                if (CY_CAPSENSE_BIST_FAIL_E != result)
                {
                    result = CY_CAPSENSE_BIST_SUCCESS_E;
                }
            }
            else
            {
                result = CY_CAPSENSE_BIST_HW_BUSY_E;
            }
        }
    }

    return (result);
}


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_CheckCRCWidget_V2
****************************************************************************//**
*
* Checks the stored CRC of the \ref cy_stc_capsense_widget_context_t data
* structure of the specified widget.
*
* This function validates the data integrity of the
* \ref cy_stc_capsense_widget_context_t data structure of the specified widget
* by calculating the CRC and comparing it with the stored CRC value of the
* specified widget.
*
* Initially, after the device power up, the Cy_CapSense_Enable() function
* calculates CRC for each widget and stores them in the .ptrWdgtCrc[] array
* of the \ref cy_stc_capsense_bist_context_t structure. The test execution
* compares this stored CRC value with the newly calculated and if the stored
* and calculated CRC values differ:
* 1. The calculated CRC is stored to the .wdgtCrcCalc field
*    of the \ref cy_stc_capsense_bist_context_t data structure.
* 2. The widget ID is stored to the .crcWdgtId field.
* 3. The CY_CAPSENSE_BIST_CRC_WDGT_MASK bit is set in the .testResultMask field.
*
* The function never clears the CY_CAPSENSE_BIST_CRC_WDGT_MASK bit.
* If the CY_CAPSENSE_BIST_CRC_WDGT_MASK bit is set, the wdgtCrcCalc
* and .crcWdgtId fields are not updated.
*
* It is recommended to use the Cy_CapSense_SetParam() function to change
* the value of the \ref cy_stc_capsense_widget_context_t data structure elements
* as the CRC is updated by Cy_CapSense_SetParam() function.
*
* You can initiate this test by the Cy_CapSense_RunSelfTest() function with
* the CY_CAPSENSE_BIST_CRC_WDGT_MASK mask as an input.
*
* The function clears the CY_CAPSENSE_WD_WORKING_MASK bit of the .status
* field in \ref cy_stc_capsense_widget_context_t structure if the calculated
* CRC value differs to the stored CRC value.
* Those non-working widgets are skipped by the high-level scanning and
* processing functions. Restoring a widget to its working state should
* be done by the application level.
*
* For details of the used CRC algorithm, refer to the Cy_CapSense_GetCRC()
* function.
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
*
* \param widgetId
* Specifies the ID number of the widget.
* A macro for the widget ID can be found in the
* CAPSENSE&trade; Configuration header file (cycfg_capsense.h) defined as
* CY_CAPSENSE_<WidgetName>_WDGT_ID.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E          - The stored CRC matches
*                                         the calculated CRC.
* - CY_CAPSENSE_BIST_FAIL_E             - The widget CRC differs to
*                                         the stored CRC.
* - CY_CAPSENSE_BIST_BAD_PARAM_E        - The input parameters are invalid.
*                                         The test was not executed.
*
*******************************************************************************/
cy_en_capsense_bist_status_t Cy_CapSense_CheckCRCWidget_V2(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context)
{
    uint16_t crcValue;
    cy_stc_capsense_widget_context_t * ptrWdCxt;
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_BAD_PARAM_E;

    if(NULL != context)
    {
        if (context->ptrCommonConfig->numWd > widgetId)
        {
            crcValue = Cy_CapSense_GetCrcWidget(widgetId, context);
            if ((context->ptrBistContext->ptrWdgtCrc[widgetId]) != crcValue)
            {
                /* Get a pointer to the specified widget context structure */
                ptrWdCxt = &context->ptrWdContext[widgetId];

                /* Write to the self-test data structure widgetId of the first badly-tested widget */
                if (0Lu == (context->ptrBistContext->testResultMask & CY_CAPSENSE_BIST_CRC_WDGT_MASK))
                {
                    context->ptrBistContext->wdgtCrcCalc = crcValue;
                    context->ptrBistContext->crcWdgtId = (uint8_t)widgetId;
                    context->ptrBistContext->testResultMask |= CY_CAPSENSE_BIST_CRC_WDGT_MASK;
                }
                ptrWdCxt->status &= (uint8_t)~CY_CAPSENSE_WD_WORKING_MASK;
                result = CY_CAPSENSE_BIST_FAIL_E;
            }
            else
            {
                result = CY_CAPSENSE_BIST_SUCCESS_E;
            }
        }
    }

    return (result);
}


/*******************************************************************************
* Function Name: Cy_CapSense_CheckAllWidgetCRC
****************************************************************************//**
*
* The internal function that checks CRC of all widget structures.
*
* The function calculates CRC of all widget structures and compare it
* to the stored CRCs. It is called by the Cy_CapSense_RunSelfTest() function.
* In the first case of failed comparison the function updates
* testResultMask and returns the status. Next widgets are not checked.
* The function use the Cy_CapSense_CheckCRCWidget() function.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the test processing:
* - CY_CAPSENSE_BIST_SUCCESS_E if all widget CRC are OK;
* - CY_CAPSENSE_BIST_FAIL_E if any widget CRC is wrong.
*
*******************************************************************************/
static cy_en_capsense_bist_status_t Cy_CapSense_CheckAllWidgetCRC(
                cy_stc_capsense_context_t * context)
{
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_SUCCESS_E;
    uint32_t widgetId;

    for (widgetId = 0u; widgetId < context->ptrCommonConfig->numWd; widgetId++)
    {
        if (CY_CAPSENSE_BIST_SUCCESS_E != (Cy_CapSense_CheckCRCWidget_V2(widgetId, context)))
        {
            result = CY_CAPSENSE_BIST_FAIL_E;
            break;
        }
    }
    return (result);
}


/*******************************************************************************
* Function Name: Cy_CapSense_UpdateCrcWidget
****************************************************************************//**
*
* The internal function updates the CRC
* of the \ref cy_stc_capsense_widget_context_t data structure
* for the specified widget.
*
* The function implements the following functionality:
* - Executes the Cy_CapSense_GetCRC() routine for the specified widget.
* - Updates the self-test CRC array with the CRC value, calculated for the
*   specified widget.
*
* The CRC value is stored in the special wdgtCrc[CY_CAPSENSE_WIDGET_COUNT] array
* declared in the cycfg_capsense.c file.
*
* \param widgetId
* Specifies the ID number of the widget.
* A macro for the widget ID can be found in the
* CAPSENSE&trade; Configuration header file (cycfg_capsense.h) defined as
* CY_CAPSENSE_<WidgetName>_WDGT_ID.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_UpdateCrcWidget(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context)
{
    uint16_t crcValue;

    crcValue = Cy_CapSense_GetCrcWidget(widgetId, context);

    /* Write the calculated CRC value to the self-test CRC array */
    context->ptrBistContext->ptrWdgtCrc[widgetId] = crcValue;
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_BSLN_INTEGRITY_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_CheckIntegritySensorBaseline_V2
****************************************************************************//**
*
* Checks if the baseline of the specified sensor is not corrupted
* by comparing it with its inverse copy and checks if the baseline is
* within the specified range.
*
* The function checks whether or not the baseline binary inverted to
* its inverse copy is saved to the self-test baseline-inverse structure
* and is within the user-defined limits. If the baseline does
* not match its inverse copy or if the baseline is out of the user-defined
* limits, the function sets the CY_CAPSENSE_BIST_BSLN_INTEGRITY_MASK bit
* in the .testResultMask field of the \ref cy_stc_capsense_bist_context_t
* structure.
*
* The test is integrated into the CAPSENSE&trade; Middleware. All CAPSENSE&trade;
* processing functions like Cy_CapSense_ProcessAllWidgets()
* or Cy_CapSense_UpdateSensorBaseline() automatically verify the baseline
* value before using it and update its inverse copy after processing.
* If a baseline update fails, a CY_CAPSENSE_STATUS_BAD_DATA result
* is returned. The baseline initialization functions do not verify the
* baseline and update the baseline inverse copy.
*
* This function does not update the CY_CAPSENSE_WD_WORKING_MASK bit of
* the .status field in \ref cy_stc_capsense_widget_context_t structure
* and is not available in the Cy_CapSense_RunSelfTest() function.
*
* Use this function to verify the uniformity of sensors, for example, at
* mass-production or during an operation phase together with the
* Cy_CapSense_CheckIntegritySensorRawcount() function.
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
*
* \param widgetId
* Specifies the ID number of the widget.
* A macro for the widget ID can be found in the
* CAPSENSE&trade; Configuration header file (cycfg_capsense.h) defined as
* CY_CAPSENSE_<WidgetName>_WDGT_ID.
*
* \param sensorId
* Specifies the ID number of the sensor within the widget.
* A macro for the sensor ID within the specified widget can be found in
* the CAPSENSE&trade; Configuration header file (cycfg_capsense.h) defined as
* CY_CAPSENSE_<WidgetName>_SNS<SensorNumber>_ID.
*
* \param baselineHighLimit
* Specifies the upper limit for a baseline.
*
* \param baselineLowLimit
* Specifies the lower limit for a baseline.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E          - The baseline is within the
*                                         specified range.
* - CY_CAPSENSE_BIST_FAIL_E             - The test failed and the baseline
*                                         is not binary inverted to its inverse
*                                         copy or is out of the specified limits.
* - CY_CAPSENSE_BIST_BAD_PARAM_E        - The input parameter is invalid.
*                                         The test was not executed.
*
*******************************************************************************/
cy_en_capsense_bist_status_t Cy_CapSense_CheckIntegritySensorBaseline_V2(
                uint32_t widgetId,
                uint32_t sensorId,
                uint16_t baselineHighLimit,
                uint16_t baselineLowLimit,
                cy_stc_capsense_context_t * context)
{
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_BAD_PARAM_E;
    uint16_t bslnInv;
    uint32_t freqChIndex;
    uint32_t cxtOffset;

    const cy_stc_capsense_sensor_context_t *ptrSnsCxt;
    cy_stc_capsense_widget_config_t const *ptrWdgtCfg;

    if(NULL != context)
    {
        if ((context->ptrCommonConfig->numWd > widgetId) &&
            (context->ptrWdConfig[widgetId].numSns > sensorId))
        {
            /* Get a pointer to the specified widget configuration structure */
            ptrWdgtCfg = &context->ptrWdConfig[widgetId];
            /* Get a pointer to the specified sensor context structure */
            ptrSnsCxt = &ptrWdgtCfg->ptrSnsContext[sensorId];
            /* Check baselines for all frequencies */
            for(freqChIndex = 0u; freqChIndex < CY_CAPSENSE_CONFIGURED_FREQ_NUM; freqChIndex++)
            {
                cxtOffset = sensorId + (freqChIndex * context->ptrCommonConfig->numSns);
                bslnInv = (uint16_t)(~(ptrWdgtCfg->ptrBslnInv[cxtOffset]));
                if ((ptrSnsCxt->bsln != bslnInv) ||
                    (ptrSnsCxt->bsln > baselineHighLimit) ||
                    (ptrSnsCxt->bsln < baselineLowLimit))
                {
                    context->ptrBistContext->testResultMask |= CY_CAPSENSE_BIST_BSLN_INTEGRITY_MASK;
                    result = CY_CAPSENSE_BIST_FAIL_E;
                    break;
                }

                ptrSnsCxt += context->ptrCommonConfig->numSns;
            }

            if (CY_CAPSENSE_BIST_FAIL_E != result)
            {
                result = CY_CAPSENSE_BIST_SUCCESS_E;
            }
        }
    }

    return (result);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_BSLN_INTEGRITY_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_RAW_INTEGRITY_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_CheckIntegritySensorRawcount_V2
****************************************************************************//**
*
* Checks the raw count of the specified widget/sensor is within the specified
* range.
*
* The raw count is within a specific range (based on the calibration target)
* for good units. The function checks whether or not the raw count is within
* the user-defined limits in the ranges function arguments.
* If the raw count is out of limits, this function sets the
* CY_CAPSENSE_BIST_RAW_INTEGRITY_MASK bit in the .testResultMask field of the
* \ref cy_stc_capsense_bist_context_t structure.
*
* This function does not update the CY_CAPSENSE_WD_WORKING_MASK bit of
* the .status field in \ref cy_stc_capsense_widget_context_t structure
* and is not available in the Cy_CapSense_RunSelfTest() function.
*
* Use this function to verify the uniformity of sensors, for example, at
* mass-production or during an operation phase together with the
* Cy_CapSense_CheckIntegritySensorBaseline() function.
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
*
* \param widgetId
* Specifies the ID number of the widget.
* A macro for the widget ID can be found in the
* CAPSENSE&trade; Configuration header file (cycfg_capsense.h) defined as
* CY_CAPSENSE_<WidgetName>_WDGT_ID.
*
* \param sensorId
* Specifies the ID number of the sensor within the widget.
* A macro for the sensor ID within the specified widget can be found in
* the CAPSENSE&trade; Configuration header file (cycfg_capsense.h) defined as
* CY_CAPSENSE_<WidgetName>_SNS<SensorNumber>_ID.
*
* \param rawcountHighLimit
* Specifies the upper limit for the widget/sensor raw count.
*
* \param rawcountLowLimit
* Specifies the lower limit for the widget/sensor raw count.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E          - The raw count is within the
*                                         specified range.
* - CY_CAPSENSE_BIST_FAIL_E             - The test failed and raw count is out
*                                         of the specified limits.
* - CY_CAPSENSE_BIST_BAD_PARAM_E        - The input parameter is invalid.
*                                         The test was not executed.
*
*******************************************************************************/
cy_en_capsense_bist_status_t Cy_CapSense_CheckIntegritySensorRawcount_V2(
                uint32_t widgetId,
                uint32_t sensorId,
                uint16_t rawcountHighLimit,
                uint16_t rawcountLowLimit,
                cy_stc_capsense_context_t * context)
{
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_BAD_PARAM_E;
    uint32_t freqChIndex;
    const cy_stc_capsense_sensor_context_t *ptrSnsCxt;
    cy_stc_capsense_widget_config_t const *ptrWdgtCfg;

    if(NULL != context)
    {
        if ((context->ptrCommonConfig->numWd > widgetId) &&
            (context->ptrWdConfig[widgetId].numSns > sensorId))
        {
            /* Find a pointer to the specified widget configuration structure */
            ptrWdgtCfg = &context->ptrWdConfig[widgetId];
            /* Find a pointer to the specified sensor context structure */
            ptrSnsCxt = &ptrWdgtCfg->ptrSnsContext[sensorId];
            /* Check raw counts for all frequencies */
            for(freqChIndex = 0u; freqChIndex < CY_CAPSENSE_CONFIGURED_FREQ_NUM; freqChIndex++)
            {
                if ((ptrSnsCxt->raw  > rawcountHighLimit) ||
                    (ptrSnsCxt->raw  < rawcountLowLimit))
                {
                    context->ptrBistContext->testResultMask |= CY_CAPSENSE_BIST_RAW_INTEGRITY_MASK;
                    result = CY_CAPSENSE_BIST_FAIL_E;
                    break;
                }

                ptrSnsCxt += context->ptrCommonConfig->numSns;
            }

            if (CY_CAPSENSE_BIST_FAIL_E != result)
            {
                result = CY_CAPSENSE_BIST_SUCCESS_E;
            }
        }
    }

    return (result);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_RAW_INTEGRITY_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_SHORT_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_CheckIntegritySensorPins_V2
****************************************************************************//**
*
* Checks the specified widget/sensor for shorts to GND, VDD or other sensors.
*
* This function performs several sub-tests to verify the specified sensor
* is not electrically shorted and is in a good condition to reliably detect
* user interactions.
*
* This function performs tests to check if the specified sensor is shorted to:
* * GND
* * VDD
* * Other GPIOs used by CAPSENSE&trade; (such as sensors, Tx, Rx,
*   shield electrodes, and external capacitors)
* * Other non-CAPSENSE&trade; GPIOs (only if they are configured
*   in a strong high or low state during the test execution).
*
* The absolute resistance of an electrical short must be less than 1500 Ohm
* including all series resistors on a sensor for a short to be detected
* to GND, VDD or GPIOs. For example, if a series resistor on a sensor is
* 560 Ohm (as recommended) and the sensor is shorted with another sensor,
* the function can detect a short with a short resistance up to 380 Ohm as
* there are two 560 ohm resistors between the shorted sensor GPIOs.
*
* The function executes the following flow to detect a short:
* * Configures all CAPSENSE&trade; controlled GPIOs to strong-drive-high,
*   and the specified sensor GPIO to resistive pull down mode.
* * Waits for a delay (defined by .snsIntgShortSettlingTime field
*   of the \ref cy_stc_capsense_bist_context_t structure) to get established
*   all transient processes.
* * Checks the status of the specified sensor for the expected state
*   (logic low).
* * Configures all CAPSENSE&trade; controlled GPIOs to strong-drive-low,
*   and the specified sensor GPIO to resistive pull up mode.
* * Waits for the above mentioned delay.
* * Checks the status of the specified sensor for the expected state
*   (logic high).
* * Stores the test result in the CAPSENSE&trade; Data Structure.
*   A short is reported only when the sensor status check returns
*   an unexpected state.
*
* Due to the sensor parasitic capacitance and internal pull-up/down resistance,
* logic high-to-low (and vice versa) transitions require a settling time before
* checking the sensor status. A 2us delay is used as a settling time and can
* be changed using the .snsIntgShortSettlingTime field
* of the cy_stc_capsense_bist_context_t structure.
*
* If a short is detected this function updates the following statuses:
* * The widget ID is stored to the .shortedWdId field
*   of the \ref cy_stc_capsense_bist_context_t structure.
* * The sensor ID is stored to the .shortedSnsId field
*   of the \ref cy_stc_capsense_bist_context_t structure.
* * The CY_CAPSENSE_BIST_SNS_INTEGRITY_MASK bit is set in the .testResultMask field
*   of the \ref cy_stc_capsense_bist_context_t structure.
* * If CY_CAPSENSE_BIST_SNS_INTEGRITY_MASK is already set due to a previously
*   detected fault on any of the sensor, this function does not update
*   the .shortedWdId and .shortedSnsId fields. For this reason,
*   clear the CY_CAPSENSE_BIST_SNS_INTEGRITY_MASK bit prior calling this function.
* * The widget is disabled by clearing the CY_CAPSENSE_WD_WORKING_MASK bit
*   in the .status field of the \ref cy_stc_capsense_widget_context_t structure
*   of the specified widget.
*   The disabled widget is ignored by high-level functions of scanning / data
*   processing. To restore the widget operation
*   the application layer should manually set the CY_CAPSENSE_WD_WORKING_MASK
*   bit.
*
* To check all the project sensors at once, use the Cy_CapSense_RunSelfTest()
* function with the CY_CAPSENSE_BIST_SNS_INTEGRITY_MASK mask.
*
* To detect an electrical short or fault condition with resistance
* higher than 1500 ohm, the Cy_CapSense_MeasureCapacitanceSensor() function can
* be used as the fault condition affects the measured sensor capacitance.
*
* This test can be executed only if the CAPSENSE&trade; Middleware is in the IDLE
* state. This function must not be called while CAPSENSE&trade; Middleware is busy.
*
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
*
* \param widgetId
* Specifies the ID number of the widget.
* A macro for the widget ID can be found in the
* CAPSENSE&trade; Configuration header file (cycfg_capsense.h) defined as
* CY_CAPSENSE_<WidgetName>_WDGT_ID.
*
* \param sensorId
* Specifies the ID of the sensor (electrode for CSX widgets) within the widget
* to be tested.
*
* For the CSD widgets, a macro for the sensor ID within the specified widget
* can be found in the CAPSENSE&trade; Configuration header file (cycfg_capsense.h)
* defined as CY_CAPSENSE_<WidgetName>_SNS<SensorNumber>_ID.
*
* For the CSX widgets, sensorId is an electrode ID and is defined as Rx ID
* or Tx ID. The first Rx in a widget corresponds to electrodeId = 0, the
* second Rx in a widget corresponds to electrodeId = 1, and so on.
* The last Tx in a widget corresponds to electrodeId = (RxNum + TxNum - 1).
* Macros for Rx and Tx IDs can be found in the CAPSENSE&trade; Configuration header
* file (cycfg_capsense.h) defined as:
* * CapSense_<WidgetName>_RX<RXNumber>_ID
* * CapSense_<WidgetName>_TX<TXNumber>_ID.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E          - The sensor pin(s) are valid
*                                         for CAPSENSE&trade; operations.
* - CY_CAPSENSE_BIST_FAIL_E             - A short is detected on the
*                                         specified sensor.
* - CY_CAPSENSE_BIST_BAD_PARAM_E        - The input parameter is invalid.
*                                         The test was not executed.
* - CY_CAPSENSE_BIST_HW_BUSY_E          - The CSD HW block is busy with a
*                                         previous operation. The function
*                                         was not executed.
*
*******************************************************************************/
cy_en_capsense_bist_status_t Cy_CapSense_CheckIntegritySensorPins_V2(
                uint32_t widgetId,
                uint32_t sensorId,
                cy_stc_capsense_context_t * context)
{
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_BAD_PARAM_E;
    uint32_t numWdgtElectrodes;

    if(NULL != context)
    {
        if (context->ptrCommonConfig->numWd > widgetId)
        {
            /* Get a total number of the widget elements: for CSX it is numRows + numCols, for CSD it is totalNumSns */
            if (CY_CAPSENSE_CSX_GROUP == context->ptrWdConfig[widgetId].senseMethod)
            {
                /* For the CSX widgets, get the index of the Rx electrode */
                numWdgtElectrodes = context->ptrWdConfig[widgetId].numRows +
                          (uint32_t)context->ptrWdConfig[widgetId].numCols;
            }
            else
            {
                numWdgtElectrodes = context->ptrWdConfig[widgetId].numSns;
            }
            if (numWdgtElectrodes > sensorId)
            {
                /* Initialize the result */
                result = CY_CAPSENSE_BIST_SUCCESS_E;
                /* Release previously-captured HW resources by the other mode and capture them for BIST */
                if (CY_CAPSENSE_SUCCESS_E == Cy_CapSense_SwitchSensingMode(CY_CAPSENSE_BIST_GROUP, context))
                {
                    /* Switch the HW resource configuration to the sensor short test */
                    Cy_CapSense_BistSwitchHwConfig(CY_CAPSENSE_BIST_HW_SHORT_E, context);

                    /* Set all CAPSENSE&trade; pins to strong-high */
                    Cy_CapSense_BistSwitchAllSnsPinState(CY_CAPSENSE_BIST_IO_STRONG_HIGH_E, context);

                    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
                        Cy_CapSense_BistSwitchAllShieldPinState(CY_CAPSENSE_BIST_IO_STRONG_HIGH_E, context);
                    #endif

                    Cy_CapSense_BistSwitchAllExternalCapPinState(CY_CAPSENSE_BIST_IO_STRONG_HIGH_E, context);
                    /* Wait for the maximum possible external capacitor charging time */
                    Cy_SysLib_DelayUs(context->ptrBistContext->capacitorSettlingTime);

                    if (CY_CAPSENSE_BIST_SUCCESS_E != Cy_CapSense_SnsShortCheckSensor(widgetId, sensorId, CY_CAPSENSE_BIST_DR_PIN2VDD, context))
                    {
                        result = CY_CAPSENSE_BIST_FAIL_E;
                    }

                    /* Set all CAPSENSE&trade; pins to strong-low */
                    Cy_CapSense_BistSwitchAllSnsPinState(CY_CAPSENSE_BIST_IO_STRONG_E, context);

                    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
                        Cy_CapSense_BistSwitchAllShieldPinState(CY_CAPSENSE_BIST_IO_STRONG_E, context);
                    #endif

                    Cy_CapSense_BistSwitchAllExternalCapPinState(CY_CAPSENSE_BIST_IO_STRONG_E, context);

                    /* Wait for the maximum possible external capacitor charging time */
                    Cy_SysLib_DelayUs(context->ptrBistContext->capacitorSettlingTime);

                    if (CY_CAPSENSE_BIST_SUCCESS_E != Cy_CapSense_SnsShortCheckSensor(widgetId, sensorId, CY_CAPSENSE_BIST_DR_PIN2GND, context))
                    {
                        result = CY_CAPSENSE_BIST_FAIL_E;
                    }
                }
                else
                {
                    result = CY_CAPSENSE_BIST_HW_BUSY_E;
                }
            }
        }
    }

    return (result);
}


/*******************************************************************************
* Function Name: Cy_CapSense_SnsShortCheckSensor
****************************************************************************//**
*
* The internal function checks if the specified sensor element is shorted
* to the VDD or GND level by configuring each of its electrodes to pull-up or
* pull-down and check their state.
*
* An additional delay is added between configuring the electrode and
* reading its state to establish the transition process for cases
* with big capacitance and short resistance.
* The function assumes all rest electrodes are set to strong drive mode,
* so the sensor-to-sensor short condition is also detected.
*
* \param widgetId
* Specifies the ID number of the widget.
* A macro for the widget ID can be found in the
* CAPSENSE&trade; Configuration header file (cycfg_capsense.h) defined as
* CY_CAPSENSE_<WidgetName>_WDGT_ID.
*
* \param sensorId
* Specifies the ID of the sensor element within the widget to change
* its pin state.
* * For the CSD widgets, use the sensor ID. A macro for the
*   sensor ID within a specified widget can be found in the cycfg_capsense.h
*   file defined as CY_CAPSENSE_<WIDGET_NAME>_SNS<SENSOR_NUMBER>_ID.
* * For the CSX widgets use either Rx ID or Tx ID.
*   The first Rx in a widget corresponds to sensorElement = 0; the second
*   Rx in a widget corresponds to sensorElement = 1, and so on.
*   The last Tx in a widget corresponds to sensorElement = (RxNum + TxNum - 1).
*   A macro for the Rx ID or Tx ID can be found in the cycfg_capsense.h
*   file defined as CY_CAPSENSE_<WIDGET_NAME>_<TX/RX><TX/RX_NUMBER>_ID.
*
* \param mode
* Specifies the test mode, either:
* * CY_CAPSENSE_BIST_DR_PIN2GND means sensor is configured
*   to pull-up and checked for logical 0
* * CY_CAPSENSE_BIST_DR_PIN2VDD means sensor is configured
*   to pull-down and checked for logical 1
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E - The sensor pin(s) are not shorted.
* - CY_CAPSENSE_BIST_FAIL_E - A short is detected on the specified sensor.
*
*******************************************************************************/
static cy_en_capsense_bist_status_t Cy_CapSense_SnsShortCheckSensor(
                uint32_t widgetId,
                uint32_t sensorId,
                uint32_t mode,
                cy_stc_capsense_context_t * context)
{
    cy_en_capsense_bist_status_t result;
    uint32_t ioSnsId;

    if (CY_CAPSENSE_CSX_GROUP == context->ptrWdConfig[widgetId].senseMethod)
    {
        /* For the CSX widgets, get the index of the Rx electrode */
        ioSnsId = sensorId / context->ptrWdConfig[widgetId].numRows;
        result = Cy_CapSense_SnsShortCheckElectrode(widgetId, ioSnsId, mode, context);
        if (CY_CAPSENSE_BIST_SUCCESS_E == result)
        {
            /* For the CSX widgets, get the index of the Tx electrode */
            ioSnsId = (uint32_t)(sensorId % context->ptrWdConfig[widgetId].numRows) +
                      (uint32_t)context->ptrWdConfig[widgetId].numCols;
            result = Cy_CapSense_SnsShortCheckElectrode(widgetId, ioSnsId, mode, context);
        }
    }
    else
    {
        result = Cy_CapSense_SnsShortCheckElectrode(widgetId, sensorId, mode, context);
    }

    if (CY_CAPSENSE_BIST_SUCCESS_E != result)
    {
        Cy_CapSense_SnsShortUpdateTestResult(widgetId, sensorId, context);
    }
    return (result);
}


/*******************************************************************************
* Function Name: CapSense_SnsShortCheckElectrodeV2
****************************************************************************//**
*
* This internal function checks if a sensor or Rx or Tx electrode is shorted
* to VDD or GND by configuring each of its pins to pull-up or pull-down
* and checks its state.
*
* An additional delay is added between configuring the electrode and
* reading its state to establish the transition process for cases
* with big capacitance and short resistance.
* The function assumes all rest electrodes are set to strong drive mode,
* so the sensor-to-sensor short condition is also detected.
*
* \param widgetId
* Specifies the ID number of the widget.
* A macro for the widget ID can be found in the
* CAPSENSE&trade; Configuration header file (cycfg_capsense.h) defined as
* CY_CAPSENSE_<WidgetName>_WDGT_ID.
*
* \param ioSnsId
* Specifies the ID number of the sensor (Rx or Tx electrode for CSX widgets)
* within the widget to be processed.
*
* \param mode
* Specifies the test mode, either:
* * CY_CAPSENSE_BIST_DR_PIN2GND means sensor is configured
*   to pull-up and checked for logical 0
* * CY_CAPSENSE_BIST_DR_PIN2VDD means sensor is configured
*   to pull-down and checked for logical 1
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E - The sensor pin(s) are not shorted.
* - CY_CAPSENSE_BIST_FAIL_E - A short is detected on the specified sensor.
*
*******************************************************************************/
static cy_en_capsense_bist_status_t Cy_CapSense_SnsShortCheckElectrode(
                uint32_t widgetId,
                uint32_t ioSnsId,
                uint32_t mode,
                const cy_stc_capsense_context_t * context)
{
    uint32_t i;
    uint32_t eltdNum;
    uint32_t eltdState;
    uint32_t eltdDM = CY_GPIO_DM_PULLDOWN;
    cy_en_capsense_bist_status_t result;
    const cy_stc_capsense_pin_config_t *ioPtr = context->ptrWdConfig[widgetId].ptrEltdConfig[ioSnsId].ptrPin;

    if (CY_CAPSENSE_BIST_DR_PIN2GND == mode)
    {
        eltdDM = CY_GPIO_DM_PULLUP;
    }

    eltdNum = context->ptrWdConfig[widgetId].ptrEltdConfig[ioSnsId].numPins;

    /* Loop through all electrodes of the specified sensor */
    for (i = 0u; i < eltdNum; i++)
    {
        /* Set pin Drive mode and data register */
        Cy_CapSense_SetPinDr(ioPtr, (mode ^ 0x01u));
        Cy_CapSense_SetPinPc(ioPtr, eltdDM);
        /* Wait for establishing the transition process */
        Cy_SysLib_DelayUs((uint16_t)context->ptrBistContext->snsIntgShortSettlingTime);
        /* Read the electrode state */
        eltdState = Cy_GPIO_Read(ioPtr->pcPtr, (uint32_t)ioPtr->pinNumber);
        if (CY_CAPSENSE_BIST_DR_PIN2GND != eltdState)
        {
            eltdState = CY_CAPSENSE_BIST_DR_PIN2VDD;
        }
        /* Revert the electrode to the default Drive mode */
        Cy_CapSense_SetPinDr(ioPtr, mode);
        Cy_CapSense_SetPinPc(ioPtr, CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF);
        /* Check the electrode state */
        if (mode == eltdState)
        {
            result = CY_CAPSENSE_BIST_FAIL_E;
            break;
        }
        else
        {
            result = CY_CAPSENSE_BIST_SUCCESS_E;
        }
        /* Get the next electrode */
        ioPtr++;
    }
    return (result);
}


/*******************************************************************************
* Function Name: Cy_CapSense_SnsShortUpdateTestResult
****************************************************************************//**
* The internal function updates the BIST data structure and Widget Working bit
* in the .status field of the cy_stc_capsense_widget_context_t structure.
*
* The function resets a Widget Working bit, checks the .testResultMask field
* of the cy_stc_capsense_bist_context_t structure
* for the CY_CAPSENSE_BIST_SNS_INTEGRITY_MASK bit and if it was not set to 1,
* the function sets it and memorizes widgetId and sensorId
* in corresponding fields of the cy_stc_capsense_bist_context_t structure.
*
* \param widgetId
* Specifies the ID number of the widget to be processed.
*
* \param sensorId
* Specifies the ID number of the sensor within the widget which
* will be processed.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_SnsShortUpdateTestResult(
                uint32_t widgetId,
                uint32_t sensorId,
                cy_stc_capsense_context_t * context)
{
    context->ptrWdContext[widgetId].status &= (uint8_t)~CY_CAPSENSE_WD_WORKING_MASK;
    if (0Lu == (context->ptrBistContext->testResultMask & CY_CAPSENSE_BIST_SNS_INTEGRITY_MASK))
    {
        /* Write to the BIST context structure widgetId and sensorId of the first shorted sensor */
        context->ptrBistContext->testResultMask |= CY_CAPSENSE_BIST_SNS_INTEGRITY_MASK;
        context->ptrBistContext->shortedWdId = (uint8_t)widgetId;
        context->ptrBistContext->shortedSnsId = (uint8_t)sensorId;
    }
}


/*******************************************************************************
* Function Name: Cy_CapSense_SnsShortCheckAllSensors
****************************************************************************//**
*
* The internal function that checks for all the sensors short.
*
* The function that checks for shorts on VDD/GND or to another sensors of all
* sensor (not electrode) by using the Cy_CapSense_SnsShortCheckSensor() function.
* The function is called by the Cy_CapSense_RunSelfTest() function.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the test processing:
* - CY_CAPSENSE_BIST_SUCCESS_E if test passed successfully;
* - CY_CAPSENSE_BIST_FAIL_E if any sensor of any widget is
*   shorted to VDD or GND.
*
*******************************************************************************/
static cy_en_capsense_bist_status_t Cy_CapSense_SnsShortCheckAllSensors(
                cy_stc_capsense_context_t * context)
{
    uint32_t widgetId;
    uint32_t sensorId;
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_SUCCESS_E;

    /* Previously-captured HW resources were released by the other mode in the RunSelfTest function */
    /* Switch HW resource configuration to sensor short test */
    Cy_CapSense_BistSwitchHwConfig(CY_CAPSENSE_BIST_HW_SHORT_E, context);

    Cy_CapSense_BistSwitchAllSnsPinState(CY_CAPSENSE_BIST_IO_STRONG_HIGH_E, context);
    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
        Cy_CapSense_BistSwitchAllShieldPinState(CY_CAPSENSE_BIST_IO_STRONG_HIGH_E, context);
    #endif
    Cy_CapSense_BistSwitchAllExternalCapPinState(CY_CAPSENSE_BIST_IO_STRONG_HIGH_E, context);
    /* Wait for the maximum possible external capacitor charging time */
    Cy_SysLib_DelayUs(context->ptrBistContext->capacitorSettlingTime);

    for (widgetId = 0u; widgetId < context->ptrCommonConfig->numWd; widgetId++)
    {
        for (sensorId = 0u; sensorId < context->ptrWdConfig[widgetId].numSns; sensorId++)
        {
            if (CY_CAPSENSE_BIST_SUCCESS_E != Cy_CapSense_SnsShortCheckSensor(widgetId, sensorId, CY_CAPSENSE_BIST_DR_PIN2VDD, context))
            {
                result = CY_CAPSENSE_BIST_FAIL_E;
                break;
            }
        }
    }

    Cy_CapSense_BistSwitchAllSnsPinState(CY_CAPSENSE_BIST_IO_STRONG_E, context);
    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
        Cy_CapSense_BistSwitchAllShieldPinState(CY_CAPSENSE_BIST_IO_STRONG_E, context);
    #endif
    Cy_CapSense_BistSwitchAllExternalCapPinState(CY_CAPSENSE_BIST_IO_STRONG_E, context);
    /* Wait for the maximum possible external capacitor charging time */
    Cy_SysLib_DelayUs(context->ptrBistContext->capacitorSettlingTime);

    for (widgetId = 0u; widgetId < context->ptrCommonConfig->numWd; widgetId++)
    {
        for (sensorId = 0u; sensorId < context->ptrWdConfig[widgetId].numSns; sensorId++)
        {
            if (CY_CAPSENSE_BIST_SUCCESS_E != Cy_CapSense_SnsShortCheckSensor(widgetId, sensorId, CY_CAPSENSE_BIST_DR_PIN2GND, context))
            {
                result = CY_CAPSENSE_BIST_FAIL_E;
                break;
            }
        }
    }

    return (result);
}


/*******************************************************************************
* Function Name: Cy_CapSense_SetPinDr
****************************************************************************//**
*
* The internal function that sets a certain pin output data register (DR).
*
* The function sets a pin output data register (DR) in a desired state.
*
* \param *ioPtr
* A pointer to the specified pin in the widget pin configuration structure.
*
* \param value
* A port output data which will be set for the pin.
*
*******************************************************************************/
static void Cy_CapSense_SetPinDr(
                cy_stc_capsense_pin_config_t const *ioPtr,
                uint32_t value)
{
    uint32_t  interruptState;

    /* Set a data register */
    interruptState = Cy_SysLib_EnterCriticalSection();
    Cy_GPIO_Write(ioPtr->pcPtr, (uint32_t)ioPtr->pinNumber, value);
    Cy_SysLib_ExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Cy_CapSense_SetPinPc
****************************************************************************//**
*
* The internal function that sets a certain pin output drive mode (PC).
*
* The function sets a pin port control register (PC) in a desired state.
*
* \param *ioPtr
* A pointer to the specified pin in the widget pin configuration structure.
*
* \param value
* Drive mode to be set for the pin.
*
*******************************************************************************/
static void Cy_CapSense_SetPinPc(
                cy_stc_capsense_pin_config_t const *ioPtr,
                uint32_t value)
{
    uint32_t  interruptState;

    /* Update the port configuration register (Drive mode) */
    interruptState = Cy_SysLib_EnterCriticalSection();
    Cy_GPIO_SetDrivemode(ioPtr->pcPtr, (uint32_t)ioPtr->pinNumber, value);
    Cy_SysLib_ExitCriticalSection(interruptState);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_SHORT_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_MeasureCapacitanceSensor
****************************************************************************//**
*
* Measures the specified CSD sensor / CSX electrode capacitance in femtofarads.
*
* This function measures the capacitance of the sensor (electrode for CSX
* widgets) and returns the measurement status. For a CSX sensor, the
* measurement is done on either Rx or Tx electrode.
* For a CSD sensor, measurement is done on a sensor (refer to the
* sensorId parameter description).
* If the specified sensor (electrode) is a ganged sensor, the capacitance
* is measured for all the pins ganged together that belong to this sensor
* (electrode).
*
* The measured capacitance is stored in the .eltdCap[] array.
* The .ptrEltdCapacitance field of the
* \ref cy_stc_capsense_widget_config_t structure contains a pointer to
* the first widget sensor (electrode) element within the .eltdCap[] array.
*
* In addition to the measuring sensor (electrode) capacitance, this function
* is used to identify various fault conditions with sensors such
* as electrically-opened or -shorted sensors. For example, the PCB track is
* broken or shorted to other nodes in the system - in all of these conditions,
* this function returns changed capacitance which can be compared
* against predetermined capacitance for the sensor to detect a
* fault condition.
*
* The sensor capacitance is measured independently of the sensor scan
* configuration. For the capacitance measurement, the CSD sensing method is used.
* The measurements consists of up to four scans with different IDAC current.
* The IDAC current of the first measurement is 6 uA and each next measurement
* the IDAC current increase by four times. The default scanning parameters
* are the following:
* * I (6 uA) is the current equal to IDAC Gain * IDAC Code
*   (Compensation IDAC is disabled).
* * Res (12 bits) is the scanning resolution.
* * Vref (1.2 V) is the reference voltage.
* * SnsClk (375 kHz) is the sensor clock frequency.
*
* If the scanning raw count is within 7.5% to 45% range of a maximum raw count
* the raw count is converted into capacitance using the following equation:
*
*  Cs = Rawcount * I / ((2^Res - 1) * Vref * SnsClk)
*
* where:
* * Cs is the sensor capacitance.
* * Rawcount is the measured raw count value.
*
* If the raw count is less than 7.5% of the maximum limit (2^Res - 1), the
* function stops scanning the sequence and returns the
* CY_CAPSENSE_BIST_LOW_LIMIT_E status.
*
* If the raw count is between 7.5% and 45% of the maximum, the function
* calculates the sensor capacitance, updates the register map and
* returns CY_CAPSENSE_BIST_SUCCESS_E status.
*
* If the raw count is above 45% of the maximum, the function repeats
* scanning with a 4x increased IDAC current (up to four scans in total).
*
* The minimum measurable input by this function is 1pF and the
* maximum is either 384pF or limited by the RC time constant
* (Cs < 1 / (2*5*SnsClk*R), where R is the total sensor series
* resistance that includes on-chip GPIO resistance ~500 Ohm and
* external series resistance). The measurement accuracy is about 15%.
*
* By default, all CAPSENSE&trade; sensors (electrodes) that are not being
* measured are set to the GND state for CSD measured electrodes (sensors) and
* to the HIGH-Z state for CSX measured electrodes (Rx and Tx).
* Shield electrodes are also configured to the GND state.
* The inactive state can be changed in run-time by using
* the Cy_CapSense_SetInactiveElectrodeState() function.
*
* By default, the Cmod capacitor is used for the measurement. If a dedicated
* Cmod is not available (e.g. the design has CSX widgets only), CintA and CintB
* capacitors are combined together by the firmware to form a single integration
* capacitor for the measurement.
*
* The sensor measurement can be done on all the sensors using
* the Cy_CapSense_RunSelfTest() function along with
* the CY_CAPSENSE_BIST_SNS_CAP_MASK mask.
*
* This function must not be called while the CSD HW block is busy by another
* state.
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
*
* \param widgetId
* Specifies the ID number of the widget.
* A macro for the widget ID can be found in the
* CAPSENSE&trade; Configuration header file (cycfg_capsense.h) defined as
* CY_CAPSENSE_<WidgetName>_WDGT_ID.
*
* \param sensorId
* Specifies the ID of the sensor (electrode for CSX widgets) within the widget
* to be measured.
*
* For the CSD widgets, a macro for the sensor ID within the specified widget
* can be found in the CAPSENSE&trade; Configuration header file (cycfg_capsense.h)
* defined as CY_CAPSENSE_<WidgetName>_SNS<SensorNumber>_ID.
*
* For the CSX widgets, sensorId is an electrode ID and is defined as Rx ID
* or Tx ID. The first Rx in a widget corresponds to electrodeId = 0, the
* second Rx in a widget corresponds to electrodeId = 1, and so on.
* The last Tx in a widget corresponds to electrodeId = (RxNum + TxNum - 1).
* Macros for Rx and Tx IDs can be found in the CAPSENSE&trade; Configuration header
* file (cycfg_capsense.h) defined as:
* * CapSense_<WidgetName>_RX<RXNumber>_ID
* * CapSense_<WidgetName>_TX<TXNumber>_ID.
*
* \param ptrValue
* The pointer to the measured capacitance in femtofarads.
* The user declares a variable of the uint32_t type and passes the variable
* pointer as the function parameter. If the ptrValue parameter is NULL,
* the capacitance value is not returned through the parameter but still stored
* in the corresponding field of the data structure.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E          - The measurement completes
*                                         successfully, the result is valid.
* - CY_CAPSENSE_BIST_BAD_PARAM_E        - The input parameter is invalid.
*                                         The measurement was not executed.
* - CY_CAPSENSE_BIST_HW_BUSY_E          - The CSD HW block is busy with a
*                                         previous operation.
*                                         The measurement was not executed.
* - CY_CAPSENSE_BIST_LOW_LIMIT_E        - The measurement was executed and
*                                         the scanning result is below
*                                         the minimum possible value.
*                                         The measurement result could be invalid.
*                                         The sensor might be shorted to VDD
*                                         or a sensor PCB track
*                                         was broken (open sensor).
* - CY_CAPSENSE_BIST_HIGH_LIMIT_E       - The measurement was executed and
*                                         the scanning result is above the
*                                         maximum possible value.
*                                         The measurement result could be invalid.
*                                         The sensor might be shorted to GND.
* - CY_CAPSENSE_BIST_ERROR_E            - An unexpected fault occurred during
*                                         the measurement.
*
*******************************************************************************/
cy_en_capsense_bist_status_t Cy_CapSense_MeasureCapacitanceSensor(
                uint32_t widgetId,
                uint32_t sensorId,
                uint32_t * ptrValue,
                cy_stc_capsense_context_t * context)
{
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_BAD_PARAM_E;
    cy_en_capsense_bist_io_state_t desiredIoState;
    uint32_t numWdgtElectrodes;
    cy_en_capsense_bist_hw_config_t hwConfiguration;
    uint32_t convNumber;

    if(NULL != context)
    {
        if ((context->ptrCommonConfig->numWd > widgetId))
        {
            /* Get a total number of the widget elements: for CSX, it is numRows + numCols, for CSD, it is totalNumSns */
            if (CY_CAPSENSE_CSX_GROUP == context->ptrWdConfig[widgetId].senseMethod)
            {
                /* For CSX widgets, get the index of the Rx electrode */
                numWdgtElectrodes = context->ptrWdConfig[widgetId].numRows +
                          (uint32_t)context->ptrWdConfig[widgetId].numCols;
            }
            else
            {
                numWdgtElectrodes = context->ptrWdConfig[widgetId].numSns;
            }
            if (numWdgtElectrodes > sensorId)
            {
                /* Release previously-captured HW resources by other mode and capture them for BIST */
                if (CY_CAPSENSE_SUCCESS_E == Cy_CapSense_SwitchSensingMode(CY_CAPSENSE_BIST_GROUP, context))
                {
                    /* Set the BUSY status */
                    context->ptrCommonContext->status = CY_CAPSENSE_BUSY;
                    /* Choose an inactive sensor connection (ISC) depending on the widget type */
                    switch (context->ptrWdConfig[widgetId].senseMethod)
                    {
                        case CY_CAPSENSE_CSD_GROUP:
                            desiredIoState = context->ptrBistContext->intrEltdCapCsdISC;
                            break;
                        case CY_CAPSENSE_CSX_GROUP:
                            desiredIoState = context->ptrBistContext->intrEltdCapCsxISC;
                            break;
                        default:
                            desiredIoState = CY_CAPSENSE_BIST_IO_UNDEFINED_E;
                            break;
                    }

                    hwConfiguration = CY_CAPSENSE_BIST_HW_ELTD_CAP_E;
                    if (CY_CAPSENSE_BIST_IO_SHIELD_E == desiredIoState)
                    {
                        hwConfiguration = CY_CAPSENSE_BIST_HW_ELTD_CAP_SH_E;
                    }
                    /* Switch the HW resource configuration to the sensor element capacitance measurement */
                    Cy_CapSense_BistSwitchHwConfig(hwConfiguration, context);
                    Cy_CapSense_BistSwitchAllSnsPinState(desiredIoState, context);

                    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
                        Cy_CapSense_BistSwitchAllShieldPinState(CY_CAPSENSE_BIST_IO_STRONG_E, context);
                    #endif

                    /* Set the divider value for the mod clock 1u lower than the desired divider */
                    Cy_CapSense_SetClkDivider(((uint32_t)context->ptrBistContext->eltdCapModClk - 1u), context);

                    /* Set the divider value for the sense clock (1u lower than the desired divider) */
                    context->ptrCommonConfig->ptrCsdBase->SENSE_PERIOD = ((uint32_t)context->ptrBistContext->eltdCapSnsClk - 1u);

                    /* Calculate the number of sub-conversions */
                    convNumber = (uint32_t)((0x01uL << context->ptrBistContext->eltdCapResolution) / context->ptrBistContext->eltdCapSnsClk);
                    if (convNumber == 0u)
                    {
                        convNumber = 1u;
                    }
                    context->ptrCommonConfig->ptrCsdBase->SEQ_NORM_CNT = convNumber;

                    Cy_CapSense_BistConnectElectrode(widgetId, sensorId, context);
                    result = Cy_CapSense_BistMeasureCapacitanceSensor(&context->ptrWdConfig[widgetId].ptrEltdCapacitance[sensorId], context);

                    Cy_CapSense_BistDisconnectElectrode(widgetId, sensorId, context);
                    if(NULL != ptrValue)
                    {
                        *ptrValue = context->ptrWdConfig[widgetId].ptrEltdCapacitance[sensorId];
                    }

                    /* Clear the BUSY flag */
                    context->ptrCommonContext->status = CY_CAPSENSE_NOT_BUSY;
                }
                else
                {
                    result = CY_CAPSENSE_BIST_HW_BUSY_E;
                }
            }
        }
    }

    return (result);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN) */


#if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN) &&\
     (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN))
/*******************************************************************************
* Function Name: Cy_CapSense_MeasureCapacitanceShield
****************************************************************************//**
*
* Measures shield electrode capacitance in femtofarads.
*
* This function measures the capacitance of the shield electrode and
* returns a status of this measurement. The measurement result in femtofarads
* is stored in the .shieldCap field of the \ref cy_stc_capsense_bist_context_t
* structure. If the shield consists of several electrodes, the total
* capacitance of all shield electrodes is reported.
*
* This function uses an algorithm identical to the sensor capacitance
* measurement. Refer to the Cy_CapSense_MeasureCapacitanceSensor() function
* for more details.
*
* In addition to measuring shield capacitance, this function is used to
* identify various fault conditions with a shield electrode such as an
* electrically-open or -short shield electrode, e.g. the PCB track is broken or
* shorted to other nodes in the system - in all of these conditions,
* this function returns changed capacitance that can be compared
* against pre-determined capacitance for the shield electrode to
* detect a fault condition.
*
* By default, all CAPSENSE&trade; sensors (electrodes) that are not being
* measured are set to the GND state.
* The inactive state can be changed in run-time by using
* the Cy_CapSense_SetInactiveElectrodeState() function.
* When the inactive sensor (electrode) connection is set
* to the CY_CAPSENSE_SNS_CONNECTION_SHIELD state,
* all the CAPSENSE&trade; electrodes are connected to the shield and
* the total capacitance are measured.
*
* By default, the Cmod capacitor is used for the measurement. If a dedicated
* Cmod is not available (e.g. the design has CSX widgets only), CintA and CintB
* capacitors are combined together by the firmware to form a single integration
* capacitor which is used for measurement.
*
* This test can be executed using the CapSense_RunSelfTest()
* function with the CY_CAPSENSE_BIST_SHIELD_CAP_MASK mask.
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
*
* \param ptrValue
* The pointer to the variable the measured capacitance is stored. The user
* should declare a variable of uint32_t type and pass the variable pointer as
* the function parameter. If the ptrValue parameter is NULL then the shield
* capacitance value is not returned through the parameter but is still stored
* in the .shieldCap field of the \ref cy_stc_capsense_bist_context_t structure.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E          - The measurement completes
*                                         successfully, the result is valid.
* - CY_CAPSENSE_BIST_BAD_PARAM_E        - The input parameter is invalid.
*                                         The measurement was not executed.
* - CY_CAPSENSE_BIST_HW_BUSY_E          - The CSD HW block is busy with a
*                                         previous operation. The measurement
*                                         was not executed.
* - CY_CAPSENSE_BIST_LOW_LIMIT_E        - The measurement was executed but
*                                         the measured raw count is below
*                                         the minimum possible value.
*                                         The measurement result could be invalid.
*                                         The shield might be shorted to VDD
*                                         or a shield PCB track
*                                         is broken (the open shield electrode).
* - CY_CAPSENSE_BIST_HIGH_LIMIT_E       - The measurement was executed but the
*                                         measured raw count is above the
*                                         maximum possible value.
*                                         The measurement result is invalid.
*                                         The sensor might be shorted to GND.
* - CY_CAPSENSE_BIST_ERROR_E            - An unexpected fault occurred during
*                                         the measurement.
*
*******************************************************************************/
cy_en_capsense_bist_status_t Cy_CapSense_MeasureCapacitanceShield(
                uint32_t * ptrValue,
                cy_stc_capsense_context_t * context)
{
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_BAD_PARAM_E;
    uint32_t convNumber;

    if(NULL != context)
    {
        if((0u != context->ptrCommonConfig->csdShieldNumPin) ||
           (CY_CAPSENSE_BIST_IO_SHIELD_E == context->ptrBistContext->intrEltdCapShieldISC))
        {
            /* Release previously-captured HW resources by the other mode and capture them for BIST */
            if (CY_CAPSENSE_SUCCESS_E == Cy_CapSense_SwitchSensingMode(CY_CAPSENSE_BIST_GROUP, context))
            {
                /* Set the BUSY status */
                context->ptrCommonContext->status = CY_CAPSENSE_BUSY;

                /* Set all sensor pins to an ISC */
                if(CY_CAPSENSE_BIST_IO_SHIELD_E == context->ptrBistContext->intrEltdCapShieldISC)
                {
                    Cy_CapSense_BistSwitchAllSnsPinState(CY_CAPSENSE_BIST_IO_SENSE_E, context);
                }
                else
                {
                    Cy_CapSense_BistSwitchAllSnsPinState(context->ptrBistContext->intrEltdCapShieldISC, context);
                }

                /* Connect shield electrode(s) to Analog bus A to measure the capacitance */
                Cy_CapSense_SetShieldPinState(CY_CAPSENSE_CSD_SCAN_PIN_DM, 0u, CY_CAPSENSE_HSIOM_SEL_CSD_SENSE, context);
                /* Switch theHW resource configuration to the sensor short test */
                Cy_CapSense_BistSwitchHwConfig(CY_CAPSENSE_BIST_HW_ELTD_CAP_E, context);
                /* Set the divider value for mod clock (1u lower than the desired divider) */
                Cy_CapSense_SetClkDivider(((uint32_t)context->ptrBistContext->eltdCapModClk - 1u), context);
                /* Set the divider value for the sense clock (1u lower than the desired divider) */
                context->ptrCommonConfig->ptrCsdBase->SENSE_PERIOD = ((uint32_t)context->ptrBistContext->eltdCapSnsClk - 1u);
                /* Calculate the conversion number to rich the desired resolution */
                convNumber = (uint32_t)((0x01uL << context->ptrBistContext->eltdCapResolution) / context->ptrBistContext->eltdCapSnsClk);
                if (convNumber == 0u)
                {
                    convNumber = 1u;
                }

                /* Set Number Of Conversions based on scanning resolution */
                context->ptrCommonConfig->ptrCsdBase->SEQ_NORM_CNT = convNumber;
                /* Measure and store the shield electrode(s) capacitance value, return the value and status */
                result = Cy_CapSense_BistMeasureCapacitanceSensor(&context->ptrBistContext->shieldCap, context);
                if(NULL != ptrValue)
                {
                    *ptrValue = context->ptrBistContext->shieldCap;
                }

                /* Clear the BUSY flag */
                context->ptrCommonContext->status = CY_CAPSENSE_NOT_BUSY;
            }
            else
            {
                result = CY_CAPSENSE_BIST_HW_BUSY_E;
            }
        }
    }

    return (result);
}
#endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN) && (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_MeasureCapacitanceSensorExt
****************************************************************************//**
*
* Measures specified widget/sensor (electrode) capacitance using specified
* scanning parameters.
*
* This function performs a single scan using the CSD sensing method and then
* converts the measured raw count into capacitance using the following equation:
*
* Cs = Rawcount * I / ((2^Res - 1) * Vref * SnsClk)
*
* Where:
* * Cs is the sensor capacitance.
* * Rawcount is the measured raw count value.
* * I is the current equal to IDAC gain * IDAC code
*   (Compensation IDAC is disabled).
* * Res is the scanning resolution.
* * Vref is the reference voltage.
* * SnsClk is the sensor clock frequency.
*
* By default,the  Cmod capacitor is used for the measurement. If a dedicated
* Cmod is not available (e.g. the design has CSX widgets only), the CintA and
* CintB capacitors are combined together by the firmware to form a single
* integration capacitor for the measurement.
*
* This function must not be called while the CSD HW block is busy by another
* state.
*
* It is not recommended to use this function in application code. The function
* usage requires expert knowledge of the CAPSENSE&trade; HW block, details of operation,
* details of scanning parameters, and their interdependencies. The function
* does not perform parameter values validation, and it is easy to break
* CAPSENSE&trade; operation using this function.
*
* \param widgetId
* Specifies the ID number of the widget.
* A macro for the widget ID can be found in the
* CAPSENSE&trade; Configuration header file (cycfg_capsense.h) defined as
* CY_CAPSENSE_<WidgetName>_WDGT_ID.
*
* \param sensorId
* Specifies the ID of the sensor (electrode for CSX widgets) within the widget
* to be measured.
*
* For the CSD widgets, a macro for the sensor ID within the specified widget
* can be found in the CAPSENSE&trade; Configuration header file (cycfg_capsense.h)
* defined as CY_CAPSENSE_<WidgetName>_SNS<SensorNumber>_ID.
*
* For the CSX widgets, sensorId is an electrode ID and is defined as Rx ID
* or Tx ID. The first Rx in a widget corresponds to electrodeId = 0, the
* second Rx in a widget corresponds to electrodeId = 1, and so on.
* The last Tx in a widget corresponds to electrodeId = (RxNum + TxNum - 1).
* Macros for Rx and Tx IDs can be found in the CAPSENSE&trade; Configuration header
* file (cycfg_capsense.h) defined as:
* * CapSense_<WidgetName>_RX<RXNumber>_ID
* * CapSense_<WidgetName>_TX<TXNumber>_ID.
*
* \param ptrScanConfig
* The pointer to the scan configuration parameter structure. The user
* should initialize all the scan configuration parameters before
* the function usage.
*
* \param ptrValue
* The pointer to the result of scan. The result is calculated as a sensor
* capacitance value in femtofarads. The user
* declares a variable of uint32_t type and passes the variable pointer as
* the function parameter.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E          - The scan completes successfully,
*                                         the calculated capacitance value is valid.
* - CY_CAPSENSE_BIST_BAD_PARAM_E        - The input parameter is invalid.
*                                         The measurement was not executed.
* - CY_CAPSENSE_BIST_HW_BUSY_E          - The CSD HW block is busy with a
*                                         previous operation. The measurement
*                                         was not executed.
* - CY_CAPSENSE_BIST_TIMEOUT_E          - The software watchdog timeout occurred
*                                         during the scan, the scan was not
*                                         completed, the calculated
*                                         capacitance is invalid.
*
*******************************************************************************/
cy_en_capsense_bist_status_t Cy_CapSense_MeasureCapacitanceSensorExt(
                uint32_t widgetId,
                uint32_t sensorId,
                cy_stc_capsense_bist_custom_parameters_t * ptrScanConfig,
                uint32_t * ptrValue,
                cy_stc_capsense_context_t * context)
{
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_BAD_PARAM_E;
    cy_en_capsense_bist_io_state_t desiredIoState;
    cy_en_capsense_bist_hw_config_t hwConfiguration;
    uint32_t numWdgtElectrodes;
    uint32_t rawCountTmp;
    uint32_t idacIdx;
    uint32_t idacCode;
    uint32_t snsClkFreqHz;
    uint32_t rawMaxNum;
    uint32_t vRefMv;
    uint32_t temp;
    uint64_t cp;
    uint32_t modClkDivider;
    uint32_t snsClkDivider;
    uint32_t cpuFreqMHz;
    uint32_t watchdogPeriod;
    uint64_t isBusyWatchdogTimeUs;


    if((NULL != context) && (NULL != ptrScanConfig))
    {
        idacIdx = (uint32_t)ptrScanConfig->idacGainIndex;
        idacCode = (uint32_t)ptrScanConfig->idacMod;
        if (0u == ptrScanConfig->modClk)
        {
            ptrScanConfig->modClk = 1u;
        }
        snsClkFreqHz = context->ptrCommonConfig->periClkHz / ptrScanConfig->modClk / ptrScanConfig->snsClk;
        rawMaxNum = ((uint32_t)ptrScanConfig->convNum * (uint32_t)ptrScanConfig->snsClk) - 1u;

        if ((context->ptrCommonConfig->numWd > widgetId))
        {
            /* Get a total number of widget elements: for CSX, it is numRows + numCols, for CSD, it is totalNumSns */
            if (CY_CAPSENSE_CSX_GROUP == context->ptrWdConfig[widgetId].senseMethod)
            {
                /* For CSX widgets, get the index of the Rx electrode */
                numWdgtElectrodes = context->ptrWdConfig[widgetId].numRows +
                          (uint32_t)context->ptrWdConfig[widgetId].numCols;
                desiredIoState = context->ptrBistContext->intrEltdCapCsxISC;
            }
            else
            {
                numWdgtElectrodes = context->ptrWdConfig[widgetId].numSns;
                desiredIoState = context->ptrBistContext->intrEltdCapCsdISC;
            }
            if (numWdgtElectrodes > sensorId)
            {
                /* Release previously-captured HW resources by the other mode and capture them for BIST */
                if (CY_CAPSENSE_SUCCESS_E == Cy_CapSense_SwitchSensingMode(CY_CAPSENSE_BIST_GROUP, context))
                {
                    /* Set the BUSY status */
                    context->ptrCommonContext->status = CY_CAPSENSE_BUSY;
                    hwConfiguration = CY_CAPSENSE_BIST_HW_ELTD_CAP_E;
                    if (CY_CAPSENSE_BIST_IO_SHIELD_E == desiredIoState)
                    {
                        hwConfiguration = CY_CAPSENSE_BIST_HW_ELTD_CAP_SH_E;
                    }
                    /* Switch the HW resource configuration to sensor short test */
                    Cy_CapSense_BistSwitchHwConfig(hwConfiguration, context);
                    Cy_CapSense_BistSwitchAllSnsPinState(desiredIoState, context);
                    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
                        Cy_CapSense_BistSwitchAllShieldPinState(CY_CAPSENSE_BIST_IO_STRONG_E, context);
                    #endif
                    /* Calculate the VrefHigh voltage */
                    vRefMv = Cy_CapSense_GetVrefHighMv((uint32_t)ptrScanConfig->vrefGain, context);

                    /* RefGen initialization */
                    temp = CSD_REFGEN_REFGEN_EN_Msk | CSD_REFGEN_RES_EN_Msk |
                            ((uint32_t)ptrScanConfig->vrefGain << CSD_REFGEN_GAIN_Pos);
                    #if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
                        if (CY_CAPSENSE_LOW_VOLTAGE_LIMIT > context->ptrCommonConfig->vdda)
                        {
                            temp = CSD_REFGEN_REFGEN_EN_Msk | CSD_REFGEN_BYPASS_Msk;
                        }
                    #endif
                    context->ptrCommonConfig->ptrCsdBase->REFGEN = temp;

                    /* Connect the specified sensor (CSX electrode) */
                    Cy_CapSense_BistConnectElectrode(widgetId, sensorId, context);
                    /* Set the divider value for the mod clock (1u lower than the desired divider) */
                    Cy_CapSense_SetClkDivider(((uint32_t)ptrScanConfig->modClk - 1u), context);
                    /* Set the divider value for the sense clock (1u lower than the desired divider) */
                    context->ptrCommonConfig->ptrCsdBase->SENSE_PERIOD = ((uint32_t)ptrScanConfig->snsClk - 1u);
                    /* Set Number Of Conversions for the custom scan */
                    context->ptrCommonConfig->ptrCsdBase->SEQ_NORM_CNT = (uint32_t)ptrScanConfig->convNum;
                    /* Setup the IDAC code and Gain */
                    context->ptrCommonConfig->ptrCsdBase->IDACA =
                            (context->ptrCommonConfig->ptrCsdBase->IDACA & ~CY_CAPSENSE_BIST_IDAC_BITS_TO_WRITE) |
                            ((context->ptrCommonConfig->idacGainTable[idacIdx].gainReg | idacCode |
                            CSD_IDACA_LEG1_MODE_Msk | CSD_IDACA_LEG2_MODE_Msk) & CY_CAPSENSE_BIST_IDAC_BITS_TO_WRITE);

                    /* Perform scanning */
                    result = Cy_CapSense_BistMeasureCapacitanceSensorRun(context);
                    if (CY_CAPSENSE_BIST_TIMEOUT_E != result)
                    {
                        modClkDivider = ptrScanConfig->modClk;
                        snsClkDivider = ptrScanConfig->snsClk;

                        if(0u == snsClkDivider)
                        {
                            snsClkDivider = 1u;
                        }

                        isBusyWatchdogTimeUs  = (uint64_t)ptrScanConfig->convNum;
                        isBusyWatchdogTimeUs *= (uint64_t)snsClkDivider * modClkDivider * CY_CAPSENSE_CONVERSION_MEGA;
                        isBusyWatchdogTimeUs /= context->ptrCommonConfig->periClkHz;

                        if(0u == isBusyWatchdogTimeUs)
                        {
                            isBusyWatchdogTimeUs = 1u;
                        }

                        isBusyWatchdogTimeUs *= CY_CAPSENSE_BIST_WATCHDOG_MARGIN_COEFF;

                        cpuFreqMHz = context->ptrCommonConfig->cpuClkHz / CY_CAPSENSE_CONVERSION_MEGA;
                        watchdogPeriod = Cy_CapSense_WatchdogCyclesNum((uint32_t)isBusyWatchdogTimeUs, cpuFreqMHz,
                                                                       CY_CAPSENSE_BIST_CAP_MEAS_WDT_CYCLES_PER_LOOP);

                        /* Wait for the end of the scan and get the raw counts */
                        if (0u == Cy_CapSense_BistWaitEndOfScan(watchdogPeriod, context))
                        {
                            result = CY_CAPSENSE_BIST_TIMEOUT_E;
                        }
                        else
                        {
                            rawCountTmp = (context->ptrCommonConfig->ptrCsdBase->RESULT_VAL1 &
                                          CY_CAPSENSE_CSD_RESULT_VAL1_VALUE_MSK);
                            /* Capacitance calculation and storage */
                            if(NULL != ptrValue)
                            {
                                cp = ((uint64_t)context->ptrCommonConfig->idacGainTable[idacIdx].gainValue) * (uint64_t)idacCode;
                                cp *= (uint64_t)rawCountTmp;
                                cp *= CY_CAPSENSE_CONVERSION_MEGA;
                                cp /= (uint64_t)rawMaxNum;
                                cp /= (uint64_t)snsClkFreqHz;
                                cp /= (uint64_t)vRefMv;
                                if (((uint64_t)CY_CAPSENSE_BIST_CP_MAX_VALUE) < cp)
                                {
                                    cp = (uint64_t)CY_CAPSENSE_BIST_CP_MAX_VALUE;
                                }
                                *ptrValue = (uint32_t)cp;
                            }
                            result = CY_CAPSENSE_BIST_SUCCESS_E;
                        }
                    }
                    /* Clear all interrupt pending requests */
                    context->ptrCommonConfig->ptrCsdBase->INTR = CY_CAPSENSE_CSD_INTR_ALL_MSK;
                    (void)context->ptrCommonConfig->ptrCsdBase->INTR;
                    /* Disconnect the sensor */
                    Cy_CapSense_BistDisconnectElectrode(widgetId, sensorId, context);
                    /* Clear the BUSY flag */
                    context->ptrCommonContext->status = CY_CAPSENSE_NOT_BUSY;
                }
                else
                {
                    result = CY_CAPSENSE_BIST_HW_BUSY_E;
                }
            }
        }
    }

    return (result);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN) */


#if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN) ||\
     (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN))
/*******************************************************************************
* Function Name: Cy_CapSense_BistMeasureCapacitanceSensorInit
****************************************************************************//**
*
* This internal function calculates the parameters for sensor or shield
* capacitance measurements and register values before speeding up
* the execution.
*
* It is called by Cy_CapSense_BistDsInitialize() once at the CAPSENSE&trade; MW start.
*
* The following parameters of cy_stc_capsense_bist_context_t are used as
* an input for the calculation:
* * .eltdCapModClk
* * .eltdCapSnsClk
* * .eltdCapVrefMv
* * .eltdCapResolution
*
* The function checks for parameter limitations and corrects the values before
* the calculation if they exceed.
*
* The following parameters of cy_stc_capsense_bist_context_t are updated
* by the calculation:
* * .eltdCapModClk
* * .eltdCapSnsClk
* * .eltdCapSnsClkFreqHz
* * .eltdCapVrefGain
* * .eltdCapVrefMv
* * .eltdCapResolution
*
* Restarting CAPSENSE&trade; MW or calling of the Cy_CapSense_BistDsInitialize()
* function overwrites the output parameters.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_BistMeasureCapacitanceSensorInit(
                cy_stc_capsense_context_t * context)
{
    uint32_t temp;
    cy_stc_capsense_bist_context_t * ptrBistCxt = context->ptrBistContext;

    /* ModClk */
    if (0u == ptrBistCxt->eltdCapModClk)
    {
        ptrBistCxt->eltdCapModClk = 1u;
    }
    if (CY_CAPSENSE_BIST_ELTD_CAP_MAX_MODCLK < (context->ptrCommonConfig->periClkHz / ptrBistCxt->eltdCapModClk))
    {
        ptrBistCxt->eltdCapModClk <<= 1u;
    }

    /* SnsClk */
    if (0u == ptrBistCxt->eltdCapSnsClk)
    {
        /*
         * Calculate the snsClc divider with rounding to achieve a frequency closer to
         * CY_CAPSENSE_BIST_ELTD_CAP_SNSCLK_DEFAULT snsClk
         */
        ptrBistCxt->eltdCapSnsClk = (uint16_t)(((context->ptrCommonConfig->periClkHz / ptrBistCxt->eltdCapModClk) +
                (CY_CAPSENSE_BIST_ELTD_CAP_SNSCLK_DEFAULT >> 1uL)) / CY_CAPSENSE_BIST_ELTD_CAP_SNSCLK_DEFAULT);
    }
    /* Check the snsClk divider value */
    if (CY_CAPSENSE_BIST_SNS_CLK_MIN_DIVIDER > ptrBistCxt->eltdCapSnsClk)
    {
        ptrBistCxt->eltdCapSnsClk = CY_CAPSENSE_BIST_SNS_CLK_MIN_DIVIDER;
    }
    if (CY_CAPSENSE_BIST_SNS_CLK_MAX_DIVIDER < ptrBistCxt->eltdCapSnsClk)
    {
        ptrBistCxt->eltdCapSnsClk = CY_CAPSENSE_BIST_SNS_CLK_MAX_DIVIDER;
    }
    ptrBistCxt->eltdCapSnsClkFreqHz = context->ptrCommonConfig->periClkHz / ptrBistCxt->eltdCapModClk / ptrBistCxt->eltdCapSnsClk;

    /* Reference Voltage */
    if(ptrBistCxt->eltdCapVrefMv == 0u)
    {
        /* Get the recommended reference voltage */
        temp = CY_CAPSENSE_BIST_CAP_MEAS_VREF_MV_DEFAULT;
    }
    else
    {
        /* Use the user-defined reference voltage */
        temp = (uint32_t)ptrBistCxt->eltdCapVrefMv;
    }
    ptrBistCxt->eltdCapVrefGain = (uint8_t)Cy_CapSense_GetVrefHighGain(temp, context);
    ptrBistCxt->eltdCapVrefMv = (uint16_t)Cy_CapSense_GetVrefHighMv((uint32_t)ptrBistCxt->eltdCapVrefGain, context);

    /* Resolution */
    if (CY_CAPSENSE_BIST_ELTD_CAP_MAX_RESOLUTION < ptrBistCxt->eltdCapResolution)
    {
        ptrBistCxt->eltdCapResolution = CY_CAPSENSE_BIST_ELTD_CAP_MAX_RESOLUTION;
    }
    if (CY_CAPSENSE_BIST_ELTD_CAP_MIN_RESOLUTION > ptrBistCxt->eltdCapResolution)
    {
        ptrBistCxt->eltdCapResolution = CY_CAPSENSE_BIST_ELTD_CAP_MIN_RESOLUTION;
    }

    /* HW block register pre-calculation */
    /* BYP switch selection */
    ptrBistCxt->regSwBypSel = CY_CAPSENSE_CSD_SW_BYP_SEL_SW_BYA_MSK;
    ptrBistCxt->regSwBypSelShield = CY_CAPSENSE_CSD_SW_BYP_SEL_SW_BYA_MSK;
    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
        ptrBistCxt->regSwBypSel = CY_CAPSENSE_CSD_SW_BYP_SEL_SW_BYA_MSK | CY_CAPSENSE_CSD_SW_BYP_SEL_SW_BYB_MSK;
        ptrBistCxt->regSwBypSelShield = CY_CAPSENSE_CSD_SW_BYP_SEL_SW_BYA_MSK | CY_CAPSENSE_CSD_SW_BYP_SEL_SW_BYB_MSK;
    #endif

    ptrBistCxt->regAmbuf = 0u;
    ptrBistCxt->regSwResInit = ((uint32_t)context->ptrCommonConfig->csdInitSwRes << CSD_SW_RES_RES_HCAV_Pos) |
                               ((uint32_t)context->ptrCommonConfig->csdInitSwRes << CSD_SW_RES_RES_HCBV_Pos);
    ptrBistCxt->regSwResScan = ((uint32_t)context->ptrCommonConfig->csdShieldSwRes << CSD_SW_RES_RES_HCBV_Pos) |
                               ((uint32_t)context->ptrCommonConfig->csdShieldSwRes << CSD_SW_RES_RES_HCBG_Pos);
    ptrBistCxt->regIoSel = (CY_CAPSENSE_CSD_TX_N_OUT_EN_PHI1 | CY_CAPSENSE_CSD_TX_N_AMUXA_EN_PHI2);
    ptrBistCxt->regSwDsiSel = CY_CAPSENSE_BIST_SW_DSI_SEL_DEFAULT;
    ptrBistCxt->regSwRefgenSel = CY_CAPSENSE_CSD_SW_REFGEN_SEL_SW_SGR_MSK;

    #if (CY_CAPSENSE_PSOC6_FOURTH_GEN)
        if (CY_CAPSENSE_VREF_PASS == context->ptrCommonConfig->ssVrefSource)
        {
            ptrBistCxt->regSwRefgenSel = CY_CAPSENSE_CSD_SW_REFGEN_SEL_SW_SGRP_MSK;
        }
    #endif

    #if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
            switch (context->ptrInternalContext->csdCmodConnection)
            {
                case (uint8_t)CY_CAPSENSE_CMODPAD_E:
                    ptrBistCxt->regSwDsiSel |= CY_CAPSENSE_CSD_SW_DSI_SEL_CMOD_MSK;
                    break;
                case (uint8_t)CY_CAPSENSE_CTANKPAD_E:
                    ptrBistCxt->regSwDsiSel |= CY_CAPSENSE_CSD_SW_DSI_SEL_CSH_TANK_MSK;
                    break;
                default:
                    /* No action on other connection types */
                    break;
            }

            #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) && \
                (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_CAP_EN))
                switch (context->ptrInternalContext->csdCshConnection)
                {
                    case (uint8_t)CY_CAPSENSE_CMODPAD_E:
                        ptrBistCxt->regSwDsiSel |= CY_CAPSENSE_CSD_SW_DSI_SEL_CMOD_MSK;
                        break;
                    case (uint8_t)CY_CAPSENSE_CTANKPAD_E:
                        ptrBistCxt->regSwDsiSel |= CY_CAPSENSE_CSD_SW_DSI_SEL_CSH_TANK_MSK;
                        break;
                    default:
                        /* No action on other connection types */
                        break;
                }
            #endif
        #else
            ptrBistCxt->regSwDsiSel = CY_CAPSENSE_CSD_SW_DSI_SEL_CMOD_MSK |
                    CY_CAPSENSE_CSD_SW_DSI_SEL_CSH_TANK_MSK;
        #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

    #endif

    /* Prepares a CONFIG register value */
    if ((context->ptrCommonConfig->periClkHz / context->ptrBistContext->eltdCapModClk) > CY_CAPSENSE_MOD_CSD_CLK_24000000_HZ)
    {
        ptrBistCxt->regConfig = CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_48MHZ;
    }
    else if ((context->ptrCommonConfig->periClkHz / context->ptrBistContext->eltdCapModClk) > CY_CAPSENSE_MOD_CSD_CLK_12000000_HZ)
    {
        ptrBistCxt->regConfig = CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_24MHZ;
    }
    else
    {
        ptrBistCxt->regConfig = CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_12MHZ;
    }

    #if (CY_CAPSENSE_PSOC6_FOURTH_GEN)
        if (CY_CAPSENSE_IREF_PASS == context->ptrCommonConfig->ssIrefSource)
        {
            ptrBistCxt->regConfig |= CY_CAPSENSE_CSD_CONFIG_IREF_SEL_MSK;
        }
    #endif

    ptrBistCxt->regConfig |= CSD_CONFIG_SENSE_EN_Msk | CSD_CONFIG_ENABLE_Msk;

    ptrBistCxt->regSwShieldSelScan = 0u;
    ptrBistCxt->regSwShieldSelScanShield = 0u;

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_CAP_EN)
            ptrBistCxt->regSwShieldSelScan = CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBV_PHI1_HSCMP;
            ptrBistCxt->regSwShieldSelScanShield = CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBV_PHI1_HSCMP;
        #else
            ptrBistCxt->regSwShieldSelScan = CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBG_PHI1 |
                                             CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBV_PHI2_HSCMP;
            ptrBistCxt->regSwShieldSelScanShield = CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBG_PHI1 |
                                                   CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBV_PHI2_HSCMP;
        #endif
    #endif

    /* High-Speed Comparator initialization */
    ptrBistCxt->regHscmpScan = CY_CAPSENSE_CSD_HSCMP_HSCMP_EN_MSK;
    ptrBistCxt->regHscmpScanShield = CY_CAPSENSE_CSD_HSCMP_HSCMP_EN_MSK;

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
        ptrBistCxt->regHscmpScan = 0u;
        ptrBistCxt->regHscmpScanShield = 0u;
    #endif

    ptrBistCxt->regSwHsPSelCmodInit = 0u;
    ptrBistCxt->regSwHsPSelCtankInit = 0u;
    ptrBistCxt->regSwHsPSelScan = 0u;
    ptrBistCxt->regSwHsPSelScanShield = 0u;
    switch (context->ptrInternalContext->csdCmodConnection)
    {
        case (uint8_t)CY_CAPSENSE_CMODPAD_E:
            ptrBistCxt->regSwHsPSelCmodInit = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE;
            break;
        case (uint8_t)CY_CAPSENSE_CSHIELDPAD_E:
            ptrBistCxt->regSwHsPSelCmodInit = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE;
            break;
        default:
            ptrBistCxt->regSwHsPSelCmodInit = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE;
            break;
    }

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_CAP_EN)
            switch (context->ptrInternalContext->csdCshConnection)
            {
                case (uint8_t)CY_CAPSENSE_CMODPAD_E:
                    ptrBistCxt->regSwHsPSelCtankInit = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE;
                    ptrBistCxt->regSwHsPSelScan = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE;
                    ptrBistCxt->regSwHsPSelScanShield = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE;
                    break;
                case (uint8_t)CY_CAPSENSE_CSHIELDPAD_E:
                    ptrBistCxt->regSwHsPSelCtankInit = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE;
                    ptrBistCxt->regSwHsPSelScan = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE;
                    ptrBistCxt->regSwHsPSelScanShield = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE;
                    break;
                default:
                    ptrBistCxt->regSwHsPSelCtankInit = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE;
                    ptrBistCxt->regSwHsPSelScan = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE;
                    ptrBistCxt->regSwHsPSelScanShield = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE;
                    break;
            }
        #else
            ptrBistCxt->regSwHsPSelScan = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE;
            ptrBistCxt->regSwHsPSelScanShield = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE;
        #endif
    #endif

    /* Pre-calculate config with a shield */
    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
        if (CY_CAPSENSE_LOW_VOLTAGE_LIMIT > context->ptrCommonConfig->vdda)
        {
            ptrBistCxt->regAmbuf = CY_CAPSENSE_CSD_AMBUF_PWR_MODE_NORM;
            ptrBistCxt->regAmbufShield = CY_CAPSENSE_CSD_AMBUF_PWR_MODE_NORM;
        }
        else
        {
            ptrBistCxt->regAmbuf = CY_CAPSENSE_CSD_AMBUF_PWR_MODE_HI;
            ptrBistCxt->regAmbufShield = CY_CAPSENSE_CSD_AMBUF_PWR_MODE_HI;
        }
    #else
        ptrBistCxt->regAmbuf = CY_CAPSENSE_CSD_AMBUF_PWR_MODE_OFF;
        ptrBistCxt->regAmbufShield = CY_CAPSENSE_CSD_AMBUF_PWR_MODE_OFF;
    #endif

    /* Switch AMUXBUF selection */
    ptrBistCxt->regSwAmuxbufSel = 0u;
    ptrBistCxt->regSwAmuxbufSelShield = 0u;
    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
        if (CY_CAPSENSE_LOW_VOLTAGE_LIMIT <= context->ptrCommonConfig->vdda)
        {
            ptrBistCxt->regSwAmuxbufSel = CY_CAPSENSE_CSD_SW_AMUXBUF_SEL_SW_IRH_STATIC_CLOSE |
                                          CY_CAPSENSE_CSD_SW_AMUXBUF_SEL_SW_ICB_PHI2;
            ptrBistCxt->regSwAmuxbufSelShield = CY_CAPSENSE_CSD_SW_AMUXBUF_SEL_SW_IRH_STATIC_CLOSE |
                                                CY_CAPSENSE_CSD_SW_AMUXBUF_SEL_SW_ICB_PHI2;
        }
    #endif

    ptrBistCxt->regIoSelShield = CY_CAPSENSE_CSD_TX_N_OUT_EN_PHI1 | CY_CAPSENSE_CSD_TX_N_AMUXA_EN_PHI2 |
            CY_CAPSENSE_CSD_TX_OUT_EN_PHI1_DELAY | CY_CAPSENSE_CSD_TX_AMUXB_EN_PHI2_DELAY;
    ptrBistCxt->regConfigShield = ptrBistCxt->regConfig |
            (((uint32_t)context->ptrCommonConfig->csdShieldDelay) << CY_CAPSENSE_CSD_CONFIG_SHIELD_DELAY_POS);
}


/*******************************************************************************
* Function Name: Cy_CapSense_BistMeasureCapacitanceSensorEnable
****************************************************************************//**
*
* The internal function sets up the CSD HW block to perform electrode
* (sensor or shield) capacitance measuring.
*
* This function prepares the CSD HW block to CSD sensing mode
* with BIST-defined parameters.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_BistMeasureCapacitanceSensorEnable(
                cy_stc_capsense_context_t * context)
{
    CSD_Type * ptrCsdHwBase = context->ptrCommonConfig->ptrCsdBase;

    /* Connect External Capacitor as CMOD to AMUXBUS-A and to CSDCOMP */
    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
        Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCmod,
                (uint32_t)context->ptrCommonConfig->pinCmod, CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_HSIOM_SEL_AMUXA);
        ptrCsdHwBase->SW_CMP_P_SEL = context->ptrInternalContext->csdRegSwCmpPSel;

        #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) && \
             (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_CAP_EN))
            Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCsh, (uint32_t)context->ptrCommonConfig->pinCsh,
                    CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_HSIOM_SEL_AMUXB);
        #endif
    #else /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */
        Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCintA,
                (uint32_t)context->ptrCommonConfig->pinCintA, CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_HSIOM_SEL_AMUXA);
        Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCintB,
                (uint32_t)context->ptrCommonConfig->pinCintB, CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_HSIOM_SEL_AMUXA);
        ptrCsdHwBase->SW_CMP_P_SEL = CY_CAPSENSE_CSD_SW_CMP_P_SEL_SW_SFPT_STATIC_CLOSE |
                                     CY_CAPSENSE_CSD_SW_CMP_P_SEL_SW_SFPM_STATIC_CLOSE;
    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

    ptrCsdHwBase->CONFIG = context->ptrBistContext->regConfig;
    ptrCsdHwBase->REFGEN =
            CSD_REFGEN_REFGEN_EN_Msk |
            CSD_REFGEN_RES_EN_Msk    |
            ((uint32_t)context->ptrBistContext->eltdCapVrefGain << CSD_REFGEN_GAIN_Pos);
    #if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
        if (CY_CAPSENSE_LOW_VOLTAGE_LIMIT > context->ptrCommonConfig->vdda)
        {
            ptrCsdHwBase->REFGEN = CSD_REFGEN_REFGEN_EN_Msk | CSD_REFGEN_BYPASS_Msk;
        }
    #endif
    ptrCsdHwBase->INTR_MASK = CY_CAPSENSE_CSD_INTR_MASK_CLEAR_MSK;
    ptrCsdHwBase->AMBUF = context->ptrBistContext->regAmbuf;
    ptrCsdHwBase->ADC_CTL = 0u;
    ptrCsdHwBase->SEQ_TIME = 0u;
    ptrCsdHwBase->IDACA = 0u;
    ptrCsdHwBase->IDACB = 0u;
    ptrCsdHwBase->SENSE_DUTY = CY_CAPSENSE_CSD_SENSE_DUTY_CFG;
    ptrCsdHwBase->INTR_SET = 0u;
    ptrCsdHwBase->SEQ_INIT_CNT = (uint32_t)context->ptrBistContext->fineInitTime;
    ptrCsdHwBase->SW_REFGEN_SEL = context->ptrBistContext->regSwRefgenSel;
    ptrCsdHwBase->SW_HS_N_SEL = CY_CAPSENSE_CSD_SW_HS_N_SEL_SW_HCRH_STATIC_CLOSE;
    ptrCsdHwBase->SW_CMP_N_SEL = CY_CAPSENSE_CSD_SW_CMP_N_SEL_SW_SCRH_STATIC_CLOSE;
    ptrCsdHwBase->SW_HS_P_SEL = 0u;
    ptrCsdHwBase->SW_AMUXBUF_SEL = context->ptrBistContext->regSwAmuxbufSel;
    ptrCsdHwBase->SW_BYP_SEL = context->ptrBistContext->regSwBypSel;
    #if (CY_CAPSENSE_PSOC6_FOURTH_GEN)
        ptrCsdHwBase->IO_SEL = context->ptrBistContext->regIoSel;
    #endif
    ptrCsdHwBase->SW_DSI_SEL = context->ptrBistContext->regSwDsiSel;
}
#endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN) ||\
           (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN)) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN)
#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_BistMeasureCapacitanceSensorShieldEnable
****************************************************************************//**
*
* The internal function sets up the CSD HW block to perform electrode
* (sensor or shield) capacitance measuring with a configured shield.
*
* This function prepares HW of the CAPSENSE&trade; block to CSD sensing mode
* with BIST-defined parameters with inactive sensor connection (ISC) set
* to the shield.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_BistMeasureCapacitanceSensorShieldEnable(
                cy_stc_capsense_context_t * context)
{
    CSD_Type * ptrCsdHwBase = context->ptrCommonConfig->ptrCsdBase;

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
        Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCmod,
                (uint32_t)context->ptrCommonConfig->pinCmod, CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_HSIOM_SEL_AMUXA);
        ptrCsdHwBase->SW_CMP_P_SEL = context->ptrInternalContext->csdRegSwCmpPSel;

        #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) && \
             (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_CAP_EN))
            Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCsh, (uint32_t)context->ptrCommonConfig->pinCsh,
                    CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_HSIOM_SEL_AMUXB);
        #endif
    #else /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */
        Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCintA,
                (uint32_t)context->ptrCommonConfig->pinCintA, CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_HSIOM_SEL_AMUXA);
        Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCintB,
                (uint32_t)context->ptrCommonConfig->pinCintB, CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_HSIOM_SEL_AMUXA);
        ptrCsdHwBase->SW_CMP_P_SEL = CY_CAPSENSE_CSD_SW_CMP_P_SEL_SW_SFPT_STATIC_CLOSE |
                                     CY_CAPSENSE_CSD_SW_CMP_P_SEL_SW_SFPM_STATIC_CLOSE;
    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

    ptrCsdHwBase->CONFIG = context->ptrBistContext->regConfigShield;
    ptrCsdHwBase->REFGEN =
            CSD_REFGEN_REFGEN_EN_Msk |
            CSD_REFGEN_RES_EN_Msk    |
            ((uint32_t)context->ptrBistContext->eltdCapVrefGain << CSD_REFGEN_GAIN_Pos);
    #if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
        if (CY_CAPSENSE_LOW_VOLTAGE_LIMIT > context->ptrCommonConfig->vdda)
        {
            ptrCsdHwBase->REFGEN = CSD_REFGEN_REFGEN_EN_Msk | CSD_REFGEN_BYPASS_Msk;
        }
    #endif
    ptrCsdHwBase->INTR_MASK = CY_CAPSENSE_CSD_INTR_MASK_CLEAR_MSK;
    ptrCsdHwBase->AMBUF = context->ptrBistContext->regAmbufShield;
    ptrCsdHwBase->ADC_CTL = 0u;
    ptrCsdHwBase->SEQ_TIME = 0u;
    ptrCsdHwBase->IDACA = 0u;
    ptrCsdHwBase->IDACB = 0u;
    ptrCsdHwBase->SENSE_DUTY = CY_CAPSENSE_CSD_SENSE_DUTY_CFG;
    ptrCsdHwBase->INTR_SET = 0u;
    ptrCsdHwBase->SEQ_INIT_CNT = (uint32_t)context->ptrBistContext->fineInitTime;
    ptrCsdHwBase->SW_REFGEN_SEL = context->ptrBistContext->regSwRefgenSel;
    ptrCsdHwBase->SW_HS_N_SEL = CY_CAPSENSE_CSD_SW_HS_N_SEL_SW_HCRH_STATIC_CLOSE;
    ptrCsdHwBase->SW_CMP_N_SEL = CY_CAPSENSE_CSD_SW_CMP_N_SEL_SW_SCRH_STATIC_CLOSE;
    ptrCsdHwBase->SW_HS_P_SEL = context->ptrBistContext->regSwHsPSelScanShield;
    ptrCsdHwBase->SW_AMUXBUF_SEL = context->ptrBistContext->regSwAmuxbufSelShield;
    ptrCsdHwBase->SW_BYP_SEL = context->ptrBistContext->regSwBypSelShield;
    #if (CY_CAPSENSE_PSOC6_FOURTH_GEN)
        ptrCsdHwBase->IO_SEL = context->ptrBistContext->regIoSelShield;
    #endif
    ptrCsdHwBase->SW_DSI_SEL = context->ptrBistContext->regSwDsiSel;
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) */
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN) */


#if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN) ||\
     (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN))
/*******************************************************************************
* Function Name: Cy_CapSense_BistMeasureCapacitanceSensor
****************************************************************************//**
*
* This internal function measures a capacitance attached to AMUXBUS.
*
* The function measures Cp of a certain electrode (CSD sensor or shield or CSX
* Rx/Tx electrode) by using CSD mode and defined IDAC configuration,
* sense clock frequency and resolution.
* The range for sensor measuring is 1 to 360 pF.
* The function performs up to 4 CSD scans with fixed IDAC values
* to reach a defined target of raw counts in the range from 7% to 45%
* of the maximum raw count value. This range provides a possibility of
* classical raw counts formula usage for capacitance calculation.
* The function stores the Cp value
* in the corresponding element of the eltdCap[CY_CAPSENSE_ELTD_COUNT] array.
*
* \param cpPtr
* The pointer to the uint32_t to store measured value of the capacitance.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E - The measurement completes
*                              successfully, the result is valid.
* - CY_CAPSENSE_BIST_BAD_PARAM_E - The input parameter is invalid.
* - CY_CAPSENSE_BIST_LOW_LIMIT_E - The measured capacitance is below
*                                the minimum possible value.
*                                The measurement result is invalid.
*                                The sensor might be shorted to VDD or a sensor
*                                PCB track was broken (open sensor).
* - CY_CAPSENSE_BIST_HIGH_LIMIT_E - The measured capacitance is above the
*                                 maximum possible value.
*                                 The measurement result is invalid.
*                                 The sensor might be shorted to GND.
* - CY_CAPSENSE_BIST_ERROR_E - An unexpected fault occurred during
*                            the measurement, the measurement may need
*                            to be repeated.
* - CY_CAPSENSE_BIST_TIMEOUT_E - The scan reached the timeout. It can be caused
*                              by a measured capacitance short or CSD HW block
*                              failure or invalid configuration. You may need to
*                              repeat the measurement after the issue fix.
*
*******************************************************************************/
static cy_en_capsense_bist_status_t Cy_CapSense_BistMeasureCapacitanceSensor(
                uint32_t * cpPtr,
                cy_stc_capsense_context_t * context)
{
    const uint32_t idacGainIdxTable[] = {2u, 2u, 4u, 5u};
    const uint32_t idacCodeTable[]= {20u, 80u, 40u, 80u};
    cy_en_capsense_bist_status_t result;
    uint32_t rawMaxNum = (0x01uL << context->ptrBistContext->eltdCapResolution) - 1u;
    uint32_t rawMinLimit = (rawMaxNum * CY_CAPSENSE_BIST_ELTD_CAP_MIN_RAW_PROMILLE) / CY_CAPSENSE_BIST_PROMILLE_FACTOR;
    uint32_t rawMaxLimit = (rawMaxNum * CY_CAPSENSE_BIST_ELTD_CAP_MAX_RAW_PROMILLE) / CY_CAPSENSE_BIST_PROMILLE_FACTOR;
    uint32_t counter = 0u;
    uint32_t idacCode;
    uint32_t idacIdx;
    uint32_t rawCountTmp = rawMaxNum;
    uint64_t cp;
    uint32_t modClkDivider;
    uint32_t cpuFreqMHz;
    uint32_t watchdogPeriod;
    uint64_t isBusyWatchdogTimeUs;


    /* Perform up to 4 scans to measure Cp */
    do
    {
        /* Setup scan parameters: IDAC and Gain */
        idacCode = idacCodeTable[counter];
        idacIdx = idacGainIdxTable[counter];
        context->ptrCommonConfig->ptrCsdBase->IDACA =
                (context->ptrCommonConfig->ptrCsdBase->IDACA & ~CY_CAPSENSE_BIST_IDAC_BITS_TO_WRITE) |
                ((context->ptrCommonConfig->idacGainTable[idacIdx].gainReg | idacCode |
                CSD_IDACA_LEG1_MODE_Msk | CSD_IDACA_LEG2_MODE_Msk) & CY_CAPSENSE_BIST_IDAC_BITS_TO_WRITE);

        /* Perform scanning */
        result = Cy_CapSense_BistMeasureCapacitanceSensorRun(context);
        if (CY_CAPSENSE_BIST_TIMEOUT_E != result)
        {

            modClkDivider = context->ptrBistContext->eltdCapModClk;
            if(0u == modClkDivider)
            {
                modClkDivider = 1u;
            }

            isBusyWatchdogTimeUs  = (uint64_t)((uint64_t)0x01 << context->ptrBistContext->eltdCapResolution);
            isBusyWatchdogTimeUs *= (uint64_t)modClkDivider * CY_CAPSENSE_CONVERSION_MEGA;
            isBusyWatchdogTimeUs /= context->ptrCommonConfig->periClkHz;

            if(0u == isBusyWatchdogTimeUs)
            {
                isBusyWatchdogTimeUs = 1u;
            }

            isBusyWatchdogTimeUs *= CY_CAPSENSE_BIST_WATCHDOG_MARGIN_COEFF;

            cpuFreqMHz = context->ptrCommonConfig->cpuClkHz / CY_CAPSENSE_CONVERSION_MEGA;
            watchdogPeriod = Cy_CapSense_WatchdogCyclesNum((uint32_t)isBusyWatchdogTimeUs, cpuFreqMHz,
                                                           CY_CAPSENSE_BIST_CAP_MEAS_WDT_CYCLES_PER_LOOP);

            /* Wait for an end of the scan and get a raw count */
            if (0u != Cy_CapSense_BistWaitEndOfScan(watchdogPeriod, context))
            {
                rawCountTmp = context->ptrCommonConfig->ptrCsdBase->RESULT_VAL1 &
                                             CY_CAPSENSE_CSD_RESULT_VAL1_VALUE_MSK;
                /* Check for the measurement result status */
                if ((rawCountTmp < rawMinLimit) && (0u == counter))
                {
                    result = CY_CAPSENSE_BIST_LOW_LIMIT_E;
                }
                if ((rawCountTmp > rawMaxLimit) && (3u == counter))
                {
                    result = CY_CAPSENSE_BIST_HIGH_LIMIT_E;
                }
                if ((rawCountTmp >= rawMinLimit) && (rawCountTmp <= rawMaxLimit))
                {
                    result = CY_CAPSENSE_BIST_SUCCESS_E;
                }
            }
            else
            {
                result = CY_CAPSENSE_BIST_TIMEOUT_E;
            }
        }
        if (CY_CAPSENSE_BIST_TIMEOUT_E == result)
        {
            break;
        }
        counter++;
    }
    while ((CY_CAPSENSE_BIST_SUCCESS_E != result) && (CY_CAPSENSE_BIST_LOW_LIMIT_E != result) &&
           (CY_CAPSENSE_BIST_HIGH_LIMIT_E != result) && (counter < CY_CAPSENSE_BIST_ELTD_CAP_CYCLES_NUM));
    /* Clear all interrupt pending requests */
    context->ptrCommonConfig->ptrCsdBase->INTR = CY_CAPSENSE_CSD_INTR_ALL_MSK;
    (void)context->ptrCommonConfig->ptrCsdBase->INTR;

    if ((CY_CAPSENSE_BIST_TIMEOUT_E != result))
    {
        /* Capacitance calculation and storage to the data structure */
        cp = ((uint64_t)context->ptrCommonConfig->idacGainTable[idacIdx].gainValue) * (uint64_t)idacCode;
        cp *= (uint64_t)rawCountTmp;
        cp *= CY_CAPSENSE_CONVERSION_MEGA;
        cp /= (uint64_t)rawMaxNum;
        cp /= (uint64_t)context->ptrBistContext->eltdCapSnsClkFreqHz;
        cp /= (uint64_t)context->ptrBistContext->eltdCapVrefMv;
        if (((uint64_t)CY_CAPSENSE_BIST_CP_MAX_VALUE) < cp)
        {
            cp = (uint64_t)CY_CAPSENSE_BIST_CP_MAX_VALUE;
        }
        *cpPtr = (uint32_t)cp;
    }

    return (result);
}


/*******************************************************************************
* Function Name: Cy_CapSense_BistMeasureCapacitanceSensorRun
****************************************************************************//**
*
* This internal function performs coarse initialization for Cmod and Csh
* (or CintA and CintB for only CSX configurations) and triggers a scan
* for the sensor or shield electrode capacitance measurement.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the starting execution:
* - CY_CAPSENSE_BIST_HW_BUSY_E - The CSD HW block is successfully started
*                                and is busy with scanning.
* - CY_CAPSENSE_BIST_TIMEOUT_E - The pre-charge of the integration capacitor
*                                reached a timeout.
*
*******************************************************************************/
static cy_en_capsense_bist_status_t Cy_CapSense_BistMeasureCapacitanceSensorRun(
                cy_stc_capsense_context_t * context)
{
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_SUCCESS_E;
    CSD_Type * ptrCsdHwBase = context->ptrCommonConfig->ptrCsdBase;
    uint32_t watchdogSize;
    uint32_t watchdogCounter;

    /* Approximate duration of Wait For Init loop */
    const uint32_t intrInitLoopDuration = 5uL;
    const uint32_t initWatchdogTimeUs = CY_CAPSENSE_BIST_PRECHARGE_WATCHDOG_TIME_US;

    watchdogSize = Cy_CapSense_WatchdogCyclesNum(initWatchdogTimeUs,
            context->ptrCommonConfig->cpuClkHz / CY_CAPSENSE_CONVERSION_MEGA,
            intrInitLoopDuration);

    Cy_CapSense_DischargeExtCapacitors(context);

    /* External capacitor pre-charging */
    ptrCsdHwBase->CSDCMP = 0u;
    ptrCsdHwBase->HSCMP = CY_CAPSENSE_CSD_HSCMP_HSCMP_EN_MSK;
    ptrCsdHwBase->SW_RES = context->ptrBistContext->regSwResInit;
    ptrCsdHwBase->SW_FW_MOD_SEL = 0u;
    ptrCsdHwBase->SW_FW_TANK_SEL = 0u;

    #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) && \
         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_CAP_EN))
        /* Clear previous interrupts */
        ptrCsdHwBase->INTR = CY_CAPSENSE_CSD_INTR_ALL_MSK;
        (void)ptrCsdHwBase->INTR;

        ptrCsdHwBase->SW_HS_P_SEL = context->ptrBistContext->regSwHsPSelCtankInit;
        ptrCsdHwBase->SW_SHIELD_SEL = CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBV_HSCMP;

        /* Start SEQUENCER for coarse initialization for Ctank */
        ptrCsdHwBase->SEQ_START = CY_CAPSENSE_CSD_SEQ_START_SEQ_MODE_MSK |
                                  CY_CAPSENSE_CSD_SEQ_START_START_MSK    |
                                  CY_CAPSENSE_BIST_FSM_AZ0_SKIP          |
                                  CY_CAPSENSE_BIST_FSM_AZ1_SKIP;
    #endif

    /* Init Watchdog Counter to prevent a hang */
    watchdogCounter = Cy_CapSense_WaitForSeqIdle(watchdogSize, context);
    if (0u == watchdogCounter)
    {
        /* Set the sequencer to the idle state if the coarse initialization fails */
        ptrCsdHwBase->SEQ_START = CY_CAPSENSE_CSD_SEQ_START_ABORT_MSK;
        result = CY_CAPSENSE_BIST_TIMEOUT_E;
    }

    if (CY_CAPSENSE_BIST_SUCCESS_E == result)
    {
        /* Clear previous interrupts */
        context->ptrCommonConfig->ptrCsdBase->INTR = CY_CAPSENSE_CSD_INTR_ALL_MSK;
        (void)ptrCsdHwBase->INTR;

        ptrCsdHwBase->SW_HS_P_SEL = context->ptrBistContext->regSwHsPSelCmodInit;
        ptrCsdHwBase->SW_SHIELD_SEL = CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCAV_HSCMP;

        /* Start SEQUENCER for coarse initialization for Cmod */
        ptrCsdHwBase->SEQ_START = CY_CAPSENSE_CSD_SEQ_START_SEQ_MODE_MSK |
                                  CY_CAPSENSE_CSD_SEQ_START_START_MSK    |
                                  CY_CAPSENSE_BIST_FSM_AZ0_SKIP          |
                                  CY_CAPSENSE_BIST_FSM_AZ1_SKIP;
        /* Init Watchdog Counter to prevent a hang */
        watchdogCounter = Cy_CapSense_WaitForSeqIdle(watchdogSize, context);

        if (0u == watchdogCounter)
        {
            /* Set the sequencer to the idle state if the coarse initialization fails */
            ptrCsdHwBase->SEQ_START = CY_CAPSENSE_CSD_SEQ_START_ABORT_MSK;
            result = CY_CAPSENSE_BIST_TIMEOUT_E;
        }
    }

    /* Scanning */
    if (CY_CAPSENSE_BIST_SUCCESS_E == result)
    {
        /* Clear previous interrupts */
        ptrCsdHwBase->INTR = CY_CAPSENSE_CSD_INTR_ALL_MSK;
        (void)ptrCsdHwBase->INTR;

        ptrCsdHwBase->CSDCMP = CY_CAPSENSE_CSD_CSDCMP_CSDCMP_EN_MSK;
        ptrCsdHwBase->SW_RES = context->ptrBistContext->regSwResScan;

        if (CY_CAPSENSE_BIST_HW_ELTD_CAP_SH_E != context->ptrBistContext->hwConfig)
        {
            ptrCsdHwBase->SW_HS_P_SEL = context->ptrBistContext->regSwHsPSelScan;
            ptrCsdHwBase->HSCMP = context->ptrBistContext->regHscmpScan;
            ptrCsdHwBase->SW_SHIELD_SEL = context->ptrBistContext->regSwShieldSelScan;
        }
        else
        {
            ptrCsdHwBase->SW_HS_P_SEL = context->ptrBistContext->regSwHsPSelScanShield;
            ptrCsdHwBase->HSCMP = context->ptrBistContext->regHscmpScanShield;
            ptrCsdHwBase->SW_SHIELD_SEL = context->ptrBistContext->regSwShieldSelScanShield;
        }

        ptrCsdHwBase->SEQ_START = CY_CAPSENSE_CSD_SEQ_START_AZ0_SKIP_MSK |
                                  CY_CAPSENSE_CSD_SEQ_START_AZ1_SKIP_MSK |
                                  CY_CAPSENSE_CSD_SEQ_START_START_MSK;
        result = CY_CAPSENSE_BIST_HW_BUSY_E;
    }

    return (result);
}
#endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN) ||\
           (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN)) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_BistMeasureCapacitanceSensorAll
****************************************************************************//**
*
* This internal function measures all the sensors Cp capacitance.
*
* This function measures Cp of all the sensors by using the
* CapSense_GetSensorCapacitance function.
* The function stores the Cp values in the corresponding BIST data
* structure registers.
* The function is called by the Cy_CapSense_RunSelfTest() function.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the measuring process:
* - CY_CAPSENSE_BIST_SUCCESS_E if all the measurements passed successfully.
* - CY_CAPSENSE_BIST_FAIL_E if any measurement was failed.
*
*******************************************************************************/
static cy_en_capsense_bist_status_t Cy_CapSense_BistMeasureCapacitanceSensorAll(
                cy_stc_capsense_context_t * context)
{
    uint32_t widgetId;
    uint32_t sensorElement;
    uint32_t numWdgtElectrodes;
    uint32_t snsCap;
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_SUCCESS_E;

    /* Loop through all the widgets */
    for (widgetId = 0u; widgetId < context->ptrCommonConfig->numWd; widgetId++)
    {
        /* Get a total number of the widget elements: for CSX, it is numRows + numCols, for CSD, it is totalNumSns */
        if (CY_CAPSENSE_CSX_GROUP == context->ptrWdConfig[widgetId].senseMethod)
        {
            numWdgtElectrodes = context->ptrWdConfig[widgetId].numRows +
                                (uint32_t)context->ptrWdConfig[widgetId].numCols;
        }
        else
        {
            numWdgtElectrodes = context->ptrWdConfig[widgetId].numSns;
        }
        /* Loop through all the sensor electrodes */
        for (sensorElement = 0u; sensorElement < numWdgtElectrodes; sensorElement++)
        {
            if (CY_CAPSENSE_BIST_SUCCESS_E != Cy_CapSense_MeasureCapacitanceSensor(widgetId, sensorElement, &snsCap, context))
            {
                if (CY_CAPSENSE_BIST_SUCCESS_E == result)
                {
                    result = CY_CAPSENSE_BIST_FAIL_E;
                }
            }
        }
    }

    return (result);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_EXTERNAL_CAP_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_MeasureCapacitanceCap_V2
****************************************************************************//**
*
* Measures the capacitance in picofarads of the specified CAPSENSE&trade; integration
* (external) capacitor.
*
* The function measures the capacitance of the specified external capacitor
* such as Cmod and returns the result through ptrValue, alternatively
* the measurement result is stored in the corresponding field of the
* \ref cy_stc_capsense_bist_context_t structure (either .cModCap, .cIntACap,
* .cIntBCap, or .cShieldCap).
*
* The maximum measurement capacitance is 25nF. The measurement accuracy is
* up to 15%. The measurement resolution is 10 bit which corresponds to the
* maximum capacitance specified by the maxCapacitance parameter. The bigger
* specified maximum capacitance is, the bigger capacitance value is for
* one measured count.
* It is recommended to specify the maximum capacitance twice bigger as the
* nominal capacitor capacitance. For example, if the nominal Cmod value
* is 2.2nF, the maxCapacitance parameter is set to 4nF-5nF.
*
* The function configures all CAPSENSE&trade; pins to  Strong-drive-low mode that
* allows detecting a short of the measured capacitor to other pins.
*
* To measure all the available capacitors, the Cy_CapSense_RunSelfTest()
* function can be used with the CY_CAPSENSE_BIST_SNS_INTEGRITY_MASK mask. The measured
* results are stored in the corresponding field of the
* \ref cy_stc_capsense_bist_context_t structure.
*
* Measurement can be done only if the CAPSENSE&trade; Middleware is in the IDLE
* state. This function must not be called while the CAPSENSE&trade; Middleware is busy.
* The function is blocking, i.e. waits for the measurement to be completed
* prior to returning to the caller.
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
*
* \param integrationCapId
* Indexes of external capacitors to measure their capacitance.
* There are macros for each of them, namely:
* * CY_CAPSENSE_BIST_CMOD_ID for the CSD method Cmod capacitor
* * CY_CAPSENSE_BIST_CINTA_ID for the CSX method CintA capacitor
* * CY_CAPSENSE_BIST_CINTB_ID for the CSX method CintB capacitor
* * CY_CAPSENSE_BIST_CSH_ID for the CSD method Csh capacitor
*
* \param ptrValue
* The pointer to the result of the measurement. The result is calculated as
* a specified capacitor capacitance value in picofarads. The user
* declares a variable of the uint32_t type and passes the pointer to this
* variable as the function parameter. If the ptrValue parameter is NULL then
* the capacitance value is not returned through the parameter but stored to the
* corresponding field of the \ref cy_stc_capsense_bist_context_t structure.
*
* \param maxCapacitance
* An expected by the user maximum value of the measured capacitance in
* nanofarads in the range from 1 to 25 nF.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E          - The measurement completes
*                                         successfully, the result is valid.
* - CY_CAPSENSE_BIST_BAD_PARAM_E        - The input parameter is invalid.
*                                         The measurement was not executed.
* - CY_CAPSENSE_BIST_HW_BUSY_E          - The CSD HW block is busy with
*                                         a previous operation. The measurement
*                                         was not executed.
* - CY_CAPSENSE_BIST_LOW_LIMIT_E        - The measurement was performed
*                                         but the scanning result is
*                                         below the minimum possible value.
*                                         The measurement result could be invalid.
*                                         The capacitor might be shorted to
*                                         VDD or a PCB track
*                                         is broken (open capacitor).
* - CY_CAPSENSE_BIST_HIGH_LIMIT_E       - The measurement was performed but
*                                         the scanning result is above the
*                                         maximum possible value.
*                                         The measurement result could be invalid.
*                                         The capacitor might be shorted to GND.
* - CY_CAPSENSE_BIST_ERROR_E            - An unexpected fault occurred during
*                                         the measurement.
*
*******************************************************************************/
cy_en_capsense_bist_status_t Cy_CapSense_MeasureCapacitanceCap_V2(
                cy_en_capsense_bist_external_cap_id_t integrationCapId,
                uint32_t * ptrValue,
                uint32_t maxCapacitance,
                cy_stc_capsense_context_t * context)
{
    uint32_t extCapValue = 0u;
    GPIO_PRT_Type * ptrCapPort = NULL;
    uint32_t capacitorPin = 0u;
    uint16_t * ptrResult = NULL;
    uint32_t idacCode = 0u;
    uint32_t idacIdx = 0u;
    uint32_t idacGain = 0u;
    uint64_t tempIDAC;
    cy_en_capsense_bist_status_t bistStatus = CY_CAPSENSE_BIST_SUCCESS_E;

    if ((NULL == context) || (CY_CAPSENSE_BIST_CAP_MEAS_MAX_CAP < maxCapacitance) || (0u == maxCapacitance))
    {
        bistStatus = CY_CAPSENSE_BIST_BAD_PARAM_E;
    }
    if (CY_CAPSENSE_SUCCESS_E != Cy_CapSense_SwitchSensingMode(CY_CAPSENSE_BIST_GROUP, context))
    {
        bistStatus = CY_CAPSENSE_BIST_HW_BUSY_E;
    }

    if (CY_CAPSENSE_BIST_SUCCESS_E == bistStatus)
    {
        switch (integrationCapId)
        {
            case CY_CAPSENSE_BIST_CMOD_ID_E:
                if (CY_CAPSENSE_ENABLE != context->ptrCommonConfig->csdEn)
                {
                    bistStatus = CY_CAPSENSE_BIST_BAD_PARAM_E;
                }
                ptrCapPort = context->ptrCommonConfig->portCmod;
                capacitorPin = (uint32_t)context->ptrCommonConfig->pinCmod;
                ptrResult = &context->ptrBistContext->cModCap;
                break;
            case CY_CAPSENSE_BIST_CINTA_ID_E:
                if (CY_CAPSENSE_ENABLE != context->ptrCommonConfig->csxEn)
                {
                    bistStatus = CY_CAPSENSE_BIST_BAD_PARAM_E;
                }
                ptrCapPort = context->ptrCommonConfig->portCintA;
                capacitorPin = (uint32_t)context->ptrCommonConfig->pinCintA;
                ptrResult = &context->ptrBistContext->cIntACap;
                break;
            case CY_CAPSENSE_BIST_CINTB_ID_E:
                if (CY_CAPSENSE_ENABLE != context->ptrCommonConfig->csxEn)
                {
                    bistStatus = CY_CAPSENSE_BIST_BAD_PARAM_E;
                }
                ptrCapPort = context->ptrCommonConfig->portCintB;
                capacitorPin = (uint32_t)context->ptrCommonConfig->pinCintB;
                ptrResult = &context->ptrBistContext->cIntBCap;
                break;
            #if((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) && \
                (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_CAP_EN))
            case CY_CAPSENSE_BIST_CSH_ID_E:
                ptrCapPort = context->ptrCommonConfig->portCsh;
                capacitorPin = (uint32_t)context->ptrCommonConfig->pinCsh;
                ptrResult = &context->ptrBistContext->cShieldCap;
                break;
            #endif
            default:
                bistStatus = CY_CAPSENSE_BIST_BAD_PARAM_E;
                break;
        }
    }

    if (CY_CAPSENSE_BIST_SUCCESS_E == bistStatus)
    {
        /* Set the BUSY status */
        context->ptrCommonContext->status = CY_CAPSENSE_BUSY;
        Cy_CapSense_BistSwitchHwConfig(CY_CAPSENSE_BIST_HW_EXTERNAL_CAP_E, context);

        /* Calculate the needed IDAC value */
        tempIDAC = ((((((uint64_t)CY_CAPSENSE_BIST_CAP_MEAS_ACCURACY_FACTOR *
                        (uint64_t)context->ptrBistContext->extCapVrefMv) *
                        (uint64_t)context->ptrCommonConfig->periClkHz) * (uint64_t)maxCapacitance) /
                        (uint64_t)context->ptrBistContext->extCapModClk) /
                        (uint64_t)context->ptrBistContext->extCapSnsClk) /
                        (uint64_t)CY_CAPSENSE_BIST_PROMILLE_FACTOR;
        /* IDAC Gain - LSB */
        tempIDAC = (tempIDAC + (CY_CAPSENSE_BIST_IDAC_MAX - 1u)) / CY_CAPSENSE_BIST_IDAC_MAX;
        /* Search for corresponding IDAC gain */
        while(idacIdx < (CY_CAPSENSE_IDAC_GAIN_NUMBER - 1u))
        {
            if (context->ptrCommonConfig->idacGainTable[idacIdx].gainValue > (uint32_t)tempIDAC)
            {
                break;
            }
            idacIdx++;
        }
        idacGain = context->ptrCommonConfig->idacGainTable[idacIdx].gainValue;
        /* Calculate the  IDAC code */
        idacCode = (uint32_t)((((tempIDAC * CY_CAPSENSE_BIST_IDAC_MAX) + idacGain) - 1u) / idacGain);
        if (CY_CAPSENSE_BIST_IDAC_MAX < idacCode)
        {
            idacCode = CY_CAPSENSE_BIST_IDAC_MAX;
        }
        if (0u == idacCode)
        {
            idacCode = 1u;
        }

        context->ptrBistContext->extCapIdacPa = idacCode * idacGain;
        context->ptrCommonConfig->ptrCsdBase->IDACA = CY_CAPSENSE_BIST_CAP_IDAC_MODE_DEFAULT |
                                                      idacCode |
                                                      context->ptrCommonConfig->idacGainTable[idacIdx].gainReg;

        /* Connect the capacitor to the analog bus for further measurement */
        Cy_CapSense_SsConfigPinRegisters(ptrCapPort, capacitorPin, CY_CAPSENSE_CSD_SCAN_PIN_DM, CY_CAPSENSE_HSIOM_SEL_CSD_SENSE);
        /* Perform the measurement */
        bistStatus = Cy_CapSense_BistMeasureCapacitanceCapRun(&extCapValue, context);
        /* Disconnect and discharge the capacitor */
        Cy_CapSense_SsConfigPinRegisters(ptrCapPort, capacitorPin, CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF, CY_CAPSENSE_HSIOM_SEL_GPIO);
        Cy_GPIO_Clr(ptrCapPort, capacitorPin);

        if (CY_CAPSENSE_BIST_TIMEOUT_E != bistStatus)
        {
            *ptrResult = (uint16_t)extCapValue;
            if(NULL != ptrValue)
            {
                *ptrValue = extCapValue;
            }
        }
        /* Clear the BUSY flag */
        context->ptrCommonContext->status = CY_CAPSENSE_NOT_BUSY;
    }
    return (bistStatus);
}


/*******************************************************************************
* Function Name: Cy_CapSense_BistMeasureCapacitanceCapInit
****************************************************************************//**
*
* This internal function calculates the parameters for the external capacitor
* capacitance measurement and register values before speeding up
* the execution.
*
* It is called by Cy_CapSense_BistDsInitialize() once at CAPSENSE&trade; MW start.
*
* The following parameters of cy_stc_capsense_bist_context_t are used as
* an input for the calculation:
* * .extCapModClk
* * .extCapVrefMv
* * .extCapModClk
*
* The following parameters of cy_stc_capsense_bist_context_t are updated
* by the calculation:
* * .extCapModClk
* * .extCapVrefMv
* * .extCapVrefGain
* * .extCapWDT
*
* Restarting CAPSENSE&trade; MW or calling of the Cy_CapSense_BistDsInitialize()
* function overwrites the output parameters.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_BistMeasureCapacitanceCapInit(
                cy_stc_capsense_context_t * context)
{
    uint32_t temp;
    cy_stc_capsense_bist_context_t * ptrBistCxt = context->ptrBistContext;

    if (0u == ptrBistCxt->extCapModClk)
    {
        ptrBistCxt->extCapModClk = 1u;
    }
    while (CY_CAPSENSE_BIST_CAP_MEAS_MAX_MODCLK < (context->ptrCommonConfig->periClkHz / ptrBistCxt->extCapModClk))
    {
        ptrBistCxt->extCapModClk <<= 1u;
    }

    if(ptrBistCxt->extCapVrefMv == 0u)
    {
        /* Get the recommended reference voltage */
        temp = CY_CAPSENSE_BIST_CAP_MEAS_VREF_MV_DEFAULT;
    }
    else
    {
        /* Use the user-defined reference voltage */
        temp = (uint32_t)ptrBistCxt->extCapVrefMv;
    }
    ptrBistCxt->extCapVrefGain = (uint8_t)Cy_CapSense_GetVrefHighGain(temp, context);
    ptrBistCxt->extCapVrefMv = (uint16_t)Cy_CapSense_GetVrefHighMv((uint32_t)ptrBistCxt->extCapVrefGain, context);

    ptrBistCxt->extCapWDT = CY_CAPSENSE_BIST_CAP_MEAS_WDT_TIMEOUT;
    ptrBistCxt->capacitorSettlingTime = CY_CAPSENSE_BIST_CAP_SETTLING_TIME_DEFAULT;
}


/*******************************************************************************
* Function Name: Cy_CapSense_BistMeasureCapacitanceCapEnable
****************************************************************************//**
*
* This internal function configures the CSD HW block operation and
* the HW block-level analog routing to the external capacitor capacitance
* measurement test.
*
* Sets up the CSD HW block to perform the external capacitor capacitance
* measuring.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_BistMeasureCapacitanceCapEnable(
                cy_stc_capsense_context_t * context)
{
    CSD_Type * ptrCsdHwBase = context->ptrCommonConfig->ptrCsdBase;

    /* Disable all interrupts from the HW block */
    ptrCsdHwBase->INTR_MASK = CY_CAPSENSE_CSD_INTR_MASK_CLEAR_MSK;
    (void)ptrCsdHwBase->INTR_MASK;
    /* Clear all pending interrupt requests */
    ptrCsdHwBase->INTR = CY_CAPSENSE_CSD_INTR_ALL_MSK;
    (void)ptrCsdHwBase->INTR;

    /* Set the divider value for mod clock (1u lower than the desired divider) */
    Cy_CapSense_SetClkDivider(((uint32_t)context->ptrBistContext->extCapModClk - 1u), context);

    Cy_CapSense_BistSwitchAllSnsPinState(CY_CAPSENSE_BIST_IO_STRONG_E, context);
    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
        Cy_CapSense_BistSwitchAllShieldPinState(CY_CAPSENSE_BIST_IO_STRONG_E, context);
    #endif
    Cy_CapSense_BistSwitchAllExternalCapPinState(CY_CAPSENSE_BIST_IO_STRONG_E, context);
    /* Wait for the maximum possible external capacitor charging time */
    Cy_SysLib_DelayUs(context->ptrBistContext->capacitorSettlingTime);

    /* Initialize the CSD registers to perform external capacitor capacitance measurement */
    ptrCsdHwBase->CONFIG = CY_CAPSENSE_BIST_CAP_CONFIG_DEFAULT;
    ptrCsdHwBase->SW_REFGEN_SEL = CY_CAPSENSE_BIST_CAP_SW_REFGEN_SEL_SRSS_DEFAULT;
    #if (CY_CAPSENSE_PSOC6_FOURTH_GEN)
        if (CY_CAPSENSE_IREF_PASS == context->ptrCommonConfig->ssIrefSource)
        {
            ptrCsdHwBase->CONFIG = CY_CAPSENSE_BIST_CAP_CONFIG_IREF_DEFAULT;
        }
        if (CY_CAPSENSE_VREF_PASS == context->ptrCommonConfig->ssVrefSource)
        {
            ptrCsdHwBase->SW_REFGEN_SEL = CY_CAPSENSE_BIST_CAP_SW_REFGEN_SEL_PASS_DEFAULT;
        }
        ptrCsdHwBase->IO_SEL = CY_CAPSENSE_BIST_CAP_IO_SEL_DEFAULT;
    #endif
    ptrCsdHwBase->REFGEN = CY_CAPSENSE_BIST_CAP_REFGEN_DEFAULT |
                          ((uint32_t)context->ptrBistContext->extCapVrefGain << CSD_REFGEN_GAIN_Pos);
    #if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
        if (CY_CAPSENSE_LOW_VOLTAGE_LIMIT > context->ptrCommonConfig->vdda)
        {
            ptrCsdHwBase->REFGEN = CY_CAPSENSE_BIST_CAP_REFGEN_LOW_VOLTAGE_DEFAULT;
        }
    #endif
    ptrCsdHwBase->CSDCMP = CY_CAPSENSE_BIST_CAP_CSDCMP_DEFAULT;
    ptrCsdHwBase->SENSE_DUTY = CY_CAPSENSE_BIST_CAP_SENSE_DUTY_DEFAULT;
    ptrCsdHwBase->SENSE_PERIOD = (uint32_t)context->ptrBistContext->extCapSnsClk - 1u;
    ptrCsdHwBase->SEQ_NORM_CNT = 1u;
    ptrCsdHwBase->SEQ_TIME = 0uL;
    ptrCsdHwBase->SEQ_INIT_CNT = 0uL;
    ptrCsdHwBase->ADC_CTL = 0uL;
    ptrCsdHwBase->IDACA = 0u;
    ptrCsdHwBase->IDACB = 0u;
    ptrCsdHwBase->INTR_SET = 0uL;
    ptrCsdHwBase->HSCMP = 0uL;
    ptrCsdHwBase->AMBUF = 0uL;
    ptrCsdHwBase->SW_RES = 0uL;
    ptrCsdHwBase->SW_HS_P_SEL = 0uL;
    ptrCsdHwBase->SW_HS_N_SEL = 0uL;
    ptrCsdHwBase->SW_SHIELD_SEL = 0u;
    ptrCsdHwBase->SW_AMUXBUF_SEL = 0uL;
    ptrCsdHwBase->SW_FW_MOD_SEL = 0uL;
    ptrCsdHwBase->SW_FW_TANK_SEL = 0uL;
    ptrCsdHwBase->SW_DSI_SEL = 0uL;
    ptrCsdHwBase->SW_BYP_SEL = CY_CAPSENSE_BIST_CAP_SW_BYP_SEL_DEFAULT;
    ptrCsdHwBase->SW_CMP_N_SEL = CY_CAPSENSE_BIST_CAP_SW_CMP_N_SEL_DEFAULT;
    ptrCsdHwBase->SW_CMP_P_SEL = CY_CAPSENSE_BIST_CAP_SW_CMP_P_SEL_DEFAULT;
}


/*******************************************************************************
* Function Name: Cy_CapSense_BistMeasureCapacitanceCapRun
****************************************************************************//**
*
* This internal function starts the specific scan for the external capacitor
* capacitance measurement.
*
* \param ptrExtCapValue
* The pointer to the result of the measurement in picofarads.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E - The measurement completes
*                              successfully, the result is valid.
* - CY_CAPSENSE_BIST_LOW_LIMIT_E - A measured capacitance is below
*                                the minimum possible value.
*                                The measurement result is invalid.
*                                The capacitor might be shorted to VDD or a
*                                PCB track is broken (open capacitor).
* - CY_CAPSENSE_BIST_HIGH_LIMIT_E - The measured capacitance is above the
*                                 maximum possible value.
*                                 The measurement result is invalid.
*                                 The capacitor might be shorted to GND.
* - CY_CAPSENSE_BIST_TIMEOUT_E - The measuring scan is not finished properly
*                                and reached the timeout.
*
*******************************************************************************/
static cy_en_capsense_bist_status_t Cy_CapSense_BistMeasureCapacitanceCapRun(
                uint32_t * ptrExtCapValue,
                cy_stc_capsense_context_t * context)
{
    uint32_t tempRawcount;
    uint64_t tempCapacitance;
    cy_en_capsense_bist_status_t bistStatus = CY_CAPSENSE_BIST_TIMEOUT_E;
    CSD_Type * ptrCsdHwBase = context->ptrCommonConfig->ptrCsdBase;
    uint32_t watchdogPeriod;

    watchdogPeriod = Cy_CapSense_WatchdogCyclesNum(
            (uint32_t)context->ptrBistContext->extCapWDT,
            (context->ptrCommonConfig->cpuClkHz / CY_CAPSENSE_CONVERSION_MEGA),
            CY_CAPSENSE_BIST_CAP_MEAS_WDT_CYCLES_PER_LOOP);

    /* Clear all pending interrupt requests */
    ptrCsdHwBase->INTR = CY_CAPSENSE_CSD_INTR_ALL_MSK;
    (void)ptrCsdHwBase->INTR;

    /* Start SEQUENCER for fine initialization and then for conversion */
    ptrCsdHwBase->SEQ_START = CY_CAPSENSE_BIST_CAP_SEQ_START_DEFAULT;

    /* Wait for the end of the scan and get the raw counts */
    if (0u != Cy_CapSense_BistWaitEndOfScan(watchdogPeriod, context))
    {
        tempRawcount = ptrCsdHwBase->RESULT_VAL1 &
                       CY_CAPSENSE_CSD_RESULT_VAL1_VALUE_MSK;

        /* Check for the measurement result status */
        if (CY_CAPSENSE_BIST_CAP_MEAS_MIN_RAWCOUNT > tempRawcount)
        {
            bistStatus = CY_CAPSENSE_BIST_LOW_LIMIT_E;
        }
        else if (((uint32_t)context->ptrBistContext->extCapSnsClk - CY_CAPSENSE_BIST_CAP_MEAS_DUTY_WIDTH) < tempRawcount)
        {
            bistStatus = CY_CAPSENSE_BIST_HIGH_LIMIT_E;
        }
        else
        {
            bistStatus = CY_CAPSENSE_BIST_SUCCESS_E;
        }

        /* Calculate the capacitance value in pF */
        tempCapacitance = (((((uint64_t)context->ptrBistContext->extCapIdacPa *
                              (uint64_t)context->ptrBistContext->extCapModClk) * (uint64_t)tempRawcount) *
                              (uint64_t)CY_CAPSENSE_BIST_PROMILLE_FACTOR) /
                              (uint64_t)context->ptrCommonConfig->periClkHz) /
                              (uint64_t)context->ptrBistContext->extCapVrefMv;
        *ptrExtCapValue = (uint32_t)tempCapacitance;
    }

    return (bistStatus);
}


/*******************************************************************************
* Function Name: Cy_CapSense_BistMeasureCapacitanceCapAll
****************************************************************************//**
*
* This internal function measures capacitance of all external capacitors.
*
* The function measures capacitances of all external capacitors Cmod,
* Csh, CintA, CintB (if available in a design).
* The function stores cap values in the corresponding registers.
* The function is called by the Cy_CapSense_RunSelfTest() function.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E - The measurement completes
*                              successfully, the result is valid.
* - CY_CAPSENSE_BIST_BAD_PARAM_E - The input parameter is invalid.
* - CY_CAPSENSE_BIST_HW_BUSY_E - The CSD HW block is busy with a previous
*                              operation.
* - CY_CAPSENSE_BIST_LOW_LIMIT_E - A measured capacitance is below
*                                the minimum possible value.
*                                The measurement result is invalid.
*                                The capacitor might be shorted to VDD or a
*                                PCB track is broken (open capacitor).
* - CY_CAPSENSE_BIST_HIGH_LIMIT_E - The measured capacitance is above the
*                                 maximum possible value.
*                                 The measurement result is invalid.
*                                 The capacitor might be shorted to GND.
* - CY_CAPSENSE_BIST_ERROR_E - An unexpected fault occurred during
*                            the measurement, you may need to repeat the measurement.
*
*******************************************************************************/
static cy_en_capsense_bist_status_t Cy_CapSense_BistMeasureCapacitanceCapAll(
                cy_stc_capsense_context_t * context)
{
    uint32_t capCapacitance = 0u;
    cy_en_capsense_bist_status_t tempStatus;
    cy_en_capsense_bist_status_t bistStatus = CY_CAPSENSE_BIST_SUCCESS_E;

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
        tempStatus = Cy_CapSense_MeasureCapacitanceCap_V2(CY_CAPSENSE_BIST_CMOD_ID_E, &capCapacitance,
                CY_CAPSENSE_BIST_CAP_MEAS_CMOD_MAX_VALUE, context);
        if (CY_CAPSENSE_BIST_SUCCESS_E != tempStatus)
        {
            bistStatus = tempStatus;
        }
        #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) && \
             (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_CAP_EN))
            tempStatus = Cy_CapSense_MeasureCapacitanceCap_V2(CY_CAPSENSE_BIST_CSH_ID_E, &capCapacitance,
                    CY_CAPSENSE_BIST_CAP_MEAS_CSH_MAX_VALUE, context);
            if (CY_CAPSENSE_BIST_SUCCESS_E != tempStatus)
            {
                bistStatus = tempStatus;
            }
        #endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) && \
                   (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_CAP_EN)) */
    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
        tempStatus = Cy_CapSense_MeasureCapacitanceCap_V2(CY_CAPSENSE_BIST_CINTA_ID_E, &capCapacitance,
                CY_CAPSENSE_BIST_CAP_MEAS_CINT_MAX_VALUE, context);
        if (CY_CAPSENSE_BIST_SUCCESS_E != tempStatus)
        {
            bistStatus = tempStatus;
        }
        tempStatus = Cy_CapSense_MeasureCapacitanceCap_V2(CY_CAPSENSE_BIST_CINTB_ID_E, &capCapacitance,
                CY_CAPSENSE_BIST_CAP_MEAS_CINT_MAX_VALUE, context);
        if (CY_CAPSENSE_BIST_SUCCESS_E != tempStatus)
        {
            bistStatus = tempStatus;
        }
    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

    return (bistStatus);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_EXTERNAL_CAP_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_VDDA_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_MeasureVdda_V2
****************************************************************************//**
*
* Measures a VDDA voltage, returns the measured voltage in
* millivolts through the ptrValue argument and stores it to the .vddaVoltage
* field of the \ref cy_stc_capsense_bist_context_t structure.
*
* This function measures the device analog supply voltage (VDDA) without need
* of explicitly connecting VDDA to any additional GPIO input.
* This capability can be used in various cases, for example to monitor
* the battery voltage.
*
* A measurement can be done only if the CAPSENSE&trade; middleware is in the IDLE
* state. This function must not be called while the CAPSENSE&trade; middleware is busy.
* The function is blocking, i.e. waits for the conversion to be completed
* prior to returning to the caller.
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
*
* \param ptrValue
* The pointer to the uint32_t to store measured VDDA voltage value.
* If the ptrValue parameter is NULL then VDDA voltage value is not returned
* through the parameter and is stored in the .vddaVoltage
* field of the \ref cy_stc_capsense_bist_context_t structure.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E          - The measurement executed
*                                         successfully.
* - CY_CAPSENSE_BIST_BAD_PARAM_E        - The input parameter is invalid.
*                                         The measurement was not executed.
* - CY_CAPSENSE_BIST_ERROR_E            - An unexpected fault occurred during
*                                         the measurement.
*
*******************************************************************************/
cy_en_capsense_bist_status_t Cy_CapSense_MeasureVdda_V2(
                uint32_t * ptrValue,
                cy_stc_capsense_context_t * context)
{
    cy_en_capsense_return_status_t csStatus;
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_BAD_PARAM_E;

    if (NULL != context)
    {
        csStatus = Cy_CapSense_SwitchSensingMode(CY_CAPSENSE_BIST_GROUP, context);

        if (CY_CAPSENSE_SUCCESS_E == csStatus)
        {
            Cy_CapSense_BistSwitchHwConfig(CY_CAPSENSE_BIST_HW_VDDA_E, context);
            result = Cy_CapSense_BistMeasureVddaRun(context);
            if ((NULL != ptrValue) && (CY_CAPSENSE_BIST_SUCCESS_E == result))
            {
                *ptrValue = (uint16_t)context->ptrBistContext->vddaVoltage;
            }
        }
        else
        {
            result = CY_CAPSENSE_BIST_ERROR_E;
        }
    }

    return (result);
}


/*******************************************************************************
* Function Name: Cy_CapSense_BistMeasureVddaInit
****************************************************************************//**
*
* This internal function calculates the parameters for VDDA measurement
* and register values before speeding up the execution.
*
* It is called by Cy_CapSense_BistDsInitialize() once at the CAPSENSE&trade; MW start.
*
* The following parameters of cy_stc_capsense_bist_context_t are used as
* an input for the calculation:
* * .vddaModClk
* * .vddaVrefMv
*
* The following parameters of cy_stc_capsense_bist_context_t are updated
* by the calculation:
* * .vddaModClk
* * .vddaVrefMv
* * .vddaVrefGain
* * .vddaIdacDefault
* * .vddaAzCycles
* * .vddaAcqCycles
*
* Restarting CAPSENSE&trade; MW or calling of the Cy_CapSense_BistDsInitialize()
* function overwrites the output parameters.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_BistMeasureVddaInit(cy_stc_capsense_context_t * context)
{
    uint32_t idacVal;
    uint32_t vddaValMv;
    uint32_t vrefValMv;
    uint32_t maxVoltageMv;
    uint32_t fsmFreqHz;

    vddaValMv = (uint32_t)context->ptrCommonConfig->vdda;
    vrefValMv = (uint32_t)context->ptrBistContext->vddaVrefMv;

    /* Check for the Vref limitations */
    if (vrefValMv > (vddaValMv - CY_CAPSENSE_BIST_VDDA_MIN_DIFF))
    {
        vrefValMv = (vddaValMv - CY_CAPSENSE_BIST_VDDA_MIN_DIFF);
    }
    if(vrefValMv < CY_CAPSENSE_BIST_VDDA_VREF_MIN_MV)
    {
        vrefValMv = CY_CAPSENSE_BIST_VDDA_VREF_MIN_MV;
    }

    /* Calculate the refgen gain for the desired reference voltage */
    context->ptrBistContext->vddaVrefGain = (uint8_t)Cy_CapSense_GetVrefHighGain(vrefValMv, context);
    /* Calculate the reference voltage */
    vrefValMv = Cy_CapSense_GetVrefHighMv((uint32_t)context->ptrBistContext->vddaVrefGain, context);

    /* Update the nominal Vref to real Vref considering available trimming for SRSS */
    #if (CY_CAPSENSE_PSOC6_FOURTH_GEN)
        if(CY_CAPSENSE_VREF_SRSS == context->ptrCommonConfig->ssVrefSource)
        {
            vrefValMv = Cy_CSD_GetVrefTrim(vrefValMv);
        }
    #endif

    maxVoltageMv = (((vddaValMv - vrefValMv) > vrefValMv) ? (vddaValMv - vrefValMv) : vrefValMv);

    if (context->ptrBistContext->vddaModClk == 0u)
    {
        context->ptrBistContext->vddaModClk = 1u;
    }
    if ((context->ptrCommonConfig->periClkHz / context->ptrBistContext->vddaModClk) > CY_CAPSENSE_BIST_VDDA_MAX_MODCLK)
    {
        context->ptrBistContext->vddaModClk++;
    }
    idacVal = (context->ptrCommonConfig->periClkHz / CY_CAPSENSE_BIST_VDDA_RES) / context->ptrBistContext->vddaModClk;
    idacVal = (((idacVal * maxVoltageMv) / CY_CAPSENSE_CONVERSION_MEGA) * CY_CAPSENSE_BIST_VDDA_CREF) /
                 CY_CAPSENSE_BIST_VDDA_IDAC_LSB;

    if (CY_CAPSENSE_BIST_IDAC_MAX < idacVal)
    {
        idacVal = CY_CAPSENSE_BIST_IDAC_MAX;
    }
    if (0u == idacVal)
    {
        idacVal = 1u;
    }

    context->ptrBistContext->vddaIdacDefault = (uint8_t)idacVal;
    context->ptrBistContext->vddaVrefMv = (uint16_t)vrefValMv;

    fsmFreqHz = (context->ptrCommonConfig->periClkHz / context->ptrBistContext->vddaModClk) /
                 CY_CAPSENSE_BIST_VDDA_SENSE_PERIOD_DEFAULT;
    context->ptrBistContext->vddaAzCycles = (uint8_t)((CY_CAPSENSE_BIST_VDDA_AZ_TIME_US * fsmFreqHz) /
                                                       CY_CAPSENSE_CONVERSION_MEGA);
    context->ptrBistContext->vddaAcqCycles = (uint8_t)((CY_CAPSENSE_BIST_VDDA_ACQ_TIME_US * fsmFreqHz) /
                                                        CY_CAPSENSE_CONVERSION_MEGA);
}


/*******************************************************************************
* Function Name: Cy_CapSense_BistMeasureVddaEnable
****************************************************************************//**
*
* This internal function configures the CSD HW block operation and the
* block-level analog routing for the VDDA measurement.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_BistMeasureVddaEnable(cy_stc_capsense_context_t * context)
{
    uint32_t temp;
    CSD_Type * ptrCsdHwBase = context->ptrCommonConfig->ptrCsdBase;

    /* Disable all interrupts from the HW block */
    ptrCsdHwBase->INTR_MASK = CY_CAPSENSE_CSD_INTR_MASK_CLEAR_MSK;
    (void)ptrCsdHwBase->INTR_MASK;
    /* Clear all pending interrupt requests */
    ptrCsdHwBase->INTR = CY_CAPSENSE_CSD_INTR_ALL_MSK;
    (void)ptrCsdHwBase->INTR;

    /* Set the divider value for mod clock (1u lower than the desired divider) */
    Cy_CapSense_SetClkDivider(((uint32_t)context->ptrBistContext->vddaModClk - 1u), context);

    Cy_CapSense_BistSwitchAllSnsPinState(CY_CAPSENSE_BIST_IO_STRONG_E, context);
    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
        Cy_CapSense_BistSwitchAllShieldPinState(CY_CAPSENSE_BIST_IO_STRONG_E, context);
    #endif
    Cy_CapSense_BistSwitchAllExternalCapPinState(CY_CAPSENSE_BIST_IO_STRONG_E, context);
    /* Wait for the maximum possible external capacitor charging time */
    Cy_SysLib_DelayUs(context->ptrBistContext->capacitorSettlingTime);

    /* Configure the HW block for operation in VDDA measurement mode */
    ptrCsdHwBase->CONFIG = CY_CAPSENSE_BIST_VDDA_CONFIG_DEFAULT;
    ptrCsdHwBase->SW_REFGEN_SEL = CY_CAPSENSE_CSD_SW_REFGEN_SEL_SW_SGR_MSK;
    #if (CY_CAPSENSE_PSOC6_FOURTH_GEN)
        if (CY_CAPSENSE_IREF_PASS == context->ptrCommonConfig->ssIrefSource)
        {
            ptrCsdHwBase->CONFIG = CY_CAPSENSE_BIST_VDDA_CONFIG_DEFAULT |
                                   CY_CAPSENSE_CSD_CONFIG_IREF_SEL_MSK;
        }
        if (CY_CAPSENSE_VREF_PASS == context->ptrCommonConfig->ssVrefSource)
        {
            ptrCsdHwBase->SW_REFGEN_SEL = CY_CAPSENSE_CSD_SW_REFGEN_SEL_SW_SGRP_MSK;
        }
        ptrCsdHwBase->IO_SEL = CY_CAPSENSE_BIST_VDDA_IO_SEL_DEFAULT;
    #endif

    /* RefGen initialization */
    temp = CSD_REFGEN_REFGEN_EN_Msk | CSD_REFGEN_RES_EN_Msk |
            ((uint32_t)(context->ptrBistContext->vddaVrefGain) << CSD_REFGEN_GAIN_Pos);
    #if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
        if (CY_CAPSENSE_LOW_VOLTAGE_LIMIT > context->ptrCommonConfig->vdda)
        {
            temp = CSD_REFGEN_REFGEN_EN_Msk | CSD_REFGEN_BYPASS_Msk;
        }
    #endif

    ptrCsdHwBase->HSCMP = CY_CAPSENSE_BIST_VDDA_HSCMP_DEFAULT;
    ptrCsdHwBase->AMBUF = CY_CAPSENSE_BIST_VDDA_AMBUF_DEFAULT;
    ptrCsdHwBase->REFGEN = temp;
    ptrCsdHwBase->SENSE_PERIOD = (uint32_t)CY_CAPSENSE_BIST_VDDA_SENSE_PERIOD_DEFAULT - 1u;
    ptrCsdHwBase->CSDCMP = CY_CAPSENSE_BIST_VDDA_CSDCMP_DEFAULT;
    ptrCsdHwBase->IDACA = CY_CAPSENSE_BIST_VDDA_IDACA_DEFAULT;
    ptrCsdHwBase->IDACB = (uint32_t)CY_CAPSENSE_BIST_VDDA_IDACB_DEFAULT |
                          context->ptrBistContext->vddaIdacDefault;
    ptrCsdHwBase->SEQ_TIME = (uint32_t)context->ptrBistContext->vddaAzCycles - 1u;
    ptrCsdHwBase->ADC_CTL = (uint32_t)context->ptrBistContext->vddaAcqCycles - 1u;
    ptrCsdHwBase->SENSE_DUTY = CY_CAPSENSE_BIST_VDDA_SENSE_DUTY_DEFAULT;
    ptrCsdHwBase->SEQ_INIT_CNT = CY_CAPSENSE_BIST_VDDA_SEQ_INIT_CNT_DEFAULT;
    ptrCsdHwBase->SEQ_NORM_CNT = CY_CAPSENSE_BIST_VDDA_SEQ_NORM_CNT_DEFAULT;
    ptrCsdHwBase->SW_RES = CY_CAPSENSE_BIST_VDDA_SW_RES_DEFAULT;
    ptrCsdHwBase->SW_HS_P_SEL = CY_CAPSENSE_BIST_VDDA_SW_HS_P_SEL_DEFAULT;
    ptrCsdHwBase->SW_HS_N_SEL = CY_CAPSENSE_BIST_VDDA_SW_HS_N_SEL_DEFAULT;
    ptrCsdHwBase->SW_SHIELD_SEL = CY_CAPSENSE_BIST_VDDA_SW_SHIELD_SEL_DEFAULT;
    ptrCsdHwBase->SW_AMUXBUF_SEL = CY_CAPSENSE_BIST_VDDA_SW_AMUXBUF_SEL_DEFAULT;
    ptrCsdHwBase->SW_BYP_SEL = CY_CAPSENSE_BIST_VDDA_SW_BYP_SEL_DEFAULT;
    ptrCsdHwBase->SW_CMP_P_SEL = CY_CAPSENSE_BIST_VDDA_SW_CMP_P_SEL_DEFAULT;
    ptrCsdHwBase->SW_CMP_N_SEL = CY_CAPSENSE_BIST_VDDA_SW_CMP_N_SEL_DEFAULT;
    ptrCsdHwBase->SW_FW_MOD_SEL = CY_CAPSENSE_BIST_VDDA_SW_FW_MOD_SEL_DEFAULT;
    ptrCsdHwBase->SW_FW_TANK_SEL = CY_CAPSENSE_BIST_VDDA_SW_FW_TANK_SEL_DEFAULT;
    ptrCsdHwBase->SW_DSI_SEL = CY_CAPSENSE_BIST_VDDA_SW_DSI_SEL_DEFAULT;
}


/*******************************************************************************
* Function Name: Cy_CapSense_BistMeasureVddaRun
****************************************************************************//**
*
* This internal function initiates the analog to digital conversion and
* converts the measurement result to the voltage in millivolts.
*
* The function performs the following tasks:
* * Measures the time to bring Cref1 + Cref2 up from Vssa to Vrefhi.
* * Measures the time to bring Cref1 + Cref2 back up to Vrefhi
*   (after bringing them down for time A/2 cycles with IDACB sinking).
* * Measures the time to bring Cref1 + Cref2 from Vdda to Vrefhi.
* * Converts the results of measurements to millivolts.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E - The measurement completes
*                                successfully, the result is valid.
* - CY_CAPSENSE_BIST_ERROR_E - An unexpected fault occurred during
*                              the measurement, you may need to repeat
*                              the measurement.
*
*******************************************************************************/
static cy_en_capsense_bist_status_t Cy_CapSense_BistMeasureVddaRun(
                cy_stc_capsense_context_t * context)
{
    uint32_t vddaValue;
    uint32_t tVssa2Vref = 0u;
    uint32_t tRecover = 0u;
    uint32_t tVdda2Vref = 0u;
    uint32_t watchdogPeriod;
    uint32_t watchdogCounter;
    cy_en_csd_status_t conversionStatus;
    cy_en_capsense_bist_status_t retStatus = CY_CAPSENSE_BIST_SUCCESS_E;
    CSD_Type * ptrCsdHwBase = context->ptrCommonConfig->ptrCsdBase;

    watchdogPeriod = Cy_CapSense_WatchdogCyclesNum(
            CY_CAPSENSE_BIST_VDDA_WDT_TIMEOUT,
            (context->ptrCommonConfig->cpuClkHz / CY_CAPSENSE_CONVERSION_MEGA),
            CY_CAPSENSE_BIST_VDDA_WDT_CYCLES_PER_LOOP);

    /* Set the BUSY status */
    context->ptrCommonContext->status = CY_CAPSENSE_BUSY;

    /*
     * Phase 1:
     * Measures the time to bring Cref1 + Cref2 up from Vssa to Vrefhi
     */
    ptrCsdHwBase->ADC_CTL = (ptrCsdHwBase->ADC_CTL & ~CY_CAPSENSE_CSD_ADC_CTL_ADC_MODE_MSK) |
            ((uint32_t)CY_CAPSENSE_BIST_VDDA_MEASMODE_VREF & CY_CAPSENSE_CSD_ADC_CTL_ADC_MODE_MSK);
    ptrCsdHwBase->SEQ_START = CY_CAPSENSE_BIST_VDDA_SEQ_START_MEASURE;
    watchdogCounter = watchdogPeriod;
    do
    {
        conversionStatus = Cy_CSD_GetConversionStatus(ptrCsdHwBase, context->ptrCommonConfig->ptrCsdContext);
        watchdogCounter--;
    }
    while((CY_CSD_BUSY == conversionStatus) && (0u != watchdogCounter));
    ptrCsdHwBase->INTR = CY_CAPSENSE_CSD_INTR_ALL_MSK;
    (void)ptrCsdHwBase->INTR;
    tVssa2Vref = ptrCsdHwBase->ADC_RES;
    if ((0u != (tVssa2Vref & CY_CAPSENSE_CSD_ADC_RES_ADC_OVERFLOW_MSK)) || (0u == watchdogCounter))
    {
        retStatus = CY_CAPSENSE_BIST_ERROR_E;
    }

    /*
     * Phase 2:
     * Measures the time to bring Cref1 + Cref2 back up to Vrefhi
     * (after bringing them down for time A/2 cycles with IDACB sinking)
     */
    if(CY_CAPSENSE_BIST_SUCCESS_E == retStatus)
    {
        ptrCsdHwBase->ADC_CTL = (ptrCsdHwBase->ADC_CTL & ~CY_CAPSENSE_CSD_ADC_CTL_ADC_MODE_MSK) |
                ((uint32_t)CY_CAPSENSE_BIST_VDDA_MEASMODE_VREFBY2 & CY_CAPSENSE_CSD_ADC_CTL_ADC_MODE_MSK);
        ptrCsdHwBase->SEQ_START = CY_CAPSENSE_BIST_VDDA_SEQ_START_MEASURE;
        watchdogCounter = watchdogPeriod;
        do
        {
            conversionStatus = Cy_CSD_GetConversionStatus(ptrCsdHwBase, context->ptrCommonConfig->ptrCsdContext);
            watchdogCounter--;
        }
        while((CY_CSD_BUSY == conversionStatus) && (0u != watchdogCounter));
        ptrCsdHwBase->INTR = CY_CAPSENSE_CSD_INTR_ALL_MSK;
        (void)ptrCsdHwBase->INTR;
        tRecover = ptrCsdHwBase->ADC_RES;
        if ((0u != (tRecover & CY_CAPSENSE_CSD_ADC_RES_ADC_OVERFLOW_MSK)) || (0u == watchdogCounter))
        {
            retStatus = CY_CAPSENSE_BIST_ERROR_E;
        }
    }

    /*
     * Phase 3:
     * Measures the time to bring Cref1 + Cref2 from Vdda to Vrefhi
     */
    if(CY_CAPSENSE_BIST_SUCCESS_E == retStatus)
    {
        /* Connect VDDA to csdbusb */
        ptrCsdHwBase->SW_SHIELD_SEL = CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBV_STATIC_CLOSE;
        ptrCsdHwBase->ADC_CTL = (ptrCsdHwBase->ADC_CTL & ~CY_CAPSENSE_CSD_ADC_CTL_ADC_MODE_MSK) |
                ((uint32_t)CY_CAPSENSE_BIST_VDDA_MEASMODE_VIN & CY_CAPSENSE_CSD_ADC_CTL_ADC_MODE_MSK);
        ptrCsdHwBase->SEQ_START = CY_CAPSENSE_BIST_VDDA_SEQ_START_MEASURE;
        watchdogCounter = watchdogPeriod;
        do
        {
            conversionStatus = Cy_CSD_GetConversionStatus(ptrCsdHwBase, context->ptrCommonConfig->ptrCsdContext);
            watchdogCounter--;
        }
        while((CY_CSD_BUSY == conversionStatus) && (0u != watchdogCounter));
        ptrCsdHwBase->INTR = CY_CAPSENSE_CSD_INTR_ALL_MSK;
        (void)ptrCsdHwBase->INTR;
        tVdda2Vref = ptrCsdHwBase->ADC_RES;
        if ((0u != (tVdda2Vref & CY_CAPSENSE_CSD_ADC_RES_ADC_OVERFLOW_MSK)) || (0u == watchdogCounter))
        {
            retStatus = CY_CAPSENSE_BIST_ERROR_E;
        }
    }

    /*
     * Phase 4:
     * Convert the results of measurements to millivolts.
     */
    if(CY_CAPSENSE_BIST_SUCCESS_E == retStatus)
    {
        tVssa2Vref &= CY_CAPSENSE_CSD_ADC_RES_VALUE_MSK;
        tRecover &= CY_CAPSENSE_CSD_ADC_RES_VALUE_MSK;
        tVdda2Vref &= CY_CAPSENSE_CSD_ADC_RES_VALUE_MSK;

        /* Adjust tVdda2Vref based on IDAC sink / source mismatch */
        tVdda2Vref = (((2u * tRecover) * tVdda2Vref) + (tVssa2Vref >> 1u)) / tVssa2Vref;
        /* Calculate VDDA */
        vddaValue = context->ptrBistContext->vddaVrefMv;
        vddaValue += ((vddaValue * tVdda2Vref) + (tVssa2Vref >> 1uL)) / tVssa2Vref;
        /* Check for overflow */
        if (CY_CAPSENSE_BIST_VDDA_MAX_16_BITS < vddaValue)
        {
            vddaValue = CY_CAPSENSE_BIST_VDDA_MAX_16_BITS;
        }
        context->ptrBistContext->vddaVoltage = (uint16_t)vddaValue;
    }

    /* Clear the BUSY flag */
    context->ptrCommonContext->status = CY_CAPSENSE_NOT_BUSY;

    return (retStatus);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_VDDA_EN) */


/*******************************************************************************
* Function Name: Cy_CapSense_BistInitialize
****************************************************************************//**
*
* The internal function initializes some critical parameters
* for Built-in Self-test (BIST) mode.
*
* This function prepares the resource capturing to execute the BIST functions.
* The HW resource configuring is performed by the Cy_CapSense_BistSwitchHwConfig()
* function depending on a the type of the test to be executed.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_BistInitialize(cy_stc_capsense_context_t * context)
{
    /*
     * This function prepares the BIST HW and pins re-configuring by setting some
     * critical internal parameters to undefined states.
     * Use this function after switching from CSD or CSX sensing modes.
     */
    context->ptrBistContext->hwConfig = CY_CAPSENSE_BIST_HW_UNDEFINED_E;
    context->ptrBistContext->currentISC = CY_CAPSENSE_BIST_IO_UNDEFINED_E;
}


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_HW_GROUP_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_BistDisableMode
****************************************************************************//**
*
* This internal function releases HW resources and pins captured by BIST
* to be used by other CAPSENSE&trade; modes.
*
* This function releases the shared HW resources like connection
* to the analog bus.
* The function does not configure CSD HW block registers to the default state.
* It is used by the Cy_CapSense_SwitchSensingMode() function only at switching
* to another sensing mode.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_BistDisableMode(cy_stc_capsense_context_t * context)
{
    Cy_CapSense_BistSwitchHwConfig(CY_CAPSENSE_BIST_HW_UNDEFINED_E, context);

    Cy_CapSense_BistSwitchAllSnsPinState(CY_CAPSENSE_BIST_IO_UNDEFINED_E, context);
    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
        Cy_CapSense_BistSwitchAllShieldPinState(CY_CAPSENSE_BIST_IO_UNDEFINED_E, context);
    #endif
    Cy_CapSense_BistSwitchAllExternalCapPinState(CY_CAPSENSE_BIST_IO_STRONG_E, context);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_HW_GROUP_EN) */


/*******************************************************************************
* Function Name: Cy_CapSense_BistDsInitialize_V2
****************************************************************************//**
*
* This internal function initializes the BIST cy_stc_capsense_bist_context_t
* data structure parameters to be used in the test execution.
*
* The function is called once at the CAPSENSE&trade; start and performs the CSD HW block
* register pre-calculation based on the configured parameters.
*
* Some of the parameters of the \ref cy_stc_capsense_bist_context_t structure
* can be changed in the run-time, but some changes require repeating the call
* of this function to the re-calculate register values.
* Refer to description of the following functions which parameters are used
* as an input and which are outputs:
* * Cy_CapSense_BistMeasureCapacitanceSensorInit()
* * Cy_CapSense_BistMeasureCapacitanceCapInit()
* * Cy_CapSense_BistMeasureVddaInit()
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_BistDsInitialize_V2(cy_stc_capsense_context_t * context)
{
    uint32_t wdIndex;
    uint32_t wdNum = (uint32_t)context->ptrCommonConfig->numWd;

    /* Initialize CRC and status for all widgets */
    for (wdIndex = 0u; wdIndex < wdNum; wdIndex++)
    {
        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN)
            Cy_CapSense_UpdateCrcWidget(wdIndex, context);
        #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN) */
        context->ptrWdContext[wdIndex].status |= (uint8_t)CY_CAPSENSE_WD_WORKING_MASK;
    }

    #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN) ||\
         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN))
        Cy_CapSense_BistMeasureCapacitanceSensorInit(context);
    #endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN) ||\
               (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN)) */

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_EXTERNAL_CAP_EN)
        Cy_CapSense_BistMeasureCapacitanceCapInit(context);
    #endif

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_VDDA_EN)
        Cy_CapSense_BistMeasureVddaInit(context);
    #endif

    context->ptrBistContext->hwConfig = CY_CAPSENSE_BIST_HW_UNDEFINED_E;
    context->ptrBistContext->currentISC = CY_CAPSENSE_BIST_IO_UNDEFINED_E;
}


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_HW_GROUP_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_BistSwitchHwConfig
****************************************************************************//**
*
* This internal function switches the CSD HW block configuration for
* BIST operations.
*
* The function checks the current CSD HW block configuration.
* If it differs from a desired configuration, the function disables the current
* configuration and sets the desired one.
*
* \param hwCfg
* Specifies the desired configuration.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_BistSwitchHwConfig(
                cy_en_capsense_bist_hw_config_t hwCfg,
                cy_stc_capsense_context_t * context)
{
    if (context->ptrBistContext->hwConfig != hwCfg)
    {
        context->ptrBistContext->hwConfig = hwCfg;
        /* Enable the specified mode */
        switch(hwCfg)
        {
            case CY_CAPSENSE_BIST_HW_SHORT_E:
            {
                /* Nothing to do */
                break;
            }

            #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN) ||\
                 (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN))
                case CY_CAPSENSE_BIST_HW_ELTD_CAP_E:
                {
                    Cy_CapSense_BistMeasureCapacitanceSensorEnable(context);
                    break;
                }

                #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
                    case CY_CAPSENSE_BIST_HW_ELTD_CAP_SH_E:
                    {
                        Cy_CapSense_BistMeasureCapacitanceSensorShieldEnable(context);
                        break;
                    }
                #endif
            #endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN) ||\
                 (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN)) */

            #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_EXTERNAL_CAP_EN)
                case CY_CAPSENSE_BIST_HW_EXTERNAL_CAP_E:
                {
                    Cy_CapSense_BistMeasureCapacitanceCapEnable(context);
                    break;
                }
            #endif

            #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_VDDA_EN)
                case CY_CAPSENSE_BIST_HW_VDDA_E:
                {
                    Cy_CapSense_BistMeasureVddaEnable(context);
                    break;
                }
            #endif

            default:
            {
                /* Nothing to do */
                break;
            }
        }
    }
}


/*******************************************************************************
* Function Name: Cy_CapSense_BistSwitchAllSnsPinState
****************************************************************************//**
*
* This internal function sets all the port control (PC), data (DR) and HSIOM
* registers of all sensor pins to the desired state.
*
* The function sets the desired state for the pin port control register (PC),
* the output data register (DR) and the HSIOM register for all sensor pins
* (Drive Mode, output state, and HSIOM state).
*
* \param desiredPinState
* Specifies the desired pin state. See the possible states
* in the cy_en_capsense_bist_io_state_t enum description.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_BistSwitchAllSnsPinState(
                cy_en_capsense_bist_io_state_t desiredPinState,
                const cy_stc_capsense_context_t * context)
{
    uint32_t desiredDriveMode = CY_CAPSENSE_DM_GPIO_ANALOG;
    en_hsiom_sel_t desiredHsiom = CY_CAPSENSE_HSIOM_SEL_GPIO;
    uint32_t desiredPinOutput = CY_CAPSENSE_BIST_DR_PIN2GND;

    if (context->ptrBistContext->currentISC != desiredPinState)
    {
        /* Change Drive mode and HSIOM depending on the current inactive sensor connection */
        if (CY_CAPSENSE_BIST_IO_STRONG_E == desiredPinState)
        {
            desiredDriveMode = CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF;
            desiredHsiom = CY_CAPSENSE_HSIOM_SEL_GPIO;
            desiredPinOutput = CY_CAPSENSE_BIST_DR_PIN2GND;
        }
        else if (CY_CAPSENSE_BIST_IO_SENSE_E == desiredPinState)
        {
            desiredDriveMode = CY_CAPSENSE_CSD_SCAN_PIN_DM;
            desiredHsiom = CY_CAPSENSE_HSIOM_SEL_CSD_SENSE;
            desiredPinOutput = CY_CAPSENSE_BIST_DR_PIN2GND;
        }
        else if (CY_CAPSENSE_BIST_IO_SHIELD_E == desiredPinState)
        {
            desiredDriveMode = CY_CAPSENSE_DM_SHIELD;
            desiredHsiom = CY_CAPSENSE_HSIOM_SEL_CSD_SHIELD;
            desiredPinOutput = CY_CAPSENSE_BIST_DR_PIN2GND;
        }
        else if (CY_CAPSENSE_BIST_IO_STRONG_HIGH_E == desiredPinState)
        {
            desiredDriveMode = CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF;
            desiredHsiom = CY_CAPSENSE_HSIOM_SEL_GPIO;
            desiredPinOutput = CY_CAPSENSE_BIST_DR_PIN2VDD;
        }
        else
        {
            /* Do nothing */
        }
        /* Set all sensor electrodes to the desired state.*/
        Cy_CapSense_SetIOsInDesiredState(desiredDriveMode, desiredPinOutput, desiredHsiom, context);
        context->ptrBistContext->currentISC = desiredPinState;
    }
}

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_BistSwitchAllShieldPinState
****************************************************************************//**
*
* This internal function sets all the port control (PC), data (DR) and HSIOM
* registers of all shield pins to the desired state.
*
* The function sets the desired state for the pin port control register (PC),
* the output data register (DR) and the HSIOM register for all shield pins
* (Drive Mode, output state, and HSIOM state).
*
* \param desiredPinState
* Specifies the desired pin state. See the possible states
* in the cy_en_capsense_bist_io_state_t enum description.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_BistSwitchAllShieldPinState(
                cy_en_capsense_bist_io_state_t desiredPinState,
                const cy_stc_capsense_context_t * context)
{
    uint32_t desiredDriveMode = CY_CAPSENSE_DM_GPIO_ANALOG;
    en_hsiom_sel_t desiredHsiom = CY_CAPSENSE_HSIOM_SEL_GPIO;
    uint32_t desiredPinOutput = CY_CAPSENSE_BIST_DR_PIN2GND;

    if (CY_CAPSENSE_ENABLE == context->ptrCommonConfig->csdEn)
    {
        /* Change Drive mode and HSIOM depending on the current inactive sensor connection */
        if (CY_CAPSENSE_BIST_IO_STRONG_E == desiredPinState)
        {
            desiredDriveMode = CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF;
            desiredHsiom = CY_CAPSENSE_HSIOM_SEL_GPIO;
            desiredPinOutput = CY_CAPSENSE_BIST_DR_PIN2GND;
        }
        else if (CY_CAPSENSE_BIST_IO_SENSE_E == desiredPinState)
        {
            desiredDriveMode = CY_CAPSENSE_CSD_SCAN_PIN_DM;
            desiredHsiom = CY_CAPSENSE_HSIOM_SEL_CSD_SENSE;
            desiredPinOutput = CY_CAPSENSE_BIST_DR_PIN2GND;
        }
        else if (CY_CAPSENSE_BIST_IO_SHIELD_E == desiredPinState)
        {
            desiredDriveMode = CY_CAPSENSE_DM_SHIELD;
            desiredHsiom = CY_CAPSENSE_HSIOM_SEL_CSD_SHIELD;
            desiredPinOutput = CY_CAPSENSE_BIST_DR_PIN2GND;
        }
        else if (CY_CAPSENSE_BIST_IO_STRONG_HIGH_E == desiredPinState)
        {
            desiredDriveMode = CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF;
            desiredHsiom = CY_CAPSENSE_HSIOM_SEL_GPIO;
            desiredPinOutput = CY_CAPSENSE_BIST_DR_PIN2VDD;
        }
        else
        {
            /* Do nothing */
        }
        /* Set all CAPSENSE&trade; pins to the desired state */
        Cy_CapSense_SetShieldPinState(desiredDriveMode, desiredPinOutput, desiredHsiom, context);
    }
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) */


/*******************************************************************************
* Function Name: Cy_CapSense_BistSwitchAllExternalCapPinState
****************************************************************************//**
*
* The internal function sets all the port control (PC), data (DR) and HSIOM
* registers of all external capacitor pins to the desired state.
*
* The function sets the desired state for the pin port control register (PC),
* the output data register (DR) and the HSIOM register for all external
* capacitor pins (Drive Mode, output state, and HSIOM state).
*
* \param desiredPinState
* Specifies the desired pin state. See the possible states
* in the cy_en_capsense_bist_io_state_t enum description.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_BistSwitchAllExternalCapPinState(
                cy_en_capsense_bist_io_state_t desiredPinState,
                const cy_stc_capsense_context_t * context)
{
    /* If CSD is enabled, set the Cmod pin to the desired state */
    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
        Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCmod, (uint32_t)context->ptrCommonConfig->pinCmod, CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF, CY_CAPSENSE_HSIOM_SEL_GPIO);
        if (CY_CAPSENSE_BIST_IO_STRONG_HIGH_E == desiredPinState)
        {
            Cy_GPIO_Set(context->ptrCommonConfig->portCmod, (uint32_t)context->ptrCommonConfig->pinCmod);
        }
        else
        {
            Cy_GPIO_Clr(context->ptrCommonConfig->portCmod, (uint32_t)context->ptrCommonConfig->pinCmod);
        }

        /* If Csh is enabled, set the Csh pin to the desired state */
        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_CAP_EN)
            Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCsh, (uint32_t)context->ptrCommonConfig->pinCsh, CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF, CY_CAPSENSE_HSIOM_SEL_GPIO);
            if (CY_CAPSENSE_BIST_IO_STRONG_HIGH_E == desiredPinState)
            {
                Cy_GPIO_Set(context->ptrCommonConfig->portCsh, (uint32_t)context->ptrCommonConfig->pinCsh);
            }
            else
            {
                Cy_GPIO_Clr(context->ptrCommonConfig->portCsh, (uint32_t)context->ptrCommonConfig->pinCsh);
            }
        #endif
    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

    /* If CSX is enabled, set the CintA and CintB pins to the desired state */
    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
        Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCintA, (uint32_t)context->ptrCommonConfig->pinCintA, CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF, CY_CAPSENSE_HSIOM_SEL_GPIO);
        Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCintB, (uint32_t)context->ptrCommonConfig->pinCintB, CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF, CY_CAPSENSE_HSIOM_SEL_GPIO);
        if (CY_CAPSENSE_BIST_IO_STRONG_HIGH_E == desiredPinState)
        {
            Cy_GPIO_Set(context->ptrCommonConfig->portCintA, (uint32_t)context->ptrCommonConfig->pinCintA);
            Cy_GPIO_Set(context->ptrCommonConfig->portCintB, (uint32_t)context->ptrCommonConfig->pinCintB);
        }
        else
        {
            Cy_GPIO_Clr(context->ptrCommonConfig->portCintA, (uint32_t)context->ptrCommonConfig->pinCintA);
            Cy_GPIO_Clr(context->ptrCommonConfig->portCintB, (uint32_t)context->ptrCommonConfig->pinCintB);
        }
    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */
}


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_SetShieldPinState
****************************************************************************//**
*
* This internal function sets all the port control (PC), data (DR) and HSIOM
* registers of all shield pins to the desired state.
*
* The function sets the desired state of the pin the port control register (PC),
* output data register (DR) and HSIOM register for all shield (if defined) pins
* (Drive Mode, output state and HSIOM state).
* The function is called by the Cy_CapSense_BistSwitchAllShieldPinState()
* function and by the shield capacity measurement test. Do not call this
* function directly from the application program - the project
* behavior is unpredictable.
*
* \param desiredDriveMode
* Specifies the desired pin control port (PC) configuration.
*
* \param desiredPinOutput
* Specifies the desired pin output data register (DR) state.
*
* \param desiredHsiom
* Specifies the desired pin HSIOM state.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_SetShieldPinState(
                uint32_t desiredDriveMode,
                uint32_t desiredPinOutput,
                en_hsiom_sel_t desiredHsiom,
                const cy_stc_capsense_context_t * context)
{
    uint32_t loopIndex;
    const cy_stc_capsense_pin_config_t * ptrPinCfg;

    /* Set the shield pins to the desired state */
    ptrPinCfg = context->ptrShieldPinConfig;
    for (loopIndex = 0u; loopIndex < context->ptrCommonConfig->csdShieldNumPin; loopIndex++)
    {
        Cy_CapSense_SsConfigPinRegisters(ptrPinCfg->pcPtr, (uint32_t)ptrPinCfg->pinNumber, desiredDriveMode, desiredHsiom);
        if (0u != desiredPinOutput)
        {
            Cy_GPIO_Set(ptrPinCfg->pcPtr, (uint32_t)ptrPinCfg->pinNumber);
        }
        else
        {
            Cy_GPIO_Clr(ptrPinCfg->pcPtr, (uint32_t)ptrPinCfg->pinNumber);
        }
        /* Get a next electrode */
        ptrPinCfg++;
    }
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_BistConnectElectrode
****************************************************************************//**
*
* This internal function connects the electrode (including a ganged one)
* to the CSD HW block via the AMUX bus.
*
* The function gets the pin configuration registers addresses, their shifts and
* masks from the cy_stc_capsense_pin_config_t object. Based on this data, it
* updates the HSIOM and PC registers.
*
* Do not call this function directly from the application program -
* the project behavior is unpredictable.
*
* \param widgetId
* Specifies the ID number of the widget.
* A macro for the widget ID can be found in the
* CAPSENSE&trade; Configuration header file (cycfg_capsense.h) defined as
* CY_CAPSENSE_<WidgetName>_WDGT_ID.
*
* \param electrodeId
* Specifies the ID of the sensor (electrode for CSX widgets) within the widget
* to be measured.
*
* For the CSD widgets, a macro for the electrodeId is identical
* to the sensor ID within the specified widget and can be found
* in the CAPSENSE&trade; Configuration header file (cycfg_capsense.h)
* defined as CY_CAPSENSE_<WidgetName>_SNS<SensorNumber>_ID.
*
* For the CSX widgets, the electrodeId is defined as Rx electrode ID
* or Tx electrode ID. The first Rx in a widget corresponds to electrodeId = 0,
* the second Rx in a widget corresponds to electrodeId = 1, and so on.
* The last Tx in a widget corresponds to electrodeId = (RxNum + TxNum - 1).
* Macros for Rx and Tx IDs can be found in the CAPSENSE&trade; Configuration header
* file (cycfg_capsense.h) defined as:
* * CapSense_<WidgetName>_RX<RXNumber>_ID
* * CapSense_<WidgetName>_TX<TXNumber>_ID.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_BistConnectElectrode(
                uint32_t widgetId,
                uint32_t electrodeId,
                const cy_stc_capsense_context_t * context)
{
    uint32_t i;
    const cy_stc_capsense_electrode_config_t * ptrEltdCfg = &context->ptrWdConfig[widgetId].ptrEltdConfig[electrodeId];
    const cy_stc_capsense_pin_config_t * ptrPinCfg = ptrEltdCfg->ptrPin;

    /* Connect all electrode pins */
    for(i = 0u; i < ptrEltdCfg->numPins; i++)
    {
        Cy_CapSense_SsConfigPinRegisters(ptrPinCfg->pcPtr, (uint32_t)ptrPinCfg->pinNumber,
                CY_CAPSENSE_CSD_SCAN_PIN_DM, CY_CAPSENSE_HSIOM_SEL_CSD_SENSE);
        ptrPinCfg++;
    }
}


/*******************************************************************************
* Function Name: Cy_CapSense_BistDisconnectElectrode
****************************************************************************//**
*
* This internal function disconnects the electrode (including a ganged one)
* from the CSD HW block and sets all its pins to the configured
* in the .snsCapCsdISC or .snsCapCsxISC fields
* of the cy_stc_capsense_bist_context_t structure.
*
* The function gets the pin configuration registers addresses, their shifts and
* masks from the cy_stc_capsense_pin_config_t object. Based on this data, it
* updates the HSIOM and PC registers.
*
* Do not call this function directly from the application program -
* the project behavior is unpredictable.
*
* \param widgetId
* Specifies the ID number of the widget.
* A macro for the widget ID can be found in the
* CAPSENSE&trade; Configuration header file (cycfg_capsense.h) defined as
* CY_CAPSENSE_<WidgetName>_WDGT_ID.
*
* \param electrodeId
* Specifies the ID of the sensor (electrode for CSX widgets) within the widget
* to be measured.
*
* For the CSD widgets, a macro for the electrodeId is identical
* to the sensor ID within the specified widget and can be found
* in the CAPSENSE&trade; Configuration header file (cycfg_capsense.h)
* defined as CY_CAPSENSE_<WidgetName>_SNS<SensorNumber>_ID.
*
* For the CSX widgets, the electrode ID is defined as Rx electrode ID
* or Tx electrode ID. The first Rx in a widget corresponds to electrodeId = 0,
* the second Rx in a widget corresponds to electrodeId = 1, and so on.
* The last Tx in a widget corresponds to electrodeId = (RxNum + TxNum - 1).
* Macros for Rx and Tx IDs can be found in the CAPSENSE&trade; Configuration header
* file (cycfg_capsense.h) defined as:
* * CapSense_<WidgetName>_RX<RXNumber>_ID
* * CapSense_<WidgetName>_TX<TXNumber>_ID.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_BistDisconnectElectrode(
                uint32_t widgetId,
                uint32_t electrodeId,
                const cy_stc_capsense_context_t * context)

{
    uint32_t i;
    uint32_t driveModeTmp;
    en_hsiom_sel_t hsiomTmp;
    const cy_stc_capsense_electrode_config_t * ptrEltdCfg = &context->ptrWdConfig[widgetId].ptrEltdConfig[electrodeId];
    const cy_stc_capsense_pin_config_t * ptrPinCfg = ptrEltdCfg->ptrPin;

    /* Change Drive mode and HSIOM depending on the current inactive sensor connection */
    switch (context->ptrBistContext->currentISC)
    {
        case CY_CAPSENSE_BIST_IO_STRONG_E:
            driveModeTmp = CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF;
            hsiomTmp = CY_CAPSENSE_HSIOM_SEL_GPIO;
            break;
        case CY_CAPSENSE_BIST_IO_SHIELD_E:
            driveModeTmp = CY_CAPSENSE_DM_SHIELD;
            hsiomTmp = CY_CAPSENSE_HSIOM_SEL_AMUXB;
            break;
        default:
            driveModeTmp = CY_CAPSENSE_DM_GPIO_ANALOG;
            hsiomTmp = CY_CAPSENSE_HSIOM_SEL_GPIO;
            break;
    }

    /* Disconnect all electrode pins */
    for(i = 0u; i < ptrEltdCfg->numPins; i++)
    {
        Cy_CapSense_SsConfigPinRegisters(ptrPinCfg->pcPtr, (uint32_t)ptrPinCfg->pinNumber, driveModeTmp, hsiomTmp);
        Cy_GPIO_Clr(ptrPinCfg->pcPtr, (uint32_t)ptrPinCfg->pinNumber);

        ptrPinCfg++;
    }
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN) || \
    (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN)  || \
    (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_EXTERNAL_CAP_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_BistWaitEndOfScan
****************************************************************************//**
*
* This internal function checks for the scan status. If the scan ends before
* the software watch-dog triggering, the function returns a non-zero watch-dog
* cycles number. If the software watch-dog triggers during the scan,
* the function returns zero.
*
* \param watchdogCycleNum
* A watch-dog cycle number to check a timeout.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns watch-dog counter. If it is equal to zero, it means timeout happened.
*
*******************************************************************************/
static uint32_t Cy_CapSense_BistWaitEndOfScan(
                uint32_t watchdogCycleNum,
                const cy_stc_capsense_context_t * context)
{
    uint32_t watchdogCounter = watchdogCycleNum;

    while (((context->ptrCommonConfig->ptrCsdBase->INTR &
             CY_CAPSENSE_CSD_INTR_SAMPLE_MSK) == 0u) && (0u != watchdogCounter))
    {
        watchdogCounter--;
    }

    return (watchdogCounter);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN) || \
          (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN)  || \
          (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_EXTERNAL_CAP_EN) */

#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_HW_GROUP_EN) */

#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) */

#endif /* (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2)) */


/* [] END OF FILE */
