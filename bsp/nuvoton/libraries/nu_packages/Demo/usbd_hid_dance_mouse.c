/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-6-16       HPHuang      First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(RT_USB_DEVICE_HID) && (defined(BSP_USING_USBD) || defined(BSP_USING_HSUSBD))

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_SECTION_NAME "dancemouse"
#define DBG_LEVEL DBG_LOG
#include <rtdbg.h>

static struct rt_thread usb_thread;
ALIGN(RT_ALIGN_SIZE)
static char usb_thread_stack[512];
static struct rt_semaphore tx_sem_complete;

static rt_err_t event_hid_in(rt_device_t dev, void *buffer)
{
    rt_sem_release(&tx_sem_complete);
    return RT_EOK;
}

static void usb_thread_entry(void *parameter)
{
    int8_t i8MouseTable[] = { -16, -16, -16, 0, 16, 16, 16, 0};
    uint8_t u8MouseIdx = 0;
    uint8_t u8MoveLen=0, u8MouseMode = 1;
    uint8_t pu8Buf[4];

    rt_device_t device = (rt_device_t)parameter;

    rt_sem_init(&tx_sem_complete, "tx_complete_sem_hid", 1, RT_IPC_FLAG_FIFO);

    rt_device_set_tx_complete(device, event_hid_in);

    LOG_I("Ready.\n");

    while (1)
    {
        u8MouseMode ^= 1;
        if (u8MouseMode)
        {
            if (u8MoveLen > 14)
            {
                /* Update new report data */
                pu8Buf[0] = 0x00;
                pu8Buf[1] = i8MouseTable[u8MouseIdx & 0x07];
                pu8Buf[2] = i8MouseTable[(u8MouseIdx + 2) & 0x07];
                pu8Buf[3] = 0x00;
                u8MouseIdx++;
                u8MoveLen = 0;
            }
        }
        else
        {
            pu8Buf[0] = pu8Buf[1] = pu8Buf[2] = pu8Buf[3] = 0;
        }

        u8MoveLen++;

        if (rt_device_write(device, HID_REPORT_ID_MOUSE, pu8Buf, 4) == 0)
        {
            /* Sleep 200 Milli-seconds */
            rt_thread_mdelay(200);
        }
        else
        {
            /* Wait it done. */
            rt_sem_take(&tx_sem_complete, RT_WAITING_FOREVER);
        }

    } // while(1)
}

static int dance_mouse_init(void)
{
    int err = 0;
    rt_device_t device = rt_device_find("hidd");

    RT_ASSERT(device != RT_NULL);

    err = rt_device_open(device, RT_DEVICE_FLAG_WRONLY);

    if (err != RT_EOK)
    {
        LOG_E("open dev failed!\n");
        return -1;
    }

    rt_thread_init(&usb_thread,
                   "hidd",
                   usb_thread_entry, device,
                   usb_thread_stack, sizeof(usb_thread_stack),
                   10, 20);

    rt_thread_startup(&usb_thread);

    return 0;
}
INIT_APP_EXPORT(dance_mouse_init);

#endif /* #if defined(RT_USB_DEVICE_HID) && (defined(BSP_USING_USBD) || defined(BSP_USING_HSUSBD)) */
