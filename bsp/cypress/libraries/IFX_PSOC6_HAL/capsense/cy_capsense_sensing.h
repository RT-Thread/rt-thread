/***************************************************************************//**
* \file cy_capsense_sensing.h
* \version 3.0
*
* \brief
* This file provides the common function prototypes for different supported
* platforms like fourth and fifth generation platforms.
*
********************************************************************************
* \copyright
* Copyright 2021, Cypress Semiconductor Corporation (an Infineon company)
* or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_SENSING_H)
#define CY_CAPSENSE_SENSING_H

#include "cycfg_capsense_defines.h"
#include "cy_capsense_common.h"
#include "cy_capsense_structure.h"

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
cy_capsense_status_t Cy_CapSense_ScanAllWidgets(
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_ScanWidget(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context);
uint32_t Cy_CapSense_IsBusy(
                const cy_stc_capsense_context_t * context);
void Cy_CapSense_InterruptHandler(
                void * base,
                cy_stc_capsense_context_t * context);
/** \} */

/******************************************************************************/
/** \addtogroup group_capsense_low_level *//** \{ */
/******************************************************************************/
cy_capsense_status_t Cy_CapSense_CalibrateAllWidgets(
                cy_stc_capsense_context_t * context);
#if (((CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN) && (1u == CY_CAPSENSE_TOTAL_CH_NUMBER)) || (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN))
cy_capsense_status_t Cy_CapSense_CalibrateWidget(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context);
#endif
cy_capsense_status_t Cy_CapSense_ScanSensor(
                uint32_t widgetId,
                uint32_t sensorId,
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_SetPinState(
                uint32_t widgetId,
                uint32_t sensorElement,
                uint32_t state,
                const cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_SetInactiveElectrodeState(
                uint32_t inactiveState,
                uint32_t sensingGroup,
                cy_stc_capsense_context_t * context);
/** \} */


/******************************************************************************/
/** \cond SECTION_CAPSENSE_INTERNAL */
/** \addtogroup group_capsense_internal *//** \{ */
/******************************************************************************/
#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
    void Cy_CapSense_SetCsdInactiveState(
                    cy_stc_capsense_context_t * context);
#endif

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
    void Cy_CapSense_SetCsxInactiveState(
                    cy_stc_capsense_context_t * context);
#endif
/** \} \endcond */

#if defined(__cplusplus)
}
#endif

#endif /* (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3)) */

#endif/* CY_CAPSENSE_SENSING_H */


/* [] END OF FILE */
