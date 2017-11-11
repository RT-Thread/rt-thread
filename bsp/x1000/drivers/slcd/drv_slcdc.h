/*
 * File      : drv_slcdc.h
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017Äê3ÔÂ21ÈÕ     Urey         the first version
 */
#ifndef _DRV_SLCDC_H_
#define _DRV_SLCDC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//#define CONFIG_SLCDC_CONTINUA
#define SLCDC_USING_DUAL_BUFFER
#define CONFIG_SLCDC_USE_TE

#define FB_BASE            0x80200000

#ifndef FB_PAGE_SIZE
#  define FB_PAGE_SIZE    4096
#endif

/* SLCDC reg ops */
#define slcd_reg_write(addr,config)      writel(config,addr)
#define slcd_reg_read(addr)              readl(addr)


struct slcdc_dma_descriptor
{
    uint32_t fdadr;       /* Frame descriptor address register */
    uint32_t fsadr;       /* Frame source address register */
    uint32_t fidr;        /* Frame ID register */
    uint32_t ldcmd;       /* Command register */
    uint32_t offsize;     /* Stride Offsize(in word) */
    uint32_t page_width;  /* Stride Pagewidth(in word) */
    uint32_t cmd_num;     /* Command Number(for SLCD) */
    uint32_t desc_size;   /* Foreground Size */
};

/* smart lcd interface_type */
enum smart_lcd_type {
    SMART_LCD_TYPE_PARALLEL,
    SMART_LCD_TYPE_SERIAL,
};

/* smart lcd command width */
enum smart_lcd_cwidth {
    SMART_LCD_CWIDTH_16_BIT_ONCE = (0 << 8),
    SMART_LCD_CWIDTH_9_BIT_ONCE = SMART_LCD_CWIDTH_16_BIT_ONCE,
    SMART_LCD_CWIDTH_8_BIT_ONCE = (0x1 << 8),
    SMART_LCD_CWIDTH_18_BIT_ONCE = (0x2 << 8),
    SMART_LCD_CWIDTH_24_BIT_ONCE = (0x3 << 8),
};

/* smart lcd data width */
enum smart_lcd_dwidth {
    SMART_LCD_DWIDTH_18_BIT_ONCE_PARALLEL_SERIAL = (0 << 10),
    SMART_LCD_DWIDTH_16_BIT_ONCE_PARALLEL_SERIAL = (0x1 << 10),
    SMART_LCD_DWIDTH_8_BIT_THIRD_TIME_PARALLEL = (0x2 << 10),
    SMART_LCD_DWIDTH_8_BIT_TWICE_TIME_PARALLEL = (0x3 << 10),
    SMART_LCD_DWIDTH_8_BIT_ONCE_PARALLEL_SERIAL = (0x4 << 10),
    SMART_LCD_DWIDTH_24_BIT_ONCE_PARALLEL = (0x5 << 10),
    SMART_LCD_DWIDTH_9_BIT_TWICE_TIME_PARALLEL = (0x7 << 10),
    SMART_LCD_DWIDTH_MASK = (0x7 << 10),
};

/* smart lcd new data width */
enum smart_lcd_new_dwidth {
    SMART_LCD_NEW_DWIDTH_24_BIT = (4 << 13),
    SMART_LCD_NEW_DWIDTH_18_BIT = (3 << 13),
    SMART_LCD_NEW_DWIDTH_16_BIT = (2 << 13),
    SMART_LCD_NEW_DWIDTH_9_BIT = (1 << 13),
    SMART_LCD_NEW_DWIDTH_8_BIT = (0 << 13),
};

/* smart lcd data times */
enum smart_lcd_new_dtimes {
    SMART_LCD_NEW_DTIMES_ONCE = (0 << 8),
    SMART_LCD_NEW_DTIMES_TWICE = (1 << 8),
    SMART_LCD_NEW_DTIMES_THICE = (2 << 8),
};


/* smart lcd init code type */
enum smart_config_type
{
    SMART_CONFIG_CMD    =  0,
    SMART_CONFIG_DATA   =  1,
    SMART_CONFIG_UDELAY =  2,
};

struct slcd_data_table
{
    enum smart_config_type type;
    uint32_t value;
};

typedef void (*lcd_bl_func_t)(rt_bool_t isPowerON);

struct slcd_configure;
struct slcdc_dev_s
{
    struct rt_device parent;
    struct rt_mutex lock;
    struct slcd_configure *cfg;

    struct slcdc_dma_descriptor *desc_tmp;
    struct slcdc_dma_descriptor *desc_cmd;
    struct slcdc_dma_descriptor *desc_dat;
    struct slcdc_dma_descriptor *desc_self;

    rt_uint32_t fb_base;
    rt_uint32_t fb_cmd;
    rt_uint32_t fb_screen;
#ifdef SLCDC_USING_DUAL_BUFFER
    rt_uint32_t fb_dual;
#endif
    rt_uint32_t fb_size;
};

struct slcd_configure
{
    unsigned pinmd :1;
    unsigned pixclk_falling_edge :1;
    unsigned data_enable_active_low :1;
    unsigned clkply_active_rising:1;    /* smart lcd clock polarity:
                                           0: Active edge is Falling,
                                           1: Active edge is Rasing */
    unsigned rsply_cmd_high:1;          /* smart lcd RS polarity.
                                           0: Command_RS=0, Data_RS=1;
                                           1: Command_RS=1, Data_RS=0 */
    unsigned csply_active_high:1;       /* smart lcd CS Polarity.
                                           0: Active level is low,
                                           1: Active level is high */
    unsigned newcfg_6800_md:1;
    unsigned newcfg_fmt_conv:1;
    unsigned newcfg_cmd_9bit:1;


    rt_uint32_t width;
    rt_uint32_t height;

    rt_uint32_t fmt;
    rt_uint32_t bpp;
    rt_uint32_t bus_width;
    rt_uint32_t reg_width;
    rt_uint32_t refresh;

    const struct slcd_data_table *data_table;
    rt_uint32_t data_table_num;

    const rt_uint32_t *cmd_table; /* write GRAM command */
    rt_uint32_t cmd_table_num;
};

int     rt_hw_slcd_init          (struct slcd_configure *cfg);
void    rt_hw_slcd_set_bl_func   (lcd_bl_func_t bl_func);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_SLCDC_H_ */
