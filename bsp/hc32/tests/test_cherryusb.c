/*
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-08-08     CDT          first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* 请关注并阅读bsp/hc32/ev_hc32xxxx/README.md中，关于USB使用的相关注意事项
*/

#if defined(RT_CHERRYUSB_HOST) && defined(RT_CHERRYUSB_DEVICE)
    #if defined(HC32F4A0) || defined(HC32F4A8)
        #define TEST_USBH_CORE_BASE   (CM_USBFS_BASE)
        #define TEST_USBD_CORE_BASE   (CM_USBHS_BASE)
    #else
        #error "Only one USB role can be selected"
    #endif
#else
    #if defined(RT_CHERRYUSB_HOST)
        #define TEST_USBH_CORE_BASE   (CM_USBFS_BASE)
    #elif defined(RT_CHERRYUSB_DEVICE)
        #define TEST_USBD_CORE_BASE   (CM_USBFS_BASE)
    #endif
#endif

#if defined(RT_CHERRYUSB_HOST)
#include "usbh_core.h"
#if defined(RT_CHERRYUSB_HOST_CDC_ECM) || defined(RT_CHERRYUSB_HOST_CDC_RNDIS) || defined(RT_CHERRYUSB_HOST_MSC)
/*  使用USB Host 时，应确保主机对设备供电充足

    menuconfig: ECM 关键配置

    RT-Thread Kernel --->[*] Enable soft timer with a timer thread
                            (4096) The stack size of timer thread

    RT-Thread Components--->Devicee Drivers--->[*] Using USB with CherryUSB
                                                  [*] Enable usb host mode
                                                      Selectot usb host ip.... --->
                                                          [*]dwc2_hc
                                                      [*] Enable usb cdc ecm driver

    RT-Thread Components--->Network---> lwIP--->lwIP version ---> v2.1.2
                                                ...
                                                [*] Enable alloc ip address through DHCP
                                                ...
                                                (4096) the stack size of lwIP thread
                                                [*] Not use Rx thread
                                                [*] Not use Tx thread
                                                ...
                                                [*] Enable ping features

    备注:CherryUSB Host枚举设备时，默认选择Configuration 1，若指定设备(如CH397A模组CDC-ECM模式)需要选择Configuration 2，需在
        components/drivers/usb/cherryusb/core/usbh_core.c文件中usbh_enumerate()函数内添加如下代码：
        int usbh_enumerate(struct usbh_hubport *hport)
        {
            ...
            config_index = 0;
            // Add code start
            if((0x1A86 == ((struct usb_device_descriptor *)ep0_request_buffer[hport->bus->busid])->idVendor) && \
               (0x5397 == ((struct usb_device_descriptor *)ep0_request_buffer[hport->bus->busid])->idProduct)) {
                config_index = 1; // For CH397, we need to select configuration 2
            }
            // Add code end
            USB_LOG_DBG("The device selects config %d\r\n", config_index);
            ...
        }


    menuconfig: MSC 关键配置

    RT-Thread Kernel --->[*] Enable soft timer with a timer thread
                            (4096) The stack size of timer thread

    RT-Thread Components--->Devicee Drivers--->[*] Using USB with CherryUSB
                                                  [*] Enable usb host mode
                                                      Selectot usb host ip.... --->
                                                          [*]dwc2_hc
                                                      [*] Enable usb msc driver
                                                      ...
                                                      (/)usb host dfs mount point

*/


/*  ECM 测试
msh />ipconfig
    network interface: u0 (Default)
    MTU: 1500
    MAC: 4e 61 e9 06 9b ff
    FLAGS: UP LINK_UP ETHARP BROADCAST IGMP
    ip address: 192.168.225.29
    gw address: 192.168.225.1
    net mask  : 255.255.255.0
    dns server #0: 108.7.254.31
    dns server #1: 112.7.254.31
msh />ping www.baidu.com
    60 bytes from 183.2.172.177 icmp_seq=0 ttl=51 time=149 ms
    60 bytes from 183.2.172.177 icmp_seq=1 ttl=51 time=69 ms
    60 bytes from 183.2.172.177 icmp_seq=2 ttl=51 time=51 ms
    60 bytes from 183.2.172.177 icmp_seq=3 ttl=51 time=52 ms
*/
static int cherryusb_host_init(void)
{
    usbh_initialize(0, TEST_USBH_CORE_BASE);
    return 0;
}
INIT_APP_EXPORT(cherryusb_host_init);

#if defined(RT_CHERRYUSB_HOST_CDC_ECM) || defined(RT_CHERRYUSB_HOST_CDC_RNDIS)
void ipconfig(void)
{
    extern void list_if(void);
    list_if();
}
MSH_CMD_EXPORT(ipconfig, list network interface information);
#endif

#endif
#endif

#if defined(RT_CHERRYUSB_DEVICE)
#if defined(RT_CHERRYUSB_DEVICE_TEMPLATE_CDC_ACM)
/*
    menuconfig:关键配置

    RT-Thread Components--->Devicee Drivers--->[*] Using USB with CherryUSB
                                                  [*] Enable usb device mode
                                                      Selectot usb host ip.... --->
                                                         [*]dwc2_hc
                                                      [*] Enable usb cdc acm device
                                                          Select usb device template...--->
                                                             [*] cdc acm
*/

static int  cherryusb_device_cdc_acm_init(void)
{
    extern void cdc_acm_init(uint8_t busid, uint32_t reg_base);
    cdc_acm_init(0, TEST_USBD_CORE_BASE);
    return 0;
}
INIT_APP_EXPORT(cherryusb_device_cdc_acm_init);

static void cherryusb_cdc_send(int argc, char **argv)
{
    extern void cdc_acm_data_send_with_dtr_test(uint8_t busid);
    cdc_acm_data_send_with_dtr_test(0);
}
MSH_CMD_EXPORT(cherryusb_cdc_send, cdc acm data send with dtr test);

#endif
#endif
