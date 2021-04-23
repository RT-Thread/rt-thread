/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-1-16       Wayne        First version
*
******************************************************************************/

#include <rtdevice.h>
#include <drv_gpio.h>

#if defined(BOARD_USING_STORAGE_SPIFLASH)
#if defined(RT_USING_SFUD)
    #include "spi_flash.h"
    #include "spi_flash_sfud.h"
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
    /* Here, we use Dual I/O to drive the SPI flash by default. */
    /* If you want to use Quad I/O, you can modify to 4 from 2 and crossover D2/D3 pin of SPI flash. */
    if (nu_qspi_bus_attach_device("qspi0", "qspi01", 2, SpiFlash_EnterQspiMode, SpiFlash_ExitQspiMode) != RT_EOK)
        return -1;

#if defined(RT_USING_SFUD)
    if (rt_sfud_flash_probe("flash0", "qspi01") == RT_NULL)
    {
        return -(RT_ERROR);
    }
#endif
    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_spiflash_init);
#endif /* BOARD_USING_STORAGE_SPIFLASH */

#if defined(BOARD_USING_SRAM0_AS_MEMHEAP)
/*
In Advance board design, SRAM address bus A16/A17/A18 are GPIO-controlled by SW, not EBI.
So we just remap 128KB only to RTT memory heap, due to it is out of controll.
AD0~AD15: 2^16*16bit = 128KB
*/
#include <drv_ebi.h>
#include "NuMicro.h"
static struct rt_memheap system_heap;
int nu_use_exsram_as_heap(void)
{
    rt_err_t ret;

    /* Open ebi bank1 */
    ret = nu_ebi_init(EBI_BANK1, EBI_BUSWIDTH_16BIT, EBI_TIMING_SLOWEST, EBI_OPMODE_NORMAL, EBI_CS_ACTIVE_LOW);
    if (ret != RT_EOK)
        return ret;

    /* Initial sram as heap */
    return rt_memheap_init(&system_heap, "nu_sram_heap", (void *)EBI_BANK1_BASE_ADDR, 128 * 1024);
}
INIT_BOARD_EXPORT(nu_use_exsram_as_heap);
#endif /* BOARD_USING_SRAM0_AS_MEMHEAP */


#if defined(BOARD_USING_MAX31875)
#include <sensor_max31875.h>
int rt_hw_max31875_port(void)
{
    struct rt_sensor_config cfg;

    cfg.intf.dev_name = "i2c1";
    cfg.intf.user_data = (void *)MAX31875_I2C_SLAVE_ADR_R0;
    cfg.irq_pin.pin = RT_PIN_NONE;

    rt_hw_max31875_init("max31875", &cfg);
    return 0;
}
INIT_APP_EXPORT(rt_hw_max31875_port);
#endif /* BOARD_USING_MAX31875 */

#if defined(BOARD_USING_MPU6500)
#include <sensor_inven_mpu6xxx.h>
int rt_hw_mpu6500_port(void)
{
    struct rt_sensor_config cfg;

    cfg.intf.dev_name = "i2c2";
    cfg.intf.user_data = (void *)MPU6XXX_ADDR_DEFAULT;
    cfg.irq_pin.pin = RT_PIN_NONE;

    rt_hw_mpu6xxx_init("mpu",  &cfg);
    return 0;
}
INIT_APP_EXPORT(rt_hw_mpu6500_port);
#endif /* BOARD_USING_MPU6500 */

#if defined(BOARD_USING_LCD_ILI9341) && defined(NU_PKG_USING_ILI9341_EBI)
#include <lcd_ili9341.h>
#if defined(PKG_USING_GUIENGINE)
    #include <rtgui/driver.h>
#endif
int rt_hw_ili9341_port(void)
{
    rt_err_t ret = RT_EOK;

    /* Open ebi BOARD_USING_ILI9341_EBI_PORT */
    ret = nu_ebi_init(BOARD_USING_ILI9341_EBI_PORT, EBI_BUSWIDTH_16BIT, EBI_TIMING_NORMAL, EBI_OPMODE_NORMAL, EBI_CS_ACTIVE_LOW);
    if (ret != RT_EOK)
        return ret;

    switch (BOARD_USING_ILI9341_EBI_PORT)
    {
    case 0:
        EBI->CTL0 |= EBI_CTL0_CACCESS_Msk;
        EBI->TCTL0 |= (EBI_TCTL0_WAHDOFF_Msk | EBI_TCTL0_RAHDOFF_Msk);
        break;
    case 1:
        EBI->CTL1 |= EBI_CTL1_CACCESS_Msk;
        EBI->TCTL1 |= (EBI_TCTL1_WAHDOFF_Msk | EBI_TCTL1_RAHDOFF_Msk);
        break;
    case 2:
        EBI->CTL2 |= EBI_CTL2_CACCESS_Msk;
        EBI->TCTL2 |= (EBI_TCTL2_WAHDOFF_Msk | EBI_TCTL2_RAHDOFF_Msk);
        break;
    default:
        return -1;
    }

    if (rt_hw_lcd_ili9341_ebi_init(EBI_BANK0_BASE_ADDR + BOARD_USING_ILI9341_EBI_PORT * EBI_MAX_SIZE) != RT_EOK)
        return -1;

    rt_hw_lcd_ili9341_init();

#if defined(PKG_USING_GUIENGINE)
    rt_device_t lcd_ili9341;
    lcd_ili9341 = rt_device_find("lcd");
    if (lcd_ili9341)
    {
        rtgui_graphic_set_device(lcd_ili9341);
    }
#endif

    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_ili9341_port);
#endif /* BOARD_USING_LCD_ILI9341 */

#if defined(BOARD_USING_NAU88L25) && defined(NU_PKG_USING_NAU88L25)
#include <acodec_nau88l25.h>
S_NU_NAU88L25_CONFIG sCodecConfig =
{
    .i2c_bus_name = "i2c2",

    .i2s_bus_name = "sound0",

    .pin_phonejack_en = NU_GET_PININDEX(NU_PE, 13),

    .pin_phonejack_det = 0,
};

int rt_hw_nau88l25_port(void)
{
    if (nu_hw_nau88l25_init(&sCodecConfig) != RT_EOK)
        return -1;

    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_nau88l25_port);
#endif /* BOARD_USING_NAU88L25 */

#if defined(BOARD_USING_BUZZER)

#define BPWM_DEV_NAME       "bpwm0"
#define BPWM_DEV_CHANNEL    (5)

static void PlayRingTone(void)
{
    struct rt_device_pwm *bpwm_dev;
    rt_uint32_t period;
    int i, j;

    period = 1000;

    if ((bpwm_dev = (struct rt_device_pwm *)rt_device_find(BPWM_DEV_NAME)) != RT_NULL)
    {
        rt_pwm_set(bpwm_dev, BPWM_DEV_CHANNEL, period, period);
        rt_pwm_enable(bpwm_dev, BPWM_DEV_CHANNEL);

        for (j = 0; j < 5; j++)
        {
            for (i = 0; i < 10; i++)
            {
                rt_pwm_set(bpwm_dev, BPWM_DEV_CHANNEL, period, period);
                rt_thread_mdelay(50);

                rt_pwm_set(bpwm_dev, BPWM_DEV_CHANNEL, period, period / 2);
                rt_thread_mdelay(50);
            }

            /* Mute 2 seconds */
            rt_pwm_set(bpwm_dev, BPWM_DEV_CHANNEL, period, period);
            rt_thread_mdelay(2000);
        }
        rt_pwm_disable(bpwm_dev, BPWM_DEV_CHANNEL);
    }
    else
    {
        rt_kprintf("Can't find %s\n", BPWM_DEV_NAME);
    }
}

int buzzer_test(void)
{
    PlayRingTone();
    return 0;
}
#ifdef FINSH_USING_MSH
    MSH_CMD_EXPORT(buzzer_test, Buzzer - Play ring tone);
#endif
#endif /* BOARD_USING_BUZZER */
