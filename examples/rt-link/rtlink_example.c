
/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-15     Sherman      the first version
 */

#include <stdlib.h>
#include <string.h>
#include <rtthread.h>
#include <rtlink.h>

#define DBG_ENABLE
#define DBG_TAG "rtlink_exam"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define TEST_CONTEXT    "This message is sent by RT-Link"

enum
{
    NONE_TEST = 0,
    SHORT_FRAME_TEST,
    LONG_FRAME_TEST
};

void rt_link_speed_test(void *paremeter);
static rt_uint8_t speed_test_type = NONE_TEST;

rt_err_t rt_link_receive_example_callback(void *data, rt_size_t length)
{
    LOG_I("recv data %d",length);
    LOG_HEX("example",8,data,length);
    rt_free(data);
    return RT_EOK;
}

void create_thead_to_test_speed(rt_uint8_t mutil_num)
{
    rt_uint8_t i = 0;

    LOG_D("Speed test type [%02d], mutil [%02d]", speed_test_type, mutil_num);
    for(i = 0; i< mutil_num; i++)
    {
        rt_thread_t tid;
        char tid_name[RT_NAME_MAX + 1] = {0};

        rt_snprintf(tid_name, sizeof(tid_name), "lny_s%03d", i + 1);
        tid = rt_thread_create(tid_name, rt_link_speed_test, RT_NULL, 1024, 20, 10);
        rt_thread_startup(tid);
        LOG_I("Speed test thread[%s] startup", tid_name);
    }
}

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

    if(speed_test_type == SHORT_FRAME_TEST)
    {
        bufflen = 2044;
    }
    else
    {
        bufflen = 6132;
    }

    send_buf = rt_malloc(bufflen);
    if(send_buf != RT_NULL)
    {
        data = send_buf;
        for(count = 0;count < bufflen; count++)
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
        ret = rt_link_send(RT_LINK_SERVICE_RTLINK, send_buf, bufflen);
        if(ret > 0)
        {
            sentlen += ret;
        }

        tick2 = rt_tick_get();
        if (tick2 - tick1 >= RT_TICK_PER_SECOND)//* 10
        {
            total = sentlen * RT_TICK_PER_SECOND / 125 / (tick2 - tick1);
            integer = total/1000;
            decimal = total%1000;
            LOG_I("%d.%03d0 Mbps!", integer, decimal);
            sentlen = 0;
            tick1 = tick2;
        }
    }
    rt_free(send_buf);
    LOG_W("speed test end, type %d",speed_test_type);
}

int rt_link_example_send(int argc, char **argv)
{
    char *receive = RT_NULL;
    rt_size_t length = 0;
    rt_uint16_t count = 0;

    if(argc == 1)
    {
        receive = rt_malloc(sizeof(TEST_CONTEXT));
        rt_memcpy(receive, TEST_CONTEXT, sizeof(TEST_CONTEXT) - 1);
        length = rt_link_send(RT_LINK_SERVICE_RTLINK, receive, sizeof(TEST_CONTEXT) - 1);
        LOG_I("send data length: %d.", length);
        rt_free(receive);
    }
        else if(argc >= 3)
    {
        if(strcmp(argv[1], "-l") == 0)
        {
            receive = rt_malloc(atoi((const char *)argv[2]));
            for(count = 0;count < atoi((const char *)argv[2]); count++)
            {
                *receive++ = (count % 93 + 33);
            }
            length = rt_link_send(RT_LINK_SERVICE_RTLINK, receive - atoi((const char *)argv[2]), atoi((const char *)argv[2]));
            rt_free(receive - atoi((const char *)argv[2]));

            LOG_I("send data length: %d.", length);
        }
        else if(strcmp(argv[1], "-s") == 0)
        {
            if(speed_test_type == NONE_TEST)
            {
                rt_uint8_t mutil_num = 1;
                if(argc > 3)
                {
                    mutil_num = atoi((const char *)argv[3]);
                }

                if(strncmp(argv[2], "-s", rt_strlen(argv[2])) == 0)
                {
                    speed_test_type = SHORT_FRAME_TEST;
                }
                else if(strncmp(argv[2], "-l", rt_strlen(argv[2])) == 0)
                {
                    speed_test_type = LONG_FRAME_TEST;
                }
                create_thead_to_test_speed(mutil_num);
            }
            else
            {
                speed_test_type = NONE_TEST;
                LOG_I("set NONE_TEST");
            }
        }
        else
        {
            LOG_E("Invalid parameter.");
        }
    }
    return 0;
}
MSH_CMD_EXPORT(rt_link_example_send, rt link layer send test);

int rt_link_example_init(void)
{

    rt_link_service_attach(RT_LINK_SERVICE_RTLINK, rt_link_receive_example_callback);
    return RT_EOK;
}
MSH_CMD_EXPORT(rt_link_example_init, rt link layer example init);
