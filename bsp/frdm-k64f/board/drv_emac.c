/*
 * COPYRIGHT (C) 2018, Real-Thread Information Technology Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-07-15     Bernard      The first version
 */

#include <board.h>
#include <rtthread.h>
#include "drv_emac.h"

#if defined(RT_USING_LWIP)

#include <finsh.h>
#include <stdint.h>
#include <netif/ethernetif.h>
#include <lwip/opt.h>

#include "MK64F12.h"
#include "fsl_port.h"
#include "fsl_enet.h"
#include "fsl_phy.h"

//#define DRV_EMAC_DEBUG
//#define DRV_EMAC_RX_DUMP
//#define DRV_EMAC_TX_DUMP

#ifdef DRV_EMAC_DEBUG
#define DEBUG_PRINTF(...)          rt_kprintf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(...)
#endif

#define MAX_ADDR_LEN                6
#define ENET_RX_RING_LEN            (16)
#define ENET_TX_RING_LEN            (8)

#define K64_EMAC_DEVICE(eth)        (struct emac_device*)(eth)

#define ENET_ALIGN(x) \
    ((unsigned int)((x) + ((ENET_BUFF_ALIGNMENT)-1)) & (unsigned int)(~(unsigned int)((ENET_BUFF_ALIGNMENT)-1)))

#define ENET_RXBUFF_SIZE            (ENET_FRAME_MAX_FRAMELEN)
#define ENET_TXBUFF_SIZE            (ENET_FRAME_MAX_FRAMELEN)
#define ENET_ETH_MAX_FLEN           (1522) // recommended size for a VLAN frame

struct emac_device
{
    /* inherit from Ethernet device */
    struct eth_device parent;

    ALIGN(64) enet_rx_bd_struct_t RxBuffDescrip[ENET_RX_RING_LEN];
    ALIGN(64) enet_tx_bd_struct_t TxBuffDescrip[ENET_TX_RING_LEN];
    ALIGN(64) uint8_t RxDataBuff[ENET_RX_RING_LEN * ENET_ALIGN(ENET_RXBUFF_SIZE)];
    ALIGN(64) uint8_t TxDataBuff[ENET_TX_RING_LEN * ENET_ALIGN(ENET_TXBUFF_SIZE)];

    enet_handle_t enet_handle;
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];         /* MAC address  */
    struct rt_semaphore tx_wait;
};
static struct emac_device _emac;

static void setup_k64_io_enet(void)
{
    port_pin_config_t configENET = {0};

#ifndef FEATURE_UVISOR
    /* Disable MPU only when uVisor is not around. */
    SYSMPU->CESR &= ~SYSMPU_CESR_VLD_MASK;
#endif/*FEATURE_UVISOR*/

    /* Affects PORTC_PCR16 register */
    PORT_SetPinMux(PORTC, 16u, kPORT_MuxAlt4);
    /* Affects PORTC_PCR17 register */
    PORT_SetPinMux(PORTC, 17u, kPORT_MuxAlt4);
    /* Affects PORTC_PCR18 register */
    PORT_SetPinMux(PORTC, 18u, kPORT_MuxAlt4);
    /* Affects PORTC_PCR19 register */
    PORT_SetPinMux(PORTC, 19u, kPORT_MuxAlt4);
    /* Affects PORTB_PCR1 register */
    PORT_SetPinMux(PORTB, 1u, kPORT_MuxAlt4);

    configENET.openDrainEnable = kPORT_OpenDrainEnable;
    configENET.mux = kPORT_MuxAlt4;
    configENET.pullSelect = kPORT_PullUp;
    /* Ungate the port clock */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Affects PORTB_PCR0 register */
    PORT_SetPinConfig(PORTB, 0u, &configENET);

    /* Affects PORTA_PCR13 register */
    PORT_SetPinMux(PORTA, 13u, kPORT_MuxAlt4);
    /* Affects PORTA_PCR12 register */
    PORT_SetPinMux(PORTA, 12u, kPORT_MuxAlt4);
    /* Affects PORTA_PCR14 register */
    PORT_SetPinMux(PORTA, 14u, kPORT_MuxAlt4);
    /* Affects PORTA_PCR5 register */
    PORT_SetPinMux(PORTA, 5u, kPORT_MuxAlt4);
    /* Affects PORTA_PCR16 register */
    PORT_SetPinMux(PORTA, 16u, kPORT_MuxAlt4);
    /* Affects PORTA_PCR17 register */
    PORT_SetPinMux(PORTA, 17u, kPORT_MuxAlt4);
    /* Affects PORTA_PCR15 register */
    PORT_SetPinMux(PORTA, 15u, kPORT_MuxAlt4);
    /* Affects PORTA_PCR28 register */
    PORT_SetPinMux(PORTA, 28u, kPORT_MuxAlt4);
}

static void setup_enet_clock_init(void)
{
    CLOCK_EnableClock(kCLOCK_PortC);
    CLOCK_EnableClock(kCLOCK_PortB);

    /* Select the Ethernet timestamp clock source */
    CLOCK_SetEnetTime0Clock(0x2);
}

static void enet_mac_rx_isr(struct emac_device* emac)
{
    rt_err_t result;

    result = eth_device_ready(&(_emac.parent));
    if( result != RT_EOK )
    {
        DEBUG_PRINTF("RX err =%d\n", result );
    }
}

static void enet_mac_tx_isr(struct emac_device* emac)
{
    rt_sem_release(&emac->tx_wait);
}

static void ethernet_callback(ENET_Type *base, enet_handle_t *handle, enet_event_t event, void *param)
{
    struct emac_device* emac = param;

    switch (event)
    {
      case kENET_RxEvent:
        enet_mac_rx_isr(emac);
        break;
      case kENET_TxEvent:
        enet_mac_tx_isr(emac);
        break;
      default:
        break;
    }
}

static rt_err_t k64_emac_init(rt_device_t dev)
{
    struct emac_device* emac = K64_EMAC_DEVICE(dev);
    enet_handle_t * enet_handle = &emac->enet_handle;

    bool link = false;
    uint32_t phyAddr = 0;
    phy_speed_t phy_speed;
    phy_duplex_t phy_duplex;
    uint32_t sysClock;
    enet_buffer_config_t buffCfg;
    enet_config_t config;

    /* initialize config according to emac device */
    setup_enet_clock_init();
    /* enable iomux and clock */
    setup_k64_io_enet();

    /* prepare the buffer configuration. */
    buffCfg.rxBdNumber = ENET_RX_RING_LEN;                     /* Receive buffer descriptor number. */
    buffCfg.txBdNumber = ENET_TX_RING_LEN;                     /* Transmit buffer descriptor number. */
    buffCfg.rxBuffSizeAlign = ENET_ALIGN(ENET_RXBUFF_SIZE); /* Aligned receive data buffer size. */
    buffCfg.txBuffSizeAlign = ENET_ALIGN(ENET_TXBUFF_SIZE); /* Aligned transmit data buffer size. */
    buffCfg.rxBdStartAddrAlign = emac->RxBuffDescrip; /* Aligned receive buffer descriptor start address. */
    buffCfg.txBdStartAddrAlign = emac->TxBuffDescrip; /* Aligned transmit buffer descriptor start address. */
    buffCfg.rxBufferAlign = emac->RxDataBuff; /* Receive data buffer start address. */
    buffCfg.txBufferAlign = emac->TxDataBuff; /* Transmit data buffer start address. */

    sysClock = CLOCK_GetFreq(kCLOCK_CoreSysClk);
    DEBUG_PRINTF("sysClock: %d\n", sysClock);

    ENET_GetDefaultConfig(&config);

    PHY_Init(ENET, 0, CLOCK_GetFreq(kCLOCK_CoreSysClk));
    if (PHY_GetLinkStatus(ENET, phyAddr, &link) == kStatus_Success)
    {
        if (link)
        {
            DEBUG_PRINTF("phy link up\n");
            /* Get link information from PHY */
            PHY_GetLinkSpeedDuplex(ENET, phyAddr, &phy_speed, &phy_duplex);

            /* Change the MII speed and duplex for actual link status. */
            config.miiSpeed = (enet_mii_speed_t)phy_speed;
            config.miiDuplex = (enet_mii_duplex_t)phy_duplex;
            config.interrupt = kENET_RxFrameInterrupt | kENET_TxFrameInterrupt;
        }
        else
        {
            DEBUG_PRINTF("phy link down\n");
        }
        config.rxMaxFrameLen = ENET_ETH_MAX_FLEN;
        config.macSpecialConfig = kENET_ControlFlowControlEnable;
        config.txAccelerConfig = 0;
        config.rxAccelerConfig = kENET_RxAccelMacCheckEnabled;

        ENET_Init(ENET, enet_handle, &config, &buffCfg, emac->dev_addr, sysClock);
        ENET_SetCallback(enet_handle, ethernet_callback, emac);
        ENET_ActiveRead(ENET);
    }
    else
    {
        DEBUG_PRINTF("read phy failed\n");
    }

    return RT_EOK;
}

static rt_err_t k64_emac_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t k64_emac_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t k64_emac_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_size_t k64_emac_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t k64_emac_control(rt_device_t dev, int cmd, void *args)
{
    struct emac_device *emac;

    DEBUG_PRINTF("k64_emac_control\n");

    emac = K64_EMAC_DEVICE(dev);
    RT_ASSERT(emac != RT_NULL);

    switch(cmd)
    {
    case NIOCTL_GADDR:
        /* get MAC address */
        if(args) rt_memcpy(args, emac->dev_addr, 6);
        else return -RT_ERROR;
        break;

    default :
        break;
    }

    return RT_EOK;
}

static rt_err_t k64_emac_tx(rt_device_t dev, struct pbuf* p)
{
    rt_err_t result = RT_EOK;

    struct emac_device *emac = K64_EMAC_DEVICE(dev);
    enet_handle_t * enet_handle = &emac->enet_handle;

    RT_ASSERT(p != NULL);

    DEBUG_PRINTF("k64_emac_tx: %d\n", p->len);

    emac = K64_EMAC_DEVICE(dev);
    RT_ASSERT(emac != RT_NULL);

#ifdef DRV_EMAC_RX_DUMP
    {
        int i;
        uint8_t * buf;
        buf = (uint8_t *)p->payload;
        for (i = 0; i < p->len; i++)
        {
            DEBUG_PRINTF("%02X ", buf[i]);
            if (i % 16 == 15)
                DEBUG_PRINTF("\n");
        }
        DEBUG_PRINTF("\n");
    }

#endif

    do
    {
        result = ENET_SendFrame(ENET, enet_handle, p->payload, p->len);

        if (result == kStatus_ENET_TxFrameBusy)
        {
            rt_sem_take(&emac->tx_wait, RT_WAITING_FOREVER);
        }

    } while (result == kStatus_ENET_TxFrameBusy);

    return RT_EOK;
}

struct pbuf *k64_emac_rx(rt_device_t dev)
{
    uint32_t length = 0;
    status_t status;
    enet_data_error_stats_t eErrStatic;

    struct pbuf* p = RT_NULL;
    struct emac_device *emac = K64_EMAC_DEVICE(dev);
    enet_handle_t * enet_handle = &emac->enet_handle;

    RT_ASSERT(emac != RT_NULL);
    DEBUG_PRINTF("k64_emac_rx\n");

    /* Get the Frame size */
    status = ENET_GetRxFrameSize(enet_handle, &length);

    if (status == kStatus_ENET_RxFrameError)
    {
        /* Update the received buffer when error happened. */
        /* Get the error information of the received g_frame. */
        ENET_GetRxErrBeforeReadFrame(enet_handle, &eErrStatic);
        /* update the receive buffer. */
        ENET_ReadFrame(ENET, enet_handle, NULL, 0);

        DEBUG_PRINTF("receive frame faild\n");

        return p;
    }

    /* Call ENET_ReadFrame when there is a received frame. */
    if (length != 0)
    {
        /* Received valid frame. Deliver the rx buffer with the size equal to length. */
        p = pbuf_alloc(PBUF_RAW, length, PBUF_POOL);
    }

    if (p != NULL)
    {
        status = ENET_ReadFrame(ENET, enet_handle, p->payload, length);
        if (status == kStatus_Success)
        {
#ifdef DRV_EMAC_RX_DUMP
            uint8_t *buf;
            int i;

            DEBUG_PRINTF(" A frame received. the length:%d\n", p->len);
            buf = (uint8_t *)p->payload;
            for (i = 0; i < p->len; i++)
            {
                DEBUG_PRINTF("%02X ", buf[i]);
                if (i % 16 == 15)
                    DEBUG_PRINTF("\n");
            }
            DEBUG_PRINTF("\n");
#endif
        }
        else
        {
            DEBUG_PRINTF(" A frame read failed\n");
            pbuf_free(p);
        }
    }

    return p;
}

int drv_emac_hw_init(void)
{
    /* use the test MAC address */
    _emac.dev_addr[0] = 0x00;
    _emac.dev_addr[1] = 0x04;
    _emac.dev_addr[2] = 0x9f;
    _emac.dev_addr[3] = 0xc4;
    _emac.dev_addr[4] = 0x44;
    _emac.dev_addr[5] = 0x22;

    _emac.parent.parent.init       = k64_emac_init;
    _emac.parent.parent.open       = k64_emac_open;
    _emac.parent.parent.close      = k64_emac_close;
    _emac.parent.parent.read       = k64_emac_read;
    _emac.parent.parent.write      = k64_emac_write;
    _emac.parent.parent.control    = k64_emac_control;
    _emac.parent.parent.user_data  = RT_NULL;

    _emac.parent.eth_rx     = k64_emac_rx;
    _emac.parent.eth_tx     = k64_emac_tx;

    /* init tx semaphore */
    rt_sem_init(&_emac.tx_wait, "tx_wait", ENET_TX_RING_LEN - 1, RT_IPC_FLAG_FIFO);

    /* register ETH device */
    eth_device_init(&(_emac.parent), "e0");

    return 0;
}
INIT_DEVICE_EXPORT(drv_emac_hw_init);

#ifdef DRV_EMAC_DEBUG

long k64_dump_tx_bd(void)
{
    int i;

    enet_tx_bd_struct_t *txbd = _emac.TxBuffDescrip;

    for (i = 0; i < ENET_RX_RING_LEN; i++)
    {
        DEBUG_PRINTF("status: %04X,  length: %04X, data: %08X\n", txbd[i].control, txbd[i].length, (uint32_t)txbd[i].buffer);
    }

    return 0;
}
FINSH_FUNCTION_EXPORT(k64_dump_tx_bd, dump all receive buffer descriptor);
MSH_CMD_EXPORT(k64_dump_tx_bd, dump all receive buffer descriptor);

long k64_dump_rx_bd(void)
{
    int i;
    enet_rx_bd_struct_t *rxbd = _emac.RxBuffDescrip;

    for (i = 0; i < ENET_RX_RING_LEN; i++)
    {
        DEBUG_PRINTF("bd:%08X, ", (void *)&rxbd[i]);
        //rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, (void *)&rxbd[i], sizeof(enet_rx_bd_struct_t));
        DEBUG_PRINTF("status:%04X,  length:%04X, data:%08X ", rxbd[i].control, rxbd[i].length, (uint32_t)rxbd[i].buffer);
#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
        DEBUG_PRINTF("ce:%04X/%04X/%04X ", rxbd[i].controlExtend0, rxbd[i].controlExtend1, rxbd[i].controlExtend2);
        DEBUG_PRINTF("crc:%04X, len:%04X, type:%04X, ts:%04X", rxbd[i].payloadCheckSum, rxbd[i].headerLength, rxbd[i].protocolTyte, rxbd[i].timestamp);
#endif
        DEBUG_PRINTF("\n");
    }

    return 0;
}
FINSH_FUNCTION_EXPORT(k64_dump_rx_bd, dump all receive buffer descriptor);
MSH_CMD_EXPORT(k64_dump_rx_bd, dump all receive buffer descriptor);
#endif

#endif
