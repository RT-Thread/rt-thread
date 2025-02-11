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
 * 程序清单：这是一个 SPI 设备使用例程
 * 例程导出了 spi_w25q_sample 命令到控制终端
 * 命令调用格式：spi_w25q_sample spi10
 * 命令解释：命令第二个参数是要使用的SPI设备名称，为空则使用默认的SPI设备
 * 程序功能：通过SPI设备读取 w25q 的 ID 数据
*/

#include <rtthread.h>
#include <rtdevice.h>
#include "board_config.h"
#include <string.h>

#if defined(BSP_USING_SPI)
#include "drv_spi.h"

#define W25Q_FLAG_BUSY                  (0x01)
#define W25Q_WR_ENABLE                  (0x06)
#define W25Q_SECTOR_ERASE               (0x20)
#define W25Q_RD_STATUS_REG1             (0x05)
#define W25Q_PAGE_PROGRAM               (0x02)
#define W25Q_STD_RD                     (0x03)

#define W25Q_PAGE_SIZE                  (256UL)
#define W25Q_SECTOR_SIZE                (1024UL * 4UL)
#define W25Q_PAGE_PER_SECTOR            (W25Q_SECTOR_SIZE / W25Q_PAGE_SIZE)
#define W25Q_MAX_ADDR                   (0x800000UL)

#define W25Q_SPI_WR_RD_ADDR             0x4000
#define W25Q_SPI_DATA_BUF_LEN           0x2000


#if defined(HC32F4A0) || defined(HC32F448)
    #define SPI_CS_PORT                 SPI1_CS_PORT
    #define SPI_CS_PIN                  SPI1_CS_PIN
    #define SPI_CS_PORT_PIN             GET_PIN(C, 7)

    #define W25Q_SPI_BUS_NAME           "spi1"
    #define W25Q_SPI_DEVICE_NAME        "spi10"
#elif defined(HC32F472)
    #define SPI_CS_PORT                 SPI1_CS_PORT
    #define SPI_CS_PIN                  SPI1_CS_PIN
    #define SPI_CS_PORT_PIN             GET_PIN(B, 12)

    #define W25Q_SPI_BUS_NAME           "spi1"
    #define W25Q_SPI_DEVICE_NAME        "spi10"
#elif defined(HC32F460)
    #define SPI_CS_PORT                 SPI3_CS_PORT
    #define SPI_CS_PIN                  SPI3_CS_PIN
    #define SPI_CS_PORT_PIN             GET_PIN(C, 7)

    #define W25Q_SPI_BUS_NAME           "spi3"
    #define W25Q_SPI_DEVICE_NAME        "spi30"
#endif


struct rt_spi_device *spi_dev_w25q;     /* SPI 设备句柄 */

static uint8_t u8WrBuf[W25Q_SPI_DATA_BUF_LEN];
static uint8_t u8RdBuf[W25Q_SPI_DATA_BUF_LEN];


static int rt_hw_spi_flash_init(void)
{
    if (RT_EOK != rt_hw_spi_device_attach(W25Q_SPI_BUS_NAME, W25Q_SPI_DEVICE_NAME, SPI_CS_PORT_PIN))
    {
        rt_kprintf("Failed to attach the spi device.");
        return -RT_ERROR;
    }

    return RT_EOK;
}
/* 导出到自动初始化 */
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_init);

void w25q_read_uid(struct rt_spi_device *device)
{
    rt_uint8_t w25x_read_uid = 0x4B;    /* 命令 */
    rt_uint8_t u8UID[8] = {0};
    rt_uint8_t txBuf[5] = {0};

    memset(txBuf, 0xFF, 5);
    txBuf[0] = w25x_read_uid;
    /* 方式1：使用 rt_spi_send_then_recv()发送命令读取ID */
    if (RT_EOK != rt_spi_send_then_recv(device, txBuf, 5, u8UID, 8))
    {
        rt_kprintf("spi get uid failed!\n");
    }
    else
    {
        rt_kprintf("w25q UID is: %02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x\r\n",
                   u8UID[0], u8UID[1], u8UID[2], u8UID[3], u8UID[4], u8UID[5], u8UID[6], u8UID[7]);
    }

    /* 方式2：使用 rt_spi_transfer_message()发送命令读取ID */
    struct rt_spi_message msg1, msg2;

    msg1.send_buf   = txBuf;
    msg1.recv_buf   = RT_NULL;
    msg1.length     = 5;
    msg1.cs_take    = 1;
    msg1.cs_release = 0;
    msg1.next       = &msg2;

    msg2.send_buf   = RT_NULL;
    msg2.recv_buf   = u8UID;
    msg2.length     = 8;
    msg2.cs_take    = 0;
    msg2.cs_release = 1;
    msg2.next       = RT_NULL;

    rt_spi_transfer_message(device, &msg1);
    rt_kprintf("use rt_spi_transfer_message() read w25q ID is: UID is: %02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x\r\n",
               u8UID[0], u8UID[1], u8UID[2], u8UID[3], u8UID[4], u8UID[5], u8UID[6], u8UID[7]);
}


int32_t w25q_check_process_done(struct rt_spi_device *device, uint32_t u32Timeout)
{
    __IO uint32_t u32Count = 0U;
    int32_t i32Ret = LL_ERR_TIMEOUT;
    rt_uint8_t rxBuf[5] = {0};
    rt_uint8_t txBuf[5] = {0};

    txBuf[0] = W25Q_RD_STATUS_REG1;
    while (u32Count < u32Timeout)
    {
        if (RT_EOK != rt_spi_send_then_recv(device, txBuf, 1, rxBuf, 1))
        {
            rt_kprintf("spi get SR failed!\n");
        }
        else
        {
            if (W25Q_FLAG_BUSY != (rxBuf[0] & W25Q_FLAG_BUSY))
            {
                i32Ret = LL_OK;
                break;
            }
        }
        rt_thread_mdelay(1);
        u32Count++;
    }

    return i32Ret;
}

int32_t w25q_read_data(struct rt_spi_device *device, uint32_t u32Addr, uint8_t *pu8ReadBuf, uint32_t u32Size)
{
    int32_t i32Ret = LL_OK;
    rt_uint8_t txBuf[5] = {0};

    txBuf[0] = W25Q_STD_RD;
    txBuf[1] = (u32Addr >> 16) & 0xFFU;
    txBuf[2] = (u32Addr >> 8) & 0xFFU;
    txBuf[3] = u32Addr & 0xFFU;
    if (RT_EOK != rt_spi_send_then_recv(device, txBuf, 4, pu8ReadBuf, u32Size))
    {
        i32Ret = LL_ERR;
    }

    return i32Ret;
}


int32_t w25q_write_data(struct rt_spi_device *device, uint32_t u32Addr, uint8_t *pu8WriteBuf, uint32_t u32Size)
{
    int32_t i32Ret = LL_OK;
    uint32_t u32TempSize, u32AddrOffset = 0U;
    uint8_t w25q_txBuf[W25Q_PAGE_SIZE + 10];

    if ((u32Addr % W25Q_PAGE_SIZE) != 0U)
    {
        return LL_ERR_INVD_PARAM;
    }
    while (u32Size != 0UL)
    {
        if (u32Size >= W25Q_PAGE_SIZE)
        {
            u32TempSize = W25Q_PAGE_SIZE;
        }
        else
        {
            u32TempSize = u32Size;
        }

        w25q_txBuf[0] = W25Q_WR_ENABLE;
        if (1 != rt_spi_send(device, w25q_txBuf, 1))
        {
            rt_kprintf("spi send cmd failed!\n");
        }
        w25q_txBuf[0] = W25Q_PAGE_PROGRAM;
        w25q_txBuf[1] = (u32Addr >> 16) & 0xFFU;
        w25q_txBuf[2] = (u32Addr >> 8) & 0xFFU;
        w25q_txBuf[3] = u32Addr & 0xFFU;
        memcpy(&w25q_txBuf[4], &pu8WriteBuf[u32AddrOffset], u32TempSize);
        if ((u32TempSize + 4) != rt_spi_send(device, w25q_txBuf, u32TempSize + 4))
        {
            rt_kprintf("spi send addr failed!\n");
        }
        i32Ret = w25q_check_process_done(device, 500U);
        if (i32Ret != LL_OK)
        {
            break;
        }

        u32Addr       += u32TempSize;
        u32AddrOffset += u32TempSize;
        u32Size       -= u32TempSize;
    }

    return i32Ret;
}

int32_t w25q_erase_sector(struct rt_spi_device *device, uint32_t u32Addr, uint32_t u32Size)
{
    uint8_t txBuf[10];
    uint32_t u32SectorNum, u32Cnt;
    int32_t i32Ret = LL_OK;

    if ((u32Addr % W25Q_SECTOR_SIZE) != 0U)
    {
        return LL_ERR_INVD_PARAM;
    }
    u32SectorNum = u32Size / W25Q_SECTOR_SIZE;
    if ((u32Size % W25Q_SECTOR_SIZE) != 0U)
    {
        u32SectorNum += 1;
    }
    for (u32Cnt = 0; u32Cnt < u32SectorNum; u32Cnt++)
    {
        txBuf[0] = W25Q_WR_ENABLE;
        if (1 != rt_spi_send(device, txBuf, 1))
        {
            rt_kprintf("spi send cmd failed!\n");
        }
        txBuf[0] = W25Q_SECTOR_ERASE;
        txBuf[1] = (u32Addr >> 16) & 0xFFU;
        txBuf[2] = (u32Addr >> 8) & 0xFFU;
        txBuf[3] = u32Addr & 0xFFU;
        if (4 != rt_spi_send(device, txBuf, 4))
        {
            rt_kprintf("spi send addr failed!\n");
        }
        if (LL_OK != w25q_check_process_done(device, 500U))
        {
            i32Ret = LL_ERR;
            break;
        }
        u32Addr += W25Q_SECTOR_SIZE;
    }

    return i32Ret;
}

void w25q_write_read_data(struct rt_spi_device *device, uint32_t u32Addr)
{
    uint32_t u32Cnt;

    for (u32Cnt = 0; u32Cnt < W25Q_SPI_DATA_BUF_LEN; u32Cnt++)
    {
        u8WrBuf[u32Cnt] = u32Cnt & 0xFFUL;
        u8RdBuf[u32Cnt] = 0U;
    }
    if (LL_OK != w25q_erase_sector(device, u32Addr, W25Q_SPI_DATA_BUF_LEN))
    {
        rt_kprintf("spi erase sector failed!\n");
    }
    if (LL_OK !=  w25q_write_data(device, u32Addr, u8WrBuf, W25Q_SPI_DATA_BUF_LEN))
    {
        rt_kprintf("spi write data failed!\n");
    }
    if (LL_OK !=  w25q_read_data(device, u32Addr, u8RdBuf, W25Q_SPI_DATA_BUF_LEN))
    {
        rt_kprintf("spi read data failed!\n");
    }
    if (memcmp(u8WrBuf, u8RdBuf, W25Q_SPI_DATA_BUF_LEN) == 0)
    {
        rt_kprintf("spi write and read test ok! addr=%06x\n", u32Addr);
    }
    else
    {
        rt_kprintf("spi write and read failed!\n");
    }
}

static void spi_thread_entry(void *parameter)
{
    uint32_t u32Addr = W25Q_SPI_WR_RD_ADDR;
    struct rt_spi_configuration cfg;

    cfg.data_width = 8;
    cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB;
    cfg.max_hz = 80 * 1000 * 1000;  /* 80M */
    rt_spi_configure(spi_dev_w25q, &cfg);
    /* 读取UID */
    w25q_read_uid(spi_dev_w25q);

    while (1)
    {
        /* 读写对比数据 */
        w25q_write_read_data(spi_dev_w25q, u32Addr);
        u32Addr += W25Q_SPI_DATA_BUF_LEN;
        if (u32Addr >= (W25Q_MAX_ADDR - W25Q_SPI_DATA_BUF_LEN))
        {
            u32Addr = W25Q_SPI_WR_RD_ADDR;
        }
        rt_thread_mdelay(500);
    }
}

static void spi_w25q_sample(int argc, char *argv[])
{
    char name[RT_NAME_MAX];

    if (argc == 2)
    {
        rt_strncpy(name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(name, W25Q_SPI_DEVICE_NAME, RT_NAME_MAX);
    }
    /* 查找 spi 设备获取设备句柄 */
    spi_dev_w25q = (struct rt_spi_device *)rt_device_find(name);
    if (!spi_dev_w25q)
    {
        rt_kprintf("spi sample run failed! can't find %s device!\n", name);
    }
    else
    {
        /* 创建 线程 */
        rt_thread_t thread = rt_thread_create("spi", spi_thread_entry, RT_NULL, 2048, 15, 10);
        /* 创建成功则启动线程 */
        if (thread != RT_NULL)
        {
            rt_thread_startup(thread);
        }
    }
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(spi_w25q_sample, spi w25q sample);

#endif
