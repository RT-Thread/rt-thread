/***************************************************************************//**
* \file cy_usb_dev_audio_descr.h
* \version 2.10
*
* Provides Audio class-specific descriptor defines.
*
********************************************************************************
* \copyright
* (c) 2018-2021, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USB_DEV_AUDIO_DESCR_H)
#define CY_USB_DEV_AUDIO_DESCR_H

#if (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS))

#if defined(__cplusplus)
extern "C" {
#endif


/*******************************************************************************
*                             USB AUDIO
*******************************************************************************/

/** \cond INTERNAL */
/**
* Audio Interface Class, Subclass and Protocol Codes
*/
#define CY_USB_DEV_AUDIO_CLASS                      (0x01U)
#define CY_USB_DEV_AUDIO_SUBCLASS_UNDEFINED         (0x00U)
#define CY_USB_DEV_AUDIO_SUBCLASS_AUDIO_CONTROL     (0x01U)
#define CY_USB_DEV_AUDIO_SUBCLASS_AUDIO_STREAMING   (0x02U)
#define CY_USB_DEV_AUDIO_SUBCLASS_MIDI_STREAMING    (0x03U)
#define CY_USB_DEV_AUDIO_PROTOCOL_UNDEFINED         (0x00U)

/**
* Audio Class-Specific Descriptor Types
*/
#define CY_USB_DEV_AUDIO_CS_UNDEFINED               (0x20U)
#define CY_USB_DEV_AUDIO_CS_DEVICE                  (0x21U)
#define CY_USB_DEV_AUDIO_CS_CONFIGURATION           (0x22U)
#define CY_USB_DEV_AUDIO_CS_STRING                  (0x23U)
#define CY_USB_DEV_AUDIO_CS_INTERFACE               (0x24U)
#define CY_USB_DEV_AUDIO_CS_ENDPOINT                (0x25U)


/*******************************************************************************
*                       USB AUDIO version 1.0
*******************************************************************************/

/**
* Audio Class-Specific AC Interface Descriptor Subtypes
*/
#define CY_USB_DEV_AUDIO_AC_DESCRIPTOR_UNDEFINED    (0x00U)
#define CY_USB_DEV_AUDIO_HEADER                     (0x01U)
#define CY_USB_DEV_AUDIO_INPUT_TERMINAL             (0x02U)
#define CY_USB_DEV_AUDIO_OUTPUT_TERMINAL            (0x03U)
#define CY_USB_DEV_AUDIO_MIXER_UNIT                 (0x04U)
#define CY_USB_DEV_AUDIO_SELECTOR_UNIT              (0x05U)
#define CY_USB_DEV_AUDIO_FEATURE_UNIT               (0x06U)
#define CY_USB_DEV_AUDIO_PROCESSING_UNIT            (0x07U)
#define CY_USB_DEV_AUDIO_EXTENSION_UNIT             (0x08U)

/**
* Audio Class-Specific AS Interface Descriptor Subtypes
*/
#define CY_USB_DEV_AUDIO_AS_DESCRIPTOR_UNDEFINED    (0x00U)
#define CY_USB_DEV_AUDIO_AS_GENERAL                 (0x01U)
#define CY_USB_DEV_AUDIO_FORMAT_TYPE                (0x02U)
#define CY_USB_DEV_AUDIO_FORMAT_SPECIFIC            (0x03U)

/**
* Processing Unit Process Types
*/
#define CY_USB_DEV_AUDIO_PROCESS_UNDEFINED          (0x00U)
#define CY_USB_DEV_AUDIO_UP_DOWNMIX_PROCESS         (0x01U)
#define CY_USB_DEV_AUDIO_DOLBY_PROLOGIC_PROCESS     (0x02U)
#define CY_USB_DEV_AUDIO_3D_STEREO_EXTENDER_PROCESS (0x03U)
#define CY_USB_DEV_AUDIO_REVERBERATION_PROCESS      (0x04U)
#define CY_USB_DEV_AUDIO_CHORUS_PROCESS             (0x05U)
#define CY_USB_DEV_AUDIO_DYN_RANGE_COMP_PROCESS     (0x06U)

/**
* Audio Class-Specific Endpoint Descriptor Subtypes
*/
#define CY_USB_DEV_AUDIO_DESCRIPTOR_UNDEFINED       (0x00U)
#define CY_USB_DEV_AUDIO_EP_GENERAL                 (0x01U)

/**
* Terminal Control Selectors
*/
#define USB_AUDIO_TE_CONTROL_UNDEFINED              (0x00U)
#define USB_AUDIO_COPY_PROTECT_CONTROL              (0x01U)

/**
* Feature Unit Control Selectors
*/
#define CY_USB_DEV_AUDIO_FU_CONTROL_UNDEFINED       (0x00U)
#define CY_USB_DEV_AUDIO_MUTE_CONTROL               (0x01U)
#define CY_USB_DEV_AUDIO_VOLUME_CONTROL             (0x02U)
#define CY_USB_DEV_AUDIO_BASS_CONTROL               (0x03U)
#define CY_USB_DEV_AUDIO_MID_CONTROL                (0x04U)
#define CY_USB_DEV_AUDIO_TREBLE_CONTROL             (0x05U)
#define CY_USB_DEV_AUDIO_GRAPHIC_EQUALIZER_CONTROL  (0x06U)
#define CY_USB_DEV_AUDIO_AUTOMATIC_GAIN_CONTROL     (0x07U)
#define CY_USB_DEV_AUDIO_DELAY_CONTROL              (0x08U)
#define CY_USB_DEV_AUDIO_BASS_BOOST_CONTROL         (0x09U)
#define CY_USB_DEV_AUDIO_LOUDNESS_CONTROL           (0x0AU)

/**
* Endpoint Control Selectors
*/
#define CY_USB_DEV_AUDIO_EP_CONTROL_UNDEFINED       (0x00U)
#define CY_USB_DEV_AUDIO_SAMPLING_FREQ_CONTROL      (0x01U)
#define CY_USB_DEV_AUDIO_PITCH_CONTROL              (0x02U)

/**
* Descriptor Sizes
*/
#define CY_USB_DEV_AUDIO_AC_HEADER_SIZE(a)          (8U + (a))
#define CY_USB_DEV_AUDIO_AC_IN_TERM_LENGTH          (0x0CU)
#define CY_USB_DEV_AUDIO_AC_FE_UNIT_LENGTH          (0x09U)
#define CY_USB_DEV_AUDIO_AC_OUT_TERM_LENGTH         (0x09U)
#define CY_USB_DEV_AUDIO_AS_GEN_IF_LENGTH           (0x07U)
#define CY_USB_DEV_AUDIO_AS_FORMAT_I_LENGTH         (0x0BU)

/**
* Endpoint Control Selectors (AUDIO Table A-19)
*/
#define CY_USB_DEV_AUDIO_CS_SAMPLING_FREQ_CTRL   (0x01U)  /**< Audio v1.0: sample frequency control selector */
#define CY_USB_DEV_AUDIO_CS_PITCH_CTRL           (0x02U)  /**< Audio v1.0: pitch control selector */

/**
* Feature Unit Control Selectors (AUDIO Table A-11)
*/
#define CY_USB_DEV_AUDIO_CS_MUTE_CONTROL               (0x01U)    /**< Audio v1.0: mute control selector */
#define CY_USB_DEV_AUDIO_CS_VOLUME_CONTROL             (0x02U)    /**< Audio v1.0: volume control selector */
#define CY_USB_DEV_AUDIO_CS_BASS_CONTROL               (0x03U)    /**< Audio v1.0: bass control selector */
#define CY_USB_DEV_AUDIO_CS_MID_CONTROL                (0x04U)    /**< Audio v1.0: mid control selector */
#define CY_USB_DEV_AUDIO_CS_TREBLE_CONTROL             (0x05U)    /**< Audio v1.0: treble control selector */
#define CY_USB_DEV_AUDIO_CS_GRAPHIC_EQUALIZER_CONTROL  (0x06U)    /**< Audio v1.0: graphic equalizer control selector */
#define CY_USB_DEV_AUDIO_CS_AUTOMATIC_GAIN_CONTROL     (0x07U)    /**< Audio v1.0: automatic gain control selector */
#define CY_USB_DEV_AUDIO_CS_DELAY_CONTROL              (0x08U)    /**< Audio v1.0: delay control selector */
#define CY_USB_DEV_AUDIO_CS_BASS_BOOST_CONTROL         (0x09U)    /**< Audio v1.0: bass control selector */
#define CY_USB_DEV_AUDIO_CS_LOUDNESS_CONTROL           (0x0AU)    /**< Audio v1.0: loudness control selector */


/*******************************************************************************
*                          USB AUDIO version 1.0
*******************************************************************************/

/**
* Audio Interface Protocol Codes
*/
#define CY_USB_DEV_AUDIO2_INTERFACE_PROTOCOL_UNDEFINED  (0x00U)
#define CY_USB_DEV_AUDIO2_IP_VERSION_02_00              (0x20U)

/**
* A.7 Audio Function Category Codes
*/
#define CY_USB_DEV_AUDIO2_FUNCTION_SUBCLASS_UNDEFINED   (0x00U)
#define CY_USB_DEV_AUDIO2_FUNCTION_DESKTOP_SPEAKER      (0x01U)
#define CY_USB_DEV_AUDIO2_FUNCTION_HOME_THEATER         (0x02U)
#define CY_USB_DEV_AUDIO2_FUNCTION_MICROPHONE           (0x03U)
#define CY_USB_DEV_AUDIO2_FUNCTION_HEADSET              (0x04U)
#define CY_USB_DEV_AUDIO2_FUNCTION_TELEPHONE            (0x05U)
#define CY_USB_DEV_AUDIO2_FUNCTION_CONVERTER            (0x06U)
#define CY_USB_DEV_AUDIO2_FUNCTION_SOUND_RECORDER       (0x07U)
#define CY_USB_DEV_AUDIO2_FUNCTION_IO_BOX               (0x08U)
#define CY_USB_DEV_AUDIO2_FUNCTION_MUSICAL_INSTRUMENT   (0x09U)
#define CY_USB_DEV_AUDIO2_FUNCTION_PRO_AUDIO            (0x0AU)
#define CY_USB_DEV_AUDIO2_FUNCTION_AUDIO_VIDEO          (0x0BU)
#define CY_USB_DEV_AUDIO2_FUNCTION_CONTROL_PANEL        (0x0CU)
#define CY_USB_DEV_AUDIO2_FUNCTION_OTHER                (0xFFU)

/**
* A.9 Audio Class-Specific AC Interface Descriptor Subtypes
*/
#define CY_USB_DEV_AUDIO2_AC_DESCRIPTOR_UNDEFINED       (0x00U)
#define CY_USB_DEV_AUDIO2_HEADER                        (0x01U)
#define CY_USB_DEV_AUDIO2_INPUT_TERMINAL                (0x02U)
#define CY_USB_DEV_AUDIO2_OUTPUT_TERMINAL               (0x03U)
#define CY_USB_DEV_AUDIO2_MIXER_UNIT                    (0x04U)
#define CY_USB_DEV_AUDIO2_SELECTOR_UNIT                 (0x05U)
#define CY_USB_DEV_AUDIO2_FEATURE_UNIT                  (0x06U)
#define CY_USB_DEV_AUDIO2_EFFECT_UNIT                   (0x07U)
#define CY_USB_DEV_AUDIO2_PROCESSING_UNIT_V2            (0x08U)
#define CY_USB_DEV_AUDIO2_EXTENSION_UNIT_V2             (0x09U)
#define CY_USB_DEV_AUDIO2_CLOCK_SOURCE                  (0x0AU)
#define CY_USB_DEV_AUDIO2_CLOCK_SELECTOR                (0x0BU)
#define CY_USB_DEV_AUDIO2_CLOCK_MULTIPLIER              (0x0CU)
#define CY_USB_DEV_AUDIO2_SAMPLE_RATE_CONVERTER         (0x0DU)

/**
* Audio Class-Specific AS Interface Descriptor Subtypes
*/
#define CY_USB_DEV_AUDIO2_AS_DESCRIPTOR_UNDEFINED       (0x00U)
#define CY_USB_DEV_AUDIO2_AS_GENERAL                    (0x01U)
#define CY_USB_DEV_AUDIO2_FORMAT_TYPE                   (0x02U)
#define CY_USB_DEV_AUDIO2_ENCODER                       (0x03U)
#define CY_USB_DEV_AUDIO2_DECODER                       (0x04U)

/**
* Audio Class-Specific Endpoint Descriptor Subtypes
*/
#define CY_USB_DEV_AUDIO2_DESCRIPTOR_UNDEFINED          (0x00U)
#define CY_USB_DEV_AUDIO2_EP_GENERAL                    (0x01U)

/**
* Clock Source Control Selectors
*/
#define CY_USB_DEV_AUDIO2_CS_UNDEFINED                  (0x00U)
#define CY_USB_DEV_AUDIO2_CS_CONTROL_SAM_FREQ           (0x01U)
#define CY_USB_DEV_AUDIO2_CS_CONTROL_CLOCK_VALID        (0x02U)

/**
* Clock Selector Control Selectors
*/
#define CY_USB_DEV_AUDIO2_CX_UNDEFINED                  (0x00U)
#define CY_USB_DEV_AUDIO2_CX_CLOCK_SELECTOR             (0x01U)

/**
* Clock Multiplier Control Selectors
*/
#define CY_USB_DEV_AUDIO2_CM_UNDEFINED                  (0x00U)
#define CY_USB_DEV_AUDIO2_CM_NUMERATOR                  (0x01U)
#define CY_USB_DEV_AUDIO2_CM_DENOMINTATOR               (0x02U)

/**
* Terminal Control Selectors
*/
#define CY_USB_DEV_AUDIO2_TE_UNDEFINED                  (0x00U)
#define CY_USB_DEV_AUDIO2_TE_COPY_PROTECT               (0x01U)
#define CY_USB_DEV_AUDIO2_TE_CONNECTOR                  (0x02U)
#define CY_USB_DEV_AUDIO2_TE_OVERLOAD                   (0x03U)
#define CY_USB_DEV_AUDIO2_TE_CLUSTER                    (0x04U)
#define CY_USB_DEV_AUDIO2_TE_UNDERFLOW                  (0x05U)
#define CY_USB_DEV_AUDIO2_TE_OVERFLOW                   (0x06U)
#define CY_USB_DEV_AUDIO2_TE_LATENCY                    (0x07U)

/**
* AudioStreaming Interface Control Selectors
*/
#define CY_USB_DEV_AUDIO2_AS_UNDEFINED                  (0x00U)
#define CY_USB_DEV_AUDIO2_AS_ACT_ALT_SETTING            (0x01U)
#define CY_USB_DEV_AUDIO2_AS_VAL_ALT_SETTINGS           (0x02U)
#define CY_USB_DEV_AUDIO2_AS_AUDIO_DATA_FORMAT          (0x03U)

/**
* Endpoint Control Selectors
*/
#define CY_USB_DEV_AUDIO2_EP_CS_UNDEFINED               (0x00U)
#define CY_USB_DEV_AUDIO2_EP_CS_PITCH                   (0x01U)
#define CY_USB_DEV_AUDIO2_EP_CS_DATA_OVERRUN            (0x02U)
#define CY_USB_DEV_AUDIO2_EP_CS_DATA_UNDERRUN           (0x03U)

/** \endcond */

#if defined(__cplusplus)
}
#endif

#endif /* (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS)) */

#endif /* (CY_USB_DEV_AUDIO_DESCR_H) */


/* [] END OF FILE */
