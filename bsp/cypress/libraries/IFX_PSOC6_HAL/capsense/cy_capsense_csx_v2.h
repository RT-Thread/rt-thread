/***************************************************************************//**
* \file cy_capsense_csx_v2.h
* \version 3.0
*
* \brief
* This file provides the function prototypes specific to the CSX sensing
* implementation.
*
********************************************************************************
* \copyright
* Copyright 2018-2021, Cypress Semiconductor Corporation (an Infineon company)
* or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_CAPSENSE_CSX_V2_H)
#define CY_CAPSENSE_CSX_V2_H

#include "cy_syslib.h"
#include "cycfg_capsense_defines.h"
#include "cy_capsense_structure.h"
#include "cy_capsense_common.h"

#if (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2))

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)

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

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN)
    cy_capsense_status_t Cy_CapSense_CSXCalibrateWidget(uint32_t widgetId, uint32_t target, cy_stc_capsense_context_t * context);
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN) */

void Cy_CapSense_CSXSetupWidget(uint32_t widgetId, cy_stc_capsense_context_t * context);
void Cy_CapSense_CSXSetupWidgetExt(uint32_t widgetId, uint32_t sensorId, cy_stc_capsense_context_t * context);
void Cy_CapSense_CSXScan(cy_stc_capsense_context_t * context);
void Cy_CapSense_CSXScanExt(cy_stc_capsense_context_t * context);

void Cy_CapSense_CSXConnectRx(const cy_stc_capsense_pin_config_t * rxPtr, const cy_stc_capsense_context_t * context);
void Cy_CapSense_CSXConnectTx(const cy_stc_capsense_pin_config_t * txPtr, const cy_stc_capsense_context_t * context);
void Cy_CapSense_CSXDisconnectRx(const cy_stc_capsense_pin_config_t * rxPtr, const cy_stc_capsense_context_t * context);
void Cy_CapSense_CSXDisconnectTx(const cy_stc_capsense_pin_config_t * txPtr, const cy_stc_capsense_context_t * context);

void Cy_CapSense_CSXConnectRxExt(cy_stc_capsense_context_t * context);
void Cy_CapSense_CSXConnectTxExt(cy_stc_capsense_context_t * context);
void Cy_CapSense_CSXDisconnectRxExt(const cy_stc_capsense_context_t * context);
void Cy_CapSense_CSXDisconnectTxExt(const cy_stc_capsense_context_t * context);

void Cy_CapSense_CSXSetUpIdacs(cy_stc_capsense_context_t * context);
void Cy_CapSense_CSXDisableMode(cy_stc_capsense_context_t * context);
void Cy_CapSense_CSXInitialize(cy_stc_capsense_context_t * context);
void Cy_CapSense_CSXElectrodeCheck(cy_stc_capsense_context_t * context);

void Cy_CapSense_CSXSetWidgetTxClkSrc(const cy_stc_capsense_widget_config_t * ptrWdConfig);

void Cy_CapSense_CSXScanISR(void * capsenseContext);

/** \} \endcond */

/*******************************************************************************
* Local definition
*******************************************************************************/
#define CY_CAPSENSE_CSX_DEADBAND_CYCLES_NUMBER              (2u)
#define CY_CAPSENSE_CSX_PRECHARGE_MAX_TIME_US               (1000u)
#define CY_CAPSENSE_CSX_WATCHDOG_MARGIN_COEFF               (3u)
#define CY_CAPSENSE_CSX_PRECHARGE_WATCHDOG_TIME_US          (CY_CAPSENSE_CSX_PRECHARGE_MAX_TIME_US *\
                                                             CY_CAPSENSE_CSX_WATCHDOG_MARGIN_COEFF)


/*******************************************************************************
* CSD HW block registers configuration, required for the CSX mode initialization
*******************************************************************************/
#define CY_CAPSENSE_DEFAULT_CSD_CONFIG_CFG                  (0x800C1020u)
#define CY_CAPSENSE_DEFAULT_CSD_INTR_MASK_CFG               (CY_CAPSENSE_CSD_INTR_MASK_SAMPLE_MSK)
#define CY_CAPSENSE_DEFAULT_CSD_HSCMP_CFG                   (0x00000000u)
#define CY_CAPSENSE_DEFAULT_CSD_AMBUF_CFG                   (0x00000000u)
#define CY_CAPSENSE_LOW_VOLTAGE_CSD_AMBUF_CFG               (0x00000001u)
/* Intended to be used for PSoC&trade; 4 devices in case if VDDA >= 2V */
#define CY_CAPSENSE_DEFAULT_CSD_REFGEN_CFG                  (0x00001F41u)
/* Intended to be used for PSoC&trade; 4 devices in case if VDDA < 2V */
#define CY_CAPSENSE_LOW_VOLTAGE_CSD_REFGEN_CFG              (0x00800011u)
/* Intended to be used for PSoC&trade; 6 devices in case if the PASS is selected as the VREF source */
#define CY_CAPSENSE_PASS_CSD_REFGEN_CFG                     (0x00001F41u)
/* Intended to be used for PSoC&trade; 6 devices in case if the SRSS is selected as the VREF source */
#define CY_CAPSENSE_SRSS_CSD_REFGEN_CFG                     (0x00001541u)
#define CY_CAPSENSE_DEFAULT_CSD_CSDCMP_CFG                  (0x00000300u)
#define CY_CAPSENSE_DEFAULT_CSD_IDACA_CFG                   (0x010F0E80u)
#define CY_CAPSENSE_DEFAULT_CSD_IDACB_CFG                   (0x00000000u)
#define CY_CAPSENSE_DEFAULT_CSD_SENSE_DUTY_CFG              (0x00000000u)
#define CY_CAPSENSE_DEFAULT_CSD_SW_HS_P_SEL_CFG             (0x00000000u)
#define CY_CAPSENSE_DEFAULT_CSD_SW_HS_N_SEL_CFG             (0x00000000u)
#define CY_CAPSENSE_DEFAULT_CSD_SW_SHIELD_SEL_CFG           (0x00000000u)
#define CY_CAPSENSE_DEFAULT_CSD_SW_AMUXBUF_SEL_CFG          (0x00000000u)
#define CY_CAPSENSE_LOW_VOLTAGE_CSD_SW_AMUXBUF_SEL_CFG      (0x01000100u)

#if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
    #define CY_CAPSENSE_DEFAULT_CSD_SW_BYP_SEL_CFG          (0x00001000u)
#else
    #define CY_CAPSENSE_DEFAULT_CSD_SW_BYP_SEL_CFG          (0x00000000u)
#endif

#if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
    #define CY_CAPSENSE_DEFAULT_CSD_SW_CMP_P_SEL_CFG        (0x00000032u)
#else
    #define CY_CAPSENSE_DEFAULT_CSD_SW_CMP_P_SEL_CFG        (0x00000023u)
#endif

#define CY_CAPSENSE_DEFAULT_CSD_SW_CMP_N_SEL_CFG            (0x01000000u)
#define CY_CAPSENSE_LOW_VOLTAGE_CSD_SW_CMP_N_SEL_CFG        (0x10000000u)

#if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
    #define CY_CAPSENSE_DEFAULT_CSD_SW_FW_MOD_SEL_CFG       (0x00000000u)
#else
    #define CY_CAPSENSE_DEFAULT_CSD_SW_FW_MOD_SEL_CFG       (0x00030301u)
#endif

#if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
    #define CY_CAPSENSE_DEFAULT_CSD_SW_FW_TANK_SEL_CFG      (0x00000000u)
#else
    #define CY_CAPSENSE_DEFAULT_CSD_SW_FW_TANK_SEL_CFG      (0x00002210u)
#endif

#define CY_CAPSENSE_DEFAULT_CSD_SW_IO_SEL_CFG               (0x0000001Fu)

#if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
    #define CY_CAPSENSE_DEFAULT_CSD_SW_DSI_SEL_CFG          (0x00000023u)
#else
    #define CY_CAPSENSE_DEFAULT_CSD_SW_DSI_SEL_CFG          (0x00000000u)
#endif

#define CY_CAPSENSE_DEFAULT_CSD_SEQ_NORM_CNT_CFG            (0x00000000u)
#define CY_CAPSENSE_DEFAULT_CSD_ADC_CTL_CFG                 (0x00000000u)
#define CY_CAPSENSE_DEFAULT_CSD_SEQ_START_CFG               (0x00000308u)


/*******************************************************************************
* CSD HW block registers configuration, required for coarse initialization of
* integration capacitors
*******************************************************************************/
#define CY_CAPSENSE_PRESCAN_CSD_CONFIG_CFG                  (0x800C1000u)
#define CY_CAPSENSE_PRESCAN_CSD_CSDCMP_CFG                  (0x00000301u)
#define CY_CAPSENSE_PRECHARGE_CSD_HSCMP_CFG                 (0x00000001u)
#define CY_CAPSENSE_PRECHARGE_CSD_SW_HS_P_SEL_CFG           (0x00000011u)
#define CY_CAPSENSE_PRECHARGE_CSD_SW_HS_N_SEL_CFG           (0x01000000u)

#if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
    #define CY_CAPSENSE_PRECHARGE_CSD_SW_DSI_SEL_CFG        (0x00000011u)
#else
    #define CY_CAPSENSE_PRECHARGE_CSD_SW_DSI_SEL_CFG        (0x00000000u)
#endif

#define CY_CAPSENSE_PRECHARGE_CSD_SW_SHIELD_SEL_CFG         (0x00000006u)
#define CY_CAPSENSE_PRECHARGE_CSD_SW_FW_MOD_SEL_CFG         (0x00010101u)

#if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
    #define CY_CAPSENSE_PRECHARGE_CSD_SW_FW_TANK_SEL_CFG    (0x00001010u)
#else
    #define CY_CAPSENSE_PRECHARGE_CSD_SW_FW_TANK_SEL_CFG    (0x00001110u)
#endif

#define CY_CAPSENSE_PRECHARGE_CSD_SEQ_START_CFG             (0x00000303u)


/*******************************************************************************
* CSD HW block registers configuration, required to perform the CSX scan
*******************************************************************************/
#if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
    #define CY_CAPSENSE_SCAN_CSD_SW_FW_MOD_SEL_CFG          (0x00000000u)
#else
    #define CY_CAPSENSE_SCAN_CSD_SW_FW_MOD_SEL_CFG          (0x00030301u)
#endif

#if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
    #define CY_CAPSENSE_SCAN_CSD_SW_FW_TANK_SEL_CFG         (0x00000000u)
#else
    #define CY_CAPSENSE_SCAN_CSD_SW_FW_TANK_SEL_CFG         (0x00002210u)
#endif

#define CY_CAPSENSE_SCAN_CSD_SEQ_START_CFG                  (0x00000301u)

#if defined(__cplusplus)
}
#endif

#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

#endif /* (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2)) */

#endif  /* CY_CAPSENSE_CSX_V2_H */


/* [] END OF FILE */
