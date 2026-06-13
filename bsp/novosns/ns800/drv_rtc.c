/**
 * @file    drv_rtc.c
 * @brief   RT-Thread RTC device driver (通用外接RTC芯片框架)
 *
 * 支持通过 rtconfig.h 中的宏定义选择 RTC 芯片:
 *   BSP_USING_DS1307  - DS1307  (I2C addr 0x68, 5V)
 *   BSP_USING_PCF8563 - PCF8563 (I2C addr 0x51, 3.3V)
 *
 * 添加新芯片: 在下方加 #elif 分支,实现 init/get_time/set_time 即可
 *
 * 引脚: GP34(SDA), GP35(SCL)
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

/* ========== RTC 芯片选择 ========== */
#if defined(BSP_USING_DS1307)
#  include "ds1307.h"
#  define RTC_INIT()        ds1307_init()
#  define RTC_GET_TIME(t)   ds1307_get_time(t)
#  define RTC_SET_TIME(t)   ds1307_set_time(t)
#  define RTC_CHIP_NAME     "DS1307"

#elif defined(BSP_USING_PCF8563)
#  include "pcf8563.h"
#  define RTC_INIT()        pcf8563_init()
#  define RTC_GET_TIME(t)   pcf8563_get_time(t)
#  define RTC_SET_TIME(t)   pcf8563_set_time(t)
#  define RTC_CHIP_NAME     "PCF8563"

#else
#  error "RTC chip not selected! Define BSP_USING_DS1307 or BSP_USING_PCF8563 in rtconfig.h"
#endif

static struct rt_device g_rtc_dev;

static rt_err_t ns800_rtc_init(struct rt_device *dev)
{
    rt_err_t result = RTC_INIT();
    if (result != RT_EOK) {
        rt_kprintf("RTC: %s init failed!\n", RTC_CHIP_NAME);
        return result;
    }
    rt_kprintf("RTC: %s init success!\n", RTC_CHIP_NAME);
    return RT_EOK;
}

static rt_err_t ns800_rtc_open(struct rt_device *dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t ns800_rtc_close(struct rt_device *dev)
{
    return RT_EOK;
}

static rt_err_t ns800_rtc_control(struct rt_device *dev, int cmd, void *args)
{
    rt_err_t result = RT_EOK;
    struct tm time_struct;
    time_t *time = (time_t *)args;

    switch (cmd) {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        result = RTC_GET_TIME(&time_struct);
        if (result == RT_EOK) {
            *time = mktime(&time_struct);
        }
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        result = RTC_SET_TIME(localtime(time));
        break;

    default:
        result = -RT_ENOSYS;
        break;
    }
    return result;
}

int rt_hw_rtc_init(void)
{
    rt_err_t result;

    g_rtc_dev.type       = RT_Device_Class_RTC;
    g_rtc_dev.init       = ns800_rtc_init;
    g_rtc_dev.open       = ns800_rtc_open;
    g_rtc_dev.close      = ns800_rtc_close;
    g_rtc_dev.read       = RT_NULL;
    g_rtc_dev.write      = RT_NULL;
    g_rtc_dev.control    = ns800_rtc_control;

    result = rt_device_register(&g_rtc_dev, "rtc",
                                RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);
    if (result != RT_EOK) {
        rt_kprintf("RTC: device register failed!\n");
        return -1;
    }
    rt_kprintf("RTC: device registered successfully!\n");

    result = ns800_rtc_init(&g_rtc_dev);
    if (result != RT_EOK) {
        rt_kprintf("[MAIN] RTC hardware init FAILED!\n");
        return -1;
    }
    rt_kprintf("[MAIN] RTC hardware init SUCCESS! Ready to use.\n");
    return 0;
}

/* MSH cmd: use FINSH_FUNCTION_EXPORT instead */
static void show_rtc(void)
{
    time_t now;
    rt_device_t dev = rt_device_find("rtc");
    if (dev) {
        rt_device_control(dev, RT_DEVICE_CTRL_RTC_GET_TIME, &now);
        rt_kprintf("[RTC] %s", ctime(&now));
    }
}
#include <finsh.h>
FINSH_FUNCTION_EXPORT(show_rtc, show rtc time)
