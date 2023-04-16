/***************************************************************************//**
* \file cy_pdm_pcm_v2.h
* \version 1.10
*
* The header file of the PDM_PCM driver.
*
********************************************************************************
* \copyright
* Copyright 2019-2022 Cypress Semiconductor Corporation
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
* \addtogroup group_pdm_pcm_v2
* \{
* \note IP Supported: PDM
* \note Device Categories: CAT1B. Please refer <a href="usergroup1.html">Device Catalog</a>.
*
* The pulse-density modulation to pulse-code modulation (PDM-PCM) driver provides an
* API to manage PDM-PCM conversion. A PDM-PCM converter is used
* to convert 1-bit digital audio streaming data to PCM data.
*
* The functions and other declarations used in this driver are in cy_pdm_pcm_v2.h.
* You can include cy_pdl.h (ModusToolbox only) to get access to all functions
* and declarations in the PDL.
*
* Features:
*        - Supports up to 8 PDM receivers
*        - Supports Stereo/Mono dual mode PDM (pulse-density-modulated) to PCM (pulse-code-modulated) conversion
*        - Half rate sampling to reduce system power consumption
*        - CIC filter, FIR filter, DC block filter signal processing path
*        - Programmable interface clock
*        - Programmable FIR filter coefficients
*        - Programmable CIC and FIR filter decimation
*        - Programmable DC blocking coefficient
*        - Programmable PCM word size (8, 10, 12, 14, 16, 18, 20, 24, 32 bits)
*        - Programmable sampling delay, to cope with different master-slavemaster roundtrip delays
*        - 64 entry RX FIFO with interrupt and trigger support
*        - Debug/freeze trigger support
*        - Receiver activate trigger support
*        - Test mode support, the IP includes a programmable PDM pattern    generator
*
* Pulse-density modulation, or PDM, represents
* an analog signal with a binary signal. In a PDM signal, specific amplitude values
* are not encoded into codewords of pulses of different weight as they would be
* in pulse-code modulation (PCM); rather, the relative density of the pulses corresponds
* to the analog signal's amplitude. The output of a 1-bit DAC is the same
* as the PDM encoding of the signal.
*
* Pulse-code modulation (PCM) is the method used to digitally represent sampled analog signals.
* It is the standard form of digital audio in computers, compact discs, digital telephony,
* and other digital audio applications. In a PCM stream, the amplitude of the analog signal
* is sampled regularly at uniform intervals, and each sample is quantized
* to the nearest value within a range of digital steps.
*
* \section group_pdm_pcm_configuration_considerations_v2 Configuration Considerations
*
* To set up a PDM-PCM, provide the configuration parameters in the
* \ref cy_stc_pdm_pcm_config_v2_t structure.
*
* For example, set dataStreamingEnable to true, configure rxFifoTriggerLevel,
* dmaTriggerEnable (depending on whether DMA is going to be used),
* provide clock settings (clkDiv, mclkDiv and ckoDiv), set sincDecRate
* to the appropriate decimation rate, wordLen, and wordBitExtension.
* No other parameters are necessary for this example.
*
* To initialize the PDM-PCM channels, call \ref Cy_PDM_PCM_Channel_Init function, providing the
* filled \ref cy_stc_pdm_pcm_channel_config_t structure
* To initialize the PDM-PCM block, call the \ref Cy_PDM_PCM_Init function, providing the
* filled \ref cy_stc_pdm_pcm_config_v2_t structure.
*
* If you use a DMA, the DMA channel should be previously configured. PDM-PCM interrupts
* (if applicable) can be enabled by calling \ref Cy_PDM_PCM_SetInterruptMask.
*
* For example, if the trigger interrupt is used during operation, the ISR
* should call the \ref Cy_PDM_PCM_ReadFifo as many times as required for your
* FIFO payload. Then call \ref Cy_PDM_PCM_Channel_ClearInterrupt with appropriate parameters.
*
* If a DMA is used and the DMA channel is properly configured, no CPU activity
* (or application code) is needed for PDM-PCM operation.
*
* \section group_pdm_pcm_changelog_v2 Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.10</td>
*     <td>Minor documentation updates.</td>
*     <td>Documentation enhancement.</td>
*     <td></td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_pdm_pcm_macros_v2 Macros
* \defgroup group_pdm_pcm_functions_v2 Functions
* \defgroup group_pdm_pcm_data_structures_v2 Data Structures
* \defgroup group_pdm_pcm_enums_v2 Enumerated Types
*
*/

#if !defined (CY_PDM_PCM_V2_H__)
#define CY_PDM_PCM_V2_H__

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

#include "cy_device.h"

#if defined (CY_IP_MXPDM)

#include "cy_syslib.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Global definitions
 ******************************************************************************/

/* Macros */
/**
* \addtogroup group_pdm_pcm_macros_v2
* \{
*/

/** The driver major version */
#define CY_PDM_PCM_V2_DRV_VERSION_MAJOR       1

/** The driver minor version */
#define CY_PDM_PCM_V2_DRV_VERSION_MINOR       1

/** The PDM-PCM driver identifier */
#define CY_PDM_PCM_V2_ID                       CY_PDL_DRV_ID(0x73u)

/**
* \defgroup group_pdm_pcm_macros_interrupt_masks_v2 Interrupt Masks
* \{
*/

/** More entries in the RX FIFO than specified by Trigger Level*/
#define CY_PDM_PCM_INTR_RX_TRIGGER         (PDM_CH_INTR_RX_FIFO_TRIGGER_Msk)
/** Attempt to write to a full RX FIFO*/
#define CY_PDM_PCM_INTR_RX_OVERFLOW       (PDM_CH_INTR_RX_FIFO_OVERFLOW_Msk)
/** Attempt to read from an empty RX FIFO*/
#define CY_PDM_PCM_INTR_RX_UNDERFLOW        (PDM_CH_INTR_RX_FIFO_UNDERFLOW_Msk)
/** CIC filter PCM samples are produced at a faster rate than the FIR filter can process them*/
#define CY_PDM_PCM_INTR_RX_FIR_OVERFLOW       (PDM_CH_INTR_RX_FIR_OVERFLOW_Msk)
/** when PDM samples are generated too fast*/
#define CY_PDM_PCM_INTR_RX_IF_OVERFLOW       (PDM_CH_INTR_RX_IF_OVERFLOW_Msk)

/** \} group_pdm_pcm_macros_interrupt_masks_v2 */

/** \} group_pdm_pcm_macros_v2 */

/**
* \addtogroup group_pdm_pcm_enums_v2
* \{
*/

/** PDM Word Length*/
typedef enum
{
    CY_PDM_PCM_WSIZE_8_BIT      = 0U,         /**< Word length: 8 bit*/
    CY_PDM_PCM_WSIZE_10_BIT     = 1U,         /**< Word length: 10 bit*/
    CY_PDM_PCM_WSIZE_12_BIT     = 2U,         /**< Word length: 12 bit*/
    CY_PDM_PCM_WSIZE_14_BIT     = 3U,         /**< Word length: 14 bit*/
    CY_PDM_PCM_WSIZE_16_BIT     = 4U,         /**< Word length: 16 bit*/
    CY_PDM_PCM_WSIZE_18_BIT     = 5U,         /**< Word length: 18 bit*/
    CY_PDM_PCM_WSIZE_20_BIT     = 6U,         /**< Word length: 20 bit*/
    CY_PDM_PCM_WSIZE_24_BIT     = 7U,         /**< Word length: 24 bit*/
    CY_PDM_PCM_WSIZE_32_BIT     = 8U          /**< Word length: 32 bit*/
} cy_en_pdm_pcm_word_size_t;

/** cy_en_pdm_pcm_clock_sel_t*/
typedef enum
{
    CY_PDM_PCM_SEL_SRSS_CLOCK   = 0U,         /**< Interface clock is selected as clk_if_srss[0]*/
    CY_PDM_PCM_SEL_PDM_DATA0    = 1U,         /**< Interface clock is selected as pdm_data[0]*/
    CY_PDM_PCM_SEL_PDM_DATA1    = 2U,         /**< Interface clock is selected as pdm_data[1]*/
    CY_PDM_PCM_SEL_OFF          = 3U          /**< Interface clock clk_if is off*/
} cy_en_pdm_pcm_clock_sel_t;

/** PDM Halve Rate Sampling*/
typedef enum
{
    CY_PDM_PCM_RATE_FULL       = 0U,         /**< Channel full*/
    CY_PDM_PCM_RATE_HALVE      = 1U          /**< Channel halve*/
} cy_en_pdm_pcm_halve_rate_sel_t;

/** CIC DECIMATION CODE*/
typedef enum
{
    CY_PDM_PCM_CHAN_CIC_DECIM_2   = 0U,         /**< CIC Filter PCM Frequency is 1/2 * PDM Frequency*/
    CY_PDM_PCM_CHAN_CIC_DECIM_4   = 1U,         /**< CIC Filter PCM Frequency is 1/4 * PDM Frequency*/
    CY_PDM_PCM_CHAN_CIC_DECIM_8   = 2U,         /**< CIC Filter PCM Frequency is 1/8 * PDM Frequency*/
    CY_PDM_PCM_CHAN_CIC_DECIM_16  = 3U,         /**< CIC Filter PCM Frequency is 1/16 * PDM Frequency*/
    CY_PDM_PCM_CHAN_CIC_DECIM_32  = 4U          /**< CIC Filter PCM Frequency is 1/32 * PDM Frequency*/
} cy_en_pdm_pcm_ch_cic_decimcode_t;

/** FIR0 DECIMATION CODE*/
typedef enum
{
    CY_PDM_PCM_CHAN_FIR0_DECIM_1  = 0U,         /**< FIR0 Filter PCM Frequency is 1/1 * PCM Frequency*/
    CY_PDM_PCM_CHAN_FIR0_DECIM_2  = 1U,         /**< FIR0 Filter PCM Frequency is 1/2 * PCM Frequency*/
    CY_PDM_PCM_CHAN_FIR0_DECIM_3  = 2U,         /**< FIR0 Filter PCM Frequency is 1/3 * PCM Frequency*/
    CY_PDM_PCM_CHAN_FIR0_DECIM_4  = 3U,         /**< FIR0 Filter PCM Frequency is 1/4 * PCM Frequency*/
    CY_PDM_PCM_CHAN_FIR0_DECIM_5  = 4U          /**< FIR0 Filter PCM Frequency is 1/5 * PCM Frequency*/
} cy_en_pdm_pcm_ch_fir0_decimcode_t;

/** FIR1 DECIMATION CODE*/
typedef enum
{
    CY_PDM_PCM_CHAN_FIR1_DECIM_1   = 0U,         /**< FIR1 Filter PCM Frequency is 1/1 * PCM Frequency*/
    CY_PDM_PCM_CHAN_FIR1_DECIM_2   = 1U,         /**< FIR1 Filter PCM Frequency is 1/2 * PCM Frequency*/
    CY_PDM_PCM_CHAN_FIR1_DECIM_3   = 2U,         /**< FIR1 Filter PCM Frequency is 1/3 * PCM Frequency*/
    CY_PDM_PCM_CHAN_FIR1_DECIM_4   = 3U,         /**< FIR1 Filter PCM Frequency is 1/4 * PCM Frequency*/
} cy_en_pdm_pcm_ch_fir1_decimcode_t;

/** DC Block CODE*/
typedef enum
{
    CY_PDM_PCM_CHAN_DCBLOCK_CODE_1   = 0U,         /**< DCBLOCK Filter alpha = 1 - (1/2^(12-0))*/
    CY_PDM_PCM_CHAN_DCBLOCK_CODE_2   = 1U,         /**< DCBLOCK Filter alpha = 1 - (1/2^(12-1))*/
    CY_PDM_PCM_CHAN_DCBLOCK_CODE_4   = 2U,         /**< DCBLOCK Filter alpha = 1 - (1/2^(12-2))*/
    CY_PDM_PCM_CHAN_DCBLOCK_CODE_8   = 3U,         /**< DCBLOCK Filter alpha = 1 - (1/2^(12-3))*/
    CY_PDM_PCM_CHAN_DCBLOCK_CODE_16  = 4U,         /**< DCBLOCK Filter alpha = 1 - (1/2^(12-4))*/
    CY_PDM_PCM_CHAN_DCBLOCK_CODE_32  = 5U,         /**< DCBLOCK Filter alpha = 1 - (1/2^(12-5))*/
    CY_PDM_PCM_CHAN_DCBLOCK_CODE_64  = 6U,         /**< DCBLOCK Filter alpha = 1 - (1/2^(12-6))*/
    CY_PDM_PCM_CHAN_DCBLOCK_CODE_128 = 7U,         /**< DCBLOCK Filter alpha = 1 - (1/2^(12-7))*/
} cy_en_pdm_pcm_ch_dcblock_coef_t;

/** \cond INTERNAL */
/** PDM Output Mode*/
typedef enum
{
    CY_PDM_PCM_OUT_CHAN_LEFT   = 1U,         /**< Channel mono left*/
    CY_PDM_PCM_OUT_CHAN_RIGHT  = 2U,         /**< Channel mono right*/
    CY_PDM_PCM_OUT_STEREO      = 3U          /**< Channel stereo*/
} cy_en_pdm_pcm_out_t;
/** \endcond */

/** The PDM-PCM status codes*/
typedef enum
{
    CY_PDM_PCM_SUCCESS         = 0x00UL,    /**< Success status code*/
    CY_PDM_PCM_BAD_PARAM       = CY_PDM_PCM_V2_ID | CY_PDL_STATUS_ERROR |0x01UL     /**< Bad parameter status code*/
} cy_en_pdm_pcm_status_t;

/** \} group_pdm_pcm_enums_v2 */


/**
* \addtogroup group_pdm_pcm_data_structures_v2
* \{
*/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

 /** PDM-PCM Test Mode configuration */
 typedef struct
 {
     uint8_t drive_delay_hi;                /**< Interface drive delay on the high phase of the PDM interface clock.
                                             This field specifies when a PDM value is driven expressed in clk_if clock cycles.
                                             DRIVE_DELAY should be set in the range [0, IF_CTL.CLOCK_DIV]:
                                            "0": Drive PDM value 1 clk_if cycle after the rising edge of clk_pdm.
                                            "1": Drive PDM value 2 clk_if cycles after the rising edge of clk_pdm.
                                            ...
                                            "255": Drive PDM value 256 clk_if cycles after the rising edge of clk_pdm*/
     uint8_t drive_delay_lo;                /**< Interface drive delay on the low phase of the PDM interface clock.
                                             This field specifies when a PDM value is driven expressed in clk_if clock cycles.
                                             DRIVE_DELAY should be set in the range [0, IF_CTL.CLOCK_DIV]:
                                            "0": Drive PDM value 1 clk_if cycle after the rising edge of clk_pdm.
                                            "1": Drive PDM value 2 clk_if cycles after the rising edge of clk_pdm.
                                            ...
                                            "255": Drive PDM value 256 clk_if cycles after the rising edge of clk_pdm*/
     uint8_t mode_hi;                        /**< Pattern generator mode on the high phase of the PDM interface clock.
                                            This field specifies the type of pattern driven by the generator:
                                            "0": constant 0's
                                            "1": constant 1's
                                            "2": alternating 0's and 1's (clock pattern)
                                            "3": sine wave */
     uint8_t mode_lo;                        /**< Pattern generator mode on the low phase of the PDM interface clock.
                                            This field specifies the type of pattern driven by the generator:
                                            "0": constant 0's
                                            "1": constant 1's
                                            "2": alternating 0's and 1's (clock pattern)
                                            "3": sine wave */
     uint8_t audio_freq_div;                /**< Frequency division factor (legal range [3, 13]) to obtain audio frequency
                                            from the PDM clock frequency. This field determines the frequency of the sine wave
                                            generated by the pattern generator when MODE=3. The formula is below:
                                            Sine wave Frequency = PDM clock frequency / 2p*2^(AUDIO_FREQ_DIV) */
     bool    enable;            /**<  enable*/


 }cy_stc_test_config_t;

 /** PDM-PCM fir coeff_data structure */
 typedef struct
 {

    int16_t         coeff_data0;            /**<  filter taps coefficients data 0*/
    int16_t         coeff_data1;            /**<  filter taps coefficients data 1*/
 }cy_stc_pdm_pcm_fir_coeff_t;

 /** PDM-PCM Channel initialization configuration */
 typedef struct
 {
    uint8_t                               sampledelay;    /**< Interface sample delay. This field specifies when a PDM value is captured. The value that user assigns here will be incremented by 1 and assigned internally */

    cy_en_pdm_pcm_word_size_t             wordSize;       /**< see #cy_en_pdm_pcm_word_size_t */
    bool                                 signExtension;  /**< Word extension type:
                                                        - 0: extension by zero
                                                        - 1: extension by sign bits */

    uint8_t                              rxFifoTriggerLevel;  /**< Fifo interrupt trigger level (in words),
                                                        range: 0 - 63  */

    bool                                fir0_enable;    /**< FIR 0 filter coefficient enable (does NOT effect FIR filter scaling and FIR filter decimation):
                                                         - 0: Disabled
                                                         - 1: Enabled */


    cy_en_pdm_pcm_ch_cic_decimcode_t     cic_decim_code; /**< CIC filter decimation. The CIC filter PCM frequency is a fraction of the PDM frequency. \ref cy_en_pdm_pcm_ch_cic_decimcode_t */

    cy_en_pdm_pcm_ch_fir0_decimcode_t    fir0_decim_code;/**< FIR filter decimation. The FIR filter PCM frequency is a fraction of the CIC filter PCM frequency. \ref cy_en_pdm_pcm_ch_fir0_decimcode_t */

    uint8_t                                fir0_scale;        /**< FIR 0 filter PCM scaling. range 0-31 */

    cy_en_pdm_pcm_ch_fir1_decimcode_t    fir1_decim_code;/**< FIR filter decimation. The FIR filter PCM frequency is a fraction of the FIR0 filter PCM frequency. \ref cy_en_pdm_pcm_ch_fir1_decimcode_t */

    uint8_t                                fir1_scale;        /**< FIR 1 filter PCM scaling. range 0 to 31 */

    bool                                   dc_block_disable;  /**< Disables DC BLOCK if set to true. This is for debug only. To be used for test modes 0,1 and 2 in test config ie. if the input is constant 0's or constant 1's or alternating 0's and 1's*/

    cy_en_pdm_pcm_ch_dcblock_coef_t        dc_block_code;    /**< DC blocker coefficient. \ref cy_en_pdm_pcm_ch_dcblock_coef_t*/
 } cy_stc_pdm_pcm_channel_config_t;


/** PDM-PCM initialization configuration */
typedef struct
{
    uint8_t                             clkDiv;         /**< PDM Clock Divider
                                                        This configures a frequency of PDM CLK. The configured frequency
                                                        is used to operate PDM core. The value that user assigns here will be incremented by 1 and assigned internally. For example, if the clkDiv value is 0, it is internally incremented by 1.*/
    cy_en_pdm_pcm_clock_sel_t           clksel;         /**< Interface clock clk_if selection. \ref cy_en_pdm_pcm_clock_sel_t */
    cy_en_pdm_pcm_halve_rate_sel_t      halverate;      /**< Halve rate sampling. \ref cy_en_pdm_pcm_halve_rate_sel_t*/
    uint8_t                             route;          /**< Specifies what IOSS data input signal "pdm_data[]" is routed to a specific PDM receiver.
                                                        Each PDM receiver j has a dedicated     1-bit control field: PDM receiver j uses DATA_SEL[j].
                                                        The 1-bit field DATA_SEL[j] specification is as follows:
                                                        '0': PDM receiver j uses data input signal "pdm_data[j]".
                                                        '1': PDM receiver j uses data input signal "pdm_data[j ^ 1]" (the lower bit of the index is inverted)*/


    uint8_t fir0_coeff_user_value;    /**< FIR 0 filter coefficient enable. User has to configure the coeff values. 0: Disabled. 1: Enabled*/

    uint8_t fir1_coeff_user_value;    /**< FIR 1 filter coefficient enable. User has to configure the coeff values. 0: Disabled. 1: Enabled*/

    cy_stc_pdm_pcm_fir_coeff_t             fir0_coeff[8];   /**<  The (symmetric) 30-taps finite impulse response (FIR) filter with 14-bit signed coefficients
                                                            (in the range [-8192, 8191]) are specified by FIR0_COEFF0, ..., FIR0_COEFF7.
                                                            The FIR filter coefficients have no default values:
                                                            the coefficients MUST be programmed BEFORE the filter is enabled.
                                                            By Default FIR0 is disabled and is only used for 8Khz and 16 Khz sample frequencies*/

    cy_stc_pdm_pcm_fir_coeff_t             fir1_coeff[14];        /**< The (symmetric) 55-taps finite impulse response (FIR) filter
                                                            with 14-bit signed coefficients (in the range [-8192, 8191])
                                                            are specified by FIR1_COEFF0, ..., FIR1_COEFF13.
                                                            The (default) FIR filter has built in droop correction.
                                                            The filter gain (sum of the coefficients) is 13921 and the default
                                                            coefficients (as specified by FIR1_COEFFx.DATA0/1[13:0]) are:
                                                            (-2,   21), (26,  -17), (-41,   25), (68, -33),
                                                            (-107,   41), (160,  -48), (-230,   54), (325, -56),
                                                            (-453,   51), (631,  -31), (-894,  -21), (1326, 172),
                                                            (-2191, -770), (4859, 8191)*/
} cy_stc_pdm_pcm_config_v2_t;

/** \cond INTERNAL */
typedef cy_stc_pdm_pcm_config_v2_t cy_stc_pdm_pcm_config_t;
/** \endcond */

/** \} group_pdm_pcm_data_structures_v2 */


/** \cond INTERNAL */
/******************************************************************************
 * Local definitions
*******************************************************************************/
/** Define bit mask for all available interrupt sources */
#define CY_PDM_PCM_INTR_MASK        (CY_PDM_PCM_INTR_RX_TRIGGER           | \
                                     CY_PDM_PCM_INTR_RX_FIR_OVERFLOW     | \
                                     CY_PDM_PCM_INTR_RX_OVERFLOW          | \
                                     CY_PDM_PCM_INTR_RX_IF_OVERFLOW      | \
                                     CY_PDM_PCM_INTR_RX_UNDERFLOW)

/* Non-zero default values */
#define CY_PDM_PCM_CH_IF_CTL_DEFAULT    (0x3U)

#define CY_PDM_PCM_CLK_DIV_MAX 255

#define CY_PDM_PCM_CH_CIC_DECIM_CODE_DEFAULT    (0x4U)
#define CY_PDM_PCM_CH_FIR0_DECIM_CODE_DEFAULT   (0x0U)
#define CY_PDM_PCM_CH_FIR0_SCALE_DEFAULT           (0x0U)
#define CY_PDM_PCM_CH_FIR1_DECIM_CODE_DEFAULT   (0x1U)
#define CY_PDM_PCM_CH_FIR1_SCALE_DEFAULT           (0x0FU)
#define CY_PDM_PCM_CH_FIR1_ENABLE_DEFAULT       (0x1U)
#define CY_PDM_PCM_CH_DCBLOCK_CODE_DEFAULT       (0x1U)
#define CY_PDM_PCM_CH_DCBLOCK_ENABLE_DEFAULT       (0x1U)

#define PDM_TEST_CTL_DRIVE_DELAY_HI_DEFAULT       (0x00U)
#define PDM_TEST_CTL_DRIVE_DELAY_LO_DEFAULT       (0x04U)
#define PDM_TEST_CTL_MODE_HI_DEFAULT               (0x3U)
#define PDM_TEST_CTL_MODE_LO_DEFAULT               (0x3U)
#define PDM_TEST_CTL_AUDIO_FREQ_DIV_DEFAULT       (0x7U)
#define PDM_TEST_CTL_CH_ENABLED_DEFAULT           (0x0U)

#define PDM_CLOCK_CTL_CLOCK_DIV_DEFAULT           (0x07U)
#define PDM_CLOCK_CTL_CLOCK_SEL_DEFAULT           (0x3U)
#define PDM_CLOCK_CTL_HALVE_DEFAULT               (0x0U)


#define CY_PDM_PCM_ENABLE  (0x1U)
#define CY_PDM_PCM_DISABLE (0x0U)



#define CY_PDM_PCM_CH_CTL_WORDSIZE_DEFAULT        (0x0U)
#define CY_PDM_PCM_CH_CTL_WORDSIGN_EXT_DEFAULT  (0x100U)
#define CY_PDM_PCM_CH_CTL_CH_ENABLE_DEFAULT        (0x00000000U)

#define CY_PDM_PCM_TEST_CTL_DEFAULT (_VAL2FLD(PDM_TEST_CTL_DRIVE_DELAY_HI, PDM_TEST_CTL_DRIVE_DELAY_HI_DEFAULT) | \
                                _VAL2FLD(PDM_TEST_CTL_DRIVE_DELAY_LO, PDM_TEST_CTL_DRIVE_DELAY_LO_DEFAULT) | \
                                _VAL2FLD(PDM_TEST_CTL_MODE_HI, PDM_TEST_CTL_MODE_HI_DEFAULT) | \
                                _VAL2FLD(PDM_TEST_CTL_MODE_LO, PDM_TEST_CTL_MODE_LO_DEFAULT) | \
                                _VAL2FLD(PDM_TEST_CTL_AUDIO_FREQ_DIV, PDM_TEST_CTL_AUDIO_FREQ_DIV_DEFAULT) | \
                                _VAL2FLD(PDM_TEST_CTL_CH_ENABLED, PDM_TEST_CTL_CH_ENABLED_DEFAULT))

#define CY_PDM_PCM_CLK_CTL_DEFAULT (_VAL2FLD(PDM_CLOCK_CTL_CLOCK_DIV, PDM_CLOCK_CTL_CLOCK_DIV_DEFAULT) | \
                                _VAL2FLD(PDM_CLOCK_CTL_CLOCK_SEL, PDM_CLOCK_CTL_CLOCK_SEL_DEFAULT) | \
                                _VAL2FLD(PDM_CLOCK_CTL_HALVE, PDM_CLOCK_CTL_HALVE_DEFAULT))

#define CY_PDM_PCM_CH_CTL_DEFAULT (_VAL2FLD(PDM_CH_CTL_WORD_SIZE, CY_PDM_PCM_CH_CTL_WORDSIZE_DEFAULT) | \
                                _VAL2FLD(PDM_CH_CTL_WORD_SIGN_EXTEND, CY_PDM_PCM_CH_CTL_WORDSIGN_EXT_DEFAULT) | \
                                _VAL2FLD(PDM_CH_CTL_ENABLED, CY_PDM_PCM_CH_CTL_CH_ENABLE_DEFAULT))

#define CY_PDM_PCM_CH_FIR1_DEFAULT (_VAL2FLD(PDM_CH_FIR1_CTL_DECIM2, CY_PDM_PCM_CH_FIR1_DECIM_CODE_DEFAULT) | \
                                _VAL2FLD(PDM_CH_FIR1_CTL_SCALE, CY_PDM_PCM_CH_FIR1_SCALE_DEFAULT) | \
                                _VAL2FLD(PDM_CH_FIR1_CTL_ENABLED, CY_PDM_PCM_CH_FIR1_ENABLE_DEFAULT))

#define CY_PDM_PCM_CH_DCBLOCK_DEFAULT (_VAL2FLD(PDM_CH_DC_BLOCK_CTL_CODE, CY_PDM_PCM_CH_DCBLOCK_CODE_DEFAULT) | \
                                _VAL2FLD(PDM_CH_DC_BLOCK_CTL_ENABLED, CY_PDM_PCM_CH_DCBLOCK_ENABLE_DEFAULT))



/* Macros for conditions used by CY_ASSERT calls */

#define CY_PDM_PCM_IS_CLK_DIV_VALID(clkDiv)    (((clkDiv)  >= 1U) && ((clkDiv) <= CY_PDM_PCM_CLK_DIV_MAX))

#define CY_PDM_PCM_IS_CLK_SEL_VALID(clksel)    (((clksel) == CY_PDM_PCM_SEL_SRSS_CLOCK)   || \
                                                ((clksel) == CY_PDM_PCM_SEL_PDM_DATA0)       || \
                                                ((clksel) == CY_PDM_PCM_SEL_PDM_DATA1)    || \
                                                ((clksel) == CY_PDM_PCM_SEL_OFF))

#define CY_PDM_PCM_IS_HALVE_RATE_SET_VALID(halverate) (((halverate) == CY_PDM_PCM_RATE_FULL)  || \
                                                       ((halverate) == CY_PDM_PCM_RATE_HALVE))

#define CY_PDM_PCM_IS_ROUTE_VALID(route)        ((route) <= 126)

#define CY_PDM_PCM_IS_CH_SET_VALID(chanselect)    (((chanselect) >= 1U) && ((chanselect) <= 255))

#define CY_PDM_PCM_IS_SAMPLE_DELAY_VALID(sampledelay)    ((sampledelay) <= 255)

#define CY_PDM_PCM_IS_WORD_SIZE_VALID(wordSize) (((wordSize) == CY_PDM_PCM_WSIZE_8_BIT) || \
                                                ((wordSize) == CY_PDM_PCM_WSIZE_10_BIT) || \
                                                ((wordSize) == CY_PDM_PCM_WSIZE_12_BIT) || \
                                                ((wordSize) == CY_PDM_PCM_WSIZE_14_BIT) || \
                                                ((wordSize) == CY_PDM_PCM_WSIZE_16_BIT) || \
                                                ((wordSize) == CY_PDM_PCM_WSIZE_18_BIT) || \
                                                ((wordSize) == CY_PDM_PCM_WSIZE_20_BIT) || \
                                                ((wordSize) == CY_PDM_PCM_WSIZE_24_BIT) || \
                                                ((wordSize) == CY_PDM_PCM_WSIZE_32_BIT))

#define CY_PDM_PCM_IS_SCALE_VALID(scale)        ((scale) <= 31)

#define CY_PDM_PCM_IS_ENABLE_VALID(enable)         ((enable == 0)||(enable == 1))

#define CY_PDM_PCM_IS_SIGNEXTENSION_VALID(signExtension) ((signExtension == 0)||(signExtension == 1))

#define CY_PDM_PCM_IS_INTR_MASK_VALID(interrupt)  (0UL == ((interrupt) & ((uint32_t) ~CY_PDM_PCM_INTR_MASK)))
#define CY_PDM_PCM_IS_TRIG_LEVEL(trigLevel)     ((trigLevel) <= 63)

/** \endcond */

/**
* \addtogroup group_pdm_pcm_functions_v2
* \{
*/

cy_en_pdm_pcm_status_t Cy_PDM_PCM_Channel_Init(PDM_Type * base, cy_stc_pdm_pcm_channel_config_t const * channel_config, uint8_t channel_num);
void Cy_PDM_PCM_Channel_DeInit(PDM_Type * base, uint8_t channel_num);

cy_en_pdm_pcm_status_t   Cy_PDM_PCM_Init(PDM_Type * base, cy_stc_pdm_pcm_config_v2_t const * config);
                void     Cy_PDM_PCM_DeInit(PDM_Type * base);

cy_en_pdm_pcm_status_t      Cy_PDM_PCM_test_Init(PDM_Type * base, cy_stc_pdm_pcm_config_v2_t const * config, cy_stc_test_config_t const * test_config);

__STATIC_INLINE void      Cy_PDM_PCM_Activate_Channel(PDM_Type * base, uint8_t channel_num);
__STATIC_INLINE void      Cy_PDM_PCM_DeActivate_Channel(PDM_Type * base, uint8_t channel_num);
__STATIC_INLINE void     Cy_PDM_PCM_SetRateSampling(PDM_Type * base, cy_en_pdm_pcm_halve_rate_sel_t rate);

__STATIC_INLINE void     Cy_PDM_PCM_Channel_Enable(PDM_Type * base, uint8_t channel_num);
__STATIC_INLINE void     Cy_PDM_PCM_Channel_Disable(PDM_Type * base, uint8_t channel_num);
__STATIC_INLINE void     Cy_PDM_PCM_Channel_Set_Cic_DecimCode(PDM_Type * base, uint8_t channel_num, cy_en_pdm_pcm_ch_cic_decimcode_t decimcode);
__STATIC_INLINE void     Cy_PDM_PCM_Channel_Set_Fir0(PDM_Type * base, uint8_t channel_num, cy_en_pdm_pcm_ch_fir0_decimcode_t decimcode,uint8_t scale);
__STATIC_INLINE void     Cy_PDM_PCM_Channel_Set_Fir1(PDM_Type * base, uint8_t channel_num, cy_en_pdm_pcm_ch_fir1_decimcode_t decimcode,uint8_t scale);
__STATIC_INLINE void     Cy_PDM_PCM_Channel_Set_DCblock(PDM_Type * base, uint8_t channel_num, cy_en_pdm_pcm_ch_dcblock_coef_t coef);
__STATIC_INLINE void     Cy_PDM_PCM_Channel_SetInterruptMask(PDM_Type * base, uint8_t channel_num, uint32_t interrupt);
__STATIC_INLINE uint32_t Cy_PDM_PCM_Channel_GetInterruptMask(PDM_Type const * base, uint8_t channel_num);
__STATIC_INLINE uint32_t Cy_PDM_PCM_Channel_GetInterruptStatusMasked(PDM_Type const * base, uint8_t channel_num);
__STATIC_INLINE uint32_t Cy_PDM_PCM_Channel_GetInterruptStatus(PDM_Type const * base, uint8_t channel_num);
__STATIC_INLINE void     Cy_PDM_PCM_Channel_ClearInterrupt(PDM_Type * base, uint8_t channel_num, uint32_t interrupt);
__STATIC_INLINE void     Cy_PDM_PCM_Channel_SetInterrupt(PDM_Type * base, uint8_t channel_num, uint32_t interrupt);
__STATIC_INLINE uint8_t  Cy_PDM_PCM_Channel_GetNumInFifo(PDM_Type const * base, uint8_t channel_num);
__STATIC_INLINE uint32_t Cy_PDM_PCM_Channel_ReadFifo(PDM_Type const * base, uint8_t channel_num);
__STATIC_INLINE void     Cy_PDM_PCM_Channel_FreezeFifo(PDM_Type * base, uint8_t channel_num);
__STATIC_INLINE void     Cy_PDM_PCM_Channel_UnfreezeFifo(PDM_Type * base, uint8_t channel_num);
__STATIC_INLINE uint32_t Cy_PDM_PCM_Channel_ReadFifoSilent(PDM_Type const * base, uint8_t channel_num);


/** \} group_pdm_pcm_functions_v2 */

/**
* \addtogroup group_pdm_pcm_functions_v2
* \{
*/

/******************************************************************************
* Function Name: Cy_PDM_PCM_Channel_Enable
***************************************************************************//**
*
* Enables the PDM-PCM data conversion.
*
* \param base The pointer to the  PDM-PCM instance address.
* \param channel_num Channel number to be enabled
*
* \funcusage
* \snippet pdm_pcmv2/snippet/main.c snippet_Cy_PDM_PCM_Channel_Enable
*
******************************************************************************/
__STATIC_INLINE void Cy_PDM_PCM_Channel_Enable(PDM_Type * base, uint8_t channel_num)
{
    PDM_PCM_CH_CTL(base,channel_num) |= PDM_CH_CTL_ENABLED_Msk;

}

/******************************************************************************
* Function Name: Cy_PDM_PCM_Channel_Disable
***************************************************************************//**
*
* Disables the PDM-PCM data conversion.
*
* \param base The pointer to the PDM-PCM instance address.
* \param channel_num Channel number to be disabled
*
* \funcusage
* \snippet pdm_pcmv2/snippet/main.c snippet_Cy_PDM_PCM_Channel_Disable
*
******************************************************************************/
__STATIC_INLINE void Cy_PDM_PCM_Channel_Disable(PDM_Type * base, uint8_t channel_num)
{
    PDM_PCM_CH_CTL(base,channel_num) &= (uint32_t) ~PDM_CH_CTL_ENABLED_Msk;

}

/******************************************************************************
* Function Name: Cy_PDM_PCM_Activate_Channel
***************************************************************************//**
*
* Activates the PDM-PCM channel.
*
* \param base The pointer to the  PDM-PCM instance address.
* \param channel_num Channel number to be activated
*
* \funcusage
* \snippet pdm_pcmv2/snippet/main.c snippet_Cy_PDM_PCM_Activate_Channel
*
******************************************************************************/
__STATIC_INLINE void Cy_PDM_PCM_Activate_Channel(PDM_Type * base, uint8_t channel_num)
{
    PDM_PCM_CTL_SET(base) = (1UL << channel_num);
}

/******************************************************************************
* Function Name: Cy_PDM_PCM_DeActivate_Channel
***************************************************************************//**
*
* DeActivates the PDM-PCM channel.
*
* \param base The pointer to the  PDM-PCM instance address.
* \param channel_num Channel number to be deactivated
*
* \funcusage
* \snippet pdm_pcmv2/snippet/main.c snippet_Cy_PDM_PCM_DeActivate_Channel
*
******************************************************************************/
__STATIC_INLINE void Cy_PDM_PCM_DeActivate_Channel(PDM_Type * base, uint8_t channel_num)
{
    PDM_PCM_CTL_CLR(base) = (1UL << channel_num);
}


/******************************************************************************
* Function Name: Cy_PDM_PCM_Channel_GetCurrentState
***************************************************************************//**
*
* Returns the current PDM-PCM state (active/stopped).
*
* \param base The pointer to the PDM-PCM instance address.
* \param channel_num Channel number
* \return true if channel is active, false when stopped.
*
* \funcusage
* \snippet pdm_pcmv2/snippet/main.c snippet_Cy_PDM_PCM_Channel_GetCurrentState
*
******************************************************************************/
__STATIC_INLINE bool Cy_PDM_PCM_Channel_GetCurrentState(PDM_Type const * base, uint8_t channel_num)
{
    return ((bool) (PDM_PCM_CTL(base) & (1UL << channel_num)));
}


/******************************************************************************
* Function Name: Cy_PDM_PCM_Channel_SetRateSampling
***************************************************************************//**
*
* Sets Halve rate Sampling rate.
*
* \param base The pointer to the PDM-PCM instance address.
* \param rate Halve rate sampling or Full rate sampling \ref cy_en_pdm_pcm_halve_rate_sel_t.
*
* \funcusage
* \snippet pdm_pcmv2/snippet/main.c snippet_Cy_PDM_PCM_SetRateSampling
*
******************************************************************************/
__STATIC_INLINE void Cy_PDM_PCM_SetRateSampling(PDM_Type * base, cy_en_pdm_pcm_halve_rate_sel_t rate)
{
    CY_ASSERT_L2(CY_PDM_PCM_IS_HALVE_RATE_SET_VALID(rate));
    PDM_PCM_CLOCK_CTL(base) &= ~PDM_CLOCK_CTL_HALVE_Msk;
    PDM_PCM_CLOCK_CTL(base) |= _VAL2FLD(PDM_CLOCK_CTL_HALVE, rate);
}

/******************************************************************************
* Function Name: Cy_PDM_PCM_Channel_SetCicDecimCode
***************************************************************************//**
*
* Sets  PDM-PCM CIC Filter Decimation code.
*
* \param base The pointer to the PDM-PCM instance address
* \param channel_num Channel number for which the CIC filter Decimation code to be set
* \param decimcode decimation code value to be set. \ref cy_en_pdm_pcm_ch_cic_decimcode_t.
*
* \funcusage
* \snippet pdm_pcmv2/snippet/main.c snippet_Cy_PDM_PCM_Channel_Set_Cic_DecimCode
*
******************************************************************************/
__STATIC_INLINE void  Cy_PDM_PCM_Channel_Set_Cic_DecimCode(PDM_Type * base, uint8_t channel_num, cy_en_pdm_pcm_ch_cic_decimcode_t decimcode)
{
    PDM_PCM_CH_CIC_CTL(base, channel_num) = (uint32_t)decimcode;
}


/******************************************************************************
* Function Name: Cy_PDM_PCM_Channel_Set_Fir0
***************************************************************************//**
*
* Sets  PDM-PCM FIR0 Filter Decim code and Scale.
* The FIR filter coefficients have no default values:
* the coefficients MUST be programmed BEFORE the filter is enabled.
* By Default FIR0 is disabled and is only used for 8Khz and 16 Khz sample frequencies.
* For other frequencies it is a pass through.
*
* \param base The pointer to the PDM-PCM instance address
* \param channel_num Channel number for which the FIR0 Decimation code and the filter to be set.
* \param decimcode Decimation code value to be set. \ref cy_en_pdm_pcm_ch_fir0_decimcode_t.
* \param scale Scale value to be set.
*
* \funcusage
* \snippet pdm_pcmv2/snippet/main.c snippet_Cy_PDM_PCM_Channel_Set_Fir0
*
******************************************************************************/
__STATIC_INLINE void  Cy_PDM_PCM_Channel_Set_Fir0(PDM_Type * base, uint8_t channel_num, cy_en_pdm_pcm_ch_fir0_decimcode_t decimcode,uint8_t scale)
{
    CY_ASSERT_L2(CY_PDM_PCM_IS_SCALE_VALID(scale));
    PDM_PCM_CH_FIR0_CTL(base, channel_num) &= ~(PDM_CH_FIR0_CTL_DECIM3_Msk | PDM_CH_FIR0_CTL_SCALE_Msk);
    PDM_PCM_CH_FIR0_CTL(base, channel_num) |= _VAL2FLD(PDM_CH_FIR0_CTL_DECIM3,  decimcode) |
                                              _VAL2FLD(PDM_CH_FIR0_CTL_SCALE,        scale);
}

/******************************************************************************
* Function Name: Cy_PDM_PCM_Channel_Set_Fir1
***************************************************************************//**
*
* Sets  PDM-PCM FIR1 Filter Decimation code and Scale.
*
* \param base The pointer to the PDM-PCM instance address
* \param channel_num Channel number for which the FIR1 Decimation code and the filter to be set.
* \param decimcode Decimation code value to be set. \ref cy_en_pdm_pcm_ch_fir1_decimcode_t.
* \param scale Scale value to be set.
*
* \funcusage
* \snippet pdm_pcmv2/snippet/main.c snippet_Cy_PDM_PCM_Channel_Set_Fir1
*
******************************************************************************/
__STATIC_INLINE void  Cy_PDM_PCM_Channel_Set_Fir1(PDM_Type * base, uint8_t channel_num, cy_en_pdm_pcm_ch_fir1_decimcode_t decimcode,uint8_t scale)
{
    CY_ASSERT_L2(CY_PDM_PCM_IS_SCALE_VALID(scale));
    PDM_PCM_CH_FIR1_CTL(base, channel_num) &= ~(PDM_CH_FIR1_CTL_DECIM2_Msk | PDM_CH_FIR1_CTL_SCALE_Msk);
    PDM_PCM_CH_FIR1_CTL(base, channel_num) |= _VAL2FLD(PDM_CH_FIR1_CTL_DECIM2,  decimcode) |
                                             _VAL2FLD(PDM_CH_FIR1_CTL_SCALE,        scale);
}



/******************************************************************************
* Function Name: Cy_PDM_PCM_Channel_Set_DCblock
***************************************************************************//**
*
* Sets the DC blocker filter with programmable coefficient.
* The filter is used to remove a DC component.
*
* \param base The pointer to the PDM-PCM instance address
* \param channel_num Channel number for which DC block coef to be set.
* \param coef coef value to be set. \ref cy_en_pdm_pcm_ch_dcblock_coef_t.
*
* \funcusage
* \snippet pdm_pcmv2/snippet/main.c snippet_Cy_PDM_PCM_Channel_Set_DCblock
*
******************************************************************************/
__STATIC_INLINE void  Cy_PDM_PCM_Channel_Set_DCblock(PDM_Type * base, uint8_t channel_num, cy_en_pdm_pcm_ch_dcblock_coef_t coef)
{
    PDM_PCM_CH_DC_BLOCK_CTL(base, channel_num) &= ~(PDM_CH_DC_BLOCK_CTL_CODE_Msk);
    PDM_PCM_CH_DC_BLOCK_CTL(base, channel_num) |= _VAL2FLD(PDM_CH_DC_BLOCK_CTL_CODE,    coef);
}

/******************************************************************************
* Function Name: Cy_PDM_PCM_Channel_SetInterruptMask
***************************************************************************//**
*
* Sets one or more PDM-PCM interrupt factor bits (sets the INTR_MASK register).
*
* \param base The pointer to the PDM-PCM instance address
* \param channel_num Channel number
* \param interrupt Interrupt bit mask
* \ref group_pdm_pcm_macros_interrupt_masks_v2.
*
* \funcusage
* \snippet pdm_pcmv2/snippet/main.c snippet_Cy_PDM_PCM_Channel_SetInterruptMask
*
******************************************************************************/
__STATIC_INLINE void Cy_PDM_PCM_Channel_SetInterruptMask(PDM_Type * base, uint8_t channel_num, uint32_t interrupt)
{
    CY_ASSERT_L2(CY_PDM_PCM_IS_INTR_MASK_VALID(interrupt));
    PDM_PCM_INTR_RX_MASK(base, channel_num) = interrupt;
}


/******************************************************************************
* Function Name: Cy_PDM_PCM_Channel_GetInterruptMask
***************************************************************************//**
*
* Returns the PDM-PCM interrupt mask (a content of the INTR_MASK register).
*
* \param base The pointer to the PDM-PCM instance address.
* \param channel_num Channel number
* \return The interrupt bit mask \ref group_pdm_pcm_macros_interrupt_masks_v2.
*
******************************************************************************/
__STATIC_INLINE uint32_t Cy_PDM_PCM_Channel_GetInterruptMask(PDM_Type const * base, uint8_t channel_num)
{
    return (PDM_PCM_INTR_RX_MASK(base, channel_num));
}


/******************************************************************************
* Function Name: Cy_PDM_PCM_Channel_GetInterruptStatusMasked
***************************************************************************//**
*
* Reports the status of enabled (masked) PDM-PCM interrupt sources.
* (an INTR_MASKED register).
*
* \param base The pointer to the PDM-PCM instance address.
* \param channel_num Channel number
* \return The interrupt bit mask \ref group_pdm_pcm_macros_interrupt_masks_v2.
*
* \funcusage
* \snippet pdm_pcmv2/snippet/main.c snippet_Cy_PDM_PCM_Channel_ReadFifo
*
*****************************************************************************/
__STATIC_INLINE uint32_t Cy_PDM_PCM_Channel_GetInterruptStatusMasked(PDM_Type const * base, uint8_t channel_num)
{
    return (PDM_PCM_INTR_RX_MASKED(base, channel_num));
}


/******************************************************************************
* Function Name: Cy_PDM_PCM_Channel_GetInterruptStatus
***************************************************************************//**
*
* Reports the status of PDM-PCM interrupt sources (an INTR register).
*
* \param base The pointer to the PDM-PCM instance address.
* \param channel_num Channel number
* \return The interrupt bit mask \ref group_pdm_pcm_macros_interrupt_masks_v2.
*
* \funcusage
* \snippet pdm_pcmv2/snippet/main.c snippet_Cy_PDM_PCM_Channel_ReadFifo
*
******************************************************************************/
__STATIC_INLINE uint32_t Cy_PDM_PCM_Channel_GetInterruptStatus(PDM_Type const * base, uint8_t channel_num)
{
    return (PDM_PCM_INTR_RX(base, channel_num));
}


/******************************************************************************
* Function Name: Cy_PDM_PCM_Channel_ClearInterrupt
***************************************************************************//**
*
* Clears one or more PDM-PCM interrupt statuses (sets an INTR register's bits).
*
* \param base The pointer to the PDM-PCM instance address
* \param channel_num Channel number
* \param interrupt
*  The interrupt bit mask \ref group_pdm_pcm_macros_interrupt_masks_v2.
*
* \funcusage
* \snippet pdm_pcmv2/snippet/main.c snippet_Cy_PDM_PCM_Channel_ClearInterrupt
*
******************************************************************************/
__STATIC_INLINE void Cy_PDM_PCM_Channel_ClearInterrupt(PDM_Type * base, uint8_t channel_num, uint32_t interrupt)
{
    CY_ASSERT_L2(CY_PDM_PCM_IS_INTR_MASK_VALID(interrupt));
    PDM_PCM_INTR_RX(base, channel_num) = interrupt;
    (void) PDM_PCM_INTR_RX(base, channel_num);
}


/******************************************************************************
* Function Name: Cy_PDM_PCM_Channel_SetInterrupt
***************************************************************************//**
*
* Sets one or more interrupt source statuses (sets an INTR_SET register).
*
* \param base The pointer to the PDM-PCM instance address.
* \param channel_num Channel number
* \param interrupt
*  The interrupt bit mask \ref group_pdm_pcm_macros_interrupt_masks_v2.
*
******************************************************************************/
__STATIC_INLINE void Cy_PDM_PCM_Channel_SetInterrupt(PDM_Type * base, uint8_t channel_num, uint32_t interrupt)
{
    CY_ASSERT_L2(CY_PDM_PCM_IS_INTR_MASK_VALID(interrupt));
    PDM_PCM_INTR_RX_SET(base, channel_num) = interrupt;
}


/******************************************************************************
* Function Name: Cy_PDM_PCM_Channel_GetNumInFifo
***************************************************************************//**
*
* Reports the current number of used words in the output data FIFO.
*
* \param base The pointer to the PDM-PCM instance address.
* \param channel_num Channel number
* \return The current number of used FIFO words (range is 0 - 63).
*
* \funcusage
* \snippet pdm_pcmv2/snippet/main.c snippet_Cy_PDM_PCM_Channel_GetNumInFifo
*
******************************************************************************/
__STATIC_INLINE uint8_t Cy_PDM_PCM_Channel_GetNumInFifo(PDM_Type const * base, uint8_t channel_num)
{
    return (uint8_t) (_FLD2VAL(PDM_CH_RX_FIFO_STATUS_USED, PDM_PCM_RX_FIFO_STATUS(base, channel_num)));
}


/******************************************************************************
* Function Name: Cy_PDM_PCM_Channel_ReadFifo
***************************************************************************//**
*
* Reads ("pops") one word from the output data FIFO.
*
* \param base The pointer to the PDM-PCM instance address.
* \param channel_num Channel number
* \return The data word read from the FIFO is returned.
*
* \funcusage
* \snippet pdm_pcmv2/snippet/main.c snippet_Cy_PDM_PCM_Channel_ReadFifo
*
******************************************************************************/
__STATIC_INLINE uint32_t Cy_PDM_PCM_Channel_ReadFifo(PDM_Type const * base, uint8_t channel_num)
{
    return (PDM_PCM_RX_FIFO_RD(base, channel_num));
}

/******************************************************************************
* Function Name: Cy_PDM_PCM_Channel_FreezeFifo
***************************************************************************//**
*
* Freezes the RX FIFO (Debug purpose).
*
* \param base The pointer to the PDM-PCM instance address.
* \param channel_num Channel number
*
* \funcusage
* \snippet pdm_pcmv2/snippet/main.c snippet_Cy_PDM_PCM_Channel_FreezeFifo
*
******************************************************************************/
__STATIC_INLINE void Cy_PDM_PCM_Channel_FreezeFifo(PDM_Type * base, uint8_t channel_num)
{
    PDM_PCM_RX_FIFO_CTL(base, channel_num) |= PDM_CH_RX_FIFO_CTL_FREEZE_Msk;
}


/******************************************************************************
* Function Name: Cy_PDM_PCM_Channel_UnfreezeFifo
***************************************************************************//**
*
* Unfreezes the RX FIFO (Debug purpose).
*
* \param base The pointer to the PDM-PCM instance address.
* \param channel_num Channel number
*
* \funcusage
* \snippet pdm_pcmv2/snippet/main.c snippet_Cy_PDM_PCM_Channel_UnfreezeFifo
*
******************************************************************************/
__STATIC_INLINE void Cy_PDM_PCM_Channel_UnfreezeFifo(PDM_Type * base, uint8_t channel_num)
{
    PDM_PCM_RX_FIFO_CTL(base, channel_num) &= (uint32_t) ~PDM_CH_RX_FIFO_CTL_FREEZE_Msk;
}


/******************************************************************************
* Function Name: Cy_PDM_PCM_Channel_ReadFifoSilent
***************************************************************************//**
*
* Reads the RX FIFO silent (without touching the FIFO function).
*
* \param base Pointer to PDM-PCM instance address.
* \param channel_num Channel number
* \return Silent FIFO value is read and returned.
*
* \funcusage
* \snippet pdm_pcmv2/snippet/main.c snippet_Cy_PDM_PCM_Channel_ReadFifoSilent
*
******************************************************************************/
__STATIC_INLINE uint32_t Cy_PDM_PCM_Channel_ReadFifoSilent(PDM_Type const * base, uint8_t channel_num)
{
    return (PDM_PCM_RX_FIFO_RD_SILENT(base, channel_num));
}

/** \} group_pdm_pcm_functions_v2 */

#ifdef __cplusplus
}
#endif  /* of __cplusplus */

#endif /* CY_IP_MXPDM */

#endif /* CY_PDM_PCM_V2_H__ */

/** \} group_pdm_pcm_v2 */


/* [] END OF FILE */
