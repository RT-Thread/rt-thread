/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.

 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-10     CDT          first version
 */

/*
* 功能
*   展示捕获单元 ic1、ic2、ic3 的捕获输入功能
*   当捕获单元捕获到设定数量（watermark）的数据(微秒级别的电平宽度)后，终端将输出这些已捕获的数据
*
* 默认配置
*   input pin：
*       ic1: INPUT_CAPTURE_TMR6_1_PORT, INPUT_CAPTURE_TMR6_1_PIN
*       ic2: INPUT_CAPTURE_TMR6_2_PORT, INPUT_CAPTURE_TMR6_2_PIN
*       ic3: INPUT_CAPTURE_TMR6_3_PORT, INPUT_CAPTURE_TMR6_3_PIN
*   watermark：
*       ic1：5
*       ic2：5
*       ic3: 5
*
* 命令行命令
*   1）开启捕获单元：
*       格式：
*           ic open <unit>
*       示例：
*           MSH >ic open 3（开启 ic3）
*   2）关闭捕获单元：
*       格式：
*           ic close <unit>
*       示例：
*           MSH >ic close 3 （关闭 ic3）
*   3）设置捕获单元的 watermark：
*       格式：
*           ic wm <unit> <wm>
*       示例：
*           MSH >ic wm 3 11 （设置 ic3 的 watermark 为 11）
*   4）清除捕获单元的捕获数据：
*       格式：
*           ic clr <unit>
*       示例：
*           MSH >ic clr 3 （清除 ic3 的捕获数据）
*   5）显示命令的使用方法说明：
*       格式：
*           ic
*       示例：
*           MSH >ic
*/

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <stdlib.h>

#define MSH_USAGE_IC_OPEN               "  ic open <unit>     - e.g., open ic3: ic open 3 \n"
#define MSH_USAGE_IC_CLOSE              "  ic close <unit>    - e.g., close ic3: ic close 3\n"
#define MSH_USAGE_IC_SET_WM             "  ic wm <unit> <wm>  - e.g., set warter mark of ic3 to 11: ic wm 3 11\n"
#define MSH_USAGE_IC_CLR                "  ic clr <unit>      - e.g., clear data buffer of ic3: ic clr 3 \n"

#if defined (HC32F4A0)
    #define IC_DEV_CNT                  (8)
#elif defined (HC32F460)
    #define IC_DEV_CNT                  (3)
#endif
#define IC_NAME_LEN                     (3)
#define DEFAULT_WATER_MARK              (5)

#ifdef BSP_USING_INPUT_CAPTURE

typedef struct
{
    rt_device_t ic_dev;
    rt_sem_t rx_sem;
    rt_mutex_t mutex;
    __IO rt_size_t ic_data_size;
    rt_thread_t thread;
} test_ic_t;

static test_ic_t g_arr_test_ic[IC_DEV_CNT] = {0};

static int32_t _get_test_id(rt_device_t ic_dev)
{
    for (int i = 0; i < IC_DEV_CNT; i++)
    {
        if (ic_dev == g_arr_test_ic[i].ic_dev)
        {
            return i;
        }
    }

    return -1;
}

static rt_err_t ic_rx_all(rt_device_t dev, rt_size_t size)
{
    uint32_t id = _get_test_id(dev);

    g_arr_test_ic[id].ic_data_size = size;
    rt_sem_release((g_arr_test_ic[id].rx_sem));

    return RT_EOK;
}

static void ic_rx_thread(void *parameter)
{
    rt_size_t  size;
    rt_device_t ic_dev;
    rt_uint32_t id = *(uint32_t *)parameter;
    test_ic_t *p_test_ic = &g_arr_test_ic[id];
    ic_dev = p_test_ic->ic_dev;
    struct rt_inputcapture_data *pData = RT_NULL;
    struct rt_inputcapture_data *pItem = RT_NULL;
    int i = 0;
    while (1)
    {
        rt_sem_take((p_test_ic->rx_sem), RT_WAITING_FOREVER);
        pData = (struct rt_inputcapture_data *)rt_malloc(sizeof(struct rt_inputcapture_data) * p_test_ic->ic_data_size);
        if (pData)
        {
            rt_mutex_take(p_test_ic->mutex, RT_WAITING_FOREVER);
            size = rt_device_read(ic_dev, 0, pData, p_test_ic->ic_data_size);
            rt_mutex_release(p_test_ic->mutex);
            if (size == 0)
            {
                rt_free(pData);
                pData = RT_NULL;
                continue;
            }
            rt_kprintf("ic%d captured %d data:\n", id + 1, size);
            for (i = 0; i < size; i++)
            {
                pItem = pData + i;
                rt_kprintf("%d : h = %d, w =%d\n", i, pItem->is_high, pItem->pulsewidth_us);
            }
            rt_free(pData);
            pData = RT_NULL;
        }
        rt_kprintf("-------------------\n");

    }
}

static rt_int32_t _ic_test_open(rt_int32_t id)
{
    rt_err_t ret = RT_EOK;
    uint32_t def_wm = DEFAULT_WATER_MARK;
    rt_device_t ic_dev;


    char ic_name[IC_NAME_LEN] = "ic";
    ic_name[IC_NAME_LEN - 1] = 0x30 + id + 1;

    ic_dev = rt_device_find(ic_name);
    RT_ASSERT(ic_dev != RT_NULL);
    g_arr_test_ic[id].ic_dev = ic_dev;
    g_arr_test_ic[id].rx_sem = rt_sem_create(ic_name, 0, RT_IPC_FLAG_FIFO);
    g_arr_test_ic[id].mutex = rt_mutex_create(ic_name, RT_IPC_FLAG_FIFO);

    ret = rt_device_init(ic_dev);
    RT_ASSERT(ret == RT_EOK);
    rt_device_set_rx_indicate(ic_dev, ic_rx_all);

    g_arr_test_ic[id].thread = rt_thread_create(ic_name, ic_rx_thread, &id, 2048, 5, 10);
    RT_ASSERT(g_arr_test_ic[id].thread != RT_NULL);
    rt_thread_startup(g_arr_test_ic[id].thread);

    ret = rt_device_open(ic_dev, 0);
    RT_ASSERT(ret == RT_EOK);
    ret = rt_device_control(ic_dev, INPUTCAPTURE_CMD_SET_WATERMARK, &def_wm);
    RT_ASSERT(ret == RT_EOK);

    return RT_EOK;
}

static rt_int32_t _ic_test_close(rt_int32_t id)
{
    rt_err_t ret = RT_EOK;

    ret = rt_device_close(g_arr_test_ic[id].ic_dev);
    RT_ASSERT(ret == RT_EOK);
    rt_sem_delete(g_arr_test_ic[id].rx_sem);
    rt_mutex_delete(g_arr_test_ic[id].mutex);
    rt_thread_delete(g_arr_test_ic[id].thread);
    rt_memset(&g_arr_test_ic[id], 0, sizeof(test_ic_t));

    return RT_EOK;
}

static rt_int32_t _ic_ctrl(rt_int32_t id, rt_int32_t cmd, char *param)
{
    rt_err_t ret = RT_EOK;
    uint32_t int_param = (param == RT_NULL) ? 0 : atoi(param);

    rt_mutex_take(g_arr_test_ic[id].mutex, RT_WAITING_FOREVER);
    ret = rt_device_control(g_arr_test_ic[id].ic_dev, cmd, &int_param);
    rt_mutex_release(g_arr_test_ic[id].mutex);

    return ret;
}

static rt_err_t _msh_cmd_parse_unit(char *n, uint32_t *u_out)
{
    rt_err_t result = -RT_ERROR;
    uint32_t u_temp = atoi(n) - 1;
    if (u_temp >= IC_DEV_CNT)
    {
        rt_kprintf("param error: channel exceed max value %d \n", IC_DEV_CNT);
        return result;
    }
    *u_out = u_temp;

    return RT_EOK;
}

void _show_usage(void)
{
    rt_kprintf("Usage: \n");
    rt_kprintf(MSH_USAGE_IC_OPEN);
    rt_kprintf(MSH_USAGE_IC_CLOSE);
    rt_kprintf(MSH_USAGE_IC_SET_WM);
    rt_kprintf(MSH_USAGE_IC_CLR);
}

static rt_int32_t ic(int argc, char *argv[])
{
    uint32_t id = 0;

    if (argc == 1)
    {
        _show_usage();
        return 0;
    }

    switch (argc)
    {
    case 1:
        _show_usage();
        return 0;

    case 3:
    case 4:
        if (_msh_cmd_parse_unit(argv[2], &id) != RT_EOK)
        {
            return 0;
        }
        if (!rt_strcmp(argv[1], "open"))
        {
            if (g_arr_test_ic[id].ic_dev != RT_NULL)
            {
                return 0;
            }
            _ic_test_open(id);
            break;
        }

        if (g_arr_test_ic[id].ic_dev == RT_NULL)
        {
            return 0;
        }
        if (!rt_strcmp(argv[1], "close"))
        {
            _ic_test_close(id);
        }
        else if (!rt_strcmp(argv[1], "wm"))
        {
            _ic_ctrl(id, INPUTCAPTURE_CMD_SET_WATERMARK, argv[3]);
        }
        else if (!rt_strcmp(argv[1], "clr"))
        {
            _ic_ctrl(id, INPUTCAPTURE_CMD_CLEAR_BUF, RT_NULL);
        }
        else
        {
            rt_kprintf("usage error, input \"ic\" to show cmd info\n");
            return 0;
        }
        break;
    default:
        rt_kprintf("usage error, input \"ic\" to show cmd info\n");
        return 0;
    }

    rt_kprintf("done \n");

    return 0;
}


MSH_CMD_EXPORT(ic, ic [opt])
#endif
/*
 EOF
*/
