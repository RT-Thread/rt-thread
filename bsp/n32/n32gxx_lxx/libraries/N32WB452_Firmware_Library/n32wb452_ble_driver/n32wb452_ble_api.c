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
 * @file n32wb452_ble_api.c
 * @author Nations
 * @version v1.0.1
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32wb452.h"
#include "Eif_uart.h"
#include "user.h"
#include "n32wb452_ble_api.h"
#include "n32wb452_data_fifo.h"
#include "n32wb452_log_level.h"
#include "app_task.h"
#include "eif_spi.h"
#include "interface.h"
#include "app.h"
#include "app_user.h"
#include "rwip.h"
#include "ke.h"
#include "ble_monitor.h"
#include "main.h"

#define XOTRIM          0

#ifdef N32WB452_BT_API

//static uint32_t g_overtime_count;
//static uint32_t g_timer_count_flag;
bt_attr_param * g_bt_init = NULL;
uint32_t g_bt_start_finished_flag = 0;
uint32_t g_connnet_start;
bt_event_callback_handler_t g_pcallback = NULL;


void eif_timer_init(void);
void bt_state_get(void);

void bt_handler(void)
{
    eif_spi_recv_irq_handler();
}



/***************************************************************************************
declaraction: int32_t bt_ware_init(bt_attr_param *pinit, bt_event_callback_handler_t pcallback)
function    : 初始化蓝牙模??
parameter   : 蓝牙初始化数??
parameter   : 蓝牙事件回调函数
return      : NONE
***************************************************************************************/
int32_t bt_ware_init(bt_attr_param *pinit, bt_event_callback_handler_t pcallback)
{
    int32_t ret;
//    uint32_t ble_init_status = 0;
    g_bt_init = pinit;

    ret = ble_interface_init();
    if (ret != E_OK) {
        return BT_RET_OPERATED_FAILDED_ERR;
    }

    //2
    ret = ble_hardware_init();
        if (ret != E_OK) {
    return BT_RET_OPERATED_FAILDED_ERR;
    }

    //3
    ret = ble_initdata_down();
    if (ret != E_OK) {
        return BT_RET_OPERATED_FAILDED_ERR;
    }

#if (XOTRIM)
        //--crystal frequency accuracy calibration--
    eif_delay_ms(300);

    //01 03 fd 08 04 00 00 43 ff ff ff ff
    uint8_t cmd_1[12] ={0x01, 0x03, 0xfd,0x08, 0x04, 0x00, 0x00, 0x43, 0xff, 0xff , 0xff, 0xff};
    eif_spi_send_bytes(cmd_1, 12);
    eif_spi_recv_bytes(cmd_1, 7) ; //no need to return
    //01 03 fd 08 00 00 40 52 0A 00 03 00
    uint8_t cmd_2[12] ={0x01, 0x03, 0xfd,0x08, 0x00, 0x00, 0x40, 0x52, 0x0a, 0x00, 0x03, 0x00};
    eif_spi_send_bytes(cmd_2, 12);
    eif_spi_recv_bytes(cmd_2, 7) ; //no need to return
    while (1);
#endif

    //4
    ret = ble_host_init();
    if (ret != E_OK) {
        return BT_RET_OPERATED_FAILDED_ERR;
    }

    g_pcallback = pcallback;

    gBT_STS = BT_INITIALIZED;

    return BT_RET_SUCCESS;
}


/***************************************************************************************
declaraction: void bt_run_thread(void)
function    : 蓝牙运行的主线程，用于蓝牙接收、发送、通知等处??
parameter   : void
return      : NONE
***************************************************************************************/
void bt_run_thread(void)
{
    BT_handle();
}


/***************************************************************************************
declaraction: uint32_t bt_rcv_data(uint8_t *data, uint32_t size, uint32_t character)
function    : 根据BT_EVENT_RCV_DATA事件，读取相应服务特征字的数??
parameter   : uint8_t *data 接收数据buf
parameter   : uint32_t size buf大小(最大不超过512Bytes)
parameter   : uint32_t character 发生数据通知对应的特征字ID
return      : 返回实际读取大小
***************************************************************************************/
uint32_t bt_rcv_data(uint8_t *data, uint32_t size, uint32_t character)
{
    uint32_t read_size;

    read_size = fifo_read(data, &size);
    return read_size;
}


/***************************************************************************************
declaraction: uint32_t bt_rcv_data(const uint8_t *data, uint32_t size, uint32_t character)
function    : 发送数据到对应的特征字
parameter   : uint8_t *data 发送数据buf
parameter   : uint32_t 发送数据大??最大不超过512Bytes)
parameter   : uint32_t character 对应特征字ID
return      : 返回值0
***************************************************************************************/
uint32_t bt_snd_data(const uint8_t *data, uint32_t size, uint32_t character)
{
//    if (g_connnet_start) {
//        if (data && size && character) {
            app_user_data_notify(size, (uint8_t *)data,  character);
//            return size;
//        }
//    }
    return 0;
}

/***************************************************************************************
declaraction: void bt_disconnect(void)
function    : slave主动断开蓝牙连接
parameter   : NULL
return      : NULL
***************************************************************************************/
void bt_disconnect(void)
{
    appm_disconnect();
}

/***************************************************************************************
declaraction: uint32_t bluetooth_state_get(void)
function    : 获取蓝牙连接状态,不对外开放
parameter   : NULL
return      : NULL
***************************************************************************************/
void bt_state_get(void)
{
    static ke_state_t ble_state_last;
    ke_state_t ble_state;
//    bt_event_enum bt_status = BT_EVENT_DISCONNECTD;

    ble_state = ke_state_get(TASK_APP);


    switch (ble_state)
    {
        case APPM_CREATE_DB:
            break;
        case APPM_ADVERTISING:
            if (ble_state_last == APPM_CONNECTED)
            {
                if (g_pcallback) {
                    g_pcallback(BT_EVENT_DISCONNECTD, NULL, 0, 0);
                }
                g_connnet_start = 0;
            }
            break;
        case APPM_CONNECTED:
            if (ble_state_last == APPM_ADVERTISING)
            {
                if (g_pcallback) {
                    g_pcallback(BT_EVENT_CONNECTED, NULL, 0, 0);
                }
                g_connnet_start = 1;
            }
            break;
        case APPM_START_ENC:
            break;
        case APPM_ENCRYPTED:
            break;
        case APPM_INIT:
            break;
    }
    ble_state_last = ble_state;
}

/*contain standard bluetooth version and frimware version*/
#define BT_VERSION_INFO "V4.2_1127"


/*==============================================================================
BT_Init
<Description>
    This function is to initialize bluetooth stack
==============================================================================*/
void BT_init(void)
{
    rwip_init(RESET_NO_ERROR);
}

/*==============================================================================
is_bt_busy

<Description>
    This function is to get the bt kernel processing is ongoing or not.
    if not onging, then allow to sleep, otherwise not allow to sleep.

<return>
    0:  bt kernel processing is not ongoing
    1:  bt kernel processing is ongoing
==============================================================================*/
bool is_bt_busy(void)
{
    return (!ke_sleep_check());
}


/*==============================================================================
BT_handle

<Description>
    This function is schedule the BT tasks
==============================================================================*/
void BT_handle(void)
{
    rwip_schedule();
}


/*==============================================================================
BT_get_version

<Description>
    This function is to get version  of BT API.

<parameter out>
    version:   store the data of the BT API version, size 10 byte;
==============================================================================*/
void BT_get_version(uint8_t * version)
{
    if (version == NULL)
    {
        return;
    }
    memcpy(version, BT_VERSION_INFO, sizeof(BT_VERSION_INFO));
}

#endif

