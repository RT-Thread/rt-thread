/**
 * Copyright (c) 2016 - 2017 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 * 
 * All Rights Reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
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
#ifndef PHY_COMMON_H_INCLUDED
#define PHY_COMMON_H_INCLUDED

/** @file
 * This file contains declarations of commonly used PHY routines and necessary macros/types.
 *
 * @defgroup phy_common PHY Common API
 * @{
 * @brief Module to declare PHY Common API
 */

/**@brief   The maximum PSDU size (in octets) the PHY shall be able to receive (aMaxPHYPacketSize).
 *
 * @details See Table 22 - PHY constants.
 */
#define PHY_MAX_PACKET_SIZE     127


/**@brief   The maximum PHR size (in octets).
 *
 * @details See 6.3 PPDU format.
 */
#define PHY_MAX_HEADER_SIZE       1

/**@brief Maximum PPDU size */
#define PHY_MAX_PPDU_SIZE       (PHY_MAX_HEADER_SIZE + PHY_MAX_PACKET_SIZE)

/**@brief Position of PHY header related to income PPDU start pointer.*/
#define PHY_HEADER_POS          (-1)

/**@brief Size of PHY header in bytes.*/
#define PHY_HEADER_SIZE          1

/**@brief Maximum channel number.*/
#define PHY_MAX_CHANNEL_NUM      0x1A

/**@brief Minimum channel number.*/
#define PHY_MIN_CHANNEL_NUM      0x0B

// for 2400 MHz O-QPSK 1 octet = 2 symbols  1 symbol = 32bits chip
#define aMaxPHYPacketSize        PHY_MAX_PACKET_SIZE    // in octets
#define aTurnaroundTime          12     // in symbols

#define aTurnaroundTimeUs        192    // in us


// Read only parameters
#define PHY_CURRENT_PAGE         0x0u
#define PHY_CHANNEL_SUPPORTED    0x07FFF800ul
#define PHY_SHR_DURATION         10u
#define PHY_MAX_FRAME_DURATION  (PHY_SHR_DURATION + (int)((aMaxPHYPacketSize + 1) * PHY_SYMBOLS_PER_OCTET))
#define PHY_SYMBOLS_PER_OCTET    2u

// CCA values
#define PHY_TRX_CCA_MODE0            0
#define PHY_TRX_CCA_MODE1            1
#define PHY_TRX_CCA_MODE2            2
#define PHY_TRX_CCA_MODE3            3


/** @brief Minimum value that can be used to set radio transmit power. Equals
 * to -32 dBm.
 *
 * This is a combination of digits which includes:
 * 2 MSBs represent the tolerance on the transmit power
 * 6 LSBs which may be written to, represent a signed integer in twos-complement format,
 * corresponding to the nominal transmit power of the device in decibels relative to 1 mW.
 * All combinations less than 0xBF are valid.
 */
#define PHY_MIN_TX_POWER                   0x20

/** @brief Internal parameter of the PHY layer.
 *
 * @details Position of the sign bit inside transmit power attribute.*/
#define PHY_TRANSMIT_POWER_SIGN_BIT_POS    5

/** @brief Internal parameter of the PHY layer.
 *
 * @details This mask hides transmit power from transmit power attribute value,
 * but leaves precision bitfield.
 */
#define PHY_TRANSMIT_POWER_MASK            0xC0

/** @brief Internal parameter of the PHY layer.
 *
 * @details This mask hides precision bitfield from transmit power attribute value,
 * leaving transmit power unchanged.
 */
#define PHY_TRANSMIT_POWER_MASK_INV        0x3F

// Possible transmit power
#define DBM_11     (  11  & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_10     (  10  & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_9      (   9  & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_8      (   8  & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_7      (   7  & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_6      (   6  & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_5      (   5  & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_4      (   4  & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_3      (   3  & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_2      (   2  & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_1      (   1  & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_0      (   0  & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_1  (( -1) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_2  (( -2) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_3  (( -3) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_4  (( -4) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_5  (( -5) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_6  (( -6) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_7  (( -7) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_8  (( -8) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_9  (( -9) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_10 ((-10) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_11 ((-11) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_12 ((-12) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_13 ((-13) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_14 ((-14) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_15 ((-15) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_16 ((-16) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_17 ((-17) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_18 ((-18) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_19 ((-19) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_20 ((-20) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_21 ((-21) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_22 ((-22) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_23 ((-23) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_24 ((-24) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_25 ((-25) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_26 ((-26) & PHY_TRANSMIT_POWER_MASK_INV)
#define DBM_MIN_27 ((-27) & PHY_TRANSMIT_POWER_MASK_INV)


/**@brief   Common PHY enumerations description used in various PHY primitives.
 *
 * @details See Table 18-PHY enumerations description for detailed info on the statuses up to PHY_READ_ONLY.
 * The statuses with higher numbers are implementation specific and used for synchronous API only.
 */
typedef enum
{
    /** The CCA attempt has detected a busy channel. */
    PHY_BUSY                    = 0x00,

    /** The transceiver is asked to change its state while receiving. */
    PHY_BUSY_RX                 = 0x01,

    /** The transceiver is asked to change its state while transmitting. */
    PHY_BUSY_TX                 = 0x02,

    /** The transceiver is to be switched off immediately. */
    PHY_FORCE_TRX_OFF           = 0x03,

    /** The CCA attempt has detected an idle channel. */
    PHY_IDLE                    = 0x04,

    /** A SET/GET request was issued with a parameter in the primitive that is
        out of the valid range. */
    PHY_INVALID_PARAMETER       = 0x05,

    /** The transceiver is in or is to be configured into the receiver enabled state. */
    PHY_RX_ON                   = 0x06,

    /** A SET/GET, an ED operation, or a transceiver state change was successful. */
    PHY_SUCCESS                 = 0x07,

    /** The transceiver is in or is to be configured into the transceiver disabled state. */
    PHY_TRX_OFF                 = 0x08,

    /** The transceiver is in or is to be configured into the transmitter enabled state. */
    PHY_TX_ON                   = 0x09,

    /** A SET/GET request was issued with the identifier of an attribute that is not supported. */
    PHY_UNSUPPORTED_ATTRIBUTE   = 0x0A,

    /** A SET/GET request was issued with the identifier of an attribute that is read-only.*/
    PHY_READ_ONLY               = 0x0B,


    /* Statuses out of the standard. They are used for synchronous API */
    /** Transceiver is forced to change it's state to PHY_TX_ON (potential packet drop). */
    PHY_FORCE_TX_ON             = 0xFB,

    /** Data with ACK request transmitted successfully
     * and pending bit in received ACK is set to one.
     */
    PHY_SUCCESS_DATA_PENDING    = 0xFC,

    /** Data cannot be sent due to failed CCA results.*/
    PHY_CHANNEL_ACCESS_FAILURE  = 0xFD,

    /** Data had been sent but ACK frame hasn't been received.*/
    PHY_NO_ACK                  = 0xFE,

    /** PHY is not available for synchronous access */
    PHY_IS_NOT_AVAILABLE        = 0xFF
} phy_enum_t;

/**@brief PHY status type.*/
typedef phy_enum_t  phy_status_t;

/** @} */

#endif // PHY_COMMON_H_INCLUDED
