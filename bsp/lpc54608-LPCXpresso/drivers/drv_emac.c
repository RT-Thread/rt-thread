/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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

#define DEBUG
//#define ETH_RX_DUMP
//#define ETH_TX_DUMP
#define ETH_STATISTICS

#ifdef DEBUG
#define ETH_PRINTF          rt_kprintf
#else
#define ETH_PRINTF(...)
#endif

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

#define MAX_ADDR_LEN                     6u
#define ENET_RXBD_NUM                    4u
#define ENET_TXBD_NUM                    4u

#define ENET_ALIGN(x) \
    ((unsigned int)((x) + ((ENET_BUFF_ALIGNMENT)-1)) & (unsigned int)(~(unsigned int)((ENET_BUFF_ALIGNMENT)-1)))

#define ENET_RXBUFF_SIZE                (ENET_FRAME_MAX_FRAMELEN)
#define ENET_TXBUFF_SIZE                (ENET_FRAME_MAX_FRAMELEN)

struct lpc_emac
{
    /* inherit from ethernet device */
    struct eth_device parent;
    struct rt_semaphore tx_wait;

    ENET_Type *base;
    enet_handle_t handle;

    /* interface address info. */
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];     /* hw address   */
    uint32_t phyAddr;

    uint8_t RxBuffDescrip[ENET_RXBD_NUM * sizeof(enet_rx_bd_struct_t) + ENET_BUFF_ALIGNMENT];
    uint8_t TxBuffDescrip[ENET_TXBD_NUM * sizeof(enet_tx_bd_struct_t) + ENET_BUFF_ALIGNMENT];
    uint8_t RxDataBuff[ENET_RXBD_NUM * ENET_ALIGN(ENET_RXBUFF_SIZE) + ENET_BUFF_ALIGNMENT];
    uint8_t TxDataBuff[ENET_TXBD_NUM * ENET_ALIGN(ENET_TXBUFF_SIZE) + ENET_BUFF_ALIGNMENT];
    uint8_t txIdx;
};

static struct lpc_emac lpc_emac_device;

#ifdef ETH_STATISTICS
static uint32_t isr_rx_counter = 0;
static uint32_t isr_tx_counter = 0;
#endif

static inline enet_rx_bd_struct_t *get_rx_desc(uint32_t index)
{
    return (enet_rx_bd_struct_t *)ENET_ALIGN(&lpc_emac_device.RxBuffDescrip[index * sizeof(enet_rx_bd_struct_t)]);
}

static inline enet_tx_bd_struct_t *get_tx_desc(uint32_t index)
{
    return (enet_tx_bd_struct_t *)ENET_ALIGN(&lpc_emac_device.TxBuffDescrip[index * sizeof(enet_tx_bd_struct_t)]);
}

#if defined(ETH_RX_DUMP) ||  defined(ETH_TX_DUMP)
static void packet_dump(const char * msg, const struct pbuf* p)
{
    const struct pbuf* q;
    rt_uint32_t i,j;
    rt_uint8_t *ptr;

    rt_kprintf("%s %d byte\n", msg, p->tot_len);

    i=0;
    for(q=p; q != RT_NULL; q= q->next)
    {
        ptr = q->payload;

        for(j=0; j<q->len; j++)
        {
            if( (i%8) == 0 )
            {
                rt_kprintf("  ");
            }
            if( (i%16) == 0 )
            {
                rt_kprintf("\r\n");
            }
            rt_kprintf("%02x ",*ptr);

            i++;
            ptr++;
        }
    }

    rt_kprintf("\n\n");
}
#else
#define packet_dump(...)
#endif /* dump */

static void ethernet_callback(ENET_Type *base, enet_handle_t *handle, enet_event_t event, uint8_t channel, void *param)
{
    switch (event)
    {
        case kENET_RxIntEvent:
#ifdef ETH_STATISTICS
            isr_rx_counter++;
#endif
            /* a frame has been received */
            eth_device_ready(&(lpc_emac_device.parent));
            break;
        case kENET_TxIntEvent:
#ifdef ETH_STATISTICS
            isr_tx_counter++;
#endif
            /* set event */
            rt_sem_release(&lpc_emac_device.tx_wait);
            break;
        default:
            break;
    }
}

static void lcp_emac_io_init(void)
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

static rt_err_t lpc_emac_phy_init(phy_speed_t * speed, phy_duplex_t * duplex)
{
    bool link = false;
    int32_t status;

    RT_ASSERT(speed != NULL);
    RT_ASSERT(duplex != NULL);

    status = PHY_Init(lpc_emac_device.base, lpc_emac_device.phyAddr, 0);
    if (status != kStatus_Success)
    {
        /* Half duplex. */
        *duplex = kPHY_HalfDuplex;
        /* 10M speed. */
        *speed = kPHY_Speed10M;

        eth_device_linkchange(&lpc_emac_device.parent, RT_FALSE);

        ETH_PRINTF("PHY_Init failed!\n");
        return -RT_ERROR;
    }

    /* Wait for link up and get the actual PHY link speed. */
    PHY_GetLinkStatus(lpc_emac_device.base, lpc_emac_device.phyAddr, &link);
    while (!link)
    {
        uint32_t timedelay;
        ETH_PRINTF("PHY Wait for link up!\n");
        for (timedelay = 0; timedelay < 0xFFFFFU; timedelay++)
        {
            __ASM("nop");
        }
        PHY_GetLinkStatus(lpc_emac_device.base, lpc_emac_device.phyAddr, &link);
    }

    PHY_GetLinkSpeedDuplex(lpc_emac_device.base, lpc_emac_device.phyAddr, speed, duplex);

    eth_device_linkchange(&lpc_emac_device.parent, RT_TRUE);

    return RT_EOK;
}

static rt_err_t lpc_emac_init(rt_device_t dev)
{
    int i;
    phy_speed_t speed;
    phy_duplex_t duplex;
    enet_config_t config;
    enet_buffer_config_t buffCfg;
    uint32_t rxBufferStartAddr[ENET_RXBD_NUM];

    lcp_emac_io_init();

    lpc_emac_phy_init(&speed, &duplex);

    /* calculate start addresses of all rx buffers */
    for (i = 0; i < ENET_RXBD_NUM; i++)
    {
        rxBufferStartAddr[i] = ENET_ALIGN(&lpc_emac_device.RxDataBuff[i * ENET_ALIGN(ENET_RXBUFF_SIZE)]);
    }

    buffCfg.rxRingLen = ENET_RXBD_NUM;
    buffCfg.txRingLen = ENET_TXBD_NUM;
    buffCfg.txDescStartAddrAlign = get_tx_desc(0U);
    buffCfg.txDescTailAddrAlign  = get_tx_desc(0U);
    buffCfg.rxDescStartAddrAlign = get_rx_desc(0U);
    buffCfg.rxDescTailAddrAlign  = get_rx_desc(ENET_RXBD_NUM);
    buffCfg.rxBufferStartAddr    = rxBufferStartAddr;
    buffCfg.rxBuffSizeAlign      = ENET_ALIGN(ENET_RXBUFF_SIZE);

    /* Get default configuration 100M RMII. */
    ENET_GetDefaultConfig(&config);
    /* Use the actual speed and duplex when phy success to finish the autonegotiation. */
    config.miiSpeed = (enet_mii_speed_t)speed;
    config.miiDuplex = (enet_mii_duplex_t)duplex;

    ETH_PRINTF("Auto negotiation, Speed: ");
    if (config.miiSpeed == kENET_MiiSpeed100M)
        ETH_PRINTF("100M");
    else
        ETH_PRINTF("10M");

    ETH_PRINTF(", Duplex: ");
    if (config.miiSpeed == kENET_MiiSpeed100M)
        ETH_PRINTF("Full\n");
    else
        ETH_PRINTF("Half\n");

    /* Initialize lpc_emac_device.base. */
    ENET_Init(lpc_emac_device.base, &config, &lpc_emac_device.dev_addr[0], CLOCK_GetFreq(kCLOCK_CoreSysClk));

    /* Enable the tx/rx interrupt. */
    ENET_EnableInterrupts(lpc_emac_device.base, (kENET_DmaTx | kENET_DmaRx));
    ENET_CreateHandler(lpc_emac_device.base, &lpc_emac_device.handle, &config, &buffCfg, ethernet_callback, NULL);

    /* Initialize Descriptor. */
    ENET_DescriptorInit(lpc_emac_device.base, &config, &buffCfg);

    /* Active TX/RX. */
    ENET_StartRxTx(lpc_emac_device.base, 1, 1);

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

static rt_ssize_t lpc_emac_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t lpc_emac_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
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
    rt_err_t result = RT_EOK;
    enet_handle_t * enet_handle = &lpc_emac_device.handle;
    ENET_Type *enet_base = lpc_emac_device.base;
    uint8_t * data;

    uint16_t    len;

    RT_ASSERT(p != NULL);
    RT_ASSERT(enet_handle != RT_NULL);

    if (p->tot_len > ENET_TXBUFF_SIZE)
    {
        return -RT_ERROR;
    }

    packet_dump("TX dump", p);

    /* get free tx buffer */
    {
        rt_err_t result;
        result = rt_sem_take(&lpc_emac_device.tx_wait, RT_TICK_PER_SECOND/10);
        if (result != RT_EOK)
        {
            return -RT_ERROR;
        }
    }

    //  fix RxDataBuff -> TxDataBuff, ENET_RXBUFF_SIZE -> ENET_TXBUFF_SIZE
    data = (uint8_t *)ENET_ALIGN(&lpc_emac_device.TxDataBuff[lpc_emac_device.txIdx * ENET_ALIGN(ENET_TXBUFF_SIZE)]);
    len = pbuf_copy_partial(p, data, p->tot_len, 0);
    lpc_emac_device.txIdx = (lpc_emac_device.txIdx + 1) / ENET_TXBD_NUM;

    // fix 'p->len' to 'len', avoid send wrong partial packet.
    result = ENET_SendFrame(enet_base, enet_handle, data, len);

    if ((result == kStatus_ENET_TxFrameFail) || (result == kStatus_ENET_TxFrameOverLen) || (result == kStatus_ENET_TxFrameBusy))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

/* reception packet. */
struct pbuf *lpc_emac_rx(rt_device_t dev)
{
    uint32_t length = 0;
    status_t status;

    struct pbuf* p = RT_NULL;
    enet_handle_t * enet_handle = &lpc_emac_device.handle;
    ENET_Type *enet_base = lpc_emac_device.base;

    /* Get the Frame size */
    status = ENET_GetRxFrameSize(enet_base, enet_handle, &length, 0);

    /* Call ENET_ReadFrame when there is a received frame. */
    if (length != 0)
    {
        /* Received valid frame. Deliver the rx buffer with the size equal to length. */
        p = pbuf_alloc(PBUF_RAW, length, PBUF_POOL);

        if (p != NULL)
        {
            status = ENET_ReadFrame(enet_base, enet_handle, p->payload, length, 0);
            if (status == kStatus_Success)
            {
                packet_dump("RX dump", p);
                return p;
            }
            else
            {
                ETH_PRINTF(" A frame read failed\n");
                pbuf_free(p);
            }
        }
        else
        {
            ETH_PRINTF(" pbuf_alloc faild\n");
        }
    }
    else if (status == kStatus_ENET_RxFrameError)
    {
        ETH_PRINTF("ENET_GetRxFrameSize: kStatus_ENET_RxFrameError\n");
        ENET_ReadFrame(enet_base, enet_handle, NULL, 0, 0);
    }

    return NULL;
}

int lpc_emac_hw_init(void)
{
    /* init tx semaphore */
    rt_sem_init(&lpc_emac_device.tx_wait, "tx_wait", ENET_TXBD_NUM, RT_IPC_FLAG_FIFO);

    lpc_emac_device.phyAddr = 0;
    lpc_emac_device.txIdx = 0;
    lpc_emac_device.base = ENET;

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

#ifdef ETH_STATISTICS
int emac_stat(void)
{
    rt_kprintf("enter rx isr coutner : %d\n", isr_rx_counter);
    rt_kprintf("enter tx isr coutner : %d\n", isr_tx_counter);

    return 0;
}
#endif

void phy_dump(void)
{
    status_t PHY_Read(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t *dataPtr);

    int i;

    for (i = 0; i < 31; i++)
    {
        status_t result = kStatus_Success;
        uint32_t reg;

        result = PHY_Read(lpc_emac_device.base, lpc_emac_device.phyAddr, i, &reg);

        if (result == kStatus_Success)
        {
            rt_kprintf("%02d: %08d\n", i, reg);
        }
        else
        {
            rt_kprintf("read register %d faild\n", i);
        }
    }
}

void emac_dump(void)
{
    #define DUMP_REG(__NAME)    \
        rt_kprintf("%-40s, %08x: %08x\n", #__NAME, (uint32_t)&(lpc_emac_device.base->__NAME), lpc_emac_device.base->__NAME)

    DUMP_REG(MAC_CONFIG);
    DUMP_REG(MAC_EXT_CONFIG);
    DUMP_REG(MAC_FRAME_FILTER);
    DUMP_REG(MAC_WD_TIMEROUT);
    DUMP_REG(MAC_VLAN_TAG);
    DUMP_REG(MAC_TX_FLOW_CTRL_Q[0]);
    DUMP_REG(MAC_TX_FLOW_CTRL_Q[1]);
    DUMP_REG(MAC_RX_FLOW_CTRL);
    DUMP_REG(MAC_TXQ_PRIO_MAP);
    DUMP_REG(MAC_RXQ_CTRL[0]);
    DUMP_REG(MAC_RXQ_CTRL[1]);
    DUMP_REG(MAC_RXQ_CTRL[2]);
    DUMP_REG(MAC_INTR_STAT);
    DUMP_REG(MAC_INTR_EN);
    DUMP_REG(MAC_RXTX_STAT);
    DUMP_REG(MAC_PMT_CRTL_STAT);
    DUMP_REG(MAC_RWAKE_FRFLT);
    DUMP_REG(MAC_LPI_CTRL_STAT);
    DUMP_REG(MAC_LPI_TIMER_CTRL);
    DUMP_REG(MAC_LPI_ENTR_TIMR);
    DUMP_REG(MAC_1US_TIC_COUNTR);
    DUMP_REG(MAC_VERSION);
    DUMP_REG(MAC_DBG);
    DUMP_REG(MAC_HW_FEAT[0]);
    DUMP_REG(MAC_HW_FEAT[1]);
    DUMP_REG(MAC_HW_FEAT[2]);
    DUMP_REG(MAC_MDIO_ADDR);
    DUMP_REG(MAC_MDIO_DATA);
    DUMP_REG(MAC_ADDR_HIGH);
    DUMP_REG(MAC_ADDR_LOW);
    DUMP_REG(MAC_TIMESTAMP_CTRL);
    DUMP_REG(MAC_SUB_SCND_INCR);
    DUMP_REG(MAC_SYS_TIME_SCND);
    DUMP_REG(MAC_SYS_TIME_NSCND);
    DUMP_REG(MAC_SYS_TIME_SCND_UPD);
    DUMP_REG(MAC_SYS_TIME_NSCND_UPD);
    DUMP_REG(MAC_SYS_TIMESTMP_ADDEND);
    DUMP_REG(MAC_SYS_TIME_HWORD_SCND);
    DUMP_REG(MAC_SYS_TIMESTMP_STAT);
    DUMP_REG(MAC_TX_TIMESTAMP_STATUS_NANOSECONDS);
    DUMP_REG(MAC_TX_TIMESTAMP_STATUS_SECONDS);
    DUMP_REG(MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND);
    DUMP_REG(MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND);
    DUMP_REG(MTL_OP_MODE);
    DUMP_REG(MTL_INTR_STAT);
    DUMP_REG(MTL_RXQ_DMA_MAP);
    DUMP_REG(DMA_MODE);
    DUMP_REG(DMA_SYSBUS_MODE);
    DUMP_REG(DMA_INTR_STAT);
    DUMP_REG(DMA_DBG_STAT);

    DUMP_REG(MTL_QUEUE[0].MTL_TXQX_OP_MODE);
    DUMP_REG(MTL_QUEUE[0].MTL_TXQX_UNDRFLW);
    DUMP_REG(MTL_QUEUE[0].MTL_TXQX_DBG);
    DUMP_REG(MTL_QUEUE[0].MTL_TXQX_ETS_CTRL);
    DUMP_REG(MTL_QUEUE[0].MTL_TXQX_ETS_STAT);
    DUMP_REG(MTL_QUEUE[0].MTL_TXQX_QNTM_WGHT);
    DUMP_REG(MTL_QUEUE[0].MTL_TXQX_SNDSLP_CRDT);
    DUMP_REG(MTL_QUEUE[0].MTL_TXQX_HI_CRDT);
    DUMP_REG(MTL_QUEUE[0].MTL_TXQX_LO_CRDT);
    DUMP_REG(MTL_QUEUE[0].MTL_TXQX_INTCTRL_STAT);
    DUMP_REG(MTL_QUEUE[0].MTL_RXQX_OP_MODE);
    DUMP_REG(MTL_QUEUE[0].MTL_RXQX_MISSPKT_OVRFLW_CNT);
    DUMP_REG(MTL_QUEUE[0].MTL_RXQX_DBG);
    DUMP_REG(MTL_QUEUE[0].MTL_RXQX_CTRL);

    DUMP_REG(MTL_QUEUE[1].MTL_TXQX_OP_MODE);
    DUMP_REG(MTL_QUEUE[1].MTL_TXQX_UNDRFLW);
    DUMP_REG(MTL_QUEUE[1].MTL_TXQX_DBG);
    DUMP_REG(MTL_QUEUE[1].MTL_TXQX_ETS_CTRL);
    DUMP_REG(MTL_QUEUE[1].MTL_TXQX_ETS_STAT);
    DUMP_REG(MTL_QUEUE[1].MTL_TXQX_QNTM_WGHT);
    DUMP_REG(MTL_QUEUE[1].MTL_TXQX_SNDSLP_CRDT);
    DUMP_REG(MTL_QUEUE[1].MTL_TXQX_HI_CRDT);
    DUMP_REG(MTL_QUEUE[1].MTL_TXQX_LO_CRDT);
    DUMP_REG(MTL_QUEUE[1].MTL_TXQX_INTCTRL_STAT);
    DUMP_REG(MTL_QUEUE[1].MTL_RXQX_OP_MODE);
    DUMP_REG(MTL_QUEUE[1].MTL_RXQX_MISSPKT_OVRFLW_CNT);
    DUMP_REG(MTL_QUEUE[1].MTL_RXQX_DBG);
    DUMP_REG(MTL_QUEUE[1].MTL_RXQX_CTRL);

    DUMP_REG(DMA_CH[0].DMA_CHX_CTRL);
    DUMP_REG(DMA_CH[0].DMA_CHX_TX_CTRL);
    DUMP_REG(DMA_CH[0].DMA_CHX_RX_CTRL);
    DUMP_REG(DMA_CH[0].DMA_CHX_TXDESC_LIST_ADDR);
    DUMP_REG(DMA_CH[0].DMA_CHX_RXDESC_LIST_ADDR);
    DUMP_REG(DMA_CH[0].DMA_CHX_TXDESC_TAIL_PTR);
    DUMP_REG(DMA_CH[0].DMA_CHX_RXDESC_TAIL_PTR);
    DUMP_REG(DMA_CH[0].DMA_CHX_TXDESC_RING_LENGTH);
    DUMP_REG(DMA_CH[0].DMA_CHX_RXDESC_RING_LENGTH);
    DUMP_REG(DMA_CH[0].DMA_CHX_INT_EN);
    DUMP_REG(DMA_CH[0].DMA_CHX_RX_INT_WDTIMER);
    DUMP_REG(DMA_CH[0].DMA_CHX_SLOT_FUNC_CTRL_STAT);
    DUMP_REG(DMA_CH[0].DMA_CHX_CUR_HST_TXDESC);
    DUMP_REG(DMA_CH[0].DMA_CHX_CUR_HST_RXDESC);
    DUMP_REG(DMA_CH[0].DMA_CHX_CUR_HST_TXBUF);
    DUMP_REG(DMA_CH[0].DMA_CHX_CUR_HST_RXBUF);
    DUMP_REG(DMA_CH[0].DMA_CHX_STAT);

    DUMP_REG(DMA_CH[1].DMA_CHX_CTRL);
    DUMP_REG(DMA_CH[1].DMA_CHX_TX_CTRL);
    DUMP_REG(DMA_CH[1].DMA_CHX_RX_CTRL);
    DUMP_REG(DMA_CH[1].DMA_CHX_TXDESC_LIST_ADDR);
    DUMP_REG(DMA_CH[1].DMA_CHX_RXDESC_LIST_ADDR);
    DUMP_REG(DMA_CH[1].DMA_CHX_TXDESC_TAIL_PTR);
    DUMP_REG(DMA_CH[1].DMA_CHX_RXDESC_TAIL_PTR);
    DUMP_REG(DMA_CH[1].DMA_CHX_TXDESC_RING_LENGTH);
    DUMP_REG(DMA_CH[1].DMA_CHX_RXDESC_RING_LENGTH);
    DUMP_REG(DMA_CH[1].DMA_CHX_INT_EN);
    DUMP_REG(DMA_CH[1].DMA_CHX_RX_INT_WDTIMER);
    DUMP_REG(DMA_CH[1].DMA_CHX_SLOT_FUNC_CTRL_STAT);
    DUMP_REG(DMA_CH[1].DMA_CHX_CUR_HST_TXDESC);
    DUMP_REG(DMA_CH[1].DMA_CHX_CUR_HST_RXDESC);
    DUMP_REG(DMA_CH[1].DMA_CHX_CUR_HST_TXBUF);
    DUMP_REG(DMA_CH[1].DMA_CHX_CUR_HST_RXBUF);
    DUMP_REG(DMA_CH[1].DMA_CHX_STAT);
}

void emac_bd_dump(void)
{
    int i;

    rt_kprintf("rx bd dump: \n");
    for (i = 0; i < ENET_RXBD_NUM; i++)
    {
        enet_rx_bd_struct_t * rx_bd = get_rx_desc(i);
        rt_kprintf("buf1: %p, buf2: %p, ctrl: %08x\n",
                        rx_bd->buff1Addr,
                        rx_bd->buff2Addr,
                        rx_bd->control);
    }

    rt_kprintf("tx bd dump: \n");
    for (i = 0; i < ENET_TXBD_NUM; i++)
    {
        enet_tx_bd_struct_t * tx_bd = get_tx_desc(i);
        rt_kprintf("buf1: %p, buf2: %p, len: %08x, ctrl: %08x\n",
                        tx_bd->buff1Addr,
                        tx_bd->buff2Addr,
                        tx_bd->buffLen,
                        tx_bd->controlStat);
    }
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(emac_stat, dump emac stat data);
FINSH_FUNCTION_EXPORT(phy_dump, dump phy registers);
FINSH_FUNCTION_EXPORT(emac_dump, dump emac registers);
FINSH_FUNCTION_EXPORT(emac_bd_dump, dump emac tx and rx descriptor);
#endif
