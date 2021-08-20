/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     zyh          the first version
 */

#ifndef __UAPI_USB_CDC_H__
#define __UAPI_USB_CDC_H__

#include <rtdef.h>

#define USB_CDC_SUBCLASS_ACM                (0x02U)
#define USB_CDC_SUBCLASS_ETHERNET           (0x06U)
#define USB_CDC_SUBCLASS_WHCM               (0x08U)
#define USB_CDC_SUBCLASS_DMM                (0x09U)
#define USB_CDC_SUBCLASS_MDLM               (0x0aU)
#define USB_CDC_SUBCLASS_OBEX               (0x0bU)
#define USB_CDC_SUBCLASS_EEM                (0x0cU)
#define USB_CDC_SUBCLASS_NCM                (0x0dU)
#define USB_CDC_SUBCLASS_MBIM               (0x0eU)

#define USB_CDC_PROTO_NONE                  (0x00U)

#define USB_CDC_ACM_PROTO_AT_V25TER         (0x01U)
#define USB_CDC_ACM_PROTO_AT_PCCA101        (0x02U)
#define USB_CDC_ACM_PROTO_AT_PCCA101_WAKE   (0x03U)
#define USB_CDC_ACM_PROTO_AT_GSM            (0x04U)
#define USB_CDC_ACM_PROTO_AT_3G             (0x05U)
#define USB_CDC_ACM_PROTO_AT_CDMA           (0x06U)
#define USB_CDC_ACM_PROTO_VENDOR            (0xffU)

#define USB_CDC_PROTO_EEM                   (0x07U)

#define USB_CDC_NCM_PROTO_NTB               (0x01U)
#define USB_CDC_MBIM_PROTO_NTB              (0x02U)

/*-------------------------------------------------------------------------*/

/*
 * Class-Specific descriptors ... there are a couple dozen of them
 */

#define USB_CDC_HEADER_TYPE                 (0x00U)    /* header_desc */
#define USB_CDC_CALL_MANAGEMENT_TYPE        (0x01U)    /* call_mgmt_descriptor */
#define USB_CDC_ACM_TYPE                    (0x02U)    /* acm_descriptor */
#define USB_CDC_UNION_TYPE                  (0x06U)    /* union_desc */
#define USB_CDC_COUNTRY_TYPE                (0x07U)
#define USB_CDC_NETWORK_TERMINAL_TYPE       (0x0aU)    /* network_terminal_desc */
#define USB_CDC_ETHERNET_TYPE               (0x0fU)    /* ether_desc */
#define USB_CDC_WHCM_TYPE                   (0x11U)
#define USB_CDC_MDLM_TYPE                   (0x12U)    /* mdlm_desc */
#define USB_CDC_MDLM_DETAIL_TYPE            (0x13U)    /* mdlm_detail_desc */
#define USB_CDC_DMM_TYPE                    (0x14U)
#define USB_CDC_OBEX_TYPE                   (0x15U)
#define USB_CDC_NCM_TYPE                    (0x1aU)
#define USB_CDC_MBIM_TYPE                   (0x1bU)
#define USB_CDC_MBIM_EXTENDED_TYPE          (0x1cU)

/* "Header Functional Descriptor" from CDC spec  5.2.3.1 */
struct usb_cdc_header_desc {
    rt_uint8_t  bLength;
    rt_uint8_t  bDescriptorType;
    rt_uint8_t  bDescriptorSubType;
    rt_le16_t   bcdCDC;
} __attribute__ ((packed));

/* "Call Management Descriptor" from CDC spec  5.2.3.2 */
struct usb_cdc_call_mgmt_descriptor {
    rt_uint8_t  bLength;
    rt_uint8_t  bDescriptorType;
    rt_uint8_t  bDescriptorSubType;
    rt_uint8_t  bmCapabilities;
#define USB_CDC_CALL_MGMT_CAP_CALL_MGMT     (0x01U)
#define USB_CDC_CALL_MGMT_CAP_DATA_INTF     (0x02U)
    rt_uint8_t  bDataInterface;
} __attribute__ ((packed));

/* "Abstract Control Management Descriptor" from CDC spec  5.2.3.3 */
struct usb_cdc_acm_descriptor {
    rt_uint8_t  bLength;
    rt_uint8_t  bDescriptorType;
    rt_uint8_t  bDescriptorSubType;
    rt_uint8_t  bmCapabilities;
} __attribute__ ((packed));

/* capabilities from 5.2.3.3 */

#define USB_CDC_COMM_FEATURE                (0x01U)
#define USB_CDC_CAP_LINE                    (0x02U)
#define USB_CDC_CAP_BRK                     (0x04U)
#define USB_CDC_CAP_NOTIFY                  (0x08U)

/* "Union Functional Descriptor" from CDC spec 5.2.3.8 */
struct usb_cdc_union_desc {
    rt_uint8_t  bLength;
    rt_uint8_t  bDescriptorType;
    rt_uint8_t  bDescriptorSubType;
    rt_uint8_t  bMasterInterface0;
    rt_uint8_t  bSlaveInterface0;
    /* ... and there could be other slave interfaces */
} __attribute__ ((packed));

/* "Country Selection Functional Descriptor" from CDC spec 5.2.3.9 */
struct usb_cdc_country_functional_desc {
    rt_uint8_t  bLength;
    rt_uint8_t  bDescriptorType;
    rt_uint8_t  bDescriptorSubType;
    rt_uint8_t  iCountryCodeRelDate;
    rt_le16_t   wCountyCode0;
    /* ... and there can be a lot of country codes */
} __attribute__ ((packed));

/* "Network Channel Terminal Functional Descriptor" from CDC spec 5.2.3.11 */
struct usb_cdc_network_terminal_desc {
    rt_uint8_t  bLength;
    rt_uint8_t  bDescriptorType;
    rt_uint8_t  bDescriptorSubType;
    rt_uint8_t  bEntityId;
    rt_uint8_t  iName;
    rt_uint8_t  bChannelIndex;
    rt_uint8_t  bPhysicalInterface;
} __attribute__ ((packed));

/* "Ethernet Networking Functional Descriptor" from CDC spec 5.2.3.16 */
struct usb_cdc_ether_desc {
    rt_uint8_t  bLength;
    rt_uint8_t  bDescriptorType;
    rt_uint8_t  bDescriptorSubType;
    rt_uint8_t  iMACAddress;
    rt_le32_t   bmEthernetStatistics;
    rt_le16_t   wMaxSegmentSize;
    rt_le16_t   wNumberMCFilters;
    rt_uint8_t  bNumberPowerFilters;
} __attribute__ ((packed));

/* "Telephone Control Model Functional Descriptor" from CDC WMC spec 6.3..3 */
struct usb_cdc_dmm_desc {
    rt_uint8_t  bFunctionLength;
    rt_uint8_t  bDescriptorType;
    rt_uint8_t  bDescriptorSubtype;
    rt_le16_t   bcdVersion;
    rt_le16_t   wMaxCommand;
} __attribute__ ((packed));

/* "MDLM Functional Descriptor" from CDC WMC spec 6.7.2.3 */
struct usb_cdc_mdlm_desc {
    rt_uint8_t  bLength;
    rt_uint8_t  bDescriptorType;
    rt_uint8_t  bDescriptorSubType;
    rt_le16_t   bcdVersion;
    rt_uint8_t  bGUID[16];
} __attribute__ ((packed));

/* "MDLM Detail Functional Descriptor" from CDC WMC spec 6.7.2.4 */
struct usb_cdc_mdlm_detail_desc {
    rt_uint8_t  bLength;
    rt_uint8_t  bDescriptorType;
    rt_uint8_t  bDescriptorSubType;
    /* type is associated with mdlm_desc.bGUID */
    rt_uint8_t  bGuidDescriptorType;
    rt_uint8_t  bDetailData[0];
} __attribute__ ((packed));

/* "OBEX Control Model Functional Descriptor" */
struct usb_cdc_obex_desc {
    rt_uint8_t  bLength;
    rt_uint8_t  bDescriptorType;
    rt_uint8_t  bDescriptorSubType;
    rt_le16_t   bcdVersion;
} __attribute__ ((packed));

/* "NCM Control Model Functional Descriptor" */
struct usb_cdc_ncm_desc {
    rt_uint8_t  bLength;
    rt_uint8_t  bDescriptorType;
    rt_uint8_t  bDescriptorSubType;
    rt_le16_t   bcdNcmVersion;
    rt_uint8_t  bmNetworkCapabilities;
} __attribute__ ((packed));

/* "MBIM Control Model Functional Descriptor" */
struct usb_cdc_mbim_desc {
    rt_uint8_t  bLength;
    rt_uint8_t  bDescriptorType;
    rt_uint8_t  bDescriptorSubType;
    rt_le16_t   bcdMBIMVersion;
    rt_le16_t   wMaxControlMessage;
    rt_uint8_t  bNumberFilters;
    rt_uint8_t  bMaxFilterSize;
    rt_le16_t   wMaxSegmentSize;
    rt_uint8_t  bmNetworkCapabilities;
} __attribute__ ((packed));

/* "MBIM Extended Functional Descriptor" from CDC MBIM spec 1.0 errata-1 */
struct usb_cdc_mbim_extended_desc {
    rt_uint8_t  bLength;
    rt_uint8_t  bDescriptorType;
    rt_uint8_t  bDescriptorSubType;
    rt_le16_t   bcdMBIMExtendedVersion;
    rt_uint8_t  bMaxOutstandingCommandMessages;
    rt_le16_t   wMTU;
} __attribute__ ((packed));

/*-------------------------------------------------------------------------*/

/*
 * Class-Specific Control Requests (6.2)
 *
 * section 3.6.2.1 table 4 has the ACM profile, for modems.
 * section 3.8.2 table 10 has the ethernet profile.
 *
 * Microsoft's RNDIS stack for Ethernet is a vendor-specific CDC ACM variant,
 * heavily dependent on the encapsulated (proprietary) command mechanism.
 */

#define USB_CDC_SEND_ENCAPSULATED_COMMAND           (0x00U)
#define USB_CDC_GET_ENCAPSULATED_RESPONSE           (0x01U)
#define USB_CDC_REQ_SET_LINE_CODING                 (0x20U)
#define USB_CDC_REQ_GET_LINE_CODING                 (0x21U)
#define USB_CDC_REQ_SET_CONTROL_LINE_STATE          (0x22U)
#define USB_CDC_REQ_SEND_BREAK                      (0x23U)
#define USB_CDC_SET_ETHERNET_MULTICAST_FILTERS      (0x40U)
#define USB_CDC_SET_ETHERNET_PM_PATTERN_FILTER      (0x41U)
#define USB_CDC_GET_ETHERNET_PM_PATTERN_FILTER      (0x42U)
#define USB_CDC_SET_ETHERNET_PACKET_FILTER          (0x43U)
#define USB_CDC_GET_ETHERNET_STATISTIC              (0x44U)
#define USB_CDC_GET_NTB_PARAMETERS                  (0x80U)
#define USB_CDC_GET_NET_ADDRESS                     (0x81U)
#define USB_CDC_SET_NET_ADDRESS                     (0x82U)
#define USB_CDC_GET_NTB_FORMAT                      (0x83U)
#define USB_CDC_SET_NTB_FORMAT                      (0x84U)
#define USB_CDC_GET_NTB_INPUT_SIZE                  (0x85U)
#define USB_CDC_SET_NTB_INPUT_SIZE                  (0x86U)
#define USB_CDC_GET_MAX_DATAGRAM_SIZE               (0x87U)
#define USB_CDC_SET_MAX_DATAGRAM_SIZE               (0x88U)
#define USB_CDC_GET_CRC_MODE                        (0x89U)
#define USB_CDC_SET_CRC_MODE                        (0x8aU)

/* Line Coding Structure from CDC spec 6.2.13 */
struct usb_cdc_line_coding {
    rt_le32_t    dwDTERate;
    rt_uint8_t    bCharFormat;
#define USB_CDC_1_STOP_BITS                         (0x00U)
#define USB_CDC_1_5_STOP_BITS                       (0x01U)
#define USB_CDC_2_STOP_BITS                         (0x02U)

    rt_uint8_t    bParityType;
#define USB_CDC_NO_PARITY                           (0x00U)
#define USB_CDC_ODD_PARITY                          (0x01U)
#define USB_CDC_EVEN_PARITY                         (0x02U)
#define USB_CDC_MARK_PARITY                         (0x03U)
#define USB_CDC_SPACE_PARITY                        (0x04U)

    rt_uint8_t    bDataBits;
} __attribute__ ((packed));

/* table 62; bits in multicast filter */
#define USB_CDC_PACKET_TYPE_PROMISCUOUS             (0x01U << 0)
#define USB_CDC_PACKET_TYPE_ALL_MULTICAST           (0x01U << 1) /* no filter */
#define USB_CDC_PACKET_TYPE_DIRECTED                (0x01U << 2)
#define USB_CDC_PACKET_TYPE_BROADCAST               (0x01U << 3)
#define USB_CDC_PACKET_TYPE_MULTICAST               (0x01U << 4) /* filtered */


/*-------------------------------------------------------------------------*/

/*
 * Class-Specific Notifications (6.3) sent by interrupt transfers
 *
 * section 3.8.2 table 11 of the CDC spec lists Ethernet notifications
 * section 3.6.2.1 table 5 specifies ACM notifications, accepted by RNDIS
 * RNDIS also defines its own bit-incompatible notifications
 */

#define USB_CDC_NOTIFY_NETWORK_CONNECTION           (0x00U)
#define USB_CDC_NOTIFY_RESPONSE_AVAILABLE           (0x01U)
#define USB_CDC_NOTIFY_SERIAL_STATE                 (0x20U)
#define USB_CDC_NOTIFY_SPEED_CHANGE                 (0x2aU)

struct usb_cdc_notification {
    rt_uint8_t  bmRequestType;
    rt_uint8_t  bNotificationType;
    rt_le16_t   wValue;
    rt_le16_t   wIndex;
    rt_le16_t   wLength;
} __attribute__ ((packed));

struct usb_cdc_speed_change {
    rt_le32_t   DLBitRRate;    /* contains the downlink bit rate (IN pipe) */
    rt_le32_t   ULBitRate;    /* contains the uplink bit rate (OUT pipe) */
} __attribute__ ((packed));

/*-------------------------------------------------------------------------*/

/*
 * Class Specific structures and constants
 *
 * CDC NCM NTB parameters structure, CDC NCM subclass 6.2.1
 *
 */

struct usb_cdc_ncm_ntb_parameters {
    rt_le16_t  wLength;
    rt_le16_t  bmNtbFormatsSupported;
    rt_le32_t  dwNtbInMaxSize;
    rt_le16_t  wNdpInDivisor;
    rt_le16_t  wNdpInPayloadRemainder;
    rt_le16_t  wNdpInAlignment;
    rt_le16_t  wPadding1;
    rt_le32_t  dwNtbOutMaxSize;
    rt_le16_t  wNdpOutDivisor;
    rt_le16_t  wNdpOutPayloadRemainder;
    rt_le16_t  wNdpOutAlignment;
    rt_le16_t  wNtbOutMaxDatagrams;
} __attribute__ ((packed));

/*
 * CDC NCM transfer headers, CDC NCM subclass 3.2
 */

#define USB_CDC_NCM_NTH16_SIGN        (0x484D434EU) /* NCMH */
#define USB_CDC_NCM_NTH32_SIGN        (0x686D636EU) /* ncmh */

struct usb_cdc_ncm_nth16 {
    rt_le32_t  dwSignature;
    rt_le16_t  wHeaderLength;
    rt_le16_t  wSequence;
    rt_le16_t  wBlockLength;
    rt_le16_t  wNdpIndex;
} __attribute__ ((packed));

struct usb_cdc_ncm_nth32 {
    rt_le32_t  dwSignature;
    rt_le16_t  wHeaderLength;
    rt_le16_t  wSequence;
    rt_le32_t  dwBlockLength;
    rt_le32_t  dwNdpIndex;
} __attribute__ ((packed));

/*
 * CDC NCM datagram pointers, CDC NCM subclass 3.3
 */

#define USB_CDC_NCM_NDP16_CRC_SIGN      (0x314D434EU)/* NCM1 */
#define USB_CDC_NCM_NDP16_NOCRC_SIGN    (0x304D434EU)/* NCM0 */
#define USB_CDC_NCM_NDP32_CRC_SIGN      (0x316D636EU)/* ncm1 */
#define USB_CDC_NCM_NDP32_NOCRC_SIGN    (0x306D636EU)/* ncm0 */

#define USB_CDC_MBIM_NDP16_IPS_SIGN     (0x00535049U) /* IPS<sessionID> : IPS0 for now */
#define USB_CDC_MBIM_NDP32_IPS_SIGN     (0x00737069U) /* ips<sessionID> : ips0 for now */
#define USB_CDC_MBIM_NDP16_DSS_SIGN     (0x00535344U) /* DSS<sessionID> */
#define USB_CDC_MBIM_NDP32_DSS_SIGN     (0x00737364U) /* dss<sessionID> */

/* 16-bit NCM Datagram Pointer Entry */
struct usb_cdc_ncm_dpe16 {
    rt_le16_t  wDatagramIndex;
    rt_le16_t  wDatagramLength;
} __attribute__((__packed__));

/* 16-bit NCM Datagram Pointer Table */
struct usb_cdc_ncm_ndp16 {
    rt_le32_t  dwSignature;
    rt_le16_t  wLength;
    rt_le16_t  wNextNdpIndex;
    struct usb_cdc_ncm_dpe16 dpe16[0];
} __attribute__ ((packed));

/* 32-bit NCM Datagram Pointer Entry */
struct usb_cdc_ncm_dpe32 {
    rt_le32_t  dwDatagramIndex;
    rt_le32_t  dwDatagramLength;
} __attribute__((__packed__));

/* 32-bit NCM Datagram Pointer Table */
struct usb_cdc_ncm_ndp32 {
    rt_le32_t  dwSignature;
    rt_le16_t  wLength;
    rt_le16_t  wReserved6;
    rt_le32_t  dwNextNdpIndex;
    rt_le32_t  dwReserved12;
    struct usb_cdc_ncm_dpe32 dpe32[0];
} __attribute__ ((packed));

/* CDC NCM subclass 3.2.1 and 3.2.2 */
#define USB_CDC_NCM_NDP16_INDEX_MIN                 (0x000CU)
#define USB_CDC_NCM_NDP32_INDEX_MIN                 (0x0010U)

/* CDC NCM subclass 3.3.3 Datagram Formatting */
#define USB_CDC_NCM_DATAGRAM_FORMAT_CRC             (0x30U)
#define USB_CDC_NCM_DATAGRAM_FORMAT_NOCRC           (0X31U)

/* CDC NCM subclass 4.2 NCM Communications Interface Protocol Code */
#define USB_CDC_NCM_PROTO_CODE_NO_ENCAP_COMMANDS    (0x00U)
#define USB_CDC_NCM_PROTO_CODE_EXTERN_PROTO         (0xFEU)

/* CDC NCM subclass 5.2.1 NCM Functional Descriptor, bmNetworkCapabilities */
#define USB_CDC_NCM_NCAP_ETH_FILTER                 (0x01U << 0)
#define USB_CDC_NCM_NCAP_NET_ADDRESS                (0x01U << 1)
#define USB_CDC_NCM_NCAP_ENCAP_COMMAND              (0x01U << 2)
#define USB_CDC_NCM_NCAP_MAX_DATAGRAM_SIZE          (0x01U << 3)
#define USB_CDC_NCM_NCAP_CRC_MODE                   (0x01U << 4)
#define    USB_CDC_NCM_NCAP_NTB_INPUT_SIZE          (0x01U << 5)

/* CDC NCM subclass Table 6-3: NTB Parameter Structure */
#define USB_CDC_NCM_NTB16_SUPPORTED                 (0x01U << 0)
#define USB_CDC_NCM_NTB32_SUPPORTED                 (0x01U << 1)

/* CDC NCM subclass Table 6-3: NTB Parameter Structure */
#define USB_CDC_NCM_NDP_ALIGN_MIN_SIZE              (0x04U)
#define USB_CDC_NCM_NTB_MAX_LENGTH                  (0x1CU)

/* CDC NCM subclass 6.2.5 SetNtbFormat */
#define USB_CDC_NCM_NTB16_FORMAT                    (0x00U)
#define USB_CDC_NCM_NTB32_FORMAT                    (0x01U)

/* CDC NCM subclass 6.2.7 SetNtbInputSize */
#define USB_CDC_NCM_NTB_MIN_IN_SIZE                 (2048)
#define USB_CDC_NCM_NTB_MIN_OUT_SIZE                (2048)

/* NTB Input Size Structure */
struct usb_cdc_ncm_ndp_input_size {
    rt_le32_t  dwNtbInMaxSize;
    rt_le16_t  wNtbInMaxDatagrams;
    rt_le16_t  wReserved;
} __attribute__ ((packed));

/* CDC NCM subclass 6.2.11 SetCrcMode */
#define USB_CDC_NCM_CRC_NOT_APPENDED                (0x00U)
#define USB_CDC_NCM_CRC_APPENDED                    (0x01U)

#endif /* __UAPI_USB_CDC_H__ */
