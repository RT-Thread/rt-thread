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
#if defined(BSP_USING_RSCDRRM020NDSE3)
#include "rscdrrm020ndse3.h"
#elif defined(BSP_USING_AD7730)
#include "ad7730.h"
#endif
//#include "sendwave.h"
#include "app.h"
//#include "cmd.h"
#include "cyclequeue.h"
#include "board_config.h"

//#include "at.h"
extern "C"
{
  //  #include "fal.h"
  #include "cmd_parser.h"
}

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
#ifdef __cplusplus
extern   "C"
{
#endif

/*----------------------------------------------------------------------------*
**                             Mcaro Definitions                              *
**----------------------------------------------------------------------------*/
/* EVENT定义 */
#define SENSOR_EVENT_RX_IND 0x00000001
#define VCOM_EVENT_RX_IND 0x00000002
#define VCOM_EVENT_TX_DONE 0x00000004

/* Vcom发送缓冲区长度 */
#define VCOM_SEND_BUF_SIZE (1024)
/* BT发送缓冲区长度 */
#define BT_SEND_BUF_SIZE (1024)

/* Vcom设备名 */
#define VCOM_DEVICE_NAME "vcom"



/*----------------------------------------------------------------------------*
**                             Data Structures                                *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Local Vars                                     *
**----------------------------------------------------------------------------*/
/* event for application */
static rt_event_t app_event = RT_NULL;




/* VCOM设备 */
static rt_device_t vcom_dev = RT_NULL;
/* VCOM接收缓冲区 */
static uint8_t vcom_data_buf[128] = {0};
/* Vcom数据发送队列 */
static CycleQueue_T s_tVcomSendQ = {NULL};
/* Vcom发送队列缓冲区 */
static uint8_t s_pu8VcomSendQueBuf[VCOM_SEND_BUF_SIZE * 4] = {0};
/* Vcom发送缓冲区 */
static uint8_t s_pu8VcomSendBuf[VCOM_SEND_BUF_SIZE] = {0};
/* Vcom是否正在发送状态 */
static bool s_bVcomSending = false;
/*----------------------------------------------------------------------------*
**                             Extern Function                                *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Local Function                                 *
**----------------------------------------------------------------------------*/

/*************************************************
* Function: vcom_rx_ind
* Description: VCOM数据收取回调函数
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
static rt_err_t vcom_rx_ind(rt_device_t dev, rt_size_t size)
{
	if (size > 0)
	{
		rt_event_send(app_event, VCOM_EVENT_RX_IND);
	}
	
	return RT_EOK;
}

/*************************************************
* Function: vcom_tx_done
* Description: VCOM数据发送完成回调函数
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
static rt_err_t vcom_tx_done(rt_device_t dev, void *buffer)
{
	rt_event_send(app_event, VCOM_EVENT_TX_DONE);
	
	return RT_EOK;
}


/*----------------------------------------------------------------------------*
**                             Public Function                                *
**----------------------------------------------------------------------------*/
static COM_MODE_E com_mode = COM_MODE_VCOM; // 默认VCOM优先

/*************************************************
* Function: set_com_mode
* Description: 配置通信模式(BT优先/VCOM优先)
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
bool set_com_mode(COM_MODE_E mode)
{
	APP_TRACE("set_com_mode() mode=%d\r\n", mode);
	if ((COM_MODE_BT != mode) 
		&& (COM_MODE_VCOM != mode))
	{ // 模式无效
		APP_TRACE("set_com_mode() failed, invalid mode(%d)!\r\n", mode);
		return false;
	}
	
	/* 设置当前模式 */
	com_mode = mode;
	
	return true;
}

/*************************************************
* Function: get_com_mode
* Description: 读取通信模式(BT优先/VCOM优先)
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
// COM_MODE_E get_com_mode(void)
// {
// 	return com_mode;
// }

/*************************************************
* Function: get_com_device
* Description: 当前的通信设备(BT/VCOM)
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
rt_device_t get_com_device(void)
{
	rt_device_t device = RT_NULL;
	
	switch (com_mode)
	{
		case COM_MODE_VCOM:
		{
			device = vcom_dev;
			break;
		}
		case COM_MODE_BT:
		{
		//	device = bt_dev;
			break;
		}
		default:
			break;
	}
	
	return device;
}

/*************************************************
* Function: _CMD_Response
* Description: 命令处理结果应答
* Author: Reic
* Returns:
* Parameter:
* History:
*************************************************/
/*************************************************
* Function: com_send_data
* Description: 通过配置选择的通道(BT/VCOM)尝试输出数据
* Author: wangk
* Returns: 返回实际输出的字节数
* Parameter:
* History:
*************************************************/
uint32_t com_send_data(const uint8_t* data, uint32_t len)
{
	uint32_t sent_len = 0;
	
	switch (com_mode)
	{
		case COM_MODE_VCOM:
		{
			/* 优先尝试VCOM发送 */
			sent_len = vcom_send_data(data, len);
			if (0 == sent_len)
			{ // 发送失败
				/* 再尝试BT发送 */
			//	sent_len = bt_send_data(data, len);
			}
			break;
		}
		case COM_MODE_BT:
		{
			/* 优先尝试BT发送 */
		//	sent_len = bt_send_data(data, len);
			if (0 == sent_len)
			{ // 发送失败
				/* 再尝试VCOM发送 */
				sent_len = vcom_send_data(data, len);
			}
			break;
		}
		default:
			break;
	}
	
	return sent_len;
}




/*************************************************
* Function: vcom_send_data
* Description: 通过VCOM输出数据
* Author: wangk
* Returns: 返回实际输出的字节数
* Parameter:
* History:
*************************************************/
uint32_t vcom_send_data(const uint8_t* data, uint32_t len)
{	
	if (RT_NULL == vcom_dev)
	{
		return 0;
	}
	
	/* 数据插入发送缓冲队列 */
	uint32_t u32SendLen = CycleQueue_Insert(&s_tVcomSendQ, data, len);
	
	if (s_bVcomSending)
	{ // 正在发送状态
		/* 将会自动发送缓冲区中的数据 */
	}
	else
	{ // 已停止发送
		/* 启动发送 */
		uint8_t* pu8SendBuf = s_pu8VcomSendBuf;
		uint32_t u32DataLen = CycleQueue_Delete(&s_tVcomSendQ, pu8SendBuf, VCOM_SEND_BUF_SIZE, NULL);
		if (u32DataLen > 0)
		{
			/* 设置正在发送状态 */
			s_bVcomSending = true;
			/* 请求发送缓冲区中的数据 */
			rt_device_write(vcom_dev, 0, pu8SendBuf, (rt_size_t)u32DataLen);
		}
	}
	
	return u32SendLen;
}

/*************************************************
* Function: main
* Description: main入口函数
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
int main(void)
{
	int main_ret = 0;
	rt_err_t ret = RT_EOK;
	rt_kprintf("BUILD=%s\r\n",BUILD);
	
	/* 创建Vcom发送循环队列 */
	CycleQueue_Create(&s_tVcomSendQ, s_pu8VcomSendQueBuf, sizeof(s_pu8VcomSendQueBuf));
	
	/* 初始化CMD模块 */
	cmd_init();
   
	
	/* 创建EVENT */
	app_event = rt_event_create("app_event", RT_IPC_FLAG_FIFO);
	if (RT_NULL == app_event)
	{
		APP_TRACE("create app event failed!\r\n");
		main_ret = -RT_ERROR;
		goto _END;
	}
	
	/* 打开VCOM设备 */
	vcom_dev = rt_device_find(VCOM_DEVICE_NAME);
	if (RT_NULL == vcom_dev)
	{
		APP_TRACE("main() call rt_device_find(%s) failed!\r\n", VCOM_DEVICE_NAME);
		//main_ret = -RT_ERROR;
		//goto _END;
	}
	else
    {
        ret = rt_device_open(vcom_dev, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_DMA_TX);
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
		ret = rt_event_recv(app_event, (VCOM_EVENT_RX_IND | VCOM_EVENT_TX_DONE ),
						  (RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR),
						  RT_WAITING_FOREVER, &event_recved);
		if (RT_EOK != ret)
		{
			APP_TRACE("recv event failed(%d)!\r\n", ret);
			main_ret = ret;
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
				rt_size_t read_len = rt_device_read(vcom_dev, 0, vcom_data_buf, sizeof(vcom_data_buf));
				if (read_len > 0)
				{ // 收取到数据
					//APP_TRACE("vcom read_len=%d\r\n", read_len);
					
					///* 数据输入到CMD模块 */
					//CMD_OnRecvData(vcom_data_buf, (uint32_t)read_len);
					cmd_parsing((char *)vcom_data_buf);
					rt_memset(vcom_data_buf, 0, sizeof(vcom_data_buf));
				}
				else
				{ // 数据已收取完毕
					break;
				}

				
		
			}
		}
		
		if (event_recved & VCOM_EVENT_TX_DONE)
		{ // VCOM数据已发送完毕
			/* 读取数据到Vcom发送缓冲区 */
			uint8_t* pu8SendBuf = s_pu8VcomSendBuf;
			uint32_t u32DataLen = CycleQueue_Delete(&s_tVcomSendQ, pu8SendBuf, VCOM_SEND_BUF_SIZE, NULL);
			if (u32DataLen > 0)
			{ // 有数据需要发送
                if (vcom_dev == RT_NULL)
                {
                    continue;
                }
				/* 请求发送缓冲区中的数据 */
				rt_device_write(vcom_dev, 0, pu8SendBuf, (rt_size_t)u32DataLen);
			}
			else
			{ // 队列中的数据已发送完毕
				/* 清除正在发送状态 */
				s_bVcomSending = false;
			}
		}
	}
		
	
_END:
	/* 释放资源 */
	if (RT_NULL != app_event)
	{
		rt_event_delete(app_event);
		app_event = RT_NULL;
	}
	if (RT_NULL != vcom_dev)
	{
		rt_device_close(vcom_dev);
		vcom_dev = RT_NULL;
	}

    return main_ret;
}

/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif
// End of main.cpp
