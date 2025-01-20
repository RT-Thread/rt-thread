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
 * 程序清单：这是 I2C 设备使用例程。
 * 例程导出了 i2c_sample 到控制终端。
 * 命令调用格式：i2c_sample
 * 命令解释：
 * 程序功能：查找I2C模块，读写I2C设备。
 * 注意：测试要用逻辑分析仪或示波器抓取信号
*/

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/*
 * to readout/write  from/into i2c device, user could use this macro to choice
 * either rt_i2c_master_send & rt_i2c_master_recv or rt_i2c_transfer
*/
#if defined(RT_USING_I2C)

#define USING_RT_I2C_TRANSFER

/* defined EEPROM */
#if defined(HC32F472) || defined(HC32F460) || defined(HC32F4A0) || defined(HC32F448)
    #define EE_DEV_ADDR                 0x50
    #define EE_TEST_PAGE_CNT            8       // Test 8 pages
#endif

/* define EEPROM hardware */
#if defined(HC32F472) || defined(HC32F460) || defined(HC32F448)
    #define EE24C256
#elif defined(HC32F4A0)
    #define EE24C02
#endif

#if defined (EE24C1024)
    #define EE_PAGE_SIZE                256 // 24C1024
    #define EE_WORD_ADR_SIZE            2   // 2 word addr
#elif defined (EE24C256)
    #define EE_PAGE_SIZE                64  // 24C256
    #define EE_WORD_ADR_SIZE            2   // 2 word addr
#elif defined (EE24C02)
    #define EE_PAGE_SIZE                8   // 24C02
    #define EE_WORD_ADR_SIZE            1   // 1 word addr
#endif

/* device information */
#if defined(HC32F472) || defined(HC32F4A0) || defined(HC32F448)
    #define HW_I2C_DEV                  "i2c1"
    #define SW_I2C_DEV                  "i2c1_sw"
#elif defined(HC32F460)
    #define HW_I2C_DEV                  "i2c3"
    #define SW_I2C_DEV                  "i2c1_sw"
#endif

/* this API is for eeprom size is smaller than  256Bytes */
static void eeprom_page_write(uint32_t page, uint8_t *pBuf)
{
    struct rt_i2c_bus_device *hc32_i2c = RT_NULL;
    uint8_t TxBuf[EE_PAGE_SIZE + EE_WORD_ADR_SIZE] = {0};
    struct rt_i2c_msg msg[1];

#if defined (BSP_USING_I2C_HW)
    hc32_i2c = rt_i2c_bus_device_find(HW_I2C_DEV);  //hw i2c
#else
    hc32_i2c = rt_i2c_bus_device_find(SW_I2C_DEV);  //sw i2c
#endif

    /* START --- ADR_W --- WORD_ADR(1 byte) --- DATAn --- STOP */
    if (EE_WORD_ADR_SIZE == 2)
    {
        TxBuf[0] = (page * EE_PAGE_SIZE) / 256;     // addrH
        TxBuf[1] = page * EE_PAGE_SIZE;             // addrL
    }
    else
    {
        TxBuf[0] = page * EE_PAGE_SIZE;
    }
    for (int i = 0; i < EE_PAGE_SIZE; i++)  // data fill
    {
        TxBuf[i + EE_WORD_ADR_SIZE] = *pBuf++;
    }
    msg[0].addr  = EE_DEV_ADDR;
    msg[0].flags = RT_I2C_WR;
    msg[0].len   = EE_PAGE_SIZE + EE_WORD_ADR_SIZE;
    msg[0].buf   = TxBuf;

#if defined(USING_RT_I2C_TRANSFER)
    rt_i2c_transfer(hc32_i2c, &msg[0], 1);
#else
    rt_i2c_master_send(hc32_i2c, EE_DEV_ADDR, RT_I2C_NO_STOP, TxBuf, msg[0].len / 2);
    rt_i2c_master_send(hc32_i2c, EE_DEV_ADDR, RT_I2C_NO_START, TxBuf + msg[0].len / 2, msg[0].len - msg[0].len / 2);
#endif
    /* write cycle 5ms */
    rt_thread_mdelay(5);
}

static void eeprom_page_read(uint32_t page, uint8_t *pBuf)
{
    struct rt_i2c_bus_device *hc32_i2c = RT_NULL;
    uint8_t readAddr[EE_WORD_ADR_SIZE];
#if defined(USING_RT_I2C_TRANSFER)
    struct rt_i2c_msg msg[2];
#endif

#if defined (BSP_USING_I2C_HW)
    hc32_i2c = rt_i2c_bus_device_find(HW_I2C_DEV);  //hw i2c
#else
    hc32_i2c = rt_i2c_bus_device_find(SW_I2C_DEV);  //sw i2c
#endif

    if (EE_WORD_ADR_SIZE == 2)
    {
        readAddr[0] = (page * EE_PAGE_SIZE) / 256;  // addrH
        readAddr[1] = page * EE_PAGE_SIZE;          // addrL
    }
    else
    {
        readAddr[0] = page * EE_PAGE_SIZE;
    }

#if defined(USING_RT_I2C_TRANSFER)
    msg[0].addr  = EE_DEV_ADDR;
    msg[0].flags = RT_I2C_WR;
    msg[0].len   = EE_WORD_ADR_SIZE;
    msg[0].buf   = readAddr;

    msg[1].addr  = EE_DEV_ADDR;
    msg[1].flags = RT_I2C_RD;
    msg[1].len   = EE_PAGE_SIZE;
    msg[1].buf   = pBuf;
    rt_i2c_transfer(hc32_i2c, &msg[0], 2);
#else
    rt_i2c_master_send(hc32_i2c, EE_DEV_ADDR, RT_I2C_NO_STOP, readAddr, EE_WORD_ADR_SIZE);
    rt_i2c_master_recv(hc32_i2c, EE_DEV_ADDR, 0, pBuf, EE_PAGE_SIZE);
#endif
}

void eeprom_test(void)
{
    uint32_t page, i;
    uint32_t compareValueDiff = 0;
    static rt_uint8_t trans_buf[EE_PAGE_SIZE * EE_TEST_PAGE_CNT];
    static rt_uint8_t recv_buf[EE_PAGE_SIZE * EE_TEST_PAGE_CNT];

    /* write e2 */
    for (i = 0; i < sizeof(trans_buf); i++)
    {
        trans_buf[i] = i;
    }
    for (page = 0; page < EE_TEST_PAGE_CNT; page++)
    {
        eeprom_page_write(page, trans_buf + EE_PAGE_SIZE * page);
    }
    /* read e2 */
    for (i = 0; i < sizeof(trans_buf); i++)
    {
        recv_buf[i] = 0;
    }
    for (page = 0; page < EE_TEST_PAGE_CNT; page++)
    {
        eeprom_page_read(page, recv_buf + EE_PAGE_SIZE * page);
    }
    /* compare e2 */
    for (i = 0; i < sizeof(recv_buf); i++)
    {
        if (trans_buf[i] != recv_buf[i])
        {
            compareValueDiff = 1;
            break;
        }
    }
    if (compareValueDiff == 0)
    {
        rt_kprintf("eeprom test ok!\r\n");
    }
    else
    {
        rt_kprintf("eeprom test failed!\r\n");
    }
}

/* TCA9539 device */
#if defined(HC32F472) || defined(HC32F4A0) || defined(HC32F448)

/* TCA9539 define */
#define TCA9539_DEV_ADDR                (0x74)       // TCA9539 chip address on I2C bus

#define TCA9539_REG_INPUT_PORT0         (0x00U)
#define TCA9539_REG_INPUT_PORT1         (0x01U)
#define TCA9539_REG_OUTPUT_PORT0        (0x02U)
#define TCA9539_REG_OUTPUT_PORT1        (0x03U)
#define TCA9539_REG_INVERT_PORT0        (0x04U)
#define TCA9539_REG_INVERT_PORT1        (0x05U)
#define TCA9539_REG_CONFIG_PORT0        (0x06U)
#define TCA9539_REG_CONFIG_PORT1        (0x07U)

void tca9539_test(void)
{
    struct rt_i2c_bus_device *hc32_i2c = RT_NULL;
    static rt_uint8_t send_buf0[0x10];
    static rt_uint8_t send_buf1[0x10], recv_buf1[0x10];
    struct rt_i2c_msg msg[2];

#if defined (BSP_USING_I2C_HW)
    hc32_i2c = rt_i2c_bus_device_find(HW_I2C_DEV);  //hw i2c
#else
    hc32_i2c = rt_i2c_bus_device_find(SW_I2C_DEV);  //sw i2c
#endif
    RT_ASSERT(hc32_i2c != RT_NULL);

    send_buf0[0] = TCA9539_REG_CONFIG_PORT1;
    send_buf0[1] = 0xFF;
    msg[0].addr  = TCA9539_DEV_ADDR;
    msg[0].flags = RT_I2C_WR;
    msg[0].len   = 2;
    msg[0].buf   = send_buf0;
    rt_i2c_transfer(hc32_i2c, &msg[0], 1);

    send_buf0[0] = TCA9539_REG_OUTPUT_PORT1;
    send_buf0[1] = 0xAC;
    msg[1].addr  = TCA9539_DEV_ADDR;
    msg[1].flags = RT_I2C_WR;
    msg[1].len   = 2;
    msg[1].buf   = send_buf0;
    rt_i2c_transfer(hc32_i2c, &msg[1], 1);

    /* read */
    send_buf1[0] = TCA9539_REG_OUTPUT_PORT1;
    msg[0].addr  = TCA9539_DEV_ADDR;
    msg[0].flags = RT_I2C_WR;
    msg[0].len   = 1;
    msg[0].buf   = send_buf1;

    msg[1].addr  = TCA9539_DEV_ADDR;
    msg[1].flags = RT_I2C_RD;
    msg[1].len   = 1;
    msg[1].buf   = recv_buf1;
    rt_i2c_transfer(hc32_i2c, &msg[0], 2);

    if (recv_buf1[0] == 0xAC)
    {
        rt_kprintf("tca9539 test ok!\r\n");
    }
    else
    {
        rt_kprintf("tca9539 test failed!\r\n");
    }
}
#endif

static void i2c_sample(int argc, char *argv[])
{
    eeprom_test();
#if defined(HC32F472) || defined(HC32F4A0) || defined(HC32F448)
    tca9539_test();
#endif
}

MSH_CMD_EXPORT(i2c_sample, i2c sample);

#endif/* RT_USING_I2C */

/*
 EOF
*/
