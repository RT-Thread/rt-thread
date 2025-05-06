/*
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-30     CDT          first version
 */

/*
 * 程序清单：ETH设备使用例程，例程导出了eth_webserver命令到控制终端
 * 命令调用格式：eth_webserver
 *
 * ************************** 测试case 1 **************************
 * 1）网线连接目标板和PC的网络端口，设置PC的对应网卡的IP地址，如下：
 *    IPv4地址：192.168.1.10
 *    子网掩码: 255.255.255.0
 *    默认网关: 192.168.1.1
 * 2）配置RTT工程
 *    menuconfig:
 *     RT-Thread Componets  --->  Network  ---->  LwIP  ---->  lwIP version(lwIP v2.1.2)
 *                                                             Static IPv4 Address，按照如下配置IP：
 *                                                                                  IP address      : 192.168.1.30
 *                                                                                  Gateway address : 192.168.1.1
 *                                                                                  Mask address    : 255.255.255.0
 *                                                             Enable alloc ip address through DHCP，取消该选项
 *     Hardware Drivers Config  --->  Onboard Peripheral Drivers  ---->  Enable Ethernet: ETH PHY USING RTL8201F
 *                                                                                        ETH Communication USING MII
 * 3）拨码开关J33拨到MII端，编译下载、运行代码
 * 4）等待msh>
 * 5）msh>窗口输入命令：ping 192.168.1.10，显示连接正常（60 bytes from 192.168.1.120 icmp_seq=0 ttl=128 time=1 ms）
 * 6）msh>窗口输入命令：eth_webserver
 * 7）PC打开浏览器，输入IP地址：192.168.1.30再按回车键，显示lwip的简介网页（lwIP - A Lightweight TCP/IP Stack），
 *    表示成功访问目标板的HTTP服务器。
 *
 * ************************** 测试case 2 **************************
 * 1）网线连接目标板和PC的网络端口，维持测试case 2配置
 * 2）配置RTT工程，在测试case 1的基础上，使能Enable ETH PHY interrupt mode
 *    menuconfig:
 *     Hardware Drivers Config  --->  Onboard Peripheral Drivers  ---->  Enable ETH PHY interrupt mode: (16) ETH PHY Interrupt pin number
 * 3）拨码开关J33拨到MII端，编译下载、运行代码
 * 4）等待msh>
 * 5）msh>窗口输入命令：ping 192.168.1.10，显示连接正常（60 bytes from 192.168.1.120 icmp_seq=0 ttl=128 time=1 ms）
 * 6）msh>窗口输入命令：eth_webserver
 * 7）PC打开浏览器，输入IP地址：192.168.1.30再按回车键，显示lwip的简介网页（lwIP - A Lightweight TCP/IP Stack），
 *    表示成功访问目标板的HTTP服务器。
 *
 * ************************** 测试case 3 **************************
 * 1）网线连接目标板和PC的网络端口，维持测试case 2配置
 * 2）配置RTT工程，在测试case 2的基础上，ETH Communication USING MII改为ETH Communication USING RMII
 *     Hardware Drivers Config  --->  Onboard Peripheral Drivers  ---->  Enable Ethernet: ETH Communication USING RMII
 * 3）拨码开关J33拨到RMII端，编译下载、运行代码
 * 4）等待msh>
 * 5）msh>窗口输入命令：ping 192.168.1.10，显示连接正常（60 bytes from 192.168.1.120 icmp_seq=0 ttl=128 time=1 ms）
 * 6）msh>窗口输入命令：eth_webserver
 * 7）PC打开浏览器，输入IP地址：192.168.1.30再按回车键，显示lwip的简介网页（lwIP - A Lightweight TCP/IP Stack），
 *    表示成功访问目标板的HTTP服务器。
 */

#include <rtthread.h>

#if defined(BSP_USING_ETH) && defined(RT_USING_LWIP)

extern void httpd_init(void);

void eth_webserver(void)
{
    rt_kprintf("Initialize the httpd...... \r\n");
    httpd_init();
}
MSH_CMD_EXPORT(eth_webserver, eth: start web server);

#endif
