/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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
#ifndef APP_USBD_CDC_TYPES_H__
#define APP_USBD_CDC_TYPES_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @defgroup app_usbd_cdc_types CDC class types
 * @ingroup app_usbd_cdc_acm
 *
 * @brief @tagAPI52840 Variable types used by the CDC class implementation.
 * @{
 */

/**
 * @brief Communications Interface Class code.
 *
 * Used for control interface in communication class.
 * @ref app_usbd_descriptor_iface_t::bInterfaceClass
 */
#define APP_USBD_CDC_COMM_CLASS 0x02

/**
 * @brief Data Class Interface code.
 *
 * Used for data interface in communication class.
 * @ref app_usbd_descriptor_iface_t::bInterfaceClass
 */
#define APP_USBD_CDC_DATA_CLASS 0x0A

/**
 * @brief CDC subclass possible values.
 *
 * @ref app_usbd_descriptor_iface_t::bInterfaceSubClass
 */
typedef enum {
    APP_USBD_CDC_SUBCLASS_RESERVED = 0x00, /**< Reserved in documentation.         */
    APP_USBD_CDC_SUBCLASS_DLCM     = 0x01, /**< Direct Line Control Model.         */
    APP_USBD_CDC_SUBCLASS_ACM      = 0x02, /**< Abstract Control Model.            */
    APP_USBD_CDC_SUBCLASS_TCM      = 0x03, /**< Telephone Control Model.           */
    APP_USBD_CDC_SUBCLASS_MCCM     = 0x04, /**< Multi-Channel Control Model.       */
    APP_USBD_CDC_SUBCLASS_CAPI     = 0x05, /**< CAPI Control Model.                */
    APP_USBD_CDC_SUBCLASS_ENCM     = 0x06, /**< Ethernet Networking Control Model. */
    APP_USBD_CDC_SUBCLASS_ATM      = 0x07, /**< ATM Networking Control Model.      */
    APP_USBD_CDC_SUBCLASS_WHCM     = 0x08, /**< Wireless Handset Control Model.    */
    APP_USBD_CDC_SUBCLASS_DM       = 0x09, /**< Device Management.                 */
    APP_USBD_CDC_SUBCLASS_MDLM     = 0x0A, /**< Mobile Direct Line Model.          */
    APP_USBD_CDC_SUBCLASS_OBEX     = 0x0B, /**< OBEX.                              */
    APP_USBD_CDC_SUBCLASS_EEM      = 0x0C, /**< Ethernet Emulation Model.          */
    APP_USBD_CDC_SUBCLASS_NCM      = 0x0D  /**< Network Control Model.             */
} app_usbd_cdc_subclass_t;

/**
 * @brief CDC protocol possible values.
 *
 * @ref app_usbd_descriptor_iface_t::bInterfaceProtocol
 */
typedef enum {
    APP_USBD_CDC_COMM_PROTOCOL_NONE              = 0x00, /**< No class specific protocol required.                                      */
    APP_USBD_CDC_COMM_PROTOCOL_AT_V250           = 0x01, /**< AT Commands: V.250 etc.                                                   */
    APP_USBD_CDC_COMM_PROTOCOL_AT_PCCA101        = 0x02, /**< AT Commands defined by PCCA-101.                                          */
    APP_USBD_CDC_COMM_PROTOCOL_AT_PCCA101_ANNEXO = 0x03, /**< AT Commands defined by PCCA-101 & Annex O.                                */
    APP_USBD_CDC_COMM_PROTOCOL_AT_GSM707         = 0x04, /**< AT Commands defined by GSM 07.07.                                         */
    APP_USBD_CDC_COMM_PROTOCOL_AT_3GPP_27007     = 0x05, /**< AT Commands defined by 3GPP 27.007.                                       */
    APP_USBD_CDC_COMM_PROTOCOL_AT_CDMA           = 0x06, /**< AT Commands defined by TIA for CDMA.                                      */
    APP_USBD_CDC_COMM_PROTOCOL_EEM               = 0x07, /**< Ethernet Emulation Model.                                                 */
    APP_USBD_CDC_COMM_PROTOCOL_EXTERNAL          = 0xFE, /**< External Protocol: Commands defined by Command Set Functional Descriptor. */
    APP_USBD_CDC_COMM_PROTOCOL_VENDOR            = 0xFF  /**< Vendor-specific.                                                          */
} app_usbd_cdc_comm_protocol_t;

/**
 * @brief CDC data interface protocols possible values.
 */
typedef enum {
    APP_USBD_CDC_DATA_PROTOCOL_NONE        = 0x00, /**< No class specific protocol required.                   */
    APP_USBD_CDC_DATA_PROTOCOL_NTB         = 0x01, /**< Network Transfer Block.                                */
    APP_USBD_CDC_DATA_PROTOCOL_ISDN_BRI    = 0x30, /**< Physical interface protocol for ISDN BRI.              */
    APP_USBD_CDC_DATA_PROTOCOL_HDLC        = 0x31, /**< HDLC.                                                  */
    APP_USBD_CDC_DATA_PROTOCOL_TRANSPARENT = 0x32, /**< Transparent.                                           */
    APP_USBD_CDC_DATA_PROTOCOL_Q921M       = 0x50, /**< Management protocol for Q.921 data link protocol.      */
    APP_USBD_CDC_DATA_PROTOCOL_Q921        = 0x51, /**< Data link protocol for Q.921.                          */
    APP_USBD_CDC_DATA_PROTOCOL_Q921TM      = 0x52, /**< TEI-multiplexor for Q.921 data link protocol.          */
    APP_USBD_CDC_DATA_PROTOCOL_V42BIS      = 0x90, /**< Data compression procedures.                           */
    APP_USBD_CDC_DATA_PROTOCOL_Q931        = 0x91, /**< Euro-ISDN protocol control.                            */
    APP_USBD_CDC_DATA_PROTOCOL_V120        = 0x92, /**< V.24 rate adaptation to ISDN.                          */
    APP_USBD_CDC_DATA_PROTOCOL_CAPI20      = 0x93, /**< CAPI Commands.                                         */
    APP_USBD_CDC_DATA_PROTOCOL_HOST        = 0xFD, /**< Host based driver.
                                                     *   @note This protocol code should only be used in messages
                                                     *   between host and device to identify the host driver portion
                                                     *   of a protocol stack.
                                                     */
    APP_USBD_CDC_DATA_PROTOCOL_EXTERNAL    = 0xFE, /**< The protocol(s) are described using a Protocol Unit Functional
                                                     * Descriptors on Communications Class Interface.
                                                     */
    APP_USBD_CDC_DATA_PROTOCOL_VENDOR      = 0xFF  /**< Vendor-specific. */
} app_usbd_cdc_data_protocol_t;

/**
 * @brief CDC Functional Descriptor types.
 */
typedef enum {
    APP_USBD_CDC_CS_INTERFACE = 0x24, /**< Class specific interface descriptor type.*/
    APP_USBD_CDC_CS_ENDPOINT  = 0x25  /**< Class specific endpoint descriptor type.*/
} app_usbd_cdc_func_type_t;

/**
 * @brief CDC Functional Descriptor subtypes.
 */
typedef enum {
    APP_USBD_CDC_SCS_HEADER      = 0x00, /**< Header Functional Descriptor, which marks the beginning of the concatenated set of functional descriptors for the interface. */
    APP_USBD_CDC_SCS_CALL_MGMT   = 0x01, /**< Call Management Functional Descriptor.                                                                                       */
    APP_USBD_CDC_SCS_ACM         = 0x02, /**< Abstract Control Management Functional Descriptor.                                                                           */
    APP_USBD_CDC_SCS_DLM         = 0x03, /**< Direct Line Management Functional Descriptor.                                                                                */
    APP_USBD_CDC_SCS_TEL_R       = 0x04, /**< Telephone Ringer Functional Descriptor.                                                                                      */
    APP_USBD_CDC_SCS_TEL_CAP     = 0x05, /**< Telephone Call and Line State Reporting Capabilities Functional Descriptor.                                                  */
    APP_USBD_CDC_SCS_UNION       = 0x06, /**< Union Functional Descriptor.                                                                                                 */
    APP_USBD_CDC_SCS_COUNTRY_SEL = 0x07, /**< Country Selection Functional Descriptor.                                                                                     */
    APP_USBD_CDC_SCS_TEL_OM      = 0x08, /**< Telephone Operational Modes Functional Descriptor.                                                                           */
    APP_USBD_CDC_SCS_USB_TERM    = 0x09, /**< USB Terminal Functional Descriptor.                                                                                          */
    APP_USBD_CDC_SCS_NCT         = 0x0A, /**< Network Channel Terminal Descriptor.                                                                                         */
    APP_USBD_CDC_SCS_PU          = 0x0B, /**< Protocol Unit Functional Descriptor.                                                                                         */
    APP_USBD_CDC_SCS_EU          = 0x0C, /**< Extension Unit Functional Descriptor.                                                                                        */
    APP_USBD_CDC_SCS_MCM         = 0x0D, /**< Multi-Channel Management Functional Descriptor.                                                                              */
    APP_USBD_CDC_SCS_CAPI        = 0x0E, /**< CAPI Control Management Functional Descriptor.                                                                               */
    APP_USBD_CDC_SCS_ETH         = 0x0F, /**< Ethernet Networking Functional Descriptor.                                                                                   */
    APP_USBD_CDC_SCS_ATM         = 0x10, /**< ATM Networking Functional Descriptor.                                                                                        */
    APP_USBD_CDC_SCS_WHCM        = 0x11, /**< Wireless Handset Control Model Functional Descriptor.                                                                        */
    APP_USBD_CDC_SCS_MDLM        = 0x12, /**< Mobile Direct Line Model Functional Descriptor.                                                                              */
    APP_USBD_CDC_SCS_MDLM_DET    = 0x13, /**< MDLM Detail Functional Descriptor.                                                                                           */
    APP_USBD_CDC_SCS_DMM         = 0x14, /**< Device Management Model Functional Descriptor.                                                                               */
    APP_USBD_CDC_SCS_OBEX        = 0x15, /**< OBEX Functional Descriptor.                                                                                                  */
    APP_USBD_CDC_SCS_CS          = 0x16, /**< Command Set Functional Descriptor.                                                                                           */
    APP_USBD_CDC_SCS_CS_DET      = 0x17, /**< Command Set Detail Functional Descriptor.                                                                                    */
    APP_USBD_CDC_SCS_TEL_CM      = 0x18, /**< Telephone Control Model Functional Descriptor.                                                                               */
    APP_USBD_CDC_SCS_OBEX_SI     = 0x19, /**< OBEX Service Identifier Functional Descriptor.                                                                               */
    APP_USBD_CDC_SCS_NCM         = 0x1A  /**< NCM Functional Descriptor.                                                                                                   */
} app_usbd_cdc_func_subtype_t;

/* Make all descriptors packed */
#pragma pack(push, 1)

/**
 * @brief Header Functional Descriptor.
 */
typedef struct {
    uint8_t bFunctionLength;    //!< Size of this descriptor in bytes.
    uint8_t bDescriptorType;    //!< @ref APP_USBD_CDC_CS_INTERFACE descriptor type.
    uint8_t bDescriptorSubtype; //!< Descriptor subtype @ref APP_USBD_CDC_SCS_HEADER.
    uint8_t bcdCDC[2];          //!< USB Class Definitions for Communications Devices Specification release number in binary-coded decimal.
} app_usbd_cdc_desc_header_t;

/**
 * @brief Call management capabilities.
 *
 * @ref app_usbd_cdc_desc_call_mgmt_t::bmCapabilities bit.
 * */
typedef enum {
    APP_USBD_CDC_CALL_MGMT_SUPPORTED = (1 << 0),  /**< Call management capability bit 0.*/
    APP_USBD_CDC_CALL_MGMT_OVER_DCI  = (1 << 1),  /**< Call management capability bit 1.*/
} app_subd_cdc_call_mgmt_cap_t;

/**
 * @brief CDC Call Management Functional Descriptor.
 */
typedef struct {
    uint8_t bFunctionLength;    //!< Size of this functional descriptor, in bytes.
    uint8_t bDescriptorType;    //!< Descriptor type @ref APP_USBD_CDC_CS_INTERFACE.
    uint8_t bDescriptorSubtype; //!< Descriptor subtype @ref APP_USBD_CDC_SCS_CALL_MGMT.
    uint8_t bmCapabilities;     //!< Capabilities @ref app_subd_cdc_call_mgmt_cap_t.
    uint8_t bDataInterface;     //!< Data interface number.
} app_usbd_cdc_desc_call_mgmt_t;

/**
 * @brief ACM capabilities.
 *
 * @ref app_usbd_cdc_desc_acm_t::bmCapabilities bit.
 * */
typedef enum {
    APP_USBD_CDC_ACM_FEATURE_REQUESTS   = (1 << 0),  /**< ACM capability bit FEATURE_REQUESTS.  */
    APP_USBD_CDC_ACM_LINE_REQUESTS      = (1 << 1),  /**< ACM capability bit LINE_REQUESTS.     */
    APP_USBD_CDC_ACM_SENDBREAK_REQUESTS = (1 << 2),  /**< ACM capability bit SENDBREAK_REQUESTS.*/
    APP_USBD_CDC_ACM_NOTIFY_REQUESTS    = (1 << 3),  /**< ACM capability bit NOTIFY_REQUESTS.   */
} app_subd_cdc_acm_cap_t;

/**
 * @brief CDC ACM Functional Descriptor.
 */
typedef struct {
    uint8_t bFunctionLength;      //!< Size of this functional descriptor, in bytes.
    uint8_t bDescriptorType;      //!< Descriptor type @ref APP_USBD_CDC_CS_INTERFACE.
    uint8_t bDescriptorSubtype;   //!< Descriptor subtype @ref APP_USBD_CDC_SCS_ACM.
    uint8_t bmCapabilities;       //!< Capabilities @ref app_subd_cdc_acm_cap_t.
} app_usbd_cdc_desc_acm_t;

/**
 * @brief Union Functional Descriptor.
 */
typedef struct {
    uint8_t bFunctionLength;         //!< Size of this functional descriptor, in bytes.
    uint8_t bDescriptorType;         //!< Descriptor type @ref APP_USBD_CDC_CS_INTERFACE.
    uint8_t bDescriptorSubtype;      //!< Descriptor subtype @ref APP_USBD_CDC_SCS_UNION.
    uint8_t bControlInterface;       //!< The interface number of the Communications or Data Class interface, designated as the controlling interface for the union.
    uint8_t bSubordinateInterface[]; //!< Interface number of subordinate interfaces in the union. Number of interfaced depends on descriptor size.
} app_usbd_cdc_desc_union_t;

/**
 * @brief Country Selection Functional Descriptor.
 */
typedef struct {
    uint8_t bFunctionLength;        //!< Size of this functional descriptor, in bytes.
    uint8_t bDescriptorType;        //!< Descriptor type @ref APP_USBD_CDC_CS_INTERFACE.
    uint8_t bDescriptorSubtype;     //!< Descriptor subtype @ref APP_USBD_CDC_SCS_COUNTRY_SEL.
    uint8_t iCountryCodeRelDate;    //!< Index of a string giving the release date for the implemented ISO 3166 Country Codes.
} app_usbd_cdc_desc_country_sel_t;

/**
 * @brief CDC Requests
 *
 */
typedef enum {
    /* CDC General */
    APP_USBD_CDC_REQ_SEND_ENCAPSULATED_COMMAND = 0x00, /**< This request is used to issue a command in the format of the supported control protocol of the Communications Class interface.    */
    APP_USBD_CDC_REQ_GET_ENCAPSULATED_RESPONSE = 0x01, /**< This request is used to request a response in the format of the supported control protocol of the Communications Class interface. */
    /* CDC PSTN */
    APP_USBD_CDC_REQ_SET_COMM_FEATURE          = 0x02, /**< This request controls the settings for a particular communications feature of a particular target. */
    APP_USBD_CDC_REQ_GET_COMM_FEATURE          = 0x03, /**< This request returns the current settings for the communications feature as selected. */
    APP_USBD_CDC_REQ_CLEAR_COMM_FEATURE        = 0x04, /**< This request controls the settings for a particular communications feature of a particular target, setting the selected feature to its default state. */
    APP_USBD_CDC_REQ_SET_AUX_LINE_STATE        = 0x10, /**< This request is used to connect or disconnect a secondary jack to POTS circuit or CODEC, depending on hook state. */
    APP_USBD_CDC_REQ_SET_HOOK_STATE            = 0x11, /**< This request is used to set the necessary PSTN line relay code for on-hook, off-hook, and caller ID states. */
    APP_USBD_CDC_REQ_PULSE_SETUP               = 0x12, /**< This request is used to prepare for a pulse-dialing cycle. */
    APP_USBD_CDC_REQ_SEND_PULSE                = 0x13, /**< This request is used to generate a specified number of make/break pulse cycles. */
    APP_USBD_CDC_REQ_SET_PULSE_TIME            = 0x14, /**< This request sets the timing of the make and break periods for pulse dialing. */
    APP_USBD_CDC_REQ_RING_AUX_JACK             = 0x15, /**< This request is used to generate a ring signal on a secondary phone jack. */
    APP_USBD_CDC_REQ_SET_LINE_CODING           = 0x20, /**< This request allows the host to specify typical asynchronous line-character formatting properties. */
    APP_USBD_CDC_REQ_GET_LINE_CODING           = 0x21, /**< This request allows the host to find out the currently configured line coding. */
    APP_USBD_CDC_REQ_SET_CONTROL_LINE_STATE    = 0x22, /**< This request generates RS-232/V.24 style control signals. */
    APP_USBD_CDC_REQ_SEND_BREAK                = 0x23, /**< This request sends special carrier modulation that generates an RS-232 style break. */
    APP_USBD_CDC_REQ_SET_RINGER_PARMS          = 0x30, /**< This request configures the ringer for the communications device. */
    APP_USBD_CDC_REQ_GET_RINGER_PARMS          = 0x31, /**< This request returns the ringer capabilities of the device and the current status of the device’s ringer. */
    APP_USBD_CDC_REQ_SET_OPERATION_PARMS       = 0x32, /**< Sets the operational mode for the device, between a simple mode, standalone mode and a host centric mode. */
    APP_USBD_CDC_REQ_GET_OPERATION_PARMS       = 0x33, /**< This request gets the current operational mode for the device. */
    APP_USBD_CDC_REQ_SET_LINE_PARMS            = 0x34, /**< This request is used to change the state of the line, corresponding to the interface or master interface of a union to which the command was sent. */
    APP_USBD_CDC_REQ_GET_LINE_PARMS            = 0x35, /**< This request is used to report the state of the line that corresponds to the interface or master interface of a union to which the command was sent. */
    APP_USBD_CDC_REQ_DIAL_DIGITS               = 0x36, /**< This request dials the DTMF digits over the specified line. */
} app_usbd_cdc_req_id_t;

/**
 * @brief CDC Notifications.
 */
typedef enum {
    /* CDC General */
    APP_USBD_CDC_NOTIF_NETWORK_CONNECTION      = 0x00, /**< This notification allows the device to notify the host about network connection status. */
    APP_USBD_CDC_NOTIF_RESPONSE_AVAILABLE      = 0x01, /**< This notification allows the device to notify the host that a response is available.
                                                        *   This response can be retrieved with a subsequent GetEncapsulatedResponse request.
                      _                                 */
    APP_USBD_CDC_NOTIF_CONNECTION_SPEED_CHANGE = 0x2A, /**< This notification allows the device to inform the host-networking driver
                                                        *   that a change in either the up-link or the down-link bit rate of the connection has occurred.
                                                        */
    /* CDC PSTN */
    APP_USBD_CDC_NOTIF_AUX_JACK_HOOK_STATE     = 0x08, /**< (DLM) This notification indicates the loop has changed on the auxiliary phone interface of the USB device. */
    APP_USBD_CDC_NOTIF_RING_DETECT             = 0x09, /**< (DLM) This notification indicates ring voltage on the POTS line interface of the USB device. */
    APP_USBD_CDC_NOTIF_SERIAL_STATE            = 0x20, /**< (ACM) This notification sends asynchronous notification of UART status. */
    APP_USBD_CDC_NOTIF_CALL_STATE_CHANGE       = 0x28, /**< (TCM) This notification identifies that a change has occurred to the state of a call on the line corresponding to the interface or union for the line. */
    APP_USBD_CDC_NOTIF_LINE_STATE_CHANGE       = 0x29  /**< (TCM) This notification identifies that a change has occurred to the state of the line corresponding to the interface or master interface of a union sending the notification message. */
} app_usbd_cdc_notify_id_t;

/**
 * @brief Notification sent via CDC COMM endpoint.
 * */
typedef struct {
    uint8_t  bmRequestType; //!< Request type.
    uint8_t  bRequest;      //!< Request ID @ref app_usbd_cdc_req_id_t.
    uint16_t wValue;        //!< Value field.
    uint16_t wIndex;        //!< Index field.
    uint16_t wLength;       //!< Length of payload following.
} app_usbd_cdc_notify_t;

/**
 * @brief CDC line coding structure.
 */
typedef struct {
    uint8_t dwDTERate[4];   //!< Line baudrate.
    uint8_t bCharFormat;    //!< Character format @ref app_usbd_cdc_line_stopbit_t.
    uint8_t bParityType;    //!< Parity bits @ref app_usbd_cdc_line_parity_t.
    uint8_t bDataBits;      //!< Number of data bits.
} app_usbd_cdc_line_coding_t;

/**
 * @brief Possible values of @ref app_usbd_cdc_line_coding_t::bCharFormat.
 */
typedef enum {
    APP_USBD_CDC_LINE_STOPBIT_1   = 0, /**< 1 stop bit.       */
    APP_USBD_CDC_LINE_STOPBIT_1_5 = 1, /**< 1.5 stop bits.    */
    APP_USBD_CDC_LINE_STOPBIT_2   = 2, /**< 2 stop bits.      */
} app_usbd_cdc_line_stopbit_t;

/**
 * @brief Possible values of @ref app_usbd_cdc_line_coding_t::bParityType.
 */
typedef enum {
    APP_USBD_CDC_LINE_PARITY_NONE  = 0,  /**< No parity.                 */
    APP_USBD_CDC_LINE_PARITY_ODD   = 1,  /**< Odd parity.                */
    APP_USBD_CDC_LINE_PARITY_EVEN  = 2,  /**< Even parity.               */
    APP_USBD_CDC_LINE_PARITY_MARK  = 3,  /**< Parity forced to 0 (space).*/
    APP_USBD_CDC_LINE_PARITY_SPACE = 4,  /**< Parity forced to 1 (mark). */
} app_usbd_cdc_line_parity_t;


#pragma pack(pop)

/** @} */
#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_TYPES_H__ */
