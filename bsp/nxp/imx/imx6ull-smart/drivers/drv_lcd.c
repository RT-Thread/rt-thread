/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-11     Lyons        first version
 * 2021-06-24     RiceChen     refactor
 * 2021-07-28     songchao     add cmd
 */

#include <rthw.h>
#include <rtdevice.h>

#ifdef BSP_USING_LCD

#define LOG_TAG              "drv.lcd"
#include <drv_log.h>

#include "fsl_iomuxc.h"
#include "drv_lcd.h"
#include <lwp_user_mm.h>

static struct imx6ull_lcd_config _lcd_config = LCD_BUS_CONFIG;
static struct imx6ull_lcd_bus _lcd_obj;

static rt_err_t imx6ull_elcd_init(rt_device_t device)
{
    struct imx6ull_lcd_bus *elcd_dev = RT_NULL;
    clock_video_pll_config_t pll_config;
    elcdif_rgb_mode_config_t lcd_config;

    RT_ASSERT(device != RT_NULL);

    elcd_dev = (struct imx6ull_lcd_bus *)device;
    ELCDIF_Reset(elcd_dev->config->ELCDIF);
    pll_config.loopDivider = 32;
    pll_config.postDivider = LCD_PLL_DIV;

    pll_config.numerator   = 0;
    pll_config.denominator = 0;

    CLOCK_InitVideoPll(&pll_config);

    lcd_config.hfp           = LCD_HFP;
    lcd_config.vfp           = LCD_VFP;
    lcd_config.hbp           = LCD_HBP;
    lcd_config.vbp           = LCD_VBP;
    lcd_config.hsw           = LCD_HSW;
    lcd_config.vsw           = LCD_VSW;

    lcd_config.polarityFlags = kELCDIF_DataEnableActiveHigh  |
                               kELCDIF_VsyncActiveLow      |
                               kELCDIF_HsyncActiveLow      |
                               kELCDIF_DriveDataOnRisingClkEdge;

    switch(elcd_dev->info.pixel_format)
    {
        case RTGRAPHIC_PIXEL_FORMAT_RGB888:
            lcd_config.pixelFormat = kELCDIF_PixelFormatRGB888;
            break;
        case RTGRAPHIC_PIXEL_FORMAT_RGB565:
            lcd_config.pixelFormat = kELCDIF_PixelFormatRGB565;
            break;
        default:
            LOG_E("not support this pixel_format %d\n",elcd_dev->info.pixel_format);
            return RT_ERROR;
    }

    lcd_config.panelWidth    = elcd_dev->info.width;
    lcd_config.panelHeight   = elcd_dev->info.height;
    lcd_config.bufferAddr    = (uint32_t)elcd_dev->fb_phy;
    lcd_config.dataBus       = kELCDIF_DataBus24Bit;

    ELCDIF_RgbModeInit(elcd_dev->config->ELCDIF, &lcd_config);
    ELCDIF_RgbModeStart(elcd_dev->config->ELCDIF);

    return RT_EOK;
}
static rt_err_t imx6ull_elcd_control(rt_device_t device, int cmd, void *args)
{
    struct imx6ull_lcd_bus *elcd_dev = RT_NULL;
    int mem_size = 0;

    RT_ASSERT(device != RT_NULL);

    elcd_dev = (struct imx6ull_lcd_bus *)device;
    switch(cmd)
    {
        case RTGRAPHIC_CTRL_RECT_UPDATE:
        {
            mem_size = elcd_dev->info.width * elcd_dev->info.height * elcd_dev->info.bits_per_pixel / 8;
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)(_lcd_obj.info.framebuffer), mem_size);
            break;
        }
        case RTGRAPHIC_CTRL_POWERON:
        {
            rt_pin_write(IMX6ULL_LCD_BL_PIN, PIN_HIGH);
            break;
        }
        case RTGRAPHIC_CTRL_POWEROFF:
        {
            rt_pin_write(IMX6ULL_LCD_BL_PIN, PIN_LOW);
            break;
        }
        case RTGRAPHIC_CTRL_GET_INFO:
        {
            struct lcd_info *info = (struct lcd_info *)args;
            RT_ASSERT(info != RT_NULL);
            rt_memcpy(&info->graphic, &elcd_dev->info, sizeof(struct rt_device_graphic_info));
            info->screen.shamem_len = elcd_dev->info.width * elcd_dev->info.height * elcd_dev->info.bits_per_pixel / 8;
            info->screen.shamem_start = (rt_uint32_t)lwp_map_user_phy(lwp_self(), RT_NULL,
                                                                        elcd_dev->fb_phy,
                                                                        info->screen.shamem_len, 1);
            break;
        }
        case RTGRAPHIC_CTRL_SET_MODE:
        {
            break;
        }
        case FBIOGET_FSCREENINFO:
        {
            struct fb_fix_screeninfo *info = (struct fb_fix_screeninfo *)args;
            rt_memcpy(info->id, elcd_dev->config->name, (strlen(elcd_dev->config->name)+1));
            info->smem_len = elcd_dev->info.width * elcd_dev->info.height * elcd_dev->info.bits_per_pixel / 8;
            info->smem_start = (rt_uint32_t)lwp_map_user_phy(lwp_self(), RT_NULL,
                                                                        elcd_dev->fb_phy,
                                                                        info->smem_len, 1);
            info->line_length = elcd_dev->info.width * 2;
            break;
        }
        case FBIOGET_VSCREENINFO:
        {
            struct fb_var_screeninfo *info = (struct fb_var_screeninfo *)args;
            info->bits_per_pixel = elcd_dev->info.bits_per_pixel;
            info->xres = elcd_dev->info.width;
            info->yres = elcd_dev->info.height;
            break;
        }

    }
    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops elcd_ops =
{
    imx6ull_elcd_init,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    imx6ull_elcd_control,
};
#endif

int rt_hw_elcd_init(void)
{
    rt_err_t ret = 0;

    _lcd_config.ELCDIF       = (LCDIF_Type *)imx6ull_get_periph_vaddr((rt_uint32_t)(_lcd_config.ELCDIF));
    _lcd_config.lcd_mux_base = (rt_uint32_t)imx6ull_get_periph_vaddr((rt_uint32_t)(_lcd_config.lcd_mux_base));
    _lcd_config.lcd_cfg_base = (rt_uint32_t)imx6ull_get_periph_vaddr((rt_uint32_t)(_lcd_config.lcd_cfg_base));

    for(int i = 0; i < LCD_GPIO_MAX; i++)
    {
        IOMUXC_SetPinMux((_lcd_config.lcd_mux_base + i * 4),
                            0x0U, 0x0U, 0x0U, (_lcd_config.lcd_cfg_base + i * 4), 0);
        IOMUXC_SetPinConfig((_lcd_config.lcd_mux_base + i * 4),
                            0x0U, 0x0U, 0x0U, (_lcd_config.lcd_cfg_base + i * 4), 0xB9);
    }

    CLOCK_EnableClock(_lcd_config.apd_clk_name);
    CLOCK_EnableClock(_lcd_config.pix_clk_name);

    _lcd_obj.config = &_lcd_config;

    _lcd_obj.fb_virt = rt_pages_alloc(rt_page_bits(LCD_BUF_SIZE));
    _lcd_obj.fb_phy = _lcd_obj.fb_virt + PV_OFFSET;

    LOG_D("fb address => 0x%08x\n", _lcd_obj.fb_phy);
    if(_lcd_obj.fb_phy == RT_NULL)
    {
        LOG_E("initialize frame buffer failed!\n");
        return -RT_ERROR;
    }

    _lcd_obj.info.width          = LCD_WIDTH;
    _lcd_obj.info.height         = LCD_HEIGHT;
    _lcd_obj.info.pixel_format   = RTGRAPHIC_PIXEL_FORMAT_RGB888;
    _lcd_obj.info.bits_per_pixel = LCD_BITS_PER_PIXEL;
    _lcd_obj.info.framebuffer    = (void *)_lcd_obj.fb_virt;

    _lcd_obj.parent.type = RT_Device_Class_Graphic;

#ifdef RT_USING_DEVICE_OPS
    _lcd_obj.parent.ops         = &elcd_ops;
#else
    _lcd_obj.parent.init    = imx6ull_elcd_init;
    _lcd_obj.parent.open    = RT_NULL;
    _lcd_obj.parent.close   = RT_NULL;
    _lcd_obj.parent.read    = RT_NULL;
    _lcd_obj.parent.write   = RT_NULL;
    _lcd_obj.parent.control = imx6ull_elcd_control;
#endif

    _lcd_obj.parent.user_data = (void *)&_lcd_obj.info;

    ret = rt_device_register(&_lcd_obj.parent, _lcd_obj.config->name, RT_DEVICE_FLAG_RDWR);

    /* LCD_BL */
    rt_pin_mode(IMX6ULL_LCD_BL_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(IMX6ULL_LCD_BL_PIN, PIN_HIGH);

    rt_memset((rt_uint8_t *)_lcd_obj.fb_virt, 0xff, LCD_BUF_SIZE);

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_elcd_init);

#endif

