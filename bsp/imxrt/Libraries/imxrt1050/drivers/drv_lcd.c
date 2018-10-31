/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-10-30     Tanek        the first version
 * 2018-04-05     Liu2guang    export LCD config parameters.
 */

#include "drv_lcd.h"

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "fsl_elcdif.h"

#if !defined(LCD_WIDTH) || !defined(LCD_HEIGHT)
#error "Please config lcd pixel parameters."
#endif

#if !defined(LCD_HFP) || !defined(LCD_HBP) || !defined(LCD_HSW) || \
    !defined(LCD_VFP) || !defined(LCD_VBP) || !defined(LCD_VSW)
#error "Please config lcd timing parameters."
#endif

#if !defined(LCD_BL_PIN) || !defined(LCD_RST_PIN)
#error "Please config lcd backlight or reset pin."
#endif

struct rt1050_lcd
{
    struct rt_device device;
    struct rt_device_graphic_info info;
};

static struct rt1050_lcd lcd;

static volatile int fb_index = 0;
static volatile rt_bool_t fb_modified  = RT_TRUE;

ALIGN(64) static uint16_t frame_buffer0[LCD_HEIGHT][LCD_WIDTH] SECTION("NonCacheable");
ALIGN(64) static uint16_t frame_buffer1[LCD_HEIGHT][LCD_WIDTH] SECTION("NonCacheable");

static rt_err_t rt1050_lcd_init(rt_device_t device)
{
    RT_ASSERT(device != RT_NULL);

    memset(frame_buffer0, 0x00, sizeof(frame_buffer0));
    memset(frame_buffer1, 0x00, sizeof(frame_buffer1));

    /* DeInit Video PLL. */
    CLOCK_DeinitVideoPll();

    /*
     * Initialize the Video PLL.
     * Video PLL output clock is OSC24M * (loopDivider + (denominator / numerator)) / postDivider = 93MHz.
     */
    clock_video_pll_config_t config =
    {
        .loopDivider = 31, .postDivider = 8, .numerator = 0, .denominator = 1,
    };

    CLOCK_InitVideoPll(&config);

    /*
     * 000 derive clock from PLL2
     * 001 derive clock from PLL3 PFD3
     * 010 derive clock from PLL5
     * 011 derive clock from PLL2 PFD0
     * 100 derive clock from PLL2 PFD1
     * 101 derive clock from PLL3 PFD1
     */
    CLOCK_SetMux(kCLOCK_LcdifPreMux, 2);

    CLOCK_SetDiv(kCLOCK_LcdifPreDiv, 4);

    CLOCK_SetDiv(kCLOCK_LcdifDiv, 1);

    /* GPIO */
    CLOCK_EnableClock(kCLOCK_Iomuxc);

    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_04_LCD_DATA00, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_04_LCD_DATA00, 0x01B0B0U); /* LCD_B3 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_05_LCD_DATA01, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_05_LCD_DATA01, 0x01B0B0U); /* LCD_B4 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_06_LCD_DATA02, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_06_LCD_DATA02, 0x01B0B0U); /* LCD_B5 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_07_LCD_DATA03, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_07_LCD_DATA03, 0x01B0B0U); /* LCD_B6 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_08_LCD_DATA04, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_08_LCD_DATA04, 0x01B0B0U); /* LCD_B7 */

    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_09_LCD_DATA05, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_09_LCD_DATA05, 0x01B0B0U); /* LCD_G2 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_10_LCD_DATA06, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_10_LCD_DATA06, 0x01B0B0U); /* LCD_G3 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_11_LCD_DATA07, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_11_LCD_DATA07, 0x01B0B0U); /* LCD_G4 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_12_LCD_DATA08, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_12_LCD_DATA08, 0x01B0B0U); /* LCD_G5 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_13_LCD_DATA09, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_13_LCD_DATA09, 0x01B0B0U); /* LCD_G6 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_14_LCD_DATA10, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_14_LCD_DATA10, 0x01B0B0U); /* LCD_G7 */

    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_15_LCD_DATA11, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_15_LCD_DATA11, 0x01B0B0U); /* LCD_R3 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_00_LCD_DATA12, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_00_LCD_DATA12, 0x01B0B0U); /* LCD_R4 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_01_LCD_DATA13, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_01_LCD_DATA13, 0x01B0B0U); /* LCD_R5 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_02_LCD_DATA14, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_02_LCD_DATA14, 0x01B0B0U); /* LCD_R6 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_03_LCD_DATA15, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_03_LCD_DATA15, 0x01B0B0U); /* LCD_R7 */

    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_00_LCD_CLK,    0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_00_LCD_CLK,    0x01B0B0u); /* LCD_CLK */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_02_LCD_HSYNC,  0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_02_LCD_HSYNC,  0x01B0B0u); /* LCD_HSYNC */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_03_LCD_VSYNC,  0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_03_LCD_VSYNC,  0x01B0B0u); /* LCD_VSYNC */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_01_LCD_ENABLE, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_01_LCD_ENABLE, 0x01B0B0u); /* LCD_ENABLE */

    rt_pin_mode(LCD_RST_PIN, PIN_MODE_OUTPUT); /* LCD_RESET */
    rt_pin_write(LCD_RST_PIN, PIN_LOW);
    rt_thread_delay(RT_TICK_PER_SECOND / 100);
    rt_pin_write(LCD_RST_PIN, PIN_HIGH);

    rt_pin_mode(LCD_BL_PIN, PIN_MODE_OUTPUT);   /* LCD_BL */
    rt_pin_write(LCD_BL_PIN, PIN_HIGH);

    /* LCD */
    elcdif_rgb_mode_config_t lcd_config;

    lcd_config.hfp           = LCD_HFP;
    lcd_config.vfp           = LCD_VFP;
    lcd_config.hbp           = LCD_HBP;
    lcd_config.vbp           = LCD_VBP;
    lcd_config.hsw           = LCD_HSW;
    lcd_config.vsw           = LCD_VSW;

    lcd_config.polarityFlags = kELCDIF_DataEnableActiveHigh |
                               kELCDIF_VsyncActiveHigh      |
                               kELCDIF_HsyncActiveLow       |
                               kELCDIF_DriveDataOnRisingClkEdge;

    lcd_config.panelWidth    = LCD_WIDTH;
    lcd_config.panelHeight   = LCD_HEIGHT;
    lcd_config.pixelFormat   = kELCDIF_PixelFormatRGB565;
    lcd_config.dataBus       = kELCDIF_DataBus16Bit;
    lcd_config.bufferAddr    = (uint32_t)frame_buffer0;

    ELCDIF_RgbModeInit(LCDIF, &lcd_config);
    ELCDIF_RgbModeStart(LCDIF);

    /* LCD DEVICE */
    lcd.info.width          = LCD_WIDTH;
    lcd.info.height         = LCD_HEIGHT;
    lcd.info.pixel_format   = RTGRAPHIC_PIXEL_FORMAT_RGB565;
    lcd.info.bits_per_pixel = 16;
    lcd.info.framebuffer    = (void *)rt_malloc_align(LCD_WIDTH * LCD_HEIGHT * 2, 32);

    return RT_EOK;
}

void LCDIF_IRQHandler(void)
{
    uint32_t intStatus;

    intStatus = ELCDIF_GetInterruptStatus(LCDIF);

    ELCDIF_ClearInterruptStatus(LCDIF, intStatus);
    if (intStatus & kELCDIF_CurFrameDone)
    {
        fb_modified = RT_TRUE;
    }
}

static rt_err_t rt1050_lcd_control(rt_device_t device, int cmd, void *args)
{
    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
    {
        uint8_t  *ptr;

        if (fb_index == 0)
        {
            ptr = (uint8_t *)&frame_buffer1[0];
        }
        else
        {
            ptr = (uint8_t *)&frame_buffer0[0];
        }

        while(LCDIF->CUR_BUF != LCDIF->NEXT_BUF);

        memcpy(ptr, lcd.info.framebuffer, LCD_WIDTH * LCD_HEIGHT * 2);

        if (fb_index == 0)
        {
            /* use fb1 */
            ELCDIF_SetNextBufferAddr(LCDIF, (uint32_t)&frame_buffer1[0]);
            fb_index = 1;
        }
        else
        {
            /* use fb0 */
            ELCDIF_SetNextBufferAddr(LCDIF, (uint32_t)&frame_buffer0[0]);
            fb_index = 0;
        }
    }
    break;

    case RTGRAPHIC_CTRL_POWERON:
        rt_pin_write(LCD_BL_PIN, PIN_HIGH);
        break;

    case RTGRAPHIC_CTRL_POWEROFF:
        rt_pin_write(LCD_BL_PIN, PIN_LOW);
        break;

    case RTGRAPHIC_CTRL_GET_INFO:
        memcpy(args, &lcd.info, sizeof(lcd.info));
        break;

    case RTGRAPHIC_CTRL_SET_MODE:
        break;
    }

    return RT_EOK;
}

int rt_hw_lcd_init(void)
{
    rt_err_t ret;

    lcd.device.type    = RT_Device_Class_Graphic;
    lcd.device.init    = rt1050_lcd_init;
    lcd.device.open    = RT_NULL;
    lcd.device.close   = RT_NULL;
    lcd.device.read    = RT_NULL;
    lcd.device.write   = RT_NULL;
    lcd.device.control = rt1050_lcd_control;

    lcd.device.user_data = (void *)&lcd.info;

    ret = rt_device_register(&lcd.device, "lcd", RT_DEVICE_FLAG_RDWR);

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_lcd_init);
