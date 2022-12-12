/***************************************************************************//**
* \file cy_capsense_sensing_v2.h
* \version 3.0
*
* \brief
* This file provides the function prototypes specific to the sensing module.
*
********************************************************************************
* \copyright
* Copyright 2018-2021, Cypress Semiconductor Corporation (an Infineon company)
* or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_CAPSENSE_SENSING_V2_H)
#define CY_CAPSENSE_SENSING_V2_H

#include "cy_gpio.h"
#include "cy_syslib.h"
#include "cy_sysclk.h"
#include "cy_capsense_common.h"
#include "cy_capsense_structure.h"
#include "cycfg_capsense_defines.h"

#if (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2))

#if defined(__cplusplus)
extern "C" {
#endif


/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************/
/** \addtogroup group_capsense_high_level *//** \{ */
/******************************************************************************/

cy_capsense_status_t Cy_CapSense_SetupWidget(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_Scan(
                cy_stc_capsense_context_t * context);

/** \} */

/******************************************************************************/
/** \addtogroup group_capsense_low_level *//** \{ */
/******************************************************************************/

cy_capsense_status_t Cy_CapSense_SetupWidgetExt(
                uint32_t widgetId,
                uint32_t sensorId,
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_ScanExt(
                cy_stc_capsense_context_t * context);

/** \} */

/******************************************************************************/
/** \cond SECTION_CAPSENSE_INTERNAL */
/** \addtogroup group_capsense_internal *//** \{ */
/******************************************************************************/
cy_capsense_status_t Cy_CapSense_ScanWidget_V2(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_ScanSensor_V2(
                uint32_t widgetId,
                uint32_t sensorId,
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_ScanAllWidgets_V2(
                cy_stc_capsense_context_t * context);
uint32_t Cy_CapSense_IsBusy_V2(
                const cy_stc_capsense_context_t * context);
void Cy_CapSense_InterruptHandler_V2(
                const CSD_Type * base,
                cy_stc_capsense_context_t * context);

#if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CALIBRATION_EN) || \
     (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN))
    cy_capsense_status_t Cy_CapSense_CalibrateWidget_V2(
                    uint32_t widgetId,
                    cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_CalibrateAllWidgets_V2(
                cy_stc_capsense_context_t * context);
#endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CALIBRATION_EN) || \
           (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN)) */

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CALIBRATION_EN)
cy_capsense_status_t Cy_CapSense_CalibrateAllCsdWidgets(
                cy_stc_capsense_context_t * context);
#endif

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN)
cy_capsense_status_t Cy_CapSense_CalibrateAllCsxWidgets(
                cy_stc_capsense_context_t * context);
#endif

cy_capsense_status_t Cy_CapSense_SetPinState_V2(
                uint32_t widgetId,
                uint32_t sensorElement,
                uint32_t state,
                const cy_stc_capsense_context_t * context);
void Cy_CapSense_SetBusyFlags(
                cy_stc_capsense_context_t * context);
void Cy_CapSense_ClrBusyFlags(
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_SsInitialize(
                cy_stc_capsense_context_t * context);
void Cy_CapSense_SsPostAllWidgetsScan(
                cy_stc_capsense_context_t * context);
void Cy_CapSense_SetIOsInDesiredState(
                uint32_t desiredDriveMode,
                uint32_t desiredPinOutput,
                en_hsiom_sel_t desiredHsiom,
                const cy_stc_capsense_context_t * context);
void Cy_CapSense_SetSpecificIOsInDefaultState(
                const cy_stc_capsense_context_t * context);
cy_en_capsense_return_status_t Cy_CapSense_SwitchSensingMode(
                uint8_t mode,
                cy_stc_capsense_context_t * context);

#if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_SMARTSENSE_FULL_EN) || \
     (CY_CAPSENSE_ENABLE == CY_CAPSENSE_SMARTSENSE_HW_EN))
cy_capsense_status_t Cy_CapSense_SsAutoTune(
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_SsAutoTuneWidget(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context);
#endif

void Cy_CapSense_InitializeSourceSenseClk(
                const cy_stc_capsense_context_t * context);
uint32_t Cy_CapSense_SsCalcLfsrSize(
                uint32_t clkDivider,
                uint32_t conversionsNum);

void Cy_CapSense_DischargeExtCapacitors(
                cy_stc_capsense_context_t * context);
void Cy_CapSense_InitActivePtrSns(
                uint32_t sensorId,
                cy_stc_capsense_context_t * context);
void Cy_CapSense_InitActivePtrWd(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context);
void Cy_CapSense_InitActivePtr(
                uint32_t widgetId,
                uint32_t sensorId,
                cy_stc_capsense_context_t * context);
void Cy_CapSense_SsConfigPinRegisters(
                GPIO_PRT_Type * base,
                uint32_t pinNum,
                uint32_t dm,
                en_hsiom_sel_t hsiom);
void Cy_CapSense_SsReadPinRegisters(
                GPIO_PRT_Type * base,
                uint32_t pinNum,
                uint32_t *dm,
                en_hsiom_sel_t *hsiom);
void Cy_CapSense_SetClkDivider(
                uint32_t dividerValue,
                const cy_stc_capsense_context_t * context);
uint32_t Cy_CapSense_WatchdogCyclesNum(
                uint32_t desiredTimeUs,
                uint32_t cpuFreqMHz,
                uint32_t cyclesPerLoop);
#if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CALIBRATION_EN) ||\
     (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN))
cy_capsense_status_t Cy_CapSense_CalibrateCheck(
                uint32_t widgetId,
                uint32_t target,
                uint32_t senseMethod,
                const cy_stc_capsense_context_t * context);
#endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CALIBRATION_EN) ||\
           (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN)) */
uint32_t Cy_CapSense_GetVrefAutoMv(
                const cy_stc_capsense_context_t * context);
uint32_t Cy_CapSense_GetVrefHighGain(
                uint32_t vrefDesiredMv,
                const cy_stc_capsense_context_t * context);
uint32_t Cy_CapSense_GetVrefHighMv(
                uint32_t vrefGain,
                const cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_InternalPreCalculation(
                cy_stc_capsense_context_t * context);
uint32_t Cy_CapSense_WaitForSeqIdle(
                uint32_t watchdogCycleNum,
                const cy_stc_capsense_context_t * context);
uint32_t Cy_CapSense_WaitEndOfScan(
                uint32_t watchdogCycleNum,
                const cy_stc_capsense_context_t * context);
/** \} \endcond */


#if (CY_CAPSENSE_DISABLE == CY_CAPSENSE_USE_CAPTURE)

/*******************************************************************************
* Local definition
*******************************************************************************/
/*
 *  Definition of the default configuration of the CSD HW registers that is
 *  intended to be used on the CSD HW block capturing stage.
 *  The configuration includes:
 *  1. Start of the analog settling process:
 *      - Enables the CSD HW block;
 *      - Enables all the modules of the CSD HW block (AMBUF, REFGEN, CSDCMP, HSCMP);
 *      - Enables the Sense Modulator output;
 *  2. Clear all of the pending interrupt requests of the CSD HW block (SAMPLE, INIT, ADC_RES);
 *  3. Sets into default state the rest of the CSD HW block registers which are not related
 *     to actions #1 and #2.
*/
    #define CY_CAPSENSE_CSD_CONFIG_DEFAULT  {\
    .config         = 0x84001000uL, /* ENABLE = "1", SENSE_EN = "1". Set other fields into default state. */\
    .spare          = 0x00000000uL, /* Set all fields into default state. */                                \
    .status         = 0x00000000uL, /* Set all fields into default state. */                                \
    .statSeq        = 0x00000000uL, /* Set all fields into default state. */                                \
    .statCnts       = 0x00000000uL, /* Set all fields into default state. */                                \
    .statHcnt       = 0x00000000uL, /* Set all fields into default state. */                                \
    .resultVal1     = 0x00000000uL, /* Set all fields into default state. */                                \
    .resultVal2     = 0x00000000uL, /* Set all fields into default state. */                                \
    .adcRes         = 0x00000000uL, /* Set all fields into default state. */                                \
    .intr           = 0x00000106uL, /* SAMPLE = "1", INIT = "1", ADC_RES = "1". */                          \
    .intrSet        = 0x00000000uL, /* Set all fields into default state. */                                \
    .intrMask       = 0x00000000uL, /* Set all fields into default state. */                                \
    .intrMasked     = 0x00000000uL, /* Set all fields into default state. */                                \
    .hscmp          = 0x00000001uL, /* HSCMP_EN  = "1". Set all other fields into default state. */         \
    .ambuf          = 0x00000001uL, /* PWR_MODE  = "1". Set all other fields into default state. */         \
    .refgen         = 0x00000001uL, /* REFGEN_EN = "1". Set all other fields into default state. */         \
    .csdCmp         = 0x00000001uL, /* CSDCMP_EN = "1". Set all other fields into default state. */         \
    .swRes          = 0x00000000uL, /* Set all fields into default state. */                                \
    .sensePeriod    = 0x0C000000uL, /* Set all fields into default state. */                                \
    .senseDuty      = 0x00000000uL, /* Set all fields into default state. */                                \
    .swHsPosSel     = 0x00000000uL, /* Set all fields into default state. */                                \
    .swHsNegSel     = 0x00000000uL, /* Set all fields into default state. */                                \
    .swShieldSel    = 0x00000000uL, /* Set all fields into default state. */                                \
    .swAmuxbufSel   = 0x00000000uL, /* Set all fields into default state. */                                \
    .swBypSel       = 0x00000000uL, /* Set all fields into default state. */                                \
    .swCmpPosSel    = 0x00000000uL, /* Set all fields into default state. */                                \
    .swCmpNegSel    = 0x00000000uL, /* Set all fields into default state. */                                \
    .swRefgenSel    = 0x00000000uL, /* Set all fields into default state. */                                \
    .swFwModSel     = 0x00000000uL, /* Set all fields into default state. */                                \
    .swFwTankSel    = 0x00000000uL, /* Set all fields into default state. */                                \
    .swDsiSel       = 0x00000000uL, /* Set all fields into default state. */                                \
    .ioSel          = 0x00000000uL, /* Set all fields into default state. */                                \
    .seqTime        = 0x00000000uL, /* Set all fields into default state. */                                \
    .seqInitCnt     = 0x00000000uL, /* Set all fields into default state. */                                \
    .seqNormCnt     = 0x00000000uL, /* Set all fields into default state. */                                \
    .adcCtl         = 0x00000000uL, /* Set all fields into default state. */                                \
    .seqStart       = 0x00000000uL, /* Set all fields into default state. */                                \
    .idacA          = 0x00000000uL, /* Set all fields into default state. */                                \
    .idacB          = 0x00000000uL, /* Set all fields into default state. */                                \
    }

    extern const cy_stc_csd_config_t cy_capsense_csdCfg;
#endif


/*******************************************************************************
* CSD HW Waveform Selection values
*******************************************************************************/
#define CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN                    (0x00000000uL)
#define CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED                  (0x00000001uL)
#define CY_CAPSENSE_CSD_WAVEFORM_PHI1                           (0x00000002uL)
#define CY_CAPSENSE_CSD_WAVEFORM_PHI2                           (0x00000003uL)
#define CY_CAPSENSE_CSD_WAVEFORM_PHI1_HSCMP                     (0x00000004uL)
#define CY_CAPSENSE_CSD_WAVEFORM_PHI2_HSCMP                     (0x00000005uL)
#define CY_CAPSENSE_CSD_WAVEFORM_HSCMP                          (0x00000006uL)
#define CY_CAPSENSE_CSD_WAVEFORM_SENSE_INV                      (0x00000007uL)
#define CY_CAPSENSE_CSD_WAVEFORM_PHI1_DELAY                     (0x00000008uL)
#define CY_CAPSENSE_CSD_WAVEFORM_PHI2_DELAY                     (0x00000009uL)
#define CY_CAPSENSE_CSD_WAVEFORM_PHI1_INV                       (0x0000000AuL)
#define CY_CAPSENSE_CSD_WAVEFORM_PHI2_INV                       (0x0000000BuL)
#define CY_CAPSENSE_CSD_WAVEFORM_PHI1_HSCMP_INV                 (0x0000000CuL)
#define CY_CAPSENSE_CSD_WAVEFORM_PHI2_HSCMP_INV                 (0x0000000DuL)
#define CY_CAPSENSE_CSD_WAVEFORM_HSCMP_INV                      (0x0000000EuL)
#define CY_CAPSENSE_CSD_WAVEFORM_SENSE                          (0x0000000FuL)


/*******************************************************************************
* CSD HW Block Register Mask Definition
*******************************************************************************/

/* CSD_CONFIG register masks */
#if (CY_CAPSENSE_PSOC6_FOURTH_GEN)
    #define CY_CAPSENSE_CSD_CONFIG_IREF_SEL_MSK                 (CSD_CONFIG_IREF_SEL_Msk)
#endif

#define CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_2_CYCLES            (0x00000002uL)
#define CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_3_CYCLES            (0x00000003uL)
#define CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_4_CYCLES            (0x00000004uL)
#define CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_POS                 (CSD_CONFIG_FILTER_DELAY_Pos)
#define CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_MSK                 (CSD_CONFIG_FILTER_DELAY_Msk)
#define CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_12MHZ               (CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_2_CYCLES << CSD_CONFIG_FILTER_DELAY_Pos)
#define CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_24MHZ               (CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_3_CYCLES << CSD_CONFIG_FILTER_DELAY_Pos)
#define CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_48MHZ               (CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_4_CYCLES << CSD_CONFIG_FILTER_DELAY_Pos)
#define CY_CAPSENSE_CSD_CONFIG_SHIELD_DELAY_MSK                 (CSD_CONFIG_SHIELD_DELAY_Msk)
#define CY_CAPSENSE_CSD_CONFIG_SHIELD_DELAY_POS                 (CSD_CONFIG_SHIELD_DELAY_Pos)
#define CY_CAPSENSE_CSD_CONFIG_SENSE_EN_MSK                     (CSD_CONFIG_SENSE_EN_Msk)
#define CY_CAPSENSE_CSD_CONFIG_DSI_COUNT_SEL_POS                (CSD_CONFIG_DSI_COUNT_SEL_Pos)
#define CY_CAPSENSE_CSD_CONFIG_DSI_COUNT_SEL_MSK                (CSD_CONFIG_DSI_COUNT_SEL_Msk)
#define CY_CAPSENSE_CSD_CONFIG_SAMPLE_SYNC_MSK                  (CSD_CONFIG_SAMPLE_SYNC_Msk)
#define CY_CAPSENSE_CSD_CONFIG_ENABLE_MSK                       (CSD_CONFIG_ENABLE_Msk)

/* CSD_STAT_SEQ register masks */
#define CY_CAPSENSE_CSD_STAT_SEQ_SEQ_STATE_MSK                  (CSD_STAT_SEQ_SEQ_STATE_Msk)

/* CSD_DSI_SEL register masks */
#define CY_CAPSENSE_CSD_SW_DSI_SEL_CSH_TANK_MSK                 (0x00000001uL)
#define CY_CAPSENSE_CSD_SW_DSI_SEL_CMOD_MSK                     (0x00000010uL)

/* CSD_RESULT_VAL1 register masks */
#define CY_CAPSENSE_CSD_RESULT_VAL1_VALUE_MSK                   (CSD_RESULT_VAL1_VALUE_Msk)
#define CY_CAPSENSE_CSD_RESULT_VAL1_BAD_CONVS_MSK               (CSD_RESULT_VAL1_BAD_CONVS_Msk)
#define CY_CAPSENSE_CSD_RESULT_VAL1_BAD_CONVS_POS               (CSD_RESULT_VAL1_BAD_CONVS_Pos)

/* CSD_RESULT_VAL2 register masks */
#define CY_CAPSENSE_CSD_RESULT_VAL2_VALUE_MSK                   (CSD_RESULT_VAL2_VALUE_Msk)

/* CSD_ADC_RES register masks */
#define CY_CAPSENSE_CSD_ADC_RES_VALUE_MSK                       (CSD_ADC_RES_VIN_CNT_Msk)
#define CY_CAPSENSE_CSD_ADC_RES_ADC_OVERFLOW_MSK                (CSD_ADC_RES_ADC_OVERFLOW_Msk)

/* CSD_ADC_CTL register masks */
#define CY_CAPSENSE_CSD_ADC_CTL_ADC_MODE_MSK                    (CSD_ADC_CTL_ADC_MODE_Msk)

/* CSD_INTR register masks */
#define CY_CAPSENSE_CSD_INTR_SAMPLE_MSK                         (CSD_INTR_SAMPLE_Msk)
#define CY_CAPSENSE_CSD_INTR_INIT_MSK                           (CSD_INTR_INIT_Msk)
#define CY_CAPSENSE_CSD_INTR_ADC_RES_MSK                        (CSD_INTR_ADC_RES_Msk)
#define CY_CAPSENSE_CSD_INTR_ALL_MSK                            (CSD_INTR_SAMPLE_Msk | CSD_INTR_INIT_Msk | CSD_INTR_ADC_RES_Msk)

/* CSD_INTR_MASK register masks */
#define CY_CAPSENSE_CSD_INTR_MASK_SAMPLE_MSK                    (CSD_INTR_MASK_SAMPLE_Msk)
#define CY_CAPSENSE_CSD_INTR_MASK_INIT_MSK                      (CSD_INTR_MASK_INIT_Msk)
#define CY_CAPSENSE_CSD_INTR_MASK_ADC_RES_MSK                   (CSD_INTR_MASK_ADC_RES_Msk)
#define CY_CAPSENSE_CSD_INTR_MASK_CLEAR_MSK                     (0uL)

/* CSD_HSCMP register masks */
#define CY_CAPSENSE_CSD_HSCMP_HSCMP_EN_MSK                      (CSD_HSCMP_HSCMP_EN_Msk)
#define CY_CAPSENSE_CSD_HSCMP_HSCMP_INVERT_MSK                  (CSD_HSCMP_HSCMP_INVERT_Msk)
#define CY_CAPSENSE_CSD_HSCMP_AZ_EN_MSK                         (CSD_HSCMP_AZ_EN_Msk)

/* CSD_AMBUF register masks */
#define CY_CAPSENSE_CSD_AMBUF_PWR_MODE_OFF                      (0uL)
#define CY_CAPSENSE_CSD_AMBUF_PWR_MODE_NORM                     (1uL)
#define CY_CAPSENSE_CSD_AMBUF_PWR_MODE_HI                       (2uL)

/* CSD_REFGEN register masks */
#define CY_CAPSENSE_CSD_REFGEN_REFGEN_EN_MSK                    (CSD_REFGEN_REFGEN_EN_Msk)
#define CY_CAPSENSE_CSD_REFGEN_BYPASS_MSK                       (CSD_REFGEN_BYPASS_Msk)
#define CY_CAPSENSE_CSD_REFGEN_VDDA_EN_MSK                      (CSD_REFGEN_VDDA_EN_Msk)
#define CY_CAPSENSE_CSD_REFGEN_RES_EN_MSK                       (CSD_REFGEN_RES_EN_Msk)
#define CY_CAPSENSE_CSD_REFGEN_GAIN_POS                         (CSD_REFGEN_GAIN_Pos)
#define CY_CAPSENSE_CSD_REFGEN_GAIN_MSK                         (CSD_REFGEN_GAIN_Msk)
#define CY_CAPSENSE_CSD_REFGEN_VREFLO_SEL_MSK                   (CSD_REFGEN_VREFLO_SEL_Msk)
#define CY_CAPSENSE_CSD_REFGEN_VREFLO_INT_MSK                   (CSD_REFGEN_VREFLO_INT_Msk)

#define CY_CAPSENSE_VREF_HI_OVERSHOOT_CORRECTION                (0x00000001uL)

/* CSD_CSDCMP register masks */
#define CY_CAPSENSE_CSD_CSDCMP_CSDCMP_EN_MSK                    (CSD_CSDCMP_CSDCMP_EN_Msk)
#define CY_CAPSENSE_CSD_CSDCMP_CMP_PHASE_PHI2_MSK               (0x0200u)

/* CSD_SENSE_PERIOD register masks */
#define CY_CAPSENSE_CSD_SENSE_PERIOD_SENSE_DIV_MSK              (CSD_SENSE_PERIOD_SENSE_DIV_Msk)
#define CY_CAPSENSE_CSD_SENSE_PERIOD_LFSR_SIZE_MSK              (CSD_SENSE_PERIOD_LFSR_SIZE_Msk)
#define CY_CAPSENSE_CSD_SENSE_PERIOD_LFSR_SIZE_POS              (CSD_SENSE_PERIOD_LFSR_SIZE_Pos)
#define CY_CAPSENSE_CSD_SENSE_PERIOD_LFSR_SCALE_MSK             (CSD_SENSE_PERIOD_LFSR_SCALE_Msk)
#define CY_CAPSENSE_CSD_SENSE_PERIOD_LFSR_CLEAR_MSK             (CSD_SENSE_PERIOD_LFSR_CLEAR_Msk)
#define CY_CAPSENSE_CSD_SENSE_PERIOD_SEL_LFSR_MSB_MSK           (CSD_SENSE_PERIOD_SEL_LFSR_MSB_Msk)
#define CY_CAPSENSE_CSD_SENSE_PERIOD_LFSR_BITS_MSK              (CSD_SENSE_PERIOD_LFSR_BITS_Msk)

/* CSD_SENSE_DUTY register masks */
#define CY_CAPSENSE_CSD_SENSE_DUTY_SENSE_WIDTH_MSK              (CSD_SENSE_DUTY_SENSE_WIDTH_Msk)
#define CY_CAPSENSE_CSD_SENSE_DUTY_SENSE_POL_MSK                (CSD_SENSE_DUTY_SENSE_POL_Msk)
#define CY_CAPSENSE_CSD_SENSE_DUTY_SENSE_POL_PHI_LOW            (0uL)
#define CY_CAPSENSE_CSD_SENSE_DUTY_SENSE_POL_PHI_HIGH           (CSD_SENSE_DUTY_SENSE_POL_Msk)
#define CY_CAPSENSE_CSD_SENSE_DUTY_OVERLAP_PHI1_MSK             (CSD_SENSE_DUTY_OVERLAP_PHI1_Msk)
#define CY_CAPSENSE_CSD_SENSE_DUTY_OVERLAP_PHI2_MSK             (CSD_SENSE_DUTY_OVERLAP_PHI2_Msk)

#if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
    #define CY_CAPSENSE_CSD_SENSE_DUTY_CFG                      (CSD_SENSE_DUTY_OVERLAP_PHI1_Msk | CSD_SENSE_DUTY_OVERLAP_PHI2_Msk)
#else
    #define CY_CAPSENSE_CSD_SENSE_DUTY_CFG                      (CY_CAPSENSE_CSD_SENSE_DUTY_SENSE_POL_PHI_HIGH)
#endif

#define CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPM_STATIC_OPEN         (CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN << CSD_SW_HS_P_SEL_SW_HMPM_Pos)
#define CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE        (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_HS_P_SEL_SW_HMPM_Pos)
#define CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPT_STATIC_OPEN         (CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN << CSD_SW_HS_P_SEL_SW_HMPT_Pos)
#define CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE        (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_HS_P_SEL_SW_HMPT_Pos)
#define CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPS_STATIC_OPEN         (CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN << CSD_SW_HS_P_SEL_SW_HMPS_Pos)
#define CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE        (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_HS_P_SEL_SW_HMPS_Pos)
#define CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMMA_STATIC_OPEN         (CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN << CSD_SW_HS_P_SEL_SW_HMMA_Pos)
#define CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMMA_STATIC_CLOSE        (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_HS_P_SEL_SW_HMMA_Pos)
#define CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMMB_STATIC_OPEN         (CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN << CSD_SW_HS_P_SEL_SW_HMMB_Pos)
#define CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE        (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_HS_P_SEL_SW_HMMB_Pos)
#define CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMRH_STATIC_OPEN         (CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN << CSD_SW_HS_P_SEL_SW_HMRH_Pos)
#define CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMRH_STATIC_CLOSE        (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_HS_P_SEL_SW_HMRH_Pos)

#define CY_CAPSENSE_CSD_SW_HS_N_SEL_SW_HCRH_STATIC_OPEN         (CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN << CSD_SW_HS_N_SEL_SW_HCRH_Pos)
#define CY_CAPSENSE_CSD_SW_HS_N_SEL_SW_HCRH_STATIC_CLOSE        (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_HS_N_SEL_SW_HCRH_Pos)
#define CY_CAPSENSE_CSD_SW_HS_N_SEL_SW_HCRL_STATIC_OPEN         (CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN << CSD_SW_HS_N_SEL_SW_HCRL_Pos)
#define CY_CAPSENSE_CSD_SW_HS_N_SEL_SW_HCRL_STATIC_CLOSE        (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_HS_N_SEL_SW_HCRL_Pos)
#define CY_CAPSENSE_CSD_SW_HS_N_SEL_SW_HCCD_STATIC_OPEN         (CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN << CSD_SW_HS_N_SEL_SW_HCCD_Pos)
#define CY_CAPSENSE_CSD_SW_HS_N_SEL_SW_HCCD_STATIC_CLOSE        (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_HS_N_SEL_SW_HCCD_Pos)

#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCAV_HSCMP             (CY_CAPSENSE_CSD_WAVEFORM_HSCMP << CSD_SW_SHIELD_SEL_SW_HCAV_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCAV_PHI1              (CY_CAPSENSE_CSD_WAVEFORM_PHI1 << CSD_SW_SHIELD_SEL_SW_HCAV_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCAV_PHI2              (CY_CAPSENSE_CSD_WAVEFORM_PHI2 << CSD_SW_SHIELD_SEL_SW_HCAV_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCAV_PHI1_HSCMP        (CY_CAPSENSE_CSD_WAVEFORM_PHI1_HSCMP << CSD_SW_SHIELD_SEL_SW_HCAV_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCAV_PHI2_HSCMP        (CY_CAPSENSE_CSD_WAVEFORM_PHI2_HSCMP << CSD_SW_SHIELD_SEL_SW_HCAV_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCAV_STATIC_OPEN       (CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN << CSD_SW_SHIELD_SEL_SW_HCAV_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCAV_STATIC_CLOSE      (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_SHIELD_SEL_SW_HCAV_Pos)

#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCAG_HSCMP             (CY_CAPSENSE_CSD_WAVEFORM_HSCMP << CSD_SW_SHIELD_SEL_SW_HCAG_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCAG_PHI1              (CY_CAPSENSE_CSD_WAVEFORM_PHI1 << CSD_SW_SHIELD_SEL_SW_HCAG_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCAG_PHI2              (CY_CAPSENSE_CSD_WAVEFORM_PHI2 << CSD_SW_SHIELD_SEL_SW_HCAG_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCAG_PHI1_HSCMP        (CY_CAPSENSE_CSD_WAVEFORM_PHI1_HSCMP << CSD_SW_SHIELD_SEL_SW_HCAG_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCAG_PHI2_HSCMP        (CY_CAPSENSE_CSD_WAVEFORM_PHI2_HSCMP << CSD_SW_SHIELD_SEL_SW_HCAG_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCAG_STATIC_OPEN       (CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN << CSD_SW_SHIELD_SEL_SW_HCAG_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCAG_STATIC_CLOSE      (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_SHIELD_SEL_SW_HCAG_Pos)

#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBV_HSCMP             (CY_CAPSENSE_CSD_WAVEFORM_HSCMP << CSD_SW_SHIELD_SEL_SW_HCBV_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBV_PHI1              (CY_CAPSENSE_CSD_WAVEFORM_PHI1 << CSD_SW_SHIELD_SEL_SW_HCBV_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBV_PHI2              (CY_CAPSENSE_CSD_WAVEFORM_PHI2 << CSD_SW_SHIELD_SEL_SW_HCBV_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBV_PHI1_HSCMP        (CY_CAPSENSE_CSD_WAVEFORM_PHI1_HSCMP << CSD_SW_SHIELD_SEL_SW_HCBV_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBV_PHI2_HSCMP        (CY_CAPSENSE_CSD_WAVEFORM_PHI2_HSCMP << CSD_SW_SHIELD_SEL_SW_HCBV_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBV_STATIC_OPEN       (CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN << CSD_SW_SHIELD_SEL_SW_HCBV_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBV_STATIC_CLOSE      (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_SHIELD_SEL_SW_HCBV_Pos)

#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBG_HSCMP             (CY_CAPSENSE_CSD_WAVEFORM_HSCMP << CSD_SW_SHIELD_SEL_SW_HCBG_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBG_PHI1              (CY_CAPSENSE_CSD_WAVEFORM_PHI1 << CSD_SW_SHIELD_SEL_SW_HCBG_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBG_PHI2              (CY_CAPSENSE_CSD_WAVEFORM_PHI2 << CSD_SW_SHIELD_SEL_SW_HCBG_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBG_PHI1_HSCMP        (CY_CAPSENSE_CSD_WAVEFORM_PHI1_HSCMP << CSD_SW_SHIELD_SEL_SW_HCBG_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBG_PHI2_HSCMP        (CY_CAPSENSE_CSD_WAVEFORM_PHI2_HSCMP << CSD_SW_SHIELD_SEL_SW_HCBG_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBG_STATIC_OPEN       (CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN << CSD_SW_SHIELD_SEL_SW_HCBG_Pos)
#define CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBG_STATIC_CLOSE      (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_SHIELD_SEL_SW_HCBG_Pos)

#define CY_CAPSENSE_CSD_SW_AMUXBUF_SEL_SW_IRLB_STATIC_CLOSE     (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_AMUXBUF_SEL_SW_IRLB_Pos)
#define CY_CAPSENSE_CSD_SW_AMUXBUF_SEL_SW_IRH_STATIC_CLOSE      (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_AMUXBUF_SEL_SW_IRH_Pos)
#define CY_CAPSENSE_CSD_SW_AMUXBUF_SEL_SW_ICB_PHI2              (CY_CAPSENSE_CSD_WAVEFORM_PHI2 << CSD_SW_AMUXBUF_SEL_SW_ICB_Pos)
#define CY_CAPSENSE_CSD_SW_AMUXBUF_SEL_SW_DEFAULT               (CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN)

/* CSD_SW_BYP_SEL register masks */
#define CY_CAPSENSE_CSD_SW_BYP_SEL_SW_BYA_MSK                   (CSD_SW_BYP_SEL_SW_BYA_Msk)
#define CY_CAPSENSE_CSD_SW_BYP_SEL_SW_BYB_MSK                   (CSD_SW_BYP_SEL_SW_BYB_Msk)

#define CY_CAPSENSE_CSD_SW_CMP_P_SEL_SW_SFPM_STATIC_OPEN        (CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN << CSD_SW_CMP_P_SEL_SW_SFPM_Pos)
#define CY_CAPSENSE_CSD_SW_CMP_P_SEL_SW_SFPM_STATIC_CLOSE       (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_CMP_P_SEL_SW_SFPM_Pos)
#define CY_CAPSENSE_CSD_SW_CMP_P_SEL_SW_SFPT_STATIC_OPEN        (CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN << CSD_SW_CMP_P_SEL_SW_SFPT_Pos)
#define CY_CAPSENSE_CSD_SW_CMP_P_SEL_SW_SFPT_STATIC_CLOSE       (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_CMP_P_SEL_SW_SFPT_Pos)
#define CY_CAPSENSE_CSD_SW_CMP_P_SEL_SW_SFPS_STATIC_OPEN        (CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN << CSD_SW_CMP_P_SEL_SW_SFPS_Pos)
#define CY_CAPSENSE_CSD_SW_CMP_P_SEL_SW_SFPS_STATIC_CLOSE       (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_CMP_P_SEL_SW_SFPS_Pos)
#define CY_CAPSENSE_CSD_SW_CMP_P_SEL_SW_SFMA_STATIC_OPEN        (CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN << CSD_SW_CMP_P_SEL_SW_SFMA_Pos)
#define CY_CAPSENSE_CSD_SW_CMP_P_SEL_SW_SFMA_STATIC_CLOSE       (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_CMP_P_SEL_SW_SFMA_Pos)
#define CY_CAPSENSE_CSD_SW_CMP_P_SEL_SW_SFCA_STATIC_OPEN        (CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN << CSD_SW_CMP_P_SEL_SW_SFCA_Pos)
#define CY_CAPSENSE_CSD_SW_CMP_P_SEL_SW_SFCA_STATIC_CLOSE       (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_CMP_P_SEL_SW_SFCA_Pos)
#define CY_CAPSENSE_CSD_SW_CMP_P_SEL_SW_SFCA_MSK                (CSD_SW_CMP_P_SEL_SW_SFCA_Msk)

#define CY_CAPSENSE_CSD_SW_CMP_N_SEL_SW_SCRH_STATIC_OPEN        (CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN << CSD_SW_CMP_N_SEL_SW_SCRH_Pos)
#define CY_CAPSENSE_CSD_SW_CMP_N_SEL_SW_SCRH_STATIC_CLOSE       (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_CMP_N_SEL_SW_SCRH_Pos)
#define CY_CAPSENSE_CSD_SW_CMP_N_SEL_SW_SCRL_STATIC_OPEN        (CY_CAPSENSE_CSD_WAVEFORM_STATIC_OPEN << CSD_SW_CMP_N_SEL_SW_SCRL_Pos)
#define CY_CAPSENSE_CSD_SW_CMP_N_SEL_SW_SCRL_STATIC_CLOSE       (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_CMP_N_SEL_SW_SCRL_Pos)

/* CSD_SW_REFGEN_SEL register masks */
#define CY_CAPSENSE_CSD_SW_REFGEN_SEL_SW_IAIB_MSK               (CSD_SW_REFGEN_SEL_SW_IAIB_Msk)
#define CY_CAPSENSE_CSD_SW_REFGEN_SEL_SW_IBCB_MSK               (CSD_SW_REFGEN_SEL_SW_IBCB_Msk)
#define CY_CAPSENSE_CSD_SW_REFGEN_SEL_SW_SGMB_MSK               (CSD_SW_REFGEN_SEL_SW_SGMB_Msk)
#define CY_CAPSENSE_CSD_SW_REFGEN_SEL_SW_SGRP_MSK               (CSD_SW_REFGEN_SEL_SW_SGRP_Msk)
#define CY_CAPSENSE_CSD_SW_REFGEN_SEL_SW_SGRE_MSK               (CSD_SW_REFGEN_SEL_SW_SGRE_Msk)
#define CY_CAPSENSE_CSD_SW_REFGEN_SEL_SW_SGR_MSK                (CSD_SW_REFGEN_SEL_SW_SGR_Msk)

#define CY_CAPSENSE_CSD_SW_FW_MOD_SEL_SW_F1PM_MSK               (CSD_SW_FW_MOD_SEL_SW_F1PM_Msk)
#define CY_CAPSENSE_CSD_SW_FW_MOD_SEL_SW_F1PM_STATIC_CLOSE      (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_FW_MOD_SEL_SW_F1PM_Pos)
#define CY_CAPSENSE_CSD_SW_FW_MOD_SEL_SW_F1MA_MSK               (CSD_SW_FW_MOD_SEL_SW_F1MA_Msk)
#define CY_CAPSENSE_CSD_SW_FW_MOD_SEL_SW_F1MA_STATIC_CLOSE      (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_FW_MOD_SEL_SW_F1MA_Pos)
#define CY_CAPSENSE_CSD_SW_FW_MOD_SEL_SW_F1CA_MSK               (CSD_SW_FW_MOD_SEL_SW_F1CA_Msk)
#define CY_CAPSENSE_CSD_SW_FW_MOD_SEL_SW_F1CA_STATIC_CLOSE      (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_FW_MOD_SEL_SW_F1CA_Pos)
#define CY_CAPSENSE_CSD_SW_FW_MOD_SEL_SW_F1CA_PHI2              (CY_CAPSENSE_CSD_WAVEFORM_PHI2 << CSD_SW_FW_MOD_SEL_SW_F1CA_Pos)
#define CY_CAPSENSE_CSD_SW_FW_MOD_SEL_SW_C1CC_STATIC_OPEN       (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_FW_MOD_SEL_SW_C1CC_Pos)
#define CY_CAPSENSE_CSD_SW_FW_MOD_SEL_SW_C1CC_STATIC_CLOSE      (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_FW_MOD_SEL_SW_C1CC_Pos)
#define CY_CAPSENSE_CSD_SW_FW_MOD_SEL_SW_C1CD_STATIC_OPEN       (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_FW_MOD_SEL_SW_C1CD_Pos)
#define CY_CAPSENSE_CSD_SW_FW_MOD_SEL_SW_C1CD_STATIC_CLOSE      (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_FW_MOD_SEL_SW_C1CD_Pos)

#define CY_CAPSENSE_CSD_SW_FW_TANK_SEL_SW_F2PT_MSK              (CSD_SW_FW_TANK_SEL_SW_F2PT_Msk)
#define CY_CAPSENSE_CSD_SW_FW_TANK_SEL_SW_F2PT_STATIC_CLOSE     (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_FW_TANK_SEL_SW_F2PT_Pos)
#define CY_CAPSENSE_CSD_SW_FW_TANK_SEL_SW_F2MA_MSK              (CSD_SW_FW_TANK_SEL_SW_F2MA_Msk)
#define CY_CAPSENSE_CSD_SW_FW_TANK_SEL_SW_F2MA_STATIC_CLOSE     (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_FW_TANK_SEL_SW_F2MA_Pos)
#define CY_CAPSENSE_CSD_SW_FW_TANK_SEL_SW_F2CA_MSK              (CSD_SW_FW_TANK_SEL_SW_F2CA_Msk)
#define CY_CAPSENSE_CSD_SW_FW_TANK_SEL_SW_F2CA_STATIC_CLOSE     (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_FW_TANK_SEL_SW_F2CA_Pos)
#define CY_CAPSENSE_CSD_SW_FW_TANK_SEL_SW_F2CB_MSK              (CSD_SW_FW_TANK_SEL_SW_F2CB_Msk)
#define CY_CAPSENSE_CSD_SW_FW_TANK_SEL_SW_F2CB_STATIC_CLOSE     (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_FW_TANK_SEL_SW_F2CB_Pos)
#define CY_CAPSENSE_CSD_SW_FW_TANK_SEL_SW_F2CA_PHI2             (CY_CAPSENSE_CSD_WAVEFORM_PHI2 << CSD_SW_FW_TANK_SEL_SW_F2CA_Pos)
#define CY_CAPSENSE_CSD_SW_FW_TANK_SEL_SW_F2CB_PHI2             (CY_CAPSENSE_CSD_WAVEFORM_PHI2 << CSD_SW_FW_TANK_SEL_SW_F2CB_Pos)
#define CY_CAPSENSE_CSD_SW_FW_TANK_SEL_SW_C2CC_STATIC_OPEN      (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_FW_TANK_SEL_SW_C2CC_Pos)
#define CY_CAPSENSE_CSD_SW_FW_TANK_SEL_SW_C2CC_STATIC_CLOSE     (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_FW_TANK_SEL_SW_C2CC_Pos)
#define CY_CAPSENSE_CSD_SW_FW_TANK_SEL_SW_C2CD_STATIC_OPEN      (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_FW_TANK_SEL_SW_C2CD_Pos)
#define CY_CAPSENSE_CSD_SW_FW_TANK_SEL_SW_C2CD_STATIC_CLOSE     (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_SW_FW_TANK_SEL_SW_C2CD_Pos)

#if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
    #define CY_CAPSENSE_CSD_TX_OUT_MSK                          (0u)
    #define CY_CAPSENSE_CSD_TX_OUT_EN_PHI1_DELAY                (0u)
    #define CY_CAPSENSE_CSD_TX_AMUXB_EN_PHI2_DELAY              (0u)
    #define CY_CAPSENSE_CSD_TX_N_OUT_STATIC_CLOSE               (0u)
    #define CY_CAPSENSE_CSD_TX_N_OUT_EN_PHI1                    (0u)
    #define CY_CAPSENSE_CSD_TX_N_AMUXA_EN_PHI2                  (0u)
#else
    #define CY_CAPSENSE_CSD_TX_OUT_MSK                          (CSD_IO_SEL_CSD_TX_OUT_Msk)
    #define CY_CAPSENSE_CSD_TX_OUT_EN_PHI1_DELAY                (CY_CAPSENSE_CSD_WAVEFORM_PHI1_DELAY << 4u)
    #define CY_CAPSENSE_CSD_TX_AMUXB_EN_PHI2_DELAY              (CY_CAPSENSE_CSD_WAVEFORM_PHI2_DELAY << 12u)
    #define CY_CAPSENSE_CSD_TX_N_OUT_STATIC_CLOSE               (CY_CAPSENSE_CSD_WAVEFORM_STATIC_CLOSED << CSD_IO_SEL_CSD_TX_N_OUT_Pos)
    #define CY_CAPSENSE_CSD_TX_N_OUT_EN_PHI1                    (CY_CAPSENSE_CSD_WAVEFORM_PHI1 << CSD_IO_SEL_CSD_TX_N_OUT_EN_Pos)
    #define CY_CAPSENSE_CSD_TX_N_AMUXA_EN_PHI2                  (CY_CAPSENSE_CSD_WAVEFORM_PHI2 << CSD_IO_SEL_CSD_TX_N_AMUXA_EN_Pos)
#endif

/* CSD_SEQ_INIT_CNT register masks */
#define CY_CAPSENSE_CSD_SEQ_INIT_CNT_CONV_CNT_MSK               (CSD_SEQ_INIT_CNT_CONV_CNT_Msk)

/* CSD_SEQ_NORM_CNT register masks */
#define CY_CAPSENSE_CSD_SEQ_NORM_CNT_CONV_CNT_MSK               (CSD_SEQ_NORM_CNT_CONV_CNT_Msk)

/* CSD_SEQ_START register masks */
#define CY_CAPSENSE_CSD_SEQ_START_START_MSK                     (CSD_SEQ_START_START_Msk)
#define CY_CAPSENSE_CSD_SEQ_START_SEQ_MODE_MSK                  (CSD_SEQ_START_SEQ_MODE_Msk)
#define CY_CAPSENSE_CSD_SEQ_START_ABORT_MSK                     (CSD_SEQ_START_ABORT_Msk)
#define CY_CAPSENSE_CSD_SEQ_START_DSI_START_EN_MSK              (CSD_SEQ_START_DSI_START_EN_Msk)
#define CY_CAPSENSE_CSD_SEQ_START_AZ0_SKIP_MSK                  (CSD_SEQ_START_AZ0_SKIP_Msk)
#define CY_CAPSENSE_CSD_SEQ_START_AZ1_SKIP_MSK                  (CSD_SEQ_START_AZ1_SKIP_Msk)

#define CY_CAPSENSE_CSD_IDAC_BITS_USED                          (7u)

#define CY_CAPSENSE_CAL_MIDDLE_VALUE                            (1u << (CY_CAPSENSE_CSD_IDAC_BITS_USED - 1u))
#define CY_CAPSENSE_CAL_IDAC_MAX_VALUE                          ((uint8_t)(1u << CY_CAPSENSE_CSD_IDAC_BITS_USED) - 1u)


/* CSD_IDACA register masks */
#define CY_CAPSENSE_CSD_IDACA_VAL_MSK                           (CSD_IDACA_VAL_Msk)
#define CY_CAPSENSE_CSD_IDACA_VAL_POS                           (CSD_IDACA_VAL_Pos)

#define CY_CAPSENSE_CSD_IDACA_POL_DYN_MSK                       (CSD_IDACA_POL_DYN_Msk)
#define CY_CAPSENSE_CSD_IDACA_POL_DYN_POS                       (CSD_IDACA_POL_DYN_Pos)

#define CY_CAPSENSE_CSD_IDACA_POLARITY_MSK                      (CSD_IDACA_POLARITY_Msk)
#define CY_CAPSENSE_CSD_IDACA_POLARITY_POS                      (CSD_IDACA_POLARITY_Pos)
#define CY_CAPSENSE_CSD_IDACA_POLARITY_VSSA_SRC                 (0uL)
#define CY_CAPSENSE_CSD_IDACA_POLARITY_VDDA_SNK                 (1uL)
#define CY_CAPSENSE_CSD_IDACA_POLARITY_SENSE                    (2uL)
#define CY_CAPSENSE_CSD_IDACA_POLARITY_SENSE_INV                (3uL)

#define CY_CAPSENSE_CSD_IDACA_BALL_MODE_MSK                     (CSD_IDACA_BAL_MODE_Msk)
#define CY_CAPSENSE_CSD_IDACA_BALL_MODE_POS                     (CSD_IDACA_BAL_MODE_Pos)
#define CY_CAPSENSE_CSD_IDACA_BALL_MODE_FULL                    (0uL)
#define CY_CAPSENSE_CSD_IDACA_BALL_MODE_PHI1                    (1uL)
#define CY_CAPSENSE_CSD_IDACA_BALL_MODE_PHI2                    (2uL)
#define CY_CAPSENSE_CSD_IDACA_BALL_MODE_PHI1_2                  (3uL)

#define CY_CAPSENSE_CSD_IDACA_LEG1_MODE_MSK                     (CSD_IDACA_LEG1_MODE_Msk)
#define CY_CAPSENSE_CSD_IDACA_LEG1_MODE_POS                     (CSD_IDACA_LEG1_MODE_Pos)
#define CY_CAPSENSE_CSD_IDACA_LEG1_MODE_GP_STATIC               (0uL)
#define CY_CAPSENSE_CSD_IDACA_LEG1_MODE_GP                      (1uL)
#define CY_CAPSENSE_CSD_IDACA_LEG1_MODE_CSD_STATIC              (2uL)
#define CY_CAPSENSE_CSD_IDACA_LEG1_MODE_CSD                     (3uL)

#define CY_CAPSENSE_CSD_IDACA_LEG2_MODE_MSK                     (CSD_IDACA_LEG2_MODE_Msk)
#define CY_CAPSENSE_CSD_IDACA_LEG2_MODE_POS                     (CSD_IDACA_LEG2_MODE_Pos)
#define CY_CAPSENSE_CSD_IDACA_LEG2_MODE_GP_STATIC               (0uL)
#define CY_CAPSENSE_CSD_IDACA_LEG2_MODE_GP                      (1uL)
#define CY_CAPSENSE_CSD_IDACA_LEG2_MODE_CSD_STATIC              (2uL)
#define CY_CAPSENSE_CSD_IDACA_LEG2_MODE_CSD                     (3uL)

#define CY_CAPSENSE_CSD_IDACA_RANGE_MSK                         (CSD_IDACA_RANGE_Msk)
#define CY_CAPSENSE_CSD_IDACA_RANGE_POS                         (CSD_IDACA_RANGE_Pos)
#define CY_CAPSENSE_CSD_IDACA_RANGE_IDAC_LO                     (0uL)
#define CY_CAPSENSE_CSD_IDACA_RANGE_IDAC_MED                    (1uL)
#define CY_CAPSENSE_CSD_IDACA_RANGE_IDAC_HI                     (2uL)

#define CY_CAPSENSE_CSD_IDACA_LEG1_EN_MSK                       (CSD_IDACA_LEG1_EN_Msk)
#define CY_CAPSENSE_CSD_IDACA_LEG2_EN_MSK                       (CSD_IDACA_LEG2_EN_Msk)

/* CSD_IDACB register masks */
#define CY_CAPSENSE_CSD_IDACB_VAL_MSK                          (CSD_IDACB_VAL_Msk)
#define CY_CAPSENSE_CSD_IDACB_VAL_POS                          (CSD_IDACB_VAL_Pos)

#define CY_CAPSENSE_CSD_IDACB_POL_DYN_MSK                       (CSD_IDACB_POL_DYN_Msk)
#define CY_CAPSENSE_CSD_IDACB_POL_DYN_POS                       (CSD_IDACB_POL_DYN_Pos)
#define CY_CAPSENSE_CSD_IDACB_POL_DYN_STATIC                    (0uL)
#define CY_CAPSENSE_CSD_IDACB_POL_DYN_DYNAMIC                   (1uL)

#define CY_CAPSENSE_CSD_IDACB_POLARITY_MSK                      (CSD_IDACB_POLARITY_Msk)
#define CY_CAPSENSE_CSD_IDACB_POLARITY_POS                      (CSD_IDACB_POLARITY_Pos)
#define CY_CAPSENSE_CSD_IDACB_POLARITY_VSSA_SRC                 (0uL)
#define CY_CAPSENSE_CSD_IDACB_POLARITY_VDDA_SNK                 (1uL)
#define CY_CAPSENSE_CSD_IDACB_POLARITY_SENSE                    (2uL)
#define CY_CAPSENSE_CSD_IDACB_POLARITY_SENSE_INV                (3uL)

#define CY_CAPSENSE_CSD_IDACB_BALL_MODE_MSK                     (CSD_IDACB_BAL_MODE_Msk)
#define CY_CAPSENSE_CSD_IDACB_BALL_MODE_POS                     (CSD_IDACB_BAL_MODE_Pos)
#define CY_CAPSENSE_CSD_IDACB_BALL_MODE_FULL                    (0uL)
#define CY_CAPSENSE_CSD_IDACB_BALL_MODE_PHI1                    (1uL)
#define CY_CAPSENSE_CSD_IDACB_BALL_MODE_PHI2                    (2uL)
#define CY_CAPSENSE_CSD_IDACB_BALL_MODE_PHI1_2                  (3uL)

#define CY_CAPSENSE_CSD_IDACB_LEG1_MODE_MSK                     (CSD_IDACB_LEG1_MODE_Msk)
#define CY_CAPSENSE_CSD_IDACB_LEG1_MODE_POS                     (CSD_IDACB_LEG1_MODE_Pos)
#define CY_CAPSENSE_CSD_IDACB_LEG1_MODE_GP_STATIC               (0uL)
#define CY_CAPSENSE_CSD_IDACB_LEG1_MODE_GP                      (1uL)
#define CY_CAPSENSE_CSD_IDACB_LEG1_MODE_CSD_STATIC              (2uL)
#define CY_CAPSENSE_CSD_IDACB_LEG1_MODE_CSD                     (3uL)

#define CY_CAPSENSE_CSD_IDACB_LEG2_MODE_MSK                     (CSD_IDACB_LEG2_MODE_Msk)
#define CY_CAPSENSE_CSD_IDACB_LEG2_MODE_POS                     (CSD_IDACB_LEG2_MODE_Pos)
#define CY_CAPSENSE_CSD_IDACB_LEG2_MODE_GP_STATIC               (0uL)
#define CY_CAPSENSE_CSD_IDACB_LEG2_MODE_GP                      (1uL)
#define CY_CAPSENSE_CSD_IDACB_LEG2_MODE_CSD_STATIC              (2uL)
#define CY_CAPSENSE_CSD_IDACB_LEG2_MODE_CSD                     (3uL)

#define CY_CAPSENSE_CSD_IDACB_RANGE_MSK                         (CSD_IDACB_RANGE_Msk)
#define CY_CAPSENSE_CSD_IDACB_RANGE_POS                         (CSD_IDACB_RANGE_Pos)
#define CY_CAPSENSE_CSD_IDACB_RANGE_IDAC_LO                     (0uL)
#define CY_CAPSENSE_CSD_IDACB_RANGE_IDAC_MED                    (1uL)
#define CY_CAPSENSE_CSD_IDACB_RANGE_IDAC_HI                     (2uL)

#define CY_CAPSENSE_CSD_IDACB_LEG1_EN_MSK                       (CSD_IDACB_LEG1_EN_Msk)
#define CY_CAPSENSE_CSD_IDACB_LEG2_EN_MSK                       (CSD_IDACB_LEG2_EN_Msk)
#define CY_CAPSENSE_CSD_IDACB_LEG3_EN_MSK                       (CSD_IDACB_LEG3_EN_Msk)

/*******************************************************************************
* PRS & LFSR masks
*******************************************************************************/
#define CY_CAPSENSE_PRS_LENGTH_8_BITS                           (0x000000FFuL)
#define CY_CAPSENSE_PRS_LENGTH_12_BITS                          (0x00000FFFuL)

#define CY_CAPSENSE_SNSCLK_SSC1_PERIOD                          (63u)
#define CY_CAPSENSE_SNSCLK_SSC2_PERIOD                          (127u)
#define CY_CAPSENSE_SNSCLK_SSC3_PERIOD                          (511u)
#define CY_CAPSENSE_SNSCLK_SSC4_PERIOD                          (1023u)

#define CY_CAPSENSE_SNSCLK_LFSR_RANGE                           (16u)
#define CY_CAPSENSE_LFSR_DITHER_PERCENTAGE                      (10uL)
#define CY_CAPSENSE_SNSCLK_LFSR_THRESHOLD                       (CY_CAPSENSE_LFSR_DITHER_PERCENTAGE * CY_CAPSENSE_SNSCLK_LFSR_RANGE)

/*******************************************************************************
* HSIOM and PC Macros redefinition platform dependent and for readability
*******************************************************************************/
#define CY_CAPSENSE_DM_GPIO_ANALOG                          (CY_GPIO_DM_ANALOG)
#define CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF                   (CY_GPIO_DM_STRONG_IN_OFF)
#if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
    #define CY_CAPSENSE_HSIOM_SEL_GPIO                          (HSIOM_SEL_GPIO)
    #define CY_CAPSENSE_HSIOM_SEL_CSD_SENSE                     (HSIOM_SEL_CSD_SENSE)
    #define CY_CAPSENSE_HSIOM_SEL_CSD_SHIELD                    (HSIOM_SEL_CSD_SHIELD)
    #define CY_CAPSENSE_HSIOM_SEL_AMUXA                         (HSIOM_SEL_AMUXA)
    #define CY_CAPSENSE_HSIOM_SEL_AMUXB                         (HSIOM_SEL_AMUXB)
    #define CY_CAPSENSE_DM_SHIELD                                (CY_GPIO_DM_ANALOG)
    #define CY_CAPSENSE_CSD_SCAN_PIN_DM                         (CY_GPIO_DM_ANALOG)
    #define CY_CAPSENSE_CSX_TX_SCAN_PIN_HSIOM                   (HSIOM_SEL_CSD_SENSE)
    #define CY_CAPSENSE_CSX_CINT_SCAN_PIN_HSIOM                 (HSIOM_SEL_AMUXA)
#else
    #define CY_CAPSENSE_HSIOM_SEL_GPIO                          (HSIOM_SEL_GPIO)
    #define CY_CAPSENSE_HSIOM_SEL_CSD_SENSE                     (HSIOM_SEL_ACT_3)
    #define CY_CAPSENSE_HSIOM_SEL_CSD_SHIELD                    (HSIOM_SEL_ACT_2)
    #define CY_CAPSENSE_HSIOM_SEL_AMUXA                         (HSIOM_SEL_AMUXA)
    #define CY_CAPSENSE_HSIOM_SEL_AMUXB                         (HSIOM_SEL_AMUXB)
    #define CY_CAPSENSE_DM_SHIELD                                (CY_GPIO_DM_STRONG_IN_OFF)
    #define CY_CAPSENSE_CSD_SCAN_PIN_DM                         (CY_GPIO_DM_STRONG_IN_OFF)
    #define CY_CAPSENSE_CSX_TX_SCAN_PIN_HSIOM                   (HSIOM_SEL_ACT_2)
    #define CY_CAPSENSE_CSX_CINT_SCAN_PIN_HSIOM                 (HSIOM_SEL_GPIO)
#endif

/*******************************************************************************
* Clock Macros
*******************************************************************************/
#define CY_CAPSENSE_MODCLK_CMD_DIV_SHIFT                        (0uL)
#define CY_CAPSENSE_MODCLK_CMD_PA_DIV_SHIFT                     (8uL)
#define CY_CAPSENSE_MODCLK_CMD_DISABLE_SHIFT                    (30uL)
#define CY_CAPSENSE_MODCLK_CMD_ENABLE_SHIFT                     (31uL)
#define CY_CAPSENSE_MODCLK_CMD_DISABLE_MASK                     ((uint32_t)(1uL << CY_CAPSENSE_MODCLK_CMD_DISABLE_SHIFT))
#define CY_CAPSENSE_MODCLK_CMD_ENABLE_MASK                      ((uint32_t)(1uL << CY_CAPSENSE_MODCLK_CMD_ENABLE_SHIFT))

#define CY_CAPSENSE_MOD_CSD_CLK_12000000_HZ                     (12000000uL)
#define CY_CAPSENSE_MOD_CSD_CLK_24000000_HZ                     (24000000uL)
#define CY_CAPSENSE_MOD_CSD_CLK_48000000_HZ                     (48000000uL)

#define CY_CAPSENSE_MIN_SNS_CLK_DIVIDER                         (4000u)

#define CY_CAPSENSE_PERI_CLK_KHZ                                (50000000U / 1000U)
#define CY_CAPSENSE_PERI_CLK_MHZ                                (CY_CAPSENSE_PERI_CLK_KHZ / 1000U)

#define CY_CAPSENSE_CPU_CLK_KHZ                                 (50000000U / 1000U)
#define CY_CAPSENSE_CPU_CLK_MHZ                                 (CY_CAPSENSE_CPU_CLK_KHZ / 1000U)

/*******************************************************************************
* Miscellaneous Macros
*******************************************************************************/
#define CY_CAPSENSE_2000_MV                                     (2000u)

#if defined(__cplusplus)
}
#endif

#endif /* (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2)) */

#endif /* CY_CAPSENSE_SENSING_V2_H */


/* [] END OF FILE */
