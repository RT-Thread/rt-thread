/***************************************************************************//**
* \file cy_adcmic.h
* \version 1.0
*
* Provides an API declaration of the ADCMic driver.
*
********************************************************************************
* \copyright
* Copyright 2022 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/**
* \addtogroup group_adcmic
* \{
* ADCMic driver is used to process analog and digital microphone signal and
* DC signal with the mxs40adcmic IP. This IP interfaces with Delta-Sigma modulator part
* of the s40adcmic and implements CIC, decimation (FIR) and biquad filters.
* The ADC result is read by the CPU or the DMA from the FIFO of mxs40adcmic
* (and from CIC register for DC measurement). Instead of taking modulator data
* from s40adcmic, mxs40adcmic can also be configured to take PDM input
* directly from an external digital microphone.
*
* \image html ADCMicBlockDiagram.png
*
* Consult the datasheet of your device for details of the
* clocking system.
*
* The high level features of the subsystem are:
*   - Analog (MIC) and digital (PDM) microphones support.
*   - Sample rate 8/16 ksps for audio (MIC and PDM modes).
*   - Configurable biquad filter for custom audio equalization.
*   - Selectable DC measurement range.
*   - Interrupt & trigger generation.
*   - Built-in FIFO buffer (for audio only).
*
* \section group_adcmic_usage Usage
*
* The high level steps to use this driver are:
*
*   -# \ref group_adcmic_initialization
*   -# \ref group_adcmic_clock
*   -# \ref group_adcmic_trigger
*   -# \ref group_adcmic_timer
*   -# \ref group_adcmic_interrupt
*   -# \ref group_adcmic_dc_measurement
*   -# \ref group_adcmic_fifo
*
* \section group_adcmic_initialization Initialization and Enabling
*
* To configure the ADCMic subsystem call \ref Cy_ADCMic_Init.
* Pass in a pointer to the \ref MXS40ADCMIC_Type structure for the base hardware register address,
* pass in the configuration structure \ref cy_stc_adcmic_config_t, and
* pass in the operation mode.
*
* After initialization, call \ref Cy_ADCMic_Enable to enable the block.
*
* The configuration can be defined as follows:
* \snippet adcmic_snippet/snippet.c SNIPPET_ADCMIC_CFG
*
* \subsection group_adcmic_mic Analog Microphone (MIC) Mode
*
* \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_MIC_OP
*
* Usually the MIC mode is used with FIFO, see \ref group_adcmic_fifo
*
* \subsection group_adcmic_pdm Digital Microphone (PDM) Mode
*
* \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_PDM_OP
*
* Usually the MIC mode is used with FIFO, see \ref group_adcmic_fifo
*
* \subsection group_adcmic_dc DC Measurement (DC) Mode
*
* \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_DC_OP
*
* \subsection group_adcmic_biquad Biquad filter Initialization
*
* The biquad filter usually is used to the audio stream equalization (in MIC or PDM modes):
* \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_BIQUAD
* \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_BIQUAD_INIT
*
* \section group_adcmic_clock Clocks
*
* The ADCMic requires two input clocks:
* - clk_sys - recommended frequency is 96MHz, input for the \ref group_adcmic_timer, usually is routed from one of the \ref group_sysclk_clk_hf
* - clk_hf - recommended frequency is 24MHz, the audio (MIC and PDM modes) reference clock, usually is routed from one of the \ref group_sysclk_clk_hf
*
* For more exact information on the ADCMic clock routing, refer to the datasheet for your device.
*
* \section group_adcmic_trigger Triggering
*
* The ADCMic subsystem has two output triggers: from the timer and from the FIFO,
* the timer generates trigger always if enabled, the FIFO trigger could be
* configured separately for MIC and PDM modes by the \ref cy_stc_adcmic_mic_config_t::fifoTrigger and
* \ref cy_stc_adcmic_pdm_config_t::fifoTrigger respectively.
*
* Also, they could be routed to any periphery using \ref group_trigmux driver, e.g. to DW block:
* \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_TRIGGER
*
* \section group_adcmic_timer Timer
*
* The Timer is used for DC measurement for two purposes:
* - generate periodic events based on ADCMic clk_sys clock.
* - count the CIC data update events.
*
* The timer period and input signal source are configured by the \ref cy_stc_adcmic_dc_config_t::timerPeriod and
* \ref cy_stc_adcmic_dc_config_t::timerInput fields correspondingly.
*
* \section group_adcmic_interrupt Handling Interrupts
*
* The ADCMic subsystem has two interrupt sources: the timer and the FIFO.
* The FIFO interrupt can have several reasons, see \ref group_adcmic_macros_fifo_status
*
* The ADCMic interrupt to the NVIC is raised any time the intersection (logic and) of the interrupt
* flags and the corresponding interrupt masks are non-zero.
*
* Implement an interrupt routine and assign it to the ADCMic interrupt.
* Use the pre-defined enumeration, adcmic_interrupt_adcmic_IRQn, as the interrupt source for the ADCMic.
*
* The following code snippet demonstrates how to implement a routine to handle the interrupt.
* The routine gets called when any one of the ADCMic interrupts are triggered.
* When servicing an interrupt, the user must clear the interrupt so that subsequent
* interrupts can be handled.
*
* The following code snippet demonstrates how to configure and enable the interrupt.
* \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_ISR
* \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_CONFIG_INTR
*
* Alternately, instead of handling the interrupts, the \ref Cy_ADCMic_IsEndConversion function
* allows for firmware polling of the end of DC conversion status.
*
* \section group_adcmic_fifo FIFO Usage
* The ADCMic subsystem in the MIC and PDM modes stores the audio data into the FIFO.
* It can be configured separately for the MIC and PDM modes using
* \ref cy_stc_adcmic_mic_config_t::fifoFull,
* \ref cy_stc_adcmic_mic_config_t::fifoEmpty and
* \ref cy_stc_adcmic_pdm_config_t::fifoFull,
* \ref cy_stc_adcmic_pdm_config_t::fifoEmpty
* respectively and served either by ISR:
* \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_ISR
* Or by DMA:
* \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_TRIGGER
*
* \section group_adcmic_dc_measurement DC Voltage Measurement Accuracy
*
* * The Offset is practically a raw count of the measured Ground voltage.
* * The Gain is essentially an amount of raw counts per 1 Volt of input voltage.
*   It depends on the DC measurement range \ref cy_en_adcmic_dc_range_t.
*
* The default Offset \ref CY_ADCMIC_DC_OFFSET and
* Gain for both ranges \ref CY_ADCMIC_DC_1_8_GAIN and \ref CY_ADCMIC_DC_3_6_GAIN are precalculated
* based on the theory of the ADCMic operation \ref group_adcmic_macros_dc_measurement.
*
* So basically the raw count retrieved using \ref Cy_ADCMic_GetDcResult for the desired DC input
* can be directly feed into any of the \ref Cy_ADCMic_CountsTo_Volts, \ref Cy_ADCMic_CountsTo_mVolts,
* or \ref Cy_ADCMic_CountsTo_uVolts functions and have for some extend accurate result.
*
* However, to increase the accuracy the real ADCMic Gain and Offset can be defined by physically
* measuring the Reference Ground \ref CY_ADCMIC_REFGND and the Reference BandGap \ref CY_ADCMIC_BGREF.
*
* For example:
* \snippet adcmic_snippet/snippet.c SNIPPET_ADCMIC_DC_MEASURE_AVG
* \note this code snippet is not the only valid way to use this driver - it is just one possible example how it can be used.
*
* \subsection group_adcmic_dc_vbg_calib BandGap Calibration
* For further increase the measurement accuracy, the real BandGap voltage can be defined
* using external precise reference with exact known voltage:
*
* Real BandGap voltage = external reference exact voltage * (BandGap counts - GND counts) / (external reference counts - GND counts).
*
* And then use it in the Gain calculation as shown above instead of the nominal BandGap voltage \ref CY_ADCMIC_DC_VBG.
*
* \subsection group_adcmic_dc_double_sampling Correlated Double Sampling
* To further improve the DC measurement accuracy, the low frequency Noise could be dynamically
* removed by performing two measurements for each input channel sequentially:
* one measuring the desired DC input and the other one measuring the \ref CY_ADCMIC_REFGND.
* The second measurement of the\ref CY_ADCMIC_REFGND contains only the low frequency Noise (Flick Noise) information.
* It is important to perform these two measurements one after another as close as possible.
* The final true ADC output value is then obtained by subtracting the ADC output of the
* second measurement from the ADC output of the first measurement.
*
* For example:
* \snippet adcmic_snippet/snippet.c SNIPPET_ADCMIC_DC_MEASURE_DS
* \note this code snippet is not the only valid way to use this driver - it is just one possible example how it can be used.
*
* \section group_adcmic_more_information More Information
* For more information on the ADCMic ADC subsystem, refer to the datasheet of your device.
*
* \section group_adcmic_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.0</td>
*     <td>
*       The cy_en_adcmic_source_t is renamed to \ref cy_en_adcmic_mode_t.<br>
*       The CY_ADCMIC_480KSPS item is removed from the \ref cy_en_adcmic_sample_rate_t.<br>
*       The cy_en_adcmic_dc_conv_time_t is removed.<br>
*       The cy_stc_adcmic_fifo_config_t is removed.<br>
*       The cy_en_adcmic_dc_result_latch_mode_t is removed.<br>
*       The cy_stc_adcmic_audio_analog_path_config_t is renamed to \ref cy_stc_adcmic_mic_config_t.<br>
*       The cy_stc_adcmic_audio_digital_path_config_t is renamed to \ref cy_stc_adcmic_pdm_config_t.<br>
*       The cy_stc_adcmic_dc_path_config_t is renamed to \ref cy_stc_adcmic_dc_config_t.<br>
*
*       The micPd parameter is removed from the \ref cy_stc_adcmic_mic_config_t<br>
*
*       The next parameters are added into \ref cy_stc_adcmic_mic_config_t :<br>
*       * \ref cy_stc_adcmic_mic_config_t::sampleRate,<br>
*       * \ref cy_stc_adcmic_mic_config_t::biQuadConfig,<br>
*       * \ref cy_stc_adcmic_mic_config_t::fifoTrigger,<br>
*       * \ref cy_stc_adcmic_mic_config_t::fifoFull,<br>
*       * \ref cy_stc_adcmic_mic_config_t::fifoEmpty.<br>
*
*       The clockDiv parameter is removed from the \ref cy_stc_adcmic_pdm_config_t<br>
*
*       The next parameters are added into \ref cy_stc_adcmic_pdm_config_t :<br>
*       * \ref cy_stc_adcmic_pdm_config_t::sampleRate,<br>
*       * \ref cy_stc_adcmic_pdm_config_t::biQuadConfig,<br>
*       * \ref cy_stc_adcmic_pdm_config_t::fifoTrigger,<br>
*       * \ref cy_stc_adcmic_pdm_config_t::fifoFull,<br>
*       * \ref cy_stc_adcmic_pdm_config_t::fifoEmpty.<br>
*
*       The next parameters are removed from the \ref cy_stc_adcmic_dc_config_t :<br>
*       * tmrLatch,<br>
*       * time.<br>
*
*       The next parameter is renamed in the \ref cy_stc_adcmic_dc_config_t :<br>
*       * input -> \ref cy_stc_adcmic_dc_config_t::channel.<br>
*
*       The next parameters are added into \ref cy_stc_adcmic_dc_config_t :<br>
*       * \ref cy_stc_adcmic_dc_config_t::timerPeriod,<br>
*       * \ref cy_stc_adcmic_dc_config_t::timerInput,<br>
*       * \ref cy_stc_adcmic_dc_config_t::context.<br>
*
*       The next parameters are removed from the cy_stc_adcmic_config_t :<br>
*       * clockDiv,<br>
*       * source,<br>
*       * sampleRate,<br>
*       * biQuadConfig,<br>
*       * fifoConfig,<br>
*       * tmrTrgConfig.<br>
*
*       The next parameters are renamed in the cy_stc_adcmic_config_t :<br>
*       * anaConfig -> \ref cy_stc_adcmic_config_t::micConfig,<br>
*       * digConfig -> \ref cy_stc_adcmic_config_t::pdmConfig.<br>
*
*       The new parameter 'mode' is added to the \ref Cy_ADCMic_Init.<br>
*       The \ref Cy_ADCMic_Init functions if fixed to proper process the \ref cy_stc_adcmic_mic_config_t::micClamp setting.<br>
*       The Cy_ADCMic_StartConvert and Cy_ADCMic_StopConvert API functions are removed.<br>
*       The \ref Cy_ADCMic_Enable and \ref Cy_ADCMic_Disable are updated to inherit the Start/StopConvert functionality.<br>
*       The Cy_ADCMic_SleepMic and Cy_ADCMic_WakeUpMic API functions are removed.<br>
*       The \ref Cy_ADCMic_Enable and \ref Cy_ADCMic_Disable are updated to power down all the analog subsystems at disabling and power up them at enabling.<br>
*       The parameter dcChannel of the \ref Cy_ADCMic_SelectDcChannel is renamed to channel.<br>
*       The function Cy_ADCMic_SetDcConvTime is removed.<br>
*       The interface of \ref Cy_ADCMic_SetDcOffset, \ref Cy_ADCMic_SetDcGain, \ref Cy_ADCMic_CountsTo_mVolts, \ref Cy_ADCMic_CountsTo_uVolts,<br>
*       and \ref Cy_ADCMic_CountsTo_Volts functions is changed: the 'base' parameters are removed, and the 'context' parameters are added.<br>
*       The documentation is enhanced with code snippets: \ref group_adcmic_dc_measurement, \ref group_adcmic_dc_double_sampling.
*     </td>
*     <td>Usability review</td>
*   </tr>
*   <tr>
*     <td>0.1</td>
*     <td>This is a pre-production driver release. The driver is not recommended for production use, unless the functionality is delivered in Cypress-provided applications.</td>
*     <td>Pre-production support of the CAT1B Devices</td>
*   </tr>
* </table>
*
* \defgroup group_adcmic_macros Macros
* \{
*   \defgroup group_adcmic_macros_interrupt        Interrupt Masks
*   \defgroup group_adcmic_macros_triggers         Triggers
*   \defgroup group_adcmic_macros_reg_pointers     Register Pointers
*   \defgroup group_adcmic_macros_fifo_status      FIFO Status Masks
*   \defgroup group_adcmic_macros_fifo_samples     FIFO Samples definitions
*   \defgroup group_adcmic_macros_dc_measurement   DC measurement definitions
* \}
* \defgroup group_adcmic_enums Enumerated Types
* \defgroup group_adcmic_data_structures Data Structures
* \defgroup group_adcmic_functions Functions
* \{
*   \defgroup group_adcmic_functions_basic         Initialization and Basic Functions
*   \defgroup group_adcmic_functions_interrupt     Interrupt Functions
*   \defgroup group_adcmic_functions_fifo          FIFO Functions
*   \defgroup group_adcmic_functions_dc            DC Measurement Functions
*   \defgroup group_adcmic_functions_timer         Timer Functions
*   \defgroup group_adcmic_functions_mic           Analog Microphone (MIC) Functions
* \}
*/

#if !defined (CY_ADCMIC_H)
#define CY_ADCMIC_H

#include "cy_device_headers.h"

#if defined (CY_IP_MXS40ADCMIC)

#include "cy_syslib.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
* \addtogroup group_adcmic_macros
* \{
*/
/** Driver major version */
#define CY_ADCMIC_DRV_VERSION_MAJOR            1

/** Driver minor version */
#define CY_ADCMIC_DRV_VERSION_MINOR            0

/** ADCMic PDL ID */
#define CY_ADCMIC_ID                           CY_PDL_DRV_ID(0x48U)

/**
* \addtogroup group_adcmic_macros_interrupt
* \{
*/

#define CY_ADCMIC_INTR_DC     (MXS40ADCMIC_ADCMIC_INTR_INTERRUPT_DC_Msk)   /**< DC interrupt mask */
#define CY_ADCMIC_INTR_DATA   (MXS40ADCMIC_ADCMIC_INTR_INTERRUPT_DATA_Msk) /**< DATA interrupt mask */
#define CY_ADCMIC_INTR        (CY_ADCMIC_INTR_DC | CY_ADCMIC_INTR_DATA)    /**< Combined interrupt mask */

/** \} group_adcmic_macros_interrupt */

/**
* \addtogroup group_adcmic_macros_triggers
* \{
*/

#define CY_ADCMIC_TRIG_DC     (MXS40ADCMIC_ADCMIC_TRIGGER_CLR_TR_DC_Msk)   /**< DC trigger mask, to be used with \ref Cy_ADCMic_ClearTrigger */
#define CY_ADCMIC_TRIG_DATA   (MXS40ADCMIC_ADCMIC_TRIGGER_CLR_TR_DATA_Msk) /**< DATA trigger mask, to be used with \ref Cy_ADCMic_ClearTrigger */
#define CY_ADCMIC_TRIG        (CY_ADCMIC_TRIG_DC | CY_ADCMIC_TRIG_DATA)    /**< Combined interrupt mask, to be used with \ref Cy_ADCMic_ClearTrigger */

/** \} group_adcmic_macros_triggers */

/**
* \addtogroup group_adcmic_macros_reg_pointers
* \{
*/

/** The pointer to the FIFO data read register, to be used for the DMA data acquisition */
#define CY_ADCMIC_FIFO_DATA_REG_PTR(base)   ((void*)&((base)->ADCMIC_DATA))

/** The pointer to the trigger clearing register, to be used for the DMA data acquisition */
#define CY_ADCMIC_TRIGGER_CLR_REG_PTR(base) ((void*)&((base)->ADCMIC_TRIGGER_CLR))

/** \} group_adcmic_macros_reg_pointers */

/**
* \addtogroup group_adcmic_macros_fifo_status
* \{
*/
#define CY_ADCMIC_FIFO_OVERFLOW     (0x01U)   /**< FIFO overflow status mask */
#define CY_ADCMIC_FIFO_PRG_FULL     (0x02U)   /**< FIFO programmable full status mask */
#define CY_ADCMIC_FIFO_ALMOST_FULL  (0x04U)   /**< FIFO almost full status mask */
#define CY_ADCMIC_FIFO_FULL         (0x08U)   /**< FIFO full status mask */
#define CY_ADCMIC_FIFO_UNDERFLOW    (0x10U)   /**< FIFO underflow status mask */
#define CY_ADCMIC_FIFO_PRG_EMPTY    (0x20U)   /**< FIFO programmable empty status mask */
#define CY_ADCMIC_FIFO_ALMOST_EMPTY (0x40U)   /**< FIFO almost empty status mask */
#define CY_ADCMIC_FIFO_EMPTY        (0x80U)   /**< FIFO empty status mask */
/** \} group_adcmic_macros_fifo_status */

/**
* \addtogroup group_adcmic_macros_fifo_samples
* To be used with low-level API \ref Cy_ADCMic_ReadFifo.
* \{
*/
#define CY_ADCMIC_FIFO_FIRST_SAMPLE_Pos     (0U)           /**< the ADCMIC_DATA first sample position */
#define CY_ADCMIC_FIFO_FIRST_SAMPLE_Msk     (0x0000FFFFUL) /**< the ADCMIC_DATA first sample mask */
#define CY_ADCMIC_FIFO_SECOND_SAMPLE_Pos    (16U)          /**< the ADCMIC_DATA second sample position */
#define CY_ADCMIC_FIFO_SECOND_SAMPLE_Msk    (0xFFFF0000UL) /**< the ADCMIC_DATA second sample mask */
/** \} group_adcmic_macros_fifo_samples */

/**
* \addtogroup group_adcmic_macros_dc_measurement
* To be used for DC measurement voltage calculation/calibration.
* \{
*/
/** The Full Scale counts */
#define CY_ADCMIC_DC_FS         (0xFFFFUL)
/** The coefficient to calculate lower range limit count */
#define CY_ADCMIC_DC_LO         (3U)
/** The coefficient to calculate upper range limit count, scaled by 10000 to avoid fractional math */
#define CY_ADCMIC_DC_HI         (3725U)
/** The default raw count offset for DC measurement */
#define CY_ADCMIC_DC_OFFSET     (-((int16_t)CY_SYSLIB_DIV_ROUND(CY_ADCMIC_DC_FS, CY_ADCMIC_DC_LO)))
/** The upper range limit count */
#define CY_ADCMIC_DC_HI_CNT     ((int16_t)CY_SYSLIB_DIV_ROUND(CY_ADCMIC_DC_FS * CY_ADCMIC_DC_HI, 10000U))
/** The full range counts, scaled by 10 to avoid fractional math */
#define CY_ADCMIC_DC_FS_CNT     ((uint32_t)(CY_ADCMIC_DC_HI_CNT - CY_ADCMIC_DC_OFFSET) * 10U)
/** The default amount of raw counts per 1 volt for 3.6V range */
#define CY_ADCMIC_DC_3_6_GAIN   ((int16_t)CY_SYSLIB_DIV_ROUND(CY_ADCMIC_DC_FS_CNT, 36U))
/** The default amount of raw counts per 1 volt for 1.8V range */
#define CY_ADCMIC_DC_1_8_GAIN   ((int16_t)CY_SYSLIB_DIV_ROUND(CY_ADCMIC_DC_FS_CNT, 18U))
/** The BandGap reference nominal voltage in millivolts */
#define CY_ADCMIC_DC_VBG        (850L)
/** \} group_adcmic_macros_dc_measurement */
/** \} group_adcmic_macros */

/** \addtogroup group_adcmic_enums
* \{
*/

/** The ADC error codes */
typedef enum
{
    CY_ADCMIC_SUCCESS                 = 0x00UL,                                      /**< Successful */
    CY_ADCMIC_BAD_PARAM               = CY_ADCMIC_ID | CY_PDL_STATUS_ERROR | 0x01UL, /**< One or more invalid parameters */
    CY_ADCMIC_TIMEOUT                 = CY_ADCMIC_ID | CY_PDL_STATUS_ERROR | 0x02UL, /**< Timeout */
    CY_ADCMIC_CONVERSION_NOT_COMPLETE = CY_ADCMIC_ID | CY_PDL_STATUS_INFO  | 0x03UL, /**< Conversion is not complete */
    CY_ADCMIC_UNKNOWN                 = CY_ADCMIC_ID | CY_PDL_STATUS_ERROR | 0xFFUL, /**< Unknown failure */
} cy_en_adcmic_status_t;


/** The PGA gain settings */
typedef enum
{
    CY_ADCMIC_PGA_GAIN_0  = 0U,  /**<  0 db */
    CY_ADCMIC_PGA_GAIN_1  = 1U,  /**<  1 db */
    CY_ADCMIC_PGA_GAIN_2  = 2U,  /**<  2 db */
    CY_ADCMIC_PGA_GAIN_3  = 3U,  /**<  3 db */
    CY_ADCMIC_PGA_GAIN_4  = 4U,  /**<  4 db */
    CY_ADCMIC_PGA_GAIN_5  = 5U,  /**<  5 db */
    CY_ADCMIC_PGA_GAIN_6  = 6U,  /**<  6 db */
    CY_ADCMIC_PGA_GAIN_7  = 7U,  /**<  7 db */
    CY_ADCMIC_PGA_GAIN_8  = 8U,  /**<  8 db */
    CY_ADCMIC_PGA_GAIN_9  = 9U,  /**<  9 db */
    CY_ADCMIC_PGA_GAIN_10 = 10U, /**< 10 db */
    CY_ADCMIC_PGA_GAIN_11 = 11U, /**< 11 db */
    CY_ADCMIC_PGA_GAIN_12 = 12U, /**< 12 db */
    CY_ADCMIC_PGA_GAIN_13 = 13U, /**< 13 db */
    CY_ADCMIC_PGA_GAIN_14 = 14U, /**< 14 db */
    CY_ADCMIC_PGA_GAIN_15 = 15U, /**< 15 db */
    CY_ADCMIC_PGA_GAIN_16 = 16U, /**< 16 db */
    CY_ADCMIC_PGA_GAIN_17 = 17U, /**< 17 db */
    CY_ADCMIC_PGA_GAIN_18 = 18U, /**< 18 db */
    CY_ADCMIC_PGA_GAIN_19 = 19U, /**< 19 db */
    CY_ADCMIC_PGA_GAIN_20 = 20U, /**< 20 db */
    CY_ADCMIC_PGA_GAIN_21 = 21U, /**< 21 db */
    CY_ADCMIC_PGA_GAIN_22 = 22U, /**< 22 db */
    CY_ADCMIC_PGA_GAIN_23 = 23U, /**< 23 db */
    CY_ADCMIC_PGA_GAIN_24 = 24U, /**< 24 db */
    CY_ADCMIC_PGA_GAIN_25 = 25U, /**< 25 db */
    CY_ADCMIC_PGA_GAIN_26 = 26U, /**< 26 db */
    CY_ADCMIC_PGA_GAIN_27 = 27U, /**< 27 db */
    CY_ADCMIC_PGA_GAIN_28 = 28U, /**< 28 db */
    CY_ADCMIC_PGA_GAIN_29 = 29U, /**< 29 db */
    CY_ADCMIC_PGA_GAIN_30 = 30U, /**< 30 db */
    CY_ADCMIC_PGA_GAIN_31 = 31U, /**< 31 db */
    CY_ADCMIC_PGA_GAIN_32 = 32U, /**< 32 db */
    CY_ADCMIC_PGA_GAIN_33 = 33U, /**< 33 db */
    CY_ADCMIC_PGA_GAIN_34 = 34U, /**< 34 db */
    CY_ADCMIC_PGA_GAIN_35 = 35U, /**< 35 db */
    CY_ADCMIC_PGA_GAIN_36 = 36U, /**< 36 db */
    CY_ADCMIC_PGA_GAIN_37 = 37U, /**< 37 db */
    CY_ADCMIC_PGA_GAIN_38 = 38U, /**< 38 db */
    CY_ADCMIC_PGA_GAIN_39 = 39U, /**< 39 db */
    CY_ADCMIC_PGA_GAIN_40 = 40U, /**< 40 db */
    CY_ADCMIC_PGA_GAIN_41 = 41U, /**< 41 db */
    CY_ADCMIC_PGA_GAIN_42 = 42U  /**< 42 db */
} cy_en_adcmic_pga_gain_t;

/** The operation mode */
typedef enum
{
    CY_ADCMIC_DC  = 1U, /**< DC voltage measurement */
    CY_ADCMIC_MIC = 3U, /**< Analog microphone with PGA */
    CY_ADCMIC_PDM = 4U  /**< PDM digital microphone */
} cy_en_adcmic_mode_t;

/** The sample rate for MIC and PDM modes */
typedef enum
{
    CY_ADCMIC_8KSPS,  /**< 8 ksps, for microphone only */
    CY_ADCMIC_16KSPS  /**< 16 ksps, for microphone only */
} cy_en_adcmic_sample_rate_t;

/** The DC channel
 * \note Some options may be unavailable on particular devices.
 */
typedef enum
{
    CY_ADCMIC_REFGND = 0x0FU, /**< ADC reference ground */
    CY_ADCMIC_BGREF  = 0x0EU, /**< ADC BG REF */
    CY_ADCMIC_VDDC   = 0x0DU, /**< Core supply */
    CY_ADCMIC_VDDIO  = 0x0CU, /**< Battery/IO supply */
    CY_ADCMIC_GPIO7  = 0x17U, /**< GPIO 7  */
    CY_ADCMIC_GPIO6  = 0x16U, /**< GPIO 6  */
    CY_ADCMIC_GPIO5  = 0x15U, /**< GPIO 5  */
    CY_ADCMIC_GPIO4  = 0x14U, /**< GPIO 4  */
    CY_ADCMIC_GPIO3  = 0x13U, /**< GPIO 3  */
    CY_ADCMIC_GPIO2  = 0x12U, /**< GPIO 2  */
    CY_ADCMIC_GPIO1  = 0x11U, /**< GPIO 1  */
    CY_ADCMIC_GPIO0  = 0x10U  /**< GPIO 0  */
} cy_en_adcmic_dc_channel_t;

/** Definitions for the return mode used in \ref Cy_ADCMic_IsEndConversion */
typedef enum
{
    CY_ADCMIC_RETURN_STATUS      = 0U,    /**< Immediately returns the conversion status. */
    CY_ADCMIC_WAIT_FOR_RESULT    = 1U     /**< Does not return a result until the conversion is complete. This mode is blocking. */
} cy_en_adcmic_return_mode_t;


/** Definitions for the microphone bias settings */
typedef enum
{
    CY_ADCMIC_BIAS_1_12_REF      = 0U,    /**< 1.12 X Reference Voltage */
    CY_ADCMIC_BIAS_1_14_REF      = 1U,    /**< 1.14 X Reference Voltage */
    CY_ADCMIC_BIAS_1_17_REF      = 2U,    /**< 1.12 X Reference Voltage */
    CY_ADCMIC_BIAS_1_10_REF      = 3U     /**< 1.10 X Reference Voltage */
} cy_en_adcmic_bias_t;

/** Definitions for the PGA input common mode settings */
typedef enum
{
    CY_ADCMIC_INCM_0_4           = 0U,    /**< 0.4 X aVdd */
    CY_ADCMIC_INCM_0_45          = 1U,    /**< 0.45 X aVdd */
    CY_ADCMIC_INCM_0_35          = 2U     /**< 0.35 X aVdd */
} cy_en_adcmic_pga_incm_t;

/** Definitions for the PGA input common mode settings */
typedef enum
{
    CY_ADCMIC_OUTCM_0_6          = 0U,    /**< 0.6 */
    CY_ADCMIC_OUTCM_0_7          = 1U,    /**< 0.7 */
    CY_ADCMIC_OUTCM_0_5          = 2U     /**< 0.5 */
} cy_en_adcmic_pga_outcm_t;


/** Definitions for the DC input range settings */
typedef enum
{
    CY_ADCMIC_DC_RANGE_3_6V      = 0U,    /**< DC range 0..3.6V */
    CY_ADCMIC_DC_RANGE_1_8V      = 1U     /**< DC range 0..1.8V */
} cy_en_adcmic_dc_range_t;

/** Definitions for the timer count input settings */
typedef enum
{
    CY_ADCMIC_TIMER_COUNT_INPUT_CIC_UPDATE = 0U, /**< Counts when CIC is updated */
    CY_ADCMIC_TIMER_COUNT_INPUT_CLK_SYS    = 1U  /**< Counts up every clk_sys cycle */
} cy_en_adcmic_timer_count_input_t;

/** \} group_adcmic_enums */

/** \addtogroup group_adcmic_data_structures
* \{
*/

/** The biquad filter configuration structure */
typedef struct
{
    uint16_t bq0_num1_coeff; /**< The numerator 1 for biquad filter stage 0 */
    uint16_t bq0_num2_coeff; /**< The numerator 2 for biquad filter stage 0 */
    uint16_t bq0_num3_coeff; /**< The numerator 3 for biquad filter stage 0 */
    uint16_t bq0_den2_coeff; /**< The denominator 2 for biquad filter stage 0 */
    uint16_t bq0_den3_coeff; /**< The denominator 3 for biquad filter stage 0 */
    uint16_t bq1_num1_coeff; /**< The numerator 1 for biquad filter stage 1 */
    uint16_t bq1_num2_coeff; /**< The numerator 2 for biquad filter stage 1 */
    uint16_t bq1_num3_coeff; /**< The numerator 3 for biquad filter stage 1 */
    uint16_t bq1_den2_coeff; /**< The denominator 2 for biquad filter stage 1 */
    uint16_t bq1_den3_coeff; /**< The denominator 3 for biquad filter stage 1 */
    uint16_t bq2_num1_coeff; /**< The numerator 1 for biquad filter stage 2 */
    uint16_t bq2_num2_coeff; /**< The numerator 2 for biquad filter stage 2 */
    uint16_t bq2_num3_coeff; /**< The numerator 3 for biquad filter stage 2 */
    uint16_t bq2_den2_coeff; /**< The denominator 2 for biquad filter stage 2 */
    uint16_t bq2_den3_coeff; /**< The denominator 3 for biquad filter stage 2 */
    uint16_t bq3_num1_coeff; /**< The numerator 1 for biquad filter stage 3 */
    uint16_t bq3_num2_coeff; /**< The numerator 2 for biquad filter stage 3 */
    uint16_t bq3_num3_coeff; /**< The numerator 3 for biquad filter stage 3 */
    uint16_t bq3_den2_coeff; /**< The denominator 2 for biquad filter stage 3 */
    uint16_t bq3_den3_coeff; /**< The denominator 3 for biquad filter stage 3 */
    uint16_t bq4_num1_coeff; /**< The numerator 1 for biquad filter stage 4 */
    uint16_t bq4_num2_coeff; /**< The numerator 2 for biquad filter stage 4 */
    uint16_t bq4_num3_coeff; /**< The numerator 3 for biquad filter stage 4 */
    uint16_t bq4_den2_coeff; /**< The denominator 2 for biquad filter stage 4 */
    uint16_t bq4_den3_coeff; /**< The denominator 3 for biquad filter stage 4 */
} cy_stc_adcmic_biquad_config_t;

/** The analog microphone configuration structure */
typedef struct
{
    cy_en_adcmic_sample_rate_t        sampleRate; /**< Sample rate */
    cy_en_adcmic_bias_t                  micBias; /**< MIC bias selection */
    bool                               micBiasLz; /**< MIC bias output impedance during power down: false - hight Z, true - low Z */
    bool                                micClamp; /**< Enable MIC PGA clamping */
    cy_en_adcmic_pga_gain_t              pgaGain; /**< PGA gain 0...42 dB */
    cy_en_adcmic_pga_incm_t              pgaInCm; /**< PGA input common mode voltage selection */
    cy_en_adcmic_pga_outcm_t            pgaOutCm; /**< PGA output common mode voltage selection */
    cy_stc_adcmic_biquad_config_t * biQuadConfig; /**< The pointer to the biquad filter configuration structure */
    bool                             fifoTrigger; /**< Trigger out on valid FIFO data */
    uint8_t                             fifoFull; /**< Count for FIFO full condition */
    uint8_t                            fifoEmpty; /**< Count for FIFO empty condition */
} cy_stc_adcmic_mic_config_t;

/** The PDM path configuration structure */
typedef struct
{
    cy_en_adcmic_sample_rate_t        sampleRate; /**< Sample rate */
    bool                                clockInv; /**< Inverts the clock */
    uint8_t                           latchDelay; /**< the PDM data latch delay,
                                                   *   when clockInv is false, the valid range is 1...8
                                                   *   when clockInv is true, the valid range is 2...9
                                                   */
    cy_stc_adcmic_biquad_config_t * biQuadConfig; /**< The pointer to the biquad filter configuration structure */
    bool                             fifoTrigger; /**< Trigger out on valid FIFO data */
    uint8_t                             fifoFull; /**< Count for FIFO full condition */
    uint8_t                            fifoEmpty; /**< Count for FIFO empty condition */
} cy_stc_adcmic_pdm_config_t;

/** The ADCMic driver context structure - it stores the gain and offset values for DC voltage measurement. */
typedef struct
{
    int16_t offset; /**< The storage for the offset calibration value */
    int16_t gain;   /**< The storage for the gain calibration value */
} cy_stc_adcmic_context_t;

/** The DC measurement path configuration structure */
typedef struct
{
    cy_en_adcmic_dc_range_t               range; /**< Selects the DC measurement range */
    cy_en_adcmic_dc_channel_t           channel; /**< DC channel to be measured */
    uint16_t                        timerPeriod; /**< Timer period */
    cy_en_adcmic_timer_count_input_t timerInput; /**< Timer count input */
    cy_stc_adcmic_context_t           * context; /**< The pointer to the context structure.
                                                  *   If none of the \ref Cy_ADCMic_CountsTo_uVolts,
                                                  *                  \ref Cy_ADCMic_CountsTo_mVolts,
                                                  *              nor \ref Cy_ADCMic_CountsTo_Volts
                                                  *   functions is used, this pointer can be NULL.
                                                  */
} cy_stc_adcmic_dc_config_t;

/** The ADCMic driver configuration structure. */
typedef struct
{
    cy_stc_adcmic_mic_config_t * micConfig; /**< The pointer to the audio analog path configuration structure */
    cy_stc_adcmic_pdm_config_t * pdmConfig; /**< The pointer to the audio digital path configuration structure */
    cy_stc_adcmic_dc_config_t  * dcConfig;  /**< The pointer to the DC measurement path configuration structure */
} cy_stc_adcmic_config_t;

/** \} group_adcmic_data_structures */

/** \addtogroup group_adcmic_functions
* \{
*/

/** \addtogroup group_adcmic_functions_basic
* This set of functions is for initialization and basic usage
* \{
*/

/*******************************************************************************
* Function Name: Cy_ADCMic_Init
****************************************************************************//**
*
* Initializes the ADCMic block from a pre-initialized configuration structure.
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \param config
* The pointer to the configuration structure \ref cy_stc_adcmic_config_t.
*
* \param mode
* The ADCMic operation mode /ref cy_en_adcmic_mode_t.
*
* \return
* The status \ref cy_en_adcmic_status_t.
*
* \funcusage
* \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_MIC_OP
*
*******************************************************************************/
cy_en_adcmic_status_t Cy_ADCMic_Init(MXS40ADCMIC_Type * base, cy_stc_adcmic_config_t const * config, cy_en_adcmic_mode_t mode);


/*******************************************************************************
* Function Name: Cy_ADCMic_InitBiquad
****************************************************************************//**
*
* Initializes the biquad filter coefficients.
* Usually is called from the \ref Cy_ADCMic_Init.
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \param biQuadConfig
* The pointer to the biquad filter configuration structure \ref cy_stc_adcmic_biquad_config_t.
*
* \funcusage \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_BIQUAD_INIT
*
*******************************************************************************/
void Cy_ADCMic_InitBiquad(MXS40ADCMIC_Type * base, cy_stc_adcmic_biquad_config_t const * biQuadConfig);


/*******************************************************************************
* Function Name: Cy_ADCMic_BiquadBypass
****************************************************************************//**
*
* Bypasses/unbypasses the biquad filter.
* Usually is called from the \ref Cy_ADCMic_Init.
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \param bypass
* The boolean specifier to bypass(true) or unbypass(false) the biquad filter.
*
*******************************************************************************/
__STATIC_INLINE void Cy_ADCMic_BiquadBypass(MXS40ADCMIC_Type * base, bool bypass)
{
    CY_REG32_CLR_SET(base->AUXADC_CTRL, MXS40ADCMIC_AUXADC_CTRL_BIQUAD_BYPASS, (bypass) ? 1UL : 0UL);
}


/*******************************************************************************
* Function Name: Cy_ADCMic_Enable
****************************************************************************//**
*
* Enables the ADCMic block operation.
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \funcusage \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_MIC_OP
*
*******************************************************************************/
void Cy_ADCMic_Enable(MXS40ADCMIC_Type * base);


/*******************************************************************************
* Function Name: Cy_ADCMic_Disable
****************************************************************************//**
*
* Disables the ADCMic block operation.
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \funcusage \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_STOP
*
*******************************************************************************/
void Cy_ADCMic_Disable(MXS40ADCMIC_Type * base);


/*******************************************************************************
* Function Name: Cy_ADCMic_SetSampleRate
****************************************************************************//**
*
* Sets the specified ADC sample rate. Applicable for MIC/PDM modes only.
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \param sampleRate
* The source value \ref cy_en_adcmic_sample_rate_t.
*
* \return
* The status \ref cy_en_adcmic_status_t.
*
* \funcusage \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_MIC_OP
*
*******************************************************************************/
cy_en_adcmic_status_t Cy_ADCMic_SetSampleRate(MXS40ADCMIC_Type * base, cy_en_adcmic_sample_rate_t sampleRate);


/*******************************************************************************
* Function Name: Cy_ADCMic_ClearTrigger
****************************************************************************//**
*
* Clears the specified trigger signal.
*
* \param base
* The pointer to the hardware ADC block.
*
* \param trigMask
* The mask of triggers to clear.
* Select one or more masks from \ref group_adcmic_macros_triggers and "OR" them together:
* - \ref CY_ADCMIC_TRIG_DC
* - \ref CY_ADCMIC_TRIG_DATA
*
*******************************************************************************/
__STATIC_INLINE void Cy_ADCMic_ClearTrigger(MXS40ADCMIC_Type * base, uint32_t trigMask)
{
    base->ADCMIC_TRIGGER_CLR = trigMask & CY_ADCMIC_TRIG;
}
/** \} group_adcmic_functions_basic */

/** \addtogroup group_adcmic_functions_mic
* This set of functions is for analog microphone resources control
* \{
*/

/*******************************************************************************
* Function Name: Cy_ADCMic_SetPgaGain
****************************************************************************//**
*
* Configures the PGA gain (0dB to 42dB in steps of 1dB)
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \param gain
* The gain value \ref cy_en_adcmic_pga_gain_t.
*
* \return
* The status \ref cy_en_adcmic_status_t.
*
* \funcusage \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_GAIN
*
*******************************************************************************/
cy_en_adcmic_status_t Cy_ADCMic_SetPgaGain(MXS40ADCMIC_Type * base, cy_en_adcmic_pga_gain_t gain);

/** \} group_adcmic_functions_mic */

/** \addtogroup group_adcmic_functions_timer
* This set of functions is for Timer control
* \{
*/

/*******************************************************************************
* Function Name: Cy_ADCMic_EnableTimer
****************************************************************************//**
*
* Enables the timer.
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \funcusage \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_TIMER
*
*******************************************************************************/
__STATIC_INLINE void Cy_ADCMic_EnableTimer(MXS40ADCMIC_Type * base)
{
    base->ADCMIC_TRIG_INTRPT_TIMER_CTRL &= ~MXS40ADCMIC_ADCMIC_TRIG_INTRPT_TIMER_CTRL_TIMER_CLR_Msk;
    (void)base->ADCMIC_TRIG_INTRPT_TIMER_CTRL; /* Dummy read to ensure write is done before return */
}


/*******************************************************************************
* Function Name: Cy_ADCMic_DisableTimer
****************************************************************************//**
*
* Disables the timer.
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \funcusage \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_TIMER
*
*******************************************************************************/
__STATIC_INLINE void Cy_ADCMic_DisableTimer(MXS40ADCMIC_Type * base)
{
    base->ADCMIC_TRIG_INTRPT_TIMER_CTRL |= MXS40ADCMIC_ADCMIC_TRIG_INTRPT_TIMER_CTRL_TIMER_CLR_Msk;
    (void)base->ADCMIC_TRIG_INTRPT_TIMER_CTRL; /* Dummy read to ensure write is done before return */
}


/*******************************************************************************
* Function Name: Cy_ADCMic_SetTimerPeriod
****************************************************************************//**
*
* Sets the timer period.
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \param period
* The 16-bit timer period.
*
* \funcusage \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_TIMER
*
*******************************************************************************/
__STATIC_INLINE void Cy_ADCMic_SetTimerPeriod(MXS40ADCMIC_Type * base, uint16_t period)
{
    CY_REG32_CLR_SET(base->ADCMIC_TRIG_INTRPT_TIMER_CTRL, MXS40ADCMIC_ADCMIC_TRIG_INTRPT_TIMER_CTRL_TIMER_LIMIT, period);
}
/** \} group_adcmic_functions_timer */

/** \addtogroup group_adcmic_functions_dc
* This set of functions is for DC measurement mode
* \{
*/

/*******************************************************************************
* Function Name: Cy_ADCMic_SelectDcChannel
****************************************************************************//**
*
* Sets the specified DC measurement channel.
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \param channel
* The DC measurement channel \ref cy_en_adcmic_dc_channel_t.
*
* \note This function is useful for DC measurement only.
*
* \funcusage \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_DC_OP
*
*******************************************************************************/
void Cy_ADCMic_SelectDcChannel(MXS40ADCMIC_Type * base, cy_en_adcmic_dc_channel_t channel);


/*******************************************************************************
* Function Name: Cy_ADCMic_IsEndConversion
****************************************************************************//**
*
* Immediately return the status of the conversion or does not return (blocking)
* until the conversion completes, depending on the retMode parameter.
* In blocking mode, there is a time out of about 10 seconds for a CPU speed of
* 100 MHz.
*
* \param base
* Pointer to structure describing registers
*
* \param retMode
* A value of the enum \ref cy_en_adcmic_return_mode_t
*
* \return
* - \ref CY_ADCMIC_SUCCESS : the last conversion is complete
* - \ref CY_ADCMIC_CONVERSION_NOT_COMPLETE : the conversion has not completed
* - \ref CY_ADCMIC_TIMEOUT : the watchdog timer has expired in blocking mode
*
* \sideeffect
* This function reads the end of conversion status interrupt bit and clears it after.
*
* \note
* \ref CY_ADCMIC_WAIT_FOR_RESULT return modes are not recommended
* for use in RTOS environment.
*
* \funcusage \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_DC_OP
*
*******************************************************************************/
cy_en_adcmic_status_t Cy_ADCMic_IsEndConversion (MXS40ADCMIC_Type * base, cy_en_adcmic_return_mode_t retMode);


/*******************************************************************************
* Function Name: Cy_ADCMic_GetDcResult
****************************************************************************//**
*
* Returns the DC conversion result from the CIC status register.
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \return
* The signed DC conversion result.
*
* \funcusage \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_DC_OP
*
*******************************************************************************/
__STATIC_INLINE int16_t Cy_ADCMic_GetDcResult(MXS40ADCMIC_Type * base)
{
    return ((int16_t)((uint16_t)_FLD2VAL(MXS40ADCMIC_AUXADC_CIC_STATUS_CIC, base->AUXADC_CIC_STATUS)));
}


/*******************************************************************************
* Function Name: Cy_ADCMic_SetDcOffset
****************************************************************************//**
*
* Sets the offset value for DC measurement calibration.
*
* \param offset
* The offset value.
*
* \param context
* The pointer to the context structure \ref cy_stc_adcmic_context_t.
*
*******************************************************************************/
void Cy_ADCMic_SetDcOffset(int16_t offset, cy_stc_adcmic_context_t * context);


/*******************************************************************************
* Function Name: Cy_ADCMic_SetDcGain
****************************************************************************//**
*
* Sets the gain value for DC measurement calibration.
*
* \param gain
* The gain value.
*
* \param context
* The pointer to the context structure \ref cy_stc_adcmic_context_t.
*
*******************************************************************************/
void Cy_ADCMic_SetDcGain(int16_t gain, cy_stc_adcmic_context_t * context);


/*******************************************************************************
* Function Name: Cy_ADCMic_CountsTo_mVolts
****************************************************************************//**
*
* Convert the ADC output to millivolts as an int16. For example, if the ADC
* measured 0.534 volts, the return value would be 534.
* The calculation of voltage depends on the DC range.
* The equation used is:
*
*     mV = (RawCounts - Offset) * 1000 / Gain
*
* where,
* - RawCounts: Raw counts returned by the \ref Cy_ADCMic_GetDcResult.
* - Offset - the offset value, can be adjusted by the \ref Cy_ADCMic_SetDcOffset,
*   essentially it is a raw count value of the \ref CY_ADCMIC_REFGND voltage measurement.
* - 1000 - amount of millivolts in 1 volt
* - Gain: the gain value, can be adjusted by the \ref Cy_ADCMic_SetDcGain, depends on DC range,
*   essentially it is an amount of raw counts per 1 volt of input voltage.
*
* \note
* This function is for DC measurement only.
*
* \param adcCounts
* Conversion result from \ref Cy_ADCMic_GetDcResult
*
* \param context
* The pointer to the context structure \ref cy_stc_adcmic_context_t.
*
* \return
* Result in millivolts.
*
* \funcusage \snippet adcmic_snippet/snippet.c SNIPPET_ADCMIC_DC_MEASURE
*
*******************************************************************************/
int16_t Cy_ADCMic_CountsTo_mVolts(int16_t adcCounts, cy_stc_adcmic_context_t const * context);


/*******************************************************************************
* Function Name: Cy_ADCMic_CountsTo_uVolts
****************************************************************************//**
*
* Convert the ADC output to microvolts as an int32. For example, if the ADC
* measured 0.534 volts, the return value would be 534000.
* The calculation of voltage depends on the DC range.
* The equation used is:
*
*     uV = (RawCounts - Offset) * 1000000 / Gain
*
* where,
* - RawCounts: Raw counts returned by the \ref Cy_ADCMic_GetDcResult.
* - Offset - the offset value, can be adjusted by the \ref Cy_ADCMic_SetDcOffset,
*   essentially it is a raw count value of the \ref CY_ADCMIC_REFGND voltage measurement.
* - 1000000 - amount of microvolts in 1 volt
* - Gain: the gain value, can be adjusted by the \ref Cy_ADCMic_SetDcGain, depends on DC range,
*   essentially it is an amount of raw counts per 1 volt of input voltage.
*
* \note
* This function is for DC measurement only.
*
* \param adcCounts
* Conversion result from \ref Cy_ADCMic_GetDcResult
*
* \param context
* The pointer to the context structure \ref cy_stc_adcmic_context_t.
*
* \return
* Result in microvolts.
*
* \funcusage \snippet adcmic_snippet/snippet.c SNIPPET_ADCMIC_DC_MEASURE
*
*******************************************************************************/
int32_t Cy_ADCMic_CountsTo_uVolts(int16_t adcCounts, cy_stc_adcmic_context_t const * context);


/*******************************************************************************
* Function Name: Cy_ADCMic_CountsTo_Volts
****************************************************************************//**
*
* Convert the ADC output to volts as a float. For example, if the ADC
* measured 0.534 volts, the return value would be 0.534.
* The calculation of voltage depends on the DC range.
* The equation used is:
*
*     V = (RawCounts - Offset) / Gain
*
* where,
* - RawCounts: Raw counts returned by the \ref Cy_ADCMic_GetDcResult.
* - Offset - the offset value, can be adjusted by the \ref Cy_ADCMic_SetDcOffset,
*   essentially it is a raw count value of the \ref CY_ADCMIC_REFGND voltage measurement.
* - Gain: the gain value, can be adjusted by the \ref Cy_ADCMic_SetDcGain, depends on DC range,
*   essentially it is an amount of raw counts per 1 volt of input voltage.
*
* \note
* This function is for DC measurement only.
*
* \param adcCounts
* Conversion result from \ref Cy_ADCMic_GetDcResult
*
* \param context
* The pointer to the context structure \ref cy_stc_adcmic_context_t.
*
* \return
* Result in volts.
*
* \funcusage \snippet adcmic_snippet/snippet.c SNIPPET_ADCMIC_DC_MEASURE
*
*******************************************************************************/
float Cy_ADCMic_CountsTo_Volts(int16_t adcCounts, cy_stc_adcmic_context_t const * context);
/** \} group_adcmic_functions_dc */

/** \addtogroup group_adcmic_functions_interrupt
* This set of functions are related to ADCMic interrupts.
* \{
*/

/*******************************************************************************
* Function Name: Cy_ADCMic_EnableInterrupt
****************************************************************************//**
*
* Sets the specified interrupt bit in the interrupt mask register.
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \param intrMask
* The mask of interrupts to enable.
* Select one or more values from \ref group_adcmic_macros_interrupt and "OR" them together.
* - \ref CY_ADCMIC_INTR_DC
* - \ref CY_ADCMIC_INTR_DATA
*
* \funcusage \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_CONFIG_INTR
*
*******************************************************************************/
void Cy_ADCMic_EnableInterrupt(MXS40ADCMIC_Type * base, uint32_t intrMask);


/*******************************************************************************
* Function Name: Cy_ADCMic_DisableInterrupt
****************************************************************************//**
*
* Clears the specified interrupt bit in the interrupt mask register.
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \param intrMask
* The mask of interrupts to disable.
* Select one or more values from \ref group_adcmic_macros_interrupt and "OR" them together.
* - \ref CY_ADCMIC_INTR_DC
* - \ref CY_ADCMIC_INTR_DATA
*
* \funcusage \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_CONFIG_INTR
*
*******************************************************************************/
void Cy_ADCMic_DisableInterrupt(MXS40ADCMIC_Type * base, uint32_t intrMask);


/*******************************************************************************
* Function Name: CY_ADCMIC_GetInterruptStatus
****************************************************************************//**
*
* Returns the interrupt status of the specified channel.
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \return
* The interrupt status.
*
* \funcusage \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_CONFIG_INTR
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_ADCMic_GetInterruptStatus(MXS40ADCMIC_Type const * base)
{
    return (base->ADCMIC_INTR & CY_ADCMIC_INTR);
}


/*******************************************************************************
* Function Name: Cy_ADCMic_ClearInterrupt
****************************************************************************//**
*
* Clears the interrupt status.
*
* \param base
* The pointer to the hardware ADC block.
*
* \param intrMask
* The mask of interrupts to clear. Typically this will be the value returned
* from \ref Cy_ADCMic_GetInterruptStatus.
* Alternately, select one or more values from \ref group_adcmic_macros_interrupt and "OR" them together.
* - \ref CY_ADCMIC_INTR_DC
* - \ref CY_ADCMIC_INTR_DATA
*
* \funcusage \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_CONFIG_INTR
*
*******************************************************************************/
__STATIC_INLINE void Cy_ADCMic_ClearInterrupt(MXS40ADCMIC_Type * base, uint32_t intrMask)
{
    base->ADCMIC_INTR = intrMask & CY_ADCMIC_INTR;
    (void) base->ADCMIC_INTR;
}


/*******************************************************************************
* Function Name: Cy_ADCMic_SetInterrupt
****************************************************************************//**
*
* Sets the interrupt for the specified channel.
* Intended mostly for debugging.
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \param intrMask
* The mask of interrupts to set.
* Select one or more values from \ref group_adcmic_macros_interrupt and "OR" them together.
* - \ref CY_ADCMIC_INTR_DC
* - \ref CY_ADCMIC_INTR_DATA
*
*******************************************************************************/
__STATIC_INLINE void Cy_ADCMic_SetInterrupt(MXS40ADCMIC_Type * base, uint32_t intrMask)
{
    base->ADCMIC_INTR_SET = intrMask & CY_ADCMIC_INTR;
}


/*******************************************************************************
* Function Name: CY_ADCMIC_GetInterruptMask
****************************************************************************//**
*
* Returns the interrupt mask value of the specified channel.
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \return
* The interrupt mask value.
*
* \funcusage \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_GET_INTERRUPT_MASK
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_ADCMic_GetInterruptMask(MXS40ADCMIC_Type const * base)
{
    return (base->ADCMIC_INTR_MASK & CY_ADCMIC_INTR);
}


/*******************************************************************************
* Function Name: CY_ADCMIC_SetInterruptMask
****************************************************************************//**
*
* Sets an interrupt mask value for the specified channel.
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \param intrMask
* The mask of interrupts.
* Select one or more values from \ref group_adcmic_macros_interrupt and "OR" them together.
* - \ref CY_ADCMIC_INTR_DC
* - \ref CY_ADCMIC_INTR_DATA
*
* \funcusage \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_SET_INTERRUPT_MASK
*
*******************************************************************************/
__STATIC_INLINE void Cy_ADCMic_SetInterruptMask(MXS40ADCMIC_Type * base, uint32_t intrMask)
{
    base->ADCMIC_INTR_MASK = intrMask & CY_ADCMIC_INTR;
}


/*******************************************************************************
* Function Name: CY_ADCMIC_GetInterruptStatusMasked
****************************************************************************//**
*
* Returns the logical AND of the corresponding INTR and INTR_MASK fields
* in a single-load operation.
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \return
* The masked interrupt status.
*
* \funcusage \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_CONFIG_INTR
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_ADCMic_GetInterruptStatusMasked(MXS40ADCMIC_Type const * base)
{
    return (base->ADCMIC_INTR_MASKED & CY_ADCMIC_INTR);
}
/** \} group_adcmic_functions_interrupt */

/** \addtogroup group_adcmic_functions_fifo
* This set of functions are related to ADCMic FIFO buffer.
* \{
*/

/*******************************************************************************
* Function Name: Cy_ADCMic_ReadFifoAll
****************************************************************************//**
*
* Reads whole the FIFO payload into the data array.
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \param data
* The pointer to the uint16_t data array for the FIFO payload.
*
* \return
* The 8-bit FIFO data count.
*
* \funcusage \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_ISR
*
*******************************************************************************/
uint8_t Cy_ADCMic_ReadFifoAll(MXS40ADCMIC_Type const * base, uint16_t * data);


/*******************************************************************************
* Function Name: Cy_ADCMic_ReadFifoStatus
****************************************************************************//**
*
* Returns the fifo status.
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \return
* The 8-bit fifo status, see \ref group_adcmic_macros_fifo_status.
*
* \funcusage \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_ADCMIC_ISR
*
*******************************************************************************/
__STATIC_INLINE uint8_t Cy_ADCMic_GetFifoStatus(MXS40ADCMIC_Type const * base)
{
    return ((uint8_t)_FLD2VAL(MXS40ADCMIC_ADCMIC_FIFO_CTRL_FIFO_STATUS, base->ADCMIC_FIFO_CTRL));
}


/*******************************************************************************
* Function Name: Cy_ADCMic_ReadFifo
****************************************************************************//**
*
* Low-level API which returns the ADCMIC_DATA register value
* that contains \b two subsequent FIFO data samples.
*
* \param base
* The pointer to the hardware ADCMic block.
*
* \return
* The combined 32-bit value of two 16-bit samples.
* Use \ref group_adcmic_macros_fifo_samples to parse it.
*
* \funcusage \snippet adcmic/snippet/adcmic_snippet.c SNIPPET_READ_FIFO
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_ADCMic_ReadFifo(MXS40ADCMIC_Type const * base)
{
    return (base->ADCMIC_DATA);
}

/** \} group_adcmic_functions_fifo */

/** \} group_adcmic_functions */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXS40ADCMIC */

#endif  /* (CY_ADCMIC_H) */

/** \} group_adcmic */

/* [] END OF FILE */
