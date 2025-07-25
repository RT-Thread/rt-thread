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
 * @file     drv/mbox.h
 * @brief    Header File for MBOX Driver
 * @version  V1.0
 * @date     5. Apr 2020
 * @model    mbox
 ******************************************************************************/

#ifndef _DRV_MBOX_H_
#define _DRV_MBOX_H_

#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    MBOX_EVENT_SEND_COMPLETE       = 0U,  ///< Send completed; however mbox may still transmit data
    MBOX_EVENT_RECEIVED            = 1U,  ///< Data Received, only in mbox buf, call memcpy() get the data
    MBOX_EVENT_ERROR               = 2U,  ///< Mbox transmit error occurred
} csi_mbox_event_t;

typedef struct csi_mbox csi_mbox_t;
struct csi_mbox {
    csi_dev_t        dev;
    void (*callback)(csi_mbox_t *mbox, csi_mbox_event_t event, uint32_t channel_id, uint32_t received_len, void *arg);
    void             *arg;
    void             *priv;
};

/**
  \brief       Initialize mbox Interface.
               Initializes the resources needed for the mbox interface.
  \param[in]   mbox  Operate handle.
  \param[in]   idx  The device idx.
  \return      Error code \ref csi_error_t.
*/
csi_error_t csi_mbox_init(csi_mbox_t *mbox, uint32_t idx);

/**
  \brief       Uninitialize mbox interface. stops operation and releases the software resources used by the interface.
  \param[in]   mbox  Operate handle.
*/
void csi_mbox_uninit(csi_mbox_t *mbox);

/**
  \brief       Start sending data to mbox transmitter.
  \param[in]   mbox  Operate handle.
  \param[in]   channel_id  Index of channel.
  \param[in]   data  Pointer to buffer with data to send to mbox transmitter.
  \param[in]   size  Number of data items to send.
  \return      sent Number of data or error code.
*/
int32_t csi_mbox_send(csi_mbox_t *mbox, uint32_t channel_id, const void *data, uint32_t size);

/**
  \brief       Start receiving data from mbox receiver.
  \param[in]   mbox  Operate handle.
  \param[in]   channel_id  Index of channel.
  \param[out]  data  Pointer to buffer with data to receive from mailbox.
  \param[in]   size  Number of data items to receive.
  \return      received  Number or error code.
*/
int32_t csi_mbox_receive(csi_mbox_t *mbox, uint32_t channel_id, void *data, uint32_t size);

/**
  \brief       Attach callback to the mbox.
  \param[in]   mbox  Operate handle.
  \param[in]   cb  Event callback function.
  \param[in]   arg  User private param  for event callback.
  \return      Error code \ref csi_error_t.
*/
csi_error_t csi_mbox_attach_callback(csi_mbox_t *mbox, void *callback, void *arg);

/**
  \brief       Detach callback from the mbox
  \param[in]   mbox  Operate handle.
*/
void csi_mbox_detach_callback(csi_mbox_t *mbox);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_MBOX_H_ */
