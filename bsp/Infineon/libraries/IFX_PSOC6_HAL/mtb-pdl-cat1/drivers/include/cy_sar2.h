/***************************************************************************//**
* \file cy_sar2.h
* \version 1.0
*
* Provides an API declaration of the SAR2 driver
*
*******************************************************************************
* \copyright
* (c) (2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

/**
* \addtogroup group_sar2
* \{
* The SAR2 driver provides an API to configure the SAR2 ADC.
* The SAR2 has up to 4 ADCs and up to 32 channels for each ADC module. About
* actual number of supported modules and channels, refer to the technical
* reference manual (TRM) and device datasheet.
*
* \section group_sar2_configuration Configuration Considerations
* Typical usage:
*  - Call Cy_SAR2_Init to initialize the ADC module and its channels
*  - Call Cy_SAR2_Channel_SetInterruptMask if you need to use the interrupt.
* After initializing channel(s) call, trigger a call by the software
* (calling Cy_SAR2_Channel_SoftwareTrigger) or start a peripheral
* configured for the HW trigger.
*
\note It is not recommended to set the  triggerSelection structure member
* of the \ref cy_stc_sar2_channel_config_t to CY_SAR2_TRIGGER_CONTINUOUS if
* cy_en_sar2_preemption_type_t is set to CY_SAR2_PREEMPTION_ABORT_CANCEL.
* It may work to the effect that the channel or channel group will not be able
* to complete without advanced priority tuning.
* \par
*
* \note If you use an interrupt for ADC, create an interrupt handler
* and register it by using the sysint module. In the handler, you can check
* which interrupt is occurred by Cy_SAR2_Channel_GetInterruptStatusMasked
* and can get the conversion result by Cy_SAR2_Channel_GetResult.
* If you do not use the interrupt, you can poll the conversion status by
* Cy_SAR2_Channel_GetInterruptStatus.
* For both of polling and interrupt, clear the interrupt flags by
* Cy_SAR2_Channel_ClearInterrupt after handling data.
* \par
*
* \note SAR2 block can operate in Active or Sleep mode only.
*
* \subsection group_sar2_config Configuration Example
* First step would be to configure clock:
*
* \snippet sar2/snippet/main.c SNIPPET_CLOCK_INIT
*
* Group of two SAR2 ADC channels are configured, one for bandgap voltage
* and one for the AN0 analogue input:
*
* \snippet sar2/snippet/main.c SNIPPET_SAR2_CONFIG
*
* \subsection group_sar2_init Initialization
*
* \snippet sar2/snippet/main.c SNIPPET_SAR2_INIT
*
* \subsection group_sar2_result Obtaining results in counts
*
* \snippet sar2/snippet/main.c SNIPPET_SAR2_GET_RESULT
*
* \subsection group_sar2_calc_volts Calculating results in V, mV or uV
*
* \snippet sar2/snippet/main.c SNIPPET_SAR2_CALC_VOLTS
*
* \subsection group_sar2_die_temperature Die temperature
*
* \snippet sar2/snippet/main.c SNIPPET_SAR2_DIE_TEMPERATURE
*
* Once done, in the variable, returned by the
* \ref Cy_SAR2_CalculateDieTemperature function will contain the die temperature
* value in Celsius degrees.
*
* The accuracy can be increased by executing the calibration procedure
* (see \ref group_sar2_calibration section) before doing the conversion.
*
* In the function call, the first argument is the enumeration value,
* representing the VDDA value range supplied to this particular chip being used,
* see \ref cy_en_sar2_vdda_range_t.
*
* \subsection group_sar2_channel_grouping Channel grouping
* The SAR2 driver supports the channel grouping. Each channel can be either in
* an individual group or in a group of 2 or more channels. By default, the
* hardware will execute the next channel if it exists and is in the Enabled
* state if the current channel does not have the flag 'Group End' set. You can
* set triggers to start either the first channel or any channel of the group to
* execute all the next channels.
*
* \section group_sar2_more_information More Information
* Refer to the technical reference manual (TRM) and the device datasheet.
*
* \section group_sar2_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_sar2_macro Macros
* \{
*   \defgroup group_sar2_macros_interrupt        Interrupt Masks
*   \defgroup group_sar2_macros_status           Status Masks
* \}
* \defgroup group_sar2_functions Functions
* \defgroup group_sar2_data_structures Data structures
* \defgroup group_sar2_enums Enumerated Types
* \defgroup group_sar2_calibration Calibration procedure
*
* \n
* \addtogroup group_sar2_calibration
* \{
* To start the procedure, perform \ref group_sar2_config and
* \ref group_sar2_init with included extra channel, which can be re-used
* after this procedure is complete:
* \snippet sar2/snippet/main.c SNIPPET_CALIB_CH_INIT
* The ADC has an offset adjustment function to compensate for offset error.
* It is possible to select code from +127 to -128 in a dec. for analog
* calibration.
* \n
* The offset adjustment step is a quarter of 1LSb. \n
* Offset = max( 0, min( 4095, floor( VIN/VREFH x 4096 + OFST/4 ) ) )
* \image html sar2_offset_calibration.png
* \note Enable reference buffer mode using \ref Cy_SAR2_SetReferenceBufferMode
* function.
*
* \n
* Following code snippet can be used:
* \snippet sar2/snippet/main.c SNIPPET_SAR2_OFFSET_CALIBRATION
*
* After that, the Gain should also be calibrated as well.
* The ADC has a gain adjustment function to compensate for gain error.
* It is possible to set code from +15 to -15 dec.
* The gain adjustment step is a quarter of 1LSb. \n
* Gain = max(0, min(4095, floor((4096 - GAIN)/VREFH x (VIN - VREFH/2) + 2048)))
* \image html sar2_gain_calibration.png
* \snippet sar2/snippet/main.c SNIPPET_SAR2_GAIN_CALIBRATION
* \n
* Once done, the calibrationConfig global structure contains calibration data
* for SAR2 block 0. Calibration is advised to be done as frequent as possible.
* \}
*/


#if !defined(CY_SAR2_H)
#define CY_SAR2_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <math.h>
#include "cy_syslib.h"
#include "cy_utils.h"
#include "cy_device.h"

#if defined (CY_IP_MXS40EPASS_ESAR)

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
*       Macro definitions
***************************************/

/**
* \addtogroup group_sar2_macro
* \{
*/

/** Driver major version */
#define CY_SAR2_DRV_VERSION_MAJOR  1

/** Driver minor version */
#define CY_SAR2_DRV_VERSION_MINOR  0

/** Sar2 driver ID */
#define CY_SAR2_ID                 CY_PDL_DRV_ID(0x4BUL)

/** Number of input triggers */
#define CY_SAR2_TR_IN_NUM          (5UL)

/** Number of output triggers */
#define CY_SAR2_TR_OUT_NUM         (2UL)

/** Maximum generic input trigger */
#define CY_SAR2_GEN_TR_IN_NUM      (16UL)

/** Maximum generic output trigger */
#define CY_SAR2_GEN_TR_OUT_NUM     (64UL)

/** Temperature matrix sixe */
#define CY_SAR2_TEMP_MATRIX_SIZE   (3UL)

/** Channel number */
#define CY_SAR2_NUM_CHANNELS       (32UL)

/***************************************
*       Group status
***************************************/
/** \addtogroup group_sar2_macros_status
* \{
*/
/** If this bit is true, "out of range" was detected and the value was above the High threshold. */
#define CY_SAR2_STATUS_ABOVE       (PASS_SAR_CH_RESULT_ABOVE_HI_MIR_Msk)

/** If this bit is true, the range is detected. */
#define CY_SAR2_STATUS_RANGE       (PASS_SAR_CH_RESULT_RANGE_INTR_MIR_Msk)

/** If this bit is true, the pulse is detected. */
#define CY_SAR2_STATUS_PULSE       (PASS_SAR_CH_RESULT_PULSE_INTR_MIR_Msk)

/** If this bit is true, the result data is valid. */
#define CY_SAR2_STATUS_VALID       (PASS_SAR_CH_RESULT_VALID_MIR_Msk)

/** Group acquisition completed. This bit can be set for the last channel of a group if the group scan is done. */
#define CY_SAR2_GRP_COMPLETE       (PASS_SAR_CH_GRP_STAT_GRP_COMPLETE_Msk)

/** Group Cancelled. This bit can be set for the last channel of a group if the group scan was
 *  preempted and cancelled. */
#define CY_SAR2_GRP_CANCELLED      (PASS_SAR_CH_GRP_STAT_GRP_CANCELLED_Msk)

/** Group Overflow. This bit can be set for the last channel of a group if the group scan is
 *  done and the Done interrupt is already (still) pending. */
#define CY_SAR2_GRP_OVERFLOW       (PASS_SAR_CH_GRP_STAT_GRP_OVERFLOW_Msk)

/** Channel Range completed. This bit can be set for each channel if the conversion result
 *  (after averaging) of that channel met the condition specified by the range detection
 *  mode settings of the channel. */
#define CY_SAR2_CH_RANGE_COMPLETE  (PASS_SAR_CH_GRP_STAT_CH_RANGE_COMPLETE_Msk)

/** Channel Pulse completed. This bit can be set for each channel if the positive pulse counter reaches zero. */
#define CY_SAR2_CH_PULSE_COMPLETE  (PASS_SAR_CH_GRP_STAT_CH_PULSE_COMPLETE_Msk)

/** Channel Overflow. This bit can be set for each channel if a new Pulse or Range interrupt is detected
 *  while the interrupt is still pending or when HW did not acknowledge data pickup.*/
#define CY_SAR2_CH_OVERFLOW        (PASS_SAR_CH_GRP_STAT_CH_OVERFLOW_Msk)

/** Group acquisition busy. */
#define CY_SAR2_GRP_BUSY           (PASS_SAR_CH_GRP_STAT_GRP_BUSY_Msk)

/** \} group_sar2_macros_status */


/***************************************
*       Interrupts
***************************************/
/** \addtogroup group_sar2_macros_interrupt
* \{
*/
/** Group done. */
#define CY_SAR2_INT_GRP_DONE                 (PASS_SAR_CH_INTR_GRP_DONE_Msk)

/** Group cancelled. */
#define CY_SAR2_INT_GRP_CANCELLED            (PASS_SAR_CH_INTR_GRP_CANCELLED_Msk)

/** Group overflow. */
#define CY_SAR2_INT_GRP_OVERFLOW             (PASS_SAR_CH_INTR_GRP_OVERFLOW_Msk)

/** Channel range event. */
#define CY_SAR2_INT_CH_RANGE                 (PASS_SAR_CH_INTR_CH_RANGE_Msk)

/** Channel pulse event. */
#define CY_SAR2_INT_CH_PULSE                 (PASS_SAR_CH_INTR_CH_PULSE_Msk)

/** Channel overflow event. */
#define CY_SAR2_INT_CH_OVERFLOW              (PASS_SAR_CH_INTR_CH_OVERFLOW_Msk)

/** Combined interrupt mask. */
#define CY_SAR2_INTR                     (CY_SAR2_INT_GRP_DONE | \
                                         CY_SAR2_INT_GRP_CANCELLED | \
                                         CY_SAR2_INT_GRP_OVERFLOW | \
                                         CY_SAR2_INT_CH_RANGE | \
                                         CY_SAR2_INT_CH_PULSE | \
                                         CY_SAR2_INT_CH_OVERFLOW)

/** \} group_sar2_macros_interrupt */

/** \cond INTERNAL */
/** Macro that returns the channel number for a specified SAR instance. */
#define CY_SAR2_CHAN_NUM(base)               ((PASS0_SAR0 == (base)) ? PASS_SAR_SLICE_NR0_SAR_SAR_MUX_IN :\
                                              (PASS0_SAR1 == (base)) ? PASS_SAR_SLICE_NR1_SAR_SAR_MUX_IN :\
                                                                       PASS_SAR_SLICE_NR2_SAR_SAR_MUX_IN)

#define CY_SAR2_CHAN_NUM_VALID(base, channel) (CY_SAR2_CHAN_NUM(base) > (channel))

/** \endcond */

/** \} group_sar2_macro */

/***************************************
*       Enumeration
***************************************/

/**
* \addtogroup group_sar2_enums
* \{
*/

/**
* SAR2 Driver error codes
*/
typedef enum {
    CY_SAR2_SUCCESS   = 0x00U,                                    /**< Returned successful */
    CY_SAR2_BAD_PARAM = CY_SAR2_ID | CY_PDL_STATUS_ERROR | 0x01U, /**< A bad parameter was passed */
} cy_en_sar2_status_t;

/** When set uses 2 cycles for the Most Significant Bit (MSB). */
typedef enum {
    CY_SAR2_MSB_STRETCH_MODE_1CYCLE = 0U, /**< Use 1 clock cycles per conversion. */
    CY_SAR2_MSB_STRETCH_MODE_2CYCLE = 1U  /**< Use 2 clock cycles per conversion. */
} cy_en_sar2_msb_stretch_mode_t;

/** The Diagnostic Reference function selection. */
typedef enum {
    CY_SAR2_DIAG_REFERENCE_SELECT_VREFL       = 0U,  /**< DiagOut = VrefL */
    CY_SAR2_DIAG_REFERENCE_SELECT_VREFH_1DIV8 = 1U,  /**< DiagOut = VrefH * 1/8 */
    CY_SAR2_DIAG_REFERENCE_SELECT_VREFH_2DIV8 = 2U,  /**< DiagOut = VrefH * 2/8 */
    CY_SAR2_DIAG_REFERENCE_SELECT_VREFH_3DIV8 = 3U,  /**< DiagOut = VrefH * 3/8 */
    CY_SAR2_DIAG_REFERENCE_SELECT_VREFH_4DIV8 = 4U,  /**< DiagOut = VrefH * 4/8 */
    CY_SAR2_DIAG_REFERENCE_SELECT_VREFH_5DIV8 = 5U,  /**< DiagOut = VrefH * 5/8 */
    CY_SAR2_DIAG_REFERENCE_SELECT_VREFH_6DIV8 = 6U,  /**< DiagOut = VrefH * 6/8 */
    CY_SAR2_DIAG_REFERENCE_SELECT_VREFH_7DIV8 = 7U,  /**< DiagOut = VrefH * 7/8 */
    CY_SAR2_DIAG_REFERENCE_SELECT_VREFH       = 8U,  /**< DiagOut = VrefH */
    CY_SAR2_DIAG_REFERENCE_SELECT_VREFX       = 9U,  /**< DiagOut = VrefX = VrefH * 199/200 */
    CY_SAR2_DIAG_REFERENCE_SELECT_VBG         = 10U, /**< DiagOut = Vbg from SRSS */
    CY_SAR2_DIAG_REFERENCE_SELECT_VIN1        = 11U, /**< DiagOut = Vin1 */
    CY_SAR2_DIAG_REFERENCE_SELECT_VIN2        = 12U, /**< DiagOut = Vin2 */
    CY_SAR2_DIAG_REFERENCE_SELECT_VIN3        = 13U, /**< DiagOut = Vin3 */
    CY_SAR2_DIAG_REFERENCE_SELECT_I_SOURCE    = 14U, /**< DiagOut = Isource (10uA) */
    CY_SAR2_DIAG_REFERENCE_SELECT_I_SINK      = 15U  /**< DiagOut = Isink (10uA) */
} cy_en_sar2_diag_reference_select_t;

/** The SAR2 trigger mode selection. */
typedef enum {
    CY_SAR2_TRIGGER_OFF        = 0U, /**< Use for channels in group, except the first channel */
    CY_SAR2_TRIGGER_TCPWM      = 1U, /**< Trigger from corresponding TCPWM channel */
    CY_SAR2_TRIGGER_GENERIC0   = 2U, /**< Generic trigger input 0 */
    CY_SAR2_TRIGGER_GENERIC1   = 3U, /**< Generic trigger input 1 */
    CY_SAR2_TRIGGER_GENERIC2   = 4U, /**< Generic trigger input 2 */
    CY_SAR2_TRIGGER_GENERIC3   = 5U, /**< Generic trigger input 3 */
    CY_SAR2_TRIGGER_GENERIC4   = 6U, /**< Generic trigger input 4 */
    CY_SAR2_TRIGGER_CONTINUOUS = 7U  /**< Always triggered (also called idle), can only be used for at most 1 channel */
} cy_en_sar2_trigger_selection_t;

/** The SAR2 ADC preemption type selection. */
typedef enum {
    CY_SAR2_PREEMPTION_ABORT_CANCEL  = 0U, /**< Abort the ongoing acquisition, does not return. */
    CY_SAR2_PREEMPTION_ABORT_RESTART = 1U, /**< Abort ongoing acquisition, up on return Restart
                                               group from the first channel. */
    CY_SAR2_PREEMPTION_ABORT_RESUME  = 2U, /**< Abort the ongoing acquisition, up on return Resume group from
                                               the aborted channel. */
    CY_SAR2_PREEMPTION_FINISH_RESUME = 3U  /**< Completed ongoing acquisition (including averaging), up on return
                                               Resume group from the next channel. */
} cy_en_sar2_preemption_type_t;

/** Conversion done, trigger output selection. */
typedef enum {
    CY_SAR2_DONE_LEVEL_PULSE = 0U,   /**< The conversion done signal for other IPs is a 2-cycle pulse (clk_sys), no need
                                         to read the result register. Typically used for triggering another IPs other
                                         than DW. */
    CY_SAR2_DONE_LEVEL_LEVEL = 1U    /**< The conversion done signal for other IPs is the level output until the result
                                         register is read. Typically used for DW and also overflowed? detection. */
} cy_en_sar2_done_level_t;

/** The address of the analog signal (pin) to be sampled by a corresponding channel. */
typedef enum {
    CY_SAR2_PIN_ADDRESS_AN0       = 0U,  /**<  Vout = AN0, select the corresponding analog input. */
    CY_SAR2_PIN_ADDRESS_AN1       = 1U,
    CY_SAR2_PIN_ADDRESS_AN2       = 2U,
    CY_SAR2_PIN_ADDRESS_AN3       = 3U,
    CY_SAR2_PIN_ADDRESS_AN4       = 4U,
    CY_SAR2_PIN_ADDRESS_AN5       = 5U,
    CY_SAR2_PIN_ADDRESS_AN6       = 6U,
    CY_SAR2_PIN_ADDRESS_AN7       = 7U,
    CY_SAR2_PIN_ADDRESS_AN8       = 8U,
    CY_SAR2_PIN_ADDRESS_AN9       = 9U,
    CY_SAR2_PIN_ADDRESS_AN10      = 10U,
    CY_SAR2_PIN_ADDRESS_AN11      = 11U,
    CY_SAR2_PIN_ADDRESS_AN12      = 12U,
    CY_SAR2_PIN_ADDRESS_AN13      = 13U,
    CY_SAR2_PIN_ADDRESS_AN14      = 14U,
    CY_SAR2_PIN_ADDRESS_AN15      = 15U,
    CY_SAR2_PIN_ADDRESS_AN16      = 16U,
    CY_SAR2_PIN_ADDRESS_AN17      = 17U,
    CY_SAR2_PIN_ADDRESS_AN18      = 18U,
    CY_SAR2_PIN_ADDRESS_AN19      = 19U,
    CY_SAR2_PIN_ADDRESS_AN20      = 20U,
    CY_SAR2_PIN_ADDRESS_AN21      = 21U,
    CY_SAR2_PIN_ADDRESS_AN22      = 22U,
    CY_SAR2_PIN_ADDRESS_AN23      = 23U,
    CY_SAR2_PIN_ADDRESS_AN24      = 24U,
    CY_SAR2_PIN_ADDRESS_AN25      = 25U,
    CY_SAR2_PIN_ADDRESS_AN26      = 26U,
    CY_SAR2_PIN_ADDRESS_AN27      = 27U,
    CY_SAR2_PIN_ADDRESS_AN28      = 28U,
    CY_SAR2_PIN_ADDRESS_AN29      = 29U,
    CY_SAR2_PIN_ADDRESS_AN30      = 30U,
    CY_SAR2_PIN_ADDRESS_AN31      = 31U,
    CY_SAR2_PIN_ADDRESS_VMOTOR    = 32U, /**< Vout = Vmotor, select the motor input. */
    CY_SAR2_PIN_ADDRESS_VAUX      = 33U, /**< Vout = Vaux, select the auxiliarly input. */
    CY_SAR2_PIN_ADDRESS_AMUXBUS_A = 34U, /**< Vout = AmuxbusA. */
    CY_SAR2_PIN_ADDRESS_AMUXBUS_B = 35U, /**< Vout = AmuxbusB. */
    CY_SAR2_PIN_ADDRESS_VCCD      = 36U, /**< Vout = Vccd. */
    CY_SAR2_PIN_ADDRESS_VDDA      = 37U, /**< Vout = Vdda. */
    CY_SAR2_PIN_ADDRESS_VBG       = 38U, /**< Vout = Vbg, Bandgap voltage from SRSS. */
    CY_SAR2_PIN_ADDRESS_VTEMP     = 39U, /**< Vout = Vtemp, select the temperature sensor.
                                             Ensure that only 1 ADC is allowed to use this. */
    CY_SAR2_PIN_ADDRESS_VREF_L    = 62U, /**< Vout = VrefL (VrefL actually bypasses the SARMUX (XSL)). */
    CY_SAR2_PIN_ADDRESS_VREF_H    = 63U  /**< Vout = VrefH  (VrefH actually bypasses the SARMUX (XSH)) */
} cy_en_sar2_pin_address_t;

/** The physical port. This field is only valid for the SAR2 ADC0 block. */
typedef enum {
    CY_SAR2_PORT_ADDRESS_SARMUX0 = 0U, /**< ADC uses its own SARMUX. */
    CY_SAR2_PORT_ADDRESS_SARMUX1 = 1U, /**< ADC0 uses SARMUX1 (only valid for ADC0,
                                           undefined result if used for ADC1-3). */
    CY_SAR2_PORT_ADDRESS_SARMUX2 = 2U, /**< ADC0 uses SARMUX2 (only valid for ADC0,
                                           undefined result if used for ADC1-3). */
    CY_SAR2_PORT_ADDRESS_SARMUX3 = 3U  /**< ADC0 uses SARMUX3 (only valid for ADC0,
                                           undefined result if used for ADC1-3). */
} cy_en_sar2_port_address_t;

/** Preconditioning mode selection.
    Preconditioning charges or discharges the SAR sample capacitor to the selected reference voltage for precondition
    time (global) cycles, a break before a make cycle will be inserted before sampling starts the sample time.
    See also \ref cy_stc_sar2_config_t */
typedef enum {
    CY_SAR2_PRECONDITION_MODE_OFF    = 0U,   /**< No preconditioning. */
    CY_SAR2_PRECONDITION_MODE_VREFL  = 1U,   /**< Discharge to VREFL. */
    CY_SAR2_PRECONDITION_MODE_VREFH  = 2U,   /**< Charge to VREFH. */
    CY_SAR2_PRECONDITION_MODE_DIAG   = 3U    /**< Connect the Diagnostic reference output during preconditioning.
                                                 Configure the Diagnostic reference to output
                                                 the reference voltage. */
} cy_en_sar2_precondition_mode_t;

/** Overlap mode or SARMUX Diagnostics selection, in both cases only used when the Diagnostic reference is used. */
typedef enum {
    CY_SAR2_OVERLAP_DIAG_MODE_OFF        = 0U,   /**< No overlap or SARMUX Diagnostics. */
    CY_SAR2_OVERLAP_DIAG_MODE_HALF       = 1U,   /**< Sample the selected analog input for 2 sample time periods.
                                                     During the first period, use the overlap sampling,
                                                     i.e. connect both the analog input and Diagnostic reference.
                                                     During the second period only connect the analog input */
    CY_SAR2_OVERLAP_DIAG_MODE_FULL       = 2U,   /**< The selected analog input for a single sample
                                                     time period is like a normal sample but use the overlap sampling,
                                                     i.e. connect both the analog input and Diagnostic reference. */
    CY_SAR2_OVERLAP_DIAG_MODE_MUX_DIAG   = 3U    /**< Select Diagnostic reference instead of analog signal at the
                                                     input of the SARMUX. This enables a functional safety check
                                                     of the SARMUX analog connections. */
} cy_en_sar2_overlap_diag_mode_t;

/** Calibration values selection. */
typedef enum {
    CY_SAR2_CALIBRATION_VALUE_REGULAR    = 0U,   /**< Use regular calibration values */
    CY_SAR2_CALIBRATION_VALUE_ALTERNATE  = 1U    /**< Use alternate calibration values */
} cy_en_sar2_calibration_value_select_t;


/** Post processing mode selection. */
typedef enum {
    CY_SAR2_POST_PROCESSING_MODE_NONE        = 0U,  /**< No post processing. */
    CY_SAR2_POST_PROCESSING_MODE_AVG         = 1U,  /**< Averaging. */
    CY_SAR2_POST_PROCESSING_MODE_AVG_RANGE   = 2U,  /**< Averaging followed by Range detect. */
    CY_SAR2_POST_PROCESSING_MODE_RANGE       = 3U,  /**< Range detect. */
    CY_SAR2_POST_PROCESSING_MODE_RANGE_PULSE = 4U,  /**< Range detect followed by pulse detect. */
} cy_en_sar2_post_processing_mode_t;

/** Result data alignment selection. */
typedef enum {
    CY_SAR2_RESULT_ALIGNMENT_RIGHT           = 0U, /**< The data is right aligned in result[11:0], with sign extension
                                                       to 16 bits if enabled. */
    CY_SAR2_RESULT_ALIGNMENT_LEFT            = 1U, /**< The data shifts left in result[15:4] with the
                                                       lower nibble 0. Caveat if the result is more than 12 bits
                                                       (e.g. after averaging), then the bits above 12 will be
                                                       discarded. */

} cy_en_sar2_result_alignment_t;

/** Select whether result data is signed or unsigned. */
typedef enum {
    CY_SAR2_SIGN_EXTENTION_UNSIGNED          = 0U, /**< Result data is unsigned (zero-extended if needed). */
    CY_SAR2_SIGN_EXTENTION_SIGNED            = 1U, /**< Result data is signed (sign-extended if needed). */
} cy_en_sar2_sign_extention_t;

/** Range detection mode selection. */
typedef enum {
    CY_SAR2_RANGE_DETECTION_MODE_BELOW_LO        = 0U,   /**< Below Low threshold (result < Lo) */
    CY_SAR2_RANGE_DETECTION_MODE_INSIDE_RANGE    = 1U,   /**< Inside range (Lo <= result < Hi) */
    CY_SAR2_RANGE_DETECTION_MODE_ABOVE_HI        = 2U,   /**< Above high threshold (Hi <= result) */
    CY_SAR2_RANGE_DETECTION_MODE_OUTSIDE_RANGE   = 3U    /**< Outside range (result < Lo || Hi <= result) */
} cy_en_sar2_range_detection_mode_t;

/** Reference buffer mode selection. */
typedef enum {
    CY_SAR2_REF_BUF_MODE_OFF     = 0U,   /**< No reference mode selected */
    CY_SAR2_REF_BUF_MODE_ON      = 1U,   /**< Reference buffered Vbg from SRSS */
    CY_SAR2_REF_BUF_MODE_BYPASS  = 3U,   /**< Reference unbuffered Vbg from SRSS */
} cy_en_sar2_ref_buf_mode_t;

/** VDDA voltage range selection. */
typedef enum {
    CY_SAR2_VDDA_2_7V_TO_4_5V     = 0U,   /**< The Vdda is in range from 2.7 to 4.5 V */
    CY_SAR2_VDDA_4_5V_TO_5_5V     = 1U,   /**< The Vdda is in range from 4.5 to 5.5 V */
} cy_en_sar2_vdda_range_t;

/** \} group_sar2_enums */

/***************************************
*       Configuration Structure
***************************************/
/**
* \addtogroup group_sar2_data_structures
* \{
*/

/** Configuration structure of the SAR2 ADC channel */
typedef struct {
    bool                                channelHwEnable;    /**< If HW is started, or just configured. */
    cy_en_sar2_trigger_selection_t      triggerSelection;   /**< The ADC trigger mode selection,
                                                                see \ref cy_en_sar2_trigger_selection_t */
    uint8_t                             channelPriority;    /**< Channel priority. 0=highest, 7=lowest.*/
    cy_en_sar2_preemption_type_t        preenptionType;     /**< The ADC preemption type selection,
                                                                see \ref cy_en_sar2_preemption_type_t */
    bool                                isGroupEnd;         /**< This value indicates that this channel is the last
                                                                channel of a group or not */
    cy_en_sar2_done_level_t             doneLevel;          /**< Conversion done, trigger output selection,
                                                                see \ref cy_en_sar2_done_level_t */
    cy_en_sar2_pin_address_t            pinAddress;         /**< The address of the analog signal (pin) to be sampled by
                                                                a corresponding channel,
                                                                see \ref cy_en_sar2_pin_address_t */
    cy_en_sar2_port_address_t           portAddress;        /**< Select the physical port,
                                                                see \ref cy_en_sar2_port_address_t */
    uint8_t                             extMuxSelect;       /**< External analog mux selection. */
    bool                                extMuxEnable;       /**< External analog mux enable. */
    cy_en_sar2_precondition_mode_t      preconditionMode;   /**< Select Preconditioning mode,
                                                                see \ref cy_en_sar2_precondition_mode_t */
    cy_en_sar2_overlap_diag_mode_t      overlapDiagMode;    /**< Select Overlap mode or SARMUX Diagnostics,
                                                                see \ref cy_en_sar2_overlap_diag_mode_t */
    uint16_t                            sampleTime;         /**< Sample time (aperture) in ADC clock cycles.
                                                                The minimum is 1 (0 gives the same result as 1),
                                                                the minimum time needed for the proper settling is at
                                                                least 300ns, i.e. 6 clock cycles at the max frequency of
                                                                20MHz. */
    cy_en_sar2_calibration_value_select_t calibrationValueSelect;    /**< Select calibration values, see
                                                                         \ref cy_en_sar2_calibration_value_select_t */
    cy_en_sar2_result_alignment_t         resultAlignment;    /**< Select the result data alignment,
                                                                  see \ref cy_en_sar2_result_alignment_t */
    cy_en_sar2_sign_extention_t           signExtention;      /**< Select whether the result data is signed or unsigned,
                                                                  see \ref cy_en_sar2_sign_extention_t */
    cy_en_sar2_post_processing_mode_t     postProcessingMode; /**< Select Post processing mode == ,
                                                                  see \ref cy_en_sar2_post_processing_mode_t */
    uint16_t                              averageCount;       /**< Averaging count. Active only if post processing mode
                                                                  is set to Averaging or Averaging + Range detect.
                                                                  The valid range is [1..256] */
    uint8_t                               rightShift;         /**< Shift Right. When using post processing mode with
                                                                  averaging, the set value is used for the right-shift
                                                                  value of the conversion result. Averaging data may be
                                                                  over 12 bits, therefore the user must ensure the
                                                                  conversion result is not to over 12 bits by using
                                                                  this value. This value is also used to fit the 12-bit
                                                                  result in 8 bits. The valid range is [0..15]*/
    uint16_t                              positiveReload;      /**< Positive pulse reload value. Active only if
                                                                   post processing is set to the Pulse detection.
                                                                   The valid range is [0..255]. */
    uint8_t                               negativeReload;      /**< Negative pulse reload value. Active only if
                                                                   post processing is set to the Pulse detection.
                                                                   The valid range is [0..31]. */
    cy_en_sar2_range_detection_mode_t     rangeDetectionMode; /**< Select Range detection mode,
                                                                  see \ref cy_en_sar2_range_detection_mode_t */
    uint16_t                      rangeDetectionLoThreshold;  /**< Range detect low threshold (Lo) */
    uint16_t                      rangeDetectionHiThreshold;  /**< Range detect high threshold (Hi) */
    uint32_t                      interruptMask;              /**< Select the interrupt sources.
                                                                  See \ref group_sar2_macros_interrupt */

} cy_stc_sar2_channel_config_t;

/** Configuration structure of the SAR2 HW block */
typedef struct {
    uint8_t                       preconditionTime;    /**< The number of ADC clock cycles when Preconditioning is done
                                                           before the sample window starts. */
    uint8_t                       powerupTime;         /**< The number of cycles to wait for power up after
                                                           IDLE_PWRDWN. */
    bool                          enableIdlePowerDown; /**< When idle automatically power is down, the analog if
                                                            true. */
    cy_en_sar2_msb_stretch_mode_t msbStretchMode;      /**< When the set uses 2 cycles for the Most Significant Bit
                                                           (MSB), see \ref cy_en_sar2_msb_stretch_mode_t */
    bool                          enableHalfLsbConv;   /**< When true takes an extra cycle to convert the half LSB and
                                                           add it to the 12-bit result for Missing Code Recovery */
    bool                          sarMuxEnable;        /**< Enable the SARMUX (only valid if sarIpEnable = true). */
    bool                          adcEnable;           /**< Enable the SAR ADC and SAR sequencer
                                                           (only valid if sarIpEnable = true). */
    bool                          sarIpEnable;         /**< Enable the SAR IP. */
    cy_stc_sar2_channel_config_t * channelConfig[CY_SAR2_NUM_CHANNELS];  /**< Channel configuration pointer array. */
} cy_stc_sar2_config_t;

/** Digital calibration values. */
typedef struct {
    uint16_t    offset; /**< Digital offset correction. The valid range is [0..4095] */
    int8_t     gain;   /**< Digital gain correction. The valid range is [-32..31] */
} cy_stc_sar2_digital_calibration_config_t;

/** Analog calibration values. */
typedef struct {
    int8_t     offset; /**< Analog offset correction. The valid range is [-128..127] */
    int8_t     gain;   /**< Analog gain correction. The valid range is [-16..15] */
} cy_stc_sar2_analog_calibration_conifg_t;

/** Configuration structure of diagnosis function. */
typedef struct {
    cy_en_sar2_diag_reference_select_t   referenceSelect;    /**< Select Diagnostic Reference function,
                                                                 see \ref cy_en_sar2_diag_reference_select_t */
} cy_stc_sar2_diag_config_t;

/** Control freeze feature for debugging. */
typedef struct {
    bool      enableFreezeAdc0; /**< If true, freeze ADC0 in Debug mode. */
    bool      enableFreezeAdc1; /**< If true, freeze ADC1 in Debug mode. */
    bool      enableFreezeAdc2; /**< If true, freeze ADC2 in Debug mode. */
    bool      enableFreezeAdc3; /**< If true, freeze ADC3 in Debug mode. */
} cy_stc_sar2_debug_freeze_config_t;

/** \} group_sar2_data_structures */

/***************************************
*       Function Prototypes
***************************************/
/**
* \addtogroup group_sar2_functions
* \{
*/

/* For each ADC */
cy_en_sar2_status_t Cy_SAR2_Init(PASS_SAR_Type * base, const cy_stc_sar2_config_t * config);
__STATIC_INLINE void Cy_SAR2_DeInit(PASS_SAR_Type * base);
__STATIC_INLINE void Cy_SAR2_Enable(PASS_SAR_Type * base);
__STATIC_INLINE void Cy_SAR2_Disable(PASS_SAR_Type * base);
__STATIC_INLINE uint32_t Cy_SAR2_GetPendingStatus(const PASS_SAR_Type * base);
__STATIC_INLINE uint32_t Cy_SAR2_GetWorkValidStatus(const PASS_SAR_Type * base);
__STATIC_INLINE uint32_t Cy_SAR2_GetWorkRangeStatus(const PASS_SAR_Type * base);
__STATIC_INLINE uint32_t Cy_SAR2_GetWorkRangeHiStatus(const PASS_SAR_Type * base);
__STATIC_INLINE uint32_t Cy_SAR2_GetWorkPulseStatus(const PASS_SAR_Type * base);
__STATIC_INLINE uint32_t Cy_SAR2_GetResultValidStatus(const PASS_SAR_Type * base);
__STATIC_INLINE uint32_t Cy_SAR2_GetResultRangeHiStatus(const PASS_SAR_Type * base);

/* For each channel */
cy_en_sar2_status_t Cy_SAR2_Channel_Init(PASS_SAR_Type * base, uint32_t channel,
                                                                    const cy_stc_sar2_channel_config_t * channelConfig);
void Cy_SAR2_Channel_DeInit(PASS_SAR_Type * base, uint32_t channel);
uint16_t Cy_SAR2_Channel_GetResult(PASS_SAR_Type * base, uint32_t channel, uint32_t * status);
uint16_t Cy_SAR2_Channel_GetWorkingData(PASS_SAR_Type * base, uint32_t channel, uint32_t * status);
__STATIC_INLINE uint32_t Cy_SAR2_Channel_GetGroupStatus(PASS_SAR_Type * base, uint32_t channel);
__STATIC_INLINE void Cy_SAR2_Channel_Enable(PASS_SAR_Type * base, uint32_t channel);
__STATIC_INLINE void Cy_SAR2_Channel_Disable(PASS_SAR_Type * base, uint32_t channel);
__STATIC_INLINE void Cy_SAR2_Channel_SoftwareTrigger(PASS_SAR_Type * base, uint32_t channel);
__STATIC_INLINE void Cy_SAR2_Channel_SetInterruptMask(PASS_SAR_Type * base, uint32_t channel, uint32_t intrMask);
__STATIC_INLINE uint32_t Cy_SAR2_Channel_GetInterruptMask(PASS_SAR_Type * base, uint32_t channel);
__STATIC_INLINE void Cy_SAR2_Channel_ClearInterrupt(PASS_SAR_Type * base, uint32_t channel, uint32_t intrMask);
__STATIC_INLINE uint32_t Cy_SAR2_Channel_GetInterruptStatus(PASS_SAR_Type * base, uint32_t channel);
__STATIC_INLINE uint32_t Cy_SAR2_Channel_GetInterruptStatusMasked(PASS_SAR_Type * base, uint32_t channel);
__STATIC_INLINE void Cy_SAR2_Channel_SetInterrupt(PASS_SAR_Type * base, uint32_t channel, uint32_t intrMask);

/* For diagnosis function */
cy_en_sar2_status_t Cy_SAR2_Diag_Init(PASS_SAR_Type * base, const cy_stc_sar2_diag_config_t * diagConfig);
__STATIC_INLINE void Cy_SAR2_Diag_Enable(PASS_SAR_Type * base);
__STATIC_INLINE void Cy_SAR2_Diag_Disable(PASS_SAR_Type * base);

/* For calibration */
__STATIC_INLINE void Cy_SAR2_TriggerCalibrationUpdate(PASS_SAR_Type * base);
__STATIC_INLINE bool Cy_SAR2_IsCalibrationUpdateDone(PASS_SAR_Type * base);
cy_en_sar2_status_t Cy_SAR2_SetDigitalCalibrationValue(PASS_SAR_Type * base,
                                                       const cy_stc_sar2_digital_calibration_config_t * digCalibConfig);
cy_en_sar2_status_t Cy_SAR2_GetDigitalCalibrationValue(PASS_SAR_Type * base,
                                                             cy_stc_sar2_digital_calibration_config_t * digCalibConfig);
cy_en_sar2_status_t Cy_SAR2_SetAltDigitalCalibrationValue(PASS_SAR_Type * base,
                                                    const cy_stc_sar2_digital_calibration_config_t * altDigCalibConfig);
cy_en_sar2_status_t Cy_SAR2_GetAltDigitalCalibrationValue(PASS_SAR_Type * base,
                                                          cy_stc_sar2_digital_calibration_config_t * altDigCalibConfig);
cy_en_sar2_status_t Cy_SAR2_SetAnalogCalibrationValue(PASS_SAR_Type * base,
                                                           cy_stc_sar2_analog_calibration_conifg_t * analogCalibConfig);
cy_en_sar2_status_t Cy_SAR2_GetAnalogCalibrationValue(PASS_SAR_Type * base,
                                                           cy_stc_sar2_analog_calibration_conifg_t * analogCalibConfig);
cy_en_sar2_status_t Cy_SAR2_SetAltAnalogCalibrationValue(PASS_SAR_Type * base,
                                                        cy_stc_sar2_analog_calibration_conifg_t * altAnalogCalibConfig);
cy_en_sar2_status_t Cy_SAR2_GetAltAnalogCalibrationValue(PASS_SAR_Type * base,
                                                        cy_stc_sar2_analog_calibration_conifg_t * altAnalogCalibConfig);

/* For debugging */
__STATIC_INLINE cy_en_sar2_ref_buf_mode_t Cy_SAR2_GetReferenceBufferMode(PASS_EPASS_MMIO_Type * base);
__STATIC_INLINE void Cy_SAR2_SetReferenceBufferMode(PASS_EPASS_MMIO_Type * base, cy_en_sar2_ref_buf_mode_t mode);
cy_en_sar2_status_t Cy_SAR2_SetDebugFreezeMode(PASS_EPASS_MMIO_Type * base,
                                                                   const cy_stc_sar2_debug_freeze_config_t * debConfig);

/* For SAR general trigger input / output trigger setting */
cy_en_sar2_status_t Cy_SAR2_SetGenericTriggerInput(PASS_EPASS_MMIO_Type * base, uint8_t numOfAdc,
                                                               uint8_t triggerInputNumber, uint8_t genericTriggerValue);
cy_en_sar2_status_t Cy_SAR2_SetGenericTriggerOutput(PASS_EPASS_MMIO_Type * base, uint8_t numOfAdc,
                                                              uint8_t triggerOutputNumber, uint8_t genericTriggerValue);

/* For temperature measurements */
double Cy_SAR2_CalculateDieTemperature(cy_en_sar2_vdda_range_t VDDARange, uint16_t adcVtempRawValue,
                                                                                               uint16_t adcVbgRawValue);

/*******************************************************************************
*                       In-line Function Implementation
*******************************************************************************/

/*******************************************************************************
* Function Name: Cy_SAR2_Enable
****************************************************************************//**
*
* Enables the SAR ADC block.
*
* \param base : The pointer to the SAR block.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR2_Enable(PASS_SAR_Type * base)
{
    base->CTL |= PASS_SAR_CTL_ENABLED_Msk;
}

/*******************************************************************************
* Function Name: Cy_SAR2_Disable
****************************************************************************//**
*
* Disables the SAR ADC block.
*
* \param base : The pointer to the SAR block.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR2_Disable(PASS_SAR_Type * base)
{
    base->CTL &= ~PASS_SAR_CTL_ENABLED_Msk;
}

/*******************************************************************************
* Function Name: Cy_SAR2_DeInit
****************************************************************************//**
*
* De-initializes the SAR ADC block, returns the register values to default.
*
* \param base : The pointer to the SAR block.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR2_DeInit(PASS_SAR_Type * base)
{
    base->PRECOND_CTL = 0UL;
    base->CTL = 0UL;
}

/*******************************************************************************
* Function Name: Cy_SAR2_GetPendingStatus
****************************************************************************//**
*
* Returns the trigger pending status.
*
* \param base
* The pointer to the SAR instance.
*
* \return Pending status. Each bit corresponds a channel, i.e.
* If bit0 is 1, ch.0 is pending for a trigger.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR2_GetPendingStatus(const PASS_SAR_Type * base)
{
    return base->TR_PEND;
}

/*******************************************************************************
* Function Name: Cy_SAR2_GetWorkValidStatus
****************************************************************************//**
*
* Returns the work register valid status.
*
* \param base
* The pointer to the SAR instance.
*
* \return Work register valid status. Each bit corresponds a channel, i.e.
* If bit0 is 1, ch.0's work register is valid.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR2_GetWorkValidStatus(const PASS_SAR_Type * base)
{
    return base->WORK_VALID;
}

/*******************************************************************************
* Function Name: Cy_SAR2_GetWorkRangeStatus
****************************************************************************//**
*
* Returns work register range status.
*
* \param base
* The pointer to the SAR instance.
*
* \return Work register range status. Each bit correspond a channel, i.e.
* If bit0 is 1, ch.0 detected a range.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR2_GetWorkRangeStatus(const PASS_SAR_Type * base)
{
    return base->WORK_RANGE;
}

/*******************************************************************************
* Function Name: Cy_SAR2_GetWorkRangeHiStatus
****************************************************************************//**
*
* Returns work register range high status.
*
* \param base
* The pointer to the SAR instance.
*
* \return Work register range Hi status. Each bit corresponds a channel, i.e.
* If bit0 is 1, ch.0 detected "out of range" and the value was above the high
* threshold.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR2_GetWorkRangeHiStatus(const PASS_SAR_Type * base)
{
    return base->WORK_RANGE_HI;
}

/*******************************************************************************
* Function Name: Cy_SAR2_GetWorkPulseStatus
****************************************************************************//**
*
* Returns the work register pulse status.
*
* \param base
* The pointer to the SAR instance.
*
* \return Work register pulse status. Each bit corresponds a channel, i.e.
* If bit0 is 1, ch.0 detected a pulse.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR2_GetWorkPulseStatus(const PASS_SAR_Type * base)
{
    return base->WORK_PULSE;
}

/*******************************************************************************
* Function Name: Cy_SAR2_GetResultValidStatus
****************************************************************************//**
*
* Returns result register valid status.
*
* \param base
* The pointer to the SAR instance.
*
* \return Result register pulse status. Each bit corresponds a channel, i.e.
* If bit0 is 1, ch.0's result register is valid.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR2_GetResultValidStatus(const PASS_SAR_Type * base)
{
    return base->RESULT_VALID;
}

/*******************************************************************************
* Function Name: Cy_SAR2_GetResultRangeHiStatus
****************************************************************************//**
*
* Returns result register range high status.
*
* \param base
* The pointer to the SAR instance.
*
* \return Result register range high. Each bit corresponds a channel, i.e.
* If bit0 is 1, ch.0 detected "out of range" and the value was above the high
* threshold.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR2_GetResultRangeHiStatus(const PASS_SAR_Type * base)
{
    return base->RESULT_RANGE_HI;
}

/*******************************************************************************
* Function Name: Cy_SAR2_Channel_Enable
****************************************************************************//**
*
* Enables a corresponding channel.
*
* \param base
* The pointer to the SAR instance.
*
* \param channel
* The channel number.
*
* \note To enable a group either start with enabling the last channel first
* and the first channel last, or start the trigger after all channels are
* enabled.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR2_Channel_Enable(PASS_SAR_Type * base, uint32_t channel)
{
    CY_ASSERT_L1(CY_SAR2_CHAN_NUM_VALID(base, channel));

    base->CH[channel].ENABLE |= PASS_SAR_CH_ENABLE_CHAN_EN_Msk;
}

/*******************************************************************************
* Function Name: Cy_SAR2_Channel_Disable
****************************************************************************//**
*
* Disables a corresponding channel.
*
* \param base
* The pointer to the SAR instance.
*
* \param channel
* The channel number.
*
* \note To disable a group either stop the trigger first or begin with disabling
* the lowest channel first.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR2_Channel_Disable(PASS_SAR_Type * base, uint32_t channel)
{
    CY_ASSERT_L1(CY_SAR2_CHAN_NUM_VALID(base, channel));

    base->CH[channel].ENABLE &= ~PASS_SAR_CH_ENABLE_CHAN_EN_Msk;
}

/*******************************************************************************
* Function Name: Cy_SAR2_Channel_SoftwareTrigger
****************************************************************************//**
*
* Issues a software start trigger.
*
* \param base
* The pointer to the SAR instance.
*
* \param channel
* The channel number.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR2_Channel_SoftwareTrigger(PASS_SAR_Type * base, uint32_t channel)
{
    CY_ASSERT_L1(CY_SAR2_CHAN_NUM_VALID(base, channel));

    SAR2_CH_TR_CMD(base, channel) |= _VAL2FLD(PASS_SAR_CH_TR_CMD_START, 1UL);
}

/*******************************************************************************
* Function Name: Cy_SAR2_Diag_Enable
****************************************************************************//**
*
* Enables the diagnostic function.
*
* \param  base: The pointer to the hardware SAR block.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR2_Diag_Enable(PASS_SAR_Type * base)
{
    base->DIAG_CTL |= _VAL2FLD(PASS_SAR_DIAG_CTL_DIAG_EN, 1UL);
}

/*******************************************************************************
* Function Name: Cy_SAR2_Diag_Disable
****************************************************************************//**
*
* Disables the diagnostic function.
*
* \param  base: The pointer to the hardware SAR block.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR2_Diag_Disable(PASS_SAR_Type * base)
{
    base->DIAG_CTL &= ~PASS_SAR_DIAG_CTL_DIAG_EN_Msk;
}

/*******************************************************************************
* Function Name: Cy_SAR2_TriggerCalibrationUpdate
****************************************************************************//**
*
* Triggers calibration update. After triggering, coherently copies the values
* from alternate calibration regs to the current calibration regs.
*
* \param  base: The pointer to the hardware SAR block.
*
* \note Set an alternate calibration value before calling this function.
*       After triggering, calibration will be updated as soon as the SAR is
*       idle or a "continuous" triggered group completes.
*       To determine whether calibration update is done or not call
*       the Cy_SAR2_IsCalibrationUpdateDone function.
*******************************************************************************/
__STATIC_INLINE void Cy_SAR2_TriggerCalibrationUpdate(PASS_SAR_Type * base)
{
    base->CAL_UPD_CMD = _VAL2FLD(PASS_SAR_CAL_UPD_CMD_UPDATE, 1UL);
}

/*******************************************************************************
* Function Name: Cy_SAR2_IsCalibrationUpdateDone
****************************************************************************//**
*
* Gets the status of calibration update.
*
* \param  base: The pointer to the hardware SAR block.
*
* \return If true, calibration update is done.
*         If false, calibration update is not yet done.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_SAR2_IsCalibrationUpdateDone(PASS_SAR_Type * base)
{
    return (_FLD2BOOL(PASS_SAR_CAL_UPD_CMD_UPDATE, base->CAL_UPD_CMD));
}

/*******************************************************************************
* Function Name: Cy_SAR2_Channel_SetInterruptMask
****************************************************************************//**
*
* Configures the channel interrupt.
*
* \param base
* The pointer to the SAR instance.
*
* \param channel
* The channel number.
*
* \param intrMask
* The mask of interrupts. Select one or more values from
* \ref group_sar2_macros_interrupt and "OR" them together:
* - \ref CY_SAR2_INT_GRP_DONE
* - \ref CY_SAR2_INT_GRP_CANCELLED
* - \ref CY_SAR2_INT_GRP_OVERFLOW
* - \ref CY_SAR2_INT_CH_RANGE
* - \ref CY_SAR2_INT_CH_PULSE
* - \ref CY_SAR2_INT_CH_OVERFLOW
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR2_Channel_SetInterruptMask(PASS_SAR_Type * base, uint32_t channel, uint32_t intrMask)
{
    CY_ASSERT_L1(CY_SAR2_CHAN_NUM_VALID(base, channel));

    SAR2_CH_INTR_MASK(base, channel) = (intrMask & CY_SAR2_INTR);
}

/*******************************************************************************
* Function Name: Cy_SAR2_Channel_GetInterruptMask
****************************************************************************//**
*
* Returns interrupt mask configuration.
*
* \param base
* The pointer to the SAR instance.
*
* \param channel
* The channel number.
*
* \return Interrupt mask value \ref group_sar2_macros_interrupt
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR2_Channel_GetInterruptMask(PASS_SAR_Type * base, uint32_t channel)
{
    return SAR2_CH_INTR_MASK(base, channel);
}

/*******************************************************************************
* Function Name: Cy_SAR2_Channel_ClearInterrupt
****************************************************************************//**
*
* Clears the interrupt.
* The interrupt must be cleared with this function so that the hardware
* can set subsequent interrupts and those interrupts can be forwarded
* to the interrupt controller, if enabled.
*
* \param base
* The pointer to the SAR instance.
*
* \param channel
* The channel number.
*
* \param intrMask
* The mask of interrupts to clear. Typically this will be the value returned
* from \ref Cy_SAR_GetInterruptStatus.
* Alternately, select one or more values from \ref group_sar2_macros_interrupt
* and "OR" them together.
* - \ref CY_SAR2_INT_GRP_DONE
* - \ref CY_SAR2_INT_GRP_CANCELLED
* - \ref CY_SAR2_INT_GRP_OVERFLOW
* - \ref CY_SAR2_INT_CH_RANGE
* - \ref CY_SAR2_INT_CH_PULSE
* - \ref CY_SAR2_INT_CH_OVERFLOW
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR2_Channel_ClearInterrupt(PASS_SAR_Type * base, uint32_t channel, uint32_t intrMask)
{
    CY_ASSERT_L1(CY_SAR2_CHAN_NUM_VALID(base, channel));

    SAR2_CH_INTR(base, channel) = (intrMask & CY_SAR2_INTR);
    /* Dummy read for buffered writes. */
    (void) SAR2_CH_INTR(base, channel);
}

/*******************************************************************************
* Function Name: Cy_SAR2_Channel_GetInterruptStatus
****************************************************************************//**
*
* Returns the channel interrupt register status.
*
* \param base
* The pointer to the SAR instance.
*
* \param channel
* The channel number.
*
* \return status
* Contents of the channel interrupt register. See
* \ref group_sar2_macros_interrupt.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR2_Channel_GetInterruptStatus(PASS_SAR_Type * base, uint32_t channel)
{
    CY_ASSERT_L1(CY_SAR2_CHAN_NUM_VALID(base, channel));

    return (SAR2_CH_INTR(base, channel));
}

/*******************************************************************************
* Function Name: Cy_SAR2_Channel_GetInterruptStatusMasked
****************************************************************************//**
*
* Returns interrupt status.
*
* \param base
* The pointer to the SAR instance.
*
* \param channel
* The channel number.
*
* \return status
* Contents of the channel interrupt register. See
* \ref group_sar2_macros_interrupt.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR2_Channel_GetInterruptStatusMasked(PASS_SAR_Type * base, uint32_t channel)
{
    CY_ASSERT_L1(CY_SAR2_CHAN_NUM_VALID(base, channel));

    return (SAR2_CH_INTR_MASKED(base, channel));
}

/*******************************************************************************
* Function Name: Cy_SAR2_Channel_SetInterrupt
****************************************************************************//**
*
* Triggers an interrupt with software.
*
* \param base
* The pointer to the SAR instance.
*
* \param channel
* The channel number.
*
* \param intrMask
* The mask of interrupts to set.
* Select one or more values from \ref group_sar2_macros_interrupt and "OR" them
* together.
* - \ref CY_SAR2_INT_GRP_DONE
* - \ref CY_SAR2_INT_GRP_CANCELLED
* - \ref CY_SAR2_INT_GRP_OVERFLOW
* - \ref CY_SAR2_INT_CH_RANGE
* - \ref CY_SAR2_INT_CH_PULSE
* - \ref CY_SAR2_INT_CH_OVERFLOW
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR2_Channel_SetInterrupt(PASS_SAR_Type * base, uint32_t channel, uint32_t intrMask)
{
    CY_ASSERT_L1(CY_SAR2_CHAN_NUM_VALID(base, channel));

    SAR2_CH_INTR_SET(base, channel) = (intrMask & CY_SAR2_INTR);
}

/*******************************************************************************
* Function Name: Cy_SAR2_Channel_GetGroupStatus
****************************************************************************//**
*
* Returns the group conversion status.
*
* \param base
* The pointer to an SAR instance.
*
* \param channel
* The channel number.
*
* \return status
* The status of the group, conversion status bits ORed.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR2_Channel_GetGroupStatus(PASS_SAR_Type * base, uint32_t channel)
{
    CY_ASSERT_L1(CY_SAR2_CHAN_NUM_VALID(base, channel));

    return (base->CH[channel].GRP_STAT);
}

/*******************************************************************************
* Function Name: Cy_SAR2_SetReferenceBufferMode
****************************************************************************//**
*
* Sets ePASS MMIO reference buffer mode.
*
* \param base
* The pointer to the PASS instance.
*
* \param mode
* The reference buffer mode number.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR2_SetReferenceBufferMode(PASS_EPASS_MMIO_Type * base, cy_en_sar2_ref_buf_mode_t mode)
{
    base->PASS_CTL = _CLR_SET_FLD32U(base->PASS_CTL, PASS_EPASS_MMIO_PASS_CTL_REFBUF_MODE, mode);
}

/*******************************************************************************
* Function Name: Cy_SAR2_GetReferenceBufferMode
****************************************************************************//**
*
* Gets ePASS MMIO reference buffer mode.
*
* \param base
* The pointer to the PASS instance.
*
* \return
* \ref cy_en_sar2_ref_buf_mode_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_sar2_ref_buf_mode_t Cy_SAR2_GetReferenceBufferMode(PASS_EPASS_MMIO_Type * base)
{
    return (cy_en_sar2_ref_buf_mode_t)(int32_t)(uint32_t)_FLD2VAL(PASS_EPASS_MMIO_PASS_CTL_REFBUF_MODE, base->PASS_CTL);
}


/** \} group_sar2_functions */

#if defined(__cplusplus)
}
#endif

#endif /* CY_SAR2_H */

/** \} group_sar2 */
#endif /* CY_IP_MXS40EPASS_ESAR */

/* [] END OF FILE */
