/**
 * Copyright (c) 2011 - 2018, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/**
 * @file
 * @brief Gazell Link Layer constants and default values.
 *
 * NOTE! Changing values here has no effect. They are only provided as a reference.
 */

#ifndef NRF_GZLL_CONSTANTS_H__
#define NRF_GZLL_CONSTANTS_H__

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @addtogroup gzll_02_api
 * @{
 */


/*****************************************************************************/
/** @name Hardware resources used by Gazell */
/*****************************************************************************/
#define NRF_GZLL_HIGH_IRQ_PRIORITY  0                               ///< Interrupt priority the Gazell timer and the radio
#define NRF_GZLL_LOW_IRQ_PRIORITY   1                               ///< Interrupt priority for Gazell callback functions.

#ifndef USE_SD_HW_RESOURCES

#define NRF_GZLL_SWI_IRQn           SWI0_IRQn                       ///< Software interrupt # used for callback functions.
#define NRF_GZLL_SWI_IRQ_HANDLER    SWI0_IRQHandler                 ///< Software interrupt handler used for callback functions.
#define NRF_GZLL_TIMER              NRF_TIMER2                      ///< Timer to be used as flywheel timer.
#define NRF_GZLL_TIMER_IRQn         TIMER2_IRQn                     ///< Interrupt # for the timer.
#define NRF_GZLL_TIMER_IRQ_HANDLER  TIMER2_IRQHandler               ///< Interrupt handler for the timer.

// In addition, Gazell uses the radio peripheral and radio interrupts.

/*
 * PPI configuration
 */
#define NRF_GZLL_PPI_EEP0 (NRF_PPI->CH0_EEP)                        ///< Gazell PPI event endpoint 0
#define NRF_GZLL_PPI_TEP0 (NRF_PPI->CH0_TEP)                        ///< Gazell PPI task endpoint 0
#define NRF_GZLL_PPI_EEP1 (NRF_PPI->CH1_EEP)                        ///< Gazell PPI event endpoint 1
#define NRF_GZLL_PPI_TEP1 (NRF_PPI->CH1_TEP)                        ///< Gazell PPI task endpoint 1
#define NRF_GZLL_PPI_EEP2 (NRF_PPI->CH2_EEP)                        ///< Gazell PPI event endpoint 2
#define NRF_GZLL_PPI_TEP2 (NRF_PPI->CH2_TEP)                        ///< Gazell PPI task endpoint 2

#define NRF_GZLL_PPI_CHEN_MSK_0_AND_1 (0x03)                        ///< Channel enable/disable mask for PPI endpoint 0 and 1.
#define NRF_GZLL_PPI_CHEN_MSK_2       (0x04)                        ///< Channel enable/disable mask for PPI endpoint 2.

#else

#define NRF_GZLL_SWI_IRQn           SWI1_IRQn                       ///< Software interrupt # used for callback functions.
#define NRF_GZLL_SWI_IRQ_HANDLER    SWI1_IRQHandler                 ///< Software interrupt handler used for callback functions.
#define NRF_GZLL_TIMER              NRF_TIMER0                      ///< Timer to be used as flywheel timer.
#define NRF_GZLL_TIMER_PERPOWER_Msk POWER_PERPOWER_TIMER0_Msk       ///< PERPOWER mask for the timer.
#define NRF_GZLL_TIMER_IRQn         TIMER0_IRQn                     ///< Interrupt # for the timer.
#define NRF_GZLL_TIMER_IRQ_HANDLER  TIMER0_IRQHandler               ///< Interrupt handler for the timer.

// In addition, Gazell uses the radio peripheral and radio interrupts.

/*
 * PPI configuration
 */
#define NRF_GZLL_PPI_EEP0 (NRF_PPI->CH8_EEP)                        ///< Gazell PPI event endpoint 0
#define NRF_GZLL_PPI_TEP0 (NRF_PPI->CH8_TEP)                        ///< Gazell PPI task endpoint 0
#define NRF_GZLL_PPI_EEP1 (NRF_PPI->CH9_EEP)                        ///< Gazell PPI event endpoint 1
#define NRF_GZLL_PPI_TEP1 (NRF_PPI->CH9_TEP)                        ///< Gazell PPI task endpoint 1
#define NRF_GZLL_PPI_EEP2 (NRF_PPI->CH10_EEP)                       ///< Gazell PPI event endpoint 2
#define NRF_GZLL_PPI_TEP2 (NRF_PPI->CH10_TEP)                       ///< Gazell PPI task endpoint 2

#define NRF_GZLL_PPI_CHEN_MSK_0_AND_1 (0x300)                       ///< Channel enable/disable mask for PPI endpoint 0 and 1.
#define NRF_GZLL_PPI_CHEN_MSK_2       (0x400)                       ///< Channel enable/disable mask for PPI endpoint 2.

#endif
/** @} */

/*****************************************************************************/
/** @name Constant pipe and FIFO configuration */
/*****************************************************************************/
#define NRF_GZLL_CONST_PIPE_COUNT            8                      ///< Number of TX pipes (at least one for each Device-Host pairs).
#define NRF_GZLL_CONST_FIFO_LENGTH           3                      ///< Maximum number of packets allowed in a TX or RX FIFO.
#define NRF_GZLL_CONST_MAX_TOTAL_PACKETS     6                      ///< Maximum number of packets available for reservation at any one time.
#define NRF_GZLL_CONST_MAX_PAYLOAD_LENGTH    32                     ///< Maximum allowed payload length in bytes.
#define NRF_GZLL_CONST_CALLBACK_QUEUE_LENGTH 10                     ///< Maximum number of notifications allowed in the callback queue.
/** @} */

/*****************************************************************************/
/** @name Default radio configuration */
/*****************************************************************************/
#define NRF_GZLL_DEFAULT_TX_POWER NRF_GZLL_TX_POWER_0_DBM           ///< Default TX power.
#define NRF_GZLL_DEFAULT_DATARATE NRF_GZLL_DATARATE_2MBIT           ///< Default data rate.

#define NRF_GZLL_DEFAULT_CHANNEL_TABLE        {4, 25, 42, 63, 77}   ///< Default channel table.
#define NRF_GZLL_DEFAULT_CHANNEL_TABLE_SIZE   5                     ///< Default channel table size.
#define NRF_GZLL_CONST_MAX_CHANNEL_TABLE_SIZE 16                    ///< Maximum channel table size allowed by Gazell.
/** @} */

/*****************************************************************************/
/** @name Default Address configuration */
/*****************************************************************************/

/*
Corresponds to Legacy nRFgo SDK Gazell config:
#define GZLL_DEFAULT_ADDRESS_PIPE0 {0x01, 0x04, 0x07, 0x0A, 0x0D}
#define GZLL_DEFAULT_ADDRESS_PIPE1 {0x02, 0x05, 0x08, 0x0B, 0x0E}
#define GZLL_DEFAULT_ADDRESS_PIPE2 3
#define GZLL_DEFAULT_ADDRESS_PIPE3 4
#define GZLL_DEFAULT_ADDRESS_PIPE4 5
#define GZLL_DEFAULT_ADDRESS_PIPE5 6
*/

#define NRF_GZLL_DEFAULT_FULL_ADDRESS_PIPE0  {0x01, 0x04, 0x07, 0x0A, 0x0D}   ///< Corresponding legacy Gazell pipe 0 address.
#define NRF_GZLL_DEFAULT_BASE_ADDRESS_0      0x0D0A0704                       ///< Default base address 0.
#define NRF_GZLL_DEFAULT_BASE_ADDRESS_1      0x0E0B0805                       ///< Default base address 1.
#define NRF_GZLL_DEFAULT_PREFIX_BYTE_0       1                                ///< Default prefix address pipe 0.
#define NRF_GZLL_DEFAULT_PREFIX_BYTE_1       2                                ///< Default prefix address pipe 1.
#define NRF_GZLL_DEFAULT_PREFIX_BYTE_2       3                                ///< Default prefix address pipe 2.
#define NRF_GZLL_DEFAULT_PREFIX_BYTE_3       4                                ///< Default prefix address pipe 3.
#define NRF_GZLL_DEFAULT_PREFIX_BYTE_4       5                                ///< Default prefix address pipe 4.
#define NRF_GZLL_DEFAULT_PREFIX_BYTE_5       6                                ///< Default prefix address pipe 5.
#define NRF_GZLL_DEFAULT_PREFIX_BYTE_6       7                                ///< Default prefix address pipe 6.
#define NRF_GZLL_DEFAULT_PREFIX_BYTE_7       8                                ///< Default prefix address pipe 7.
#define NRF_GZLL_DEFAULT_BASE_ADDRESS_LENGTH NRF_GZLL_BASE_ADDRESS_LENGTH_4B  ///< Default on-air base address length.
#define NRF_GZLL_DEFAULT_RX_PIPES_ENABLED    0x000000FF                       ///< Enabled Rx pipes. See nrf_gzll_set_rx_pipes_enabled().
/** @} */

/*****************************************************************************/
/** @name Default timeslot and synchronization configuration */
/*****************************************************************************/
#define NRF_GZLL_DEFAULT_TIMESLOT_PERIOD                 600                                                      ///< Default timeslot period.
#define NRF_GZLL_DEFAULT_TIMESLOTS_PER_CHANNEL           2                                                        ///< Timeslots use by the Host and by the Device when communication is in sync.
#define NRF_GZLL_DEFAULT_DEVICE_CHANNEL_SELECTION_POLICY NRF_GZLL_DEVICE_CHANNEL_SELECTION_POLICY_USE_SUCCESSFUL  ///< Default channel Gazell Device channel selection policy
#define NRF_GZLL_DEFAULT_MAX_TX_ATTEMPTS                 0                                                        ///< Default maximum TX attempts for each packet. A value of zero implies the infinite number of TX attempts.
#define NRF_GZLL_DEFAULT_XOSC_CTL                        NRF_GZLL_XOSC_CTL_AUTO                                   ///< Deafult setting for controlling the XOSC
#define NRF_GZLL_DEFAULT_TIMESLOTS_PER_CHANNEL_WHEN_DEVICE_OUT_OF_SYNC  15                                        ///< Timeslots use by the Device before communication is in sync.
#define NRF_GZLL_DEFAULT_SYNC_LIFETIME (3 * NRF_GZLL_DEFAULT_CHANNEL_TABLE_SIZE * NRF_GZLL_DEFAULT_TIMESLOTS_PER_CHANNEL) ///< Number of timeslots to keep the timer running so that communication remains synchronized.
/** @} */

#define NRF_GZLL_PA_LNA_MAX_RAMP_UP_TIME    129                               ///< Max external front end ramp up time [us].
#define NRF_GZLL_PA_LNA_PPI_CHANNELS_NUM    4                                 ///< Number of PPI channels used for front end control.

/** @} */

#ifdef __cplusplus
}
#endif

#endif
