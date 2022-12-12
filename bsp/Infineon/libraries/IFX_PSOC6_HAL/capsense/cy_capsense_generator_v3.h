/***************************************************************************//**
* \file cy_capsense_generator_v3.h
* \version 3.0
*
* \brief
* This file provides the function prototypes specific to the register
* map generation module.
*
********************************************************************************
* \copyright
* Copyright 2020-2021, Cypress Semiconductor Corporation (an Infineon company)
* or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_CAPSENSE_GENERATOR_V3_H)
#define CY_CAPSENSE_GENERATOR_V3_H

#include "cy_capsense_common.h"
#include "cy_capsense_structure.h"
#include "cy_capsense_sm_base_full_wave_v3.h"

#if (defined(CY_IP_M0S8MSCV3))

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
* Function Prototypes
*******************************************************************************/



/******************************************************************************/
/** \cond SECTION_CAPSENSE_INTERNAL */
/** \addtogroup group_capsense_internal *//** \{ */
/******************************************************************************/
cy_capsense_status_t Cy_CapSense_GenerateBaseConfig(
                uint32_t chIndex,
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_GenerateSensorConfig(
                uint32_t chIndex,
                uint32_t scanSlot,
                uint32_t * ptrSensorCfg,
                cy_stc_capsense_context_t * context);
void Cy_CapSense_GenerateAllSensorConfig(
                uint32_t chId,
                uint32_t * ptrSensorCfg,
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_GenerateCdacConfig(
                uint32_t scanSlot,
                uint32_t * ptrSensorCfg,
                const cy_stc_capsense_context_t * context);

#if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
void Cy_CapSense_CalculateMaskRegisters(
                uint32_t mask,
                uint32_t funcState,
                uint32_t * ptrCfg);
#endif

/** \} \endcond */


/*******************************************************************************
* Sensor Config Register indexes in the frame
*******************************************************************************/
#define CY_CAPSENSE_SNS_SW_SEL_CSW_MASK2_INDEX                                  (0u)
#define CY_CAPSENSE_SNS_SW_SEL_CSW_MASK1_INDEX                                  (1u)
#define CY_CAPSENSE_SNS_SW_SEL_CSW_MASK0_INDEX                                  (2u)
#define CY_CAPSENSE_SNS_SCAN_CTL_INDEX                                          (3u)
#define CY_CAPSENSE_SNS_CDAC_CTL_INDEX                                          (4u)
#define CY_CAPSENSE_SNS_CTL_INDEX                                               (5u)


/*******************************************************************************
* Macros for Cmod selection
*******************************************************************************/
#define CY_CAPSENSE_MSC0_CMOD1PADD_PIN                                          (2u)
#define CY_CAPSENSE_MSC1_CMOD1PADD_PIN                                          (1u)

#define CY_CAPSENSE_CMOD12_PAIR_SELECTION                                       (0u)
#define CY_CAPSENSE_CMOD34_PAIR_SELECTION                                       (1u)


/*******************************************************************************
* Register definition for FW CSD CTRLMUX with Active Shielding
*******************************************************************************/
#define CY_CAPSENSE_FW_SHIELD_ACTIVE_CTRLMUX_REG_SW_SEL_TOP_MASK                (0x4FFC0000uL)
#define CY_CAPSENSE_FW_SHIELD_ACTIVE_CTRLMUX_REG_SW_SEL_SH_MASK                 (0x80050000uL)
#define CY_CAPSENSE_FW_SHIELD_ACTIVE_CTRLMUX_REG_SW_SEL_TOP_VALUE               (0x44280000uL)
#define CY_CAPSENSE_FW_SHIELD_ACTIVE_CTRLMUX_REG_SW_SEL_SH_VALUE                (0x80050000uL)
#define CY_CAPSENSE_FW_SHIELD_ACTIVE_CTRLMUX_REG_SW_SEL_CSW_VALUE               (0x84022000uL)


/*******************************************************************************
* Register definition for FW CSD CTRLMUX with Passive Shielding
*******************************************************************************/
#define CY_CAPSENSE_FW_SHIELD_PASSIVE_CTRLMUX_REG_SW_SEL_TOP_MASK               (0x0FFC0000uL)
#define CY_CAPSENSE_FW_SHIELD_PASSIVE_CTRLMUX_REG_SW_SEL_TOP_VALUE              (0x09800000uL)
#define CY_CAPSENSE_FW_SHIELD_PASSIVE_CTRLMUX_REG_SW_SEL_CSW_VALUE              (0x09080000uL)


/*******************************************************************************
* Register definition for FW CSD AMUX with Active Shielding
*******************************************************************************/
#define CY_CAPSENSE_FW_SHIELD_ACTIVE_AMUX_REG_SW_SEL_TOP_MASK                   (0x40000000uL)
#define CY_CAPSENSE_FW_SHIELD_ACTIVE_AMUX_REG_SW_SEL_SH_MASK                    (0x80010100uL)
#define CY_CAPSENSE_FW_SHIELD_ACTIVE_AMUX_REG_SW_SEL_TOP_VALUE                  (0x40000000uL)
#define CY_CAPSENSE_FW_SHIELD_ACTIVE_AMUX_REG_SW_SEL_SH_VALUE                   (0x80010100uL)


/*******************************************************************************
* Register definition for FW CSX VDDA/2
*******************************************************************************/
#define CY_CAPSENSE_FW_CSX_VDDA2_CTLMUX_MODE_SW_SEL_SH_VALUE                    (0x87050000uL)
#define CY_CAPSENSE_FW_CSX_VDDA2_AMUX_MODE_SW_SEL_SH_VALUE                      (0x87010100uL)


/*******************************************************************************
* The MODE_SENSE_DUTY_CTL register configuration for the FW CSX AMUX
*******************************************************************************/
#define CY_CAPSENSE_FW_CSX_AMUX_MODE_SENSE_DUTY_CTL_VALUE                       (0x11000000uL)


/*******************************************************************************
* The MODE_SW_SEL_TOP register configuration for the FW CSX
*******************************************************************************/
#define CY_CAPSENSE_CSX_FW_CTLMUX_MODE_SW_SEL_TOP_VALUE            (1uL << MSC_MODE_SW_SEL_TOP_SHG_Pos)
#define CY_CAPSENSE_CSX_FW_AMUX_MODE_SW_SEL_TOP_VALUE              ((2uL << MSC_MODE_SW_SEL_TOP_AYA_CTL_Pos) |\
                                                                    (1uL << MSC_MODE_SW_SEL_TOP_AYA_EN_Pos)  |\
                                                                    (2uL << MSC_MODE_SW_SEL_TOP_AYB_CTL_Pos) |\
                                                                    (1uL << MSC_MODE_SW_SEL_TOP_AYB_EN_Pos)  |\
                                                                    (1uL << MSC_MODE_SW_SEL_TOP_SHG_Pos))

/* CSW0 = RX MUX */
#define CY_CAPSENSE_SM_REG_SW_SEL_CSW0_RX_VALUE \
((CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW0_FLD_SW_SNCA  << MSC_SW_SEL_CSW_SW_SNCA_Pos)  | \
 (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW0_FLD_SW_SNCB  << MSC_SW_SEL_CSW_SW_SNCB_Pos)  | \
 (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW0_FLD_SW_SNCC  << MSC_SW_SEL_CSW_SW_SNCC_Pos)  | \
 (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW0_FLD_SW_SNCV  << MSC_SW_SEL_CSW_SW_SNCV_Pos)  | \
 (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW0_FLD_SW_SNCG  << MSC_SW_SEL_CSW_SW_SNCG_Pos)  | \
 (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW0_FLD_REF_MODE << MSC_SW_SEL_CSW_REF_MODE_Pos) | \
 (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW0_FLD_ENABLED  << MSC_SW_SEL_CSW_ENABLED_Pos))

/* CSW1 = Positive TX MUX */
#define CY_CAPSENSE_SM_REG_SW_SEL_CSW1_TX_VALUE \
((CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW1_FLD_SW_SNCA  << MSC_SW_SEL_CSW_SW_SNCA_Pos)  | \
 (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW1_FLD_SW_SNCB  << MSC_SW_SEL_CSW_SW_SNCB_Pos)  | \
 (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW1_FLD_SW_SNCC  << MSC_SW_SEL_CSW_SW_SNCC_Pos)  | \
 (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW1_FLD_SW_SNCV  << MSC_SW_SEL_CSW_SW_SNCV_Pos)  | \
 (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW1_FLD_SW_SNCG  << MSC_SW_SEL_CSW_SW_SNCG_Pos)  | \
 (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW1_FLD_REF_MODE << MSC_SW_SEL_CSW_REF_MODE_Pos) | \
 (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW1_FLD_ENABLED  << MSC_SW_SEL_CSW_ENABLED_Pos))

/* CSW2 = Negative TX MUX */
#define CY_CAPSENSE_SM_REG_SW_SEL_CSW2_NEG_TX_VALUE \
((CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW2_FLD_SW_SNCA  << MSC_SW_SEL_CSW_SW_SNCA_Pos)  | \
 (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW2_FLD_SW_SNCB  << MSC_SW_SEL_CSW_SW_SNCB_Pos)  | \
 (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW2_FLD_SW_SNCC  << MSC_SW_SEL_CSW_SW_SNCC_Pos)  | \
 (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW2_FLD_SW_SNCV  << MSC_SW_SEL_CSW_SW_SNCV_Pos)  | \
 (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW2_FLD_SW_SNCG  << MSC_SW_SEL_CSW_SW_SNCG_Pos)  | \
 (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW2_FLD_REF_MODE << MSC_SW_SEL_CSW_REF_MODE_Pos) | \
 (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW2_FLD_ENABLED  << MSC_SW_SEL_CSW_ENABLED_Pos))

/* CSW3 = Cs Sensor MUX */
#define CY_CAPSENSE_SM_REG_SW_SEL_CSW3_SNS_VALUE \
((CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW3_FLD_SW_SNCA  << MSC_SW_SEL_CSW_SW_SNCA_Pos)  | \
 (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW3_FLD_SW_SNCB  << MSC_SW_SEL_CSW_SW_SNCB_Pos)  | \
 (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW3_FLD_SW_SNCC  << MSC_SW_SEL_CSW_SW_SNCC_Pos)  | \
 (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW3_FLD_SW_SNCV  << MSC_SW_SEL_CSW_SW_SNCV_Pos)  | \
 (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW3_FLD_SW_SNCG  << MSC_SW_SEL_CSW_SW_SNCG_Pos)  | \
 (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW3_FLD_REF_MODE << MSC_SW_SEL_CSW_REF_MODE_Pos) | \
 (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW3_FLD_ENABLED  << MSC_SW_SEL_CSW_ENABLED_Pos))

/* CSW4 = Shield MUX for grounded shield */
#define CY_CAPSENSE_SM_REG_SW_SEL_CSW4_GND_VALUE \
((CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW4_FLD_SW_SNCA  << MSC_SW_SEL_CSW_SW_SNCA_Pos)  | \
 (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW4_FLD_SW_SNCB  << MSC_SW_SEL_CSW_SW_SNCB_Pos)  | \
 (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW4_FLD_SW_SNCC  << MSC_SW_SEL_CSW_SW_SNCC_Pos)  | \
 (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW4_FLD_SW_SNCV  << MSC_SW_SEL_CSW_SW_SNCV_Pos)  | \
 (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW4_FLD_SW_SNCG  << MSC_SW_SEL_CSW_SW_SNCG_Pos)  | \
 (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW4_FLD_REF_MODE << MSC_SW_SEL_CSW_REF_MODE_Pos) | \
 (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW4_FLD_ENABLED  << MSC_SW_SEL_CSW_ENABLED_Pos)) \

/* CSW5 = High Z */
#define CY_CAPSENSE_SM_REG_SW_SEL_CSW5_HIGH_Z_VALUE \
((CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW5_FLD_SW_SNCA  << MSC_SW_SEL_CSW_SW_SNCA_Pos)  | \
 (CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW5_FLD_SW_SNCB  << MSC_SW_SEL_CSW_SW_SNCB_Pos)  | \
 (CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW5_FLD_SW_SNCC  << MSC_SW_SEL_CSW_SW_SNCC_Pos)  | \
 (CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW5_FLD_SW_SNCV  << MSC_SW_SEL_CSW_SW_SNCV_Pos)  | \
 (CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW5_FLD_SW_SNCG  << MSC_SW_SEL_CSW_SW_SNCG_Pos)  | \
 (CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW5_FLD_REF_MODE << MSC_SW_SEL_CSW_REF_MODE_Pos) | \
 (CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW5_FLD_ENABLED  << MSC_SW_SEL_CSW_ENABLED_Pos)) \

/* CSW6 = CSDBUSC connection */
#define CY_CAPSENSE_SM_REG_SW_SEL_CSW6_VDDA2_VALUE \
((CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW6_FLD_SW_SNCA  << MSC_SW_SEL_CSW_SW_SNCA_Pos)  | \
 (CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW6_FLD_SW_SNCB  << MSC_SW_SEL_CSW_SW_SNCB_Pos)  | \
 (CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW6_FLD_SW_SNCC  << MSC_SW_SEL_CSW_SW_SNCC_Pos)  | \
 (CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW6_FLD_SW_SNCV  << MSC_SW_SEL_CSW_SW_SNCV_Pos)  | \
 (CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW6_FLD_SW_SNCG  << MSC_SW_SEL_CSW_SW_SNCG_Pos)  | \
 (CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW6_FLD_REF_MODE << MSC_SW_SEL_CSW_REF_MODE_Pos) | \
 (CY_CAPSENSE_SM_FULL_WAVE_CTRL_MUX_REG_SW_SEL_CSW6_FLD_ENABLED  << MSC_SW_SEL_CSW_ENABLED_Pos)) \


#define CY_CAPSENSE_CSD_RM_SENSING_METHOD_INDEX         (0u)
#define CY_CAPSENSE_CSX_RM_SENSING_METHOD_INDEX         (1u)
#define CY_CAPSENSE_CSD_DITHERING_SENSING_METHOD_INDEX  (2u)
#define CY_CAPSENSE_CSX_DITHERING_SENSING_METHOD_INDEX  (3u)


/** Initialization of sensing method template variable */
#define CY_CAPSENSE_SENSING_METHOD_BASE_TEMPLATE            \
    {                                                   \
        .ctl = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CTL_FLD_SENSE_EN << MSC_CTL_SENSE_EN_Pos)                    | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CTL_FLD_MSCCMP_EN << MSC_CTL_MSCCMP_EN_Pos)                   | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CTL_FLD_CLK_SYNC_EN << MSC_CTL_CLK_SYNC_EN_Pos)               | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CTL_FLD_EXT_FRAME_START_EN << MSC_CTL_EXT_FRAME_START_EN_Pos) | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CTL_FLD_OPERATING_MODE << MSC_CTL_OPERATING_MODE_Pos)         | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CTL_FLD_BUF_MODE << MSC_CTL_BUF_MODE_Pos)                     | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CTL_FLD_CLK_MSC_RATIO << MSC_CTL_CLK_MSC_RATIO_Pos)           | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CTL_FLD_ENABLED << MSC_CTL_ENABLED_Pos)),                      \
        .spare = \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SPARE_FLD_SPARE), \
        .scanCtl1 = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SCAN_CTL1_FLD_NUM_AUTO_RESAMPLE << MSC_SCAN_CTL1_NUM_AUTO_RESAMPLE_Pos) | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SCAN_CTL1_FLD_RESCAN_DEBUG_MODE << MSC_SCAN_CTL1_RESCAN_DEBUG_MODE_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SCAN_CTL1_FLD_NUM_SAMPLES << MSC_SCAN_CTL1_NUM_SAMPLES_Pos)              | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SCAN_CTL1_FLD_RAW_COUNT_MODE << MSC_SCAN_CTL1_RAW_COUNT_MODE_Pos)        | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SCAN_CTL1_FLD_DEBUG_CONV_PH_SEL << MSC_SCAN_CTL1_DEBUG_CONV_PH_SEL_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SCAN_CTL1_FLD_FRAME_START_PTR << MSC_SCAN_CTL1_FRAME_START_PTR_Pos)),     \
        .scanCtl2 = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SCAN_CTL2_FLD_NUM_EPI_CYCLES << MSC_SCAN_CTL2_NUM_EPI_CYCLES_Pos)       | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SCAN_CTL2_FLD_CHOP_POL << MSC_SCAN_CTL2_CHOP_POL_Pos)                    | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SCAN_CTL2_FLD_CHOP_EVEN_HOLD_EN << MSC_SCAN_CTL2_CHOP_EVEN_HOLD_EN_Pos)), \
        .initCtl1 = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL1_FLD_NUM_INIT_CMOD_12_RAIL_CYCLES << MSC_INIT_CTL1_NUM_INIT_CMOD_12_RAIL_CYCLES_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL1_FLD_NUM_INIT_CMOD_12_SHORT_CYCLES << MSC_INIT_CTL1_NUM_INIT_CMOD_12_SHORT_CYCLES_Pos) | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL1_FLD_PER_SAMPLE << MSC_INIT_CTL1_PER_SAMPLE_Pos)),                                      \
        .initCtl2 = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL2_FLD_NUM_INIT_CMOD_34_RAIL_CYCLES << MSC_INIT_CTL2_NUM_INIT_CMOD_34_RAIL_CYCLES_Pos)   | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL2_FLD_NUM_INIT_CMOD_34_SHORT_CYCLES << MSC_INIT_CTL2_NUM_INIT_CMOD_34_SHORT_CYCLES_Pos)), \
        .initCtl3 = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL3_FLD_NUM_PRO_OFFSET_CYCLES << MSC_INIT_CTL3_NUM_PRO_OFFSET_CYCLES_Pos) | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL3_FLD_NUM_PRO_OFFSET_TRIPS << MSC_INIT_CTL3_NUM_PRO_OFFSET_TRIPS_Pos)    | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL3_FLD_CMOD_SEL << MSC_INIT_CTL3_CMOD_SEL_Pos)                            | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL3_FLD_INIT_MODE << MSC_INIT_CTL3_INIT_MODE_Pos)),                         \
        .initCtl4 = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL4_FLD_NUM_PRO_DUMMY_SUB_CONVS << MSC_INIT_CTL4_NUM_PRO_DUMMY_SUB_CONVS_Pos) | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INIT_CTL4_FLD_NUM_PRO_WAIT_CYCLES << MSC_INIT_CTL4_NUM_PRO_WAIT_CYCLES_Pos)), \
        .senseDutyCtl = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SENSE_DUTY_CTL_FLD_PHASE_WIDTH << MSC_SENSE_DUTY_CTL_PHASE_WIDTH_Pos)              | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SENSE_DUTY_CTL_FLD_PHASE_SHIFT_CYCLES << MSC_SENSE_DUTY_CTL_PHASE_SHIFT_CYCLES_Pos) | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SENSE_DUTY_CTL_FLD_PHASE_WIDTH_SEL << MSC_SENSE_DUTY_CTL_PHASE_WIDTH_SEL_Pos)),      \
        .sensePeriodCtl = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SENSE_PERIOD_CTL_FLD_LFSR_POLY << MSC_SENSE_PERIOD_CTL_LFSR_POLY_Pos)   | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SENSE_PERIOD_CTL_FLD_LFSR_SCALE << MSC_SENSE_PERIOD_CTL_LFSR_SCALE_Pos)), \
        .filterCtl = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_FILTER_CTL_FLD_BIT_FORMAT << MSC_FILTER_CTL_BIT_FORMAT_Pos)   | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_FILTER_CTL_FLD_FILTER_MODE << MSC_FILTER_CTL_FILTER_MODE_Pos)), \
        .ccompCdacCtl = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CCOMP_CDAC_CTL_FLD_SEL_CO_PRO_OFFSET << MSC_CCOMP_CDAC_CTL_SEL_CO_PRO_OFFSET_Pos) | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CCOMP_CDAC_CTL_FLD_EPILOGUE_EN << MSC_CCOMP_CDAC_CTL_EPILOGUE_EN_Pos)),             \
        .ditherCdacCtl = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_DITHER_CDAC_CTL_FLD_SEL_FL << MSC_DITHER_CDAC_CTL_SEL_FL_Pos)             | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_DITHER_CDAC_CTL_FLD_LFSR_POLY_FL << MSC_DITHER_CDAC_CTL_LFSR_POLY_FL_Pos)), \
        .cswCtl = \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_CSW_CTL_FLD_CSW_FUNC_MODE), \
        .swSelGpio = \
                    ((CY_CAPSENSE_SM_CSX_FULL_WAVE_GPIO_REG_SW_SEL_GPIO_FLD_SW_CSD_SENSE   << MSC_SW_SEL_GPIO_SW_CSD_SENSE_Pos)     | \
                    (CY_CAPSENSE_SM_CSX_FULL_WAVE_GPIO_REG_SW_SEL_GPIO_FLD_SW_CSD_SHIELD   << MSC_SW_SEL_GPIO_SW_CSD_SHIELD_Pos)    | \
                    (CY_CAPSENSE_SM_CSX_FULL_WAVE_GPIO_REG_SW_SEL_GPIO_FLD_SW_CSD_MUTUAL   << MSC_SW_SEL_GPIO_SW_CSD_MUTUAL_Pos)    | \
                    (CY_CAPSENSE_SM_CSX_FULL_WAVE_GPIO_REG_SW_SEL_GPIO_FLD_SW_CSD_POLARITY << MSC_SW_SEL_GPIO_SW_CSD_POLARITY_Pos)  | \
                    (CY_CAPSENSE_SM_CSX_FULL_WAVE_GPIO_REG_SW_SEL_GPIO_FLD_SW_CSD_CHARGE   << MSC_SW_SEL_GPIO_SW_CSD_CHARGE_Pos)    | \
                    (CY_CAPSENSE_SM_CSX_FULL_WAVE_GPIO_REG_SW_SEL_GPIO_FLD_SW_DSI_CMOD     << MSC_SW_SEL_GPIO_SW_DSI_CMOD_Pos)      | \
                    (CY_CAPSENSE_SM_CSX_FULL_WAVE_GPIO_REG_SW_SEL_GPIO_FLD_SW_DSI_CSH_TANK << MSC_SW_SEL_GPIO_SW_DSI_CSH_TANK_Pos)), \
        .swSelCdacRe = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_RE_FLD_SW_RETCA << MSC_SW_SEL_CDAC_RE_SW_RETCA_Pos) | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_RE_FLD_SW_RECB   << MSC_SW_SEL_CDAC_RE_SW_RECB_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_RE_FLD_SW_RETV   << MSC_SW_SEL_CDAC_RE_SW_RETV_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_RE_FLD_SW_RETG   << MSC_SW_SEL_CDAC_RE_SW_RETG_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_RE_FLD_SW_REBV   << MSC_SW_SEL_CDAC_RE_SW_REBV_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_RE_FLD_SW_REBG   << MSC_SW_SEL_CDAC_RE_SW_REBG_Pos)), \
        .swSelCdacCo = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CO_FLD_SW_COTCA << MSC_SW_SEL_CDAC_CO_SW_COTCA_Pos) | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CO_FLD_SW_COCB   << MSC_SW_SEL_CDAC_CO_SW_COCB_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CO_FLD_SW_COTV   << MSC_SW_SEL_CDAC_CO_SW_COTV_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CO_FLD_SW_COTG   << MSC_SW_SEL_CDAC_CO_SW_COTG_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CO_FLD_SW_COBV   << MSC_SW_SEL_CDAC_CO_SW_COBV_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CO_FLD_SW_COBG   << MSC_SW_SEL_CDAC_CO_SW_COBG_Pos)), \
        .swSelCdacCf = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CF_FLD_SW_CFTCA << MSC_SW_SEL_CDAC_CF_SW_CFTCA_Pos) | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CF_FLD_SW_CFTCB  << MSC_SW_SEL_CDAC_CF_SW_CFTCB_Pos) | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CF_FLD_SW_CFTV   << MSC_SW_SEL_CDAC_CF_SW_CFTV_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CF_FLD_SW_CFTG   << MSC_SW_SEL_CDAC_CF_SW_CFTG_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CF_FLD_SW_CFBV   << MSC_SW_SEL_CDAC_CF_SW_CFBV_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_SW_SEL_CDAC_CF_FLD_SW_CFBG   << MSC_SW_SEL_CDAC_CF_SW_CFBG_Pos)), \
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
        .obsCtl = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_OBS_CTL_FLD_OBSERVE0 << MSC_OBS_CTL_OBSERVE0_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_OBS_CTL_FLD_OBSERVE1  << MSC_OBS_CTL_OBSERVE1_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_OBS_CTL_FLD_OBSERVE2  << MSC_OBS_CTL_OBSERVE2_Pos)  | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_OBS_CTL_FLD_OBSERVE3  << MSC_OBS_CTL_OBSERVE3_Pos)), \
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
        .intrSet = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_SET_FLD_SUB_SAMPLE    << MSC_INTR_SET_SUB_SAMPLE_Pos)     | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_SET_FLD_SAMPLE         << MSC_INTR_SET_SAMPLE_Pos)         | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_SET_FLD_SCAN           << MSC_INTR_SET_SCAN_Pos)           | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_SET_FLD_INIT           << MSC_INTR_SET_INIT_Pos)           | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_SET_FLD_FRAME          << MSC_INTR_SET_FRAME_Pos)          | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_SET_FLD_FIFO_UNDERFLOW << MSC_INTR_SET_FIFO_UNDERFLOW_Pos) | \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_SET_FLD_FIFO_OVERFLOW  << MSC_INTR_SET_FIFO_OVERFLOW_Pos)), \
        .intrMask = \
                    ((CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_MASK_FLD_SUB_SAMPLE        << MSC_INTR_MASK_SUB_SAMPLE_Pos)     | \
                        (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_MASK_FLD_SAMPLE         << MSC_INTR_MASK_SAMPLE_Pos)         | \
                        (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_MASK_FLD_SCAN           << MSC_INTR_MASK_SCAN_Pos)           | \
                        (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_MASK_FLD_INIT           << MSC_INTR_MASK_INIT_Pos)           | \
                        (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_MASK_FLD_FRAME          << MSC_INTR_MASK_FRAME_Pos)          | \
                        (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_MASK_FLD_FIFO_UNDERFLOW << MSC_INTR_MASK_FIFO_UNDERFLOW_Pos) | \
                        (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_INTR_MASK_FLD_FIFO_OVERFLOW  << MSC_INTR_MASK_FIFO_OVERFLOW_Pos)), \
        .intrMasked         = 0x00uL, \
        .frameCmd = \
                    (CY_CAPSENSE_SM_BASE_FULL_WAVE_REG_FRAME_CMD_FLD_START_FRAME), \
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
            [CY_CAPSENSE_CTRLMUX_PIN_STATE_TX_NEGATIVE] = (CY_CAPSENSE_SM_REG_SW_SEL_CSW2_NEG_TX_VALUE), \
            [CY_CAPSENSE_CTRLMUX_PIN_STATE_SNS] = (CY_CAPSENSE_SM_REG_SW_SEL_CSW3_SNS_VALUE), \
            [CY_CAPSENSE_CTRLMUX_PIN_STATE_GND] = (CY_CAPSENSE_SM_REG_SW_SEL_CSW4_GND_VALUE), \
            [CY_CAPSENSE_CTRLMUX_PIN_STATE_HIGH_Z] = (CY_CAPSENSE_SM_REG_SW_SEL_CSW5_HIGH_Z_VALUE), \
            [CY_CAPSENSE_CTRLMUX_PIN_STATE_VDDA2] = (CY_CAPSENSE_SM_REG_SW_SEL_CSW6_VDDA2_VALUE), \
            [CY_CAPSENSE_CTRLMUX_PIN_STATE_SHIELD] = (CY_CAPSENSE_FW_SHIELD_ACTIVE_CTRLMUX_REG_SW_SEL_CSW_VALUE), \
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
                .swSelCdacFl = \
                        ((CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTCA        << MSC_MODE_SW_SEL_CDAC_FL_SW_FLTCA_Pos)         | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLCB         << MSC_MODE_SW_SEL_CDAC_FL_SW_FLCB_Pos)          | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTV         << MSC_MODE_SW_SEL_CDAC_FL_SW_FLTV_Pos)          | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTG         << MSC_MODE_SW_SEL_CDAC_FL_SW_FLTG_Pos)          | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLBV         << MSC_MODE_SW_SEL_CDAC_FL_SW_FLBV_Pos)          | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLBG         << MSC_MODE_SW_SEL_CDAC_FL_SW_FLBG_Pos)          | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_ACTIVATION_MODE << MSC_MODE_SW_SEL_CDAC_FL_ACTIVATION_MODE_Pos)), \
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
                .swSelComp = \
                        ((CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCS1        << MSC_MODE_SW_SEL_COMP_CPCS1_Pos)        | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCS3        << MSC_MODE_SW_SEL_COMP_CPCS3_Pos)        | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPMA         << MSC_MODE_SW_SEL_COMP_CPMA_Pos)         | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCA         << MSC_MODE_SW_SEL_COMP_CPCA_Pos)         | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCB         << MSC_MODE_SW_SEL_COMP_CPCB_Pos)         | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMCB         << MSC_MODE_SW_SEL_COMP_CMCB_Pos)         | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPF          << MSC_MODE_SW_SEL_COMP_CPF_Pos)          | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMCS2        << MSC_MODE_SW_SEL_COMP_CMCS2_Pos)        | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMCS4        << MSC_MODE_SW_SEL_COMP_CMCS4_Pos)        | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMV          << MSC_MODE_SW_SEL_COMP_CMV_Pos)          | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMG          << MSC_MODE_SW_SEL_COMP_CMG_Pos)          | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMF          << MSC_MODE_SW_SEL_COMP_CMF_Pos)          | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_HALF_WAVE_EN << MSC_MODE_SW_SEL_COMP_HALF_WAVE_EN_Pos)), \
                .swSelSh = \
                        ((CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_C1SHG   << MSC_MODE_SW_SEL_SH_C1SHG_Pos)   | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_C1SH    << MSC_MODE_SW_SEL_SH_C1SH_Pos)    | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_C3SHG   << MSC_MODE_SW_SEL_SH_C3SHG_Pos)   | \
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
                .swSelCdacFl = \
                        ((CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTCA        << MSC_MODE_SW_SEL_CDAC_FL_SW_FLTCA_Pos)         | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLCB         << MSC_MODE_SW_SEL_CDAC_FL_SW_FLCB_Pos)          | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTV         << MSC_MODE_SW_SEL_CDAC_FL_SW_FLTV_Pos)          | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTG         << MSC_MODE_SW_SEL_CDAC_FL_SW_FLTG_Pos)          | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLBV         << MSC_MODE_SW_SEL_CDAC_FL_SW_FLBV_Pos)          | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLBG         << MSC_MODE_SW_SEL_CDAC_FL_SW_FLBG_Pos)          | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_ACTIVATION_MODE << MSC_MODE_SW_SEL_CDAC_FL_ACTIVATION_MODE_Pos)), \
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
                .swSelComp = \
                        ((CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCS1        << MSC_MODE_SW_SEL_COMP_CPCS1_Pos)        | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCS3        << MSC_MODE_SW_SEL_COMP_CPCS3_Pos)        | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPMA         << MSC_MODE_SW_SEL_COMP_CPMA_Pos)         | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCA         << MSC_MODE_SW_SEL_COMP_CPCA_Pos)         | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCB         << MSC_MODE_SW_SEL_COMP_CPCB_Pos)         | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMCB         << MSC_MODE_SW_SEL_COMP_CMCB_Pos)         | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPF          << MSC_MODE_SW_SEL_COMP_CPF_Pos)          | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMCS2        << MSC_MODE_SW_SEL_COMP_CMCS2_Pos)        | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMCS4        << MSC_MODE_SW_SEL_COMP_CMCS4_Pos)        | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMV          << MSC_MODE_SW_SEL_COMP_CMV_Pos)          | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMG          << MSC_MODE_SW_SEL_COMP_CMG_Pos)          | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMF          << MSC_MODE_SW_SEL_COMP_CMF_Pos)          | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_HALF_WAVE_EN << MSC_MODE_SW_SEL_COMP_HALF_WAVE_EN_Pos)), \
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
            [CY_CAPSENSE_CSD_DITHERING_SENSING_METHOD_INDEX] = \
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
                .swSelCdacFl = \
                        ((CY_CAPSENSE_SM_CSD_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTCA        << MSC_MODE_SW_SEL_CDAC_FL_SW_FLTCA_Pos)         | \
                         (CY_CAPSENSE_SM_CSD_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLCB         << MSC_MODE_SW_SEL_CDAC_FL_SW_FLCB_Pos)          | \
                         (CY_CAPSENSE_SM_CSD_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTV         << MSC_MODE_SW_SEL_CDAC_FL_SW_FLTV_Pos)          | \
                         (CY_CAPSENSE_SM_CSD_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTG         << MSC_MODE_SW_SEL_CDAC_FL_SW_FLTG_Pos)          | \
                         (CY_CAPSENSE_SM_CSD_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLBV         << MSC_MODE_SW_SEL_CDAC_FL_SW_FLBV_Pos)          | \
                         (CY_CAPSENSE_SM_CSD_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLBG         << MSC_MODE_SW_SEL_CDAC_FL_SW_FLBG_Pos)          | \
                         (CY_CAPSENSE_SM_CSD_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_ACTIVATION_MODE << MSC_MODE_SW_SEL_CDAC_FL_ACTIVATION_MODE_Pos)), \
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
                .swSelComp = \
                        ((CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCS1        << MSC_MODE_SW_SEL_COMP_CPCS1_Pos)        | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCS3        << MSC_MODE_SW_SEL_COMP_CPCS3_Pos)        | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPMA         << MSC_MODE_SW_SEL_COMP_CPMA_Pos)         | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCA         << MSC_MODE_SW_SEL_COMP_CPCA_Pos)         | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCB         << MSC_MODE_SW_SEL_COMP_CPCB_Pos)         | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMCB         << MSC_MODE_SW_SEL_COMP_CMCB_Pos)         | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPF          << MSC_MODE_SW_SEL_COMP_CPF_Pos)          | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMCS2        << MSC_MODE_SW_SEL_COMP_CMCS2_Pos)        | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMCS4        << MSC_MODE_SW_SEL_COMP_CMCS4_Pos)        | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMV          << MSC_MODE_SW_SEL_COMP_CMV_Pos)          | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMG          << MSC_MODE_SW_SEL_COMP_CMG_Pos)          | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMF          << MSC_MODE_SW_SEL_COMP_CMF_Pos)          | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_HALF_WAVE_EN << MSC_MODE_SW_SEL_COMP_HALF_WAVE_EN_Pos)), \
                .swSelSh = \
                        ((CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_C1SHG   << MSC_MODE_SW_SEL_SH_C1SHG_Pos)   | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_C1SH    << MSC_MODE_SW_SEL_SH_C1SH_Pos)    | \
                         (CY_CAPSENSE_SM_CSD_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_SH_FLD_C3SHG   << MSC_MODE_SW_SEL_SH_C3SHG_Pos)   | \
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
            [CY_CAPSENSE_CSX_DITHERING_SENSING_METHOD_INDEX] = \
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
                .swSelCdacFl = \
                        ((CY_CAPSENSE_SM_CSX_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTCA        << MSC_MODE_SW_SEL_CDAC_FL_SW_FLTCA_Pos)         | \
                         (CY_CAPSENSE_SM_CSX_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLCB         << MSC_MODE_SW_SEL_CDAC_FL_SW_FLCB_Pos)          | \
                         (CY_CAPSENSE_SM_CSX_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTV         << MSC_MODE_SW_SEL_CDAC_FL_SW_FLTV_Pos)          | \
                         (CY_CAPSENSE_SM_CSX_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLTG         << MSC_MODE_SW_SEL_CDAC_FL_SW_FLTG_Pos)          | \
                         (CY_CAPSENSE_SM_CSX_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLBV         << MSC_MODE_SW_SEL_CDAC_FL_SW_FLBV_Pos)          | \
                         (CY_CAPSENSE_SM_CSX_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_SW_FLBG         << MSC_MODE_SW_SEL_CDAC_FL_SW_FLBG_Pos)          | \
                         (CY_CAPSENSE_SM_CSX_DITH_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_CDAC_FL_FLD_ACTIVATION_MODE << MSC_MODE_SW_SEL_CDAC_FL_ACTIVATION_MODE_Pos)), \
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
                .swSelComp = \
                        ((CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCS1        << MSC_MODE_SW_SEL_COMP_CPCS1_Pos)        | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCS3        << MSC_MODE_SW_SEL_COMP_CPCS3_Pos)        | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPMA         << MSC_MODE_SW_SEL_COMP_CPMA_Pos)         | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCA         << MSC_MODE_SW_SEL_COMP_CPCA_Pos)         | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPCB         << MSC_MODE_SW_SEL_COMP_CPCB_Pos)         | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMCB         << MSC_MODE_SW_SEL_COMP_CMCB_Pos)         | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CPF          << MSC_MODE_SW_SEL_COMP_CPF_Pos)          | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMCS2        << MSC_MODE_SW_SEL_COMP_CMCS2_Pos)        | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMCS4        << MSC_MODE_SW_SEL_COMP_CMCS4_Pos)        | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMV          << MSC_MODE_SW_SEL_COMP_CMV_Pos)          | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMG          << MSC_MODE_SW_SEL_COMP_CMG_Pos)          | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_CMF          << MSC_MODE_SW_SEL_COMP_CMF_Pos)          | \
                         (CY_CAPSENSE_SM_CSX_FULL_WAVE_CTRL_MUX_REG_MODE0_SW_SEL_COMP_FLD_HALF_WAVE_EN << MSC_MODE_SW_SEL_COMP_HALF_WAVE_EN_Pos)), \
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
        }, \
    }

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_M0S8MSCV3 */

#endif /* CY_CAPSENSE_GENERATOR_V3_H */


/* [] END OF FILE */
