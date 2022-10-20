/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @brief bluetooth functions.
 * @file n32wb452_ble_api.h
 * @author Nations
 * @version v1.0.1
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __N32WB452_BLE_API_H__
#define __N32WB452_BLE_API_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32wb452.h"

#define BLE_SERVICE_USED        1       //用到的蓝牙服务数量
#define BLE_CHARACTER_USED      1       //用到的特征字数量

/**
 * @brief 返回值类型定义
 */
typedef enum bt_ret_enum_t
{
    BT_RET_SUCCESS = 0,             //操作成功
    BT_RET_OPERATED_FAILDED_ERR,    //操作失败
    BT_RET_PARAM_NULL_ERR,          //参数为空错误
    BT_RET_PARAM_ERR,               //参数错误
}bt_ret_enum;


/**
 * @brief 定义蓝牙事件
 */
typedef enum bt_event_enum_t
{
    BT_EVENT_VERSION,               //返回蓝牙软件版本，如'V1000'表示Ver1.000
    BT_EVENT_CONNECTED,             //表示蓝牙已连接
    BT_EVENT_DISCONNECTD,           //表示蓝牙已断开
    BT_EVENT_RCV_DATA,              //表示蓝牙模块接收到了主机端下发的数据
}bt_event_enum;

/**
 * @brief 特征字权限
 */
typedef enum bt_character_perm_t
{
    BT_RD_PERM          = 0x00001,      //主机只读
    BT_WRITE_PERM       = 0x00002,      //主机可写，设备端无response
    BT_WRITE_REQ_PERM   = 0x00004,      //主机可写，设备端有response
    BT_NTF_PERM         = 0x00008,      //设备通知
}bt_character_perm;


typedef void (*bt_event_callback_handler_t)(bt_event_enum event, const uint8_t * data, uint32_t size, uint32_t character_uuid);


/**
 * @brief 蓝牙控制参数配置
 */
typedef struct bt_control_param_t
{
    uint32_t multi_mode:1;  //0:disable connect multiple,1:enable connect multiple
    uint32_t reserved:31;  //
}bt_control_param;

/**
 * @brief 蓝牙服务定义
 */
typedef struct bt_svc_param_t
{
    uint16_t svc_uuid;  /// 16 bits UUID，从0xFEC1开始

    struct bt_character{
        uint16_t uuid;
        uint16_t permission;//reference to bt_character_perm
    }character[BLE_CHARACTER_USED];
}bt_svc_param;



/**
 * @brief 蓝牙相关属性配置
 */
typedef struct bt_attr_param_t
{
    bt_control_param ctrl_param;    //蓝牙控制参数
    uint8_t device_name[32];        //蓝牙设备名.4字符以上有效。如全为0x00或无效名称，则使用自带默认名称
    uint8_t scan_rsp_data[31];      //广播应答数据，实际有效长度30
    uint8_t scan_rsp_data_len;      //广播应答数据
    uint8_t device_addr[20];        //格式如："11:22:33:44:55:66"。如配置为0则为默认地址

    //adv data
    bt_svc_param service[BLE_SERVICE_USED];
}bt_attr_param;


/***************************************************************************************
declaraction: int32_t bt_ware_init(bt_event_pcallback pcallback)
function    : 初始化蓝牙模块
parameter   : 蓝牙初始化数据
parameter   : 蓝牙事件回调函数
return      : NONE
***************************************************************************************/
int32_t bt_ware_init(bt_attr_param *pinit, bt_event_callback_handler_t pcallback);


/***************************************************************************************
declaraction: void bt_tick_count(void)
function    : 蓝牙模块需要的计时函数(默认定时:5ms)
parameter   : void
return      : NONE
***************************************************************************************/
//void bt_tick_count(void);


/***************************************************************************************
declaraction: void bt_handler(void)
function    : 蓝牙中断处理
parameter   : void
return      : NONE
***************************************************************************************/
void bt_handler(void);

/***************************************************************************************
declaraction: void bt_run_thread(void)
function    : 蓝牙运行的主线程，用于蓝牙接收、发送、通知等处理
parameter   : void
return      : NONE
***************************************************************************************/
void bt_run_thread(void);


/***************************************************************************************
declaraction: uint32_t bt_rcv_data(uint8_t *data, uint32_t size, uint32_t character)
function    : 根据BT_EVENT_RCV_DATA事件，读取相应服务特征字的数据
parameter   : uint8_t *data 接收数据buf
parameter   : uint32_t size buf大小(最大不超过512Bytes)
parameter   : uint32_t character 发生数据通知对应的特征字ID
return      : 返回实际读取大小
***************************************************************************************/
uint32_t bt_rcv_data(uint8_t *data, uint32_t size, uint32_t character);


/***************************************************************************************
declaraction: uint32_t bt_rcv_data(const uint8_t *data, uint32_t size, uint32_t character)
function    : 发送数据到对应的特征字
parameter   : uint8_t *data 发送数据buf
parameter   : uint32_t 发送数据大小(最大不超过512Bytes)
parameter   : uint32_t character 对应特征字ID
return      : 返回值0
***************************************************************************************/
uint32_t bt_snd_data(const uint8_t *data, uint32_t size, uint32_t character);


/***************************************************************************************
declaraction: void bt_disconnect(void)
function    : slave主动断开蓝牙连接
parameter   : NULL
return      : NULL
***************************************************************************************/
void bt_disconnect(void);

/***************************************************************************************
declaraction: void ble_status_monitor(void)
function    : 蓝牙状态监控
parameter   : NULL
return      : NULL
***************************************************************************************/
void ble_status_monitor(void);

/*==============================================================================
BT_Init
<Description>
    This function is to initialize bluetooth stack
==============================================================================*/
void BT_init(void);


/*==============================================================================
is_bt_busy

<Description>
    This function is to get the bt kernel processing is ongoing or not.
    if not onging, then allow to sleep, otherwise not allow to sleep.

<return>
    0:  bt kernel processing is not ongoing
    1:  bt kernel processing is ongoing
==============================================================================*/
bool is_bt_busy(void);


/*==============================================================================
BT_handle

<Description>
    This function is schedule the BT tasks
==============================================================================*/
void BT_handle(void);

/*==============================================================================
BT_get_version

<Description>
    This function is to get version  of BT API.

<parameter out>
    version:   store the data of the BT API version, size 10 byte;
==============================================================================*/
void BT_get_version(uint8_t * version);

extern bt_event_callback_handler_t g_pcallback;
extern uint32_t g_connnet_start;

/*==============================================================================
ble_get_drv_version


<Description>
    This function is to get the version of the ble driver.

<parameter out>
    version:   store the data of the ble driver version, size 6 byte:"V1.0.0";
==============================================================================*/
extern void ble_get_drv_version(char *version);

#if defined __cplusplus
}
#endif
#endif // __N32WB452_BLE_API_H__


