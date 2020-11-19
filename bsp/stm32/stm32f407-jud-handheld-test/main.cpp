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
#include "sendwave.h"
#include "app.h"
#include "cmd.h"
#include "cyclequeue.h"
#include "at.h"
#include "sensor.h"
extern "C"
{
    #include "fal.h"
}
#include "oled_gui.h"

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

/* 电量测量ADC */
#define BAT_LEVEL_ADC_NAME "adc1"
#define BAT_LEVEL_ADC_CHANNEL 1

/* defined the CHARGE_S pin: PC8 */
#define CHARGE_S_PIN GET_PIN(C, 8)
/* defined the CHARGE_D pin: PC7 */
#define CHARGE_D_PIN GET_PIN(C, 7)

/* defined the SWITCH_INT pin: PA8 */
#define SWITCH_INT_PIN GET_PIN(A, 8)
/* defined the SWITCH_KILL pin: PC9 */
#define SWITCH_KILL_PIN GET_PIN(C, 9)

/* defined the ADC_VIN_LI pin: PA1 */
#define ADC_VIN_LI_PIN GET_PIN(A, 1)

/* defined the BME280_SDO pin: PB5 */
#define BME280_SDO_PIN GET_PIN(B, 5)

/* defined the LIGHT_B pin: PE9 */
#define LIGHT_B_PIN GET_PIN(E, 9)
/* defined the LIGHT_G pin: PE11 */
#define LIGHT_G_PIN GET_PIN(E, 11)
/* defined the LIGHT_R pin: PE13 */
#define LIGHT_R_PIN GET_PIN(E, 13)

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
	
#define OLED_SPI_PIN_RES       GET_PIN(A, 4)  // PA4
#define OLED_SPI_PIN_DC        GET_PIN(A, 6)  // PA6
#define OLED_SPI_PIN_CS        GET_PIN(A, 3)  // PA3

// In u8x8.h #define U8X8_USE_PINS 
#define U8G2_PIN_UP            GET_PIN(E, 2)      // PE2(KEY3)
#define U8G2_PIN_DOWN          GET_PIN(E, 3)      // PE3(KEY2)
#define U8G2_PIN_LEFT          U8X8_PIN_NONE
#define U8G2_PIN_RIGHT         GET_PIN(E, 4)      // PE4(KEY1)
#define U8G2_PIN_SELECT        GET_PIN(E, 5)      // PE5(KEY0)
#define U8G2_PIN_HOME          U8X8_PIN_NONE

/*----------------------------------------------------------------------------*
**                             Data Structures                                *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Local Vars                                     *
**----------------------------------------------------------------------------*/
/* event for application */
static rt_event_t app_event = RT_NULL;

/* BME280传感器设备 */
static rt_device_t temp_bme280_dev = RT_NULL;
static rt_device_t humi_bme280_dev = RT_NULL;
static rt_device_t baro_bme280_dev = RT_NULL;

/* SENSOR设备 */
static rt_device_t sensor_dev = RT_NULL;

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

/* 校准完成回调函数 */
static CAL_CPL_FUNC s_pfnCalCompleted = NULL;

/* 是否已启动ADC采集 */
static bool adc_started = false;

/* 通信模式 */
static COM_MODE_E com_mode = COM_MODE_VCOM; // 默认VCOM优先

/* 电量测量ADC设备 */
static rt_adc_device_t bat_level_adc_dev = RT_NULL;

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
* Function: bme280_init
* Description: 初始化bme280
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
static bool bme280_init(void)
{
	APP_TRACE("bme280_init()\r\n");
    
    /* 
        Connecting SDO to GND results in slave address 1110110 (0x76); 
        connection it to VDDIO results in slave address 1110111 (0x77)
    */
    rt_pin_mode(BME280_SDO_PIN, PIN_MODE_OUTPUT);
	rt_pin_write(BME280_SDO_PIN, PIN_LOW);
	
	/* Temperature */
	temp_bme280_dev = rt_device_find("temp_bme280");
	if (RT_NULL == temp_bme280_dev)
	{
		APP_TRACE("bme280_init() call rt_device_find(temp_bme280) failed!\r\n");
		return false;
	}
	rt_err_t ret = rt_device_open(temp_bme280_dev, RT_DEVICE_FLAG_RDONLY);
	if (RT_EOK != ret)
	{
		APP_TRACE("bme280_init() call rt_device_open(temp_bme280) failed!\r\n");
		return false;
	}
	
	/* Relative Humidity */
	humi_bme280_dev = rt_device_find("humi_bme280");
	if (RT_NULL == humi_bme280_dev)
	{
		APP_TRACE("bme280_init() call rt_device_find(humi_bme280) failed!\r\n");
		return false;
	}
	ret = rt_device_open(humi_bme280_dev, RT_DEVICE_FLAG_RDONLY);
	if (RT_EOK != ret)
	{
		APP_TRACE("bme280_init() call rt_device_open(humi_bme280) failed!\r\n");
		return false;
	}
	
	/* Barometer */
	baro_bme280_dev = rt_device_find("baro_bme280");
	if (RT_NULL == baro_bme280_dev)
	{
		APP_TRACE("bme280_init() call rt_device_find(baro_bme280) failed!\r\n");
		return false;
	}
	ret = rt_device_open(baro_bme280_dev, RT_DEVICE_FLAG_RDONLY);
	if (RT_EOK != ret)
	{
		APP_TRACE("bme280_init() call rt_device_open(baro_bme280) failed!\r\n");
		return false;
	}
	
	return true;
}

/*************************************************
* Function: bme280_deinit
* Description: bme280_init的相反操作
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
static void bme280_deinit(void)
{
	APP_TRACE("bme280_deinit()\r\n");
	
	/* Temperature */
	if (RT_NULL != temp_bme280_dev)
	{
		rt_device_close(temp_bme280_dev);
		temp_bme280_dev = RT_NULL;
	}
	
	/* Relative Humidity */
	if (RT_NULL != humi_bme280_dev)
	{
		rt_device_close(humi_bme280_dev);
		humi_bme280_dev = RT_NULL;
	}
	
	/* Barometer */
	if (RT_NULL != baro_bme280_dev)
	{
		rt_device_close(baro_bme280_dev);
		baro_bme280_dev = RT_NULL;
	}
}
	
/*************************************************
* Function: sensor_rx_ind
* Description: AD7730数据收取回调函数
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
static rt_err_t sensor_rx_ind(rt_device_t dev, rt_size_t size)
{
	if (size > 0)
	{
		rt_event_send(app_event, SENSOR_EVENT_RX_IND);
	}
	
	return RT_EOK;
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
* Function: app_power_off
* Description: 关机
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
void app_power_off(void)
{
    APP_TRACE("app_power_off()\r\n");
    
    /* 拉低SWITCH_KILL关机 */
    rt_pin_write(SWITCH_KILL_PIN, PIN_LOW);
}

/*************************************************
* Function: is_in_changing
* Description: 当前是否正在充电状态
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
bool is_in_changing(void)
{
    //APP_TRACE("is_in_changing()\r\n");
    
    return (PIN_LOW == rt_pin_read(CHARGE_S_PIN));
}

/*************************************************
* Function: is_changer_connect
* Description: 当前是否外接了充电电源
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
bool is_changer_connect(void)
{
    //APP_TRACE("is_changer_connect()\r\n");
    
    return (PIN_LOW == rt_pin_read(CHARGE_D_PIN));
}

/*************************************************
* Function: get_battery_level
* Description: 取得电池电量(百分比)
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
uint8_t get_battery_level(void)
{
    rt_uint32_t adc_value = rt_adc_read(bat_level_adc_dev, BAT_LEVEL_ADC_CHANNEL);
    /*
		VCHANNELx = VREF * ADC_DATAx / FULL_SCALE
		对于12bit采样,FULL_SCALE=2^12-1=4095
	*/

    /* 
        分压系数: (1M + 1M) / 1M = 2
        可测电压范围: 0 ~ 6600 (mv)
    */
    // (2 * 3300 * u32AdcValue) / 4095; 公约数15
    rt_uint32_t vol_mv = (uint32_t)(((2 * 220 * 1000 * (uint64_t)adc_value) / 273) / 1000);
#if 0
    if (vol_mv >= 4160) // >= 4.16V
    {
        return 100;
    }
    else if (vol_mv >= 4150) // >= 4.15V
    {
        return 99;
    }
    else if (vol_mv >= 4140) // >= 4.14V
    {
        return 97;
    }
    else if (vol_mv >= 4120) // >= 4.12V
    {
        return 95;
    }
    else if (vol_mv >= 4100) // >= 4.10V
    {
        return 92;
    }
    else if (vol_mv >= 4080) // >= 4.08V
    {
        return 90;
    }
    else if (vol_mv >= 4050) // >= 4.05V
    {
        return 87;
    }
    else if (vol_mv >= 4030) // >= 4.03V
    {
        return 85;
    }
    else if (vol_mv >= 3970) // >= 3.97V
    {
        return 80;
    }
    else if (vol_mv >= 3930) // >= 3.93V
    {
        return 75;
    }
    else if (vol_mv >= 3900) // >= 3.90V
    {
        return 70;
    }
    else if (vol_mv >= 3870) // >= 3.87V
    {
        return 65;
    }
    else if (vol_mv >= 3840) // >= 3.84V
    {
        return 60;
    }
    else if (vol_mv >= 3810) // >= 3.81V
    {
        return 55;
    }
    else if (vol_mv >= 3790) // >= 3.79V
    {
        return 50;
    }
    else if (vol_mv >= 3770) // >= 3.77V
    {
        return 45;
    }
    else if (vol_mv >= 3760) // >= 3.76V
    {
        return 40;
    }
    else if (vol_mv >= 3740) // >= 3.74V
    {
        return 35;
    }
    else if (vol_mv >= 3730) // >= 3.73V
    {
        return 30;
    }
    else if (vol_mv >= 3720) // >= 3.72V
    {
        return 25;
    }
    else if (vol_mv >= 3710) // >= 3.71V
    {
        return 20;
    }
    else if (vol_mv >= 3690) // >= 3.69V
    {
        return 15;
    }
    else if (vol_mv >= 3660) // >= 3.66V
    {
        return 12;
    }
    else if (vol_mv >= 3650) // >= 3.65V
    {
        return 10;
    }
    else if (vol_mv >= 3640) // >= 3.64V
    {
        return 8;
    }
    else if (vol_mv >= 3630) // >= 3.63V
    {
        return 5;
    }
    else if (vol_mv >= 3610) // >= 3.61V
    {
        return 3;
    }
    else if (vol_mv >= 3590) // >= 3.59V
    {
        return 1;
    }
    else if (vol_mv >= 3580) // >= 3.58V
    {
        return 0;
    }
#else
    if (vol_mv >= 4200) // >= 4.20V
    {
        return 100;
    }
    else if (vol_mv >= 4080) // >= 4.08V
    {
        return 90;
    }
    else if (vol_mv >= 4000) // >= 4.00V
    {
        return 80;
    }
    else if (vol_mv >= 3930) // >= 3.93V
    {
        return 70;
    }
    else if (vol_mv >= 3870) // >= 3.87V
    {
        return 60;
    }
    else if (vol_mv >= 3820) // >= 3.82V
    {
        return 50;
    }
    else if (vol_mv >= 3790) // >= 3.79V
    {
        return 40;
    }
    else if (vol_mv >= 3770) // >= 3.77V
    {
        return 30;
    }
    else if (vol_mv >= 3730) // >= 3.73V
    {
        return 20;
    }
    else if (vol_mv >= 3700) // >= 3.70V
    {
        return 15;
    }
    else if (vol_mv >= 3680) // >= 3.68V
    {
        return 10;
    }
    else if (vol_mv >= 3500) // >= 3.50V
    {
        return 5;
    }
    else if (vol_mv >= 2500) // >= 2.5V
    {
        return 0;
    }
#endif
    return 0;
}

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
* Function: is_ble_connect
* Description: BLE是否已建立连接
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
bool is_ble_connect(void)
{
    return (PIN_HIGH == rt_pin_read(BT_STATUS_PIN));
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
	if (!is_ble_connect())
	{ // BT Disconnected
		return 0;
	}
	
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
* Function: adc_calibration
* Description: 执行ADC通道校准
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
bool adc_calibration(int adc_channel, CAL_CPL_FUNC pfnCalCompleted)
{
	APP_TRACE("adc_calibration() adc_channel=%d\r\n", adc_channel);
    
    if (sensor_dev == RT_NULL)
    {
        APP_TRACE("adc_calibration() failed, sensor_dev is null!\r\n");
        return false;
    }

#if defined(BSP_USING_RSCDRRM020NDSE3)
	if (0 != adc_channel)
	{
		APP_TRACE("adc_calibration() failed, invalid channel(%d)!\r\n", adc_channel);
		return false;
	}
	
	s_pfnCalCompleted = pfnCalCompleted;
	
	rt_err_t ret = rt_device_control(sensor_dev, RSCDRRM020NDSE3_AUTO_ZERO, (void *)on_auto_zero_completed);
	if (RT_EOK != ret)
	{
		APP_TRACE("adc_calibration() failed, rt_device_control(RSCDRRM020NDSE3_AUTO_ZERO) error(%d)!\r\n", ret);
		s_pfnCalCompleted = NULL;
		return false;
	}
#elif defined(BSP_USING_AD7730)
	if ((adc_channel < 0)
		|| (adc_channel >= 3))
	{
		APP_TRACE("adc_calibration() failed, invalid channel(%d)!\r\n", adc_channel);
		return false;
	}
	
	rt_err_t ret = rt_device_control(sensor_dev, AD7730_DO_CALIBRATION, (void*)adc_channel);
	if (RT_EOK != ret)
	{
		APP_TRACE("adc_calibration() failed, rt_device_control(AD7730_DO_CALIBRATION) error(%d)!\r\n", ret);
		return false;
	}
	if (pfnCalCompleted)
	{
		pfnCalCompleted();
	}
#endif
	
	return true;
}

/*************************************************
* Function: adc_get_freq
* Description: 读取ADC采样率
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
uint32_t adc_get_freq(void)
{
	APP_TRACE("adc_get_freq()\r\n");
    
    if (sensor_dev == RT_NULL)
    {
        APP_TRACE("adc_get_freq() failed, sensor_dev is null!\r\n");
        return 0xFFFFFFFF;
    }

	uint32_t u32FreqIndex = 0xFFFFFFFF;
	
#if defined(BSP_USING_RSCDRRM020NDSE3)
	rt_err_t ret = rt_device_control(sensor_dev, RSCDRRM020NDSE3_GET_FREQ, &u32FreqIndex);
	if (RT_EOK != ret)
	{
		APP_TRACE("adc_get_freq() failed, rt_device_control(RSCDRRM020NDSE3_GET_FREQ) error(%d)!\r\n", ret);
		return 0xFFFFFFFF;
	}
#endif
	
	return u32FreqIndex;
}

/*************************************************
* Function: adc_set_freq
* Description: 设置ADC采样率
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
bool adc_set_freq(uint32_t u32FreqIndex)
{
	APP_TRACE("adc_set_freq() u32FreqIndex=%u\r\n", u32FreqIndex);
    
    if (sensor_dev == RT_NULL)
    {
        APP_TRACE("adc_set_freq() failed, sensor_dev is null!\r\n");
        return false;
    }

	bool bRet = false;
	
#if defined(BSP_USING_RSCDRRM020NDSE3)
	rt_err_t ret = rt_device_control(sensor_dev, RSCDRRM020NDSE3_SET_FREQ, (void*)u32FreqIndex);
	if (RT_EOK != ret)
	{
		APP_TRACE("adc_set_freq() failed, rt_device_control(RSCDRRM020NDSE3_SET_FREQ) error(%d)!\r\n", ret);
		return false;
	}
	bRet = true;
#endif
	
	return bRet;
}

/*************************************************
* Function: adc_get_temperature
* Description: 读取ADC温度
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
float adc_get_temperature(void)
{
	APP_TRACE("adc_get_temperature()\r\n");
    
    if (sensor_dev == RT_NULL)
    {
        APP_TRACE("adc_get_temperature() failed, sensor_dev is null!\r\n");
        return 0.0f;
    }

	float fTemperature = 0.0f;
	
#if defined(BSP_USING_RSCDRRM020NDSE3)
	rt_err_t ret = rt_device_control(sensor_dev, RSCDRRM020NDSE3_GET_TEMP, &fTemperature);
	if (RT_EOK != ret)
	{
		APP_TRACE("adc_get_temperature() failed, rt_device_control(RSCDRRM020NDSE3_GET_TEMP) error(%d)!\r\n", ret);
		return 0.0f;
	}
#endif
	
	return fTemperature;
}

/*************************************************
* Function: adc_start
* Description: 启动ADC采集
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
bool adc_start(int adc_channel)
{
	APP_TRACE("adc_start() adc_channel=%d\r\n", adc_channel);
    
    if (sensor_dev == RT_NULL)
    {
        APP_TRACE("adc_start() failed, sensor_dev is null!\r\n");
        return false;
    }
	
#if defined(BSP_USING_RSCDRRM020NDSE3)
	if (0 != adc_channel)
	{
		APP_TRACE("adc_start() failed, invalid channel(%d)!\r\n", adc_channel);
		return false;
	}
	
	/* 启动RSCDRRM020NDSE3 */
	rt_err_t ret = rt_device_control(sensor_dev, RSCDRRM020NDSE3_START, RT_NULL);
	if (RT_EOK != ret)
	{
		APP_TRACE("adc_start() failed, rt_device_control(RSCDRRM020NDSE3_START) error(%d)!\r\n", ret);
		return false;
	}
#elif defined(BSP_USING_AD7730)
	if ((adc_channel < 0)
		|| (adc_channel >= 3))
	{
		APP_TRACE("adc_start() failed, invalid channel(%d)!\r\n", adc_channel);
		return false;
	}
	
#if 0
	/* 执行ADC校准 */
	rt_err_t ret = rt_device_control(sensor_dev, AD7730_DO_CALIBRATION, (void*)adc_channel);
	if (RT_EOK != ret)
	{
		APP_TRACE("adc_start() failed, rt_device_control(AD7730_DO_CALIBRATION) error(%d)!\r\n", ret);
		return false;
	}
#else
	rt_err_t ret = RT_EOK;
#endif
	
	/* 启动AD7730连续读取 */
	ret = rt_device_control(sensor_dev, AD7730_START_CONT_READ, (void*)adc_channel);
	if (RT_EOK != ret)
	{
		APP_TRACE("adc_start() failed, rt_device_control(AD7730_START_CONT_READ) error(%d)!\r\n", ret);
		return false;
	}
#endif

    rt_pin_write(LIGHT_G_PIN, PIN_HIGH);
	
	/* 设置ADC采集已启动标志 */
	adc_started = true;
	
	return true;
}

/*************************************************
* Function: adc_stop
* Description: 停止ADC采集
* Author: wangk
* Returns: 
* Parameter:
* History:
*************************************************/
bool adc_stop(void)
{
	APP_TRACE("adc_stop()\r\n");
    
    if (sensor_dev == RT_NULL)
    {
        APP_TRACE("adc_stop() failed, sensor_dev is null!\r\n");
        return false;
    }
	
#if defined(BSP_USING_RSCDRRM020NDSE3)
	/* 停止RSCDRRM020NDSE3 */
	rt_err_t ret = rt_device_control(sensor_dev, RSCDRRM020NDSE3_STOP, RT_NULL);
	if (RT_EOK != ret)
	{
		APP_TRACE("adc_stop() failed, rt_device_control(RSCDRRM020NDSE3_STOP) error(%d)!\r\n", ret);
		return false;
	}
#elif defined(BSP_USING_AD7730)
	/* 停止AD7730连续读取 */
	rt_err_t ret = rt_device_control(sensor_dev, AD7730_STOP_CONT_READ, RT_NULL);
	if (RT_EOK != ret)
	{
		APP_TRACE("adc_stop() failed, rt_device_control(AD7730_STOP_CONT_READ) error(%d)!\r\n", ret);
		return false;
	}
#endif
	
    rt_pin_write(LIGHT_G_PIN, PIN_LOW);
    
	/* 清除ADC采集已启动标志 */
	adc_started = false;
	
	return true;
}

/*************************************************
* Function: bme280_get_temp
* Description: 通过bme280读取温度
* Author: wangk
* Returns: 温度单位,摄氏度
* Parameter:
* History:
*************************************************/
float bme280_get_temp(void)
{
    if (temp_bme280_dev == RT_NULL)
    {
        APP_TRACE("bme280_get_temp() failed, temp_bme280_dev is null!\r\n");
        return 0.0f;
    }
    
	struct rt_sensor_data sensor_data = {0};
	rt_size_t read_len = rt_device_read(temp_bme280_dev, 0, &sensor_data, 1);
	if (1 != read_len)
	{
		return 0.0f;
	}
	
	return (float)(sensor_data.data.temp) / 10.0f;
}

/*************************************************
* Function: bme280_get_humi
* Description: 通过bme280读取相对湿度
* Author: wangk
* Returns: 相对湿度单位,百分比
* Parameter:
* History:
*************************************************/
float bme280_get_humi(void)
{
    if (humi_bme280_dev == RT_NULL)
    {
        APP_TRACE("bme280_get_humi() failed, humi_bme280_dev is null!\r\n");
        return 0.0f;
    }
    
	struct rt_sensor_data sensor_data = {0};
	rt_size_t read_len = rt_device_read(humi_bme280_dev, 0, &sensor_data, 1);
	if (1 != read_len)
	{
		return 0.0f;
	}
	
	return (float)(sensor_data.data.humi) / 10.0f;
}

/*************************************************
* Function: bme280_get_baro
* Description: 通过bme280读取大气压
* Author: wangk
* Returns: 大气压单位,帕
* Parameter:
* History:
*************************************************/
float bme280_get_baro(void)
{
    if (baro_bme280_dev == RT_NULL)
    {
        APP_TRACE("bme280_get_baro() failed, baro_bme280_dev is null!\r\n");
        return 0.0f;
    }
    
	struct rt_sensor_data sensor_data = {0};
	rt_size_t read_len = rt_device_read(baro_bme280_dev, 0, &sensor_data, 1);
	if (1 != read_len)
	{
		return 0.0f;
	}
	
	return (float)(sensor_data.data.baro);
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
    
    /* 开机拉高SWITCH_KILL */
    rt_pin_mode(SWITCH_KILL_PIN, PIN_MODE_OUTPUT);
	rt_pin_write(SWITCH_KILL_PIN, PIN_HIGH);
    
    /* set SWITCH_INT pin mode to input(检测关机信号) */
    rt_pin_mode(SWITCH_INT_PIN, PIN_MODE_INPUT_PULLUP);
    /* 配置关机信中断检测 */
	ret = rt_pin_attach_irq(SWITCH_INT_PIN, PIN_IRQ_MODE_FALLING, switch_int_isr, RT_NULL);
	if (RT_EOK != ret)
	{
        APP_TRACE("call rt_pin_attach_irq(SWITCH_INT_PIN) failed, error(%d)!\r\n", ret);
		//main_ret = ret;
		//goto _END;
	}
    else
    {
        /* 使能关机中断检测 */
        ret = rt_pin_irq_enable(SWITCH_INT_PIN, PIN_IRQ_ENABLE);
        if (RT_EOK != ret)
        {
            APP_TRACE("call rt_pin_irq_enable(SWITCH_INT_PIN) failed, error(%d)!\r\n", ret);
            //main_ret = ret;
            //goto _END;
        }
    }
    
    /* set CHARGE_S pin mode to input(检测充电状态) */
    rt_pin_mode(CHARGE_S_PIN, PIN_MODE_INPUT_PULLUP);
    /* set CHARGE_D pin mode to input(检测充电电源状态) */
    rt_pin_mode(CHARGE_D_PIN, PIN_MODE_INPUT_PULLUP);
    
    /* set LIGHT_B/G/R pin mode to output */
    rt_pin_mode(LIGHT_B_PIN, PIN_MODE_OUTPUT);
	rt_pin_write(LIGHT_B_PIN, PIN_LOW);
    rt_pin_mode(LIGHT_G_PIN, PIN_MODE_OUTPUT);
	rt_pin_write(LIGHT_G_PIN, PIN_LOW);
    rt_pin_mode(LIGHT_R_PIN, PIN_MODE_OUTPUT);
	rt_pin_write(LIGHT_R_PIN, PIN_LOW);
	
    /* 初始化FAL库 */
	fal_init();
	
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
	
	/* 初始化BME280传感器 */
	{ // 消除编译警告
		bool init_ret = bme280_init();
		if (!init_ret)
		{
			APP_TRACE("call bme280_init() failed!\r\n");
            bme280_deinit();
			//main_ret = -RT_ERROR;
			//goto _END;
		}
	}
	
#if defined(BSP_USING_RSCDRRM020NDSE3)
	/* 打开AD7730设备 */
	sensor_dev = rt_device_find(RSCDRRM020NDSE3_DEVICE_NAME);
	if (RT_NULL == sensor_dev)
	{
		APP_TRACE("device %s not found!\r\n", RSCDRRM020NDSE3_DEVICE_NAME);
		//main_ret = -RT_ERROR;
		//goto _END;
	}
#elif defined(BSP_USING_AD7730)
	/* 打开AD7730设备 */
	sensor_dev = rt_device_find(AD7730_DEVICE_NAME);
	if (RT_NULL == sensor_dev)
	{
		APP_TRACE("device %s not found!\r\n", AD7730_DEVICE_NAME);
		//main_ret = -RT_ERROR;
		//goto _END;
	}
#endif
	
	if (RT_NULL != sensor_dev)
	{
		ret = rt_device_open(sensor_dev, RT_DEVICE_FLAG_RDONLY | RT_DEVICE_FLAG_INT_RX);
		if (RT_EOK != ret)
		{
			APP_TRACE("open device sensor failed(%d)!\r\n", ret);
			//main_ret = ret;
			//goto _END;
		}
		else
        {
            ret = rt_device_set_rx_indicate(sensor_dev, sensor_rx_ind);
            if (RT_EOK != ret)
            {
                APP_TRACE("set vcom rx indicate failed(%d)!\r\n", ret);
                //main_ret = ret;
                //goto _END;
            }
        }
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
    
    /* 初始化电量测量ADC设备 */
    bat_level_adc_dev = (rt_adc_device_t)rt_device_find(BAT_LEVEL_ADC_NAME);
    if (RT_NULL == bt_dev)
	{
		APP_TRACE("main() call rt_device_find(%s) failed!\r\n", BAT_LEVEL_ADC_NAME);
		//main_ret = -RT_ERROR;
		//goto _END;
	}
	else
    {
        ret = rt_adc_enable(bat_level_adc_dev, BAT_LEVEL_ADC_CHANNEL);
        if (RT_EOK != ret)
        {
            APP_TRACE("main() call rt_adc_enable(bat_level_adc_dev) failed, error(%d)!\r\n", ret);
            //main_ret = ret;
            //goto _END;
        }
    }
        
    /* 初始化并启动OLED GUI模块 */
    oled_gui_init();
    oled_gui_start();
    
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
		
        if (event_recved & SWITCH_INT_EVENT)
        {
            // TODO 保存数据
            /* 关机 */
            app_power_off();
        }
        
		if (event_recved & SENSOR_EVENT_RX_IND)
		{ // 收到SENSOR数据
            if (sensor_dev == RT_NULL)
            {
                continue;
            }
            
			if (adc_started)
			{ // ADC采集已启动
			#if defined(BSP_USING_RSCDRRM020NDSE3)
				float sensor_val = 0;
				rt_size_t read_len = rt_device_read(sensor_dev, 0, &sensor_val, sizeof(sensor_val));
				//APP_TRACE("sensor_val=%f\r\n", sensor_val);
				/* 发送波形数据帧 */
				send_wave(sensor_val);
			#elif defined(BSP_USING_AD7730)
				int32_t sensor_val = 0;
				rt_size_t read_len = rt_device_read(sensor_dev, 0, &sensor_val, sizeof(sensor_val));
				//APP_TRACE("sensor_val=%d\r\n", sensor_val);
				/* 发送波形数据帧 */
				send_wave(sensor_val);
			#endif
			} // 否则丢弃数据
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
		
		if (event_recved & SENSOR_AUTO_ZERO_DONE)
		{ // 传感器自动归零完毕
			if (s_pfnCalCompleted)
			{
				s_pfnCalCompleted();
				s_pfnCalCompleted = NULL;
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
	bme280_deinit();
	if (RT_NULL != sensor_dev)
	{
		rt_device_close(sensor_dev);
		sensor_dev = RT_NULL;
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
static int ota_app_vtor_reconfig(void)
{
	#define NVIC_VTOR_MASK    0x3FFFFF80
	/* Set the Vector Table base location by user application firmware definition */
	SCB->VTOR = RT_APP_PART_ADDR & NVIC_VTOR_MASK;
	
	return 0;
}
INIT_BOARD_EXPORT(ota_app_vtor_reconfig);

/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif
// End of main.cpp
