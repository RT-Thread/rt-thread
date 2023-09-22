/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date        Author    Email                    Notes
 * 2022-04-16  Kevin.Liu kevin.liu.mchp@gmail.com First Release
 */

#include <rtthread.h>

#include "atmel_start.h"
#include "driver_init.h"
#include "utils.h"

#include "can_demo.h"

#ifdef SAM_CAN_EXAMPLE

#if defined(SOC_SAMC21) || defined(SOC_SAME54)
#define CAN_HARDWARE            (void *)CAN1
#elif defined(SOC_SAME70)
#define CAN_HARDWARE            (void *)MCAN1
#else
#error "CAN undefined SOC Platform"
#endif

static volatile enum can_async_interrupt_type can_errors;
static rt_sem_t   can_txdone;
static rt_sem_t   can_rxdone;
static rt_uint8_t can_stack[ 512 ];
static struct rt_thread can_thread;

/**
 * @brief    Callback function and should be invoked after call can_async_write.
 *
 * @note
 *
 * @param    descr is CAN device description.
 *
 * @return   None.
 */

static void can_tx_callback(struct can_async_descriptor *const descr)
{
    rt_err_t result;

    rt_interrupt_enter();
    result = rt_sem_release(can_txdone);
    if (RT_EOK != result)
    {
#ifndef RT_USING_FINSH
        rt_kprintf("rt_sem_release failed in %s %d\r\n",__FUNCTION__, __LINE__);
#endif
    }
    rt_interrupt_leave();
}

/**
 * @brief    Callback function and should be invoked after remote device send.
 *
 * @note     This callback function will be called in CAN interrupt function
 *
 * @param    descr is CAN device description.
 *
 * @return   None.
 */

static void can_rx_callback(struct can_async_descriptor *const descr)
{
    rt_err_t result;

    rt_interrupt_enter();
    result = rt_sem_release(can_rxdone);
    if (RT_EOK != result)
    {
#ifndef RT_USING_FINSH
        rt_kprintf("rt_sem_release failed in %s %d\r\n",__FUNCTION__, __LINE__);
#endif
    }
    rt_interrupt_leave();
}

/**
 * @brief    Callback function and should be invoked after CAN device IRQ handler detects errors happened.
 *
 * @note     This callback function will be called in CAN interrupt function
 *
 * @param    descr is CAN device description.
 *
 * @return   None.
 */

static void can_err_callback(struct can_async_descriptor *const descr,
                             enum can_async_interrupt_type type)
{
    rt_err_t result;

    if (type == CAN_IRQ_EW)
    {
      /* Error warning, Error counter has reached the error warning limit of 96,
       * An error count value greater than about 96 indicates a heavily disturbed
       * bus. It may be of advantage to provide means to test for this condition.
       */
    }
    else if (type == CAN_IRQ_EA)
    {
        /* Error Active State, The CAN node normally take part in bus communication
         * and sends an ACTIVE ERROR FLAG when an error has been detected.
         */
    }
    else if (type == CAN_IRQ_EP)
    {
        /* Error Passive State, The Can node goes into error passive state if at least
         * one of its error counters is greater than 127. It still takes part in bus
         * activities, but it sends a passive error frame only, on errors.
         */
    }
    else if (type == CAN_IRQ_BO)
    {
        /* Bus Off State, The CAN node is 'bus off' when the TRANSMIT ERROR COUNT is
         * greater than or equal to 256.
         */

        /* Suspend CAN task and re-initialize CAN module. */
        can_errors = type;
        rt_interrupt_enter();
        result = rt_sem_release(can_rxdone);
        if (RT_EOK != result)
        {
#ifndef RT_USING_FINSH
            rt_kprintf("rt_sem_release failed in %s %d\r\n",__FUNCTION__, __LINE__);
#endif
        }
        rt_interrupt_leave();
    }
    else if (type == CAN_IRQ_DO)
    {
        /* Data Overrun in receive queue. A message was lost because the messages in
         * the queue was not reading and releasing fast enough. There is not enough
         * space for a new message in receive queue.
         */

        /* Suggest to delete CAN task and re-initialize it. */
        can_errors = type;
        rt_interrupt_enter();
        result = rt_sem_release(can_rxdone);
        if (RT_EOK != result)
        {
#ifndef RT_USING_FINSH
            rt_kprintf("rt_sem_release failed in %s %d\r\n",__FUNCTION__, __LINE__);
#endif
        }
        rt_interrupt_leave();
    }
};

/**
 * @brief    Initialize CAN module before task run.
 *
 * @note     This function will set CAN Tx/Rx callback function and filters.
 *
 * @param    None.
 *
 * @return   None.
 */

static inline void can_demo_init(void)
{
    struct can_filter  filter;

    /**
     * CAN_Node0_tx_callback callback should be invoked after call
     * can_async_write, and remote device should receive message with ID=0x45A
     */
    can_async_register_callback(&CAN_0, CAN_ASYNC_TX_CB, (FUNC_PTR)can_tx_callback);

    /**
     * CAN_0_rx_callback callback should be invoked after call
     * can_async_set_filter and remote device send CAN Message with the same
     * content as the filter.
     */
    can_async_register_callback(&CAN_0, CAN_ASYNC_RX_CB, (FUNC_PTR)can_rx_callback);


    /* Should set at least one CAN standard & message filter before enable it. */

    filter.id   = 0x469;
    filter.mask = 0;
    can_async_set_filter(&CAN_0, 0, CAN_FMT_STDID, &filter);

    /* If set second standard message filter, should increase filter index
     * and filter algorithm
     * For example: index should set to 1, otherwise it will replace filter 0.
     * can_async_set_filter(&CAN_0, 1, CAN_FMT_STDID, &filter); */

    filter.id   = 0x10000096;
    filter.mask = 0;
    can_async_set_filter(&CAN_0, 0, CAN_FMT_EXTID, &filter);

    can_async_enable(&CAN_0);
}

/**
 * @brief    CAN task.
 *
 * @note     This task will waiting for CAN RX semaphore and then process input.
 *
 * @param    parameter - task input parameter.
 *
 * @return   None.
 */

static void can_thread_entry(void* parameter)
{
    int32_t  ret;
    rt_err_t result;
    uint8_t  data[64];
    uint32_t count=0;
    struct can_message msg;

    while (1)
    {
#ifndef RT_USING_FINSH
        rt_kprintf("can task run count : %d\r\n",count);
#endif
        count++;

        result = rt_sem_take(can_rxdone, RT_WAITING_FOREVER);
        if (RT_EOK != result)
            continue;

        do
        {
            /* Process the incoming packet. */
            ret = can_async_read(&CAN_0, &msg);
            if (ret == ERR_NONE)
            {
#ifndef RT_USING_FINSH
                rt_kprintf("CAN RX Message is % frame\r\n",
                           msg.type == CAN_TYPE_DATA ? "data" : "remote");
                rt_kprintf("CAN RX Message is % frame\r\n",
                           msg.type == CAN_FMT_STDID ? "Standard" : "Extended");
                rt_kprintf("can RX Message ID: 0x%X length: %d\r\n", msg.id, msg.len);
                rt_kprintf("CAN RX Message content: ");
                for (uint8_t i = 0; i < msg.len; i++)
                    rt_kprintf("0x%02X ", data[i]);
                rt_kprintf("\r\n");
#endif
            }
        } while (ret == ERR_NONE); /* Get all data stored in CAN RX FIFO */

        /* CAN task got CAN error message, handler CAN Error Status */
        if ((can_errors == CAN_IRQ_BO) || (can_errors == CAN_IRQ_DO))
        {
            can_async_init(&CAN_0, CAN_HARDWARE);
        }
    }
}

/**
 * @brief    Call this function will to send a CAN message.
 *
 * @note
 *
 * @param    msg - message to be sent, timeouts - wait timeouts for Tx completion.
 *
 * @return   RT_OK or -RT_ERROR.
 */

rt_err_t can_send_message(struct can_message *msg, rt_uint32_t timeouts)
{
    rt_err_t result;

    if (RT_NULL == msg)
    {
        rt_kprintf("can_send_message input message error\r\n");
        return -RT_ERROR;
    }

    can_async_write(&CAN_0, msg);
    result = rt_sem_take(can_rxdone, timeouts);

    return result;
}

/**
 * @brief    Call this function will create a CAN task.
 *
 * @note     Should create Tx/Rx semaphore before run task.
 *
 * @param    None.
 *
 * @return   RT_OK or -RT_ERROR.
 */

rt_err_t can_demo_run(void)
{
    rt_err_t result;

    can_rxdone = rt_sem_create("can_rx", 0, RT_IPC_FLAG_FIFO);
    if (RT_NULL == can_rxdone)
    {
        rt_kprintf("can_rx semaphore create failed\r\n");
        return (-RT_ERROR);
    }

    can_txdone = rt_sem_create("can_tx", 0, RT_IPC_FLAG_FIFO);
    if (RT_NULL == can_txdone)
    {
        rt_kprintf("can_tx semaphore create failed\r\n");
        return (-RT_ERROR);
    }

    can_demo_init();

    /* initialize CAN thread */
    result = rt_thread_init(&can_thread,
                            "can",
                            can_thread_entry,
                            RT_NULL,
                            (rt_uint8_t*)&can_stack[0],
                            sizeof(can_stack),
                            RT_THREAD_PRIORITY_MAX/3,
                            5);
    if (result == RT_EOK)
    {
        rt_thread_startup(&can_thread);
    }

    return result;
}
#endif

/*@}*/
