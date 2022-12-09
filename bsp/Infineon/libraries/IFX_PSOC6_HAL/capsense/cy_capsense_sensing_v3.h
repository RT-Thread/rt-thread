/***************************************************************************//**
* \file cy_capsense_sensing_v3.h
* \version 3.0
*
* \brief
* This file provides the function prototypes specific to the scanning module.
*
********************************************************************************
* \copyright
* Copyright 2020-2021, Cypress Semiconductor Corporation (an Infineon company)
* or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_CAPSENSE_SENSING_V3_H)
#define CY_CAPSENSE_SENSING_V3_H

#include "cy_syslib.h"
#include "cy_capsense_common.h"
#include "cy_capsense_structure.h"
#if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
    #include "cy_msc.h"
#endif

#if (defined(CY_IP_M0S8MSCV3))

#if defined(__cplusplus)
extern "C" {
#endif


/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************/
/** \addtogroup group_capsense_high_level *//** \{ */
/******************************************************************************/
cy_capsense_status_t Cy_CapSense_ScanAllSlots(
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_ScanSlots(
                uint32_t startSlotId,
                uint32_t numberSlots,
                cy_stc_capsense_context_t * context);
cy_capsense_mw_state_t Cy_CapSense_MwState(
                const cy_stc_capsense_context_t * context);
/** \} */


/******************************************************************************/
/** \addtogroup group_capsense_low_level *//** \{ */
/******************************************************************************/
#if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CALIBRATION_EN) ||\
     (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN))
cy_capsense_status_t Cy_CapSense_CalibrateAllSlots(
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_SetCalibrationTargets(
                uint32_t csdCalibrTarget,
                uint32_t csxCalibrTarget,
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_CalibrateAllWidgets(
                cy_stc_capsense_context_t * context);
#endif

#if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
cy_capsense_status_t Cy_CapSense_SlotPinState(
                uint32_t slotId,
                const cy_stc_capsense_electrode_config_t * ptrEltdCfg,
                uint32_t pinState,
                cy_stc_capsense_context_t * context);
#endif

cy_capsense_status_t Cy_CapSense_ScanAbort(
                cy_stc_capsense_context_t * context);
/** \} */


/******************************************************************************/
/** \cond SECTION_CAPSENSE_INTERNAL */
/** \addtogroup group_capsense_internal *//** \{ */
/******************************************************************************/
cy_capsense_status_t Cy_CapSense_ScanWidget_V3(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_ScanSensor_V3(
                uint32_t widgetId,
                uint32_t sensorId,
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_ScanAllWidgets_V3(
                cy_stc_capsense_context_t * context);
uint32_t Cy_CapSense_IsBusy_V3(
                const cy_stc_capsense_context_t * context);
void Cy_CapSense_InterruptHandler_V3(
                const MSC_Type * base,
                cy_stc_capsense_context_t * context);

#if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
cy_capsense_status_t Cy_CapSense_SetPinState_V3(
                uint32_t widgetId,
                uint32_t sensorElement,
                uint32_t state,
                const cy_stc_capsense_context_t * context);
#endif

#if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CALIBRATION_EN) ||\
     (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN))
cy_capsense_status_t Cy_CapSense_CalibrateAllWidgets_V3(
                cy_stc_capsense_context_t * context);
#if (1u == CY_CAPSENSE_TOTAL_CH_NUMBER)
cy_capsense_status_t Cy_CapSense_CalibrateWidget_V3(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context);
#endif /* (1u == CY_CAPSENSE_TOTAL_CH_NUMBER) */
#endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CALIBRATION_EN) ||\
           (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN)) */
void Cy_CapSense_SetBusyFlags(
                uint32_t chIndex,
                cy_stc_capsense_context_t * context);
void Cy_CapSense_ClrBusyFlags(
                uint32_t chIndex,
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_SsInitialize(
                cy_stc_capsense_context_t * context);
uint32_t Cy_CapSense_WatchdogCyclesNum(
                uint32_t desiredTimeUs,
                uint32_t cpuFreqMHz,
                uint32_t cyclesPerLoop);
#if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
void Cy_CapSense_ConfigureAnalogMuxResource(
                uint32_t chIndex,
                uint32_t snsMethod,
                cy_stc_capsense_context_t * context);
#endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD) */
#if (CY_CAPSENSE_SCAN_MODE_DMA_DRIVEN == CY_CAPSENSE_SCAN_MODE)
cy_capsense_status_t Cy_CapSense_InitializeDmaResource(
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_ConfigureDmaResource(
                uint32_t mscChIndex,
                cy_stc_capsense_context_t * context);
#endif /* (CY_CAPSENSE_SCAN_MODE_DMA_DRIVEN == CY_CAPSENSE_SCAN_MODE) */
void Cy_CapSense_SetModClkDivider(
                uint32_t dividerValue,
                const cy_stc_capsense_context_t * context);
void Cy_CapSense_ScanISR(void * capsenseContext);
void Cy_CapSense_SetCmodInDefaultState(
                uint32_t chIndex,
                const cy_stc_capsense_context_t * context);
#if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
void Cy_CapSense_SetCmodInAmuxModeState(
                uint32_t chIndex,
                const cy_stc_capsense_context_t * context);
#endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD) */
void Cy_CapSense_InitActivePtrSns(
                uint32_t chIndex,
                uint32_t sensorId,
                cy_stc_capsense_context_t * context);
void Cy_CapSense_InitActivePtrWd(
                uint32_t chIndex,
                uint32_t widgetId,
                cy_stc_capsense_context_t * context);
void Cy_CapSense_InitActivePtr(
                uint32_t chIndex,
                uint32_t widgetId,
                uint32_t sensorId,
                cy_stc_capsense_context_t * context);
#if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
void Cy_CapSense_SetIOsInDesiredState(
                uint32_t desiredDriveMode,
                uint32_t desiredPinOutput,
                en_hsiom_sel_t desiredHsiom,
                uint32_t chIndex,
                const cy_stc_capsense_context_t * context);
#endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD) */
void Cy_CapSense_SetIOsInDefaultState(
                const cy_stc_capsense_context_t * context);
void Cy_CapSense_SsConfigPinRegisters(
                GPIO_PRT_Type * base,
                uint32_t pinNum,
                uint32_t dm,
                en_hsiom_sel_t hsiom);
#if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)
void Cy_CapSense_ConnectSensor(
                uint32_t chIndex,
                cy_stc_capsense_context_t * context);
void Cy_CapSense_DisconnectSensor(
                uint32_t chIndex,
                cy_stc_capsense_context_t * context);

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
void Cy_CapSense_CsdConnectSns(
                uint32_t chIndex,
                const cy_stc_capsense_context_t * context);
void Cy_CapSense_CsdDisconnectSns(
                uint32_t chIndex,
                const cy_stc_capsense_context_t * context);
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
void Cy_CapSense_CsxConnectRx(
                uint32_t chIndex,
                const cy_stc_capsense_context_t * context);
void Cy_CapSense_CsxConnectTx(
                uint32_t chIndex,
                const cy_stc_capsense_context_t * context);
void Cy_CapSense_CsxDisconnectRx(
                uint32_t chIndex,
                const cy_stc_capsense_context_t * context);
void Cy_CapSense_CsxDisconnectTx(
                uint32_t chIndex,
                const cy_stc_capsense_context_t * context);
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
void Cy_CapSense_EnableShieldElectrodes(
                uint32_t chIndex,
                cy_stc_capsense_context_t * context);
void Cy_CapSense_DisableShieldElectrodes(
                uint32_t chIndex,
                cy_stc_capsense_context_t * context);
#endif
#endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD) */

#if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CALIBRATION_EN) ||\
     (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN))
cy_capsense_status_t Cy_CapSense_CalibrateSlot(
                uint32_t scanSlotId,
                uint32_t autoCalibrMode,
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_NormalizeCdac(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_CalibrateCompDivider(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_VerifyCalibration(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context);
#endif
cy_capsense_status_t Cy_CapSense_WaitEndScan(
                uint32_t timeout,
                cy_stc_capsense_context_t * context);
void Cy_CapSense_SetShieldPinsInDefaultState(
                const cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_SwitchHwConfiguration(
                uint32_t configuration,
                cy_stc_capsense_context_t * context);
uint32_t Cy_CapSense_GetLfsrDitherVal(
                uint32_t lfsrBits,
                uint32_t lfsrScale);
uint32_t Cy_CapSense_GetLfsrDitherLimit(
                uint32_t snsClkDivider,
                uint32_t snsClkDividerMin,
                uint32_t ditherLimitPercents,
                uint32_t lfsrScale);
cy_capsense_status_t Cy_CapSense_InitializeSourceSenseClk(
                const cy_stc_capsense_context_t * context);

#if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_SMARTSENSE_FULL_EN) || \
     (CY_CAPSENSE_ENABLE == CY_CAPSENSE_SMARTSENSE_HW_EN))
cy_capsense_status_t Cy_CapSense_SsAutoTune(
                cy_stc_capsense_context_t * context);
#endif
uint32_t Cy_CapSense_GetMaxRaw(
                uint32_t snsClk,
                const cy_stc_capsense_widget_config_t * ptrWdConfig,
                const cy_stc_capsense_context_t * context);

/** \} \endcond */


/*******************************************************************************
* Local definition
*******************************************************************************/

#define CY_CAPSENSE_MSC_INTR_ALL_MSK                            (MSC_INTR_MASK_SUB_SAMPLE_Msk |\
                                                                 MSC_INTR_MASK_SAMPLE_Msk |\
                                                                 MSC_INTR_MASK_SCAN_Msk |\
                                                                 MSC_INTR_MASK_INIT_Msk |\
                                                                 MSC_INTR_MASK_FRAME_Msk |\
                                                                 MSC_INTR_MASK_CIC2_ERROR_Msk |\
                                                                 MSC_INTR_MASK_CONFIG_REQ_Msk |\
                                                                 MSC_INTR_MASK_FIFO_UNDERFLOW_Msk |\
                                                                 MSC_INTR_MASK_FIFO_OVERFLOW_Msk)


#define CY_CAPSENSE_FW_SHIELD_ACTIVE_AMUX_REG_SW_CSD_SHIELD_VALUE    (0x00000040uL)
#define CY_CAPSENSE_FW_SHIELD_PASSIVE_AMUX_REG_SW_CSD_SHIELD_VALUE   (0x00000050uL)
#define CY_CAPSENSE_FW_NEGATIVE_TX_AMUX_REG_SW_CSD_SHIELD_VALUE      (0x00000060uL)

#define CY_CAPSENSE_CALIBRATION_TIMEOUT                         (1000000uL)
#define CY_CAPSENSE_MAX_CH_NUM                                  (4u)
#define CY_CAPSENSE_CDAC_MAX_CODE                               (0xFFu)
#define CY_CAPSENSE_CAL_MIDDLE_VALUE                            (0x80u)

#define CY_CAPSENSE_CAL_MODE_REF_CDAC_SUC_APPR                  (0u)
#define CY_CAPSENSE_CAL_MODE_COMP_CDAC_SUC_APPR                 (2u)
#define CY_CAPSENSE_CAL_MODE_COMP_CDAC_MAX_CODE                 (3u)

#define CY_CAPSENSE_CMOD_AMUX_MSK                               (MSC_SW_SEL_GPIO_SW_CSD_SENSE_Msk |\
                                                                 MSC_SW_SEL_GPIO_SW_CSD_MUTUAL_Msk |\
                                                                 MSC_SW_SEL_GPIO_SW_CSD_POLARITY_Msk |\
                                                                 MSC_SW_SEL_GPIO_SW_DSI_CMOD_Msk |\
                                                                 MSC_SW_SEL_GPIO_SW_DSI_CSH_TANK_Msk)

#define CY_CAPSENSE_FW_CMOD_AMUX_CSD_REG_SW_SEL_GPIO_VALUE      ((4uL << MSC_SW_SEL_GPIO_SW_CSD_SENSE_Pos) |\
                                                                 (2uL << MSC_SW_SEL_GPIO_SW_CSD_POLARITY_Pos) |\
                                                                 (3uL << MSC_SW_SEL_GPIO_SW_DSI_CMOD_Pos) |\
                                                                 (3uL << MSC_SW_SEL_GPIO_SW_DSI_CSH_TANK_Pos))

#define CY_CAPSENSE_FW_CMOD_AMUX_CSX_REG_SW_SEL_GPIO_VALUE      ((2uL << MSC_SW_SEL_GPIO_SW_CSD_SENSE_Pos) |\
                                                                 (1uL << MSC_SW_SEL_GPIO_SW_CSD_MUTUAL_Pos))

#define CY_CAPSENSE_LFSR_RANGE_0_DITHER_MAX                     (2u)
#define CY_CAPSENSE_LFSR_RANGE_1_DITHER_MAX                     (4u)
#define CY_CAPSENSE_LFSR_RANGE_2_DITHER_MAX                     (8u)
#define CY_CAPSENSE_LFSR_RANGE_3_DITHER_MAX                     (16u)

#define CY_CAPSENSE_2PH_PRS_SNS_CLOCK_DIVIDER_SHIFT             (1u)
#define CY_CAPSENSE_4PH_PRS_SNS_CLOCK_DIVIDER_SHIFT             (2u)

#define CY_CAPSENSE_DIRECT_SNS_CLOCK_DIVIDER_MAX                (4096u)
#define CY_CAPSENSE_2PH_DIRECT_SNS_CLOCK_DIVIDER_MIN            (4u)
#define CY_CAPSENSE_4PH_DIRECT_SNS_CLOCK_DIVIDER_MIN            (8u)

#define CY_CAPSENSE_SMARTSENSE_PRELIMINARY_SCAN_NSUB            (8u)
#define CY_CAPSENSE_SMARTSENSE_PRELIMINARY_SCAN_SNS_CLK         (256u)
#define CY_CAPSENSE_SMARTSENSE_PRELIMINARY_SCAN_NSUB_RANGE2     (64u)
#define CY_CAPSENSE_SMARTSENSE_PRELIMINARY_SCAN_SNS_CLK_RANGE2  (32u)
#define CY_CAPSENSE_SMARTSENSE_PRELIMINARY_SCAN_REF_CDAC        (10u)
#define CY_CAPSENSE_SMARTSENSE_WD_MAX_NUMBER                    (64u)
#define CY_CAPSENSE_SMARTSENSE_PRO_EPI_CYCLE_NUMBER             (119u)
#define CY_CAPSENSE_SMARTSENSE_ROUND_UP_2_BITS_MASK             (0x03u)
#define CY_CAPSENSE_SMARTSENSE_MAX_KREF_VAL                     (2048u)
#define CY_CAPSENSE_SMARTSENSE_SCALING_DECI_VAL                 (10u)
#define CY_CAPSENSE_SMARTSENSE_CORRECTION                       (8u)

#define CY_CAPSENSE_MAX_PRO_EPI_PRS_CYCLE_NUMBER                (1023u)

#define CY_CAPSENSE_CALIBRATION_REF_CDAC_MASK                   (0x01u)
#define CY_CAPSENSE_CALIBRATION_COMP_DIV_MASK                   (0x02u)
#define CY_CAPSENSE_CALIBRATION_COMP_CDAC_MASK                  (0x04u)

#define CY_CAPSENSE_MFS_FREQ_CHANNELS_NUM_MASK                  (0xFu)
#define CY_CAPSENSE_MFS_EN_MASK                                 (0x10u)
#define CY_CAPSENSE_MFS_WIDGET_FREQ_ALL_CH_MASK                 (0x60u)
#define CY_CAPSENSE_MFS_WIDGET_FREQ_CH_1_MASK                   (0x20u)
#define CY_CAPSENSE_MFS_WIDGET_FREQ_CH_2_MASK                   (0x40u)

#define CY_CAPSENSE_SLOT_COUNT_MAX_VALUE                        (0xFFFFu)

/*******************************************************************************
* HSIOM and PC Macros redefinition platform dependent and for readability
*******************************************************************************/
#define CY_CAPSENSE_HSIOM_SEL_GPIO                          (HSIOM_SEL_GPIO)
#define CY_CAPSENSE_HSIOM_SEL_CSD_SHIELD                    (HSIOM_SEL_CSD_SHIELD)
#define CY_CAPSENSE_HSIOM_SEL_CSD_SENSE                     (HSIOM_SEL_CSD_SENSE)
#define CY_CAPSENSE_HSIOM_SEL_AMUXA                         (HSIOM_SEL_AMUXA)
#define CY_CAPSENSE_HSIOM_SEL_AMUXB                         (HSIOM_SEL_AMUXB)
#define CY_CAPSENSE_DM_GPIO_ANALOG                          (CY_GPIO_DM_ANALOG)
#define CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF                   (CY_GPIO_DM_STRONG_IN_OFF)


#if (CY_CAPSENSE_DISABLE == CY_CAPSENSE_USE_CAPTURE)

/*******************************************************************************
* Constant definition
*******************************************************************************/
/*
 *  Definition of the default configuration of the MSC HW registers that is
 *  intended to be used on the MSC HW block capturing stage.
 *  The configuration includes:
 *  1. Start of the analog settling process:
 *      - Enables the MSC HW block;
 *      - Enables all the sub-blocks of the MSC HW block;
 *      - Enables the Sense Modulator output;
 *  2. Clear all of the pending interrupt requests of the MSC HW block;
 *  3. Sets into default state the rest of the CSD HW block registers which are not related
 *     to actions #1 and #2.
*/

    #define CY_CAPSENSE_MSC_CONFIG_DEFAULT                  \
    {                                                       \
        .ctl                = MSC_CTL_SENSE_EN_Msk |        \
                              MSC_CTL_MSCCMP_EN_Msk |       \
                              MSC_CTL_ENABLED_Msk,          \
        .spare              = 0x00uL,                       \
        .scanCtl1           = 0x00uL,                       \
        .scanCtl2           = 0x00uL,                       \
        .initCtl1           = 0x00uL,                       \
        .initCtl2           = 0x00uL,                       \
        .initCtl3           = 0x00uL,                       \
        .initCtl4           = 0x00uL,                       \
        .senseDutyCtl       = 0x00uL,                       \
        .sensePeriodCtl     = 0x00uL,                       \
        .filterCtl          = 0x00uL,                       \
        .ccompCdacCtl       = 0x00uL,                       \
        .ditherCdacCtl      = 0x00uL,                       \
        .cswCtl             = 0x00uL,                       \
        .swSelGpio          = 0x00uL,                       \
        .swSelCdacRe        = 0x00uL,                       \
        .swSelCdacCo        = 0x00uL,                       \
        .swSelCdacCf        = 0x00uL,                       \
        .swSelCmod1         = 0x00uL,                       \
        .swSelCmod2         = 0x00uL,                       \
        .swSelCmod3         = 0x00uL,                       \
        .swSelCmod4         = 0x00uL,                       \
        .obsCtl             = 0x00uL,                       \
        .status1            = 0x00uL,                       \
        .status2            = 0x00uL,                       \
        .status3            = 0x00uL,                       \
        .resultFifoStatus   = 0x00uL,                       \
        .resultFifoRd       = 0x00uL,                       \
        .intr               = 0x00uL,                       \
        .intrSet            = 0x00uL,                       \
        .intrMask           = 0x00uL,                       \
        .intrMasked         = 0x00uL,                       \
        .frameCmd           = 0x00uL,                       \
        .sensorConfig =                                     \
        {                                                   \
            .snsSwSelCswMask2   = 0x00uL,                   \
            .snsSwSelCswMask1   = 0x00uL,                   \
            .snsSwSelCswMask0   = 0x00uL,                   \
            .snsScanCtl         = 0x00uL,                   \
            .snsCdacCtl         = 0x00uL,                   \
            .snsCtl             = 0x00uL,                   \
        },                                                  \
        .swSelCsw[0u]       = 0x00uL,                       \
        .swSelCsw[1u]       = 0x00uL,                       \
        .swSelCsw[2u]       = 0x00uL,                       \
        .swSelCsw[3u]       = 0x00uL,                       \
        .swSelCsw[4u]       = 0x00uL,                       \
        .swSelCsw[5u]       = 0x00uL,                       \
        .swSelCsw[6u]       = 0x00uL,                       \
        .swSelCsw[7u]       = 0x00uL,                       \
        .swSelCsw[8u]       = 0x00uL,                       \
        .swSelCsw[9u]       = 0x00uL,                       \
        .swSelCsw[10u]      = 0x00uL,                       \
        .swSelCsw[11u]      = 0x00uL,                       \
        .swSelCsw[12u]      = 0x00uL,                       \
        .swSelCsw[13u]      = 0x00uL,                       \
        .swSelCsw[14u]      = 0x00uL,                       \
        .swSelCsw[15u]      = 0x00uL,                       \
        .swSelCsw[16u]      = 0x00uL,                       \
        .swSelCsw[17u]      = 0x00uL,                       \
        .swSelCsw[18u]      = 0x00uL,                       \
        .swSelCsw[19u]      = 0x00uL,                       \
        .swSelCsw[20u]      = 0x00uL,                       \
        .swSelCsw[21u]      = 0x00uL,                       \
        .swSelCsw[22u]      = 0x00uL,                       \
        .swSelCsw[23u]      = 0x00uL,                       \
        .swSelCsw[24u]      = 0x00uL,                       \
        .swSelCsw[25u]      = 0x00uL,                       \
        .swSelCsw[26u]      = 0x00uL,                       \
        .swSelCsw[27u]      = 0x00uL,                       \
        .swSelCsw[28u]      = 0x00uL,                       \
        .swSelCsw[29u]      = 0x00uL,                       \
        .swSelCsw[30u]      = 0x00uL,                       \
        .swSelCsw[31u]      = 0x00uL,                       \
        .swSelCswFunc[0u]   = 0x00uL,                       \
        .swSelCswFunc[1u]   = 0x00uL,                       \
        .swSelCswFunc[2u]   = 0x00uL,                       \
        .swSelCswFunc[3u]   = 0x00uL,                       \
        .swSelCswFunc[4u]   = 0x00uL,                       \
        .swSelCswFunc[5u]   = 0x00uL,                       \
        .swSelCswFunc[6u]   = 0x00uL,                       \
        .swSelCswFunc[7u]   = 0x00uL,                       \
        .mode[0u] =                                         \
        {                                                   \
            .senseDutyCtl   = 0x00uL,                       \
            .swSelCdacFl    = 0x00uL,                       \
            .swSelTop       = 0x00uL,                       \
            .swSelComp      = 0x00uL,                       \
            .swSelSh        = 0x00uL,                       \
        },                                                  \
        .mode[1u] =                                         \
        {                                                   \
            .senseDutyCtl   = 0x00uL,                       \
            .swSelCdacFl    = 0x00uL,                       \
            .swSelTop       = 0x00uL,                       \
            .swSelComp      = 0x00uL,                       \
            .swSelSh        = 0x00uL,                       \
        },                                                  \
        .mode[2u] =                                         \
        {                                                   \
            .senseDutyCtl   = 0x00uL,                       \
            .swSelCdacFl    = 0x00uL,                       \
            .swSelTop       = 0x00uL,                       \
            .swSelComp      = 0x00uL,                       \
            .swSelSh        = 0x00uL,                       \
        },                                                  \
        .mode[3u] =                                         \
        {                                                   \
            .senseDutyCtl   = 0x00uL,                       \
            .swSelCdacFl    = 0x00uL,                       \
            .swSelTop       = 0x00uL,                       \
            .swSelComp      = 0x00uL,                       \
            .swSelSh        = 0x00uL,                       \
        },                                                  \
    }

    extern const cy_stc_msc_base_config_t cy_capsense_mscCfg;
#endif

#define CY_CAPSENSE_CSD_CDAC_COMP_USAGE             ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) &&\
                                                         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CDAC_COMP_EN))
#define CY_CAPSENSE_CSD_CDAC_COMP_DIV_AUTO_USAGE    ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CDAC_COMP_USAGE) &&\
                                                         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CALIBRATION_EN) &&\
                                                         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CDAC_COMP_DIV_AUTO_EN))
#define CY_CAPSENSE_CSD_CDAC_REF_AUTO_USAGE         ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) &&\
                                                         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CALIBRATION_EN) &&\
                                                         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CDAC_REF_AUTO_EN))

#define CY_CAPSENSE_CSX_CDAC_COMP_USAGE             ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) &&\
                                                         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CDAC_COMP_EN))
#define CY_CAPSENSE_CSX_CDAC_COMP_DIV_AUTO_USAGE    ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CDAC_COMP_USAGE) &&\
                                                         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN) &&\
                                                         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CDAC_COMP_DIV_AUTO_EN))
#define CY_CAPSENSE_CSX_CDAC_REF_AUTO_USAGE         ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) &&\
                                                         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN) &&\
                                                         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CDAC_REF_AUTO_EN))


#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_M0S8MSCV3 */

#endif /* CY_CAPSENSE_SENSING_V3_H */


/* [] END OF FILE */
