/***************************************************************************//**
* \file cy_capsense_filter.c
* \version 3.0
*
* \brief
* This file contains the source code of all filters implementation.
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
#include "cycfg_capsense_defines.h"
#include "cy_capsense_filter.h"
#include "cy_capsense_common.h"
#include "cy_capsense_lib.h"

#if (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3))


/*******************************************************************************
* Local definition
*******************************************************************************/
#define CY_CAPSENSE_IIR_BL_SHIFT                                (8u)

#define CY_CAPSENSE_IIR_SHIFT_STANDARD                          (0u)
#define CY_CAPSENSE_IIR_SHIFT_PERFORMANCE                       (8u)

#define CY_CAPSENSE_RC_MEDIAN_SIZE                              (2u)
#define CY_CAPSENSE_RC_IIR_SIZE                                 (1u)
#define CY_CAPSENSE_RC_AVG_SIZE                                 (3u)

/* IIR filter constant */
#define CY_CAPSENSE_IIR_COEFFICIENT_K                           (256u)

/******************************************************************************/
/** \cond SECTION_CAPSENSE_INTERNAL */
/** \addtogroup group_capsense_internal *//** \{ */
/******************************************************************************/

static cy_capsense_status_t Cy_CapSense_CheckBaselineInv(
                cy_stc_capsense_widget_context_t * ptrWdContext,
                const cy_stc_capsense_sensor_context_t * ptrSnsContext,
                const uint16_t * ptrSnsBslnInv,
                const cy_stc_capsense_context_t * context);

/** \} \endcond */


/*******************************************************************************
* Function Name: Cy_CapSense_UpdateAllBaselines
****************************************************************************//**
*
* Updates the baseline for all the sensors in all the widgets.
*
* Baselines must be updated after sensor scan to ignore low frequency
* changes in the sensor data caused by environment changes such as
* temperature from sensor status decision.
*
* This function ignores the widget enable bit in the widget status register.
* Calling this function multiple times without a new sensor scan leads to
* unexpected behavior and should be avoided.
*
* This function is called by Cy_CapSense_ProcessAllWidgets() and
* Cy_CapSense_ProcessWidget(), hence the application program need not use this
* function if any of the above functions is already used. This function can be
* used for custom application implementation.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the update baseline operation of all the widgets:
* - CY_CAPSENSE_STATUS_SUCCESS  - The operation is successfully completed.
* - CY_CAPSENSE_STATUS_BAD_DATA - The baseline processing failed.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_UpdateAllBaselines(
                const cy_stc_capsense_context_t * context)
{
    uint32_t wdIndex;
    cy_capsense_status_t bslnStatus = CY_CAPSENSE_STATUS_SUCCESS;

    for(wdIndex = context->ptrCommonConfig->numWd; wdIndex-- > 0u;)
    {
        bslnStatus |= Cy_CapSense_UpdateWidgetBaseline(wdIndex, context);
    }

    return(bslnStatus);
}


/*******************************************************************************
* Function Name: Cy_CapSense_UpdateWidgetBaseline
****************************************************************************//**
*
* Updates the baselines for all the sensors in a widget specified by
* the input parameter.
*
* This function performs exactly the same tasks as
* Cy_CapSense_UpdateAllBaselines() but only for a specified widget.
*
* Calling this function multiple times without a new sensor scan leads to
* unexpected behavior and should be avoided. The application program need
* not use this function if the Cy_CapSense_UpdateAllBaselines(),
* Cy_CapSense_ProcessAllWidgets() or Cy_CapSense_ProcessWidget() functions
* are already used.
*
* \param widgetId
* Specifies the ID number of the widget. A macro for the widget ID can be found
* in the cycfg_capsense.h file defined as CY_CAPSENSE_<WIDGET_NAME>_WDGT_ID.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the specified widget update baseline operation:
* - CY_CAPSENSE_STATUS_SUCCESS - The operation is successfully completed.
* - CY_CAPSENSE_STATUS_BAD_DATA - The baseline processing failed.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_UpdateWidgetBaseline(
                uint32_t widgetId,
                const cy_stc_capsense_context_t * context)
{
    uint32_t snsIndex;
    cy_capsense_status_t bslnStatus = CY_CAPSENSE_STATUS_SUCCESS;

    for(snsIndex = context->ptrWdConfig[widgetId].numSns; snsIndex-- > 0u;)
    {
        bslnStatus |= Cy_CapSense_UpdateSensorBaseline(widgetId, snsIndex, context);
    }

    return(bslnStatus);
}


/*******************************************************************************
* Function Name: Cy_CapSense_UpdateSensorBaseline
****************************************************************************//**
*
* Updates the baseline for a sensor in a widget specified by the
* input parameters.
*
* This function performs exactly the same tasks as
* Cy_CapSense_UpdateAllBaselines() and Cy_CapSense_UpdateWidgetBaseline()
* but only for a specified sensor.
*
* Calling this function multiple times without a new sensor scan leads to
* unexpected behavior and should be avoided. The application need not use
* this function if the Cy_CapSense_UpdateWidgetBaseline (),
* Cy_CapSense_UpdateAllBaselines (), Cy_CapSense_ProcessAllWidgets(),
* or Cy_CapSense_ProcessWidget() functions are already used.
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
* Returns the status of the specified sensor update baseline operation:
* - CY_CAPSENSE_STATUS_SUCCESS - The operation is successfully completed.
* - CY_CAPSENSE_STATUS_BAD_DATA - The baseline processing failed.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_UpdateSensorBaseline(
                uint32_t widgetId,
                uint32_t sensorId,
                const cy_stc_capsense_context_t * context)
{
    uint32_t result;
    const cy_stc_capsense_widget_config_t * ptrWdCfg = &context->ptrWdConfig[widgetId];
    cy_stc_capsense_sensor_context_t * ptrSnsCxt = &ptrWdCfg->ptrSnsContext[sensorId];

    result = Cy_CapSense_FtUpdateBaseline(ptrWdCfg->ptrWdContext, ptrSnsCxt, &ptrWdCfg->ptrBslnInv[sensorId], context);

    return (result);
}


/*******************************************************************************
* Function Name: Cy_CapSense_CheckBaselineInv
****************************************************************************//**
*
* Check a matching of present baseline and its inverse duplication.
*
* \param ptrWdContext
* The pointer to the widget context structure where all the widget parameters
* are stored.
*
* \param ptrSnsContext
* The pointer to the sensor context structure where the sensor data
* is stored.
*
* \param ptrSnsBslnInv
* The pointer to the sensor baseline inversion used for BIST if enabled.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status indicating check result:
* - CY_CAPSENSE_STATUS_SUCCESS -  if the BIST baseline integrity test is enabled and
*                                 baseline and its inverse duplication match or BIST
*                                 baseline integrity test is disabled.
* - CY_CAPSENSE_STATUS_BAD_DATA - if the BIST baseline integrity test is enabled and
*                                 the sensor's baseline and its inversion doesn't
*                                 match. In this case the function as well clears
*                                 the bit[2] (Widget Working) of the .status field
*                                 in the widget context structure preventing corrupted
*                                 data usage and set the CY_CAPSENSE_BIST_BSLN_INTEGRITY_MASK
*                                 bit of the .testResultMask field
*                                 in the /ref cy_stc_capsense_bist_context_t structure.
*
*******************************************************************************/
static cy_capsense_status_t Cy_CapSense_CheckBaselineInv(
                cy_stc_capsense_widget_context_t * ptrWdContext,
                const cy_stc_capsense_sensor_context_t * ptrSnsContext,
                const uint16_t * ptrSnsBslnInv,
                const cy_stc_capsense_context_t * context)
{
    cy_capsense_status_t result = CY_CAPSENSE_STATUS_SUCCESS;

    #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) &&\
         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_BSLN_INTEGRITY_EN))
        uint16_t bslnInv = (uint16_t)(~ptrSnsContext->bsln);

        if (*ptrSnsBslnInv != bslnInv)
        {
            result = CY_CAPSENSE_STATUS_BAD_DATA;
            ptrWdContext->status &= (uint8_t)~CY_CAPSENSE_WD_WORKING_MASK;
            context->ptrBistContext->testResultMask |= CY_CAPSENSE_BIST_BSLN_INTEGRITY_MASK;
        }
    #else
        (void) ptrWdContext;
        (void) ptrSnsContext;
        (void) ptrSnsBslnInv;
        (void) context;
    #endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) &&\
               (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_BSLN_INTEGRITY_EN)) */

    return result;
}

/*******************************************************************************
* Function Name: Cy_CapSense_FtUpdateBaseline
****************************************************************************//**
*
* Updates the baseline for a sensor specified by an input parameter.
*
* Check a matching of present baseline and its inverse duplication. If they
* match, then the function updates the baseline for a sensor specified by an input parameter.
* If they don't match, the function returns CY_CAPSENSE_TST_BSLN_DUPLICATION
* result and doesn't update the baseline.
*
* \param ptrWdContext
* The pointer to the widget context structure where all the widget parameters
* are stored.
*
* \param ptrSnsContext
* The pointer to the sensor context structure where the sensor data
* is stored.
*
* \param ptrSnsBslnInv
* The pointer to the sensor baseline inversion used for BIST if enabled.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status indicating whether the baseline has been updated:
* - CY_CAPSENSE_STATUS_SUCCESS - if baseline updating was successful.
* - CY_CAPSENSE_STATUS_BAD_DATA - if the BIST baseline integrity test is enabled and
*                                 the sensor's baseline and its inversion doesn't
*                                 match. In this case the function as well clears
*                                 the bit[2] (Widget Working) of the .status field
*                                 in the widget context structure preventing corrupted
*                                 data usage and set the CY_CAPSENSE_BIST_BSLN_INTEGRITY_MASK
*                                 bit of the .testResultMask field
*                                 in the /ref cy_stc_capsense_bist_context_t structure.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_FtUpdateBaseline(
                cy_stc_capsense_widget_context_t * ptrWdContext,
                cy_stc_capsense_sensor_context_t * ptrSnsContext,
                uint16_t * ptrSnsBslnInv,
                const cy_stc_capsense_context_t * context)
{
    cy_capsense_status_t result;
    uint32_t bslnHistory;

    result = Cy_CapSense_CheckBaselineInv(ptrWdContext, ptrSnsContext, ptrSnsBslnInv, context);

    if (CY_CAPSENSE_STATUS_SUCCESS == result)
    {
        /* Reset negative baseline counter */
        if(ptrSnsContext->raw >= ptrSnsContext->bsln)
        {
            ptrSnsContext->negBslnRstCnt = 0u;
        }

        /* Reset baseline */
        if ((uint32_t)ptrSnsContext->bsln > ((uint32_t)ptrWdContext->nNoiseTh + ptrSnsContext->raw))
        {
            if (ptrSnsContext->negBslnRstCnt >= ptrWdContext->lowBslnRst)
            {
                Cy_CapSense_FtInitializeBaseline(ptrSnsContext);
            }
            else
            {
                ptrSnsContext->negBslnRstCnt++;
            }
        }
        else
        {
            /*
            * Update baseline only if:
            * - signal is in range between noiseThreshold and negativenoiseThreshold
            * or
            * - sensor Auto-reset is enabled
            */
            if ((0u != context->ptrCommonConfig->swSensorAutoResetEn) ||
                ((uint32_t)ptrSnsContext->raw <= ((uint32_t)ptrWdContext->noiseTh + ptrSnsContext->bsln)))
            {
                /* Get real baseline */
                bslnHistory = ((uint32_t)ptrSnsContext->bsln << CY_CAPSENSE_IIR_BL_SHIFT) | ptrSnsContext->bslnExt;
                /* Calculate baseline value */
                bslnHistory = Cy_CapSense_FtIIR1stOrder((uint32_t)ptrSnsContext->raw << CY_CAPSENSE_IIR_BL_SHIFT, bslnHistory, (uint32_t)ptrWdContext->bslnCoeff);
                /* Split baseline */
                ptrSnsContext->bsln = (uint16_t)(bslnHistory >> CY_CAPSENSE_IIR_BL_SHIFT);
                ptrSnsContext->bslnExt = (uint8_t)(bslnHistory);
            }
        }
        /* If BIST enabled, update the baseline inverse duplication */
        #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) &&\
             (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_BSLN_INTEGRITY_EN))
            *ptrSnsBslnInv = ~ptrSnsContext->bsln;
        #endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) &&\
                   (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_BSLN_INTEGRITY_EN)) */
    }
    return result;
}


/*******************************************************************************
* Function Name: Cy_CapSense_InitializeAllBaselines
****************************************************************************//**
*
* Initializes the baselines of all the sensors of all the widgets.
*
* This function initializes baselines for all sensors and widgets in the project.
* It can also be used to re-initialize baselines at any time, however, note
* that all sensor data history information and sensor status shall be reset
* along with re-initialization of baseline.
*
* Following functions to initialize sensor and widgets and filter history
* should be called after initializing baseline for proper operation of
* the CAPSENSE&trade; middleware:
* * Cy_CapSense_InitializeAllStatuses()
* * Cy_CapSense_InitializeAllFilters()
*
* These functions are called by the CapSense_Enable() function, hence it is
* not required to use this function if above function is used.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_InitializeAllBaselines(cy_stc_capsense_context_t * context)
{
    uint32_t wdIndex;

    for(wdIndex = context->ptrCommonConfig->numWd; wdIndex-- > 0u;)
    {
        Cy_CapSense_InitializeWidgetBaseline(wdIndex, context);
    }
}


/*******************************************************************************
* Function Name: Cy_CapSense_InitializeWidgetBaseline
****************************************************************************//**
*
* Initializes the baselines of all the sensors in a specific widget.
*
* This function initializes baselines for all sensors in a specific widget
* in the project. It can also be used to re-initialize baselines at any time,
* however, note that all sensor data history information and sensor status
* should be reset along with re-initialization of baseline.
*
* The following functions to initialize sensor and widgets and filter history
* should be called after initializing baselines for proper operation of
* middleware.
* * Cy_CapSense_InitializeWidgetStatus()
* * Cy_CapSense_InitializeWidgetFilter()
*
* These functions are called by CapSense_Enable() function, hence it is not
* required to use this function is above function is used.
*
* \param widgetId
* Specifies the ID number of the widget. A macro for the widget ID can be found
* in the cycfg_capsense.h file defined as CY_CAPSENSE_<WIDGET_NAME>_WDGT_ID.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_InitializeWidgetBaseline(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context)
{
    uint32_t snsIndex;

    for(snsIndex = context->ptrWdConfig[widgetId].numSns; snsIndex-- > 0u;)
    {
        Cy_CapSense_InitializeSensorBaseline(widgetId, snsIndex, context);
    }
}


/*******************************************************************************
* Function Name: Cy_CapSense_InitializeSensorBaseline
****************************************************************************//**
*
* Initializes the baseline of a sensor in a widget specified
* by the input parameters.
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
*******************************************************************************/
void Cy_CapSense_InitializeSensorBaseline(
                uint32_t widgetId,
                uint32_t sensorId,
                cy_stc_capsense_context_t * context)
{
    uint32_t cxtOffset;
    uint32_t freqChIndex;
    for(freqChIndex = 0u; freqChIndex < CY_CAPSENSE_CONFIGURED_FREQ_NUM; freqChIndex++)
    {
        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_MULTI_FREQUENCY_SCAN_EN)
            cxtOffset = sensorId + (freqChIndex * context->ptrCommonConfig->numSns);
        #else
            cxtOffset = sensorId;
        #endif
        Cy_CapSense_FtInitializeBaseline(&context->ptrWdConfig[widgetId].ptrSnsContext[cxtOffset]);
        /* If BIST enabled, create a baseline inverse duplication */
        #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) &&\
                (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_BSLN_INTEGRITY_EN))
            context->ptrWdConfig[widgetId].ptrBslnInv[cxtOffset] =
                                            ~context->ptrWdConfig[widgetId].ptrSnsContext[cxtOffset].bsln;
        #endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) &&\
                    (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_BSLN_INTEGRITY_EN)) */
    }
}


/*******************************************************************************
* Function Name: Cy_CapSense_FtInitializeBaseline
****************************************************************************//**
*
* Initializes the baseline history for a sensor indicated by an input
* parameter.
*
* \param ptrSnsContext
* The pointer to the sensor context structure.
*
*******************************************************************************/
void Cy_CapSense_FtInitializeBaseline(cy_stc_capsense_sensor_context_t * ptrSnsContext)
{
    ptrSnsContext->bslnExt = 0u;
    ptrSnsContext->bsln = ptrSnsContext->raw;
    ptrSnsContext->negBslnRstCnt = 0u;
}

#if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_RAWCOUNT_FILTER_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_InitializeAllFilters
****************************************************************************//**
*
* Initializes (or re-initializes) all the firmware filter history, except
* the baseline.
*
* Calling this function is accompanied by
* * Cy_CapSense_InitializeAllStatuses()
* * Cy_CapSense_InitializeAllBaselines()
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_InitializeAllFilters(const cy_stc_capsense_context_t * context)
{
    uint32_t widgetId;

    for(widgetId = context->ptrCommonConfig->numWd; widgetId-- > 0u;)
    {
        Cy_CapSense_InitializeWidgetFilter(widgetId, context);
    }
}


/*******************************************************************************
* Function Name: Cy_CapSense_InitializeWidgetFilter
****************************************************************************//**
*
* Initializes (or re-initializes) the raw count filter history of all
* the sensors in a widget specified by the input parameter.
*
* Calling this function is accompanied by
* - Cy_CapSense_InitializeWidgetStatus().
* - Cy_CapSense_InitializeWidgetBaseline().
*
* \param widgetId
* Specifies the ID number of the widget. A macro for the widget ID can be found
* in the cycfg_capsense.h file defined as CY_CAPSENSE_<WIDGET_NAME>_WDGT_ID.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_InitializeWidgetFilter(
                uint32_t widgetId,
                const cy_stc_capsense_context_t * context)
{
    uint32_t snsIndex;
    uint32_t freqChIndex;
    uint32_t snsHistorySize;
    uint32_t historyOffset;

    const cy_stc_capsense_widget_config_t * ptrWdCfg = &context->ptrWdConfig[widgetId];

    uint32_t rawFilterCfg = ptrWdCfg->rawFilterConfig;
    uint16_t * ptrHistory;
    const cy_stc_capsense_sensor_context_t * ptrSnsCtx ;
    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_SMARTSENSE_FULL_EN)
        cy_stc_capsense_smartsense_csd_noise_envelope_t * ptrNEHistory;
    #endif
    #if (CY_CAPSENSE_REGULAR_RC_IIR_FILTER_EN || CY_CAPSENSE_PROX_RC_IIR_FILTER_EN)
        uint8_t * ptrHistoryLow = NULL;
    #endif

    snsHistorySize = (uint32_t)ptrWdCfg->rawFilterConfig & CY_CAPSENSE_RC_FILTER_SNS_HISTORY_SIZE_MASK;
    for(freqChIndex = 0u; freqChIndex < CY_CAPSENSE_CONFIGURED_FREQ_NUM; freqChIndex++)
    {
        for(snsIndex = 0u; snsIndex < ptrWdCfg->numSns; snsIndex++)
        {
            ptrSnsCtx = &ptrWdCfg->ptrSnsContext[snsIndex + (freqChIndex * context->ptrCommonConfig->numSns)];
            historyOffset = (freqChIndex * (CY_CAPSENSE_RAW_HISTORY_SIZE / CY_CAPSENSE_CONFIGURED_FREQ_NUM)) + (snsHistorySize * snsIndex);
            ptrHistory = &ptrWdCfg->ptrRawFilterHistory[historyOffset];

            #if (CY_CAPSENSE_REGULAR_RC_MEDIAN_FILTER_EN || CY_CAPSENSE_PROX_RC_MEDIAN_FILTER_EN)
                if(0u != (CY_CAPSENSE_RC_FILTER_MEDIAN_EN_MASK & rawFilterCfg))
                {
                    Cy_CapSense_InitializeMedianInternal(ptrWdCfg, ptrSnsCtx, ptrHistory);
                    ptrHistory += CY_CAPSENSE_RC_MEDIAN_SIZE;
                }
            #endif

            #if (CY_CAPSENSE_REGULAR_RC_IIR_FILTER_EN || CY_CAPSENSE_PROX_RC_IIR_FILTER_EN)
            if(0u != (CY_CAPSENSE_RC_FILTER_IIR_EN_MASK & rawFilterCfg))
            {
                if(CY_CAPSENSE_IIR_FILTER_PERFORMANCE == (ptrWdCfg->rawFilterConfig & CY_CAPSENSE_RC_FILTER_IIR_MODE_MASK))
                {
                    ptrHistoryLow = &ptrWdCfg->ptrRawFilterHistoryLow[snsIndex +
                            (freqChIndex * (CY_CAPSENSE_IIR_HISTORY_LOW_SIZE / CY_CAPSENSE_CONFIGURED_FREQ_NUM))];
                }
                Cy_CapSense_InitializeIIRInternal(ptrWdCfg, ptrSnsCtx, ptrHistory, ptrHistoryLow);
                ptrHistory += CY_CAPSENSE_RC_IIR_SIZE;
            }
            #endif

            #if (CY_CAPSENSE_REGULAR_RC_AVERAGE_FILTER_EN || CY_CAPSENSE_PROX_RC_AVERAGE_FILTER_EN)
            if(0u != (CY_CAPSENSE_RC_FILTER_AVERAGE_EN_MASK & rawFilterCfg))
            {
                Cy_CapSense_InitializeAverageInternal(ptrWdCfg, ptrSnsCtx, ptrHistory);
            }
            #endif
        }
    }

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_SMARTSENSE_FULL_EN)
    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
        /* Noise envelope is available for CSD widgets only */
        if (CY_CAPSENSE_CSD_GROUP == ptrWdCfg->senseMethod)
        {
            ptrSnsCtx = ptrWdCfg->ptrSnsContext;
            ptrNEHistory = ptrWdCfg->ptrNoiseEnvelope;
            for(snsIndex = 0u; snsIndex < ptrWdCfg->numSns; snsIndex++)
            {
                Cy_CapSense_InitializeNoiseEnvelope_Lib(ptrSnsCtx->raw,
                        ptrWdCfg->ptrWdContext->sigPFC, ptrNEHistory);
                ptrSnsCtx++;
                ptrNEHistory++;
            }
        }
    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */
    #endif
}
#endif /*(CY_CAPSENSE_DISABLE != CY_CAPSENSE_RAWCOUNT_FILTER_EN)*/

#if (CY_CAPSENSE_REGULAR_RC_IIR_FILTER_EN || CY_CAPSENSE_PROX_RC_IIR_FILTER_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_InitializeIIRInternal
****************************************************************************//**
*
* Initializes the IIR filter history.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure.
*
* \param ptrSnsContext
* The pointer to the sensor context structure.
*
* \param ptrSnsRawHistory
* The pointer to the filter history of the sensor.
*
* \param ptrSnsRawHistoryLow
* The pointer to the extended filter history of the sensor.
*
*******************************************************************************/
void Cy_CapSense_InitializeIIRInternal(
                const cy_stc_capsense_widget_config_t * ptrWdConfig,
                const cy_stc_capsense_sensor_context_t * ptrSnsContext,
                uint16_t * ptrSnsRawHistory,
                uint8_t * ptrSnsRawHistoryLow)
{
    ptrSnsRawHistory[0u] = ptrSnsContext->raw;

    if ((NULL != ptrSnsRawHistoryLow) &&
       (CY_CAPSENSE_IIR_FILTER_PERFORMANCE == (ptrWdConfig->rawFilterConfig & CY_CAPSENSE_RC_FILTER_IIR_MODE_MASK)))
    {
        ptrSnsRawHistoryLow[0u] = 0u;
    }
}


/*******************************************************************************
* Function Name: Cy_CapSense_RunIIRInternal
****************************************************************************//**
*
* Runs the IIR filter.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure.
*
* \param ptrSnsContext
* The pointer to the sensor context structure.
*
* \param ptrSnsRawHistory
* The pointer to the filter history of the sensor.
*
* \param ptrSnsRawHistoryLow
* The pointer to the extended filter history of the sensor.
*
*******************************************************************************/
void Cy_CapSense_RunIIRInternal(
                const cy_stc_capsense_widget_config_t * ptrWdConfig,
                cy_stc_capsense_sensor_context_t * ptrSnsContext,
                uint16_t * ptrSnsRawHistory,
                uint8_t * ptrSnsRawHistoryLow)
{
    uint32_t tempHistory;
    uint32_t tempRaw;

    if(CY_CAPSENSE_IIR_FILTER_PERFORMANCE == (ptrWdConfig->rawFilterConfig & CY_CAPSENSE_RC_FILTER_IIR_MODE_MASK))
    {
        tempRaw = ((uint32_t)ptrSnsContext->raw) << CY_CAPSENSE_IIR_SHIFT_PERFORMANCE;
        tempHistory  = ((uint32_t)(*ptrSnsRawHistory)) << CY_CAPSENSE_IIR_SHIFT_PERFORMANCE;
        tempHistory |= (uint32_t)(*ptrSnsRawHistoryLow);
        tempRaw = Cy_CapSense_FtIIR1stOrder(tempRaw, tempHistory, ptrWdConfig->iirCoeff);
        *ptrSnsRawHistory = (uint16_t)(tempRaw >> CY_CAPSENSE_IIR_SHIFT_PERFORMANCE);
        *ptrSnsRawHistoryLow = (uint8_t)(tempRaw);
        ptrSnsContext->raw = (uint16_t)(tempRaw >> CY_CAPSENSE_IIR_SHIFT_PERFORMANCE);
    }
    else
    {
        tempRaw = Cy_CapSense_FtIIR1stOrder((uint32_t)ptrSnsContext->raw, (uint32_t)(*ptrSnsRawHistory), ptrWdConfig->iirCoeff);
        *ptrSnsRawHistory = (uint16_t)(tempRaw);
        ptrSnsContext->raw = *ptrSnsRawHistory;
    }
}
#endif /* (CY_CAPSENSE_REGULAR_RC_IIR_FILTER_EN || CY_CAPSENSE_PROX_RC_IIR_FILTER_EN) */

#if (CY_CAPSENSE_REGULAR_RC_MEDIAN_FILTER_EN || CY_CAPSENSE_PROX_RC_MEDIAN_FILTER_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_InitializeMedianInternal
****************************************************************************//**
*
* Initializes the median filter.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure.
*
* \param ptrSnsContext
* The pointer to the sensor context structure.
*
* \param ptrSnsRawHistory
* The pointer to the filter history of the sensor.
*
*******************************************************************************/
void Cy_CapSense_InitializeMedianInternal(
                const cy_stc_capsense_widget_config_t * ptrWdConfig,
                const cy_stc_capsense_sensor_context_t * ptrSnsContext,
                uint16_t * ptrSnsRawHistory)
{
    (void)ptrWdConfig;

    ptrSnsRawHistory[0u] = ptrSnsContext->raw;
    ptrSnsRawHistory[1u] = ptrSnsContext->raw;
}


/*******************************************************************************
* Function Name: Cy_CapSense_RunMedianInternal
****************************************************************************//**
*
* Runs the median filter.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure.
*
* \param ptrSnsContext
* The pointer to the sensor context structure.
*
* \param ptrSnsRawHistory
* The pointer to the filter history of the sensor.
*
*******************************************************************************/
void Cy_CapSense_RunMedianInternal(
                const cy_stc_capsense_widget_config_t * ptrWdConfig,
                cy_stc_capsense_sensor_context_t * ptrSnsContext,
                uint16_t * ptrSnsRawHistory)
{
    uint32_t temp = Cy_CapSense_FtMedian(
                    (uint32_t)ptrSnsContext->raw,
                    (uint32_t)ptrSnsRawHistory[0u],
                    (uint32_t)ptrSnsRawHistory[1u]);

    (void)ptrWdConfig;

    ptrSnsRawHistory[1u] = ptrSnsRawHistory[0u];
    ptrSnsRawHistory[0u] = ptrSnsContext->raw;
    ptrSnsContext->raw = (uint16_t)(temp);
}
#endif /* (CY_CAPSENSE_REGULAR_RC_MEDIAN_FILTER_EN || CY_CAPSENSE_PROX_RC_MEDIAN_FILTER_EN) */

#if (CY_CAPSENSE_REGULAR_RC_AVERAGE_FILTER_EN || CY_CAPSENSE_PROX_RC_AVERAGE_FILTER_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_InitializeAverageInternal
****************************************************************************//**
*
* Initializes the average filter.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure.
*
* \param ptrSnsContext
* The pointer to the sensor context structure.
*
* \param ptrSnsRawHistory
* The pointer to the filter history of the sensor.
*
*******************************************************************************/
void Cy_CapSense_InitializeAverageInternal(
                const cy_stc_capsense_widget_config_t * ptrWdConfig,
                const cy_stc_capsense_sensor_context_t * ptrSnsContext,
                uint16_t * ptrSnsRawHistory)
{
    (void)ptrWdConfig;
    ptrSnsRawHistory[0u] = ptrSnsContext->raw;
    ptrSnsRawHistory[1u] = ptrSnsContext->raw;
    ptrSnsRawHistory[2u] = ptrSnsContext->raw;
}


/*******************************************************************************
* Function Name: Cy_CapSense_RunAverageInternal
****************************************************************************//**
*
* Runs the average filter.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure.
*
* \param ptrSnsContext
* The pointer to the sensor context structure.
*
* \param ptrSnsRawHistory
* The pointer to the filter history of the sensor.
*
*******************************************************************************/
void Cy_CapSense_RunAverageInternal(
                const cy_stc_capsense_widget_config_t * ptrWdConfig,
                cy_stc_capsense_sensor_context_t * ptrSnsContext,
                uint16_t * ptrSnsRawHistory)
{
    uint32_t temp;

    if(CY_CAPSENSE_AVERAGE_FILTER_LEN_4 == (ptrWdConfig->rawFilterConfig & CY_CAPSENSE_RC_FILTER_AVERAGE_MODE_MASK))
    {
        temp = ((uint32_t)ptrSnsContext->raw + ptrSnsRawHistory[0u] + ptrSnsRawHistory[1u] + ptrSnsRawHistory[2u]) >> 2u;
        ptrSnsRawHistory[2u] = ptrSnsRawHistory[1u];
        ptrSnsRawHistory[1u] = ptrSnsRawHistory[0u];
    }
    else
    {
        temp = ((uint32_t)ptrSnsContext->raw + ptrSnsRawHistory[0u]) >> 1u;
    }
    ptrSnsRawHistory[0u] = ptrSnsContext->raw;
    ptrSnsContext->raw = (uint16_t)(temp);
}
#endif /* (CY_CAPSENSE_REGULAR_RC_AVERAGE_FILTER_EN || CY_CAPSENSE_PROX_RC_AVERAGE_FILTER_EN) */

#if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_RAWCOUNT_FILTER_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_FtRunEnabledFiltersInternal
****************************************************************************//**
*
* Runs all enabled filters.
*
* \param ptrWdConfig
* The pointer to the widget configuration structure.
*
* \param ptrSnsContext
* The pointer to the sensor context structure.
*
* \param ptrSnsRawHistory
* The pointer to the filter history of the sensor.
*
* \param ptrSnsRawHistoryLow
* The pointer to the extended filter history of the sensor.
*
*******************************************************************************/
void Cy_CapSense_FtRunEnabledFiltersInternal(
                const cy_stc_capsense_widget_config_t * ptrWdConfig,
                cy_stc_capsense_sensor_context_t * ptrSnsContext,
                uint16_t * ptrSnsRawHistory,
                uint8_t * ptrSnsRawHistoryLow)
{
    uint16_t rawFilterCfg;
    rawFilterCfg = ptrWdConfig->rawFilterConfig;
    uint16_t * ptrSnsRawHistoryLocal = ptrSnsRawHistory;

    #if (CY_CAPSENSE_REGULAR_RC_MEDIAN_FILTER_EN || CY_CAPSENSE_PROX_RC_MEDIAN_FILTER_EN)
        if(0u != (CY_CAPSENSE_RC_FILTER_MEDIAN_EN_MASK & rawFilterCfg))
        {
            Cy_CapSense_RunMedianInternal(ptrWdConfig, ptrSnsContext, ptrSnsRawHistoryLocal);
            ptrSnsRawHistoryLocal += CY_CAPSENSE_RC_MEDIAN_SIZE;
        }
    #endif

    #if (CY_CAPSENSE_REGULAR_RC_IIR_FILTER_EN || CY_CAPSENSE_PROX_RC_IIR_FILTER_EN)
        if(0u != (CY_CAPSENSE_RC_FILTER_IIR_EN_MASK & rawFilterCfg))
        {
            Cy_CapSense_RunIIRInternal(ptrWdConfig, ptrSnsContext, ptrSnsRawHistoryLocal, ptrSnsRawHistoryLow);
            ptrSnsRawHistoryLocal += CY_CAPSENSE_RC_IIR_SIZE;
        }
    #else
        (void)ptrSnsRawHistoryLow;
    #endif

    #if (CY_CAPSENSE_REGULAR_RC_AVERAGE_FILTER_EN || CY_CAPSENSE_PROX_RC_AVERAGE_FILTER_EN)
        if(0u != (CY_CAPSENSE_RC_FILTER_AVERAGE_EN_MASK & rawFilterCfg))
        {
            Cy_CapSense_RunAverageInternal(ptrWdConfig, ptrSnsContext, ptrSnsRawHistoryLocal);
        }
    #endif
}
#endif /* (CY_CAPSENSE_DISABLE != CY_CAPSENSE_RAWCOUNT_FILTER_EN) */

#if (CY_CAPSENSE_POS_MEDIAN_FILTER_EN || CY_CAPSENSE_REGULAR_RC_MEDIAN_FILTER_EN \
    || CY_CAPSENSE_PROX_RC_MEDIAN_FILTER_EN || CY_CAPSENSE_MULTI_FREQUENCY_SCAN_EN || CY_CAPSENSE_MULTI_FREQUENCY_WIDGET_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_FtMedian
****************************************************************************//**
*
* Returns the median value from the three passed arguments.
*
* \param x1
* The first value to be compared.
*
* \param x2
* The second value to be compared.
*
* \param x3
* The third value to be compared.
*
* \return
* Returns the median value of input arguments.
*
*******************************************************************************/
uint32_t Cy_CapSense_FtMedian(uint32_t x1, uint32_t x2, uint32_t x3)
{
    uint32_t tmp;
    uint32_t x1Local = x1;
    uint32_t x2Local = x2;

    if (x1Local > x2Local)
    {
        tmp = x2Local;
        x2Local = x1Local;
        x1Local = tmp;
    }

    if (x2Local > x3)
    {
        x2Local = x3;
    }

    return ((x1Local > x2Local) ? x1Local : x2Local);
}
#endif /*#if (CY_CAPSENSE_POS_MEDIAN_FILTER_EN || CY_CAPSENSE_REGULAR_RC_MEDIAN_FILTER_EN \
    || CY_CAPSENSE_PROX_RC_MEDIAN_FILTER_EN || CY_CAPSENSE_MULTI_FREQUENCY_SCAN_EN)*/

/*******************************************************************************
* Function Name: Cy_CapSense_FtIIR1stOrder
****************************************************************************//**
*
* Returns the filtered data by the IIR 1-st order algorithm
*
* \param input
* The data to be filtered.
*
* \param prevOutput
* The previous filtered data.
*
* \param n
* The IIR filter coefficient (n/256).
*
* \return
* Returns the filtered data.
*
*******************************************************************************/
uint32_t Cy_CapSense_FtIIR1stOrder(uint32_t input, uint32_t prevOutput, uint32_t n)
{
    uint32_t filteredOutput;

    filteredOutput = ((n * input) + ((CY_CAPSENSE_IIR_COEFFICIENT_K - n) * prevOutput)) >> 8u;

    return filteredOutput;
}

#if (CY_CAPSENSE_DISABLE != CY_CAPSENSE_POS_JITTER_FILTER_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_FtJitter
****************************************************************************//**
*
* Returns the filtered data by the jitter algorithm.
*
* \param input
* The data to be filtered.
*
* \param prevOutput
* The previous filtered data.
*
* \return
* Returns the filtered data.
*
*******************************************************************************/
uint32_t Cy_CapSense_FtJitter(uint32_t input, uint32_t prevOutput)
{
    uint32_t inputLocal = input;

    if (prevOutput > inputLocal)
    {
        inputLocal++;
    }
    else if (prevOutput < inputLocal)
    {
        inputLocal--;
    }
    else
    {
        /* No action, input equal to prevOutput */
    }
    return inputLocal;
}
#endif /*(CY_CAPSENSE_DISABLE != CY_CAPSENSE_POS_JITTER_FILTER_EN)*/

#endif /* (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3)) */


/* [] END OF FILE */
