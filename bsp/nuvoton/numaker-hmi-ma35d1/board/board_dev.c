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

#if defined(BOARD_USING_MPU6500) && defined(PKG_USING_MPU6XXX)

#include "sensor_inven_mpu6xxx.h"

int rt_hw_mpu6xxx_port(void)
{
    struct rt_sensor_config cfg;
    rt_base_t mpu_int = NU_GET_PININDEX(NU_PL, 8);

    cfg.intf.dev_name = "i2c1";
    cfg.intf.arg = (void *)MPU6XXX_ADDR_DEFAULT;
    cfg.irq_pin.pin = mpu_int;

    return rt_hw_mpu6xxx_init("mpu", &cfg);
}
INIT_APP_EXPORT(rt_hw_mpu6xxx_port);
#endif /* BOARD_USING_MPU6500 */

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
    .i2c_bus_name = "i2c2",

    .i2s_bus_name = "sound0",

    .pin_phonejack_en = NU_GET_PININDEX(NU_PD, 13),

    .pin_phonejack_det = NU_GET_PININDEX(NU_PI, 0),
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
S_CALIBRATION_MATRIX g_sCalMat = { -17558, 1, 69298832, -10, 11142, -2549195, 65536 };
#endif

#if defined(NU_PKG_USING_TPC_GT911) && defined(BOARD_USING_GT911)
#include "drv_gpio.h"
#include "gt911.h"

#define TPC_RST_PIN   NU_GET_PININDEX(NU_PM, 12)
#define TPC_IRQ_PIN   NU_GET_PININDEX(NU_PD, 12)

extern int tpc_sample(const char *name);
int rt_hw_gt911_port(void)
{
    struct rt_touch_config cfg;
    rt_uint8_t rst_pin;

    rst_pin = TPC_RST_PIN;
    cfg.dev_name = "i2c5";
    cfg.irq_pin.pin = TPC_IRQ_PIN;
    cfg.irq_pin.mode = PIN_MODE_INPUT_PULLDOWN;
    cfg.user_data = &rst_pin;

    rt_hw_gt911_init("gt911", &cfg);

    return tpc_sample("gt911");
}
INIT_ENV_EXPORT(rt_hw_gt911_port);
#endif /* if defined(BOARD_USING_GT911) && defined(PKG_USING_GT911) */

#if defined(BOARD_USING_BUZZER)

#define EPWM_DEV_NAME       "epwm1"
#define EPWM_DEV_CHANNEL    (5)

static void PlayRingTone(void)
{
    struct rt_device_pwm *epwm_dev;
    rt_uint32_t period;
    int i, j;

    period = 1000;

    if ((epwm_dev = (struct rt_device_pwm *)rt_device_find(EPWM_DEV_NAME)) != RT_NULL)
    {
        rt_pwm_set(epwm_dev, EPWM_DEV_CHANNEL, period, period);
        rt_pwm_enable(epwm_dev, EPWM_DEV_CHANNEL);

        for (j = 0; j < 5; j++)
        {
            for (i = 0; i < 10; i++)
            {
                rt_pwm_set(epwm_dev, EPWM_DEV_CHANNEL, period, period);
                rt_thread_mdelay(50);

                rt_pwm_set(epwm_dev, EPWM_DEV_CHANNEL, period, period / 2);
                rt_thread_mdelay(50);
            }

            /* Mute 2 seconds */
            rt_pwm_set(epwm_dev, EPWM_DEV_CHANNEL, period, period);
            rt_thread_mdelay(2000);
        }
        rt_pwm_disable(epwm_dev, EPWM_DEV_CHANNEL);
    }
    else
    {
        rt_kprintf("Can't find %s\n", EPWM_DEV_NAME);
    }
}

#if defined(BOARD_USING_LCM)

#if defined(PKG_USING_GUIENGINE)
    #include <rtgui/driver.h>
#endif

#if defined(RT_USING_PIN)
    #include <drv_gpio.h>

    /* defined the LCM_BLEN pin: PK7 */
    #define LCM_BACKLIGHT_CTRL  NU_GET_PININDEX(NU_PK, 7)
#endif

#define EPWM_DEV_NAME       "epwm1"
#define LCM_PWM_CHANNEL      (1)

void nu_lcd_backlight_on(void)
{
    struct rt_device_pwm *pwm_dev;

    if ((pwm_dev = (struct rt_device_pwm *)rt_device_find(EPWM_DEV_NAME)) != RT_NULL)
    {
        rt_pwm_enable(pwm_dev, LCM_PWM_CHANNEL);
        rt_pwm_set(pwm_dev, LCM_PWM_CHANNEL, 100000, 100);
    }
    else
    {
        rt_kprintf("Can't find %s\n", EPWM_DEV_NAME);
    }

    rt_pin_mode(LCM_BACKLIGHT_CTRL, PIN_MODE_OUTPUT);
    rt_pin_write(LCM_BACKLIGHT_CTRL, PIN_HIGH);
}

void nu_lcd_backlight_off(void)
{
    struct rt_device_pwm *pwm_dev;

    if ((pwm_dev = (struct rt_device_pwm *)rt_device_find(EPWM_DEV_NAME)) != RT_NULL)
    {
        rt_pwm_disable(pwm_dev, LCM_PWM_CHANNEL);
    }
    else
    {
        rt_kprintf("Can't find %s\n", EPWM_DEV_NAME);
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

#if defined(BOARD_USING_SENSOR0)
#include "ccap_sensor.h"

#define SENSOR0_RST_PIN    NU_GET_PININDEX(NU_PM, 1)
#define SENSOR0_PD_PIN     NU_GET_PININDEX(NU_PK, 8)

ccap_sensor_io sIo_sensor0 =
{
    .RstPin          = SENSOR0_RST_PIN,
    .PwrDwnPin       = SENSOR0_PD_PIN,
    .I2cName         = "i2c3"
};
#endif /* BOARD_USING_SENSOR0 */

#if defined(BOARD_USING_SENSOR1)
#include "ccap_sensor.h"

#define SENSOR1_RST_PIN    NU_GET_PININDEX(NU_PN, 14)
#define SENSOR1_PD_PIN     NU_GET_PININDEX(NU_PD, 15)

ccap_sensor_io sIo_sensor1 =
{
    .RstPin          = SENSOR1_RST_PIN,
    .PwrDwnPin       = SENSOR1_PD_PIN,
    .I2cName         = "i2c4"
};
#endif /* BOARD_USING_SENSOR1 */

int rt_hw_sensors_port(void)
{
#if defined(BOARD_USING_SENSOR0)
    nu_ccap_sensor_create(&sIo_sensor0, (ccap_sensor_id)BOARD_USING_SENSON0_ID, "sensor0");
#endif
#if defined(BOARD_USING_SENSOR1)
    nu_ccap_sensor_create(&sIo_sensor1, (ccap_sensor_id)BOARD_USING_SENSON1_ID, "sensor1");
#endif
    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_sensors_port);


void nu_rtp_sspcc_setup(void)
{
    SSPCC_SET_REALM(SSPCC_UART16, SSPCC_SSET_SUBM);
    SSPCC_SET_REALM(SSPCC_TMR23, SSPCC_SSET_SUBM);

    /* PDMA2/3 */
    SSPCC_SET_REALM(SSPCC_PDMA2, SSPCC_SSET_SUBM);
    SSPCC_SET_REALM(SSPCC_PDMA3, SSPCC_SSET_SUBM);

    /* UART16 Pins */
    SSPCC_SET_GPIO_REALM(PK, 0, SSPCC_SSET_SUBM);
    SSPCC_SET_GPIO_REALM(PK, 1, SSPCC_SSET_SUBM);
    SSPCC_SET_GPIO_REALM(PK, 2, SSPCC_SSET_SUBM);
    SSPCC_SET_GPIO_REALM(PK, 3, SSPCC_SSET_SUBM);

    /* LED_1 Pin */
    SSPCC_SET_GPIO_REALM(PJ, 15, SSPCC_SSET_SUBM);
}

#define CLK_CLKDIV0_DCUPDIV_2       CLK_CLKDIV0_DCUP(1)
#define DISP_FRAMEBUFFERCONFIG0     (DISP_BASE + 0x1518U)
#define DISP_OVERLAYCONFIG0         (DISP_BASE + 0x1540U)

static S_NU_REG s_NuReg_arr[] =
{
    /* DISP PIN */
    NUREG_EXPORT(SYS_GPH_MFPH, SYS_GPH_MFPH_PH15MFP_Msk, SYS_GPH_MFPH_PH15MFP_LCM_DATA23),
    NUREG_EXPORT(SYS_GPH_MFPH, SYS_GPH_MFPH_PH14MFP_Msk, SYS_GPH_MFPH_PH14MFP_LCM_DATA22),
    NUREG_EXPORT(SYS_GPH_MFPH, SYS_GPH_MFPH_PH13MFP_Msk, SYS_GPH_MFPH_PH13MFP_LCM_DATA21),
    NUREG_EXPORT(SYS_GPH_MFPH, SYS_GPH_MFPH_PH12MFP_Msk, SYS_GPH_MFPH_PH12MFP_LCM_DATA20),

    NUREG_EXPORT(SYS_GPC_MFPH, SYS_GPC_MFPH_PC15MFP_Msk, SYS_GPC_MFPH_PC15MFP_LCM_DATA19),
    NUREG_EXPORT(SYS_GPC_MFPH, SYS_GPC_MFPH_PC14MFP_Msk, SYS_GPC_MFPH_PC14MFP_LCM_DATA18),
    NUREG_EXPORT(SYS_GPC_MFPH, SYS_GPC_MFPH_PC13MFP_Msk, SYS_GPC_MFPH_PC13MFP_LCM_DATA17),
    NUREG_EXPORT(SYS_GPC_MFPH, SYS_GPC_MFPH_PC12MFP_Msk, SYS_GPC_MFPH_PC12MFP_LCM_DATA16),

    NUREG_EXPORT(SYS_GPH_MFPL, SYS_GPH_MFPL_PH7MFP_Msk, SYS_GPH_MFPL_PH7MFP_LCM_DATA15),
    NUREG_EXPORT(SYS_GPH_MFPL, SYS_GPH_MFPL_PH6MFP_Msk, SYS_GPH_MFPL_PH6MFP_LCM_DATA14),
    NUREG_EXPORT(SYS_GPH_MFPL, SYS_GPH_MFPL_PH5MFP_Msk, SYS_GPH_MFPL_PH5MFP_LCM_DATA13),
    NUREG_EXPORT(SYS_GPH_MFPL, SYS_GPH_MFPL_PH4MFP_Msk, SYS_GPH_MFPL_PH4MFP_LCM_DATA12),
    NUREG_EXPORT(SYS_GPH_MFPL, SYS_GPH_MFPL_PH3MFP_Msk, SYS_GPH_MFPL_PH3MFP_LCM_DATA11),
    NUREG_EXPORT(SYS_GPH_MFPL, SYS_GPH_MFPL_PH2MFP_Msk, SYS_GPH_MFPL_PH2MFP_LCM_DATA10),
    NUREG_EXPORT(SYS_GPH_MFPL, SYS_GPH_MFPL_PH1MFP_Msk, SYS_GPH_MFPL_PH1MFP_LCM_DATA9),
    NUREG_EXPORT(SYS_GPH_MFPL, SYS_GPH_MFPL_PH0MFP_Msk, SYS_GPH_MFPL_PH0MFP_LCM_DATA8),

    NUREG_EXPORT(SYS_GPI_MFPH, SYS_GPI_MFPH_PI15MFP_Msk, SYS_GPI_MFPH_PI15MFP_LCM_DATA7),
    NUREG_EXPORT(SYS_GPI_MFPH, SYS_GPI_MFPH_PI14MFP_Msk, SYS_GPI_MFPH_PI14MFP_LCM_DATA6),
    NUREG_EXPORT(SYS_GPI_MFPH, SYS_GPI_MFPH_PI13MFP_Msk, SYS_GPI_MFPH_PI13MFP_LCM_DATA5),
    NUREG_EXPORT(SYS_GPI_MFPH, SYS_GPI_MFPH_PI12MFP_Msk, SYS_GPI_MFPH_PI12MFP_LCM_DATA4),
    NUREG_EXPORT(SYS_GPI_MFPH, SYS_GPI_MFPH_PI11MFP_Msk, SYS_GPI_MFPH_PI11MFP_LCM_DATA3),
    NUREG_EXPORT(SYS_GPI_MFPH, SYS_GPI_MFPH_PI10MFP_Msk, SYS_GPI_MFPH_PI10MFP_LCM_DATA2),
    NUREG_EXPORT(SYS_GPI_MFPH, SYS_GPI_MFPH_PI9MFP_Msk, SYS_GPI_MFPH_PI9MFP_LCM_DATA1),
    NUREG_EXPORT(SYS_GPI_MFPH, SYS_GPI_MFPH_PI8MFP_Msk, SYS_GPI_MFPH_PI8MFP_LCM_DATA0),

    NUREG_EXPORT(SYS_GPK_MFPL, SYS_GPK_MFPL_PK4MFP_Msk, SYS_GPK_MFPL_PK4MFP_LCM_DEN),

    NUREG_EXPORT(SYS_GPG_MFPH, SYS_GPG_MFPH_PG10MFP_Msk, SYS_GPG_MFPH_PG10MFP_LCM_CLK),
    NUREG_EXPORT(SYS_GPG_MFPH, SYS_GPG_MFPH_PG9MFP_Msk, SYS_GPG_MFPH_PG9MFP_LCM_HSYNC),
    NUREG_EXPORT(SYS_GPG_MFPH, SYS_GPG_MFPH_PG8MFP_Msk, SYS_GPG_MFPH_PG8MFP_LCM_VSYNC),

    /* DISP CLK */
    NUREG_EXPORT(CLK_SYSCLK0, CLK_SYSCLK0_DCUEN_Msk, CLK_SYSCLK0_DCUEN_Msk),

    /* DISP Engine */
    NUREG_EXPORT(DISP_FRAMEBUFFERCONFIG0, DISP_FrameBufferConfig0_UNDERFLOW_Msk, DISP_FrameBufferConfig0_UNDERFLOW_Msk),
    NUREG_EXPORT(DISP_OVERLAYCONFIG0, DISP_OverlayConfig0_UNDERFLOW_Msk, DISP_OverlayConfig0_UNDERFLOW_Msk),

    /* I2C5 */
    NUREG_EXPORT(SYS_GPJ_MFPH, SYS_GPJ_MFPH_PJ12MFP_Msk, SYS_GPJ_MFPH_PJ12MFP_I2C5_SDA),
    NUREG_EXPORT(SYS_GPJ_MFPH, SYS_GPJ_MFPH_PJ13MFP_Msk, SYS_GPJ_MFPH_PJ13MFP_I2C5_SCL),

    /* GPD12, PM12 */
    NUREG_EXPORT(SYS_GPD_MFPH, SYS_GPD_MFPH_PD12MFP_Msk, (0 << SYS_GPD_MFPH_PD12MFP_Pos)),
    NUREG_EXPORT(SYS_GPM_MFPH, SYS_GPM_MFPH_PM12MFP_Msk, (0 << SYS_GPM_MFPH_PM12MFP_Pos)),

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

    /* USB Host */
    NUREG_EXPORT(CLK_SYSCLK0, CLK_SYSCLK0_USBHEN_Msk,   CLK_SYSCLK0_USBHEN_Msk),
    NUREG_EXPORT(CLK_SYSCLK0, CLK_SYSCLK0_HUSBH0EN_Msk, CLK_SYSCLK0_HUSBH0EN_Msk),
    NUREG_EXPORT(CLK_SYSCLK0, CLK_SYSCLK0_HUSBH1EN_Msk, CLK_SYSCLK0_HUSBH1EN_Msk),
    NUREG_EXPORT(SYS_USBPMISCR, SYS_USBPMISCR_PHY0SUSPEND_Msk, SYS_USBPMISCR_PHY0SUSPEND_Msk),
    NUREG_EXPORT(SYS_USBPMISCR, SYS_USBPMISCR_PHY1SUSPEND_Msk, SYS_USBPMISCR_PHY1SUSPEND_Msk),
    NUREG_EXPORT(SYS_GPL_MFPH, SYS_GPL_MFPH_PL12MFP_Msk, SYS_GPL_MFPH_PL12MFP_HSUSBH_PWREN),
    NUREG_EXPORT(SYS_GPL_MFPH, SYS_GPL_MFPH_PL13MFP_Msk, SYS_GPL_MFPH_PL13MFP_HSUSBH_OVC),

    /* SDH0 */
    NUREG_EXPORT(CLK_SYSCLK0, CLK_SYSCLK0_SDH0EN_Msk,   CLK_SYSCLK0_SDH0EN_Msk),
    NUREG_EXPORT(CLK_CLKSEL0, CLK_CLKSEL0_SD0SEL_Msk,   CLK_CLKSEL0_SD0SEL_APLL),
    NUREG_EXPORT(CLK_CLKSEL0, CLK_CLKSEL0_SD0SEL_Msk,   CLK_CLKSEL0_SD0SEL_SYSPLL),

    NUREG_EXPORT(SYS_GPC_MFPL, SYS_GPC_MFPL_PC7MFP_Msk, SYS_GPC_MFPL_PC7MFP_SD0_WP),
    NUREG_EXPORT(SYS_GPC_MFPL, SYS_GPC_MFPL_PC6MFP_Msk, SYS_GPC_MFPL_PC6MFP_SD0_nCD),
    NUREG_EXPORT(SYS_GPC_MFPL, SYS_GPC_MFPL_PC5MFP_Msk, SYS_GPC_MFPL_PC5MFP_SD0_DAT3),
    NUREG_EXPORT(SYS_GPC_MFPL, SYS_GPC_MFPL_PC4MFP_Msk, SYS_GPC_MFPL_PC4MFP_SD0_DAT2),
    NUREG_EXPORT(SYS_GPC_MFPL, SYS_GPC_MFPL_PC3MFP_Msk, SYS_GPC_MFPL_PC3MFP_SD0_DAT1),
    NUREG_EXPORT(SYS_GPC_MFPL, SYS_GPC_MFPL_PC2MFP_Msk, SYS_GPC_MFPL_PC2MFP_SD0_DAT0),
    NUREG_EXPORT(SYS_GPC_MFPL, SYS_GPC_MFPL_PC1MFP_Msk, SYS_GPC_MFPL_PC1MFP_SD0_CLK),
    NUREG_EXPORT(SYS_GPC_MFPL, SYS_GPC_MFPL_PC0MFP_Msk, SYS_GPC_MFPL_PC0MFP_SD0_CMD),

    /* SDH1 */
    NUREG_EXPORT(CLK_SYSCLK0, CLK_SYSCLK0_SDH1EN_Msk,   CLK_SYSCLK0_SDH1EN_Msk),
    NUREG_EXPORT(CLK_CLKSEL0, CLK_CLKSEL0_SD1SEL_Msk,   CLK_CLKSEL0_SD1SEL_APLL),
    NUREG_EXPORT(CLK_CLKSEL0, CLK_CLKSEL0_SD1SEL_Msk,   CLK_CLKSEL0_SD1SEL_SYSPLL),

    NUREG_EXPORT(SYS_GPJ_MFPH, SYS_GPJ_MFPH_PJ11MFP_Msk, SYS_GPJ_MFPH_PJ11MFP_SD1_DAT3),
    NUREG_EXPORT(SYS_GPJ_MFPH, SYS_GPJ_MFPH_PJ10MFP_Msk, SYS_GPJ_MFPH_PJ10MFP_SD1_DAT2),
    NUREG_EXPORT(SYS_GPJ_MFPH, SYS_GPJ_MFPH_PJ9MFP_Msk, SYS_GPJ_MFPH_PJ9MFP_SD1_DAT1),
    NUREG_EXPORT(SYS_GPJ_MFPH, SYS_GPJ_MFPH_PJ8MFP_Msk, SYS_GPJ_MFPH_PJ8MFP_SD1_DAT0),
    NUREG_EXPORT(SYS_GPJ_MFPL, SYS_GPJ_MFPL_PJ7MFP_Msk, SYS_GPJ_MFPL_PJ7MFP_SD1_CLK),
    NUREG_EXPORT(SYS_GPJ_MFPL, SYS_GPJ_MFPL_PJ6MFP_Msk, SYS_GPJ_MFPL_PJ6MFP_SD1_CMD),
    NUREG_EXPORT(SYS_GPJ_MFPL, SYS_GPJ_MFPL_PJ5MFP_Msk, SYS_GPJ_MFPL_PJ5MFP_SD1_nCD),
    NUREG_EXPORT(SYS_GPJ_MFPL, SYS_GPJ_MFPL_PJ4MFP_Msk, SYS_GPJ_MFPL_PJ4MFP_SD1_WP),

    /* UART11 */
    NUREG_EXPORT(SYS_GPL_MFPL, SYS_GPL_MFPL_PL0MFP_Msk, SYS_GPL_MFPL_PL0MFP_UART11_nCTS),
    NUREG_EXPORT(SYS_GPL_MFPL, SYS_GPL_MFPL_PL1MFP_Msk, SYS_GPL_MFPL_PL1MFP_UART11_nRTS),
    NUREG_EXPORT(SYS_GPL_MFPL, SYS_GPL_MFPL_PL2MFP_Msk, SYS_GPL_MFPL_PL2MFP_UART11_RXD),
    NUREG_EXPORT(SYS_GPL_MFPL, SYS_GPL_MFPL_PL3MFP_Msk, SYS_GPL_MFPL_PL3MFP_UART11_TXD),

    NUREG_EXPORT(CLK_CLKSEL3, CLK_CLKSEL3_UART11SEL_Msk, CLK_CLKSEL3_UART11SEL_HXT),
    NUREG_EXPORT(CLK_APBCLK0, CLK_APBCLK0_UART11CKEN_Msk, CLK_APBCLK0_UART11CKEN_Msk),

    /* WDT */
    NUREG_EXPORT(CLK_CLKSEL3, CLK_CLKSEL3_WDT0SEL_Msk, CLK_CLKSEL3_WDT0SEL_PCLK3_DIV4096),

    /* GMAC0 */
    NUREG_EXPORT(SYS_GPE_MFPL, SYS_GPE_MFPL_PE0MFP_Msk, SYS_GPE_MFPL_PE0MFP_RGMII0_MDC),
    NUREG_EXPORT(SYS_GPE_MFPL, SYS_GPE_MFPL_PE1MFP_Msk, SYS_GPE_MFPL_PE1MFP_RGMII0_MDIO),
    NUREG_EXPORT(SYS_GPE_MFPL, SYS_GPE_MFPL_PE2MFP_Msk, SYS_GPE_MFPL_PE2MFP_RGMII0_TXCTL),
    NUREG_EXPORT(SYS_GPE_MFPL, SYS_GPE_MFPL_PE3MFP_Msk, SYS_GPE_MFPL_PE3MFP_RGMII0_TXD0),
    NUREG_EXPORT(SYS_GPE_MFPL, SYS_GPE_MFPL_PE4MFP_Msk, SYS_GPE_MFPL_PE4MFP_RGMII0_TXD1),
    NUREG_EXPORT(SYS_GPE_MFPL, SYS_GPE_MFPL_PE5MFP_Msk, SYS_GPE_MFPL_PE5MFP_RGMII0_RXCLK),
    NUREG_EXPORT(SYS_GPE_MFPL, SYS_GPE_MFPL_PE6MFP_Msk, SYS_GPE_MFPL_PE6MFP_RGMII0_RXCTL),
    NUREG_EXPORT(SYS_GPE_MFPL, SYS_GPE_MFPL_PE7MFP_Msk, SYS_GPE_MFPL_PE7MFP_RGMII0_RXD0),
    NUREG_EXPORT(SYS_GPE_MFPH, SYS_GPE_MFPH_PE8MFP_Msk, SYS_GPE_MFPH_PE8MFP_RGMII0_RXD1),
    NUREG_EXPORT(SYS_GPE_MFPH, SYS_GPE_MFPH_PE9MFP_Msk, SYS_GPE_MFPH_PE9MFP_RGMII0_RXD2),
    NUREG_EXPORT(SYS_GPE_MFPH, SYS_GPE_MFPH_PE10MFP_Msk, SYS_GPE_MFPH_PE10MFP_RGMII0_RXD3),
    NUREG_EXPORT(SYS_GPE_MFPH, SYS_GPE_MFPH_PE11MFP_Msk, SYS_GPE_MFPH_PE11MFP_RGMII0_TXCLK),
    NUREG_EXPORT(SYS_GPE_MFPH, SYS_GPE_MFPH_PE12MFP_Msk, SYS_GPE_MFPH_PE12MFP_RGMII0_TXD2),
    NUREG_EXPORT(SYS_GPE_MFPH, SYS_GPE_MFPH_PE13MFP_Msk, SYS_GPE_MFPH_PE13MFP_RGMII0_TXD3),
    NUREG_EXPORT(SYS_GPE_MFPH, SYS_GPE_MFPH_PE13MFP_Msk, SYS_GPE_MFPH_PE13MFP_RGMII0_TXD3),
    NUREG_EXPORT(CLK_SYSCLK0,  CLK_SYSCLK0_GMAC0EN_Msk, CLK_SYSCLK0_GMAC0EN_Msk),
    NUREG_EXPORT(CLK_SYSCLK1,  CLK_SYSCLK1_GPECKEN_Msk, CLK_SYSCLK1_GPECKEN_Msk),
    NUREG_EXPORT(CLK_CLKDIV0,  CLK_CLKDIV0_EMAC0DIV_Msk, 0 << CLK_CLKDIV0_EMAC0DIV_Pos), //RGMII

    /* GMAC1 */
    NUREG_EXPORT(SYS_GPF_MFPL, SYS_GPF_MFPL_PF0MFP_Msk, SYS_GPF_MFPL_PF0MFP_RGMII1_MDC),
    NUREG_EXPORT(SYS_GPF_MFPL, SYS_GPF_MFPL_PF1MFP_Msk, SYS_GPF_MFPL_PF1MFP_RGMII1_MDIO),
    NUREG_EXPORT(SYS_GPF_MFPL, SYS_GPF_MFPL_PF2MFP_Msk, SYS_GPF_MFPL_PF2MFP_RGMII1_TXCTL),
    NUREG_EXPORT(SYS_GPF_MFPL, SYS_GPF_MFPL_PF3MFP_Msk, SYS_GPF_MFPL_PF3MFP_RGMII1_TXD0),
    NUREG_EXPORT(SYS_GPF_MFPL, SYS_GPF_MFPL_PF4MFP_Msk, SYS_GPF_MFPL_PF4MFP_RGMII1_TXD1),
    NUREG_EXPORT(SYS_GPF_MFPL, SYS_GPF_MFPL_PF5MFP_Msk, SYS_GPF_MFPL_PF5MFP_RGMII1_RXCLK),
    NUREG_EXPORT(SYS_GPF_MFPL, SYS_GPF_MFPL_PF6MFP_Msk, SYS_GPF_MFPL_PF6MFP_RGMII1_RXCTL),
    NUREG_EXPORT(SYS_GPF_MFPL, SYS_GPF_MFPL_PF7MFP_Msk, SYS_GPF_MFPL_PF7MFP_RGMII1_RXD0),
    NUREG_EXPORT(SYS_GPF_MFPH, SYS_GPF_MFPH_PF8MFP_Msk, SYS_GPF_MFPH_PF8MFP_RGMII1_RXD1),
    NUREG_EXPORT(SYS_GPF_MFPH, SYS_GPF_MFPH_PF9MFP_Msk, SYS_GPF_MFPH_PF9MFP_RGMII1_RXD2),
    NUREG_EXPORT(SYS_GPF_MFPH, SYS_GPF_MFPH_PF10MFP_Msk, SYS_GPF_MFPH_PF10MFP_RGMII1_RXD3),
    NUREG_EXPORT(SYS_GPF_MFPH, SYS_GPF_MFPH_PF11MFP_Msk, SYS_GPF_MFPH_PF11MFP_RGMII1_TXCLK),
    NUREG_EXPORT(SYS_GPF_MFPH, SYS_GPF_MFPH_PF12MFP_Msk, SYS_GPF_MFPH_PF12MFP_RGMII1_TXD2),
    NUREG_EXPORT(SYS_GPF_MFPH, SYS_GPF_MFPH_PF13MFP_Msk, SYS_GPF_MFPH_PF13MFP_RGMII1_TXD3),
    NUREG_EXPORT(CLK_SYSCLK0,  CLK_SYSCLK0_GMAC1EN_Msk, CLK_SYSCLK0_GMAC1EN_Msk),
    NUREG_EXPORT(CLK_SYSCLK1,  CLK_SYSCLK1_GPFCKEN_Msk, CLK_SYSCLK1_GPFCKEN_Msk),
    NUREG_EXPORT(CLK_CLKDIV0,  CLK_CLKDIV0_EMAC1DIV_Msk, 0 << CLK_CLKDIV0_EMAC1DIV_Pos), //RGMII

    /* CANFD0 CLK */
    NUREG_EXPORT(CLK_SYSCLK0,  CLK_SYSCLK0_CANFD0CKEN_Msk, CLK_SYSCLK0_CANFD0CKEN_Msk),
    NUREG_EXPORT(CLK_CLKSEL4,  CLK_CLKSEL4_CANFD0SEL_Msk, CLK_CLKSEL4_CANFD0SEL_APLL),
    NUREG_EXPORT(CLK_CLKDIV0,  CLK_CLKDIV0_CANFD0DIV_Msk, CLK_CLKDIV0_CANFD0(1)),

    {0}
};

void nu_check_register(void)
{
    nu_sys_check_register(&s_NuReg_arr[0]);
}
MSH_CMD_EXPORT(nu_check_register, Check registers);
