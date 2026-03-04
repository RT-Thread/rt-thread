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
 * @file Interface.c
 * @author Nations
 * @version v1.0.2
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */

#include <stdint.h>
#include "Interface.h"
#include "rwip.h"
#include "Ramcode.h"
#include "gapm_task.h"
#include "app.h"
#include "stdlib.h"
#include "string.h"
#include "stdlib.h"
#include "app_user.h"
#include "Eif_uart.h"
#include "ke_event.h"
#include "Eif_flash.h"
#include "Eif_timer.h"
#include "Eif_spi.h"
#include "Eif_iom.h"
#include "log.h"

#ifdef N32WB452_BT_API
#include "n32wb452_data_fifo.h"
#include "n32wb452_ble_api.h"
#include "n32wb452_log_level.h"


extern uint32_t g_bt_start_finished_flag;
extern bt_attr_param * g_bt_init;

#endif

#define  RAMCODE_CMD        0xBB
#define  PATCH_CMD          0xCC
#define  NVDS_CMD           0xDD
#define  SINGLE_CMD_SIZE    0xFA

uint8_t read_state_flag = READ_STATE_RX_START;
void data_read_state_handle(uint8_t read_state_value)
{
    read_state_flag = read_state_value;
}


const struct rwip_eif_api spi_eif_api =
{
    eif_spi_read,
    eif_spi_write,
    eif_spi_flow_on,
    eif_spi_flow_off,
};


const struct rwip_eif_api *rwip_eif_get(uint8_t type)
{
    /*harry would add */
    const struct rwip_eif_api *ret = NULL;
    switch (type)
    {
        case RWIP_EIF_AHI:
            //ret = &uart_eif_api;
            break;
        case RWIP_EIF_HCIH:
            ret = &spi_eif_api;
            break;

        default:
            ASSERT_INFO(0, type, 0);
            break;
    }
    return ret;
}


bool wait_for_status_enable(void)
{
#if 0
    while (!eif_get_status_io_value());
    eif_delay_us(500);  //根据时钟频率设置为延时100us
    while (!eif_get_status_io_value());
    return 1;
#else
    uint16_t cnt = 25000;
    while (cnt--)
    {
        if (eif_get_status_io_value() == 1)
        {
            return 1;
        }
        eif_delay_us(50);
    }

    return 0;
#endif
}

void eif_delay_us(uint32_t Cnt)
{
    while (Cnt--)
        for(uint16_t m = 0; m < 28; m++);
}

void eif_delay_ms(uint32_t Cnt)
{
    while (Cnt--)
    {
        eif_delay_us(999);
    }
}

#ifdef N32WB452_BT_API
int32_t IsAscii(uint8_t ch)
{
    if ((ch >= 0x20) && (ch <= 0x7E)) /*ASCII*/
    {
        return E_OK;
    }
    else
    {
        return E_PAR;
    }
}
#endif


extern struct app_env_tag app_env;
void bt_features_init(void)
{
#ifdef N32WB452_BT_API
    uint32_t size;
    uint32_t name_len = 0;
    uint32_t i;
    uint8_t  addr[BD_ADDR_LEN], ch1, ch2;
    uint8_t device_name[32] = {0};
    uint8_t *ptmp = "12:34:56:AB:CD:EF";
#endif

    app_env.adv_para.adv_type       =  GAPM_ADV_UNDIRECT;    // GAP OPCODE     direct  ,no connect  undirect
    app_env.adv_para.channel_map    = 0x7; // BTstack_data.user_config.adv_para.channel_map;//
    app_env.adv_para.adv_int_min    = 0x320;  //广播间隔时间最小值：0.5S = 0x320*0.625 ms
    app_env.adv_para.adv_int_max    = 0x320;  //广播间隔时间最大值：0.5S = 0x320*0.625 ms
    app_env.adv_para.discover_mode  = GAP_GEN_DISCOVERABLE;

#ifdef N32WB452_BT_API
    if (g_bt_init) {
        size = sizeof(g_bt_init->device_name);
        for (i = 0; i < size; i++) {
            if (E_OK == IsAscii(g_bt_init->device_name[i])) {
                device_name[name_len] = g_bt_init->device_name[i];
                name_len++;
            }
        }
        if (name_len >= 3) {//必须2个字符以上
            //fill name in addr data
            app_env.adv_data_buf[app_env.adv_data_len++] = name_len + 1; // length
            app_env.adv_data_buf[app_env.adv_data_len++] = 0x08;                // device name tag
            memcpy( &app_env.adv_data_buf[app_env.adv_data_len], device_name, name_len);
            app_env.adv_data_len += name_len;
            memcpy(app_env.dev_name, device_name, name_len);
            ble_log(BLE_DEBUG,"device_name:%0s.\r\n", device_name);
        } else {
            uint8_t dev_name[31] = {'N','Z','_','B','L','E'};
            uint8_t dev_name_len = 6;
            //fill name in addr data
            app_env.adv_data_buf[app_env.adv_data_len++] = dev_name_len + 1; // length
            app_env.adv_data_buf[app_env.adv_data_len++] = 0x08;                // device name tag
            memcpy( &app_env.adv_data_buf[app_env.adv_data_len], dev_name, dev_name_len);
            app_env.adv_data_len += dev_name_len;
            memcpy(app_env.dev_name, device_name, name_len);
        }
    } else {
        uint8_t dev_name[31] = {'N','Z','_','B','L','E'};
        uint8_t dev_name_len = 6;
        //fill name in addr data
        app_env.adv_data_buf[app_env.adv_data_len++] = dev_name_len + 1; // length
        app_env.adv_data_buf[app_env.adv_data_len++] = 0x08;                // device name tag
        memcpy( &app_env.adv_data_buf[app_env.adv_data_len], dev_name, dev_name_len);
        app_env.adv_data_len += dev_name_len;
        memcpy(app_env.dev_name, device_name, name_len);
    }
#else
    uint8_t dev_name[31] = {'N','S','_','B','L','E'};
    uint8_t dev_name_len = 6;
    //fill name in addr data
    app_env.adv_data_buf[app_env.adv_data_len++] = dev_name_len + 1; // length
    app_env.adv_data_buf[app_env.adv_data_len++] = 0x08;                // device name tag
    memcpy( &app_env.adv_data_buf[app_env.adv_data_len], dev_name, dev_name_len);
    app_env.adv_data_len += dev_name_len;
    memcpy(app_env.dev_name, device_name, name_len);
#endif

#ifdef N32WB452_BT_API
    if (g_bt_init) {
        memcpy(app_env.scan_rsp_data_buf, g_bt_init->scan_rsp_data, g_bt_init->scan_rsp_data_len);
        app_env.scan_rsp_data_buf[g_bt_init->scan_rsp_data_len] = 0x00;//最后一个设置为0
        app_env.scan_rsp_data_len  = g_bt_init->scan_rsp_data_len;
    } else {
        uint8_t scan_rsp_data[31] = "\x09\xFF\x60\x52\x57\x2D\x42\x4C\x45\0x00";
        memcpy(app_env.scan_rsp_data_buf, scan_rsp_data, 10);
        app_env.scan_rsp_data_len  = 10;
    }
#endif
    app_env.pairing_mode = GAPM_PAIRING_DISABLE/*GAPM_PAIRING_LEGACY*/;
    app_env.iocap        = GAP_IO_CAP_NO_INPUT_NO_OUTPUT;

#ifdef N32WB452_BT_API
    if (g_bt_init) {
        //地址为十六进制如12:34:56:AB:CD:EF
        size = MIN(strlen((const char *)ptmp), sizeof(g_bt_init->device_addr));
        for (i = 0; i < size;) {
            if ((g_bt_init->device_addr[i + 0] && (g_bt_init->device_addr[i + 0] >= '0') && (g_bt_init->device_addr[i + 0] <= '9'))) {
                ch1 = g_bt_init->device_addr[i + 0] - '0';
            } else if ((g_bt_init->device_addr[i + 0] && (g_bt_init->device_addr[i + 0] >= 'a') && (g_bt_init->device_addr[i + 0] <= 'f'))) {
                ch1 = g_bt_init->device_addr[i + 0] - 'a' + 10;
            } else if ((g_bt_init->device_addr[i + 0] && (g_bt_init->device_addr[i + 0] >= 'A') && (g_bt_init->device_addr[i + 0] <= 'F'))) {
                ch1 = g_bt_init->device_addr[i + 0] - 'A' + 10;
            } else {
                ble_log(BLE_DEBUG,"***err1,addr[%d] = %c.\r\n", i + 0, g_bt_init->device_addr[i + 0]);
                break;
            }

            if ((g_bt_init->device_addr[i + 1] && (g_bt_init->device_addr[i + 1] >= '0') && (g_bt_init->device_addr[i + 1] <= '9'))) {
                ch2 = g_bt_init->device_addr[i + 1] - '0';
            } else if ((g_bt_init->device_addr[i + 1] && (g_bt_init->device_addr[i + 1] >= 'a') && (g_bt_init->device_addr[i + 1] <= 'f'))) {
                ch2 = g_bt_init->device_addr[i + 1] - 'a' + 10;
            } else if ((g_bt_init->device_addr[i + 1] && (g_bt_init->device_addr[i + 1] >= 'A') && (g_bt_init->device_addr[i + 1] <= 'F'))) {
                ch2 = g_bt_init->device_addr[i + 1] - 'A' + 10;
            } else {
                ble_log(BLE_DEBUG,"***err2,addr[%d] = %c.\r\n", i + 1, g_bt_init->device_addr[i + 1]);
                break;
            }

            if ((i + 2) < strlen((const char *)ptmp)) {
                if ((g_bt_init->device_addr[i + 2]) && (g_bt_init->device_addr[i + 2] == ':')) {
                    //nothint to do
                } else {
                    ble_log(BLE_DEBUG,"***err3,addr[%d] = %c.\r\n", i + 2, g_bt_init->device_addr[i + 2]);
                    break;
                }
            }

            addr[i / 3] = ch1 * 16 + ch2;
            ble_log(BLE_DEBUG,"addr[%d]:%0x.\r\n", i / 3, addr[i / 3]);
            i += 3;
        }
        if (i >= size) {
            app_env.bdaddr.addr[0] = addr[5];
            app_env.bdaddr.addr[1] = addr[4];
            app_env.bdaddr.addr[2] = addr[3];
            app_env.bdaddr.addr[3] = addr[2];
            app_env.bdaddr.addr[4] = addr[1];
            app_env.bdaddr.addr[5] = addr[0];

            ble_log(BLE_DEBUG,"addr  set ok\r\n");
        } else {
            uint8_t bd_addr[6] = "\x21\x22\x22\x22\x22\x12";
            memcpy(app_env.bdaddr.addr, bd_addr, 6);
        }
    } else {
        uint8_t bd_addr[6] = "\x21\x22\x22\x22\x22\x12";
        memcpy(app_env.bdaddr.addr, bd_addr, 6);
    }
#else
    uint8_t bd_addr[6] = "\x21\x22\x22\x22\x22\x12";
    memcpy(app_env.bdaddr.addr, bd_addr, 6);
#endif

#ifdef BLE_OTA_WRITE_CHAR_EN
    //在广播中增加manufacture数据
    app_env.adv_data_buf[app_env.adv_data_len++] = 3+sizeof(app_env.bdaddr.addr);                // device name tag
    app_env.adv_data_buf[app_env.adv_data_len++] = 0xff;                // device name tag
    app_env.adv_data_buf[app_env.adv_data_len++] = 0x56;                // device name tag
    app_env.adv_data_buf[app_env.adv_data_len++] = 0x00;                // device name tag
    memcpy(&app_env.adv_data_buf[app_env.adv_data_len], app_env.bdaddr.addr, sizeof(app_env.bdaddr.addr));
    app_env.adv_data_len += sizeof(app_env.bdaddr.addr);

    //在广播中增加服务ID数据
    uint8_t service_uuid_len                     = sizeof(g_bt_init->service[0].svc_uuid);
    app_env.adv_data_buf[app_env.adv_data_len++] = service_uuid_len + 1; // length
    app_env.adv_data_buf[app_env.adv_data_len++] = 0x03;                 // service uuid tag
    memcpy(&app_env.adv_data_buf[app_env.adv_data_len], (uint8_t *)&g_bt_init->service[0].svc_uuid, service_uuid_len);
    app_env.adv_data_len += service_uuid_len;
#endif

    app_env.bdaddr_type = 0;

    app_env.batt_lvl = 100; // device battery level

#ifdef N32WB452_BT_API
    g_bt_start_finished_flag = 1;
#endif
}

int32_t send_vendor_array(uint8_t cmd_type, const uint8_t * byte_array, uint16_t  size, uint16_t crc)
{
    uint8_t recv_event[5];
    uint8_t length_cmd[6] =  { 0x01, 0xBB, 0xF1, 0x02, 0x00, 0x00 };
    length_cmd[1] = cmd_type;
    length_cmd[4] = size % 0x100;
    length_cmd[5] = size / 0x100;
    int32_t ret;
    //增加SPI发送和接收
   // eif_uart_send_bytes(length_cmd, 6);
   // eif_uart_recv_bytes(recv_event,5);
    eif_spi_send_bytes(length_cmd, 6);

    ret = eif_spi_recv_bytes(recv_event,5);
    if (ret == E_WAIT) {
        ble_log(BLE_DEBUG,"send_vendor_array-wait1.\r\n");
        return ret;
    }
    else if ((recv_event[0] !=0x04) || (recv_event[4] !=0x00))
    {
        ASSERT_ERR(0);
        ble_log(BLE_DEBUG,"send_vendor_array-errdata1.\r\n");
        return E_ERRDATA;
    }

    uint16_t left_data_length = 0;
    uint8_t data_cmd[256] = { 0x01, 0xBB, 0xF2 };
    data_cmd[1] = cmd_type;
    for(int i = 0; i*SINGLE_CMD_SIZE < size; i++ )
    {
        left_data_length = size - SINGLE_CMD_SIZE*i;
        if (left_data_length >= SINGLE_CMD_SIZE)
        {
            data_cmd[3] = SINGLE_CMD_SIZE;
            memcpy(&data_cmd[4], &byte_array[SINGLE_CMD_SIZE*i], SINGLE_CMD_SIZE);
            //eif_uart_send_bytes(data_cmd, SINGLE_CMD_SIZE+4);
            eif_spi_send_bytes(data_cmd, SINGLE_CMD_SIZE+4);
        }
        else
        {
            data_cmd[3] = left_data_length;
            memcpy(&data_cmd[4], &byte_array[size - left_data_length], left_data_length);
            // eif_uart_send_bytes(data_cmd, left_data_length+4);
            eif_spi_send_bytes(data_cmd, left_data_length+4);
        }
       // eif_uart_recv_bytes(recv_event, 5);
        ret = eif_spi_recv_bytes(recv_event, 5);
        if (ret == E_WAIT) {
            ble_log(BLE_DEBUG,"send_vendor_array-wait2.\r\n");
            return ret;
        }
        else if ((recv_event[0] !=0x04) || (recv_event[4] !=0x00))
        {
            ASSERT_ERR(0);
            ble_log(BLE_DEBUG,"send_vendor_array-errdata2.\r\n");
            return E_ERRDATA;
        }
    }

    uint8_t crc_cmd[6] =  { 0x01, 0xBB, 0xF3, 0x02, 0x00, 0x00 };
    crc_cmd[1] = cmd_type;
    crc_cmd[4] = crc % 0x100;
    crc_cmd[5] = crc / 0x100;

//    eif_uart_send_bytes(crc_cmd, 6);
//    eif_uart_recv_bytes(recv_event, 5);
    eif_spi_send_bytes(crc_cmd, 6);
    ret = eif_spi_recv_bytes(recv_event, 5);
    if (ret == E_WAIT) {
        ble_log(BLE_DEBUG,"send_vendor_array-wait3.\r\n");
        return ret;
    }
    else if (recv_event[0] !=0x04 || recv_event[4] !=0x00)
    {
        ASSERT_ERR(0);
        ble_log(BLE_DEBUG,"send_vendor_array-errdata3.\r\n");
        return E_ERRDATA;
    }

    return E_OK;
}



int32_t send_vendor_bypass_command()
{
    int32_t ret;
    uint8_t passby[6] =  { 0x01, 0xEE, 0xf1, 0x02, 0x00, 0x00 };
    //eif_uart_send_bytes(passby, 6);
    eif_spi_send_bytes(passby, 6);

    uint8_t recv_event[5];
   // eif_uart_recv_bytes(recv_event, 5);
    ret = eif_spi_recv_bytes(recv_event,5);
    if (ret == E_WAIT) {
        ble_log(BLE_DEBUG,"send_vendor_bypass_command-wait1.\r\n");
        return ret;
    }
    else if (recv_event[0] !=0x04 || recv_event[4] !=0x00)
    {
        ASSERT_ERR(0);
        ble_log(BLE_DEBUG,"send_vendor_bypass_command-errdata1.\r\n");
        return E_ERRDATA;
    }

    return E_OK;
}




void eif_reset_ble_core(void)
{
    eif_delay_ms(20);
    eif_pull_down_reset_io();
    //eif_delay_ms(20);
    eif_delay_ms(50);
    eif_pull_up_reset_io();
    //eif_delay_ms(10);
    eif_delay_ms(50);
}


///Z32HUB system init and timer driver
static const struct interface_sys_tag interface_sys_api =
{
    //timer handle
    eif_set_timeout,
    eif_get_time,
    eif_enable_timer,

    //flash handle
    eif_flash_init,
    eif_flash_erase,
    eif_flash_write,
    eif_flash_read,

    //init bt feature
    bt_features_init,
};

struct interface_sys_tag interface_sys;


int32_t ble_interface_init(void)
{
    interface_sys       =   interface_sys_api;

    return E_OK;
}

extern void eif_spi_init(void);
int32_t ble_hardware_init(void)
{
    eif_spi_recv_irq_enable(0);
    eif_gpio_init();  //io init
    eif_timer_init();
    eif_spi_init();
    eif_reset_ble_core();
    return E_OK;
}

int32_t ble_hardware_reinit(void)
{
    ble_interface_init();
    eif_gpio_ReInit();
    eif_spi_init();
    eif_timer_init();
    return E_OK;
}


int32_t ble_init_check(void)
{
    uint8_t length_cmd[6] =  { 0x01, 0xBB, 0xF1, 0x02, 0x00, 0x00 };
    length_cmd[1] = RAMCODE_CMD;
    length_cmd[4] = CopyArrayLength % 0x100;
    length_cmd[5] = CopyArrayLength / 0x100;
    volatile uint32_t i;
    uint32_t tmp;

    while (1) {
        //delay
        eif_delay_ms(100);

        eif_spi_send_bytes(length_cmd, 6);

        for (i = 0; i < 30000; i++) {
            if (eif_spi_ack_event_check() == E_OK) {
                break;
            }

            if ((i > 0) && ((i % 10000) == 0)) {
                tmp = 100 + i / 10;
                ble_log(BLE_DEBUG,"reset continue[%d],dly-time[%d].\r\n", i, tmp);
                eif_reset_ble_core();
                eif_delay_ms(tmp);
                eif_spi_send_bytes(length_cmd, 6);
            }
        }

        if (i < 10000) {
                ble_log(BLE_DEBUG,"ble_init_check-ok[%d].\r\n", i);
                break;
            } else {
                ble_log(BLE_DEBUG,"eif_reset_ble_core-again.\r\n");
                eif_reset_ble_core();
            }
        }

        return E_OK;
    }


int32_t ble_initdata_down(void)
{
    send_vendor_array(RAMCODE_CMD, CopyArray, CopyArrayLength, CopyCrcValue);
    send_vendor_bypass_command();
    send_vendor_array(RAMCODE_CMD, RamcodeArray, RamcodeArrayLength, RamcodeCrcValue);
    send_vendor_array(PATCH_CMD, PatchArray, PatchArrayLength, PatchCrcValue);
    send_vendor_array(NVDS_CMD, NvdsArray, NvdsArrayLength, NvdsCrcValue);
    send_vendor_bypass_command();
    return E_OK;
}


int32_t ble_host_init(void)
{
    //eif_uart_init(500000);
    //eif_uart_recv_irq_enable(1);
    eif_spi_recv_irq_enable(1);
    BT_init();
    appm_init();

    return E_OK;
}

void ble_system_Init(void)
{
    ble_interface_init();
    ble_hardware_init();
    ble_initdata_down();
    ble_host_init();
}


