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
#include "cmd.h"
#include "cyclequeue.h"
#include "common.h"
//#include "at.h"
extern "C"
{
  //  #include "fal.h"
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
#define BT_EVENT_RX_IND 0x00000008
#define BT_EVENT_TX_DONE 0x00000010
#define SENSOR_AUTO_ZERO_DONE 0x00000020
#define SWITCH_INT_EVENT 0x00000040

/* Vcom发送缓冲区长度 */
#define VCOM_SEND_BUF_SIZE (1024)
/* BT发送缓冲区长度 */
#define BT_SEND_BUF_SIZE (1024)

/* Vcom设备名 */
#define VCOM_DEVICE_NAME "vcom"
/* BT串口设备名 */
#define BT_UART_NAME "uart3"
/* defined the BT_TRANS pin: PD10 */
#define BT_TRANS_PIN GET_PIN(D, 10)
/* defined the BT_DISCON pin: PD11 */
#define BT_DISCON_PIN GET_PIN(D, 11)
/* defined the BT_RESET pin: PD12 */
#define BT_RESET_PIN GET_PIN(D, 12)
/* defined the BT_STATUS pin: PD13 */
#define BT_STATUS_PIN GET_PIN(D, 13)
/* defined the BT_LIGHT pin: PD14 */
#define BT_LIGHT_PIN GET_PIN(D, 14)
/* defined the BT_POWER pin: PD15 */
#define BT_POWER_PIN GET_PIN(D, 15)


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

/* BT串口设备 */
static rt_device_t bt_dev = RT_NULL;

/* BT接收缓冲区 */
static uint8_t bt_data_buf[128] = {0};

/* BT数据发送队列 */
static CycleQueue_T s_tBTSendQ = {NULL};

/* BT发送队列缓冲区 */
static uint8_t s_pu8BTSendQueBuf[BT_SEND_BUF_SIZE * 4] = {0};

/* BT发送缓冲区 */
static uint8_t s_pu8BTSendBuf[BT_SEND_BUF_SIZE] = {0};

/* BT是否正在发送状态 */
static bool s_bBTSending = false;

/* 通信模式 */
static COM_MODE_E com_mode = COM_MODE_VCOM; // 默认VCOM优先


/*----------------------------------------------------------------------------*
**                             Extern Function                                *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Local Function                                 *
**----------------------------------------------------------------------------*/
/* SWITCH_INT interupt service */
static void switch_int_isr(void *args)
{
	/* 通知主线程收到SWITCH_INT_EVENT信号 */
	rt_event_send(app_event, SWITCH_INT_EVENT);
}
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

/*************************************************
* Function: bt_rx_ind
* Description: BT数据收取回调函数
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
static rt_err_t bt_rx_ind(rt_device_t dev, rt_size_t size)
{
	if (size > 0)
	{
		rt_event_send(app_event, BT_EVENT_RX_IND);
	}
	
	return RT_EOK;
}

/*************************************************
* Function: bt_tx_done
* Description: BT数据发送完成回调函数
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
static rt_err_t bt_tx_done(rt_device_t dev, void *buffer)
{
	rt_event_send(app_event, BT_EVENT_TX_DONE);
	
	return RT_EOK;
}

#if defined(BSP_USING_RSCDRRM020NDSE3)
/*************************************************
* Function: send_wave
* Description: 发送波形数据帧
* Author: wangk
* Returns: 返回实际发送的字节数
* Parameter:
* History:
*************************************************/
static rt_size_t send_wave(float val)
{
	//APP_TRACE("send_wave() val=%f\r\n", val);
	
	char buf[16] = {0};
	
	char len = ws_point_float(buf, CH1, val);
	
	/* 通过配置选择的通道(BT/VCOM)尝试输出数据 */
	uint32_t sent_len = com_send_data((const uint8_t*)buf, (uint32_t)len);
	
	return (rt_size_t)sent_len;
}
#elif defined(BSP_USING_AD7730)
/*************************************************
* Function: send_wave
* Description: 发送波形数据帧
* Author: wangk
* Returns: 返回实际发送的字节数
* Parameter:
* History:
*************************************************/
static rt_size_t send_wave(int32_t val)
{
	//APP_TRACE("send_wave() val=%d\r\n", val);
	
	char buf[16] = {0};
	
	char len = ws_point_int32(buf, CH1, val);
	
	/* 通过配置选择的通道(BT/VCOM)尝试输出数据 */
	uint32_t sent_len = com_send_data((const uint8_t*)buf, (uint32_t)len);
	
	return (rt_size_t)sent_len;
}
#endif

#if defined(BSP_USING_RSCDRRM020NDSE3)
/*************************************************
* Function: on_auto_zero_completed
* Description: 自动归零完成回调函数
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
static void on_auto_zero_completed(void)
{
	rt_event_send(app_event, SENSOR_AUTO_ZERO_DONE);
}
#endif

/*----------------------------------------------------------------------------*
**                             Public Function                                *
**----------------------------------------------------------------------------*/

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
				sent_len = bt_send_data(data, len);
			}
			break;
		}
		case COM_MODE_BT:
		{
			/* 优先尝试BT发送 */
			sent_len = bt_send_data(data, len);
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
COM_MODE_E get_com_mode(void)
{
	return com_mode;
}

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
			device = bt_dev;
			break;
		}
		default:
			break;
	}
	
	return device;
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
* Function: bt_send_data
* Description: 通过BT输出数据
* Author: wangk
* Returns: 返回实际输出的字节数
* Parameter:
* History:
*************************************************/
uint32_t bt_send_data(const uint8_t* data, uint32_t len)
{
//	if (!is_ble_connect())
//	{ // BT Disconnected
//		return 0;
//	}
	
	if (RT_NULL == bt_dev)
	{
		return 0;
	}
	
	/* 数据插入发送缓冲队列 */
	uint32_t u32SendLen = CycleQueue_Insert(&s_tBTSendQ, data, len);
	
	if (s_bBTSending)
	{ // 正在发送状态
		/* 将会自动发送缓冲区中的数据 */
	}
	else
	{ // 已停止发送
		/* 启动发送 */
		uint8_t* pu8SendBuf = s_pu8BTSendBuf;
		uint32_t u32DataLen = CycleQueue_Delete(&s_tBTSendQ, pu8SendBuf, BT_SEND_BUF_SIZE, NULL);
		if (u32DataLen > 0)
		{
			/* 设置正在发送状态 */
			s_bBTSending = true;
			/* 请求发送缓冲区中的数据 */
			rt_device_write(bt_dev, 0, pu8SendBuf, (rt_size_t)u32DataLen);
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
	
	
    /* 初始化FAL库 */
	//fal_init();
	
	/* 创建Vcom发送循环队列 */
	CycleQueue_Create(&s_tVcomSendQ, s_pu8VcomSendQueBuf, sizeof(s_pu8VcomSendQueBuf));
	/* 创建BT发送循环队列 */
	CycleQueue_Create(&s_tBTSendQ, s_pu8BTSendQueBuf, sizeof(s_pu8BTSendQueBuf));
	
	/* 初始化CMD模块 */
	CMD_Init();
    
	/* set BT_POWER pin mode to output */
    rt_pin_mode(BT_POWER_PIN, PIN_MODE_OUTPUT);
	rt_pin_write(BT_POWER_PIN, PIN_LOW);
	
	/* set BT_TRANS pin mode to output */
    rt_pin_mode(BT_TRANS_PIN, PIN_MODE_OUTPUT);
	rt_pin_write(BT_TRANS_PIN, PIN_LOW); // L=透传模式,H=指令模式
	
	/* set BT_STATUS pin mode to input */
    rt_pin_mode(BT_STATUS_PIN, PIN_MODE_INPUT); // L=Disconnected,H=Connected
	
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
	
	/* 开启蓝牙模块电源 */
	rt_pin_write(BT_POWER_PIN, PIN_HIGH);
	
	/* 打开BT串口设备 */
	bt_dev = rt_device_find(BT_UART_NAME);
	if (RT_NULL == bt_dev)
	{
		APP_TRACE("main() call rt_device_find(%s) failed!\r\n", BT_UART_NAME);
		//main_ret = -RT_ERROR;
		//goto _END;
	}
	else
    {
        ret = rt_device_open(bt_dev, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_DMA_TX);
        if (RT_EOK != ret)
        {
            APP_TRACE("main() call rt_device_open(bt_dev) failed, error(%d)!\r\n", ret);
            //main_ret = ret;
            //goto _END;
        }
        else
        {
            ret = rt_device_set_rx_indicate(bt_dev, bt_rx_ind);
            if (RT_EOK != ret)
            {
                APP_TRACE("main() call rt_device_set_rx_indicate(bt_dev) failed, error(%d)!\r\n", ret);
                //main_ret = ret;
                //goto _END;
            }
            
            ret = rt_device_set_tx_complete(bt_dev, bt_tx_done);
            if (RT_EOK != ret)
            {
                APP_TRACE("main() call rt_device_set_tx_complete(bt_dev) failed, error(%d)!\r\n", ret);
                //main_ret = ret;
                //goto _END;
            }
        }
    }
	/* 进入事件循环 */
    while (1)
	{
		
		rt_uint32_t event_recved = 0;
		ret = rt_event_recv(app_event, (SENSOR_EVENT_RX_IND | VCOM_EVENT_RX_IND | VCOM_EVENT_TX_DONE | 
                          BT_EVENT_RX_IND | BT_EVENT_TX_DONE | SENSOR_AUTO_ZERO_DONE | SWITCH_INT_EVENT),
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
					
					/* 数据输入到CMD模块 */
					CMD_OnRecvData(vcom_data_buf, (uint32_t)read_len);
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
		
		if (event_recved & BT_EVENT_RX_IND)
		{ // 收到BT数据
            if (bt_dev == RT_NULL)
            {
                continue;
            }
            
			/* 收取所有数据 */
			while (1)
			{
				rt_size_t read_len = rt_device_read(bt_dev, 0, bt_data_buf, sizeof(bt_data_buf));
				if (read_len > 0)
				{ // 收取到数据
					//APP_TRACE("bt read_len=%d\r\n", read_len);
					
					/* 数据输入到CMD模块 */
					CMD_OnRecvData(bt_data_buf, (uint32_t)read_len);
				}
				else
				{ // 数据已收取完毕
					break;
				}
			}
		}
		
		if (event_recved & BT_EVENT_TX_DONE)
		{ // BT数据已发送完毕
			/* 读取数据到BT发送缓冲区 */
			uint8_t* pu8SendBuf = s_pu8BTSendBuf;
			uint32_t u32DataLen = CycleQueue_Delete(&s_tBTSendQ, pu8SendBuf, BT_SEND_BUF_SIZE, NULL);
			if (u32DataLen > 0)
			{ // 有数据需要发送
                if (bt_dev == RT_NULL)
                {
                    continue;
                }
            
				/* 请求发送缓冲区中的数据 */
				rt_device_write(bt_dev, 0, pu8SendBuf, (rt_size_t)u32DataLen);
			}
			else
			{ // 队列中的数据已发送完毕
				/* 清除正在发送状态 */
				s_bBTSending = false;
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
	if (RT_NULL != bt_dev)
	{
		rt_device_close(bt_dev);
		bt_dev = RT_NULL;
	}
	
    return main_ret;
}

/**
 * Function    ota_app_vtor_reconfig
 * Description Set Vector Table base location to the start addr of app(RT_APP_PART_ADDR).
*/
//static int ota_app_vtor_reconfig(void)
//{
//	#define NVIC_VTOR_MASK    0x3FFFFF80
//	/* Set the Vector Table base location by user application firmware definition */
//	SCB->VTOR = RT_APP_PART_ADDR & NVIC_VTOR_MASK;
//	
//	return 0;
//}
//INIT_BOARD_EXPORT(ota_app_vtor_reconfig);

/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif
// End of main.cpp
