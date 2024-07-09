/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBH_AUDIO_H
#define USBH_AUDIO_H

#include "usb_audio.h"

struct usbh_audio_format_type {
    uint8_t channels;
    uint8_t format_type;
    uint8_t bitresolution;
    uint8_t sampfreq_num;
    uint32_t sampfreq[3];
};

/**
 * bSourceID in feature_unit = input_terminal_id
 * bSourceID in output_terminal = feature_unit_id
 * terminal_link_id = input_terminal_id or output_terminal_id (if input_terminal_type or output_terminal_type is 0x0101)
 *
 *
*/
struct usbh_audio_module {
    const char *name;
    uint8_t data_intf;
    uint8_t input_terminal_id;
    uint16_t input_terminal_type;
    uint16_t input_channel_config;
    uint8_t output_terminal_id;
    uint16_t output_terminal_type;
    uint8_t feature_unit_id;
    uint8_t feature_unit_controlsize;
    uint8_t feature_unit_controls[8];
    uint8_t terminal_link_id;
    struct usbh_audio_format_type altsetting[CONFIG_USBHOST_MAX_INTF_ALTSETTINGS];
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
    uint8_t num_of_intf_altsettings;
    struct usbh_audio_module module[2];
    uint8_t module_num;

    void *user_data;
};

#ifdef __cplusplus
extern "C" {
#endif

int usbh_audio_open(struct usbh_audio *audio_class, const char *name, uint32_t samp_freq);
int usbh_audio_close(struct usbh_audio *audio_class, const char *name);
int usbh_audio_set_volume(struct usbh_audio *audio_class, const char *name, uint8_t ch, uint8_t volume);
int usbh_audio_set_mute(struct usbh_audio *audio_class, const char *name, uint8_t ch, bool mute);

void usbh_audio_run(struct usbh_audio *audio_class);
void usbh_audio_stop(struct usbh_audio *audio_class);

#ifdef __cplusplus
}
#endif

#endif /* USBH_AUDIO_H */
