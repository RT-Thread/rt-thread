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
#include "NuMicro.h"
#include "drv_common.h"

#if defined(BOARD_USING_NUFUN)

#if defined(BOARD_USING_QSPI_FLASH)
#include "qspinor.h"

static int rt_hw_spiflash_init(void)
{
    /* Here, we use Dual I/O to drive the SPI flash by default. */
    /* If you want to use Quad I/O, you can modify to 4 from 2 and crossover D2/D3 pin of SPI flash. */
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
#endif /* BOARD_USING_QSPI_FLASH */

#if defined(BOARD_USING_NUFUN_ADC_TOUCH) && defined(NU_PKG_USING_ADC_TOUCH_SW)

#include "adc_touch.h"
#include "touch_sw.h"

S_CALIBRATION_MATRIX g_sCalMat = { 36, 6227, -2817292, 4936, -37, -1969986, 65536 };

static void tp_switch_to_analog(rt_base_t pin)
{
    GPIO_T *port = (GPIO_T *)(GPIOA_BASE + (0x40) * NU_GET_PORT(pin));

    nu_pin_func(pin, (1 << NU_MFP_POS(NU_GET_PINS(pin))));

    /* Disable the digital input path to avoid the leakage current. */
    /* Disable digital path on these ADC pin */
    GPIO_DISABLE_DIGITAL_PATH(port, NU_GET_PIN_MASK(NU_GET_PINS(pin)));
}

static void tp_switch_to_digital(rt_base_t pin)
{
    GPIO_T *port = (GPIO_T *)(GPIOA_BASE + (0x40) * NU_GET_PORT(pin));

    nu_pin_func(pin, 0);

    /* Enable digital path on these ADC pins */
    GPIO_ENABLE_DIGITAL_PATH(port, NU_GET_PIN_MASK(NU_GET_PINS(pin)));
}

static S_TOUCH_SW sADCTP =
{
    .adc_name    = "eadc0",
    .i32ADCChnYU = 4,
    .i32ADCChnXR = 3,
    .pin =
    {
        NU_GET_PININDEX(NU_PB, 5), // XL
        NU_GET_PININDEX(NU_PB, 4), // YU
        NU_GET_PININDEX(NU_PB, 3), // XR
        NU_GET_PININDEX(NU_PB, 2), // YD
    },
    .switch_to_analog  = tp_switch_to_analog,
    .switch_to_digital = tp_switch_to_digital,
};

#endif /* defined(BOARD_USING_NUFUN_ADC_TOUCH) && defined(NU_PKG_USING_ADC_TOUCH_SW) */

#if defined(BOARD_USING_LCD_ILI9341) && defined(NU_PKG_USING_ILI9341_SPI)

#include <lcd_ili9341.h>
#if defined(PKG_USING_GUIENGINE)
    #include <rtgui/driver.h>
#endif

int rt_hw_ili9341_port(void)
{
    if (rt_hw_lcd_ili9341_spi_init("spi1", (void *)RT_NULL) != RT_EOK)
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

#if defined(BOARD_USING_NUFUN_ADC_TOUCH) && defined(NU_PKG_USING_ADC_TOUCH_SW)
    rt_err_t nu_adc_touch_sw_register(S_TOUCH_SW * psTouchSW);
    nu_adc_touch_sw_register(&sADCTP);
#endif

    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_ili9341_port);
#endif /* defined(BOARD_USING_LCD_ILI9341) && defined(NU_PKG_USING_ILI9341_SPI) */

#if defined(BOARD_USING_AUDIO_CODEC) && defined(NU_PKG_USING_NAU8822)
#include "acodec_nau8822.h"
S_NU_NAU8822_CONFIG sCodecConfig =
{
    .i2c_bus_name = "i2c1",
    .i2s_bus_name = "sound0",
    .pin_phonejack_en = NU_GET_PININDEX(NU_PD, 11),
    .pin_phonejack_det = NU_GET_PININDEX(NU_PD, 10),
};

int rt_hw_nau8822_port(void)
{
    if (nu_hw_nau8822_init(&sCodecConfig) != RT_EOK)
        return -1;

    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_nau8822_port);
#endif /* BOARD_USING_AUDIO_CODEC */

#if defined(BOARD_USING_NUFUN_I2C_TEMPERATURE_SENSOR)

#include "sensor_tmp112.h"

int rt_hw_tmp112_port(void)
{
    struct rt_sensor_config cfg;

    cfg.intf.dev_name = "i2c2";
    cfg.irq_pin.pin = RT_PIN_NONE;

    return rt_hw_tmp112_init("tmp112", &cfg);
}
INIT_ENV_EXPORT(rt_hw_tmp112_port);
#endif /* BOARD_USING_NUFUN_I2C_TEMPERATURE_SENSOR */

#if defined(BOARD_USING_NUFUN_I2C_3AXIS_SENSOR) && defined(NU_PKG_USING_LIS3DH)

#include "st_lis3dh_sensor_v1.h"

int rt_hw_lis3dh_port(void)
{
    struct rt_sensor_config cfg;

    cfg.intf.dev_name = "i2c2";
    cfg.irq_pin.pin = RT_PIN_NONE;

    return rt_hw_lis3dh_init("lis3dh", &cfg);
}
INIT_ENV_EXPORT(rt_hw_lis3dh_port);
#endif /* BOARD_USING_NUFUN_I2C_TEMPERATURE_SENSOR */

#if defined(BOARD_USING_NUFUN_I3C_BAROMETER_SENSOR) && defined(NU_PKG_USING_LPS22HH)

#include "st_lps22hh_sensor_v1.h"

int rt_hw_lps22hh_port(void)
{
    struct rt_sensor_config cfg;

    cfg.intf.dev_name = "i3c0";
    cfg.irq_pin.pin = RT_PIN_NONE;

    return rt_hw_lps22hh_init("lps22hh", &cfg);
}
INIT_ENV_EXPORT(rt_hw_lps22hh_port);
#endif /* BOARD_USING_NUFUN_I2C_TEMPERATURE_SENSOR */

#endif /* defined(BOARD_USING_NUFUN) */
