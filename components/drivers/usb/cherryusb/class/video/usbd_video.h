/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBD_VIDEO_H
#define USBD_VIDEO_H

#include "usb_video.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Init video interface driver */
struct usbd_interface *usbd_video_init_intf(uint8_t busid, struct usbd_interface *intf,
                                            uint32_t dwFrameInterval,
                                            uint32_t dwMaxVideoFrameSize,
                                            uint32_t dwMaxPayloadTransferSize);

void usbd_video_open(uint8_t busid, uint8_t intf);
void usbd_video_close(uint8_t busid, uint8_t intf);

bool usbd_video_stream_split_transfer(uint8_t busid, uint8_t ep);
int usbd_video_stream_start_write(uint8_t busid, uint8_t ep, uint8_t *ep_buf0, uint8_t *ep_buf1, uint32_t ep_bufsize, uint8_t *stream_buf, uint32_t stream_len);

#ifdef __cplusplus
}
#endif

#endif /* USBD_VIDEO_H */
