#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <hal_clk.h>
#include <hal_gpio.h>
#include "disp_sys_intf.h"
#include "disp_board_config.h"

#include <rtthread.h>

#include "lcd_cfg.h"

struct property_t *g_lcd0_config = NULL;
static struct lcd_cfg_panel_info _panel_info = DEFAULT_LCD_CONFIG;

struct property_t g_lcd0_config_rgb[] = {
    {
        .name = "lcd_used",
        .type = PROPERTY_INTGER,
        .v.value = 1,
    },
    {
        .name = "lcd_driver_name",
        .type = PROPERTY_STRING,
        .v.str = "default_lcd",
    },
    {
        .name = "lcd_if",
        .type = PROPERTY_INTGER,
        .v.value = 0, /* LCD_IF_HV */
    },
    {
        .name = "lcd_hv_if",
        .type = PROPERTY_INTGER,
        .v.value = 0, /* LCD_HV_IF_PRGB_1CYC */
    },
    {
        .name = "lcd_x",
        .type = PROPERTY_INTGER,
        .v.value = 480, //
    },
    {
        .name = "lcd_y",
        .type = PROPERTY_INTGER,
        .v.value = 272,
    },
    {
        .name = "lcd_width",
        .type = PROPERTY_INTGER,
        .v.value = 80,
    },
    {
        .name = "lcd_height",
        .type = PROPERTY_INTGER,
        .v.value = 47,
    },
    {
        .name = "lcd_dclk_freq",
        .type = PROPERTY_INTGER,
        .v.value = 10,
    },
    /* lcd_ht = lcd_x + lcd_hspw + lcd_hbp + lcd_hfp */
    {
        .name = "lcd_ht",
        .type = PROPERTY_INTGER,
        .v.value = 592,
    },
    {
        .name = "lcd_hbp",
        .type = PROPERTY_INTGER,
        .v.value = 56,
    },
    {
        .name = "lcd_hspw",
        .type = PROPERTY_INTGER,
        .v.value = 40,
    },
    /* lcd_vt = lcd_y + lcd_vspw + lcd_vbp + lcd_vfp */
    {
        .name = "lcd_vt",
        .type = PROPERTY_INTGER,
        .v.value = 286,
    },
    {
        .name = "lcd_vspw",
        .type = PROPERTY_INTGER,
        .v.value = 5,
    },
    {
        .name = "lcd_vbp",
        .type = PROPERTY_INTGER,
        .v.value = 6,
    },
    {
        .name = "lcd_frm",
        .type = PROPERTY_INTGER,
        .v.value = 1,
    },
    {
        .name = "lcd_io_phase",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "lcd_gamma_en",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "lcd_bright_curve_en",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "lcd_cmap_en",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "deu_mode",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "lcdgamma4iep",
        .type = PROPERTY_INTGER,
        .v.value = 22,
    },
    {
        .name = "smart_color",
        .type = PROPERTY_INTGER,
        .v.value = 90,
    },

    // backlight enable
    {
        .name = "lcd_gpio_1",
        .type = PROPERTY_GPIO,
        .v.gpio_list = {
            .gpio = GPIOG(13),
            .mul_sel = GPIO_DIRECTION_OUTPUT,
            .pull = 0,
            .drv_level = 3,
            .data = 1,
        },
    },
    {
        .name = "lcd_backlight",
        .type = PROPERTY_INTGER,
        .v.value = 50,
    },
    {
        .name = "lcd_pwm_used",
        .type = PROPERTY_INTGER,
        .v.value = 1,
    },
    {
        .name = "lcd_pwm_ch",
        .type = PROPERTY_INTGER,
        .v.value = 1,
    },
    {
        .name = "lcd_pwm_freq",
        .type = PROPERTY_INTGER,
        .v.value = 1000,
    },
    {
        .name = "lcd_pwm_pol",
        .type = PROPERTY_INTGER,
        .v.value = 1,
    },
    {
        .name = "lcd_pwm_max_limit",
        .type = PROPERTY_INTGER,
        .v.value = 255,
    },
    /* POWER-vcc */
    {
        .name = "lcd_gpio_0",
        .type = PROPERTY_GPIO,
        .v.gpio_list = {
            .gpio = GPIOG(15),
            .mul_sel = GPIO_DIRECTION_OUTPUT,
            .pull = 0,
            .drv_level = 3,
            .data = 1,
        },
    },
    // gpio
    {
        .name = "LCD0_D2",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(0),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D3",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(1),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D4",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(2),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D5",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(3),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D6",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(4),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D7",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(5),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D10",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(6),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D11",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(7),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D12",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(8),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D13",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(9),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D14",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(10),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D15",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(11),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D18",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(12),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D19",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(13),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D20",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(14),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D21",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(15),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D22",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(16),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D23",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(17),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_CLK",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(18),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_DE",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(19),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_HSYNC",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(20),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_VSYNC",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(21),
            .mul_sel = 2,
            .pull = 0,
            .drv_level = 3,
        },
    }};

struct property_t g_lcd0_config_mipi[] = {
    {
        .name = "lcd_used",
        .type = PROPERTY_INTGER,
        .v.value = 1,
    },
    {
        .name = "lcd_driver_name",
        .type = PROPERTY_STRING,
        .v.str = "tft08006",
    },
    {
        .name = "lcd_backlight",
        .type = PROPERTY_INTGER,
        .v.value = 50,
    },
    {
        .name = "lcd_if",
        .type = PROPERTY_INTGER,
        .v.value = LCD_IF_DSI,
    },
    {
        .name = "lcd_x",
        .type = PROPERTY_INTGER,
        .v.value = 540,
    },
    {
        .name = "lcd_y",
        .type = PROPERTY_INTGER,
        .v.value = 960, // 1280
    },
    {
        .name = "lcd_width",
        .type = PROPERTY_INTGER,
        .v.value = 52,
    },
    {
        .name = "lcd_height",
        .type = PROPERTY_INTGER,
        .v.value = 52,
    },
    {
        .name = "lcd_dclk_freq",
        .type = PROPERTY_INTGER,
        .v.value = 43,
    },
    {
        .name = "lcd_pwm_used",
        .type = PROPERTY_INTGER,
        .v.value = 1,
    },
    {
        .name = "lcd_pwm_ch",
        .type = PROPERTY_INTGER,
        .v.value = 1,
    },
    {
        .name = "lcd_pwm_freq",
        .type = PROPERTY_INTGER,
        .v.value = 50000,
    },
    {
        .name = "lcd_pwm_pol",
        .type = PROPERTY_INTGER,
        .v.value = 1,
    },
    {
        .name = "lcd_pwm_max_limit",
        .type = PROPERTY_INTGER,
        .v.value = 255,
    },
    {
        .name = "lcd_hbp",
        .type = PROPERTY_INTGER,
        .v.value = 88,
    },
    {
        .name = "lcd_ht",
        .type = PROPERTY_INTGER,
        .v.value = 721,
    },
    {
        .name = "lcd_hspw",
        .type = PROPERTY_INTGER,
        .v.value = 56,
    },
    {
        .name = "lcd_vbp",
        .type = PROPERTY_INTGER,
        .v.value = 23,
    },
    {
        .name = "lcd_vt",
        .type = PROPERTY_INTGER,
        .v.value = 996,
    },
    {
        .name = "lcd_vspw",
        .type = PROPERTY_INTGER,
        .v.value = 10,
    },
    {
        .name = "lcd_frm",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "lcd_io_phase",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "lcd_gamma_en",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "lcd_bright_curve_en",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "lcd_cmap_en",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "deu_mode",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "lcdgamma4iep",
        .type = PROPERTY_INTGER,
        .v.value = 22,
    },
    {
        .name = "smart_color",
        .type = PROPERTY_INTGER,
        .v.value = 90,
    },
    {
        .name = "lcd_dsi_if",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "lcd_dsi_lane",
        .type = PROPERTY_INTGER,
        .v.value = 2,
    },
    {
        .name = "lcd_dsi_format",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "lcd_dsi_te",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "lcd_fsync_act_time",
        .type = PROPERTY_INTGER,
        .v.value = 1000,
    },
    {
        .name = "lcd_fsync_dis_time",
        .type = PROPERTY_INTGER,
        .v.value = 1000,
    },

    // backlight enable
    /*
    {
        .name = "lcd_gpio_1",
        .type = PROPERTY_GPIO,
        .v.gpio_list = {
            .gpio = GPIOE(11),
            .mul_sel = GPIO_DIRECTION_OUTPUT,
            .pull = 0,
            .drv_level = 3,
            .data = 1,
        },
    },
    */
    /* DSI reset */
    // {
    //  .name = "lcd_gpio_0",
    //  .type = PROPERTY_GPIO,
    //  .v.gpio_list = {
    //      .gpio = GPIOG(13),
    //      .mul_sel = GPIO_DIRECTION_OUTPUT,
    //      .pull = 0,
    //      .drv_level = 3,
    //      .data = 1,
    //  },
    // },
    // gpio
    {
        .name = "LCD0_D0",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(0),
            .mul_sel = 4,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D1",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(1),
            .mul_sel = 4,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D2",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(2),
            .mul_sel = 4,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D3",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(3),
            .mul_sel = 4,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D4",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(4),
            .mul_sel = 4,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D5",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(5),
            .mul_sel = 4,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D6",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(6),
            .mul_sel = 4,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D7",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(7),
            .mul_sel = 4,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D8",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(8),
            .mul_sel = 4,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D9",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(9),
            .mul_sel = 4,
            .pull = 0,
            .drv_level = 3,
        },
    },
};

struct property_t g_lcd0_config_lvds[] = {
    {
        .name = "lcd_used",
        .type = PROPERTY_INTGER,
        .v.value = 1,
    },
    {
        .name = "lcd_driver_name",
        .type = PROPERTY_STRING,
        .v.str = "default_lcd",
    },
    {
        .name = "lcd_backlight",
        .type = PROPERTY_INTGER,
        .v.value = 150,
    },
    {
        .name = "lcd_if",
        .type = PROPERTY_INTGER,
        .v.value = LCD_IF_LVDS,
    },
    {
        .name = "lcd_x",
        .type = PROPERTY_INTGER,
        .v.value = 1920,
    },
    {
        .name = "lcd_y",
        .type = PROPERTY_INTGER,
        .v.value = 1080,
    },
    {
        .name = "lcd_width",
        .type = PROPERTY_INTGER,
        .v.value = 150,
    },
    {
        .name = "lcd_height",
        .type = PROPERTY_INTGER,
        .v.value = 94,
    },
    {
        .name = "lcd_dclk_freq",
        .type = PROPERTY_INTGER,
        .v.value = 71 * 2, // dual lvds, freq=single*2.
    },
    {
        .name = "lcd_rb_swap",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "lcd_pwm_used",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "lcd_pwm_ch",
        .type = PROPERTY_INTGER,
        .v.value = 7,
    },
    {
        .name = "lcd_pwm_freq",
        .type = PROPERTY_INTGER,
        .v.value = 50000,
    },
    {
        .name = "lcd_pwm_pol",
        .type = PROPERTY_INTGER,
        .v.value = 1,
    },
    {
        .name = "lcd_pwm_max_limit",
        .type = PROPERTY_INTGER,
        .v.value = 255,
    },
    {
        .name = "lcd_hbp",
        .type = PROPERTY_INTGER,
        .v.value = 90, // P19: Tblk(h) period 74-90-140
    },
    {
        .name = "lcd_ht",
        .type = PROPERTY_INTGER,
        .v.value = (960 + 90) * 2, // x+hbp P19: Th period 1034-1050-1100
    },
    {
        .name = "lcd_hspw",
        .type = PROPERTY_INTGER,
        .v.value = 10,
    },
    {
        .name = "lcd_vbp",
        .type = PROPERTY_INTGER,
        .v.value = 50, // P19: Tblk(v) period 12-50-738
    },
    {
        .name = "lcd_vt",
        .type = PROPERTY_INTGER,
        .v.value = (1080 + 50) + 50, // y+vbp P19: Tv period 1092-1130-1818
    },
    {
        .name = "lcd_vspw",
        .type = PROPERTY_INTGER,
        .v.value = 5,
    },
    {
        .name = "lcd_lvds_if",
        .type = PROPERTY_INTGER,
        .v.value = LCD_LVDS_IF_DUAL_LINK,
    },
    {
        .name = "lcd_lvds_colordepth",
        .type = PROPERTY_INTGER,
        .v.value = LCD_LVDS_8bit,
    },
    {
        .name = "lcd_lvds_mode",
        .type = PROPERTY_INTGER,
        .v.value = LCD_LVDS_MODE_NS,
    },
    {
        .name = "lcd_frm",
        .type = PROPERTY_INTGER,
        .v.value = 1,
    },
    {
        .name = "lcd_io_phase",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "lcd_hv_clk_phase",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "lcd_hv_sync_polarity",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "lcd_gamma_en",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "lcd_bright_curve_en",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "lcd_cmap_en",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "deu_mode",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "lcdgamma4iep",
        .type = PROPERTY_INTGER,
        .v.value = 22,
    },
    {
        .name = "smart_color",
        .type = PROPERTY_INTGER,
        .v.value = 90,
    },

    // gpio
    {
        .name = "LCD0_D0",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(0),
            .mul_sel = 3,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D1",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(1),
            .mul_sel = 3,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D2",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(2),
            .mul_sel = 3,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D3",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(3),
            .mul_sel = 3,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D4",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(4),
            .mul_sel = 3,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D5",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(5),
            .mul_sel = 3,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D6",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(6),
            .mul_sel = 3,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D7",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(7),
            .mul_sel = 3,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D8",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(8),
            .mul_sel = 3,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D9",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(9),
            .mul_sel = 3,
            .pull = 0,
            .drv_level = 3,
        },
    },
#if 1
    {
        .name = "LCD0_D14",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(10),
            .mul_sel = 3,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D15",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(11),
            .mul_sel = 3,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D18",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(12),
            .mul_sel = 3,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D19",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(13),
            .mul_sel = 3,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D20",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(14),
            .mul_sel = 3,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D21",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(15),
            .mul_sel = 3,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D22",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(16),
            .mul_sel = 3,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_D23",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(17),
            .mul_sel = 3,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_CLK",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(18),
            .mul_sel = 3,
            .pull = 0,
            .drv_level = 3,
        },
    },
    {
        .name = "LCD0_DE",
        .type = PROPERTY_PIN,
        .v.gpio_list = {
            .gpio = GPIOD(19),
            .mul_sel = 3,
            .pull = 0,
            .drv_level = 3,
        },
    },
#endif

};

struct property_t g_lcd1_config[] = {
    {
        .name = "lcd_used",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
};

struct property_t g_disp_config[] = {
    {
        .name = "disp_init_enable",
        .type = PROPERTY_INTGER,
        .v.value = 1,
    },
    {
        .name = "disp_mode",
        .type = PROPERTY_INTGER,
        .v.value = 0, /* DISP_INIT_MODE_SCREEN0 */
    },
    {
        .name = "screen0_output_type",
        .type = PROPERTY_INTGER,
        .v.value = 1, /* DISP_OUTPUT_TYPE_LCD */
    },
    {
        .name = "screen0_output_mode",
        .type = PROPERTY_INTGER,
        .v.value = 4,
    },
    {
        .name = "screen0_output_format",
        .type = PROPERTY_INTGER,
        .v.value = 1,
    },
    {
        .name = "screen0_output_bits",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "screen0_output_eotf",
        .type = PROPERTY_INTGER,
        .v.value = 4,
    },
    {
        .name = "screen0_output_cs",
        .type = PROPERTY_INTGER,
        .v.value = 257,
    },
    {
        .name = "screen0_output_dvi_hdmi",
        .type = PROPERTY_INTGER,
        .v.value = 2,
    },
    {
        .name = "screen0_output_range",
        .type = PROPERTY_INTGER,
        .v.value = 2,
    },
    {
        .name = "screen0_output_scan",
        .type = PROPERTY_INTGER,
        .v.value = 0,
    },
    {
        .name = "screen0_output_aspect_ratio",
        .type = PROPERTY_INTGER,
        .v.value = 8,
    },
};

u32 g_lcd0_config_len = sizeof(g_lcd0_config_rgb) / sizeof(struct property_t);
u32 g_lcd1_config_len = sizeof(g_lcd1_config) / sizeof(struct property_t);
u32 g_disp_config_len = sizeof(g_disp_config) / sizeof(struct property_t);

static struct property_t *_lcd_property_find(const char *name, struct property_t *_config, const u32 config_len)
{
    u32 i;

    for (i = 0; i < config_len; i++)
    {
        if (_config[i].type != PROPERTY_INTGER)
        {
            continue;
        }

        if (!strcmp(name, _config[i].name))
        {
            return _config + i;
        }
    }

    return NULL;
}

#ifndef LCD_XML_CONFIG_FILE
#define LCD_CONFIG_FILE "/etc/lcd_config.xml"
#else
#define LCD_CONFIG_FILE LCD_XML_CONFIG_FILE
#endif
const struct lcd_cfg_panel_info *load_lcd_config_from_xml(void)
{
    struct property_t *_config_item;
    static rt_uint8_t init_state = 0;

    rt_enter_critical();
    if (init_state == 0)
    {
        init_state = 1;
        rt_exit_critical();
    }
    else
    {
        rt_exit_critical();

        while (init_state != 2)
        {
            rt_thread_mdelay(10);
        }
        goto _RET;
    }

    g_lcd0_config = g_lcd0_config_rgb;
    g_lcd0_config_len = sizeof(g_lcd0_config_rgb) / sizeof(struct property_t);
_RET:

    init_state = 2;
    _config_item = _lcd_property_find("lcd_x", g_lcd0_config, g_lcd0_config_len);
    _panel_info.width = _config_item->v.value;
    _config_item = _lcd_property_find("lcd_y", g_lcd0_config, g_lcd0_config_len);
    _panel_info.height = _config_item->v.value;

    return &_panel_info;
}
