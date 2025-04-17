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
INIT_COMPONENT_EXPORT(rt_hw_spiflash_init);
#endif /* BOARD_USING_STORAGE_SPIFLASH */

#if defined(RT_USING_MTD_NAND) && defined(BSP_USING_FMINAND)
struct rt_mtd_nand_device mtd_partitions[MTD_FMINAND_PARTITION_NUM] =
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
        .block_end   = 1023,
        .block_total = 960,
    },
    [2] =
    {
        /*nand2: Whole blocks size, overlay*/
        .block_start = 0,
        .block_end   = 1023,
        .block_total = 1024,
    }
};
#endif

#if defined(BOARD_USING_NAU8822) && defined(NU_PKG_USING_NAU8822)
#include <acodec_nau8822.h>
S_NU_NAU8822_CONFIG sCodecConfig =
{
    .i2c_bus_name = "i2c0",

    .i2s_bus_name = "sound0",

    .pin_phonejack_en = 0,

    .pin_phonejack_det = 0,
};

int rt_hw_nau8822_port(void)
{
    if (nu_hw_nau8822_init(&sCodecConfig) != RT_EOK)
        return -1;

    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_nau8822_port);
#endif /* BOARD_USING_NAU8822 */

#if defined(NU_PKG_USING_ADC_TOUCH)
#include "adc_touch.h"
S_CALIBRATION_MATRIX g_sCalMat = { 13321, -53, -1069280, 96, 8461, -1863312, 65536 };
#endif

#if defined(NU_PKG_USING_TPC_GT911) && defined(BOARD_USING_GT911)
#include "drv_gpio.h"
#include "gt911.h"

#define TPC_RST_PIN   NU_GET_PININDEX(NU_PG, 4)
#define TPC_IRQ_PIN   NU_GET_PININDEX(NU_PG, 5)

extern int tpc_sample(const char *name);
int rt_hw_gt911_port(void)
{
    struct rt_touch_config cfg;
    rt_uint8_t rst_pin;

    rst_pin = TPC_RST_PIN;
    cfg.dev_name = "i2c0";
    cfg.irq_pin.pin = TPC_IRQ_PIN;
    cfg.irq_pin.mode = PIN_MODE_INPUT_PULLDOWN;
    cfg.user_data = &rst_pin;

    rt_hw_gt911_init("gt911", &cfg);

    return tpc_sample("gt911");
}
INIT_ENV_EXPORT(rt_hw_gt911_port);
#endif /* if defined(NU_PKG_USING_TPC_GT911) && defined(BOARD_USING_GT911) */

#if defined(NU_PKG_USING_TPC_FT5446) && defined(BOARD_USING_FT5446)
#include "drv_gpio.h"
#include "ft5446.h"

#define TPC_RST_PIN   NU_GET_PININDEX(NU_PG, 4)
#define TPC_IRQ_PIN   NU_GET_PININDEX(NU_PG, 5)

extern int tpc_sample(const char *name);
int rt_hw_gt911_port(void)
{
    struct rt_touch_config cfg;
    rt_uint8_t rst_pin;

    rst_pin = TPC_RST_PIN;
    cfg.dev_name = "i2c0";
    cfg.irq_pin.pin = TPC_IRQ_PIN;
    cfg.irq_pin.mode = PIN_MODE_INPUT;//PIN_MODE_INPUT_PULLDOWN;
    cfg.user_data = &rst_pin;

    rt_hw_ft5446_init("ft5446", &cfg);

    return tpc_sample("ft5446");
}
INIT_ENV_EXPORT(rt_hw_gt911_port);
#endif /* if defined(NU_PKG_USING_TPC_FT5446) && defined(BOARD_USING_FT5446) */


#if defined(BOARD_USING_BUZZER)

#define PWM_DEV_NAME       "pwm0"
#define PWM_DEV_CHANNEL    (1)

static void PlayRingTone(void)
{
    struct rt_device_pwm *pwm_dev;
    rt_uint32_t period;
    int i, j;

    period = 1000;

    if ((pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME)) != RT_NULL)
    {
        rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, period);
        rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);

        for (j = 0; j < 3; j++)
        {
            for (i = 0; i < 10; i++)
            {
                rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, period);
                rt_thread_mdelay(50);

                rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, period / 2);
                rt_thread_mdelay(50);
            }

            /* Mute 2 seconds */
            rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, period);
            rt_thread_mdelay(2000);
        }
        rt_pwm_disable(pwm_dev, PWM_DEV_CHANNEL);
    }
    else
    {
        rt_kprintf("Can't find %s\n", PWM_DEV_NAME);
    }
}

#if defined(BOARD_USING_LCM)

#if defined(PKG_USING_GUIENGINE)
    #include <rtgui/driver.h>
#endif

#if defined(RT_USING_PIN)
    #include <drv_gpio.h>

    /* defined the LCM_BLEN pin: PH3 */
    #define LCM_BACKLIGHT_CTRL  NU_GET_PININDEX(NU_PH, 3)
#endif

#define PWM_DEV_NAME         "pwm0"
#define LCM_PWM_CHANNEL      (0)

void nu_lcd_backlight_on(void)
{
    struct rt_device_pwm *pwm_dev;

    if ((pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME)) != RT_NULL)
    {
        rt_pwm_enable(pwm_dev, LCM_PWM_CHANNEL);
        rt_pwm_set(pwm_dev, LCM_PWM_CHANNEL, 100000, 100);
    }
    else
    {
        rt_kprintf("Can't find %s\n", PWM_DEV_NAME);
    }

    rt_pin_mode(LCM_BACKLIGHT_CTRL, PIN_MODE_OUTPUT);
    rt_pin_write(LCM_BACKLIGHT_CTRL, PIN_HIGH);
}

void nu_lcd_backlight_off(void)
{
    struct rt_device_pwm *pwm_dev;

    if ((pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME)) != RT_NULL)
    {
        rt_pwm_disable(pwm_dev, LCM_PWM_CHANNEL);
    }
    else
    {
        rt_kprintf("Can't find %s\n", PWM_DEV_NAME);
    }

    rt_pin_mode(LCM_BACKLIGHT_CTRL, PIN_MODE_OUTPUT);
    rt_pin_write(LCM_BACKLIGHT_CTRL, PIN_LOW);
}

int rt_hw_lcm_port(void)
{
#if defined(PKG_USING_GUIENGINE)
    rt_device_t lcm_vpost;
    lcm_vpost = rt_device_find("lcd");
    if (lcm_vpost)
    {
        rtgui_graphic_set_device(lcm_vpost);
    }
#endif

    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_lcm_port);
#endif /* BOARD_USING_LCM */


int buzzer_test(void)
{
    PlayRingTone();
    return 0;
}
#ifdef FINSH_USING_MSH
    MSH_CMD_EXPORT(buzzer_test, Buzzer - Play ring tone);
#endif
#endif /* BOARD_USING_BUZZER */

#if defined(BOARD_USING_RS485)

#include <drv_uart.h>

int test_rs485(int argc, char **argv)
{
    rt_device_t serial;
    char txbuf[16];
    rt_err_t ret;
    int str_len;

    if (argc < 2)
        goto exit_test_rs485;

    serial = rt_device_find(argv[1]);
    if (!serial)
    {
        rt_kprintf("Can't find %s. EXIT.\n", argv[1]);
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

    return 0;

exit_test_rs485:

    return -1;
}
MSH_CMD_EXPORT(test_rs485, test rs485 communication);

#endif //defined(BOARD_USING_RS485)

