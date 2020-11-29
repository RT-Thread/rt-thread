/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-11-29     bigmagic       first version
 */
#include <rthw.h>
#include <rtthread.h>

#include "drv_bluetooth.h"
#include "drv_uart.h"
#include "raspi4.h"

//https://github.com/RPi-Distro/bluez-firmware/tree/master/broadcom
//arm-none-eabi-objcopy.exe -I binary -O elf32-littlearm -B arm driver\BCM4345C0.hcd driver\BCM4345C0.a

#define     BT_UART_NAME       "uart0"
#define     BT_TX_MAX          (256)
#define     BT_RX_MAX          (256)
#define     BT_HEAD_NUM        (4)
#define     BT_TRY_NUM_MAX     (3)
#define     BT_SEND_MIN_PACK   (8)

unsigned char lo(unsigned int val) { return (unsigned char)(val & 0xff); }
unsigned char hi(unsigned int val) { return (unsigned char)((val & 0xff00) >> 8); }

#define     BT_THREAD_STACK_SIZE    (2048)
#define     BT_THREAD_PRIORITY      (15)
#define     BT_THREAD_TICK          (10)

static char ch;
static rt_sem_t bt_rx_sem = RT_NULL;
static rt_device_t bt_device;

static rt_uint8_t tx_buff[BT_TX_MAX];
static rt_uint8_t rx_buff[BT_RX_MAX];

static rt_err_t bt_rx_ind(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(bt_rx_sem);
    return RT_EOK;
}

int bt_uart_send_data(rt_device_t dev, rt_uint32_t *buf, int len)
{
    return rt_device_write(dev, 0, buf, len);
}


void bt_uart_receive_flush(rt_device_t dev)
{
    rt_device_read(dev, RT_NULL, rx_buff, BT_RX_MAX);
}

int bt_uart_receive_data(rt_device_t dev, rt_uint8_t *buf, rt_uint32_t *len, rt_int32_t time)
{
    rt_uint16_t ii = 0;
    rt_uint32_t buf_sz = *len;
    rt_uint32_t overflow_len = 0;

    ii =  rt_device_read(dev, 0, buf, BT_RX_MAX);
    *len = ii;
    return ii;
}


void bt_data_pack(rt_uint8_t *tx_buff, rt_uint8_t ogf, rt_uint8_t ocf, rt_uint32_t data_len)
{
    tx_buff[0] = BT_HCI_COMMAND_PKT;
    tx_buff[1] = ogf;//hi(ogf << 10 | ocf);//opcode hi
    tx_buff[2] = ocf;//lo(ogf << 10 | ocf);//opcode lo
    tx_buff[3] = data_len;
}

rt_uint32_t bt_reply_check(const rt_uint8_t *buff, rt_uint16_t ogf, rt_uint16_t ocf, int pack_len)
{
    //step 1
    if(buff[0] != BT_HCI_EVENT_PKT)
    {
        return 1;
    }

    //step2
    if (buff[1] == BT_CONNECT_COMPLETE_CODE)
    {
        if(buff[2] != 4)
        {
            return 2;
        }

        //err code
        if(buff[3] != 0)
        {
            rt_kprintf("Saw HCI COMMAND STATUS error:%d", buff[3]);
            return 12;
        }

        if(buff[4] == 0)
        {
            return 3;
        }

        if(buff[5] != ogf)
        {
            return 4;
        }

        if(buff[6] != ocf)
        {
            return 5;
        }
    }
    else if(buff[1] == BT_COMMAND_COMPLETE_CODE)
    {
        if(buff[2] != 4)
        {
            return 6;
        }

        if(buff[3] == 0)
        {
            return 7;
        }

        if(buff[4] != ogf)
        {
            return 8;
        }

        if(buff[5] != ocf)
        {
            return 9;
        }

        if(buff[6] == 0)
        {
            return 10;
        }
    }
    else
    {
        return 11;
    }
    
    return 0;
}

rt_err_t bt_loadfirmware(void)
{

    int ii = 0;
    int ret = 0;
    int recv_len = BT_RX_MAX;
    int step = 0;
    rt_uint8_t ogf,ocf;

    rt_memset(tx_buff, 0, BT_TX_MAX);

    ogf = hi(BT_OGF_VENDOR << 10 | BT_COMMAND_LOAD_FIRMWARE);
    ocf = lo(BT_OGF_VENDOR << 10 | BT_COMMAND_LOAD_FIRMWARE);

    bt_data_pack(tx_buff, ogf, ocf, 0);
    int kk = 0;
    for (ii = 0; ii < BT_TRY_NUM_MAX; ii++)
    {
        recv_len = BT_RX_MAX;
        bt_uart_receive_flush(bt_device);
        bt_uart_send_data(bt_device, tx_buff, BT_SEND_MIN_PACK);
        rt_thread_mdelay(5);

        ret = bt_uart_receive_data(bt_device, rx_buff, &recv_len, 2000);

        if(ret > 0)
        {
            ret = bt_reply_check(rx_buff, ogf, ocf, ret);
            if(ret == 0)
            {
                step = 1;
                break;
            }
            else
            {
                rt_kprintf("err code is %d\n", ret);
            }
        }
    }

    if (step == 1)
    {
        extern unsigned char _binary_driver_BCM4345C0_hcd_size[];
        extern unsigned char _binary_driver_BCM4345C0_hcd_start[];
        unsigned int c = 0;
        unsigned int size = (long)&_binary_driver_BCM4345C0_hcd_size;
        while (c < size)
        {
            //unsigned char opcodebytes[] = {_binary_BCM4345C0_hcd_start[c], _binary_BCM4345C0_hcd_start[c + 1]};
            unsigned char length = _binary_driver_BCM4345C0_hcd_start[c + 2];
            unsigned char *data = &(_binary_driver_BCM4345C0_hcd_start[c + 3]);
            rt_memset(tx_buff, 0, BT_TX_MAX);

            ogf = _binary_driver_BCM4345C0_hcd_start[c + 1];
            ocf = _binary_driver_BCM4345C0_hcd_start[c];
            bt_data_pack(tx_buff, ogf, ocf, length);

            rt_memcpy(&tx_buff[BT_HEAD_NUM], data, length);
            int kk = 0;
            for (ii = 0; ii < BT_TRY_NUM_MAX; ii++)
            {
                recv_len = BT_RX_MAX;
                rt_memset(rx_buff, 0, BT_TX_MAX);
                bt_uart_receive_flush(bt_device);
                bt_uart_send_data(bt_device, tx_buff, length + BT_HEAD_NUM);
                bt_uart_receive_flush(bt_device);
                rt_thread_mdelay(5);
                ret = bt_uart_receive_data(bt_device, rx_buff, &recv_len, 1000);

                if(ret > 0)
                {
                    ret = bt_reply_check(rx_buff, ogf, ocf, ret);
                    if(ret == 0)
                    {
                        step = 2;
                        break;
                    }
                    else
                    {
                        rt_kprintf("err code is %d\n", ret);
                    }
                }
            }

            if(ii >= 3)
            {
                step = 3;
                break;
            }
            c += 3 + length;
        }

        if(step != 3)
        {
            return RT_EOK;
        }
    }
    else
    {
        return RT_ERROR;
    }
    
    return RT_ERROR;
}


rt_err_t bt_reset(void) 
{
    int ii = 0;
    int ret = 0;
    int recv_len = BT_RX_MAX;
    rt_uint16_t ogf,ocf;

    rt_memset(tx_buff, 0, BT_TX_MAX);

    ogf = hi(BT_OGF_HOST_CONTROL << 10 | BT_COMMAND_RESET_CHIP);
    ocf = lo(BT_OGF_HOST_CONTROL << 10 | BT_COMMAND_RESET_CHIP);

    bt_data_pack(tx_buff, ogf, ocf, 0);
    for (ii = 0; ii < BT_TRY_NUM_MAX; ii++)
    {
        recv_len = BT_RX_MAX;
        bt_uart_receive_flush(bt_device);
        bt_uart_send_data(bt_device, tx_buff, 8);
        rt_thread_mdelay(5);
        ret = bt_uart_receive_data(bt_device, rx_buff, &recv_len, 1000);
        //rt_kprintf("recv_len is %d\n", recv_len);
        if(ret > 0)
        {
            
            ret = bt_reply_check(rx_buff, ogf, ocf, ret);
            if(ret == 0)
            {
                return RT_EOK;
            }
            else
            {
                rt_kprintf("err code is %d\n", ret);
            }
        }
    }
    return RT_ERROR;
}


rt_device_t bt_uart_init(const char *uartname)
{
    rt_device_t dev = RT_NULL;
    if (strcmp(uartname, BT_UART_NAME) == 0)
    {
        bt_rx_sem = rt_sem_create("btbuf", 0, RT_IPC_FLAG_FIFO);
        dev = rt_device_find(uartname);    
        if (dev == RT_NULL)
        {
            rt_kprintf("can no find dev %s\n", uartname);
            return dev;
        }

        if (rt_device_open(dev, RT_DEVICE_OFLAG_RDWR) == RT_EOK)
        {
            rt_device_set_rx_indicate(dev, bt_rx_ind);
        }
        return dev;
    }
    return dev;
}

static void bt_task_entry(void *param)
{
    while (1)
    {
        rt_thread_delay(1000);
    }
    
}

void bt_uart_protocol_init()
{
    rt_thread_t bt_tid = RT_NULL;
    bt_device = bt_uart_init(BT_UART_NAME);
    bt_tid = rt_thread_create("bt_task",bt_task_entry,RT_NULL,BT_THREAD_STACK_SIZE,BT_THREAD_PRIORITY,BT_THREAD_TICK);
    if(bt_tid == RT_NULL)
    {
        rt_kprintf("bt_task create err!\n");
        return 0;
    }
    rt_thread_startup(bt_tid);
}

int rt_hw_bluetooth_init(void)
{
    rt_kprintf("Initialising Bluetooth: \n");
    bt_uart_protocol_init();
    if(bt_reset() == RT_EOK)
    {
        rt_kprintf("bluetooth reset ok!\n");
    }
    else
    {
        rt_kprintf("bluetooth reset err!\n");
    }

        if(bt_reset() == RT_EOK)
    {
        rt_kprintf("bluetooth reset ok!\n");
    }
    else
    {
        rt_kprintf("bluetooth reset err!\n");
    }
    rt_thread_delay(10);
    if(bt_loadfirmware() == RT_EOK)
    {
        rt_kprintf("loadfirmware ok!\n");
    }
    else
    {
        rt_kprintf("loadfirmware err!\n");
    }
}
