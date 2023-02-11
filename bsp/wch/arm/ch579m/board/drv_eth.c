/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-02-16     Tuber             first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include <netif/ethernetif.h>
#include "drv_eth.h"

#ifdef BSP_USING_ETH

static struct eth_device eth_device;

//DMA接收内存区，必须4字节对齐
__align(4) UINT8 eth_dma_tx_buf[ETH_BUF_SIZE];
__align(4) UINT8 eth_dma_rx_buf[ETH_BUF_SIZE];

UINT16 eth_rx_len = 0; //接收状态和长度
UINT8 eth_rx_buf[ETH_BUF_SIZE]; //中间缓冲区

UINT8 eth_mac_addr[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };

static rt_err_t eth_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t eth_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t eth_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t eth_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t eth_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if (args) rt_memcpy(args, eth_mac_addr, 6);
        else return -RT_ERROR;
        break;
    default :
        break;
    }

    return RT_EOK;
}

rt_err_t eth_tx(rt_device_t dev, struct pbuf *p)
{
    //判断eth是否处于发送状态
    if ((R8_ETH_ECON1 & RB_ETH_ECON1_TXRTS) != 0x00)
    {
        return ERR_INPROGRESS;
    }

    //确定缓冲区是否足够
    if (p->tot_len > sizeof(eth_dma_tx_buf))
    {
        return ERR_MEM;
    }

    //拷贝数据到dma缓冲区
    rt_memcpy(eth_dma_tx_buf, p->payload, p->tot_len);

    //设置数据长度
    R16_ETH_ETXLN = p->tot_len;

    //开始发送
    R8_ETH_ECON1 |= RB_ETH_ECON1_TXRTS;

    return ERR_OK;
}

struct pbuf *eth_rx(rt_device_t dev)
{
    struct pbuf *p = NULL;

    //检查是否有数据
    if (eth_rx_len == 0)
    {
        return NULL;
    }

    p = pbuf_alloc(PBUF_RAW, eth_rx_len, PBUF_POOL);
    if (p == NULL)
    {
        rt_kprintf("eth_rx: pbuf_alloc failed\n");
        eth_rx_len = 0;
        return NULL;
    }

    //拷贝数据到pbuf
    rt_memcpy((uint8_t *)((uint8_t *)p->payload), (uint8_t *)((uint8_t *)eth_rx_buf), eth_rx_len);
    //恢复状态
    eth_rx_len = 0;

    return p;
}

int read_eth_link_status()
{
    R8_ETH_MIREGADR = 0x01;//状态寄存器
    R8_ETH_MISTAT |= 0x00; //读MII寄存器

    //获取link状态
    if ((R16_ETH_MIRD & 0x04) != 0)
    {
        return 1; //已插入
    }

    return 0;
}

void ETH_IRQHandler(void) /* 以太网中断 */
{
    rt_interrupt_enter();

    //接收到数据包
    if ((R8_ETH_EIR & RB_ETH_EIR_RXIF) != 0)
    {
        //判断缓存区是否有数据
        if (eth_rx_len == 0)
        {
            rt_memcpy(eth_rx_buf, eth_dma_rx_buf, R16_ETH_ERXLN);
            eth_rx_len = R16_ETH_ERXLN;
            //通知拿数据
            eth_device_ready(&eth_device);
        }

        R8_ETH_EIR |= RB_ETH_EIR_RXIF; //清除中断
    }

    //接收错误
    if ((R8_ETH_EIR & RB_ETH_EIE_RXERIE) != 0)
    {
        R8_ETH_EIR |= RB_ETH_EIE_RXERIE; //清除中断
    }

    //发送完成
    if ((R8_ETH_EIR & RB_ETH_EIR_TXIF) != 0)
    {
        R8_ETH_EIR |= RB_ETH_EIR_TXIF; //清除中断
    }

    //发送错误
    if ((R8_ETH_EIR & RB_ETH_EIE_TXERIE) != 0)
    {
        R8_ETH_EIR |= RB_ETH_EIE_TXERIE; //清除中断
    }

    //Link 变化标志
    if ((R8_ETH_EIR & RB_ETH_EIR_LINKIF) != 0)
    {
        //获取连接状态
        if (read_eth_link_status())
        {
            eth_device_linkchange(&eth_device, RT_TRUE);
            rt_kprintf("eth1: link is up\n");
        }
        else
        {
            eth_device_linkchange(&eth_device, RT_FALSE);
            rt_kprintf("eth1: link is down\n");
        }

        R8_ETH_EIR |= RB_ETH_EIR_LINKIF; //清除中断
    }

    rt_interrupt_leave();
}

int rt_hw_eth_init(void)
{
    //使能ETH引脚
    R16_PIN_ANALOG_IE |= RB_PIN_ETH_IE;

    //进入安全访问模式
    R8_SAFE_ACCESS_SIG = 0x57;
    R8_SAFE_ACCESS_SIG = 0xA8;
    //打开以太网时钟
    R8_SLP_CLK_OFF1 &= (~RB_SLP_CLK_ETH);
    //打开以太网电源
    R8_SLP_POWER_CTRL &= (~RB_SLP_ETH_PWR_DN);
    //退出安全访问模式
    R8_SAFE_ACCESS_SIG = 0x00;

    //开启以太网中断
    R8_ETH_EIE |= RB_ETH_EIE_INTIE;
    //启用以太网接收中断
    R8_ETH_EIE |= RB_ETH_EIE_RXIE;
    //R8_ETH_EIE |= RB_ETH_EIE_RXERIE;
    //启用以太网发送中断
    R8_ETH_EIE |= RB_ETH_EIR_TXIF;
    R8_ETH_EIE |= RB_ETH_EIR_TXERIF;
    //启用Link变化中断
    R8_ETH_EIE |= RB_ETH_EIE_LINKIE;
    //启用内置的50欧姆阻抗匹配电阻
    R8_ETH_EIE |= RB_ETH_EIE_R_EN50;

    //配置接收过滤模式
    R8_ETH_ERXFCON = RB_ETH_ERXFCON_ANDOR | RB_ETH_ERXFCON_CRCEN;

    //设置发送dma
    R16_ETH_ETXST = (uint32_t)eth_dma_tx_buf;
    //设置接收dma
    R16_ETH_ERXST = (uint32_t)eth_dma_rx_buf;
    //设置最大接收长度
    R16_ETH_MAMXFL = sizeof(eth_dma_rx_buf);

    //使能MAC层接收
    R8_ETH_MACON1 |= RB_ETH_MACON1_MARXEN;
    //开启硬件CRC
    R8_ETH_MACON2 |= RB_ETH_MACON2_TXCRCEN;
    //所有短包填充0至60字节，再4字节 CRC
    R8_ETH_MACON2 |= 0x20;
    //使能接收
    R8_ETH_ECON1 |= RB_ETH_ECON1_RXEN;

    //开启中断
    NVIC_EnableIRQ(ETH_IRQn);

    //设置回调函数
    eth_device.parent.init       = eth_init;
    eth_device.parent.open       = eth_open;
    eth_device.parent.close      = eth_close;
    eth_device.parent.read       = eth_read;
    eth_device.parent.write      = eth_write;
    eth_device.parent.control    = eth_control;
    eth_device.parent.user_data  = RT_NULL;
    eth_device.eth_rx            = eth_rx;
    eth_device.eth_tx            = eth_tx;

    return eth_device_init(&(eth_device), "e0");
}
INIT_DEVICE_EXPORT(rt_hw_eth_init);
#endif /* BSP_USING_ETH */
