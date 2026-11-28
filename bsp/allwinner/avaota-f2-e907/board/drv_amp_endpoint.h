/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * AMP endpoint channel: named ept + multi-byte SHM + MSGBOX
 * LINK/QUEUE kicks. Not libmetal / virtio-rpmsg.
 */

#ifndef DRV_AMP_ENDPOINT_H__
#define DRV_AMP_ENDPOINT_H__

#include <stdint.h>

#define OA_SHM_BASE    0x41001000U
#define OA_EPT_NAME    "avaota-ept"
#define OA_PAYLOAD_MAX 64U

#define OA_EVT_LINK      0x00000001U
#define OA_EVT_QUEUE     0x00000002U
#define OA_EVT_LINK_ACK  0x00000011U
#define OA_EVT_QUEUE_ACK 0x00000012U

int amp_endpoint_master_start(uint32_t spins);
int amp_endpoint_slave_start(uint32_t spins);
int amp_endpoint_send(const void *data, uint32_t len, uint32_t spins);
int amp_endpoint_recv(void *data, uint32_t *len, uint32_t spins);
int amp_endpoint_echo_once(uint32_t spins);

#endif
