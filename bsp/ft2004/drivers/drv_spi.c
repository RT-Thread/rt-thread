/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-25 14:01:29
 * @LastEditTime: 2021-05-26 15:42:52
 * @Description:  This files is for
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "drv_spi.h"
#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include "ft_spi.h"
#include "ft_mux.h"
#include "ft_trace.h"
#include "ft_generic_timer.h"

#ifdef BSP_USE_SPI

#define DRV_DEBUG
#define LOG_TAG "drv.spi"
#include <drv_log.h>

typedef void (*spi_cs_handler_t)(const rt_bool_t select);
typedef struct
{
    FSpi_Ctrl_t spi_ctrl;
    struct rt_spi_bus spi_bus;
    rt_uint16_t spi_cs_pin;
    spi_cs_handler_t spi_cs_handler;
} ft2004_spi_class;

void ft2004_spi_cs(const rt_bool_t select);
static ft2004_spi_class spi_obj = {
    .spi_cs_handler = ft2004_spi_cs,
    .spi_ctrl = {
        .CtrlId = SPI_CTRL_ID_0,
        .DevId = SPI_DEV_ID_0,
        .IsReady = FALSE,
        .CsPin = 5, /* use pin 5 in gpio group a as cs signal pin */
    },
};
static const FSpi_Conf_t spi_conf[NUM_OF_SPI_CTRL] =
    {
        {
            .DevAddr = {0x00, 0x00, 0x00, 0x00},
            .DevAddrLen = SPI_4_BYTE_ADDR,
            .WorkMode = SPI_CTRL_MASTER_MODE,
            /* mode 2 CPOL = 1, CPHA = 0 */
            .Cpol = SPI_CTRL_CPOL_HIGH,
            .Cpha = SPI_CTRL_CPHA_1EDGE,
            .BaudRDiv = SPI_SCKDV_4,
        },
        {
            .DevAddr = {0x00, 0x00, 0x00, 0x00},
            .DevAddrLen = SPI_4_BYTE_ADDR,
            .WorkMode = SPI_CTRL_MASTER_MODE,
            .Cpol = SPI_CTRL_CPOL_HIGH,
            .Cpha = SPI_CTRL_CPHA_1EDGE,
            .BaudRDiv = SPI_SCKDV_MAX,
        }};

inline static ft2004_spi_class *ft2004_spi_get_class()
{
    return &spi_obj;
}

inline static FSpi_Ctrl_t *ft2004_spi_get_ctrl()
{
    return &(ft2004_spi_get_class()->spi_ctrl);
}

static const FSpi_Conf_t *ft2004_lookup_conf(FT_IN FSpi_CtrlId_t CtrlId)
{
    return &spi_conf[CtrlId];
}

void ft2004_spi_cs(const rt_bool_t select)
{
    FSpi_Ctrl_t *ctrl_p = ft2004_spi_get_ctrl();
    FSpi_SelectSlave(ctrl_p, ctrl_p->DevId, (bool_t)select);
}

/**spi flash operations***/
u32 ft2004_spi_transcation(const u8 tx_data, u8 *rx_data_p)
{
    FSpi_Ctrl_t *ctrl_p = ft2004_spi_get_ctrl();
    u32 ret = ERR_SPI_OK;

    ret = FSpi_ReadWriteByte(ctrl_p, tx_data, rx_data_p);
    return ret;
}
/**spi flash operations***/

static rt_err_t ft2004_spi_init(struct rt_spi_configuration *cfg)
{
    FSpi_Ctrl_t *ctrl_p = ft2004_spi_get_ctrl();
    FSpi_DevId_t dev_id;
    u32 ret = ERR_SPI_OK;

    //RT_ASSERT(cfg != RT_NULL);
    RT_ASSERT(ctrl_p != RT_NULL);
    dev_id = ctrl_p->DevId;

    /* get spi flash default config */
    ctrl_p->Config = *(ft2004_lookup_conf(dev_id));

    /* change config according to inputs, cfg could be RT_NULL */

    /* reset ctrl block */
    ctrl_p->IsReady = FALSE;

    /* set spi pin mux */
    Ft_setSpiMux(ctrl_p->CtrlId);

    /* init spi ctrl */
    ret = FSpi_Init(ctrl_p);

    if (ERR_SPI_OK == ret)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}

static rt_uint32_t spi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    rt_size_t message_length, loop;
    rt_uint8_t *recv_buf;
    const rt_uint8_t *send_buf;
    u32 tx_rx_result = ERR_SPI_OK;
    spi_cs_handler_t cs_handler = ft2004_spi_get_class()->spi_cs_handler;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    if (message->cs_take && cs_handler)
    {
        cs_handler(TRUE);
    }

    message_length = message->length;
    recv_buf = message->recv_buf;
    send_buf = message->send_buf;

    /* handle msg */
    for (loop = 0; loop < message_length; loop++)
    {
        /* start data exchange */
        if ((message->recv_buf) && (message->send_buf))
        {
            /* need tx and rx */
            tx_rx_result |= ft2004_spi_transcation(*send_buf, recv_buf);
            send_buf++;
            recv_buf++;
        }
        else if (message->send_buf)
        {
            /* tx only */
            tx_rx_result |= ft2004_spi_transcation(*send_buf, RT_NULL);
            send_buf++;
        }
        else
        {
            /* rx only */
            tx_rx_result |= ft2004_spi_transcation(SPI_DUMMY_TX_DATA, recv_buf);
            recv_buf++;
        }
    }

    if (ERR_SPI_OK != tx_rx_result)
    {
        LOG_E("spi transfer error : 0x%x", tx_rx_result);
        message->length = 0;
    }
    else
    {
    }

    if (message->cs_release && cs_handler)
    {
        cs_handler(FALSE);
    }

    return message->length;
}

static rt_err_t spi_configure(struct rt_spi_device *device,
                              struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    return ft2004_spi_init(configuration);
}

static const struct rt_spi_ops ft2004_spi_ops =
    {
        .configure = spi_configure,
        .xfer = spi_xfer,
};

/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_uint16_t cs_gpio_pin)
{
    rt_err_t result;
    struct rt_spi_device *spi_device;
    ft2004_spi_class *spi_class = ft2004_spi_get_class();

    RT_ASSERT(spi_class != RT_NULL);

    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);

    result = rt_spi_bus_attach_device(spi_device, device_name, bus_name, RT_NULL);

    LOG_I("attach result 0x%x", result);

    if (result != RT_EOK)
    {
        if (spi_device)
        {
            rt_free(spi_device);
        }
    }
    return result;
}

static int rt_hw_spi_bus_init(void)
{
    rt_err_t result;
    ft2004_spi_class *spi_class = ft2004_spi_get_class();

    LOG_I("init spi ctrl");
    spi_class->spi_bus.parent.user_data = &spi_class->spi_bus;
    result = rt_spi_bus_register(&spi_class->spi_bus, SPI_BUS_NAME, &ft2004_spi_ops);
    return result;
}

int rt_hw_spi_init(void)
{
    return rt_hw_spi_bus_init();
}
INIT_BOARD_EXPORT(rt_hw_spi_init);

static void rthw_spi_delay(u32 delayCnt)
{
    Ft_GenericTimer_UsDelay(delayCnt);
}

/************spi flash operatiosn implemented for sample test****************/
/* definition of s25fs maunfactor id */
typedef struct
{
    u8 Mid;
    u8 MemoryType;
    u8 Density;
    u8 RemainBytes;
    u8 PhySectArch;
    u8 FamilyID;
} ft2004_manuid_t;

/* definition of cmd for s25fs */
#define S25FS_ENABLE_WR 0x06
#define S25FS_DISABLE_WR 0x04
#define S25FS_READ_ID 0x9F
#define S25FS_READ_4BYTE_ADD 0x13
#define S25FS_ERASE_4BYTE_ADD 0x21
#define S25FS_READ_STATUS_1 0x05
#define S25FS_READ_FLASH_PARAM 0x5A

static void ft2004_dump_manuid(const ft2004_manuid_t *pId)
{
    rt_kprintf("0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\r\n",
               pId->Mid, pId->MemoryType, pId->Density, pId->RemainBytes,
               pId->PhySectArch, pId->FamilyID);
}

static u32 ft2004_read_in_4byte_addr(const u32 ReadAddr, const u32 BytesToRead, u8 *pBuf)
{
    u32 ret = ERR_SPI_OK;
    u32 loop;

    RT_ASSERT(RT_NULL != pBuf);

    ft2004_spi_cs(TRUE);
    ret |= ft2004_spi_transcation(S25FS_READ_4BYTE_ADD, RT_NULL);
    /* only 4-bytes address, MSB first */
    ret |= ft2004_spi_transcation((u8)(ReadAddr >> 24), RT_NULL);
    ret |= ft2004_spi_transcation((u8)(ReadAddr >> 16), RT_NULL);
    ret |= ft2004_spi_transcation((u8)(ReadAddr >> 8), RT_NULL);
    ret |= ft2004_spi_transcation((u8)ReadAddr, RT_NULL);
    /* read out data */
    for (loop = 0; loop < BytesToRead; loop++)
    {
        ret |= ft2004_spi_transcation(SPI_DUMMY_TX_DATA, pBuf + loop);
        if (ERR_SPI_OK != ret)
        {
            break;
        }
    }
    ft2004_spi_cs(FALSE);
    return ret;
}

u32 ft2004_spi_enable_wr(const bool_t enable)
{
    u32 ret = ERR_SPI_OK;
    ft2004_spi_cs(TRUE);
    if (enable)
    {
        ret |= ft2004_spi_transcation(S25FS_ENABLE_WR, RT_NULL);
    }
    else
    {
        ret |= ft2004_spi_transcation(S25FS_DISABLE_WR, RT_NULL);
    }
    ft2004_spi_cs(FALSE);
    return ret;
}

u32 ft2004_erase_sector_in_4byte_addr(const u32 sector_addr)
{
    u32 Ret = ERR_SPI_OK;

    ft2004_spi_enable_wr(TRUE);
    LOG_I("erase sector 0x%x", Ret);
    if (ERR_SPI_OK != Ret)
    {
        return Ret;
    }

    ft2004_spi_cs(TRUE);
    Ret |= ft2004_spi_transcation(S25FS_ERASE_4BYTE_ADD, RT_NULL);
    Ret |= ft2004_spi_transcation((u8)(sector_addr >> 24), RT_NULL);
    Ret |= ft2004_spi_transcation((u8)(sector_addr >> 16), RT_NULL);
    Ret |= ft2004_spi_transcation((u8)(sector_addr >> 8), RT_NULL);
    Ret |= ft2004_spi_transcation((u8)(sector_addr), RT_NULL);
    ft2004_spi_cs(FALSE);

    return Ret;
}

u32 ft2004_spi_read_params(const u32 Addr)
{
    u32 Ret = ERR_SPI_OK;
    u8 dat[8] = {0};
    u32 loop;

    ft2004_spi_cs(TRUE);
    Ret |= ft2004_spi_transcation(S25FS_READ_FLASH_PARAM, RT_NULL);
    Ret |= ft2004_spi_transcation((u8)(Addr >> 16), RT_NULL);
    Ret |= ft2004_spi_transcation((u8)(Addr >> 8), RT_NULL);
    Ret |= ft2004_spi_transcation((u8)(Addr), RT_NULL);
    for (loop = 0; loop < 8; loop++)
    {
        Ret |= ft2004_spi_transcation(SPI_DUMMY_TX_DATA, dat + loop);
        rt_kprintf("%d: 0x%x", loop, *(dat + loop));
    }

    ft2004_spi_cs(FALSE);
    return Ret;
}

static u32 ft2004_spi_readid_for_test(ft2004_manuid_t *pId)
{
    FSpi_Ctrl_t *ctrl_p = ft2004_spi_get_ctrl();
    u32 ret = ERR_SPI_OK;

    if (!ctrl_p->IsReady)
    {
        return ERR_SPI_NOT_READY;
    }

    RT_ASSERT(RT_NULL != pId);

    ft2004_spi_cs(TRUE);

    /* shifting the command code “90H” followed by a 24-bit address */
    ret |= ft2004_spi_transcation(S25FS_READ_ID, RT_NULL);

    /* Manufacturer ID and the Device ID are shifted out */
    ret |= ft2004_spi_transcation(SPI_DUMMY_TX_DATA, &pId->Mid);
    ret |= ft2004_spi_transcation(SPI_DUMMY_TX_DATA, &pId->MemoryType);
    ret |= ft2004_spi_transcation(SPI_DUMMY_TX_DATA, &pId->Density);
    ret |= ft2004_spi_transcation(SPI_DUMMY_TX_DATA, &pId->RemainBytes);
    ret |= ft2004_spi_transcation(SPI_DUMMY_TX_DATA, &pId->PhySectArch);
    ret |= ft2004_spi_transcation(SPI_DUMMY_TX_DATA, &pId->FamilyID);
    ft2004_spi_cs(FALSE);

    if (ERR_SPI_OK == ret)
    {
        ft2004_dump_manuid(pId);
    }

    return ret;
}

static void spi_9f_s25fs_sample(int argc, char *argv[])
{
    ft2004_manuid_t dev_id;
    u32 ret = ERR_SPI_OK;
    u32 delay = SPI_TIMEOUT * 10;

    rt_kprintf("test s25fs spi flash\r\n");
    ret |= ft2004_spi_init(RT_NULL);
    ret |= ft2004_spi_readid_for_test(&dev_id);

    rt_kprintf("result is: 0x%x \r\n", ret);
    while (--delay)
    {
        rthw_spi_delay(10);
    }
}
MSH_CMD_EXPORT(spi_9f_s25fs_sample, "spi s25fs cmd 9fH sample");

static u8 read_buf[256];
static void spi_5a_s25fs_sample(int argc, char *argv[])
{
    u32 ret = ERR_SPI_OK;
    u32 delay = SPI_TIMEOUT * 10;
    u32 read_addr = 0x0000;

    rt_kprintf("test s25fs spi flash\r\n");
    ret |= ft2004_spi_init(RT_NULL);
    ret |= ft2004_spi_read_params(read_addr);
    ret |= ft2004_read_in_4byte_addr(read_addr, 256, read_buf);
    rt_kprintf("result is: 0x%x \r\n", ret);
    while (--delay)
    {
        rthw_spi_delay(10);
    }
}
MSH_CMD_EXPORT(spi_5a_s25fs_sample, "spi s25fs cmd 5aH sample");

#endif
