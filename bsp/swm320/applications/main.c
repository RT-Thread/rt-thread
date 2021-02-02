/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include <rtdevice.h>

#define LED_PIN 21

int main(void)
{
    int count = 1;

    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);
    while (count++)
    {
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(1000);
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_mdelay(1000);
    }

    return RT_EOK;
}

// #ifdef RT_USING_PIN
// #define KEY1_PIN 25
// void key1_cb(void *args)
// {
//     rt_kprintf("key1 irq!\n");
// }
// static int pin_sample(int argc, char *argv[])
// {
//     rt_pin_mode(KEY1_PIN, PIN_IRQ_MODE_FALLING);
//     rt_pin_attach_irq(KEY1_PIN, PIN_IRQ_MODE_FALLING, key1_cb, RT_NULL);
//     rt_pin_irq_enable(KEY1_PIN, PIN_IRQ_ENABLE);

//     return RT_EOK;
// }
// MSH_CMD_EXPORT(pin_sample, pin sample);
// #endif

#ifdef RT_USING_ADC
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
        return RT_ERROR;
    }

    while (1)
    {
        ret = rt_adc_enable(adc_dev, ADC_DEV_CHANNEL);
        value = rt_adc_read(adc_dev, ADC_DEV_CHANNEL);
        rt_kprintf("the value is :%d,", value);
        vol = value * REFER_VOLTAGE / CONVERT_BITS;
        rt_kprintf("the voltage is :%d.%02d \n", vol / 100, vol % 100);
        rt_thread_mdelay(500);
        ret = rt_adc_disable(adc_dev, ADC_DEV_CHANNEL);
    }

    return ret;
}
MSH_CMD_EXPORT(adc_vol_sample, adc voltage convert sample);
#endif

#ifdef RT_USING_HWTIMER
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
        return RT_ERROR;
    }

    rt_thread_mdelay(3500);

    rt_device_read(hw_dev, 0, &timeout_s, sizeof(timeout_s));
    rt_kprintf("Read: Sec = %d, Usec = %d\n", timeout_s.sec, timeout_s.usec);

    return ret;
}
MSH_CMD_EXPORT(hwtimer_sample, hwtimer sample);
#endif

#ifdef RT_USING_PWM
#define PWM_DEV_NAME "pwm0" /* PWM???? */
#define PWM_DEV_CHANNEL 0   /* PWM?? */

struct rt_device_pwm *pwm_dev; /* PWM???? */

static int pwm_sample(int argc, char *argv[])
{
    rt_uint32_t period, pulse;

    period = 500000; /* ???0.5ms,?????ns */
    pulse = 250000;  /* PWM?????,?????ns */

    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
        return RT_ERROR;
    }

    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
    return RT_EOK;
}
MSH_CMD_EXPORT(pwm_sample, pwm sample);
#endif

#ifdef RT_USING_RTC
static int rtc_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    time_t now;

    ret = set_date(2020, 6, 15);
    if (ret != RT_EOK)
    {
        rt_kprintf("set RTC date failed\n");
        return ret;
    }

    ret = set_time(11, 15, 50);
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
    rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, NULL);
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
    wdg_dev = rt_device_find(device_name);
    if (!wdg_dev)
    {
        rt_kprintf("find %s failed!\n", device_name);
        return RT_ERROR;
    }
    ret = rt_device_init(wdg_dev);
    if (ret != RT_EOK)
    {
        rt_kprintf("initialize %s failed!\n", device_name);
        return RT_ERROR;
    }
    ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
    if (ret != RT_EOK)
    {
        rt_kprintf("set %s timeout failed!\n", device_name);
        return RT_ERROR;
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

#ifdef RT_USING_SPI
#define W25Q_SPI_DEVICE_NAME "spi00"
#define W25Q_FLASH_NAME "norflash0"

#include "drv_spi.h"
#include "spi_flash_sfud.h"
#include "dfs_posix.h"

static int rt_hw_spi_flash_init(void)
{
    rt_hw_spi_device_attach("spi0", "spi00", GPIOA, PIN12);

    if (RT_NULL == rt_sfud_flash_probe(W25Q_FLASH_NAME, W25Q_SPI_DEVICE_NAME))
    {
        return -RT_ERROR;
    };

    return RT_EOK;
}
/* ???????? */
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

    /* ?? spi ???????? */
    spi_dev_w25q = (struct rt_spi_device *)rt_device_find(name);
    struct rt_spi_configuration cfg;
    cfg.data_width = 8;
    cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB;
    cfg.max_hz = 20 * 1000 * 1000; /* 20M */

    rt_spi_configure(spi_dev_w25q, &cfg);
    if (!spi_dev_w25q)
    {
        rt_kprintf("spi sample run failed! can't find %s device!\n", name);
    }
    else
    {
        /* ??1:?? rt_spi_send_then_recv()??????ID */
        rt_spi_send_then_recv(spi_dev_w25q, &w25x_read_id, 1, id, 5);
        rt_kprintf("use rt_spi_send_then_recv() read w25q ID is:%x%x\n", id[3], id[4]);

        /* ??2:?? rt_spi_transfer_message()??????ID */
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
static void spi_flash_elmfat_sample(void)
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

    /* ????????????,??????????????*/
    fd = open("/user/test.txt", O_WRONLY | O_CREAT);
    if (fd >= 0)
    {
        if (write(fd, str, sizeof(str)) == sizeof(str))
            rt_kprintf("Write data done.\n");

        close(fd);
    }

    /* ????????? */
    fd = open("/user/test.txt", O_RDONLY);
    if (fd >= 0)
    {
        size = read(fd, buf, sizeof(buf));

        close(fd);

        if (size == sizeof(str))
            rt_kprintf("Read data from file test.txt(size: %d): %s \n", size, buf);
    }
}
MSH_CMD_EXPORT(spi_flash_elmfat_sample, spi flash elmfat sample);
MSH_CMD_EXPORT(spi_w25q_sample, spi w25q sample);
#endif

//#ifdef RT_USING_SPI
//#define SD_SPI_DEVICE_NAME "spi10"
//#define SDCARD_NAME "sd0"

//#include "drv_spi.h"
//#include "dfs_posix.h"
//#include "spi_msd.h"

//static int rt_hw_spi1_tfcard(void)
//{
//    rt_hw_spi_device_attach("spi1", SD_SPI_DEVICE_NAME, GPIOB, PIN6);
//    return msd_init(SDCARD_NAME, SD_SPI_DEVICE_NAME);
//}
//INIT_DEVICE_EXPORT(rt_hw_spi1_tfcard);

//static void elmfat_sample(void)
//{
//    int fd, size;
//    struct statfs elm_stat;
//    char str[] = "elmfat mount to sdcard.\r\n", buf[80];

//    if (dfs_mkfs("elm", SDCARD_NAME) == 0)
//        rt_kprintf("make elmfat filesystem success.\n");

//    if (dfs_mount(SDCARD_NAME, "/", "elm", 0, 0) == 0)
//        rt_kprintf("elmfat filesystem mount success.\n");

//    if (statfs("/", &elm_stat) == 0)
//        rt_kprintf("elmfat filesystem block size: %d, total blocks: %d, free blocks: %d.\n",
//                   elm_stat.f_bsize, elm_stat.f_blocks, elm_stat.f_bfree);

//    if (mkdir("/user", 0x777) == 0)
//        rt_kprintf("make a directory: '/user'.\n");

//    rt_kprintf("Write string '%s' to /user/test.txt.\n", str);

//    fd = open("/user/test.txt", O_WRONLY | O_CREAT);
//    if (fd >= 0)
//    {
//        if (write(fd, str, sizeof(str)) == sizeof(str))
//            rt_kprintf("Write data done.\n");

//        close(fd);
//    }

//    fd = open("/user/test.txt", O_RDONLY);
//    if (fd >= 0)
//    {
//        size = read(fd, buf, sizeof(buf));

//        close(fd);

//        if (size == sizeof(str))
//            rt_kprintf("Read data from file test.txt(size: %d): %s \n", size, buf);
//    }
//}
//MSH_CMD_EXPORT(elmfat_sample, elmfat sample);
//#endif

#ifdef RT_USING_SDIO
#define SDCARD_NAME "sd0"

#include "dfs_posix.h"

static void sdio_elmfat_sample(void)
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
MSH_CMD_EXPORT(sdio_elmfat_sample, sdio elmfat sample);
#endif

#ifdef RT_USING_HWCRYPTO
static void crypto_sample(void)
{
    rt_uint8_t temp[] = {0, 1, 2, 3, 4, 5, 6, 7};
    struct rt_hwcrypto_ctx *ctx;
    rt_uint32_t result = 0;
    struct hwcrypto_crc_cfg cfg =
        {
            .last_val = 0x0,
            .poly = 0x04C11DB7,
            .width = 8,
            .xorout = 0x00000000,
            .flags = 0,
        };

    ctx = rt_hwcrypto_crc_create(rt_hwcrypto_dev_default(), HWCRYPTO_CRC_CRC32);
    rt_hwcrypto_crc_cfg(ctx, &cfg);
    result = rt_hwcrypto_crc_update(ctx, temp, sizeof(temp));
    rt_kprintf("result: 0x%08x \n", result);
    rt_hwcrypto_crc_destroy(ctx);
}
MSH_CMD_EXPORT(crypto_sample, crypto sample);
#endif

#ifdef BSP_USING_NOR_FLASH
#define NORFLASH_DEV_NAME "nor"
static int norflash_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    rt_device_t hw_dev = RT_NULL;

    hw_dev = rt_device_find(NORFLASH_DEV_NAME);
    if (hw_dev == RT_NULL)
    {
        rt_kprintf("norflash sample run failed! can't find %s device!\n", NORFLASH_DEV_NAME);
        return RT_ERROR;
    }
    else
    {
        rt_kprintf("norflash sample run success! find %s device!\n", NORFLASH_DEV_NAME);
    }

    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", NORFLASH_DEV_NAME);
        return ret;
    }
    else
    {
        rt_kprintf("open %s device success!\n", NORFLASH_DEV_NAME);
    }

    struct rt_mtd_nor_device *hw_nor;
    hw_nor = RT_MTD_NOR_DEVICE(hw_dev);
    long id = hw_nor->ops->read_id(hw_nor);
    rt_kprintf("id = %08x!\n", id);
    // rt_device_set_rx_indicate(hw_dev, timeout_cb);

    // mode = HWTIMER_MODE_PERIOD;
    // //mode = HWTIMER_MODE_ONESHOT;
    // ret = rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);
    // if (ret != RT_EOK)
    // {
    //     rt_kprintf("set mode failed! ret is :%d\n", ret);
    //     return ret;
    // }

    // timeout_s.sec = 2;
    // timeout_s.usec = 0;

    // if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s))
    // {
    //     rt_kprintf("set timeout value failed\n");
    //     return RT_ERROR;
    // }

    // rt_thread_mdelay(3500);

    // rt_device_read(hw_dev, 0, &timeout_s, sizeof(timeout_s));
    // rt_kprintf("Read: Sec = %d, Usec = %d\n", timeout_s.sec, timeout_s.usec);

    return ret;
}
MSH_CMD_EXPORT(norflash_sample, norflash sample);
#endif
