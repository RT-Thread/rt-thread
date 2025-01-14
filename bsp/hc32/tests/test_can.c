/*
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-30     CDT          first version
 */

/*
* 功能
*   展示 CAN1、CAN2、CAN3 接收消息和回发消息。
* 代码使用方法
*   在终端执行：can_sample 参数选择：can1 | can2 | can3 以启动CAN收发测试
*
* 默认波特率
*   仲裁段:波特率500K,采样率80%
*   数据段:波特率为4M,采样率80% (仅支持CAN FD的单元)
*
* 接收和发送消息
*  CAN1:
*  仅接收满足以下过滤条件的消息，并发送接收到的消息
*   1）标准帧：match ID:0x100~0x1ff
*   2）扩展帧：match ID:0x12345100~0x123451ff
*   3）固定ID帧: match ID: 0x555
*  测试设备发送满足以上过滤条件的消息后，会在终端打印接收到的ID和消息，并将消息原样发回给测试设备。
*
* 命令行命令
*   1）设置时序： (仅支持CAN FD的单元)
*       注意：使用此项设置前，需修改 MSH 最大参数格式为 20
*           （menuconfig-->RT-Thread Components-->MSH: command shell-->The number of arguments for a shell command）
*       格式：
*           can set_bittiming <count> <rt_can_bit_timing_arbitration> <rt_can_bit_timing_data>
*       示例:
*           MSH >can set_bittiming 1 1 64 16 16 0             (设置can 仲裁段波特率500K)
*           MSH >can set_bittiming 2 1 64 16 16 0 1 16 4 4 16 (设置can 仲裁段波特率500K,数据段波特率2M)
*   2）设置仲裁段波特率：
*       格式：
*           can set_baud <baud>
*       示例：
*           MSH >can set_baud 1000000 （设置can仲裁段波特率1M）
*   3）设置数据段波特率： (仅支持CAN FD的单元)
*       格式：
*           can set_baudfd <baudfd>
*       示例：
*           MSH >can set_baudfd 2000000 （设置can数据段波特率2M）
*   4）发送消息：
*       格式：
*           can send_msg
*       示例：
*           MSH >can send_msg （触发can发送数据）
*/

#include <rtthread.h>
#include "rtdevice.h"
#if defined (HC32F4A0) || defined (HC32F472) || defined (HC32F460)
    #include "drv_can.h"
#elif defined (HC32F448)
    #include "drv_mcan.h"
#endif

#include <stdlib.h>
#include <string.h>

#if defined(BSP_USING_CAN) || defined(BSP_USING_MCAN)

#define MSH_USAGE_CAN_SET_BAUD          "can set_baud <baud>        - set can baud\n"
#define MSH_USAGE_CAN_SET_BAUDFD        "can set_baudfd <baudfd>    - set can baudfd\n"
#define MSH_USAGE_CAN_SET_BITTIMING     "can set_bittiming <count> <rt_can_bit_timing_arbitration> <rt_can_bit_timing_data>  - set can bit timing,\n"
#define MSH_USAGE_CAN_SEND_MSG          "can send_msg \n"

#define MSH_RESULT_STR(result)          ((result == RT_EOK) ? "success" : "failure")

static rt_device_t can_dev = RT_NULL;
static struct rt_semaphore can_rx_sem;
static rt_mutex_t can_mutex = RT_NULL;
static rt_thread_t rx_thread;
static uint32_t can_msg_tx_cnt = 0U;
static uint32_t can_msg_rx_cnt = 0U;

#define CAN_IF_INIT()                   do {                            \
                                            if (can_dev == RT_NULL || can_mutex == RT_NULL) { \
                                                rt_kprintf("failed! please first execute can_sample cmd!\n"); \
                                                return;                 \
                                            }                           \
                                        } while (0)

static rt_err_t can_rx_call(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(&can_rx_sem);
    return RT_EOK;
}

static void _set_default_filter(void)
{
#ifdef RT_CAN_USING_HDR
    struct rt_can_filter_item can_items[3] =
    {
        RT_CAN_FILTER_ITEM_INIT(0x100, RT_CAN_STDID, RT_CAN_DTR, 1, 0x700, RT_NULL, RT_NULL),           /* std,match ID:0x100~0x1ff，过滤表模式为1(0表示标识符列表模式，1表示标识符屏蔽位模式)，hdr = -1(表示不指定过滤表号)，设置默认过滤表，过滤表回调函数和参数均为NULL */
        RT_CAN_FILTER_ITEM_INIT(0x12345100, RT_CAN_EXTID, RT_CAN_DTR, 1, 0xFFFFFF00, RT_NULL, RT_NULL), /* ext,match ID:0x12345100~0x123451ff，hdr = -1 */
        {0x555, RT_CAN_STDID, RT_CAN_DTR, 1, 0x7ff, 7}                                                  /* std,match ID:0x555，hdr= 7，指定设置7号过滤表 */
    };
    struct rt_can_filter_config cfg = {3, 1, can_items}; /* 一共有3个过滤表，1表示初始化过滤表控制块 */
    rt_err_t res;
    res = rt_device_control(can_dev, RT_CAN_CMD_SET_FILTER, &cfg);
    RT_ASSERT(res == RT_EOK);
#endif
}

static void can_rx_thread(void *parameter)
{
    struct rt_can_msg rxmsg = {0};
    rt_size_t  size;

    while (1)
    {
        rt_memset(&rxmsg, 0, sizeof(struct rt_can_msg));
        rt_sem_take(&can_rx_sem, RT_WAITING_FOREVER);
        rt_mutex_take(can_mutex, RT_WAITING_FOREVER);
        /* hdr 值为 - 1，表示直接从 uselist 链表读取数据 */
        rxmsg.hdr_index = -1;
        /* 从 CAN 读取一帧数据 */
        rt_device_read(can_dev, 0, &rxmsg, sizeof(rxmsg));
        /* 打印数据 ID 及内容 */
        rt_kprintf("ID:%x Data:", rxmsg.id);
        for (int i = 0; i < 8; i++)
        {
            rt_kprintf("%2x ", rxmsg.data[i]);
        }
        rt_kprintf("\n");
        /* 发送接收到的消息 */
        size = rt_device_write(can_dev, 0, &rxmsg, sizeof(rxmsg));
        rt_mutex_release(can_mutex);
        can_msg_rx_cnt++;
        if (size == 0)
        {
            rt_kprintf("can dev write data failed!\n");
        }
    }
}

static void _msh_cmd_set_baud(int argc, char **argv)
{
    rt_err_t result;

    if (argc == 3)
    {
        uint32_t baud = atoi(argv[2]);
        CAN_IF_INIT();
        rt_mutex_take(can_mutex, RT_WAITING_FOREVER);
        result = rt_device_control(can_dev, RT_CAN_CMD_SET_BAUD, (void *)baud);
        rt_mutex_release(can_mutex);
        rt_kprintf("set %s \n", MSH_RESULT_STR(result));
    }
    else
    {
        rt_kprintf(MSH_USAGE_CAN_SET_BAUD);
        rt_kprintf("    e.g. MSH >can set_baud 500000\n");
    }
}

#ifdef RT_CAN_USING_CANFD
void _msh_cmd_set_timing(int argc, char **argv)
{
    rt_err_t result;

    if (argc == 8 || argc == 13)
    {
        uint32_t count = atoi(argv[2]);
        if (count > 2)
        {
            rt_kprintf("param error: count exceed max value 2 \n");
            return;
        }

        struct rt_can_bit_timing items[2];
        struct rt_can_bit_timing_config cfg;
        uint32_t pos = 3;
        items[0].prescaler = atoi(argv[pos++]);
        items[0].num_seg1 =  atoi(argv[pos++]);
        items[0].num_seg2 =  atoi(argv[pos++]);
        items[0].num_sjw =  atoi(argv[pos++]);
        items[0].num_sspoff =  atoi(argv[pos++]);
        if (count > 1)
        {
            items[1].prescaler =  atoi(argv[pos++]);
            items[1].num_seg1 =  atoi(argv[pos++]);
            items[1].num_seg2 =  atoi(argv[pos++]);
            items[1].num_sjw =  atoi(argv[pos++]);
            items[1].num_sspoff =  atoi(argv[pos]);
        }
        cfg.count = count;
        cfg.items = items;
        CAN_IF_INIT();
        rt_mutex_take(can_mutex, RT_WAITING_FOREVER);
        result = rt_device_control(can_dev, RT_CAN_CMD_SET_BITTIMING, &cfg);
        rt_mutex_release(can_mutex);
        rt_kprintf("set %s \n", MSH_RESULT_STR(result));
    }
    else
    {
        rt_kprintf(MSH_USAGE_CAN_SET_BITTIMING);
        rt_kprintf("    e.g. MSH >can set_bittiming 1 1 64 16 16 0\n");
        rt_kprintf("    e.g. MSH >can set_bittiming 2 1 64 16 16 0 1 16 4 4 16\n");
    }
}

void _msh_cmd_set_baudfd(int argc, char **argv)
{
    rt_err_t result;

    if (argc == 3)
    {
        uint32_t baudfd = atoi(argv[2]);
        CAN_IF_INIT();
        rt_mutex_take(can_mutex, RT_WAITING_FOREVER);
        result = rt_device_control(can_dev, RT_CAN_CMD_SET_BAUD_FD, (void *)baudfd);
        rt_mutex_release(can_mutex);
        rt_kprintf("set %s \n", MSH_RESULT_STR(result));
    }
    else
    {
        rt_kprintf(MSH_USAGE_CAN_SET_BAUDFD);
        rt_kprintf("    e.g. MSH >can set_baudfd 4000000\n");
    }
}
#endif

void _msh_cmd_send_msg(int argc, char **argv)
{
    rt_size_t  size;
    struct rt_can_msg msg = {0};
    uint8_t u8Tick;

    if (argc == 2)
    {
        CAN_IF_INIT();
        rt_mutex_take(can_mutex, RT_WAITING_FOREVER);
#ifdef RT_CAN_USING_CANFD
        msg.id  = 0x300;
        msg.ide = RT_CAN_STDID;
        msg.rtr = RT_CAN_DTR;
#ifdef BSP_USING_MCAN
        msg.len = MCAN_DLC64;
#else
        msg.len = CAN_DLC64;
#endif
        msg.fd_frame = 1;
        msg.brs = 1;
        for (u8Tick = 0; u8Tick < 64; u8Tick++)
        {
            msg.data[u8Tick] = u8Tick + 1 + 0xA0;
        }
#else
        msg.id  = 0x300;
        msg.ide = RT_CAN_STDID;
        msg.rtr = RT_CAN_DTR;
        msg.len = CAN_DLC8;
        for (u8Tick = 0; u8Tick < 8; u8Tick++)
        {
            msg.data[u8Tick] = u8Tick + 1 + 0xA0;
        }
#endif
        /* 发送一帧 CAN 数据 */
        size = rt_device_write(can_dev, 0, &msg, sizeof(msg));
        if (size == 0)
        {
            rt_kprintf("can dev write data failed!\n");
        }
        rt_mutex_release(can_mutex);
        can_msg_tx_cnt++;
        rt_kprintf("send msg ok! \n");
    }
    else
    {
        rt_kprintf(MSH_USAGE_CAN_SET_BAUD);
        rt_kprintf("    e.g. MSH >can send_msg \n");
    }
}

void _show_usage(void)
{
    rt_kprintf("Usage: \n");
    rt_kprintf(MSH_USAGE_CAN_SET_BAUD);
#ifdef RT_CAN_USING_CANFD
    rt_kprintf(MSH_USAGE_CAN_SET_BAUDFD);
    rt_kprintf(MSH_USAGE_CAN_SET_BITTIMING);
#endif
    rt_kprintf(MSH_USAGE_CAN_SEND_MSG);
}

int can(int argc, char **argv)
{
    if (!strcmp(argv[1], "set_baud"))
    {
        _msh_cmd_set_baud(argc, argv);
    }
#ifdef RT_CAN_USING_CANFD
    else if (!strcmp(argv[1], "set_baudfd"))
    {
        _msh_cmd_set_baudfd(argc, argv);
    }
    else if (!strcmp(argv[1], "set_bittiming"))
    {
        _msh_cmd_set_timing(argc, argv);
    }
#endif
    else if (!strcmp(argv[1], "send_msg"))
    {
        _msh_cmd_send_msg(argc, argv);
    }
    else
    {
        _show_usage();
    }

    return 0;
}
MSH_CMD_EXPORT(can, can function configuration);

int can_sample(int argc, char **argv)
{
    char can_name[RT_NAME_MAX] = "can1";
    char sem_name[RT_NAME_MAX] = "can_sem";
    char mutex_name[RT_NAME_MAX] = "can_mtx";
    rt_err_t res;

    /* 参数无输入或者输入错误按照默认值处理 */
    if (argc == 2)
    {
        if (0 == rt_strcmp(argv[1], "can1"))
        {
            rt_strcpy(can_name, "can1");
        }
#if defined (HC32F4A0) || defined (HC32F448) || defined (HC32F472)
        else if (0 == rt_strcmp(argv[1], "can2"))
        {
            rt_strcpy(can_name, "can2");
        }
#endif
#if defined (HC32F472)
        else if (0 == rt_strcmp(argv[1], "can3"))
        {
            rt_strcpy(can_name, "can3");
        }
#endif
        else
        {
            rt_kprintf("The chip hasn't the can unit!\r\n");
            return -RT_ERROR;
        }
    }
    else
    {
        rt_kprintf("Default used %s to test!\r\n", can_name);
    }

    /* 设备已经打开则关闭 */
    if (can_dev != RT_NULL)
    {
        rt_device_close(can_dev);
    }
    /* 查找设备 */
    can_dev = rt_device_find(can_name);
    if (!can_dev)
    {
        rt_kprintf("find %s failed!\n", can_name);
        return -RT_ERROR;
    }

    rt_kprintf("found %s\n", can_name);

    if (can_mutex == RT_NULL)
    {
        rt_sem_init(&can_rx_sem, sem_name, 0, RT_IPC_FLAG_FIFO);
        can_mutex = rt_mutex_create(mutex_name, RT_IPC_FLAG_FIFO);
    }

    res = rt_device_open(can_dev, RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);
    RT_ASSERT(res == RT_EOK);
    res = rt_device_control(can_dev, RT_CAN_CMD_SET_BAUD, (void *)CAN500kBaud);
    RT_ASSERT(res == RT_EOK);
    res = rt_device_control(can_dev, RT_CAN_CMD_SET_MODE, (void *)RT_CAN_MODE_NORMAL);
    RT_ASSERT(res == RT_EOK);
#ifdef RT_CAN_USING_CANFD
#if defined (HC32F4A0)
    if (can_name == "can2")
#endif
    {
#ifdef BSP_USING_MCAN
        res = rt_device_control(can_dev, RT_CAN_CMD_SET_BAUD_FD, (void *)MCANFD_DATA_BAUD_4M);
#else
        res = rt_device_control(can_dev, RT_CAN_CMD_SET_BAUD_FD, (void *)CANFD_DATA_BAUD_4M);
#endif
        RT_ASSERT(res == RT_EOK);
    }
#endif
    rt_device_set_rx_indicate(can_dev, can_rx_call);

    _set_default_filter();

    if (rx_thread == RT_NULL)
    {
        rx_thread = rt_thread_create("can_rx", can_rx_thread, RT_NULL, 2048, 15, 10);
        if (rx_thread != RT_NULL)
        {
            rt_thread_startup(rx_thread);
        }
        else
        {
            rt_kprintf("create can_rx rx_thread failed!\n");
        }
    }

    return RT_EOK;
}

MSH_CMD_EXPORT(can_sample, can sample: select < can1 | can2 | can3 >);

#endif
