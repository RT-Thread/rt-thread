/***************************************************************************//**
* \file cy_capsense_filter.h
* \version 3.0
*
* \brief
* This file contains the definitions for all the filters implementation.
*
********************************************************************************
* \copyright
* Copyright 2018-2021, Cypress Semiconductor Corporation (an Infineon company)
* or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_CAPSENSE_FILTER_H)
#define CY_CAPSENSE_FILTER_H

#include "cy_syslib.h"

#include "cycfg_capsense_defines.h"
#include "cy_capsense_structure.h"
#include "cy_capsense_common.h"

#if (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3))

#if defined(__cplusplus)
extern "C" {
#endif


/***************************************
* Function Prototypes
***************************************/

/*******************************************************************************
* LOW LEVEL FUNCTIONS
*******************************************************************************/

/******************************************************************************/
/** \addtogroup group_capsense_low_level *//** \{ */
/******************************************************************************/

void Cy_CapSense_InitializeAllBaselines(cy_stc_capsense_context_t * context);
void Cy_CapSense_InitializeWidgetBaseline(uint32_t widgetId, cy_stc_capsense_context_t * context);
void Cy_CapSense_InitializeSensorBaseline(uint32_t widgetId, uint32_t sensorId, cy_stc_capsense_context_t * context);

#if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_RAWCOUNT_FILTER_EN)
    void Cy_CapSense_InitializeAllFilters(const cy_stc_capsense_context_t * context);
    void Cy_CapSense_InitializeWidgetFilter(uint32_t widgetId, const cy_stc_capsense_context_t * context);
#endif

cy_capsense_status_t Cy_CapSense_UpdateAllBaselines(const cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_UpdateWidgetBaseline(uint32_t widgetId, const cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_UpdateSensorBaseline(uint32_t widgetId, uint32_t sensorId, const cy_stc_capsense_context_t * context);

/** \} */


/*******************************************************************************
* Function Prototypes - Internal functions
*******************************************************************************/

/******************************************************************************/
/** \cond SECTION_CAPSENSE_INTERNAL */
/** \addtogroup group_capsense_internal *//** \{ */
/******************************************************************************/
void Cy_CapSense_FtInitializeBaseline(
                cy_stc_capsense_sensor_context_t * ptrSnsContext);
cy_capsense_status_t Cy_CapSense_FtUpdateBaseline(
                cy_stc_capsense_widget_context_t * ptrWdContext,
                cy_stc_capsense_sensor_context_t * ptrSnsContext,
                uint16_t * ptrSnsBslnInv,
                const cy_stc_capsense_context_t * context);

#if (CY_CAPSENSE_POS_MEDIAN_FILTER_EN || CY_CAPSENSE_REGULAR_RC_MEDIAN_FILTER_EN \
    || CY_CAPSENSE_PROX_RC_MEDIAN_FILTER_EN || CY_CAPSENSE_MULTI_FREQUENCY_SCAN_EN || CY_CAPSENSE_MULTI_FREQUENCY_WIDGET_EN)
    uint32_t Cy_CapSense_FtMedian(uint32_t x1, uint32_t x2, uint32_t x3);
#endif

uint32_t Cy_CapSense_FtIIR1stOrder(uint32_t input, uint32_t prevOutput, uint32_t n);

#if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_POS_JITTER_FILTER_EN)
    uint32_t Cy_CapSense_FtJitter(uint32_t input, uint32_t prevOutput);
#endif

#if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_RAWCOUNT_FILTER_EN)
    void Cy_CapSense_FtRunEnabledFiltersInternal(
                    const cy_stc_capsense_widget_config_t * ptrWdConfig,
                    cy_stc_capsense_sensor_context_t * ptrSnsContext,
                    uint16_t * ptrSnsRawHistory,
                    uint8_t * ptrSnsRawHistoryLow);
#endif

#if (CY_CAPSENSE_REGULAR_RC_IIR_FILTER_EN || CY_CAPSENSE_PROX_RC_IIR_FILTER_EN)
    void Cy_CapSense_InitializeIIRInternal(
                    const cy_stc_capsense_widget_config_t * ptrWdConfig,
                    const cy_stc_capsense_sensor_context_t * ptrSnsContext,
                    uint16_t * ptrSnsRawHistory,
                    uint8_t * ptrSnsRawHistoryLow);
    void Cy_CapSense_RunIIRInternal(
                    const cy_stc_capsense_widget_config_t * ptrWdConfig,
                    cy_stc_capsense_sensor_context_t * ptrSnsContext,
                    uint16_t * ptrSnsRawHistory,
                    uint8_t * ptrSnsRawHistoryLow);
#endif

#if (CY_CAPSENSE_REGULAR_RC_MEDIAN_FILTER_EN || CY_CAPSENSE_PROX_RC_MEDIAN_FILTER_EN)
    void Cy_CapSense_InitializeMedianInternal(
                    const cy_stc_capsense_widget_config_t * ptrWdConfig,
                    const cy_stc_capsense_sensor_context_t * ptrSnsContext,
                    uint16_t * ptrSnsRawHistory);
    void Cy_CapSense_RunMedianInternal(
                    const cy_stc_capsense_widget_config_t * ptrWdConfig,
                    cy_stc_capsense_sensor_context_t * ptrSnsContext,
                    uint16_t * ptrSnsRawHistory);
#endif

#if (CY_CAPSENSE_REGULAR_RC_AVERAGE_FILTER_EN || CY_CAPSENSE_PROX_RC_AVERAGE_FILTER_EN)
    void Cy_CapSense_InitializeAverageInternal(
                    const cy_stc_capsense_widget_config_t * ptrWdConfig,
                    const cy_stc_capsense_sensor_context_t * ptrSnsContext,
                    uint16_t * ptrSnsRawHistory);
    void Cy_CapSense_RunAverageInternal(
                    const cy_stc_capsense_widget_config_t * ptrWdConfig,
                    cy_stc_capsense_sensor_context_t * ptrSnsContext,
                    uint16_t * ptrSnsRawHistory);
#endif

/** \} \endcond */

#if defined(__cplusplus)
}
#endif

#endif /* (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3)) */

#endif /* CY_CAPSENSE_FILTER_H */


/* [] END OF FILE */
