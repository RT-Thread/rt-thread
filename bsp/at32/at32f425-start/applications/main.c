/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-31     shelton      first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
#include "drv_gpio.h"

/* defined the led2 pin: pc2 */
#define LED2_PIN    GET_PIN(C, 2)
/* defined the led3 pin: pc3 */
#define LED3_PIN    GET_PIN(C, 3)
/* defined the led4 pin: pc5 */
#define LED4_PIN    GET_PIN(C, 5)

int main(void)
{
    rt_uint32_t speed = 200;
    /* set led2 pin mode to output */
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);
    /* set led3 pin mode to output */
    rt_pin_mode(LED3_PIN, PIN_MODE_OUTPUT);
    /* set led4 pin mode to output */
    rt_pin_mode(LED4_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED2_PIN, PIN_LOW);
        rt_thread_mdelay(speed);
        rt_pin_write(LED3_PIN, PIN_LOW);
        rt_thread_mdelay(speed);
        rt_pin_write(LED4_PIN, PIN_LOW);
        rt_thread_mdelay(speed);
        rt_pin_write(LED2_PIN, PIN_HIGH);
        rt_thread_mdelay(speed);
        rt_pin_write(LED3_PIN, PIN_HIGH);
        rt_thread_mdelay(speed);
        rt_pin_write(LED4_PIN, PIN_HIGH);
        rt_thread_mdelay(speed);
    }
}

#define SAMPLE_UART_NAME       "uart2"

static struct rt_semaphore rx_sem;
static rt_device_t serial;

static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(&rx_sem);

    return RT_EOK;
}

static void serial_thread_entry(void *parameter)
{
    rt_uint32_t len = 0;
    char ch[20];

    while (1)
    {
        while ((len = rt_device_read(serial, 0, ch, 50)) <= 0)
        {
            rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
        }

        rt_device_write(serial, 0, ch, len);
    }
}

static int uart_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    char uart_name[RT_NAME_MAX];

    if (argc == 2)
    {
        rt_strncpy(uart_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(uart_name, SAMPLE_UART_NAME, RT_NAME_MAX);
    }

    serial = rt_device_find(uart_name);
    if (!serial)
    {
        rt_kprintf("find %s failed!\n", uart_name);
        return RT_ERROR;
    }

    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);

    rt_device_open(serial, RT_DEVICE_FLAG_DMA_RX);

    rt_device_set_rx_indicate(serial, uart_input);

    rt_thread_t thread = rt_thread_create("serial", serial_thread_entry, RT_NULL, 1024, 25, 10);

    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        ret = RT_ERROR;
    }

    return ret;
}

MSH_CMD_EXPORT(uart_sample, uart device sample);

#ifdef BSP_USING_SPI
#include "drv_spi.h"
#include "spi_flash.h"
#include "spi_flash_sfud.h"

static int rt_hw_spi_flash_with_sfud_init(void)
{
    rt_hw_spi_device_attach("spi2", "spi2_0", GPIOB, GPIO_PINS_12);

    if (RT_NULL == rt_sfud_flash_probe("w25q", "spi2_0"))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

INIT_COMPONENT_EXPORT(rt_hw_spi_flash_with_sfud_init);
#endif

#ifdef BSP_USING_QSPI
#include "drv_qspi.h"
#include "spi_flash.h"
#include "spi_flash_sfud.h"

static int rt_hw_qspi_flash_with_sfud_init(void)
{
    at32_qspi_bus_attach_device("qspi2", "qspi2_0", RT_NULL, 4, RT_NULL, RT_NULL);

    /* init n25qxx */
    if (RT_NULL == rt_sfud_flash_probe("w25q", "qspi2_0"))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

INIT_COMPONENT_EXPORT(rt_hw_qspi_flash_with_sfud_init);
#endif

#ifdef BSP_USING_ON_CHIP_FLASH
#include "drv_flash.h"

void dump(rt_uint8_t *buff, rt_uint32_t size)
{
    rt_uint32_t index = 0;

    rt_kprintf("dump data:");
    for(index = 0; index < size; index++)
    {
        rt_kprintf(" %x", *(buff + index));
    }
    rt_kprintf("\n");
}

void fill(rt_uint8_t *buff, rt_uint32_t size)
{
    rt_uint32_t index = 0;

    for(index = 0; index < size; index++)
    {
        *(buff + index) = ~(*(buff + index) + index);
    }
}

static int flash_sample(int argc, char *argv[])
{
#define TEST_ADDR                       0x0800F000
#define BUFFER_SIZE                     0x1000

    rt_uint8_t *buff = rt_malloc(BUFFER_SIZE);
    rt_memset(buff, 0, BUFFER_SIZE);

    if(at32_flash_read(TEST_ADDR, buff, BUFFER_SIZE) != BUFFER_SIZE)
    {
        rt_kprintf("flash read error\n");
    }
    dump(buff, BUFFER_SIZE);

    if(at32_flash_erase(TEST_ADDR, BUFFER_SIZE) != BUFFER_SIZE)
    {
        rt_kprintf("flash erase error\n");
    }

    fill(buff, BUFFER_SIZE);
    if(at32_flash_write(TEST_ADDR, buff, BUFFER_SIZE) != BUFFER_SIZE)
    {
        rt_kprintf("flash write error\n");
    }

    if(at32_flash_read(TEST_ADDR, buff, BUFFER_SIZE) != BUFFER_SIZE)
    {
        rt_kprintf("flash read error\n");
    }
    dump(buff, BUFFER_SIZE);

    rt_free(buff);

    return 0;
}

MSH_CMD_EXPORT(flash_sample, flash sample);
#endif

#ifdef RT_USING_WDT
#define WDT_DEVICE_NAME    "wdt"

static rt_device_t wdt_dev;

static void idle_hook(void)
{
    rt_device_control(wdt_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, NULL);
    rt_kprintf("feed the dog!\n ");
}

static int wdt_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t timeout = 1;
    char device_name[RT_NAME_MAX];

    if (argc == 2)
    {
        rt_strncpy(device_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(device_name, WDT_DEVICE_NAME, RT_NAME_MAX);
    }

    wdt_dev = rt_device_find(device_name);
    if (!wdt_dev)
    {
        rt_kprintf("find %s failed!\n", device_name);
        return RT_ERROR;
    }

    ret = rt_device_control(wdt_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
    if (ret != RT_EOK)
    {
        rt_kprintf("set %s timeout failed!\n", device_name);
        return RT_ERROR;
    }

    ret = rt_device_control(wdt_dev, RT_DEVICE_CTRL_WDT_START, RT_NULL);
    if (ret != RT_EOK)
    {
        rt_kprintf("start %s failed!\n", device_name);
        return -RT_ERROR;
    }

    rt_thread_idle_sethook(idle_hook);

    return ret;
}

MSH_CMD_EXPORT(wdt_sample, wdt sample);
#endif

#ifdef BSP_USING_CAN
#define CAN_DEV_NAME       "can1"

static struct rt_semaphore rx_sem;
static rt_device_t can_dev;

static rt_err_t can_rx_call(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(&rx_sem);

    return RT_EOK;
}

static void can_rx_thread(void *parameter)
{
    int i;
#ifdef RT_CAN_USING_HDR
    rt_err_t res;
#endif
    struct rt_can_msg rxmsg = {0};

    rt_device_set_rx_indicate(can_dev, can_rx_call);

#ifdef RT_CAN_USING_HDR
    struct rt_can_filter_item items[5] =
    {
        RT_CAN_FILTER_ITEM_INIT(0x100, 0, 0, 0, 0x700, RT_NULL, RT_NULL), /* std,match ID:0x100~0x1ff,hdr ? - 1,??????? */
        RT_CAN_FILTER_ITEM_INIT(0x300, 0, 0, 0, 0x700, RT_NULL, RT_NULL), /* std,match ID:0x300~0x3ff,hdr ? - 1 */
        RT_CAN_FILTER_ITEM_INIT(0x211, 0, 0, 0, 0x7ff, RT_NULL, RT_NULL), /* std,match ID:0x211,hdr ? - 1 */
        RT_CAN_FILTER_STD_INIT(0x486, RT_NULL, RT_NULL),                  /* std,match ID:0x486,hdr ? - 1 */
        {0x555, 0, 0, 0, 0x7ff, 7,}                                       /* std,match ID:0x555,hdr ? 7,???? 7 ???? */
    };
    struct rt_can_filter_config cfg = {5, 1, items};

    res = rt_device_control(can_dev, RT_CAN_CMD_SET_FILTER, &cfg);
    RT_ASSERT(res == RT_EOK);
#endif

    while (1)
    {
        rxmsg.hdr_index = -1;
        rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
        rt_device_read(can_dev, 0, &rxmsg, sizeof(rxmsg));
        rt_kprintf("ID:%x", rxmsg.id);
        for (i = 0; i < 8; i++)
        {
            rt_kprintf("%2x", rxmsg.data[i]);
        }

        rt_kprintf("\n");
    }
}

int can_sample(int argc, char *argv[])
{
    struct rt_can_msg msg = {0};
    rt_err_t res;
    rt_size_t  size;
    rt_thread_t thread;
    char can_name[RT_NAME_MAX];

    if (argc == 2)
    {
        rt_strncpy(can_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(can_name, CAN_DEV_NAME, RT_NAME_MAX);
    }
    can_dev = rt_device_find(can_name);
    if (!can_dev)
    {
        rt_kprintf("find %s failed!\n", can_name);
        return RT_ERROR;
    }

    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);

    res = rt_device_open(can_dev, RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);
    RT_ASSERT(res == RT_EOK);

    res = rt_device_control(can_dev, RT_CAN_CMD_SET_BAUD, (void *)CAN1MBaud);

    thread = rt_thread_create("can_rx", can_rx_thread, RT_NULL, 1024, 25, 10);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        rt_kprintf("create can_rx thread failed!\n");
    }

    msg.id = 0x78;
    msg.ide = RT_CAN_STDID;
    msg.rtr = RT_CAN_DTR;
    msg.len = 8;

    msg.data[0] = 0x00;
    msg.data[1] = 0x11;
    msg.data[2] = 0x22;
    msg.data[3] = 0x33;
    msg.data[4] = 0x44;
    msg.data[5] = 0x55;
    msg.data[6] = 0x66;
    msg.data[7] = 0x77;

    size = rt_device_write(can_dev, 0, &msg, sizeof(msg));
    if (size == 0)
    {
        rt_kprintf("can dev write data failed!\n");
    }

    return res;
}

MSH_CMD_EXPORT(can_sample, can_sample);
#endif

#ifdef BSP_USING_I2C
#define EEPROM_I2C_BUS_NAME         "i2c1"
#define EEPROM_ADDR                 0x50

static rt_err_t read_reg(struct rt_i2c_bus_device *bus, rt_uint8_t reg, rt_uint8_t *data)
{
    rt_uint8_t buf[3];
    struct rt_i2c_msg msgs;
    buf[0] = reg;
    msgs.addr = EEPROM_ADDR;
    msgs.flags = RT_I2C_WR;
    msgs.buf = buf;
    msgs.len = 1;

    if (rt_i2c_transfer(bus, &msgs, 1) != 1)
    {
        return -RT_ERROR;
    }

    msgs.addr = EEPROM_ADDR;
    msgs.flags = RT_I2C_RD;
    msgs.buf = data;
    msgs.len = 2;

    if (rt_i2c_transfer(bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}

static rt_err_t write_reg(struct rt_i2c_bus_device *bus, rt_uint8_t reg, rt_uint8_t *data)
{
    rt_uint8_t buf[3];
    struct rt_i2c_msg msgs;
    buf[0] = reg;
    buf[1] = data[0];
    buf[2] = data[1];
    msgs.addr = EEPROM_ADDR;
    msgs.flags = RT_I2C_WR;
    msgs.buf = buf;
    msgs.len = 3;

    if (rt_i2c_transfer(bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}

int i2c_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    static struct rt_i2c_bus_device *i2c_bus = RT_NULL;
    rt_uint8_t rx_buff[2] = {0}, tx_buff[2] = {0x12, 0x34};

    i2c_bus = (struct rt_i2c_bus_device *)rt_device_find(EEPROM_I2C_BUS_NAME);
    if (i2c_bus == RT_NULL)
    {
        rt_kprintf("can't find %s device!\n", EEPROM_I2C_BUS_NAME);
    }
    else
    {
        write_reg(i2c_bus, 0x10, tx_buff);
        rt_thread_mdelay(10);
        read_reg(i2c_bus, 0x10, rx_buff);
        rt_kprintf("rx_buff: %x %x\r\n", rx_buff[0], rx_buff[1]);
    }

    return ret;
}

MSH_CMD_EXPORT(i2c_sample, i2c sample);
#endif

#ifdef BSP_USING_HWTIMER
#define HWTIMER_DEV_NAME   "timer3"

static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_kprintf("this is hwtimer timeout callback fucntion!\n");
    rt_kprintf("tick is :%d !\n", rt_tick_get());

    return 0;
}

static int hwtimer_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    rt_hwtimerval_t timeout_s;
    rt_device_t hw_dev = RT_NULL;
    rt_hwtimer_mode_t mode;

    hw_dev = rt_device_find(HWTIMER_DEV_NAME);
    if (hw_dev == RT_NULL)
    {
        rt_kprintf("hwtimer sample run failed! can't find %s device!\n", HWTIMER_DEV_NAME);
        return RT_ERROR;
    }

    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", HWTIMER_DEV_NAME);
        return ret;
    }

    rt_device_set_rx_indicate(hw_dev, timeout_cb);

    mode = HWTIMER_MODE_PERIOD;
    ret = rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);
    if (ret != RT_EOK)
    {
        rt_kprintf("set mode failed! ret is :%d\n", ret);
        return ret;
    }

    timeout_s.sec = 5;
    timeout_s.usec = 0;

    if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s))
    {
        rt_kprintf("set timeout value failed\n");
        return RT_ERROR;
    }

    rt_thread_mdelay(1000);

    rt_device_read(hw_dev, 0, &timeout_s, sizeof(timeout_s));
    rt_kprintf("Read: Sec = %d, Usec = %d\n", timeout_s.sec, timeout_s.usec);

    return ret;
}

MSH_CMD_EXPORT(hwtimer_sample, hwtimer sample);
#endif



#ifdef BSP_USING_SPI
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_spi.h"

#define W25Q_SPI_DEVICE "spi1_0"
#define MAX_DATA_LEN    3
static void spi_sample(int argc, char * argv[])
{
    struct rt_spi_device *spi_device;
    char name[RT_NAME_MAX];
    rt_uint8_t tx_data[MAX_DATA_LEN] = {0x0};
    rt_uint8_t rx_data[MAX_DATA_LEN] = {0x0};
    rt_uint32_t index = 0;

    rt_hw_spi_device_attach("spi1", W25Q_SPI_DEVICE, GPIOA, GPIO_PINS_4);

    for(index = 0; index < MAX_DATA_LEN; index ++)
    {
        tx_data[index] = index;
    }

    if(argc == 2)
    {
        rt_strncpy(name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(name, W25Q_SPI_DEVICE, RT_NAME_MAX);
    }

    spi_device = (struct rt_spi_device *)rt_device_find(name);
    if(!spi_device)
    {
        rt_kprintf("can't find %s device!\n", name);
    }
    else
    {
        rt_spi_send_then_recv(spi_device, tx_data, MAX_DATA_LEN, rx_data, MAX_DATA_LEN);

        rt_kprintf("recv data:\n");
        for(index = 0; index < MAX_DATA_LEN; index ++)
        {
            rt_kprintf(" 0x%x", rx_data[index]);
        }
        rt_kprintf("\n");

        struct rt_spi_message msg1, msg2;

        msg1.send_buf = tx_data;
        msg1.recv_buf = RT_NULL;
        msg1.length = MAX_DATA_LEN;
        msg1.cs_take = 1;
        msg1.cs_release = 0;
        msg1.next = RT_NULL;

        rt_spi_transfer_message(spi_device, &msg1);

        msg2.send_buf = RT_NULL;
        msg2.recv_buf = rx_data;
        msg2.length = MAX_DATA_LEN;
        msg2.cs_take = 0;
        msg2.cs_release = 1;
        msg2.next = RT_NULL;

        rt_spi_transfer_message(spi_device, &msg2);
    }
}

MSH_CMD_EXPORT(spi_sample, spi device sample);

#endif
