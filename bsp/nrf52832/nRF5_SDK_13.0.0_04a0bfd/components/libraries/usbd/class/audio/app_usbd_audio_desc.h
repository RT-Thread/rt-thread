/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
#ifndef APP_USBD_AUDIO_DESC_H__
#define APP_USBD_AUDIO_DESC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "app_usbd_descriptor.h"

/**
 * @defgroup app_usbd_audio_dsc USB Audio descriptors
 * @brief @tagAPI52840 Descriptors used in the USB Audio class.
 * @ingroup app_usbd_audio
 * @{
 */

/**
 * @brief Initializer of interface descriptor for AUDIO class
 *
 * @param interface_number Interface number
 * @param alt_setting      Interface alternate setting
 * @param ep_num           Number of endpoints
 * @param subclass         Audio subclass @ref app_usbd_audio_subclass_t
 * */
#define APP_USBD_AUDIO_INTERFACE_DSC(interface_number, alt_setting, ep_num, subclass)   \
    /*.bLength =            */ sizeof(app_usbd_descriptor_iface_t),                     \
    /*.bDescriptorType =    */ APP_USBD_DESCRIPTOR_INTERFACE,                           \
    /*.bInterfaceNumber =   */ (interface_number),                                      \
    /*.bAlternateSetting =  */ (alt_setting),                                           \
    /*.bNumEndpoints =      */ (ep_num),                                                \
    /*.bInterfaceClass =    */ APP_USBD_AUDIO_CLASS,                                    \
    /*.bInterfaceSubClass = */ (subclass),                                              \
    /*.bInterfaceProtocol = */ APP_USBD_AUDIO_CLASS_PROTOCOL_UNDEFINED,                 \
    /*.iInterface = 0,      */ 0x00,                                                    \

/**
 * @brief Initializer of isochronous endpoint descriptors for audio class
 *
 * @param ep            ISO endpoint id: @ref NRF_DRV_USBD_EPIN8, @ref NRF_DRV_USBD_EPOUT8
 * @param ep_size       Endpoint size (bytes)
 * @param interval      Endpoint interval (milliseconds)
 * @param refresh       Refresh value (usually 0)
 * @param synch_addr    Synch address (usually 0)
 * */
#define APP_USBD_AUDIO_ISO_EP_DSC(ep, ep_size, interval, refresh, synch_addr)       \
    /*.bLength =          */ sizeof(app_usbd_descriptor_ep_t) + 2,                  \
    /*.bDescriptorType =  */ APP_USBD_DESCRIPTOR_ENDPOINT,                          \
    /*.bEndpointAddress = */ ep,                                                    \
    /*.bmAttributes =     */ APP_USBD_DESCRIPTOR_EP_ATTR_TYPE_ISOCHRONOUS,          \
    /*.wMaxPacketSize =   */ APP_USBD_U16_TO_RAW_DSC(ep_size),                      \
    /*.bInterval =        */ (interval),                                            \
    /*.bRefresh =         */ (refresh),                                             \
    /*.bInterval =        */ (synch_addr),                                          \

/**
 * @brief Simplified version of @ref APP_USBD_AUDIO_ISO_EP_DSC for ISO IN endpoint
 */
#define APP_USBD_AUDIO_ISO_EP_IN_DSC(ep_size)           \
        APP_USBD_AUDIO_ISO_EP_DSC(NRF_DRV_USBD_EPIN8, ep_size, 1, 0, 0)

/**
 * @brief Simplified version of @ref APP_USBD_AUDIO_ISO_EP_DSC for ISO OUT endpoint
 */
#define APP_USBD_AUDIO_ISO_EP_OUT_DSC(ep_size)           \
        APP_USBD_AUDIO_ISO_EP_DSC(NRF_DRV_USBD_EPOUT8, ep_size, 1, 0, 0)

/**
 * @brief Initializer of @ref app_usbd_audio_ac_iface_header_desc_t
 *
 * @param descriptor_list   Descriptor list following audio interface header descriptor
 * @param ...               List of interfaces following audio control interface
 * */
#define APP_USBD_AUDIO_AC_IFACE_HEADER_DSC(descriptor_list, ...)                            \
    /*.bLength =            */ sizeof(app_usbd_audio_ac_iface_header_desc_t) +              \
                               (NUM_VA_ARGS(__VA_ARGS__)),                                  \
    /*.bDescriptorType =    */ APP_USBD_AUDIO_DESCRIPTOR_INTERFACE,                         \
    /*.bDescriptorSubtype = */ APP_USBD_AUDIO_AC_IFACE_SUBTYPE_HEADER,                      \
    /*.bcdADC =             */ APP_USBD_U16_TO_RAW_DSC(0x0100),                             \
    /*.wTotalLength =       */ APP_USBD_U16_TO_RAW_DSC(                                     \
                               sizeof((uint8_t[]){BRACKET_EXTRACT(descriptor_list)}) +      \
                               sizeof(app_usbd_audio_ac_iface_header_desc_t) +              \
                               (NUM_VA_ARGS(__VA_ARGS__))),                                 \
    /*.bInCollection =      */ (NUM_VA_ARGS(__VA_ARGS__)),                                  \
    /*.baInterfaceNr[] =    */ __VA_ARGS__,                                                 \


/**
 * @brief Initializer of @ref app_usbd_audio_input_terminal_desc_t
 *
 * @param terminal_id   Terminal ID
 * @param terminal_type Terminal type @ref app_usbd_audio_terminal_type_t
 * @param nr_channels   Number of channels
 * @param ch_config     CHannel config bitmask
 * */
#define APP_USBD_AUDIO_INPUT_TERMINAL_DSC(terminal_id, terminal_type, nr_channels, ch_config) \
    /*.bLength =            */ sizeof(app_usbd_audio_input_terminal_desc_t),                  \
    /*.bDescriptorType =    */ APP_USBD_AUDIO_DESCRIPTOR_INTERFACE,                           \
    /*.bDescriptorSubtype = */ APP_USBD_AUDIO_AC_IFACE_SUBTYPE_INPUT_TERMINAL,                \
    /*.bTerminalID =        */ (terminal_id),                                                 \
    /*.wTerminalType =      */ APP_USBD_U16_TO_RAW_DSC(terminal_type),                        \
    /*.bAssocTerminal =     */ 0,                                                             \
    /*.bNrChannels =        */ (nr_channels),                                                 \
    /*.wChannelConfig =     */ APP_USBD_U16_TO_RAW_DSC(ch_config),                            \
    /*.iChannelNames =      */ 0,                                                             \
    /*.iTerminal =          */ 0,                                                             \


/**
 * @brief Initializer of @ref app_usbd_audio_output_terminal_desc_t
 *
 * @param terminal_id   Terminal ID
 * @param terminal_type Terminal type @ref app_usbd_audio_terminal_type_t
 * @param source_id     Source ID
 * */
#define APP_USBD_AUDIO_OUTPUT_TERMINAL_DSC(terminal_id, terminal_type, source_id) \
    /*.bLength =            */ sizeof(app_usbd_audio_output_terminal_desc_t),     \
    /*.bDescriptorType =    */ APP_USBD_AUDIO_DESCRIPTOR_INTERFACE,               \
    /*.bDescriptorSubtype = */ APP_USBD_AUDIO_AC_IFACE_SUBTYPE_OUTPUT_TERNINAL,   \
    /*.bTerminalID =        */ (terminal_id),                                     \
    /*.wTerminalType =      */ APP_USBD_U16_TO_RAW_DSC(terminal_type),            \
    /*.bAssocTerminal =     */ 0,                                                 \
    /*.bSourceID =          */ (source_id),                                       \
    /*.iTerminal =          */ 0,                                                 \


/**
 * @brief Initializer of @ref app_usbd_audio_feature_unit_desc_t
 *
 * @param unit_id   Unit ID
 * @param source_id Source ID
 * @param ...       List of controls
 * */
#define APP_USBD_AUDIO_FEATURE_UNIT_DSC(unit_id, source_id, ...)             \
    /*.bLength =            */ sizeof(app_usbd_audio_feature_unit_desc_t) +  \
                               1 + (NUM_VA_ARGS(__VA_ARGS__)),               \
    /*.bDescriptorType =    */ APP_USBD_AUDIO_DESCRIPTOR_INTERFACE,          \
    /*.bDescriptorSubtype = */ APP_USBD_AUDIO_AC_IFACE_SUBTYPE_FEATURE_UNIT, \
    /*.bUnitID =            */ (unit_id),                                    \
    /*.bSourceID =          */ (source_id),                                  \
    /*.bControlSize =       */ sizeof(uint16_t),                             \
    /*.bmaControls[] =      */ __VA_ARGS__,                                  \
    /*.iFeature =           */ 0,                                            \


/**
 * @brief Initializer of @ref app_usbd_audio_as_iface_desc_t
 *
 * @param terminal_link Terminal link
 * @param delay         Delay
 * @param format_tag    Format TAG
 * */
#define APP_USBD_AUDIO_AS_IFACE_DSC(terminal_link, delay, format_tag)   \
    /*.bLength =            */ sizeof(app_usbd_audio_as_iface_desc_t),  \
    /*.bDescriptorType =    */ APP_USBD_AUDIO_DESCRIPTOR_INTERFACE,     \
    /*.bDescriptorSubtype = */ APP_USBD_AUDIO_AS_IFACE_SUBTYPE_GENERAL, \
    /*.bTerminalLink =      */ (terminal_link),                         \
    /*.bDelay =             */ (delay),                                 \
    /*.wFormatTag =         */ APP_USBD_U16_TO_RAW_DSC(format_tag),     \

/**
 * @brief Initializer of @ref app_usbd_audio_as_format_type_one_desc_t
 *
 * @param nr_channels       Number of channels
 * @param subframe_size     Subframe size
 * @param resolution        Bit resolution
 * @param freq_type         Frequency type
 * @param ...               List of frequencies
 * */
#define APP_USBD_AUDIO_AS_FORMAT_I_DSC(nr_channels, subframe_size, resolution, freq_type, ...) \
    /*.bLength =            */ sizeof(app_usbd_audio_as_format_type_one_desc_t) +              \
                               (NUM_VA_ARGS(__VA_ARGS__)),                                     \
    /*.bDescriptorType =    */ APP_USBD_AUDIO_DESCRIPTOR_INTERFACE,                            \
    /*.bDescriptorSubtype = */ APP_USBD_AUDIO_AS_IFACE_SUBTYPE_FORMAT_TYPE,                    \
    /*.bFormatType =        */ (1),                                                            \
    /*.bNrChannels =        */ (nr_channels),                                                  \
    /*.bSubframeSize =      */ (subframe_size),                                                \
    /*.bBitResolution =     */ (resolution),                                                   \
    /*.bSamFreqType =       */ (freq_type),                                                    \
    /*.tSamFreq =           */ __VA_ARGS__,                                                    \

/**
 * @brief Initializer of @ref app_usbd_audio_as_format_type_two_desc_t
 *
 * @param max_bitrate        Maximum bitrate
 * @param samples_per_frame  Samples per frame
 * @param freq_type          Frequency type
 * @param ...                List of frequencies
 * */
#define APP_USBD_AUDIO_AS_FORMAT_II_DSC(max_bitrate, samples_per_frame, freq_type, ...) \
    /*.bLength =            */ sizeof(app_usbd_audio_as_format_type_two_desc_t) +       \
                            (NUM_VA_ARGS(__VA_ARGS__)),                                 \
    /*.bDescriptorType =    */ APP_USBD_AUDIO_DESCRIPTOR_INTERFACE,                     \
    /*.bDescriptorSubtype = */ APP_USBD_AUDIO_AS_IFACE_SUBTYPE_FORMAT_TYPE,             \
    /*.bFormatType =        */ (2),                                                     \
    /*.wMaxBitRate =        */ APP_USBD_U16_TO_RAW_DSC(max_bitrate),                    \
    /*.wSamplesPerFrame =   */ APP_USBD_U16_TO_RAW_DSC(samples_per_frame),              \
    /*.bSamFreqType =       */ (freq_type),                                             \
    /*.tSamFreq =           */ __VA_ARGS__,                                             \

/**
* @brief Initializer of @ref app_usbd_audio_as_format_type_three_desc_t
 *
 * @param nr_channels       Number of channels
 * @param subframe_size     Subframe size
 * @param resolution        Bit resolution
 * @param freq_type         Frequency type
 * @param ...               List of frequencies
 * */
#define APP_USBD_AUDIO_AS_FORMAT_III_DSC(nr_channels, subframe_size, resolution, freq_type, ...) \
    /*.bLength =            */ sizeof(app_usbd_audio_as_format_type_three_desc_t) +              \
                            (NUM_VA_ARGS(__VA_ARGS__)),                                          \
    /*.bDescriptorType =    */ APP_USBD_AUDIO_DESCRIPTOR_INTERFACE,                              \
    /*.bDescriptorSubtype = */ APP_USBD_AUDIO_AS_IFACE_SUBTYPE_FORMAT_TYPE,                      \
    /*.bFormatType =        */ (3),                                                              \
    /*.bNrChannels =        */ (nr_channels),                                                    \
    /*.bSubframeSize =      */ (subframe_size),                                                  \
    /*.bBitResolution =     */ (resolution),                                                     \
    /*.bSamFreqType =       */ (freq_type),                                                      \
    /*.tSamFreq =           */ __VA_ARGS__,                                                      \


/**
 * @brief Initializer of @ref app_usbd_audio_as_endpoint_desc_t
 *
 * @param attributes       Endpoint attributes
 * @param lock_delay_units Lock delay units
 * @param lock_delay       Lock delay
 * */
#define APP_USBD_AUDIO_EP_GENERAL_DSC(attributes, lock_delay_units, lock_delay) \
    /*.bLength =            */ sizeof(app_usbd_audio_as_endpoint_desc_t),       \
    /*.bDescriptorType =    */ APP_USBD_AUDIO_DESCRIPTOR_ENDPOINT,              \
    /*.bDescriptorSubtype = */ APP_USBD_AUDIO_EP_SUBTYPE_GENERAL,               \
    /*.bmAttributes =       */ (attributes),                                    \
    /*.bLockDelayUnits =    */ (lock_delay_units),                              \
    /*.wLockDelay =         */ APP_USBD_U16_TO_RAW_DSC(lock_delay),             \

/**
 * @brief Macro to configure Audio Class control descriptor
 *
 * @param interface_number  Interface number
 * @param descriptor_list   List of descriptors after Audio interface header descriptor
 * @param interface_list    List of interfaces passed to @ref APP_USBD_AUDIO_AC_IFACE_HEADER_DSC
 * */
#define APP_USBD_AUDIO_CONTROL_DSC(interface_number, descriptor_list, interface_list)              \
        APP_USBD_AUDIO_INTERFACE_DSC(interface_number, 0, 0, APP_USBD_AUDIO_SUBCLASS_AUDIOCONTROL) \
        APP_USBD_AUDIO_AC_IFACE_HEADER_DSC(descriptor_list, BRACKET_EXTRACT(interface_list))       \
        BRACKET_EXTRACT(descriptor_list)


/**
 * @brief Macro to configure Audio Class streaming descriptor
 *
 * @param interface_number  Interface number
 * @param alt_setting       Alternate interface setting
 * @param ep_num            Number of endpoints
 */
#define APP_USBD_AUDIO_STREAMING_DSC(interface_number, alt_setting, ep_num)    \
        APP_USBD_AUDIO_INTERFACE_DSC(interface_number, alt_setting, ep_num,    \
                                    APP_USBD_AUDIO_SUBCLASS_AUDIOSTREAMING)

/**
 * @brief Macro to configure Audio Class MIDI streaming descriptor
 *
 * @param interface_number  Interface number
 * @param alt_setting       Alternate interface setting
 * @param ep_num            Number of endpoints
 */
#define APP_USBD_AUDIO_MIDI_STREAMING_DSC(interface_number, alt_setting, ep_num)  \
        APP_USBD_AUDIO_INTERFACE_DSC(interface_number, alt_setting, ep_num,       \
                                     APP_USBD_AUDIO_SUBCLASS_MIDISTREAMING)


/** @} */

#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_AUDIO_DESC_H__ */
