/***************************************************************************//**
* \file cy_capsense_sensing.c
* \version 3.0
*
* \brief
* This file consists of common parts for different supported platforms
* like fourth and fifth generation platforms.
*
********************************************************************************
* \copyright
* Copyright 2021, Cypress Semiconductor Corporation (an Infineon company)
* or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "cy_capsense_common.h"
#include "cycfg_capsense_defines.h"
#include "cy_capsense_structure.h"
#include "cy_capsense_sensing.h"
#include "cy_gpio.h"
#if (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN)
    #include "cy_capsense_sensing_v2.h"
#else /* (CY_CAPSENSE_PSOC4_FIFTH_GEN) */
    #include "cy_capsense_sensing_v3.h"
    #include "cy_capsense_generator_v3.h"
#endif

#if (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3))


/*******************************************************************************
* Function Name: Cy_CapSense_ScanWidget
****************************************************************************//**
*
* Initiates the scanning of all sensors in the widget. Scanning is
* initiated only if no scan is in progress. Scan finishing can be
* checked by the Cy_CapSense_IsBusy() function.
*
* \note
* For the fifth-generation CAPSENSE&trade; this function is available in
* single-channel solution only. It is recommended to use
* the Cy_CapSense_ScanSlots() function instead for compatibility with
* further CAPSENSE&trade; middleware versions.
*
* \param widgetId
* Specifies the ID number of the widget. A macro for the widget ID can be found
* in the cycfg_capsense.h file defined as CY_CAPSENSE_<WIDGET_NAME>_WDGT_ID.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the operation \ref cy_capsense_status_t.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_ScanWidget(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context)
{
    #if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
        return Cy_CapSense_ScanWidget_V3(widgetId, context);
    #else /* (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN) */
        return Cy_CapSense_ScanWidget_V2(widgetId, context);
    #endif /* (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN) */
}

/*******************************************************************************
* Function Name: Cy_CapSense_ScanSensor
****************************************************************************//**
*
* Initiates the scanning of the selected sensor in the widget. Scanning is
* initiated only if no scan is in progress. Scan finishing can be
* checked by the Cy_CapSense_IsBusy() function.
*
* \note
* For the fifth-generation CAPSENSE&trade; this function is available in
* single-channel solution. It is recommended to use
* the Cy_CapSense_ScanSlots() function instead for compatibility with
* further CAPSENSE&trade; middleware versions.
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
* Returns the status of the operation \ref cy_capsense_status_t.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_ScanSensor(
                uint32_t widgetId,
                uint32_t sensorId,
                cy_stc_capsense_context_t * context)
{
    #if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
        return Cy_CapSense_ScanSensor_V3(widgetId, sensorId, context);
    #else /* (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN) */
        return Cy_CapSense_ScanSensor_V2(widgetId, sensorId, context);
    #endif /* (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN) */
}


/*******************************************************************************
* Function Name: Cy_CapSense_ScanAllWidgets
****************************************************************************//**
*
* Initiates scanning of all enabled widgets (and sensors) in the project.
* Scanning is initiated only if no scan is in progress.
*
* This function initiates a scan only for the first sensor in the first widget
* for the fourth-generation CAPSENSE&trade; or a scan for the first slot
* for the fifth-generation CAPSENSE&trade; and then exits the function. The scan
* for the remaining sensors(slots) are initiated in the interrupt-driven mode
* in the interrupt service routine (part of middleware) triggered at the end
* of each scan completion or by DMA controllers in the DMA mode. The status
* of the current scan should be checked by using the Cy_CapSense_IsBusy() and wait
* until all scans is finished prior to starting a next scan or initializing
* another widget.
*
* \note
* For the fifth-generation CAPSENSE&trade; it is recommended to use
* the Cy_CapSense_ScanAllSlots() function instead for compatibility with
* further CAPSENSE&trade; middleware versions.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the operation \ref cy_capsense_status_t.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_ScanAllWidgets(
                cy_stc_capsense_context_t * context)
{
    #if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
        return Cy_CapSense_ScanAllWidgets_V3(context);
    #else /* (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN) */
        return Cy_CapSense_ScanAllWidgets_V2(context);
    #endif /* (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN) */
}


/*******************************************************************************
* Function Name: Cy_CapSense_IsBusy
****************************************************************************//**
*
* This function returns a status of the CAPSENSE&trade; middleware whether a scan is
* currently in progress or not.
*
* If the middleware is busy, a new scan or setup widgets should not be initiated.
*
* Use the Cy_CapSense_MwState() function to check a detailed CAPSENSE&trade; middleware
* state for the fifth-generation CAPSENSE&trade;.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the middleware as a sum of the masks.
* - CY_CAPSENSE_NOT_BUSY                - No scan is in progress and
*                                         a next scan can be initiated.
* - CY_CAPSENSE_BUSY                    - The previously initiated scan is
*                                         in progress.
*
*******************************************************************************/
uint32_t Cy_CapSense_IsBusy(
                const cy_stc_capsense_context_t * context)
{
    #if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
        return Cy_CapSense_IsBusy_V3(context);
    #else /* (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN) */
        return Cy_CapSense_IsBusy_V2(context);
    #endif /* (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN) */
}


/*******************************************************************************
* Function Name: Cy_CapSense_InterruptHandler
****************************************************************************//**
*
* Implements interrupt service routine for CAPSENSE&trade; Middleware.
*
* The MSC HW block generates an interrupt at end of every sensor scan.
* The CAPSENSE&trade; middleware uses this interrupt to implement a
* non-blocking sensor scan method, in which only the first sensor scan is
* initiated by the application program and subsequent sensor scans are
* initiated in the interrupt service routine as soon as the current scan
* is completed. The above stated interrupt service routine is implemented
* as a part of the CAPSENSE&trade; middleware.
*
* The CAPSENSE&trade; middleware does not initialize or modify the priority
* of interrupts. For the operation of middleware, the application program
* must configure MSC interrupt and assign interrupt vector to
* the Cy_CapSense_InterruptHandler() function. Refer to function
* usage example for details.
*
* The calls of the Start Sample and End Of Scan callbacks
* (see the \ref group_capsense_callbacks section for details) are the part of the
* Cy_CapSense_InterruptHandler() routine and they lengthen its execution. These
* callbacks will lengthen the ISR execution in case of a direct call of the
* Cy_CapSense_InterruptHandler() function from a ISR.
*
* \param base
* The pointer to the base register address of the CSD HW block.
* This argument is kept for uniformity and backward compatibility
* and is not used. The function can be called with value NULL.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
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
void Cy_CapSense_InterruptHandler(
                void * base,
                cy_stc_capsense_context_t * context)
{
    (void)base;
    #if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
        Cy_CapSense_InterruptHandler_V3(NULL, context);
    #else /* (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN) */
        Cy_CapSense_InterruptHandler_V2(NULL, context);
    #endif /* (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN) */
}


/*******************************************************************************
* Function Name: Cy_CapSense_CalibrateAllWidgets
****************************************************************************//**
*
* Executes the CapDAC/IDAC calibration for all the sensors in all widgets in
* the middleware to default target value.
*
* This function detects the sensing method used by each widget and performs
* a successive approximation search algorithm to find the appropriate modulator
* and compensation CapDAC/IDAC (if enabled) values for all sensors in CSD widgets
* and/or IDAC values for all sensors in CSX widgets to make sensor raw count
* to the default value level.
*
* This function could be used only if Enable auto-calibration parameter
* is enabled for CSD and/or CSX widgets.
*
* \note
* For the fifth-generation CAPSENSE&trade; this function is available in
* single-channel solution. It is recommended to use
* the Cy_CapSense_CalibrateAllSlots() function instead for compatibility with
* further CAPSENSE&trade; middleware versions.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the operation \ref cy_capsense_status_t.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_CalibrateAllWidgets(
                cy_stc_capsense_context_t * context)
{
    #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CALIBRATION_EN) || \
         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN))
        #if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
            return Cy_CapSense_CalibrateAllWidgets_V3(context);
        #else /* (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN) */
            return Cy_CapSense_CalibrateAllWidgets_V2(context);
        #endif /* (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN) */
    #else
        (void)context;
        return CY_CAPSENSE_STATUS_BAD_CONFIG;
    #endif
}

#if (((CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN) && (1u == CY_CAPSENSE_TOTAL_CH_NUMBER)) || (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN))
/*******************************************************************************
* Function Name: Cy_CapSense_CalibrateWidget
****************************************************************************//**
*
* Executes the CapDAC/IDAC calibration for all the sensors in the specified
* widget to the default target value.
*
* This function performs exactly the same tasks as
* Cy_CapSense_CalibrateAllWidgets(), but only for a specified widget.
*
* \note
* For the fifth-generation CAPSENSE&trade; this function is available in
* single-channel solution. It is recommended to use
* the Cy_CapSense_CalibrateAllSlots() function instead for compatibility with
* further CAPSENSE&trade; middleware versions.
*
* \param widgetId
* Specifies the ID number of the widget. A macro for the widget ID can be found
* in the cycfg_capsense.h file defined as CY_CAPSENSE_<WIDGET_NAME>_WDGT_ID.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the operation \ref cy_capsense_status_t.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_CalibrateWidget(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context)
{
    #if ((CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_CALIBRATION_EN) || \
         (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_CALIBRATION_EN))
        #if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
            return Cy_CapSense_CalibrateWidget_V3(widgetId, context);
        #else /* (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN) */
            return Cy_CapSense_CalibrateWidget_V2(widgetId, context);
        #endif /* (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN) */
    #else
        (void)widgetId;
        (void)context;
        return CY_CAPSENSE_STATUS_BAD_CONFIG;
    #endif
}
#endif /* (((CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN) && (1u == CY_CAPSENSE_TOTAL_CH_NUMBER)) || (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN)) */


#if (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN || \
 ((CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN) && (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_AMUX_SENSOR_CONNECTION_METHOD)))
/*******************************************************************************
* Function Name: Cy_CapSense_SetPinState
****************************************************************************//**
*
* Sets the state (drive mode and HSIOM state) of the GPIO used by a sensor.
*
* The possible states are GND, Shield, High-Z, Tx, Negative Tx, Rx, and Sensor.
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
* the Cy_CapSense_SetPinState() function should be called in StartSample
* callback (see the \ref group_capsense_callbacks section for details)
* or with low-level functions that perform a single-sensor scanning.
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
* 1. CY_CAPSENSE_GROUND          - The pin is connected to the ground.
* 2. CY_CAPSENSE_HIGHZ           - The drive mode of the pin is set to High-Z
*                                  Analog.
* 3. CY_CAPSENSE_SHIELD          - The shield signal is routed to the pin
*                                  (available only if CSD sensing method with
*                                  shield electrode is enabled).
* 4. CY_CAPSENSE_SENSOR          - The pin is connected to the scanning bus
*                                  (available only if CSD sensing method
*                                   is enabled).
* 5. CY_CAPSENSE_TX_PIN          - The Tx signal is routed to the sensor
*                                  (available only if CSX sensing method
*                                   is enabled).
* 6. CY_CAPSENSE_RX_PIN          - The pin is connected to the scanning bus
*                                  (available only if CSX sensing method
*                                   is enabled).
* 7. CY_CAPSENSE_NEGATIVE_TX_PIN - The Negative Tx signal is routed to the sensor
*                                  (available only if CSD sensing method
*                                   is enabled).
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return status
* Returns the operation status:
* - CY_CAPSENSE_STATUS_SUCCESS   - Indicates the successful electrode setting.
* - CY_CAPSENSE_STATUS_BAD_PARAM - 1) widgetID, sensorElement or state
*                                     are not valid;
*                      2) the CSD sensing method is disabled for desired
*                         CY_CAPSENSE_SHIELD or CY_CAPSENSE_SENSOR states;
*                      3) the CSX sensing method is disabled for desired
*                         CY_CAPSENSE_TX_PIN, CY_CAPSENSE_NEGATIVE_TX_PIN or
*                         CY_CAPSENSE_RX_PIN states.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_SetPinState(
                uint32_t widgetId,
                uint32_t sensorElement,
                uint32_t state,
                const cy_stc_capsense_context_t * context)
{
    #if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
        return Cy_CapSense_SetPinState_V3(widgetId, sensorElement, state, context);
    #else /* (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN) */
        return Cy_CapSense_SetPinState_V2(widgetId, sensorElement, state, context);
    #endif
}
#endif


/*******************************************************************************
* Function Name: Cy_CapSense_SetInactiveElectrodeState
****************************************************************************//**
*
* Sets a desired state for all inactive CAPSENSE&trade;-related electrodes for CSD
* or CSX scans.
*
* Use the function to set/change the desired state of all CAPSENSE&trade;-related
* electrodes which are not scanned during regular scans or BIST capacitance
* measurements. There are separate states for the CSX
* sensing method group, the CSD sensing method group, the BIST CSD sensor
* (electrode) capacitance measurement, the BIST CSX sensor
* (electrode) capacitance measurement, and the BIST shield electrode
* capacitance measurement. For instance, it can be configured the GND state
* for all inactive sensors for CSX scanning and the High-Z state for CSD
* scanning and the Shield state for BIST CSD sensor (electrode) capacitance
* measurement.
* The function updates some corresponding parameters in the CAPSENSE&trade; Data
* Structure to provide the desired state and not changes pin state immediately.
* The desired state will be applied to all inactive electrodes
* during the CSD or CSX scans or BIST capacitance measurements.
* It is not recommended to update the Data Structure registers directly.
* Additionally (only for fifth-generation CAPSENSE&trade;), the function recalculates
* sensor frames in a case of the CTRLMUX sensor connection method.
*
* \param  inactiveState
* Specifies the inactive CAPSENSE&trade; electrode state:
* - CY_CAPSENSE_SNS_CONNECTION_HIGHZ
* - CY_CAPSENSE_SNS_CONNECTION_SHIELD (only for CSD scan)
* - CY_CAPSENSE_SNS_CONNECTION_GROUND
*
* \param sensingGroup
* Specifies the sensing group:
* - CY_CAPSENSE_CSD_GROUP
* - CY_CAPSENSE_CSX_GROUP
* - CY_CAPSENSE_BIST_CSD_GROUP
* - CY_CAPSENSE_BIST_CSX_GROUP
* - CY_CAPSENSE_BIST_SHIELD_GROUP
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns the status of the operation \ref cy_capsense_status_t.
*
*******************************************************************************/
cy_capsense_status_t Cy_CapSense_SetInactiveElectrodeState(
             uint32_t inactiveState,
             uint32_t sensingGroup,
             cy_stc_capsense_context_t * context)
{
    cy_capsense_status_t capStatus = CY_CAPSENSE_STATUS_BAD_PARAM;

    #if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
        uint32_t curChIndex;
    #endif

    #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN)
        cy_en_capsense_bist_io_state_t inactiveStateEn;
    #endif

    if (NULL != context)
    {
        context->ptrActiveScanSns->currentSenseMethod = CY_CAPSENSE_UNDEFINED_GROUP;
        #if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
            (void) Cy_CapSense_SwitchHwConfiguration(CY_CAPSENSE_HW_CONFIG_UNDEFINED, context);
        #endif

        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
            if ((CY_CAPSENSE_CSD_GROUP == sensingGroup) &&
                ((CY_CAPSENSE_SNS_CONNECTION_GROUND == inactiveState) ||
                 (CY_CAPSENSE_SNS_CONNECTION_HIGHZ == inactiveState) ||
                 (CY_CAPSENSE_SNS_CONNECTION_SHIELD == inactiveState)))
            {
                if(context->ptrInternalContext->intrCsdInactSnsConn != (uint8_t)inactiveState)
                {
                    context->ptrInternalContext->intrCsdInactSnsConn = (uint8_t)inactiveState;
                    Cy_CapSense_SetCsdInactiveState(context);
                }
                capStatus = CY_CAPSENSE_STATUS_SUCCESS;
            }
        #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */

        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
            #if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
                if ((CY_CAPSENSE_CSX_GROUP == sensingGroup) &&
                    ((CY_CAPSENSE_SNS_CONNECTION_GROUND == inactiveState) ||
                     (CY_CAPSENSE_SNS_CONNECTION_HIGHZ == inactiveState) ||
                     ((CY_CAPSENSE_SNS_CONNECTION_VDDA_BY_2 == inactiveState))))
                {
                    if(context->ptrInternalContext->intrCsxInactSnsConn != (uint8_t)inactiveState)
                    {
                        /* There are MSC HW modules that should be enabled and the MSC HW internal switches
                         * that should be closed only if VDDA/2 Inactive Sensor Connection is used. These
                         * modules and switches are part of the Base configuration of the MSC HW block.
                         * The code below is intended to generate the Base MSC HW configuration depending
                         * on the Inactive Sensor Connection selection.
                        */
                        if((CY_CAPSENSE_SNS_CONNECTION_VDDA_BY_2 == context->ptrInternalContext->intrCsxInactSnsConn) ||
                           (CY_CAPSENSE_SNS_CONNECTION_VDDA_BY_2 == inactiveState))
                        {
                            context->ptrInternalContext->intrCsxInactSnsConn = (uint8_t)inactiveState;

                            for (curChIndex = 0u; curChIndex < CY_CAPSENSE_TOTAL_CH_NUMBER; curChIndex++)
                            {
                                /* Generate base frame configurations for all enabled MSC channels, depending on
                                 * the Inactive Sensor Connection selection.
                                 */
                                capStatus = Cy_CapSense_GenerateBaseConfig(curChIndex, context);

                                if (CY_CAPSENSE_STATUS_SUCCESS != capStatus)
                                {
                                    break;
                                }
                            }
                        }
                        else
                        {
                            context->ptrInternalContext->intrCsxInactSnsConn = (uint8_t)inactiveState;
                        }

                        Cy_CapSense_SetCsxInactiveState(context);
                    }
                    capStatus = CY_CAPSENSE_STATUS_SUCCESS;
                }
            #else
                if ((CY_CAPSENSE_CSX_GROUP == sensingGroup) &&
                    ((CY_CAPSENSE_SNS_CONNECTION_GROUND == inactiveState) ||
                     (CY_CAPSENSE_SNS_CONNECTION_HIGHZ == inactiveState)))
                 {
                    if(context->ptrInternalContext->intrCsxInactSnsConn != (uint8_t)inactiveState)
                    {
                        context->ptrInternalContext->intrCsxInactSnsConn = (uint8_t)inactiveState;
                        Cy_CapSense_SetCsxInactiveState(context);
                    }

                    capStatus = CY_CAPSENSE_STATUS_SUCCESS;
                 }
            #endif /* (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN) */
        #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

        #if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN)
            switch(inactiveState)
            {
                case CY_CAPSENSE_SNS_CONNECTION_GROUND:
                    inactiveStateEn = CY_CAPSENSE_BIST_IO_STRONG_E;
                    break;
                case CY_CAPSENSE_SNS_CONNECTION_HIGHZ:
                    inactiveStateEn = CY_CAPSENSE_BIST_IO_HIGHZA_E;
                    break;
                case CY_CAPSENSE_SNS_CONNECTION_SHIELD:
                    inactiveStateEn = CY_CAPSENSE_BIST_IO_SHIELD_E;
                    break;
                default:
                    inactiveStateEn = CY_CAPSENSE_BIST_IO_UNDEFINED_E;
                    break;
            }

            if ((CY_CAPSENSE_BIST_CSD_GROUP == sensingGroup) &&
                ((CY_CAPSENSE_SNS_CONNECTION_GROUND == inactiveState) ||
                 (CY_CAPSENSE_SNS_CONNECTION_HIGHZ == inactiveState) ||
                 (CY_CAPSENSE_SNS_CONNECTION_SHIELD == inactiveState)))
            {
                if(context->ptrBistContext->intrEltdCapCsdISC != inactiveStateEn)
                {
                    context->ptrBistContext->intrEltdCapCsdISC = inactiveStateEn;
                }
                capStatus = CY_CAPSENSE_STATUS_SUCCESS;
            }

            if ((CY_CAPSENSE_BIST_CSX_GROUP == sensingGroup) &&
                ((CY_CAPSENSE_SNS_CONNECTION_GROUND == inactiveState) ||
                 (CY_CAPSENSE_SNS_CONNECTION_HIGHZ == inactiveState)))
            {
                if(context->ptrBistContext->intrEltdCapCsxISC != inactiveStateEn)
                {
                    context->ptrBistContext->intrEltdCapCsxISC = inactiveStateEn;
                }
                capStatus = CY_CAPSENSE_STATUS_SUCCESS;
            }

            if ((CY_CAPSENSE_BIST_SHIELD_GROUP == sensingGroup) &&
                ((CY_CAPSENSE_SNS_CONNECTION_GROUND == inactiveState) ||
                 (CY_CAPSENSE_SNS_CONNECTION_HIGHZ == inactiveState) ||
                 (CY_CAPSENSE_SNS_CONNECTION_SHIELD == inactiveState)))
            {
                if(context->ptrBistContext->intrEltdCapShieldISC != inactiveStateEn)
                {
                    context->ptrBistContext->intrEltdCapShieldISC = inactiveStateEn;
                }
                capStatus = CY_CAPSENSE_STATUS_SUCCESS;
            }
        #endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) */

        #if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
            for (curChIndex = 0u; curChIndex < CY_CAPSENSE_TOTAL_CH_NUMBER; curChIndex++)
            {
                context->ptrActiveScanSns[curChIndex].currentSenseMethod = CY_CAPSENSE_UNDEFINED_GROUP;

                #if (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD)
                    if ((CY_CAPSENSE_STATUS_SUCCESS == capStatus) &&
                        ((CY_CAPSENSE_CSD_GROUP == sensingGroup) ||
                         (CY_CAPSENSE_CSX_GROUP == sensingGroup)))
                    {
                        Cy_CapSense_GenerateAllSensorConfig(curChIndex, &context->ptrSensorFrameContext[(CY_CAPSENSE_SLOT_COUNT *
                                    (curChIndex + context->ptrCommonConfig->channelOffset)) * CY_MSC_6_SNS_REGS], context);
                    }
                #endif /* (CY_CAPSENSE_SENSOR_CONNECTION_MODE == CY_CAPSENSE_CTRLMUX_SENSOR_CONNECTION_METHOD) */

            }
        #endif
    }
    return (capStatus);
}


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_SetCsdInactiveState
****************************************************************************//**
*
* Sets a desired pin state for all inactive CAPSENSE&trade;-related electrodes for CSD
* scans.
*
* There is the internal function and it is not recommended to call it directly
* from the application program. The function sets the desired state of all
* CSD group CAPSENSE&trade;-related electrodes which are not scanned.
* The function updates some corresponding parameters in the CAPSENSE&trade; Data
* Structure to provide the desired state and not changes pin state immediately.
* The desired state will be applied to all inactive electrodes during the CSD scan.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_SetCsdInactiveState(
             cy_stc_capsense_context_t * context)
{
    context->ptrInternalContext->csdInactiveSnsHsiom = CY_CAPSENSE_HSIOM_SEL_GPIO;
    switch (context->ptrInternalContext->intrCsdInactSnsConn)
    {
        case CY_CAPSENSE_SNS_CONNECTION_HIGHZ:
            context->ptrInternalContext->csdInactiveSnsDm = CY_CAPSENSE_DM_GPIO_ANALOG;
            break;

        case CY_CAPSENSE_SNS_CONNECTION_SHIELD:
            context->ptrInternalContext->csdInactiveSnsHsiom = CY_CAPSENSE_HSIOM_SEL_CSD_SHIELD;
            #if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
                if (CY_CAPSENSE_SHIELD_ACTIVE == context->ptrCommonConfig->csdShieldMode)
                {
                    context->ptrInternalContext->csdInactiveSnsDm = CY_CAPSENSE_DM_GPIO_ANALOG;
                }
                else
                {
                    context->ptrInternalContext->csdInactiveSnsDm = CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF;
                }
            #endif

            #if (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN)
                context->ptrInternalContext->csdInactiveSnsDm = CY_CAPSENSE_DM_SHIELD;
            #endif
            break;

        case CY_CAPSENSE_SNS_CONNECTION_GROUND:
            /* CY_CAPSENSE_SNS_CONNECTION_GROUND */
            context->ptrInternalContext->csdInactiveSnsDm = CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF;
            break;

        default:
            /* Set the default pin state: High-Z */
            context->ptrInternalContext->csdInactiveSnsDm = CY_CAPSENSE_DM_GPIO_ANALOG;
            break;
    }
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSD_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_SetCsxInactiveState
****************************************************************************//**
*
* Sets a desired pin state for all inactive CAPSENSE&trade;-related electrodes for CSX
* scans.
*
* There is the internal function and it is not recommended to call it directly
* from the application program. The function sets the desired state of all
* CSX group CAPSENSE&trade;-related electrodes which are not scanned.
* The function updates some corresponding parameters in the CAPSENSE&trade; Data
* Structure to provide the desired state and not changes pin state immediately.
* The desired state will be applied to all inactive electrodes during the CSX scan.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_SetCsxInactiveState(
             cy_stc_capsense_context_t * context)
{
    context->ptrInternalContext->csxInactiveSnsHsiom = CY_CAPSENSE_HSIOM_SEL_GPIO;
    switch (context->ptrInternalContext->intrCsxInactSnsConn)
    {
        case CY_CAPSENSE_SNS_CONNECTION_HIGHZ:
            context->ptrInternalContext->csxInactiveSnsDm = CY_CAPSENSE_DM_GPIO_ANALOG;
            break;
        case CY_CAPSENSE_SNS_CONNECTION_GROUND:
            /* CY_CAPSENSE_SNS_CONNECTION_GROUND */
            context->ptrInternalContext->csxInactiveSnsDm = CY_CAPSENSE_DM_GPIO_STRONG_IN_OFF;
            break;
        case CY_CAPSENSE_SNS_CONNECTION_VDDA_BY_2:
            /* CY_CAPSENSE_SNS_CONNECTION_VDDA_BY_2 */
            context->ptrInternalContext->csxInactiveSnsHsiom = CY_CAPSENSE_HSIOM_SEL_AMUXB;
            context->ptrInternalContext->csxInactiveSnsDm = CY_CAPSENSE_DM_GPIO_ANALOG;
            break;
        default:
            /* Set the default pin state: High-Z */
            context->ptrInternalContext->csdInactiveSnsDm = CY_CAPSENSE_DM_GPIO_ANALOG;
            break;
    }
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_CSX_EN) */

#endif /* (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3)) */
/* [] END OF FILE */
