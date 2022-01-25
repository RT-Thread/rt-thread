/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
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

#define BT_UART_NAME     "uart0"
#define BT_TX_MAX        (256)
#define BT_RX_MAX        (256)
#define BT_HEAD_NUM      (4)
#define BT_TRY_NUM_MAX   (3)
#define BT_SEND_MIN_PACK (8)

unsigned char lo(unsigned int val) { return (unsigned char)(val & 0xff); }
unsigned char hi(unsigned int val) { return (unsigned char)((val & 0xff00) >> 8); }

#define BT_THREAD_STACK_SIZE (2048)
#define BT_THREAD_PRIORITY   (15)
#define BT_THREAD_TICK       (10)

enum
{
    LE_EVENT_CODE = 0x3e,
    LE_CONNECT_CODE = 0x01,
    LE_ADREPORT_CODE = 0x02,
    HCI_ACL_PKT = 0x02,
    HCI_EVENT_PKT = 0x04
};

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

    ii = rt_device_read(dev, 0, buf, BT_RX_MAX);
    *len = ii;
    return ii;
}

void bt_data_pack(rt_uint8_t *tx_buff, rt_uint8_t ogf, rt_uint8_t ocf, rt_uint32_t data_len)
{
    tx_buff[0] = BT_HCI_COMMAND_PKT;
    tx_buff[1] = ogf; //hi(ogf << 10 | ocf);//opcode hi
    tx_buff[2] = ocf; //lo(ogf << 10 | ocf);//opcode lo
    tx_buff[3] = data_len;
}

rt_uint32_t bt_reply_check(const rt_uint8_t *buff, rt_uint16_t ogf, rt_uint16_t ocf, int pack_len)
{
    //step 1
    if (buff[0] != BT_HCI_EVENT_PKT)
    {
        return 1;
    }

    //step2
    if (buff[1] == BT_CONNECT_COMPLETE_CODE)
    {
        if (buff[2] != 4)
        {
            return 2;
        }

        //err code
        if (buff[3] != 0)
        {
            rt_kprintf("Saw HCI COMMAND STATUS error:%d", buff[3]);
            return 12;
        }

        if (buff[4] == 0)
        {
            return 3;
        }

        if (buff[5] != ogf)
        {
            return 4;
        }

        if (buff[6] != ocf)
        {
            return 5;
        }
    }
    else if (buff[1] == BT_COMMAND_COMPLETE_CODE)
    {
        if (buff[2] != 4)
        {
            return 6;
        }

        if (buff[3] == 0)
        {
            return 7;
        }

        if (buff[4] != ogf)
        {
            return 8;
        }

        if (buff[5] != ocf)
        {
            return 9;
        }

        if (buff[6] == 0)
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
    rt_uint8_t ogf, ocf;

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

        if (ret > 0)
        {
            ret = bt_reply_check(rx_buff, ogf, ocf, RT_NULL);
            if (ret == 0)
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

                if (ret > 0)
                {
                    ret = bt_reply_check(rx_buff, ogf, ocf, RT_NULL);
                    if (ret == 0)
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

            if (ii >= 3)
            {
                step = 3;
                break;
            }
            c += 3 + length;
        }

        if (step != 3)
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

rt_err_t bt_setbaud(void)
{
    static unsigned char params[] = {0, 0, 0x00, 0xc2, 0x01, 0x00}; // little endian, 115200
    int params_len = 6;
    int ii = 0;
    int ret = 0;

    int recv_len = BT_RX_MAX;
    rt_uint16_t ogf, ocf;

    rt_memset(tx_buff, 0, BT_TX_MAX);

    ogf = hi(BT_OGF_VENDOR << 10 | BT_COMMAND_SET_BAUD);
    ocf = lo(BT_OGF_VENDOR << 10 | BT_COMMAND_SET_BAUD);

    bt_data_pack(tx_buff, ogf, ocf, params_len);

    //rt_memcpy(&tx_buff[BT_HEAD_NUM], params, params_len);
    tx_buff[4] = 0x00;
    tx_buff[5] = 0x01;
    tx_buff[6] = 0xc2;
    tx_buff[7] = 0x00;
    tx_buff[8] = 0x00;
    tx_buff[9] = 0x00;

    for (ii = 0; ii < BT_TRY_NUM_MAX; ii++)
    {
        recv_len = BT_RX_MAX;
        bt_uart_receive_flush(bt_device);
        bt_uart_send_data(bt_device, tx_buff, params_len + BT_HEAD_NUM);
        rt_thread_mdelay(5);
        ret = bt_uart_receive_data(bt_device, rx_buff, &recv_len, 1000);
        if (ret > 0)
        {
            ret = bt_reply_check(rx_buff, ogf, ocf, RT_NULL);
            if (ret == 0)
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

rt_err_t setLEeventmask(unsigned char mask)
{
    unsigned char params[] = {mask, 0, 0, 0, 0, 0, 0, 0};

    //static unsigned char params[] = { 0xee, 0xff, 0xc0, 0xee, 0xff, 0xc0 }; // reversed
    int params_len = 8;
    int ii = 0;
    int ret = 0;

    int recv_len = BT_RX_MAX;
    rt_uint16_t ogf, ocf;

    rt_memset(tx_buff, 0, BT_TX_MAX);

    ogf = hi(BT_OGF_LE_CONTROL << 10 | 0x01);
    ocf = lo(BT_OGF_LE_CONTROL << 10 | 0x01);

    bt_data_pack(tx_buff, ogf, ocf, params_len);

    //rt_memcpy(&tx_buff[BT_HEAD_NUM], params, params_len);
    tx_buff[4] = params[0];
    tx_buff[5] = params[1];
    tx_buff[6] = params[2];
    tx_buff[7] = params[3];
    tx_buff[8] = params[4];
    tx_buff[9] = params[5];
    tx_buff[10] = params[6];
    tx_buff[11] = params[7];


    for (ii = 0; ii < BT_TRY_NUM_MAX; ii++)
    {
        recv_len = BT_RX_MAX;
        bt_uart_receive_flush(bt_device);
        bt_uart_send_data(bt_device, tx_buff, params_len + BT_HEAD_NUM);
        rt_thread_mdelay(5);
        ret = bt_uart_receive_data(bt_device, rx_buff, &recv_len, 1000);
        if (ret > 0)
        {
            ret = bt_reply_check(rx_buff, ogf, ocf, RT_NULL);
            if (ret == 0)
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

    //if (hciCommand(OGF_LE_CONTROL, 0x01, params, 8)) uart_writeText("setLEeventmask failed\n");
}

rt_err_t bt_getbdaddr(unsigned char *bdaddr)
{
    static unsigned char params[] = {0x00, 0x10, 0x09, BT_HCI_COMMAND_PKT}; //get bdaddr
    int params_len = 4;
    int recv_len = BT_RX_MAX;

    // rt_memcpy(tx_buff, params, 4);
    tx_buff[0] = BT_HCI_COMMAND_PKT;
    tx_buff[1] = 0x09;
    tx_buff[2] = 0x10;
    tx_buff[3] = 0x00;

    bt_uart_receive_flush(bt_device);
    bt_uart_send_data(bt_device, tx_buff, 4);
    rt_thread_mdelay(100);
    bt_uart_receive_data(bt_device, rx_buff, &recv_len, 1000);
    if (recv_len > 0)
    {
        if ((rx_buff[0] != BT_HCI_EVENT_PKT) || (rx_buff[1] != BT_COMMAND_COMPLETE_CODE))
        {
            return RT_ERROR;
        }

        if ((rx_buff[2] != 0x0a) || (rx_buff[3] != 0x01))
        {
            return RT_ERROR;
        }

        if ((rx_buff[4] != 0x09) || (rx_buff[5] != 0x10))
        {
            return RT_ERROR;
        }
        bdaddr[0] = rx_buff[7];
        bdaddr[1] = rx_buff[8];
        bdaddr[2] = rx_buff[9];

        bdaddr[3] = rx_buff[10];
        bdaddr[4] = rx_buff[11];
        bdaddr[5] = rx_buff[12];

    }
    else
    {
        return RT_ERROR;
    }

    return RT_EOK;
}

rt_err_t setLEscanenable(unsigned char state, unsigned char duplicates)
{
    unsigned char params[] = {state, duplicates};

    //static unsigned char params[] = { 0xee, 0xff, 0xc0, 0xee, 0xff, 0xc0 }; // reversed
    int params_len = 2;
    int ii = 0;
    int ret = 0;

    int recv_len = BT_RX_MAX;
    rt_uint16_t ogf, ocf;

    rt_memset(tx_buff, 0, BT_TX_MAX);

    ogf = hi(BT_OGF_LE_CONTROL << 10 | 0x0c);
    ocf = lo(BT_OGF_LE_CONTROL << 10 | 0x0c);

    bt_data_pack(tx_buff, ogf, ocf, params_len);
    tx_buff[4] = params[0];
    tx_buff[5] = params[1];

    //rt_memcpy(&tx_buff[BT_HEAD_NUM], params, params_len);

    for (ii = 0; ii < BT_TRY_NUM_MAX; ii++)
    {
        recv_len = BT_RX_MAX;
        bt_uart_receive_flush(bt_device);
        bt_uart_send_data(bt_device, tx_buff, params_len + BT_HEAD_NUM);
        rt_thread_mdelay(5);
        ret = bt_uart_receive_data(bt_device, rx_buff, &recv_len, 1000);
        if (ret > 0)
        {
            ret = bt_reply_check(rx_buff, ogf, ocf, RT_NULL);
            if (ret == 0)
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

rt_err_t setLEscanparameters(unsigned char type, unsigned char linterval, unsigned char hinterval, unsigned char lwindow, unsigned char hwindow, unsigned char own_address_type, unsigned char filter_policy)
{
    unsigned char params[] = {type, linterval, hinterval, lwindow, hwindow, own_address_type, filter_policy};

    int params_len = 7;
    int ii = 0;
    int ret = 0;

    int recv_len = BT_RX_MAX;
    rt_uint16_t ogf, ocf;

    rt_memset(tx_buff, 0, BT_TX_MAX);

    ogf = hi(BT_OGF_LE_CONTROL << 10 | 0x0b);
    ocf = lo(BT_OGF_LE_CONTROL << 10 | 0x0b);

    bt_data_pack(tx_buff, ogf, ocf, params_len);
    tx_buff[4] = params[0];
    tx_buff[5] = params[1];
    tx_buff[6] = params[2];
    tx_buff[7] = params[3];
    tx_buff[8] = params[4];
    tx_buff[9] = params[5];
    tx_buff[10] = params[6];
    //rt_memcpy(&tx_buff[BT_HEAD_NUM], params, params_len);

    for (ii = 0; ii < BT_TRY_NUM_MAX; ii++)
    {
        recv_len = BT_RX_MAX;
        bt_uart_receive_flush(bt_device);
        bt_uart_send_data(bt_device, tx_buff, params_len + BT_HEAD_NUM);
        rt_thread_mdelay(5);
        ret = bt_uart_receive_data(bt_device, rx_buff, &recv_len, 1000);
        if (ret > 0)
        {
            ret = bt_reply_check(rx_buff, ogf, ocf, RT_NULL);
            if (ret == 0)
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

rt_err_t startActiveScanning()
{
    float BleScanInterval = 60; // every 60ms
    float BleScanWindow = 60;
    float BleScanDivisor = 0.625;

    unsigned int p = BleScanInterval / BleScanDivisor;
    unsigned int q = BleScanWindow / BleScanDivisor;

    if (setLEscanparameters(BT_LL_SCAN_ACTIVE, lo(p), hi(p), lo(q), hi(q), 0, 0) == RT_EOK)
    {
        rt_kprintf("setLEscanparameters ok!\n");
    }
    if (setLEscanenable(1, 0) == RT_EOK)
    {
        rt_kprintf("setLEscanenable ok!\n");
    }
}

rt_err_t bt_setbdaddr(void)
{
    static unsigned char params[] = {0xee, 0xff, 0xc0, 0xee, 0xff, 0xc0}; // reversed
    int params_len = 6;
    int ii = 0;
    int ret = 0;

    int recv_len = BT_RX_MAX;
    rt_uint16_t ogf, ocf;

    rt_memset(tx_buff, 0, BT_TX_MAX);

    ogf = hi(BT_OGF_VENDOR << 10 | BT_COMMAND_SET_BDADDR);
    ocf = lo(BT_OGF_VENDOR << 10 | BT_COMMAND_SET_BDADDR);

    bt_data_pack(tx_buff, ogf, ocf, params_len);

    tx_buff[4] = 0xc0;
    tx_buff[5] = 0xff;
    tx_buff[6] = 0xee;
    tx_buff[7] = 0xc0;
    tx_buff[8] = 0xff;
    tx_buff[9] = 0xee;

    //rt_memcpy(&tx_buff[BT_HEAD_NUM], params, params_len);

    for (ii = 0; ii < BT_TRY_NUM_MAX; ii++)
    {
        recv_len = BT_RX_MAX;
        bt_uart_receive_flush(bt_device);
        bt_uart_send_data(bt_device, tx_buff, params_len + BT_HEAD_NUM);
        rt_thread_mdelay(5);
        ret = bt_uart_receive_data(bt_device, rx_buff, &recv_len, 1000);
        if (ret > 0)
        {
            ret = bt_reply_check(rx_buff, ogf, ocf, RT_NULL);
            if (ret == 0)
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
rt_err_t bt_reset(void)
{
    int ii = 0;
    int ret = 0;
    int recv_len = BT_RX_MAX;
    rt_uint16_t ogf, ocf;

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
        if (ret > 0)
        {
            ret = bt_reply_check(rx_buff, ogf, ocf, RT_NULL);
            if (ret == 0)
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

#define MAX_MSG_LEN 50
#define MAX_READ_RUN 100

unsigned char data_buf[MAX_MSG_LEN];
unsigned int data_len;
unsigned int messages_received = 0;
unsigned int poll_state = 0;

unsigned int got_echo_sid = 0;
unsigned int got_echo_name = 0;
unsigned char echo_addr[6];

void hci_poll2(unsigned char byte)
{
    switch (poll_state)
    {
    case 0:
        if (byte != HCI_EVENT_PKT)
            poll_state = 0;
        else
            poll_state = 1;
        break;
    case 1:
        if (byte != LE_EVENT_CODE)
            poll_state = 0;
        else
            poll_state = 2;
        break;
    case 2:
        if (byte > MAX_MSG_LEN)
            poll_state = 0;
        else
        {
            poll_state = 3;
            data_len = byte;
        }
        break;
    default:
        data_buf[poll_state - 3] = byte;
        if (poll_state == data_len + 3 - 1)
        {
            messages_received++;
            poll_state = 0;
        }
        else
            poll_state++;
    }
}

unsigned char *hci_poll()
{
    int recv_len = 256;
    unsigned int goal = messages_received + 1;
    bt_uart_receive_data(bt_device, rx_buff, &recv_len, 1000);
    rt_thread_mdelay(10);
    if (recv_len > 0)
    {
        unsigned int run = 0;
        while (run < MAX_READ_RUN && messages_received < goal)
        {

            recv_len = recv_len - 1;
            hci_poll2(rx_buff[recv_len]);
            run++;

            if (recv_len == 0)
            {
                break;
            }
        }
        if (run == MAX_READ_RUN)
            return 0;
        else
            return data_buf;
    }
    return 0;
}

void bt_search()
{
    unsigned char *buf;

    while ((buf = hci_poll()))
    {
        if (data_len >= 2)
        {
            if (buf[0] == LE_ADREPORT_CODE)
            {
                unsigned char numreports = buf[1];

                if (numreports == 1)
                {
                    unsigned char event_type = buf[2];

                    if (event_type == 0x00)
                    {
                        unsigned char buf_len = buf[10];
                        unsigned char ad_len = buf[11];

                        if (ad_len < data_len && buf_len + 11 == data_len - 1)
                        {
                            for (int c = 9; c >= 4; c--)
                                echo_addr[9 - c] = buf[c];
                            buf += 11;

                            got_echo_sid = 0;
                            got_echo_name = 0; // Reset the search state machine
                            do
                            {
                                ad_len = buf[0];
                                unsigned char ad_type = buf[1];
                                buf += 2;

                                if (ad_len >= 2)
                                {
                                    if (ad_type == 0x03)
                                    {
                                        unsigned int sid = 0;

                                        for (int d = 0; d < ad_len - 1; d += 2)
                                        {
                                            sid = buf[d] | (buf[d + 1] << 8);
                                            if (sid == 0xEC00)
                                            {
                                                rt_kprintf("sid is %d\n", sid);
                                                //uart_hex(sid); uart_writeText(" ");
                                                got_echo_sid = 1;
                                            }
                                        }
                                    }
                                    else if (ad_type == 0x09)
                                    {
                                        char remote_name[ad_len - 1];
                                        unsigned int d = 0;

                                        while (d < ad_len - 1)
                                        {
                                            remote_name[d] = buf[d];
                                            d++;
                                        }
                                        if (!memcmp(remote_name, "echo", 4))
                                        {
                                            rt_kprintf("remote_name is %s\n", remote_name);
                                            got_echo_name = 1;
                                        }
                                    }
                                }

                                buf += ad_len - 1;
                            } while (buf[1]);
                        }
                    }
                }
            }
        }
    }
}

void bt_uart_protocol_init()
{
    rt_thread_t bt_tid = RT_NULL;
    bt_device = bt_uart_init(BT_UART_NAME);
    bt_tid = rt_thread_create("bt_task", bt_task_entry, RT_NULL, BT_THREAD_STACK_SIZE, BT_THREAD_PRIORITY, BT_THREAD_TICK);
    if (bt_tid == RT_NULL)
    {
        rt_kprintf("bt_task create err!\n");
        return 0;
    }
    rt_thread_startup(bt_tid);
}

int rt_hw_bluetooth_init(void)
{
    bt_uart_protocol_init();
    if (bt_reset() == RT_EOK)
    {
        rt_kprintf("bluetooth reset ok!\n");
    }
    else
    {
        rt_kprintf("bluetooth reset err!\n");
    }

    rt_thread_delay(10);
    if (bt_loadfirmware() == RT_EOK)
    {
        rt_kprintf("loadfirmware ok!\n");
    }
    else
    {
        rt_kprintf("loadfirmware err!\n");
    }
    rt_thread_delay(10);
    if (bt_setbaud() == RT_EOK)
    {
        rt_kprintf("setbaud ok!\n");
    }
    else
    {
        rt_kprintf("setbaud err!\n");
    }

    rt_thread_delay(10);
    if (bt_setbdaddr() == RT_EOK)
    {
        rt_kprintf("setbdaddr ok!\n");
    }
    else
    {
        rt_kprintf("setbdaddr err!\n");
    }
    rt_thread_delay(100);
    rt_uint8_t bdaddr[6];
    if (bt_getbdaddr(bdaddr) == RT_EOK)
    {
        rt_kprintf("bdaddr :%02x:%02x:%02x:%02x:%02x:%02x\n", bdaddr[0], bdaddr[1], bdaddr[2], bdaddr[3], bdaddr[4], bdaddr[5]);
    }
    else
    {
        rt_kprintf("getbdaddr err!\n");
    }

    rt_thread_delay(100);

    if (setLEeventmask(0xff) == RT_EOK)
    {
        rt_kprintf("setLEeventmask ok!\n");
    }
    rt_thread_delay(100);
    startActiveScanning();
    rt_thread_delay(500);
    rt_kprintf("start!\n");
    while (1)
    {
        bt_search();
        if (got_echo_sid && got_echo_name)
        {
            break;
        }
        rt_thread_mdelay(10);
    }
    rt_kprintf("stop scan!\n");
}
