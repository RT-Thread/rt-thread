/***************************************************************************//**
* \file cy_capsense_selftest.c
* \version 3.0
*
* \brief
* This file provides the source code to the Built-in Self-test (BIST)
* functions.
*
********************************************************************************
* \copyright
* Copyright 2021, Cypress Semiconductor Corporation (an Infineon company)
* or an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include <stddef.h>
#include <string.h>
#include "cy_capsense_selftest.h"

#if (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3))

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN)

/*******************************************************************************
* Function Name: Cy_CapSense_RunSelfTest
****************************************************************************//**
*
* Runs built-in self-tests specified by the test enable mask.
*
* The function performs various self-tests on all the enabled widgets
* and sensors in the project. Select the required set of tests
* using the bit-mask in testEnMask parameter.
*
* Use CY_CAPSENSE_BIST_RUN_AVAILABLE_SELF_TEST_MASK to execute
* all the self-tests or any combination of the masks
* (defined in testEnMask parameter) to specify the desired test list.
*
* To execute a single-element test (i.e. for one widget or one sensor),
* the following low-level functions are available:
* for the fourth-generation CAPSENSE&trade;:
* - Cy_CapSense_CheckCRCWidget()
* - Cy_CapSense_CheckIntegritySensorPins()
* - Cy_CapSense_MeasureCapacitanceSensor()
* - Cy_CapSense_MeasureCapacitanceShield()
* - Cy_CapSense_MeasureCapacitanceCap()
* - Cy_CapSense_MeasureVdda()
* for the fifth-generation CAPSENSE&trade;:
* - Cy_CapSense_CheckCRCWidget()
* - Cy_CapSense_CheckIntegritySensorPins()
* - Cy_CapSense_MeasureCapacitanceSensorElectrode()
* - Cy_CapSense_MeasureCapacitanceSlotSensors()
* - Cy_CapSense_MeasureCapacitanceShieldElectrode()
*
* Refer to these functions descriptions for detail information
* on the corresponding test.
*
* \param testEnMask
* Specifies the tests to be executed. Each bit corresponds to one test. It is
* possible to launch the function with any combination of the available tests.
* - CY_CAPSENSE_BIST_CRC_WDGT_MASK       - Verifies the RAM widget structure CRC
*                                          for all the widgets.
* - CY_CAPSENSE_BIST_SNS_INTEGRITY_MASK  - Checks all the sensors for a short
*                                          to GND / VDD / other sensors.
* - CY_CAPSENSE_BIST_SNS_CAP_MASK        - Measures all the sensors capacitance.
* - CY_CAPSENSE_BIST_ELTD_CAP_MASK       - Measures all the electrodes capacitance
*                                          (only for the fifth-generation CAPSENSE&trade;).
* - CY_CAPSENSE_BIST_SHIELD_CAP_MASK     - Measures the shield capacitance.
* - CY_CAPSENSE_BIST_EXTERNAL_CAP_MASK   - Measures the capacitance of the available
*                                          external capacitors
*                                          (only for the fourth-generation CAPSENSE&trade;).
* - CY_CAPSENSE_BIST_VDDA_MASK           - Measures the VDDA voltage
*                                          (only for the fourth-generation CAPSENSE&trade;).
* - CY_CAPSENSE_BIST_RUN_AVAILABLE_SELF_TEST_MASK
*                                        - Executes all available tests.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a bit-mask with a status of execution of the specified tests:
* - CY_CAPSENSE_BIST_SUCCESS_E      - All the tests passed successfully.
* - CY_CAPSENSE_BIST_BAD_PARAM_E    - A non-defined test was requested in the
*                                     testEnMask parameter or the context is
*                                     a NULL pointer. The function
*                                     was not performed.
* - CY_CAPSENSE_BIST_HW_BUSY_E      - The CSD HW block is busy with a previous
*                                     operation. The function was not performed.
* - CY_CAPSENSE_BIST_ERROR_E        - An unexpected fault occurred during
*                                     the measurement, you may need to repeat
*                                     the measurement.
* - CY_CAPSENSE_BIST_FAIL_E         - Any of tests specified by the testEnMask
*                                     parameters has faulted.
*
*******************************************************************************/
cy_en_capsense_bist_status_t Cy_CapSense_RunSelfTest(
                uint32_t testEnMask,
                cy_stc_capsense_context_t * context)

{
    cy_en_capsense_bist_status_t result;

    #if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
        result = Cy_CapSense_RunSelfTest_V3(testEnMask, context);
    #else /* (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN) */
        result = Cy_CapSense_RunSelfTest_V2(testEnMask, context);
    #endif

    return (result);
}


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_CheckCRCWidget
****************************************************************************//**
*
* Checks the stored CRC of the \ref cy_stc_capsense_widget_context_t data
* structure of the specified widget.
*
* This function validates the data integrity of the
* \ref cy_stc_capsense_widget_context_t data structure of the specified widget
* by calculating the CRC and comparing it with the stored CRC value of the
* specified widget.
*
* Initially, after the device power up, the Cy_CapSense_Enable() function
* calculates CRC for each widget and stores them in the .ptrWdgtCrc[] array
* of the \ref cy_stc_capsense_bist_context_t structure. The test execution
* compares this stored CRC value with the newly calculated and if the stored
* and calculated CRC values differ:
* 1. The calculated CRC is stored to the .wdgtCrcCalc field
*    of the \ref cy_stc_capsense_bist_context_t data structure.
* 2. The widget ID is stored to the .crcWdgtId field.
* 3. The CY_CAPSENSE_BIST_CRC_WDGT_MASK bit is set in the .testResultMask field.
*
* The function never clears the CY_CAPSENSE_BIST_CRC_WDGT_MASK bit.
* If the CY_CAPSENSE_BIST_CRC_WDGT_MASK bit is set, the wdgtCrcCalc
* and .crcWdgtId fields are not updated.
*
* It is recommended to use the Cy_CapSense_SetParam() function to change
* the value of the \ref cy_stc_capsense_widget_context_t data structure elements
* as the CRC is updated by Cy_CapSense_SetParam() function.
*
* You can initiate this test by the Cy_CapSense_RunSelfTest() function with
* the CY_CAPSENSE_BIST_CRC_WDGT_MASK mask as an input.
*
* The function clears the CY_CAPSENSE_WD_WORKING_MASK bit of the .status
* field in \ref cy_stc_capsense_widget_context_t structure if the calculated
* CRC value differs to the stored CRC value.
* Those non-working widgets are skipped by the high-level scanning and
* processing functions. Restoring a widget to its working state should
* be done by the application level.
*
* For details of the used CRC algorithm, refer to the Cy_CapSense_GetCRC()
* function.
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
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E          - The stored CRC matches
*                                         the calculated CRC.
* - CY_CAPSENSE_BIST_FAIL_E             - The widget CRC differs to
*                                         the stored CRC.
* - CY_CAPSENSE_BIST_BAD_PARAM_E        - The input parameters are invalid.
*                                         The test was not executed.
*
*******************************************************************************/
cy_en_capsense_bist_status_t Cy_CapSense_CheckCRCWidget(
                uint32_t widgetId,
                cy_stc_capsense_context_t * context)
{
    cy_en_capsense_bist_status_t result;

    #if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
        result = Cy_CapSense_CheckCRCWidget_V3(widgetId, context);
    #else /* (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN) */
        result = Cy_CapSense_CheckCRCWidget_V2(widgetId, context);
    #endif

    return (result);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_WDGT_CRC_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_BSLN_INTEGRITY_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_CheckIntegritySensorBaseline
****************************************************************************//**
*
* Checks if the baseline of the specified sensor is not corrupted
* by comparing it with its inverse copy and checks if the baseline is
* within the specified range.
*
* The function checks whether or not the baseline binary inverted to
* its inverse copy is saved to the self-test baseline-inverse structure
* and is within the user-defined limits. If the baseline does
* not match its inverse copy or if the baseline is out of the user-defined
* limits, the function sets the CY_CAPSENSE_BIST_BSLN_INTEGRITY_MASK bit
* in the .testResultMask field of the \ref cy_stc_capsense_bist_context_t
* structure.
*
* The test is integrated into the CAPSENSE&trade; Middleware. All CAPSENSE&trade;
* processing functions like Cy_CapSense_ProcessAllWidgets()
* or Cy_CapSense_UpdateSensorBaseline() automatically verify the baseline
* value before using it and update its inverse copy after processing.
* If a baseline update fails, a CY_CAPSENSE_STATUS_BAD_DATA result
* is returned. The baseline initialization functions do not verify the
* baseline and update the baseline inverse copy.
*
* This function does not update the CY_CAPSENSE_WD_WORKING_MASK bit of
* the .status field in \ref cy_stc_capsense_widget_context_t structure
* and is not available in the Cy_CapSense_RunSelfTest() function.
*
* Use this function to verify the uniformity of sensors, for example, at
* mass-production or during an operation phase together with the
* Cy_CapSense_CheckIntegritySensorRawcount() function.
*
* \param widgetId
* Specifies the ID number of the widget.
* A macro for the widget ID can be found in the
* CAPSENSE&trade; Configuration header file (cycfg_capsense.h) defined as
* CY_CAPSENSE_<WidgetName>_WDGT_ID.
*
* \param sensorId
* Specifies the ID number of the sensor within the widget.
* A macro for the sensor ID within the specified widget can be found in
* the CAPSENSE&trade; Configuration header file (cycfg_capsense.h) defined as
* CY_CAPSENSE_<WidgetName>_SNS<SensorNumber>_ID.
*
* \param baselineHighLimit
* Specifies the upper limit for a baseline.
*
* \param baselineLowLimit
* Specifies the lower limit for a baseline.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E          - The baseline is within the
*                                         specified range.
* - CY_CAPSENSE_BIST_FAIL_E             - The test failed and the baseline
*                                         is not binary inverted to its inverse
*                                         copy or is out of the specified limits.
* - CY_CAPSENSE_BIST_BAD_PARAM_E        - The input parameter is invalid.
*                                         The test was not executed.
*
*******************************************************************************/
cy_en_capsense_bist_status_t Cy_CapSense_CheckIntegritySensorBaseline(
                uint32_t widgetId,
                uint32_t sensorId,
                uint16_t baselineHighLimit,
                uint16_t baselineLowLimit,
                cy_stc_capsense_context_t * context)
{
    cy_en_capsense_bist_status_t result;

    #if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
        result = Cy_CapSense_CheckIntegritySensorBaseline_V3(widgetId,
                                                            sensorId,
                                                            baselineHighLimit,
                                                            baselineLowLimit,
                                                            context);
    #else /* (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN) */
        result = Cy_CapSense_CheckIntegritySensorBaseline_V2(widgetId,
                                                            sensorId,
                                                            baselineHighLimit,
                                                            baselineLowLimit,
                                                            context);
    #endif

    return (result);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_BSLN_INTEGRITY_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_RAW_INTEGRITY_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_CheckIntegritySensorRawcount
****************************************************************************//**
*
* Checks the raw count of the specified widget/sensor is within the specified
* range.
*
* The raw count is within a specific range (based on the calibration target)
* for good units. The function checks whether or not the raw count is within
* the user-defined limits in the ranges function arguments.
* If the raw count is out of limits, this function sets the
* CY_CAPSENSE_BIST_RAW_INTEGRITY_MASK bit in the .testResultMask field of the
* \ref cy_stc_capsense_bist_context_t structure.
*
* This function does not update the CY_CAPSENSE_WD_WORKING_MASK bit of
* the .status field in \ref cy_stc_capsense_widget_context_t structure
* and is not available in the Cy_CapSense_RunSelfTest() function.
*
* Use this function to verify the uniformity of sensors, for example, at
* mass-production or during an operation phase together with the
* Cy_CapSense_CheckIntegritySensorBaseline() function.
*
* \param widgetId
* Specifies the ID number of the widget.
* A macro for the widget ID can be found in the
* CAPSENSE&trade; Configuration header file (cycfg_capsense.h) defined as
* CY_CAPSENSE_<WidgetName>_WDGT_ID.
*
* \param sensorId
* Specifies the ID number of the sensor within the widget.
* A macro for the sensor ID within the specified widget can be found in
* the CAPSENSE&trade; Configuration header file (cycfg_capsense.h) defined as
* CY_CAPSENSE_<WidgetName>_SNS<SensorNumber>_ID.
*
* \param rawcountHighLimit
* Specifies the upper limit for the widget/sensor raw count.
*
* \param rawcountLowLimit
* Specifies the lower limit for the widget/sensor raw count.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E          - The raw count is within the
*                                         specified range.
* - CY_CAPSENSE_BIST_FAIL_E             - The test failed and raw count is out
*                                         of the specified limits.
* - CY_CAPSENSE_BIST_BAD_PARAM_E        - The input parameter is invalid.
*                                         The test was not executed.
*
*******************************************************************************/
cy_en_capsense_bist_status_t Cy_CapSense_CheckIntegritySensorRawcount(
                uint32_t widgetId,
                uint32_t sensorId,
                uint16_t rawcountHighLimit,
                uint16_t rawcountLowLimit,
                cy_stc_capsense_context_t * context)
{
    cy_en_capsense_bist_status_t result;

    #if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
        result = Cy_CapSense_CheckIntegritySensorRawcount_V3(widgetId,
                                                            sensorId,
                                                            rawcountHighLimit,
                                                            rawcountLowLimit,
                                                            context);
    #else /* (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN) */
        result = Cy_CapSense_CheckIntegritySensorRawcount_V2(widgetId,
                                                            sensorId,
                                                            rawcountHighLimit,
                                                            rawcountLowLimit,
                                                            context);
    #endif

    return (result);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_RAW_INTEGRITY_EN) */


#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_SHORT_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_CheckIntegritySensorPins
****************************************************************************//**
*
* Checks the specified widget/sensor for shorts to GND, VDD or other sensors.
*
* This function performs several sub-tests to verify the specified sensor
* is not electrically shorted and is in a good condition to reliably detect
* user interactions.
*
* This function performs tests to check if the specified sensor is shorted to:
* * GND
* * VDD
* * Other GPIOs used by CAPSENSE&trade; (such as sensors, Tx, Rx,
*   shield electrodes, and external capacitors)
* * Other non-CAPSENSE&trade; GPIOs (only if they are configured
*   in a strong high or low state during the test execution).
*
* The absolute resistance of an electrical short must be less than 1500 Ohm
* including all series resistors on a sensor for a short to be detected
* to GND, VDD or GPIOs. For example, if a series resistor on a sensor is
* 560 Ohm (as recommended) and the sensor is shorted with another sensor,
* the function can detect a short with a short resistance up to 380 Ohm as
* there are two 560 ohm resistors between the shorted sensor GPIOs.
*
* The function executes the following flow to detect a short:
* * Configures all CAPSENSE&trade; controlled GPIOs to strong-drive-high,
*   and the specified sensor GPIO to resistive pull down mode.
* * Waits for a delay (defined by .snsIntgShortSettlingTime field
*   of the \ref cy_stc_capsense_bist_context_t structure) to get established
*   all transient processes.
* * Checks the status of the specified sensor for the expected state
*   (logic low).
* * Configures all CAPSENSE&trade; controlled GPIOs to strong-drive-low,
*   and the specified sensor GPIO to resistive pull up mode.
* * Waits for the above mentioned delay.
* * Checks the status of the specified sensor for the expected state
*   (logic high).
* * Stores the test result in the CAPSENSE&trade; Data Structure.
*   A short is reported only when the sensor status check returns
*   an unexpected state.
*
* Due to the sensor parasitic capacitance and internal pull-up/down resistance,
* logic high-to-low (and vice versa) transitions require a settling time before
* checking the sensor status. A 2us delay is used as a settling time and can
* be changed using the .snsIntgShortSettlingTime field
* of the cy_stc_capsense_bist_context_t structure.
*
* If a short is detected this function updates the following statuses:
* * The widget ID is stored to the .shortedWdId field
*   of the \ref cy_stc_capsense_bist_context_t structure.
* * The sensor ID is stored to the .shortedSnsId field
*   of the \ref cy_stc_capsense_bist_context_t structure.
* * The CY_CAPSENSE_BIST_SNS_INTEGRITY_MASK bit is set in the .testResultMask field
*   of the \ref cy_stc_capsense_bist_context_t structure.
* * If CY_CAPSENSE_BIST_SNS_INTEGRITY_MASK is already set due to a previously
*   detected fault on any of the sensor, this function does not update
*   the .shortedWdId and .shortedSnsId fields. For this reason,
*   clear the CY_CAPSENSE_BIST_SNS_INTEGRITY_MASK bit prior calling this function.
* * The widget is disabled by clearing the CY_CAPSENSE_WD_WORKING_MASK bit
*   in the .status field of the \ref cy_stc_capsense_widget_context_t structure
*   of the specified widget.
*   The disabled widget is ignored by high-level functions of scanning / data
*   processing. To restore the widget operation
*   the application layer should manually set the CY_CAPSENSE_WD_WORKING_MASK
*   bit.
*
* To check all the project sensors at once, use the Cy_CapSense_RunSelfTest()
* function with the CY_CAPSENSE_BIST_SNS_INTEGRITY_MASK mask.
*
* To detect an electrical short or fault condition with resistance
* higher than 1500 ohm, the Cy_CapSense_MeasureCapacitanceSensor() (4th Generation)
* or Cy_CapSense_MeasureCapacitanceSensorElectrode() (5th Generation) function can
* be used as the fault condition affects the measured sensor capacitance.
*
* This test can be executed only if the CAPSENSE&trade; Middleware is in the IDLE
* state. This function must not be called while CAPSENSE&trade; Middleware is busy.
*
* \param widgetId
* Specifies the ID number of the widget.
* A macro for the widget ID can be found in the
* CAPSENSE&trade; Configuration header file (cycfg_capsense.h) defined as
* CY_CAPSENSE_<WidgetName>_WDGT_ID.
*
* \param sensorId
* Specifies the ID of the sensor (electrode for CSX widgets) within the widget
* to be tested.
*
* For the CSD widgets, a macro for the sensor ID within the specified widget
* can be found in the CAPSENSE&trade; Configuration header file (cycfg_capsense.h)
* defined as CY_CAPSENSE_<WidgetName>_SNS<SensorNumber>_ID.
*
* For the CSX widgets, sensorId is an electrode ID and is defined as Rx ID
* or Tx ID. The first Rx in a widget corresponds to electrodeId = 0, the
* second Rx in a widget corresponds to electrodeId = 1, and so on.
* The last Tx in a widget corresponds to electrodeId = (RxNum + TxNum - 1).
* Macros for Rx and Tx IDs can be found in the CAPSENSE&trade; Configuration header
* file (cycfg_capsense.h) defined as:
* * CapSense_<WidgetName>_RX<RXNumber>_ID
* * CapSense_<WidgetName>_TX<TXNumber>_ID.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E          - The sensor pin(s) are valid
*                                         for CAPSENSE&trade; operations.
* - CY_CAPSENSE_BIST_FAIL_E             - A short is detected on the
*                                         specified sensor.
* - CY_CAPSENSE_BIST_BAD_PARAM_E        - The input parameter is invalid.
*                                         The test was not executed.
* - CY_CAPSENSE_BIST_HW_BUSY_E          - The CSD HW block is busy with a
*                                         previous operation. The function
*                                         was not executed.
*
*******************************************************************************/
cy_en_capsense_bist_status_t Cy_CapSense_CheckIntegritySensorPins(
                uint32_t widgetId,
                uint32_t sensorId,
                cy_stc_capsense_context_t * context)
{
    cy_en_capsense_bist_status_t result;

    #if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
        result = Cy_CapSense_CheckIntegritySensorPins_V3(widgetId, sensorId, context);
    #else /* (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN) */
        result = Cy_CapSense_CheckIntegritySensorPins_V2(widgetId, sensorId, context);
    #endif

    return (result);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_SNS_SHORT_EN) */


/*******************************************************************************
* Function Name: Cy_CapSense_BistDsInitialize
****************************************************************************//**
*
* This internal function initializes the BIST cy_stc_capsense_bist_context_t
* data structure parameters to be used in the test execution.
*
* The function is called once at the CAPSENSE&trade; start and performs
* the \ref cy_stc_capsense_bist_context_t structure initialization based
* on the configured parameters.
*
* Some of the parameters of the \ref cy_stc_capsense_bist_context_t structure
* can be changed in the run-time, but some changes require repeating the call
* of this function to the re-calculate register values.
* Refer to description of the following functions which parameters are used
* as an input and which are outputs:
* * Cy_CapSense_BistMeasureCapacitanceSensorInit()
* * Cy_CapSense_BistMeasureCapacitanceCapInit()
* * Cy_CapSense_BistMeasureVddaInit()
*
* \note
* Two last functions are available only for the fourth-generation CAPSENSE&trade;.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
*******************************************************************************/
void Cy_CapSense_BistDsInitialize(cy_stc_capsense_context_t * context)
{
#if (CY_CAPSENSE_PLATFORM_BLOCK_FIFTH_GEN)
    Cy_CapSense_BistDsInitialize_V3(context);
#else /* (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN) */
    Cy_CapSense_BistDsInitialize_V2(context);
#endif
}


#if (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN)

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_EXTERNAL_CAP_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_MeasureCapacitanceCap
****************************************************************************//**
*
* Measures the capacitance in picofarads of the specified CAPSENSE&trade; integration
* (external) capacitor.
*
* The function measures the capacitance of the specified external capacitor
* such as Cmod and returns the result through ptrValue, alternatively
* the measurement result is stored in the corresponding field of the
* \ref cy_stc_capsense_bist_context_t structure (either .cModCap, .cIntACap,
* .cIntBCap, or .cShieldCap).
*
* The maximum measurement capacitance is 25nF. The measurement accuracy is
* up to 15%. The measurement resolution is 10 bit which corresponds to the
* maximum capacitance specified by the maxCapacitance parameter. The bigger
* specified maximum capacitance is, the bigger capacitance value is for
* one measured count.
* It is recommended to specify the maximum capacitance twice bigger as the
* nominal capacitor capacitance. For example, if the nominal Cmod value
* is 2.2nF, the maxCapacitance parameter is set to 4nF-5nF.
*
* The function configures all CAPSENSE&trade; pins to  Strong-drive-low mode that
* allows detecting a short of the measured capacitor to other pins.
*
* To measure all the available capacitors, the Cy_CapSense_RunSelfTest()
* function can be used with the CY_CAPSENSE_BIST_EXTERNAL_CAP_MASK mask. The measured
* results are stored in the corresponding field of the
* \ref cy_stc_capsense_bist_context_t structure.
*
* Measurement can be done only if the CAPSENSE&trade; Middleware is in the IDLE
* state. This function must not be called while the CAPSENSE&trade; Middleware is busy.
* The function is blocking, i.e. waits for the measurement to be completed
* prior to returning to the caller.
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
*
* \param integrationCapId
* Indexes of external capacitors to measure their capacitance.
* There are macros for each of them, namely:
* * CY_CAPSENSE_BIST_CMOD_ID for the CSD method Cmod capacitor
* * CY_CAPSENSE_BIST_CINTA_ID for the CSX method CintA capacitor
* * CY_CAPSENSE_BIST_CINTB_ID for the CSX method CintB capacitor
* * CY_CAPSENSE_BIST_CSH_ID for the CSD method Csh capacitor
*
* \param ptrValue
* The pointer to the result of the measurement. The result is calculated as
* a specified capacitor capacitance value in picofarads. The user
* declares a variable of the uint32_t type and passes the pointer to this
* variable as the function parameter. If the ptrValue parameter is NULL then
* the capacitance value is not returned through the parameter but stored to the
* corresponding field of the \ref cy_stc_capsense_bist_context_t structure.
*
* \param maxCapacitance
* An expected by the user maximum value of the measured capacitance in
* nanofarads in the range from 1 to 25 nF.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E          - The measurement completes
*                                         successfully, the result is valid.
* - CY_CAPSENSE_BIST_BAD_PARAM_E        - The input parameter is invalid.
*                                         The measurement was not executed.
* - CY_CAPSENSE_BIST_HW_BUSY_E          - The CSD HW block is busy with
*                                         a previous operation. The measurement
*                                         was not executed.
* - CY_CAPSENSE_BIST_LOW_LIMIT_E        - The measurement was performed
*                                         but the scanning result is
*                                         below the minimum possible value.
*                                         The measurement result could be invalid.
*                                         The capacitor might be shorted to
*                                         VDD or a PCB track
*                                         is broken (open capacitor).
* - CY_CAPSENSE_BIST_HIGH_LIMIT_E       - The measurement was performed but
*                                         the scanning result is above the
*                                         maximum possible value.
*                                         The measurement result could be invalid.
*                                         The capacitor might be shorted to GND.
* - CY_CAPSENSE_BIST_ERROR_E            - An unexpected fault occurred during
*                                         the measurement.
*
*******************************************************************************/
cy_en_capsense_bist_status_t Cy_CapSense_MeasureCapacitanceCap(
                cy_en_capsense_bist_external_cap_id_t integrationCapId,
                uint32_t * ptrValue,
                uint32_t maxCapacitance,
                cy_stc_capsense_context_t * context)
{
    cy_en_capsense_bist_status_t bistStatus = CY_CAPSENSE_BIST_SUCCESS_E;

    bistStatus = Cy_CapSense_MeasureCapacitanceCap_V2(integrationCapId,
                                                     ptrValue,
                                                     maxCapacitance,
                                                     context);

    return (bistStatus);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_EXTERNAL_CAP_EN) */

#if (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_VDDA_EN)
/*******************************************************************************
* Function Name: Cy_CapSense_MeasureVdda
****************************************************************************//**
*
* Measures a VDDA voltage, returns the measured voltage in
* millivolts through the ptrValue argument and stores it to the .vddaVoltage
* field of the \ref cy_stc_capsense_bist_context_t structure.
*
* This function measures the device analog supply voltage (VDDA) without need
* of explicitly connecting VDDA to any additional GPIO input.
* This capability can be used in variate cases, for example to monitor
* the battery voltage.
*
* A measurement can be done only if the CAPSENSE&trade; middleware is in the IDLE
* state. This function must not be called while the CAPSENSE&trade; middleware is busy.
* The function is blocking, i.e. waits for the conversion to be completed
* prior to returning to the caller.
*
* \note
* This function is available only for the fourth-generation CAPSENSE&trade;.
*
* \param ptrValue
* The pointer to the uint32_t to store measured VDDA voltage value.
* If the ptrValue parameter is NULL then VDDA voltage value is not returned
* through the parameter and is stored in the .vddaVoltage
* field of the \ref cy_stc_capsense_bist_context_t structure.
*
* \param context
* The pointer to the CAPSENSE&trade; context structure \ref cy_stc_capsense_context_t.
*
* \return
* Returns a status of the test execution:
* - CY_CAPSENSE_BIST_SUCCESS_E          - The measurement executed
*                                         successfully.
* - CY_CAPSENSE_BIST_BAD_PARAM_E        - The input parameter is invalid.
*                                         The measurement was not executed.
* - CY_CAPSENSE_BIST_ERROR_E            - An unexpected fault occurred during
*                                         the measurement.
*
*******************************************************************************/
cy_en_capsense_bist_status_t Cy_CapSense_MeasureVdda(
                uint32_t * ptrValue,
                cy_stc_capsense_context_t * context)
{
    cy_en_capsense_bist_status_t result = CY_CAPSENSE_BIST_BAD_PARAM_E;
    result = Cy_CapSense_MeasureVdda_V2(ptrValue, context);

    return (result);
}
#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_TST_VDDA_EN) */

#endif /* (CY_CAPSENSE_PLATFORM_BLOCK_FOURTH_GEN) */

#endif /* (CY_CAPSENSE_ENABLE == CY_CAPSENSE_BIST_EN) */

#endif /* (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2) || defined(CY_IP_M0S8MSCV3)) */


/* [] END OF FILE */
