/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-08     HPMicro      the first version
 * 2023-05-08     HPMicro      Adapt RT-Thread v5.0.0
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include "board.h"
#include "hpm_can_drv.h"


#define CAN_SEND_WAIT_MS_MAX (1000U)    /* CAN maximum wait time for transmission */
#define CAN_SENDBOX_NUM (1U)            /* CAN Hardware Transmission buffer number */
#define CAN_FILTER_NUM_MAX (16U)        /* CAN Hardware Filter number */


#ifdef RT_USING_CAN

typedef struct _hpm_can_struct
{
    CAN_Type *can_base;                                     /**< CAN Base address  */
    const char *name;                                       /**< CAN device name */
    int32_t irq_num;                                        /**< CAN IRQ index */
    uint32_t fifo_index;                                    /**< FIFO index, it is a fake value to satisfy the driver framework */
    can_config_t can_config;                                /**< CAN configuration for IP */
    struct rt_can_device can_dev;                           /**< CAN device configuration in rt-thread */
    uint32_t filter_num;                                    /**< Filter number */
    can_filter_config_t filter_list[CAN_FILTER_NUM_MAX];    /**< Filter list */
} hpm_can_t;

/**
 * @brief Configure CAN controller
 * @param [in/out] can CAN device pointer
 * @param [in] cfg CAN configuration pointer
 * @retval RT_EOK for valid configuration
 * @retval -RT_ERROR for invalid configuration
 */
static rt_err_t hpm_can_configure(struct rt_can_device *can, struct can_configure *cfg);

/**
 * @brief Control/Get CAN state
 *        including:interrupt, mode, priority, baudrate, filter, status
 * @param [in/out] can CAN device pointer
 * @param [in] cmd Control command
 * @param [in/out] arg Argument pointer
 * @retval RT_EOK for valid control command and arg
 * @retval -RT_ERROR for invalid control command or arg
 */
static rt_err_t hpm_can_control(struct rt_can_device *can, int cmd, void *arg);

/**
 * @brief Send out CAN message
 * @param [in] can CAN device pointer
 * @param [in] buf CAN message buffer
 * @param [in] boxno Mailbox number, it is not used in this porting
 * @retval RT_EOK No error
 * @retval -RT_ETIMEOUT timeout happened
 * @retval -RT_EFULL Transmission buffer is full
 */
static int hpm_can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno);

/**
 * @brief Receive message from CAN
 * @param [in] can CAN device pointer
 * @param [out] buf CAN receive buffer
 * @param [in] boxno Mailbox Number, it is not used in this porting
 * @retval RT_EOK no error
 * @retval -RT_ERROR Error happened during reading receive FIFO
 * @retval -RT_EMPTY no data in receive FIFO
 */
static int hpm_can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno);

/**
 * @brief Common Interrupt Service routine
 * @param [in] hpm_can HPM CAN pointer
 */
static void hpm_can_isr(hpm_can_t *hpm_can);

/**
 * @brief Decode data bytes from DLC
 * @param [in] dlc Data Length Code
 * @return decoded data bytes
 */
static uint8_t can_get_data_bytes_from_dlc(uint32_t dlc);

#if defined(HPM_CAN0_BASE) && defined(BSP_USING_CAN0)
static hpm_can_t dev_can0 =
{
    .can_base = HPM_CAN0,
    .name = "can0",
    .irq_num = IRQn_CAN0,
    .fifo_index = 0,
};

void can0_isr(void)
{
    hpm_can_isr(&dev_can0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_CAN0, can0_isr);

#endif

#if defined(HPM_CAN1_BASE) && defined(BSP_USING_CAN1)
static hpm_can_t dev_can1 =
{
        .can_base = HPM_CAN1,
        .name = "can1",
        .irq_num = IRQn_CAN1,
        .fifo_index = 1,
};
void can1_isr(void)
{
    hpm_can_isr(&dev_can1);
}
SDK_DECLARE_EXT_ISR_M(IRQn_CAN1, can1_isr);
#endif

#if defined(HPM_CAN2_BASE) && defined(BSP_USING_CAN2)
static hpm_can_t dev_can2 =
{
        .can_base = HPM_CAN2,
        .name = "can2",
        .irq_num = IRQn_CAN2,
        .fifo_index = 2,
};
void can2_isr(void)
{
    hpm_can_isr(&dev_can2);
}
SDK_DECLARE_EXT_ISR_M(IRQn_CAN2, can2_isr);
#endif

#if defined(HPM_CAN3_BASE) && defined(BSP_USING_CAN3)
static hpm_can_t dev_can3 =
{
        .can_base = HPM_CAN3,
        .name = "can3",
        .irq_num = IRQn_CAN3,
        .fifo_index = 3,
};
void can3_isr(void)
{
    hpm_can_isr(&dev_can3);
}
SDK_DECLARE_EXT_ISR_M(IRQn_CAN3, can3_isr);
#endif

static hpm_can_t *hpm_cans[] = {
#if defined(HPM_CAN0_BASE) && defined(BSP_USING_CAN0)
        &dev_can0,
#endif
#if defined(HPM_CAN1_BASE) && defined(BSP_USING_CAN1)
        &dev_can1,
#endif
#if defined(HPM_CAN2_BASE) && defined(BSP_USING_CAN2)
        &dev_can2,
#endif
#if defined(HPM_CAN3_BASE) && defined(BSP_USING_CAN3)
        &dev_can3,
#endif
        };


static const struct rt_can_ops hpm_can_ops = {
        .configure = hpm_can_configure,
        .control = hpm_can_control,
        .sendmsg = hpm_can_sendmsg,
        .recvmsg = hpm_can_recvmsg,
};



static void hpm_can_isr(hpm_can_t *hpm_can)
{
    uint8_t tx_rx_flags = can_get_tx_rx_flags(hpm_can->can_base);
    uint8_t error_flags = can_get_error_interrupt_flags(hpm_can->can_base);

    /* High-priority message transmission done */
    if ((tx_rx_flags & CAN_EVENT_TX_PRIMARY_BUF) != 0U)
    {
        rt_hw_can_isr(&hpm_can->can_dev, RT_CAN_EVENT_TX_DONE | (0UL << 8));
    }

    /* Normal priority message transmission done */
    if ((tx_rx_flags & CAN_EVENT_TX_SECONDARY_BUF) != 0U)
    {
        rt_hw_can_isr(&hpm_can->can_dev, RT_CAN_EVENT_TX_DONE | (0UL << 8));
    }

    /* Data available in FIFO */
    if ((tx_rx_flags & CAN_EVENT_RECEIVE) == CAN_EVENT_RECEIVE)
    {
        rt_hw_can_isr(&hpm_can->can_dev, RT_CAN_EVENT_RX_IND | (hpm_can->fifo_index << 8));
    }

    /* RX FIFO overflow */
    if ((tx_rx_flags & CAN_EVENT_RX_BUF_OVERRUN) != 0U)
    {
        rt_hw_can_isr(&hpm_can->can_dev, RT_CAN_EVENT_RXOF_IND | (hpm_can->fifo_index << 8));
    }

    /* Error happened on CAN Bus */
    if (((tx_rx_flags & CAN_EVENT_ERROR) != 0U) || (error_flags != 0U))
    {
        uint8_t err_kind = can_get_last_error_kind(hpm_can->can_base);
        switch(err_kind)
        {
        case CAN_KIND_OF_ERROR_ACK_ERROR:
            hpm_can->can_dev.status.ackerrcnt++;
            break;
        case CAN_KIND_OF_ERROR_BIT_ERROR:
            hpm_can->can_dev.status.biterrcnt++;
            break;
        case CAN_KIND_OF_ERROR_CRC_ERROR:
            hpm_can->can_dev.status.crcerrcnt++;
            break;
        case CAN_KIND_OF_ERROR_FORM_ERROR:
            hpm_can->can_dev.status.formaterrcnt++;
            break;
        case CAN_KIND_OF_ERROR_STUFF_ERROR:
            hpm_can->can_dev.status.bitpaderrcnt++;
            break;
        }

        hpm_can->can_dev.status.rcverrcnt = can_get_receive_error_count(hpm_can->can_base);
        hpm_can->can_dev.status.snderrcnt = can_get_transmit_error_count(hpm_can->can_base);
        hpm_can->can_dev.status.lasterrtype = can_get_last_error_kind(hpm_can->can_base);
        hpm_can->can_dev.status.errcode = 0;
        if ((error_flags & CAN_ERROR_WARNING_LIMIT_FLAG) != 0U)
        {
            hpm_can->can_dev.status.errcode |= ERRWARNING;
        }
        if ((error_flags & CAN_ERROR_PASSIVE_INT_FLAG) != 0U)
        {
            hpm_can->can_dev.status.errcode |= ERRPASSIVE;
        }
        if (can_is_in_bus_off_mode(hpm_can->can_base))
        {
            hpm_can->can_dev.status.errcode |= BUSOFF;
        }
    }

    can_clear_tx_rx_flags(hpm_can->can_base, tx_rx_flags);
    can_clear_error_interrupt_flags(hpm_can->can_base, error_flags);
}

static rt_err_t hpm_can_configure(struct rt_can_device *can, struct can_configure *cfg)
{
    RT_ASSERT(can);
    RT_ASSERT(cfg);

    hpm_can_t *drv_can = (hpm_can_t*) can->parent.user_data;
    RT_ASSERT(drv_can);

#ifdef RT_CAN_USING_CANFD
    drv_can->can_config.enable_canfd = (cfg->enable_canfd != 0) ? true : false;
    if (cfg->use_bit_timing != 0U)
    {
        drv_can->can_config.use_lowlevel_timing_setting = true;
        drv_can->can_config.can_timing.prescaler = cfg->can_timing.prescaler;
        drv_can->can_config.can_timing.num_seg1 = cfg->can_timing.num_seg1;
        drv_can->can_config.can_timing.num_seg2 = cfg->can_timing.num_seg2;
        drv_can->can_config.can_timing.num_sjw = cfg->can_timing.num_sjw;

        drv_can->can_config.canfd_timing.prescaler = cfg->canfd_timing.prescaler;
        drv_can->can_config.canfd_timing.num_seg1 = cfg->canfd_timing.num_seg1;
        drv_can->can_config.canfd_timing.num_seg2 = cfg->canfd_timing.num_seg2;
        drv_can->can_config.canfd_timing.num_sjw = cfg->canfd_timing.num_sjw;
    }
    else
#endif
    {
        drv_can->can_config.use_lowlevel_timing_setting = false;
        drv_can->can_config.baudrate = cfg->baud_rate;
#ifdef RT_CAN_USING_CANFD
        drv_can->can_config.baudrate_fd = cfg->baud_rate_fd;
#endif
    }


    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        drv_can->can_config.mode = can_mode_normal;
        break;
    case RT_CAN_MODE_LISTEN:
        drv_can->can_config.mode = can_mode_listen_only;
        break;
    case RT_CAN_MODE_LOOPBACK:
        drv_can->can_config.mode = can_mode_loopback_internal;
        break;
    default:
        return -RT_ERROR;
        break;
    }

    drv_can->can_config.enable_tx_buffer_priority_mode = (cfg->privmode != 0U) ? true : false;
    init_can_pins(drv_can->can_base);
    uint32_t can_clk = board_init_can_clock(drv_can->can_base);
    drv_can->can_config.filter_list_num = drv_can->filter_num;
    drv_can->can_config.filter_list = &drv_can->filter_list[0];
    hpm_stat_t status = can_init(drv_can->can_base, &drv_can->can_config, can_clk);
    if (status != status_success)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t hpm_can_control(struct rt_can_device *can, int cmd, void *arg)
{
    RT_ASSERT(can);

    hpm_can_t *drv_can = (hpm_can_t*) can->parent.user_data;
    RT_ASSERT(drv_can);

    uint32_t arg_val;
    rt_err_t err = RT_EOK;

    uint32_t temp;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        arg_val = (uint32_t) arg;
        intc_m_disable_irq(drv_can->irq_num);
        if (arg_val == RT_DEVICE_FLAG_INT_RX)
        {
            uint8_t irq_txrx_mask = CAN_EVENT_RECEIVE | CAN_EVENT_RX_BUF_ALMOST_FULL | CAN_EVENT_RX_BUF_FULL | CAN_EVENT_RX_BUF_OVERRUN;
            drv_can->can_config.irq_txrx_enable_mask &= (uint8_t)~irq_txrx_mask;
            can_disable_tx_rx_irq(drv_can->can_base, irq_txrx_mask);
        }
        else if (arg_val == RT_DEVICE_FLAG_INT_TX)
        {
            uint8_t irq_txrx_mask = CAN_EVENT_TX_PRIMARY_BUF | CAN_EVENT_TX_SECONDARY_BUF;
            drv_can->can_config.irq_txrx_enable_mask &= (uint8_t)~irq_txrx_mask;
            can_disable_tx_rx_irq(drv_can->can_base, irq_txrx_mask);
        }
        else if (arg_val == RT_DEVICE_CAN_INT_ERR)
        {
            uint8_t irq_txrx_mask = CAN_EVENT_ERROR;
            uint8_t irq_error_mask = CAN_ERROR_ARBITRAITION_LOST_INT_ENABLE | CAN_ERROR_PASSIVE_INT_ENABLE | CAN_ERROR_BUS_ERROR_INT_ENABLE;
            drv_can->can_config.irq_txrx_enable_mask &= (uint8_t)~irq_txrx_mask;
            drv_can->can_config.irq_error_enable_mask &= (uint8_t)~irq_error_mask;
            can_disable_tx_rx_irq(drv_can->can_base, irq_txrx_mask);
            can_disable_error_irq(drv_can->can_base, irq_error_mask);
        }
        else
        {
            err = -RT_ERROR;
        }
        break;
    case RT_DEVICE_CTRL_SET_INT:
        arg_val = (uint32_t) arg;
        if (arg_val == RT_DEVICE_FLAG_INT_RX)
        {
            uint8_t irq_txrx_mask = CAN_EVENT_RECEIVE | CAN_EVENT_RX_BUF_ALMOST_FULL | CAN_EVENT_RX_BUF_FULL | CAN_EVENT_RX_BUF_OVERRUN;
            drv_can->can_config.irq_txrx_enable_mask |= irq_txrx_mask;
            can_enable_tx_rx_irq(drv_can->can_base, irq_txrx_mask);
            intc_m_enable_irq_with_priority(drv_can->irq_num, 1);
        }
        else if (arg_val == RT_DEVICE_FLAG_INT_TX)
        {
            uint8_t irq_txrx_mask = CAN_EVENT_TX_PRIMARY_BUF | CAN_EVENT_TX_SECONDARY_BUF;
            drv_can->can_config.irq_txrx_enable_mask |= irq_txrx_mask;
            can_enable_tx_rx_irq(drv_can->can_base, irq_txrx_mask);
            intc_m_enable_irq_with_priority(drv_can->irq_num, 1);
        }
        else if (arg_val == RT_DEVICE_CAN_INT_ERR)
        {
            uint8_t irq_txrx_mask = CAN_EVENT_ERROR;
            uint8_t irq_error_mask = CAN_ERROR_ARBITRAITION_LOST_INT_ENABLE | CAN_ERROR_PASSIVE_INT_ENABLE | CAN_ERROR_BUS_ERROR_INT_ENABLE;
            drv_can->can_config.irq_txrx_enable_mask |= irq_txrx_mask;
            drv_can->can_config.irq_error_enable_mask |= irq_error_mask;
            can_enable_tx_rx_irq(drv_can->can_base, irq_txrx_mask);
            can_enable_error_irq(drv_can->can_base, irq_error_mask);
            intc_m_enable_irq_with_priority(drv_can->irq_num, 1);
        }
        else
        {
            err = -RT_ERROR;
        }
        break;
    case RT_CAN_CMD_SET_FILTER:
        {
            /* Convert the RT-Thread Filter format to the filter format supported by HPM CAN */
            struct rt_can_filter_config *filter = (struct rt_can_filter_config*)arg;
            if (filter != NULL)
            {
                drv_can->filter_num = filter->count;
                RT_ASSERT(filter->count <= CAN_FILTER_NUM_MAX);
                for (uint32_t i=0; i<filter->count; i++)
                {
                    drv_can->filter_list[i].index = i;
                    drv_can->filter_list[i].enable = (filter->actived != 0U) ? true : false;
                    drv_can->filter_list[i].code = filter->items[i].id;
                    drv_can->filter_list[i].id_mode = (filter->items[i].ide != 0U) ? can_filter_id_mode_extended_frames : can_filter_id_mode_standard_frames;
                    drv_can->filter_list[i].mask = (~filter->items[i].mask) & ~(7UL <<29);
                }
            }
            else
            {
                drv_can->filter_num = 0;
            }
            err = hpm_can_configure(can, &drv_can->can_dev.config);
        }
        break;
    case RT_CAN_CMD_SET_MODE:
        arg_val = (uint32_t) arg;
        if ((arg_val != RT_CAN_MODE_NORMAL) && (arg_val != RT_CAN_MODE_LISTEN) && (arg_val != RT_CAN_MODE_LOOPBACK))
        {
            err = -RT_ERROR;
            break;
        }
        if (arg_val != drv_can->can_dev.config.mode)
        {
            drv_can->can_dev.config.mode = arg_val;
            err = hpm_can_configure(can, &drv_can->can_dev.config);
        }

        break;
    case RT_CAN_CMD_SET_BAUD:
        arg_val = (uint32_t) arg;
        if (arg_val != drv_can->can_dev.config.baud_rate)
        {
            drv_can->can_dev.config.baud_rate = arg_val;
        }
        err = hpm_can_configure(can, &drv_can->can_dev.config);
        break;
#ifdef RT_CAN_USING_CANFD
    case RT_CAN_CMD_SET_CANFD:
        arg_val = (uint32_t) arg;
        if (arg_val != drv_can->can_dev.config.enable_canfd)
        {
            drv_can->can_dev.config.enable_canfd = arg_val;
            err = hpm_can_configure(can, &drv_can->can_dev.config);
        }
        break;
    case RT_CAN_CMD_SET_BAUD_FD:
        arg_val = (uint32_t) arg;
        if (arg_val != drv_can->can_dev.config.baud_rate_fd)
        {
            drv_can->can_dev.config.baud_rate_fd = arg_val;
            err = hpm_can_configure(can, &drv_can->can_dev.config);
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
                drv_can->can_dev.config.can_timing = timing_configs->items[0];
            }
            if (timing_configs->count == 2)
            {
                drv_can->can_dev.config.canfd_timing = timing_configs->items[1];
            }
            err = hpm_can_configure(can, &drv_can->can_dev.config);
        }
        break;
#endif
    case RT_CAN_CMD_SET_PRIV:
        arg_val = (uint32_t)arg;
        if ((arg_val != RT_CAN_MODE_PRIV) && (arg_val != RT_CAN_MODE_NOPRIV))
        {
            return -RT_ERROR;
        }
        if (arg_val != drv_can->can_dev.config.privmode)
        {
            drv_can->can_dev.config.privmode = arg_val;
            err = hpm_can_configure(can, &drv_can->can_dev.config);
        }
        break;
    case RT_CAN_CMD_GET_STATUS:
        drv_can->can_dev.status.rcverrcnt = can_get_receive_error_count(drv_can->can_base);
        drv_can->can_dev.status.snderrcnt = can_get_transmit_error_count(drv_can->can_base);
        drv_can->can_dev.status.lasterrtype = can_get_last_error_kind(drv_can->can_base);
        temp = can_get_error_interrupt_flags(drv_can->can_base);
        drv_can->can_dev.status.errcode = 0;
        if ((temp & CAN_ERROR_WARNING_LIMIT_FLAG) != 0U)
        {
            drv_can->can_dev.status.errcode |= ERRWARNING;
        }
        if ((temp & CAN_ERROR_PASSIVE_INT_FLAG) != 0U)
        {
            drv_can->can_dev.status.errcode |= ERRPASSIVE;
        }
        if (can_is_in_bus_off_mode(drv_can->can_base))
        {
            drv_can->can_dev.status.errcode |= BUSOFF;
        }
        rt_memcpy(arg, &drv_can->can_dev.status, sizeof(drv_can->can_dev.status));
        break;
    }
}

static int hpm_can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno)
{
    RT_ASSERT(can);

    hpm_can_t *drv_can = (hpm_can_t*) can->parent.user_data;
    RT_ASSERT(drv_can);

    struct rt_can_msg *can_msg = (struct rt_can_msg *) buf;

    can_transmit_buf_t tx_buf = { 0 };
    tx_buf.id = can_msg->id;
    if (can_msg->ide == RT_CAN_STDID)
    {
        tx_buf.extend_id = false;
    }
    else
    {
        tx_buf.extend_id = true;
    }

    if (can_msg->rtr == RT_CAN_DTR)
    {
        tx_buf.remote_frame = false;
    }
    else
    {
        tx_buf.remote_frame = true;
    }

#ifdef RT_CAN_USING_CANFD
    if (can_msg->fd_frame != 0)
    {
        tx_buf.canfd_frame = 1;
        tx_buf.bitrate_switch = 1;

        RT_ASSERT(can_msg->len <= 15);
    }
    else
#endif
    {
        RT_ASSERT(can_msg->len <= 8);
    }

    uint32_t msg_len = can_get_data_bytes_from_dlc(can_msg->len);
    for (uint32_t i = 0; i < msg_len; i++)
    {
        tx_buf.data[i] = can_msg->data[i];
    }
    tx_buf.dlc = can_msg->len;

    uint32_t delay_cnt = 0;

   if (can_msg->priv != 0U)
    {
        while (can_is_primary_transmit_buffer_full(drv_can->can_base))
        {
            rt_thread_mdelay(1);
            delay_cnt++;
            if (delay_cnt >= CAN_SEND_WAIT_MS_MAX)
            {
                return -RT_ETIMEOUT;
            }
        }
        hpm_stat_t status = can_send_message_nonblocking(drv_can->can_base, &tx_buf);
        if (status != status_success)
        {
            return -RT_EFULL;
        }
    }
    else
    {
        while (can_is_secondary_transmit_buffer_full(drv_can->can_base))
        {
            rt_thread_mdelay(1);
            delay_cnt++;
            if (delay_cnt >= CAN_SEND_WAIT_MS_MAX)
            {
                return -RT_ETIMEOUT;
            }
        }
        hpm_stat_t status = can_send_message_nonblocking(drv_can->can_base, &tx_buf);
        if (status != status_success)
        {
            return -RT_EFULL;
        }
    }

    return RT_EOK;
}

static int hpm_can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno)
{
    RT_ASSERT(can);

    hpm_can_t *drv_can = (hpm_can_t*) can->parent.user_data;
    RT_ASSERT(drv_can);

    rt_can_msg_t can_msg = (rt_can_msg_t)buf;

    if (can_is_data_available_in_receive_buffer(drv_can->can_base)) {
        can_receive_buf_t rx_buf;
        hpm_stat_t status = can_read_received_message(drv_can->can_base, &rx_buf);
        if (status != status_success) {
            return -RT_ERROR;
        }

        if (rx_buf.extend_id != 0) {
            can_msg->ide = RT_CAN_EXTID;
        }
        else {
            can_msg->ide = RT_CAN_STDID;
        }
        can_msg->id = rx_buf.id;

        if (rx_buf.remote_frame != 0) {
            can_msg->rtr = RT_CAN_RTR;
        }
        else {
            can_msg->rtr = RT_CAN_DTR;
        }

        can_msg->len = rx_buf.dlc;
        uint32_t msg_len = can_get_data_bytes_from_dlc(can_msg->len);
        for(uint32_t i = 0; i < msg_len; i++) {
            can_msg->data[i] = rx_buf.data[i];
        }
    }
    else {
        return -RT_EEMPTY;
    }

    return RT_EOK;
}

static uint8_t can_get_data_bytes_from_dlc(uint32_t dlc)
{
    uint32_t data_bytes = 0;

    dlc &= 0xFU;
    if (dlc <= 8U) {
        data_bytes = dlc;
    } else {
        switch (dlc) {
            case can_payload_size_12:
                data_bytes = 12U;
                break;
            case can_payload_size_16:
                data_bytes = 16U;
                break;
            case can_payload_size_20:
                data_bytes = 20U;
                break;
            case can_payload_size_24:
                data_bytes = 24U;
                break;
            case can_payload_size_32:
                data_bytes = 32U;
                break;
            case can_payload_size_48:
                data_bytes = 48U;
                break;
            case can_payload_size_64:
                data_bytes = 64U;
                break;
            default:
                /* Code should never touch here */
                break;
        }
    }

    return data_bytes;
}

int rt_hw_can_init(void)
{
    struct can_configure config = CANDEFAULTCONFIG;
    config.privmode = RT_CAN_MODE_NOPRIV;
    config.sndboxnumber = CAN_SENDBOX_NUM;
    config.ticks = 50;

    for (uint32_t i = 0; i < ARRAY_SIZE(hpm_cans); i++)
    {
        hpm_cans[i]->can_dev.config = config;
        hpm_cans[i]->filter_num = 0;
        can_get_default_config(&hpm_cans[i]->can_config);
        rt_hw_can_register(&hpm_cans[i]->can_dev, hpm_cans[i]->name, &hpm_can_ops, hpm_cans[i]);
    }
    return RT_EOK;
}

INIT_BOARD_EXPORT(rt_hw_can_init);

#endif
