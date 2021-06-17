
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "ad7730.h"

#ifdef RT_USING_FINSH
#include <finsh.h>

static long ad7730_dump(void)
{
	rt_device_t ad7730_dev = rt_device_find("ad7730");
	if (RT_NULL == ad7730_dev)
	{
		rt_kprintf("device ad7730 not found!\r\n");
		return -RT_ERROR;
	}
	
	rt_err_t ret = rt_device_control(ad7730_dev, AD7730_DUMP_REG, RT_NULL);
	if (RT_EOK != ret)
	{
		rt_kprintf("control device ad7730 failed(%d)!\r\n", ret);
		return ret;
	}
	
	rt_kprintf("OK\r\n");
	
	return RT_EOK;
}
FINSH_FUNCTION_EXPORT(ad7730_dump, dump ad7730 registers);
MSH_CMD_EXPORT(ad7730_dump, dump ad7730 registers);

static long ad7730_start(void)
{
	rt_device_t ad7730_dev = rt_device_find("ad7730");
	if (RT_NULL == ad7730_dev)
	{
		rt_kprintf("device ad7730 not found!\r\n");
		return -RT_ERROR;
	}
	
	rt_err_t ret = rt_device_control(ad7730_dev, AD7730_START_CONT_READ, RT_NULL);
	if (RT_EOK != ret)
	{
		rt_kprintf("ad7730 start continuous read failed(%d)!\r\n", ret);
		return ret;
	}
	
	rt_kprintf("OK\r\n");
	
	return RT_EOK;
}
FINSH_FUNCTION_EXPORT(ad7730_start, start ad7730 continuous read);
MSH_CMD_EXPORT(ad7730_start, start ad7730 continuous read);

static long ad7730_stop(void)
{
	rt_device_t ad7730_dev = rt_device_find("ad7730");
	if (RT_NULL == ad7730_dev)
	{
		rt_kprintf("device ad7730 not found!\r\n");
		return -RT_ERROR;
	}
	
	rt_err_t ret = rt_device_control(ad7730_dev, AD7730_STOP_CONT_READ, RT_NULL);
	if (RT_EOK != ret)
	{
		rt_kprintf("ad7730 stop continuous read failed(%d)!\r\n", ret);
		return ret;
	}
	
	rt_kprintf("OK\r\n");
	
	return RT_EOK;
}
FINSH_FUNCTION_EXPORT(ad7730_stop, stop ad7730 continuous read);
MSH_CMD_EXPORT(ad7730_stop, stop ad7730 continuous read);

static long ad7730_single(void)
{
	rt_device_t ad7730_dev = rt_device_find("ad7730");
	if (RT_NULL == ad7730_dev)
	{
		rt_kprintf("device ad7730 not found!\r\n");
		return -RT_ERROR;
	}
	
	rt_err_t ret = rt_device_control(ad7730_dev, AD7730_START_SINGLE_READ, RT_NULL);
	if (RT_EOK != ret)
	{
		rt_kprintf("ad7730 start single read failed(%d)!\r\n", ret);
		return ret;
	}
	
	rt_kprintf("OK\r\n");
	
	return RT_EOK;
}
FINSH_FUNCTION_EXPORT(ad7730_single, start ad7730 single read);
MSH_CMD_EXPORT(ad7730_single, start ad7730 single read);
#endif

/* event for ad7730 */
static rt_event_t ad7730_event = RT_NULL;

#define AD7730_EVENT_RX_IND 0x00000001

static rt_err_t ad7730_rx_ind(rt_device_t dev, rt_size_t size)
{
	if (ad7730_event && size > 0)
	{
		rt_event_send(ad7730_event, AD7730_EVENT_RX_IND);
	}
	
	return RT_EOK;
}

int main(void)
{
	rt_device_t ad7730_dev = rt_device_find("ad7730");
	if (RT_NULL == ad7730_dev)
	{
		rt_kprintf("device ad7730 not found!\r\n");
		return -RT_ERROR;
	}
	
	rt_err_t ret = rt_device_open(ad7730_dev, RT_DEVICE_FLAG_RDONLY | RT_DEVICE_FLAG_INT_RX);
	if (RT_EOK != ret)
	{
		rt_kprintf("open device ad7730 failed(%d)!\r\n", ret);
		return ret;
	}
	
	ad7730_event = rt_event_create("ad7730_ev", RT_IPC_FLAG_FIFO);
	if (RT_NULL == ad7730_event)
	{
		rt_device_close(ad7730_dev);
		rt_kprintf("create ad7730 mailbox failed!\r\n");
		return -RT_ERROR;
	}
	
	ret = rt_device_set_rx_indicate(ad7730_dev, ad7730_rx_ind);
	if (RT_EOK != ret)
	{
		rt_event_delete(ad7730_event);
		rt_device_close(ad7730_dev);
		rt_kprintf("set vcom rx indicate failed(%d)!\r\n", ret);
		return ret;
	}

    while (1)
	{
		
		rt_uint32_t event_recved = 0;
		ret = rt_event_recv(ad7730_event, (AD7730_EVENT_RX_IND),
						  (RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR),
						  RT_WAITING_FOREVER, &event_recved);
		if (RT_EOK != ret)
		{
			rt_kprintf("recv event failed(%d)!\r\n", ret);
			break;
		}
		
		int32_t ad7730_val = 0;
		rt_size_t read_len = rt_device_read(ad7730_dev, 0, &ad7730_val, sizeof(ad7730_val));
		rt_kprintf("ad7730_val=%d\r\n", ad7730_val);
    }
	
	rt_event_delete(ad7730_event);
	ad7730_event = RT_NULL;
	rt_device_close(ad7730_dev);
	ad7730_dev = RT_NULL;
	
    return ret;
}