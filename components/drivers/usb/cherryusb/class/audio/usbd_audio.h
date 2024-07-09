/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBD_AUDIO_H
#define USBD_AUDIO_H

#include "usb_audio.h"

#ifdef __cplusplus
extern "C" {
#endif

struct audio_entity_info {
    uint8_t bDescriptorSubtype;
    uint8_t bEntityId;
    uint8_t ep;
};

/* Init audio interface driver */
struct usbd_interface *usbd_audio_init_intf(uint8_t busid, struct usbd_interface *intf,
                                            uint16_t uac_version,
                                            struct audio_entity_info *table,
                                            uint8_t num);

void usbd_audio_open(uint8_t busid, uint8_t intf);
void usbd_audio_close(uint8_t busid, uint8_t intf);

void usbd_audio_set_volume(uint8_t busid, uint8_t ep, uint8_t ch, int volume);
int usbd_audio_get_volume(uint8_t busid, uint8_t ep, uint8_t ch);
void usbd_audio_set_mute(uint8_t busid, uint8_t ep, uint8_t ch, bool mute);
bool usbd_audio_get_mute(uint8_t busid, uint8_t ep, uint8_t ch);
void usbd_audio_set_sampling_freq(uint8_t busid, uint8_t ep, uint32_t sampling_freq);
uint32_t usbd_audio_get_sampling_freq(uint8_t busid, uint8_t ep);

void usbd_audio_get_sampling_freq_table(uint8_t busid, uint8_t ep, uint8_t **sampling_freq_table);

#ifdef __cplusplus
}
#endif

#endif /* USBD_AUDIO_H */
