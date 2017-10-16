/*
 * File      : drv_emac.c
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-08     Yang        the first version
 */

#include <rtthread.h>
#include "lwipopts.h"
#include <netif/ethernetif.h>
#include <board.h>

#include "drv_emac.h"

#include "fsl_iocon.h"
#include "fsl_sctimer.h"
#include "fsl_phy.h"


#define IOCON_PIO_DIGITAL_EN        0x0100u   /*!< Enables digital function */
#define IOCON_PIO_FUNC0               0x00u   /*!< Selects pin function 0 */
#define IOCON_PIO_FUNC1               0x01u   /*!< Selects pin function 1 */
#define IOCON_PIO_FUNC7               0x07u   /*!< Selects pin function 7 */
#define IOCON_PIO_INPFILT_OFF       0x0200u   /*!< Input filter disabled */
#define IOCON_PIO_INV_DI              0x00u   /*!< Input function is not inverted */
#define IOCON_PIO_MODE_INACT          0x00u   /*!< No addition pin function */
#define IOCON_PIO_MODE_PULLUP         0x20u   /*!< Selects pull-up function */
#define IOCON_PIO_OPENDRAIN_DI        0x00u   /*!< Open drain is disabled */
#define IOCON_PIO_SLEW_FAST         0x0400u   /*!< Fast mode, slew rate control is disabled */
#define IOCON_PIO_SLEW_STANDARD       0x00u   /*!< Standard mode, output slew rate control is enabled */
#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in a port 4 */
#define PIN10_IDX                       10u   /*!< Pin number for pin 10 in a port 4 */
#define PIN11_IDX                       11u   /*!< Pin number for pin 11 in a port 4 */
#define PIN12_IDX                       12u   /*!< Pin number for pin 12 in a port 4 */
#define PIN13_IDX                       13u   /*!< Pin number for pin 13 in a port 4 */
#define PIN14_IDX                       14u   /*!< Pin number for pin 14 in a port 4 */
#define PIN15_IDX                       15u   /*!< Pin number for pin 15 in a port 4 */
#define PIN16_IDX                       16u   /*!< Pin number for pin 16 in a port 4 */
#define PIN17_IDX                       17u   /*!< Pin number for pin 17 in a port 0 */
#define PIN26_IDX                       26u   /*!< Pin number for pin 26 in a port 2 */
#define PIN29_IDX                       29u   /*!< Pin number for pin 29 in a port 0 */
#define PIN30_IDX                       30u   /*!< Pin number for pin 30 in a port 0 */
#define PORT0_IDX                        0u   /*!< Port index */
#define PORT2_IDX                        2u   /*!< Port index */
#define PORT4_IDX                        4u   /*!< Port index */


#define EMAC_PHY_AUTO       0
#define EMAC_PHY_10MBIT     1
#define EMAC_PHY_100MBIT    2

#define MAX_ADDR_LEN 6

/* EMAC_RAM_BASE is defined in board.h and the size is 16KB */
#define RX_DESC_BASE        ETH_RAM_BASE
#define RX_STAT_BASE        (RX_DESC_BASE + NUM_RX_FRAG*8)
#define TX_DESC_BASE        (RX_STAT_BASE + NUM_RX_FRAG*8)
#define TX_STAT_BASE        (TX_DESC_BASE + NUM_TX_FRAG*8)
#define RX_BUF_BASE         (TX_STAT_BASE + NUM_TX_FRAG*4)
#define TX_BUF_BASE         (RX_BUF_BASE  + NUM_RX_FRAG*ETH_FRAG_SIZE)

/* RX and TX descriptor and status definitions. */
#define RX_DESC_PACKET(i)   (*(unsigned int *)(RX_DESC_BASE   + 8*i))
#define RX_DESC_CTRL(i)     (*(unsigned int *)(RX_DESC_BASE+4 + 8*i))
#define RX_STAT_INFO(i)     (*(unsigned int *)(RX_STAT_BASE   + 8*i))
#define RX_STAT_HASHCRC(i)  (*(unsigned int *)(RX_STAT_BASE+4 + 8*i))
#define TX_DESC_PACKET(i)   (*(unsigned int *)(TX_DESC_BASE   + 8*i))
#define TX_DESC_CTRL(i)     (*(unsigned int *)(TX_DESC_BASE+4 + 8*i))
#define TX_STAT_INFO(i)     (*(unsigned int *)(TX_STAT_BASE   + 4*i))
#define RX_BUF(i)           (RX_BUF_BASE + ETH_FRAG_SIZE*i)
#define TX_BUF(i)           (TX_BUF_BASE + ETH_FRAG_SIZE*i)

struct lpc_emac
{
    /* inherit from ethernet device */
    struct eth_device parent;

    rt_uint8_t phy_mode;

    /* interface address info. */
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];     /* hw address   */
};
static struct lpc_emac lpc_emac_device;
static struct rt_semaphore sem_lock;
static struct rt_event tx_event;

#if defined(__GNUC__)
#ifndef __ALIGN_END
#define __ALIGN_END __attribute__((aligned(ENET_BUFF_ALIGNMENT)))
#endif
#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN
#endif
#else
#ifndef __ALIGN_END
#define __ALIGN_END
#endif
#ifndef __ALIGN_BEGIN
#if defined(__CC_ARM)
#define __ALIGN_BEGIN __align(ENET_BUFF_ALIGNMENT)
#elif defined(__ICCARM__)
#define __ALIGN_BEGIN
#endif
#endif
#endif

#define ENET_RXBD_NUM (4)
#define ENET_TXBD_NUM (4)
#define PHY_ADDR (0x00U)
#define ENET_LOOP_COUNT (20U)
#define ENET_ALIGN(x, align) ((unsigned int)((x) + ((align)-1)) & (unsigned int)(~(unsigned int)((align)-1)))
#define ENET_BuffSizeAlign(n) ENET_ALIGN(n, ENET_BUFF_ALIGNMENT)

__ALIGN_BEGIN enet_rx_bd_struct_t g_rxBuffDescrip[ENET_RXBD_NUM] __ALIGN_END;
__ALIGN_BEGIN enet_tx_bd_struct_t g_txBuffDescrip[ENET_TXBD_NUM] __ALIGN_END;


uint8_t multicastAddr[6] = {0x01, 0x00, 0x5e, 0x00, 0x01, 0x81};
uint8_t *g_txbuff[ENET_TXBD_NUM];
uint32_t g_txIdx = 0;
uint8_t g_txbuffIdx = 0;
uint8_t g_txGenIdx = 0;
uint8_t g_txCosumIdx = 0;
uint8_t g_txUsed = 0;
uint8_t g_rxGenIdx = 0;
uint32_t g_rxCosumIdx = 0;
uint32_t g_rxbuffer[ENET_RXBD_NUM];


static uint8_t *ENET_RXRead(int32_t *length)
{
    uint32_t control;
    uint8_t *data;
    *length = 0;

    /* Get the Frame size */
    control = ENET_GetRxDescriptor(&g_rxBuffDescrip[g_rxGenIdx]);
    if (!(control & ENET_RXDESCRIP_RD_OWN_MASK))
    {
        if (control & ENET_RXDESCRIP_WR_LD_MASK)
        {
            /* if no error */
            if (control & ENET_RXDESCRIP_WR_ERRSUM_MASK)
            {
                *length = -1;
            }
            else
            {
                *length = control & ENET_RXDESCRIP_WR_PACKETLEN_MASK;
                data = (uint8_t *)g_rxbuffer[g_rxGenIdx];
            }
            g_rxGenIdx = (g_rxGenIdx + 1) % ENET_RXBD_NUM;
        }
    }
    return data;
}

static void ENET_RXClaim(uint8_t* buffer)
{
    if (ENET_GetDmaInterruptStatus(ENET, 0) & kENET_DmaRxBuffUnavail)
    {
        ENET_UpdateRxDescriptor(&g_rxBuffDescrip[g_rxCosumIdx], buffer, NULL, true, false);
        /* Command for rx poll when the dma suspend. */
        ENET_UpdateRxDescriptorTail(ENET, 0, (uint32_t)&g_rxBuffDescrip[ENET_RXBD_NUM]);
    }
    else
    {
        ENET_UpdateRxDescriptor(&g_rxBuffDescrip[g_rxCosumIdx], buffer, NULL, true, false);
    }

    if (buffer)
    {
        g_rxbuffer[g_rxCosumIdx] = (uint32_t)buffer;
    }

    g_rxCosumIdx = (g_rxCosumIdx + 1) % ENET_RXBD_NUM;
}


static status_t ENET_TXQueue(uint8_t *data, uint16_t length)
{
    uint32_t txdescTailAddr;

    /* Fill the descriptor. */
    if (ENET_IsTxDescriptorDmaOwn(&g_txBuffDescrip[g_txGenIdx]))
    {
        return kStatus_Fail;
    }
    ENET_SetupTxDescriptor(&g_txBuffDescrip[g_txGenIdx], data, length, NULL, 0, length, true, false, kENET_FirstLastFlag, 0);

    /* Increase the index. */
    g_txGenIdx = (g_txGenIdx + 1) % ENET_TXBD_NUM;
    g_txUsed++;

    /* Update the transmit tail address. */
    txdescTailAddr = (uint32_t)&g_txBuffDescrip[g_txGenIdx];
    if (!g_txGenIdx)
    {
        txdescTailAddr = (uint32_t)&g_txBuffDescrip[ENET_TXBD_NUM];
    }
    ENET_UpdateTxDescriptorTail(ENET, 0, txdescTailAddr);
    return kStatus_Success;
}

static void ENET_TXReclaim()
{
    if (!ENET_IsTxDescriptorDmaOwn(&g_txBuffDescrip[g_txCosumIdx]) && (g_txUsed > 0))
    {
        /* Free tx buffers. */
        free(g_txbuff[g_txCosumIdx]);
        g_txUsed--;
        g_txCosumIdx = (g_txCosumIdx + 1) % ENET_TXBD_NUM;
    }
}

void ETHERNET_IRQHandler(void)
{
    /* Check for the interrupt source type. */
    /* DMA CHANNEL 0. */
    uint32_t status;

    /* enter interrupt */
    rt_interrupt_enter();

    status = ENET_GetDmaInterruptStatus(ENET, 0);
    if (status)
    {
        if (status & kENET_DmaRx)
        {
            /* a frame has been received */
            eth_device_ready(&(lpc_emac_device.parent));
        }
        if (status & kENET_DmaTx)
        {
            /* set event */
            rt_event_send(&tx_event, 0x01);
        }

        /* Clear the interrupt. */
        ENET_ClearDmaInterruptStatus(ENET, 0, status);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}

static rt_err_t lpc_emac_init(rt_device_t dev)
{
    int32_t status, index;
    void *buff;
    phy_speed_t speed;
    phy_duplex_t duplex;
    enet_config_t config;
    bool link = false;
    uint32_t timedelay;
    uint32_t refClock = 50000000; /* 50MHZ for rmii reference clock. */

    for (index = 0; index < ENET_RXBD_NUM; index++)
    {
        /* This is for rx buffers, static alloc and dynamic alloc both ok. use as your wish. */
        buff = rt_malloc(ENET_FRAME_MAX_FRAMELEN);
        if (buff)
        {
            g_rxbuffer[index] = (uint32_t)buff;
        }
        else
        {
            rt_kprintf("Mem Alloc fail\r\n");
        }
    }

    /* prepare the buffer configuration. */
    enet_buffer_config_t buffConfig =
    {
        ENET_RXBD_NUM,
        ENET_TXBD_NUM,
        &g_txBuffDescrip[0],
        &g_txBuffDescrip[0],
        &g_rxBuffDescrip[0],
        &g_rxBuffDescrip[4],
        &g_rxbuffer[0],
        ENET_BuffSizeAlign(ENET_FRAME_MAX_FRAMELEN),
    };

    {
        const uint32_t port0_pin17_config = (
                                                IOCON_PIO_FUNC7 |                                        /* Pin is configured as ENET_TXD1 */
                                                IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                                IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                                IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                                IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                                IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                                IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                            );
        IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN17_IDX, port0_pin17_config); /* PORT0 PIN17 (coords: E14) is configured as ENET_TXD1 */
        const uint32_t port2_pin26_config = (
                                                IOCON_PIO_FUNC0 |                                        /* Pin is configured as PIO2_26 */
                                                IOCON_PIO_MODE_PULLUP |                                  /* Selects pull-up function */
                                                IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                                IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                                IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                                IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                                IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                            );
        IOCON_PinMuxSet(IOCON, PORT2_IDX, PIN26_IDX, port2_pin26_config); /* PORT2 PIN26 (coords: H11) is configured as PIO2_26 */
        const uint32_t port4_pin10_config = (
                                                IOCON_PIO_FUNC1 |                                        /* Pin is configured as ENET_RX_DV */
                                                IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                                IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                                IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                                IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                                IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                                IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                            );
        IOCON_PinMuxSet(IOCON, PORT4_IDX, PIN10_IDX, port4_pin10_config); /* PORT4 PIN10 (coords: B9) is configured as ENET_RX_DV */
        const uint32_t port4_pin11_config = (
                                                IOCON_PIO_FUNC1 |                                        /* Pin is configured as ENET_RXD0 */
                                                IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                                IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                                IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                                IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                                IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                                IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                            );
        IOCON_PinMuxSet(IOCON, PORT4_IDX, PIN11_IDX, port4_pin11_config); /* PORT4 PIN11 (coords: A9) is configured as ENET_RXD0 */
        const uint32_t port4_pin12_config = (
                                                IOCON_PIO_FUNC1 |                                        /* Pin is configured as ENET_RXD1 */
                                                IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                                IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                                IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                                IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                                IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                                IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                            );
        IOCON_PinMuxSet(IOCON, PORT4_IDX, PIN12_IDX, port4_pin12_config); /* PORT4 PIN12 (coords: A6) is configured as ENET_RXD1 */
        const uint32_t port4_pin13_config = (
                                                IOCON_PIO_FUNC1 |                                        /* Pin is configured as ENET_TX_EN */
                                                IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                                IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                                IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                                IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                                IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                                IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                            );
        IOCON_PinMuxSet(IOCON, PORT4_IDX, PIN13_IDX, port4_pin13_config); /* PORT4 PIN13 (coords: B6) is configured as ENET_TX_EN */
        const uint32_t port4_pin14_config = (
                                                IOCON_PIO_FUNC1 |                                        /* Pin is configured as ENET_RX_CLK */
                                                IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                                IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                                IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                                IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                                IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                                IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                            );
        IOCON_PinMuxSet(IOCON, PORT4_IDX, PIN14_IDX, port4_pin14_config); /* PORT4 PIN14 (coords: B5) is configured as ENET_RX_CLK */
        const uint32_t port4_pin15_config = (
                                                IOCON_PIO_FUNC1 |                                        /* Pin is configured as ENET_MDC */
                                                IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                                IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                                IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                                IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                                IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                                IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                            );
        IOCON_PinMuxSet(IOCON, PORT4_IDX, PIN15_IDX, port4_pin15_config); /* PORT4 PIN15 (coords: A4) is configured as ENET_MDC */
        const uint32_t port4_pin16_config = (
                                                IOCON_PIO_FUNC1 |                                        /* Pin is configured as ENET_MDIO */
                                                IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                                IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                                IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                                IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                                IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                                IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                            );
        IOCON_PinMuxSet(IOCON, PORT4_IDX, PIN16_IDX, port4_pin16_config); /* PORT4 PIN16 (coords: C4) is configured as ENET_MDIO */
        const uint32_t port4_pin8_config = (
                                               IOCON_PIO_FUNC1 |                                        /* Pin is configured as ENET_TXD0 */
                                               IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
                                               IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
                                               IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
                                               IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
                                               IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
                                               IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
                                           );
        IOCON_PinMuxSet(IOCON, PORT4_IDX, PIN8_IDX, port4_pin8_config); /* PORT4 PIN8 (coords: B14) is configured as ENET_TXD0 */
    }

    status = PHY_Init(ENET, PHY_ADDR, 0);
    if (status == kStatus_Success)
    {
        PHY_GetLinkSpeedDuplex(ENET, PHY_ADDR, &speed, &duplex);
        /* Use the actual speed and duplex when phy success to finish the autonegotiation. */
        config.miiSpeed = (enet_mii_speed_t)speed;
        config.miiDuplex = (enet_mii_duplex_t)duplex;
    }
    else
    {
        rt_kprintf("PHY_Init failed!\n");
        return RT_ERROR;
    }

    /* Wait for link up and get the actual PHY link speed. */
    PHY_GetLinkStatus(ENET, PHY_ADDR, &link);
    while (!link)
    {
        rt_kprintf("PHY Wait for link up!\n");
        for (timedelay = 0; timedelay < 0xFFFFFU; timedelay++)
        {
            __ASM("nop");
        }
        PHY_GetLinkStatus(ENET, PHY_ADDR, &link);
    }

    /* Get default configuration 100M RMII. */
    ENET_GetDefaultConfig(&config);

    /* Initialize ENET. */
    ENET_Init(ENET, &config, &lpc_emac_device.dev_addr[0], refClock);

    /* Enable the tx/rx interrupt. */
    ENET_EnableInterrupts(ENET, (kENET_DmaTx | kENET_DmaRx));
    EnableIRQ(ETHERNET_IRQn);

    /* Initialize Descriptor. */
    ENET_DescriptorInit(ENET, &config, &buffConfig);

    /* Active TX/RX. */
    ENET_StartRxTx(ENET, 1, 1);

    return RT_EOK;
}

static rt_err_t lpc_emac_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t lpc_emac_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t lpc_emac_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_size_t lpc_emac_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t lpc_emac_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if (args) rt_memcpy(args, lpc_emac_device.dev_addr, 6);
        else return -RT_ERROR;
        break;

    default :
        break;
    }

    return RT_EOK;
}

/* EtherNet Device Interface */
/* transmit packet. */
rt_err_t lpc_emac_tx(rt_device_t dev, struct pbuf *p)
{
    rt_uint8_t *buffer;
    rt_err_t result;
    rt_uint32_t recved;

    /* lock EMAC device */
    rt_sem_take(&sem_lock, RT_WAITING_FOREVER);

    /* there is no block yet, wait a flag */
    result = rt_event_recv(&tx_event, 0x01, RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR, RT_WAITING_NO, &recved);
    if (result == RT_EOK)
        ENET_TXReclaim();

    /* Create the buffer for zero-copy transmit. */
    buffer = (uint8_t *)malloc(p->tot_len);
    if (buffer)
    {
        /* copy data to tx buffer */
        pbuf_copy_partial(p, buffer, p->tot_len, 0);

        while ((g_txbuffIdx + 1) % ENET_TXBD_NUM == g_txCosumIdx)
        {
            rt_thread_delay(RT_TICK_PER_SECOND / 20);	// 50 ms
        }

        /* Store the buffer for mem free. */
        g_txbuff[g_txbuffIdx] = buffer;
        g_txbuffIdx = (g_txbuffIdx + 1) % ENET_TXBD_NUM;
        /* Send the frame out (wait unitl the descriptor ready). */
        while (ENET_TXQueue(buffer, p->tot_len) != kStatus_Success);
    }

    /* unlock EMAC device */
    rt_sem_release(&sem_lock);

    return RT_EOK;
}

/* reception packet. */
struct pbuf *lpc_emac_rx(rt_device_t dev)
{
    struct pbuf *p;
    uint8_t *data;
    int length;

    /* init p pointer */
    p = RT_NULL;

    /* lock EMAC device */
    rt_sem_take(&sem_lock, RT_WAITING_FOREVER);

    length = 0;
    data = ENET_RXRead(&length);
    if (length > 0)
    {
        void *buffer;
        /* Update the buffers and then we can delivery the previous buffer diectly to
         the application without memcpy. */
        buffer = rt_malloc(ENET_FRAME_MAX_FRAMELEN);
        if (buffer)
        {
            ENET_RXClaim(buffer);
        }
        else
        {
            ENET_RXClaim(NULL);
        }

        /* Do what you want to do with the data and then free the used one. */
        p = pbuf_alloc(PBUF_LINK, length, PBUF_RAM);
        if (p != RT_NULL)
        {
            rt_memcpy(p->payload, data, length);
            p->tot_len = length;
        }
        rt_free(data);
    }
    else if (length < 0)
    {
        ENET_RXClaim(NULL);
    }

    /* unlock EMAC device */
    rt_sem_release(&sem_lock);

    return p;
}

int lpc_emac_hw_init(void)
{
    rt_event_init(&tx_event, "tx_event", RT_IPC_FLAG_FIFO);
    rt_sem_init(&sem_lock, "eth_lock", 1, RT_IPC_FLAG_FIFO);

    /* set autonegotiation mode */
    lpc_emac_device.phy_mode = EMAC_PHY_AUTO;

    // OUI 00-60-37 NXP Semiconductors
    lpc_emac_device.dev_addr[0] = 0x00;
    lpc_emac_device.dev_addr[1] = 0x60;
    lpc_emac_device.dev_addr[2] = 0x37;
    /* set mac address: (only for test) */
    lpc_emac_device.dev_addr[3] = 0x12;
    lpc_emac_device.dev_addr[4] = 0x34;
    lpc_emac_device.dev_addr[5] = 0x56;

    lpc_emac_device.parent.parent.init      = lpc_emac_init;
    lpc_emac_device.parent.parent.open      = lpc_emac_open;
    lpc_emac_device.parent.parent.close     = lpc_emac_close;
    lpc_emac_device.parent.parent.read      = lpc_emac_read;
    lpc_emac_device.parent.parent.write     = lpc_emac_write;
    lpc_emac_device.parent.parent.control   = lpc_emac_control;
    lpc_emac_device.parent.parent.user_data = RT_NULL;

    lpc_emac_device.parent.eth_rx           = lpc_emac_rx;
    lpc_emac_device.parent.eth_tx           = lpc_emac_tx;

    eth_device_init(&(lpc_emac_device.parent), "e0");
    return 0;
}
INIT_DEVICE_EXPORT(lpc_emac_hw_init);
