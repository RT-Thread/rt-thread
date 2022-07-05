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
* Copyright 2021, Cypress Semiconductor Corporation (an Infineon company)
* or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include <stddef.h>
#include <string.h>
#include "cy_syslib.h"
#include "cy_sysclk.h"
#include "cycfg_capsense_defines.h"
#include "cy_capsense_common.h"
#include "cy_capsense_sensing.h"
#include "cy_capsense_sensing_v3.h"
#include "cy_capsense_generator_v3.h"
#include "cy_capsense_selftest_v3.h"
#include "cy_gpio.h"


#if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
    #include "cy_msc.h"
#endif

#if (defined(CY_IP_M0S8MSCV3))

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN)

/*******************************************************************************
* Common local definitions for self-test
*******************************************************************************/

/* Port Data Register macros for BIST */
#define CY_CAPSENSE_BIST_DR_PIN2GND                             (0u)
#define CY_CAPSENSE_BIST_DR_PIN2VDD                             (1u)
/* Electrode capacitance measurement macros for BIST */
#define CY_CAPSENSE_BIST_CAP_SLOT_SCAN                          (0u)
#define CY_CAPSENSE_BIST_CAP_ELTD_SCAN                          (1u)
#define CY_CAPSENSE_BIST_CAP_SHIELD_SCAN                        (2u)
/** The number of BIST sense mode configurations for capacitance measurements (CSD + CSX) */
#define CY_CAPSENSE_BIST_SENSE_MODE_CONFIG_NUMBER               (2u)
#define CY_CAPSENSE_BIST_ELTD_CAP_MODCLK_DIV_DEFAULT            (1u)
#define CY_CAPSENSE_BIST_ELTD_CAP_MAX_MODCLK                    (48000000u)
#define CY_CAPSENSE_BIST_ELTD_CAP_SNSCLK_DIV_DEFAULT            (256u)
#define CY_CAPSENSE_BIST_SHIELD_CAP_SNSCLK_DIV_DEFAULT          (1024u)
#define CY_CAPSENSE_BIST_SNS_CLK_MIN_DIVIDER                    (4u)
#define CY_CAPSENSE_BIST_SNS_CLK_MAX_DIVIDER                    (4096u)
#define CY_CAPSENSE_BIST_ELTD_CAP_SUBCONV_NUM_DEFAULT           (100u)
#define CY_CAPSENSE_BIST_SHIELD_CAP_REF_CDAC_DEFAULT            (200u)
#define CY_CAPSENSE_BIST_ELTD_CAP_REF_CDAC_DEFAULT              (100u)
#define CY_CAPSENSE_BIST_MUTUAL_CAP_REF_CDAC_DEFAULT            (50u)
#define CY_CAPSENSE_BIST_WATCHDOG_MARGIN_COEFF                  (3u)
#define CY_CAPSENSE_BIST_CAP_MEAS_WDT_CYCLES_PER_LOOP           (5u)
#define CY_CAPSENSE_BIST_V3_ELTD_CAP_CYCLES_NUM                 (1u)
#define CY_CAPSENSE_BIST_CAP_MEAS_CDAC_LSB_FF_DIV_1000          (8860u)
#define CY_CAPSENSE_BIST_CP_MAX_VALUE                           (200000u)
#define CY_CAPSENSE_BIST_CSH_MAX_VALUE                          (1600000u)
#define CY_CAPSENSE_BIST_PROMILLE_FACTOR                        (1000u)

/** Initialization of sensing method template variable */
#define CY_CAPSENSE_BIST_SENSING_METHOD_BASE_TEMPLATE   \
    {                                                   \
        .ctl = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CTL_FLD_SENSE_EN << MSC_CTL_SENSE_EN_Pos)                    | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CTL_FLD_MSCCMP_EN << MSC_CTL_MSCCMP_EN_Pos)                   | \
                    ((uint32_t)CY_CAPSENSE_SCAN_MODE_INT_DRIVEN << MSC_CTL_OPERATING_MODE_Pos)                       | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CTL_FLD_BUF_MODE << MSC_CTL_BUF_MODE_Pos)                     | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CTL_FLD_CLK_MSC_RATIO << MSC_CTL_CLK_MSC_RATIO_Pos)           | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CTL_FLD_ENABLED << MSC_CTL_ENABLED_Pos)),                      \
        .spare              = 0x00uL, \
        .scanCtl1           = 0x00uL, \
        .scanCtl2           = 0x00uL, \
        .initCtl1           = 0x00uL, \
        .initCtl2           = 0x00uL, \
        .initCtl3           = 0x00uL, \
        .initCtl4           = 0x00uL, \
        .senseDutyCtl = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SENSE_DUTY_CTL_FLD_PHASE_WIDTH << MSC_SENSE_DUTY_CTL_PHASE_WIDTH_Pos)              | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SENSE_DUTY_CTL_FLD_PHASE_SHIFT_CYCLES << MSC_SENSE_DUTY_CTL_PHASE_SHIFT_CYCLES_Pos) | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SENSE_DUTY_CTL_FLD_PHASE_WIDTH_SEL << MSC_SENSE_DUTY_CTL_PHASE_WIDTH_SEL_Pos)),      \
        .sensePeriodCtl     = 0x00uL, \
        .filterCtl          = 0x00uL, \
        .ccompCdacCtl       = 0x00uL, \
        .ditherCdacCtl      = 0x00uL, \
        .cswCtl             = 0x00uL, \
        .swSelGpio          = 0x00uL, \
        .swSelCdacRe = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_RE_FLD_SW_RETCA << MSC_SW_SEL_CDAC_RE_SW_RETCA_Pos) | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_RE_FLD_SW_RECB   << MSC_SW_SEL_CDAC_RE_SW_RECB_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_RE_FLD_SW_RETV   << MSC_SW_SEL_CDAC_RE_SW_RETV_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_RE_FLD_SW_RETG   << MSC_SW_SEL_CDAC_RE_SW_RETG_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_RE_FLD_SW_REBV   << MSC_SW_SEL_CDAC_RE_SW_REBV_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_RE_FLD_SW_REBG   << MSC_SW_SEL_CDAC_RE_SW_REBG_Pos)), \
        .swSelCdacCo        = 0x00uL, \
        .swSelCdacCf        = 0x00uL, \
        .swSelCmod1 = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD1_FLD_SW_C1CA << MSC_SW_SEL_CMOD1_SW_C1CA_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD1_FLD_SW_C1CB  << MSC_SW_SEL_CMOD1_SW_C1CB_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD1_FLD_SW_C1CC  << MSC_SW_SEL_CMOD1_SW_C1CC_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD1_FLD_SW_C1CV  << MSC_SW_SEL_CMOD1_SW_C1CV_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD1_FLD_SW_C1CG  << MSC_SW_SEL_CMOD1_SW_C1CG_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD1_FLD_REF_MODE << MSC_SW_SEL_CMOD1_REF_MODE_Pos) | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD1_FLD_ENABLED  << MSC_SW_SEL_CMOD1_ENABLED_Pos)), \
        .swSelCmod2 = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD2_FLD_SW_C2CA << MSC_SW_SEL_CMOD2_SW_C2CA_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD2_FLD_SW_C2CB  << MSC_SW_SEL_CMOD2_SW_C2CB_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD2_FLD_SW_C2CC  << MSC_SW_SEL_CMOD2_SW_C2CC_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD2_FLD_SW_C2CV  << MSC_SW_SEL_CMOD2_SW_C2CV_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD2_FLD_SW_C2CG  << MSC_SW_SEL_CMOD2_SW_C2CG_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD2_FLD_REF_MODE << MSC_SW_SEL_CMOD2_REF_MODE_Pos) | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD2_FLD_ENABLED  << MSC_SW_SEL_CMOD2_ENABLED_Pos)), \
        .swSelCmod3 = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD3_FLD_SW_C3CA << MSC_SW_SEL_CMOD3_SW_C3CA_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD3_FLD_SW_C3CB  << MSC_SW_SEL_CMOD3_SW_C3CB_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD3_FLD_SW_C3CC  << MSC_SW_SEL_CMOD3_SW_C3CC_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD3_FLD_SW_C3CV  << MSC_SW_SEL_CMOD3_SW_C3CV_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD3_FLD_SW_C3CG  << MSC_SW_SEL_CMOD3_SW_C3CG_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD3_FLD_REF_MODE << MSC_SW_SEL_CMOD3_REF_MODE_Pos) | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD3_FLD_ENABLED  << MSC_SW_SEL_CMOD3_ENABLED_Pos)), \
        .swSelCmod4 = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD4_FLD_SW_C4CA << MSC_SW_SEL_CMOD4_SW_C4CA_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD4_FLD_SW_C4CB  << MSC_SW_SEL_CMOD4_SW_C4CB_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD4_FLD_SW_C4CC  << MSC_SW_SEL_CMOD4_SW_C4CC_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD4_FLD_SW_C4CV  << MSC_SW_SEL_CMOD4_SW_C4CV_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD4_FLD_SW_C4CG  << MSC_SW_SEL_CMOD4_SW_C4CG_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD4_FLD_REF_MODE << MSC_SW_SEL_CMOD4_REF_MODE_Pos) | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD4_FLD_ENABLED  << MSC_SW_SEL_CMOD4_ENABLED_Pos)), \
        .obsCtl             = 0x00uL, \
        .status1            = 0x00uL, \
        .status2            = 0x00uL, \
        .status3            = 0x00uL, \
        .resultFifoStatus   = 0x00uL, \
        .resultFifoRd       = 0x00uL, \
        .intr = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_FLD_SUB_SAMPLE    << MSC_INTR_SUB_SAMPLE_Pos)     | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_FLD_SAMPLE         << MSC_INTR_SAMPLE_Pos)         | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_FLD_SCAN           << MSC_INTR_SCAN_Pos)           | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_FLD_INIT           << MSC_INTR_INIT_Pos)           | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_FLD_FRAME          << MSC_INTR_FRAME_Pos)          | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_FLD_FIFO_UNDERFLOW << MSC_INTR_FIFO_UNDERFLOW_Pos) | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_FLD_FIFO_OVERFLOW  << MSC_INTR_FIFO_OVERFLOW_Pos)), \
        .intrSet            = 0x00uL, \
        .intrMask           = 0x00uL, \
        .intrMasked         = 0x00uL, \
        .frameCmd           = 0x00uL, \
        .sensorConfig = \
        { \
            .snsSwSelCswMask2   = 0x00uL, \
            .snsSwSelCswMask1   = 0x00uL, \
            .snsSwSelCswMask0   = 0x00uL, \
            .snsScanCtl         = 0x00uL, \
            .snsCdacCtl         = 0x00uL, \
            .snsCtl             = 0x00uL, \
        }, \
        .swSelCsw = \
        { \
            [0u]       = 0x00uL, \
            [1u]       = 0x00uL, \
            [2u]       = 0x00uL, \
            [3u]       = 0x00uL, \
            [4u]       = 0x00uL, \
            [5u]       = 0x00uL, \
            [6u]       = 0x00uL, \
            [7u]       = 0x00uL, \
            [8u]       = 0x00uL, \
            [9u]       = 0x00uL, \
            [10u]      = 0x00uL, \
            [11u]      = 0x00uL, \
            [12u]      = 0x00uL, \
            [13u]      = 0x00uL, \
            [14u]      = 0x00uL, \
            [15u]      = 0x00uL, \
            [16u]      = 0x00uL, \
            [17u]      = 0x00uL, \
            [18u]      = 0x00uL, \
            [19u]      = 0x00uL, \
            [20u]      = 0x00uL, \
            [21u]      = 0x00uL, \
            [22u]      = 0x00uL, \
            [23u]      = 0x00uL, \
            [24u]      = 0x00uL, \
            [25u]      = 0x00uL, \
            [26u]      = 0x00uL, \
            [27u]      = 0x00uL, \
            [28u]      = 0x00uL, \
            [29u]      = 0x00uL, \
            [30u]      = 0x00uL, \
            [31u]      = 0x00uL, \
        }, \
        .swSelCswFunc = \
        { \
            [CY_CAPSENSE_CTRLMUX_PIN_STATE_RX] = (CY_CAPSENSE_SM_REG_SW_SEL_CSW0_RX_VALUE), \
            [CY_CAPSENSE_CTRLMUX_PIN_STATE_TX] = (CY_CAPSENSE_SM_REG_SW_SEL_CSW1_TX_VALUE), \
            [CY_CAPSENSE_CTRLMUX_PIN_STATE_TX_NEGATIVE] = 0x00uL, \
            [CY_CAPSENSE_CTRLMUX_PIN_STATE_GND] = (CY_CAPSENSE_SM_REG_SW_SEL_CSW4_GND_VALUE), \
            [CY_CAPSENSE_CTRLMUX_PIN_STATE_SNS] = (CY_CAPSENSE_SM_REG_SW_SEL_CSW3_SNS_VALUE), \
            [CY_CAPSENSE_CTRLMUX_PIN_STATE_HIGH_Z] = (CY_CAPSENSE_SM_REG_SW_SEL_CSW5_HIGH_Z_VALUE), \
            [CY_CAPSENSE_CTRLMUX_PIN_STATE_SHIELD] = 0x00uL, \
            [CY_CAPSENSE_CTRLMUX_PIN_STATE_VDDA2] = 0x00uL, \
        }, \
        .mode = \
        { \
            [CY_CAPSENSE_CSD_RM_SENSING_METHOD_INDEX] = \
            { \
                .senseDutyCtl = \
                        ((CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH0_EN     << MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_PH0_EN_Pos)     | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH1_EN     << MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_PH1_EN_Pos)     | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH2_EN     << MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_PH2_EN_Pos)     | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH3_EN     << MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_PH3_EN_Pos)     | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_FS2_PH0_EN << MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_FS2_PH0_EN_Pos) | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_FS2_PH1_EN << MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_FS2_PH1_EN_Pos) | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PH_GAP_2CYCLE_EN     << MSC_MODE_SENSE_DUTY_CTL_PH_GAP_2CYCLE_EN_Pos)     | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH0X_EN    << MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_PH0X_EN_Pos)    | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH1X_EN    << MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_PH1X_EN_Pos)    | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHX_GAP_2CYCLE_EN    << MSC_MODE_SENSE_DUTY_CTL_PHX_GAP_2CYCLE_EN_Pos)    | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_SHIFT_EN       << MSC_MODE_SENSE_DUTY_CTL_PHASE_SHIFT_EN_Pos)       | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_MODE_SEL       << MSC_MODE_SENSE_DUTY_CTL_PHASE_MODE_SEL_Pos)),      \
                .swSelCdacFl =  0u, \
                .swSelTop = \
                        ((CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_CACB     << MSC_MODE_SW_SEL_TOP_CACB_Pos)    | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_CACC     << MSC_MODE_SW_SEL_TOP_CACC_Pos)    | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_CBCC     << MSC_MODE_SW_SEL_TOP_CBCC_Pos)    | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_MBCC     << MSC_MODE_SW_SEL_TOP_MBCC_Pos)    | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_AYA_CTL  << MSC_MODE_SW_SEL_TOP_AYA_CTL_Pos) | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_AYB_CTL  << MSC_MODE_SW_SEL_TOP_AYB_CTL_Pos) | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_BYB      << MSC_MODE_SW_SEL_TOP_BYB_Pos)     | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_SOSH     << MSC_MODE_SW_SEL_TOP_SOSH_Pos)    | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_SHV      << MSC_MODE_SW_SEL_TOP_SHV_Pos)     | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_SHG      << MSC_MODE_SW_SEL_TOP_SHG_Pos)     | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_BGRF     << MSC_MODE_SW_SEL_TOP_BGRF_Pos)    | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_RMF      << MSC_MODE_SW_SEL_TOP_RMF_Pos)     | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_MBF      << MSC_MODE_SW_SEL_TOP_MBF_Pos)),    \
                .swSelComp = 0u, \
                .swSelSh = \
                        ((CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_C1SH    << MSC_MODE_SW_SEL_SH_C1SH_Pos)    | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_C3SH    << MSC_MODE_SW_SEL_SH_C3SH_Pos)    | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_SOMB    << MSC_MODE_SW_SEL_SH_SOMB_Pos)    | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_CBSO    << MSC_MODE_SW_SEL_SH_CBSO_Pos)    | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_SPCS1   << MSC_MODE_SW_SEL_SH_SPCS1_Pos)   | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_SPCS3   << MSC_MODE_SW_SEL_SH_SPCS3_Pos)   | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_FSP     << MSC_MODE_SW_SEL_SH_FSP_Pos)     | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_CCSO    << MSC_MODE_SW_SEL_SH_CCSO_Pos)    | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_BUF_SEL << MSC_MODE_SW_SEL_SH_BUF_SEL_Pos) | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_BUF_EN  << MSC_MODE_SW_SEL_SH_BUF_EN_Pos)), \
            }, \
            [CY_CAPSENSE_CSX_RM_SENSING_METHOD_INDEX] = \
            { \
                .senseDutyCtl = \
                        ((CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH0_EN     << MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_PH0_EN_Pos)     | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH1_EN     << MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_PH1_EN_Pos)     | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH2_EN     << MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_PH2_EN_Pos)     | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH3_EN     << MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_PH3_EN_Pos)     | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_FS2_PH0_EN << MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_FS2_PH0_EN_Pos) | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_FS2_PH1_EN << MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_FS2_PH1_EN_Pos) | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PH_GAP_2CYCLE_EN     << MSC_MODE_SENSE_DUTY_CTL_PH_GAP_2CYCLE_EN_Pos)     | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH0X_EN    << MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_PH0X_EN_Pos)    | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH1X_EN    << MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_PH1X_EN_Pos)    | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHX_GAP_2CYCLE_EN    << MSC_MODE_SENSE_DUTY_CTL_PHX_GAP_2CYCLE_EN_Pos)    | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_SHIFT_EN       << MSC_MODE_SENSE_DUTY_CTL_PHASE_SHIFT_EN_Pos)       | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_MODE_SEL       << MSC_MODE_SENSE_DUTY_CTL_PHASE_MODE_SEL_Pos)),      \
                .swSelCdacFl =  0u, \
                .swSelTop = \
                        ((CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_CACB     << MSC_MODE_SW_SEL_TOP_CACB_Pos)    | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_CACC     << MSC_MODE_SW_SEL_TOP_CACC_Pos)    | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_CBCC     << MSC_MODE_SW_SEL_TOP_CBCC_Pos)    | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_MBCC     << MSC_MODE_SW_SEL_TOP_MBCC_Pos)    | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_AYA_CTL  << MSC_MODE_SW_SEL_TOP_AYA_CTL_Pos) | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_AYB_CTL  << MSC_MODE_SW_SEL_TOP_AYB_CTL_Pos) | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_BYB      << MSC_MODE_SW_SEL_TOP_BYB_Pos)     | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_SOSH     << MSC_MODE_SW_SEL_TOP_SOSH_Pos)    | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_SHV      << MSC_MODE_SW_SEL_TOP_SHV_Pos)     | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_SHG      << MSC_MODE_SW_SEL_TOP_SHG_Pos)     | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_BGRF     << MSC_MODE_SW_SEL_TOP_BGRF_Pos)    | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_RMF      << MSC_MODE_SW_SEL_TOP_RMF_Pos)     | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_MBF      << MSC_MODE_SW_SEL_TOP_MBF_Pos)),    \
                .swSelComp = 0u, \
                .swSelSh = \
                        ((CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_C1SHG   << MSC_MODE_SW_SEL_SH_C1SHG_Pos)   | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_C1SH    << MSC_MODE_SW_SEL_SH_C1SH_Pos)    | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_C3SHG   << MSC_MODE_SW_SEL_SH_C3SHG_Pos)   | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_C3SH    << MSC_MODE_SW_SEL_SH_C3SH_Pos)    | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_SOMB    << MSC_MODE_SW_SEL_SH_SOMB_Pos)    | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_CBSO    << MSC_MODE_SW_SEL_SH_CBSO_Pos)    | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_SPCS1   << MSC_MODE_SW_SEL_SH_SPCS1_Pos)   | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_SPCS3   << MSC_MODE_SW_SEL_SH_SPCS3_Pos)   | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_FSP     << MSC_MODE_SW_SEL_SH_FSP_Pos)     | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_CCSO    << MSC_MODE_SW_SEL_SH_CCSO_Pos)    | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_BUF_SEL << MSC_MODE_SW_SEL_SH_BUF_SEL_Pos) | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_BUF_EN  << MSC_MODE_SW_SEL_SH_BUF_EN_Pos)), \
            }, \
            [2u] = \
            { \
                .senseDutyCtl   = 0x00uL, \
                .swSelCdacFl    = 0x00uL, \
                .swSelTop       = 0x00uL, \
                .swSelComp      = 0x00uL, \
                .swSelSh        = 0x00uL, \
            }, \
            [3u] = \
            { \
                .senseDutyCtl   = 0x00uL, \
                .swSelCdacFl    = 0x00uL, \
                .swSelTop       = 0x00uL, \
                .swSelComp      = 0x00uL, \
                .swSelSh        = 0x00uL, \
            }, \
        }, \
    }


/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************/
/** \cond SECTION_CAPSENSE_INTERNAL */
/** \addtogroup group_capsense_internal *//** \{ */
/******************************************************************************/

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN)
    static cy_en_capsense_bist_status_t Cy_CapSense_CheckAllWidgetCRC(
                cy_stc_capsense_context_t * context);
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN)) */

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_SHORT_EN)
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

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_HW_GROUP_EN)
    static void Cy_CapSense_BistSwitchHwConfig(
                    cy_en_capsense_bist_hw_config_t hwCfg,
                    uint8_t bistSenseGroup,
                    uint8_t bistScanMode,
                    cy_stc_capsense_context_t * context);
    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_SHORT_EN)
        static void Cy_CapSense_BistSetPinDr(
                        cy_stc_capsense_pin_config_t const *ioPtr,
                        uint32_t value);
        static void Cy_CapSense_BistSetPinPc(
                        cy_stc_capsense_pin_config_t const *ioPtr,
                        uint32_t value);
    #endif
    static void Cy_CapSense_BistSwitchAllSnsPinState(
                    cy_en_capsense_bist_io_state_t desiredPinState,
                    const cy_stc_capsense_context_t * context);
    static void Cy_CapSense_BistSwitchAllExternalCapPinState(
                    cy_en_capsense_bist_io_state_t desiredPinState,
                    const cy_stc_capsense_context_t * context);
    void Cy_CapSense_BistSetAllSnsPinsState(
                    uint32_t desiredDriveMode,
                    uint32_t desiredPinOutput,
                    en_hsiom_sel_t desiredHsiom,
                    const cy_stc_capsense_context_t * context);
    void Cy_CapSense_BistSetAllCmodPinsState(
                    uint32_t desiredDriveMode,
                    uint32_t desiredPinOutput,
                    en_hsiom_sel_t desiredHsiom,
                    const cy_stc_capsense_context_t * context);

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
        static void Cy_CapSense_BistSwitchAllShieldPinState(
                        cy_en_capsense_bist_io_state_t desiredPinState,
                        const cy_stc_capsense_context_t * context);
        void Cy_CapSense_BistSetAllShieldPinsState(
                        uint32_t desiredDriveMode,
                        uint32_t desiredPinOutput,
                        en_hsiom_sel_t desiredHsiom,
                        const cy_stc_capsense_context_t * context);
    #endif

    static void Cy_CapSense_BistSetDmHsiomPinState(
                    cy_en_capsense_bist_io_state_t desiredPinState,
                    const cy_stc_capsense_context_t * context);
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_HW_GROUP_EN) */

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_ELTD_CAP_EN)
    static cy_en_capsense_bist_status_t Cy_CapSense_MeasureCapacitanceAllElectrodes(
                cy_stc_capsense_context_t * context);
#endif

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN)
    static cy_en_capsense_bist_status_t Cy_CapSense_MeasureCapacitanceAllSensors(
                cy_stc_capsense_context_t * context);
#endif

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_ELTD_CAP_EN)
    static cy_en_capsense_bist_status_t Cy_CapSense_BistMeasureCapacitanceSensor(
                    uint32_t * cpPtr,
                    cy_stc_capsense_context_t * context);
#endif

#if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN) || \
    ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) && \
     (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN)))
    static cy_en_capsense_bist_status_t Cy_CapSense_BistMeasureCapacitanceSlot(
                    uint32_t slotId,
                    cy_stc_capsense_context_t * context);
#endif

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_MEASUREMENT_GROUP_EN)
    static cy_capsense_status_t Cy_CapSense_BistMeasureCapacitanceSensorEnable(
                    cy_stc_capsense_context_t * context);
    static void Cy_CapSense_BistMeasureCapacitanceSensorRun(
                    cy_stc_capsense_context_t * context);
    static void Cy_CapSense_BistGenerateBaseConfig(
                    uint32_t chIndex,
                    cy_stc_capsense_context_t * context);
    static void Cy_CapSense_BistGenerateSensorConfig(
                    uint32_t chIndex,
                    uint32_t * ptrSensorCfg,
                    cy_stc_capsense_context_t * context);

    #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
        static void Cy_CapSense_BistGenerateSnsCfgMaskReg(
                        const cy_stc_capsense_electrode_config_t * ptrEltdCfg,
                        uint32_t * ptrSensorCfg,
                        uint32_t cswFuncNum);
    #endif

    #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_ELTD_CAP_EN) && \
         (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD))
        static void Cy_CapSense_BistConnectEltd(
                        const cy_stc_capsense_electrode_config_t * ptrEltdConfig,
                        const cy_stc_capsense_context_t * context);
        static void Cy_CapSense_BistDisconnectEltd(
                        const cy_stc_capsense_electrode_config_t * ptrEltdConfig,
                        cy_en_capsense_bist_io_state_t desiredPinState,
                        const cy_stc_capsense_context_t * context);
    #endif

    static uint32_t Cy_CapSense_BistWatchdogPeriodCalc(
                    const cy_stc_capsense_context_t * context);
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_MEASUREMENT_GROUP_EN) */


/** \} \endcond */


/*******************************************************************************
* Function Name: Cy_CapSense_RunSelfTest_V3
****************************************************************************//**
*
* Runs built-in self-tests for specified by the test enable mask.
*
* The function performs various self-tests on all the enabled widgets
* and sensors in the project. Select the required set of tests
* using the bit-mask in testEnMask parameter.
*
* Use CY_CAPSENSE_BIST_RUN_AVAILABLE_SELF_TEST_MASK to execute
* all the self-tests or any combination of the masks
* (defined in testEnMask parameter) to specify the desired test list.
*
* To execute a single-element test (i.e. for one widget or one sensor),
* the following low-level functions are available:
* - Cy_CapSense_CheckCRCWidget()
* - Cy_CapSense_CheckIntegritySensorPins()
* - Cy_CapSense_MeasureCapacitanceSensorElectrode()
* - Cy_CapSense_MeasureCapacitanceSlotSensors()
* - Cy_CapSense_MeasureCapacitanceChannelsShield()
*
* Refer to these functions descriptions for detail information
* on the corresponding test.
*
* \note
* The function is available only for the fifth-generation CAPSENSE&trade;.
*
* \param testEnMask
* Specifies the tests to be executed. Each bit corresponds to one test. It is
* possible to launch the function with any combination of the available tests.
* - CY_CAPSENSE_BIST_CRC_WDGT_MASK       - Verifies the RAM widget structure CRC
*                                          for all the widgets.
* - CY_CAPSENSE_BIST_SNS_INTEGRITY_MASK  - Checks all the sensors for a short
*                                          to GND / VDD / other sensors.
* - CY_CAPSENSE_BIST_SNS_CAP_MASK        - Measures all the sensors capacitance.
* - CY_CAPSENSE_BIST_ELTD_CAP_MASK       - Measures all the electrodes capacitance.
* - CY_CAPSENSE_BIST_SHIELD_CAP_MASK     - Measures the shield capacitance.
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
cy_en_capsense_bist_status_t Cy_CapSense_RunSelfTest_V3(
                uint32_t testEnMask,
                cy_stc_capsense_context_t * context)
{
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_BAD_PARAM_E;

    if (0u == (testEnMask & (~CY_CAPSENSE_BIST_RUN_AVAILABLE_SELF_TEST_MASK)))
    {
        if(NULL != context)
        {
            if(CY_CAPSENSE_NOT_BUSY == Cy_CapSense_IsBusy(context))
            {
                result = CY_CAPSENSE_BIST_SUCCESS_E;

                #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN)
                    if (0u != (CY_CAPSENSE_BIST_CRC_WDGT_MASK & testEnMask))
                    {
                        if (CY_CAPSENSE_BIST_SUCCESS_E != Cy_CapSense_CheckAllWidgetCRC(context))
                        {
                            result = CY_CAPSENSE_BIST_FAIL_E;
                            context->ptrBistContext->testResultMask |= CY_CAPSENSE_BIST_CRC_WDGT_MASK;
                        }
                    }
                #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN) */

                #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_HW_GROUP_EN)
                    /* The next group of tests is hardware-dependent and they need to switch the configuration to BIST one */
                    if((uint32_t)CY_CAPSENSE_SUCCESS_E == Cy_CapSense_SwitchHwConfiguration(CY_CAPSENSE_HW_CONFIG_BIST_FUNCTIONALITY, context))
                    {

                        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_SHORT_EN)
                            if (0u != (CY_CAPSENSE_BIST_SNS_INTEGRITY_MASK & testEnMask))
                            {
                                if (CY_CAPSENSE_BIST_SUCCESS_E != Cy_CapSense_SnsShortCheckAllSensors(context))
                                {
                                    result = CY_CAPSENSE_BIST_FAIL_E;
                                    context->ptrBistContext->testResultMask |= CY_CAPSENSE_BIST_SNS_INTEGRITY_MASK;
                                }
                            }
                        #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_SHORT_EN) */

                        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN)
                            if (0u != (CY_CAPSENSE_BIST_SNS_CAP_MASK & testEnMask))
                            {
                                if (CY_CAPSENSE_BIST_SUCCESS_E != Cy_CapSense_MeasureCapacitanceAllSensors(context))
                                {
                                    result = CY_CAPSENSE_BIST_FAIL_E;
                                    context->ptrBistContext->testResultMask |= CY_CAPSENSE_BIST_SNS_CAP_MASK;
                                }
                            }
                        #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN) */

                        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_ELTD_CAP_EN)
                            if (0u != (CY_CAPSENSE_BIST_ELTD_CAP_MASK & testEnMask))
                            {
                                if (CY_CAPSENSE_BIST_SUCCESS_E != Cy_CapSense_MeasureCapacitanceAllElectrodes(context))
                                {
                                    result = CY_CAPSENSE_BIST_FAIL_E;
                                    context->ptrBistContext->testResultMask |= CY_CAPSENSE_BIST_ELTD_CAP_MASK;
                                }
                            }
                        #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_ELTD_CAP_EN) */

                        #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) &&\
                             (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN))
                            if ((0u != (CY_CAPSENSE_BIST_SHIELD_CAP_MASK & testEnMask)) &&
                                (CY_CAPSENSE_DISABLE != context->ptrCommonConfig->csdShieldMode))
                            {
                                if (CY_CAPSENSE_BIST_SUCCESS_E != Cy_CapSense_MeasureCapacitanceShieldElectrode(0u, context))
                                {
                                    result = CY_CAPSENSE_BIST_FAIL_E;
                                    context->ptrBistContext->testResultMask |= CY_CAPSENSE_BIST_SHIELD_CAP_MASK;
                                }
                            }
                        #endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) &&\
                                   (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN)) */
                    }
                    else
                    {
                        result = CY_CAPSENSE_BIST_ERROR_E;
                    }
                #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_HW_GROUP_EN) */
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
* Function Name: Cy_CapSense_CheckCRCWidget_V3
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
cy_en_capsense_bist_status_t Cy_CapSense_CheckCRCWidget_V3(
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
        if (CY_CAPSENSE_BIST_SUCCESS_E != (Cy_CapSense_CheckCRCWidget_V3(widgetId, context)))
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


/*******************************************************************************
* Function Name: Cy_CapSense_UpdateAllWidgetCrc
****************************************************************************//**
*
* The internal function that updates CRC of all widget structures.
*
* The function implements the following functionality:
* - Executes the Cy_CapSense_UpdateCrcWidget() for all widgets.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_UpdateAllWidgetCrc(cy_stc_capsense_context_t * context)
{
    uint32_t wdIndex;
    uint32_t wdNum = (uint32_t)context->ptrCommonConfig->numWd;

    /* Initialize CRC and status for all widgets */
    for (wdIndex = 0u; wdIndex < wdNum; wdIndex++)
    {
        Cy_CapSense_UpdateCrcWidget(wdIndex, context);
    }
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_BSLN_INTEGRITY_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_CheckIntegritySensorBaseline_V3
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
cy_en_capsense_bist_status_t Cy_CapSense_CheckIntegritySensorBaseline_V3(
                uint32_t widgetId,
                uint32_t sensorId,
                uint16_t baselineHighLimit,
                uint16_t baselineLowLimit,
                cy_stc_capsense_context_t * context)
{
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_BAD_PARAM_E;
    uint16_t bslnInv;
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

            /* Check baselines */

            cxtOffset = sensorId;
            bslnInv = (uint16_t)(~(ptrWdgtCfg->ptrBslnInv[cxtOffset]));
            if ((ptrSnsCxt->bsln != bslnInv) ||
                (ptrSnsCxt->bsln > baselineHighLimit) ||
                (ptrSnsCxt->bsln < baselineLowLimit))
            {
                context->ptrBistContext->testResultMask |= CY_CAPSENSE_BIST_BSLN_INTEGRITY_MASK;
                result = CY_CAPSENSE_BIST_FAIL_E;
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
* Function Name: Cy_CapSense_CheckIntegritySensorRawcount_V3
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
cy_en_capsense_bist_status_t Cy_CapSense_CheckIntegritySensorRawcount_V3(
                uint32_t widgetId,
                uint32_t sensorId,
                uint16_t rawcountHighLimit,
                uint16_t rawcountLowLimit,
                cy_stc_capsense_context_t * context)
{
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_BAD_PARAM_E;
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
            /* Check raw counts */
            if ((ptrSnsCxt->raw  > rawcountHighLimit) ||
                (ptrSnsCxt->raw  < rawcountLowLimit))
            {
                context->ptrBistContext->testResultMask |= CY_CAPSENSE_BIST_RAW_INTEGRITY_MASK;
                result = CY_CAPSENSE_BIST_FAIL_E;
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
* Function Name: Cy_CapSense_CheckIntegritySensorPins_V3
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
*   bit in the .status field of the \ref cy_stc_capsense_widget_context_t structure
*   of the specified widget.
*
* To check all the project sensors at once, use the Cy_CapSense_RunSelfTest()
* function with the CY_CAPSENSE_BIST_SNS_INTEGRITY_MASK mask.
*
* To detect an electrical short or fault condition with resistance
* higher than 1500 ohm, the Cy_CapSense_MeasureCapacitanceSensorElectrode() function can
* be used as the fault condition affects the measured sensor capacitance.
*
* This test can be executed only if the CAPSENSE&trade; Middleware is in the IDLE
* state. This function must not be called while CAPSENSE&trade; Middleware is busy.
*
*
* \note
* This function is available only for the fifth-generation CAPSENSE&trade;.
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
* - CY_CAPSENSE_BIST_SUCCESS_E          - Sensor pin resistances are in defined range.
* - CY_CAPSENSE_BIST_FAIL_E             - The test failed and Sensor pin resistances
*                                         are out of the defined range.
* - CY_CAPSENSE_BIST_BAD_PARAM_E        - The input parameter is invalid.
*                                         The test was not executed.
* - CY_CAPSENSE_BIST_HW_BUSY_E          - The CSD HW block is busy with a
*                                         previous operation. The function
*                                         was not executed.
*
*******************************************************************************/
cy_en_capsense_bist_status_t Cy_CapSense_CheckIntegritySensorPins_V3(
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
                if ((uint32_t)CY_CAPSENSE_SUCCESS_E == Cy_CapSense_SwitchHwConfiguration(CY_CAPSENSE_HW_CONFIG_BIST_FUNCTIONALITY, context))
                {
                    /* Switch the HW resource configuration to the sensor short test */
                    Cy_CapSense_BistSwitchHwConfig(CY_CAPSENSE_BIST_HW_SHORT_E, CY_CAPSENSE_UNDEFINED_GROUP, 0u,
                                                   context);

                    /* Set all CAPSENSE&trade; pins to strong-high */
                    Cy_CapSense_BistSwitchAllSnsPinState(CY_CAPSENSE_BIST_IO_STRONG_HIGH_E, context);
                    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
                        Cy_CapSense_BistSwitchAllShieldPinState(CY_CAPSENSE_BIST_IO_STRONG_HIGH_E, context);
                    #endif
                    Cy_CapSense_BistSwitchAllExternalCapPinState(CY_CAPSENSE_BIST_IO_STRONG_HIGH_E, context);

                    /* Wait for the maximum possible external capacitor charging time */
                    Cy_SysLib_DelayUs(context->ptrBistContext->snsIntgShortSettlingTime);

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
                    Cy_SysLib_DelayUs(context->ptrBistContext->snsIntgShortSettlingTime);

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
* Function Name: Cy_CapSense_SnsShortCheckElectrode
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
        Cy_CapSense_BistSetPinDr(ioPtr, (mode ^ 0x01u));
        Cy_CapSense_BistSetPinPc(ioPtr, eltdDM);
        /* Wait for establishing the transition process */
        Cy_SysLib_DelayUs((uint16_t)context->ptrBistContext->snsIntgShortSettlingTime);
        /* Read the electrode state */
        eltdState = Cy_GPIO_Read(ioPtr->pcPtr, (uint32_t)ioPtr->pinNumber);
        if (CY_CAPSENSE_BIST_DR_PIN2GND != eltdState)
        {
            eltdState = CY_CAPSENSE_BIST_DR_PIN2VDD;
        }
        /* Revert the electrode to the default Drive mode */
        Cy_CapSense_BistSetPinDr(ioPtr, mode);
        Cy_CapSense_BistSetPinPc(ioPtr, CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF);
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
    uint32_t numWdgtElectrodes;
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_SUCCESS_E;

    /* Previously-captured HW resources were released by the other mode in the RunSelfTest function */
    /* Switch HW resource configuration to sensor short test */
    Cy_CapSense_BistSwitchHwConfig(CY_CAPSENSE_BIST_HW_SHORT_E, CY_CAPSENSE_UNDEFINED_GROUP, 0u,
                                   context);

    Cy_CapSense_BistSwitchAllSnsPinState(CY_CAPSENSE_BIST_IO_STRONG_HIGH_E, context);
    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
        Cy_CapSense_BistSwitchAllShieldPinState(CY_CAPSENSE_BIST_IO_STRONG_HIGH_E, context);
    #endif
    Cy_CapSense_BistSwitchAllExternalCapPinState(CY_CAPSENSE_BIST_IO_STRONG_HIGH_E, context);

    /* Wait for the maximum possible external capacitor charging time */
    Cy_SysLib_DelayUs(context->ptrBistContext->snsIntgShortSettlingTime);

    for (widgetId = 0u; widgetId < context->ptrCommonConfig->numWd; widgetId++)
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

        for (sensorId = 0u; sensorId < numWdgtElectrodes; sensorId++)
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
    Cy_SysLib_DelayUs(context->ptrBistContext->snsIntgShortSettlingTime);

    for (widgetId = 0u; widgetId < context->ptrCommonConfig->numWd; widgetId++)
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

        for (sensorId = 0u; sensorId < numWdgtElectrodes; sensorId++)
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
* Function Name: Cy_CapSense_BistSetPinDr
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
static void Cy_CapSense_BistSetPinDr(
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
* Function Name: Cy_CapSense_BistSetPinPc
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
static void Cy_CapSense_BistSetPinPc(
                cy_stc_capsense_pin_config_t const *ioPtr,
                uint32_t value)
{
    uint32_t  interruptState;

    /* Update the port configuration register (Drive mode) */
    interruptState = Cy_SysLib_EnterCriticalSection();
    Cy_GPIO_SetDrivemode(ioPtr->pcPtr, (uint32_t)ioPtr->pinNumber, value);
    Cy_SysLib_ExitCriticalSection(interruptState);
}
#endif


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_HW_GROUP_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_BistSetAllSnsPinsState
****************************************************************************//**
*
* Sets all CAPSENSE&trade; pins into a desired state.
*
* Sets all the CSD/CSX IOs into a desired state.
* Default state:
* - HSIOM   - Disconnected, the GPIO mode.
* - DM      - Strong drive.
* - State   - Zero.
*
* Do not call this function directly from the application program.
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
void Cy_CapSense_BistSetAllSnsPinsState(
                uint32_t desiredDriveMode,
                uint32_t desiredPinOutput,
                en_hsiom_sel_t desiredHsiom,
                const cy_stc_capsense_context_t * context)
{
    uint32_t loopIndex;
    const cy_stc_capsense_pin_config_t * ptrPinCfg = context->ptrPinConfig;

    /* Loop through all electrodes */
    for (loopIndex = 0u; loopIndex < context->ptrCommonConfig->numPin; loopIndex++)
    {
        Cy_CapSense_SsConfigPinRegisters(ptrPinCfg->pcPtr,
            (uint32_t)ptrPinCfg->pinNumber, desiredDriveMode, desiredHsiom);

        if (0u != desiredPinOutput)
        {
            Cy_GPIO_Set(ptrPinCfg->pcPtr, (uint32_t)ptrPinCfg->pinNumber);
        }
        else
        {
            Cy_GPIO_Clr(ptrPinCfg->pcPtr, (uint32_t)ptrPinCfg->pinNumber);
        }
        /* Get next electrode */
        ptrPinCfg++;
    }
}


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_BistSetAllShieldPinsState
****************************************************************************//**
*
* Sets all shield pins into a desired state.
*
* Sets all the dedicated shield electrodes into a desired state.
* Do not call this function directly from the application program.
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
void Cy_CapSense_BistSetAllShieldPinsState(
                uint32_t desiredDriveMode,
                uint32_t desiredPinOutput,
                en_hsiom_sel_t desiredHsiom,
                const cy_stc_capsense_context_t * context)
{
    uint32_t loopIndex;
    const cy_stc_capsense_pin_config_t * ptrPinCfg = context->ptrShieldPinConfig;

    /* Loop through all electrodes */
    for (loopIndex = 0u; loopIndex < context->ptrCommonConfig->csdShieldNumPin; loopIndex++)
    {
        Cy_CapSense_SsConfigPinRegisters(ptrPinCfg->pcPtr,
            (uint32_t)ptrPinCfg->pinNumber, desiredDriveMode, desiredHsiom);

        if (0u != desiredPinOutput)
        {
            Cy_GPIO_Set(ptrPinCfg->pcPtr, (uint32_t)ptrPinCfg->pinNumber);
        }
        else
        {
            Cy_GPIO_Clr(ptrPinCfg->pcPtr, (uint32_t)ptrPinCfg->pinNumber);
        }
        /* Get next electrode */
        ptrPinCfg++;
    }
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) */


/*******************************************************************************
* Function Name: Cy_CapSense_BistSetAllCmodPinsState
****************************************************************************//**
*
* Sets all available MSC Cmod pins connected into a desired state .
*
* Sets all external capacitors connected into a desired state.
* Do not call this function directly from the application program.
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
void Cy_CapSense_BistSetAllCmodPinsState(
                uint32_t desiredDriveMode,
                uint32_t desiredPinOutput,
                en_hsiom_sel_t desiredHsiom,
                const cy_stc_capsense_context_t * context)
{
    uint32_t curChIndex;

    uint8_t cmod1Pin;
    uint8_t cmod2Pin;

    GPIO_PRT_Type * cmod1Port;
    GPIO_PRT_Type * cmod2Port;

    const cy_stc_capsense_common_config_t * ptrCommonCfg = context->ptrCommonConfig;

    /* Loop through all electrodes */
    for (curChIndex = 0u; curChIndex < CY_CAPSENSE_TOTAL_CH_NUMBER; curChIndex++)
    {
        cmod1Port = ptrCommonCfg->ptrMscChConfig[curChIndex].portCmod1;
        cmod1Pin = ptrCommonCfg->ptrMscChConfig[curChIndex].pinCmod1;

        cmod2Port = ptrCommonCfg->ptrMscChConfig[curChIndex].portCmod2;
        cmod2Pin = ptrCommonCfg->ptrMscChConfig[curChIndex].pinCmod2;

        Cy_CapSense_SsConfigPinRegisters(cmod1Port, (uint32_t)cmod1Pin, desiredDriveMode, desiredHsiom);
        Cy_CapSense_SsConfigPinRegisters(cmod2Port, (uint32_t)cmod2Pin, desiredDriveMode, desiredHsiom);

        if (0u != desiredPinOutput)
        {
            Cy_GPIO_Set(cmod1Port, (uint32_t)cmod1Pin);
        }
        else
        {
            Cy_GPIO_Clr(cmod1Port, (uint32_t)cmod1Pin);
        }

        if (0u != desiredPinOutput)
        {
            Cy_GPIO_Set(cmod2Port, (uint32_t)cmod2Pin);
        }
        else
        {
            Cy_GPIO_Clr(cmod2Port, (uint32_t)cmod2Pin);
        }
    }
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_HW_GROUP_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_ELTD_CAP_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_MeasureCapacitanceSensorElectrode
****************************************************************************//**
*
* Measures the specified CSD sensor / CSX electrode capacitance in femtofarads.
*
* This function measures the sensor capacitance for CSD widgets or the electrode
* capacitance for CSX
* widgets and returns the measurement status. For a CSX sensor, the
* measurement is done on either Rx or Tx electrode.
* For a CSD sensor, measurement is done on a sensor (refer to the
* eltdId parameter description).
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
* The default scanning parameters are the following:
* * SnsClk divider (256) is the divider for the sensor clock frequency.
* * NumConv (100) is the number of sub-conversions.
* * The reference CDAC capacitance (886 fF) is equivalent to CDAC Code of 100u.
* * The compensation CDAC is disabled.
* * The CIC2 filter is disabled.
* * The dithering is disabled.
* * The chopping is disabled.
*
* The raw count is converted into capacitance using the following equation:
*
*  Cs = Rawcount * RefCDAC capacitance / NumConv
*
* where:
* * Cs is the sensor capacitance.
* * Rawcount is the measured raw count value.
*
* The minimum measurable input by this function is 1pF and the
* maximum is either 200pF or limited by the RC time constant
* (Cs < 1 / (2*5*SnsClk*R), where R is the total sensor series
* resistance that includes on-chip GPIO resistance ~500 Ohm and
* external series resistance). The measurement accuracy is about 30% and
* is defined by the RefCDAC tolerance.
*
* By default, all CAPSENSE&trade; sensors (electrodes) that are not being
* measured are set to the GND state for CSD measured electrodes (sensors) and
* to the HIGH-Z state for CSX measured electrodes (Rx and Tx).
* Shield electrodes are also configured to the GND state.
* The inactive state can be changed in run-time by using
* the Cy_CapSense_SetInactiveElectrodeState() function.
*
* By default, the both Cmod1 and Cmod2 capacitors are used for the measurement.
*
* The sensor measurement can be done on all the electrodes using
* the Cy_CapSense_RunSelfTest() function along with
* the CY_CAPSENSE_BIST_ELTD_CAP_MASK mask.
*
* This function must not be called while the CAPSENSE&trade; MW is busy
* by another scan.
*
* \note
* This function is available only for the fifth-generation CAPSENSE&trade;.
*
* \param widgetId
* Specifies the ID number of the widget.
* A macro for the widget ID can be found in the
* CAPSENSE&trade; Configuration header file (cycfg_capsense.h) defined as
* CY_CAPSENSE_<WidgetName>_WDGT_ID.
*
* \param eltdId
* Specifies the ID of the electrode within the widget (sensorID for CSD
* widgets and Rx or Tx electrode ID for CSX widgets).
*
* For the CSD widgets, a macro for the sensor ID within the specified widget
* can be found in the CAPSENSE&trade; Configuration header file (cycfg_capsense.h)
* defined as CY_CAPSENSE_<WidgetName>_SNS<SensorNumber>_ID.
*
* For the CSX widgets, eltdId is an electrode ID and is defined as Rx ID
* or Tx ID. The first Rx in a widget corresponds to eltdId = 0, the
* second Rx in a widget corresponds to eltdId = 1, and so on.
* The last Tx in a widget corresponds to eltdId = (RxNum + TxNum - 1).
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
* - CY_CAPSENSE_BIST_SUCCESS_E          - The measurement completes
*                                         successfully, the result is valid.
* - CY_CAPSENSE_BIST_BAD_PARAM_E        - The input parameter is invalid.
*                                         The measurement was not executed.
* - CY_CAPSENSE_BIST_HW_BUSY_E          - The CSD HW block is busy with a
*                                         previous operation.
*                                         The measurement was not executed.
*
*******************************************************************************/
cy_en_capsense_bist_status_t Cy_CapSense_MeasureCapacitanceSensorElectrode(
                uint32_t widgetId,
                uint32_t eltdId,
                cy_stc_capsense_context_t * context)
{
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_BAD_PARAM_E;
    uint32_t numWdgtElectrodes;
    const cy_stc_capsense_electrode_config_t * ptrEltdCfg;

    if(NULL != context)
    {
        if ((context->ptrCommonConfig->numWd > widgetId))
        {
            /* Get the total widget electrode number: for CSX it is numRows + numCols, for CSD it is totalNumSns */
            if ((uint8_t)CY_CAPSENSE_CSX_GROUP == context->ptrWdConfig[widgetId].senseMethod)
            {
                /* For CSX widgets, get the sum of Rx and Tx electrode numbers */
                numWdgtElectrodes = context->ptrWdConfig[widgetId].numRows +
                          (uint32_t)context->ptrWdConfig[widgetId].numCols;
                context->ptrBistContext->currentISC = context->ptrBistContext->intrEltdCapCsxISC;
            }
            else
            {
                numWdgtElectrodes = context->ptrWdConfig[widgetId].numSns;
                context->ptrBistContext->currentISC = context->ptrBistContext->intrEltdCapCsdISC;
            }
            if (numWdgtElectrodes > eltdId)
            {
                if (CY_CAPSENSE_NOT_BUSY == Cy_CapSense_IsBusy(context))
                {
                    /* Set the BUSY status */
                    context->ptrCommonContext->status = CY_CAPSENSE_BUSY | CY_CAPSENSE_MW_STATE_BIST_MASK;
                    (void)Cy_CapSense_SwitchHwConfiguration(CY_CAPSENSE_HW_CONFIG_BIST_FUNCTIONALITY, context);
                    /* Find the pointer to the electrode pin configuration and the electrode channel */
                    ptrEltdCfg = &context->ptrWdConfig[widgetId].ptrEltdConfig[eltdId];
                    /* Store the necessary values to the Bist context structure */
                    context->ptrBistContext->curBistChId = ptrEltdCfg->chId;
                    context->ptrBistContext->skipChannelMask = ~(1u << ptrEltdCfg->chId);
                    context->ptrBistContext->curPtrEltdCfg = ptrEltdCfg;
                    /* Switch the HW resource configuration to the sensor element capacitance measurement */
                    Cy_CapSense_BistSwitchHwConfig(CY_CAPSENSE_BIST_HW_ELTD_CAP_E,
                                                   CY_CAPSENSE_CSD_GROUP,
                                                   CY_CAPSENSE_BIST_CAP_ELTD_SCAN,
                                                   context);
                    #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
                        Cy_CapSense_BistConnectEltd(ptrEltdCfg, context);
                    #endif
                    result = Cy_CapSense_BistMeasureCapacitanceSensor(
                                &context->ptrWdConfig[widgetId].ptrEltdCapacitance[eltdId],
                                context);
                    #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
                        Cy_CapSense_BistDisconnectEltd(ptrEltdCfg, context->ptrBistContext->currentISC, context);
                    #endif
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
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_ELTD_CAP_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_MeasureCapacitanceAllSensors
****************************************************************************//**
*
* This internal function measures all the sensor capacitances
* (Cp for CSD sensors and Cm for CSX sensors).
*
* This function measures capacitances of all the sensors by using the
* Cy_CapSense_MeasureCapacitanceSlotSensors() function.
* The function stores sensor capacitance values in femtofarads
* in the snsCap array defined
* in the cycfg_capsense.c file. The pointer to the first element of the snsCap
* array that contains the widget sensor capacitances is stored
* in the .ptrSnsCapacitance field of the cy_stc_capsense_widget_config_t
* structure.
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
static cy_en_capsense_bist_status_t Cy_CapSense_MeasureCapacitanceAllSensors(
                cy_stc_capsense_context_t * context)
{
    uint32_t slotId;
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_SUCCESS_E;

    /* Loop through all the slots */
    for (slotId = 0u; slotId < CY_CAPSENSE_SLOT_COUNT; slotId++)
    {
        if (CY_CAPSENSE_BIST_SUCCESS_E != Cy_CapSense_MeasureCapacitanceSlotSensors(slotId, 0u, context))
        {
            if (CY_CAPSENSE_BIST_SUCCESS_E == result)
            {
                result = CY_CAPSENSE_BIST_FAIL_E;
            }
        }
    }

    return (result);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_ELTD_CAP_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_MeasureCapacitanceAllElectrodes
****************************************************************************//**
*
* This internal function measures all the electrodes (sensor for CSD widgets and
* Rx/Tx electrodes for CSX widgets) parasitic capacitance (Cp).
*
* This function measures Cp of all the electrodes by using the
* Cy_CapSense_MeasureCapacitanceSensorElectrode() function.
* The function stores the Cp values in femtofarads in the eltdCap array defined
* in the cycfg_capsense.c file. The pointer to the first element of the eltdCap
* array that contains the widget electrode capacitances is stored
* in the .ptrEltdCapacitance field of the cy_stc_capsense_widget_config_t
* structure.
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
static cy_en_capsense_bist_status_t Cy_CapSense_MeasureCapacitanceAllElectrodes(
                cy_stc_capsense_context_t * context)
{
    uint32_t widgetId;
    uint32_t electrodeId;
    uint32_t numWdgtElectrodes;
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
        for (electrodeId = 0u; electrodeId < numWdgtElectrodes; electrodeId++)
        {
            if (CY_CAPSENSE_BIST_SUCCESS_E != Cy_CapSense_MeasureCapacitanceSensorElectrode(widgetId, electrodeId, context))
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
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_ELTD_CAP_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_MeasureCapacitanceSlotSensors
****************************************************************************//**
*
* Measures the specified slot sensor capacitance in femtofarads. The function
* measures the Cp capacitance for CSD widgets and the Cm capacitance
* for CSX widgets.
*
* This function performs BIST slot scan with predefined parameters,
* back-calculates the slot sensor capacitances (Cp for CSD and Cm for CSX)
* by using the raw-count equation, stores the calculated capacitances
* to the sensor context structure, and returns the measurement status.
* If the specified slot has a ganged sensor, the capacitance
* is measured for all the pins ganged together that belong to this sensor.
*
* Besides the sensor capacitance measuring, this function could be
* used to identify various fault conditions with sensors such
* as electrically-opened or -shorted sensors. For example, the PCB track is
* broken or shorted to other nodes in the system - in all of these conditions,
* the function returns changed capacitance which can be compared
* against predetermined capacitance for the sensor to detect a
* fault condition.
*
* The sensor capacitance is measured independently of the sensor regular scan
* configuration. For the capacitance measurement, the BIST specific scan
* parameters are used. They can be found in the Electrode capacitance measurement
* macros group.
* The CDAC code for the CSD sensors is 100u and that provides about 0.886 pF
* of the CDAC value and for CSX sensors the CDAC code is 50u (0.443 pF).
* Compensation CDAC is disabled during the BIST scan.
* Another default scanning parameters are the following:
* * NumConv (100) is the number of sub-conversions.
* * SnsClk divider (256) is the divider for the sensor clock frequency.
*
* The raw count is converted into capacitance using the following equation:
*
*  Cs = Rawcount * CDAC / 2 / NumConv / 2
*
* where:
* * Cs is the sensor capacitance.
* * Rawcount is the measured raw count value.
* * The first divider of 2 is determined by the divided ref_clk frequency usage.
* * The second divider of 2 is used only for CSX sensors.
*
* The minimum measurable input by this function is 0.5 pF and the
* maximum is either 200pF or limited by the RC time constant
* (Cs < 1 / (2*10*SnsClk*R), where R is the total sensor series
* resistance that includes on-chip pin resistance ~500 Ohm and
* external series resistance). The measurement accuracy is about 30%.
*
* By default, all CAPSENSE&trade; sensors (electrodes) that are not being
* measured are set to the GND state for CSD measured electrodes (sensors) and
* to the HIGH-Z state for CSX measured electrodes (Rx and Tx).
* Shield electrodes are also configured to the GND state.
* The inactive state can be changed in run-time by using
* the Cy_CapSense_SetInactiveElectrodeState() function.
*
* By default, the both Cmod1 and Cmod2 capacitors are used for the measurement.
*
* Measured capacitance values (Cp for CSD widgets and Cm for CSX widgets)
* are stored in the .snsCap field of the \ref cy_stc_capsense_sensor_context_t
* structure.
*
* The all sensor measurement can be done on all the sensors using
* the Cy_CapSense_RunSelfTest() function along with
* the CY_CAPSENSE_BIST_SNS_CAP_MASK mask.
*
* This function must not be called while the CAPSENSE&trade; MW is busy
* by another scan.
*
* \note
* This function is available only for the fifth-generation CAPSENSE&trade;.
*
* \param slotId
* Specifies the ID number of the slot to measure sensor capacitance.
* The slot ID should be in the admissible range.
*
* \param skipChMask
* Specifies the mask to skip some channels during the slot sensor capacitance
* measurement. If the bit N in the skipChMask is set to 1, the channel N
* will be excluded from measuring and all its pins will be set to the inactive
* sensor connection state (see the .eltdCapCsdISC field
* of the \ref cy_stc_capsense_bist_context_t structure for CSD widgets
* and the .eltdCapCsxISC field respectively for CSX widgets).
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
* - CY_CAPSENSE_BIST_ERROR_E            - An unexpected fault occurred during
*                                         the measurement.
*
*******************************************************************************/
cy_en_capsense_bist_status_t Cy_CapSense_MeasureCapacitanceSlotSensors(
                uint32_t slotId,
                uint32_t skipChMask,
                cy_stc_capsense_context_t * context)
{
    #if (CY_CAPSENSE_TOTAL_CH_NUMBER > 1u)
        uint32_t i;
    #endif

    uint32_t wdIndex;
    uint32_t snsIndex;
    uint32_t curChIndex;
    uint32_t curSlotIndex;
    uint32_t scanSlotIndexValid;
    const cy_stc_capsense_common_config_t * ptrCommonCfg;
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_BAD_PARAM_E;

    if(NULL != context)
    {
        if (CY_CAPSENSE_SLOT_COUNT > slotId)
        {
            if (CY_CAPSENSE_NOT_BUSY == Cy_CapSense_IsBusy(context))
            {
                ptrCommonCfg = context->ptrCommonConfig;

                /* Set the BUSY status */
                context->ptrCommonContext->status = CY_CAPSENSE_BUSY | CY_CAPSENSE_MW_STATE_BIST_MASK;
                (void)Cy_CapSense_SwitchHwConfiguration(CY_CAPSENSE_HW_CONFIG_BIST_FUNCTIONALITY, context);
                /* Set the slot measurement mode for the BIST scan */
                context->ptrBistContext->eltdCapScanMode = CY_CAPSENSE_BIST_CAP_SLOT_SCAN;
                /* Store the current slot and the skip channel mask for the BIST scan */
                context->ptrBistContext->curBistSlotId = (uint16_t)slotId;
                context->ptrBistContext->skipChannelMask = (uint8_t)skipChMask;
                /* Initialize active scan structure for BIST scan */
                for (curChIndex = 0u; curChIndex < CY_CAPSENSE_TOTAL_CH_NUMBER; curChIndex++)
                {
                    Cy_CapSense_SetBusyFlags(curChIndex, context);
                    curSlotIndex = slotId + ((curChIndex + ptrCommonCfg->channelOffset) * CY_CAPSENSE_SLOT_COUNT);
                    scanSlotIndexValid = curSlotIndex;
                    wdIndex = context->ptrScanSlots[curSlotIndex].wdId;
                    if(CY_CAPSENSE_SLOT_EMPTY == wdIndex)
                    {
                        #if (CY_CAPSENSE_TOTAL_CH_NUMBER > 1u)
                            for (i = 0u; i < CY_CAPSENSE_TOTAL_CH_NUMBER; i++)
                            {
                                /* Seek for the real sensor's slot index (not empty, not Tx only, not shield) */
                                if (CY_CAPSENSE_SLOT_SHIELD_ONLY >
                                    context->ptrScanSlots[slotId + ((i + ptrCommonCfg->channelOffset)
                                                                    * CY_CAPSENSE_SLOT_COUNT)].wdId)
                                {
                                    scanSlotIndexValid = slotId + ((i + ptrCommonCfg->channelOffset)
                                                                   * CY_CAPSENSE_SLOT_COUNT);
                                    break;
                                }
                            }
                            if (i == CY_CAPSENSE_TOTAL_CH_NUMBER)
                            {
                                result = CY_CAPSENSE_BIST_BAD_CONFIG_E;
                            }
                        #else
                            result = CY_CAPSENSE_BIST_BAD_CONFIG_E;
                        #endif /* (CY_CAPSENSE_TOTAL_CH_NUMBER > 1u) */
                    }
                    else if (CY_CAPSENSE_SLOT_SHIELD_ONLY <= wdIndex)
                    {
                        /* The snsId field keeps the channel number of the valid slot for Tx only slots */
                        scanSlotIndexValid = ((uint32_t)context->ptrScanSlots[curSlotIndex].snsId * CY_CAPSENSE_SLOT_COUNT) +
                                             slotId;
                    }
                    else
                    {
                        scanSlotIndexValid = curSlotIndex;
                    }
                    if (CY_CAPSENSE_BIST_BAD_CONFIG_E != result)
                    {
                        /* Initializes for each channel the active sensor structure for the current sensor */
                        wdIndex = context->ptrScanSlots[scanSlotIndexValid].wdId;
                        snsIndex = context->ptrScanSlots[scanSlotIndexValid].snsId;
                        Cy_CapSense_InitActivePtr(curChIndex, wdIndex, snsIndex, context);
                    }
                }
                if (CY_CAPSENSE_BIST_BAD_CONFIG_E != result)
                {
                    /* Define the current ISC for BIST scan.
                     * The CSD or CSX group is the same for all slot sensors, choose the #0u channel
                     */
                    if (CY_CAPSENSE_CSD_GROUP == context->ptrActiveScanSns[0u].currentSenseMethod)
                    {
                        context->ptrBistContext->currentISC = context->ptrBistContext->intrEltdCapCsdISC;
                        #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
                            context->ptrInternalContext->csdInactiveSnsDm = CY_CAPSENSE_DM_GPIO_ANALOG;
                            context->ptrInternalContext->csdInactiveSnsHsiom = CY_CAPSENSE_HSIOM_SEL_GPIO;
                            /* Change Drive mode and HSIOM depending on the current inactive sensor connection */
                            if (CY_CAPSENSE_BIST_IO_STRONG_E == context->ptrBistContext->currentISC)
                            {
                                context->ptrInternalContext->csdInactiveSnsDm = CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF;
                            }
                            else if (CY_CAPSENSE_BIST_IO_HIGHZA_E == context->ptrBistContext->currentISC)
                            {
                                /* Do nothing */
                            }
                            else if (CY_CAPSENSE_BIST_IO_SHIELD_E == context->ptrBistContext->currentISC)
                            {
                                context->ptrInternalContext->csdInactiveSnsDm = CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF;
                                context->ptrInternalContext->csdInactiveSnsHsiom = CY_CAPSENSE_HSIOM_SEL_CSD_SHIELD;
                            }
                            else
                            {
                                /* Do nothing */
                            }
                        #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD) */
                    }
                    else
                    {
                        context->ptrBistContext->currentISC = context->ptrBistContext->intrEltdCapCsxISC;
                        #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
                            context->ptrInternalContext->csxInactiveSnsDm = CY_CAPSENSE_DM_GPIO_ANALOG;
                            context->ptrInternalContext->csxInactiveSnsHsiom = CY_CAPSENSE_HSIOM_SEL_GPIO;
                            /* Change Drive mode and HSIOM depending on the current inactive sensor connection */
                            if (CY_CAPSENSE_BIST_IO_STRONG_E == context->ptrBistContext->currentISC)
                            {
                                context->ptrInternalContext->csxInactiveSnsDm = CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF;
                            }
                        #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD) */
                    }
                    /* Switch the HW resource configuration to the sensor element capacitance measurement */
                    Cy_CapSense_BistSwitchHwConfig(CY_CAPSENSE_BIST_HW_ELTD_CAP_E,
                                                   context->ptrActiveScanSns[0u].currentSenseMethod,
                                                   CY_CAPSENSE_BIST_CAP_SLOT_SCAN,
                                                   context);
                    #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
                        for (curChIndex = 0u; curChIndex < context->ptrCommonConfig->numChannels; curChIndex++)
                        {
                            if (((0x01uL << curChIndex) & skipChMask) == 0u)
                            {
                                curSlotIndex = slotId + ((curChIndex + ptrCommonCfg->channelOffset) * CY_CAPSENSE_SLOT_COUNT);
                                if((context->ptrScanSlots[curSlotIndex].wdId != CY_CAPSENSE_SLOT_EMPTY) &&
                                   (context->ptrScanSlots[curSlotIndex].wdId != CY_CAPSENSE_SLOT_SHIELD_ONLY))
                                   {
                                       Cy_CapSense_ConnectSensor(curChIndex, context);
                                   }
                            }
                        }
                    #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD) */
                    result = Cy_CapSense_BistMeasureCapacitanceSlot(slotId, context);
                    #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
                        for (curChIndex = 0u; curChIndex < context->ptrCommonConfig->numChannels; curChIndex++)
                        {
                            if (((0x01uL << curChIndex) & skipChMask) == 0u)
                            {
                                curSlotIndex = slotId + ((curChIndex + ptrCommonCfg->channelOffset) * CY_CAPSENSE_SLOT_COUNT);
                                if((context->ptrScanSlots[curSlotIndex].wdId != CY_CAPSENSE_SLOT_EMPTY) &&
                                   (context->ptrScanSlots[curSlotIndex].wdId != CY_CAPSENSE_SLOT_SHIELD_ONLY))
                                   {
                                       Cy_CapSense_DisconnectSensor(curChIndex, context);
                                   }
                            }
                        }
                    #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD) */
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
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_MEASUREMENT_GROUP_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_BistMeasureCapacitanceSensorEnable
****************************************************************************//**
*
* The internal function sets up the MSC HW block to perform electrode
* (sensor or shield) capacitance measuring.
*
* This function prepares the MSC HW block to CSD FW sensing mode
* with BIST-defined parameters.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static cy_capsense_status_t Cy_CapSense_BistMeasureCapacitanceSensorEnable(
                cy_stc_capsense_context_t * context)
{
    cy_en_msc_status_t mscStatus;
    cy_capsense_status_t capStatus = CY_CAPSENSE_STATUS_SUCCESS;
    uint32_t curChIndex;
    const cy_stc_msc_base_config_t cy_capsense_BistBaseTemplate = CY_CAPSENSE_BIST_SENSING_METHOD_BASE_TEMPLATE;

    /* Set the modClk divider for BIST scans */
    Cy_CapSense_SetModClkDivider(context->ptrBistContext->eltdCapModClk, context);
    /* Generate the MSC base configuration for BIST scan and send it to the MSC HW block */
    for (curChIndex = 0u; curChIndex < CY_CAPSENSE_TOTAL_CH_NUMBER; curChIndex++)
    {
        mscStatus = Cy_MSC_Configure(context->ptrCommonConfig->ptrMscChConfig[curChIndex].ptrMscBase,
                                     &cy_capsense_BistBaseTemplate, CY_MSC_CAPSENSE_KEY,
                                     context->ptrCommonConfig->ptrMscChConfig[curChIndex].ptrMscContext);
        if (CY_MSC_SUCCESS != mscStatus)
        {
            capStatus = CY_CAPSENSE_STATUS_HW_BUSY;
            break;
        }
        Cy_CapSense_BistGenerateBaseConfig(curChIndex, context);
    }
    /* Check if all MSC channel is not busy and clear all pending interrupts */
    if (CY_CAPSENSE_STATUS_SUCCESS == capStatus)
    {
        for (curChIndex = 0u; curChIndex < CY_CAPSENSE_TOTAL_CH_NUMBER; curChIndex++)
        {
            /* Clear all pending interrupts of the MSC HW block */
            context->ptrCommonConfig->ptrMscChConfig[curChIndex].ptrMscBase->INTR =
                                 CY_CAPSENSE_MSC_INTR_ALL_MSK;
            (void)context->ptrCommonConfig->ptrMscChConfig[curChIndex].ptrMscBase->INTR;
        }
    }

    return (capStatus);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_MEASUREMENT_GROUP_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_ELTD_CAP_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_BistMeasureCapacitanceSensor
****************************************************************************//**
*
* This internal function measures a capacitance attached to AMUXBUS.
*
* The function measures Cp of a certain electrode (CSD sensor or CSX
* Rx/Tx electrode) by using CSD FW mode and defined scan configuration,
* sense clock frequency and resolution.
* The range for sensor measuring is 1 to 200 pF.
* The function performs the CSD scan with the fixed CDAC value. This provides
* a possibility of classical raw counts formula usage for the capacitance
* calculation. The function stores the Cp value
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
* - CY_CAPSENSE_BIST_SUCCESS_E - The measurement is completed
*                                successfully, the result is valid.
* - CY_CAPSENSE_BIST_TIMEOUT_E - The scan reached the timeout. It can be caused
*                                by a measured capacitance short or HW block
*                                failure or invalid configuration. You may need
*                                to repeat the measurement after the issue fix.
*
*******************************************************************************/
static cy_en_capsense_bist_status_t Cy_CapSense_BistMeasureCapacitanceSensor(
                uint32_t * cpPtr,
                cy_stc_capsense_context_t * context)
{
    uint64_t cp;
    uint32_t watchdogPeriod;
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_TIMEOUT_E;
    const cy_stc_capsense_common_config_t * ptrCommonCfg = context->ptrCommonConfig;
    uint32_t rawCountTmp;
    uint32_t chIndex;

    /* Setup scan parameters: Ref CDAC code for Cp measurement */
    context->ptrBistContext->eltdCapRefCdac = CY_CAPSENSE_BIST_ELTD_CAP_REF_CDAC_DEFAULT;
    /* Perform BIST scan */
    Cy_CapSense_BistMeasureCapacitanceSensorRun(context);
    watchdogPeriod = Cy_CapSense_BistWatchdogPeriodCalc(context);
    /* Wait for the end of scan and get the raw count */
    while (((ptrCommonCfg->ptrMscChConfig[context->ptrBistContext->curBistChId].ptrMscBase->INTR &
            MSC_INTR_MASK_SCAN_Msk) == 0u) && (0u != watchdogPeriod))
    {
        watchdogPeriod--;
    }
    if (0u != watchdogPeriod)
    {
        rawCountTmp =
            ptrCommonCfg->ptrMscChConfig[context->ptrBistContext->curBistChId].ptrMscBase->RESULT_FIFO_RD;
        result = CY_CAPSENSE_BIST_SUCCESS_E;
    }
    /* Clear all pending interrupts of all MSC HW blocks */
    for (chIndex = 0u; chIndex < CY_CAPSENSE_TOTAL_CH_NUMBER; chIndex++)
    {
        ptrCommonCfg->ptrMscChConfig[chIndex].ptrMscBase->INTR = CY_CAPSENSE_MSC_INTR_ALL_MSK;
        (void)ptrCommonCfg->ptrMscChConfig[chIndex].ptrMscBase->INTR;
    }
    /* Check for timeout and if no, then calculate capacitance and store the value to the data structure */
    if ((CY_CAPSENSE_BIST_TIMEOUT_E != result))
    {
        cp = (uint64_t)CY_CAPSENSE_BIST_CAP_MEAS_CDAC_LSB_FF_DIV_1000 * context->ptrBistContext->eltdCapRefCdac;
        cp *= rawCountTmp;
        cp /= CY_CAPSENSE_CONVERSION_KILO;
        cp /= context->ptrBistContext->eltdCapSubConvNum;
        if (((uint64_t)CY_CAPSENSE_BIST_CP_MAX_VALUE) < cp)
        {
            cp = (uint64_t)CY_CAPSENSE_BIST_CP_MAX_VALUE;
        }
        *cpPtr = (uint32_t)cp;
    }

    return (result);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_ELTD_CAP_EN_EN) */


#if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN) || \
    ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) && \
     (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN)))
/*******************************************************************************
* Function Name: Cy_CapSense_BistMeasureCapacitanceSlot
****************************************************************************//**
*
* This internal function measures slot sensor capacitances.
*
* The function measures Cp of a certain CSD sensor or shield
* or Cm of a certain CSX sensor by using the predefined scan configuration.
* The range for sensor measuring is 1 to 200 pF for CSD/CSX sensors and
* 1600 pF for shield electrodes.
* The function performs the CSD or CSX scan with fixed reference CDAC values
* (100u and 50u respectively) and 200u for shield electrodes' capacitance
* measurements. The function stores the Cp or Cm value
* in the corresponding element
* of the cy_capsense_snsCap[CY_CAPSENSE_SENSOR_COUNT] array and
* Cshield values for each channel
* in the corresponding element
* of the cy_capsense_shieldCap[CY_CAPSENSE_TOTAL_CH_NUMBER] array.
* The pointer to the first sensor capacitance value of a widget is
* in the .ptrSnsCapacitance field of the \ref cy_stc_capsense_widget_config_t
* structure.
*
* \param slotId
* Specifies the ID number of the slot to measure sensor capacitance.
* The slot ID should be in the admissible range.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E - The measurement completes
*                              successfully, the result is valid.
* - CY_CAPSENSE_BIST_BAD_PARAM_E - The input parameter is invalid.
* - CY_CAPSENSE_BIST_TIMEOUT_E - The scan reached the timeout. It can be caused
*                              by a measured capacitance short or CSD HW block
*                              failure or invalid configuration. You may need to
*                              repeat the measurement after the issue fix.
*
*******************************************************************************/
static cy_en_capsense_bist_status_t Cy_CapSense_BistMeasureCapacitanceSlot(
                uint32_t slotId,
                cy_stc_capsense_context_t * context)
{
    uint64_t cp;
    uint32_t watchdogPeriod;
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_TIMEOUT_E;
    const cy_stc_capsense_common_config_t * ptrCommonCfg = context->ptrCommonConfig;
    uint32_t * ptrSnsCap;
    uint32_t rawCountTmp;
    uint32_t chIndex;
    uint32_t slotStcIdx;
    uint32_t wdgtIdx;
    uint32_t snsIdx;

    /* Setup scan parameters: Ref CDAC code for shield or electrode Cp measurement */
    if (CY_CAPSENSE_BIST_CAP_SHIELD_SCAN == context->ptrBistContext->eltdCapScanMode)
    {
        context->ptrBistContext->eltdCapRefCdac = CY_CAPSENSE_BIST_SHIELD_CAP_REF_CDAC_DEFAULT;
    }
    /* The CSD or CSX group is the same for all slot sensors, choose the group by the #0u channel */
    else if (CY_CAPSENSE_CSX_GROUP == context->ptrActiveScanSns[0u].currentSenseMethod)
    {
        context->ptrBistContext->eltdCapRefCdac = CY_CAPSENSE_BIST_MUTUAL_CAP_REF_CDAC_DEFAULT;
    }
    else
    {
        context->ptrBistContext->eltdCapRefCdac = CY_CAPSENSE_BIST_ELTD_CAP_REF_CDAC_DEFAULT;
    }
    /* Perform BIST scan */
    Cy_CapSense_BistMeasureCapacitanceSensorRun(context);
    for (chIndex = 0u; chIndex < CY_CAPSENSE_TOTAL_CH_NUMBER; chIndex++)
    {
        watchdogPeriod = Cy_CapSense_BistWatchdogPeriodCalc(context);
        result = CY_CAPSENSE_BIST_TIMEOUT_E;
        /* Wait for the end of scan and get the raw count */
        while (((ptrCommonCfg->ptrMscChConfig[chIndex].ptrMscBase->INTR & MSC_INTR_MASK_SCAN_Msk) == 0u) &&
                (0u != watchdogPeriod))
        {
            watchdogPeriod--;
        }
        if (0u != watchdogPeriod)
        {
            rawCountTmp = ptrCommonCfg->ptrMscChConfig[chIndex].ptrMscBase->RESULT_FIFO_RD;
            result = CY_CAPSENSE_BIST_SUCCESS_E;
        }
        /* Clear all pending interrupts of the current MSC HW block */
        ptrCommonCfg->ptrMscChConfig[chIndex].ptrMscBase->INTR = CY_CAPSENSE_MSC_INTR_ALL_MSK;
        (void)ptrCommonCfg->ptrMscChConfig[chIndex].ptrMscBase->INTR;
        /* Check for timeout and if no, then calculate capacitance and store the value to the data structure */
        if (CY_CAPSENSE_BIST_TIMEOUT_E != result)
        {
            if (CY_CAPSENSE_BIST_CAP_SHIELD_SCAN != context->ptrBistContext->eltdCapScanMode)
            {
                /* Get the slot index in the slot structure for the current channel */
                slotStcIdx = slotId + ((chIndex + ptrCommonCfg->channelOffset) * CY_CAPSENSE_SLOT_COUNT);
                wdgtIdx = context->ptrScanSlots[slotStcIdx].wdId;
            }
            if ((0u == ((1u << (chIndex + context->ptrCommonConfig->channelOffset)) &
                        context->ptrBistContext->skipChannelMask)) &&
                ((CY_CAPSENSE_BIST_CAP_SHIELD_SCAN == context->ptrBistContext->eltdCapScanMode) ||
                 (CY_CAPSENSE_SLOT_SHIELD_ONLY > wdgtIdx)))
            {
                cp = (uint64_t)CY_CAPSENSE_BIST_CAP_MEAS_CDAC_LSB_FF_DIV_1000 * context->ptrBistContext->eltdCapRefCdac;
                cp *= rawCountTmp;
                cp /= CY_CAPSENSE_CONVERSION_KILO;
                cp /= context->ptrBistContext->eltdCapSubConvNum;
                /* Divide the result by 2 for the FW CSX scanning method */
                if ((CY_CAPSENSE_BIST_CAP_SHIELD_SCAN != context->ptrBistContext->eltdCapScanMode) &&
                    (CY_CAPSENSE_CSX_GROUP == context->ptrActiveScanSns[0u].currentSenseMethod))
                {
                    cp /= CY_CAPSENSE_DIVIDER_TWO;
                }
            }
            else
            {
                cp = 0u;
            }
            /* Store the Cp value in the appropriate structure */
            if ((CY_CAPSENSE_BIST_CAP_SHIELD_SCAN != context->ptrBistContext->eltdCapScanMode) &&
                (CY_CAPSENSE_SLOT_SHIELD_ONLY > wdgtIdx))
            {
                snsIdx = context->ptrScanSlots[slotStcIdx].snsId;
                ptrSnsCap = &context->ptrWdConfig[wdgtIdx].ptrSnsCapacitance[snsIdx];
                if (((uint64_t)CY_CAPSENSE_BIST_CP_MAX_VALUE) < cp)
                {
                    cp = (uint64_t)CY_CAPSENSE_BIST_CP_MAX_VALUE;
                }
                *ptrSnsCap = (uint32_t)cp;
            }
            else if (CY_CAPSENSE_BIST_CAP_SHIELD_SCAN == context->ptrBistContext->eltdCapScanMode)
            {
                ptrSnsCap = &context->ptrBistContext->ptrChShieldCap[chIndex];
                if (((uint64_t)CY_CAPSENSE_BIST_CSH_MAX_VALUE) < cp)
                {
                    cp = (uint64_t)CY_CAPSENSE_BIST_CSH_MAX_VALUE;
                }
                *ptrSnsCap = (uint32_t)cp;
            }
            else
            {
                /* Do nothing */
            }
        }
        else
        {
            break;
        }
    }

    return (result);
}
#endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_CAP_EN) || \
          ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) && \
           (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN))) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_MEASUREMENT_GROUP_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_BistMeasureCapacitanceSensorRun
****************************************************************************//**
*
* This internal function performs the scan initialization
* and triggers the scan for the sensor or shield electrode capacitance measurement.
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
static void Cy_CapSense_BistMeasureCapacitanceSensorRun(
                cy_stc_capsense_context_t * context)
{
    const cy_stc_capsense_common_config_t * ptrCommonCfg = context->ptrCommonConfig;
    MSC_Type * ptrMscHwBase;
    uint32_t chIndex;
    uint32_t sensorFrame[CY_MSC_6_SNS_REGS];

    #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
        /* Connect Cmods to the AMUX-BusA in the AMUX mode */
        for (chIndex = 0u; chIndex < CY_CAPSENSE_TOTAL_CH_NUMBER; chIndex++)
        {
            Cy_CapSense_SsConfigPinRegisters(
            context->ptrCommonConfig->ptrMscChConfig[chIndex].portCmod1,
            (uint32_t)context->ptrCommonConfig->ptrMscChConfig[chIndex].pinCmod1,
            CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_HSIOM_SEL_AMUXA);

            Cy_CapSense_SsConfigPinRegisters(
            context->ptrCommonConfig->ptrMscChConfig[chIndex].portCmod2,
            (uint32_t)context->ptrCommonConfig->ptrMscChConfig[chIndex].pinCmod2,
            CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_HSIOM_SEL_AMUXA);
        }
    #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD) */

    /* Initiate the frame start for all channels */
    for (chIndex = 0u; chIndex < CY_CAPSENSE_TOTAL_CH_NUMBER; chIndex++)
    {
        /* Get the pointer to the MSC channel base register */
        ptrMscHwBase = ptrCommonCfg->ptrMscChConfig[chIndex].ptrMscBase;
        ptrMscHwBase->FRAME_CMD = MSC_FRAME_CMD_START_FRAME_Msk;
    }
    for (chIndex = 0u; chIndex < CY_CAPSENSE_TOTAL_CH_NUMBER; chIndex++)
    {
        /* Get the pointer to the MSC channel base register */
        ptrMscHwBase = ptrCommonCfg->ptrMscChConfig[chIndex].ptrMscBase;
        /* Clear the sensor configuration structure */
        (void)memset(&sensorFrame[0u], 0, sizeof(cy_stc_msc_sensor_config_t));
        /* Get the sensor frame configuration and write it to the MSC HW block to start scan */
        Cy_CapSense_BistGenerateSensorConfig(chIndex, &sensorFrame[0u], context);
        Cy_MSC_ConfigureScan(ptrMscHwBase, CY_MSC_6_SNS_REGS, &sensorFrame[0u]);
    }
}


/*******************************************************************************
* Function Name: Cy_CapSense_BistGenerateBaseConfig
****************************************************************************//**
*
* Changes the configuration for all registers that have to be changed
* one-time to initialize the MSC block for BIST scan.
*
* \param chIndex
* The channel index the base configuration is generated for.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the operation:
* - CY_CAPSENSE_STATUS_SUCCESS       - The operation is performed successfully.
*
*******************************************************************************/
static void Cy_CapSense_BistGenerateBaseConfig(
                uint32_t chIndex,
                cy_stc_capsense_context_t * context)
{
    uint32_t i;
    MSC_Type * ptrBaseCfg = context->ptrCommonConfig->ptrMscChConfig[chIndex].ptrMscBase;
    MSC_MODE_Type * ptrBaseCfgMode;
    const cy_stc_msc_channel_config_t * ptrMscChConfig = &context->ptrCommonConfig->ptrMscChConfig[chIndex];

    #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
        uint32_t cswFuncMode = 0uL;
        const cy_stc_capsense_pin_config_t * ptrPinCfg = context->ptrPinConfig;
    #endif

    if((CY_CAPSENSE_MSC0_CMOD1PADD_PIN != ptrMscChConfig->pinCmod1) &&
       (CY_CAPSENSE_MSC1_CMOD1PADD_PIN != ptrMscChConfig->pinCmod1))
    {
        ptrBaseCfg->SW_SEL_CMOD1 = 0u;
        ptrBaseCfg->SW_SEL_CMOD2 = 0u;
    }
    else
    {
        ptrBaseCfg->SW_SEL_CMOD3 = 0u;
        ptrBaseCfg->SW_SEL_CMOD4 = 0u;
    }

    /* Set the GPIO configuration for AMUX mode */
    #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)

        ptrBaseCfg->SW_SEL_GPIO &= ~CY_CAPSENSE_CMOD_AMUX_MSK;
        if ((CY_CAPSENSE_BIST_CAP_SLOT_SCAN == context->ptrBistContext->eltdCapScanMode) &&
            (CY_CAPSENSE_CSX_GROUP == context->ptrActiveScanSns[0u].currentSenseMethod))
        {
            ptrBaseCfg->SW_SEL_GPIO |= CY_CAPSENSE_FW_CMOD_AMUX_CSX_REG_SW_SEL_GPIO_VALUE;
        }
        else
        {
            ptrBaseCfg->SW_SEL_GPIO |= CY_CAPSENSE_FW_CMOD_AMUX_CSD_REG_SW_SEL_GPIO_VALUE;
        }

        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
            /* The shield signal generation for BIST scans in AMUX mode */
            if (CY_CAPSENSE_BIST_IO_SHIELD_E == context->ptrBistContext->intrEltdCapCsdISC)
            {
                if (CY_CAPSENSE_SHIELD_ACTIVE == context->ptrCommonConfig->csdShieldMode)
                {
                    ptrBaseCfg->SW_SEL_GPIO |= CY_CAPSENSE_FW_SHIELD_ACTIVE_AMUX_REG_SW_CSD_SHIELD_VALUE;
                }
                else if (CY_CAPSENSE_SHIELD_PASSIVE == context->ptrCommonConfig->csdShieldMode)
                {
                    ptrBaseCfg->SW_SEL_GPIO |= CY_CAPSENSE_FW_SHIELD_PASSIVE_AMUX_REG_SW_CSD_SHIELD_VALUE;
                }
                else
                {
                    /* Do nothing */
                }
            }
        #endif
    #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD) */

    /*
     * MODE CONFIGURATION
     * For the BIST electrode capacitance measurement the CSD FW is used, the mode #0)
     * For the BIST slot sensor capacitance measurement the CSD FW (the mode #0) and CSX FW (the mode #1) are used
     */
    for (i = 0u; i < CY_CAPSENSE_BIST_SENSE_MODE_CONFIG_NUMBER; i++)
    {
        ptrBaseCfg->MODE[i].SW_SEL_SH &= (~MSC_MODE_SW_SEL_SH_C1SHG_Msk);
        ptrBaseCfg->MODE[i].SW_SEL_SH &= (~MSC_MODE_SW_SEL_SH_C3SHG_Msk);

        if((CY_CAPSENSE_MSC0_CMOD1PADD_PIN == ptrMscChConfig->pinCmod1) ||
           (CY_CAPSENSE_MSC1_CMOD1PADD_PIN == ptrMscChConfig->pinCmod1))
        {
            ptrBaseCfg->MODE[i].SW_SEL_COMP |= MSC_MODE_SW_SEL_COMP_CPCS1_Msk;
            ptrBaseCfg->MODE[i].SW_SEL_COMP |= MSC_MODE_SW_SEL_COMP_CMCS2_Msk;
            ptrBaseCfg->MODE[i].SW_SEL_SH |= MSC_MODE_SW_SEL_SH_C1SHG_Msk;
        }
        else
        {
            ptrBaseCfg->MODE[i].SW_SEL_COMP |= MSC_MODE_SW_SEL_COMP_CPCS3_Msk;
            ptrBaseCfg->MODE[i].SW_SEL_COMP |= MSC_MODE_SW_SEL_COMP_CMCS4_Msk;
            ptrBaseCfg->MODE[i].SW_SEL_SH |= MSC_MODE_SW_SEL_SH_C3SHG_Msk;
        }
    }

    /* Shielding is available in CSD only */
    #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) &&\
         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN))
        /*
         * PINS CONFIGURATION for the CTRL-MUX mode
         */
        #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
            ptrBaseCfg->SW_SEL_CSW_FUNC[CY_CAPSENSE_CTRLMUX_PIN_STATE_SHIELD] = CY_CAPSENSE_FW_SHIELD_ACTIVE_CTRLMUX_REG_SW_SEL_CSW_VALUE;
            if (CY_CAPSENSE_SHIELD_PASSIVE == context->ptrCommonConfig->csdShieldMode)
            {
                ptrBaseCfg->SW_SEL_CSW_FUNC[CY_CAPSENSE_CTRLMUX_PIN_STATE_SHIELD] = CY_CAPSENSE_FW_SHIELD_PASSIVE_CTRLMUX_REG_SW_SEL_CSW_VALUE;
            }
        #endif

        if(CY_CAPSENSE_BIST_IO_SHIELD_E == context->ptrBistContext->currentISC)
        {
            ptrBaseCfgMode = &ptrBaseCfg->MODE[0u];
            ptrBaseCfgMode->SENSE_DUTY_CTL &= ~(MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_FS2_PH0_EN_Msk |
                                              MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_FS2_PH1_EN_Msk);
            /* Active Shield mode */
            if (CY_CAPSENSE_SHIELD_ACTIVE == context->ptrCommonConfig->csdShieldMode)
            {
                #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
                    ptrBaseCfgMode->SW_SEL_TOP &= ~CY_CAPSENSE_FW_SHIELD_ACTIVE_CTRLMUX_REG_SW_SEL_TOP_MASK;
                    ptrBaseCfgMode->SW_SEL_SH  &= ~CY_CAPSENSE_FW_SHIELD_ACTIVE_CTRLMUX_REG_SW_SEL_SH_MASK;
                    ptrBaseCfgMode->SW_SEL_TOP |= CY_CAPSENSE_FW_SHIELD_ACTIVE_CTRLMUX_REG_SW_SEL_TOP_VALUE;
                    ptrBaseCfgMode->SW_SEL_SH  |= CY_CAPSENSE_FW_SHIELD_ACTIVE_CTRLMUX_REG_SW_SEL_SH_VALUE;
                #else /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD) */
                    /* Amux sensor_connection_method */
                    ptrBaseCfgMode->SW_SEL_TOP &= ~CY_CAPSENSE_FW_SHIELD_ACTIVE_AMUX_REG_SW_SEL_TOP_MASK;
                    ptrBaseCfgMode->SW_SEL_SH  &= ~CY_CAPSENSE_FW_SHIELD_ACTIVE_AMUX_REG_SW_SEL_SH_MASK;
                    ptrBaseCfgMode->SW_SEL_TOP |= CY_CAPSENSE_FW_SHIELD_ACTIVE_AMUX_REG_SW_SEL_TOP_VALUE;
                    ptrBaseCfgMode->SW_SEL_SH  |= CY_CAPSENSE_FW_SHIELD_ACTIVE_AMUX_REG_SW_SEL_SH_VALUE;
                #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD) */
            }
            /* Passive Shield mode */
            else
            {
                #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
                    ptrBaseCfgMode->SW_SEL_TOP &= ~CY_CAPSENSE_FW_SHIELD_PASSIVE_CTRLMUX_REG_SW_SEL_TOP_MASK;
                    ptrBaseCfgMode->SW_SEL_TOP |= CY_CAPSENSE_FW_SHIELD_PASSIVE_CTRLMUX_REG_SW_SEL_TOP_VALUE;
                    ptrBaseCfgMode->SENSE_DUTY_CTL |= ((1u << MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_FS2_PH0_EN_Pos) |
                                                     (1u << MSC_MODE_SENSE_DUTY_CTL_PHASE_GAP_FS2_PH1_EN_Pos));
                #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD) */
            }
        }
    #endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) &&\
               (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */
    /* For CSX mode (#1u) swSelTop values should be generated */
    ptrBaseCfgMode = &ptrBaseCfg->MODE[1u];
    #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
        ptrBaseCfgMode->SW_SEL_TOP = CY_CAPSENSE_CSX_FW_AMUX_MODE_SW_SEL_TOP_VALUE;
    #else /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD) */
        ptrBaseCfgMode->SW_SEL_TOP = CY_CAPSENSE_CSX_FW_CTLMUX_MODE_SW_SEL_TOP_VALUE;
    #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD) */

    /* Generating the common configuration for the control mux switch control */
    #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
        for (i = 0u; i < context->ptrCommonConfig->numPin; i++)
        {
            if ((chIndex + context->ptrCommonConfig->channelOffset) == ptrPinCfg->chId)
            {
                cswFuncMode |= (0x01uL << ptrPinCfg->padNumber);
            }
            ptrPinCfg++;
        }
        #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) &&\
             (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN))
            ptrPinCfg = context->ptrShieldPinConfig;
            for (i = 0u; i < context->ptrCommonConfig->csdShieldNumPin; i++)
            {
                if ((chIndex + context->ptrCommonConfig->channelOffset) == ptrPinCfg->chId)
                {
                    cswFuncMode |= 0x01uL << ptrPinCfg->padNumber;
                }
                ptrPinCfg++;
            }
        #endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) &&\
                   (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)) */
        ptrBaseCfg->CSW_CTL = cswFuncMode;
    #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD) */
    /* Check for modClk divider value */
    if (1u == context->ptrBistContext->eltdCapModClk)
    {
        ptrBaseCfg->CTL |= MSC_CTL_CLK_MSC_RATIO_Msk;
    }
    else
    {
        ptrBaseCfg->CTL &= ~MSC_CTL_CLK_MSC_RATIO_Msk;
    }
    /* Generating the multi-channel mode for each channel with updating the sensor control registers */
    if (0u != context->ptrCommonConfig->syncMode)
    {
        ptrBaseCfg->SNS_CTL = ((uint32_t)context->ptrCommonConfig->syncMode << MSC_SNS_CTL_MULTI_CH_MODE_Pos);
    }
    /* Generating the common configuration for the BIST epilogue cycle number */
    if (0u < context->ptrBistContext->eltdCapNumEpiCycles)
    {
        ptrBaseCfg->SCAN_CTL2 |= (uint32_t)context->ptrBistContext->eltdCapNumEpiCycles <<
                                                                    MSC_SCAN_CTL2_NUM_EPI_CYCLES_Pos;
    }
    else
    {
        ptrBaseCfg->SCAN_CTL2 |= (uint32_t)(1uL << MSC_SCAN_CTL2_NUM_EPI_CYCLES_Pos);
    }
    /* Generating the common configuration for the coarse initialization and coarse short phase */
    if((CY_CAPSENSE_MSC0_CMOD1PADD_PIN == ptrMscChConfig->pinCmod1) ||
       (CY_CAPSENSE_MSC1_CMOD1PADD_PIN == ptrMscChConfig->pinCmod1))
    {
        ptrBaseCfg->INIT_CTL1 |= (uint32_t)context->ptrBistContext->eltdCapNumCoarseInitChargeCycles <<
                                                                    MSC_INIT_CTL1_NUM_INIT_CMOD_12_RAIL_CYCLES_Pos;
        ptrBaseCfg->INIT_CTL1 |= (uint32_t)context->ptrBistContext->eltdCapNumCoarseInitSettleCycles <<
                                                                    MSC_INIT_CTL1_NUM_INIT_CMOD_12_SHORT_CYCLES_Pos;
        ptrBaseCfg->INIT_CTL3 |= CY_CAPSENSE_CMOD12_PAIR_SELECTION << MSC_INIT_CTL3_CMOD_SEL_Pos;
    }
    else
    {
        ptrBaseCfg->INIT_CTL2 |= (uint32_t)context->ptrBistContext->eltdCapNumCoarseInitChargeCycles <<
                                                                    MSC_INIT_CTL2_NUM_INIT_CMOD_34_RAIL_CYCLES_Pos;
        ptrBaseCfg->INIT_CTL2 |= (uint32_t)context->ptrBistContext->eltdCapNumCoarseInitSettleCycles <<
                                                                    MSC_INIT_CTL2_NUM_INIT_CMOD_34_SHORT_CYCLES_Pos;
        ptrBaseCfg->INIT_CTL3 |= (uint32_t)CY_CAPSENSE_CMOD34_PAIR_SELECTION << MSC_INIT_CTL3_CMOD_SEL_Pos;
    }
    /*
     * Generating the common configuration for the number of sub-conversions to be run during the PRO_DUMMY phase and
     * the modClk period number during the PRO_WAIT phase.
     */
    ptrBaseCfg->INIT_CTL4 |= (((uint32_t)context->ptrBistContext->eltdCapNumFineInitCycles <<
                                                                  MSC_INIT_CTL4_NUM_PRO_DUMMY_SUB_CONVS_Pos) |
                              ((uint32_t)context->ptrBistContext->eltdCapNumFineInitWaitCycles <<
                                                                  MSC_INIT_CTL4_NUM_PRO_WAIT_CYCLES_Pos));
}


/*******************************************************************************
* Function Name: Cy_CapSense_BistGenerateSensorConfig
****************************************************************************//**
*
* Generates the configuration for registers that have to be configured to start
* a scan for a single sensor. It is used the next sensor configuration for BIST
* scan:
* - CIC2 filter is off
* - is used mode structure 0u
* - Multi-channel mode is off
* - System level chopping is off
* - Coarse Init Bypass is off
*
* \param chIndex
* The channel index the sensor configuration is generated for.
*
* \param ptrSensorCfg
* Specifies the pointer to the sensor configuration to be filled.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the operation:
* - CY_CAPSENSE_STATUS_SUCCESS       - The operation is performed successfully.
*
*******************************************************************************/
static void Cy_CapSense_BistGenerateSensorConfig(
                uint32_t chIndex,
                uint32_t * ptrSensorCfg,
                cy_stc_capsense_context_t * context)
{
    uint16_t snsClkDividerVal;
    #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
        uint32_t i;
        const cy_stc_capsense_electrode_config_t * ptrEltdCfg;
        uint32_t padMask = 0u;
        uint32_t cswFuncNum;
        uint32_t slotStcWdgtIdx = context->ptrScanSlots[context->ptrBistContext->curBistSlotId +
                ((chIndex + context->ptrCommonConfig->channelOffset) * CY_CAPSENSE_SLOT_COUNT)].wdId;
    #else
        (void) chIndex;
    #endif

    /* Set the synchronization mode */
    if (0u != context->ptrCommonConfig->syncMode)
    {
        ptrSensorCfg[CY_CAPSENSE_SNS_CTL_INDEX] = ((uint32_t)context->ptrCommonConfig->syncMode << MSC_SNS_CTL_MULTI_CH_MODE_Pos);
    }
    /* Getting the BIST sense clock divider */
    snsClkDividerVal = context->ptrBistContext->eltdCapSnsClk;
    if (CY_CAPSENSE_BIST_CAP_SHIELD_SCAN == context->ptrBistContext->eltdCapScanMode)
    {
        snsClkDividerVal = CY_CAPSENSE_BIST_SHIELD_CAP_SNSCLK_DIV_DEFAULT;
    }
    if (snsClkDividerVal > 0u)
    {
        snsClkDividerVal -= 1u;
    }
    /* Set snsClk and Valid, Start scan, and Last slot bits */
    ptrSensorCfg[CY_CAPSENSE_SNS_CTL_INDEX] |= ((((uint32_t)snsClkDividerVal) << MSC_SNS_CTL_SENSE_DIV_Pos) |
                                                MSC_SNS_CTL_VALID_Msk |
                                                MSC_SNS_CTL_START_SCAN_Msk |
                                                MSC_SNS_CTL_LAST_Msk);
    /*
     * Set the sense mode selection.
     * For the electrode capacitance measurement only the CSD mode is used (SENSE_MODE_SEL = 0u).
     * For the slot sensor capacitance measurement the CSD mode can be used (SENSE_MODE_SEL = 0u) and
     * the CSX mode can be used (SENSE_MODE_SEL = 1u) depending on the measured slot.
     */
    if ((CY_CAPSENSE_BIST_CAP_SLOT_SCAN == context->ptrBistContext->eltdCapScanMode) &&
        (CY_CAPSENSE_CSX_GROUP == context->ptrActiveScanSns[0u].currentSenseMethod))
    {
        ptrSensorCfg[CY_CAPSENSE_SNS_CTL_INDEX] |= (1u << MSC_SNS_CTL_SENSE_MODE_SEL_Pos);
    }
    /*
     * CapDAC configuration: CapDAC dithering is off for BIST,
     * only the reference CDAC is used for BIST scans.
     */
    ptrSensorCfg[CY_CAPSENSE_SNS_CDAC_CTL_INDEX] =
                (((uint32_t)context->ptrBistContext->eltdCapRefCdac) << MSC_SNS_CDAC_CTL_SEL_RE_Pos) |
                MSC_SNS_CDAC_CTL_CLOCK_REF_RATE_Msk;
    /* Compensation CDAC Divider set to BIST Sns clock divider */
    ptrSensorCfg[CY_CAPSENSE_SNS_SCAN_CTL_INDEX] |= (((uint32_t)snsClkDividerVal) << MSC_SNS_SCAN_CTL_COMP_DIV_Pos);
    /* Number of sub-conversions */
    ptrSensorCfg[CY_CAPSENSE_SNS_SCAN_CTL_INDEX] |= ((uint32_t)context->ptrBistContext->eltdCapSubConvNum - 1u) << MSC_SNS_SCAN_CTL_NUM_SUB_CONVS_Pos;

    #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
        /* Get mask for all channel pins */
        padMask = context->ptrCommonConfig->ptrMscChConfig[chIndex].ptrMscBase->CSW_CTL;
        /* Change the control switch function depending on the current inactive sensor connection */
        cswFuncNum = CY_CAPSENSE_CTRLMUX_PIN_STATE_GND;
        if (CY_CAPSENSE_BIST_IO_HIGHZA_E == context->ptrBistContext->currentISC)
        {
            cswFuncNum = CY_CAPSENSE_CTRLMUX_PIN_STATE_HIGH_Z;
        }
        else if (CY_CAPSENSE_BIST_IO_SHIELD_E == context->ptrBistContext->currentISC)
        {
            cswFuncNum = CY_CAPSENSE_CTRLMUX_PIN_STATE_SHIELD;
        }
        else
        {
            /* Do nothing */
        }
        /* Set the control mux switch registers for inactive pins */
        Cy_CapSense_CalculateMaskRegisters(padMask, cswFuncNum, ptrSensorCfg);
        /* Check for active electrodes */
        if (0u == ((1u << (chIndex + context->ptrCommonConfig->channelOffset)) &
                    context->ptrBistContext->skipChannelMask))
        {
            if ((CY_CAPSENSE_BIST_CAP_ELTD_SCAN == context->ptrBistContext->eltdCapScanMode) ||
                (CY_CAPSENSE_BIST_CAP_SHIELD_SCAN == context->ptrBistContext->eltdCapScanMode) ||
                ((CY_CAPSENSE_BIST_CAP_SLOT_SCAN == context->ptrBistContext->eltdCapScanMode) &&
                 ((CY_CAPSENSE_SLOT_EMPTY != slotStcWdgtIdx) && (CY_CAPSENSE_SLOT_SHIELD_ONLY != slotStcWdgtIdx))))
            {
                /* Initializes an active sensor (including ganged sensors) by SNS sensor state */
                if (CY_CAPSENSE_BIST_CAP_SHIELD_SCAN == context->ptrBistContext->eltdCapScanMode)
                {
                    /* Generate CTRL_MUX masks for the electrode or CSD sensor connection */
                    cswFuncNum = CY_CAPSENSE_CTRLMUX_PIN_STATE_SNS;
                    if (CY_CAPSENSE_BIST_IO_SHIELD_E == context->ptrBistContext->currentISC)
                    {
                        padMask = context->ptrCommonConfig->ptrMscChConfig[chIndex].ptrMscBase->CSW_CTL;
                    }
                    else
                    {
                        padMask = 0u;
                        for (i = 0u; i < context->ptrCommonConfig->csdShieldNumPin; i++)
                        {
                            /* Proceed only if the shield electrode is connected belongs to the current channel */
                            if ((chIndex + context->ptrCommonConfig->channelOffset) == context->ptrShieldPinConfig[i].chId)
                            {
                                padMask |= 0x01uL << context->ptrShieldPinConfig[i].padNumber;
                            }
                        }
                    }
                    Cy_CapSense_CalculateMaskRegisters(padMask, cswFuncNum, ptrSensorCfg);
                }
                else
                {
                    if ((CY_CAPSENSE_BIST_CAP_ELTD_SCAN == context->ptrBistContext->eltdCapScanMode) ||
                        (CY_CAPSENSE_CSD_GROUP == context->ptrActiveScanSns[0u].currentSenseMethod))
                    {
                        /* Generate CTRL_MUX masks for the electrode or CSD sensor connection */
                        if (CY_CAPSENSE_BIST_CAP_ELTD_SCAN == context->ptrBistContext->eltdCapScanMode)
                        {
                            ptrEltdCfg = context->ptrBistContext->curPtrEltdCfg;
                        }
                        else
                        {
                            ptrEltdCfg = context->ptrActiveScanSns[chIndex].ptrEltdConfig;
                        }
                        cswFuncNum = CY_CAPSENSE_CTRLMUX_PIN_STATE_SNS;
                        /* Proceed only if electrode configuration belongs to selected channel */
                        if ((chIndex + context->ptrCommonConfig->channelOffset) == ptrEltdCfg->chId)
                        {
                            Cy_CapSense_BistGenerateSnsCfgMaskReg(ptrEltdCfg, ptrSensorCfg, cswFuncNum);
                        }
                    }
                    else
                    {
                        /* RX ELECTRODE */
                        if (CY_CAPSENSE_SLOT_SHIELD_ONLY > slotStcWdgtIdx)
                        {
                            cswFuncNum = CY_CAPSENSE_CTRLMUX_PIN_STATE_RX;
                            ptrEltdCfg = context->ptrActiveScanSns[chIndex].ptrRxConfig;
                            if ((chIndex + context->ptrCommonConfig->channelOffset) == ptrEltdCfg->chId)
                            {
                                Cy_CapSense_BistGenerateSnsCfgMaskReg(ptrEltdCfg, ptrSensorCfg, cswFuncNum);
                            }
                        }
                        /* TX ELECTRODE */
                        cswFuncNum = CY_CAPSENSE_CTRLMUX_PIN_STATE_TX;
                        ptrEltdCfg = context->ptrActiveScanSns[chIndex].ptrTxConfig;
                        if ((chIndex + context->ptrCommonConfig->channelOffset) == ptrEltdCfg->chId)
                        {
                            Cy_CapSense_BistGenerateSnsCfgMaskReg(ptrEltdCfg, ptrSensorCfg, cswFuncNum);
                        }
                    }
                }
            }
        }
    #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD) */
}

#if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
/*******************************************************************************
* Function Name: Cy_CapSense_BistGenerateSnsCfgMaskReg
****************************************************************************//**
*
* Calculates the configuration for all sensor configuration mask registers that
* have to be changed to set the desired CTRL-MUX function
* for the specified electrode for BIST scan.
*
* \param ptrEltdCfg
* The pointer to the specified electrode configuration
* \ref cy_stc_capsense_electrode_config_t structure.
*
* \param ptrSensorCfg
* Specifies the pointer to the sensor configuration to be filled.
*
* \param cswFuncNum
* The desired CTRL-MUX Switch Control Global function.
*
* \return
* Returns the status of the operation:
* - CY_CAPSENSE_STATUS_SUCCESS       - The operation is performed successfully.
*
*******************************************************************************/
static void Cy_CapSense_BistGenerateSnsCfgMaskReg(
                const cy_stc_capsense_electrode_config_t * ptrEltdCfg,
                uint32_t * ptrSensorCfg,
                uint32_t cswFuncNum)
{
    uint32_t padMask = 0u;
    uint32_t i;

    /* Loop through all pads for this electrode (ganged sensor) */
    for (i = 0u; i < ptrEltdCfg->numPins; i++)
    {
        padMask |= 0x01uL << ptrEltdCfg->ptrPin[i].padNumber;
    }
    Cy_CapSense_CalculateMaskRegisters(padMask, cswFuncNum, ptrSensorCfg);
}
#endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD) */
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_MEASUREMENT_GROUP_EN) */


#if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) &&\
        (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN))
/*******************************************************************************
* Function Name: Cy_CapSense_MeasureCapacitanceShieldElectrode
****************************************************************************//**
*
* Measures shield electrode capacitances in femtofarads.
*
* This function measures the capacitances of all shield electrodes for all
* enabled MSCv3 channels and returns a status of this measurement.
* The function checks if there is any CSD widget in the project and
* if the shield is enabled.
* The measurement results in femtofarads are stored
* in the chShieldCap[CY_MSC_ENABLED_CH_NUMBER] array.
* The pointer to the array is in the .ptrChShieldCap field
* of the \ref cy_stc_capsense_bist_context_t structure,
* the CY_MSC_ENABLED_CH_NUMBER define is in the cycfg_peripherals.h file.
* If the any channel shield consists of several electrodes, the total
* capacitance of all the shield electrodes is measured.
*
* This function uses an algorithm identical to the electrode capacitance
* measurement. Refer to the Cy_CapSense_MeasureCapacitanceSensorElectrode()
* function for more details.
*
* In addition to measuring shield capacitance, this function is used to
* identify various fault conditions with shield electrodes such as an
* electrically-open or -short shield electrodes, e.g. the PCB track is broken or
* shorted to other nodes in the system - in all of these conditions,
* this function returns changed capacitance that can be compared
* against pre-determined capacitance for the shield electrode to
* detect a hardware fault.
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
* By default, the both Cmod1 and Cmod2 capacitors are used for the measurement.
*
* This test can be executed using the CapSense_RunSelfTest()
* function with the CY_CAPSENSE_BIST_SHIELD_CAP_MASK mask.
*
* \note
* This function is available only for the fifth-generation CAPSENSE&trade;.
*
* \param skipChMask
* Specifies the mask to skip some channels during the shield electrode
* capacitance measurement. If the bit N in the skipChMask is set to 1,
* the channel N will be excluded from measuring and all its shield pins will be
* set to the shield inactive sensor connection state (see the .shieldCapISC
* field of the \ref cy_stc_capsense_bist_context_t structure).
*
* \param context
* The pointer to the CAPSENSE&trade; context
* structure \ref cy_stc_capsense_context_t.
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
* - CY_CAPSENSE_BIST_BAD_CONFIG_E       - The shield is disabled.
*
*******************************************************************************/
cy_en_capsense_bist_status_t Cy_CapSense_MeasureCapacitanceShieldElectrode(
                uint32_t skipChMask,
                cy_stc_capsense_context_t * context)
{
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_BAD_PARAM_E;

    #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
        uint32_t pinIndex;
        const cy_stc_capsense_pin_config_t * ptrPinCfg;
    #endif

    if(NULL != context)
    {
    #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) &&\
         (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_SHIELD_EN))
        if ((0u < context->ptrCommonConfig->csdShieldNumPin) ||
            (CY_CAPSENSE_BIST_IO_SHIELD_E == context->ptrBistContext->intrEltdCapShieldISC))
        {
            context->ptrBistContext->currentISC = context->ptrBistContext->intrEltdCapShieldISC;
            if (CY_CAPSENSE_NOT_BUSY == Cy_CapSense_IsBusy(context))
            {
                /* Set the BUSY status */
                context->ptrCommonContext->status = CY_CAPSENSE_BUSY | CY_CAPSENSE_MW_STATE_BIST_MASK;
                (void)Cy_CapSense_SwitchHwConfiguration(CY_CAPSENSE_HW_CONFIG_BIST_FUNCTIONALITY, context);
                /* Store the current slot and the skip channel mask for the BIST scan */
                context->ptrBistContext->curBistSlotId = 0u;
                context->ptrBistContext->skipChannelMask = (uint8_t)skipChMask;
                /* Switch the HW resource configuration to the electrode capacitance measurement */
                Cy_CapSense_BistSwitchHwConfig(CY_CAPSENSE_BIST_HW_ELTD_CAP_E,
                                               CY_CAPSENSE_CSD_GROUP,
                                               CY_CAPSENSE_BIST_CAP_SHIELD_SCAN,
                                               context);
                #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
                    /* Connect all shield pins as sensors for CSD BIST scan */
                    if (0u < context->ptrCommonConfig->csdShieldNumPin)
                    {
                        ptrPinCfg = context->ptrShieldPinConfig;
                        for (pinIndex = 0u; pinIndex < context->ptrCommonConfig->csdShieldNumPin; pinIndex++)
                        {
                            if (((0x01uL << ptrPinCfg->chId) & skipChMask) == 0u)
                            {
                                Cy_CapSense_SsConfigPinRegisters(ptrPinCfg->pcPtr, (uint32_t)ptrPinCfg->pinNumber,
                                                                 CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_HSIOM_SEL_CSD_SENSE);
                            }
                            ptrPinCfg++;
                        }
                    }
                    if (CY_CAPSENSE_BIST_IO_SHIELD_E == context->ptrBistContext->currentISC)
                    {
                        /* Connect all sensor pins for CSD BIST scan */
                        ptrPinCfg = context->ptrPinConfig;
                        for (pinIndex = 0u; pinIndex < context->ptrCommonConfig->numPin; pinIndex++)
                        {
                            if (((0x01uL << ptrPinCfg->chId) & skipChMask) == 0u)
                            {
                                Cy_CapSense_SsConfigPinRegisters(ptrPinCfg->pcPtr, (uint32_t)ptrPinCfg->pinNumber,
                                                                 CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_HSIOM_SEL_CSD_SENSE);
                            }
                            ptrPinCfg++;
                        }
                    }
                #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD) */
                /* Perform the CSD BIST slot scan with connected all channel shields as active electrodes */
                result = Cy_CapSense_BistMeasureCapacitanceSlot(0u, context);
                #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
                    /* Disconnect all shield pins by setting them to the current BIST ISC */
                    if (0u < context->ptrCommonConfig->csdShieldNumPin)
                    {
                        ptrPinCfg = context->ptrShieldPinConfig;
                        for (pinIndex = 0u; pinIndex < context->ptrCommonConfig->csdShieldNumPin; pinIndex++)
                        {
                            if (((0x01uL << ptrPinCfg->chId) & skipChMask) == 0u)
                            {
                                Cy_CapSense_SsConfigPinRegisters(ptrPinCfg->pcPtr,
                                                                 (uint32_t)ptrPinCfg->pinNumber,
                                                                 context->ptrBistContext->eltdInactiveDm,
                                                                 context->ptrBistContext->eltdInactiveHsiom);
                            }
                            ptrPinCfg++;
                        }
                    }
                    if (CY_CAPSENSE_BIST_IO_SHIELD_E == context->ptrBistContext->currentISC)
                    {
                        /* Disconnect all sensor pins by setting them to the current BIST ISC */
                        ptrPinCfg = context->ptrPinConfig;
                        for (pinIndex = 0u; pinIndex < context->ptrCommonConfig->numPin; pinIndex++)
                        {
                            if (((0x01uL << ptrPinCfg->chId) & skipChMask) == 0u)
                            {
                                Cy_CapSense_SsConfigPinRegisters(ptrPinCfg->pcPtr,
                                                                 (uint32_t)ptrPinCfg->pinNumber,
                                                                 context->ptrBistContext->eltdInactiveDm,
                                                                 context->ptrBistContext->eltdInactiveHsiom);
                            }
                            ptrPinCfg++;
                        }
                    }
                #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD) */
                /* Clear the BUSY flag */
                context->ptrCommonContext->status = CY_CAPSENSE_NOT_BUSY;
            }
            else
            {
                result = CY_CAPSENSE_BIST_HW_BUSY_E;
            }
        }
    #endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) &&\
               (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)) */
    }

    return (result);
}
#endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) &&\
           (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SH_CAP_EN)) */


#if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_ELTD_CAP_EN) && \
     (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD))
/*******************************************************************************
* Function Name: Cy_CapSense_BistConnectEltd
****************************************************************************//**
*
* Connects a specified electrode as CSD sensor to the BIST active MSC HW block.
*
* The function connects all the electrode pins including ganged.
* The BIST active MSC HW block is specified
* in the \ref cy_stc_capsense_bist_context_t structure.
*
* \param ptrEltdConfig
* The pointer to the specified electrode configuration
* \ref cy_stc_capsense_electrode_config_t structure.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_BistConnectEltd(
                const cy_stc_capsense_electrode_config_t * ptrEltdConfig,
                const cy_stc_capsense_context_t * context)
{
    const cy_stc_capsense_pin_config_t * ptrActivePin = ptrEltdConfig->ptrPin;
    uint32_t i;

    if((context->ptrBistContext->curBistChId + context->ptrCommonConfig->channelOffset) == ptrEltdConfig->chId)
    {
        /* Connect all pins of current sensors */
        for(i = 0u; i < ptrEltdConfig->numPins; i++)
        {
            Cy_CapSense_SsConfigPinRegisters(ptrActivePin->pcPtr, (uint32_t)ptrActivePin->pinNumber,
                    CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_HSIOM_SEL_CSD_SENSE);
            ptrActivePin++;
        }
    }
}


/*******************************************************************************
* Function Name: Cy_CapSense_BistDisconnectEltd
****************************************************************************//**
*
* The function disconnects all the electrode pins including ganged.
* The BIST active MSC HW block is specified
* in the \ref cy_stc_capsense_bist_context_t structure.
*
* \param ptrEltdConfig
* The pointer to the specified electrode configuration
* \ref cy_stc_capsense_electrode_config_t structure.
*
* \param desiredPinState
* Specifies the desired pin state. See the possible states
* in the cy_en_capsense_bist_io_state_t enum description.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_BistDisconnectEltd(
                const cy_stc_capsense_electrode_config_t * ptrEltdConfig,
                cy_en_capsense_bist_io_state_t desiredPinState,
                const cy_stc_capsense_context_t * context)
{
    const cy_stc_capsense_pin_config_t * ptrActivePin = ptrEltdConfig->ptrPin;
    uint32_t i;
    uint32_t desiredDriveMode = CY_CAPSENSE_DM_GPIO_ANALOG;
    en_hsiom_sel_t desiredHsiom = CY_CAPSENSE_HSIOM_SEL_GPIO;

    if((context->ptrBistContext->curBistChId + context->ptrCommonConfig->channelOffset) == ptrEltdConfig->chId)
    {
        /* Change Drive mode and HSIOM depending on the current inactive sensor connection */
        if (CY_CAPSENSE_BIST_IO_STRONG_E == desiredPinState)
        {
            desiredDriveMode = CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF;
            desiredHsiom = CY_CAPSENSE_HSIOM_SEL_GPIO;
        }
        else if (CY_CAPSENSE_BIST_IO_HIGHZA_E == desiredPinState)
        {
            /* Do nothing */
        }
        else if (CY_CAPSENSE_BIST_IO_SHIELD_E == desiredPinState)
        {
            desiredDriveMode = CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF;
            desiredHsiom = CY_CAPSENSE_HSIOM_SEL_CSD_SHIELD;
        }
        else
        {
            /* Do nothing */
        }
        /* Disconnect all pins of the current sensor */
        for(i = 0u; i < ptrEltdConfig->numPins; i++)
        {
            Cy_CapSense_SsConfigPinRegisters(ptrActivePin->pcPtr, (uint32_t)ptrActivePin->pinNumber,
                                             desiredDriveMode, desiredHsiom);
            Cy_GPIO_Clr(ptrActivePin->pcPtr, (uint32_t)ptrActivePin->pinNumber);
            ptrActivePin++;
        }
    }
}
#endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_ELTD_CAP_EN) && \
           (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)) */


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
    context->ptrBistContext->eltdCapSenseGroup = CY_CAPSENSE_UNDEFINED_GROUP;
}


/*******************************************************************************
* Function Name: Cy_CapSense_BistDsInitialize_V3
****************************************************************************//**
*
* This internal function initializes the BIST cy_stc_capsense_bist_context_t
* data structure parameters to be used in the test execution.
*
* The function is called once at the CAPSENSE&trade; start and performs
* the \ref cy_stc_capsense_bist_context_t structure initialization based
* on the configured parameters.
*
* Some of the parameters of the \ref cy_stc_capsense_bist_context_t structure
* can be changed in the run-time, but some changes require repeating the call
* of this function to the re-calculate register values.
* Refer to description of the following functions which parameters are used
* as an input and which are outputs:
* * Cy_CapSense_BistMeasureCapacitanceSensorInit()
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_BistDsInitialize_V3(cy_stc_capsense_context_t * context)
{
    uint32_t wdIndex;
    uint32_t wdNum = (uint32_t)context->ptrCommonConfig->numWd;

    /* Initialize CRC and status for all widgets */
    for (wdIndex = 0u; wdIndex < wdNum; wdIndex++)
    {
        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN)
            Cy_CapSense_UpdateCrcWidget(wdIndex, context);
        #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN)) */
        context->ptrWdContext[wdIndex].status |= (uint8_t)CY_CAPSENSE_WD_WORKING_MASK;
    }

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_MEASUREMENT_GROUP_EN)
        Cy_CapSense_BistMeasureCapacitanceSensorInit(context);
    #endif

    context->ptrBistContext->hwConfig = CY_CAPSENSE_BIST_HW_UNDEFINED_E;
    context->ptrBistContext->currentISC = CY_CAPSENSE_BIST_IO_UNDEFINED_E;
    context->ptrBistContext->eltdCapSenseGroup = CY_CAPSENSE_UNDEFINED_GROUP;
    context->ptrBistContext->intrEltdCapCsdISC = context->ptrBistContext->eltdCapCsdISC;
    context->ptrBistContext->intrEltdCapCsxISC = context->ptrBistContext->eltdCapCsxISC;
    context->ptrBistContext->intrEltdCapShieldISC = context->ptrBistContext->shieldCapISC;
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
* to the analog bus in the AMUX mode.
* The function does not configure HW block registers to the default state.
* It is used by the Cy_CapSense_SwitchHwConfiguration() function only at switching
* to another sensing mode.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_BistDisableMode(cy_stc_capsense_context_t * context)
{
    Cy_CapSense_BistSwitchAllSnsPinState(CY_CAPSENSE_BIST_IO_STRONG_E, context);
    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
        Cy_CapSense_BistSwitchAllShieldPinState(CY_CAPSENSE_BIST_IO_STRONG_E, context);
    #endif
    Cy_CapSense_BistSwitchAllExternalCapPinState(CY_CAPSENSE_BIST_IO_STRONG_E, context);

    context->ptrBistContext->hwConfig = CY_CAPSENSE_BIST_HW_UNDEFINED_E;
    context->ptrBistContext->currentISC = CY_CAPSENSE_BIST_IO_UNDEFINED_E;
}


/*******************************************************************************
* Function Name: Cy_CapSense_BistSwitchHwConfig
****************************************************************************//**
*
* This internal function switches the MSCv3 HW block configuration for
* BIST operations.
*
* The function checks the current MSCv3 HW block configuration.
* If it differs from a desired configuration, the function disables the current
* configuration and sets the desired one.
*
* \param hwCfg
* Specifies the desired configuration.
*
* \param bistSenseGroup
* Specifies the sense group to be scanned during the sensor or electrode
* capacitance measurement scan.
* The parameter does not matter for short tests.
*
* \param bistScanMode
* Specifies the scanning mode (by electrodes or by slots) during the sensor
* or electrode capacitance measurement scan.
* The parameter does not matter for short tests.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_BistSwitchHwConfig(
                cy_en_capsense_bist_hw_config_t hwCfg,
                uint8_t bistSenseGroup,
                uint8_t bistScanMode,
                cy_stc_capsense_context_t * context)
{
    #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD) || (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_SHORT_EN)
        uint32_t curChIndex;
    #endif

    if ((context->ptrBistContext->hwConfig != hwCfg) ||
        (context->ptrBistContext->eltdCapSenseGroup != bistSenseGroup) ||
        (context->ptrBistContext->eltdCapScanMode != bistScanMode))
    {
        context->ptrBistContext->hwConfig = hwCfg;
        context->ptrBistContext->eltdCapSenseGroup = bistSenseGroup;
        context->ptrBistContext->eltdCapScanMode = bistScanMode;
        /* Enable the specified mode */
        switch(hwCfg)
        {
            #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_SHORT_EN)
                case CY_CAPSENSE_BIST_HW_SHORT_E:
                {
                    /* Configure all the MSC channels to perform pin integrity tests */
                    for(curChIndex = 0u; curChIndex < CY_CAPSENSE_TOTAL_CH_NUMBER; curChIndex++)
                    {
                        context->ptrCommonConfig->ptrMscChConfig[curChIndex].ptrMscBase->CSW_CTL = 0x00u;
                    }
                    break;
                }
            #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_SHORT_EN) */

            #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_MEASUREMENT_GROUP_EN)
                case CY_CAPSENSE_BIST_HW_ELTD_CAP_E:
                {
                    #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
                        Cy_CapSense_BistSwitchAllSnsPinState(context->ptrBistContext->currentISC, context);
                        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
                            Cy_CapSense_BistSwitchAllShieldPinState(context->ptrBistContext->currentISC, context);
                        #endif
                    #else /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD) */
                        Cy_CapSense_SetIOsInDefaultState(context);
                        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
                            Cy_CapSense_SetShieldPinsInDefaultState(context);
                        #endif
                        for (curChIndex = 0u; curChIndex < context->ptrCommonConfig->numChannels; curChIndex++)
                        {
                            Cy_CapSense_SetCmodInDefaultState(curChIndex, context);
                        }
                    #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD) */

                    (void)Cy_CapSense_BistMeasureCapacitanceSensorEnable(context);
                    break;
                }
                case CY_CAPSENSE_BIST_HW_ELTD_CAP_SH_E:
                {
                    #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
                        Cy_CapSense_BistSwitchAllSnsPinState(context->ptrBistContext->intrEltdCapShieldISC, context);
                        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
                            Cy_CapSense_BistSwitchAllShieldPinState(context->ptrBistContext->intrEltdCapShieldISC, context);
                        #endif
                    #else /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD) */
                        Cy_CapSense_SetIOsInDefaultState(context);
                        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
                            Cy_CapSense_SetShieldPinsInDefaultState(context);
                        #endif
                        for (curChIndex = 0u; curChIndex < context->ptrCommonConfig->numChannels; curChIndex++)
                        {
                            Cy_CapSense_SetCmodInDefaultState(curChIndex, context);
                        }
                    #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD) */

                    (void)Cy_CapSense_BistMeasureCapacitanceSensorEnable(context);

                    break;
                }
            #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_MEASUREMENT_GROUP_EN) */

            default:
            {
                /* Nothing to do */
                break;
            }
        }
    }
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_HW_GROUP_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_MEASUREMENT_GROUP_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_BistMeasureCapacitanceSensorInit
****************************************************************************//**
*
* This internal function calculates the parameters for sensor, shield or
* electrode capacitance measurements.
*
* It is called by Cy_CapSense_BistDsInitialize() once at the CAPSENSE&trade; MW start.
*
* The following parameters of cy_stc_capsense_bist_context_t are used as
* an input for the calculation:
* * .eltdCapModClk
* * .eltdCapSnsClk
*
* The function checks for parameter limitations and corrects the values before
* the calculation if they exceed.
*
* The following parameters of cy_stc_capsense_bist_context_t are updated
* by the calculation:
* * .eltdCapModClk
* * .eltdCapSnsClk
* * .eltdCapSubConvNum
*
* Restarting CAPSENSE&trade; MW or calling of the Cy_CapSense_BistDsInitialize()
* function overwrites the output parameters.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_BistMeasureCapacitanceSensorInit(
                cy_stc_capsense_context_t * context)
{
    cy_stc_capsense_bist_context_t * ptrBistCxt = context->ptrBistContext;

    /* ModClk */
    if (0u == ptrBistCxt->eltdCapModClk)
    {
        ptrBistCxt->eltdCapModClk = (uint16_t)CY_CAPSENSE_BIST_ELTD_CAP_MODCLK_DIV_DEFAULT;
    }
    if (CY_CAPSENSE_BIST_ELTD_CAP_MAX_MODCLK < (context->ptrCommonConfig->periClkHz / ptrBistCxt->eltdCapModClk))
    {
        ptrBistCxt->eltdCapModClk <<= 1u;
    }

    /* SnsClk */
    if (0u == ptrBistCxt->eltdCapSnsClk)
    {
        ptrBistCxt->eltdCapSnsClk = (uint16_t)CY_CAPSENSE_BIST_ELTD_CAP_SNSCLK_DIV_DEFAULT;
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
    /* NumSubConv */
    ptrBistCxt->eltdCapSubConvNum = (uint16_t)CY_CAPSENSE_BIST_ELTD_CAP_SUBCONV_NUM_DEFAULT;
    /* NumEpiCycles and NumProWaitCycles depends on SnsClk divider */
    ptrBistCxt->eltdCapNumEpiCycles = ptrBistCxt->eltdCapSnsClk / CY_CAPSENSE_DIVIDER_TWO;
    ptrBistCxt->eltdCapNumFineInitWaitCycles = ptrBistCxt->eltdCapNumEpiCycles;
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_MEASUREMENT_GROUP_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_HW_GROUP_EN)
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
    uint32_t desiredPinOutput = CY_CAPSENSE_BIST_DR_PIN2GND;

    Cy_CapSense_BistSetDmHsiomPinState(desiredPinState, context);
    if (CY_CAPSENSE_BIST_IO_STRONG_HIGH_E == desiredPinState)
    {
        desiredPinOutput = CY_CAPSENSE_BIST_DR_PIN2VDD;
    }
    Cy_CapSense_BistSetAllSnsPinsState(context->ptrBistContext->eltdInactiveDm, desiredPinOutput,
                                       context->ptrBistContext->eltdInactiveHsiom, context);
}


/*******************************************************************************
* Function Name: Cy_CapSense_BistSetDmHsiomPinState
****************************************************************************//**
*
* This internal function changes the port control (PC) and HSIOM
* register values needed to set pins to the desired state.
*
* The function changes the .eltdInactiveDm and .eltdInactiveHsiom field values
* of the \ref cy_stc_capsense_bist_context_t structure on ones needed to set
* pins to the desired pin state (Drive Mode and HSIOM state).
*
* \param desiredPinState
* Specifies the desired pin state. See the possible states
* in the cy_en_capsense_bist_io_state_t enum description.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_BistSetDmHsiomPinState(
                cy_en_capsense_bist_io_state_t desiredPinState,
                const cy_stc_capsense_context_t * context)
{
    context->ptrBistContext->eltdInactiveDm = CY_CAPSENSE_DM_GPIO_ANALOG;
    context->ptrBistContext->eltdInactiveHsiom = CY_CAPSENSE_HSIOM_SEL_GPIO;

    /* Change Drive mode and HSIOM depending on the current inactive sensor connection */
    if ((CY_CAPSENSE_BIST_IO_STRONG_E == desiredPinState) ||
        (CY_CAPSENSE_BIST_IO_STRONG_HIGH_E == desiredPinState))
    {
        context->ptrBistContext->eltdInactiveDm = CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF;
    }

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
        if (CY_CAPSENSE_BIST_IO_SHIELD_E == desiredPinState)
        {
            context->ptrBistContext->eltdInactiveHsiom = CY_CAPSENSE_HSIOM_SEL_CSD_SHIELD;
            if (CY_CAPSENSE_SHIELD_PASSIVE == context->ptrCommonConfig->csdShieldMode)
            {
                context->ptrBistContext->eltdInactiveDm = CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF;
            }
        }
    #endif
}


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
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
    uint32_t desiredPinOutput = CY_CAPSENSE_BIST_DR_PIN2GND;

    if (0u < context->ptrCommonConfig->csdShieldNumPin)
    {
        Cy_CapSense_BistSetDmHsiomPinState(desiredPinState, context);
        if (CY_CAPSENSE_BIST_IO_STRONG_HIGH_E == desiredPinState)
        {
            desiredPinOutput = CY_CAPSENSE_BIST_DR_PIN2VDD;
        }
        Cy_CapSense_BistSetAllShieldPinsState(context->ptrBistContext->eltdInactiveDm, desiredPinOutput,
                                              context->ptrBistContext->eltdInactiveHsiom, context);
    }
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) */
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */


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
    uint32_t desiredDriveMode = CY_CAPSENSE_DM_GPIO_ANALOG;
    en_hsiom_sel_t desiredHsiom = CY_CAPSENSE_HSIOM_SEL_GPIO;
    uint32_t desiredPinOutput = CY_CAPSENSE_BIST_DR_PIN2GND;

    /* Change Drive mode and HSIOM depending on the current inactive sensor connection */
    if (CY_CAPSENSE_BIST_IO_STRONG_E == desiredPinState)
    {
        desiredDriveMode = CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF;
        desiredHsiom = CY_CAPSENSE_HSIOM_SEL_GPIO;
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
    Cy_CapSense_BistSetAllCmodPinsState(desiredDriveMode, desiredPinOutput, desiredHsiom, context);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_HW_GROUP_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_MEASUREMENT_GROUP_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_BistWatchdogPeriodCalc
****************************************************************************//**
*
* The internal function calculates the watch-dog period for BIST sensor
* capacity measurement scans in CPU cycles.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the calculated watch-dog period for BIST sensor capacity measurement
* scans in CPU cycles:
*******************************************************************************/
static uint32_t Cy_CapSense_BistWatchdogPeriodCalc(
                const cy_stc_capsense_context_t * context)
{
    uint64_t isBusyWatchdogTimeUs;
    uint32_t modClkDivider;
    uint32_t watchdogPeriod;

    modClkDivider = context->ptrBistContext->eltdCapModClk;
    if(0u == modClkDivider)
    {
        modClkDivider = 1u;
    }

    isBusyWatchdogTimeUs  = ((uint64_t)context->ptrBistContext->eltdCapSnsClk) *
                            ((uint64_t)context->ptrBistContext->eltdCapSubConvNum);
    isBusyWatchdogTimeUs *= (uint64_t)modClkDivider * CY_CAPSENSE_CONVERSION_MEGA;
    isBusyWatchdogTimeUs /= context->ptrCommonConfig->periClkHz;
    if(0u == isBusyWatchdogTimeUs)
    {
        isBusyWatchdogTimeUs = 1u;
    }
    isBusyWatchdogTimeUs *= CY_CAPSENSE_BIST_WATCHDOG_MARGIN_COEFF;
    watchdogPeriod = Cy_CapSense_WatchdogCyclesNum((uint32_t)isBusyWatchdogTimeUs,
                                                   context->ptrCommonConfig->cpuClkHz / CY_CAPSENSE_CONVERSION_MEGA,
                                                   CY_CAPSENSE_BIST_CAP_MEAS_WDT_CYCLES_PER_LOOP);
    return (watchdogPeriod);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_MEASUREMENT_GROUP_EN) */

#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) */

#endif /* (defined(CY_IP_M0S8MSCV3)) */


/* [] END OF FILE */
