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
 * 程序清单： Pulse encoder 设备使用例程, 请在图形化配置界面打开pulse encoder device，
 * 并使能tmra_1和tmr6_1.
 * 例程导出了 encoder_sample 命令到控制终端, 通过串口可查看当前的count数值
 * 命令调用格式：pulse_encoder_sample devname [option1] [option2]
 *                                  devname: [pulse_a1/pulse_61] 编码器单元名称
 *                                  option1: 正转脉冲数
 *                                  option2: 反转脉冲数
 * eg:encoder_sample pulse_a1 2000 1000
 * 编码器的分辨率是1000
 * 硬件IO查看对应board/board_config.h中相关端口定义，并且需要正确连接到对应模拟脉冲生成的端口
 * 程序功能：
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <stdlib.h>
#include "board_config.h"
#include <board.h>

#ifdef BSP_USING_PULSE_ENCODER

#if defined (HC32F4A0)
    #define TEST_IO_A_PIN GET_PIN(A, 5)
    #define TEST_IO_B_PIN GET_PIN(A, 6)
#else
    #define TEST_IO_A_PIN GET_PIN(B, 0)
    #define TEST_IO_B_PIN GET_PIN(B, 1)
#endif

static rt_device_t pulse_encoder_dev = RT_NULL;

static void printf_connect(void)
{
#if defined (HC32F4A0)
#if defined(BSP_USING_PULSE_ENCODER_TMRA_1)
    rt_kprintf("  [tmra]*connect PA5-->PA8 PA6-->PA9\n");
#endif
#if defined(BSP_USING_PULSE_ENCODER_TMR6_1)
    rt_kprintf("  [tmr6]*connect PA5-->PB9 PA6-->PB8\n");
#endif
#endif
#if defined (HC32F460)
#if defined(BSP_USING_PULSE_ENCODER_TMRA_1)
    rt_kprintf("  [tmra]*connect PB0-->PA8 PB1-->PA9\n");
#endif
#if defined(BSP_USING_PULSE_ENCODER_TMR6_1)
    rt_kprintf("  [tmr6]*connect PB0-->PE9 PB1-->PE8\n");
#endif
#endif
#if defined (HC32F448)
#if defined(BSP_USING_PULSE_ENCODER_TMRA_1)
    rt_kprintf("  [tmra]*connect PB0-->PA8 PB1-->PA9\n");
#endif
#if defined(BSP_USING_PULSE_ENCODER_TMR6_1)
    rt_kprintf("  [tmr6]*connect PB0-->PB5 PB1-->PB13\n");
#endif
#endif
#if defined (HC32F472)
#if defined(BSP_USING_PULSE_ENCODER_TMRA_1)
    rt_kprintf("  [tmra]*connect PB0-->PA0 PB1-->PA1\n");
#endif
#if defined(BSP_USING_PULSE_ENCODER_TMR6_1)
    rt_kprintf("  [tmr6]*connect PB0-->PA3 PB1-->PA7\n");
#endif
#endif
}

static void _pulse_cmd_print_usage(void)
{
    rt_kprintf("encoder_sample devname [option1] [option2]\n");
    rt_kprintf("  devname: [pulse_a1/pulse_61..] pulse uint\n");
    rt_kprintf("  option1: number of positive pulses\n");
    rt_kprintf("  option2: number of reversal pulses\n");
    rt_kprintf("    e.g. MSH >encoder_sample pulse_a1 2000 1000\n");
    printf_connect();
}

static void GenClkUp(const uint16_t cnt)
{
    uint32_t i, j;
    rt_int32_t count;
    const uint8_t bAin[4U] = {1U, 1U, 0U, 0U};
    const uint8_t bBin[4U] = {0U, 1U, 1U, 0U};
    for (j = 0UL; j < cnt; j++)
    {
        for (i = 0UL; i < 4UL; i++)
        {
            if (0U == bAin[i])
            {
                rt_pin_write(TEST_IO_A_PIN, PIN_LOW);
            }
            else
            {
                rt_pin_write(TEST_IO_A_PIN, PIN_HIGH);
            }
            if (0U == bBin[i])
            {
                rt_pin_write(TEST_IO_B_PIN, PIN_LOW);
            }
            else
            {
                rt_pin_write(TEST_IO_B_PIN, PIN_HIGH);
            }
            rt_thread_mdelay(1UL);
        }
        rt_device_read(pulse_encoder_dev, 0, &count, 1);
        rt_kprintf("%d\r\n", count);
    }
}

static void GenClkDown(const uint16_t cnt)
{
    uint32_t i, j;
    rt_int32_t count;
    const uint8_t bAin[4U] = {0U, 1U, 1U, 0U};
    const uint8_t bBin[4U] = {1U, 1U, 0U, 0U};
    for (j = 0UL; j < cnt; j++)
    {
        for (i = 0UL; i < 4UL; i++)
        {
            if (0U == bAin[i])
            {
                rt_pin_write(TEST_IO_A_PIN, PIN_LOW);
            }
            else
            {
                rt_pin_write(TEST_IO_A_PIN, PIN_HIGH);
            }
            if (0U == bBin[i])
            {
                rt_pin_write(TEST_IO_B_PIN, PIN_LOW);
            }
            else
            {
                rt_pin_write(TEST_IO_B_PIN, PIN_HIGH);
            }
            rt_thread_mdelay(1UL);
        }
        rt_device_read(pulse_encoder_dev, 0, &count, 1);
        rt_kprintf("%d\r\n", count);
    }
}

static int encoder_sample(int argc, char **argv)
{
    rt_int32_t count;

    if ((argc != 4))
    {
        _pulse_cmd_print_usage();
        return -RT_ERROR;
    }

    rt_pin_mode(TEST_IO_A_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(TEST_IO_B_PIN, PIN_MODE_OUTPUT);

    pulse_encoder_dev = rt_device_find(argv[1]);
    if (pulse_encoder_dev == RT_NULL)
    {
        rt_kprintf("encoder_sample run failed! can't find %s device!\n", argv[1]);
        _pulse_cmd_print_usage();
        return -RT_ERROR;
    }
    rt_device_open(pulse_encoder_dev, RT_DEVICE_OFLAG_RDONLY);
    rt_device_control(pulse_encoder_dev, PULSE_ENCODER_CMD_CLEAR_COUNT, RT_NULL);
    rt_device_control(pulse_encoder_dev, PULSE_ENCODER_CMD_ENABLE, RT_NULL);

    /* 自测DISABLE和CLEAR功能 */
    GenClkUp(100);
    rt_device_control(pulse_encoder_dev, PULSE_ENCODER_CMD_DISABLE, RT_NULL);
    /* 测试DISABLE后是否还会计数 */
    GenClkUp(10);
    rt_device_read(pulse_encoder_dev, 0, &count, 1);
    rt_device_control(pulse_encoder_dev, PULSE_ENCODER_CMD_CLEAR_COUNT, RT_NULL);
    if (count != 100)
    {
        rt_kprintf("**************Self-test failed**************\n");
        rt_device_close(pulse_encoder_dev);
        _pulse_cmd_print_usage();
        return -RT_ERROR;
    }
    else
    {
        rt_kprintf("**************Self-test success**************\n");
        rt_device_control(pulse_encoder_dev, PULSE_ENCODER_CMD_ENABLE, RT_NULL);
        GenClkUp(atoi(argv[2]));
        GenClkDown(atoi(argv[3]));

        rt_device_read(pulse_encoder_dev, 0, &count, 1);
        if (count == (atoi(argv[2]) - atoi(argv[3])))
        {
            rt_kprintf("encoder_sample test success\n");
        }
        else
        {
            rt_kprintf("encoder_sample test failed\n");
        }

        rt_device_close(pulse_encoder_dev);
    }

    return RT_EOK;
}

/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(encoder_sample, encoder sample devname [option1] [option2]);
#endif
