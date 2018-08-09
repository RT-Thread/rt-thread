/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
#ifndef APP_USBD_AUDIO_TYPES_H__
#define APP_USBD_AUDIO_TYPES_H__

#include "app_util.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup app_usbd_audio_types USB Audio types
 * @brief @tagAPI52840 Type definitions for the USB Audio class.
 * @ingroup app_usbd_audio
 * @{
 */

/** @brief Audio class definition in interface descriptor
 *
 *  Fixed value, @ref app_usbd_descriptor_iface_t::bInterfaceClass
 * */
#define  APP_USBD_AUDIO_CLASS                  0x01

/** @brief Audio class protocol definition in interface descriptor
 *
 *  Fixed value, @ref app_usbd_descriptor_iface_t::bInterfaceProtocol
 * */
#define  APP_USBD_AUDIO_CLASS_PROTOCOL_UNDEFINED  0x00

/**
 * @brief Audio subclass possible values
 *
 * @ref app_usbd_descriptor_iface_t::bInterfaceSubClass
 */
typedef enum {
    APP_USBD_AUDIO_SUBCLASS_UNDEFINED = 0x00, /**< UNDEFINED subclass      */
    APP_USBD_AUDIO_SUBCLASS_AUDIOCONTROL,     /**< AUDIOCONTROL subclass   */
    APP_USBD_AUDIO_SUBCLASS_AUDIOSTREAMING,   /**< AUDIOSTREAMING subclass */
    APP_USBD_AUDIO_SUBCLASS_MIDISTREAMING     /**< MIDISTREAMING  subclass */
} app_usbd_audio_subclass_t;


/**
 * @brief Audio class specific descriptor types
 */
typedef enum {
    APP_USBD_AUDIO_DESCRIPTOR_UNDEFINED     = 0x20, /**< UNDEFINED descriptor type     */
    APP_USBD_AUDIO_DESCRIPTOR_DEVICE        = 0x21, /**< DEVICE descriptor type        */
    APP_USBD_AUDIO_DESCRIPTOR_CONFIGURATION = 0x22, /**< CONFIGURATION descriptor type */
    APP_USBD_AUDIO_DESCRIPTOR_STRING        = 0x23, /**< STRING descriptor type        */
    APP_USBD_AUDIO_DESCRIPTOR_INTERFACE     = 0x24, /**< INTERFACE descriptor type     */
    APP_USBD_AUDIO_DESCRIPTOR_ENDPOINT      = 0x25, /**< ENDPOINT descriptor type      */
} app_usbd_audio_descriptor_type_t;


/**
 * @brief Audio control interface subtype
 */
typedef enum {
    APP_USBD_AUDIO_AC_IFACE_SUBTYPE_UNDEFINED = 0x00, /**< Audio control interface subtype UNDEFINED       */
    APP_USBD_AUDIO_AC_IFACE_SUBTYPE_HEADER,           /**< Audio control interface subtype HEADER          */
    APP_USBD_AUDIO_AC_IFACE_SUBTYPE_INPUT_TERMINAL,   /**< Audio control interface subtype INPUT_TERMINAL  */
    APP_USBD_AUDIO_AC_IFACE_SUBTYPE_OUTPUT_TERNINAL,  /**< Audio control interface subtype OUTPUT_TERNINAL */
    APP_USBD_AUDIO_AC_IFACE_SUBTYPE_MIXER_UNIT,       /**< Audio control interface subtype MIXER_UNIT      */
    APP_USBD_AUDIO_AC_IFACE_SUBTYPE_SELECTOR_UNIT,    /**< Audio control interface subtype SELECTOR_UNIT   */
    APP_USBD_AUDIO_AC_IFACE_SUBTYPE_FEATURE_UNIT,     /**< Audio control interface subtype FEATURE_UNIT    */
    APP_USBD_AUDIO_AC_IFACE_SUBTYPE_PROCESSING_UNIT,  /**< Audio control interface subtype PROCESSING_UNIT */
    APP_USBD_AUDIO_AC_IFACE_SUBTYPE_EXTENSION_UNIT,   /**< Audio control interface subtype EXTENSION_UNIT  */
} app_usbd_audio_ac_iface_subtype_t;

/**
 * @brief Audio streaming interface subtype
 */
typedef enum {
    APP_USBD_AUDIO_AS_IFACE_SUBTYPE_UNDEFINED = 0x00, /**< Audio streaming interface subtype UNDEFINED      */
    APP_USBD_AUDIO_AS_IFACE_SUBTYPE_GENERAL,          /**< Audio streaming interface subtype GENERAL        */
    APP_USBD_AUDIO_AS_IFACE_SUBTYPE_FORMAT_TYPE,      /**< Audio streaming interface subtype FORMAT_TYPE    */
    APP_USBD_AUDIO_AS_IFACE_SUBTYPE_FORMAT_SPECIFIC,  /**< Audio streaming interface subtype FORMAT_SPECIFIC*/
} app_usbd_audio_as_iface_subtype_t;


/**
 * @brief Audio class specific endpoint subtypes
 */
typedef enum {
    APP_USBD_AUDIO_EP_SUBTYPE_UNDEFINED = 0x00, /**< APP_USBD_AUDIO_EP_SUBTYPE_UNDEFINED */
    APP_USBD_AUDIO_EP_SUBTYPE_GENERAL,          /**< APP_USBD_AUDIO_EP_SUBTYPE_GENERAL   */
} app_usbd_audio_ep_subtype_t;

/**
 * @brief Audio class specific requests
 *
 * @ref nrf_drv_usbd_setup_t::bmRequestType
 */
typedef enum {
    APP_USBD_AUDIO_REQ_UNDEFINED = 0x00, /**< UNDEFINED request*/

    APP_USBD_AUDIO_REQ_SET_CUR   = 0x01, /**< SET_CUR request  */
    APP_USBD_AUDIO_REQ_SET_MIN   = 0x02, /**< SET_MIN request  */
    APP_USBD_AUDIO_REQ_SET_MAX   = 0x03, /**< SET_MAX request  */
    APP_USBD_AUDIO_REQ_SET_RES   = 0x04, /**< SET_RES request  */
    APP_USBD_AUDIO_REQ_SET_MEM   = 0x05, /**< SET_MEM request  */

    APP_USBD_AUDIO_REQ_GET_CUR   = 0x81, /**< GET_CUR request  */
    APP_USBD_AUDIO_REQ_GET_MIN   = 0x82, /**< GET_MIN request  */
    APP_USBD_AUDIO_REQ_GET_MAX   = 0x83, /**< GET_MAX request  */
    APP_USBD_AUDIO_REQ_GET_RES   = 0x84, /**< GET_RES request  */
    APP_USBD_AUDIO_REQ_GET_MEM   = 0x85, /**< GET_MEM request  */

    APP_USBD_AUDIO_REQ_GET_STAT  = 0xFF, /**< GET_STAT request */
} app_usbd_audio_req_type_t;

/**
 * @brief Audio class terminal types
 * */
typedef enum {
    /*USB terminals*/
    APP_USBD_AUDIO_TERMINAL_USB_UNDEFINED   = 0x0100,   /**< USB_UNDEFINED*/
    APP_USBD_AUDIO_TERMINAL_USB_STREAMING   = 0x0101,   /**< USB_STREAMING */
    APP_USBD_AUDIO_TERMINAL_USB_VENDOR_SPEC = 0x01FF,   /**< USB_VENDOR_SPEC*/

    /*Input terminals*/
    APP_USBD_AUDIO_TERMINAL_IN_UNDEFINED      = 0x0200, /**< UNDEFINED      */
    APP_USBD_AUDIO_TERMINAL_IN_MICROPHONE     = 0x0201, /**< MICROPHONE     */
    APP_USBD_AUDIO_TERMINAL_IN_DESKTOP_MIC    = 0x0202, /**< DESKTOP_MIC    */
    APP_USBD_AUDIO_TERMINAL_IN_PERSONAL_MIC   = 0x0203, /**< PERSONAL_MIC   */
    APP_USBD_AUDIO_TERMINAL_IN_OM_DIR_MIC     = 0x0204, /**< OM_DIR_MIC     */
    APP_USBD_AUDIO_TERMINAL_IN_MIC_ARRAY      = 0x0205, /**< MIC_ARRAY      */
    APP_USBD_AUDIO_TERMINAL_IN_PROC_MIC_ARRAY = 0x0205, /**< PROC_MIC_ARRAY */

    /*Output terminals*/
    APP_USBD_AUDIO_TERMINAL_OUT_UNDEFINED        = 0x0300, /**< UNDEFINED        */
    APP_USBD_AUDIO_TERMINAL_OUT_SPEAKER          = 0x0301, /**< SPEAKER          */
    APP_USBD_AUDIO_TERMINAL_OUT_HEADPHONES       = 0x0302, /**< HEADPHONES       */
    APP_USBD_AUDIO_TERMINAL_OUT_HEAD_AUDIO       = 0x0303, /**< HEAD_AUDIO       */
    APP_USBD_AUDIO_TERMINAL_OUT_DESKTOP_SPEAKER  = 0x0304, /**< DESKTOP_SPEAKER  */
    APP_USBD_AUDIO_TERMINAL_OUT_ROOM_SPEAKER     = 0x0305, /**< ROOM_SPEAKER     */
    APP_USBD_AUDIO_TERMINAL_OUT_COMM_SPEAKER     = 0x0306, /**< COMM_SPEAKER     */
    APP_USBD_AUDIO_TERMINAL_OUT_LOW_FREQ_SPEAKER = 0x0307, /**< LOW_FREQ_SPEAKER */

    /*Input/Output terminals*/
    APP_USBD_AUDIO_TERMINAL_IO_UNDEFINED              = 0x0400, /**< UNDEFINED              */
    APP_USBD_AUDIO_TERMINAL_IO_HANDSET                = 0x0401, /**< HANDSET                */
    APP_USBD_AUDIO_TERMINAL_IO_HEADSET                = 0x0402, /**< HEADSET                */
    APP_USBD_AUDIO_TERMINAL_IO_SPEAKERPHONE_ECHO_NONE = 0x0403, /**< SPEAKERPHONE_ECHO_NONE */
    APP_USBD_AUDIO_TERMINAL_IO_SPEAKERPHONE_ECHO_SUP  = 0x0404, /**< SPEAKERPHONE_ECHO_SUP  */
    APP_USBD_AUDIO_TERMINAL_IO_SPEAKERPHONE_ECHO_CAN  = 0x0405, /**< SPEAKERPHONE_ECHO_CAN  */
} app_usbd_audio_terminal_type_t;

/**
 * @brief Audio class control interface header descriptor
 */
typedef struct {
    uint8_t bLength;             //!< Length of the descriptor
    uint8_t bDescriptorType;     //!< Descriptor type @ref APP_USBD_AUDIO_DESCRIPTOR_INTERFACE
    uint8_t bDescriptorSubType;  //!< Descriptor subtype @ref APP_USBD_AUDIO_AC_IFACE_SUBTYPE_HEADER
    uint8_t bcdADC[2];           //!< BCD ADC
    uint8_t wTotalLength[2];     //!< Total interfaces length
    uint8_t bInCollection;       //!< Input collection
    uint8_t baInterfaceNr[];     //!< Interface number list
} app_usbd_audio_ac_iface_header_desc_t;


/**
 * @brief Possible values of input terminal channel config
 *
 * @ref app_usbd_audio_input_terminal_desc_t::wChannelConfig
 * */
typedef enum {
    APP_USBD_AUDIO_IN_TERM_CH_CONFIG_LEFT_FRONT         = (1u << 0),  /**< Channel config bit LEFT_FRONT      */
    APP_USBD_AUDIO_IN_TERM_CH_CONFIG_RIGHT_FRONT        = (1u << 1),  /**< Channel config bit RIGHT_FRONT     */
    APP_USBD_AUDIO_IN_TERM_CH_CONFIG_CENTER_FRONT       = (1u << 2),  /**< Channel config bit CENTER_FRONT    */
    APP_USBD_AUDIO_IN_TERM_CH_CONFIG_LOW_FREQ_ENH       = (1u << 3),  /**< Channel config bit LOW_FREQ_ENH    */
    APP_USBD_AUDIO_IN_TERM_CH_CONFIG_LEFT_SURROUND      = (1u << 4),  /**< Channel config bit LEFT_SURROUND   */
    APP_USBD_AUDIO_IN_TERM_CH_CONFIG_RIGHT_SURROUND     = (1u << 5),  /**< Channel config bit RIGHT_SURROUND  */
    APP_USBD_AUDIO_IN_TERM_CH_CONFIG_LEFT_OF_CENTER     = (1u << 6),  /**< Channel config bit LEFT_OF_CENTER  */
    APP_USBD_AUDIO_IN_TERM_CH_CONFIG_RIGHT_OF_CENTER    = (1u << 7),  /**< Channel config bit RIGHT_OF_CENTER */
    APP_USBD_AUDIO_IN_TERM_CH_CONFIG_SURROUND           = (1u << 8),  /**< Channel config bit SURROUND        */
    APP_USBD_AUDIO_IN_TERM_CH_CONFIG_SIDE_LEFT          = (1u << 9),  /**< Channel config bit SIDE_LEFT       */
    APP_USBD_AUDIO_IN_TERM_CH_CONFIG_SIDE_RIGHT         = (1u << 10), /**< Channel config bit SIDE_RIGHT      */
    APP_USBD_AUDIO_IN_TERM_CH_CONFIG_TOP                = (1u << 11), /**< Channel config bit TOP             */
} app_usbd_audio_in_term_ch_config_t;

/**
 * @brief Audio class input terminal descriptor
 */
typedef struct {
    uint8_t bLength;             //!< Length of the descriptor
    uint8_t bDescriptorType;     //!< Descriptor type @ref APP_USBD_AUDIO_DESCRIPTOR_INTERFACE
    uint8_t bDescriptorSubType;  //!< Descriptor subtype @ref APP_USBD_AUDIO_AC_IFACE_SUBTYPE_INPUT_TERMINAL
    uint8_t bTerminalID;         //!< Terminal ID
    uint8_t wTerminalType[2];    //!< Terminal type
    uint8_t bAssocTerminal;      //!< Association terminal
    uint8_t bNrChannels;         //!< Number of channels
    uint8_t wChannelConfig[2];   //!< Channel config
    uint8_t iChannelNames;       //!< Channel names
    uint8_t iTerminal;           //!< Terminal string ID
} app_usbd_audio_input_terminal_desc_t;

/**
 * @brief Audio class output terminal descriptor
 */
typedef struct {
    uint8_t bLength;            //!< Length of the descriptor
    uint8_t bDescriptorType;    //!< Descriptor type @ref APP_USBD_AUDIO_DESCRIPTOR_INTERFACE
    uint8_t bDescriptorSubType; //!< Descriptor subtype @ref APP_USBD_AUDIO_AC_IFACE_SUBTYPE_OUTPUT_TERNINAL
    uint8_t bTerminalID;        //!< Terminal ID
    uint8_t wTerminalType[2];   //!< Terminal type
    uint8_t bAssocTerminal;     //!< Association terminal
    uint8_t bSourceID;          //!< Source ID
    uint8_t iTerminal;          //!< Terminal string ID
} app_usbd_audio_output_terminal_desc_t;

/**
 * @brief Possible values of feature unit control field*/
typedef enum {
    APP_USBD_AUDIO_FEATURE_UNIT_CONTROL_MUTE       = (1u << 0), /**< Feature unit control bit MUTE      */
    APP_USBD_AUDIO_FEATURE_UNIT_CONTROL_VOLUME     = (1u << 1), /**< Feature unit control bit VOLUME    */
    APP_USBD_AUDIO_FEATURE_UNIT_CONTROL_BASS       = (1u << 2), /**< Feature unit control bit BASS      */
    APP_USBD_AUDIO_FEATURE_UNIT_CONTROL_MID        = (1u << 3), /**< Feature unit control bit MID       */
    APP_USBD_AUDIO_FEATURE_UNIT_CONTROL_TREBLE     = (1u << 4), /**< Feature unit control bit TREBLE    */
    APP_USBD_AUDIO_FEATURE_UNIT_CONTROL_GRAPH_EQ   = (1u << 5), /**< Feature unit control bit GRAPH_EQ  */
    APP_USBD_AUDIO_FEATURE_UNIT_CONTROL_AUTO_GAIN  = (1u << 6), /**< Feature unit control bit AUTO_GAIN */
    APP_USBD_AUDIO_FEATURE_UNIT_CONTROL_DELAY      = (1u << 7), /**< Feature unit control bit DELAY     */
    APP_USBD_AUDIO_FEATURE_UNIT_CONTROL_BASS_BOOST = (1u << 8), /**< Feature unit control bit BASS_BOOST*/
    APP_USBD_AUDIO_FEATURE_UNIT_CONTROL_LOUDNESS   = (1u << 9), /**< Feature unit control bit LOUDNESS  */
} app_usbd_audio_feature_unit_control_t;

/**
 * @brief Audio class feature unit descriptor
 */
typedef struct {
    uint8_t bLength;                //!< Length of the descriptor
    uint8_t bDescriptorType;        //!< Descriptor type @ref APP_USBD_AUDIO_DESCRIPTOR_INTERFACE
    uint8_t bDescriptorSubType;     //!< Descriptor subtype @ref APP_USBD_AUDIO_AC_IFACE_SUBTYPE_FEATURE_UNIT
    uint8_t bUnitID;                //!< Unit ID
    uint8_t bSourceID;              //!< Source ID
    uint8_t bControlSize;           //!< Control size
    uint8_t bmaControls[];          //!< Controls array
} app_usbd_audio_feature_unit_desc_t;

/**
 * @brief   Format tag in audio streaming interface descriptor
 *
 * @ref app_usbd_audio_as_iface_desc_t::wFormatTag
 * */
typedef enum {
    APP_USBD_AUDIO_AS_IFACE_FORMAT_TYPE_I_UNDEFINED = 0x0000, /**< AS format TYPE_I_UNDEFINED  */
    APP_USBD_AUDIO_AS_IFACE_FORMAT_PCM              = 0x0001, /**< AS format PCM               */
    APP_USBD_AUDIO_AS_IFACE_FORMAT_PCM8             = 0x0002, /**< AS format PCM8              */
    APP_USBD_AUDIO_AS_IFACE_FORMAT_IEEE_FLOAT       = 0x0003, /**< AS format IEEE_FLOAT        */
    APP_USBD_AUDIO_AS_IFACE_FORMAT_ALAW             = 0x0004, /**< AS format ALAW              */
    APP_USBD_AUDIO_AS_IFACE_FORMAT_MULAW            = 0x0005, /**< AS format MULAW             */

    APP_USBD_AUDIO_AS_IFACE_FORMAT_TYPE_II_UNDEFINED = 0x1000, /**< AS format TYPE_II_UNDEFINED  */
    APP_USBD_AUDIO_AS_IFACE_FORMAT_MPEG              = 0x1001, /**< AS format MPEG               */
    APP_USBD_AUDIO_AS_IFACE_FORMAT_AC3               = 0x1002, /**< AS format AC3                */

    APP_USBD_AUDIO_AS_IFACE_FORMAT_TYPE_III_UNDEFINED        = 0x2000, /**< AS format TYPE_III_UNDEFINED         */
    APP_USBD_AUDIO_AS_IFACE_FORMAT_IEC1937_AC_3              = 0x2001, /**< AS format IEC1937_AC_3               */
    APP_USBD_AUDIO_AS_IFACE_FORMAT_IEC1937_MPEG_1_LAYER1     = 0x2002, /**< AS format IEC1937_MPEG_1_LAYER1      */
    APP_USBD_AUDIO_AS_IFACE_FORMAT_IEC1937_MPEG_2_NOEXT      = 0x2003, /**< AS format IEC1937_MPEG_2_NOEXT       */
    APP_USBD_AUDIO_AS_IFACE_FORMAT_IEC1937_MPEG_2_EXT        = 0x2004, /**< AS format IEC1937_MPEG_2_EXT         */
    APP_USBD_AUDIO_AS_IFACE_FORMAT_IEC1937_MPEG_2_LAYER1_LS  = 0x2005, /**< AS format IEC1937_MPEG_2_LAYER1_LS   */
    APP_USBD_AUDIO_AS_IFACE_FORMAT_IEC1937_MPEG_2_LAYER23_LS = 0x2005, /**< AS format IEC1937_MPEG_2_LAYER23_LS  */
} app_usbd_audio_as_iface_format_tag_t;

/**
 * @brief Audio class audio streaming interface descriptor
 */
typedef struct {
    uint8_t bLength;                //!< Length of the descriptor
    uint8_t bDescriptorType;        //!< Descriptor type @ref APP_USBD_AUDIO_DESCRIPTOR_INTERFACE
    uint8_t bDescriptorSubType;     //!< Descriptor subtype @ref app_usbd_audio_ac_iface_subtype_t
    uint8_t bTerminalLink;          //!< Terminal link
    uint8_t bDelay;                 //!< Delay
    uint8_t wFormatTag[2];          //!< Format TAG
} app_usbd_audio_as_iface_desc_t;

/**
 * @brief Audio class audio streaming format type I descriptor
 */
typedef struct {
    uint8_t bLength;                //!< Length of the descriptor
    uint8_t bDescriptorType;        //!< Descriptor type @ref APP_USBD_AUDIO_DESCRIPTOR_INTERFACE
    uint8_t bDescriptorSubType;     //!< Descriptor subtype @ref app_usbd_audio_as_iface_subtype_t
    uint8_t bFormatType;            //!< Format type: fixed value 1
    uint8_t bNrChannels;            //!< Number of channels
    uint8_t bSubframeSize;          //!< Subframe size
    uint8_t bBitResolution;         //!< Bit resolution
    uint8_t bSamFreqType;           //!< Number of supported sampling frequencies
    uint8_t tSamFreq[];             //!< Number of supported sampling frequencies table (24 bit entries)
} app_usbd_audio_as_format_type_one_desc_t;


/**
 * @brief Audio class audio streaming format type II descriptor
 */
typedef struct {
    uint8_t bLength;                //!< Length of the descriptor
    uint8_t bDescriptorType;        //!< Descriptor type @ref APP_USBD_AUDIO_DESCRIPTOR_INTERFACE
    uint8_t bDescriptorSubType;     //!< Descriptor subtype @ref app_usbd_audio_as_iface_subtype_t
    uint8_t bFormatType;            //!< Format type: fixed value 2
    uint8_t wMaxBitRate[2];         //!< Maximum bitrate
    uint8_t wSamplesPerFrame[2];    //!< Samples per frame
    uint8_t bSamFreqType;           //!< Number of supported sampling frequencies
    uint8_t tSamFreq[];             //!< Number of supported sampling frequencies table (24 bit entries)
} app_usbd_audio_as_format_type_two_desc_t;

/**
 * @brief Audio class audio streaming format type III descriptor
 */
typedef struct {
    uint8_t bLength;              //!< Length of the descriptor
    uint8_t bDescriptorType;      //!< Descriptor type @ref APP_USBD_AUDIO_DESCRIPTOR_INTERFACE
    uint8_t bDescriptorSubType;   //!< Descriptor subtype @ref app_usbd_audio_as_iface_subtype_t
    uint8_t bFormatType;          //!< Format type: fixed value 1
    uint8_t bNrChannels;          //!< Number of channels
    uint8_t bSubframeSize;        //!< Subframe size
    uint8_t bBitResolution;       //!< Bit resolution
    uint8_t bSamFreqType;         //!< Number of supported sampling frequencies
    uint8_t tSamFreq[];           //!< Number of supported sampling frequencies table (24 bit entries)
} app_usbd_audio_as_format_type_three_desc_t;

/**
 * @brief Audio class audio endpoint descriptor
 */
typedef struct {
    uint8_t bLength;                //!< Length of the descriptor
    uint8_t bDescriptorType;        //!< Descriptor type @ref APP_USBD_AUDIO_DESCRIPTOR_ENDPOINT
    uint8_t bDescriptorSubType;     //!< Descriptor subtype @ref APP_USBD_AUDIO_EP_SUBTYPE_GENERAL
    uint8_t bmAttributes;           //!< Audio endpoint attributes
    uint8_t bLockDelayUnits;        //!< Lock delay units
    uint8_t wLockDelay[2];          //!< Lock delay value
} app_usbd_audio_as_endpoint_desc_t;

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_AUDIO_TYPES_H__ */

