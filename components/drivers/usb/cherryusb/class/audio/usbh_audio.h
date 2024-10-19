/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBH_AUDIO_H
#define USBH_AUDIO_H

#include "usb_audio.h"

#ifndef CONFIG_USBHOST_AUDIO_MAX_STREAMS
#define CONFIG_USBHOST_AUDIO_MAX_STREAMS 3
#endif

struct usbh_audio_ac_msg {
    struct audio_cs_if_ac_input_terminal_descriptor ac_input;
    struct audio_cs_if_ac_feature_unit_descriptor ac_feature_unit;
    struct audio_cs_if_ac_output_terminal_descriptor ac_output;
};

struct usbh_audio_as_msg {
    const char *stream_name;
    uint8_t stream_intf;
    uint8_t input_terminal_id;
    uint8_t feature_terminal_id;
    uint8_t output_terminal_id;
    uint8_t ep_attr;
    uint8_t num_of_altsetting;
    struct audio_cs_if_as_general_descriptor as_general;
    struct audio_cs_if_as_format_type_descriptor as_format[CONFIG_USBHOST_MAX_INTF_ALTSETTINGS];
};

struct usbh_audio {
    struct usbh_hubport *hport;
    struct usb_endpoint_descriptor *isoin;  /* ISO IN endpoint */
    struct usb_endpoint_descriptor *isoout; /* ISO OUT endpoint */

    uint8_t ctrl_intf; /* interface number */
    uint8_t minor;
    uint16_t isoin_mps;
    uint16_t isoout_mps;
    bool is_opened;
    uint16_t bcdADC;
    uint8_t bInCollection;
    uint8_t stream_intf_num;
    struct usbh_audio_ac_msg ac_msg_table[CONFIG_USBHOST_AUDIO_MAX_STREAMS];
    struct usbh_audio_as_msg as_msg_table[CONFIG_USBHOST_AUDIO_MAX_STREAMS];

    void *user_data;
};

#ifdef __cplusplus
extern "C" {
#endif

int usbh_audio_open(struct usbh_audio *audio_class, const char *name, uint32_t samp_freq, uint8_t bitresolution);
int usbh_audio_close(struct usbh_audio *audio_class, const char *name);
int usbh_audio_set_volume(struct usbh_audio *audio_class, const char *name, uint8_t ch, uint8_t volume);
int usbh_audio_set_mute(struct usbh_audio *audio_class, const char *name, uint8_t ch, bool mute);

void usbh_audio_run(struct usbh_audio *audio_class);
void usbh_audio_stop(struct usbh_audio *audio_class);

#ifdef __cplusplus
}
#endif

#endif /* USBH_AUDIO_H */
