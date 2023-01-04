/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __DEV_DISP_H__
#define __DEV_DISP_H__

#include "de/include.h"
#include "de/bsp_display.h"
#include "de/disp_display.h"
#include "de/disp_manager.h"

enum disp_standby_flags {
    DISPLAY_NORMAL = 0,
    DISPLAY_LIGHT_SLEEP = 1,
    DISPLAY_DEEP_SLEEP = 2,
    DISPLAY_BLANK = 4,
};


struct disp_init_para {
    bool b_init;
    enum disp_init_mode disp_mode;

    /* for screen0/1/2 */
    enum disp_output_type output_type[8];
    unsigned int output_mode[8];
    enum disp_csc_type      output_format[DISP_SCREEN_NUM];
    enum disp_data_bits     output_bits[DISP_SCREEN_NUM];
    enum disp_eotf          output_eotf[DISP_SCREEN_NUM];
    enum disp_color_space   output_cs[DISP_SCREEN_NUM];
    enum disp_dvi_hdmi      output_dvi_hdmi[DISP_SCREEN_NUM];
    enum disp_color_range   output_range[DISP_SCREEN_NUM];
    enum disp_scan_info     output_scan[DISP_SCREEN_NUM];
    unsigned int            output_aspect_ratio[DISP_SCREEN_NUM];
    bool using_device_config[DISP_SCREEN_NUM];
    unsigned int            reserve1;
    unsigned int            reserve2;

    /* for fb0/1/2 */
    unsigned int buffer_num[DISP_SCREEN_NUM];
    enum disp_pixel_format format[DISP_SCREEN_NUM];
    unsigned int fb_width[DISP_SCREEN_NUM];
    unsigned int fb_height[DISP_SCREEN_NUM];

    unsigned int chn_cfg_mode;
};


struct disp_drv_info {
    struct device *dev;
    uintptr_t reg_base[DISP_MOD_NUM];
    u32 irq_no[DISP_MOD_NUM];

    hal_clk_id_t clk_de[DE_NUM];
    hal_clk_id_t clk_bus_de[DE_NUM];
    hal_clk_id_t clk_bus_dpss_top[DISP_DEVICE_NUM];
    hal_clk_id_t clk_tcon_lcd[DISP_DEVICE_NUM];
    hal_clk_id_t clk_bus_tcon_lcd[DISP_DEVICE_NUM];

#if defined(SUPPORT_DSI)
    hal_clk_id_t clk_mipi_dsi[CLK_DSI_NUM];
    hal_clk_id_t clk_bus_mipi_dsi[CLK_DSI_NUM];
#endif

    struct disp_init_para disp_init;
    struct disp_manager *mgr[DISP_SCREEN_NUM];
    hal_sem_t mlock;
    hal_work start_work;

    u32 exit_mode;      /* 0:clean all  1:disable interrupt */
    bool b_lcd_enabled[DISP_SCREEN_NUM];
    bool inited;        /* indicate driver if init */
    struct disp_bsp_init_para para;
};

struct sunxi_disp_mod {
    enum disp_mod_id id;
    char name[32];
};

struct __fb_addr_para {
    uintptr_t fb_paddr;
    int fb_size;
};

struct bmp_color_table_entry {
    u8 blue;
    u8 green;
    u8 red;
    u8 reserved;
} __packed;

struct lzma_header {
    char signature[4];
    u32 file_size;
    u32 original_file_size;
};

struct bmp_header {
    /* Header */
    char signature[2];
    u32 file_size;
    u32 reserved;
    u32 data_offset;
    /* InfoHeader */
    u32 size;
    u32 width;
    u32 height;
    u16 planes;
    u16 bit_count;
    u32 compression;
    u32 image_size;
    u32 x_pixels_per_m;
    u32 y_pixels_per_m;
    u32 colors_used;
    u32 colors_important;
    /* ColorTable */
} __packed;

struct bmp_pad_header {
    char data[2];       /* pading 2 byte */
    char signature[2];
    u32 file_size;
    u32 reserved;
    u32 data_offset;
    /* InfoHeader */
    u32 size;
    u32 width;
    u32 height;
    u16 planes;
    u16 bit_count;
    u32 compression;
    u32 image_size;
    u32 x_pixels_per_m;
    u32 y_pixels_per_m;
    u32 colors_used;
    u32 colors_important;
} __packed;

struct bmp_image {
    struct bmp_header header;
    /*
     * We use a zero sized array just as a placeholder for variable
     * sized array
     */
    struct bmp_color_table_entry color_table[0];
};

struct sunxi_bmp_store {
    int x;
    int y;
    int bit;
    void *buffer;
};

void disp_set_suspend_output_type(u8 disp, u8 output_type);

int disp_suspend(void *para);
int disp_resume(void *para);
s32 disp_create_heap(u32 pHeapHead, u32 pHeapHeadPhy, u32 nHeapSize);
void *disp_malloc(u32 num_bytes, void *phy_addr);
void disp_free(void *virt_addr, void *phy_addr, u32 num_bytes);

extern s32 disp_register_sync_proc(void (*proc) (u32));
extern s32 disp_unregister_sync_proc(void (*proc) (u32));
extern s32 disp_register_sync_finish_proc(void (*proc) (u32));
extern s32 disp_unregister_sync_finish_proc(void (*proc) (u32));
extern s32 disp_register_ioctl_func(unsigned int cmd,
                    int (*proc)(unsigned int cmd,
                         unsigned long arg));
extern s32 disp_unregister_ioctl_func(unsigned int cmd);
extern s32 disp_register_compat_ioctl_func(unsigned int cmd,
                       int (*proc)(unsigned int cmd,
                            unsigned long arg));
extern s32 disp_unregister_compat_ioctl_func(unsigned int cmd);
extern s32 disp_register_standby_func(int (*suspend) (void),
                      int (*resume)(void));
extern s32 disp_unregister_standby_func(int (*suspend) (void),
                    int (*resume)(void));
extern s32 composer_init(struct disp_drv_info *psg_disp_drv);
extern unsigned int composer_dump(char *buf);
extern s32 disp_tv_register(struct disp_tv_func *func);
extern s32 disp_set_hdmi_detect(bool hpd);
s32 disp_set_edp_func(struct disp_tv_func *func);

extern struct disp_drv_info g_disp_drv;

extern int sunxi_disp_get_source_ops(struct sunxi_disp_source_ops *src_ops);
extern s32 disp_lcd_open(u32 sel);
extern s32 disp_lcd_close(u32 sel);
extern s32 fb_exit(void);
extern unsigned long fb_get_address_info(u32 fb_id, u32 phy_virt_flag);
extern int lcd_init(void);

s32 disp_set_hdmi_func(struct disp_device_func *func);
s32 disp_set_vdpo_func(struct disp_tv_func *func);
s32 sunxi_get_fb_addr_para(struct __fb_addr_para *fb_addr_para);
s32 drv_disp_vsync_event(u32 sel);
void DRV_disp_int_process(u32 sel);
s32 Display_set_fb_timming(u32 sel);
unsigned int disp_boot_para_parse(const char *name);
const char *disp_boot_para_parse_str(const char *name);
int disp_get_parameter_for_cmdlind(char *cmdline, char *name, char *value);
extern s32 bsp_disp_shadow_protect(u32 disp, bool protect);
extern int disp_attr_node_init(void);
extern int capture_module_init(void);
extern void capture_module_exit(void);
ssize_t disp_sys_show(void);
ssize_t disp_colorbar_store(u32 disp, u32 val);
ssize_t disp_capture_dump(u32 disp, const char *image_name);

int disp_enhance_mode_store(u32 disp, u32 value);
int disp_enhance_saturation_store(u32 disp, u32 value);
int disp_enhance_bright_store(u32 disp, u32 value);
int disp_enhance_contrast_store(u32 disp, u32 value);
int disp_color_temperature_store(u32 disp, s32 value);
int disp_enhance_denoise_store(u32 disp, u32 value);
int disp_enhance_detail_store(u32 disp, u32 value);

int disp_enhance_mode_show(u32 disp, char *buf);
int disp_enhance_saturation_show(u32 disp, char *buf);
int disp_enhance_bright_show(u32 disp, char *buf);
int disp_enhance_contrast_show(u32 disp, char *buf);
int disp_color_temperature_show(u32 disp, char *buf);
int disp_enhance_denoise_show(u32 disp, char *buf);
int disp_enhance_detail_show(u32 disp, char *buf);


#endif
