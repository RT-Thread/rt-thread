/***************************************************************************//**
* \file cy_capsense_csx_v2.c
* \version 3.0
*
* \brief
* This file defines the data structure global variables and provides
* implementation for the low-level functions of the CSX part of
* the Sensing module. The file contains the functions used for the CSD HW block
* initialization, calibration, and scanning.
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
#include "cy_syslib.h"
#include "cy_sysclk.h"
#include "cy_gpio.h"
#include "cy_csd.h"

#include "cy_device_headers.h"
#include "cycfg_capsense_defines.h"
#include "cy_capsense_common.h"
#include "cy_capsense_structure.h"
#include "cy_capsense_csx_v2.h"
#include "cy_capsense_sensing_v2.h"

#if (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2))

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)


/*******************************************************************************
* Local function declarations
*******************************************************************************/

/******************************************************************************/
/** \cond SECTION_CAPSENSE_INTERNAL */
/** \addtogroup group_capsense_internal *//** \{ */
/******************************************************************************/
static void Cy_CapSense_CSXSetSnsClkFreq(uint32_t channelIndex, cy_stc_capsense_context_t * context);
static void Cy_CapSense_CSXStartSample(cy_stc_capsense_context_t * context);
#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_MULTI_FREQUENCY_SCAN_EN)
static void Cy_CapSense_CSXInitNextChScan(cy_stc_capsense_context_t * context);
#endif
static void Cy_CapSense_CSXInitNextScan(cy_stc_capsense_context_t * context);

__STATIC_INLINE void Cy_CapSense_CSXStartSampleExt(cy_stc_capsense_context_t * context);

/** \} \endcond */

/*******************************************************************************
* Function Name: Cy_CapSense_CSXInitialize
****************************************************************************//**
*
* Performs hardware and firmware initialization required for the CSX operation
* of the CAPSENSE&trade; middleware.
*
* This function initializes hardware to perform the CSX sensing operation.
* If both CSX and CSD sensing methods are used in the
* middleware, this function is called by the Cy_CapSense_SetupWidget() to
* change hardware configured for CSD sensing method to re-initialize for the
* CSX sensing method.
*
* If the CSD and CSX widgets are used in the middleware, do not
* mix the CSD widgets between the CSX widgets. Instead, place all
* CSX widgets in the required scanning order and then place the CSD widgets
* in the CAPSENSE&trade; Configurator tool.
* For the middleware, this action will eliminate the need for changing
* the CSD HW block configuration for every widget scan and will increase the
* execution speed in the Cy_CapSense_ScanAllWidgets() when the function is
* called.
*
* Similarly, set up and scan all the CSX widgets in such
* a sequence that the Cy_CapSense_SetupWidget() does not need to perform
* hardware sensing-configuration switches.
*
* Do not call this function directly from
* the application program.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_CSXInitialize(cy_stc_capsense_context_t * context)
{
    uint32_t modClkDivider;

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN)
        uint32_t shieldIndex;
        const cy_stc_capsense_pin_config_t * ptrShieldPin = context->ptrShieldPinConfig;
    #endif

    Cy_CapSense_DischargeExtCapacitors(context);

    Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCintA, (uint32_t)context->ptrCommonConfig->pinCintA, CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_CSX_CINT_SCAN_PIN_HSIOM);
    Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCintB, (uint32_t)context->ptrCommonConfig->pinCintB, CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_CSX_CINT_SCAN_PIN_HSIOM);

    /* Clear all pending interrupts of the CSD HW block */
    context->ptrCommonConfig->ptrCsdBase->INTR = CY_CAPSENSE_CSD_INTR_ALL_MSK;

    /* Enable the End Of Scan interrupt */
    context->ptrCommonConfig->ptrCsdBase->INTR_MASK = CY_CAPSENSE_DEFAULT_CSD_INTR_MASK_CFG;
    context->ptrCommonConfig->ptrCsdBase->INTR_SET = 0u;
    context->ptrCommonConfig->ptrCsdBase->HSCMP = CY_CAPSENSE_DEFAULT_CSD_HSCMP_CFG;
    context->ptrCommonConfig->ptrCsdBase->AMBUF = context->ptrInternalContext->csxRegAMuxBuf;
    context->ptrCommonConfig->ptrCsdBase->REFGEN = context->ptrInternalContext->csxRegRefgen;
    context->ptrCommonConfig->ptrCsdBase->CSDCMP = CY_CAPSENSE_DEFAULT_CSD_CSDCMP_CFG;
    context->ptrCommonConfig->ptrCsdBase->IDACA = CY_CAPSENSE_DEFAULT_CSD_IDACA_CFG;
    context->ptrCommonConfig->ptrCsdBase->IDACB = CY_CAPSENSE_DEFAULT_CSD_IDACB_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_RES = context->ptrInternalContext->csxRegSwResInit;
    context->ptrCommonConfig->ptrCsdBase->SENSE_DUTY = CY_CAPSENSE_DEFAULT_CSD_SENSE_DUTY_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_HS_P_SEL = CY_CAPSENSE_DEFAULT_CSD_SW_HS_P_SEL_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_HS_N_SEL = CY_CAPSENSE_DEFAULT_CSD_SW_HS_N_SEL_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_SHIELD_SEL = CY_CAPSENSE_DEFAULT_CSD_SW_SHIELD_SEL_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_AMUXBUF_SEL = context->ptrInternalContext->csxRegRefgenSel;
    context->ptrCommonConfig->ptrCsdBase->SW_BYP_SEL = CY_CAPSENSE_DEFAULT_CSD_SW_BYP_SEL_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_CMP_P_SEL = CY_CAPSENSE_DEFAULT_CSD_SW_CMP_P_SEL_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_CMP_N_SEL = context->ptrInternalContext->csxRegSwCmpNSel;
    context->ptrCommonConfig->ptrCsdBase->SW_REFGEN_SEL = context->ptrInternalContext->csxRegSwRefGenSel;
    context->ptrCommonConfig->ptrCsdBase->SW_FW_MOD_SEL = CY_CAPSENSE_DEFAULT_CSD_SW_FW_MOD_SEL_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_FW_TANK_SEL = CY_CAPSENSE_DEFAULT_CSD_SW_FW_TANK_SEL_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_DSI_SEL = CY_CAPSENSE_DEFAULT_CSD_SW_DSI_SEL_CFG;
    context->ptrCommonConfig->ptrCsdBase->SEQ_TIME = 0u;
    context->ptrCommonConfig->ptrCsdBase->SEQ_INIT_CNT = (uint32_t)context->ptrCommonConfig->csxFineInitTime;
    context->ptrCommonConfig->ptrCsdBase->SEQ_NORM_CNT = CY_CAPSENSE_DEFAULT_CSD_SEQ_NORM_CNT_CFG;
    context->ptrCommonConfig->ptrCsdBase->ADC_CTL = CY_CAPSENSE_DEFAULT_CSD_ADC_CTL_CFG;
    context->ptrCommonConfig->ptrCsdBase->SEQ_START = CY_CAPSENSE_DEFAULT_CSD_SEQ_START_CFG;
    context->ptrCommonConfig->ptrCsdBase->CONFIG = context->ptrInternalContext->csxRegConfigInit;

    #if (CY_CAPSENSE_PSOC6_FOURTH_GEN)
        context->ptrCommonConfig->ptrCsdBase->IO_SEL = CY_CAPSENSE_DEFAULT_CSD_SW_IO_SEL_CFG;
    #endif

    modClkDivider = (uint32_t)context->ptrCommonContext->modCsxClk;
    if(0u == modClkDivider)
    {
        modClkDivider = 1u;
    }

    Cy_CapSense_SetClkDivider(modClkDivider - 1u, context);

    /* Set all sensor states to the defined ISC state including shield (if enabled) */
    Cy_CapSense_SetIOsInDesiredState(context->ptrInternalContext->csxInactiveSnsDm, 0u,
                                     context->ptrInternalContext->csxInactiveSnsHsiom, context);
    #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_SHIELD_EN) && (0u != CY_CAPSENSE_SHIELD_PIN_COUNT))
        /* Connect shields to CSX ISC */
        for (shieldIndex = 0u; shieldIndex < CY_CAPSENSE_SHIELD_PIN_COUNT; shieldIndex++)
        {
            Cy_CapSense_SsConfigPinRegisters(ptrShieldPin->pcPtr, (uint32_t)ptrShieldPin->pinNumber,
                                             context->ptrInternalContext->csxInactiveSnsDm,
                                             context->ptrInternalContext->csxInactiveSnsHsiom);
            ptrShieldPin++;
        }
    #endif

    /* Enable the CSD HW block interrupt and set interrupt vector to CSX sensing method */
    context->ptrInternalContext->ptrISRCallback = &Cy_CapSense_CSXScanISR;

    context->ptrActiveScanSns->mfsChannelIndex = 0u;
}


/*******************************************************************************
* Function Name: Cy_CapSense_CSXElectrodeCheck
****************************************************************************//**
*
* Check whether electrodes were previously connected using
* the Cy_CapSense_CSXSetupWidgetExt() function and if yes, disconnect them.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_CSXElectrodeCheck(cy_stc_capsense_context_t * context)
{
    if (CY_CAPSENSE_SNS_CONNECTED == context->ptrActiveScanSns->connectedSnsState)
    {
        /* Disconnect all Tx pins */
        Cy_CapSense_CSXDisconnectTxExt(context);
        /* Disconnect all Rx pins */
        Cy_CapSense_CSXDisconnectRxExt(context);
        /* Mark the current sensor as disconnected */
        context->ptrActiveScanSns->connectedSnsState = CY_CAPSENSE_SNS_DISCONNECTED;
    }
}


/*******************************************************************************
* Function Name: Cy_CapSense_CSXDisableMode
****************************************************************************//**
*
* This function disables CSX mode.
*
* To disable CSX mode, the following tasks are performed:
* 1. Disconnect previous CSX electrode if it has been connected.
* 2. Disconnect the external capacitors (CintA and CintB).
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_CSXDisableMode(cy_stc_capsense_context_t * context)
{
    /* Disconnect previous CSX electrode if it has been connected */
    Cy_CapSense_CSXElectrodeCheck(context);

    /* Disconnect the external capacitors (CintA and CintB) */
    Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCintA, (uint32_t)context->ptrCommonConfig->pinCintA, CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_HSIOM_SEL_GPIO);
    Cy_CapSense_SsConfigPinRegisters(context->ptrCommonConfig->portCintB, (uint32_t)context->ptrCommonConfig->pinCintB, CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_HSIOM_SEL_GPIO);
}


/*******************************************************************************
* Function Name: Cy_CapSense_CSXSetupWidget
****************************************************************************//**
*
* Performs the initialization required to scan the specified CSX widget.
*
* \deprecated This function is obsolete and kept for backward compatibility only.
* The Cy_CapSense_SetupWidget() function should be used instead.
*
* This function prepares the middleware to scan all the sensors in the
* specified CSX widget by executing the following tasks:
* 1. Configure the CSD HW block if it is not configured to perform the
* CSX sensing method used by the specified widget.
* 2. Initialize the CSD HW block with specific sensing configuration (e.g.
* sensor clock, scan resolution) used by the widget.
* 3. Disconnect all previously connected electrodes, if the electrodes
* connected by the Cy_CapSense_CSDSetupWidgetExt(),
* Cy_CapSense_CSXSetupWidgetExt() functions are not disconnected.
*
* This function does not start sensor scanning. The Cy_CapSense_CSXScan()
* function must be called to start the scan sensors in the widget. If this
* function is called more than once, it does not break the middleware
* operation, but only the last initialized widget is in effect.
* Calling this function directly from the application program is not
* recommended. This function is used to implement only the user's specific
* use cases (for example faster execution).
*
* The status of a sensor scan must be checked using the Cy_CapSense_IsBusy()
* function prior to starting a next scan or setting up another widget.
*
* \param widgetId
* Specifies the ID number of the widget. A macro for the widget ID can be found
* in the cycfg_capsense.h file defined as CY_CAPSENSE_<WIDGET_NAME>_WDGT_ID.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_CSXSetupWidget(uint32_t widgetId, cy_stc_capsense_context_t * context)
{
    /* variable to access widget details */
    uint32_t tmpRegVal;

    (void)Cy_CapSense_SwitchSensingMode(CY_CAPSENSE_CSX_GROUP, context);
    /*
    * Check whether CSX electrodes were previously connected using
    * Cy_CapSense_CSXSetupWidgetExt and if yes, disconnect them
    */
    Cy_CapSense_CSXElectrodeCheck(context);
    /* Set up widget and its first sensor IDs and pointers to have assess to them after scanning  */
    Cy_CapSense_InitActivePtr(widgetId, 0u, context);
    /* Number of conversion and maxRawCount setup */
    tmpRegVal = (uint32_t)context->ptrActiveScanSns->ptrWdContext->resolution;
    context->ptrCommonConfig->ptrCsdBase->SEQ_NORM_CNT = tmpRegVal;
    context->ptrActiveScanSns->ptrWdContext->maxRawCount = (uint16_t)tmpRegVal *
        (context->ptrActiveScanSns->ptrWdContext->snsClk - CY_CAPSENSE_CSX_DEADBAND_CYCLES_NUMBER);

        /* SnsClk setup */
    #if (CY_CAPSENSE_ENABLE != CY_CAPSENSE_MULTI_FREQUENCY_SCAN_EN)
        Cy_CapSense_CSXSetSnsClkFreq(CY_CAPSENSE_MFS_CH0_INDEX, context);
    #endif
}

/*******************************************************************************
* Function Name: Cy_CapSense_CSXSetupWidgetExt
****************************************************************************//**
*
* Performs extended initialization required to scan a specified sensor in
* a widget using CSX sensing method.
*
* \deprecated This function is obsolete and kept for backward compatibility only.
* The Cy_CapSense_SetupWidgetExt() function should be used instead.
*
* This function performs the same tasks of Cy_CapSense_CSXSetupWidget() and
* also connects and configures specified sensor for scan. Hence this
* function, along with Cy_CapSense_CSXScanExt() function, can be used to
* scan a specific sensor in the widget.
*
* This function should be called for a widget that is configured to use
* CSX sensing method. Using this function on a non-CSX sensing widget
* would cause an unexpected result.
*
* This function requires using the Cy_CapSense_CSXScanExt() function to
* initiate a scan.
*
* Calling this function directly from the application program is not
* recommended. This function is used to implement only the user's
* specific use cases (for example faster execution).
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
void Cy_CapSense_CSXSetupWidgetExt(
                uint32_t widgetId,
                uint32_t sensorId,
                cy_stc_capsense_context_t * context)
{
    /* Initialize widget */
    Cy_CapSense_CSXSetupWidget(widgetId, context);

    /* Initialize sensor data structure pointer to appropriate address */
    Cy_CapSense_InitActivePtrSns(sensorId, context);

    /*
    * Connect current sensor's Tx and Rx IOs for scan and set flag
    * to indicate that IOs should be disconnected
    */
    Cy_CapSense_CSXConnectTxExt(context);
    Cy_CapSense_CSXConnectRxExt(context);
}


/*******************************************************************************
* Function Name: Cy_CapSense_CSXScan
****************************************************************************//**
*
* This function initiates a scan for the sensors of the widget initialized
* by the Cy_CapSense_CSXSetupWidget() function.
*
* \deprecated This function is obsolete and kept for backward compatibility only.
* The Cy_CapSense_Scan() function should be used instead.
*
* This function does the following tasks:
* 1. Connects the first sensor of the widget.
* 2. Configures the IDAC value.
* 3. Starts scanning for the first sensor in the widget.
*
* This function is called by the Cy_CapSense_Scan() if the given
* widget uses the CSX sensing method.
*
* Calling this function directly from the application program is not
* recommended. This function is used to implement only the user's specific
* use cases (for example faster execution).
*
* This function is called when no scanning is in progress. I.e.
* Cy_CapSense_IsBusy() returns a non-busy status and the widget must be
* preconfigured using the Cy_CapSense_CSXSetupWidget() function prior
* to calling this function.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_CSXScan(cy_stc_capsense_context_t * context)
{
    Cy_CapSense_InitActivePtrSns(0u, context);

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_MULTI_FREQUENCY_SCAN_EN)
        Cy_CapSense_CSXSetSnsClkFreq(CY_CAPSENSE_MFS_CH0_INDEX, context);
    #endif

    context->ptrActiveScanSns->scanScope |= CY_CAPSENSE_SCAN_SCOPE_ALL_SNS_MASK;

    /* Connect electrodes */
    Cy_CapSense_CSXConnectTxExt(context);
    Cy_CapSense_CSXConnectRxExt(context);

    /* Set Start of scan flag */
    Cy_CapSense_SetBusyFlags(context);
    Cy_CapSense_CSXStartSample(context);
}


/*******************************************************************************
* Function Name: Cy_CapSense_CSXScanExt()
****************************************************************************//**
*
* Starts the CSD conversion on the preconfigured sensor.
*
* \deprecated This function is obsolete and kept for backward compatibility only.
* The Cy_CapSense_ScanExt() function should be used instead.
*
* This function performs scanning of a specific sensor in the widget
* previously initialized using the Cy_CapSense_CSXSetupWidgetExt() function.
*
* This function is called when no scanning is in progress.
* I.e. Cy_CapSense_IsBusy() returns a non-busy status and the widget must
* be preconfigured using Cy_CapSense_CSXSetupWidgetExt() function prior
* to calling this function. Calling this function directly from
* the application program is not recommended. This function is used to
* implement only the user's specific use cases (for example faster execution).
*
* This function does not disconnect sensor GPIOs from CSD HW block at the
* end of a scan, therefore making subsequent scan of the same sensor is faster.
* If sensor must be disconnected after the scan,
* the Cy_CapSense_CSXDisconnectTx() or Cy_CapSense_CSXDisconnectRx() functions
* can be used.
*
* Calling Cy_CapSense_SetupWidget(), Cy_CapSense_CSXSetupWidget(),
* Cy_CapSense_ScanAllWidgets(), or if Cy_CapSense_RunTuner() returns
* CY_CAPSENSE_STATUS_RESTART_DONE status invalidated initialization
* made by this function.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_CSXScanExt(cy_stc_capsense_context_t * context)
{
    cy_stc_active_scan_sns_t * ptrActive = context->ptrActiveScanSns;

    /* Set busy flag and start conversion */
    Cy_CapSense_SetBusyFlags(context);

    /* Set scope flag */
    ptrActive->scanScope = CY_CAPSENSE_SCAN_SCOPE_SNGL_SNS;

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_MULTI_FREQUENCY_SCAN_EN)
        if(0u != ptrActive->mfsChannelIndex)
        {
            Cy_CapSense_InitActivePtrSns(ptrActive->sensorIndex, context);
            Cy_CapSense_CSXSetSnsClkFreq(CY_CAPSENSE_MFS_CH0_INDEX, context);
        }
    #endif

    Cy_CapSense_CSXStartSample(context);
}


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_CSXCalibrateWidget
****************************************************************************//**
*
* Executes the IDAC calibration for all the sensors in the widget specified in
* the input.
*
* \deprecated This function is obsolete and kept for backward compatibility only.
* The Cy_CapSense_CalibrateWidget() function should be used instead.
*
* Performs a successive approximation search algorithm to find appropriate
* IDAC values for all sensors in the specified widget that provide
* the raw count to the level specified by the target parameter.
*
* Calibration returns CY_CAPSENSE_STATUS_BAD_DATA if the achieved raw count is outside
* of the range specified by the target and acceptable calibration deviation
* parameters.
*
* This function could be used when the CSX Enable IDAC auto-calibration
* parameter is enabled.
*
* \param widgetId
* Specifies the ID number of the widget. A macro for the widget ID can be found
* in the cycfg_capsense.h file defined as CY_CAPSENSE_<WIDGET_NAME>_WDGT_ID.
*
* \param target
* Specifies the calibration target in percentages of the maximum raw count.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the specified widget calibration:
* - CY_CAPSENSE_STATUS_SUCCESS       - The operation is successfully completed.
* - CY_CAPSENSE_STATUS_BAD_PARAM     - The input parameter is invalid.
* - CY_CAPSENSE_STATUS_BAD_DATA      - The calibration failed and CAPSENSE&trade; may not operate
*                         as expected.
* - CY_CAPSENSE_STATUS_INVALID_STATE - The previous scanning is not completed, and
*                         the CAPSENSE&trade; middleware is busy.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_CSXCalibrateWidget(
                uint32_t widgetId,
                uint32_t target,
                cy_stc_capsense_context_t * context)
{
    uint32_t cpuFreqMHz;
    uint32_t watchdogCounter;
    uint32_t freqChIndex;

    cy_capsense_status_t calibrateStatus = CY_CAPSENSE_STATUS_SUCCESS;
    const cy_stc_capsense_widget_config_t * ptrWdCfg;
    cy_stc_capsense_sensor_context_t * ptrActSnsContext;

    uint32_t rawTarget;
    uint32_t totalSns;
    uint32_t modClkDivider;
    uint32_t snsClkDivider;
    uint32_t calibrationIndex;
    /* Currently used IDAC-bit */
    uint8_t curIdacMask = CY_CAPSENSE_CAL_MIDDLE_VALUE;
    /* Next used IDAC-bit */
    uint8_t nextIdacMask = ((uint8_t)CY_CAPSENSE_CAL_MIDDLE_VALUE) >> 1u;

    /* Approximate duration of Wait For Init loop */
    const uint32_t isBusyLoopDuration = 5u;

    /* Wait For Init watchdog timeout in microseconds */
    uint64_t isBusyWatchdogTimeUs = 0u;


    if((context->ptrCommonConfig->numWd <= widgetId) ||
        (CY_CAPSENSE_DISABLE == context->ptrCommonConfig->csxIdacAutocalEn))
    {
        calibrateStatus = CY_CAPSENSE_STATUS_BAD_PARAM;
    }

    if(CY_CAPSENSE_CSX_GROUP != context->ptrWdConfig[widgetId].senseMethod)
    {
        calibrateStatus = CY_CAPSENSE_STATUS_BAD_PARAM;
    }

    if(CY_CAPSENSE_BUSY  == (context->ptrCommonContext->status & CY_CAPSENSE_BUSY))
    {
        /* Previous widget is being scanned, return error */
        calibrateStatus = CY_CAPSENSE_STATUS_INVALID_STATE;
    }

    if(CY_CAPSENSE_STATUS_SUCCESS == calibrateStatus)
    {
        ptrWdCfg = &context->ptrWdConfig[widgetId];
        ptrActSnsContext = ptrWdCfg->ptrSnsContext;
        totalSns = ptrWdCfg->numSns;

        /* Calculate target raw count */
        rawTarget = ((uint32_t)context->ptrWdContext[widgetId].maxRawCount * target) / CY_CAPSENSE_PERCENTAGE_100;

        /* Clear raw count registers and IDAC registers of all the sensors/nodes */
        for(freqChIndex = 0u; freqChIndex < CY_CAPSENSE_CONFIGURED_FREQ_NUM; freqChIndex++)
        {
            /* Clear raw count registers and IDAC registers of all the sensors/nodes */
            for (calibrationIndex = 0u; calibrationIndex < totalSns; calibrationIndex++)
            {
                ptrActSnsContext[calibrationIndex + (freqChIndex * context->ptrCommonConfig->numSns)].raw = 0u;
                ptrActSnsContext[calibrationIndex + (freqChIndex * context->ptrCommonConfig->numSns)].idacComp = curIdacMask;
            }
        }
        modClkDivider = (uint32_t)context->ptrCommonContext->modCsxClk;
        snsClkDivider = (uint32_t)ptrWdCfg->ptrWdContext->snsClk;

        if(0u == modClkDivider)
        {
            modClkDivider = 1u;
        }

        if(0u == snsClkDivider)
        {
            snsClkDivider = 1u;
        }

        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_MULTI_FREQUENCY_SCAN_EN)
            if(context->ptrCommonConfig->csxMfsDividerOffsetF1 >
               context->ptrCommonConfig->csxMfsDividerOffsetF2)
            {
                snsClkDivider += context->ptrCommonConfig->csxMfsDividerOffsetF1;
            }
            else
            {
                snsClkDivider += context->ptrCommonConfig->csxMfsDividerOffsetF2;
            }

            isBusyWatchdogTimeUs  = (uint64_t)totalSns * CY_CAPSENSE_MAX_SUPPORTED_FREQ_NUM * ptrWdCfg->ptrWdContext->resolution;
        #else
            isBusyWatchdogTimeUs  = (uint64_t)totalSns * ptrWdCfg->ptrWdContext->resolution;
        #endif

        isBusyWatchdogTimeUs *= (uint64_t)snsClkDivider * modClkDivider * CY_CAPSENSE_CONVERSION_MEGA;
        isBusyWatchdogTimeUs /= context->ptrCommonConfig->periClkHz;

        if(0uL == isBusyWatchdogTimeUs)
        {
            isBusyWatchdogTimeUs = 1u;
        }

        isBusyWatchdogTimeUs *= CY_CAPSENSE_CSX_WATCHDOG_MARGIN_COEFF;

        /* Perform binary search for accurate IDAC value for each sensor/node */
        do
        {
            /* Scan all the sensors/nodes in widget */
            (void)Cy_CapSense_SetupWidget(widgetId, context);
            (void)Cy_CapSense_Scan(context);

            cpuFreqMHz = context->ptrCommonConfig->cpuClkHz / CY_CAPSENSE_CONVERSION_MEGA;
            watchdogCounter = Cy_CapSense_WatchdogCyclesNum((uint32_t)isBusyWatchdogTimeUs, cpuFreqMHz, isBusyLoopDuration);

            /* Wait for EOS */
            while (CY_CAPSENSE_BUSY  == (context->ptrCommonContext->status & CY_CAPSENSE_BUSY))
            {
                if(0uL == watchdogCounter)
                {
                    break;
                }

                watchdogCounter--;
            }

            /* Set pointer to the widget's first sensor data */
            ptrActSnsContext = ptrWdCfg->ptrSnsContext;

            /* Check raw count and adjust IDAC, loop through all the sensors/nodes */
            for (freqChIndex = 0u; freqChIndex < CY_CAPSENSE_CONFIGURED_FREQ_NUM; freqChIndex++)
            {
                for (calibrationIndex = 0u; calibrationIndex < totalSns; calibrationIndex++)
                {
                    /* Check whether the current raw count is above target.
                    * If yes, clear the MS bit of bit.
                    * If no, keep the MS bit and set next bit.
                    */
                    if (ptrActSnsContext[calibrationIndex + (freqChIndex * context->ptrCommonConfig->numSns)].raw > rawTarget)
                    {
                        ptrActSnsContext[calibrationIndex + (freqChIndex * context->ptrCommonConfig->numSns)].idacComp &= (uint8_t)(~curIdacMask);
                    }
                    ptrActSnsContext[calibrationIndex + (freqChIndex * context->ptrCommonConfig->numSns)].idacComp |= nextIdacMask;
                }
            }

            /* Shift both current IDAC and pre IDAC values to the right by 1 */
            curIdacMask = nextIdacMask;
            nextIdacMask = nextIdacMask >> 1u;
        }
        while (curIdacMask != 0u);
        calibrateStatus = CY_CAPSENSE_STATUS_SUCCESS;
    }

    if(CY_CAPSENSE_STATUS_SUCCESS == calibrateStatus)
    {
        /* Perform specified widget scan to check calibration result */
        /* Scan all the sensors/nodes in widget */
        (void)Cy_CapSense_SetupWidget(widgetId, context);
        (void)Cy_CapSense_Scan(context);

        cpuFreqMHz = context->ptrCommonConfig->cpuClkHz / CY_CAPSENSE_CONVERSION_MEGA;
        watchdogCounter = Cy_CapSense_WatchdogCyclesNum((uint32_t)isBusyWatchdogTimeUs, cpuFreqMHz, isBusyLoopDuration);

        /* Wait for EOS */
        while (CY_CAPSENSE_BUSY  == (context->ptrCommonContext->status & CY_CAPSENSE_BUSY))
        {
            if(0uL == watchdogCounter)
            {
                calibrateStatus = CY_CAPSENSE_STATUS_TIMEOUT;
                break;
            }

            watchdogCounter--;
        }

        if(CY_CAPSENSE_STATUS_SUCCESS == calibrateStatus)
        {
            calibrateStatus = Cy_CapSense_CalibrateCheck(widgetId, target, CY_CAPSENSE_CSX_GROUP, context);
        }
    }

    return(calibrateStatus);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN) */


/*******************************************************************************
* Function Name: Cy_CapSense_CSXSetUpIdacs
****************************************************************************//**
*
* Configures IDAC for the CSX sensing method.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_CSXSetUpIdacs(cy_stc_capsense_context_t * context)
{
    uint32_t tmpRegVal;

    /* Set IDAC gain */
    tmpRegVal = context->ptrCommonConfig->idacGainTable[context->ptrActiveScanSns->ptrWdContext->idacGainIndex].gainReg;
    /* Set IDAC code */
    tmpRegVal |= (uint32_t)context->ptrActiveScanSns->ptrSnsContext->idacComp & CY_CAPSENSE_CSD_IDACA_VAL_MSK;
    tmpRegVal |= CY_CAPSENSE_DEFAULT_CSD_IDACA_CFG;

    context->ptrCommonConfig->ptrCsdBase->IDACA = tmpRegVal;
}

/*******************************************************************************
* Function Name: Cy_CapSense_SsCSXStartSample
****************************************************************************//**
*
* Starts scanning for the CSX widget.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_CSXStartSample(cy_stc_capsense_context_t * context)
{
    /* Set up IDAC Value */
    Cy_CapSense_CSXSetUpIdacs(context);

    /* Clear previous interrupts */
    context->ptrCommonConfig->ptrCsdBase->INTR = CY_CAPSENSE_CSD_INTR_ALL_MSK;
    (void)context->ptrCommonConfig->ptrCsdBase->INTR;

    /* Enable interrupt */
    context->ptrCommonConfig->ptrCsdBase->INTR_MASK = CY_CAPSENSE_CSD_INTR_MASK_SAMPLE_MSK;

    if(NULL != context->ptrInternalContext->ptrSSCallback)
    {
        context->ptrInternalContext->ptrSSCallback(context->ptrActiveScanSns);
    }

    Cy_CapSense_CSXStartSampleExt(context);
}


/*******************************************************************************
* Function Name: Cy_CapSense_CSXConnectRx
****************************************************************************//**
*
* Connects port pin (an Rx electrode) to the CSD HW block using AMUX bus.
*
* \deprecated This function is obsolete and kept for backward compatibility only.
* The Cy_CapSense_SetPinState() function should be used instead.
*
* This function can be used to customize the default sensor connection
* by connecting one or more pins to an existing sensor as an Rx electrode
* prior to initiating scan of the sensor.
*
* The function ignores whether the sensor is a ganged sensor and
* connects only a specified port pin to the CSD HW block. This function can
* only use GPIOs that is already assigned to CAPSENSE&trade; middleware.
*
* The functions that perform a setup and scan of a sensor/widget do not
* take into account changes in the design made by
* the Cy_CapSense_CSXConnectRx() function. Hence all GPIOs connected
* using this function must be disconnected using
* the Cy_CapSense_CSXDisconnectRx() function prior to initializing
* new widgets. Use this function in StartSample
* callback (see the \ref group_capsense_callbacks section for details)
* or with low-level functions that perform a single-sensor scanning.
*
* Scanning should be completed before calling this function.
*
* \param rxPtr
* Specifies the pointer to the cy_stc_capsense_pin_config_t object belonging to
* a sensor which to be connected to the CSD HW block as an Rx electrode.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \funcusage
*
* An example of using the function to perform port pin re-connection:
* \snippet capsense/snippet/main.c snippet_Cy_CapSense_CSXConnect
*
*******************************************************************************/
void Cy_CapSense_CSXConnectRx(
                const cy_stc_capsense_pin_config_t * rxPtr,
                const cy_stc_capsense_context_t * context)
{
    (void) context;
    Cy_CapSense_SsConfigPinRegisters(rxPtr->pcPtr, (uint32_t)rxPtr->pinNumber, CY_CAPSENSE_DM_GPIO_ANALOG, CY_CAPSENSE_HSIOM_SEL_AMUXA);
}


/*******************************************************************************
* Function Name: Cy_CapSense_CSXConnectTx
****************************************************************************//**
*
* Connects port pin (a Tx electrode) to the CSD HW block.
*
* \deprecated This function is obsolete and kept for backward compatibility only.
* The Cy_CapSense_SetPinState() function should be used instead.
*
* This function can be used to customize the default sensor connection
* by connecting one or more pins to an existing sensor as a Tx electrode
* prior to initiating scan of the sensor.
*
* The function ignores whether the sensor is a ganged sensor and
* connects only a specified port pin to the CSD HW block. This function can
* only use GPIOs that is already assigned to CAPSENSE&trade; middleware.
*
* The functions that perform a setup and scan of a sensor/widget do not
* take into account changes in the design made by
* the Cy_CapSense_CSXConnectTx() function. Hence all GPIOs connected
* using this function must be disconnected using
* the Cy_CapSense_CSXDisconnectTx() function prior to initializing
* new widgets. Use this function in StartSample
* callback (see the \ref group_capsense_callbacks section for details)
* or with low-level functions that perform a single-sensor scanning.
*
* Scanning should be completed before calling this function.
*
* \param txPtr
* Specifies the pointer to the cy_stc_capsense_pin_config_t object belonging to
* a sensor which to be connected to the CSD HW block as a Tx electrode.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \funcusage
*
* An example of using the function to perform port pin re-connection:
* \snippet capsense/snippet/main.c snippet_Cy_CapSense_CSXConnect
*
*******************************************************************************/
void Cy_CapSense_CSXConnectTx(
                const cy_stc_capsense_pin_config_t * txPtr,
                const cy_stc_capsense_context_t * context)
{
    (void) context;
    Cy_CapSense_SsConfigPinRegisters(txPtr->pcPtr, (uint32_t)txPtr->pinNumber, CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF, CY_CAPSENSE_CSX_TX_SCAN_PIN_HSIOM);
}


/*******************************************************************************
* Function Name: Cy_CapSense_CSXDisconnectRx
****************************************************************************//**
*
* Disconnects port pin (an Rx electrode) from the CSD HW block by disconnecting
* it from the AMUX bus.
*
* \deprecated This function is obsolete and kept for backward compatibility only.
* The Cy_CapSense_SetPinState() function should be used instead.
*
* This function can be used to disconnect a sensor connected
* using the Cy_CapSense_CSXConnectRx() function. In addition, this
* function can be used to customize default sensor connection by
* disconnecting one or more already connected sensors prior to
* initiating scan of the sensor.
*
* This function works identically to the Cy_CapSense_CSDConnectRx() function
* except it disconnects the specified port pin used by the sensor.
*
* Scanning should be completed before calling this function.
*
* \param rxPtr
* Specifies the pointer to the cy_stc_capsense_pin_config_t object belonging
* to an Rx pin sensor to be disconnected from the CSD HW block.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \funcusage
*
* An example of using the function to perform port pin re-connection:
* \snippet capsense/snippet/main.c snippet_Cy_CapSense_CSXConnect
*
*******************************************************************************/
void Cy_CapSense_CSXDisconnectRx(
                const cy_stc_capsense_pin_config_t * rxPtr,
                const cy_stc_capsense_context_t * context)
{
    (void) context;
    Cy_CapSense_SsConfigPinRegisters(rxPtr->pcPtr, (uint32_t)rxPtr->pinNumber,
                                     context->ptrInternalContext->csxInactiveSnsDm,
                                     context->ptrInternalContext->csxInactiveSnsHsiom);
    Cy_GPIO_Clr(rxPtr->pcPtr, (uint32_t)rxPtr->pinNumber);
}


/*******************************************************************************
* Function Name: Cy_CapSense_CSXDisconnectTx
****************************************************************************//**
*
* Disconnects port pin (a Tx electrode) from the CSD HW block.
*
* \deprecated This function is obsolete and kept for backward compatibility only.
* The Cy_CapSense_SetPinState() function should be used instead.
*
* This function can be used to disconnect a sensor connected
* using the Cy_CapSense_CSXConnectTx() function. In addition, this
* function can be used to customize default sensor connection by
* disconnecting one or more already connected sensors prior to
* initiating scan of the sensor.
*
* This function works identically to the Cy_CapSense_CSDConnectTx() function
* except it disconnects the specified port pin used by the sensor.
*
* Scanning should be completed before calling this function.
*
* \param txPtr
* Specifies the pointer to the cy_stc_capsense_pin_config_t object belonging
* to a Tx pin sensor to be disconnected from the CSD HW block.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \funcusage
*
* An example of using the function to perform port pin re-connection:
* \snippet capsense/snippet/main.c snippet_Cy_CapSense_CSXConnect
*
*******************************************************************************/
void Cy_CapSense_CSXDisconnectTx(
                const cy_stc_capsense_pin_config_t * txPtr,
                const cy_stc_capsense_context_t * context)
{
    (void) context;
    Cy_CapSense_SsConfigPinRegisters(txPtr->pcPtr, (uint32_t)txPtr->pinNumber,
                                     context->ptrInternalContext->csxInactiveSnsDm,
                                     context->ptrInternalContext->csxInactiveSnsHsiom);
    Cy_GPIO_Clr(txPtr->pcPtr, (uint32_t)txPtr->pinNumber);
}


/*******************************************************************************
* Function Name: Cy_CapSense_CSXConnectTxExt
****************************************************************************//**
*
* Connects a current Tx electrode to the CSX scanning hardware.
*
* This function connects all current Tx electrode's pins to the CSD_SENSE signal.
* It is assumed that drive mode of the port pin is already set to STRONG
* in the HSIOM_PORT_SELx register.
*
* Calling this function directly from the application program is not
* recommended. This function is used to implement only the user's specific
* use cases (for faster execution time when there is only one port pin for an
* electrode for example).
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_CSXConnectTxExt(cy_stc_capsense_context_t * context)
{
    uint32_t pinIndex;
    const cy_stc_capsense_pin_config_t * pinPointer = context->ptrActiveScanSns->ptrTxConfig->ptrPin;

    for (pinIndex = context->ptrActiveScanSns->ptrTxConfig->numPins; pinIndex-- > 0u;)
    {
        Cy_CapSense_CSXConnectTx(pinPointer, context);
        pinPointer++;
    }
    context->ptrActiveScanSns->connectedSnsState = CY_CAPSENSE_SNS_CONNECTED;
}


/*******************************************************************************
* Function Name: Cy_CapSense_CSXConnectRxExt
****************************************************************************//**
*
* Connects a current Rx electrode to the CSX scanning hardware.
*
* This function connects all current Rx electrode's pins to the CSD_SENSE signal.
* It is assumed that drive mode of the port pin is already set to STRONG
* in the HSIOM_PORT_SELx register.
*
* Calling this function directly from the application program is not
* recommended. This function is used to implement only the user's specific
* use cases (for faster execution time when there is only one port pin for an
* electrode for example).
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_CSXConnectRxExt(cy_stc_capsense_context_t * context)
{
    uint32_t pinIndex;
    const cy_stc_capsense_pin_config_t * pinPointer = context->ptrActiveScanSns->ptrRxConfig->ptrPin;

    for (pinIndex = context->ptrActiveScanSns->ptrRxConfig->numPins; pinIndex-- > 0u;)
    {
        Cy_CapSense_CSXConnectRx(pinPointer, context);
        pinPointer++;
    }
    context->ptrActiveScanSns->connectedSnsState = CY_CAPSENSE_SNS_CONNECTED;
}


/*******************************************************************************
* Function Name: Cy_CapSense_CSXDisconnectTxExt
****************************************************************************//**
*
* Disconnects a current Tx electrode from the CSX scanning hardware.
*
* This function connects all current Tx electrode's pins to the CSD_SENSE signal.
* It is assumed that drive mode of the port pin is already set to STRONG
* in the HSIOM_PORT_SELx register.
*
* Calling this function directly from the application program is not
* recommended. This function is used to implement only the user's specific
* use cases (for faster execution time when there is only one port pin for an
* electrode for example).
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_CSXDisconnectTxExt(const cy_stc_capsense_context_t * context)
{
    uint32_t pinIndex;
    const cy_stc_capsense_pin_config_t * pinPointer = context->ptrActiveScanSns->ptrTxConfig->ptrPin;

    for (pinIndex = context->ptrActiveScanSns->ptrTxConfig->numPins; pinIndex-- > 0u;)
    {
        Cy_CapSense_CSXDisconnectTx(pinPointer, context);
        pinPointer++;
    }
}


/*******************************************************************************
* Function Name: Cy_CapSense_CSXDisconnectRxExt
****************************************************************************//**
*
* Connects a current Tx electrode to the CSX scanning hardware.
*
* This function connects all current Tx electrode's pins to the CSD_SENSE signal.
* It is assumed that drive mode of the port pin is already set to STRONG
* in the HSIOM_PORT_SELx register.
*
* Calling this function directly from the application program is not
* recommended. This function is used to implement only the user's specific
* use cases (for faster execution time when there is only one port pin for an
* electrode for example).
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_CSXDisconnectRxExt(const cy_stc_capsense_context_t * context)
{
    uint32_t pinIndex;
    const cy_stc_capsense_pin_config_t * pinPointer = context->ptrActiveScanSns->ptrRxConfig->ptrPin;

    for (pinIndex = context->ptrActiveScanSns->ptrRxConfig->numPins; pinIndex-- > 0u;)
    {
        Cy_CapSense_CSXDisconnectRx(pinPointer, context);
        pinPointer++;
    }
}


/*******************************************************************************
* Function Name: Cy_CapSense_CSXSetWidgetTxClkSrc
****************************************************************************//**
*
* Sets a source for the Tx clock for a widget.
*
* \param ptrWdConfig
* The pointer to the cy_stc_capsense_widget_context_t structure.
*
*******************************************************************************/
void Cy_CapSense_CSXSetWidgetTxClkSrc(const cy_stc_capsense_widget_config_t * ptrWdConfig)
{
    cy_stc_capsense_widget_context_t * ptrWdCxt = ptrWdConfig->ptrWdContext;

    if (0u != (ptrWdCxt->snsClkSource & CY_CAPSENSE_CLK_SOURCE_AUTO_MASK))
    {
        ptrWdCxt->snsClkSource = (uint8_t)Cy_CapSense_SsCalcLfsrSize((uint32_t)ptrWdCxt->snsClk, (uint32_t)ptrWdCxt->resolution) | CY_CAPSENSE_CLK_SOURCE_AUTO_MASK;
    }
}


/*******************************************************************************
* Function Name: Cy_CapSense_CSXScanISR
****************************************************************************//**
*
* This is an internal ISR function to handle the CSX sensing method operation.
*
* This handler covers the following functionality:
* - Read the result of the measurement and store it into the corresponding register of
* the data structure.
* - If the Noise Metric functionality is enabled, then check the number of bad
* conversions and repeat the scan of the current sensor if the number of bad
* conversions is greater than the Noise Metric Threshold.
* - Initiate the scan of the next sensor for multiple sensor scanning mode.
* - Update the Status register in the data structure.
* - Switch the HW IP block to the default state if scanning of all the sensors is
* completed.
*
* \param capsenseContext
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_CSXScanISR(void * capsenseContext)
{
    uint32_t tmpRawCount;
    cy_stc_capsense_context_t * cxt = (cy_stc_capsense_context_t *)capsenseContext;
    const cy_stc_active_scan_sns_t * ptrActive = cxt->ptrActiveScanSns;
    uint32_t maxCount = (uint32_t) ptrActive->ptrWdContext->maxRawCount;

    cxt->ptrCommonConfig->ptrCsdBase->INTR_MASK = CY_CAPSENSE_CSD_INTR_MASK_CLEAR_MSK;

    /* Clear all pending interrupts of the CSD HW block */
    cxt->ptrCommonConfig->ptrCsdBase->INTR = CY_CAPSENSE_CSD_INTR_ALL_MSK;
    (void)cxt->ptrCommonConfig->ptrCsdBase->INTR;


    tmpRawCount  = (uint16_t)(cxt->ptrCommonConfig->ptrCsdBase->RESULT_VAL1 &
                                             CY_CAPSENSE_CSD_RESULT_VAL1_VALUE_MSK);

    tmpRawCount += (uint16_t)(cxt->ptrCommonConfig->ptrCsdBase->RESULT_VAL2 &
                                             CY_CAPSENSE_CSD_RESULT_VAL2_VALUE_MSK);

    /* This workaround needed to prevent overflow in the SW register map. ID #234358 */
    if(tmpRawCount > maxCount)
    {
        tmpRawCount = maxCount;
    }
    ptrActive->ptrSnsContext->raw = (uint16_t) (maxCount - tmpRawCount);

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_MULTI_FREQUENCY_SCAN_EN)
        /* Either complete scan or initiate new one */
        if(ptrActive->mfsChannelIndex < CY_CAPSENSE_MFS_CH2_INDEX)
        {
            Cy_CapSense_CSXInitNextChScan(cxt);
        }
        else if (CY_CAPSENSE_SCAN_SCOPE_SNGL_SNS == ptrActive->scanScope)
        {
            Cy_CapSense_ClrBusyFlags(cxt);
            cxt->ptrCommonConfig->ptrCsdBase->CONFIG = cxt->ptrInternalContext->csxRegConfigInit;
            cxt->ptrCommonConfig->ptrCsdBase->CSDCMP = CY_CAPSENSE_DEFAULT_CSD_CSDCMP_CFG;
            cxt->ptrCommonConfig->ptrCsdBase->IDACA = CY_CAPSENSE_DEFAULT_CSD_IDACA_CFG;
        }
        else
        {
            /* Disconnect Tx electrodes of previously scanned sensor as preparation for next sensor scan */
            Cy_CapSense_CSXDisconnectTxExt(cxt);
            /* Scan the next sensor */
            Cy_CapSense_CSXInitNextScan(cxt);
        }
    #else
        if (CY_CAPSENSE_SCAN_SCOPE_SNGL_SNS == ptrActive->scanScope)
        {
            Cy_CapSense_ClrBusyFlags(cxt);
            cxt->ptrCommonConfig->ptrCsdBase->CONFIG = cxt->ptrInternalContext->csxRegConfigInit;
            cxt->ptrCommonConfig->ptrCsdBase->CSDCMP = CY_CAPSENSE_DEFAULT_CSD_CSDCMP_CFG;
            cxt->ptrCommonConfig->ptrCsdBase->IDACA = CY_CAPSENSE_DEFAULT_CSD_IDACA_CFG;
        }
        else
        {
            /* Disconnect Tx electrodes of previously scanned sensor as preparation for next sensor scan */
            Cy_CapSense_CSXDisconnectTxExt(cxt);
            /* Scan the next sensor */
            Cy_CapSense_CSXInitNextScan(cxt);
        }
    #endif

}


/*******************************************************************************
* Function Name: Cy_CapSense_CSXInitNextScan
****************************************************************************//**
*
* This function initializes the next sensor scan.
*
* The function increments the sensor index, updates sense clock for matrix
* or touchpad widgets only, sets up Compensation IDAC, enables the sensor and
* scans it. When all the sensors are scanned it continues to set up the next
* widget until all the widgets are scanned.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_CSXInitNextScan(cy_stc_capsense_context_t * context)
{
    cy_stc_active_scan_sns_t * ptrActive = context->ptrActiveScanSns;

    ptrActive->mfsChannelIndex = 0u;
    ptrActive->ptrSnsContext = &ptrActive->ptrWdConfig->ptrSnsContext[ptrActive->sensorIndex];

    /* Increment sensor index and sensor's context pointer to scope next sensor in widget */
    ptrActive->sensorIndex++;
    ptrActive->ptrSnsContext++;
    /* Initiate scan for next sensor in widget, if all the sensors in widget are not scanned */
    ptrActive->txIndex--;

        if (ptrActive->txIndex > 0u)
        {
            /* Increment pointer to the next Tx electrode and connect it for scan  */
            ptrActive->ptrTxConfig++;
            Cy_CapSense_CSXConnectTxExt(context);
            /* Initiate a next scan */
            Cy_CapSense_CSXSetUpIdacs(context);
            Cy_CapSense_CSXStartSample(context);
        }
        /* Check whether all Rx are looped through */
        else
        {
            ptrActive->rxIndex--;
            if (ptrActive->rxIndex > 0u)
            {
                /* Disconnect the current Rx electrode and connect a next Rx electrode */
                Cy_CapSense_CSXDisconnectRxExt(context);
                ptrActive->ptrRxConfig++;
                Cy_CapSense_CSXConnectRxExt(context);
                /* Re-initialize Tx index to be scanned per Rx and connect the first Tx electrode again */
                ptrActive->txIndex = ptrActive->ptrWdConfig->numRows;
                ptrActive->ptrTxConfig = &ptrActive->ptrWdConfig->ptrEltdConfig[ptrActive->ptrWdConfig->numCols];
                Cy_CapSense_CSXConnectTxExt(context);
                /* Initiate a next scan */
                Cy_CapSense_CSXSetUpIdacs(context);
                Cy_CapSense_CSXStartSample(context);
            }
            else
            {
                /* If all the sensors are scanned, disconnect the last Rx electrode */
                Cy_CapSense_CSXDisconnectRxExt(context);
                ptrActive->connectedSnsState = CY_CAPSENSE_SNS_DISCONNECTED;
                /* Call scan of next widget if requested. If not, complete scan */
                if (0u != (ptrActive->scanScope & CY_CAPSENSE_SCAN_SCOPE_ALL_WD_MASK))
                {
                    Cy_CapSense_SsPostAllWidgetsScan(context);
                }
                else
                {
                    /* All pending scans completed, clear busy state as scanning is completed  */
                    Cy_CapSense_ClrBusyFlags(context);
            }
        }
    }
}


/*******************************************************************************
* Function Name: Cy_CapSense_SsCSXStartSampleExt
****************************************************************************//**
*
* Starts the HW sequencer to perform the CSX conversion.
*
* This function covers the following functionality:
* 1. Configures the HW sequencer to perform the coarse initialization.
* 2. Waiting for completion of the coarse initialization.
* 3. Configures the HW sequencer to perform the normal conversion.
* 4. Starts the normal conversion
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
__STATIC_INLINE void Cy_CapSense_CSXStartSampleExt(cy_stc_capsense_context_t * context)
{
    uint32_t cpuFreqMHz;
    uint32_t watchdogCounter;

    /* Approximate duration of Wait For Init loop */
    const uint32_t intrInitLoopDuration = 5uL;

    /* Wait For Init watchdog timeout in microseconds */
    const uint32_t initWatchdogTimeUs = CY_CAPSENSE_CSX_PRECHARGE_WATCHDOG_TIME_US;

    /* Configure the HW sequencer to perform the coarse initialization. */
    context->ptrCommonConfig->ptrCsdBase->CONFIG = context->ptrInternalContext->csxRegConfigInit;
    context->ptrCommonConfig->ptrCsdBase->HSCMP = CY_CAPSENSE_PRECHARGE_CSD_HSCMP_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_HS_P_SEL = CY_CAPSENSE_PRECHARGE_CSD_SW_HS_P_SEL_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_HS_N_SEL = CY_CAPSENSE_PRECHARGE_CSD_SW_HS_N_SEL_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_DSI_SEL = CY_CAPSENSE_PRECHARGE_CSD_SW_DSI_SEL_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_SHIELD_SEL = CY_CAPSENSE_PRECHARGE_CSD_SW_SHIELD_SEL_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_FW_MOD_SEL = CY_CAPSENSE_PRECHARGE_CSD_SW_FW_MOD_SEL_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_FW_TANK_SEL = CY_CAPSENSE_PRECHARGE_CSD_SW_FW_TANK_SEL_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_RES = context->ptrInternalContext->csxRegSwResPrech;
    context->ptrCommonConfig->ptrCsdBase->SEQ_START = CY_CAPSENSE_PRECHARGE_CSD_SEQ_START_CFG;

    /* Init Watchdog Counter to prevent a hang */
    cpuFreqMHz = context->ptrCommonConfig->cpuClkHz / CY_CAPSENSE_CONVERSION_MEGA;
    watchdogCounter = Cy_CapSense_WatchdogCyclesNum(initWatchdogTimeUs, cpuFreqMHz, intrInitLoopDuration);

    /* Approximate duration of Wait For Init loop */
    while((0u != (CY_CAPSENSE_CSD_SEQ_START_START_MSK &
        context->ptrCommonConfig->ptrCsdBase->SEQ_START)))
    {
        if(0uL == watchdogCounter)
        {
            break;
        }

        watchdogCounter--;
    }


    /* Reset the sequencer to the IDLE state if HSCMP not triggered till watchdog period is out. */
    if(0u != (CY_CAPSENSE_CSD_SEQ_START_START_MSK & context->ptrCommonConfig->ptrCsdBase->SEQ_START))
    {
        context->ptrCommonConfig->ptrCsdBase->SEQ_START = CY_CAPSENSE_DEFAULT_CSD_SEQ_START_CFG;
    }

    /* Configure the HW sequencer to perform the normal conversion. */
    context->ptrCommonConfig->ptrCsdBase->CONFIG = context->ptrInternalContext->csxRegConfigScan;
    context->ptrCommonConfig->ptrCsdBase->CSDCMP = CY_CAPSENSE_PRESCAN_CSD_CSDCMP_CFG;
    context->ptrCommonConfig->ptrCsdBase->HSCMP = CY_CAPSENSE_DEFAULT_CSD_HSCMP_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_HS_P_SEL = CY_CAPSENSE_DEFAULT_CSD_SW_HS_P_SEL_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_HS_N_SEL = CY_CAPSENSE_DEFAULT_CSD_SW_HS_N_SEL_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_DSI_SEL = CY_CAPSENSE_DEFAULT_CSD_SW_DSI_SEL_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_SHIELD_SEL = CY_CAPSENSE_DEFAULT_CSD_SW_SHIELD_SEL_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_FW_MOD_SEL = CY_CAPSENSE_DEFAULT_CSD_SW_FW_MOD_SEL_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_FW_TANK_SEL = CY_CAPSENSE_DEFAULT_CSD_SW_FW_TANK_SEL_CFG;
    context->ptrCommonConfig->ptrCsdBase->SW_RES = context->ptrInternalContext->csxRegSwResScan;

    /* Clear all pending interrupts of the CSD HW block */
    context->ptrCommonConfig->ptrCsdBase->INTR = CY_CAPSENSE_CSD_INTR_ALL_MSK;
    (void)context->ptrCommonConfig->ptrCsdBase->INTR;

    /* Start the normal conversion */
    context->ptrCommonConfig->ptrCsdBase->SEQ_START = CY_CAPSENSE_SCAN_CSD_SEQ_START_CFG;
}


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_MULTI_FREQUENCY_SCAN_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_CSXInitNextChScan
****************************************************************************//**
*
* This function initializes the next frequency of the sensor scan.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_CSXInitNextChScan(cy_stc_capsense_context_t * context)
{
    cy_stc_active_scan_sns_t * ptrActive = context->ptrActiveScanSns;

        ptrActive->mfsChannelIndex++;
        ptrActive->ptrSnsContext += context->ptrCommonConfig->numSns;

        Cy_CapSense_CSXSetSnsClkFreq((uint32_t)ptrActive->mfsChannelIndex, context);
        Cy_CapSense_CSXConnectTxExt(context);
        Cy_CapSense_CSXSetUpIdacs(context);
        Cy_CapSense_CSXStartSample(context);
}
#endif


/*******************************************************************************
* Function Name: Cy_CapSense_CSXSetSnsClkFreq
****************************************************************************//**
*
* Calculates sensor frequency depending on the specified frequency channel
* and configures the CSD HW block. If the multi-frequency scan feature is
* disabled, the function sets the snsClk divider and clock source
* from the active widget context structure.
*
* \param channelIndex
* Specifies frequency index.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
static void Cy_CapSense_CSXSetSnsClkFreq(uint32_t channelIndex, cy_stc_capsense_context_t * context)
{
    uint32_t tmpRegVal;
    uint32_t snsClkDivider;

    /* SnsClk setup */
    snsClkDivider = (uint32_t) context->ptrActiveScanSns->ptrWdContext->snsClk;

    /* Check divider value */
    if (0u == snsClkDivider)
    {
        snsClkDivider = 1u;
    }

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_MULTI_FREQUENCY_SCAN_EN)
        /* Change the divider based on the chId */
        switch (channelIndex)
        {
            case CY_CAPSENSE_MFS_CH1_INDEX:
                snsClkDivider += context->ptrCommonConfig->csxMfsDividerOffsetF1;
                break;

            case CY_CAPSENSE_MFS_CH2_INDEX:
                snsClkDivider += context->ptrCommonConfig->csxMfsDividerOffsetF2;
                break;

            default:
                /* No action for other indexes */
                break;

        }
    #else
        (void) channelIndex;
    #endif

    tmpRegVal = (uint32_t)context->ptrActiveScanSns->ptrWdContext->snsClkSource & (uint32_t)~((uint32_t)CY_CAPSENSE_CLK_SOURCE_AUTO_MASK);
    tmpRegVal = ((tmpRegVal << CY_CAPSENSE_CSD_SENSE_PERIOD_LFSR_SIZE_POS) | (snsClkDivider - 1u) |
            CY_CAPSENSE_CSD_SENSE_PERIOD_LFSR_CLEAR_MSK | CY_CAPSENSE_CSD_SENSE_PERIOD_LFSR_BITS_MSK);
    /* Update reg value with divider and configuration */
    context->ptrCommonConfig->ptrCsdBase->SENSE_PERIOD = tmpRegVal;

}

#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

#endif /* (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2)) */


/* [] END OF FILE */
