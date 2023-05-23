/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2023-5-23      Chushicheng    first version.
 */
/*
 * 程序清单：这是一个触摸设备使用例程
 * 例程导出了 touch_sample 命令到控制终端
 * 命令调用格式：touch_sample
 * 程序功能：检测触摸点，并打印触摸点坐标。
*/

#include <rtthread.h>
#include <rtdevice.h>

#ifdef BSP_USING_TOUCH

#define TOUCH_DEV_NAME  "touch"

static void touch_sample(void){
    char name[RT_NAME_MAX];
    rt_strncpy(name, TOUCH_DEV_NAME, RT_NAME_MAX);

    static rt_device_t dev = RT_NULL;
    static struct rt_touch_data *read_data;
    read_data = (struct rt_touch_data *)rt_malloc(sizeof(struct rt_touch_data));
    
    dev = rt_device_find(name);
    if (dev == RT_NULL)
    {
        rt_kprintf("can't find %s device!\n", name);
    }
    rt_device_open(dev, RT_DEVICE_FLAG_INT_RX);

    while(1){
        if(rt_pin_read(TOUCH_INT_PIN) == 0){ //if int pin is 0 was touched
            if(rt_device_read(dev, 0, read_data, 1)!=0){
            uint16_t pos_x = read_data->x_coordinate;
            uint16_t pos_y = read_data->y_coordinate;
            rt_kprintf("x: %d y:%d\r\n",pos_x,pos_y);
            }
        }
        
        rt_thread_mdelay(10);
    }
}
MSH_CMD_EXPORT(touch_sample, touch sample);

#endif  /* RT_USING_TOUCH */
