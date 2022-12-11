
#include <aw_list.h>
#include <rtthread.h>
#include <init.h>
#include <hal_reset.h>
// #include <melis/standby/standby.h>
#include "de/include.h"
#include "dev_disp.h"

struct disp_drv_info g_disp_drv;
#define DISP_MEM_NUM 10
/* alloc based on 4K byte */
#define MY_BYTE_ALIGN(x) (((x + (4*1024-1)) >> 12) << 12)
static unsigned int g_disp = 0, g_enhance_mode = 0, g_cvbs_enhance_mode;
static bool g_pm_runtime_enable;
struct disp_layer_config lyr_cfg[16];
struct disp_layer_config2 lyr_cfg2[16];
struct disp_layer_config2 lyr_cfg2_1[16];
#define FDT_DISP_PATH "disp"
hal_workqueue *g_disp_work_queue;
static u32 suspend_output_type[4] = {0};
static u32 DISP_print = 0xffff; /* print cmd which eq DISP_print */
static u32 power_status_init;

/*
 * 0:normal;
 * suspend_status&1 != 0:in early_suspend;
 * suspend_status&2 != 0:in suspend;
 */
static u32 suspend_status;

/* pm device */
struct dev_pm *pm;


#if 0
static int _csc_enhance_setting[3][4] = {
    {50, 50, 50, 50},
    /* normal */
    {50, 50, 50, 50},
    /* vivid */
    {50, 40, 50, 50},
    /* soft */
};
#else
extern int _csc_enhance_setting[3][4];
#endif

int disp_enhance_mode_show(u32 disp, char *buf)
{
    sprintf(buf, "%u\n", g_enhance_mode);
    return g_enhance_mode;
}


int disp_enhance_mode_store(u32 disp, u32 value)
{

    /*
     * mode: 0: standard; 1: vivid; 2: soft; 3: demo vivid
     */
    if (value > 3)
        pr_warn("Invalid value, 0~3 is expected!\n");
    else {
        int num_screens = 2;
        struct disp_manager *mgr = NULL;
        struct disp_enhance *enhance = NULL;

        g_enhance_mode = value;

        num_screens = bsp_disp_feat_get_num_screens();

        if (disp < num_screens)
            mgr = g_disp_drv.mgr[disp];

        if (mgr) {
            enhance = mgr->enhance;
            if (enhance && enhance->set_mode)
#if defined(CONFIG_ARCH_SUN8IW15) || defined(CONFIG_ARCH_SUN50IW1)
                enhance->set_mode(enhance,
                          (g_enhance_mode == 2) ?
                          1 : g_enhance_mode);
            if (g_enhance_mode == 2)
                g_enhance_mode = 3;
#else
            enhance->set_mode(enhance,
                      (g_enhance_mode == 3) ?
                      1 : g_enhance_mode);
#endif

            if (enhance && enhance->demo_enable
                && enhance->demo_disable) {
                if (g_enhance_mode == 3)
                    enhance->demo_enable(enhance);
                else
                    enhance->demo_disable(enhance);
            }
        }
    }

    return 0;
}


int disp_enhance_bright_show(u32 disp, char *buf)
{
    int num_screens = 2;
    struct disp_manager *mgr = NULL;
    struct disp_enhance *enhance = NULL;
    int value = 0;
    int real_mode = (g_enhance_mode == 3) ? 1 : g_enhance_mode;

    num_screens = bsp_disp_feat_get_num_screens();
    if (disp < num_screens)
        mgr = g_disp_drv.mgr[disp];

    if (mgr) {
        enhance = mgr->enhance;
        if (enhance && enhance->get_bright)
            value = enhance->get_bright(enhance);
    }

    sprintf(buf, "%d %d\n", _csc_enhance_setting[real_mode][0], value);
    return value;
}

int disp_enhance_bright_store(u32 disp, u32 value)
{
    int err;
    int num_screens = 2;
    struct disp_manager *mgr = NULL;
    struct disp_enhance *enhance = NULL;
    int real_mode = (g_enhance_mode == 3) ? 1 : g_enhance_mode;

    num_screens = bsp_disp_feat_get_num_screens();
    if (disp < num_screens)
        mgr = g_disp_drv.mgr[disp];

    if (mgr) {
        enhance = mgr->enhance;
        if (enhance && enhance->set_bright) {
            _csc_enhance_setting[real_mode][0] = value;
            enhance->set_bright(enhance, value);
        }
        if (enhance && enhance->set_mode) {
            enhance->set_mode(enhance, real_mode ? 0 : 1);
            enhance->set_mode(enhance, real_mode);
        }
    }

    return 0;
}

int disp_enhance_saturation_show(u32 disp, char *buf)
{
    int num_screens = 2;
    struct disp_manager *mgr = NULL;
    struct disp_enhance *enhance = NULL;
    int value = 0;
    int real_mode = (g_enhance_mode == 3) ? 1 : g_enhance_mode;

    num_screens = bsp_disp_feat_get_num_screens();
    if (disp < num_screens)
        mgr = g_disp_drv.mgr[disp];

    if (mgr) {
        enhance = mgr->enhance;
        if (enhance && enhance->get_saturation)
            value = enhance->get_saturation(enhance);
    }

    sprintf(buf, "%d %d\n", value, _csc_enhance_setting[real_mode][2]);
    return value;
}

int disp_enhance_saturation_store(u32 disp, u32 value)
{
    int err;
    int num_screens = 2;
    struct disp_manager *mgr = NULL;
    struct disp_enhance *enhance = NULL;
    int real_mode = (g_enhance_mode == 3) ? 1 : g_enhance_mode;


    num_screens = bsp_disp_feat_get_num_screens();
    if (disp < num_screens)
        mgr = g_disp_drv.mgr[disp];

    if (mgr) {
        enhance = mgr->enhance;
        if (enhance && enhance->set_saturation) {
            _csc_enhance_setting[real_mode][2] = value;
            enhance->set_saturation(enhance, value);
        }
        if (enhance && enhance->set_mode) {
            enhance->set_mode(enhance, real_mode ? 0 : 1);
            enhance->set_mode(enhance, real_mode);
        }
    }

    return 0;
}

int disp_enhance_contrast_show(u32 disp, char *buf)
{
    int num_screens = 2;
    struct disp_manager *mgr = NULL;
    struct disp_enhance *enhance = NULL;
    int value = 0;
    int real_mode = (g_enhance_mode == 3) ? 1 : g_enhance_mode;

    num_screens = bsp_disp_feat_get_num_screens();
    if (disp < num_screens)
        mgr = g_disp_drv.mgr[disp];

    if (mgr) {
        enhance = mgr->enhance;
        if (enhance && enhance->get_contrast)
            value = enhance->get_contrast(enhance);
    }

    sprintf(buf, "%d %d\n", value, _csc_enhance_setting[real_mode][1]);
    return value;
}

int disp_enhance_contrast_store(u32 disp, u32 value)
{
    int err;
    int num_screens = 2;
    struct disp_manager *mgr = NULL;
    struct disp_enhance *enhance = NULL;
    int real_mode = (g_enhance_mode == 3) ? 1 : g_enhance_mode;


    num_screens = bsp_disp_feat_get_num_screens();
    if (disp < num_screens)
        mgr = g_disp_drv.mgr[disp];

    if (mgr) {
        enhance = mgr->enhance;
        if (enhance && enhance->set_contrast) {
            _csc_enhance_setting[real_mode][1] = value;
            enhance->set_contrast(enhance, value);
        }
        if (enhance && enhance->set_mode) {
            enhance->set_mode(enhance, real_mode ? 0 : 1);
            enhance->set_mode(enhance, real_mode);
        }
    }

    return 0;
}

int disp_enhance_edge_show(u32 disp, char *buf)
{
    int num_screens = 2;
    struct disp_manager *mgr = NULL;
    struct disp_enhance *enhance = NULL;
    int value = 0;

    num_screens = bsp_disp_feat_get_num_screens();
    if (disp < num_screens)
        mgr = g_disp_drv.mgr[disp];

    if (mgr) {
        enhance = mgr->enhance;
        if (enhance && enhance->get_edge)
            value = enhance->get_edge(enhance);
    }

    sprintf(buf, "%d\n", value);
    return value;
}

int disp_enhance_edge_store(u32 disp, u32 value)
{
    int err;
    int num_screens = 2;
    struct disp_manager *mgr = NULL;
    struct disp_enhance *enhance = NULL;


    num_screens = bsp_disp_feat_get_num_screens();
    if (disp < num_screens)
        mgr = g_disp_drv.mgr[disp];

    if (mgr) {
        enhance = mgr->enhance;
        if (enhance && enhance->set_edge)
            enhance->set_edge(enhance, value);
    }

    return 0;
}

int disp_enhance_detail_show(u32 disp, char *buf)
{
    int num_screens = 2;
    struct disp_manager *mgr = NULL;
    struct disp_enhance *enhance = NULL;
    int value = 0;

    num_screens = bsp_disp_feat_get_num_screens();
    if (disp < num_screens)
        mgr = g_disp_drv.mgr[disp];

    if (mgr) {
        enhance = mgr->enhance;
        if (enhance && enhance->get_detail)
            value = enhance->get_detail(enhance);
    }

    sprintf(buf, "%d\n", value);
    return value;
}

int disp_enhance_detail_store(u32 disp, u32 value)
{
    int err;
    int num_screens = 2;
    struct disp_manager *mgr = NULL;
    struct disp_enhance *enhance = NULL;


    num_screens = bsp_disp_feat_get_num_screens();
    if (disp < num_screens)
        mgr = g_disp_drv.mgr[disp];

    if (mgr) {
        enhance = mgr->enhance;
        if (enhance && enhance->set_detail)
            enhance->set_detail(enhance, value);
    }

    return 0;
}

int disp_enhance_denoise_show(u32 disp, char *buf)
{
    int num_screens = 2;
    struct disp_manager *mgr = NULL;
    struct disp_enhance *enhance = NULL;
    int value = 0;

    num_screens = bsp_disp_feat_get_num_screens();
    if (disp < num_screens)
        mgr = g_disp_drv.mgr[disp];

    if (mgr) {
        enhance = mgr->enhance;
        if (enhance && enhance->get_denoise)
            value = enhance->get_denoise(enhance);
    }

    sprintf(buf, "%d\n", value);
    return value;
}

int disp_enhance_denoise_store(u32 disp, u32 value)
{
    int err;
    int num_screens = 2;
    struct disp_manager *mgr = NULL;
    struct disp_enhance *enhance = NULL;

    num_screens = bsp_disp_feat_get_num_screens();
    if (disp < num_screens)
        mgr = g_disp_drv.mgr[disp];

    if (mgr) {
        enhance = mgr->enhance;
        if (enhance && enhance->set_denoise)
            enhance->set_denoise(enhance, value);
    }

    return 0;
}



int disp_color_temperature_show(u32 disp, char *buf)
{
    int num_screens = 2;
    struct disp_manager *mgr = NULL;
    struct disp_device *dispdev = NULL;
    int value = 0;

    num_screens = bsp_disp_feat_get_num_screens();
    if (disp < num_screens)
        mgr = g_disp_drv.mgr[disp];

    if (mgr && mgr->device) {
        dispdev = mgr->device;
        if (dispdev->get_color_temperature)
            value = dispdev->get_color_temperature(dispdev);
    }

    sprintf(buf, "%d\n", value);
    return value;
}

int disp_color_temperature_store(u32 disp, s32 value)
{
    int err;
    int num_screens = 2;
    struct disp_manager *mgr = NULL;
    struct disp_device *dispdev = NULL;

    if ((value > 256) || (value < -256)) {
        pr_warn("value shoud in range [-256,256]\n");
        value = (value > 256) ? 256 : value;
        value = (value < -256) ? -256 : value;
    }

    num_screens = bsp_disp_feat_get_num_screens();
    if (g_disp < num_screens)
        mgr = g_disp_drv.mgr[g_disp];

    if (mgr && mgr->device) {
        dispdev = mgr->device;
        if (dispdev->set_color_temperature)
            value = dispdev->set_color_temperature(dispdev, value);
    }

    return 0;
}

int sunxi_disp_get_source_ops(struct sunxi_disp_source_ops *src_ops)
{
    memset((void *)src_ops, 0, sizeof(struct sunxi_disp_source_ops));

    src_ops->sunxi_lcd_set_panel_funs = bsp_disp_lcd_set_panel_funs;
    src_ops->sunxi_lcd_delay_ms = disp_delay_ms;
    src_ops->sunxi_lcd_delay_us = disp_delay_us;
    src_ops->sunxi_lcd_backlight_enable = bsp_disp_lcd_backlight_enable;
    src_ops->sunxi_lcd_backlight_disable = bsp_disp_lcd_backlight_disable;
    src_ops->sunxi_lcd_pwm_enable = bsp_disp_lcd_pwm_enable;
    src_ops->sunxi_lcd_pwm_disable = bsp_disp_lcd_pwm_disable;
    src_ops->sunxi_lcd_power_enable = bsp_disp_lcd_power_enable;
    src_ops->sunxi_lcd_power_disable = bsp_disp_lcd_power_disable;
    src_ops->sunxi_lcd_tcon_enable = bsp_disp_lcd_tcon_enable;
    src_ops->sunxi_lcd_tcon_disable = bsp_disp_lcd_tcon_disable;
    src_ops->sunxi_lcd_pin_cfg = bsp_disp_lcd_pin_cfg;
    src_ops->sunxi_lcd_gpio_set_value = bsp_disp_lcd_gpio_set_value;
    src_ops->sunxi_lcd_gpio_set_direction = bsp_disp_lcd_gpio_set_direction;
#ifdef SUPPORT_DSI
    src_ops->sunxi_lcd_dsi_dcs_write = bsp_disp_lcd_dsi_dcs_wr;
    src_ops->sunxi_lcd_dsi_gen_write = bsp_disp_lcd_dsi_gen_wr;
    src_ops->sunxi_lcd_dsi_clk_enable = bsp_disp_lcd_dsi_clk_enable;
    src_ops->sunxi_lcd_dsi_mode_switch = bsp_disp_lcd_dsi_mode_switch;
    src_ops->sunxi_lcd_dsi_gen_short_read = bsp_disp_lcd_dsi_gen_short_read;
    src_ops->sunxi_lcd_dsi_dcs_read = bsp_disp_lcd_dsi_dcs_read;
    src_ops->sunxi_lcd_dsi_set_max_ret_size = bsp_disp_lcd_set_max_ret_size;
#endif
    src_ops->sunxi_lcd_cpu_write = tcon0_cpu_wr_16b;
    src_ops->sunxi_lcd_cpu_write_data = tcon0_cpu_wr_16b_data;
    src_ops->sunxi_lcd_cpu_write_index = tcon0_cpu_wr_16b_index;
    src_ops->sunxi_lcd_cpu_set_auto_mode = tcon0_cpu_set_auto_mode;

    return 0;
}

static s32 parser_disp_init_para(struct disp_init_para *init_para)
{
    s32 value;
    s32 i;

    memset(init_para, 0, sizeof(struct disp_init_para));

    if (disp_sys_script_get_item("disp","disp_init_enable", &value, 1) != 1) {
        DE_WRN("of_property_read disp_init.disp_init_enable fail\n");
        return -1;
    }
    init_para->b_init = value;

    if (disp_sys_script_get_item("disp","disp_mode", &value, 1) != 1) {
        DE_WRN("of_property_read disp_init.disp_mode fail\n");
        return -1;
    }
    init_para->disp_mode = value;

    /* screen0 */
    if (disp_sys_script_get_item("disp", "screen0_output_type", &value, 1) != 1) {
        DE_WRN("of_property_read disp_init.screen0_output_type fail\n");
        return -1;
    }
    if (value == 0) {
        init_para->output_type[0] = DISP_OUTPUT_TYPE_NONE;
    } else if (value == 1) {
        init_para->output_type[0] = DISP_OUTPUT_TYPE_LCD;
    } else if (value == 2) {
        init_para->output_type[0] = DISP_OUTPUT_TYPE_TV;
    } else if (value == 3) {
        init_para->output_type[0] = DISP_OUTPUT_TYPE_HDMI;
    } else if (value == 4) {
        init_para->output_type[0] = DISP_OUTPUT_TYPE_VGA;
    } else if (value == 5) {
        init_para->output_type[0] = DISP_OUTPUT_TYPE_VDPO;
    } else if (value == 6) {
        init_para->output_type[0] = DISP_OUTPUT_TYPE_EDP;
    } else {
        DE_WRN("invalid screen0_output_type %d\n",
              init_para->output_type[0]);
        return -1;
    }

    if (disp_sys_script_get_item("disp", "screen0_output_mode", &value, 1) != 1) {
        DE_WRN("of_property_read disp_init.screen0_output_mode fail\n");
        return -1;
    }

    if (init_para->output_type[0] != DISP_OUTPUT_TYPE_NONE &&
        init_para->output_type[0] != DISP_OUTPUT_TYPE_LCD)
        init_para->output_mode[0] = value;

    if (disp_sys_script_get_item("disp", "screen0_output_format", &value, 1) != 1) {
        DE_INF("of_property_read screen0_output_format fail\n");
    } else {
        init_para->output_format[0] = value;
        init_para->using_device_config[0] = true;
    }

    if (disp_sys_script_get_item("disp", "screen0_output_bits", &value, 1) != 1) {
        DE_INF("of_property_read screen0_output_bits fail\n");
    } else {
        init_para->output_bits[0] = value;
        init_para->using_device_config[0] = true;
    }

    if (disp_sys_script_get_item("disp", "screen0_output_eotf", &value, 1) != 1) {
        DE_INF("of_property_read screen0_output_eotf fail\n");
    } else {
        init_para->output_eotf[0] = value;
        init_para->using_device_config[0] = true;
    }

    if (disp_sys_script_get_item("disp", "screen0_output_cs", &value, 1) != 1) {
        DE_INF("of_property_read screen0_output_cs fail\n");
    } else {
        init_para->output_cs[0] = value;
        init_para->using_device_config[0] = true;
    }

    if (disp_sys_script_get_item("disp", "screen0_output_dvi_hdmi", &value, 1) != 1) {
        DE_INF("of_property_read screen0_output_dvi_hdmi fail\n");
    } else {
        init_para->output_dvi_hdmi[0] = value;
        init_para->using_device_config[0] = true;
    }

    if (disp_sys_script_get_item("disp", "screen0_output_range", &value, 1) != 1) {
        DE_INF("of_property_read screen0_output_range fail\n");
    } else {
        init_para->output_range[0] = value;
        init_para->using_device_config[0] = true;
    }

    if (disp_sys_script_get_item("disp", "screen0_output_scan", &value, 1) != 1) {
        DE_INF("of_property_read screen0_output_scan fail\n");
    } else {
        init_para->output_scan[0] = value;
        init_para->using_device_config[0] = true;
    }

    if (disp_sys_script_get_item("disp", "screen0_output_aspect_ratio", &value, 1) != 1) {
        DE_INF("of_property_read screen0_output_aspect_ratio fail\n");
    } else {
        init_para->output_aspect_ratio[0] = value;
        init_para->using_device_config[0] = true;
    }

#if DISP_SCREEN_NUM > 1
        /* screen1 */
        if (disp_sys_script_get_item("disp", "screen1_output_type", &value, 1) != 1) {
            DE_WRN("of_property_read screen1_output_type fail\n");
            return -1;
        }
        if (value == 0) {
            init_para->output_type[1] = DISP_OUTPUT_TYPE_NONE;
        } else if (value == 1) {
            init_para->output_type[1] = DISP_OUTPUT_TYPE_LCD;
        } else if (value == 2) {
            init_para->output_type[1] = DISP_OUTPUT_TYPE_TV;
        } else if (value == 3) {
            init_para->output_type[1] = DISP_OUTPUT_TYPE_HDMI;
        } else if (value == 4) {
            init_para->output_type[1] = DISP_OUTPUT_TYPE_VGA;
        } else if (value == 5) {
            init_para->output_type[1] = DISP_OUTPUT_TYPE_VDPO;
        } else if (value == 6) {
            init_para->output_type[1] = DISP_OUTPUT_TYPE_EDP;
        } else {
            DE_WRN("invalid screen1_output_type %d\n",
                  init_para->output_type[1]);
            return -1;
        }

        if (disp_sys_script_get_item("disp", "screen1_output_mode", &value, 1) != 1)
            DE_INF
                ("of_property_read screen1_output_mode fail\n");
        if (init_para->output_type[1] != DISP_OUTPUT_TYPE_NONE &&
            init_para->output_type[1] != DISP_OUTPUT_TYPE_LCD)
            init_para->output_mode[1] = value;

        if (disp_sys_script_get_item("disp", "screen1_output_format", &value, 1) != 1) {
            DE_INF("of_property_read screen1_output_format fail\n");
        } else {
            init_para->output_format[1] = value;
            init_para->using_device_config[1] = true;
        }

        if (disp_sys_script_get_item("disp", "screen1_output_bits",
                         &value, 1) != 1) {
            DE_INF("of_property_read screen1_output_bits fail\n");
        } else {
            init_para->output_bits[1] = value;
            init_para->using_device_config[1] = true;
        }

        if (disp_sys_script_get_item("disp", "screen1_output_eotf",
                         &value, 1) != 1) {
            DE_INF("of_property_read screen1_output_eotf fail\n");
        } else {
            init_para->output_eotf[1] = value;
            init_para->using_device_config[1] = true;
        }

        if (disp_sys_script_get_item("disp", "screen1_output_cs",
                         &value, 1) != 1) {
            DE_INF("of_property_read screen1_output_cs fail\n");
        } else {
            init_para->output_cs[1] = value;
            init_para->using_device_config[1] = true;
        }

        if (disp_sys_script_get_item("disp", "screen1_output_dvi_hdmi",
                         &value, 1) != 1) {
            DE_INF(
                "of_property_read screen1_output_dvi_hdmi fail\n");
        } else {
            init_para->output_dvi_hdmi[1] = value;
            init_para->using_device_config[1] = true;
        }

        if (disp_sys_script_get_item("disp", "screen1_output_range",
                         &value, 1) != 1) {
            DE_INF("of_property_read screen1_output_range fail\n");
        } else {
            init_para->output_range[1] = value;
            init_para->using_device_config[1] = true;
        }

        if (disp_sys_script_get_item("disp", "screen1_output_scan",
                         &value, 1) != 1) {
            DE_INF("of_property_read screen1_output_scan fail\n");
        } else {
            init_para->output_scan[1] = value;
            init_para->using_device_config[1] = true;
        }

        if (disp_sys_script_get_item("disp",
                         "screen1_output_aspect_ratio",
                         &value, 1) != 1) {
            DE_INF("read screen1_output_aspect_ratio fail\n");
        } else {
            init_para->output_aspect_ratio[1] = value;
            init_para->using_device_config[1] = true;
        }
#endif
    /* fb0 */
    init_para->buffer_num[0] = 2;
    if (disp_sys_script_get_item("disp", "fb0_buffer_num", &value, 1) != 1)
        init_para->buffer_num[0] = 2;
    else
        init_para->buffer_num[0] = value;

    if (disp_sys_script_get_item("disp", "fb0_format", &value, 1) != 1) {
        DE_INF("of_property_read disp_init.fb0_format fail\n");
        init_para->format[0] = 0;
    } else
        init_para->format[0] = value;

    if (disp_sys_script_get_item("disp", "fb0_width", &value, 1) != 1) {
        DE_INF("of_property_read fb0_width fail\n");
        init_para->fb_width[0] = 0;
    } else
        init_para->fb_width[0] = value;

    if (disp_sys_script_get_item("disp", "fb0_height", &value, 1) != 1) {
        DE_INF("of_property_read fb0_height fail\n");
        init_para->fb_height[0] = 0;
    } else
        init_para->fb_height[0] = value;

    /* fb1 */
#if DISP_SCREEN_NUM > 1
        init_para->buffer_num[1] = 2;

        if (disp_sys_script_get_item("disp", "fb1_buffer_num", &value,
                         1) != 1)
            init_para->buffer_num[1] = value;

        if (disp_sys_script_get_item("disp", "fb1_format", &value, 1) !=
            1)
            init_para->format[1] = value;

        if (disp_sys_script_get_item("disp", "fb1_width", &value, 1) !=
            1)
            init_para->fb_width[1] = value;

        if (disp_sys_script_get_item("disp", "fb_height", &value, 1) != 1)
            init_para->fb_height[1] = value;
#endif

    DE_INF("====display init para begin====\n");
    DE_INF("b_init:%d\n", init_para->b_init);
    DE_INF("disp_mode:%d\n\n", init_para->disp_mode);
    for (i = 0; i < DISP_SCREEN_NUM; i++) {
        DE_INF("output_type[%d]:%d\n", i, init_para->output_type[i]);
        DE_INF("output_mode[%d]:%d\n", i, init_para->output_mode[i]);
    }
    for (i = 0; i < DISP_SCREEN_NUM; i++) {
        DE_INF("buffer_num[%d]:%d\n", i, init_para->buffer_num[i]);
        DE_INF("format[%d]:%d\n", i, init_para->format[i]);
        DE_INF("fb_width[%d]:%d\n", i, init_para->fb_width[i]);
        DE_INF("fb_height[%d]:%d\n", i, init_para->fb_height[i]);
    }
    DE_INF("====display init para end====\n");

    return 0;
}

static void start_work(hal_work *work, void* work_data)
{
    int num_screens;
    int screen_id;
    int count = 0;

    num_screens = bsp_disp_feat_get_num_screens();
    while ((g_disp_drv.inited == 0) && (count < 5)) {
        count++;
        disp_delay_ms(20);
    }
    if (count >= 5)
        DE_WRN("%s, timeout\n", __func__);
    if (g_disp_drv.para.boot_info.sync == 0) {
        for (screen_id = 0; screen_id < num_screens; screen_id++) {
            int disp_mode = g_disp_drv.disp_init.disp_mode;
            int output_type =
                g_disp_drv.disp_init.output_type[screen_id%DE_NUM];
            int output_mode =
                g_disp_drv.disp_init.output_mode[screen_id%DE_NUM];
            int lcd_registered =
                bsp_disp_get_lcd_registered(screen_id);
            int hdmi_registered = bsp_disp_get_hdmi_registered();

            DE_INF(
                "sel=%d, output_type=%d, lcd_reg=%d,hdmi_reg=%d\n",
                screen_id, output_type, lcd_registered,
                hdmi_registered);
            if (((disp_mode == DISP_INIT_MODE_SCREEN0)
                 && (screen_id == 0))
                || ((disp_mode == DISP_INIT_MODE_SCREEN1)
                && (screen_id == 1))) {
                if (output_type == DISP_OUTPUT_TYPE_LCD) {
                    if (lcd_registered &&
                        bsp_disp_get_output_type(screen_id)
                        != DISP_OUTPUT_TYPE_LCD) {
                        bsp_disp_device_switch(screen_id, output_type, output_mode);
                        suspend_output_type[screen_id] =
                            output_type;
                    }
                } else if (output_type
                    == DISP_OUTPUT_TYPE_HDMI) {
                    if (hdmi_registered &&
                        bsp_disp_get_output_type(screen_id)
                        != DISP_OUTPUT_TYPE_HDMI) {
                        disp_delay_ms(600);
                        bsp_disp_device_switch(screen_id, output_type, output_mode);
                        suspend_output_type[screen_id] =
                            output_type;
                    }
                } else {
                    bsp_disp_device_switch(screen_id,
                                   output_type,
                                   output_mode);
                    suspend_output_type[screen_id] =
                        output_type;
                }
            }
        }
    } else {
        if ((g_disp_drv.para.boot_info.type == DISP_OUTPUT_TYPE_HDMI)
            && !bsp_disp_get_hdmi_registered())
            return;
        if (bsp_disp_get_output_type(g_disp_drv.para.boot_info.disp) !=
            g_disp_drv.para.boot_info.type) {
            bsp_disp_sync_with_hw(&g_disp_drv.para);
            suspend_output_type[g_disp_drv.para.boot_info.disp] =
                g_disp_drv.para.boot_info.type;
        }
    }
}

static s32 start_process(void)
{
    hal_workqueue_dowork(g_disp_work_queue, &g_disp_drv.start_work);
    return 0;
}

rt_weak s32 lcd_vsync_event_process(u32 sel)
{
    return 0;
}

static rt_err_t disp_init(void)
{
    struct disp_bsp_init_para *para;
    int i, disp, num_screens;
    unsigned int value, value1, value2, output_type, output_mode;
    unsigned int output_format, output_bits, output_eotf, output_cs;
    rt_err_t ret = -1;

    DE_INF("%s start\n", __func__);

    g_disp_work_queue = hal_workqueue_create("disp2", 8192, 15);

    if (!g_disp_work_queue) {
        DE_WRN("Create disp work queue fail!\n");
        goto OUT;
    }

    parser_disp_init_para(&g_disp_drv.disp_init);

    hal_work_init(&g_disp_drv.start_work, start_work, NULL);

    ret = disp_sys_mutex_init(&g_disp_drv.mlock);
    para = &g_disp_drv.para;
    for (i = 0; i < DISP_MOD_NUM; i++) {
        para->reg_base[i] = g_disp_drv.reg_base[i];
        para->irq_no[i] = g_disp_drv.irq_no[i];
        DE_INF("mod %d, base=0x%lx, irq=%d\n", i,
              para->reg_base[i], para->irq_no[i]);
    }

    for (i = 0; i < DE_NUM; i++) {
        para->clk_de[i] = g_disp_drv.clk_de[i];
        para->clk_bus_de[i] = g_disp_drv.clk_bus_de[i];
    }
    for (i = 0; i < DISP_DEVICE_NUM; i++) {
        para->clk_bus_dpss_top[i] = g_disp_drv.clk_bus_dpss_top[i];
        para->clk_tcon_lcd[i] = g_disp_drv.clk_tcon_lcd[i];
        para->clk_bus_tcon_lcd[i] = g_disp_drv.clk_bus_tcon_lcd[i];
    }

#if defined(SUPPORT_DSI)
    for (i = 0; i < CLK_DSI_NUM; i++) {
        para->clk_mipi_dsi[i] = g_disp_drv.clk_mipi_dsi[i];
        para->clk_bus_mipi_dsi[i] = g_disp_drv.clk_bus_mipi_dsi[i];
    }

#endif
    para->boot_info.dvi_hdmi =
        g_disp_drv.disp_init.output_dvi_hdmi[para->boot_info.disp];
    para->boot_info.range =
        g_disp_drv.disp_init.output_range[para->boot_info.disp];
    para->boot_info.scan =
        g_disp_drv.disp_init.output_scan[para->boot_info.disp];
    para->boot_info.aspect_ratio =
        g_disp_drv.disp_init.output_aspect_ratio[para->boot_info.disp];
    para->boot_info.sync = 0;
    para->start_process = start_process;
    para->vsync_event = lcd_vsync_event_process;

    bsp_disp_init(para);

    num_screens = bsp_disp_feat_get_num_screens();
    for (disp = 0; disp < num_screens; disp++)
        g_disp_drv.mgr[disp] = disp_get_layer_manager(disp);
#if defined(SUPPORT_EINK)
    g_disp_drv.eink_manager[0] = disp_get_eink_manager(0);
#endif

    lcd_init();

    g_disp_drv.inited = true;
    start_process();

    DE_INF("%s finish\n", __func__);
OUT:
    return ret;

}

static int disp_clk_get_wrap(struct disp_drv_info *disp_drv)
{
    int i;
    char id[32];

    /* get clocks for de */
    for (i = 0; i < DE_NUM; i++) {
        sprintf(id, "clk_de%d", i);
        disp_drv->clk_de[i] = disp_getprop_clk(id);
        if (disp_drv->clk_de[i] == (hal_clk_id_t)-1) {
            DE_WRN("failed to get clk for %s\n", id);
        }

        sprintf(id, "clk_bus_de%d", i);
        disp_drv->clk_bus_de[i] = disp_getprop_clk(id);
        if (disp_drv->clk_bus_de[i] == (hal_clk_id_t)-1) {
            DE_WRN("failed to get clk for %s\n", id);
        }
    }
    for (i = 0; i < DISP_DEVICE_NUM; i++) {
        /* get clocks for dpss */
        sprintf(id, "clk_bus_dpss_top%d", i);
        disp_drv->clk_bus_dpss_top[i] = disp_getprop_clk(id);
        if (disp_drv->clk_bus_dpss_top[i] == (hal_clk_id_t)-1) {
            DE_WRN("failed to get clk for %s\n", id);
        }

        /* get clocks for tcon */
        sprintf(id, "clk_tcon%d", i);
        disp_drv->clk_tcon_lcd[i] = disp_getprop_clk(id);
        if (disp_drv->clk_tcon_lcd[i] == (hal_clk_id_t)-1) {
            DE_WRN("failed to get clk for %s\n", id);
        }

        sprintf(id, "clk_bus_tcon%d", i);
        disp_drv->clk_bus_tcon_lcd[i] = disp_getprop_clk(id);
        if (disp_drv->clk_bus_tcon_lcd[i] == (hal_clk_id_t)-1) {
            DE_WRN("failed to get clk for %s\n", id);
        }
    }

#if defined(SUPPORT_DSI)
    for (i = 0; i < CLK_DSI_NUM; i++) {
        sprintf(id, "clk_mipi_dsi%d", i);
        disp_drv->clk_mipi_dsi[i] = disp_getprop_clk(id);
        if (disp_drv->clk_mipi_dsi[i] == (hal_clk_id_t)-1) {
            DE_WRN("failed to get clk for %s\n", id);
        }

        sprintf(id, "clk_bus_mipi_dsi%d", i);
        disp_drv->clk_bus_mipi_dsi[i] = disp_getprop_clk(id);
        if (disp_drv->clk_bus_mipi_dsi[i] == (hal_clk_id_t)-1) {
            DE_WRN("failed to get clk for %s\n", id);
        }
    }
#endif

#if defined(SUPPORT_LVDS)
    for (i = 0; i < DEVICE_LVDS_NUM; i++) {
        sprintf(id, "rst_bus_lvds%d", i);
        disp_drv->para.rst_bus_lvds = disp_get_rst_by_name(id);
        if (disp_drv->para.rst_bus_lvds == NULL) {
            DE_WRN("failed to get rst for %s\n", id);
        }
    }
#endif

    /*FIXME*/
    /*need to get rst bus for lvds*/
    return 0;
}

int disp_suspend(void *para)
{
    u32 screen_id = 0;
    int num_screens;
    struct disp_manager *mgr = NULL;
    struct disp_device *dispdev_suspend = NULL;
    struct list_head *disp_list = NULL;
    struct disp_device *dispdev = NULL;

    num_screens = bsp_disp_feat_get_num_screens();

    if (g_pm_runtime_enable) {

        for (screen_id = 0; screen_id < num_screens;
             screen_id++) {
            mgr = g_disp_drv.mgr[screen_id];
            if (!mgr || !mgr->device)
                continue;
            dispdev = mgr->device;
            if (suspend_output_type[screen_id] ==
                DISP_OUTPUT_TYPE_LCD)
                hal_workqueue_dowork(g_disp_work_queue,
                    &g_disp_drv.start_work);
            if (suspend_output_type[screen_id] !=
                DISP_OUTPUT_TYPE_NONE) {
                if (dispdev->is_enabled(dispdev))
                    dispdev->disable(dispdev);
            }
        }
    } else {

        for (screen_id = 0; screen_id < num_screens;
             screen_id++) {
            mgr = g_disp_drv.mgr[screen_id];
            if (!mgr || !mgr->device)
                continue;
            dispdev = mgr->device;
            if (suspend_output_type[screen_id] !=
                DISP_OUTPUT_TYPE_NONE) {
                if (dispdev->is_enabled(dispdev))
                    dispdev->disable(dispdev);
            }
        }
    }

    /*suspend for all display device */
    disp_list = disp_device_get_list_head();
    list_for_each_entry(dispdev_suspend, disp_list, list) {
        if (dispdev_suspend->suspend)
            dispdev_suspend->suspend(dispdev_suspend);
    }

    /* FIXME: hdmi suspend */
    suspend_status |= DISPLAY_DEEP_SLEEP;

    DE_INF("%s finish\n", __func__);

    return 0;
}

int disp_resume(void *para)
{
    u32 screen_id = 0;
    int num_screens = bsp_disp_feat_get_num_screens();
    struct disp_manager *mgr = NULL;
    struct disp_device_config config;

    struct disp_device *dispdev = NULL;
    struct list_head *disp_list = NULL;

    memset(&config, 0, sizeof(struct disp_device_config));

    /* resume for all display device */
    disp_list = disp_device_get_list_head();
    list_for_each_entry(dispdev, disp_list, list) {
        if (dispdev->resume)
            dispdev->resume(dispdev);
    }

    for (screen_id = 0; screen_id < num_screens; screen_id++) {
        mgr = g_disp_drv.mgr[screen_id];
        if (!mgr || !mgr->device)
            continue;

        if (suspend_output_type[screen_id] != DISP_OUTPUT_TYPE_NONE) {

            if (mgr->device->set_static_config &&
                    mgr->device->get_static_config) {
                mgr->device->get_static_config(mgr->device,
                                &config);
                mgr->device->set_static_config(mgr->device,
                                &config);
            }
            mgr->device->enable(mgr->device);
        }
    }

    suspend_status &= (~DISPLAY_DEEP_SLEEP);

    DE_INF("%s finish\n", __func__);

    return 0;
}

int disp_probe(void)
{
    int i;
    rt_err_t ret;
    int counter = 0;
    pm = NULL;

    DE_INF("[DISP]disp_probe\n");

    memset(&g_disp_drv, 0, sizeof(struct disp_drv_info));

    /* iomap */
    /* de - [device(tcon-top)] - lcd0/1/2.. - dsi */
    counter = 0;

    g_disp_drv.reg_base[DISP_MOD_DE] = disp_getprop_regbase(FDT_DISP_PATH, counter);
    if (!g_disp_drv.reg_base[DISP_MOD_DE]) {
        DE_WRN("unable to map de registers\n");
        ret = -1;
        goto exit;
    }
    ++counter;

#if defined(CONFIG_INDEPENDENT_DE)
    g_disp_drv.reg_base[DISP_MOD_DE1] = disp_getprop_regbase(FDT_DISP_PATH, counter);
    if (!g_disp_drv.reg_base[DISP_MOD_DE1]) {
        DE_WRN("unable to map de registers\n");
        ret = -1;
        goto exit;
    }
    ++counter;
#endif

#if defined(HAVE_DEVICE_COMMON_MODULE)
    g_disp_drv.reg_base[DISP_MOD_DEVICE] = disp_getprop_regbase(FDT_DISP_PATH, counter);
    if (!g_disp_drv.reg_base[DISP_MOD_DEVICE]) {
        DE_WRN("unable to map device common module registers\n");
        ret = -1;
        goto exit;
    }
    ++counter;
#if defined(CONFIG_INDEPENDENT_DE)
    g_disp_drv.reg_base[DISP_MOD_DEVICE1] = disp_getprop_regbase(FDT_DISP_PATH, counter);
    if (!g_disp_drv.reg_base[DISP_MOD_DEVICE1]) {
        DE_WRN("unable to map device common module registers\n");
        ret = -1;
        goto exit;
    }
    ++counter;
#endif
#endif

    for (i=0; i<DISP_DEVICE_NUM; i++) {
        g_disp_drv.reg_base[DISP_MOD_LCD0 + i] = disp_getprop_regbase(FDT_DISP_PATH, counter);
        if (!g_disp_drv.reg_base[DISP_MOD_LCD0 + i]) {
            DE_WRN("unable to map timing controller %d registers\n", i);
            ret = -1;
            goto exit;
        }
        ++counter;
    }

#if defined(SUPPORT_DSI)
    for (i = 0; i < DEVICE_DSI_NUM; ++i) {
        g_disp_drv.reg_base[DISP_MOD_DSI0 + i] =
            disp_getprop_regbase(FDT_DISP_PATH, counter);
        if (!g_disp_drv.reg_base[DISP_MOD_DSI0 + i]) {
            DE_WRN("unable to map dsi%d registers\n", i);
            ret = -1;
            goto exit;
        }
        ++counter;
    }
#endif

#if defined(SUPPORT_EINK)
        g_disp_drv.reg_base[DISP_MOD_EINK] = disp_getprop_regbase(FDT_DISP_PATH, counter);
        if (!g_disp_drv.reg_base[DISP_MOD_EINK]) {
            DE_WRN("unable to map eink registers\n");
            ret = -1;
            goto exit;
        }
        ++counter;
#endif

    /* parse and map irq */
    /* lcd0/1/2.. - dsi */
    counter = 0;

#ifdef DE_VERSION_V33X
    g_disp_drv.irq_no[DISP_MOD_DE] =
        disp_getprop_irq(FDT_DISP_PATH, counter);
    if (!g_disp_drv.irq_no[DISP_MOD_DE]) {
        DE_WRN("irq_of_parse_and_map de irq fail\n");
    }
    ++counter;
#endif

    for (i=0; i<DISP_DEVICE_NUM; i++) {
        g_disp_drv.irq_no[DISP_MOD_LCD0 + i] = disp_getprop_irq(FDT_DISP_PATH, counter);
        if (!g_disp_drv.irq_no[DISP_MOD_LCD0 + i]) {
            DE_WRN("irq_of_parse_and_map irq %d fail for lcd%d\n", counter, i);
        }
        ++counter;
    }

#if defined(SUPPORT_DSI)
    for (i = 0; i < DEVICE_DSI_NUM; ++i) {
        g_disp_drv.irq_no[DISP_MOD_DSI0 + i] =
            disp_getprop_irq(FDT_DISP_PATH, counter);
        if (!g_disp_drv.irq_no[DISP_MOD_DSI0 + i])
            DE_WRN("irq_of_parse_and_map irq %d fail for dsi\n", i);
        ++counter;
    }
#endif

#if defined(SUPPORT_EINK)
        g_disp_drv.irq_no[DISP_MOD_DE] = disp_getprop_irq(FDT_DISP_PATH, counter);
        if (!g_disp_drv.irq_no[DISP_MOD_DE]) {
            DE_WRN("irq_of_parse_and_map de irq %d fail for dsi\n", counter);
        }
        ++counter;


        g_disp_drv.irq_no[DISP_MOD_EINK] = disp_getprop_irq(FDT_DISP_PATH, counter);
        if (!g_disp_drv.irq_no[DISP_MOD_EINK]) {
            DE_WRN("irq_of_parse_and_map irq %d fail for eink\n", counter);
        }
        ++counter;
#endif

    /* get clk */
    ret = disp_clk_get_wrap(&g_disp_drv);
    if (ret)
        return ret;

    ret = disp_init();

#ifdef CONFIG_STANDBY
    pm = register_pm_dev_notify(disp_suspend, disp_resume, NULL);
#endif

exit:
    return ret;
}

static int disp_blank(bool blank)
{
    u32 screen_id = 0;
    int num_screens;
    struct disp_manager *mgr = NULL;

    num_screens = bsp_disp_feat_get_num_screens();

    for (screen_id = 0; screen_id < num_screens; screen_id++) {
        mgr = g_disp_drv.mgr[screen_id];
        /* Currently remove !mgr->device condition,
         * avoiding problem in the following case:
         *
         *   attach manager and device -> disp blank --> blank success
         *   deattach manager and device -> disp unblank --> fail
         *   (cause don't satisfy !mgr->device condition)
         *   attach manager and device --> problem arises
         *   (manager will be always on unblank state)
         *
         * The scenario is: hdmi plug in -> enter standy
         *  -> hdmi plug out -> exit standby -> hdmi plug in
         *  -> display blank on hdmi screen
         */
        if (!mgr)
            continue;

        if (mgr->blank)
            mgr->blank(mgr, blank);
    }


    return 0;
}

ssize_t disp_sys_show(void)
{
    struct disp_manager *mgr = NULL;
    struct disp_device *dispdev = NULL;
    int num_screens, screen_id;
    int num_layers, layer_id;
    int num_chans, chan_id;
    num_screens = bsp_disp_feat_get_num_screens();
    for (screen_id = 0; screen_id < num_screens; screen_id++) {
        u32 width = 0, height = 0;
        int fps = 0;
        struct disp_health_info info;

        mgr = disp_get_layer_manager(screen_id);
        if (mgr == NULL)
            continue;
        dispdev = mgr->device;
        if (dispdev == NULL)
            continue;
        dispdev->get_resolution(dispdev, &width, &height);
        fps = bsp_disp_get_fps(screen_id);
        bsp_disp_get_health_info(screen_id, &info);

        if (!dispdev->is_enabled(dispdev))
            continue;
        DISP_PRINT("screen %d:\n", screen_id);
        DISP_PRINT("de_rate %8ld hz, ref_fps:%8d\n", (long)mgr->get_clk_rate(mgr),
               (int)dispdev->get_fps(dispdev));
        mgr->dump(mgr);
        /* output */
        if (dispdev->type == DISP_OUTPUT_TYPE_LCD) {
            DISP_PRINT("\tlcd output\tbacklight(%3d)\tfps:%d.%d",
                   (int)dispdev->get_bright(dispdev), fps / 10,
                   fps % 10);
        } else if (dispdev->type == DISP_OUTPUT_TYPE_HDMI) {
            int mode = dispdev->get_mode(dispdev);

            DISP_PRINT("\thdmi output mode(%d)\tfps:%d.%d", mode,
                   fps / 10, fps % 10);
        } else if (dispdev->type == DISP_OUTPUT_TYPE_TV) {
            int mode = dispdev->get_mode(dispdev);

            DISP_PRINT("\ttv output mode(%d)\tfps:%d.%d", mode,
                   fps / 10, fps % 10);
        } else if (dispdev->type == DISP_OUTPUT_TYPE_VGA) {
            int mode = dispdev->get_mode(dispdev);

            DISP_PRINT("\tvga output mode(%d)\tfps:%d.%d", mode,
                   fps / 10, fps % 10);
        } else if (dispdev->type == DISP_OUTPUT_TYPE_VDPO) {
            int mode = dispdev->get_mode(dispdev);

            DISP_PRINT("\tvdpo output mode(%d)\tfps:%d.%d", mode,
                   fps / 10, fps % 10);
        } else if (dispdev->type == DISP_OUTPUT_TYPE_EDP) {
            DISP_PRINT("\tEDP output(%s) \tfps:%d.%d",
                   (dispdev->is_enabled(dispdev) == 1) ? "enable"
                                   : "disable",
                   fps / 10, fps % 10);
        }
        if (dispdev->type != DISP_OUTPUT_TYPE_NONE) {
            DISP_PRINT("\t%4ux%4u\n", (unsigned)width, (unsigned)height);
            DISP_PRINT("\terr:%u\tskip:%u\tirq:%llu\tvsync:%u\tvsync_"
                   "skip:%u\t\n",
                   info.error_cnt, info.skip_cnt, info.irq_cnt,
                   info.vsync_cnt, info.vsync_skip_cnt);
        }

        num_chans = bsp_disp_feat_get_num_channels(screen_id);

        /* layer info */
        for (chan_id = 0; chan_id < num_chans; chan_id++) {
            num_layers = bsp_disp_feat_get_num_layers_by_chn(
                screen_id, chan_id);
            for (layer_id = 0; layer_id < num_layers; layer_id++) {
                struct disp_layer *lyr = NULL;
                struct disp_layer_config config;

                lyr = disp_get_layer(screen_id, chan_id,
                             layer_id);
                config.channel = chan_id;
                config.layer_id = layer_id;
                mgr->get_layer_config(mgr, &config, 1);
                if (lyr && (true == config.enable) && lyr->dump)
                    lyr->dump(lyr);
            }
        }
    }

    return 0;
}

/**
 * @name       :disp_draw_colorbar
 * @brief      :draw colorbar using DE's LAYER MODE
 * @param[IN]  :disp:screen index
 * @return     :0 if success
 */
static int disp_draw_colorbar(u32 disp)
{
    struct disp_manager *mgr = NULL;
    struct disp_layer_config config[4];
    unsigned int i = 0;
    u32 width = 0, height = 0, num_screens;
    int ret = -1;

    num_screens = bsp_disp_feat_get_num_screens();
    if (disp < num_screens)
        mgr = g_disp_drv.mgr[disp];
    else
        return ret;

    if (mgr && mgr->device && mgr->device->get_resolution)
        mgr->device->get_resolution(mgr->device, &width, &height);
    else
        return ret;

    memset(config, 0, 4 * sizeof(struct disp_layer_config));
    for (i = 0; i < 4; ++i) {
        config[i].channel = 0;
        config[i].layer_id = i;
        config[i].enable = 1;
        config[i].info.zorder = 16;
        config[i].info.mode = LAYER_MODE_COLOR;
        config[i].info.fb.format = DISP_FORMAT_ARGB_8888;
        config[i].info.screen_win.width = width / 4;
        config[i].info.screen_win.height = height;
        config[i].info.screen_win.x = (width / 4) * i;
        config[i].info.screen_win.y = 0;
        config[i].info.fb.crop.x =
            ((long long)(config[i].info.screen_win.x) << 32);
        config[i].info.fb.crop.y =
            ((long long)(config[i].info.screen_win.y) << 32);
        config[i].info.fb.crop.width =
            ((long long)(config[i].info.screen_win.width) << 32);
        config[i].info.fb.crop.height =
            ((long long)(config[i].info.screen_win.height) << 32);
    }
    config[0].info.color = 0xffff0000; /*red*/
    config[1].info.color = 0xff00ff00; /*green*/
    config[2].info.color = 0xff0000ff; /*blue*/
    config[3].info.color = 0xffffff00; /*yellow*/

    if (mgr->set_layer_config)
        ret = mgr->set_layer_config(mgr, config, 4);

    return ret;
}


ssize_t disp_colorbar_store(u32 disp, u32 val)
{
    int err;
    unsigned int num_screens;
    struct disp_manager *mgr = NULL;


    num_screens = bsp_disp_feat_get_num_screens();

    if (disp < num_screens)
        mgr = g_disp_drv.mgr[disp];

    if (!mgr) {
        DE_WRN("Null mgr!\n");
        return -1;
    }

    /*val:*/
    /*0:DE-->tcon-->other interface*/
    /*1-7:tcon or edp or other device's builtin patten*/
    /*for tcon:*/
    /*1:color bar*/
    /*2:grayscale check*/
    /*3:black and white check*/
    /*4:all 0*/
    /*5:all 1*/
    /*6:reserve*/
    /*7:Gridding*/
    /*for edp:*/
    /*1:colorbar*/
    /*2:mosaic*/
    if (val == 8) {
        disp_draw_colorbar(disp);
        if (mgr && mgr->device && mgr->device->show_builtin_patten)
            mgr->device->show_builtin_patten(mgr->device, 0);
    } else {
        if (mgr && mgr->device && mgr->device->show_builtin_patten)
            mgr->device->show_builtin_patten(mgr->device, val);
    }

    return 0;
}

ssize_t disp_capture_dump(u32 disp, const char *image_name)
{
    FILE *pfile;
    void *buf_addr_vir = NULL;
    unsigned long phy_addr = 0;
    struct disp_capture_info cptr_info;
    u32 size = 0, width = 0, height = 0, num_screens = 0;
    struct disp_manager *mgr = NULL;
    int ret = -1, cs = DISP_CSC_TYPE_RGB;
    struct bmp_header bmp_header;
    size_t write_size = 0;

    num_screens = bsp_disp_feat_get_num_screens();

    DE_WRN("Capturing screen%d to %s\n", disp, image_name);

    if (disp < num_screens)
        mgr = g_disp_drv.mgr[disp];

    if (!mgr || !mgr->device || !mgr->cptr)
        goto OUT;

    memset(&cptr_info, 0, sizeof(struct disp_capture_info));


    pfile = fopen(image_name, "w+");
    if (!pfile) {
        DE_WRN("%s, open %s err\n", __func__, image_name);
        goto OUT;
    }

    if (mgr->device->get_resolution)
        ret = mgr->device->get_resolution(mgr->device, &width, &height);
    if (ret) {
        DE_WRN("Get resolution fail!\n");
        goto FILE_CLOSE;
    }

    cptr_info.out_frame.size[0].width = width;
    cptr_info.out_frame.size[0].height = height;
    cptr_info.window.width = width;
    cptr_info.window.height = height;
    cptr_info.out_frame.crop.width = width;
    cptr_info.out_frame.crop.height = height;
    if (strstr(image_name, ".bmp"))
        cptr_info.out_frame.format = DISP_FORMAT_ARGB_8888;
    else if (strstr(image_name, ".yuv420_p"))
        cptr_info.out_frame.format = DISP_FORMAT_YUV420_P;
    else if (strstr(image_name, ".yuv420_sp_uvuv"))
        cptr_info.out_frame.format = DISP_FORMAT_YUV420_SP_UVUV;
    else if (strstr(image_name, ".yuv420_sp_vuvu"))
        cptr_info.out_frame.format = DISP_FORMAT_YUV420_SP_VUVU;
    else if (strstr(image_name, ".argb8888"))
        cptr_info.out_frame.format = DISP_FORMAT_ARGB_8888;
    else if (strstr(image_name, ".abgr8888"))
        cptr_info.out_frame.format = DISP_FORMAT_ABGR_8888;
    else if (strstr(image_name, ".rgb888"))
        cptr_info.out_frame.format = DISP_FORMAT_RGB_888;
    else if (strstr(image_name, ".bgr888"))
        cptr_info.out_frame.format = DISP_FORMAT_BGR_888;
    else if (strstr(image_name, ".rgba8888"))
        cptr_info.out_frame.format = DISP_FORMAT_RGBA_8888;
    else if (strstr(image_name, ".bgra8888"))
        cptr_info.out_frame.format = DISP_FORMAT_BGRA_8888;
    else {
        if (mgr->device->get_input_csc)
            cs = mgr->device->get_input_csc(mgr->device);
        if (cs == DISP_CSC_TYPE_RGB)
            cptr_info.out_frame.format = DISP_FORMAT_ARGB_8888;
        else
            cptr_info.out_frame.format = DISP_FORMAT_YUV420_P;
    }

    size = width * height * 4;

    buf_addr_vir = disp_dma_malloc(size, (void *)&phy_addr);
    if (!phy_addr || !buf_addr_vir) {
        DE_WRN("%s, disp_dma_malloc phy_addr err\n", __func__);
        goto FILE_CLOSE;
    }

    cptr_info.out_frame.addr[0] = (unsigned long)phy_addr;
    cptr_info.out_frame.addr[1] =
        cptr_info.out_frame.addr[0] + width * height;
    cptr_info.out_frame.addr[2] =
        cptr_info.out_frame.addr[1] + width * height / 4;

    ret = mgr->cptr->start(mgr->cptr);
    if (ret) {
        DE_WRN("Capture start fail!\n");
        mgr->cptr->stop(mgr->cptr);
        goto FREE_DMA;
    }

    ret = mgr->cptr->commmit(mgr->cptr, &cptr_info);
    if (ret) {
        DE_WRN("Capture commit fail!\n");
        mgr->cptr->stop(mgr->cptr);
        goto FREE_DMA;
    }
    disp_delay_ms(1000);
    ret = mgr->cptr->stop(mgr->cptr);
    if (ret) {
        DE_WRN("Capture stop fail!\n");
        goto FREE_DMA;
    }

    if (strstr(image_name, ".bmp")) {
        memset(&bmp_header, 0, sizeof(struct bmp_header));
        bmp_header.signature[0] = 'B';
        bmp_header.signature[1] = 'M';
        bmp_header.data_offset = sizeof(struct bmp_header);
        bmp_header.file_size = bmp_header.data_offset + size;
        bmp_header.size = sizeof(struct bmp_header) - 14;
        bmp_header.width = width;
        bmp_header.height = -height;
        bmp_header.planes = 1;
        bmp_header.bit_count = 32;
        bmp_header.image_size = size;
        write_size = fwrite(&bmp_header,
                   sizeof(struct bmp_header), 1,  pfile);
        if (write_size != 1) {
            DE_WRN("fwrite fail!\n");
            goto FREE_DMA;
        }
    }

    write_size = fwrite(buf_addr_vir, size, 1, pfile);
    if (write_size != 1) {
        DE_WRN("fwrite fail!\n");
        goto FREE_DMA;
    }
    DE_WRN("Capture dump done!!!\n");

FREE_DMA:
    disp_dma_free((void *)buf_addr_vir, (void *)phy_addr, size);
FILE_CLOSE:
    fclose(pfile);
OUT:
    return 0;
}

int disp_ioctl(int cmd, void *arg)
{
    unsigned long *ubuffer = arg;
    s32 ret = 0;
    int num_screens = 2;
    struct disp_manager *mgr = NULL;
    struct disp_device *dispdev = NULL;
    struct disp_enhance *enhance = NULL;
    struct disp_smbl *smbl = NULL;
    struct disp_capture *cptr = NULL;
#if defined(SUPPORT_EINK)
    struct disp_eink_manager *eink_manager = NULL;
#endif
    char enhance_buf[20] = {0};
    num_screens = bsp_disp_feat_get_num_screens();

    if (ubuffer[0] < num_screens)
        mgr = g_disp_drv.mgr[ubuffer[0]];
    if (mgr) {
        dispdev = mgr->device;
        enhance = mgr->enhance;
        smbl = mgr->smbl;
        cptr = mgr->cptr;
    }

#if defined(SUPPORT_EINK)
    eink_manager = g_disp_drv.eink_manager[0];

    if (!eink_manager)
        DE_WRN("eink_manager is NULL!\n");
#endif

    if (cmd < DISP_FB_REQUEST) {
        if (ubuffer[0] >= num_screens) {
            DE_WRN
                ("para err, cmd = 0x%x,screen id = %d\n",
                 cmd, (int)ubuffer[0]);
            return -1;
        }
    }

    if (cmd == DISP_print)
        DE_WRN("cmd:0x%x,%ld,%ld\n", cmd, ubuffer[0], ubuffer[1]);

    switch (cmd) {
        /* ----disp global---- */
    case DISP_SET_BKCOLOR:
        {
            struct disp_color para;

            memcpy(&para, (void *)ubuffer[1], sizeof(struct disp_color));

            if (mgr && (mgr->set_back_color != NULL))
                ret = mgr->set_back_color(mgr, &para);
            break;
        }

    case DISP_GET_OUTPUT_TYPE:
        {
            if (suspend_status != DISPLAY_NORMAL)
                ret = suspend_output_type[ubuffer[0]];
            else
                ret = bsp_disp_get_output_type(ubuffer[0]);

            break;
        }

    case DISP_GET_SCN_WIDTH:
        {
            u32 width = 0, height = 0;

            if (mgr && mgr->device && mgr->device->get_resolution)
                mgr->device->get_resolution(mgr->device, &width,
                                &height);
            ret = width;
            break;
        }

    case DISP_GET_SCN_HEIGHT:
        {
            u32 width = 0, height = 0;

            if (mgr && mgr->device && mgr->device->get_resolution)
                mgr->device->get_resolution(mgr->device, &width,
                                &height);
            ret = height;
            break;
        }

    case DISP_VSYNC_EVENT_EN:
        {
            ret =
                bsp_disp_vsync_event_enable(ubuffer[0], ubuffer[1]);
            break;
        }

    case DISP_SHADOW_PROTECT:
        {
            ret = bsp_disp_shadow_protect(ubuffer[0], ubuffer[1]);
            break;
        }

    case DISP_BLANK:
        {
            /* only response main device' blank request */

            if (!g_pm_runtime_enable)
                break;

            if (ubuffer[0] != 0)
                break;

            if (ubuffer[1]) {
#ifdef CONFIG_ARCH_SUN50IW6
            bsp_disp_hdmi_cec_standby_request();
#endif
                suspend_status |= DISPLAY_BLANK;
                disp_blank(true);
            } else {
                if (power_status_init) {
                    /* avoid first unblank */
                    power_status_init = 0;
                    break;
                }

                disp_blank(false);
                suspend_status &= ~DISPLAY_BLANK;
            }
            break;
        }

    case DISP_DEVICE_SWITCH:
        {
            /* if the display device has already enter blank status,
             * DISP_DEVICE_SWITCH request will not be responsed.
             */
            if (!(suspend_status & DISPLAY_BLANK))
                ret =
                    bsp_disp_device_switch(ubuffer[0],
                       (enum disp_output_type)ubuffer[1],
                       (enum disp_output_type)ubuffer[2]);
            suspend_output_type[ubuffer[0]] = ubuffer[1];
#if defined(SUPPORT_TV) && defined(CONFIG_ARCH_SUN50IW2P1)
            bsp_disp_tv_set_hpd(1);
#endif
        break;
    }

    case DISP_DEVICE_SET_CONFIG:
    {
        struct disp_device_config config;

        memcpy(&config, (void *)ubuffer[1], sizeof(struct disp_device_config));
        suspend_output_type[ubuffer[0]] = config.type;

        ret = bsp_disp_device_set_config(ubuffer[0], &config);
        break;
    }

    case DISP_DEVICE_GET_CONFIG:
    {
        struct disp_device_config config;

        if (mgr && dispdev)
            dispdev->get_static_config(dispdev, &config);
        else
            ret = -1;

        if (ret == 0) {
            memcpy((void *)ubuffer[1], &config,
                   sizeof(struct disp_device_config));
        }
        break;
    }
#if defined(SUPPORT_EINK)

    case DISP_EINK_UPDATE:
        {
            s32 i = 0;
            struct area_info area;

            if (!eink_manager) {
                pr_err("there is no eink manager!\n");
                break;
            }

            memset(lyr_cfg, 0,
                   16 * sizeof(struct disp_layer_config));
            memcpy(lyr_cfg, (void *)ubuffer[3],
                   sizeof(struct disp_layer_config) * ubuffer[1]);

            memset(&area, 0, sizeof(struct area_info));
            memcpy(&area, (void *)ubuffer[0],
                   sizeof(struct area_info));

            for (i = 0; i < ubuffer[1]; i++)
                __disp_config_transfer2inner(&eink_para[i],
                                &lyr_cfg[i]);

            ret = bsp_disp_eink_update(eink_manager,
                (struct disp_layer_config_inner *)&eink_para[0],
                (unsigned int)ubuffer[1],
                (enum eink_update_mode)ubuffer[2], &area);
            break;
        }

    case DISP_EINK_UPDATE2:
        {
            s32 i = 0;
            struct area_info area;

            if (!eink_manager) {
                pr_err("there is no eink manager!\n");
                break;
            }

            memset(lyr_cfg2, 0,
                   16 * sizeof(struct disp_layer_config2));
            memcpy(lyr_cfg2, (void *)ubuffer[3],
                   sizeof(struct disp_layer_config2) * ubuffer[1]);

            memset(&area, 0, sizeof(struct area_info));
            memcpy(&area, (void *)ubuffer[1],
                   sizeof(struct area_info));

            for (i = 0; i < ubuffer[1]; i++)
                __disp_config2_transfer2inner(&eink_para[i],
                                &lyr_cfg2[i]);

            ret = bsp_disp_eink_update(eink_manager,
                (struct disp_layer_config_inner *)&eink_para[0],
                (unsigned int)ubuffer[1],
                (enum eink_update_mode)ubuffer[2], &area);
            break;
        }

    case DISP_EINK_SET_TEMP:
        {
            ret =
                bsp_disp_eink_set_temperature(eink_manager,
                              ubuffer[0]);
            break;
        }
    case DISP_EINK_GET_TEMP:
        {
            ret = bsp_disp_eink_get_temperature(eink_manager);
            break;
        }
    case DISP_EINK_OVERLAP_SKIP:
        {
            ret = bsp_disp_eink_op_skip(eink_manager, ubuffer[0]);
            break;
        }
#endif

    case DISP_GET_OUTPUT:
        {
            struct disp_output para;

            memset(&para, 0, sizeof(struct disp_output));

            if (mgr && mgr->device) {
                para.type =
                    bsp_disp_get_output_type(ubuffer[0]);
                if (mgr->device->get_mode)
                    para.mode =
                        mgr->device->get_mode(mgr->device);
            }

            memcpy((void *)ubuffer[1], &para, sizeof(struct disp_output));
            break;
        }

    case DISP_SET_COLOR_RANGE:
        {
            if (mgr && mgr->set_output_color_range)
                ret =
                    mgr->set_output_color_range(mgr,
                                ubuffer[1]);

            break;
        }

    case DISP_GET_COLOR_RANGE:
        {
            if (mgr && mgr->get_output_color_range)
                ret = mgr->get_output_color_range(mgr);

            break;
        }

        /* ----layer---- */
    case DISP_LAYER_SET_CONFIG:
    {
        unsigned int i = 0;
        const unsigned int lyr_cfg_size = ARRAY_SIZE(lyr_cfg);

        disp_sys_mutex_lock(&g_disp_drv.mlock);

        if (ubuffer[2] > lyr_cfg_size) {
            DE_WRN("Total layer number is %d\n", lyr_cfg_size);
            disp_sys_mutex_unlock(&g_disp_drv.mlock);
            return -1;
        }

        memcpy(lyr_cfg, (void *)ubuffer[1],
               sizeof(struct disp_layer_config) * ubuffer[2]);

        for (i = 0; (i < lyr_cfg_size) && (i < ubuffer[2]); ++i) {
            if (lyr_cfg[i].enable == 0) {
                memset(&(lyr_cfg[i].info), 0,
                    sizeof(lyr_cfg[i].info));
            }
        }

#if !defined(CONFIG_EINK_PANEL_USED)
        if (mgr && mgr->set_layer_config)
            ret = mgr->set_layer_config(mgr, lyr_cfg, ubuffer[2]);
#endif
        disp_sys_mutex_unlock(&g_disp_drv.mlock);
        break;
    }

    case DISP_LAYER_GET_CONFIG:
    {
        memcpy(lyr_cfg, (void *)ubuffer[1],
               sizeof(struct disp_layer_config) * ubuffer[2]);
        if (mgr && mgr->get_layer_config)
            ret = mgr->get_layer_config(mgr, lyr_cfg, ubuffer[2]);
        memcpy((void *)ubuffer[1], lyr_cfg,
               sizeof(struct disp_layer_config) * ubuffer[2]);
        break;
    }

    case DISP_LAYER_SET_CONFIG2:
    {
        struct disp_layer_config2 *pLyr_cfg2;
        unsigned int i = 0;
        const unsigned int lyr_cfg_size =
            ARRAY_SIZE(lyr_cfg2);

        /* adapt to multi thread call in case of disp 0 & 1 work together*/
        if (ubuffer[0] == 0)
            pLyr_cfg2 = lyr_cfg2;
        else
            pLyr_cfg2 = lyr_cfg2_1;

        memcpy(pLyr_cfg2, (void *)ubuffer[1],
               sizeof(struct disp_layer_config2) * ubuffer[2]);

        for (i = 0; (i < lyr_cfg_size) && (i < ubuffer[2]); ++i) {
            if (pLyr_cfg2[i].enable == 0) {
                memset(&(pLyr_cfg2[i].info), 0,
                    sizeof(pLyr_cfg2[i].info));
            }
        }

#if !defined(CONFIG_EINK_PANEL_USED)
        if (mgr && mgr->set_layer_config2)
            ret = mgr->set_layer_config2(mgr, pLyr_cfg2, ubuffer[2]);
#endif
        break;
    }

    case DISP_LAYER_GET_CONFIG2:
    {
        memcpy(lyr_cfg2, (void *)ubuffer[1],
               sizeof(struct disp_layer_config2) * ubuffer[2]);
        if (mgr && mgr->get_layer_config2)
            ret = mgr->get_layer_config2(mgr, lyr_cfg2, ubuffer[2]);

        memcpy((void *)ubuffer[1], lyr_cfg2,
               sizeof(struct disp_layer_config2) * ubuffer[2]);
        break;
    }
        /* ---- lcd --- */
    case DISP_LCD_SET_BRIGHTNESS:
        {
            if (dispdev && dispdev->set_bright)
                ret = dispdev->set_bright(dispdev, ubuffer[1]);
            break;
        }

    case DISP_LCD_GET_BRIGHTNESS:
        {
            if (dispdev && dispdev->get_bright)
                ret = dispdev->get_bright(dispdev);
            break;
        }
    case DISP_TV_SET_GAMMA_TABLE:
    {
        if (dispdev && (DISP_OUTPUT_TYPE_TV == dispdev->type)) {
            u32 *gamma_tbl = disp_sys_malloc(LCD_GAMMA_TABLE_SIZE);
            u32 size = ubuffer[2];

            if (gamma_tbl == NULL) {
                DE_WRN("kmalloc fail\n");
                ret = -1;
                break;
            }

            size = (size > LCD_GAMMA_TABLE_SIZE) ?
                LCD_GAMMA_TABLE_SIZE : size;
            memcpy(gamma_tbl, (void *)ubuffer[1], size);

            if (dispdev->set_gamma_tbl)
                ret = dispdev->set_gamma_tbl(dispdev, gamma_tbl,
                                 size);
            disp_sys_free(gamma_tbl);
        }
        break;
    }

    case DISP_LCD_GAMMA_CORRECTION_ENABLE:
        {
            if (dispdev &&
                (dispdev->type == DISP_OUTPUT_TYPE_LCD)) {
                ret = dispdev->enable_gamma(dispdev);
            }
            break;
        }

    case DISP_LCD_GAMMA_CORRECTION_DISABLE:
    {
        if (dispdev && (dispdev->type == DISP_OUTPUT_TYPE_LCD))
            ret = dispdev->disable_gamma(dispdev);
        break;
    }

    case DISP_LCD_SET_GAMMA_TABLE:
    {
        if (dispdev && (dispdev->type == DISP_OUTPUT_TYPE_LCD)) {
            u32 *gamma_tbl = disp_sys_malloc(LCD_GAMMA_TABLE_SIZE);
            u32 size = ubuffer[2];

            if (gamma_tbl == NULL) {
                DE_WRN("kmalloc fail\n");
                ret = -1;
                break;
            }

            size = (size > LCD_GAMMA_TABLE_SIZE) ?
                LCD_GAMMA_TABLE_SIZE : size;
            memcpy(gamma_tbl, (void *)ubuffer[1], size);
            ret = dispdev->set_gamma_tbl(dispdev, gamma_tbl, size);
            disp_sys_free(gamma_tbl);
        }
        break;
    }


        /* ---- hdmi --- */
    case DISP_HDMI_SUPPORT_MODE:
        {
            ret =
                bsp_disp_hdmi_check_support_mode(ubuffer[0],
                                 ubuffer[1]);
            break;
        }

    case DISP_SET_TV_HPD:
        {
            ret = bsp_disp_tv_set_hpd(ubuffer[0]);
            break;
        }
#ifdef CONFIG_ARCH_SUN50IW6
    case DISP_CEC_ONE_TOUCH_PLAY:
    {
        ret = bsp_disp_hdmi_cec_send_one_touch_play();
        break;
    }
#endif
        /* ----enhance---- */
    case DISP_ENHANCE_ENABLE:
        {
            if (enhance && enhance->enable)
                ret = enhance->enable(enhance);
            break;
        }

    case DISP_ENHANCE_DISABLE:
        {
            if (enhance && enhance->disable)
                ret = enhance->disable(enhance);
            break;
        }

    case DISP_ENHANCE_DEMO_ENABLE:
        {
            if (enhance && enhance->demo_enable)
                ret = enhance->demo_enable(enhance);
            break;
        }

    case DISP_ENHANCE_DEMO_DISABLE:
        {
            if (enhance && enhance->demo_disable)
                ret = enhance->demo_disable(enhance);
            break;
        }

    case DISP_ENHANCE_SET_MODE:
        {
            if (enhance && enhance->set_mode)
                ret = enhance->set_mode(enhance, ubuffer[1]);
            break;
        }

    case DISP_ENHANCE_GET_MODE:
        {
            if (enhance && enhance->get_mode)
                ret = enhance->get_mode(enhance);
            break;
        }

    case DISP_ENHANCE_SET_BRIGHT:
        {
            ret = disp_enhance_bright_store(ubuffer[0], ubuffer[1]);
            break;
        }

    case DISP_ENHANCE_GET_BRIGHT:
        {
            ret = disp_enhance_bright_show(ubuffer[0], enhance_buf);
            break;
        }

    case DISP_ENHANCE_SET_CONTRAST:
        {
            ret = disp_enhance_contrast_store(ubuffer[0], ubuffer[1]);
            break;
        }

    case DISP_ENHANCE_GET_CONTRAST:
        {
            ret = disp_enhance_contrast_show(ubuffer[0], enhance_buf);
            break;
        }

    case DISP_ENHANCE_SET_SATURATION:
        {
            ret = disp_enhance_saturation_store(ubuffer[0], ubuffer[1]);
            break;
        }

    case DISP_ENHANCE_GET_SATURATION:
        {
            ret = disp_enhance_saturation_show(ubuffer[0], enhance_buf);
            break;
        }

        /* ---smart backlight -- */
    case DISP_SMBL_ENABLE:
        {
            if (smbl && smbl->enable)
                ret = smbl->enable(smbl);
            break;
        }

    case DISP_SMBL_DISABLE:
        {
            if (smbl && smbl->disable)
                ret = smbl->disable(smbl);
            break;
        }

    case DISP_SMBL_SET_WINDOW:
        {
            struct disp_rect rect;

            memcpy(&rect, (void *)ubuffer[1], sizeof(struct disp_rect));
            if (smbl && smbl->set_window)
                ret = smbl->set_window(smbl, &rect);
            break;
        }

        /* ---capture -- */
    case DISP_CAPTURE_START:
        {
            if (cptr && cptr->start)
                ret = cptr->start(cptr);
            break;
        }

    case DISP_CAPTURE_STOP:
        {
            if (cptr && cptr->stop)
                ret = cptr->stop(cptr);
            break;
        }

    case DISP_CAPTURE_COMMIT:
        {
            struct disp_capture_info info;

            memcpy(&info, (void *)ubuffer[1],
                   sizeof(struct disp_capture_info));
            if (cptr && cptr->commmit)
                ret = cptr->commmit(cptr, &info);
            break;
        }

        /* ----for test---- */
#if defined(SUPPORT_VDPO)
    case DISP_VDPO_SET_CONFIG:
        {
            struct disp_vdpo_config vdpo_para;

            memcpy(&vdpo_para, (void *)ubuffer[1],
                   sizeof(struct disp_vdpo_config) * ubuffer[2]);
            if (mgr && mgr->device)
                disp_vdpo_set_config(mgr->device, &vdpo_para);
            break;
        }
#endif /*endif SUPPORT_VDPO*/

#if defined(CONFIG_SUNXI_DISP2_FB_ROTATION_SUPPORT)
    case DISP_ROTATION_SW_SET_ROT:
        {
            int num_screens = bsp_disp_feat_get_num_screens();
            u32 degree, chn, lyr_id;

            disp_sys_mutex_lock(&g_disp_drv.mlock);
            if (mgr == NULL) {
                DE_WRN("mgr is null\n");
            }
            if (mgr->rot_sw == NULL) {
                DE_WRN("mgr->rot_sw is null\n");
            }
            if (!mgr || !mgr->rot_sw || num_screens <= ubuffer[0]) {
                ret = -1;
                disp_sys_mutex_unlock(&g_disp_drv.mlock);
                break;
            }
            degree = ubuffer[3];
            switch (degree) {
            case ROTATION_SW_0:
            case ROTATION_SW_90:
            case ROTATION_SW_180:
            case ROTATION_SW_270:
                chn = ubuffer[1];
                lyr_id = ubuffer[2];
                ret = mgr->rot_sw->set_layer_degree(mgr->rot_sw, chn, lyr_id, degree);
                break;
            default:
                ret = -1;
            }
            disp_sys_mutex_unlock(&g_disp_drv.mlock);
            break;
        }

    case DISP_ROTATION_SW_GET_ROT:
        {
            int num_screens = bsp_disp_feat_get_num_screens();
            u32 chn, lyr_id;
            disp_sys_mutex_lock(&g_disp_drv.mlock);
            if (mgr && mgr->rot_sw && num_screens > ubuffer[0]) {
                chn = ubuffer[1];
                lyr_id = ubuffer[2];
                ret = mgr->rot_sw->get_layer_degree(mgr->rot_sw, chn, lyr_id);
            } else {
                ret = -1;
            }
            disp_sys_mutex_unlock(&g_disp_drv.mlock);
            break;
        }
#endif

    case DISP_LCD_CHECK_OPEN_FINISH:
        {
            if (mgr && mgr->device) {
                if (mgr->device->is_enabled)
                    return mgr->device->is_enabled(mgr->device);
                else
                    return -1;
            } else
                    return -1;
        }

    case DISP_LCD_BACKLIGHT_ENABLE:
        {
            if (mgr && mgr->device) {
                if (mgr->device->pwm_enable)
                    mgr->device->pwm_enable(mgr->device);
                if (mgr->device->backlight_enable)
                    mgr->device->backlight_enable(mgr->device);

                return 0;
            }
            return -1;
            break;
        }
    case DISP_LCD_BACKLIGHT_DISABLE:
        {
            if (mgr && mgr->device) {
                if (mgr->device->pwm_disable)
                    mgr->device->pwm_disable(mgr->device);
                if (mgr->device->backlight_disable)
                    mgr->device->backlight_disable(mgr->device);
                return 0;
            }
            return -1;
            break;
        }

    default:
        DE_WRN("Unknown cmd 0x%x\n", cmd);
        break;
    }
    return ret;
}

int disp_release(void)
{
#if 0
    int num_screens = 0, i = 0, j = 0;
    struct disp_manager *mgr = NULL;

    memset(lyr_cfg, 0, 16*sizeof(struct disp_layer_config));

    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            lyr_cfg[i + j].enable = false;
            lyr_cfg[i + j].channel = i;
            lyr_cfg[i + j].layer_id = j;
        }
    }
    num_screens = bsp_disp_feat_get_num_screens();
    for (i = 0; i < num_screens; ++i) {
        mgr = g_disp_drv.mgr[i];
        if (mgr && mgr->device) {
            if (mgr->device->disable && mgr->device->is_enabled) {
                if (mgr->device->is_enabled(mgr->device)) {
                    mgr->set_layer_config(mgr, lyr_cfg, 16);
                    disp_delay_ms(20);
                    mgr->device->disable(mgr->device);
                }
            }
        }
    }
#endif
    return 0;
}

int disp_open(void)
{
    return 0;
}

