/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-12-12      Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>
#include <rtdevice.h>

#if defined(BOARD_USING_STORAGE_SPIFLASH)
#if defined(RT_USING_SFUD)
    #include "dev_spi_flash.h"
    #include "dev_spi_flash_sfud.h"
#endif

#include "drv_qspi.h"

#define W25X_REG_READSTATUS    (0x05)
#define W25X_REG_READSTATUS2   (0x35)
#define W25X_REG_WRITEENABLE   (0x06)
#define W25X_REG_WRITESTATUS   (0x01)
#define W25X_REG_QUADENABLE    (0x02)

static rt_uint8_t SpiFlash_ReadStatusReg(struct rt_qspi_device *qspi_device)
{
    rt_uint8_t u8Val;
    rt_err_t result = RT_EOK;
    rt_uint8_t w25x_txCMD1 = W25X_REG_READSTATUS;

    result = rt_qspi_send_then_recv(qspi_device, &w25x_txCMD1, 1, &u8Val, 1);
    RT_ASSERT(result > 0);

    return u8Val;
}

static rt_uint8_t SpiFlash_ReadStatusReg2(struct rt_qspi_device *qspi_device)
{
    rt_uint8_t u8Val;
    rt_err_t result = RT_EOK;
    rt_uint8_t w25x_txCMD1 = W25X_REG_READSTATUS2;

    result = rt_qspi_send_then_recv(qspi_device, &w25x_txCMD1, 1, &u8Val, 1);
    RT_ASSERT(result > 0);

    return u8Val;
}

static rt_err_t SpiFlash_WriteStatusReg(struct rt_qspi_device *qspi_device, uint8_t u8Value1, uint8_t u8Value2)
{
    rt_uint8_t w25x_txCMD1;
    rt_uint8_t au8Val[2];
    rt_err_t result;
    struct rt_qspi_message qspi_message = {0};

    /* Enable WE */
    w25x_txCMD1 = W25X_REG_WRITEENABLE;
    result = rt_qspi_send(qspi_device, &w25x_txCMD1, sizeof(w25x_txCMD1));
    if (result != sizeof(w25x_txCMD1))
        goto exit_SpiFlash_WriteStatusReg;

    /* Prepare status-1, 2 data */
    au8Val[0] = u8Value1;
    au8Val[1] = u8Value2;

    /* 1-bit mode: Instruction+payload */
    qspi_message.instruction.content = W25X_REG_WRITESTATUS;
    qspi_message.instruction.qspi_lines = 1;

    qspi_message.qspi_data_lines   = 1;
    qspi_message.parent.cs_take    = 1;
    qspi_message.parent.cs_release = 1;
    qspi_message.parent.send_buf   = &au8Val[0];
    qspi_message.parent.length     = sizeof(au8Val);
    qspi_message.parent.next       = RT_NULL;

    if (rt_qspi_transfer_message(qspi_device, &qspi_message) != sizeof(au8Val))
    {
        result = -RT_ERROR;
    }

    result  = RT_EOK;

exit_SpiFlash_WriteStatusReg:

    return result;
}

static void SpiFlash_WaitReady(struct rt_qspi_device *qspi_device)
{
    volatile uint8_t u8ReturnValue;

    do
    {
        u8ReturnValue = SpiFlash_ReadStatusReg(qspi_device);
        u8ReturnValue = u8ReturnValue & 1;
    }
    while (u8ReturnValue != 0);   // check the BUSY bit
}

static void SpiFlash_EnterQspiMode(struct rt_qspi_device *qspi_device)
{
    rt_err_t result = RT_EOK;

    uint8_t u8Status1 = SpiFlash_ReadStatusReg(qspi_device);
    uint8_t u8Status2 = SpiFlash_ReadStatusReg2(qspi_device);

    u8Status2 |= W25X_REG_QUADENABLE;

    result = SpiFlash_WriteStatusReg(qspi_device, u8Status1, u8Status2);
    RT_ASSERT(result == RT_EOK);

    SpiFlash_WaitReady(qspi_device);
}

static void SpiFlash_ExitQspiMode(struct rt_qspi_device *qspi_device)
{
    rt_err_t result = RT_EOK;
    uint8_t u8Status1 = SpiFlash_ReadStatusReg(qspi_device);
    uint8_t u8Status2 = SpiFlash_ReadStatusReg2(qspi_device);

    u8Status2 &= ~W25X_REG_QUADENABLE;

    result = SpiFlash_WriteStatusReg(qspi_device, u8Status1, u8Status2);
    RT_ASSERT(result == RT_EOK);

    SpiFlash_WaitReady(qspi_device);
}

static int rt_hw_spiflash_init(void)
{
    if (nu_qspi_bus_attach_device("qspi0", "qspi01", 2, SpiFlash_EnterQspiMode, SpiFlash_ExitQspiMode) != RT_EOK)
        return -1;

#if defined(RT_USING_SFUD)
    if (rt_sfud_flash_probe(FAL_USING_NOR_FLASH_DEV_NAME, "qspi01") == RT_NULL)
    {
        return -(RT_ERROR);
    }
#endif
    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_spiflash_init);
#endif

#if defined(BOARD_USING_STORAGE_SPINAND) && defined(NU_PKG_USING_SPINAND)

#include "drv_qspi.h"
#include "spinand.h"

struct rt_mtd_nand_device mtd_partitions[MTD_SPINAND_PARTITION_NUM] =
{
    [0] =
    {
        .block_start =  0,
        .block_end   = 23,
        .block_total = 24,
    },
    [1] =
    {
        .block_start = 24,
        .block_end   = 1023,
        .block_total = 1000,
    },
    [2] =
    {
        .block_start = 0,
        .block_end   = 1023,
        .block_total = 1024,
    }
};

static int rt_hw_spinand_init(void)
{
    if (nu_qspi_bus_attach_device("qspi0", "qspi01", 4, RT_NULL, RT_NULL) != RT_EOK)
        return -1;

    if (rt_hw_mtd_spinand_register("qspi01") != RT_EOK)
        return -1;

    return 0;
}

INIT_COMPONENT_EXPORT(rt_hw_spinand_init);
#endif

#if defined(BOARD_USING_UART8_RS485)

#include <drv_uart.h>

#define NU_UART_DEVNAME "uart8"

int test_rs485(int argc, char **argv)
{
    rt_device_t serial;
    char txbuf[16];
    rt_err_t ret;
    int str_len;

    serial = rt_device_find(NU_UART_DEVNAME);
    if (!serial)
    {
        rt_kprintf("Can't find %s. EXIT.\n", NU_UART_DEVNAME);
        goto exit_test_rs485;
    }

    /* Interrupt RX */
    ret = rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);
    RT_ASSERT(ret == RT_EOK);

    /* Nuvoton private command */
    nu_uart_set_rs485aud((struct rt_serial_device *)serial, RT_FALSE);

    rt_snprintf(&txbuf[0], sizeof(txbuf), "Hello World!\r\n");
    str_len = rt_strlen(txbuf);

    /* Say Hello */
    ret = rt_device_write(serial, 0, &txbuf[0], str_len);
    RT_ASSERT(ret == str_len);

    ret = rt_device_close(serial);
    RT_ASSERT(ret == RT_EOK);

exit_test_rs485:

    return 0;
}
MSH_CMD_EXPORT(test_rs485, test rs485 communication);

#endif //defined(BOARD_USING_UART8_RS485)

