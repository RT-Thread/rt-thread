/***************************************************************************//**
* \file cy_capsense_control.h
* \version 3.0
*
* \brief
* This file provides the function prototypes of the Control module.
*
********************************************************************************
* \copyright
* Copyright 2018-2021, Cypress Semiconductor Corporation (an Infineon company)
* or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_CAPSENSE_CONTROL_H)
#define CY_CAPSENSE_CONTROL_H

#include "cy_syspm.h"
#include "cy_capsense_structure.h"
#include "cy_capsense_common.h"

#if (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3))

#if defined(__cplusplus)
extern "C" {
#endif


/*******************************************************************************
* Local definition
*******************************************************************************/
#define CY_CAPSENSE_ANALOG_SETTLING_TIME_US             (25u)


/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************/
/** \addtogroup group_capsense_high_level *//** \{ */
/******************************************************************************/

cy_capsense_status_t Cy_CapSense_Init(cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_DeInit(cy_stc_capsense_context_t * context);

cy_capsense_status_t Cy_CapSense_Enable(cy_stc_capsense_context_t * context);

cy_capsense_status_t Cy_CapSense_Save(cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_Restore(cy_stc_capsense_context_t * context);

cy_capsense_status_t Cy_CapSense_ProcessAllWidgets(
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_ProcessWidget(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context);

#if ((CY_CAPSENSE_DISABLE != CY_CAPSENSE_GESTURE_EN) || \
     (CY_CAPSENSE_DISABLE != CY_CAPSENSE_BALLISTIC_MULTIPLIER_EN))
    void Cy_CapSense_IncrementGestureTimestamp(cy_stc_capsense_context_t * context);
    void Cy_CapSense_SetGestureTimestamp(
                    uint32_t value,
                    cy_stc_capsense_context_t * context);
#endif

void Cy_CapSense_Wakeup(const cy_stc_capsense_context_t * context);

cy_en_syspm_status_t Cy_CapSense_DeepSleepCallback(
                cy_stc_syspm_callback_params_t * callbackParams,
                cy_en_syspm_callback_mode_t mode);

cy_capsense_status_t Cy_CapSense_RegisterCallback(
                cy_en_capsense_callback_event_t callbackType,
                cy_capsense_callback_t callbackFunction,
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_UnRegisterCallback(
                cy_en_capsense_callback_event_t callbackType,
                cy_stc_capsense_context_t * context);


/** \} */

/******************************************************************************/
/** \addtogroup group_capsense_low_level *//** \{ */
/******************************************************************************/

cy_capsense_status_t Cy_CapSense_ProcessWidgetExt(
                uint32_t widgetId,
                uint32_t mode,
                cy_stc_capsense_context_t * context);
cy_capsense_status_t Cy_CapSense_ProcessSensorExt(
                uint32_t widgetId,
                uint32_t sensorId,
                uint32_t mode,
                const cy_stc_capsense_context_t * context);
/** \} */

/******************************************************************************/
/** \cond SECTION_CAPSENSE_INTERNAL */
/** \addtogroup group_capsense_internal *//** \{ */
/******************************************************************************/

cy_capsense_status_t Cy_CapSense_Initialize(
    cy_stc_capsense_context_t * context);

/** \} \endcond */

#if defined(__cplusplus)
}
#endif

#endif /* (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3)) */

#endif /* CY_CAPSENSE_CONTROL_H */


/* [] END OF FILE */
