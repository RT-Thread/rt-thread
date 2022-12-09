/***************************************************************************//**
* \file cy_capsense_sm_base_full_wave_v3.h
* \version 3.0
*
* \brief
* This file lists a set of macros for each register bit-field for the specified
* sensing method.
*
********************************************************************************
* \copyright
* Copyright 2020-2021, Cypress Semiconductor Corporation (an Infineon company)
* or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_SM_BASE_FULL_WAVE_V3_H)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_V3_H

#if defined(CY_IP_M0S8MSCV3)

#if defined(__cplusplus)
extern "C" {
#endif

/* CTL Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CTL_FLD_SENSE_EN                                              (1uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CTL_FLD_MSCCMP_EN                                             (1uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CTL_FLD_CLK_SYNC_EN                                           (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CTL_FLD_EXT_FRAME_START_EN                                    (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CTL_FLD_OPERATING_MODE                                        (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CTL_FLD_BUF_MODE                                              (1uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CTL_FLD_CLK_MSC_RATIO                                         (1uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CTL_FLD_ENABLED                                               (1uL)

/* SPARE Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SPARE_FLD_SPARE                                               (0uL)

/* SCAN_CTL1 Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SCAN_CTL1_FLD_NUM_AUTO_RESAMPLE                               (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SCAN_CTL1_FLD_RESCAN_DEBUG_MODE                               (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SCAN_CTL1_FLD_NUM_SAMPLES                                     (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SCAN_CTL1_FLD_RAW_COUNT_MODE                                  (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SCAN_CTL1_FLD_DEBUG_CONV_PH_SEL                               (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SCAN_CTL1_FLD_FRAME_START_PTR                                 (0uL)

/* SCAN_CTL2 Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SCAN_CTL2_FLD_NUM_EPI_CYCLES                                  (20uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SCAN_CTL2_FLD_CHOP_POL                                        (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SCAN_CTL2_FLD_CHOP_EVEN_HOLD_EN                               (0uL)

/* INIT_CTL1 Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL1_FLD_NUM_INIT_CMOD_12_RAIL_CYCLES                    (200uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL1_FLD_NUM_INIT_CMOD_12_SHORT_CYCLES                   (200uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL1_FLD_PER_SAMPLE                                      (0uL)

/* INIT_CTL2 Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL2_FLD_NUM_INIT_CMOD_34_RAIL_CYCLES                    (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL2_FLD_NUM_INIT_CMOD_34_SHORT_CYCLES                   (0uL)

/* INIT_CTL3 Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL3_FLD_NUM_PRO_OFFSET_CYCLES                           (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL3_FLD_NUM_PRO_OFFSET_TRIPS                            (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL3_FLD_CMOD_SEL                                        (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL3_FLD_INIT_MODE                                       (0uL)

/* INIT_CTL4 Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL4_FLD_NUM_PRO_DUMMY_SUB_CONVS                         (3uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL4_FLD_NUM_PRO_WAIT_CYCLES                             (15uL)

/* SENSE_DUTY_CTL Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SENSE_DUTY_CTL_FLD_PHASE_WIDTH                                (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SENSE_DUTY_CTL_FLD_PHASE_SHIFT_CYCLES                         (1uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SENSE_DUTY_CTL_FLD_PHASE_WIDTH_SEL                            (0uL)

/* SENSE_PERIOD_CTL Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SENSE_PERIOD_CTL_FLD_LFSR_POLY                                (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SENSE_PERIOD_CTL_FLD_LFSR_SCALE                               (0uL)

/* FILTER_CTL Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_FILTER_CTL_FLD_BIT_FORMAT                                     (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_FILTER_CTL_FLD_FILTER_MODE                                    (0uL)

/* CCOMP_CDAC_CTL Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CCOMP_CDAC_CTL_FLD_SEL_CO_PRO_OFFSET                          (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CCOMP_CDAC_CTL_FLD_EPILOGUE_EN                                (0uL)

/* DITHER_CDAC_CTL Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_DITHER_CDAC_CTL_FLD_SEL_FL                                    (255uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_DITHER_CDAC_CTL_FLD_LFSR_POLY_FL                              (142uL)

/* CSW_CTL Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CSW_CTL_FLD_CSW_FUNC_MODE                                     (0uL)

/* SW_SEL_CDAC_RE Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_RE_FLD_SW_RETCA                                   (3uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_RE_FLD_SW_RECB                                    (2uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_RE_FLD_SW_RETV                                    (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_RE_FLD_SW_RETG                                    (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_RE_FLD_SW_REBV                                    (2uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_RE_FLD_SW_REBG                                    (3uL)

/* SW_SEL_CDAC_CO Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CO_FLD_SW_COTCA                                   (2uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CO_FLD_SW_COCB                                    (3uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CO_FLD_SW_COTV                                    (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CO_FLD_SW_COTG                                    (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CO_FLD_SW_COBV                                    (3uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CO_FLD_SW_COBG                                    (2uL)

/* SW_SEL_CDAC_CF Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CF_FLD_SW_CFTCA                                   (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CF_FLD_SW_CFTCB                                   (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CF_FLD_SW_CFTV                                    (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CF_FLD_SW_CFTG                                    (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CF_FLD_SW_CFBV                                    (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CF_FLD_SW_CFBG                                    (0uL)

/* SW_SEL_CMOD1 Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD1_FLD_SW_C1CA                                      (1uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD1_FLD_SW_C1CB                                      (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD1_FLD_SW_C1CC                                      (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD1_FLD_SW_C1CV                                      (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD1_FLD_SW_C1CG                                      (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD1_FLD_REF_MODE                                     (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD1_FLD_ENABLED                                      (1uL)

/* SW_SEL_CMOD2 Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD2_FLD_SW_C2CA                                      (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD2_FLD_SW_C2CB                                      (1uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD2_FLD_SW_C2CC                                      (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD2_FLD_SW_C2CV                                      (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD2_FLD_SW_C2CG                                      (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD2_FLD_REF_MODE                                     (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD2_FLD_ENABLED                                      (1uL)

/* SW_SEL_CMOD3 Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD3_FLD_SW_C3CA                                      (1uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD3_FLD_SW_C3CB                                      (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD3_FLD_SW_C3CC                                      (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD3_FLD_SW_C3CV                                      (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD3_FLD_SW_C3CG                                      (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD3_FLD_REF_MODE                                     (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD3_FLD_ENABLED                                      (1uL)

/* SW_SEL_CMOD4 Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD4_FLD_SW_C4CA                                      (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD4_FLD_SW_C4CB                                      (1uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD4_FLD_SW_C4CC                                      (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD4_FLD_SW_C4CV                                      (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD4_FLD_SW_C4CG                                      (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD4_FLD_REF_MODE                                     (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CMOD4_FLD_ENABLED                                      (1uL)

/* OBS_CTL Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_OBS_CTL_FLD_OBSERVE0                                          (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_OBS_CTL_FLD_OBSERVE1                                          (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_OBS_CTL_FLD_OBSERVE2                                          (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_OBS_CTL_FLD_OBSERVE3                                          (0uL)

/* WAKEUP_CTL Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_WAKEUP_CTL_FLD_WAKEUP_TIMER                                   (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_WAKEUP_CTL_FLD_ENABLED                                        (0uL)

/* LP_AOC_CTL Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_LP_AOC_CTL_FLD_BUCKET_THRESHOLD                               (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_LP_AOC_CTL_FLD_BUCKET_STEP_SIZE                               (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_LP_AOC_CTL_FLD_DEBOUNCE_THRESHOLD                             (0uL)

/* INTR Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_FLD_SUB_SAMPLE                                           (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_FLD_SAMPLE                                               (1uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_FLD_SCAN                                                 (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_FLD_INIT                                                 (1uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_FLD_FRAME                                                (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_FLD_FIFO_UNDERFLOW                                       (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_FLD_FIFO_OVERFLOW                                        (0uL)

/* INTR_SET Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_SET_FLD_SUB_SAMPLE                                       (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_SET_FLD_SAMPLE                                           (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_SET_FLD_SCAN                                             (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_SET_FLD_INIT                                             (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_SET_FLD_FRAME                                            (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_SET_FLD_FIFO_UNDERFLOW                                   (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_SET_FLD_FIFO_OVERFLOW                                    (0uL)

/* INTR_MASK Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_MASK_FLD_SUB_SAMPLE                                      (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_MASK_FLD_SAMPLE                                          (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_MASK_FLD_SCAN                                            (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_MASK_FLD_INIT                                            (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_MASK_FLD_FRAME                                           (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_MASK_FLD_FIFO_UNDERFLOW                                  (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_MASK_FLD_FIFO_OVERFLOW                                   (0uL)

/* INTR_LP Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_LP_FLD_WAKEUP                                            (0uL)

/* INTR_LP_SET Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_LP_SET_FLD_WAKEUP                                        (0uL)

/* INTR_LP_MASK Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_LP_MASK_FLD_WAKEUP                                       (0uL)

/* FRAME_CMD Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_FRAME_CMD_FLD_START_FRAME                                     (1uL)

/* WAKEUP_CMD Register */
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_WAKEUP_CMD_FLD_WAIT_FOR_DS                                    (0uL)
#define CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_WAKEUP_CMD_FLD_ABORT                                          (0uL)

/* MODE0_SENSE_DUTY_CTL Register for CSD SM */
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH0_EN             (1uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH1_EN             (1uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH2_EN             (1uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH3_EN             (1uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_FS2_PH0_EN         (1uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_FS2_PH1_EN         (1uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PH_GAP_2CYCLE_EN             (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH0X_EN            (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH1X_EN            (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHX_GAP_2CYCLE_EN            (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_SHIFT_EN               (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_MODE_SEL               (0uL)

/* MODE0_SW_SEL_CDAC_FL Register for CSD SM */
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTCA                     (3uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLCB                      (2uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTV                      (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTG                      (3uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLBV                      (6uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLBG                      (7uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_ACTIVATION_MODE              (0uL)

/* MODE0_SW_SEL_TOP Register for CSD SM */
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_CACB                             (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_CACC                             (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_CBCC                             (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_MBCC                             (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_AYA_CTL                          (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_AYA_EN                           (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_AYB_CTL                          (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_AYB_EN                           (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_BYB                              (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_SOSH                             (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_SHV                              (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_SHG                              (1uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_BGRF                             (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_RMF                              (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_MBF                              (0uL)

/* MODE0_SW_SEL_COMP Register for CSD SM */
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCS1                           (1uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCS3                           (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPMA                            (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCA                            (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCB                            (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMCB                            (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPF                             (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMCS2                           (1uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMCS4                           (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMV                             (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMG                             (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMF                             (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_HALF_WAVE_EN                    (0uL)

/* MODE0_SW_SEL_SH Register for CSD SM */
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_C1SHG                             (1uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_C1SH                              (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_C3SHG                             (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_C3SH                              (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_SOMB                              (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_CBSO                              (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_SPCS1                             (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_SPCS3                             (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_FSP                               (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_CCSO                              (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_BUF_SEL                           (7uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_BUF_EN                            (0uL)

/* MODE0_SENSE_DUTY_CTL Register for CSX SM */
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH0_EN             (1uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH1_EN             (1uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH2_EN             (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH3_EN             (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_FS2_PH0_EN         (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_FS2_PH1_EN         (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PH_GAP_2CYCLE_EN             (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH0X_EN            (1uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_GAP_PH1X_EN            (1uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHX_GAP_2CYCLE_EN            (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_SHIFT_EN               (1uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SENSE_DUTY_CTL_FLD_PHASE_MODE_SEL               (1uL)

/* MODE0_SW_SEL_CDAC_FL Register for CSX SM */
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTCA                     (5uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLCB                      (4uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTV                      (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTG                      (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLBV                      (4uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLBG                      (5uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_ACTIVATION_MODE              (0uL)

/* MODE0_SW_SEL_TOP Register for CSX SM */
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_CACB                             (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_CACC                             (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_CBCC                             (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_MBCC                             (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_AYA_CTL                          (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_AYA_EN                           (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_AYB_CTL                          (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_AYB_EN                           (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_BYB                              (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_SOSH                             (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_SHV                              (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_SHG                              (1uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_BGRF                             (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_RMF                              (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_TOP_FLD_MBF                              (0uL)

/* MODE0_SW_SEL_COMP Register for CSX SM */
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCS1                           (1uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCS3                           (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPMA                            (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCA                            (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCB                            (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMCB                            (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPF                             (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMCS2                           (1uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMCS4                           (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMV                             (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMG                             (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMF                             (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_HALF_WAVE_EN                    (0uL)

/* MODE0_SW_SEL_SH Register for CSX SM */
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_C1SHG                             (1uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_C1SH                              (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_C3SHG                             (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_C3SH                              (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_SOMB                              (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_CBSO                              (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_SPCS1                             (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_SPCS3                             (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_FSP                               (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_CCSO                              (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_BUF_SEL                           (7uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_BUF_EN                            (0uL)

/* MODE0_SW_SEL_CDAC_FL Register for CSD SM with CapDAC dithering */
#define CY_CAPSENSE_SM_CSD_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTCA                (3uL)
#define CY_CAPSENSE_SM_CSD_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLCB                 (2uL)
#define CY_CAPSENSE_SM_CSD_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTV                 (2uL)
#define CY_CAPSENSE_SM_CSD_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTG                 (3uL)
#define CY_CAPSENSE_SM_CSD_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLBV                 (6uL)
#define CY_CAPSENSE_SM_CSD_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLBG                 (7uL)
#define CY_CAPSENSE_SM_CSD_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_ACTIVATION_MODE         (0uL)

/* MODE0_SW_SEL_CDAC_FL Register for CSX SM with CapDAC dithering */
#define CY_CAPSENSE_SM_CSX_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTCA                (4uL)
#define CY_CAPSENSE_SM_CSX_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLCB                 (5uL)
#define CY_CAPSENSE_SM_CSX_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTV                 (0uL)
#define CY_CAPSENSE_SM_CSX_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTG                 (0uL)
#define CY_CAPSENSE_SM_CSX_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLBV                 (2uL)
#define CY_CAPSENSE_SM_CSX_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLBG                 (3uL)
#define CY_CAPSENSE_SM_CSX_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_ACTIVATION_MODE         (0uL)

/* SW_SEL_GPIO Register for CSD SM */
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_GPIO_REG_SW_SEL_GPIO_FLD_SW_CSD_SENSE                              (4uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_GPIO_REG_SW_SEL_GPIO_FLD_SW_CSD_SHIELD                             (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_GPIO_REG_SW_SEL_GPIO_FLD_SW_CSD_MUTUAL                             (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_GPIO_REG_SW_SEL_GPIO_FLD_SW_CSD_POLARITY                           (2uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_GPIO_REG_SW_SEL_GPIO_FLD_SW_CSD_CHARGE                             (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_GPIO_REG_SW_SEL_GPIO_FLD_SW_DSI_CMOD                               (3uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_GPIO_REG_SW_SEL_GPIO_FLD_SW_DSI_CSH_TANK                           (3uL)

/* SW_SEL_GPIO Register for CSX SM */
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_GPIO_REG_SW_SEL_GPIO_FLD_SW_CSD_SENSE                              (5uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_GPIO_REG_SW_SEL_GPIO_FLD_SW_CSD_SHIELD                             (6uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_GPIO_REG_SW_SEL_GPIO_FLD_SW_CSD_MUTUAL                             (1uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_GPIO_REG_SW_SEL_GPIO_FLD_SW_CSD_POLARITY                           (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_GPIO_REG_SW_SEL_GPIO_FLD_SW_CSD_CHARGE                             (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_GPIO_REG_SW_SEL_GPIO_FLD_SW_DSI_CMOD                               (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_GPIO_REG_SW_SEL_GPIO_FLD_SW_DSI_CSH_TANK                           (0uL)

/* SW_SEL_CSW0 Register */
/* CSW0 = RX Electrode */
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW0_FLD_SW_SNCA                               (2uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW0_FLD_SW_SNCB                               (2uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW0_FLD_SW_SNCC                               (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW0_FLD_SW_SNCV                               (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW0_FLD_SW_SNCG                               (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW0_FLD_REF_MODE                              (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW0_FLD_ENABLED                               (1uL)

/* SW_SEL_CSW1 Register */
/* CSW1 = Positive TX Electrode */
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW1_FLD_SW_SNCA                               (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW1_FLD_SW_SNCB                               (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW1_FLD_SW_SNCC                               (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW1_FLD_SW_SNCV                               (6uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW1_FLD_SW_SNCG                               (8uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW1_FLD_REF_MODE                              (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW1_FLD_ENABLED                               (0uL)

/* SW_SEL_CSW2 Register */
/* CSW2 = Negative TX Electrode */
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW2_FLD_SW_SNCA                               (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW2_FLD_SW_SNCB                               (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW2_FLD_SW_SNCC                               (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW2_FLD_SW_SNCV                               (7uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW2_FLD_SW_SNCG                               (7uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW2_FLD_REF_MODE                              (0uL)
#define CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW2_FLD_ENABLED                               (0uL)

/* SW_SEL_CSW3 Register */
/* CSW3 = CSD Sensor Electrode */
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW3_FLD_SW_SNCA                               (3uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW3_FLD_SW_SNCB                               (3uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW3_FLD_SW_SNCC                               (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW3_FLD_SW_SNCV                               (2uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW3_FLD_SW_SNCG                               (4uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW3_FLD_REF_MODE                              (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW3_FLD_ENABLED                               (1uL)

/* SW_SEL_CSW4 Register */
/* CSW4 = GND state */
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW4_FLD_SW_SNCA                               (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW4_FLD_SW_SNCB                               (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW4_FLD_SW_SNCC                               (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW4_FLD_SW_SNCV                               (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW4_FLD_SW_SNCG                               (1uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW4_FLD_REF_MODE                              (0uL)
#define CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW4_FLD_ENABLED                               (0uL)

/* SW_SEL_CSW5 Register */
/* CSW5 = High-Z state */
#define CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW5_FLD_SW_SNCA                                   (0uL)
#define CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW5_FLD_SW_SNCB                                   (0uL)
#define CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW5_FLD_SW_SNCC                                   (0uL)
#define CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW5_FLD_SW_SNCV                                   (0uL)
#define CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW5_FLD_SW_SNCG                                   (0uL)
#define CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW5_FLD_REF_MODE                                  (0uL)
#define CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW5_FLD_ENABLED                                   (0uL)

/* SW_SEL_CSW6 Register */
/* CSW6 = VDDA/2 state */
#define CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW6_FLD_SW_SNCA                                   (0uL)
#define CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW6_FLD_SW_SNCB                                   (0uL)
#define CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW6_FLD_SW_SNCC                                   (1uL)
#define CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW6_FLD_SW_SNCV                                   (0uL)
#define CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW6_FLD_SW_SNCG                                   (0uL)
#define CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW6_FLD_REF_MODE                                  (1uL)
#define CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW6_FLD_ENABLED                                   (1uL)


#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_M0S8MSCV3 */

#endif /* CY_CAPSENSE_SM_BASE_FULL_WAVE_V3_H */


/* [] END OF FILE */
