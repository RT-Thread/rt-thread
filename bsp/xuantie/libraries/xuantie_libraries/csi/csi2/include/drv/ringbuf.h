 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
* @file     ringbuffer.h
* @brief    header file for ringbuffer Driver
* @version  V1.0
* @date     August 15.  2019
******************************************************************************/
#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include <stdbool.h>

typedef struct ringbuffer {
    uint8_t *buffer;
    uint32_t size;
    uint32_t write;
    uint32_t read;
    uint32_t data_len;
} csi_ringbuf_t;

void csi_ringbuf_reset(csi_ringbuf_t *fifo);
uint32_t csi_ringbuf_len(csi_ringbuf_t *fifo);
uint32_t csi_ringbuf_avail(csi_ringbuf_t *fifo);
bool csi_ringbuf_is_empty(csi_ringbuf_t *fifo);
bool csi_ringbuf_is_full(csi_ringbuf_t *fifo);

/*write to ringbuffer*/
uint32_t csi_ringbuf_in(csi_ringbuf_t *fifo, const void *in, uint32_t len);

/*read to ringbuffer*/
uint32_t csi_ringbuf_out(csi_ringbuf_t *fifo, void *out, uint32_t len);

/*move to another ringbuffer*/
uint32_t csi_ringbuf_move(csi_ringbuf_t *fifo_in, csi_ringbuf_t *fifo_out);

#ifdef __cplusplus
}
#endif

#endif /* _RING_BUFFER_H_ */
