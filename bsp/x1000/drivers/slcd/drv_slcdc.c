/*
 * File      : drv_slcd_new.c
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017Äê4ÔÂ10ÈÕ     Urey         the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <cache.h>

#include "board.h"

#include "drv_slcdc.h"
#include "drv_clock.h"
#include "drv_gpio.h"

static     struct slcdc_dev_s *_slcd_device;

static void _slcd_enable(struct slcdc_dev_s *lcd_dev);
static void _slcd_disable(struct slcdc_dev_s *lcd_dev);

static void udelay(uint32_t x)
{
    volatile uint32_t   n ;

    while(x--)
    {
        for (n = 0; n < 200; ++n);
    }
}

static int _slcd_convert_bpp(uint32_t bpp)
{
    switch (bpp)
    {
    case 18:
    case 24:
        return 32;
    case 15:
        return 16;
    default:
        return bpp;
    }
}

static uint32_t refresh_pixclock_auto_adapt(struct slcdc_dev_s *lcd_dev)
{
    uint32_t pixclk = 0;

    if((lcd_dev->cfg->refresh < 10) || (lcd_dev->cfg->refresh > 100))
        lcd_dev->cfg->refresh = 60;

    pixclk = lcd_dev->fb_size * lcd_dev->cfg->refresh * 9;// Range 7 to 10

    return pixclk;
}

static void _slcd_wait_busy(void)
{
    int count = 10000;
    while ((slcd_reg_read(SLCDC_STATE) & SLCDC_STATE_BUSY) && count--);
}
/* Sent a command without data (18-bit bus, 16-bit index) */
static void _slcd_mcu_send_command(struct slcdc_dev_s *lcd_dev,uint16_t cmd)
{
    _slcd_wait_busy();

    cmd &= 0xffffff;
    slcd_reg_write(SLCDC_DATA, SLCDC_DATA_RS_COMMAND | cmd);
}

static void _slcd_mcu_send_data(struct slcdc_dev_s *lcd_dev,uint16_t data)
{
    _slcd_wait_busy();

    data &= 0xffffff;
    slcd_reg_write(SLCDC_DATA, SLCDC_DATA_RS_DATA | data);
}

/* Sent a command with data (18-bit bus, 16-bit index, 16-bit register value) */
static void _slcd_mcu_set_register(struct slcdc_dev_s *lcd_dev,uint16_t cmd, uint16_t data)
{
    _slcd_mcu_send_command(lcd_dev,cmd);
    _slcd_mcu_send_data(lcd_dev,data);
}

static void _slcd_init_mcu(struct slcdc_dev_s *lcd_dev)
{
    struct slcd_configure *cfg = lcd_dev->cfg;
    uint32_t index,j;
    uint32_t reg_width = lcd_dev->cfg->reg_width;
    uint32_t bus_width = lcd_dev->cfg->bus_width;

    if(reg_width < bus_width)
        reg_width = bus_width;

    if (cfg->data_table_num && cfg->data_table)
    {
        for (index = 0; index < cfg->data_table_num; index ++)
        {
            uint32_t value = cfg->data_table[index].value;
            switch (cfg->data_table[index].type)
            {
                case SMART_CONFIG_CMD:
                    for (j = reg_width / bus_width; j > 0; j--)
                        _slcd_mcu_send_command(lcd_dev, ((value << (32 - bus_width * j)) >> (32 - bus_width)));
                break;
                case SMART_CONFIG_DATA:
                    for (j = reg_width / bus_width; j > 0; j--)
                        _slcd_mcu_send_data(lcd_dev,((value << (32 - bus_width * j))>> (32 - bus_width)));
                break;
                case SMART_CONFIG_UDELAY:
                    udelay(cfg->data_table[index].value);
                break;
            }
        }
        _slcd_wait_busy();
    }

    if (cfg->bpp / cfg->bus_width != 1)
    {
        int tmp = slcd_reg_read(SLCDC_CFG_NEW);
        tmp &= ~(SMART_LCD_DWIDTH_MASK);    //mask the 8~9bit
        tmp |= (cfg->bpp / cfg->bus_width) == 2 ? SMART_LCD_NEW_DTIMES_TWICE : SMART_LCD_NEW_DTIMES_THICE ;
        slcd_reg_write(SLCDC_CFG_NEW, tmp);
    }
}

static void _slcd_init_mem(struct slcdc_dev_s *lcd_dev)
{
    struct slcd_configure *cfg = lcd_dev->cfg;
    int i;
    uint32_t bypes_per_panel = (((cfg->width * _slcd_convert_bpp(cfg->bpp) / 8 + 3) >> 2 << 2) * cfg->height);

#ifdef FB_BASE
    lcd_dev->fb_base = FB_BASE;
#else
#ifdef SLCDC_USING_DUAL_BUFFER
    lcd_dev->fb_base = (rt_uint32_t)rt_malloc_align((bypes_per_panel + FB_PAGE_SIZE) * 2, 32);
#else
    lcd_dev->fb_base = (rt_uint32_t)rt_malloc_align((bypes_per_panel + FB_PAGE_SIZE) * 1, 32);
#endif
#endif

    lcd_dev->desc_cmd = (struct slcdc_dma_descriptor *)(lcd_dev->fb_base + 0 * sizeof(struct slcdc_dma_descriptor));
    lcd_dev->desc_tmp = (struct slcdc_dma_descriptor *)(lcd_dev->fb_base + 1 * sizeof(struct slcdc_dma_descriptor));
    lcd_dev->desc_dat = (struct slcdc_dma_descriptor *)(lcd_dev->fb_base + 2 * sizeof(struct slcdc_dma_descriptor));
    //nop
    lcd_dev->fb_cmd   = (rt_uint32_t)lcd_dev->fb_base + 4 * sizeof(struct slcdc_dma_descriptor);

    lcd_dev->fb_screen= (rt_uint32_t)lcd_dev->fb_base + FB_PAGE_SIZE;
    rt_memset((void *) lcd_dev->fb_screen, 0, bypes_per_panel);

#ifdef SLCDC_USING_DUAL_BUFFER
    lcd_dev->fb_dual  = (lcd_dev->fb_screen + bypes_per_panel + FB_PAGE_SIZE) & ~(FB_PAGE_SIZE - 1);
    rt_memset((void *)lcd_dev->fb_dual,0,bypes_per_panel);
#endif

    lcd_dev->fb_size  = bypes_per_panel;

    /* copy command tbl */
    {
        uint32_t* cmd_ptr = (uint32_t*) lcd_dev->fb_cmd;
        for (i = 0; i < cfg->cmd_table_num; ++i)
        {
            cmd_ptr[i] = cfg->cmd_table[i];
        }
    }
}

static void _slcd_init_dma_desc(struct slcdc_dev_s *lcd_dev)
{
    struct slcd_configure *cfg = lcd_dev->cfg;
    uint32_t bypes_per_panel = (((cfg->width * _slcd_convert_bpp(cfg->bpp) / 8 + 3) >> 2 << 2) * cfg->height);

    //dmadesc_tmp used to start DMA
    lcd_dev->desc_tmp->fdadr        = virt_to_phys((void *)lcd_dev->desc_dat);
    lcd_dev->desc_tmp->fsadr        = 0;
    lcd_dev->desc_tmp->fidr         = 0xda0c0;
    lcd_dev->desc_tmp->ldcmd        = LCDC_CMD_CMD | LCDC_CMD_FRM_EN | 0;
    lcd_dev->desc_tmp->offsize      = 0;
    lcd_dev->desc_tmp->page_width   = 0;
    lcd_dev->desc_tmp->cmd_num      = 0;
    lcd_dev->desc_tmp->desc_size    = 0;

    //dmadesc_cmd used to write CMD
    lcd_dev->desc_cmd->fdadr        = virt_to_phys((void *)lcd_dev->desc_dat);
    lcd_dev->desc_cmd->fsadr        = virt_to_phys((void *)lcd_dev->fb_cmd);
    lcd_dev->desc_cmd->fidr         = 0xda0c1;
    lcd_dev->desc_cmd->offsize      = 0;
    lcd_dev->desc_cmd->page_width   = 0;
    lcd_dev->desc_cmd->desc_size    = 0;

    /* if connect mipi smart lcd, do not sent command by slcdc, send command by mipi dsi controller. */
    switch (cfg->bus_width)
    {
    case 8:
        lcd_dev->desc_cmd->ldcmd    = LCDC_CMD_CMD | LCDC_CMD_FRM_EN | 1;
        lcd_dev->desc_cmd->cmd_num  = 4;
        break;
    case 9:
    case 16:
        lcd_dev->desc_cmd->ldcmd    = LCDC_CMD_CMD | LCDC_CMD_FRM_EN | 1;
        lcd_dev->desc_cmd->cmd_num  = 2;
        break;
    default:
        lcd_dev->desc_cmd->ldcmd    = LCDC_CMD_CMD | LCDC_CMD_FRM_EN | 1;
        lcd_dev->desc_cmd->cmd_num  = 1;
        break;
    }

    //frame_desc[1] used to update GRAM
    lcd_dev->desc_dat->fdadr         = virt_to_phys((void *)lcd_dev->desc_cmd);
    lcd_dev->desc_dat->fsadr         = virt_to_phys((void *)lcd_dev->fb_screen);
    lcd_dev->desc_dat->fidr          = 0xda0d0;
    lcd_dev->desc_dat->ldcmd         = LCDC_CMD_EOFINT | LCDC_CMD_FRM_EN | (bypes_per_panel / 4);
    lcd_dev->desc_dat->offsize       = 0;
    lcd_dev->desc_dat->page_width    = 0;
    switch(_slcd_convert_bpp(cfg->bpp))
    {
    case 16 :
        lcd_dev->desc_dat->cmd_num   =  LCDC_CPOS_RGB_RGB565 | LCDC_CPOS_BPP_16;;
        break;
    case 30 :
        lcd_dev->desc_dat->cmd_num   =  LCDC_CPOS_BPP_30;
        break;
    default:
        lcd_dev->desc_dat->cmd_num   =  LCDC_CPOS_BPP_18_24;
        break;
    }

    /* data has not been premultied */
    lcd_dev->desc_dat->cmd_num |= LCDC_CPOS_PREMULTI;
    /* coef_sle 0 use 1 */
    lcd_dev->desc_dat->cmd_num |= LCDC_CPOS_COEF_SLE_1;

    lcd_dev->desc_dat->desc_size = (((cfg->height - 1) << LCDC_DESSIZE_HEIGHT_BIT) | ((cfg->width - 1) << LCDC_DESSIZE_WIDTH_BIT));

    slcd_reg_write(LCDC_DA0, virt_to_phys(lcd_dev->desc_cmd));

    //desc self
    rt_hw_flush_cache_all();
}

static void _slcd_init_ctrl(struct slcdc_dev_s *lcd_dev)
{
    struct slcd_configure *lcd_cfg = lcd_dev->cfg;
    struct clk *clk,*gate_clk;

    uint32_t ctrl;
    uint32_t size0;
    uint32_t smart_cfg = 0, smart_ctrl = 0;
    uint32_t pcfg;
    uint32_t smart_new_cfg = 0;
    uint32_t smart_wtime = 0, smart_tas = 0;

    /* clear all registers*/
    _slcd_disable(lcd_dev);
    slcd_reg_write(SLCDC_CTRL,0);

    /*The SLCD rd and ce function only can be used by set PB16/PB18 as normal GPIO function
     * SLCS_D00   PA00
     * ...
     * SLCS_D07   PA07
     *
     * slcd_rd    PB16 (not use,must set high)
     * slcd_wr    PB17
     * slcd_ce    PB18
     * slcd_te    PB19 (not use)
     * slcd_dc    PB20
     * 2. setup SLCD for register mode
     * */
    gpio_set_func(GPIO_PORT_A, 0x000000FF, GPIO_FUNC_1);
    gpio_set_func(GPIO_PORT_B, (GPIO_Pin_17 | GPIO_Pin_18 | GPIO_Pin_20), GPIO_FUNC_1);
#ifdef CONFIG_SLCDC_USE_TE
    gpio_set_func(GPIO_PORT_B, (GPIO_Pin_19), GPIO_FUNC_1);
#endif
    gpio_set_func(GPIO_PORT_B, GPIO_Pin_16, GPIO_OUTPUT1);

    /* set clock */
    gate_clk = clk_get("lcd");
    clk = clk_get("cgu_lcd");
    clk_disable(clk);
    clk_set_rate(clk, refresh_pixclock_auto_adapt(lcd_dev));
    clk_enable(clk);
    clk_enable(gate_clk);

    ctrl = LCDC_CTRL_BST_64 | LCDC_CTRL_OFUM;
    if(lcd_cfg->pinmd)
        ctrl |= LCDC_CTRL_PINMD;

    smart_cfg = SMART_LCD_DWIDTH_24_BIT_ONCE_PARALLEL;
    switch (lcd_cfg->bus_width)
    {
    case 8:
        smart_cfg |= SMART_LCD_CWIDTH_8_BIT_ONCE;
        smart_new_cfg |= SMART_LCD_NEW_DWIDTH_8_BIT;
        break;
    case 9:
        smart_cfg |= SMART_LCD_CWIDTH_9_BIT_ONCE;
        smart_new_cfg |= SMART_LCD_NEW_DWIDTH_9_BIT;
        break;
    case 16:
        smart_cfg |= SMART_LCD_CWIDTH_16_BIT_ONCE;
        smart_new_cfg |= SMART_LCD_NEW_DWIDTH_16_BIT;
        break;
    case 18:
        smart_cfg |= SMART_LCD_CWIDTH_18_BIT_ONCE;
        smart_new_cfg |= SMART_LCD_NEW_DWIDTH_18_BIT;
        break;
    case 24:
        smart_cfg |= SMART_LCD_CWIDTH_24_BIT_ONCE;
        smart_new_cfg |= SMART_LCD_NEW_DWIDTH_24_BIT;
        break;
    default:
        rt_kprintf("ERR: please check out your bus width config\n");
        break;
    }

    if (lcd_cfg->clkply_active_rising)
        smart_cfg |= SLCDC_CFG_CLK_ACTIVE_RISING;
    if (lcd_cfg->rsply_cmd_high)
        smart_cfg |= SLCDC_CFG_RS_CMD_HIGH;
    if (lcd_cfg->csply_active_high)
        smart_cfg |= SLCDC_CFG_CS_ACTIVE_HIGH;

    /* SLCD DMA mode select 0 */
    smart_ctrl = SLCDC_CTRL_DMA_MODE;
    smart_ctrl &= ~SLCDC_CTRL_GATE_MASK;

    smart_ctrl |= (SLCDC_CTRL_NEW_MODE | SLCDC_CTRL_NOT_USE_TE | SLCDC_CTRL_FAST_MODE);    //new slcd mode
    smart_ctrl &= ~SLCDC_CTRL_MIPI_MODE;
    smart_new_cfg |= SMART_LCD_NEW_DTIMES_ONCE;

    if (lcd_cfg->newcfg_6800_md)
        smart_new_cfg |= SLCDC_NEW_CFG_6800_MD;
    if (lcd_cfg->newcfg_cmd_9bit)
        smart_new_cfg |= SLCDC_NEW_CFG_CMD_9BIT;

    slcd_reg_write(LCDC_VAT, (lcd_cfg->width << 16) | lcd_cfg->height);
    slcd_reg_write(LCDC_DAH, lcd_cfg->width);
    slcd_reg_write(LCDC_DAV, lcd_cfg->height);

    slcd_reg_write(SLCDC_CFG, smart_cfg);
    slcd_reg_write(SLCDC_CTRL, smart_ctrl);
    slcd_reg_write(SLCDC_CFG_NEW, smart_new_cfg);
    slcd_reg_write(SLCDC_WTIME, smart_wtime);
    slcd_reg_write(SLCDC_TAS, smart_tas);
	slcd_reg_write(SLCDC_SLOW_TIME, 0x0000FFFF);
    slcd_reg_write(LCDC_CTRL, ctrl);

    pcfg = 0xC0000000 | (511 << 18) | (400 << 9) | (256 << 0);
    slcd_reg_write(LCDC_PCFG, pcfg);

    size0  = (lcd_cfg->width << LCDC_SIZE_WIDTH_BIT) & LCDC_SIZE_WIDTH_MASK;
    size0 |= (lcd_cfg->height << LCDC_SIZE_HEIGHT_BIT) & LCDC_SIZE_HEIGHT_MASK;
    slcd_reg_write(LCDC_SIZE0, size0);
    slcd_reg_write(LCDC_CTRL,slcd_reg_read(LCDC_CTRL) | LCDC_CTRL_ENA);
    _slcd_init_dma_desc(lcd_dev);

    _slcd_init_mcu(lcd_dev);

    _slcd_enable(lcd_dev);

    if (lcd_cfg->newcfg_fmt_conv)
    {
        smart_new_cfg = slcd_reg_read(SLCDC_CFG_NEW);
        smart_new_cfg |= SLCDC_NEW_CFG_FMT_CONV_EN;
        slcd_reg_write(SLCDC_CFG_NEW, smart_new_cfg);
    }

#ifdef CONFIG_SLCDC_CONTINUA
    smart_ctrl &= ~SLCDC_CTRL_DMA_MODE;
#else
    smart_ctrl |= SLCDC_CTRL_DMA_START;
#endif
    smart_ctrl |= SLCDC_CTRL_DMA_EN;

#ifdef CONFIG_SLCDC_USE_TE
    smart_ctrl &= ~SLCDC_CTRL_NOT_USE_TE;
	//smart_ctrl |= SLCDC_CTRL_TE_INV;
	smart_ctrl &= ~SLCDC_CTRL_TE_INV;
#endif
    slcd_reg_write(SLCDC_CTRL, smart_ctrl);
}

static void _slcd_enable(struct slcdc_dev_s *lcd_dev)
{
    uint32_t ctrl,state;
    int count = 2000;
    while ((slcd_reg_read(SLCDC_STATE) & SLCDC_STATE_BUSY) && count--)
    {
        udelay(10);
    }

    slcd_reg_write(LCDC_STATE, 0);
    slcd_reg_write(LCDC_CTRL,slcd_reg_read(LCDC_CTRL) | LCDC_CTRL_ENA);
}

static void _slcd_disable(struct slcdc_dev_s *lcd_dev)
{
    /* SLCD and TVE only support quick disable */
    slcd_reg_write(LCDC_CTRL, slcd_reg_read(LCDC_CTRL) & ~LCDC_CTRL_ENA);
}

/* common device interface */
static rt_err_t  _slcd_device_control(rt_device_t dev, int cmd, void *args)
{
    struct slcdc_dev_s *slcd;
	
	uint32_t smart_ctrl = 0;

    slcd = (struct slcdc_dev_s *)dev;
    RT_ASSERT(slcd != RT_NULL);

    rt_mutex_take(&(slcd->lock), RT_WAITING_FOREVER);

    switch (cmd)
    {
    case RTGRAPHIC_CTRL_GET_INFO:
    {
        struct rt_device_graphic_info *info = (struct rt_device_graphic_info *) args;

        info->bits_per_pixel    = slcd->cfg->bpp;
        info->pixel_format      = slcd->cfg->fmt;
#ifdef SLCDC_USING_DUAL_BUFFER
        info->framebuffer       = (rt_uint8_t *)(KSEG1ADDR(slcd->fb_dual));
#else
        info->framebuffer       = (rt_uint8_t *)(KSEG1ADDR(slcd->fb_screen));
#endif

        info->width             = slcd->cfg->width;
        info->height            = slcd->cfg->height;
        break;
    }

    case RTGRAPHIC_CTRL_RECT_UPDATE:
    {
#ifdef SLCDC_USING_DUAL_BUFFER
        rt_memcpy((void *)(slcd->fb_screen), (void *)(slcd->fb_dual), slcd->fb_size);
#endif
        rt_hw_dcache_flush_range((rt_uint32_t)slcd->fb_screen,slcd->fb_size);
		
		smart_ctrl = slcd_reg_read(SLCDC_CTRL);
		smart_ctrl |= SLCDC_CTRL_DMA_START;
		slcd_reg_write(SLCDC_CTRL, smart_ctrl);
		while (slcd_reg_read(SLCDC_STATE) & SLCDC_STATE_BUSY);

        break;
    }
    case RTGRAPHIC_CTRL_SET_MODE:
        break;
    }

    rt_mutex_release(&(slcd->lock));

    return RT_EOK;
}

int rt_hw_slcd_init(struct slcd_configure *cfg)
{
    struct slcdc_dev_s *slcd;

    slcd = (struct slcdc_dev_s *)rt_malloc(sizeof(struct slcdc_dev_s));
    if(slcd == RT_NULL)
    {
        rt_kprintf("error no memory!\n");

        return -RT_ENOMEM;
    }
    _slcd_device = slcd;

    slcd->cfg = cfg;
    rt_mutex_init(&slcd->lock, "lcdfb", RT_IPC_FLAG_FIFO);

    _slcd_disable(slcd);
    _slcd_init_mem(slcd);
    _slcd_init_ctrl(slcd);
    _slcd_enable(slcd);
    /* device support */
    slcd->parent.type       = RT_Device_Class_Graphic;
    slcd->parent.init       = RT_NULL;
    slcd->parent.open       = RT_NULL;
    slcd->parent.close      = RT_NULL;
    slcd->parent.read       = RT_NULL;
    slcd->parent.write      = RT_NULL;
    slcd->parent.control    = _slcd_device_control;

    rt_device_register(&slcd->parent, "lcd", RT_DEVICE_FLAG_RDWR);

    return RT_EOK;
}
