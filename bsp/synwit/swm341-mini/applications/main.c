/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

#define LED_PIN GET_PIN(B,0)

int main(void)
{
    int count = 1;

    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    while (count++)
    {
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}

#ifdef BSP_USING_GPIO
#define KEY1_PIN GET_PIN(A,8)
void key1_cb(void *args)
{
    rt_kprintf("key1 irq!\n");
}
static int pin_sample(int argc, char *argv[])
{
    rt_pin_mode(KEY1_PIN, PIN_IRQ_MODE_FALLING);
    rt_pin_attach_irq(KEY1_PIN, PIN_IRQ_MODE_FALLING, key1_cb, RT_NULL);
    rt_pin_irq_enable(KEY1_PIN, PIN_IRQ_ENABLE);

    return RT_EOK;
}
MSH_CMD_EXPORT(pin_sample, pin sample);
#endif

#ifdef BSP_USING_ADC
#define ADC_DEV_NAME "adc0"
#define ADC_DEV_CHANNEL 0
#define REFER_VOLTAGE 330
#define CONVERT_BITS (1 << 12)

static int adc_vol_sample(int argc, char *argv[])
{
    rt_adc_device_t adc_dev;
    rt_uint32_t value, vol;
    rt_err_t ret = RT_EOK;

    adc_dev = (rt_adc_device_t)rt_device_find(ADC_DEV_NAME);
    if (adc_dev == RT_NULL)
    {
        rt_kprintf("adc sample run failed! can't find %s device!\n", ADC_DEV_NAME);
        return -RT_ERROR;
    }

    ret = rt_adc_enable(adc_dev, ADC_DEV_CHANNEL);
    value = rt_adc_read(adc_dev, ADC_DEV_CHANNEL);
    rt_kprintf("the value is :%d,", value);
    vol = value * REFER_VOLTAGE / CONVERT_BITS;
    rt_kprintf("the voltage is :%d.%02d \n", vol / 100, vol % 100);

    ret = rt_adc_disable(adc_dev, ADC_DEV_CHANNEL);

    return ret;
}
MSH_CMD_EXPORT(adc_vol_sample, adc voltage convert sample);
#endif

#ifdef BSP_USING_DAC
#include <stdlib.h>

#define DAC_DEV_NAME        "dac"  /* DAC 设备名称 */
#define DAC_DEV_CHANNEL     0       /* DAC 通道 */
#define REFER_VOLTAGE       330         /* 参考电压 3.3V,数据精度乘以100保留2位小数*/
#define CONVERT_BITS        (1 << 12)   /* 转换位数为12位 */

static int dac_vol_sample(int argc, char *argv[])
{
    rt_dac_device_t dac_dev;
    rt_uint32_t value, vol;
    rt_err_t ret = RT_EOK;

    /* 查找设备 */
    dac_dev = (rt_dac_device_t)rt_device_find(DAC_DEV_NAME);
    if (dac_dev == RT_NULL)
    {
        rt_kprintf("dac sample run failed! can't find %s device!\n", DAC_DEV_NAME);
        return -RT_ERROR;
    }

    /* 打开通道 */
    ret = rt_dac_enable(dac_dev, DAC_DEV_CHANNEL);

    /* 设置输出值 */
    value = atoi(argv[1]);
    rt_dac_write(dac_dev, DAC_DEV_CHANNEL, value);
    rt_kprintf("the value is :%d \n", value);

    /* 转换为对应电压值 */
    vol = value * REFER_VOLTAGE / CONVERT_BITS;
    rt_kprintf("the voltage is :%d.%02d \n", vol / 100, vol % 100);
    rt_thread_mdelay(500);
    /* 关闭通道 */
    ret = rt_dac_disable(dac_dev, DAC_DEV_CHANNEL);

    return ret;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(dac_vol_sample, dac voltage convert sample);
#endif

#ifdef BSP_USING_CAN
#define CAN_DEV_NAME       "can0"      /* CAN 设备名称 */

static struct rt_semaphore rx_sem;     /* 用于接收消息的信号量 */
static rt_device_t can_dev;            /* CAN 设备句柄 */

/* 接收数据回调函数 */
static rt_err_t can_rx_call(rt_device_t dev, rt_size_t size)
{
    /* CAN 接收到数据后产生中断，调用此回调函数，然后发送接收信号量 */
    rt_sem_release(&rx_sem);

    return RT_EOK;
}

static void can_rx_thread(void *parameter)
{
    int i;
    rt_err_t res;
    struct rt_can_msg rxmsg = {0};

    /* 设置接收回调函数 */
    rt_device_set_rx_indicate(can_dev, can_rx_call);

#ifdef RT_CAN_USING_HDR
    struct rt_can_filter_item items[5] =
    {
        RT_CAN_FILTER_ITEM_INIT(0x100, 0, 0, 0, 0x700, RT_NULL, RT_NULL), /* std,match ID:0x100~0x1ff，hdr 为 - 1，设置默认过滤表 */
        RT_CAN_FILTER_ITEM_INIT(0x300, 0, 0, 0, 0x700, RT_NULL, RT_NULL), /* std,match ID:0x300~0x3ff，hdr 为 - 1 */
        RT_CAN_FILTER_ITEM_INIT(0x211, 0, 0, 0, 0x7ff, RT_NULL, RT_NULL), /* std,match ID:0x211，hdr 为 - 1 */
        RT_CAN_FILTER_STD_INIT(0x486, RT_NULL, RT_NULL),                  /* std,match ID:0x486，hdr 为 - 1 */
        {0x555, 0, 0, 0, 0x7ff, 7,}                                       /* std,match ID:0x555，hdr 为 7，指定设置 7 号过滤表 */
    };
    struct rt_can_filter_config cfg = {5, 1, items}; /* 一共有 5 个过滤表 */
    /* 设置硬件过滤表 */
    res = rt_device_control(can_dev, RT_CAN_CMD_SET_FILTER, &cfg);
    RT_ASSERT(res == RT_EOK);
#endif

    while (1)
    {
        /* hdr 值为 - 1，表示直接从 uselist 链表读取数据 */
        v .hdr = -1;
        /* 阻塞等待接收信号量 */
        rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
        /* 从 CAN 读取一帧数据 */
        rt_device_read(can_dev, 0, &rxmsg, sizeof(rxmsg));
        /* 打印数据 ID 及内容 */
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
    /* 查找 CAN 设备 */
    can_dev = rt_device_find(can_name);
    if (!can_dev)
    {
        rt_kprintf("find %s failed!\n", can_name);
        return -RT_ERROR;
    }

    /* 初始化 CAN 接收信号量 */
    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);

    /* 以中断接收及发送方式打开 CAN 设备 */
    res = rt_device_open(can_dev, RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);
    RT_ASSERT(res == RT_EOK);
    /* 创建数据接收线程 */
    thread = rt_thread_create("can_rx", can_rx_thread, RT_NULL, 1024, 25, 10);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        rt_kprintf("create can_rx thread failed!\n");
    }

    msg.id = 0x78;              /* ID 为 0x78 */
    msg.ide = RT_CAN_STDID;     /* 标准格式 */
    msg.rtr = RT_CAN_DTR;       /* 数据帧 */
    msg.len = 8;                /* 数据长度为 8 */
    /* 待发送的 8 字节数据 */
    msg.data[0] = 0x00;
    msg.data[1] = 0x11;
    msg.data[2] = 0x22;
    msg.data[3] = 0x33;
    msg.data[4] = 0x44;
    msg.data[5] = 0x55;
    msg.data[6] = 0x66;
    msg.data[7] = 0x77;
    /* 发送一帧 CAN 数据 */
    size = rt_device_write(can_dev, 0, &msg, sizeof(msg));
    if (size == 0)
    {
        rt_kprintf("can dev write data failed!\n");
    }

    return res;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(can_sample, can device sample);
#endif
#ifdef BSP_USING_TIM
#define HWTIMER_DEV_NAME "timer0"

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
        return -RT_ERROR;
    }

    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", HWTIMER_DEV_NAME);
        return ret;
    }

    rt_device_set_rx_indicate(hw_dev, timeout_cb);

    mode = HWTIMER_MODE_PERIOD;
    //mode = HWTIMER_MODE_ONESHOT;
    ret = rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);
    if (ret != RT_EOK)
    {
        rt_kprintf("set mode failed! ret is :%d\n", ret);
        return ret;
    }

    timeout_s.sec = 2;
    timeout_s.usec = 0;

    if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s))
    {
        rt_kprintf("set timeout value failed\n");
        return -RT_ERROR;
    }

    rt_thread_mdelay(3500);

    rt_device_read(hw_dev, 0, &timeout_s, sizeof(timeout_s));
    rt_kprintf("Read: Sec = %d, Usec = %d\n", timeout_s.sec, timeout_s.usec);

    return ret;
}
MSH_CMD_EXPORT(hwtimer_sample, hwtimer sample);
#endif

#ifdef BSP_USING_PWM
#define PWM_DEV_NAME "pwm0" /* PWM设备名称 */
#define PWM_DEV_CHANNEL 0   /* PWM通道 */

struct rt_device_pwm *pwm_dev; /* PWM设备句柄 */

static int pwm_sample(int argc, char *argv[])
{
    rt_uint32_t period, pulse;

    period = 500000; /* 周期为0.5ms，单位为纳秒ns */
    pulse = 100000;  /* PWM脉冲宽度值，单位为纳秒ns */

    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
        return -RT_ERROR;
    }

    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
    return RT_EOK;
}
MSH_CMD_EXPORT(pwm_sample, pwm sample);
#endif

#ifdef BSP_USING_RTC
#include "sys/time.h"

static int rtc_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    time_t now;

    ret = set_date(2000, 2, 28);
    if (ret != RT_EOK)
    {
        rt_kprintf("set RTC date failed\n");
        return ret;
    }

    ret = set_time(23, 59, 55);
    if (ret != RT_EOK)
    {
        rt_kprintf("set RTC time failed\n");
        return ret;
    }

    rt_thread_mdelay(3000);
    now = time(RT_NULL);
    rt_kprintf("%s\n", ctime(&now));

    return ret;
}
MSH_CMD_EXPORT(rtc_sample, rtc sample);
#endif

#ifdef RT_USING_WDT
#define WDT_DEVICE_NAME "wdt"

static rt_device_t wdg_dev;

static void idle_hook(void)
{
    rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, RT_NULL);
    rt_kprintf("feed the dog!\n ");
}

static int wdt_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t timeout = 5;
    char device_name[RT_NAME_MAX];

    if (argc == 2)
    {
        rt_strncpy(device_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(device_name, WDT_DEVICE_NAME, RT_NAME_MAX);
    }
    wdg_dev = rt_device_find(device_name);
    if (!wdg_dev)
    {
        rt_kprintf("find %s failed!\n", device_name);
        return -RT_ERROR;
    }
    ret = rt_device_init(wdg_dev);
    if (ret != RT_EOK)
    {
        rt_kprintf("initialize %s failed!\n", device_name);
        return -RT_ERROR;
    }
    ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
    if (ret != RT_EOK)
    {
        rt_kprintf("set %s timeout failed!\n", device_name);
        return -RT_ERROR;
    }
    ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_START, RT_NULL);
    if (ret != RT_EOK)
    {
        rt_kprintf("start %s failed!\n", device_name);
        return -RT_ERROR;
    }
    // rt_thread_idle_sethook(idle_hook);

    return ret;
}
MSH_CMD_EXPORT(wdt_sample, wdt sample);
#endif

#ifdef BSP_USING_SPI
#define W25Q_SPI_DEVICE_NAME "spi00"
#define W25Q_FLASH_NAME "norflash0"

#include "drv_spi.h"
#ifdef RT_USING_SFUD
#include "dev_spi_flash_sfud.h"

static int rt_hw_spi_flash_init(void)
{
    rt_hw_spi_device_attach("spi0", "spi00", GPIOM, PIN3);

    if (RT_NULL == rt_sfud_flash_probe(W25Q_FLASH_NAME, W25Q_SPI_DEVICE_NAME))
    {
        return -RT_ERROR;
    };

    return RT_EOK;
}
/* 导出到自动初始化 */
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_init);

static void spi_w25q_sample(int argc, char *argv[])
{
    struct rt_spi_device *spi_dev_w25q;
    char name[RT_NAME_MAX];
    rt_uint8_t w25x_read_id = 0x90;
    rt_uint8_t id[5] = {0};

    if (argc == 2)
    {
        rt_strncpy(name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(name, W25Q_SPI_DEVICE_NAME, RT_NAME_MAX);
    }

    /* 查找 spi 设备获取设备句柄 */
    spi_dev_w25q = (struct rt_spi_device *)rt_device_find(name);
    if (!spi_dev_w25q)
    {
        rt_kprintf("spi sample run failed! can't find %s device!\n", name);
    }
    else
    {
        /* 方式1：使用 rt_spi_send_then_recv()发送命令读取ID */
        rt_spi_send_then_recv(spi_dev_w25q, &w25x_read_id, 1, id, 5);
        rt_kprintf("use rt_spi_send_then_recv() read w25q ID is:%x%x\n", id[3], id[4]);

        /* 方式2：使用 rt_spi_transfer_message()发送命令读取ID */
        struct rt_spi_message msg1, msg2;

        msg1.send_buf = &w25x_read_id;
        msg1.recv_buf = RT_NULL;
        msg1.length = 1;
        msg1.cs_take = 1;
        msg1.cs_release = 0;
        msg1.next = &msg2;

        msg2.send_buf = RT_NULL;
        msg2.recv_buf = id;
        msg2.length = 5;
        msg2.cs_take = 0;
        msg2.cs_release = 1;
        msg2.next = RT_NULL;

        rt_spi_transfer_message(spi_dev_w25q, &msg1);
        rt_kprintf("use rt_spi_transfer_message() read w25q ID is:%x%x\n", id[3], id[4]);
    }
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(spi_w25q_sample, spi w25q sample);

#ifdef RT_USING_DFS_ELMFAT
#include <dfs_file.h>
#include <unistd.h>
static void elmfat_sample(void)
{
    int fd, size;
    struct statfs elm_stat;
    char str[] = "elmfat mount to W25Q flash.\r\n", buf[80];

    if (dfs_mkfs("elm", W25Q_FLASH_NAME) == 0)
        rt_kprintf("make elmfat filesystem success.\n");

    if (dfs_mount(W25Q_FLASH_NAME, "/", "elm", 0, 0) == 0)
        rt_kprintf("elmfat filesystem mount success.\n");

    if (statfs("/", &elm_stat) == 0)
        rt_kprintf("elmfat filesystem block size: %d, total blocks: %d, free blocks: %d.\n",
                   elm_stat.f_bsize, elm_stat.f_blocks, elm_stat.f_bfree);

    if (mkdir("/user", 0x777) == 0)
        rt_kprintf("make a directory: '/user'.\n");

    rt_kprintf("Write string '%s' to /user/test.txt.\n", str);

    fd = open("/user/test.txt", O_WRONLY | O_CREAT);
    if (fd >= 0)
    {
        if (write(fd, str, sizeof(str)) == sizeof(str))
            rt_kprintf("Write data done.\n");

        close(fd);
    }

    fd = open("/user/test.txt", O_RDONLY);
    if (fd >= 0)
    {
        size = read(fd, buf, sizeof(buf));

        close(fd);

        if (size == sizeof(str))
            rt_kprintf("Read data from file test.txt(size: %d): %s \n", size, buf);
    }
}
MSH_CMD_EXPORT(elmfat_sample, elmfat sample);
#endif
#endif
#endif

#ifdef BSP_USING_SPI
#ifdef RT_USING_SPI_MSD
#define SD_SPI_DEVICE_NAME "spi00"
#define SDCARD_NAME "sd0"

#include "drv_spi.h"
#include "dev_spi_msd.h"
#include <dfs_file.h>
#include <unistd.h>
static int rt_hw_spi0_tfcard(void)
{
    rt_hw_spi_device_attach("spi0", SD_SPI_DEVICE_NAME, GPION, PIN1);
    return msd_init(SDCARD_NAME, SD_SPI_DEVICE_NAME);
}
INIT_DEVICE_EXPORT(rt_hw_spi0_tfcard);

static void elmfat_sample(void)
{
    int fd, size;
    struct statfs elm_stat;
    char str[] = "elmfat mount to sdcard.\r\n", buf[80];

    if (dfs_mkfs("elm", SDCARD_NAME) == 0)
        rt_kprintf("make elmfat filesystem success.\n");

    if (dfs_mount(SDCARD_NAME, "/", "elm", 0, 0) == 0)
        rt_kprintf("elmfat filesystem mount success.\n");

    if (statfs("/", &elm_stat) == 0)
        rt_kprintf("elmfat filesystem block size: %d, total blocks: %d, free blocks: %d.\n",
                   elm_stat.f_bsize, elm_stat.f_blocks, elm_stat.f_bfree);

    if (mkdir("/user", 0x777) == 0)
        rt_kprintf("make a directory: '/user'.\n");

    rt_kprintf("Write string '%s' to /user/test.txt.\n", str);

    fd = open("/user/test.txt", O_WRONLY | O_CREAT);
    if (fd >= 0)
    {
        if (write(fd, str, sizeof(str)) == sizeof(str))
            rt_kprintf("Write data done.\n");

        close(fd);
    }

    fd = open("/user/test.txt", O_RDONLY);
    if (fd >= 0)
    {
        size = read(fd, buf, sizeof(buf));

        close(fd);

        if (size == sizeof(str))
            rt_kprintf("Read data from file test.txt(size: %d): %s \n", size, buf);
    }
}
MSH_CMD_EXPORT(elmfat_sample, elmfat sample);
#endif
#endif

#ifdef BSP_USING_SDIO
#define SDCARD_NAME "sd0"

#include <dfs_file.h>
#include <unistd.h>

static void elmfat_sample(void)
{
    int fd, size;
    struct statfs elm_stat;
    char str[] = "elmfat mount to sdcard.\n", buf[80];

    if (dfs_mkfs("elm", SDCARD_NAME) == 0)
        rt_kprintf("make elmfat filesystem success.\n");

    if (dfs_mount(SDCARD_NAME, "/", "elm", 0, 0) == 0)
        rt_kprintf("elmfat filesystem mount success.\n");

    if (statfs("/", &elm_stat) == 0)
        rt_kprintf("elmfat filesystem block size: %d, total blocks: %d, free blocks: %d.\n",
                   elm_stat.f_bsize, elm_stat.f_blocks, elm_stat.f_bfree);

    if (mkdir("/user", 0x777) == 0)
        rt_kprintf("make a directory: '/user'.\n");

    rt_kprintf("Write string '%s' to /user/test.txt.\n", str);

    fd = open("/user/test.txt", O_WRONLY | O_CREAT);
    if (fd >= 0)
    {
        if (write(fd, str, sizeof(str)) == sizeof(str))
            rt_kprintf("Write data done.\n");

        close(fd);
    }

    fd = open("/user/test.txt", O_RDONLY);
    if (fd >= 0)
    {
        size = read(fd, buf, sizeof(buf));

        close(fd);

        if (size == sizeof(str))
            rt_kprintf("Read data from file test.txt(size: %d): %s \n", size, buf);
    }
}
MSH_CMD_EXPORT(elmfat_sample, elmfat sample);
#endif

#ifdef RT_USING_HWCRYPTO
static void crypto_sample(void)
{
#ifdef BSP_USING_CRC
    rt_uint8_t temp[] = {0, 1, 2, 3, 4, 5, 6, 7};
    struct rt_hwcrypto_ctx *ctx;
    rt_uint32_t result = 0;
    struct hwcrypto_crc_cfg cfg =
        {
            .last_val = 0x00000000,
            .poly = 0x04C11DB7,
            .width = 8,
            .xorout = 0x00000000, //不支持XOR
            .flags = 0,
        };

    ctx = rt_hwcrypto_crc_create(rt_hwcrypto_dev_default(), HWCRYPTO_CRC_CRC32);
    rt_hwcrypto_crc_cfg(ctx, &cfg);

    result = rt_hwcrypto_crc_update(ctx, temp, sizeof(temp));
    rt_kprintf("result: 0x%08x \n", result);
    rt_hwcrypto_crc_destroy(ctx);
#endif /* BSP_USING_CRC */

#ifdef BSP_USING_RNG
    rt_uint32_t rng_result = 0;
    int i;

    for (i = 0; i < 20; i++)
    {
        rng_result = rt_hwcrypto_rng_update();
        rt_kprintf("rng:0x%08x.\n", rng_result);
    }
#endif /* BSP_USING_RNG */
}
MSH_CMD_EXPORT(crypto_sample, crypto sample);
#endif

#ifdef BSP_USING_SDRAM
#include <rtthread.h>

#define THREAD_PRIORITY 25
#define THREAD_STACK_SIZE 512
#define THREAD_TIMESLICE 5

/* 线程入口 */
void thread1_entry(void *parameter)
{
    int i;
    char *ptr = RT_NULL; /* 内存块的指针 */

    for (i = 0;; i++)
    {
        /* 每次分配 (1 << i) 大小字节数的内存空间 */
        ptr = rt_malloc(1 << i);

        /* 如果分配成功 */
        if (ptr != RT_NULL)
        {
            rt_kprintf("get memory :%d byte\n", (1 << i));
            /* 释放内存块 */
            rt_free(ptr);
            rt_kprintf("free memory :%d byte\n", (1 << i));
            ptr = RT_NULL;
        }
        else
        {
            rt_kprintf("try to get %d byte memory failed!\n", (1 << i));
            return;
        }
    }
}

int dynmem_sample(void)
{
    rt_thread_t tid = RT_NULL;

    /* 创建线程 1 */
    tid = rt_thread_create("thread1",
                           thread1_entry, RT_NULL,
                           THREAD_STACK_SIZE,
                           THREAD_PRIORITY,
                           THREAD_TIMESLICE);
    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(dynmem_sample, dynmem sample);
#endif

#ifdef RT_USING_TOUCH
#include "gt9147.h"

#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        5

int rt_hw_gt9147_port(void)
{
    struct rt_touch_config config;
    rt_uint8_t rst;

    rst = GT9147_RST_PIN;
    config.dev_name = "i2c0";
    config.irq_pin.pin = GT9147_IRQ_PIN;
    config.irq_pin.mode = PIN_MODE_INPUT_PULLDOWN;
    config.user_data = &rst;

    rt_hw_gt9147_init("gt9147", &config);

    return 0;
}
INIT_ENV_EXPORT(rt_hw_gt9147_port);

static rt_thread_t  gt9147_thread = RT_NULL;
static rt_sem_t     gt9147_sem = RT_NULL;
static rt_device_t  dev = RT_NULL;
static struct       rt_touch_data *read_data;

/* 读取数据线程入口函数 */
static void gt9147_entry(void *parameter)
{
    struct rt_touch_data *read_data;
    read_data = (struct rt_touch_data *)rt_malloc(sizeof(struct rt_touch_data) * 5);

    while (1)
    {
        /* 请求信号量 */
        rt_sem_take(gt9147_sem, RT_WAITING_FOREVER);
        /* 读取五个点的触摸信息 */
        if (rt_device_read(dev, 0, read_data, 5) == 5)
        {
            for (rt_uint8_t i = 0; i < 5; i++)
            {
                if (read_data[i].event == RT_TOUCH_EVENT_DOWN || read_data[i].event == RT_TOUCH_EVENT_MOVE)
                {
                    rt_kprintf("%d %d %d %d %d\n",
                                read_data[i].track_id,
                                read_data[i].x_coordinate,
                                read_data[i].y_coordinate,
                                read_data[i].timestamp,
                                read_data[i].width);
                }
            }
        }
        /* 打开中断 */
        rt_device_control(dev, RT_TOUCH_CTRL_ENABLE_INT, RT_NULL);
    }
}

/* 接收回调函数 */
static rt_err_t rx_callback(rt_device_t dev, rt_size_t size)
{
    /* 关闭中断 */
    rt_device_control(dev, RT_TOUCH_CTRL_DISABLE_INT, RT_NULL);
    /* 释放信号量 */
    rt_sem_release(gt9147_sem);
    return 0;
}

static int gt9147_sample(void)
{
    /* 查找 Touch 设备 */
    dev = rt_device_find("gt9147");

    if (dev == RT_NULL)
    {
        rt_kprintf("can't find device:%s\n", "touch");
        return -1;
    }
    /* 以中断的方式打开设备 */
    if (rt_device_open(dev, RT_DEVICE_FLAG_INT_RX) != RT_EOK)
    {
        rt_kprintf("open device failed!");
        return -1;
    }
    /* 设置接收回调 */
    rt_device_set_rx_indicate(dev, rx_callback);
    /* 创建信号量 */
    gt9147_sem = rt_sem_create("dsem", 0, RT_IPC_FLAG_PRIO);

    if (gt9147_sem == RT_NULL)
    {
        rt_kprintf("create dynamic semaphore failed.\n");
        return -1;
    }
    /* 创建读取数据线程 */
    gt9147_thread = rt_thread_create("thread1",
                                     gt9147_entry,
                                     RT_NULL,
                                     THREAD_STACK_SIZE,
                                     THREAD_PRIORITY,
                                     THREAD_TIMESLICE);
    /* 启动线程 */
    if (gt9147_thread != RT_NULL)
        rt_thread_startup(gt9147_thread);

    return 0;
}
MSH_CMD_EXPORT(gt9147_sample, gt9147 sample);
#endif
