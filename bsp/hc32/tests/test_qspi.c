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
 * 程序清单：这是一个 QSPI 设备使用例程
 * 例程导出了 qspi_w25q_sample 命令到控制终端
 * 命令调用格式：qspi_w25q_sample qspi10
 * 命令解释：命令第二个参数是要使用的QSPI设备名称，为空则使用默认的QSPI设备
 * 程序功能：通过QSPI设备读取 w25q 的 ID 数据
*/

#include <rtthread.h>
#include <rtdevice.h>
#include "board_config.h"


#if defined(BSP_USING_QSPI)
#include "drv_qspi.h"

#define W25Q_QSPI_DEVICE_NAME           "qspi10"

#define W25Q_FLAG_BUSY                  (0x01)
#define W25Q_WR_ENABLE                  (0x06)
#define W25Q_SECTOR_ERASE               (0x20)
#define W25Q_RD_STATUS_REG1             (0x05)
#define W25Q_PAGE_PROGRAM               (0x02)
#define W25Q64_QUAD_INPUT_PAGE_PROGRAM  (0x32)

#define W25Q_STD_RD                     (0x03)
#define W25Q_FAST_RD                    (0x0B)
#define W25Q_FAST_RD_DUAL_OUTPUT        (0x3B)
#define W25Q_FAST_RD_DUAL_IO            (0xBB)
#define W25Q_FAST_RD_QUAD_OUTPUT        (0x6B)
#define W25Q_FAST_RD_QUAD_IO            (0xEB)

#define W25Q64_RD_STATUS_REG1           (0x05)
#define W25Q64_WR_STATUS_REG1           (0x01)
#define W25Q64_RD_STATUS_REG2           (0x35)
#define W25Q64_WR_STATUS_REG2           (0x31)
#define W25Q64_RD_STATUS_REG3           (0x15)
#define W25Q64_WR_STATUS_REG3           (0x11)

#define W25Q_PAGE_SIZE                  (256UL)
#define W25Q_SECTOR_SIZE                (1024UL * 4UL)
#define W25Q_PAGE_PER_SECTOR            (W25Q_SECTOR_SIZE / W25Q_PAGE_SIZE)
#define W25Q_MAX_ADDR                   (0x800000UL)

#define W25Q_QSPI_DATA_LINE_WIDTH       1
#define W25Q_QSPI_RD_MD                 (W25Q_FAST_RD_QUAD_IO)

#define W25Q_QSPI_WR_RD_ADDR            0x4000
#define W25Q_QSPI_DATA_BUF_LEN          0x2000
#define W25Q_QSPI_WR_CMD                W25Q64_QUAD_INPUT_PAGE_PROGRAM

#if defined (HC32F460) || defined (HC32F4A0) || defined (HC32F472)
    #ifndef BSP_QSPI_USING_SOFT_CS
        #if (W25Q_QSPI_WR_CMD == W25Q64_QUAD_INPUT_PAGE_PROGRAM)
            #error "QUAD PAGE PROGRAM must use soft CS pin!!"
        #endif
    #endif
#endif

#if W25Q_QSPI_RD_MD == W25Q_STD_RD
    #define W25Q_QSPI_RD_DUMMY_CYCLE    0
#elif W25Q_QSPI_RD_MD == W25Q_FAST_RD_DUAL_IO
    #define W25Q_QSPI_RD_DUMMY_CYCLE    4
#elif W25Q_QSPI_RD_MD == W25Q_FAST_RD_QUAD_IO
    #define W25Q_QSPI_RD_DUMMY_CYCLE    6
#else
    #define W25Q_QSPI_RD_DUMMY_CYCLE    8
#endif

#if (W25Q_QSPI_RD_MD == W25Q_FAST_RD_QUAD_IO)
    #define W25Q_QSPI_ADDR_LINE         4
#elif (W25Q_QSPI_RD_MD == W25Q_FAST_RD_DUAL_IO)
    #define W25Q_QSPI_ADDR_LINE         2
#else
    #define W25Q_QSPI_ADDR_LINE         1
#endif

#if (W25Q_QSPI_RD_MD == W25Q_STD_RD) || (W25Q_QSPI_RD_MD == W25Q_FAST_RD)
    #define W25Q_QSPI_DATA_LINE         1
#elif (W25Q_QSPI_RD_MD == W25Q_FAST_RD_DUAL_OUTPUT) || (W25Q_QSPI_RD_MD == W25Q_FAST_RD_DUAL_IO)
    #define W25Q_QSPI_DATA_LINE         2
#else
    #define W25Q_QSPI_DATA_LINE         4
#endif


struct rt_qspi_device *qspi_dev_w25q;     /* QSPI 设备句柄 */

static uint8_t u8WrBuf[W25Q_QSPI_DATA_BUF_LEN];
static uint8_t u8RdBuf[W25Q_QSPI_DATA_BUF_LEN];


static int rt_hw_qspi_flash_init(void)
{
#ifndef BSP_QSPI_USING_SOFT_CS
    if (RT_EOK != rt_hw_qspi_bus_attach_device("qspi1", "qspi10", RT_NULL, W25Q_QSPI_DATA_LINE_WIDTH, RT_NULL, RT_NULL))
#else
#if defined (HC32F472)
    if (RT_EOK != rt_hw_qspi_bus_attach_device("qspi1", "qspi10", GET_PIN(B, 12), W25Q_QSPI_DATA_LINE_WIDTH, RT_NULL, RT_NULL))
#elif defined (HC32F4A0) || defined (HC32F460) || defined (HC32F448)
    if (RT_EOK != rt_hw_qspi_bus_attach_device("qspi1", "qspi10", GET_PIN(C, 7), W25Q_QSPI_DATA_LINE_WIDTH, RT_NULL, RT_NULL))
#endif
#endif
    {
        rt_kprintf("Failed to attach the qspi device.");
        return -RT_ERROR;
    }

    return RT_EOK;
}
/* 导出到自动初始化 */
INIT_COMPONENT_EXPORT(rt_hw_qspi_flash_init);


void w25q_read_uid(struct rt_qspi_device *device)
{
    rt_uint8_t w25x_read_uid = 0x4B;    /* 命令 */
    rt_uint8_t u8UID[8] = {0};
    rt_uint8_t txBuf[5] = {0};

    rt_memset(txBuf, 0xFF, 5);
    txBuf[0] = w25x_read_uid;

    if (8 != rt_qspi_send_then_recv(device, txBuf, 5, u8UID, 8))
    {
        rt_kprintf("qspi get uid failed!\n");
    }
    else
    {
        rt_kprintf("w25q UID is: %02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x\r\n",
                   u8UID[0], u8UID[1], u8UID[2], u8UID[3], u8UID[4], u8UID[5], u8UID[6], u8UID[7]);
    }
}


int32_t w25q_check_process_done(struct rt_qspi_device *device, uint32_t u32Timeout)
{
    __IO uint32_t u32Count = 0U;
    int32_t i32Ret = LL_ERR_TIMEOUT;
    rt_uint8_t rxBuf[5] = {0};
    rt_uint8_t txBuf[5] = {0};

    txBuf[0] = W25Q_RD_STATUS_REG1;
    while (u32Count < u32Timeout)
    {
        if (1 != rt_qspi_send_then_recv(device, txBuf, 1, rxBuf, 1))
        {
            rt_kprintf("qspi get SR failed!\n");
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

rt_err_t bsp_qspi_send_then_recv(struct rt_qspi_device *device, const void *send_buf, rt_size_t send_length, void *recv_buf, rt_size_t recv_length)
{
    RT_ASSERT(send_buf);
    RT_ASSERT(recv_buf);
    RT_ASSERT(send_length != 0);

    struct rt_qspi_message message;
    unsigned char *ptr = (unsigned char *)send_buf;
    rt_size_t count = 0;
    rt_err_t result = 0;

    message.instruction.content = ptr[0];
    message.instruction.qspi_lines = 1;
    count++;

    /* get address */
    if (send_length > 1)
    {
        if (send_length >= 4)
        {
            /* address size is 3 Byte */
            message.address.content = (ptr[1] << 16) | (ptr[2] << 8) | (ptr[3]);
            message.address.size = 24;
            count += 3;
        }
        else
        {
            return -RT_ERROR;
        }
        message.address.qspi_lines = W25Q_QSPI_ADDR_LINE;
    }
    else
    {
        /* no address stage */
        message.address.content = 0 ;
        message.address.qspi_lines = 0;
        message.address.size = 0;
    }

    message.alternate_bytes.content = 0;
    message.alternate_bytes.size = 0;
    message.alternate_bytes.qspi_lines = 0;

    /* set dummy cycles */
    message.dummy_cycles = W25Q_QSPI_RD_DUMMY_CYCLE;

    /* set recv buf and recv size */
    message.parent.recv_buf = recv_buf;
    message.parent.send_buf = RT_NULL;
    message.parent.length = recv_length;
    message.parent.cs_take = 1;
    message.parent.cs_release = 1;
    message.qspi_data_lines = W25Q_QSPI_DATA_LINE;

    result = rt_qspi_transfer_message(device, &message);
    if (result == 0)
    {
        result = -RT_EIO;
    }
    else
    {
        result = recv_length;
    }

    return result;
}


rt_err_t bsp_qspi_send(struct rt_qspi_device *device, const void *send_buf, rt_size_t length, uint8_t dataLine)
{
    RT_ASSERT(send_buf);
    RT_ASSERT(length != 0);

    struct rt_qspi_message message;
    unsigned char *ptr = (unsigned char *)send_buf;
    rt_size_t  count = 0;
    rt_err_t result = 0;

    message.instruction.content = ptr[0];
    message.instruction.qspi_lines = 1;
    count++;

    /* get address */
    if (length > 1)
    {
        if (device->config.medium_size > 0x1000000 && length >= 5)
        {
            /* medium size greater than 16Mb, address size is 4 Byte */
            message.address.content = (ptr[1] << 24) | (ptr[2] << 16) | (ptr[3] << 8) | (ptr[4]);
            message.address.size = 32;
            message.address.qspi_lines = 1;
            count += 4;
        }
        else if (length >= 4)
        {
            /* address size is 3 Byte */
            message.address.content = (ptr[1] << 16) | (ptr[2] << 8) | (ptr[3]);
            message.address.size = 24;
            message.address.qspi_lines = 1;
            count += 3;
        }
        else
        {
            /* no address stage */
            message.address.content = 0 ;
            message.address.qspi_lines = 0;
            message.address.size = 0;
        }

    }
    else
    {
        /* no address stage */
        message.address.content = 0 ;
        message.address.qspi_lines = 0;
        message.address.size = 0;
    }

    message.alternate_bytes.content = 0;
    message.alternate_bytes.size = 0;
    message.alternate_bytes.qspi_lines = 0;

    message.dummy_cycles = 0;

    /* determine if there is data to send */
    if (length - count > 0)
    {
        message.qspi_data_lines = dataLine;
    }
    else
    {
        message.qspi_data_lines = 0;
    }

    /* set send buf and send size */
    message.parent.send_buf = ptr + count;
    message.parent.recv_buf = RT_NULL;
    message.parent.length = length - count;
    message.parent.cs_take = 1;
    message.parent.cs_release = 1;

    result = rt_qspi_transfer_message(device, &message);
    if (result == 0)
    {
        result = -RT_EIO;
    }
    else
    {
        result = length;
    }

    return result;
}



void w25q_write_sr(struct rt_qspi_device *device, uint8_t reg, uint8_t value)
{
    rt_uint8_t txBuf[5] = {0};

    txBuf[0] = W25Q_WR_ENABLE;
    if (1 != rt_qspi_send(device, txBuf, 1))
    {
        rt_kprintf("qspi send cmd failed!\n");
    }
    txBuf[0] = reg;
    txBuf[1] = value;
    if (2 != bsp_qspi_send(device, txBuf, 2, 1))
    {
        rt_kprintf("qspi send addr failed!\n");
    }
    if (LL_OK != w25q_check_process_done(device, 500U))
    {
        rt_kprintf("qspi wait busy failed!\n");
    }
}


int32_t w25q_read_data(struct rt_qspi_device *device, uint32_t u32Addr, uint8_t *pu8ReadBuf, uint32_t u32Size)
{
    int32_t i32Ret = LL_OK;
    rt_uint8_t txBuf[5] = {0};

    txBuf[0] = W25Q_QSPI_RD_MD;
    txBuf[1] = (u32Addr >> 16) & 0xFFU;
    txBuf[2] = (u32Addr >> 8) & 0xFFU;
    txBuf[3] = u32Addr & 0xFFU;
    if (u32Size != bsp_qspi_send_then_recv(device, txBuf, 4, pu8ReadBuf, u32Size))
    {
        i32Ret = LL_ERR;
    }

    return i32Ret;
}


int32_t w25q_write_data(struct rt_qspi_device *device, uint32_t u32Addr, uint8_t *pu8WriteBuf, uint32_t u32Size)
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
        if (1 != rt_qspi_send(device, w25q_txBuf, 1))
        {
            rt_kprintf("qspi send cmd failed!\n");
        }
        w25q_txBuf[0] = W25Q_QSPI_WR_CMD;
        w25q_txBuf[1] = (u32Addr >> 16) & 0xFFU;
        w25q_txBuf[2] = (u32Addr >> 8) & 0xFFU;
        w25q_txBuf[3] = u32Addr & 0xFFU;
        rt_memcpy(&w25q_txBuf[4], &pu8WriteBuf[u32AddrOffset], u32TempSize);
        if (W25Q64_QUAD_INPUT_PAGE_PROGRAM == w25q_txBuf[0])
        {
            if ((u32TempSize + 4) != bsp_qspi_send(device, w25q_txBuf, u32TempSize + 4, 4))
            {
                rt_kprintf("qspi send addr failed!\n");
            }
        }
        else
        {
            if ((u32TempSize + 4) != bsp_qspi_send(device, w25q_txBuf, u32TempSize + 4, 1))
            {
                rt_kprintf("qspi send addr failed!\n");
            }
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

int32_t w25q_erase_sector(struct rt_qspi_device *device, uint32_t u32Addr, uint32_t u32Size)
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
        if (1 != rt_qspi_send(device, txBuf, 1))
        {
            rt_kprintf("qspi send cmd failed!\n");
        }
        txBuf[0] = W25Q_SECTOR_ERASE;
        txBuf[1] = (u32Addr >> 16) & 0xFFU;
        txBuf[2] = (u32Addr >> 8) & 0xFFU;
        txBuf[3] = u32Addr & 0xFFU;
        if (4 != rt_qspi_send(device, txBuf, 4))
        {
            rt_kprintf("qspi send addr failed!\n");
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

void w25q_write_read_data(struct rt_qspi_device *device, uint32_t u32Addr)
{
    uint32_t u32Cnt;

    for (u32Cnt = 0; u32Cnt < W25Q_QSPI_DATA_BUF_LEN; u32Cnt++)
    {
        u8WrBuf[u32Cnt] = u32Cnt & 0xFFUL;
        u8RdBuf[u32Cnt] = 0U;
    }
    if (LL_OK != w25q_erase_sector(device, u32Addr, W25Q_QSPI_DATA_BUF_LEN))
    {
        rt_kprintf("qspi erase sector failed!\n");
    }
    if (LL_OK !=  w25q_write_data(device, u32Addr, u8WrBuf, W25Q_QSPI_DATA_BUF_LEN))
    {
        rt_kprintf("qspi write data failed!\n");
    }
    if (LL_OK !=  w25q_read_data(device, u32Addr, u8RdBuf, W25Q_QSPI_DATA_BUF_LEN))
    {
        rt_kprintf("qspi read data failed!\n");
    }
    if (rt_memcmp(u8WrBuf, u8RdBuf, W25Q_QSPI_DATA_BUF_LEN) == 0)
    {
        rt_kprintf("qspi write and read test ok: addr=0x%06X\n", u32Addr);
    }
    else
    {
        rt_kprintf("qspi write and read failed!\n");
    }
}

static void qspi_thread_entry(void *parameter)
{
    rt_err_t ret;
    struct rt_qspi_configuration qcfg = {0};
    uint32_t u32Addr = W25Q_QSPI_WR_RD_ADDR;

    qcfg.medium_size        = W25Q_MAX_ADDR;
    qcfg.qspi_dl_width      = W25Q_QSPI_DATA_LINE_WIDTH;
    qcfg.parent.mode        = RT_SPI_MODE_0;
    qcfg.parent.data_width  = 8;
    qcfg.parent.max_hz      = 10000000UL;
    ret = rt_qspi_configure(qspi_dev_w25q, &qcfg);
    if ((RT_EOK != ret) && (-RT_EBUSY != ret))
    {
        rt_kprintf("qspi config failed!\n");
    }

    /* 读取UID */
    w25q_read_uid(qspi_dev_w25q);
    /* Set QE = 1 */
    w25q_write_sr(qspi_dev_w25q, W25Q64_WR_STATUS_REG2, 0x02);

    while (1)
    {
        /* 读写对比数据 */
        w25q_write_read_data(qspi_dev_w25q, u32Addr);
        u32Addr += W25Q_QSPI_DATA_BUF_LEN;
        if (u32Addr >= (W25Q_MAX_ADDR - W25Q_QSPI_DATA_BUF_LEN))
        {
            u32Addr = W25Q_QSPI_WR_RD_ADDR;
        }
        rt_thread_mdelay(500);
    }
}


void qspi_w25q_sample(int argc, char *argv[])
{
    char name[RT_NAME_MAX];

    if (argc == 2)
    {
        rt_strncpy(name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(name, W25Q_QSPI_DEVICE_NAME, RT_NAME_MAX);
    }

    /* 查找 qspi 设备获取设备句柄 */
    qspi_dev_w25q = (struct rt_qspi_device *)rt_device_find(name);
    if (!qspi_dev_w25q)
    {
        rt_kprintf("qspi sample run failed! can't find %s device!\n", name);
    }
    else
    {
        /* 创建 线程 */
        rt_thread_t thread = rt_thread_create("qspi", qspi_thread_entry, RT_NULL, 2048, 15, 10);
        /* 创建成功则启动线程 */
        if (thread != RT_NULL)
        {
            rt_thread_startup(thread);
        }
    }
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(qspi_w25q_sample, qspi w25q sample);

#endif
