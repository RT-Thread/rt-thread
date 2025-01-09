/*!
    \file    usb_cdc.h
    \brief   the header file of communication device class standard

    \version 2024-07-31, V1.1.0, firmware for GD32F5xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#ifndef USB_CDC_H
#define USB_CDC_H

#include "usb_ch9_std.h"

/* communications device class code */
#define USB_CLASS_CDC                                       0x02U

/* communications interface class control protocol codes */
#define USB_CDC_PROTOCOL_NONE                               0x00U               /*!< CDC none protocol */
#define USB_CDC_PROTOCOL_AT                                 0x01U               /*!< CDC AT protocol */
#define USB_CDC_PROTOCOL_VENDOR                             0xFFU               /*!< CDC vendor protocol */

/* data interface class code */
#define USB_CLASS_DATA                                      0x0AU

#define USB_DESCTYPE_CDC_ACM                                0x21U               /*!< CDC descriptor type */
#define USB_DESCTYPE_CS_INTERFACE                           0x24U               /*!< CDC interface descriptor type */

#define USB_CDC_ACM_CONFIG_DESC_SIZE                        0x43U               /*!< CDC configuration descriptor size */

/* class-specific notification codes for pstn subclasses */
#define USB_CDC_NOTIFY_SERIAL_STATE                         0x20U

/* class-specific request codes */
#define SEND_ENCAPSULATED_COMMAND                           0x00U               /*!< send encapsulated command request */
#define GET_ENCAPSULATED_RESPONSE                           0x01U               /*!< get encapsulated response request */
#define SET_COMM_FEATURE                                    0x02U               /*!< set command feature request */
#define GET_COMM_FEATURE                                    0x03U               /*!< get command feature request */
#define CLEAR_COMM_FEATURE                                  0x04U               /*!< clear command feature request */

#define SET_AUX_LINE_STATE                                  0x10U               /*!< set AUX line state code */
#define SET_HOOK_STATE                                      0x11U               /*!< set hook state code */
#define PULSE_SETUP                                         0x12U               /*!< pulse setup code */
#define SEND_PULSE                                          0x13U               /*!< send pulse code */
#define SET_PULSE_TIME                                      0x14U               /*!< set pulse time code */
#define RING_AUX_JACK                                       0x15U               /*!< ring AUX jack code */

#define SET_LINE_CODING                                     0x20U               /*!< set line coding request */
#define GET_LINE_CODING                                     0x21U               /*!< get line coding request */
#define SET_CONTROL_LINE_STATE                              0x22U               /*!< set control line state request */
#define SEND_BREAK                                          0x23U               /*!< send break request */
#define NO_CMD                                              0xFFU               /*!< no command request */

#define SET_RINGER_PARMS                                    0x30U               /*!< set ringer parameter */
#define GET_RINGER_PARMS                                    0x31U               /*!< get ringer parameter */
#define SET_OPERATION_PARMS                                 0x32U               /*!< set operation parameter */
#define GET_OPERATION_PARMS                                 0x33U               /*!< get ringer parameter */
#define SET_LINE_PARMS                                      0x34U               /*!< set line parameter */
#define GET_LINE_PARMS                                      0x35U               /*!< get ringer parameter */
#define DIAL_DIGITS                                         0x36U               /*!< dial digits */
#define SET_UNIT_PARAMETER                                  0x37U               /*!< set unit parameter */
#define GET_UNIT_PARAMETER                                  0x38U               /*!< get unit parameter */
#define CLEAR_UNIT_PARAMETER                                0x39U               /*!< clear unit parameter */
#define GET_PROFILE                                         0x3AU               /*!< get profile */

#define SET_ETHERNET_MULTICAST_FILTERS                      0x40U               /*!< set ethernet muilcast filters */
#define SET_ETHERNET_POWER_MANAGEMENT_PATTERN FILTER        0x41U               /*!< set ethernet power management pattern filter */
#define GET_ETHERNET_POWER_MANAGEMENT_PATTERN FILTER        0x42U               /*!< get ethernet power management pattern filter */
#define SET_ETHERNET_PACKET_FILTER                          0x43U               /*!< set ethernet power pocket filter */
#define GET_ETHERNET_STATISTIC                              0x44U               /*!< get ethernet statistic */

#define SET_ATM_DATA_FORMAT                                 0x50U               /*!< set ATM data format */
#define GET_ATM_DEVICE_STATISTICS                           0x51U               /*!< get ATM device statistics */
#define SET_ATM_DEFAULT_VC                                  0x52U               /*!< set ATM default VC */
#define GET_ATM_VC_STATISTICS                               0x53U               /*!< get ATM VC statistics */

/* wValue for set control line state */
#define CDC_ACTIVATE_CARRIER_SIGNAL_RTS                     0x0002U             /*!< CDC activate carrier signal RTS */
#define CDC_DEACTIVATE_CARRIER_SIGNAL_RTS                   0x0000U             /*!< CDC deactivate carrier signal RTS */
#define CDC_ACTIVATE_SIGNAL_DTR                             0x0001U             /*!< CDC activate signal DTR */
#define CDC_DEACTIVATE_SIGNAL_DTR                           0x0000U             /*!< CDC deactivate signal DTR */

/* CDC subclass code */
enum usb_cdc_subclass {
    USB_CDC_SUBCLASS_RESERVED = 0U,  /*!< reserved */
    USB_CDC_SUBCLASS_DLCM,           /*!< direct line control mode */
    USB_CDC_SUBCLASS_ACM,            /*!< abstract control mode */
    USB_CDC_SUBCLASS_TCM,            /*!< telephone control mode */
    USB_CDC_SUBCLASS_MCM,            /*!< multichannel control model */
    USB_CDC_SUBCLASS_CCM,            /*!< CAPI control model */
    USB_CDC_SUBCLASS_ENCM,           /*!< ethernet networking control model */
    USB_CDC_SUBCLASS_ANCM            /*!< ATM networking control model */
};

#pragma pack(1)

/* cdc acm line coding structure */
typedef struct {
    uint32_t dwDTERate;                   /*!< data terminal rate */
    uint8_t  bCharFormat;                 /*!< stop bits */
    uint8_t  bParityType;                 /*!< parity */
    uint8_t  bDataBits;                   /*!< data bits */
} acm_line;

/* notification structure */
typedef struct {
    uint8_t bmRequestType;                /*!< type of request */
    uint8_t bNotification;                /*!< communication interface class notifications */
    uint16_t wValue;                      /*!< value of notification */
    uint16_t wIndex;                      /*!< index of interface */
    uint16_t wLength;                     /*!< length of notification data */
} acm_notification;

typedef struct {
    usb_desc_header header;               /*!< descriptor header, including type and size. */
    uint8_t   bDescriptorSubtype;         /*!< bDescriptorSubtype: header function descriptor */
    uint16_t  bcdCDC;                     /*!< bcdCDC: low byte of spec release number (CDC1.10) */
} usb_desc_header_func;

typedef struct {
    usb_desc_header header;               /*!< descriptor header, including type and size. */
    uint8_t  bDescriptorSubtype;          /*!< bDescriptorSubtype:  call management function descriptor */
    uint8_t  bmCapabilities;              /*!< bmCapabilities: D0 is reset, D1 is ignored */
    uint8_t  bDataInterface;              /*!< bDataInterface: 1 interface used for call management */
} usb_desc_call_managment_func;

typedef struct {
    usb_desc_header header;               /*!< descriptor header, including type and size. */
    uint8_t  bDescriptorSubtype;          /*!< bDescriptorSubtype: abstract control management descriptor */
    uint8_t  bmCapabilities;              /*!< bmCapabilities: D1 */
} usb_desc_acm_func;

typedef struct {
    usb_desc_header header;               /*!< descriptor header, including type and size. */
    uint8_t  bDescriptorSubtype;          /*!< bDescriptorSubtype: union function descriptor */
    uint8_t  bMasterInterface;            /*!< bMasterInterface: communication class interface */
    uint8_t  bSlaveInterface0;            /*!< bSlaveInterface0: data class interface */
} usb_desc_union_func;

#pragma pack()

typedef struct {
    usb_desc_config                  config;                     /*!< configure descriptor */
    usb_desc_itf                     cmd_itf;                    /*!< CDC cmd interface descriptor */
    usb_desc_header_func             cdc_header;                 /*!< CDC header function descriptor */
    usb_desc_call_managment_func     cdc_call_managment;         /*!< CDC call management descriptor */
    usb_desc_acm_func                cdc_acm;                    /*!< CDC acm descriptor */
    usb_desc_union_func              cdc_union;                  /*!< CDC union function descriptor */
    usb_desc_ep                      cdc_cmd_endpoint;           /*!< CDC cmd endpoint descriptor */
    usb_desc_itf                     cdc_data_interface;         /*!< CDC data interface descriptor */
    usb_desc_ep                      cdc_out_endpoint;           /*!< CDC OUT endpoint descriptor */
    usb_desc_ep                      cdc_in_endpoint;            /*!< CDC IN endpoint descriptor */
} usb_cdc_desc_config_set;

#endif /* USB_CDC_H */
