/*
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-30     CDT          first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USB_DEVICE_CDC
/* menuconfig:
  1.Hardware Drivers Config--->On-Chip Peripheral Driver--->Enable USB--->
                                                            [*]Use USBFS Core
                                                                Select USB Mode(USB Device Mode)
                                                            [*]Enable VBUS Sensing for Device
  2.RT-Thread Components--->
        Using USB legacy version--->
            Using USB device--->Device type--->
                [*]Enable to use device as CDC device
*/
/*
 * 程序清单：这是一个 usb device 设备使用例程
 * 例程导出了 cdc_sample 命令到控制终端
 * PC上需要使用串口助手以DTR[√]方式打开USB的虚拟串口(比如 SSCOM 有这个功能)
 * 命令调用格式：cdc_sample
 * 程序功能：首先会打印三次str_write字符串内容，同时虚拟串口可输入发送任意小于255个字符的字符串，
 * 发送内容可在Finsh串口显示。
 */

#define USBD_DEV_NAME   "vcom"     /* 名称 */
rt_uint8_t str_read[255];

static rt_err_t cdc_rx_handle(rt_device_t dev, rt_size_t size)
{
    /* 读取虚拟串口接收内容 */
    rt_device_read(dev, 0, str_read, size);
    rt_kprintf("Read message:  %s\n", str_read);

    return RT_EOK;
}

static int cdc_sample(void)
{
    rt_uint8_t i;
    rt_err_t ret = RT_EOK;
    rt_device_t cdc_dev = RT_NULL;                           /* usb device设备句柄 */
    rt_uint8_t str_write[] = "This is a usb cdc device test!\r\n";


    /* 查找USB虚拟串口设备 */
    cdc_dev = rt_device_find(USBD_DEV_NAME);
    if (cdc_dev == RT_NULL)
    {
        rt_kprintf("cdc sample run failed! can't find %s device!\n", USBD_DEV_NAME);
        return -RT_ERROR;
    }

    /* 以读写方式打开设备 */
    ret = rt_device_open(cdc_dev, RT_DEVICE_FLAG_INT_RX);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", USBD_DEV_NAME);
        return ret;
    }
    rt_device_set_rx_indicate(cdc_dev, cdc_rx_handle);

    for (i = 1; i < 4; i++)
    {
        rt_kprintf("Start to send test message 3 timers :%d.\n", i);
        if (rt_device_write(cdc_dev, 0, str_write, sizeof(str_write)) != sizeof(str_write))
        {
            rt_kprintf("send test message failed\n");
            return -RT_ERROR;
        }
        /* 延时1000ms */
        rt_thread_mdelay(1000);
    }

    // for (;;);
    return ret;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(cdc_sample, usbd cdc sample);
#endif


#if defined(RT_USB_DEVICE_MSTORAGE)

/* F4A0 only FS can used with spi flash */
#if (defined(HC32F4A0) && defined(BSP_USING_USBFS)) || \
     defined(HC32F460)  || defined(HC32F472)

/* Enable spibus1, SFUD, usb msc */
/* menuconfig:
1. Hardware Drivers Config--->On-Chip Peripheral Driver--->Enable SPI BUS--->Enable SPI1 BUS
2. Hardware Drivers Config--->On-Chip Peripheral Driver--->Enable USB--->
                                                            [*]Use USBFS Core
                                                                Select USB Mode(USB Device Mode)
                                                            [*]Enable VBUS Sensing for Device
3. RT-Thread Components--->Device Drivers--->Using SPI Bus/Device device drivers
                                                [*]Using Serial Flash Universal Driver
                                                    [*]Using auto probe flash JEDEC SFDP parameters
                                                    [*]Using defined supported flash chip information table
                                                    (50000000)Default spi maximum speed(HZ)
4. RT-Thread Components--->Using USB legacy version
                                                [*]Using USB device--->
                                                    Device type--->...Mass Storage device
                                                    (spiflash)msc class disk name

*/
#include "drv_gpio.h"
#include "drv_spi.h"
#include "dev_spi_flash_sfud.h"

#define SPI_FLASH_CHIP                  RT_USB_MSTORAGE_DISK_NAME /* msc class disk name */
#if defined(HC32F4A0)
    #define SPI_FLASH_SS_PORT               GPIO_PORT_C
    #define SPI_FLASH_SS_PIN                GPIO_PIN_07
    #define SPI_BUS_NAME                    "spi1"
    #define SPI_FLASH_DEVICE_NAME           "spi10"
#elif defined(HC32F460)
    #define SPI_FLASH_SS_PORT               GPIO_PORT_C
    #define SPI_FLASH_SS_PIN                GPIO_PIN_07
    #define SPI_BUS_NAME                    "spi3"
    #define SPI_FLASH_DEVICE_NAME           "spi30"
#elif defined(HC32F472)
    #define SPI_FLASH_SS_PORT               GPIO_PORT_B
    #define SPI_FLASH_SS_PIN                GPIO_PIN_12
    #define SPI_BUS_NAME                    "spi1"
    #define SPI_FLASH_DEVICE_NAME           "spi10"
#endif

static void rt_hw_spi_flash_reset(char *spi_dev_name)
{
    struct rt_spi_device *spi_dev_w25;
    rt_uint8_t w25_en_reset = 0x66;
    rt_uint8_t w25_reset_dev = 0x99;

    spi_dev_w25 = (struct rt_spi_device *)rt_device_find(spi_dev_name);
    if (!spi_dev_w25)
    {
        rt_kprintf("Can't find %s device!\n", spi_dev_name);
    }
    else
    {
        rt_spi_send(spi_dev_w25, &w25_en_reset, 1U);
        rt_spi_send(spi_dev_w25, &w25_reset_dev, 1U);
        DDL_DelayMS(1U);
        rt_kprintf("Reset ext flash!\n");
    }
}


static int rt_hw_spi_flash_with_sfud_init(void)
{
#if defined(HC32F4A0) || defined(HC32F460)
    rt_hw_spi_device_attach(SPI_BUS_NAME, SPI_FLASH_DEVICE_NAME, GET_PIN(C, 7));
#elif defined(HC32F472)
    rt_hw_spi_device_attach(SPI_BUS_NAME, SPI_FLASH_DEVICE_NAME, GET_PIN(B, 12));
#endif
    if (RT_NULL == rt_sfud_flash_probe(SPI_FLASH_CHIP, SPI_FLASH_DEVICE_NAME))
    {
        rt_hw_spi_flash_reset(SPI_FLASH_DEVICE_NAME);
        if (RT_NULL == rt_sfud_flash_probe(SPI_FLASH_CHIP, SPI_FLASH_DEVICE_NAME))
        {
            return -RT_ERROR;
        }
    }

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_with_sfud_init);
#endif

#endif

#ifdef RT_USB_DEVICE_HID
#include "drv_gpio.h"

/* menuconfig:
1. Hardware Drivers Config--->On-Chip Peripheral Driver--->Enable USB--->
                                                            [*]Use USBFS Core
                                                                Select USB Mode(USB Device Mode)
                                                            [*]Enable VBUS Sensing for Device
2. RT-Thread Components--->
    Using USB legacy version--->
        Using USB device--->Device type--->
            [*]Enable to use device as HID device
*/
/*
 * 程序清单：这是一个 usb hid device 设备使用例程
 * 例程导出了 hid_sample 命令到控制终端
 * 命令调用格式：hid_sample
 * 程序功能：首先会打印str_write[0]字符串内容，然后按下按键WKUP，hid设备将发送按键keyn，n是按下次数，可
 * 通过bus hound查看数据。
 * 发送内容可在Finsh串口显示。
*/

#define USBD_DEV_NAME   "hidd"     /* 名称 */
#if defined(HC32F4A0)
    #define KEY_PIN_NUM     GET_PIN(A,0)          /* PA0 */
#elif defined(HC32F460)
    #define KEY_PIN_NUM     GET_PIN(B,1)          /* PB1 */
#elif defined(HC32F472)
    #define KEY_PIN_NUM     GET_PIN(B,5)          /* PB5 */
#endif

static int hid_sample(void)
{
    rt_err_t ret = RT_EOK;
    rt_device_t hid_dev = RT_NULL;                           /* usb device设备句柄 */
    char str_write[2][5] = {"test", "Key0"};


    /* 查找设备 */
    hid_dev = rt_device_find(USBD_DEV_NAME);
    if (hid_dev == RT_NULL)
    {
        rt_kprintf("hid sample run failed! can't find %s device!\n", USBD_DEV_NAME);
        return -RT_ERROR;
    }

    /* 以收中断方式打开设备 */
    ret = rt_device_open(hid_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", USBD_DEV_NAME);
        return ret;
    }

    rt_kprintf("This is a usb hid device test!\r\n");
    rt_device_write(hid_dev, 0, str_write[0], sizeof(str_write[0]));
    rt_pin_mode(KEY_PIN_NUM, PIN_MODE_INPUT);

    for (;;)
    {
        rt_thread_mdelay(200);
        if (PIN_LOW == rt_pin_read(KEY_PIN_NUM))
        {
            rt_device_write(hid_dev, 0, str_write[1], sizeof(str_write[1]));
            str_write[1][3] += 0x01;
        }
    }

    //return ret;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(hid_sample, usbd hid sample);
#endif

#ifdef RT_USB_DEVICE_WINUSB
/* menuconfig:
1. Hardware Drivers Config--->On-Chip Peripheral Driver--->Enable USB--->
                                                            [*]Use USBFS Core
                                                                Select USB Mode(USB Device Mode)
                                                            [*]Enable VBUS Sensing for Device
2. RT-Thread Components--->
    Using USB legacy version--->
        Using USB device--->Device type--->
            [*]Enable to use device as winusb device
*/
/*
 * 程序清单：这是一个 usb WINUSB device 设备使用例程
 * RTT 的WINUSB Windows无法免驱，需要使用zadig安装winusb驱动程序(如设备管理器-通用串行总线设备-RTT Win USB已识别则不需要安装)。
 * 例程导出了 winusb_sample 命令到控制终端
 * 命令调用格式：winusb_sample
 * 软件：llcom.exe
 * 程序功能：MSH命令发送winusb_sample，运行测试程序。
 * 打开llcom.exe软件，选择小工具-WinUSB设备-选择对应RTT Win USB设备-打开-勾选Hex发送-发送数据。
 * 通过llcom.exe可发送bulk数据（100字符以内）到设备，设备收到后会回发给主机(llcom.exe)，同时通过MSH终端显示收到的HEX数据。
 * 注意：1、llcom.exe中的GUID与驱动程序中设定保持一致(通过设备管理器选择RTT Win USB设备的属性来查看)；
 *      2、win_usb_read()函数中的UIO_REQUEST_READ_FULL改为UIO_REQUEST_READ_BEST，实现数据即读即取;
 *         否则需要接满传入的size数量，才会回调接收函数。
 *
 */
#define WINUSB_DEV_NAME   "winusb"     /* 名称 */
uint8_t str_read[100];

static rt_err_t winusb_rx_handle(rt_device_t dev, rt_size_t size)
{
    uint8_t i;
    /* 读取定时器当前值 */
    rt_kprintf("Rx:");
    for (i = 0; i < size; i++)
    {
        rt_kprintf("%x", str_read[i]);
    }
    rt_kprintf("\r\n");
    rt_device_write(dev, 0, str_read, size);
    /* prepare read config */
    rt_device_read(dev, 0, str_read, sizeof(str_read));
    return RT_EOK;
}

static int winusb_sample(void)
{
    rt_err_t ret = RT_EOK;
    rt_device_t winusb_dev = RT_NULL;                       /* usb device设备句柄 */

    /* 查找设备 */
    winusb_dev = rt_device_find(WINUSB_DEV_NAME);
    if (winusb_dev == RT_NULL)
    {
        rt_kprintf("winusb sample run failed! can't find %s device!\n", WINUSB_DEV_NAME);
        return -RT_ERROR;
    }

    /* 以读写方式打开设备 */
    ret = rt_device_open(winusb_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", WINUSB_DEV_NAME);
        return ret;
    }
    rt_kprintf("Found and open success %s device!\n", WINUSB_DEV_NAME);

    ret = rt_device_set_rx_indicate(winusb_dev, winusb_rx_handle);
    if (ret == RT_EOK)
    {
        /* prepare read config,set once,read once, */
        rt_device_read(winusb_dev, 0, str_read, sizeof(str_read));
    }
    return ret;
}

/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(winusb_sample, usbd winusb sample);
#endif
