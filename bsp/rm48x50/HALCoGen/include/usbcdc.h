//*****************************************************************************
//
// usbhid.h - Definitions used by Communication Device Class devices.
//
// Copyright (c) 2007-2010 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
//
//*****************************************************************************

//*****************************************************************************
//
// Note: This header contains definitions related to the USB Communication
//       Device Class specification.  The header is complete for ACM model
//       devices but request and notification definitions specific to other
//       modem types, ISDN, ATM and Ethernet are currently incomplete or
//       omitted.
//
//*****************************************************************************

#ifndef __USBCDC_H__
#define __USBCDC_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup cdc_device_class_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// Generic macros to read a byte, word or long from a character pointer.
//
//*****************************************************************************
#define BYTE(pucData)           (*(uint8 *)(pucData))
#define SHORT(pucData)          (*(uint16 *)(pucData))
#define LONG(pucData)           (*(uint32 *)(pucData))

//*****************************************************************************
//
// USB CDC subclass codes.  Used in interface descriptor, bInterfaceClass
//
//*****************************************************************************
#define USB_CDC_SUBCLASS_DIRECT_LINE_MODEL          0x01
#define USB_CDC_SUBCLASS_ABSTRACT_MODEL             0x02
#define USB_CDC_SUBCLASS_TELEPHONE_MODEL            0x03
#define USB_CDC_SUBCLASS_MULTI_CHANNEL_MODEL        0x04
#define USB_CDC_SUBCLASS_CAPI_MODEL                 0x05
#define USB_CDC_SUBCLASS_ETHERNET_MODEL             0x06
#define USB_CDC_SUBCLASS_ATM_MODEL                  0x07

//*****************************************************************************
//
// USB CDC control interface protocols.  Used in control interface descriptor,
// bInterfaceProtocol
//
//*****************************************************************************
#define USB_CDC_PROTOCOL_NONE                       0x00
#define USB_CDC_PROTOCOL_V25TER                     0x01
#define USB_CDC_PROTOCOL_VENDOR                     0xFF

//*****************************************************************************
//
// USB CDC data interface protocols.  Used in data interface descriptor,
// bInterfaceProtocol
//
//*****************************************************************************
//      USB_CDC_PROTOCOL_NONE                       0x00
#define USB_CDC_PROTOCOL_I420                       0x30
#define USB_CDC_PROTOCOL_TRANSPARENT                0x32
#define USB_CDC_PROTOCOL_Q921M                      0x50
#define USB_CDC_PROTOCOL_Q921                       0x51
#define USB_CDC_PROTOCOL_Q921TM                     0x52
#define USB_CDC_PROTOCOL_V42BIS                     0x90
#define USB_CDC_PROTOCOL_Q921EURO                   0x91
#define USB_CDC_PROTOCOL_V120                       0x92
#define USB_CDC_PROTOCOL_CAPI20                     0x93
#define USB_CDC_PROTOCOL_HOST_DRIVER                0xFD
#define USB_CDC_PROTOCOL_CDC_SPEC                   0xFE
//      USB_CDC_PROTOCOL_VENDOR                     0xFF

//*****************************************************************************
//
// Functional descriptor definitions
//
//*****************************************************************************

//*****************************************************************************
//
// Functional descriptor types
//
//*****************************************************************************
#define USB_CDC_CS_INTERFACE                    0x24
#define USB_CDC_CS_ENDPOINT                     0x25

//*****************************************************************************
//
// Functional descriptor subtypes
//
//*****************************************************************************
#define USB_CDC_FD_SUBTYPE_HEADER               0x00
#define USB_CDC_FD_SUBTYPE_CALL_MGMT            0x01
#define USB_CDC_FD_SUBTYPE_ABSTRACT_CTL_MGMT    0x02
#define USB_CDC_FD_SUBTYPE_DIRECT_LINE_MGMT     0x03
#define USB_CDC_FD_SUBTYPE_TELEPHONE_RINGER     0x04
#define USB_CDC_FD_SUBTYPE_LINE_STATE_CAPS      0x05
#define USB_CDC_FD_SUBTYPE_UNION                0x06
#define USB_CDC_FD_SUBTYPE_COUNTRY              0x07
#define USB_CDC_FD_SUBTYPE_TELEPHONE_MODES      0x08
#define USB_CDC_FD_SUBTYPE_USB_TERMINAL         0x09
#define USB_CDC_FD_SUBTYPE_NETWORK_TERMINAL     0x0A
#define USB_CDC_FD_SUBTYPE_PROTOCOL_UNIT        0x0B
#define USB_CDC_FD_SUBTYPE_EXTENSION_UNIT       0x0C
#define USB_CDC_FD_SUBTYPE_MULTI_CHANNEL_MGMT   0x0D
#define USB_CDC_FD_SUBTYPE_CAPI_MGMT            0x0E
#define USB_CDC_FD_SUBTYPE_ETHERNET             0x0F
#define USB_CDC_FD_SUBTYPE_ATM                  0x10

//*****************************************************************************
//
// USB_CDC_FD_SUBTYPE_CALL_MGMT, Header functional descriptor, bmCapabilities
//
//*****************************************************************************
#define USB_CDC_CALL_MGMT_VIA_DATA              0x02
#define USB_CDC_CALL_MGMT_HANDLED               0x01

//*****************************************************************************
//
// USB_CDC_FD_SUBTYPE_ABSTRACT_CTL_MGMT, Abstract Control Management functional
// descriptor, bmCapabilities
//
//*****************************************************************************
#define USB_CDC_ACM_SUPPORTS_NETWORK_CONNECTION 0x08
#define USB_CDC_ACM_SUPPORTS_SEND_BREAK         0x04
#define USB_CDC_ACM_SUPPORTS_LINE_PARAMS        0x02
#define USB_CDC_ACM_SUPPORTS_COMM_FEATURE       0x01

//*****************************************************************************
//
// USB_CDC_FD_SUBTYPE_DIRECT_LINE_MGMT, Direct Line Management functional
// descriptor, bmCapabilities
//
//*****************************************************************************
#define USB_CDC_DLM_NEEDS_EXTRA_PULSE_SETUP     0x04
#define USB_CDC_DLM_SUPPORTS_AUX                0x02
#define USB_CDC_DLM_SUPPORTS_PULSE              0x01

//*****************************************************************************
//
// USB_CDC_FD_SUBTYPE_TELEPHONE_MODES, Telephone Operational Modes functional
// descriptor, bmCapabilities
//
//*****************************************************************************
#define USB_CDC_TELEPHONE_SUPPORTS_COMPUTER     0x04
#define USB_CDC_TELEPHONE_SUPPORTS_STANDALONE   0x02
#define USB_CDC_TELEPHONE_SUPPORTS_SIMPLE       0x01

//*****************************************************************************
//
// USB_CDC_FD_SUBTYPE_LINE_STATE_CAPS, Telephone Call and Line State Reporting
// Capabilities descriptor
//
//*****************************************************************************
#define USB_CDC_LINE_STATE_CHANGES_NOTIFIED     0x20
#define USB_CDC_LINE_STATE_REPORTS_DTMF         0x10
#define USB_CDC_LINE_STATE_REPORTS_DIST_RING    0x08
#define USB_CDC_LINE_STATE_REPORTS_CALLERID     0x04
#define USB_CDC_LINE_STATE_REPORTS_BUSY         0x02
#define USB_CDC_LINE_STATE_REPORTS_INT_DIALTONE 0x01

//*****************************************************************************
//
// USB_CDC_FD_SUBTYPE_USB_TERMINAL, USB Terminal functional descriptor,
// bmOptions
//
//*****************************************************************************
#define USB_CDC_TERMINAL_NO_WRAPPER_USED        0x00
#define USB_CDC_TERMINAL_WRAPPER_USED           0x01

//*****************************************************************************
//
// USB_CDC_FD_SUBTYPE_MULTI_CHANNEL_MGMT, Multi-Channel Management functional
// descriptor, bmCapabilities
//
//*****************************************************************************
#define USB_CDC_MCM_SUPPORTS_SET_UNIT_PARAM     0x04
#define USB_CDC_MCM_SUPPORTS_CLEAR_UNIT_PARAM   0x02
#define USB_CDC_MCM_UNIT_PARAMS_NON_VOLATILE    0x01

//*****************************************************************************
//
// USB_CDC_FD_SUBTYPE_CAPI_MGMT, CAPI Control Management functional descriptor,
// bmCapabilities
//
//*****************************************************************************
#define USB_CDC_CAPI_INTELLIGENT                0x01
#define USB_CDC_CAPI_SIMPLE                     0x00

//*****************************************************************************
//
// USB_CDC_FD_SUBTYPE_ETHERNET, Ethernet Networking functional descriptor,
// bmEthernetStatistics
//
//*****************************************************************************
#define USB_CDC_ETHERNET_XMIT_OK                0x01000000
#define USB_CDC_ETHERNET_RCV_OK                 0x02000000
#define USB_CDC_ETHERNET_XMIT_ERROR             0x04000000
#define USB_CDC_ETHERNET_RCV_ERROR              0x08000000
#define USB_CDC_ETHERNET_RCV_NO_BUFFER          0x10000000
#define USB_CDC_ETHERNET_DIRECTED_BYTES_XMIT    0x20000000
#define USB_CDC_ETHERNET_DIRECTED_FRAMES_XMIT   0x40000000
#define USB_CDC_ETHERNET_MULTICAST_BYTES_XMIT   0x80000000
#define USB_CDC_ETHERNET_MULTICAST_FRAMES_XMIT  0x00010000
#define USB_CDC_ETHERNET_BROADCAST_BYTES_XMIT   0x00020000
#define USB_CDC_ETHERNET_BROADCAST_FRAMES_XMIT  0x00040000
#define USB_CDC_ETHERNET_DIRECTED_BYTES_RCV     0x00080000
#define USB_CDC_ETHERNET_DIRECTED_FRAMES_RCV    0x00100000
#define USB_CDC_ETHERNET_MULTICAST_BYTES_RCV    0x00200000
#define USB_CDC_ETHERNET_MULTICAST_FRAMES_RCV   0x00400000
#define USB_CDC_ETHERNET_BROADCAST_BYTES_RCV    0x00800000
#define USB_CDC_ETHERNET_BROADCAST_FRAMES_RCV   0x00000100
#define USB_CDC_ETHERNET_RCV_CRC_ERROR          0x00000200
#define USB_CDC_ETHERNET_TRANSMIT_QUEUE_LENGTH  0x00000400
#define USB_CDC_ETHERNET_RCV_ERROR_ALIGNMENT    0x00000800
#define USB_CDC_ETHERNET_XMIT_ONE_COLLISION     0x00001000
#define USB_CDC_ETHERNET_XMIT_MORE_COLLISIONS   0x00002000
#define USB_CDC_ETHERNET_XMIT_DEFERRED          0x00004000
#define USB_CDC_ETHERNET_XMIT_MAX_COLLISIONS    0x00008000
#define USB_CDC_ETHERNET_RCV_OVERRUN            0x00000001
#define USB_CDC_ETHERNET_XMIT_UNDERRUN          0x00000002
#define USB_CDC_ETHERNET_XMIT_HEARTBEAT_FAILURE 0x00000004
#define USB_CDC_ETHERNET_XMIT_TIMES_CRS_LOST    0x00000008
#define USB_CDC_ETHERNET_XMIT_LATE_COLLISIONS   0x00000010

//*****************************************************************************
//
// USB_CDC_FD_SUBTYPE_ATM, ATM Networking functional descriptor,
// bmDataCapabilities
//
//*****************************************************************************
#define USB_CDC_ATM_TYPE_3                      0x08
#define USB_CDC_ATM_TYPE_2                      0x04
#define USB_CDC_ATM_TYPE_1                      0x02

//*****************************************************************************
//
// bmATMDeviceStatistics
//
//*****************************************************************************
#define USB_CDC_ATM_VC_US_CELLS_SENT            0x10
#define USB_CDC_ATM_VC_US_CELLS_RECEIVED        0x08
#define USB_CDC_ATM_DS_CELLS_HEC_ERR_CORRECTED  0x04
#define USB_CDC_ATM_US_CELLS_SENT               0x02
#define USB_CDC_ATM_US_CELLS_RECEIVED           0x01

//*****************************************************************************
//
// Management Element Requests (provided in tUSBRequest.ucRequest)
//
//*****************************************************************************
#define USB_CDC_SEND_ENCAPSULATED_COMMAND                       0x00
#define USB_CDC_GET_ENCAPSULATED_RESPONSE                       0x01
#define USB_CDC_SET_COMM_FEATURE                                0x02
#define USB_CDC_GET_COMM_FEATURE                                0x03
#define USB_CDC_CLEAR_COMM_FEATURE                              0x04
#define USB_CDC_SET_AUX_LINE_STATE                              0x10
#define USB_CDC_SET_HOOK_STATE                                  0x11
#define USB_CDC_PULSE_SETUP                                     0x12
#define USB_CDC_SEND_PULSE                                      0x13
#define USB_CDC_SET_PULSE_TIME                                  0x14
#define USB_CDC_RING_AUX_JACK                                   0x15
#define USB_CDC_SET_LINE_CODING                                 0x20
#define USB_CDC_GET_LINE_CODING                                 0x21
#define USB_CDC_SET_CONTROL_LINE_STATE                          0x22
#define USB_CDC_SEND_BREAK                                      0x23
#define USB_CDC_SET_RINGER_PARMS                                0x30
#define USB_CDC_GET_RINGER_PARMS                                0x31
#define USB_CDC_SET_OPERATION_PARMS                             0x32
#define USB_CDC_GET_OPERATION_PARMS                             0x33
#define USB_CDC_SET_LINE_PARMS                                  0x34
#define USB_CDC_GET_LINE_PARMS                                  0x35
#define USB_CDC_DIAL_DIGITS                                     0x36
#define USB_CDC_SET_UNIT_PARAMETER                              0x37
#define USB_CDC_GET_UNIT_PARAMETER                              0x38
#define USB_CDC_CLEAR_UNIT_PARAMETER                            0x39
#define USB_CDC_GET_PROFILE                                     0x3A
#define USB_CDC_SET_ETHERNET_MULTICAST_FILTERS                  0x40
#define USB_CDC_SET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER    0x41
#define USB_CDC_GET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER    0x42
#define USB_CDC_SET_ETHERNET_PACKET_FILTER                      0x43
#define USB_CDC_GET_ETHERNET_STATISTIC                          0x44
#define USB_CDC_SET_ATM_DATA_FORMAT                             0x50
#define USB_CDC_GET_ATM_DEVICE_STATISTICS                       0x51
#define USB_CDC_SET_ATM_DEFAULT_VC                              0x52
#define USB_CDC_GET_ATM_VC_STATISTICS                           0x53

//*****************************************************************************
//
// In cases where a request defined above results in the return of a fixed size
// data block, the following group of labels define the size of that block.  In
// each of these cases, an access macro is also provided to write the response
// data into an appropriately-sized array of uint8acters.
//
//*****************************************************************************
#define USB_CDC_SIZE_COMM_FEATURE                                2
#define USB_CDC_SIZE_LINE_CODING                                 7
#define USB_CDC_SIZE_RINGER_PARMS                                4
#define USB_CDC_SIZE_OPERATION_PARMS                             2
#define USB_CDC_SIZE_UNIT_PARAMETER                              2
#define USB_CDC_SIZE_PROFILE                                     64
#define USB_CDC_SIZE_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER    2
#define USB_CDC_SIZE_ETHERNET_STATISTIC                          4
#define USB_CDC_SIZE_ATM_DEVICE_STATISTICS                       4
#define USB_CDC_SIZE_ATM_VC_STATISTICS                           4
#define USB_CDC_SIZE_LINE_PARMS                                  10

//*****************************************************************************
//
// NB: USB_CDC_SIZE_LINE_PARAMS assumes only a single call.  For multiple
// calls, add 4 bytes per additional call.
//
//*****************************************************************************

//*****************************************************************************
//
// USB_CDC_GET_COMM_FEATURE & USB_CDC_SET_COMM_FEATURE
//
//*****************************************************************************

//*****************************************************************************
//
// wValue (Feature Selector)
//
//*****************************************************************************
#define USB_CDC_ABSTRACT_STATE                  0x0001
#define USB_CDC_COUNTRY_SETTING                 0x0002

//*****************************************************************************
//
// Data when feature selector is USB_DCD_ABSTRACT_STATE
//
//*****************************************************************************
#define USB_CDC_ABSTRACT_CALL_DATA_MULTIPLEXED  0x0002
#define USB_CDC_ABSTRACT_ENDPOINTS_IDLE         0x0001

//*****************************************************************************
//
// Macros to populate the response data buffer (whose size in bytes is defined
// by USB_CDC_SIZE_COMM_FEATURE).
//
//*****************************************************************************
#define SetResponseCommFeature(pcBuf, usData)        \
        do                                           \
        {                                            \
            (*(uint16 *)(pcBuf)) = (usData); \
        }                                            \
        while(0)

//*****************************************************************************
//
// USB_CDC_SET_AUX_LINE_STATE, wValue
//
//*****************************************************************************
#define USB_CDC_AUX_DISCONNECT                  0x0000
#define USB_CDC_AUX_CONNECT                     0x0001

//*****************************************************************************
//
// USB_CDC_SET_HOOK_STATE, wValue
//
//*****************************************************************************
#define USB_CDC_ON_HOOK                         0x0000
#define USB_CDC_OFF_HOOK                        0x0001
#define USB_CDC_SNOOPING                        0x0002

//*****************************************************************************
//
// USB_CDC_GET_LINE_CODING
//
//*****************************************************************************
#define USB_CDC_STOP_BITS_1                     0x00
#define USB_CDC_STOP_BITS_1_5                   0x01
#define USB_CDC_STOP_BITS_2                     0x02

#define USB_CDC_PARITY_NONE                     0x00
#define USB_CDC_PARITY_ODD                      0x01
#define USB_CDC_PARITY_EVEN                     0x02
#define USB_CDC_PARITY_MARK                     0x03
#define USB_CDC_PARITY_SPACE                    0x04

//*****************************************************************************
//
// Macro to populate the response data buffer (whose size in bytes is defined
// by USB_CDC_SIZE_LINE_CODING).
//
//*****************************************************************************
#define SetResponseLineCoding(pcBuf, ucRate, ucStop, ucParity, ucDatabits) \
        do                                                                 \
        {                                                                  \
            (*(uint32 *)(pcBuf)) = (ucRate);                        \
            (*((uint8 *)(pcBuf) + 4)) = (ucStop);                  \
            (*((uint8 *)(pcBuf) + 5)) = (ucParity);                \
            (*((uint8 *)(pcBuf) + 6)) = (ucDatabits);              \
        }                                                                  \
        while(0)

//*****************************************************************************
//
// USB_CDC_SET_CONTROL_LINE_STATE, wValue
//
//*****************************************************************************
#define USB_CDC_DEACTIVATE_CARRIER              0x00
#define USB_CDC_ACTIVATE_CARRIER                0x02
#define USB_CDC_DTE_NOT_PRESENT                 0x00
#define USB_CDC_DTE_PRESENT                     0x01

//*****************************************************************************
//
// USB_CDC_SET_RINGER_PARMS, USB_CDC_GET_RINGER_PARMS and
// USB_CDC_GET_LINE_PARMS (ulRingerBmp)
//
//*****************************************************************************
#define USB_CDC_RINGER_EXISTS                   0x80000000
#define USB_CDC_RINGER_DOES_NOT_EXIST           0x00000000

//*****************************************************************************
//
// Macro to populate the response data buffer to USB_CDC_GET_RINGER_PARMS.
// Parameter buf points to a buffer of size USB_CDC_SIZE_RINGER_PARMS bytes.
//
//*****************************************************************************
#define SetResponseRingerParms(pcBuf, ucPattern, ucVolume, ulExists)          \
        do                                                                    \
        {                                                                     \
            *(uint32 *)(pcBuf) = ((ucPattern) +                        \
                                         ((ucVolume & 0xFF) << 8) +           \
                                         (ulExists & USB_CDC_RINGER_EXISTS)); \
        }                                                                     \
        while(0)

//*****************************************************************************
//
// Macros to extract fields from the USB_CDC_SET_RINGER_PARMS data
//
//*****************************************************************************
#define GetRingerVolume(pcData)  (BYTE((pcData)+1))
#define GetRingerPattern(pcData) (BYTE(pcData))
#define GetRingerExists(pcData)  ((LONG(pcData)) & USB_CDC_RINGER_EXISTS)

//*****************************************************************************
//
// USB_CDC_SET_OPERATION_PARMS, wValue
//
//*****************************************************************************
#define USB_CDC_SIMPLE_MODE                     0x0000
#define USB_CDC_STANDALONE_MODE                 0x0001
#define USB_CDC_HOST_CENTRIC_MODE               0x0002

//*****************************************************************************
//
// Macro to populate the response data buffer to USB_CDC_GET_OPERATION_PARMS.
// Parameter buf points to a buffer of size USB_CDC_SIZE_OPERATION_PARMS
// bytes.
//
//*****************************************************************************
#define SetResponseOperationParms(pBbuf, usData) \
        do                                       \
        {                                        \
            WORD(pcBuf) = (usData);              \
        }                                        \
        while(0)

//*****************************************************************************
//
// USB_CDC_SET_LINE_PARMS, wParam - Line State Change
//
//*****************************************************************************
#define USB_CDC_DROP_ACTIVE_CALL                0x0000
#define USB_CDC_START_NEW_CALL                  0x0001
#define USB_CDC_APPLY_RINGING                   0x0002
#define USB_CDC_REMOVE_RINGING                  0x0003
#define USB_CDC_SWITCH_CALL                     0x0004

//*****************************************************************************
//
// Line state bitmap in USB_CDC_GET_LINE_PARMS response
//
//*****************************************************************************
#define USB_CDC_LINE_IS_ACTIVE                  0x80000000
#define USB_CDC_LINE_IS_IDLE                    0x00000000
#define USB_CDC_LINE_NO_ACTIVE_CALL             0x000000FF

#define USB_CDC_CALL_ACTIVE                     0x80000000

//*****************************************************************************
//
// Call state value definitions
//
//*****************************************************************************
#define USB_CDC_CALL_IDLE                       0x00000000
#define USB_CDC_CALL_TYPICAL_DIALTONE           0x00000001
#define USB_CDC_CALL_INTERRUPTED_DIALTONE       0x00000002
#define USB_CDC_CALL_DIALING                    0x00000003
#define USB_CDC_CALL_RINGBACK                   0x00000004
#define USB_CDC_CALL_CONNECTED                  0x00000005
#define USB_CDC_CALL_INCOMING                   0x00000006

//*****************************************************************************
//
// Call state change value definitions
//
//*****************************************************************************
#define USB_CDC_CALL_STATE_IDLE                 0x01
#define USB_CDC_CALL_STATE_DIALING              0x02
#define USB_CDC_CALL_STATE_RINGBACK             0x03
#define USB_CDC_CALL_STATE_CONNECTED            0x04
#define USB_CDC_CALL_STATE_INCOMING             0x05

//*****************************************************************************
//
// Extra byte of data describing the connection type for
// USB_CDC_CALL_STATE_CONNECTED.
//
//*****************************************************************************
#define USB_CDC_VOICE                           0x00
#define USB_CDC_ANSWERING_MACHINE               0x01
#define USB_CDC_FAX                             0x02
#define USB_CDC_MODEM                           0x03
#define USB_CDC_UNKNOWN                         0xFF

//*****************************************************************************
//
// Macro to extract call index from request in cases where wParam is
// USB_CDC_SWITCH_CALL.
//
//*****************************************************************************
#define GetCallIndex(pcData) (BYTE(pcData))

//*****************************************************************************
//
// Macro to populate the CallState entries in response to request
// USB_CDC_GET_LINE_PARMS.  The ucIndex parameter is a zero based index
// indicating which call entry in the pcBuf response buffer to fill in.  Note
// that pcBuf points to the first byte of the buffer (the wLength field).
//
//*****************************************************************************
#define SetResponseCallState(pcBuf, ucIndex, ulActive, ucStateChange,   \
                             ucState)                                   \
        do                                                              \
        {                                                               \
            (LONG((uint8 *)(pcBuf) + (10 + (4 * (ucIndex))))) = \
                (((ulActive) & USB_CDC_CALL_IS_ACTIVE) +                \
                 (((ucStateChange) & 0xFF) << 8) +                      \
                 ((ucState) & 0xFF));                                   \
        }                                                               \
        while(0)

//*****************************************************************************
//
// Macro to populate the response data buffer (whose size in bytes is defined
// by USB_CDC_SIZE_LINE_PARMS).  Note that this macro only populates fields for
// a single call.  If multiple calls are being managed, additional 4 byte
// fields must be appended to provide call state for each call after the first.
// This may be done using the SetResponseCallState macro with the appropriate
// call index supplied.
//
//*****************************************************************************
#define SetResponseLineParms(pcBuf, usLength,                              \
                             ucRingPattern, ucRingVolume, ulRingExists,    \
                             ulLineActive, ucLineCallIndex,                \
                             ulCallActive, ucCallStateChange, ucCallState) \
        do                                                                 \
        {                                                                  \
            (WORD(pcBuf)) = (usLength);                                    \
            SetResponseRingerParams(((uint8 *)(pcBuf) + 2),        \
                                    (ucRingPattern), (ucRingVolume),       \
                                    (ulRingExists));                       \
            (LONG((uint8 *)(pcBuf) + 6)) =                         \
                (((ulLineActive) & USB_CDC_LINE_IS_ACTIVE) +               \
                 ((ucLineCallIndex) & 0xFF)) ;                             \
            SetResponseCallState((pcBuf), 0, (ulCallActive),               \
                                 (ucCallStateChange), (ucCallState));      \
        }                                                                  \
        while(0)

//*****************************************************************************
//
// Notification Element definitions
//
//*****************************************************************************
#define USB_CDC_NOTIFY_NETWORK_CONNECTION               0x00
#define USB_CDC_NOTIFY_RESPONSE_AVAILABLE               0x01
#define USB_CDC_NOTIFY_AUX_JACK_HOOK_STATE              0x08
#define USB_CDC_NOTIFY_RING_DETECT                      0x09
#define USB_CDC_NOTIFY_SERIAL_STATE                     0x20
#define USB_CDC_NOTIFY_CALL_STATE_CHANGE                0x28
#define USB_CDC_NOTIFY_LINE_STATE_CHANGE                0x29
#define USB_CDC_NOTIFY_CONNECTION_SPEED_CHANGE          0x2A

//*****************************************************************************
//
// USB_CDC_NOTIFY_NETWORK_CONNECTION, wValue
//
//*****************************************************************************
#define USB_CDC_NETWORK_DISCONNECTED                    0x0000
#define USB_CDC_NETWORK_CONNECTED                       0x0001

//*****************************************************************************
//
// USB_CDC_NOTIFY_AUX_JACK_HOOK_STATE, wValue
//
//*****************************************************************************
#define USB_CDC_AUX_JACK_ON_HOOK                        0x0000
#define USB_CDC_AUX_JACK_OFF_HOOK                       0x0001

//*****************************************************************************
//
// USB_CDC_NOTIFY_SERIAL_STATE, Data
//
//*****************************************************************************

//*****************************************************************************
//
// Number of bytes of data returned alongside this notification.
//
//*****************************************************************************
#define USB_CDC_NOTIFY_SERIAL_STATE_SIZE                2

#define USB_CDC_SERIAL_STATE_OVERRUN                    0x0040
#define USB_CDC_SERIAL_STATE_PARITY                     0x0020
#define USB_CDC_SERIAL_STATE_FRAMING                    0x0010
#define USB_CDC_SERIAL_STATE_RING_SIGNAL                0x0008
#define USB_CDC_SERIAL_STATE_BREAK                      0x0004
#define USB_CDC_SERIAL_STATE_TXCARRIER                  0x0002
#define USB_CDC_SERIAL_STATE_RXCARRIER                  0x0001

//*****************************************************************************
//
// USB_CDC_NOTIFY_CALL_STATE_CHANGE, wValue
//
// Call state values are defined above in the group beginning
// USB_CDC_CALL_STATE_IDLE.  Note that the data returned alongside this
// notification are heavily dependent upon the call state being reported so no
// specific lengths or access macros are provided here.
//
// Macro to construct the correct wValue for this notification given a state
// and call index.
//
//*****************************************************************************
#define SetNotifyCallStatewValue(psResult, ucCallState, ucIndex) \
        do                                                       \
        {                                                        \
            (WORD(psResult)) = (((ucCallState) & 0xFF) +         \
                                (((ucIndex) & 0xFF) << 8));      \
        }                                                        \
        while(0)

//*****************************************************************************
//
// USB_CDC_NOTIFY_LINE_STATE_CHANGE, wValue
//
// Note that the data returned alongside this notification are heavily
// dependent upon the call state being reported so no specific lengths or
// access macros are provided here.
//
//*****************************************************************************
#define USB_CDC_LINE_STATE_IDLE                         0x0000
#define USB_CDC_LINE_STATE_HOLD                         0x0001
#define USB_CDC_LINE_STATE_OFF_HOOK                     0x0002
#define USB_CDC_LINE_STATE_ON_HOOK                      0x0003

//*****************************************************************************
//
// USB_CDC_NOTIFY_CONNECTION_SPEED_CHANGE, Data
//
// Macro to populate the 8 byte data structure returned alongside this
// notification.
//
//*****************************************************************************
#define SetNotifyConnectionSpeedChange(pcBuf, ulUSBitRate, ulDSBitRate) \
        do                                                              \
        {                                                               \
            LONG(pcBuf) = ulUSBitRate;                                  \
            LONG((uint8 *)(pcBuf) + 4) = ulDSBitRate;           \
        }                                                               \
        while(0)

//*****************************************************************************
//
// Packed structure definitions for request/response data blocks
//
//*****************************************************************************

//*****************************************************************************
//
// All structures defined in this section of the header require byte packing of
// fields.  This is usually accomplished using the PACKED macro but, for IAR
// Embedded Workbench, this requires a pragma.
//
//*****************************************************************************
#if defined(ewarm) || defined(__IAR_SYSTEMS_ICC__)
#pragma pack(1)
#endif

//*****************************************************************************
//
//! USB_CDC_GET/SET_LINE_CODING request-specific data.
//
//*****************************************************************************
typedef struct
{
    //
    //! The data terminal rate in bits per second.
    //
    uint32 ulRate;

    //
    //! The number of stop bits.  Valid values are USB_CDC_STOP_BITS_1,
    //! USB_CDC_STOP_BITS_1_5 or USB_CDC_STOP_BITS_2
    //
    uint8 ucStop;

    //
    //! The parity setting.  Valid values are USB_CDC_PARITY_NONE,
    //! USB_CDC_PARITY_ODD, USB_CDC_PARITY_EVEN, USB_CDC_PARITY_MARK and
    //! USB_CDC_PARITY_SPACE.
    //
    uint8 ucParity;

    //
    //! The number of data bits per character.  Valid values are 5, 6, 7 and 8
    //! in this implementation.
    //
    uint8 ucDatabits;
}
PACKED tLineCoding;

//*****************************************************************************
//
// Return to default packing when using the IAR Embedded Workbench compiler.
//
//*****************************************************************************
#if defined(ewarm) || defined(__IAR_SYSTEMS_ICC__)
#pragma pack()
#endif

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __USBCDC_H__
