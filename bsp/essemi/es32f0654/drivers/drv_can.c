/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-11-09     wangyq        the first version
 * 2021-04-20     liuhy         the second version
 * 2026-11-09     wdfk-prog     adapt CAN driver to Generic CAN framework
 */

#include "drv_can.h"

#ifdef RT_USING_CAN


static struct es32f0_can can;


static rt_uint32_t get_can_baud_index(rt_uint32_t baud,can_init_t * init)
{
/* attention !!! baud calculation example: Pclk / ((1 + seg1 + seg2) * psc)       Pclk=48 / ((1 + seg1=3 + seg2=2) * 8) = 1MHz */
    double target,temp,min;
    uint32_t i,j,j_max,near = 0;
    target = (double)(ald_cmu_get_pclk1_clock());
    target/= baud;                               /*计算误差1*/

    min = 0xFFFFFFFF;

    for(i = 1 + 16 + 8 ;i > 2;i--)     /*SYNC_SEG + SEG1 + SEG2*/
    {
        j_max = target/i/(0.98) + 1;                          /*缩小范围*/
        j_max = (j_max > 1024) ? (1024) : (j_max);

        for(j = target/i/1.02 ;j < j_max;j++)
        {
            temp = target/i/j;                      /*计算误差2*/
            temp = (temp > 1) ? (temp - 1) : (1 - temp);
            temp+= ((1.0 * i * j) / 0xFFFFFFFF) ;

            if(temp < min)
            {
                if(temp > 0.000001)
                {
                     near = (i<<16) + j;
                     min = temp;
                }
                else
                {
                     init->seg1 = (can_seg1_t)((i - 1)*2/3-1);
                     init->seg2 = (can_seg2_t)(i - init->seg1 - 1 - 1 - 1);
                     init->psc = j;

                     return 0;
                 }
             }
         }
    }

    if(min < 0.01)
    {
        i = near>>16;
        j = near % (1<<16);
        init->seg1 = (can_seg1_t)((i - 1)*2/3-1);
        init->seg2 = (can_seg2_t)(i - init->seg1 - 1 - 1 - 1);
        init->psc = j;

        return 0;
    }
    else
    {
        return 1;
    }
}


static rt_err_t _can_config(struct rt_can_device *can_device, struct can_configure *cfg)
{
    struct es32f0_can *drv_can;

    RT_ASSERT(can_device);
    RT_ASSERT(cfg);
    drv_can = (struct es32f0_can *)can_device->parent.user_data;
    RT_ASSERT(drv_can);

    drv_can->CanHandle.perh = CAN0;
    drv_can->CanHandle.init.ttcm = DISABLE;
    drv_can->CanHandle.init.abom = ENABLE;
    drv_can->CanHandle.init.awk = DISABLE;
    drv_can->CanHandle.init.artx = (type_func_t)ES_CAN0_AUTO_BAN_RE_T;
    drv_can->CanHandle.init.rfom   = DISABLE;
    drv_can->CanHandle.init.txmp   = ENABLE;

    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        drv_can->CanHandle.init.mode = CAN_MODE_NORMAL;
        break;
    case RT_CAN_MODE_LISTEN:
        drv_can->CanHandle.init.mode = CAN_MODE_SILENT;
        break;
    case RT_CAN_MODE_LOOPBACK:
        drv_can->CanHandle.init.mode = CAN_MODE_LOOPBACK;
        break;
    case RT_CAN_MODE_LOOPBACKANLISTEN:
        drv_can->CanHandle.init.mode = CAN_MODE_SILENT_LOOPBACK;
        break;
    }
    /*配置参数*/
    if(get_can_baud_index(cfg->baud_rate,&(drv_can->CanHandle.init)))
    {
        return -RT_ERROR;
    }
    drv_can->CanHandle.init.sjw = (can_sjw_t)(cfg->reserved);

    /* init can */

   // baud_index = get_can_baud_index(cfg->baud_rate);
    //drv_can->CanHandle.init.sjw = CAN_SJW_1;
   // drv_can->CanHandle.init.seg1 = CAN_SEG1_3;
   // drv_can->CanHandle.init.seg2 = CAN_SEG2_2;
   // drv_can->CanHandle.init.psc = can_baud_rate_tab[baud_index].config_data;
    /* init can */
    if (ald_can_init(&drv_can->CanHandle) != OK)
    {
        return -RT_ERROR;
    }
    /* default filter config */
    ald_can_filter_config(&drv_can->CanHandle, &drv_can->FilterConfig);

    return RT_EOK;
}

static rt_err_t _can_control(struct rt_can_device *can_device, int cmd, void *arg)
{
    rt_uint32_t argval;
    struct es32f0_can *drv_can;

#ifdef RT_CAN_USING_HDR
    struct rt_can_filter_config *filter_cfg;
#endif

    RT_ASSERT(can_device != RT_NULL);
    drv_can = (struct es32f0_can *)can_device->parent.user_data;
    RT_ASSERT(drv_can != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_FP0, DISABLE);
            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_FF0, DISABLE);
            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_FOV0, DISABLE);
            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_FP1, DISABLE);
            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_FF1, DISABLE);
            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_FOV1, DISABLE);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_TXM, DISABLE);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_WARN, DISABLE);
            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_PERR, DISABLE);
            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_BOF, DISABLE);
            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_PRERR, DISABLE);
            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_ERR, DISABLE);
        }
        break;
    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            NVIC_SetPriority(CAN0_IRQn, 1);
            NVIC_EnableIRQ(CAN0_IRQn);

            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_FP0, ENABLE);
//            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_FF0, ENABLE);
            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_FOV0, ENABLE);
            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_FP1, ENABLE);
//            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_FF1, ENABLE);
            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_FOV1, ENABLE);

        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            NVIC_SetPriority(CAN0_IRQn, 1);
            NVIC_EnableIRQ(CAN0_IRQn);

            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_TXM, ENABLE);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            NVIC_SetPriority(CAN0_IRQn, 1);
            NVIC_EnableIRQ(CAN0_IRQn);

            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_WARN, ENABLE);
            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_PERR, ENABLE);
            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_BOF, ENABLE);
            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_PRERR, ENABLE);
            ald_can_interrupt_config(&drv_can->CanHandle, CAN_IT_ERR, ENABLE);

        }
        break;
#ifdef RT_CAN_USING_HDR
    case RT_CAN_CMD_SET_FILTER:
        if (RT_NULL == arg)
        {
            /* default filter config */
            ald_can_filter_config(&drv_can->CanHandle, &drv_can->FilterConfig);
        }
        else
        {
            filter_cfg = (struct rt_can_filter_config *)arg;
            for (int i = 0; i < filter_cfg->count; i++)
            {
                /* filter is a per-item copy; id/mask are converted locally; bank is the requested index. */
                can_filter_t filter = drv_can->FilterConfig;
                rt_uint32_t id = filter_cfg->items[i].id;
                rt_uint32_t mask = filter_cfg->items[i].mask;
                rt_int32_t bank = filter_cfg->items[i].hdr_bank;

                filter.number = (bank >= 0 && bank < (rt_int32_t)drv_can->device.config.maxhdr) ?
                                bank : ES_C_CAN_DEFAULT_FILTER_NUMBER;
                filter.fifo = (can_filter_fifo_t)filter_cfg->items[i].rxfifo;
                filter.active = filter_cfg->actived ? ENABLE : DISABLE;

                if (filter_cfg->items[i].mode)
                {
                    if (filter_cfg->items[i].ide)
                    {
                        mask = (mask << 3) | (filter_cfg->items[i].ide << 2) |
                               (filter_cfg->items[i].rtr << 1);
                    }
                    else
                    {
                        id <<= 18;
                        mask = (mask << 21) | (filter_cfg->items[i].ide << 2) |
                               (filter_cfg->items[i].rtr << 1);
                    }
                }
                else
                {
                    if (filter_cfg->items[i].ide)
                    {
                        mask <<= 3;
                    }
                    else
                    {
                        id <<= 18;
                        mask <<= 21;
                    }
#if ES_C_CAN_FILTER_FRAME_TYPE
                    mask |= 0x6;
#endif
                }

                filter.id_high = (id >> 13) & 0xFFFF;
                filter.id_low = ((id << 3) | (filter_cfg->items[i].ide << 2) |
                                 (filter_cfg->items[i].rtr << 1)) & 0xFFFF;
                filter.mask_id_high = (mask >> 16) & 0xFFFF;
                filter.mask_id_low = mask & 0xFFFF;
                filter.mode = (can_filter_mode_t)filter_cfg->items[i].mode;
                ald_can_filter_config(&drv_can->CanHandle, &filter);
            }
        }
        break;

#endif
    case RT_CAN_CMD_SET_MODE:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_NORMAL &&
                argval != RT_CAN_MODE_LISTEN &&
                argval != RT_CAN_MODE_LOOPBACK &&
                argval != RT_CAN_MODE_LOOPBACKANLISTEN)
        {
            return -RT_ERROR;
        }
        if (argval != drv_can->device.config.mode)
        {
            drv_can->device.config.mode = argval;
            return _can_config(&drv_can->device, &drv_can->device.config);
        }
        break;
    case RT_CAN_CMD_SET_BAUD:
        argval = (rt_uint32_t) arg;

        if (argval != drv_can->device.config.baud_rate)
        {
            drv_can->device.config.baud_rate = argval;
            return _can_config(&drv_can->device, &drv_can->device.config);
        }
        break;
    case RT_CAN_CMD_SET_PRIV:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_PRIV &&
                argval != RT_CAN_MODE_NOPRIV)
        {
            return -RT_ERROR;
        }
        if (argval != drv_can->device.config.privmode)
        {
            drv_can->device.config.privmode = argval;
            return _can_config(&drv_can->device, &drv_can->device.config);
        }
        break;
    case RT_CAN_CMD_ABORT_TX:
        argval = (rt_uint32_t)(rt_ubase_t)arg;
        if (argval >= 3U || argval >= can_device->config.sndboxnumber)
            return -RT_EINVAL;
        /* TXSTAT has W1C terminal bits; do not read-modify-write the abort request. */
        WRITE_REG(drv_can->CanHandle.perh->TXSTAT, CAN_TXSTAT_M0STPREQ_MSK << (argval * 8U));
        break;
    case RT_CAN_CMD_START:
        if ((rt_ubase_t)arg != 0U)
        {
            return _can_config(can_device, &can_device->config);
        }
        else
        {
            /* h_can owns the hardware, empty_mask covers every TX mailbox. */
            can_handle_t *h_can = &drv_can->CanHandle;
            rt_uint32_t empty_mask = CAN_TXSTAT_TXM0EF_MSK |
                                     CAN_TXSTAT_TXM1EF_MSK | CAN_TXSTAT_TXM2EF_MSK;
            /* start_tick and timeout_ticks share one deadline for the full STOP sequence. */
            rt_tick_t start_tick = rt_tick_get();
            rt_tick_t timeout_ticks = rt_tick_from_millisecond(200);

            WRITE_REG(h_can->perh->TXSTAT, CAN_TXSTAT_M0STPREQ_MSK |
                                         CAN_TXSTAT_M1STPREQ_MSK | CAN_TXSTAT_M2STPREQ_MSK);
            while ((h_can->perh->TXSTAT & empty_mask) != empty_mask)
            {
                if ((rt_tick_t)(rt_tick_get() - start_tick) >= timeout_ticks)
                    return -RT_ERROR;
                rt_thread_mdelay(1);
            }
            CLEAR_BIT(h_can->perh->CON, CAN_CON_SLPREQ_MSK);
            SET_BIT(h_can->perh->CON, CAN_CON_INIREQ_MSK);
            while ((h_can->perh->STAT & CAN_STAT_INISTAT_MSK) == 0U)
            {
                if ((rt_tick_t)(rt_tick_get() - start_tick) >= timeout_ticks)
                    return -RT_ERROR;
                rt_thread_mdelay(1);
            }
            WRITE_REG(h_can->perh->TXSTATC, CAN_TXSTATC_M0REQC_MSK |
                                           CAN_TXSTATC_M1REQC_MSK | CAN_TXSTATC_M2REQC_MSK);
            NVIC_ClearPendingIRQ(CAN0_IRQn);
            ald_can_reset(h_can);
        }
        break;
    case RT_CAN_CMD_GET_STATUS:
    {
        rt_uint32_t errtype;
        errtype = drv_can->CanHandle.perh->ERRSTAT;
        drv_can->device.status.rcverrcnt = errtype >> 24;
        drv_can->device.status.snderrcnt = (errtype >> 16 & 0xFF);
        drv_can->device.status.lasterrtype = (errtype & 0x70U) >> 4;
        drv_can->device.status.errcode = errtype & 0x07;

        rt_memcpy(arg, &drv_can->device.status, sizeof(drv_can->device.status));
    }
    break;
    }

    return RT_EOK;
}

static rt_ssize_t _can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_num)
{
    can_handle_t *h_can;
    h_can = &((struct es32f0_can *) can->parent.user_data)->CanHandle;
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
    can_tx_msg_t txheader = {0};
    can_state_t state = h_can->state;

    /* Check the parameters */
    RT_ASSERT(IS_CAN_DATA_LEN(pmsg->len));

    if (box_num >= 3U || box_num >= can->config.sndboxnumber)
        return -RT_EINVAL;

    if ((state == CAN_STATE_READY) ||
        (state == CAN_STATE_BUSY_RX0) ||
        (state == CAN_STATE_BUSY_RX1) ||
        (state == CAN_STATE_BUSY_RX0_RX1))
    {
        /* An empty mailbox with an unconsumed terminal still belongs to the old TX. */
        switch (box_num)
        {
        case CAN_TX_MAILBOX_0:
            if (ald_can_get_flag_status(h_can, CAN_FLAG_TXM0) != SET ||
                ald_can_get_flag_status(h_can, CAN_FLAG_M0REQC) == SET)
                return -RT_EBUSY;
            break;
        case CAN_TX_MAILBOX_1:
            if (ald_can_get_flag_status(h_can, CAN_FLAG_TXM1) != SET ||
                ald_can_get_flag_status(h_can, CAN_FLAG_M1REQC) == SET)
                return -RT_EBUSY;
            break;
        case CAN_TX_MAILBOX_2:
            if (ald_can_get_flag_status(h_can, CAN_FLAG_TXM2) != SET ||
                ald_can_get_flag_status(h_can, CAN_FLAG_M2REQC) == SET)
                return -RT_EBUSY;
            break;
        default:
            return -RT_EINVAL;
        }

        if (RT_CAN_STDID == pmsg->ide)
        {
            txheader.type = CAN_ID_STD;
            RT_ASSERT(IS_CAN_STDID(pmsg->id));
            txheader.std = pmsg->id;
        }
        else
        {
            txheader.type = CAN_ID_EXT;
            RT_ASSERT(IS_CAN_EXTID(pmsg->id));
            txheader.ext = pmsg->id;
        }

        if (RT_CAN_DTR == pmsg->rtr)
        {
            txheader.rtr = CAN_RTR_DATA;
        }
        else
        {
            txheader.rtr = CAN_RTR_REMOTE;
        }
        /* clear TIR */
        WRITE_REG(h_can->perh->TxMailBox[box_num].TXID, 0U);
        /* Set up the Id */
        if (RT_CAN_STDID == pmsg->ide)
        {
            h_can->perh->TxMailBox[box_num].TXID |= (txheader.std << CAN_TXID0_STDID_POSS) | (txheader.rtr << CAN_TXID0_RTR_POS);
        }
        else
        {
            h_can->perh->TxMailBox[box_num].TXID |=
                (((txheader.ext >> 18) & 0x7FFU) << CAN_TXID0_STDID_POSS) |
                ((txheader.ext & 0x3FFFFU) << CAN_TXID0_EXID_POSS) |
                (txheader.type << CAN_TXID0_IDE_POS) | (txheader.rtr << CAN_TXID0_RTR_POS);
        }
        /* Set up the DLC */
        h_can->perh->TxMailBox[box_num].TXFCON = pmsg->len & 0x0FU;
        /* Set up the data field */
        WRITE_REG(h_can->perh->TxMailBox[box_num].TXDH,
                  ((uint32_t)pmsg->data[7] << CAN_TXDH0_BYTE7_POSS) |
                  ((uint32_t)pmsg->data[6] << CAN_TXDH0_BYTE6_POSS) |
                  ((uint32_t)pmsg->data[5] << CAN_TXDH0_BYTE5_POSS) |
                  ((uint32_t)pmsg->data[4] << CAN_TXDH0_BYTE4_POSS));
        WRITE_REG(h_can->perh->TxMailBox[box_num].TXDL,
                  ((uint32_t)pmsg->data[3] << CAN_TXDL0_BYTE3_POSS) |
                  ((uint32_t)pmsg->data[2] << CAN_TXDL0_BYTE2_POSS) |
                  ((uint32_t)pmsg->data[1] << CAN_TXDL0_BYTE1_POSS) |
                  ((uint32_t)pmsg->data[0] << CAN_TXDL0_BYTE0_POSS));
        /* Request transmission */
        SET_BIT(h_can->perh->TxMailBox[box_num].TXID, CAN_TXID0_TXMREQ_MSK);

        return RT_EOK;
    }
    else
    {
        /* Update error code */
        h_can->err |= 0x00040000U;

        return -RT_ERROR;
    }
}

/**
 * @brief Submit one CAN frame to an available hardware TX mailbox without waiting.
 * @param can CAN device.
 * @param buf CAN frame to submit.
 * @param mailbox Selected mailbox index, written only after hardware acceptance.
 * @return RT_EOK on acceptance, -RT_EBUSY when all mailboxes are unavailable, or a send error.
 */
static rt_ssize_t _can_sendmsg_nonblocking(struct rt_can_device *can,
                                          const void *buf, rt_uint32_t *mailbox)
{
    /* box_num scans mailbox indices; result tracks the immediate submit attempt. */
    rt_uint32_t box_num;
    rt_ssize_t result;

    for (box_num = 0; box_num < can->config.sndboxnumber && box_num < 3U; box_num++)
    {
        if (can->status.sndchange & (1UL << box_num))
            continue;
        result = _can_sendmsg(can, buf, box_num);
        if (result == RT_EOK)
        {
            *mailbox = box_num;
            return RT_EOK;
        }
        if (result != -RT_EBUSY)
            return result;
    }
    return -RT_EBUSY;
}

static rt_ssize_t _can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    can_handle_t *h_can;
    struct rt_can_msg *pmsg;
    can_rx_msg_t rxheader = {0};

    RT_ASSERT(can);

    h_can = &((struct es32f0_can *)can->parent.user_data)->CanHandle;
    pmsg = (struct rt_can_msg *) buf;

    /* get data */
    if (CAN_RX_MSG_PENDING(h_can, (can_rx_fifo_t)fifo) == 0)
        return -RT_ERROR;
    /* ald_can_recv() releases the RX FIFO entry on success. */
    if (ald_can_recv(h_can, (can_rx_fifo_t)fifo, &rxheader, 0) != OK)
        return -RT_ERROR;
    pmsg->data[0] = rxheader.data[0];
    pmsg->data[1] = rxheader.data[1];
    pmsg->data[2] = rxheader.data[2];
    pmsg->data[3] = rxheader.data[3];
    pmsg->data[4] = rxheader.data[4];
    pmsg->data[5] = rxheader.data[5];
    pmsg->data[6] = rxheader.data[6];
    pmsg->data[7] = rxheader.data[7];

    /* get id */
    if (CAN_ID_STD == rxheader.type)
    {
        pmsg->ide = RT_CAN_STDID;
        pmsg->id = rxheader.std;
    }
    else
    {
        pmsg->ide = RT_CAN_EXTID;
        pmsg->id = rxheader.ext;
    }
    /* get type */
    if (CAN_RTR_DATA == rxheader.rtr)
    {
        pmsg->rtr = RT_CAN_DTR;
    }
    else
    {
        pmsg->rtr = RT_CAN_RTR;
    }
    /* get len */
    pmsg->len = rxheader.len;
    /* get hdr_index */
    pmsg->hdr_index = (rxheader.fmi + 1) >> 1;

    return RT_EOK;
}


static const struct rt_can_ops _can_ops =
{
    _can_config,
    _can_control,
    _can_sendmsg,
    _can_recvmsg,
    _can_sendmsg_nonblocking,
};

static void _can_rx_isr(struct rt_can_device *can, rt_uint32_t fifo)
{
    can_handle_t *h_can;
    RT_ASSERT(can);
    h_can = &((struct es32f0_can *) can->parent.user_data)->CanHandle;

    switch (fifo)
    {
    case CAN_RX_FIFO0:
        /* Check Overrun flag for FIFO0 */
        if (ald_can_get_flag_status(h_can, CAN_FLAG_FOV0) && ald_can_get_it_status(h_can, CAN_IT_FOV0))
        {
            /* Clear FIFO0 Overrun Flag */
            ald_can_clear_flag_status(h_can, CAN_FLAG_FOV0);
            rt_hw_can_isr(can, RT_CAN_EVENT_RXOF_IND | fifo << 8);
        }
        /* RX interrupt */
        else
        {
           if(CAN_RX_MSG_PENDING(h_can, CAN_RX_FIFO0) != 0)
            {
            /* save to user list */
            rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | fifo << 8);
            }

        }
        break;
    case CAN_RX_FIFO1:
        /* Check Overrun flag for FIFO1 */
        if (ald_can_get_flag_status(h_can, CAN_FLAG_FOV1) && ald_can_get_it_status(h_can, CAN_IT_FOV1))
        {
            /* Clear FIFO1 Overrun Flag */
            ald_can_clear_flag_status(h_can, CAN_FLAG_FOV1);
            rt_hw_can_isr(can, RT_CAN_EVENT_RXOF_IND | fifo << 8);
        }
        /* RX interrupt */
        else
        {
            if(CAN_RX_MSG_PENDING(h_can, CAN_RX_FIFO1) != 0)
            {
            /* save to user list */
            rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | fifo << 8);
            }

        }
        break;
    }
}

/**
 * @brief This function handles CAN interrupts.
 */
void CAN0_Handler(void)
{
    rt_interrupt_enter();

    rt_uint32_t errtype;
    can_handle_t *h_can;
    h_can = &can.CanHandle;

    /* RX FIFO0 interrupt */
    if ((ald_can_get_it_status(h_can, CAN_IT_FP0)) && (CAN_RX_MSG_PENDING(h_can, CAN_RX_FIFO0) != 0))
    {
        _can_rx_isr(&can.device, CAN_RX_FIFO0);
    }

    /* RX FIFO1 interrupt */
    if ((ald_can_get_it_status(h_can, CAN_IT_FP1)) && (CAN_RX_MSG_PENDING(h_can, CAN_RX_FIFO1) != 0))
    {
        _can_rx_isr(&can.device, CAN_RX_FIFO1);
    }

    /* TX interrupt. transmit fifo0/1/2 is empty can trigger this interrupt */
    if (ald_can_get_flag_status(h_can, CAN_FLAG_M0REQC) && ald_can_get_it_status(h_can, CAN_IT_TXM))
    {
        if (ald_can_get_flag_status(h_can, CAN_FLAG_M0TXC))
        {
            rt_hw_can_isr(&can.device, RT_CAN_EVENT_TX_DONE | 0 << 8);
        }
        else
        {
            rt_hw_can_isr(&can.device, RT_CAN_EVENT_TX_FAIL | 0 << 8);
        }
        /* Clear transmission status flag M0REQC */
        ald_can_clear_flag_status(h_can, CAN_FLAG_M0REQC);
    }
    if (ald_can_get_flag_status(h_can, CAN_FLAG_M1REQC) && ald_can_get_it_status(h_can, CAN_IT_TXM))
    {
        if (ald_can_get_flag_status(h_can, CAN_FLAG_M1TXC))
        {
            rt_hw_can_isr(&can.device, RT_CAN_EVENT_TX_DONE | 1 << 8);
        }
        else
        {
            rt_hw_can_isr(&can.device, RT_CAN_EVENT_TX_FAIL | 1 << 8);
        }
        ald_can_clear_flag_status(h_can, CAN_FLAG_M1REQC);
    }
    if (ald_can_get_flag_status(h_can, CAN_FLAG_M2REQC) && ald_can_get_it_status(h_can, CAN_IT_TXM))
    {
        if (ald_can_get_flag_status(h_can, CAN_FLAG_M2TXC))
        {
            rt_hw_can_isr(&can.device, RT_CAN_EVENT_TX_DONE | 2 << 8);
        }
        else
        {
            rt_hw_can_isr(&can.device, RT_CAN_EVENT_TX_FAIL | 2 << 8);
        }
        ald_can_clear_flag_status(h_can, CAN_FLAG_M2REQC);
    }

    /* CAN error interrupt */
    if (ald_can_get_flag_status(h_can, CAN_FLAG_ERR) && ald_can_get_it_status(h_can, CAN_IT_ERR))
    {
        errtype = h_can->perh->ERRSTAT;
        /* Protocol errors do not retire a mailbox; only a TX terminal does. */
        rt_hw_can_isr(&can.device, RT_CAN_EVENT_ERR | ((errtype & 0x70U) << 4));
        can.device.status.lasterrtype = (errtype & 0x70U) >> 4;
        can.device.status.rcverrcnt = errtype >> 24;
        can.device.status.snderrcnt = (errtype >> 16) & 0xFFU;
        can.device.status.errcode = errtype & 0x07U;
        WRITE_REG(h_can->perh->IFC, CAN_IFC_ERRIFC_MSK);
    }
    rt_interrupt_leave();
}

int rt_hw_can_init(void)
{
    gpio_init_t h_gpio;

    /* Initialize can common pin */
    h_gpio.odos = GPIO_PUSH_PULL;
    h_gpio.pupd = GPIO_PUSH_UP;
    h_gpio.odrv = GPIO_OUT_DRIVE_NORMAL;
    h_gpio.flt  = GPIO_FILTER_DISABLE;
    h_gpio.type = GPIO_TYPE_TTL;

#if  defined(ES_CAN0_RX_GPIO_FUNC)&&defined(ES_CAN0_RX_GPIO_PORT)&&defined(ES_CAN0_RX_GPIO_PIN)
    /* Initialize can rx pin */
    h_gpio.mode = GPIO_MODE_INPUT;
    h_gpio.func = ES_CAN0_RX_GPIO_FUNC;
    ald_gpio_init(ES_CAN0_RX_GPIO_PORT, ES_CAN0_RX_GPIO_PIN, &h_gpio);
#endif


#if  defined(ES_CAN0_TX_GPIO_FUNC)&&defined(ES_CAN0_TX_GPIO_PORT)&&defined(ES_CAN0_TX_GPIO_PIN)
    /* Initialize can tx pin */
    h_gpio.mode = GPIO_MODE_OUTPUT;
    h_gpio.func = ES_CAN0_TX_GPIO_FUNC;
    ald_gpio_init(ES_CAN0_TX_GPIO_PORT, ES_CAN0_TX_GPIO_PIN, &h_gpio);
#endif


    /* config default filter */
    can_filter_t filter = {0};
    filter.id_high = 0x0000;
    filter.id_low = 0x0000;
    filter.mask_id_high = 0x0000;
    filter.mask_id_low = 0x0000;
    filter.fifo = CAN_FILTER_FIFO0;
    filter.number = ES_C_CAN_DEFAULT_FILTER_NUMBER;
    filter.mode = CAN_FILTER_MODE_MASK;
    filter.scale = CAN_FILTER_SCALE_32;
    filter.active = ENABLE;

    can.FilterConfig = filter;
    can.device.config = (struct can_configure)ES_CAN0_CONFIG;
    can.device.config.sndboxnumber = 3U;
#ifdef RT_CAN_USING_HDR
    can.device.config.maxhdr = 14;
#endif
    can.device.config.privmode = RT_CAN_MODE_NOPRIV;
    can.device.config.ticks = 50;
    can.device.config.reserved = ES_CAN0_SJW;
    /* register CAN1 device */
    rt_hw_can_register(&can.device, ES_DEVICE_NAME_CAN0, &_can_ops, &can);

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_can_init);

#endif /* RT_USING_CAN */
