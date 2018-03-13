/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-06-08     tanek        first implementation
 */
#include <rtthread.h>
#include "board.h"
#include <rtdevice.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#include "fsl_enet.h"
#include "fsl_gpio.h"
#include "fsl_iomuxc.h"
#include "fsl_phy.h"

#ifdef RT_USING_LWIP

#include <netif/ethernetif.h>
#include "lwipopts.h"

#define ENET_RXBD_NUM (4)
#define ENET_TXBD_NUM (4)
#define ENET_RXBUFF_SIZE (ENET_FRAME_MAX_FRAMELEN)
#define ENET_TXBUFF_SIZE (ENET_FRAME_MAX_FRAMELEN)

#define PHY_ADDRESS     0x02u

/* debug option */
//#define ETH_RX_DUMP
//#define ETH_TX_DUMP

#define DBG_ENABLE
#define DBG_SECTION_NAME    "[ETH]"
#define DBG_COLOR
#define DBG_LEVEL           DBG_INFO
#include <rtdbg.h>

#define MAX_ADDR_LEN 6

struct rt_imxrt_eth
{
	/* inherit from ethernet device */
	struct eth_device parent;

    enet_handle_t enet_handle;
    ENET_Type *enet_base;
    enet_data_error_stats_t error_statistic;
	rt_uint8_t  dev_addr[MAX_ADDR_LEN];			/* hw address	*/

    rt_bool_t tx_is_waiting;
    struct rt_semaphore tx_wait;

    enet_mii_speed_t speed;
    enet_mii_duplex_t duplex;
};

ALIGN(ENET_BUFF_ALIGNMENT) enet_tx_bd_struct_t g_txBuffDescrip[ENET_TXBD_NUM] SECTION("NonCacheable");
ALIGN(ENET_BUFF_ALIGNMENT) rt_uint8_t g_txDataBuff[ENET_TXBD_NUM][RT_ALIGN(ENET_TXBUFF_SIZE, ENET_BUFF_ALIGNMENT)];

ALIGN(ENET_BUFF_ALIGNMENT) enet_rx_bd_struct_t g_rxBuffDescrip[ENET_RXBD_NUM] SECTION("NonCacheable");
ALIGN(ENET_BUFF_ALIGNMENT) rt_uint8_t g_rxDataBuff[ENET_RXBD_NUM][RT_ALIGN(ENET_RXBUFF_SIZE, ENET_BUFF_ALIGNMENT)];

static struct rt_imxrt_eth imxrt_eth_device;

void _enet_rx_callback(struct rt_imxrt_eth * eth)
{
    rt_err_t result;

    ENET_DisableInterrupts(eth->enet_base, kENET_RxFrameInterrupt);

    result = eth_device_ready(&(eth->parent));
    if( result != RT_EOK )
        rt_kprintf("RX err =%d\n", result );
}

void _enet_tx_callback(struct rt_imxrt_eth * eth)
{
    if (eth->tx_is_waiting == RT_TRUE)
    {
        eth->tx_is_waiting = RT_FALSE;
        rt_sem_release(&eth->tx_wait);
    }
}

void _enet_callback(ENET_Type *base, enet_handle_t *handle, enet_event_t event, void *userData)
{
    switch(event)
    {
    case kENET_RxEvent:

        _enet_rx_callback((struct rt_imxrt_eth *)userData);
        break;

    case kENET_TxEvent:
        _enet_tx_callback((struct rt_imxrt_eth *)userData);
        break;

    case kENET_ErrEvent:
        //rt_kprintf("kENET_ErrEvent\n");
        break;

    case kENET_WakeUpEvent:
        //rt_kprintf("kENET_WakeUpEvent\n");
        break;

    case kENET_TimeStampEvent:
        //rt_kprintf("kENET_TimeStampEvent\n");
        break;

    case kENET_TimeStampAvailEvent:
        //rt_kprintf("kENET_TimeStampAvailEvent \n");
        break;

    default:
        //rt_kprintf("unknow error\n");
        break;
    }
}

static void _enet_io_init(void)
{
  CLOCK_EnableClock(kCLOCK_Iomuxc);          /* iomuxc clock (iomuxc_clk_enable): 0x03u */

  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_B0_09_GPIO1_IO09,        /* GPIO_AD_B0_09 is configured as GPIO1_IO09 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_B0_10_GPIO1_IO10,        /* GPIO_AD_B0_10 is configured as GPIO1_IO10 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_B0_12_LPUART1_TX,        /* GPIO_AD_B0_12 is configured as LPUART1_TX */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_B0_13_LPUART1_RX,        /* GPIO_AD_B0_13 is configured as LPUART1_RX */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B1_04_ENET_RX_DATA00,       /* GPIO_B1_04 is configured as ENET_RX_DATA00 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B1_05_ENET_RX_DATA01,       /* GPIO_B1_05 is configured as ENET_RX_DATA01 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B1_06_ENET_RX_EN,           /* GPIO_B1_06 is configured as ENET_RX_EN */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B1_07_ENET_TX_DATA00,       /* GPIO_B1_07 is configured as ENET_TX_DATA00 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B1_08_ENET_TX_DATA01,       /* GPIO_B1_08 is configured as ENET_TX_DATA01 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B1_09_ENET_TX_EN,           /* GPIO_B1_09 is configured as ENET_TX_EN */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B1_10_ENET_REF_CLK,         /* GPIO_B1_10 is configured as ENET_REF_CLK */
      1U);                                    /* Software Input On Field: Force input path of pad GPIO_B1_10 */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_B1_11_ENET_RX_ER,           /* GPIO_B1_11 is configured as ENET_RX_ER */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_EMC_40_ENET_MDC,            /* GPIO_EMC_40 is configured as ENET_MDC */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_EMC_41_ENET_MDIO,           /* GPIO_EMC_41 is configured as ENET_MDIO */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_B0_09_GPIO1_IO09,        /* GPIO_AD_B0_09 PAD functional properties : */
      0xB0A9u);                               /* Slew Rate Field: Fast Slew Rate
                                                 Drive Strength Field: R0/5
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Disabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_B0_10_GPIO1_IO10,        /* GPIO_AD_B0_10 PAD functional properties : */
      0xB0A9u);                               /* Slew Rate Field: Fast Slew Rate
                                                 Drive Strength Field: R0/5
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Disabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_B0_12_LPUART1_TX,        /* GPIO_AD_B0_12 PAD functional properties : */
      0x10B0u);                               /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Keeper
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Down
                                                 Hyst. Enable Field: Hysteresis Disabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_B0_13_LPUART1_RX,        /* GPIO_AD_B0_13 PAD functional properties : */
      0x10B0u);                               /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Keeper
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Down
                                                 Hyst. Enable Field: Hysteresis Disabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B1_04_ENET_RX_DATA00,       /* GPIO_B1_04 PAD functional properties : */
      0xB0E9u);                               /* Slew Rate Field: Fast Slew Rate
                                                 Drive Strength Field: R0/5
                                                 Speed Field: max(200MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Disabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B1_05_ENET_RX_DATA01,       /* GPIO_B1_05 PAD functional properties : */
      0xB0E9u);                               /* Slew Rate Field: Fast Slew Rate
                                                 Drive Strength Field: R0/5
                                                 Speed Field: max(200MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Disabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B1_06_ENET_RX_EN,           /* GPIO_B1_06 PAD functional properties : */
      0xB0E9u);                               /* Slew Rate Field: Fast Slew Rate
                                                 Drive Strength Field: R0/5
                                                 Speed Field: max(200MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Disabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B1_07_ENET_TX_DATA00,       /* GPIO_B1_07 PAD functional properties : */
      0xB0E9u);                               /* Slew Rate Field: Fast Slew Rate
                                                 Drive Strength Field: R0/5
                                                 Speed Field: max(200MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Disabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B1_08_ENET_TX_DATA01,       /* GPIO_B1_08 PAD functional properties : */
      0xB0E9u);                               /* Slew Rate Field: Fast Slew Rate
                                                 Drive Strength Field: R0/5
                                                 Speed Field: max(200MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Disabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B1_09_ENET_TX_EN,           /* GPIO_B1_09 PAD functional properties : */
      0xB0E9u);                               /* Slew Rate Field: Fast Slew Rate
                                                 Drive Strength Field: R0/5
                                                 Speed Field: max(200MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Disabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B1_10_ENET_REF_CLK,         /* GPIO_B1_10 PAD functional properties : */
      0x31u);                                 /* Slew Rate Field: Fast Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: low(50MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Disabled
                                                 Pull / Keep Select Field: Keeper
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Down
                                                 Hyst. Enable Field: Hysteresis Disabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_B1_11_ENET_RX_ER,           /* GPIO_B1_11 PAD functional properties : */
      0xB0E9u);                               /* Slew Rate Field: Fast Slew Rate
                                                 Drive Strength Field: R0/5
                                                 Speed Field: max(200MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Disabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_EMC_40_ENET_MDC,            /* GPIO_EMC_40 PAD functional properties : */
      0xB0E9u);                               /* Slew Rate Field: Fast Slew Rate
                                                 Drive Strength Field: R0/5
                                                 Speed Field: max(200MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Disabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_EMC_41_ENET_MDIO,           /* GPIO_EMC_41 PAD functional properties : */
      0xB829u);                               /* Slew Rate Field: Fast Slew Rate
                                                 Drive Strength Field: R0/5
                                                 Speed Field: low(50MHz)
                                                 Open Drain Enable Field: Open Drain Enabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Pull
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                 Hyst. Enable Field: Hysteresis Disabled */


}

static void _enet_clk_init(void)
{
    const clock_enet_pll_config_t config = {true, false, false, 1, 1};
    CLOCK_InitEnetPll(&config);

    IOMUXC_EnableMode(IOMUXC_GPR, kIOMUXC_GPR_ENET1TxClkOutputDir, true);
}

static void _delay(void)
{
    volatile int i = 1000000;

    while (i--)
        i = i;
}

static void _enet_phy_reset_by_gpio(void)
{
    gpio_pin_config_t gpio_config = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};

    GPIO_PinInit(GPIO1, 9, &gpio_config);
    GPIO_PinInit(GPIO1, 10, &gpio_config);
    /* pull up the ENET_INT before RESET. */
    GPIO_WritePinOutput(GPIO1, 10, 1);
    GPIO_WritePinOutput(GPIO1, 9, 0);
    _delay();
    GPIO_WritePinOutput(GPIO1, 9, 1);
}

static void _enet_config(void)
{
    enet_config_t config;
    uint32_t sysClock;

    /* prepare the buffer configuration. */
    enet_buffer_config_t buffConfig = {
        ENET_RXBD_NUM,
        ENET_TXBD_NUM,
        SDK_SIZEALIGN(ENET_RXBUFF_SIZE, ENET_BUFF_ALIGNMENT),
        SDK_SIZEALIGN(ENET_TXBUFF_SIZE, ENET_BUFF_ALIGNMENT),
        &g_rxBuffDescrip[0],
        &g_txBuffDescrip[0],
        &g_rxDataBuff[0][0],
        &g_txDataBuff[0][0],
    };

    /* Get default configuration. */
    /*
     * config.miiMode = kENET_RmiiMode;
     * config.miiSpeed = kENET_MiiSpeed100M;
     * config.miiDuplex = kENET_MiiFullDuplex;
     * config.rxMaxFrameLen = ENET_FRAME_MAX_FRAMELEN;
     */
    ENET_GetDefaultConfig(&config);
    config.interrupt = kENET_TxFrameInterrupt | kENET_RxFrameInterrupt;
    //config.interrupt = 0xFFFFFFFF;
    config.miiSpeed = imxrt_eth_device.speed;
    config.miiDuplex = imxrt_eth_device.duplex;

    /* Set SMI to get PHY link status. */
    sysClock = CLOCK_GetFreq(kCLOCK_AhbClk);

    dbg_log(DBG_LOG, "deinit\n");
    ENET_Deinit(imxrt_eth_device.enet_base);
    dbg_log(DBG_LOG, "init\n");
    ENET_Init(imxrt_eth_device.enet_base, &imxrt_eth_device.enet_handle, &config, &buffConfig, &imxrt_eth_device.dev_addr[0], sysClock);
    dbg_log(DBG_LOG, "set call back\n");
    ENET_SetCallback(&imxrt_eth_device.enet_handle, _enet_callback, &imxrt_eth_device);
    dbg_log(DBG_LOG, "active read\n");
    ENET_ActiveRead(imxrt_eth_device.enet_base);
}

/* initialize the interface */
static rt_err_t rt_imxrt_eth_init(rt_device_t dev)
{
    dbg_log(DBG_LOG, "rt_imxrt_eth_init...\n");
    _enet_config();

    return RT_EOK;
}

static rt_err_t rt_imxrt_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    dbg_log(DBG_LOG, "rt_imxrt_eth_open...\n");
	return RT_EOK;
}

static rt_err_t rt_imxrt_eth_close(rt_device_t dev)
{
    dbg_log(DBG_LOG, "rt_imxrt_eth_close...\n");
	return RT_EOK;
}

static rt_size_t rt_imxrt_eth_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    dbg_log(DBG_LOG, "rt_imxrt_eth_read...\n");
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_size_t rt_imxrt_eth_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    dbg_log(DBG_LOG, "rt_imxrt_eth_write...\n");
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_err_t rt_imxrt_eth_control(rt_device_t dev, int cmd, void *args)
{
    dbg_log(DBG_LOG, "rt_imxrt_eth_control...\n");
	switch(cmd)
	{
	case NIOCTL_GADDR:
		/* get mac address */
		if(args) rt_memcpy(args, imxrt_eth_device.dev_addr, 6);
		else return -RT_ERROR;
		break;

	default :
		break;
	}

	return RT_EOK;
}

/* ethernet device interface */
/* transmit packet. */
rt_err_t rt_imxrt_eth_tx( rt_device_t dev, struct pbuf* p)
{
	rt_err_t result = RT_EOK;
	enet_handle_t * enet_handle = &imxrt_eth_device.enet_handle;

	RT_ASSERT(p != NULL);
    RT_ASSERT(enet_handle != RT_NULL);

	dbg_log(DBG_LOG, "rt_imxrt_eth_tx: %d\n", p->len);

#ifdef ETH_TX_DUMP
	{
		int i;
		uint8_t * buf;
		buf = (uint8_t *)p->payload;
		for (i = 0; i < p->len; i++)
		{
			dbg_log(DBG_LOG, "%02X ", buf[i]);
			if (i % 16 == 15)
				dbg_log(DBG_LOG, "\n");
		}
		dbg_log(DBG_LOG, "\n");
	}
#endif

	do
	{
		result = ENET_SendFrame(imxrt_eth_device.enet_base, enet_handle, p->payload, p->len);

		if (result == kStatus_ENET_TxFrameBusy)
		{
			rt_sem_take(&imxrt_eth_device.tx_wait, RT_WAITING_FOREVER);
		}

	} while (result == kStatus_ENET_TxFrameBusy);

	return RT_EOK;
}

/* reception packet. */
struct pbuf *rt_imxrt_eth_rx(rt_device_t dev)
{
 	uint32_t length = 0;
	status_t status;

	struct pbuf* p = RT_NULL;
	enet_handle_t * enet_handle = &imxrt_eth_device.enet_handle;
    ENET_Type *enet_base = imxrt_eth_device.enet_base;
    enet_data_error_stats_t *error_statistic = &imxrt_eth_device.error_statistic;

	/* Get the Frame size */
	status = ENET_GetRxFrameSize(enet_handle, &length);

	/* Call ENET_ReadFrame when there is a received frame. */
	if (length != 0)
	{
		/* Received valid frame. Deliver the rx buffer with the size equal to length. */
		p = pbuf_alloc(PBUF_RAW, length, PBUF_POOL);

        if (p != NULL)
        {
            status = ENET_ReadFrame(enet_base, enet_handle, p->payload, length);
            if (status == kStatus_Success)
            {
    #ifdef ETH_RX_DUMP
                uint8_t *buf;
                int i;

                ETH_PRINTF("A frame received. the length:%d\n", p->len);
                buf = (uint8_t *)p->payload;
                for (i = 0; i < p->len; i++)
                {
                    dbg_log(DBG_LOG, "%02X ", buf[i]);
                    if (i % 16 == 15)
                        dbg_log(DBG_LOG, "\n");
                }
                dbg_log(DBG_LOG, "\n");
    #endif
                return p;
            }
            else
            {
                dbg_log(DBG_LOG, " A frame read failed\n");
                pbuf_free(p);
            }
        }
        else
        {
            dbg_log(DBG_LOG, " pbuf_alloc faild\n");
        }
	}
	else if (status == kStatus_ENET_RxFrameError)
	{
		dbg_log(DBG_WARNING, "ENET_GetRxFrameSize: kStatus_ENET_RxFrameError\n");
		/* Update the received buffer when error happened. */
		/* Get the error information of the received g_frame. */
		ENET_GetRxErrBeforeReadFrame(enet_handle, error_statistic);
		/* update the receive buffer. */
		ENET_ReadFrame(enet_base, enet_handle, NULL, 0);
	}

    ENET_EnableInterrupts(enet_base, kENET_RxFrameInterrupt);
    return NULL;
}

static void phy_monitor_thread_entry(void *parameter)
{
    
    phy_speed_t speed;
    phy_duplex_t duplex;
    bool link = false;
    
    _enet_phy_reset_by_gpio();

    PHY_Init(imxrt_eth_device.enet_base, PHY_ADDRESS, CLOCK_GetFreq(kCLOCK_AhbClk));
    
    while (1)
    {
        bool new_link = false;
        status_t status = PHY_GetLinkStatus(imxrt_eth_device.enet_base, PHY_ADDRESS, &new_link);
        
        if ((status == kStatus_Success) && (link != new_link))
        {
            link = new_link;
            
            if (link)   // link up
            {
                PHY_GetLinkSpeedDuplex(imxrt_eth_device.enet_base, 
                                       PHY_ADDRESS, &speed, &duplex);
                
                if (kPHY_Speed10M == speed)
                {
                    dbg_log(DBG_LOG, "10M\n");
                }
                else
                {
                    dbg_log(DBG_LOG, "100M\n");
                }
                
                if (kPHY_HalfDuplex == duplex)
                {
                    dbg_log(DBG_LOG, "half dumplex\n");
                }
                else
                {
                    dbg_log(DBG_LOG, "full dumplex\n");
                }
                
                if ((imxrt_eth_device.speed != (enet_mii_speed_t)speed) 
                    || (imxrt_eth_device.duplex != (enet_mii_duplex_t)duplex))
                {
                    imxrt_eth_device.speed = (enet_mii_speed_t)speed; 
                    imxrt_eth_device.duplex = (enet_mii_duplex_t)duplex;
                    
                    dbg_log(DBG_LOG, "link up, and update eth mode.\n");
                    rt_imxrt_eth_init((rt_device_t)&imxrt_eth_device);
                }
                else
                {
                    dbg_log(DBG_LOG, "link up, eth not need re-config.\n");
                }
                dbg_log(DBG_LOG, "link up.\n");
                eth_device_linkchange(&imxrt_eth_device.parent, RT_TRUE);
            }
            else        // link down
            {
                dbg_log(DBG_LOG, "link down.\n");
                eth_device_linkchange(&imxrt_eth_device.parent, RT_FALSE);
            }
        }
        
        rt_thread_delay(RT_TICK_PER_SECOND * 2);
    }
}

static int rt_hw_imxrt_eth_init(void)
{
    rt_err_t state;

    _enet_io_init();
    _enet_clk_init();
    
    /* OUI 00-80-E1 STMICROELECTRONICS. */
    imxrt_eth_device.dev_addr[0] = 0x00;
    imxrt_eth_device.dev_addr[1] = 0x80;
    imxrt_eth_device.dev_addr[2] = 0xE1;
    /* generate MAC addr from 96bit unique ID (only for test). */
    imxrt_eth_device.dev_addr[3] = 0x12;
    imxrt_eth_device.dev_addr[4] = 0x34;
    imxrt_eth_device.dev_addr[5] = 0x56;
    
    imxrt_eth_device.speed = kENET_MiiSpeed100M; 
    imxrt_eth_device.duplex = kENET_MiiFullDuplex;

    imxrt_eth_device.enet_base = ENET;

    imxrt_eth_device.parent.parent.init       = rt_imxrt_eth_init;
    imxrt_eth_device.parent.parent.open       = rt_imxrt_eth_open;
    imxrt_eth_device.parent.parent.close      = rt_imxrt_eth_close;
    imxrt_eth_device.parent.parent.read       = rt_imxrt_eth_read;
    imxrt_eth_device.parent.parent.write      = rt_imxrt_eth_write;
    imxrt_eth_device.parent.parent.control    = rt_imxrt_eth_control;
    imxrt_eth_device.parent.parent.user_data  = RT_NULL;

    imxrt_eth_device.parent.eth_rx     = rt_imxrt_eth_rx;
    imxrt_eth_device.parent.eth_tx     = rt_imxrt_eth_tx;

    dbg_log(DBG_LOG, "sem init: tx_wait\r\n");
    /* init tx semaphore */
    rt_sem_init(&imxrt_eth_device.tx_wait, "tx_wait", 0, RT_IPC_FLAG_FIFO);

    /* register eth device */
    dbg_log(DBG_LOG, "eth_device_init start\r\n");
    state = eth_device_init(&(imxrt_eth_device.parent), "e0");
    if (RT_EOK == state)
    {
        dbg_log(DBG_LOG, "eth_device_init success\r\n");
    }
    else
    {
        dbg_log(DBG_LOG, "eth_device_init faild: %d\r\n", state);
    }
    
    eth_device_linkchange(&imxrt_eth_device.parent, RT_FALSE);
    
    /* start phy monitor */
    {
        rt_thread_t tid;
        tid = rt_thread_create("phy",
                               phy_monitor_thread_entry,
                               RT_NULL,
                               512,
                               RT_THREAD_PRIORITY_MAX - 2,
                               2);
        if (tid != RT_NULL)
            rt_thread_startup(tid);
    }
    
    return state;
}
INIT_DEVICE_EXPORT(rt_hw_imxrt_eth_init);
#endif

#ifdef RT_USING_FINSH
#include <finsh.h>

void phy_read(uint32_t phyReg)
{
    uint32_t data;
    status_t status;

    status = PHY_Read(imxrt_eth_device.enet_base, PHY_ADDRESS, phyReg, &data);
    if (kStatus_Success == status)
    {
        rt_kprintf("PHY_Read: %02X --> %08X", phyReg, data);
    }
    else
    {
        rt_kprintf("PHY_Read: %02X --> faild", phyReg);
    }
}

void phy_write(uint32_t phyReg, uint32_t data)
{
    status_t status;

    status = PHY_Write(imxrt_eth_device.enet_base, PHY_ADDRESS, phyReg, data);
    if (kStatus_Success == status)
    {
        rt_kprintf("PHY_Write: %02X --> %08X\n", phyReg, data);
    }
    else
    {
        rt_kprintf("PHY_Write: %02X --> faild\n", phyReg);
    }
}

void phy_dump(void)
{
    uint32_t data;
    status_t status;

    int i;
    for (i = 0; i < 32; i++)
    {
        status = PHY_Read(imxrt_eth_device.enet_base, PHY_ADDRESS, i, &data);
        if (kStatus_Success != status)
        {
            rt_kprintf("phy_dump: %02X --> faild", i);
            break;
        }

        if (i % 8 == 7)
        {
            rt_kprintf("%02X --> %08X ", i, data);
        }
        else
        {
            rt_kprintf("%02X --> %08X\n", i, data);
        }

    }
}

void enet_reg_dump(void)
{
    ENET_Type *enet_base = imxrt_eth_device.enet_base;

#define DUMP_REG(__REG)  \
    rt_kprintf("%s(%08X): %08X\n", #__REG, (uint32_t)&enet_base->__REG, enet_base->__REG)

	DUMP_REG(EIR);
	DUMP_REG(EIMR);
	DUMP_REG(RDAR);
	DUMP_REG(TDAR);
	DUMP_REG(ECR);
	DUMP_REG(MMFR);
	DUMP_REG(MSCR);
	DUMP_REG(MIBC);
	DUMP_REG(RCR);
	DUMP_REG(TCR);
	DUMP_REG(PALR);
	DUMP_REG(PAUR);
	DUMP_REG(OPD);
	DUMP_REG(TXIC);
	DUMP_REG(RXIC);
	DUMP_REG(IAUR);
	DUMP_REG(IALR);
	DUMP_REG(GAUR);
	DUMP_REG(GALR);
	DUMP_REG(TFWR);
	DUMP_REG(RDSR);
	DUMP_REG(TDSR);
	DUMP_REG(MRBR);
	DUMP_REG(RSFL);
	DUMP_REG(RSEM);
	DUMP_REG(RAEM);
	DUMP_REG(RAFL);
	DUMP_REG(TSEM);
	DUMP_REG(TAEM);
	DUMP_REG(TAFL);
	DUMP_REG(TIPG);
	DUMP_REG(FTRL);
	DUMP_REG(TACC);
	DUMP_REG(RACC);
	DUMP_REG(RMON_T_DROP);
	DUMP_REG(RMON_T_PACKETS);
	DUMP_REG(RMON_T_BC_PKT);
	DUMP_REG(RMON_T_MC_PKT);
	DUMP_REG(RMON_T_CRC_ALIGN);
	DUMP_REG(RMON_T_UNDERSIZE);
	DUMP_REG(RMON_T_OVERSIZE);
	DUMP_REG(RMON_T_FRAG);
	DUMP_REG(RMON_T_JAB);
	DUMP_REG(RMON_T_COL);
	DUMP_REG(RMON_T_P64);
	DUMP_REG(RMON_T_P65TO127);
	DUMP_REG(RMON_T_P128TO255);
	DUMP_REG(RMON_T_P256TO511);
	DUMP_REG(RMON_T_P512TO1023);
	DUMP_REG(RMON_T_P1024TO2047);
	DUMP_REG(RMON_T_P_GTE2048);
	DUMP_REG(RMON_T_OCTETS);
	DUMP_REG(IEEE_T_DROP);
	DUMP_REG(IEEE_T_FRAME_OK);
	DUMP_REG(IEEE_T_1COL);
	DUMP_REG(IEEE_T_MCOL);
	DUMP_REG(IEEE_T_DEF);
	DUMP_REG(IEEE_T_LCOL);
	DUMP_REG(IEEE_T_EXCOL);
	DUMP_REG(IEEE_T_MACERR);
	DUMP_REG(IEEE_T_CSERR);
	DUMP_REG(IEEE_T_SQE);
	DUMP_REG(IEEE_T_FDXFC);
	DUMP_REG(IEEE_T_OCTETS_OK);
	DUMP_REG(RMON_R_PACKETS);
	DUMP_REG(RMON_R_BC_PKT);
	DUMP_REG(RMON_R_MC_PKT);
	DUMP_REG(RMON_R_CRC_ALIGN);
	DUMP_REG(RMON_R_UNDERSIZE);
	DUMP_REG(RMON_R_OVERSIZE);
	DUMP_REG(RMON_R_FRAG);
	DUMP_REG(RMON_R_JAB);
	DUMP_REG(RMON_R_RESVD_0);
	DUMP_REG(RMON_R_P64);
	DUMP_REG(RMON_R_P65TO127);
	DUMP_REG(RMON_R_P128TO255);
	DUMP_REG(RMON_R_P256TO511);
	DUMP_REG(RMON_R_P512TO1023);
	DUMP_REG(RMON_R_P1024TO2047);
	DUMP_REG(RMON_R_P_GTE2048);
	DUMP_REG(RMON_R_OCTETS);
	DUMP_REG(IEEE_R_DROP);
	DUMP_REG(IEEE_R_FRAME_OK);
	DUMP_REG(IEEE_R_CRC);
	DUMP_REG(IEEE_R_ALIGN);
	DUMP_REG(IEEE_R_MACERR);
	DUMP_REG(IEEE_R_FDXFC);
	DUMP_REG(IEEE_R_OCTETS_OK);
	DUMP_REG(ATCR);
	DUMP_REG(ATVR);
	DUMP_REG(ATOFF);
	DUMP_REG(ATPER);
	DUMP_REG(ATCOR);
	DUMP_REG(ATINC);
	DUMP_REG(ATSTMP);
	DUMP_REG(TGSR);
}

void enet_nvic_tog(void)
{
    NVIC_SetPendingIRQ(ENET_IRQn);
}

void enet_rx_stat(void)
{
    enet_data_error_stats_t *error_statistic = &imxrt_eth_device.error_statistic;

#define DUMP_STAT(__VAR)  \
    rt_kprintf("%-25s: %08X\n", #__VAR, error_statistic->__VAR);

    DUMP_STAT(statsRxLenGreaterErr);
    DUMP_STAT(statsRxAlignErr);
    DUMP_STAT(statsRxFcsErr);
    DUMP_STAT(statsRxOverRunErr);
    DUMP_STAT(statsRxTruncateErr);

#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
    DUMP_STAT(statsRxProtocolChecksumErr);
    DUMP_STAT(statsRxIpHeadChecksumErr);
    DUMP_STAT(statsRxMacErr);
    DUMP_STAT(statsRxPhyErr);
    DUMP_STAT(statsRxCollisionErr);
    DUMP_STAT(statsTxErr);
    DUMP_STAT(statsTxFrameErr);
    DUMP_STAT(statsTxOverFlowErr);
    DUMP_STAT(statsTxLateCollisionErr);
    DUMP_STAT(statsTxExcessCollisionErr);
    DUMP_STAT(statsTxUnderFlowErr);
    DUMP_STAT(statsTxTsErr);
#endif

}

void enet_buf_info(void)
{

    int i = 0;
    for (i = 0; i < ENET_RXBD_NUM; i++)
    {
        rt_kprintf("%d: length: %-8d, control: %04X, buffer:%p\n",
                    i,
                    g_rxBuffDescrip[i].length,
                    g_rxBuffDescrip[i].control,
                    g_rxBuffDescrip[i].buffer);
    }

    for (i = 0; i < ENET_TXBD_NUM; i++)
    {
        rt_kprintf("%d: length: %-8d, control: %04X, buffer:%p\n",
                    i,
                    g_txBuffDescrip[i].length,
                    g_txBuffDescrip[i].control,
                    g_txBuffDescrip[i].buffer);
    }
}

FINSH_FUNCTION_EXPORT(phy_read, read phy register);
FINSH_FUNCTION_EXPORT(phy_write, write phy register);
FINSH_FUNCTION_EXPORT(phy_dump, dump phy registers);
FINSH_FUNCTION_EXPORT(enet_reg_dump, dump enet registers);
FINSH_FUNCTION_EXPORT(enet_nvic_tog, toggle enet nvic pendding bit);
FINSH_FUNCTION_EXPORT(enet_rx_stat, dump enet rx statistic);
FINSH_FUNCTION_EXPORT(enet_buf_info, dump enet tx and tx buffer descripter);

#endif
