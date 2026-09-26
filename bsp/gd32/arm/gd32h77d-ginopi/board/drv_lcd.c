/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-04     RTT          add FL7707N MIPI DSI LCD support
 * 2026-09-08     CYFS         stabilize FL7707N timing, framebuffer swaps, and backlight control
 */

#include <board.h>
#include <rthw.h>
#include <rtdevice.h>

#include "gd32h77x_78x_dsi.h"
#include "gd32h77x_78x_axiim.h"
#include "gd32h77x_78x_tli.h"

#ifdef BSP_USING_LCD_MIPI

#define DRV_DEBUG
#define LOG_TAG                         "drv.lcd"
#include <drv_log.h>

#define LCD_DEVICE_NAME                 "lcd"
#define LCD_WIDTH                       720U
#define LCD_HEIGHT                      720U
#define LCD_BYTES_PER_PIXEL             2U
#define LCD_FRAMEBUFFER_SIZE            (LCD_WIDTH * LCD_HEIGHT * LCD_BYTES_PER_PIXEL)
#define LCD_FRAMEBUFFER_COUNT           2U
#define LCD_FRAMEBUFFER_TOTAL_SIZE      (LCD_FRAMEBUFFER_SIZE * LCD_FRAMEBUFFER_COUNT)
#define LCD_FRAMEBUFFER_ADDRESS         EXT_SDRAM_BEGIN
#define LCD_FRAMEBUFFER_BACK_ADDRESS    (LCD_FRAMEBUFFER_ADDRESS + LCD_FRAMEBUFFER_SIZE)
#define LCD_BACKLIGHT_PIN               GET_PIN(A, 0)
#define LCD_BACKLIGHT_PWM_DEVICE_NAME   "pwm1"
#define LCD_BACKLIGHT_PWM_CHANNEL       1U
#define LCD_BACKLIGHT_PWM_PERIOD_NS     50000U
#define LCD_BACKLIGHT_DEFAULT_LEVEL     100U
#define LCD_VSYNC_TIMEOUT_MS            100U

#define LCD_HSYNC                       60U
#define LCD_HBP                         120U
#define LCD_HFP                         106U
#define LCD_VSYNC                       4U
#define LCD_VBP                         20U
#define LCD_VFP                         20U

#define LCD_PIXEL_CLOCK                 46125000U
#define LCD_DSI_LP_CLOCK                12500000U
#define LCD_DSI_HS_RATE                 800000000U
#define LCD_DSI_FORMAT                  DSI_VIDEO_MODE_FMT_RGB565
#define LCD_DSI_VIDEO_MODE              DSI_BURST_MODE
#define LCD_DSI_LANES                   2U
#define LCD_DSI_CHANNEL                 0U
#define LCD_DSI_TIMEOUT                 1000000U
#define LCD_DSI_CMD_MAX_BYTES           64U

#define MIPI_DSI_DCS_SHORT_WRITE        0x05U
#define MIPI_DSI_DCS_SHORT_WRITE_PARAM  0x15U
#define MIPI_DSI_DCS_LONG_WRITE         0x39U
#define DIV_ROUND_UP(value, divisor)    (((value) + (divisor) - 1U) / (divisor))
#define MAX_VALUE(a, b)                 ((a) > (b) ? (a) : (b))

struct lcd_init_cmd
{
    rt_uint8_t len;
    rt_uint16_t delay_ms;
    rt_uint8_t data[LCD_DSI_CMD_MAX_BYTES];
};

struct lcd_dphy_timing
{
    rt_uint8_t freq_mode;
    rt_uint8_t esc_ck_sel;
    rt_uint8_t pll_divider;
    rt_uint16_t dlcfg;
    rt_uint16_t ck_hs2lp;
    rt_uint16_t ck_lp2hs;
    rt_uint16_t lp_clkc;
    rt_uint8_t dhs_prep;
    rt_uint8_t dhs_zero;
    rt_uint8_t dhs_trail;
    rt_uint8_t dhs_exit;
    rt_uint8_t ckhs_prep;
    rt_uint8_t ckhs_zero;
    rt_uint8_t ckhs_trail;
    rt_uint8_t ckhs_exit;
};

struct gd32_lcd
{
    struct rt_device parent;
    struct rt_device_graphic_info info;
    struct rt_device_pwm *backlight_pwm;
    rt_base_t backlight_pin;
    rt_uint8_t brightness;
    rt_bool_t backlight_powered;
    rt_bool_t initialized;
};

static struct gd32_lcd lcd;
static struct rt_completion lcd_reload_completion;
static struct rt_device_rect_info lcd_dirty_rect;
static rt_bool_t lcd_dirty_valid;
static rt_bool_t lcd_reload_timeout_reported;

static rt_err_t lcd_backlight_apply(void)
{
    rt_uint32_t pulse;
    rt_err_t result;

    if (lcd.backlight_pwm == RT_NULL)
    {
        lcd.backlight_pwm = (struct rt_device_pwm *)
                            rt_device_find(LCD_BACKLIGHT_PWM_DEVICE_NAME);
        if (lcd.backlight_pwm == RT_NULL)
        {
            LOG_E("cannot find %s for backlight",
                  LCD_BACKLIGHT_PWM_DEVICE_NAME);
            return -RT_ENOSYS;
        }
    }

    if (!lcd.backlight_powered || (lcd.brightness == 0U))
    {
        result = rt_pwm_disable(lcd.backlight_pwm,
                                LCD_BACKLIGHT_PWM_CHANNEL);
        rt_pin_mode(lcd.backlight_pin, PIN_MODE_OUTPUT);
        rt_pin_write(lcd.backlight_pin, PIN_LOW);
        return result;
    }

    pulse = (rt_uint32_t)(((rt_uint64_t)LCD_BACKLIGHT_PWM_PERIOD_NS *
                           lcd.brightness) / 100U);
    result = rt_pwm_set(lcd.backlight_pwm, LCD_BACKLIGHT_PWM_CHANNEL,
                        LCD_BACKLIGHT_PWM_PERIOD_NS, pulse);
    if (result != RT_EOK)
    {
        return result;
    }

    return rt_pwm_enable(lcd.backlight_pwm, LCD_BACKLIGHT_PWM_CHANNEL);
}

static rt_err_t lcd_backlight_set_brightness(rt_uint8_t brightness)
{
    if (brightness > 100U)
    {
        return -RT_EINVAL;
    }

    lcd.brightness = brightness;
    return lcd_backlight_apply();
}

static void lcd_framebuffer_flush(void)
{
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH,
                         (void *)LCD_FRAMEBUFFER_ADDRESS,
                         LCD_FRAMEBUFFER_TOTAL_SIZE);
}

static void lcd_framebuffer_fill(rt_uint16_t color)
{
    rt_uint16_t *framebuffer = (rt_uint16_t *)LCD_FRAMEBUFFER_ADDRESS;
    rt_size_t index;

    for (index = 0U;
         index < LCD_WIDTH * LCD_HEIGHT * LCD_FRAMEBUFFER_COUNT;
         index++)
    {
        framebuffer[index] = color;
    }
    lcd_framebuffer_flush();
}

static const struct lcd_init_cmd panel_init_cmds[] =
{
    { 4, 0, { 0xB9, 0xF1, 0x12, 0x87 } },
    { 4, 0, { 0xB2, 0xB4, 0x03, 0x70 } },
    { 11, 0, { 0xB3, 0x10, 0x10, 0x28, 0x28, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x00 } },
    { 2, 0, { 0xB4, 0x80 } },
    { 3, 0, { 0xB5, 0x0A, 0x0A } },
    { 3, 0, { 0xB6, 0x8D, 0x8D } },
    { 5, 0, { 0xB8, 0x26, 0x22, 0xF0, 0x13 } },
    { 28, 0, { 0xBA, 0x31, 0x81, 0x05, 0xF9, 0x0E, 0x0E, 0x20,
               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44,
               0x25, 0x00, 0x91, 0x0A, 0x00, 0x00, 0x01, 0x4F,
               0x01, 0x00, 0x00, 0x37 } },
    { 2, 0, { 0xBC, 0x47 } },
    { 6, 0, { 0xBF, 0x02, 0x10, 0x00, 0x80, 0x04 } },
    { 10, 0, { 0xC0, 0x73, 0x73, 0x50, 0x50, 0x00, 0x00, 0x12, 0x73, 0x00 } },
    { 18, 0, { 0xC1, 0x36, 0x00, 0x32, 0x32, 0x77, 0xE1, 0x77, 0x77,
               0xCC, 0xCC, 0xFF, 0xFF, 0x11, 0x11, 0x00, 0x00, 0x32 } },
    { 13, 0, { 0xC7, 0x10, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00,
               0xED, 0xC5, 0x00, 0xA5 } },
    { 5, 0, { 0xC8, 0x10, 0x40, 0x1E, 0x03 } },
    { 2, 0, { 0xCC, 0x0B } },
    { 35, 0, { 0xE0, 0x00, 0x0A, 0x0F, 0x2A, 0x33, 0x3F, 0x44, 0x39,
               0x06, 0x0C, 0x0E, 0x14, 0x15, 0x13, 0x15, 0x10, 0x18,
               0x00, 0x0A, 0x0F, 0x2A, 0x33, 0x3F, 0x44, 0x39, 0x06,
               0x0C, 0x0E, 0x14, 0x15, 0x13, 0x15, 0x10, 0x18 } },
    { 8, 0, { 0xE1, 0x11, 0x11, 0x91, 0x00, 0x00, 0x00, 0x00 } },
    { 15, 0, { 0xE3, 0x07, 0x07, 0x0B, 0x0B, 0x0B, 0x0B, 0x00, 0x00,
               0x00, 0x00, 0xFF, 0x04, 0xC0, 0x10 } },
    { 64, 0, { 0xE9, 0xC8, 0x10, 0x0A, 0x00, 0x00, 0x80, 0x81, 0x12,
               0x31, 0x23, 0x4F, 0x86, 0xA0, 0x00, 0x47, 0x08, 0x00,
               0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00,
               0x00, 0x00, 0x98, 0x02, 0x8B, 0xAF, 0x46, 0x02, 0x88,
               0x88, 0x88, 0x88, 0x88, 0x98, 0x13, 0x8B, 0xAF, 0x57,
               0x13, 0x88, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00,
               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
               0x00 } },
    { 62, 0, { 0xEA, 0x97, 0x0C, 0x09, 0x09, 0x09, 0x78, 0x00, 0x00,
               0x00, 0x00, 0x00, 0x00, 0x9F, 0x31, 0x8B, 0xA8, 0x31,
               0x75, 0x88, 0x88, 0x88, 0x88, 0x88, 0x9F, 0x20, 0x8B,
               0xA8, 0x20, 0x64, 0x88, 0x88, 0x88, 0x88, 0x88, 0x23,
               0x00, 0x00, 0x02, 0x71, 0x00, 0x00, 0x00, 0x00, 0x00,
               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
               0x00, 0x40, 0x80, 0x81, 0x00, 0x00, 0x00, 0x00 } },
    { 4, 0, { 0xEF, 0xFF, 0xFF, 0x01 } },
    { 2, 0, { 0x3A, 0x50 } },
    { 1, 250, { 0x11 } },
    { 1, 50, { 0x29 } },
};

static rt_err_t dsi_wait_fifo(uint32_t flag, FlagStatus expected)
{
    rt_uint32_t timeout = LCD_DSI_TIMEOUT;

    while ((dsi_fifo_status_get(flag) != expected) && (timeout > 0U))
    {
        timeout--;
    }

    return timeout > 0U ? RT_EOK : -RT_ETIMEOUT;
}

static rt_err_t dsi_write_cmd(const rt_uint8_t *data, rt_size_t len)
{
    rt_uint32_t word;
    rt_size_t offset;
    rt_size_t remaining;
    rt_uint8_t type;

    /* Panel commands must not read beyond an initialization entry's payload. */
    if ((data == RT_NULL) || (len == 0U) || (len > LCD_DSI_CMD_MAX_BYTES))
    {
        return -RT_EINVAL;
    }

    if (dsi_wait_fifo(DSI_FIFOSTAT_LPCTLFIFOF, RESET) != RT_EOK)
    {
        return -RT_ETIMEOUT;
    }

    if (len <= 2U)
    {
        type = len == 1U ? MIPI_DSI_DCS_SHORT_WRITE : MIPI_DSI_DCS_SHORT_WRITE_PARAM;
        word = data[0];
        if (len == 2U)
        {
            word |= (rt_uint32_t)data[1] << 8;
        }
        dsi_dcs_word_count_set(0U);
        dsi_lp_control_set(type, LCD_DSI_CHANNEL, word);
    }
    else
    {
        dsi_dcs_word_count_set((uint32_t)len);
        for (offset = 0U; offset < len; offset += sizeof(word))
        {
            if (dsi_wait_fifo(DSI_FIFOSTAT_LPDTFIFOF, RESET) != RT_EOK)
            {
                return -RT_ETIMEOUT;
            }

            word = 0U;
            remaining = len - offset;
            if (remaining > sizeof(word))
            {
                remaining = sizeof(word);
            }
            rt_memcpy(&word, data + offset, remaining);
            dsi_lp_data_write(word);
        }
        dsi_lp_control_set(MIPI_DSI_DCS_LONG_WRITE, LCD_DSI_CHANNEL, (uint32_t)len);
    }

    if ((dsi_wait_fifo(DSI_FIFOSTAT_LPCTLFIFOE, SET) != RT_EOK) ||
        (dsi_wait_fifo(DSI_FIFOSTAT_LPDTFIFOE, SET) != RT_EOK))
    {
        return -RT_ETIMEOUT;
    }

    return RT_EOK;
}

static void dsi_command_mode_supported_set(uint32_t supported)
{
    DSI_FUNCPRG = (DSI_FUNCPRG & ~DSI_FUNCPRG_SDTWCM) |
                  ((supported << 13) & DSI_FUNCPRG_SDTWCM);
}

static void dsi_wrapper_rgb565_set(void)
{
    DSI_WRGBDF = 1U;
}

static rt_uint32_t dsi_byte_clock_cycles_get(rt_uint32_t time_ns,
                                             rt_uint32_t ui_count)
{
    rt_uint64_t scaled_time;

    /* Keep nanoseconds and unit intervals exact until the final ceiling. */
    scaled_time = (rt_uint64_t)time_ns * LCD_DSI_HS_RATE +
                  (rt_uint64_t)ui_count * 1000000000ULL;
    return (rt_uint32_t)DIV_ROUND_UP(scaled_time, 8000000000ULL);
}

static void dsi_timing_calculate(struct lcd_dphy_timing *timing)
{
    timing->pll_divider = LCD_DSI_HS_RATE / 2U / LCD_DSI_LP_CLOCK;
    timing->esc_ck_sel = LCD_DSI_LP_CLOCK > 20000000U ? 1U : 0U;
    timing->freq_mode = LCD_DSI_HS_RATE > 200000000U ? 1U : 0U;
    timing->lp_clkc = dsi_byte_clock_cycles_get(60U, 0U) - 1U;
    timing->dhs_prep = dsi_byte_clock_cycles_get(40U, 4U) - 1U;
    timing->dhs_zero = dsi_byte_clock_cycles_get(90U, 6U) - 1U;
    timing->dhs_trail = MAX_VALUE(1U, dsi_byte_clock_cycles_get(260U, 4U)) - 1U;
    timing->dhs_exit = dsi_byte_clock_cycles_get(230U, 0U) - 1U;
    timing->ckhs_prep = dsi_byte_clock_cycles_get(50U, 0U) - 1U;
    timing->ckhs_zero = dsi_byte_clock_cycles_get(270U, 0U) - 1U;
    timing->ckhs_trail = dsi_byte_clock_cycles_get(200U, 0U) - 1U;
    timing->ckhs_exit = dsi_byte_clock_cycles_get(230U, 0U) - 1U;
    timing->dlcfg = timing->lp_clkc + timing->dhs_prep + timing->dhs_zero + 4U;
    timing->ck_hs2lp = timing->ckhs_trail + timing->ckhs_exit + 3U;
    timing->ck_lp2hs = timing->lp_clkc + timing->ckhs_prep + timing->ckhs_zero + 6U;
}

static rt_uint32_t dsi_horizontal_count_get(rt_uint32_t pixels, rt_uint32_t byte_clock)
{
    return (rt_uint32_t)(((rt_uint64_t)pixels * byte_clock) / LCD_PIXEL_CLOCK);
}

static rt_uint32_t dsi_horizontal_count_round_up_get(rt_uint32_t pixels,
                                                      rt_uint32_t byte_clock)
{
    return (rt_uint32_t)((((rt_uint64_t)pixels * byte_clock) + LCD_PIXEL_CLOCK - 1U) /
                         LCD_PIXEL_CLOCK);
}

static rt_err_t dsi_host_init(void)
{
    struct lcd_dphy_timing timing;
    rt_uint32_t timeout = LCD_DSI_TIMEOUT;
    rt_uint32_t byte_clock = LCD_DSI_HS_RATE / 8U;
    rt_uint32_t hsa_count;
    rt_uint32_t hbp_count;
    rt_uint32_t hfp_count;
    rt_uint32_t hact_count;
    rt_uint32_t htotal_count;

    rt_memset(&timing, 0, sizeof(timing));
    dsi_timing_calculate(&timing);
    hsa_count = dsi_horizontal_count_get(LCD_HSYNC, byte_clock);
    hbp_count = dsi_horizontal_count_get(LCD_HBP, byte_clock);
    hact_count = dsi_horizontal_count_get(LCD_WIDTH, byte_clock);
    htotal_count = dsi_horizontal_count_round_up_get(LCD_HSYNC + LCD_HBP +
                                                     LCD_WIDTH + LCD_HFP,
                                                     byte_clock);
    hfp_count = htotal_count - hsa_count - hbp_count - hact_count;

    rcu_periph_clock_enable(RCU_DSI);
    rcu_dsi_preceding_stage_clock_config(RCU_DSIPRESEL_HXTAL);
    rcu_dsi_clock_div_config(RCU_DSI_DIV2);

    dsi_dphy_dfe_reset_enable();
    dsi_eot_transmission_disable();
    dsi_clock_stopping_enable();
    dsi_data_lanes_number_set(LCD_DSI_LANES);
    dsi_command_mode_supported_set(1U);
    dsi_wrapper_lp_cmd_data_source_set(DSI_LP_DATASRC_LPDATA);
    dsi_wrapper_tli_dma_mode_config(DSI_TLI_DMA_MODE_DISABLE);
    dsi_video_mode_virtual_channel_set(LCD_DSI_CHANNEL);
    dsi_wrapper_rgb565_set();
    dsi_video_mode_color_format_set(LCD_DSI_FORMAT);
    dsi_video_mode_format_set(LCD_DSI_VIDEO_MODE);
    dsi_video_bta_disable();

    dsi_hs_tx_timeout_set(0xFFFFFFU);
    dsi_lp_rx_timeout_set(0xFFFFFFU);
    dsi_turnaround_timeout_set(0x1FU);
    dsi_device_reset_timer_set(0xFFFFU);
    dsi_dpi_resolution_set(LCD_WIDTH, LCD_HEIGHT);
    dsi_horizontal_sync_active_count_set(hsa_count);
    dsi_horizontal_back_porch_count_set(hbp_count);
    dsi_horizontal_front_porch_count_set(hfp_count);
    dsi_horizontal_active_count_set(hact_count);
    dsi_vertical_sync_active_count_set(LCD_VSYNC);
    dsi_vertical_back_porch_count_set(LCD_VBP);
    dsi_vertical_front_porch_count_set(LCD_VFP);
    dsi_init_counter_set(0xD07U);

    dsi_error_auto_recovery_disable(DSI_ERR_AUTO_REC_ECC_MUL);
    dsi_error_auto_recovery_disable(DSI_ERR_AUTO_REC_INVLD_DT);
    dsi_error_auto_recovery_disable(DSI_ERR_AUTO_REC_HI_CONT);
    dsi_error_auto_recovery_disable(DSI_ERR_AUTO_REC_LO_CONT);
    dsi_error_auto_recovery_disable(DSI_ERR_AUTO_REC_HS_RX_TO);
    dsi_error_auto_recovery_disable(DSI_ERR_AUTO_REC_LP_RX_TO);

    dsi_dphy_hs_prepare_time_set(timing.dhs_prep);
    dsi_dphy_hs_zero_time_set(timing.dhs_zero);
    dsi_dphy_hs_trail_time_set(timing.dhs_trail);
    dsi_dphy_hs_exit_time_set(timing.dhs_exit);
    dsi_dphy_clk_prepare_time_set(timing.ckhs_prep);
    dsi_dphy_clk_zero_time_set(timing.ckhs_zero);
    dsi_dphy_clk_trail_time_set(timing.ckhs_trail);
    dsi_dphy_clk_exit_time_set(timing.ckhs_exit);

    DSI_DPHY_TRIMCTL1 = ((rt_uint32_t)timing.pll_divider & 0x7FU) |
                        (((rt_uint32_t)timing.esc_ck_sel & 0x1U) << 31);
    DSI_DPHY_TRIMCTL1 |= DSI_DPHY_TRIMCTL1_CDPD0;
    dsi_ddr_freq_mode_set(timing.freq_mode);
    dsi_lp_byte_clk_config(timing.lp_clkc);
    dsi_data_lane_switch_count_set(timing.dlcfg);
    dsi_clk_hs_to_lp_switch_count_set(timing.ck_hs2lp);
    dsi_clk_lp_to_hs_switch_count_set(timing.ck_lp2hs);
    dsi_device_ready_set(1U);

    while (((DSI_INTSTAT0 & DSI_INTSTAT0_INIT_DONE) == 0U) && (timeout > 0U))
    {
        timeout--;
    }

    if (timeout == 0U)
    {
        return -RT_ETIMEOUT;
    }
    if ((DSI_WINTSTAT & DSI_WINTSTAT_PLLLKS) == 0U)
    {
        LOG_E("DSI DPHY PLL failed to lock");
        return -RT_ETIMEOUT;
    }

    return RT_EOK;
}

static rt_err_t panel_init(void)
{
    rt_size_t index;
    rt_err_t result;

    lcd.backlight_pin = LCD_BACKLIGHT_PIN;

    rt_pin_mode(lcd.backlight_pin, PIN_MODE_OUTPUT);
    rt_pin_write(lcd.backlight_pin, PIN_LOW);

    /* LCD reset is tied to MCU_NRST through R13 on GD32H77x_EVB_V0.1. */
    rt_thread_mdelay(120);

    result = dsi_host_init();
    if (result != RT_EOK)
    {
        LOG_E("DSI host init timed out");
        return result;
    }

    for (index = 0U; index < sizeof(panel_init_cmds) / sizeof(panel_init_cmds[0]); index++)
    {
        result = dsi_write_cmd(panel_init_cmds[index].data, panel_init_cmds[index].len);
        if (result != RT_EOK)
        {
            LOG_E("panel command 0x%02x failed", panel_init_cmds[index].data[0]);
            return result;
        }
        if (panel_init_cmds[index].delay_ms > 0U)
        {
            rt_thread_mdelay(panel_init_cmds[index].delay_ms);
        }
    }

    LOG_I("FL7707N initialized with %u commands", (rt_uint32_t)index);

    return RT_EOK;
}

static rt_err_t mipi_power_init(void)
{
    rt_uint32_t timeout = LCD_DSI_TIMEOUT;

    pmu_mipi_ldo_enable();
    while ((pmu_flag_get(PMU_FLAG_RDYF) == RESET) && (timeout > 0U))
    {
        timeout--;
    }
    if (timeout == 0U)
    {
        return -RT_ETIMEOUT;
    }

    pmu_mipi_power_enable();
    pmu_mipi_output_isolation_enable();
    return RT_EOK;
}

static rt_err_t tli_clock_init(void)
{
    RCU_PLLALL &= ~(RCU_PLLALL_PLLSEL | RCU_PLLALL_PLL2VCOSEL | RCU_PLLALL_PLL2RNG);
    RCU_PLLALL |= RCU_PLLSRC_HXTAL | RCU_PLL2VCO_192M_836M | RCU_PLL2RNG_1M_2M;

    if (rcu_pll2_config(25U, 369U, 1U, 1U, 4U) != SUCCESS)
    {
        LOG_E("invalid PLL2 configuration");
        return -RT_EINVAL;
    }

    rcu_tli_clock_div_config(RCU_PLL2R_DIV2);
    rcu_pll_clock_output_enable(RCU_PLL2R);
    rcu_osci_on(RCU_PLL2_CK);
    if (rcu_osci_stab_wait(RCU_PLL2_CK) != SUCCESS)
    {
        LOG_E("PLL2 failed to lock");
        return -RT_ETIMEOUT;
    }

    LOG_I("TLI pixel clock: %u Hz", rcu_clock_freq_get(CK_PLL2R) / 2U);
    rcu_periph_clock_enable(RCU_TLI);
    return RT_EOK;
}

static void lcd_tli_init(void)
{
    tli_parameter_struct tli_config;
    tli_layer_parameter_struct layer_config;

    rt_memset(&tli_config, 0, sizeof(tli_config));
    tli_config.signalpolarity_hs = TLI_HSYN_ACTIVE_LOW;
    tli_config.signalpolarity_vs = TLI_VSYN_ACTIVE_LOW;
    tli_config.signalpolarity_de = TLI_DE_ACTIVE_LOW;
    tli_config.signalpolarity_pixelck = TLI_PIXEL_CLOCK_TLI;
    tli_config.synpsz_hpsz = LCD_HSYNC - 1U;
    tli_config.backpsz_hbpsz = LCD_HSYNC + LCD_HBP - 1U;
    tli_config.activesz_hasz = LCD_HSYNC + LCD_HBP + LCD_WIDTH - 1U;
    tli_config.totalsz_htsz = LCD_HSYNC + LCD_HBP + LCD_WIDTH + LCD_HFP - 1U;
    tli_config.synpsz_vpsz = LCD_VSYNC - 1U;
    tli_config.backpsz_vbpsz = LCD_VSYNC + LCD_VBP - 1U;
    tli_config.activesz_vasz = LCD_VSYNC + LCD_VBP + LCD_HEIGHT - 1U;
    tli_config.totalsz_vtsz = LCD_VSYNC + LCD_VBP + LCD_HEIGHT + LCD_VFP - 1U;
    tli_config.backcolor_red = 0U;
    tli_config.backcolor_green = 0U;
    tli_config.backcolor_blue = 0U;
    tli_init(&tli_config);

    rt_memset(&layer_config, 0, sizeof(layer_config));
    layer_config.layer_window_leftpos = LCD_HSYNC + LCD_HBP;
    layer_config.layer_window_rightpos = LCD_HSYNC + LCD_HBP + LCD_WIDTH - 1U;
    layer_config.layer_window_toppos = LCD_VSYNC + LCD_VBP;
    layer_config.layer_window_bottompos = LCD_VSYNC + LCD_VBP + LCD_HEIGHT - 1U;
    layer_config.layer_ppf = LAYER_PPF_RGB565;
    layer_config.layer_sa = 255U;
    layer_config.layer_default_alpha = 0U;
    layer_config.layer_acf1 = LAYER_ACF1_PASA;
    layer_config.layer_acf2 = LAYER_ACF2_PASA;
    layer_config.layer_frame_bufaddr = LCD_FRAMEBUFFER_ADDRESS;
    layer_config.layer_frame_line_length = LCD_WIDTH * LCD_BYTES_PER_PIXEL + 7U;
    layer_config.layer_frame_buf_stride_offset = LCD_WIDTH * LCD_BYTES_PER_PIXEL;
    layer_config.layer_frame_total_line_number = LCD_HEIGHT;
    tli_layer_init(LAYER0, &layer_config);
    tli_dither_config(TLI_DITHER_DISABLE);
    tli_layer_enable(LAYER0);
    tli_reload_config(TLI_REQUEST_RELOAD_EN);
    AXI_SPX_RDQOS_CTL(SLAVE_PORT5) =
        (AXI_SPX_RDQOS_CTL(SLAVE_PORT5) & ~AXI_SPX_RDQOS_CTL_RDQOS) | 0xFU;

    rt_completion_init(&lcd_reload_completion);
    tli_interrupt_disable(TLI_INT_LM | TLI_INT_LCR | TLI_INT_FE | TLI_INT_TE);
    tli_interrupt_flag_clear(TLI_INT_FLAG_LM | TLI_INT_FLAG_LCR |
                             TLI_INT_FLAG_FE | TLI_INT_FLAG_TE);
    nvic_irq_enable(TLI_IRQn, 5U, 0U);
    tli_enable();
}

void TLI_IRQHandler(void)
{
    rt_interrupt_enter();

    if (tli_interrupt_flag_get(TLI_INT_FLAG_LCR) != RESET)
    {
        tli_interrupt_disable(TLI_INT_LCR);
        tli_interrupt_flag_clear(TLI_INT_FLAG_LCR);
        rt_completion_done(&lcd_reload_completion);
    }
    __DSB();
    rt_interrupt_leave();
}

static rt_err_t lcd_hardware_init(void)
{
    rt_err_t result;

    if (!rt_hw_sdram_is_ready())
    {
        LOG_E("SDRAM is not ready");
        return -RT_EIO;
    }
    RT_ASSERT(LCD_FRAMEBUFFER_TOTAL_SIZE <= EXT_SDRAM_LCD_RESERVED_SIZE);
#ifdef BSP_USING_OV7670
    RT_ASSERT(LCD_FRAMEBUFFER_TOTAL_SIZE <= EXT_SDRAM_LCD_SCANOUT_SIZE);
#endif

    result = mipi_power_init();
    if (result != RT_EOK)
    {
        LOG_E("MIPI LDO ready timed out");
        return result;
    }

    dsi_deinit();

    lcd_framebuffer_fill(0x0000U);

    result = panel_init();
    if (result != RT_EOK)
    {
        return result;
    }

    result = tli_clock_init();
    if (result != RT_EOK)
    {
        LOG_E("TLI clock init failed");
        return result;
    }

    lcd_tli_init();
    DSI_INTSTAT0 = DSI_INTSTAT0_DPILTO | DSI_INTSTAT0_DPIPE;
    rt_thread_mdelay(40U);

    lcd.backlight_powered = RT_TRUE;
    result = lcd_backlight_apply();
    if (result != RT_EOK)
    {
        LOG_E("backlight PWM initialization failed: %d", result);
        return result;
    }
    LOG_I("backlight %u%% on %s channel %u (PA0 TIMER1_CH0)",
          lcd.brightness, LCD_BACKLIGHT_PWM_DEVICE_NAME,
          LCD_BACKLIGHT_PWM_CHANNEL);
    return RT_EOK;
}

static rt_err_t lcd_device_init(rt_device_t device)
{
    rt_err_t result;

    if (lcd.initialized)
    {
        return RT_EOK;
    }

    result = lcd_hardware_init();
    if (result == RT_EOK)
    {
        lcd.initialized = RT_TRUE;
    }
    return result;
}

static rt_err_t lcd_dirty_rect_include(const struct rt_device_rect_info *rect)
{
    rt_uint32_t right;
    rt_uint32_t bottom;
    rt_uint32_t dirty_right;
    rt_uint32_t dirty_bottom;

    if (rect == RT_NULL)
    {
        lcd_dirty_rect.x = 0U;
        lcd_dirty_rect.y = 0U;
        lcd_dirty_rect.width = LCD_WIDTH;
        lcd_dirty_rect.height = LCD_HEIGHT;
        lcd_dirty_valid = RT_TRUE;
        return RT_EOK;
    }

    right = (rt_uint32_t)rect->x + rect->width;
    bottom = (rt_uint32_t)rect->y + rect->height;
    if ((rect->width == 0U) || (rect->height == 0U) ||
        (right > LCD_WIDTH) || (bottom > LCD_HEIGHT))
    {
        return -RT_EINVAL;
    }

    if (!lcd_dirty_valid)
    {
        lcd_dirty_rect = *rect;
        lcd_dirty_valid = RT_TRUE;
        return RT_EOK;
    }

    dirty_right = (rt_uint32_t)lcd_dirty_rect.x + lcd_dirty_rect.width;
    dirty_bottom = (rt_uint32_t)lcd_dirty_rect.y + lcd_dirty_rect.height;
    if (rect->x < lcd_dirty_rect.x)
    {
        lcd_dirty_rect.x = rect->x;
    }
    if (rect->y < lcd_dirty_rect.y)
    {
        lcd_dirty_rect.y = rect->y;
    }
    if (right > dirty_right)
    {
        dirty_right = right;
    }
    if (bottom > dirty_bottom)
    {
        dirty_bottom = bottom;
    }
    lcd_dirty_rect.width = dirty_right - lcd_dirty_rect.x;
    lcd_dirty_rect.height = dirty_bottom - lcd_dirty_rect.y;

    return RT_EOK;
}

static void lcd_cache_flush(void *framebuffer,
                            const struct rt_device_rect_info *rect)
{
    rt_uint8_t *base = (rt_uint8_t *)framebuffer;
    rt_uint16_t row;

    if (rect == RT_NULL)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, base, LCD_FRAMEBUFFER_SIZE);
        return;
    }

    if ((rect->x == 0U) && (rect->width == LCD_WIDTH))
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH,
                             base + rect->y * LCD_WIDTH * LCD_BYTES_PER_PIXEL,
                             rect->height * LCD_WIDTH * LCD_BYTES_PER_PIXEL);
        return;
    }

    for (row = 0U; row < rect->height; row++)
    {
        rt_uint8_t *address = base +
                              ((rect->y + row) * LCD_WIDTH + rect->x) * LCD_BYTES_PER_PIXEL;
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH,
                             address,
                             rect->width * LCD_BYTES_PER_PIXEL);
    }
}

static rt_err_t lcd_pan_display(void *framebuffer)
{
    rt_ubase_t address = (rt_ubase_t)framebuffer;

    if ((address != LCD_FRAMEBUFFER_ADDRESS) &&
        (address != LCD_FRAMEBUFFER_BACK_ADDRESS))
    {
        return -RT_EINVAL;
    }
    if ((TLI_RL & (TLI_RL_RQR | TLI_RL_FBR)) != 0U)
    {
        return -RT_EBUSY;
    }

    /* Commit pixels before asking the scanout hardware to use this buffer. */
    if (lcd_dirty_valid)
    {
        lcd_cache_flush(framebuffer, &lcd_dirty_rect);
    }
    else
    {
        lcd_cache_flush(framebuffer, RT_NULL);
    }

    tli_interrupt_disable(TLI_INT_LCR);
    tli_interrupt_flag_clear(TLI_INT_FLAG_LCR);
    (void)rt_completion_wait(&lcd_reload_completion, 0);
    TLI_LXFBADDR(LAYER0) = address;
    __DSB();
    /* A sampled VDE/line IRQ cannot guarantee the task is still in blanking.
     * FBR makes the actual address change atomic with the hardware frame boundary. */
    tli_reload_config(TLI_FRAME_BLANK_RELOAD_EN);
    tli_interrupt_enable(TLI_INT_LCR);
    __DSB();
    lcd_dirty_valid = RT_FALSE;

    return RT_EOK;
}

static rt_err_t lcd_wait_vsync(void)
{
    rt_tick_t start = rt_tick_get();
    rt_tick_t timeout = rt_tick_from_millisecond(LCD_VSYNC_TIMEOUT_MS);

    while ((TLI_RL & (TLI_RL_RQR | TLI_RL_FBR)) != 0U)
    {
        rt_tick_t elapsed = rt_tick_get() - start;

        if (elapsed >= timeout)
        {
            if ((TLI_RL & (TLI_RL_RQR | TLI_RL_FBR)) == 0U)
            {
                break;
            }
            tli_interrupt_disable(TLI_INT_LCR);
            if (!lcd_reload_timeout_reported)
            {
                LOG_E("TLI layer reload timed out");
                lcd_reload_timeout_reported = RT_TRUE;
            }
            return -RT_ETIMEOUT;
        }
        (void)rt_completion_wait(&lcd_reload_completion, timeout - elapsed);
    }

    /* Hardware completion, not just waking the thread, releases the old buffer. */
    __DSB();
    lcd_reload_timeout_reported = RT_FALSE;
    return RT_EOK;
}

static rt_err_t lcd_device_control(rt_device_t device, int cmd, void *args)
{
    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
        return lcd_dirty_rect_include((const struct rt_device_rect_info *)args);

    case RTGRAPHIC_CTRL_POWERON:
        lcd.backlight_powered = RT_TRUE;
        return lcd_backlight_apply();

    case RTGRAPHIC_CTRL_POWEROFF:
        lcd.backlight_powered = RT_FALSE;
        return lcd_backlight_apply();

    case RTGRAPHIC_CTRL_SET_BRIGHTNESS:
        if (args == RT_NULL)
        {
            return -RT_EINVAL;
        }
        return lcd_backlight_set_brightness(*(rt_uint8_t *)args);

    case RTGRAPHIC_CTRL_GET_BRIGHTNESS:
        if (args == RT_NULL)
        {
            return -RT_EINVAL;
        }
        *(rt_uint8_t *)args = lcd.brightness;
        break;

    case RTGRAPHIC_CTRL_GET_INFO:
        if (args == RT_NULL)
        {
            return -RT_EINVAL;
        }
        rt_memcpy(args, &lcd.info, sizeof(lcd.info));
        break;

    case RTGRAPHIC_CTRL_PAN_DISPLAY:
        if (args == RT_NULL)
        {
            return -RT_EINVAL;
        }
        return lcd_pan_display(args);

    case RTGRAPHIC_CTRL_WAIT_VSYNC:
        return lcd_wait_vsync();

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops lcd_device_ops =
{
    lcd_device_init,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    lcd_device_control,
};
#endif

static int rt_hw_lcd_init(void)
{
    rt_memset(&lcd, 0, sizeof(lcd));
    lcd.brightness = LCD_BACKLIGHT_DEFAULT_LEVEL;
    lcd.info.pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565;
    lcd.info.bits_per_pixel = 16U;
    lcd.info.pitch = LCD_WIDTH * LCD_BYTES_PER_PIXEL;
    lcd.info.width = LCD_WIDTH;
    lcd.info.height = LCD_HEIGHT;
    lcd.info.framebuffer = (void *)LCD_FRAMEBUFFER_ADDRESS;
    lcd.info.smem_len = LCD_FRAMEBUFFER_TOTAL_SIZE;
    lcd.parent.type = RT_Device_Class_Graphic;
#ifdef RT_USING_DEVICE_OPS
    lcd.parent.ops = &lcd_device_ops;
#else
    lcd.parent.init = lcd_device_init;
    lcd.parent.control = lcd_device_control;
#endif
    lcd.parent.user_data = &lcd.info;

    return rt_device_register(&lcd.parent, LCD_DEVICE_NAME, RT_DEVICE_FLAG_RDWR);
}
INIT_DEVICE_EXPORT(rt_hw_lcd_init);

#endif /* BSP_USING_LCD_MIPI */
