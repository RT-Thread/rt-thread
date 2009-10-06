/*
 * File      : eth_cl.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-05     Bernard      eth interface driver for STM32F107 CL
 */

#include <rtthread.h>
#include "Libraries/STM32_ETH_Driver/inc/stm32_eth.h"

#include <netif/ethernetif.h>
#include "lwipopts.h"

#define DP83848_PHY        /* Ethernet pins mapped on STM3210C-EVAL Board */
#define PHY_ADDRESS       0x01 /* Relative to STM3210C-EVAL Board */

#define ETH_RXBUFNB        8
#define ETH_TXBUFNB        2
ETH_InitTypeDef ETH_InitStructure;
ETH_DMADESCTypeDef  DMARxDscrTab[ETH_RXBUFNB], DMATxDscrTab[ETH_TXBUFNB];
rt_uint8_t Rx_Buff[ETH_RXBUFNB][ETH_MAX_PACKET_SIZE], Tx_Buff[ETH_TXBUFNB][ETH_MAX_PACKET_SIZE];

#define MAX_ADDR_LEN 6
struct rt_stm32_eth
{
	/* inherit from ethernet device */
	struct eth_device parent;

	/* interface address info. */
	rt_uint8_t  dev_addr[MAX_ADDR_LEN];			/* hw address	*/
};
static struct rt_stm32_eth stm32_eth_device;

/* interrupt service routine */
void rt_stm32_eth_isr(int irqno)
{
    rt_uint32_t status;

    if (status) // if receive packet
    {
        rt_err_t result;

        /* a frame has been received */
        result = eth_device_ready(&(stm32_eth_device.parent));
        RT_ASSERT(result == RT_EOK);
    }

    if (status) // if finished packet transmission
    {
    }
}

/* RT-Thread Device Interface */
/* initialize the interface */
static rt_err_t rt_stm32_eth_init(rt_device_t dev)
{
    vu32 Value = 0;

    /* Reset ETHERNET on AHB Bus */
    ETH_DeInit();

    /* Software reset */
    ETH_SoftwareReset();

    /* Wait for software reset */
    while(ETH_GetSoftwareResetStatus()==SET);

    /* ETHERNET Configuration ------------------------------------------------------*/
    /* Call ETH_StructInit if you don't like to configure all ETH_InitStructure parameter */
    ETH_StructInit(&ETH_InitStructure);

    /* Fill ETH_InitStructure parametrs */
    /*------------------------   MAC   -----------------------------------*/
    ETH_InitStructure.ETH_AutoNegotiation = ETH_AutoNegotiation_Enable  ;
    ETH_InitStructure.ETH_Speed = ETH_Speed_100M;
    ETH_InitStructure.ETH_LoopbackMode = ETH_LoopbackMode_Disable;
    ETH_InitStructure.ETH_Mode = ETH_Mode_FullDuplex;
    ETH_InitStructure.ETH_RetryTransmission = ETH_RetryTransmission_Disable;
    ETH_InitStructure.ETH_AutomaticPadCRCStrip = ETH_AutomaticPadCRCStrip_Disable;
    ETH_InitStructure.ETH_ReceiveAll = ETH_ReceiveAll_Enable;
    ETH_InitStructure.ETH_BroadcastFramesReception = ETH_BroadcastFramesReception_Disable;
    ETH_InitStructure.ETH_PromiscuousMode = ETH_PromiscuousMode_Disable;
    ETH_InitStructure.ETH_MulticastFramesFilter = ETH_MulticastFramesFilter_Perfect;
    ETH_InitStructure.ETH_UnicastFramesFilter = ETH_UnicastFramesFilter_Perfect;

    /* Configure ETHERNET */
    Value = ETH_Init(&ETH_InitStructure, PHY_ADDRESS);

    /* Initialize Tx Descriptors list: Chain Mode */
    ETH_DMATxDescChainInit(DMATxDscrTab, &Tx_Buff[0][0], ETH_TXBUFNB);
    /* Initialize Rx Descriptors list: Chain Mode  */
    ETH_DMARxDescChainInit(DMARxDscrTab, &Rx_Buff[0][0], ETH_RXBUFNB);

    /* Enable MAC and DMA transmission and reception */
    ETH_Start();

    return RT_EOK;
}

static rt_err_t rt_stm32_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t rt_stm32_eth_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_size_t rt_stm32_eth_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_size_t rt_stm32_eth_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_err_t rt_stm32_eth_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
	switch(cmd)
	{
	case NIOCTL_GADDR:
		/* get mac address */
		if(args) rt_memcpy(args, stm32_eth_device.dev_addr, 6);
		else return -RT_ERROR;
		break;

	default :
		break;
	}

	return RT_EOK;
}

/* ethernet device interface */
/* transmit packet. */
rt_err_t rt_stm32_eth_tx( rt_device_t dev, struct pbuf* p)
{
	struct pbuf* q;
	rt_uint32_t len;
	rt_uint8_t* ptr;

	for (q = p; q != NULL; q = q->next)
	{
		len = q->len;
		ptr = q->payload;

		/* write data to device */
	}

	return RT_EOK;
}

/* reception packet. */
struct pbuf *rt_stm32_eth_rx(rt_device_t dev)
{
    struct pbuf* p;
	rt_uint32_t len;

    /* init p pointer */
    p = RT_NULL;

    if (1) // if there is packet in device
    {
        /* get one packet length */
        len = 0; // packet length

        /* allocate buffer */
        p = pbuf_alloc(PBUF_LINK, len, PBUF_RAM);

        if (p != RT_NULL)
        {
            rt_uint8_t* data;
            struct pbuf* q;

            for (q = p; q != RT_NULL; q= q->next)
            {
                data = q->payload;
                len = q->len;

                /* read data from device */
            }
        }
    }
    else
    {
        /* restore interrupt */
    }

    return p;
}

void rt_hw_stm32_eth_init()
{
	stm32_eth_device.parent.parent.init       = rt_stm32_eth_init;
	stm32_eth_device.parent.parent.open       = rt_stm32_eth_open;
	stm32_eth_device.parent.parent.close      = rt_stm32_eth_close;
	stm32_eth_device.parent.parent.read       = rt_stm32_eth_read;
	stm32_eth_device.parent.parent.write      = rt_stm32_eth_write;
	stm32_eth_device.parent.parent.control    = rt_stm32_eth_control;
	stm32_eth_device.parent.parent.private    = RT_NULL;

	stm32_eth_device.parent.eth_rx     = rt_stm32_eth_rx;
	stm32_eth_device.parent.eth_tx     = rt_stm32_eth_tx;

	eth_device_init(&(stm32_eth_device.parent), "e0");
}
