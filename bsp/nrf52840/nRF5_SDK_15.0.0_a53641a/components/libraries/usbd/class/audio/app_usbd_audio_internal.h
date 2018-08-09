/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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
#ifndef APP_USBD_AUDIO_INTERNAL_H__
#define APP_USBD_AUDIO_INTERNAL_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup app_usbd_audio_internal USB Audio internals
 * @brief @tagAPI52840 USB Audio class internals.
 * @ingroup app_usbd_audio
 * @{
 */

/**
 * @brief Forward declaration of type defined by @ref APP_USBD_CLASS_TYPEDEF in audio class
 *
 */
APP_USBD_CLASS_FORWARD(app_usbd_audio);

/*lint -save -e165*/
/**
 * @brief Forward declaration of @ref app_usbd_audio_user_event_e
 *
 */
enum app_usbd_audio_user_event_e;

/*lint -restore*/

/**
 * @brief User event handler
 *
 * @param[in] p_inst    Class instance
 * @param[in] event     User event
 *
 */
typedef void (*app_usbd_audio_user_ev_handler_t)(app_usbd_class_inst_t const *  p_inst,
                                                 enum app_usbd_audio_user_event_e event);


/**
* @brief Audio subclass descriptor.
*/

typedef struct {
   size_t                size;
   uint8_t               type;
   uint8_t const * const p_data;
} app_usbd_audio_subclass_desc_t;

/**
 * @brief Audio class part of class instance data
 */
typedef struct {

    app_usbd_audio_subclass_desc_t const * const p_format_dsc;  //!< Audio class Format descriptor
    app_usbd_audio_subclass_desc_t const * const p_input_dsc;   //!< Audio class Input Terminal descriptor
    app_usbd_audio_subclass_desc_t const * const p_output_dsc;  //!< Audio class Output Terminal descriptor
    app_usbd_audio_subclass_desc_t const * const p_feature_dsc; //!< Audio class Feature Unit descriptor

    uint8_t  delay;     //!< Streaming delay
    uint16_t format;    //!< FormatTag (@ref app_usbd_audio_as_iface_format_tag_t)
    uint16_t ep_size;   //!< Endpoint size

    app_usbd_audio_subclass_t type_streaming;   //Streaming type MIDISTREAMING/AUDIOSTREAMING (@ref app_usbd_audio_subclass_t)

    app_usbd_audio_user_ev_handler_t user_ev_handler; //!< User event handler
} app_usbd_audio_inst_t;

/**
 * @brief Audio class request target
 */
typedef enum {
    APP_USBD_AUDIO_CLASS_REQ_IN,  /**< Audio class request IN              */
    APP_USBD_AUDIO_CLASS_REQ_OUT, /**< Audio class request OUT             */
    APP_USBD_AUDIO_EP_REQ_IN,     /**< Audio class endpoint request IN     */
    APP_USBD_AUDIO_EP_REQ_OUT,    /**< Audio class endpoint request OUT    */
} app_usbd_audio_class_req_target_t;

/**
 * @brief Audio class specific request handled via control endpoint
 */
typedef struct {
    app_usbd_audio_class_req_target_t req_target;   //!< Request target
    app_usbd_audio_req_type_t         req_type;     //!< Request type

    uint8_t  control;       //!< Request control field
    uint8_t  channel;       //!< Channel ID
    uint8_t  interface;     //!< Interface ID
    uint8_t  entity;        //!< Entity ID
    uint16_t length;        //!< Request payload length

    uint8_t payload[64];    //!< Request payload
} app_usbd_audio_req_t;


/**
 * @brief Audio class context
 *
 */
typedef struct {
    app_usbd_audio_req_t request;    //!< Audio class request
    bool                 streaming;  //!< Streaming flag
} app_usbd_audio_ctx_t;


/**
 * @brief Audio class configuration macro
 *
 * Used by @ref APP_USBD_AUDIO_GLOBAL_DEF
 *
 * @param iface_control     Interface number of audio control
 * @param iface_stream      Interface number of audio stream
 */
#define APP_USBD_AUDIO_CONFIG(iface_control, iface_stream)  \
        ((iface_control),                                   \
         (iface_stream, 0))

/**
 * @brief Only IN audio stream configuration
 *
 * @param iface_control     Interface number of audio control
 * @param iface_stream_in   Interface number of audio stream on IN endpoint
 */
#define APP_USBD_AUDIO_CONFIG_IN(iface_control, iface_stream_in)  \
        ((iface_control), (iface_stream_in, NRF_DRV_USBD_EPIN8))


/**
 * @brief Only OUT audio stream configuration
 *
 * @param iface_control     Interface number of audio control
 * @param iface_stream_out  Interface number of audio stream on OUT endpoint
 */
#define APP_USBD_AUDIO_CONFIG_OUT(iface_control, iface_stream_out)  \
        ((iface_control), (iface_stream_out, NRF_DRV_USBD_EPOUT8))

/**
 * @brief Specific class constant data for audio class
 *
 * @ref app_usbd_audio_inst_t
 */
#define APP_USBD_AUDIO_INSTANCE_SPECIFIC_DEC app_usbd_audio_inst_t inst;

/**
 * @brief Configures audio class instance
 *
 * @param user_event_handler        User event handler
 * @param format_descriptor         Audio class Format descriptor
 * @param input_descriptor          Audio class Input Terminal descriptor
 * @param output_descriptor         Audio class Output Terminal descriptor
 * @param feature_descriptor        Audio class Feature Unit descriptor
 * @param dlay                      Streaming delay
 * @param frmat                     FormatTag (@ref app_usbd_audio_as_iface_format_tag_t)
 * @param ep_siz                    Endpoint size
 * @param type_str                  Streaming type MIDISTREAMING/AUDIOSTREAMING
 */
 #define APP_USBD_AUDIO_INST_CONFIG(user_event_handler,             \
                                    format_descriptor,              \
                                    input_descriptor,               \
                                    output_descriptor,              \
                                    feature_descriptor,             \
                                    dlay,                           \
                                    frmat,                          \
                                    ep_siz,                         \
                                    type_str)                       \
    .inst = {                                                       \
         .user_ev_handler = user_event_handler,                     \
         .p_format_dsc    = format_descriptor,                      \
         .p_input_dsc     = input_descriptor,                       \
         .p_output_dsc    = output_descriptor,                      \
         .p_feature_dsc   = feature_descriptor,                     \
         .delay           = dlay,                                   \
         .format          = frmat,                                  \
         .ep_size         = ep_siz,                                 \
         .type_streaming  = type_str                                \
    }

/**
 * @brief Specific class data for audio class
 *
 * @ref app_usbd_audio_ctx_t
 */
#define APP_USBD_AUDIO_DATA_SPECIFIC_DEC app_usbd_audio_ctx_t ctx;


/**
 * @brief Audio class descriptors config macro
 *
 * @param interface_number Interface number
 * @param ...              Extracted endpoint list
 */
#define APP_USBD_AUDIO_DSC_CONFIG(interface_number, ...) {              \
    APP_USBD_AUDIO_INTERFACE_DSC(interface_number,                      \
                                 0,                                     \
                                 0,                                     \
                                 APP_USBD_AUDIO_SUBCLASS_AUDIOCONTROL)  \
    }

/**
 * @brief Public audio class interface
 *
 */
extern const app_usbd_class_methods_t app_usbd_audio_class_methods;

/**
 * @brief Global definition of @ref app_usbd_audio_t class
 *
 */
 #define APP_USBD_AUDIO_GLOBAL_DEF_INTERNAL(instance_name,          \
                                    interfaces_configs,             \
                                    user_ev_handler,                \
                                    format_descriptor,              \
                                    input_descriptor,               \
                                    output_descriptor,              \
                                    feature_descriptor,             \
                                    delay,                          \
                                    format,                         \
                                    ep_size,                        \
                                    type_str)                       \
    APP_USBD_CLASS_INST_GLOBAL_DEF(                                 \
        instance_name,                                              \
        app_usbd_audio,                                             \
        &app_usbd_audio_class_methods,                              \
        interfaces_configs,                                         \
        (APP_USBD_AUDIO_INST_CONFIG(user_ev_handler,                \
                                    format_descriptor,              \
                                    input_descriptor,               \
                                    output_descriptor,              \
                                    feature_descriptor,             \
                                    delay,                          \
                                    format,                         \
                                    ep_size,                        \
                                    type_str))                      \
    )


/** @} */


#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_AUDIO_INTERNAL_H__ */
