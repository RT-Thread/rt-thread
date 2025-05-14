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

#include <string.h>
#include <soc.h>
#include <drv/mbox.h>
#include <drv/irq.h>
#include <drv/porting.h>

#define CHN_NUM 4
#define INFO_NUM 8
#define MBOX_SEND_MAX_MESSAGE_LENGTH           ((INFO_NUM - 1U) * 4U)

/**
  \brief       wj_box_irq_handler
  \param[in]   mbox handle of mbox instance
*/
static void wj_mbox_irq_handler(void *arg)
{
    CSI_PARAM_CHK_NORETVAL(arg);

    ///< TODO：获取中断状态
    ///< TODO：清除中断
    ///< TODO：根据中断状态处理中断

}

/**
  \brief       Initialize MAILBOX Interface. 1. Initializes the resources needed for the MAILBOX interface 2.registers event callback function
  \param[in]   mbox    operate handle
  \param[in]   idx     the device idx
  \return      error code
*/
csi_error_t csi_mbox_init(csi_mbox_t *mbox, uint32_t idx)
{
    CSI_PARAM_CHK(mbox, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    ///< 获取中断号、基地址等相关信息
    ret = target_get(DEV_WJ_MBOX_TAG, idx, &mbox->dev);

    if (ret == CSI_OK) {

        for (uint32_t i = 0U; i < CHN_NUM; i++) {
            for (uint32_t j = 0U; j < INFO_NUM; j++) {
                /// TODO：把CPU0所有通道的MBOX_INFO清零
            }

            ///< TODO：屏蔽CPU0所有通道的中断
        }

        for (uint32_t i = 0U; i < CHN_NUM; i++) {
            ///< TODO：不屏蔽CPU0所有通道的中断
            ///< TODO：清除CPU0所有通道的中断
        }
    }

    return ret;
}

/**
  \brief       De-initialize MAILBOX Interface. stops operation and releases the software resources used by the interface
  \param[in]   mbox    operate handle
*/
void csi_mbox_uninit(csi_mbox_t *mbox)
{
    CSI_PARAM_CHK_NORETVAL(mbox);

    for (uint32_t i = 0U; i < CHN_NUM; i++) {

        ///< TODO：屏蔽CPU0所有通道的读中断
        ///< TODO：清除CPU0所有通道的中断

    }

    ///< 注销MBOX中断服务函数，禁止中断控制器中对应的中断
    csi_irq_detach((uint32_t)mbox->dev.irq_num);
    csi_irq_disable((uint32_t)mbox->dev.irq_num);
}

/**
  \brief       Start sending data to MAILBOX transmitter,(received data is ignored).
               This function is non-blocking,\ref mailbox_event_e is signaled when operation completes or error happens.
               \ref csi_mailbox_get_status can get operation status.
  \param[in]   mbox       operate handle
  \param[in]   channel_id index of channel
  \param[in]   data       Pointer to buffer with data to send to MAILBOX transmitter.
  \param[in]   size       size of data items to send
  \return      sent number of data
*/
int32_t csi_mbox_send(csi_mbox_t *mbox, uint32_t channel_id, const void *data, uint32_t size)
{
    CSI_PARAM_CHK(mbox, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    int32_t tx_len = (size > MBOX_SEND_MAX_MESSAGE_LENGTH) ? (int32_t)MBOX_SEND_MAX_MESSAGE_LENGTH : (int32_t)size;

    ///< TODO：获取某个CPU的某个通道

    if (ret == CSI_OK) {
        uint32_t mbox_busy = 0;
        ///< TODO：获取指定的CPU以及该CPU的某个通道的繁忙状态到mbox_busy

        if (mbox_busy & 0x1U) {
            tx_len = 0;
        } else {
            uint32_t buf[(MBOX_SEND_MAX_MESSAGE_LENGTH + 3U) >> 2U] = {0U};
            uint32_t gen_interrupt = 0U;
            memcpy(&buf, data, (uint32_t)tx_len);

            for (uint32_t count = (uint32_t)(((uint32_t)tx_len + 3U) / 4U); count > 0U; count--) {
                ///< TODO：往指定的CPU以及该CPU的某个通道写数据（buf[count - 1U]）
                gen_interrupt += (uint32_t)((uint32_t)1U << (count - 1U));
            }

            /* send tx_len to target channel */
            ///< TODO：往指定的CPU以及该CPU的某个通道写数据（(uint32_t)(((uint32_t)tx_len & 0xfffU) << 4U)）

            ///< TODO：使能指定的CPU以及该CPU的某个通道的中断
        }

    } else {
        tx_len = -1;
    }

    return tx_len;
}

/**
  \brief       Start Receiving data from Mailbox receiver.
  \param[in]   mbox   operate handle.
  \param[in]   channel_id index of channel
  \param[out]  data   Pointer to buffer with data to receive from mailbox.
  \param[in]   size   Number of data items to receive
  \return      received number or  error code
*/
int32_t csi_mbox_receive(csi_mbox_t *mbox, uint32_t channel_id, void *data, uint32_t size)
{
    CSI_PARAM_CHK(mbox, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    int32_t rx_len = (int32_t)size;

    uint32_t buf[(MBOX_SEND_MAX_MESSAGE_LENGTH + 3U) >> 2U] = {0U};

    ///< TODO：获取某个CPU的某个通道

    if (channel_id < CHN_NUM) {
        for (uint32_t i = 0U; i < ((size + 3U) >> 2U); i++) {
            ///< TODO：获取数据到buf[i]
            ///< TODO：往指定的CPU以及该CPU的某个通道写数据（0）
        }

        ///< TODO：禁止指定的CPU以及该CPU的某个通道的中断
        memcpy(data, buf, size);

        ///< TODO：往指定的CPU以及该CPU的某个通道写数据（(MBOX_ACK << 16U) | 1U）
        ///< TODO：使能指定的CPU以及该CPU的某个通道的中断
    } else {
        rx_len = -1;
    }

    return rx_len;
}

/**
\brief       Attach callback to the mbox
\param[in]   mbox    operate handle.
\param[in]   cb      event callback function \ref csi_mbox_callback_t
\param[in]   arg     user private param  for event callback
\return      error code
*/
csi_error_t csi_mbox_attach_callback(csi_mbox_t *mbox, void *callback, void *arg)
{
    CSI_PARAM_CHK(mbox, CSI_ERROR);
    CSI_PARAM_CHK(callback, CSI_ERROR);
    csi_error_t ret = CSI_OK;
    mbox->callback = callback;
    mbox->arg = arg;
    ///< TODO：注册MBOX中断服务函数，使能中断控制器对应的中断
    csi_irq_attach((uint32_t)mbox->dev.irq_num, &wj_mbox_irq_handler, &mbox->dev);
    csi_irq_enable((uint32_t)mbox->dev.irq_num);
    return ret;
}

/**
\brief       detach callback from the mbox
\param[in]   mbox   operate handle.
*/
void csi_mbox_detach_callback(csi_mbox_t *mbox)
{
    CSI_PARAM_CHK_NORETVAL(mbox);
    mbox->callback  = NULL;
    mbox->arg = NULL;
    ///< TODO：注销MBOX的中断服务函数，禁止中断控制器对应的中断
    csi_irq_detach((uint32_t)mbox->dev.irq_num);
    csi_irq_disable((uint32_t)mbox->dev.irq_num);
}
