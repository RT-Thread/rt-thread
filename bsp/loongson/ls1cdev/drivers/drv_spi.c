/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-02     勤为本       first version
 * 2018-06-09     zhuangwei    add spi0 cs0 support,remove msd_init
 */

#include <rtthread.h>
#include "drivers/dev_spi.h"
#include <rthw.h>
#include "drv_spi.h"
#include "ls1c_public.h"
#include "dev_spi_msd.h"
#include "dfs_fs.h"
#include "../libraries/ls1c_pin.h"

#ifdef RT_USING_SPI
#ifdef DEBUG
#define DEBUG_PRINTF(...)           rt_kprintf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(...)
#endif


static rt_err_t configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration);
static rt_uint32_t xfer(struct rt_spi_device *device, struct rt_spi_message *message);


static struct rt_spi_ops ls1c_spi_ops =
{
    .configure  = configure,
    .xfer       = xfer
};


static rt_err_t configure(struct rt_spi_device *device,
                          struct rt_spi_configuration *configuration)
{
    struct rt_spi_bus *spi_bus = NULL;
    struct ls1c_spi *ls1c_spi = NULL;
    unsigned char SPIx = 0;
    void *spi_base = NULL;
    unsigned char cpol = 0;
    unsigned char cpha = 0;
    unsigned char val = 0;

    RT_ASSERT(NULL != device);
    RT_ASSERT(NULL != configuration);

    spi_bus = device->bus;
    ls1c_spi = (struct ls1c_spi *)spi_bus->parent.user_data;
    SPIx = ls1c_spi->SPIx;
    spi_base = ls1c_spi_get_base(SPIx);

    {
        // 使能SPI控制器，master模式，关闭中断
        reg_write_8(0x53, spi_base + LS1C_SPI_SPCR_OFFSET);

        // 清空状态寄存器
        reg_write_8(0xc0, spi_base + LS1C_SPI_SPSR_OFFSET);

        // 1字节产生中断，采样(读)与发送(写)时机同时
        reg_write_8(0x03, spi_base + LS1C_SPI_SPER_OFFSET);

        // 关闭SPI flash
        val = reg_read_8(spi_base + LS1C_SPI_SFC_PARAM_OFFSET);
        val &= 0xfe;
        reg_write_8(val, spi_base + LS1C_SPI_SFC_PARAM_OFFSET);

        // spi flash时序控制寄存器
        reg_write_8(0x05, spi_base + LS1C_SPI_SFC_TIMING_OFFSET);
    }

    // baudrate
    ls1c_spi_set_clock(spi_base, configuration->max_hz);

    // 设置通信模式(时钟极性和相位)
    if (configuration->mode & RT_SPI_CPOL)      // cpol
    {
        cpol = SPI_CPOL_1;
    }
    else
    {
        cpol = SPI_CPOL_0;
    }
    if (configuration->mode & RT_SPI_CPHA)      // cpha
    {
        cpha = SPI_CPHA_1;
    }
    else
    {
        cpha = SPI_CPHA_0;
    }
    ls1c_spi_set_mode(spi_base, cpol, cpha);

    DEBUG_PRINTF("ls1c spi%d configuration\n", SPIx);

    return RT_EOK;
}


static rt_uint32_t xfer(struct rt_spi_device *device,
                        struct rt_spi_message *message)
{
    struct rt_spi_bus *spi_bus = NULL;
    struct ls1c_spi *ls1c_spi = NULL;
    void *spi_base = NULL;
    unsigned char SPIx = 0;
    struct ls1c_spi_cs *ls1c_spi_cs = NULL;
    unsigned char cs = 0;
    rt_uint32_t size = 0;
    const rt_uint8_t *send_ptr = NULL;
    rt_uint8_t *recv_ptr = NULL;
    rt_uint8_t data = 0;

    RT_ASSERT(NULL != device);
    RT_ASSERT(NULL != message);

    spi_bus = device->bus;
    ls1c_spi = spi_bus->parent.user_data;
    SPIx = ls1c_spi->SPIx;
    spi_base = ls1c_spi_get_base(SPIx);
    ls1c_spi_cs = device->parent.user_data;
    cs = ls1c_spi_cs->cs;
    size = message->length;

    DEBUG_PRINTF("[%s] SPIx=%d, cs=%d\n", __FUNCTION__, SPIx, cs);

    // take cs
    if (message->cs_take)
    {
        ls1c_spi_set_cs(spi_base, cs, 0);
    }

    // 收发数据
    send_ptr = message->send_buf;
    recv_ptr = message->recv_buf;
    while (size--)
    {
        data = 0xFF;
        if (NULL != send_ptr)
        {
            data = *send_ptr++;
        }

        if (NULL != recv_ptr)
        {
            *recv_ptr++ = ls1c_spi_txrx_byte(spi_base, data);
        }
        else
        {
            ls1c_spi_txrx_byte(spi_base, data);
        }
    }

    // release cs
    if (message->cs_release)
    {
        ls1c_spi_set_cs(spi_base, cs, 1);
    }

    return message->length;
}


#ifdef RT_USING_SPI0
struct ls1c_spi ls1c_spi0 =
{
    .SPIx = LS1C_SPI_0,
};

static struct rt_spi_bus spi0_bus;
#endif


#ifdef RT_USING_SPI1
struct ls1c_spi ls1c_spi1 =
{
    .SPIx = LS1C_SPI_1,
};

static struct rt_spi_bus spi1_bus;
#endif


/*
 * 初始化并注册龙芯1c的spi总线
 * @SPI SPI总线，比如LS1C_SPI_0， LS1C_SPI_1
 * @spi_bus_name 总线名字
 * @ret
 */
rt_err_t ls1c_spi_bus_register(rt_uint8_t SPI, const char *spi_bus_name)
{
    struct rt_spi_bus *spi_bus = NULL;

#ifdef RT_USING_SPI0
    if (LS1C_SPI_0 == SPI)
    {
        spi_bus = &spi0_bus;
        spi_bus->parent.user_data = &ls1c_spi0;
    }
#endif

#ifdef RT_USING_SPI1
    if (LS1C_SPI_1 == SPI)
    {
        spi_bus = &spi1_bus;
        spi_bus->parent.user_data = &ls1c_spi1;
    }
#endif

    return rt_spi_bus_register(spi_bus, spi_bus_name, &ls1c_spi_ops);
}

int ls1c_hw_spi_init(void)
{
#ifdef RT_USING_SPI0
    pin_set_purpose(78, PIN_PURPOSE_OTHER);
    pin_set_purpose(79, PIN_PURPOSE_OTHER);
    pin_set_purpose(80, PIN_PURPOSE_OTHER);
    pin_set_purpose(83, PIN_PURPOSE_OTHER);//cs2 - SD card
    pin_set_purpose(82, PIN_PURPOSE_OTHER);//cs1
    pin_set_purpose(81, PIN_PURPOSE_OTHER);//cs0

    pin_set_remap(78, PIN_REMAP_DEFAULT);
    pin_set_remap(79, PIN_REMAP_DEFAULT);
    pin_set_remap(80, PIN_REMAP_DEFAULT);
    pin_set_remap(83, PIN_REMAP_DEFAULT);//cs2 - SD card
    pin_set_remap(82, PIN_REMAP_DEFAULT);//CS1
    pin_set_remap(81, PIN_REMAP_DEFAULT);//cs0
    ls1c_spi_bus_register(LS1C_SPI_0, "spi0");
#endif

#ifdef RT_USING_SPI1
    pin_set_purpose(46, PIN_PURPOSE_OTHER);
    pin_set_purpose(47, PIN_PURPOSE_OTHER);
    pin_set_purpose(48, PIN_PURPOSE_OTHER);
    pin_set_purpose(49, PIN_PURPOSE_OTHER);//CS0 - touch screen
    pin_set_remap(46, PIN_REMAP_THIRD);
    pin_set_remap(47, PIN_REMAP_THIRD);
    pin_set_remap(48, PIN_REMAP_THIRD);
    pin_set_remap(49, PIN_REMAP_THIRD);//CS0 - touch screen
    ls1c_spi_bus_register(LS1C_SPI_1, "spi1");

#endif


#ifdef RT_USING_SPI0
    /* attach cs */
    {
     static struct rt_spi_device spi_device0;
     static struct rt_spi_device spi_device1;
     static struct rt_spi_device spi_device2;
     static struct rt_spi_device spi_device3;
     static struct ls1c_spi_cs  spi_cs0;
     static struct ls1c_spi_cs  spi_cs1;
     static struct ls1c_spi_cs  spi_cs2;
     static struct ls1c_spi_cs  spi_cs3;
     /* spi02: CS2  SD Card*/
     spi_cs2.cs = LS1C_SPI_CS_2;
     rt_spi_bus_attach_device(&spi_device2, "spi02", "spi0", (void *)&spi_cs2);
     spi_cs1.cs = LS1C_SPI_CS_1;
     rt_spi_bus_attach_device(&spi_device1, "spi01", "spi0", (void *)&spi_cs1);
     spi_cs0.cs = LS1C_SPI_CS_0;
     rt_spi_bus_attach_device(&spi_device0, "spi00", "spi0", (void *)&spi_cs0);
     spi_cs3.cs = LS1C_SPI_CS_3;
     rt_spi_bus_attach_device(&spi_device3, "spi03", "spi0", (void*)&spi_cs3);
     msd_init("sd0", "spi02");
    }
#endif
#ifdef RT_USING_SPI1
    {
        static struct rt_spi_device spi_device;
        static struct ls1c_spi_cs  spi_cs;

        /* spi10: CS0  Touch*/
        spi_cs.cs = LS1C_SPI_CS_0;
        rt_spi_bus_attach_device(&spi_device, "spi10", "spi1", (void *)&spi_cs);
    }
#endif
}


INIT_BOARD_EXPORT(ls1c_hw_spi_init);

static int board_sd_init(void)
{
    #if defined(RT_USING_DFS) && defined(RT_USING_DFS_ELMFAT)
        /* mount sd card fat partition 1 as root directory */
        if( dfs_mount("sd0", "/", "elm", 0, 0) == 0)
        {
            rt_kprintf("File System initialized!\n");
        }
        else
        {
            rt_kprintf("File System initialzation failed!\n");
        }
    #endif /* RT_USING_DFS && RT_USING_DFS_ELMFAT */
}
INIT_APP_EXPORT(board_sd_init);

#endif

