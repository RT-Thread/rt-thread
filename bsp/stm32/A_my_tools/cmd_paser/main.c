/****************************************************************************
 *
 * File Name
 *  main.cpp
 * Author
 *  wangk
 * Date
 *  2019/08/04
 * Descriptions:
 * main接口实现
 *
 ******************************************************************************/
/*----------------------------------------------------------------------------*
**                             Dependencies                                   *
**----------------------------------------------------------------------------*/
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "app.h"
#include "cmd.h"


/**---------------------------------------------------------------------------*
 **                            Debugging Flag                                 *
 **---------------------------------------------------------------------------*/
//#define APP_DEBUG
#ifdef APP_DEBUG
    #define APP_TRACE rt_kprintf
#else
    #define APP_TRACE(...)
#endif /* APP_DEBUG */

/**---------------------------------------------------------------------------*
**                             Compiler Flag                                  *
**----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*
**                             Mcaro Definitions                              *
**----------------------------------------------------------------------------*/

/* EVENT定义 */
#define VCOM_EVENT_RX_IND 0x00000002
#define VCOM_EVENT_TX_DONE 0x00000004

/* Vcom发送缓冲区长度 */
#define VCOM_SEND_BUF_SIZE (1024)

/* Vcom设备名 */
#define VCOM_DEVICE_NAME "vcom"

/* event for application */
static rt_event_t app_event = RT_NULL;

/* VCOM设备 */
static rt_device_t vcom_dev = RT_NULL;

/* VCOM接收缓冲区 */
static uint8_t vcom_data_buf[128];

void test1_cmd(void)
{
    rt_kprintf("test1_cmd\n");
	//rt_device_write(vcom);
}

void test2_cmd(void)
{
    rt_kprintf("test2_cmd\n");
}

void test3_cmd(void)
{
    rt_kprintf("test3_cmd\n");
}

REGISTER_CMD(test1, test1_cmd,test1 demo);
REGISTER_CMD(test2, test2_cmd,test2 demo);
REGISTER_CMD(test3, test3_cmd,test3 demo);

static rt_err_t vcom_rx_ind(rt_device_t dev, rt_size_t size)
{
	if (size > 0)
	{
		rt_event_send(app_event, VCOM_EVENT_RX_IND);
	}
	
	return RT_EOK;
}

static rt_err_t vcom_tx_done(rt_device_t dev, void *buffer)
{
	rt_event_send(app_event, VCOM_EVENT_TX_DONE);
	
	return RT_EOK;
}




int main(void)
{

	rt_err_t ret = RT_EOK;
	
	
	
	cmd_init();
	
	/* 创建EVENT */
	app_event = rt_event_create("app_event", RT_IPC_FLAG_FIFO);
	if (RT_NULL == app_event)
	{
		APP_TRACE("create app event failed!\r\n");
	
		
	}
	
	/* 打开VCOM设备 */
	vcom_dev = rt_device_find(VCOM_DEVICE_NAME);
	if (RT_NULL == vcom_dev)
	{
		APP_TRACE("main() call rt_device_find(%s) failed!\r\n", VCOM_DEVICE_NAME);

	}
	else
    {
        ret = rt_device_open(vcom_dev, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX);
        if (RT_EOK != ret)
        {
            APP_TRACE("main() call rt_device_open(vcom_dev) failed, error(%d)!\r\n", ret);
            //main_ret = ret;
            //goto _END;
        }
        else
        {
            ret = rt_device_set_rx_indicate(vcom_dev, vcom_rx_ind);
            if (RT_EOK != ret)
            {
                APP_TRACE("main() call rt_device_set_rx_indicate(vcom_dev) failed, error(%d)!\r\n", ret);
                //main_ret = ret;
                //goto _END;
            }
            
            ret = rt_device_set_tx_complete(vcom_dev, vcom_tx_done);
            if (RT_EOK != ret)
            {
                APP_TRACE("main() call rt_device_set_tx_complete(vcom_dev) failed, error(%d)!\r\n", ret);
                //main_ret = ret;
                //goto _END;
            }
        }
    }

	/* 进入事件循环 */
    while (1)
	{
		
		rt_uint32_t event_recved = 0;
		ret = rt_event_recv(app_event, ( VCOM_EVENT_RX_IND | VCOM_EVENT_TX_DONE ),
						  (RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR),
						  RT_WAITING_FOREVER, &event_recved);
		if (RT_EOK != ret)
		{
			APP_TRACE("recv event failed(%d)!\r\n", ret);
		
			break;
		}		
		if (event_recved & VCOM_EVENT_RX_IND)
		{ // 收到VCOM数据
            if (vcom_dev == RT_NULL)
            {
                continue;
            }
            
			/* 收取所有数据 */
			while (1)
			{
				rt_size_t read_len = rt_device_read(vcom_dev, 0,vcom_data_buf, sizeof(vcom_data_buf));
        if(read_len > 0)   
				{
				rt_kprintf("-$ %s\r\n", vcom_data_buf);
        cmd_parsing((char *)vcom_data_buf);					
        memset(&vcom_data_buf, 0, sizeof(vcom_data_buf));					
				}
				else
				{
					break;
				}
					
        
			

			}
		}	
		
			if (event_recved & VCOM_EVENT_TX_DONE)
		{ 

		}

   }
	
}

/**
 * Function    ota_app_vtor_reconfig
 * Description Set Vector Table base location to the start addr of app(RT_APP_PART_ADDR).
*/

/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/

