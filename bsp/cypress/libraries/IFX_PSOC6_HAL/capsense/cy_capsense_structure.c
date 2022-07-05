/***************************************************************************//**
* \file cy_capsense_structure.c
* \version 3.0
*
* \brief
* This file defines the data structure global variables and provides the
* implementation for the functions of the Data Structure module.
*
********************************************************************************
* \copyright
* Copyright 2018-2021, Cypress Semiconductor Corporation (an Infineon company)
* or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include <stddef.h>
#include <string.h>
#include "cycfg_capsense_defines.h"
#include "cy_syslib.h"
#include "cy_utils.h"
#include "cy_capsense_common.h"
#include "cy_capsense_structure.h"
#include "cy_capsense_lib.h"
#include "cy_capsense_selftest.h"
#if (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN)
    #include "cy_csd.h"
#else /* (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN) */
    #include "cy_msc.h"
#endif
#include "cycfg_capsense_defines.h"

#if (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3))

/*******************************************************************************
* Local definition
*******************************************************************************/
#define CY_CAPSENSE_DS_PARAM_TYPE_UINT8     (1u)
#define CY_CAPSENSE_DS_PARAM_TYPE_UINT16    (2u)
#define CY_CAPSENSE_DS_PARAM_TYPE_UINT32    (3u)
#define CY_CAPSENSE_UINT16_ALIGN_MASK       (1u)
#define CY_CAPSENSE_UINT32_ALIGN_MASK       (3u)
#define CY_CAPSENSE_PARAM_TYPE_OFFSET       (24u)
#define CY_CAPSENSE_PARAM_TYPE_MASK         (3uL << CY_CAPSENSE_PARAM_TYPE_OFFSET)
#define CY_CAPSENSE_PARAM_CRC_OFFSET        (26u)
#define CY_CAPSENSE_PARAM_CRC_MASK          (1uL << CY_CAPSENSE_PARAM_CRC_OFFSET)
#define CY_CAPSENSE_PARAM_WIDGET_OFFSET     (16u)
#define CY_CAPSENSE_PARAM_WIDGET_MASK       (0xFFuL << CY_CAPSENSE_PARAM_WIDGET_OFFSET)


/*******************************************************************************
* Function Name: Cy_CapSense_IsAnyWidgetActive
****************************************************************************//**
*
* Reports whether any widget has detected touch.
*
* This function reports whether any widget has detected a touch by extracting
* information from the widget status registers. This function does
* not process widget data but extracts previously processed results
* from the \ref group_capsense_structures.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the touch detection status of all the widgets:
* - Zero - No touch is detected in any of the widgets or sensors.
* - Non-zero - At least one widget or sensor has detected a touch.
*
*******************************************************************************/
uint32_t Cy_CapSense_IsAnyWidgetActive(const cy_stc_capsense_context_t * context)
{
    uint32_t capStatus = 0u;
    uint32_t wdIndex;

    for (wdIndex = context->ptrCommonConfig->numWd; wdIndex-- > 0u;)
    {
        capStatus |= (uint32_t)context->ptrWdContext[wdIndex].status & CY_CAPSENSE_WD_ACTIVE_MASK;
    }

    return capStatus;
}


/*******************************************************************************
* Function Name: Cy_CapSense_IsWidgetActive
****************************************************************************//**
*
* Reports whether the specified widget detected touch on any of its sensors.
*
* This function reports whether the specified widget has detected a touch by
* extracting information from the widget status register.
* This function does not process widget data but extracts previously processed
* results from the \ref group_capsense_structures.
*
* \param widgetId
* Specifies the ID number of the widget. A macro for the widget ID can be found
* in the cycfg_capsense.h file defined as CY_CAPSENSE_<WIDGET_NAME>_WDGT_ID.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the touch detection status of the specified widgets:
* - Zero - No touch is detected in the specified widget or a wrong widgetId
* is specified.
* - Non-zero if at least one sensor of the specified widget is active, i.e.
* a touch is detected.
*
*******************************************************************************/
uint32_t Cy_CapSense_IsWidgetActive(
                uint32_t widgetId,
                const cy_stc_capsense_context_t * context)
{
    uint32_t capStatus = 0uL;

    if (widgetId < context->ptrCommonConfig->numWd)
    {
        capStatus = (uint32_t)context->ptrWdContext[widgetId].status & CY_CAPSENSE_WD_ACTIVE_MASK;
    }
    return capStatus;
}


/*******************************************************************************
* Function Name: Cy_CapSense_IsSensorActive
****************************************************************************//**
*
* Reports whether the specified sensor in the widget detected touch.
*
* This function reports whether the specified sensor in the widget has detected a
* touch by extracting information from the widget status register.
* This function does not process widget or sensor data but extracts previously
* processed results from the \ref group_capsense_structures.
*
* For proximity sensors, this function returns the proximity detection status.
* To get the touch status of proximity sensors, use the
* Cy_CapSense_IsProximitySensorActive() function.
*
* \param widgetId
* Specifies the ID number of the widget. A macro for the widget ID can be found
* in the cycfg_capsense.h file defined as CY_CAPSENSE_<WIDGET_NAME>_WDGT_ID.
*
* \param sensorId
* Specifies the ID number of the sensor within the widget. A macro for the
* sensor ID within a specified widget can be found in the cycfg_capsense.h
* file defined as CY_CAPSENSE_<WIDGET_NAME>_SNS<SENSOR_NUMBER>_ID.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the touch detection status of the specified sensor/widget:
* - Zero if no touch is detected in the specified sensor/widget or a wrong
* widget ID/sensor ID is specified.
* - Non-zero if the specified sensor is active, i.e. touch is detected. If the
* specific sensor belongs to a proximity widget, the proximity detection
* status is returned.
*
*******************************************************************************/
uint32_t Cy_CapSense_IsSensorActive(
                uint32_t widgetId,
                uint32_t sensorId,
                const cy_stc_capsense_context_t * context)
{
    uint32_t capStatus = 0uL;

    if (widgetId < context->ptrCommonConfig->numWd)
    {
        if (sensorId < context->ptrWdConfig[widgetId].numSns)
        {
            capStatus = context->ptrWdConfig[widgetId].ptrSnsContext[sensorId].status;
        }
    }
    return capStatus;
}


#if(CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_PROXIMITY_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_IsProximitySensorActive
****************************************************************************//**
*
* Reports the status of the specified proximity widget/sensor.
*
* This function reports whether the specified proximity sensor has detected
* a touch or proximity event by extracting information from the widget
* status register. This function is used only with proximity widgets.
* This function does not process widget data but extracts previously processed
* results from the \ref group_capsense_structures.
*
* \param widgetId
* Specifies the ID number of the widget. A macro for the widget ID can be found
* in the cycfg_capsense.h file defined as CY_CAPSENSE_<WIDGET_NAME>_WDGT_ID.
*
* \param sensorId
* Specifies the ID number of the sensor within the widget. A macro for the
* sensor ID within a specified widget can be found in the cycfg_capsense.h
* file defined as CY_CAPSENSE_<WIDGET_NAME>_SNS<SENSOR_NUMBER>_ID.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the specified sensor of the proximity widget. Zero
* indicates that no touch is detected in the specified sensor/widget or a
* wrong widgetId/proxId is specified.
* - Bits [31..2] are reserved.
* - Bit [1] indicates that a touch is detected.
* - Bit [0] indicates that a proximity is detected.
*
*******************************************************************************/
uint32_t Cy_CapSense_IsProximitySensorActive(
                uint32_t widgetId,
                uint32_t sensorId,
                const cy_stc_capsense_context_t * context)
{
    uint32_t capStatus = 0uL;

    if (widgetId < context->ptrCommonConfig->numWd)
    {
        if ((uint8_t)CY_CAPSENSE_WD_PROXIMITY_E == context->ptrWdConfig[widgetId].wdType)
        {
            if (sensorId < context->ptrWdConfig[widgetId].numSns)
            {
                capStatus |= context->ptrWdConfig[widgetId].ptrSnsContext[sensorId].status;
            }
        }
    }

    return capStatus;
}
#endif /* (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_PROXIMITY_EN) */


#if((CY_CAPSENSE_DISABLE != CY_CAPSENSE_TOUCHPAD_EN) ||\
    (CY_CAPSENSE_DISABLE != CY_CAPSENSE_MATRIX_EN) ||\
    (CY_CAPSENSE_DISABLE != CY_CAPSENSE_SLIDER_EN))
/*******************************************************************************
* Function Name: Cy_CapSense_GetTouchInfo
****************************************************************************//**
*
* Reports the details of touch position detected on the specified touchpad,
* matrix buttons or slider widgets.
*
* This function does not process widget data but extracts previously processed
* results from the \ref group_capsense_structures.
*
* \param widgetId
* Specifies the ID number of the widget. A macro for the widget ID can be found
* in the cycfg_capsense.h file defined as CY_CAPSENSE_<WIDGET_NAME>_WDGT_ID.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the pointer to widget cy_stc_capsense_touch_t structure that
* contains number of positions and data about each position.
*
*
*******************************************************************************/
cy_stc_capsense_touch_t * Cy_CapSense_GetTouchInfo(
                uint32_t widgetId,
                const cy_stc_capsense_context_t * context)
{
    cy_stc_capsense_touch_t * ptrTouch = NULL;

    const cy_stc_capsense_widget_config_t * ptrWdCfg;

    if (widgetId < context->ptrCommonConfig->numWd)
    {
        ptrWdCfg = &context->ptrWdConfig[widgetId];
        switch (ptrWdCfg->wdType)
        {
            case (uint8_t)CY_CAPSENSE_WD_TOUCHPAD_E:
            case (uint8_t)CY_CAPSENSE_WD_MATRIX_BUTTON_E:
            case (uint8_t)CY_CAPSENSE_WD_LINEAR_SLIDER_E:
            case (uint8_t)CY_CAPSENSE_WD_RADIAL_SLIDER_E:
                ptrTouch = &ptrWdCfg->ptrWdContext->wdTouch;
                break;

            default:
                /* No action on other widget types */
                break;
        }
    }

    return ptrTouch;
}
#endif /* ((CY_CAPSENSE_DISABLE != CY_CAPSENSE_TOUCHPAD_EN) ||\
           (CY_CAPSENSE_DISABLE != CY_CAPSENSE_MATRIX_EN) ||\
           (CY_CAPSENSE_DISABLE != CY_CAPSENSE_SLIDER_EN)) */


/*******************************************************************************
* Function Name: Cy_CapSense_CheckConfigIntegrity
****************************************************************************//**
*
* Performs verification of CAPSENSE&trade; data structure initialization.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return status
* Returns status of operation:
* - Zero        - Indicates successful initialization.
* - Non-zero    - One or more errors occurred in the initialization process.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_CheckConfigIntegrity(const cy_stc_capsense_context_t * context)
{
    cy_capsense_status_t capStatus = CY_CAPSENSE_STATUS_SUCCESS;

    const cy_stc_capsense_common_config_t * ptrCommonCfg = context->ptrCommonConfig;
    const cy_stc_capsense_common_context_t * ptrCommonCxt = context->ptrCommonContext;
    const cy_stc_capsense_internal_context_t * ptrInternalCxt = context->ptrInternalContext;
    const cy_stc_capsense_widget_config_t * ptrWdCfg = context->ptrWdConfig;
    const cy_stc_capsense_widget_context_t * ptrWdCxt = context->ptrWdContext;
    const cy_stc_capsense_pin_config_t * ptrPinCfg = context->ptrPinConfig;
    const cy_stc_active_scan_sns_t * ptrActScanSns = context->ptrActiveScanSns;

    if (ptrCommonCfg == NULL)       {capStatus = CY_CAPSENSE_STATUS_BAD_DATA;}
    if (ptrCommonCxt == NULL)       {capStatus = CY_CAPSENSE_STATUS_BAD_DATA;}
    if (ptrInternalCxt == NULL)     {capStatus = CY_CAPSENSE_STATUS_BAD_DATA;}
    if (ptrWdCfg == NULL)           {capStatus = CY_CAPSENSE_STATUS_BAD_DATA;}
    if (ptrWdCxt == NULL)           {capStatus = CY_CAPSENSE_STATUS_BAD_DATA;}
    if (ptrPinCfg == NULL)          {capStatus = CY_CAPSENSE_STATUS_BAD_DATA;}
    if (ptrActScanSns == NULL)      {capStatus = CY_CAPSENSE_STATUS_BAD_DATA;}

    return (capStatus);
}


/*******************************************************************************
* Function Name: Cy_CapSense_GetCRC
****************************************************************************//**
*
* Calculates CRC for the specified buffer and length.
*
* This API is used for the CRC protection of a packet received from
* the CAPSENSE&trade; Tuner tool and for BIST operations.
* CRC polynomial is 0xAC9A. It has a Hamming distance 5 for data words
* up to 241 bits.
*
* Reference:  "P. Koopman, T. Chakravarthy,
* "Cyclic Redundancy Code (CRC) Polynomial Selection for Embedded Networks",
* The International Conference on Dependable Systems and Networks, DSN-2004"
*
* \param ptrData
* The pointer to the data.
*
* \param len
* The length of the data in bytes.
*
* \return
* Returns a calculated CRC-16 value.
*
*******************************************************************************/
uint16_t Cy_CapSense_GetCRC(const uint8_t *ptrData, uint32_t len)
{
    uint32_t idx;
    uint32_t actualCrc = 0u;
    uint32_t length = len;
    const uint8_t * ptrDataLocal = ptrData;
    const uint16_t crcTable[] =
    {
        0x0000u, 0xAC9Au, 0xF5AEu, 0x5934u, 0x47C6u, 0xEB5Cu, 0xB268u, 0x1EF2u,
        0x8F8Cu, 0x2316u, 0x7A22u, 0xD6B8u, 0xC84Au, 0x64D0u, 0x3DE4u, 0x917Eu
    };

    for (;length-- > 0u;)
    {
        /* Process HI Nibble */
        idx = ((actualCrc >> 12u) ^ (((uint32_t)*ptrDataLocal) >> 4u)) & 0xFLu;
        actualCrc = crcTable[idx] ^ (actualCrc << 4u);

        /* Process LO Nibble */
        idx = ((actualCrc >> 12u) ^ (uint32_t)*ptrDataLocal) & 0xFLu;
        actualCrc = crcTable[idx] ^ (actualCrc << 4u);

        ptrDataLocal++;
    }

    return (uint16_t)actualCrc;
}


/*******************************************************************************
* Function Name: Cy_CapSense_GetCrcWidget
****************************************************************************//**
*
* Calculates CRC for the specified widget. This function implements the
* following functionality:
* - Fills the \ref cy_stc_capsense_widget_crc_data_t with 0.
* - Initializes fields of the \ref cy_stc_capsense_widget_crc_data_t with the
*   data from corresponding fields of the \ref cy_stc_capsense_widget_context_t.
* - Executes the Cy_CapSense_GetCRC() routine for full
*   \ref cy_stc_capsense_widget_crc_data_t, structure, including padding.
* If the CSD tuning mode is set to smart sensing algorithm (Full Auto-Tune)
* then the fields of the \ref cy_stc_capsense_widget_context_t that changing
* it's value in the run-time will be excluded from CRC calculation for the
* CSD widgets.
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
* Returns a calculated CRC-16 value.
*
*******************************************************************************/
uint16_t Cy_CapSense_GetCrcWidget(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context)
{
    uint16_t crcValue;
    const cy_stc_capsense_widget_context_t * ptrWdCxt;
    const cy_stc_capsense_widget_config_t * ptrWdCfg;
    cy_stc_capsense_widget_crc_data_t crcDataVal;

    /* Get a pointer to the specified widget config structure */
    ptrWdCfg = &context->ptrWdConfig[widgetId];

    /* Get a pointer to the specified widget context structure */
    ptrWdCxt = &context->ptrWdContext[widgetId];

    (void)memset((void*)&crcDataVal, 0, sizeof(crcDataVal));

    crcDataVal.fingerCapVal      = ptrWdCxt->fingerCap;
    crcDataVal.sigPFCVal         = ptrWdCxt->sigPFC;
    crcDataVal.lowBslnRstVal     = ptrWdCxt->lowBslnRst;
    crcDataVal.snsClkVal         = ptrWdCxt->snsClk;
    crcDataVal.rowSnsClkVal      = ptrWdCxt->rowSnsClk;
    crcDataVal.onDebounceVal     = ptrWdCxt->onDebounce;
    crcDataVal.snsClkSourceVal   = ptrWdCxt->snsClkSource;

    if((CY_CAPSENSE_CSX_GROUP == ptrWdCfg->senseMethod) ||
       (CY_CAPSENSE_CSD_SS_DIS == context->ptrCommonConfig->csdAutotuneEn))
    {
        crcDataVal.fingerThVal       = ptrWdCxt->fingerTh;
        crcDataVal.proxThVal         = ptrWdCxt->proxTh;
        crcDataVal.noiseThVal        = ptrWdCxt->noiseTh;
        crcDataVal.nNoiseThVal       = ptrWdCxt->nNoiseTh;
        crcDataVal.hysteresisVal     = ptrWdCxt->hysteresis;
    }

    #if (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN)
        crcDataVal.resolutionVal     = ptrWdCxt->resolution;
        crcDataVal.idacModVal[0u]    = ptrWdCxt->idacMod[0u];
        crcDataVal.idacModVal[1u]    = ptrWdCxt->idacMod[1u];
        crcDataVal.idacModVal[2u]    = ptrWdCxt->idacMod[2u];
        crcDataVal.idacGainIndexVal  = ptrWdCxt->idacGainIndex;
        crcDataVal.rowIdacModVal[0u] = ptrWdCxt->rowIdacMod[0u];
        crcDataVal.rowIdacModVal[1u] = ptrWdCxt->rowIdacMod[1u];
        crcDataVal.rowIdacModVal[2u] = ptrWdCxt->rowIdacMod[2u];
    #endif /* (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN) */

    #if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
        crcDataVal.resolutionVal   = ptrWdCxt->numSubConversions;
        crcDataVal.cdacRef         = ptrWdCxt->cdacRef;
        crcDataVal.rowCdacRef      = ptrWdCxt->rowCdacRef;
        crcDataVal.cdacCompDivider = ptrWdCxt->cdacCompDivider;
        crcDataVal.cicRate         = ptrWdCxt->cicRate;
        crcDataVal.lfsrBits        = ptrWdCxt->lfsrBits;
    #endif /* (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN) */

    crcValue = Cy_CapSense_GetCRC((uint8_t *)(&crcDataVal), sizeof(crcDataVal));

    return (crcValue);
}


/*******************************************************************************
* Function Name: Cy_CapSense_GetParam
****************************************************************************//**
*
* Gets a value of the specified parameter from the cy_capsense_tuner structure.
*
* This function gets the value of the specified parameter by the paramId
* argument. The paramId for each register of cy_capsense_tuner is available
* in the cycfg_capsense.h file as CY_CAPSENSE_<ParameterName>_PARAM_ID.
* The paramId is a special enumerated value generated by the CAPSENSE&trade;
* Configurator. The format of paramId is as follows:
* 1. [ byte 3 byte 2 byte 1 byte 0 ]
* 2. [ RRRRRUTT IIIIIIII MMMMMMMM LLLLLLLL ]
* 3. U - indicates if the parameter affects the RAM Widget Object CRC.
* 4. T - encodes the parameter type:
*    * 01b: uint8_t
*    * 10b: uint16_t
*    * 11b: uint32_t
* 5. I - specifies that the widgetId parameter belongs to.
* 6. M,L - the parameter offset MSB and LSB accordingly in cy_capsense_tuner.
* 7. R - reserved
*
* \param paramId
* Specifies the ID of parameter to get its value.
* A macro for the parameter ID can be found in the cycfg_capsense.h file
* defined as CY_CAPSENSE_<ParameterName>_PARAM_ID.
*
* \param value
* The pointer to a variable to be updated with the obtained value.
*
* \param ptrTuner
* The pointer to the cy_capsense_tuner variable of cy_stc_capsense_tuner_t.
* The cy_capsense_tuner is declared in CAPSENSE&trade; Configurator generated files:
* * cycfg_capsense.c/h
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the operation. If CY_CAPSENSE_STATUS_SUCCESS is not received,
* either paramId is invalid or ptrTuner is null.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_GetParam(
                uint32_t paramId,
                uint32_t * value,
                const void * ptrTuner,
                const cy_stc_capsense_context_t * context)
{
    cy_capsense_status_t capStatus = CY_CAPSENSE_STATUS_BAD_PARAM;
    uint32_t paramType;
    uint32_t paramOffset;

    const uint8_t * bytePtr;
    const uint16_t * halfWordPtr;
    const uint32_t * wordPtr;

    (void)context;
    if ((value != NULL) && (ptrTuner != NULL))
    {
        /* Check parameter type, offset alignment and read data */
        paramType = (paramId & CY_CAPSENSE_PARAM_TYPE_MASK) >> CY_CAPSENSE_PARAM_TYPE_OFFSET;
        paramOffset = (uint16_t)(paramId);
        switch (paramType)
        {
            case CY_CAPSENSE_DS_PARAM_TYPE_UINT32:
                if (0u == (paramOffset & CY_CAPSENSE_UINT32_ALIGN_MASK))
                {
                    paramOffset >>= 2u;
                    wordPtr = (const uint32_t *)ptrTuner;
                    *value = (uint32_t)wordPtr[paramOffset];
                    capStatus = CY_CAPSENSE_STATUS_SUCCESS;
                }
                break;
            case CY_CAPSENSE_DS_PARAM_TYPE_UINT16:
                if (0u == (paramOffset & CY_CAPSENSE_UINT16_ALIGN_MASK))
                {
                    paramOffset >>= 1u;
                    halfWordPtr = (const uint16_t *)ptrTuner;
                    *value = (uint32_t)halfWordPtr[paramOffset];
                    capStatus = CY_CAPSENSE_STATUS_SUCCESS;
                }
                break;
            case CY_CAPSENSE_DS_PARAM_TYPE_UINT8:
                bytePtr = (const uint8_t *)ptrTuner;
                *value = (uint32_t)bytePtr[paramOffset];
                capStatus = CY_CAPSENSE_STATUS_SUCCESS;
               break;
            default:
                /* No action on other parameter types */
                break;
        }
    }
    return capStatus;
}


/*******************************************************************************
* Function Name: Cy_CapSense_SetParam
****************************************************************************//**
*
* Sets a new value for the specified parameter in cy_capsense_tuner structure.
*
* This function sets the value of the specified parameter by the paramId
* argument. The paramId for each register of cy_capsense_tuner is available
* in the cycfg_capsense.h file as CY_CAPSENSE_<ParameterName>_PARAM_ID.
* The paramId is a special enumerated value generated by the CAPSENSE&trade;
* Configurator. The format of paramId is as follows:
* 1. [ byte 3 byte 2 byte 1 byte 0 ]
* 2. [ RRRRRUTT IIIIIIII MMMMMMMM LLLLLLLL ]
* 3. U - indicates if the parameter affects the RAM Widget Object CRC.
* 4. T - encodes the parameter type:
*    * 01b: uint8_t
*    * 10b: uint16_t
*    * 11b: uint32_t
* 5. I - specifies that the widgetId parameter belongs to
* 6. M,L - the parameter offset MSB and LSB accordingly in cy_capsense_tuner.
* 7. R - reserved
*
* This function writes specified value into the desired register without
* other registers update. It is application layer responsibility to keep all
* the data structure registers aligned. Repeated call of
* Cy_CapSense_Enable() function helps aligning dependent register values.
*
* This function updates also the widget CRC field if Built-in Self-test
* is enabled and paramId requires that.
*
* \param paramId
* Specifies the ID of parameter to set its value.
* A macro for the parameter ID can be found in the cycfg_capsense.h file
* defined as CY_CAPSENSE_<ParameterName>_PARAM_ID.
*
* \param value
* Specifies the new parameter's value.
*
* \param ptrTuner
* The pointer to the cy_capsense_tuner variable of cy_stc_capsense_tuner_t.
* The cy_capsense_tuner is declared in CAPSENSE&trade; Configurator generated files:
* * cycfg_capsense.c/h
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the operation. If CY_CAPSENSE_STATUS_SUCCESS is not received,
* the parameter was not updated with the new value, either paramId is invalid
* or ptrTuner is null.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_SetParam(
                uint32_t paramId,
                uint32_t value,
                void * ptrTuner,
                cy_stc_capsense_context_t * context)
{
    cy_capsense_status_t capStatus = CY_CAPSENSE_STATUS_SUCCESS;
    uint32_t paramOffset;
    uint32_t paramType;
    #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) &&\
         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN))
        uint32_t paramCrc;
        uint32_t paramWidget;
    #endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) &&
               (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN)) */

    uint8_t * bytePtr;
    uint16_t * halfWordPtr;
    uint32_t * wordPtr;

    if ((context == NULL) || (ptrTuner == NULL))
    {
        capStatus = CY_CAPSENSE_STATUS_BAD_PARAM;
    }

    /* Parse paramId */
    if (CY_CAPSENSE_STATUS_SUCCESS == capStatus)
    {
        paramOffset = (uint16_t)(paramId);
        paramType = (paramId & CY_CAPSENSE_PARAM_TYPE_MASK) >> CY_CAPSENSE_PARAM_TYPE_OFFSET;

        #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) &&\
             (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN))
            paramCrc = (paramId & CY_CAPSENSE_PARAM_CRC_MASK) >> CY_CAPSENSE_PARAM_CRC_OFFSET;
            paramWidget = (paramId & CY_CAPSENSE_PARAM_WIDGET_MASK) >> CY_CAPSENSE_PARAM_WIDGET_OFFSET;
            if ((paramWidget > context->ptrCommonConfig->numWd) &&
                (0u != paramCrc))
            {
                capStatus = CY_CAPSENSE_STATUS_BAD_PARAM;
            }
        #endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) &&
                   (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN)) */
    }

    /* Check parameter type, offset alignment, write the specified parameter */
    if (CY_CAPSENSE_STATUS_SUCCESS == capStatus)
    {
        switch (paramType)
        {
            case CY_CAPSENSE_DS_PARAM_TYPE_UINT32:
                if (0u == (paramOffset & CY_CAPSENSE_UINT32_ALIGN_MASK))
                {
                    paramOffset >>= 2u;
                    wordPtr = (uint32_t *)ptrTuner;
                    wordPtr[paramOffset] = value;
                }
                break;
            case CY_CAPSENSE_DS_PARAM_TYPE_UINT16:
                if (0u == (paramOffset & CY_CAPSENSE_UINT16_ALIGN_MASK))
                {
                    paramOffset >>= 1u;
                    halfWordPtr = (uint16_t *)ptrTuner;
                    halfWordPtr[paramOffset] = (uint16_t)value;
                }
                break;
            case CY_CAPSENSE_DS_PARAM_TYPE_UINT8:
               bytePtr = (uint8_t *)ptrTuner;
               bytePtr[paramOffset] = (uint8_t)value;
               break;
            default:
                capStatus = CY_CAPSENSE_STATUS_BAD_PARAM;
                break;
        }
    }

    /* Update widget CRC if needed */
    #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) &&\
         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN))
        if ((CY_CAPSENSE_STATUS_SUCCESS == capStatus) &&
            (0u != paramCrc))
        {
            Cy_CapSense_UpdateCrcWidget(paramWidget, context);
        }
    #endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) &&
               (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN)) */

    return capStatus;
}


#endif /* (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3)) */


/* [] END OF FILE */
