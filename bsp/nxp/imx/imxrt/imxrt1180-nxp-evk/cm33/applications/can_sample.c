/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2024-08-13     nxp-ran    CAN3 loopback and two-node sample for IMXRT1180 CM33
 *
 * Usage:
 *   Loopback test (no external CAN hardware required):
 *     can_loopback can3
 *
 *   Two-node transmit test (requires CAN transceiver and second node):
 *     can_send can3 0x123 1122334455667788
 *
 *   Two-node receive test (run on the receiving node):
 *     can_recv can3
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include <stdlib.h>

#ifdef BSP_USING_CAN

#define CAN_SAMPLE_BAUD_RATE CAN1MBaud  /* 1 Mbit/s */

/* ------------------------------------------------------------------ */
/* Helper: open a CAN device in the given mode, enable interrupts      */
/*                                                                      */
/* The mode and baud rate must be written into the device's config     */
/* BEFORE the first open, because rt_can_init() (called at open time)  */
/* passes can->config directly to the hardware configure callback.     */
/* ------------------------------------------------------------------ */
static rt_device_t can_open(const char *devname, rt_uint32_t mode)
{
    struct rt_can_device *can_dev;
    rt_device_t dev = rt_device_find(devname);
    if (!dev)
    {
        rt_kprintf("[can_sample] device '%s' not found\n", devname);
        return RT_NULL;
    }

    /* set mode and baud rate before open so rt_can_init() picks them up */
    can_dev = (struct rt_can_device *)dev;
    can_dev->config.baud_rate = CAN_SAMPLE_BAUD_RATE;
    can_dev->config.mode = (rt_uint32_t)mode;

    rt_device_open(dev, RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);
    rt_device_control(dev, RT_DEVICE_CTRL_SET_INT, (void *)RT_DEVICE_FLAG_INT_RX);
    rt_device_control(dev, RT_DEVICE_CTRL_SET_INT, (void *)RT_DEVICE_FLAG_INT_TX);

    return dev;
}

/* ------------------------------------------------------------------ */
/* Loopback test: send one frame and receive it back on the same node  */
/* ------------------------------------------------------------------ */
static void can_loopback(int argc, char *argv[])
{
    const char *devname = (argc > 1) ? argv[1] : "can3";
    rt_device_t dev;
    struct rt_can_msg tx_msg, rx_msg;
    int i;

    rt_kprintf("[can_sample] loopback test on '%s'\n", devname);

    dev = can_open(devname, RT_CAN_MODE_LOOPBACK);
    if (!dev)
        return;

    /* build TX frame */
    rt_memset(&tx_msg, 0, sizeof(tx_msg));
    tx_msg.id = 0x123;
    tx_msg.ide = RT_CAN_STDID;
    tx_msg.rtr = RT_CAN_DTR;
    tx_msg.len = 8;
    for (i = 0; i < 8; i++)
        tx_msg.data[i] = (rt_uint8_t)(0x11 * (i + 1));

    /* send */
    if (rt_device_write(dev, 0, &tx_msg, sizeof(tx_msg)) != sizeof(tx_msg))
    {
        rt_kprintf("[can_sample] send failed\n");
        rt_device_close(dev);
        return;
    }
    rt_kprintf("[can_sample] TX id=0x%03X data:", tx_msg.id);
    for (i = 0; i < tx_msg.len; i++)
        rt_kprintf(" %02X", tx_msg.data[i]);
    rt_kprintf("\n");

    /* wait for loopback reception (polling with timeout) */
    rt_uint32_t tick_start = rt_tick_get();
    while (rt_tick_get() - tick_start < RT_TICK_PER_SECOND)
    {
        if (rt_device_read(dev, 0, &rx_msg, sizeof(rx_msg)) == sizeof(rx_msg))
        {
            rt_kprintf("[can_sample] RX id=0x%03X data:", rx_msg.id);
            for (i = 0; i < rx_msg.len; i++)
                rt_kprintf(" %02X", rx_msg.data[i]);
            rt_kprintf("\n");

            if (rx_msg.id == tx_msg.id &&
                rt_memcmp(rx_msg.data, tx_msg.data, tx_msg.len) == 0)
            {
                rt_kprintf("[can_sample] loopback PASS\n");
            }
            else
            {
                rt_kprintf("[can_sample] loopback FAIL: data mismatch\n");
            }
            rt_device_close(dev);
            return;
        }
        rt_thread_mdelay(1);
    }

    rt_kprintf("[can_sample] loopback FAIL: receive timeout\n");
    rt_device_close(dev);
}
MSH_CMD_EXPORT(can_loopback, CAN loopback test : can_loopback[devname]);

/* ------------------------------------------------------------------ */
/* Two-node TX: send one frame on the normal CAN bus                   */
/* Usage: can_send can3 0x123 1122334455667788                         */
/* ------------------------------------------------------------------ */
static void can_send(int argc, char *argv[])
{
    const char *devname = (argc > 1) ? argv[1] : "can3";
    rt_uint32_t id = (argc > 2) ? (rt_uint32_t)strtoul(argv[2], RT_NULL, 16) : 0x123U;
    const char *hexdata = (argc > 3) ? argv[3] : "0102030405060708";
    struct rt_can_msg msg;
    rt_device_t dev;
    int i, len;
    char byte_str[3] = { 0 };

    rt_kprintf("[can_sample] send on '%s' id=0x%03X data=%s\n", devname, id, hexdata);

    dev = can_open(devname, RT_CAN_MODE_NORMAL);
    if (!dev)
        return;

    rt_memset(&msg, 0, sizeof(msg));
    msg.id = id;
    msg.ide = RT_CAN_STDID;
    msg.rtr = RT_CAN_DTR;

    len = (int)(rt_strlen(hexdata) / 2);
    if (len > 8)
        len = 8;
    msg.len = (rt_uint32_t)len;
    for (i = 0; i < len; i++)
    {
        byte_str[0] = hexdata[i * 2];
        byte_str[1] = hexdata[i * 2 + 1];
        msg.data[i] = (rt_uint8_t)strtoul(byte_str, RT_NULL, 16);
    }

    if (rt_device_write(dev, 0, &msg, sizeof(msg)) != sizeof(msg))
        rt_kprintf("[can_sample] send failed\n");
    else
        rt_kprintf("[can_sample] frame sent OK\n");

    rt_device_close(dev);
}
MSH_CMD_EXPORT(can_send, CAN two - node TX : can_send[dev][id_hex][data_hex]);

/* ------------------------------------------------------------------ */
/* Two-node RX: receive and print frames until 'q' or timeout 10 s    */
/* Usage: can_recv can3                                                */
/* ------------------------------------------------------------------ */
static void can_recv(int argc, char *argv[])
{
    const char *devname = (argc > 1) ? argv[1] : "can3";
    rt_device_t dev;
    struct rt_can_msg msg;
    int i;
    rt_uint32_t tick_start;

    rt_kprintf("[can_sample] receive on '%s', waiting up to 10s ...\n", devname);

    dev = can_open(devname, RT_CAN_MODE_NORMAL);
    if (!dev)
        return;

    tick_start = rt_tick_get();
    while (rt_tick_get() - tick_start < 10 * RT_TICK_PER_SECOND)
    {
        if (rt_device_read(dev, 0, &msg, sizeof(msg)) == sizeof(msg))
        {
            rt_kprintf("[can_sample] RX id=0x%03X ide=%s rtr=%s len=%d data:",
                       msg.id,
                       (msg.ide == RT_CAN_STDID) ? "STD" : "EXT",
                       (msg.rtr == RT_CAN_DTR) ? "DATA" : "REMOTE",
                       msg.len);
            for (i = 0; i < (int)msg.len; i++)
                rt_kprintf(" %02X", msg.data[i]);
            rt_kprintf("\n");
            /* reset timeout after each received frame */
            tick_start = rt_tick_get();
        }
        rt_thread_mdelay(1);
    }

    rt_kprintf("[can_sample] receive stopped\n");
    rt_device_close(dev);
}
MSH_CMD_EXPORT(can_recv, CAN two - node RX : can_recv[devname]);

#endif /* BSP_USING_CAN */
