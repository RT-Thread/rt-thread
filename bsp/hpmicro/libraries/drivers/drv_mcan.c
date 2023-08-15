/*
 * Copyright (c) 2021 - 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-07     HPMicro      the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include "board.h"
#include "hpm_mcan_drv.h"


#define CAN_SEND_WAIT_MS_MAX   (1000U)       /* CAN maximum wait time for transmission */
#define CAN_SENDBOX_NUM        (1U)          /* CAN Hardware Transmission buffer number */
#define CAN_STD_FILTER_NUM_MAX (128U)        /* std Filter number */
#define CAN_EXT_FILTER_NUM_MAX (64U)         /* ext Filter number */

#ifdef RT_USING_CAN

typedef struct _hpm_can_struct
{
    MCAN_Type *can_base;                                     /**< CAN Base address  */
    const char *name;                                       /**< CAN device name */
    int32_t irq_num;                                        /**< CAN IRQ index */
    uint32_t fifo_index;                                    /**< FIFO index, it is a fake value to satisfy the driver framework */
    mcan_config_t can_config;                               /**< CAN configuration for IP */
    struct rt_can_device can_dev;                           /**< CAN device configuration in rt-thread */
    uint32_t irq_txrx_err_enable_mask;                          /**< CAN TX and RX IRQ Enable Mask */
    uint32_t std_filter_num;                                /**< std Filter number */
    mcan_filter_elem_t std_can_filters[CAN_STD_FILTER_NUM_MAX];
    uint32_t ext_filter_num;                                /**< ext Filter number */
    mcan_filter_elem_t ext_can_filters[CAN_EXT_FILTER_NUM_MAX];
} hpm_can_t;

static const mcan_filter_elem_t k_default_std_id_filter = {
    /* Use classic filter */
    .filter_type = MCAN_FILTER_TYPE_CLASSIC_FILTER,
    /* Store message into RXFIFO0 if matching */
    .filter_config = MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO0_IF_MATCH,
    /* For Standard Identify only */
    .can_id_type = MCAN_CAN_ID_TYPE_STANDARD,
    /* Sync Message, only evaluated when "CCCR.UTSU" is set */
    .sync_message = 0U,
    /* Don't care if mask is set to all 1s */
    .filter_id = 0U,
    /* Accept all messages */
    .filter_mask = 0x7FFU,
};

static const mcan_filter_elem_t k_default_ext_id_filter = {
    /* Use classic filter */
    .filter_type = MCAN_FILTER_TYPE_CLASSIC_FILTER,
    /* Store message into RXFIFO0 if matching */
    .filter_config = MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO0_IF_MATCH,
    /* For Standard Identify only */
    .can_id_type = MCAN_CAN_ID_TYPE_EXTENDED,
    /* Sync Message, only evaluated when "CCCR.UTSU" is set */
    .sync_message = 0,
    /* Don't care if mask is set to all 1s */
    .filter_id = 0,
    /* Accept all messages */
    .filter_mask = 0x1FFFFFFFUL,
};


/**
 * @brief Configure CAN controller
 * @param [in/out] can CAN device pointer
 * @param [in] cfg CAN configuration pointer
 * @retval RT_EOK for valid configuration
 * @retval -RT_ERROR for invalid configuration
 */
static rt_err_t hpm_mcan_configure(struct rt_can_device *can, struct can_configure *cfg);

/**
 * @brief Control/Get CAN state
 *        including:interrupt, mode, priority, baudrate, filter, status
 * @param [in/out] can CAN device pointer
 * @param [in] cmd Control command
 * @param [in/out] arg Argument pointer
 * @retval RT_EOK for valid control command and arg
 * @retval -RT_ERROR for invalid control command or arg
 */
static rt_err_t hpm_mcan_control(struct rt_can_device *can, int cmd, void *arg);

/**
 * @brief Send out CAN message
 * @param [in] can CAN device pointer
 * @param [in] buf CAN message buffer
 * @param [in] boxno Mailbox number, it is not used in this porting
 * @retval RT_EOK No error
 * @retval -RT_ETIMEOUT timeout happened
 * @retval -RT_EFULL Transmission buffer is full
 */
static int hpm_mcan_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno);

/**
 * @brief Receive message from CAN
 * @param [in] can CAN device pointer
 * @param [out] buf CAN receive buffer
 * @param [in] boxno Mailbox Number, it is not used in this porting
 * @retval RT_EOK no error
 * @retval -RT_ERROR Error happened during reading receive FIFO
 * @retval -RT_EMPTY no data in receive FIFO
 */
static int hpm_mcan_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno);

/**
 * @brief Common Interrupt Service routine
 * @param [in] hpm_can HPM CAN pointer
 */
static void hpm_mcan_isr(hpm_can_t *hpm_can);

/**
 * @brief Decode data bytes from DLC
 * @param [in] dlc Data Length Code
 * @return decoded data bytes
 */
static uint8_t can_get_data_bytes_from_dlc(uint32_t dlc);

#if defined(HPM_MCAN0_BASE) && defined(BSP_USING_MCAN0)
static hpm_can_t dev_can0 =
{
    .can_base = HPM_MCAN0,
    .name = "can0",
    .irq_num = IRQn_CAN0,
    .fifo_index = 0,
};

void can0_isr(void)
{
    hpm_mcan_isr(&dev_can0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_CAN0, can0_isr);

#endif

#if defined(HPM_MCAN1_BASE) && defined(BSP_USING_MCAN1)
static hpm_can_t dev_can1 =
{
        .can_base = HPM_MCAN1,
        .name = "can1",
        .irq_num = IRQn_CAN1,
        .fifo_index = 1,
};
void can1_isr(void)
{
    hpm_mcan_isr(&dev_can1);
}
SDK_DECLARE_EXT_ISR_M(IRQn_CAN1, can1_isr);
#endif

#if defined(HPM_MCAN2_BASE) && defined(BSP_USING_MCAN2)
static hpm_can_t dev_can2 =
{
        .can_base = HPM_MCAN2,
        .name = "can2",
        .irq_num = IRQn_CAN2,
        .fifo_index = 2,
};
void can2_isr(void)
{
    hpm_mcan_isr(&dev_can2);
}
SDK_DECLARE_EXT_ISR_M(IRQn_CAN2, can2_isr);
#endif

#if defined(HPM_MCAN3_BASE) && defined(BSP_USING_MCAN3)
static hpm_can_t dev_can3 =
{
        .can_base = HPM_MCAN3,
        .name = "can3",
        .irq_num = IRQn_CAN3,
        .fifo_index = 3,
};
void can3_isr(void)
{
    hpm_mcan_isr(&dev_can3);
}
SDK_DECLARE_EXT_ISR_M(IRQn_CAN3, can3_isr);
#endif

static hpm_can_t *hpm_cans[] = {
#if defined(HPM_MCAN0_BASE) && defined(BSP_USING_MCAN0)
        &dev_can0,
#endif
#if defined(HPM_MCAN1_BASE) && defined(BSP_USING_MCAN1)
        &dev_can1,
#endif
#if defined(HPM_MCAN2_BASE) && defined(BSP_USING_MCAN2)
        &dev_can2,
#endif
#if defined(HPM_MCAN3_BASE) && defined(BSP_USING_MCAN3)
        &dev_can3,
#endif
        };


static const struct rt_can_ops hpm_can_ops = {
        .configure = hpm_mcan_configure,
        .control   = hpm_mcan_control,
        .sendmsg   = hpm_mcan_sendmsg,
        .recvmsg   = hpm_mcan_recvmsg,
};



static void hpm_mcan_isr(hpm_can_t *hpm_can)
{
    uint8_t error_flags = mcan_get_last_error_code(hpm_can->can_base);
    uint32_t flags = mcan_get_interrupt_flags(hpm_can->can_base);
    mcan_error_count_t err_cnt;
    /* Transmit completed */
    if ((flags & (MCAN_EVENT_TRANSMIT)) != 0U) {
        rt_hw_can_isr(&hpm_can->can_dev, RT_CAN_EVENT_TX_DONE | (0UL << 8));
    }

    /* Data available in FIFO */
    if ((flags & MCAN_EVENT_RECEIVE) != 0)
    {
        rt_hw_can_isr(&hpm_can->can_dev, RT_CAN_EVENT_RX_IND | (hpm_can->fifo_index << 8));
    }

    /* RX FIFO overflow */
    if ((flags & MCAN_INT_RXFIFO0_FULL) != 0U)
    {
        rt_hw_can_isr(&hpm_can->can_dev, RT_CAN_EVENT_RXOF_IND | (hpm_can->fifo_index << 8));
    }

    if ((flags & MCAN_INT_RXFIFO1_FULL) != 0U)
    {
        rt_hw_can_isr(&hpm_can->can_dev, RT_CAN_EVENT_RXOF_IND | (hpm_can->fifo_index << 8));
    }

    /* Error happened on CAN Bus */
    if (((flags & MCAN_EVENT_ERROR) != 0U) || (error_flags != 0U))
    {
        mcan_get_error_counter(hpm_can->can_base, &err_cnt);
        switch(error_flags)
        {
        case 3:
            hpm_can->can_dev.status.ackerrcnt++;
            break;
        case 4:
            hpm_can->can_dev.status.biterrcnt++;
            break;
        case 6:
            hpm_can->can_dev.status.crcerrcnt++;
            break;
        case 2:
            hpm_can->can_dev.status.formaterrcnt++;
            break;
        case 1:
            hpm_can->can_dev.status.bitpaderrcnt++;
            break;
        }

        hpm_can->can_dev.status.rcverrcnt = err_cnt.receive_error_count;
        hpm_can->can_dev.status.snderrcnt = err_cnt.transmit_error_count;
        hpm_can->can_dev.status.lasterrtype = mcan_get_last_error_code(hpm_can->can_base);
        hpm_can->can_dev.status.errcode = 0;
        if ((error_flags & MCAN_INT_WARNING_STATUS) != 0U)
        {
            hpm_can->can_dev.status.errcode |= ERRWARNING;
        }
        if ((error_flags & MCAN_INT_ERROR_PASSIVE) != 0U)
        {
            hpm_can->can_dev.status.errcode |= ERRPASSIVE;
        }
        if (mcan_is_in_busoff_state(hpm_can->can_base))
        {
            hpm_can->can_dev.status.errcode |= BUSOFF;
        }
    }

    mcan_clear_interrupt_flags(hpm_can->can_base, flags);
}

static rt_err_t hpm_mcan_configure(struct rt_can_device *can, struct can_configure *cfg)
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
        drv_can->can_config.mode = mcan_mode_normal;
        break;
    case RT_CAN_MODE_LISTEN:
        drv_can->can_config.mode = mcan_mode_listen_only;
        break;
    case RT_CAN_MODE_LOOPBACK:
        drv_can->can_config.mode = mcan_mode_loopback_internal;
        break;
    default:
        return -RT_ERROR;
        break;
    }

    init_can_pins(drv_can->can_base);
    uint32_t can_clk = board_init_can_clock(drv_can->can_base);

    drv_can->can_config.all_filters_config.std_id_filter_list.filter_elem_list                        = &drv_can->std_can_filters[0];
    drv_can->can_config.all_filters_config.std_id_filter_list.mcan_filter_elem_count                  = drv_can->std_filter_num;
    drv_can->can_config.all_filters_config.ext_id_filter_list.filter_elem_list                        = &drv_can->ext_can_filters[0];
    drv_can->can_config.all_filters_config.ext_id_filter_list.mcan_filter_elem_count                  = drv_can->ext_filter_num;
    drv_can->can_config.all_filters_config.ext_id_mask                                                = (1UL << 30) - 1UL;

    hpm_stat_t status = mcan_init(drv_can->can_base, &drv_can->can_config, can_clk);
    if (status != status_success)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t hpm_mcan_control(struct rt_can_device *can, int cmd, void *arg)
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
            uint32_t irq_txrx_mask = MCAN_EVENT_RECEIVE;
            drv_can->irq_txrx_err_enable_mask &= ~irq_txrx_mask;
            mcan_disable_interrupts(drv_can->can_base, drv_can->irq_txrx_err_enable_mask);
        }
        else if (arg_val == RT_DEVICE_FLAG_INT_TX)
        {
            uint32_t irq_txrx_mask = MCAN_EVENT_TRANSMIT;
            drv_can->irq_txrx_err_enable_mask &= ~irq_txrx_mask;
            mcan_disable_interrupts(drv_can->can_base, drv_can->irq_txrx_err_enable_mask);
            mcan_disable_txbuf_interrupt(drv_can->can_base, ~0UL);
        } else if (arg_val == RT_DEVICE_CAN_INT_ERR) {
            uint32_t irq_txrx_mask = MCAN_EVENT_ERROR;
            drv_can->irq_txrx_err_enable_mask &= ~irq_txrx_mask;
            mcan_disable_interrupts(drv_can->can_base, drv_can->irq_txrx_err_enable_mask);
        } else {
            err = -RT_ERROR;
        }
        break;
    case RT_DEVICE_CTRL_SET_INT:
        arg_val = (uint32_t) arg;
        if (arg_val == RT_DEVICE_FLAG_INT_RX)
        {
            uint32_t irq_txrx_mask = MCAN_EVENT_RECEIVE;
            drv_can->irq_txrx_err_enable_mask |= irq_txrx_mask;
            mcan_enable_interrupts(drv_can->can_base, drv_can->irq_txrx_err_enable_mask);
            intc_m_enable_irq_with_priority(drv_can->irq_num, 1);
        }
        else if (arg_val == RT_DEVICE_FLAG_INT_TX)
        {
            uint32_t irq_txrx_mask = MCAN_EVENT_TRANSMIT;
            drv_can->irq_txrx_err_enable_mask |= irq_txrx_mask;
            mcan_enable_interrupts(drv_can->can_base, drv_can->irq_txrx_err_enable_mask);
            mcan_enable_txbuf_interrupt(drv_can->can_base, ~0UL);
            intc_m_enable_irq_with_priority(drv_can->irq_num, 1);
        }
        else if (arg_val == RT_DEVICE_CAN_INT_ERR)
        {
            uint32_t irq_txrx_mask = MCAN_EVENT_ERROR;
            drv_can->irq_txrx_err_enable_mask |= irq_txrx_mask;
            mcan_enable_interrupts(drv_can->can_base, drv_can->irq_txrx_err_enable_mask);
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
            drv_can->std_filter_num = 0;
            drv_can->ext_filter_num = 0;
            if (filter != NULL)
            {
                for (uint32_t i = 0; i < filter->count; i++)
                {
                    if (filter->items[i].ide != 0)
                    {
                        drv_can->ext_can_filters[drv_can->ext_filter_num].filter_type   = MCAN_FILTER_TYPE_CLASSIC_FILTER;
                        drv_can->ext_can_filters[drv_can->ext_filter_num].filter_config = MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO0_IF_MATCH;
                        drv_can->ext_can_filters[drv_can->ext_filter_num].can_id_type   = MCAN_CAN_ID_TYPE_EXTENDED;
                        drv_can->ext_can_filters[drv_can->ext_filter_num].filter_id     = filter->items[i].id;
                        drv_can->ext_can_filters[drv_can->ext_filter_num].filter_mask   = filter->items[i].mask;
                        drv_can->ext_filter_num++;
                        RT_ASSERT(drv_can->ext_filter_num <= CAN_EXT_FILTER_NUM_MAX);
                    }
                    else
                    {
                        drv_can->std_can_filters[drv_can->std_filter_num].filter_type   = MCAN_FILTER_TYPE_CLASSIC_FILTER;
                        drv_can->std_can_filters[drv_can->std_filter_num].filter_config = MCAN_FILTER_ELEM_CFG_STORE_IN_RX_FIFO0_IF_MATCH;
                        drv_can->std_can_filters[drv_can->std_filter_num].can_id_type   = MCAN_CAN_ID_TYPE_STANDARD;
                        drv_can->std_can_filters[drv_can->std_filter_num].filter_id     = filter->items[i].id;
                        drv_can->std_can_filters[drv_can->std_filter_num].filter_mask   = filter->items[i].mask;
                        drv_can->std_filter_num++;
                        RT_ASSERT(drv_can->std_filter_num <= CAN_STD_FILTER_NUM_MAX);

                    }
                    if (filter->items[i].rtr != 0)
                    {
                        if (drv_can->ext_filter_num)
                        {
                            drv_can->can_config.all_filters_config.global_filter_config.reject_remote_ext_frame = false;
                        }
                        else
                        {
                            drv_can->can_config.all_filters_config.global_filter_config.reject_remote_ext_frame = true;
                        }
                        if (drv_can->std_filter_num)
                        {
                            drv_can->can_config.all_filters_config.global_filter_config.reject_remote_std_frame = false;
                        }
                        else
                        {
                            drv_can->can_config.all_filters_config.global_filter_config.reject_remote_std_frame = true;
                        }
                    }
                }

                if (filter->actived != 0U)
                {
                    drv_can->can_config.all_filters_config.global_filter_config.accept_non_matching_std_frame_option  = MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_REJECT;
                    drv_can->can_config.all_filters_config.global_filter_config.accept_non_matching_ext_frame_option  = MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_REJECT;
                }
                else
                {
                    drv_can->can_config.all_filters_config.global_filter_config.accept_non_matching_std_frame_option  = MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO0;
                    drv_can->can_config.all_filters_config.global_filter_config.accept_non_matching_ext_frame_option  = MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO0;
                }
            }
            else
            {
                drv_can->can_config.all_filters_config.global_filter_config.reject_remote_ext_frame                   = false;
                drv_can->can_config.all_filters_config.global_filter_config.reject_remote_std_frame                   = false;
                drv_can->can_config.all_filters_config.global_filter_config.accept_non_matching_std_frame_option      = MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO0;
                drv_can->can_config.all_filters_config.global_filter_config.accept_non_matching_ext_frame_option      = MCAN_ACCEPT_NON_MATCHING_FRAME_OPTION_IN_RXFIFO0;
                drv_can->can_config.all_filters_config.ext_id_mask                                                    = 0x1FFFFFFFUL;
                drv_can->can_config.all_filters_config.std_id_filter_list.filter_elem_list                            = &k_default_std_id_filter;
                drv_can->can_config.all_filters_config.std_id_filter_list.mcan_filter_elem_count                      = 1;
                drv_can->can_config.all_filters_config.ext_id_filter_list.filter_elem_list                            = &k_default_ext_id_filter;
                drv_can->can_config.all_filters_config.ext_id_filter_list.mcan_filter_elem_count                      = 1;
            }
            err = hpm_mcan_configure(can, &drv_can->can_dev.config);
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
            err = hpm_mcan_configure(can, &drv_can->can_dev.config);
        }

        break;
    case RT_CAN_CMD_SET_BAUD:
        arg_val = (uint32_t) arg;
        if (arg_val != drv_can->can_dev.config.baud_rate)
        {
            drv_can->can_dev.config.baud_rate = arg_val;
        }
        err = hpm_mcan_configure(can, &drv_can->can_dev.config);
        break;
#ifdef RT_CAN_USING_CANFD
    case RT_CAN_CMD_SET_CANFD:
        arg_val = (uint32_t) arg;
        if (arg_val != drv_can->can_dev.config.enable_canfd)
        {
            drv_can->can_dev.config.enable_canfd = arg_val;
            err = hpm_mcan_configure(can, &drv_can->can_dev.config);
        }
        break;
    case RT_CAN_CMD_SET_BAUD_FD:
        arg_val = (uint32_t) arg;
        if (arg_val != drv_can->can_dev.config.baud_rate_fd)
        {
            drv_can->can_dev.config.baud_rate_fd = arg_val;
            err = hpm_mcan_configure(can, &drv_can->can_dev.config);
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
            err = hpm_mcan_configure(can, &drv_can->can_dev.config);
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
            err = hpm_mcan_configure(can, &drv_can->can_dev.config);
        }
        break;
    case RT_CAN_CMD_GET_STATUS:
        mcan_error_count_t err_cnt;
        mcan_get_error_counter(drv_can->can_base, &err_cnt);
        drv_can->can_dev.status.rcverrcnt = err_cnt.receive_error_count;
        drv_can->can_dev.status.snderrcnt = err_cnt.transmit_error_count;
        drv_can->can_dev.status.lasterrtype = mcan_get_last_error_code(drv_can->can_base);
        temp = mcan_get_interrupt_flags(drv_can->can_base);
        drv_can->can_dev.status.errcode = 0;
        if ((temp & MCAN_INT_WARNING_STATUS) != 0U)
        {
            drv_can->can_dev.status.errcode |= ERRWARNING;
        }
        if ((temp & MCAN_INT_ERROR_PASSIVE) != 0U)
        {
            drv_can->can_dev.status.errcode |= ERRPASSIVE;
        }
        if (mcan_is_in_busoff_state(drv_can->can_base))
        {
            drv_can->can_dev.status.errcode |= BUSOFF;
        }
        rt_memcpy(arg, &drv_can->can_dev.status, sizeof(drv_can->can_dev.status));
        break;
    }
}

static int hpm_mcan_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno)
{
    RT_ASSERT(can);

    hpm_can_t *drv_can = (hpm_can_t*) can->parent.user_data;
    RT_ASSERT(drv_can);

    struct rt_can_msg *can_msg = (struct rt_can_msg *) buf;

    mcan_tx_frame_t tx_frame = {0};
    memset(&tx_frame, 0, sizeof(tx_frame));
    if (can_msg->ide == RT_CAN_STDID)
    {
        tx_frame.use_ext_id = 0;
        tx_frame.std_id = can_msg->id;
    }
    else
    {
        tx_frame.use_ext_id = 1;
        tx_frame.ext_id = can_msg->id;
    }
    if (can_msg->rtr == RT_CAN_DTR)
    {
        tx_frame.rtr = false;
    }
    else
    {
        tx_frame.rtr = true;
    }

 #ifdef RT_CAN_USING_CANFD
    if (can_msg->fd_frame != 0)
    {
        tx_frame.canfd_frame    = 1;
        tx_frame.bitrate_switch = 1;
        RT_ASSERT(can_msg->len <= 15);
    }
    else
 #endif
    {
        RT_ASSERT(can_msg->len <= 8);
    }

    uint32_t msg_len = mcan_get_message_size_from_dlc(can_msg->len);
    for (uint32_t i = 0; i < msg_len; i++)
    {
        tx_frame.data_8[i] = can_msg->data[i];
    }
    tx_frame.dlc = can_msg->len;

    uint32_t delay_cnt = 0;
    while (mcan_is_txfifo_full(drv_can->can_base))
    {
        rt_thread_mdelay(1);
        delay_cnt++;
        if (delay_cnt >= CAN_SEND_WAIT_MS_MAX)
        {
            return -RT_ETIMEOUT;
        }
    }
    hpm_stat_t status = mcan_transmit_via_txbuf_nonblocking(drv_can->can_base, 0, &tx_frame);
    if (status != status_success)
    {
        return -RT_EFULL;
    }

    return RT_EOK;
}

static int hpm_mcan_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno)
{
    RT_ASSERT(can);

    hpm_can_t *drv_can = (hpm_can_t*) can->parent.user_data;
    RT_ASSERT(drv_can);

    rt_can_msg_t can_msg = (rt_can_msg_t)buf;
    mcan_rx_message_t rx_buf;
    hpm_stat_t status = mcan_read_rxfifo(drv_can->can_base, 0, &rx_buf);
    if (status == status_success)
    {
        if (rx_buf.use_ext_id)
        {
            can_msg->ide = RT_CAN_EXTID;
            can_msg->id = rx_buf.ext_id;
        }
        else
        {
            can_msg->ide = RT_CAN_STDID;
            can_msg->id = rx_buf.std_id;
        }


        if (rx_buf.rtr != 0) {
            can_msg->rtr = RT_CAN_RTR;
        }
        else {
            can_msg->rtr = RT_CAN_DTR;
        }

        can_msg->len = rx_buf.dlc;
        uint32_t msg_len = mcan_get_message_size_from_dlc(can_msg->len);
        for(uint32_t i = 0; i < msg_len; i++) {
            can_msg->data[i] = rx_buf.data_8[i];
        }

    }
    else
    {
        return -RT_EEMPTY;
    }

    return RT_EOK;
}

int rt_hw_mcan_init(void)
{
    struct can_configure config = CANDEFAULTCONFIG;
    config.privmode = RT_CAN_MODE_NOPRIV;
    config.sndboxnumber = CAN_SENDBOX_NUM;
    config.ticks = 50;

    for (uint32_t i = 0; i < ARRAY_SIZE(hpm_cans); i++)
    {
        hpm_cans[i]->can_dev.config = config;
        hpm_cans[i]->ext_filter_num = 0;
        hpm_cans[i]->std_filter_num = 0;
        mcan_get_default_config(hpm_cans[i]->can_base, &hpm_cans[i]->can_config);
        rt_hw_can_register(&hpm_cans[i]->can_dev, hpm_cans[i]->name, &hpm_can_ops, hpm_cans[i]);
    }
    return RT_EOK;
}

INIT_BOARD_EXPORT(rt_hw_mcan_init);

#endif

