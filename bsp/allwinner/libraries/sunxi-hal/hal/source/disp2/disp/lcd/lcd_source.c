/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include "lcd_source.h"

/**
 * sunxi_lcd_delay_ms.
 * @ms: Delay time, unit: millisecond.
 */
s32 sunxi_lcd_delay_ms(u32 ms)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_delay_ms)
        return g_lcd_drv.src_ops.sunxi_lcd_delay_ms(ms);

    return -1;
}

/**
 * sunxi_lcd_delay_us.
 * @us: Delay time, unit: microsecond.
 */
s32 sunxi_lcd_delay_us(u32 us)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_delay_us)
        return g_lcd_drv.src_ops.sunxi_lcd_delay_us(us);

    return -1;
}

/**
 * sunxi_lcd_tcon_enable - enable timing controller.
 * @screen_id: The index of screen.
 */
void sunxi_lcd_tcon_enable(u32 screen_id)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_tcon_enable)
        g_lcd_drv.src_ops.sunxi_lcd_tcon_enable(screen_id);
}


/**
 * sunxi_lcd_dsi_mode_switch
 * @screen_id: The index of screen.
 * @cmd_en : enable command mode
 * @lp_en : enable low power mode for video mode
 */
void sunxi_lcd_dsi_mode_switch(u32 screen_id, u32 cmd_en, u32 lp_en)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_dsi_mode_switch)
        g_lcd_drv.src_ops.sunxi_lcd_dsi_mode_switch(screen_id, cmd_en,
                                lp_en);
}

/**
 * sunxi_lcd_tcon_disable - disable timing controller.
 * @screen_id: The index of screen.
 */
void sunxi_lcd_tcon_disable(u32 screen_id)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_tcon_disable)
        g_lcd_drv.src_ops.sunxi_lcd_tcon_disable(screen_id);
}

/**
 * sunxi_lcd_backlight_enable - enable the backlight of panel.
 * @screen_id: The index of screen.
 */
void sunxi_lcd_backlight_enable(u32 screen_id)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_backlight_enable)
        g_lcd_drv.src_ops.sunxi_lcd_backlight_enable(screen_id);
}

/**
 * sunxi_lcd_backlight_disable - disable the backlight of panel.
 * @screen_id: The index of screen.
 */
void sunxi_lcd_backlight_disable(u32 screen_id)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_backlight_disable)
        g_lcd_drv.src_ops.sunxi_lcd_backlight_disable(screen_id);
}

/**
 * sunxi_lcd_power_enable - enable the power of panel.
 * @screen_id: The index of screen.
 * @pwr_id:     The index of power
 */
void sunxi_lcd_power_enable(u32 screen_id, u32 pwr_id)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_power_enable)
        g_lcd_drv.src_ops.sunxi_lcd_power_enable(screen_id, pwr_id);
}

/**
 * sunxi_lcd_power_disable - disable the power of panel.
 * @screen_id: The index of screen.
 * @pwr_id:     The index of power
 */
void sunxi_lcd_power_disable(u32 screen_id, u32 pwr_id)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_power_disable)
        g_lcd_drv.src_ops.sunxi_lcd_power_disable(screen_id, pwr_id);
}

/**
 * sunxi_lcd_pwm_enable - enable pwm modules, start output pwm wave.
 * @screen_id: The index of screen.
 *
 * need to conifg gpio for pwm function
 */
s32 sunxi_lcd_pwm_enable(u32 screen_id)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_pwm_enable)
        return g_lcd_drv.src_ops.sunxi_lcd_pwm_enable(screen_id);

    return -1;
}

/**
 * sunxi_lcd_pwm_disable - disable pwm modules, stop output pwm wave.
 * @screen_id: The index of screen.
 */
s32 sunxi_lcd_pwm_disable(u32 screen_id)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_pwm_disable)
        return g_lcd_drv.src_ops.sunxi_lcd_pwm_disable(screen_id);

    return -1;
}

/**
 *
 * sunxi_lcd_cpu_set_auto_mode
 * @screen_id: The index of screen.
 */
s32 sunxi_lcd_cpu_set_auto_mode(u32 screen_id)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_cpu_set_auto_mode)
        return g_lcd_drv.src_ops.sunxi_lcd_cpu_set_auto_mode(screen_id);

    return -1;
}

/**
 * sunxi_lcd_cpu_write - write command and para to cpu panel.
 * @screen_id: The index of screen.
 * @command: Command to be transfer.
 * @para: The pointer to para
 * @para_num: The number of para
 */
s32 sunxi_lcd_cpu_write(u32 screen_id, u32 index, u32 data)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_cpu_write)
        return g_lcd_drv.src_ops.sunxi_lcd_cpu_write(screen_id,
                                 index, data);

    return -1;
}

/**
 * sunxi_lcd_cpu_write_index - write command to cpu panel.
 * @screen_id: The index of screen.
 * @index: Command or index to be transfer.
 */
s32 sunxi_lcd_cpu_write_index(u32 screen_id, u32 index)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_cpu_write_index)
        return g_lcd_drv.src_ops.sunxi_lcd_cpu_write_index(screen_id,
                                   index);

    return -1;
}

/**
 * sunxi_lcd_cpu_write_data - write data to cpu panel.
 * @screen_id: The index of screen.
 * @data: Data to be transfer.
 */
s32 sunxi_lcd_cpu_write_data(u32 screen_id, u32 data)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_cpu_write_data)
        return g_lcd_drv.src_ops.sunxi_lcd_cpu_write_data(screen_id,
                                  data);

    return -1;
}

/**
 * sunxi_lcd_dsi_dcs_write - write command and para to mipi panel.
 * @screen_id: The index of screen.
 * @command: Command to be transfer.
 * @para: The pointer to para.
 * @para_num: The number of para
 */
s32 sunxi_lcd_dsi_dcs_write(u32 screen_id, u8 command, u8 *para, u32 para_num)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_dsi_dcs_write)
        return g_lcd_drv.src_ops.sunxi_lcd_dsi_dcs_write(screen_id,
                                 command, para,
                                 para_num);

    return -1;
}

/**
 * sunxi_lcd_dsi_dcs_write - write command and para to mipi panel.
 * @screen_id: The index of screen.
 * @command: Command to be transfer.
 */
s32 sunxi_lcd_dsi_dcs_write_0para(u32 screen_id, u8 command)
{
    u8 tmp[5];

    sunxi_lcd_dsi_dcs_write(screen_id, command, tmp, 0);

    return -1;
}

/**
 * sunxi_lcd_dsi_dcs_write_1para - write command and para to mipi panel.
 * @screen_id: The index of screen.
 * @command: Command to be transfer.
 * @paran: Para to be transfer.
 */
s32 sunxi_lcd_dsi_dcs_write_1para(u32 screen_id, u8 command, u8 para1)
{
    u8 tmp[5];

    tmp[0] = para1;
    sunxi_lcd_dsi_dcs_write(screen_id, command, tmp, 1);

    return -1;
}

s32 sunxi_lcd_dsi_dcs_write_2para(u32 screen_id, u8 command, u8 para1, u8 para2)
{
    u8 tmp[5];

    tmp[0] = para1;
    tmp[1] = para2;
    sunxi_lcd_dsi_dcs_write(screen_id, command, tmp, 2);

    return -1;
}

s32 sunxi_lcd_dsi_dcs_write_3para(u32 screen_id, u8 command, u8 para1, u8 para2,
                  u8 para3)
{
    u8 tmp[5];

    tmp[0] = para1;
    tmp[1] = para2;
    tmp[2] = para3;
    sunxi_lcd_dsi_dcs_write(screen_id, command, tmp, 3);

    return -1;
}

s32 sunxi_lcd_dsi_dcs_write_4para(u32 screen_id, u8 command, u8 para1, u8 para2,
                  u8 para3, u8 para4)
{
    u8 tmp[5];

    tmp[0] = para1;
    tmp[1] = para2;
    tmp[2] = para3;
    tmp[3] = para4;
    sunxi_lcd_dsi_dcs_write(screen_id, command, tmp, 4);

    return -1;
}

s32 sunxi_lcd_dsi_dcs_write_5para(u32 screen_id, u8 command, u8 para1, u8 para2,
                  u8 para3, u8 para4, u8 para5)
{
    u8 tmp[5];

    tmp[0] = para1;
    tmp[1] = para2;
    tmp[2] = para3;
    tmp[3] = para4;
    tmp[4] = para5;
    sunxi_lcd_dsi_dcs_write(screen_id, command, tmp, 5);

    return -1;
}

s32 sunxi_lcd_dsi_dcs_write_6para(u32 screen_id, u8 command, u8 para1, u8 para2,
                  u8 para3, u8 para4, u8 para5, u8 para6)
{
    u8 tmp[6];

    tmp[0] = para1;
    tmp[1] = para2;
    tmp[2] = para3;
    tmp[3] = para4;
    tmp[4] = para5;
    tmp[5] = para6;
    sunxi_lcd_dsi_dcs_write(screen_id, command, tmp, 6);

    return -1;
}

/**
 * sunxi_lcd_dsi_gen_write - write command and para to mipi panel.
 * @screen_id: The index of screen.
 * @command: Command to be transfer.
 * @para: The pointer to para.
 * @para_num: The number of para
 */
s32 sunxi_lcd_dsi_gen_write(u32 screen_id, u8 command, u8 *para, u32 para_num)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_dsi_gen_write)
        return g_lcd_drv.src_ops.sunxi_lcd_dsi_gen_write(screen_id,
                                 command, para,
                                 para_num);

    return -1;
}

/**
 * sunxi_lcd_dsi_gen_write - write command and para to mipi panel.
 * @screen_id: The index of screen.
 * @command: Command to be transfer.
 */
s32 sunxi_lcd_dsi_gen_write_0para(u32 screen_id, u8 command)
{
    u8 tmp[5];

    sunxi_lcd_dsi_gen_write(screen_id, command, tmp, 0);

    return -1;
}

/**
 * sunxi_lcd_dsi_gen_write_1para - write command and para to mipi panel.
 * @screen_id: The index of screen.
 * @command: Command to be transfer.
 * @paran: Para to be transfer.
 */
s32 sunxi_lcd_dsi_gen_write_1para(u32 screen_id, u8 command, u8 para1)
{
    u8 tmp[5];

    tmp[0] = para1;
    sunxi_lcd_dsi_gen_write(screen_id, command, tmp, 1);

    return -1;
}

s32 sunxi_lcd_dsi_gen_write_2para(u32 screen_id, u8 command, u8 para1, u8 para2)
{
    u8 tmp[5];

    tmp[0] = para1;
    tmp[1] = para2;
    sunxi_lcd_dsi_gen_write(screen_id, command, tmp, 2);

    return -1;
}

s32 sunxi_lcd_dsi_gen_write_3para(u32 screen_id, u8 command, u8 para1, u8 para2,
                  u8 para3)
{
    u8 tmp[5];

    tmp[0] = para1;
    tmp[1] = para2;
    tmp[2] = para3;
    sunxi_lcd_dsi_gen_write(screen_id, command, tmp, 3);

    return -1;
}

s32 sunxi_lcd_dsi_gen_write_4para(u32 screen_id, u8 command, u8 para1, u8 para2,
                  u8 para3, u8 para4)
{
    u8 tmp[5];

    tmp[0] = para1;
    tmp[1] = para2;
    tmp[2] = para3;
    tmp[3] = para4;
    sunxi_lcd_dsi_gen_write(screen_id, command, tmp, 4);

    return -1;
}

s32 sunxi_lcd_dsi_gen_write_5para(u32 screen_id, u8 command, u8 para1, u8 para2,
                  u8 para3, u8 para4, u8 para5)
{
    u8 tmp[5];

    tmp[0] = para1;
    tmp[1] = para2;
    tmp[2] = para3;
    tmp[3] = para4;
    tmp[4] = para5;
    sunxi_lcd_dsi_gen_write(screen_id, command, tmp, 5);

    return -1;
}

/**
 * sunxi_lcd_dsi_clk_enable - enable dsi clk.
 * @screen_id: The index of screen.
 */
s32 sunxi_lcd_dsi_clk_enable(u32 screen_id)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_dsi_clk_enable)
        return g_lcd_drv.src_ops.sunxi_lcd_dsi_clk_enable(screen_id, 1);

    return -1;
}

/**
 * sunxi_lcd_dsi_clk_disable - disable dsi clk.
 * @screen_id: The index of screen.
 */
s32 sunxi_lcd_dsi_clk_disable(u32 screen_id)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_dsi_clk_enable)
        return g_lcd_drv.src_ops.sunxi_lcd_dsi_clk_enable(screen_id, 0);

    return -1;
}

/**
 * sunxi_lcd_dsi_gen_read - generic short read
 * @screen_id: The index of screen.
 * @result: pointer that store the result
 */
static s32 sunxi_lcd_dsi_gen_short_read(u32 screen_id, u8 *para, u8 para_num,
                    u8 *result)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_dsi_gen_short_read)
        return g_lcd_drv.src_ops.sunxi_lcd_dsi_gen_short_read(screen_id,
                                 para, para_num,
                                 result);
    return -1;
}

/**
 * @name       :sunxi_lcd_dsi_set_max_ret_size
 * @brief      :set max ret size of dsi read
 * @param[IN]  :sel:index of dsi
 * @param[IN]  :size:number of byte of max size
 * @return     :0
 */
s32 sunxi_lcd_dsi_set_max_ret_size(u32 sel, u32 size)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_dsi_dcs_read)
        return g_lcd_drv.src_ops.sunxi_lcd_dsi_set_max_ret_size(sel,
                                    size);
    return 0;
}

/**
 * @name       :sunxi_lcd_dsi_dcs_read
 * @brief      :dcs read
 * @param[IN]  :sel:index of dsi
 * @param[IN]  :cmd: dcs command
 * @param[OUT] :result: pointer of read result,larger then max ret size
 * @param[OUT] :num_p: number of bytes have been readed
 * @return     :number of bytes have been readed
 */
s32 sunxi_lcd_dsi_dcs_read(u32 sel, u8 cmd, u8 *result, u32 *num_p)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_dsi_dcs_read)
        return g_lcd_drv.src_ops.sunxi_lcd_dsi_dcs_read(sel, cmd,
                                result, num_p);
    return 0;
}

/**
 * sunxi_lcd_dsi_gen_short_read0p - generic read without param
 * @screen_id: The index of screen.
 * @paran: Para to be transfer.
 * @result: pointer that store the result
 */
s32 sunxi_lcd_dsi_gen_short_read0p(u32 screen_id, u8 *result)
{
    u8 tmp[2];

    return sunxi_lcd_dsi_gen_short_read(screen_id, tmp, 0, result);
}

/**
 * sunxi_lcd_dsi_gen_short_read1p - generic read with 1 param
 * @screen_id: The index of screen.
 * @paran: Para to be transfer.
 * @result: pointer that store the result
 */
s32 sunxi_lcd_dsi_gen_short_read1p(u32 screen_id, u8 para0, u8 *result)
{
    u8 tmp[2];

    tmp[0] = para0;
    sunxi_lcd_dsi_gen_short_read(screen_id,  tmp, 1, result);

    return -1;
}

/**
 * sunxi_lcd_dsi_gen_short_read2p - generic read with 2 param
 * @screen_id: The index of screen.
 * @paran: Para to be transfer.
 * @result: pointer that store the result
 */
s32 sunxi_lcd_dsi_gen_short_read2p(u32 screen_id, u8 para0, u8 para1,
                   u8 *result)
{
    u8 tmp[2];

    tmp[0] = para0;
    tmp[1] = para1;
    return sunxi_lcd_dsi_gen_short_read(screen_id, tmp, 2, result);
}

/**
 * sunxi_lcd_set_panel_funs -  set panel functions.
 * @name: The panel driver name.
 * @lcd_cfg: The functions.
 */
s32 sunxi_lcd_set_panel_funs(char *name, struct disp_lcd_panel_fun *lcd_cfg)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_set_panel_funs)
        return g_lcd_drv.src_ops.sunxi_lcd_set_panel_funs(name,
                                  lcd_cfg);

    return -1;
}

/**
 * sunxi_lcd_pin_cfg - config pin panel used
 * @screen_id: The index of screen.
 * @bon:     1: config pin according to sys_config, 0: set disable state
 */
s32 sunxi_lcd_pin_cfg(u32 screen_id, u32 bon)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_pin_cfg)
        return g_lcd_drv.src_ops.sunxi_lcd_pin_cfg(screen_id, bon);

    return -1;
}

/**
 * sunxi_lcd_gpio_set_value
 * @screen_id: The index of screen.
 * @io_index:  the index of gpio
 * @value: value of gpio to be set
 */
s32 sunxi_lcd_gpio_set_value(u32 screen_id, u32 io_index, u32 value)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_gpio_set_value)
        return g_lcd_drv.src_ops.sunxi_lcd_gpio_set_value(screen_id,
                                  io_index,
                                  value);

    return -1;
}

/**
 * sunxi_lcd_gpio_set_direction
 * @screen_id: The index of screen.
 * @io_index:  the index of gpio
 * @direct: value of gpio to be set
 */
s32 sunxi_lcd_gpio_set_direction(u32 screen_id, u32 io_index, u32 direct)
{
    if (g_lcd_drv.src_ops.sunxi_lcd_gpio_set_direction)
        return g_lcd_drv.src_ops.sunxi_lcd_gpio_set_direction(screen_id,
                                      io_index,
                                      direct);

    return -1;
}
