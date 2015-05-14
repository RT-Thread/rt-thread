/*
 * File      : canapp.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       		Notes
 * 2015-05-14     aubrcool@qq.com 	first version
 */

#ifdef RT_USING_CAN
#include <board.h>
#include <rtthread.h>
#include <rtdevice.h>
struct can_app_struct
{
    const char* name;
    struct rt_event event;
    struct rt_can_filter_config * filter;
    rt_uint8_t eventopt;
};
static struct can_app_struct can_data[2];
static rt_err_t  can1ind(rt_device_t dev,  void* args, rt_int32_t hdr, rt_size_t size)
{
    rt_event_t pevent = (rt_event_t)args;
    rt_event_send(pevent, 1 << (hdr));
    return RT_EOK;
}
static rt_err_t  can2ind(rt_device_t dev, void* args, rt_int32_t hdr, rt_size_t size)
{
    rt_event_t pevent = (rt_event_t)args;
    rt_event_send(pevent, 1 << (hdr));
    return RT_EOK;
}
struct rt_can_filter_item filter1item[4] =
{
  RT_CAN_FILTER_STD_INIT(1,can1ind,&can_data[0].event),
  RT_CAN_FILTER_STD_INIT(2,can1ind,&can_data[0].event),
  RT_CAN_STD_RMT_FILTER_INIT(3,can1ind,&can_data[0].event),
  RT_CAN_STD_RMT_DATA_FILTER_INIT(4,can1ind,&can_data[0].event),
};
struct rt_can_filter_item filter2item[4] =
{
  RT_CAN_FILTER_STD_INIT(1,can2ind,&can_data[1].event),
  RT_CAN_FILTER_STD_INIT(2,can2ind,&can_data[1].event),
  RT_CAN_STD_RMT_FILTER_INIT(3,can2ind,&can_data[1].event),
  RT_CAN_STD_RMT_DATA_FILTER_INIT(4,can2ind,&can_data[1].event),
};
struct rt_can_filter_config filter1 =
{
       .count = 4,
       .actived = 1,
       .items = filter1item,
};
struct rt_can_filter_config filter2 =
{
       .count = 4,
       .actived = 1,
       .items = filter2item,
};
static struct can_app_struct can_data[2] = {
    {
      .name = "bxcan1",
      .filter = &filter1,
      .eventopt = RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
    },
    {
      .name = "bxcan2",
      .filter = &filter2,
      .eventopt = RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
    },
};
void rt_can_thread_entry(void* parameter)
{
      struct rt_can_msg msg;
      struct can_app_struct* canpara = (struct can_app_struct*) parameter;
      rt_device_t candev;
      rt_uint32_t e;

      candev = rt_device_find(canpara->name);
      RT_ASSERT(candev);
      rt_event_init(&canpara->event, canpara->name, RT_IPC_FLAG_FIFO);
      rt_device_open(candev, (RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX));
      rt_device_control(candev,RT_CAN_CMD_SET_FILTER,canpara->filter);
      while(1) {
              if (
                     rt_event_recv(&canpara->event, 
                     ((1 << canpara->filter->items[0].hdr)  |
                      (1 << canpara->filter->items[1].hdr) |
                      (1 << canpara->filter->items[2].hdr) |
                      (1 << canpara->filter->items[3].hdr)),
                      canpara->eventopt,
                      RT_WAITING_FOREVER, &e) != RT_EOK
                  ) {
                    continue;
                  }
              if(e & (1 << canpara->filter->items[0].hdr)) {
                  msg.hdr = canpara->filter->items[0].hdr;
                  while (rt_device_read(candev, 0, &msg, sizeof(msg)) == sizeof(msg)) {
                     rt_device_write(candev, 0, &msg, sizeof(msg));
                  }
              }
              if(e & (1 << canpara->filter->items[1].hdr)) {
                  msg.hdr = canpara->filter->items[1].hdr;
                  while (rt_device_read(candev, 0, &msg, sizeof(msg)) == sizeof(msg)) {
                     rt_device_write(candev, 0, &msg, sizeof(msg));
                  }
              }
              if(e & (1 << canpara->filter->items[2].hdr)) {
                  msg.hdr = canpara->filter->items[2].hdr;
                  while (rt_device_read(candev, 0, &msg, sizeof(msg)) == sizeof(msg)) {
                     rt_device_write(candev, 0, &msg, sizeof(msg));
                  }
              }
              if(e & (1 << canpara->filter->items[3].hdr)) {
                  msg.hdr = canpara->filter->items[3].hdr;
                  while (rt_device_read(candev, 0, &msg, sizeof(msg)) == sizeof(msg)) {
                     rt_device_write(candev, 0, &msg, sizeof(msg));
                  }
              }
      }
}
int rt_can_app_init(void)
{
    rt_thread_t tid;
    
    tid = rt_thread_create("canapp1",
    rt_can_thread_entry, &can_data[0],
    512, RT_THREAD_PRIORITY_MAX /3 - 1, 20);
    if (tid != RT_NULL) rt_thread_startup(tid);
    
    tid = rt_thread_create("canapp2",
    rt_can_thread_entry, &can_data[1],
    512, RT_THREAD_PRIORITY_MAX /3 - 1, 20);
    if (tid != RT_NULL) rt_thread_startup(tid);
    
    return 0;
}

INIT_APP_EXPORT(rt_can_app_init);
#endif /*RT_USING_CAN*/
