/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-6-1        Wayne        First version
*
******************************************************************************/

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_gpio.h"
#include "drv_sys.h"
#include "drv_sspcc.h"

#include "board.h"


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
    if (nu_qspi_bus_attach_device("qspi0", "qspi01", 4, SpiFlash_EnterQspiMode, SpiFlash_ExitQspiMode) != RT_EOK)
        return -1;

#if defined(RT_USING_SFUD)
    if (rt_sfud_flash_probe(FAL_USING_NOR_FLASH_DEV_NAME, "qspi01") == RT_NULL)
    {
        return -(RT_ERROR);
    }
#endif
    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_spiflash_init);
#endif /* BOARD_USING_STORAGE_SPIFLASH */

#if defined(BOARD_USING_STORAGE_SPINAND) && defined(NU_PKG_USING_SPINAND)

#include "drv_qspi.h"
#include "spinand.h"

struct rt_mtd_nand_device mtd_partitions[MTD_SPINAND_PARTITION_NUM] =
{
    [0] =
    {
        /*nand0: U-boot, env, rtthread*/
        .block_start = 0,
        .block_end   = 63,
        .block_total = 64,
    },
    [1] =
    {
        /*nand1: for filesystem mounting*/
        .block_start = 64,
        .block_end   = 4095,
        .block_total = 4032,
    },
    [2] =
    {
        /*nand2: Whole blocks size, overlay*/
        .block_start = 0,
        .block_end   = 4095,
        .block_total = 4096,
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

INIT_DEVICE_EXPORT(rt_hw_spinand_init);
#endif

#if defined(BOARD_USING_STORAGE_RAWNAND) && defined(BSP_USING_NFI)
struct rt_mtd_nand_device mtd_partitions_nfi[MTD_NFI_PARTITION_NUM] =
{
    [0] =
    {
        /*nand0:  rtthread*/
        .block_start = 0,
        .block_end   = 63,
        .block_total = 64,
    },
    [1] =
    {
        /*nand1: for filesystem mounting*/
        .block_start = 64,
        .block_end   = 8191,
        .block_total = 8128,
    },
    [2] =
    {
        /*nand2: Whole blocks size, overlay*/
        .block_start = 0,
        .block_end   = 8191,
        .block_total = 8192,
    }
};
#endif

#if defined(BOARD_USING_NAU8822) && defined(NU_PKG_USING_NAU8822)
#include <acodec_nau8822.h>
S_NU_NAU8822_CONFIG sCodecConfig =
{
    .i2c_bus_name = "i2c1",

    .i2s_bus_name = "sound0",

    .pin_phonejack_en = NU_GET_PININDEX(NU_PC, 2),

    .pin_phonejack_det = NU_GET_PININDEX(NU_PC, 3),
};

int rt_hw_nau8822_port(void)
{
    if (nu_hw_nau8822_init(&sCodecConfig) != RT_EOK)
        return -1;

    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_nau8822_port);
#endif /* BOARD_USING_NAU8822 */


#if defined(BOARD_USING_SENSOR0)
#include "ccap_sensor.h"

#define SENSOR0_RST_PIN    NU_GET_PININDEX(NU_PM, 1)
#define SENSOR0_PD_PIN     NU_GET_PININDEX(NU_PC, 12)

ccap_sensor_io sIo_sensor0 =
{
    .RstPin          = SENSOR0_RST_PIN,
    .PwrDwnPin       = SENSOR0_PD_PIN,
    .I2cName         = "i2c2"
};
#endif /* BOARD_USING_SENSOR0 */
int rt_hw_sensors_port(void)
{
#if defined(BOARD_USING_SENSOR0)
    nu_ccap_sensor_create(&sIo_sensor0, (ccap_sensor_id)BOARD_USING_SENSON0_ID, "sensor0");
#endif
    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_sensors_port);
void nu_rtp_sspcc_setup(void)
{
    /* PDMA2/3 */
    SSPCC_SET_REALM(SSPCC_PDMA2, SSPCC_SSET_SUBM);
    SSPCC_SET_REALM(SSPCC_PDMA3, SSPCC_SSET_SUBM);
}

static S_NU_REG s_NuReg_arr[] =
{
    /* QSPI0 */
    NUREG_EXPORT(CLK_CLKSEL4, CLK_CLKSEL4_QSPI0SEL_Msk, CLK_CLKSEL4_QSPI0SEL_PCLK0),
    NUREG_EXPORT(CLK_APBCLK1, CLK_APBCLK1_QSPI0CKEN_Msk, CLK_APBCLK1_QSPI0CKEN_Msk),
    NUREG_EXPORT(SYS_GPD_MFPL, SYS_GPD_MFPL_PD5MFP_Msk, SYS_GPD_MFPL_PD5MFP_QSPI0_MISO1),
    NUREG_EXPORT(SYS_GPD_MFPL, SYS_GPD_MFPL_PD4MFP_Msk, SYS_GPD_MFPL_PD4MFP_QSPI0_MOSI1),
    NUREG_EXPORT(SYS_GPD_MFPL, SYS_GPD_MFPL_PD3MFP_Msk, SYS_GPD_MFPL_PD3MFP_QSPI0_MISO0),
    NUREG_EXPORT(SYS_GPD_MFPL, SYS_GPD_MFPL_PD2MFP_Msk, SYS_GPD_MFPL_PD2MFP_QSPI0_MOSI0),
    NUREG_EXPORT(SYS_GPD_MFPL, SYS_GPD_MFPL_PD1MFP_Msk, SYS_GPD_MFPL_PD1MFP_QSPI0_CLK),
    NUREG_EXPORT(SYS_GPD_MFPL, SYS_GPD_MFPL_PD0MFP_Msk, SYS_GPD_MFPL_PD0MFP_QSPI0_SS0),

    /* TIMERn */
    NUREG_EXPORT(CLK_APBCLK0, CLK_APBCLK0_TMR0CKEN_Msk, CLK_APBCLK0_TMR0CKEN_Msk),
    NUREG_EXPORT(CLK_APBCLK0, CLK_APBCLK0_TMR1CKEN_Msk, CLK_APBCLK0_TMR1CKEN_Msk),
    NUREG_EXPORT(CLK_APBCLK0, CLK_APBCLK0_TMR2CKEN_Msk, CLK_APBCLK0_TMR2CKEN_Msk),
    NUREG_EXPORT(CLK_APBCLK0, CLK_APBCLK0_TMR3CKEN_Msk, CLK_APBCLK0_TMR3CKEN_Msk),
    NUREG_EXPORT(CLK_APBCLK0, CLK_APBCLK0_TMR4CKEN_Msk, CLK_APBCLK0_TMR4CKEN_Msk),
    NUREG_EXPORT(CLK_APBCLK0, CLK_APBCLK0_TMR5CKEN_Msk, CLK_APBCLK0_TMR5CKEN_Msk),
    NUREG_EXPORT(CLK_APBCLK0, CLK_APBCLK0_TMR6CKEN_Msk, CLK_APBCLK0_TMR6CKEN_Msk),
    NUREG_EXPORT(CLK_APBCLK0, CLK_APBCLK0_TMR7CKEN_Msk, CLK_APBCLK0_TMR7CKEN_Msk),
    NUREG_EXPORT(CLK_APBCLK0, CLK_APBCLK0_TMR8CKEN_Msk, CLK_APBCLK0_TMR8CKEN_Msk),
    NUREG_EXPORT(CLK_APBCLK0, CLK_APBCLK0_TMR9CKEN_Msk, CLK_APBCLK0_TMR9CKEN_Msk),
    NUREG_EXPORT(CLK_APBCLK0, CLK_APBCLK0_TMR10CKEN_Msk, CLK_APBCLK0_TMR10CKEN_Msk),
    NUREG_EXPORT(CLK_APBCLK0, CLK_APBCLK0_TMR11CKEN_Msk, CLK_APBCLK0_TMR11CKEN_Msk),
    {0}
};

void nu_check_register(void)
{
    nu_sys_check_register(&s_NuReg_arr[0]);
}
MSH_CMD_EXPORT(nu_check_register, Check registers);
