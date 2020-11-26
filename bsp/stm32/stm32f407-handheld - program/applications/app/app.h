/****************************************************************************
 *
 * File Name
 *  app.h
 * Author
 *  wangk
 * Date
 *  2019/08/04
 * Descriptions:
 * app接口定义头文件
 *
 ****************************************************************************/

#ifndef __APP_H__
#define __APP_H__

#include <stdint.h>
#include <stdbool.h>
#include <rtthread.h>

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
typedef enum
{
    COM_MODE_VCOM = 0, // VCOM优先
    COM_MODE_BT // BT优先
} COM_MODE_E;
/*----------------------------------------------------------------------------*
**                             Data Structures                                *
**----------------------------------------------------------------------------*/
/* 校准完成回调函数类型定义 */
typedef void (*CAL_CPL_FUNC)(void);

/* 通信模式 */


/*----------------------------------------------------------------------------*
**                             Function Define                                *
**----------------------------------------------------------------------------*/
/*************************************************
* Function: app_power_off
* Description: 关机
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
void app_power_off(void);

/*************************************************
* Function: is_in_changing
* Description: 当前是否正在充电状态
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
bool is_in_changing(void);

/*************************************************
* Function: is_changer_connect
* Description: 当前是否外接了充电电源
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
bool is_changer_connect(void);

/*************************************************
* Function: is_ble_connect
* Description: BLE是否已建立连接
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
bool is_ble_connect(void);

/*************************************************
* Function: get_battery_level
* Description: 取得电池电量(百分比)
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
uint8_t get_battery_level(void);

/*************************************************
* Function: com_send_data
* Description: 通过配置选择的通道(BT/VCOM)尝试输出数据
* Author: wangk
* Returns: 返回实际输出的字节数
* Parameter:
* History:
*************************************************/
uint32_t com_send_data(const uint8_t* data, uint32_t len);

/*************************************************
* Function: set_com_mode
* Description: 配置通信模式(BT优先/VCOM优先)
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
bool set_com_mode(COM_MODE_E mode);

/*************************************************
* Function: get_com_mode
* Description: 读取通信模式(BT优先/VCOM优先)
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
COM_MODE_E get_com_mode(void);

/*************************************************
* Function: get_com_device
* Description: 当前的通信设备(BT/VCOM)
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
rt_device_t get_com_device(void);

/*************************************************
* Function: vcom_send_data
* Description: 通过VCOM输出数据
* Author: wangk
* Returns: 返回实际输出的字节数
* Parameter:
* History:
*************************************************/
uint32_t vcom_send_data(const uint8_t* data, uint32_t len);

/*************************************************
* Function: bt_send_data
* Description: 通过BT输出数据
* Author: wangk
* Returns: 返回实际输出的字节数
* Parameter:
* History:
*************************************************/
uint32_t bt_send_data(const uint8_t* data, uint32_t len);

/*************************************************
* Function: adc_calibration
* Description: 执行ADC通道校准
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
bool adc_calibration(int adc_channel, CAL_CPL_FUNC pfnCalCompleted);

/*************************************************
* Function: adc_get_freq
* Description: 读取ADC采样率
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
uint32_t adc_get_freq(void);

/*************************************************
* Function: adc_set_freq
* Description: 设置ADC采样率
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
bool adc_set_freq(uint32_t u32FreqIndex);

/*************************************************
* Function: adc_get_temperature
* Description: 读取ADC温度
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
float adc_get_temperature(void);

/*************************************************
* Function: adc_start
* Description: 启动ADC采集
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
bool adc_start(int adc_channel);

/*************************************************
* Function: adc_stop
* Description: 停止ADC采集
* Author: wangk
* Returns:
* Parameter:
* History:
*************************************************/
bool adc_stop(void);

/*************************************************
* Function: bme280_get_temp
* Description: 通过bme280读取温度
* Author: wangk
* Returns: 温度单位,摄氏度
* Parameter:
* History:
*************************************************/
float bme280_get_temp(void);

/*************************************************
* Function: bme280_get_humi
* Description: 通过bme280读取相对湿度
* Author: wangk
* Returns: 相对湿度单位,百分比
* Parameter:
* History:
*************************************************/
float bme280_get_humi(void);

/*************************************************
* Function: bme280_get_baro
* Description: 通过bme280读取大气压
* Author: wangk
* Returns: 大气压单位,帕
* Parameter:
* History:
*************************************************/
float bme280_get_baro(void);

/**--------------------------------------------------------------------------*
**                         Compiler Flag                                     *
**---------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif

#endif // __APP_H__
