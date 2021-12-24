/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-06-19     Sherman    the first version
 */

#include <string.h>
#include <stdlib.h>

#define DBG_TAG    "example"
#define DBG_LVL    DBG_LOG
#include <rtdbg.h>
#include <rtlink_dev.h>

enum
{
    NONE_TEST = 0,
    SHORT_FRAME_TEST,
    LONG_FRAME_TEST
};
static rt_uint8_t speed_test_type = NONE_TEST;

static struct rt_link_device rtlink_dev = {0};
#define  RTLINK01       "rtlink01"
#define TEST_CONTEXT    "This message is sent by RT-Link"
rt_uint8_t test_buff[1024] = {0};

static rt_err_t rtlink_dev_rx_ind(rt_device_t dev, rt_size_t size)
{
    RT_ASSERT(dev != RT_NULL);
    LOG_I("rx_ind: dev name %s, rx size %d", dev->parent.name, size);
    return RT_EOK;
}

static rt_err_t rtlink_dev_tx_done(rt_device_t dev, void *buffer)
{
    RT_ASSERT(dev != RT_NULL);
    struct rt_link_device *rtlink_dev = (struct rt_link_device *)dev;
    LOG_I("tx_done: dev name %s, buffer 0x%p errno %d", dev->parent.name, buffer, rtlink_dev->service.err);
    rt_free(buffer);
    return RT_EOK;
}

#ifdef RT_USING_POSIX_DEVIO
#include <dfs_posix.h>
#include <poll.h>
#include <sys/select.h>

#define RTLINK01_PATH "/dev/rtlink01"
int fd  = -1;

static void rtlink_fopen(int argc, char *argv[])
{
    fd = open(RTLINK01_PATH, O_RDWR | O_NONBLOCK);

    if (fd < 0)
    {
        LOG_E("open rt_link failed!");
    }
}
MSH_CMD_EXPORT(rtlink_fopen, rtlink posix interface example);

static void rtlink_fclose(int argc, char *argv[])
{
    LOG_D("colse %d", fd);
    close(fd);
    fd = -1;
}
MSH_CMD_EXPORT(rtlink_fclose, rtlink posix interface example);

static void rtlink_fread(int argc, char *argv[])
{
    int read_len;
    read_len = read(fd, test_buff, sizeof(test_buff));
    LOG_D("read len %d", read_len);
    LOG_HEX("read", 8, test_buff, 32);
}
MSH_CMD_EXPORT(rtlink_fread, rtlink posix interface example);

static void rtlink_fwrite(int argc, char *argv[])
{
    char *data = RT_NULL;
    rt_size_t length = 0;
    rt_uint16_t count = 0;
    rt_size_t ret = 0;

    if (argc == 1)
    {
        data = rt_malloc(sizeof(TEST_CONTEXT));
        if (data)
        {
            length = sizeof(TEST_CONTEXT) - 1;
            rt_memcpy(data, TEST_CONTEXT, sizeof(TEST_CONTEXT) - 1);
            ret = write(fd, data, length);
        }
        LOG_I("write data(0x%p) result: %d.", data, ret);
    }
    else if (argc >= 3)
    {
        if (strcmp(argv[1], "-l") == 0)
        {
            data = rt_malloc(atoi((const char *)argv[2]));
            if (data)
            {
                for (count = 0; count < atoi((const char *)argv[2]); count++)
                {
                    data[count] = (count % 93 + 33);
                }
                length = atoi((const char *)argv[2]);
                ret = write(fd, data, length);
            }
            LOG_I("write data(0x%p) result: %d.", data, ret);
        }
        else
        {
            LOG_E("Invalid parameter.");
        }
    }
}
MSH_CMD_EXPORT(rtlink_fwrite, rtlink posix interface example);

#define RTLINK02         "rtlink02"
#define RTLINK02_PATH    "/dev/rtlink02"
static struct rt_link_device rtlink_fd = {0};
rt_uint8_t fd_buff[1024] = {0};

static void listen_thread(void *param)
{
    int fd  = open(RTLINK02_PATH, O_RDWR | O_NONBLOCK);
    if (fd < 0)
    {
        LOG_E("open (%s) failed", RTLINK02);
        return;
    }
    while (1)
    {
        rt_uint8_t *write_buf = RT_NULL;
        int write_len = 0;
        fd_set readfds, writefds;
        FD_ZERO(&readfds);
        FD_ZERO(&writefds);
        FD_SET(fd, &readfds);
        FD_SET(fd, &writefds);

        int ret = select(fd + 1, &readfds, &writefds, RT_NULL, RT_NULL);
        LOG_D("select ret(%d), read (%d), write (%d)", ret, readfds, writefds);
        if (FD_ISSET(fd, &readfds))
        {
            LOG_I("POLLIN");
            int read_len = read(fd, fd_buff, sizeof(test_buff));
            LOG_D("read len %d", read_len);
            LOG_HEX("read", 8, test_buff, 32);
        }

        if (FD_ISSET(fd, &writefds))
        {
            LOG_I("POLLOUT");
            write_buf = rt_malloc(1024);
            if (write_buf)
            {
                write_len = write(fd, write_buf, 1024);
                LOG_D("write %d", write_len);
            }
        }

        rt_thread_delay(500);
    }
    LOG_I("fd (%s) listen thread exit", RTLINK02);
}

static void rtlink_fselect()
{
    /* step1: register rtlink to to the device framework */
    rt_link_dev_register(&rtlink_fd, RTLINK02,
                         RT_DEVICE_FLAG_RDWR |
                         RT_DEVICE_FLAG_REMOVABLE |
                         RT_DEVICE_FLAG_STANDALONE,
                         RT_NULL);

    /* step2: Initialize the rlink device as the default configuration,  */
    rt_device_t device = rt_device_find(RTLINK02);
    if (device == RT_NULL)
    {
        LOG_E("device not find!");
        return ;
    }
    rt_device_init(device);

    /* step3: config rtlink device rx/tx callback, channel, send timeout */
    rt_device_set_rx_indicate(device, rtlink_dev_rx_ind);
    rt_device_set_tx_complete(device, rtlink_dev_tx_done);
    struct rt_link_service service;
    service.service = RT_LINK_SERVICE_MNGT;
    service.timeout_tx = RT_WAITING_NO;
    rt_device_control(device, RT_DEVICE_CTRL_CONFIG, &service);

    rt_thread_t tid = rt_thread_create(RTLINK02, listen_thread, RT_NULL, 1024, 21, 20);
    if (tid)
    {
        rt_thread_startup(tid);
    }
}
MSH_CMD_EXPORT(rtlink_fselect, rtlink posix interface example);
#endif  /* RT_USING_POSIX_DEVIO */

static void rtlink_dread(void)
{
    rt_size_t read_len = 0;
    rt_device_t dev = rt_device_find(RTLINK01);
    if (dev == RT_NULL)
    {
        LOG_E("dev %s not find ", RTLINK01);
        return;
    }

    read_len = rt_device_read(dev, 0, test_buff, sizeof(test_buff));

    LOG_D("read len %d", read_len);
    LOG_HEX("read", 8, test_buff, 32);
}
MSH_CMD_EXPORT(rtlink_dread, rtlink device interface example);

void rt_link_speed_test(void *paremeter)
{
    int ret;
    rt_uint8_t *send_buf, *data;
    rt_size_t bufflen = 0;
    rt_size_t sentlen = 0;
    rt_size_t count = 0;
    rt_tick_t tick1, tick2;
    rt_size_t total = 0;
    rt_uint32_t integer, decimal;
    rt_device_t dev = rt_device_find(RTLINK01);
    if (dev == RT_NULL)
    {
        LOG_E("dev %s not find!", RTLINK01);
        return ;
    }

    if (speed_test_type == SHORT_FRAME_TEST)
    {
        bufflen = 988;
    }
    else
    {
        bufflen = 3036;
    }

    send_buf = rt_malloc(bufflen);
    if (send_buf != RT_NULL)
    {
        data = send_buf;
        for (count = 0; count < bufflen; count++)
        {
            *data++ = (count % 93 + 33);
        }
    }
    else
    {
        rt_kprintf("speed of send buffer malloc failed.");
        return;
    }

    tick1 = rt_tick_get();
    while (speed_test_type)
    {
        ret = rt_device_write(dev, 0, send_buf, bufflen);

        if (ret == RT_EOK)
        {
            sentlen += bufflen;
        }

        tick2 = rt_tick_get();
        if (tick2 - tick1 >= RT_TICK_PER_SECOND)
        {
            total = sentlen * RT_TICK_PER_SECOND / 125 / (tick2 - tick1);
            integer = total / 1000;
            decimal = total % 1000;
            LOG_I("%d.%03d0 Mbps!", integer, decimal);
            sentlen = 0;
            tick1 = tick2;
        }
    }
    rt_free(send_buf);
    LOG_W("speed test end, type %d", speed_test_type);
}

void create_thead_to_test_speed(rt_uint8_t mutil_num)
{
    rt_uint8_t i = 0;

    LOG_D("Speed test type [%02d], mutil [%02d]", speed_test_type, mutil_num);
    for (i = 0; i < mutil_num; i++)
    {
        rt_thread_t tid;
        char tid_name[RT_NAME_MAX + 1] = {0};

        rt_snprintf(tid_name, sizeof(tid_name), "lny_s%03d", i + 1);
        tid = rt_thread_create(tid_name, rt_link_speed_test, RT_NULL, 1024, 20, 10);
        rt_thread_startup(tid);
        LOG_I("Speed test thread[%s] startup", tid_name);
    }
}

static void rtlink_dwrite(int argc, char *argv[])
{
    char *data = RT_NULL;
    rt_size_t length = 0;
    rt_uint16_t count = 0;
    rt_size_t ret = RT_ERROR;

    rt_device_t dev = rt_device_find(RTLINK01);
    if (dev == RT_NULL)
    {
        LOG_E("device not find!");
        return ;
    }

    if (argc == 1)
    {
        data = rt_malloc(sizeof(TEST_CONTEXT));
        length = sizeof(TEST_CONTEXT) - 1;
        rt_memcpy(data, TEST_CONTEXT, sizeof(TEST_CONTEXT) - 1);

        ret = rt_device_write(dev, 0, data, length);
        LOG_I("write data(0x%p) result: %d.", data, ret);
    }
    else if (argc >= 3)
    {
        if (strcmp(argv[1], "-l") == 0)
        {
            data = rt_malloc(atoi((const char *)argv[2]));
            for (count = 0; count < atoi((const char *)argv[2]); count++)
            {
                data[count] = (count % 93 + 33);
            }
            length = atoi((const char *)argv[2]);
            ret = rt_device_write(dev, 0, data, length);
            LOG_I("write data(0x%p) result: %d.", data, ret);
        }
        else
        {
            LOG_E("Invalid parameter.");
        }
    }
}
MSH_CMD_EXPORT(rtlink_dwrite, rtlink device interface example);

static void rtlink_dinit(void)
{
    /* step1: register rtlink to to the device framework */
    rt_link_dev_register(&rtlink_dev, RTLINK01,
                         RT_DEVICE_FLAG_RDWR |
                         RT_DEVICE_FLAG_REMOVABLE |
                         RT_DEVICE_FLAG_STANDALONE,
                         RT_NULL);

    /* step2: Initialize the rlink device as the default configuration,  */
    rt_device_t device = rt_device_find(RTLINK01);
    if (device == RT_NULL)
    {
        LOG_E("device not find!");
        return ;
    }
    rt_device_init(device);

    /* step3: config rtlink device rx/tx callback, channel, send timeout */
    rt_device_set_rx_indicate(device, rtlink_dev_rx_ind);
    rt_device_set_tx_complete(device, rtlink_dev_tx_done);
    struct rt_link_service service;
    service.service = RT_LINK_SERVICE_SOCKET;
    service.timeout_tx = RT_WAITING_FOREVER;
    service.flag = RT_LINK_FLAG_ACK | RT_LINK_FLAG_CRC;
    rt_device_control(device, RT_DEVICE_CTRL_CONFIG, &service);
}
MSH_CMD_EXPORT(rtlink_dinit, rtlink device interface example);

static void rtlink_dopen()
{
    /* step4: open rtlink device, attach the service channel */
    rt_device_t device = rt_device_find(RTLINK01);
    if (device == RT_NULL)
    {
        LOG_E("device not find!");
        return ;
    }
    rt_err_t ret = rt_device_open(device, RT_DEVICE_OFLAG_RDWR);
    LOG_I("dev open ret %d", ret);
}
MSH_CMD_EXPORT(rtlink_dopen, rtlink device interface example);
