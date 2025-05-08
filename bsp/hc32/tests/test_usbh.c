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

#if defined(RT_USING_USB_HOST)

#ifdef RT_USBH_MSTORAGE

/* menuconfig:
  1.  Hardware Drivers Config ---> On-Chip Peripheral Drivers ---> Enable USB --->
                                                                    Select USB Mode (USB Host Mode)
                                                                [*] Enable Udisk Drivers -->
                                                                (/) Udisk mount dir
  2.  RT-Thread Components ---> DFS: device virtual files system --->
                                ......
                                [*] Enable elm0chan fatfs
                                ......
  3.如果命令执行不成功，需参考对应Board目录下的README.md文件(注意事项中的USB Host部分)
 */

/*
 * 程序清单：这是一个 usb host 读写U盘 使用例程
 * 例程导出了 usbh_readwrite 命令到控制终端
 * 命令调用格式：usbh_readwrite
 * 软件：串口助手
 * 程序功能：MSH命令发送 usbh_readwrite，运行测试程序。通过文件系统的命令查看写入的文件，并进行读写删除等操作。
 *
*/
#include <unistd.h>
#include <fcntl.h>
#define TEST_FN     "/test_usbh.c"
static char test_data[120], buffer[120];

void usbh_readwrite(const char *filename)
{
    int fd;
    int index, length;

    fd = open(TEST_FN, O_WRONLY | O_CREAT | O_TRUNC, 0);
    if (fd < 0)
    {
        rt_kprintf("open file for write failed\n");
        return;
    }

    for (index = 0; index < sizeof(test_data); index ++)
    {
        test_data[index] = index + 27;
    }

    length = write(fd, test_data, sizeof(test_data));
    if (length != sizeof(test_data))
    {
        rt_kprintf("write data failed\n");
        close(fd);
        return;
    }

    close(fd);

    fd = open(TEST_FN, O_RDONLY, 0);
    if (fd < 0)
    {
        rt_kprintf("check: open file for read failed\n");
        return;
    }

    length = read(fd, buffer, sizeof(buffer));
    if (length != sizeof(buffer))
    {
        rt_kprintf("check: read file failed\n");
        close(fd);
        return;
    }

    for (index = 0; index < sizeof(test_data); index ++)
    {
        if (test_data[index] != buffer[index])
        {
            rt_kprintf("check: check data failed at %d\n", index);
            close(fd);
            return;
        }
    }

    rt_kprintf("usb host read/write udisk successful\r\n");

    close(fd);
}

MSH_CMD_EXPORT(usbh_readwrite, usb host read write test);

#endif /* RT_USBH_MSTORAGE */

#ifdef RT_USBH_HID

#endif /* RT_USBH_HID */

#ifdef RT_USBH_HID_MOUSE

#endif /* RT_USBH_HID_MOUSE */

#ifdef RT_USBH_HID_KEYBOARD

#endif /* RT_USBH_HID_KEYBOARD */

#endif /* RT_USING_USB_HOST */
