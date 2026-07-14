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

#if defined(BOARD_USING_NUTFT)

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

#if defined(BOARD_USING_NUTFT_ADC_TOUCH) && defined(NU_PKG_USING_ADC_TOUCH_SW)

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
    .i32ADCChnYU = 14,
    .i32ADCChnXR = 9,
    .pin =
    {
        NU_GET_PININDEX(NU_PB, 15), // XL
        NU_GET_PININDEX(NU_PB, 14), // YU
        NU_GET_PININDEX(NU_PB, 9), // XR
        NU_GET_PININDEX(NU_PB, 8), // YD
    },
    .switch_to_analog  = tp_switch_to_analog,
    .switch_to_digital = tp_switch_to_digital,
};

#endif /* defined(BOARD_USING_NUTFT_ADC_TOUCH) && defined(NU_PKG_USING_ADC_TOUCH_SW) */

#if defined(BOARD_USING_LCD_ILI9341) && defined(NU_PKG_USING_ILI9341_SPI)

#include <lcd_ili9341.h>
#if defined(PKG_USING_GUIENGINE)
    #include <rtgui/driver.h>
#endif

int rt_hw_ili9341_port(void)
{
    if (rt_hw_lcd_ili9341_spi_init("spi2", (void *)RT_NULL) != RT_EOK)
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

#if defined(BOARD_USING_NUTFT_ADC_TOUCH) && defined(NU_PKG_USING_ADC_TOUCH_SW)
    nu_adc_touch_sw_register(&sADCTP);
#endif

    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_ili9341_port);
#endif /* defined(BOARD_USING_LCD_ILI9341) && defined(NU_PKG_USING_ILI9341_SPI) */

#endif /* defined(BOARD_USING_NUTFT) */
