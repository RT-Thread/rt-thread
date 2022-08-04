/***************************************************************************//**
* \file cy_capsense_sensing_v2.c
* \version 3.0
*
* \brief
* This file contains the source of functions common for different sensing
* methods.
*
********************************************************************************
* \copyright
* Copyright 2018-2021, Cypress Semiconductor Corporation (an Infineon company)
* or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include <stdlib.h>
#include <stddef.h>
#include "cy_gpio.h"
#include "cy_sysclk.h"

#include "cycfg_capsense_defines.h"
#include "cy_capsense_common.h"
#include "cy_capsense_structure.h"
#include "cy_capsense_sensing_v2.h"
#include "cy_capsense_sensing.h"
#include "cy_capsense_csx_v2.h"
#include "cy_capsense_csd_v2.h"
#include "cy_capsense_lib.h"
#include "cy_capsense_selftest.h"
#if (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN)
    #include "cy_csd.h"
#endif

#if (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2))


/*******************************************************************************
* Constants
*******************************************************************************/
#define CY_CAPSENSE_AUTOTUNE_CALIBRATION_RESOLUTION             (12u)
#define CY_CAPSENSE_AUTOTUNE_CALIBRATION_FREQ_KHZ               (1500u)
#define CY_CAPSENSE_CSD_SNS_FREQ_KHZ_MAX                        (6000u)
#define CY_CAPSENSE_CSD_AUTOTUNE_CAL_UNITS                      (1000u)
#define CY_CAPSENSE_AUTOTUNE_CP_MAX                             (69000Lu)

#define CY_CAPSENSE_EXT_CAP_DISCHARGE_TIME                      (1u)

#define CY_CAPSENSE_VREF_GAIN_MAX                               (32u)
#define CY_CAPSENSE_VREF_VDDA_MIN_DIFF                          (600u)
#if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
    #define CY_CAPSENSE_VREF_SRSS_MV                            (1200u)
#else
    #define CY_CAPSENSE_VREF_SRSS_MV                            (800u)
#endif
#define CY_CAPSENSE_VREF_PASS_MV                                (1200u)

#if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
    #define CY_CAPSENSE_VREF_RANGE_0                            (4700u)
    #define CY_CAPSENSE_VREF_RANGE_1                            (3200u)
    #define CY_CAPSENSE_VREF_RANGE_2                            (2600u)
    #define CY_CAPSENSE_VREF_VALUE_0                            (2743u)
    #define CY_CAPSENSE_VREF_VALUE_1                            (2021u)
    #define CY_CAPSENSE_VREF_VALUE_2                            (1477u)
    #define CY_CAPSENSE_VREF_VALUE_MIN                          (1200u)
#else
    #define CY_CAPSENSE_VREF_RANGE_0                            (2750u)
    #define CY_CAPSENSE_VREF_RANGE_1                            (2200u)
    #define CY_CAPSENSE_VREF_VALUE_0                            (2133u)
    #define CY_CAPSENSE_VREF_VALUE_1                            (1600u)
    #define CY_CAPSENSE_VREF_VALUE_MIN_SRSS                     (1164u)
    #define CY_CAPSENSE_VREF_VALUE_MIN_PASS                     (1200u)
#endif

#if (CY_CAPSENSE_DISABLE == CY_CAPSENSE_USE_CAPTURE)
    const cy_stc_csd_config_t cy_capsense_csdCfg = CY_CAPSENSE_CSD_CONFIG_DEFAULT;
#endif

/*******************************************************************************
* Function Name: Cy_CapSense_IsBusy_V2
****************************************************************************//**
*
* This function returns a status of the CAPSENSE&trade; middleware whether a scan is
* currently in progress or not.
*
* If the middleware is busy, a new scan or setup widgets should not be initiated.
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the middleware:
* - CY_CAPSENSE_NOT_BUSY    - No scan is in progress and a next scan
*                             can be initiated.
* - CY_CAPSENSE_BUSY        - The previously initiated scan is in progress.
*
*******************************************************************************/
uint32_t Cy_CapSense_IsBusy_V2(const cy_stc_capsense_context_t * context)
{
    return (context->ptrCommonContext->status & CY_CAPSENSE_BUSY);
}


/*******************************************************************************
* Function Name: Cy_CapSense_SetBusyFlags
****************************************************************************//**
*
* Sets BUSY flags of the cy_capsense_context.status register specified
* by the flags parameter.
*
* This is an internal function. Do not call this function directly from
* the application program.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_SetBusyFlags(cy_stc_capsense_context_t * context)
{
    context->ptrCommonContext->status |= CY_CAPSENSE_BUSY;
}


/*******************************************************************************
* Function Name: Cy_CapSense_ClrBusyFlags
****************************************************************************//**
*
* Clears BUSY flags of the cy_capsense_context.status register specified
* by the flags parameter.
*
* This is an internal function. Do not call this function directly from
* the application program.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_ClrBusyFlags(cy_stc_capsense_context_t * context)
{
    /* Clear busy flag */
    context->ptrCommonContext->status &= (uint32_t)(~((uint32_t)CY_CAPSENSE_BUSY));
    context->ptrActiveScanSns->scanScope = CY_CAPSENSE_SCAN_SCOPE_SNGL_SNS;

    /* Mark completion of scan cycle */
    context->ptrCommonContext->scanCounter++;

    if(NULL != context->ptrInternalContext->ptrEOSCallback)
    {
        context->ptrInternalContext->ptrEOSCallback(context->ptrActiveScanSns);
    }
}


/*******************************************************************************
* Function Name: Cy_CapSense_SetupWidget
****************************************************************************//**
*
* Performs the initialization required to scan the specified widget.
*
* This function prepares the middleware to scan all the sensors in the specified
* widget by executing the following tasks:
* 1. Configure the CSD HW block if it is not configured to perform the
* sensing method used by the specified widget. This happens only if the
* CSD and CSX methods are used in a user's project.
* 2. Initialize the CSD HW block with specific sensing configuration (e.g.
* sensor clock, scan resolution) used by the widget.
* 3. Disconnect all previously connected electrodes, if the electrodes are
* connected by the Cy_CapSense_CSDSetupWidgetExt(),
* Cy_CapSense_CSXSetupWidgetExt(), or Cy_CapSense_CSDConnectSns()
* functions and are not disconnected.
*
* This function does not start sensor scanning. The Cy_CapSense_Scan()
* function must be called to start the scan sensors in the widget. If this
* function is called more than once, it does not break the middleware operation,
* but only the last initialized widget is in effect.
*
* The status of a sensor scan must be checked using the Cy_CapSense_IsBusy()
* function prior to starting a next scan or setting up another widget.
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
*
* \param widgetId
* Specifies the ID number of the widget. A macro for the widget ID can be found
* in the cycfg_capsense.h file defined as CY_CAPSENSE_<WIDGET_NAME>_WDGT_ID.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the widget setting up operation:
* - CY_CAPSENSE_STATUS_SUCCESS       - The operation is successfully completed.
* - CY_CAPSENSE_STATUS_BAD_PARAM     - The widget is invalid or if the specified widget is
*                          disabled.
* - CY_CAPSENSE_STATUS_INVALID_STATE - The previous scanning is not completed and
*                          the CSD HW block is busy.
* - CY_CAPSENSE_STATUS_UNKNOWN       - An unknown sensing method is used by the widget or
*                          any other spurious error occurred.
*
**********************************************************************************/
cy_capsense_status_t Cy_CapSense_SetupWidget(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context)
{
    cy_capsense_status_t widgetStatus;

    if (CY_CAPSENSE_BUSY == Cy_CapSense_IsBusy(context))
    {
        /* Previous widget is being scanned. Return error. */
        widgetStatus = CY_CAPSENSE_STATUS_INVALID_STATE;
    }
    /*
     * Check whether widget id is valid, specified widget is enabled and widget did not
     * detect any fault conditions. If all conditions are met,
     * set widgetStatus as good, if not, set widgetStatus as bad.
     */
    else if ((context->ptrCommonConfig->numWd > widgetId) &&
        (0u == (context->ptrWdConfig[widgetId].ptrWdContext->status & CY_CAPSENSE_WD_DISABLE_MASK)))
    {
        /* Check widget sensing method and call corresponding setup function */
        switch(context->ptrWdConfig[widgetId].senseMethod)
        {
            #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
                case CY_CAPSENSE_CSD_GROUP:
                    Cy_CapSense_CSDSetupWidget(widgetId, context);
                    break;
            #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

            #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
                case CY_CAPSENSE_CSX_GROUP:
                    Cy_CapSense_CSXSetupWidget(widgetId, context);
                    break;
            #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

            default:
                /* No other sensing methods */
                break;
        }
        widgetStatus = CY_CAPSENSE_STATUS_SUCCESS;
    }
    else
    {
        widgetStatus = CY_CAPSENSE_STATUS_BAD_PARAM;
    }

    return (widgetStatus);
}


/*******************************************************************************
* Function Name: Cy_CapSense_Scan
****************************************************************************//**
*
* Initiates scanning of all the sensors in the widget initialized by
* Cy_CapSense_SetupWidget(), if no scan is in progress.
*
* Prior to calling this function to scan sensors, the widget required
* to be scanned must be initialized using Cy_CapSense_SetupWidget() function.
*
* This function initiates scan only for the first sensor in the widget and then
* exits the function. The scan for the remaining sensors in the widget is
* initiated in the interrupt service routine (part of middleware) triggered
* at the end of each scan completion. Hence, status of the current scan
* should be checked using the Cy_CapSense_IsBusy() and wait until all scans
* in the current widget are finished prior to starting the next scan or
* initializing another widget.
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the scan initiation operation:
* - CY_CAPSENSE_STATUS_SUCCESS       - Scanning is successfully started.
* - CY_CAPSENSE_STATUS_INVALID_STATE - The previous scan is not completed and
*                          the CSD HW block is busy.
* - CY_CAPSENSE_STATUS_UNKNOWN       - An unknown sensing method is used by the widget.
*
********************************************************************************/
cy_capsense_status_t Cy_CapSense_Scan(cy_stc_capsense_context_t * context)
{
    cy_capsense_status_t scanStatus = CY_CAPSENSE_STATUS_SUCCESS;

    if (CY_CAPSENSE_BUSY == Cy_CapSense_IsBusy(context))
    {
        /* Previous widget is being scanned. Return error. */
        scanStatus = CY_CAPSENSE_STATUS_INVALID_STATE;
    }
    else
    {
        /* Check widget sensing method and call appropriate functions */
        switch(context->ptrActiveScanSns->ptrWdConfig->senseMethod)
        {
            #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
                case CY_CAPSENSE_CSD_GROUP:
                    Cy_CapSense_CSDScan(context);
                    break;
            #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

            #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
                case CY_CAPSENSE_CSX_GROUP:
                    Cy_CapSense_CSXScan(context);
                    break;
            #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

            default:
                scanStatus = CY_CAPSENSE_STATUS_UNKNOWN;
                break;
        }
    }
    return (scanStatus);
}


/*******************************************************************************
* Function Name: Cy_CapSense_ScanWidget_V2
****************************************************************************//**
*
* Configures the specified widget and initiates scanning of all the sensors
* in the widget if no scan is in progress.
*
* This function initiates scan only for the first sensor in the widget and then
* exits the function. The scan for the remaining sensors in the widget is
* initiated in the interrupt service routine (part of middleware) triggered
* at the end of each scan completion. Hence, status of the current scan
* should be checked using the Cy_CapSense_IsBusy() and wait until all scans
* in the current widget are finished prior to starting the next scan or
* initializing another widget.
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
*
* \param widgetId
* Specifies the ID number of the widget. A macro for the widget ID can be found
* in the cycfg_capsense.h file defined as CY_CAPSENSE_<WIDGET_NAME>_WDGT_ID.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the scan initiation operation:
* - CY_CAPSENSE_STATUS_SUCCESS       - Scanning is successfully started.
* - CY_CAPSENSE_STATUS_INVALID_STATE - The previous scan is not completed and
*                                      the CSD HW block is busy.
* - CY_CAPSENSE_STATUS_UNKNOWN       - An unknown sensing method is used by the widget.
*
********************************************************************************/
cy_capsense_status_t Cy_CapSense_ScanWidget_V2(uint32_t widgetId, cy_stc_capsense_context_t * context)
{
    cy_stc_active_scan_sns_t * ptrActive = context->ptrActiveScanSns;
    cy_capsense_status_t scanStatus = CY_CAPSENSE_STATUS_SUCCESS;

    if (CY_CAPSENSE_BUSY == Cy_CapSense_IsBusy(context))
    {
        /* Previous widget is being scanned. Return error. */
        scanStatus = CY_CAPSENSE_STATUS_INVALID_STATE;
    }
    else
    {
        if ((context->ptrActiveScanSns->widgetIndex != (uint8_t)widgetId) ||
            (ptrActive->connectedSnsState != CY_CAPSENSE_SNS_DISCONNECTED) ||
            (ptrActive->currentSenseMethod != context->ptrWdConfig[widgetId].senseMethod))
        {
            scanStatus = Cy_CapSense_SetupWidget(widgetId, context);
        }
        if (CY_CAPSENSE_STATUS_SUCCESS == scanStatus)
        {
           scanStatus = Cy_CapSense_Scan(context);
        }
    }
    return (scanStatus);
}


/*******************************************************************************
* Function Name: Cy_CapSense_SetupWidgetExt
****************************************************************************//**
*
* Performs extended initialization for the specified widget and also performs
* initialization required for a specific sensor in the widget.
*
* This function requires using the Cy_CapSense_ScanExt() function to
* initiate a scan.
*
* This function does the same as Cy_CapSense_SetupWidget() and also
* does the following tasks:
* 1. Connects the specified sensor of the widget.
* 2. Configures the CSD HW block to perform a scan of the specified sensor.
*
* Once this function is called to initialize a widget and a sensor, the
* Cy_CapSense_ScanExt() function is called to scan the sensor.
*
* This function is called when no scanning is in progress. I.e.
* Cy_CapSense_IsBusy() returns a non-busy status.
*
* Calling this function directly from the application program is not
* recommended. This function is used to implement only the user's specific
* use cases (for faster execution time or pipeline scanning, for example).
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
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
**********************************************************************************/
cy_capsense_status_t Cy_CapSense_SetupWidgetExt(
                uint32_t widgetId,
                uint32_t sensorId,
                cy_stc_capsense_context_t * context)
{
    cy_capsense_status_t widgetStatus = CY_CAPSENSE_STATUS_BAD_PARAM;

    if (CY_CAPSENSE_BUSY == Cy_CapSense_IsBusy(context))
    {
        /* Previous widget is being scanned. Return error. */
        widgetStatus = CY_CAPSENSE_STATUS_INVALID_STATE;
    }
    /*
     * Check whether widget id is valid, specified widget is enabled and widget did not
     * detect any fault conditions. If all conditions are met,
     * set widgetStatus as good, if not, set widgetStatus as bad.
     */
    else if (context->ptrCommonConfig->numWd > widgetId)
    {
        if (context->ptrWdConfig[widgetId].numSns > sensorId)
        {
            /* Check widget sensing method and call corresponding setup function */
            switch(context->ptrWdConfig[widgetId].senseMethod)
            {
                #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
                    case CY_CAPSENSE_CSD_GROUP:
                        Cy_CapSense_CSDSetupWidgetExt(widgetId, sensorId, context);
                        break;
                #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

                #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
                    case CY_CAPSENSE_CSX_GROUP:
                        Cy_CapSense_CSXSetupWidgetExt(widgetId, sensorId, context);
                        break;
                #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

                default:
                    /* No other sensing methods */
                    break;
            }

            widgetStatus = CY_CAPSENSE_STATUS_SUCCESS;
        }
    }
    else
    {
        /* Do nothing */
    }

    return (widgetStatus);
}


/*******************************************************************************
* Function Name: Cy_CapSense_ScanExt
****************************************************************************//**
*
* Starts a conversion on the pre-configured sensor. This function requires
* using the Cy_CapSense_SetupWidgetExt() function to set up the a
* widget.
*
* This function performs single scanning of one sensor in the widget configured
* by the Cy_CapSense_SetupWidgetExt() function.
*
* Calling this function directly from the application program is not
* recommended. This function is used to implement only the user's specific
* use cases (for faster execution time or pipeline scanning, for example).
* This function is called when no scanning is in progress. I.e.
* Cy_CapSense_IsBusy() returns a non-busy status.
*
* The sensor must be pre-configured by using the
* Cy_CapSense_SetupWidgetExt() prior to calling this function.
* The sensor remains ready for the next scan if a previous scan was triggered
* by using the Cy_CapSense_ScanExt() function. In this case, calling
* Cy_CapSense_SetupWidgetExt() is not required every time before the
* Cy_CapSense_ScanExt() function. If a previous scan was triggered in
* any other way - Cy_CapSense_Scan(), Cy_CapSense_ScanAllWidgets(), or
* Cy_CapSense_RunTuner() - (see the Cy_CapSense_RunTuner() function
* description for more details), the sensor must be pre-configured again by
* using the Cy_CapSense_SetupWidgetExt() prior to calling the
* Cy_CapSense_ScanExt() function.
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_ScanExt(cy_stc_capsense_context_t * context)
{
    cy_capsense_status_t scanStatus = CY_CAPSENSE_STATUS_SUCCESS;

    if (CY_CAPSENSE_BUSY == Cy_CapSense_IsBusy(context))
    {
        /* Previous widget is being scanned. Return error. */
        scanStatus = CY_CAPSENSE_STATUS_INVALID_STATE;
    }
    else
    {
        /* Check widget sensing method and call appropriate functions */
        switch(context->ptrActiveScanSns->ptrWdConfig->senseMethod)
        {
            #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
                case CY_CAPSENSE_CSD_GROUP:
                    Cy_CapSense_CSDScanExt(context);
                    break;
            #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

            #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
                case CY_CAPSENSE_CSX_GROUP:
                    Cy_CapSense_CSXScanExt(context);
                    break;
            #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

            default:
                scanStatus = CY_CAPSENSE_STATUS_UNKNOWN;
                break;
        }
    }
    return (scanStatus);
}


/*******************************************************************************
* Function Name: Cy_CapSense_ScanSensor_V2
****************************************************************************//**
*
* Starts a conversion on the specified sensor.
*
* Calling this function directly from the application program is not
* recommended. This function is used to implement only the user's specific
* use cases (for faster execution time or pipeline scanning, for example).
* This function is called when no scanning is in progress. I.e.
* Cy_CapSense_IsBusy() returns a non-busy status.
* If the widget is already configured by previous call of this function, the
* widget re-configuration is skipped.
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
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
cy_capsense_status_t Cy_CapSense_ScanSensor_V2(
                uint32_t widgetId,
                uint32_t sensorId,
                cy_stc_capsense_context_t * context)
{
    cy_stc_active_scan_sns_t * ptrActive = context->ptrActiveScanSns;
    cy_capsense_status_t scanStatus = CY_CAPSENSE_STATUS_SUCCESS;

    if (CY_CAPSENSE_BUSY == Cy_CapSense_IsBusy(context))
    {
        /* Previous widget is being scanned. Return error. */
        scanStatus = CY_CAPSENSE_STATUS_INVALID_STATE;
    }
    else
    {
        if ((ptrActive->widgetIndex != (uint8_t)widgetId) ||
            (ptrActive->sensorIndex != (uint8_t)sensorId) ||
            (ptrActive->currentSenseMethod != context->ptrWdConfig[widgetId].senseMethod) ||
            (ptrActive->connectedSnsState != CY_CAPSENSE_SNS_CONNECTED))
        {
            scanStatus = Cy_CapSense_SetupWidgetExt(widgetId, sensorId, context);
        }
        if (CY_CAPSENSE_STATUS_SUCCESS == scanStatus)
        {
            scanStatus = Cy_CapSense_ScanExt(context);
        }
    }
    return (scanStatus);
}


/*******************************************************************************
* Function Name: Cy_CapSense_ScanAllWidgets_V2
****************************************************************************//**
*
* Initiates scanning of all enabled widgets (and sensors) in the project.
*
* The tasks of both Cy_CapSense_SetupWidget() and Cy_CapSense_Scan() functions
* are executed by this function. The status of a sensor scan must be checked
* using the Cy_CapSense_IsBusy() prior to starting the next scan or setting
* up another widget.
*
* This function initiates a scan only for the first sensor in the first widget
* and then exits the function. The scan for the remaining sensors are initiated
* in the interrupt service routine (part of middleware) triggered at the end
* of each scan completion. Hence, the status of the current scan should be
* checked using the Cy_CapSense_IsBusy() and wait until all scans is finished
* prior to starting a next scan or initializing another widget.
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the operation:
* - CY_CAPSENSE_STATUS_SUCCESS       - Scanning is successfully started.
* - CY_CAPSENSE_STATUS_BAD_PARAM     - All the widgets are disabled.
* - CY_CAPSENSE_STATUS_INVALID_STATE - The previous scanning is not completed and the
*                          CSD HW block is busy.
* - CY_CAPSENSE_STATUS_UNKNOWN       - There are unknown errors.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_ScanAllWidgets_V2(cy_stc_capsense_context_t * context)
{
    uint32_t wdgtIndex;
    cy_stc_active_scan_sns_t * ptrActive = context->ptrActiveScanSns;
    cy_capsense_status_t scanStatus = CY_CAPSENSE_STATUS_UNKNOWN;

    if (CY_CAPSENSE_BUSY == Cy_CapSense_IsBusy(context))
    {
        /* Previous widget is being scanned. Return error. */
        scanStatus = CY_CAPSENSE_STATUS_INVALID_STATE;
    }
    else
    {
        /*
        * Set up first widget. If widget returned error,
        * set up next, continue same until widget does not return error.
        */
        for (wdgtIndex = 0u; wdgtIndex < context->ptrCommonConfig->numWd; wdgtIndex++)
        {
            scanStatus = Cy_CapSense_SetupWidget(wdgtIndex, context);
            if (CY_CAPSENSE_STATUS_SUCCESS == scanStatus)
            {
                ptrActive->scanScope = CY_CAPSENSE_SCAN_SCOPE_ALL_WD_MASK;

                /* Initiate scan and quit loop */
                scanStatus = Cy_CapSense_Scan(context);

                break;
            }
        }
    }

    return (scanStatus);
}


/*******************************************************************************
* Function Name: Cy_CapSense_InternalPreCalculation
****************************************************************************//**
*
* Calculate different internal parameters, register values in advance to
* speed up execution time.
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
cy_capsense_status_t Cy_CapSense_InternalPreCalculation(cy_stc_capsense_context_t * context)
{
    cy_capsense_status_t initStatus = CY_CAPSENSE_STATUS_SUCCESS;
    uint32_t wdgtIndex;
    uint32_t temp;

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
        if ((context->ptrCommonConfig->portCmodPadNum == context->ptrCommonConfig->portCmodNum) &&
            (context->ptrCommonConfig->pinCmodPad == context->ptrCommonConfig->pinCmod))
        {
            context->ptrInternalContext->csdCmodConnection = (uint8_t)CY_CAPSENSE_CMODPAD_E;
        }
        else if ((context->ptrCommonConfig->portCshPadNum == context->ptrCommonConfig->portCmodNum) &&
                 (context->ptrCommonConfig->pinCshPad == context->ptrCommonConfig->pinCmod))
        {
            context->ptrInternalContext->csdCmodConnection = (uint8_t)CY_CAPSENSE_CTANKPAD_E;
        }
        else if ((context->ptrCommonConfig->portShieldPadNum == context->ptrCommonConfig->portCmodNum) &&
                 (context->ptrCommonConfig->pinShieldPad == context->ptrCommonConfig->pinCmod))
        {
            context->ptrInternalContext->csdCmodConnection = (uint8_t)CY_CAPSENSE_CSHIELDPAD_E;
        }
        else if ((context->ptrCommonConfig->portVrefExtPadNum == context->ptrCommonConfig->portCmodNum) &&
                 (context->ptrCommonConfig->pinVrefExtPad == context->ptrCommonConfig->pinCmod))
        {
            context->ptrInternalContext->csdCmodConnection = (uint8_t)CY_CAPSENSE_VREFEXTPAD_E;
        }
        else
        {
            context->ptrInternalContext->csdCmodConnection = (uint8_t)CY_CAPSENSE_CMODPAD_E;
            initStatus = CY_CAPSENSE_STATUS_BAD_PARAM;
        }

        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_CAP_EN)
            /* Csh Capacitor Placement */
            if ((context->ptrCommonConfig->portCmodPadNum == context->ptrCommonConfig->portCshNum) &&
                (context->ptrCommonConfig->pinCmodPad == context->ptrCommonConfig->pinCsh))
            {
                context->ptrInternalContext->csdCshConnection = (uint8_t)CY_CAPSENSE_CMODPAD_E;
            }
            else if ((context->ptrCommonConfig->portCshPadNum == context->ptrCommonConfig->portCshNum) &&
                     (context->ptrCommonConfig->pinCshPad == context->ptrCommonConfig->pinCsh))
            {
                context->ptrInternalContext->csdCshConnection = (uint8_t)CY_CAPSENSE_CTANKPAD_E;
            }
            else if ((context->ptrCommonConfig->portShieldPadNum == context->ptrCommonConfig->portCshNum) &&
                     (context->ptrCommonConfig->pinShieldPad == context->ptrCommonConfig->pinCsh))
            {
                context->ptrInternalContext->csdCshConnection = (uint8_t)CY_CAPSENSE_CSHIELDPAD_E;
            }
            else if ((context->ptrCommonConfig->portVrefExtPadNum == context->ptrCommonConfig->portCshNum) &&
                     (context->ptrCommonConfig->pinVrefExtPad == context->ptrCommonConfig->pinCsh))
            {
                context->ptrInternalContext->csdCshConnection = (uint8_t)CY_CAPSENSE_VREFEXTPAD_E;
            }
            else
            {
                context->ptrInternalContext->csdCshConnection = (uint8_t)CY_CAPSENSE_CTANKPAD_E;
                initStatus = CY_CAPSENSE_STATUS_BAD_PARAM;
            }
        #else
            context->ptrInternalContext->csdCshConnection = 0u;
        #endif

        /* Switch CSD Comparator Selection */
        switch (context->ptrInternalContext->csdCmodConnection)
        {
            case (uint8_t)CY_CAPSENSE_CMODPAD_E:
                context->ptrInternalContext->csdRegSwCmpPSel = CY_CAPSENSE_CSD_SW_CMP_P_SEL_SW_SFPM_STATIC_CLOSE;
                break;
            case (uint8_t)CY_CAPSENSE_CSHIELDPAD_E:
                context->ptrInternalContext->csdRegSwCmpPSel = CY_CAPSENSE_CSD_SW_CMP_P_SEL_SW_SFPS_STATIC_CLOSE;
                break;
            default:
                context->ptrInternalContext->csdRegSwCmpPSel = CY_CAPSENSE_CSD_SW_CMP_P_SEL_SW_SFPT_STATIC_CLOSE;
                break;
        }
        context->ptrInternalContext->csdRegSwCmpNSel = CY_CAPSENSE_CSD_SW_CMP_N_SEL_SW_SCRH_STATIC_CLOSE;

        /* Defines the drive mode of pins depending on the Inactive sensor connection setting */
        (void) Cy_CapSense_SetInactiveElectrodeState(context->ptrCommonConfig->csdInactiveSnsConnection,
                                                     CY_CAPSENSE_CSD_GROUP, context);

        /* Prepares CONFIG register value */
        context->ptrInternalContext->csdRegConfig = 0u;
        /* Iref Source */
        #if (CY_CAPSENSE_PSOC6_FOURTH_GEN)
            if (CY_CAPSENSE_IREF_PASS == context->ptrCommonConfig->ssIrefSource)
            {
                context->ptrInternalContext->csdRegConfig |= CY_CAPSENSE_CSD_CONFIG_IREF_SEL_MSK;
            }
        #endif

        /* Filter Delay */
        temp = context->ptrCommonConfig->periClkHz / context->ptrCommonContext->modCsdClk;
        if (temp > CY_CAPSENSE_MOD_CSD_CLK_24000000_HZ)
        {
            context->ptrInternalContext->csdRegConfig |= CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_48MHZ;
        }
        else if (temp > CY_CAPSENSE_MOD_CSD_CLK_12000000_HZ)
        {
            context->ptrInternalContext->csdRegConfig |= CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_24MHZ;
        }
        else
        {
            context->ptrInternalContext->csdRegConfig |= CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_12MHZ;
        }
        /* Shield Delay */
        context->ptrInternalContext->csdRegConfig |= (((uint32_t)context->ptrCommonConfig->csdShieldDelay) << CY_CAPSENSE_CSD_CONFIG_SHIELD_DELAY_POS);
        /* Sense Enable */
        context->ptrInternalContext->csdRegConfig |= CSD_CONFIG_SENSE_EN_Msk;
        /* Power On */
        context->ptrInternalContext->csdRegConfig |= CSD_CONFIG_ENABLE_Msk;

        context->ptrInternalContext->csdRegSwHsPSelCmodInit = 0u;
        context->ptrInternalContext->csdRegSwHsPSelCtankInit = 0u;
        context->ptrInternalContext->csdRegSwHsPSelScan = 0u;

        switch (context->ptrInternalContext->csdCmodConnection)
        {
            case (uint8_t)CY_CAPSENSE_CMODPAD_E:
                context->ptrInternalContext->csdRegSwHsPSelCmodInit = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE;
                break;
            case (uint8_t)CY_CAPSENSE_CSHIELDPAD_E:
                context->ptrInternalContext->csdRegSwHsPSelCmodInit = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE;
                break;
            default:
                context->ptrInternalContext->csdRegSwHsPSelCmodInit = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE;
                break;
        }

        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
            #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_CAP_EN)
                switch (context->ptrInternalContext->csdCshConnection)
                {
                    case (uint8_t)CY_CAPSENSE_CMODPAD_E:
                        context->ptrInternalContext->csdRegSwHsPSelCtankInit = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE;
                        context->ptrInternalContext->csdRegSwHsPSelScan = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE;
                        break;
                    case (uint8_t)CY_CAPSENSE_CSHIELDPAD_E:
                        context->ptrInternalContext->csdRegSwHsPSelCtankInit = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE;
                        context->ptrInternalContext->csdRegSwHsPSelScan = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE;
                        break;
                    default:
                        context->ptrInternalContext->csdRegSwHsPSelCtankInit = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE;
                        context->ptrInternalContext->csdRegSwHsPSelScan = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE;
                        break;

                }
            #else
                context->ptrInternalContext->csdRegSwHsPSelScan = CY_CAPSENSE_CSD_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE;
            #endif

        /* BYP switch selection */
            context->ptrInternalContext->csdRegSwBypSel = CY_CAPSENSE_CSD_SW_BYP_SEL_SW_BYA_MSK | CY_CAPSENSE_CSD_SW_BYP_SEL_SW_BYB_MSK;
        #else
            context->ptrInternalContext->csdRegSwBypSel = CY_CAPSENSE_CSD_SW_BYP_SEL_SW_BYA_MSK;
        #endif

        /* Switch resistance selection */
        context->ptrInternalContext->csdRegSwResInit = ((uint32_t)context->ptrCommonConfig->csdInitSwRes << CSD_SW_RES_RES_HCAV_Pos) |
                                                       ((uint32_t)context->ptrCommonConfig->csdInitSwRes << CSD_SW_RES_RES_HCBV_Pos);
        context->ptrInternalContext->csdRegSwResScan = ((uint32_t)context->ptrCommonConfig->csdShieldSwRes << CSD_SW_RES_RES_HCBV_Pos) |
                                                       ((uint32_t)context->ptrCommonConfig->csdShieldSwRes << CSD_SW_RES_RES_HCBG_Pos);

        /* Switch DSI selection */
        context->ptrInternalContext->csdRegSwDsiSel = CY_CAPSENSE_DEFAULT_CSD_SW_DSI_SEL;

        #if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
            switch (context->ptrInternalContext->csdCmodConnection)
            {
                case (uint8_t)CY_CAPSENSE_CMODPAD_E:
                    context->ptrInternalContext->csdRegSwDsiSel |= CY_CAPSENSE_CSD_SW_DSI_SEL_CMOD_MSK;
                    break;
                case (uint8_t)CY_CAPSENSE_CTANKPAD_E:
                        context->ptrInternalContext->csdRegSwDsiSel |= CY_CAPSENSE_CSD_SW_DSI_SEL_CSH_TANK_MSK;
                    break;
                default:
                    /* No action on other connections */
                    break;
            }

            #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) && \
                 (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_CAP_EN))
                switch (context->ptrInternalContext->csdCshConnection)
                {
                    case (uint8_t)CY_CAPSENSE_CMODPAD_E:
                        context->ptrInternalContext->csdRegSwDsiSel |= CY_CAPSENSE_CSD_SW_DSI_SEL_CMOD_MSK;
                        break;
                    case (uint8_t)CY_CAPSENSE_CTANKPAD_E:
                        context->ptrInternalContext->csdRegSwDsiSel |= CY_CAPSENSE_CSD_SW_DSI_SEL_CSH_TANK_MSK;
                        break;
                    default:
                        /* No action on other connections */
                        break;
                }
            #endif
        #endif

        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
            if (CY_CAPSENSE_LOW_VOLTAGE_LIMIT > context->ptrCommonConfig->vdda)
            {
                context->ptrInternalContext->csdRegAmuxbufInit = CY_CAPSENSE_CSD_AMBUF_PWR_MODE_NORM;
            }
            else
            {
                context->ptrInternalContext->csdRegAmuxbufInit = CY_CAPSENSE_CSD_AMBUF_PWR_MODE_HI;
            }
        #else
            context->ptrInternalContext->csdRegAmuxbufInit = CY_CAPSENSE_CSD_AMBUF_PWR_MODE_OFF;
        #endif

        /* Switch AMUXBUF selection */
        context->ptrInternalContext->csdRegSwAmuxbufSel = 0u;

        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
            if (((CY_CAPSENSE_LOW_VOLTAGE_LIMIT > context->ptrCommonConfig->vdda) &&
                 (CY_CAPSENSE_IDAC_SINKING == context->ptrCommonConfig->csdChargeTransfer)) ||
                ((CY_CAPSENSE_LOW_VOLTAGE_LIMIT <= context->ptrCommonConfig->vdda) &&
                 (CY_CAPSENSE_IDAC_SOURCING == context->ptrCommonConfig->csdChargeTransfer)))
            {
                context->ptrInternalContext->csdRegSwAmuxbufSel = CY_CAPSENSE_CSD_SW_AMUXBUF_SEL_SW_IRH_STATIC_CLOSE | CY_CAPSENSE_CSD_SW_AMUXBUF_SEL_SW_ICB_PHI2;
            }
        #endif

        context->ptrInternalContext->csdRegSwShieldSelScan = 0u;

        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
            #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_CAP_EN)
                if (CY_CAPSENSE_IDAC_SINKING == context->ptrCommonConfig->csdChargeTransfer)
                {
                    context->ptrInternalContext->csdRegSwShieldSelScan = CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBG_HSCMP;
                }
                else
                {
                    context->ptrInternalContext->csdRegSwShieldSelScan = CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBV_PHI1_HSCMP;
                }
            #else
                if (CY_CAPSENSE_IDAC_SINKING == context->ptrCommonConfig->csdChargeTransfer)
                {
                    context->ptrInternalContext->csdRegSwShieldSelScan = CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBV_PHI1 |
                                                                         CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBG_PHI2_HSCMP;
                }
                else
                {
                    context->ptrInternalContext->csdRegSwShieldSelScan = CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBG_PHI1 |
                                                                         CY_CAPSENSE_CSD_SW_SHIELD_SEL_SW_HCBV_PHI2_HSCMP;
                }
            #endif
        #endif

        /* High-Speed Comparator initialization */
        context->ptrInternalContext->csdRegHscmpInit = CY_CAPSENSE_CSD_HSCMP_HSCMP_EN_MSK;
        context->ptrInternalContext->csdRegHscmpScan = CY_CAPSENSE_CSD_HSCMP_HSCMP_EN_MSK;
        if (CY_CAPSENSE_IDAC_SINKING == context->ptrCommonConfig->csdChargeTransfer)
        {
            context->ptrInternalContext->csdRegHscmpScan = CY_CAPSENSE_CSD_HSCMP_HSCMP_EN_MSK | CY_CAPSENSE_CSD_HSCMP_HSCMP_INVERT_MSK;
        }

        #if (CY_CAPSENSE_DISABLE == CY_CAPSENSE_CSD_SHIELD_EN)
            context->ptrInternalContext->csdRegHscmpScan = 0u;
        #endif

        /* IDACs Config */
        context->ptrInternalContext->csdIdacAConfig = context->ptrCommonConfig->idacGainTable[0u].gainReg;
        context->ptrInternalContext->csdIdacBConfig = context->ptrCommonConfig->idacGainTable[0u].gainReg;

        /* IDACs Polarities */
        if (CY_CAPSENSE_IDAC_SINKING == context->ptrCommonConfig->csdChargeTransfer)
        {
            context->ptrInternalContext->csdIdacAConfig |= (CY_CAPSENSE_CSD_IDACA_POLARITY_VDDA_SNK << CY_CAPSENSE_CSD_IDACA_POLARITY_POS);
            context->ptrInternalContext->csdIdacBConfig |= (CY_CAPSENSE_CSD_IDACB_POLARITY_VDDA_SNK << CY_CAPSENSE_CSD_IDACB_POLARITY_POS);
        }
        else
        {
            context->ptrInternalContext->csdIdacAConfig |= (CY_CAPSENSE_CSD_IDACA_POLARITY_VSSA_SRC << CY_CAPSENSE_CSD_IDACA_POLARITY_POS);
            context->ptrInternalContext->csdIdacBConfig |= (CY_CAPSENSE_CSD_IDACB_POLARITY_VSSA_SRC << CY_CAPSENSE_CSD_IDACB_POLARITY_POS);
        }
        /* IDACs Balancing Mode */
        context->ptrInternalContext->csdIdacAConfig |= (CY_CAPSENSE_CSD_IDACA_BALL_MODE_FULL << CY_CAPSENSE_CSD_IDACA_BALL_MODE_POS);
        context->ptrInternalContext->csdIdacBConfig |= (CY_CAPSENSE_CSD_IDACB_BALL_MODE_FULL << CY_CAPSENSE_CSD_IDACB_BALL_MODE_POS);
        /* Legs Config */
        context->ptrInternalContext->csdIdacAConfig |= (CY_CAPSENSE_CSD_IDACA_LEG1_MODE_CSD << CY_CAPSENSE_CSD_IDACA_LEG1_MODE_POS);
        context->ptrInternalContext->csdIdacAConfig |= (CY_CAPSENSE_CSD_IDACA_LEG2_MODE_CSD << CY_CAPSENSE_CSD_IDACA_LEG2_MODE_POS);
        context->ptrInternalContext->csdIdacAConfig |= (CY_CAPSENSE_CSD_IDACA_LEG1_EN_MSK);

        context->ptrInternalContext->csdIdacBConfig |= (CY_CAPSENSE_CSD_IDACB_LEG1_MODE_CSD_STATIC << CY_CAPSENSE_CSD_IDACB_LEG1_MODE_POS);
        context->ptrInternalContext->csdIdacBConfig |= (CY_CAPSENSE_CSD_IDACB_LEG2_MODE_CSD_STATIC << CY_CAPSENSE_CSD_IDACB_LEG2_MODE_POS);

        #if(CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_IDAC_COMP_EN)
            context->ptrInternalContext->csdIdacBConfig |= (CY_CAPSENSE_CSD_IDACB_LEG1_EN_MSK);
        #endif

        /* IO Control Selection */
        if (CY_CAPSENSE_IDAC_SINKING == context->ptrCommonConfig->csdChargeTransfer)
        {
            #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
                context->ptrInternalContext->csdRegIoSel = (CY_CAPSENSE_CSD_TX_N_OUT_EN_PHI1 |
                                                            CY_CAPSENSE_CSD_TX_N_AMUXA_EN_PHI2 |
                                                            CY_CAPSENSE_CSD_TX_OUT_EN_PHI1_DELAY |
                                                            CY_CAPSENSE_CSD_TX_AMUXB_EN_PHI2_DELAY |
                                                            CY_CAPSENSE_CSD_TX_OUT_MSK |
                                                            CY_CAPSENSE_CSD_TX_N_OUT_STATIC_CLOSE);
            #else
                context->ptrInternalContext->csdRegIoSel = (CY_CAPSENSE_CSD_TX_N_OUT_EN_PHI1 |
                                                            CY_CAPSENSE_CSD_TX_N_AMUXA_EN_PHI2 |
                                                            CY_CAPSENSE_CSD_TX_N_OUT_STATIC_CLOSE);
            #endif
        }
        else
        {
            #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
                context->ptrInternalContext->csdRegIoSel = (CY_CAPSENSE_CSD_TX_N_OUT_EN_PHI1 |
                                                            CY_CAPSENSE_CSD_TX_N_AMUXA_EN_PHI2 |
                                                            CY_CAPSENSE_CSD_TX_OUT_EN_PHI1_DELAY |
                                                            CY_CAPSENSE_CSD_TX_AMUXB_EN_PHI2_DELAY);
            #else
                context->ptrInternalContext->csdRegIoSel = (CY_CAPSENSE_CSD_TX_N_OUT_EN_PHI1 |
                                                            CY_CAPSENSE_CSD_TX_N_AMUXA_EN_PHI2);
            #endif
        }

        if(context->ptrCommonConfig->csdVref == 0u)
        {
            /* Get the recommended Vref voltage value if the Custom Vref option is not used */
            temp = Cy_CapSense_GetVrefAutoMv(context);
        }
        else
        {
            /* Initialize the Temp variable with the user defined Vref voltage */
            temp = (uint32_t)context->ptrCommonConfig->csdVref;
            if(temp > (uint32_t)((uint32_t)context->ptrCommonConfig->vdda - CY_CAPSENSE_VREF_VDDA_MIN_DIFF))
            {
                temp = (uint32_t)context->ptrCommonConfig->vdda - CY_CAPSENSE_VREF_VDDA_MIN_DIFF;
            }
        }

        /* Calculate the VrefHigh Gain for the desired Vref voltage when PASS is used as the Vref source. */
        temp = Cy_CapSense_GetVrefHighGain(temp, context);
        /* Calculates the VrefHigh voltage, when SRSS is used as the Vref source. */
        context->ptrInternalContext->csdVrefVoltageMv = (uint16_t)Cy_CapSense_GetVrefHighMv(temp, context);
        context->ptrInternalContext->csdVrefGain = (uint8_t)temp;

        /* RefGen initialization */
        context->ptrInternalContext->csdRegRefgen  = (CSD_REFGEN_REFGEN_EN_Msk |
                                                      CSD_REFGEN_RES_EN_Msk |
                                                      (uint32_t)(temp << CSD_REFGEN_GAIN_Pos));
        #if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
            if (CY_CAPSENSE_LOW_VOLTAGE_LIMIT > context->ptrCommonConfig->vdda)
            {
                context->ptrInternalContext->csdRegRefgen  = (CSD_REFGEN_REFGEN_EN_Msk |
                                                              CSD_REFGEN_BYPASS_Msk);
            }
        #endif

        /* SW_RefGen_SEL initialization */
        context->ptrInternalContext->csdRegSwRefGenSel = CSD_SW_REFGEN_SEL_SW_SGR_Msk;
        #if (CY_CAPSENSE_PSOC6_FOURTH_GEN)
            if(CY_CAPSENSE_VREF_PASS == context->ptrCommonConfig->ssVrefSource)
            {
                context->ptrInternalContext->csdRegSwRefGenSel = CSD_SW_REFGEN_SEL_SW_SGRP_Msk;
            }
        #endif

        #if(CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_IDAC_COMP_EN)
            context->ptrInternalContext->csdRegSwRefGenSel |= CSD_SW_REFGEN_SEL_SW_IAIB_Msk;
        #endif

    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

    /* Initialize maxRawCount for all widgets */
    for (wdgtIndex = context->ptrCommonConfig->numWd; wdgtIndex-- > 0u;)
    {
        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
            if (CY_CAPSENSE_CSD_GROUP == context->ptrWdConfig[wdgtIndex].senseMethod)
            {
                context->ptrWdContext[wdgtIndex].maxRawCount =
                                (uint16_t)(((uint32_t)0x01u << context->ptrWdContext[wdgtIndex].resolution) - 1u);
            }
        #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
            if (CY_CAPSENSE_CSX_GROUP == context->ptrWdConfig[wdgtIndex].senseMethod)
            {
                context->ptrWdContext[wdgtIndex].maxRawCount = (uint16_t)(context->ptrWdContext[wdgtIndex].resolution *
                                (context->ptrWdContext[wdgtIndex].snsClk - CY_CAPSENSE_CSX_DEADBAND_CYCLES_NUMBER));
            }
        #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */
    }

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
        /* CSX Initialization */
        /* Defines the inactive electrode mode depending on the Inactive sensor connection setting */
        (void) Cy_CapSense_SetInactiveElectrodeState(context->ptrCommonConfig->csxInactiveSnsConnection,
                                                     CY_CAPSENSE_CSX_GROUP, context);

        context->ptrInternalContext->csxRegSwRefGenSel = CSD_SW_REFGEN_SEL_SW_SGR_Msk;
        #if (CY_CAPSENSE_PSOC6_FOURTH_GEN)
            if(CY_CAPSENSE_VREF_PASS == context->ptrCommonConfig->ssVrefSource)
            {
                context->ptrInternalContext->csxRegSwRefGenSel = CSD_SW_REFGEN_SEL_SW_SGRP_Msk;
            }
        #endif

        /* Initialize CONFIG register values */
        context->ptrInternalContext->csxRegConfigInit = CY_CAPSENSE_DEFAULT_CSD_CONFIG_CFG;
        context->ptrInternalContext->csxRegConfigScan = CY_CAPSENSE_PRESCAN_CSD_CONFIG_CFG;
        #if (CY_CAPSENSE_PSOC6_FOURTH_GEN)
            if(CY_CAPSENSE_IREF_PASS == context->ptrCommonConfig->ssIrefSource)
            {
                context->ptrInternalContext->csxRegConfigInit |= CY_CAPSENSE_CSD_CONFIG_IREF_SEL_MSK;
                context->ptrInternalContext->csxRegConfigScan |= CY_CAPSENSE_CSD_CONFIG_IREF_SEL_MSK;
            }
        #endif

        /* Initialize FilterDelay for CSX sensing */
        if (CY_CAPSENSE_MOD_CSD_CLK_12000000_HZ < context->ptrCommonConfig->periClkHz)
        {
            /* Calculate CSX modClk in Hz */
            temp = context->ptrCommonConfig->periClkHz / (uint32_t) context->ptrCommonContext->modCsxClk;
            if(temp <= CY_CAPSENSE_MOD_CSD_CLK_12000000_HZ)
            {
                context->ptrInternalContext->csxRegConfigScan |= CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_12MHZ;
            }
            else if(temp <= CY_CAPSENSE_MOD_CSD_CLK_24000000_HZ)
            {
                context->ptrInternalContext->csxRegConfigScan |= CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_24MHZ;
            }
            else
            {
                context->ptrInternalContext->csxRegConfigScan |= CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_48MHZ;
            }
        }
        else
        {
            context->ptrInternalContext->csxRegConfigScan |= CY_CAPSENSE_CSD_CONFIG_FILTER_DELAY_12MHZ;
        }

        /* Default switch resistance selection */
        context->ptrInternalContext->csxRegSwResInit =
        (((uint32_t)context->ptrCommonConfig->csxInitShieldSwRes << CSD_SW_RES_RES_HCAV_Pos) |
         ((uint32_t)context->ptrCommonConfig->csxInitShieldSwRes << CSD_SW_RES_RES_HCAG_Pos) |
         ((uint32_t)context->ptrCommonConfig->csxInitShieldSwRes << CSD_SW_RES_RES_HCBV_Pos) |
         ((uint32_t)context->ptrCommonConfig->csxInitShieldSwRes << CSD_SW_RES_RES_HCBG_Pos) |
         ((uint32_t)context->ptrCommonConfig->csxInitSwRes << CSD_SW_RES_RES_F1PM_Pos) |
         ((uint32_t)context->ptrCommonConfig->csxInitSwRes << CSD_SW_RES_RES_F2PT_Pos));
        /* Switch resistance selection for scan */
        context->ptrInternalContext->csxRegSwResScan =
        (((uint32_t)context->ptrCommonConfig->csxScanShieldSwRes << CSD_SW_RES_RES_HCAV_Pos) |
         ((uint32_t)context->ptrCommonConfig->csxScanShieldSwRes << CSD_SW_RES_RES_HCAG_Pos) |
         ((uint32_t)context->ptrCommonConfig->csxScanShieldSwRes << CSD_SW_RES_RES_HCBV_Pos) |
         ((uint32_t)context->ptrCommonConfig->csxScanShieldSwRes << CSD_SW_RES_RES_HCBG_Pos) |
         ((uint32_t)context->ptrCommonConfig->csxScanSwRes << CSD_SW_RES_RES_F1PM_Pos) |
         ((uint32_t)context->ptrCommonConfig->csxScanSwRes << CSD_SW_RES_RES_F2PT_Pos));

        /* Switch resistance selection for precharge */
        context->ptrInternalContext->csxRegSwResPrech = context->ptrInternalContext->csxRegSwResInit;

        /* AMUXBUF_CFG / AMUXBUF_SEL_CFG / SW_CMP_N_SEL initialization */
        context->ptrInternalContext->csxRegAMuxBuf = CY_CAPSENSE_DEFAULT_CSD_AMBUF_CFG;
        context->ptrInternalContext->csxRegRefgenSel = CY_CAPSENSE_DEFAULT_CSD_SW_AMUXBUF_SEL_CFG;
        context->ptrInternalContext->csxRegSwCmpNSel = CY_CAPSENSE_DEFAULT_CSD_SW_CMP_N_SEL_CFG;
        #if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
            if (context->ptrCommonConfig->vdda < CY_CAPSENSE_LOW_VOLTAGE_LIMIT)
            {
                context->ptrInternalContext->csxRegAMuxBuf = CY_CAPSENSE_LOW_VOLTAGE_CSD_AMBUF_CFG;
                context->ptrInternalContext->csxRegRefgenSel = CY_CAPSENSE_LOW_VOLTAGE_CSD_SW_AMUXBUF_SEL_CFG;
                context->ptrInternalContext->csxRegSwCmpNSel = CY_CAPSENSE_LOW_VOLTAGE_CSD_SW_CMP_N_SEL_CFG;
            }
        #endif

        /* REFGEN_CFG initialization */
        #if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
            if (context->ptrCommonConfig->vdda < CY_CAPSENSE_LOW_VOLTAGE_LIMIT)
            {
                context->ptrInternalContext->csxRegRefgen = CY_CAPSENSE_LOW_VOLTAGE_CSD_REFGEN_CFG;
            }
            else
            {
                context->ptrInternalContext->csxRegRefgen = CY_CAPSENSE_DEFAULT_CSD_REFGEN_CFG;
            }
        #else
            /* Initialize RefGen Gain and Vref switches for sensing operation */
            if(CY_CAPSENSE_VREF_PASS == context->ptrCommonConfig->ssVrefSource)
            {
                context->ptrInternalContext->csxRegRefgen = CY_CAPSENSE_PASS_CSD_REFGEN_CFG;
            }
            else
            {
                context->ptrInternalContext->csxRegRefgen = CY_CAPSENSE_SRSS_CSD_REFGEN_CFG;
            }
        #endif
    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

    return (initStatus);
}


/*******************************************************************************
* Function Name: Cy_CapSense_SsInitialize
****************************************************************************//**
*
* Performs hardware and firmware initialization required for proper operation
* of the CAPSENSE&trade; middleware. This function is called from
* the Cy_CapSense_Init() prior to calling any other function of the middleware.
*
* This function
* 1. Depending on the configuration, the function initializes the CSD HW block
* for the corresponding sensing mode.
* 2. Sets all IOs into the default state.
* 3. Performs pre-calculations of register values depending on configuration.
*
* Calling the Cy_CapSense_Init() is the recommended method to initialize
* the CAPSENSE&trade; middleware at power-up. The Cy_CapSense_SsInitialize()
* should not be used for initialization, resume, or wake-up operations.
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
cy_capsense_status_t Cy_CapSense_SsInitialize(cy_stc_capsense_context_t * context)
{
    cy_capsense_status_t initStatus;

    initStatus = Cy_CapSense_InternalPreCalculation(context);

    Cy_CapSense_InitializeSourceSenseClk(context);

    /* Set all IO states to the default state */
    Cy_CapSense_SetIOsInDesiredState(CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF, 0u, CY_CAPSENSE_HSIOM_SEL_GPIO, context);
    Cy_CapSense_SetSpecificIOsInDefaultState(context);

    /* The CSD HW block is initialized in the Setup Widget functions based on widget sensing method */
    (void)Cy_CapSense_SwitchSensingMode(CY_CAPSENSE_UNDEFINED_GROUP, context);

    return (initStatus);
}


/*******************************************************************************
* Function Name: Cy_CapSense_SetPinState_V2
****************************************************************************//**
*
* Sets the state (drive mode and HSIOM state) of the GPIO used by a sensor.
*
* The possible states are GND, Shield, High-Z, Tx, Rx, and Sensor.
* If the sensor specified in the input parameter is a ganged sensor, then
* the state of all GPIOs associated with the ganged sensor is updated.
*
* To access a sensor of CSD of button or slider widgets, use the sensor ID.
* To access a sensor of CSD matrix button or touchpad widgets,
* use either row ID or column ID as appropriate.
* To access sensor CSX widgets, use either Rx ID or Tx ID as appropriate.
*
* This function accepts the CY_CAPSENSE_SHIELD and CY_CAPSENSE_SENSOR states
* as an input only if there is at least one CSD widget in the project.
* Similarly, this function accepts the CY_CAPSENSE_TX_PIN and
* CY_CAPSENSE_RX_PIN states as an input only if there is at least one
* CSX widget in the project.
*
* This function must not be called while the middleware is in the busy state.
* Calling this function directly from the application program is not
* recommended. This function is used to implement only the custom-specific
* use cases.
*
* Functions that perform a setup and scan of a sensor/widget automatically
* set the required pin states for a sensor as required and overwrite changes
* made by this function to a sensor that are going to be scanned. Therefore
* the Cy_CapSense_SetPinState() function could be called in StartSample
* callback (see the \ref group_capsense_callbacks section for details)
* or with low-level functions that perform a single-sensor scanning.
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
*
* \param widgetId
* Specifies the ID number of the widget. A macro for the widget ID can be found
* in the cycfg_capsense.h file defined as CY_CAPSENSE_<WIDGET_NAME>_WDGT_ID.
*
* \param sensorElement
* Specifies the ID of the sensor element within the widget to change
* its pin state.
* * For the CSD widgets use the sensor ID. A macro for the
*   sensor ID within a specified widget can be found in the cycfg_capsense.h
*   file defined as CY_CAPSENSE_<WIDGET_NAME>_SNS<SENSOR_NUMBER>_ID.
* * For the CSX widgets use either Rx ID or Tx ID.
*   The first Rx in a widget corresponds to sensorElement = 0; the second
*   Rx in a widget corresponds to sensorElement = 1, and so on.
*   The last Tx in a widget corresponds to sensorElement = (RxNum + TxNum - 1).
*   A macro for the Rx ID or Tx ID can be found in the cycfg_capsense.h
*   file defined as CY_CAPSENSE_<WIDGET_NAME>_<TX/RX><TX/RX_NUMBER>_ID.
*
* \param state
* Specifies the state of the sensor to be set:
* 1. CY_CAPSENSE_GROUND - The pin is connected to the ground.
* 2. CY_CAPSENSE_HIGHZ  - The drive mode of the pin is set to High-Z
*                         Analog.
* 3. CY_CAPSENSE_SHIELD - The shield signal is routed to the pin
*                         (available only if CSD sensing method with
*                         shield electrode is enabled).
* 4. CY_CAPSENSE_SENSOR - The pin is connected to the scanning bus
*                         (available only if CSD sensing method is enabled).
* 5. CY_CAPSENSE_TX_PIN - The Tx signal is routed to the sensor
*                         (available only if CSX sensing method is enabled).
* 6. CY_CAPSENSE_RX_PIN - The pin is connected to the scanning bus
*                         (available only if CSX sensing method is enabled).
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return status
* Returns the operation status:
* - CY_CAPSENSE_STATUS_SUCCESS   - Indicates the successful electrode setting.
* - CY_CAPSENSE_STATUS_BAD_PARAM - 1) widgetID or sensorElement are not valid;
*                      2) the CSD sensing method is disabled for desired
*                         CY_CAPSENSE_SHIELD or CY_CAPSENSE_SENSOR states;
*                      3) the CSX sensing method is disabled for desired
*                         CY_CAPSENSE_TX_PIN or CY_CAPSENSE_RX_PIN states.
*
* \funcusage
*
* An example of using the Cy_CapSense_SetPinState() function to perform
* sensor state re-configuration:
* \snippet capsense/snippet/main.c snippet_Cy_CapSense_SetPinState
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_SetPinState_V2(
                uint32_t widgetId,
                uint32_t sensorElement,
                uint32_t state,
                const cy_stc_capsense_context_t * context)
{
    cy_capsense_status_t connState = CY_CAPSENSE_STATUS_BAD_PARAM;
    uint32_t eltdNum;
    uint32_t eltdIndex;
    uint32_t interruptState;
    cy_stc_capsense_pin_config_t const * ioPtr;
    cy_stc_capsense_widget_config_t const * ptrWdCfg = &context->ptrWdConfig[widgetId];
    cy_stc_capsense_electrode_config_t const * ptrSnsEltdConfig;

    if (context->ptrCommonConfig->numWd > widgetId)
    {
        /* Get number of electrodes within the widget */
        eltdNum = (uint32_t)ptrWdCfg->numCols + ptrWdCfg->numRows;

        if (eltdNum > sensorElement)
        {
            /* Set the pointer to the specified sensor element configuration structure */
            ptrSnsEltdConfig = &ptrWdCfg->ptrEltdConfig[sensorElement];
            /* Get number of electrode's pins and a pointer to the electrode's pin structure */
            eltdNum = ptrSnsEltdConfig->numPins;
            ioPtr = ptrSnsEltdConfig->ptrPin;
            /* Loop through all pins of the specified sensor electrode */
            for (eltdIndex = 0u; eltdIndex < eltdNum; eltdIndex++)
            {
                /* Reset HSIOM and PC registers */
                interruptState = Cy_SysLib_EnterCriticalSection();
                Cy_GPIO_SetHSIOM(ioPtr->pcPtr, (uint32_t)ioPtr->pinNumber, CY_CAPSENSE_HSIOM_SEL_GPIO);
                Cy_SysLib_ExitCriticalSection(interruptState);

                switch (state)
                {
                    case CY_CAPSENSE_GROUND:
                        interruptState = Cy_SysLib_EnterCriticalSection();
                        Cy_GPIO_SetDrivemode(ioPtr->pcPtr, (uint32_t)ioPtr->pinNumber, CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF);
                        Cy_GPIO_Clr(ioPtr->pcPtr, (uint32_t)ioPtr->pinNumber);
                        Cy_SysLib_ExitCriticalSection(interruptState);

                        connState = CY_CAPSENSE_STATUS_SUCCESS;
                        break;

                    case CY_CAPSENSE_HIGHZ:
                        interruptState = Cy_SysLib_EnterCriticalSection();
                        Cy_GPIO_SetDrivemode(ioPtr->pcPtr, (uint32_t)ioPtr->pinNumber, CY_CAPSENSE_DM_GPIO_ANALOG);
                        Cy_GPIO_Clr(ioPtr->pcPtr, (uint32_t)ioPtr->pinNumber);
                        Cy_SysLib_ExitCriticalSection(interruptState);

                        connState = CY_CAPSENSE_STATUS_SUCCESS;
                        break;

                    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
                        case CY_CAPSENSE_SENSOR:
                            /* Enable sensor */
                            Cy_CapSense_CSDConnectSns(ioPtr, context);
                            connState = CY_CAPSENSE_STATUS_SUCCESS;
                            break;

                    case CY_CAPSENSE_SHIELD:
                        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
                            Cy_CapSense_SsConfigPinRegisters(ioPtr->pcPtr, (uint32_t)ioPtr->pinNumber,
                                    CY_CAPSENSE_DM_SHIELD, CY_CAPSENSE_HSIOM_SEL_CSD_SHIELD);
                            connState = CY_CAPSENSE_STATUS_SUCCESS;
                        #endif
                        break;
                    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

                    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
                        case CY_CAPSENSE_TX_PIN:
                            Cy_CapSense_SsConfigPinRegisters(ioPtr->pcPtr, (uint32_t)ioPtr->pinNumber,
                                    CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF, CY_CAPSENSE_HSIOM_SEL_CSD_SHIELD);
                            connState = CY_CAPSENSE_STATUS_SUCCESS;
                            break;

                        case CY_CAPSENSE_RX_PIN:
                            Cy_CapSense_SsConfigPinRegisters(ioPtr->pcPtr, (uint32_t)ioPtr->pinNumber,
                                    CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_HSIOM_SEL_AMUXA);
                            connState = CY_CAPSENSE_STATUS_SUCCESS;
                            break;
                    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

                    default:
                        /* No other sensor states */
                        break;
                }

                ioPtr++;
            }
        }
    }
    return (connState);
}


/*******************************************************************************
* Function Name: Cy_CapSense_SwitchSensingMode
****************************************************************************//**
*
* This function changes the mode for case when both CSD and CSX widgets are
* scanned.
*
* Once the function is called it performs the following tasks:
* 1. Releasing the CSD HW block by existing sensing method.
* 2. Configuring corresponding external capacitors and sensor pins into
*    default states.
* 3. Setting new mode.
* 4. Configuring HW to the new sensing mode.
*
* \param mode
* Specifies the scan mode:
* - CY_CAPSENSE_CSD_GROUP
* - CY_CAPSENSE_CSX_GROUP
* - CY_CAPSENSE_UNDEFINED_GROUP
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return status
* Returns the operation status:
* - CY_CAPSENSE_SUCCESS_E   - Indicates the successful mode switching or
*                             the CSD HW block is in the same mode as desired.
* - CY_CAPSENSE_HW_BUSY_E   - The CSD HW block is busy with previous operation.
* - CY_CAPSENSE_HW_LOCKED_E - The CSD HW block is captured by another middleware.
*
*******************************************************************************/
cy_en_capsense_return_status_t Cy_CapSense_SwitchSensingMode(uint8_t mode, cy_stc_capsense_context_t * context)
{
    cy_en_capsense_return_status_t switchStatus = CY_CAPSENSE_SUCCESS_E;

    if (context->ptrActiveScanSns->currentSenseMethod != mode)
    {
        /* Check the CSD HW lock status */
        if(CY_CSD_CAPSENSE_KEY == Cy_CSD_GetLockStatus(context->ptrCommonConfig->ptrCsdBase,
                                                       context->ptrCommonConfig->ptrCsdContext))
        {
            if (CY_CAPSENSE_NOT_BUSY == Cy_CapSense_IsBusy(context))
            {
                /* The requested mode differs from the current one. Disable the current mode. */
                switch(context->ptrActiveScanSns->currentSenseMethod)
                {
                #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
                    case CY_CAPSENSE_CSD_GROUP:
                        Cy_CapSense_CSDDisableMode(context);
                        break;
                #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

                #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
                    case CY_CAPSENSE_CSX_GROUP:
                        Cy_CapSense_CSXDisableMode(context);
                        break;
                #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

                #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_HW_GROUP_EN)
                    case CY_CAPSENSE_BIST_GROUP:
                            Cy_CapSense_BistDisableMode(context);
                        break;
                #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_HW_GROUP_EN) */
                    default:
                        /* No action for other sensing methods */
                        break;
                }

                context->ptrActiveScanSns->currentSenseMethod = mode;

                /* Enable the specified mode */
                switch(context->ptrActiveScanSns->currentSenseMethod)
                {
                #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
                    case CY_CAPSENSE_CSD_GROUP:
                        Cy_CapSense_CSDInitialize(context);
                        break;
                #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

                #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
                    case CY_CAPSENSE_CSX_GROUP:
                        Cy_CapSense_CSXInitialize(context);
                        break;
                #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

                #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN)
                    case CY_CAPSENSE_BIST_GROUP:
                        Cy_CapSense_BistInitialize(context);
                        break;
                #endif

                    default:
                        /* No action for other sensing methods */
                        break;
                    }
            }
            else
            {
                switchStatus = CY_CAPSENSE_HW_BUSY_E;
            }
        }
        else
        {
            switchStatus = CY_CAPSENSE_HW_LOCKED_E;
        }
    }

    return (switchStatus);
}


/*******************************************************************************
* Function Name: Cy_CapSense_SetIOsInDesiredState
****************************************************************************//**
*
* Sets all CAPSENSE&trade; pins into a desired state.
*
* Sets all the CSD/CSX IOs into a desired state.
* Default state:
* - HSIOM   - Disconnected, the GPIO mode.
* - DM      - Strong drive.
* - State   - Zero.
*
* Do not call this function directly from the application program.
*
* \param desiredDriveMode
* Specifies the desired pin control port (PC) configuration.
*
* \param desiredPinOutput
* Specifies the desired pin output data register (DR) state.
*
* \param desiredHsiom
* Specifies the desired pin HSIOM state.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_SetIOsInDesiredState(
                uint32_t desiredDriveMode,
                uint32_t desiredPinOutput,
                en_hsiom_sel_t desiredHsiom,
                const cy_stc_capsense_context_t * context)
{
    uint32_t loopIndex;
    const cy_stc_capsense_pin_config_t * ptrPinCfg = context->ptrPinConfig;

    /* Loop through all electrodes */
    for (loopIndex = 0u; loopIndex < context->ptrCommonConfig->numPin; loopIndex++)
    {
        Cy_CapSense_SsConfigPinRegisters(ptrPinCfg->pcPtr, (uint32_t)ptrPinCfg->pinNumber, desiredDriveMode, desiredHsiom);
        if (0u != desiredPinOutput)
        {
            Cy_GPIO_Set(ptrPinCfg->pcPtr, (uint32_t)ptrPinCfg->pinNumber);
        }
        else
        {
            Cy_GPIO_Clr(ptrPinCfg->pcPtr, (uint32_t)ptrPinCfg->pinNumber);
        }

        /* Get next electrode */
        ptrPinCfg++;
    }
}


/*******************************************************************************
* Function Name: Cy_CapSense_SetSpecificIOsInDefaultState
****************************************************************************//**
*
* Sets specific CAPSENSE&trade; pins into a default state.
*
* Sets all external capacitors and shield electrodes into the default state:
* - HSIOM   - Disconnected, the GPIO mode.
* - DM      - High-Z Analog.
*
* Do not call this function directly from the application program.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_SetSpecificIOsInDefaultState(const cy_stc_capsense_context_t * context)
{
    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
        /* Cmod pin to default state */
        Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCmod, (uint32_t)context->ptrCommonConfig->pinCmod, CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_HSIOM_SEL_GPIO);

        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
            /* Disconnect shields */
            Cy_CapSense_CSDDisableShieldElectrodes(context);

            #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_CAP_EN)
                /* Csh pin to default state */
                Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCsh, (uint32_t)context->ptrCommonConfig->pinCsh, CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_HSIOM_SEL_GPIO);
            #endif
        #endif
    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
        /* CintA pin to default state */
        Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCintA, (uint32_t)context->ptrCommonConfig->pinCintA, CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_HSIOM_SEL_GPIO);

        /* CintB pin to default state */
        Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCintB, (uint32_t)context->ptrCommonConfig->pinCintB, CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_HSIOM_SEL_GPIO);
    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */
}


/*******************************************************************************
* Function Name: Cy_CapSense_SsPostAllWidgetsScan
****************************************************************************//**
*
* Configures and triggers the scan of the next widget if queue is not empty.
* This function should not be used by the application program.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_SsPostAllWidgetsScan(cy_stc_capsense_context_t * context)
{
    /*
    * 1. Increment widget index
    * 2. Check whether all the widgets are scanned
    * 3. If all the widgets are not scanned, set up and scan next widget
    */
    cy_capsense_status_t postScanStatus;
    const cy_stc_active_scan_sns_t * ptrActive = context->ptrActiveScanSns;
    uint32_t widgetId = (uint32_t)ptrActive->widgetIndex + 1u;

    do
    {
        if (context->ptrCommonConfig->numWd > widgetId)
        {
            /* Set up the next widget */
            context->ptrCommonContext->status = 0u;
            postScanStatus = Cy_CapSense_SetupWidget(widgetId, context);
            if (CY_CAPSENSE_STATUS_SUCCESS == postScanStatus)
            {
                (void)Cy_CapSense_Scan(context);
            }
            else
            {
                /* The next widget is not available for scanning. Skip it. */
                widgetId++;
            }
        }
        else
        {
            /* All the widgets are scanned. Reset BUSY flag. */
            Cy_CapSense_ClrBusyFlags(context);

            /* Set postScanStatus to exit the while loop */
            postScanStatus = CY_CAPSENSE_STATUS_SUCCESS;
        }
    } while (CY_CAPSENSE_STATUS_SUCCESS != postScanStatus);
}


/*******************************************************************************
* Function Name: Cy_CapSense_InterruptHandler_V2
****************************************************************************//**
*
* Implements interrupt service routine for CAPSENSE&trade; Middleware.
*
* The CSD HW block generates an interrupt at end of every sensor scan.
* The CAPSENSE&trade; middleware uses this interrupt to implement a
* non-blocking sensor scan method, in which only the first sensor scan is
* initiated by the application program and subsequent sensor scans are
* initiated in the interrupt service routine as soon as the current scan
* is completed. The above stated interrupt service routine is implemented
* as a part of the CAPSENSE&trade; middleware.
*
* The CAPSENSE&trade; middleware does not initialize or modify the priority
* of interrupts. For the operation of middleware, the application program
* must configure CSD interrupt and assign interrupt vector to
* the Cy_CapSense_InterruptHandler() function. Refer to function
* usage example for details.
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
*
* \param base
* The pointer to the base register address of the CSD HW block.
* This argument is kept for uniformity and backward compatibility
* and is not used. The function can be called with value NULL.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* The calls of the Start Sample and End Of Scan callbacks
* (see the \ref group_capsense_callbacks section for details) are the part of the
* Cy_CapSense_InterruptHandler() routine and they lengthen its execution. These
* callbacks will lengthen the CSD ISR execution in case of a direct call of the
* Cy_CapSense_InterruptHandler() function from a CSD ISR.
*
* \funcusage
*
* An example of the ISR initialization:
*
* The CapSense_ISR_cfg variable should be declared by the application
* program according to the examples below:<br>
* For Core CM0+:
* \snippet capsense/snippet/main.c snippet_m0p_capsense_interrupt_source_declaration
*
* For Core CM4:
* \snippet capsense/snippet/main.c snippet_m4_capsense_interrupt_source_declaration
*
* The CAPSENSE&trade; interrupt handler should be defined by the application program
* according to the example below:
* \snippet capsense/snippet/main.c snippet_Cy_CapSense_IntHandler
*
* Then, the application program should configure and enable the CSD block interrupt
* between calls of the Cy_CapSense_Init() and Cy_CapSense_Enable() functions:
* \snippet capsense/snippet/main.c snippet_Cy_CapSense_Initialization
*
* CapSense_HW is the pointer to the base register address of
* the CSD HW block. A macro for the pointer can be found in the cycfg_peripherals.h
* file defined as \<Csd_Personality_Name\>_HW. If no name specified,
* the default name is used csd_\<Block_Number\>_csd_\<Block_Number\>_HW.
*
* An example of sharing the CSD HW block by the CAPSENSE&trade; and CSDADC middleware.<br>
* Declares the CapSense_ISR_cfg variable:
* \snippet capsense/snippet/main.c snippet_m4_capsense_interrupt_source_declaration
*
* Declares the CSDADC_ISR_cfg variable:
* \snippet capsense/snippet/main.c snippet_m4_adc_interrupt_source_declaration
*
* Defines the CAPSENSE&trade; interrupt handler:
* \snippet capsense/snippet/main.c snippet_CapSense_Interrupt
*
* Defines the CSDADC interrupt handler:
* \snippet capsense/snippet/main.c snippet_CSDADC_Interrupt
*
* The part of the main.c FW flow:
* \snippet capsense/snippet/main.c snippet_Cy_CapSense_TimeMultiplex
*
*******************************************************************************/
void Cy_CapSense_InterruptHandler_V2(const CSD_Type * base, cy_stc_capsense_context_t * context)
{
    (void)base;
    context->ptrInternalContext->ptrISRCallback((void *)context);
}


#if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CALIBRATION_EN) || \
     (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN))
/*******************************************************************************
* Function Name: Cy_CapSense_CalibrateWidget_V2
****************************************************************************//**
*
* Executes the IDAC calibration for all the sensors in the specified widget
* to the default target value.
*
* This function performs exactly the same tasks as
* Cy_CapSense_CalibrateAllWidgets(), but only for a specified widget.
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
*
* \param widgetId
* Specifies the ID number of the widget. A macro for the widget ID can be found
* in the cycfg_capsense.h file defined as CY_CAPSENSE_<WIDGET_NAME>_WDGT_ID.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the specified widget calibration:
* - CY_CAPSENSE_STATUS_SUCCESS - The operation is successfully completed.
* - CY_CAPSENSE_STATUS_BAD_PARAM - The input parameter is invalid.
* - CY_CAPSENSE_STATUS_BAD_DATA - The calibration failed and the middleware may not
* operate as expected.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_CalibrateWidget_V2(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context)
{
    cy_capsense_status_t calibrateStatus = CY_CAPSENSE_STATUS_BAD_PARAM;

    if(context->ptrCommonConfig->numWd > widgetId)
    {
        switch(context->ptrWdConfig[widgetId].senseMethod)
        {
        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CALIBRATION_EN)
            case CY_CAPSENSE_CSD_GROUP:
                calibrateStatus = Cy_CapSense_CSDCalibrateWidget(
                        widgetId, (uint32_t)context->ptrCommonConfig->csdRawTarget, context);
                break;
        #endif

        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN)
            case CY_CAPSENSE_CSX_GROUP:
                calibrateStatus = Cy_CapSense_CSXCalibrateWidget(
                        widgetId, (uint32_t)context->ptrCommonConfig->csxRawTarget, context);
                break;
        #endif

            default:
                /* No action for other methods */
                break;
        }
    }

    /* Update CRC if BIST is enabled */
    #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) &&\
         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN))
        Cy_CapSense_UpdateCrcWidget(widgetId, context);
    #endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) &&
               (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN)) */

    return calibrateStatus;
}


/*******************************************************************************
* Function Name: Cy_CapSense_CalibrateAllWidgets_V2
****************************************************************************//**
*
* Executes the IDAC calibration for all the sensors in all widgets in
* the middleware to default target value.
*
* This function detects the sensing method used by each widget and performs
* a successive approximation search algorithm to find the appropriate modulator
* and compensation IDAC (if enabled) values for all sensors in CSD widgets
* and/or IDAC values for all sensors in CSX widgets to make sensor raw count
* to the default value level.
*
* Calibration returns CY_CAPSENSE_STATUS_BAD_DATA if resulted raw count is outside
* the limits.
*
* This function could be used only if Enable IDAC auto-calibration parameter
* is enabled for CSD and/or CSX widgets.
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the calibration process:
* - CY_CAPSENSE_STATUS_SUCCESS  - The operation is successfully completed.
* - CY_CAPSENSE_STATUS_BAD_DATA - The calibration failed and the middleware may not
*                     operate as expected.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_CalibrateAllWidgets_V2(cy_stc_capsense_context_t * context)
{
    cy_capsense_status_t calibrateStatus = CY_CAPSENSE_STATUS_SUCCESS;
    uint32_t wdgtIndex;

    for (wdgtIndex = 0u; wdgtIndex < context->ptrCommonConfig->numWd; wdgtIndex++)
    {
        calibrateStatus |= Cy_CapSense_CalibrateWidget(wdgtIndex, context);
    }

    return calibrateStatus;
}
#endif


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CALIBRATION_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_CalibrateAllCsdWidgets
****************************************************************************//**
*
* Executes the IDAC calibration for all the sensors in CSD widgets to
* the default target value.
*
* \deprecated This function is obsolete and kept for backward compatibility only.
* The Cy_CapSense_CalibrateAllWidgets() function should be used instead.
*
* This function performs exact same tasks of Cy_CapSense_CalibrateAllWidgets(),
* but only for CSD widgets.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the operation:
* - Zero     - All the widgets are calibrated successfully.
* - Non-zero - Calibration failed for at least one widget.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_CalibrateAllCsdWidgets(cy_stc_capsense_context_t * context)
{
    uint32_t widgetId;
    cy_capsense_status_t calibrateStatus = CY_CAPSENSE_STATUS_SUCCESS;

    for(widgetId = 0uL; widgetId < context->ptrCommonConfig->numWd; widgetId++)
    {
        if(CY_CAPSENSE_CSD_GROUP == context->ptrWdConfig[widgetId].senseMethod)
        {
            calibrateStatus |= Cy_CapSense_CSDCalibrateWidget(
                    widgetId, (uint32_t)context->ptrCommonConfig->csdRawTarget, context);
            /* Update CRC if BIST is enabled */
            #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) &&\
                 (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN))
                Cy_CapSense_UpdateCrcWidget(widgetId, context);
            #endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) &&
                       (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN)) */
        }
    }

    return(calibrateStatus);
}
#endif


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_CalibrateAllCsxWidgets
****************************************************************************//**
*
* Executes the IDAC calibration for all the sensors in CSX widgets to
* the default target value.
*
* \deprecated This function is obsolete and kept for backward compatibility only.
* The Cy_CapSense_CalibrateAllWidgets() function should be used instead.
*
* This function performs the exact same tasks of Cy_CapSense_CalibrateAllWidgets(),
* but only for CSX widgets.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the operation:
* - Zero     - All the widgets are calibrated successfully.
* - Non-zero - Calibration failed for at least one widget.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_CalibrateAllCsxWidgets(cy_stc_capsense_context_t * context)
{
    uint32_t widgetId;
    cy_capsense_status_t calibrateStatus = CY_CAPSENSE_STATUS_SUCCESS;

    for(widgetId = 0uL; widgetId < context->ptrCommonConfig->numWd; widgetId++)
    {
        if(CY_CAPSENSE_CSX_GROUP == context->ptrWdConfig[widgetId].senseMethod)
        {
            calibrateStatus |= Cy_CapSense_CSXCalibrateWidget(
                    widgetId, (uint32_t)context->ptrCommonConfig->csxRawTarget, context);
            /* Update CRC if BIST is enabled */
            #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) &&\
                       (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN))
                Cy_CapSense_UpdateCrcWidget(widgetId, context);
            #endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) &&
                       (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN)) */
        }
    }

    return(calibrateStatus);

}
#endif


#if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_SMARTSENSE_FULL_EN) || \
     (CY_CAPSENSE_ENABLE == CY_CAPSENSE_SMARTSENSE_HW_EN))
/*******************************************************************************
* Function Name: Cy_CapSense_SsAutoTune
****************************************************************************//**
*
* Performs the parameters auto-tuning for the optimal CAPSENSE&trade; operation when
* smart sensing algorithm is enabled.
*
* This function performs the following tasks:
* - Calibrate Modulator and Compensation IDACs.
* - Tune the Sense Clock optimal value to get a Sense Clock period greater
*   than 2*5*R*Cp.
* - Calculate the resolution for the optimal finger capacitance.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the operation:
* - Zero     - All the widgets are auto-tuned successfully.
* - Non-zero - Auto-tuning failed for any widget.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_SsAutoTune(cy_stc_capsense_context_t * context)
{
    cy_capsense_status_t autoTuneStatus = CY_CAPSENSE_STATUS_SUCCESS;
    uint32_t wdIndex;

    for (wdIndex = 0u; wdIndex < context->ptrCommonConfig->numWd; wdIndex++)
    {
        if (CY_CAPSENSE_CSD_GROUP == context->ptrWdConfig[wdIndex].senseMethod)
        {
            autoTuneStatus |= Cy_CapSense_SsAutoTuneWidget(wdIndex, context);
        }
    }

    return autoTuneStatus;
}


/*******************************************************************************
* Function Name: Cy_CapSense_SsAutoTuneWidget
****************************************************************************//**
*
* Performs the parameters auto-tuning for the optimal CAPSENSE&trade; operation when
* smart sensing algorithm is enabled.
*
* This function performs the following tasks:
* - Calibrate Modulator and Compensation IDACs.
* - Tune the Sense Clock optimal value to get a Sense Clock period greater
*   than 2*5*R*Cp.
* - Calculate the resolution for the optimal finger capacitance.
*
* \param widgetId
* Specifies the ID number of the widget. A macro for the widget ID can be found
* in the cycfg_capsense.h file defined as CY_CAPSENSE_<WIDGET_NAME>_WDGT_ID.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the operation:
* - Zero     - All the widgets are auto-tuned successfully.
* - Non-zero - Auto-tuning failed.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_SsAutoTuneWidget(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context)
{
    cy_capsense_status_t autoTuneStatus = CY_CAPSENSE_STATUS_SUCCESS;

    uint32_t snsIndex;
    uint32_t inputSnsClk;
    uint32_t minSnsClkDiv;
    uint32_t snsClkSourceAuto;

    cy_stc_capsense_auto_tune_config_t autoTuneConfig;

    uint32_t maxRaw = 0u;
    uint32_t maxCp = 0u;
    uint32_t maxIdacComp = 0u;

    const cy_stc_capsense_widget_config_t * ptrWdCfg = &context->ptrWdConfig[widgetId];
    cy_stc_capsense_widget_context_t * ptrWdCxt = ptrWdCfg->ptrWdContext;
    const cy_stc_capsense_sensor_context_t * ptrSnsCtx;

    #if((CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_MATRIX_EN) ||\
        (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_TOUCHPAD_EN))
        uint32_t maxCpSnsId = 0u;
        uint32_t maxCpRowSnsId = 0u;
    #endif

    /* Store sense clock source to be restored at the end of function */
    snsClkSourceAuto = ptrWdCxt->snsClkSource;

    /* Find input of sensor clock frequency */
    inputSnsClk = context->ptrCommonConfig->periClkHz /
                    context->ptrCommonContext->modCsdClk /
                    CY_CAPSENSE_CSD_AUTOTUNE_CAL_UNITS;

    minSnsClkDiv = context->ptrCommonConfig->periClkHz /
                    context->ptrCommonContext->modCsdClk /
                    CY_CAPSENSE_CSD_SNS_FREQ_KHZ_MAX;
    if (CY_CAPSENSE_MIN_SNS_CLK_DIVIDER > minSnsClkDiv)
    {
        minSnsClkDiv = CY_CAPSENSE_MIN_SNS_CLK_DIVIDER;
    }
    minSnsClkDiv = (minSnsClkDiv + (CY_CAPSENSE_CSD_AUTOTUNE_CAL_UNITS - 1u)) / CY_CAPSENSE_CSD_AUTOTUNE_CAL_UNITS;
    /* Make divider even */
    if (0u != (minSnsClkDiv & 0x01u))
    {
        minSnsClkDiv++;
    }

    /* Initialize auto-tuning configuration structure */
    autoTuneConfig.snsClkInputClock = (uint16_t)inputSnsClk;
    autoTuneConfig.snsClkConstantR = context->ptrCommonConfig->csdRConst;
    autoTuneConfig.vRef = context->ptrInternalContext->csdVrefVoltageMv;
    autoTuneConfig.fingerCap = ptrWdCxt->fingerCap;
    autoTuneConfig.sigPFC = &(ptrWdCxt->sigPFC);

    /*
    * Autotune phase #1:
    * - performing the first calibration at fixed settings
    * - getting maximum sensor Cp
    * - getting sense clock frequency based on Cp
    */

    ptrWdCxt->resolution = CY_CAPSENSE_AUTOTUNE_CALIBRATION_RESOLUTION;
    ptrWdCxt->maxRawCount = (uint16_t)(0x01uL << CY_CAPSENSE_AUTOTUNE_CALIBRATION_RESOLUTION) - 1u;
    ptrWdCxt->snsClkSource = CY_CAPSENSE_CLK_SOURCE_DIRECT;
    ptrWdCxt->snsClk = (uint16_t)(inputSnsClk / CY_CAPSENSE_AUTOTUNE_CALIBRATION_FREQ_KHZ);
    ptrWdCxt->rowSnsClk = ptrWdCxt->snsClk;

    /* Calibrate CSD widget to the default calibration target */
    (void)Cy_CapSense_CSDCalibrateWidget(widgetId,
                                         (uint32_t)context->ptrCommonConfig->csdRawTarget,
                                         context);

    /* Find raw count and IDAC of a sensor with maximum Cp */
    ptrSnsCtx = ptrWdCfg->ptrSnsContext;

    #if(CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_IDAC_COMP_EN)
        for (snsIndex = 0u; snsIndex < ptrWdCfg->numCols; snsIndex++)
        {
            if (maxIdacComp < ptrSnsCtx->idacComp)
            {
                #if((CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_MATRIX_EN) ||\
                    (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_TOUCHPAD_EN))
                    maxCpSnsId = snsIndex;
                #endif
                maxIdacComp = ptrSnsCtx->idacComp;
                maxRaw = ptrSnsCtx->raw;
            }
            ptrSnsCtx++;
        }
    #else
        for (snsIndex = 0u; snsIndex < ptrWdCfg->numCols; snsIndex++)
        {
            if (maxRaw < ptrSnsCtx->raw)
            {
                #if((CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_MATRIX_EN) ||\
                    (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_TOUCHPAD_EN))
                    maxCpSnsId = snsIndex;
                #endif
                maxRaw = ptrSnsCtx->raw;
            }
            ptrSnsCtx++;
        }
    #endif

    /* Update auto-tuning configuration structure */
    autoTuneConfig.iDacMod = ptrWdCxt->idacMod[CY_CAPSENSE_MFS_CH0_INDEX];
    autoTuneConfig.iDacComp = (uint8_t)maxIdacComp;
    autoTuneConfig.iDacGain = context->ptrCommonConfig->idacGainTable[ptrWdCxt->idacGainIndex].gainValue;
    autoTuneConfig.ptrSenseClk = &ptrWdCxt->snsClk;
    autoTuneConfig.calTarget = (uint16_t)((maxRaw * CY_CAPSENSE_CSD_AUTOTUNE_CAL_UNITS) /
            ((uint32_t)(0x01uL << CY_CAPSENSE_AUTOTUNE_CALIBRATION_RESOLUTION) - 1u));

    /* Find sensor Cp and optimum sense clock value */
    maxCp = Cy_CapSense_TunePrescalers_Lib(&autoTuneConfig);
    autoTuneConfig.sensorCap = maxCp;

    /* Increase sensor clock divider to valid value */
    if (((uint32_t)ptrWdCxt->snsClk) < minSnsClkDiv)
    {
        ptrWdCxt->snsClk = (uint16_t)minSnsClkDiv;
    }

    #if((CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_MATRIX_EN) ||\
        (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_TOUCHPAD_EN))
        if (((uint8_t)CY_CAPSENSE_WD_TOUCHPAD_E == ptrWdCfg->wdType) ||
            ((uint8_t)CY_CAPSENSE_WD_MATRIX_BUTTON_E == ptrWdCfg->wdType))
        {
            /* Find a sensor with maximum Cp */
            maxRaw = 0u;
            maxIdacComp = 0u;

            #if(CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_IDAC_COMP_EN)
                for (snsIndex = 0u; snsIndex < ptrWdCfg->numCols; snsIndex++)
                {
                    if (maxIdacComp < ptrSnsCtx->idacComp)
                    {
                        maxCpRowSnsId = snsIndex;
                        maxIdacComp = ptrSnsCtx->idacComp;
                        maxRaw = ptrSnsCtx->raw;
                    }
                    ptrSnsCtx++;
                }
            #else
                for (snsIndex = 0u; snsIndex < ptrWdCfg->numCols; snsIndex++)
                {
                    if (maxRaw < ptrSnsCtx->raw)
                    {
                        maxCpRowSnsId = snsIndex;
                        maxRaw = ptrSnsCtx->raw;
                    }
                    ptrSnsCtx++;
                }
            #endif

            /* Configure auto-tuning configuration structure */
            autoTuneConfig.iDacMod = ptrWdCxt->rowIdacMod[CY_CAPSENSE_MFS_CH0_INDEX];
            autoTuneConfig.iDacComp = (uint8_t)maxIdacComp;
            autoTuneConfig.ptrSenseClk = &ptrWdCxt->rowSnsClk;
            autoTuneConfig.calTarget = (uint16_t)((maxRaw * CY_CAPSENSE_CSD_AUTOTUNE_CAL_UNITS) /
                    ((uint32_t)(0x01uL << CY_CAPSENSE_AUTOTUNE_CALIBRATION_RESOLUTION) - 1u));

            /* Find correct sense clock value */
            maxCp = Cy_CapSense_TunePrescalers_Lib(&autoTuneConfig);
            /* Save maximum sensor Cp and corresponding sensor Id */
            if (autoTuneConfig.sensorCap < maxCp)
            {
                autoTuneConfig.sensorCap = maxCp;
                maxCpSnsId = maxCpRowSnsId;
            }

            /* Increase sensor clock divider to valid value */
            if (((uint32_t)ptrWdCxt->rowSnsClk) < minSnsClkDiv)
            {
                ptrWdCxt->rowSnsClk = (uint16_t)minSnsClkDiv;
            }
        }
    #endif /* ((CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_MATRIX_EN) ||
               (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_TOUCHPAD_EN)) */

    /* Check tuning results */
    if (CY_CAPSENSE_AUTOTUNE_CP_MAX < maxCp)
    {
        autoTuneStatus = CY_CAPSENSE_STATUS_BAD_DATA;
    }

    /*
    * Autotune phase #2:
    * - repeating calibration with new sense clock frequency
    * - getting resolution
    */

    /* Calibrate CSD widget to the default calibration target with newly defined sense frequency */
    (void)Cy_CapSense_CSDCalibrateWidget(widgetId,
                                         (uint32_t)context->ptrCommonConfig->csdRawTarget,
                                         context);

    autoTuneConfig.iDacGain = context->ptrCommonConfig->idacGainTable[ptrWdCxt->idacGainIndex].gainValue;
    autoTuneConfig.iDacMod = ptrWdCxt->idacMod[CY_CAPSENSE_MFS_CH0_INDEX];
    autoTuneConfig.ptrSenseClk = &ptrWdCxt->snsClk;

    #if((CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_MATRIX_EN) ||\
        (CY_CAPSENSE_DISABLE != CY_CAPSENSE_CSD_TOUCHPAD_EN))
        if (((uint8_t)CY_CAPSENSE_WD_TOUCHPAD_E == ptrWdCfg->wdType) ||
            ((uint8_t)CY_CAPSENSE_WD_MATRIX_BUTTON_E == ptrWdCfg->wdType))
        {
            if (maxCpSnsId >= ptrWdCfg->numCols)
            {
                autoTuneConfig.iDacMod = ptrWdCxt->rowIdacMod[CY_CAPSENSE_MFS_CH0_INDEX];
                autoTuneConfig.ptrSenseClk = &ptrWdCxt->rowSnsClk;
            }
        }
    #endif

    /* Find resolution */
    ptrWdCxt->resolution = Cy_CapSense_TuneSensitivity_Lib(&autoTuneConfig);
    ptrWdCxt->maxRawCount = (uint16_t)(0x01uL << ptrWdCxt->resolution) - 1u;


    /*
    * Autotune phase #3:
    * - selecting a widget clock source if AUTO
    * - repeating calibration with found clock frequency, resolution and clock source
    * - updating sensitivity
    */

    /* Update clock source */
    ptrWdCxt->snsClkSource = (uint8_t)snsClkSourceAuto;
    Cy_CapSense_CSDSetWidgetSenseClkSrc(ptrWdCfg);

    /* Calibrate CSD widget to the default calibration target with newly defined resolution */
    autoTuneStatus |= Cy_CapSense_CSDCalibrateWidget(widgetId,
                                                     (uint32_t)context->ptrCommonConfig->csdRawTarget,
                                                     context);
    /* Update CRC if BIST is enabled */
    #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) &&\
         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN))
        Cy_CapSense_UpdateCrcWidget(widgetId, context);
    #endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) &&
               (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN)) */

    return autoTuneStatus;
}
#endif


/*******************************************************************************
* Function Name: Cy_CapSense_InitializeSourceSenseClk
****************************************************************************//**
*
* Sets a source for Sense/Tx clock for all widgets.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_InitializeSourceSenseClk(const cy_stc_capsense_context_t * context)
{
    uint32_t wdIndex;
    const cy_stc_capsense_widget_config_t * ptrWdCfg = context->ptrWdConfig;

    for (wdIndex = 0u; wdIndex < context->ptrCommonConfig->numWd; wdIndex++)
    {
        switch(ptrWdCfg->senseMethod)
        {
        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
            case CY_CAPSENSE_CSD_GROUP:
                Cy_CapSense_CSDSetWidgetSenseClkSrc(ptrWdCfg);
                break;
        #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
            case CY_CAPSENSE_CSX_GROUP:
                Cy_CapSense_CSXSetWidgetTxClkSrc(ptrWdCfg);
                break;
        #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

            default:
                /* No action for other methods */
                break;
        }
        /* Switch to the next widget */
        ptrWdCfg++;
    }
}


/*******************************************************************************
* Function Name: Cy_CapSense_SsCalcLfsrSize
****************************************************************************//**
*
* Finds a SSC polynomial size when clock source is configured to Auto mode.
*
* The SSC polynomial size in the auto mode is found based on the following
* requirements:
* - an LFSR value should be selected so that the max clock dither
*   is limited with +/-10%.
* - at least one full spread spectrum polynomial should pass during
*   the scan time.
* - the value of the number of conversions should be an integer multiple
*   of the repeat period of the programmed LFSR_SIZE.
*
* \param clkDivider
* The divider value for the sense/Tx clock.
*
* \param conversionsNum
* The widget conversion number.
*
* \return
* Returns the size of LFSR value for the SENSE_PERIOD register.
*
*******************************************************************************/
uint32_t Cy_CapSense_SsCalcLfsrSize(uint32_t clkDivider, uint32_t conversionsNum)
{
    uint32_t lfsrSize = 0u;

    if(CY_CAPSENSE_SNSCLK_LFSR_THRESHOLD <= clkDivider)
    {
        /* Find LFSR value */
        if((CY_CAPSENSE_SNSCLK_SSC4_PERIOD <= conversionsNum) &&
           (0uL == (conversionsNum % CY_CAPSENSE_SNSCLK_SSC4_PERIOD)))
        {
            lfsrSize = CY_CAPSENSE_CLK_SOURCE_SSC10;
        }
        else if((CY_CAPSENSE_SNSCLK_SSC3_PERIOD <= conversionsNum) &&
                (0uL == (conversionsNum % CY_CAPSENSE_SNSCLK_SSC3_PERIOD)))
        {
            lfsrSize = CY_CAPSENSE_CLK_SOURCE_SSC9;
        }
        else if((CY_CAPSENSE_SNSCLK_SSC2_PERIOD <= conversionsNum) &&
                (0uL == (conversionsNum % CY_CAPSENSE_SNSCLK_SSC2_PERIOD)))
        {
            lfsrSize = CY_CAPSENSE_CLK_SOURCE_SSC7;
        }
        else if((CY_CAPSENSE_SNSCLK_SSC1_PERIOD <= conversionsNum) &&
                (0uL == (conversionsNum % CY_CAPSENSE_SNSCLK_SSC1_PERIOD)))
        {
            lfsrSize = CY_CAPSENSE_CLK_SOURCE_SSC6;
        }
        else
        {
            lfsrSize = CY_CAPSENSE_CLK_SOURCE_DIRECT;
        }
    }

    return lfsrSize;
}


/*******************************************************************************
* Function Name: Cy_CapSense_DischargeExtCapacitors
****************************************************************************//**
*
* Discharges available external capacitors.
*
* The function discharges available external capacitors by disconnecting them
* from an analog bus and configuring strong GPIO drive mode with 0.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_DischargeExtCapacitors(cy_stc_capsense_context_t * context)
{
    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
        uint32_t cmodPcReg = 0uL;
        en_hsiom_sel_t cmodHsiomReg = CY_CAPSENSE_HSIOM_SEL_GPIO;
    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
        uint32_t cintAPcReg = 0uL;
        uint32_t cintBPcReg = 0uL;
        en_hsiom_sel_t cintAHsiomReg = CY_CAPSENSE_HSIOM_SEL_GPIO;
        en_hsiom_sel_t cintBHsiomReg = CY_CAPSENSE_HSIOM_SEL_GPIO;
    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

    #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) && \
         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_CAP_EN))
        uint32_t cshPcReg = 0uL;
        en_hsiom_sel_t cshHsiomReg = CY_CAPSENSE_HSIOM_SEL_GPIO;
    #endif

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
        Cy_CapSense_SsReadPinRegisters(context->ptrCommonConfig->portCmod,
            (uint32_t)context->ptrCommonConfig->pinCmod, &cmodPcReg, &cmodHsiomReg);
        Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCmod,
            (uint32_t)context->ptrCommonConfig->pinCmod, CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF, CY_CAPSENSE_HSIOM_SEL_GPIO);
        Cy_GPIO_Clr(context->ptrCommonConfig->portCmod, (uint32_t)context->ptrCommonConfig->pinCmod);

        #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) && \
             (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_CAP_EN))
            Cy_CapSense_SsReadPinRegisters(context->ptrCommonConfig->portCsh,
                (uint32_t)context->ptrCommonConfig->pinCsh, &cshPcReg, &cshHsiomReg);
            Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCsh,
                (uint32_t)context->ptrCommonConfig->pinCsh, CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF, CY_CAPSENSE_HSIOM_SEL_GPIO);
            Cy_GPIO_Clr(context->ptrCommonConfig->portCsh, (uint32_t)context->ptrCommonConfig->pinCsh);
        #endif
    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
        Cy_CapSense_SsReadPinRegisters(context->ptrCommonConfig->portCintA,
            (uint32_t)context->ptrCommonConfig->pinCintA, &cintAPcReg, &cintAHsiomReg);
        Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCintA,
            (uint32_t)context->ptrCommonConfig->pinCintA, CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF, CY_CAPSENSE_HSIOM_SEL_GPIO);
        Cy_GPIO_Clr(context->ptrCommonConfig->portCintA, (uint32_t)context->ptrCommonConfig->pinCintA);

        Cy_CapSense_SsReadPinRegisters(context->ptrCommonConfig->portCintB,
            (uint32_t)context->ptrCommonConfig->pinCintB, &cintBPcReg, &cintBHsiomReg);
        Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCintB,
            (uint32_t)context->ptrCommonConfig->pinCintB, CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF, CY_CAPSENSE_HSIOM_SEL_GPIO);
        Cy_GPIO_Clr(context->ptrCommonConfig->portCintB, (uint32_t)context->ptrCommonConfig->pinCintB);
    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

    Cy_SysLib_DelayUs(CY_CAPSENSE_EXT_CAP_DISCHARGE_TIME);

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
        Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCmod,
            (uint32_t)context->ptrCommonConfig->pinCmod, cmodPcReg, cmodHsiomReg);

        #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) && \
             (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_CAP_EN))
            Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCsh,
                (uint32_t)context->ptrCommonConfig->pinCsh, cshPcReg, cshHsiomReg);
        #endif
    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
        Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCintA,
            (uint32_t)context->ptrCommonConfig->pinCintA, cintAPcReg, cintAHsiomReg);

        Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCintB,
            (uint32_t)context->ptrCommonConfig->pinCintB, cintBPcReg, cintBHsiomReg);
    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */
}


/*******************************************************************************
* Function Name: Cy_CapSense_InitActivePtr
****************************************************************************//**
*
* Initializes active scan sensor structure with all available
* pointers for further faster access to widget/sensor parameters.
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
void Cy_CapSense_InitActivePtr(
                uint32_t widgetId,
                uint32_t sensorId,
                cy_stc_capsense_context_t * context)
{
    Cy_CapSense_InitActivePtrWd(widgetId, context);
    Cy_CapSense_InitActivePtrSns(sensorId, context);
}


/*******************************************************************************
* Function Name: Cy_CapSense_InitActivePtrSns
****************************************************************************//**
*
* Initializes active scan sensor structure with pointers to sensor
* for further faster access to widget/sensor parameters.
*
* This function supposes that the Cy_CapSense_InitActivePtrWd() function
* is called before.
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
void  Cy_CapSense_InitActivePtrSns(
                uint32_t sensorId,
                cy_stc_capsense_context_t * context)
{
    cy_stc_active_scan_sns_t * ptrActive = context->ptrActiveScanSns;

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
        uint32_t numberRows;
        uint32_t numberCols;
    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

    ptrActive->mfsChannelIndex = 0u;
    switch(context->ptrActiveScanSns->currentSenseMethod)
    {
    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
        case CY_CAPSENSE_CSD_GROUP:
            ptrActive->sensorIndex = (uint16_t)sensorId;
            ptrActive->ptrEltdConfig = &ptrActive->ptrWdConfig->ptrEltdConfig[sensorId];
            ptrActive->ptrSnsContext = &ptrActive->ptrWdConfig->ptrSnsContext[sensorId];
            ptrActive->connectedSnsState = CY_CAPSENSE_SNS_DISCONNECTED;
            break;
    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
        case CY_CAPSENSE_CSX_GROUP:
            ptrActive->sensorIndex = (uint16_t)sensorId;
            ptrActive->ptrSnsContext = &ptrActive->ptrWdConfig->ptrSnsContext[sensorId];
            ptrActive->connectedSnsState = CY_CAPSENSE_SNS_DISCONNECTED;

            numberRows = ptrActive->ptrWdConfig->numRows;
            numberCols = ptrActive->ptrWdConfig->numCols;
            ptrActive->rxIndex = (uint8_t)numberCols;
            ptrActive->txIndex = (uint8_t)numberRows;
            ptrActive->ptrRxConfig = &ptrActive->ptrWdConfig->ptrEltdConfig[sensorId / numberRows];
            ptrActive->ptrTxConfig = &ptrActive->ptrWdConfig->ptrEltdConfig[numberCols + (sensorId % numberRows)];

            break;
    #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

        default:
            /* No action for other methods */
            break;
    }
}

/*******************************************************************************
* Function Name: Cy_CapSense_InitActivePtrWd
****************************************************************************//**
*
* Initializes active scan sensor structure with pointers to current widget
* for further faster access to widget/sensor parameters.
*
* This function does not update pointers to current sensor and the
* Cy_CapSense_InitActivePtrSns() function should be called after current one.
*
* \param widgetId
* Specifies the ID number of the widget. A macro for the widget ID can be found
* in the cycfg_capsense.h file defined as CY_CAPSENSE_<WIDGET_NAME>_WDGT_ID.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_InitActivePtrWd(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context)
{
    cy_stc_active_scan_sns_t * ptrActive = context->ptrActiveScanSns;

    ptrActive->widgetIndex = (uint8_t)widgetId;
    ptrActive->ptrWdConfig = &context->ptrWdConfig[widgetId];
    ptrActive->ptrWdContext = ptrActive->ptrWdConfig->ptrWdContext;
}


/*******************************************************************************
* Function Name: Cy_CapSense_SsConfigPinRegisters
****************************************************************************//**
*
* Configures drive mode and HSIOM state of a desired pin. The action
* is performed inside the critical section.
*
* \param base
* The pointer to the pin's port register base address.
*
* \param pinNum
* Position of the pin bit-field within the port register.
*
* \param dm
* Specifies drive mode of the pin.
*
* \param hsiom
* Specifies HSIOM state of the pin.
*
*******************************************************************************/
void Cy_CapSense_SsConfigPinRegisters(
                GPIO_PRT_Type * base,
                uint32_t pinNum,
                uint32_t dm,
                en_hsiom_sel_t hsiom)
{
    uint32_t interruptState = Cy_SysLib_EnterCriticalSection();
    if (CY_CAPSENSE_HSIOM_SEL_GPIO == hsiom)
    {
        Cy_GPIO_SetHSIOM(base, pinNum, hsiom);
        Cy_GPIO_SetDrivemode(base, pinNum, dm);
    }
    else
    {
        Cy_GPIO_SetDrivemode(base, pinNum, dm);
        Cy_GPIO_SetHSIOM(base, pinNum, hsiom);
    }
    Cy_SysLib_ExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Cy_CapSense_SsReadPinRegisters
****************************************************************************//**
*
* Reads drive mode and HSIOM registers of the specified pin.
*
* \param base
* The pointer to the pin's port register base address.
*
* \param pinNum
* Position of the pin bit-field within the port register.
*
* \param dm
* The pointer to the drive mode variable.
*
* \param hsiom
* The pointer to the HSIOM variable.
*
*
*******************************************************************************/
void Cy_CapSense_SsReadPinRegisters(GPIO_PRT_Type * base, uint32_t pinNum, uint32_t * dm, en_hsiom_sel_t * hsiom)
{
    uint32_t interruptState = Cy_SysLib_EnterCriticalSection();
    *dm = Cy_GPIO_GetDrivemode(base, pinNum);
    *hsiom = Cy_GPIO_GetHSIOM(base, pinNum);
    Cy_SysLib_ExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Cy_CapSense_SetClkDivider
****************************************************************************//**
*
* Sets the modulator clock and then starts it.
*
* Do not call this function directly from the application program.
*
* \param dividerValue
* The divider value for the modulator clock.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_SetClkDivider(
                uint32_t dividerValue,
                const cy_stc_capsense_context_t * context)
{
    uint32_t dividerIndex = (uint32_t)context->ptrCommonConfig->periDividerIndex;

    #if (0u != CY_CAPSENSE_PSOC6_FOURTH_GEN)
        cy_en_divider_types_t dividerType;
    #else
        cy_en_sysclk_divider_types_t dividerType;
    #endif

    switch(context->ptrCommonConfig->periDividerType)
    {
        case (uint8_t)CY_SYSCLK_DIV_8_BIT:
            dividerType = CY_SYSCLK_DIV_8_BIT;
            break;
        case (uint8_t)CY_SYSCLK_DIV_16_BIT:
            dividerType = CY_SYSCLK_DIV_16_BIT;
            break;
        case (uint8_t)CY_SYSCLK_DIV_16_5_BIT:
            dividerType = CY_SYSCLK_DIV_16_5_BIT;
            break;
        default:
            dividerType = CY_SYSCLK_DIV_24_5_BIT;
            break;
    }

    (void)Cy_SysClk_PeriphDisableDivider(dividerType, dividerIndex);

    if ((CY_SYSCLK_DIV_8_BIT == dividerType) || (CY_SYSCLK_DIV_16_BIT == dividerType))
    {
        (void)Cy_SysClk_PeriphSetDivider(dividerType, dividerIndex, dividerValue);
    }
    else
    {
        (void)Cy_SysClk_PeriphSetFracDivider(dividerType, dividerIndex, dividerValue, 0u);
    }
    (void)Cy_SysClk_PeriphEnableDivider(dividerType, dividerIndex);
}


/*******************************************************************************
* Function Name: Cy_CapSense_WatchdogCyclesNum
****************************************************************************//**
*
* Converts the specified time into number of CPU cycles.
*
* \param desiredTimeUs
* The time (delay) specified in us.
*
* \param cpuFreqMHz
* The CPU frequency in MHz.
*
* \param cyclesPerLoop
* The number of cycles per a loop.
*
*******************************************************************************/
uint32_t Cy_CapSense_WatchdogCyclesNum(
                uint32_t desiredTimeUs,
                uint32_t cpuFreqMHz,
                uint32_t cyclesPerLoop)
{
    uint32_t retVal;

    if(0uL != cyclesPerLoop)
    {
        retVal = (desiredTimeUs * cpuFreqMHz) / cyclesPerLoop;
    }
    else
    {
        retVal = 0xFFFFFFFFuL;
    }

    return(retVal);
}


/*******************************************************************************
* Function Name: Cy_CapSense_WaitForSeqIdle
****************************************************************************//**
*
* This internal function checks the state of the CSD HW sequencer. If the
* sequencer is switched to the IDLE state before the software timeout,
* the function returns a non-zero. If the software watchdog is triggered
* during the scan, the function returns zero.
*
* \param watchdogCycleNum
* A watchdog cycle number to check a timeout.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns watchdog counter. If it is equal to zero, it means timeout happened.
*
*******************************************************************************/
uint32_t Cy_CapSense_WaitForSeqIdle(
         uint32_t watchdogCycleNum,
         const cy_stc_capsense_context_t * context)
{
    uint32_t watchdogCounter = watchdogCycleNum;

    while((0u != (CY_CAPSENSE_CSD_SEQ_START_START_MSK &
        context->ptrCommonConfig->ptrCsdBase->SEQ_START)))
    {
        if(0uL == watchdogCounter)
        {
            break;
        }

        watchdogCounter--;
    }


    return (watchdogCounter);
}


/*******************************************************************************
* Function Name: Cy_CapSense_WaitEndOfScan
****************************************************************************//**
*
* This internal function checks for the scan status. If the scan ends before
* the software watchdog triggering, the function returns a non-zero watchdog
* cycles number. If the software watchdog triggers during the scan,
* the function returns zero.
*
* \param watchdogCycleNum
* A watchdog cycle number to check a timeout.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns watchdog counter. If it is equal to zero, it means timeout happened.
*
*******************************************************************************/
uint32_t Cy_CapSense_WaitEndOfScan(
         uint32_t watchdogCycleNum,
         const cy_stc_capsense_context_t * context)
{
    uint32_t watchdogCounter = watchdogCycleNum;

    while (((context->ptrCommonConfig->ptrCsdBase->INTR &
             CY_CAPSENSE_CSD_INTR_SAMPLE_MSK) == 0u) && (0u != watchdogCounter))
    {
        watchdogCounter--;
    }

    return (watchdogCounter);
}


#if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CALIBRATION_EN) || \
     (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN))
/*******************************************************************************
* Function Name: Cy_CapSense_CalibrateCheck
****************************************************************************//**
*
* Verifies that the calibrated widget meets the configured conditions.
*
* This function checks whether the raw count of each sensor of the specified widget
* is within the raw count range defined by raw count target and +/- calibration
* error.
*
* \param widgetId
* Specifies the ID number of the widget. A macro for the widget ID can be found
* in the cycfg_capsense.h file defined as CY_CAPSENSE_<WIDGET_NAME>_WDGT_ID.
*
* \param target
* The raw count target in percentage.
*
* \param senseMethod
* The widget sensing method.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_CalibrateCheck(
                uint32_t widgetId,
                uint32_t target,
                uint32_t senseMethod,
                const cy_stc_capsense_context_t * context)
{
    cy_capsense_status_t calibrateStatus = CY_CAPSENSE_STATUS_SUCCESS;
    uint32_t tmpRawcount;
    uint32_t snsIndex;
    uint32_t upperLimit;
    uint32_t lowerLimit;
    uint8_t calibrationError;
    const cy_stc_capsense_widget_config_t * ptrWdCfg = &context->ptrWdConfig[widgetId];
    const cy_stc_capsense_sensor_context_t * ptrChCxt = ptrWdCfg->ptrSnsContext;
    uint32_t freqChIndex;
    const cy_stc_capsense_sensor_context_t * ptrSnsCxt;

    /* Calculate acceptable raw count range based on the resolution, target and error */
    if(CY_CAPSENSE_CSD_GROUP == senseMethod)
    {
        tmpRawcount = (1uL << context->ptrWdContext[widgetId].resolution) - 1u;
        calibrationError = context->ptrCommonConfig->csdCalibrationError;
    }
    else
    {
        tmpRawcount = context->ptrWdContext[widgetId].maxRawCount;
        calibrationError = context->ptrCommonConfig->csxCalibrationError;
    }

    lowerLimit = 0u;

    if (target > calibrationError)
    {
        lowerLimit = target - calibrationError;
    }
    upperLimit = target + calibrationError;
    if (upperLimit > CY_CAPSENSE_PERCENTAGE_100)
    {
        upperLimit = CY_CAPSENSE_PERCENTAGE_100;
    }
    lowerLimit = (tmpRawcount * lowerLimit) / CY_CAPSENSE_PERCENTAGE_100;
    upperLimit = (tmpRawcount * upperLimit) / CY_CAPSENSE_PERCENTAGE_100;

    /* Check whether sensors' rawcount is in the defined range */
    for (freqChIndex = 0u; freqChIndex < CY_CAPSENSE_CONFIGURED_FREQ_NUM; freqChIndex++)
    {
        ptrSnsCxt = ptrChCxt;
        for(snsIndex = 0u; snsIndex < ptrWdCfg->numSns; snsIndex++)
        {
            tmpRawcount = ptrSnsCxt->raw;
            if ((tmpRawcount < lowerLimit) || (tmpRawcount > upperLimit))
            {
                calibrateStatus = CY_CAPSENSE_STATUS_BAD_DATA;
                break;
            }
            ptrSnsCxt++;
        }
        ptrChCxt += context->ptrCommonConfig->numSns;
    }

    return (calibrateStatus);
}
#endif /* ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CALIBRATION_EN) ||\
           (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN)) */


/*******************************************************************************
* Function Name: Cy_CapSense_GetVrefAutoMv
****************************************************************************//**
*
* Finds the optimal Vref value based on the VDDA voltage.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the recommended reference voltage based on the configuration.
*
*******************************************************************************/
uint32_t Cy_CapSense_GetVrefAutoMv(const cy_stc_capsense_context_t * context)
{
    uint32_t vddaMv = (uint32_t)context->ptrCommonConfig->vdda;
    uint32_t vrefHighVoltageMv;

    #if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
        if(vddaMv >= CY_CAPSENSE_VREF_RANGE_0)
        {
            vrefHighVoltageMv = CY_CAPSENSE_VREF_VALUE_0;
        }
        else if(vddaMv >= CY_CAPSENSE_VREF_RANGE_1)
        {
            vrefHighVoltageMv = CY_CAPSENSE_VREF_VALUE_1;
        }
        else if(vddaMv >= CY_CAPSENSE_VREF_RANGE_2)
        {
            vrefHighVoltageMv = CY_CAPSENSE_VREF_VALUE_2;
        }
        else
        {
            vrefHighVoltageMv = CY_CAPSENSE_VREF_VALUE_MIN;
        }
    #else
        if(vddaMv >= CY_CAPSENSE_VREF_RANGE_0)
        {
            vrefHighVoltageMv = CY_CAPSENSE_VREF_VALUE_0;
        }
        else if(vddaMv >= CY_CAPSENSE_VREF_RANGE_1)
        {
            vrefHighVoltageMv = CY_CAPSENSE_VREF_VALUE_1;
        }
        else
        {
            if (CY_CAPSENSE_VREF_PASS == context->ptrCommonConfig->ssVrefSource)
            {
                vrefHighVoltageMv = CY_CAPSENSE_VREF_VALUE_MIN_PASS;
            }
            else
            {
                vrefHighVoltageMv = CY_CAPSENSE_VREF_VALUE_MIN_SRSS;
            }
        }
    #endif

    return(vrefHighVoltageMv);
}


/*******************************************************************************
* Function Name: Cy_CapSense_GetVrefHighGain
****************************************************************************//**
*
* Calculates the VrefHigh Gain, based on the values of the device VDDA voltage,
* the Vref source voltage, and the desired VrefHigh voltage.
*
* \param vrefDesiredMv
* Desired VrefHigh voltage.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the lowest Gain code required to produce the VrefHigh voltage,
* when the VrefHigh is close to the desired voltage (passed through the
* vrefDesiredMv parameter) but not greater than the desired voltage.
*
*******************************************************************************/
uint32_t Cy_CapSense_GetVrefHighGain(uint32_t vrefDesiredMv, const cy_stc_capsense_context_t * context)
{
    uint32_t vferhiGain;
    uint32_t vrefInputMv;

    #if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
        (void) context;
        vrefInputMv = CY_CAPSENSE_VREF_SRSS_MV;
    #else
        if (CY_CAPSENSE_VREF_PASS == context->ptrCommonConfig->ssVrefSource)
        {
            vrefInputMv = CY_CAPSENSE_VREF_PASS_MV;
        }
        else
        {
            vrefInputMv = CY_CAPSENSE_VREF_SRSS_MV;
        }
    #endif

    vferhiGain = ((CY_CAPSENSE_VREF_GAIN_MAX * vrefInputMv) - 1u) / (vrefDesiredMv + 1u);

    if (vferhiGain > ((uint32_t)CY_CAPSENSE_VREF_GAIN_MAX - 1u))
    {
        vferhiGain = (uint32_t)CY_CAPSENSE_VREF_GAIN_MAX - 1u;
    }

    return (vferhiGain);
}


/*******************************************************************************
* Function Name: Cy_CapSense_GetVrefHighMv
****************************************************************************//**
*
* Calculates the VrefHigh voltage, based on the Gain code and the Vref source
* voltage.
*
* \param vrefGain
* The Gain code.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the VrefHigh voltage in mV, to be produced for the specified vref Gain
* code and Vref source voltage.
*
*******************************************************************************/
uint32_t Cy_CapSense_GetVrefHighMv(uint32_t vrefGain, const cy_stc_capsense_context_t * context)
{
    uint32_t vrefHighMv;
    uint32_t vrefInputMv;

    #if (CY_CAPSENSE_PSOC4_FOURTH_GEN)
        (void) context;
        vrefInputMv = CY_CAPSENSE_VREF_SRSS_MV;
    #else
        if (CY_CAPSENSE_VREF_PASS == context->ptrCommonConfig->ssVrefSource)
        {
            vrefInputMv = CY_CAPSENSE_VREF_PASS_MV;
        }
        else
        {
            vrefInputMv = CY_CAPSENSE_VREF_SRSS_MV;
        }
    #endif

    vrefHighMv = (CY_CAPSENSE_VREF_GAIN_MAX * vrefInputMv) / (vrefGain + 1u);

    return (vrefHighMv);
}

#endif /* (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2)) */


/* [] END OF FILE */
