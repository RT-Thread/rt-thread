/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       		Notes
 * 2015-05-14     aubrcool@qq.com 	first version
 */

#include <board.h>
#include <rtthread.h>
#include <rtdevice.h>
#ifdef RT_USING_CAN
#include "drv_lpccan.h"
struct can_app_struct
{
	const char* name;
	struct rt_can_filter_config * filter;
	rt_uint8_t eventopt;
	struct rt_semaphore sem;
};
static struct can_app_struct can_data[1];
struct rt_can_filter_item filter1item[4] =
{
	LPC_CAN_AF_STD_INIT(1),
	LPC_CAN_AF_STD_GRP_INIT(3,5),
	LPC_CAN_AF_EXT_INIT(2),
	LPC_CAN_AF_EXT_GRP_INIT(4,6),
};
struct rt_can_filter_config filter1 =
{
	4,
	1,
	filter1item,
};
static struct can_app_struct can_data[1] = {
	{
		"lpccan1",
		&filter1,
		RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
	},
};
static rt_err_t lpccanind(rt_device_t dev, rt_size_t size)
{
	rt_sem_release(&can_data[0].sem);
}
void rt_can_thread_entry(void* parameter)
{
	struct rt_can_msg msg;
	struct can_app_struct* canpara = (struct can_app_struct*) parameter;
	rt_device_t candev;

	candev = rt_device_find(canpara->name);
	RT_ASSERT(candev);
	rt_sem_init(&canpara->sem, canpara->name, 0, RT_IPC_FLAG_FIFO);
	rt_device_open(candev, (RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX));
	rt_device_control(candev,RT_CAN_CMD_SET_FILTER,canpara->filter);
	rt_device_set_rx_indicate(candev, lpccanind);
	while(1) {
		rt_sem_take(&canpara->sem, RT_WAITING_FOREVER);
		while (rt_device_read(candev, 0, &msg, sizeof(msg)) == sizeof(msg)) {
			rt_device_write(candev, 0, &msg, sizeof(msg));
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

	return 0;
}

INIT_APP_EXPORT(rt_can_app_init);
#endif /*RT_USING_CAN*/
