/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "disp.sunxi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "sunxi-display-output.h"

#define SUNXI_TCON0_LVDS_CTL             0x0084

#define SUNXI_TOP_DSI_SRC                0x0004
#define SUNXI_TOP_LCD_CLK_SRC            0x000c
#define SUNXI_TOP_MODULE_GATE            0x0020

#define SUNXI_DSI_GCTL                   0x0000
#define SUNXI_DSI_BASIC_CTL              0x000c
#define SUNXI_DSI_BASIC_CTL0             0x0010
#define SUNXI_DSI_BASIC_CTL1             0x0014
#define SUNXI_DSI_BASIC_SIZE0            0x0018
#define SUNXI_DSI_BASIC_SIZE1            0x001c
#define SUNXI_DSI_INST_FUNC0             0x0020
#define SUNXI_DSI_INST_LOOP_SEL          0x0040
#define SUNXI_DSI_INST_LOOP_NUM          0x0044
#define SUNXI_DSI_INST_JUMP_SEL          0x0048
#define SUNXI_DSI_INST_JUMP_CFG          0x004c
#define SUNXI_DSI_INST_LOOP_NUM2         0x0054
#define SUNXI_DSI_TRANS_START            0x0060
#define SUNXI_DSI_TCON_DRQ               0x007c
#define SUNXI_DSI_PIXEL_CTL0             0x0080
#define SUNXI_DSI_PIXEL_PH               0x0090
#define SUNXI_DSI_PIXEL_PF0              0x0098
#define SUNXI_DSI_PIXEL_PF1              0x009c
#define SUNXI_DSI_SYNC_HSS               0x00b0
#define SUNXI_DSI_SYNC_HSE               0x00b4
#define SUNXI_DSI_SYNC_VSS               0x00b8
#define SUNXI_DSI_SYNC_VSE               0x00bc
#define SUNXI_DSI_BLK_HSA0               0x00c0
#define SUNXI_DSI_BLK_HSA1               0x00c4
#define SUNXI_DSI_BLK_HBP0               0x00c8
#define SUNXI_DSI_BLK_HBP1               0x00cc
#define SUNXI_DSI_BLK_HFP0               0x00d0
#define SUNXI_DSI_BLK_HFP1               0x00d4
#define SUNXI_DSI_BLK_HBLK0              0x00e0
#define SUNXI_DSI_BLK_HBLK1              0x00e4
#define SUNXI_DSI_BLK_VBLK0              0x00e8
#define SUNXI_DSI_BLK_VBLK1              0x00ec
#define SUNXI_DSI_CMD_CTL                0x0200
#define SUNXI_DSI_CMD_CTL_TX_FLAG        RT_BIT(9)
#define SUNXI_DSI_CMD_TX(n)              (0x0300 + (n) * 4)

#define SUNXI_DPHY_GCTL                  0x0000
#define SUNXI_DPHY_ANA1                  0x0050
#define SUNXI_DPHY_ANA2                  0x0054
#define SUNXI_DPHY_ANA3                  0x0058
#define SUNXI_DPHY_ANA4                  0x005c
#define SUNXI_DPHY_PLL0                  0x0104
#define SUNXI_DPHY_PLL1                  0x0108
#define SUNXI_DPHY_PLL2                  0x010c
#define SUNXI_DPHY_COMBO0                0x0110
#define SUNXI_DPHY_COMBO1                0x0114
#define SUNXI_DPHY_COMBO2                0x0118

#define SUNXI_DSI_DT_VSS                 0x01
#define SUNXI_DSI_DT_VSE                 0x11
#define SUNXI_DSI_DT_HSS                 0x21
#define SUNXI_DSI_DT_HSE                 0x31
#define SUNXI_DSI_DT_BLK                 0x19
#define SUNXI_DSI_DT_DCS_SHORT_WRITE     0x05
#define SUNXI_DSI_DT_DCS_SHORT_WRITE_PARAM 0x15
#define SUNXI_DSI_DT_DCS_LONG_WRITE      0x39
#define SUNXI_DSI_DT_RGB888              0x3e

#define SUNXI_DSI_INST_LP11              0
#define SUNXI_DSI_INST_TBA               1
#define SUNXI_DSI_INST_HSC               2
#define SUNXI_DSI_INST_HSD               3
#define SUNXI_DSI_INST_LPDT              4
#define SUNXI_DSI_INST_HSCEXIT           5
#define SUNXI_DSI_INST_NOP               6
#define SUNXI_DSI_INST_DLY               7
#define SUNXI_DSI_INST_END               15

#define SUNXI_DSI_MODE_STOP              0
#define SUNXI_DSI_MODE_TBA               1
#define SUNXI_DSI_MODE_HS                2
#define SUNXI_DSI_MODE_ESCAPE            3
#define SUNXI_DSI_MODE_HSCEXIT           4
#define SUNXI_DSI_MODE_NOP               5

static rt_uint8_t sunxi_dsi_parity(rt_uint32_t value)
{
    value ^= value >> 16;
    value ^= value >> 8;
    value ^= value >> 4;
    value ^= value >> 2;
    value ^= value >> 1;

    return value & 1;
}

/* MIPI DSI uses a shortened Hamming code over the three header bytes. */
static rt_uint8_t sunxi_dsi_ecc(rt_uint32_t header)
{
    static const rt_uint32_t masks[] =
    {
        RT_BIT(0) | RT_BIT(1) | RT_BIT(2) | RT_BIT(4) | RT_BIT(5) |
            RT_BIT(7) | RT_BIT(10) | RT_BIT(11) | RT_BIT(13) | RT_BIT(16) |
            RT_BIT(20) | RT_BIT(21) | RT_BIT(22) | RT_BIT(23),
        RT_BIT(0) | RT_BIT(1) | RT_BIT(3) | RT_BIT(4) | RT_BIT(6) |
            RT_BIT(8) | RT_BIT(10) | RT_BIT(12) | RT_BIT(14) | RT_BIT(17) |
            RT_BIT(20) | RT_BIT(21) | RT_BIT(22),
        RT_BIT(0) | RT_BIT(2) | RT_BIT(3) | RT_BIT(5) | RT_BIT(6) |
            RT_BIT(9) | RT_BIT(11) | RT_BIT(12) | RT_BIT(15) | RT_BIT(18) |
            RT_BIT(20) | RT_BIT(21) | RT_BIT(22),
        RT_BIT(1) | RT_BIT(2) | RT_BIT(3) | RT_BIT(7) | RT_BIT(8) |
            RT_BIT(9) | RT_BIT(13) | RT_BIT(14) | RT_BIT(15) | RT_BIT(19) |
            RT_BIT(20) | RT_BIT(22) | RT_BIT(23),
        RT_BIT(4) | RT_BIT(5) | RT_BIT(6) | RT_BIT(7) | RT_BIT(8) |
            RT_BIT(9) | RT_BIT(16) | RT_BIT(17) | RT_BIT(18) | RT_BIT(19) |
            RT_BIT(20) | RT_BIT(22) | RT_BIT(23),
        RT_BIT(10) | RT_BIT(11) | RT_BIT(12) | RT_BIT(13) | RT_BIT(14) |
            RT_BIT(15) | RT_BIT(16) | RT_BIT(17) | RT_BIT(18) | RT_BIT(19) |
            RT_BIT(21) | RT_BIT(22) | RT_BIT(23),
    };
    rt_uint8_t ecc = 0;
    rt_size_t index;

    for (index = 0; index < RT_ARRAY_SIZE(masks); index++)
    {
        ecc |= sunxi_dsi_parity(header & masks[index]) << index;
    }

    return ecc;
}

static rt_uint16_t sunxi_dsi_crc(const rt_uint8_t *data, rt_size_t length)
{
    rt_uint16_t crc = 0xffff;
    rt_uint32_t bit;

    while (length--)
    {
        crc ^= *data++;
        for (bit = 0; bit < 8; bit++)
        {
            crc = (crc >> 1) ^ ((crc & 1) ? 0x8408 : 0);
        }
    }

    return crc;
}

static rt_uint16_t sunxi_dsi_crc_zeroes(rt_uint32_t count)
{
    rt_uint16_t crc = 0xffff;
    rt_uint32_t bit;

    while (count--)
    {
        for (bit = 0; bit < 8; bit++)
        {
            crc = (crc >> 1) ^ ((crc & 1) ? 0x8408 : 0);
        }
    }

    return crc;
}

static rt_uint32_t sunxi_dsi_header(rt_uint8_t type, rt_uint16_t word_count)
{
    rt_uint32_t header = type | ((rt_uint32_t)word_count << 8);

    return header | ((rt_uint32_t)sunxi_dsi_ecc(header) << 24);
}

static rt_uint32_t sunxi_dsi_inst(rt_uint8_t mode, rt_uint8_t packet,
        rt_bool_t clock_lane, rt_uint8_t data_lanes)
{
    return data_lanes | (clock_lane ? RT_BIT(4) : 0) |
            ((rt_uint32_t)packet << 20) | ((rt_uint32_t)mode << 28);
}

static void sunxi_dsi_block(void *dsi, rt_uint32_t header_reg,
        rt_uint32_t footer_reg, rt_uint16_t word_count)
{
    HWREG32(dsi + header_reg) = sunxi_dsi_header(SUNXI_DSI_DT_BLK, word_count);
    HWREG32(dsi + footer_reg) = (rt_uint32_t)sunxi_dsi_crc_zeroes(word_count) << 16;
}

static void sunxi_dsi_abort(void *dsi)
{
    HWREG32(dsi + SUNXI_DSI_BASIC_CTL0) &= ~RT_BIT(0);
}

static void sunxi_dsi_commit(void *dsi)
{
    HWREG32(dsi + SUNXI_DSI_BASIC_CTL0) |= RT_BIT(0);
}

static rt_err_t sunxi_dsi_wait_for_completion(void *dsi)
{
    rt_uint32_t timeout = 500;

    while (HWREG32(dsi + SUNXI_DSI_BASIC_CTL0) & RT_BIT(0))
    {
        if (!timeout--)
        {
            return -RT_ETIMEOUT;
        }

        rt_hw_us_delay(10);
    }

    return RT_EOK;
}

static void sunxi_dsi_start_lptx(void *dsi)
{
    HWREG32(dsi + SUNXI_DSI_INST_JUMP_SEL) =
            (SUNXI_DSI_INST_LPDT << (4 * SUNXI_DSI_INST_LP11)) |
            (SUNXI_DSI_INST_END << (4 * SUNXI_DSI_INST_LPDT));
    sunxi_dsi_abort(dsi);
    sunxi_dsi_commit(dsi);
}

static rt_err_t sunxi_dsi_dcs_write(struct sunxi_display_output *output,
        rt_uint8_t type, const rt_uint8_t *payload, rt_size_t length)
{
    void *dsi = output->dsi;
    rt_uint16_t crc;
    rt_uint32_t value;
    rt_size_t index;
    rt_size_t byte;
    rt_uint8_t data;
    rt_err_t err;

    if (!payload || !length)
    {
        return -RT_EINVAL;
    }

    if ((type == SUNXI_DSI_DT_DCS_SHORT_WRITE && length != 1) ||
        (type == SUNXI_DSI_DT_DCS_SHORT_WRITE_PARAM && length != 2) ||
        (type == SUNXI_DSI_DT_DCS_LONG_WRITE && length < 3) ||
        (type != SUNXI_DSI_DT_DCS_SHORT_WRITE &&
         type != SUNXI_DSI_DT_DCS_SHORT_WRITE_PARAM &&
         type != SUNXI_DSI_DT_DCS_LONG_WRITE))
    {
        return -RT_EINVAL;
    }

    err = sunxi_dsi_wait_for_completion(dsi);
    if (err)
    {
        sunxi_dsi_abort(dsi);
    }

    HWREG32(dsi + SUNXI_DSI_CMD_CTL) = SUNXI_DSI_CMD_CTL_TX_FLAG;
    if (type == SUNXI_DSI_DT_DCS_LONG_WRITE)
    {
        HWREG32(dsi + SUNXI_DSI_CMD_TX(0)) = sunxi_dsi_header(type, length);
        crc = sunxi_dsi_crc(payload, length);

        for (index = 0; index < length + sizeof(crc); index += sizeof(value))
        {
            value = 0;
            for (byte = 0; byte < sizeof(value) &&
                    index + byte < length + sizeof(crc); byte++)
            {
                data = index + byte < length ? payload[index + byte] :
                        ((const rt_uint8_t *)&crc)[index + byte - length];

                value |= (rt_uint32_t)data << (byte * 8);
            }
            HWREG32(dsi + SUNXI_DSI_CMD_TX(1 + index / sizeof(value))) = value;
        }
        HWREG32(dsi + SUNXI_DSI_CMD_CTL) = length + sizeof(crc) + 4 - 1;
    }
    else
    {
        value = payload[0];
        if (length == 2)
        {
            value |= (rt_uint32_t)payload[1] << 8;
        }
        HWREG32(dsi + SUNXI_DSI_CMD_TX(0)) = sunxi_dsi_header(type, value);
        HWREG32(dsi + SUNXI_DSI_CMD_CTL) = 4 - 1;
    }

    sunxi_dsi_start_lptx(dsi);
    err = sunxi_dsi_wait_for_completion(dsi);
    if (err)
    {
        sunxi_dsi_abort(dsi);
    }

    return err;
}

static rt_err_t sunxi_display_output_parse_dsi(struct rt_device *dev,
        struct sunxi_display_output *output)
{
    const char *format = "rgb888";
    rt_ssize_t length;
    rt_uint32_t lanes;
    rt_err_t err;
    const char *delay_props[] =
    {
        "panel-power-off-delay-ms", "prepare-delay-ms",
        "reset-delay-ms", "init-delay-ms",
    };
    rt_uint32_t *delays[] =
    {
        &output->panel_power_off_delay_ms, &output->panel_prepare_delay_ms,
        &output->panel_reset_delay_ms, &output->panel_init_delay_ms,
    };

    output->dsi_lanes = 4;
    if (!rt_dm_dev_prop_read_u32(dev, "dsi,lanes", &lanes))
    {
        if (lanes < 1 || lanes > 4)
        {
            return -RT_EINVAL;
        }
        output->dsi_lanes = lanes;
    }
    if (output->dsi_lanes < 1 || output->dsi_lanes > 4)
    {
        return -RT_EINVAL;
    }

    if (!rt_ofw_prop_read_string(dev->ofw_node, "dsi,format", &format) &&
        rt_strcmp(format, "rgb888"))
    {
        LOG_E("%s: only rgb888 DSI video is supported", rt_dm_dev_get_name(dev));
        return -RT_ENOSYS;
    }

    output->panel_init_sequence = rt_ofw_prop_read_raw(dev->ofw_node,
            "panel-init-sequence", &length);
    if (output->panel_init_sequence && length > 0)
    {
        output->panel_init_sequence_len = length;
    }

    if (rt_dm_dev_prop_read_bool(dev, "enable-gpios"))
    {
        output->panel_enable_pin = rt_pin_get_named_pin(dev, "enable", 0,
                RT_NULL, &output->panel_enable_active);
        if (output->panel_enable_pin < 0)
        {
            return output->panel_enable_pin;
        }
    }
    if (rt_dm_dev_prop_read_bool(dev, "reset-gpios"))
    {
        output->panel_reset_pin = rt_pin_get_named_pin(dev, "reset", 0,
                RT_NULL, &output->panel_reset_active);
        if (output->panel_reset_pin < 0)
        {
            return output->panel_reset_pin;
        }
    }
    for (rt_size_t i = 0; i < RT_ARRAY_SIZE(delay_props); ++i)
    {
        if (!rt_dm_dev_prop_read_bool(dev, delay_props[i]))
        {
            continue;
        }
        err = rt_dm_dev_prop_read_u32(dev, delay_props[i], delays[i]);
        if (err || *delays[i] > 10000)
        {
            return err ? err : -RT_EINVAL;
        }
    }

    return RT_EOK;
}

rt_err_t sunxi_display_output_parse(struct rt_device *dev,
        struct sunxi_display_output *output)
{
    const char *type = "rgb";

    rt_memset(output, 0, sizeof(*output));
    output->panel_enable_pin = PIN_NONE;
    output->panel_reset_pin = PIN_NONE;
    output->panel_reset_delay_ms = 10;
    output->panel_init_delay_ms = 120;

    if (!rt_ofw_prop_read_string(dev->ofw_node, "allwinner,output", &type))
    {
        if (!rt_strcmp(type, "lvds"))
        {
            output->type = SUNXI_DISPLAY_OUTPUT_LVDS;
        }
        else if (!rt_strcmp(type, "dsi"))
        {
            output->type = SUNXI_DISPLAY_OUTPUT_DSI;
        }
        else if (rt_strcmp(type, "rgb"))
        {
            LOG_E("%s: unsupported display output %s", rt_dm_dev_get_name(dev), type);
            return -RT_EINVAL;
        }
    }

    output->lvds_8bit = rt_dm_dev_prop_read_bool(dev, "allwinner,lvds-8bit");
    output->lvds_jeida = rt_dm_dev_prop_read_bool(dev, "allwinner,lvds-jeida");
    rt_dm_dev_prop_read_u32(dev, "allwinner,lvds-polarity", &output->lvds_polarity);

    if (output->type == SUNXI_DISPLAY_OUTPUT_DSI)
    {
        return sunxi_display_output_parse_dsi(dev, output);
    }

    return RT_EOK;
}

static rt_err_t sunxi_dphy_setup(struct sunxi_display_output *output,
        const struct sunxi_fb_timing *timing)
{
    rt_uint32_t lane_mask = RT_BIT(output->dsi_lanes) - 1;
    rt_uint64_t frequency = (rt_uint64_t)timing->pixelclock * 24 / output->dsi_lanes;
    rt_uint64_t vco_frequency = frequency;
    rt_uint32_t multiplier = 1;
    rt_uint32_t coefficient = 24 / output->dsi_lanes;
    rt_uint32_t divider_n;
    rt_uint32_t divider_m2;
    rt_uint32_t divider_m3;
    rt_uint32_t pll0;

    while (vco_frequency < 1100000000)
    {
        multiplier++;
        vco_frequency += frequency;
    }

    divider_n = (rt_uint32_t)(vco_frequency / 24000000);
    divider_m2 = !(coefficient % 3) ? 3 : (!(coefficient % 2) ? 2 : 1);
    divider_m3 = multiplier * coefficient / divider_m2;

    if (!divider_n || divider_n > 0xff || multiplier > 16 || divider_m3 > 16)
    {
        LOG_E("DSI pixel clock %u is outside Combo PHY range", timing->pixelclock);
        return -RT_EINVAL;
    }

    /* F101 requires this calibrated analog value before enabling the PHY. */
    HWREG32(output->dphy + SUNXI_DPHY_ANA4) = 0x84313480;
    HWREG32(output->dphy + SUNXI_DPHY_ANA2) = RT_BIT(1) | RT_BIT(4);
    HWREG32(output->dphy + SUNXI_DPHY_ANA3) = RT_BIT(16) | RT_BIT(17) |
            RT_BIT(18) | RT_BIT(19) | RT_BIT(20) | (lane_mask << 21);
    HWREG32(output->dphy + SUNXI_DPHY_ANA1) = RT_BIT(31);

    /* The CCU supplies 24 MHz. Program the F101 Combo PHY video PLL. */
    pll0 = ((multiplier - 1) << 0) | (divider_n << 8) |
            RT_BIT(20) | RT_BIT(22) |
            ((divider_m3 - 1) << 24) | ((divider_m2 - 1) << 28) | RT_BIT(31);
    HWREG32(output->dphy + SUNXI_DPHY_PLL0) = pll0;
    HWREG32(output->dphy + SUNXI_DPHY_PLL1) = RT_BIT(12) | RT_BIT(23) | RT_BIT(22);
    HWREG32(output->dphy + SUNXI_DPHY_PLL2) = 0;
    HWREG32(output->dphy + SUNXI_DPHY_COMBO0) = RT_BIT(0) | RT_BIT(1) | RT_BIT(3);
    HWREG32(output->dphy + SUNXI_DPHY_COMBO2) = 20;
    rt_hw_us_delay(20);
    HWREG32(output->dphy + SUNXI_DPHY_GCTL) = RT_BIT(0);

    return RT_EOK;
}

static rt_err_t sunxi_dsi_setup(struct sunxi_display_output *output,
        const struct sunxi_fb_timing *timing)
{
    rt_uint32_t lane_mask = RT_BIT(output->dsi_lanes) - 1;
    rt_uint32_t hsa;
    rt_uint32_t hbp_bytes;
    rt_uint32_t hfp;
    rt_uint32_t hblk;
    rt_uint32_t vblk = 0;
    rt_uint32_t remainder;

    if (timing->hsync_len < 4 || timing->hback_porch < 4 ||
        timing->hfront_porch < 4)
    {
        LOG_E("DSI sync and porch values must be at least four pixels");
        return -RT_EINVAL;
    }

    hsa = timing->hsync_len * 3 - 10;
    hbp_bytes = timing->hback_porch * 3 - 10;
    hfp = timing->hfront_porch * 3 - 12;
    hblk = (timing->htotal - timing->hsync_len) * 3 - 10;

    if (output->dsi_lanes == 4)
    {
        remainder = (timing->htotal * 3 * timing->vtotal - hblk - 6) % 4;
        vblk = remainder ? 4 - remainder : 0;
    }

    /* DSI source and TCON-to-DSI clock gate live in DISPLAY_TOP. */
    HWREG32(output->top + SUNXI_TOP_DSI_SRC) &= ~RT_BIT(0);
    HWREG32(output->top + SUNXI_TOP_LCD_CLK_SRC) |= RT_BIT(0) | RT_BIT(4);
    HWREG32(output->top + SUNXI_TOP_MODULE_GATE) |= RT_BIT(16);

    HWREG32(output->dsi + SUNXI_DSI_GCTL) = 0;
    HWREG32(output->dsi + SUNXI_DSI_BASIC_CTL) = 0;
    HWREG32(output->dsi + SUNXI_DSI_BASIC_CTL0) = RT_BIT(16) | RT_BIT(17);
    HWREG32(output->dsi + SUNXI_DSI_BASIC_CTL1) = RT_BIT(0) | RT_BIT(1) |
            RT_BIT(2) | (1 << 4);
    HWREG32(output->dsi + SUNXI_DSI_BASIC_SIZE0) = timing->vsync_len |
            (timing->vback_porch << 16);
    HWREG32(output->dsi + SUNXI_DSI_BASIC_SIZE1) = timing->vactive |
            (timing->vtotal << 16);
    HWREG32(output->dsi + SUNXI_DSI_TRANS_START) = 10;
    HWREG32(output->dsi + SUNXI_DSI_TCON_DRQ) = timing->hfront_porch > 20 ?
            ((timing->hfront_porch - 20) * 3 / 32) | RT_BIT(24) : 0;

    HWREG32(output->dsi + SUNXI_DSI_PIXEL_CTL0) = 8 | RT_BIT(16);
    HWREG32(output->dsi + SUNXI_DSI_PIXEL_PH) =
            sunxi_dsi_header(SUNXI_DSI_DT_RGB888, timing->hactive * 3);
    HWREG32(output->dsi + SUNXI_DSI_PIXEL_PF0) = 0xffff;
    HWREG32(output->dsi + SUNXI_DSI_PIXEL_PF1) = 0xffffffff;

    HWREG32(output->dsi + SUNXI_DSI_SYNC_HSS) = sunxi_dsi_header(SUNXI_DSI_DT_HSS, 0);
    HWREG32(output->dsi + SUNXI_DSI_SYNC_HSE) = sunxi_dsi_header(SUNXI_DSI_DT_HSE, 0);
    HWREG32(output->dsi + SUNXI_DSI_SYNC_VSS) = sunxi_dsi_header(SUNXI_DSI_DT_VSS, 0);
    HWREG32(output->dsi + SUNXI_DSI_SYNC_VSE) = sunxi_dsi_header(SUNXI_DSI_DT_VSE, 0);
    sunxi_dsi_block(output->dsi, SUNXI_DSI_BLK_HSA0, SUNXI_DSI_BLK_HSA1, hsa);
    sunxi_dsi_block(output->dsi, SUNXI_DSI_BLK_HBP0, SUNXI_DSI_BLK_HBP1, hbp_bytes);
    sunxi_dsi_block(output->dsi, SUNXI_DSI_BLK_HFP0, SUNXI_DSI_BLK_HFP1, hfp);
    sunxi_dsi_block(output->dsi, SUNXI_DSI_BLK_HBLK0, SUNXI_DSI_BLK_HBLK1, hblk);
    sunxi_dsi_block(output->dsi, SUNXI_DSI_BLK_VBLK0, SUNXI_DSI_BLK_VBLK1, vblk);

    HWREG32(output->dsi + SUNXI_DSI_INST_FUNC0 + 4 * SUNXI_DSI_INST_LP11) =
            sunxi_dsi_inst(SUNXI_DSI_MODE_STOP, 0, RT_TRUE, lane_mask);
    HWREG32(output->dsi + SUNXI_DSI_INST_FUNC0 + 4 * SUNXI_DSI_INST_TBA) =
            sunxi_dsi_inst(SUNXI_DSI_MODE_TBA, 0, RT_FALSE, 1);
    HWREG32(output->dsi + SUNXI_DSI_INST_FUNC0 + 4 * SUNXI_DSI_INST_HSC) =
            sunxi_dsi_inst(SUNXI_DSI_MODE_HS, 0, RT_TRUE, 0);
    HWREG32(output->dsi + SUNXI_DSI_INST_FUNC0 + 4 * SUNXI_DSI_INST_HSD) =
            sunxi_dsi_inst(SUNXI_DSI_MODE_HS, 0, RT_FALSE, lane_mask);
    HWREG32(output->dsi + SUNXI_DSI_INST_FUNC0 + 4 * SUNXI_DSI_INST_LPDT) =
            sunxi_dsi_inst(SUNXI_DSI_MODE_ESCAPE, 1, RT_FALSE, 1);
    HWREG32(output->dsi + SUNXI_DSI_INST_FUNC0 + 4 * SUNXI_DSI_INST_HSCEXIT) =
            sunxi_dsi_inst(SUNXI_DSI_MODE_HSCEXIT, 0, RT_TRUE, 0);
    HWREG32(output->dsi + SUNXI_DSI_INST_FUNC0 + 4 * SUNXI_DSI_INST_NOP) =
            sunxi_dsi_inst(SUNXI_DSI_MODE_STOP, 0, RT_FALSE, lane_mask);
    HWREG32(output->dsi + SUNXI_DSI_INST_FUNC0 + 4 * SUNXI_DSI_INST_DLY) =
            sunxi_dsi_inst(SUNXI_DSI_MODE_NOP, 0, RT_TRUE, lane_mask);
    HWREG32(output->dsi + SUNXI_DSI_INST_LOOP_SEL) =
            (SUNXI_DSI_INST_HSC << (4 * SUNXI_DSI_INST_LP11)) |
            (SUNXI_DSI_INST_HSD << (4 * SUNXI_DSI_INST_DLY));
    HWREG32(output->dsi + SUNXI_DSI_INST_LOOP_NUM) = 49 | (49 << 16);
    HWREG32(output->dsi + SUNXI_DSI_INST_LOOP_NUM2) = 49 | (49 << 16);
    HWREG32(output->dsi + SUNXI_DSI_INST_JUMP_CFG) =
            1 | (SUNXI_DSI_INST_NOP << 16) | (SUNXI_DSI_INST_HSCEXIT << 20);
    HWREG32(output->dsi + SUNXI_DSI_GCTL) = RT_BIT(0);

    return sunxi_dphy_setup(output, timing);
}

static void sunxi_lvds_setup(struct sunxi_display_output *output)
{
    rt_uint32_t lvds_ctl = RT_BIT(20) |
            (output->lvds_polarity & 0x1f);

    if (output->lvds_8bit)
    {
        lvds_ctl |= RT_BIT(26);
    }
    if (output->lvds_jeida)
    {
        lvds_ctl |= RT_BIT(27);
    }

    /* Route TCON0's pixel clock through Combo PHY0 before enabling LVDS. */
    HWREG32(output->top + SUNXI_TOP_LCD_CLK_SRC) |= RT_BIT(0) | RT_BIT(4);
    HWREG32(output->tcon + SUNXI_TCON0_LVDS_CTL) = lvds_ctl;
    HWREG32(output->dphy + SUNXI_DPHY_COMBO1) = 0x53;
    HWREG32(output->dphy + SUNXI_DPHY_COMBO0) = RT_BIT(0);
    rt_hw_us_delay(5);
    HWREG32(output->dphy + SUNXI_DPHY_COMBO0) = RT_BIT(0) | RT_BIT(2);
    rt_hw_us_delay(5);
    HWREG32(output->dphy + SUNXI_DPHY_COMBO0) = RT_BIT(0) | RT_BIT(1) | RT_BIT(2);
    rt_hw_us_delay(5);
    HWREG32(output->dphy + SUNXI_DPHY_ANA4) = 0x84000000;
    HWREG32(output->dphy + SUNXI_DPHY_ANA3) = 0x01040000;
    HWREG32(output->dphy + SUNXI_DPHY_ANA2) = 0;
    HWREG32(output->dphy + SUNXI_DPHY_ANA1) = 0;
}

static void sunxi_display_panel_prepare(struct sunxi_display_output *output)
{
    if (output->panel_prepared)
    {
        return;
    }

    if (output->panel_reset_pin >= 0)
    {
        rt_pin_write(output->panel_reset_pin, output->panel_reset_active);
        rt_pin_mode(output->panel_reset_pin, PIN_MODE_OUTPUT);
    }
    if (output->panel_enable_pin >= 0)
    {
        rt_pin_write(output->panel_enable_pin, !output->panel_enable_active);
        rt_pin_mode(output->panel_enable_pin, PIN_MODE_OUTPUT);
        if (output->panel_power_off_delay_ms)
        {
            rt_thread_mdelay(output->panel_power_off_delay_ms);
        }
        rt_pin_write(output->panel_enable_pin, output->panel_enable_active);
    }
    if (output->panel_prepare_delay_ms)
    {
        rt_thread_mdelay(output->panel_prepare_delay_ms);
    }
    if (output->panel_reset_pin >= 0)
    {
        rt_thread_mdelay(output->panel_reset_delay_ms);
        rt_pin_write(output->panel_reset_pin, !output->panel_reset_active);
        rt_thread_mdelay(output->panel_init_delay_ms);
    }
    output->panel_prepared = RT_TRUE;
}

rt_err_t sunxi_display_output_prepare(struct sunxi_display_output *output,
        const struct sunxi_fb_timing *timing)
{
    switch (output->type)
    {
    case SUNXI_DISPLAY_OUTPUT_RGB:
        return RT_EOK;

    case SUNXI_DISPLAY_OUTPUT_LVDS:
        if (!output->dphy || !output->top)
        {
            return -RT_ENOENT;
        }
        sunxi_lvds_setup(output);
        return RT_EOK;

    case SUNXI_DISPLAY_OUTPUT_DSI:
        if (!output->dsi || !output->dphy || !output->top)
        {
            return -RT_ENOENT;
        }
        sunxi_display_panel_prepare(output);
        return sunxi_dsi_setup(output, timing);
    }

    return -RT_EINVAL;
}

rt_err_t sunxi_display_output_panel_init(struct sunxi_display_output *output)
{
    const rt_uint8_t *sequence;
    rt_size_t remaining;

    if (output->type != SUNXI_DISPLAY_OUTPUT_DSI ||
        !output->panel_init_sequence_len)
    {
        return RT_EOK;
    }

    sequence = output->panel_init_sequence;
    remaining = output->panel_init_sequence_len;
    while (remaining)
    {
        rt_uint8_t type;
        rt_uint8_t delay_ms;
        rt_uint8_t payload_length;
        rt_err_t err;

        if (remaining < 3)
        {
            return -RT_EINVAL;
        }

        type = *sequence++;
        delay_ms = *sequence++;
        payload_length = *sequence++;
        remaining -= 3;
        if (!payload_length || payload_length > remaining)
        {
            return -RT_EINVAL;
        }

        err = sunxi_dsi_dcs_write(output, type, sequence, payload_length);
        if (err)
        {
            return err;
        }

        sequence += payload_length;
        remaining -= payload_length;
        if (delay_ms)
        {
            rt_thread_mdelay(delay_ms);
        }
    }

    return RT_EOK;
}

void sunxi_display_output_enable(struct sunxi_display_output *output)
{
    if (output->type == SUNXI_DISPLAY_OUTPUT_LVDS)
    {
        HWREG32(output->tcon + SUNXI_TCON0_LVDS_CTL) |= RT_BIT(31);
    }
    else if (output->type == SUNXI_DISPLAY_OUTPUT_DSI)
    {
        /* Enter high speed on the data lanes before starting the clock lane. */
        HWREG32(output->dsi + SUNXI_DSI_INST_JUMP_SEL) =
                (SUNXI_DSI_INST_NOP << (4 * SUNXI_DSI_INST_LP11)) |
                (SUNXI_DSI_INST_HSD << (4 * SUNXI_DSI_INST_NOP)) |
                (SUNXI_DSI_INST_DLY << (4 * SUNXI_DSI_INST_HSD)) |
                (SUNXI_DSI_INST_NOP << (4 * SUNXI_DSI_INST_DLY)) |
                (SUNXI_DSI_INST_END << (4 * SUNXI_DSI_INST_HSCEXIT));
        HWREG32(output->dsi + SUNXI_DSI_BASIC_CTL0) &= ~RT_BIT(0);
        HWREG32(output->dsi + SUNXI_DSI_BASIC_CTL0) |= RT_BIT(0);
        HWREG32(output->dsi + SUNXI_DSI_INST_JUMP_SEL) =
                (SUNXI_DSI_INST_HSC << (4 * SUNXI_DSI_INST_LP11)) |
                (SUNXI_DSI_INST_END << (4 * SUNXI_DSI_INST_HSC));
        HWREG32(output->dsi + SUNXI_DSI_BASIC_CTL0) &= ~RT_BIT(0);
        HWREG32(output->dsi + SUNXI_DSI_BASIC_CTL0) |= RT_BIT(0);
    }
}

void sunxi_display_output_disable(struct sunxi_display_output *output)
{
    if (output->type == SUNXI_DISPLAY_OUTPUT_DSI)
    {
        if (output->dsi)
        {
            HWREG32(output->dsi + SUNXI_DSI_GCTL) = 0;
        }
        if (output->dphy)
        {
            HWREG32(output->dphy + SUNXI_DPHY_GCTL) = 0;
            HWREG32(output->dphy + SUNXI_DPHY_COMBO0) = 0;
        }
        if (output->top)
        {
            HWREG32(output->top + SUNXI_TOP_MODULE_GATE) &= ~RT_BIT(16);
        }
    }
    else if (output->type == SUNXI_DISPLAY_OUTPUT_LVDS)
    {
        if (output->tcon)
        {
            HWREG32(output->tcon + SUNXI_TCON0_LVDS_CTL) = 0;
        }
        if (output->dphy)
        {
            HWREG32(output->dphy + SUNXI_DPHY_COMBO1) = 0;
            HWREG32(output->dphy + SUNXI_DPHY_COMBO0) = 0;
            HWREG32(output->dphy + SUNXI_DPHY_ANA4) = 0;
        }
    }

    if (output->panel_prepared)
    {
        if (output->panel_reset_pin >= 0)
        {
            rt_pin_write(output->panel_reset_pin, output->panel_reset_active);
        }
        if (output->panel_enable_pin >= 0)
        {
            rt_pin_write(output->panel_enable_pin, !output->panel_enable_active);
        }
        output->panel_prepared = RT_FALSE;
    }
}
