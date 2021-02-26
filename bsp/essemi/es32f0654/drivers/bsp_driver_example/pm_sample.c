/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-15     liuhy       first implementation.
 */
/*
 * 程序清单：这是一个 pm睡眠唤醒的使用例程
 * 例程导出了 pm_sample 命令到控制终端
 * 命令调用格式：pm_sample
 * 命令解释：进入不同的睡眠模式，然后用按键唤醒
 * 程序功能：通过串口输出字符串，告知进入睡眠和唤醒睡眠的情况。
*/

#include <rtthread.h>
#include <rtdevice.h>

#define PM_NAME       "pm"      /* 设备名称 */
#define WAKE_UP_PIN     18      /* 唤醒源 */
#define SLEEP_TIMES     12      /* 进入睡眠次数，轮流进入不同的睡眠模式，包括无睡眠模式 */


struct pm_callback_t
{
     volatile int in_fun_times;   /*进入函数的次数*/
     volatile char flag;          /*标志*/
     volatile int mode;           /*需要打印的模式*/
};

volatile struct pm_callback_t g_pm_data;

/*进入睡眠前，睡眠唤醒后，都会进入。*/
/*函数打印睡眠相关的信息*/
void sleep_in_out_callback(rt_uint8_t event, rt_uint8_t mode, void *data)
{
    /*没有标志，不处理*/
    if(!(g_pm_data.flag))
    {
        return;
    }
    
    /*标志不正常，清空标志*/
    if((g_pm_data.flag) > 2)
    {
        (g_pm_data.flag) = 0;
        return;
    }
    
    /*模式不匹配*/
    if(g_pm_data.mode != mode )
    {
        return;
    }
 
    /*进入的事件*/
    switch(event)
    {
        /*进入睡眠前*/
        case RT_PM_ENTER_SLEEP: g_pm_data.flag = 1;
                                rt_kprintf("\n\r##%d :  ENTER  ",g_pm_data.in_fun_times);
                                g_pm_data.in_fun_times++;     /*进入睡眠次数+1*/
                                break;
        /*睡眠唤醒后*/
        case RT_PM_EXIT_SLEEP:  g_pm_data.flag = 0;  /*睡眠唤醒后*/
                                rt_kprintf("\n\rEXIT\n\r");
                                rt_pm_release(mode);   /*释放休眠模式*/
                                return;
        
        default: break;
        
    };
    
    /*当前的睡眠模式*/
    switch(mode)
    {
        case PM_SLEEP_MODE_NONE: rt_kprintf("PM_SLEEP_MODE_NONE\n\r");
                                break;
        case PM_SLEEP_MODE_IDLE:  rt_kprintf("PM_SLEEP_MODE_IDLE\n\r");
                                break;
        case PM_SLEEP_MODE_LIGHT: rt_kprintf("PM_SLEEP_MODE_LIGHT\n\r");
                                break;
        case PM_SLEEP_MODE_DEEP:  rt_kprintf("PM_SLEEP_MODE_DEEP\n\r");
                                break;
        case PM_SLEEP_MODE_STANDBY: rt_kprintf("PM_SLEEP_MODE_STANDBY\n\r");
                                break;
        case PM_SLEEP_MODE_SHUTDOWN:  rt_kprintf("PM_SLEEP_MODE_SHUTDOWN\n\r");
                                break;      
        case PM_SLEEP_MODE_MAX:  rt_kprintf("PM_SLEEP_MODE_MAX\n\r");
                                break;
        default: break;           
    }
    
}

/* pm测试函数 */
static void pm_test(void *parameter)
{
    int in_mode[7],i = 0;
    
        g_pm_data.in_fun_times = 0;
        g_pm_data.flag = 0;
    
        in_mode[0] = PM_SLEEP_MODE_NONE;
        in_mode[1] = PM_SLEEP_MODE_IDLE;
        in_mode[2] = PM_SLEEP_MODE_LIGHT;
        in_mode[3] = PM_SLEEP_MODE_DEEP;
        in_mode[4] = PM_SLEEP_MODE_STANDBY;
        in_mode[5] = PM_SLEEP_MODE_SHUTDOWN;
        in_mode[6] = PM_SLEEP_MODE_MAX;
    
    /*设置回调函数和私有数据*/
    rt_pm_notify_set(sleep_in_out_callback,RT_NULL);
       
    while(i < SLEEP_TIMES)
   {
       
       g_pm_data.mode = in_mode[i%6];
       
       /*无休眠模式，不赋予标志*/
       if(g_pm_data.mode != PM_SLEEP_MODE_NONE)
       {
            g_pm_data.flag = 2;  
       
       }
       
       /*请求选择的休眠模式*/
       rt_pm_request(in_mode[i%6]);

       rt_thread_mdelay(500);
       
       /*无休眠模式，不需要额外的等待*/
       while(( g_pm_data.flag != 0 )&&(g_pm_data.mode != PM_SLEEP_MODE_NONE))
       {
           rt_thread_mdelay(500);
       }
       
       /*释放选择的休眠模式*/
       rt_pm_release(in_mode[i%6]);
       
       i++;
       
   }
      /*清除回调函数和私有数据*/
    rt_pm_notify_set(RT_NULL,RT_NULL);
   rt_kprintf("thread pm_test close\n\r");
}

/*按键唤醒的回调函数*/
void wake_by_pin(void *args)
{

}

static int pm_sample(int argc, char *argv[])
{
    rt_thread_t thread;
    
    /* 按键引脚为输入模式 */
    rt_pin_mode(WAKE_UP_PIN, PIN_MODE_INPUT_PULLUP);
    
    /* 绑定中断，下降沿模式，回调函数名为wake_by_pin */
    rt_pin_attach_irq(WAKE_UP_PIN, PIN_IRQ_MODE_RISING, wake_by_pin, RT_NULL);
    /* 使能中断 */
    rt_pin_irq_enable(WAKE_UP_PIN, PIN_IRQ_ENABLE);
    
    thread = rt_thread_create("pm_test", pm_test, RT_NULL, 1024, 25, 10);
    
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        rt_kprintf("create pm_test thread failed!\n\r");
    }
    
    return RT_EOK;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(pm_sample, pm sample);
