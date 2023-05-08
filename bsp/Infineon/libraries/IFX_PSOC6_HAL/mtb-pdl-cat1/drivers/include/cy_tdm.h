/***************************************************************************//**
* \file cy_tdm.h
* \version 1.0
*
* \brief
* The header file of the Audio TDM driver.
*
********************************************************************************
* \copyright
* Copyright 2021 Cypress Semiconductor Corporation
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
* \addtogroup group_tdm
* \{
* \note IP Supported: TDM
* \note Device Categories: CAT1B. Please refer <a href="usergroup1.html">Device Catalog</a>.
* Configures audio TDM/I2S.
*
* The functions and other declarations used in this driver are in cy_tdm.h.
* You can include cy_pdl.h (ModusToolbox only) to get access to all functions
* and declarations in the PDL.
*
*
* Features:
* * Supports I2S mode and TDM mode.
* * Master and slave functionality.
* * Full-duplex transmitter and receiver operation.
* * Support for up to 32 channels.
* * Programmable channel size (up to 32 bits)
* * Programmable channel delay of 0 or 1 bit.
* * Delayed sampling support.
* * Programmable PCM sample formatting (8, 10, 12, 14, 16, 18, 20, 24, 32 bits).
* * Programmable synchronization pulse type.
* * Left-aligned and right-aligned sample formatting.
* * 128 entry TX FIFO with interrupt and trigger support.
* * 128 entry RX FIFO with interrupt and trigger support.
*
* \section group_tdm_configuration Configuration Considerations
*
* To set up a TDM driver, initialize the TDM Transmitter module in accordance with a configuration structure.
*
* * Each TDM/I2S (TX, RX) pair consists of a TDM/I2S transmitter and a TDM/I2S receiver.
* * The transmitter and receiver can function simultaneously and have dedicated clock control.
* * The transmitter and receiver have dedicated MMIO registers and a dedicated FIFO.
* * The transmitter and receiver have a dedicated FIFO interrupt and FIFO trigger.
* * The transmitter trigger is activated when a programmable number of PCM data slots is available in the TX FIFO.
* * The receiver trigger is activated when a programmable number of PCM data words is received into the RX FIFO.
*
*
* To set up TDM, provide the configuration parameters in the
* \ref cy_stc_tdm_config_t structure.
*
* For example, for Tx configuration, set txEnabled to true, configure
* txDmaTrigger (depending on whether DMA is going to be used or not), set
* extClk (if an external clock is used), provide clkDiv, masterMode,
* sckPolarity, fsyncPolarity, channelSize, wordSize,
* either i2sMode or TDM (based on Mode setting),
* fifoTriggerLevel (when the Trig interrupt will be used) and format
* A similar setup is for the Rx configuration.
*
* To initialize the TDM block, call the \ref Cy_AudioTDM_Init function, providing the
* filled \ref cy_stc_tdm_config_t structure.
* Before starting the transmission, enable the Tx \ref Cy_AudioTDM_EnableTx, then
* fill the first Tx data frame by calling \ref Cy_AudioTDM_WriteTxData. Then
* call the \ref Cy_AudioTDM_ActivateTx.
* For the reception the sequence is the same except for filling the first data
* frame.
*
* For example:
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_Init
*
* If you use a DMA, the DMA channel should be previously configured. The TDM interrupts
* (if applicable) can be enabled by calling \ref Cy_AudioTDM_SetTxInterruptMask.
*
* For example, if the trigger interrupt is used during operation, the ISR
* should call the \ref Cy_AudioTDM_WriteTxData as many times as required for your
* FIFO payload, but not more than the FIFO size. Then call \ref Cy_AudioTDM_ClearTxInterrupt
* with appropriate parameters.
*
* If a DMA is used and the DMA channel is properly configured - no CPU activity
* (or any application code) is needed for I2S/TDM operation.
*
* The I2S frame appears as:
* \image html i2s_frame.png
* This is an example for the channel length = 32. A similar case exists for the rest
* channel length configuration, with one limitation: the word length should be less than or equal
* to the channel length. See the datasheet of your device for more details.
*
* \section group_tdm_MISRA MISRA-C Compliance
* The TDM driver has the following specific deviations:
*
* <table class="doxtable">
*   <tr>
*     <th>MISRA Rule</th>
*     <th>Rule Class (Required/Advisory)</th>
*     <th>Rule Description</th>
*     <th>Description of Deviation(s)</th>
*   </tr>
*   <tr>
*     <td>10.3</td>
*     <td>R</td>
*     <td>A composite expression of the "essentially unsigned" type is being
*         cast to a different type category.</td>
*     <td>The value got from the bitfield physically cannot exceed the enumeration
*         that describes this bitfield. So, the code is safe by design.</td>
*   </tr>
*   <tr>
*     <td>11.4</td>
*     <td>A</td>
*     <td>A cast should not be performed between a pointer to object type and
*         a different pointer to object type.</td>
*   </tr>
*   <tr>
*     <td>20.3</td>
*     <td>R</td>
*     <td>The validity of values passed to library functions shall be checked.</td>
*     <td>This violation is not caused by code changes, i.e. is not a regression.</td>
*   </tr>
* </table>
*
* \section group_tdm_changelog Changelog
*
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*

* \defgroup group_tdm_i2s_macros_interrupt_masks Interrupt Masks
* \defgroup group_tdm_data_structures Data Structures
* \defgroup group_tdm_enums Enumerated Types
* \defgroup group_tdm_macros Macros
* \defgroup group_tdm_functions Functions

*/

#if !defined (CY_TDM_H)
#define CY_TDM_H

#include "cy_device.h"

#if defined (CY_IP_MXTDM)

#include "cy_syslib.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 14.3', 14, \
'Checked manually, passed true or false in _BOOL2FLD for appropriate functionality.');

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 10.1', 14, \
'Checked manually, passed true or false in _BOOL2FLD for appropriate functionality.');

/******************************************************************************
 * Macro definitions                                                          *
 ******************************************************************************/

/**
* \addtogroup group_tdm_macros
* \{
*/

/** The driver major version */
#define CY_I2S_DRV_VERSION_MAJOR       1

/** The driver minor version */
#define CY_I2S_DRV_VERSION_MINOR       0

/** The TDM driver identifier */
#define CY_TDM_ID                      (CY_PDL_DRV_ID(0x50U))

/** \} group_tdm_macros */

/**
* \addtogroup group_tdm_i2s_macros_interrupt_masks
* \{
*/

/** Bit 0: Less entries in the TX FIFO than specified by Trigger Level. */
#define CY_TDM_INTR_TX_FIFO_TRIGGER         (TDM_TDM_STRUCT_TDM_TX_STRUCT_INTR_TX_FIFO_TRIGGER_Msk)
/** Bit 1: Attempt to write to a full TX FIFO. */
#define CY_TDM_INTR_TX_FIFO_OVERFLOW        (TDM_TDM_STRUCT_TDM_TX_STRUCT_INTR_TX_FIFO_OVERFLOW_Msk)
/** Bit 2: Attempt to read from an empty TX FIFO. */
#define CY_TDM_INTR_TX_FIFO_UNDERFLOW       (TDM_TDM_STRUCT_TDM_TX_STRUCT_INTR_TX_FIFO_UNDERFLOW_Msk)
/** Bit 8: Interface frequency is higher than PCM sample frequency. */
#define CY_TDM_INTR_TX_IF_UNDERFLOW         (TDM_TDM_STRUCT_TDM_TX_STRUCT_INTR_TX_IF_UNDERFLOW_Msk)

/** Bit 0: Less entries in the RX FIFO than specified by Trigger Level. */
#define CY_TDM_INTR_RX_FIFO_TRIGGER         (TDM_TDM_STRUCT_TDM_RX_STRUCT_INTR_RX_FIFO_TRIGGER_Msk)
/** Bit 1: Attempt to write to a full RX FIFO. */
#define CY_TDM_INTR_RX_FIFO_OVERFLOW        (TDM_TDM_STRUCT_TDM_RX_STRUCT_INTR_RX_FIFO_OVERFLOW_Msk)
/** Bit 2: Attempt to read from an empty RX FIFO. */
#define CY_TDM_INTR_RX_FIFO_UNDERFLOW       (TDM_TDM_STRUCT_TDM_RX_STRUCT_INTR_RX_FIFO_UNDERFLOW_Msk)
/** Bit 8: Interface frequency is higher than PCM sample frequency. */
#define CY_TDM_INTR_RX_IF_UNDERFLOW         (TDM_TDM_STRUCT_TDM_RX_STRUCT_INTR_RX_IF_OVERFLOW_Msk)

/** \} group_tdm_i2s_macros_interrupt_masks */


/**
* \addtogroup group_tdm_enums
* \{
*/

/** cy_en_tdm_ws_t */
typedef enum
{
    CY_TDM_SIZE_8           = 0U, /**< PCM word size:8bit.  */
    CY_TDM_SIZE_10          = 1U, /**< PCM word size:10bit. */
    CY_TDM_SIZE_12          = 2U, /**< PCM word size:12bit. */
    CY_TDM_SIZE_14          = 3U, /**< PCM word size:14bit. */
    CY_TDM_SIZE_16          = 4U, /**< PCM word size:16bit. */
    CY_TDM_SIZE_18          = 5U, /**< PCM word size:18bit. */
    CY_TDM_SIZE_20          = 6U, /**< PCM word size:20bit. */
    CY_TDM_SIZE_24          = 7U, /**< PCM word size:24bit. */
    CY_TDM_SIZE_32          = 8U  /**< PCM word size:32bit. */
} cy_en_tdm_ws_t;

/** cy_en_tdm_format_t */
typedef enum
{
    CY_TDM_LEFT_DELAYED     = 0, /**< Format is left aligned and delayed. */
    CY_TDM_LEFT             = 1, /**< Format is left aligned. */
    CY_TDM_RIGHT_DELAYED    = 2, /**< Format is right aligned and delayed. */
    CY_TDM_RIGHT            = 3  /**< Format is right aligned. */
} cy_en_tdm_format_t;

/** cy_en_tdm_device_cfg_t */
typedef enum
{
    CY_TDM_DEVICE_SLAVE     = 0U, /**< Device is configured as slave. */
    CY_TDM_DEVICE_MASTER    = 1U  /**< Device is configured as master. */
} cy_en_tdm_device_cfg_t;

/** cy_en_tdm_word_extend_cfg_t */
typedef enum
{
    CY_ZERO_EXTEND      = 0U,    /**< Zero extended. */
    CY_SIGN_EXTEND      = 1U    /**< sign extended. */
} cy_en_tdm_word_extend_cfg_t;

/** cy_en_tdm_clock_sel_t */
typedef enum
{
    CY_TDM_SEL_SRSS_CLK0    = 0U, /**< Interface clock is selected as clk_if_srss[0]. */
    CY_TDM_SEL_SRSS_CLK1    = 1U, /**< Interface clock is selected as clk_if_srss[1]. */
    CY_TDM_SEL_SRSS_CLK2    = 2U, /**< Interface clock is selected as clk_if_srss[2]. */
    CY_TDM_SEL_SRSS_CLK3    = 3U, /**< Interface clock is selected as clk_if_srss[3]. */
    CY_TDM_SEL_MCLK_IN      = 4U  /**< Interface clock is selected as tdm_tx/rx_mclk_in. */
} cy_en_tdm_clock_sel_t;

/** cy_en_tdm_sckpolarity_t */
typedef enum
{
    CY_TDM_CLK              = 0U, /**< TDM Clock is used as is. */
    CY_TDM_CLK_INVERTED     = 1U  /**< TDM Clock is inverted. */
} cy_en_tdm_sckpolarity_t;

/** cy_en_tdm_fsyncpolarity_t*/
typedef enum
{
    CY_TDM_SIGN             = 0U, /**< TDM Sign is used as is. */
    CY_TDM_SIGN_INVERTED    = 1U  /**< TDM Sign is inverted. */
} cy_en_tdm_fsyncpolarity_t;

/** cy_en_tdm_fsyncformat_t */
typedef enum
{
    CY_TDM_BIT_PERIOD       = 0U, /**< TDM Channel Synchronization is duration of a bit period. */
    CY_TDM_CH_PERIOD        = 1U  /**< TDM Channel Synchronization is duration of a channel period. */
} cy_en_tdm_fsyncformat_t;

/**
* TDM status definitions.
*/
typedef enum
{
    CY_TDM_SUCCESS          = 0x00UL,                                     /**< Successful. */
    CY_TDM_BAD_PARAM        = CY_TDM_ID | CY_PDL_STATUS_ERROR | 0x01UL  /**< One or more invalid parameters. */
} cy_en_tdm_status_t;

/** cy_en_tdm_source_status_t */
typedef enum
{
    CY_TDM_OK                = 0x00UL, /**< Successful. */
    CY_TDM_BAD               = 0x01UL  /**< Not Good    */
} cy_en_tdm_source_status_t;

/** \} group_tdm_enums */

/**
* \addtogroup group_tdm_data_structures
* \{
*/
/** TDM Initialization configuration. */
typedef struct
{
    bool                        enable;               /**<  Enables/Disables TDM TX */
    cy_en_tdm_device_cfg_t      masterMode;           /**<  Master mode/Slave mode configuration. \ref cy_en_tdm_device_cfg_t */
    cy_en_tdm_ws_t              wordSize;             /**<  TX word length. Channel size must be greater or equal to the word size.*/
    cy_en_tdm_format_t          format;               /**<  TX data format, \ref cy_en_tdm_format_t. */
    uint16_t                    clkDiv;               /**<  Should be set to an even value ({2, 4, 6, ..., 256}), to ensure a 50/50% duty cycle clock. Only for Master Mode */
    cy_en_tdm_clock_sel_t       clkSel;               /**<  Interface clock "clk_if" selection, \ref cy_en_tdm_clock_sel_t. */
    cy_en_tdm_sckpolarity_t     sckPolarity;          /**<  TX clock polarity, 0: as is and 1: inverted \ref cy_en_tdm_sckpolarity_t */
    cy_en_tdm_fsyncpolarity_t   fsyncPolarity;        /**<  Synchronization polarity:0:as is 1:inverted. \ref cy_en_tdm_fsyncpolarity_t*/
    cy_en_tdm_fsyncformat_t     fsyncFormat;          /**<  Channel synchronization pulse format \ref cy_en_tdm_fsyncformat_t */
    uint8_t                     channelNum;           /**<  Number of channels in the frame:
                                                            1 to 32 channels supported. In I2S mode number of channels should be 2. */
    uint8_t                     channelSize;          /**<  Channel Size. Channel size must be greater or equal to the word size. */
    uint8_t                     fifoTriggerLevel;     /**<  Trigger level. When the TX FIFO has less entries than the number of this field, a transmitter trigger event is generated. */
    uint32_t                    chEn;                 /**<  Channels enabled: channel i is controlled by bit chEn[i]. For example : In I2S mode for 2 channels the chEn  will be 0x3 */
    uint32_t                    signalInput;          /**<  Controls routing to the TX slave signaling  inputs (FSYNC/SCK):
                                                              '0': TX slave signaling independent from RX signaling :
                                                              '1': TX slave signaling inputs driven by RX Slave:
                                                              '2': TX slave signaling inputs driven by RX Master: */
    bool                        i2sMode;              /**<  IF set to 1 the IP is configured for I2S mode else for TDM mode    */
}cy_stc_tdm_config_tx_t;

/** cy_stc_tdm_config_rx_t */
typedef struct
{
    bool                        enable;               /**<  Enables/Disables TDM RX */
    cy_en_tdm_device_cfg_t      masterMode;           /**<  Master mode/Slave mode configuration. \ref cy_en_tdm_device_cfg_t */
    cy_en_tdm_ws_t              wordSize;             /**<  RX word length. Channel size must be greater or equal to the word size.*/
    cy_en_tdm_word_extend_cfg_t signExtend;           /**<  Word extension \ref cy_en_tdm_word_extend_cfg_t */
    cy_en_tdm_format_t          format;               /**<  RX data format, \ref cy_en_tdm_format_t. */
    uint16_t                    clkDiv;               /**<  Should be set to an even value ({2, 4, 6, ..., 256}), to ensure a 50/50% duty cycle clock. Only for Master Mode */
    cy_en_tdm_clock_sel_t       clkSel;               /**<  Interface clock "clk_if" selection, \ref cy_en_tdm_clock_sel_t. */
    cy_en_tdm_sckpolarity_t     sckPolarity;          /**<  RX clock polarity, 0: as is and 1: inverted \ref cy_en_tdm_sckpolarity_t */
    cy_en_tdm_fsyncpolarity_t   fsyncPolarity;        /**<  Channel synchronization polarity:'false':used "as is". 'true': inverted. */
    bool                        lateSample;           /**<  Interface late sample delay.
                                                          *   Slave configuration: "false": Sample PCM bit value on rising edge or falling edge of receiver "rx_sck_in
                                                          *   "true": Sample PCM bit value on falling edge or rising edge of receiver "rx_sck_in" (half a cycle delay).
                                                          *   Master configuration: "false": Sample PCM bit value on rising edge or falling edge of receiver "rx_sck_out".
                                                          *   "true": Sample PCM bit value on falling edge or rising edge of receiver "rx_sck_out" (half a cycle delay). */
                                                        /**<  RISING = 0  FALLING = 1 */
    cy_en_tdm_fsyncformat_t     fsyncFormat;          /**<  Channel synchronization pulse format \ref cy_en_tdm_fsyncformat_t */
    uint8_t                     channelNum;           /**<  Number of channels in the frame:
                                                            1 to 32 channels supported. In I2S mode number of channels should be 2. */
    uint8_t                     channelSize;          /**<  Channel Size. Channel size must be greater or equal to the word size. */
    uint32_t                    chEn;                 /**<  Channels enabled: channel i is controlled by bit chEn[i]. For example : In I2S mode for 2 channels the chEn  will be 0x3 */
    uint8_t                     fifoTriggerLevel;     /**<  Trigger level. When the TX FIFO has less entries than the number of this field, a transmitter trigger event is generated. */
    uint32_t                    signalInput;          /**<  Controls routing to the RX slave signaling  inputs (FSYNC/SCK):
                                                              '0': RX slave signaling independent from TX signaling :
                                                              '1': RX slave signaling inputs driven by TX Slave:
                                                              '2': RX slave signaling inputs driven by TX Master: */
    bool                        i2sMode;              /**<  IF set to 1 the IP is configured for I2S mode else for TDM mode    */
} cy_stc_tdm_config_rx_t;

/** cy_stc_tdm_config_t */
typedef struct
{
    cy_stc_tdm_config_tx_t* tx_config;                    /**< TDM Initialization configuration for TX. */
    cy_stc_tdm_config_rx_t* rx_config;                    /**< TDM Initialization configuration for RX. */
}cy_stc_tdm_config_t;

/** \} group_tdm_data_structures */

/**
* \addtogroup group_tdm_macros
* \{
*/
/** \cond INTERNAL */
/*******************************************************************************/
/*                               Local definitions                             */
/********************************************************************************/

#define CY_TDM_INTR_TX_MASK            (CY_TDM_INTR_TX_FIFO_TRIGGER     |\
                                        CY_TDM_INTR_TX_FIFO_OVERFLOW    |\
                                        CY_TDM_INTR_TX_FIFO_UNDERFLOW   |\
                                        CY_TDM_INTR_TX_IF_UNDERFLOW)


#define CY_TDM_INTR_RX_MASK            (CY_TDM_INTR_RX_FIFO_TRIGGER     |\
                                        CY_TDM_INTR_RX_FIFO_OVERFLOW    |\
                                        CY_TDM_INTR_RX_FIFO_UNDERFLOW   |\
                                        CY_TDM_INTR_RX_IF_UNDERFLOW)


/* Non-zero default values for TX_CTL register */
#define CY_TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_CTL_MS_DEFAULT               (0x1U)  /**<  Default mode is selected as master */

#define CY_TDM_TX_CTL_DEFAULT                                           (_VAL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_CTL_MS, CY_TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_CTL_MS_DEFAULT))

/* Non-zero default values for TX_IF_CTL register */
#define CY_TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_CLOCK_DIV_DEFAULT     (0x7U)  /**< Default clock is clk_if/(CLOCK_DIV+1) */
#define CY_TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_CLOCK_SEL_DEFAULT     (0x7U)  /**< Default clock is selected as clk_if_srss[0], later it will be off */
#define CY_TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_CH_SIZE_DEFAULT       (0x1FU) /**< Default channel size is 32 bits */

#define CY_TDM_TX_IF_CTL_DEFAULT               (_VAL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_CLOCK_DIV, CY_TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_CLOCK_DIV_DEFAULT) | \
                                                _VAL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_CLOCK_SEL, CY_TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_CLOCK_SEL_DEFAULT) | \
                                                _VAL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_CH_SIZE, CY_TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_IF_CTL_CH_SIZE_DEFAULT))

/* Non-zero default values for RX_CTL register */
#define CY_TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_CTL_WORD_SIGN_EXTEND_DEFAULT (0x1U)  /**< Default RX data word with sign extension */

#define CY_TDM_RX_CTL_DEFAULT                   (_VAL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_CTL_WORD_SIGN_EXTEND, CY_TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_CTL_WORD_SIGN_EXTEND_DEFAULT))


/* Non-zero default values for RX_IF_CTL register */
#define CY_TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_CLOCK_DIV_DEFAULT     (0x7U)  /**< Default clock is clk_if/(CLOCK_DIV+1) */
#define CY_TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_CLOCK_SEL_DEFAULT     (0x7U)  /**< Default clock is selected as clk_if_srss[0], later it will be off */
#define CY_TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_CH_SIZE_DEFAULT       (0x1FU) /**< Default channel size is 32 bits */

#define CY_TDM_RX_IF_CTL_DEFAULT               (_VAL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_CLOCK_DIV, CY_TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_CLOCK_DIV_DEFAULT) | \
                                                _VAL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_CLOCK_SEL, CY_TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_CLOCK_SEL_DEFAULT) | \
                                                _VAL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_CH_SIZE, CY_TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_IF_CTL_CH_SIZE_DEFAULT))

/** \endcond */

/** TDM Macro */
#define CY_TDM_IS_CLK_DIV_VALID(clkDiv)      (clkDiv <= 255U)
/** TDM Macro */
#define CY_TDM_IS_CHANNELS_VALID(channels)   (((channels) > 0UL) && ((channels) <= 31UL))
/** TDM Macro */
#define CY_TDM_IS_CHANNEL_SIZE_VALID(channel_size)   (((channel_size) > 2UL) && ((channel_size) <= 31UL))
/** TDM Macro */
#define CY_I2S_TDM_INTR_TX_MASK_VALID(interrupt) (0UL == ((interrupt) & ((uint32_t) ~CY_TDM_INTR_TX_MASK)))
/** TDM Macro */
#define CY_I2S_TDM_INTR_RX_MASK_VALID(interrupt) (0UL == ((interrupt) & ((uint32_t) ~CY_TDM_INTR_RX_MASK)))
/** TDM Macro */
#define CY_I2S_TDM_IS_INPUT_SIGNAL_MODE_VALID(signalInput)   (signalInput <= 2UL)

/** \} group_tdm_macros */


/**
* \addtogroup group_tdm_functions
* \{
*/
/*******************************************************************************/
/*                      Global initialization functions                        */
/*******************************************************************************/

cy_en_tdm_status_t Cy_AudioTDM_Init( TDM_STRUCT_Type * base, cy_stc_tdm_config_t const * config);
void Cy_AudioTDM_DeInit( TDM_STRUCT_Type * base);


/*****************************************************************************/
/*                      Audio TDM Control and Status                         */
/*****************************************************************************/

__STATIC_INLINE void        Cy_AudioTDM_EnableTx( TDM_TX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_DisableTx( TDM_TX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_EnableRx( TDM_RX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_DisableRx( TDM_RX_STRUCT_Type * base);

__STATIC_INLINE void        Cy_AudioTDM_WriteTxData( TDM_TX_STRUCT_Type * base, uint32_t data);
__STATIC_INLINE void        Cy_AudioTDM_FreezeTxFifo( TDM_TX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_UnfreezeTxFifo( TDM_TX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_MuteTxFifo( TDM_TX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_ActivateTx( TDM_TX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_DeActivateTx( TDM_TX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_ReplayTxFifo( TDM_TX_STRUCT_Type * base);
__STATIC_INLINE uint8_t     Cy_AudioTDM_GetNumInTxFifo( TDM_TX_STRUCT_Type * base);
__STATIC_INLINE uint8_t     Cy_AudioTDM_GetTxReadPointer( TDM_TX_STRUCT_Type * base);
__STATIC_INLINE uint8_t     Cy_AudioTDM_GetTxWritePointer( TDM_TX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_EnableTxTestMode( TDM_TX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_DisableTxTestMode( TDM_TX_STRUCT_Type * base);

__STATIC_INLINE uint32_t    Cy_AudioTDM_ReadRxData( TDM_RX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_FreezeRxFifo( TDM_RX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_UnfreezeRxFifo( TDM_RX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_ActivateRx( TDM_RX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_DeActivateRx( TDM_RX_STRUCT_Type * base);
__STATIC_INLINE uint32_t    Cy_AudioTDM_ReadSilentRXFifo( TDM_RX_STRUCT_Type * base);
__STATIC_INLINE uint8_t     Cy_AudioTDM_GetNumInRxFifo( TDM_RX_STRUCT_Type * base);
__STATIC_INLINE uint8_t     Cy_AudioTDM_GetRxReadPointer( TDM_RX_STRUCT_Type * base);
__STATIC_INLINE uint8_t     Cy_AudioTDM_GetRxWritePointer( TDM_RX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_EnableRxTestMode( TDM_RX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_DisableRxTestMode( TDM_RX_STRUCT_Type * base);


__STATIC_INLINE void        Cy_AudioTDM_ClearTxInterrupt( TDM_TX_STRUCT_Type * base, uint32_t interrupt);
__STATIC_INLINE void        Cy_AudioTDM_SetTxInterrupt( TDM_TX_STRUCT_Type * base, uint32_t interrupt);
__STATIC_INLINE uint32_t    Cy_AudioTDM_GetTxInterruptMask( TDM_TX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_SetTxInterruptMask( TDM_TX_STRUCT_Type * base, uint32_t interrupt);
__STATIC_INLINE uint32_t    Cy_AudioTDM_GetTxInterruptStatusMasked( TDM_TX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_SetTxTriggerInterruptMask( TDM_TX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_ClearTxTriggerInterruptMask( TDM_TX_STRUCT_Type * base);

__STATIC_INLINE void        Cy_AudioTDM_ClearRxInterrupt( TDM_RX_STRUCT_Type * base, uint32_t interrupt);
__STATIC_INLINE void        Cy_AudioTDM_SetRxInterrupt( TDM_RX_STRUCT_Type * base, uint32_t interrupt);
__STATIC_INLINE uint32_t    Cy_AudioTDM_GetRxInterruptMask( TDM_RX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_SetRxInterruptMask( TDM_RX_STRUCT_Type * base, uint32_t interrupt);
__STATIC_INLINE uint32_t    Cy_AudioTDM_GetRxInterruptStatusMasked( TDM_RX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_SetRxTriggerInterruptMask( TDM_RX_STRUCT_Type * base);
__STATIC_INLINE void        Cy_AudioTDM_ClearRxTriggerInterruptMask( TDM_RX_STRUCT_Type * base);


/** \cond INTERNAL */
/*******************************************************************************
* These are legacy API for I2S.
* for backward compatibility.
* Do not use them in new designs.
*******************************************************************************/

#define Cy_AudioI2S_Init                                 Cy_AudioTDM_Init
#define Cy_AudioI2S_DeInit                                Cy_AudioTDM_DeInit

#define Cy_AudioI2S_EnableTx                              Cy_AudioTDM_EnableTx
#define Cy_AudioI2S_DisableTx                              Cy_AudioTDM_DisableTx
#define Cy_AudioI2S_EnableRx                               Cy_AudioTDM_EnableRx
#define Cy_AudioI2S_DisableRx                           Cy_AudioTDM_DisableRx

#define Cy_AudioI2S_WriteTxData                           Cy_AudioTDM_WriteTxData
#define Cy_AudioI2S_FreezeTxFifo                           Cy_AudioTDM_FreezeTxFifo
#define Cy_AudioI2S_UnfreezeTxFifo                         Cy_AudioTDM_UnfreezeTxFifo
#define Cy_AudioI2S_MuteTxFifo                          Cy_AudioTDM_MuteTxFifo
#define Cy_AudioI2S_ActivateTx                             Cy_AudioTDM_ActivateTx
#define Cy_AudioI2S_DeActivateTx                           Cy_AudioTDM_DeActivateTx
#define Cy_AudioI2S_ReplayTxFifo                          Cy_AudioTDM_ReplayTxFifo
#define Cy_AudioI2S_GetNumInTxFifo                         Cy_AudioTDM_GetNumInTxFifo
#define Cy_AudioI2S_GetTxReadPointer                      Cy_AudioTDM_GetTxReadPointer
#define Cy_AudioI2S_GetTxWritePointer                      Cy_AudioTDM_GetTxWritePointer
#define Cy_AudioI2S_EnableTxTestMode                       Cy_AudioTDM_EnableTxTestMode
#define Cy_AudioI2S_DisableTxTestMode                   Cy_AudioTDM_DisableTxTestMode

#define Cy_AudioI2S_ReadRxData                          Cy_AudioTDM_ReadRxData
#define Cy_AudioI2S_FreezeRxFifo                          Cy_AudioTDM_FreezeRxFifo
#define Cy_AudioI2S_UnfreezeRxFifo                         Cy_AudioTDM_UnfreezeRxFifo
#define Cy_AudioI2S_ActivateRx                          Cy_AudioTDM_ActivateRx
#define Cy_AudioI2S_DeActivateRx                          Cy_AudioTDM_DeActivateRx
#define Cy_AudioI2S_ReadSilentRXFifo                      Cy_AudioTDM_ReadSilentRXFifo
#define Cy_AudioI2S_GetNumInRxFifo                         Cy_AudioTDM_GetNumInRxFifo
#define Cy_AudioI2S_GetRxReadPointer                    Cy_AudioTDM_GetRxReadPointer
#define Cy_AudioI2S_GetRxWritePointer                      Cy_AudioTDM_GetRxWritePointer
#define Cy_AudioI2S_EnableRxTestMode                      Cy_AudioTDM_EnableRxTestMode
#define Cy_AudioI2S_DisableRxTestMode                      Cy_AudioTDM_DisableRxTestMode

#define Cy_AudioI2S_ClearTxInterrupt                      Cy_AudioTDM_ClearTxInterrupt
#define Cy_AudioI2S_SetTxInterrupt                         Cy_AudioTDM_SetTxInterrupt
#define Cy_AudioI2S_GetTxInterruptMask                  Cy_AudioTDM_GetTxInterruptMask
#define Cy_AudioI2S_SetTxInterruptMask                  Cy_AudioTDM_SetTxInterruptMask
#define Cy_AudioI2S_GetTxInterruptStatusMasked          Cy_AudioTDM_GetTxInterruptStatusMasked
#define Cy_AudioI2S_SetTxTriggerInterruptMask           Cy_AudioTDM_SetTxTriggerInterruptMask
#define Cy_AudioI2S_ClearTxTriggerInterruptMask         Cy_AudioTDM_ClearTxTriggerInterruptMask

#define Cy_AudioI2S_ClearRxInterrupt                      Cy_AudioTDM_ClearRxInterrupt
#define Cy_AudioI2S_SetRxInterrupt                         Cy_AudioTDM_SetRxInterrupt
#define Cy_AudioI2S_GetRxInterruptMask                  Cy_AudioTDM_GetRxInterruptMask
#define Cy_AudioI2S_SetRxInterruptMask                  Cy_AudioTDM_SetRxInterruptMask
#define Cy_AudioI2S_GetRxInterruptStatusMasked          Cy_AudioTDM_GetRxInterruptStatusMasked
#define Cy_AudioI2S_SetRxTriggerInterruptMask           Cy_AudioTDM_SetRxTriggerInterruptMask
#define Cy_AudioI2S_ClearRxTriggerInterruptMask         Cy_AudioTDM_ClearRxTriggerInterruptMask

/** \endcond */

/** \} group_tdm_functions */

/**
* \addtogroup group_tdm_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_AudioTDM_EnableTx
****************************************************************************//**
*
* Starts an I2S/TDM transmission. Interrupt enabling (by the
* \ref Cy_AudioTDM_SetTxInterrupt) is required after this function call, in case
* if any I2S/TDM interrupts are used in the application.
*
* \pre Cy_AudioTDM_Init() must be called before.
*
* \param base The pointer to the I2S/TDM instance address.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_EnableTx
*******************************************************************************/

__STATIC_INLINE void Cy_AudioTDM_EnableTx( TDM_TX_STRUCT_Type * base)
{
    TDM_STRUCT_TX_CTL(base) |= TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_CTL_ENABLED_Msk;
}

/*******************************************************************************
* Function Name: Cy_AudioTDM_DisableTx
****************************************************************************//**
*
* Stops an I2S/TDM transmission.
*
* \pre TX interrupt disabling (by the \ref Cy_AudioTDM_SetTxInterrupt) is required
* prior to this function call, in case any TX I2S/TDM interrupts are used.
*
* \param base The pointer to the I2S/TDM instance address.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_DisableTx
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_DisableTx( TDM_TX_STRUCT_Type * base)
{
    TDM_STRUCT_TX_CTL(base) &= (uint32_t) ~TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_CTL_ENABLED_Msk;
}

/*******************************************************************************
* Function Name: Cy_AudioTDM_EnableRx
****************************************************************************//**
*
* Starts an I2S/TDM transmission. Interrupt enabling (by the
* \ref Cy_AudioTDM_SetRxInterrupt) is required after this function call, in case
* if any I2S/TDM interrupts are used in the application.
*
* \pre Cy_AudioTDM_Init() must be called before.
*
* \param base The pointer to the I2S/TDM instance address.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_EnableRx
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_EnableRx( TDM_RX_STRUCT_Type * base)
{
    TDM_STRUCT_RX_CTL(base) |= TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_CTL_ENABLED_Msk;
}

/*******************************************************************************
* Function Name: Cy_AudioTDM_DisableRx
****************************************************************************//**
*
* Stops an I2S/TDM transmission.
*
* \pre TX interrupt disabling (by the \ref Cy_AudioTDM_SetRxInterrupt) is required
* prior to this function call, in case any TX I2S/TDM interrupts are used.
*
* \param base The pointer to the I2S/TDM instance address.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_DisableRx
*******************************************************************************/

__STATIC_INLINE void Cy_AudioTDM_DisableRx( TDM_RX_STRUCT_Type * base)
{
    TDM_STRUCT_RX_CTL(base) &= (uint32_t) ~TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_CTL_ENABLED_Msk;
}

/*******************************************************************************
* Function Name: Cy_AudioTDM_WriteTxData
****************************************************************************//**
*
* Writes data to the TX FIFO. Increases the TX FIFO level.
*
* \param base The pointer to the I2S/TDM instance address.
*
* \param data Data to be written to the TX FIFO.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_WriteTxData
*******************************************************************************/

__STATIC_INLINE void Cy_AudioTDM_WriteTxData( TDM_TX_STRUCT_Type * base, uint32_t data)
{
    TDM_STRUCT_TX_FIFO_WR(base) = data;
}

/*******************************************************************************
* Function Name: Cy_AudioTDM_FreezeTxFifo
****************************************************************************//**
*
* Freezes the TX FIFO. This function is for debug purposes.
* HW uses a constant PCM data value of "0" or the previous channel PCM data is replayed.
* Freeze does not advance the FIFO read pointer (the FIFO data is not used).
*
* \param base The pointer to the I2S/TDM instance address.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_FreezeTxFifo
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_FreezeTxFifo( TDM_TX_STRUCT_Type * base)
{
    TDM_STRUCT_TX_FIFO_CTL(base) &= ~TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_CTL_FREEZE_Msk;
    TDM_STRUCT_TX_FIFO_CTL(base) &= ~TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_CTL_REPLAY_Msk;
    TDM_STRUCT_TX_FIFO_CTL(base) |= _BOOL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_CTL_FREEZE, 1U) |
                           _BOOL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_CTL_REPLAY, 0U);
}

/*******************************************************************************
* Function Name: Cy_AudioTDM_UnfreezeTxFifo
****************************************************************************//**
*
* Unfreezes the TX FIFO. This function is for debug purposes.
* HW uses TX FIFO data and advances the FIFO read pointer.
*
* \param base The pointer to the I2S/TDM instance address.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_UnFreezeTxFifo
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_UnfreezeTxFifo( TDM_TX_STRUCT_Type * base)
{
    TDM_STRUCT_TX_FIFO_CTL(base) &= ~TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_CTL_FREEZE_Msk;
    TDM_STRUCT_TX_FIFO_CTL(base) |= _BOOL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_CTL_FREEZE, 0U);
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_MuteTxFifo                                   */
/***************************************************************************//**
*
* Mutes the TX FIFO.
* HW uses a constant PCM data value of "0". Mute does advance the FIFO read pointer.
*
* \param base The pointer to the I2S/TDM instance address.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_MuteTxFifo
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_MuteTxFifo( TDM_TX_STRUCT_Type * base)
{
    TDM_STRUCT_TX_FIFO_CTL(base) &= ~TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_CTL_MUTE_Msk;
    TDM_STRUCT_TX_FIFO_CTL(base) |= _BOOL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_CTL_MUTE, 1U);
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_ActivateTx                                      */
/***************************************************************************//**
*
* Activate/start the TX FIFO.
* This will set the transmitter state to on.
*
* \param base The pointer to the I2S/TDM instance address.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_ActivateTx
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_ActivateTx( TDM_TX_STRUCT_Type * base)
{
    TDM_STRUCT_TX_FIFO_CTL(base) &= ~TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_CTL_ACTIVE_Msk;
    TDM_STRUCT_TX_FIFO_CTL(base) |= _BOOL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_CTL_ACTIVE, 1U);
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_DeActivateTx                                       */
/***************************************************************************//**
*
* Stop the TX FIFO.
* This will set the transmitter state to off.
*
* \param base The pointer to the I2S/TDM instance address.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_DeActivateTx
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_DeActivateTx( TDM_TX_STRUCT_Type * base)
{
    TDM_STRUCT_TX_FIFO_CTL(base) &= ~TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_CTL_ACTIVE_Msk;
    TDM_STRUCT_TX_FIFO_CTL(base) |= _BOOL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_CTL_ACTIVE, 0U);
}
/***************************************************************************/
/* Function Name: Cy_AudioTDM_ReplayTxFifo                           */
/***************************************************************************//**
*
* Replay functionality (used when FREEZE is '1' or in case of a FIFO underflow event).
* HW uses the previous PCM data value.
*
* \param base The pointer to the I2S/TDM instance address.
*
*******************************************************************************/
//data replay
__STATIC_INLINE void Cy_AudioTDM_ReplayTxFifo( TDM_TX_STRUCT_Type * base)
{
    TDM_STRUCT_TX_FIFO_CTL(base) &= ~TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_CTL_FREEZE_Msk;
    TDM_STRUCT_TX_FIFO_CTL(base) &= ~TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_CTL_REPLAY_Msk;
    TDM_STRUCT_TX_FIFO_CTL(base) |= _BOOL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_CTL_FREEZE, 1U) |
                           _BOOL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_CTL_REPLAY, 1U);
}
/***************************************************************************/
/* Function Name: Cy_AudioTDM_GetNumInTxFifo                               */
/***************************************************************************//**
*
* Gets the number of used words in the TX FIFO.,
* Number of used/occupied entries in the TX FIFO. The field value is in the range [0, 128].
* When "0", the FIFO is empty. When "128", the FIFO is full.
*
* \param base The pointer to the I2S/TDM instance address.
*
* \return The current number of used words in the TX FIFO.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_GetNumInTxFifo
*******************************************************************************/
__STATIC_INLINE uint8_t Cy_AudioTDM_GetNumInTxFifo( TDM_TX_STRUCT_Type * base)
{
    return ((uint8_t)(TDM_STRUCT_TX_FIFO_STATUS(base) & TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_STATUS_USED_Msk));
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_GetTxReadPointer                             */
/***************************************************************************//**
*
* Get the TX FIFO Read Pointer.
* TX FIFO read pointer: FIFO location from which a data is read.
* This functionality is intended for debugging purposes.
*
* \param base The pointer to the I2S/TDM instance address.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_GetTxReadPointer
*******************************************************************************/
__STATIC_INLINE uint8_t Cy_AudioTDM_GetTxReadPointer( TDM_TX_STRUCT_Type * base)
{
    uint32_t reg_value;
    reg_value = (TDM_STRUCT_TX_FIFO_STATUS(base) & TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_STATUS_RD_PTR_Msk);
    return ((uint8_t)(reg_value >> TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_STATUS_RD_PTR_Pos));
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_GetTxWritePointer                            */
/***************************************************************************//**
*
* Get the TX FIFO Write Pointer.
* TX FIFO write pointer: FIFO location at which a new data is written by the hardware.
* This functionality is intended for debugging purposes.
*
* \param base The pointer to the I2S/TDM instance address.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_GetTxWritePointer
*******************************************************************************/
__STATIC_INLINE uint8_t Cy_AudioTDM_GetTxWritePointer( TDM_TX_STRUCT_Type * base)
{
    uint32_t reg_value;
    reg_value = (TDM_STRUCT_TX_FIFO_STATUS(base) & TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_STATUS_WR_PTR_Msk);
    return ((uint8_t)(reg_value >> TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_FIFO_STATUS_WR_PTR_Pos));
}
/***************************************************************************/
/* Function Name: Cy_AudioTDM_EnableTxTestMode                            */
/***************************************************************************//**
*
* Enables the test mode. Used for debugging purposes only.
* Tx and Rx test modes cannot be enabled simultaneously.
*
* \param base The pointer to the I2S/TDM instance address.
*
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_EnableTxTestMode( TDM_TX_STRUCT_Type * base)
{
    TDM_STRUCT_TX_TEST_CTL(base) |= TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_TEST_CTL_ENABLED_Msk;
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_DisableTxTestMode                            */
/***************************************************************************//**
*
* Disables Test mode.
*
* \param base The pointer to the I2S/TDM instance address.
*
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_DisableTxTestMode( TDM_TX_STRUCT_Type * base)
{
    TDM_STRUCT_TX_TEST_CTL(base) &= (uint32_t) ~TDM_TDM_STRUCT_TDM_TX_STRUCT_TX_TEST_CTL_ENABLED_Msk;
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_ReadRxData                                   */
/***************************************************************************//**
*
* Read Rx data from the Rx FIFO.
* Data (PCM sample) read from the RX FIFO. Reading removes the data from the RX FIFO.
* Reading from an empty RX FIFO activates FIFO_UNDERFLOW interrupt.
*
* \param base The pointer to the I2S/TDM instance address.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_ReadRxData
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_AudioTDM_ReadRxData( TDM_RX_STRUCT_Type * base)
{
    return (TDM_STRUCT_RX_FIFO_RD(base));
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_FreezeRxFifo                                 */
/***************************************************************************//**
*
* Freeze RX FIFO.
* HW writes from the RX FIFO have no effect: freeze will not advance the FIFO write pointer.
* This functionality is intended for debugging purposes.
*
* \param base The pointer to the I2S/TDM instance address.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_FreezeRxFifo
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_FreezeRxFifo( TDM_RX_STRUCT_Type * base)
{
    TDM_STRUCT_RX_FIFO_CTL(base) &= ~TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_FIFO_CTL_FREEZE_Msk;
    TDM_STRUCT_RX_FIFO_CTL(base) |= _BOOL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_FIFO_CTL_FREEZE, 1U);
}
/***************************************************************************/
/* Function Name: Cy_AudioTDM_UnfreezeRxFifo                               */
/***************************************************************************//**
*
* UnFreeze Rx FIFO.
* HW writes to the RX FIFO and advances the FIFO write pointer.
*
* \param base The pointer to the I2S/TDM instance address.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_UnfreezeRxFifo
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_UnfreezeRxFifo( TDM_RX_STRUCT_Type * base)
{
    TDM_STRUCT_RX_FIFO_CTL(base) &= ~TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_FIFO_CTL_FREEZE_Msk;
    TDM_STRUCT_RX_FIFO_CTL(base) |= _BOOL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_FIFO_CTL_FREEZE, 0U);
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_ActivateRx                                      */
/***************************************************************************//**
*
* Start Rx FIFO.
* Sets Receiver state to on.
*
* \param base The pointer to the I2S/TDM instance address.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_ActivateRx
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_ActivateRx( TDM_RX_STRUCT_Type * base)
{
    TDM_STRUCT_RX_FIFO_CTL(base) |= TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_FIFO_CTL_ACTIVE_Msk;
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_DeActivateRx                                       */
/***************************************************************************//**
*
* Stop Rx FIFO.
* Sets Receiver state to off.
*
* \param base The pointer to the I2S/TDM instance address.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_DeActivateRx
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_DeActivateRx( TDM_RX_STRUCT_Type * base)
{
    TDM_STRUCT_RX_FIFO_CTL(base) &= ~TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_FIFO_CTL_ACTIVE_Msk;
    TDM_STRUCT_RX_FIFO_CTL(base) |= _BOOL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_FIFO_CTL_ACTIVE, 0U);
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_ReadSilentRXFifo                             */
/***************************************************************************//**
*
* When the RX FIFO is empty, a read from this register returns "0".
*
* \param base The pointer to the I2S/TDM instance address.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_ReadSilentRXFifo
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_AudioTDM_ReadSilentRXFifo( TDM_RX_STRUCT_Type * base)
{
    return (TDM_STRUCT_RX_FIFO_RD_SILENT(base));
}
/***************************************************************************/
/* Function Name: Cy_AudioTDM_GetNumInRxFifo                               */
/***************************************************************************//**
*
* Reads RX FIFO status.
* Number of used/occupied entries in the RX FIFO. The field value is in the range [0, 128].
* When "0", the FIFO is empty. When "128", the FIFO is full.
*
* \param base The pointer to the I2S/TDM instance address.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_GetNumInRxFifo
*******************************************************************************/
__STATIC_INLINE uint8_t Cy_AudioTDM_GetNumInRxFifo( TDM_RX_STRUCT_Type * base)
{
    return ((uint8_t)(TDM_STRUCT_RX_FIFO_STATUS(base) & TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_FIFO_STATUS_USED_Msk));
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_GetRxReadPointer                            */
/***************************************************************************//**
*
* Reads RX FIFO Read Pointer
* RX FIFO read pointer: FIFO location from which a data is read.
* This functionality is intended for debugging purposes.
*
* \param base The pointer to the I2S/TDM instance address.
*
* \return The current RX Read pointer value.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_GetRxReadPointer
*******************************************************************************/
__STATIC_INLINE uint8_t Cy_AudioTDM_GetRxReadPointer( TDM_RX_STRUCT_Type * base)
{
    uint32_t reg_value;
    reg_value = (TDM_STRUCT_RX_FIFO_STATUS(base) & TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_FIFO_STATUS_RD_PTR_Msk);
    return ((uint8_t)(reg_value >> TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_FIFO_STATUS_RD_PTR_Pos));
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_GetRxWritePointer                            */
/***************************************************************************//**
*
* Reads RX FIFO Write Pointer
* RX FIFO write pointer: FIFO location at which a new data is written by the hardware.
* This functionality is intended for debugging purposes.
*
* \param base The pointer to the I2S/TDM instance address.
*
* \return The current RX Write pointer value.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_GetRxWritePointer
*******************************************************************************/
__STATIC_INLINE uint8_t Cy_AudioTDM_GetRxWritePointer( TDM_RX_STRUCT_Type * base)
{
    uint32_t reg_value;
    reg_value = (TDM_STRUCT_RX_FIFO_STATUS(base) & TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_FIFO_STATUS_WR_PTR_Msk);
    return ((uint8_t)(reg_value >> TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_FIFO_STATUS_WR_PTR_Pos));
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_EnableRxTestMode                             */
/***************************************************************************//**
*
* Enables Test mode (intended to be used with (master transmitter, slave receiver) configuration).
* Both TX and RX should not be set in Test mode simultaneously.
*
* \param base The pointer to the I2S/TDM instance address.
*
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_EnableRxTestMode( TDM_RX_STRUCT_Type * base)
{
    TDM_STRUCT_RX_TEST_CTL(base) |= TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_TEST_CTL_ENABLED_Msk;
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_DisableRxTestMode                            */
/***************************************************************************//**
*
* Disable RX test mode
*
* \param base The pointer to the I2S/TDM instance address.
*
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_DisableRxTestMode( TDM_RX_STRUCT_Type * base)
{
    TDM_STRUCT_RX_TEST_CTL(base) &= ~TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_TEST_CTL_ENABLED_Msk;
    TDM_STRUCT_RX_TEST_CTL(base) |= _BOOL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_RX_TEST_CTL_ENABLED, 0U);
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_ClearTxInterrupt                             */
/***************************************************************************//**
*
* Clear TX interrupt
*
* \param base The pointer to the I2S/TDM instance address.
* \param interrupt interrupt
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_ClearTxInterrupt
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_ClearTxInterrupt( TDM_TX_STRUCT_Type * base, uint32_t interrupt)
{
    CY_ASSERT_L2(CY_I2S_TDM_INTR_TX_MASK_VALID(interrupt));

    TDM_STRUCT_TX_INTR_TX(base) = interrupt;
    (void) TDM_STRUCT_TX_INTR_TX(base);
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_SetTxInterrupt                               */
/***************************************************************************//**
*
* Set the Tx Interrupt
*
* \param base The pointer to the I2S/TDM instance address.
* \param interrupt interrupts to set.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_SetTxInterrupt
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_SetTxInterrupt( TDM_TX_STRUCT_Type * base, uint32_t interrupt)
{
    CY_ASSERT_L2(CY_I2S_TDM_INTR_TX_MASK_VALID(interrupt));

    TDM_STRUCT_TX_INTR_TX_SET(base) = interrupt;
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_GetTxInterruptMask                             */
/***************************************************************************//**
*
* Get TX interrupt Mask
*
* \param base The pointer to the I2S/TDM instance address.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_GetTxInterruptMask
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_AudioTDM_GetTxInterruptMask( TDM_TX_STRUCT_Type * base)
{
    return (TDM_STRUCT_TX_INTR_TX_MASK(base));
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_SetTxInterruptMask                             */
/***************************************************************************//**
*
* Set TX interrupt Mask
*
* \param base The pointer to the I2S/TDM instance address.
* \param interrupt interrupt
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_SetTxInterruptMask
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_SetTxInterruptMask( TDM_TX_STRUCT_Type * base, uint32_t interrupt)
{
    CY_ASSERT_L2(CY_I2S_TDM_INTR_TX_MASK_VALID(interrupt));

    TDM_STRUCT_TX_INTR_TX_MASK(base) = interrupt;
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_GetTxInterruptStatusMasked                   */
/***************************************************************************//**
*
*  Reflects a bitwise AND between the INTR_TX and INTR_TX_MASK registers.
*
* \param base The pointer to the I2S/TDM instance address.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_AudioTDM_GetTxInterruptStatusMasked( TDM_TX_STRUCT_Type * base)
{
    return (TDM_STRUCT_TX_INTR_TX_MASKED(base));
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_SetTxTriggerInterruptMask                     */
/***************************************************************************//**
*
* Sets TX interrupt Mask
*
* \param base The pointer to the I2S/TDM instance address.
*
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_SetTxTriggerInterruptMask( TDM_TX_STRUCT_Type * base)
{
    TDM_STRUCT_TX_INTR_TX_MASK(base) |= TDM_TDM_STRUCT_TDM_TX_STRUCT_INTR_TX_MASK_FIFO_TRIGGER_Msk;
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_ClearTxTriggerInterruptMask                  */
/***************************************************************************//**
*
*  Clears TX interrupt Mask
*
* \param base The pointer to the I2S/TDM instance address.
*
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_ClearTxTriggerInterruptMask( TDM_TX_STRUCT_Type * base)
{
    TDM_STRUCT_TX_INTR_TX_MASK(base) &= ~TDM_TDM_STRUCT_TDM_TX_STRUCT_INTR_TX_MASK_FIFO_TRIGGER_Msk;
    TDM_STRUCT_TX_INTR_TX_MASK(base) |= _BOOL2FLD(TDM_TDM_STRUCT_TDM_TX_STRUCT_INTR_TX_MASK_FIFO_TRIGGER, 0U);
}
/***************************************************************************/
/* Function Name: Cy_AudioTDM_ClearRxInterrupt                             */
/***************************************************************************//**
*
*  Clears RX interrupt
*
* \param base The pointer to the I2S/TDM instance address.
* \param interrupt interrupt
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_ClearRxInterrupt
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_ClearRxInterrupt( TDM_RX_STRUCT_Type * base, uint32_t interrupt)
{
    CY_ASSERT_L2(CY_I2S_TDM_INTR_RX_MASK_VALID(interrupt));

    TDM_STRUCT_RX_INTR_RX(base) = interrupt;
    (void) TDM_STRUCT_RX_INTR_RX(base);

}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_SetRxInterrupt                               */
/***************************************************************************//**
*
*  Sets RX interrupt
*
* \param base The pointer to the I2S/TDM instance address.
* \param interrupt interrupt
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_SetRxInterrupt
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_SetRxInterrupt( TDM_RX_STRUCT_Type * base, uint32_t interrupt)
{
    CY_ASSERT_L2(CY_I2S_TDM_INTR_RX_MASK_VALID(interrupt));

    TDM_STRUCT_RX_INTR_RX_SET(base) = interrupt;
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_GetRxInterruptMask                           */
/***************************************************************************//**
*
* Returns RX interrupt Mask
*
* \param base The pointer to the I2S/TDM instance address.
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_GetRxInterruptMask
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_AudioTDM_GetRxInterruptMask( TDM_RX_STRUCT_Type * base)
{
    return (TDM_STRUCT_RX_INTR_RX_MASK(base));
}
/***************************************************************************/
/* Function Name: Cy_AudioTDM_SetRxInterruptMask                             */
/***************************************************************************//**
*
* Sets RX interrupt Mask
*
* \param base The pointer to the I2S/TDM instance address.
* \param interrupt interrupt
*
* \funcusage
* \snippet tdm/snippet/main.c snippet_Cy_AudioTDM_SetRxInterruptMask
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_SetRxInterruptMask( TDM_RX_STRUCT_Type * base, uint32_t interrupt)
{
    CY_ASSERT_L2(CY_I2S_TDM_INTR_RX_MASK_VALID(interrupt));

    TDM_STRUCT_RX_INTR_RX_MASK(base) = interrupt;
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_GetRxInterruptStatusMasked                  */
/***************************************************************************//**
*
* Returns  a bitwise AND between the INTR_RX and INTR_RX_MASK registers
*
* \param base The pointer to the I2S/TDM instance address.
*
* \return The interrupt bit mask(s).
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_AudioTDM_GetRxInterruptStatusMasked( TDM_RX_STRUCT_Type * base)
{
    return (TDM_STRUCT_RX_INTR_RX_MASKED(base));
}
/***************************************************************************/
/* Function Name: Cy_AudioTDM_SetRxTriggerInterruptMask                   */
/***************************************************************************//**
*
* Sets Rx Interrupt Mask
*
* \param base The pointer to the I2S/TDM instance address.
*
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_SetRxTriggerInterruptMask( TDM_RX_STRUCT_Type * base)
{
    TDM_STRUCT_RX_INTR_RX_MASK(base) |= TDM_TDM_STRUCT_TDM_RX_STRUCT_INTR_RX_MASK_FIFO_TRIGGER_Msk;
}

/***************************************************************************/
/* Function Name: Cy_AudioTDM_ClearRxTriggerInterruptMask                  */
/***************************************************************************//**
*
* Clear RX interrupt Mask
*
* \param base The pointer to the I2S/TDM instance address.
*
*******************************************************************************/
__STATIC_INLINE void Cy_AudioTDM_ClearRxTriggerInterruptMask( TDM_RX_STRUCT_Type * base)
{
    TDM_STRUCT_RX_INTR_RX_MASK(base) &= ~TDM_TDM_STRUCT_TDM_RX_STRUCT_INTR_RX_MASK_FIFO_TRIGGER_Msk;
    TDM_STRUCT_RX_INTR_RX_MASK(base) |= _BOOL2FLD(TDM_TDM_STRUCT_TDM_RX_STRUCT_INTR_RX_MASK_FIFO_TRIGGER, 0U);
}

/** \} group_tdm_functions */


#if defined(__cplusplus)
}
#endif

#endif  /* (CY_TDM_H) */

/** \} group_tdm */

CY_MISRA_BLOCK_END('MISRA C-2012 Rule 10.1');

CY_MISRA_BLOCK_END('MISRA C-2012 Rule 14.3');

#endif /* CY_IP_MXTDM */
/* [] END OF FILE */
