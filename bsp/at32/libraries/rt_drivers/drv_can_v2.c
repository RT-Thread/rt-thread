/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-30     shelton      first version
 */

#include "drv_can_v2.h"
#include "drv_config.h"

#ifdef BSP_USING_CAN_V2

#define LOG_TAG    "drv_can"
#include <drv_log.h>

#ifdef RT_CAN_USING_CANFD
static const uint8_t dlc_to_bytes[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64};
#endif

#ifdef SOC_SERIES_AT32M412
/* attention !!! baud calculation example: apbclk / ((bs1 + bs2) * bittime_div), ep: 180 / ((45 + 135) * 1) = 1MHz*/
/* attention !!! default apbclk 180 mhz */
static const struct at32_baud_rate can_baud_rate_tab[] =
{
    {CAN1MBaud,   1 ,  45,  135,  45},
    {CAN800kBaud, 1 ,  45,  180,  45},
    {CAN500kBaud, 1 ,  90,  270,  90},
    {CAN250kBaud, 2 ,  90,  270,  90},
    {CAN125kBaud, 3 ,  120, 360, 120},
    {CAN100kBaud, 5 ,  90,  270,  90},
    {CAN50kBaud,  9 ,  100, 300, 100},
    {CAN20kBaud,  18,  125, 375, 125},
    {CAN10kBaud,  30,  120, 480, 120},
};
#endif

#ifdef SOC_SERIES_AT32M416
/* attention !!! baud calculation example: apbclk / ((bs1 + bs2) * bittime_div), ep: 180 / ((45 + 135) * 1) = 1MHz*/
/* attention !!! default apbclk 180 mhz */
static const struct at32_baud_rate can_baud_rate_tab[] =
{
    {CAN1MBaud,   1 ,  45,  135,  45},
    {CAN800kBaud, 1 ,  45,  180,  45},
    {CAN500kBaud, 1 ,  90,  270,  90},
    {CAN250kBaud, 2 ,  90,  270,  90},
    {CAN125kBaud, 3 ,  120, 360, 120},
    {CAN100kBaud, 5 ,  90,  270,  90},
    {CAN50kBaud,  9 ,  100, 300, 100},
    {CAN20kBaud,  18,  125, 375, 125},
    {CAN10kBaud,  30,  120, 480, 120},
};

#ifdef RT_CAN_USING_CANFD
/* attention !!! baud calculation example: apbclk / ((bs1 + bs2) * bittime_div), ep: 180 / ((45 + 135) * 1) = 1MHz*/
/* attention !!! default apbclk 180 mhz, ssoffset default value is 'seg1 + 1', baud_rate_fd.div must equal to baud_rate.div */
static const struct at32_baud_rate_fd canfd_baud_rate_tab[] =
{
    {CANFD_DATA_1MBaud, 1 ,  45,  135,  45, 136},
    {CANFD_DATA_2MBaud, 1 ,  18,   72,  18,  73},
    {CANFD_DATA_3MBaud, 1 ,  15,   45,  15,  46},
    {CANFD_DATA_4MBaud, 1 ,   9,   36,   9,  37},
    {CANFD_DATA_5MBaud, 1 ,   9,   27,   9,  28},
    {CANFD_DATA_6MBaud, 1 ,   6,   24,   6,  25},
};
#endif
#endif

enum {
#ifdef BSP_USING_CAN1
    CAN1_INDEX,
#endif
#ifdef BSP_USING_CAN2
    CAN2_INDEX,
#endif
#ifdef BSP_USING_CAN3
    CAN3_INDEX,
#endif
};

static struct at32_can can_config[] = {
#ifdef BSP_USING_CAN1
    CAN1_CONFIG,
#endif
#ifdef BSP_USING_CAN2
    CAN2_CONFIG,
#endif
#ifdef BSP_USING_CAN3
    CAN3_CONFIG,
#endif
};

static rt_uint32_t get_can_baud_index(rt_uint32_t baud)
{
    rt_uint32_t len, index;

    len = sizeof(can_baud_rate_tab) / sizeof(can_baud_rate_tab[0]);
    for (index = 0; index < len; index++)
    {
        if (can_baud_rate_tab[index].baud_rate == baud)
            return index;
    }
    /* default baud is CAN1MBaud */
    return 0;
}

#ifdef RT_CAN_USING_CANFD
static rt_uint32_t get_canfd_baud_index(rt_uint32_t baud)
{
    rt_uint32_t len, index;

    len = sizeof(canfd_baud_rate_tab) / sizeof(canfd_baud_rate_tab[0]);
    for (index = 0; index < len; index++)
    {
        if (canfd_baud_rate_tab[index].baud_rate == baud)
            return index;
    }
    /* default baud is CAN1MBaud */
    return 0;
}
#endif

static rt_err_t _can_config(struct rt_can_device *can, struct can_configure *cfg)
{
    rt_uint32_t baud_index;
    can_mode_type can_mode;
    can_transmit_status_type statues;

    RT_ASSERT(can);
    RT_ASSERT(cfg);

    struct at32_can *can_instance = rt_container_of(can, struct at32_can, device);
    RT_ASSERT(can_instance);

    at32_msp_can_init((void *)can_instance->can_x);
    /* config can baudrate */
    do {
        can_transmit_status_get(can_instance->can_x, &statues);
    }
    while((statues.current_tstat != CAN_TSTAT_IDLE) || (can_stb_status_get(can_instance->can_x) != CAN_STB_STATUS_EMPTY) || \
          (can_rxbuf_status_get(can_instance->can_x) != CAN_RXBUF_STATUS_EMPTY));
    can_software_reset(can_instance->can_x, TRUE);
#ifdef RT_CAN_USING_CANFD
    can_instance->enable_canfd = cfg->enable_canfd;
    if (cfg->use_bit_timing != 0U)
    {
        can_instance->can_x->lbtcfg_bit.presc = cfg->can_timing.prescaler - 1;
        can_instance->can_x->actime_bit.ac_seg_1 = cfg->can_timing.num_seg1 - 2;
        can_instance->can_x->actime_bit.ac_seg_2 = cfg->can_timing.num_seg2 - 1;
        can_instance->can_x->actime_bit.ac_sjw = cfg->can_timing.num_sjw - 1;
        can_instance->can_x->fdtime_bit.fd_seg_1 = cfg->canfd_timing.num_seg1 - 2;
        can_instance->can_x->fdtime_bit.fd_seg_2 = cfg->canfd_timing.num_seg2 - 1;
        can_instance->can_x->fdtime_bit.fd_sjw = cfg->canfd_timing.num_sjw - 1;
        can_instance->can_x->lbtcfg_bit.fd_sspoff = cfg->canfd_timing.num_sspoff;
    }
    else if(cfg->baud_rate_fd != 0U)
    {
        baud_index = get_canfd_baud_index(cfg->baud_rate_fd);
        /* get baudrate parameters */
        can_instance->can_x->fdtime_bit.fd_seg_1 = canfd_baud_rate_tab[baud_index].div - 1;
        can_instance->can_x->fdtime_bit.fd_seg_1 = canfd_baud_rate_tab[baud_index].bts1_size - 2;
        can_instance->can_x->fdtime_bit.fd_seg_2 = canfd_baud_rate_tab[baud_index].bts2_size - 1;
        can_instance->can_x->fdtime_bit.fd_sjw = canfd_baud_rate_tab[baud_index].rsaw_size - 1;
        can_instance->can_x->lbtcfg_bit.fd_sspoff = canfd_baud_rate_tab[baud_index].ssoffset;
    }
    else
#endif
    {
        baud_index = get_can_baud_index(cfg->baud_rate);
        /* get baudrate parameters */
        can_instance->can_x->lbtcfg_bit.presc = can_baud_rate_tab[baud_index].div - 1;
        can_instance->can_x->actime_bit.ac_seg_1 = can_baud_rate_tab[baud_index].bts1_size - 2;
        can_instance->can_x->actime_bit.ac_seg_2 = can_baud_rate_tab[baud_index].bts2_size - 1;
        can_instance->can_x->actime_bit.ac_sjw = can_baud_rate_tab[baud_index].rsaw_size - 1;
    }

    can_stb_transmit_mode_set(can_instance->can_x, CAN_STB_TRANSMIT_BY_FIFO);
    can_software_reset(can_instance->can_x, FALSE);

    /* config can base parameters */
    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        can_mode = CAN_MODE_COMMUNICATE;
        break;
    case RT_CAN_MODE_LISTEN:
        can_mode = CAN_MODE_LISTENONLY;
        break;
    case RT_CAN_MODE_LOOPBACK:
        can_mode = CAN_MODE_EXT_LOOPBACK;
        break;
    case RT_CAN_MODE_LOOPBACKANLISTEN:
        can_mode = CAN_MODE_LISTENONLY_EXT;
        break;
    }
    can_mode_set(can_instance->can_x, can_mode);
    can_retransmission_limit_set(can_instance->can_x, CAN_RE_TRANS_TIMES_UNLIMIT);
    can_rearbitration_limit_set(can_instance->can_x, CAN_RE_ARBI_TIMES_UNLIMIT);
    can_rxbuf_warning_set(can_instance->can_x, 3);

    return RT_EOK;
}

static rt_err_t _can_control(struct rt_can_device *can, int cmd, void *arg)
{
    rt_uint32_t argval;
    rt_uint32_t errtype;
    rt_uint8_t filter_number = 0;
    can_transmit_status_type statues;
    struct rt_can_filter_config *filter_cfg;

    RT_ASSERT(can != RT_NULL);
    struct at32_can *can_instance = rt_container_of(can, struct at32_can, device);
    RT_ASSERT(can_instance != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            nvic_irq_disable(can_instance->rx_irqn);
            /* disable interrupt */
            can_interrupt_enable(can_instance->can_x, CAN_RAFIE_INT, FALSE);
            can_interrupt_enable(can_instance->can_x, CAN_RFIE_INT, FALSE);
            can_interrupt_enable(can_instance->can_x, CAN_ROIE_INT, FALSE);
            can_interrupt_enable(can_instance->can_x, CAN_RIE_INT, FALSE);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            nvic_irq_disable(can_instance->tx_irqn);
            /* disable interrupt */
            can_interrupt_enable(can_instance->can_x, CAN_TSIE_INT, FALSE);
            can_interrupt_enable(can_instance->can_x, CAN_TPIE_INT, FALSE);
            can_interrupt_enable(can_instance->can_x, CAN_AIE_INT, FALSE);
            can_interrupt_enable(can_instance->can_x, CAN_ALIE_INT, FALSE);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            nvic_irq_disable(can_instance->err_irqn);
            /* disable interrupt */
            can_interrupt_enable(can_instance->can_x, CAN_EIE_INT, FALSE);
            can_interrupt_enable(can_instance->can_x, CAN_BEIE_INT, FALSE);
            can_interrupt_enable(can_instance->can_x, CAN_EPIE_INT, FALSE);
        }
        break;
    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            /* enable interrupt */
            can_interrupt_enable(can_instance->can_x, CAN_RAFIE_INT, TRUE);
            can_interrupt_enable(can_instance->can_x, CAN_RFIE_INT, TRUE);
            can_interrupt_enable(can_instance->can_x, CAN_ROIE_INT, TRUE);
            can_interrupt_enable(can_instance->can_x, CAN_RIE_INT, TRUE);
            nvic_irq_enable(can_instance->rx_irqn, 1, 0);

        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            /* enable interrupt */
            can_interrupt_enable(can_instance->can_x, CAN_TSIE_INT, TRUE);
            can_interrupt_enable(can_instance->can_x, CAN_TPIE_INT, TRUE);
            can_interrupt_enable(can_instance->can_x, CAN_AIE_INT, TRUE);
            can_interrupt_enable(can_instance->can_x, CAN_ALIE_INT, TRUE);
            nvic_irq_enable(can_instance->tx_irqn, 1, 0);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            /* enable interrupt */
            can_interrupt_enable(can_instance->can_x, CAN_EIE_INT, TRUE);
            can_interrupt_enable(can_instance->can_x, CAN_BEIE_INT, TRUE);
            can_interrupt_enable(can_instance->can_x, CAN_EPIE_INT, TRUE);
            nvic_irq_enable(can_instance->err_irqn, 1, 0);
        }
        break;
    case RT_CAN_CMD_SET_FILTER:
        if (RT_NULL == arg)
        {
            /* default filter config */
            can_filter_default_para_init(&can_instance->filter_init_struct);
        }
        else
        {
            filter_cfg = (struct rt_can_filter_config *)arg;
            /* get default filter */
            for (int i = 0; i < filter_cfg->count; i++)
            {
                if (filter_cfg->items[i].hdr_bank == -1)
                {
                    filter_number = i;
                }
                else
                {
                    filter_number = filter_cfg->items[i].hdr_bank;
                }

                can_instance->filter_init_struct.code_para.id = filter_cfg->items[i].id;
                can_instance->filter_init_struct.code_para.id_type = (can_identifier_type)filter_cfg->items[i].ide;
                can_instance->filter_init_struct.mask_para.id =  (~(filter_cfg->items[i].mask) & ~(filter_cfg->items[i].id & filter_cfg->items[i].mask));
                can_instance->filter_init_struct.mask_para.id_type = FALSE;
                can_instance->filter_init_struct.mask_para.data_length = 0xF;
                can_instance->filter_init_struct.mask_para.frame_type = TRUE;
                can_instance->filter_init_struct.mask_para.recv_frame = TRUE;

                /* filter configuration */
                do {
                    can_transmit_status_get(can_instance->can_x, &statues);
                }
                while((statues.current_tstat != CAN_TSTAT_IDLE) || (can_stb_status_get(can_instance->can_x) != CAN_STB_STATUS_EMPTY) || \
                      (can_rxbuf_status_get(can_instance->can_x) != CAN_RXBUF_STATUS_EMPTY));
                can_software_reset(can_instance->can_x, TRUE);
                can_filter_set(can_instance->can_x, (can_filter_type)filter_number, &can_instance->filter_init_struct);
                can_software_reset(can_instance->can_x, FALSE);
                can_filter_enable(can_instance->can_x, (can_filter_type)filter_number, TRUE);
            }
        }
        break;
    case RT_CAN_CMD_SET_MODE:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_NORMAL &&
            argval != RT_CAN_MODE_LISTEN &&
            argval != RT_CAN_MODE_LOOPBACK &&
            argval != RT_CAN_MODE_LOOPBACKANLISTEN)
        {
            return -RT_ERROR;
        }
        if (argval != can_instance->device.config.mode)
        {
            can_instance->device.config.mode = argval;
            return _can_config(&can_instance->device, &can_instance->device.config);
        }
        break;
    case RT_CAN_CMD_SET_BAUD:
        argval = (rt_uint32_t) arg;
        if (argval != CAN1MBaud   &&
            argval != CAN800kBaud &&
            argval != CAN500kBaud &&
            argval != CAN250kBaud &&
            argval != CAN125kBaud &&
            argval != CAN100kBaud &&
            argval != CAN50kBaud  &&
            argval != CAN20kBaud  &&
            argval != CAN10kBaud)
        {
            return -RT_ERROR;
        }
        if (argval != can_instance->device.config.baud_rate)
        {
            can_instance->device.config.baud_rate = argval;
            return _can_config(&can_instance->device, &can_instance->device.config);
        }
        break;
    case RT_CAN_CMD_SET_PRIV:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_PRIV &&
            argval != RT_CAN_MODE_NOPRIV)
        {
            return -RT_ERROR;
        }
        if (argval != can_instance->device.config.privmode)
        {
            can_instance->device.config.privmode = argval;
            return _can_config(&can_instance->device, &can_instance->device.config);
        }
        break;
    case RT_CAN_CMD_GET_STATUS:
        errtype = can_instance->can_x->err;
        can_instance->device.status.rcverrcnt = errtype >> 24;
        can_instance->device.status.snderrcnt = ((errtype >> 16) & 0xFF);
        can_instance->device.status.lasterrtype = ((errtype >> 13) & 0x7);

        rt_memcpy(arg, &can_instance->device.status, sizeof(can_instance->device.status));
        break;
#ifdef RT_CAN_USING_CANFD
    case RT_CAN_CMD_SET_CANFD:
        if(can_instance->enable_canfd != argval)
        {
            can_instance->enable_canfd = (rt_uint32_t) argval;
        }
        break;
    case RT_CAN_CMD_SET_BAUD_FD:
        argval = (rt_uint32_t) arg;
        if (argval != CANFD_DATA_1MBaud &&
            argval != CANFD_DATA_2MBaud &&
            argval != CANFD_DATA_3MBaud &&
            argval != CANFD_DATA_4MBaud &&
            argval != CANFD_DATA_5MBaud &&
            argval != CANFD_DATA_6MBaud)
        {
            return -RT_ERROR;
        }
        if (argval != can_instance->device.config.baud_rate_fd)
        {
            can_instance->device.config.baud_rate_fd = argval;
            return _can_config(&can_instance->device, &can_instance->device.config);
        }
        break;
    case RT_CAN_CMD_SET_BITTIMING:
        {
            struct rt_can_bit_timing_config *timing_configs = (struct rt_can_bit_timing_config*)arg;
            if ((timing_configs == RT_NULL) || (timing_configs->count < 1) || (timing_configs->count > 2))
            {
                return -RT_ERROR;
            }
            if (timing_configs->count != 0U)
            {
                can_instance->device.config.can_timing = timing_configs->items[0];
            }
            if (timing_configs->count == 2)
            {
                can_instance->device.config.canfd_timing = timing_configs->items[1];
            }
            _can_config(&can_instance->device, &can_instance->device.config);
        }
        break;
#endif
    }
    return RT_EOK;
}

static rt_ssize_t _can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_num)
{
    rt_uint8_t copy_length = 0;
    can_txbuf_type tx_message;
    struct at32_can *can_instance = rt_container_of(can, struct at32_can, device);
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;

    tx_message.id = pmsg->id;
    if (RT_CAN_STDID == pmsg->ide)
    {
        tx_message.id_type = CAN_ID_STANDARD;
    }
    else
    {
        tx_message.id_type = CAN_ID_EXTENDED;
    }

    if (RT_CAN_DTR == pmsg->rtr)
    {
        tx_message.frame_type = CAN_FRAME_DATA;
    }
    else
    {
        tx_message.frame_type = CAN_FRAME_REMOTE;
    }
#ifdef RT_CAN_USING_CANFD
    if (pmsg->fd_frame != 0)
    {
        tx_message.fd_format = CAN_FORMAT_FD;
        tx_message.fd_rate_switch = (can_rate_switch_type)pmsg->brs;
        RT_ASSERT(pmsg->len <= 15);
    }
    else
#endif
    {
        RT_ASSERT(pmsg->len <= 8);
    }

#ifdef RT_CAN_USING_CANFD
    copy_length = dlc_to_bytes[pmsg->len];
#else
    copy_length = pmsg->len;
#endif
    /* set up the data field */
    rt_memcpy(&tx_message.data[0], &pmsg->data[0], copy_length);
    /* set up the dlc */
    tx_message.data_length = (can_data_length_type)pmsg->len;
    can_txbuf_write(can_instance->can_x, CAN_TXBUF_STB, &tx_message);
    can_txbuf_transmit(can_instance->can_x, CAN_TRANSMIT_STB_ALL);
    return RT_EOK;
}

static rt_ssize_t _can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    can_rxbuf_type rx_message;
    struct at32_can *can_instance = rt_container_of(can, struct at32_can, device);
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;

    /* get data */
    can_rxbuf_read(can_instance->can_x, &rx_message);

#ifdef RT_CAN_USING_CANFD
    pmsg->len = dlc_to_bytes[rx_message.data_length];
    pmsg->fd_frame = rx_message.fd_format;
    pmsg->brs = rx_message.fd_rate_switch;
#else
    if(rx_message.data_length > 8)
        pmsg->len = 8;
    else
        pmsg->len = rx_message.data_length;
#endif
    pmsg->id = rx_message.id;
    /* get the data field */
    rt_memcpy(&pmsg->data[0], &rx_message.data[0], pmsg->len);

    if (rx_message.id_type == CAN_ID_STANDARD)
    {
        pmsg->ide = RT_CAN_STDID;
    }
    else
    {
        pmsg->ide = RT_CAN_EXTID;
    }

    pmsg->rtr = rx_message.frame_type;

    return RT_EOK;
}

static const struct rt_can_ops _can_ops =
{
    _can_config,
    _can_control,
    _can_sendmsg,
    _can_recvmsg,
};

static void _can_rx_isr(struct rt_can_device *can)
{
    struct at32_can *can_instance = rt_container_of(can, struct at32_can, device);

    /* rx_buffer had data be received */
    if(can_interrupt_flag_get(can_instance->can_x, CAN_RIF_FLAG) != RESET)
    {
        can_flag_clear(can_instance->can_x, CAN_RIF_FLAG);
        rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND);
    }

    /* rx_buffer almost full */
    if(can_interrupt_flag_get(can_instance->can_x, CAN_RAFIF_FLAG) != RESET)
    {
        can_flag_clear(can_instance->can_x, CAN_RAFIF_FLAG);
    }

    /* rx_buffer full */
    if(can_interrupt_flag_get(can_instance->can_x, CAN_RFIF_FLAG) != RESET)
    {
        can_flag_clear(can_instance->can_x, CAN_RFIF_FLAG);
    }

    /* rx_buffer overflow */
    if(can_interrupt_flag_get(can_instance->can_x, CAN_ROIF_FLAG) != RESET)
    {
        can_flag_clear(can_instance->can_x, CAN_ROIF_FLAG);
        rt_hw_can_isr(can, RT_CAN_EVENT_RXOF_IND);
    }
}

static void _can_tx_isr(struct rt_can_device *can)
{
    struct at32_can *can_instance = rt_container_of(can, struct at32_can, device);

    /* transmit buffer be completed */
    if(can_interrupt_flag_get(can_instance->can_x, CAN_TSIF_FLAG) != RESET)
    {
        can_flag_clear(can_instance->can_x, CAN_TSIF_FLAG);
        rt_hw_can_isr(can, RT_CAN_EVENT_TX_DONE);
    }
}

void _can_err_isr(struct rt_can_device *can)
{
    rt_uint32_t errtype;
    struct at32_can *can_instance = rt_container_of(can, struct at32_can, device);

    errtype = can_instance->can_x->err;

    switch (((errtype >> 13) & 0x7))
    {
    case RT_CAN_BUS_BIT_PAD_ERR:
        can_instance->device.status.bitpaderrcnt++;
        break;
    case RT_CAN_BUS_FORMAT_ERR:
        can_instance->device.status.formaterrcnt++;
        break;
    case RT_CAN_BUS_ACK_ERR:
        can_instance->device.status.ackerrcnt++;
        rt_hw_can_isr(&can_instance->device, RT_CAN_EVENT_TX_FAIL);
    case RT_CAN_BUS_IMPLICIT_BIT_ERR:
    case RT_CAN_BUS_EXPLICIT_BIT_ERR:
        can_instance->device.status.biterrcnt++;
        break;
    case RT_CAN_BUS_CRC_ERR:
        can_instance->device.status.crcerrcnt++;
        break;
    }

    can_instance->device.status.rcverrcnt = errtype >> 24;
    can_instance->device.status.snderrcnt = (errtype >> 16 & 0xFF);
    can_instance->device.status.lasterrtype = (errtype >> 13 & 0x7);
    can_flag_clear(can_instance->can_x, CAN_BEIF_FLAG);
}

#ifdef BSP_USING_CAN1
void CAN1_TX_IRQHandler(void) {
    rt_interrupt_enter();

    _can_tx_isr(&can_config[CAN1_INDEX].device);

    rt_interrupt_leave();
}

void CAN1_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    _can_rx_isr(&can_config[CAN1_INDEX].device);

    /* leave interrupt */
    rt_interrupt_leave();
}

void CAN1_ERR_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    _can_err_isr(&can_config[CAN1_INDEX].device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CAN2
void CAN2_TX_IRQHandler(void) {
    rt_interrupt_enter();

    _can_tx_isr(&can_config[CAN2_INDEX].device);

    rt_interrupt_leave();
}

void CAN2_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    _can_rx_isr(&can_config[CAN2_INDEX].device);

    /* leave interrupt */
    rt_interrupt_leave();
}

void CAN2_ERR_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    _can_err_isr(&can_config[CAN2_INDEX].device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CAN3
void CAN3_TX_IRQHandler(void) {
    rt_interrupt_enter();

    _can_tx_isr(&can_config[CAN3_INDEX].device);

    rt_interrupt_leave();
}

void CAN3_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    _can_rx_isr(&can_config[CAN3_INDEX].device);

    /* leave interrupt */
    rt_interrupt_leave();
}

void CAN3_ERR_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    _can_err_isr(&can_config[CAN3_INDEX].device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

int rt_hw_can_init(void)
{
    rt_size_t obj_num;
    int index;

    obj_num = sizeof(can_config) / sizeof(struct at32_can);
    struct can_configure config = CANDEFAULTCONFIG;

    config.privmode = RT_CAN_MODE_NOPRIV;
    config.ticks = 50;
#ifdef RT_CAN_USING_HDR
    config.maxhdr = 16;
#endif
    for (index = 0; index < obj_num; index++) {
    /* config default filter */
    can_filter_config_type filter_config;
    can_filter_default_para_init(&filter_config);

    can_config[index].filter_init_struct = filter_config;
    can_config[index].device.config = config;
    rt_hw_can_register(&can_config[index].device,
                       can_config[index].name,
                       &_can_ops,
                       &can_config[index]);
    }

    return 0;
}

INIT_BOARD_EXPORT(rt_hw_can_init);

#endif /* BSP_USING_CAN_V2 */
