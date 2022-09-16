/***************************************************************************//**
* \file cy_capsense_processing.h
* \version 3.0
*
* \brief
* This file provides the function prototypes for the Data Processing module.
* The Data Processing module is responsible for the low level raw counts
* processing provided by the sensing module, maintaining baseline and
* difference values and performing high-level widget processing like updating
* button status or calculating slider position.
*
********************************************************************************
* \copyright
* Copyright 2018-2021, Cypress Semiconductor Corporation (an Infineon company)
* or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_CAPSENSE_PROCESSING_H)
#define CY_CAPSENSE_PROCESSING_H

#include "cycfg_capsense_defines.h"
#include "cy_capsense_common.h"
#include "cy_capsense_structure.h"
#include "cy_capsense_lib.h"

#if (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3))


#if defined(__cplusplus)
extern "C" {
#endif


/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************/
/** \addtogroup group_capsense_high_level *//** \{ */
/******************************************************************************/
#if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_GESTURE_EN)
    uint32_t Cy_CapSense_DecodeWidgetGestures(
                    uint32_t widgetId,
                    const cy_stc_capsense_context_t * context);
#endif
/** \} */

/******************************************************************************/
/** \addtogroup group_capsense_low_level *//** \{ */
/******************************************************************************/
#if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_GESTURE_EN)
    void Cy_CapSense_InitializeWidgetGestures(
                    uint32_t widgetId,
                    const cy_stc_capsense_context_t * context);
#endif
void Cy_CapSense_InitializeAllStatuses(const cy_stc_capsense_context_t * context);
void Cy_CapSense_InitializeWidgetStatus(
                uint32_t widgetId,
                const cy_stc_capsense_context_t * context);

#if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_MULTI_PHASE_ENABLED)
        cy_capsense_status_t Cy_CapSense_ProcessWidgetMptxDeconvolution(
                        uint32_t widgetId,
                        cy_stc_capsense_context_t * context);
    #endif
void Cy_CapSense_PreProcessWidget(
                uint32_t widgetId,
                const cy_stc_capsense_context_t * context);
void Cy_CapSense_PreProcessSensor(
                uint32_t widgetId,
                uint32_t sensorId,
                const cy_stc_capsense_context_t * context);
    #if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_MULTI_FREQUENCY_WIDGET_EN)
        cy_capsense_status_t Cy_CapSense_RunMfsMedian(
                        uint32_t widgetId,
                        const cy_stc_capsense_context_t * context);
    #endif
#endif

/** \} */

/******************************************************************************/
/** \cond SECTION_CAPSENSE_INTERNAL */
/** \addtogroup group_capsense_internal *//** \{ */
/******************************************************************************/
#if((CY_CAPSENSE_DISABLE != CY_CAPSENSE_BUTTON_EN) ||\
    (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_MATRIX_EN))
    void Cy_CapSense_DpProcessButton(
                    const cy_stc_capsense_widget_config_t * ptrWdConfig);
#endif

#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSX_TOUCHPAD_EN)
    void Cy_CapSense_DpProcessCsxTouchpad(
                    const cy_stc_capsense_widget_config_t * ptrWdConfig);
#endif

#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_PROXIMITY_EN)
    void Cy_CapSense_DpProcessProximity(
                    const cy_stc_capsense_widget_config_t * ptrWdConfig);
#endif

#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_TOUCHPAD_EN)
    void Cy_CapSense_DpProcessCsdTouchpad(
                    const cy_stc_capsense_widget_config_t * ptrWdConfig,
                    const cy_stc_capsense_context_t * context);
#endif

#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_SLIDER_EN)
    void Cy_CapSense_DpProcessSlider(
                    const cy_stc_capsense_widget_config_t * ptrWdConfig);
#endif

#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_MATRIX_EN)
    void Cy_CapSense_DpProcessCsdMatrix(
                    const cy_stc_capsense_widget_config_t * ptrWdConfig);
#endif

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
void Cy_CapSense_DpProcessCsdWidgetStatus(
                const cy_stc_capsense_widget_config_t * ptrWdConfig,
                cy_stc_capsense_context_t * context);

uint32_t Cy_CapSense_DpProcessCsdWidgetRawCounts(
                uint32_t widgetId,
                const cy_stc_capsense_context_t * context);

uint32_t Cy_CapSense_DpProcessCsdSensorRawCountsExt(
                const cy_stc_capsense_widget_config_t * ptrWdConfig,
                cy_stc_capsense_sensor_context_t * ptrSnsContext,
                uint16_t * ptrSnsRawHistory,
                uint8_t * ptrSnsRawHistoryLow,
                uint32_t mode,
                uint16_t * ptrBslnInvSns,
                const cy_stc_capsense_context_t * context);
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
void Cy_CapSense_DpProcessCsxWidgetStatus(
                const cy_stc_capsense_widget_config_t * ptrWdConfig);

uint32_t Cy_CapSense_DpProcessCsxWidgetRawCounts(
                uint32_t widgetId,
                const cy_stc_capsense_context_t * context);

uint32_t Cy_CapSense_DpProcessCsxSensorRawCountsExt(
                const cy_stc_capsense_widget_config_t * ptrWdConfig,
                cy_stc_capsense_sensor_context_t * ptrSnsContext,
                uint16_t * ptrSnsRawHistory,
                uint8_t * ptrSnsRawHistoryLow,
                uint32_t mode,
                uint16_t * ptrSnsBslnInv,
                const cy_stc_capsense_context_t * context);
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

void Cy_CapSense_DpUpdateDifferences(
                const cy_stc_capsense_widget_context_t * ptrWdContext,
                cy_stc_capsense_sensor_context_t * ptrSnsContext);

void Cy_CapSense_DpUpdateThresholds(
                cy_stc_capsense_widget_context_t * ptrWdContext,
                const cy_stc_capsense_smartsense_csd_noise_envelope_t * ptrNoiseEnvelope,
                uint32_t startFlag);

#if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_MULTI_FREQUENCY_SCAN_EN)
    void Cy_CapSense_RunMfsFiltering(
                    cy_stc_capsense_sensor_context_t * ptrSnsContext,
                    const cy_stc_capsense_context_t * context);
#endif

#if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
void Cy_CapSense_PreProcessWidgetInvertRaw(
                uint32_t widgetId,
                const cy_stc_capsense_context_t * context);
void Cy_CapSense_PreProcessSensorInvertRaw(
                uint32_t widgetId,
                uint32_t sensorId,
                const cy_stc_capsense_context_t * context);
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

void Cy_CapSense_PreProcessWidgetLimitRaw(
                uint32_t widgetId,
                const cy_stc_capsense_context_t * context);
void Cy_CapSense_PreProcessSensorLimitRaw(
                uint32_t widgetId,
                uint32_t sensorId,
                const cy_stc_capsense_context_t * context);
#if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CIC2_FILTER_EN)
void Cy_CapSense_PreProcessWidgetCic2Raw(
                uint32_t widgetId,
                const cy_stc_capsense_context_t * context);
void Cy_CapSense_PreProcessSensorCic2Raw(
                uint32_t widgetId,
                uint32_t sensorId,
                const cy_stc_capsense_context_t * context);
uint32_t Cy_CapSense_GetCIC2HwDivider(
                uint32_t cic2Samples);
#endif

#endif /* CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN */
/** \} \endcond */

#if defined(__cplusplus)
}
#endif

#endif /* (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3)) */

#endif /* CY_CAPSENSE_PROCESSING_H */


/* [] END OF FILE */
